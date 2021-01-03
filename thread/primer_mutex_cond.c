/*
 * 通过多线程的方式筛质数,加入条件变量，变成非忙等版本。
 * zhanghexie
 * 2021-1-2
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEFT 30000000
#define RIGHT 30000200
#define THRUNM 10

static int num = 0;
static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_num = PTHREAD_COND_INITIALIZER;

void* is_primer(void* arg) {
  while (1) {
    pthread_mutex_lock(&mut_num);
    while (0 == num) {
      pthread_cond_wait(&cond_num, &mut_num);
    }
    if (-1 == num) {
      pthread_mutex_unlock(&mut_num);
      break;
    }
    int i = num;
    num = 0;
    pthread_cond_broadcast(&cond_num);
    pthread_mutex_unlock(&mut_num);
    int mask = 0;
    mask = 0;
    for (int j = 2; j * j <= i; ++j) {
      if (0 == i % j) {
        mask = 1;
        break;
      }
    }
    if (!mask) {
      printf("[%d]%d is primer\n", (int)arg, i);
    }
  }
  pthread_exit(NULL);
}

int main() {
  // 开启进程
  pthread_t tid[THRUNM];
  for (int i = 0; i < THRUNM; ++i) {
    int err = pthread_create(&tid[i], NULL, is_primer, (void*)i);
    if (0 != err) {
      fprintf(stderr, "pthread_create fail%s", strerror(err));
      exit(0);
    }
  }

  // 分发任务
  for (int i = LEFT; i < RIGHT; ++i) {
    pthread_mutex_lock(&mut_num);
    while (0 != num) {
      pthread_cond_wait(&cond_num, &mut_num);
    }
    num = i;
    pthread_cond_signal(&cond_num);
    pthread_mutex_unlock(&mut_num);
  }

  // 最后置为-1
  pthread_mutex_lock(&mut_num);
  while (0 != num) {
    pthread_mutex_unlock(&mut_num);
    sched_yield();  //出让调度器给其它进程
    pthread_mutex_lock(&mut_num);
  }
  num = -1;
  pthread_cond_broadcast(&cond_num);
  pthread_mutex_unlock(&mut_num);

  // 释放资源
  for (int i = 0; i < THRUNM; ++i) {
    pthread_join(tid[i], NULL);
  }

  pthread_mutex_destroy(&mut_num);
  exit(0);
}