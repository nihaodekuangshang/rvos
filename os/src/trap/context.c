#include "context.h"
#include "riscv.h"
void set_cont_sp(struct trap_cont* tc,uint64_t sp)
{
	tc->x[2] = sp;
}
void init_app_context(struct trap_cont* tc,uint64_t entry,uint64_t sp)
{
	uint64_t ss = r_sstatus();
	ss = ss & ~SSTATUS_SPP_S;
	for(int i = 0;i < 32; ++i){
		tc->x[i] = 0;
	}
	tc->sstatus = ss;
	tc->sepc = entry;
	set_cont_sp(tc,sp);
}
