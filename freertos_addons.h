uint32_t* pvTaskStackStartAddrForTask(TaskHandle_t xTask)
{
	return xTask->pxStack;
}

uint32_t xTaskStackSizeForTask(TaskHandle_t xTask)
{
	return xTask->uxSizeOfStack;
}

uint32_t *xTaskStackAddrForTask(TaskHandle_t xTask)
{
	return xTask->pxTopOfStack;
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
