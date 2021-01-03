/*
 * 用系统调用复制文件
 * zhanghexie
 * 2021-1-2
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

#include "mytbf.h"
#define CPS 10
#define BUFSIZE 1024
#define BURST 100

int main(int argc, char* argv[]) {
  // 出错时返回负值不要用char。
  int sfd, dfd = 1;
  int token = 0;
  char buf[BUFSIZE];

  if (argc < 2) {
    fprintf(stderr, "Usage:%s <src_file>\n", argv[0]);
    exit(1);
  }

  mytbf_st* tbf = mytbf_init(CPS, BURST);
  if (!tbf) {
    fprintf(stderr, "tbf init failed");
    exit(0);
  }

  do {
    sfd = open(argv[1], O_RDONLY);
    if (sfd < 0) {
      if (errno != EINTR) {
        perror("open()");
        exit(1);
      }
    }
  } while (sfd < 0);

  int len, ret, size;
  while (1) {
    size = mytbf_fetchtoken(tbf, BUFSIZE);
    if (size < 0) {
      fprintf(stderr, "mytbf_fetchtoken() failed :%s", strerror(-size));
      exit(-1);
    }
    // 读
    while (len = read(sfd, buf, size)) {
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

    if (size - len > 0) {
      mytbf_returntoken(tbf, size - len);
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
  mytbf_destory(tbf);
  close(sfd);
  exit(0);
}
