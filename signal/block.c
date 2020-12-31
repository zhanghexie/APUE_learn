/*
 * sigprocmask函数。
 * zhanghexie
 * 2020-12-29
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void int_handler(int s) { write(1, "!", 1); }

int main() {
  signal(SIGINT, int_handler);

  sigset_t set, oset, saveset;
  sigemptyset(&set);
  sigaddset(&set, SIGINT);
  // 确保set中的信号不阻塞，并保存之前mask的状态
  sigprocmask(SIG_UNBLOCK, &set, &saveset);
  while (1) {
    // 阻塞set中的信号
    sigprocmask(SIG_BLOCK, &set, &oset);
    for (int i = 0; i < 10; ++i) {
      write(1, "*", 1);
      sleep(1);
    }
    // sigprocmask(SIG_UNBLOCK, &set, NULL);
    sigprocmask(SIG_SETMASK, &oset, NULL);
    write(1, "\n", 1);
  }
  // 恢复之前状态
  sigprocmask(SIG_SETMASK, &saveset, NULL);
  exit(0);
}
