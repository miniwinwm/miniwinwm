################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_bsp/mcu/all/r_bsp_common.c 

COMPILER_OBJS += \
src/smc_gen/r_bsp/mcu/all/r_bsp_common.obj 

C_DEPS += \
src/smc_gen/r_bsp/mcu/all/r_bsp_common.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_bsp/mcu/all/%.obj: ../src/smc_gen/r_bsp/mcu/all/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_bsp\mcu\all\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\mcu\all\cDepSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_bsp\mcu\all\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo src\smc_gen\r_bsp\mcu\all\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\mcu\all\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_bsp\mcu\all\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

