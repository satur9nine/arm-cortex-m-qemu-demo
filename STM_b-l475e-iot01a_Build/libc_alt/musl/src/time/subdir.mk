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
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -DCMB_USER_CFG -D_FORTIFY_SOURCE=2 -DSTM32L475xx -I../cm_backtrace -I../FreeRTOS/Source/portable/GCC/ARM_CM3 -I../FreeRTOS/CommonDemoFiles/include -I../FreeRTOS/Source/include -I../rrc-backtrace/include -I../libc_alt/musl/include -I../common/include -I../STM_b-l475e-iot01a/stm32l4xx_hal_driver/Inc -I../STM_b-l475e-iot01a/include -I../STM_b-l475e-iot01a/CMSIS/Include -I../STM_b-l475e-iot01a/CMSIS/Core/Include -std=gnu11 -Werror=stringop-overflow -funwind-tables -fstack-protector-strong -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


