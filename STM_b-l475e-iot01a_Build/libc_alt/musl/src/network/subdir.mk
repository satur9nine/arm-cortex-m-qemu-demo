################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libc_alt/musl/src/network/htonl.c \
../libc_alt/musl/src/network/htons.c \
../libc_alt/musl/src/network/ntohl.c \
../libc_alt/musl/src/network/ntohs.c 

OBJS += \
./libc_alt/musl/src/network/htonl.o \
./libc_alt/musl/src/network/htons.o \
./libc_alt/musl/src/network/ntohl.o \
./libc_alt/musl/src/network/ntohs.o 

C_DEPS += \
./libc_alt/musl/src/network/htonl.d \
./libc_alt/musl/src/network/htons.d \
./libc_alt/musl/src/network/ntohl.d \
./libc_alt/musl/src/network/ntohs.d 


# Each subdirectory must supply rules for building sources it contributes
libc_alt/musl/src/network/%.o: ../libc_alt/musl/src/network/%.c libc_alt/musl/src/network/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -DCMB_USER_CFG -D_FORTIFY_SOURCE=2 -DSTM32L475xx -I../cm_backtrace -I../FreeRTOS/Source/portable/GCC/ARM_CM3 -I../FreeRTOS/CommonDemoFiles/include -I../FreeRTOS/Source/include -I../rrc-backtrace/include -I../libc_alt/musl/include -I../common/include -I../STM_b-l475e-iot01a/stm32l4xx_hal_driver/Inc -I../STM_b-l475e-iot01a/include -I../STM_b-l475e-iot01a/CMSIS/Include -I../STM_b-l475e-iot01a/CMSIS/Core/Include -std=gnu11 -Werror=stringop-overflow -funwind-tables -fstack-protector-strong -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


