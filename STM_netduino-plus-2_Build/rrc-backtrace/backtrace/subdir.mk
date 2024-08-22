################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rrc-backtrace/backtrace/backtrace.c 

OBJS += \
./rrc-backtrace/backtrace/backtrace.o 

C_DEPS += \
./rrc-backtrace/backtrace/backtrace.d 


# Each subdirectory must supply rules for building sources it contributes
rrc-backtrace/backtrace/%.o: ../rrc-backtrace/backtrace/%.c rrc-backtrace/backtrace/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -DSTM32F405xx -DCMB_USER_CFG -I../LocalDemoFiles -I../cm_backtrace -I../FreeRTOS/Source/portable/GCC/ARM_CM3 -I../FreeRTOS/CommonDemoFiles/include -I../FreeRTOS/Source/include -I../rrc-backtrace/include -I../libc_alt/musl/include -I../common/include -I../STM_netduino-plus-2/STM32F4xx_HAL_Driver/Inc -I../STM_netduino-plus-2/include -I../STM_netduino-plus-2/CMSIS/Include -I../STM_netduino-plus-2/CMSIS/Core/Include -std=gnu11 -funwind-tables -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


