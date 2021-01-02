/*
 * 四个线程输出abcd
 * zhanghexie
 * 2021-1-1
 */

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define THRNUM 4

static void* thr_func(void* arg) {
  char c = 'a' + (int)arg;
  while (1) {
    write(1, &c, 1);
  }
}
int main() {
  pthread_t tids[THRNUM];

  for (int i = 0; i < THRNUM; ++i) {
    int err = pthread_create(&tids[i], NULL, thr_func, (void*)i);
    if (0 != err) {
      fprintf(stderr, "thread create failed : %s", strerror(err));
    }
  }

  alarm(3);

  for (int i = 0; i < THRNUM; ++i) {
    pthread_join(tids[i], NULL);
  }
  exit(0);
}
