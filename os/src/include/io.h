#ifndef __IO__RVOS_H
#define __IO__RVOS_H
#define STDOUT 1
#include "keldef.h"
#include "kelarg.h"


 #define ZEROPAD    1       /* pad with zero */
 #define SIGN   2       /* unsigned/signed long */
 #define PLUS   4       /* show plus */
 #define SPACE  8       /* space if plus */
 #define LEFT   16      /* left justified */
 #define SPECIAL    32      /* 0x */
 #define LARGE  64      /* use 'ABCDEF' instead of 'abcdef' */

#define do_div(n,base) _div(&n,base)/*({ \
    int __res; \
    __res = ((unsigned long) n) % (unsigned) base; \
    n = ((unsigned long) n) / (unsigned) base; \
    __res; })*/

int sprint(char *buf, const char *fmt, ...);
int vsprint(char *buf, const char *fmt, va_list args);
int print(const char *fmt, ...);
int putchar(int ch);
int puts(const char *str);
#endif
