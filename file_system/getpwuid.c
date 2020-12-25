/*
 * 通过用户id获取用户名
 * zhanghexie
 * 2020-12-23
 */

#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage %s <user_id>");
    exit(1);
  }

  struct passwd* pwd;
  if (!(pwd = getpwuid(atoi(argv[1])))) {
    printf("user id not exist！\n");
    exit(1);
  } else {
    printf("uaername: %s\n", pwd->pw_name);
  }
  exit(0);
}