#include <stdio.h>
#include <string.h>
#include "context.h"
#include "loader.h"
#include "trap.h"
void  _num_app();
usize get_base_i(usize);
usize  get_num_app();
struct kernel_stack k_stack[MAX_APP_NUM];
struct user_stack  u_stack[MAX_APP_NUM];
struct trap_context  t_context;
void init_loader()
{
	for(int i=0;i<MAX_APP_NUM;++i){
		memset(k_stack[i].data,0,KERNEL_STACK_SIZE);
		memset(u_stack[i].data,0,USER_STACK_SIZE);
	}
	t_context.sepc = 0;
	t_context.sstatus = 0;
	memset(t_context.x,0,32);
}
void load_apps()
{
	uint64_t* ptr = (uint64_t*)_num_app;
	uint64_t num = get_num_app();
	uint64_t ads[MAX_APP_NUM+1] ;
	//num+1个地址，最后是结束地址
	for(int32_t i = 1; i <= num + 1; i++){
		ads[i-1] = *((uint64_t*)ptr + i);
	}
	__asm__ volatile ("fence.i");
    // load apps

	for(int32_t i = 0; i < num;++i){
		usize  base_i = get_base_i(i);
		for(uint64_t j = base_i; j < base_i + APP_SIZE_LIMIT; ++j){
			*(uint8_t*)j = 0;
		}

		uint8_t* sptr = (uint8_t*)ads[i];
		uint8_t* dptr = (uint8_t*)base_i;
		for(uint64_t j=0; j< ads[i+1]-ads[i];j++){
		*(dptr + j) = *(sptr + j);
		}
	}
}
usize get_base_i( usize app_id)
{
    return APP_BASE_ADDRESS + app_id * APP_SIZE_LIMIT;
}
usize  get_num_app()
{
	uint64_t* p = _num_app;
    return *p;
}
uint64_t   push_context(struct kernel_stack *ks,struct trap_context* tc)
{
	uint64_t* sp = (uint64_t *)(get_kel_sp(ks) -sizeof *tc );
	//uint64_t x[32];
	//uint64_t sstatus;
	//uint64_t sepc;
	struct trap_context *tc_ptr = (struct trap_cont*)sp;
	tc_ptr->sstatus = tc->sstatus;
	tc_ptr->sepc = tc->sepc;
	for(int i = 0; i < 32; ++i){
		tc_ptr->x[i] = tc->x[i];
	}
	return (uint64_t)tc_ptr;
}
uint64_t get_usr_sp(struct user_stack *uss)
{
	return (uint64_t)&uss->data + USER_STACK_SIZE;
}
uint64_t get_kel_sp(struct kernel_stack *kes)
{
	return (uint64_t)&kes->data + KERNEL_STACK_SIZE;
}
uint64_t init_app_ct(uint64_t id)
{

	init_app_context(&t_context,get_base_i(id),get_usr_sp(&u_stack));
	return push_context(&k_stack[id],&t_context);
}
