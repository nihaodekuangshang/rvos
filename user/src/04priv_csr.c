#include "lib.h"


int32_t main()
{
    print("Try to access privileged CSR in U Mode");
    print("Kernel should kill this application!");
    return 0;
}
