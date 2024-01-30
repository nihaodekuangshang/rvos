#ifndef __SYSCALL_RVOS_H
#define __SYSCALL_RVOS_H
#define  SYS_WRITE  64
#define  SYS_EXIT  93
#include <stddef.h>
#define FD_STDOUT 1
int64_t syscall(uint64_t id, uint64_t args[3]);
int64_t sys_write(uint64_t fd, uint8_t* buf,uint64_t len);
void sys_exit(int32_t exc);
#endif
