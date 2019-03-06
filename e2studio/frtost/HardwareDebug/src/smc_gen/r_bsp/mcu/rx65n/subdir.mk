################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_bsp/mcu/rx65n/cpu.c \
../src/smc_gen/r_bsp/mcu/rx65n/locking.c \
../src/smc_gen/r_bsp/mcu/rx65n/mcu_clocks.c \
../src/smc_gen/r_bsp/mcu/rx65n/mcu_init.c \
../src/smc_gen/r_bsp/mcu/rx65n/mcu_interrupts.c \
../src/smc_gen/r_bsp/mcu/rx65n/mcu_locks.c \
../src/smc_gen/r_bsp/mcu/rx65n/mcu_mapped_interrupts.c \
../src/smc_gen/r_bsp/mcu/rx65n/mcu_startup.c 

COMPILER_OBJS += \
src/smc_gen/r_bsp/mcu/rx65n/cpu.obj \
src/smc_gen/r_bsp/mcu/rx65n/locking.obj \
src/smc_gen/r_bsp/mcu/rx65n/mcu_clocks.obj \
src/smc_gen/r_bsp/mcu/rx65n/mcu_init.obj \
src/smc_gen/r_bsp/mcu/rx65n/mcu_interrupts.obj \
src/smc_gen/r_bsp/mcu/rx65n/mcu_locks.obj \
src/smc_gen/r_bsp/mcu/rx65n/mcu_mapped_interrupts.obj \
src/smc_gen/r_bsp/mcu/rx65n/mcu_startup.obj 

C_DEPS += \
src/smc_gen/r_bsp/mcu/rx65n/cpu.d \
src/smc_gen/r_bsp/mcu/rx65n/locking.d \
src/smc_gen/r_bsp/mcu/rx65n/mcu_clocks.d \
src/smc_gen/r_bsp/mcu/rx65n/mcu_init.d \
src/smc_gen/r_bsp/mcu/rx65n/mcu_interrupts.d \
src/smc_gen/r_bsp/mcu/rx65n/mcu_locks.d \
src/smc_gen/r_bsp/mcu/rx65n/mcu_mapped_interrupts.d \
src/smc_gen/r_bsp/mcu/rx65n/mcu_startup.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_bsp/mcu/rx65n/%.obj: ../src/smc_gen/r_bsp/mcu/rx65n/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_bsp\mcu\rx65n\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\mcu\rx65n\cDepSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_bsp\mcu\rx65n\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo src\smc_gen\r_bsp\mcu\rx65n\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_bsp\mcu\rx65n\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_bsp\mcu\rx65n\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

