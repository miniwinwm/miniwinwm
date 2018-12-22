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

#ifndef _MINWIN_H
#define _MINWIN_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include <stdint.h>
#include <stdbool.h>
#include "miniwin_config.h"
#include "miniwin_debug.h"
#include "miniwin_settings.h"
#include "gl/gl.h"

/****************
*** CONSTANTS ***
****************/

/**
 * System define constants, changing may break things!
 */
#define MW_BORDER_WIDTH 							1               					/**< Width of a window border */
#define MW_TITLE_BAR_HEIGHT 						(MW_GL_TITLE_FONT_HEIGHT + 2)       /**< Height of a window's title bar which must be greater than MW_LARGE_CHARACTER_HEIGHT */
#define MW_TITLE_X_OFFSET							18									/**< Title text x offset in title bar of normal window */
#define MW_MODAL_TITLE_X_OFFSET						2									/**< Title text x offset in title bar of modal window */
#define MW_TITLE_Y_OFFSET							2									/**< Title text y offset in title bar */
#define MW_USER_MESSAGE_BASE						50      							/**< User messages can be defined from this base value upwards */
#define MW_ROOT_Z_ORDER 							0       							/**< Root z order is always the lowest */
#define MW_MIN_Z_ORDER 								1       							/**< Lowest window z order */
#define MW_MAX_Z_ORDER 								0xff    							/**< The highest possible value of z order */
#define MW_ROOT_WINDOW_ID 							0       							/**< This window always exists and is created on initialisation */
#define MW_ROOT_WINDOW_HANDLE						1       							/**< This window always has this handle and is set on initialisation */
#define MW_FIRST_USER_WINDOW_ID 					(MW_ROOT_WINDOW_ID + 1)      		/**< User window identifiers are from this value upwards */
#define MW_TITLE_BAR_ICON_SIZE						14									/**< Size of icons, which are square */
#define MW_TITLE_BAR_ICON_OFFSET					16									/**< Distance between each title bar icon */
#define MW_DESKTOP_ICONS_PER_ROW					4           						/**< Number of icons of minimized windows to show across bottom of screen */
#define MW_DESKTOP_ICON_WIDTH						(MW_HAL_LCD_WIDTH / MW_DESKTOP_ICONS_PER_ROW)	/**< Number of icons across desktop */
#define MW_DESKTOP_ICON_HEIGHT						18									/**< Height of desktop minimised icons */
#define MW_UNUSED_MESSAGE_PARAMETER					0									/**< To indicate that a parameter to post message is unused rather than zero */
#define MW_ALL_ITEMS_ENABLED						0xffff								/**< All items in a control that can have individual items enabled are enabled */
#define MW_ALL_ITEMS_DISABLED						0									/**< All items in a control that can have individual items enabled are disabled */
#define MW_SCROLL_BAR_NARROW_DIMENSION				12									/**< Width of vertical scroll bar, height of horizontal */
#define MW_SCROLL_BAR_SLIDER_SIZE					MW_SCROLL_BAR_NARROW_DIMENSION      /**< Length of scroll bar slider */
#define MW_SCROLL_BAR_LARGE_NARROW_DIMENSION		24									/**< Width of large vertical scroll bar, height of large horizontal */
#define MW_SCROLL_BAR_LARGE_SLIDER_SIZE				MW_SCROLL_BAR_LARGE_NARROW_DIMENSION/**< Length of large scroll bar slider */
#define MW_MENU_BAR_HEIGHT							14									/**< Standard menu bar height */
#define MW_LARGE_MENU_BAR_HEIGHT					20									/**< Large menu bar height */
#define MW_MENU_BAR_LABEL_Y_OFFSET					3               					/**< Gap between top edge of menu bar and text */
#define MW_INVALID_HANDLE							0									/**< Invalid handle, returned when a resource cannot be allocated */

 /**
 * Window option and state flags
 */
#define MW_WINDOW_FLAG_HAS_BORDER					0x00000001	/**< Indicates that a window is to be drawn with a border */
#define MW_WINDOW_FLAG_HAS_TITLE_BAR				0x00000002	/**< Indicates that a window is to be drawn with a title bar */
#define MW_WINDOW_FLAG_CAN_BE_CLOSED				0x00000004	/**< Indicates that a window can be closed */
#define MW_WINDOW_FLAG_IS_VISIBLE					0x00000008	/**< Indicates that a window is visible */
#define MW_WINDOW_FLAG_IS_MINIMISED					0x00000010	/**< Indicates that a window is minimised */
#define MW_WINDOW_FLAG_IS_USED						0x00000020	/**< Indicates that a window is used */
#define MW_WINDOW_FLAG_IS_MODAL						0x00000040	/**< Indicates that a window is currently modal */
#define MW_WINDOW_FLAG_HAS_VERT_SCROLL_BAR			0x00000080  /**< Indicates that a window has a vertical scroll bar */
#define MW_WINDOW_FLAG_HAS_HORIZ_SCROLL_BAR			0x00000100  /**< Indicates that a window has a horizontal scroll bar */
#define MW_WINDOW_FLAG_HAS_MENU_BAR					0x00000200  /**< Indicates that a window has a menu bar */
#define MW_WINDOW_FLAG_MENU_BAR_ENABLED				0x00000400	/**< Indicates that a menu bar, if existing, is enabled */
#define MW_WINDOW_FLAG_MENU_BAR_ITEM_IS_SELECTED	0x00000800 	/**< Indicates that a menu bar, if existing, has an item selected */
#define MW_WINDOW_FLAG_VERT_SCROLL_BAR_ENABLED		0x00001000	/**< Indicates that a vertical scroll bar, if existing, is enabled */
#define MW_WINDOW_FLAG_HORIZ_SCROLL_BAR_ENABLED		0x00002000	/**< Indicates that a horizontal scroll bar, if existing, is enabled */
#define MW_WINDOW_FLAG_TOUCH_FOCUS_AND_EVENT		0x00004000	/**< Indicates that a touch in a non-focused window gives it focus and generates a touch down event */
#define MW_WINDOW_FLAG_LARGE_SIZE					0x00008000	/**< Indicates that a window's menu bar and scroll bars are to be drawn large sized */

/**
 * Control option and state flags
 */
#define MW_CONTROL_FLAG_IS_VISIBLE					0x0001		/**< Indicates that a control is visible */
#define MW_CONTROL_FLAG_IS_ENABLED					0x0002		/**< Indicates that a control is enabled */
#define MW_CONTROL_FLAG_IS_USED						0x0004 		/**< Indicates that a control is used */
#define MW_CONTROL_FLAG_LARGE_SIZE					0x0008		/**< Indicates that a control is to be drawn large size */

/**
 * Bitfields representing window frame components required to be redrawm
 */
#define MW_WINDOW_FRAME_COMPONENT_TITLE_BAR			0x01		/**< Title bar window frame components */
#define MW_WINDOW_FRAME_COMPONENT_BORDER			0x02		/**< Border window frame components */
#define MW_WINDOW_FRAME_COMPONENT_MENU_BAR			0x04		/**< Menu bar window frame components */
#define MW_WINDOW_FRAME_COMPONENT_VERT_SCROLL_BAR	0x08		/**< Vertical scroll bar window frame components */
#define MW_WINDOW_FRAME_COMPONENT_HORIZ_SCROLL_BAR	0x10		/**< Horizontal scroll bar window frame components */
#define MW_WINDOW_FRAME_COMPONENT_ALL (MW_WINDOW_FRAME_COMPONENT_TITLE_BAR | \
										MW_WINDOW_FRAME_COMPONENT_BORDER | \
										MW_WINDOW_FRAME_COMPONENT_MENU_BAR | \
										MW_WINDOW_FRAME_COMPONENT_VERT_SCROLL_BAR | \
										MW_WINDOW_FRAME_COMPONENT_HORIZ_SCROLL_BAR)		/**< All window frame components */

/************
*** TYPES ***
************/

/**
 * System defined window manager messages
 */
typedef enum
{
	/****************************************
	*										*
	* Messages posted by the window manager *
	* 										*
	****************************************/

	/**
	 * Message send to window as soon as it is created and before it is painted
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_WINDOW_CREATED_MESSAGE,

	/**
	 * Message sent to window just before it is removed
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_WINDOW_REMOVED_MESSAGE,

	/**
	 * Message sent to a window when it gains focus
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_WINDOW_GAINED_FOCUS_MESSAGE,

	/**
	 * Message sent to a window when it loses focus
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_WINDOW_LOST_FOCUS_MESSAGE,

	/**
	 * Message to a window when it has been resized
	 *
	 * message_data: Upper 16 bits = window new width, lower 16 bits = window new height
	 * message_pointer: Unused
	 */
	MW_WINDOW_RESIZED_MESSAGE,

	/**
	 * Message to a window when it has been moved
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_WINDOW_MOVED_MESSAGE,

	/**
	 * Message to a window when it has been minimised
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_WINDOW_MINIMISED_MESSAGE,

	/**
	 * Message to a window when it has been restored
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_WINDOW_RESTORED_MESSAGE,

	/**
	 * Message to a window when its visibility has changed
	 *
	 * message_data: true if made visible, false if made invisible
	 * message_pointer: Unused
	 */
	MW_WINDOW_VISIBILITY_CHANGED_MESSAGE,

	/**
	 * Message to a window when a window vertical scroll bar has been scrolled
	 *
	 * message_data: new vertical scroll position 0 - UINT8_MAX as a proportion of scroll bar length
	 * message_pointer: Unused
	 */
	MW_WINDOW_VERT_SCROLL_BAR_SCROLLED_MESSAGE,

	/**
	 * Message to a window when a window horizontal scroll bar has been scrolled
	 *
	 * message_data: new horizontal scroll position 0 - UINT8_MAX as a proportion of scroll bar length
	 * message_pointer: Unused
	 */
	MW_WINDOW_HORIZ_SCROLL_BAR_SCROLLED_MESSAGE,

	/**
	 * Message send to control as soon as it is created and before it is painted
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_CONTROL_CREATED_MESSAGE,

	/**
	 * Message sent to control just before it is removed
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_CONTROL_REMOVED_MESSAGE,

	/**
	 * Message sent to all controls in a window when parent window gains focus or control made visible
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_CONTROL_GAINED_FOCUS_MESSAGE,

	/**
	 * Message to a control when its visibility has changed
	 *
	 * message_data: true if made visible, false if made invisible
	 * message_pointer: Unused
	 */
	MW_CONTROL_VISIBILITY_CHANGED_MESSAGE,

	/**
	 * Message sent to all controls in a window when parent window loses focus or control made invisible
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_CONTROL_LOST_FOCUS_MESSAGE,

	/**
	 * Message sent to a window or control when it receives a touch down event
	 *
	 * message_data: Upper 16 bits = x coordinate, lower 16 bits = y coordinate
	 * message_pointer: Unused
	 */
	MW_TOUCH_DOWN_MESSAGE,

	/**
	 * Message sent to a window or control when it receives a touch hold down event
	 *
	 * message_data: Upper 16 bits = x coordinate, lower 16 bits = y coordinate
	 * message_pointer: Unused
	 */
	MW_TOUCH_HOLD_DOWN_MESSAGE,

	/**
	 * Message sent to a window or control when it receives a touch up event
	 *
	 * message_data: The handle of the original window or control where the touch down occurred
	 * message_pointer: Unused
	 */
	MW_TOUCH_UP_MESSAGE,

	/**
	 * Message sent to a window or control when it receives a drag event
	 *
	 * message_data: Upper 16 bits = x coordinate, lower 16 bits = y coordinate
	 * message_pointer: Unused
	 */
	MW_TOUCH_DRAG_MESSAGE,

	/**
	 * Response message from a menu bar that an item has been pressed
	 *
	 * message_data: The menu bar item selected, zero based
	 * message_pointer: Unused
	 */
	MW_MENU_BAR_ITEM_PRESSED_MESSAGE,

	/**
	 * Message sent to a window or control when a timer has expired
	 *
	 * message_data: The handle of the timer that has just expired
	 * message_pointer: Unused
	 */
	MW_TIMER_MESSAGE,

	/********************************************************************
	*						   									        *
	* Messages posted from controls in response to user interface input *
	*																    *
	********************************************************************/

	/**
	 * Response message from a button that it has been pressed
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_BUTTON_PRESSED_MESSAGE,

	/**
	 * Response message from a check box that its state has changed
	 *
	 * message_data: true if check box checked, false if check box unchecked
	 * message_pointer: Unused
	 */
	MW_CHECKBOX_STATE_CHANGE_MESSAGE,

	/**
	 * Response message from a radio button that its state has changed
	 *
	 * message_data: The selected radio button zero based
	 * message_pointer: Unused
	 */
	MW_RADIO_BUTTON_ITEM_SELECTED_MESSAGE,

	/**
	 * Response message from a list box that an item has been pressed
	 *
	 * message_data: The selected list box line zero based
	 * message_pointer: Unused
	 */
	MW_LIST_BOX_ITEM_PRESSED_MESSAGE,

	/**
	 * Message posted by a list box to its parent window indicating if scrolling is required,
	 * i.e. too many lines to display in the box at once
	 *
	 * message_data: upper 16 bits: 1 if scrolling required, 0 if scrolling not required; lower 16 bits: the maximum lines that can be scrolled
	 * message_pointer: Unused
	 */
	MW_LIST_BOX_SCROLLING_REQUIRED_MESSAGE,

	/**
	 * Response message from a vertical control scroll bar that it has been scrolled
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_CONTROL_VERT_SCROLL_BAR_SCROLLED_MESSAGE,

	/**
	 * Response message from a horizontal control scroll bar that it has been scrolled
	 *
	 * message_data: new horizontal scroll position from 0 - UINT8_MAX as a proportion of the scroll bar
	 * message_pointer: Unused
	 */
	MW_CONTROL_HORIZ_SCROLL_BAR_SCROLLED_MESSAGE,

	/**
	 * Response message from a arrow that it has been pressed
	 *
	 * message_data: The arrow direction
	 * message_pointer: Unused
	 */
	MW_ARROW_PRESSED_MESSAGE,
	
	/**
	 * ASCII value of key pressed, can be backspace
	 *
	 * message_data: The ASCII code of the pressed key
	 * message_pointer: Unused
	 */
	MW_KEY_PRESSED_MESSAGE,

	/**
	 * Message posted by a text box to its parent window indicating if scrolling is required,
	 * i.e. too much text to display in the box at once
	 *
	 * message_data: upper 16 bits: 1 if scrolling required, 0 if scrolling not required;
	 * 				 lower 16 bits: the maximum lines that can be scrolled in pixels
	 * message_pointer: Unused
	 */
	MW_TEXT_BOX_SCROLLING_REQUIRED_MESSAGE,

	/*********************************************
	*											 *
	* Messages posted to controls from user code *
	* 											 *
	*********************************************/

	/**
	 * Set the label's text by passing a pointer to a character buffer
	 *
	 * message_data: Unused
	 * message_pointer: Pointer to the label's new text
	 */
	MW_LABEL_SET_LABEL_TEXT_MESSAGE,

	/**
	 * Set a check box's checked state
	 *
	 * message_data: true to set check box checked or false to set it unchecked
	 * message_pointer: Unused
	 */
	MW_CHECK_BOX_SET_CHECKED_STATE_MESSAGE,

	/**
	 * Set a progress bar's progress level as a percentage
	 *
	 * message_data: Percentage to set progress bar's progress from 0 - 100
	 * message_pointer: Unused
	 */
	MW_PROGRESS_BAR_SET_PROGRESS_MESSAGE,

	/**
	 * Set a scroll bar's scroll position
	 *
	 * message_data: Set a scroll bar's scroll position from 0 - UINT8_MAX
	 * message_pointer: Unused
	 */
	MW_SCROLL_BAR_SET_SCROLL_MESSAGE,

	/**
	 * Set how many lines to scroll a list box through the list box's lines
	 *
	 * message_data: Number of lines to scroll zero based
	 * message_pointer: Unused
	 */
	MW_LIST_BOX_LINES_TO_SCROLL_MESSAGE,

	/**
	 * Position of a scroll bar associated with a list box
	 *
	 * message_data: Scroll bar position, 0 - UINT8_MAX
	 * message_pointer: Unused
	 */
	MW_LIST_BOX_SCROLL_BAR_POSITION_MESSAGE,

	/**
	 * Set new entries and entry count for a list box
	 *
	 * message_data: Number of entries in new array of entries
	 * message_pointer: Pointer to array of entries
	 */
	MW_LIST_BOX_SET_ENTRIES_MESSAGE,

	/**
	 * Set a radio button's chosen button
	 *
	 * message_data: The button to set zero based
	 * message_pointer: Unused
	 */
	MW_RADIO_BUTTON_SET_SELECTED_MESSAGE,

	/**
	 * Set the scrollable text box's text by passing a pointer to a character buffer
	 *
	 * message_data: Unused
	 * message_pointer: Pointer to the scrollable text box's new text
	 */
	MW_TEXT_BOX_SET_TEXT_MESSAGE,

	/**
	 * Position of a scroll bar associated with a text box
	 *
	 * message_data: Scroll bar position, 0 - UINT8_MAX
	 * message_pointer: Unused
	 */
	MW_TEXT_BOX_SCROLL_BAR_POSITION_MESSAGE,

	/**
	 * Set how many lines to scroll a text box
	 *
	 * message_data: Number of lines to scroll in pixels
	 * message_pointer: Unused
	 */
	MW_TEXT_BOX_LINES_TO_SCROLL_MESSAGE,

	/**************************************
	*	 								  *
	* Messages posted by standard dialogs *
	* 									  *
	**************************************/

	/**
	 * One button dialog has been dismissed
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_DIALOG_ONE_BUTTON_DISMISSED_MESSAGE,

	/**
	 * Two button dialog has been dismissed
	 *
	 * message_data: 0 if left button pressed, 1 if right button pressed
	 * message_pointer: Unused
	 */
	MW_DIALOG_TWO_BUTTONS_DISMISSED_MESSAGE,

	/**
	 * Time chooser dialog has been dismissed by ok button
	 *
	 * message_data: Mask with 0x00ff for minutes, mask with 0xff00 for hours
	 * message_pointer: Unused
	 */
	MW_DIALOG_TIME_CHOOSER_OK_MESSAGE,

	/**
	 * Time chooser dialog has been dismissed by cancel button
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_DIALOG_TIME_CHOOSER_CANCEL_MESSAGE,

	/**
	 * Date chooser dialog has been dismissed by ok button
	 *
	 * message_data: Mask with 0xffff0000 for 4 digit year, mask with 0x0000ff00 for month (1-12), mask with 0x000000ff for date (1-31)
	 * message_pointer: Unused
	 */
	MW_DIALOG_DATE_CHOOSER_OK_MESSAGE,

	/**
	 * Date chooser dialog has been dismissed by cancel button
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_DIALOG_DATE_CHOOSER_CANCEL_MESSAGE,

	/**
	 * File chosen in file chooser dialog
	 *
	 * message_data: Unused
	 * message_pointer: Pointer to char buffer holding path and file name
	 */
	MW_DIALOG_FILE_CHOOSER_FILE_OK_MESSAGE,

	/**
	 * Folder chosen in file chooser dialog
	 *
	 * message_data: Unused
	 * message_pointer: Pointer to char buffer holding path name
	 */
	MW_DIALOG_FILE_CHOOSER_FOLDER_OK_MESSAGE,

	/**
	 * File chooser dialog was cancelled with no file chosen
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_DIALOG_FILE_CHOOSER_CANCEL_MESSAGE,

	/**
	 * Text entry dialog ok message
	 *
	 * message_data: Unused
	 * message_pointer: Pointer to char buffer holding entered text
	 */
	MW_DIALOG_TEXT_ENTRY_OK_MESSAGE,

	/**
	 * Text entry dialog cancel message
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_DIALOG_TEXT_ENTRY_CANCEL_MESSAGE,

	/**
	 * Number entry dialog ok message
	 *
	 * message_data: Unused
	 * message_pointer: Pointer to char buffer holding entered number as text including '-' if entered by user
	 */
	MW_DIALOG_NUMBER_ENTRY_OK_MESSAGE,

	/**
	 * Number entry dialog cancel message
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_DIALOG_NUMBER_ENTRY_CANCEL_MESSAGE,


	/*******************
	*                  *
	* Utility messages *
	*                  *
	*******************/

	/**
	 * System message to paint everything
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_WINDOW_PAINT_ALL_MESSAGE,

	/**
	 * System message to get a window's frame painted
	 *
	 * message_data: Combination of MW_WINDOW_FRAME_COMPONENT_TITLE_BAR, MW_WINDOW_FRAME_COMPONENT_BORDER, MW_WINDOW_FRAME_COMPONENT_MENU_BAR,
	 * 				 MW_WINDOW_FRAME_COMPONENT_VERT_SCROLL_BAR, MW_WINDOW_FRAME_COMPONENT_HORIZ_SCROLL_BAR
	 * message_pointer: Unused
	 */
	MW_WINDOW_FRAME_PAINT_MESSAGE,

	/**
	 * System message to call a window's client area paint function
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_WINDOW_CLIENT_PAINT_MESSAGE,

	/**
	 * System message to call a window's client area paint rect function
	 *
	 * message_data: Unused
	 * message_pointer: Pointer to a mw_util_rect_t structure
	 */
	MW_WINDOW_CLIENT_PAINT_RECT_MESSAGE,

	/**
	 * System message to call a control's paint function
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_CONTROL_PAINT_MESSAGE,

	/**
	 * System message to call a control's paint rect function
	 *
	 * message_data: Unused
	 * message_pointer: Pointer to a mw_util_rect_t structure
	 */
	MW_CONTROL_PAINT_RECT_MESSAGE,

	/**
	 * Message to a window when another window has been removed that is not the window receiving the message.
	 * Use this message when a window is removed as a result of user code and another window needs to know
	 *
	 * message_data: Unused
	 * message_pointer: Unused
	 */
	MW_WINDOW_EXTERNAL_WINDOW_REMOVED_MESSAGE,

	/**
	 * Message to a window for any user-defined purpose
	 *
	 * message_data: Any user meaning
	 * message_pointer: Any user meaning
	 */
	MW_USER_1_MESSAGE,

	/**
	 * Message to a window for any user-defined purpose
	 *
	 * message_data: Any user meaning
	 * message_pointer: Any user meaning
	 */
	MW_USER_2_MESSAGE,

	/**
	 * Message to a window for any user-defined purpose
	 *
	 * message_data: Any user meaning
	 * message_pointer: Any user meaning
	 */
	MW_USER_3_MESSAGE,

	/**
	 * Message to a window for any user-defined purpose
	 *
	 * message_data: Any user meaning
	 * message_pointer: Any user meaning
	 */
	MW_USER_4_MESSAGE,

	/**
	 * Message to a window for any user-defined purpose
	 *
	 * message_data: Any user meaning
	 * message_pointer: Any user meaning
	 */
	MW_USER_5_MESSAGE
} mw_message_id_t;

/**
 * Message recipient types
 */
typedef enum
{
	MW_WINDOW_MESSAGE,         		    			/**< The recipient of a message is a window, which can be the root window */
	MW_CONTROL_MESSAGE,        	    				/**< The recipient of a message is a control */
	MW_SYSTEM_MESSAGE,          					/**< The recipient of a message is the window manager */
	MW_CANCELLED_MESSAGE							/**< Message has been cancelled but not removed from queue, ignore */
} mw_message_recipient_type_t;

/**
 * Window manager handle type
 */
typedef uint32_t mw_handle_t;

/* forward declare message struct and its typedef */
struct mw_message_tag;
typedef struct mw_message_tag mw_message_t;

/**
 * Function signature definition for the paint function that every window and control must implement
 *
 * @param window_handle The window/control handle of the window/control being painted in the paint function
 * @param draw_info Draw info structure describing offset and clip region
 * @note Do not call this directly from user code
 */
typedef void (*mw_paint_func_p)(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info);

/**
 * Function signature definition for the message handling function that every window and control must implement
 *
 * @param message The message to be processed
 * @note Do not call this directly from user code
 */
typedef void (*mw_message_func_p)(const mw_message_t *user_message);

/**
 * Message queue message information structure
 */
typedef struct mw_message_tag
{
	mw_handle_t sender_handle;			/**< Handle of sender of message, not always used  */
	mw_handle_t recipient_handle;       /**< Handle of recipient of message, not always used */
	mw_message_id_t message_id;       	/**< Identifier of the message; this is a system identifier or a user defined identifier */
	mw_message_recipient_type_t message_recipient_type;        /**< Type of recipient this message is for */
	uint32_t message_data;              /**< Data value passed to recipient with a message; this is message specific and can be used for anything */
	void *message_pointer;				/**< Pointer value passed to recipient with a message; this pointer is message specific and can be used for anything */
} mw_message_t;

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * User implemented functions
 */

/**
 * This function is declared by MiniWin but is up to the user to implement.
 * All user user interface initializations like creating windows and controls
 * can be collected together here . A stubbed version is found in miniwin_user.c
 * in MiniWin/user. Remove this file from the build, copy it to your
 * application folder, and implement this function. The user never calls this
 * function; it is called by the window manager.
 *
 * @note Do not call this directly from user code
 */
void mw_user_init(void);

/**
 * This function is declared by MiniWin but is up to the user to implement. In
 * this function the user implements the painting of the root window. A stubbed
 * version is found in miniwin_user.c in MiniWin/user. Remove this file from the
 * build, copy it to your application folder, and implement this function. The
 * user never calls this function; it is called by the window manager.
 *
 * @param draw_info Draw info structure describing offset and clip region
 * @note Do not call this directly from user code
 */
void mw_user_root_paint_function(const mw_gl_draw_info_t *draw_info);

/**
 * This function is declared by MiniWin but is up to the user to implement. The
 * user can respond to messages sent to the root window here, for example a tap
 * on the root window. A stubbed version is found in miniwin_user.c in
 * MiniWin/user. Remove this file from the build, copy it to your application
 * folder, and implement this function. The user never calls this function; it
 * is called by the window manager.
 *
 * @param message The message to be processed
 * @note Do not call this directly from user code
 */
void mw_user_root_message_function(const mw_message_t *message);

/**
 * Non-user implemented functions
 */

/**
 * Initialize the window manager. This initialize all the drivers, create the
 * root window and calls wm_user_init. This function needs to be called before
 * any messages are posted or processed. This function is usually called from
 * your application's main function, or MiniWin thread first call if running in
 * a thread.
 */
void mw_init();

/**
 * Returns the state of initializtion process
 *
 * @return true when miniwin and user initializations complete else false
 */
bool mw_is_init_complete(void);

/**
 * Memory for holding window data is allocated statically at compile time.
 * Before adding a new window it may be useful to see if there are any slots
 * in the array of window data structures free.
 *
 * @return true if there are else false
 */
bool mw_find_if_any_window_slots_free(void);

/**
 * Add a new window. This can be called in mw_user_init for windows that exist
 * for the lifetime of the application or later for windows which come and go.
 * There must be space statically allocated to create the new window. Returns
 * new window reference number or MW_INVALID_HANDLE if there is an error.
 *
 * @param rect The rect of the window's total area, including border and title bar
 * @param title The window title as shown in title bar
 * @param paint_func Pointer to paint function
 * @param message_func Pointer to message handling function
 * @param menu_bar_items Pointer to array holding menu bar item text labels
 * @param menu_bar_items_count Number of entries in above array
 * @param window_flags The new window's description and state flags
 * @param instance_data Optional pointer to any extra window data that is instance specific, can be NULL if no instance data
 * @return The new window handle if created or MW_INVALID_HANDLE if it could not be created
 * @warning Do not call from within any paint function
 */
mw_handle_t mw_add_window(mw_util_rect_t *rect,
		char *title,
		mw_paint_func_p paint_func,
		mw_message_func_p message_func,
		const char **menu_bar_items,
		uint8_t menu_bar_items_count,
		uint32_t window_flags,
		void *instance_data);

/**
 * Test if a window handle is valid and represents a valid window
 *
 * @param window_handle The handle to test
 * @return true if valid else false
 */
bool mw_is_window_handle_valid(mw_handle_t window_handle);

/**
 * Bring a window to the front giving it the highest Z order of all windows.
 *
 * @param window_handle Position in array of all windows of this window
 * @note It is up to the user to issue appropriate paint messages (window frame and
 *       client area) to get the window repainted
 */
void mw_bring_window_to_front(mw_handle_t window_handle);

/**
 * Send a window to the back giving it the lowest Z order of all windows.
 *
 * @param window_handle Position in array of all windows of this window
 * @note It is up to the user to issue a paint all message to get windows repainted that
 * 		 have been exposed by sending this window to the back
 */
void mw_send_window_to_back(mw_handle_t window_handle);

/**
 *  Set a window's visibility if it is used. If set visible it is given focus and brought
 *  to the front of other showing windows.
 *
 * @param window_handle Position in array of all windows of this window
 * @param visible true or false
 * @note It is up to the user to issue the appropriate window paint messages (paint all
 *       if a window is made invisible or paint window frame and client area if made
 *       visible.
 */
void mw_set_window_visible(mw_handle_t window_handle, bool visible);

/**
 * Set a window minimised if it is used.
 *
 * @param window_handle Position in array of all windows of this window
 * @param minimised true or false
 * @note It is up to the user to issue the appropriate window paint messages (paint all
 *       if a window is mainimized or paint window frame and client area if restored
 */
void mw_set_window_minimised(mw_handle_t window_handle, bool minimised);

/**
 * Reposition a window. All contained controls' client areas updated automatically.
 *
 * @param window_handle Position in array of all windows of this window
 * @param new_x The new x position of the left edge of the window
 * @param new_y The new y position of the top edge of the window
 * @note It is up to the user to issue a paint all message
 */
void mw_reposition_window(mw_handle_t window_handle, int16_t new_x, int16_t new_y);

/**
 * Resize a window. All contained controls' client areas updated automatically.
 *
 * @param window_handle Position in array of all windows of this window
 * @param new_width The new width of the window
 * @param new_height The new height of the window
 * @return If the resize was successful
 * @note It is up to the user to issue a paint all message
 */
bool mw_resize_window(mw_handle_t window_handle, uint16_t new_width, uint16_t new_height);

/**
 * Find the window with focus. This is the visible window with the highest Z order.
 *
 * @return The window handle of the window.
 */
mw_handle_t mw_find_window_with_focus(void);

/**
 * Return if any user window is currently modal.
 *
 * @return true if any window is modal else false
 */
bool mw_is_any_window_modal(void);

/**
 * Set the specified window system modal. This means that the window cannot be switched away from and no
 * other window accepts input. The title bar icons are removed while in modal state so that the window cannot
 * be closed or minimised. If any window is currently modal this call is ignored. Call ignored for unused,
 * minimised or invisible windows. A model window has a different title bar colour set in miniwin_config.h.
 *
 * @param window_handle Position in array of all windows of this window
 * @param modal true to set modal, false to set non-modal
 * @note Some means of setting the window non-modal again must be implemented, usually a button in the
 *       window. A modal window cannot be closed from a title bar icon.
 */
void mw_set_window_modal(mw_handle_t window_handle, bool modal);

/**
 * Set a menu bar enabled or disabled for a window
 *
 * @param window_handle The window containing the menu bar
 * @param enabled The new state
 */
void mw_set_menu_bar_enabled_state(mw_handle_t window_handle, bool enabled);

/**
 * Set menu bar's individual items enabled or disabled
 *
 * @param window_handle The window containing the menu bar
 * @param item_enables Bit field containing the states, msb is first menu ar item, 1 is enabled, 0 is disabled
 * @note Maximum of 16 items in a menu bar.
 */
void mw_set_menu_bar_items_enabled_state(mw_handle_t window_handle, uint16_t item_enables);

/**
 * Set a window horizontal scroll bar enabled or disabled
 *
 * @param window_handle The window containing the scroll bar
 * @param enabled The new state
 */
void mw_set_window_horiz_scroll_bar_enabled_state(mw_handle_t window_handle, bool enabled);

/**
 * Set a window vertical scroll bar enabled or disabled
 *
 * @param window_handle The window containing the scroll bar
 * @param enabled The new state
 */
void mw_set_window_vert_scroll_bar_enabled_state(mw_handle_t window_handle, bool enabled);

/**
 * Set a window horizontal scroll bar position
 *
 * @param window_handle The window containing the scroll bar
 * @param enabled The new position
 * @note User must do a paint of the scroll bar for the change to be seen
 */
void mw_set_window_horiz_scroll_bar_position(mw_handle_t window_handle, uint8_t position);

/**
 * Set a window vertical scroll bar position
 *
 * @param window_handle The window containing the scroll bar
 * @param enabled The new position
 * @note User must do a paint of the scroll bar for the change to be seen
 */
void mw_set_window_vert_scroll_bar_position(mw_handle_t window_handle, uint8_t position);

/**
 * Add a message to the message queue to get a window frame painted. This
 * paints the borders, title bar, menu bar and scroll bars.
 *
 * @param window_handle Position in array of all windows of this window
 * @param components The constituent components of a window frame to be painted
 */
void mw_paint_window_frame(mw_handle_t window_handle, uint8_t components);

/**
 * Add a message to the message queue to get a window's client area and contained controls painted.
 * This is useful when you know that the window is at the front and has focus and the borders and title
 * bar do not need repainting.
 *
 * @param window_handle Position in array of all windows of this window
 */
void mw_paint_window_client(mw_handle_t window_handle);

/**
 * Add a message to the message queue to get a specified part of a window's client area and contained controls painted.
 * This is useful when you know that the window is at the front and has focus and the borders and title
 * bar do not need repainting.
 *
 * @param window_handle Position in array of all windows of this window
 * @param rect The area to be repainted in window client coordinates
 * @note The rect pointed to by rect must be persistent and not a local variable of the calling function
 */
void mw_paint_window_client_rect(mw_handle_t window_handle, const mw_util_rect_t *rect);

/**
 * Remove a window and all its controls if it has any.
 *
 * @param window_handle Position in array of all windows of this window
 */
void mw_remove_window(mw_handle_t window_handle);

/**
 * Get a window's client area rect
 *
 * @param window_handle The window to get the rect for
 * @return The returned rect
 */
mw_util_rect_t mw_get_window_client_rect(mw_handle_t window_handle);

/**
 * Get a window's instance_data data pointer
 *
 * @param window_handle The window to get the instance data pointer for
 * @return The returned instance_data data pointer
 */
void *mw_get_window_instance_data(mw_handle_t window_handle);

/**
 * Get a window's flags bitfield
 *
 * @param window_handle Handle of the window to get flags bitfield for.
 * @return The returned flags bitfield
 */
uint16_t mw_get_window_flags(mw_handle_t window_handle);

/**
 * Set the window's title bar text
 *
 * @param window_handle The window to set the title bar text for
 * @param title_text The new title bar text
 */
void wm_set_window_title(mw_handle_t window_handle, char *title_text);

/**
 * Find if there are any free control slots in array of controls
 *
 * @return true if there are else false
 */
bool mw_find_if_any_control_slots_free(void);

/**
 * Add a new control to a window. Returns new control reference number or MAX_WINDOW_COUNT if there is an error.
 *
 * @param rect The rect of the control's area
 * @param parent_handle The window handle of the control's parent window
 * @param paint_func Pointer to paint function
 * @param message_func Pointer to message handling function
 * @param control_flags Flags describing the control and its state
 * @param instance_data void Pointer to control specific data structure containing extra control specific configuration data for this instance
 * @return The new control handle if created or MW_INVALID_HANDLE if it could not be created
 */
mw_handle_t mw_add_control(mw_util_rect_t *rect,
		mw_handle_t parent_handle,
		mw_paint_func_p paint_func,
		mw_message_func_p message_func,
		uint16_t control_flags,
		void *instance_data);

/**
 * Test if a control handle is valid and represents a valid control
 *
 * @param control_handle The handle to test
 * @return true if valid else false
 */
bool mw_is_control_handle_valid(mw_handle_t control_handle);

/**
 * Set a control visible if it is used
 *
 * @param control_handle Handle of this control.
 * @param visible true or false
 */
void mw_set_control_visible(mw_handle_t control_handle, bool visible);

/**
 * Set a control enabled if it is used
 *
 * @param control_handle Handle of this control.
 * @param enabled true or false
 */
void mw_set_control_enabled(mw_handle_t control_handle, bool enabled);

/**
 * Add a message to the message queue to get a control painted.
 *
 * @param control_handle Handle of this control.
 */
void mw_paint_control(mw_handle_t control_handle);

/**
 * Add a message to the message queue to get a specified part of a control's client area painted.
 *
 * @param control_handle Handle of this control.
 * @param rect The area to be repainted in control client coordinates
 * @note The rect pointed to by rect must be persistent and not a local variable of the calling function
 */
void mw_paint_control_rect(mw_handle_t control_handle, const mw_util_rect_t *rect);

/**
 * Remove a control.
 *
 * @param control_handle Handle of this control.
 */
void mw_remove_control(mw_handle_t control_handle);

/**
 * Get a control's rect
 *
 * @param control_handle Handle of the control to get rect for.
 * @return The returned rect
 */
mw_util_rect_t mw_get_control_rect(mw_handle_t control_handle);

/**
 * Get a control's parent window handle
 *
 * @param control_handle Handle of the control to get parent of.
 * @return The returned parent's window handle
 */
mw_handle_t mw_get_control_parent_window_handle(mw_handle_t control_handle);

/**
 * Get a control's instance_data data pointer
 *
 * @param control_handle Handle of the control to get instance data for.
 * @return The returned instance_data data pointer
 */
void *mw_get_control_instance_data(mw_handle_t control_handle);

/**
 * Get a control's flags bitfield
 *
 * @param control_handle Handle of the control to get flags bitfield for.
 * @return The returned flags bitfield
 */
uint16_t mw_get_control_flags(mw_handle_t control_handle);

/**
 * Find if there are any free control slots in array of controls
 *
 * @return true if there are else false
 */
bool mw_find_if_any_control_slots_free(void);

/**
 * Set a timer if there is space for it in the array of timers.
 *
 * @param fire_time The time in window manager ticks for the timer to timeout; this is an absolute time, not relative
 * @param recipient_handle The handle of the recipient window or control
 * @param recipient_type If the recipient is a window or a conreol
 * @return The new handle if the timer could be set or MW_INVALID_HANDLE if it could not be set
 */
mw_handle_t mw_set_timer(uint32_t fire_time, mw_handle_t recipient_handle, mw_message_recipient_type_t recipient_type);

/**
 * Cancel a previously set timer.
 *
 * @param timer_handle The handle of the timer to cancel as returned by set_timer
 */
void mw_cancel_timer(mw_handle_t timer_handle);

/**
 * Package up the filling in and sending of a windows message.
 *
 * The message is added to the window manager message queue and will be processed by the recipient
 * asynchronously.
 *
 * @param message_id The message id of the message to create
 * @param sender_handle The message hadle of the sender
 * @param recipient_handle The recipient handle for the message
 * @param message_data 32 bit field of general purpose data
 * @param message_pointer Pointer field to a general purpose pointer
 * @param recipient_type Recipient type of message, window, control or system
 */
void mw_post_message(uint8_t message_id,
		mw_handle_t sender_handle,
		mw_handle_t recipient_handle,
		uint32_t message_data,
		void *message_pointer,
		mw_message_recipient_type_t recipient_type);

/**
 * Process the next message in the message queue. This function must be called frequently to enable user interface responsiveness.
 *
 * @return If a message was available and was processed return true else return false if no messages were waiting
 */
bool mw_process_message(void);

/**
 * Paint everything.
 */
void mw_paint_all();

/**
 * Show a busy string as defined in minwin_user.h when a long process is locking the user interface
 *
 * @param show true to show message, false to stop showing it
 */
void mw_show_busy(bool show);

#include "ui/ui_common.h"
#include "dialogs/dialog_common.h"

#ifdef __cplusplus
}
#endif

#endif
