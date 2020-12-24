/*
 * 向文件里输出时间
 * zhanghexie
 * 2020-12-23
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define FILE_NAME "/tmp/out"
#define BUF_SIZE 1024

int main(int argc, char* argv[]) {
  FILE* fp;
  fp = fopen(FILE_NAME, "a+");
  if (NULL == fp) {
    perror("fopen()");
    exit(1);
  }

  char buf[BUF_SIZE];
  int count = 0;
  while (NULL != fgets(buf, BUF_SIZE, fp)) {
    ++count;
  }

  time_t stamp;
  struct tm* tm;
  while (1) {
    time(&stamp);
    tm = localtime(&stamp);
    fprintf(fp, "%-4d%d-%d-%d %d:%d:%d\n", count++, tm->tm_year + 1900,
            tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    //文件流采用全缓冲模式，手动刷新一下比较好。
    fflush(fp);
    sleep(1);
  }
  fclose(fp);
  exit(0);
}