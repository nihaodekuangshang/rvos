#include "context.h"
#include "batch.h"
#include <stdio.h>
#include <stddef.h>
#include "riscv.h"
#include "trap.h"
#include "sbi.h"
#include "syscall.h"
void __alltraps();
void init_trap()
{
	uint64_t x =\
		    ((uint64_t)__alltraps ) & (~(uint64_t)(3));
	w_stvec(x);

}
struct trap_cont* trap_handler(struct trap_cont *tc)
{
	uint64_t sc = r_scause();
	uint64_t sv = r_stval();
	switch ((uint64_t)SCAUSE_ECO(sc)){
		case (uint64_t)SCE_USR_ECALL: 
			tc->sepc += 4;
			tc->x[10] = syscall(\
					tc->x[17],\
					tc->x+10);
			break;
		case (uint64_t)SCE_SR_ACC_FAU:
		case (uint64_t)SCE_SR_PAG_FAU: 
			printf("[kernel] PageFault in application, kernel killed it.\n");
			run_next_app();
			break;
		case (uint64_t)SCE_ILL_INS: 
			printf("[kernel] IllegalInstruction in application, kernel killed it.\n");
			run_next_app();

			break;
		default:printf(\
			"Unsupported trap %lu, stval =%lx !\n",\
			(uint64_t)SCAUSE_ECO(sc) , sv);
			shutdown();
	}
	return tc;
}
