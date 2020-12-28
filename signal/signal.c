/*
 * signal函数。
 * zhanghexie
 * 2020-12-27
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void int_handler(int s) {
  write(1, "!", 1);
  return;
}

int main() {
  // signal(SIGINT, SIG_IGN); //忽略中断信号
  signal(SIGINT, int_handler);  //收到中断信号打印感叹号

  for (int i = 0; i < 10; ++i) {
    write(1, "*", 1);
    sleep(1);
  }
  exit(0);
}