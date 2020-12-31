/*
 * 信号驱动程序。
 * zhanghexie
 * 2020-12-31
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
  sigprocmask(SIG_UNBLOCK, &set, &saveset);
  sigprocmask(SIG_BLOCK, &set, &oset);
  while (1) {
    for (int i = 0; i < 10; ++i) {
      write(1, "*", 1);
      sleep(1);
    }
    // sigset_t tmpset;
    // sigprocmask(SIG_SETMASK, &oset, &tmpset);
    // pause();
    // sigprocmask(SIG_SETMASK, &tmpset, NULL);
    // suspend相当于上面几句的原子操作
    sigsuspend(&oset);
    write(1, "\n", 1);
  }
  // sigprocmask(SIG_SETMASK, &saveset, NULL);
  exit(0);
}
