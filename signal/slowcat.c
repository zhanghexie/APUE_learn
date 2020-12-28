/*
 * 流量控制cat文件
 * zhanghexie
 * 2020-12-27
 */

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

static volatile int loop = 0;
static void alarm_hanler(int s) {
  alarm(1);
  loop = 1;
}

int main(int argc, char* argv[]) {
  signal(SIGALRM, alarm_hanler);
  alarm(1);

  FILE* fps;
  int ch;

  if (argc < 2) {
    fprintf(stderr, "Usage:%s <src_file>\n", argv[0]);
    exit(1);
  }

  fps = fopen(argv[1], "r");
  if (NULL == fps) {
    perror("fopen(fps)");
    exit(1);
  }

  while (1) {
    while (!loop) {
      pause();
    };
    loop = 0;
    ch = fgetc(fps);
    if (EOF == ch) break;
    fputc(ch, stdout);
    fflush(NULL);
  }

  fclose(fps);
  exit(0);
}
