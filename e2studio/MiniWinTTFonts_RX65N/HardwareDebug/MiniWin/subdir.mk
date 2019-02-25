################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/calibrate.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/miniwin.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/miniwin_debug.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/miniwin_message_queue.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/miniwin_settings.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/miniwin_touch.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/miniwin_utilities.c 

COMPILER_OBJS += \
MiniWin/calibrate.obj \
MiniWin/miniwin.obj \
MiniWin/miniwin_debug.obj \
MiniWin/miniwin_message_queue.obj \
MiniWin/miniwin_settings.obj \
MiniWin/miniwin_touch.obj \
MiniWin/miniwin_utilities.obj 

C_DEPS += \
MiniWin/calibrate.d \
MiniWin/miniwin.d \
MiniWin/miniwin_debug.d \
MiniWin/miniwin_message_queue.d \
MiniWin/miniwin_settings.d \
MiniWin/miniwin_touch.d \
MiniWin/miniwin_utilities.d 

# Each subdirectory must supply rules for building sources it contributes
MiniWin/%.obj: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo MiniWin\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\cDepSubCommand.tmp"
	ccrx -subcommand="MiniWin\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo MiniWin\cSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\cSubCommand.tmp"
	ccrx -subcommand="MiniWin\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

