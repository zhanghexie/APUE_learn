/*
 * 函数跳转
 * zhanghexie
 * 2020-12-24
 */

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

static jmp_buf j;

static void c() {
  printf("%s : c() jump to a\n", __FUNCTION__);
  // 如果第二个参数设为0，会自动改成1。
  longjmp(j, 6);
  printf("%s : c() end\n", __FUNCTION__);
}

static void b() {
  printf("%s : b() begin\n", __FUNCTION__);
  printf("%s : b() call c()\n", __FUNCTION__);
  c();
  printf("%s : c() retruned\n", __FUNCTION__);
  printf("%s : b() end\n", __FUNCTION__);
}

static void a() {
  int ret;
  printf("%s : a() begin\n", __FUNCTION__);
  // 如果是设置返回0,如果过是从longjmp跳回来，返回设置的值。
  ret = setjmp(j);
  if (0 == ret) {
    printf("%s : a() call b()\n", __FUNCTION__);
    b();
    printf("%s : b() retruned\n", __FUNCTION__);
  } else {
    printf("%s : jumped back here with code %d\n", __FUNCTION__, ret);
  }
  printf("%s : a() end\n", __FUNCTION__);
}

int main() {
  printf("%s : main() begin\n", __FUNCTION__);
  printf("%s : main() call a()\n", __FUNCTION__);
  a();
  printf("%s : a() retruned\n", __FUNCTION__);
  printf("%s : main() end\n", __FUNCTION__);
}