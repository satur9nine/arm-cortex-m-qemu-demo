#ifndef ACCOUTREMENTS_H
#define ACCOUTREMENTS_H

#include <stdio.h>
#include <stdarg.h>

int fault_printf(const char *__restrict format, ...)
               _ATTRIBUTE ((__format__ (__printf__, 1, 2)));

void print_mem(const void *ptr, const size_t size);

#endif // ACCOUTREMENTS_H
