#ifndef __SYSCALL_RVOS_H
#define __SYSCALL_RVOS_H
#define  SYS_WRITE  64
#define  SYS_EXIT  93
#define  SYS_YIED   124
#define SYS_GET_TIME 169
#include <stddef.h>
#include <stdbool.h>
#define FD_STDOUT 1
int64_t syscall(uint64_t id, uint64_t args[3]);
int64_t sys_write(uint64_t fd, uint8_t* buffer);
int64_t sys_exit(int32_t exit_code);
int64_t sys_yield();
bool sys_get_time();
#endif
