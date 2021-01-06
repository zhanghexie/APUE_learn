/*
 * 中继程序，使用epoll监视文件描述符解决盲等问题。
 * zhanghexie
 * 2021-1-4
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define TTY1 "/dev/tty11"
#define TTY2 "/dev/tty12"
#define BUFFSIZE 1024

enum { STATE_R = 1, STATE_W, STATE_AUTO, STATE_Ex, STATE_T };

struct fsm_st {
  int state;
  int sfd;
  int dfd;
  char buf[BUFFSIZE];
  int len;
  int pos;
  char* err;
};

static int max(int a, int b) { return a > b ? a : b; }

static void fsm_driver(struct fsm_st* fsm) {
  switch (fsm->state) {
    case STATE_R: {
      fsm->len = read(fsm->sfd, fsm->buf, BUFFSIZE);
      if (0 == fsm->len) {
        fsm->state = STATE_T;
      } else if (fsm->len < 0) {
        if (errno == EAGAIN) {
          fsm->state = STATE_R;
        } else {
          fsm->err = "read()";
          fsm->state = STATE_Ex;
        }
      } else {
        fsm->pos = 0;
        fsm->state = STATE_W;
      }
      break;
    }

    case STATE_W: {
      int ret = write(fsm->dfd, fsm->buf + fsm->pos, fsm->len);
      if (ret < 0) {
        if (errno == EAGAIN) {
          fsm->state = STATE_W;
        } else {
          fsm->err = "write()";
          fsm->state = STATE_Ex;
        }
      } else {
        fsm->pos += ret;
        fsm->len -= ret;
        if (0 == fsm->len) {
          fsm->state = STATE_R;
        } else {
          fsm->state = STATE_W;
        }
      }
      break;
    }

    case STATE_Ex: {
      fprintf(stderr, fsm->err);
      fsm->state = STATE_T;
      break;
    }

    case STATE_T: {
      // do something!
      break;
    }

    default: {
      abort();
      break;
    }
  }
}

static void relay(int fd1, int fd2) {
  struct fsm_st fsm12, fsm21;
  struct epoll_event ev;

  //全部转化为非阻塞状态
  int fd1_save = fcntl(fd1, F_GETFL);
  fcntl(fd1, F_SETFL, fd1_save | O_NONBLOCK);
  int fd2_save = fcntl(fd2, F_GETFL);
  fcntl(fd2, F_SETFL, fd2_save | O_NONBLOCK);

  fsm12.state = STATE_R;
  fsm12.sfd = fd1;
  fsm12.dfd = fd2;

  fsm21.state = STATE_R;
  fsm21.sfd = fd2;
  fsm21.dfd = fd1;

  int epfd = epoll_create(10);
  if (epfd < 0) {
    perror("epoll_create()");
    exit(1);
  }
  ev.events = 0;
  ev.data.fd = fd1;
  epoll_ctl(epfd, EPOLL_CTL_ADD, fd1, &ev);
  ev.events = 0;
  ev.data.fd = fd2;
  epoll_ctl(epfd, EPOLL_CTL_ADD, fd2, &ev);

  while (fsm12.state != STATE_T || fsm21.state != STATE_T) {
    // 布置监视任务
    ev.data.fd = fd1;
    ev.events = 0;
    if (STATE_R == fsm12.state) {
      ev.events |= EPOLLIN;
    }
    if (STATE_W == fsm21.state) {
      ev.events |= EPOLLOUT;
    }
    epoll_ctl(epfd, EPOLL_CTL_MOD, fd1, &ev);

    ev.data.fd = fd2;
    ev.events = 0;
    if (STATE_R == fsm21.state) {
      ev.events |= EPOLLIN;
    }
    if (STATE_W == fsm12.state) {
      ev.events |= EPOLLOUT;
    }
    epoll_ctl(epfd, EPOLL_CTL_MOD, fd2, &ev);

    // 监视
    if (fsm12.state < STATE_AUTO || fsm21.state < STATE_AUTO) {
      while (epoll_wait(epfd, &ev, 1, -1) < 0) {
        if (EINTR == errno) {
          continue;
        }
        perror("epoll()");
        exit(1);
      }
    }

    // 查看监视结果
    if (ev.data.fd == fd1 && ev.events & EPOLLIN ||
        ev.data.fd == fd2 && ev.events & EPOLLOUT || fsm12.state > STATE_AUTO) {
      fsm_driver(&fsm12);
    }
    if (ev.data.fd == fd2 && ev.events & EPOLLIN ||
        ev.data.fd == fd1 && ev.events & EPOLLOUT || fsm21.state > STATE_AUTO) {
      fsm_driver(&fsm21);
    }
  }

  fcntl(fd1, F_SETFL, fd1_save);
  fcntl(fd2, F_SETFL, fd2_save);

  close(epfd);
}

int main() {
  int fd1, fd2;
  fd1 = open(TTY1, O_RDWR);
  if (fd1 < 0) {
    perror("open()");
    exit(1);
  }
  write(fd1, "TTY1\n", 5);

  fd2 = open(TTY2, O_RDWR | O_NONBLOCK);
  if (fd1 < 0) {
    perror("open()");
    exit(1);
  }
  write(fd2, "TTY2\n", 5);

  relay(fd1, fd2);

  close(fd1);
  close(fd2);
  exit(0);
}