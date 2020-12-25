/*
 * 用fread，fwrite实现复制文件
 * zhanghexie
 * 2020-12-12
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFSIZE 1024

int main(int argc, char* argv[]) {
  FILE *fps, *fpd;
  char buf[BUFFSIZE];
  int num; // 保存读到字节数。

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

  while ((num = fread(buf,1,BUFFSIZE,fps)) > 0) {
    fwrite(buf,1,num,fpd);
  }

  puts("well down!");
  fclose(fpd);
  fclose(fps);
  exit(0);
}