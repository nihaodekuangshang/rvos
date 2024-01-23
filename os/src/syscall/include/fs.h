#ifndef __FS_RVOS_H
#define __FS_RVOS_H

#define FD_STDOUT 1
#include "keldef.h"
int64_t sys_write(uint64_t fd, uint8_t* buf,uint64_t len);
#endif
