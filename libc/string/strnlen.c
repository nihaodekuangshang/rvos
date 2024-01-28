
#include <string.h>

size_t strnlen(const char* str,unsigned long max) {
	size_t len = 0;
	while (str[len] && len <=max)
		len++;
	return len;
}
