#ifndef RELAYER_H__
#define RELAYER_H__
#include <stdint.h>
#define REL_JOBMAX 1024

enum { STATE_RUNNING = 1, STATE_CANCELED, STATE_OVER };

struct rel_stat_t {
  int state;
  int fd1;
  int fd2;
  int64_t counter12, counter21;
};

int rel_addjob(int fd1, int fd2);
/*
 * return >= 0          成功，返回当前任务ID
 *        == -EINVAL    失败，参数非法
 *        == -ENOSPC    失败，任务数组满
 *        == -ENOMEM    失败，内存分配有误
 */

int rel_canceljob(int id);
/*
 * return == 0          成功
 *        == -EINVAL    失败，参数非法
 *        == -EBUSY     失败，任务重复取消
 */

int rel_waitjob(int id, struct rel_stat_t*);
/*
 * return == 0          成功
 *        == -EINVAL    失败，参数非法
 */

int rel_statjob(int id, struct rel_stat_t*);
/*
 * return == 0          成功
 *        == -EINVAL    失败，参数非法
 */

#endif