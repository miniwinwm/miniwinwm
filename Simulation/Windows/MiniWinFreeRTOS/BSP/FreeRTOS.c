#include <windows.h>
#include <stdint.h>
#include <stdbool.h>
#include "FreeRTOS.h"

static float x;
static float y;
static float z;

void vTaskDelay(uint32_t ms)
{
	Sleep(ms);
}

void vTaskStartScheduler(void)
{
	SetPriorityClass( GetCurrentProcess(), REALTIME_PRIORITY_CLASS );

	while (true)
	{
		Sleep(1000);
	}
}

TickType_t xTaskGetTickCount(void)
{
	return 0;
}

void vTaskDelayUntil(TickType_t *last, uint32_t increment)
{
	Sleep(increment);
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
	HANDLE h;

	if (i == 3)
	{
		return;
	}

	h = CreateThread(NULL, 10000, (LPTHREAD_START_ROUTINE)main_thread, NULL, 0, NULL);
	SetThreadPriority(h, THREAD_PRIORITY_TIME_CRITICAL);
	SetThreadPriorityBoost(h, TRUE);
	SetThreadAffinityMask(h, 0x01);
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