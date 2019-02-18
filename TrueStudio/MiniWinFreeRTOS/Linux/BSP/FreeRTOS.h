#ifndef FREE_RTOS_H
#define FREE_RTOS_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define configMINIMAL_STACK_SIZE 1
#define configTIMER_TASK_STACK_DEPTH 1
typedef uint8_t StackType_t;
typedef uint8_t StaticTask_t;
typedef uint8_t MessageBufferHandle_t;
typedef uint8_t StaticMessageBuffer_t;
typedef uint32_t TickType_t;
typedef uint32_t SemaphoreHandle_t;
typedef uint32_t StaticSemaphore_t;

void vTaskDelay(uint32_t ms);
void vTaskStartScheduler(void);
TickType_t xTaskGetTickCount(void);
void vTaskDelayUntil(TickType_t *last, uint32_t increment);
MessageBufferHandle_t xMessageBufferCreateStatic(size_t s, uint8_t *b, StaticMessageBuffer_t *mb);
void xMessageBufferSend(MessageBufferHandle_t mbh, void *r, size_t s, uint8_t i);
uint8_t xMessageBufferReceive(MessageBufferHandle_t mbh, void *r, size_t s, uint8_t a);
void xTaskCreateStatic(void (main_thread)(void *), char *name, uint32_t ss, void *n, uint8_t u, uint8_t *s, uint8_t *th);
uint32_t xSemaphoreCreateMutexStatic(uint32_t *);
void xSemaphoreGive(uint32_t);
bool xSemaphoreTake(uint32_t, uint32_t);

#endif
