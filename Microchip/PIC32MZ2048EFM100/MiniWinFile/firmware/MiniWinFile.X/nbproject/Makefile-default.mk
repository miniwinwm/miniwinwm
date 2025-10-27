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
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/flags/default/11fa9ef24ccb2b221cc02a2d7ebd5e4da25903c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1249264884/plib_coretimer.o: ../src/config/default/peripheral/coretimer/plib_coretimer.c  .generated_files/flags/default/7e8a2c21e71e1c9457c8125ab1c5f9401d2c596 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1249264884" 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ../src/config/default/peripheral/coretimer/plib_coretimer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/flags/default/4acb81c223cab32f6b61e34cba26fe406f3d7378 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/flags/default/3d090b499b84b913d2eadddbb59be86f14f888e4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60176403/plib_nvm.o: ../src/config/default/peripheral/nvm/plib_nvm.c  .generated_files/flags/default/58203d3cf6601b676e4bbe1d0b22246c9bfd64f7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60176403" 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ../src/config/default/peripheral/nvm/plib_nvm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/298189674/plib_spi2_master.o: ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c  .generated_files/flags/default/588c63b0b74e49816763c60b81968cb9da5d490f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/298189674" 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d" -o ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/298189674/plib_spi1_master.o: ../src/config/default/peripheral/spi/spi_master/plib_spi1_master.c  .generated_files/flags/default/7a6c30aa2f17e196806a19855e0b0d74b54911bb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/298189674" 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/298189674/plib_spi1_master.o.d" -o ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o ../src/config/default/peripheral/spi/spi_master/plib_spi1_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60181895/plib_tmr2.o: ../src/config/default/peripheral/tmr/plib_tmr2.c  .generated_files/flags/default/75493cf7c89d76ddbe837813dc3c707ed631d877 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ../src/config/default/peripheral/tmr/plib_tmr2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60181895/plib_tmr3.o: ../src/config/default/peripheral/tmr/plib_tmr3.c  .generated_files/flags/default/d07a0b6d22f55056283a07c944a67fc94fbe20f8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr3.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr3.o ../src/config/default/peripheral/tmr/plib_tmr3.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/679f00d76764e1549111da2c0b2fd423246332e8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/flags/default/b738cf7c8481c23e8dc78575dec1ee29c215bb5c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/flags/default/e736d854a451f42c1f447b17de49ae0948657546 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/flags/default/dada177ae250548076f60ed592191b5da3e50667 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/ff.o: ../../FatFS/ff.c  .generated_files/flags/default/88c571f8282776201abee8b3af79f2ee89629866 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/ff.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/ff.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/ff.o.d" -o ${OBJECTDIR}/_ext/1592496102/ff.o ../../FatFS/ff.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/sdmm.o: ../../FatFS/sdmm.c  .generated_files/flags/default/5b866ba78ffc055fbc21c36c370951573d692882 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/sdmm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/sdmm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/sdmm.o.d" -o ${OBJECTDIR}/_ext/1592496102/sdmm.o ../../FatFS/sdmm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/spi_driver.o: ../../FatFS/spi_driver.c  .generated_files/flags/default/83505bb401959950c1cd81f4395ec149dfc74d29 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/spi_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/spi_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/spi_driver.o.d" -o ${OBJECTDIR}/_ext/1592496102/spi_driver.o ../../FatFS/spi_driver.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/backspace_key.o: ../../../../../MiniWin/bitmaps/backspace_key.c  .generated_files/flags/default/6a8ea6afc705daf8e6b4ac8924d53789bc282105 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/backspace_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/backspace_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/backspace_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/backspace_key.o ../../../../../MiniWin/bitmaps/backspace_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/close_icon.o: ../../../../../MiniWin/bitmaps/close_icon.c  .generated_files/flags/default/2f1c876f79f9e03da4ea8eef3663bf054474a783 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/close_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/close_icon.o ../../../../../MiniWin/bitmaps/close_icon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/close_icon_large.o: ../../../../../MiniWin/bitmaps/close_icon_large.c  .generated_files/flags/default/64007141c79f46dc4340d172569c6b43e4eef1ad .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/close_icon_large.o ../../../../../MiniWin/bitmaps/close_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/file_icon_large.o: ../../../../../MiniWin/bitmaps/file_icon_large.c  .generated_files/flags/default/5100b82b49d3242107d7279253327ca26e19135e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/file_icon_large.o ../../../../../MiniWin/bitmaps/file_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/file_icon_small.o: ../../../../../MiniWin/bitmaps/file_icon_small.c  .generated_files/flags/default/79afa59c22d1f1cd2da4a3195a5b826bee7e1a92 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/file_icon_small.o ../../../../../MiniWin/bitmaps/file_icon_small.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o: ../../../../../MiniWin/bitmaps/folder_close_icon_large.c  .generated_files/flags/default/50faca2a94c48335031e01d60f5c21518ccd0a7d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o ../../../../../MiniWin/bitmaps/folder_close_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o: ../../../../../MiniWin/bitmaps/folder_close_icon_small.c  .generated_files/flags/default/e79fc0693e8c6e1c1b40dab9284b000c5641fe8a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o ../../../../../MiniWin/bitmaps/folder_close_icon_small.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_icon_large.o: ../../../../../MiniWin/bitmaps/folder_icon_large.c  .generated_files/flags/default/52abb08d7f1205a6e74b593be4270897f27b3d9b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o ../../../../../MiniWin/bitmaps/folder_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_icon_small.o: ../../../../../MiniWin/bitmaps/folder_icon_small.c  .generated_files/flags/default/f2b5ab2e536374aa85f80c93b03cc3b4e6e0ba3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o ../../../../../MiniWin/bitmaps/folder_icon_small.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o: ../../../../../MiniWin/bitmaps/folder_open_icon_large.c  .generated_files/flags/default/c1b715808a54caeadbaf50f92f90b7e71f876437 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o ../../../../../MiniWin/bitmaps/folder_open_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o: ../../../../../MiniWin/bitmaps/folder_open_icon_small.c  .generated_files/flags/default/6363868ff533c64855423cae045d2ed66ff9c26b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o ../../../../../MiniWin/bitmaps/folder_open_icon_small.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/let_key.o: ../../../../../MiniWin/bitmaps/let_key.c  .generated_files/flags/default/d30cb0d478f5fb0bda7d1c5dc77a0421d378f479 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/let_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/let_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/let_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/let_key.o ../../../../../MiniWin/bitmaps/let_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/maximise_icon.o: ../../../../../MiniWin/bitmaps/maximise_icon.c  .generated_files/flags/default/a6fa41395a7daf6730867d6fc4e21785320c4f52 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/maximise_icon.o ../../../../../MiniWin/bitmaps/maximise_icon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o: ../../../../../MiniWin/bitmaps/maximise_icon_large.c  .generated_files/flags/default/e5e02b5723e57ca2220932125c29c8a91a08cc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o ../../../../../MiniWin/bitmaps/maximise_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/minimise_icon.o: ../../../../../MiniWin/bitmaps/minimise_icon.c  .generated_files/flags/default/7ad0953cde436ec0046af8c76a8fd7e43f924ada .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/minimise_icon.o ../../../../../MiniWin/bitmaps/minimise_icon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o: ../../../../../MiniWin/bitmaps/minimise_icon_large.c  .generated_files/flags/default/ecca7835cc1ba0520163ec1f81349a654e69a550 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o ../../../../../MiniWin/bitmaps/minimise_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/num_key.o: ../../../../../MiniWin/bitmaps/num_key.c  .generated_files/flags/default/361b17efb00c00e5c3a3026ad456497cc59dd87 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/num_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/num_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/num_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/num_key.o ../../../../../MiniWin/bitmaps/num_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/resize_icon.o: ../../../../../MiniWin/bitmaps/resize_icon.c  .generated_files/flags/default/b11ab1814c8d886642e29f0fc2f35954dff6909a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/resize_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/resize_icon.o ../../../../../MiniWin/bitmaps/resize_icon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/resize_icon_large.o: ../../../../../MiniWin/bitmaps/resize_icon_large.c  .generated_files/flags/default/347f2199d0dcbaa7b1ead0dd5780d00fc61271ed .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o ../../../../../MiniWin/bitmaps/resize_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/shift_key.o: ../../../../../MiniWin/bitmaps/shift_key.c  .generated_files/flags/default/c480c30addd3a9616d4a8c2821e8e3e6cfd0728e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/shift_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/shift_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/shift_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/shift_key.o ../../../../../MiniWin/bitmaps/shift_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/sym_key.o: ../../../../../MiniWin/bitmaps/sym_key.c  .generated_files/flags/default/28e82e6d7b629e02034d6a53e9fbe43c2905ec9b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/sym_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/sym_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/sym_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/sym_key.o ../../../../../MiniWin/bitmaps/sym_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/tick.o: ../../../../../MiniWin/bitmaps/tick.c  .generated_files/flags/default/52515f59c2778ace21f08096486a42823d5a4583 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/tick.o.d" -o ${OBJECTDIR}/_ext/1275709973/tick.o ../../../../../MiniWin/bitmaps/tick.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/tick_large.o: ../../../../../MiniWin/bitmaps/tick_large.c  .generated_files/flags/default/3ece6f5e282475204229d0f59ede9b474273d5be .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/tick_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/tick_large.o ../../../../../MiniWin/bitmaps/tick_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o: ../../../../../MiniWin/dialogs/dialog_colour_chooser.c  .generated_files/flags/default/55f227a88345aa210368b0101e8f072857549a0b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o ../../../../../MiniWin/dialogs/dialog_colour_chooser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o: ../../../../../MiniWin/dialogs/dialog_date_chooser.c  .generated_files/flags/default/da0df81f990f50e91461e8c026b2ebf2fd6770cf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o ../../../../../MiniWin/dialogs/dialog_date_chooser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o: ../../../../../MiniWin/dialogs/dialog_file_chooser.c  .generated_files/flags/default/a4d8360e90cd694f043dab8b6b38c87acfb1edef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o ../../../../../MiniWin/dialogs/dialog_file_chooser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_number_entry.o: ../../../../../MiniWin/dialogs/dialog_number_entry.c  .generated_files/flags/default/2e0ee0ac671b4c34f4684346048164cb77b0fa5c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o ../../../../../MiniWin/dialogs/dialog_number_entry.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_one_button.o: ../../../../../MiniWin/dialogs/dialog_one_button.c  .generated_files/flags/default/fe973456c2fdec85be69c678f95dd2a5b241705b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_one_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_one_button.o ../../../../../MiniWin/dialogs/dialog_one_button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_text_entry.o: ../../../../../MiniWin/dialogs/dialog_text_entry.c  .generated_files/flags/default/aa655e4c3968c78e246478c48583c01e5b37975c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o ../../../../../MiniWin/dialogs/dialog_text_entry.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o: ../../../../../MiniWin/dialogs/dialog_time_chooser.c  .generated_files/flags/default/e5feacd6ba8707c012ab0434fcf24d2201a6c287 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o ../../../../../MiniWin/dialogs/dialog_time_chooser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_two_button.o: ../../../../../MiniWin/dialogs/dialog_two_button.c  .generated_files/flags/default/3534a71a3ee1ca019c601b80819ee9614b424a46 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_two_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_two_button.o ../../../../../MiniWin/dialogs/dialog_two_button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font12.o: ../../../../../MiniWin/gl/fonts/bitmapped/font12.c  .generated_files/flags/default/cf84470582efce9ef23e6590abc3128277e1884d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font12.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font12.o.d" -o ${OBJECTDIR}/_ext/194049764/font12.o ../../../../../MiniWin/gl/fonts/bitmapped/font12.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font16.o: ../../../../../MiniWin/gl/fonts/bitmapped/font16.c  .generated_files/flags/default/a41b059f47da549cb32c06b8349be492ec5d14e7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font16.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font16.o.d" -o ${OBJECTDIR}/_ext/194049764/font16.o ../../../../../MiniWin/gl/fonts/bitmapped/font16.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font20.o: ../../../../../MiniWin/gl/fonts/bitmapped/font20.c  .generated_files/flags/default/21054e78fcedb0ab87cae37db509a165404eb0a2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font20.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font20.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font20.o.d" -o ${OBJECTDIR}/_ext/194049764/font20.o ../../../../../MiniWin/gl/fonts/bitmapped/font20.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font24.o: ../../../../../MiniWin/gl/fonts/bitmapped/font24.c  .generated_files/flags/default/4fcb33f86db03198f4285636c53148c21865bcf6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font24.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font24.o.d" -o ${OBJECTDIR}/_ext/194049764/font24.o ../../../../../MiniWin/gl/fonts/bitmapped/font24.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font9.o: ../../../../../MiniWin/gl/fonts/bitmapped/font9.c  .generated_files/flags/default/5d373ea25db40b6fce1f87a839a63849548b4cc6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font9.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font9.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font9.o.d" -o ${OBJECTDIR}/_ext/194049764/font9.o ../../../../../MiniWin/gl/fonts/bitmapped/font9.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/gl_title_font.o: ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c  .generated_files/flags/default/8d4af0d12c6c293f0a2f451267d352d9a82b38a0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/gl_title_font.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/gl_title_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/gl_title_font.o.d" -o ${OBJECTDIR}/_ext/194049764/gl_title_font.o ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_bwfont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c  .generated_files/flags/default/12a52badb35821cc6a299523eb5cdafafbce3c95 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_encoding.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c  .generated_files/flags/default/1ed33fc9fe395b58a2d08a1cc20b19bd7f0f9a2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_encoding.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_encoding.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_font.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c  .generated_files/flags/default/78c8e8e4c2c5e219da9dbaa41185e21c297ffc83 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_font.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_font.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_font.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_justify.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c  .generated_files/flags/default/c70dea75226a7c3d8160d825961d7164786777ae .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_justify.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_justify.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_justify.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_justify.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_kerning.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c  .generated_files/flags/default/666d58225dedfbc6f81c91bffb9f65e60915ce58 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_kerning.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_kerning.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_rlefont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c  .generated_files/flags/default/fb1a2d509e1f519d7d40f0eca1543675f20b1a09 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c  .generated_files/flags/default/62148b17dfef950be3763937ff331e60ef738d31 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c  .generated_files/flags/default/acb73db3a60565a7eaa325c4d2691c0b8e5735f8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o: ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c  .generated_files/flags/default/fe306bd17dca88391fcb86546e00e440d1684180 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d" -o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o: ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c  .generated_files/flags/default/be03454c5f82faaa4c64f52422fcb3b494ff2c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d" -o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o: ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c  .generated_files/flags/default/8cdfaba7dd931094a226a832afec27e26c77a3ac .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d" -o ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494914114/gl.o: ../../../../../MiniWin/gl/gl.c  .generated_files/flags/default/322e075a72bb52d3b3a1e7ce85357fde4910787 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494914114" 
	@${RM} ${OBJECTDIR}/_ext/1494914114/gl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494914114/gl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494914114/gl.o.d" -o ${OBJECTDIR}/_ext/1494914114/gl.o ../../../../../MiniWin/gl/gl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_delay.o: ../../../../../MiniWin/hal/DevKitC/hal_delay.c  .generated_files/flags/default/528a86052fe19c52187f32ee6e5d11b467c3a8fd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_delay.o ../../../../../MiniWin/hal/DevKitC/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_lcd.o: ../../../../../MiniWin/hal/DevKitC/hal_lcd.c  .generated_files/flags/default/34db56378509bc1b750fcbc80fe4596dfde0a120 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_lcd.o ../../../../../MiniWin/hal/DevKitC/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_non_vol.o: ../../../../../MiniWin/hal/DevKitC/hal_non_vol.c  .generated_files/flags/default/d2cdd19bfca6e71bbfe53dcdd99c441197aa1b56 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o ../../../../../MiniWin/hal/DevKitC/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_timer.o: ../../../../../MiniWin/hal/DevKitC/hal_timer.c  .generated_files/flags/default/8f5b69c2f33e749e34d2ebb6a63da3702435dc34 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_timer.o ../../../../../MiniWin/hal/DevKitC/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_touch.o: ../../../../../MiniWin/hal/DevKitC/hal_touch.c  .generated_files/flags/default/7ed802903b6536fa42995e27a6b5a306b0acb8f3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_touch.o ../../../../../MiniWin/hal/DevKitC/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_delay.o: ../../../../../MiniWin/hal/linux/hal_delay.c  .generated_files/flags/default/f058c989057e67251f6154d60e183d0924a2ada3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_delay.o ../../../../../MiniWin/hal/linux/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_lcd.o: ../../../../../MiniWin/hal/linux/hal_lcd.c  .generated_files/flags/default/4e2e084c96aa847d4d5016f55a1de945614596ff .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_lcd.o ../../../../../MiniWin/hal/linux/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_non_vol.o: ../../../../../MiniWin/hal/linux/hal_non_vol.c  .generated_files/flags/default/98ebeee646fc5711f0b7fd61d7cd3f614d9edd4c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o ../../../../../MiniWin/hal/linux/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_timer.o: ../../../../../MiniWin/hal/linux/hal_timer.c  .generated_files/flags/default/11e21cb4da4bb4fd990567be03a57a78c3d923ae .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_timer.o ../../../../../MiniWin/hal/linux/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_touch.o: ../../../../../MiniWin/hal/linux/hal_touch.c  .generated_files/flags/default/1af88c0fe3f02d746bd46f9071bf9fc9ac9406e9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_touch.o ../../../../../MiniWin/hal/linux/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_delay.o: ../../../../../MiniWin/hal/lpc54628/hal_delay.c  .generated_files/flags/default/875d89b32c3e117389ba4a01063b4ce51509108a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_delay.o ../../../../../MiniWin/hal/lpc54628/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_lcd.o: ../../../../../MiniWin/hal/lpc54628/hal_lcd.c  .generated_files/flags/default/2008996674d5106177fa84fcf1c436b90220e158 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_lcd.o ../../../../../MiniWin/hal/lpc54628/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_non_vol.o: ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c  .generated_files/flags/default/f05eeb2ff6f9c2683f3bf01ebe8c67cadd386f6b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_timer.o: ../../../../../MiniWin/hal/lpc54628/hal_timer.c  .generated_files/flags/default/34cbd0141ba20a3a2a90ac31d402dd482663fd52 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_timer.o ../../../../../MiniWin/hal/lpc54628/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_touch.o: ../../../../../MiniWin/hal/lpc54628/hal_touch.c  .generated_files/flags/default/19ba9e3e6ffd494bb570267dfc2e4756580df8cf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_touch.o ../../../../../MiniWin/hal/lpc54628/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_delay.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c  .generated_files/flags/default/8c6a4009d802c8b1d4dc01ad1ef2e71f02494e4b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_delay.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_delay.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_lcd.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c  .generated_files/flags/default/e8637ee342d3d986736b3b0f80e2e9ff710d753e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_lcd.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_non_vol.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c  .generated_files/flags/default/faa39b691f6e74d3807d9b392aaca45ec9f43341 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_non_vol.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_timer.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c  .generated_files/flags/default/2276a7694b0318d1c41a1c1550355adfba796a02 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_timer.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_timer.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_touch.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c  .generated_files/flags/default/94a743c9c9072644da318787d5ac0d1e38b2364f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_touch.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_touch.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_delay.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_delay.c  .generated_files/flags/default/f999247904864f2c74adaf7e839ec3027eced92c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_delay.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_delay.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_lcd.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_lcd.c  .generated_files/flags/default/f24f79164fa067239664fd58e36bc7c0cd8dd2dd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_lcd.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_non_vol.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_non_vol.c  .generated_files/flags/default/e4c2d08484ddd7cff9c78cb5def54d4dec5332af .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_non_vol.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_timer.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_timer.c  .generated_files/flags/default/44c32bc693d824146d3e5b5148e125479e4b145a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_timer.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_timer.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_touch.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_touch.c  .generated_files/flags/default/dd598963abee7d280453525b6dd0ac61a78a78fb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_touch.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_touch.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_delay.o: ../../../../../MiniWin/hal/rx65n/hal_delay.c  .generated_files/flags/default/9fe883e2cafe9ff0bb7a62d02f92cdf78e9bafca .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_delay.o ../../../../../MiniWin/hal/rx65n/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_lcd.o: ../../../../../MiniWin/hal/rx65n/hal_lcd.c  .generated_files/flags/default/5a360e655f22a73fe0d794f8c4ad95b237f8ccc8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_lcd.o ../../../../../MiniWin/hal/rx65n/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_non_vol.o: ../../../../../MiniWin/hal/rx65n/hal_non_vol.c  .generated_files/flags/default/5b7451d760bb4211d68f3ab37e090f01e9623c9f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o ../../../../../MiniWin/hal/rx65n/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_timer.o: ../../../../../MiniWin/hal/rx65n/hal_timer.c  .generated_files/flags/default/e9dd953921f380f6f815e6fe851db05a9385aefe .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_timer.o ../../../../../MiniWin/hal/rx65n/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_touch.o: ../../../../../MiniWin/hal/rx65n/hal_touch.c  .generated_files/flags/default/1ae49f79805cf564480dc47270927429e6fe096b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_touch.o ../../../../../MiniWin/hal/rx65n/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_delay.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c  .generated_files/flags/default/8a9078336239473f3e98e7b0a48a6947027117c2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_delay.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_delay.o ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_lcd.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c  .generated_files/flags/default/c15ea001fb4b61ccea60b03372481cd5f8593043 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_lcd.o ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_non_vol.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c  .generated_files/flags/default/352f6b6c0601998db029fb48bb02c60ceb2488ea .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_non_vol.o ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_timer.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c  .generated_files/flags/default/4a28046258dfe884dea7830bbff57f3f054cb1c1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_timer.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_timer.o ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_touch.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c  .generated_files/flags/default/6cd94f0ca40718b82571de57a68c9dcf93905e9e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_touch.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_touch.o ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_delay.o: ../../../../../MiniWin/hal/stm32f407/hal_delay.c  .generated_files/flags/default/de369f9488300f6a2a45dbe9b79cc9cb11211380 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_delay.o ../../../../../MiniWin/hal/stm32f407/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_lcd.o: ../../../../../MiniWin/hal/stm32f407/hal_lcd.c  .generated_files/flags/default/6beaa235aed4f2792b5a42c923eceb06529ea691 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_lcd.o ../../../../../MiniWin/hal/stm32f407/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_non_vol.o: ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c  .generated_files/flags/default/885402928a7809f19701666fea1e2e95404901b3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_timer.o: ../../../../../MiniWin/hal/stm32f407/hal_timer.c  .generated_files/flags/default/7716985895394abbf964a1602a3a2d101b99c27f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_timer.o ../../../../../MiniWin/hal/stm32f407/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_touch.o: ../../../../../MiniWin/hal/stm32f407/hal_touch.c  .generated_files/flags/default/a691902a35e5ac973128668af69538908207fa1b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_touch.o ../../../../../MiniWin/hal/stm32f407/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_delay.o: ../../../../../MiniWin/hal/stm32f429/hal_delay.c  .generated_files/flags/default/8b1e48ef0d00916691679b909478764a4b9cd673 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_delay.o ../../../../../MiniWin/hal/stm32f429/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_lcd.o: ../../../../../MiniWin/hal/stm32f429/hal_lcd.c  .generated_files/flags/default/29b98a6147f0f8ce87655b465211d5a38d6a6681 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_lcd.o ../../../../../MiniWin/hal/stm32f429/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_non_vol.o: ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c  .generated_files/flags/default/3257e32fd8cd4453bbccef56a7e81494674d881a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_timer.o: ../../../../../MiniWin/hal/stm32f429/hal_timer.c  .generated_files/flags/default/275345cb49456e9d506cbbd03b648dc66182d129 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_timer.o ../../../../../MiniWin/hal/stm32f429/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_touch.o: ../../../../../MiniWin/hal/stm32f429/hal_touch.c  .generated_files/flags/default/b602efb060b7efa1ceea3f023f8102d42337675a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_touch.o ../../../../../MiniWin/hal/stm32f429/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_delay.o: ../../../../../MiniWin/hal/windows/hal_delay.c  .generated_files/flags/default/73d2416195c0d5aebed93dfd69f81e05e8238db4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_delay.o ../../../../../MiniWin/hal/windows/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_lcd.o: ../../../../../MiniWin/hal/windows/hal_lcd.c  .generated_files/flags/default/1d80f4738acb4cec7f0e017ae0c2cd71447fa231 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_lcd.o ../../../../../MiniWin/hal/windows/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_non_vol.o: ../../../../../MiniWin/hal/windows/hal_non_vol.c  .generated_files/flags/default/52d4576f432ff762f75ea14d475eb192354ff098 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o ../../../../../MiniWin/hal/windows/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_timer.o: ../../../../../MiniWin/hal/windows/hal_timer.c  .generated_files/flags/default/5eacd00216acfdb5644e85d6b3330266dc0aa03a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_timer.o ../../../../../MiniWin/hal/windows/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_touch.o: ../../../../../MiniWin/hal/windows/hal_touch.c  .generated_files/flags/default/384cd3f1eb7ee6e28e0b1e8a065818b33c3da24a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_touch.o ../../../../../MiniWin/hal/windows/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/902303450/hal_init.o: ../../../../../MiniWin/hal/hal_init.c  .generated_files/flags/default/fbbf367e44c5a362b8aaa77a378d5968b5c514f0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/902303450" 
	@${RM} ${OBJECTDIR}/_ext/902303450/hal_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/902303450/hal_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/902303450/hal_init.o.d" -o ${OBJECTDIR}/_ext/902303450/hal_init.o ../../../../../MiniWin/hal/hal_init.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_arrow.o: ../../../../../MiniWin/ui/ui_arrow.c  .generated_files/flags/default/682e255196770cc668ac1618d80c4c0be533b3d2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_arrow.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_arrow.o ../../../../../MiniWin/ui/ui_arrow.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_button.o: ../../../../../MiniWin/ui/ui_button.c  .generated_files/flags/default/d5e7f7b7dbf9085d06c79c5b322279b37e00f99d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_button.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_button.o ../../../../../MiniWin/ui/ui_button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_check_box.o: ../../../../../MiniWin/ui/ui_check_box.c  .generated_files/flags/default/9eb0699efc3bab5965ae46bce063202f477412e9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_check_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_check_box.o ../../../../../MiniWin/ui/ui_check_box.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_common.o: ../../../../../MiniWin/ui/ui_common.c  .generated_files/flags/default/bbc963d21d0db61e495c2cd859eaf1e1ae994449 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_common.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_common.o ../../../../../MiniWin/ui/ui_common.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_keyboard.o: ../../../../../MiniWin/ui/ui_keyboard.c  .generated_files/flags/default/365e8fa0b461f89537dbefba9df9ffcf00c7e303 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o ../../../../../MiniWin/ui/ui_keyboard.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_keypad.o: ../../../../../MiniWin/ui/ui_keypad.c  .generated_files/flags/default/8ebb31a2da869cbbc2ca057997cc4407e80de652 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keypad.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_keypad.o ../../../../../MiniWin/ui/ui_keypad.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_label.o: ../../../../../MiniWin/ui/ui_label.c  .generated_files/flags/default/4d80407559c9145bf3937249548d6635b6460ffd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_label.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_label.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_label.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_label.o ../../../../../MiniWin/ui/ui_label.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_list_box.o: ../../../../../MiniWin/ui/ui_list_box.c  .generated_files/flags/default/c82d08a5e946f6f588de9852f26b6675872670e6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_list_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_list_box.o ../../../../../MiniWin/ui/ui_list_box.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o: ../../../../../MiniWin/ui/ui_progress_bar.c  .generated_files/flags/default/9a429a18181156f887118ad3fbacc8cd8c9c7c0d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o ../../../../../MiniWin/ui/ui_progress_bar.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_radio_button.o: ../../../../../MiniWin/ui/ui_radio_button.c  .generated_files/flags/default/e2b862b95ace951cf5b7fcb0c9ef6f9f27e98c67 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o ../../../../../MiniWin/ui/ui_radio_button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o: ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c  .generated_files/flags/default/c968fc8e6dc9d4d72b81e2b2e1b3ca13c7c82f8d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o: ../../../../../MiniWin/ui/ui_scroll_bar_vert.c  .generated_files/flags/default/2ed46ed03f5a9ecd1fac37c746942b8ef21ccda3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o ../../../../../MiniWin/ui/ui_scroll_bar_vert.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_tabs.o: ../../../../../MiniWin/ui/ui_tabs.c  .generated_files/flags/default/1288db7fc0ab0fff38412784b244a71b0c365e1d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tabs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_tabs.o ../../../../../MiniWin/ui/ui_tabs.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_text_box.o: ../../../../../MiniWin/ui/ui_text_box.c  .generated_files/flags/default/cded543f31139d035b7751de8696b0b42838e221 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_text_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_text_box.o ../../../../../MiniWin/ui/ui_text_box.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_tree.o: ../../../../../MiniWin/ui/ui_tree.c  .generated_files/flags/default/216728a3eac7caea95d3941cd2a9cf57494482ec .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tree.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tree.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_tree.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_tree.o ../../../../../MiniWin/ui/ui_tree.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/calibrate.o: ../../../../../MiniWin/calibrate.c  .generated_files/flags/default/33faa283227360d51403c6cd073c02eb1550d7e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/calibrate.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/calibrate.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/calibrate.o.d" -o ${OBJECTDIR}/_ext/59636182/calibrate.o ../../../../../MiniWin/calibrate.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin.o: ../../../../../MiniWin/miniwin.c  .generated_files/flags/default/82f51e346b6204c3337a581fbd177a23a3a85cac .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin.o ../../../../../MiniWin/miniwin.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_debug.o: ../../../../../MiniWin/miniwin_debug.c  .generated_files/flags/default/1ff5e0cd1984ca34e28ba0c4a92c134ad5fae9e5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_debug.o ../../../../../MiniWin/miniwin_debug.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o: ../../../../../MiniWin/miniwin_message_queue.c  .generated_files/flags/default/c79fbc19fa5429857127ee075c08b31b8ed503d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o ../../../../../MiniWin/miniwin_message_queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_settings.o: ../../../../../MiniWin/miniwin_settings.c  .generated_files/flags/default/989b6d783a01b9d7083aeaa0b688fb77dc3125db .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_settings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_settings.o ../../../../../MiniWin/miniwin_settings.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_touch.o: ../../../../../MiniWin/miniwin_touch.c  .generated_files/flags/default/3e55cc92c725d8771c9ff9c4cc5a79643ae11047 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_touch.o ../../../../../MiniWin/miniwin_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o: ../../../../../MiniWin/miniwin_tree_container.c  .generated_files/flags/default/a2e7c5b0b83f69e1bd59dd7c0128d6c9f85ec537 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o ../../../../../MiniWin/miniwin_tree_container.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_utilities.o: ../../../../../MiniWin/miniwin_utilities.c  .generated_files/flags/default/2babd33ec60d3bf8f36b13323f5948c0357116bb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o ../../../../../MiniWin/miniwin_utilities.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/main.o: ../../../../../MiniWinFile_Common/main.c  .generated_files/flags/default/485584fcfc1c585f4dbe951c911c2d138521e88 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/main.o.d" -o ${OBJECTDIR}/_ext/165771656/main.o ../../../../../MiniWinFile_Common/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/miniwin_user.o: ../../../../../MiniWinFile_Common/miniwin_user.c  .generated_files/flags/default/26dd4af1723d11e81a1f5edb4936c9543a0abab5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/miniwin_user.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/miniwin_user.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/miniwin_user.o.d" -o ${OBJECTDIR}/_ext/165771656/miniwin_user.o ../../../../../MiniWinFile_Common/miniwin_user.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_file.o: ../../../../../MiniWinFile_Common/window_file.c  .generated_files/flags/default/ca09318cd168e17f929e8bbae028849b613a4aa4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_file.o.d" -o ${OBJECTDIR}/_ext/165771656/window_file.o ../../../../../MiniWinFile_Common/window_file.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_file_tree.o: ../../../../../MiniWinFile_Common/window_file_tree.c  .generated_files/flags/default/86f4952cbb12f86f04cc48ae4e9299194511e2ba .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file_tree.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file_tree.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_file_tree.o.d" -o ${OBJECTDIR}/_ext/165771656/window_file_tree.o ../../../../../MiniWinFile_Common/window_file_tree.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_image.o: ../../../../../MiniWinFile_Common/window_image.c  .generated_files/flags/default/8c64b6e6d44d0c18af109cb97c2952b1424432c6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_image.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_image.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_image.o.d" -o ${OBJECTDIR}/_ext/165771656/window_image.o ../../../../../MiniWinFile_Common/window_image.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_selection.o: ../../../../../MiniWinFile_Common/window_selection.c  .generated_files/flags/default/5220240a55e1aad1f2391cb672b7349d66b0d591 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_selection.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_selection.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_selection.o.d" -o ${OBJECTDIR}/_ext/165771656/window_selection.o ../../../../../MiniWinFile_Common/window_selection.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_text.o: ../../../../../MiniWinFile_Common/window_text.c  .generated_files/flags/default/f321c3cbf28fdd31362e31fbff3c68cc187914bc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_text.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_text.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_text.o.d" -o ${OBJECTDIR}/_ext/165771656/window_text.o ../../../../../MiniWinFile_Common/window_text.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1445274692/app.o: ../../src/app.c  .generated_files/flags/default/c238750d88a8765cb0acb632987e41c3a840839c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1445274692" 
	@${RM} ${OBJECTDIR}/_ext/1445274692/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1445274692/app.o.d" -o ${OBJECTDIR}/_ext/1445274692/app.o ../../src/app.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/flags/default/aded1d7b5c6471252c63d12068b344a9108278b9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1249264884/plib_coretimer.o: ../src/config/default/peripheral/coretimer/plib_coretimer.c  .generated_files/flags/default/bd01c0e2c0dfb6fc9426935c56d8315ef9b96a31 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1249264884" 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ../src/config/default/peripheral/coretimer/plib_coretimer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/flags/default/80bd7fe0e9fdfbaa1afbb402e9e9bdd0e7e09f6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/flags/default/430fbf4e2f134107d002bcef975e7e486522a4bb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60176403/plib_nvm.o: ../src/config/default/peripheral/nvm/plib_nvm.c  .generated_files/flags/default/da05d5a1a8b6d88d89234d55ea3696df39d5cc2a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60176403" 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ../src/config/default/peripheral/nvm/plib_nvm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/298189674/plib_spi2_master.o: ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c  .generated_files/flags/default/ee5e91cd488245e22b1c3e6d979a388a2c6e6ca1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/298189674" 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d" -o ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/298189674/plib_spi1_master.o: ../src/config/default/peripheral/spi/spi_master/plib_spi1_master.c  .generated_files/flags/default/8184ae732f39f327bcf44118de8731485df9dede .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/298189674" 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/298189674/plib_spi1_master.o.d" -o ${OBJECTDIR}/_ext/298189674/plib_spi1_master.o ../src/config/default/peripheral/spi/spi_master/plib_spi1_master.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60181895/plib_tmr2.o: ../src/config/default/peripheral/tmr/plib_tmr2.c  .generated_files/flags/default/c54fa716019c6a26adb6a055b0922245c3b00a04 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ../src/config/default/peripheral/tmr/plib_tmr2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60181895/plib_tmr3.o: ../src/config/default/peripheral/tmr/plib_tmr3.c  .generated_files/flags/default/a75a508012c9fda5395983af8f98992aa83d2e3a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr3.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr3.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr3.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr3.o ../src/config/default/peripheral/tmr/plib_tmr3.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/9818a3977c275952a71e6b532a2c2cd641417f3e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/flags/default/4e629f2b565795d58e546373730eee879e21493 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/flags/default/4008280a68d80bb87ffdd64d214126b24a06b875 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/flags/default/d228eae3f8b08437d1bbd8a53f057e46e52e7fcc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/ff.o: ../../FatFS/ff.c  .generated_files/flags/default/6a4dd1d828dd3e9b1e96c5e2b8d6a1e9e153361e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/ff.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/ff.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/ff.o.d" -o ${OBJECTDIR}/_ext/1592496102/ff.o ../../FatFS/ff.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/sdmm.o: ../../FatFS/sdmm.c  .generated_files/flags/default/63145b22ada16d9617ef3032c915cb42a360f6b0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/sdmm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/sdmm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/sdmm.o.d" -o ${OBJECTDIR}/_ext/1592496102/sdmm.o ../../FatFS/sdmm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1592496102/spi_driver.o: ../../FatFS/spi_driver.c  .generated_files/flags/default/ec285c4654bb3222bd4394b9e3fbc19412033c6a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1592496102" 
	@${RM} ${OBJECTDIR}/_ext/1592496102/spi_driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/1592496102/spi_driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1592496102/spi_driver.o.d" -o ${OBJECTDIR}/_ext/1592496102/spi_driver.o ../../FatFS/spi_driver.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/backspace_key.o: ../../../../../MiniWin/bitmaps/backspace_key.c  .generated_files/flags/default/70153ef70a124e3f782853ee41a11c01a40a6fdb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/backspace_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/backspace_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/backspace_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/backspace_key.o ../../../../../MiniWin/bitmaps/backspace_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/close_icon.o: ../../../../../MiniWin/bitmaps/close_icon.c  .generated_files/flags/default/46c85658674bbe2aa9bcc9f3b9e158445cfb95b2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/close_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/close_icon.o ../../../../../MiniWin/bitmaps/close_icon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/close_icon_large.o: ../../../../../MiniWin/bitmaps/close_icon_large.c  .generated_files/flags/default/7913874233bd66e2a3424a0f6cabf92756ada514 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/close_icon_large.o ../../../../../MiniWin/bitmaps/close_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/file_icon_large.o: ../../../../../MiniWin/bitmaps/file_icon_large.c  .generated_files/flags/default/f03a5b4b6f6e6f2692ecef371dc226d7d6fb582 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/file_icon_large.o ../../../../../MiniWin/bitmaps/file_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/file_icon_small.o: ../../../../../MiniWin/bitmaps/file_icon_small.c  .generated_files/flags/default/e504ed740fbeed662635efccfa6c0b1c6bac1fa5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/file_icon_small.o ../../../../../MiniWin/bitmaps/file_icon_small.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o: ../../../../../MiniWin/bitmaps/folder_close_icon_large.c  .generated_files/flags/default/eac0e1767e575a25971d7c5f36d0228fafef2da3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o ../../../../../MiniWin/bitmaps/folder_close_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o: ../../../../../MiniWin/bitmaps/folder_close_icon_small.c  .generated_files/flags/default/4bc8bf7687f2eed6e18b8d60af91d368f7f6ba19 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o ../../../../../MiniWin/bitmaps/folder_close_icon_small.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_icon_large.o: ../../../../../MiniWin/bitmaps/folder_icon_large.c  .generated_files/flags/default/bea06c57c96566a575d901b7ad829b25d331998 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o ../../../../../MiniWin/bitmaps/folder_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_icon_small.o: ../../../../../MiniWin/bitmaps/folder_icon_small.c  .generated_files/flags/default/9a8245c6ff35da79573c033e78cec85ee532db09 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o ../../../../../MiniWin/bitmaps/folder_icon_small.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o: ../../../../../MiniWin/bitmaps/folder_open_icon_large.c  .generated_files/flags/default/ca4bbadb71a752edd8eaaea8407bdae69b911924 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o ../../../../../MiniWin/bitmaps/folder_open_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o: ../../../../../MiniWin/bitmaps/folder_open_icon_small.c  .generated_files/flags/default/a93cd9e70b05b17b74cbd19347c544144c944385 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o ../../../../../MiniWin/bitmaps/folder_open_icon_small.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/let_key.o: ../../../../../MiniWin/bitmaps/let_key.c  .generated_files/flags/default/ac6dcabd928914a7c1c910ce2a49442de08f287 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/let_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/let_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/let_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/let_key.o ../../../../../MiniWin/bitmaps/let_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/maximise_icon.o: ../../../../../MiniWin/bitmaps/maximise_icon.c  .generated_files/flags/default/a0063373ef61cd0a01495d05aa3112638e62f394 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/maximise_icon.o ../../../../../MiniWin/bitmaps/maximise_icon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o: ../../../../../MiniWin/bitmaps/maximise_icon_large.c  .generated_files/flags/default/1271d16a2e0dc7d75bb5385664aebf34619788cc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o ../../../../../MiniWin/bitmaps/maximise_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/minimise_icon.o: ../../../../../MiniWin/bitmaps/minimise_icon.c  .generated_files/flags/default/b03b5d56d56d9cbb8c6dc083bc931ef2759b2a9d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/minimise_icon.o ../../../../../MiniWin/bitmaps/minimise_icon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o: ../../../../../MiniWin/bitmaps/minimise_icon_large.c  .generated_files/flags/default/220ada7526dff5db463ffa6bd901bc60fd0a3153 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o ../../../../../MiniWin/bitmaps/minimise_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/num_key.o: ../../../../../MiniWin/bitmaps/num_key.c  .generated_files/flags/default/99a05c3015d27cccd287181e0707fd96b2ba7b7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/num_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/num_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/num_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/num_key.o ../../../../../MiniWin/bitmaps/num_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/resize_icon.o: ../../../../../MiniWin/bitmaps/resize_icon.c  .generated_files/flags/default/beaf5a4c23ddcb0fefd0a84fc813af90d837659a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/resize_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/resize_icon.o ../../../../../MiniWin/bitmaps/resize_icon.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/resize_icon_large.o: ../../../../../MiniWin/bitmaps/resize_icon_large.c  .generated_files/flags/default/82f5350959b7b0011f1df4df1090f1412c8e2589 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o ../../../../../MiniWin/bitmaps/resize_icon_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/shift_key.o: ../../../../../MiniWin/bitmaps/shift_key.c  .generated_files/flags/default/ef67045220e187183a983dcc6bbc497f4808a159 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/shift_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/shift_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/shift_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/shift_key.o ../../../../../MiniWin/bitmaps/shift_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/sym_key.o: ../../../../../MiniWin/bitmaps/sym_key.c  .generated_files/flags/default/ac39649a1b4732f1980dfbf220d2de8ed0ba5e33 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/sym_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/sym_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/sym_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/sym_key.o ../../../../../MiniWin/bitmaps/sym_key.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/tick.o: ../../../../../MiniWin/bitmaps/tick.c  .generated_files/flags/default/7f6cfe7ef5cee6038d2fdcc8dc0d5482f188b314 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/tick.o.d" -o ${OBJECTDIR}/_ext/1275709973/tick.o ../../../../../MiniWin/bitmaps/tick.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/tick_large.o: ../../../../../MiniWin/bitmaps/tick_large.c  .generated_files/flags/default/ae2e8dad9760d28ff4c404db8cbb5174ecd01c51 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/tick_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/tick_large.o ../../../../../MiniWin/bitmaps/tick_large.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o: ../../../../../MiniWin/dialogs/dialog_colour_chooser.c  .generated_files/flags/default/cf6fdf551ab51c9a1b99d2bda84cff6055fe1326 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o ../../../../../MiniWin/dialogs/dialog_colour_chooser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o: ../../../../../MiniWin/dialogs/dialog_date_chooser.c  .generated_files/flags/default/98e5dc8e9c9fdfc1c59763f28ad83a2dd5f7cea5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o ../../../../../MiniWin/dialogs/dialog_date_chooser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o: ../../../../../MiniWin/dialogs/dialog_file_chooser.c  .generated_files/flags/default/18801414266f3ac8ac71614a821a011f9fc6db5f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o ../../../../../MiniWin/dialogs/dialog_file_chooser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_number_entry.o: ../../../../../MiniWin/dialogs/dialog_number_entry.c  .generated_files/flags/default/fa7c3004768b2bcc5c9451bb9a8c756adefc8168 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o ../../../../../MiniWin/dialogs/dialog_number_entry.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_one_button.o: ../../../../../MiniWin/dialogs/dialog_one_button.c  .generated_files/flags/default/68ec7621c903f6effef3c2775179f2b37a137798 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_one_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_one_button.o ../../../../../MiniWin/dialogs/dialog_one_button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_text_entry.o: ../../../../../MiniWin/dialogs/dialog_text_entry.c  .generated_files/flags/default/8a3b5b071c155f09a8c00ee1493964d6bd555a2a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o ../../../../../MiniWin/dialogs/dialog_text_entry.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o: ../../../../../MiniWin/dialogs/dialog_time_chooser.c  .generated_files/flags/default/6e61f0564e88d4739e343297fb23e39d0e303e3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o ../../../../../MiniWin/dialogs/dialog_time_chooser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_two_button.o: ../../../../../MiniWin/dialogs/dialog_two_button.c  .generated_files/flags/default/7b472c24743d993bd7164b39e947fc3de522bbd0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_two_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_two_button.o ../../../../../MiniWin/dialogs/dialog_two_button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font12.o: ../../../../../MiniWin/gl/fonts/bitmapped/font12.c  .generated_files/flags/default/db6701e177eaacb6842c03b21dae9a39aa054439 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font12.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font12.o.d" -o ${OBJECTDIR}/_ext/194049764/font12.o ../../../../../MiniWin/gl/fonts/bitmapped/font12.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font16.o: ../../../../../MiniWin/gl/fonts/bitmapped/font16.c  .generated_files/flags/default/afa90c4a1e7e7116fe06add2dfd6914481f6be5e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font16.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font16.o.d" -o ${OBJECTDIR}/_ext/194049764/font16.o ../../../../../MiniWin/gl/fonts/bitmapped/font16.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font20.o: ../../../../../MiniWin/gl/fonts/bitmapped/font20.c  .generated_files/flags/default/2396d3768a3d2cd884d059ad05f5d88b871e4b45 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font20.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font20.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font20.o.d" -o ${OBJECTDIR}/_ext/194049764/font20.o ../../../../../MiniWin/gl/fonts/bitmapped/font20.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font24.o: ../../../../../MiniWin/gl/fonts/bitmapped/font24.c  .generated_files/flags/default/796691c866150ae145fe30449e9f4edd0f8ed02 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font24.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font24.o.d" -o ${OBJECTDIR}/_ext/194049764/font24.o ../../../../../MiniWin/gl/fonts/bitmapped/font24.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font9.o: ../../../../../MiniWin/gl/fonts/bitmapped/font9.c  .generated_files/flags/default/2b5ee9311c3c42e8ca5ba60fadb5aaab10b52fa5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font9.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font9.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font9.o.d" -o ${OBJECTDIR}/_ext/194049764/font9.o ../../../../../MiniWin/gl/fonts/bitmapped/font9.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/gl_title_font.o: ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c  .generated_files/flags/default/39f579d77fbde503395d1d7d139f87fe54464e5d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/gl_title_font.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/gl_title_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/gl_title_font.o.d" -o ${OBJECTDIR}/_ext/194049764/gl_title_font.o ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_bwfont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c  .generated_files/flags/default/f503b87311f747f62949554c4a556595d5254b69 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_encoding.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c  .generated_files/flags/default/6801b647ba12287146736593a64c162a63b97f16 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_encoding.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_encoding.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_font.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c  .generated_files/flags/default/39fec695dd42dac81a0daac1150cac8dad4a6daf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_font.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_font.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_font.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_justify.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c  .generated_files/flags/default/ba61ddc6e1a347eed6b92279513e4bcae284a970 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_justify.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_justify.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_justify.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_justify.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_kerning.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c  .generated_files/flags/default/8bb44c8a8ace0ee92ec17d47f1e87c9ec37cc4c7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_kerning.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_kerning.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_rlefont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c  .generated_files/flags/default/aac470fc6417af76e46c2109088573ee41e8b82d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c  .generated_files/flags/default/1f3933f8822f78d6090eaa9d31e9e52e611c193a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c  .generated_files/flags/default/6b6a60827812814e1be2333105ce71bcbc690d50 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o: ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c  .generated_files/flags/default/18bf89208bbae2d1aa02ab271b60ebc1ed6f815d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d" -o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o: ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c  .generated_files/flags/default/5e433b9e86b6df9934c903c09de479aa5c08b125 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d" -o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o: ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c  .generated_files/flags/default/c74654c325aebe3df5463a6e6ef23192fe7270cb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d" -o ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494914114/gl.o: ../../../../../MiniWin/gl/gl.c  .generated_files/flags/default/ffd62fac2c721fd129902fde7cb777de85314c2e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494914114" 
	@${RM} ${OBJECTDIR}/_ext/1494914114/gl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494914114/gl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494914114/gl.o.d" -o ${OBJECTDIR}/_ext/1494914114/gl.o ../../../../../MiniWin/gl/gl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_delay.o: ../../../../../MiniWin/hal/DevKitC/hal_delay.c  .generated_files/flags/default/cd1bb1309eac2b58b854824e8710321efd7768e9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_delay.o ../../../../../MiniWin/hal/DevKitC/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_lcd.o: ../../../../../MiniWin/hal/DevKitC/hal_lcd.c  .generated_files/flags/default/f8c7a48d07f0caf5a92b0eff004033c5d0b131c3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_lcd.o ../../../../../MiniWin/hal/DevKitC/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_non_vol.o: ../../../../../MiniWin/hal/DevKitC/hal_non_vol.c  .generated_files/flags/default/cc6d6bfa99f570d13dd0b74e519203fcb8049ea9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_non_vol.o ../../../../../MiniWin/hal/DevKitC/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_timer.o: ../../../../../MiniWin/hal/DevKitC/hal_timer.c  .generated_files/flags/default/42f344b13978934b0a645b69df432dcde4052d5c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_timer.o ../../../../../MiniWin/hal/DevKitC/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1063548019/hal_touch.o: ../../../../../MiniWin/hal/DevKitC/hal_touch.c  .generated_files/flags/default/c24e9a095d116b4225e41965226ac3445ba2f2ec .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1063548019" 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1063548019/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1063548019/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1063548019/hal_touch.o ../../../../../MiniWin/hal/DevKitC/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_delay.o: ../../../../../MiniWin/hal/linux/hal_delay.c  .generated_files/flags/default/1bc8bf2a483031543484fb89abb527f39512de5c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_delay.o ../../../../../MiniWin/hal/linux/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_lcd.o: ../../../../../MiniWin/hal/linux/hal_lcd.c  .generated_files/flags/default/68827a012dcd7674d5e29c234bd0a63e16e96059 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_lcd.o ../../../../../MiniWin/hal/linux/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_non_vol.o: ../../../../../MiniWin/hal/linux/hal_non_vol.c  .generated_files/flags/default/2bf632d0d2d14ec560e6f0bdb25d9080679fce11 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o ../../../../../MiniWin/hal/linux/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_timer.o: ../../../../../MiniWin/hal/linux/hal_timer.c  .generated_files/flags/default/20de453f7476077602f6af83ecefba1535037cdb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_timer.o ../../../../../MiniWin/hal/linux/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_touch.o: ../../../../../MiniWin/hal/linux/hal_touch.c  .generated_files/flags/default/ad5674b4ad587b4ea767d6acb30edd5878869aa2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_touch.o ../../../../../MiniWin/hal/linux/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_delay.o: ../../../../../MiniWin/hal/lpc54628/hal_delay.c  .generated_files/flags/default/14fc6fc739010975ce5bacb1bd249570ea6808b7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_delay.o ../../../../../MiniWin/hal/lpc54628/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_lcd.o: ../../../../../MiniWin/hal/lpc54628/hal_lcd.c  .generated_files/flags/default/b33d1738b04a6bf06f0086d97b23a013d94fea88 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_lcd.o ../../../../../MiniWin/hal/lpc54628/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_non_vol.o: ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c  .generated_files/flags/default/f16dde103f00507b49a03351a951f221e1b0a3d7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_timer.o: ../../../../../MiniWin/hal/lpc54628/hal_timer.c  .generated_files/flags/default/ae4b528624bbfeefcc0b156221dfc4aaea03e861 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_timer.o ../../../../../MiniWin/hal/lpc54628/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_touch.o: ../../../../../MiniWin/hal/lpc54628/hal_touch.c  .generated_files/flags/default/95ed462b5d5915ca83e839bba17fa5a7c4a38d03 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_touch.o ../../../../../MiniWin/hal/lpc54628/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_delay.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c  .generated_files/flags/default/3a722b738ab370104fb25b7d41094dda4cd3fc68 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_delay.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_delay.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_lcd.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c  .generated_files/flags/default/c6efe26d2ac284ac62c0d7c8bc0850338bda4e7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_lcd.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_non_vol.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c  .generated_files/flags/default/af6b2b636f2d0f0cefb1e78c4f2d0de5819c6ead .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_non_vol.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_timer.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c  .generated_files/flags/default/39827172cf72e1a6ef3e0d6b6b2e7f79c8a01bb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_timer.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_timer.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_touch.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c  .generated_files/flags/default/690bc32a727fb026b592f27e15d6195d09ccb795 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_touch.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_touch.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_delay.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_delay.c  .generated_files/flags/default/2a25dbb4927d25bfee25b2c0f6c32a151bc6d2d7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_delay.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_delay.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_lcd.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_lcd.c  .generated_files/flags/default/297d030739ca861a3b012d5e9d7561d4dd6b2562 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_lcd.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_non_vol.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_non_vol.c  .generated_files/flags/default/4e801a242eb97abd297b7c9ef297c6feb91786ec .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_non_vol.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_timer.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_timer.c  .generated_files/flags/default/1d931379041fc51a4c2e326e7763d09e43ddc4dd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_timer.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_timer.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/776318040/hal_touch.o: ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_touch.c  .generated_files/flags/default/ca94d3ddc2e91b60aa3792b092f19e680bbd0ba2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/776318040" 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/776318040/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/776318040/hal_touch.o.d" -o ${OBJECTDIR}/_ext/776318040/hal_touch.o ../../../../../MiniWin/hal/PIC32MZ2048EFM100/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_delay.o: ../../../../../MiniWin/hal/rx65n/hal_delay.c  .generated_files/flags/default/25f0aeef805722be5724dcb4b4ceaa22a00fe9d5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_delay.o ../../../../../MiniWin/hal/rx65n/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_lcd.o: ../../../../../MiniWin/hal/rx65n/hal_lcd.c  .generated_files/flags/default/787633d8ec80ed2e55160de780c71d8a1e179b61 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_lcd.o ../../../../../MiniWin/hal/rx65n/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_non_vol.o: ../../../../../MiniWin/hal/rx65n/hal_non_vol.c  .generated_files/flags/default/804a245e89597631470bf9e7b37b14dabacea36c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o ../../../../../MiniWin/hal/rx65n/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_timer.o: ../../../../../MiniWin/hal/rx65n/hal_timer.c  .generated_files/flags/default/7eaac22021814c5a4ce861153f638dd18f79b3ab .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_timer.o ../../../../../MiniWin/hal/rx65n/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_touch.o: ../../../../../MiniWin/hal/rx65n/hal_touch.c  .generated_files/flags/default/f6cf5ea5a35444be7c24c87b669b0796bd3b7c64 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_touch.o ../../../../../MiniWin/hal/rx65n/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_delay.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c  .generated_files/flags/default/9efbc8cba89a5ab5cd2412fafb07470639b16d80 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_delay.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_delay.o ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_lcd.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c  .generated_files/flags/default/1c42c6c43a4ef7bac79922ab9b89d35a4ddb7e07 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_lcd.o ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_non_vol.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c  .generated_files/flags/default/69a088707676bf112b105e77e1a70a1c5d57a28a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_non_vol.o ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_timer.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c  .generated_files/flags/default/ab349787d53ca56350236f88e4851a9d09ac10fb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_timer.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_timer.o ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_touch.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c  .generated_files/flags/default/1fe0fcc53639755189df6ea3444bed33199b471 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_touch.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_touch.o ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_delay.o: ../../../../../MiniWin/hal/stm32f407/hal_delay.c  .generated_files/flags/default/bbba0ee3892ef827b3e922d1123b7b5dcecd2b68 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_delay.o ../../../../../MiniWin/hal/stm32f407/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_lcd.o: ../../../../../MiniWin/hal/stm32f407/hal_lcd.c  .generated_files/flags/default/30c82b9ca47ca290c3ad2ae8b7a8fb14432c58c9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_lcd.o ../../../../../MiniWin/hal/stm32f407/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_non_vol.o: ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c  .generated_files/flags/default/4f29008220a253b521dedb44901cf186c361f42b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_timer.o: ../../../../../MiniWin/hal/stm32f407/hal_timer.c  .generated_files/flags/default/840d0e072b815486d2a2762cd202a9b31522ee08 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_timer.o ../../../../../MiniWin/hal/stm32f407/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_touch.o: ../../../../../MiniWin/hal/stm32f407/hal_touch.c  .generated_files/flags/default/c87fa765649afecb3e58e0313bbdeb66ab2f6576 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_touch.o ../../../../../MiniWin/hal/stm32f407/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_delay.o: ../../../../../MiniWin/hal/stm32f429/hal_delay.c  .generated_files/flags/default/ca7272cf5c4fb866754d31e826e68e9a1bcc7c18 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_delay.o ../../../../../MiniWin/hal/stm32f429/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_lcd.o: ../../../../../MiniWin/hal/stm32f429/hal_lcd.c  .generated_files/flags/default/9242fddd52bf057bf446d18e7ec9cba3327c0e32 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_lcd.o ../../../../../MiniWin/hal/stm32f429/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_non_vol.o: ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c  .generated_files/flags/default/fb25ed691b13fc4d33e40542ae578b0953ddbb15 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_timer.o: ../../../../../MiniWin/hal/stm32f429/hal_timer.c  .generated_files/flags/default/8fe58f4f85639adae42fa680ed95cdcb21c19548 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_timer.o ../../../../../MiniWin/hal/stm32f429/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_touch.o: ../../../../../MiniWin/hal/stm32f429/hal_touch.c  .generated_files/flags/default/796a4db9fc544694cd3ea00807765363bdfd53ca .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_touch.o ../../../../../MiniWin/hal/stm32f429/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_delay.o: ../../../../../MiniWin/hal/windows/hal_delay.c  .generated_files/flags/default/234564d143be53370f846a3509f5acb702fda00c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_delay.o ../../../../../MiniWin/hal/windows/hal_delay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_lcd.o: ../../../../../MiniWin/hal/windows/hal_lcd.c  .generated_files/flags/default/36b7a3281bcb3b4386d45184e254369351776ea7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_lcd.o ../../../../../MiniWin/hal/windows/hal_lcd.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_non_vol.o: ../../../../../MiniWin/hal/windows/hal_non_vol.c  .generated_files/flags/default/12392c6127e97139ddaddcbd713e855c17aba1e1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o ../../../../../MiniWin/hal/windows/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_timer.o: ../../../../../MiniWin/hal/windows/hal_timer.c  .generated_files/flags/default/511a0552603e9e7940d482e0c5d350a3e898c85 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_timer.o ../../../../../MiniWin/hal/windows/hal_timer.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_touch.o: ../../../../../MiniWin/hal/windows/hal_touch.c  .generated_files/flags/default/1d636f54106e536daf6a6220035563a7d66033ce .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_touch.o ../../../../../MiniWin/hal/windows/hal_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/902303450/hal_init.o: ../../../../../MiniWin/hal/hal_init.c  .generated_files/flags/default/c3f07001146b7cf8266ff99ea739d674ed493764 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/902303450" 
	@${RM} ${OBJECTDIR}/_ext/902303450/hal_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/902303450/hal_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/902303450/hal_init.o.d" -o ${OBJECTDIR}/_ext/902303450/hal_init.o ../../../../../MiniWin/hal/hal_init.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_arrow.o: ../../../../../MiniWin/ui/ui_arrow.c  .generated_files/flags/default/15172378533470b9705e8a081a63ce9a2858f6f4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_arrow.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_arrow.o ../../../../../MiniWin/ui/ui_arrow.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_button.o: ../../../../../MiniWin/ui/ui_button.c  .generated_files/flags/default/828724bd176f2adb54edbfb68f1328ae32c2f9be .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_button.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_button.o ../../../../../MiniWin/ui/ui_button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_check_box.o: ../../../../../MiniWin/ui/ui_check_box.c  .generated_files/flags/default/38cab55e5f5923abb2f174f3580ee6b018e5653f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_check_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_check_box.o ../../../../../MiniWin/ui/ui_check_box.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_common.o: ../../../../../MiniWin/ui/ui_common.c  .generated_files/flags/default/2ff488610925ca07d05a5d150ae353e66b0f8bf6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_common.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_common.o ../../../../../MiniWin/ui/ui_common.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_keyboard.o: ../../../../../MiniWin/ui/ui_keyboard.c  .generated_files/flags/default/113e244342147fa31a397ae2a54183308c5ab657 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o ../../../../../MiniWin/ui/ui_keyboard.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_keypad.o: ../../../../../MiniWin/ui/ui_keypad.c  .generated_files/flags/default/eda3703ce22bc31357d888a88f286707f2297207 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keypad.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_keypad.o ../../../../../MiniWin/ui/ui_keypad.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_label.o: ../../../../../MiniWin/ui/ui_label.c  .generated_files/flags/default/8b586d3d2ba510893ee83265457cd67dd5a0badd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_label.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_label.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_label.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_label.o ../../../../../MiniWin/ui/ui_label.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_list_box.o: ../../../../../MiniWin/ui/ui_list_box.c  .generated_files/flags/default/769ceda9fe5c72ded783b49890ffc43145a45ca1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_list_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_list_box.o ../../../../../MiniWin/ui/ui_list_box.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o: ../../../../../MiniWin/ui/ui_progress_bar.c  .generated_files/flags/default/a8dc09abfd5b2fa1cf9d072cc2ee2929df3c6d5c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o ../../../../../MiniWin/ui/ui_progress_bar.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_radio_button.o: ../../../../../MiniWin/ui/ui_radio_button.c  .generated_files/flags/default/946b99552d2f0ec4914f6b73dee1b452523fe577 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o ../../../../../MiniWin/ui/ui_radio_button.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o: ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c  .generated_files/flags/default/3abb5c92c0df5cd3693e3c1162740e094f8e60f5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o: ../../../../../MiniWin/ui/ui_scroll_bar_vert.c  .generated_files/flags/default/ed505300daf4dce6bcd435614ccb36dfae017780 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o ../../../../../MiniWin/ui/ui_scroll_bar_vert.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_tabs.o: ../../../../../MiniWin/ui/ui_tabs.c  .generated_files/flags/default/a8d0b7c6b7e3ac94ef4c57fca78046eff12c3b9a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tabs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_tabs.o ../../../../../MiniWin/ui/ui_tabs.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_text_box.o: ../../../../../MiniWin/ui/ui_text_box.c  .generated_files/flags/default/3b3c9d2ecbdc8626bd25d50e4cff3879a53e3cfd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_text_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_text_box.o ../../../../../MiniWin/ui/ui_text_box.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_tree.o: ../../../../../MiniWin/ui/ui_tree.c  .generated_files/flags/default/908b406019148ed3be6f8c22ae896ee9f09512b0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tree.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tree.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_tree.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_tree.o ../../../../../MiniWin/ui/ui_tree.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/calibrate.o: ../../../../../MiniWin/calibrate.c  .generated_files/flags/default/15049d44212bd75e59820308d112be2ecf139d8a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/calibrate.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/calibrate.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/calibrate.o.d" -o ${OBJECTDIR}/_ext/59636182/calibrate.o ../../../../../MiniWin/calibrate.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin.o: ../../../../../MiniWin/miniwin.c  .generated_files/flags/default/cb78e5ee6e6a6d7aa5c6fda4f39707d1b87ec4a3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin.o ../../../../../MiniWin/miniwin.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_debug.o: ../../../../../MiniWin/miniwin_debug.c  .generated_files/flags/default/6272d63b424115ebcaa8e95f591e9188697b77a5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_debug.o ../../../../../MiniWin/miniwin_debug.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o: ../../../../../MiniWin/miniwin_message_queue.c  .generated_files/flags/default/d343b0967c24fc5c5c6e194ef62d99bf13e55228 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o ../../../../../MiniWin/miniwin_message_queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_settings.o: ../../../../../MiniWin/miniwin_settings.c  .generated_files/flags/default/332bcdd45907ba77d9511c13e69343ee565833c8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_settings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_settings.o ../../../../../MiniWin/miniwin_settings.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_touch.o: ../../../../../MiniWin/miniwin_touch.c  .generated_files/flags/default/f603710a667211cc26d16d21f87e38a0a5ea7d59 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_touch.o ../../../../../MiniWin/miniwin_touch.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o: ../../../../../MiniWin/miniwin_tree_container.c  .generated_files/flags/default/87acd545196d11ebf50344459ba5f1bed1280e49 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o ../../../../../MiniWin/miniwin_tree_container.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_utilities.o: ../../../../../MiniWin/miniwin_utilities.c  .generated_files/flags/default/91bf4d6dbb8b04e9539164affe4782cb967a5cd1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o ../../../../../MiniWin/miniwin_utilities.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/main.o: ../../../../../MiniWinFile_Common/main.c  .generated_files/flags/default/3555f1f4ba5893f12ec046b9f817429cc28afd4d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/main.o.d" -o ${OBJECTDIR}/_ext/165771656/main.o ../../../../../MiniWinFile_Common/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/miniwin_user.o: ../../../../../MiniWinFile_Common/miniwin_user.c  .generated_files/flags/default/10925e940fbbb84536b2cc09d79df6bd06b02416 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/miniwin_user.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/miniwin_user.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/miniwin_user.o.d" -o ${OBJECTDIR}/_ext/165771656/miniwin_user.o ../../../../../MiniWinFile_Common/miniwin_user.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_file.o: ../../../../../MiniWinFile_Common/window_file.c  .generated_files/flags/default/dc18a68f70886a4add22dc01b7992306cedaf3d4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_file.o.d" -o ${OBJECTDIR}/_ext/165771656/window_file.o ../../../../../MiniWinFile_Common/window_file.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_file_tree.o: ../../../../../MiniWinFile_Common/window_file_tree.c  .generated_files/flags/default/ce1cb5c57ffb4553395c32b68273e8c21be22847 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file_tree.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_file_tree.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_file_tree.o.d" -o ${OBJECTDIR}/_ext/165771656/window_file_tree.o ../../../../../MiniWinFile_Common/window_file_tree.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_image.o: ../../../../../MiniWinFile_Common/window_image.c  .generated_files/flags/default/a757253891fd891400e62ce4c92536150752c4b4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_image.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_image.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_image.o.d" -o ${OBJECTDIR}/_ext/165771656/window_image.o ../../../../../MiniWinFile_Common/window_image.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_selection.o: ../../../../../MiniWinFile_Common/window_selection.c  .generated_files/flags/default/9104623873d8b4ab2514fefd8091ae8a2e02222f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_selection.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_selection.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_selection.o.d" -o ${OBJECTDIR}/_ext/165771656/window_selection.o ../../../../../MiniWinFile_Common/window_selection.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/165771656/window_text.o: ../../../../../MiniWinFile_Common/window_text.c  .generated_files/flags/default/a415100f24620228947633d53738c4ed297f775c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/165771656" 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_text.o.d 
	@${RM} ${OBJECTDIR}/_ext/165771656/window_text.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -fno-common -DPIC32MZ2048EFM100 -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MZ2048EFM100_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWinFile_Common" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../FatFS" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/165771656/window_text.o.d" -o ${OBJECTDIR}/_ext/165771656/window_text.o ../../../../../MiniWinFile_Common/window_text.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1445274692/app.o: ../../src/app.c  .generated_files/flags/default/9826ce92156894f96e1c2eaa0b27b3ac15bd7573 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -mreserve=prog@0x1D1FC000:0x1D1FFFFF -o ${DISTDIR}/MiniWinFile.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x37F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/MiniWinFile.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/default/p32MZ2048EFM100.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -mreserve=prog@0x1D1FC000:0x1D1FFFFF -o ${DISTDIR}/MiniWinFile.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
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

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
