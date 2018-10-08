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

/***************
*** INCLUDES ***
***************/

#include <string.h>
#include <math.h>
#include <miniwin_debug.h>
#include "hal/hal_delay.h"
#include "gl/gl.h"

/****************
*** CONSTANTS ***
****************/

#ifndef M_PI
#define M_PI				3.1415926535f
#endif
#define	DEGREES_IN_RAD		(180.0f / M_PI)

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

extern const uint16_t mw_fonts_large_positions[];   	/**< positions of start of character data of proportional fonts */
extern const uint8_t mw_fonts_large_pro[];      		/**< 16 high proportional font, widths vary */
extern const uint8_t mw_fonts_ascii_5x9[]; 					/**< 5x9 fixed width font */
extern const uint8_t mw_fonts_iso8859_15_5x9[];				/**< 5x9 fixed width font ISO8859 part 15 extension */

/**********************
*** LOCAL VARIABLES ***
**********************/

static mw_gl_gc_t gc;                       /**< the graphics context used to hold all the settings used by the plotting routines */

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void pixel(const mw_gl_draw_info_t *draw_info, int16_t client_x, int16_t client_y, mw_hal_lcd_colour_t colour);
static void filled_rectangle(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, int16_t width, int16_t height, mw_hal_lcd_colour_t colour);
static void filled_poly(const mw_gl_draw_info_t *draw_info, uint8_t poly_corners, const int16_t *poly_x, const int16_t *poly_y, int16_t x_offset, int16_t y_offset);
static void arc_bres(const mw_gl_draw_info_t *draw_info, int16_t centre_x, int16_t centre_y, int16_t radius, int16_t start_angle, int16_t end_angle);
static void arc_point(const mw_gl_draw_info_t *draw_info, int16_t centre_x, int16_t centre_y, int16_t x, int16_t y, int16_t start_angle, int16_t end_angle);
static void filled_circle(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, int16_t radius);
static void circle_bres(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, int16_t radius);
static void filled_segment(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, int16_t radius, int16_t start_angle, int16_t end_angle, int16_t angle_step_size);

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

	if (display_x >= 0 && display_x < MW_HAL_LCD_WIDTH && display_y >= 0 && display_y < MW_HAL_LCD_HEIGHT)
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

	if (draw_info->origin_x + draw_info->clip_rect.x > MW_GL_MAX_X ||
			draw_info->origin_y + draw_info->clip_rect.y > MW_GL_MAX_Y)
	{
		return;
	}

	if (draw_info->origin_x + client_x > MW_GL_MAX_X || draw_info->origin_y + client_y > MW_GL_MAX_Y)
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
static void filled_poly(const mw_gl_draw_info_t *draw_info, uint8_t poly_corners, const int16_t *poly_x, const int16_t *poly_y, int16_t x_offset, int16_t y_offset)
{
	uint8_t i;
	uint8_t j;
	int16_t swap;
	int16_t line_node_count;
	int16_t y;
	int16_t node_x[MW_GL_MAX_POLY_CORNERS - 1];
	int16_t y_min = 32767;
	uint16_t y_max = -32768;
	uint16_t x;

	MW_ASSERT(draw_info, "Null pointer argument");
	MW_ASSERT(poly_x, "Null pointer argument");
	MW_ASSERT(poly_y, "Null pointer argument");
	MW_ASSERT(poly_corners <= MW_GL_MAX_POLY_CORNERS, "Too many points in polygon shape");

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
		j = poly_corners - 1;
		for (i = 0; i  <poly_corners; i++)
		{
			if ((poly_y[i] < y && poly_y[j] >= y) || (poly_y[j] < y && poly_y[i] >= y))
			{
				float temp = (float)(y - poly_y[i]) / (float)((poly_y[j] - poly_y[i]));
				node_x[line_node_count++] = (int32_t)(poly_x[i] + temp * ((poly_x[j] - poly_x[i])));
			}
			j = i;
		}

		/* sort the nodes, via a simple bubble sort */
		i = 0;
		while (i < line_node_count - 1)
		{
			if (node_x[i] > node_x[i + 1])
			{
				swap = node_x[i];
				node_x[i] = node_x[i + 1];
				node_x[i + 1] = swap;
				if (i)
				{
					i--;
				}
			}
			else
			{
				i++;
			}
		}

		/* fill the pixels between node pairs */
		for (i = 0; i < line_node_count; i += 2)
		{
			node_x[i] += x_offset;
			node_x[i + 1] += x_offset;

			if (node_x[i] > MW_GL_MAX_X)
			{
				break;
			}
			if (node_x[i + 1] > 0)
			{
				if (node_x[i] < 0)
				{
					node_x[i] = 0;
				}
				if (node_x[i + 1]>MW_GL_MAX_X)
				{
					node_x[i + 1]=MW_GL_MAX_Y;
				}
				if (gc.pattern_set)
				{
					for (x = 0; x <= node_x[i + 1]  -node_x[i] + 1; x++)
					{
						mw_gl_solid_fill_pixel(draw_info, x + node_x[i], y + y_offset);
					}
				}
				else
				{
					filled_rectangle(draw_info, node_x[i], y + y_offset, node_x[i + 1]-node_x[i] + 1, 1 , gc.solid_fill_colour);
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

	/* plot top, bottom, left and right */
	arc_point(draw_info, centre_x, centre_y, centre_x, centre_y + radius, start_angle, end_angle);
	arc_point(draw_info, centre_x, centre_y, centre_x, centre_y - radius, start_angle, end_angle);
	arc_point(draw_info, centre_x, centre_y, centre_x + radius, centre_y, start_angle, end_angle);
	arc_point(draw_info, centre_x, centre_y, centre_x - radius, centre_y, start_angle, end_angle);

	while (y_point > x_point)
	{
		if (decision < 0)
		{
			decision += (x_point << 1) + 3;
			x_point++;
		}
		else
		{
			decision += ((x_point - y_point) << 1) + 5;
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
	MW_ASSERT(draw_info, "Null pointer argument");

	/* calculate the angle the current point makes with the circle centre */
	int16_t angle = (int16_t)(DEGREES_IN_RAD  *(atan2(centre_y - y, centre_x - x))) -90;
	if (angle < 0)
	{
		angle += 360;
	}

	if (angle >= start_angle && angle < end_angle)
	{
		mw_gl_fg_pixel(draw_info, x, y);
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
		for (y =- radius; y <= radius + 1; y++)
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
			decision += (x_point << 1) + 3;
			x_point++;
		}
		else
		{
			decision += ((x_point - y_point) << 1) + 5;
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
			decision += (x_point << 1) + 3;
			x_point++;
		}
		else
		{
			decision += ((x_point - y_point) << 1) + 5;
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
	int16_t old_x = x + (int16_t)(sin((float)start_angle / DEGREES_IN_RAD) * (float)radius);
	int16_t old_y = y - (int16_t)(cos((float)start_angle / DEGREES_IN_RAD) * (float)radius);
	int16_t i;
	float angle;
	int16_t triangle_corners_x[3];
	int16_t triangle_corners_y[3];

	MW_ASSERT(draw_info, "Null pointer argument");

	triangle_corners_x[0] = x;
	triangle_corners_y[0] = y;

	if (start_angle > end_angle)
	{
		end_angle += 360;
	}

	for (i = start_angle + angle_step_size; i <= end_angle; i += angle_step_size)
	{
		angle = (float)i / DEGREES_IN_RAD;
		triangle_corners_x[1] = x + (int16_t)(sin(angle) * (float)radius);
		triangle_corners_y[1] = y - (int16_t)(cos(angle) * (float)radius);
		triangle_corners_x[2] = old_x;
		triangle_corners_y[2] = old_y;

		filled_poly(draw_info, 3, triangle_corners_x, triangle_corners_y, 0, 0);

		old_x = triangle_corners_x[1];
		old_y = triangle_corners_y[1];
	}

	i -= angle_step_size;
	if ( i <end_angle)
	{
		triangle_corners_x[1] = x + (int16_t)(sin(end_angle / DEGREES_IN_RAD) * (float)radius);
		triangle_corners_y[1] = y - (int16_t)(cos(end_angle / DEGREES_IN_RAD) * (float)radius);
		triangle_corners_x[2] = x + (int16_t)(sin(i / DEGREES_IN_RAD) * (float)radius);
		triangle_corners_y[2] = y - (int16_t)(cos(i / DEGREES_IN_RAD) * (float)radius);

		filled_poly(draw_info, 3, triangle_corners_x, triangle_corners_y, 0, 0);
	}
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
}

mw_gl_gc_t *mw_gl_get_gc(void)
{
	return &gc;
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
	memcpy(gc.pattern, pattern, sizeof(mw_gl_pattern_t));
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

void mw_gl_solid_fill_pixel(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y)
{
	uint16_t mask;
	uint16_t pattern_y;

	if (!draw_info)
	{
		MW_ASSERT(false, "Null pointer argument");
		return;
	}

	if (x > MW_GL_MAX_X || y > MW_GL_MAX_Y)
	{
	    return;
	}
	
	if (gc.pattern_set)
	{
		mask = 0x8000 >> (x & 0x000F);
		pattern_y = y & 0x000F;

		if (gc.pattern[pattern_y] & mask)
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
	if (!draw_info)
	{
		MW_ASSERT(false, "Null pointer argument");
		return;
	}

	pixel(draw_info, client_x, client_y, gc.fg_colour);
}

void mw_gl_bg_pixel(const mw_gl_draw_info_t *draw_info, int16_t client_x, int16_t client_y)
{
	if (!draw_info)
	{
		MW_ASSERT(false, "Null pointer argument");
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
	uint16_t mask = 0x8000;

	if (!draw_info)
	{
		MW_ASSERT(false, "Null pointer argument");
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
			if (mask & gc.line)
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
			mask >>= 1;
			if (!mask)
			{
				mask = 0x8000;
			}
		}
	}
}

void mw_gl_vline(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y_start, int16_t y_end)
{
	int16_t temp;
	int16_t y;
	uint16_t mask = 0x8000;

	if (!draw_info)
	{
		MW_ASSERT(false, "Null pointer argument");
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
			if (mask & gc.line)
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
			mask >>= 1;
			if (!mask)
			{
				mask = 0x8000;
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
	uint16_t mask = 0x8000;

	if (!draw_info)
	{
		MW_ASSERT(false, "Null pointer argument");
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
	dy2 = (dy << 1);
	dx2 = (dx << 1);
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
					if (mask & gc.line)
					{
						mw_gl_fg_pixel(draw_info, x, y);
					}
					else
					{
						mw_gl_bg_pixel(draw_info, x, y);
					}
					mask >>= 1;
					if (!mask)
					{
						mask = 0x8000;
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
					if (mask & gc.line)
					{
						mw_gl_fg_pixel(draw_info, x, y);
					}
					else
					{
						mw_gl_bg_pixel(draw_info, x, y);
					}
					mask >>= 1;
					if (!mask)
					{
						mask = 0x8000;
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
					if (mask & gc.line)
					{
						mw_gl_fg_pixel(draw_info, x, y);
					}
					else
					{
						mw_gl_bg_pixel(draw_info, x, y);
					}
					mask >>= 1;
					if (!mask)
					{
						mask = 0x8000;
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
					if (mask & gc.line)
					{
						mw_gl_fg_pixel(draw_info, x, y);
					}
					else
					{
						mw_gl_bg_pixel(draw_info, x, y);
					}
					mask >>= 1;
					if (!mask)
					{
						mask = 0x8000;
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

	if (!draw_info)
	{
		MW_ASSERT(false, "Null pointer argument");
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
	int16_t char_x;
	int16_t char_y;
	uint16_t bitmap_start_position;
	uint16_t bitmap_start_byte;
	uint8_t mask;
	uint8_t byte;
	unsigned char uc;
	const uint8_t *font_bitmap_array;

	uc = (unsigned char)c;

	if (!draw_info)
	{
		MW_ASSERT(false, "Null pointer argument");
		return;
	}

	if (x >= draw_info->clip_rect.x + draw_info->clip_rect.width ||
			y >= draw_info->clip_rect.y + draw_info->clip_rect.height ||
			x + MW_GL_STANDARD_CHARACTER_WIDTH <= draw_info->clip_rect.x ||
			y + MW_GL_STANDARD_CHARACTER_HEIGHT <= draw_info->clip_rect.y)
	{
		return;
	}

	if (uc < ' ' || (uc > '~' && uc < 0xa0))
	{
		uc = '*';
	}

	if (gc.bg_transparent == MW_GL_BG_NOT_TRANSPARENT)
	{
		filled_rectangle(draw_info, x, y, MW_GL_STANDARD_CHARACTER_WIDTH, MW_GL_STANDARD_CHARACTER_HEIGHT, gc.bg_colour);
	}

	if (uc <= '~')
	{
		bitmap_start_position = (uc - ' ') * MW_GL_STANDARD_CHARACTER_WIDTH;
		font_bitmap_array = mw_fonts_ascii_5x9;
	}
	else
	{
		bitmap_start_position = (uc - 0xa0) * MW_GL_STANDARD_CHARACTER_WIDTH;
		font_bitmap_array = mw_fonts_iso8859_15_5x9;
	}

	for (char_y = 0; char_y < MW_GL_STANDARD_CHARACTER_HEIGHT - 1; char_y++)
	{
		bitmap_start_byte = (char_y * 72) + (bitmap_start_position / 8);
		mask = 0x80 >> (bitmap_start_position % 8);
		byte = font_bitmap_array[bitmap_start_byte];

		for (char_x = 0; char_x < MW_GL_STANDARD_CHARACTER_WIDTH - 1; char_x++)
		{
			if (!(byte & mask))
			{
				mw_gl_fg_pixel(draw_info, x + char_x, y + char_y);
			}

			mask >>= 1;
			if (mask == 0)
			{
				mask = 0x80;
				bitmap_start_byte++;
				byte = font_bitmap_array[bitmap_start_byte];
			}
		}
	}
}

void mw_gl_string(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, const char *s)
{
	uint8_t c;
	uint8_t length;

	if (!draw_info || !s)
	{
		MW_ASSERT(false, "Null pointer argument");
		return;
	}

	length = strlen((char *)s);
	for (c = 0; c < length; c++)
	{
		mw_gl_character(draw_info, x + c * MW_GL_STANDARD_CHARACTER_WIDTH, y, s[c]);
	}
}

void mw_gl_character_vert(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, char c)
{
	int16_t char_x;
	int16_t char_y;
	uint16_t bitmap_start_position;
	uint16_t bitmap_start_byte;
	uint8_t mask;
	uint8_t byte;
	unsigned char uc;
	const uint8_t *font_bitmap_array;

	uc = (unsigned char)c;

	if (!draw_info)
	{
		MW_ASSERT(false, "Null pointer argument");
		return;
	}

	if (x >= draw_info->clip_rect.x + draw_info->clip_rect.width ||
			y >= draw_info->clip_rect.y + draw_info->clip_rect.height ||
			x + MW_GL_STANDARD_CHARACTER_WIDTH <= draw_info->clip_rect.x ||
			y + MW_GL_STANDARD_CHARACTER_HEIGHT <= draw_info->clip_rect.y)
	{
		return;
	}

	if (uc < ' ' || (uc > '~' && uc < 0xa0))
	{
		uc = '*';
	}

	if (gc.bg_transparent == MW_GL_BG_NOT_TRANSPARENT)
	{
		filled_rectangle(draw_info, x - MW_GL_STANDARD_CHARACTER_HEIGHT + 1, y,
				MW_GL_STANDARD_CHARACTER_HEIGHT, MW_GL_STANDARD_CHARACTER_WIDTH, gc.bg_colour);
	}

	if (uc <= '~')
	{
		bitmap_start_position = (uc - ' ') * MW_GL_STANDARD_CHARACTER_WIDTH;
		font_bitmap_array = mw_fonts_ascii_5x9;
	}
	else
	{
		bitmap_start_position = (uc - 0xa0) * MW_GL_STANDARD_CHARACTER_WIDTH;
		font_bitmap_array = mw_fonts_iso8859_15_5x9;
	}
	for (char_y = 0; char_y < MW_GL_STANDARD_CHARACTER_HEIGHT - 1; char_y++)
	{
		bitmap_start_byte = (char_y * 72) + (bitmap_start_position / 8);
		mask = 0x80 >> (bitmap_start_position % 8);
		byte = font_bitmap_array[bitmap_start_byte];

		for (char_x = 0; char_x < MW_GL_STANDARD_CHARACTER_WIDTH - 1; char_x++)
		{
			if (!(byte & mask))
			{
	   			mw_gl_fg_pixel(draw_info, x - char_y, y + char_x);
			}

			mask >>= 1;
			if (mask == 0)
			{
				mask = 0x80;
				bitmap_start_byte++;
				byte = font_bitmap_array[bitmap_start_byte];
			}
		}
	}
}

void mw_gl_string_vert(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, const char *s)
{
	uint8_t c;
	uint8_t length;

	if (!draw_info || !s)
	{
		MW_ASSERT(false, "Null pointer argument");
		return;
	}

	length = strlen((char *)s);
	for (c = 0; c < length; c++)
	{
		mw_gl_character_vert(draw_info, x, y + c * MW_GL_STANDARD_CHARACTER_WIDTH, s[c]);
	}
}

void mw_gl_large_string(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, const char *s)
{
	uint8_t length = strlen((char *)s);
	uint8_t mask;
	uint16_t start_pos_in_bitmap;
	uint16_t end_pos_in_bitmap;
	int16_t char_x;
	int16_t char_y;
	uint8_t i;
	uint8_t byte_from_bitmap;
	char c;
	uint8_t next_char_start_x = 0;
	uint16_t x_position_in_character;
	uint16_t string_width_pixels;

	if (!draw_info || !s)
	{
		MW_ASSERT(false, "Null pointer argument");
		return;
	}

	string_width_pixels = mw_gl_large_string_width(s);

	/* check for completely off rect */
	if (x > draw_info->clip_rect.x + draw_info->clip_rect.width ||
			y > draw_info->clip_rect.y + draw_info->clip_rect.height ||
			x + string_width_pixels < draw_info->clip_rect.x ||
			y + MW_GL_LARGE_CHARACTER_HEIGHT < draw_info->clip_rect.y)
	{
		return;
	}

	if (gc.bg_transparent == MW_GL_BG_NOT_TRANSPARENT)
	{
		filled_rectangle(draw_info, x, y, mw_gl_large_string_width(s), MW_GL_LARGE_CHARACTER_HEIGHT, gc.bg_colour);
	}

	for (i = 0; i < length; i++)
	{
		for (char_y = 0; char_y < MW_GL_LARGE_CHARACTER_HEIGHT; char_y++)
		{
			c = s[i];
			if (c < ' ' || c > '~')
			{
				c = '*';
			}
			c -= ' ';

			start_pos_in_bitmap = mw_fonts_large_positions[(uint8_t)c];
			end_pos_in_bitmap = mw_fonts_large_positions[(uint8_t)c + 1];

			mask = 0x80;
			mask >>= (mw_fonts_large_positions[(uint8_t)c] % 8);

			x_position_in_character = 0;
			for (char_x = start_pos_in_bitmap; char_x < end_pos_in_bitmap; char_x++)
			{
				byte_from_bitmap = mw_fonts_large_pro[(char_x >> 3) + char_y * 87];

				if (!(byte_from_bitmap & mask))
				{
					mw_gl_fg_pixel(draw_info, x + x_position_in_character + next_char_start_x, y + char_y);
				}

				mask >>= 1;
				if (mask == 0)
				{
					mask = 0x80;
				}
				x_position_in_character++;
			}
		}
		next_char_start_x += x_position_in_character;
	}
}

void mw_gl_large_string_vert(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, const char *s)
{
	uint8_t length = strlen((char *)s);
	uint8_t mask;
	uint16_t start_pos_in_bitmap, end_pos_in_bitmap;
	int16_t char_x;
	int16_t char_y;
	uint8_t i;
	uint8_t byte_from_bitmap;
	char c;
	uint16_t next_char_start_y = 0;
	uint16_t x_position_in_character;
	uint16_t string_width_pixels;

	if (!draw_info || !s)
	{
		MW_ASSERT(false, "Null pointer argument");
		return;
	}

	string_width_pixels = mw_gl_large_string_width(s);

	/* check for completely off rect */
	if (x - MW_GL_LARGE_CHARACTER_HEIGHT > draw_info->clip_rect.x + draw_info->clip_rect.width ||
			y > draw_info->clip_rect.y + draw_info->clip_rect.height ||
			x < draw_info->clip_rect.x ||
			y + string_width_pixels < draw_info->clip_rect.y)
	{
		return;
	}

	if (gc.bg_transparent == MW_GL_BG_NOT_TRANSPARENT)
	{
		filled_rectangle(draw_info, x - MW_GL_LARGE_CHARACTER_HEIGHT + 1, y,
				MW_GL_LARGE_CHARACTER_HEIGHT, mw_gl_large_string_width(s), gc.bg_colour);
	}

	for (i = 0; i < length; i++)
	{
		for (char_y = 0; char_y < MW_GL_LARGE_CHARACTER_HEIGHT; char_y++)
		{
			c = s[i];
			if (c < ' ' || c > '~')
			{
				c = '*';
			}
			c -= ' ';

			start_pos_in_bitmap = mw_fonts_large_positions[(uint8_t)c];
			end_pos_in_bitmap = mw_fonts_large_positions[(uint8_t)c + 1];

			mask = 0x80;
			mask >>= (mw_fonts_large_positions[(uint8_t)c] % 8);

			x_position_in_character = 0;
			for (char_x = start_pos_in_bitmap; char_x < end_pos_in_bitmap; char_x++)
			{
				byte_from_bitmap = mw_fonts_large_pro[(char_x >> 3) + char_y * 87];

				if (!(byte_from_bitmap & mask))
				{
					mw_gl_fg_pixel(draw_info, x + (MW_GL_LARGE_CHARACTER_HEIGHT - char_y) - MW_GL_LARGE_CHARACTER_HEIGHT,
							y + x_position_in_character + next_char_start_y);
				}

				mask >>= 1;
				if (mask == 0)
				{
					mask = 0x80;
				}
				x_position_in_character++;
			}
		}
		next_char_start_y+=x_position_in_character;
	}
}

uint16_t mw_gl_large_string_width(const char *s)
{
	uint8_t i;
	uint16_t width = 0;

	if (!s)
	{
		MW_ASSERT(false, "Null pointer argument");
		return 0;
	}

	for (i = 0; i < strlen((char *)s); i++)
	{
		width += mw_fonts_large_positions[s[i] - ' ' + 1] - mw_fonts_large_positions[s[i] - ' '];
	}

	return width;
}

uint16_t mw_gl_largest_string_width(const char **s, uint16_t count)
{
	uint16_t i;
	uint16_t largest_width = 0;
	uint16_t width;

	if (!s || !*s)
	{
		MW_ASSERT(false, "Null pointer argument");
		return 0;
	}

	for (i = 0; i < count; i++)
	{
		width = mw_gl_large_string_width(s[i]);
		if (width > largest_width)
		{
			largest_width = width;
		}
	}

	return largest_width;
}

void mw_gl_circle(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, int16_t radius)
{
	uint8_t outline_required = true;

	if (!draw_info)
	{
		MW_ASSERT(false, "Null pointer argument");
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
	uint8_t draw_outline = true;

	if (!draw_info || !poly_x || !poly_y)
	{
		MW_ASSERT(false, "Null pointer argument");
		return;
	}

	if (gc.fill == MW_GL_FILL && poly_corners > 2)
	{
		filled_poly(draw_info, poly_corners, poly_x, poly_y, x_offset, y_offset);
		if (gc.border == MW_GL_BORDER_OFF)
		{
			draw_outline = false;
		}
	}

	if (draw_outline)
	{
		for (i = 0; i < poly_corners - 1; i++)
		{
			mw_gl_line(draw_info, poly_x[i] + x_offset, poly_y[i] + y_offset, poly_x[i+ 1] + x_offset, poly_y[i + 1] + y_offset);
		}
		mw_gl_line(draw_info, poly_x[i] + x_offset, poly_y[i] + y_offset, poly_x[0] + x_offset, poly_y[0] + y_offset);
	}
}

void mw_gl_rotate_shape(uint8_t poly_corners, int16_t *poly_x, int16_t *poly_y, int16_t angle_degrees)
{
	uint8_t i;
	int16_t x;
	float angle_rads;

	if (!poly_x || !poly_y)
	{
		MW_ASSERT(false, "Null pointer argument");
		return;
	}

	angle_rads = (float)angle_degrees / DEGREES_IN_RAD;
	for (i = 0; i < poly_corners; i++)
	{
		x = (int16_t)roundf(((float)poly_x[i] * cos(angle_rads) - (float)poly_y[i] * sin(angle_rads)));
		poly_y[i] = (int16_t)roundf(((float)poly_x[i] * sin(angle_rads) + (float)poly_y[i] * cos(angle_rads)));
		poly_x[i] = x;
	}
}

void mw_gl_scale_shape(uint8_t poly_corners, int16_t *poly_x, int16_t *poly_y, int16_t scale_x, int16_t scale_y)
{
	uint8_t i;

	if (!poly_x || !poly_y)
	{
		MW_ASSERT(false, "Null pointer argument");
		return;
	}

	for (i = 0; i < poly_corners; i++)
	{
		poly_x[i] = poly_x[i] * scale_x / 10;
		poly_y[i] = poly_y[i] * scale_y / 10;;
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
	uint16_t mask = 0x8000;

	if (!draw_info)
	{
		MW_ASSERT(false, "Null pointer argument");
		return;
	}

	if (start_angle > 360 || end_angle > 360 || radius == 0 || start_angle == end_angle)
	{
		return;
	}

	angle_step = 1.0 / (float)radius;

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
		x = centre_x + (int16_t)((float)radius * sin(angle));
		y = centre_y - (int16_t)((float)radius * cos(angle));
		if (mask&gc.line)
		{
			mw_gl_fg_pixel(draw_info, x, y);
		}
		else
		{
			mw_gl_bg_pixel(draw_info, x, y);
		}
		mask >>= 1;
		if (mask == 0x0000)
		{
			mask = 0x8000;
		}
	}
}

void mw_gl_rounded_rectangle(const mw_gl_draw_info_t *draw_info, int16_t x, int16_t y, int16_t width, int16_t height, int16_t corner_radius)
{
	uint8_t outline_required = true;
	mw_gl_border_t border_old;

	if (!draw_info)
	{
		MW_ASSERT(false, "Null pointer argument");
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
	uint8_t outline_required = true;

	if (!draw_info)
	{
		MW_ASSERT(false, "Null pointer argument");
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
		mw_gl_line(draw_info,
				centre_x,
				centre_y,
				centre_x + (int16_t)(sin((float)start_angle / DEGREES_IN_RAD) * (float)radius),
				centre_y - (int16_t)(cos((float)start_angle / DEGREES_IN_RAD) * (float)radius));

		mw_gl_line(draw_info,
				centre_x,
				centre_y,
				centre_x + (int16_t)(sin((float)end_angle / DEGREES_IN_RAD) * (float)radius),
				centre_y - (int16_t)(cos((float)end_angle / DEGREES_IN_RAD) * (float)radius));

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
	if (!draw_info || !image_data)
	{
		MW_ASSERT(false, "Null pointer argument");
		return;
	}

	/* check for off window starting point */
	if (start_x > draw_info->clip_rect.x + draw_info->clip_rect.width ||
			start_y > draw_info->clip_rect.y + draw_info->clip_rect.height)
	{
		return;
	}

	/* check for being completely off window */
	if (start_x + image_data_width_pixels <= draw_info->clip_rect.x ||
			start_y + image_data_height_pixels <= draw_info->clip_rect.y)
	{
		return;
	}

	if (gc.bg_transparent == MW_GL_BG_TRANSPARENT)
	{
		int16_t x;
		int16_t y;
		uint8_t a;
		uint8_t colour;
		uint8_t image_byte;
		uint8_t mask;
		uint8_t array_width;

		array_width = image_data_width_pixels >> 3;
		if (image_data_width_pixels % 8 > 0)
		{
			array_width++;
		}

		for (y = 0; y < image_data_height_pixels; y++)
		{
			for (a = 0; a < array_width; a++)
			{
				image_byte = image_data[y * array_width + a];
				mask = 0x80;
				for (x = 0; x < 8; x++)
				{
					if ((a << 3) + x == image_data_width_pixels)
					{
						break;
					}
					colour = !(image_byte & mask);
					if (colour)
					{
						mw_gl_fg_pixel(draw_info, (a << 3) + x + start_x, y + start_y);
					}
					mask >>= 1;
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
	if (!draw_info || !image_data)
	{
		MW_ASSERT(false, "Null pointer argument");
		return;
	}

	/* check for left edge being to right of clip rect or top edge being below clip rect*/
	if (start_x > draw_info->clip_rect.x + draw_info->clip_rect.width ||
			start_y > draw_info->clip_rect.y + draw_info->clip_rect.height)
	{
		return;
	}

	/* check for right edge being to left of clip rect or bottom edge being above rect */
	if (start_x + image_data_width_pixels - 1 < draw_info->clip_rect.x ||
			start_y + image_data_height_pixels - 1 < draw_info->clip_rect.y)
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
