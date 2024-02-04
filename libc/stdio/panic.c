#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <kernel/kelio.h>
#include <kernel/syscall.h>

void shutdown_err();

void  panic(const char* restrict format, ...) {
	char c[256];
	va_list parameters;
	va_start(parameters, format);

	int len = vsprintf(c,format,parameters);
	
	printf("%s\n",c);
#if defined( __is_libk)
	shutdown_err();
#elif defined(__is_libc)
	exit(1);
#endif
}
