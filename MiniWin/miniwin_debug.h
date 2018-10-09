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

#ifndef _MINWIN_DEBUG_H
#define _MINWIN_DEBUG_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include <stdint.h>
#include <stdbool.h>

/****************
*** CONSTANTS ***
****************/

#ifdef NDEBUG
#define MW_ASSERT(test)
#else
#define MW_ASSERT(expression, message) mw_debug_print_assert(expression,__func__, __LINE__, message)
#endif

/************
*** TYPES ***
************/

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Print a debug assertion fail message on the display
 * 
 * @param expression true if the assert passed, false if the assert failed
 * @param function_name The name of the function the assertion failed in
 * @param line_number The line number in the file the assertion failed on
 * @param message General purpose text to be displayed on assert failure
 */
void mw_debug_print_assert(bool expression, const char *function_name, int32_t line_number, char *message);

#ifdef __cplusplus
}
#endif

#endif
