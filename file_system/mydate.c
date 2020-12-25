/*
 * 解析参数
 * zhanghexie
 * 2020-12-23
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define FILE_NAME "/tmp/out"
#define TIME_STR_SIZE 1024
#define FMTSTRSIZE 1024

/*
 * -y : year
 * -m : month
 * -d : day
 * -H : hour
 * -M : minute
 * -S : second
 */

int main(int argc, char* argv[]) {
  time_t stamp;
  time(&stamp);

  struct tm* tm;
  tm = localtime(&stamp);

  int c = 0;
  char fmtstr[FMTSTRSIZE];

  FILE* fp = stdout;
  while (1) {
    c = getopt(argc, argv, "-H:MSy:md");
    // 加上‘-’时，非选参数返回1。
    // 加上‘:’表示接受参数，参数被设置为optarg。
    if (c < 0) {
      break;
    }
    switch (c) {
      case 1:
        if(fp != stdout) {
          break;
        }
        fp = fopen(argv[optind - 1], "w");
        if (NULL == fp) {
          perror("fopen()");
          fp = stdout;
        }
        break;
      case 'H':
        if (0 == strcmp(optarg, "12")) {
          strncat(fmtstr, "%I(%P) ", FMTSTRSIZE - 1);
        } else if ((0 == strcmp(optarg, "24"))) {
          strncat(fmtstr, "%H ", FMTSTRSIZE - 1);
        } else {
          fprintf(stderr, "-H 12/24\n");
        }
        break;
      case 'M':
        strncat(fmtstr, "%M", FMTSTRSIZE - 1);
        break;
      case 'S':
        strncat(fmtstr, "%S ", FMTSTRSIZE - 1);
        break;
      case 'y':
        if (0 == strcmp(optarg, "2")) {
          strncat(fmtstr, "%y ", FMTSTRSIZE - 1);
        } else if ((0 == strcmp(optarg, "4"))) {
          strncat(fmtstr, "%Y ", FMTSTRSIZE - 1);
        } else {
          fprintf(stderr, "-y 2/4\n");
        }
        break;
      case 'm':
        strncat(fmtstr, "%m ", FMTSTRSIZE - 1);
        break;
      case 'd':
        strncat(fmtstr, "%d ", FMTSTRSIZE - 1);
        break;
      default:
        break;
    }
  }
  char timeStr[TIME_STR_SIZE];
  strftime(timeStr, TIME_STR_SIZE, fmtstr, tm);
  strncat(timeStr, "\n", TIME_STR_SIZE - 1);
  fputs(timeStr, fp);

  if (fp != stdout) {
    fclose(fp);
  }
  exit(0);
}