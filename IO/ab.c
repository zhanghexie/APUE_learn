/*
 * 验证文件IO与系统IO不可混用 
 * zhanghexie
 * 2020-12-14
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  // 等价与putc('a',stdout)。
  putchar('a');
  write(1,"b",1);

  putchar('a');
  write(1,"b",1);

  putchar('a');
  write(1,"b",1);

  exit(0);
}