#include "task.h"
#include <stdio.h>
void sys_exit(int32_t exc)
{
	printf("[kernel] Application exited with code %d\n", exc);
	exit_task(&task_man);
	panic("Unreachable in sys_exit!");
}
int64_t sys_yield()
{

 	suspend_task(&task_man);
	return 0;
}
