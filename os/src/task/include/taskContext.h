#ifndef __TASKCONTEXT_RVOS_H
#define __TASKCONTEXT_RVOS_H 1
#include "stddef.h"
struct task_context{
	uint64_t ra;
	uint64_t sp;
	uint64_t s[12];
};
void  zero_init(struct task_context *con) ;
void  goto_restore(struct task_context *con,uint64_t ksp);
#endif
