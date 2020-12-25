/*
 * 使用readdir等函数获取给定目录下的所有文件。
 * zhanghexie
 * 2020-12-21
 */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  
  if(argc < 2) {
    fprintf(stderr, "Usege %s <dir_name>\n", argv[0]);
    exit(1);
  }

  DIR *dp;
  struct dirent *cur;

  dp = opendir(argv[1]);
  if (!dp) {
    perror("opendir()");
    exit(1);
  }

  while ((cur = readdir(dp))) {
    puts(cur->d_name);
  }

  closedir(dp);
  exit(0);
}