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
#include <ctype.h>
#include "miniwin_debug.h"
#include "miniwin_utilities.h"

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

void mw_util_set_rect(mw_util_rect_t *r, int16_t x, int16_t y, int16_t width, int16_t height)
{
	if (!r)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return;
	}

	r->x = x;
	r->y = y;
	r->width = width;
	r->height = height;
}

bool mw_util_is_point_in_rect(const mw_util_rect_t *r, int16_t x, int16_t y)
{
	if (!r)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return (false);
	}

	if (x < r->x || x >= (r->x + r->width) || y < r->y || y >= (r->y + r->height))
	{
		return (false);
	}

	return (true);
}

bool mw_util_do_rects_coincide(const mw_util_rect_t *a, const mw_util_rect_t *b)
{
	if (!a || !b)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return (false);
	}

    return (!(a->x + a->width < b->x || a->y + a->height < b->y || a->x > b->x + b->width || a->y > b->y + b->height));
}

bool mw_util_does_rect_a_obscure_rect_b(const mw_util_rect_t *a, const mw_util_rect_t *b)
{
	if (!a || !b)
	{
		MW_ASSERT((bool)false, "Null pointer argument");
		return (false);
	}

	if (a->x <= b->x &&
			a->y <= b->y &&
			a->x + a->width >= b->x + b->width &&
			a->y + a->height >= b->y + b->height)
	{
		return (true);
	}

	return (false);
}

char *mw_util_safe_strcpy(char *dest, size_t size, const char *src)
{
    size_t i;

    if (dest == NULL || src == NULL)
    {
    	MW_ASSERT((bool)false, "Null pointer argument");
    	return (NULL);
    }

    if (size > 0U)
    {
        for (i = 0U; i < size - (size_t)1U && src[i]; i++)
        {
             dest[i] = src[i];
        }
        dest[i] = '\0';
    }

    return (dest);
}

char *mw_util_safe_strcat(char *dest, size_t size, const char *src)
{
	return (strncat(dest, src, size - strlen(dest) - (size_t)1U));
}

uint16_t mw_util_change_bit(uint16_t word, uint8_t bit, bool state)
{
	uint16_t mask;

	if (bit < 16U)
	{
		mask = (uint16_t)1U << bit;

		if (state)
		{
			word |= mask;
		}
		else
		{
			word &= ~mask;
		}
	}

	return (word);
}

bool mw_util_get_bit(uint16_t word, uint8_t bit)
{
	uint16_t mask;
	bool result = false;

	if (bit < 16U)
	{
		mask = (uint16_t)1U << bit;
		if ((word & mask) == mask)
		{
			result = true;
		}
	}

	return (result);
}


void mw_util_shell_sort(int16_t *array, uint16_t n)
{
    int16_t temp;
    uint16_t increment;
    uint16_t i;
    uint16_t j;

    for (increment = n/2U; increment > 0U; increment /= 2U)
    {
        for (i = increment; i < n; i++)
        {
        	temp = array[i];
            for (j = i; j >= increment; j -= increment)
            {
                if(temp < array[j-increment])
                {
                	array[j] = array[j-increment];
                }
                else
                {
                    break;
                }
            }
            array[j] = temp;
        }
    }
}

const char *mw_util_get_filename_ext(const char *filename)
{
    const char *dot = strrchr(filename, '.');

    if (dot == NULL || dot == filename)
    {
    	return ("");
    }

    return (dot + 1);
}

int32_t mw_util_strcicmp(char const *a, char const *b)
{
	int32_t d;

    for (;; a++, b++)
    {
        d = (int32_t)(tolower((unsigned char)*a) - tolower((unsigned char)*b));
        if (d != 0 || *a == '\0')
        {
            return (d);
        }
    }

    return (0);
}

void mw_util_limit_point_to_rect_size(int16_t *x, int16_t *y, const mw_util_rect_t *r)
{
	if (x == NULL || y == NULL || r == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");
		return;
	}

	if (*x < 0)
	{
		*x = 0;
	}
	if (*y < 0)
	{
		*y = 0;
	}
	if (*x >= r->width)
	{
		*x = r->width - 1;
	}
	if (*y >= r->height)
	{
		*y = r->height - 1;
	}
}

char* mw_util_safe_itoa(int32_t value, char *const result, size_t buffer_length, int32_t base, bool do_padding, uint8_t width, char pad_character)
{
	char *interator_pointer = result;
	//char *const original_start_pointer = result;
	char *swap_pointer = result;
	char swap_char;
	int32_t predivision_value;
	uint8_t next_pad_position;

	if (result == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");
		return ("");
	}

	*result = '\0';
	if (buffer_length < 2)
	{
		MW_ASSERT((bool)false, "No buffer space");
		return ("");
	}

	if (base < 2 || base > 16)
	{
		MW_ASSERT((bool)false, "Illegal base");
		return ("");
	}

	if (do_padding && width > (buffer_length - 1))
	{
		MW_ASSERT((bool)false, "Insufficient buffer space");
		return ("");
	}

	/* do the base conversion */
	do
	{
		predivision_value = value;
		value /= base;
		if (interator_pointer - result < (buffer_length - 1))
		{
			*interator_pointer = "FEDCBA9876543210123456789ABCDEF"[15 + (predivision_value - value * base)];
			interator_pointer++;
		}
		else
		{
			/* overflow so give up */
			*result = '\0';
			return ("");
			break;
		}
	}
	while (value);

	/* do padding if required */
	*interator_pointer = '\0';
	if (do_padding)
	{
		for (next_pad_position = strlen(result); next_pad_position < width; next_pad_position++)
		{
			*interator_pointer = pad_character;
			interator_pointer++;
		}
	}

	/* apply negative sign */
	if (predivision_value < 0)
	{
		if (interator_pointer - result < buffer_length - 1)
		{
			*interator_pointer++ = '-';
		}
		else
		{
			/* overflow so give up */
			*result = '\0';
			return ("");
		}
	}
	*interator_pointer = '\0';
	interator_pointer--;

	/* reverse string */
	swap_pointer = result;
	while (swap_pointer < interator_pointer)
	{
		swap_char = *interator_pointer;
		*interator_pointer = *swap_pointer;
		interator_pointer--;
		*swap_pointer = swap_char;
		swap_pointer++;
	}

	return (result);
}
