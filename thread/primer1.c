/*
 * 通过多线程的方式筛质数,改用结构体传参数
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

struct thr_arg_st {
  int n;
};

void* is_primer(void* arg) {
  int i = ((struct thr_arg_st*)arg)->n;
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
  return(arg);
}

int main() {
  pthread_t tid[THRUNM];
  struct thr_arg_st* p;

  for (int i = 0; i < THRUNM; ++i) {
    p = malloc(sizeof(*p));
    if (NULL == p) {
      perror("malloc()");
      exit(1);
    }
    p->n = LEFT + i;
    int err = pthread_create(&tid[i], NULL, is_primer, p);
    if (0 != err) {
      fprintf(stderr, "pthread_create fail%s", strerror(err));
      exit(0);
    }
  }

  void *ptr;
  for (int i = 0; i < THRUNM; ++i) {
    pthread_join(tid[i], &ptr);
    free(ptr);
  }
  exit(0);
}