/*
 * 打开文件
 * zhanghexie
 * 2020-12-12
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int main() {
//   FILE *fp;
//   fp = fopen("tmp","r");
//   if (NULL == fp) {
//     fprintf(stderr, "fopen()fialed!errno = %d\n", errno);
//     exit(1);
//   }
//   puts("ok!");
// }

int main() {
  FILE *fp;
  fp = fopen("tmp", "r");
  if (NULL == fp) {
    // fprintf(stderr, "fopen()fialed!errno = %d\n", errno);
    // 打印系统错误信息
    perror("fopen()");
    // 打印系统错误信息
    fprintf(stderr, "fopen(): %s\n", strerror(errno));
    exit(1);
  }
  puts("ok!");
  fclose(fp);
  exit(0);
}