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

#ifndef MINWIN_MESSAGE_QUEUE_H
#define MINWIN_MESSAGE_QUEUE_H

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

/************
*** TYPES ***
************/

/*************************
*** EXTERNAL VARIABLES ***
*************************/

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Insert a message at the tail of the message queue
 *
 * @param incoming_message The message to insert
 * @return true if there was space and the message was inserted else false
 */
bool mw_message_queue_insert(const mw_message_t *incoming_message);

/**
 * Remove the message at the head of the message queue
 *
 * @param outgoing_message Pointer to a message structure to copy in the removed message
 * @return true if there was a message else false
 */
bool mw_message_queue_remove(mw_message_t *outgoing_message);

/**
 * Get a pointer to a message at a given position
 *
 * @param position The position in the queue to copy the message from
 * @return Pointer to the message
 * @note This does not change any aspect of the contents of the queue; no message is removed
 */
mw_message_t *mw_message_queue_get_ref_to_item_at_position(uint8_t position);

#ifdef __cplusplus
}
#endif

#endif
