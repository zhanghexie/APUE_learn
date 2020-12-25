/*
 * 筛质数单进程
 * zhanghexie
 * 2020-12-25
 */

#include <stdio.h>
#include <stdlib.h>
#define LEFT 2
#define RIGHT 30000200

int main() {
  int mask = 0;
  for (int i = LEFT; i <= RIGHT; ++i) {
    mask = 0;
    for (int j = 2; j * j <= i; ++j) {
      if (0 == i % j) {
        mask = 1;
        break;
      }
    }
    if (!mask) {
      printf("%d is primer\n", i);
    }
  }
}