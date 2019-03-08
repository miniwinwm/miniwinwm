/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2014(2015-2018) Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name    : r_tfat_driver_rx_if.h
* Description  : TFAT driver Interface.
*******************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 01.12.2014 1.00     First Release
*              : 05.01.2015 1.01     Added support USB Mini Firmware.
*              : 22.06.2015 1.02     Added support MCU RX231.
*              : 01.04.2016 1.03     Added support RX family.
*              : 29.06.2018 1.04     Modified SDHI to SDMEM.
*******************************************************************************/
#ifndef _R_TFAT_DRIVER_RX_IF_H_
#define _R_TFAT_DRIVER_RX_IF_H_

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include <stdint.h>
#include "r_tfat_lib.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/
/* used memory define */
#define TFAT_CTRL_USB     1
#define TFAT_CTRL_SDMEM    2
//#define TFAT_CTRL_MMC     3
#define TFAT_CTRL_USB_MINI     4

/*******************************************************************************
Typedef definitions
*******************************************************************************/
/* Drive number define ("uint8_t drive") */
typedef enum
{
    TFAT_DRIVE_NUM_0 = 0x00,
    TFAT_DRIVE_NUM_1,
    TFAT_DRIVE_NUM_2,
    TFAT_DRIVE_NUM_3,
    TFAT_DRIVE_NUM_4,
    TFAT_DRIVE_NUM_5,
    TFAT_DRIVE_NUM_6,
    TFAT_DRIVE_NUM_7,
    TFAT_DRIVE_NUM_8,
    TFAT_DRIVE_NUM_9,
    TFAT_DRIVE_NUM_MAX,
}TFAT_DRV_NUM;

/*******************************************************************************
Exported global functions (to be accessed by other files)
*******************************************************************************/

/* refer to r_tfat_lib.h(r_tfat_rx:TFAT module) */
#if 0
DSTATUS R_tfat_disk_initialize(uint8_t drive);
DRESULT R_tfat_disk_read(uint8_t drive, uint8_t* buffer, uint32_t sector_number, uint8_t sector_count);
DRESULT R_tfat_disk_write(uint8_t crive, const uint8_t* buffer, uint32_t sector_number, uint8_t sector_count);
DRESULT R_tfat_disk_ioctl(uint8_t crive, uint8_t command, void* buffer);
DSTATUS R_tfat_disk_status(uint8_t drive);

/* User defined function to give a current time to fatfs module */
/* 31-25: Year(0-127 +1980), 24-21: Month(1-12), 20-16: Day(1-31)
   15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */
extern uint32_t R_tfat_get_fattime(void);
#endif

extern DRESULT R_tfat_drv_change_alloc(TFAT_DRV_NUM tfat_drv, uint8_t dev_type, uint8_t dev_drv_num );

#endif    /* _R_TFAT_DRIVER_RX_IF_H_ */

/*******************************************************************************
End  of file
*******************************************************************************/
