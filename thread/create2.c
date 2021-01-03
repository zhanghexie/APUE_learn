/*
 * 查看创建线程上限
 * zhanghexie
 * 2020-1-2
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void* f(void* args) {
  int i;
  printf("[%d] : %lld\n",(int)args,(long long)&i);
  while(1);
  pthread_exit(NULL);
}

int main(){
  int i = 0;
  pthread_t tid;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setstacksize(&attr,1024*1024);

  for(i=0; ;++i){
    int err = pthread_create(&tid,&attr,f,(void*)i);
    if(err){
      break;
    }
  }
  printf("%d\n",i);
} 