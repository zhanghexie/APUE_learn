/*
 * 学习内存映射,实现父子进程之间的通信。
 * zhanghexie
 * 2021-1-4
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MEMSIZE 1024
int main() {
  char *ptr = mmap(NULL, MEMSIZE, PROT_READ | PROT_WRITE,
                   MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (MAP_FAILED == ptr) {
    perror("mmap()");
    exit(1);
  }

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    munmap(ptr, MEMSIZE);
    exit(1);
  }
  if (0 == pid) {
    strcpy(ptr, "hello!");
    munmap(ptr, MEMSIZE);
    exit(0);
  } else {
    wait(NULL);
    puts(ptr);
    munmap(ptr, MEMSIZE);
    exit(0);
  }
}
