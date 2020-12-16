/*
 * 研究fllush函数 
 * zhanghexie
 * 2020-12-13
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
//   printf("before while:");
//   while(1);
//   printf("after while:");
  
  printf("before while:");
  fflush(stdout);
  while(1);
  printf("after while:");
}
