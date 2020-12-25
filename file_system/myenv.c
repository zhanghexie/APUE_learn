/*
 * 输出所有环境变量
 * zhanghexie
 * 2020-12-23
 */

#include <stdio.h>
#include <stdlib.h>

extern char** environ;

int main(int argc, char* argv[]) {
  for (int i = 0; environ[i] != NULL; ++i) {
    puts(environ[i]);
  }
  exit(0);
}