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

#ifdef RX65N_GCC

/***************
*** INCLUDES ***
***************/

#include <stdbool.h>
#include <stdlib.h>
#include <iodefine.h>
#include "hal/hal_touch.h"
#include "hal/hal_delay.h"

/****************
*** CONSTANTS ***
****************/

#define TOUCH_CONTROLLER_I2C_ADDRESS 	0x38U

/************
*** TYPES ***
************/

/**
 * Enumeration of I2C start and stop conditions
 */
typedef enum
{
	start_condition,		/**< Request to create I2C start condition */
	stop_condition  		/**< Request to create I2C stop condition */
} start_stop_condition_t;

/**
 * Enumeration of I2C frame types
 */
typedef enum
{
	read_frame,				/**< Frame type is a read frame */
	write_frame				/**< Frame type is a write frame */
} frame_type_t;

/***********************
*** GLOBAL VARIABLES ***
***********************/

extern volatile bool rx_complete_interrupt_flag;
extern volatile bool tx_complete_interrupt_flag;
extern volatile bool start_complete_interrupt_flag;
extern volatile uint8_t received_byte;

/**********************
*** LOCAL VARIABLES ***
**********************/

static bool first_touch_received = false;
static uint8_t i2c_buffer[7];

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void generate_start_stop_condition(start_stop_condition_t start_stop_condition);
static bool write_device_address(uint8_t device_address, frame_type_t frame_type);
static bool write_device_data(uint8_t device_address, uint8_t *data, uint16_t length);
static bool read_device_data(uint8_t device_address, uint8_t *data, uint16_t length);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Read data from an I2C device where the device register to start reading from has already been set
 *
 * @param device_address The I2C 7 bit address of the device, in bits b0 to b6
 * @param data Pointer to buffer big enough to hold read data
 * @param length Number of bytes to read
 * @return True if in ACK returned by I2C device, false if NACK returned
 */
static bool read_device_data(uint8_t device_address, uint8_t *data, uint16_t length)
{
	bool success = false;
	uint16_t i;

	/* disable read interrupt generation */
	SCI6.SCR.BIT.RIE = 0U;

	generate_start_stop_condition(start_condition);

	/* check ACK received */
	if (write_device_address(device_address, read_frame))
	{
		success = true;

		SCI6.SIMR2.BIT.IICACKT = 0U;

		/* enable read interrupt generation */
		SCI6.SCR.BIT.RIE = 1U;

		for (i = 0U; i < length; i++)
		{
			if (i == length - 1U)
			{
				SCI6.SIMR2.BIT.IICACKT = 1U;
			}

			/* do a dummy write to trigger read */
			SCI6.TDR = 0xffU;

			/* wait for rx interrupt */
			while (!rx_complete_interrupt_flag)
			{
			}
			rx_complete_interrupt_flag = false;

			data[i] = received_byte;

			/* wait for tx interrupt */
			while (!tx_complete_interrupt_flag)
			{
			}
			tx_complete_interrupt_flag = false;
		}
	}

	generate_start_stop_condition(stop_condition);

	return success;
}

/**
 * Write data to an I2C device
 *
 * @param device_address The I2C 7 bit address of the device, in bits b0 to b6
 * @param data Pointer to buffer holding data to write
 * @param length Number of bytes to write
 * @return True if in ACK returned by I2C device, false if NACK returned
 */static bool write_device_data(uint8_t device_address, uint8_t *data, uint16_t length)
{
	bool success = false;
	uint16_t i;

	/* disable read interrupt generation */
	SCI6.SCR.BIT.RIE = 0U;

	generate_start_stop_condition(start_condition);

	if (write_device_address(device_address, write_frame))
	{
		success = true;

		for (i = 0U; i < length; i++)
		{
			SCI6.TDR = data[i];

			/* wait for tx interrupt */
			while (!tx_complete_interrupt_flag)
			{
			}
			tx_complete_interrupt_flag = false;
		}
	}

	generate_start_stop_condition(stop_condition);

	return success;
}

/**
 * Write an I2C device 7 bit address to the SCI6 module
 *
 * @param device_address 7 bit I2C address of target device in bits b0 to b6
 * @param frame_type Read or write frame about to occue
 * @return True if ACK received, false if NACK received
 */
static bool write_device_address(uint8_t device_address, frame_type_t frame_type)
{
	uint8_t byte_to_write;

	byte_to_write = device_address << 1;
	if (frame_type == read_frame)
	{
		byte_to_write++;
	}

	/* send device address to transmit register with write bit */
	SCI6.TDR = byte_to_write;

	/* wait for tx interrupt */
	while (!tx_complete_interrupt_flag)
	{
	}
	tx_complete_interrupt_flag = false;

	/* check ACK received */
	if (SCI6.SISR.BIT.IICACKR == 0U)
	{
		return true;
	}

	return false;
}

/**
 * Make the SCI6 hardware module generate a start or stop condition
 *
 * @param start_stop_condition Start or stop
 */
static void generate_start_stop_condition(start_stop_condition_t start_stop_condition)
{
	switch (start_stop_condition)
	{
	case start_condition:
		/* generate a start condition */
		SCI6.SIMR3.BYTE = 0x51U;
		break;

	case stop_condition:
		/* generate a stop condition */
		SCI6.SIMR3.BYTE = 0x54U;
		break;

	default:
		return;
		break;				/* keep MISRA happy */
	}

	/* wait for start condition completed interrupt */
	while (!start_complete_interrupt_flag)
	{
	}
	start_complete_interrupt_flag = false;

	switch (start_stop_condition)
	{
	case start_condition:
		/* end start condition generation */
		SCI6.SIMR3.BIT.IICSCLS = 0U;
		SCI6.SIMR3.BIT.IICSDAS = 0U;
		break;

	case stop_condition:
		/* end stop condition generation */
		SCI6.SIMR3.BIT.IICSCLS = 3U;
		SCI6.SIMR3.BIT.IICSDAS = 3U;
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_touch_init(void)
{
	/* set up touch interrupt gpio input */
	PORT0.PMR.BIT.B2 = 0U;	/* mode to gpio */
	PORT0.PDR.BIT.B2 = 0U;	/* input */
	PORT0.PCR.BIT.B2 = 0U;  /* pull-up disable */

	/* set up touch reset gpio output */
	PORT0.PMR.BIT.B7 = 0U;	/* mode to gpio */
	PORT0.PDR.BIT.B7 = 1U;	/* output */
	PORT0.ODR1.BIT.B6 = 0U;	/* cmos */

	/* reset touch driver chip */
	PORT0.PODR.BIT.B7 = 0U;
	mw_hal_delay_ms(2U);
	PORT0.PODR.BIT.B7 = 1U;
	mw_hal_delay_ms(100U);

	/* set up pins in pin controller */

	/* enable writing to MPC */
    MPC.PWPR.BIT.B0WI = 0;
    MPC.PWPR.BIT.PFSWE = 1;

    /* set SSCL6 pin to P00 */
    MPC.P01PFS.BYTE = 0x0AU;

    /* set SSCL6 pin to P01 */
    MPC.P00PFS.BYTE = 0x0AU;

    /* disable writing MPC */
    MPC.PWPR.BIT.PFSWE = 0U;
    MPC.PWPR.BIT.B0WI = 1U;


	/* release SCI6 from stop */
	SYSTEM.PRCR.WORD = 0xa502U;
	SYSTEM.MSTPCRB.BIT.MSTPB25 = 0U;
	SYSTEM.PRCR.WORD = 0xa500U;

	/* disable SCI6 and all its interrupts */
    SCI6.SCR.BYTE = 0U;

	/* set P01 drive capacity control high */
	PORT0.DSCR.BIT.B1 = 1U;

	/* set P01 pull-Up resistor off */
	PORT0.PCR.BIT.B1 = 0U;

	/* set P01 port direction to input */
	PORT0.PDR.BIT.B1 = 0U;

	/* set P01 open-drain to NMOS OD output */
	PORT0.ODR0.BIT.B2 = 1U;

	/* set P01 mode to not GPIO */
    PORT0.PMR.BIT.B1 = 1U;

	/* set P00 drive capacity control high */
	PORT0.DSCR.BIT.B0 = 1U;

	/* set P00 pull-up resistor off */
	PORT0.PCR.BIT.B0 = 0U;

	/* set P00 port direction to input */
	PORT0.PDR.BIT.B0 = 0U;

	/* set P00 open-drain to NMOS OD output */
	PORT0.ODR0.BIT.B0 = 1U;

	/* set P00 mode to not GPIO */
    PORT0.PMR.BIT.B0 = 1U;

	/* place i2c pins in high impedance */
	SCI6.SIMR3.BIT.IICSCLS = 3U;
	SCI6.SIMR3.BIT.IICSDAS = 3U;

    /* clock select */
    SCI6.SMR.BYTE = 0;

    /* msb first */
    SCI6.SCMR.BIT.SDIR = 1U;

    /* no inversion */
    SCI6.SCMR.BIT.SINV = 0U;

    /* not smart card mode */
    SCI6.SCMR.BIT.SMIF = 0U;

    /* baud rate */
    SCI6.BRR = 4U;

    /* set noise filter enable */
    SCI6.SEMR.BIT.NFEN = 1U;

    /* bit rate modulation disable */
    SCI6.SEMR.BIT.BRME = 0U;

    /* noie filter clock select */
    SCI6.SNFR.BIT.NFCS = 1U;

    /* select simple IIC mode */
    SCI6.SIMR1.BIT.IICM = 1U;

    /* set SDA output delay */
    SCI6.SIMR1.BIT.IICDL = 18U;

    /* set reception/transmission of ACK/NACK */
    SCI6.SIMR2.BIT.IICACKT = 1U;

    /* clock synch on */
    SCI6.SIMR2.BIT.IICCSC = 1U;

    /* use tx/rx interrupts */
    SCI6.SIMR2.BIT.IICINTM = 1U;

    /* SPI mode off */
    SCI6.SPMR.BYTE = 0U;

    /* enable tx/tx, txi/rxi and tei (used as start/stop bit generation complete) interrupts */
	SCI6.SCR.BYTE = 0xb4U;

	/* enable group BL0 interupt 12 tei (used as start/stop bit generation complete) interrupt) */
	ICU.GENBL0.BIT.EN12 = 1U;

	/* set up group BL0 interrupt for start/stop bit generation complete interrupt */
	IR(ICU, GROUPBL0) = 0U;
	IPR(ICU, GROUPBL0) = 2U;
	IEN(ICU, GROUPBL0) = 1U;

	/* set up rx interrupt */
	IR(SCI6, RXI6) = 0U;
	IPR(SCI6, RXI6) = 5U;
	IEN(SCI6, RXI6) = 1U;

	/* set up transmit interrupt */
	IR(SCI6, TXI6) = 0U;
	IPR(SCI6, TXI6) = 5U;
	IEN(SCI6, TXI6) = 1U;
}

bool mw_hal_touch_is_recalibration_required(void)
{
	/* if board button pressed clear settings which forces a screen recalibration */
	if (PORT0.PIDR.BIT.B5 == 0U)
	{
		return (true);
	}

	return (false);
}

mw_hal_touch_state_t mw_hal_touch_get_state(void)
{
	uint8_t device_register = 0x02U;

	/* touch sensor powers up thinking that there's a touch down so ignore this until touch interrupt
	 * line indicates a real first touch down */
	if (!first_touch_received)
	{
		if (PORT0.PIDR.BIT.B2 == 1U)
		{
			return MW_HAL_TOUCH_STATE_UP;
		}

		first_touch_received = true;
		return MW_HAL_TOUCH_STATE_DOWN;
	}

	/* touch interrupt line is unreliable so interrogate touch module for a touch down */

	/* write register address to touch controller */
	write_device_data(TOUCH_CONTROLLER_I2C_ADDRESS, &device_register, sizeof(device_register));

	/* read data from touch controller starting at register address just written */
	read_device_data(TOUCH_CONTROLLER_I2C_ADDRESS, i2c_buffer, 1);

	if (i2c_buffer[0] > 0U)
	{
		return (MW_HAL_TOUCH_STATE_DOWN);
	}

	return (MW_HAL_TOUCH_STATE_UP);
}

bool mw_hal_touch_get_point(uint16_t* x, uint16_t* y)
{
	uint8_t device_register = 0x02U;

	if (x == NULL || y == NULL)
	{
		return false;
	}

	/* touch sensor powers up thinking that there's a touch down so ignore this until touch interrupt
	 * line indicates a real first touch down */
	if (!first_touch_received)
	{
		if (PORT0.PIDR.BIT.B2 == 1U)
		{
			return false;
		}

		first_touch_received = true;
		return true;
	}

	/* touch interrupt line is unreliable so interrogate touch module for a touch down */

	/* write register address to touch controller */
	write_device_data(TOUCH_CONTROLLER_I2C_ADDRESS, &device_register, sizeof(device_register));

	/* read data from touch controller starting at register address just written */
	read_device_data(TOUCH_CONTROLLER_I2C_ADDRESS, i2c_buffer, sizeof(i2c_buffer));

	if (i2c_buffer[0] > 0U)
	{
		*x = ((uint16_t)(i2c_buffer[1]) & 0x000FU) << 8U | (uint16_t)i2c_buffer[2];
		*y = ((uint16_t)(i2c_buffer[3]) & 0x000FU) << 8U | (uint16_t)i2c_buffer[4];
		return true;
	}

	return false;
}

#endif
