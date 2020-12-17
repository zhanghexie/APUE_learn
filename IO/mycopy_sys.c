/*
 * 用系统调用复制文件
 * zhanghexie
 * 2020-12-14
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#ifndef BUFSIZE
#define BUFSIZE 1024
#endif
int main(int argc, char* argv[]) {
  // 出错时返回负值不要用char。
  int ch;
  int sfd, dfd;
  char buf[BUFSIZE];

  if (argc < 3) {
    fprintf(stderr, "Usage:%s <src_file> <dst_file>\n", argv[0]);
    exit(1);
  }

  sfd = open(argv[1], O_RDONLY);
  if (sfd < 0) {
    perror("open()");
    exit(1);
  }

  dfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600);
  if (dfd < 0) {
    close(sfd);
    perror("open()");
    exit(1);
  }

  int len, ret;
  while (1) {
    len = read(sfd, buf, BUFSIZE);
    if (len < 0) {
      perror("read()");
      break;
    }
    if (0 == len) {
      break;
    }
    int pos = 0;
    while (len > 0) {
      ret = write(dfd, buf + pos, len);
      if (ret < 0) {
        exit(1);
      }
      pos += ret;
      len -= ret;
    }
  }
  close(dfd);
  close(sfd);
  exit(0);
}
