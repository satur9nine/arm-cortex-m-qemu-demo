################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../common/accoutrements.c \
../common/heap_newlib.c \
../common/security.c \
../common/security_tests.c \
../common/strntoint_r.c \
../common/sys_shared.c 

OBJS += \
./common/accoutrements.o \
./common/heap_newlib.o \
./common/security.o \
./common/security_tests.o \
./common/strntoint_r.o \
./common/sys_shared.o 

C_DEPS += \
./common/accoutrements.d \
./common/heap_newlib.d \
./common/security.d \
./common/security_tests.d \
./common/strntoint_r.d \
./common/sys_shared.d 


# Each subdirectory must supply rules for building sources it contributes
common/%.o: ../common/%.c common/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -DSTM32F405xx -DCMB_USER_CFG -D_FORTIFY_SOURCE=2 -I../LocalDemoFiles -I../cm_backtrace -I../FreeRTOS/Source/portable/GCC/ARM_CM3 -I../FreeRTOS/CommonDemoFiles/include -I../FreeRTOS/Source/include -I../rrc-backtrace/include -I../libc_alt/musl/include -I../common/include -I../STM_netduino-plus-2/STM32F4xx_HAL_Driver/Inc -I../STM_netduino-plus-2/include -I../STM_netduino-plus-2/CMSIS/Include -I../STM_netduino-plus-2/CMSIS/Core/Include -std=gnu11 -Werror=stringop-overflow -funwind-tables -fstack-protector-strong -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


