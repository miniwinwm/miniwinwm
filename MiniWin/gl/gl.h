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

#ifndef _GL_H
#define _GL_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include <miniwin_utilities.h>
#include "hal/hal_lcd.h"

/****************
*** CONSTANTS ***
****************/

/**
 * User configurable value
 */
#define MW_GL_MAX_POLY_CORNERS 				5                   /**< Maximum number of corner coordinate points to a polygon */
#define MW_GL_SEGMENT_FILL_ANGLE_STEP_SIZE	5                   /**< Step angle when filling a circular segment with triangles */
#define MW_GL_MAX_X					(MW_HAL_LCD_WIDTH - 1)      /**< Maximum x pixel coordinate */
#define MW_GL_MAX_Y					(MW_HAL_LCD_HEIGHT - 1)     /**< Maximum y pixel coordinate */

/**
 * Non-user configurable values
 */
#define MW_GL_STANDARD_CHARACTER_HEIGHT 	10                  /**< Height of standard character plus inter-line space */
#define MW_GL_STANDARD_CHARACTER_WIDTH 		6                   /**< Width of standard character plus inter-character space */ 
#define MW_GL_LARGE_CHARACTER_HEIGHT		16                  /**< Height of large character plus inter-line space */

/************
*** TYPES ***
************/

/**
 * Enum of border values for shapes
 */
typedef enum
{
	MW_GL_BORDER_OFF,                  /**< No border drawn on shape */
	MW_GL_BORDER_ON                    /**< Draw border on shape */
} mw_gl_border_t;

/**
 * Enum of fill values for shapes
 */
typedef enum
{
	MW_GL_NO_FILL,                     /**< Fill shape when drawing */
	MW_GL_FILL                         /**< Leave shape empty after drawing */
} mw_gl_fill_t;

/**
 * Enum of transparency of fill, text or monochrome bitmaps
 */
typedef enum
{
	MW_GL_BG_TRANSPARENT,              /**< Draw transparently, i.e. do not plot background pixels */
	MW_GL_BG_NOT_TRANSPARENT           /**< Do not draw transparently */
} mw_gl_bg_transparent_t;

/**
 * Enum of line styles. These need to be 16 bits.
 */
typedef enum
{
	MW_GL_LINE_NONE = 0x0000,          	/**< No line drawn */
	MW_GL_DOT_LINE = 0x5555,			/**< Small dots line drawn */
	MW_GL_DOUBLE_DOT_LINE = 0xCCCC,    	/**< Double dot pattern line drawn */
	MW_GL_SMALL_DASH_LINE = 0xEEEE,    	/**< Small dash pattern line drawn */
	MW_GL_DASH_LINE = 0xFCFC,          	/**< Standard dash pattern line drawn */
	MW_GL_LARGE_DASH_LINE = 0xFFF0,    	/**< Large dash with small space pattern line drawn */
	MW_GL_DASH_DOT_LINE = 0xFAFA,      	/**< Dash dot pattern line drawn */
	MW_GL_EQUAL_LARGE_DASH = 0xFF00,   	/**< Large dash with equal space pattern line drawn */
	MW_GL_SOLID_LINE = 0xFFFF          	/**< Solid line drawn */
} mw_gl_line_t;

/**
 * Fill pattern type. This is an array of 16 16 bit values/
 */
typedef uint16_t mw_gl_pattern_t[16];

/**
 * Graphics context definition. This controls all line, text and shape filling routines apart from clear screen.
 */
typedef struct
{
	mw_hal_lcd_colour_t fg_colour;             		/**< foreground colour for text and line drawing */
	mw_hal_lcd_colour_t bg_colour;                     /**< background colour for text and line drawing */
	mw_hal_lcd_colour_t solid_fill_colour;             /**< solid fill colour for filled shapes */
	mw_gl_line_t line;                            /**< line style */
	mw_gl_pattern_t pattern;                      /**< pattern fill definition - 16x16 bits */
	mw_gl_border_t border;                        /**< whether to plot a border on shapes that are filled */
	mw_gl_fill_t fill;                            /**< whether to fill a shape with solid colour or pattern */
	uint8_t pattern_set;                    /**< whether a pattern has been set and used. If not set, fill will be solid colour */
	mw_gl_bg_transparent_t bg_transparent;    	/**< whether to clear the background of text or draw transparently */
} mw_gl_gc_t;

/**
 * Reference frame and clip rect information passed to all draw routines
 *
 * @note if the reference frame contains origin_x = 42, origin_y = 21 and user requests pixel 10, 5 to be plotted
 *       the actual point on the screen that will be plotted will be 52, 26
 */
typedef struct
{
	int16_t origin_x;                   /**< x coordinate of origin of reference frame */
	int16_t origin_y;                   /**< y coordinate of origin of reference frame */
	mw_util_rect_t clip_rect;           /**< clip rect that will be applied to points requested to be plotted, in coordinates relative to offset_x, offset_y */
} mw_gl_draw_info_t;

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Initialise the hardware and set gc to default values.
 */
void mw_gl_init(void);

/**
 * Get a pointer to the internal graphics context.
 *
 * @return A pointer to the graphics context
 */
mw_gl_gc_t *mw_gl_get_gc(void);

/**
 * Set colour used for foreground in text, lines and pattern fills.
 *
 * @param colour The new foreground colour to store in the graphics context
 */
void mw_gl_set_fg_colour(mw_hal_lcd_colour_t colour);

/**
 * Set colour used for background in text, lines and pattern fills.
 *
 * @param colour The new background colour to store in the graphics context
 */
void mw_gl_set_bg_colour(mw_hal_lcd_colour_t colour);

/**
 * Set colour used for fills.
 *
 * @param colour The new solid fill colour to store in the graphics context
 */
void mw_gl_set_solid_fill_colour(mw_hal_lcd_colour_t colour);

/**
 * Set line dash/dot pattern.
 *
 * @param line The new line style to store in the graphics context
 */
void mw_gl_set_line(mw_gl_line_t line);

/**
 * Set fill bitmap pattern.
 *
 * @param pattern The new fill bitmap pattern to store in the graphics context
 */
void mw_gl_set_pattern(const mw_gl_pattern_t pattern);

/**
 * Clear bitmap fill pattern and set fill back to solid.
 */
void mw_gl_clear_pattern(void);

/**
 * Set filled shape border on or off.
 *
 * @param border The new state of border drawing to store in the graphics context
 */
void mw_gl_set_border(mw_gl_border_t border);

/**
 * Set shape fill on or off.
 *
 * @param fill The new state of shape filling to store in the graphics context
 */
void mw_gl_set_fill(mw_gl_fill_t fill);

/**
 * Sets transparent mode so all plotting routines that use background colour will leave background pixels unchanged.
 *
 * @param bg_transparent The new state of background transparency to store in the graphics context
 */
void mw_gl_set_bg_transparency(mw_gl_bg_transparent_t bg_transparent);

/**
 * Draw a single pixel taking into account pattern and solid fill colour.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x X coordinate of point
 * @param y Y coodinate of point
 */
void mw_gl_solid_fill_pixel(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y);

/**
 * Plot a single pixel using the foreground colour.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x X coordinate of the pixel to plot
 * @param y Y coordinate of the pixel to plot
 */
void mw_gl_fg_pixel(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y);

/**
 * Plot a single pixel using the background colour.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x X coordinate of the pixel to plot
 * @param y Y coordinate of the pixel to plot
 */
void mw_gl_bg_pixel(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y);

/**
 * Draw a horizontal line. Foreground colour, background colour and line style controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x_start X coordinate of the start of the line
 * @param x_end X coordinate of the end of the line; this pixel is plotted
 * @param y Y coordinate of the horizontal line
 */
void mw_gl_hline(const mw_gl_draw_info_t *draw_info, int16_t x_start, int16_t x_end, int16_t y);

/**
 * Draw a vertical line. Foreground colour, background colour and line style controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x X coordinate of the vertical line
 * @param y_start Y coordinate of the start of the line
 * @param y_end Y coordinate of the end of the line; this pixel is plotted
 */
void mw_gl_vline(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y_start, int16_t y_end);

/**
 * Draw a general angle line. Foreground colour, background colour and line style controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param p1x X coordinate of the start of the line
 * @param p1y Y coordinate of the start of the line
 * @param p2x X coordinate of the end of the line; this pixel is plotted
 * @param p2y Y coordinate of the end of the line; this pixel is plotted
 */
void mw_gl_line(const mw_gl_draw_info_t *draw_info, int16_t p1x, int16_t p1y, int16_t p2x, int16_t p2y);

/**
 * Draw a filled or unfilled rectangle. Fill, border, line style and colours controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x X coordinate of the left edge of the rectangle
 * @param y Y coordinate of the top edge of the rectangle
 * @param width Width of the rectangle
 * @param height Height of the rectangle
 */
void mw_gl_rectangle(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, int16_t width, int16_t height);

/**
 * Draw a single small fixed width horizontal character. Foreground colour, background colour and transparency controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x Coordinate of the left edge of the rectangle containing the character
 * @param y Coordinate of the top edge of the rectangle containing the character
 * @param c The ISO8859-15 character
 */
void mw_gl_character(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, char c);

/**
 * Draw a horizontal string of small fixed width horizontal characters. Foreground colour, background colour and transparency controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x Coordinate of the left edge of the rectangle containing the first character
 * @param y Coordinate of the top edge of the rectangle containing the first character
 * @param s Pointer to the null terminated string containing ISO8859-1 characters
 */
void mw_gl_string(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, const char *s);

/**
 * Draw a single small fixed width vertical character rotated 90 degrees clockwise. Foreground colour, background colour and transparency controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x Coordinate of the top of the rotated character, i.e. the character will be drawn from this point left
 * @param y Coordinate of the left edge of the character, i.e. the character will be drawn from this point down
 * @param c the ISO8859-15 character
 */
void mw_gl_character_vert(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, char c);

/**
 * Draw a vertical string of small fixed width horizontal characters rotated 90 degrees clockwise. Foreground colour, background colour and transparency controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x Coordinate of the top of the rotated characters, i.e. the characters will be drawn from this point left
 * @param y Coordinate of the left edge of the first character, i.e. the characters will be drawn from this point down
 * @param s Pointer to the null terminated string containing ISO8859-15 characters
 */
void mw_gl_string_vert(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, const char *s);

/**
 * Draw a horizontal string of large proportional characters. Foreground colour, background colour and transparency controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x Coordinate of the left edge of the rectangle containing the first character
 * @param y Coordinate of the top edge of the rectangle containing the first character
 * @param s Pointer to the null terminated string containing ISO8859-15 characters
 */
void mw_gl_large_string(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, const char *s);

/**
 * Draw a vertical string of large proportional characters rotated 90 degrees clockwise.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x Coordinate of the top of the rotated characters, i.e. the characters will be drawn from this point left
 * @param y Coordinate of the left edge of the first character, i.e. the characters will be drawn from this point down
 * @param s Pointer to the null terminated string containing ISO8859-15 characters
 */
void mw_gl_large_string_vert(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, const char *s);

/**
 * Calculate the width in pixels of a string of large proportional characters.
 * @param s Null terminated string to calculate the width of
 * @return Width in pixels
 */
uint16_t mw_gl_large_string_width(const char *s);

/**
 * Calculate the width in pixels of an array of strings of large proportional characters.
 *
 * @param s Pointer to array of strings to look for the largest string
 * @param count The number of entries in the array
 * @return Width in pixels
 */
uint16_t mw_gl_largest_string_width(const char **s, uint16_t count);

/**
 * Draw a filled or unfilled circle.  Fill, border, line style and colours controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x X position of the centre of the circle
 * @param y Y position of the centre of the circle
 * @param radius Radius of the circle
 */
void mw_gl_circle(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, int16_t radius);

/**
 * Draw a filled or unfilled polygon.  Fill, border, line style and colours controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param poly_corners Number of point pairs in the points arrays
 * @param poly_x Array of x coordinates of the polygon points
 * @param poly_y Array of y coordinates of the polygon points
 * @param x_offset Fixed value to be added to all x coordinates in poly_x
 * @param y_offset Fixed value to be added to all y coordinates in poly_y
 */
void mw_gl_poly(const mw_gl_draw_info_t *draw_info, uint8_t poly_corners, const int16_t *poly_x, const int16_t *poly_y, int16_t x_offset, int16_t y_offset);

/**
 * Rotate (but not plot) polygon coordinates.
 * 
 * @param poly_corners Number of point pairs in the points arrays
 * @param poly_x Array of x coordinates of the polygon points
 * @param poly_y Array of y coordinates of the polygon points
 * @param angle_degrees Angle to rotate the polygon points
 */
void mw_gl_rotate_shape(uint8_t poly_corners, int16_t *poly_x, int16_t *poly_y, int16_t angle_degrees);

/**
 * Scale (but not plot) polygon coordinates. Scale 10 remains same size.
 *
 * @param poly_corners Number of point pairs in the points arrays
 * @param poly_x Array of x coordinates of the polygon points
 * @param poly_y Array of y coordinates of the polygon points
 * @param scale_x Stretch factor to apply to the shape in the x direction, multiplied by 10
 * @param scale_y Stretch factor to apply to the shape in the y direction, multiplied by 10
 */
void mw_gl_scale_shape(uint8_t poly_corners, int16_t *poly_x, int16_t *poly_y, int16_t scale_x, int16_t scale_y);

/**
 * Draw an arc. Line style and colours controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param centre_x X coordinate of the centre point of the circle describing the arc
 * @param centre_y Y coordinate of the centre point of the circle describing the arc
 * @param radius Radius of the circle describing the arc
 * @param start_angle Start angle of the arc, clockwise angle from line upwards from origin
 * @param end_angle End angle of the arc, clockwise angle from line upwards from origin
 */
void mw_gl_arc(const mw_gl_draw_info_t *draw_info, int16_t centre_x, int16_t centre_y, int16_t radius, int16_t start_angle, int16_t end_angle);

/**
 *  Draw a filled or unfilled round cornered rectangle using.  Fill, border, line style and colours controlled by gc. Width and height must be > 2 * corner_radius.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x X coordinate of left edge of rectangle
 * @param y Y coordinate of top end of rectangle
 * @param width Width of rectangle
 * @param height Height of rectangle
 * @param corner_radius Radius of curved quarter-circle corner
 */
void mw_gl_rounded_rectangle(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, int16_t width, int16_t height, int16_t corner_radius);

/**
 * Draw a filled or unfilled circular segment.  Fill, border, line style and colours controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param centre_x X coordinate of the centre point of the circle describing the arc
 * @param centre_y Y coordinate of the centre point of the circle describing the arc
 * @param radius Radius of the circle describing the arc
 * @param start_angle Start angle of the arc, clockwise angle from line upwards from origin
 * @param end_angle End angle of the arc, clockwise angle from line upwards from origin
 */
void mw_gl_segment(const mw_gl_draw_info_t *draw_info, int16_t centre_x, int16_t centre_y, int16_t radius, int16_t start_angle, int16_t end_angle);

/**
 * Plot a bi-colour bitmap using the foreground and background colours, and transparency if set. Clips if necessary
 * 
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param start_x Coordinate of where to plot the left edge of the bitmap
 * @param start_y Coordinate of where to plot the top edge of the bitmap
 * @param image_data_width_pixels Width of the bitmap in pixels in the supplied data
 * @param image_data_height_pixels Height of the bitmap in pixels in the supplied data
 * @param image_data Pointer to data containing the bitmap data; each row will be bigger than (width / 8) bytes if (width % 8) > 0
 */
void mw_gl_monochrome_bitmap(const mw_gl_draw_info_t *draw_info,
		int16_t start_x,
		int16_t start_y,
		uint16_t image_data_width_pixels,
		uint16_t image_data_height_pixels,
		const uint8_t *image_data);

/**
 * Plot a full colour bitmap. Clips if necessary.
 * 
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param start_x X coordinate of where to plot the left edge of the bitmap
 * @param start_y Y coordinate of where to plot the top edge of the bitmap
 * @param image_data_width_pixels Width of the bitmap in pixels in the supplied data
 * @param image_data_height_pixels Height of the bitmap in pixels in the supplied data
 * @param image_data Pointer to data containing the bitmap data in colour_t format
 */
void mw_gl_colour_bitmap(const mw_gl_draw_info_t *draw_info,
		int16_t start_x,
		int16_t start_y,
		uint16_t image_data_width_pixels,
		uint16_t image_data_height_pixels,
		const mw_hal_lcd_colour_t *image_data);

#ifdef __cplusplus
}
#endif

#endif
