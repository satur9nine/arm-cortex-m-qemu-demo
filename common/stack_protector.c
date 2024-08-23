#include <stdint.h>
#include "accoutrements.h"


// Should be populated at boot by TRNG
unsigned long __stack_chk_guard = 0xC1C2C3C4;

void __stack_chk_fail(void)
{
    fault_printf("Stack overflow detected\n");
    force_crash(CRASH_TYPE_STACK_PROTECTOR);
}
