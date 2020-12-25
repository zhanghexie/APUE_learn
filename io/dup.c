#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#define FNAME "/tmp/out"

int main() {
  int fd;

  fd = open(FNAME, O_WRONLY | O_CREAT | O_TRUNC, 0777);
  if(fd < 0) {
    perror("open()");
    exit(1);
  }
  
  // 如果没有使用文件描述符号就会出错，不原子
  // close(1);
  // dup(fd);

  dup2(fd,1);
  
  if(fd != 1) {
      clse(1);
  }

  puts("hello");
  exit(0);
}