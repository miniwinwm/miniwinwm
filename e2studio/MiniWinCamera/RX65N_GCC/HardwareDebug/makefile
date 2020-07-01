################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

-include makefile.init

RM := rm -rf *.lst *.lis *.lpp *.map

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include generate/subdir.mk
-include MiniWinCamera_Common/subdir.mk
-include MiniWin/ui/subdir.mk
-include MiniWin/hal/windows/subdir.mk
-include MiniWin/hal/stm32f429/subdir.mk
-include MiniWin/hal/stm32f407/subdir.mk
-include MiniWin/hal/rx65n_gcc/subdir.mk
-include MiniWin/hal/rx65n/subdir.mk
-include MiniWin/hal/lpc54628/subdir.mk
-include MiniWin/hal/linux/subdir.mk
-include MiniWin/hal/subdir.mk
-include MiniWin/gl/fonts/truetype/mcufont/subdir.mk
-include MiniWin/gl/fonts/truetype/subdir.mk
-include MiniWin/gl/fonts/bitmapped/subdir.mk
-include MiniWin/gl/subdir.mk
-include MiniWin/dialogs/subdir.mk
-include MiniWin/bitmaps/subdir.mk
-include MiniWin/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(SRC_UPPER_DEPS)),)
-include $(SRC_UPPER_DEPS)
endif
ifneq ($(strip $(P_UPPER_DEPS)),)
-include $(P_UPPER_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(PP_UPPER_DEPS)),)
-include $(PP_UPPER_DEPS)
endif
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif
ifneq ($(strip $(FSY_UPPER_DEPS)),)
-include $(FSY_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif
ifneq ($(strip $(JMP_UPPER_DEPS)),)
-include $(JMP_UPPER_DEPS)
endif
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(SX_UPPER_DEPS)),)
-include $(SX_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS += \

OBJCOPY += \
MiniWinCamera_RX65N_GCC.mot \


# All Target
all: MiniWinCamera_RX65N_GCC.elf secondary-outputs

# Tool invocations
MiniWinCamera_RX65N_GCC.elf: $(OBJS) $(USER_OBJS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(LINKER_SCRIPT)
	@echo 'Building target: $@'
	@echo 'Invoking Linker'
	$(file > MiniWinCamera_RX65N_GCC.elf.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -o "MiniWinCamera_RX65N_GCC.elf" $(OBJS) $(USER_OBJS) $(LIBS) -T "C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate/linker_script.ld" -Wl,--start-group -lm -lc -lgcc -Wl,--end-group -nostartfiles -Wl,-e_PowerON_Reset -Wl,-M=MiniWinCamera_RX65N_GCC.map)
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -o "MiniWinCamera_RX65N_GCC.elf" $(OBJS) $(USER_OBJS) $(LIBS) -T "C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate/linker_script.ld" -Wl,--start-group -lm -lc -lgcc -Wl,--end-group -nostartfiles -Wl,-e_PowerON_Reset -Wl,-M=MiniWinCamera_RX65N_GCC.map'

	rx-elf-gcc @"MiniWinCamera_RX65N_GCC.elf.in"
	@echo 'Finished building target: $@'
	@echo ' '
: 
	@echo 'Invoking: Library Generator'
	rx-elf-libgen  --header-files=all --select-lib=newlib --compiler-options=-O0,-ffunction-sections,-fdata-sections,-m64bit-doubles,-mcpu=rx64m,-misa=v2,-mlittle-endian-data --assembler-options=-m64bit-doubles,-mlittle-endian-data -o
	@echo 'Finished building: $@'
	@echo ' '
MiniWinCamera_RX65N_GCC.mot: MiniWinCamera_RX65N_GCC.elf
	@echo 'Invoking Object Copy'
	rx-elf-objcopy "MiniWinCamera_RX65N_GCC.elf" -O srec -I elf32-rx-be-ns  "MiniWinCamera_RX65N_GCC.mot"
	@echo 'Finished building: $@'
	@echo ' '
# Other Targets
clean:
ifneq ($(strip $(JMP_DEPS)),)
	-$(file > clean_JMP_DEPS.tmp, $(JMP_DEPS))
	-@ xargs -s 6000 -t -a clean_JMP_DEPS.tmp $(RM)
	-@$(RM) clean_JMP_DEPS.tmp
endif
ifneq ($(strip $(FSY_DEPS)),)
	-$(file > clean_FSY_DEPS.tmp, $(FSY_DEPS))
	-@ xargs -s 6000 -t -a clean_FSY_DEPS.tmp $(RM)
	-@$(RM) clean_FSY_DEPS.tmp
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
	-$(file > clean_C_UPPER_DEPS.tmp, $(C_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_C_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_C_UPPER_DEPS.tmp
endif
ifneq ($(strip $(SRC_UPPER_DEPS)),)
	-$(file > clean_SRC_UPPER_DEPS.tmp, $(SRC_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_SRC_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_SRC_UPPER_DEPS.tmp
endif
ifneq ($(strip $(P_UPPER_DEPS)),)
	-$(file > clean_P_UPPER_DEPS.tmp, $(P_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_P_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_P_UPPER_DEPS.tmp
endif
ifneq ($(strip $(S_DEPS)),)
	-$(file > clean_S_DEPS.tmp, $(S_DEPS))
	-@ xargs -s 6000 -t -a clean_S_DEPS.tmp $(RM)
	-@$(RM) clean_S_DEPS.tmp
endif
ifneq ($(strip $(PP_UPPER_DEPS)),)
	-$(file > clean_PP_UPPER_DEPS.tmp, $(PP_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_PP_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_PP_UPPER_DEPS.tmp
endif
ifneq ($(strip $(P_DEPS)),)
	-$(file > clean_P_DEPS.tmp, $(P_DEPS))
	-@ xargs -s 6000 -t -a clean_P_DEPS.tmp $(RM)
	-@$(RM) clean_P_DEPS.tmp
endif
ifneq ($(strip $(FSY_UPPER_DEPS)),)
	-$(file > clean_FSY_UPPER_DEPS.tmp, $(FSY_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_FSY_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_FSY_UPPER_DEPS.tmp
endif
ifneq ($(strip $(C_DEPS)),)
	-$(file > clean_C_DEPS.tmp, $(C_DEPS))
	-@ xargs -s 6000 -t -a clean_C_DEPS.tmp $(RM)
	-@$(RM) clean_C_DEPS.tmp
endif
ifneq ($(strip $(SRC_DEPS)),)
	-$(file > clean_SRC_DEPS.tmp, $(SRC_DEPS))
	-@ xargs -s 6000 -t -a clean_SRC_DEPS.tmp $(RM)
	-@$(RM) clean_SRC_DEPS.tmp
endif
ifneq ($(strip $(OBJCOPY)),)
	-$(file > clean_OBJCOPY.tmp, $(OBJCOPY))
	-@ xargs -s 6000 -t -a clean_OBJCOPY.tmp $(RM)
	-@$(RM) clean_OBJCOPY.tmp
endif
ifneq ($(strip $(JMP_UPPER_DEPS)),)
	-$(file > clean_JMP_UPPER_DEPS.tmp, $(JMP_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_JMP_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_JMP_UPPER_DEPS.tmp
endif
ifneq ($(strip $(PP_DEPS)),)
	-$(file > clean_PP_DEPS.tmp, $(PP_DEPS))
	-@ xargs -s 6000 -t -a clean_PP_DEPS.tmp $(RM)
	-@$(RM) clean_PP_DEPS.tmp
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
	-$(file > clean_ASM_UPPER_DEPS.tmp, $(ASM_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_ASM_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_ASM_UPPER_DEPS.tmp
endif
ifneq ($(strip $(SX_DEPS)),)
	-$(file > clean_SX_DEPS.tmp, $(SX_DEPS))
	-@ xargs -s 6000 -t -a clean_SX_DEPS.tmp $(RM)
	-@$(RM) clean_SX_DEPS.tmp
endif
ifneq ($(strip $(OBJS)),)
	-$(file > clean_OBJS.tmp, $(OBJS))
	-@ xargs -s 6000 -t -a clean_OBJS.tmp $(RM)
	-@$(RM) clean_OBJS.tmp
endif
ifneq ($(strip $(SX_UPPER_DEPS)),)
	-$(file > clean_SX_UPPER_DEPS.tmp, $(SX_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_SX_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_SX_UPPER_DEPS.tmp
endif
ifneq ($(strip $(ASM_DEPS)),)
	-$(file > clean_ASM_DEPS.tmp, $(ASM_DEPS))
	-@ xargs -s 6000 -t -a clean_ASM_DEPS.tmp $(RM)
	-@$(RM) clean_ASM_DEPS.tmp
endif
ifneq ($(strip $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS)),)
	-$(file > clean_LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS.tmp, $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS))
	-@ xargs -s 6000 -t -a clean_LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS.tmp $(RM)
	-@$(RM) clean_LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS.tmp
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
	-$(file > clean_S_UPPER_DEPS.tmp, $(S_UPPER_DEPS))
	-@ xargs -s 6000 -t -a clean_S_UPPER_DEPS.tmp $(RM)
	-@$(RM) clean_S_UPPER_DEPS.tmp
endif
	-$(RM)  MiniWinCamera_RX65N_GCC.elf
	-@echo ' '

secondary-outputs: $(OBJCOPY)

.PHONY: all clean dependents 

-include ../makefile.targets
