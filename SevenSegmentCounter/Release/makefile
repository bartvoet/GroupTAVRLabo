################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
SevenSegmentCounter.lss \

FLASH_IMAGE += \
SevenSegmentCounter.hex \

EEPROM_IMAGE += \
SevenSegmentCounter.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: SevenSegmentCounter.elf secondary-outputs

# Tool invocations
SevenSegmentCounter.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SevenSegmentCounter.map -mmcu=atmega328p -o "SevenSegmentCounter.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SevenSegmentCounter.lss: SevenSegmentCounter.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SevenSegmentCounter.elf  >"SevenSegmentCounter.lss"
	@echo 'Finished building: $@'
	@echo ' '

SevenSegmentCounter.hex: SevenSegmentCounter.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex SevenSegmentCounter.elf  "SevenSegmentCounter.hex"
	@echo 'Finished building: $@'
	@echo ' '

SevenSegmentCounter.eep: SevenSegmentCounter.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex SevenSegmentCounter.elf  "SevenSegmentCounter.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SevenSegmentCounter.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p SevenSegmentCounter.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) SevenSegmentCounter.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
