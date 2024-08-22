################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM_b-l475e-iot01a/main.c \
../STM_b-l475e-iot01a/stm32l4xx_hal_msp.c \
../STM_b-l475e-iot01a/stm32l4xx_it.c \
../STM_b-l475e-iot01a/sys.c \
../STM_b-l475e-iot01a/system_stm32l4xx.c 

S_UPPER_SRCS += \
../STM_b-l475e-iot01a/startup_stm32l475xx.S 

OBJS += \
./STM_b-l475e-iot01a/main.o \
./STM_b-l475e-iot01a/startup_stm32l475xx.o \
./STM_b-l475e-iot01a/stm32l4xx_hal_msp.o \
./STM_b-l475e-iot01a/stm32l4xx_it.o \
./STM_b-l475e-iot01a/sys.o \
./STM_b-l475e-iot01a/system_stm32l4xx.o 

S_UPPER_DEPS += \
./STM_b-l475e-iot01a/startup_stm32l475xx.d 

C_DEPS += \
./STM_b-l475e-iot01a/main.d \
./STM_b-l475e-iot01a/stm32l4xx_hal_msp.d \
./STM_b-l475e-iot01a/stm32l4xx_it.d \
./STM_b-l475e-iot01a/sys.d \
./STM_b-l475e-iot01a/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
STM_b-l475e-iot01a/%.o: ../STM_b-l475e-iot01a/%.c STM_b-l475e-iot01a/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -DSTM32L475xx -DCMB_USER_CFG -I../LocalDemoFiles -I../cm_backtrace -I../FreeRTOS/Source/portable/GCC/ARM_CM3 -I../FreeRTOS/CommonDemoFiles/include -I../FreeRTOS/Source/include -I../STM_b-l475e-iot01a/stm32l4xx_hal_driver/Inc -I../STM_b-l475e-iot01a/include -I../STM_b-l475e-iot01a/CMSIS/Include -I../STM_b-l475e-iot01a/CMSIS/Core/Include -I../rrc-backtrace/include -I../libc_alt/musl/include -I../common/include -std=gnu11 -funwind-tables -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

STM_b-l475e-iot01a/%.o: ../STM_b-l475e-iot01a/%.S STM_b-l475e-iot01a/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


