#ifndef __LOADER_RVOS_H
#define __LOADER_RVOS_H
#include <stddef.h>
#define APP_BASE_ADDRESS 0x80400000

#define APP_SIZE_LIMIT 0x20000

#define KERNEL_STACK_SIZE (4096 * 2)

#define MAX_APP_NUM 0x10

#define USER_STACK_SIZE (4096 * 2)
struct kernel_stack{
	uint8_t data[KERNEL_STACK_SIZE];
};
struct user_stack{
	uint8_t data[USER_STACK_SIZE];
};
uint64_t get_usr_sp(struct user_stack *uss);
uint64_t get_kel_sp(struct kernel_stack *kes);
//内核使用的 栈
extern struct kernel_stack k_stack[MAX_APP_NUM];

//用户使用的 栈
extern struct user_stack  u_stack[MAX_APP_NUM];
//暂存trap上下文
extern struct trap_context  t_context;
usize get_base_i(usize);
usize  get_num_app();
void init_loader();
void load_apps();
uint64_t init_app_ct(uint64_t id);
#endif
