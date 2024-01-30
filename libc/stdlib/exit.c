#include <stddef.h>
#include <kernel/syscall.h>
__attribute__((__noreturn__))
void  exit(int32_t exit_code) 
{
#if defined(__is_libc)
    sys_exit(exit_code);
	while (1) { }
    __builtin_unreachable();
#elif defined(__is_libk)
    printf("unsupport function in Smode");
    return;
#endif
}
