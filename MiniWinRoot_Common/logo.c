/***************
*** INCLUDES ***
***************/

#include <stdint.h>
#include "miniwin_user.h"

/****************
*** CONSTANTS ***
****************/

/* Bitmap width: 66 */
/* Bitmap height: 92 */

const uint8_t logo_array[] = {
  0xffU, 0xffU, 0xc7U, 0xffU, 0xffU, 0xf8U, 0x7fU, 0xffU, 0xc0U,
  0xffU, 0xffU, 0xc7U, 0xffU, 0xffU, 0xf8U, 0x7fU, 0xffU, 0xc0U,
  0xffU, 0xffU, 0x83U, 0xffU, 0xffU, 0xf0U, 0x7fU, 0xffU, 0xc0U,
  0xffU, 0xffU, 0x81U, 0xffU, 0xffU, 0xe0U, 0x3fU, 0xffU, 0xc0U,
  0xffU, 0xffU, 0x81U, 0xffU, 0xffU, 0xe0U, 0x3fU, 0xffU, 0xc0U,
  0xffU, 0xffU, 0x00U, 0xffU, 0xffU, 0xc0U, 0x1fU, 0xffU, 0xc0U,
  0xffU, 0xffU, 0x00U, 0xffU, 0xffU, 0xc0U, 0x1fU, 0xffU, 0xc0U,
  0xffU, 0xfeU, 0x00U, 0x7fU, 0xffU, 0x80U, 0x1fU, 0xffU, 0xc0U,
  0xffU, 0xfeU, 0x00U, 0x7fU, 0xffU, 0x80U, 0x0fU, 0xffU, 0xc0U,
  0xffU, 0xfcU, 0x00U, 0x3fU, 0xffU, 0x00U, 0x0fU, 0xffU, 0xc0U,
  0xffU, 0xfcU, 0x00U, 0x3fU, 0xffU, 0x00U, 0x07U, 0xffU, 0xc0U,
  0xffU, 0xf8U, 0x00U, 0x1fU, 0xffU, 0x00U, 0x07U, 0xffU, 0xc0U,
  0xffU, 0xf8U, 0x00U, 0x1fU, 0xfeU, 0x00U, 0x07U, 0xffU, 0xc0U,
  0xffU, 0xf8U, 0x00U, 0x0fU, 0xfeU, 0x00U, 0x03U, 0xffU, 0xc0U,
  0xffU, 0xf0U, 0x00U, 0x07U, 0xfcU, 0x00U, 0x03U, 0xffU, 0xc0U,
  0xffU, 0xf0U, 0x00U, 0x07U, 0xfcU, 0x00U, 0x01U, 0xffU, 0xc0U,
  0xffU, 0xe0U, 0x00U, 0x03U, 0xf8U, 0x00U, 0x01U, 0xffU, 0xc0U,
  0xffU, 0xe0U, 0x00U, 0x01U, 0xf8U, 0x00U, 0x01U, 0xffU, 0xc0U,
  0xffU, 0xc0U, 0x00U, 0x01U, 0xf0U, 0x00U, 0x00U, 0xffU, 0xc0U,
  0xffU, 0xc0U, 0x00U, 0x00U, 0xe0U, 0x00U, 0x00U, 0xffU, 0xc0U,
  0xffU, 0x80U, 0x00U, 0x00U, 0xe0U, 0x00U, 0x00U, 0x7fU, 0xc0U,
  0xffU, 0x80U, 0x00U, 0x00U, 0x40U, 0x00U, 0x00U, 0x7fU, 0xc0U,
  0xffU, 0x80U, 0x00U, 0x00U, 0x40U, 0x00U, 0x00U, 0x3fU, 0xc0U,
  0xffU, 0x80U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x3fU, 0xc0U,
  0xffU, 0x80U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x3fU, 0xc0U,
  0xffU, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x1fU, 0xc0U,
  0xffU, 0x08U, 0x00U, 0x00U, 0x02U, 0x00U, 0x00U, 0x0fU, 0xc0U,
  0xfeU, 0x08U, 0x00U, 0x00U, 0x06U, 0x00U, 0x00U, 0x0fU, 0xc0U,
  0xfeU, 0x1cU, 0x00U, 0x00U, 0x07U, 0x00U, 0x00U, 0x07U, 0xc0U,
  0xfeU, 0x1cU, 0x00U, 0x00U, 0x0fU, 0x00U, 0x00U, 0x07U, 0xc0U,
  0xfcU, 0x1eU, 0x00U, 0x00U, 0x1fU, 0x00U, 0x00U, 0x03U, 0xc0U,
  0xfcU, 0x3fU, 0x00U, 0x00U, 0x1fU, 0x80U, 0x00U, 0x03U, 0xc0U,
  0xf8U, 0x3fU, 0x00U, 0x00U, 0x3fU, 0x80U, 0x00U, 0x01U, 0xc0U,
  0xf8U, 0x7fU, 0x80U, 0x00U, 0x3fU, 0xc0U, 0x00U, 0x01U, 0xc0U,
  0xf0U, 0x7fU, 0x80U, 0x00U, 0x7fU, 0xc0U, 0x00U, 0x00U, 0xc0U,
  0xf0U, 0x7fU, 0xc0U, 0x00U, 0x7fU, 0xc0U, 0x00U, 0x00U, 0xc0U,
  0xe0U, 0x7fU, 0xc0U, 0x00U, 0xffU, 0xe0U, 0x00U, 0x00U, 0xc0U,
  0xe0U, 0xffU, 0xe0U, 0x00U, 0xffU, 0xe0U, 0x00U, 0x00U, 0x40U,
  0xe0U, 0xffU, 0xf0U, 0x01U, 0xffU, 0xf0U, 0x00U, 0x00U, 0x40U,
  0xc1U, 0xffU, 0xf0U, 0x01U, 0xffU, 0xf0U, 0x00U, 0x00U, 0x00U,
  0xc1U, 0xffU, 0xf8U, 0x03U, 0xffU, 0xf0U, 0x00U, 0x00U, 0x00U,
  0x81U, 0xffU, 0xf8U, 0x07U, 0xffU, 0xf8U, 0x00U, 0x00U, 0x00U,
  0x83U, 0xffU, 0xfcU, 0x07U, 0xffU, 0xf8U, 0x00U, 0x00U, 0x00U,
  0x03U, 0xffU, 0xfcU, 0x0fU, 0xffU, 0xfcU, 0x00U, 0x00U, 0x00U,
  0x07U, 0xffU, 0xfeU, 0x0fU, 0xffU, 0xfcU, 0x00U, 0x00U, 0x00U,
  0x07U, 0xffU, 0xfeU, 0x1fU, 0xffU, 0xfcU, 0x00U, 0x00U, 0x00U,
  0x00U, 0x00U, 0x07U, 0xffU, 0xffU, 0x9fU, 0xffU, 0xfeU, 0x00U,
  0x00U, 0x00U, 0x07U, 0xffU, 0xffU, 0x0fU, 0xffU, 0xfeU, 0x00U,
  0x80U, 0x00U, 0x07U, 0xffU, 0xffU, 0x0fU, 0xffU, 0xfeU, 0x00U,
  0x80U, 0x00U, 0x03U, 0xffU, 0xfeU, 0x07U, 0xffU, 0xfcU, 0x00U,
  0xc0U, 0x00U, 0x03U, 0xffU, 0xfeU, 0x07U, 0xffU, 0xfcU, 0x00U,
  0xc0U, 0x00U, 0x01U, 0xffU, 0xfcU, 0x03U, 0xffU, 0xf8U, 0x40U,
  0xe0U, 0x00U, 0x01U, 0xffU, 0xf8U, 0x03U, 0xffU, 0xf8U, 0x40U,
  0xe0U, 0x00U, 0x01U, 0xffU, 0xf8U, 0x01U, 0xffU, 0xf8U, 0xc0U,
  0xf0U, 0x00U, 0x00U, 0xffU, 0xf0U, 0x01U, 0xffU, 0xf0U, 0xc0U,
  0xf0U, 0x00U, 0x00U, 0xffU, 0xf0U, 0x00U, 0xffU, 0xf0U, 0xc0U,
  0xf0U, 0x00U, 0x00U, 0x7fU, 0xe0U, 0x00U, 0x7fU, 0xe1U, 0xc0U,
  0xf8U, 0x00U, 0x00U, 0x7fU, 0xe0U, 0x00U, 0x7fU, 0xe1U, 0xc0U,
  0xf8U, 0x00U, 0x00U, 0x7fU, 0xc0U, 0x00U, 0x3fU, 0xe3U, 0xc0U,
  0xfcU, 0x00U, 0x00U, 0x3fU, 0xc0U, 0x00U, 0x3fU, 0xc3U, 0xc0U,
  0xfcU, 0x00U, 0x00U, 0x3fU, 0x80U, 0x00U, 0x1fU, 0xc7U, 0xc0U,
  0xfeU, 0x00U, 0x00U, 0x1fU, 0x80U, 0x00U, 0x1fU, 0x87U, 0xc0U,
  0xfeU, 0x00U, 0x00U, 0x1fU, 0x00U, 0x00U, 0x0fU, 0x8fU, 0xc0U,
  0xfeU, 0x00U, 0x00U, 0x1eU, 0x00U, 0x00U, 0x07U, 0x8fU, 0xc0U,
  0xffU, 0x00U, 0x00U, 0x0eU, 0x00U, 0x00U, 0x07U, 0x0fU, 0xc0U,
  0xffU, 0x00U, 0x00U, 0x0cU, 0x00U, 0x00U, 0x03U, 0x1fU, 0xc0U,
  0xffU, 0x80U, 0x00U, 0x04U, 0x00U, 0x00U, 0x02U, 0x1fU, 0xc0U,
  0xffU, 0x80U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x3fU, 0xc0U,
  0xffU, 0x80U, 0x00U, 0x00U, 0x40U, 0x00U, 0x00U, 0x3fU, 0xc0U,
  0xffU, 0xc0U, 0x00U, 0x00U, 0xc0U, 0x00U, 0x00U, 0x7fU, 0xc0U,
  0xffU, 0xc0U, 0x00U, 0x00U, 0xe0U, 0x00U, 0x00U, 0x7fU, 0xc0U,
  0xffU, 0xe0U, 0x00U, 0x01U, 0xe0U, 0x00U, 0x00U, 0x7fU, 0xc0U,
  0xffU, 0xe0U, 0x00U, 0x01U, 0xf0U, 0x00U, 0x00U, 0xffU, 0xc0U,
  0xffU, 0xf0U, 0x00U, 0x03U, 0xf0U, 0x00U, 0x00U, 0xffU, 0xc0U,
  0xffU, 0xf0U, 0x00U, 0x07U, 0xf8U, 0x00U, 0x01U, 0xffU, 0xc0U,
  0xffU, 0xf0U, 0x00U, 0x07U, 0xfcU, 0x00U, 0x01U, 0xffU, 0xc0U,
  0xffU, 0xf8U, 0x00U, 0x0fU, 0xfcU, 0x00U, 0x03U, 0xffU, 0xc0U,
  0xffU, 0xf8U, 0x00U, 0x0fU, 0xfeU, 0x00U, 0x03U, 0xffU, 0xc0U,
  0xffU, 0xfcU, 0x00U, 0x1fU, 0xfeU, 0x00U, 0x07U, 0xffU, 0xc0U,
  0xffU, 0xfcU, 0x00U, 0x1fU, 0xffU, 0x00U, 0x07U, 0xffU, 0xc0U,
  0xffU, 0xfcU, 0x00U, 0x3fU, 0xffU, 0x00U, 0x07U, 0xffU, 0xc0U,
  0xffU, 0xfeU, 0x00U, 0x3fU, 0xffU, 0x80U, 0x0fU, 0xffU, 0xc0U,
  0xffU, 0xfeU, 0x00U, 0x7fU, 0xffU, 0x80U, 0x0fU, 0xffU, 0xc0U,
  0xffU, 0xffU, 0x00U, 0x7fU, 0xffU, 0xc0U, 0x1fU, 0xffU, 0xc0U,
  0xffU, 0xffU, 0x00U, 0xffU, 0xffU, 0xc0U, 0x1fU, 0xffU, 0xc0U,
  0xffU, 0xffU, 0x00U, 0xffU, 0xffU, 0xe0U, 0x3fU, 0xffU, 0xc0U,
  0xffU, 0xffU, 0x81U, 0xffU, 0xffU, 0xe0U, 0x3fU, 0xffU, 0xc0U,
  0xffU, 0xffU, 0x81U, 0xffU, 0xffU, 0xf0U, 0x7fU, 0xffU, 0xc0U,
  0xffU, 0xffU, 0xc3U, 0xffU, 0xffU, 0xf0U, 0x7fU, 0xffU, 0xc0U,
  0xffU, 0xffU, 0xc7U, 0xffU, 0xffU, 0xf8U, 0x7fU, 0xffU, 0xc0U,
  0xffU, 0xffU, 0xc7U, 0xffU, 0xffU, 0xfcU, 0xffU, 0xffU, 0xc0U,
  0xffU, 0xffU, 0xefU, 0xffU, 0xffU, 0xfcU, 0xffU, 0xffU, 0xc0U};

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

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
