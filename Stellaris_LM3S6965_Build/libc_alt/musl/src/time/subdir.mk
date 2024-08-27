################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libc_alt/musl/src/time/__month_to_secs.c \
../libc_alt/musl/src/time/__secs_to_tm.c \
../libc_alt/musl/src/time/__tm_to_secs.c \
../libc_alt/musl/src/time/__year_to_secs.c \
../libc_alt/musl/src/time/gmtime_r.c \
../libc_alt/musl/src/time/timegm.c 

OBJS += \
./libc_alt/musl/src/time/__month_to_secs.o \
./libc_alt/musl/src/time/__secs_to_tm.o \
./libc_alt/musl/src/time/__tm_to_secs.o \
./libc_alt/musl/src/time/__year_to_secs.o \
./libc_alt/musl/src/time/gmtime_r.o \
./libc_alt/musl/src/time/timegm.o 

C_DEPS += \
./libc_alt/musl/src/time/__month_to_secs.d \
./libc_alt/musl/src/time/__secs_to_tm.d \
./libc_alt/musl/src/time/__tm_to_secs.d \
./libc_alt/musl/src/time/__year_to_secs.d \
./libc_alt/musl/src/time/gmtime_r.d \
./libc_alt/musl/src/time/timegm.d 


# Each subdirectory must supply rules for building sources it contributes
libc_alt/musl/src/time/%.o: ../libc_alt/musl/src/time/%.c libc_alt/musl/src/time/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -DCMB_USER_CFG -D_FORTIFY_SOURCE=3 -I../cm_backtrace -I../libc_alt/musl/include -I../FreeRTOS/Source/include -I../FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Stellaris_LM3S6965/FreeRTOS/LocalDemoFiles -I../Stellaris_LM3S6965/FreeRTOS/CommonDemoFiles/include -I../Stellaris_LM3S6965/LuminaryMicroDrivers -I../Stellaris_LM3S6965/include -I../Stellaris_LM3S6965/CMSIS/Device/TI/LM3S/Include -I../Stellaris_LM3S6965/CMSIS/Core/Include -I../rrc-backtrace/include -I../common/include -std=gnu11 -Werror=stringop-overflow -funwind-tables -fstack-protector-strong -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


