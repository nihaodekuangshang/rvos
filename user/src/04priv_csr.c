#include <stdio.h>
#include <stddef.h>


int32_t main()
{
    printf("Try to access privileged CSR in U Mode\n");
    printf("Kernel should kill this application!\n");
    return 0;
}
