################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_flash_rx/src/flash_type_4/r_flash_type4.c 

COMPILER_OBJS += \
src/smc_gen/r_flash_rx/src/flash_type_4/r_flash_type4.obj 

C_DEPS += \
src/smc_gen/r_flash_rx/src/flash_type_4/r_flash_type4.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_flash_rx/src/flash_type_4/%.obj: ../src/smc_gen/r_flash_rx/src/flash_type_4/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_flash_rx\src\flash_type_4\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_flash_rx\src\flash_type_4\cDepSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_flash_rx\src\flash_type_4\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo src\smc_gen\r_flash_rx\src\flash_type_4\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_flash_rx\src\flash_type_4\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_flash_rx\src\flash_type_4\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

