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
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -DCMB_USER_CFG -D_FORTIFY_SOURCE=3 -I../cm_backtrace -I../libc_alt/musl/include -I../FreeRTOS/Source/include -I../FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Stellaris_LM3S6965/FreeRTOS/LocalDemoFiles -I../Stellaris_LM3S6965/FreeRTOS/CommonDemoFiles/include -I../Stellaris_LM3S6965/LuminaryMicroDrivers -I../Stellaris_LM3S6965/include -I../Stellaris_LM3S6965/CMSIS/Device/TI/LM3S/Include -I../Stellaris_LM3S6965/CMSIS/Core/Include -I../rrc-backtrace/include -I../common/include -std=gnu11 -Werror=stringop-overflow -funwind-tables -fstack-protector-strong -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


