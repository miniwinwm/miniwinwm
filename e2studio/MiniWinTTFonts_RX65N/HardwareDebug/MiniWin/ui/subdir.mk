################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/ui/ui_arrow.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/ui/ui_button.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/ui/ui_check_box.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/ui/ui_common.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/ui/ui_keyboard.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/ui/ui_keypad.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/ui/ui_label.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/ui/ui_list_box.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/ui/ui_progress_bar.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/ui/ui_radio_button.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/ui/ui_scroll_bar_horiz.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/ui/ui_scroll_bar_vert.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/ui/ui_text_box.c 

COMPILER_OBJS += \
MiniWin/ui/ui_arrow.obj \
MiniWin/ui/ui_button.obj \
MiniWin/ui/ui_check_box.obj \
MiniWin/ui/ui_common.obj \
MiniWin/ui/ui_keyboard.obj \
MiniWin/ui/ui_keypad.obj \
MiniWin/ui/ui_label.obj \
MiniWin/ui/ui_list_box.obj \
MiniWin/ui/ui_progress_bar.obj \
MiniWin/ui/ui_radio_button.obj \
MiniWin/ui/ui_scroll_bar_horiz.obj \
MiniWin/ui/ui_scroll_bar_vert.obj \
MiniWin/ui/ui_text_box.obj 

C_DEPS += \
MiniWin/ui/ui_arrow.d \
MiniWin/ui/ui_button.d \
MiniWin/ui/ui_check_box.d \
MiniWin/ui/ui_common.d \
MiniWin/ui/ui_keyboard.d \
MiniWin/ui/ui_keypad.d \
MiniWin/ui/ui_label.d \
MiniWin/ui/ui_list_box.d \
MiniWin/ui/ui_progress_bar.d \
MiniWin/ui/ui_radio_button.d \
MiniWin/ui/ui_scroll_bar_horiz.d \
MiniWin/ui/ui_scroll_bar_vert.d \
MiniWin/ui/ui_text_box.d 

# Each subdirectory must supply rules for building sources it contributes
MiniWin/ui/%.obj: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/ui/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo MiniWin\ui\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\ui\cDepSubCommand.tmp"
	ccrx -subcommand="MiniWin\ui\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo MiniWin\ui\cSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\ui\cSubCommand.tmp"
	ccrx -subcommand="MiniWin\ui\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

