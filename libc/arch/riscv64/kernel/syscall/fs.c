
#include "include/syscall.h"
#include <stdio.h>
int64_t write(uint64_t fd, uint8_t *buf) 
{
    return sys_write(fd, buf);
}
