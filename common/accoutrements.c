#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "FreeRTOS.h"
#include "task.h"

#include "cmsis_impl.h"

#include "accoutrements.h"

//
// A collection of helpful code for projects with FreeRTOS, CMSIS and CmBacktrace
//

extern void NVIC_SystemReset(void);

extern int _write(int handle, char *data, int size);

__NO_RETURN void force_crash(uint16_t crash_type)
{
    __disable_irq();

    // Should crash on every Cortex-M, looking at the PC of the crash we can
    // find the crash type
    void(* explode)(void) = (void (*)(void)) (0xFFFF0000 + crash_type);
    explode();
    while (1);
}

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

__NO_RETURN void vApplicationStackOverflowHook(TaskHandle_t pxTask, char * pcTaskName)
{
    ( void ) pxTask;

    __disable_irq();

    fault_printf("Stack overflow in task %s\n", pcTaskName);
    force_crash(CRASH_TYPE_FREERTOS_STACK_OVERFLOW);
}

__NO_RETURN void vAssertCalled(const char * pcFile, uint32_t ulLine)
{
    __disable_irq();

    fault_printf("FreeRTOS assert %s:%"PRIu32"\n", pcFile, ulLine);
    force_crash(CRASH_TYPE_FREERTOS_ASSERT);
}

__NO_RETURN void cm_backtrace_late_fault_handler(uint32_t stacked_pc, uint32_t stacked_psr, uint32_t stacked_lr, uint32_t cfsr,
        uint32_t *backtrace_addrs, uint32_t backtrace_buf_size)
{
    (void) stacked_pc;
    (void) stacked_psr;
    (void) stacked_lr;
    (void) cfsr;
    (void) backtrace_addrs;
    (void) backtrace_buf_size;

    fault_printf("Resetting...\n\n");
    NVIC_SystemReset();
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
