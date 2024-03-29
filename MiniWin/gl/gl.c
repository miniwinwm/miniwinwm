/*

MIT License

Copyright (c) John Blaiklock 2019 miniwin Embedded Window Manager

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

/***************
*** INCLUDES ***
***************/

#include <string.h>
#include <math.h>
#include "miniwin_debug.h"
#include "miniwin_config.h"
#include "gl/gl.h"
#include "gl/fonts/bitmapped/fonts.h"
#include "gl/fonts/bitmapped/gl_title_font.h"
#include "gl/fonts/truetype/mcufont/mcufont.h"

/****************
*** CONSTANTS ***
****************/

#define	DEGREES_IN_RAD		(180.0f / M_PI)

/************
*** TYPES ***
************/

/**
 * Struct to hold true type drawing info as the rendering procedure descends through its stack.
 */
typedef struct
{
	const mw_gl_draw_info_t *draw_info;				/**< Draw info structure to be passed on to pixel plotting routine */
    const struct mf_font_s *font;					/**< Run-length encoded font structure to use for text rendering */
    mw_util_rect_t bounding_box;					/**< The bounding box to render the text in to */
    int16_t bottom;									/**< Bottom line in pixels of bounding box, y + height */
    uint8_t fg_red;									/**< Foreground colour to plot text, red component */
    uint8_t fg_green;								/**< Foreground colour to plot text, green component */
    uint8_t fg_blue;								/**< Foreground colour to plot text, blue component */
    uint8_t bg_red;									/**< Background colour to plot text, red component */
    uint8_t bg_green;								/**< Background colour to plot text, green component */
    uint8_t bg_blue;								/**< Background colour to plot text, blue component */
    mw_gl_tt_font_justification_t justification;	/**< Rendering justification used */
    int16_t rendered_line_count;					/**< How many lines in pixels that have been rendered so far */
    int16_t vert_scroll_pixels;						/**< How many pixel lines to scroll the text up */
} tt_font_state_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern const sFONT Font9;							/**< Information structure for font */
extern const sFONT Font12;							/**< Information structure for font */
extern const sFONT Font16;							/**< Information structure for font */
extern const sFONT Font20;							/**< Information structure for font */
extern const sFONT Font24;							/**< Information structure for font */

/**********************
*** LOCAL VARIABLES ***
**********************/

static mw_gl_gc_t gc;                       		/**< The graphics context used to hold all the settings used by the plotting routines */

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void pixel(const mw_gl_draw_info_t *draw_info, int16_t client_x, int16_t client_y, mw_hal_lcd_colour_t colour);
static void filled_rectangle(const mw_gl_draw_info_t *draw_info, int16_t client_x, int16_t client_y, int16_t width, int16_t height, mw_hal_lcd_colour_t colour);
static void filled_poly(const mw_gl_draw_info_t *draw_info, uint16_t poly_corners, const int16_t *poly_x, const int16_t *poly_y, int16_t x_offset, int16_t y_offset);
static void arc_bres(const mw_gl_draw_info_t *draw_info, int16_t centre_x, int16_t centre_y, int16_t radius, int16_t start_angle, int16_t end_angle);
static void arc_point(const mw_gl_draw_info_t *draw_info, int16_t centre_x, int16_t centre_y, int16_t x, int16_t y, int16_t start_angle, int16_t end_angle);
static void filled_circle(const mw_gl_draw_info_t *draw_info, int16_t centre_x, int16_t centre_y, int16_t radius);
static void circle_bres(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, int16_t radius);
static void filled_segment(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, int16_t radius, int16_t start_angle, int16_t end_angle, int16_t angle_step_size);
static void draw_character_0_degrees(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, char c);
static void draw_character_90_degrees(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, char c);
static void draw_character_180_degrees(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, char c);
static void draw_character_270_degrees(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, char c);
static void title_font_string(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, const char *s);
static const uint8_t *get_font_data(void);
static void tt_pixel_callback_anti_aliasing(int16_t x, int16_t y, uint8_t count, uint8_t alpha, void *state);
static uint8_t tt_character_callback(int16_t x, int16_t y, mf_char character, void *state);
static void tt_pixel_callback_no_anti_aliasing(int16_t x, int16_t y, uint8_t count, uint8_t alpha, void *state);
static bool tt_line_callback(mf_str line, uint16_t count, void *state);
static bool tt_dummy_line_callback(mf_str line, uint16_t count, void *state);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Draw a pixel using a specified colour rather than a value from the graphics context. 
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param client_x X coordinate relative to the client rect
 * @param client_y Y coordinate relative to the client rect
 * @param colour Colour to draw the pixel
 */
static void pixel(const mw_gl_draw_info_t *draw_info, int16_t client_x, int16_t client_y, mw_hal_lcd_colour_t colour)
{
	int16_t display_x;
	int16_t display_y;
	int16_t root_width = MW_ROOT_WIDTH;
	int16_t root_height = MW_ROOT_HEIGHT;

	MW_ASSERT(draw_info, "Null pointer argument");

	if (client_x >= draw_info->clip_rect.x + draw_info->clip_rect.width)
	{
		return;
	}

	if (client_y >= draw_info->clip_rect.y + draw_info->clip_rect.height)
	{
		return;
	}

	if (client_x < draw_info->clip_rect.x)
	{
		return;
	}

	if (client_y < draw_info->clip_rect.y)
	{
		return;
	}

	display_x = client_x + draw_info->origin_x;
	display_y = client_y + draw_info->origin_y;

	if (display_x >= 0 && display_x < root_width && display_y >= 0 && display_y < root_height)
	{
		mw_hal_lcd_pixel(display_x, display_y, colour);
	}
}

/**
 * Draw a filled rectangle with no border using a specified solid fill colour. 
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param client_x X coordinate of left edge
 * @param client_y Y coordinate of top edge
 * @param width Width of rectangle to draw
 * @param height Height of rectangle to draw
 * @param colour Solid fill colour
 */
static void filled_rectangle(const mw_gl_draw_info_t *draw_info, int16_t client_x, int16_t client_y, int16_t width, int16_t height, mw_hal_lcd_colour_t colour)
{
	int16_t overlap;
	int16_t gl_max_x = MW_GL_MAX_X;
	int16_t gl_max_y = MW_GL_MAX_Y;

	MW_ASSERT(draw_info, "Null pointer argument");

	if (draw_info->clip_rect.width == 0 || draw_info->clip_rect.height == 0)
	{
		return;
	}

	if (client_x < draw_info->clip_rect.x)
	{
		overlap = draw_info->clip_rect.x - client_x;
		width -= overlap;
		client_x = draw_info->clip_rect.x;
	}

	if (client_y < draw_info->clip_rect.y)
	{
		overlap = draw_info->clip_rect.y - client_y;
		height -= overlap;
		client_y = draw_info->clip_rect.y;
	}

	if (client_x + width > draw_info->clip_rect.x + draw_info->clip_rect.width)
	{
		overlap = client_x + width - (draw_info->clip_rect.x + draw_info->clip_rect.width);
		width -= overlap;
	}

	if (client_y + height > draw_info->clip_rect.y + draw_info->clip_rect.height)
	{
		overlap = client_y + height - (draw_info->clip_rect.y + draw_info->clip_rect.height);
		height -= overlap;
	}

	if (width <= 0 || height <= 0)
	{
		return;
	}

	if (draw_info->origin_x + draw_info->clip_rect.x + draw_info->clip_rect.width < 0 ||
			draw_info->origin_y + draw_info->clip_rect.y + draw_info->clip_rect.height < 0)
	{
		return;
	}

	if (draw_info->origin_x + client_x + width < 0 || draw_info->origin_y + client_y + height < 0)
	{
		return;
	}

	if (draw_info->origin_x + draw_info->clip_rect.x > gl_max_x ||
			draw_info->origin_y + draw_info->clip_rect.y > gl_max_y)
	{
		return;
	}

	if (draw_info->origin_x + client_x > gl_max_x || draw_info->origin_y + client_y > gl_max_y)
	{
		return;
	}

	if (draw_info->origin_x + client_x < 0)
	{
		width += draw_info->origin_x;
		client_x -= draw_info->origin_x;
		if (width <= 0)
		{
			return;
		}
	}

	if (draw_info->origin_y + client_y < 0)
	{
		height += draw_info->origin_y;
		client_y -= draw_info->origin_y;
		if (height <= 0)
		{
			return;
		}
	}

	mw_hal_lcd_filled_rectangle(client_x + draw_info->origin_x,
			client_y + draw_info->origin_y,
			width,
			height,
			colour);
}

/**
 * Draw a filled polygon defined by its corners.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param poly_corners The number of corners to the polygon data
 * @param poly_x Array of x coordinates of the corners; size must be same as poly_corners
 * @param poly_y Array of y coordinates of the corners; size must be same as poly_corners 
 * @param x_offset Fixed value to add to every member of poly_x
 * @param y_offset Fixed value to add to every member of poly_y 
 * @param colour Colour to draw the pixel
 */
static void filled_poly(const mw_gl_draw_info_t *draw_info, uint16_t poly_corners, const int16_t *poly_x, const int16_t *poly_y, int16_t x_offset, int16_t y_offset)
{
	uint16_t i;
	uint16_t j;
	int16_t swap;
	uint16_t line_node_count;
	int16_t y;
	int16_t node_x[MW_GL_MAX_POLY_CORNERS - 1U];
	int16_t y_min = INT16_MAX;
	int16_t y_max = INT16_MIN;
	int16_t x;
	float temp_float;

	MW_ASSERT(draw_info, "Null pointer argument");
	MW_ASSERT(poly_x, "Null pointer argument");
	MW_ASSERT(poly_y, "Null pointer argument");
	MW_ASSERT(poly_corners <= MW_GL_MAX_POLY_CORNERS, "Too many points in polygon shape");
	MW_ASSERT(poly_corners >= 3U, "Too few points in polygon shape");

	/* find y range of shape */
	for (i = 0; i < poly_corners; i++)
	{
		if (poly_y[i]<y_min)
		{
			y_min = poly_y[i];
		}
		if (poly_y[i] > y_max)
		{
			y_max = poly_y[i];
		}
	}

	/*  Loop through the rows of the image */
	for (y = y_min; y <= y_max; y++)
	{
		if (y + y_offset > MW_GL_MAX_Y)
		{
			return;
		}

		/* build a list of nodes on this line */
		line_node_count = 0;
		j = poly_corners - 1U;
		for (i = 0U; i  <poly_corners; i++)
		{
			if ((poly_y[i] < y && poly_y[j] >= y) || (poly_y[j] < y && poly_y[i] >= y))
			{
				temp_float = ((float)y - (float)poly_y[i]) / ((float)poly_y[j] - (float)poly_y[i]);
				temp_float *= ((float)poly_x[j] - (float)poly_x[i]);
				node_x[line_node_count++] = poly_x[i] + (int16_t)temp_float;
			}
			j = i;
		}

		/* sort the nodes, via a simple bubble sort */
		if (line_node_count > 1U)
		{
			i = 0U;
			while (i < line_node_count - 1U)
			{
				if (node_x[i] > node_x[i + 1U])
				{
					swap = node_x[i];
					node_x[i] = node_x[i + 1U];
					node_x[i + 1U] = swap;
					if (i > 0U)
					{
						i--;
					}
				}
				else
				{
					i++;
				}
			}
		}

		/* fill the pixels between node pairs */
		for (i = 0; i < line_node_count; i += 2U)
		{
			node_x[i] += x_offset;
			node_x[i + 1U] += x_offset;

			if (node_x[i] > MW_GL_MAX_X)
			{
				break;
			}
			if (node_x[i + 1U] > 0)
			{
				if (node_x[i] < 0)
				{
					node_x[i] = 0;
				}
				if (node_x[i + 1U] > MW_GL_MAX_X)
				{
					node_x[i + 1U] = MW_GL_MAX_Y;
				}
				if (gc.pattern_set)
				{
					for (x = 0; x <= node_x[i + 1U] - node_x[i] + 1; x++)
					{
						mw_gl_solid_fill_pixel(draw_info, x + node_x[i], y + y_offset);
					}
				}
				else
				{
					filled_rectangle(draw_info, node_x[i], y + y_offset, node_x[i + 1U] - node_x[i] + 1, 1 , gc.solid_fill_colour);
				}
			}
		}
	}
}

/**
 * Draw an arc section of a circle calculated using the Bresenham algorithm.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param centre_x X coordinate the centre of the describing circle
 * @param centre_y Y coordinate the centre of the describing circle
 * @param radius Radius of the describing circle
 * @param start_angle Start angle of arc
 * @param end_angle End angle of arc 
 */
static void arc_bres(const mw_gl_draw_info_t *draw_info, int16_t centre_x, int16_t centre_y, int16_t radius, int16_t start_angle, int16_t end_angle)
{
	int16_t x_point = 0;
	int16_t y_point = radius;
	int16_t decision = 1 - radius;

	MW_ASSERT(draw_info, "Null pointer argument");

	if (start_angle < 0)
	{
		start_angle += 360;
	}

	if (end_angle < 0)
	{
		end_angle += 360;
	}

	/* plot top, bottom, left and right */
	arc_point(draw_info, centre_x, centre_y, centre_x, centre_y + radius, start_angle, end_angle);
	arc_point(draw_info, centre_x, centre_y, centre_x, centre_y - radius, start_angle, end_angle);
	arc_point(draw_info, centre_x, centre_y, centre_x + radius, centre_y, start_angle, end_angle);
	arc_point(draw_info, centre_x, centre_y, centre_x - radius, centre_y, start_angle, end_angle);

	while (y_point > x_point)
	{
		if (decision < 0)
		{
			decision += (x_point * 2) + 3;
			x_point++;
		}
		else
		{
			decision += ((x_point - y_point) * 2) + 5;
			x_point++;
			y_point--;
		}

		/* plot all quadrants */
		arc_point(draw_info, centre_x, centre_y, centre_x + x_point, centre_y + y_point, start_angle, end_angle);
		arc_point(draw_info, centre_x, centre_y, centre_x - x_point, centre_y + y_point, start_angle, end_angle);
		arc_point(draw_info, centre_x, centre_y, centre_x + x_point, centre_y - y_point, start_angle, end_angle);
		arc_point(draw_info, centre_x, centre_y, centre_x - x_point, centre_y - y_point, start_angle, end_angle);
		arc_point(draw_info, centre_x, centre_y, centre_x + y_point, centre_y + x_point, start_angle, end_angle);
		arc_point(draw_info, centre_x, centre_y, centre_x - y_point, centre_y + x_point, start_angle, end_angle);
		arc_point(draw_info, centre_x, centre_y, centre_x + y_point, centre_y - x_point, start_angle, end_angle);
		arc_point(draw_info, centre_x, centre_y, centre_x - y_point, centre_y - x_point, start_angle, end_angle);
	}
}

/**
 * Plot a single point in an arc clipped to start and end angles of the arc
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param centre_x X coordinate the centre of the describing circle
 * @param centre_y Y coordinate the centre of the describing circle
 * @param x X coordinate of the point to plot
 * @param y Y coordinate of the point to plot 
 * @param start_angle Start angle of arc
 * @param end_angle End angle of arc 
 */
static void arc_point(const mw_gl_draw_info_t *draw_info, int16_t centre_x, int16_t centre_y, int16_t x, int16_t y, int16_t start_angle, int16_t end_angle)
{
	float temp_float;
	int16_t temp_1_int16;
	int16_t temp_2_int16;

	MW_ASSERT(draw_info, "Null pointer argument");

	/* calculate the angle the current point makes with the circle centre */
	temp_1_int16 = centre_y - y;
	temp_2_int16 = centre_x - x;

	temp_float = DEGREES_IN_RAD * atan2f((float)temp_1_int16, (float)temp_2_int16);
	int16_t angle = (int16_t)temp_float - 90;
	if (angle < 0)
	{
		angle += 360;
	}

	if (end_angle > start_angle)
	{
		if (angle >= start_angle && angle < end_angle)
		{
			mw_gl_fg_pixel(draw_info, x, y);
		}
	}
	else
	{
		if (!(angle >= end_angle && angle < start_angle))
		{
			mw_gl_fg_pixel(draw_info, x, y);
		}
	}
}

/**
 * Draw a filled circle with the fill style and colour according to the graphics context
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param centre_x X coordinate centre of circle
 * @param centre_y Y coordinate centre of circle
 * @param radius Radius of circle
 */
static void filled_circle(const mw_gl_draw_info_t *draw_info, int16_t centre_x, int16_t centre_y, int16_t radius)
{
	int16_t x_point = 0;
	int16_t y_point = radius;
	int16_t decision = 1 - radius;
	int16_t y;

	MW_ASSERT(draw_info, "Null pointer argument");

	/* plot centre line */
	if (gc.pattern_set)
	{
		for (y = -radius; y <= radius + 1; y++)
		{
			mw_gl_solid_fill_pixel(draw_info, centre_x, centre_y + y);
		}
	}
	else
	{
		filled_rectangle(draw_info, centre_x, centre_y - radius, 1, radius * 2 + 1, gc.solid_fill_colour);
	}

	while (y_point > x_point)
	{
		if (decision < 0)
		{
			decision += (x_point * 2) + 3;
			x_point++;
		}
		else
		{
			decision += ((x_point - y_point) * 2) + 5;
			x_point++;
			y_point--;
		}

		/* plot all quadrants */
		if (gc.pattern_set)
		{
			for (y = 0; y <= y_point * 2 + 1; y++)
			{
				mw_gl_solid_fill_pixel(draw_info, centre_x + x_point, centre_y - y_point + y);
			}
			for (y = 0; y <= y_point * 2 + 1; y++)
			{
				mw_gl_solid_fill_pixel(draw_info, centre_x - x_point, centre_y - y_point + y);
			}
			for (y = 0; y <= x_point * 2 + 1; y++)
			{
				mw_gl_solid_fill_pixel(draw_info, centre_x + y_point, centre_y - x_point + y);
			}
			for (y = 0; y <= x_point * 2 + 1; y++)
			{
				mw_gl_solid_fill_pixel(draw_info, centre_x - y_point, centre_y - x_point + y);
			}
		}
		else
		{
			filled_rectangle(draw_info, centre_x + x_point, centre_y - y_point, 1, y_point * 2 + 1, gc.solid_fill_colour);
			filled_rectangle(draw_info, centre_x - x_point, centre_y - y_point, 1, y_point * 2 + 1, gc.solid_fill_colour);
			filled_rectangle(draw_info, centre_x + y_point, centre_y - x_point, 1, x_point * 2 + 1, gc.solid_fill_colour);
			filled_rectangle(draw_info, centre_x - y_point, centre_y - x_point, 1, x_point * 2 + 1, gc.solid_fill_colour);
		}
	}
}

/**
 * Draw an empty circle with using the bresenham algorithm
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x X coordinate centre of circle
 * @param y Y coordinate centre of circle
 * @param Radius radius of circle
 */
static void circle_bres(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, int16_t radius)
{
	int16_t x_point = 0;
	int16_t y_point = radius;
	int16_t decision = 1 - radius;

	MW_ASSERT(draw_info, "Null pointer argument");

	/* plot top, bottom, left and right */
	mw_gl_fg_pixel(draw_info, x, y + radius);
	mw_gl_fg_pixel(draw_info, x, y - radius);
	mw_gl_fg_pixel(draw_info, x + radius, y);
	mw_gl_fg_pixel(draw_info, x - radius, y);

	while (y_point > x_point)
	{
		if (decision < 0)
		{
			decision += (x_point * 2) + 3;
			x_point++;
		}
		else
		{
			decision += ((x_point - y_point) * 2) + 5;
			x_point++;
			y_point--;
		}

		/* plot all quadrants */
		mw_gl_fg_pixel(draw_info, x + x_point, y + y_point);
		mw_gl_fg_pixel(draw_info, x - x_point, y + y_point);
		mw_gl_fg_pixel(draw_info, x + x_point, y - y_point);
		mw_gl_fg_pixel(draw_info, x - x_point, y - y_point);
		mw_gl_fg_pixel(draw_info, x + y_point, y + x_point);
		mw_gl_fg_pixel(draw_info, x - y_point, y + x_point);
		mw_gl_fg_pixel(draw_info, x + y_point, y - x_point);
		mw_gl_fg_pixel(draw_info, x - y_point, y - x_point);
	}
}

/**
 * Draw a filled segment of a circle using the fill colour and style from the graphics context
 * 
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x X coordinate centre of the describing circle
 * @param y Y coordinate centre of the describing circle
 * @param start_angle Start angle of the segment, clockwise from 0 which is vertically up, in degrees
 * @param end_angle End angle of the segment, clockwise from 0 which is vertically up, in degrees 
 * @param step_size Step size in degrees of the describing circle edge; straight lines will be drawn for each point of the radius at step size angles
 * @param radius Radius of the describing circle
 */
static void filled_segment(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, int16_t radius, int16_t start_angle, int16_t end_angle, int16_t angle_step_size)
{
	int16_t old_x;
	int16_t old_y;
	int16_t i;
	float angle;
	int16_t triangle_corners_x[3];
	int16_t triangle_corners_y[3];
	float temp_float;

	MW_ASSERT(draw_info, "Null pointer argument");

	temp_float = sinf((float)start_angle / DEGREES_IN_RAD) * (float)radius;
	old_x = x + (int16_t)temp_float;
	temp_float = cosf((float)start_angle / DEGREES_IN_RAD) * (float)radius;
	old_y = y - (int16_t)temp_float;

	triangle_corners_x[0] = x;
	triangle_corners_y[0] = y;

	if (start_angle > end_angle)
	{
		end_angle += 360;
	}

	for (i = start_angle + angle_step_size; i <= end_angle; i += angle_step_size)
	{
		angle = (float)i / DEGREES_IN_RAD;
		temp_float = sinf(angle) * (float)radius;
		triangle_corners_x[1] = x + (int16_t)temp_float;
		temp_float = cosf(angle) * (float)radius;
		triangle_corners_y[1] = y - (int16_t)temp_float;
		triangle_corners_x[2] = old_x;
		triangle_corners_y[2] = old_y;

		filled_poly(draw_info, 3, triangle_corners_x, triangle_corners_y, 0, 0);

		old_x = triangle_corners_x[1];
		old_y = triangle_corners_y[1];
	}

	i -= angle_step_size;
	if ( i <end_angle)
	{
		temp_float = sinf((float)end_angle / DEGREES_IN_RAD) * (float)radius;
		triangle_corners_x[1] = x + (int16_t)temp_float;
		temp_float = cosf((float)end_angle / DEGREES_IN_RAD) * (float)radius;
		triangle_corners_y[1] = y - (int16_t)temp_float;
		temp_float = sinf((float)i / DEGREES_IN_RAD) * (float)radius;
		triangle_corners_x[2] = x + (int16_t)temp_float;
		temp_float = cosf((float)i / DEGREES_IN_RAD) * (float)radius;
		triangle_corners_y[2] = y - (int16_t)temp_float;

		filled_poly(draw_info, 3, triangle_corners_x, triangle_corners_y, 0, 0);
	}
}

/**
 * Draw a single fixed width character at 0 degrees rotation.
 * Foreground colour, background colour, font and transparency controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x Coordinate of the left edge of the rectangle containing the character
 * @param y Coordinate of the top edge of the rectangle containing the character
 * @param c The character
 */
static void draw_character_0_degrees(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, char c)
{
	int16_t char_x;
	int16_t char_y;
	uint32_t mask;
	uint32_t word;
	int16_t character_byte_width;
	int16_t byte_pos;
	int16_t byte;
	int16_t font_width = mw_gl_get_font_width();
	int16_t font_height = mw_gl_get_font_height();
	int16_t i;

	if (x >= draw_info->clip_rect.x + draw_info->clip_rect.width ||
			y >= draw_info->clip_rect.y + draw_info->clip_rect.height ||
			x + font_width + 1 <= draw_info->clip_rect.x ||
			y + font_height + 1 <= draw_info->clip_rect.y)
	{
		return;
	}

	if (gc.bg_transparent == MW_GL_BG_NOT_TRANSPARENT)
	{
		filled_rectangle(draw_info,
				x,
				y,
				font_width + 1,
				font_height + 1,
				gc.bg_colour);
	}

	character_byte_width = font_width / 8 + (int16_t)(font_width % 8 > 0 ? 1 : 0);
	byte_pos = ((int16_t)c - (int16_t)' ') * font_height * character_byte_width;

	for (char_y = 0; char_y < mw_gl_get_font_height(); char_y++)
	{
		word = 0U;
		for (byte = 0; byte < character_byte_width; byte++)
		{
			word <<= 8U;
			word |= (uint32_t)get_font_data()[byte_pos];
			byte_pos++;
		}

		for (i = 0; i < 4 - character_byte_width; i++)
		{
			word <<= 8;
		}
		mask = 0x80000000U;

		for (char_x = 0; char_x < font_width; char_x++)
		{
			if ((word & mask) == mask)
			{
				mw_gl_fg_pixel(draw_info, x + char_x, y + char_y);
			}

			mask >>= 1U;
		}
	}
}

/**
 * Draw a single fixed width character at 90 degrees rotation.
 * Foreground colour, background colour, font and transparency controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x Coordinate of the left edge of the rectangle containing the character
 * @param y Coordinate of the top edge of the rectangle containing the character
 * @param c The character
 */
static void draw_character_90_degrees(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, char c)
{
	int16_t char_x;
	int16_t char_y;
	uint32_t mask;
	uint32_t word;
	int16_t character_byte_width;
	int16_t byte_pos;
	int16_t byte;
	int16_t font_width = mw_gl_get_font_width();
	int16_t font_height = mw_gl_get_font_height();
	int16_t i;

	if (x - font_height >= draw_info->clip_rect.x + draw_info->clip_rect.width ||
			y >= draw_info->clip_rect.y + draw_info->clip_rect.height ||
			x <= draw_info->clip_rect.x ||
			y + font_width <= draw_info->clip_rect.y)
	{
		return;
	}

	if (gc.bg_transparent == MW_GL_BG_NOT_TRANSPARENT)
	{
		filled_rectangle(draw_info,
				x - font_height,
				y,
				font_height + 1,
				font_width + 1,
				gc.bg_colour);
	}

	character_byte_width = font_width / 8 + (int16_t)(font_width % 8 > 0 ? 1 : 0);
	byte_pos = ((int16_t)c - (int16_t)' ') * font_height * character_byte_width;

	for (char_y = 0; char_y < font_height; char_y++)
	{
		word = 0U;
		for (byte = 0; byte < character_byte_width; byte++)
		{
			word <<= 8U;
			word |= (uint32_t)get_font_data()[byte_pos];
			byte_pos++;
		}

		for (i = 0; i < 4 - character_byte_width; i++)
		{
			word <<= 8;
		}
		mask = 0x80000000U;

		for (char_x = 0; char_x < font_width; char_x++)
		{
			if ((word & mask) == mask)
			{
	   			mw_gl_fg_pixel(draw_info, x - char_y, y + char_x);
			}

			mask >>= 1U;
		}
	}
}

/**
 * Draw a single fixed width character at 180 degrees rotation.
 * Foreground colour, background colour, font and transparency controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x Coordinate of the left edge of the rectangle containing the character
 * @param y Coordinate of the top edge of the rectangle containing the character
 * @param c The character
 */
static void draw_character_180_degrees(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, char c)
{
	int16_t char_x;
	int16_t char_y;
	uint32_t mask;
	uint32_t word;
	int16_t character_byte_width;
	int16_t byte_pos;
	int16_t byte;
	int16_t font_width = mw_gl_get_font_width();
	int16_t font_height = mw_gl_get_font_height();
	int16_t i;

	if (x <= draw_info->clip_rect.x ||
			y <= draw_info->clip_rect.y ||
			x - font_width + 1 >= draw_info->clip_rect.x + draw_info->clip_rect.width ||
			y - font_height + 1 >= draw_info->clip_rect.y +  draw_info->clip_rect.height)
	{
		return;
	}

	if (gc.bg_transparent == MW_GL_BG_NOT_TRANSPARENT)
	{
		filled_rectangle(draw_info,
				x - font_width,
				y - font_height,
				font_width + 1,
				mw_gl_get_font_height() + 1,
				gc.bg_colour);
	}

	character_byte_width = font_width / 8 + (int16_t)(font_width % 8 > 0 ? 1 : 0);
	byte_pos = ((int16_t)c - (int16_t)' ') * font_height * character_byte_width;

	for (char_y = 0; char_y < font_height; char_y++)
	{
		word = 0U;
		for (byte = 0; byte < character_byte_width; byte++)
		{
			word <<= 8U;
			word |= (uint32_t)get_font_data()[byte_pos];
			byte_pos++;
		}

		for (i = 0; i < 4 - character_byte_width; i++)
		{
			word <<= 8;
		}
		mask = 0x80000000U;

		for (char_x = 0; char_x < font_width; char_x++)
		{
			if ((word & mask) == mask)
			{
				mw_gl_fg_pixel(draw_info, x - char_x, y - char_y);
			}

			mask >>= 1U;
		}
	}
}

/**
 * Draw a single fixed width character at 270 degrees rotation.
 * Foreground colour, background colour, font and transparency controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x Coordinate of the left edge of the rectangle containing the character
 * @param y Coordinate of the top edge of the rectangle containing the character
 * @param c The character
 */
static void draw_character_270_degrees(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, char c)
{
	int16_t char_x;
	int16_t char_y;
	uint32_t mask;
	uint32_t word;
	int16_t character_byte_width;
	int16_t byte_pos;
	int16_t byte;
	int16_t font_width = mw_gl_get_font_width();
	int16_t font_height = mw_gl_get_font_height();
	int16_t i;

	if (x >= draw_info->clip_rect.x + draw_info->clip_rect.width ||
			y <= draw_info->clip_rect.y ||
			x + font_height + 1 <= draw_info->clip_rect.x ||
			y - font_width + 1 >= draw_info->clip_rect.y +  draw_info->clip_rect.height)
	{
		return;
	}

	if (gc.bg_transparent == MW_GL_BG_NOT_TRANSPARENT)
	{
		filled_rectangle(draw_info,
				x,
				y - font_width,
				font_height + 1,
				font_width + 1,
				gc.bg_colour);
	}

	character_byte_width = font_width / 8 + (int16_t)(font_width % 8 > 0 ? 1 : 0);
	byte_pos = ((int16_t)c - (int16_t)' ') * font_height * character_byte_width;

	for (char_y = 0; char_y < mw_gl_get_font_height(); char_y++)
	{
		word = 0U;
		for (byte = 0; byte < character_byte_width; byte++)
		{
			word <<= 8U;
			word |= (uint32_t)get_font_data()[byte_pos];
			byte_pos++;
		}

		for (i = 0; i < 4 - character_byte_width; i++)
		{
			word <<= 8;
		}
		mask = 0x80000000U;

		for (char_x = 0; char_x < font_width; char_x++)
		{
			if ((word & mask) == mask)
			{
	   			mw_gl_fg_pixel(draw_info, x + char_y, y - char_x);
			}

			mask >>= 1U;
		}
	}
}

/**
 * Draw a string of proportional title font string. Foreground colour, background colour, rotation and transparency controlled by gc.
 *
 * @param draw_info Reference frame origin coordinates and clip region rect
 * @param x Coordinate of the left edge of the rectangle containing the first character
 * @param y Coordinate of the top edge of the rectangle containing the first character
 * @param s Pointer to the null terminated string containing characters
 */
static void title_font_string(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, const char *s)
{
	size_t length = strlen(s);
	uint8_t mask;
	int16_t start_pos_in_bitmap;
	int16_t end_pos_in_bitmap;
	int16_t bitmap_x;
	int16_t bitmap_y;
	uint8_t i;
	uint8_t byte_from_bitmap;
	char c;
	int16_t next_char_start_position_along_string = 0;
	int16_t position_across_character;
	int16_t string_width_pixels;
	uint16_t temp_uint16;

	if (draw_info == NULL || s == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	string_width_pixels = mw_gl_get_string_width_pixels(s);

	switch (gc.text_rotation)
	{
	case MW_GL_TEXT_ROTATION_0:
		/* check for completely off rect */
		if (x >= draw_info->clip_rect.x + draw_info->clip_rect.width ||
				y >= draw_info->clip_rect.y + draw_info->clip_rect.height ||
				x + string_width_pixels <= draw_info->clip_rect.x ||
				y + MW_GL_TITLE_FONT_HEIGHT <= draw_info->clip_rect.y)
		{
			return;
		}

		if (gc.bg_transparent == MW_GL_BG_NOT_TRANSPARENT)
		{
			filled_rectangle(draw_info,
					x,
					y,
					string_width_pixels,
					MW_GL_TITLE_FONT_HEIGHT,
					gc.bg_colour);
		}
		break;

	case MW_GL_TEXT_ROTATION_90:
		/* check for completely off rect */
		if (x - MW_GL_TITLE_FONT_HEIGHT >= draw_info->clip_rect.x + draw_info->clip_rect.width ||
				y >= draw_info->clip_rect.y + draw_info->clip_rect.height ||
				x <= draw_info->clip_rect.x ||
				y + string_width_pixels <= draw_info->clip_rect.y)
		{
			return;
		}

		if (gc.bg_transparent == MW_GL_BG_NOT_TRANSPARENT)
		{
			filled_rectangle(draw_info,
					x - MW_GL_TITLE_FONT_HEIGHT + 1,
					y,
					MW_GL_TITLE_FONT_HEIGHT,
					string_width_pixels,
					gc.bg_colour);
		}
		break;

	case MW_GL_TEXT_ROTATION_180:
		/* check for completely off rect */
		if (x <= draw_info->clip_rect.x ||
				y <= draw_info->clip_rect.y ||
				x - string_width_pixels >= draw_info->clip_rect.x  + draw_info->clip_rect.width ||
				y - MW_GL_TITLE_FONT_HEIGHT >= draw_info->clip_rect.y + draw_info->clip_rect.height)
		{
			return;
		}

		if (gc.bg_transparent == MW_GL_BG_NOT_TRANSPARENT)
		{
			filled_rectangle(draw_info,
					x - string_width_pixels + 1,
					y - MW_GL_TITLE_FONT_HEIGHT + 1,
					string_width_pixels,
					MW_GL_TITLE_FONT_HEIGHT,
					gc.bg_colour);
		}
		break;

	case MW_GL_TEXT_ROTATION_270:
		/* check for completely off rect */
		if (x >= draw_info->clip_rect.x + draw_info->clip_rect.width ||
				y <= draw_info->clip_rect.y ||
				x + MW_GL_TITLE_FONT_HEIGHT <= draw_info->clip_rect.x ||
				y - string_width_pixels >= draw_info->clip_rect.y +  draw_info->clip_rect.height)
		{
			return;
		}

		if (gc.bg_transparent == MW_GL_BG_NOT_TRANSPARENT)
		{
			filled_rectangle(draw_info,
					x,
					y - string_width_pixels + 1,
					MW_GL_TITLE_FONT_HEIGHT,
					string_width_pixels,
					gc.bg_colour);
		}
		break;

	default:
		MW_ASSERT((bool)false, "Unknown text rotation");
		break;
	}

	for (i = 0U; i < length; i++)
	{
		for (bitmap_y = 0; bitmap_y < MW_GL_TITLE_FONT_HEIGHT; bitmap_y++)
		{
			c = s[i];
			if (c < ' ' || c > '~')
			{
				c = '*';
			}
			c -= 32;

			start_pos_in_bitmap = (int16_t)mw_title_font_positions[(uint8_t)c];
			end_pos_in_bitmap = (int16_t)mw_title_font_positions[(uint8_t)c + 1U];

			mask = 0x80U;
			temp_uint16 = mw_title_font_positions[(uint8_t)c] & 0x07U;
			/* the next line is MISRA compliant despite a warning because the shift operand cannot be > 7 */
			mask >>= (uint8_t)temp_uint16;

			position_across_character = 0;
			for (bitmap_x = start_pos_in_bitmap; bitmap_x < end_pos_in_bitmap; bitmap_x++)
			{
				byte_from_bitmap = mw_title_font_bitmap[((uint16_t)bitmap_x >> 3U) + (uint16_t)bitmap_y * 87U];

				if ((byte_from_bitmap & mask) == 0U)
				{
					switch (gc.text_rotation)
					{
					case MW_GL_TEXT_ROTATION_0:
						mw_gl_fg_pixel(draw_info,
								x + next_char_start_position_along_string + position_across_character ,
								y + bitmap_y);
						break;

					case MW_GL_TEXT_ROTATION_90:
						mw_gl_fg_pixel(draw_info,
								x - bitmap_y,
								y + next_char_start_position_along_string + position_across_character);
						break;

					case MW_GL_TEXT_ROTATION_180:
						mw_gl_fg_pixel(draw_info,
								x - next_char_start_position_along_string - position_across_character,
								y - bitmap_y);

						break;

					case MW_GL_TEXT_ROTATION_270:
						mw_gl_fg_pixel(draw_info,
								x + bitmap_y,
								y - next_char_start_position_along_string - position_across_character);
						break;

					default:
						/* keep MISRA happy */
						break;
					}
				}

				mask >>= 1U;
				if (mask == 0U)
				{
					mask = 0x80U;
				}
				position_across_character++;
			}
		}
		next_char_start_position_along_string += position_across_character;
	}
}

/**
 * Get a pointer to a font's bitmap for fixed width fonts
 *
 * @return Pointer to bit map data
 */
static const uint8_t *get_font_data(void)
{
	switch (gc.font)
	{
	case MW_GL_FONT_9:
		return (Font9.table);
		break;

#ifdef MW_FONT_12_INCLUDED
	case MW_GL_FONT_12:
		return (Font12.table);
		break;
#endif

#ifdef MW_FONT_16_INCLUDED
	case MW_GL_FONT_16:
		return (Font16.table);
		break;
#endif

#ifdef MW_FONT_20_INCLUDED
	case MW_GL_FONT_20:
		return (Font20.table);
		break;
#endif

#ifdef MW_FONT_24_INCLUDED
	case MW_GL_FONT_24:
		return (Font24.table);
		break;
#endif

	default:
		return (NULL);
		break;
	}

	return (NULL);
}

/**
 * Draw alpha blended true type font pixels with anti-aliasing
 *
 * @param x The x coordinate of the left most pixel
 * @param y The y coordinate of all the pixels
 * @param count The number of pixels to draw
 * @alpha Alpha blending value between background colour and foreground colour
 * @param state Pointer to font rendering state structure
 */
static void tt_pixel_callback_anti_aliasing(int16_t x, int16_t y, uint8_t count, uint8_t alpha, void *state)
{
	uint8_t alpha_red;
	uint8_t alpha_green;
	uint8_t alpha_blue;

	/* get tt font rendering state */
	tt_font_state_t *tt_font_state = (tt_font_state_t *)state;

	/* check y value is still in box */
    if (y - tt_font_state->vert_scroll_pixels >= tt_font_state->bottom)
    {
    	return;
    }

    if (y - tt_font_state->vert_scroll_pixels < 0)
    {
    	return;
    }

    /* do all pixels */
	y = y - tt_font_state->vert_scroll_pixels;

	/* calculate alpha blended colour values */
	alpha_red = ((tt_font_state->fg_red * alpha) + (tt_font_state->bg_red * ((uint8_t)UINT8_MAX - alpha))) / (uint8_t)UINT8_MAX;
	alpha_green = ((tt_font_state->fg_green * alpha) + (tt_font_state->bg_green * ((uint8_t)UINT8_MAX - alpha))) / (uint8_t)UINT8_MAX;
	alpha_blue = ((tt_font_state->fg_blue * alpha) + (tt_font_state->bg_blue * ((uint8_t)UINT8_MAX - alpha))) / (uint8_t)UINT8_MAX;

    while (count-- > 0U)
    {
    	/* set pixel colour with this value */
    	mw_gl_set_fg_colour(((mw_hal_lcd_colour_t)alpha_red << 16U) +
    			((mw_hal_lcd_colour_t)alpha_green << 8U) +
				(mw_hal_lcd_colour_t)alpha_blue);

    	/* draw pixel */
        mw_gl_fg_pixel(tt_font_state->draw_info, x, y);

        /* move on to next pixel */
        x++;
    }
}


/**
 * Draw a true type font character
 *
 * @param x The x position of the left edge of the character to render
 * @param y The x position of the top edge of the character to render
 * @param character The character to plot
 * @param state Pointer to font rendering state structure
 */
static uint8_t tt_character_callback(int16_t x, int16_t y, mf_char character, void *state)
{
	/* get tt font rendering state */
	tt_font_state_t *tt_font_state = (tt_font_state_t *)state;

	/* render the character with anti-aliasing */
	if ((tt_font_state->font->flags & MF_FONT_FLAG_BW) == MF_FONT_FLAG_BW)
	{
		return (mf_render_character(tt_font_state->font, x, y, character, tt_pixel_callback_no_anti_aliasing, state));
	}
	else
	{
		return (mf_render_character(tt_font_state->font, x, y, character, tt_pixel_callback_anti_aliasing, state));
	}
}

/**
 * Draw a monochrome true type font pixels without anti-aliasing
 *
 * @param x The x coordinate of the left most pixel
 * @param y The y coordinate of all the pixels
 * @param count The number of pixels to draw
 * @alpha Alpha blending value between background colour and foreground colour
 * @param state Pointer to font rendering state structure
 */
static void tt_pixel_callback_no_anti_aliasing(int16_t x, int16_t y, uint8_t count, uint8_t alpha, void *state)
{
    (void)alpha;

	/* get tt font rendering state */
	tt_font_state_t *tt_font_state = (tt_font_state_t *)state;

	/* check y value is still in box */
    if ((int16_t)(y - tt_font_state->vert_scroll_pixels) >= (int16_t)tt_font_state->bottom)
    {
    	return;
    }

    if ((int16_t)(y - tt_font_state->vert_scroll_pixels) < 0)
    {
    	return;
    }

    /* do all pixels */
	y = y - tt_font_state->vert_scroll_pixels;

    while (count-- > 0U)
    {
    	/* draw pixel */
        mw_gl_fg_pixel(tt_font_state->draw_info, x, y);

        /* move on to next pixel */
        x++;
    }
}

/**
 * Draw a true type font justified line
 *
 * @param line Pointer to start of the text to render in this line
 * @param count Number of characters to render in this line
 * @param state Pointer to font rendering state structure
 * @return true if rendering should stop as reached bottom of box, else false to continue rendering next line
 */
static bool tt_line_callback(mf_str line, uint16_t count, void *state)
{
	/* get tt font rendering state */
	tt_font_state_t *tt_font_state = (tt_font_state_t *)state;

	/* draw background for this line, gc already set up */
	mw_gl_rectangle(tt_font_state->draw_info,
			tt_font_state->bounding_box.x,
			tt_font_state->bounding_box.y,
			tt_font_state->bounding_box.width,
			(int16_t)tt_font_state->font->line_height);

	/* now check justification */
    if (tt_font_state->justification == MW_GL_TT_FULLY_JUSTIFIED)
    {
		mf_render_justified(tt_font_state->font,
				tt_font_state->bounding_box.x,
				tt_font_state->bounding_box.y,
				tt_font_state->bounding_box.width,
				line,
				count,
				tt_character_callback,
				state);
    }
    else if (tt_font_state->justification == MW_GL_TT_LEFT_JUSTIFIED)
    {
    	mf_render_aligned(tt_font_state->font,
    			tt_font_state->bounding_box.x,
				tt_font_state->bounding_box.y,
				MF_ALIGN_LEFT,
    			line,
    			count,
				tt_character_callback,
    			state);
    }
    else if (tt_font_state->justification == MW_GL_TT_RIGHT_JUSTIFIED)
    {
    	mf_render_aligned(tt_font_state->font,
    			tt_font_state->bounding_box.x + tt_font_state->bounding_box.width,
				tt_font_state->bounding_box.y,
				MF_ALIGN_RIGHT,
    			line,
    			count,
				tt_character_callback,
    			state);
    }
    else if (tt_font_state->justification == MW_GL_TT_CENTRE_JUSTIFIED)
    {
    	mf_render_aligned(tt_font_state->font,
    			tt_font_state->bounding_box.x + (tt_font_state->bounding_box.width / 2),
				tt_font_state->bounding_box.y,
				MF_ALIGN_CENTER,
    			line,
    			count,
				tt_character_callback,
    			state);
    }
    else
    {
    	MW_ASSERT((bool)false, "Invalid justification");
    }

    /* move next y value on by font height */
    tt_font_state->bounding_box.y += (int16_t)tt_font_state->font->line_height;

    /* check if y value is still in the text box */
    if (tt_font_state->bounding_box.y - tt_font_state->vert_scroll_pixels > tt_font_state->bottom)
    {
    	return (false);
    }

	return (true);
}

/**
 * Do a dummy draw of a true type font justified line and increment line counter
 *
 * @param line The text to dummy render in this line
 * @param count Unused
 * @param state Pointer to font rendering state structure
 */
static bool tt_dummy_line_callback(mf_str line, uint16_t count, void *state)
{
    (void)count;
    (void)line;

	/* get tt font rendering state */
	tt_font_state_t *tt_font_state = (tt_font_state_t *)state;

    /* increment line count */
    tt_font_state->rendered_line_count++;

	return (true);
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_gl_init(void)
{
	gc.fg_colour = MW_HAL_LCD_WHITE;
	gc.bg_colour = MW_HAL_LCD_BLACK;
	gc.solid_fill_colour = MW_HAL_LCD_WHITE;
	gc.line = MW_GL_SOLID_LINE;
	gc.border = MW_GL_BORDER_ON;
	gc.fill = MW_GL_NO_FILL;
	gc.pattern_set = false;
	gc.bg_transparent = MW_GL_BG_NOT_TRANSPARENT;
	gc.font = MW_GL_FONT_9;
	gc.text_rotation = MW_GL_TEXT_ROTATION_0;
}

mw_gl_gc_t *mw_gl_get_gc(void)
{
	return (&gc);
}

void mw_gl_set_fg_colour(mw_hal_lcd_colour_t colour)
{
	gc.fg_colour = colour;
}

void mw_gl_set_bg_colour(mw_hal_lcd_colour_t colour)
{
	gc.bg_colour = colour;
}

void mw_gl_set_solid_fill_colour(mw_hal_lcd_colour_t colour)
{
	gc.solid_fill_colour = colour;
}

void mw_gl_set_line(mw_gl_line_t line)
{
	gc.line = line;
}

void mw_gl_set_pattern(const mw_gl_pattern_t pattern)
{
	(void)memcpy((gc.pattern), (pattern), (sizeof(mw_gl_pattern_t)));
	gc.pattern_set = true;
}

void mw_gl_clear_pattern(void)
{
	gc.pattern_set = false;
}

void mw_gl_set_border(mw_gl_border_t border)
{
	gc.border = border;
}

void mw_gl_set_fill(mw_gl_fill_t fill)
{
	gc.fill = fill;
}

void mw_gl_set_bg_transparency(mw_gl_bg_transparent_t bg_transparent)
{
	gc.bg_transparent = bg_transparent;
}

void mw_gl_set_font(mw_gl_font_t font)
{
#ifndef MW_FONT_12_INCLUDED
	MW_ASSERT(font != MW_GL_FONT_12, "Font not included");
#endif

#ifndef MW_FONT_16_INCLUDED
	MW_ASSERT(font != MW_GL_FONT_16, "Font not included");
#endif

#ifndef MW_FONT_20_INCLUDED
	MW_ASSERT(font != MW_GL_FONT_20, "Font not included");
#endif

#ifndef MW_FONT_20_INCLUDED
	MW_ASSERT(font != MW_GL_FONT_20, "Font not included");
#endif

#ifndef MW_FONT_24_INCLUDED
	MW_ASSERT(font != MW_GL_FONT_24, "Font not included");
#endif

	MW_ASSERT(font == MW_GL_FONT_9 ||
			font == MW_GL_FONT_12 ||
			font == MW_GL_FONT_16 ||
			font == MW_GL_FONT_20 ||
			font == MW_GL_FONT_24 ||
			font == MW_GL_TITLE_FONT,
			"Unknown font");

	gc.font = font;
}

void mw_gl_set_text_rotation(mw_gl_text_rotation_t text_rotation)
{
	gc.text_rotation = text_rotation;
}

int16_t mw_gl_get_font_width(void)
{
	switch (gc.font)
	{
	case MW_GL_FONT_9:
		return ((int16_t)Font9.Width);
		break;

#ifdef MW_FONT_12_INCLUDED
	case MW_GL_FONT_12:
		return ((int16_t)Font12.Width);
		break;
#endif

#ifdef MW_FONT_16_INCLUDED
	case MW_GL_FONT_16:
		return ((int16_t)Font16.Width);
		break;
#endif

#ifdef MW_FONT_20_INCLUDED
	case MW_GL_FONT_20:
		return ((int16_t)Font20.Width);
		break;
#endif

#ifdef MW_FONT_24_INCLUDED
	case MW_GL_FONT_24:
		return ((int16_t)Font24.Width);
		break;
#endif

	default:
		return (0);
		break;
	}

	return (0);
}

int16_t mw_gl_get_font_height(void)
{
	switch (gc.font)
	{
	case MW_GL_FONT_9:
		return ((int16_t)Font9.Height);
		break;

#ifdef MW_FONT_12_INCLUDED
	case MW_GL_FONT_12:
		return ((int16_t)Font12.Height);
		break;
#endif

#ifdef MW_FONT_16_INCLUDED
	case MW_GL_FONT_16:
		return ((int16_t)Font16.Height);
		break;
#endif

#ifdef MW_FONT_20_INCLUDED
	case MW_GL_FONT_20:
		return ((int16_t)Font20.Height);
		break;
#endif

#ifdef MW_FONT_24_INCLUDED
	case MW_GL_FONT_24:
		return ((int16_t)Font24.Height);
		break;
#endif

	case MW_GL_TITLE_FONT:
		return (MW_GL_TITLE_FONT_HEIGHT);
		break;

	default:
		return (0);
		break;
	}

	return (0);
}

void mw_gl_solid_fill_pixel(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y)
{
	uint16_t mask;
	uint16_t pattern_y;

	if (draw_info == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}
	
	if (gc.pattern_set)
	{
		/* the next line is MISRA compliant despite the warning because the shift operand cannot be > 15 */
		mask = 0x8000U >> ((uint16_t)x & 0x0FU);
		pattern_y = (uint16_t)y & 0x0FU;

		if ((gc.pattern[pattern_y] & mask) == mask)
		{
			mw_gl_fg_pixel(draw_info, x, y);
		}
		else
		{
			mw_gl_bg_pixel(draw_info, x, y);
		}
	}
	else
	{
		pixel(draw_info, x, y, gc.solid_fill_colour);
	}
}

void mw_gl_fg_pixel(const mw_gl_draw_info_t *draw_info, int16_t client_x, int16_t client_y)
{
	if (draw_info == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	pixel(draw_info, client_x, client_y, gc.fg_colour);
}

void mw_gl_bg_pixel(const mw_gl_draw_info_t *draw_info, int16_t client_x, int16_t client_y)
{
	if (draw_info == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	if (gc.bg_transparent == MW_GL_BG_NOT_TRANSPARENT)
	{
		pixel(draw_info, client_x, client_y, gc.bg_colour);
	}
}

void mw_gl_hline(const mw_gl_draw_info_t *draw_info, int16_t x_start, int16_t x_end, int16_t y)
{
	int16_t temp;
	int16_t x;
	uint16_t mask = 0x8000U;

	if (draw_info == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	if (x_start > x_end)
	{
		temp = x_end;
		x_end = x_start;
		x_start = temp;
	}

	if (x_start >= draw_info->clip_rect.x + draw_info->clip_rect.width ||
			x_end < draw_info->clip_rect.x ||
			y < draw_info->clip_rect.y || y >= draw_info->clip_rect.y + draw_info->clip_rect.height)
	{
		return;
	}

	if (gc.line == MW_GL_SOLID_LINE)
	{
		filled_rectangle(draw_info, x_start, y, (x_end - x_start) + 1, 1, gc.fg_colour);
	}
	else
	{
		for (x = x_start; x <= x_end; x++)
		{
			if (((uint16_t)gc.line & mask) == mask)
			{
				pixel(draw_info, x, y, gc.fg_colour);
			}
			else
			{
				if (gc.bg_transparent == MW_GL_BG_NOT_TRANSPARENT)
				{
					pixel(draw_info, x, y, gc.bg_colour);
				}
			}
			mask >>= 1U;
			if (mask == 0U)
			{
				mask = 0x8000U;
			}
		}
	}
}

void mw_gl_vline(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y_start, int16_t y_end)
{
	int16_t temp;
	int16_t y;
	uint16_t mask = 0x8000U;

	if (draw_info == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	if (y_start > y_end)
	{
		temp = y_end;
		y_end = y_start;
		y_start = temp;
	}

	if (x < draw_info->clip_rect.x || x >= draw_info->clip_rect.x + draw_info->clip_rect.width ||
			y_start >= draw_info->clip_rect.y + draw_info->clip_rect.height ||
			y_end < draw_info->clip_rect.y)
	{
		return;
	}

	if (gc.line == MW_GL_SOLID_LINE)
	{
		filled_rectangle(draw_info, x, y_start, 1, (y_end - y_start) + 1, gc.fg_colour);
	}
	else
	{
		for (y = y_start; y <= y_end; y++)
		{
			if (((uint16_t)gc.line & mask) == mask)
			{
				pixel(draw_info, x, y, gc.fg_colour);
			}
			else
			{
				if (gc.bg_transparent == MW_GL_BG_NOT_TRANSPARENT)
				{
					pixel(draw_info, x, y, gc.bg_colour);
				}
			}
			mask >>= 1U;
			if (mask == 0U)
			{
				mask = 0x8000U;
			}
		}
	}
}

void mw_gl_line(const mw_gl_draw_info_t *draw_info, int16_t p1x, int16_t p1y, int16_t p2x, int16_t p2y)
{
	int16_t F;
	int16_t x;
	int16_t y;
	int16_t dy;
	int16_t dx;
	int16_t dy2;
	int16_t dx2;
	int16_t dy2_minus_dx2;
	int16_t dy2_plus_dx2;
	uint16_t mask = 0x8000U;

	if (draw_info == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	if (gc.line == MW_GL_LINE_NONE)
	{
		return;
	}

	if (p1x > p2x)
	{
		F = p1x;
		p1x = p2x;
		p2x = F;

		F = p1y;
		p1y = p2y;
		p2y = F;
	}

	dy = p2y - p1y;
	dx = p2x - p1x;
	dy2 = dy * 2;
	dx2 = dx * 2;
	dy2_minus_dx2 = dy2 - dx2;
	dy2_plus_dx2 = dy2 + dx2;

	if (dy >= 0)
	{
		if (dy <= dx)
		{
			F = dy2 - dx;
			x = p1x;
			y = p1y;
			while (x <= p2x)
			{
				if (gc.line == MW_GL_SOLID_LINE)
				{
					mw_gl_fg_pixel(draw_info, x, y);
				}
				else
				{
					if (((uint16_t)gc.line & mask) == mask)
					{
						mw_gl_fg_pixel(draw_info, x, y);
					}
					else
					{
						mw_gl_bg_pixel(draw_info, x, y);
					}
					mask >>= 1U;
					if (mask == 0U)
					{
						mask = 0x8000U;
					}
				}
				if (F <= 0)
				{
					F += dy2;
				}
				else
				{
					y++;
					F += dy2_minus_dx2;
				}
				x++;
			}
		}
		else
		{
			F = dx2 - dy;
			y = p1y;
			x = p1x;
			while (y <= p2y)
			{
				if (gc.line == MW_GL_SOLID_LINE)
				{
					mw_gl_fg_pixel(draw_info, x, y);
				}
				else
				{
					if (((uint16_t)gc.line & mask) == mask)
					{
						mw_gl_fg_pixel(draw_info, x, y);
					}
					else
					{
						mw_gl_bg_pixel(draw_info, x, y);
					}
					mask >>= 1U;
					if (mask == 0U)
					{
						mask = 0x8000U;
					}
				}
				if (F <= 0)
				{
					F += dx2;
				}
				else
				{
					x++;
					F -= dy2_minus_dx2;
				}
			y++;
			}
		}
	}
	else
	{
		if (dx >= -dy)
		{
			F = -dy2 - dx;
			x = p1x;
			y = p1y;
			while (x <= p2x)
			{
				if (gc.line == MW_GL_SOLID_LINE)
				{
					mw_gl_fg_pixel(draw_info, x, y);
				}
				else
				{
					if (((uint16_t)gc.line & mask) == mask)
					{
						mw_gl_fg_pixel(draw_info, x, y);
					}
					else
					{
						mw_gl_bg_pixel(draw_info, x, y);
					}
					mask >>= 1U;
					if (mask == 0U)
					{
						mask = 0x8000U;
					}
				}
				if (F <= 0)
				{
					F -= dy2;
				}
				else
				{
					y--;
					F -= dy2_plus_dx2;
				}
				x++;
			}
		}
		else
		{
			F = dx2 + dy;
			y = p1y;
			x = p1x;
			while (y >= p2y)
			{
				if (gc.line == MW_GL_SOLID_LINE)
				{
					mw_gl_fg_pixel(draw_info, x, y);
				}
				else
				{
					if (((uint16_t)gc.line & mask) == mask)
					{
						mw_gl_fg_pixel(draw_info, x, y);
					}
					else
					{
						mw_gl_bg_pixel(draw_info, x, y);
					}
					mask >>= 1U;
					if (mask == 0U)
					{
						mask = 0x8000U;
					}
				}
				if (F <= 0)
				{
					F += dx2;
				}
				else
				{
					x++;
					F += dy2_plus_dx2;
				}
				y--;
			}
		}
	}
}

void mw_gl_rectangle(const mw_gl_draw_info_t *draw_info, int16_t x_start, int16_t y_start, int16_t width, int16_t height)
{
	int16_t x;
	int16_t y;

	if (draw_info == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	if (gc.fill == MW_GL_NO_FILL)
	{
		mw_gl_hline(draw_info, x_start, x_start + width - 1, y_start);
		mw_gl_hline(draw_info, x_start, x_start + width - 1, y_start + height - 1);
		mw_gl_vline(draw_info, x_start, y_start, y_start + height - 1);
		mw_gl_vline(draw_info, x_start + width - 1, y_start, y_start + height - 1);
	}
	else
	{
		/* fill */
		if (gc.border == MW_GL_BORDER_ON)
		{
			/* border on */
			mw_gl_hline(draw_info, x_start, x_start + width - 1, y_start);
			mw_gl_hline(draw_info, x_start, x_start + width - 1, y_start + height - 1);
			mw_gl_vline(draw_info, x_start, y_start, y_start + height - 1);
			mw_gl_vline(draw_info, x_start + width - 1, y_start, y_start + height - 1);

			if (!gc.pattern_set)
			{
				/* no pattern */
				filled_rectangle(draw_info, x_start + 1, y_start + 1, width - 2, height - 2, gc.solid_fill_colour);
			}
			else
			{
				/* pattern */
				for (x = x_start + 1; x < x_start + width - 1; x++)
				{
					for (y = y_start + 1; y < y_start + height - 1; y++)
					{
						mw_gl_solid_fill_pixel(draw_info, x, y);
					}
				}
			}
		}
		else
		{
			/* border off */
			if (!gc.pattern_set)
			{
				/* no pattern */
				filled_rectangle(draw_info, x_start, y_start, width, height, gc.solid_fill_colour);
			}
			else
			{
				/* pattern */
				for (x = x_start; x < x_start + width; x++)
				{
					for (y = y_start; y < y_start + height; y++)
					{
						mw_gl_solid_fill_pixel(draw_info, x, y);
					}
				}
			}
		}
	}
}

void mw_gl_character(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, char c)
{
	char character_buffer[2];

	if (draw_info == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	/* do not attempt to draw control characters */
	if (c < ' ')
	{
		return;
	}

	/* replace other non-ascii characters with a '*' */
	if ((unsigned char)c > (unsigned char)'~')
	{
		c = '*';
	}

	/* check for proportional title font as handled differently */
	if (gc.font == MW_GL_TITLE_FONT)
	{
		character_buffer[0] = c;
		character_buffer[1] = '\0';
		title_font_string(draw_info, x, y, character_buffer);
		return;
	}

	switch(gc.text_rotation)
	{
	case MW_GL_TEXT_ROTATION_0:
		draw_character_0_degrees(draw_info, x, y, c);
		break;

	case MW_GL_TEXT_ROTATION_90:
		draw_character_90_degrees(draw_info, x, y, c);
		break;

	case MW_GL_TEXT_ROTATION_180:
		draw_character_180_degrees(draw_info, x, y, c);
		break;

	case MW_GL_TEXT_ROTATION_270:
		draw_character_270_degrees(draw_info, x, y, c);
		break;

	default:
		MW_ASSERT((bool)false, "Unknown text rotation");
		break;
	}
}

void mw_gl_string(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, const char *s)
{
	size_t c;
	size_t length;

	if (draw_info == NULL || s == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	/* check for title font as that's done elsewhere */
	if (gc.font == MW_GL_TITLE_FONT)
	{
		title_font_string(draw_info, x, y, s);
		return;
	}

	length = strlen(s);
	for (c = (size_t)0; c < length; c++)
	{
		switch (gc.text_rotation)
		{
		case MW_GL_TEXT_ROTATION_0:
			mw_gl_character(draw_info, x + (int16_t)c * (mw_gl_get_font_width() + 1), y, s[c]);
			break;

		case MW_GL_TEXT_ROTATION_90:
			mw_gl_character(draw_info, x, y + (int16_t)c * (mw_gl_get_font_width() + 1), s[c]);
			break;

		case MW_GL_TEXT_ROTATION_180:
			mw_gl_character(draw_info, x - (int16_t)c * (mw_gl_get_font_width() + 1), y, s[c]);
			break;

		case MW_GL_TEXT_ROTATION_270:
			mw_gl_character(draw_info, x, y - (int16_t)c * (mw_gl_get_font_width() + 1), s[c]);
			break;

		default:
			MW_ASSERT((bool)false, "Unknown text rotation");
			break;
		}
	}
}

int16_t mw_gl_get_string_width_pixels(const char *s)
{
	uint8_t i;
	int16_t width = 0;

	if (s == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return (0);
	}

	if (gc.font == MW_GL_TITLE_FONT)
	{
		for (i = 0U; i < strlen(s); i++)
		{
			width += (int16_t)mw_title_font_positions[s[i] - ' ' + 1] - (int16_t)mw_title_font_positions[s[i] - ' '];
		}
	}
	else
	{
		width = (int16_t)strlen(s) * (mw_gl_get_font_width() + 1);
	}

	return (width);
}

int16_t mw_gl_largest_string_width(const char **s, uint16_t count)
{
	uint16_t i;
	int16_t largest_width = 0;
	int16_t width;

	if (s == NULL || *s == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return (0);
	}

	for (i = 0; i < count; i++)
	{
		width = mw_gl_get_string_width_pixels(s[i]);
		if (width > largest_width)
		{
			largest_width = width;
		}
	}

	return (largest_width);
}

void mw_gl_circle(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, int16_t radius)
{
	bool outline_required = true;

	if (draw_info == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	if (gc.fill == MW_GL_FILL)
	{
		filled_circle(draw_info, x, y, radius);
		if (gc.border == MW_GL_BORDER_OFF)
		{
			outline_required = false;
		}
	}

	if (outline_required)
	{
		if (gc.line == MW_GL_SOLID_LINE)
		{
			circle_bres(draw_info, x, y, radius);
		}
		else
		{
			mw_gl_arc(draw_info, x, y, radius, 0, 360);
		}
	}
}

void mw_gl_poly(const mw_gl_draw_info_t *draw_info, uint8_t poly_corners, const int16_t *poly_x, const int16_t *poly_y, int16_t x_offset, int16_t y_offset)
{
	uint8_t i;
	bool draw_outline = true;

	if (draw_info == NULL || poly_x == NULL || poly_y == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	if (gc.fill == MW_GL_FILL && poly_corners > 2U)
	{
		filled_poly(draw_info, poly_corners, poly_x, poly_y, x_offset, y_offset);
		if (gc.border == MW_GL_BORDER_OFF)
		{
			draw_outline = false;
		}
	}

	if (draw_outline)
	{
		for (i = 0U; i < poly_corners - 1U; i++)
		{
			mw_gl_line(draw_info, poly_x[i] + x_offset, poly_y[i] + y_offset, poly_x[i + 1U] + x_offset, poly_y[i + 1U] + y_offset);
		}
		mw_gl_line(draw_info, poly_x[i] + x_offset, poly_y[i] + y_offset, poly_x[0] + x_offset, poly_y[0] + y_offset);
	}
}

void mw_gl_rotate_shape(uint8_t poly_corners, int16_t *poly_x, int16_t *poly_y, int16_t angle_degrees)
{
	uint8_t i;
	int16_t x;
	float angle_rads;

	if (poly_x == NULL || poly_y == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	angle_rads = (float)angle_degrees / DEGREES_IN_RAD;
	for (i = 0U; i < poly_corners; i++)
	{
		x = (int16_t)floor(((float)poly_x[i] * cosf(angle_rads) - (float)poly_y[i] * sinf(angle_rads)));
		poly_y[i] = (int16_t)floor(((float)poly_x[i] * sinf(angle_rads) + (float)poly_y[i] * cosf(angle_rads)));
		poly_x[i] = x;
	}
}

void mw_gl_scale_shape(uint8_t poly_corners, int16_t *poly_x, int16_t *poly_y, int16_t scale_x, int16_t scale_y)
{
	uint8_t i;

	if (poly_x == NULL || poly_y == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	for (i = 0U; i < poly_corners; i++)
	{
		poly_x[i] = poly_x[i] * scale_x / 10;
		poly_y[i] = poly_y[i] * scale_y / 10;
	}
}

void mw_gl_arc(const mw_gl_draw_info_t *draw_info, int16_t centre_x, int16_t centre_y, int16_t radius, int16_t start_angle, int16_t end_angle)
{
	float angle;
	float angle_step;
	float start_angle_rads;
	float end_angle_rads;
	int16_t x;
	int16_t y;
	uint16_t mask = 0x8000U;
	float temp_float;

	if (draw_info == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	if (start_angle > 360 || end_angle > 360 || radius == 0 || start_angle == end_angle)
	{
		return;
	}

	angle_step = 1.0f / (float)radius;

	if (end_angle < start_angle)
	{
		mw_gl_arc(draw_info, centre_x, centre_y, radius, 0, end_angle);
		mw_gl_arc(draw_info, centre_x, centre_y, radius, start_angle, 360);
		return;
	}

	if (gc.line == MW_GL_SOLID_LINE)
	{
		arc_bres(draw_info, centre_x, centre_y, radius, start_angle, end_angle);
		return;
	}

	start_angle_rads = (float)start_angle / DEGREES_IN_RAD;
	end_angle_rads = (float)end_angle / DEGREES_IN_RAD;
	for (angle = (float)start_angle_rads; angle <= (float)end_angle_rads; angle += angle_step)
	{
		temp_float = (float)radius * sinf(angle);
		x = centre_x + (int16_t)temp_float;
		temp_float = (float)radius * cosf(angle);
		y = centre_y - (int16_t)temp_float;
		if (((uint16_t)gc.line & mask) == mask)
		{
			mw_gl_fg_pixel(draw_info, x, y);
		}
		else
		{
			mw_gl_bg_pixel(draw_info, x, y);
		}
		mask >>= 1U;
		if (mask == 0x0000U)
		{
			mask = 0x8000U;
		}
	}
}

void mw_gl_rounded_rectangle(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, int16_t width, int16_t height, int16_t corner_radius)
{
	bool outline_required = true;
	mw_gl_border_t border_old;

	if (draw_info == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	if (width < corner_radius * 2 || height < corner_radius * 2)
	{
		return;
	}

	if (gc.fill == MW_GL_FILL)
	{
		border_old = gc.border;
		gc.border = MW_GL_BORDER_OFF;
		mw_gl_rectangle(draw_info, x + corner_radius, y, width - (2 * corner_radius), height);
		mw_gl_rectangle(draw_info, x, y + corner_radius, corner_radius, height - (2 * corner_radius));
		mw_gl_rectangle(draw_info, x + width - corner_radius, y + corner_radius, corner_radius, height - (2 * corner_radius));
		mw_gl_segment(draw_info, x + corner_radius, y + corner_radius, corner_radius + 1, 270, 360);
		mw_gl_segment(draw_info, x + width - corner_radius - 1, y + corner_radius, corner_radius + 1, 0, 90);
		mw_gl_segment(draw_info, x + corner_radius, y + height - corner_radius - 1, corner_radius, 180, 270);
		mw_gl_segment(draw_info, x + width - corner_radius - 1, y + height - corner_radius - 1, corner_radius, 90, 180);
		gc.border = border_old;

		if (gc.border == MW_GL_BORDER_OFF)
		{
			outline_required = false;
		}
	}

	if (outline_required)
	{
		mw_gl_hline(draw_info, x + corner_radius, x + width - 1 - corner_radius, y);
		mw_gl_hline(draw_info, x + corner_radius, x + width - 1 - corner_radius, y + height - 1);
		mw_gl_vline(draw_info, x, y + corner_radius, y + height - 1 - corner_radius);
		mw_gl_vline(draw_info, x + width - 1, y + corner_radius, y + height - 1 - corner_radius);
		mw_gl_arc(draw_info, x + corner_radius, y + corner_radius, corner_radius, 270, 360);
		mw_gl_arc(draw_info, x + width - corner_radius - 1, y + corner_radius, corner_radius, 0, 90);
		mw_gl_arc(draw_info, x + corner_radius, y + height - corner_radius - 1, corner_radius, 180, 270);
		mw_gl_arc(draw_info, x + width - corner_radius - 1, y + height - corner_radius - 1, corner_radius, 90, 180);
	}
}

void mw_gl_segment(const mw_gl_draw_info_t *draw_info, int16_t centre_x, int16_t centre_y, int16_t radius, int16_t start_angle, int16_t end_angle)
{
	bool outline_required = true;
	float temp_float_1;
	float temp_float_2;

	if (draw_info == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	if (gc.fill == MW_GL_FILL)
	{
		filled_segment(draw_info, centre_x, centre_y, radius, start_angle, end_angle, MW_GL_SEGMENT_FILL_ANGLE_STEP_SIZE);
		if (gc.border == MW_GL_BORDER_OFF)
		{
			outline_required = false;
		}
	}

	if (outline_required)
	{
		temp_float_1 = sinf((float)start_angle / DEGREES_IN_RAD) * (float)radius;
		temp_float_2 = cosf((float)start_angle / DEGREES_IN_RAD) * (float)radius;

		mw_gl_line(draw_info,
				centre_x,
				centre_y,
				centre_x + (int16_t)temp_float_1,
				centre_y - (int16_t)temp_float_2);

		temp_float_1 = sinf((float)end_angle / DEGREES_IN_RAD) * (float)radius;
		temp_float_2 = cosf((float)end_angle / DEGREES_IN_RAD) * (float)radius;

		mw_gl_line(draw_info,
				centre_x,
				centre_y,
				centre_x + (int16_t)temp_float_1,
				centre_y - (int16_t)temp_float_2);

		mw_gl_arc(draw_info, centre_x, centre_y, radius, start_angle, end_angle);
	}
}

void mw_gl_monochrome_bitmap(const mw_gl_draw_info_t *draw_info,
		int16_t start_x,
		int16_t start_y,
		uint16_t image_data_width_pixels,
		uint16_t image_data_height_pixels,
		const uint8_t *image_data)
{
	int16_t x;
	int16_t y;
	uint8_t a;
	bool colour;
	uint8_t image_byte;
	uint8_t mask;
	uint16_t array_width;

	if (draw_info == NULL || image_data == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	/* check for off window starting point */
	if (start_x > draw_info->clip_rect.x + draw_info->clip_rect.width ||
			start_y > draw_info->clip_rect.y + draw_info->clip_rect.height)
	{
		return;
	}

	/* check for being completely off window */
	if (start_x + (int16_t)image_data_width_pixels <= draw_info->clip_rect.x ||
			start_y + (int16_t)image_data_height_pixels <= draw_info->clip_rect.y)
	{
		return;
	}

	if (gc.bg_transparent == MW_GL_BG_TRANSPARENT)
	{
		array_width = image_data_width_pixels / 8U;
		if (image_data_width_pixels % 8U > 0U)
		{
			array_width++;
		}

		for (y = 0; y < (int16_t)image_data_height_pixels; y++)
		{
			for (a = 0; a < array_width; a++)
			{
				image_byte = image_data[y * (int16_t)array_width + (int16_t)a];
				mask = 0x80U;
				for (x = 0; x < 8; x++)
				{
					if ((int16_t)a * 8 + x == (int16_t)image_data_width_pixels)
					{
						break;
					}
					colour = (image_byte & mask) == 0U;
					if (colour == true)
					{
						mw_gl_fg_pixel(draw_info, (int16_t)a * 8 + x + start_x, y + start_y);
					}
					mask >>= 1U;
				}
			}
		}
	}
	else
	{
		mw_hal_lcd_monochrome_bitmap_clip(draw_info->origin_x + start_x,
				draw_info->origin_y + start_y,
				image_data_width_pixels,
				image_data_height_pixels,
				draw_info->origin_x + draw_info->clip_rect.x,
				draw_info->origin_y + draw_info->clip_rect.y,
				draw_info->clip_rect.width,
				draw_info->clip_rect.height,
				gc.fg_colour,
				gc.bg_colour,
				image_data);
	}
}

void mw_gl_colour_bitmap(const mw_gl_draw_info_t *draw_info,
		int16_t start_x,
		int16_t start_y,
		uint16_t image_data_width_pixels,
		uint16_t image_data_height_pixels,
		const uint8_t *image_data)
{
	if (draw_info == NULL || image_data == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	/* check for left edge being to right of clip rect or top edge being below clip rect*/
	if (start_x > draw_info->clip_rect.x + draw_info->clip_rect.width ||
			start_y > draw_info->clip_rect.y + draw_info->clip_rect.height)
	{
		return;
	}

	/* check for right edge being to left of clip rect or bottom edge being above rect */
	if (start_x + (int16_t)image_data_width_pixels - 1 < draw_info->clip_rect.x ||
			start_y + (int16_t)image_data_height_pixels - 1 < draw_info->clip_rect.y)
	{
		return;
	}

	mw_hal_lcd_colour_bitmap_clip(draw_info->origin_x + start_x,
			draw_info->origin_y + start_y,
			image_data_width_pixels,
			image_data_height_pixels,
			draw_info->origin_x + draw_info->clip_rect.x,
			draw_info->origin_y + draw_info->clip_rect.y,
			draw_info->clip_rect.width,
			draw_info->clip_rect.height,
			image_data);
}

void mw_gl_tt_render_text(const mw_gl_draw_info_t *draw_info,
		mw_util_rect_t *text_rect,
		mw_gl_tt_font_justification_t justification,
		const struct mf_rlefont_s *rle_font,
		const char *tt_text,
		int16_t vert_scroll_pixels)
{
	tt_font_state_t tt_font_state;
	mw_hal_lcd_colour_t temp_lcd_colour;

	/* check parameters */
	if (draw_info == NULL || rle_font == NULL || tt_text == NULL || text_rect == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	/* set up tt font rendering state from parameters */
	tt_font_state.font = &rle_font->font;
	tt_font_state.draw_info = draw_info;
	(void)memcpy((&tt_font_state.bounding_box), (text_rect), (sizeof(mw_util_rect_t)));
	tt_font_state.bottom = text_rect->y + text_rect->height;
	tt_font_state.justification = justification;
	tt_font_state.vert_scroll_pixels = vert_scroll_pixels;

	/* set up alpha blending values */
	if ((rle_font->font.flags & MF_FONT_FLAG_BW) == 0U)
	{
		temp_lcd_colour = (gc.fg_colour & 0xff0000U) >> 16U;
		tt_font_state.fg_red = (uint8_t)temp_lcd_colour;
		temp_lcd_colour = (gc.fg_colour & 0xff00U) >> 8U;
		tt_font_state.fg_green = (uint8_t)temp_lcd_colour;
		temp_lcd_colour = gc.fg_colour & 0xffU;
		tt_font_state.fg_blue = (uint8_t)temp_lcd_colour;
		temp_lcd_colour = (gc.bg_colour & 0xff0000U) >> 16U;
		tt_font_state.bg_red = (uint8_t)temp_lcd_colour;
		temp_lcd_colour = (gc.bg_colour & 0xff00U) >> 8U;
		tt_font_state.bg_green = (uint8_t)temp_lcd_colour;
		temp_lcd_colour = gc.bg_colour & 0xffU;
		tt_font_state.bg_blue = (uint8_t)temp_lcd_colour;
	}

	/* set up gc for drawing background in line draw callback */
	mw_gl_set_solid_fill_colour(gc.bg_colour);
	mw_gl_clear_pattern();
	mw_gl_set_fill(MW_GL_FILL);
	mw_gl_set_border(MW_GL_BORDER_OFF);

	/* render tt text */
	mf_wordwrap(tt_font_state.font,
			text_rect->width,
			tt_text,
			tt_line_callback,
			&tt_font_state);
}

int16_t mw_gl_tt_get_render_text_lines(int16_t width,
		mw_gl_tt_font_justification_t justification,
		const struct mf_rlefont_s *rle_font,
		const char *tt_text)
{
	tt_font_state_t tt_font_state;

	/* check parameters */
	if (rle_font == NULL || tt_text == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return (0);
	}

    if (justification != MW_GL_TT_FULLY_JUSTIFIED &&
    		justification != MW_GL_TT_LEFT_JUSTIFIED &&
			justification != MW_GL_TT_RIGHT_JUSTIFIED &&
			justification != MW_GL_TT_CENTRE_JUSTIFIED)
    {
    	MW_ASSERT((bool)false, "Invalid justification");
    	return (0);
    }

	/* set up tt font rendering state from parameters */
	tt_font_state.font = &rle_font->font;
	tt_font_state.bounding_box.width = width;
	tt_font_state.justification = justification;
	tt_font_state.rendered_line_count = 0;

	/* dummy render tt text */
	mf_wordwrap(tt_font_state.font,
			width,
			tt_text,
			tt_dummy_line_callback,
			&tt_font_state);

	return (tt_font_state.rendered_line_count * (int16_t)tt_font_state.font->line_height);
}
