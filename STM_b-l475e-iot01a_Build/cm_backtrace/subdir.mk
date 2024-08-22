################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cm_backtrace/cm_backtrace.c 

S_UPPER_SRCS += \
../cm_backtrace/cmb_fault.S 

OBJS += \
./cm_backtrace/cm_backtrace.o \
./cm_backtrace/cmb_fault.o 

S_UPPER_DEPS += \
./cm_backtrace/cmb_fault.d 

C_DEPS += \
./cm_backtrace/cm_backtrace.d 


# Each subdirectory must supply rules for building sources it contributes
cm_backtrace/%.o: ../cm_backtrace/%.c cm_backtrace/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -DSTM32L475xx -DCMB_USER_CFG -I../LocalDemoFiles -I../cm_backtrace -I../FreeRTOS/Source/portable/GCC/ARM_CM3 -I../FreeRTOS/CommonDemoFiles/include -I../FreeRTOS/Source/include -I../STM_b-l475e-iot01a/stm32l4xx_hal_driver/Inc -I../STM_b-l475e-iot01a/include -I../STM_b-l475e-iot01a/CMSIS/Include -I../STM_b-l475e-iot01a/CMSIS/Core/Include -I../rrc-backtrace/include -I../libc_alt/musl/include -I../common/include -std=gnu11 -funwind-tables -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cm_backtrace/%.o: ../cm_backtrace/%.S cm_backtrace/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


