#include <stdlib.h>
int main();
//void sbss();
//void ebss();
//void clearBss();
__attribute__((used,section(".text.entry"))) void _start()
{
	exit(main());
}
//void clearBss(){
	//void (*psb)() = &sbss;
	//void (*peb)() = &ebss;
	//for(unsigned long *i = psb; i <= peb; i++){
		//*i = 0;
	//}
//}
