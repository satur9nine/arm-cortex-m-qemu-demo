#include <stdint.h>

#include "accoutrements.h"
#include "cmsis_impl.h"

// Should be populated at boot by TRNG
unsigned long __stack_chk_guard = 0xC1C2C3C4;

__NO_RETURN void __stack_chk_fail(void)
{
    __disable_irq();
    fault_printf("Stack overflow detected\n");
    force_crash(CRASH_TYPE_STACK_PROTECTOR);
}

__NO_RETURN void __chk_fail()
{
    __disable_irq();
    fault_printf("Fortify check fail\n");
    force_crash(CRASH_TYPE_FORTIFY_CHECK_FAIL);
}
