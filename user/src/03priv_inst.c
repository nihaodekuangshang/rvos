#include <stdio.h>
#include <stddef.h>

int32_t main()
{
    printf("Try to execute privileged instruction in U Mode\n");
    printf("Kernel should kill this application!\n");
        __asm__("sret");
    return 0;
}
