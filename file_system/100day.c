/*
 * 计算100天后的时间
 * zhanghexie
 * 2020-12-23
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define FILE_NAME "/tmp/out"
#define TIME_STR_SIZE 1024

int main(int argc, char* argv[]) {
  time_t stamp;
  time(&stamp);
  
  struct tm *tm;
  tm = localtime(&stamp);
  
  char timeStr[TIME_STR_SIZE];
  strftime(timeStr, TIME_STR_SIZE, "NOW: %Y-%m-%d",tm);
  puts(timeStr);

  tm->tm_mday += 100;
  mktime(tm);
  strftime(timeStr, TIME_STR_SIZE, "After 100 days: %Y-%m-%d",tm);
  puts(timeStr);
}