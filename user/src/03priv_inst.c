#include "lib.h"


int32_t main()
{
    print("Try to execute privileged instruction in U Mode");
    print("Kernel should kill this application!");
        __asm__("sret");
    return 0;
}
