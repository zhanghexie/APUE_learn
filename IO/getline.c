/*
 * getline用法
 * zhanghexie
 * 2020-12-13
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {

  // 变量值不初始化会报段错误。
  FILE *fp = NULL;
  char *linebuf = NULL;
  size_t linsize = 0;

  if (argc < 2) {
    fprintf(stderr, "Usage %s <file>\n", argv[0]);
    exit(1);
  }

  fp = fopen(argv[1], "r");
  if (NULL == fp) {
    perror("fopen()");
    exit(1);
  }
  while (1) {
    if (getline(&linebuf, &linsize, fp) < 0) {
      break;
    }
    printf("linebuf:%d\n", strlen(linebuf));
    printf("linesize:%d\n", linsize);
  }

  fclose(fp);
}