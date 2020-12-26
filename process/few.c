/*
 * 凑齐fork，exec，wait三个函数。
 * zhanghexie
 * 2020-12-26
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  puts("Begin!!!");
  fflush(NULL);  // !!!

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork()");
    exit(1);
  } else if (0 == pid) {
    fflush(NULL);
    execl("/bin/date", "date", "+%s", NULL);
    perror("execl()");
    exit(1);
  }

  wait(NULL);
  puts("End!!!");
  exit(0);
}