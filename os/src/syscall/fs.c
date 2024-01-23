
#include "fs.h"
#include "io.h"
#include "sbi.h"
int64_t sys_write(uint64_t fd, uint8_t* buf,uint64_t len)
{
	switch(fd){
		case FD_STDOUT : 
			print("%s",buf);
			return len;
			break;
		default : 
			print("unsupported fd");
			shutdown_err();
	}
	return len;
}
