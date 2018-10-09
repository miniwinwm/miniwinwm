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
#include "user/minwin_config.h"
#include <miniwin_debug.h>
#include "gl/gl.h"

/****************
*** CONSTANTS ***
****************/

/**
 * System define constants that must not be changed 
 */
#define MW_BORDER_WIDTH 						1               					/**< Width of a window border */
#define MW_TITLE_BAR_HEIGHT 					(MW_GL_LARGE_CHARACTER_HEIGHT + 2)  /**< Height of a window's title bar which should be greater than MW_LARGE_CHARACTER_HEIGHT */
#define MW_TITLE_X_OFFSET						18									/**< Title text x offset in title bar */
#define MW_TITLE_Y_OFFSET						2									/**< Title text y offset in title bar */
#define MW_USER_MESSAGE_BASE					50      							/**< User messages can be defined from this base value upwards */
#define MW_ROOT_Z_ORDER 						0       							/**< Root z order is always the lowest */
#define MW_MIN_Z_ORDER 							1       							/**< Lowest window z order */
#define MW_MAX_Z_ORDER 							0xff    							/**< The highest possible value of z order */
#define MW_ROOT_WINDOW_ID 						0       							/**< This window always exists and is created on initialisation */
#define MW_FIRST_USER_WINDOW_ID 				(MW_ROOT_WINDOW_ID + 1)      		/**< User window identifiers are from this value upwards */
#define MW_TITLE_BAR_ICON_SIZE					14									/**< Size of icons, which are square */
#define MW_TITLE_BAR_ICON_OFFSET				16									/**< Distance between each title bar icon */
#define MW_DESKTOP_ICONS_PER_ROW				4           						/**< Number of icons of minimized windows to show across bottom of screen */
#define MW_DESKTOP_ICON_WIDTH					(MW_HAL_LCD_WIDTH / MW_DESKTOP_ICONS_PER_ROW)	/**< Number of icons across desktop */
#define MW_DESKTOP_ICON_HEIGHT					(MW_GL_STANDARD_CHARACTER_HEIGHT + 8)			/**< Height of desktop minimised icons */
#define MW_UNUSED_MESSAGE_PARAMETER				0									/**< To indicate that a parameter to post message is unused rather than zero */
#define MW_ALL_ITEMS_ENABLED					0xffff								/**< All items in a control that can have individual items enabled are enabled */
#define MW_ALL_ITEMS_DISABLED					0									/**< All items in a control that can have individual items enabled are disabled */
#define MW_SCROLL_BAR_NARROW_DIMESION			12									/**< Width of vertical scroll bar, height of horizontal */
#define MW_SCROLL_BAR_SLIDER_SIZE				MW_SCROLL_BAR_NARROW_DIMESION       /**< Length of scroll bar slider */
#define MW_SCROLL_BAR_LARGE_NARROW_DIMESION		24									/**< Width of large vertical scroll bar, height of large horizontal */
#define MW_SCROLL_BAR_LARGE_SLIDER_SIZE			MW_SCROLL_BAR_LARGE_NARROW_DIMESION /**< Length of large scroll bar slider */
#define MW_MENU_BAR_HEIGHT						14									/**< Menu bar height */
#define MW_MENU_BAR_LABEL_Y_OFFSET				3               					/**< Gap between top edge of menu bar and text */

 /**
 * Window option and state flags
 */
#define MW_WINDOW_FLAG_HAS_BORDER				0x00000001	/**< Indicates that a window is to be drawn with a border */
#define MW_WINDOW_FLAG_HAS_TITLE_BAR			0x00000002	/**< Indicates that a window is to be drawn with a title bar */
#define MW_WINDOW_FLAG_CAN_BE_CLOSED			0x00000004	/**< Indicates that a window can be closed */
#define MW_WINDOW_FLAG_IS_VISIBLE				0x00000008	/**< Indicates that a window is visible */
#define MW_WINDOW_FLAG_IS_MINIMISED				0x00000010	/**< Indicates that a window is minimised */
#define MW_WINDOW_FLAG_IS_USED					0x00000020	/**< Indicates that a window is used */
#define MW_WINDOW_IS_MODAL						0x00000040	/**< Indicates that a window is currently modal */
#define MW_WINDOW_HAS_VERT_SCROLL_BAR			0x00000080  /**< Indicates that a window has a vertical scroll bar */
#define MW_WINDOW_HAS_HORIZ_SCROLL_BAR			0x00000100  /**< Indicates that a window has a horizontal scroll bar */
#define MW_WINDOW_HAS_MENU_BAR					0x00000200  /**< Indicates that a window has a menu bar */
#define MW_WINDOW_MENU_BAR_ENABLED				0x00000400	/**< Indicates that a menu bar, if existing, is enabled */
#define MW_WINDOW_MENU_BAR_ITEM_IS_SELECTED		0x00000800 	/**< Indicates that a menu bar, if existing, has an item selected */
#define MW_WINDOWS_VERT_SCROLL_BAR_ENABLED		0x00001000	/**< Indicates that a vertical scroll bar, if existing, is enabled */
#define MW_WINDOWS_HORIZ_SCROLL_BAR_ENABLED		0x00002000	/**< Indicates that a horizontal scroll bar, if existing, is enabled */
#define MW_WINDOW_TOUCH_FOCUS_AND_EVENT			0x00004000	/**< Indicates that a touch in a non-focused window gives it focus and generates a touch down event */

/**
 * Control option and state flags
 */
#define MW_CONTROL_FLAG_IS_VISIBLE				0x0001	/**< Indicates that a control is visible */
#define MW_CONTROL_FLAG_IS_ENABLED				0x0002	/**< Indicates that a control is enabled */
#define MW_CONTROL_FLAG_IS_USED					0x0004 	/**< Indicates that a control is used */
#define MW_CONTROL_FLAGS_LARGE_SIZE				0x0008	/**< Indicates that a control is to be drawn large size */

/**
 * Bitfields representing window frame components required to be redrawm
 */
#define MW_WINDOW_FRAME_COMPONENT_TITLE_BAR			0x01	/**< Title bar window frame components */
#define MW_WINDOW_FRAME_COMPONENT_BORDER			0x02	/**< Border window frame components */
#define MW_WINDOW_FRAME_COMPONENT_MENU_BAR			0x04	/**< Menu bar window frame components */
#define MW_WINDOW_FRAME_COMPONENT_VERT_SCROLL_BAR	0x08	/**< Vertical scroll bar window frame components */
#define MW_WINDOW_FRAME_COMPONENT_HORIZ_SCROLL_BAR	0x10	/**< Horizontal scroll bar window frame components */
#define MW_WINDOW_FRAME_COMPONENT_ALL (MW_WINDOW_FRAME_COMPONENT_TITLE_BAR | \
										MW_WINDOW_FRAME_COMPONENT_BORDER | \
										MW_WINDOW_FRAME_COMPONENT_MENU_BAR | \
										MW_WINDOW_FRAME_COMPONENT_VERT_SCROLL_BAR | \
										MW_WINDOW_FRAME_COMPONENT_HORIZ_SCROLL_BAR)		/**< All window frame components */

/************
*** TYPES ***
************/

/**
 * System defined window messages
 */
typedef enum
{
	/* Messages posted by the window manager */
	MW_WINDOW_CREATED_MESSAGE,						/**< Message send to window as soon as it is created and before it is painted */
	MW_WINDOW_REMOVED_MESSAGE,						/**< Message sent to window just before it is removed */
	MW_CONTROL_CREATED_MESSAGE,						/**< Message send to control as soon as it is created and before it is painted */
	MW_CONTROL_REMOVED_MESSAGE,			       		/**< Message sent to control just before it is removed */
	MW_TOUCH_DOWN_MESSAGE,					       	/**< Message sent to a window or control when it receives a touch down event */
	MW_TOUCH_HOLD_DOWN_MESSAGE,					    /**< Message sent to a window or control when it receives a touch hold down event */
	MW_TOUCH_UP_MESSAGE,					       	/**< Message sent to a window or control when it receives a touch up event */
	MW_TOUCH_DRAG_MESSAGE,							/**< Message sent to a window or control when it receives a drag event */
	MW_WINDOW_TIMER_MESSAGE,				       	/**< Message sent to a window or control when a timer has expired */
	MW_WINDOW_GAINED_FOCUS_MESSAGE,					/**< Message sent to a window when it gains focus */
	MW_WINDOW_LOST_FOCUS_MESSAGE,			 		/**< Message sent to a window when it loses focus */
	MW_CONTROL_GAINED_FOCUS_MESSAGE,				/**< Message sent to all controls in a window when parent window gains focus or control made visible */
	MW_CONTROL_LOST_FOCUS_MESSAGE,					/**< Message sent to all controls in a window when parent window loses focus or control made invisible */
	MW_WINDOW_RESIZED,								/**< Message to a window when it has been resized */
	MW_WINDOW_MOVED,								/**< Message to a window when it has been moved */
	MW_WINDOW_MINIMISED,							/**< Message to a window when it has been minimised */
	MW_WINDOW_RESTORED,								/**< Message to a window when it has been restored */
	MW_WINDOW_VISIBILITY_CHANGED,					/**< Message to a window when its visibility has changed */
	MW_WINDOW_VERT_SCROLL_BAR_SCROLLED_MESSAGE,		/**< Message to a window when a window vertical scroll bar has been scrolled */
	MW_WINDOW_HORIZ_SCROLL_BAR_SCROLLED_MESSAGE,	/**< Message to a window when a window horizontal scroll bar has been scrolled */
	MW_MENU_BAR_ITEM_PRESSED_MESSAGE,				/**< Response message from a menu bar that an item has been pressed */
	
	/* Messages posted by controls in response to user interface input */
	MW_BUTTON_PRESSED_MESSAGE,						/**< Response message from a button that it has been pressed */
	MW_CHECKBOX_STATE_CHANGE_MESSAGE,				/**< Response message from a check box that its state has changed */
	MW_RADIO_BUTTON_ITEM_SELECTED_MESSAGE,			/**< Response message from a radio button that its state has changed */
	MW_LIST_BOX_ITEM_PRESSED_MESSAGE,				/**< Response message from a list box that an item has been pressed */
	MW_INT_NUMBER_CHOOSER_OK_MESSAGE,				/**< OK response message from an integer number chooser */
	MW_INT_NUMBER_CHOOSER_CANCEL_MESSAGE,			/**< Cancel response message from an integer number chooser */
	MW_KEYBOARD_OK_MESSAGE,							/**< OK response message from a keyboard */
	MW_KEYBOARD_CANCEL_MESSAGE,						/**< Cancel Response message from a keyboard */
	MW_CONTROL_VERT_SCROLL_BAR_SCROLLED_MESSAGE,	/**< Response message from a vertical control scroll bar that it has been scrolled */
	MW_CONTROL_HORIZ_SCROLL_BAR_SCROLLED_MESSAGE,	/**< Response message from a horizontal control scroll bar that it has been scrolled */
	MW_ARROW_PRESSED_MESSAGE,						/**< Response message from a arrow that it has been pressed */

	/* Messages posted by standard dialogs */
	MW_DIALOG_ONE_BUTTON_DISMISSED_MESSAGE,			/**< One button dialog has been dismissed */
	MW_DIALOG_TWO_BUTTONS_DISMISSED_MESSAGE,		/**< Two button dialog has been dismissed */
	MW_DIALOG_TIME_CHOOSER_DISMISSED_MESSAGE,		/**< Time chooser dialog has been dismissed by ok button*/
	MW_DIALOG_DATE_CHOOSER_DISMISSED_MESSAGE,		/**< Date chooser dialog has been dismissed by ok button*/

	/* Messages that can be posted from user code or user code called utility functions */
	MW_WINDOW_PAINT_ALL_MESSAGE,			       	/**< System message to paint everything */
	MW_WINDOW_FRAME_PAINT_MESSAGE,				    /**< System message to get a window's frame painted */
	MW_WINDOW_CLIENT_PAINT_MESSAGE, 				/**< System message to call a window's client area paint function */
	MW_WINDOW_CLIENT_PAINT_RECT_MESSAGE,			/**< System message to call a window's client area paint rect function */
	MW_CONTROL_PAINT_MESSAGE,				      	/**< System message to call a control's paint function */
	MW_CONTROL_PAINT_RECT_MESSAGE, 					/**< System message to call a control's paint rect function */
	MW_TRANSFER_DATA_1_MESSAGE,						/**< Message to a window or control to send data in the data parameter; the window or control must know the format */
	MW_TRANSFER_DATA_2_MESSAGE,						/**< Message to a window or control to send data in the data parameter; the window or control must know the format */
	MW_TRANSFER_DATA_3_MESSAGE,						/**< Message to a window or control to send data in the data parameter; the window or control must know the format */
	MW_TRANSFER_DATA_4_MESSAGE,						/**< Message to a window or control to send data in the data parameter; the window or control must know the format */
	MW_TRANSFER_DATA_5_MESSAGE,						/**< Message to a window or control to send data in the data parameter; the window or control must know the format */
	MW_TRANSFER_DATA_1_PTR_MESSAGE,					/**< Message to a window or control that the data message parameter contains a pointer to data; the window or control must know the format */
	MW_TRANSFER_DATA_2_PTR_MESSAGE,					/**< Message to a window or control that the data message parameter contains a pointer to data; the window or control must know the format */
	MW_TRANSFER_DATA_3_PTR_MESSAGE,					/**< Message to a window or control that the data message parameter contains a pointer to data; the window or control must know the format */
	MW_TRANSFER_DATA_4_PTR_MESSAGE,					/**< Message to a window or control that the data message parameter contains a pointer to data; the window or control must know the format */
	MW_TRANSFER_DATA_5_PTR_MESSAGE,					/**< Message to a window or control that the data message parameter contains a pointer to data; the window or control must know the format */
	MW_USER_1_MESSAGE,								/**< Message to a window for any user-defined purpose */
	MW_USER_2_MESSAGE,								/**< Message to a window for any user-defined purpose */
	MW_USER_3_MESSAGE,								/**< Message to a window for any user-defined purpose */
	MW_USER_4_MESSAGE,								/**< Message to a window for any user-defined purpose */
	MW_USER_5_MESSAGE								/**< Message to a window for any user-defined purpose */
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

/* forward declare message struct and its typedef */
struct mw_message_tag;
typedef struct mw_message_tag mw_message_t;

/**
 * Function signature definition for the paint function that every window and control must implement
 *
 * @param window_ref The window/control id of the window/control being painted in the paint function
 * @param draw_info Draw info structure describing offset and clip region
 * @note Do not call this directly from user code
 */
typedef void (*mw_paint_func_p)(uint8_t window_ref, const mw_gl_draw_info_t *draw_info);

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
	uint8_t sender_id;					/**< Identifier of sender of message, not always used  */
	uint8_t recipient_id;               /**< Identifier of recipient of message, not always used */
	mw_message_id_t message_id;       	/**< Identifier of the message; this is a system identifier or a user defined identifier */
	mw_message_recipient_type_t message_recipient_type;        /**< Type of recipient this message is for */
	uint32_t message_data;              /**< Data value passed to recipient with a message; this is message specific and may be a pointer */
} mw_message_t;

/**
 * Structure containing information pertaining to each window
 */
typedef struct 
{
    char **menu_bar_items;				/**< Pointer to array of menu bar entry labels */
    mw_paint_func_p paint_func;         /**< Pointer to window paint function */
    mw_message_func_p message_func;     /**< Pointer to window message handler function */	
    uint32_t window_flags;				/**< All the flags defining a window's description and state */
	void *instance_data;				/**< Optional void pointer to window specific data structure containing extra window instance specific data */
	mw_util_rect_t window_rect;         /**< Rect containing coordinates of window including title bar and border if present */
	mw_util_rect_t client_rect;         /**< Rect containing coordinates of window's client area */
	uint16_t menu_bar_item_enables;		/**< Bitfield of individual enable flags for menu bar items */
	uint8_t z_order;                    /**< Z order of the window, higher value drawn on top of lower values */
    uint8_t	horiz_scroll_pos; 			/**< Current scroll position of a horizontal scroll bar scaled to 0-255 */
    uint8_t vert_scroll_pos;			/**< Current scroll position of a vertical scroll bar scaled to 0-255 */
    uint8_t menu_bar_items_count;		/**< Number of items in above array */
    uint8_t menu_bar_selected_item;		/**< The most recently selected menu bar item */
    char title[MW_MAX_TITLE_SIZE + 1];  /**< The window's title in the title bar */
} mw_window_t;

/**
 * Structure containing information pertaining to each control
 */
typedef struct 
{
    mw_paint_func_p paint_func;         /**< Pointer to control paint function */
    mw_message_func_p message_func;     /**< Pointer to control message handler function */
	void *instance_data;				/**< Void pointer to control specific data structure containing extra control specific configuration data per instance */
	uint16_t control_flags;				/**< All the flags defining a control's description and state */
	mw_util_rect_t control_rect;        /**< Rect containing coordinates of control's area */
    uint8_t parent;                     /**< This control's parent window */
} mw_control_t;

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
 * your application’s main function, or MiniWin thread first call if running in
 * a thread.
 */
void mw_init();

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
 * new window reference number or MAX_WINDOW_COUNT if there is an error.
 *
 * @param rect The rect of the window's total area, including border and title bar
 * @param title The window title as shown in title bar
 * @param paint_func Pointer to paint function
 * @param message_func Pointer to message handling function
 * @param menu_bar_items Pointer to array holding menu bar item text labels
 * @param menu_bar_items_count Number of entries in above array
 * @param window_flags The new window's description and state flags
 * @param instance_data Optional pointer to any extra window data that is instance specific, can be NULL if no instance data
 * @return The new window id if created or MAX_WINDOW_COUNT if it could not be created
 * @warning Do not call from within any paint function
 */
uint8_t mw_add_window(mw_util_rect_t *rect,
		char* title,
		mw_paint_func_p paint_func,
		mw_message_func_p message_func,
		char **menu_bar_items,
		uint8_t menu_bar_items_count,
		uint32_t window_flags,
		void *instance_data);

/**
 * Bring a window to the front giving it the highest Z order of all windows.
 *
 * @param window_ref Position in array of all windows of this window
 * @note It is up to the user to issue appropriate paint messages (window frame and
 *       client area) to get the window repainted
 */
void mw_bring_window_to_front(uint8_t window_ref);

/**
 * Send a window to the back giving it the lowest Z order of all windows.
 *
 * @param window_ref Position in array of all windows of this window
 * @note It is up to the user to issue a paint all message to get windows repainted that
 * 		 have beenexposed by sending this window to the back
 */
void mw_send_window_to_back(uint8_t window_ref);

/**
 *  Set a window's visibility if it is used. If set visible it is given focus and brought
 *  to the front of other showing windows.
 *
 * @param window_ref Position in array of all windows of this window
 * @param visible true or false
 * @note It is up to the user to issue the appropriate window paint messages (paint all
 *       if a window is made invisible or paint window frame and client area if made
 *       visible.
 */
void mw_set_window_visible(uint8_t window_ref, bool visible);

/**
 * Set a window minimised if it is used.
 *
 * @param window_ref Position in array of all windows of this window
 * @param minimised true or false
 * @note It is up to the user to issue the appropriate window paint messages (paint all
 *       if a window is mainimized or paint window frame and client area if restored
 */
void mw_set_window_minimised(uint8_t window_ref, bool minimised);

/**
 * Reposition a window. All contained controls' client areas updated automatically.
 *
 * @param window_ref Position in array of all windows of this window
 * @param new_x The new x position of the left edge of the window
 * @param new_y The new y position of the top edge of the window
 * @note It is up to the user to issue a paint all message
 */
void mw_reposition_window(uint8_t window_ref, int16_t new_x, int16_t new_y);

/**
 * Resize a window. All contained controls' client areas updated automatically.
 *
 * @param window_ref Position in array of all windows of this window
 * @param new_width The new width of the window
 * @param new_height The new height of the window
 * @return If the resize was successful
 * @note It is up to the user to issue a paint all message
 */
bool mw_resize_window(uint8_t window_ref, uint16_t new_width, uint16_t new_height);

/**
 * Find the window with focus. This is the visible window with the highest Z order.
 *
 * @return The window ref of the window.
 */
uint8_t mw_find_window_with_focus(void);

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
 * @param window_ref Position in array of all windows of this window
 * @param modal true to set modal, false to set non-modal
 * @note Some means of setting the window non-modal again must be implemented, usually a button in the
 *       window. A modal window cannot be closed from a title bar icon.
 */
void mw_set_window_modal(uint8_t window_ref, bool modal);

/**
 * Set a menu bar enabled or disabled for a window
 *
 * @param window_ref The window containing the menu bar
 * @param enabled The new state
 */
void mw_set_menu_bar_enabled_state(uint8_t window_ref, bool enabled);

/**
 * Set menu bar's individual items enabled or disabled
 *
 * @param window_ref The window containing the menu bar
 * @param item_enables Bit field containing the states, msb is first menu ar item, 1 is enabled, 0 is disabled
 * @note Maximum of 16 items in a menu bar.
 */
void mw_set_menu_bar_items_enabled_state(uint8_t window_ref, uint16_t item_enables);

/**
 * Set a window horizontal scroll bar enabled or disabled
 *
 * @param window_ref The window containing the scroll bar
 * @param enabled The new state
 */
void mw_set_window_horiz_scroll_bar_enabled_state(uint8_t window_ref, bool enabled);

/**
 * Set a window vertical scroll bar enabled or disabled
 *
 * @param window_ref The window containing the scroll bar
 * @param enabled The new state
 */
void mw_set_window_vert_scroll_bar_enabled_state(uint8_t window_ref, bool enabled);

/**
 * Add a message to the message queue to get a window frame painted. This
 * paints the borders, title bar, menu bar and scroll bars.
 *
 * @param window_ref Position in array of all windows of this window
 * @param components The constituent components of a window frame to be painted
 */
void mw_paint_window_frame(uint8_t window_ref, uint8_t components);

/**
 * Add a message to the message queue to get a window's client area and contained controls painted.
 * This is useful when you know that the window is at the front and has focus and the borders and title
 * bar do not need repainting.
 *
 * @param window_ref Position in array of all windows of this window
 */
void mw_paint_window_client(uint8_t window_ref);

/**
 * Add a message to the message queue to get a specified part of a window's client area and contained controls painted.
 * This is useful when you know that the window is at the front and has focus and the borders and title
 * bar do not need repainting.
 *
 * @param window_ref Position in array of all windows of this window
 * @param rect The area to be repainted in window client coordinates
 * @note The rect pointed to by rect must be persistent and not a local variable of the calling function
 */
void mw_paint_window_client_rect(uint8_t window_ref, const mw_util_rect_t *rect);

/**
 * Remove a window and all its controls if it has any.
 *
 * @param window_ref Position in array of all windows of this window
 */
void mw_remove_window(uint8_t window_ref);

/**
 * Get a window's client area rect
 *
 * @param window_ref The window to get the rect for
 * @return The returned rect
 */
mw_util_rect_t mw_get_window_client_rect(uint8_t window_ref);

/**
 * Get a window's instance_data data pointer
 *
 * @param window_ref The window to get the instance data pointer for
 * @return The returned instance_data data pointer
 */
void *mw_get_window_instance_data(uint8_t window_ref);

/**
 * Find if there are any free control slots in array of controls
 *
 * @return true if there are else false
 */
bool mw_find_if_any_control_slots_free(void);

/**
 * Set the window's title bar text
 *
 * @param window_ref the window to set the title bar text for
 * @param title_text the new title bar text
 */
void wm_set_window_title(uint8_t window_ref, char *title_text);

/**
 * Add a new control to a window. Returns new control reference number or MAX_WINDOW_COUNT if there is an error.
 *
 * @param rect The rect of the control's area
 * @param parent The window reference of the control's parent window
 * @param paint_func Pointer to paint function
 * @param message_func Pointer to message handling function
 * @param control_flags Flags describing the control and its state
 * @param instance_data void Pointer to control specific data structure containing extra control specific configuration data for this instance
 * @return The new control id if created or MAX_CONTROL_COUNT if it could not be created
 */
uint8_t mw_add_control(mw_util_rect_t *rect,
		uint8_t parent,
		mw_paint_func_p paint_func,
		mw_message_func_p message_func,
		uint16_t control_flags,
		void *instance_data);

/**
 * Set a control visible if it is used
 *
 * @param control_ref Position in array of all controls of this control.
 * @param visible True or false
 */
void mw_set_control_visible(uint8_t control_ref, bool visible);

/**
 * Set a control enabled if it is used
 *
 * @param control_ref Position in array of all controls of this control.
 * @param enabled True or false
 */
void mw_set_control_enabled(uint8_t control_ref, bool enabled);

/**
 * Add a message to the message queue to get a control painted.
 *
 * @param control_ref Position in array of all controls of this control
 */
void mw_paint_control(uint8_t control_ref);

/**
 * Add a message to the message queue to get a specified part of a control's client area painted.
 *
 * @param control_ref Position in array of all controls of this control
 * @param rect The area to be repainted in control client coordinates
 * @note The rect pointed to by rect must be persistent and not a local variable of the calling function
 */
void mw_paint_control_rect(uint8_t control_ref, const mw_util_rect_t *rect);

/**
 * Remove a control.
 *
 * @param control_ref Position in array of all controls of this control
 */
void mw_remove_control(uint8_t control_ref);

/**
 * Get a control's rect
 *
 * @param control_ref The control to get the rect for
 * @return The returned rect
 */
mw_util_rect_t mw_get_control_rect(uint8_t control_ref);

/**
 * Get a control's parent window ref
 *
 * @param control_ref The control to get the parent for
 * @return The returned parent's window id
 */
uint8_t mw_get_control_parent_window(uint8_t control_ref);

/**
 * Get a control's instance_data data pointer
 *
 * @param control_ref The control to get the instance data pointer for
 * @return The returned instance_data data pointer
 */
void *mw_get_control_instance_data(uint8_t control_ref);

/**
 * Get a control's flags bitfield
 *
 * @param control_ref The control to get the flags bitfield for
 * @return The returned flags bitfield
 */
uint16_t mw_get_control_flags(uint8_t control_ref);

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
 * @param recipient_id The position in the array of windows or controls of the recipient window or control
 * @param recipient_type If the recipient is a window or a conreol
 * @return The new timer id if the timer could be set or MAX_TIMER_COUNT if it could not be set
 */
uint8_t mw_set_timer(uint32_t fire_time, uint8_t recipient_id, mw_message_recipient_type_t recipient_type);

/**
 * Cancel a previously set timer.
 *
 * @param timer_id The id of the timer to cancel as returned by set_timer
 */
void mw_cancel_timer(uint8_t timer_id);

/**
 * Package up the filling in and sending of a windows message.
 *
 * The message is added to the window manager message queue and will be processed by the recipient
 * asynchronously.
 *
 * @param message_id The message id of the message to create
 * @param sender_id The message id of the sender
 * @param recipient_id The recipient id for the message
 * @param message_data 32 bit field of general purpose data; can be a pointer
 * @param recipient_type Recipient type of message, window, control or system
 */
void mw_post_message(uint8_t message_id, uint8_t sender_id, uint8_t recipient_id, uint32_t message_data, mw_message_recipient_type_t recipient_type);

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
 * @param show True to show message, false to stop showing it
 */
void mw_show_busy(bool show);


#ifdef __cplusplus
}
#endif

#endif
