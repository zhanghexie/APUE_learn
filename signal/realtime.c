/*
 * 学习实时信号。
 * zhanghexie
 * 2020-12-31
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
static void rs_handler(int s) { write(1, "!", 1); }

int main() {
  signal(SIGRTMIN+6, rs_handler);

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
    sigsuspend(&oset);
    write(1, "\n", 1);
  }
  exit(0);
}
