/*

MIT License

Copyright (c) John Blaiklock 2020 miniwin Embedded Window Manager

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

#ifdef ARDUINO_ARCH_ESP32

/***************
*** INCLUDES ***
***************/

#include "hal/hal_non_vol.h"
#include "nvs_flash.h"

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

void mw_hal_non_vol_init(void)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        /* NVS partition was truncated and needs to be erased */
        nvs_flash_erase();
        err = nvs_flash_init();
    }
}

void mw_hal_non_vol_load(uint8_t *data, uint16_t length)
{
	nvs_handle my_handle;
	size_t required_size = (size_t)length;

	nvs_open("MINIWIN_NON_VOL", NVS_READONLY, &my_handle);
	
	nvs_get_blob(my_handle, "SETTINGS", data, &required_size);

    nvs_close(my_handle);
}

void mw_hal_non_vol_save(uint8_t *data, uint16_t length)
{
	nvs_handle my_handle;

	nvs_open("MINIWIN_NON_VOL", NVS_READWRITE, &my_handle);

	nvs_set_blob(my_handle, "SETTINGS", data, (size_t)length);
	nvs_commit(my_handle);

    nvs_close(my_handle);
}

#endif
