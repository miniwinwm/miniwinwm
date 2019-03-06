################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../FreeRTOS/portable/port.c 

SRC_SRCS += \
../FreeRTOS/portable/port_asm.src 

SRC_DEPS += \
FreeRTOS/portable/port_asm.d 

ASSEMBLER_OBJS += \
FreeRTOS/portable/port_asm.obj 

COMPILER_OBJS += \
FreeRTOS/portable/port.obj 

C_DEPS += \
FreeRTOS/portable/port.d 

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/%.obj: ../FreeRTOS/portable/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo FreeRTOS\portable\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "FreeRTOS\portable\cDepSubCommand.tmp"
	ccrx -subcommand="FreeRTOS\portable\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo FreeRTOS\portable\cSubCommand.tmp=
	@sed -e "s/^/ /" "FreeRTOS\portable\cSubCommand.tmp"
	ccrx -subcommand="FreeRTOS\portable\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

FreeRTOS/portable/%.obj: ../FreeRTOS/portable/%.src 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Assembler'
	@echo FreeRTOS\portable\srcDepSubCommand.tmp=
	@sed -e "s/^/ /" "FreeRTOS\portable\srcDepSubCommand.tmp"
	asrx -subcommand="FreeRTOS\portable\srcDepSubCommand.tmp" -MF="$(@:%.obj=%.d)" -MT="$(@:%.d=%.obj)" -MT="$(@:%.obj=%.d)" "$<"
	@echo FreeRTOS\portable\srcSubCommand.tmp=
	@sed -e "s/^/ /" "FreeRTOS\portable\srcSubCommand.tmp"
	asrx -subcommand="FreeRTOS\portable\srcSubCommand.tmp" -output="$(@:%.d=%.obj)" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

