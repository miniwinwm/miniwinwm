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
#include "stm32f4xx.h"

/****************
*** CONSTANTS ***
****************/

#define OV7670_WRITE_ADDR 		0x42U
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

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static uint8_t frame_buffer[160 * 120 * 2];
static I2C_HandleTypeDef hi2c1;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void ov7670_init(void);
static void xclk_init(void);
static void cam_paralell_io_init(void);
static void sccb_init(void);
static void delay(volatile uint16_t count);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static void xclk_init(void)
{
	TIM_HandleTypeDef Tim10Handle;
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_OC_InitTypeDef sConfigOC = {0};

	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_TIM10_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF3_TIM10;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	Tim10Handle.Instance = TIM10;
	Tim10Handle.Init.Prescaler = 0U;
	Tim10Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	Tim10Handle.Init.Period = 2U;
	Tim10Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	Tim10Handle.Init.RepetitionCounter = 0U;
	(void)HAL_TIM_Base_Init(&Tim10Handle);
	(void)HAL_TIM_OC_Init(&Tim10Handle);

	sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
	sConfigOC.Pulse = 0U;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	(void)HAL_TIM_OC_ConfigChannel(&Tim10Handle, &sConfigOC, TIM_CHANNEL_1);

	(void)HAL_TIM_Base_Start(&Tim10Handle);
	(void)HAL_TIM_OC_Start(&Tim10Handle, TIM_CHANNEL_1);
}

static void cam_paralell_io_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;

	GPIO_InitStruct.Pin = GPIO_PIN_5;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_4;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_11;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_9;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}

static void sccb_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_I2C1_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	hi2c1.Instance = I2C1;
	hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c1.Init.OwnAddress1 = 0U;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.ClockSpeed = 100000U;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	(void)HAL_I2C_Init(&hi2c1);
}

static void delay(volatile uint16_t count)
{
	while (count--)
	{
	}
}

static void ov7670_init(void)
{
	uint16_t i;
	uint8_t data[2];

	for (i = 0U; i < (uint16_t)sizeof(OV7670_register_setup) / 2U; i++)
	{
		data[0] = OV7670_register_setup[i][0];
		data[1] = OV7670_register_setup[i][1];
		if (HAL_I2C_Master_Transmit(&hi2c1, OV7670_WRITE_ADDR, data, 2U, 1000U) != HAL_OK)
		{
			return;
		}

		delay(0xFFFFU);
	}
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
	(void)HAL_I2C_DeInit(&hi2c1);
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
	while (!(GPIOC->IDR & GPIO_PIN_11))
	{
	}
	while ((GPIOC->IDR & GPIO_PIN_11))
	{
	}
	i = 0UL;

	for (uint_fast8_t y = 0U; y < 120U; y++)
	{
		/* wait for first HS */
		while (!(GPIOA->IDR & GPIO_PIN_5))
		{
		}

		while ((GPIOA->IDR & GPIO_PIN_5))
		{
		}

		/* wait for second HS */
		while (!(GPIOA->IDR & GPIO_PIN_5))
		{
		}

		for (uint_fast16_t x = 0U; x < 160U; x++)
		{
			/* wait for PLK */
			while (!(GPIOB->IDR & GPIO_PIN_4))
			{
			}

			frame_buffer[i] = (uint8_t)GPIOE->IDR & 0b01111100U;
			frame_buffer[i] |= (uint8_t)(GPIOG->IDR >> 2) & 0b10000011U;
			i++;

			/* wait for ~PLK */
			while ((GPIOB->IDR & GPIO_PIN_4))
			{
			}

			/* wait for PLK */
			while (!(GPIOB->IDR & GPIO_PIN_4))
			{
			}

			frame_buffer[i] = (uint8_t)GPIOE->IDR & 0b01111100U;
			frame_buffer[i] |= (uint8_t)(GPIOG->IDR >> 2) & 0b10000011U;
			i++;

			/* wait for ~PLK */
			while ((GPIOB->IDR & GPIO_PIN_4))
			{
			}

			/* repeat ignoring read */
			while (!(GPIOB->IDR & GPIO_PIN_4))
			{
			}

			while ((GPIOB->IDR & GPIO_PIN_4))
			{
			}

			while (!(GPIOB->IDR & GPIO_PIN_4))
			{
			}

			while ((GPIOB->IDR & GPIO_PIN_4))
			{
			}
		}
	}

	__enable_irq();
}
