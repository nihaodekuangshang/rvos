#include <kernel/syscall.h>
int64_t exit(int32_t exit_code) 
{
    return sys_exit(exit_code);
}
int64_t yield()
{
	return sys_yield();
}
