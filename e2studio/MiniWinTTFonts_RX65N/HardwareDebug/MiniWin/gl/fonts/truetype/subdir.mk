################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/truetype/BLKCHCRY16.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/truetype/dejavu_sans_12.c 

COMPILER_OBJS += \
MiniWin/gl/fonts/truetype/BLKCHCRY16.obj \
MiniWin/gl/fonts/truetype/BLKCHCRY16bw.obj \
MiniWin/gl/fonts/truetype/dejavu_sans_12.obj 

C_DEPS += \
MiniWin/gl/fonts/truetype/BLKCHCRY16.d \
MiniWin/gl/fonts/truetype/BLKCHCRY16bw.d \
MiniWin/gl/fonts/truetype/dejavu_sans_12.d 

# Each subdirectory must supply rules for building sources it contributes
MiniWin/gl/fonts/truetype/%.obj: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/truetype/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo MiniWin\gl\fonts\truetype\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\gl\fonts\truetype\cDepSubCommand.tmp"
	ccrx -subcommand="MiniWin\gl\fonts\truetype\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo MiniWin\gl\fonts\truetype\cSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\gl\fonts\truetype\cSubCommand.tmp"
	ccrx -subcommand="MiniWin\gl\fonts\truetype\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

