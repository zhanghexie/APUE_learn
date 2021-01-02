/*
 * 加入互斥量使得四个线程依次输出abcd
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

static pthread_mutex_t muts[THRNUM];

static void* thr_func(void* arg) {
  char c = 'a' + (int)arg;
  while (1) {
    pthread_mutex_lock(muts + (int)arg);
    write(1, &c, 1);
    pthread_mutex_unlock((muts + ((int)arg + 1) % THRNUM));
  }
}
int main() {
  pthread_t tids[THRNUM];
  for (int i = 0; i < THRNUM; ++i) {
    pthread_mutex_init(muts + i, NULL);
    pthread_mutex_lock(muts + i);
    int err = pthread_create(&tids[i], NULL, thr_func, (void*)i);
    if (0 != err) {
      fprintf(stderr, "thread create failed : %s", strerror(err));
    }
  }

  pthread_mutex_unlock(muts);
  alarm(3);

  for (int i = 0; i < THRNUM; ++i) {
    pthread_join(tids[i], NULL);
  }
  exit(0);
}
