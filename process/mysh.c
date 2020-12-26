/*
 * 一个简单的shell程序。
 * zhanghexie
 * 2020-12-26
 */
#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define DELIMS " \t\n"

struct cmd_st {
  glob_t globres;
};

static void promot(void) {
  printf("mysh-0.1$ ");
  return;
}

static void parse(char *line, struct cmd_st *res) {
  char *tok = NULL;
  int i = 0;
  while (1) {
    tok = strsep(&line, DELIMS);
    if (tok == NULL) {
      break;
    }
    if ('\0' == tok[0]) {
      continue;
    }
    glob(tok, GLOB_NOCHECK | GLOB_APPEND * i, NULL, &(res->globres));
    i = 1;
  }
}

int main() {
  struct cmd_st cmd;
  char *linebuf = NULL;
  size_t linebuf_size = 0;
  while (1) {
    promot();                                 //打印提示符
    getline(&linebuf, &linebuf_size, stdin);  //获取命令
    parse(linebuf, &cmd);                     //解析命令

    if (0) {  //内部命令
      //暂时不处理
    } else {  // 外部命令
      fflush(NULL);
      pid_t pid = fork();
      if (pid < 0) {
        perror("fork()");
        exit(1);
      } else if (0 == pid) {
        fflush(NULL);
        execvp(cmd.globres.gl_pathv[0], cmd.globres.gl_pathv);
        perror("execvp");
        exit(1);
      }
      wait(NULL);
    }
  }
}