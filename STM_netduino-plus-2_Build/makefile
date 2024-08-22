################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include rrc-backtrace/backtrace/subdir.mk
-include libc_alt/newlib/newlib/libc/string/subdir.mk
-include libc_alt/musl/src/time/subdir.mk
-include libc_alt/musl/src/string/subdir.mk
-include libc_alt/musl/src/network/subdir.mk
-include libc_alt/musl/src/malloc/subdir.mk
-include common/subdir.mk
-include cm_backtrace/subdir.mk
-include STM_netduino-plus-2/rrc-backtrace/backtrace/subdir.mk
-include STM_netduino-plus-2/libc_alt/newlib/newlib/libc/string/subdir.mk
-include STM_netduino-plus-2/libc_alt/musl/src/time/subdir.mk
-include STM_netduino-plus-2/libc_alt/musl/src/string/subdir.mk
-include STM_netduino-plus-2/libc_alt/musl/src/network/subdir.mk
-include STM_netduino-plus-2/libc_alt/musl/src/malloc/subdir.mk
-include STM_netduino-plus-2/common/subdir.mk
-include STM_netduino-plus-2/cm_backtrace/subdir.mk
-include STM_netduino-plus-2/STM32F4xx_HAL_Driver/Src/subdir.mk
-include STM_netduino-plus-2/subdir.mk
-include FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include FreeRTOS/Source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := arm-cortex-qemu-demo
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
arm-cortex-qemu-demo.bin \

SECONDARY_SIZE += \
arm-cortex-qemu-demo.siz \


# All Target
all: main-build

# Main-build Target
main-build: arm-cortex-qemu-demo.elf secondary-outputs

# Tool invocations
arm-cortex-qemu-demo.elf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM Cross C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall -Wextra -g3 -T ../STM_netduino-plus-2/STM32F405RGTX_FLASH.ld -Xlinker --gc-sections -Wl,-Map,"arm-cortex-qemu-demo.map" --specs=nano.specs --specs=nosys.specs -o "arm-cortex-qemu-demo.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

arm-cortex-qemu-demo.bin: arm-cortex-qemu-demo.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU ARM Cross Create Flash Image'
	arm-none-eabi-objcopy -O binary "arm-cortex-qemu-demo.elf"  "arm-cortex-qemu-demo.bin"
	@echo 'Finished building: $@'
	@echo ' '

arm-cortex-qemu-demo.siz: arm-cortex-qemu-demo.elf makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Invoking: GNU ARM Cross Print Size'
	arm-none-eabi-size --format=berkeley "arm-cortex-qemu-demo.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SX_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) arm-cortex-qemu-demo.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents main-build

-include ../makefile.targets
