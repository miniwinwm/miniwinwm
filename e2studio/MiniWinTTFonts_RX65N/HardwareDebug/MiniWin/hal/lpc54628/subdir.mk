################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/lpc54628/hal_delay.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/lpc54628/hal_lcd.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/lpc54628/hal_non_vol.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/lpc54628/hal_timer.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/lpc54628/hal_touch.c 

COMPILER_OBJS += \
MiniWin/hal/lpc54628/hal_delay.obj \
MiniWin/hal/lpc54628/hal_lcd.obj \
MiniWin/hal/lpc54628/hal_non_vol.obj \
MiniWin/hal/lpc54628/hal_timer.obj \
MiniWin/hal/lpc54628/hal_touch.obj 

C_DEPS += \
MiniWin/hal/lpc54628/hal_delay.d \
MiniWin/hal/lpc54628/hal_lcd.d \
MiniWin/hal/lpc54628/hal_non_vol.d \
MiniWin/hal/lpc54628/hal_timer.d \
MiniWin/hal/lpc54628/hal_touch.d 

# Each subdirectory must supply rules for building sources it contributes
MiniWin/hal/lpc54628/%.obj: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/lpc54628/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo MiniWin\hal\lpc54628\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\hal\lpc54628\cDepSubCommand.tmp"
	ccrx -subcommand="MiniWin\hal\lpc54628\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo MiniWin\hal\lpc54628\cSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\hal\lpc54628\cSubCommand.tmp"
	ccrx -subcommand="MiniWin\hal\lpc54628\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

