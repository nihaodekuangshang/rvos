#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <sys/cdefs.h>
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif

__attribute__((__noreturn__))
void abort(void);

__attribute__((__noreturn__))
void  exit(int32_t exit_code);
int64_t yield();
int64_t write(uint64_t fd, uint8_t *buf);
#ifdef __cplusplus
}
#endif

#endif
