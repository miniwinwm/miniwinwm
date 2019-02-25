################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include makefile.init

RM := rm -rf *.sni *.dbg *.lst *.lis *.lpp *.map *.x *.lbp *.bls *.libelf *.rel *.lbk *.abs  *.obj *.p *.pp *.d *.asm 1st/*.obj 1st/*.d 1st/*.asm 1st/*.abs

# All of the sources participating in the build are defined here
-include sources.mk
-include src/smc_gen/r_bsp/mcu/rx65n/subdir.mk
-include src/smc_gen/r_sci_iic_rx/src/targets/rx65n/subdir.mk
-include MiniWin/gl/fonts/truetype/subdir.mk
-include MiniWinTTFonts_Common/subdir.mk
-include src/smc_gen/r_flash_rx/src/flash_type_1/subdir.mk
-include MiniWin/subdir.mk
-include MiniWin/hal/lpc54628/subdir.mk
-include MiniWin/hal/subdir.mk
-include MiniWin/dialogs/subdir.mk
-include src/smc_gen/r_glcdc_rx/src/targets/rx65n/subdir.mk
-include src/smc_gen/general/subdir.mk
-include MiniWin/gl/subdir.mk
-include MiniWin/hal/windows/subdir.mk
-include src/smc_gen/r_flash_rx/src/subdir.mk
-include MiniWin/bitmaps/subdir.mk
-include src/smc_gen/r_glcdc_rx/src/subdir.mk
-include MiniWin/gl/fonts/bitmapped/subdir.mk
-include MiniWin/hal/rx65n/subdir.mk
-include src/smc_gen/r_flash_rx/src/flash_type_4/subdir.mk
-include src/smc_gen/r_cmt_rx/src/subdir.mk
-include MiniWin/hal/linux/subdir.mk
-include MiniWin/gl/fonts/truetype/mcufont/subdir.mk
-include MiniWin/ui/subdir.mk
-include src/smc_gen/r_sci_iic_rx/src/subdir.mk
-include src/smc_gen/r_flash_rx/src/flash_type_3/subdir.mk
-include src/smc_gen/r_gpio_rx/src/targets/rx65n/subdir.mk
-include MiniWin/hal/stm32f407/subdir.mk
-include MiniWin/hal/stm32f429/subdir.mk
-include src/smc_gen/r_bsp/board/generic_rx65n/subdir.mk
-include src/subdir.mk
-include src/smc_gen/r_gpio_rx/src/subdir.mk
-include src/smc_gen/r_flash_rx/src/flash_type_2/subdir.mk
-include src/smc_gen/r_pincfg/subdir.mk
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
MiniWinTTFonts_RX65N.abs \
MiniWinTTFonts_RX65N.x

LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS += \
MiniWinTTFonts_RX65N.lib

OBJS := \
$(COMPILER_OBJS) \
$(INDIVIDUAL_COMPILER_OBJS) \
$(ASSEMBLER_OBJS) \
$(CUSTOM_OBJS)

# All Target
all: $(LINKER_OUTPUT_OUTPUTS) 
	@echo 'Build complete.'

MiniWinTTFonts_RX65N.abs: $(OBJS)  $(ALL_ASMS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) 
	@echo 'Invoking: Linker'
	@echo 'Building target:'
	@echo LinkerMiniWinTTFonts_RX65N.tmp=
	@sed -e "s/^/    /" "LinkerMiniWinTTFonts_RX65N.tmp"
	rlink -subcommand="LinkerMiniWinTTFonts_RX65N.tmp"
	@echo 'Finished building target:'
	@echo.


MiniWinTTFonts_RX65N.lib: 
	@echo 'Invoking: Library Generator'
	@echo LibraryGeneratorMiniWinTTFonts_RX65N.tmp=
	@sed -e "s/^/    /" "LibraryGeneratorMiniWinTTFonts_RX65N.tmp"
	lbgrx -subcommand="LibraryGeneratorMiniWinTTFonts_RX65N.tmp"
	@echo 'Finished building:'
	@echo.

MiniWinTTFonts_RX65N.x: MiniWinTTFonts_RX65N.abs
		-C:\Renesas\e2_studio\eclipse\/../\Utilities\\ccrx\renesas_cc_converter.exe MiniWinTTFonts_RX65N.abs MiniWinTTFonts_RX65N.x

# Other Targets
clean:
	-$(RM) $(LINKER_OUTPUT_OUTPUTS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS)
	-rm -rf src/smc_gen/r_bsp/mcu/rx65n/*.obj src/smc_gen/r_bsp/mcu/rx65n/*.d src/smc_gen/r_bsp/mcu/rx65n/*.asm src/smc_gen/r_bsp/mcu/rx65n/*.p src/smc_gen/r_bsp/mcu/rx65n/*.src src/smc_gen/r_bsp/mcu/rx65n/*.jmp src/smc_gen/r_bsp/mcu/rx65n/*.lst src/smc_gen/r_bsp/mcu/rx65n/*.prn 
	-rm -rf src/smc_gen/r_sci_iic_rx/src/targets/rx65n/*.obj src/smc_gen/r_sci_iic_rx/src/targets/rx65n/*.d src/smc_gen/r_sci_iic_rx/src/targets/rx65n/*.asm src/smc_gen/r_sci_iic_rx/src/targets/rx65n/*.p src/smc_gen/r_sci_iic_rx/src/targets/rx65n/*.src src/smc_gen/r_sci_iic_rx/src/targets/rx65n/*.jmp src/smc_gen/r_sci_iic_rx/src/targets/rx65n/*.lst src/smc_gen/r_sci_iic_rx/src/targets/rx65n/*.prn 
	-rm -rf MiniWin/gl/fonts/truetype/*.obj MiniWin/gl/fonts/truetype/*.d MiniWin/gl/fonts/truetype/*.asm MiniWin/gl/fonts/truetype/*.p MiniWin/gl/fonts/truetype/*.src MiniWin/gl/fonts/truetype/*.jmp MiniWin/gl/fonts/truetype/*.lst MiniWin/gl/fonts/truetype/*.prn 
	-rm -rf MiniWinTTFonts_Common/*.obj MiniWinTTFonts_Common/*.d MiniWinTTFonts_Common/*.asm MiniWinTTFonts_Common/*.p MiniWinTTFonts_Common/*.src MiniWinTTFonts_Common/*.jmp MiniWinTTFonts_Common/*.lst MiniWinTTFonts_Common/*.prn 
	-rm -rf src/smc_gen/r_flash_rx/src/flash_type_1/*.obj src/smc_gen/r_flash_rx/src/flash_type_1/*.d src/smc_gen/r_flash_rx/src/flash_type_1/*.asm src/smc_gen/r_flash_rx/src/flash_type_1/*.p src/smc_gen/r_flash_rx/src/flash_type_1/*.src src/smc_gen/r_flash_rx/src/flash_type_1/*.jmp src/smc_gen/r_flash_rx/src/flash_type_1/*.lst src/smc_gen/r_flash_rx/src/flash_type_1/*.prn 
	-rm -rf MiniWin/*.obj MiniWin/*.d MiniWin/*.asm MiniWin/*.p MiniWin/*.src MiniWin/*.jmp MiniWin/*.lst MiniWin/*.prn 
	-rm -rf MiniWin/hal/lpc54628/*.obj MiniWin/hal/lpc54628/*.d MiniWin/hal/lpc54628/*.asm MiniWin/hal/lpc54628/*.p MiniWin/hal/lpc54628/*.src MiniWin/hal/lpc54628/*.jmp MiniWin/hal/lpc54628/*.lst MiniWin/hal/lpc54628/*.prn 
	-rm -rf MiniWin/hal/*.obj MiniWin/hal/*.d MiniWin/hal/*.asm MiniWin/hal/*.p MiniWin/hal/*.src MiniWin/hal/*.jmp MiniWin/hal/*.lst MiniWin/hal/*.prn 
	-rm -rf MiniWin/dialogs/*.obj MiniWin/dialogs/*.d MiniWin/dialogs/*.asm MiniWin/dialogs/*.p MiniWin/dialogs/*.src MiniWin/dialogs/*.jmp MiniWin/dialogs/*.lst MiniWin/dialogs/*.prn 
	-rm -rf src/smc_gen/r_glcdc_rx/src/targets/rx65n/*.obj src/smc_gen/r_glcdc_rx/src/targets/rx65n/*.d src/smc_gen/r_glcdc_rx/src/targets/rx65n/*.asm src/smc_gen/r_glcdc_rx/src/targets/rx65n/*.p src/smc_gen/r_glcdc_rx/src/targets/rx65n/*.src src/smc_gen/r_glcdc_rx/src/targets/rx65n/*.jmp src/smc_gen/r_glcdc_rx/src/targets/rx65n/*.lst src/smc_gen/r_glcdc_rx/src/targets/rx65n/*.prn 
	-rm -rf src/smc_gen/general/*.obj src/smc_gen/general/*.d src/smc_gen/general/*.asm src/smc_gen/general/*.p src/smc_gen/general/*.src src/smc_gen/general/*.jmp src/smc_gen/general/*.lst src/smc_gen/general/*.prn 
	-rm -rf MiniWin/gl/*.obj MiniWin/gl/*.d MiniWin/gl/*.asm MiniWin/gl/*.p MiniWin/gl/*.src MiniWin/gl/*.jmp MiniWin/gl/*.lst MiniWin/gl/*.prn 
	-rm -rf MiniWin/hal/windows/*.obj MiniWin/hal/windows/*.d MiniWin/hal/windows/*.asm MiniWin/hal/windows/*.p MiniWin/hal/windows/*.src MiniWin/hal/windows/*.jmp MiniWin/hal/windows/*.lst MiniWin/hal/windows/*.prn 
	-rm -rf src/smc_gen/r_flash_rx/src/*.obj src/smc_gen/r_flash_rx/src/*.d src/smc_gen/r_flash_rx/src/*.asm src/smc_gen/r_flash_rx/src/*.p src/smc_gen/r_flash_rx/src/*.src src/smc_gen/r_flash_rx/src/*.jmp src/smc_gen/r_flash_rx/src/*.lst src/smc_gen/r_flash_rx/src/*.prn 
	-rm -rf MiniWin/bitmaps/*.obj MiniWin/bitmaps/*.d MiniWin/bitmaps/*.asm MiniWin/bitmaps/*.p MiniWin/bitmaps/*.src MiniWin/bitmaps/*.jmp MiniWin/bitmaps/*.lst MiniWin/bitmaps/*.prn 
	-rm -rf src/smc_gen/r_glcdc_rx/src/*.obj src/smc_gen/r_glcdc_rx/src/*.d src/smc_gen/r_glcdc_rx/src/*.asm src/smc_gen/r_glcdc_rx/src/*.p src/smc_gen/r_glcdc_rx/src/*.src src/smc_gen/r_glcdc_rx/src/*.jmp src/smc_gen/r_glcdc_rx/src/*.lst src/smc_gen/r_glcdc_rx/src/*.prn 
	-rm -rf MiniWin/gl/fonts/bitmapped/*.obj MiniWin/gl/fonts/bitmapped/*.d MiniWin/gl/fonts/bitmapped/*.asm MiniWin/gl/fonts/bitmapped/*.p MiniWin/gl/fonts/bitmapped/*.src MiniWin/gl/fonts/bitmapped/*.jmp MiniWin/gl/fonts/bitmapped/*.lst MiniWin/gl/fonts/bitmapped/*.prn 
	-rm -rf MiniWin/hal/rx65n/*.obj MiniWin/hal/rx65n/*.d MiniWin/hal/rx65n/*.asm MiniWin/hal/rx65n/*.p MiniWin/hal/rx65n/*.src MiniWin/hal/rx65n/*.jmp MiniWin/hal/rx65n/*.lst MiniWin/hal/rx65n/*.prn 
	-rm -rf src/smc_gen/r_flash_rx/src/flash_type_4/*.obj src/smc_gen/r_flash_rx/src/flash_type_4/*.d src/smc_gen/r_flash_rx/src/flash_type_4/*.asm src/smc_gen/r_flash_rx/src/flash_type_4/*.p src/smc_gen/r_flash_rx/src/flash_type_4/*.src src/smc_gen/r_flash_rx/src/flash_type_4/*.jmp src/smc_gen/r_flash_rx/src/flash_type_4/*.lst src/smc_gen/r_flash_rx/src/flash_type_4/*.prn 
	-rm -rf src/smc_gen/r_cmt_rx/src/*.obj src/smc_gen/r_cmt_rx/src/*.d src/smc_gen/r_cmt_rx/src/*.asm src/smc_gen/r_cmt_rx/src/*.p src/smc_gen/r_cmt_rx/src/*.src src/smc_gen/r_cmt_rx/src/*.jmp src/smc_gen/r_cmt_rx/src/*.lst src/smc_gen/r_cmt_rx/src/*.prn 
	-rm -rf MiniWin/hal/linux/*.obj MiniWin/hal/linux/*.d MiniWin/hal/linux/*.asm MiniWin/hal/linux/*.p MiniWin/hal/linux/*.src MiniWin/hal/linux/*.jmp MiniWin/hal/linux/*.lst MiniWin/hal/linux/*.prn 
	-rm -rf MiniWin/gl/fonts/truetype/mcufont/*.obj MiniWin/gl/fonts/truetype/mcufont/*.d MiniWin/gl/fonts/truetype/mcufont/*.asm MiniWin/gl/fonts/truetype/mcufont/*.p MiniWin/gl/fonts/truetype/mcufont/*.src MiniWin/gl/fonts/truetype/mcufont/*.jmp MiniWin/gl/fonts/truetype/mcufont/*.lst MiniWin/gl/fonts/truetype/mcufont/*.prn 
	-rm -rf MiniWin/ui/*.obj MiniWin/ui/*.d MiniWin/ui/*.asm MiniWin/ui/*.p MiniWin/ui/*.src MiniWin/ui/*.jmp MiniWin/ui/*.lst MiniWin/ui/*.prn 
	-rm -rf src/smc_gen/r_sci_iic_rx/src/*.obj src/smc_gen/r_sci_iic_rx/src/*.d src/smc_gen/r_sci_iic_rx/src/*.asm src/smc_gen/r_sci_iic_rx/src/*.p src/smc_gen/r_sci_iic_rx/src/*.src src/smc_gen/r_sci_iic_rx/src/*.jmp src/smc_gen/r_sci_iic_rx/src/*.lst src/smc_gen/r_sci_iic_rx/src/*.prn 
	-rm -rf src/smc_gen/r_flash_rx/src/flash_type_3/*.obj src/smc_gen/r_flash_rx/src/flash_type_3/*.d src/smc_gen/r_flash_rx/src/flash_type_3/*.asm src/smc_gen/r_flash_rx/src/flash_type_3/*.p src/smc_gen/r_flash_rx/src/flash_type_3/*.src src/smc_gen/r_flash_rx/src/flash_type_3/*.jmp src/smc_gen/r_flash_rx/src/flash_type_3/*.lst src/smc_gen/r_flash_rx/src/flash_type_3/*.prn 
	-rm -rf src/smc_gen/r_gpio_rx/src/targets/rx65n/*.obj src/smc_gen/r_gpio_rx/src/targets/rx65n/*.d src/smc_gen/r_gpio_rx/src/targets/rx65n/*.asm src/smc_gen/r_gpio_rx/src/targets/rx65n/*.p src/smc_gen/r_gpio_rx/src/targets/rx65n/*.src src/smc_gen/r_gpio_rx/src/targets/rx65n/*.jmp src/smc_gen/r_gpio_rx/src/targets/rx65n/*.lst src/smc_gen/r_gpio_rx/src/targets/rx65n/*.prn 
	-rm -rf MiniWin/hal/stm32f407/*.obj MiniWin/hal/stm32f407/*.d MiniWin/hal/stm32f407/*.asm MiniWin/hal/stm32f407/*.p MiniWin/hal/stm32f407/*.src MiniWin/hal/stm32f407/*.jmp MiniWin/hal/stm32f407/*.lst MiniWin/hal/stm32f407/*.prn 
	-rm -rf MiniWin/hal/stm32f429/*.obj MiniWin/hal/stm32f429/*.d MiniWin/hal/stm32f429/*.asm MiniWin/hal/stm32f429/*.p MiniWin/hal/stm32f429/*.src MiniWin/hal/stm32f429/*.jmp MiniWin/hal/stm32f429/*.lst MiniWin/hal/stm32f429/*.prn 
	-rm -rf src/smc_gen/r_bsp/board/generic_rx65n/*.obj src/smc_gen/r_bsp/board/generic_rx65n/*.d src/smc_gen/r_bsp/board/generic_rx65n/*.asm src/smc_gen/r_bsp/board/generic_rx65n/*.p src/smc_gen/r_bsp/board/generic_rx65n/*.src src/smc_gen/r_bsp/board/generic_rx65n/*.jmp src/smc_gen/r_bsp/board/generic_rx65n/*.lst src/smc_gen/r_bsp/board/generic_rx65n/*.prn 
	-rm -rf src/*.obj src/*.d src/*.asm src/*.p src/*.src src/*.jmp src/*.lst src/*.prn 
	-rm -rf src/smc_gen/r_gpio_rx/src/*.obj src/smc_gen/r_gpio_rx/src/*.d src/smc_gen/r_gpio_rx/src/*.asm src/smc_gen/r_gpio_rx/src/*.p src/smc_gen/r_gpio_rx/src/*.src src/smc_gen/r_gpio_rx/src/*.jmp src/smc_gen/r_gpio_rx/src/*.lst src/smc_gen/r_gpio_rx/src/*.prn 
	-rm -rf src/smc_gen/r_flash_rx/src/flash_type_2/*.obj src/smc_gen/r_flash_rx/src/flash_type_2/*.d src/smc_gen/r_flash_rx/src/flash_type_2/*.asm src/smc_gen/r_flash_rx/src/flash_type_2/*.p src/smc_gen/r_flash_rx/src/flash_type_2/*.src src/smc_gen/r_flash_rx/src/flash_type_2/*.jmp src/smc_gen/r_flash_rx/src/flash_type_2/*.lst src/smc_gen/r_flash_rx/src/flash_type_2/*.prn 
	-rm -rf src/smc_gen/r_pincfg/*.obj src/smc_gen/r_pincfg/*.d src/smc_gen/r_pincfg/*.asm src/smc_gen/r_pincfg/*.p src/smc_gen/r_pincfg/*.src src/smc_gen/r_pincfg/*.jmp src/smc_gen/r_pincfg/*.lst src/smc_gen/r_pincfg/*.prn 
	-rm -rf src/smc_gen/r_bsp/mcu/all/*.obj src/smc_gen/r_bsp/mcu/all/*.d src/smc_gen/r_bsp/mcu/all/*.asm src/smc_gen/r_bsp/mcu/all/*.p src/smc_gen/r_bsp/mcu/all/*.src src/smc_gen/r_bsp/mcu/all/*.jmp src/smc_gen/r_bsp/mcu/all/*.lst src/smc_gen/r_bsp/mcu/all/*.prn 
	@echo
	@echo 'Clean complete.'

.PHONY: all clean 
-include ../makefile.targets