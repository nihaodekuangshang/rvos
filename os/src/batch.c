#include "batch.h"
#include "io.h"
#include "sbi.h"
#include "context.h"
void _num_app();
void  __restore(uint64_t tc_addr);
uint64_t get_usr_sp(struct usr_stack *uss);
uint64_t get_kel_sp(struct kel_stack *kes);
struct app_manage app_manager;
struct usr_stack user_stack;
struct kel_stack kernel_stack;
struct trap_cont trap_context;
void init_batch()
{
	void (*ptr)() = _num_app;
	uint64_t num = *(uint64_t*)ptr;
	uint64_t ads[MAX_APP_NUM];
	for(int32_t i = 0; i < MAX_APP_NUM; i++){
		ads[i] = 0;
	}
	for(int32_t i = 1; i <= num + 1; i++){
		ads[i-1] = *((uint64_t*)ptr + i);
	}
	app_manager.num = num;
	app_manager.cur = 0;
	for(int i = 0; i <= MAX_APP_NUM; i++){
		app_manager.ads[i] = ads[i];
	}
	for(int i = 0; i < KERNEL_STACK_SIZE; ++i){
		kernel_stack.data[i] = 0;
	}
	for(int i = 0; i < USER_STACK_SIZE; ++i){
		user_stack.data[i] = 0;
	}


}

void load_app(uint64_t id)
{

	if (id >= app_manager.num) {
		print("All applications completed!");
		shutdown();
	}



	uint64_t *ptr = (uint64_t*)APP_BASE_ADDRESS;
	for(int32_t i = 0; i < APP_SIZE_LIMIT; i++){
		*ptr = 0;
		ptr++;
	}
	uint8_t *sptr = (uint8_t*)app_manager.ads[id];
	uint64_t num = app_manager.ads[id+1]-app_manager.ads[id];
	uint8_t src[num];
	for(int32_t i = 0;\
			i < num; \
			i++){
		src[i] = *sptr;
		sptr++;
	}

	uint8_t *dptr = (uint8_t*)APP_BASE_ADDRESS;
	for(int32_t i = 0; \
			i < num; \
			i++){
		*dptr = src[i];
		dptr++;
	}


    __asm__("fence.i");

}
void move_to_next_app(struct app_manage *am)
{
	am->num  += 1;
}
void drop_app_man(struct app_manage* am)
{
	am->num = 0;
	am->cur = 0;
for(int32_t i = 0; i < MAX_APP_NUM; i++){
		am->ads[i] = 0;
	}
}
uint64_t   push_context(struct kel_stack *ks,struct trap_cont* tc)
{
	uint64_t* sp = (uint64_t *)(get_kel_sp(ks) -sizeof *tc );
	//uint64_t x[32];
	//uint64_t sstatus;
	//uint64_t sepc;
	struct trap_cont *tc_ptr = (struct trap_cont*)sp;
	tc_ptr->sstatus = tc->sstatus;
	tc_ptr->sepc = tc->sepc;
	for(int i = 0; i < 32; ++i){
		tc_ptr->x[i] = tc->x[i];
	}
	return (uint64_t)tc_ptr;
}
void  run_next_app()
{

	uint64_t cur = app_manager.cur;
	
	load_app(cur);
	
	move_to_next_app(&app_manager);
	
	// before this we have to drop local variables related to resources manually
	
	// and release the resources
	
	init_app_context(&trap_context,APP_BASE_ADDRESS,\
			get_usr_sp(&user_stack));
	__restore(push_context(&kernel_stack,&trap_context));
	
	print("Unreachable in batch::run_current_app!");
	shutdown_err();

}
uint64_t get_usr_sp(struct usr_stack *uss)
{
	return (uint64_t)&uss->data + USER_STACK_SIZE;
}
uint64_t get_kel_sp(struct kel_stack *kes)
{
	return (uint64_t)&kes->data + KERNEL_STACK_SIZE;
}
