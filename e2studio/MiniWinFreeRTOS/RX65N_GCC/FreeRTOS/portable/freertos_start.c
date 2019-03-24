#include <iodefine.h>
#include <stdint.h>
#include "freertos.h"
#include "FreeRTOSConfig.h"

void vApplicationSetupTimerInterrupt( void )
{
	const uint32_t ulEnableRegisterWrite = 0xA50BUL, ulDisableRegisterWrite = 0xA500UL;

    /* Disable register write protection. */
    SYSTEM.PRCR.WORD = ulEnableRegisterWrite;

	/* Enable compare match timer 0. */
	MSTP( CMT1 ) = 0;

	/* Interrupt on compare match. */
	CMT1.CMCR.BIT.CMIE = 1;

	/* Set the compare match value. */
	CMT1.CMCOR = ( unsigned short ) ( ( ( configPERIPHERAL_CLOCK_HZ / configTICK_RATE_HZ ) -1 ) / 8 );

	/* Divide the PCLK by 8. */
	CMT1.CMCR.BIT.CKS = 0;

	/* Enable the interrupt... */
	_IEN( _CMT1_CMI1 ) = 1;

	/* ...and set its priority to the application defined kernel priority. */
	_IPR( _CMT1_CMI1 ) = configKERNEL_INTERRUPT_PRIORITY;

	/* Start the timer. */
	CMT.CMSTR0.BIT.STR1 = 1;

    /* Reneable register protection. */
    SYSTEM.PRCR.WORD = ulDisableRegisterWrite;
}
