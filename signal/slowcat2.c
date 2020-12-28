/*
 * 加入令牌桶
 * zhanghexie
 * 2020-12-28
 */

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define CPS 10
#define BUFSIZE CPS
#define BURST 100

static volatile int token = 0;
static void alarm_handler(int s) {
  alarm(1);
  ++token;
  token = token > BURST ? BURST : token;
}

int main(int argc, char* argv[]) {
  // 出错时返回负值不要用char。
  int sfd, dfd = 1;
  char buf[BUFSIZE];

  if (argc < 2) {
    fprintf(stderr, "Usage:%s <src_file>\n", argv[0]);
    exit(1);
  }

  signal(SIGALRM, alarm_handler);
  alarm(1);

  do {
    sfd = open(argv[1], O_RDONLY);
    if (sfd < 0) {
      if (errno != EINTR) {
        perror("open()");
        exit(1);
      }
    }
  } while (sfd < 0);

  int len, ret;
  while (1) {
    // 有令牌才能读
    while (token <= 0) {
      pause();
    }
    --token;

    // 读
    while (len = read(sfd, buf, BUFSIZE)) {
      if (len < 0) {
        if (errno != EINTR) {
          perror("read()");
          exit(0);
        }
      } else {
        break;
      }
    }
    if (0 == len) {
      break;
    }

    // 写
    int pos = 0;
    while (len > 0) {
      while (ret = write(dfd, buf + pos, len)) {
        if (ret < 0) {
          if (errno != EINTR) {
            perror("write()");
            exit(0);
          }
        } else {
          break;
        }
      }
      if (ret < 0) {
        exit(1);
      }
      pos += ret;
      len -= ret;
    }
  }
  close(sfd);
  exit(0);
}
