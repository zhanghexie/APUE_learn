#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int count = 0;
  FILE *fp = NULL;
  while(1) {
    fp = fopen("tmp","r");
    if (NULL == fp) {
      perror("fopen()");
      break;
    }
    ++count;
  }

  puts("退出!");
  printf("cout: %d\n",count);
  exit(0);
}