################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/dialog_colour_chooser.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/dialog_date_chooser.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/dialog_file_chooser.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/dialog_number_entry.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/dialog_one_button.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/dialog_text_entry.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/dialog_time_chooser.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/dialog_two_button.c 

COMPILER_OBJS += \
MiniWin/dialogs/dialog_colour_chooser.obj \
MiniWin/dialogs/dialog_date_chooser.obj \
MiniWin/dialogs/dialog_file_chooser.obj \
MiniWin/dialogs/dialog_number_entry.obj \
MiniWin/dialogs/dialog_one_button.obj \
MiniWin/dialogs/dialog_text_entry.obj \
MiniWin/dialogs/dialog_time_chooser.obj \
MiniWin/dialogs/dialog_two_button.obj 

C_DEPS += \
MiniWin/dialogs/dialog_colour_chooser.d \
MiniWin/dialogs/dialog_date_chooser.d \
MiniWin/dialogs/dialog_file_chooser.d \
MiniWin/dialogs/dialog_number_entry.d \
MiniWin/dialogs/dialog_one_button.d \
MiniWin/dialogs/dialog_text_entry.d \
MiniWin/dialogs/dialog_time_chooser.d \
MiniWin/dialogs/dialog_two_button.d 

# Each subdirectory must supply rules for building sources it contributes
MiniWin/dialogs/%.obj: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo MiniWin\dialogs\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\dialogs\cDepSubCommand.tmp"
	ccrx -subcommand="MiniWin\dialogs\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo MiniWin\dialogs\cSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\dialogs\cSubCommand.tmp"
	ccrx -subcommand="MiniWin\dialogs\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

