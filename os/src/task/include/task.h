#ifndef __TASK_RVOS_H
#define __TASK_RVOS_H 1
#define APP_BASE_ADDRESS  0x80400000
#define APP_SIZE_LIMIT  0x20000
#define MAX_APP_NUM  0x10
#include <stddef.h>
#include "taskContext.h"
enum task_status {
    task_unInit,
    task_ready,
    task_running,
    task_exited,
};
struct task_control_block {
    enum task_status status;
    struct  task_context cont;
};

struct task_manager {
    uint64_t num;
    uint64_t cur;
    struct task_control_block  tasks[MAX_APP_NUM];
};
//任务管理器
extern struct task_manager task_man;
void init_task();
void  run_next_task(struct task_manager *tm);
void suspend_task(struct task_manager *tm); 
void exit_task(struct task_manager *tm);
void  run_first_task(struct task_manager *tm);
#endif
