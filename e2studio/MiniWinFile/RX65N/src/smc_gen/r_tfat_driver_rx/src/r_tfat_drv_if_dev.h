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
* History      : DD.MM.YYYY Version  Description
*              : 01.12.2014 1.00     First Release
*              : 21.01.2015 1.01     Added support USB Mini Firmware
*              : 22.06.2015 1.02     Added support MCU RX231.
*              : 01.04.2016 1.03     Updated the xml file.
*              : 29.06.2018 1.04     Modified SDHI to SDMEM.
*******************************************************************************/
/*******************************************************************************
* File Name    : r_tfat_driver_rx_if_dev.h
* Description  : TFAT driver Interface on RX devices.
*******************************************************************************/
#ifndef _R_TFAT_DRIVER_RX_IF_DEV_H_
#define _R_TFAT_DRIVER_RX_IF_DEV_H_

/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "r_tfat_driver_rx_config.h"
#include "r_tfat_lib.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/


/*******************************************************************************
Typedef definitions
*******************************************************************************/

/*******************************************************************************
Exported global functions (to be accessed by other files)
*******************************************************************************/
#if (TFAT_USB_DRIVE_NUM > 0)
DSTATUS R_tfat_usb_disk_initialize(uint8_t drive);
DRESULT R_tfat_usb_disk_read(uint8_t drive, uint8_t* buffer, uint32_t sector_number, uint8_t sector_count);
DRESULT R_tfat_usb_disk_write(uint8_t crive, const uint8_t* buffer, uint32_t sector_number, uint8_t sector_count);
DRESULT R_tfat_usb_disk_ioctl(uint8_t crive, uint8_t command, void* buffer);
DSTATUS R_tfat_usb_disk_status(uint8_t drive);
#endif // (TFAT_USB_DRIVE_NUM > 0)

#if (TFAT_USB_MINI_DRIVE_NUM > 0)
DSTATUS R_tfat_usb_mini_disk_initialize(uint8_t drive);
DRESULT R_tfat_usb_mini_disk_read(uint8_t drive, uint8_t* buffer, uint32_t sector_number, uint8_t sector_count);
DRESULT R_tfat_usb_mini_disk_write(uint8_t crive, const uint8_t* buffer, uint32_t sector_number, uint8_t sector_count);
DRESULT R_tfat_usb_mini_disk_ioctl(uint8_t crive, uint8_t command, void* buffer);
DSTATUS R_tfat_usb_mini_disk_status(uint8_t drive);
#endif // (TFAT_USB_MINI_DRIVE_NUM > 0)

#if (TFAT_SDMEM_DRIVE_NUM > 0)
DSTATUS R_tfat_sdmem_disk_initialize(uint8_t drive);
DRESULT R_tfat_sdmem_disk_read(uint8_t drive, uint8_t* buffer, uint32_t sector_number, uint8_t sector_count);
DRESULT R_tfat_sdmem_disk_write(uint8_t crive, const uint8_t* buffer, uint32_t sector_number, uint8_t sector_count);
DRESULT R_tfat_sdmem_disk_ioctl(uint8_t crive, uint8_t command, void* buffer);
DSTATUS R_tfat_sdmem_disk_status(uint8_t drive);
#endif // (TFAT_SDMEM_DRIVE_NUM > 0)

#endif    /* _R_TFAT_DRIVER_RX_IF_DEV_H_ */

/* End of File */
