################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/linux/hal_delay.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/linux/hal_lcd.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/linux/hal_non_vol.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/linux/hal_timer.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/linux/hal_touch.c 

COMPILER_OBJS += \
MiniWin/hal/linux/hal_delay.obj \
MiniWin/hal/linux/hal_lcd.obj \
MiniWin/hal/linux/hal_non_vol.obj \
MiniWin/hal/linux/hal_timer.obj \
MiniWin/hal/linux/hal_touch.obj 

C_DEPS += \
MiniWin/hal/linux/hal_delay.d \
MiniWin/hal/linux/hal_lcd.d \
MiniWin/hal/linux/hal_non_vol.d \
MiniWin/hal/linux/hal_timer.d \
MiniWin/hal/linux/hal_touch.d 

# Each subdirectory must supply rules for building sources it contributes
MiniWin/hal/linux/%.obj: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/linux/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo MiniWin\hal\linux\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\hal\linux\cDepSubCommand.tmp"
	ccrx -subcommand="MiniWin\hal\linux\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo MiniWin\hal\linux\cSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\hal\linux\cSubCommand.tmp"
	ccrx -subcommand="MiniWin\hal\linux\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

