################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/Source/portable/GCC/ARM_CM3/port.c 

OBJS += \
./FreeRTOS/Source/portable/GCC/ARM_CM3/port.o 

C_DEPS += \
./FreeRTOS/Source/portable/GCC/ARM_CM3/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/portable/GCC/ARM_CM3/%.o: ../FreeRTOS/Source/portable/GCC/ARM_CM3/%.c FreeRTOS/Source/portable/GCC/ARM_CM3/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -DCMB_USER_CFG -D_FORTIFY_SOURCE=3 -I../cm_backtrace -I../libc_alt/musl/include -I../FreeRTOS/Source/include -I../FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Stellaris_LM3S6965/FreeRTOS/LocalDemoFiles -I../Stellaris_LM3S6965/FreeRTOS/CommonDemoFiles/include -I../Stellaris_LM3S6965/LuminaryMicroDrivers -I../Stellaris_LM3S6965/include -I../Stellaris_LM3S6965/CMSIS/Device/TI/LM3S/Include -I../Stellaris_LM3S6965/CMSIS/Core/Include -I../rrc-backtrace/include -I../common/include -std=gnu11 -Werror=stringop-overflow -funwind-tables -fstack-protector-strong -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


