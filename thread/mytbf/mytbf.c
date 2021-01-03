
#include "mytbf.h"

#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct mytbf_st {
  int cps;
  int burst;
  int token;
  int pos;
  pthread_mutex_t mut;
  pthread_cond_t cond;
};
static struct mytbf_st* job[MYBTF_MAX];
static pthread_mutex_t mut_job = PTHREAD_MUTEX_INITIALIZER;
pthread_t tid_alarm;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;

static int min(int a, int b) { return a > b ? b : a; }

static int get_free_pos_unlocked() {
  for (int i = 0; i < MYBTF_MAX; ++i) {
    if (!job[i]) {
      return i;
    }
  }
  return -1;
}

static void modle_unload() {
  pthread_cancel(tid_alarm);
  pthread_cancel(tid_alarm);
  for (int i = 0; i < MYBTF_MAX; ++i) {
    free(job[i]);
  }
  fflush(NULL);
  pthread_mutex_destroy(&mut_job);
}

static void* thr_alarm(void* arg) {
  while (1) {
    pthread_mutex_lock(&mut_job);
    for (int i = 0; i < MYBTF_MAX; ++i) {
      if (job[i] != NULL) {
        pthread_mutex_lock(&(job[i]->mut));
        job[i]->token += job[i]->cps;
        job[i]->token = min(job[i]->token, BUFSIZ);
        pthread_cond_broadcast(&job[i]->cond);
        pthread_mutex_unlock(&(job[i]->mut));
      }
    }
    pthread_mutex_unlock(&mut_job);
    sleep(1);
  }
}

static void modle_load() {
  // alarm_handler_save = signal(SIGALRM, alarm_handler);
  // alarm(1);
  int err = pthread_create(&tid_alarm, NULL, thr_alarm, NULL);
  if (err) {
    fprintf(stderr, "pthread_create():%s\n", strerror(err));
    exit(1);
  }
  atexit(modle_unload);
}

// 初始化令牌
mytbf_st* mytbf_init(int cps, int burst) {
  pthread_once(&init_once, modle_load);
  struct mytbf_st* me;
  me = malloc(sizeof(*me));
  if (me == NULL) {
    return NULL;
  }
  me->burst = burst;
  me->cps = cps;
  me->token = 0;
  pthread_mutex_init(&me->mut, NULL);
  pthread_cond_init(&me->cond,NULL);

  pthread_mutex_lock(&mut_job);
  int pos = get_free_pos_unlocked();
  if (pos < 0) {
    pthread_mutex_unlock(&mut_job);
    free(me);
    return NULL;
  }
  me->pos = pos;
  job[pos] = me;
  pthread_mutex_unlock(&mut_job);
  return me;
}

// 获取令牌
int mytbf_fetchtoken(mytbf_st* tbfPrt, int num) {
  struct mytbf_st* me = tbfPrt;
  if (num <= 0) {
    return -EINVAL;
  }

  pthread_mutex_lock(&me->mut);
  while (me->token <= 0) {
    pthread_cond_wait(&me->cond,&me->mut);
    // pthread_mutex_unlock(&(me->mut));
    // sched_yield();
    // pthread_mutex_lock(&(me->mut));
  }
  int n = min(me->token, num);
  me->token -= n;
  pthread_mutex_unlock(&(me->mut));

  return n;
}

// 归还令牌
int mytbf_returntoken(mytbf_st* tbfPrt, int num) {
  struct mytbf_st* me = tbfPrt;
  if (num < 0) {
    return -1;
  }

  pthread_mutex_lock(&me->mut);
  me->token = min(me->token + num, BUFSIZ);
  pthread_cond_broadcast(&me->cond);
  pthread_mutex_unlock(&me->mut);

  return num;
}

// 销毁
int mytbf_destory(mytbf_st* tpfPtr) {
  struct mytbf_st* me = tpfPtr;

  pthread_mutex_lock(&mut_job);
  job[me->pos] = NULL;
  pthread_mutex_unlock(&mut_job);

  pthread_cond_destroy(&me->cond);
  pthread_mutex_destroy(&me->mut);
  free(me);
  return 0;
}