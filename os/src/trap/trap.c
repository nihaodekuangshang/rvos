#include "context.h"
#include <stdio.h>
#include <stddef.h>
#include "task.h"
#include "riscv.h"
#include "trap.h"
#include "sbi.h"
#include "syscall.h"
#include "timer.h"
void __alltraps();
void init_trap()
{
	uint64_t x =\
		    ((uint64_t)__alltraps ) & (~(uint64_t)(3));
	w_stvec(x);

}
struct trap_context* trap_handler(struct trap_context *tc)
{
	uint64_t sc = r_scause();
	uint64_t sv = r_stval();
	if (SCAUSE_TYPE(sc)){
		uint64_t code = (uint64_t)SCAUSE_CODE(sc);
		switch(code){
			case SCI_SUP_TIME:
				set_next_trigger();
				suspend_task(&task_man);
				break;
			default:

				printf(\
				"Unsupported intr %lx, stval =%lx !\n",\
			 	code, sv);
		}
	}else{
		switch ((uint64_t)SCAUSE_CODE(sc)){
			case (uint64_t)SCE_USR_ECALL: 
				tc->sepc += 4;
				tc->x[10] = syscall(\
						tc->x[17],\
						tc->x+10);
				break;
			case (uint64_t)SCE_SR_ACC_FAU:
			case (uint64_t)SCE_SR_PAG_FAU: 
				printf("[kernel] PageFault in application, kernel killed it.\n");
				exit_task(&task_man);
				break;
			case (uint64_t)SCE_ILL_INS: 
				printf("[kernel] IllegalInstruction in application, kernel killed it.\n");
				exit_task(&task_man);

				break;
			default:printf(\
				"Unsupported trap %lu, stval =%lx !\n",\
				(uint64_t)SCAUSE_CODE(sc) , sv);
				shutdown();
		}
	}
	return tc;
}
