/*
 * 获取文件有效字符数
 * zhanghexie
 * 2020-12-13
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  FILE* fp = NULL;
  int count = 0;

  if (argc < 2) {
    fprintf(stderr, "Usage:%s <file>\n", argv[0]);
    exit(1);
  }

  fp = fopen(argv[1], "r");
  if (NULL == fp) {
    perror("fopen()");
  }

  while (EOF != fgetc(fp)) {
    ++count;
  }

  printf("count = %d\n", count);
  fclose(fp);
  exit(0);
}