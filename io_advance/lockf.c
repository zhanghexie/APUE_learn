/*
 * 多进程并发，将一个文件中的数字加1。
 * zhanghexie
 * 2020-1-4
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PROCNUM 20
#define FILENAME "/tmp/out"
#define BUFFSIZE 1024

void fun_add(void) {
  FILE* fp;
  char buf[BUFFSIZE];

  fp = fopen(FILENAME, "r+");
  if (NULL == fp) {
    perror("fopen()");
    exit(1);
  }

  lockf(fileno(fp), F_LOCK, 0);
  fgets(buf, BUFFSIZE, fp);
  int i = atoi(buf) + 1;
  rewind(fp);
  fprintf(fp, "%d\n", i);
  fflush(fp);
  lockf(fileno(fp), F_ULOCK, 0);
  fclose(fp);
}

int main() {
  for (int i = 0; i < PROCNUM; ++i) {
    pid_t pid = fork();
    if (pid < 0) {
      perror("fork()");
      exit(1);
    }
    if (0 == pid) {
      fun_add();
      exit(0);
    }
  }

  for (int i = 0; i < PROCNUM; ++i) {
    wait(NULL);
  }
  exit(0);
}