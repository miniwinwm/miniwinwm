#ifndef MINIWIN_CONFIG_H
#define MINIWIN_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif

#define MW_MAX_WINDOW_COUNT 				3U               		/**< Maximum number of allowed windows; root window always takes 1 space */
#define MW_MAX_CONTROL_COUNT				5U              		/**< Total maximum number of allowed controls in all windows */
#define MW_MAX_TIMER_COUNT					8U              		/**< Maximum number of timers */
#define MW_MESSAGE_QUEUE_SIZE				80U              		/**< Maximum number of messages in message queue */
#define MW_DISPLAY_ROTATION_0
/* #define MW_DISPLAY_ROTATION_90 */
/* #define MW_DISPLAY_ROTATION_180 */
/* #define MW_DISPLAY_ROTATION_270 */
#if defined(MW_DISPLAY_ROTATION_0) || defined(MW_DISPLAY_ROTATION_180)
#define MW_ROOT_WIDTH 						mw_hal_lcd_get_display_width()  /**< Width of root window */
#define MW_ROOT_HEIGHT 						mw_hal_lcd_get_display_height() /**< Height of root window */
#elif defined(MW_DISPLAY_ROTATION_90) || defined(MW_DISPLAY_ROTATION_270)
#define MW_ROOT_WIDTH 						mw_hal_lcd_get_display_height() /**< Width of root window */
#define MW_ROOT_HEIGHT 						mw_hal_lcd_get_display_width()	/**< Height of root window */
#endif
#define MW_MAX_TITLE_SIZE 					14U              		/**< Maximum window title bar title size in characters */
#define MW_TITLE_BAR_COLOUR_FOCUS			MW_HAL_LCD_BLUE    		/**< Colour of title bar of window with focus */
#define MW_TITLE_BAR_COLOUR_NO_FOCUS		MW_HAL_LCD_GREY5    	/**< Colour of title bars of windows without focus */
#define MW_TITLE_BAR_COLOUR_MODAL			MW_HAL_LCD_RED			/**< Colour of title bar of modal window */
#define MW_TITLE_TEXT_COLOUR_FOCUS			MW_HAL_LCD_WHITE    	/**< Title bar text colour of window with focus */
#define MW_TITLE_TEXT_COLOUR_NO_FOCUS		MW_HAL_LCD_WHITE    	/**< Title bar text colour of window without focus */
#define MW_TITLE_TEXT_COLOUR_MODAL			MW_HAL_LCD_WHITE   	 	/**< Title bar text colour of window that's modal */
#define MW_CONTROL_UP_COLOUR				MW_HAL_LCD_GREY2    	/**< Animated controls up colour */
#define MW_CONTROL_SEPARATOR_COLOUR			MW_HAL_LCD_GREY3		/**< Separator between control items colour */
#define MW_CONTROL_DOWN_COLOUR				MW_HAL_LCD_GREY4    	/**< Animated controls down colour */
#define MW_CONTROL_DISABLED_COLOUR			MW_HAL_LCD_GREY5		/**< Colour to draw a control that is disabled */
#define MW_CONTROL_DOWN_TIME				4U               		/**< Time for animated controls down time in system ticks */
#define MW_KEY_DOWN_TIME					3U               		/**< Time for animated keys down time in system ticks */
#define MW_TICKS_PER_SECOND					20U						/**< The number of window timer ticks per second */
#define MW_WINDOW_MIN_MAX_EFFECT_TIME		5U						/**< Number of window ticks to show window minimise/maximise effect for */
#define MW_CURSOR_PERIOD_TICKS				10U						/**< Period between cursor change in system ticks */
#define MW_TOUCH_INTERVAL_TICKS				2U               		/**< Number of window ticks a touch has to be down for to count as a touch event */
#define MW_HOLD_DOWN_DELAY_TICKS			10U						/**< Time in ticks that a ui control starts repeating if held down */
#define MW_FONT_12_INCLUDED											/**< Comment this in to include Courier 12 point font or out to exclude it */
#define MW_FONT_16_INCLUDED											/**< Comment this in to include Courier 16 point font or out to exclude it */
#define MW_FONT_20_INCLUDED											/**< Comment this in to include Courier 20 point font or out to exclude it */
#define MW_FONT_24_INCLUDED											/**< Comment this in to include Courier 24 point font or out to exclude it */
/* #define MW_DIALOG_FILE_CHOOSER */								/**< File chooser dialog is optional and is only built if this is defined */
#define MW_DRAG_THRESHOLD_PIXELS			2               		/**< Distance a touch pointer moves before a drag event is created */
#define MW_BUSY_TEXT						"BUSY..."				/**< Text to display when screen is not responsive because of long operation */
#define MW_CALIBRATE_TEXT					"Touch centre of cross"	/**< Text to display in touch screen calibrate screen */

#ifdef __cplusplus
}
#endif

#endif