################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_bsp/board/generic_rx65n/dbsct.c \
../src/smc_gen/r_bsp/board/generic_rx65n/hwsetup.c \
../src/smc_gen/r_bsp/board/generic_rx65n/lowlvl.c \
../src/smc_gen/r_bsp/board/generic_rx65n/lowsrc.c \
../src/smc_gen/r_bsp/board/generic_rx65n/resetprg.c \
../src/smc_gen/r_bsp/board/generic_rx65n/sbrk.c \
../src/smc_gen/r_bsp/board/generic_rx65n/vecttbl.c 

COMPILER_OBJS += \
src/smc_gen/r_bsp/board/generic_rx65n/dbsct.obj \
src/smc_gen/r_bsp/board/generic_rx65n/hwsetup.obj \
src/smc_gen/r_bsp/board/generic_rx65n/lowlvl.obj \
src/smc_gen/r_bsp/board/generic_rx65n/lowsrc.obj \
src/smc_gen/r_bsp/board/generic_rx65n/resetprg.obj \
src/smc_gen/r_bsp/board/generic_rx65n/sbrk.obj \
src/smc_gen/r_bsp/board/generic_rx65n/vecttbl.obj 

C_DEPS += \
src/smc_gen/r_bsp/board/generic_rx65n/dbsct.d \
src/smc_gen/r_bsp/board/generic_rx65n/hwsetup.d \
src/smc_gen/r_bsp/board/generic_rx65n/lowlvl.d \
src/smc_gen/r_bsp/board/generic_rx65n/lowsrc.d \
src/smc_gen/r_bsp/board/generic_rx65n/resetprg.d \
src/smc_gen/r_bsp/board/generic_rx65n/sbrk.d \
src/smc_gen/r_bsp/board/generic_rx65n/vecttbl.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_bsp/board/generic_rx65n/%.obj: ../src/smc_gen/r_bsp/board/generic_rx65n/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_bsp\board\generic_rx65n\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\board\generic_rx65n\cDepSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_bsp\board\generic_rx65n\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo src\smc_gen\r_bsp\board\generic_rx65n\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\board\generic_rx65n\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_bsp\board\generic_rx65n\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

