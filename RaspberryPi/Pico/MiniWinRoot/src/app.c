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

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "app.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

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

void app_init(void)
{
    /* led setup */
    gpio_init(LED_GPIO);
    gpio_set_dir(LED_GPIO, GPIO_OUT);
    
    /* spi setup */
    spi_init(SPI_TOUCH_LCD_ID, LCD_SPEED);
    gpio_set_function(SPI0_MISO_GPIO, GPIO_FUNC_SPI);
    gpio_set_function(SPI0_CLK_GPIO, GPIO_FUNC_SPI);
    gpio_set_function(SPI0_MOSI_GPIO, GPIO_FUNC_SPI);      
    
    /* touch setup */
    gpio_init(TOUCH_CS_GPIO);
    gpio_set_dir(TOUCH_CS_GPIO, GPIO_OUT);
    gpio_put(TOUCH_CS_GPIO, 1);
    gpio_init(TOUCH_T_IRQ_GPIO);
    gpio_set_dir(TOUCH_T_IRQ_GPIO, GPIO_IN);    
    gpio_init(TOUCH_RECAL_GPIO);
    gpio_set_dir(TOUCH_RECAL_GPIO, GPIO_IN);   
    gpio_pull_up(TOUCH_RECAL_GPIO);
    
    /* lcd setup */
    gpio_init(LCD_RESET_GPIO);
    gpio_set_dir(LCD_RESET_GPIO, GPIO_OUT);
    gpio_init(LCD_DC_GPIO);
    gpio_set_dir(LCD_DC_GPIO, GPIO_OUT);
    gpio_init(LCD_CS_GPIO);
    gpio_set_dir(LCD_CS_GPIO, GPIO_OUT);      
    gpio_put(LCD_CS_GPIO, 1);
}

void app_main_loop_process(void)
{
}
