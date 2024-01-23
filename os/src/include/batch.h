#ifndef __BATCH_RVOS_H
#define __BATCH_RVOS_H
#include "keldef.h"
#define USER_STACK_SIZE  4096 * 2
#define KERNEL_STACK_SIZE  4096 * 2
#define MAX_APP_NUM  16
#define APP_BASE_ADDRESS  0x80400000
#define APP_SIZE_LIMIT  0x20000
__attribute__((aligned(4096))) struct app_manage{
	uint64_t num;
	uint64_t cur;
	uint64_t ads[MAX_APP_NUM+1];
};
__attribute__((aligned(4096))) struct kel_stack{
	uint8_t data[KERNEL_STACK_SIZE];
};
struct usr_stack{
	uint8_t data[USER_STACK_SIZE];
};
extern struct app_manage app_manager;
extern struct kel_stack kernel_stack;
extern struct usr_stack user_stack;
void init_batch();
void load_app(uint64_t id);
void  run_next_app();
#endif
