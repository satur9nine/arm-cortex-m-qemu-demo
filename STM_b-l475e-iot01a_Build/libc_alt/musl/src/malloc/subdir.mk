################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libc_alt/musl/src/malloc/memalign.c \
../libc_alt/musl/src/malloc/posix_memalign.c 

OBJS += \
./libc_alt/musl/src/malloc/memalign.o \
./libc_alt/musl/src/malloc/posix_memalign.o 

C_DEPS += \
./libc_alt/musl/src/malloc/memalign.d \
./libc_alt/musl/src/malloc/posix_memalign.d 


# Each subdirectory must supply rules for building sources it contributes
libc_alt/musl/src/malloc/%.o: ../libc_alt/musl/src/malloc/%.c libc_alt/musl/src/malloc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -DSTM32L475xx -DCMB_USER_CFG -I../LocalDemoFiles -I../cm_backtrace -I../FreeRTOS/Source/portable/GCC/ARM_CM3 -I../FreeRTOS/CommonDemoFiles/include -I../FreeRTOS/Source/include -I../STM_b-l475e-iot01a/stm32l4xx_hal_driver/Inc -I../STM_b-l475e-iot01a/include -I../STM_b-l475e-iot01a/CMSIS/Include -I../STM_b-l475e-iot01a/CMSIS/Core/Include -I../rrc-backtrace/include -I../libc_alt/musl/include -I../common/include -std=gnu11 -funwind-tables -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


