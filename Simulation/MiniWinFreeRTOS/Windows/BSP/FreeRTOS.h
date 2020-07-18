#ifndef FREE_RTOS_H
#define FREE_RTOS_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define configMINIMAL_STACK_SIZE 1
#define configTIMER_TASK_STACK_DEPTH 1
#define pdTRUE 1
typedef uint8_t StackType_t;
typedef uint8_t StaticTask_t;
typedef uint8_t QueueHandle_t;
typedef uint32_t TickType_t;
typedef uint32_t SemaphoreHandle_t;
typedef uint32_t StaticSemaphore_t;
typedef uint32_t UBaseType_t;
typedef uint32_t StaticQueue_t;

void vTaskDelay(uint32_t ms);
void vTaskStartScheduler(void);
TickType_t xTaskGetTickCount(void);
void vTaskDelayUntil(TickType_t *last, uint32_t increment);
void xTaskCreateStatic(void (main_thread)(void *), char *name, uint32_t ss, void *n, uint8_t u, uint8_t *s, uint8_t *th);
uint32_t xSemaphoreCreateMutexStatic(uint32_t *);
void xSemaphoreGive(uint32_t);
bool xSemaphoreTake(uint32_t, uint32_t);
uint8_t xQueueReceive(QueueHandle_t qh, void *r, TickType_t t);
void xQueueSend(QueueHandle_t qh, const void *r, TickType_t t);
QueueHandle_t xQueueCreateStatic(UBaseType_t s1, UBaseType_t s2, uint8_t *sa, StaticQueue_t *b);

#endif
