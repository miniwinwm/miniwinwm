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

MessageBufferHandle_t xMessageBufferCreateStatic(size_t s, uint8_t *b, StaticMessageBuffer_t *mb)
{
	static uint8_t h = 0;

	h++;
	return h - 1;
}

void xMessageBufferSend(MessageBufferHandle_t mbh, void *r, size_t s, uint8_t i)
{
	if (mbh == 0)
	{
		x = *(float *)r;
	}
	else if (mbh == 1)
	{
		y = *(float *)r;
	}
	else if (mbh == 2)
	{
		z = *(float *)r;
	}
}

uint8_t xMessageBufferReceive(MessageBufferHandle_t mbh, void *r, size_t s, uint8_t a)
{
	if (mbh == 0)
	{
		*(float *)r = x;
	}
	else if (mbh == 1)
	{
		*(float *)r = y;
	}
	else if (mbh == 2)
	{
		*(float *)r = z;
	}


	return 1;
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
