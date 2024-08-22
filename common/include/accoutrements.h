#ifndef ACCOUTREMENTS_H
#define ACCOUTREMENTS_H

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

enum {
    CRASH_TYPE_HAL_ERROR = 1,
    CRASH_TYPE_FREERTOS_ASSERT,
    CRASH_TYPE_FREERTOS_STACK_OVERFLOW,
};


void force_crash(uint16_t crash_type);

int fault_printf(const char *__restrict format, ...)
               _ATTRIBUTE ((__format__ (__printf__, 1, 2)));

void print_mem(const void *ptr, const size_t size);

#endif // ACCOUTREMENTS_H
