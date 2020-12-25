#include <stdio.h>
#include <stdlib.h>

int main() {
  char s[] = "1234567";
  printf("1234567 = %d\n", atoi(s));

  char s1[] = "123a4567";
  printf("123a4567 = %d\n", atoi(s1));

  int y = 2020, m = 12, d = 13;
  char buf[1024];
  sprintf(buf,"%d-%d-%d",y,m,d);
  puts(buf);

}
