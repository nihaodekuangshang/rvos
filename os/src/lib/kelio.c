#include "sbi.h"
#include <stddef.h>
#include <stdbool.h>

bool  _print_c(char c) 
{
	enum DebugConsoleFID fid = DebugConsoleWriteByte;
	struct Sbiret  ret = ecall( DEBUGCONSOL, fid, c, 0, 0);
	if(ret.error == SBISUCCESS){
		return true;
	}else{
		return false;
	}
}
long _print_str(const char* str)
{
	unsigned long len = 0;
	for (int i = 0;str[i] != '\0';i++) {
		len = i;
	}
	unsigned long addr = (unsigned long)str | (0<<64);
	enum DebugConsoleFID fid = DebugConsoleWrite;
	struct Sbiret ret = ecall( DEBUGCONSOL, fid,len+1, addr, 0);
	return ret.value;
}
