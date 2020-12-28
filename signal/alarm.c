/*
 * alarm()函数。
 * zhanghexie
 * 2020-12-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  // 这样写无法通过alarm实现多个定时器
  alarm(20);
  alarm(10);
  alarm(1);
  while (1) pause();
  exit(0);
}