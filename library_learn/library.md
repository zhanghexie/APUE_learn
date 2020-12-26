# 链接库
## 动态链接库和静态库
- 静态库
    - 私家车
    - 编译时载入，不占用运行时间
- 动态库（共享库）
    - 公交车
    - 执行时去动态库调用
- 动态库和静态库重名时优先链接动态库。

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
// 头文件发布到
/usr/local/include

// 库文件发布到
/usr/local/lib
```
- 使用
```
gcc -L/usr/local/lib -o main mian.o -lxx
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
// 头文件发布到
/usr/local/include

// 库文件发布到
/usr/local/lib
```
> include存放.h;
lib存放库文件

- 添加路径
```
// 修改文件
/etc/ld.so.conf

//加上一句
/usr/local/lib

// 重读配置文件
/sbin/ldconfig 
```

- 使用:
```
gcc -I/usr/local/inclde -L/usr/local/lib -o ... -lxx
```
> 如果是标准位置-I 和 -L都可以省略。

> ldd 程序名： 可以查看程序关联到的动态库
```
// 输入：
ldd mytool

//输出：                                                                               linux-vdso.so.1 (0x00007ffefddf9000)
        libc.so.6 => /usr/lib/libc.so.6 (0x00007fd853982000)
        /lib64/ld-linux-x86-64.so.2 => /usr/lib64/ld-linux-x86-64.so.2 (0x00007fd853b82000)
```

- 非root用户发布
```
cp xx.so ~/lib
export LD_LIBRARY_OATH=~/lib
```