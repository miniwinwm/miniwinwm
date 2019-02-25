################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/bitmapped/font12.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/bitmapped/font16.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/bitmapped/font20.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/bitmapped/font24.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/bitmapped/font9.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/bitmapped/gl_title_font.c 

COMPILER_OBJS += \
MiniWin/gl/fonts/bitmapped/font12.obj \
MiniWin/gl/fonts/bitmapped/font16.obj \
MiniWin/gl/fonts/bitmapped/font20.obj \
MiniWin/gl/fonts/bitmapped/font24.obj \
MiniWin/gl/fonts/bitmapped/font9.obj \
MiniWin/gl/fonts/bitmapped/gl_title_font.obj 

C_DEPS += \
MiniWin/gl/fonts/bitmapped/font12.d \
MiniWin/gl/fonts/bitmapped/font16.d \
MiniWin/gl/fonts/bitmapped/font20.d \
MiniWin/gl/fonts/bitmapped/font24.d \
MiniWin/gl/fonts/bitmapped/font9.d \
MiniWin/gl/fonts/bitmapped/gl_title_font.d 

# Each subdirectory must supply rules for building sources it contributes
MiniWin/gl/fonts/bitmapped/%.obj: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/fonts/bitmapped/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo MiniWin\gl\fonts\bitmapped\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\gl\fonts\bitmapped\cDepSubCommand.tmp"
	ccrx -subcommand="MiniWin\gl\fonts\bitmapped\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo MiniWin\gl\fonts\bitmapped\cSubCommand.tmp=
	@sed -e "s/^/ /" "MiniWin\gl\fonts\bitmapped\cSubCommand.tmp"
	ccrx -subcommand="MiniWin\gl\fonts\bitmapped\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

