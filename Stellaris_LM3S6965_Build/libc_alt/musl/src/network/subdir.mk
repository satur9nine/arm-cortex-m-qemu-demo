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
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -DCMB_USER_CFG -I../cm_backtrace -I../libc_alt/musl/include -I../FreeRTOS/Source/include -I../FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Stellaris_LM3S6965/FreeRTOS/LocalDemoFiles -I../Stellaris_LM3S6965/FreeRTOS/CommonDemoFiles/include -I../Stellaris_LM3S6965/LuminaryMicroDrivers -I../Stellaris_LM3S6965/include -I../Stellaris_LM3S6965/CMSIS/Device/TI/LM3S/Include -I../Stellaris_LM3S6965/CMSIS/Core/Include -I../rrc-backtrace/include -I../common/include -std=gnu11 -funwind-tables -fstack-protector-strong -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


