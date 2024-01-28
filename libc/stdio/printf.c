#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <kernel/kelio.h>

static bool print(const char* data, size_t length) {
	size_t len = (size_t)_print_str(data);
	if(len == length){
		return true;
	}else{
		return false;
	}
}

int printf(const char* restrict format, ...) {
	char c[256];
	va_list parameters;
	va_start(parameters, format);
	int len = vsprintf(c,format,parameters);
	print(c,len);
	return len;
}

