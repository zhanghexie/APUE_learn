/*
 * 检验用户密码是否正确
 * 编译时要加-lcrypt
 * 运行时使用root权限
 * zhanghexie
 * 2020-12-23
 */

#include <crypt.h>
#include <pwd.h>
#include <shadow.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage %s <user_id>\n");
    exit(1);
  }
  char *inputPass;
  struct spwd *shadowLine;
  char *cyptedPass = NULL;
  
  // 用户输入密码
  inputPass = getpass("PassWord:");
  // 获取shadow原文
  shadowLine = getspnam(argv[1]);
  cyptedPass = crypt(inputPass, shadowLine->sp_pwdp);

  if(0 == strcmp(cyptedPass,shadowLine->sp_pwdp)) {
    printf("yes!\n");
  }else{
    printf("no!!!\n");
  }
  exit(0);
}