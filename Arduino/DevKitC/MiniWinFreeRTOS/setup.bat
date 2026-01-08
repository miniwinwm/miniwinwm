rmdir /s /q src

REM FOLDERS
mkdir src
mkdir src\hal
mkdir src\hal\hal
mkdir src\gl
mkdir src\gl\hal
mkdir src\gl\gl
mkdir src\gl\gl\hal
mkdir src\gl\gl\fonts\bitmapped
mkdir src\gl\gl\fonts\truetype\mcufont
mkdir src\gl\gl\gl\fonts\bitmapped
mkdir src\bitmaps
mkdir src\bitmaps\bitmaps
mkdir src\dialogs
mkdir src\dialogs\hal
mkdir src\dialogs\gl
mkdir src\dialogs\gl\hal
mkdir src\dialogs\gl\gl\fonts\bitmapped
mkdir src\dialogs\ui
mkdir src\dialogs\ui\ui
mkdir src\dialogs\dialogs
mkdir src\dialogs\dialogs\dialogs
mkdir src\dialogs\bitmaps
mkdir src\bitmaps
mkdir src\ui
mkdir src\ui\ui
mkdir src\ui\ui\ui
mkdir src\ui\hal
mkdir src\ui\gl
mkdir src\ui\gl\hal
mkdir src\ui\gl\gl\fonts\bitmapped
mkdir src\ui\bitmaps
mkdir src\ui\dialogs
mkdir src\ui\dialogs\dialogs

REM HAL 
mklink /h src\hal\hal_init.c ..\..\..\MiniWin\hal\hal_init.c
mklink /h src\hal\hal_delay.c ..\..\..\MiniWin\hal\Arduino_DevKitC\hal_delay.c 
mklink /h src\hal\hal_lcd.c ..\..\..\MiniWin\hal\Arduino_DevKitC\hal_lcd.c 
mklink /h src\hal\hal_non_vol.c ..\..\..\MiniWin\hal\Arduino_DevKitC\hal_non_vol.c 
mklink /h src\hal\hal_timer.c ..\..\..\MiniWin\hal\Arduino_DevKitC\hal_timer.c 
mklink /h src\hal\hal_touch.c ..\..\..\MiniWin\hal\Arduino_DevKitC\hal_touch.c 
mklink /h src\hal\hal\hal_delay.h ..\..\..\MiniWin\hal\hal_delay.h 
mklink /h src\hal\hal\hal_init.h ..\..\..\MiniWin\hal\hal_init.h 
mklink /h src\hal\hal\hal_lcd.h ..\..\..\MiniWin\hal\hal_lcd.h 
mklink /h src\hal\hal\hal_non_vol.h ..\..\..\MiniWin\hal\hal_non_vol.h 
mklink /h src\hal\hal\hal_timer.h ..\..\..\MiniWin\hal\hal_timer.h 
mklink /h src\hal\hal\hal_touch.h ..\..\..\MiniWin\hal\hal_touch.h 
mklink /h src\hal\miniwin_config.h ..\..\..\MiniWinFreeRTOS_Common\miniwin_config.h 

REM GL
mklink /h src\gl\gl.c ..\..\..\MiniWin\gl\gl.c 
mklink /h src\gl\font9.c ..\..\..\MiniWin\gl\fonts\bitmapped\font9.c
mklink /h src\gl\font12.c ..\..\..\MiniWin\gl\fonts\bitmapped\font12.c
mklink /h src\gl\font16.c ..\..\..\MiniWin\gl\fonts\bitmapped\font16.c
mklink /h src\gl\font20.c ..\..\..\MiniWin\gl\fonts\bitmapped\font20.c
mklink /h src\gl\font24.c ..\..\..\MiniWin\gl\fonts\bitmapped\font24.c
mklink /h src\gl\gl_title_font.c ..\..\..\MiniWin\gl\fonts\bitmapped\gl_title_font.c
mklink /h src\gl\gl\fonts\truetype\mcufont\BLKCHCRY16.c ..\..\..\MiniWin\gl\fonts\truetype\BLKCHCRY16.c
mklink /h src\gl\gl\fonts\truetype\mcufont\BLKCHCRY16bw.c ..\..\..\MiniWin\gl\fonts\truetype\BLKCHCRY16bw.c
mklink /h src\gl\gl\fonts\truetype\mcufont\dejavu_sans_12.c ..\..\..\MiniWin\gl\fonts\truetype\dejavu_sans_12.c
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_encoding.c ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_encoding.c
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_bwfont.c ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_bwfont.c
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_font.c ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_font.c
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_justify.c ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_justify.c
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_mf_kerning.c ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_kerning.c
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_rlefont.c ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_rlefont.c
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_scaledfont.c ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_scaledfont.c
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_wordwrap.c ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_wordwrap.c
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_bwfont.h ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_bwfont.h
mklink /h src\gl\miniwin_debug.h ..\..\..\MiniWin\miniwin_debug.h
mklink /h src\gl\miniwin_config.h ..\..\..\MiniWinFreeRTOS_Common\miniwin_config.h
mklink /h src\gl\gl\gl.h ..\..\..\MiniWin\gl\gl.h
mklink /h src\gl\gl\miniwin_utilities.h ..\..\..\MiniWin\miniwin_utilities.h
mklink /h src\gl\gl\hal\hal_lcd.h ..\..\..\MiniWin\hal\hal_lcd.h
mklink /h src\gl\gl\gl\fonts\bitmapped\fonts.h ..\..\..\MiniWin\gl\fonts\bitmapped\fonts.h
mklink /h src\gl\gl\fonts\bitmapped\fonts.h ..\..\..\MiniWin\gl\fonts\bitmapped\fonts.h
mklink /h src\gl\gl\fonts\bitmapped\gl_title_font.h ..\..\..\MiniWin\gl\fonts\bitmapped\gl_title_font.h
mklink /h src\gl\gl\fonts\truetype\mcufont\mcufont.h ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mcufont.h
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_config.h ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_config.h
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_encoding.h ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_encoding.h
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_justify.h ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_justify.h
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_rlefont.h ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_rlefont.h
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_font.h ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_font.h
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_kerning.h ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_kerning.h
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_scaledfont.h ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_scaledfont.h
mklink /h src\gl\gl\fonts\truetype\mcufont\mf_wordwrap.h ..\..\..\MiniWin\gl\fonts\truetype\mcufont\mf_wordwrap.h
mklink /h src\gl\fonts.h ..\..\..\MiniWin\gl\fonts\bitmapped\fonts.h

REM BITMAPS
mklink /h src\bitmaps\bitmaps\mw_bitmaps.h ..\..\..\MiniWin\bitmaps\mw_bitmaps.h
mklink /h src\bitmaps\backspace_key.c ..\..\..\MiniWin\bitmaps\backspace_key.c 
mklink /h src\bitmaps\close_icon.c ..\..\..\MiniWin\bitmaps\close_icon.c
mklink /h src\bitmaps\close_icon_large.c ..\..\..\MiniWin\bitmaps\close_icon_large.c
mklink /h src\bitmaps\file_icon_large.c ..\..\..\MiniWin\bitmaps\file_icon_large.c
mklink /h src\bitmaps\file_icon_small.c ..\..\..\MiniWin\bitmaps\file_icon_small.c
mklink /h src\bitmaps\folder_close_icon_large.c ..\..\..\MiniWin\bitmaps\folder_close_icon_large.c
mklink /h src\bitmaps\folder_close_icon_small.c ..\..\..\MiniWin\bitmaps\folder_close_icon_small.c
mklink /h src\bitmaps\folder_icon_large.c ..\..\..\MiniWin\bitmaps\folder_icon_large.c
mklink /h src\bitmaps\folder_icon_small.c ..\..\..\MiniWin\bitmaps\folder_icon_small.c
mklink /h src\bitmaps\folder_open_icon_large.c ..\..\..\MiniWin\bitmaps\folder_open_icon_large.c
mklink /h src\bitmaps\folder_open_icon_small.c ..\..\..\MiniWin\bitmaps\folder_open_icon_small.c
mklink /h src\bitmaps\let_key.c ..\..\..\MiniWin\bitmaps\let_key.c
mklink /h src\bitmaps\maximise_icon.c ..\..\..\MiniWin\bitmaps\maximise_icon.c
mklink /h src\bitmaps\maximise_icon_large.c ..\..\..\MiniWin\bitmaps\maximise_icon_large.c
mklink /h src\bitmaps\minimise_icon.c ..\..\..\MiniWin\bitmaps\minimise_icon.c
mklink /h src\bitmaps\minimise_icon_large.c ..\..\..\MiniWin\bitmaps\minimise_icon_large.c
mklink /h src\bitmaps\num_key.c ..\..\..\MiniWin\bitmaps\num_key.c
mklink /h src\bitmaps\resize_icon.c ..\..\..\MiniWin\bitmaps\resize_icon.c
mklink /h src\bitmaps\resize_icon_large.c ..\..\..\MiniWin\bitmaps\resize_icon_large.c
mklink /h src\bitmaps\shift_key.c ..\..\..\MiniWin\bitmaps\shift_key.c
mklink /h src\bitmaps\sym_key.c ..\..\..\MiniWin\bitmaps\sym_key.c
mklink /h src\bitmaps\tick.c ..\..\..\MiniWin\bitmaps\tick.c
mklink /h src\bitmaps\tick_large.c ..\..\..\MiniWin\bitmaps\tick_large.c

REM DIALOGS
mklink /h src\dialogs\dialog_colour_chooser.c ..\..\..\MiniWin\dialogs\dialog_colour_chooser.c
mklink /h src\dialogs\dialog_date_chooser.c ..\..\..\MiniWin\dialogs\dialog_date_chooser.c
mklink /h src\dialogs\dialog_file_chooser.c ..\..\..\MiniWin\dialogs\dialog_file_chooser.c
mklink /h src\dialogs\dialog_number_entry.c ..\..\..\MiniWin\dialogs\dialog_number_entry.c
mklink /h src\dialogs\dialog_one_button.c ..\..\..\MiniWin\dialogs\dialog_one_button.c 
mklink /h src\dialogs\dialog_text_entry.c ..\..\..\MiniWin\dialogs\dialog_text_entry.c
mklink /h src\dialogs\dialog_time_chooser.c ..\..\..\MiniWin\dialogs\dialog_time_chooser.c
mklink /h src\dialogs\dialog_dialog_two_button.c ..\..\..\MiniWin\dialogs\dialog_two_button.c
mklink /h src\dialogs\miniwin.h ..\..\..\MiniWin\miniwin.h
mklink /h src\dialogs\miniwin_config.h ..\..\..\MiniWinFreeRTOS_Common\miniwin_config.h
mklink /h src\dialogs\miniwin_debug.h ..\..\..\MiniWin\miniwin_debug.h
mklink /h src\dialogs\miniwin_settings.h ..\..\..\MiniWin\miniwin_settings.h
mklink /h src\dialogs\calibrate.h ..\..\..\MiniWin\calibrate.h
mklink /h src\dialogs\gl\gl.h ..\..\..\MiniWin\gl\gl.h
mklink /h src\dialogs\gl\miniwin_utilities.h ..\..\..\MiniWin\miniwin_utilities.h
mklink /h src\dialogs\gl\hal\hal_lcd.h ..\..\..\MiniWin\hal\hal_lcd.h
mklink /h src\dialogs\gl\gl\fonts\bitmapped\fonts.h ..\..\..\MiniWin\gl\fonts\bitmapped\fonts.h
mklink /h src\dialogs\bitmaps\mw_bitmaps.h ..\..\..\MiniWin\bitmaps\mw_bitmaps.h
mklink /h src\dialogs\miniwin_utilities.h ..\..\..\MiniWin\miniwin_utilities.h
mklink /h src\dialogs\hal\hal_timer.h ..\..\..\MiniWin\hal\hal_timer.h
mklink /h src\dialogs\ui\ui_common.h ..\..\..\MiniWin\ui\ui_common.h
mklink /h src\dialogs\ui\ui\ui_arrow.h ..\..\..\MiniWin\ui\ui_arrow.h
mklink /h src\dialogs\ui\ui\ui_button.h ..\..\..\MiniWin\ui\ui_button.h
mklink /h src\dialogs\ui\ui\ui_check_box.h ..\..\..\MiniWin\ui\ui_check_box.h
mklink /h src\dialogs\ui\ui\ui_keyboard.h ..\..\..\MiniWin\ui\ui_keyboard.h
mklink /h src\dialogs\ui\ui\ui_keypad.h ..\..\..\MiniWin\ui\ui_keypad.h
mklink /h src\dialogs\ui\ui\ui_label.h ..\..\..\MiniWin\ui\ui_label.h
mklink /h src\dialogs\ui\ui\ui_list_box.h ..\..\..\MiniWin\ui\ui_list_box.h
mklink /h src\dialogs\ui\ui\ui_progress_bar.h ..\..\..\MiniWin\ui\ui_progress_bar.h
mklink /h src\dialogs\ui\ui\ui_radio_button.h ..\..\..\MiniWin\ui\ui_radio_button.h
mklink /h src\dialogs\ui\ui\ui_scroll_bar_horiz.h ..\..\..\MiniWin\ui\ui_scroll_bar_horiz.h
mklink /h src\dialogs\ui\ui\ui_scroll_bar_vert.h ..\..\..\MiniWin\ui\ui_scroll_bar_vert.h
mklink /h src\dialogs\ui\ui\ui_tabs.h ..\..\..\MiniWin\ui\ui_tabs.h
mklink /h src\dialogs\ui\ui\ui_text_box.h ..\..\..\MiniWin\ui\ui_text_box.h
mklink /h src\dialogs\ui\ui\ui_tree.h ..\..\..\MiniWin\ui\ui_tree.h
mklink /h src\dialogs\ui\ui\miniwin_tree_container.h ..\..\..\MiniWin\miniwin_tree_container.h
mklink /h src\dialogs\ui\ui\miniwin.h ..\..\..\MiniWin\miniwin.h
mklink /h src\dialogs\dialogs\dialog_common.h ..\..\..\MiniWin\dialogs\dialog_common.h
mklink /h src\dialogs\dialogs\dialogs\dialog_colour_chooser.h ..\..\..\MiniWin\dialogs\dialog_colour_chooser.h
mklink /h src\dialogs\dialogs\dialogs\dialog_date_chooser.h ..\..\..\MiniWin\dialogs\dialog_date_chooser.h
mklink /h src\dialogs\dialogs\dialogs\dialog_file_chooser.h ..\..\..\MiniWin\dialogs\dialog_file_chooser.h
mklink /h src\dialogs\dialogs\dialogs\dialog_number_entry.h ..\..\..\MiniWin\dialogs\dialog_number_entry.h
mklink /h src\dialogs\dialogs\dialogs\dialog_one_button.h ..\..\..\MiniWin\dialogs\dialog_one_button.h
mklink /h src\dialogs\dialogs\dialogs\dialog_text_entry.h ..\..\..\MiniWin\dialogs\dialog_text_entry.h
mklink /h src\dialogs\dialogs\dialogs\dialog_time_chooser.h ..\..\..\MiniWin\dialogs\dialog_time_chooser.h
mklink /h src\dialogs\dialogs\dialogs\dialog_two_button.h ..\..\..\MiniWin\dialogs\dialog_two_button.h
mklink /h src\dialogs\app.h app\app.h

REM MINIWIN
mklink /h src\miniwin.c ..\..\..\MiniWin\miniwin.c
mklink /h src\miniwin_debug.c ..\..\..\MiniWin\miniwin_debug.c
mklink /h src\miniwin_message_queue.c ..\..\..\MiniWin\miniwin_message_queue.c
mklink /h src\miniwin_settings.c ..\..\..\MiniWin\miniwin_settings.c
mklink /h src\miniwin_touch.c ..\..\..\MiniWin\miniwin_touch.c
mklink /h src\miniwin_tree_container.c ..\..\..\MiniWin\miniwin_tree_container.c
mklink /h src\miniwin_utilities.c ..\..\..\MiniWin\miniwin_utilities.c
mklink /h src\calibrate.c ..\..\..\MiniWin\calibrate.c
mklink /h src\calibrate.h ..\..\..\MiniWin\calibrate.h
mklink /h src\miniwin.h ..\..\..\MiniWin\miniwin.h
mklink /h src\miniwin_config.h ..\..\..\MiniWinFreeRTOS_Common\miniwin_config.h
mklink /h src\miniwin_debug.h ..\..\..\MiniWin\miniwin_debug.h
mklink /h src\miniwin_settings.h ..\..\..\MiniWin\miniwin_settings.h
mklink /h src\miniwin_touch.h ..\..\..\MiniWin\miniwin_touch.h
mklink /h src\gl\gl.h ..\..\..\MiniWin\gl\gl.h
mklink /h src\gl\miniwin_utilities.h ..\..\..\MiniWin\miniwin_utilities.h
mklink /h src\gl\hal\hal_lcd.h ..\..\..\MiniWin\hal\hal_lcd.h
mklink /h src\hal\hal_timer.h ..\..\..\MiniWin\hal\hal_timer.h
mklink /h src\hal\hal_touch.h ..\..\..\MiniWin\hal\hal_touch.h
mklink /h src\hal\hal_init.h ..\..\..\MiniWin\hal\hal_init.h
mklink /h src\hal\hal_non_vol.h ..\..\..\MiniWin\hal\hal_non_vol.h
mklink /h src\hal\hal_lcd.h ..\..\..\MiniWin\hal\hal_lcd.h
mklink /h src\hal\hal_delay.h ..\..\..\MiniWin\hal\hal_delay.h
mklink /h src\bitmaps\mw_bitmaps.h ..\..\..\MiniWin\bitmaps\mw_bitmaps.h
mklink /h src\miniwin_utilities.h ..\..\..\MiniWin\miniwin_utilities.h
mklink /h src\ui\ui_common.h ..\..\..\MiniWin\ui\ui_common.h
mklink /h src\ui\ui\ui_arrow.h ..\..\..\MiniWin\ui\ui_arrow.h
mklink /h src\ui\ui\ui_button.h ..\..\..\MiniWin\ui\ui_button.h
mklink /h src\ui\ui\ui_check_box.h ..\..\..\MiniWin\ui\ui_check_box.h
mklink /h src\ui\ui\ui_keyboard.h ..\..\..\MiniWin\ui\ui_keyboard.h
mklink /h src\ui\ui\ui_keypad.h ..\..\..\MiniWin\ui\ui_keypad.h
mklink /h src\ui\ui\ui_label.h ..\..\..\MiniWin\ui\ui_label.h
mklink /h src\ui\ui\ui_list_box.h ..\..\..\MiniWin\ui\ui_list_box.h
mklink /h src\ui\ui\ui_progress_bar.h ..\..\..\MiniWin\ui\ui_progress_bar.h
mklink /h src\ui\ui\ui_radio_button.h ..\..\..\MiniWin\ui\ui_radio_button.h
mklink /h src\ui\ui\ui_scroll_bar_horiz.h ..\..\..\MiniWin\ui\ui_scroll_bar_horiz.h
mklink /h src\ui\ui\ui_scroll_bar_vert.h ..\..\..\MiniWin\ui\ui_scroll_bar_vert.h
mklink /h src\ui\ui\ui_tabs.h ..\..\..\MiniWin\ui\ui_tabs.h
mklink /h src\ui\ui\ui_text_box.h ..\..\..\MiniWin\ui\ui_text_box.h
mklink /h src\ui\ui\ui_tree.h ..\..\..\MiniWin\ui\ui_tree.h
mklink /h src\ui\ui\miniwin_tree_container.h ..\..\..\MiniWin\miniwin_tree_container.h
mklink /h src\ui\ui\miniwin.h ..\..\..\MiniWin\miniwin.h
mklink /h src\dialogs\dialog_common.h ..\..\..\MiniWin\dialogs\dialog_common.h
mklink /h src\dialogs\dialogs\dialog_colour_chooser.h ..\..\..\MiniWin\dialogs\dialog_colour_chooser.h
mklink /h src\dialogs\dialogs\dialog_date_chooser.h ..\..\..\MiniWin\dialogs\dialog_date_chooser.h
mklink /h src\dialogs\dialogs\dialog_file_chooser.h ..\..\..\MiniWin\dialogs\dialog_file_chooser.h
mklink /h src\dialogs\dialogs\dialog_number_entry.h ..\..\..\MiniWin\dialogs\dialog_number_entry.h
mklink /h src\dialogs\dialogs\dialog_one_button.h ..\..\..\MiniWin\dialogs\dialog_one_button.h
mklink /h src\dialogs\dialogs\dialog_text_entry.h ..\..\..\MiniWin\dialogs\dialog_text_entry.h
mklink /h src\dialogs\dialogs\dialog_time_chooser.h ..\..\..\MiniWin\dialogs\dialog_time_chooser.h
mklink /h src\dialogs\dialogs\dialog_two_button.h ..\..\..\MiniWin\dialogs\dialog_two_button.h
mklink /h src\miniwin_message_queue.h ..\..\..\MiniWin\miniwin_message_queue.h

REM UI
mklink /h src\ui\ui_arrow.c ..\..\..\MiniWin\ui\ui_arrow.c
mklink /h src\ui\ui_button.c ..\..\..\MiniWin\ui\ui_button.c
mklink /h src\ui\ui_check_box.c ..\..\..\MiniWin\ui\ui_check_box.c
mklink /h src\ui\ui_common.c ..\..\..\MiniWin\ui\ui_common.c
mklink /h src\ui\ui_keyboard.c ..\..\..\MiniWin\ui\ui_keyboard.c
mklink /h src\ui\ui_keypad.c ..\..\..\MiniWin\ui\ui_keypad.c
mklink /h src\ui\ui_label.c ..\..\..\MiniWin\ui\ui_label.c
mklink /h src\ui\ui_list_box.c ..\..\..\MiniWin\ui\ui_list_box.c
mklink /h src\ui\ui_progress_bar.c ..\..\..\MiniWin\ui\ui_progress_bar.c
mklink /h src\ui\ui_radio_button.c ..\..\..\MiniWin\ui\ui_radio_button.c
mklink /h src\ui\ui_scroll_bar_horiz.c ..\..\..\MiniWin\ui\ui_scroll_bar_horiz.c
mklink /h src\ui\ui_scroll_bar_vert.c ..\..\..\MiniWin\ui\ui_scroll_bar_vert.c
mklink /h src\ui\ui_tabs.c ..\..\..\MiniWin\ui\ui_tabs.c
mklink /h src\ui\ui_text_box.c ..\..\..\MiniWin\ui\ui_text_box.c
mklink /h src\ui\ui_tree.c ..\..\..\MiniWin\ui\ui_tree.c
mklink /h src\ui\miniwin.h ..\..\..\MiniWin\miniwin.h
mklink /h src\ui\miniwin_config.h ..\..\..\MiniWinFreeRTOS_Common\miniwin_config.h
mklink /h src\ui\miniwin_debug.h ..\..\..\MiniWin\miniwin_debug.h
mklink /h src\ui\miniwin_settings.h ..\..\..\MiniWin\miniwin_settings.h
mklink /h src\ui\gl\miniwin_utilities.h ..\..\..\MiniWin\miniwin_utilities.h
mklink /h src\ui\calibrate.h ..\..\..\MiniWin\calibrate.h
mklink /h src\ui\gl\gl.h ..\..\..\MiniWin\gl\gl.h
mklink /h src\ui\gl\hal\hal_lcd.h ..\..\..\MiniWin\hal\hal_lcd.h
mklink /h src\ui\gl\gl\fonts\bitmapped\fonts.h ..\..\..\MiniWin\gl\fonts\bitmapped\fonts.h
mklink /h src\ui\bitmaps\mw_bitmaps.h ..\..\..\MiniWin\bitmaps\mw_bitmaps.h
mklink /h src\ui\miniwin_utilities.h ..\..\..\MiniWin\miniwin_utilities.h
mklink /h src\ui\hal\hal_timer.h ..\..\..\MiniWin\hal\hal_timer.h
mklink /h src\ui\ui\ui_common.h ..\..\..\MiniWin\ui\ui_common.h
mklink /h src\ui\ui\ui\ui_arrow.h ..\..\..\MiniWin\ui\ui_arrow.h
mklink /h src\ui\ui\ui\ui_button.h ..\..\..\MiniWin\ui\ui_button.h
mklink /h src\ui\ui\ui\ui_check_box.h ..\..\..\MiniWin\ui\ui_check_box.h
mklink /h src\ui\ui\ui\ui_keyboard.h ..\..\..\MiniWin\ui\ui_keyboard.h
mklink /h src\ui\ui\ui\ui_keypad.h ..\..\..\MiniWin\ui\ui_keypad.h
mklink /h src\ui\ui\ui\ui_label.h ..\..\..\MiniWin\ui\ui_label.h
mklink /h src\ui\ui\ui\ui_list_box.h ..\..\..\MiniWin\ui\ui_list_box.h
mklink /h src\ui\ui\ui\ui_progress_bar.h ..\..\..\MiniWin\ui\ui_progress_bar.h
mklink /h src\ui\ui\ui\ui_radio_button.h ..\..\..\MiniWin\ui\ui_radio_button.h
mklink /h src\ui\ui\ui\ui_scroll_bar_horiz.h ..\..\..\MiniWin\ui\ui_scroll_bar_horiz.h
mklink /h src\ui\ui\ui\ui_scroll_bar_vert.h ..\..\..\MiniWin\ui\ui_scroll_bar_vert.h
mklink /h src\ui\ui\ui\ui_tabs.h ..\..\..\MiniWin\ui\ui_tabs.h
mklink /h src\ui\ui\ui\ui_text_box.h ..\..\..\MiniWin\ui\ui_text_box.h
mklink /h src\ui\ui\ui\ui_tree.h ..\..\..\MiniWin\ui\ui_tree.h
mklink /h src\ui\ui\ui\miniwin_tree_container.h ..\..\..\MiniWin\miniwin_tree_container.h
mklink /h src\ui\ui\ui\miniwin.h ..\..\..\MiniWin\miniwin.h
mklink /h src\ui\dialogs\dialog_common.h ..\..\..\MiniWin\dialogs\dialog_common.h
mklink /h src\ui\dialogs\dialogs\dialog_colour_chooser.h ..\..\..\MiniWin\dialogs\dialog_colour_chooser.h
mklink /h src\ui\dialogs\dialogs\dialog_date_chooser.h ..\..\..\MiniWin\dialogs\dialog_date_chooser.h
mklink /h src\ui\dialogs\dialogs\dialog_file_chooser.h ..\..\..\MiniWin\dialogs\dialog_file_chooser.h
mklink /h src\ui\dialogs\dialogs\dialog_number_entry.h ..\..\..\MiniWin\dialogs\dialog_number_entry.h
mklink /h src\ui\dialogs\dialogs\dialog_one_button.h ..\..\..\MiniWin\dialogs\dialog_one_button.h
mklink /h src\ui\dialogs\dialogs\dialog_text_entry.h ..\..\..\MiniWin\dialogs\dialog_text_entry.h
mklink /h src\ui\dialogs\dialogs\dialog_time_chooser.h ..\..\..\MiniWin\dialogs\dialog_time_chooser.h
mklink /h src\ui\dialogs\dialogs\dialog_two_button.h ..\..\..\MiniWin\dialogs\dialog_two_button.h

REM PROJECT COMMON 
mkdir src\MiniWinFreeRTOS_Common
mkdir src\MiniWinFreeRTOS_Common\gl
mkdir src\MiniWinFreeRTOS_Common\hal
mkdir src\MiniWinFreeRTOS_Common\gl\hal
mkdir src\MiniWinFreeRTOS_Common\gl\gl\fonts\bitmapped
mkdir src\MiniWinFreeRTOS_Common\bitmaps
mkdir src\MiniWinFreeRTOS_Common\ui
mkdir src\MiniWinFreeRTOS_Common\ui\ui
mkdir src\MiniWinFreeRTOS_Common\dialogs
mkdir src\MiniWinFreeRTOS_Common\dialogs\dialogs
mklink /h src\MiniWinFreeRTOS_Common\miniwin.h ..\..\..\MiniWin\miniwin.h 
mklink /h src\MiniWinFreeRTOS_Common\miniwin_debug.h ..\..\..\MiniWin\miniwin_debug.h
mklink /h src\MiniWinFreeRTOS_Common\miniwin_settings.h ..\..\..\MiniWin\miniwin_settings.h
mklink /h src\MiniWinFreeRTOS_Common\gl\miniwin_utilities.h ..\..\..\MiniWin\miniwin_utilities.h
mklink /h src\MiniWinFreeRTOS_Common\calibrate.h ..\..\..\MiniWin\calibrate.h
mklink /h src\MiniWinFreeRTOS_Common\gl\gl.h ..\..\..\MiniWin\gl\gl.h
mklink /h src\MiniWinFreeRTOS_Common\miniwin_config.h ..\..\..\MiniWinFreeRTOS_Common\miniwin_config.h
mklink /h src\MiniWinFreeRTOS_Common\gl\hal\hal_lcd.h ..\..\..\MiniWin\hal\hal_lcd.h
mklink /h src\MiniWinFreeRTOS_Common\gl\gl\fonts\bitmapped\fonts.h ..\..\..\MiniWin\gl\fonts\bitmapped\fonts.h
mklink /h src\MiniWinFreeRTOS_Common\bitmaps\mw_bitmaps.h ..\..\..\MiniWin\bitmaps\mw_bitmaps.h
mklink /h src\MiniWinFreeRTOS_Common\miniwin_utilities.h ..\..\..\MiniWin\miniwin_utilities.h
mklink /h src\MiniWinFreeRTOS_Common\hal\hal_timer.h ..\..\..\MiniWin\hal\hal_timer.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui_common.h ..\..\..\MiniWin\ui\ui_common.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui\ui_arrow.h ..\..\..\MiniWin\ui\ui_arrow.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui\ui_button.h ..\..\..\MiniWin\ui\ui_button.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui\ui_check_box.h ..\..\..\MiniWin\ui\ui_check_box.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui\ui_keyboard.h ..\..\..\MiniWin\ui\ui_keyboard.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui\ui_keypad.h ..\..\..\MiniWin\ui\ui_keypad.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui\ui_label.h ..\..\..\MiniWin\ui\ui_label.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui\ui_list_box.h ..\..\..\MiniWin\ui\ui_list_box.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui\ui_progress_bar.h ..\..\..\MiniWin\ui\ui_progress_bar.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui\ui_radio_button.h ..\..\..\MiniWin\ui\ui_radio_button.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui\ui_scroll_bar_horiz.h ..\..\..\MiniWin\ui\ui_scroll_bar_horiz.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui\ui_scroll_bar_vert.h ..\..\..\MiniWin\ui\ui_scroll_bar_vert.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui\ui_tabs.h ..\..\..\MiniWin\ui\ui_tabs.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui\ui_text_box.h ..\..\..\MiniWin\ui\ui_text_box.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui\ui_tree.h ..\..\..\MiniWin\ui\ui_tree.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui\miniwin_tree_container.h ..\..\..\MiniWin\miniwin_tree_container.h
mklink /h src\MiniWinFreeRTOS_Common\ui\ui\miniwin.h ..\..\..\MiniWin\miniwin.h
mklink /h src\MiniWinFreeRTOS_Common\dialogs\dialog_common.h ..\..\..\MiniWin\dialogs\dialog_common.h
mklink /h src\MiniWinFreeRTOS_Common\dialogs\dialogs\dialog_colour_chooser.h ..\..\..\MiniWin\dialogs\dialog_colour_chooser.h
mklink /h src\MiniWinFreeRTOS_Common\dialogs\dialogs\dialog_date_chooser.h ..\..\..\MiniWin\dialogs\dialog_date_chooser.h
mklink /h src\MiniWinFreeRTOS_Common\dialogs\dialogs\dialog_file_chooser.h ..\..\..\MiniWin\dialogs\dialog_file_chooser.h
mklink /h src\MiniWinFreeRTOS_Common\dialogs\dialogs\dialog_number_entry.h ..\..\..\MiniWin\dialogs\dialog_number_entry.h
mklink /h src\MiniWinFreeRTOS_Common\dialogs\dialogs\dialog_one_button.h ..\..\..\MiniWin\dialogs\dialog_one_button.h
mklink /h src\MiniWinFreeRTOS_Common\dialogs\dialogs\dialog_text_entry.h ..\..\..\MiniWin\dialogs\dialog_text_entry.h
mklink /h src\MiniWinFreeRTOS_Common\dialogs\dialogs\dialog_time_chooser.h ..\..\..\MiniWin\dialogs\dialog_time_chooser.h
mklink /h src\MiniWinFreeRTOS_Common\dialogs\dialogs\dialog_two_button.h ..\..\..\MiniWin\dialogs\dialog_two_button.h
mklink /h src\MiniWinFreeRTOS_Common\dialogs\dialogs\miniwin.h ..\..\..\MiniWin\miniwin.h
mklink /h src\MiniWinFreeRTOS_Common\app.h app\app.h
mklink /h src\app.h app\app.h
mklink /h src\MiniWinFreeRTOS_Common\app.c app\app.c

REM PROJECT SOURCE/HEADER FILES
mklink /h src\MiniWinFreeRTOS_Common\miniwin_user.c ..\..\..\MiniWinFreeRTOS_Common\miniwin_user.c 
mklink /h src\MiniWinFreeRTOS_Common\miniwin_user.h ..\..\..\MiniWinFreeRTOS_Common\miniwin_user.h
mklink /h src\MiniWinFreeRTOS_Common\main.h app\main.h
mklink /h src\MiniWinFreeRTOS_Common\gyro_util.c ..\..\..\MiniWinFreeRTOS_Common\gyro_util.c 
mklink /h src\MiniWinFreeRTOS_Common\gyro_util.h ..\..\..\MiniWinFreeRTOS_Common\gyro_util.h 
mklink /h src\MiniWinFreeRTOS_Common\window_gyro_x.c ..\..\..\MiniWinFreeRTOS_Common\window_gyro_x.c 
mklink /h src\MiniWinFreeRTOS_Common\window_gyro_x.h ..\..\..\MiniWinFreeRTOS_Common\window_gyro_x.h 
mklink /h src\MiniWinFreeRTOS_Common\window_gyro_y.c ..\..\..\MiniWinFreeRTOS_Common\window_gyro_y.c 
mklink /h src\MiniWinFreeRTOS_Common\window_gyro_y.h ..\..\..\MiniWinFreeRTOS_Common\window_gyro_y.h 
mklink /h src\MiniWinFreeRTOS_Common\window_gyro_z.c ..\..\..\MiniWinFreeRTOS_Common\window_gyro_z.c 
mklink /h src\MiniWinFreeRTOS_Common\window_gyro_z.h ..\..\..\MiniWinFreeRTOS_Common\window_gyro_z.h 
