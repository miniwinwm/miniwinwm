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
FINAL_IMAGE=${DISTDIR}/MiniWinFile.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/MiniWinFile.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/MiniWinFile.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

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
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/flags/default/114f26ecb4d74721aec7adbd2c9d265db63b7f35 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1249264884/plib_coretimer.o: ../src/config/default/peripheral/coretimer/plib_coretimer.c  .generated_files/flags/default/9824aab443db3bd176cb32d20425771403097ea1 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1249264884" 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ../src/config/default/peripheral/coretimer/plib_coretimer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/flags/default/d45e295f4f5b63d53e13dad8cd4ab619b97413e2 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/flags/default/1f41bac4d0ef1728e79b0d7872111122c552d10c .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60176403/plib_nvm.o: ../src/config/default/peripheral/nvm/plib_nvm.c  .generated_files/flags/default/d0c5f887bce536a21ef4f44c1bcae23a8755a69b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/60176403" 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ../src/config/default/peripheral/nvm/plib_nvm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/298189674/plib_spi2_master.o: ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c  .generated_files/flags/default/eccacbfda3cc50e211f03feae4d79df9f8358f04 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/298189674" 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d" -o ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/298189674/plib_spi1_master.o: ../src/config/default/peripheral/spi/spi_master/plib_spi1_master.c  .generated_files/flags/default/3cc4d47a9ad282e276ec1d42ba0c176a0666bcc2 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/298189674" 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/298189674/plib_spi1_master.o.d" -o ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o ../src/config/default/peripheral/spi/spi_master/plib_spi1_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60181895/plib_tmr2.o: ../src/config/default/peripheral/tmr/plib_tmr2.c  .generated_files/flags/default/5fafbb639a6086689e253ccfe6ffe089bded953c .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ../src/config/default/peripheral/tmr/plib_tmr2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60181895/plib_tmr3.o: ../src/config/default/peripheral/tmr/plib_tmr3.c  .generated_files/flags/default/5f4238ee95b1423c757cf7388eb62fc11840fb71 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr3.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr3.o ../src/config/default/peripheral/tmr/plib_tmr3.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/825a8953baf1714901f29896ba0507f803207be2 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/flags/default/ebfc88aacfd3b724f272f3e3b1de72c9d1dd0bb5 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/flags/default/a6aadd05f3dbd45706888bceca0c56f901b2a023 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/flags/default/bf1b7d5e07b6cd57ec7d7331244e3fb5e99c2bbc .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/ff.o: ../../FatFS/ff.c  .generated_files/flags/default/4ca67839b3beb133a942f2881be414aeb2b6cba3 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/ff.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/ff.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/ff.o.d" -o ${OBJECTDIR}/_ext/1592496102/ff.o ../../FatFS/ff.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/sdmm.o: ../../FatFS/sdmm.c  .generated_files/flags/default/4fe4d286ce04a2f2827948748314aa46cf503382 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/sdmm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/sdmm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/sdmm.o.d" -o ${OBJECTDIR}/_ext/1592496102/sdmm.o ../../FatFS/sdmm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/spi_driver.o: ../../FatFS/spi_driver.c  .generated_files/flags/default/448e0b2953712f9c28991bd949142c09903d2dd6 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/spi_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/spi_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/spi_driver.o.d" -o ${OBJECTDIR}/_ext/1592496102/spi_driver.o ../../FatFS/spi_driver.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/backspace_key.o: ../../../../../MiniWin/bitmaps/backspace_key.c  .generated_files/flags/default/99883c21490e0f417bd580bfbcfa3aa659aa9758 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/backspace_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/backspace_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/backspace_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/backspace_key.o ../../../../../MiniWin/bitmaps/backspace_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/close_icon.o: ../../../../../MiniWin/bitmaps/close_icon.c  .generated_files/flags/default/511767541082ff49ce68bb1dcef1ac24bbccf4b7 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/close_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/close_icon.o ../../../../../MiniWin/bitmaps/close_icon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/close_icon_large.o: ../../../../../MiniWin/bitmaps/close_icon_large.c  .generated_files/flags/default/28de7d6dab2f550cfb5c504c2d84057bb1c3e9cc .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/close_icon_large.o ../../../../../MiniWin/bitmaps/close_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/file_icon_large.o: ../../../../../MiniWin/bitmaps/file_icon_large.c  .generated_files/flags/default/1f119c71b2316bc9900ef3977a6f1e854f4217c5 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/file_icon_large.o ../../../../../MiniWin/bitmaps/file_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/file_icon_small.o: ../../../../../MiniWin/bitmaps/file_icon_small.c  .generated_files/flags/default/1f9e657a546e99c9956483fc94a1e5f7b97f03f2 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/file_icon_small.o ../../../../../MiniWin/bitmaps/file_icon_small.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o: ../../../../../MiniWin/bitmaps/folder_close_icon_large.c  .generated_files/flags/default/41633d724dd603751821496e1370993a2872f343 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o ../../../../../MiniWin/bitmaps/folder_close_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o: ../../../../../MiniWin/bitmaps/folder_close_icon_small.c  .generated_files/flags/default/68219602ebe3b2f6af128839d3543d6a0bb4c6ef .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o ../../../../../MiniWin/bitmaps/folder_close_icon_small.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_icon_large.o: ../../../../../MiniWin/bitmaps/folder_icon_large.c  .generated_files/flags/default/bc7061c76df7b831c64c2e4a27e5b6d0a073b957 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o ../../../../../MiniWin/bitmaps/folder_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_icon_small.o: ../../../../../MiniWin/bitmaps/folder_icon_small.c  .generated_files/flags/default/6cc398dc7abad52b60ea52798df4016080a254eb .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o ../../../../../MiniWin/bitmaps/folder_icon_small.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o: ../../../../../MiniWin/bitmaps/folder_open_icon_large.c  .generated_files/flags/default/464412a3e2addf322e41094912bcb218b334ee35 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o ../../../../../MiniWin/bitmaps/folder_open_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o: ../../../../../MiniWin/bitmaps/folder_open_icon_small.c  .generated_files/flags/default/fb46029ccc331d0035ce27971b5559bd29096cee .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o ../../../../../MiniWin/bitmaps/folder_open_icon_small.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/let_key.o: ../../../../../MiniWin/bitmaps/let_key.c  .generated_files/flags/default/d72b2cc7c4f997d94c44b8c7dec0bd56b6421d71 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/let_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/let_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/let_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/let_key.o ../../../../../MiniWin/bitmaps/let_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/maximise_icon.o: ../../../../../MiniWin/bitmaps/maximise_icon.c  .generated_files/flags/default/8c734a88a9a2281fde7393be5a9ff9853a8f245a .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/maximise_icon.o ../../../../../MiniWin/bitmaps/maximise_icon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o: ../../../../../MiniWin/bitmaps/maximise_icon_large.c  .generated_files/flags/default/2fe6e8ba6b20ce90530d15f78c150ed2cc4937f7 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o ../../../../../MiniWin/bitmaps/maximise_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/minimise_icon.o: ../../../../../MiniWin/bitmaps/minimise_icon.c  .generated_files/flags/default/af03504b709d5dcd9c3583d63f669ad96a4fdf8 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/minimise_icon.o ../../../../../MiniWin/bitmaps/minimise_icon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o: ../../../../../MiniWin/bitmaps/minimise_icon_large.c  .generated_files/flags/default/2937a7e3ba96f34dfa27117b39b83366ffb5d33c .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o ../../../../../MiniWin/bitmaps/minimise_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/num_key.o: ../../../../../MiniWin/bitmaps/num_key.c  .generated_files/flags/default/489434c5cafa72acdc88cb94f9e9ce405b199ca2 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/num_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/num_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/num_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/num_key.o ../../../../../MiniWin/bitmaps/num_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/resize_icon.o: ../../../../../MiniWin/bitmaps/resize_icon.c  .generated_files/flags/default/70b72555544fe9f5bc630c0f3c5b6b6c21fb530c .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/resize_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/resize_icon.o ../../../../../MiniWin/bitmaps/resize_icon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/resize_icon_large.o: ../../../../../MiniWin/bitmaps/resize_icon_large.c  .generated_files/flags/default/cc146b5170041841b42b06304b3d0f961641d1d0 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o ../../../../../MiniWin/bitmaps/resize_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/shift_key.o: ../../../../../MiniWin/bitmaps/shift_key.c  .generated_files/flags/default/9db2a68e97dffc50fe48d7cfb73aa2a0b772ffd0 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/shift_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/shift_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/shift_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/shift_key.o ../../../../../MiniWin/bitmaps/shift_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/sym_key.o: ../../../../../MiniWin/bitmaps/sym_key.c  .generated_files/flags/default/812d797e71789b42cf67ebe3bd0c394a2bd68c16 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/sym_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/sym_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/sym_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/sym_key.o ../../../../../MiniWin/bitmaps/sym_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/tick.o: ../../../../../MiniWin/bitmaps/tick.c  .generated_files/flags/default/91ad1e1002d8c27fa52ccc53b252cf54dbe24b16 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/tick.o.d" -o ${OBJECTDIR}/_ext/1275709973/tick.o ../../../../../MiniWin/bitmaps/tick.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/tick_large.o: ../../../../../MiniWin/bitmaps/tick_large.c  .generated_files/flags/default/7c77d1d129e11c9f80175345566eea97aed1666a .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/tick_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/tick_large.o ../../../../../MiniWin/bitmaps/tick_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o: ../../../../../MiniWin/dialogs/dialog_colour_chooser.c  .generated_files/flags/default/cf2f02842f7c880cfc2c382b503840d4df5f604d .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o ../../../../../MiniWin/dialogs/dialog_colour_chooser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o: ../../../../../MiniWin/dialogs/dialog_date_chooser.c  .generated_files/flags/default/339518d5fdc8ae0ea5d3dd9dba46f6e605ab6e9b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o ../../../../../MiniWin/dialogs/dialog_date_chooser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o: ../../../../../MiniWin/dialogs/dialog_file_chooser.c  .generated_files/flags/default/2c6a3aab903b93801db82c41ac3bf750055e4054 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o ../../../../../MiniWin/dialogs/dialog_file_chooser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_number_entry.o: ../../../../../MiniWin/dialogs/dialog_number_entry.c  .generated_files/flags/default/62aea14a33a954ea5913b1d64ed8c61ad64bfbdc .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o ../../../../../MiniWin/dialogs/dialog_number_entry.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_one_button.o: ../../../../../MiniWin/dialogs/dialog_one_button.c  .generated_files/flags/default/94d0cde4786781e288bbddf7b02d5c91b8e74eb3 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_one_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_one_button.o ../../../../../MiniWin/dialogs/dialog_one_button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_text_entry.o: ../../../../../MiniWin/dialogs/dialog_text_entry.c  .generated_files/flags/default/14a96ac834ce152c5680a37f9ecb8a5cef453725 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o ../../../../../MiniWin/dialogs/dialog_text_entry.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o: ../../../../../MiniWin/dialogs/dialog_time_chooser.c  .generated_files/flags/default/1073541475111dc00a40ec8db1784d374592cfb1 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o ../../../../../MiniWin/dialogs/dialog_time_chooser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_two_button.o: ../../../../../MiniWin/dialogs/dialog_two_button.c  .generated_files/flags/default/345cd014bbedcd2cc6852cb1c5625843454e5f40 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_two_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_two_button.o ../../../../../MiniWin/dialogs/dialog_two_button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font12.o: ../../../../../MiniWin/gl/fonts/bitmapped/font12.c  .generated_files/flags/default/87aad6ba6871f8a2bdf26919492179e8da8ba5b8 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font12.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font12.o.d" -o ${OBJECTDIR}/_ext/194049764/font12.o ../../../../../MiniWin/gl/fonts/bitmapped/font12.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font16.o: ../../../../../MiniWin/gl/fonts/bitmapped/font16.c  .generated_files/flags/default/58e6d58aff9243e8e34dd70c4a488c11fee1fd56 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font16.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font16.o.d" -o ${OBJECTDIR}/_ext/194049764/font16.o ../../../../../MiniWin/gl/fonts/bitmapped/font16.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font20.o: ../../../../../MiniWin/gl/fonts/bitmapped/font20.c  .generated_files/flags/default/cdc86ae0a5355d9db2c3c0d98d82aa7ec8c7369f .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font20.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font20.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font20.o.d" -o ${OBJECTDIR}/_ext/194049764/font20.o ../../../../../MiniWin/gl/fonts/bitmapped/font20.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font24.o: ../../../../../MiniWin/gl/fonts/bitmapped/font24.c  .generated_files/flags/default/f4b1b6782edeec7e4a81f987217a5ed543c25218 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font24.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font24.o.d" -o ${OBJECTDIR}/_ext/194049764/font24.o ../../../../../MiniWin/gl/fonts/bitmapped/font24.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font9.o: ../../../../../MiniWin/gl/fonts/bitmapped/font9.c  .generated_files/flags/default/b3c1577ff9d8d77085037b3e9758e858ab50e8e1 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font9.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font9.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font9.o.d" -o ${OBJECTDIR}/_ext/194049764/font9.o ../../../../../MiniWin/gl/fonts/bitmapped/font9.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/gl_title_font.o: ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c  .generated_files/flags/default/977882242c0b4cfc96793b1b3b355810d2fab3f9 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/gl_title_font.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/gl_title_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/gl_title_font.o.d" -o ${OBJECTDIR}/_ext/194049764/gl_title_font.o ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_bwfont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c  .generated_files/flags/default/bd8c11e3e2af60e189f3ae809dcf519fc1b342cd .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_encoding.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c  .generated_files/flags/default/3d728fb447e17ffec0902e92535628bc1fc5c30 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_encoding.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_encoding.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_font.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c  .generated_files/flags/default/9bdbb29fb82153fd089f83bfc923dbc2c9a523be .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_font.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_font.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_font.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_justify.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c  .generated_files/flags/default/fe75de3ea9d9f725a6b1bcc738f2953c3c9e6db0 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_justify.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_justify.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_justify.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_justify.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_kerning.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c  .generated_files/flags/default/9a97dd254fe1fcba86aa38459a45a9c9c4cbef04 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_kerning.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_kerning.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_rlefont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c  .generated_files/flags/default/4a126fc8129fae400c714dcb9e60872287c97d9 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c  .generated_files/flags/default/bbe4694225f8a7bba51ab06e73d46636a145df28 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c  .generated_files/flags/default/4df5fe2ca58f332be8445b4a7347d0b5c4250898 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o: ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c  .generated_files/flags/default/3a8a9bd448c079b7ec8f88da477e84295cf80467 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d" -o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o: ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c  .generated_files/flags/default/c8495cbe8d916aa117a4c16467ca58eba8ec43c3 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d" -o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o: ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c  .generated_files/flags/default/662d90c090a62f9ba327f8e73779a20dcd5109ec .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d" -o ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494914114/gl.o: ../../../../../MiniWin/gl/gl.c  .generated_files/flags/default/ae0cd96ca52675aac1b4ea6d4cf186f9c4cfb00c .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494914114" 
	@${RM} ${OBJECTDIR}/_ext/1494914114/gl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494914114/gl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494914114/gl.o.d" -o ${OBJECTDIR}/_ext/1494914114/gl.o ../../../../../MiniWin/gl/gl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_delay.o: ../../../../../MiniWin/hal/DevKitC/hal_delay.c  .generated_files/flags/default/e6d197055f14bfd4cfa406efe176e9c62844dc06 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_delay.o ../../../../../MiniWin/hal/DevKitC/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_lcd.o: ../../../../../MiniWin/hal/DevKitC/hal_lcd.c  .generated_files/flags/default/81cd0349fdee025747dcac3b9e1f41a7e6f9cf65 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_lcd.o ../../../../../MiniWin/hal/DevKitC/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_non_vol.o: ../../../../../MiniWin/hal/DevKitC/hal_non_vol.c  .generated_files/flags/default/e4367075acee8d60201842159bfde853e557abdc .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o ../../../../../MiniWin/hal/DevKitC/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_timer.o: ../../../../../MiniWin/hal/DevKitC/hal_timer.c  .generated_files/flags/default/1ae8c42a489755c38b8fdc1d71e7cbb096a41c59 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_timer.o ../../../../../MiniWin/hal/DevKitC/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_touch.o: ../../../../../MiniWin/hal/DevKitC/hal_touch.c  .generated_files/flags/default/ad6cbd38463a345577b309c6bfad560d5085285d .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_touch.o ../../../../../MiniWin/hal/DevKitC/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_delay.o: ../../../../../MiniWin/hal/linux/hal_delay.c  .generated_files/flags/default/a2554feceda73be2fcdc892e2a300a498c346f70 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_delay.o ../../../../../MiniWin/hal/linux/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_lcd.o: ../../../../../MiniWin/hal/linux/hal_lcd.c  .generated_files/flags/default/338d8af295e73b0e34d1d3d4da306a8a9141316a .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_lcd.o ../../../../../MiniWin/hal/linux/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_non_vol.o: ../../../../../MiniWin/hal/linux/hal_non_vol.c  .generated_files/flags/default/bde66058e21eed4a23fa3ebc54cff480354efbcf .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o ../../../../../MiniWin/hal/linux/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_timer.o: ../../../../../MiniWin/hal/linux/hal_timer.c  .generated_files/flags/default/8940580ede24429cdc5b713fcf2a3350b7830a96 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_timer.o ../../../../../MiniWin/hal/linux/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_touch.o: ../../../../../MiniWin/hal/linux/hal_touch.c  .generated_files/flags/default/1776dc0e6b990632d82a6000368bd2dbddd3586b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_touch.o ../../../../../MiniWin/hal/linux/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_delay.o: ../../../../../MiniWin/hal/lpc54628/hal_delay.c  .generated_files/flags/default/5993415938c292424b3d2092b3a05e9e84237d16 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_delay.o ../../../../../MiniWin/hal/lpc54628/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_lcd.o: ../../../../../MiniWin/hal/lpc54628/hal_lcd.c  .generated_files/flags/default/1b2aca8f70c56e5f95416bafea4493102c2a120c .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_lcd.o ../../../../../MiniWin/hal/lpc54628/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_non_vol.o: ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c  .generated_files/flags/default/ece6c95aeef816d18fb00c59641bf1e43bc8f56 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_timer.o: ../../../../../MiniWin/hal/lpc54628/hal_timer.c  .generated_files/flags/default/64935b4109c053a04becd6abf60861be3342a59d .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_timer.o ../../../../../MiniWin/hal/lpc54628/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_touch.o: ../../../../../MiniWin/hal/lpc54628/hal_touch.c  .generated_files/flags/default/584adf4d175b81201e51ce97f69bd118cf03b3fd .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_touch.o ../../../../../MiniWin/hal/lpc54628/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_delay.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c  .generated_files/flags/default/39b22581395824d9a1b0d5ce08dfb62eb9b33b7e .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_delay.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_delay.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_lcd.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c  .generated_files/flags/default/9989f856cacc8a5c447525f5b77ca1a64b8bde05 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_lcd.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_non_vol.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c  .generated_files/flags/default/e72d61c64ceced74b5d0b6df9bce9f439c8b7eea .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_non_vol.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_timer.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c  .generated_files/flags/default/144a002fc5e32072e16cfaeb2589fcef1921dd9f .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_timer.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_timer.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_touch.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c  .generated_files/flags/default/236b65b51b6816a63a0bb1b3d00266fd8a212a27 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_touch.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_touch.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_delay.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_delay.c  .generated_files/flags/default/46fa58ed7eaa71fc6f2de143e75aeaa24352e5bd .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_delay.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_delay.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_lcd.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_lcd.c  .generated_files/flags/default/3e67d97580efd283399236059fbb143dda2f9e41 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_lcd.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_non_vol.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_non_vol.c  .generated_files/flags/default/854e7776543e79293fc5a899af31dc512b9063e5 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_non_vol.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_timer.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_timer.c  .generated_files/flags/default/a4fce79bbb6d3553b9c4f5effa7da5280ed5bd51 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_timer.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_timer.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_touch.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_touch.c  .generated_files/flags/default/162a1a68419005d2dd330a8612989dfac0a366d1 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_touch.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_touch.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_delay.o: ../../../../../MiniWin/hal/rx65n/hal_delay.c  .generated_files/flags/default/dd76552c121057bf2164fc4ea31888c057b03a62 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_delay.o ../../../../../MiniWin/hal/rx65n/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_lcd.o: ../../../../../MiniWin/hal/rx65n/hal_lcd.c  .generated_files/flags/default/2fbae25fb8973dbdc415621d68e30aa601034495 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_lcd.o ../../../../../MiniWin/hal/rx65n/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_non_vol.o: ../../../../../MiniWin/hal/rx65n/hal_non_vol.c  .generated_files/flags/default/a09c0c7e261222682dc85c2ad90c1140803e027b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o ../../../../../MiniWin/hal/rx65n/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_timer.o: ../../../../../MiniWin/hal/rx65n/hal_timer.c  .generated_files/flags/default/e6fe65313d5b99e5d7475b0f96e43a001f77c29d .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_timer.o ../../../../../MiniWin/hal/rx65n/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_touch.o: ../../../../../MiniWin/hal/rx65n/hal_touch.c  .generated_files/flags/default/e007777060409bf1febf487a641581145849a45 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_touch.o ../../../../../MiniWin/hal/rx65n/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_delay.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c  .generated_files/flags/default/193c719887c21ea9df2f4f5f1b54e2329a1f289f .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_delay.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_delay.o ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_lcd.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c  .generated_files/flags/default/d2b3940d2ffe3d1267d4930e45d0d43fd3776ede .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_lcd.o ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_non_vol.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c  .generated_files/flags/default/51c1e35ea8b7bc8c8facd914a2bfd3eee62b688a .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_non_vol.o ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_timer.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c  .generated_files/flags/default/953813dce4c7c1aafcc1a219a3d19a5bcf107518 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_timer.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_timer.o ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_touch.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c  .generated_files/flags/default/dbef29fc94378a2ff859d42f81f01d4178937b40 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_touch.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_touch.o ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_delay.o: ../../../../../MiniWin/hal/stm32f407/hal_delay.c  .generated_files/flags/default/ecad5832bbc254421adc067050c90f5f007958c7 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_delay.o ../../../../../MiniWin/hal/stm32f407/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_lcd.o: ../../../../../MiniWin/hal/stm32f407/hal_lcd.c  .generated_files/flags/default/8d9a35bc541cc07e9059d65229c1042b900df6ff .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_lcd.o ../../../../../MiniWin/hal/stm32f407/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_non_vol.o: ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c  .generated_files/flags/default/d1b958f3f744b75983c6a477da0d09b8abfbb53b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_timer.o: ../../../../../MiniWin/hal/stm32f407/hal_timer.c  .generated_files/flags/default/b4cc9fdf6d3f1c89eef8a40372e8d65f72d5403f .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_timer.o ../../../../../MiniWin/hal/stm32f407/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_touch.o: ../../../../../MiniWin/hal/stm32f407/hal_touch.c  .generated_files/flags/default/aa6809bbdeaef7a356e8b412002ff7548553045 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_touch.o ../../../../../MiniWin/hal/stm32f407/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_delay.o: ../../../../../MiniWin/hal/stm32f429/hal_delay.c  .generated_files/flags/default/e151753fbd3a58ef54b9d969a9adfb235714cadf .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_delay.o ../../../../../MiniWin/hal/stm32f429/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_lcd.o: ../../../../../MiniWin/hal/stm32f429/hal_lcd.c  .generated_files/flags/default/d12954a47437c46637411927a1fc1cbc38999cbd .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_lcd.o ../../../../../MiniWin/hal/stm32f429/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_non_vol.o: ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c  .generated_files/flags/default/7ad816e073cc58b98be4b0e0d2ec1a35bed790b8 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_timer.o: ../../../../../MiniWin/hal/stm32f429/hal_timer.c  .generated_files/flags/default/12ba5fe546c93325a37153d84c7baa83bd01904e .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_timer.o ../../../../../MiniWin/hal/stm32f429/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_touch.o: ../../../../../MiniWin/hal/stm32f429/hal_touch.c  .generated_files/flags/default/a1de8e2e7fbc9e7b28a7905a58616dc1d870e799 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_touch.o ../../../../../MiniWin/hal/stm32f429/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_delay.o: ../../../../../MiniWin/hal/windows/hal_delay.c  .generated_files/flags/default/392ef7748fb8d35b4b8857b8328292249517619 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_delay.o ../../../../../MiniWin/hal/windows/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_lcd.o: ../../../../../MiniWin/hal/windows/hal_lcd.c  .generated_files/flags/default/f470fdf859a83bfa0c722337ba32710145615690 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_lcd.o ../../../../../MiniWin/hal/windows/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_non_vol.o: ../../../../../MiniWin/hal/windows/hal_non_vol.c  .generated_files/flags/default/bf7c3c90c9349eaa877da1c3ab3bbf3d72742e11 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o ../../../../../MiniWin/hal/windows/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_timer.o: ../../../../../MiniWin/hal/windows/hal_timer.c  .generated_files/flags/default/2b61bce49c7c3d48bbf97975cf28486eb42ea7b7 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_timer.o ../../../../../MiniWin/hal/windows/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_touch.o: ../../../../../MiniWin/hal/windows/hal_touch.c  .generated_files/flags/default/61f8bbef4c41ffe32a526598d31330c945ebcd85 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_touch.o ../../../../../MiniWin/hal/windows/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/902303450/hal_init.o: ../../../../../MiniWin/hal/hal_init.c  .generated_files/flags/default/c84e5b47b7c6b7ed2fb77a5f6428ceee3a1ee733 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/902303450" 
	@${RM} ${OBJECTDIR}/_ext/902303450/hal_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/902303450/hal_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/902303450/hal_init.o.d" -o ${OBJECTDIR}/_ext/902303450/hal_init.o ../../../../../MiniWin/hal/hal_init.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_arrow.o: ../../../../../MiniWin/ui/ui_arrow.c  .generated_files/flags/default/a7664f7593d354a14cd0cefd03a7a06d721837e4 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_arrow.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_arrow.o ../../../../../MiniWin/ui/ui_arrow.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_button.o: ../../../../../MiniWin/ui/ui_button.c  .generated_files/flags/default/16b53992a740c8b28edb79a513b145b991bc7c3d .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_button.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_button.o ../../../../../MiniWin/ui/ui_button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_check_box.o: ../../../../../MiniWin/ui/ui_check_box.c  .generated_files/flags/default/f5c5cd91c0fa305a93d50341eb0f9de07db9754b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_check_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_check_box.o ../../../../../MiniWin/ui/ui_check_box.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_common.o: ../../../../../MiniWin/ui/ui_common.c  .generated_files/flags/default/efd6f6e95bee7f1ff4c66717223a6942843f8349 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_common.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_common.o ../../../../../MiniWin/ui/ui_common.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_keyboard.o: ../../../../../MiniWin/ui/ui_keyboard.c  .generated_files/flags/default/683df4527de108631946f8850f015d008ef3edfb .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o ../../../../../MiniWin/ui/ui_keyboard.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_keypad.o: ../../../../../MiniWin/ui/ui_keypad.c  .generated_files/flags/default/8b6dc58788cbf5367095d813fe3712fefdf1d6df .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keypad.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_keypad.o ../../../../../MiniWin/ui/ui_keypad.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_label.o: ../../../../../MiniWin/ui/ui_label.c  .generated_files/flags/default/822db7bba2899ecb96927ebefc4c77b144e5ad54 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_label.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_label.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_label.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_label.o ../../../../../MiniWin/ui/ui_label.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_list_box.o: ../../../../../MiniWin/ui/ui_list_box.c  .generated_files/flags/default/b9a52d04da30c61b1340207a768e1daed8e3a379 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_list_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_list_box.o ../../../../../MiniWin/ui/ui_list_box.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o: ../../../../../MiniWin/ui/ui_progress_bar.c  .generated_files/flags/default/800382795fc4a49e2b9a0ba4b3100f64bba960f .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o ../../../../../MiniWin/ui/ui_progress_bar.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_radio_button.o: ../../../../../MiniWin/ui/ui_radio_button.c  .generated_files/flags/default/5b3a61e006aaf94a5f128daa6da864e82509861f .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o ../../../../../MiniWin/ui/ui_radio_button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o: ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c  .generated_files/flags/default/6ead41125e35d6de25fc461a4c98d5a450324e62 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o: ../../../../../MiniWin/ui/ui_scroll_bar_vert.c  .generated_files/flags/default/6db375d80bfc6f4779d609e6b3c8d729f742151b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o ../../../../../MiniWin/ui/ui_scroll_bar_vert.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_tabs.o: ../../../../../MiniWin/ui/ui_tabs.c  .generated_files/flags/default/6fe770706c48dc1f3b6580951d2e20bcf0ad3051 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tabs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_tabs.o ../../../../../MiniWin/ui/ui_tabs.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_text_box.o: ../../../../../MiniWin/ui/ui_text_box.c  .generated_files/flags/default/78570a38ac625c1ca8f7bf11038f5556dc9ff387 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_text_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_text_box.o ../../../../../MiniWin/ui/ui_text_box.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_tree.o: ../../../../../MiniWin/ui/ui_tree.c  .generated_files/flags/default/6d9ac1859686d5dd7d96cf69bbfa3feba40adaa8 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tree.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tree.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_tree.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_tree.o ../../../../../MiniWin/ui/ui_tree.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/calibrate.o: ../../../../../MiniWin/calibrate.c  .generated_files/flags/default/ab808ac5f1108f6ba1180454bd8073f3995b0d02 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/calibrate.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/calibrate.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/calibrate.o.d" -o ${OBJECTDIR}/_ext/59636182/calibrate.o ../../../../../MiniWin/calibrate.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin.o: ../../../../../MiniWin/miniwin.c  .generated_files/flags/default/1a16ff1943e02821dc6407f9705f56a013a9470e .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin.o ../../../../../MiniWin/miniwin.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_debug.o: ../../../../../MiniWin/miniwin_debug.c  .generated_files/flags/default/709f7e933d2cbcb26e52f1a010a02d5a30da811c .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_debug.o ../../../../../MiniWin/miniwin_debug.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o: ../../../../../MiniWin/miniwin_message_queue.c  .generated_files/flags/default/73132b6356800feb33b6d79cc75cd1bfc2d65838 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o ../../../../../MiniWin/miniwin_message_queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_settings.o: ../../../../../MiniWin/miniwin_settings.c  .generated_files/flags/default/72caada98e9671e3d80e54c9c828d5823efbe501 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_settings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_settings.o ../../../../../MiniWin/miniwin_settings.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_touch.o: ../../../../../MiniWin/miniwin_touch.c  .generated_files/flags/default/357b3b032d6535a451b0f80aec3eab3474376f32 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_touch.o ../../../../../MiniWin/miniwin_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o: ../../../../../MiniWin/miniwin_tree_container.c  .generated_files/flags/default/a32caff4486ec81c836b461acf003a650692e15b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o ../../../../../MiniWin/miniwin_tree_container.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_utilities.o: ../../../../../MiniWin/miniwin_utilities.c  .generated_files/flags/default/3ee58e0c2f467d7ab25c31eafae2718bc1bce923 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o ../../../../../MiniWin/miniwin_utilities.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/main.o: ../../../../../MiniWinFile_Common/main.c  .generated_files/flags/default/d45c9bdf7ef56154d16780a18b9874934025572b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/main.o.d" -o ${OBJECTDIR}/_ext/165771656/main.o ../../../../../MiniWinFile_Common/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/miniwin_user.o: ../../../../../MiniWinFile_Common/miniwin_user.c  .generated_files/flags/default/6f270e6a86ab9214ed6741b07d0c3fe50ee39df6 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/miniwin_user.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/miniwin_user.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/miniwin_user.o.d" -o ${OBJECTDIR}/_ext/165771656/miniwin_user.o ../../../../../MiniWinFile_Common/miniwin_user.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_file.o: ../../../../../MiniWinFile_Common/window_file.c  .generated_files/flags/default/3811520e402bb1db105cb1d6747f5d947024b3bf .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_file.o.d" -o ${OBJECTDIR}/_ext/165771656/window_file.o ../../../../../MiniWinFile_Common/window_file.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_file_tree.o: ../../../../../MiniWinFile_Common/window_file_tree.c  .generated_files/flags/default/d10ea33ac8ccd91dd0865134ecb2f2620fb79c66 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file_tree.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file_tree.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_file_tree.o.d" -o ${OBJECTDIR}/_ext/165771656/window_file_tree.o ../../../../../MiniWinFile_Common/window_file_tree.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_image.o: ../../../../../MiniWinFile_Common/window_image.c  .generated_files/flags/default/e2bdbf5619d69ee7ccd2906f7eb3cbbae365ba3f .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_image.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_image.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_image.o.d" -o ${OBJECTDIR}/_ext/165771656/window_image.o ../../../../../MiniWinFile_Common/window_image.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_selection.o: ../../../../../MiniWinFile_Common/window_selection.c  .generated_files/flags/default/8be93dd41c2f28507ddd98c12f3ea405c196972f .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_selection.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_selection.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_selection.o.d" -o ${OBJECTDIR}/_ext/165771656/window_selection.o ../../../../../MiniWinFile_Common/window_selection.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_text.o: ../../../../../MiniWinFile_Common/window_text.c  .generated_files/flags/default/c32fb1c7b367a1c03b59d2805f1f782a85d84dc7 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_text.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_text.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_text.o.d" -o ${OBJECTDIR}/_ext/165771656/window_text.o ../../../../../MiniWinFile_Common/window_text.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1445274692/app.o: ../../src/app.c  .generated_files/flags/default/303820a2b99a7d76b118ee13804ed6a17ad150da .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1445274692" 
	@${RM} ${OBJECTDIR}/_ext/1445274692/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1445274692/app.o.d" -o ${OBJECTDIR}/_ext/1445274692/app.o ../../src/app.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/flags/default/95da7237271063c4a2c2267f729221bc58bfa704 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1249264884/plib_coretimer.o: ../src/config/default/peripheral/coretimer/plib_coretimer.c  .generated_files/flags/default/603292a2f1fb01905de51facc2f061f9a78f46c1 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1249264884" 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ../src/config/default/peripheral/coretimer/plib_coretimer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/flags/default/da8ee56e59220905c6ea5f22bbeab1aa6b9e92d5 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/flags/default/e05695fa854eb37148ac4028376c503e49ba717 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60176403/plib_nvm.o: ../src/config/default/peripheral/nvm/plib_nvm.c  .generated_files/flags/default/ef3f41429aa998e0db96d235f200dcab4b51498a .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/60176403" 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ../src/config/default/peripheral/nvm/plib_nvm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/298189674/plib_spi2_master.o: ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c  .generated_files/flags/default/b9357d3e863bfb24ae275cd983a5ec8b9c28070f .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/298189674" 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d" -o ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/298189674/plib_spi1_master.o: ../src/config/default/peripheral/spi/spi_master/plib_spi1_master.c  .generated_files/flags/default/94d3ba8eba7e4e010a465b9e04ec5b497e0bd791 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/298189674" 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/298189674/plib_spi1_master.o.d" -o ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o ../src/config/default/peripheral/spi/spi_master/plib_spi1_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60181895/plib_tmr2.o: ../src/config/default/peripheral/tmr/plib_tmr2.c  .generated_files/flags/default/d28716621197bb8c2a85ed95ace404dde6fab40d .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ../src/config/default/peripheral/tmr/plib_tmr2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60181895/plib_tmr3.o: ../src/config/default/peripheral/tmr/plib_tmr3.c  .generated_files/flags/default/359e4c49254972b4457623870babd7f59f74455a .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr3.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr3.o ../src/config/default/peripheral/tmr/plib_tmr3.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/bcb1cf5ccb4c058413db865a3fdafd0de7349fd9 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/flags/default/4a6d61381278d40acfdccc3af96ece05692a7eb5 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/flags/default/f24dd2410fd22e94aa723d6939aa5bfa7380b087 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/flags/default/3612715befba7973b74f253476395b7c6ecd696b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/ff.o: ../../FatFS/ff.c  .generated_files/flags/default/2febd258aedbb509ff79bbeca443837ad911873 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/ff.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/ff.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/ff.o.d" -o ${OBJECTDIR}/_ext/1592496102/ff.o ../../FatFS/ff.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/sdmm.o: ../../FatFS/sdmm.c  .generated_files/flags/default/e57e3491d7c678ba93910a4cff47b0a864407956 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/sdmm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/sdmm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/sdmm.o.d" -o ${OBJECTDIR}/_ext/1592496102/sdmm.o ../../FatFS/sdmm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/spi_driver.o: ../../FatFS/spi_driver.c  .generated_files/flags/default/2d730af9a681e8a0fc4917633a65a930f14f8844 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/spi_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/spi_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/spi_driver.o.d" -o ${OBJECTDIR}/_ext/1592496102/spi_driver.o ../../FatFS/spi_driver.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/backspace_key.o: ../../../../../MiniWin/bitmaps/backspace_key.c  .generated_files/flags/default/be39ec3af1f6c2526c0e8019ded312bd800202bb .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/backspace_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/backspace_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/backspace_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/backspace_key.o ../../../../../MiniWin/bitmaps/backspace_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/close_icon.o: ../../../../../MiniWin/bitmaps/close_icon.c  .generated_files/flags/default/1cec3fffc65daad44f830ffdef26af7de45b02b4 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/close_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/close_icon.o ../../../../../MiniWin/bitmaps/close_icon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/close_icon_large.o: ../../../../../MiniWin/bitmaps/close_icon_large.c  .generated_files/flags/default/d07442a775d94719d3b86bdf74aeb5a6b5bf2b8f .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/close_icon_large.o ../../../../../MiniWin/bitmaps/close_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/file_icon_large.o: ../../../../../MiniWin/bitmaps/file_icon_large.c  .generated_files/flags/default/728fb8d2118d3de68b738c422ee2be65174bb2a1 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/file_icon_large.o ../../../../../MiniWin/bitmaps/file_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/file_icon_small.o: ../../../../../MiniWin/bitmaps/file_icon_small.c  .generated_files/flags/default/5b07afb796a217f96ce6be93b7e94fbe6514e738 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/file_icon_small.o ../../../../../MiniWin/bitmaps/file_icon_small.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o: ../../../../../MiniWin/bitmaps/folder_close_icon_large.c  .generated_files/flags/default/f594c9d21fd6dc8b9ba6c27034787af94cd5c7c6 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o ../../../../../MiniWin/bitmaps/folder_close_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o: ../../../../../MiniWin/bitmaps/folder_close_icon_small.c  .generated_files/flags/default/5a1d357f767c3d443dbc3eedc1c0cfa76c8bb907 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o ../../../../../MiniWin/bitmaps/folder_close_icon_small.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_icon_large.o: ../../../../../MiniWin/bitmaps/folder_icon_large.c  .generated_files/flags/default/8ae31254a78d44c702b2c3438f5775ccc0297758 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o ../../../../../MiniWin/bitmaps/folder_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_icon_small.o: ../../../../../MiniWin/bitmaps/folder_icon_small.c  .generated_files/flags/default/13b83dc20e1a4826fba63c1211ec2f45da48a4a3 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o ../../../../../MiniWin/bitmaps/folder_icon_small.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o: ../../../../../MiniWin/bitmaps/folder_open_icon_large.c  .generated_files/flags/default/737f754289cbfe4b7b0a20350ccc9cda93c9554d .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o ../../../../../MiniWin/bitmaps/folder_open_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o: ../../../../../MiniWin/bitmaps/folder_open_icon_small.c  .generated_files/flags/default/461a3faea04104ebc820f1042d5045b0666fdd5a .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o ../../../../../MiniWin/bitmaps/folder_open_icon_small.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/let_key.o: ../../../../../MiniWin/bitmaps/let_key.c  .generated_files/flags/default/13db4305c5a4516b85025d401b94dd05ca4eb6c8 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/let_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/let_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/let_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/let_key.o ../../../../../MiniWin/bitmaps/let_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/maximise_icon.o: ../../../../../MiniWin/bitmaps/maximise_icon.c  .generated_files/flags/default/e3547ee2966b29762f8b927d8179bfd3b755da56 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/maximise_icon.o ../../../../../MiniWin/bitmaps/maximise_icon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o: ../../../../../MiniWin/bitmaps/maximise_icon_large.c  .generated_files/flags/default/17d84afdd82c7eeef8de1b701e576eda69f374d4 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o ../../../../../MiniWin/bitmaps/maximise_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/minimise_icon.o: ../../../../../MiniWin/bitmaps/minimise_icon.c  .generated_files/flags/default/71db06ad6b1dc667fc1ba0da70f30bc2ec54b30d .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/minimise_icon.o ../../../../../MiniWin/bitmaps/minimise_icon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o: ../../../../../MiniWin/bitmaps/minimise_icon_large.c  .generated_files/flags/default/eeae91e90ef04df3c1bbe4d455f50070d1acce2 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o ../../../../../MiniWin/bitmaps/minimise_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/num_key.o: ../../../../../MiniWin/bitmaps/num_key.c  .generated_files/flags/default/1dbb9f4b545da654fe4a177728d3735f9cb67889 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/num_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/num_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/num_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/num_key.o ../../../../../MiniWin/bitmaps/num_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/resize_icon.o: ../../../../../MiniWin/bitmaps/resize_icon.c  .generated_files/flags/default/a1ecacc91ae16134064a1aa5abf157fc077ec20b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/resize_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/resize_icon.o ../../../../../MiniWin/bitmaps/resize_icon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/resize_icon_large.o: ../../../../../MiniWin/bitmaps/resize_icon_large.c  .generated_files/flags/default/4e737db1ddff42f58b2f505cb9cd6e34521eb247 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o ../../../../../MiniWin/bitmaps/resize_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/shift_key.o: ../../../../../MiniWin/bitmaps/shift_key.c  .generated_files/flags/default/91e0fd36e17eb826af2455a5ea9e516af7bd675d .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/shift_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/shift_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/shift_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/shift_key.o ../../../../../MiniWin/bitmaps/shift_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/sym_key.o: ../../../../../MiniWin/bitmaps/sym_key.c  .generated_files/flags/default/900502ff909d33e7c88a4744694b10a524d70c93 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/sym_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/sym_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/sym_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/sym_key.o ../../../../../MiniWin/bitmaps/sym_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/tick.o: ../../../../../MiniWin/bitmaps/tick.c  .generated_files/flags/default/13bc5bddddb07a51be863bcb5c1ccf70826e8303 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/tick.o.d" -o ${OBJECTDIR}/_ext/1275709973/tick.o ../../../../../MiniWin/bitmaps/tick.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/tick_large.o: ../../../../../MiniWin/bitmaps/tick_large.c  .generated_files/flags/default/64f2222adec82846b26acf8645e7f9b2d5f39855 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/tick_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/tick_large.o ../../../../../MiniWin/bitmaps/tick_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o: ../../../../../MiniWin/dialogs/dialog_colour_chooser.c  .generated_files/flags/default/cbb5fca76530199ead4765def3af271caffd2b77 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o ../../../../../MiniWin/dialogs/dialog_colour_chooser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o: ../../../../../MiniWin/dialogs/dialog_date_chooser.c  .generated_files/flags/default/d6f497887528a7d07eb338ac86e191e6b4d55e3a .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o ../../../../../MiniWin/dialogs/dialog_date_chooser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o: ../../../../../MiniWin/dialogs/dialog_file_chooser.c  .generated_files/flags/default/458fe55fc0d6a073cb9092e1ca31b63c757b2ce6 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o ../../../../../MiniWin/dialogs/dialog_file_chooser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_number_entry.o: ../../../../../MiniWin/dialogs/dialog_number_entry.c  .generated_files/flags/default/9e82518aa44ac24e5c50625ea5109882d70b340e .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o ../../../../../MiniWin/dialogs/dialog_number_entry.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_one_button.o: ../../../../../MiniWin/dialogs/dialog_one_button.c  .generated_files/flags/default/6a7fe2a8269f4aecf56a437269317564bfb0393b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_one_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_one_button.o ../../../../../MiniWin/dialogs/dialog_one_button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_text_entry.o: ../../../../../MiniWin/dialogs/dialog_text_entry.c  .generated_files/flags/default/19f12433b6529d44197e8240b5cf4a5203e0abcc .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o ../../../../../MiniWin/dialogs/dialog_text_entry.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o: ../../../../../MiniWin/dialogs/dialog_time_chooser.c  .generated_files/flags/default/6106d177362de8ca4b5ee5d2197955a126b9d4b1 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o ../../../../../MiniWin/dialogs/dialog_time_chooser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_two_button.o: ../../../../../MiniWin/dialogs/dialog_two_button.c  .generated_files/flags/default/34e6ca49430ce250e8119a25561061216d7a0e98 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_two_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_two_button.o ../../../../../MiniWin/dialogs/dialog_two_button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font12.o: ../../../../../MiniWin/gl/fonts/bitmapped/font12.c  .generated_files/flags/default/349e40d178311d1a8be6888dceaf6b9d3826eb6b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font12.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font12.o.d" -o ${OBJECTDIR}/_ext/194049764/font12.o ../../../../../MiniWin/gl/fonts/bitmapped/font12.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font16.o: ../../../../../MiniWin/gl/fonts/bitmapped/font16.c  .generated_files/flags/default/9d7b70e937a90ab22c8b86fcbf29b5ab007764a1 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font16.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font16.o.d" -o ${OBJECTDIR}/_ext/194049764/font16.o ../../../../../MiniWin/gl/fonts/bitmapped/font16.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font20.o: ../../../../../MiniWin/gl/fonts/bitmapped/font20.c  .generated_files/flags/default/19f53595e186abda7ed06ea455a126fd6058e68d .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font20.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font20.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font20.o.d" -o ${OBJECTDIR}/_ext/194049764/font20.o ../../../../../MiniWin/gl/fonts/bitmapped/font20.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font24.o: ../../../../../MiniWin/gl/fonts/bitmapped/font24.c  .generated_files/flags/default/2f64133442b90bbf10899fbee3fbbaa1d9140ae3 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font24.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font24.o.d" -o ${OBJECTDIR}/_ext/194049764/font24.o ../../../../../MiniWin/gl/fonts/bitmapped/font24.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font9.o: ../../../../../MiniWin/gl/fonts/bitmapped/font9.c  .generated_files/flags/default/544f1cdeda75f5e0407672de51c36763f0ea187e .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font9.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font9.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font9.o.d" -o ${OBJECTDIR}/_ext/194049764/font9.o ../../../../../MiniWin/gl/fonts/bitmapped/font9.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/gl_title_font.o: ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c  .generated_files/flags/default/cee076c4c072b1ae33e19d46e584d063f9716925 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/gl_title_font.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/gl_title_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/gl_title_font.o.d" -o ${OBJECTDIR}/_ext/194049764/gl_title_font.o ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_bwfont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c  .generated_files/flags/default/8337406e88d9464d7244a8c3a5bc7548d51db6c .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_encoding.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c  .generated_files/flags/default/25afa3b79e7004d5608a41d59e1416e3a3a39212 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_encoding.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_encoding.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_font.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c  .generated_files/flags/default/520c18fa061e82667d2c9eed20ba1be37db8004b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_font.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_font.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_font.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_justify.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c  .generated_files/flags/default/7d86c2f1eb6cc476de9f5f32f3dcad17a3474f1b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_justify.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_justify.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_justify.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_justify.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_kerning.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c  .generated_files/flags/default/863bc544f304ed065d2d9321b1f641face6466ed .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_kerning.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_kerning.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_rlefont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c  .generated_files/flags/default/b0ecfbcaff76ce7253dd99ece38daebd9b07171b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c  .generated_files/flags/default/5d2f73c7eff4ddfb6ee36b4f22ba5abc0f46fd .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c  .generated_files/flags/default/345f8617a230860af08da13573cb2b05112b45cd .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o: ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c  .generated_files/flags/default/42974a71f29c4f1cbe222e9b5988d9e923db2edc .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d" -o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o: ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c  .generated_files/flags/default/15bfdb0e58b8019a50c7dcb3c1a2a065a10175c .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d" -o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o: ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c  .generated_files/flags/default/b3f7d08095f97e8923ec3b3e7440795cf63fb1f2 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d" -o ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494914114/gl.o: ../../../../../MiniWin/gl/gl.c  .generated_files/flags/default/1470b5ffc8abf2d13c9fb5a65ffc406ff569a0b2 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494914114" 
	@${RM} ${OBJECTDIR}/_ext/1494914114/gl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494914114/gl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494914114/gl.o.d" -o ${OBJECTDIR}/_ext/1494914114/gl.o ../../../../../MiniWin/gl/gl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_delay.o: ../../../../../MiniWin/hal/DevKitC/hal_delay.c  .generated_files/flags/default/592354b4c6b95767ee9fa6b7e3eb61a9b2399144 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_delay.o ../../../../../MiniWin/hal/DevKitC/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_lcd.o: ../../../../../MiniWin/hal/DevKitC/hal_lcd.c  .generated_files/flags/default/e45a6a0097b3927e5d1c1dc7c097c1fb42e1aad1 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_lcd.o ../../../../../MiniWin/hal/DevKitC/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_non_vol.o: ../../../../../MiniWin/hal/DevKitC/hal_non_vol.c  .generated_files/flags/default/140e65aeb70e40f05302823a90dcb6a7fa42e730 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o ../../../../../MiniWin/hal/DevKitC/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_timer.o: ../../../../../MiniWin/hal/DevKitC/hal_timer.c  .generated_files/flags/default/6b2fd07197c916752f4ad418feaabd46eaf480eb .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_timer.o ../../../../../MiniWin/hal/DevKitC/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_touch.o: ../../../../../MiniWin/hal/DevKitC/hal_touch.c  .generated_files/flags/default/da0cebff4ce1c36ccc7e23539c651854497b9ec7 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_touch.o ../../../../../MiniWin/hal/DevKitC/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_delay.o: ../../../../../MiniWin/hal/linux/hal_delay.c  .generated_files/flags/default/61519455d138d50f5471118ce52a69835fa38ae6 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_delay.o ../../../../../MiniWin/hal/linux/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_lcd.o: ../../../../../MiniWin/hal/linux/hal_lcd.c  .generated_files/flags/default/121c298ee5ce05edbd797c9b6b9b6bfa0fa9038c .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_lcd.o ../../../../../MiniWin/hal/linux/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_non_vol.o: ../../../../../MiniWin/hal/linux/hal_non_vol.c  .generated_files/flags/default/14c1cf09457610d3408920b39d4e943bca3a8bb6 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o ../../../../../MiniWin/hal/linux/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_timer.o: ../../../../../MiniWin/hal/linux/hal_timer.c  .generated_files/flags/default/fb4cac0d1fe1c76a3cb0be250e9e2c6d0d51e285 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_timer.o ../../../../../MiniWin/hal/linux/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_touch.o: ../../../../../MiniWin/hal/linux/hal_touch.c  .generated_files/flags/default/22d509ccae359dc943e8c2638c284df3cb288498 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_touch.o ../../../../../MiniWin/hal/linux/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_delay.o: ../../../../../MiniWin/hal/lpc54628/hal_delay.c  .generated_files/flags/default/5a2e0d39fa9567a57c5ceeb27a5dc5410f3a235b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_delay.o ../../../../../MiniWin/hal/lpc54628/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_lcd.o: ../../../../../MiniWin/hal/lpc54628/hal_lcd.c  .generated_files/flags/default/bba660ed8a0157c7c7a3473f06c2efc00b52949d .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_lcd.o ../../../../../MiniWin/hal/lpc54628/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_non_vol.o: ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c  .generated_files/flags/default/5a4a1219722ad62cf3c0b14c092f34bd4d0222d8 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_timer.o: ../../../../../MiniWin/hal/lpc54628/hal_timer.c  .generated_files/flags/default/967583bf07324fdf815831a3b9e7d45f701700d0 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_timer.o ../../../../../MiniWin/hal/lpc54628/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_touch.o: ../../../../../MiniWin/hal/lpc54628/hal_touch.c  .generated_files/flags/default/ba6ee1bb503027d98b76eb2eddf981a46ccf16b9 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_touch.o ../../../../../MiniWin/hal/lpc54628/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_delay.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c  .generated_files/flags/default/3c8e3c3a261b743993d15b4e5f95f01c0e786b69 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_delay.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_delay.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_lcd.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c  .generated_files/flags/default/f6b14715b2409b80462e2c6143c2d6295521bdd4 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_lcd.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_non_vol.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c  .generated_files/flags/default/9fc09bee58e83aba95511ba1309cd15ec363bc2b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_non_vol.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_timer.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c  .generated_files/flags/default/56b089cca1738f5efed9cb9eda1178acf7c399a0 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_timer.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_timer.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_touch.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c  .generated_files/flags/default/4daaf569ed5ad0e7ba66d9842760684a77f37cc3 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_touch.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_touch.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_delay.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_delay.c  .generated_files/flags/default/689fe3af83933df7a80e03e8189e6d4f455b463a .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_delay.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_delay.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_lcd.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_lcd.c  .generated_files/flags/default/ec5ed9ef878ad916571554ae32873b022c3ba3c .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_lcd.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_non_vol.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_non_vol.c  .generated_files/flags/default/c8dc9900332da3cf45b7bdb47852b204b13dfa17 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_non_vol.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_timer.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_timer.c  .generated_files/flags/default/f35c0c04ade6eda7aaba8d48720c41619853ada .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_timer.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_timer.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_touch.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_touch.c  .generated_files/flags/default/3eb54c80eb3e3aa9c49ceb51ef663debf2fb3448 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_touch.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_touch.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_delay.o: ../../../../../MiniWin/hal/rx65n/hal_delay.c  .generated_files/flags/default/88361716b8b34ce7760156abe4f3b92b167ff519 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_delay.o ../../../../../MiniWin/hal/rx65n/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_lcd.o: ../../../../../MiniWin/hal/rx65n/hal_lcd.c  .generated_files/flags/default/f6dc88f01b6325c7560e15b4ed1934c568609bcd .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_lcd.o ../../../../../MiniWin/hal/rx65n/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_non_vol.o: ../../../../../MiniWin/hal/rx65n/hal_non_vol.c  .generated_files/flags/default/247156e34881fb5c0b7faf51ebe2db24ec1b3404 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o ../../../../../MiniWin/hal/rx65n/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_timer.o: ../../../../../MiniWin/hal/rx65n/hal_timer.c  .generated_files/flags/default/43bd90a6b772763bc8315c9a423077ed6b5484d .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_timer.o ../../../../../MiniWin/hal/rx65n/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_touch.o: ../../../../../MiniWin/hal/rx65n/hal_touch.c  .generated_files/flags/default/de2d20e51bc69abc8fb7d6f601bb4073d279f66f .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_touch.o ../../../../../MiniWin/hal/rx65n/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_delay.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c  .generated_files/flags/default/dac215424a36f8dcf004cec404b77925dbb6abb7 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_delay.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_delay.o ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_lcd.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c  .generated_files/flags/default/c6758a90afb012ed207a6d7b0e0d2c7419e9a7ed .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_lcd.o ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_non_vol.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c  .generated_files/flags/default/9fa5408b17a73c57820fb26683bcbf0b3a17ca1d .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_non_vol.o ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_timer.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c  .generated_files/flags/default/724651b88c8858795b1de6e1131d615eff4062fb .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_timer.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_timer.o ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_touch.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c  .generated_files/flags/default/b4a3748d3c929ee33f0d96f560cec16cb33df4a8 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_touch.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_touch.o ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_delay.o: ../../../../../MiniWin/hal/stm32f407/hal_delay.c  .generated_files/flags/default/b92ba55034492fd8f69d4166e36f29c43f72112b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_delay.o ../../../../../MiniWin/hal/stm32f407/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_lcd.o: ../../../../../MiniWin/hal/stm32f407/hal_lcd.c  .generated_files/flags/default/22852b660d5c4cb69ce3d20d0e462e23673cf4ee .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_lcd.o ../../../../../MiniWin/hal/stm32f407/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_non_vol.o: ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c  .generated_files/flags/default/eb418ee05dee35a9721e923d8d2cfd9a32e92f26 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_timer.o: ../../../../../MiniWin/hal/stm32f407/hal_timer.c  .generated_files/flags/default/774ad51ffc5a2e41d9c89119c938b733faba6419 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_timer.o ../../../../../MiniWin/hal/stm32f407/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_touch.o: ../../../../../MiniWin/hal/stm32f407/hal_touch.c  .generated_files/flags/default/3568d4e8e4316a10bdc68900e18fc941721e533f .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_touch.o ../../../../../MiniWin/hal/stm32f407/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_delay.o: ../../../../../MiniWin/hal/stm32f429/hal_delay.c  .generated_files/flags/default/50fb970bb842743fe02d195147f0c4f488d62db .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_delay.o ../../../../../MiniWin/hal/stm32f429/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_lcd.o: ../../../../../MiniWin/hal/stm32f429/hal_lcd.c  .generated_files/flags/default/32caa4c73db8a1755952ffd7cd6bb20f7d21c50c .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_lcd.o ../../../../../MiniWin/hal/stm32f429/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_non_vol.o: ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c  .generated_files/flags/default/4e08d02d4db3dc994a7fea9775d12c985fdca5fd .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_timer.o: ../../../../../MiniWin/hal/stm32f429/hal_timer.c  .generated_files/flags/default/6cc14e418a859a17b52ca270c9de0331db20976e .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_timer.o ../../../../../MiniWin/hal/stm32f429/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_touch.o: ../../../../../MiniWin/hal/stm32f429/hal_touch.c  .generated_files/flags/default/b7b0f98ac6acac64bde1365b99c33ecfbc12d202 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_touch.o ../../../../../MiniWin/hal/stm32f429/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_delay.o: ../../../../../MiniWin/hal/windows/hal_delay.c  .generated_files/flags/default/42ae49d3fd58f5ca137fe4889bff9a6baae91ab8 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_delay.o ../../../../../MiniWin/hal/windows/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_lcd.o: ../../../../../MiniWin/hal/windows/hal_lcd.c  .generated_files/flags/default/164cf6a9c9d3893096c8c6bc3e1b1308f07345e .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_lcd.o ../../../../../MiniWin/hal/windows/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_non_vol.o: ../../../../../MiniWin/hal/windows/hal_non_vol.c  .generated_files/flags/default/93a6a2140885e4ad1aa268618a9a13ea1bb7de1e .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o ../../../../../MiniWin/hal/windows/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_timer.o: ../../../../../MiniWin/hal/windows/hal_timer.c  .generated_files/flags/default/beefa411248e9e6f28f9bba98d6abbd338b86e88 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_timer.o ../../../../../MiniWin/hal/windows/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_touch.o: ../../../../../MiniWin/hal/windows/hal_touch.c  .generated_files/flags/default/bf395b6fa208f515b2da85e00c99bbceb306ff3d .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_touch.o ../../../../../MiniWin/hal/windows/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/902303450/hal_init.o: ../../../../../MiniWin/hal/hal_init.c  .generated_files/flags/default/51b942562d8e2b37aab510731ae0a82669e593b6 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/902303450" 
	@${RM} ${OBJECTDIR}/_ext/902303450/hal_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/902303450/hal_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/902303450/hal_init.o.d" -o ${OBJECTDIR}/_ext/902303450/hal_init.o ../../../../../MiniWin/hal/hal_init.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_arrow.o: ../../../../../MiniWin/ui/ui_arrow.c  .generated_files/flags/default/566fd9bc049e55561f58009504bfc6938dc27c2f .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_arrow.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_arrow.o ../../../../../MiniWin/ui/ui_arrow.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_button.o: ../../../../../MiniWin/ui/ui_button.c  .generated_files/flags/default/ad0d15c5f2640554abfab951b2de733962abc58 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_button.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_button.o ../../../../../MiniWin/ui/ui_button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_check_box.o: ../../../../../MiniWin/ui/ui_check_box.c  .generated_files/flags/default/664283e4df986afdeaa23a88b994f00b39e3147 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_check_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_check_box.o ../../../../../MiniWin/ui/ui_check_box.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_common.o: ../../../../../MiniWin/ui/ui_common.c  .generated_files/flags/default/bbce3c078e6d89cb37f3cd7b603de7dd38a77238 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_common.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_common.o ../../../../../MiniWin/ui/ui_common.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_keyboard.o: ../../../../../MiniWin/ui/ui_keyboard.c  .generated_files/flags/default/49038d36fab21a9054d670528412618a82308a46 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o ../../../../../MiniWin/ui/ui_keyboard.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_keypad.o: ../../../../../MiniWin/ui/ui_keypad.c  .generated_files/flags/default/6b33c11b9fdf8c263c95d63b7b6e06fd755bde86 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keypad.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_keypad.o ../../../../../MiniWin/ui/ui_keypad.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_label.o: ../../../../../MiniWin/ui/ui_label.c  .generated_files/flags/default/97e02dd788439fa9d8dc4699a0282827a3a9a1ae .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_label.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_label.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_label.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_label.o ../../../../../MiniWin/ui/ui_label.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_list_box.o: ../../../../../MiniWin/ui/ui_list_box.c  .generated_files/flags/default/7855c4eaf47d53126ef7ace6f499006f5008f8a .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_list_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_list_box.o ../../../../../MiniWin/ui/ui_list_box.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o: ../../../../../MiniWin/ui/ui_progress_bar.c  .generated_files/flags/default/456c7a7993d1c3674f5bf16c2527dcc06cd46884 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o ../../../../../MiniWin/ui/ui_progress_bar.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_radio_button.o: ../../../../../MiniWin/ui/ui_radio_button.c  .generated_files/flags/default/c46c21ae68e504621ea1dc7e1b54f29fa77a660b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o ../../../../../MiniWin/ui/ui_radio_button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o: ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c  .generated_files/flags/default/acb2e0147fa64612791af4415154154b439aa42f .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o: ../../../../../MiniWin/ui/ui_scroll_bar_vert.c  .generated_files/flags/default/91e25f2fd5ade581d9727899762c7de2d52c6e18 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o ../../../../../MiniWin/ui/ui_scroll_bar_vert.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_tabs.o: ../../../../../MiniWin/ui/ui_tabs.c  .generated_files/flags/default/1c3911abcb4c26f45735fec0be4a06538aa004f3 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tabs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_tabs.o ../../../../../MiniWin/ui/ui_tabs.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_text_box.o: ../../../../../MiniWin/ui/ui_text_box.c  .generated_files/flags/default/12fef46d4c89274f7a0b6c0402ee8281c3210ad7 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_text_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_text_box.o ../../../../../MiniWin/ui/ui_text_box.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_tree.o: ../../../../../MiniWin/ui/ui_tree.c  .generated_files/flags/default/8cd6f34c9586fdeb2d8b9817dfe2912a6a019a1d .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tree.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tree.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_tree.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_tree.o ../../../../../MiniWin/ui/ui_tree.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/calibrate.o: ../../../../../MiniWin/calibrate.c  .generated_files/flags/default/c7bc796869f9d31fec3059cea605b6350b973e40 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/calibrate.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/calibrate.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/calibrate.o.d" -o ${OBJECTDIR}/_ext/59636182/calibrate.o ../../../../../MiniWin/calibrate.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin.o: ../../../../../MiniWin/miniwin.c  .generated_files/flags/default/d9b941a08fbaa3c3e11163edcca9a5b8057fbbc0 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin.o ../../../../../MiniWin/miniwin.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_debug.o: ../../../../../MiniWin/miniwin_debug.c  .generated_files/flags/default/232a3db8803a97bd68166fbaf84b239f2f28edeb .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_debug.o ../../../../../MiniWin/miniwin_debug.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o: ../../../../../MiniWin/miniwin_message_queue.c  .generated_files/flags/default/20746b5d8f2dd58cec13fa9a631aa73a825d06b4 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o ../../../../../MiniWin/miniwin_message_queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_settings.o: ../../../../../MiniWin/miniwin_settings.c  .generated_files/flags/default/772cd335dd68effe86f7568766392d13bf014e0d .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_settings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_settings.o ../../../../../MiniWin/miniwin_settings.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_touch.o: ../../../../../MiniWin/miniwin_touch.c  .generated_files/flags/default/d4b5cbd2f7bb93fef95c9339adc2e556e6d8e8bc .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_touch.o ../../../../../MiniWin/miniwin_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o: ../../../../../MiniWin/miniwin_tree_container.c  .generated_files/flags/default/61dc7a7d429a3ac255323d28bc351e6547ad192e .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o ../../../../../MiniWin/miniwin_tree_container.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_utilities.o: ../../../../../MiniWin/miniwin_utilities.c  .generated_files/flags/default/a1257e04e422b829f6a830d35316938f5acbdfc8 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o ../../../../../MiniWin/miniwin_utilities.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/main.o: ../../../../../MiniWinFile_Common/main.c  .generated_files/flags/default/cb59c6aa77b19e635084f369f7a5de066458eda9 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/main.o.d" -o ${OBJECTDIR}/_ext/165771656/main.o ../../../../../MiniWinFile_Common/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/miniwin_user.o: ../../../../../MiniWinFile_Common/miniwin_user.c  .generated_files/flags/default/1a6e0bd97b18d519c26b30ba494e327380e5a980 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/miniwin_user.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/miniwin_user.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/miniwin_user.o.d" -o ${OBJECTDIR}/_ext/165771656/miniwin_user.o ../../../../../MiniWinFile_Common/miniwin_user.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_file.o: ../../../../../MiniWinFile_Common/window_file.c  .generated_files/flags/default/32532eec791de4c89dedfe329f3d6ddca60f08de .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_file.o.d" -o ${OBJECTDIR}/_ext/165771656/window_file.o ../../../../../MiniWinFile_Common/window_file.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_file_tree.o: ../../../../../MiniWinFile_Common/window_file_tree.c  .generated_files/flags/default/85afeb6e8484b30e87573725eb91d1492012a73b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file_tree.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file_tree.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_file_tree.o.d" -o ${OBJECTDIR}/_ext/165771656/window_file_tree.o ../../../../../MiniWinFile_Common/window_file_tree.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_image.o: ../../../../../MiniWinFile_Common/window_image.c  .generated_files/flags/default/f75218bf33c7860b8a58cc4cb40bebc6a00f3471 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_image.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_image.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_image.o.d" -o ${OBJECTDIR}/_ext/165771656/window_image.o ../../../../../MiniWinFile_Common/window_image.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_selection.o: ../../../../../MiniWinFile_Common/window_selection.c  .generated_files/flags/default/79d24a8f544abbc4d403f0c0f44643e802c3319b .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_selection.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_selection.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_selection.o.d" -o ${OBJECTDIR}/_ext/165771656/window_selection.o ../../../../../MiniWinFile_Common/window_selection.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_text.o: ../../../../../MiniWinFile_Common/window_text.c  .generated_files/flags/default/1b1f05238df8e60f0968ab033414fc0a31f37222 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_text.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_text.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_text.o.d" -o ${OBJECTDIR}/_ext/165771656/window_text.o ../../../../../MiniWinFile_Common/window_text.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1445274692/app.o: ../../src/app.c  .generated_files/flags/default/c2aefa51169c6ca21d03c5442bfad32bd19202c8 .generated_files/flags/default/81bc5fc5a660e0b86762e654f4f91d7af1decfb7
	@${MKDIR} "${OBJECTDIR}/_ext/1445274692" 
	@${RM} ${OBJECTDIR}/_ext/1445274692/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1445274692/app.o.d" -o ${OBJECTDIR}/_ext/1445274692/app.o ../../src/app.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/MiniWinFile.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/config/default/p32MZ2048EFM100.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -mreserve=prog@0x1D1FC000:0x1D1FFFFF -o ${DISTDIR}/MiniWinFile.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x37F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/MiniWinFile.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/default/p32MZ2048EFM100.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mreserve=prog@0x1D1FC000:0x1D1FFFFF -o ${DISTDIR}/MiniWinFile.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/MiniWinFile.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
