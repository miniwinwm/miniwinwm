################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/rx65n/hal_delay.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/rx65n/hal_lcd.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/rx65n/hal_non_vol.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/rx65n/hal_timer.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/rx65n/hal_touch.c 

COMPILER_OBJS += \
MiniWin/hal/rx65n/hal_delay.obj \
MiniWin/hal/rx65n/hal_lcd.obj \
MiniWin/hal/rx65n/hal_non_vol.obj \
MiniWin/hal/rx65n/hal_timer.obj \
MiniWin/hal/rx65n/hal_touch.obj 

C_DEPS += \
MiniWin/hal/rx65n/hal_delay.d \
MiniWin/hal/rx65n/hal_lcd.d \
MiniWin/hal/rx65n/hal_non_vol.d \
MiniWin/hal/rx65n/hal_timer.d \
MiniWin/hal/rx65n/hal_touch.d 

# Each subdirectory must supply rules for building sources it contributes
MiniWin/hal/rx65n/%.obj: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/rx65n/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo MiniWin\hal\rx65n\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\hal\rx65n\cDepSubCommand.tmp"
	ccrx -subcommand="MiniWin\hal\rx65n\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo MiniWin\hal\rx65n\cSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\hal\rx65n\cSubCommand.tmp"
	ccrx -subcommand="MiniWin\hal\rx65n\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

