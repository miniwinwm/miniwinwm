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

C_DEPS += \
./MiniWin/dialogs/dialog_colour_chooser.d \
./MiniWin/dialogs/dialog_date_chooser.d \
./MiniWin/dialogs/dialog_file_chooser.d \
./MiniWin/dialogs/dialog_number_entry.d \
./MiniWin/dialogs/dialog_one_button.d \
./MiniWin/dialogs/dialog_text_entry.d \
./MiniWin/dialogs/dialog_time_chooser.d \
./MiniWin/dialogs/dialog_two_button.d 

OBJS += \
./MiniWin/dialogs/dialog_colour_chooser.o \
./MiniWin/dialogs/dialog_date_chooser.o \
./MiniWin/dialogs/dialog_file_chooser.o \
./MiniWin/dialogs/dialog_number_entry.o \
./MiniWin/dialogs/dialog_one_button.o \
./MiniWin/dialogs/dialog_text_entry.o \
./MiniWin/dialogs/dialog_time_chooser.o \
./MiniWin/dialogs/dialog_two_button.o 


# Each subdirectory must supply rules for building sources it contributes
MiniWin/dialogs/dialog_colour_chooser.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/dialog_colour_chooser.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/dialogs/dialog_date_chooser.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/dialog_date_chooser.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/dialogs/dialog_file_chooser.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/dialog_file_chooser.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/dialogs/dialog_number_entry.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/dialog_number_entry.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/dialogs/dialog_one_button.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/dialog_one_button.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/dialogs/dialog_text_entry.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/dialog_text_entry.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/dialogs/dialog_time_chooser.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/dialog_time_chooser.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/dialogs/dialog_two_button.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/dialogs/dialog_two_button.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '


