#ifndef __TIMER__RVOS__h
#define __TIMER__RVOS__h 1
#define CLOCK_FRE 10000000
#define TRIG_PRE_SEC 100
#define  MICRO_PER_SEC  1000000
void init_time();
uint64_t get_timer();
uint64_t get_time_us();
void set_next_trigger();
#endif
