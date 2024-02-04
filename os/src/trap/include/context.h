#ifndef __CONTEXT__RVOS_H
#define __CONTEXT__RVOS_H
#include <stddef.h>
struct trap_context{
	uint64_t x[32];
	uint64_t sstatus;
	uint64_t sepc;
};
void init_app_context(struct trap_context* tc,uint64_t entry,uint64_t sp);
#endif
