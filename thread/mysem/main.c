/*
 * 通过多线程的方式筛质数,通过条件变量限制资源总数
 * zhanghexie
 * 2020-1-2
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "mysem.h"
#define LEFT 30000000
#define RIGHT 30000200
#define THRUNM RIGHT - LEFT + 1
#define N 4

static void* is_primer(void*);

static mysem_t* sem;

int main() {
  pthread_t tid[THRUNM];
  sem = mysem_int(N);
  if (NULL == sem) {
    fprintf(stderr, "init failed");
  }

  for (int i = 0; i < THRUNM; ++i) {
    mysem_sub(sem, 1);
    int err = pthread_create(&tid[i], NULL, is_primer, (void*)i);
    if (err) {
      fprintf(stderr, "pthread_create fail%s", strerror(err));
      exit(0);
    }
  }

  for (int i = 0; i < THRUNM; ++i) {
    pthread_join(tid[i], NULL);
  }
  exit(0);
}

static void* is_primer(void* arg) {
  int i = LEFT + (int)arg;
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

  sleep(5);
  mysem_add(sem, 1);
  pthread_exit(NULL);
}
