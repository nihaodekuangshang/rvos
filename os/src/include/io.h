#ifndef __IO__RVOS_H
#define __IO__RVOS_H
typedef char *  va_list;


 #ifdef  __cplusplus
 #define _ADDRESSOF(v)   ( &reinterpret_cast<const char &>(v) )
 #else
 #define _ADDRESSOF(v)   ( &(v) )
 #endif


 #define _INTSIZEOF(n)   ( (sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1) )




 #define _crt_va_start(ap,v)  ( ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v) )
 #define _crt_va_arg(ap,t)    ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
 #define _crt_va_end(ap)      ( ap = (va_list)0 )


 #define va_start _crt_va_start /* windows stdarg.h */
 #define va_arg _crt_va_arg
 #define va_end _crt_va_end



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
