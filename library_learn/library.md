# 动态链接库
## 动态链接库和静态库
- 静态库
    - 私家车
    - 编译时载入，不占用运行时间
- 动态库（共享库）
    - 公交车
    - 执行时去动态库调用

## 静态库
- 名称
```
libxx.a
```
- 命令
```
ar -cr libxx.a yyy.o
```
- 发布到
```
/usr/local/include
/usr/local/lib
```
- 使用
```
gcc -L/usr/local/lib -o main mian.o -lxx
```

> ldd 程序名： 可以查看程序关联到的动态库
```
// 输入：
ldd mytool

//输出：                                                                               linux-vdso.so.1 (0x00007ffefddf9000)
        libc.so.6 => /usr/lib/libc.so.6 (0x00007fd853982000)
        /lib64/ld-linux-x86-64.so.2 => /usr/lib64/ld-linux-x86-64.so.2 (0x00007fd853b82000)
```
## 动态库
- 名称
```
libxx.so
```
- 生成命令
```
gcc -shared -fpic -o libxx.so yyy.c
```

- 发布
```
// 
/usr/local/include

/usr/local/lib
```
> include存放.h;lib存放库文件