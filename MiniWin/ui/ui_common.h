/*

MIT License

Copyright (c) John Blaiklock 2018 miniwin Embedded Window Manager

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef UI_COMMON_H
#define UI_COMMON_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include <stdint.h>
#include "ui/ui_button.h"
#include "ui/ui_check_box.h"
#include "ui/ui_radio_button.h"
#include "ui/ui_list_box.h"
#include "ui/ui_label.h"
#include "ui/ui_scroll_bar_vert.h"
#include "ui/ui_scroll_bar_horiz.h"
#include "ui/ui_int_number_chooser.h"
#include "ui/ui_progress_bar.h"
#include "ui/ui_keyboard.h"
#include "ui/ui_arrow.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/
/**
 * Post a number value to a control in a message.
 *
 * @param control_id The id of the control
 * @param number The number
 */
void mw_ui_common_post_number_to_control(uint8_t control_id, uint32_t number);

/**
 * Post a pointer value to a control in a message.
 *
 * @param control_id The id of the control
 * @param pointer The pointer
 */
void mw_ui_common_post_pointer_to_control(uint8_t control_id, void *pointer);

/**
 * Scale a scroll bar touch point from the full width as it appears on the screen
 * to a width excluding half a scroll bar slider width at either end.
 * This means that the scroll bar position is taken as the centre of the slider as
 * it slides along the bar and not the edge of the slider. When the slider as at an
 * end of its bar a touch point between the centre of the slider and the nearest bar end
 * is adjusted to be the centre of the slider. This eases he user pushing the slider right
 * all the way to either end of the bar. The result is still given within a range of 0 to the
 * screen length of the scroll bar.
 *
 * @param scroll_bar_length Length of the scroll bar as drawn on screen
 * @param touch_point Touch position within the scroll bar as draw on screen
 * @return The scaled scroll bar position, ranging from 0 for left end, scroll_bar_length for roght end
 */
uint16_t mw_ui_common_scale_scroll_bar_touch_point(uint16_t scroll_bar_length, int16_t touch_point);

#ifdef __cplusplus
}
#endif

#endif
