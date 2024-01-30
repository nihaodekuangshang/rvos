#include "batch.h"
#include <stdio.h>
void sys_exit(int32_t exc)
{
	printf("[kernel] Application exited with code %d\n", exc);
	run_next_app();
}
