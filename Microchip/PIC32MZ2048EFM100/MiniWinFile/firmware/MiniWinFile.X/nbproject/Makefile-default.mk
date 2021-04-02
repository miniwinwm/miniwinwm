#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MiniWinFile.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MiniWinFile.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/coretimer/plib_coretimer.c ../src/config/default/peripheral/evic/plib_evic.c ../src/config/default/peripheral/gpio/plib_gpio.c ../src/config/default/peripheral/nvm/plib_nvm.c ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c ../src/config/default/peripheral/spi/spi_master/plib_spi1_master.c ../src/config/default/peripheral/tmr/plib_tmr2.c ../src/config/default/peripheral/tmr/plib_tmr3.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../../FatFS/ff.c ../../FatFS/sdmm.c ../../FatFS/spi_driver.c ../../../../../MiniWin/bitmaps/backspace_key.c ../../../../../MiniWin/bitmaps/close_icon.c ../../../../../MiniWin/bitmaps/close_icon_large.c ../../../../../MiniWin/bitmaps/file_icon_large.c ../../../../../MiniWin/bitmaps/file_icon_small.c ../../../../../MiniWin/bitmaps/folder_close_icon_large.c ../../../../../MiniWin/bitmaps/folder_close_icon_small.c ../../../../../MiniWin/bitmaps/folder_icon_large.c ../../../../../MiniWin/bitmaps/folder_icon_small.c ../../../../../MiniWin/bitmaps/folder_open_icon_large.c ../../../../../MiniWin/bitmaps/folder_open_icon_small.c ../../../../../MiniWin/bitmaps/let_key.c ../../../../../MiniWin/bitmaps/maximise_icon.c ../../../../../MiniWin/bitmaps/maximise_icon_large.c ../../../../../MiniWin/bitmaps/minimise_icon.c ../../../../../MiniWin/bitmaps/minimise_icon_large.c ../../../../../MiniWin/bitmaps/num_key.c ../../../../../MiniWin/bitmaps/resize_icon.c ../../../../../MiniWin/bitmaps/resize_icon_large.c ../../../../../MiniWin/bitmaps/shift_key.c ../../../../../MiniWin/bitmaps/sym_key.c ../../../../../MiniWin/bitmaps/tick.c ../../../../../MiniWin/bitmaps/tick_large.c ../../../../../MiniWin/dialogs/dialog_colour_chooser.c ../../../../../MiniWin/dialogs/dialog_date_chooser.c ../../../../../MiniWin/dialogs/dialog_file_chooser.c ../../../../../MiniWin/dialogs/dialog_number_entry.c ../../../../../MiniWin/dialogs/dialog_one_button.c ../../../../../MiniWin/dialogs/dialog_text_entry.c ../../../../../MiniWin/dialogs/dialog_time_chooser.c ../../../../../MiniWin/dialogs/dialog_two_button.c ../../../../../MiniWin/gl/fonts/bitmapped/font12.c ../../../../../MiniWin/gl/fonts/bitmapped/font16.c ../../../../../MiniWin/gl/fonts/bitmapped/font20.c ../../../../../MiniWin/gl/fonts/bitmapped/font24.c ../../../../../MiniWin/gl/fonts/bitmapped/font9.c ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c ../../../../../MiniWin/gl/gl.c ../../../../../MiniWin/hal/DevKitC/hal_delay.c ../../../../../MiniWin/hal/DevKitC/hal_lcd.c ../../../../../MiniWin/hal/DevKitC/hal_non_vol.c ../../../../../MiniWin/hal/DevKitC/hal_timer.c ../../../../../MiniWin/hal/DevKitC/hal_touch.c ../../../../../MiniWin/hal/linux/hal_delay.c ../../../../../MiniWin/hal/linux/hal_lcd.c ../../../../../MiniWin/hal/linux/hal_non_vol.c ../../../../../MiniWin/hal/linux/hal_timer.c ../../../../../MiniWin/hal/linux/hal_touch.c ../../../../../MiniWin/hal/lpc54628/hal_delay.c ../../../../../MiniWin/hal/lpc54628/hal_lcd.c ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c ../../../../../MiniWin/hal/lpc54628/hal_timer.c ../../../../../MiniWin/hal/lpc54628/hal_touch.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_delay.c ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_lcd.c ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_non_vol.c ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_timer.c ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_touch.c ../../../../../MiniWin/hal/rx65n/hal_delay.c ../../../../../MiniWin/hal/rx65n/hal_lcd.c ../../../../../MiniWin/hal/rx65n/hal_non_vol.c ../../../../../MiniWin/hal/rx65n/hal_timer.c ../../../../../MiniWin/hal/rx65n/hal_touch.c ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c ../../../../../MiniWin/hal/stm32f407/hal_delay.c ../../../../../MiniWin/hal/stm32f407/hal_lcd.c ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c ../../../../../MiniWin/hal/stm32f407/hal_timer.c ../../../../../MiniWin/hal/stm32f407/hal_touch.c ../../../../../MiniWin/hal/stm32f429/hal_delay.c ../../../../../MiniWin/hal/stm32f429/hal_lcd.c ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c ../../../../../MiniWin/hal/stm32f429/hal_timer.c ../../../../../MiniWin/hal/stm32f429/hal_touch.c ../../../../../MiniWin/hal/windows/hal_delay.c ../../../../../MiniWin/hal/windows/hal_lcd.c ../../../../../MiniWin/hal/windows/hal_non_vol.c ../../../../../MiniWin/hal/windows/hal_timer.c ../../../../../MiniWin/hal/windows/hal_touch.c ../../../../../MiniWin/hal/hal_init.c ../../../../../MiniWin/ui/ui_arrow.c ../../../../../MiniWin/ui/ui_button.c ../../../../../MiniWin/ui/ui_check_box.c ../../../../../MiniWin/ui/ui_common.c ../../../../../MiniWin/ui/ui_keyboard.c ../../../../../MiniWin/ui/ui_keypad.c ../../../../../MiniWin/ui/ui_label.c ../../../../../MiniWin/ui/ui_list_box.c ../../../../../MiniWin/ui/ui_progress_bar.c ../../../../../MiniWin/ui/ui_radio_button.c ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c ../../../../../MiniWin/ui/ui_scroll_bar_vert.c ../../../../../MiniWin/ui/ui_tabs.c ../../../../../MiniWin/ui/ui_text_box.c ../../../../../MiniWin/ui/ui_tree.c ../../../../../MiniWin/calibrate.c ../../../../../MiniWin/miniwin.c ../../../../../MiniWin/miniwin_debug.c ../../../../../MiniWin/miniwin_message_queue.c ../../../../../MiniWin/miniwin_settings.c ../../../../../MiniWin/miniwin_touch.c ../../../../../MiniWin/miniwin_tree_container.c ../../../../../MiniWin/miniwin_utilities.c ../../../../../MiniWinFile_Common/main.c ../../../../../MiniWinFile_Common/miniwin_user.c ../../../../../MiniWinFile_Common/window_file.c ../../../../../MiniWinFile_Common/window_file_tree.c ../../../../../MiniWinFile_Common/window_image.c ../../../../../MiniWinFile_Common/window_selection.c ../../../../../MiniWinFile_Common/window_text.c ../../src/app.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ${OBJECTDIR}/_ext/60181895/plib_tmr3.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1592496102/ff.o ${OBJECTDIR}/_ext/1592496102/sdmm.o ${OBJECTDIR}/_ext/1592496102/spi_driver.o ${OBJECTDIR}/_ext/1275709973/backspace_key.o ${OBJECTDIR}/_ext/1275709973/close_icon.o ${OBJECTDIR}/_ext/1275709973/close_icon_large.o ${OBJECTDIR}/_ext/1275709973/file_icon_large.o ${OBJECTDIR}/_ext/1275709973/file_icon_small.o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o ${OBJECTDIR}/_ext/1275709973/let_key.o ${OBJECTDIR}/_ext/1275709973/maximise_icon.o ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o ${OBJECTDIR}/_ext/1275709973/minimise_icon.o ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o ${OBJECTDIR}/_ext/1275709973/num_key.o ${OBJECTDIR}/_ext/1275709973/resize_icon.o ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o ${OBJECTDIR}/_ext/1275709973/shift_key.o ${OBJECTDIR}/_ext/1275709973/sym_key.o ${OBJECTDIR}/_ext/1275709973/tick.o ${OBJECTDIR}/_ext/1275709973/tick_large.o ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o ${OBJECTDIR}/_ext/481733874/dialog_one_button.o ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o ${OBJECTDIR}/_ext/481733874/dialog_two_button.o ${OBJECTDIR}/_ext/194049764/font12.o ${OBJECTDIR}/_ext/194049764/font16.o ${OBJECTDIR}/_ext/194049764/font20.o ${OBJECTDIR}/_ext/194049764/font24.o ${OBJECTDIR}/_ext/194049764/font9.o ${OBJECTDIR}/_ext/194049764/gl_title_font.o ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o ${OBJECTDIR}/_ext/1391772861/mf_encoding.o ${OBJECTDIR}/_ext/1391772861/mf_font.o ${OBJECTDIR}/_ext/1391772861/mf_justify.o ${OBJECTDIR}/_ext/1391772861/mf_kerning.o ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o ${OBJECTDIR}/_ext/1494914114/gl.o ${OBJECTDIR}/_ext/1063548019/hal_delay.o ${OBJECTDIR}/_ext/1063548019/hal_lcd.o ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o ${OBJECTDIR}/_ext/1063548019/hal_timer.o ${OBJECTDIR}/_ext/1063548019/hal_touch.o ${OBJECTDIR}/_ext/1184163457/hal_delay.o ${OBJECTDIR}/_ext/1184163457/hal_lcd.o ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o ${OBJECTDIR}/_ext/1184163457/hal_timer.o ${OBJECTDIR}/_ext/1184163457/hal_touch.o ${OBJECTDIR}/_ext/1305585261/hal_delay.o ${OBJECTDIR}/_ext/1305585261/hal_lcd.o ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o ${OBJECTDIR}/_ext/1305585261/hal_timer.o ${OBJECTDIR}/_ext/1305585261/hal_touch.o ${OBJECTDIR}/_ext/818872118/hal_delay.o ${OBJECTDIR}/_ext/818872118/hal_lcd.o ${OBJECTDIR}/_ext/818872118/hal_non_vol.o ${OBJECTDIR}/_ext/818872118/hal_timer.o ${OBJECTDIR}/_ext/818872118/hal_touch.o ${OBJECTDIR}/_ext/776318040/hal_delay.o ${OBJECTDIR}/_ext/776318040/hal_lcd.o ${OBJECTDIR}/_ext/776318040/hal_non_vol.o ${OBJECTDIR}/_ext/776318040/hal_timer.o ${OBJECTDIR}/_ext/776318040/hal_touch.o ${OBJECTDIR}/_ext/1178231276/hal_delay.o ${OBJECTDIR}/_ext/1178231276/hal_lcd.o ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o ${OBJECTDIR}/_ext/1178231276/hal_timer.o ${OBJECTDIR}/_ext/1178231276/hal_touch.o ${OBJECTDIR}/_ext/51196508/hal_delay.o ${OBJECTDIR}/_ext/51196508/hal_lcd.o ${OBJECTDIR}/_ext/51196508/hal_non_vol.o ${OBJECTDIR}/_ext/51196508/hal_timer.o ${OBJECTDIR}/_ext/51196508/hal_touch.o ${OBJECTDIR}/_ext/1317985835/hal_delay.o ${OBJECTDIR}/_ext/1317985835/hal_lcd.o ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o ${OBJECTDIR}/_ext/1317985835/hal_timer.o ${OBJECTDIR}/_ext/1317985835/hal_touch.o ${OBJECTDIR}/_ext/1317985899/hal_delay.o ${OBJECTDIR}/_ext/1317985899/hal_lcd.o ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o ${OBJECTDIR}/_ext/1317985899/hal_timer.o ${OBJECTDIR}/_ext/1317985899/hal_touch.o ${OBJECTDIR}/_ext/1357345870/hal_delay.o ${OBJECTDIR}/_ext/1357345870/hal_lcd.o ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o ${OBJECTDIR}/_ext/1357345870/hal_timer.o ${OBJECTDIR}/_ext/1357345870/hal_touch.o ${OBJECTDIR}/_ext/902303450/hal_init.o ${OBJECTDIR}/_ext/1494913683/ui_arrow.o ${OBJECTDIR}/_ext/1494913683/ui_button.o ${OBJECTDIR}/_ext/1494913683/ui_check_box.o ${OBJECTDIR}/_ext/1494913683/ui_common.o ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o ${OBJECTDIR}/_ext/1494913683/ui_keypad.o ${OBJECTDIR}/_ext/1494913683/ui_label.o ${OBJECTDIR}/_ext/1494913683/ui_list_box.o ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o ${OBJECTDIR}/_ext/1494913683/ui_tabs.o ${OBJECTDIR}/_ext/1494913683/ui_text_box.o ${OBJECTDIR}/_ext/1494913683/ui_tree.o ${OBJECTDIR}/_ext/59636182/calibrate.o ${OBJECTDIR}/_ext/59636182/miniwin.o ${OBJECTDIR}/_ext/59636182/miniwin_debug.o ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o ${OBJECTDIR}/_ext/59636182/miniwin_settings.o ${OBJECTDIR}/_ext/59636182/miniwin_touch.o ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o ${OBJECTDIR}/_ext/165771656/main.o ${OBJECTDIR}/_ext/165771656/miniwin_user.o ${OBJECTDIR}/_ext/165771656/window_file.o ${OBJECTDIR}/_ext/165771656/window_file_tree.o ${OBJECTDIR}/_ext/165771656/window_image.o ${OBJECTDIR}/_ext/165771656/window_selection.o ${OBJECTDIR}/_ext/165771656/window_text.o ${OBJECTDIR}/_ext/1445274692/app.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/60165520/plib_clk.o.d ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o.d ${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d ${OBJECTDIR}/_ext/60181895/plib_tmr3.o.d ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d ${OBJECTDIR}/_ext/1171490990/initialization.o.d ${OBJECTDIR}/_ext/1171490990/interrupts.o.d ${OBJECTDIR}/_ext/1171490990/exceptions.o.d ${OBJECTDIR}/_ext/1592496102/ff.o.d ${OBJECTDIR}/_ext/1592496102/sdmm.o.d ${OBJECTDIR}/_ext/1592496102/spi_driver.o.d ${OBJECTDIR}/_ext/1275709973/backspace_key.o.d ${OBJECTDIR}/_ext/1275709973/close_icon.o.d ${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d ${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d ${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d ${OBJECTDIR}/_ext/1275709973/let_key.o.d ${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d ${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d ${OBJECTDIR}/_ext/1275709973/num_key.o.d ${OBJECTDIR}/_ext/1275709973/resize_icon.o.d ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d ${OBJECTDIR}/_ext/1275709973/shift_key.o.d ${OBJECTDIR}/_ext/1275709973/sym_key.o.d ${OBJECTDIR}/_ext/1275709973/tick.o.d ${OBJECTDIR}/_ext/1275709973/tick_large.o.d ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d ${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d ${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d ${OBJECTDIR}/_ext/194049764/font12.o.d ${OBJECTDIR}/_ext/194049764/font16.o.d ${OBJECTDIR}/_ext/194049764/font20.o.d ${OBJECTDIR}/_ext/194049764/font24.o.d ${OBJECTDIR}/_ext/194049764/font9.o.d ${OBJECTDIR}/_ext/194049764/gl_title_font.o.d ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d ${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d ${OBJECTDIR}/_ext/1391772861/mf_font.o.d ${OBJECTDIR}/_ext/1391772861/mf_justify.o.d ${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d ${OBJECTDIR}/_ext/1494914114/gl.o.d ${OBJECTDIR}/_ext/1063548019/hal_delay.o.d ${OBJECTDIR}/_ext/1063548019/hal_lcd.o.d ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o.d ${OBJECTDIR}/_ext/1063548019/hal_timer.o.d ${OBJECTDIR}/_ext/1063548019/hal_touch.o.d ${OBJECTDIR}/_ext/1184163457/hal_delay.o.d ${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d ${OBJECTDIR}/_ext/1184163457/hal_timer.o.d ${OBJECTDIR}/_ext/1184163457/hal_touch.o.d ${OBJECTDIR}/_ext/1305585261/hal_delay.o.d ${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d ${OBJECTDIR}/_ext/1305585261/hal_timer.o.d ${OBJECTDIR}/_ext/1305585261/hal_touch.o.d ${OBJECTDIR}/_ext/818872118/hal_delay.o.d ${OBJECTDIR}/_ext/818872118/hal_lcd.o.d ${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d ${OBJECTDIR}/_ext/818872118/hal_timer.o.d ${OBJECTDIR}/_ext/818872118/hal_touch.o.d ${OBJECTDIR}/_ext/776318040/hal_delay.o.d ${OBJECTDIR}/_ext/776318040/hal_lcd.o.d ${OBJECTDIR}/_ext/776318040/hal_non_vol.o.d ${OBJECTDIR}/_ext/776318040/hal_timer.o.d ${OBJECTDIR}/_ext/776318040/hal_touch.o.d ${OBJECTDIR}/_ext/1178231276/hal_delay.o.d ${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d ${OBJECTDIR}/_ext/1178231276/hal_timer.o.d ${OBJECTDIR}/_ext/1178231276/hal_touch.o.d ${OBJECTDIR}/_ext/51196508/hal_delay.o.d ${OBJECTDIR}/_ext/51196508/hal_lcd.o.d ${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d ${OBJECTDIR}/_ext/51196508/hal_timer.o.d ${OBJECTDIR}/_ext/51196508/hal_touch.o.d ${OBJECTDIR}/_ext/1317985835/hal_delay.o.d ${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d ${OBJECTDIR}/_ext/1317985835/hal_timer.o.d ${OBJECTDIR}/_ext/1317985835/hal_touch.o.d ${OBJECTDIR}/_ext/1317985899/hal_delay.o.d ${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d ${OBJECTDIR}/_ext/1317985899/hal_timer.o.d ${OBJECTDIR}/_ext/1317985899/hal_touch.o.d ${OBJECTDIR}/_ext/1357345870/hal_delay.o.d ${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d ${OBJECTDIR}/_ext/1357345870/hal_timer.o.d ${OBJECTDIR}/_ext/1357345870/hal_touch.o.d ${OBJECTDIR}/_ext/902303450/hal_init.o.d ${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d ${OBJECTDIR}/_ext/1494913683/ui_button.o.d ${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d ${OBJECTDIR}/_ext/1494913683/ui_common.o.d ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d ${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d ${OBJECTDIR}/_ext/1494913683/ui_label.o.d ${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d ${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d ${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d ${OBJECTDIR}/_ext/1494913683/ui_tree.o.d ${OBJECTDIR}/_ext/59636182/calibrate.o.d ${OBJECTDIR}/_ext/59636182/miniwin.o.d ${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d ${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d ${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d ${OBJECTDIR}/_ext/165771656/main.o.d ${OBJECTDIR}/_ext/165771656/miniwin_user.o.d ${OBJECTDIR}/_ext/165771656/window_file.o.d ${OBJECTDIR}/_ext/165771656/window_file_tree.o.d ${OBJECTDIR}/_ext/165771656/window_image.o.d ${OBJECTDIR}/_ext/165771656/window_selection.o.d ${OBJECTDIR}/_ext/165771656/window_text.o.d ${OBJECTDIR}/_ext/1445274692/app.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ${OBJECTDIR}/_ext/60181895/plib_tmr3.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1592496102/ff.o ${OBJECTDIR}/_ext/1592496102/sdmm.o ${OBJECTDIR}/_ext/1592496102/spi_driver.o ${OBJECTDIR}/_ext/1275709973/backspace_key.o ${OBJECTDIR}/_ext/1275709973/close_icon.o ${OBJECTDIR}/_ext/1275709973/close_icon_large.o ${OBJECTDIR}/_ext/1275709973/file_icon_large.o ${OBJECTDIR}/_ext/1275709973/file_icon_small.o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o ${OBJECTDIR}/_ext/1275709973/let_key.o ${OBJECTDIR}/_ext/1275709973/maximise_icon.o ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o ${OBJECTDIR}/_ext/1275709973/minimise_icon.o ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o ${OBJECTDIR}/_ext/1275709973/num_key.o ${OBJECTDIR}/_ext/1275709973/resize_icon.o ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o ${OBJECTDIR}/_ext/1275709973/shift_key.o ${OBJECTDIR}/_ext/1275709973/sym_key.o ${OBJECTDIR}/_ext/1275709973/tick.o ${OBJECTDIR}/_ext/1275709973/tick_large.o ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o ${OBJECTDIR}/_ext/481733874/dialog_one_button.o ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o ${OBJECTDIR}/_ext/481733874/dialog_two_button.o ${OBJECTDIR}/_ext/194049764/font12.o ${OBJECTDIR}/_ext/194049764/font16.o ${OBJECTDIR}/_ext/194049764/font20.o ${OBJECTDIR}/_ext/194049764/font24.o ${OBJECTDIR}/_ext/194049764/font9.o ${OBJECTDIR}/_ext/194049764/gl_title_font.o ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o ${OBJECTDIR}/_ext/1391772861/mf_encoding.o ${OBJECTDIR}/_ext/1391772861/mf_font.o ${OBJECTDIR}/_ext/1391772861/mf_justify.o ${OBJECTDIR}/_ext/1391772861/mf_kerning.o ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o ${OBJECTDIR}/_ext/1494914114/gl.o ${OBJECTDIR}/_ext/1063548019/hal_delay.o ${OBJECTDIR}/_ext/1063548019/hal_lcd.o ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o ${OBJECTDIR}/_ext/1063548019/hal_timer.o ${OBJECTDIR}/_ext/1063548019/hal_touch.o ${OBJECTDIR}/_ext/1184163457/hal_delay.o ${OBJECTDIR}/_ext/1184163457/hal_lcd.o ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o ${OBJECTDIR}/_ext/1184163457/hal_timer.o ${OBJECTDIR}/_ext/1184163457/hal_touch.o ${OBJECTDIR}/_ext/1305585261/hal_delay.o ${OBJECTDIR}/_ext/1305585261/hal_lcd.o ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o ${OBJECTDIR}/_ext/1305585261/hal_timer.o ${OBJECTDIR}/_ext/1305585261/hal_touch.o ${OBJECTDIR}/_ext/818872118/hal_delay.o ${OBJECTDIR}/_ext/818872118/hal_lcd.o ${OBJECTDIR}/_ext/818872118/hal_non_vol.o ${OBJECTDIR}/_ext/818872118/hal_timer.o ${OBJECTDIR}/_ext/818872118/hal_touch.o ${OBJECTDIR}/_ext/776318040/hal_delay.o ${OBJECTDIR}/_ext/776318040/hal_lcd.o ${OBJECTDIR}/_ext/776318040/hal_non_vol.o ${OBJECTDIR}/_ext/776318040/hal_timer.o ${OBJECTDIR}/_ext/776318040/hal_touch.o ${OBJECTDIR}/_ext/1178231276/hal_delay.o ${OBJECTDIR}/_ext/1178231276/hal_lcd.o ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o ${OBJECTDIR}/_ext/1178231276/hal_timer.o ${OBJECTDIR}/_ext/1178231276/hal_touch.o ${OBJECTDIR}/_ext/51196508/hal_delay.o ${OBJECTDIR}/_ext/51196508/hal_lcd.o ${OBJECTDIR}/_ext/51196508/hal_non_vol.o ${OBJECTDIR}/_ext/51196508/hal_timer.o ${OBJECTDIR}/_ext/51196508/hal_touch.o ${OBJECTDIR}/_ext/1317985835/hal_delay.o ${OBJECTDIR}/_ext/1317985835/hal_lcd.o ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o ${OBJECTDIR}/_ext/1317985835/hal_timer.o ${OBJECTDIR}/_ext/1317985835/hal_touch.o ${OBJECTDIR}/_ext/1317985899/hal_delay.o ${OBJECTDIR}/_ext/1317985899/hal_lcd.o ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o ${OBJECTDIR}/_ext/1317985899/hal_timer.o ${OBJECTDIR}/_ext/1317985899/hal_touch.o ${OBJECTDIR}/_ext/1357345870/hal_delay.o ${OBJECTDIR}/_ext/1357345870/hal_lcd.o ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o ${OBJECTDIR}/_ext/1357345870/hal_timer.o ${OBJECTDIR}/_ext/1357345870/hal_touch.o ${OBJECTDIR}/_ext/902303450/hal_init.o ${OBJECTDIR}/_ext/1494913683/ui_arrow.o ${OBJECTDIR}/_ext/1494913683/ui_button.o ${OBJECTDIR}/_ext/1494913683/ui_check_box.o ${OBJECTDIR}/_ext/1494913683/ui_common.o ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o ${OBJECTDIR}/_ext/1494913683/ui_keypad.o ${OBJECTDIR}/_ext/1494913683/ui_label.o ${OBJECTDIR}/_ext/1494913683/ui_list_box.o ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o ${OBJECTDIR}/_ext/1494913683/ui_tabs.o ${OBJECTDIR}/_ext/1494913683/ui_text_box.o ${OBJECTDIR}/_ext/1494913683/ui_tree.o ${OBJECTDIR}/_ext/59636182/calibrate.o ${OBJECTDIR}/_ext/59636182/miniwin.o ${OBJECTDIR}/_ext/59636182/miniwin_debug.o ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o ${OBJECTDIR}/_ext/59636182/miniwin_settings.o ${OBJECTDIR}/_ext/59636182/miniwin_touch.o ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o ${OBJECTDIR}/_ext/165771656/main.o ${OBJECTDIR}/_ext/165771656/miniwin_user.o ${OBJECTDIR}/_ext/165771656/window_file.o ${OBJECTDIR}/_ext/165771656/window_file_tree.o ${OBJECTDIR}/_ext/165771656/window_image.o ${OBJECTDIR}/_ext/165771656/window_selection.o ${OBJECTDIR}/_ext/165771656/window_text.o ${OBJECTDIR}/_ext/1445274692/app.o

# Source Files
SOURCEFILES=../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/coretimer/plib_coretimer.c ../src/config/default/peripheral/evic/plib_evic.c ../src/config/default/peripheral/gpio/plib_gpio.c ../src/config/default/peripheral/nvm/plib_nvm.c ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c ../src/config/default/peripheral/spi/spi_master/plib_spi1_master.c ../src/config/default/peripheral/tmr/plib_tmr2.c ../src/config/default/peripheral/tmr/plib_tmr3.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../../FatFS/ff.c ../../FatFS/sdmm.c ../../FatFS/spi_driver.c ../../../../../MiniWin/bitmaps/backspace_key.c ../../../../../MiniWin/bitmaps/close_icon.c ../../../../../MiniWin/bitmaps/close_icon_large.c ../../../../../MiniWin/bitmaps/file_icon_large.c ../../../../../MiniWin/bitmaps/file_icon_small.c ../../../../../MiniWin/bitmaps/folder_close_icon_large.c ../../../../../MiniWin/bitmaps/folder_close_icon_small.c ../../../../../MiniWin/bitmaps/folder_icon_large.c ../../../../../MiniWin/bitmaps/folder_icon_small.c ../../../../../MiniWin/bitmaps/folder_open_icon_large.c ../../../../../MiniWin/bitmaps/folder_open_icon_small.c ../../../../../MiniWin/bitmaps/let_key.c ../../../../../MiniWin/bitmaps/maximise_icon.c ../../../../../MiniWin/bitmaps/maximise_icon_large.c ../../../../../MiniWin/bitmaps/minimise_icon.c ../../../../../MiniWin/bitmaps/minimise_icon_large.c ../../../../../MiniWin/bitmaps/num_key.c ../../../../../MiniWin/bitmaps/resize_icon.c ../../../../../MiniWin/bitmaps/resize_icon_large.c ../../../../../MiniWin/bitmaps/shift_key.c ../../../../../MiniWin/bitmaps/sym_key.c ../../../../../MiniWin/bitmaps/tick.c ../../../../../MiniWin/bitmaps/tick_large.c ../../../../../MiniWin/dialogs/dialog_colour_chooser.c ../../../../../MiniWin/dialogs/dialog_date_chooser.c ../../../../../MiniWin/dialogs/dialog_file_chooser.c ../../../../../MiniWin/dialogs/dialog_number_entry.c ../../../../../MiniWin/dialogs/dialog_one_button.c ../../../../../MiniWin/dialogs/dialog_text_entry.c ../../../../../MiniWin/dialogs/dialog_time_chooser.c ../../../../../MiniWin/dialogs/dialog_two_button.c ../../../../../MiniWin/gl/fonts/bitmapped/font12.c ../../../../../MiniWin/gl/fonts/bitmapped/font16.c ../../../../../MiniWin/gl/fonts/bitmapped/font20.c ../../../../../MiniWin/gl/fonts/bitmapped/font24.c ../../../../../MiniWin/gl/fonts/bitmapped/font9.c ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c ../../../../../MiniWin/gl/gl.c ../../../../../MiniWin/hal/DevKitC/hal_delay.c ../../../../../MiniWin/hal/DevKitC/hal_lcd.c ../../../../../MiniWin/hal/DevKitC/hal_non_vol.c ../../../../../MiniWin/hal/DevKitC/hal_timer.c ../../../../../MiniWin/hal/DevKitC/hal_touch.c ../../../../../MiniWin/hal/linux/hal_delay.c ../../../../../MiniWin/hal/linux/hal_lcd.c ../../../../../MiniWin/hal/linux/hal_non_vol.c ../../../../../MiniWin/hal/linux/hal_timer.c ../../../../../MiniWin/hal/linux/hal_touch.c ../../../../../MiniWin/hal/lpc54628/hal_delay.c ../../../../../MiniWin/hal/lpc54628/hal_lcd.c ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c ../../../../../MiniWin/hal/lpc54628/hal_timer.c ../../../../../MiniWin/hal/lpc54628/hal_touch.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_delay.c ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_lcd.c ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_non_vol.c ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_timer.c ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_touch.c ../../../../../MiniWin/hal/rx65n/hal_delay.c ../../../../../MiniWin/hal/rx65n/hal_lcd.c ../../../../../MiniWin/hal/rx65n/hal_non_vol.c ../../../../../MiniWin/hal/rx65n/hal_timer.c ../../../../../MiniWin/hal/rx65n/hal_touch.c ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c ../../../../../MiniWin/hal/stm32f407/hal_delay.c ../../../../../MiniWin/hal/stm32f407/hal_lcd.c ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c ../../../../../MiniWin/hal/stm32f407/hal_timer.c ../../../../../MiniWin/hal/stm32f407/hal_touch.c ../../../../../MiniWin/hal/stm32f429/hal_delay.c ../../../../../MiniWin/hal/stm32f429/hal_lcd.c ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c ../../../../../MiniWin/hal/stm32f429/hal_timer.c ../../../../../MiniWin/hal/stm32f429/hal_touch.c ../../../../../MiniWin/hal/windows/hal_delay.c ../../../../../MiniWin/hal/windows/hal_lcd.c ../../../../../MiniWin/hal/windows/hal_non_vol.c ../../../../../MiniWin/hal/windows/hal_timer.c ../../../../../MiniWin/hal/windows/hal_touch.c ../../../../../MiniWin/hal/hal_init.c ../../../../../MiniWin/ui/ui_arrow.c ../../../../../MiniWin/ui/ui_button.c ../../../../../MiniWin/ui/ui_check_box.c ../../../../../MiniWin/ui/ui_common.c ../../../../../MiniWin/ui/ui_keyboard.c ../../../../../MiniWin/ui/ui_keypad.c ../../../../../MiniWin/ui/ui_label.c ../../../../../MiniWin/ui/ui_list_box.c ../../../../../MiniWin/ui/ui_progress_bar.c ../../../../../MiniWin/ui/ui_radio_button.c ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c ../../../../../MiniWin/ui/ui_scroll_bar_vert.c ../../../../../MiniWin/ui/ui_tabs.c ../../../../../MiniWin/ui/ui_text_box.c ../../../../../MiniWin/ui/ui_tree.c ../../../../../MiniWin/calibrate.c ../../../../../MiniWin/miniwin.c ../../../../../MiniWin/miniwin_debug.c ../../../../../MiniWin/miniwin_message_queue.c ../../../../../MiniWin/miniwin_settings.c ../../../../../MiniWin/miniwin_touch.c ../../../../../MiniWin/miniwin_tree_container.c ../../../../../MiniWin/miniwin_utilities.c ../../../../../MiniWinFile_Common/main.c ../../../../../MiniWinFile_Common/miniwin_user.c ../../../../../MiniWinFile_Common/window_file.c ../../../../../MiniWinFile_Common/window_file_tree.c ../../../../../MiniWinFile_Common/window_image.c ../../../../../MiniWinFile_Common/window_selection.c ../../../../../MiniWinFile_Common/window_text.c ../../src/app.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MiniWinFile.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MZ2048EFM100
MP_LINKER_FILE_OPTION=,--script="..\src\config\default\p32MZ2048EFM100.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/7d378c5dc85b2bee5edaffe120d6934a006afe20.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1249264884/plib_coretimer.o: ../src/config/default/peripheral/coretimer/plib_coretimer.c  .generated_files/4c329ef9d8691240775f08cbc515152adbb5afce.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1249264884" 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ../src/config/default/peripheral/coretimer/plib_coretimer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/1c10f4c57aa7e788fb29f43230f37fd03ef89ad9.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/e02cd17e262a8d7e5b4d6b6426880dbe9e6128c6.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60176403/plib_nvm.o: ../src/config/default/peripheral/nvm/plib_nvm.c  .generated_files/e13611b18954c978cc431f7099d39d67293f1def.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60176403" 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ../src/config/default/peripheral/nvm/plib_nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/298189674/plib_spi2_master.o: ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c  .generated_files/f38db170040718cc0a9be1da88bf53d701bec216.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/298189674" 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d" -o ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/298189674/plib_spi1_master.o: ../src/config/default/peripheral/spi/spi_master/plib_spi1_master.c  .generated_files/99cf41a7dd16051ebbc242b2c3b89f1c4ba6c2a5.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/298189674" 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/298189674/plib_spi1_master.o.d" -o ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o ../src/config/default/peripheral/spi/spi_master/plib_spi1_master.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60181895/plib_tmr2.o: ../src/config/default/peripheral/tmr/plib_tmr2.c  .generated_files/4999fb7cb6c3620606c9d6b5986524310cba8b5a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ../src/config/default/peripheral/tmr/plib_tmr2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60181895/plib_tmr3.o: ../src/config/default/peripheral/tmr/plib_tmr3.c  .generated_files/232bb9c6c1c5a4a1f37f5aa7bf34393d28d39bfc.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr3.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr3.o ../src/config/default/peripheral/tmr/plib_tmr3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/2c61477f7fbe82e634b78b452f37eb008f79d736.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/b0315d91a4d3ff64573f0e0b1e2df7d446f063a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/f5e3774d853df3a7fab2f8e204650b3f5c7c2cae.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/1e7b5522b62b77525c03e617f52b18eb16d5a4b8.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/ff.o: ../../FatFS/ff.c  .generated_files/533b76cad3aa4aac91289c91322207c75a2ee955.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/ff.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/ff.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/ff.o.d" -o ${OBJECTDIR}/_ext/1592496102/ff.o ../../FatFS/ff.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/sdmm.o: ../../FatFS/sdmm.c  .generated_files/a5f1d7892525417924bd5f297f174920ef5effe1.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/sdmm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/sdmm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/sdmm.o.d" -o ${OBJECTDIR}/_ext/1592496102/sdmm.o ../../FatFS/sdmm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/spi_driver.o: ../../FatFS/spi_driver.c  .generated_files/64e4dcf57c228e47a3a7f833756b46a5b224def7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/spi_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/spi_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/spi_driver.o.d" -o ${OBJECTDIR}/_ext/1592496102/spi_driver.o ../../FatFS/spi_driver.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/backspace_key.o: ../../../../../MiniWin/bitmaps/backspace_key.c  .generated_files/689d64473dc40cd34ccf2a0fa499d60ab04f0209.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/backspace_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/backspace_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/backspace_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/backspace_key.o ../../../../../MiniWin/bitmaps/backspace_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/close_icon.o: ../../../../../MiniWin/bitmaps/close_icon.c  .generated_files/b9f56b5993539aad379bcf64ef7ba088647a3ebd.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/close_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/close_icon.o ../../../../../MiniWin/bitmaps/close_icon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/close_icon_large.o: ../../../../../MiniWin/bitmaps/close_icon_large.c  .generated_files/43088564ebac30f7e5e32c441b1fb6e3b45a01c7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/close_icon_large.o ../../../../../MiniWin/bitmaps/close_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/file_icon_large.o: ../../../../../MiniWin/bitmaps/file_icon_large.c  .generated_files/7def8740689025d5b5733ae689461b902c1e32b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/file_icon_large.o ../../../../../MiniWin/bitmaps/file_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/file_icon_small.o: ../../../../../MiniWin/bitmaps/file_icon_small.c  .generated_files/ea557cbab8afd05aff7fdd3794d15b316c1996d1.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/file_icon_small.o ../../../../../MiniWin/bitmaps/file_icon_small.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o: ../../../../../MiniWin/bitmaps/folder_close_icon_large.c  .generated_files/5306096fcd48fee2a705dcbfa691c9113bc7be00.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o ../../../../../MiniWin/bitmaps/folder_close_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o: ../../../../../MiniWin/bitmaps/folder_close_icon_small.c  .generated_files/96651aef6b320630ed1a94af6da6bd82d2df20ee.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o ../../../../../MiniWin/bitmaps/folder_close_icon_small.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_icon_large.o: ../../../../../MiniWin/bitmaps/folder_icon_large.c  .generated_files/5a0970974a0df8e179e589eae07cf27ec29f51ea.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o ../../../../../MiniWin/bitmaps/folder_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_icon_small.o: ../../../../../MiniWin/bitmaps/folder_icon_small.c  .generated_files/40fc9f76476a664c931384c2f35e7275ad7acc21.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o ../../../../../MiniWin/bitmaps/folder_icon_small.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o: ../../../../../MiniWin/bitmaps/folder_open_icon_large.c  .generated_files/50bb5213ef8dc104404832ad20f9f9190c169d5b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o ../../../../../MiniWin/bitmaps/folder_open_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o: ../../../../../MiniWin/bitmaps/folder_open_icon_small.c  .generated_files/f1c4176a80a931dd50ec692e31da7d6dbabdcfca.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o ../../../../../MiniWin/bitmaps/folder_open_icon_small.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/let_key.o: ../../../../../MiniWin/bitmaps/let_key.c  .generated_files/974929aadc4e9383fb4ecbb73ddffc60aa15c278.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/let_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/let_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/let_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/let_key.o ../../../../../MiniWin/bitmaps/let_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/maximise_icon.o: ../../../../../MiniWin/bitmaps/maximise_icon.c  .generated_files/19d365dd304a0f8947918057c0a335dca911f403.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/maximise_icon.o ../../../../../MiniWin/bitmaps/maximise_icon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o: ../../../../../MiniWin/bitmaps/maximise_icon_large.c  .generated_files/2107b656a30ce3214b9ff95e5be95dc9f9f299de.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o ../../../../../MiniWin/bitmaps/maximise_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/minimise_icon.o: ../../../../../MiniWin/bitmaps/minimise_icon.c  .generated_files/9cbc933fd20dd0f2324c690a8f19e3a2bf551361.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/minimise_icon.o ../../../../../MiniWin/bitmaps/minimise_icon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o: ../../../../../MiniWin/bitmaps/minimise_icon_large.c  .generated_files/d895d8276ecbff32e8405597404568dd84e75e59.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o ../../../../../MiniWin/bitmaps/minimise_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/num_key.o: ../../../../../MiniWin/bitmaps/num_key.c  .generated_files/b35df7c623d9e115f3990cfeea9464ff6d02c2ad.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/num_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/num_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/num_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/num_key.o ../../../../../MiniWin/bitmaps/num_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/resize_icon.o: ../../../../../MiniWin/bitmaps/resize_icon.c  .generated_files/a455b78d37a56bc0903a510c934a45d7def4f48a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/resize_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/resize_icon.o ../../../../../MiniWin/bitmaps/resize_icon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/resize_icon_large.o: ../../../../../MiniWin/bitmaps/resize_icon_large.c  .generated_files/66ae4fbbd14a1edc4a488eb1d611878f43adc060.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o ../../../../../MiniWin/bitmaps/resize_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/shift_key.o: ../../../../../MiniWin/bitmaps/shift_key.c  .generated_files/95107e41ee6e7c3e26aedcfcbf199fa175b0c4f1.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/shift_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/shift_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/shift_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/shift_key.o ../../../../../MiniWin/bitmaps/shift_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/sym_key.o: ../../../../../MiniWin/bitmaps/sym_key.c  .generated_files/d4669b38f819d015d0a1b1e4b16776b171ef591f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/sym_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/sym_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/sym_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/sym_key.o ../../../../../MiniWin/bitmaps/sym_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/tick.o: ../../../../../MiniWin/bitmaps/tick.c  .generated_files/93be5b7370f20e5eba2e59a7da1a753f82141241.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/tick.o.d" -o ${OBJECTDIR}/_ext/1275709973/tick.o ../../../../../MiniWin/bitmaps/tick.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/tick_large.o: ../../../../../MiniWin/bitmaps/tick_large.c  .generated_files/a41376889bf86725a8075dd5f268a06387a8313a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/tick_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/tick_large.o ../../../../../MiniWin/bitmaps/tick_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o: ../../../../../MiniWin/dialogs/dialog_colour_chooser.c  .generated_files/8d045e3cc26e10f71c49266672e1ed14e9ec2832.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o ../../../../../MiniWin/dialogs/dialog_colour_chooser.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o: ../../../../../MiniWin/dialogs/dialog_date_chooser.c  .generated_files/ab5f929a51a13cecbcb9aaa3391b989ea3ed25a0.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o ../../../../../MiniWin/dialogs/dialog_date_chooser.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o: ../../../../../MiniWin/dialogs/dialog_file_chooser.c  .generated_files/532e011d8fcd75620d34baf139596dab1f9b35d8.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o ../../../../../MiniWin/dialogs/dialog_file_chooser.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_number_entry.o: ../../../../../MiniWin/dialogs/dialog_number_entry.c  .generated_files/8c93f6aaaaedeaaec8e6fbe5b639a068d9e23f7d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o ../../../../../MiniWin/dialogs/dialog_number_entry.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_one_button.o: ../../../../../MiniWin/dialogs/dialog_one_button.c  .generated_files/ebab2b427dc0fdb3894a230a02b06e595afa0eda.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_one_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_one_button.o ../../../../../MiniWin/dialogs/dialog_one_button.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_text_entry.o: ../../../../../MiniWin/dialogs/dialog_text_entry.c  .generated_files/986a4f5f3484b05bc3b9f65044c43c7724d81a32.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o ../../../../../MiniWin/dialogs/dialog_text_entry.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o: ../../../../../MiniWin/dialogs/dialog_time_chooser.c  .generated_files/e769076409bf397fe9f797500a18f55854830293.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o ../../../../../MiniWin/dialogs/dialog_time_chooser.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_two_button.o: ../../../../../MiniWin/dialogs/dialog_two_button.c  .generated_files/1086a4a1f9ebbfa745797601c34134db7ed4073a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_two_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_two_button.o ../../../../../MiniWin/dialogs/dialog_two_button.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font12.o: ../../../../../MiniWin/gl/fonts/bitmapped/font12.c  .generated_files/e903b2f3c0ced8e7efada575739dd91c44a1b07f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font12.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font12.o.d" -o ${OBJECTDIR}/_ext/194049764/font12.o ../../../../../MiniWin/gl/fonts/bitmapped/font12.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font16.o: ../../../../../MiniWin/gl/fonts/bitmapped/font16.c  .generated_files/6356280fe4bdc6ed02c09e227d900eb52d5f71aa.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font16.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font16.o.d" -o ${OBJECTDIR}/_ext/194049764/font16.o ../../../../../MiniWin/gl/fonts/bitmapped/font16.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font20.o: ../../../../../MiniWin/gl/fonts/bitmapped/font20.c  .generated_files/788bcbed6dbfa2a8f2e9ef3b06f024345f72b477.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font20.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font20.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font20.o.d" -o ${OBJECTDIR}/_ext/194049764/font20.o ../../../../../MiniWin/gl/fonts/bitmapped/font20.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font24.o: ../../../../../MiniWin/gl/fonts/bitmapped/font24.c  .generated_files/7c0e9f92d1ef416cb5a25fab3934e793b0afffdd.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font24.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font24.o.d" -o ${OBJECTDIR}/_ext/194049764/font24.o ../../../../../MiniWin/gl/fonts/bitmapped/font24.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font9.o: ../../../../../MiniWin/gl/fonts/bitmapped/font9.c  .generated_files/951cd9b91a678530df296b464bea0309532ded45.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font9.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font9.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font9.o.d" -o ${OBJECTDIR}/_ext/194049764/font9.o ../../../../../MiniWin/gl/fonts/bitmapped/font9.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/gl_title_font.o: ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c  .generated_files/dc1e83922ba7058f243252cda5f07111ac0f44fb.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/gl_title_font.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/gl_title_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/gl_title_font.o.d" -o ${OBJECTDIR}/_ext/194049764/gl_title_font.o ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_bwfont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c  .generated_files/5dd5570183dc0117a7f41a7bb20b596182a8f7e6.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_encoding.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c  .generated_files/177e206d8625fb86d55c763716c6f7727cf9d514.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_encoding.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_encoding.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_font.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c  .generated_files/d0054380e50e5354b577573083fca4c07648d2fc.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_font.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_font.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_font.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_justify.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c  .generated_files/61078fad0e8e7b556e6ff6cdce8597de832dc8f0.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_justify.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_justify.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_justify.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_justify.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_kerning.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c  .generated_files/6f96e2b1b2dc73d5ccd423db6cf088678d65210b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_kerning.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_kerning.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_rlefont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c  .generated_files/8b98ccd10b20b6f3f52fbcdee95ebf21584b01f8.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c  .generated_files/ecb082ae83092284aca0e9f75c3cd205a5b04e6.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c  .generated_files/1de7ab198e2d763c87affe2b4c08d7aaffdda359.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o: ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c  .generated_files/ce4c3fd44892a61a0d6c864e7dc68a186e0e5f7c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d" -o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o: ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c  .generated_files/1cf29164334dd751a5369ede8ffeb4972c2bbbfd.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d" -o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o: ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c  .generated_files/d6c0345e21f3ee5c5296278854921e707afad395.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d" -o ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494914114/gl.o: ../../../../../MiniWin/gl/gl.c  .generated_files/a44b73291145dfda92a5426388f22aafdeb5eafb.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494914114" 
	@${RM} ${OBJECTDIR}/_ext/1494914114/gl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494914114/gl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494914114/gl.o.d" -o ${OBJECTDIR}/_ext/1494914114/gl.o ../../../../../MiniWin/gl/gl.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_delay.o: ../../../../../MiniWin/hal/DevKitC/hal_delay.c  .generated_files/ea9c8b71ad1a1c29464dc8f3fd12b92fd3e52bc4.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_delay.o ../../../../../MiniWin/hal/DevKitC/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_lcd.o: ../../../../../MiniWin/hal/DevKitC/hal_lcd.c  .generated_files/e716baed28efe8743d8e88e3af05349977ba8b43.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_lcd.o ../../../../../MiniWin/hal/DevKitC/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_non_vol.o: ../../../../../MiniWin/hal/DevKitC/hal_non_vol.c  .generated_files/411acd7bb63ed0c1f8841854bff1c7a33f1f9e6c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o ../../../../../MiniWin/hal/DevKitC/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_timer.o: ../../../../../MiniWin/hal/DevKitC/hal_timer.c  .generated_files/dc097dac65e8717fb42d238ff9e7cb21344ede96.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_timer.o ../../../../../MiniWin/hal/DevKitC/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_touch.o: ../../../../../MiniWin/hal/DevKitC/hal_touch.c  .generated_files/82158286d686cea2bca150f2339dbbe2923318a9.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_touch.o ../../../../../MiniWin/hal/DevKitC/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_delay.o: ../../../../../MiniWin/hal/linux/hal_delay.c  .generated_files/995447af098cce8a54a649546852dbf22c9cc588.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_delay.o ../../../../../MiniWin/hal/linux/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_lcd.o: ../../../../../MiniWin/hal/linux/hal_lcd.c  .generated_files/f3425668b7be55789c0789b0d8fdd7dcef10aee1.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_lcd.o ../../../../../MiniWin/hal/linux/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_non_vol.o: ../../../../../MiniWin/hal/linux/hal_non_vol.c  .generated_files/70b9e36faa95c07bce3b3d17516f096a8a51a1db.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o ../../../../../MiniWin/hal/linux/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_timer.o: ../../../../../MiniWin/hal/linux/hal_timer.c  .generated_files/91bbad72ea06867d19fef937e8cc6d45a495b787.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_timer.o ../../../../../MiniWin/hal/linux/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_touch.o: ../../../../../MiniWin/hal/linux/hal_touch.c  .generated_files/8f6ae8b794db6ede2ce5c19d6c71ac8379d30790.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_touch.o ../../../../../MiniWin/hal/linux/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_delay.o: ../../../../../MiniWin/hal/lpc54628/hal_delay.c  .generated_files/c2c94d7fce876450d912ea72b7452de50d0f33e7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_delay.o ../../../../../MiniWin/hal/lpc54628/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_lcd.o: ../../../../../MiniWin/hal/lpc54628/hal_lcd.c  .generated_files/5437055526876875eaa19b314d7f07b6332810c8.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_lcd.o ../../../../../MiniWin/hal/lpc54628/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_non_vol.o: ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c  .generated_files/f5f6522b012984a2592fc686a438eebde55ad330.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_timer.o: ../../../../../MiniWin/hal/lpc54628/hal_timer.c  .generated_files/9a5e37769a37194b1712c22299bbf8bc1ad27b7a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_timer.o ../../../../../MiniWin/hal/lpc54628/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_touch.o: ../../../../../MiniWin/hal/lpc54628/hal_touch.c  .generated_files/7c5a17bb70d49a987037be73dc81970089349fc9.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_touch.o ../../../../../MiniWin/hal/lpc54628/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_delay.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c  .generated_files/c85bea73fb910bf9d7a9b33888f9d676b72e2521.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_delay.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_delay.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_lcd.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c  .generated_files/30d1d00d0861d4f7243cdf38a628bdf050be0580.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_lcd.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_non_vol.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c  .generated_files/b9e5e1fa39a959b07120e705ac5822496979173.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_non_vol.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_timer.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c  .generated_files/a172c3c716c599a80ed345fa48693e9e8cbb0914.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_timer.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_timer.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_touch.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c  .generated_files/d25a267976c56da55c8d6c593cc51bd2dc4358b5.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_touch.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_touch.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_delay.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_delay.c  .generated_files/f2fea938c7b1b9a798bac729ee45cf0759d9c209.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_delay.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_delay.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_lcd.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_lcd.c  .generated_files/90489894d20c881d0bde10dc260c1d8a70b51c3f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_lcd.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_non_vol.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_non_vol.c  .generated_files/59836bcb741566fa1c9ca3857b9b7657757ac28.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_non_vol.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_timer.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_timer.c  .generated_files/48111884962bb0502835a90df2801d01f4e878f6.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_timer.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_timer.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_touch.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_touch.c  .generated_files/d21b14ac5e86e888ee40d850522ee47d1aecd66c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_touch.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_touch.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_delay.o: ../../../../../MiniWin/hal/rx65n/hal_delay.c  .generated_files/b9aae473da17605d2205a02a45cef15b60534efd.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_delay.o ../../../../../MiniWin/hal/rx65n/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_lcd.o: ../../../../../MiniWin/hal/rx65n/hal_lcd.c  .generated_files/9d2e99ba39259ed6bd028ec17976078bc84ac058.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_lcd.o ../../../../../MiniWin/hal/rx65n/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_non_vol.o: ../../../../../MiniWin/hal/rx65n/hal_non_vol.c  .generated_files/b693962048026412152b7fb83e923aece8d8e7e5.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o ../../../../../MiniWin/hal/rx65n/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_timer.o: ../../../../../MiniWin/hal/rx65n/hal_timer.c  .generated_files/6d5c46b9f0e7766eccc8d53a1f587ba983b1cc2f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_timer.o ../../../../../MiniWin/hal/rx65n/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_touch.o: ../../../../../MiniWin/hal/rx65n/hal_touch.c  .generated_files/815ba49d18676307d50b27a650fdef70410315c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_touch.o ../../../../../MiniWin/hal/rx65n/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_delay.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c  .generated_files/95437effdad6cd26cd70d19ea34fd4ccba514c5d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_delay.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_delay.o ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_lcd.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c  .generated_files/b9061bd65aecd2c4c14ecccc0601859472417823.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_lcd.o ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_non_vol.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c  .generated_files/fd1daba2fb9913297fc63a6064d361af13d5075f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_non_vol.o ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_timer.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c  .generated_files/d7477a6d4fe1f909bb5c5838fc610db12e67381d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_timer.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_timer.o ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_touch.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c  .generated_files/7f2f2eab7f401a596b3fdfeaafbcb3e7553f9f71.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_touch.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_touch.o ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_delay.o: ../../../../../MiniWin/hal/stm32f407/hal_delay.c  .generated_files/348a3ed20837d841418939acc5bfbb72fa9cfc0b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_delay.o ../../../../../MiniWin/hal/stm32f407/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_lcd.o: ../../../../../MiniWin/hal/stm32f407/hal_lcd.c  .generated_files/b87c38020da60cef3b3b50b9fbe9871767be6102.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_lcd.o ../../../../../MiniWin/hal/stm32f407/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_non_vol.o: ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c  .generated_files/cc7ef6ba1b6767c91f7be12af84ef8d8dcb29ccc.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_timer.o: ../../../../../MiniWin/hal/stm32f407/hal_timer.c  .generated_files/d7b5b0ceaba0930050f7663c0762de3925783b4b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_timer.o ../../../../../MiniWin/hal/stm32f407/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_touch.o: ../../../../../MiniWin/hal/stm32f407/hal_touch.c  .generated_files/490239896f263b15349b079969c51bf28a99cc49.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_touch.o ../../../../../MiniWin/hal/stm32f407/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_delay.o: ../../../../../MiniWin/hal/stm32f429/hal_delay.c  .generated_files/9358658e9a6430a2149003b135834035798bdf32.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_delay.o ../../../../../MiniWin/hal/stm32f429/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_lcd.o: ../../../../../MiniWin/hal/stm32f429/hal_lcd.c  .generated_files/ff91d11574daafb4816505d4ee76477780134a71.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_lcd.o ../../../../../MiniWin/hal/stm32f429/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_non_vol.o: ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c  .generated_files/16f3107df15b1a989ac32a9c762863dabc250301.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_timer.o: ../../../../../MiniWin/hal/stm32f429/hal_timer.c  .generated_files/be74400821ee16cf6c6b415735c4f556304822c0.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_timer.o ../../../../../MiniWin/hal/stm32f429/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_touch.o: ../../../../../MiniWin/hal/stm32f429/hal_touch.c  .generated_files/d2ab226d3c72b16b024d370fb167cb8a50f57c60.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_touch.o ../../../../../MiniWin/hal/stm32f429/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_delay.o: ../../../../../MiniWin/hal/windows/hal_delay.c  .generated_files/9dad3ce0c58d82a97593dc6eddc687656cd3a97d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_delay.o ../../../../../MiniWin/hal/windows/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_lcd.o: ../../../../../MiniWin/hal/windows/hal_lcd.c  .generated_files/11476d6896ee2d35a44ba0b1973d9da45fda8775.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_lcd.o ../../../../../MiniWin/hal/windows/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_non_vol.o: ../../../../../MiniWin/hal/windows/hal_non_vol.c  .generated_files/a6951ae5d044d09789a9c289c26658dd8e38f687.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o ../../../../../MiniWin/hal/windows/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_timer.o: ../../../../../MiniWin/hal/windows/hal_timer.c  .generated_files/e6686a8f9bb1a5641539ba7e75864e37a70a4c54.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_timer.o ../../../../../MiniWin/hal/windows/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_touch.o: ../../../../../MiniWin/hal/windows/hal_touch.c  .generated_files/9acea04752312c51fc27a21cdb1c8e3379037b63.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_touch.o ../../../../../MiniWin/hal/windows/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/902303450/hal_init.o: ../../../../../MiniWin/hal/hal_init.c  .generated_files/309efa447e1eae9055e25ef906b357cb58f98a3.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/902303450" 
	@${RM} ${OBJECTDIR}/_ext/902303450/hal_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/902303450/hal_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/902303450/hal_init.o.d" -o ${OBJECTDIR}/_ext/902303450/hal_init.o ../../../../../MiniWin/hal/hal_init.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_arrow.o: ../../../../../MiniWin/ui/ui_arrow.c  .generated_files/18382aee586865fb7a36ca99b3b74325fcf05624.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_arrow.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_arrow.o ../../../../../MiniWin/ui/ui_arrow.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_button.o: ../../../../../MiniWin/ui/ui_button.c  .generated_files/71f39449cb29dbcf475a5d9b913e8246df5d1ff5.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_button.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_button.o ../../../../../MiniWin/ui/ui_button.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_check_box.o: ../../../../../MiniWin/ui/ui_check_box.c  .generated_files/b7af4bdc540a1199994531c494e75cc55e5d43a7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_check_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_check_box.o ../../../../../MiniWin/ui/ui_check_box.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_common.o: ../../../../../MiniWin/ui/ui_common.c  .generated_files/1582351632089100f854201769be58fec642bc5.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_common.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_common.o ../../../../../MiniWin/ui/ui_common.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_keyboard.o: ../../../../../MiniWin/ui/ui_keyboard.c  .generated_files/fe370a772f150bc70b746f36754072cc5c46a512.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o ../../../../../MiniWin/ui/ui_keyboard.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_keypad.o: ../../../../../MiniWin/ui/ui_keypad.c  .generated_files/7741a86d91c617160b9e56d788b4cdad78414636.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keypad.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_keypad.o ../../../../../MiniWin/ui/ui_keypad.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_label.o: ../../../../../MiniWin/ui/ui_label.c  .generated_files/260b3b348915da0ee616dc5b8eefa66a7ea82b47.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_label.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_label.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_label.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_label.o ../../../../../MiniWin/ui/ui_label.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_list_box.o: ../../../../../MiniWin/ui/ui_list_box.c  .generated_files/c8f4c5f859c9bc634e155a66024d60a3a718679.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_list_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_list_box.o ../../../../../MiniWin/ui/ui_list_box.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o: ../../../../../MiniWin/ui/ui_progress_bar.c  .generated_files/8b208aa207152ce8fec95dc529b66d2a8fac554c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o ../../../../../MiniWin/ui/ui_progress_bar.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_radio_button.o: ../../../../../MiniWin/ui/ui_radio_button.c  .generated_files/426ba640ab7bb19a436a06b07dafea42344b364f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o ../../../../../MiniWin/ui/ui_radio_button.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o: ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c  .generated_files/1fdc7f15ba1b65ca9a50fccc8a0922f69285f976.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o: ../../../../../MiniWin/ui/ui_scroll_bar_vert.c  .generated_files/4e032ca80aa2eb15ce9d38fc1f6390d6952469b0.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o ../../../../../MiniWin/ui/ui_scroll_bar_vert.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_tabs.o: ../../../../../MiniWin/ui/ui_tabs.c  .generated_files/8f6e9d4c395f14a8b62b9457d1057053af13881e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tabs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_tabs.o ../../../../../MiniWin/ui/ui_tabs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_text_box.o: ../../../../../MiniWin/ui/ui_text_box.c  .generated_files/93c0b39a5896ce155c98e6d53bfefffe03415e81.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_text_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_text_box.o ../../../../../MiniWin/ui/ui_text_box.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_tree.o: ../../../../../MiniWin/ui/ui_tree.c  .generated_files/b5cecc590240d81c2e048e247fa28f84f17cee15.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tree.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tree.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_tree.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_tree.o ../../../../../MiniWin/ui/ui_tree.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/calibrate.o: ../../../../../MiniWin/calibrate.c  .generated_files/5534a6787a53df798f3a350e1b1627d7718e0188.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/calibrate.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/calibrate.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/calibrate.o.d" -o ${OBJECTDIR}/_ext/59636182/calibrate.o ../../../../../MiniWin/calibrate.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin.o: ../../../../../MiniWin/miniwin.c  .generated_files/5a3e9a5d34488b78acb82bd06e391ca2f798b761.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin.o ../../../../../MiniWin/miniwin.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_debug.o: ../../../../../MiniWin/miniwin_debug.c  .generated_files/ffaf3d94c6cc8d1f9a4559cd0b97a5dc22c27750.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_debug.o ../../../../../MiniWin/miniwin_debug.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o: ../../../../../MiniWin/miniwin_message_queue.c  .generated_files/b2ca241ccf83671142affe1c2b11fccd0d8bd4b3.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o ../../../../../MiniWin/miniwin_message_queue.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_settings.o: ../../../../../MiniWin/miniwin_settings.c  .generated_files/29428ba66ff28a7795a78a21c987fd6452cb9180.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_settings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_settings.o ../../../../../MiniWin/miniwin_settings.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_touch.o: ../../../../../MiniWin/miniwin_touch.c  .generated_files/5f93424115bfc6dc48e178d96101e6956048457b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_touch.o ../../../../../MiniWin/miniwin_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o: ../../../../../MiniWin/miniwin_tree_container.c  .generated_files/8cb9c2c1d6fa741b537666c00435fbd9581c0403.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o ../../../../../MiniWin/miniwin_tree_container.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_utilities.o: ../../../../../MiniWin/miniwin_utilities.c  .generated_files/28074cdfb1a465461481249b6950508c81549662.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o ../../../../../MiniWin/miniwin_utilities.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/main.o: ../../../../../MiniWinFile_Common/main.c  .generated_files/31c461db1e51937c01906bca264c08139394a462.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/main.o.d" -o ${OBJECTDIR}/_ext/165771656/main.o ../../../../../MiniWinFile_Common/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/miniwin_user.o: ../../../../../MiniWinFile_Common/miniwin_user.c  .generated_files/f90321a89288b57a71efdf621f119ebd8ed5df67.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/miniwin_user.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/miniwin_user.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/miniwin_user.o.d" -o ${OBJECTDIR}/_ext/165771656/miniwin_user.o ../../../../../MiniWinFile_Common/miniwin_user.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_file.o: ../../../../../MiniWinFile_Common/window_file.c  .generated_files/63f16cefac693705195988526c72309cd84a4ade.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_file.o.d" -o ${OBJECTDIR}/_ext/165771656/window_file.o ../../../../../MiniWinFile_Common/window_file.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_file_tree.o: ../../../../../MiniWinFile_Common/window_file_tree.c  .generated_files/2057465849734acf8d28d80c63baa345ce297557.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file_tree.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file_tree.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_file_tree.o.d" -o ${OBJECTDIR}/_ext/165771656/window_file_tree.o ../../../../../MiniWinFile_Common/window_file_tree.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_image.o: ../../../../../MiniWinFile_Common/window_image.c  .generated_files/7b9619ae9d2008164f94767e1788a35619338fea.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_image.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_image.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_image.o.d" -o ${OBJECTDIR}/_ext/165771656/window_image.o ../../../../../MiniWinFile_Common/window_image.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_selection.o: ../../../../../MiniWinFile_Common/window_selection.c  .generated_files/67d027a8d7e4170237339138dd5d40666e2c691.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_selection.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_selection.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_selection.o.d" -o ${OBJECTDIR}/_ext/165771656/window_selection.o ../../../../../MiniWinFile_Common/window_selection.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_text.o: ../../../../../MiniWinFile_Common/window_text.c  .generated_files/e17f342ddc74e538373fafe2557679ada627f50f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_text.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_text.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_text.o.d" -o ${OBJECTDIR}/_ext/165771656/window_text.o ../../../../../MiniWinFile_Common/window_text.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1445274692/app.o: ../../src/app.c  .generated_files/5452603c52582f08f24571412e6f72f09cded974.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1445274692" 
	@${RM} ${OBJECTDIR}/_ext/1445274692/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1445274692/app.o.d" -o ${OBJECTDIR}/_ext/1445274692/app.o ../../src/app.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/8476c7e8d07fa97d83bad38532aa930cfff30ae7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1249264884/plib_coretimer.o: ../src/config/default/peripheral/coretimer/plib_coretimer.c  .generated_files/4840fc90ec6b977380b943d5dd2ffd09a180bd25.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1249264884" 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ../src/config/default/peripheral/coretimer/plib_coretimer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/b62d1f68da85a0b8060020bf2232b0c774574314.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/5e3f3d64cb66039281c7d0e39b06fc3880c19887.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60176403/plib_nvm.o: ../src/config/default/peripheral/nvm/plib_nvm.c  .generated_files/69ae96cea2c864ddfa235675d1b9dab17067bd57.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60176403" 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ../src/config/default/peripheral/nvm/plib_nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/298189674/plib_spi2_master.o: ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c  .generated_files/7f7301a4ea2d3ba3909f098d2dd684996333206f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/298189674" 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d" -o ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/298189674/plib_spi1_master.o: ../src/config/default/peripheral/spi/spi_master/plib_spi1_master.c  .generated_files/23c6963f1c95dd5636ef56a4265dfc69ff555b2a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/298189674" 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/298189674/plib_spi1_master.o.d" -o ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o ../src/config/default/peripheral/spi/spi_master/plib_spi1_master.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60181895/plib_tmr2.o: ../src/config/default/peripheral/tmr/plib_tmr2.c  .generated_files/16fe116ea9b2c681b20cccd8ebcf7f0a37f2c9bd.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ../src/config/default/peripheral/tmr/plib_tmr2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60181895/plib_tmr3.o: ../src/config/default/peripheral/tmr/plib_tmr3.c  .generated_files/50923123ab9bdd25a0bf29cf27fb7537f8d206f3.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr3.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr3.o ../src/config/default/peripheral/tmr/plib_tmr3.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/c35d8827b27545f70d582fb9c2bc8dfff9287989.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/82dc904a9fc7169f83df654172da44d0c9e1f481.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/e4e7a804e6f25979be6f0d9d6e74d5e3a19c6a4.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/30bfb45495f1fb6eee3bee95a42cb1db3baf9ea7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/ff.o: ../../FatFS/ff.c  .generated_files/629b1a63ce55adef1af9ec5fbb8af828decfecbb.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/ff.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/ff.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/ff.o.d" -o ${OBJECTDIR}/_ext/1592496102/ff.o ../../FatFS/ff.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/sdmm.o: ../../FatFS/sdmm.c  .generated_files/7099138dcab718c10736ca43b09c8ab2723b5fa4.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/sdmm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/sdmm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/sdmm.o.d" -o ${OBJECTDIR}/_ext/1592496102/sdmm.o ../../FatFS/sdmm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/spi_driver.o: ../../FatFS/spi_driver.c  .generated_files/637b75970d026fdc8f896f1ccf4ff6c896431e05.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/spi_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/spi_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/spi_driver.o.d" -o ${OBJECTDIR}/_ext/1592496102/spi_driver.o ../../FatFS/spi_driver.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/backspace_key.o: ../../../../../MiniWin/bitmaps/backspace_key.c  .generated_files/7a04574af081ad83b2650b9fe861e4d3ba489049.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/backspace_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/backspace_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/backspace_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/backspace_key.o ../../../../../MiniWin/bitmaps/backspace_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/close_icon.o: ../../../../../MiniWin/bitmaps/close_icon.c  .generated_files/19f71169b095e9f66f521620a8dc34de336ae562.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/close_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/close_icon.o ../../../../../MiniWin/bitmaps/close_icon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/close_icon_large.o: ../../../../../MiniWin/bitmaps/close_icon_large.c  .generated_files/bad6dffba54281d6aefcc0480dd6ebc371c6542b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/close_icon_large.o ../../../../../MiniWin/bitmaps/close_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/file_icon_large.o: ../../../../../MiniWin/bitmaps/file_icon_large.c  .generated_files/5e821847279e714d8d38c304a32f5c822277538.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/file_icon_large.o ../../../../../MiniWin/bitmaps/file_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/file_icon_small.o: ../../../../../MiniWin/bitmaps/file_icon_small.c  .generated_files/5f94913709eb8211b372693feb8bbe8523834479.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/file_icon_small.o ../../../../../MiniWin/bitmaps/file_icon_small.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o: ../../../../../MiniWin/bitmaps/folder_close_icon_large.c  .generated_files/195b5ba7f49cc03fc38b66ec7de2aa072e88fd01.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o ../../../../../MiniWin/bitmaps/folder_close_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o: ../../../../../MiniWin/bitmaps/folder_close_icon_small.c  .generated_files/3bd6eb49845c0f04b2decc5416f3f277a3110ce2.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o ../../../../../MiniWin/bitmaps/folder_close_icon_small.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_icon_large.o: ../../../../../MiniWin/bitmaps/folder_icon_large.c  .generated_files/c0592babd85bf9b3d4a80b66a2c963fb856c4763.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o ../../../../../MiniWin/bitmaps/folder_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_icon_small.o: ../../../../../MiniWin/bitmaps/folder_icon_small.c  .generated_files/d0fc08d00eb9a9755cf8b49cb5430b2c44ce656d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o ../../../../../MiniWin/bitmaps/folder_icon_small.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o: ../../../../../MiniWin/bitmaps/folder_open_icon_large.c  .generated_files/f06f0d5c1356b25e84b1e1f7647aceea51efb184.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o ../../../../../MiniWin/bitmaps/folder_open_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o: ../../../../../MiniWin/bitmaps/folder_open_icon_small.c  .generated_files/239bd46f5829423c103b4b1e7cd83cd679eea67f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o ../../../../../MiniWin/bitmaps/folder_open_icon_small.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/let_key.o: ../../../../../MiniWin/bitmaps/let_key.c  .generated_files/808a1f2d8b4e186ac5ea920acd6a02ff6506700e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/let_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/let_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/let_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/let_key.o ../../../../../MiniWin/bitmaps/let_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/maximise_icon.o: ../../../../../MiniWin/bitmaps/maximise_icon.c  .generated_files/9adfff1a6e16fd8928fa15a5cd5845d6a4e2c0c0.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/maximise_icon.o ../../../../../MiniWin/bitmaps/maximise_icon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o: ../../../../../MiniWin/bitmaps/maximise_icon_large.c  .generated_files/abcdf38c6b5c910e7be557110add043fc91f9afa.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o ../../../../../MiniWin/bitmaps/maximise_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/minimise_icon.o: ../../../../../MiniWin/bitmaps/minimise_icon.c  .generated_files/174b7edd25392fb1dbd5d42fac911f99971ad66d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/minimise_icon.o ../../../../../MiniWin/bitmaps/minimise_icon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o: ../../../../../MiniWin/bitmaps/minimise_icon_large.c  .generated_files/e853b7a22635c94c70352660f2f2f4fc7d88f1e0.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o ../../../../../MiniWin/bitmaps/minimise_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/num_key.o: ../../../../../MiniWin/bitmaps/num_key.c  .generated_files/21b889457247e5eb68af618df6c5e6ed5606784c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/num_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/num_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/num_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/num_key.o ../../../../../MiniWin/bitmaps/num_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/resize_icon.o: ../../../../../MiniWin/bitmaps/resize_icon.c  .generated_files/8e1e2b793c3ebee74798492b8950ce553be6bcd8.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/resize_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/resize_icon.o ../../../../../MiniWin/bitmaps/resize_icon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/resize_icon_large.o: ../../../../../MiniWin/bitmaps/resize_icon_large.c  .generated_files/3ab633c54342e3d3ab5444fd2f79819621e4a2e3.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o ../../../../../MiniWin/bitmaps/resize_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/shift_key.o: ../../../../../MiniWin/bitmaps/shift_key.c  .generated_files/bc1aa2dc1790d3b01abb01c57c6addb264578103.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/shift_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/shift_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/shift_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/shift_key.o ../../../../../MiniWin/bitmaps/shift_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/sym_key.o: ../../../../../MiniWin/bitmaps/sym_key.c  .generated_files/b5368ab23fa770987919dc2c6981bdea2b7f330e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/sym_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/sym_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/sym_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/sym_key.o ../../../../../MiniWin/bitmaps/sym_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/tick.o: ../../../../../MiniWin/bitmaps/tick.c  .generated_files/1bda78d2ecf0d4ae9c547b83a8f8fc151a69cb89.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/tick.o.d" -o ${OBJECTDIR}/_ext/1275709973/tick.o ../../../../../MiniWin/bitmaps/tick.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/tick_large.o: ../../../../../MiniWin/bitmaps/tick_large.c  .generated_files/d0770cb02f3704c78b03ec783eb1f9975447059f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/tick_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/tick_large.o ../../../../../MiniWin/bitmaps/tick_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o: ../../../../../MiniWin/dialogs/dialog_colour_chooser.c  .generated_files/197ca45dae19bbb7da1eafb7e2a75f71eeb736a3.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o ../../../../../MiniWin/dialogs/dialog_colour_chooser.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o: ../../../../../MiniWin/dialogs/dialog_date_chooser.c  .generated_files/845ea9384296a4660cbe54cea3e77c1036391dde.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o ../../../../../MiniWin/dialogs/dialog_date_chooser.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o: ../../../../../MiniWin/dialogs/dialog_file_chooser.c  .generated_files/489f8042a4a198839f8234d0614ff84526f0763d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o ../../../../../MiniWin/dialogs/dialog_file_chooser.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_number_entry.o: ../../../../../MiniWin/dialogs/dialog_number_entry.c  .generated_files/ffd2a6738ad48eba30680b88b50d9d9ff3723ca1.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o ../../../../../MiniWin/dialogs/dialog_number_entry.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_one_button.o: ../../../../../MiniWin/dialogs/dialog_one_button.c  .generated_files/54e6f10eee69cb4baa0090fc4d04c64f36fb3728.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_one_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_one_button.o ../../../../../MiniWin/dialogs/dialog_one_button.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_text_entry.o: ../../../../../MiniWin/dialogs/dialog_text_entry.c  .generated_files/a1d15da47f7ec4f1b880ee823c3526435b0aed58.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o ../../../../../MiniWin/dialogs/dialog_text_entry.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o: ../../../../../MiniWin/dialogs/dialog_time_chooser.c  .generated_files/d7abb3988d4ba149a3ceeef19e723c7d93413f9c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o ../../../../../MiniWin/dialogs/dialog_time_chooser.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_two_button.o: ../../../../../MiniWin/dialogs/dialog_two_button.c  .generated_files/21e163769ac257a1efc9274e6aeec8e6ea9d5c93.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_two_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_two_button.o ../../../../../MiniWin/dialogs/dialog_two_button.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font12.o: ../../../../../MiniWin/gl/fonts/bitmapped/font12.c  .generated_files/2c2d2bb173568e824a66d2345b3f00bbb092a026.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font12.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font12.o.d" -o ${OBJECTDIR}/_ext/194049764/font12.o ../../../../../MiniWin/gl/fonts/bitmapped/font12.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font16.o: ../../../../../MiniWin/gl/fonts/bitmapped/font16.c  .generated_files/d7decd5d3bc87fb4f4f76f4aac688489d061e07a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font16.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font16.o.d" -o ${OBJECTDIR}/_ext/194049764/font16.o ../../../../../MiniWin/gl/fonts/bitmapped/font16.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font20.o: ../../../../../MiniWin/gl/fonts/bitmapped/font20.c  .generated_files/4906986151d78a65e7e3a1cc6ae9db434f88c3b4.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font20.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font20.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font20.o.d" -o ${OBJECTDIR}/_ext/194049764/font20.o ../../../../../MiniWin/gl/fonts/bitmapped/font20.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font24.o: ../../../../../MiniWin/gl/fonts/bitmapped/font24.c  .generated_files/afbfb15d3ef0222c58fdfa44dda588b451c2fb42.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font24.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font24.o.d" -o ${OBJECTDIR}/_ext/194049764/font24.o ../../../../../MiniWin/gl/fonts/bitmapped/font24.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font9.o: ../../../../../MiniWin/gl/fonts/bitmapped/font9.c  .generated_files/55871abdf35d4ca8d3ca500e91b256e7ff21936d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font9.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font9.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font9.o.d" -o ${OBJECTDIR}/_ext/194049764/font9.o ../../../../../MiniWin/gl/fonts/bitmapped/font9.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/gl_title_font.o: ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c  .generated_files/9d21a926c78d91497790b9f495d1d13ca907c585.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/gl_title_font.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/gl_title_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/gl_title_font.o.d" -o ${OBJECTDIR}/_ext/194049764/gl_title_font.o ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_bwfont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c  .generated_files/63145883c499b5f04e5e33c972e8619c55724209.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_encoding.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c  .generated_files/3a3d7ae824742fe8cb53806a3d86075d3437ac0e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_encoding.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_encoding.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_font.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c  .generated_files/ad81f894c1684af14fe5cd1aa2201a19d1f5e46a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_font.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_font.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_font.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_justify.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c  .generated_files/c57498d66b47bb23ba7bfd398e9b47b007831345.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_justify.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_justify.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_justify.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_justify.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_kerning.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c  .generated_files/870be6822e7790204814c9743c15b4412bee142d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_kerning.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_kerning.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_rlefont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c  .generated_files/17476534f64c6ed432e45675c7e28261cd392f81.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c  .generated_files/b4afa09960f8205d27c975c5d227770189e9bbfa.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c  .generated_files/2d96a41f716562c97bd67c2aeb880749aa5515.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o: ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c  .generated_files/dd323e77cb3a9cfc820355f532ef5ad479e25981.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d" -o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o: ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c  .generated_files/77406ee4d7a19da0e89ee70b364a0b6b821b1592.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d" -o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o: ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c  .generated_files/fbe7b36ed8db9eb6a349423b992fb08ed63fa1b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d" -o ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494914114/gl.o: ../../../../../MiniWin/gl/gl.c  .generated_files/d786a63c6a4ef9ed593a5470e3f8e41ffbc619a5.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494914114" 
	@${RM} ${OBJECTDIR}/_ext/1494914114/gl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494914114/gl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494914114/gl.o.d" -o ${OBJECTDIR}/_ext/1494914114/gl.o ../../../../../MiniWin/gl/gl.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_delay.o: ../../../../../MiniWin/hal/DevKitC/hal_delay.c  .generated_files/60f5275f4bc2625b7988aa7cb0cdb442b18f9520.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_delay.o ../../../../../MiniWin/hal/DevKitC/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_lcd.o: ../../../../../MiniWin/hal/DevKitC/hal_lcd.c  .generated_files/c8a200586b21d7f2a84cf4a87ed2b23673214f53.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_lcd.o ../../../../../MiniWin/hal/DevKitC/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_non_vol.o: ../../../../../MiniWin/hal/DevKitC/hal_non_vol.c  .generated_files/7e6c6a4184e9b43c1ed1d8b454f4f58690bb66f3.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o ../../../../../MiniWin/hal/DevKitC/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_timer.o: ../../../../../MiniWin/hal/DevKitC/hal_timer.c  .generated_files/5d04e981817656e4972f24573035e263300137ba.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_timer.o ../../../../../MiniWin/hal/DevKitC/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_touch.o: ../../../../../MiniWin/hal/DevKitC/hal_touch.c  .generated_files/ab0c1d0f4e3524eeca8ebe137f865ee1d9848c2c.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_touch.o ../../../../../MiniWin/hal/DevKitC/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_delay.o: ../../../../../MiniWin/hal/linux/hal_delay.c  .generated_files/15f320df439fb8b1905f8912cda7cfb1e50e07f8.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_delay.o ../../../../../MiniWin/hal/linux/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_lcd.o: ../../../../../MiniWin/hal/linux/hal_lcd.c  .generated_files/3e2a83b3c0aafb5814e1ffc899ffb5cf413cad4b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_lcd.o ../../../../../MiniWin/hal/linux/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_non_vol.o: ../../../../../MiniWin/hal/linux/hal_non_vol.c  .generated_files/8bf4a9a211ec93292cbc6afde8b26d45b1f7114.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o ../../../../../MiniWin/hal/linux/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_timer.o: ../../../../../MiniWin/hal/linux/hal_timer.c  .generated_files/7c63723cef7afb99333ae2715bda944e9c143971.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_timer.o ../../../../../MiniWin/hal/linux/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_touch.o: ../../../../../MiniWin/hal/linux/hal_touch.c  .generated_files/5823b2169beb8562b2085bcb2044cd13fef303ed.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_touch.o ../../../../../MiniWin/hal/linux/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_delay.o: ../../../../../MiniWin/hal/lpc54628/hal_delay.c  .generated_files/b3c19e39a43573cb471fa10df928656dc1a3877e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_delay.o ../../../../../MiniWin/hal/lpc54628/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_lcd.o: ../../../../../MiniWin/hal/lpc54628/hal_lcd.c  .generated_files/cb3ad7203b6c8911fd7560b35d84ef2175c1744d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_lcd.o ../../../../../MiniWin/hal/lpc54628/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_non_vol.o: ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c  .generated_files/e52bb0f9b68acc3e80483c5228c4953b72b07d5f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_timer.o: ../../../../../MiniWin/hal/lpc54628/hal_timer.c  .generated_files/eaee8077a97fa9e07e909ee85fa8647c6947cfba.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_timer.o ../../../../../MiniWin/hal/lpc54628/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_touch.o: ../../../../../MiniWin/hal/lpc54628/hal_touch.c  .generated_files/5f385677801564d805ea2ddaaaad4c1156d24d1f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_touch.o ../../../../../MiniWin/hal/lpc54628/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_delay.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c  .generated_files/cdedf5cfac232ac199b469d3e124fd754aa311c5.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_delay.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_delay.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_lcd.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c  .generated_files/f41b7dc8d09948e7644a497c8e61ca7aa9c5a235.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_lcd.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_non_vol.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c  .generated_files/3b218d831374f46d9989dba3797d4aa907dec459.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_non_vol.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_timer.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c  .generated_files/44d05580b063c6ca27746a16ecf15be0d774a1d8.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_timer.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_timer.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_touch.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c  .generated_files/e47ab9d7919b4cf58476410931125a86daebec86.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_touch.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_touch.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_delay.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_delay.c  .generated_files/317a9284b3817e6f86918820a9a37ac16c07d1b8.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_delay.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_delay.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_lcd.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_lcd.c  .generated_files/31fe22e84b3545bae2a211338d96f56f51a33985.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_lcd.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_non_vol.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_non_vol.c  .generated_files/1bb11b6df2c61903f9ac8509a56043959023a5f8.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_non_vol.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_timer.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_timer.c  .generated_files/40660c3a5ed73e86f09ed94341900c4a36c612f0.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_timer.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_timer.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_touch.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_touch.c  .generated_files/4c607dba329cf9d5be3af150410934bb3cdf3d24.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_touch.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_touch.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_delay.o: ../../../../../MiniWin/hal/rx65n/hal_delay.c  .generated_files/b47474d93176589d182a5815617db7ecb1d73870.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_delay.o ../../../../../MiniWin/hal/rx65n/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_lcd.o: ../../../../../MiniWin/hal/rx65n/hal_lcd.c  .generated_files/16bf0c64d48145397a83b86b395a49d7cc3ac10d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_lcd.o ../../../../../MiniWin/hal/rx65n/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_non_vol.o: ../../../../../MiniWin/hal/rx65n/hal_non_vol.c  .generated_files/39951923ee7cb4432908c6f739d65bfa78853aac.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o ../../../../../MiniWin/hal/rx65n/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_timer.o: ../../../../../MiniWin/hal/rx65n/hal_timer.c  .generated_files/3a410bd454d9033db7108cc21515914be68ae82e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_timer.o ../../../../../MiniWin/hal/rx65n/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_touch.o: ../../../../../MiniWin/hal/rx65n/hal_touch.c  .generated_files/5a409399f1bacc9ec8eb8e6e9145fb22ec1b9ed6.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_touch.o ../../../../../MiniWin/hal/rx65n/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_delay.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c  .generated_files/736be2e6fe66818069f1b7dc882864d371c716b6.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_delay.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_delay.o ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_lcd.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c  .generated_files/374407d0368287f1c8b1b1a7048f932138dda7ae.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_lcd.o ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_non_vol.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c  .generated_files/b53701694112f5d478feeca60c16d3d65581c70d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_non_vol.o ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_timer.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c  .generated_files/e74622c16e09d9fa8f47cec4559f937e61672d66.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_timer.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_timer.o ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_touch.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c  .generated_files/685bb8e96d9a398755d90757acb9a220edee11df.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_touch.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_touch.o ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_delay.o: ../../../../../MiniWin/hal/stm32f407/hal_delay.c  .generated_files/c56fdc1e74d659ea4bdf82957f78c268d10b52d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_delay.o ../../../../../MiniWin/hal/stm32f407/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_lcd.o: ../../../../../MiniWin/hal/stm32f407/hal_lcd.c  .generated_files/7d27d87e32eacc601353fa9111b050c8a67b5151.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_lcd.o ../../../../../MiniWin/hal/stm32f407/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_non_vol.o: ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c  .generated_files/6d99a5c75f1dac9c795b25cc7b4fb1c33f4c5efb.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_timer.o: ../../../../../MiniWin/hal/stm32f407/hal_timer.c  .generated_files/41dcbec27fe4a7b37f7c76eb394c05df0ccf6cd2.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_timer.o ../../../../../MiniWin/hal/stm32f407/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_touch.o: ../../../../../MiniWin/hal/stm32f407/hal_touch.c  .generated_files/c39abec5904e19a19020ff5de9802e76d8fb1b27.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_touch.o ../../../../../MiniWin/hal/stm32f407/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_delay.o: ../../../../../MiniWin/hal/stm32f429/hal_delay.c  .generated_files/a3f8f0a4ad2aaa0603de3b55ebfad123b6823b74.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_delay.o ../../../../../MiniWin/hal/stm32f429/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_lcd.o: ../../../../../MiniWin/hal/stm32f429/hal_lcd.c  .generated_files/e9ed6079e01979a6bac70b0a0c19fb261b8f8400.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_lcd.o ../../../../../MiniWin/hal/stm32f429/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_non_vol.o: ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c  .generated_files/2b07f35d4adba22babf989f48b429691a7dca9b7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_timer.o: ../../../../../MiniWin/hal/stm32f429/hal_timer.c  .generated_files/a417949ec1cf841e1ea68c797e2bb989b76ecb02.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_timer.o ../../../../../MiniWin/hal/stm32f429/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_touch.o: ../../../../../MiniWin/hal/stm32f429/hal_touch.c  .generated_files/7ee94cc1b618726191ec4019537359b037c6ac75.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_touch.o ../../../../../MiniWin/hal/stm32f429/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_delay.o: ../../../../../MiniWin/hal/windows/hal_delay.c  .generated_files/7d49c720a1efc671d8c7444200f498ffec8d08c6.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_delay.o ../../../../../MiniWin/hal/windows/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_lcd.o: ../../../../../MiniWin/hal/windows/hal_lcd.c  .generated_files/a21703345c84f7a3003fc88e49084206e6ac1607.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_lcd.o ../../../../../MiniWin/hal/windows/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_non_vol.o: ../../../../../MiniWin/hal/windows/hal_non_vol.c  .generated_files/a121f30e309b8efc29365f746e3831d7c02abe03.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o ../../../../../MiniWin/hal/windows/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_timer.o: ../../../../../MiniWin/hal/windows/hal_timer.c  .generated_files/f4574340098e6ce739dc67b930525a440f52cbca.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_timer.o ../../../../../MiniWin/hal/windows/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_touch.o: ../../../../../MiniWin/hal/windows/hal_touch.c  .generated_files/c529b354c7ed75f8d34fd849ec9a31e798645340.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_touch.o ../../../../../MiniWin/hal/windows/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/902303450/hal_init.o: ../../../../../MiniWin/hal/hal_init.c  .generated_files/3e56e2aa1f2514a2573801c3ddc124712573e856.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/902303450" 
	@${RM} ${OBJECTDIR}/_ext/902303450/hal_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/902303450/hal_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/902303450/hal_init.o.d" -o ${OBJECTDIR}/_ext/902303450/hal_init.o ../../../../../MiniWin/hal/hal_init.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_arrow.o: ../../../../../MiniWin/ui/ui_arrow.c  .generated_files/5ffdb553e06f870cd5e3dc43f5b8f0788480fa52.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_arrow.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_arrow.o ../../../../../MiniWin/ui/ui_arrow.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_button.o: ../../../../../MiniWin/ui/ui_button.c  .generated_files/a6d3d083f60e35783f99af753a12bb896a0dd754.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_button.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_button.o ../../../../../MiniWin/ui/ui_button.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_check_box.o: ../../../../../MiniWin/ui/ui_check_box.c  .generated_files/4c2cdad448aff2609c0ef1811b5a5e7af75c7e61.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_check_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_check_box.o ../../../../../MiniWin/ui/ui_check_box.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_common.o: ../../../../../MiniWin/ui/ui_common.c  .generated_files/3579e8e60d004dab99525b21fc62ec1ae5589f77.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_common.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_common.o ../../../../../MiniWin/ui/ui_common.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_keyboard.o: ../../../../../MiniWin/ui/ui_keyboard.c  .generated_files/656f66b564b81a270f72262570440b7b7117221a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o ../../../../../MiniWin/ui/ui_keyboard.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_keypad.o: ../../../../../MiniWin/ui/ui_keypad.c  .generated_files/b86d0b0ed890af3348eacb7347289f372e13249e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keypad.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_keypad.o ../../../../../MiniWin/ui/ui_keypad.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_label.o: ../../../../../MiniWin/ui/ui_label.c  .generated_files/c94f61a2569b585ab860deff055ee3f6daff035d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_label.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_label.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_label.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_label.o ../../../../../MiniWin/ui/ui_label.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_list_box.o: ../../../../../MiniWin/ui/ui_list_box.c  .generated_files/b6be99c9b0ff74d11ab4268bcb419622f87874ef.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_list_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_list_box.o ../../../../../MiniWin/ui/ui_list_box.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o: ../../../../../MiniWin/ui/ui_progress_bar.c  .generated_files/760128aeb066611245df129856a4716f6a69f00b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o ../../../../../MiniWin/ui/ui_progress_bar.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_radio_button.o: ../../../../../MiniWin/ui/ui_radio_button.c  .generated_files/21097762d2f9a93f7a8a835fdc4d7380c4fb64d6.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o ../../../../../MiniWin/ui/ui_radio_button.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o: ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c  .generated_files/e97ec080368a2dc7e8c47476199f8fddaca4b88a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o: ../../../../../MiniWin/ui/ui_scroll_bar_vert.c  .generated_files/d939f63d17e1b9e31ce92921c0898a226499fb86.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o ../../../../../MiniWin/ui/ui_scroll_bar_vert.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_tabs.o: ../../../../../MiniWin/ui/ui_tabs.c  .generated_files/9dda18eb0ac211066e9c2af95fbd99b6ce538328.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tabs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_tabs.o ../../../../../MiniWin/ui/ui_tabs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_text_box.o: ../../../../../MiniWin/ui/ui_text_box.c  .generated_files/46714300d6bd87c85f7deee03f17a1f04f155848.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_text_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_text_box.o ../../../../../MiniWin/ui/ui_text_box.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_tree.o: ../../../../../MiniWin/ui/ui_tree.c  .generated_files/51717575e2a188f45fbc326098f0183ce6cd57e2.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tree.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tree.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_tree.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_tree.o ../../../../../MiniWin/ui/ui_tree.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/calibrate.o: ../../../../../MiniWin/calibrate.c  .generated_files/9a91f434876f5fcae93c5510fda7c9f7ea2e8c67.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/calibrate.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/calibrate.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/calibrate.o.d" -o ${OBJECTDIR}/_ext/59636182/calibrate.o ../../../../../MiniWin/calibrate.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin.o: ../../../../../MiniWin/miniwin.c  .generated_files/b344882055110d0d0b62a505d7c591721238db9b.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin.o ../../../../../MiniWin/miniwin.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_debug.o: ../../../../../MiniWin/miniwin_debug.c  .generated_files/f50763d826b0e8ce5eec81ec8fe2bb0bfa5303eb.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_debug.o ../../../../../MiniWin/miniwin_debug.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o: ../../../../../MiniWin/miniwin_message_queue.c  .generated_files/b4c11c1b59f070c9f6e05de1bedfb080a3a779aa.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o ../../../../../MiniWin/miniwin_message_queue.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_settings.o: ../../../../../MiniWin/miniwin_settings.c  .generated_files/baee9f0c6d0a43c68f3accfd3e4ac293ce59e52e.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_settings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_settings.o ../../../../../MiniWin/miniwin_settings.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_touch.o: ../../../../../MiniWin/miniwin_touch.c  .generated_files/959c9aa5e612c237465f793d2f53a5f96f36c5b1.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_touch.o ../../../../../MiniWin/miniwin_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o: ../../../../../MiniWin/miniwin_tree_container.c  .generated_files/c0a9a2703cb3c7767bfb935519f468aa953e007f.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o ../../../../../MiniWin/miniwin_tree_container.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_utilities.o: ../../../../../MiniWin/miniwin_utilities.c  .generated_files/d97d67c92c45df4e8d688c2e169a6242ce24ff1d.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o ../../../../../MiniWin/miniwin_utilities.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/main.o: ../../../../../MiniWinFile_Common/main.c  .generated_files/faabab1c91d3dfe450aa139f51af66196de2850.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/main.o.d" -o ${OBJECTDIR}/_ext/165771656/main.o ../../../../../MiniWinFile_Common/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/miniwin_user.o: ../../../../../MiniWinFile_Common/miniwin_user.c  .generated_files/6a210dbe3cfa9f44343bea035c3be650cc01e0cf.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/miniwin_user.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/miniwin_user.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/miniwin_user.o.d" -o ${OBJECTDIR}/_ext/165771656/miniwin_user.o ../../../../../MiniWinFile_Common/miniwin_user.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_file.o: ../../../../../MiniWinFile_Common/window_file.c  .generated_files/4d14260b63e00353103c3b0f7ad7b34a92aed7be.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_file.o.d" -o ${OBJECTDIR}/_ext/165771656/window_file.o ../../../../../MiniWinFile_Common/window_file.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_file_tree.o: ../../../../../MiniWinFile_Common/window_file_tree.c  .generated_files/1cd94728cad3f4bdaea0e270f0231fdad8c6f43a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file_tree.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file_tree.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_file_tree.o.d" -o ${OBJECTDIR}/_ext/165771656/window_file_tree.o ../../../../../MiniWinFile_Common/window_file_tree.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_image.o: ../../../../../MiniWinFile_Common/window_image.c  .generated_files/8c159b39d7a4f7e664ad2fdf3df6390736a70de7.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_image.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_image.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_image.o.d" -o ${OBJECTDIR}/_ext/165771656/window_image.o ../../../../../MiniWinFile_Common/window_image.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_selection.o: ../../../../../MiniWinFile_Common/window_selection.c  .generated_files/34168b90cdef36f84193c56f7fc7dd472eb784f8.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_selection.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_selection.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_selection.o.d" -o ${OBJECTDIR}/_ext/165771656/window_selection.o ../../../../../MiniWinFile_Common/window_selection.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_text.o: ../../../../../MiniWinFile_Common/window_text.c  .generated_files/1b3a21583d41d7bcbd2a657c399e2393ba302db8.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_text.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_text.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_text.o.d" -o ${OBJECTDIR}/_ext/165771656/window_text.o ../../../../../MiniWinFile_Common/window_text.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1445274692/app.o: ../../src/app.c  .generated_files/2d0afec77449c189ccb4258a9169fe1d5057562a.flag .generated_files/3eda10ae19fa762b9b018eebb81f511d750eb34.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1445274692" 
	@${RM} ${OBJECTDIR}/_ext/1445274692/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1445274692/app.o.d" -o ${OBJECTDIR}/_ext/1445274692/app.o ../../src/app.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MiniWinFile.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/config/default/p32MZ2048EFM100.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -mreserve=prog@0x1D1FC000:0x1D1FFFFF -o dist/${CND_CONF}/${IMAGE_TYPE}/MiniWinFile.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x37F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MiniWinFile.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/default/p32MZ2048EFM100.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mreserve=prog@0x1D1FC000:0x1D1FFFFF -o dist/${CND_CONF}/${IMAGE_TYPE}/MiniWinFile.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MiniWinFile.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
