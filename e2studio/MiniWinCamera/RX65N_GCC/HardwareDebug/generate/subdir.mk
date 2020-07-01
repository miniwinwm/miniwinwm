################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LINKER_SCRIPT += \
../generate/linker_script.ld 

S_UPPER_SRCS += \
../generate/start.S 

C_SRCS += \
../generate/hwinit.c \
../generate/inthandler.c \
../generate/vects.c 

C_DEPS += \
./generate/hwinit.d \
./generate/inthandler.d \
./generate/vects.d 

OBJS += \
./generate/hwinit.o \
./generate/inthandler.o \
./generate/start.o \
./generate/vects.o 

S_UPPER_DEPS += \
./generate/start.d 


# Each subdirectory must supply rules for building sources it contributes
generate/%.o: ../generate/%.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

generate/%.o: ../generate/%.S
	@echo 'Building file: $<'
	@echo 'Invoking Assembler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -x assembler-with-cpp -Wa,--gdwarf2 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/src" -Wa,-adlhn="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c "$<" -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -x assembler-with-cpp -Wa,--gdwarf2 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/src" -Wa,-adlhn="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c "$<" -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '


