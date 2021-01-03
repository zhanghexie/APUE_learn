#include "mysem.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct mysem_t {
  int value;
  pthread_mutex_t mut;
  pthread_cond_t cond;
};

mysem_t* mysem_int(int initVal) {
  struct mysem_t* me;
  me = malloc(sizeof(*me));
  if (NULL == me) {
    return NULL;
  }
  me->value = initVal;
  pthread_mutex_init(&me->mut, NULL);
  pthread_cond_init(&me->cond, NULL);

  return me;
}

int mysem_add(mysem_t* sem, int num) {
  if (num < 0) {
    return -1;
  }

  struct mysem_t* me = sem;
  pthread_mutex_lock(&me->mut);
  me->value += num;
  pthread_cond_broadcast(&me->cond);
  pthread_mutex_unlock(&me->mut);

  return num;
}

int mysem_sub(mysem_t* sem, int num) {
  if (num < 0) {
    return -1;
  }

  struct mysem_t* me = sem;
  pthread_mutex_lock(&me->mut);
  while (me->value <= num) {
    pthread_cond_wait(&me->cond, &me->mut);
  }
  me->value -= num;
  pthread_mutex_unlock(&me->mut);

  return num;
}

int mysem_destory(mysem_t* sem) {
  struct mysem_t* me = sem;
  pthread_mutex_destroy(&me->mut);
  pthread_cond_destroy(&me->cond);
  free(me);

  return 0;
}