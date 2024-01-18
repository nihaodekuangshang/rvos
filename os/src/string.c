
#include "string.h"
#include "keldef.h"
size_t strnlen( const char *str, size_t strsz )
{
	size_t len = 0;
	for (int i = 0;str[i] != '\0' || i < strsz;i++) {
		len = i;
	 }
	return len+1;
}
