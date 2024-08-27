################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM_netduino-plus-2/main.c \
../STM_netduino-plus-2/stm32f4xx_hal_msp.c \
../STM_netduino-plus-2/stm32f4xx_it.c \
../STM_netduino-plus-2/sys.c \
../STM_netduino-plus-2/system_stm32f4xx.c 

S_UPPER_SRCS += \
../STM_netduino-plus-2/startup_stm32f405rgtx.S 

OBJS += \
./STM_netduino-plus-2/main.o \
./STM_netduino-plus-2/startup_stm32f405rgtx.o \
./STM_netduino-plus-2/stm32f4xx_hal_msp.o \
./STM_netduino-plus-2/stm32f4xx_it.o \
./STM_netduino-plus-2/sys.o \
./STM_netduino-plus-2/system_stm32f4xx.o 

S_UPPER_DEPS += \
./STM_netduino-plus-2/startup_stm32f405rgtx.d 

C_DEPS += \
./STM_netduino-plus-2/main.d \
./STM_netduino-plus-2/stm32f4xx_hal_msp.d \
./STM_netduino-plus-2/stm32f4xx_it.d \
./STM_netduino-plus-2/sys.d \
./STM_netduino-plus-2/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
STM_netduino-plus-2/%.o: ../STM_netduino-plus-2/%.c STM_netduino-plus-2/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -DSTM32F405xx -DCMB_USER_CFG -D_FORTIFY_SOURCE=2 -I../LocalDemoFiles -I../cm_backtrace -I../FreeRTOS/Source/portable/GCC/ARM_CM3 -I../FreeRTOS/CommonDemoFiles/include -I../FreeRTOS/Source/include -I../rrc-backtrace/include -I../libc_alt/musl/include -I../common/include -I../STM_netduino-plus-2/STM32F4xx_HAL_Driver/Inc -I../STM_netduino-plus-2/include -I../STM_netduino-plus-2/CMSIS/Include -I../STM_netduino-plus-2/CMSIS/Core/Include -std=gnu11 -Werror=stringop-overflow -funwind-tables -fstack-protector-strong -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

STM_netduino-plus-2/%.o: ../STM_netduino-plus-2/%.S STM_netduino-plus-2/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


