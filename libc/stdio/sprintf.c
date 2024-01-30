#include <stdio.h>
int sprintf(char *buf, const char *fmt, ...)
{
    //记录fmt对应的地址
    va_list args;
    int val;
    //得到首个%对应的字符地址
    va_start(args, fmt);
    int i = vsprintf(buf, fmt, args);
    va_end(args);
    return val;
}
