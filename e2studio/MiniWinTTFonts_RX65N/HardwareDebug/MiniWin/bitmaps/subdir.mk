################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/backspace_key.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/close_icon.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/close_icon_large.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/file_icon_large.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/file_icon_small.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/folder_icon_large.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/folder_icon_small.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/let_key.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/maximise_icon.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/maximise_icon_large.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/minimise_icon.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/minimise_icon_large.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/num_key.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/resize_icon.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/resize_icon_large.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/shift_key.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/sym_key.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/tick.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/tick_large.c 

COMPILER_OBJS += \
MiniWin/bitmaps/backspace_key.obj \
MiniWin/bitmaps/close_icon.obj \
MiniWin/bitmaps/close_icon_large.obj \
MiniWin/bitmaps/file_icon_large.obj \
MiniWin/bitmaps/file_icon_small.obj \
MiniWin/bitmaps/folder_icon_large.obj \
MiniWin/bitmaps/folder_icon_small.obj \
MiniWin/bitmaps/let_key.obj \
MiniWin/bitmaps/maximise_icon.obj \
MiniWin/bitmaps/maximise_icon_large.obj \
MiniWin/bitmaps/minimise_icon.obj \
MiniWin/bitmaps/minimise_icon_large.obj \
MiniWin/bitmaps/num_key.obj \
MiniWin/bitmaps/resize_icon.obj \
MiniWin/bitmaps/resize_icon_large.obj \
MiniWin/bitmaps/shift_key.obj \
MiniWin/bitmaps/sym_key.obj \
MiniWin/bitmaps/tick.obj \
MiniWin/bitmaps/tick_large.obj 

C_DEPS += \
MiniWin/bitmaps/backspace_key.d \
MiniWin/bitmaps/close_icon.d \
MiniWin/bitmaps/close_icon_large.d \
MiniWin/bitmaps/file_icon_large.d \
MiniWin/bitmaps/file_icon_small.d \
MiniWin/bitmaps/folder_icon_large.d \
MiniWin/bitmaps/folder_icon_small.d \
MiniWin/bitmaps/let_key.d \
MiniWin/bitmaps/maximise_icon.d \
MiniWin/bitmaps/maximise_icon_large.d \
MiniWin/bitmaps/minimise_icon.d \
MiniWin/bitmaps/minimise_icon_large.d \
MiniWin/bitmaps/num_key.d \
MiniWin/bitmaps/resize_icon.d \
MiniWin/bitmaps/resize_icon_large.d \
MiniWin/bitmaps/shift_key.d \
MiniWin/bitmaps/sym_key.d \
MiniWin/bitmaps/tick.d \
MiniWin/bitmaps/tick_large.d 

# Each subdirectory must supply rules for building sources it contributes
MiniWin/bitmaps/%.obj: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo MiniWin\bitmaps\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\bitmaps\cDepSubCommand.tmp"
	ccrx -subcommand="MiniWin\bitmaps\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo MiniWin\bitmaps\cSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\bitmaps\cSubCommand.tmp"
	ccrx -subcommand="MiniWin\bitmaps\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

