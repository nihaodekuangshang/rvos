#include "syscall.h"
#include <stdio.h>

int64_t syscall(uint64_t id, uint64_t args[3])
{
	int64_t ret = 0 ;
	switch (id){
		case SYS_WRITE : 
			ret = sys_write(args[0],(uint8_t*)args[1],args[2]);
			break;
		case SYS_EXIT : 
			sys_exit((int32_t)args[0]);
			break;
		case SYS_YIED :
			sys_yield();
			break;
		default :
			printf("unsupport system call id: %lu\n",id);
	}
	return ret;
}
