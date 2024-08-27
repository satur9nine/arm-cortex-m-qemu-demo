################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libc_alt/musl/src/string/memccpy.c \
../libc_alt/musl/src/string/memchr.c \
../libc_alt/musl/src/string/memcpy.c \
../libc_alt/musl/src/string/memmem.c \
../libc_alt/musl/src/string/memmove.c \
../libc_alt/musl/src/string/mempcpy.c \
../libc_alt/musl/src/string/memset.c \
../libc_alt/musl/src/string/stpcpy.c \
../libc_alt/musl/src/string/stpncpy.c \
../libc_alt/musl/src/string/strcmp.c \
../libc_alt/musl/src/string/strcpy.c \
../libc_alt/musl/src/string/strdup.c \
../libc_alt/musl/src/string/strlcpy.c \
../libc_alt/musl/src/string/strlen.c \
../libc_alt/musl/src/string/strncmp.c \
../libc_alt/musl/src/string/strncpy.c 

OBJS += \
./libc_alt/musl/src/string/memccpy.o \
./libc_alt/musl/src/string/memchr.o \
./libc_alt/musl/src/string/memcpy.o \
./libc_alt/musl/src/string/memmem.o \
./libc_alt/musl/src/string/memmove.o \
./libc_alt/musl/src/string/mempcpy.o \
./libc_alt/musl/src/string/memset.o \
./libc_alt/musl/src/string/stpcpy.o \
./libc_alt/musl/src/string/stpncpy.o \
./libc_alt/musl/src/string/strcmp.o \
./libc_alt/musl/src/string/strcpy.o \
./libc_alt/musl/src/string/strdup.o \
./libc_alt/musl/src/string/strlcpy.o \
./libc_alt/musl/src/string/strlen.o \
./libc_alt/musl/src/string/strncmp.o \
./libc_alt/musl/src/string/strncpy.o 

C_DEPS += \
./libc_alt/musl/src/string/memccpy.d \
./libc_alt/musl/src/string/memchr.d \
./libc_alt/musl/src/string/memcpy.d \
./libc_alt/musl/src/string/memmem.d \
./libc_alt/musl/src/string/memmove.d \
./libc_alt/musl/src/string/mempcpy.d \
./libc_alt/musl/src/string/memset.d \
./libc_alt/musl/src/string/stpcpy.d \
./libc_alt/musl/src/string/stpncpy.d \
./libc_alt/musl/src/string/strcmp.d \
./libc_alt/musl/src/string/strcpy.d \
./libc_alt/musl/src/string/strdup.d \
./libc_alt/musl/src/string/strlcpy.d \
./libc_alt/musl/src/string/strlen.d \
./libc_alt/musl/src/string/strncmp.d \
./libc_alt/musl/src/string/strncpy.d 


# Each subdirectory must supply rules for building sources it contributes
libc_alt/musl/src/string/%.o: ../libc_alt/musl/src/string/%.c libc_alt/musl/src/string/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -DCMB_USER_CFG -D_FORTIFY_SOURCE=3 -I../cm_backtrace -I../libc_alt/musl/include -I../FreeRTOS/Source/include -I../FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Stellaris_LM3S6965/FreeRTOS/LocalDemoFiles -I../Stellaris_LM3S6965/FreeRTOS/CommonDemoFiles/include -I../Stellaris_LM3S6965/LuminaryMicroDrivers -I../Stellaris_LM3S6965/include -I../Stellaris_LM3S6965/CMSIS/Device/TI/LM3S/Include -I../Stellaris_LM3S6965/CMSIS/Core/Include -I../rrc-backtrace/include -I../common/include -std=gnu11 -Werror=stringop-overflow -funwind-tables -fstack-protector-strong -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


