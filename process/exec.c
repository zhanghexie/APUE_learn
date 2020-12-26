/*
 * 学习exec函数。
 * zhanghexie
 * 2020-12-26
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  puts("Begin!!!");
  fflush(NULL);  // !!!
  // 第一个参数是执行函数名，第二个及之后的要传函数参数（从argv[0]开始），最后NULL结尾。
  // argv[0]可以和实际运行的程序名称不一致，利用这一点可以隐藏。
  execl("/bin/date", "date", "+%s", NULL);
  perror("execl()");
  exit(1);
  puts("End!!!");
  exit(0);
}