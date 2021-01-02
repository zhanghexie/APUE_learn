/*
 * 创建线程
 * zhanghexie
 * 2020-12-31
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void* f(void* args) {
  puts("new thread is running!!!");
  //return NULL;
  pthread_exit(NULL);
}

int main() {
  pthread_t p;
  puts("Begin!");
  int err = pthread_create(&p, NULL, f, NULL);
  if (0 != err) {
    fprintf(stderr, "pthread_create failed %s", strerror(err));
    exit(1);
  }
  pthread_join(p,NULL);
  puts("End!");

}