#include "riscv.h"
#include <stddef.h>
#include "sbi.h"
#include "timer.h"
void init_time()
{
	intr_on();
	w_sie(SIE_STIE);
}
uint64_t get_timer()
{
	return r_time();
}

uint64_t get_time_us()
{
    return get_timer() / (CLOCK_FRE / MICRO_PER_SEC);
}
void set_next_trigger()
{
	set_timer(get_timer() + CLOCK_FRE/TRIG_PRE_SEC);
}
