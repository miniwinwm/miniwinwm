################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/gl.c 

COMPILER_OBJS += \
MiniWin/gl/gl.obj 

C_DEPS += \
MiniWin/gl/gl.d 

# Each subdirectory must supply rules for building sources it contributes
MiniWin/gl/%.obj: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo MiniWin\gl\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\gl\cDepSubCommand.tmp"
	ccrx -subcommand="MiniWin\gl\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo MiniWin\gl\cSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\gl\cSubCommand.tmp"
	ccrx -subcommand="MiniWin\gl\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

