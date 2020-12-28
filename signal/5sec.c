/*
 * 累加5s。
 * zhanghexie
 * 2020-12-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

int main() {
  int64_t count = 0;
  time_t end = time(NULL) + 5;
  while (time(NULL) <= end) {
    count++;
  }
  printf("%lld\n", count);
  exit(0);
}