################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include makefile.init

RM := rm -rf *.sni *.dbg *.lst *.lis *.lpp *.map *.x *.lbp *.bls *.libelf *.rel *.lbk *.abs  *.obj *.p *.pp *.d *.asm 1st/*.obj 1st/*.d 1st/*.asm 1st/*.abs

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include FreeRTOS/subdir.mk
-include src/smc_gen/r_bsp/board/generic_rx65n/subdir.mk
-include src/smc_gen/r_bsp/mcu/rx65n/subdir.mk
-include FreeRTOS/portable/subdir.mk
-include src/smc_gen/r_pincfg/subdir.mk
-include src/smc_gen/general/subdir.mk
-include src/smc_gen/r_bsp/mcu/all/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif 
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif 
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif 
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif 
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif 
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif 
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif 
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif 
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif 
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif 
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif 
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif 
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif 
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif 
endif

ifneq ($(strip $(SRC_UPPER_SRCS)),)
ALL_ASMS += $(SRC_UPPER_SRCS) 
endif
ifneq ($(strip $(SRC_SRCS)),)
ALL_ASMS += $(SRC_SRCS) 
endif
ifneq ($(strip $(S_UPPER_SRCS)),)
ALL_ASMS += $(S_UPPER_SRCS) 
endif
ifneq ($(strip $(S_SRCS)),)
ALL_ASMS += $(S_SRCS) 
endif


-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables
LINKER_OUTPUT_OUTPUTS += \
frtost.abs \
frtost.x

LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS += \
frtost.lib

OBJS := \
$(COMPILER_OBJS) \
$(INDIVIDUAL_COMPILER_OBJS) \
$(ASSEMBLER_OBJS) \
$(CUSTOM_OBJS)

# All Target
all: $(LINKER_OUTPUT_OUTPUTS) 
	@echo 'Build complete.'

frtost.abs: $(OBJS)  $(ALL_ASMS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) 
	@echo 'Invoking: Linker'
	@echo 'Building target:'
	@echo Linkerfrtost.tmp=
	@sed -e "s/^/    /" "Linkerfrtost.tmp"
	rlink -subcommand="Linkerfrtost.tmp"
	@echo 'Finished building target:'
	@echo.


frtost.lib: 
	@echo 'Invoking: Library Generator'
	@echo LibraryGeneratorfrtost.tmp=
	@sed -e "s/^/    /" "LibraryGeneratorfrtost.tmp"
	lbgrx -subcommand="LibraryGeneratorfrtost.tmp"
	@echo 'Finished building:'
	@echo.

frtost.x: frtost.abs
		-C:\Renesas\e2_studio\eclipse\/../\Utilities\\ccrx\renesas_cc_converter.exe frtost.abs frtost.x

# Other Targets
clean:
	-$(RM) $(LINKER_OUTPUT_OUTPUTS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS)
	-rm -rf src/*.obj src/*.d src/*.asm src/*.p src/*.src src/*.jmp src/*.lst src/*.prn 
	-rm -rf FreeRTOS/*.obj FreeRTOS/*.d FreeRTOS/*.asm FreeRTOS/*.p FreeRTOS/*.src FreeRTOS/*.jmp FreeRTOS/*.lst FreeRTOS/*.prn 
	-rm -rf src/smc_gen/r_bsp/board/generic_rx65n/*.obj src/smc_gen/r_bsp/board/generic_rx65n/*.d src/smc_gen/r_bsp/board/generic_rx65n/*.asm src/smc_gen/r_bsp/board/generic_rx65n/*.p src/smc_gen/r_bsp/board/generic_rx65n/*.src src/smc_gen/r_bsp/board/generic_rx65n/*.jmp src/smc_gen/r_bsp/board/generic_rx65n/*.lst src/smc_gen/r_bsp/board/generic_rx65n/*.prn 
	-rm -rf src/smc_gen/r_bsp/mcu/rx65n/*.obj src/smc_gen/r_bsp/mcu/rx65n/*.d src/smc_gen/r_bsp/mcu/rx65n/*.asm src/smc_gen/r_bsp/mcu/rx65n/*.p src/smc_gen/r_bsp/mcu/rx65n/*.src src/smc_gen/r_bsp/mcu/rx65n/*.jmp src/smc_gen/r_bsp/mcu/rx65n/*.lst src/smc_gen/r_bsp/mcu/rx65n/*.prn 
	-rm -rf FreeRTOS/portable/*.obj FreeRTOS/portable/*.d FreeRTOS/portable/*.asm FreeRTOS/portable/*.p FreeRTOS/portable/*.src FreeRTOS/portable/*.jmp FreeRTOS/portable/*.lst FreeRTOS/portable/*.prn 
	-rm -rf src/smc_gen/r_pincfg/*.obj src/smc_gen/r_pincfg/*.d src/smc_gen/r_pincfg/*.asm src/smc_gen/r_pincfg/*.p src/smc_gen/r_pincfg/*.src src/smc_gen/r_pincfg/*.jmp src/smc_gen/r_pincfg/*.lst src/smc_gen/r_pincfg/*.prn 
	-rm -rf src/smc_gen/general/*.obj src/smc_gen/general/*.d src/smc_gen/general/*.asm src/smc_gen/general/*.p src/smc_gen/general/*.src src/smc_gen/general/*.jmp src/smc_gen/general/*.lst src/smc_gen/general/*.prn 
	-rm -rf src/smc_gen/r_bsp/mcu/all/*.obj src/smc_gen/r_bsp/mcu/all/*.d src/smc_gen/r_bsp/mcu/all/*.asm src/smc_gen/r_bsp/mcu/all/*.p src/smc_gen/r_bsp/mcu/all/*.src src/smc_gen/r_bsp/mcu/all/*.jmp src/smc_gen/r_bsp/mcu/all/*.lst src/smc_gen/r_bsp/mcu/all/*.prn 
	@echo
	@echo 'Clean complete.'

.PHONY: all clean 
-include ../makefile.targets