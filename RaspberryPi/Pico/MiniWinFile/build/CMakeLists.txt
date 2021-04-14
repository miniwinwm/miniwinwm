cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(MiniWinFile)
pico_sdk_init()

add_compile_definitions(RASPBERRY_PI_PICO)

include_directories(
# MiniWin paths
    ../../../../MiniWin 
	../../../../MiniWin
	../../../../MiniWin/gl/fonts/truetype/mcufont
# FatFS paths
    ../FatFS
# Project common paths
    ../src
# Project specific paths    
	../../../../MiniWinFile_Common
)

add_executable(MiniWinFile
# MiniWin source files
	../../../../MiniWin/hal/RaspberryPiPico/hal_delay.c
	../../../../MiniWin/hal/RaspberryPiPico/hal_timer.c
	../../../../MiniWin/hal/hal_init.c
	../../../../MiniWin/hal/RaspberryPiPico/hal_non_vol.c
	../../../../MiniWin/hal/RaspberryPiPico/hal_touch.c
	../../../../MiniWin/hal/RaspberryPiPico/hal_lcd.c
	../../../../MiniWin/calibrate.c
    ../../../../MiniWin/miniwin.c
    ../../../../MiniWin/miniwin_debug.c
    ../../../../MiniWin/miniwin_message_queue.c
    ../../../../MiniWin/miniwin_settings.c
    ../../../../MiniWin/miniwin_touch.c
    ../../../../MiniWin/miniwin_tree_container.c
    ../../../../MiniWin/miniwin_utilities.c
    ../../../../MiniWin/bitmaps/backspace_key.c
    ../../../../MiniWin/bitmaps/close_icon.c
    ../../../../MiniWin/bitmaps/close_icon_large.c
    ../../../../MiniWin/bitmaps/file_icon_large.c
    ../../../../MiniWin/bitmaps/file_icon_small.c
    ../../../../MiniWin/bitmaps/folder_close_icon_large.c
    ../../../../MiniWin/bitmaps/folder_close_icon_small.c
    ../../../../MiniWin/bitmaps/folder_icon_large.c
    ../../../../MiniWin/bitmaps/folder_icon_small.c
    ../../../../MiniWin/bitmaps/folder_open_icon_large.c
    ../../../../MiniWin/bitmaps/folder_open_icon_small.c
    ../../../../MiniWin/bitmaps/let_key.c
    ../../../../MiniWin/bitmaps/maximise_icon.c
    ../../../../MiniWin/bitmaps/maximise_icon_large.c
    ../../../../MiniWin/bitmaps/minimise_icon.c
    ../../../../MiniWin/bitmaps/minimise_icon_large.c
    ../../../../MiniWin/bitmaps/num_key.c
    ../../../../MiniWin/bitmaps/resize_icon.c
    ../../../../MiniWin/bitmaps/resize_icon_large.c
    ../../../../MiniWin/bitmaps/shift_key.c
    ../../../../MiniWin/bitmaps/sym_key.c
    ../../../../MiniWin/bitmaps/tick.c
    ../../../../MiniWin/bitmaps/tick_large.c
    ../../../../MiniWin/dialogs/dialog_colour_chooser.c
    ../../../../MiniWin/dialogs/dialog_date_chooser.c
    ../../../../MiniWin/dialogs/dialog_file_chooser.c
    ../../../../MiniWin/dialogs/dialog_number_entry.c
    ../../../../MiniWin/dialogs/dialog_one_button.c
    ../../../../MiniWin/dialogs/dialog_text_entry.c
    ../../../../MiniWin/dialogs/dialog_time_chooser.c
    ../../../../MiniWin/dialogs/dialog_two_button.c
    ../../../../MiniWin/gl/gl.c
    ../../../../MiniWin/gl/fonts/bitmapped/font9.c
    ../../../../MiniWin/gl/fonts/bitmapped/font12.c
    ../../../../MiniWin/gl/fonts/bitmapped/font16.c
    ../../../../MiniWin/gl/fonts/bitmapped/font20.c
    ../../../../MiniWin/gl/fonts/bitmapped/font24.c
    ../../../../MiniWin/gl/fonts/bitmapped/gl_title_font.c
    ../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16.c
    ../../../../MiniWin/gl/fonts/truetype/BLKCHCRY16bw.c
    ../../../../MiniWin/gl/fonts/truetype/dejavu_sans_12.c
    ../../../../MiniWin/gl/fonts/truetype/mcufont/mf_bwfont.c
    ../../../../MiniWin/gl/fonts/truetype/mcufont/mf_encoding.c
    ../../../../MiniWin/gl/fonts/truetype/mcufont/mf_font.c
    ../../../../MiniWin/gl/fonts/truetype/mcufont/mf_justify.c
    ../../../../MiniWin/gl/fonts/truetype/mcufont/mf_kerning.c
    ../../../../MiniWin/gl/fonts/truetype/mcufont/mf_rlefont.c
    ../../../../MiniWin/gl/fonts/truetype/mcufont/mf_scaledfont.c
    ../../../../MiniWin/gl/fonts/truetype/mcufont/mf_wordwrap.c
    ../../../../MiniWin/ui/ui_arrow.c
    ../../../../MiniWin/ui/ui_button.c
    ../../../../MiniWin/ui/ui_check_box.c
    ../../../../MiniWin/ui/ui_common.c
    ../../../../MiniWin/ui/ui_keyboard.c
    ../../../../MiniWin/ui/ui_keypad.c
    ../../../../MiniWin/ui/ui_label.c
    ../../../../MiniWin/ui/ui_list_box.c
    ../../../../MiniWin/ui/ui_progress_bar.c
    ../../../../MiniWin/ui/ui_radio_button.c
    ../../../../MiniWin/ui/ui_scroll_bar_horiz.c
    ../../../../MiniWin/ui/ui_scroll_bar_vert.c
    ../../../../MiniWin/ui/ui_tabs.c
    ../../../../MiniWin/ui/ui_text_box.c
    ../../../../MiniWin/ui/ui_tree.c	
# FatFS source files
    ../FatFS/ff.c
    ../FatFS/sdmm.c
    ../FatFS/spi_driver.c
# Project common source files
	../src/app.c
	../../../../MiniWinFile_Common/main.c        
	../../../../MiniWinFile_Common/miniwin_user.c
# Project specific source files    
	../../../../MiniWinFile_Common/window_file.c
	../../../../MiniWinFile_Common/window_file_tree.c
	../../../../MiniWinFile_Common/window_image.c
	../../../../MiniWinFile_Common/window_selection.c
    ../../../../MiniWinFile_Common/window_text.c
)

target_link_libraries(MiniWinFile pico_stdlib hardware_spi hardware_flash hardware_rtc)

pico_add_extra_outputs(MiniWinFile)
