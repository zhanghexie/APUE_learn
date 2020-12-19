/*
 * 测试文件类型
 * zhanghexie
 * 2020-12-19
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

static int ftype(const char*fname) {
  struct stat statres;
  if(stat(fname, &statres) < 0) {
    perror("stat()");
    exit(0);
  }
  if (S_ISREG(statres.st_mode)){
    return '-';
  }else if(S_ISDIR(statres.st_mode)) {
    return 'd';
  }else if(S_ISCHR(statres.st_mode)) {
    return 'c';
  }else if(S_ISBLK(statres.st_mode)) {
    return 'b';
  }else if(S_ISFIFO(statres.st_mode)) {
    return 'f';
  }else if(S_ISLNK(statres.st_mode)) {
    return 'l';
  }else if(S_ISSOCK(statres.st_mode)) {
    return 's';
  } else{
    return '?';
  }
}

int main(int argc, char* argv[]) {
  if(argc < 2) {
    fprintf(stderr,"Usage %s <filename>\n", argv[0]);
    exit(1);
  }
  printf("%c\n",ftype(argv[1]));

  exit(0);
}