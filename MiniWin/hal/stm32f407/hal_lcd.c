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

#include <stdbool.h>
#include "hal/hal_lcd.h"
#include "miniwin_config.h"
#include "stm32f4xx_hal.h"

/****************
*** CONSTANTS ***
****************/

#define LCD_DISPLAY_WIDTH_PIXELS	240							/**< This is the width of the display in pixels irrespective of user specified display rotation */
#define LCD_DISPLAY_HEIGHT_PIXELS	320							/**< This is the height of the display in pixels irrespective of user specified display rotation */
#define DMA_BUFFER_SIZE 			64U							/**< Number of bytes written to LCD in one go by DMA */
#define ILI9341_RST_PORT           	GPIOD						/**< Port of ILI9341 RESET# line */
#define ILI9341_RST_PIN             GPIO_PIN_6					/**< Pin of ILI9341 RESET# line */
#define ILI9341_DC_PORT             GPIOD						/**< Port of ILI9341 DC line */
#define ILI9341_DC_PIN              GPIO_PIN_7					/**< Pin of ILI9341 DC line */
#define ILI9341_CS_PORT             GPIOD						/**< Port of ILI9341 CS# line */
#define ILI9341_CS_PIN              GPIO_PIN_8					/**< Pin of ILI9341 CS# line */

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

static volatile bool dma_transmit_complete;
static SPI_HandleTypeDef hspi2;
static DMA_HandleTypeDef hdma_spi2_tx;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static inline void set_window(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y);
static inline void write_data_dma(const void *data, uint16_t length);
static inline void wait_for_dma_write_complete(void);
static inline void write_command(uint8_t command);
static inline void write_data(uint8_t data);
static inline void mw_hal_lcd_filled_rectangle_rotated(int16_t start_x,
		int16_t start_y,
		int16_t width,
		int16_t height,
		mw_hal_lcd_colour_t colour);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Wait for the SPI TX transfer to complete and return when it's done after receiving the DMA TX interrupt
 */
static inline void wait_for_dma_write_complete(void)
{
	while (dma_transmit_complete == false)
	{
	}
}

/**
 * Send a known length of data to SPI via DMA
 *
 * @param data The data to send
 * @param length The number of bytes in data
 */
static inline void write_data_dma(const void *data, uint16_t length)
{
	dma_transmit_complete = false;
	HAL_SPI_Transmit_DMA(&hspi2, (uint8_t *)data, length);
}

/**
 * Send a command to the ILI9341 panel by switching the DC line to C first
 *
 * @param command The command byte
 */
static inline void write_command(uint8_t command)
{
	HAL_GPIO_WritePin(ILI9341_DC_PORT, ILI9341_DC_PIN, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, &command, 1U, 100U);
}

/**
 * Send a data byte to the ILI9341 panel by switching the DC line to D first
 *
 * @param data The data byte
 */
static inline void write_data(uint8_t data)
{
	HAL_GPIO_WritePin(ILI9341_DC_PORT, ILI9341_DC_PIN, GPIO_PIN_SET);
	HAL_SPI_Transmit(&hspi2, &data, 1U, 100U);
}

/**
 * Send the set window command to the ILI9341 panel
 *
 * @param start_x Left edge of window
 * @param start_y Top edge of window
 * @param end_x Right edge of window
 * @param end_y Bottom edge of window

 */
static inline void set_window(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y)
{
	uint8_t data[4];

	write_command(0x2AU);
	data[0] = start_x >> 8;
	data[1] = start_x;
	data[2] = end_x >> 8;
	data[3] = end_x;
	HAL_GPIO_WritePin(ILI9341_DC_PORT, ILI9341_DC_PIN, GPIO_PIN_SET);
	write_data_dma(data, (uint16_t)sizeof(data));
	wait_for_dma_write_complete();

	write_command(0x2BU);
	data[0] = start_y >> 8;
	data[1] = start_y;
	data[2] = end_y >> 8;
	data[3] = end_y;
	HAL_GPIO_WritePin(ILI9341_DC_PORT, ILI9341_DC_PIN, GPIO_PIN_SET);
	write_data_dma(data, (uint16_t)sizeof(data));
	wait_for_dma_write_complete();

	write_command(0x2CU);
	HAL_GPIO_WritePin(ILI9341_DC_PORT, ILI9341_DC_PIN, GPIO_PIN_SET);
}

/**
 * Plot a filled rectangle using already rotated coordinates. Position and size values are not clipped to the screen.
 *
 * @param start_x X position of left edge of rectangle
 * @param start_y Y position of top of rectangle
 * @param width Width of rectangle, pixels plotted are from start_x to (start_x + width) - 1
 * @param height Height of rectangle, pixels plotted are from start_y to (start_y + height) - 1
 * @param colour The colour of the pixel to plot
 */
static inline void mw_hal_lcd_filled_rectangle_rotated(int16_t start_x,
		int16_t start_y,
		int16_t width,
		int16_t height,
		mw_hal_lcd_colour_t colour)
{
	uint16_t dmaBuffer[DMA_BUFFER_SIZE];
	uint8_t i;
	uint32_t totalBytesToWrite;
	uint32_t bytesToWriteThisTime;
	uint16_t rgb565_colour;

	/* convert pixel colour from rgb888 to rgb565 format */
	rgb565_colour = (uint16_t)((((uint32_t)colour & 0xf80000UL) >> 8) |
			(((uint32_t)colour & 0x00fc00UL) >> 5) |
			(((uint32_t)colour & 0x0000f8UL) >> 3));

	/* swap endianess */
	rgb565_colour = __builtin_bswap16(rgb565_colour);

	for (i = 0U; i < DMA_BUFFER_SIZE; i++)
	{
		dmaBuffer[i] = rgb565_colour;
	}

	totalBytesToWrite = (uint32_t)width * (uint32_t)height * (uint32_t)sizeof(uint16_t);
	bytesToWriteThisTime = DMA_BUFFER_SIZE * (uint16_t)sizeof(uint16_t);

	set_window(start_x, start_y, start_x + width - 1U, start_y + height - 1U);

	while (totalBytesToWrite > 0UL)
	{
		if (totalBytesToWrite < bytesToWriteThisTime)
		{
			bytesToWriteThisTime = totalBytesToWrite;
		}
		totalBytesToWrite -= bytesToWriteThisTime;

		write_data_dma(&dmaBuffer, bytesToWriteThisTime);
		wait_for_dma_write_complete();
	}
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

/**
 * Called by the HAL framework when SPI DMA TX interrupt fires
 */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	dma_transmit_complete = true;
}

void mw_hal_lcd_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    __HAL_RCC_SPI2_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_DMA1_CLK_ENABLE();

	/* configure GPIO pins used SPI2 MISO / MOSI / CLK pins */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_13 | GPIO_PIN_15;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* configure GPIO pins used for RESET#, CS# and DC PD6, PD7, PD8 */
	GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* configure SPI2 */
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 10;
	HAL_SPI_Init(&hspi2);

    /* configure SPI2 Tx DMA */
    hdma_spi2_tx.Instance = DMA1_Stream4;
    hdma_spi2_tx.Init.Channel = DMA_CHANNEL_0;
    hdma_spi2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi2_tx.Init.Mode = DMA_NORMAL;
    hdma_spi2_tx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    hdma_spi2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    HAL_DMA_Init(&hdma_spi2_tx);
    __HAL_LINKDMA(&hspi2, hdmatx,hdma_spi2_tx);

	/* configure DMA1_Stream4_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 0UL, 0UL);
	HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);

	/* select the device permanently */
	HAL_GPIO_WritePin(ILI9341_CS_PORT, ILI9341_CS_PIN, GPIO_PIN_RESET);

	/* reset the device */
	HAL_GPIO_WritePin(ILI9341_RST_PORT, ILI9341_RST_PIN, GPIO_PIN_RESET);
	HAL_Delay(200UL);
	HAL_GPIO_WritePin(ILI9341_RST_PORT, ILI9341_RST_PIN, GPIO_PIN_SET);
	HAL_Delay(200UL);

	write_command(0x01U);
	HAL_Delay(10UL);
	write_command(0xcbU);
	write_data(0x39U);
	write_data(0x2cU);
	write_data(0x00U);
	write_data(0x34U);
	write_data(0x02U);
	write_command(0xcfU);
	write_data(0x00U);
	write_data(0xc1U);
	write_data(0x30U);
	write_command(0xe8U);
	write_data(0x85U);
	write_data(0x00U);
	write_data(0x78U);
	write_command(0xeaU);
	write_data(0x00U);
	write_data(0x00U);
	write_command(0xedU);
	write_data(0x64U);
	write_data(0x03U);
	write_data(0x12U);
	write_data(0x81U);
	write_command(0xf7U);
	write_data(0x20U);
	write_command(0xc0U);
	write_data(0x23U);
	write_command(0xc1U);
	write_data(0x10U);
	write_command(0xc5U);
	write_data(0x3eU);
	write_data(0x28U);
	write_command(0xc7U);
	write_data(0x86U);
	write_command(0x36U);
	write_data(0x48U);
	write_command(0x3aU);
	write_data(0x55U);
	write_command(0xb1U);
	write_data(0x00U);
	write_data(0x18U);
	write_command(0xb6U);
	write_data(0x08U);
	write_data(0x82U);
	write_data(0x27U);
	write_command(0xf2U);
	write_data(0x00U);
	write_command(0x26U);
	write_data(0x01U);
	write_command(0xe0U);
	write_data(0x0fU);
	write_data(0x31U);
	write_data(0x2bU);
	write_data(0x0cU);
	write_data(0x0eU);
	write_data(0x08U);
	write_data(0x4eU);
	write_data(0xf1U);
	write_data(0x37U);
	write_data(0x07U);
	write_data(0x10U);
	write_data(0x03U);
	write_data(0x0eU);
	write_data(0x09U);
	write_data(0x00U);
	write_command(0xe1U);
	write_data(0x00U);
	write_data(0x0eU);
	write_data(0x14U);
	write_data(0x03U);
	write_data(0x11U);
	write_data(0x07U);
	write_data(0x31U);
	write_data(0xc1U);
	write_data(0x48U);
	write_data(0x08U);
	write_data(0x0fU);
	write_data(0x0cU);
	write_data(0x31U);
	write_data(0x36U);
	write_data(0x0fU);
	write_command(0x11U);
	HAL_Delay(120UL);
	write_command(0x29U);
	write_command(0x36U);
	write_data(0x48U);
}

/**
 * The ISR for the SPI TX DMA transfer complete
 */
void DMA1_Stream4_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&hdma_spi2_tx);
}

int16_t mw_hal_lcd_get_display_width(void)
{
	return (LCD_DISPLAY_WIDTH_PIXELS);
}

int16_t mw_hal_lcd_get_display_height(void)
{
	return (LCD_DISPLAY_HEIGHT_PIXELS);
}

void mw_hal_lcd_pixel(int16_t x, int16_t y, mw_hal_lcd_colour_t colour)
{
	uint16_t rgb565_colour;

	/* convert pixel colour from rgb888 to rgb565 format */
	rgb565_colour = (uint16_t)((((uint32_t)colour & 0xf80000U) >> 8) |
			(((uint32_t)colour & 0xfc00U) >> 5) |
			(((uint32_t)colour & 0xf8U) >> 3));

	/* swap endianess */
	rgb565_colour = __builtin_bswap16(rgb565_colour);

#if defined(MW_DISPLAY_ROTATION_0)
	set_window((uint16_t)x, (uint16_t)y, (uint16_t)x, (uint16_t)y);
#elif defined(MW_DISPLAY_ROTATION_90)
	set_window(y, (uint16_t)LCD_DISPLAY_HEIGHT_PIXELS - 1U - (uint16_t)x, y, (uint16_t)LCD_DISPLAY_HEIGHT_PIXELS - 1U - (uint16_t)x);
#elif defined (MW_DISPLAY_ROTATION_180)
	set_window((uint16_t)LCD_DISPLAY_WIDTH_PIXELS - (uint16_t)x - 1U, (uint16_t)LCD_DISPLAY_HEIGHT_PIXELS - 1U - (uint16_t)y, (uint16_t)LCD_DISPLAY_WIDTH_PIXELS - (uint16_t)x - 1U, (uint16_t)LCD_DISPLAY_HEIGHT_PIXELS - 1U - (uint16_t)y);
#elif defined (MW_DISPLAY_ROTATION_270)
	set_window((uint16_t)LCD_DISPLAY_WIDTH_PIXELS - 1U - (uint16_t)y, (uint16_t)x, (uint16_t)LCD_DISPLAY_WIDTH_PIXELS - 1U - (uint16_t)y, (uint16_t)x);
#endif

	HAL_SPI_Transmit(&hspi2, (uint8_t *)&rgb565_colour, sizeof(uint16_t), 100UL);
}

void mw_hal_lcd_filled_rectangle(int16_t start_x,
		int16_t start_y,
		int16_t width,
		int16_t height,
		mw_hal_lcd_colour_t colour)
{
#if defined(MW_DISPLAY_ROTATION_0)
	mw_hal_lcd_filled_rectangle_rotated(start_x, start_y, width, height, colour);
#elif defined(MW_DISPLAY_ROTATION_90)
	mw_hal_lcd_filled_rectangle_rotated(start_y, LCD_DISPLAY_HEIGHT_PIXELS - start_x - width, height, width, colour);
#elif defined (MW_DISPLAY_ROTATION_180)
	mw_hal_lcd_filled_rectangle_rotated(LCD_DISPLAY_WIDTH_PIXELS - start_x - width, LCD_DISPLAY_HEIGHT_PIXELS - start_y - height, width, height, colour);
#elif defined (MW_DISPLAY_ROTATION_270)
	mw_hal_lcd_filled_rectangle_rotated(LCD_DISPLAY_WIDTH_PIXELS - start_y - height, start_x, height, width, colour);
#endif
}

void mw_hal_lcd_colour_bitmap_clip(int16_t image_start_x,
		int16_t image_start_y,
		uint16_t bitmap_width,
		uint16_t bitmap_height,
		int16_t clip_start_x,
		int16_t clip_start_y,
		int16_t clip_width,
		int16_t clip_height,
		const uint8_t *image_data)
{
	int16_t x;
	int16_t y;
	mw_hal_lcd_colour_t pixel_colour;

	for (y = 0; y < (int16_t)bitmap_height; y++)
	{
		for (x = 0; x < (int16_t)bitmap_width; x++)
		{
			if (x + image_start_x >= clip_start_x &&
					x + image_start_x < clip_start_x + clip_width &&
					y + image_start_y >= clip_start_y &&
					y + image_start_y < clip_start_y + clip_height)
			{
				pixel_colour = *(2 + image_data + (x + y * (int16_t)bitmap_width) * 3);
				pixel_colour <<= 8;
				pixel_colour += *(1 + image_data + (x + y * (int16_t)bitmap_width) * 3);
				pixel_colour <<= 8;
				pixel_colour += *(image_data + (x + y * (int16_t)bitmap_width) * 3);
				mw_hal_lcd_pixel(x + image_start_x, y + image_start_y, pixel_colour);
			}
		}
	}
}

void mw_hal_lcd_monochrome_bitmap_clip(int16_t image_start_x,
		int16_t image_start_y,
		uint16_t bitmap_width,
		uint16_t bitmap_height,
		int16_t clip_start_x,
		int16_t clip_start_y,
		int16_t clip_width,
		int16_t clip_height,
		mw_hal_lcd_colour_t fg_colour,
		mw_hal_lcd_colour_t bg_colour,
		const uint8_t *image_data)
{
	int16_t x;
	int16_t y;
	int16_t a;
	uint8_t image_byte;
	uint8_t mask;
	int16_t array_width_bytes;

	array_width_bytes = (int16_t)bitmap_width / 8;
	if (bitmap_width % 8U > 0U)
	{
		array_width_bytes++;
	}

	for (y = 0; y < (int16_t)bitmap_height; y++)
	{
		for (a = 0; a < array_width_bytes; a++)
		{
			image_byte = image_data[y * array_width_bytes + a];
			mask = 0x80U;
			for (x = 0; x < 8; x++)
			{
				if ((a * 8) + x == (int16_t)bitmap_width)
				{
					break;
				}
				if ((a * 8) + x + image_start_x >= clip_start_x &&
						(a * 8) + x + image_start_x < clip_start_x + clip_width &&
						y + image_start_y >= clip_start_y &&
						y + image_start_y < clip_start_y + clip_height)
				{
					if ((image_byte & mask) == 0U)
					{
						mw_hal_lcd_pixel((a * 8) + x + image_start_x, y + image_start_y, fg_colour);
					}
					else
					{
						mw_hal_lcd_pixel((a * 8) + x + image_start_x, y + image_start_y, bg_colour);
					}
				}
				mask >>= 1;
			}
		}
	}
}

#endif
