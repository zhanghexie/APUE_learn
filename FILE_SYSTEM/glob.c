/*
 * 学习glob函数的使用
 * zhanghexie
 * 2020-12-21
 */
#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PAT "./*.c"

static int errfun_(const char* errpath, int eerrno) {
  puts(errpath);
  fprintf(stderr, "ERROR MSG:%s\n", strerror(eerrno));
  return eerrno;
}
int main() {
  glob_t globers;
  int err = glob(PAT, 0, NULL, &globers);
  if (err) {
    printf("Error code = %d\n", err);
  }

  for (int i = 0; i < globers.gl_pathc; ++i) {
    puts(globers.gl_pathv[i]);
  }
  
  globfree(&globers);

  exit(0);
}