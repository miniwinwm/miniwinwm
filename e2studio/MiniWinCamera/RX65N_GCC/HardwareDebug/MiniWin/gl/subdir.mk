################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/gl.c 

C_DEPS += \
./MiniWin/gl/gl.d 

OBJS += \
./MiniWin/gl/gl.o 


# Each subdirectory must supply rules for building sources it contributes
MiniWin/gl/gl.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/gl/gl.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '


