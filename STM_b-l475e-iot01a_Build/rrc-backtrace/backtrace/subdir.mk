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
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -DCMB_USER_CFG -D_FORTIFY_SOURCE=2 -DSTM32L475xx -I../cm_backtrace -I../FreeRTOS/Source/portable/GCC/ARM_CM3 -I../FreeRTOS/CommonDemoFiles/include -I../FreeRTOS/Source/include -I../rrc-backtrace/include -I../libc_alt/musl/include -I../common/include -I../STM_b-l475e-iot01a/stm32l4xx_hal_driver/Inc -I../STM_b-l475e-iot01a/include -I../STM_b-l475e-iot01a/CMSIS/Include -I../STM_b-l475e-iot01a/CMSIS/Core/Include -std=gnu11 -Werror=stringop-overflow -funwind-tables -fstack-protector-strong -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


