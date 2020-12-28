/*
 * 使用日志函数。
 * zhanghexie
 * 2020-12-26
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>
#define FNAME "/tmp/out"

static int daemonize() {
  pid_t pid = fork();
  if (pid < 0) {
    return -1;
  } else if (pid > 0) {
    return -1;
  }
  int fd = open("/dev/null", O_RDWR);
  if (fd < 0) {
    return -1;
  }
  dup2(fd, 0);
  dup2(fd, 1);
  dup2(fd, 2);
  if (fd > 2) {
    close(fd);
  }
  setsid();
  chdir("/");
  return 0;
}

int main() {
  // 和系统日志建立连接
  openlog("mydaemon", LOG_PID, LOG_DAEMON);

  FILE *fp = fopen(FNAME, "w");

  if (daemonize()) {
    // 错误日志
    syslog(LOG_ERR, "daemonize() failed!");
    exit(1);
  } else {
    // 信息日志
    syslog(LOG_INFO, "daemonize() sunccessded!");
  }

  if (NULL == fp) {
    syslog(LOG_ERR, "fopen():%s", strerror(errno));
    exit(1);
  }

  syslog(LOG_INFO, "The file %s opened", FNAME);

  for (size_t i = 0;; ++i) {
    fprintf(fp, "%d\n", i);
    fflush(fp);
    syslog(LOG_DEBUG, "The file is writed");
    sleep(1);
  }

  fclose(fp);
  // 关闭日志
  closelog();
  exit(0);
}