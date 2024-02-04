#ifndef __SWITCH_RVOS_H
#define __SWITCH_RVOS_H
#include "taskContext.h"
void __switch(struct task_context* cur,struct task_context* next);
#endif
