################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_glcdc_rx/src/targets/rx65n/r_glcdc_rx65n.c 

COMPILER_OBJS += \
src/smc_gen/r_glcdc_rx/src/targets/rx65n/r_glcdc_rx65n.obj 

C_DEPS += \
src/smc_gen/r_glcdc_rx/src/targets/rx65n/r_glcdc_rx65n.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_glcdc_rx/src/targets/rx65n/%.obj: ../src/smc_gen/r_glcdc_rx/src/targets/rx65n/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_glcdc_rx\src\targets\rx65n\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_glcdc_rx\src\targets\rx65n\cDepSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_glcdc_rx\src\targets\rx65n\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo src\smc_gen\r_glcdc_rx\src\targets\rx65n\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_glcdc_rx\src\targets\rx65n\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_glcdc_rx\src\targets\rx65n\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

