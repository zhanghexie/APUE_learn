/*
 * 加入互斥量使得四个线程依次输出abcd,加入条件变量。
 * zhanghexie
 * 2021-1-2
 */

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define THRNUM 4

static pthread_mutex_t muts = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static num = 0;

static void* thr_func(void* arg) {
  char c = 'a' + (int)arg;
  while (1) {
    pthread_mutex_lock(&muts);
    while (num != (int)arg) {
      pthread_cond_wait(&cond, &muts);
    }
    write(1, &c, 1);
    num = ((int)arg + 1) % THRNUM;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&muts);
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

  pthread_cond_destroy(&cond);
  pthread_mutex_destroy(&muts);

  exit(0);
}
