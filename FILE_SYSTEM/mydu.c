/*
 * 仿写du命令，查查目录大小。
 * zhanghexie
 * 2020-12-21
 */

#include <dirent.h>
#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define PATHSIZE 4096

// 判断目录是否指向自己或上级目录
static int path_nolopp(const char *path) {  
  char *pos = strrchr(path, '/');

  if (!pos) {
    exit(1);
  }

  if (0 == strcmp(pos + 1, ".") || 0 == strcmp(pos + 1, "..")) {
    return 0;
  } else {
    return 1;
  }
}

// 主函数返回目录或文件的大小单位为KB
static long long mydu(char *path) {
  int sum = 0;
  static struct stat statres;

  if (lstat(path, &statres) < 0) {
    perror("lstat()");
    exit(1);
  }

  //非目录文件
  if (!S_ISDIR(statres.st_mode)) {
    return statres.st_blocks / 2;
  }

  //目录文件
  glob_t globres;  // glob_t是typedef 定义的别名
  static char nextPath[PATHSIZE];
  
  sum = statres.st_blocks / 2;  //加上目录文件本身
  strncpy(nextPath, path, PATHSIZE);
  strncat(nextPath, "/*", PATHSIZE-1);
  glob(nextPath, 0, NULL, &globres);
  strncpy(nextPath, path, PATHSIZE);
  strncat(nextPath, "/.*", PATHSIZE-1);
  glob(nextPath, GLOB_APPEND, NULL, &globres);
  for (int i = 0; i < globres.gl_pathc; ++i) {
    if (path_nolopp(globres.gl_pathv[i])) {
      sum += mydu(globres.gl_pathv[i]);
    }
  }

  globfree(&globres);
  return sum;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usege %s <dir_name>\n", argv[0]);
    exit(1);
  }
  mydu(argv[1]);
  printf("%d\n", mydu(argv[1]));
  exit(0);
}