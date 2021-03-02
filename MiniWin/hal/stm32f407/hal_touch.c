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
#include "stm32f4xx_hal.h"
#include "stm32f4_discovery.h"

/****************
*** CONSTANTS ***
****************/

#define TOUCH_IRQ_PORT						GPIOD					/**< Port of incoming screen touched line */
#define TOUCH_IRQ_PIN						GPIO_PIN_9				/**< Pin of incoming screen touched line */
#define TOUCH_CHIP_SELECT_PORT				GPIOD					/**< Port of chip select line */
#define TOUCH_CHIP_SELECT_PIN				GPIO_PIN_10				/**< Pin of chip select line */
#define CHIP_SELECT_ON						(HAL_GPIO_WritePin(TOUCH_CHIP_SELECT_PORT, TOUCH_CHIP_SELECT_PIN, GPIO_PIN_RESET))  	/**< Touch screen digitizer chip select off */
#define CHIP_SELECT_OFF 					(HAL_GPIO_WritePin(TOUCH_CHIP_SELECT_PORT, TOUCH_CHIP_SELECT_PIN, GPIO_PIN_SET)) 		/**< Touch screen digitizer chip select on */
#define MW_HAL_TOUCH_READ_POINTS_COUNT		10U						/**< Number of samples to take to reduce noise */
#define COMMAND_READ_X             			0xd0U					/**< Command to read X position from touch screen */
#define COMMAND_READ_Y             			0x90U					/**< Command to read Y position from touch screen */

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static SPI_HandleTypeDef hspi3;

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

	(void)HAL_SPI_TransmitReceive(&hspi3, &byte, &result, 1U, 1000U);

	return (result);
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void mw_hal_touch_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* enable SPI3, AF, GPIOC and GPIOD clocks */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_SPI3_CLK_ENABLE();
	__HAL_RCC_SYSCFG_CLK_ENABLE();

	/* configure SPI3 pins SCK, MISO and MOSI */
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStructure.Pull = GPIO_PULLDOWN;
	GPIO_InitStructure.Pin = GPIO_PIN_10 | GPIO_PIN_11 |GPIO_PIN_12;
	GPIO_InitStructure.Alternate = GPIO_AF6_SPI3;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* configure D9 as touch up/down state line */
	GPIO_InitStructure.Pin = TOUCH_IRQ_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(TOUCH_IRQ_PORT, &GPIO_InitStructure);

	/* configure D10 as output push-pull, used as touch chip select */
	GPIO_InitStructure.Pin = TOUCH_CHIP_SELECT_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(TOUCH_CHIP_SELECT_PORT, &GPIO_InitStructure);

	/* deselect touch - chip select high */
	CHIP_SELECT_OFF;

	/* SPI3 configuration */
	hspi3.Instance = SPI3;
	(void)HAL_SPI_DeInit(&hspi3);
	hspi3.Init.Direction = SPI_DIRECTION_2LINES;
	hspi3.Init.Mode = SPI_MODE_MASTER;
	hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi3.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi3.Init.CLKPhase = SPI_PHASE_2EDGE;
	hspi3.Init.NSS = SPI_NSS_SOFT;
	hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	(void)HAL_SPI_Init(&hspi3);

	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
}

bool mw_hal_touch_is_recalibration_required(void)
{
	return (BSP_PB_GetState(BUTTON_KEY));
}

mw_hal_touch_state_t mw_hal_touch_get_state()
{
	if (HAL_GPIO_ReadPin(TOUCH_IRQ_PORT, TOUCH_IRQ_PIN) == GPIO_PIN_RESET)
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

	CHIP_SELECT_ON;

	touch_count = 0U;
	do
	{
		(void)spi_transfer(COMMAND_READ_X);
		x_raw = (uint16_t)spi_transfer(0U) << 8;
		x_raw |= (uint16_t)spi_transfer(0U);
		x_raw >>= 3;

		(void)spi_transfer(COMMAND_READ_Y);
		y_raw = (uint16_t)spi_transfer(0U) << 8;
		y_raw |= (uint16_t)spi_transfer(0U);
		y_raw >>= 3;

		databuffer[0][touch_count] = x_raw;
		databuffer[1][touch_count] = y_raw;
		touch_count++;
	}
	while (mw_hal_touch_get_state() == MW_HAL_TOUCH_STATE_DOWN && touch_count < MW_HAL_TOUCH_READ_POINTS_COUNT);

	CHIP_SELECT_OFF;

	if (touch_count != MW_HAL_TOUCH_READ_POINTS_COUNT)
	{
		return (false);
	}

	do
	{
		sorted = true;
		for (i = 0U; i < touch_count - 1U; i++)
		{
			if (databuffer[0][i] > databuffer[0][i + 1U])
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
