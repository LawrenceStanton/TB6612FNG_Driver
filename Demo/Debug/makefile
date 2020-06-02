################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
TB6612FNG_Driver_Demo.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
TB6612FNG_Driver_Demo.list \

OBJCOPY_BIN += \
TB6612FNG_Driver_Demo.bin \


# All Target
all: TB6612FNG_Driver_Demo.elf secondary-outputs

# Tool invocations
TB6612FNG_Driver_Demo.elf: $(OBJS) $(USER_OBJS) /Users/lawrencestanton/OneDrive\ -\ University\ of\ Cape\ Town/Engineering/Other\ Projects/TB6612FNG\ Driver/Demo/STM32F051C6TX_FLASH.ld
	arm-none-eabi-gcc -o "TB6612FNG_Driver_Demo.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"/Users/lawrencestanton/OneDrive - University of Cape Town/Engineering/Other Projects/TB6612FNG Driver/Demo/STM32F051C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="TB6612FNG_Driver_Demo.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

TB6612FNG_Driver_Demo.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "TB6612FNG_Driver_Demo.list"
	@echo 'Finished building: $@'
	@echo ' '

TB6612FNG_Driver_Demo.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "TB6612FNG_Driver_Demo.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
