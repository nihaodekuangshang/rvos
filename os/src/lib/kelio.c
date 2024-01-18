#include "sbi.h"
void _print_c(char c) 
{
	enum DebugConsoleFID fid = DebugConsoleWriteByte;
	ecall( DEBUGCONSOL, fid, c, 0, 0);
}
void _print_str(char* str)
{
	unsigned long len = 0;
	for (int i = 0;str[i] != '\0';i++) {
		len = i;
	}
	unsigned long addr = (unsigned long)str | (0<<64);
	enum DebugConsoleFID fid = DebugConsoleWrite;
	ecall( DEBUGCONSOL, fid,len+1, addr, 0);
}
