/*
 * 用fputs，fgets复制文件
 * zhanghexie
 * 2020-12-13
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFSIZE 1024

int main(int argc, char* argv[]) {
  FILE *fps, *fpd;
  char buf[BUFFSIZE];

  if(argc < 3) {
    fprintf(stderr,"Usage:%s <src_file> <dst_file>\n",argv[0]);
    exit(1);
  }

  fps = fopen(argv[1], "r");
  if (NULL == fps) {
    perror("fopen(fps)");
    exit(1);
  }

  fpd = fopen(argv[2], "w");
  if (NULL == fpd) {
    // 不过关闭会导致内存泄漏。
    fclose(fps);
    perror("fopen(fpd)");
    exit(1);
  }

  while (NULL != fgets(buf,BUFFSIZE,fps)) {
    fputs(buf,fpd);
  }

  puts("well down!");
  fclose(fpd);
  fclose(fps);
  exit(0);
}