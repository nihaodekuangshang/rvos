#include "sbi.h"
#include <stdio.h>
#include "batch.h"

void sbss();
void ebss();
void clearBss();
__attribute((constructor)) void init()
{
	clearBss();
	init_app_man();

}

int main(int argc, char **argv, char** envp)
{
	//	获取环境变量，需要验证子字符串
//	char** env;
//	for (env = envp; *env != 0; env++)
//	{
//	 char* thisEnv = *env;
//	 if(thisEnv == ""
//	}
	shutdown();
	printf("loading system...");
	while (1) {}
	return 0;
}
void clearBss(){
	void (*psb)() = &sbss;
	void (*peb)() = &ebss;
	for(unsigned long *i = psb; i <= peb; i++){
		*i = 0;
	}
}
