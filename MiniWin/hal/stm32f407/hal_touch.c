/*

MIT License

Copyright (c) John Blaiklock 2018 miniwin Embedded Window Manager

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

#include "stm32f4xx_conf.h"
#include "hal/hal_touch.h"
#include "hal/hal_delay.h"

/****************
*** CONSTANTS ***
****************/

#define CS_ON								(GPIO_ResetBits(GPIOB, GPIO_Pin_7))         /**< touch screen digitizer chip select off */
#define CS_OFF 								(GPIO_SetBits(GPIOB, GPIO_Pin_7))           /**< touch screen digitizer chip select on */
#define GET_STATE							(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6))  /**< GPIO pin low when screen touched else high */
#define MW_HAL_TOUCH_READ_POINTS_COUNT		10											/**< Number of samples to take to reduce noise */

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/*************************
*** EXTERNAL VARIABLES ***
**************************/

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static uint16_t spi_transfer(uint8_t byte);

/**********************
*** LOCAL FUNCTIONS ***
**********************/
/**
 * Transfer a byte to the touch screen SPI interface and return the 2 byte response
 *
 * @param byte: The byte to send
 * @return: The 2 byte response
 */
static uint16_t spi_transfer(uint8_t byte)
{
	SPI_I2S_SendData(SPI1, byte);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(SPI1);
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_touch_init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* enable SPI1, AF, GPIOA and GPIOB clocks */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* configure SPI pins as alternative function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);

	/* configure SPI1 pins SCK, MISO and MOSI */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 |GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* configure b6 as touch up/down state line */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* configure b7 as output push-pull, used as touch chip select */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* deselect touch - chip select high */
	CS_OFF;
	SPI_I2S_DeInit(SPI1);

	/* SPI1 configuration */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);

	/* select touch - chip select low */
	CS_ON;
}

mw_hal_touch_state_t mw_hal_touch_get_state(void)
{
	return (mw_hal_touch_state_t)GET_STATE;
}

bool mw_hal_touch_get_point(uint16_t* x, uint16_t* y)
{
	uint8_t i;
 	bool sorted;
 	uint16_t swap_value;
	uint16_t x_raw;
	uint16_t y_raw;
	uint16_t databuffer[2][MW_HAL_TOUCH_READ_POINTS_COUNT];
	uint8_t touch_count;

	touch_count = 0;
	do
	{
		spi_transfer(0xd0);
		mw_hal_delay_us(1);
		x_raw = spi_transfer(0) << 8;
		x_raw |= spi_transfer(0);
		x_raw >>= 3;

		spi_transfer(0x90);
		mw_hal_delay_us(1);
		y_raw = spi_transfer(0) << 8;
		y_raw |= spi_transfer(0);
		y_raw >>= 3;

		databuffer[0][touch_count] = x_raw;
		databuffer[1][touch_count] = y_raw;
		touch_count++;
	}
	while (GET_STATE == MW_HAL_TOUCH_STATE_DOWN && touch_count < MW_HAL_TOUCH_READ_POINTS_COUNT);

	if (touch_count != MW_HAL_TOUCH_READ_POINTS_COUNT)
	{
		return false;
	}

	do
	{
		sorted = true;
		for (i = 0; i < touch_count - 1; i++)
		{
			if(databuffer[0][i] > databuffer[0][i + 1])
			{
				swap_value = databuffer[0][i + 1];
				databuffer[0][i + 1] = databuffer[0][i];
				databuffer[0][i] = swap_value;
				sorted = false;
			}
		}
	}
	while (!sorted);

	do
	{
		sorted = true;
		for (i = 0; i < touch_count - 1; i++)
		{
			if (databuffer[1][i] > databuffer[1][i + 1])
			{
				swap_value = databuffer[1][i + 1];
				databuffer[1][i + 1] = databuffer[1][i];
				databuffer[1][i] = swap_value;
				sorted = false;
			}
		}
	}
	while (!sorted);

	*x = (databuffer[0][4]+databuffer[0][5]) / 8;
	*y = (databuffer[1][4]+databuffer[1][5]) / 8;

	return true;
}
