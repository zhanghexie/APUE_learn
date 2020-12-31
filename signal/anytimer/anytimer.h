#ifndef ANYTIMER_H__
#define ANYTIMER_H__

typedef void at_jobfun_t(void*);

// 添加任务
int at_addjob(int, at_jobfun_t*, void*);

// 结束资源
void at_wait();

#endif