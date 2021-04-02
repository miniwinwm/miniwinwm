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

#include "miniwin.h"
#include "board.h"
#include "pin_mux.h"
#include "fsl_spifi.h"

/****************
*** CONSTANTS ***
****************/

#define PAGE_SIZE 				256U
#define SECTOR_SIZE 			4096U
#define EXAMPLE_SPI_BAUDRATE 	96000000U
#define QUAD_MODE_VAL 			0x02U
#define READ 					0U
#define PROGRAM_PAGE 			1U
#define GET_STATUS 				2U
#define ERASE_SECTOR 			3U
#define WRITE_ENABLE 			4U
#define WRITE_REGISTER 			5U

static spifi_command_t command[] = {
    {PAGE_SIZE, false, kSPIFI_DataInput, 1U, kSPIFI_CommandDataQuad, kSPIFI_CommandOpcodeAddrThreeBytes, 0x6BU},
    {PAGE_SIZE, false, kSPIFI_DataOutput, 0U, kSPIFI_CommandDataQuad, kSPIFI_CommandOpcodeAddrThreeBytes, 0x32U},
    {1U, false, kSPIFI_DataInput, 0U, kSPIFI_CommandAllSerial, kSPIFI_CommandOpcodeOnly, 0x05U},
    {0U, false, kSPIFI_DataOutput, 0U, kSPIFI_CommandAllSerial, kSPIFI_CommandOpcodeAddrThreeBytes, 0x20U},
    {0U, false, kSPIFI_DataOutput, 0U, kSPIFI_CommandAllSerial, kSPIFI_CommandOpcodeOnly, 0x06U},
    {1U, false, kSPIFI_DataOutput, 0U, kSPIFI_CommandAllSerial, kSPIFI_CommandOpcodeOnly, 0x31U}};

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

/**
 * Enablde quad spi mode for chips that support it
 */
static void enable_quad_mode();

/**********************
*** LOCAL FUNCTIONS ***
**********************/

static void enable_quad_mode()
{
    uint8_t val = 0U;

    /* write enable */
    SPIFI_SetCommand(SPIFI0, &command[WRITE_ENABLE]);

    /* set write register command */
    SPIFI_SetCommand(SPIFI0, &command[WRITE_REGISTER]);

    SPIFI_WriteDataByte(SPIFI0, QUAD_MODE_VAL);

    /* check WIP bit */
    do
    {
        SPIFI_SetCommand(SPIFI0, &command[GET_STATUS]);
        while ((SPIFI0->STAT & SPIFI_STAT_INTRQ_MASK) == 0U)
        {
        }
        val = SPIFI_ReadDataByte(SPIFI0);
    }
    while (val & 0x1U);
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void app_init(void)
{
    spifi_config_t config;

    BOARD_InitPins();

    /* boot up FROHF96M for SPIFI to use*/
    BOARD_BootClockFROHF96M();

    /* core clock boot to 220Mhz*/
    BOARD_BootClockPLL220M();

    /* attach 12 MHz clock to SPI3 */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM9);

    /* set SPIFI clock source */
    CLOCK_AttachClk(kFRO_HF_to_SPIFI_CLK);

    /* set the clock divider */
    CLOCK_SetClkDiv(kCLOCK_DivSpifiClk, CLOCK_GetFroHfFreq() / EXAMPLE_SPI_BAUDRATE, false);

    /* initialize SPIFI */
    SPIFI_GetDefaultConfig(&config);
    SPIFI_Init(SPIFI0, &config);

    /* enable Quad mode */
    enable_quad_mode();

    /* reset to memory command mode */
    SPIFI_ResetCommand(SPIFI0);
    SPIFI_SetMemoryCommand(SPIFI0, &command[READ]);

    /* enable lcd buffer ram */
    BOARD_InitSDRAM();
}

void app_main_loop_process(void)
{
}
