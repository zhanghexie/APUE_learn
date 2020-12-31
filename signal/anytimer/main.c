#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "anytimer.h"
void job(void* string) {
  char* s = string;
  printf(s);
}

int main() {
  printf("before\n");
  int job1 = at_addjob(3, job, "hello 3\n");
  int job2 = at_addjob(5, job, "hello 5\n");
  int job3 = at_addjob(7, job, "hello 7\n");
  int job4 = at_addjob(10, job, "hello 10\n");
  at_wait();
  printf("end\n");
  exit(0);
}