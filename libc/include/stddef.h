
#ifndef _STDDEF_H
#define _STDDEF_H 1
#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ long unsigned int
#endif
#if  defined (size_t)
typedef __SIZE_TYPE__ size_t;
#endif
typedef unsigned long   size_t ;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long  uint64_t;
typedef uint64_t       usize;
typedef char           int8_t;
typedef short          int16_t;
typedef int            int32_t;
typedef long long      int64_t;
typedef int64_t        isize;
#endif

