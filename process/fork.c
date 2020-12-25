/*
 * fork函数学习
 * zhanghexie
 * 2020-12-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid;
  printf("[%d] : begin fork\n", getpid());
  fflush(NULL);  // !!!非常重要,不刷新重定向后上面一句会打印两次（因为全缓冲）。
  pid = fork();
  if (pid < 0) {
    perror("fork()");
    exit(1);
  } else if (0 == pid) {
    printf("[%d] : Child is working!!!\n", getpid());
  } else {
    printf("[%d] : Parent is working!!!\n", getpid());
  }
  printf("[%d] : end fork\n", getpid());
  exit(0);
}