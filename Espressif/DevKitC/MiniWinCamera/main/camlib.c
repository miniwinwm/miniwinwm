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

#include <stdint.h>
#include "camlib.h"
#include "driver/ledc.h"
#include "driver/i2c.h"

/****************
*** CONSTANTS ***
****************/

#define OV7670_WRITE_ADDR 	0x42U
#define VS					GPIO_NUM_2
#define HS					GPIO_NUM_39
#define PLK					GPIO_NUM_4
#define SDA					GPIO_NUM_26
#define SCL					GPIO_NUM_27
#define XLK					GPIO_NUM_12
#define D0					GPIO_NUM_32
#define D1					GPIO_NUM_33
#define D2					GPIO_NUM_34
#define D3					GPIO_NUM_35
#define D4					GPIO_NUM_36
#define D5					GPIO_NUM_3
#define D6					GPIO_NUM_14
#define D7					GPIO_NUM_15

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
    ledc_timer_config_t timer_conf;
    ledc_channel_config_t ch_conf;

    periph_module_enable(PERIPH_LEDC_MODULE);

    timer_conf.duty_resolution = LEDC_TIMER_2_BIT;
    timer_conf.freq_hz = 10000000U;
    timer_conf.speed_mode = LEDC_HIGH_SPEED_MODE;
    timer_conf.timer_num = LEDC_TIMER_0 ;
    timer_conf.clk_cfg = LEDC_AUTO_CLK;
    ledc_timer_config(&timer_conf);

    ch_conf.gpio_num = XLK;
    ch_conf.speed_mode = LEDC_HIGH_SPEED_MODE;
    ch_conf.channel = LEDC_CHANNEL_0 ;
    ch_conf.intr_type = LEDC_INTR_DISABLE;
    ch_conf.timer_sel = LEDC_TIMER_0 ;
    ch_conf.duty = 2U;
    ch_conf.hpoint = 0;
    ledc_channel_config(&ch_conf);
}

static void cam_paralell_io_init(void)
{
    gpio_set_direction(D0, GPIO_MODE_INPUT);
    gpio_set_direction(D1, GPIO_MODE_INPUT);
    gpio_set_direction(D2, GPIO_MODE_INPUT);
    gpio_set_direction(D3, GPIO_MODE_INPUT);
    gpio_set_direction(D4, GPIO_MODE_INPUT);
    gpio_set_direction(D5, GPIO_MODE_INPUT);
    gpio_set_direction(D6, GPIO_MODE_INPUT);
    gpio_set_direction(D7, GPIO_MODE_INPUT);
    gpio_set_direction(HS, GPIO_MODE_INPUT);
    gpio_set_direction(VS, GPIO_MODE_INPUT);
    gpio_set_direction(PLK, GPIO_MODE_INPUT);
}

static void sccb_init(void)
{
    i2c_config_t conf = {0};

    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = SDA;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = SCL;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 100000U;

    i2c_param_config(I2C_NUM_0, &conf);
    i2c_driver_install(I2C_NUM_0, conf.mode, (size_t)0, (size_t)0, 0);
}

static void delay(volatile uint16_t count)
{
	while (count--)
	{
	}
}

void sccb_write(uint8_t reg, uint8_t data)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, OV7670_WRITE_ADDR | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg, true);
    i2c_master_write_byte(cmd, data, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
}

static void ov7670_init(void)
{
	uint8_t i;
    uint8_t wdata[2];

	for (i = 0U; i < (uint8_t)sizeof(OV7670_register_setup) / 2U; i++)
	{
        wdata[0] = OV7670_register_setup[i][0];
        wdata[1] = OV7670_register_setup[i][1];
        sccb_write(wdata[0], wdata[1]);
        delay(0xffffU);
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
}

uint16_t *camlib_get_frame(void)
{
	return (uint16_t *)&frame_buffer[0];
}

void camlib_capture(void)
{
	uint_fast32_t i;

	portMUX_TYPE myMutex = portMUX_INITIALIZER_UNLOCKED;
	portENTER_CRITICAL(&myMutex);

	/* wait for VS */
	while (gpio_get_level(VS) == 0)
	{
	}

	while (gpio_get_level(VS) == 1)
	{
	}
	i = 0UL;

    uint_fast8_t y;
	for (y = 0U; y < 120U; y++)
	{
		/* wait for first HS */
		while (gpio_get_level(HS) == 0)
		{
		}

		while (gpio_get_level(HS) == 1)
		{
		}

		/* wait for second HS */
		while (gpio_get_level(HS) == 0)
		{
		}
        
        uint_fast16_t x;
		for (x = 0U; x < 160U; x++)
		{
			/* wait for PLK */
			while (gpio_get_level(PLK) == 0)
			{
			}

		    frame_buffer[i] = (uint8_t)GPIO.in1.data & 0x1fu;
		    frame_buffer[i] |= ((uint8_t)(GPIO.in >> 8)) & 0xc0U;
		    frame_buffer[i] |= ((uint8_t)(GPIO.in << 2)) & 0x20U;
			i++;

			/* wait for ~PLK */
			while (gpio_get_level(PLK) == 1)
			{
			}

			/* wait for PLK */
			while (gpio_get_level(PLK) == 0)
			{
			}

		    frame_buffer[i] = (uint8_t)GPIO.in1.data & 0x1fu;
		    frame_buffer[i] |= ((uint8_t)(GPIO.in >> 8)) & 0xc0U;
		    frame_buffer[i] |= ((uint8_t)(GPIO.in << 2)) & 0x20U;
			i++;            

			/* wait for ~PLK */
			while (gpio_get_level(PLK) == 1)
			{
			}

			/* repeat ignoring read */
			while (gpio_get_level(PLK) == 0)
			{
			}

			while (gpio_get_level(PLK) == 1)
			{
			}

			while (gpio_get_level(PLK) == 0)
			{
			}

			while (gpio_get_level(PLK) == 1)
			{
			}
		}
	}

	portEXIT_CRITICAL(&myMutex);
}
