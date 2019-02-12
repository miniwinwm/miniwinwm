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

#ifndef MINWIN_UTILITIES_H
#define MINWIN_UTILITIES_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/**
 * Rectangle structure
 */
typedef struct
{
	int16_t x;              /**< Left coordinate */
	int16_t y;              /**< Top coordinate */
	int16_t width;          /**< Width, right coordinate is x + width - 1 */
	int16_t height;         /**< Height, bottom coordinate is y + height - 1 */
} mw_util_rect_t;

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Set details of a rect structure.
 *
 * @param r Pointer to rect structure 
 * @param x X value to put in rect structure
 * @param y Y value to put in rect structure
 * @param width Width value to put in rect structure
 * @param height Height value to put in rect structure
 */
void mw_util_set_rect(mw_util_rect_t *r, int16_t x, int16_t y, int16_t width, int16_t height);

/**
 * Determines if a point is in a rect.
 *
 * @param r The rect
 * @param x The x coordinate of the point
 * @param y The y coordinate of the point
 * @return true if in else false
 */
bool mw_util_is_point_in_rect(const mw_util_rect_t *r, int16_t x, int16_t y);

/**
 * Tests if there is any overlap between 2 rects
 *
 * @param a First rect to check
 * @param b Second rect to check
 * @return true if the 2 rects overlap at all else false
 */
bool mw_util_do_rects_coincide(const mw_util_rect_t *a, const mw_util_rect_t *b);

/**
 * Determine if one rect (a) completely covers another (b).
 *
 * @param a Rect a
 * @param b Rect b
 * @return true if a completely obscures b else false
 */
bool mw_util_does_rect_a_obscure_rect_b(const mw_util_rect_t *a, const mw_util_rect_t *b);

/**
 * Perform a safer string copy than strcpy.
 *
 * @param dest Pointer to destination string
 * @param size The size of the dest buffer
 * @param src Pointer to source string to copy
 * @return Pointer to dest with the copied string
 */
char *mw_util_safe_strcpy(char *dest, size_t size, const char *src);

/**
 * Perform a safer string cat than strcat.
 *
 * @param dest Pointer to existing string to be added to
 * @param size The size of the existing string buffer
 * @param src Pointer to string to add
 * @return Pointer to s1 with the concatenated string
 */
char *mw_util_safe_strcat(char *dest, size_t size, const char *src);

/**
 * Change a bit in a supplied 16 bit word and return the changed word
 *
 * @param word The word to change the bit in
 * @param bit The bit position in the word, lsb is 0, msb is 15
 * @param state The new bit state
 * @return The changed word
 */
uint16_t mw_util_change_bit(uint16_t word, uint8_t bit, bool state);

/**
 * Get the state of a bit in a 16 bit word
 *
 * @param word The 16 bit word to query
 * @param bit The bit position in the word, lsb is 0, msb is 15
 * @return The bit state
 */
bool mw_util_get_bit(uint16_t word, uint8_t bit);

/**
 * Sort algorithm for uint16_t data
 *
 * @param array The array of data to sort
 * @param n The number of items in the array
 */
void mw_util_shell_sort(int16_t *array, uint16_t n);


/**
 * Finds the file name extension following a . in a file name.
 * @param filename The full file name
 * @return The extension excluding the ., or an empty string if no . found, or the full file name if it begins with a .
 * @note Never returns null
 */
const char *mw_util_get_filename_ext(const char *filename);

/**
 * Case insensitive string compare
 *
 * @param a First string to compare
 * @param b Second string to compare
 * @return < 0 if a less than b, > 0 if a greater than b or 0 if a and b equal (apart from case)
 */
int32_t mw_util_strcicmp(char const *a, char const *b);

/**
 * Limit a point to a a rect's size changing the point if necessary
 *
 * @param x Pointer to the point's x coordinate
 * @param y Pointer to the point's y coordinate
 * @param r Pointer to the bounding rect
 */
void mw_util_limit_point_to_rect_size(int16_t *x, int16_t *y, const mw_util_rect_t *r);

/**
 * Convert a signed integer value to text equivalent specifying base from 2 to 16
 *
 * @param value The numerical value to convert
 * @param result Buffer to hold the converted text
 * @param buffer_length The number of bytes available in result buffer including terminating null
 * @param base The base to use for the conversion
 * @param do_padding If to do padding
 * @param width The width to do padding to. If a negative sign is needed this is extra. Negative sign is to left of padding.
 * @param pad_character The character to use for padding
 * @return Pointer to the result buffer
 * @note If do_padding is false then width and pad_character are ignored.
 * @note If there is not enough space in the buffer for the number and sign or nuimber, sign and padding if
 *       padding is specified then this function sets result o empty string and returns an empty string.
 */
char* mw_util_safe_itoa(int32_t value, char *const result, uint8_t buffer_length, int32_t base, bool do_padding, uint8_t width, char pad_character);

#ifdef __cplusplus
}
#endif

#endif
