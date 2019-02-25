################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/windows/hal_delay.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/windows/hal_lcd.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/windows/hal_non_vol.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/windows/hal_timer.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/windows/hal_touch.c 

COMPILER_OBJS += \
MiniWin/hal/windows/hal_delay.obj \
MiniWin/hal/windows/hal_lcd.obj \
MiniWin/hal/windows/hal_non_vol.obj \
MiniWin/hal/windows/hal_timer.obj \
MiniWin/hal/windows/hal_touch.obj 

C_DEPS += \
MiniWin/hal/windows/hal_delay.d \
MiniWin/hal/windows/hal_lcd.d \
MiniWin/hal/windows/hal_non_vol.d \
MiniWin/hal/windows/hal_timer.d \
MiniWin/hal/windows/hal_touch.d 

# Each subdirectory must supply rules for building sources it contributes
MiniWin/hal/windows/%.obj: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/windows/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo MiniWin\hal\windows\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\hal\windows\cDepSubCommand.tmp"
	ccrx -subcommand="MiniWin\hal\windows\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo MiniWin\hal\windows\cSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\hal\windows\cSubCommand.tmp"
	ccrx -subcommand="MiniWin\hal\windows\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

