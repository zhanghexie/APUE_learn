#ifndef MYBTF_H__
#define MYBTF_H__

#define MYBTF_MAX 1024

// 隐藏数据结构
typedef void mytbf_st;

// 初始化一个流量控制
mytbf_st* mytbf_init(int cps, int burst);

// 获取令牌
int mytbf_fetchtoken(mytbf_st*, int);

// 归还令牌
int mytbf_returntoken(mytbf_st*, int);

// 销毁
int mytbf_destory(mytbf_st*);

#endif