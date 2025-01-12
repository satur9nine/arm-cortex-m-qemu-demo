################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/Source/croutine.c \
../FreeRTOS/Source/event_groups.c \
../FreeRTOS/Source/list.c \
../FreeRTOS/Source/queue.c \
../FreeRTOS/Source/stream_buffer.c \
../FreeRTOS/Source/tasks.c \
../FreeRTOS/Source/timers.c 

OBJS += \
./FreeRTOS/Source/croutine.o \
./FreeRTOS/Source/event_groups.o \
./FreeRTOS/Source/list.o \
./FreeRTOS/Source/queue.o \
./FreeRTOS/Source/stream_buffer.o \
./FreeRTOS/Source/tasks.o \
./FreeRTOS/Source/timers.o 

C_DEPS += \
./FreeRTOS/Source/croutine.d \
./FreeRTOS/Source/event_groups.d \
./FreeRTOS/Source/list.d \
./FreeRTOS/Source/queue.d \
./FreeRTOS/Source/stream_buffer.d \
./FreeRTOS/Source/tasks.d \
./FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/%.o: ../FreeRTOS/Source/%.c FreeRTOS/Source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -DCMB_USER_CFG -D_FORTIFY_SOURCE=2 -DSTM32L475xx -I../cm_backtrace -I../FreeRTOS/Source/portable/GCC/ARM_CM3 -I../FreeRTOS/CommonDemoFiles/include -I../FreeRTOS/Source/include -I../rrc-backtrace/include -I../libc_alt/musl/include -I../common/include -I../STM_b-l475e-iot01a/stm32l4xx_hal_driver/Inc -I../STM_b-l475e-iot01a/include -I../STM_b-l475e-iot01a/CMSIS/Include -I../STM_b-l475e-iot01a/CMSIS/Core/Include -std=gnu11 -Werror=stringop-overflow -funwind-tables -fstack-protector-strong -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


