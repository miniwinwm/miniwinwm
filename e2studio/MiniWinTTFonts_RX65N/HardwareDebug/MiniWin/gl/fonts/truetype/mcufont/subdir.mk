################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/truetype/mcufont/mf_font.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/truetype/mcufont/mf_justify.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c 

COMPILER_OBJS += \
MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.obj \
MiniWin/gl/fonts/truetype/mcufont/mf_encoding.obj \
MiniWin/gl/fonts/truetype/mcufont/mf_font.obj \
MiniWin/gl/fonts/truetype/mcufont/mf_justify.obj \
MiniWin/gl/fonts/truetype/mcufont/mf_kerning.obj \
MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.obj \
MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.obj \
MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.obj 

C_DEPS += \
MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.d \
MiniWin/gl/fonts/truetype/mcufont/mf_encoding.d \
MiniWin/gl/fonts/truetype/mcufont/mf_font.d \
MiniWin/gl/fonts/truetype/mcufont/mf_justify.d \
MiniWin/gl/fonts/truetype/mcufont/mf_kerning.d \
MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.d \
MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.d \
MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.d 

# Each subdirectory must supply rules for building sources it contributes
MiniWin/gl/fonts/truetype/mcufont/%.obj: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/truetype/mcufont/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo MiniWin\gl\fonts\truetype\mcufont\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\gl\fonts\truetype\mcufont\cDepSubCommand.tmp"
	ccrx -subcommand="MiniWin\gl\fonts\truetype\mcufont\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo MiniWin\gl\fonts\truetype\mcufont\cSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\gl\fonts\truetype\mcufont\cSubCommand.tmp"
	ccrx -subcommand="MiniWin\gl\fonts\truetype\mcufont\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

