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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MiniWinSimple.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MiniWinSimple.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/coretimer/plib_coretimer.c ../src/config/default/peripheral/evic/plib_evic.c ../src/config/default/peripheral/gpio/plib_gpio.c ../src/config/default/peripheral/nvm/plib_nvm.c ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c ../src/config/default/peripheral/tmr/plib_tmr2.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../../../../../MiniWin/bitmaps/backspace_key.c ../../../../../MiniWin/bitmaps/close_icon.c ../../../../../MiniWin/bitmaps/close_icon_large.c ../../../../../MiniWin/bitmaps/file_icon_large.c ../../../../../MiniWin/bitmaps/file_icon_small.c ../../../../../MiniWin/bitmaps/folder_close_icon_large.c ../../../../../MiniWin/bitmaps/folder_close_icon_small.c ../../../../../MiniWin/bitmaps/folder_icon_large.c ../../../../../MiniWin/bitmaps/folder_icon_small.c ../../../../../MiniWin/bitmaps/folder_open_icon_large.c ../../../../../MiniWin/bitmaps/folder_open_icon_small.c ../../../../../MiniWin/bitmaps/let_key.c ../../../../../MiniWin/bitmaps/maximise_icon.c ../../../../../MiniWin/bitmaps/maximise_icon_large.c ../../../../../MiniWin/bitmaps/minimise_icon.c ../../../../../MiniWin/bitmaps/minimise_icon_large.c ../../../../../MiniWin/bitmaps/num_key.c ../../../../../MiniWin/bitmaps/resize_icon.c ../../../../../MiniWin/bitmaps/resize_icon_large.c ../../../../../MiniWin/bitmaps/shift_key.c ../../../../../MiniWin/bitmaps/sym_key.c ../../../../../MiniWin/bitmaps/tick.c ../../../../../MiniWin/bitmaps/tick_large.c ../../../../../MiniWin/dialogs/dialog_colour_chooser.c ../../../../../MiniWin/dialogs/dialog_date_chooser.c ../../../../../MiniWin/dialogs/dialog_file_chooser.c ../../../../../MiniWin/dialogs/dialog_number_entry.c ../../../../../MiniWin/dialogs/dialog_one_button.c ../../../../../MiniWin/dialogs/dialog_text_entry.c ../../../../../MiniWin/dialogs/dialog_time_chooser.c ../../../../../MiniWin/dialogs/dialog_two_button.c ../../../../../MiniWin/gl/fonts/bitmapped/font12.c ../../../../../MiniWin/gl/fonts/bitmapped/font16.c ../../../../../MiniWin/gl/fonts/bitmapped/font20.c ../../../../../MiniWin/gl/fonts/bitmapped/font24.c ../../../../../MiniWin/gl/fonts/bitmapped/font9.c ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c ../../../../../MiniWin/gl/gl.c ../../../../../MiniWin/hal/esp32-idf/hal_delay.c ../../../../../MiniWin/hal/esp32-idf/hal_lcd.c ../../../../../MiniWin/hal/esp32-idf/hal_non_vol.c ../../../../../MiniWin/hal/esp32-idf/hal_timer.c ../../../../../MiniWin/hal/esp32-idf/hal_touch.c ../../../../../MiniWin/hal/linux/hal_delay.c ../../../../../MiniWin/hal/linux/hal_lcd.c ../../../../../MiniWin/hal/linux/hal_non_vol.c ../../../../../MiniWin/hal/linux/hal_timer.c ../../../../../MiniWin/hal/linux/hal_touch.c ../../../../../MiniWin/hal/lpc54628/hal_delay.c ../../../../../MiniWin/hal/lpc54628/hal_lcd.c ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c ../../../../../MiniWin/hal/lpc54628/hal_timer.c ../../../../../MiniWin/hal/lpc54628/hal_touch.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c ../../../../../MiniWin/hal/rx65n/hal_delay.c ../../../../../MiniWin/hal/rx65n/hal_lcd.c ../../../../../MiniWin/hal/rx65n/hal_non_vol.c ../../../../../MiniWin/hal/rx65n/hal_timer.c ../../../../../MiniWin/hal/rx65n/hal_touch.c ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c ../../../../../MiniWin/hal/stm32f407/hal_delay.c ../../../../../MiniWin/hal/stm32f407/hal_lcd.c ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c ../../../../../MiniWin/hal/stm32f407/hal_timer.c ../../../../../MiniWin/hal/stm32f407/hal_touch.c ../../../../../MiniWin/hal/stm32f429/hal_delay.c ../../../../../MiniWin/hal/stm32f429/hal_lcd.c ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c ../../../../../MiniWin/hal/stm32f429/hal_timer.c ../../../../../MiniWin/hal/stm32f429/hal_touch.c ../../../../../MiniWin/hal/windows/hal_delay.c ../../../../../MiniWin/hal/windows/hal_lcd.c ../../../../../MiniWin/hal/windows/hal_non_vol.c ../../../../../MiniWin/hal/windows/hal_timer.c ../../../../../MiniWin/hal/windows/hal_touch.c ../../../../../MiniWin/hal/hal_init.c ../../../../../MiniWin/ui/ui_arrow.c ../../../../../MiniWin/ui/ui_button.c ../../../../../MiniWin/ui/ui_check_box.c ../../../../../MiniWin/ui/ui_common.c ../../../../../MiniWin/ui/ui_keyboard.c ../../../../../MiniWin/ui/ui_keypad.c ../../../../../MiniWin/ui/ui_label.c ../../../../../MiniWin/ui/ui_list_box.c ../../../../../MiniWin/ui/ui_progress_bar.c ../../../../../MiniWin/ui/ui_radio_button.c ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c ../../../../../MiniWin/ui/ui_scroll_bar_vert.c ../../../../../MiniWin/ui/ui_tabs.c ../../../../../MiniWin/ui/ui_text_box.c ../../../../../MiniWin/ui/ui_tree.c ../../../../../MiniWin/calibrate.c ../../../../../MiniWin/miniwin.c ../../../../../MiniWin/miniwin_debug.c ../../../../../MiniWin/miniwin_message_queue.c ../../../../../MiniWin/miniwin_settings.c ../../../../../MiniWin/miniwin_touch.c ../../../../../MiniWin/miniwin_tree_container.c ../../../../../MiniWin/miniwin_utilities.c ../../../../../MiniWinSimple_Common/main.c ../../../../../MiniWinSimple_Common/miniwin_user.c ../../../../../MiniWinSimple_Common/window_simple.c ../../src/app.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1275709973/backspace_key.o ${OBJECTDIR}/_ext/1275709973/close_icon.o ${OBJECTDIR}/_ext/1275709973/close_icon_large.o ${OBJECTDIR}/_ext/1275709973/file_icon_large.o ${OBJECTDIR}/_ext/1275709973/file_icon_small.o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o ${OBJECTDIR}/_ext/1275709973/let_key.o ${OBJECTDIR}/_ext/1275709973/maximise_icon.o ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o ${OBJECTDIR}/_ext/1275709973/minimise_icon.o ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o ${OBJECTDIR}/_ext/1275709973/num_key.o ${OBJECTDIR}/_ext/1275709973/resize_icon.o ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o ${OBJECTDIR}/_ext/1275709973/shift_key.o ${OBJECTDIR}/_ext/1275709973/sym_key.o ${OBJECTDIR}/_ext/1275709973/tick.o ${OBJECTDIR}/_ext/1275709973/tick_large.o ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o ${OBJECTDIR}/_ext/481733874/dialog_one_button.o ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o ${OBJECTDIR}/_ext/481733874/dialog_two_button.o ${OBJECTDIR}/_ext/194049764/font12.o ${OBJECTDIR}/_ext/194049764/font16.o ${OBJECTDIR}/_ext/194049764/font20.o ${OBJECTDIR}/_ext/194049764/font24.o ${OBJECTDIR}/_ext/194049764/font9.o ${OBJECTDIR}/_ext/194049764/gl_title_font.o ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o ${OBJECTDIR}/_ext/1391772861/mf_encoding.o ${OBJECTDIR}/_ext/1391772861/mf_font.o ${OBJECTDIR}/_ext/1391772861/mf_justify.o ${OBJECTDIR}/_ext/1391772861/mf_kerning.o ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o ${OBJECTDIR}/_ext/1494914114/gl.o ${OBJECTDIR}/_ext/1770599754/hal_delay.o ${OBJECTDIR}/_ext/1770599754/hal_lcd.o ${OBJECTDIR}/_ext/1770599754/hal_non_vol.o ${OBJECTDIR}/_ext/1770599754/hal_timer.o ${OBJECTDIR}/_ext/1770599754/hal_touch.o ${OBJECTDIR}/_ext/1184163457/hal_delay.o ${OBJECTDIR}/_ext/1184163457/hal_lcd.o ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o ${OBJECTDIR}/_ext/1184163457/hal_timer.o ${OBJECTDIR}/_ext/1184163457/hal_touch.o ${OBJECTDIR}/_ext/1305585261/hal_delay.o ${OBJECTDIR}/_ext/1305585261/hal_lcd.o ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o ${OBJECTDIR}/_ext/1305585261/hal_timer.o ${OBJECTDIR}/_ext/1305585261/hal_touch.o ${OBJECTDIR}/_ext/818872118/hal_delay.o ${OBJECTDIR}/_ext/818872118/hal_lcd.o ${OBJECTDIR}/_ext/818872118/hal_non_vol.o ${OBJECTDIR}/_ext/818872118/hal_timer.o ${OBJECTDIR}/_ext/818872118/hal_touch.o ${OBJECTDIR}/_ext/1178231276/hal_delay.o ${OBJECTDIR}/_ext/1178231276/hal_lcd.o ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o ${OBJECTDIR}/_ext/1178231276/hal_timer.o ${OBJECTDIR}/_ext/1178231276/hal_touch.o ${OBJECTDIR}/_ext/51196508/hal_delay.o ${OBJECTDIR}/_ext/51196508/hal_lcd.o ${OBJECTDIR}/_ext/51196508/hal_non_vol.o ${OBJECTDIR}/_ext/51196508/hal_timer.o ${OBJECTDIR}/_ext/51196508/hal_touch.o ${OBJECTDIR}/_ext/1317985835/hal_delay.o ${OBJECTDIR}/_ext/1317985835/hal_lcd.o ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o ${OBJECTDIR}/_ext/1317985835/hal_timer.o ${OBJECTDIR}/_ext/1317985835/hal_touch.o ${OBJECTDIR}/_ext/1317985899/hal_delay.o ${OBJECTDIR}/_ext/1317985899/hal_lcd.o ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o ${OBJECTDIR}/_ext/1317985899/hal_timer.o ${OBJECTDIR}/_ext/1317985899/hal_touch.o ${OBJECTDIR}/_ext/1357345870/hal_delay.o ${OBJECTDIR}/_ext/1357345870/hal_lcd.o ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o ${OBJECTDIR}/_ext/1357345870/hal_timer.o ${OBJECTDIR}/_ext/1357345870/hal_touch.o ${OBJECTDIR}/_ext/902303450/hal_init.o ${OBJECTDIR}/_ext/1494913683/ui_arrow.o ${OBJECTDIR}/_ext/1494913683/ui_button.o ${OBJECTDIR}/_ext/1494913683/ui_check_box.o ${OBJECTDIR}/_ext/1494913683/ui_common.o ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o ${OBJECTDIR}/_ext/1494913683/ui_keypad.o ${OBJECTDIR}/_ext/1494913683/ui_label.o ${OBJECTDIR}/_ext/1494913683/ui_list_box.o ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o ${OBJECTDIR}/_ext/1494913683/ui_tabs.o ${OBJECTDIR}/_ext/1494913683/ui_text_box.o ${OBJECTDIR}/_ext/1494913683/ui_tree.o ${OBJECTDIR}/_ext/59636182/calibrate.o ${OBJECTDIR}/_ext/59636182/miniwin.o ${OBJECTDIR}/_ext/59636182/miniwin_debug.o ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o ${OBJECTDIR}/_ext/59636182/miniwin_settings.o ${OBJECTDIR}/_ext/59636182/miniwin_touch.o ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o ${OBJECTDIR}/_ext/692562174/main.o ${OBJECTDIR}/_ext/692562174/miniwin_user.o ${OBJECTDIR}/_ext/692562174/window_simple.o ${OBJECTDIR}/_ext/1445274692/app.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/60165520/plib_clk.o.d ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d ${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d ${OBJECTDIR}/_ext/1171490990/initialization.o.d ${OBJECTDIR}/_ext/1171490990/interrupts.o.d ${OBJECTDIR}/_ext/1171490990/exceptions.o.d ${OBJECTDIR}/_ext/1275709973/backspace_key.o.d ${OBJECTDIR}/_ext/1275709973/close_icon.o.d ${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d ${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d ${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d ${OBJECTDIR}/_ext/1275709973/let_key.o.d ${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d ${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d ${OBJECTDIR}/_ext/1275709973/num_key.o.d ${OBJECTDIR}/_ext/1275709973/resize_icon.o.d ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d ${OBJECTDIR}/_ext/1275709973/shift_key.o.d ${OBJECTDIR}/_ext/1275709973/sym_key.o.d ${OBJECTDIR}/_ext/1275709973/tick.o.d ${OBJECTDIR}/_ext/1275709973/tick_large.o.d ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d ${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d ${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d ${OBJECTDIR}/_ext/194049764/font12.o.d ${OBJECTDIR}/_ext/194049764/font16.o.d ${OBJECTDIR}/_ext/194049764/font20.o.d ${OBJECTDIR}/_ext/194049764/font24.o.d ${OBJECTDIR}/_ext/194049764/font9.o.d ${OBJECTDIR}/_ext/194049764/gl_title_font.o.d ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d ${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d ${OBJECTDIR}/_ext/1391772861/mf_font.o.d ${OBJECTDIR}/_ext/1391772861/mf_justify.o.d ${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d ${OBJECTDIR}/_ext/1494914114/gl.o.d ${OBJECTDIR}/_ext/1770599754/hal_delay.o.d ${OBJECTDIR}/_ext/1770599754/hal_lcd.o.d ${OBJECTDIR}/_ext/1770599754/hal_non_vol.o.d ${OBJECTDIR}/_ext/1770599754/hal_timer.o.d ${OBJECTDIR}/_ext/1770599754/hal_touch.o.d ${OBJECTDIR}/_ext/1184163457/hal_delay.o.d ${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d ${OBJECTDIR}/_ext/1184163457/hal_timer.o.d ${OBJECTDIR}/_ext/1184163457/hal_touch.o.d ${OBJECTDIR}/_ext/1305585261/hal_delay.o.d ${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d ${OBJECTDIR}/_ext/1305585261/hal_timer.o.d ${OBJECTDIR}/_ext/1305585261/hal_touch.o.d ${OBJECTDIR}/_ext/818872118/hal_delay.o.d ${OBJECTDIR}/_ext/818872118/hal_lcd.o.d ${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d ${OBJECTDIR}/_ext/818872118/hal_timer.o.d ${OBJECTDIR}/_ext/818872118/hal_touch.o.d ${OBJECTDIR}/_ext/1178231276/hal_delay.o.d ${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d ${OBJECTDIR}/_ext/1178231276/hal_timer.o.d ${OBJECTDIR}/_ext/1178231276/hal_touch.o.d ${OBJECTDIR}/_ext/51196508/hal_delay.o.d ${OBJECTDIR}/_ext/51196508/hal_lcd.o.d ${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d ${OBJECTDIR}/_ext/51196508/hal_timer.o.d ${OBJECTDIR}/_ext/51196508/hal_touch.o.d ${OBJECTDIR}/_ext/1317985835/hal_delay.o.d ${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d ${OBJECTDIR}/_ext/1317985835/hal_timer.o.d ${OBJECTDIR}/_ext/1317985835/hal_touch.o.d ${OBJECTDIR}/_ext/1317985899/hal_delay.o.d ${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d ${OBJECTDIR}/_ext/1317985899/hal_timer.o.d ${OBJECTDIR}/_ext/1317985899/hal_touch.o.d ${OBJECTDIR}/_ext/1357345870/hal_delay.o.d ${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d ${OBJECTDIR}/_ext/1357345870/hal_timer.o.d ${OBJECTDIR}/_ext/1357345870/hal_touch.o.d ${OBJECTDIR}/_ext/902303450/hal_init.o.d ${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d ${OBJECTDIR}/_ext/1494913683/ui_button.o.d ${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d ${OBJECTDIR}/_ext/1494913683/ui_common.o.d ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d ${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d ${OBJECTDIR}/_ext/1494913683/ui_label.o.d ${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d ${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d ${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d ${OBJECTDIR}/_ext/1494913683/ui_tree.o.d ${OBJECTDIR}/_ext/59636182/calibrate.o.d ${OBJECTDIR}/_ext/59636182/miniwin.o.d ${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d ${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d ${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d ${OBJECTDIR}/_ext/692562174/main.o.d ${OBJECTDIR}/_ext/692562174/miniwin_user.o.d ${OBJECTDIR}/_ext/692562174/window_simple.o.d ${OBJECTDIR}/_ext/1445274692/app.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/60165520/plib_clk.o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1275709973/backspace_key.o ${OBJECTDIR}/_ext/1275709973/close_icon.o ${OBJECTDIR}/_ext/1275709973/close_icon_large.o ${OBJECTDIR}/_ext/1275709973/file_icon_large.o ${OBJECTDIR}/_ext/1275709973/file_icon_small.o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o ${OBJECTDIR}/_ext/1275709973/let_key.o ${OBJECTDIR}/_ext/1275709973/maximise_icon.o ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o ${OBJECTDIR}/_ext/1275709973/minimise_icon.o ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o ${OBJECTDIR}/_ext/1275709973/num_key.o ${OBJECTDIR}/_ext/1275709973/resize_icon.o ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o ${OBJECTDIR}/_ext/1275709973/shift_key.o ${OBJECTDIR}/_ext/1275709973/sym_key.o ${OBJECTDIR}/_ext/1275709973/tick.o ${OBJECTDIR}/_ext/1275709973/tick_large.o ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o ${OBJECTDIR}/_ext/481733874/dialog_one_button.o ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o ${OBJECTDIR}/_ext/481733874/dialog_two_button.o ${OBJECTDIR}/_ext/194049764/font12.o ${OBJECTDIR}/_ext/194049764/font16.o ${OBJECTDIR}/_ext/194049764/font20.o ${OBJECTDIR}/_ext/194049764/font24.o ${OBJECTDIR}/_ext/194049764/font9.o ${OBJECTDIR}/_ext/194049764/gl_title_font.o ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o ${OBJECTDIR}/_ext/1391772861/mf_encoding.o ${OBJECTDIR}/_ext/1391772861/mf_font.o ${OBJECTDIR}/_ext/1391772861/mf_justify.o ${OBJECTDIR}/_ext/1391772861/mf_kerning.o ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o ${OBJECTDIR}/_ext/1494914114/gl.o ${OBJECTDIR}/_ext/1770599754/hal_delay.o ${OBJECTDIR}/_ext/1770599754/hal_lcd.o ${OBJECTDIR}/_ext/1770599754/hal_non_vol.o ${OBJECTDIR}/_ext/1770599754/hal_timer.o ${OBJECTDIR}/_ext/1770599754/hal_touch.o ${OBJECTDIR}/_ext/1184163457/hal_delay.o ${OBJECTDIR}/_ext/1184163457/hal_lcd.o ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o ${OBJECTDIR}/_ext/1184163457/hal_timer.o ${OBJECTDIR}/_ext/1184163457/hal_touch.o ${OBJECTDIR}/_ext/1305585261/hal_delay.o ${OBJECTDIR}/_ext/1305585261/hal_lcd.o ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o ${OBJECTDIR}/_ext/1305585261/hal_timer.o ${OBJECTDIR}/_ext/1305585261/hal_touch.o ${OBJECTDIR}/_ext/818872118/hal_delay.o ${OBJECTDIR}/_ext/818872118/hal_lcd.o ${OBJECTDIR}/_ext/818872118/hal_non_vol.o ${OBJECTDIR}/_ext/818872118/hal_timer.o ${OBJECTDIR}/_ext/818872118/hal_touch.o ${OBJECTDIR}/_ext/1178231276/hal_delay.o ${OBJECTDIR}/_ext/1178231276/hal_lcd.o ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o ${OBJECTDIR}/_ext/1178231276/hal_timer.o ${OBJECTDIR}/_ext/1178231276/hal_touch.o ${OBJECTDIR}/_ext/51196508/hal_delay.o ${OBJECTDIR}/_ext/51196508/hal_lcd.o ${OBJECTDIR}/_ext/51196508/hal_non_vol.o ${OBJECTDIR}/_ext/51196508/hal_timer.o ${OBJECTDIR}/_ext/51196508/hal_touch.o ${OBJECTDIR}/_ext/1317985835/hal_delay.o ${OBJECTDIR}/_ext/1317985835/hal_lcd.o ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o ${OBJECTDIR}/_ext/1317985835/hal_timer.o ${OBJECTDIR}/_ext/1317985835/hal_touch.o ${OBJECTDIR}/_ext/1317985899/hal_delay.o ${OBJECTDIR}/_ext/1317985899/hal_lcd.o ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o ${OBJECTDIR}/_ext/1317985899/hal_timer.o ${OBJECTDIR}/_ext/1317985899/hal_touch.o ${OBJECTDIR}/_ext/1357345870/hal_delay.o ${OBJECTDIR}/_ext/1357345870/hal_lcd.o ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o ${OBJECTDIR}/_ext/1357345870/hal_timer.o ${OBJECTDIR}/_ext/1357345870/hal_touch.o ${OBJECTDIR}/_ext/902303450/hal_init.o ${OBJECTDIR}/_ext/1494913683/ui_arrow.o ${OBJECTDIR}/_ext/1494913683/ui_button.o ${OBJECTDIR}/_ext/1494913683/ui_check_box.o ${OBJECTDIR}/_ext/1494913683/ui_common.o ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o ${OBJECTDIR}/_ext/1494913683/ui_keypad.o ${OBJECTDIR}/_ext/1494913683/ui_label.o ${OBJECTDIR}/_ext/1494913683/ui_list_box.o ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o ${OBJECTDIR}/_ext/1494913683/ui_tabs.o ${OBJECTDIR}/_ext/1494913683/ui_text_box.o ${OBJECTDIR}/_ext/1494913683/ui_tree.o ${OBJECTDIR}/_ext/59636182/calibrate.o ${OBJECTDIR}/_ext/59636182/miniwin.o ${OBJECTDIR}/_ext/59636182/miniwin_debug.o ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o ${OBJECTDIR}/_ext/59636182/miniwin_settings.o ${OBJECTDIR}/_ext/59636182/miniwin_touch.o ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o ${OBJECTDIR}/_ext/692562174/main.o ${OBJECTDIR}/_ext/692562174/miniwin_user.o ${OBJECTDIR}/_ext/692562174/window_simple.o ${OBJECTDIR}/_ext/1445274692/app.o

# Source Files
SOURCEFILES=../src/config/default/peripheral/clk/plib_clk.c ../src/config/default/peripheral/coretimer/plib_coretimer.c ../src/config/default/peripheral/evic/plib_evic.c ../src/config/default/peripheral/gpio/plib_gpio.c ../src/config/default/peripheral/nvm/plib_nvm.c ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c ../src/config/default/peripheral/tmr/plib_tmr2.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/exceptions.c ../../../../../MiniWin/bitmaps/backspace_key.c ../../../../../MiniWin/bitmaps/close_icon.c ../../../../../MiniWin/bitmaps/close_icon_large.c ../../../../../MiniWin/bitmaps/file_icon_large.c ../../../../../MiniWin/bitmaps/file_icon_small.c ../../../../../MiniWin/bitmaps/folder_close_icon_large.c ../../../../../MiniWin/bitmaps/folder_close_icon_small.c ../../../../../MiniWin/bitmaps/folder_icon_large.c ../../../../../MiniWin/bitmaps/folder_icon_small.c ../../../../../MiniWin/bitmaps/folder_open_icon_large.c ../../../../../MiniWin/bitmaps/folder_open_icon_small.c ../../../../../MiniWin/bitmaps/let_key.c ../../../../../MiniWin/bitmaps/maximise_icon.c ../../../../../MiniWin/bitmaps/maximise_icon_large.c ../../../../../MiniWin/bitmaps/minimise_icon.c ../../../../../MiniWin/bitmaps/minimise_icon_large.c ../../../../../MiniWin/bitmaps/num_key.c ../../../../../MiniWin/bitmaps/resize_icon.c ../../../../../MiniWin/bitmaps/resize_icon_large.c ../../../../../MiniWin/bitmaps/shift_key.c ../../../../../MiniWin/bitmaps/sym_key.c ../../../../../MiniWin/bitmaps/tick.c ../../../../../MiniWin/bitmaps/tick_large.c ../../../../../MiniWin/dialogs/dialog_colour_chooser.c ../../../../../MiniWin/dialogs/dialog_date_chooser.c ../../../../../MiniWin/dialogs/dialog_file_chooser.c ../../../../../MiniWin/dialogs/dialog_number_entry.c ../../../../../MiniWin/dialogs/dialog_one_button.c ../../../../../MiniWin/dialogs/dialog_text_entry.c ../../../../../MiniWin/dialogs/dialog_time_chooser.c ../../../../../MiniWin/dialogs/dialog_two_button.c ../../../../../MiniWin/gl/fonts/bitmapped/font12.c ../../../../../MiniWin/gl/fonts/bitmapped/font16.c ../../../../../MiniWin/gl/fonts/bitmapped/font20.c ../../../../../MiniWin/gl/fonts/bitmapped/font24.c ../../../../../MiniWin/gl/fonts/bitmapped/font9.c ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c ../../../../../MiniWin/gl/gl.c ../../../../../MiniWin/hal/esp32-idf/hal_delay.c ../../../../../MiniWin/hal/esp32-idf/hal_lcd.c ../../../../../MiniWin/hal/esp32-idf/hal_non_vol.c ../../../../../MiniWin/hal/esp32-idf/hal_timer.c ../../../../../MiniWin/hal/esp32-idf/hal_touch.c ../../../../../MiniWin/hal/linux/hal_delay.c ../../../../../MiniWin/hal/linux/hal_lcd.c ../../../../../MiniWin/hal/linux/hal_non_vol.c ../../../../../MiniWin/hal/linux/hal_timer.c ../../../../../MiniWin/hal/linux/hal_touch.c ../../../../../MiniWin/hal/lpc54628/hal_delay.c ../../../../../MiniWin/hal/lpc54628/hal_lcd.c ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c ../../../../../MiniWin/hal/lpc54628/hal_timer.c ../../../../../MiniWin/hal/lpc54628/hal_touch.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c ../../../../../MiniWin/hal/rx65n/hal_delay.c ../../../../../MiniWin/hal/rx65n/hal_lcd.c ../../../../../MiniWin/hal/rx65n/hal_non_vol.c ../../../../../MiniWin/hal/rx65n/hal_timer.c ../../../../../MiniWin/hal/rx65n/hal_touch.c ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c ../../../../../MiniWin/hal/stm32f407/hal_delay.c ../../../../../MiniWin/hal/stm32f407/hal_lcd.c ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c ../../../../../MiniWin/hal/stm32f407/hal_timer.c ../../../../../MiniWin/hal/stm32f407/hal_touch.c ../../../../../MiniWin/hal/stm32f429/hal_delay.c ../../../../../MiniWin/hal/stm32f429/hal_lcd.c ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c ../../../../../MiniWin/hal/stm32f429/hal_timer.c ../../../../../MiniWin/hal/stm32f429/hal_touch.c ../../../../../MiniWin/hal/windows/hal_delay.c ../../../../../MiniWin/hal/windows/hal_lcd.c ../../../../../MiniWin/hal/windows/hal_non_vol.c ../../../../../MiniWin/hal/windows/hal_timer.c ../../../../../MiniWin/hal/windows/hal_touch.c ../../../../../MiniWin/hal/hal_init.c ../../../../../MiniWin/ui/ui_arrow.c ../../../../../MiniWin/ui/ui_button.c ../../../../../MiniWin/ui/ui_check_box.c ../../../../../MiniWin/ui/ui_common.c ../../../../../MiniWin/ui/ui_keyboard.c ../../../../../MiniWin/ui/ui_keypad.c ../../../../../MiniWin/ui/ui_label.c ../../../../../MiniWin/ui/ui_list_box.c ../../../../../MiniWin/ui/ui_progress_bar.c ../../../../../MiniWin/ui/ui_radio_button.c ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c ../../../../../MiniWin/ui/ui_scroll_bar_vert.c ../../../../../MiniWin/ui/ui_tabs.c ../../../../../MiniWin/ui/ui_text_box.c ../../../../../MiniWin/ui/ui_tree.c ../../../../../MiniWin/calibrate.c ../../../../../MiniWin/miniwin.c ../../../../../MiniWin/miniwin_debug.c ../../../../../MiniWin/miniwin_message_queue.c ../../../../../MiniWin/miniwin_settings.c ../../../../../MiniWin/miniwin_touch.c ../../../../../MiniWin/miniwin_tree_container.c ../../../../../MiniWin/miniwin_utilities.c ../../../../../MiniWinSimple_Common/main.c ../../../../../MiniWinSimple_Common/miniwin_user.c ../../../../../MiniWinSimple_Common/window_simple.c ../../src/app.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MiniWinSimple.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX470F512H
MP_LINKER_FILE_OPTION=,--script="..\src\config\default\p32MX470F512H.ld"
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
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/5d31b8473bd3affb2411bbff4d612ce5ed70362b.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1249264884/plib_coretimer.o: ../src/config/default/peripheral/coretimer/plib_coretimer.c  .generated_files/33ec37b7b22dd0347dd73842bb2b1ff7ac5f0746.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1249264884" 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ../src/config/default/peripheral/coretimer/plib_coretimer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/7d5889850e16bb4e33ac43272ae69adfc01524d8.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/b5286695f3d065a471d099408034a5b0768a2723.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60176403/plib_nvm.o: ../src/config/default/peripheral/nvm/plib_nvm.c  .generated_files/33c4f4abd127aedf0d9dcfc5d7548b344f8d014a.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60176403" 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ../src/config/default/peripheral/nvm/plib_nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/298189674/plib_spi2_master.o: ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c  .generated_files/7ff3d1023608adcf8a7286f43ba99b3e7aea3b29.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/298189674" 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d" -o ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60181895/plib_tmr2.o: ../src/config/default/peripheral/tmr/plib_tmr2.c  .generated_files/1baeaf17dbb0d74c928b5fa2322aea012539cd6.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ../src/config/default/peripheral/tmr/plib_tmr2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/c919508f224710559676c9d937bbd74e98dd9c88.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/55636b563898ef60781027f42be3aae5842bf003.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/2b5af9cf06bd37a3408fc8055769cc67abfc3c8f.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/925cdecea80fe2188aafdae3f895b2dfcda9e6c4.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/backspace_key.o: ../../../../../MiniWin/bitmaps/backspace_key.c  .generated_files/6660279263f0dbe245488b6c7278360395399d42.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/backspace_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/backspace_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/backspace_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/backspace_key.o ../../../../../MiniWin/bitmaps/backspace_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/close_icon.o: ../../../../../MiniWin/bitmaps/close_icon.c  .generated_files/48bc1ca1095ca80b70a2d2494fb64217f986e43b.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/close_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/close_icon.o ../../../../../MiniWin/bitmaps/close_icon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/close_icon_large.o: ../../../../../MiniWin/bitmaps/close_icon_large.c  .generated_files/ca8514a80f887358496dfc16b06fc102753fe02.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/close_icon_large.o ../../../../../MiniWin/bitmaps/close_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/file_icon_large.o: ../../../../../MiniWin/bitmaps/file_icon_large.c  .generated_files/13d10ff917beb4a2639dd89be0ff65e409a39247.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/file_icon_large.o ../../../../../MiniWin/bitmaps/file_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/file_icon_small.o: ../../../../../MiniWin/bitmaps/file_icon_small.c  .generated_files/b27a2b8ea2fb22c5e87eb00f4f5dce493f97167a.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/file_icon_small.o ../../../../../MiniWin/bitmaps/file_icon_small.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o: ../../../../../MiniWin/bitmaps/folder_close_icon_large.c  .generated_files/b7786f41e87fb9e89994372a7400b6025311317d.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o ../../../../../MiniWin/bitmaps/folder_close_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o: ../../../../../MiniWin/bitmaps/folder_close_icon_small.c  .generated_files/aafe9962692bd2ebccbede4c3703216e71a41e5f.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o ../../../../../MiniWin/bitmaps/folder_close_icon_small.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_icon_large.o: ../../../../../MiniWin/bitmaps/folder_icon_large.c  .generated_files/26c68cad6cb5f585e07683274abc995fdfdd3605.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o ../../../../../MiniWin/bitmaps/folder_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_icon_small.o: ../../../../../MiniWin/bitmaps/folder_icon_small.c  .generated_files/7cfcc2b61946dae1b58de2b84199bbb251b0d912.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o ../../../../../MiniWin/bitmaps/folder_icon_small.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o: ../../../../../MiniWin/bitmaps/folder_open_icon_large.c  .generated_files/83153700c837392b1175dee2e7db6d42238c68f0.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o ../../../../../MiniWin/bitmaps/folder_open_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o: ../../../../../MiniWin/bitmaps/folder_open_icon_small.c  .generated_files/78ad9cc79e54cdc0667899442f612fe591a95553.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o ../../../../../MiniWin/bitmaps/folder_open_icon_small.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/let_key.o: ../../../../../MiniWin/bitmaps/let_key.c  .generated_files/770fccdb65a852d3ce91afd57a3dffe1a7c5d788.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/let_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/let_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/let_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/let_key.o ../../../../../MiniWin/bitmaps/let_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/maximise_icon.o: ../../../../../MiniWin/bitmaps/maximise_icon.c  .generated_files/edba7091905af3ef1cb7ed900719a0aa655600d1.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/maximise_icon.o ../../../../../MiniWin/bitmaps/maximise_icon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o: ../../../../../MiniWin/bitmaps/maximise_icon_large.c  .generated_files/efc47adbdaa2f217165059ccc3361914d4c2eb0f.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o ../../../../../MiniWin/bitmaps/maximise_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/minimise_icon.o: ../../../../../MiniWin/bitmaps/minimise_icon.c  .generated_files/8b2ee078a2bf5502a4bc9bae928a84ff9849a40.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/minimise_icon.o ../../../../../MiniWin/bitmaps/minimise_icon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o: ../../../../../MiniWin/bitmaps/minimise_icon_large.c  .generated_files/8dd14b4b2987dd3bccdb68590dafc59d10b48e1.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o ../../../../../MiniWin/bitmaps/minimise_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/num_key.o: ../../../../../MiniWin/bitmaps/num_key.c  .generated_files/475c99c51b240576a746b867b85ed81aa58d8619.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/num_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/num_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/num_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/num_key.o ../../../../../MiniWin/bitmaps/num_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/resize_icon.o: ../../../../../MiniWin/bitmaps/resize_icon.c  .generated_files/c3be0f542417ed9076296c0ab143f2a25a88f72d.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/resize_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/resize_icon.o ../../../../../MiniWin/bitmaps/resize_icon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/resize_icon_large.o: ../../../../../MiniWin/bitmaps/resize_icon_large.c  .generated_files/84730435fa5f17b1570aaa593fa8a1570f2c8e95.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o ../../../../../MiniWin/bitmaps/resize_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/shift_key.o: ../../../../../MiniWin/bitmaps/shift_key.c  .generated_files/bc49fb51c744a8a564559e40c46142aaaa3256a9.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/shift_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/shift_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/shift_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/shift_key.o ../../../../../MiniWin/bitmaps/shift_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/sym_key.o: ../../../../../MiniWin/bitmaps/sym_key.c  .generated_files/e1c95dad1b78e223017cf311c6fbbe539b9dd3c4.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/sym_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/sym_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/sym_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/sym_key.o ../../../../../MiniWin/bitmaps/sym_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/tick.o: ../../../../../MiniWin/bitmaps/tick.c  .generated_files/df2e5f7351c71b8b4f58ede7e46b5073e105ed3f.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/tick.o.d" -o ${OBJECTDIR}/_ext/1275709973/tick.o ../../../../../MiniWin/bitmaps/tick.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/tick_large.o: ../../../../../MiniWin/bitmaps/tick_large.c  .generated_files/bc88cfe08734a8d254194b90bef5c7e96b4e5f31.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/tick_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/tick_large.o ../../../../../MiniWin/bitmaps/tick_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o: ../../../../../MiniWin/dialogs/dialog_colour_chooser.c  .generated_files/514ea136799dfd5cd89419417f61466737608382.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o ../../../../../MiniWin/dialogs/dialog_colour_chooser.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o: ../../../../../MiniWin/dialogs/dialog_date_chooser.c  .generated_files/560ddb6a7dde2df97f89e481d3685c68cc7ba5e.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o ../../../../../MiniWin/dialogs/dialog_date_chooser.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o: ../../../../../MiniWin/dialogs/dialog_file_chooser.c  .generated_files/81ce6c38d3d62a59839a9bc52ff5840f5fc6b2a7.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o ../../../../../MiniWin/dialogs/dialog_file_chooser.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_number_entry.o: ../../../../../MiniWin/dialogs/dialog_number_entry.c  .generated_files/2795994788eabe6d8aaac74486eb8a2fe40e393.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o ../../../../../MiniWin/dialogs/dialog_number_entry.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_one_button.o: ../../../../../MiniWin/dialogs/dialog_one_button.c  .generated_files/ff45847ba07c5dccddc96b2982d82907e999c09.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_one_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_one_button.o ../../../../../MiniWin/dialogs/dialog_one_button.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_text_entry.o: ../../../../../MiniWin/dialogs/dialog_text_entry.c  .generated_files/99c4c12b0fd3d5f483e6c756f758581c7b0e099a.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o ../../../../../MiniWin/dialogs/dialog_text_entry.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o: ../../../../../MiniWin/dialogs/dialog_time_chooser.c  .generated_files/15d30ad5a61866e19b420251c0ee015dad15658.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o ../../../../../MiniWin/dialogs/dialog_time_chooser.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_two_button.o: ../../../../../MiniWin/dialogs/dialog_two_button.c  .generated_files/ebc768c46f670dbc9013e2541b100f5e0d5f977a.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_two_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_two_button.o ../../../../../MiniWin/dialogs/dialog_two_button.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font12.o: ../../../../../MiniWin/gl/fonts/bitmapped/font12.c  .generated_files/8d949824b71b1dde1f64ff49f8ab10aaae3405c4.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font12.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font12.o.d" -o ${OBJECTDIR}/_ext/194049764/font12.o ../../../../../MiniWin/gl/fonts/bitmapped/font12.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font16.o: ../../../../../MiniWin/gl/fonts/bitmapped/font16.c  .generated_files/c98246f40937ad95afe27824e5a2d44c95f47c1b.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font16.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font16.o.d" -o ${OBJECTDIR}/_ext/194049764/font16.o ../../../../../MiniWin/gl/fonts/bitmapped/font16.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font20.o: ../../../../../MiniWin/gl/fonts/bitmapped/font20.c  .generated_files/9addee1d1aff71d62081263bd140569acb624b42.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font20.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font20.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font20.o.d" -o ${OBJECTDIR}/_ext/194049764/font20.o ../../../../../MiniWin/gl/fonts/bitmapped/font20.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font24.o: ../../../../../MiniWin/gl/fonts/bitmapped/font24.c  .generated_files/ab0ea400782e92c4b63364ac5532356bf2974fee.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font24.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font24.o.d" -o ${OBJECTDIR}/_ext/194049764/font24.o ../../../../../MiniWin/gl/fonts/bitmapped/font24.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font9.o: ../../../../../MiniWin/gl/fonts/bitmapped/font9.c  .generated_files/72cb6ab54bbc4c8e0fbe6c70266346254cfeed79.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font9.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font9.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font9.o.d" -o ${OBJECTDIR}/_ext/194049764/font9.o ../../../../../MiniWin/gl/fonts/bitmapped/font9.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/gl_title_font.o: ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c  .generated_files/5948d6bcfcb8a42252fe30b17a9f2da974463375.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/gl_title_font.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/gl_title_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/gl_title_font.o.d" -o ${OBJECTDIR}/_ext/194049764/gl_title_font.o ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_bwfont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c  .generated_files/bb34285051bb7625b7aea44db42ca55c6c02434a.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_encoding.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c  .generated_files/95799bc1d3853eb709cb65705974ba0d8bdc9510.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_encoding.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_encoding.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_font.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c  .generated_files/de85da66fc8153ceb082d63eccd26e03efea911.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_font.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_font.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_font.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_justify.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c  .generated_files/5a09163632cf05ac8b6c75c282e30453eaa7ca67.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_justify.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_justify.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_justify.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_justify.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_kerning.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c  .generated_files/99e29b7776f8fbf81743d76605df6563cc473bdd.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_kerning.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_kerning.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_rlefont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c  .generated_files/75a0a37eaeabd92a82af0c670b74ec5f46531ca3.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c  .generated_files/3ca768ac819a1556af25540299124d155e031adc.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c  .generated_files/d111d421847829e80ac955856b81898fdea6193e.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o: ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c  .generated_files/ce3e0689471e08b6fece9a976c420f46f7ec06ee.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d" -o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o: ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c  .generated_files/862ccfa9debb2bee5daa28470ff71af3b4f1e4e5.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d" -o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o: ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c  .generated_files/80ec564f321705bb11d811bd150561e5eacdc899.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d" -o ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494914114/gl.o: ../../../../../MiniWin/gl/gl.c  .generated_files/4805d42ea927f045d03c0700397807d5f2b7e0ee.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494914114" 
	@${RM} ${OBJECTDIR}/_ext/1494914114/gl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494914114/gl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494914114/gl.o.d" -o ${OBJECTDIR}/_ext/1494914114/gl.o ../../../../../MiniWin/gl/gl.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1770599754/hal_delay.o: ../../../../../MiniWin/hal/esp32-idf/hal_delay.c  .generated_files/d82b9e33ea28ef8352fd737c1406d83c228f9368.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1770599754" 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1770599754/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1770599754/hal_delay.o ../../../../../MiniWin/hal/esp32-idf/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1770599754/hal_lcd.o: ../../../../../MiniWin/hal/esp32-idf/hal_lcd.c  .generated_files/c2be8056d24bfdad0b9f9c590c49db6de2c08ff7.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1770599754" 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1770599754/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1770599754/hal_lcd.o ../../../../../MiniWin/hal/esp32-idf/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1770599754/hal_non_vol.o: ../../../../../MiniWin/hal/esp32-idf/hal_non_vol.c  .generated_files/d82bc5e5b0333000101651880849485da48d1eff.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1770599754" 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1770599754/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1770599754/hal_non_vol.o ../../../../../MiniWin/hal/esp32-idf/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1770599754/hal_timer.o: ../../../../../MiniWin/hal/esp32-idf/hal_timer.c  .generated_files/f68625b3af4d983da63ad252ecd4971f9e130b85.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1770599754" 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1770599754/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1770599754/hal_timer.o ../../../../../MiniWin/hal/esp32-idf/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1770599754/hal_touch.o: ../../../../../MiniWin/hal/esp32-idf/hal_touch.c  .generated_files/37ecc733df0c7a22b3333b95e35b046306a5f4c9.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1770599754" 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1770599754/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1770599754/hal_touch.o ../../../../../MiniWin/hal/esp32-idf/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_delay.o: ../../../../../MiniWin/hal/linux/hal_delay.c  .generated_files/490b0d624717e241cbcbe5efdd530671d43ce4ae.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_delay.o ../../../../../MiniWin/hal/linux/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_lcd.o: ../../../../../MiniWin/hal/linux/hal_lcd.c  .generated_files/60d40c8b3b10d789333a953055e31e3650009ecc.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_lcd.o ../../../../../MiniWin/hal/linux/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_non_vol.o: ../../../../../MiniWin/hal/linux/hal_non_vol.c  .generated_files/e2658fc8d520aab379973676f9ee35828518a507.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o ../../../../../MiniWin/hal/linux/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_timer.o: ../../../../../MiniWin/hal/linux/hal_timer.c  .generated_files/de47f28ff9f1631c99c41d98d029b4feceb788d6.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_timer.o ../../../../../MiniWin/hal/linux/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_touch.o: ../../../../../MiniWin/hal/linux/hal_touch.c  .generated_files/a45e0aa540e80ba2a88df6156c18281503f51ff4.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_touch.o ../../../../../MiniWin/hal/linux/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_delay.o: ../../../../../MiniWin/hal/lpc54628/hal_delay.c  .generated_files/53a6dfae24a1a24ad0eb05f22e1e7e2e7f9b78d8.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_delay.o ../../../../../MiniWin/hal/lpc54628/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_lcd.o: ../../../../../MiniWin/hal/lpc54628/hal_lcd.c  .generated_files/5074d3205c16df632b0de6370d85e9eb88c74675.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_lcd.o ../../../../../MiniWin/hal/lpc54628/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_non_vol.o: ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c  .generated_files/fe5cd22d327a5bc22d27d10dad49e641e897794f.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_timer.o: ../../../../../MiniWin/hal/lpc54628/hal_timer.c  .generated_files/64e066731f49316f1adff2bac60fceddf1b37245.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_timer.o ../../../../../MiniWin/hal/lpc54628/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_touch.o: ../../../../../MiniWin/hal/lpc54628/hal_touch.c  .generated_files/f9a303e6abd92084834329379ca89749cf17292.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_touch.o ../../../../../MiniWin/hal/lpc54628/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_delay.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c  .generated_files/7b5fcaa308295c7e9733440efadc73cf6616f62b.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_delay.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_delay.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_lcd.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c  .generated_files/b5c6ccf1c2b62d1567b852b7d7c2c7394bff839c.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_lcd.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_non_vol.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c  .generated_files/a5895d11fac8bf1c8a22c7294233775bc8da11d9.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_non_vol.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_timer.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c  .generated_files/30c5761e5b9c84a7fa1ca3ae0284dd5496cdaa22.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_timer.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_timer.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_touch.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c  .generated_files/aaebbda40bf0c79dfac2f89b25aed631c859d7c5.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_touch.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_touch.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_delay.o: ../../../../../MiniWin/hal/rx65n/hal_delay.c  .generated_files/ced1b11ceba9f21fe8597afa99d0eb50dc1c2e66.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_delay.o ../../../../../MiniWin/hal/rx65n/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_lcd.o: ../../../../../MiniWin/hal/rx65n/hal_lcd.c  .generated_files/926d00b2109fe3ffe216a4189a424181c7e17635.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_lcd.o ../../../../../MiniWin/hal/rx65n/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_non_vol.o: ../../../../../MiniWin/hal/rx65n/hal_non_vol.c  .generated_files/53b3b6f2fa579d0ddd4234860436c4ada97b0543.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o ../../../../../MiniWin/hal/rx65n/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_timer.o: ../../../../../MiniWin/hal/rx65n/hal_timer.c  .generated_files/b677271de36f7a54c38d7bd734055583ca4bd200.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_timer.o ../../../../../MiniWin/hal/rx65n/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_touch.o: ../../../../../MiniWin/hal/rx65n/hal_touch.c  .generated_files/6182bf54a70e64f1c5923cc5d2539579a3703a8a.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_touch.o ../../../../../MiniWin/hal/rx65n/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_delay.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c  .generated_files/4e3df9ea28e80b570d5789c3791b974ea097f2d9.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_delay.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_delay.o ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_lcd.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c  .generated_files/384cbf485678d3d685d60caa6e2bf3d73479501f.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_lcd.o ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_non_vol.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c  .generated_files/1e6947edabb857cf44d177f39d391d048d67827c.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_non_vol.o ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_timer.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c  .generated_files/a2af2b5116c7233544aeee6b3a63ef5bbad1897c.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_timer.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_timer.o ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_touch.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c  .generated_files/9be864a30dd0ab89a0d6b2bc188b75ed80efde41.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_touch.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_touch.o ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_delay.o: ../../../../../MiniWin/hal/stm32f407/hal_delay.c  .generated_files/a154c321977256938e8963695f15b25c22c9e3cf.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_delay.o ../../../../../MiniWin/hal/stm32f407/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_lcd.o: ../../../../../MiniWin/hal/stm32f407/hal_lcd.c  .generated_files/86d9f04ec8dd2eae9eec73b0f47dba0ce63b8de9.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_lcd.o ../../../../../MiniWin/hal/stm32f407/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_non_vol.o: ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c  .generated_files/2a60fd4bd8b7b4ece09f541b664f45cff81ed13e.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_timer.o: ../../../../../MiniWin/hal/stm32f407/hal_timer.c  .generated_files/c6c177125485fefd2855473ebb9c83d38aa716c3.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_timer.o ../../../../../MiniWin/hal/stm32f407/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_touch.o: ../../../../../MiniWin/hal/stm32f407/hal_touch.c  .generated_files/841b0ec6f25e8638062b944b3662ba003f29eb03.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_touch.o ../../../../../MiniWin/hal/stm32f407/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_delay.o: ../../../../../MiniWin/hal/stm32f429/hal_delay.c  .generated_files/87514202467279a5f12eed4a62b821d36798a180.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_delay.o ../../../../../MiniWin/hal/stm32f429/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_lcd.o: ../../../../../MiniWin/hal/stm32f429/hal_lcd.c  .generated_files/a917c8931b7eec533891ed49b926a24e19805819.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_lcd.o ../../../../../MiniWin/hal/stm32f429/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_non_vol.o: ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c  .generated_files/dcacb10e2d72618bc95ef6522b2a307592b26e8b.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_timer.o: ../../../../../MiniWin/hal/stm32f429/hal_timer.c  .generated_files/97bded5d4530b3e52a853d9c29cf18b8105c9d12.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_timer.o ../../../../../MiniWin/hal/stm32f429/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_touch.o: ../../../../../MiniWin/hal/stm32f429/hal_touch.c  .generated_files/2513208b3579636c70ef227ef83b18a28315239c.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_touch.o ../../../../../MiniWin/hal/stm32f429/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_delay.o: ../../../../../MiniWin/hal/windows/hal_delay.c  .generated_files/d5aa5bbe3811682dde5678697baafb62f6233709.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_delay.o ../../../../../MiniWin/hal/windows/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_lcd.o: ../../../../../MiniWin/hal/windows/hal_lcd.c  .generated_files/91b3959c1a77f4a06e976877a32623789792dee5.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_lcd.o ../../../../../MiniWin/hal/windows/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_non_vol.o: ../../../../../MiniWin/hal/windows/hal_non_vol.c  .generated_files/58c7ec5964b724616251b821dd4fbae40efa1466.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o ../../../../../MiniWin/hal/windows/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_timer.o: ../../../../../MiniWin/hal/windows/hal_timer.c  .generated_files/ca02fdf5d3c7245964d1bdf41dd8691ad2cb8cb8.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_timer.o ../../../../../MiniWin/hal/windows/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_touch.o: ../../../../../MiniWin/hal/windows/hal_touch.c  .generated_files/a55e2ead4cd3e4782b449f87cd99260f3a7bf901.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_touch.o ../../../../../MiniWin/hal/windows/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/902303450/hal_init.o: ../../../../../MiniWin/hal/hal_init.c  .generated_files/1c18e1d52c4321f165a9137767c1f23c9429f616.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/902303450" 
	@${RM} ${OBJECTDIR}/_ext/902303450/hal_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/902303450/hal_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/902303450/hal_init.o.d" -o ${OBJECTDIR}/_ext/902303450/hal_init.o ../../../../../MiniWin/hal/hal_init.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_arrow.o: ../../../../../MiniWin/ui/ui_arrow.c  .generated_files/601f8ac7b172893c4fb48c357a484a82a17fdece.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_arrow.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_arrow.o ../../../../../MiniWin/ui/ui_arrow.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_button.o: ../../../../../MiniWin/ui/ui_button.c  .generated_files/4e841a87c07753e9da07de17f61457a5fd1ddefd.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_button.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_button.o ../../../../../MiniWin/ui/ui_button.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_check_box.o: ../../../../../MiniWin/ui/ui_check_box.c  .generated_files/779703ff131549aae8201cfead3783982f62c7c7.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_check_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_check_box.o ../../../../../MiniWin/ui/ui_check_box.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_common.o: ../../../../../MiniWin/ui/ui_common.c  .generated_files/76011087d1fedb1809901cee4fb43bda7a2c3e4a.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_common.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_common.o ../../../../../MiniWin/ui/ui_common.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_keyboard.o: ../../../../../MiniWin/ui/ui_keyboard.c  .generated_files/1f0b6c1e71f5dfa7c9b5f1972e9d4e79cad5bae0.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o ../../../../../MiniWin/ui/ui_keyboard.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_keypad.o: ../../../../../MiniWin/ui/ui_keypad.c  .generated_files/35e7083d053be42e3bb7a794c1a9e87195031588.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keypad.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_keypad.o ../../../../../MiniWin/ui/ui_keypad.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_label.o: ../../../../../MiniWin/ui/ui_label.c  .generated_files/3ca06e5915eb7d8d1b7f594137c50a0304adb3ab.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_label.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_label.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_label.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_label.o ../../../../../MiniWin/ui/ui_label.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_list_box.o: ../../../../../MiniWin/ui/ui_list_box.c  .generated_files/f594ea66e4b66e856f5120eb0121771bd5ae5e11.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_list_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_list_box.o ../../../../../MiniWin/ui/ui_list_box.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o: ../../../../../MiniWin/ui/ui_progress_bar.c  .generated_files/7b9b1ac6d978867b119591f8c6faa9513af6b547.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o ../../../../../MiniWin/ui/ui_progress_bar.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_radio_button.o: ../../../../../MiniWin/ui/ui_radio_button.c  .generated_files/152f8877a7904974bd073bc6ca382641cd10b8d4.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o ../../../../../MiniWin/ui/ui_radio_button.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o: ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c  .generated_files/547a7b16244ff4d6351ee56e76c07d43b70d70c.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o: ../../../../../MiniWin/ui/ui_scroll_bar_vert.c  .generated_files/84a598c5534df8bda9b8fa0dec2064ad79eb2726.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o ../../../../../MiniWin/ui/ui_scroll_bar_vert.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_tabs.o: ../../../../../MiniWin/ui/ui_tabs.c  .generated_files/c95eef1c9edc0de3ea5a121e5db9b0a622d6c9cc.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tabs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_tabs.o ../../../../../MiniWin/ui/ui_tabs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_text_box.o: ../../../../../MiniWin/ui/ui_text_box.c  .generated_files/ee788084a84fa620d0ce02c313419d0fa79c39e2.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_text_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_text_box.o ../../../../../MiniWin/ui/ui_text_box.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_tree.o: ../../../../../MiniWin/ui/ui_tree.c  .generated_files/27e359b48b454a41869fde1a2713ac4b025a7c56.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tree.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tree.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_tree.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_tree.o ../../../../../MiniWin/ui/ui_tree.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/calibrate.o: ../../../../../MiniWin/calibrate.c  .generated_files/c6812e37a39dcd7137fd9d378be4888664c13a42.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/calibrate.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/calibrate.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/calibrate.o.d" -o ${OBJECTDIR}/_ext/59636182/calibrate.o ../../../../../MiniWin/calibrate.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin.o: ../../../../../MiniWin/miniwin.c  .generated_files/d1de9affbcb762ff2737c86b03a790df67b2a8a4.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin.o ../../../../../MiniWin/miniwin.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_debug.o: ../../../../../MiniWin/miniwin_debug.c  .generated_files/519960ebc34339d68cd1d2be3e52598a8764d9a2.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_debug.o ../../../../../MiniWin/miniwin_debug.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o: ../../../../../MiniWin/miniwin_message_queue.c  .generated_files/c99cf8dbffbe6f5ef04f3c461028b39687f24c4a.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o ../../../../../MiniWin/miniwin_message_queue.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_settings.o: ../../../../../MiniWin/miniwin_settings.c  .generated_files/7510e567de0bb5f0e3cf2089fdab2c50f7bbc90.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_settings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_settings.o ../../../../../MiniWin/miniwin_settings.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_touch.o: ../../../../../MiniWin/miniwin_touch.c  .generated_files/f9cbaccd3dd6e8b18da6dcd4b600e5233d14cece.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_touch.o ../../../../../MiniWin/miniwin_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o: ../../../../../MiniWin/miniwin_tree_container.c  .generated_files/b268235b2b7f7b151a9f62313adde20014e0d533.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o ../../../../../MiniWin/miniwin_tree_container.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_utilities.o: ../../../../../MiniWin/miniwin_utilities.c  .generated_files/bf4bd37faf270a02c9627262ea951964a79a248d.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o ../../../../../MiniWin/miniwin_utilities.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692562174/main.o: ../../../../../MiniWinSimple_Common/main.c  .generated_files/cd5e50d5741d7a5749587844953d8fd2cfd3e459.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/692562174" 
	@${RM} ${OBJECTDIR}/_ext/692562174/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/692562174/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692562174/main.o.d" -o ${OBJECTDIR}/_ext/692562174/main.o ../../../../../MiniWinSimple_Common/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692562174/miniwin_user.o: ../../../../../MiniWinSimple_Common/miniwin_user.c  .generated_files/2ea924a2a094130949957da8de7578a3c76e3085.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/692562174" 
	@${RM} ${OBJECTDIR}/_ext/692562174/miniwin_user.o.d 
	@${RM} ${OBJECTDIR}/_ext/692562174/miniwin_user.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692562174/miniwin_user.o.d" -o ${OBJECTDIR}/_ext/692562174/miniwin_user.o ../../../../../MiniWinSimple_Common/miniwin_user.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692562174/window_simple.o: ../../../../../MiniWinSimple_Common/window_simple.c  .generated_files/38384ca64bef18f879c3009dee93f80b235169b0.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/692562174" 
	@${RM} ${OBJECTDIR}/_ext/692562174/window_simple.o.d 
	@${RM} ${OBJECTDIR}/_ext/692562174/window_simple.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692562174/window_simple.o.d" -o ${OBJECTDIR}/_ext/692562174/window_simple.o ../../../../../MiniWinSimple_Common/window_simple.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1445274692/app.o: ../../src/app.c  .generated_files/f7be80451438b12bd6884e67e96afc680816d477.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1445274692" 
	@${RM} ${OBJECTDIR}/_ext/1445274692/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1445274692/app.o.d" -o ${OBJECTDIR}/_ext/1445274692/app.o ../../src/app.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/60165520/plib_clk.o: ../src/config/default/peripheral/clk/plib_clk.c  .generated_files/9713b2b3000af003e5c20de324c13c48e7b6b874.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60165520" 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/60165520/plib_clk.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60165520/plib_clk.o.d" -o ${OBJECTDIR}/_ext/60165520/plib_clk.o ../src/config/default/peripheral/clk/plib_clk.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1249264884/plib_coretimer.o: ../src/config/default/peripheral/coretimer/plib_coretimer.c  .generated_files/44ede2b4882c529e4ee9ceadf865fe7b2e91bce5.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1249264884" 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1249264884/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1249264884/plib_coretimer.o ../src/config/default/peripheral/coretimer/plib_coretimer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865200349/plib_evic.o: ../src/config/default/peripheral/evic/plib_evic.c  .generated_files/d4e5fc6b9b89c84b7bd737383d5bd2ecb8d99fe4.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865200349" 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865200349/plib_evic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865200349/plib_evic.o.d" -o ${OBJECTDIR}/_ext/1865200349/plib_evic.o ../src/config/default/peripheral/evic/plib_evic.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1865254177/plib_gpio.o: ../src/config/default/peripheral/gpio/plib_gpio.c  .generated_files/bb58b16d4614340cb796b684372aed14b8c03f84.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1865254177" 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865254177/plib_gpio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865254177/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/1865254177/plib_gpio.o ../src/config/default/peripheral/gpio/plib_gpio.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60176403/plib_nvm.o: ../src/config/default/peripheral/nvm/plib_nvm.c  .generated_files/fffb8ffa4f379c787569fc8bc31cb777812e9623.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60176403" 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/60176403/plib_nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60176403/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/60176403/plib_nvm.o ../src/config/default/peripheral/nvm/plib_nvm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/298189674/plib_spi2_master.o: ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c  .generated_files/583688de3661cc06636188dca3a1e259946f8b51.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/298189674" 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d 
	@${RM} ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/298189674/plib_spi2_master.o.d" -o ${OBJECTDIR}/_ext/298189674/plib_spi2_master.o ../src/config/default/peripheral/spi/spi_master/plib_spi2_master.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/60181895/plib_tmr2.o: ../src/config/default/peripheral/tmr/plib_tmr2.c  .generated_files/40809d53ffa3abca44c33f45e33cdea8a7f65bf.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/60181895" 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181895/plib_tmr2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181895/plib_tmr2.o.d" -o ${OBJECTDIR}/_ext/60181895/plib_tmr2.o ../src/config/default/peripheral/tmr/plib_tmr2.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/e6c209cca54f3bb4bcaa3d144ac39e48c9523768.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/7379e33fa5edb3330debf6e9ddb258e53c33f3f1.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/31fe2b2fac7c2e064f744c18747c96980cb9bef2.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/32984ea801aede0972994652cd075b1775f14e53.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/backspace_key.o: ../../../../../MiniWin/bitmaps/backspace_key.c  .generated_files/fc3d9abf2061eccce40d08552f510600079d3adf.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/backspace_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/backspace_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/backspace_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/backspace_key.o ../../../../../MiniWin/bitmaps/backspace_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/close_icon.o: ../../../../../MiniWin/bitmaps/close_icon.c  .generated_files/9d66ce570333123f88a2e4f5230f3d022d99638.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/close_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/close_icon.o ../../../../../MiniWin/bitmaps/close_icon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/close_icon_large.o: ../../../../../MiniWin/bitmaps/close_icon_large.c  .generated_files/c19ce552e6a87508435d0cfbf78a7e9940d1c044.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/close_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/close_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/close_icon_large.o ../../../../../MiniWin/bitmaps/close_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/file_icon_large.o: ../../../../../MiniWin/bitmaps/file_icon_large.c  .generated_files/779e484e79333178a67f39e2da4deed262d4e6cf.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/file_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/file_icon_large.o ../../../../../MiniWin/bitmaps/file_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/file_icon_small.o: ../../../../../MiniWin/bitmaps/file_icon_small.c  .generated_files/f05d3d3f84e12abc19b13efe8b47ab4f4dad18c6.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/file_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/file_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/file_icon_small.o ../../../../../MiniWin/bitmaps/file_icon_small.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o: ../../../../../MiniWin/bitmaps/folder_close_icon_large.c  .generated_files/9802eaa3c50d100124889a5537e4e9877fc16336.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_large.o ../../../../../MiniWin/bitmaps/folder_close_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o: ../../../../../MiniWin/bitmaps/folder_close_icon_small.c  .generated_files/91e47549e09643f88f3f13955d5beeaf20693c19.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_close_icon_small.o ../../../../../MiniWin/bitmaps/folder_close_icon_small.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_icon_large.o: ../../../../../MiniWin/bitmaps/folder_icon_large.c  .generated_files/2d8f8a7a4589043522078cbc7c47a05cc2f7e829.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_icon_large.o ../../../../../MiniWin/bitmaps/folder_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_icon_small.o: ../../../../../MiniWin/bitmaps/folder_icon_small.c  .generated_files/b57c316890699308778b8695aadd4e8331cad1f0.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_icon_small.o ../../../../../MiniWin/bitmaps/folder_icon_small.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o: ../../../../../MiniWin/bitmaps/folder_open_icon_large.c  .generated_files/87e88a2cb21733f46e6228a27ef7980ff29a3547.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_large.o ../../../../../MiniWin/bitmaps/folder_open_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o: ../../../../../MiniWin/bitmaps/folder_open_icon_small.c  .generated_files/a52390e54beb0ae93a5d4b295e8a42b61f1e5243.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o.d" -o ${OBJECTDIR}/_ext/1275709973/folder_open_icon_small.o ../../../../../MiniWin/bitmaps/folder_open_icon_small.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/let_key.o: ../../../../../MiniWin/bitmaps/let_key.c  .generated_files/9f58b53b6313dc9c0eaa097f946c820b1b1cbc97.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/let_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/let_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/let_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/let_key.o ../../../../../MiniWin/bitmaps/let_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/maximise_icon.o: ../../../../../MiniWin/bitmaps/maximise_icon.c  .generated_files/f13c4dd7cb5bc4cf23afea4e807954dbcb8e7a30.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/maximise_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/maximise_icon.o ../../../../../MiniWin/bitmaps/maximise_icon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o: ../../../../../MiniWin/bitmaps/maximise_icon_large.c  .generated_files/672451524a63197113864046b8d53c5077015024.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/maximise_icon_large.o ../../../../../MiniWin/bitmaps/maximise_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/minimise_icon.o: ../../../../../MiniWin/bitmaps/minimise_icon.c  .generated_files/559066be8a71dee87c868ef034fe36ffe3285b9c.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/minimise_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/minimise_icon.o ../../../../../MiniWin/bitmaps/minimise_icon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o: ../../../../../MiniWin/bitmaps/minimise_icon_large.c  .generated_files/b25150125ad2b31a185f732123e41643b5258c94.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/minimise_icon_large.o ../../../../../MiniWin/bitmaps/minimise_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/num_key.o: ../../../../../MiniWin/bitmaps/num_key.c  .generated_files/1940bfb2a21e3784bfadf0682310dc897748166f.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/num_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/num_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/num_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/num_key.o ../../../../../MiniWin/bitmaps/num_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/resize_icon.o: ../../../../../MiniWin/bitmaps/resize_icon.c  .generated_files/870442c81eb800b3f847314bbace0ccde6e8eb2a.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/resize_icon.o.d" -o ${OBJECTDIR}/_ext/1275709973/resize_icon.o ../../../../../MiniWin/bitmaps/resize_icon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/resize_icon_large.o: ../../../../../MiniWin/bitmaps/resize_icon_large.c  .generated_files/c84d7153562ab8ed4f1b71cd04911b98bd1a8f11.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/resize_icon_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/resize_icon_large.o ../../../../../MiniWin/bitmaps/resize_icon_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/shift_key.o: ../../../../../MiniWin/bitmaps/shift_key.c  .generated_files/269e763a26be9a089274bbaa4d682bb3b9e43d48.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/shift_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/shift_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/shift_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/shift_key.o ../../../../../MiniWin/bitmaps/shift_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/sym_key.o: ../../../../../MiniWin/bitmaps/sym_key.c  .generated_files/832b403f743d32731ae986699ccab11e82d3ef3c.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/sym_key.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/sym_key.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/sym_key.o.d" -o ${OBJECTDIR}/_ext/1275709973/sym_key.o ../../../../../MiniWin/bitmaps/sym_key.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/tick.o: ../../../../../MiniWin/bitmaps/tick.c  .generated_files/5c96f3213673c6c6eb9fa6839c420d096783c48a.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/tick.o.d" -o ${OBJECTDIR}/_ext/1275709973/tick.o ../../../../../MiniWin/bitmaps/tick.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1275709973/tick_large.o: ../../../../../MiniWin/bitmaps/tick_large.c  .generated_files/d420f845c8b503babb4cad27c5bf1d27ab3d8fb2.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1275709973" 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick_large.o.d 
	@${RM} ${OBJECTDIR}/_ext/1275709973/tick_large.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1275709973/tick_large.o.d" -o ${OBJECTDIR}/_ext/1275709973/tick_large.o ../../../../../MiniWin/bitmaps/tick_large.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o: ../../../../../MiniWin/dialogs/dialog_colour_chooser.c  .generated_files/b18c2abb391855d2fe27882c4b6a5350b446b91c.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_colour_chooser.o ../../../../../MiniWin/dialogs/dialog_colour_chooser.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o: ../../../../../MiniWin/dialogs/dialog_date_chooser.c  .generated_files/d5ea0fa883a79e1f6bb34fe5c1f12f7ef4711aef.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_date_chooser.o ../../../../../MiniWin/dialogs/dialog_date_chooser.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o: ../../../../../MiniWin/dialogs/dialog_file_chooser.c  .generated_files/8380ed4d9b7fd55abb6f27c27a9ab2e5c8fbcdcf.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_file_chooser.o ../../../../../MiniWin/dialogs/dialog_file_chooser.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_number_entry.o: ../../../../../MiniWin/dialogs/dialog_number_entry.c  .generated_files/a69f117c66424489590df6a097230ddfd3f7b30f.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_number_entry.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_number_entry.o ../../../../../MiniWin/dialogs/dialog_number_entry.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_one_button.o: ../../../../../MiniWin/dialogs/dialog_one_button.c  .generated_files/3cae60a65181b7a8dffc43fdd47ef1667a03b1db.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_one_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_one_button.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_one_button.o ../../../../../MiniWin/dialogs/dialog_one_button.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_text_entry.o: ../../../../../MiniWin/dialogs/dialog_text_entry.c  .generated_files/6d525666e7e40fe93ee984e6a1e75080b01134ed.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_text_entry.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_text_entry.o ../../../../../MiniWin/dialogs/dialog_text_entry.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o: ../../../../../MiniWin/dialogs/dialog_time_chooser.c  .generated_files/8f268dcc59e7d29d756a02f9dc66ce944f1d59cf.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_time_chooser.o ../../../../../MiniWin/dialogs/dialog_time_chooser.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/481733874/dialog_two_button.o: ../../../../../MiniWin/dialogs/dialog_two_button.c  .generated_files/18c19db5ce4278fa66928c9ce70735bf6bb94426.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/481733874" 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/481733874/dialog_two_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/481733874/dialog_two_button.o.d" -o ${OBJECTDIR}/_ext/481733874/dialog_two_button.o ../../../../../MiniWin/dialogs/dialog_two_button.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font12.o: ../../../../../MiniWin/gl/fonts/bitmapped/font12.c  .generated_files/70809fa4fe2a72fef1eebc429c3f7a311ae8d1b1.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font12.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font12.o.d" -o ${OBJECTDIR}/_ext/194049764/font12.o ../../../../../MiniWin/gl/fonts/bitmapped/font12.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font16.o: ../../../../../MiniWin/gl/fonts/bitmapped/font16.c  .generated_files/695e96d6459c45cbc526145fa69fbecfe0d4b1dd.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font16.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font16.o.d" -o ${OBJECTDIR}/_ext/194049764/font16.o ../../../../../MiniWin/gl/fonts/bitmapped/font16.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font20.o: ../../../../../MiniWin/gl/fonts/bitmapped/font20.c  .generated_files/a642fd35319126d71f0375bcfe8f5eacef3fa270.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font20.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font20.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font20.o.d" -o ${OBJECTDIR}/_ext/194049764/font20.o ../../../../../MiniWin/gl/fonts/bitmapped/font20.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font24.o: ../../../../../MiniWin/gl/fonts/bitmapped/font24.c  .generated_files/5f0ea70295fe8d2b29427d06105bf7f933941114.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font24.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font24.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font24.o.d" -o ${OBJECTDIR}/_ext/194049764/font24.o ../../../../../MiniWin/gl/fonts/bitmapped/font24.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/font9.o: ../../../../../MiniWin/gl/fonts/bitmapped/font9.c  .generated_files/91e2e1764d7e90ed7ae8c3d777bef3ea206a0287.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/font9.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/font9.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/font9.o.d" -o ${OBJECTDIR}/_ext/194049764/font9.o ../../../../../MiniWin/gl/fonts/bitmapped/font9.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/194049764/gl_title_font.o: ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c  .generated_files/285d26f225e87d9c5ac6ee3224abc9fdd20efaa3.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/194049764" 
	@${RM} ${OBJECTDIR}/_ext/194049764/gl_title_font.o.d 
	@${RM} ${OBJECTDIR}/_ext/194049764/gl_title_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/194049764/gl_title_font.o.d" -o ${OBJECTDIR}/_ext/194049764/gl_title_font.o ../../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_bwfont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c  .generated_files/9bef3fca09d88b47775cf61bfabd7315e8b50829.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_bwfont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_bwfont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_encoding.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c  .generated_files/acde291a5fba23b9fa9ed43e3035e92e7a9cc293.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_encoding.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_encoding.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_encoding.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_font.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c  .generated_files/31063b0ae6aecd18f2e9d132f5966c866ab6319b.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_font.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_font.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_font.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_font.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_justify.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c  .generated_files/7b234bdfed8784e04fa7df1979175eaa6ed2c9cc.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_justify.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_justify.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_justify.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_justify.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_kerning.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c  .generated_files/c3692bdf4417d61c2b4db32252fe541430c30b08.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_kerning.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_kerning.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_kerning.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_rlefont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c  .generated_files/454cd20ca8aa16eba0c53c1ece5644230e3c9cde.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_rlefont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_rlefont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c  .generated_files/5e002641a16bd450e24f06f238bd39e738dc94f0.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_scaledfont.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o: ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c  .generated_files/bccf12c9800bdad2870449eab148cd909f4b6787.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1391772861" 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o.d" -o ${OBJECTDIR}/_ext/1391772861/mf_wordwrap.o ../../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o: ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c  .generated_files/b8565452363dc0380e1e0a521a06e1b2f52656be.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o.d" -o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16.o ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o: ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c  .generated_files/b20328f39eff5a8b1aab4ef7406afcf9fceed0c5.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o.d" -o ${OBJECTDIR}/_ext/2039457820/BLKCHCRY16bw.o ../../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o: ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c  .generated_files/d47b1d8199c389a5d9a60c2920a4fb3a2d3066b.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/2039457820" 
	@${RM} ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d 
	@${RM} ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o.d" -o ${OBJECTDIR}/_ext/2039457820/dejavu_sans_12.o ../../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494914114/gl.o: ../../../../../MiniWin/gl/gl.c  .generated_files/44e3e2dc0c9820908f5719fae808bfffde4d9cf.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494914114" 
	@${RM} ${OBJECTDIR}/_ext/1494914114/gl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494914114/gl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494914114/gl.o.d" -o ${OBJECTDIR}/_ext/1494914114/gl.o ../../../../../MiniWin/gl/gl.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1770599754/hal_delay.o: ../../../../../MiniWin/hal/esp32-idf/hal_delay.c  .generated_files/5fa9beb5586575872ca66f5e0505b9be9de99ce0.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1770599754" 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1770599754/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1770599754/hal_delay.o ../../../../../MiniWin/hal/esp32-idf/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1770599754/hal_lcd.o: ../../../../../MiniWin/hal/esp32-idf/hal_lcd.c  .generated_files/8082c68acf9c099301d26ca4b5cbd52d5b90749d.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1770599754" 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1770599754/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1770599754/hal_lcd.o ../../../../../MiniWin/hal/esp32-idf/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1770599754/hal_non_vol.o: ../../../../../MiniWin/hal/esp32-idf/hal_non_vol.c  .generated_files/d03983ee36f9a21ab9fee674d802d7dbfa45f185.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1770599754" 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1770599754/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1770599754/hal_non_vol.o ../../../../../MiniWin/hal/esp32-idf/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1770599754/hal_timer.o: ../../../../../MiniWin/hal/esp32-idf/hal_timer.c  .generated_files/700044d715fe865de2424ce6eadbe4336d1d2cf2.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1770599754" 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1770599754/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1770599754/hal_timer.o ../../../../../MiniWin/hal/esp32-idf/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1770599754/hal_touch.o: ../../../../../MiniWin/hal/esp32-idf/hal_touch.c  .generated_files/d68b1eaf3b00809bec051a7a8de4af4e48faece5.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1770599754" 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1770599754/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1770599754/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1770599754/hal_touch.o ../../../../../MiniWin/hal/esp32-idf/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_delay.o: ../../../../../MiniWin/hal/linux/hal_delay.c  .generated_files/ac8b31a231184b53a40a20b4940c628e060df0c1.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_delay.o ../../../../../MiniWin/hal/linux/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_lcd.o: ../../../../../MiniWin/hal/linux/hal_lcd.c  .generated_files/a0e964def2e4feaba3b58bc4e70e18e57751217e.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_lcd.o ../../../../../MiniWin/hal/linux/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_non_vol.o: ../../../../../MiniWin/hal/linux/hal_non_vol.c  .generated_files/1bb0411ace090957a412e2e1d310fc1519cc8439.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_non_vol.o ../../../../../MiniWin/hal/linux/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_timer.o: ../../../../../MiniWin/hal/linux/hal_timer.c  .generated_files/90fe177cce297cfcddb56a53500d56054dfdee1c.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_timer.o ../../../../../MiniWin/hal/linux/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1184163457/hal_touch.o: ../../../../../MiniWin/hal/linux/hal_touch.c  .generated_files/c63eb3590a1381f0f26d0a0fe5fdc94ebcc56296.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1184163457" 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1184163457/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1184163457/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1184163457/hal_touch.o ../../../../../MiniWin/hal/linux/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_delay.o: ../../../../../MiniWin/hal/lpc54628/hal_delay.c  .generated_files/53e5d61c4e96e4335adc9345c24fcc0af1d0f91f.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_delay.o ../../../../../MiniWin/hal/lpc54628/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_lcd.o: ../../../../../MiniWin/hal/lpc54628/hal_lcd.c  .generated_files/fab61fb9567001ca2a6c17dbd651285d2e1baf4.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_lcd.o ../../../../../MiniWin/hal/lpc54628/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_non_vol.o: ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c  .generated_files/9f11e272e6e213f16f859495f4176b39654cc84d.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_non_vol.o ../../../../../MiniWin/hal/lpc54628/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_timer.o: ../../../../../MiniWin/hal/lpc54628/hal_timer.c  .generated_files/9bf7df526bea9e34edf4f8db2ad9c4be27f7ab6e.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_timer.o ../../../../../MiniWin/hal/lpc54628/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1305585261/hal_touch.o: ../../../../../MiniWin/hal/lpc54628/hal_touch.c  .generated_files/eaec9f18a84b9fc77222cc0acb054c7d69886a90.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1305585261" 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1305585261/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1305585261/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1305585261/hal_touch.o ../../../../../MiniWin/hal/lpc54628/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_delay.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c  .generated_files/a112a1034f859a8a9c66d4bf09abb5642f7c654.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_delay.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_delay.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_lcd.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c  .generated_files/f5dea00b2daa949a3e4b0db897be91b895c0b45e.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_lcd.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_non_vol.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c  .generated_files/2587400909a26e7d6e526078d18b7265693cc97a.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_non_vol.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_timer.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c  .generated_files/e19dcdba064dac4009785594587c51fff8c7a9e3.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_timer.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_timer.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/818872118/hal_touch.o: ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c  .generated_files/226c8dcfba2fa98a000fd8dfe070fbb989d219ba.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/818872118" 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/818872118/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/818872118/hal_touch.o.d" -o ${OBJECTDIR}/_ext/818872118/hal_touch.o ../../../../../MiniWin/hal/PIC32MX470F512H/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_delay.o: ../../../../../MiniWin/hal/rx65n/hal_delay.c  .generated_files/ad746ca52f6c2d65e69205d257a505de7d72124c.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_delay.o ../../../../../MiniWin/hal/rx65n/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_lcd.o: ../../../../../MiniWin/hal/rx65n/hal_lcd.c  .generated_files/ed94497c867a64814385f47d7cc5217056709e8c.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_lcd.o ../../../../../MiniWin/hal/rx65n/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_non_vol.o: ../../../../../MiniWin/hal/rx65n/hal_non_vol.c  .generated_files/d4528ed6d5ce54867a919383f0e038a80d0c52c6.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_non_vol.o ../../../../../MiniWin/hal/rx65n/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_timer.o: ../../../../../MiniWin/hal/rx65n/hal_timer.c  .generated_files/19db099b1a881c9831fb2e0f949a05a0316bf35.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_timer.o ../../../../../MiniWin/hal/rx65n/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1178231276/hal_touch.o: ../../../../../MiniWin/hal/rx65n/hal_touch.c  .generated_files/8dc78ce7324a23727caa66e1870cc9704b7d417e.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1178231276" 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1178231276/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1178231276/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1178231276/hal_touch.o ../../../../../MiniWin/hal/rx65n/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_delay.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c  .generated_files/622a93ff0cdcde5c0365c8f4a1352bb2fb181d98.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_delay.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_delay.o ../../../../../MiniWin/hal/rx65n_gcc/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_lcd.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c  .generated_files/c0652793392669f708c599d1f882e16f3c38d7.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_lcd.o ../../../../../MiniWin/hal/rx65n_gcc/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_non_vol.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c  .generated_files/d24b0a3edf6672766a3baeda8b0c4a84b47d6172.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_non_vol.o ../../../../../MiniWin/hal/rx65n_gcc/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_timer.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c  .generated_files/78d69c053d785663c2d12a517d59bbc9959d0682.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_timer.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_timer.o ../../../../../MiniWin/hal/rx65n_gcc/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/51196508/hal_touch.o: ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c  .generated_files/44fa2dfaecec89c399eb3b60946a98cda654a80e.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/51196508" 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/51196508/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/51196508/hal_touch.o.d" -o ${OBJECTDIR}/_ext/51196508/hal_touch.o ../../../../../MiniWin/hal/rx65n_gcc/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_delay.o: ../../../../../MiniWin/hal/stm32f407/hal_delay.c  .generated_files/f961ed5f4517bcffc45cc04e8db0783a29247c13.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_delay.o ../../../../../MiniWin/hal/stm32f407/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_lcd.o: ../../../../../MiniWin/hal/stm32f407/hal_lcd.c  .generated_files/32580f78a4c8a0f82da63d24f216219b084992a7.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_lcd.o ../../../../../MiniWin/hal/stm32f407/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_non_vol.o: ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c  .generated_files/22fbe3e518a600fd6b685e314c658f469a26ca61.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_non_vol.o ../../../../../MiniWin/hal/stm32f407/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_timer.o: ../../../../../MiniWin/hal/stm32f407/hal_timer.c  .generated_files/9c21f4f6dddfeadc3527314810605c95025e2c95.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_timer.o ../../../../../MiniWin/hal/stm32f407/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985835/hal_touch.o: ../../../../../MiniWin/hal/stm32f407/hal_touch.c  .generated_files/1040fab2aacabb97b6623909e36f85db9da50c8e.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985835" 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985835/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985835/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1317985835/hal_touch.o ../../../../../MiniWin/hal/stm32f407/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_delay.o: ../../../../../MiniWin/hal/stm32f429/hal_delay.c  .generated_files/f03a4a1ea0cd07839e437b28c17221108363bb42.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_delay.o ../../../../../MiniWin/hal/stm32f429/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_lcd.o: ../../../../../MiniWin/hal/stm32f429/hal_lcd.c  .generated_files/f4247475b0bdb35cbd843d37ada1c5c436ed52bc.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_lcd.o ../../../../../MiniWin/hal/stm32f429/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_non_vol.o: ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c  .generated_files/e31b03a8851a66eec08b6c2cf68da5934b4e92bd.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_non_vol.o ../../../../../MiniWin/hal/stm32f429/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_timer.o: ../../../../../MiniWin/hal/stm32f429/hal_timer.c  .generated_files/6ad2aa977605e3ed04e4573c4929b0a18e4f1b71.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_timer.o ../../../../../MiniWin/hal/stm32f429/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1317985899/hal_touch.o: ../../../../../MiniWin/hal/stm32f429/hal_touch.c  .generated_files/c38d9b64fa61c0e13a97acc9e945f0727919faca.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1317985899" 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1317985899/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1317985899/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1317985899/hal_touch.o ../../../../../MiniWin/hal/stm32f429/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_delay.o: ../../../../../MiniWin/hal/windows/hal_delay.c  .generated_files/d0d4754b2a8732b5c0bbb81739fb194eee0929fc.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_delay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_delay.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_delay.o ../../../../../MiniWin/hal/windows/hal_delay.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_lcd.o: ../../../../../MiniWin/hal/windows/hal_lcd.c  .generated_files/6b2a5557bf0d0626d25305617567b8893efd5b17.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_lcd.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_lcd.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_lcd.o ../../../../../MiniWin/hal/windows/hal_lcd.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_non_vol.o: ../../../../../MiniWin/hal/windows/hal_non_vol.c  .generated_files/dcb2944f5ae53dd2b490ee0109bf19f3d175afc1.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_non_vol.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_non_vol.o ../../../../../MiniWin/hal/windows/hal_non_vol.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_timer.o: ../../../../../MiniWin/hal/windows/hal_timer.c  .generated_files/516f80f139bab9995cad3cb8fbf6e1537a3efd2c.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_timer.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_timer.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_timer.o ../../../../../MiniWin/hal/windows/hal_timer.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1357345870/hal_touch.o: ../../../../../MiniWin/hal/windows/hal_touch.c  .generated_files/7ef4ad8e61405278a2700d184fb6db460eb59ce9.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1357345870" 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/1357345870/hal_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1357345870/hal_touch.o.d" -o ${OBJECTDIR}/_ext/1357345870/hal_touch.o ../../../../../MiniWin/hal/windows/hal_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/902303450/hal_init.o: ../../../../../MiniWin/hal/hal_init.c  .generated_files/9252e49ebc8e56394d84364153610c7f58b69bbb.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/902303450" 
	@${RM} ${OBJECTDIR}/_ext/902303450/hal_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/902303450/hal_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/902303450/hal_init.o.d" -o ${OBJECTDIR}/_ext/902303450/hal_init.o ../../../../../MiniWin/hal/hal_init.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_arrow.o: ../../../../../MiniWin/ui/ui_arrow.c  .generated_files/b861da7258bcce4de4463f5e4b85602b37029811.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_arrow.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_arrow.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_arrow.o ../../../../../MiniWin/ui/ui_arrow.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_button.o: ../../../../../MiniWin/ui/ui_button.c  .generated_files/7c4d71acfa7fb1d315e5646eb5a4c4bc6feb3ce3.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_button.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_button.o ../../../../../MiniWin/ui/ui_button.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_check_box.o: ../../../../../MiniWin/ui/ui_check_box.c  .generated_files/7d0566d62ed7901b0997795bf76e1abf894de67c.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_check_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_check_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_check_box.o ../../../../../MiniWin/ui/ui_check_box.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_common.o: ../../../../../MiniWin/ui/ui_common.c  .generated_files/9aafad66d4f146b09427716ae2cb14285f664c0a.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_common.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_common.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_common.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_common.o ../../../../../MiniWin/ui/ui_common.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_keyboard.o: ../../../../../MiniWin/ui/ui_keyboard.c  .generated_files/4245f4170281cf59927e66ce85a3f9b451ae8d37.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_keyboard.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_keyboard.o ../../../../../MiniWin/ui/ui_keyboard.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_keypad.o: ../../../../../MiniWin/ui/ui_keypad.c  .generated_files/6fe2a99e1de6b4bbd9f0b11b0490f3e600e67a18.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_keypad.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_keypad.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_keypad.o ../../../../../MiniWin/ui/ui_keypad.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_label.o: ../../../../../MiniWin/ui/ui_label.c  .generated_files/f3ed0bb5e7beb09c8b27267c0d23f28c6e112eea.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_label.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_label.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_label.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_label.o ../../../../../MiniWin/ui/ui_label.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_list_box.o: ../../../../../MiniWin/ui/ui_list_box.c  .generated_files/d925487f6e4f4ae91e2f8df96f3256abc6f95cbd.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_list_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_list_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_list_box.o ../../../../../MiniWin/ui/ui_list_box.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o: ../../../../../MiniWin/ui/ui_progress_bar.c  .generated_files/1ccadff55fd020eda38163ad258aa85f5a1102b8.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_progress_bar.o ../../../../../MiniWin/ui/ui_progress_bar.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_radio_button.o: ../../../../../MiniWin/ui/ui_radio_button.c  .generated_files/c42915875f6fb8f52ba195a1cfbcf2711d572470.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_radio_button.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_radio_button.o ../../../../../MiniWin/ui/ui_radio_button.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o: ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c  .generated_files/b87f0886db76861b9b7d3715ddecc93160006b70.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_horiz.o ../../../../../MiniWin/ui/ui_scroll_bar_horiz.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o: ../../../../../MiniWin/ui/ui_scroll_bar_vert.c  .generated_files/ba668afbdf7a7a7357726e7050aeb9f79bf5ce70.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_scroll_bar_vert.o ../../../../../MiniWin/ui/ui_scroll_bar_vert.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_tabs.o: ../../../../../MiniWin/ui/ui_tabs.c  .generated_files/2507a22a49db3269c1c05f900969f44c2f358080.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tabs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_tabs.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_tabs.o ../../../../../MiniWin/ui/ui_tabs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_text_box.o: ../../../../../MiniWin/ui/ui_text_box.c  .generated_files/63ef67e5d46120b42efd5cd802a044aebf7cfc2f.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_text_box.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_text_box.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_text_box.o ../../../../../MiniWin/ui/ui_text_box.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1494913683/ui_tree.o: ../../../../../MiniWin/ui/ui_tree.c  .generated_files/fb5cde26d8405dea97b0e8662291691084f07af9.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1494913683" 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tree.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494913683/ui_tree.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1494913683/ui_tree.o.d" -o ${OBJECTDIR}/_ext/1494913683/ui_tree.o ../../../../../MiniWin/ui/ui_tree.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/calibrate.o: ../../../../../MiniWin/calibrate.c  .generated_files/33741f03eaa6df2bced6affe2fd7987acb5e2fe2.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/calibrate.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/calibrate.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/calibrate.o.d" -o ${OBJECTDIR}/_ext/59636182/calibrate.o ../../../../../MiniWin/calibrate.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin.o: ../../../../../MiniWin/miniwin.c  .generated_files/afe8e6e60f11f382769aeb1ccd783a144ad7cf19.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin.o ../../../../../MiniWin/miniwin.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_debug.o: ../../../../../MiniWin/miniwin_debug.c  .generated_files/23754b3e66ee6466fdfd47d02567e6580f69e86b.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_debug.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_debug.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_debug.o ../../../../../MiniWin/miniwin_debug.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o: ../../../../../MiniWin/miniwin_message_queue.c  .generated_files/9c190cb3665de8b4b3ba411e4fda509ba61503ae.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_message_queue.o ../../../../../MiniWin/miniwin_message_queue.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_settings.o: ../../../../../MiniWin/miniwin_settings.c  .generated_files/40e1aaeb7694a1225809ec97008a09016daaaa23.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_settings.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_settings.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_settings.o ../../../../../MiniWin/miniwin_settings.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_touch.o: ../../../../../MiniWin/miniwin_touch.c  .generated_files/60a0c034c2ba10b1299782090a1d312d4492ab42.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_touch.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_touch.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_touch.o ../../../../../MiniWin/miniwin_touch.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o: ../../../../../MiniWin/miniwin_tree_container.c  .generated_files/d8521c9258af79e42334a5ee1ed12e19a3f1e8d3.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_tree_container.o ../../../../../MiniWin/miniwin_tree_container.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/59636182/miniwin_utilities.o: ../../../../../MiniWin/miniwin_utilities.c  .generated_files/87fdccdc5800c6d739a77777c7b23d2f7eccd070.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/59636182" 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d 
	@${RM} ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/59636182/miniwin_utilities.o.d" -o ${OBJECTDIR}/_ext/59636182/miniwin_utilities.o ../../../../../MiniWin/miniwin_utilities.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692562174/main.o: ../../../../../MiniWinSimple_Common/main.c  .generated_files/c3e96f2c698eb01486c6781ef34c5392ef7be0e4.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/692562174" 
	@${RM} ${OBJECTDIR}/_ext/692562174/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/692562174/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692562174/main.o.d" -o ${OBJECTDIR}/_ext/692562174/main.o ../../../../../MiniWinSimple_Common/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692562174/miniwin_user.o: ../../../../../MiniWinSimple_Common/miniwin_user.c  .generated_files/692cb5f98fe5651085e12fb01f8c297616375263.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/692562174" 
	@${RM} ${OBJECTDIR}/_ext/692562174/miniwin_user.o.d 
	@${RM} ${OBJECTDIR}/_ext/692562174/miniwin_user.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692562174/miniwin_user.o.d" -o ${OBJECTDIR}/_ext/692562174/miniwin_user.o ../../../../../MiniWinSimple_Common/miniwin_user.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/692562174/window_simple.o: ../../../../../MiniWinSimple_Common/window_simple.c  .generated_files/26525dbc27ff3e60c3e46963f8c323a06d555bbc.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/692562174" 
	@${RM} ${OBJECTDIR}/_ext/692562174/window_simple.o.d 
	@${RM} ${OBJECTDIR}/_ext/692562174/window_simple.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/692562174/window_simple.o.d" -o ${OBJECTDIR}/_ext/692562174/window_simple.o ../../../../../MiniWinSimple_Common/window_simple.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1445274692/app.o: ../../src/app.c  .generated_files/16417d0ac3f3821b1421c113676e3e983093997f.flag .generated_files/9c38dd73fa47c8727ca672a3ac38932765b77050.flag
	@${MKDIR} "${OBJECTDIR}/_ext/1445274692" 
	@${RM} ${OBJECTDIR}/_ext/1445274692/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1445274692/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -DPIC32MX470F512H -I"../src" -I"../src/config/default" -I"../src/packs/PIC32MX470F512H_DFP" -I"../../../../../MiniWin" -I"../../../../../MiniWin/gl/fonts/truetype/mcufont" -I"../../../../../MiniWinSimple_Common" -I"../../src" -Werror -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1445274692/app.o.d" -o ${OBJECTDIR}/_ext/1445274692/app.o ../../src/app.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MiniWinSimple.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../src/config/default/p32MX470F512H.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MiniWinSimple.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC0275F  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MiniWinSimple.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../src/config/default/p32MX470F512H.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MiniWinSimple.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MiniWinSimple.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
