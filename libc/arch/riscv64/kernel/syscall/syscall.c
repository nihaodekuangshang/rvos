#include "include/syscall.h"

int64_t syscall(uint64_t id, uint64_t args[3])
{
	int64_t ret;
	register unsigned long a0 __asm__("a0") = args[0];
	register unsigned long a1 __asm__("a1") = args[1];
	register unsigned long a2 __asm__("a2") = args[2];
	register unsigned long a7 __asm__("a7") = id;
	__asm__ __volatile__(
		"ecall"
		:"+r"(a0)
		:"r"(a1),"r"(a2),"r"(a7)
		:"cc"
        );
	ret = args[0];
	return ret;
}

int64_t sys_write(uint64_t fd, uint8_t* buffer)
{
	uint64_t len = 0;
	for (int i = 0;buffer[i] != '\0';i++) {
		len = i;
	 }
	uint64_t tmp[3] = {fd,buffer,len + 1};
	syscall(SYS_WRITE, tmp);
}

int64_t sys_exit(int32_t exit_code)
{
	uint64_t tmp[3] = {exit_code,0,0};
	return syscall(SYS_EXIT, tmp);
}

int64_t sys_yield()
{
	uint64_t tmp[3] = {00,0,0};
	return syscall(SYS_YIED, tmp);
}

