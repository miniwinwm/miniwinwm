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

#include "miniwin.h"
#include "app.h"
#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

MessageBufferHandle_t gyro_x_message_buffer;
MessageBufferHandle_t gyro_y_message_buffer;
MessageBufferHandle_t gyro_z_message_buffer;

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

/* inter-thread message variables */
static StaticMessageBuffer_t gyro_x_message_buffer_struct;
static StaticMessageBuffer_t gyro_y_message_buffer_struct;
static StaticMessageBuffer_t gyro_z_message_buffer_struct;
static uint8_t gyro_x_message_storage_buffer[10];
static uint8_t gyro_y_message_storage_buffer[10];
static uint8_t gyro_z_message_storage_buffer[10];

/* thread stacks */
static StackType_t main_stack[128];
static StackType_t miniwin_stack[1024];
static StackType_t gyro_stack[128];

/* thread tasks */
static StaticTask_t main_task_handle;
static StaticTask_t miniwin_task_handle;
static StaticTask_t gyro_task_handle;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/*
 * Thread function of main thread
 *
 * @param parameters Thread parameters, if any
 */
static void main_thread(void *parameters);

/*
 * Thread function to run window manager
 *
 * @param parameters Thread parameters, if any
 */
static void miniwin_thread(void *parameters);

/*
 * Thread function to run gyro sensor
 *
 * @param parameters Thread parameters, if any
 */
static void gyro_thread(void *parameters);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static void main_thread(void *parameters)
{
	while (true)
	{
		app_main_loop_process();
		vTaskDelay(100);
    }
}

static void miniwin_thread(void *parameters)
{
	mw_init();

	while (true)
	{
		mw_process_message();
		vTaskDelay(10);
	}
}

static void gyro_thread(void *parameters)
{
	static uint8_t reading_counter = 0;
	TickType_t xLastWakeTime;
	float *gyro_readings;

	xLastWakeTime = xTaskGetTickCount();

	while (true)
	{
		gyro_readings = app_get_gyro_readings();

		/* only send 1 in every 10 readings to window */
		reading_counter++;
		if (reading_counter == 10)
		{
			reading_counter = 0;

			xMessageBufferSend(gyro_x_message_buffer, (void *)&gyro_readings[GYRO_READING_X], sizeof(float), 0);
			xMessageBufferSend(gyro_y_message_buffer, (void *)&gyro_readings[GYRO_READING_Y], sizeof(float), 0);
			xMessageBufferSend(gyro_z_message_buffer, (void *)&gyro_readings[GYRO_READING_Z], sizeof(float), 0);
		}

		/* pause thread for 10 milliseconds */
		vTaskDelayUntil(&xLastWakeTime, 10);
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

int main(void)
{
	app_init();

	/* initialise the message buffers to send gyro reading data from gyro thread to gyro windows */
	gyro_x_message_buffer = xMessageBufferCreateStatic(sizeof(gyro_x_message_storage_buffer),
			gyro_x_message_storage_buffer,
			&gyro_x_message_buffer_struct);
	gyro_y_message_buffer = xMessageBufferCreateStatic(sizeof(gyro_y_message_storage_buffer),
			gyro_y_message_storage_buffer,
			&gyro_y_message_buffer_struct);
	gyro_z_message_buffer = xMessageBufferCreateStatic(sizeof(gyro_z_message_storage_buffer),
			gyro_z_message_storage_buffer,
			&gyro_z_message_buffer_struct);

	/* Create the led task */
	xTaskCreateStatic(main_thread, "MAIN", 128, NULL, 1, main_stack, &main_task_handle);

	/* Create the gyro task */
	xTaskCreateStatic(gyro_thread, "GYRO", 128, NULL, 2, gyro_stack, &gyro_task_handle);

	/* Create the miniwin task */
	xTaskCreateStatic(miniwin_thread, "MINIWIN", 1024, NULL, 1, miniwin_stack, &miniwin_task_handle);

	/* Start the scheduler */
	vTaskStartScheduler();

	while (true);
}

/**
 * FreeRTOS memory allocation for idle task
 */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
		StackType_t **ppxIdleTaskStackBuffer,
		uint32_t *pulIdleTaskStackSize)
{
	static StaticTask_t xIdleTaskTCB;
	static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];

	*ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
	*ppxIdleTaskStackBuffer = uxIdleTaskStack;
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/**
 * FreeRTOS memory allocation for timer task
 */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer,
		StackType_t **ppxTimerTaskStackBuffer,
		uint32_t *pulTimerTaskStackSize)
{
	static StaticTask_t xTimerTaskTCB;
	static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];

	*ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
	*ppxTimerTaskStackBuffer = uxTimerTaskStack;
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
