#include <stdio.h>
#include <stdarg.h>

#include "log.h"

// TODO: this variable will be set via command line or text file
int jump_loglevel = 0; // LOG_INIT;

void jump_log(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    fprintf(stdout, fmt, ap);
    va_end(ap);
}

