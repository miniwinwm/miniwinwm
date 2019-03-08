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
* File Name     : r_tfat_driver_rx_config.h
* Description   : Configures the TFAT driver interface
*******************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 01.12.2014 1.00     First Release
*              : 21.01.2015 1.01     Added support USB Mini Firmware.
*              : 22.06.2015 1.02     Added support MCU RX231.
*              : 01.04.2016 1.03     Added support RX family.
*              : 29.06.2018 1.04     Modified SDHI to SDMEM.
*******************************************************************************/
#ifndef _R_TFAT_DRIVER_RX_CONFIG_H_
#define _R_TFAT_DRIVER_RX_CONFIG_H_

#include "r_tfat_driver_rx_if.h"

/*******************************************************************************
Configuration Options
*******************************************************************************/
/* Number of logical drives to be used.
   Setting to 0     : unused memory
              other : number of logical drives
   (USB and SD memory card can be used together.)
*/
#define TFAT_USB_DRIVE_NUM         (0)
#define TFAT_SDMEM_DRIVE_NUM       (0)
#define TFAT_USB_MINI_DRIVE_NUM    (0)

/* alocate a drive number(initial setting)
  <valid define>
  TFAT_CTRL_USB      : for USB
  TFAT_CTRL_SDMEM    : for SD memory card
  TFAT_CTRL_USB_MINI : for USB Mini
  NULL               : unallocated drive

  MAX 10 drives(TFAT module spec)

  ex.)
      #define TFAT_DRIVE_ALLOC_NUM_0    TFAT_CTRL_USB
      #define TFAT_DRIVE_ALLOC_NUM_1    TFAT_CTRL_SDMEM
      #define TFAT_DRIVE_ALLOC_NUM_2    TFAT_CTRL_SDMEM
      #define TFAT_DRIVE_ALLOC_NUM_3    TFAT_CTRL_USB

  The device channel or The drive number of device side is ascending number.

  When you'd like to change the allocation.
  Please use R_tfat_drv_change_alloc().
*/
#define TFAT_DRIVE_ALLOC_NUM_0    NULL
#define TFAT_DRIVE_ALLOC_NUM_1    NULL
#define TFAT_DRIVE_ALLOC_NUM_2    NULL
#define TFAT_DRIVE_ALLOC_NUM_3    NULL
#define TFAT_DRIVE_ALLOC_NUM_4    NULL
#define TFAT_DRIVE_ALLOC_NUM_5    NULL
#define TFAT_DRIVE_ALLOC_NUM_6    NULL
#define TFAT_DRIVE_ALLOC_NUM_7    NULL
#define TFAT_DRIVE_ALLOC_NUM_8    NULL
#define TFAT_DRIVE_ALLOC_NUM_9    NULL

#endif /* _R_TFAT_DRIVER_RX_CONFIG_H_ */
