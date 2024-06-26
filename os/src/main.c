#include "sbi.h"
#include <stdio.h>
#include "trap.h"
#include <stddef.h>
#include "task.h"
#include "loader.h"
#include "timer.h"

void sbss();
void ebss();
void clearBss();
__attribute((constructor)) void init()
{
	clearBss();
	init_trap();
	init_loader();
	load_apps();
	init_task();
	init_time();

}

int main(int argc, char **argv, char** envp)
{
	init();
	//	获取环境变量，需要验证子字符串
//	char** env;
//	for (env = envp; *env != 0; env++)
//	{
//	 char* thisEnv = *env;
//	 if(thisEnv == ""
//	}
	printf("loading system...\n");
	set_next_trigger();
	run_first_task(&task_man);
	while (1) {}
	return 0;
}
void clearBss(){
	uint64_t* psb = (uint64_t*)&sbss;
	uint64_t* peb = (uint64_t*)&ebss;
	for(unsigned long *i = psb; i <= peb; i++){
		*i = 0;
	}
}
