/*
 * 学习内存映射,数一个文件中a的个数。
 * zhanghexie
 * 2021-1-4
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage %s <file_name>", argv[0]);
    exit(1);
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    perror("open()");
    exit(1);
  }

  struct stat statres;
  if (fstat(fd, &statres) < 0) {
    perror("fstat");
    exit(1);
  }

  char *str = mmap(NULL, statres.st_size, PROT_READ, MAP_SHARED, fd, 0);
  if (MAP_FAILED == str) {
    perror("mmap()");
    exit(1);
  }

  int count = 0;
  for (int i = 0; i < statres.st_size; ++i) {
    if (str[i] == 'a') {
      ++count;
    }
  }

  printf("%d\n", count);

  close(fd);
  munmap(str, statres.st_size);
  exit(0);
}
