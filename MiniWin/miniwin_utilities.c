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

#include <miniwin_debug.h>
#include <miniwin_utilities.h>
#include <stdlib.h>

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_util_set_rect(mw_util_rect_t *r, int16_t x, int16_t y, uint16_t width, uint16_t height)
{
	if (r != NULL)
	{
		r->x = x;
		r->y = y;
		r->width = width;
		r->height = height;
	}
	else
	{
		MW_ASSERT(false);
	}
}

bool mw_util_is_point_in_rect(const mw_util_rect_t *r, int16_t x, int16_t y)
{
	if (r == NULL)
	{
		MW_ASSERT(false);
		return false;
	}

	if (x < r->x || x >= (r->x + r->width) || y < r->y || y >= (r->y + r->height))
	{
		return false;
	}

	return true;
}

bool mw_util_do_rects_coincide(const mw_util_rect_t *a, const mw_util_rect_t *b)
{
	if (!a || !b)
	{
		return false;
	}

    return !(a->x + a->width < b->x || a->y + a->height < b->y || a->x > b->x + b->width || a->y > b->y + b->height);
}

bool mw_util_does_rect_a_obscure_rect_b(const mw_util_rect_t *a, const mw_util_rect_t *b)
{
	if (a == NULL || b == NULL)
	{
		MW_ASSERT(false);
		return false;
	}

	if (a->x <= b->x &&
			a->y <= b->y &&
			a->x + a->width >= b->x + b->width &&
			a->y + a->height >= b->y + b->height)
	{
		return true;
	}

	return false;
}

char *mw_util_safe_strcpy(char *dest, size_t size, const char *src)
{
    size_t i;

    if (dest == NULL || src == NULL)
    {
    	MW_ASSERT(false);
    	return 0;
    }

    if (size > 0)
    {
        for (i = 0; i < size - 1 && src[i]; i++)
        {
             dest[i] = src[i];
        }
        dest[i] = '\0';
    }

    return dest;
}

uint16_t mw_util_change_bit(uint16_t word, uint8_t bit, bool state)
{
	uint16_t mask;

	if (bit < 16)
	{
		mask = 1U << bit;

		if (state)
		{
			word |= mask;
		}
		else
		{
			word &= ~mask;
		}
	}

	return word;
}

bool mw_util_get_bit(uint16_t word, uint8_t bit)
{
	uint16_t mask;
	bool result = false;

	if (bit < 16)
	{
		mask = 1 << bit;
		if ((word & mask) == mask)
		{
			result = true;
		}
	}

	return result;
}

int mw_util_compare_int16_t(const void *a, const void *b)
{
	if (a == NULL || b == NULL)
	{
		MW_ASSERT(false);
		return 0;
	}

	if (*(int16_t*)a < *(int16_t*)b)
	{
		return -1;
	}
	if (*(int16_t*)a == *(int16_t*)b)
	{
		return 0;
	}
  
	return 1;
}
