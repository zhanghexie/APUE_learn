/*
 * 创建size很大，但占用空间很小的文件。
 * zhanghexie
 * 2020-12-19
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char* argv[]) {
  int fd;
  if(argc < 2) {
    fprintf(stderr,"Usage %s <filename>\n", argv[0]);
    exit(1);
  }

  fd = open(argv[1],O_WRONLY | O_CREAT | O_TRUNC, 0777);
  if(fd < 0) {
    perror("fopen()");
  }

  lseek(fd, 5ll*1024ll*1024ll*1024ll-1ll, SEEK_SET);
  write(fd," ",1);
  close(fd);
  exit(0);
}