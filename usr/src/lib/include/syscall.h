#ifndef __SYSCALL_RVOS_H
#define __SYSCALL_RVOS_H
#define  SYSCALL_WRITE  64
#define  SYSCALL_EXIT  93
#include <keldef.h>
int64_t syscall(uint64_t id, uint64_t args[3]);
int64_t sys_write(uint64_t fd, uint8_t* buffer);
int64_t sys_exit(int32_t exit_code);
int64_t write(uint64_t fd, uint8_t *buf);
int64_t exit(int32_t exit_code);
#endif
