/*
 * 输出文件大小。
 * zhanghexie
 * 2020-12-18
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static off_t flen(char* pathName) {
  struct stat st;
  if (stat(pathName, &st) < 0) {
    perror("stat()");
    exit(1);
  }
  return st.st_size;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Use %s <file_name>", argv[0]);
    exit(1);
  }

  printf("File:%s\tSize:%lld\n", argv[1], flen(argv[1]));
}