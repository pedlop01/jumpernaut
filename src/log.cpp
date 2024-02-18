#include <stdio.h>
#include <stdarg.h>

int jump_loglevel = 0xffff;

void jump_log(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    fprintf(stdout, fmt, ap);
    va_end(ap);
}

