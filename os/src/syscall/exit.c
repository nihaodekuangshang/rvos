#include "batch.h"
#include "io.h"
void sys_exit(int32_t exc)
{
	print("[kernel] Application exited with code %d", exc);
	run_next_app();
}
