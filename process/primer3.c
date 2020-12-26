/*
 * 筛质数单进程,修复perimer1,perimer2中的bug使用固定数量进程。
 * zhanghexie
 * 2020-12-26
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LEFT  2
#define RIGHT 30000200
#define N 200
int main() {
  int mask = 0;
  pid_t pid;
  for (int n = 0; n < N; ++n) {
    pid = fork();
    if (pid < 0) {
      perror("fork()");
      exit(0);
    } else if (0 == pid) {
      for (int i = LEFT + n; i <= RIGHT; i += N) {
        mask = 0;
        for (int j = 2; j * j <= i; ++j) {
          if (0 == i % j) {
            mask = 1;
            break;
          }
        }
        if (!mask) {
          printf("[%d],%d is primer\n", n, i);
        }
      }
      exit(0);
    }
  }
  for (int n = 0; n < N; ++n) {
    wait(NULL);
  }
  exit(0);
}