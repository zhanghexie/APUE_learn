/*
 * 学习gcc
 * zhanghexie
 * 2020-12-16
 */

#include <stdio.h>
#include <stdlib.h>

// 预处理-编译-汇编-链接
// preprocessing, compilation, assembly and linking
// -E, -S, -c

// 1.预处理：gcc -E gcc.c -o gcc.i
//   导入头文件，宏替换（.c => .i）
// 2.编译：gcc -S gcc.i
//   生成汇编文件（.i => .s）
// 3.汇编：gcc -c gcc.s
//   汇编汇编语言代码生成二进制文件（.s => .o）
// 4.链接: gcc hello.o -o hello
//   链接程序生成可执行文件

// 一步到位：
// gcc gcc.c -o hello

int main(int argc, char* argv[]) {
  printf("hello world!!! \n");
  return 0;
}
