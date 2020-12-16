# make学习
## gcc基础

- 编译器生成程序的几个步骤
	
	1. 预处理
	2. 编译
	3. 汇编
	4. 链接
1. 预处理
	- 头文件导入、宏替换
	- **.c** -> **.i**
	- 命令：
	```
	gcc -E main.c -o main.i
	```
2. 编译
	- 生成汇编代码
	- **.i** -> **.s**
	- 命令：
	```
	gcc -S main.i
	```
3. 汇编
	- 生成可执行文件
	- **.s** -> **.o** 
	- 命令：
	```
	gcc -c main.i -o main.o
	```
4. 链接
	- 生成目标文件
	- 链接各个可执行文件生成最终执行文件
	- 命令
	```
	gcc main.o tool1.o tool2.o -o main
	```
## make基础

- 大功能依赖不同的小功能，小功能又依赖不同的c文件，其中还有交叉，这样管理起来就会非常麻烦。
- make会自动为我们分析依赖工具。
- makefile和MAKEFILE同时存在引用makefile，这样用户如果自己改就会优先调用用户写的。

## make实践

- 创建几个文件

```
touch main.c tool1.c tool2.c main.h tool1.h tool2.h
```
- tool1.h如下所示：
```
#ifndef TOOL1_H_
#define TOOL1_H_
void mytool1(void);
#endif
```
- tool1.c如下：

```
#include <stdio.h>
#include "tool1.h"

void mytool1() {
    printf("tool1 print\n");
}
```
> tool2类似不在写出。

- main.c
```
#include "tool1.h"
#include "tool2.h"

int main() {
  mytool1();
  mytool2();

  return 0;
}
```

- 分析依赖关系如下：
``` 
a.out -> main.o tool1.o tool2.o
tool1.o -> tool1.c
tool2.o -> tool2.c
```
- 书写makefile
```
mytool: main.o tool1.o tool2.o
	gcc main.o tool1.o tool2.o -o mytool

main.o: main.c
	gcc main.c -c -Wall -g -o main.o

tool1.o: tool1.c
	gcc tool1.c -c -Wall -g -o tool1.o

tool2.o: tool2.c
	gcc tool2.c -c -Wall -g -o tool2.o

clean:
	rm *.o mytool -r
```

- 改进:进行变量替换
```
OBJS=main.o tool1.o tool2.o
CC=gcc #默认就是gcc
CFLAGS+=-c -Wall -g

mytool:$(OBJS) 
	$(CC) $(OBJS) -o mytool

main.o: main.c
	$(CC) main.c $(CFLAGS) -o main.o

tool1.o: tool1.c
	$(CC) tool1.c $(CFLAGS) -o tool1.o

tool2.o: tool2.c
	$(CC) tool2.c $(CFLAGS) -o tool2.o

clean:
	$(RM) *.o mytool -r
	# RM是rm -f
``` 
- 进一步改进
	- $^ 代表依赖文件
	- ￥@ 代表目标文件
	- %代表是通配符
```
OBJS=main.o tool1.o tool2.o
CC=gcc #默认就是gcc
CFLAGS+=-c -Wall -g

mytool:$(OBJS) 
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	$(RM) *.o mytool -r
```