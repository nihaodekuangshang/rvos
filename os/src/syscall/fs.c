
#include "syscall.h"
#include <stdio.h>
#include "sbi.h"
int64_t sys_write(uint64_t fd, uint8_t* buf,uint64_t len)
{
	switch(fd){
		case FD_STDOUT : 
			printf("%s",buf);
			return len;
			break;
		default : 
			printf("unsupported fd\n");
			return -1;
	}
	return len;
}
