/*

MIT License

Copyright (c) John Blaiklock 2021 miniwin Embedded Window Manager

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
#include <stdint.h>
#include "iodefine.h"

/****************
*** CONSTANTS ***
****************/

#define _00_TMR_CNT_CLR_DISABLE                     (0x00U) /* Clearing is disabled */
#define _08_TMR_CNT_CLR_COMP_MATCH_A                (0x08U) /* Cleared by compare match A */
#define _00_TMR_CMIA_INT_DISABLE                    (0x00U) /* Compare match A interrupt (CMIAn) are disabled */
#define _00_TMR_CMIB_INT_DISABLE                    (0x00U) /* Compare match B interrupt (CMIBn) are disabled */
#define _00_TMR_OVI_INT_DISABLE                     (0x00U) /* Overflow interrupt requests (OVIn) are disabled */
#define _00_TMR_COMP_MATCH_B_OUTPUT_RETAIN          (0x00U) /* No change */
#define _03_TMR_COMP_MATCH_A_OUTPUT_TOGGLE          (0x03U) /* Toggle output */
#define _F0_TMR13_TCSR_DEFAULT                      (0xF0U) /* Default TCSR write value for TMR1/3 */
#define _01_TMR3_COMP_MATCH_VALUE_A             	(0x01U)
#define _01_TMR3_COMP_MATCH_VALUE_B             	(0x01U)
#define _08_TMR_CLK_SRC_PCLK                        (0x08U) /* Use PCLK */
#define _00_TMR_PCLK_DIV_1                          (0x00U) /* Count at PCLK */
#define BSP_REG_PROTECT_MPC
#define OV7670_WRITE_ADDR 							0x42

static const uint8_t OV7670_register_setup[][2] =
{
	{0x12U, 0x80U},		/* Reset registers */

	/* image format */
	{0x12U, 0x14U},		/* QVGA sizeU, RGB mode */

	{0x40U, 0xd0U},		/* RGB565 */
	{0xb0U, 0x84U},		/* Color mode */

	/* hardware window */
	{0x11U, 0x01U},		/* PCLK settingsU, 15 fps */
	{0x32U, 0x80U},		/* HREF */
	{0x17U, 0x17U},		/* HSTART */
	{0x18U, 0x05U},		/* HSTOP */
	{0x03U, 0x0aU},		/* VREF */
	{0x19U, 0x02U},		/* VSTART */
	{0x1aU, 0x7aU},		/* VSTOP */

	/* scaling numbers */
	{0x70U, 0x3aU},		/* X_SCALING */
	{0x71U, 0x35U},		/* Y_SCALING */
	{0x72U, 0x11U},		/* DCW_SCALING */
	{0x73U, 0xf0U},		/* PCLK_DIV_SCALING */
	{0xa2U, 0x02U},		/* PCLK_DELAY_SCALING */

	/* matrix coefficients */
	{0x4fU, 0x80U},		{0x50U, 0x80U},
	{0x51U, 0x00U},		{0x52U, 0x22U},
	{0x53U, 0x5eU},		{0x54U, 0x80U},
	{0x58U, 0x9eU},

	/* gamma curve values */
	{0x7aU, 0x20U},		{0x7bU, 0x10U},
	{0x7cU, 0x1eU},		{0x7dU, 0x35U},
	{0x7eU, 0x5aU},		{0x7fU, 0x69U},
	{0x80U, 0x76U},		{0x81U, 0x80U},
	{0x82U, 0x88U},		{0x83U, 0x8fU},
	{0x84U, 0x96U},		{0x85U, 0xa3U},
	{0x86U, 0xafU},		{0x87U, 0xc4U},
	{0x88U, 0xd7U},		{0x89U, 0xe8U},

	/* AGC and AEC parameters */
	{0xa5U, 0x05U},		{0xabU, 0x07U},
	{0x24U, 0x95U},		{0x25U, 0x33U},
	{0x26U, 0xe3U},		{0x9fU, 0x78U},
	{0xa0U, 0x68U},		{0xa1U, 0x03U},
	{0xa6U, 0xd8U},		{0xa7U, 0xd8U},
	{0xa8U, 0xf0U},		{0xa9U, 0x90U},
	{0xaaU, 0x94U},		{0x10U, 0x00U},

	/* AWB parameters */
	{0x43U, 0x0aU},		{0x44U, 0xf0U},
	{0x45U, 0x34U},		{0x46U, 0x58U},
	{0x47U, 0x28U},		{0x48U, 0x3aU},
	{0x59U, 0x88U},		{0x5aU, 0x88U},
	{0x5bU, 0x44U},		{0x5cU, 0x67U},
	{0x5dU, 0x49U},		{0x5eU, 0x0eU},
	{0x6cU, 0x0aU},		{0x6dU, 0x55U},
	{0x6eU, 0x11U},		{0x6fU, 0x9fU},
	{0x6aU, 0x40U},		{0x01U, 0x40U},
	{0x02U, 0x60U},		{0x13U, 0xe7U},

	/* additional parameters */
	{0x34U, 0x11U},		{0x3fU, 0x00U},
	{0x75U, 0x05U},		{0x76U, 0xe1U},
	{0x4cU, 0x00U},		{0x77U, 0x01U},
	{0xb8U, 0x0aU},		{0x41U, 0x18U},
	{0x3bU, 0x12U},		{0xa4U, 0x88U},
	{0x96U, 0x00U},		{0x97U, 0x30U},
	{0x98U, 0x20U},		{0x99U, 0x30U},
	{0x9aU, 0x84U},		{0x9bU, 0x29U},
	{0x9cU, 0x03U},		{0x9dU, 0x4cU},
	{0x9eU, 0x3fU},		{0x78U, 0x04U},
	{0x0eU, 0x61U},		{0x0fU, 0x4bU},
	{0x16U, 0x02U},		{0x1eU, 0x00U},
	{0x21U, 0x02U},		{0x22U, 0x91U},
	{0x29U, 0x07U},		{0x33U, 0x0bU},
	{0x35U, 0x0bU},		{0x37U, 0x1dU},
	{0x38U, 0x71U},		{0x39U, 0x2aU},
	{0x3cU, 0x78U},		{0x4dU, 0x40U},
	{0x4eU, 0x20U},		{0x69U, 0x00U},
	{0x6bU, 0x3aU},		{0x74U, 0x10U},
	{0x8dU, 0x4fU},		{0x8eU, 0x00U},
	{0x8fU, 0x00U},		{0x90U, 0x00U},
	{0x91U, 0x00U},		{0x96U, 0x00U},
	{0x9aU, 0x00U},		{0xb1U, 0x0cU},
	{0xb2U, 0x0eU},		{0xb3U, 0x82U},
	{0x4bU, 0x01U}
};

/************
*** TYPES ***
************/

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

/**********************
*** LOCAL VARIABLES ***
**********************/

static volatile bool rx_complete_interrupt_flag = false;
static volatile bool tx_complete_interrupt_flag = false;
static volatile uint8_t received_byte;
static uint8_t frame_buffer[160 * 120 * 2];

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void xclk_init(void);
static void sccb_init(void);
static void generate_start_stop_condition(start_stop_condition_t start_stop_condition);
static bool write_device_address(uint8_t device_address, frame_type_t frame_type);
static bool write_device_data(uint8_t device_address, const uint8_t *data, uint16_t length);
static void delay(volatile uint16_t count);
static void cam_paralell_io_init(void);
static void ov7670_init(void);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static void xclk_init(void)
{
    /* Enable writing to MPC pin function control registers */
    MPC.PWPR.BIT.B0WI = 0U;
    MPC.PWPR.BIT.PFSWE = 1U;

    /* Set TMO3 pin */
    MPC.P55PFS.BYTE = 0x05U;
    PORT5.PMR.BYTE |= 0x20U;

    /* Disable writing to MPC pin function control registers */
    MPC.PWPR.BIT.PFSWE = 0U;
    MPC.PWPR.BIT.B0WI = 1U;

    /* Disable protection */
    SYSTEM.PRCR.WORD = 0xA50BU;

    /* Cancel TMR module stop state */
    MSTP(TMR23) = 0U;

    /* Enable protection */
    SYSTEM.PRCR.WORD = 0xA500U;

    /* Set counter clear and interrupt */
    TMR3.TCR.BYTE = _08_TMR_CNT_CLR_COMP_MATCH_A | _00_TMR_CMIA_INT_DISABLE | _00_TMR_CMIB_INT_DISABLE |
                    _00_TMR_OVI_INT_DISABLE;

    /* Set output */
    TMR3.TCSR.BYTE = _00_TMR_COMP_MATCH_B_OUTPUT_RETAIN | _03_TMR_COMP_MATCH_A_OUTPUT_TOGGLE | _F0_TMR13_TCSR_DEFAULT;

    /* Set compare match value */
    TMR3.TCORA = _01_TMR3_COMP_MATCH_VALUE_A;
    TMR3.TCORB = _01_TMR3_COMP_MATCH_VALUE_B;

    /*Start counting*/
    TMR3.TCCR.BYTE = _08_TMR_CLK_SRC_PCLK | _00_TMR_PCLK_DIV_1;
}

#pragma interrupt (INT_Excep_SCI2_RXI2(vect=VECT_SCI2_RXI2))
void INT_Excep_SCI2_RXI2(void)
{
	received_byte = SCI2.RDR;
	rx_complete_interrupt_flag = true;
}

#pragma interrupt (INT_Excep_SCI2_TXI2(vect=VECT_SCI2_TXI2))
void INT_Excep_SCI2_TXI2(void)
{
	tx_complete_interrupt_flag = true;
}

static void sccb_init(void)
{
	/* set up pins in pin controller */

	/* enable writing to MPC */
    MPC.PWPR.BIT.B0WI = 0;
    MPC.PWPR.BIT.PFSWE = 1;

    /* set SSDA2 pin to P50 */
    MPC.P50PFS.BYTE = 0x0AU;

    /* set SSCL2 pin to P52 */
    MPC.P52PFS.BYTE = 0x0AU;

    /* disable writing MPC */
    MPC.PWPR.BIT.PFSWE = 0U;
    MPC.PWPR.BIT.B0WI = 1U;


	/* release SCI2 from stop */
	SYSTEM.PRCR.WORD = 0xa502U;
	SYSTEM.MSTPCRB.BIT.MSTPB29 = 0U;
	SYSTEM.PRCR.WORD = 0xa500U;

	/* disable SCI2 and all its interrupts */
    SCI2.SCR.BYTE = 0U;

	/* set P52 drive capacity control high */
	PORT5.DSCR.BIT.B2 = 1U;

	/* set P52 pull-Up resistor off */
	PORT5.PCR.BIT.B2 = 1U;

	/* set P52 port direction to input */
	PORT5.PDR.BIT.B2 = 0U;

	/* set P52 open-drain to NMOS OD output */
	PORT5.ODR0.BIT.B4 = 1U;

	/* set P52 mode to not GPIO */
    PORT5.PMR.BIT.B2 = 1U;

	/* set P50 drive capacity control high */
	PORT5.DSCR.BIT.B0 = 1U;

	/* set P50 pull-up resistor off */
	PORT5.PCR.BIT.B0 = 1U;

	/* set P50 port direction to input */
	PORT5.PDR.BIT.B0 = 0U;

	/* set P50 open-drain to NMOS OD output */
	PORT5.ODR0.BIT.B0 = 1U;

	/* set P50 mode to not GPIO */
    PORT5.PMR.BIT.B0 = 1U;

	/* place i2c pins in high impedance */
	SCI2.SIMR3.BIT.IICSCLS = 3U;
	SCI2.SIMR3.BIT.IICSDAS = 3U;

    /* clock select */
    SCI2.SMR.BYTE = 0;

    /* msb first */
    SCI2.SCMR.BIT.SDIR = 1U;

    /* no inversion */
    SCI2.SCMR.BIT.SINV = 0U;

    /* not smart card mode */
    SCI2.SCMR.BIT.SMIF = 0U;

    /* baud rate */
    SCI2.BRR = 18U;

    /* set noise filter enable */
    SCI2.SEMR.BIT.NFEN = 1U;

    /* bit rate modulation disable */
    SCI2.SEMR.BIT.BRME = 0U;

    /* noie filter clock select */
    SCI2.SNFR.BIT.NFCS = 1U;

    /* select simple IIC mode */
    SCI2.SIMR1.BIT.IICM = 1U;

    /* set SDA output delay */
    SCI2.SIMR1.BIT.IICDL = 18U;

    /* set reception/transmission of ACK/NACK */
    SCI2.SIMR2.BIT.IICACKT = 1U;

    /* clock synch on */
    SCI2.SIMR2.BIT.IICCSC = 1U;

    /* use tx/rx interrupts */
    SCI2.SIMR2.BIT.IICINTM = 1U;

    /* SPI mode off */
    SCI2.SPMR.BYTE = 0U;

    /* enable tx/tx, txi/rxi and tei (used as start/stop bit generation complete) interrupts although the TEI interrupt is polled */
	SCI2.SCR.BYTE = 0xb4U;

	/* enable group BL0 interupt 4 tei (used as start/stop bit generation complete) interrupt) */
	ICU.GENBL0.BIT.EN4 = 1U;

	/* set up rx interrupt */
	IR(SCI2, RXI2) = 0U;
	IPR(SCI2, RXI2) = 5U;
	IEN(SCI2, RXI2) = 1U;

	/* set up transmit interrupt */
	IR(SCI2, TXI2) = 0U;
	IPR(SCI2, TXI2) = 5U;
	IEN(SCI2, TXI2) = 1U;
}

static bool write_device_data(uint8_t device_address, const uint8_t *data, uint16_t length)
{
	bool success = false;
	uint16_t i;

	/* disable read interrupt generation */
	SCI2.SCR.BIT.RIE = 0U;

	generate_start_stop_condition(start_condition);

	if (write_device_address(device_address, write_frame))
	{
		success = true;

		for (i = 0U; i < length; i++)
		{
			SCI2.TDR = data[i];

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

static bool write_device_address(uint8_t device_address, frame_type_t frame_type)
{
	uint8_t byte_to_write;

	byte_to_write = device_address << 1;
	if (frame_type == read_frame)
	{
		byte_to_write++;
	}

	/* send device address to transmit register with write bit */
	SCI2.TDR = byte_to_write;

	/* wait for tx interrupt */
	while (!tx_complete_interrupt_flag)
	{
	}
	tx_complete_interrupt_flag = false;

	/* check ACK received */
	if (SCI2.SISR.BIT.IICACKR == 0U)
	{
		return true;
	}

	return false;
}

static void generate_start_stop_condition(start_stop_condition_t start_stop_condition)
{
	switch (start_stop_condition)
	{
	case start_condition:
		/* generate a start condition */
		SCI2.SIMR3.BYTE = 0x51U;
		break;

	case stop_condition:
		/* generate a stop condition */
		SCI2.SIMR3.BYTE = 0x54U;
		break;

	default:
		return;
		break;				/* keep MISRA happy */
	}

	/* wait for start condition completed interrupt flag is set */
	while (SCI2.SIMR3.BIT.IICSTIF == 0U)
	{
	}
	SCI2.SIMR3.BIT.IICSTIF = 0U;

	switch (start_stop_condition)
	{
	case start_condition:
		/* end start condition generation */
		SCI2.SIMR3.BIT.IICSCLS = 0U;
		SCI2.SIMR3.BIT.IICSDAS = 0U;
		break;

	case stop_condition:
		/* end stop condition generation */
		SCI2.SIMR3.BIT.IICSCLS = 3U;
		SCI2.SIMR3.BIT.IICSDAS = 3U;
		break;

	default:
		/* keep MISRA happy */
		break;
	}
}

static void ov7670_init(void)
{
	uint16_t i;

	for (i = 0U; i < (uint16_t)sizeof(OV7670_register_setup) / 2U; i++)
	{
		if (!write_device_data(OV7670_WRITE_ADDR >> 1, &OV7670_register_setup[i][0], 2U))
		{
			break;
		}

		delay(0xFFFFU);
	}
}

static void delay(volatile uint16_t count)
{
	while (count--)
	{
	}
}

static void cam_paralell_io_init(void)
{
	PORTC.PMR.BIT.B0 = 0U;	/* mode to gpio */
	PORTC.PDR.BIT.B0 = 0U;	/* input */
	PORTC.PCR.BIT.B0 = 0U;  /* pull-up disable */

	PORTC.PMR.BIT.B1 = 0U;	/* mode to gpio */
	PORTC.PDR.BIT.B1 = 0U;	/* input */
	PORTC.PCR.BIT.B1 = 0U;  /* pull-up disable */

	PORT3.PMR.BIT.B2 = 0U;	/* mode to gpio */
	PORT3.PDR.BIT.B2 = 0U;	/* input */
	PORT3.PCR.BIT.B2 = 0U;  /* pull-up disable */

	PORT3.PMR.BIT.B3 = 0U;	/* mode to gpio */
	PORT3.PDR.BIT.B3 = 0U;	/* input */
	PORT3.PCR.BIT.B3 = 0U;  /* pull-up disable */

	PORTC.PMR.BIT.B4 = 0U;	/* mode to gpio */
	PORTC.PDR.BIT.B4 = 0U;	/* input */
	PORTC.PCR.BIT.B4 = 0U;  /* pull-up disable */

	PORTC.PMR.BIT.B5 = 0U;	/* mode to gpio */
	PORTC.PDR.BIT.B5 = 0U;	/* input */
	PORTC.PCR.BIT.B5 = 0U;  /* pull-up disable */

	PORTC.PMR.BIT.B6 = 0U;	/* mode to gpio */
	PORTC.PDR.BIT.B6 = 0U;	/* input */
	PORTC.PCR.BIT.B6 = 0U;  /* pull-up disable */

	PORT5.PMR.BIT.B1 = 0U;	/* mode to gpio */
	PORT5.PDR.BIT.B1 = 0U;	/* input */
	PORT5.PCR.BIT.B1 = 0U;  /* pull-up disable */

	PORTJ.PMR.BIT.B5 = 0U;	/* mode to gpio */
	PORTJ.PDR.BIT.B5 = 0U;	/* input */
	PORTJ.PCR.BIT.B5 = 0U;  /* pull-up disable */

	PORTB.PMR.BIT.B6 = 0U;	/* mode to gpio */
	PORTB.PDR.BIT.B6 = 0U;	/* input */
	PORTB.PCR.BIT.B6 = 0U;  /* pull-up disable */

	PORTB.PMR.BIT.B7 = 0U;	/* mode to gpio */
	PORTB.PDR.BIT.B7 = 0U;	/* input */
	PORTB.PCR.BIT.B7 = 0U;  /* pull-up disable */
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void camlib_init(void)
{
	xclk_init();
	sccb_init();
	cam_paralell_io_init();
	ov7670_init();
}

void camlib_capture(void)
{
	uint_fast32_t i;

	/* disable all interrupts that are active individually as disabling all interrupts globally via PSW is not possible in user mode */
	IEN(CMT0, CMI0) = 0U;

	/* wait for VS */
	while (PORTB.PIDR.BIT.B6 == 0U)
	{
	}
	while (PORTB.PIDR.BIT.B6 == 1U)
	{
	}
	i = 0UL;

	for (uint_fast8_t y = 0U; y < 120U; y++)
	{
		/* wait for first HS */
		while (PORTB.PIDR.BIT.B7 == 0U)
		{
		}

		while (PORTB.PIDR.BIT.B7 == 1U)
		{
		}

		/* wait for second HS */
		while (PORTB.PIDR.BIT.B7 == 0U)
		{
		}

		for (uint_fast16_t x = 0U; x < 160U; x++)
		{
			/* wait for PLK */
			while (PORTJ.PIDR.BIT.B5 == 0U)
			{
			}

			frame_buffer[i] = PORTC.PIDR.BYTE & 0x73U;
			frame_buffer[i] |= (PORT3.PIDR.BYTE & 0x0cU);
			if (PORT5.PIDR.BIT.B1 == 1U)
			{
				frame_buffer[i] |= 0x80U;
			}
			i++;

			/* wait for ~PLK */
			while (PORTJ.PIDR.BIT.B5 == 1U)
			{
			}

			/* wait for PLK */
			while (PORTJ.PIDR.BIT.B5 == 0U)
			{
			}

			frame_buffer[i] = PORTC.PIDR.BYTE & 0x73U;
			frame_buffer[i] |= (PORT3.PIDR.BYTE & 0x0cU);
			if (PORT5.PIDR.BIT.B1 == 1U)
			{
				frame_buffer[i] |= 0x80U;
			}
			i++;

			/* wait for ~PLK */
			while (PORTJ.PIDR.BIT.B5 == 1U)
			{
			}

			/* repeat doing dummy read */
			while (PORTJ.PIDR.BIT.B5 == 0U)
			{
			}

			while (PORTJ.PIDR.BIT.B5 == 1)
			{
			}

			while (PORTJ.PIDR.BIT.B5 == 0U)
			{
			}

			while (PORTJ.PIDR.BIT.B5 == 1U)
			{
			}
		}
	}

	/* re-enable interrupts */
	IEN(CMT0, CMI0) = 1U;
}

uint16_t *camlib_get_frame(void)
{
	return (uint16_t *)&frame_buffer[0];
}
