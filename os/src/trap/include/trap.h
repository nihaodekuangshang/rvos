#ifndef __TRAP_RVOS_H
#define __TRAP_RVOS_H
#define DIRECT (0)
#define VECTORED (1)
void init_trap();
struct trap_context* trap_handler(struct trap_context *tc);
#endif
