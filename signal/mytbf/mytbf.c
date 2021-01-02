
#include "mytbf.h"

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct mytbf_st {
  int cps;
  int burst;
  int token;
  int pos;
};
static struct mytbf_st* job[MYBTF_MAX];
static int inited = 0;  //记录模块是否初始化
typedef void (*sighandler_t)(int);
static sighandler_t alarm_handler_save;

static int min(int a, int b) { return a > b ? b : a; }

static int get_free_pos() {
  for (int i = 0; i < MYBTF_MAX; ++i) {
    if (!job[i]) {
      return i;
    }
  }
  return -1;
}

static void modle_unload() {
  signal(SIGALRM, alarm_handler_save);
  alarm(0);
  for (int i = 0; i < MYBTF_MAX; ++i) {
    free(job[i]);
  }
  fflush(NULL);
}

static void alarm_handler() {
  alarm(1);
  for (int i = 0; i < MYBTF_MAX; ++i) {
    if (job[i] != NULL) {
      job[i]->token += job[i]->cps;
      job[i]->token = min(job[i]->token, BUFSIZ);
    }
  }
}

static void modle_load() {
  alarm_handler_save = signal(SIGALRM, alarm_handler);
  alarm(1);
  atexit(modle_unload);
}

// 初始化令牌
mytbf_st* mytbf_init(int cps, int burst) {
  if (!inited) {
    modle_load();
    inited = 1;
  }
  int pos = get_free_pos();
  if (pos < 0) {
    return NULL;
  }
  struct mytbf_st* me;
  me = malloc(sizeof(*me));
  if (me == NULL) {
    return NULL;
  }
  me->burst = burst;
  me->cps = cps;
  me->token = 0;
  me->pos = pos;
  job[pos] = me;
  return me;
}

// 获取令牌
int mytbf_fetchtoken(mytbf_st* tbfPrt, int num) {
  struct mytbf_st* me = tbfPrt;
  if (num <= 0) {
    return -EINVAL;
  }
  while (me->token <= 0) {
    pause();
  }
  int n = min(me->token, num);
  me->token -= n;
  return n;
}

// 归还令牌
int mytbf_returntoken(mytbf_st* tbfPrt, int num) {
  struct mytbf_st* me = tbfPrt;
  if (num < 0) {
    return -1;
  }
  me->token = min(me->token + num, BUFSIZ);
  return num;
}

// 销毁
int mytbf_destory(mytbf_st* tpfPtr) {
  struct mytbf_st* me = tpfPtr;
  job[me->pos] = NULL;
  free(me);
  return 0;
}