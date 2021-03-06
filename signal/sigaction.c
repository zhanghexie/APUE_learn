/*
 * 学习sigaction函数。
 * zhanghexie
 * 2020-12-31
 */

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define FNAME "/tmp/out"

static FILE* fp;

static void deamon_exit(int s) {
  fclose(fp);
  closelog();
  exit(0);
}

// 实现守护进程
static int daemonize() {
  // 父进程fork
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork()");
    return -1;
  } else if (pid > 0) {
    exit(0);
  }
  // 下面内容只有子进程执行
  // 脱离标准流
  int fd = open("/dev/null", O_RDWR);
  if (fd < 0) {
    perror("open()");
    return -1;
  }
  dup2(fd, 0);
  dup2(fd, 1);
  dup2(fd, 2);
  if (fd > 2) {
    close(fd);
  }
  // 创建新的会话
  setsid();

  // 切换工作目录，防止磁盘卸载
  chdir("/");

  // 如果有必要还可以更改umask(0);
  return 0;
}

int main() {
  // 这样做可能被信号相应时可能被其他信号打断
  // signal(SIGINT,deamon_exit);
  // signal(SIGQUIT,deamon_exit);
  // signal(SIGTERM,deamon_exit);

  struct sigaction sa;
  sa.sa_handler = deamon_exit;
  sigemptyset(&sa.sa_mask);
  sigaddset(&sa.sa_mask, SIGTERM);
  sigaddset(&sa.sa_mask, SIGQUIT);
  sigaddset(&sa.sa_mask, SIGINT);
  sa.sa_flags = 0;
  sigaction(SIGINT, &sa, NULL);
  sigaction(SIGTERM, &sa, NULL);
  sigaction(SIGQUIT, &sa, NULL);

  fp = fopen(FNAME, "w");

  if (0 != daemonize()) {
    exit(1);
  }

  if (NULL == fp) {
    perror("fopen()");
    exit(1);
  }

  for (size_t i = 0;; ++i) {
    fprintf(fp, "%d\n", i);
    fflush(fp);
    sleep(1);
  }
}