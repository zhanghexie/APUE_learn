/*
 * 累加5s，使用信号。
 * zhanghexie
 * 2020-12-27
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// 不加volatile时，gcc通过O1优化程序后会卡死。
static volatile int loop = 1;
static void alarm_handler(int s) { loop = 0; }

int main() {
  int64_t count = 0;
  alarm(5);
  signal(SIGALRM, alarm_handler);
  while (loop) {
    count++;
  }
  printf("%lld\n", count);
  exit(0);
}