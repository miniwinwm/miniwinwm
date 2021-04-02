/*

MIT License

Copyright (c) John Blaiklock 2020 miniwin Embedded Window Manager

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

#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "miniwin.h"
#include "app.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

QueueHandle_t gyro_x_queue;
QueueHandle_t gyro_y_queue;
QueueHandle_t gyro_z_queue;

/**********************
*** LOCAL VARIABLES ***
**********************/

/* inter-thread message variables */
static StaticQueue_t gyro_x_queue_buffer;
static StaticQueue_t gyro_y_queue_buffer;
static StaticQueue_t gyro_z_queue_buffer;
static uint8_t gyro_x_queue_storage_area[sizeof(float)];
static uint8_t gyro_y_queue_storage_area[sizeof(float)];
static uint8_t gyro_z_queue_storage_area[sizeof(float)];

/* thread stacks */
static StackType_t main_stack[512];
static StackType_t miniwin_stack[4096];
static StackType_t gyro_stack[512];

/* thread tasks */
static StaticTask_t main_task_handle;
static StaticTask_t miniwin_task_handle;
static StaticTask_t gyro_task_handle;

/* thread synchronization */
static SemaphoreHandle_t semaphore_handle;
static StaticSemaphore_t semaphore_buffer;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**
 * Thread function of main thread
 *
 * @param parameters Thread parameters, if any
 */
static void main_thread(void *parameters);

/**
 * Thread function to run window manager
 *
 * @param parameters Thread parameters, if any
 */
static void miniwin_thread(void *parameters);

/**
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
		vTaskDelay(100U);
    }
}

static void miniwin_thread(void *parameters)
{
	/* initialize miniwin */
	mw_init();

	while (true)
	{
    	/* do miniwin message processing */
		if (xSemaphoreTake(semaphore_handle, (TickType_t)10) == 0)
		{
			vTaskDelay(10U);
			continue;
		}

		(void)mw_process_message();

		/* the next line cannot be made MISRA compliant because of the FreeRTOS API */
		xSemaphoreGive(semaphore_handle);
		vTaskDelay(10U);
	}
}

static void gyro_thread(void *parameters)
{
	static uint8_t reading_counter = 0U;
	TickType_t xLastWakeTime;
	float *gyro_readings;

	/* wait until window manager is started */
	while (!mw_is_init_complete())
	{
		vTaskDelay(100);
	}

	xLastWakeTime = xTaskGetTickCount();
	while (true)
	{
		if (xSemaphoreTake(semaphore_handle, (TickType_t)10) == 0)
		{
			continue;
		}

		gyro_readings = app_get_gyro_readings();

		/* the next line cannot be made MISRA compliant because of the FreeRTOS API */
		xSemaphoreGive(semaphore_handle);

		/* only send 1 in every 10 readings to window */
		reading_counter++;
		if (reading_counter == 10U)
		{
			reading_counter = 0U;

			/* the next 3 lines cannot be made MISRA compliant because of the FreeRTOS API */
			(void)xQueueSend(gyro_x_queue, ((const void *)(gyro_readings + GYRO_READING_X)), (TickType_t)0);
			(void)xQueueSend(gyro_y_queue, ((const void *)(gyro_readings + GYRO_READING_Y)), (TickType_t)0);
			(void)xQueueSend(gyro_z_queue, ((const void *)(gyro_readings + GYRO_READING_Z)), (TickType_t)0);
		}

		/* pause thread until next reading */
		vTaskDelayUntil(&xLastWakeTime, 10U);
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

int app_main(void)
{
	/* initialize non-miniwin parts of the application */
	app_init();

	/* the next 3 lines cannot be made MISRA compliant because of the FreeRTOS API */

	/* initialise the message buffers to send gyro reading data from gyro thread to gyro windows */
	gyro_x_queue = xQueueCreateStatic(1, sizeof(float), gyro_x_queue_storage_area, &gyro_x_queue_buffer);
	gyro_y_queue = xQueueCreateStatic(1, sizeof(float), gyro_y_queue_storage_area, &gyro_y_queue_buffer);
	gyro_z_queue = xQueueCreateStatic(1, sizeof(float), gyro_z_queue_storage_area, &gyro_z_queue_buffer);

	/* initialize the mutex */
	semaphore_handle = xSemaphoreCreateMutexStatic(&semaphore_buffer);

	/* create the led task */
	(void)xTaskCreateStatic(main_thread, "MAIN", 512U, NULL, 1, main_stack, &main_task_handle);

	/* create the gyro task */
	(void)xTaskCreateStatic(gyro_thread, "GYRO", 512U, NULL, 2, gyro_stack, &gyro_task_handle);

	/* create the miniwin task */
	(void)xTaskCreateStatic(miniwin_thread, "MINIWIN", 4096U, NULL, 1, miniwin_stack, &miniwin_task_handle);

	while (true)
	{
		vTaskDelay(10U);
	}
}
