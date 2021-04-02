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
#include "fsl_ctimer.h"
#include "fsl_iocon.h"
#include "fsl_gpio.h"
#include "fsl_i2c.h"
#include "fsl_iocon.h"
#include "camlib.h"

/****************
*** CONSTANTS ***
****************/

#define IOCON_PIO_DIGITAL_EN 		0x0100u   				/**< Enables digital function */
#define IOCON_PIO_FUNC0 			0x00u          			/**< Selects pin function 1 */
#define IOCON_PIO_FUNC2 			0x02u          			/**< Selects pin function 2 */
#define IOCON_PIO_FUNC3 			0x03u          			/**< Selects pin function 3 */
#define IOCON_PIO_FUNC4 			0x04u          			/**< Selects pin function 4 */
#define IOCON_PIO_INPFILT_OFF 		0x0200u  				/**< Input filter disabled */
#define IOCON_PIO_INV_DI 			0x00u         			/**< Input function is not inverted */
#define IOCON_PIO_MODE_INACT 		0x00u     				/**< No addition pin function */
#define IOCON_PIO_MODE_PULLUP	 	0x20u    				/**< Selects pull-up function */
#define IOCON_PIO_OPENDRAIN_DI 		0x00u   				/**< Open drain is disabled */
#define IOCON_PIO_SLEW_STANDARD 	0x00u  					/**< Standard mode, output slew rate control is enabled */
#define IOCON_PIO_OPENDRAIN_EN 		0x0800u 				/**< Open drain is enabled */
#define I2C_MASTER_CLOCK_FREQUENCY (12000000)
#define I2C_MASTER_SLAVE_ADDR_7BIT 	0x21U

static const uint8_t OV7670_register_setup[][2] =
{
	{0x12, 0x80},		/* Reset registers */

	/* image format */
	{0x12, 0x14},		/* QVGA size, RGB mode */

	{0x40, 0xd0},		/* RGB565 */
	{0xb0, 0x84},		/* Color mode */

	/* hardware window */
	{0x11, 0x01},		/* PCLK settings, 15 fps */
	{0x32, 0x80},		/* HREF */
	{0x17, 0x17},		/* HSTART */
	{0x18, 0x05},		/* HSTOP */
	{0x03, 0x0a},		/* VREF */
	{0x19, 0x02},		/* VSTART */
	{0x1a, 0x7a},		/* VSTOP */

	/* scaling numbers */
	{0x70, 0x3a},		/* X_SCALING */
	{0x71, 0x35},		/* Y_SCALING */
	{0x72, 0x11},		/* DCW_SCALING */
	{0x73, 0xf0},		/* PCLK_DIV_SCALING */
	{0xa2, 0x02},		/* PCLK_DELAY_SCALING */

	/* matrix coefficients */
	{0x4f, 0x80},		{0x50, 0x80},
	{0x51, 0x00},		{0x52, 0x22},
	{0x53, 0x5e},		{0x54, 0x80},
	{0x58, 0x9e},

	/* gamma curve values */
	{0x7a, 0x20},		{0x7b, 0x10},
	{0x7c, 0x1e},		{0x7d, 0x35},
	{0x7e, 0x5a},		{0x7f, 0x69},
	{0x80, 0x76},		{0x81, 0x80},
	{0x82, 0x88},		{0x83, 0x8f},
	{0x84, 0x96},		{0x85, 0xa3},
	{0x86, 0xaf},		{0x87, 0xc4},
	{0x88, 0xd7},		{0x89, 0xe8},

	/* AGC and AEC parameters */
	{0xa5, 0x05},		{0xab, 0x07},
	{0x24, 0x95},		{0x25, 0x33},
	{0x26, 0xe3},		{0x9f, 0x78},
	{0xa0, 0x68},		{0xa1, 0x03},
	{0xa6, 0xd8},		{0xa7, 0xd8},
	{0xa8, 0xf0},		{0xa9, 0x90},
	{0xaa, 0x94},		{0x10, 0x00},

	/* AWB parameters */
	{0x43, 0x0a},		{0x44, 0xf0},
	{0x45, 0x34},		{0x46, 0x58},
	{0x47, 0x28},		{0x48, 0x3a},
	{0x59, 0x88},		{0x5a, 0x88},
	{0x5b, 0x44},		{0x5c, 0x67},
	{0x5d, 0x49},		{0x5e, 0x0e},
	{0x6c, 0x0a},		{0x6d, 0x55},
	{0x6e, 0x11},		{0x6f, 0x9f},
	{0x6a, 0x40},		{0x01, 0x40},
	{0x02, 0x60},		{0x13, 0xe7},

	/* additional parameters */
	{0x34, 0x11},		{0x3f, 0x00},
	{0x75, 0x05},		{0x76, 0xe1},
	{0x4c, 0x00},		{0x77, 0x01},
	{0xb8, 0x0a},		{0x41, 0x18},
	{0x3b, 0x12},		{0xa4, 0x88},
	{0x96, 0x00},		{0x97, 0x30},
	{0x98, 0x20},		{0x99, 0x30},
	{0x9a, 0x84},		{0x9b, 0x29},
	{0x9c, 0x03},		{0x9d, 0x4c},
	{0x9e, 0x3f},		{0x78, 0x04},
	{0x0e, 0x61},		{0x0f, 0x4b},
	{0x16, 0x02},		{0x1e, 0x00},
	{0x21, 0x02},		{0x22, 0x91},
	{0x29, 0x07},		{0x33, 0x0b},
	{0x35, 0x0b},		{0x37, 0x1d},
	{0x38, 0x71},		{0x39, 0x2a},
	{0x3c, 0x78},		{0x4d, 0x40},
	{0x4e, 0x20},		{0x69, 0x00},
	{0x6b, 0x3a},		{0x74, 0x10},
	{0x8d, 0x4f},		{0x8e, 0x00},
	{0x8f, 0x00},		{0x90, 0x00},
	{0x91, 0x00},		{0x96, 0x00},
	{0x9a, 0x00},		{0xb1, 0x0c},
	{0xb2, 0x0e},		{0xb3, 0x82},
	{0x4b, 0x01}
};

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static uint8_t frame_buffer[160 * 120 * 2];

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void xclk_init(void);
static void sccb_init(void);
static bool ov7670_init(void);
static void cam_paralell_io_init(void);
static void delay(volatile uint16_t count);
static bool sccb_write_reg(uint8_t reg_addr, uint8_t data);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static void delay(volatile uint16_t count)
{
	while (count--)
	{
	}
}

static void xclk_init(void)
{
	ctimer_config_t config;
	ctimer_match_config_t matchConfig;

	/* Enable the asynchronous bridge */
	SYSCON->ASYNCAPBCTRL = 1;

	CLOCK_AttachClk(kMAIN_CLK_to_ASYNC_APB);

	CLOCK_EnableClock(kCLOCK_Iocon);
	const uint32_t port2_pin2_config = (/* Pin is configured as CTIMER1_MAT1 */
										 IOCON_PIO_FUNC4 |
										 /* No addition pin function */
										 IOCON_PIO_MODE_INACT |
										 /* Input function is not inverted */
										 IOCON_PIO_INV_DI |
										 /* Enables digital function */
										 IOCON_PIO_DIGITAL_EN |
										 /* Input filter disabled */
										 IOCON_PIO_INPFILT_OFF |
										 /* Standard mode, output slew rate control is enabled */
										 IOCON_PIO_SLEW_STANDARD |
										 /* Open drain is disabled */
										 IOCON_PIO_OPENDRAIN_DI);
	/* PORT4 PIN5 is configured as CTIMER1_MAT1 */
	IOCON_PinMuxSet(IOCON, 2U, 2U, port2_pin2_config);

	CTIMER_GetDefaultConfig(&config);
	CTIMER_Init(CTIMER1, &config);

	matchConfig.enableCounterReset = true;
	matchConfig.enableCounterStop  = false;
	matchConfig.matchValue         = 5;
	matchConfig.outControl         = kCTIMER_Output_Toggle;
	matchConfig.outPinInitState    = true;
	matchConfig.enableInterrupt    = false;
	CTIMER_SetupMatch(CTIMER1, kCTIMER_Match_1, &matchConfig);
	CTIMER_StartTimer(CTIMER1);
}

static void sccb_init(void)
{
	i2c_master_config_t masterConfig;

	/* attach 12 MHz clock to FLEXCOMM8 (I2C master) */
	CLOCK_AttachClk(kFRO12M_to_FLEXCOMM8);

	/* reset FLEXCOMM for I2C */
	RESET_PeripheralReset(kFC8_RST_SHIFT_RSTn);

    const uint32_t port1_pin17_config = (/* Pin is configured as FC8_RXD_SDA_MOSI */
                                         IOCON_PIO_FUNC2 |
                                         /* Selects pull-up function */
                                         IOCON_PIO_MODE_PULLUP |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is enabled */
                                         IOCON_PIO_OPENDRAIN_EN);
    /* PORT1 PIN17 (coords: N12) is configured as FC8_RXD_SDA_MOSI */
    IOCON_PinMuxSet(IOCON, 1U, 17U, port1_pin17_config);

    const uint32_t port1_pin18_config = (/* Pin is configured as FC8_TXD_SCL_MISO */
                                         IOCON_PIO_FUNC2 |
                                         /* Selects pull-up function */
                                         IOCON_PIO_MODE_PULLUP |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is enabled */
                                         IOCON_PIO_OPENDRAIN_EN);
    /* PORT1 PIN18 (coords: D1) is configured as FC8_TXD_SCL_MISO */
    IOCON_PinMuxSet(IOCON, 1U, 18U, port1_pin18_config);


    /*
     * masterConfig.debugEnable = false;
     * masterConfig.ignoreAck = false;
     * masterConfig.pinConfig = kI2C_2PinOpenDrain;
     * masterConfig.baudRate_Bps = 100000U;
     * masterConfig.busIdleTimeout_ns = 0;
     * masterConfig.pinLowTimeout_ns = 0;
     * masterConfig.sdaGlitchFilterWidth_ns = 0;
     * masterConfig.sclGlitchFilterWidth_ns = 0;
     */
    I2C_MasterGetDefaultConfig(&masterConfig);

    /* Change the default baudrate configuration */
    masterConfig.baudRate_Bps = 100000UL;

    /* Initialize the I2C master peripheral */
    I2C_MasterInit((I2C_Type *)I2C8_BASE, &masterConfig, I2C_MASTER_CLOCK_FREQUENCY);
}

static bool ov7670_init(void)
{
	uint8_t i;
	bool result;

	for (i = 0U; i < sizeof(OV7670_register_setup) / 2; i++)
	{
		result = sccb_write_reg(OV7670_register_setup[i][0], OV7670_register_setup[i][1]);

		if (result == false)
		{
			break;
		}

		delay(0xFFFF);
	}

	return result;
}

static void cam_paralell_io_init(void)
{
    CLOCK_EnableClock(kCLOCK_Gpio3);

    const uint32_t LED3 = IOCON_FUNC0 | IOCON_MODE_PULLUP | IOCON_DIGITAL_EN | IOCON_INPFILT_OFF;

    IOCON_PinMuxSet(IOCON, 3, 16, LED3);
    IOCON_PinMuxSet(IOCON, 3, 17, LED3);
    IOCON_PinMuxSet(IOCON, 3, 18, LED3);
    IOCON_PinMuxSet(IOCON, 3, 19, LED3);
    IOCON_PinMuxSet(IOCON, 3, 20, LED3);
    IOCON_PinMuxSet(IOCON, 3, 21, LED3);
    IOCON_PinMuxSet(IOCON, 3, 22, LED3);
    IOCON_PinMuxSet(IOCON, 3, 26, LED3);

    IOCON_PinMuxSet(IOCON, 3, 27, LED3);
    IOCON_PinMuxSet(IOCON, 3, 28, LED3);
    IOCON_PinMuxSet(IOCON, 3, 29, LED3);

    gpio_pin_config_t pin_config;
    pin_config.pinDirection = kGPIO_DigitalInput;

    GPIO_PinInit(GPIO, 3, 16, &pin_config);
    GPIO_PinInit(GPIO, 3, 17, &pin_config);
    GPIO_PinInit(GPIO, 3, 18, &pin_config);
    GPIO_PinInit(GPIO, 3, 19, &pin_config);
    GPIO_PinInit(GPIO, 3, 20, &pin_config);
    GPIO_PinInit(GPIO, 3, 21, &pin_config);
    GPIO_PinInit(GPIO, 3, 22, &pin_config);
    GPIO_PinInit(GPIO, 3, 26, &pin_config);

    GPIO_PinInit(GPIO, 3, 27, &pin_config);
    GPIO_PinInit(GPIO, 3, 28, &pin_config);
    GPIO_PinInit(GPIO, 3, 29, &pin_config);
}

static bool sccb_write_reg(uint8_t reg_addr, uint8_t data)
{
	uint8_t buffer[2];

	buffer[0] = reg_addr;
	buffer[1] = data;

    if (kStatus_Success == I2C_MasterStart((I2C_Type *)I2C8_BASE, I2C_MASTER_SLAVE_ADDR_7BIT, kI2C_Write))
    {
        if (I2C_MasterWriteBlocking((I2C_Type *)I2C8_BASE, buffer, 2, kI2C_TransferDefaultFlag) == kStatus_Success)
        {
        	return true;
        }
    }

    return false;
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void camlib_init(void)
{
	xclk_init();
	delay(20000);
	sccb_init();
	cam_paralell_io_init();
	ov7670_init();
}

uint16_t *camlib_get_frame(void)
{
	return (uint16_t *)&frame_buffer[0];
}

void camlib_capture(void)
{
	uint_fast32_t i;

	__disable_irq();

	/* wait for VS */
	while (GPIO_PinRead(GPIO, 3U, 27U) == 0U)
	{
	}
	while (GPIO_PinRead(GPIO, 3U, 27U) == 1U)
	{
	}
	i = 0UL;

	for (uint_fast8_t y = 0U; y < 120U; y++)
	{
		/* wait for first HS */
		while (GPIO_PinRead(GPIO, 3U, 28U) == 0U)
		{
		}

		while (GPIO_PinRead(GPIO, 3U, 28U) == 1U)
		{
		}

		/* wait for second HS */
		while (GPIO_PinRead(GPIO, 3U, 28U) == 0U)
		{
		}

		for (uint_fast16_t x = 0U; x < 160U; x++)
		{
			/* wait for PLK */
			while (GPIO_PinRead(GPIO, 3U, 29U) == 0U)
			{
			}

			frame_buffer[i] = GPIO_PortRead(GPIO, 3U) >> 16;
			frame_buffer[i] &= ~0b10000000U;
			frame_buffer[i] |= (GPIO_PinRead(GPIO, 3U, 26U) << 7);
			i++;

			/* wait for ~PLK */
			while (GPIO_PinRead(GPIO, 3U, 29U) == 1U)
			{
			}

			/* wait for PLK */
			while (GPIO_PinRead(GPIO, 3U, 29U) == 0U)
			{
			}

			frame_buffer[i] = GPIO_PortRead(GPIO, 3U) >> 16;
			frame_buffer[i] &= ~0b10000000U;
			frame_buffer[i] |= (GPIO_PinRead(GPIO, 3U, 26U) << 7);
			i++;

			/* wait for ~PLK */
			while (GPIO_PinRead(GPIO, 3U, 29U) == 1U)
			{
			}

			/* repeat ignoring read */
			while (GPIO_PinRead(GPIO, 3U, 29U) == 0U)
			{
			}

			while (GPIO_PinRead(GPIO, 3U, 29U) == 1U)
			{
			}

			while (GPIO_PinRead(GPIO, 3U, 29U) == 0U)
			{
			}

			while (GPIO_PinRead(GPIO, 3U, 29U) == 1U)
			{
			}
		}
	}

	__enable_irq();
}
