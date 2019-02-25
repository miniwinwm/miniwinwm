################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/stm32f407/hal_delay.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/stm32f407/hal_lcd.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/stm32f407/hal_non_vol.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/stm32f407/hal_timer.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/stm32f407/hal_touch.c 

COMPILER_OBJS += \
MiniWin/hal/stm32f407/hal_delay.obj \
MiniWin/hal/stm32f407/hal_lcd.obj \
MiniWin/hal/stm32f407/hal_non_vol.obj \
MiniWin/hal/stm32f407/hal_timer.obj \
MiniWin/hal/stm32f407/hal_touch.obj 

C_DEPS += \
MiniWin/hal/stm32f407/hal_delay.d \
MiniWin/hal/stm32f407/hal_lcd.d \
MiniWin/hal/stm32f407/hal_non_vol.d \
MiniWin/hal/stm32f407/hal_timer.d \
MiniWin/hal/stm32f407/hal_touch.d 

# Each subdirectory must supply rules for building sources it contributes
MiniWin/hal/stm32f407/%.obj: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/stm32f407/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo MiniWin\hal\stm32f407\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\hal\stm32f407\cDepSubCommand.tmp"
	ccrx -subcommand="MiniWin\hal\stm32f407\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo MiniWin\hal\stm32f407\cSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\hal\stm32f407\cSubCommand.tmp"
	ccrx -subcommand="MiniWin\hal\stm32f407\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

