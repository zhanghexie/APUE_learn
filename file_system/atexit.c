/*
 * 使用atexit函数
 * zhanghexie
 * 2020-12-23
 */

#include <stdio.h>
#include <stdlib.h>

static void f1(void) {
  puts("f1()");
}

static void f2(void) {
  puts("f2()");
}

static void f3(void) {
  puts("f3()");
}




int main(int argc, char* argv[]) {
  puts("begin");
  atexit(f1);
  atexit(f2);
  atexit(f3);
  puts("end");
  exit(0);
}