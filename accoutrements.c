#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "LM3S6965.h"

#include "accoutrements.h"

extern int _write(int handle, char *data, int size);

// Write to uart directly without heap
int fault_printf(const char *__restrict format, ...)
{
    static char pbuf[180];
    va_list args;
    va_start(args, format);
    int len = vsnprintf(pbuf, sizeof(pbuf), format, args);
    (void) _write((int) stderr, pbuf, len);
    va_end (args);
    return len;
}

void cm_backtrace_late_fault_handler(uint32_t stacked_pc, uint32_t stacked_psr, uint32_t stacked_lr, uint32_t cfsr,
        uint32_t *backtrace_addrs, uint32_t backtrace_buf_size)
{
    (void) stacked_pc;
    (void) stacked_psr;
    (void) stacked_lr;
    (void) cfsr;
    (void) backtrace_addrs;
    (void) backtrace_buf_size;

    fault_printf("Reset system\n\n");
    NVIC_SystemReset();
    while (1);
}

void print_mem(const void *ptr, const size_t size)
{
    const size_t BYTES_PER_LINE = 16;
    size_t offset, read;

    uint8_t *p = (uint8_t *) ptr;
    const uint8_t *maxp = (p + size);

    if (ptr == NULL || size == 0) {
        return;
    }

    for (offset = read = 0; offset != size; offset += read) {
        uint8_t buf[BYTES_PER_LINE];

        for (read = 0; read != BYTES_PER_LINE && (&p[offset + read]) < maxp; read++) {
            buf[read] = p[offset + read];
        }

        if (read == 0)
            return;

        printf("%.8x: ", (unsigned int) (offset + (unsigned int) ptr));

        for (size_t i = 0; i < read; i++) {
            printf("%.2x", buf[i]);
        }

        printf("\n");
    }
}
