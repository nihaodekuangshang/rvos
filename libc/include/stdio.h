#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>
#include <stdarg.h>

#define EOF (-1)

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

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);
int sprint(char *buf, const char *fmt, ...);
int vsprint(char *buf, const char *fmt, va_list args);
#ifdef __cplusplus
}
#endif

#endif
