################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../FreeRTOS/croutine.c \
../FreeRTOS/event_groups.c \
../FreeRTOS/list.c \
../FreeRTOS/queue.c \
../FreeRTOS/stream_buffer.c \
../FreeRTOS/tasks.c \
../FreeRTOS/timers.c 

COMPILER_OBJS += \
FreeRTOS/croutine.obj \
FreeRTOS/event_groups.obj \
FreeRTOS/list.obj \
FreeRTOS/queue.obj \
FreeRTOS/stream_buffer.obj \
FreeRTOS/tasks.obj \
FreeRTOS/timers.obj 

C_DEPS += \
FreeRTOS/croutine.d \
FreeRTOS/event_groups.d \
FreeRTOS/list.d \
FreeRTOS/queue.d \
FreeRTOS/stream_buffer.d \
FreeRTOS/tasks.d \
FreeRTOS/timers.d 

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/%.obj: ../FreeRTOS/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo FreeRTOS\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "FreeRTOS\cDepSubCommand.tmp"
	ccrx -subcommand="FreeRTOS\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo FreeRTOS\cSubCommand.tmp=
	@sed -e "s/^/ /" "FreeRTOS\cSubCommand.tmp"
	ccrx -subcommand="FreeRTOS\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

