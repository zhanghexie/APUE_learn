/*
 * 加入互斥量
 * zhanghexie
 * 2021-1-1
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define THRUNM 20
#define FILENAME "/tmp/out"
#define BUFFSIZE 1024

static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void* func(void* arg) {
  FILE* fp;
  char buf[BUFFSIZE];
  fp = fopen(FILENAME, "r+");
  if (NULL == fp) {
    perror("fopen()");
    exit(1);
  }
  pthread_mutex_lock(&mut);
  fgets(buf, BUFFSIZE, fp);
  int i = atoi(buf) + 1;
  rewind(fp);
  fprintf(fp, "%d\n", i);
  fclose(fp);
  pthread_mutex_unlock(&mut);
  pthread_exit(NULL);
}

int main() {
  pthread_t tid[THRUNM];
  for (int i = 0; i < THRUNM; ++i) {
    int err = pthread_create(&tid[i], NULL, func, NULL);
    if (0 != err) {
      fprintf(stderr, "pthread_create fail : %s", strerror(err));
      exit(0);
    }
  }

  for (int i = 0; i < THRUNM; ++i) {
    pthread_join(tid[i], NULL);
  }

  pthread_mutex_destroy(&mut);
  exit(0);
}