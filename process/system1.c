/*
 * 模仿system函数。
 * zhanghexie
 * 2020-12-26
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  // 父进程fork
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork()");
    exit(1);
  } else if (0 == pid) {
    fflush(NULL);
    // 子进程exec
    execl("/bin/sh", "sh", "-c", "date +%s", NULL);
    perror("execl()");
    exit(1);
  }
  
  // 父进程wait
  wait(NULL);
  exit(0);
}