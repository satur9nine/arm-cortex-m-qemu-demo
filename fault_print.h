#ifndef FAULT_PRINT_H
#define FAULT_PRINT_H

#include <stdio.h>
#include <stdarg.h>

int fault_printf (const char *__restrict format, ...)
               _ATTRIBUTE ((__format__ (__printf__, 1, 2)));

#endif // FAULT_PRINT_H
