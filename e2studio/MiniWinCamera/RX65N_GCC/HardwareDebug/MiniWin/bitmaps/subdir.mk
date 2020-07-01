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
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/folder_close_icon_large.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/folder_close_icon_small.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/folder_icon_large.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/folder_icon_small.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/folder_open_icon_large.c \
C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/folder_open_icon_small.c \
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

C_DEPS += \
./MiniWin/bitmaps/backspace_key.d \
./MiniWin/bitmaps/close_icon.d \
./MiniWin/bitmaps/close_icon_large.d \
./MiniWin/bitmaps/file_icon_large.d \
./MiniWin/bitmaps/file_icon_small.d \
./MiniWin/bitmaps/folder_close_icon_large.d \
./MiniWin/bitmaps/folder_close_icon_small.d \
./MiniWin/bitmaps/folder_icon_large.d \
./MiniWin/bitmaps/folder_icon_small.d \
./MiniWin/bitmaps/folder_open_icon_large.d \
./MiniWin/bitmaps/folder_open_icon_small.d \
./MiniWin/bitmaps/let_key.d \
./MiniWin/bitmaps/maximise_icon.d \
./MiniWin/bitmaps/maximise_icon_large.d \
./MiniWin/bitmaps/minimise_icon.d \
./MiniWin/bitmaps/minimise_icon_large.d \
./MiniWin/bitmaps/num_key.d \
./MiniWin/bitmaps/resize_icon.d \
./MiniWin/bitmaps/resize_icon_large.d \
./MiniWin/bitmaps/shift_key.d \
./MiniWin/bitmaps/sym_key.d \
./MiniWin/bitmaps/tick.d \
./MiniWin/bitmaps/tick_large.d 

OBJS += \
./MiniWin/bitmaps/backspace_key.o \
./MiniWin/bitmaps/close_icon.o \
./MiniWin/bitmaps/close_icon_large.o \
./MiniWin/bitmaps/file_icon_large.o \
./MiniWin/bitmaps/file_icon_small.o \
./MiniWin/bitmaps/folder_close_icon_large.o \
./MiniWin/bitmaps/folder_close_icon_small.o \
./MiniWin/bitmaps/folder_icon_large.o \
./MiniWin/bitmaps/folder_icon_small.o \
./MiniWin/bitmaps/folder_open_icon_large.o \
./MiniWin/bitmaps/folder_open_icon_small.o \
./MiniWin/bitmaps/let_key.o \
./MiniWin/bitmaps/maximise_icon.o \
./MiniWin/bitmaps/maximise_icon_large.o \
./MiniWin/bitmaps/minimise_icon.o \
./MiniWin/bitmaps/minimise_icon_large.o \
./MiniWin/bitmaps/num_key.o \
./MiniWin/bitmaps/resize_icon.o \
./MiniWin/bitmaps/resize_icon_large.o \
./MiniWin/bitmaps/shift_key.o \
./MiniWin/bitmaps/sym_key.o \
./MiniWin/bitmaps/tick.o \
./MiniWin/bitmaps/tick_large.o 


# Each subdirectory must supply rules for building sources it contributes
MiniWin/bitmaps/backspace_key.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/backspace_key.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/close_icon.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/close_icon.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/close_icon_large.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/close_icon_large.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/file_icon_large.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/file_icon_large.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/file_icon_small.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/file_icon_small.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/folder_close_icon_large.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/folder_close_icon_large.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/folder_close_icon_small.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/folder_close_icon_small.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/folder_icon_large.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/folder_icon_large.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/folder_icon_small.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/folder_icon_small.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/folder_open_icon_large.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/folder_open_icon_large.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/folder_open_icon_small.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/folder_open_icon_small.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/let_key.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/let_key.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/maximise_icon.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/maximise_icon.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/maximise_icon_large.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/maximise_icon_large.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/minimise_icon.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/minimise_icon.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/minimise_icon_large.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/minimise_icon_large.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/num_key.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/num_key.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/resize_icon.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/resize_icon.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/resize_icon_large.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/resize_icon_large.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/shift_key.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/shift_key.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/sym_key.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/sym_key.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/tick.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/tick.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '

MiniWin/bitmaps/tick_large.o: C:/Users/John/Desktop/workspace/miniwinwm/MiniWin/bitmaps/tick_large.c
	@echo 'Building file: $<'
	@echo 'Invoking Compiler'
	$(file > $@.in,-O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@")
	@echo 'rx-elf-gcc -O0 -ffunction-sections -fdata-sections -g2 -Wstack-usage=1000 -m64bit-doubles -mcpu=rx64m -misa=v2 -mlittle-endian-data -std=c99 -I"C:/Users/John/Desktop/workspace/miniwinwm/e2studio/MiniWinCamera/RX65N_GCC/generate" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWin\\gl\\fonts\\truetype\\mcufont" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\e2studio\\MiniWinCamera\\RX65N_GCC\\src" -I"C:\\Users\\John\\Desktop\\workspace\\miniwinwm\\MiniWinCamera_Common" -DRX65N_GCC -Wa,-adlnh="$(basename $(notdir $<)).lst" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" "$<" -c -o "$@"'

	rx-elf-gcc @"$@.in"
	@echo 'Finished building: $<'
	@echo ' '


