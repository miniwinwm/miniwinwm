/*

MIT License

Copyright (c) John Blaiklock 2019 miniwin Embedded Window Manager

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

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "iodefine.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

volatile const uint8_t *sci2_send_buffer;
volatile uint8_t *sci2_receive_buffer;
volatile uint32_t sci2_buffer_size;
volatile uint32_t sci2_buffer_position;
volatile bool sci2_send_receive_done;

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void sci2_spi_init(void)
{
	/*  setup PJ5 as SPI CS/ */
	PORTJ.PMR.BIT.B5 = 0U;	/* mode to gpio */
	PORTJ.PDR.BIT.B5 = 1U;	/* output */
	PORTJ.ODR1.BIT.B2 = 0U;	/* cmos */
	PORTJ.PODR.BIT.B5 = 1U;	/* set high, unselected */

	/* write key to protect register */
	SYSTEM.PRCR.WORD = 0xa502U;

	/* power on SCI2 */
	SYSTEM.MSTPCRB.BIT.MSTPB29 = 0U;

	/* clear key from protect register */
	SYSTEM.PRCR.WORD = 0xa500U;

	/* disable SCI2 Tx/Rx and disable all interrupts in SCI2 */
	SCI2.SCR.BIT.TE = 0U;
	SCI2.SCR.BIT.RE = 0U;
	SCI2.SCR.BIT.TIE = 0U;
	SCI2.SCR.BIT.RIE = 0U;
	SCI2.SCR.BIT.TEIE = 0U;

	/* allow writing to PFSWE bit */
    MPC.PWPR.BIT.B0WI = 0U;

    /* enable writing to PFS registers. */
    MPC.PWPR.BIT.PFSWE = 1U;

    /* set P51 as SCK2 pin */
    MPC.P51PFS.BYTE = 0x0AU;

    /* set pin mode to peripheral */
    PORT5.PMR.BIT.B1 = 1U;

    /* set P52 as RXD2/SMISO2 pin */
    MPC.P52PFS.BYTE = 0x0AU;

    /* set pin mode to peripheral */
    PORT5.PMR.BIT.B2 = 1U;

    /* set P50 as TXD2/SMOSI2 pin */
    MPC.P50PFS.BYTE = 0x0AU;

    /* set pin mode to peripheral */
    PORT5.PMR.BIT.B0 = 1U;

    /* disable writing MPC */
    MPC.PWPR.BIT.PFSWE = 0U;

    /* disable writing to PFSWE */
    MPC.PWPR.BIT.B0WI = 1U;

    /* set clock to on-chip baud generator */
	SCI2.SCR.BIT.CKE = 0U;

	/* set SCI2 to SPI mode */
	SCI2.SIMR1.BIT.IICM = 0U;

	/* set SPI clock phase to not delayed */
	SCI2.SPMR.BIT.CKPH = 0U;

	/* set SPI clock to not inverted */
	SCI2.SPMR.BIT.CKPOL = 0U;

	/* set SPI master mode */
	SCI2.SPMR.BIT.MSS = 0U;

	/* disable SS pin */
	SCI2.SPMR.BIT.SSE = 0U;

	/* disable CTS function */
	SCI2.SPMR.BIT.CTSE = 0U;

	/* clear any mode fault error */
	SCI2.SPMR.BIT.MFF = 0U;

	/* clock divider 1 */
	SCI2.SMR.BIT.CKS = 0U;

	/* set comms mode to SPI */
	SCI2.SMR.BIT.CM = 1U;

	/* disable smart card mode */
	SCI2.SCMR.BIT.SMIF = 0U;

	/* disable bit invert */
	SCI2.SCMR.BIT.SINV = 0U;

	/* set msb first */
	SCI2.SCMR.BIT.SDIR = 1U;

	/* disable bit rate modulation */
	SCI2.SEMR.BIT.BRME = 0U;

	/* required to be 0 for SPI mode */
	SCI2.SEMR.BIT.NFEN = 0U;

	/* set baud rate to 1Mb/s */
	SCI2.BRR = 0x0eU;

	/* disable TXI2/RXI2 interrupts in ICU */
	IEN(SCI2, RXI2) = 0U;
	IEN(SCI2, TXI2) = 0U;

	/* clear any outstanding RXI2 interrupts */
	IR(SCI2, RXI2) = 0U;

    /* set RXI2 interrupt priority */
	IPR(SCI2, RXI2) = 5U;

	/* enable RXI2 interrupt in ICU */
	IEN(SCI2, RXI2) = 1U;

	/* enable tx, rx, and rx ir */
	SCI2.SCR.BYTE |= 0x70;
}

void sci2_spi_send_receive(const uint8_t *send_buffer, uint8_t *receive_buffer, uint32_t size)
{
	/* check prameter values sensible */
	if (size == 0U || (send_buffer == NULL && receive_buffer == NULL))
	{
		return;
	}

	/* initialize data used in isr */
	sci2_send_buffer = send_buffer;
	sci2_receive_buffer = receive_buffer;
	sci2_buffer_size = size;
	sci2_send_receive_done = false;
	sci2_buffer_position = 0U;

	/* kick off transmission with first byte, either data if sending or dummy if receiving only */
	if (send_buffer == NULL)
	{
		SCI2.TDR = 0xffU;
	}
	else
	{
		SCI2.TDR = send_buffer[0];
	}

	/* further data tranfers happen in rx isr so wait until all sent/received, done flag set in ir handler */
	while (!sci2_send_receive_done)
	{
	}
}
