/*
 * 用getc,putc复制文件
 * zhanghexie
 * 2020-12-12
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
  FILE *fps, *fpd;
  // 出错时返回负值不要用char。
  int ch;

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

  while (1) {
    ch = fgetc(fps);
    if (EOF == ch) break;
    fputc(ch, fpd);
  }

  puts("well down!");
  fclose(fpd);
  fclose(fps);
  exit(0);
}
