/***********************************************************************
*
*  FILE        : frtost.c
*  DATE        : 2019-03-05
*  DESCRIPTION : Main Program
*
*  NOTE:THIS IS A TYPICAL EXAMPLE.
*
***********************************************************************/
#include "r_smc_entry.h"
#include "FreeRTOS.h"
#include "task.h"

void vTask1(void *pvParameters)
{
	while(1) {
		PORTD.PODR.BIT.B6 = ~PORTD.PODR.BIT.B6;
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}

void vTask2(void *pvParameters)
{
	while(1)
	{
		PORTD.PODR.BIT.B7 = ~PORTD.PODR.BIT.B7;
		vTaskDelay(100/portTICK_PERIOD_MS);
	}
}

static StackType_t main1_stack[128];
static StackType_t main2_stack[128];


static StaticTask_t main1_task_handle;
static StaticTask_t main2_task_handle;


void main(void)
{
	xTaskCreateStatic(vTask1, "MAIN", 100, NULL, 1, main1_stack, &main1_task_handle);
	xTaskCreateStatic(vTask2, "MAIN", 100, NULL, 1, main2_stack, &main2_task_handle);

	vTaskStartScheduler();


	while(1);
}


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
 *
 * @param ppxIdleTaskTCBBuffer Pointer to pointer of timer task TCB
 * @param ppxIdleTaskStackBuffer Pointer to pointer of timer task stack
 * @param pulIdleTaskStackSize Pointer to timer task stack size
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

void vApplicationSetupTimerInterrupt( void )
{
const uint32_t ulEnableRegisterWrite = 0xA50BUL, ulDisableRegisterWrite = 0xA500UL;

    /* Disable register write protection. */
    SYSTEM.PRCR.WORD = ulEnableRegisterWrite;

	/* Enable compare match timer 0. */
	MSTP( CMT0 ) = 0;

	/* Interrupt on compare match. */
	CMT0.CMCR.BIT.CMIE = 1;

	/* Set the compare match value. */
	CMT0.CMCOR = ( unsigned short ) ( ( ( configPERIPHERAL_CLOCK_HZ / configTICK_RATE_HZ ) -1 ) / 8 );

	/* Divide the PCLK by 8. */
	CMT0.CMCR.BIT.CKS = 0;

	/* Enable the interrupt... */
	_IEN( _CMT0_CMI0 ) = 1;

	/* ...and set its priority to the application defined kernel priority. */
	_IPR( _CMT0_CMI0 ) = configKERNEL_INTERRUPT_PRIORITY;

	/* Start the timer. */
	CMT.CMSTR0.BIT.STR0 = 1;

    /* Reneable register protection. */
    SYSTEM.PRCR.WORD = ulDisableRegisterWrite;
}
