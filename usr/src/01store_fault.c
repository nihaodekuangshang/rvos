#include "lib.h"
int32_t main()
{
	print("Into Test store_fault, we will insert an invalid store operation...");
	print("Kernel should kill this application!");
	int *p = 0x00;
	*p = 0;
	return 0;
}
