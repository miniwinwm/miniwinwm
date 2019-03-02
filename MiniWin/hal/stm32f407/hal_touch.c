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

#ifdef STM32F407xx

/***************
*** INCLUDES ***
***************/

#include "hal/hal_touch.h"
#include "hal/hal_delay.h"
#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"

/****************
*** CONSTANTS ***
****************/

#define CS_ON								(HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET))  /**< Touch screen digitizer chip select off */
#define CS_OFF 								(HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET)) 	/**< Touch screen digitizer chip select on */
#define MW_HAL_TOUCH_READ_POINTS_COUNT		10U														/**< Number of samples to take to reduce noise */

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static SPI_HandleTypeDef SpiHandle;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static uint8_t spi_transfer(uint8_t byte);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Transfer a byte to the touch screen SPI interface and return the 2 byte response
 *
 * @param byte The byte to send
 * @return The response
 */
static uint8_t spi_transfer(uint8_t byte)
{
	uint8_t result;

	(void)HAL_SPI_TransmitReceive(&SpiHandle, &byte, &result, 1U, 1000U);

	return (result);
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_touch_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* enable SPI1, AF, GPIOA and GPIOB clocks */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_SPI2_CLK_ENABLE();
	__HAL_RCC_SYSCFG_CLK_ENABLE();

	/* configure SPI1 pins SCK, MISO and MOSI */
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;
	GPIO_InitStructure.Pin = GPIO_PIN_13 | GPIO_PIN_14 |GPIO_PIN_15;
	GPIO_InitStructure.Alternate = GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* configure b6 as touch up/down state line */
	GPIO_InitStructure.Pin = GPIO_PIN_6;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* configure b7 as output push-pull, used as touch chip select */
	GPIO_InitStructure.Pin = GPIO_PIN_7;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* deselect touch - chip select high */
	CS_OFF;

	/* SPI1 configuration */
	SpiHandle.Instance = SPI2;
	(void)HAL_SPI_DeInit(&SpiHandle);
	SpiHandle.Init.Direction = SPI_DIRECTION_2LINES;
	SpiHandle.Init.Mode = SPI_MODE_MASTER;
	SpiHandle.Init.DataSize = SPI_DATASIZE_8BIT;
	SpiHandle.Init.CLKPolarity = SPI_POLARITY_HIGH;
	SpiHandle.Init.CLKPhase = SPI_PHASE_2EDGE;
	SpiHandle.Init.NSS = SPI_NSS_SOFT;
	SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	SpiHandle.Init.FirstBit = SPI_FIRSTBIT_MSB;
	SpiHandle.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	(void)HAL_SPI_Init(&SpiHandle);

	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
}

bool mw_hal_touch_is_recalibration_required(void)
{
	return (BSP_PB_GetState(BUTTON_KEY));
}

mw_hal_touch_state_t mw_hal_touch_get_state()
{
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6) == GPIO_PIN_RESET)
	{
		return (MW_HAL_TOUCH_STATE_DOWN);
	}
	return (MW_HAL_TOUCH_STATE_UP);
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

	CS_ON;
	touch_count = 0U;
	do
	{
		spi_transfer(0xd0U);
		mw_hal_delay_us(1U);
		x_raw = (uint16_t)spi_transfer(0U) << 8;
		x_raw |= (uint16_t)spi_transfer(0U);
		x_raw >>= 3;

		spi_transfer(0x90U);
		mw_hal_delay_us(1U);
		y_raw = (uint16_t)spi_transfer(0U) << 8;
		y_raw |= (uint16_t)spi_transfer(0U);
		y_raw >>= 3;

		databuffer[0][touch_count] = x_raw;
		databuffer[1][touch_count] = y_raw;
		touch_count++;
	}
	while (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_DOWN && touch_count < MW_HAL_TOUCH_READ_POINTS_COUNT);

	CS_OFF;

	if (touch_count != MW_HAL_TOUCH_READ_POINTS_COUNT)
	{
		return (false);
	}

	do
	{
		sorted = true;
		for (i = 0U; i < touch_count - 1U; i++)
		{
			if(databuffer[0][i] > databuffer[0][i + 1U])
			{
				swap_value = databuffer[0][i + 1U];
				databuffer[0][i + 1U] = databuffer[0][i];
				databuffer[0][i] = swap_value;
				sorted = false;
			}
		}
	}
	while (!sorted);

	do
	{
		sorted = true;
		for (i = 0U; i < touch_count - 1U; i++)
		{
			if (databuffer[1][i] > databuffer[1][i + 1U])
			{
				swap_value = databuffer[1][i + 1U];
				databuffer[1][i + 1U] = databuffer[1][i];
				databuffer[1][i] = swap_value;
				sorted = false;
			}
		}
	}
	while (!sorted);

	*x = (databuffer[0][4] + databuffer[0][5]) / 8U;
	*y = (databuffer[1][4] + databuffer[1][5]) / 8U;

	return (true);
}

#endif
