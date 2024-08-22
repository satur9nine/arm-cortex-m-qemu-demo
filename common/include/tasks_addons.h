// This file in included at the bottom of FreeRTOS tasks.c to add functions
// used by other libraries such as CmBacktrace.

#include "FreeRTOSConfig.h"

#if ( configRECORD_STACK_HIGH_ADDRESS != 1 )
#error "Need to define configRECORD_STACK_HIGH_ADDRESS to 1"
#endif

uint32_t* pvTaskStackStartAddrForTask(TaskHandle_t xTask)
{
    return xTask->pxStack;
}

uint32_t xTaskStackSizeForTask(TaskHandle_t xTask)
{
    return xTask->pxEndOfStack - xTask->pxStack;
}

uint32_t *xTaskStackAddrForTask(TaskHandle_t xTask)
{
    return (uint32_t *) xTask->pxTopOfStack;
}

uint32_t *vTaskStackAddr(void)
{
    return pvTaskStackStartAddrForTask(xTaskGetCurrentTaskHandle());
}

uint32_t vTaskStackSize(void)
{
    return xTaskStackSizeForTask(xTaskGetCurrentTaskHandle());
}

char * vTaskName(void)
{
    return pcTaskGetName(xTaskGetCurrentTaskHandle());
}
