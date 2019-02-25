################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/general/r_cg_hardware_setup.c \
../src/smc_gen/general/r_smc_cgc.c \
../src/smc_gen/general/r_smc_cgc_user.c \
../src/smc_gen/general/r_smc_interrupt.c 

COMPILER_OBJS += \
src/smc_gen/general/r_cg_hardware_setup.obj \
src/smc_gen/general/r_smc_cgc.obj \
src/smc_gen/general/r_smc_cgc_user.obj \
src/smc_gen/general/r_smc_interrupt.obj 

C_DEPS += \
src/smc_gen/general/r_cg_hardware_setup.d \
src/smc_gen/general/r_smc_cgc.d \
src/smc_gen/general/r_smc_cgc_user.d \
src/smc_gen/general/r_smc_interrupt.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/general/%.obj: ../src/smc_gen/general/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\general\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\general\cDepSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\general\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo src\smc_gen\general\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\general\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\general\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

