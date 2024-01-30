#include <stdio.h>

#if defined(__is_libk)
//#include <kernel/tty.h>
#include <kernel/kelio.h>
#include <kernel/syscall.h>
#endif

int putchar(char ic) {
#if defined(__is_libk)
 	_print_c(ic);
#else
	// TODO: Implement stdio and the write system call.
	printf("%c",ic);
#endif
	return ic;
}
