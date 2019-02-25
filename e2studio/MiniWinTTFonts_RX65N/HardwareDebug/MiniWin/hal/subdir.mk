################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/hal_init.c 

COMPILER_OBJS += \
MiniWin/hal/hal_init.obj 

C_DEPS += \
MiniWin/hal/hal_init.d 

# Each subdirectory must supply rules for building sources it contributes
MiniWin/hal/%.obj: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/hal/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo MiniWin\hal\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\hal\cDepSubCommand.tmp"
	ccrx -subcommand="MiniWin\hal\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo MiniWin\hal\cSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\hal\cSubCommand.tmp"
	ccrx -subcommand="MiniWin\hal\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

