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

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "miniwin.h"

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

static mw_message_t message_queue[MW_MESSAGE_QUEUE_SIZE];  	/**< Array of structures holding the messages between windows, controls and the system */
static uint8_t items_in_queue;                              /**< Number of items currently in the queue */
static uint8_t next_write_slot;                             /**< Place in storage to write next incoming message */
static uint8_t next_read_slot;                              /**< Place in storage to remove next message from when receiving a read request */
#ifndef NDEBUG
static uint8_t max_queue_usage;                             /**< Always increasing value of how full the queue has ever been */
#endif

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

bool mw_message_queue_insert(const mw_message_t *incoming_message)
{
	/* check pointer */
	MW_ASSERT(incoming_message, "Null pointer argument");

	/* check for space in the queue */
	MW_ASSERT(items_in_queue < MW_MESSAGE_QUEUE_SIZE, "Message queue full");

	/* there's space so copy in the new message */
	memcpy(&message_queue[next_write_slot], incoming_message, sizeof(mw_message_t));
	next_write_slot++;
	if (next_write_slot == MW_MESSAGE_QUEUE_SIZE)
	{
		next_write_slot = 0;
	}

	items_in_queue++;

	/* keep a record of how full the queue becomes in debug mode */
#ifndef NDEBUG
	if (items_in_queue > max_queue_usage)
	{
		max_queue_usage = items_in_queue;
	}
#endif

	return true;
}

bool mw_message_queue_remove(mw_message_t *outgoing_message)
{
	MW_ASSERT(outgoing_message, "Null pointer argument");

	/* check if there is anything in the queue */
	if (items_in_queue == 0)
	{
		return false;
	}

	/* there is an item in the queue so copy it out */
	memcpy(outgoing_message, &message_queue[next_read_slot], sizeof(mw_message_t));
	next_read_slot++;
	if (next_read_slot == MW_MESSAGE_QUEUE_SIZE)
	{
		next_read_slot = 0;
	}

	items_in_queue--;

	return true;
}

mw_message_t *mw_message_queue_get_ref_to_item_at_position(uint8_t position)
{
	MW_ASSERT(position < MW_MESSAGE_QUEUE_SIZE, "Out of bounds message queue position");

	return (&message_queue[position]);
}
