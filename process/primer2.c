/*
 * 加入资源释放操作
 * zhanghexie
 * 2020-12-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#define LEFT 2
#define RIGHT 30000200

int main() {
  int mask = 0;
  pid_t pid;
  for (int i = LEFT; i <= RIGHT; ++i) {
    mask = 0;
    pid = fork();
    if (pid < 0) {
      perror("fork()");
      exit(0);
    } else if (0 == pid) {
      for (int j = 2; j * j <= i; ++j) {
        if (0 == i % j) {
          mask = 1;
          break;
        }
      }
      if (!mask) {
        printf("%d is primer\n", i);
      }
      exit(0);  // !!! 非常重要，不然子进程也会不断fork进程
    }
  }
  for (int i = LEFT; i <= RIGHT; ++i) {
    wait(NULL);
  }
  exit(0);
}