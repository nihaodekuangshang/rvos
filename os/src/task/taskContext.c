#include "include/taskContext.h"
void  zero_init(struct task_context *con) 
{
	con->ra=0;
	con->sp=0;
	for(int32_t i = 0; i< 12; ++i){
		con->s[i] = 0;
	}
}
void __restore();
void  goto_restore(struct task_context *con,uint64_t ksp)
{

	con->ra=(uint64_t)__restore;
	con->sp=ksp;
	for(int32_t i = 0; i< 12; ++i){
		con->s[i] = 0;
	}
}
