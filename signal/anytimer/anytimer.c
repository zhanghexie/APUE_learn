#include "anytimer.h"

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_JOBS 1024

struct at_job_st {
  int time_left;
  int job_state;  // 0：正常， >0：取消，<0：暂停
  at_jobfun_t* fun;
  void* args;
};

static int inited = 0;
typedef void (*sighandler_t)(int);

static struct at_job_st* jobs[MAX_JOBS];

static sighandler_t sighandler_saved;

static void alarm_handler(int s) {
  alarm(1);
  for (int i = 0; i < MAX_JOBS; ++i) {
    if (NULL != jobs[i]) {
      {
        //工作状态
        if (0 == jobs[i]->job_state) {
          printf("%d :time-- : %d\n", i, jobs[i]->time_left);
          --jobs[i]->time_left;
          if (jobs[i]->time_left <= 0) {
            jobs[i]->time_left = 0;
            //工作状态设为暂停
            jobs[i]->job_state = -1;
            jobs[i]->fun(jobs[i]->args);
          }
        }
      }
    }
  }
}

static void model_unload() {
  alarm(0);
  signal(SIGALRM, sighandler_saved);
  for (int i = 0; i < MAX_JOBS; ++i) {
    free(jobs[i]);
    jobs[i] = NULL;
  }
}

static void model_load() {
  sighandler_saved = signal(SIGALRM, alarm_handler);
  alarm(1);
  atexit(model_unload);
}

static int get_pos() {
  for (int i = 0; i < MAX_JOBS; ++i) {
    if (NULL == jobs[i]) {
      return i;
    }
  }
  return -1;
}

int at_addjob(int sec, at_jobfun_t* fun, void* args) {
  if (!inited) {
    model_load();
    inited = 1;
  }

  struct at_job_st* job;
  job = malloc(sizeof(*job));

  int pos = get_pos();
  if (pos < 0) {
    return -ENOSPC;
  } else {
    jobs[pos] = job;
    job->job_state = 0;
    job->time_left = sec;
    job->fun = fun;
    job->args = args;
  }

  return 0;
}

// 结束资源
void at_wait() {
  int running = 1;
  while (running) {
    running = 0;
    for (int i = 0; i < MAX_JOBS; ++i) {
      if (NULL != jobs[i]) {
        if (0 == jobs[i]->job_state) {
          running = 1;
        }
      }
    }
    pause();
  }
  model_unload();
}