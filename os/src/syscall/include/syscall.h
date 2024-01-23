#ifndef __SYSCALL_RVOS_H
#define __SYSCALL_RVOS_H
#define  SYS_WRITE  64
#define  SYS_EXIT  93
#include "keldef.h"
int64_t syscall(uint64_t id, uint64_t args[3]);
#endif
