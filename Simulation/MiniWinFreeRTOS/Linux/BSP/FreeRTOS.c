#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include "FreeRTOS.h"

static float x;
static float y;
static float z;
static pthread_t tid[3];

void vTaskDelay(uint32_t ms)
{
	usleep(ms * 1000);
}

void vTaskStartScheduler(void)
{
	while (true)
	{
		sleep(100);
	}
}

TickType_t xTaskGetTickCount(void)
{
	return 0;
}

void vTaskDelayUntil(TickType_t *last, uint32_t increment)
{
	usleep(increment * 1000);
}

QueueHandle_t xQueueCreateStatic(UBaseType_t s1, UBaseType_t s2, uint8_t *sa, StaticQueue_t *b)
{
	static uint8_t h = 0;

	h++;
	return h - 1;
}

void xQueueSend(QueueHandle_t qh, const void *r, TickType_t t)
{
	if (qh == 0)
	{
		x = *(float *)r;
	}
	else if (qh == 1)
	{
		y = *(float *)r;
	}
	else if (qh == 2)
	{
		z = *(float *)r;
	}
}

uint8_t xQueueReceive(QueueHandle_t qh, void *r, TickType_t t)
{
	if (qh == 0)
	{
		*(float *)r = x;
	}
	else if (qh == 1)
	{
		*(float *)r = y;
	}
	else if (qh == 2)
	{
		*(float *)r = z;
	}

	return pdTRUE;
}

void xTaskCreateStatic(void (main_thread)(void *), char *name, uint32_t ss, void *n, uint8_t u, uint8_t *s, uint8_t *th)
{
	static uint8_t i = 0;

	if (i == 3)
	{
		return;
	}

	pthread_create(&tid[i], NULL, (void *(*)(void *))main_thread, NULL);
	i++;
}

uint32_t xSemaphoreCreateMutexStatic(uint32_t * a)
{
	return 0;
}

void xSemaphoreGive(uint32_t a)
{
}

bool xSemaphoreTake(uint32_t a, uint32_t b)
{
	return true;
}
