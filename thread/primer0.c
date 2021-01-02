/*
 * 通过多线程的方式筛质数
 * zhanghexie
 * 2020-12-31
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEFT 30000000
#define RIGHT 30000200
#define THRUNM RIGHT - LEFT + 1

void* is_primer(void* arg) {
  int i = LEFT+ (int)arg;
  int mask = 0;
  mask = 0;
  for (int j = 2; j * j <= i; ++j) {
    if (0 == i % j) {
      mask = 1;
      break;
    }
  }
  if (!mask) {
    printf("%d is primer\n", i);
  }
}

int main() {
  pthread_t tid[THRUNM];
  for (int i = 0; i < THRUNM; ++i) {
    int err = pthread_create(&tid[i], NULL, is_primer, (void*)i);
    if (0 != err) {
      fprintf(stderr, "pthread_create fail%s", strerror(err));
      exit(0);
    }
  }

  for (int i = 0; i < THRUNM; ++i) {
    pthread_join(tid[i], NULL);
  }
  exit(0);
}