#include <stdio.h>
#include <stddef.h>
int32_t main()
{
	printf("Into Test store_fault, we will insert an invalid store operation...\n");
	printf("Kernel should kill this application!\n");
	int *p = 0x00;
	*p = 0;
	return 0;
}
