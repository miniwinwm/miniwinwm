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
* File Name    : r_tfat_drv_if.c
* Description  : TFAT driver Interface.
*******************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 01.12.2014 1.00     First Release
*              : 21.01.2015 1.01     Added Support USB Mini Firmware.
*              : 22.06.2015 1.02     Added support MCU RX231.
*              : 01.04.2016 1.03     Updated the xml file.
*              : 29.06.2018 1.04     Modified R_tfat_get_fattime() and SD memory device.
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "platform.h"
#include "r_tfat_driver_rx_if.h"
#include "r_tfat_driver_rx_config.h"
#include "r_tfat_drv_if_dev.h"
#include "r_sys_time_rx_if.h"

/*******************************************************************************
Macro definitions
*******************************************************************************/
/* for USB */
#if (TFAT_USB_DRIVE_NUM > 0)
#if (TFAT_DRIVE_ALLOC_NUM_0 == TFAT_CTRL_USB)
#define USB_NUM_0    (1)
#define DRV0_DEV_CH  (0)
#else
#define USB_NUM_0    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_0 == TFAT_CTRL_USB)
#if (TFAT_DRIVE_ALLOC_NUM_1 == TFAT_CTRL_USB)
#define USB_NUM_1    (1<<1)
#define DRV1_DEV_CH  (0 + USB_NUM_0)
#else
#define USB_NUM_1    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_1 == TFAT_CTRL_USB)
#if (TFAT_DRIVE_ALLOC_NUM_2 == TFAT_CTRL_USB)
#define USB_NUM_2    (1<<2)
#define DRV2_DEV_CH  (0 + USB_NUM_0 + (USB_NUM_1>>1))
#else
#define USB_NUM_2    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_2 == TFAT_CTRL_USB)
#if (TFAT_DRIVE_ALLOC_NUM_3 == TFAT_CTRL_USB)
#define USB_NUM_3    (1<<3)
#define DRV3_DEV_CH  (0 + USB_NUM_0 + (USB_NUM_1>>1) + (USB_NUM_2>>2))
#else
#define USB_NUM_3    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_3 == TFAT_CTRL_USB)
#if (TFAT_DRIVE_ALLOC_NUM_4 == TFAT_CTRL_USB)
#define USB_NUM_4    (1<<4)
#define DRV4_DEV_CH  (0 + USB_NUM_0 + (USB_NUM_1>>1) + (USB_NUM_2>>2) + (USB_NUM_3>>3))
#else
#define USB_NUM_4    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_4 == TFAT_CTRL_USB)
#if (TFAT_DRIVE_ALLOC_NUM_5 == TFAT_CTRL_USB)
#define USB_NUM_5    (1<<5)
#define DRV5_DEV_CH  (0 + USB_NUM_0 + (USB_NUM_1>>1) + (USB_NUM_2>>2) + (USB_NUM_3>>3) + (USB_NUM_4>>4))
#else
#define USB_NUM_5    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_5 == TFAT_CTRL_USB)
#if (TFAT_DRIVE_ALLOC_NUM_6 == TFAT_CTRL_USB)
#define USB_NUM_6    (1<<6)
#define DRV6_DEV_CH  (0 + USB_NUM_0 + (USB_NUM_1>>1) + (USB_NUM_2>>2) + (USB_NUM_3>>3) + (USB_NUM_4>>4) + (USB_NUM_5>>5))
#else
#define USB_NUM_6    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_6 == TFAT_CTRL_USB)
#if (TFAT_DRIVE_ALLOC_NUM_7 == TFAT_CTRL_USB)
#define USB_NUM_7    (1<<7)
#define DRV7_DEV_CH  (0 + USB_NUM_0 + (USB_NUM_1>>1) + (USB_NUM_2>>2) + (USB_NUM_3>>3) + (USB_NUM_4>>4) + (USB_NUM_5>>5) + (USB_NUM_6>>6))
#else
#define USB_NUM_7    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_7 == TFAT_CTRL_USB)
#if (TFAT_DRIVE_ALLOC_NUM_8 == TFAT_CTRL_USB)
#define USB_NUM_8    (1<<8)
#define DRV8_DEV_CH  (0 + USB_NUM_0 + (USB_NUM_1>>1) + (USB_NUM_2>>2) + (USB_NUM_3>>3) + (USB_NUM_4>>4) + (USB_NUM_5>>5) + (USB_NUM_6>>6) + (USB_NUM_7>>7))
#else
#define USB_NUM_8    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_8 == TFAT_CTRL_USB)
#if (TFAT_DRIVE_ALLOC_NUM_9 == TFAT_CTRL_USB)
#define USB_NUM_9    (1<<9)
#define DRV9_DEV_CH  (0 + USB_NUM_0 + (USB_NUM_1>>1) + (USB_NUM_2>>2) + (USB_NUM_3>>3) + (USB_NUM_4>>4) + (USB_NUM_5>>5) + (USB_NUM_6>>6) + (USB_NUM_7>>7) + (USB_NUM_8>>8))
#else
#define USB_NUM_9    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_9 == TFAT_CTRL_USB)

static uint32_t TFAT_DRIVE_USB_ALLOC = (USB_NUM_9 | USB_NUM_8 | USB_NUM_7 | USB_NUM_6 | USB_NUM_5 | USB_NUM_4 | USB_NUM_3 | USB_NUM_2 | USB_NUM_1 | USB_NUM_0);

#if TFAT_USB_DRIVE_NUM != ( (USB_NUM_9>>9)+(USB_NUM_8>>8)+(USB_NUM_7>>7)+(USB_NUM_6>>6)+(USB_NUM_5>>5)+(USB_NUM_4>>4)+(USB_NUM_3>>3)+(USB_NUM_2>>2)+(USB_NUM_1>>1)+USB_NUM_0 )
#error "Error! Invalid setting for TFAT_USB_DRIVE_NUM or TFAT_DRIVE_ALLOC_NUM_x in r_tfat_driver_rx_config.h"
#endif

#endif // (TFAT_USB_DRIVE_NUM > 0)


/* for SD memory card */
#if (TFAT_SDMEM_DRIVE_NUM > 0)
#if (TFAT_DRIVE_ALLOC_NUM_0 == TFAT_CTRL_SDMEM)
#define SDMEM_NUM_0   (1)
#define DRV0_DEV_CH   (0)
#else
#define SDMEM_NUM_0   (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_0 == TFAT_CTRL_SDMEM)
#if (TFAT_DRIVE_ALLOC_NUM_1 == TFAT_CTRL_SDMEM)
#define SDMEM_NUM_1   (1<<1)
#define DRV1_DEV_CH   (0 + SDMEM_NUM_0)
#else
#define SDMEM_NUM_1   (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_1 == TFAT_CTRL_SDMEM)
#if (TFAT_DRIVE_ALLOC_NUM_2 == TFAT_CTRL_SDMEM)
#define SDMEM_NUM_2   (1<<2)
#define DRV2_DEV_CH   (0 + SDMEM_NUM_0 + (SDMEM_NUM_1>>1))
#else
#define SDMEM_NUM_2   (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_2 == TFAT_CTRL_SDMEM)
#if (TFAT_DRIVE_ALLOC_NUM_3 == TFAT_CTRL_SDMEM)
#define SDMEM_NUM_3   (1<<3)
#define DRV3_DEV_CH   (0 + SDMEM_NUM_0 + (SDMEM_NUM_1>>1) + (SDMEM_NUM_2>>2))
#else
#define SDMEM_NUM_3   (0)
#endif //  (TFAT_DRIVE_ALLOC_NUM_3 == TFAT_CTRL_SDMEM)
#if (TFAT_DRIVE_ALLOC_NUM_4 == TFAT_CTRL_SDMEM)
#define SDMEM_NUM_4   (1<<4)
#define DRV4_DEV_CH   (0 + SDMEM_NUM_0 + (SDMEM_NUM_1>>1) + (SDMEM_NUM_2>>2) + (SDMEM_NUM_3>>3))
#else
#define SDMEM_NUM_4    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_4 == TFAT_CTRL_SDMEM)
#if (TFAT_DRIVE_ALLOC_NUM_5 == TFAT_CTRL_SDMEM)
#define SDMEM_NUM_5   (1<<5)
#define DRV5_DEV_CH   (0 + SDMEM_NUM_0 + (SDMEM_NUM_1>>1) + (SDMEM_NUM_2>>2) + (SDMEM_NUM_3>>3) + (SDMEM_NUM_4>>4))
#else
#define SDMEM_NUM_5    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_5 == TFAT_CTRL_SDMEM)
#if (TFAT_DRIVE_ALLOC_NUM_6 == TFAT_CTRL_SDMEM)
#define SDMEM_NUM_6   (1<<6)
#define DRV6_DEV_CH   (0 + SDMEM_NUM_0 + (SDMEM_NUM_1>>1) + (SDMEM_NUM_2>>2) + (SDMEM_NUM_3>>3) + (SDMEM_NUM_4>>4) + (SDMEM_NUM_5>>5))
#else
#define SDMEM_NUM_6    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_6 == TFAT_CTRL_SDMEM)
#if (TFAT_DRIVE_ALLOC_NUM_7 == TFAT_CTRL_SDMEM)
#define SDMEM_NUM_7   (1<<7)
#define DRV7_DEV_CH   (0 + SDMEM_NUM_0 + (SDMEM_NUM_1>>1) + (SDMEM_NUM_2>>2) + (SDMEM_NUM_3>>3) + (SDMEM_NUM_4>>4) + (SDMEM_NUM_5>>5) + (SDMEM_NUM_6>>6))
#else
#define SDMEM_NUM_7    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_7 == TFAT_CTRL_SDMEM)
#if (TFAT_DRIVE_ALLOC_NUM_8 == TFAT_CTRL_SDMEM)
#define SDMEM_NUM_8   (1<<8)
#define DRV8_DEV_CH   (0 + SDMEM_NUM_0 + (SDMEM_NUM_1>>1) + (SDMEM_NUM_2>>2) + (SDMEM_NUM_3>>3) + (SDMEM_NUM_4>>4) + (SDMEM_NUM_5>>5) + (SDMEM_NUM_6>>6) + (SDMEM_NUM_7>>7))
#else
#define SDMEM_NUM_8    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_8 == TFAT_CTRL_SDMEM)
#if (TFAT_DRIVE_ALLOC_NUM_9 == TFAT_CTRL_SDMEM)
#define SDMEM_NUM_9   (1<<9)
#define DRV9_DEV_CH   (0 + SDMEM_NUM_0 + (SDMEM_NUM_1>>1) + (SDMEM_NUM_2>>2) + (SDMEM_NUM_3>>3) + (SDMEM_NUM_4>>4) + (SDMEM_NUM_5>>5) + (SDMEM_NUM_6>>6) + (SDMEM_NUM_7>>7) + (SDMEM_NUM_8>>8))
#else
#define SDMEM_NUM_9   (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_9 == TFAT_CTRL_SDMEM)

static uint32_t TFAT_DRIVE_SDMEM_ALLOC = (SDMEM_NUM_9 | SDMEM_NUM_8 | SDMEM_NUM_7 | SDMEM_NUM_6 | SDMEM_NUM_5 | SDMEM_NUM_4 | SDMEM_NUM_3 | SDMEM_NUM_2 | SDMEM_NUM_1 | SDMEM_NUM_0);

#if TFAT_SDMEM_DRIVE_NUM != ( (SDMEM_NUM_9>>9)+(SDMEM_NUM_8>>8)+(SDMEM_NUM_7>>7)+(SDMEM_NUM_6>>6)+(SDMEM_NUM_5>>5)+(SDMEM_NUM_4>>4)+(SDMEM_NUM_3>>3)+(SDMEM_NUM_2>>2)+(SDMEM_NUM_1>>1)+SDMEM_NUM_0 )
#error "Error! Invalid setting for TFAT_SDMEM_DRIVE_NUM or TFAT_DRIVE_ALLOC_NUM_x in r_tfat_driver_rx_config.h"
#endif

#endif // (TFAT_SDMEM_DRIVE_NUM > 0)


/* for MMC */
#if (TFAT_MMC_DRIVE_NUM > 0)
#if (TFAT_DRIVE_ALLOC_NUM_0 == TFAT_CTRL_MMC)
#define MMC_NUM_0    (1)
#define DRV0_DEV_CH  (0)
#else
#define MMC_NUM_0    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_0 == TFAT_CTRL_MMC)
#if (TFAT_DRIVE_ALLOC_NUM_1 == TFAT_CTRL_MMC)
#define MMC_NUM_1    (1<<1)
#define DRV1_DEV_CH  (0 + MMC_NUM_0)
#else
#define MMC_NUM_1    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_1 == TFAT_CTRL_MMC)
#if (TFAT_DRIVE_ALLOC_NUM_2 == TFAT_CTRL_MMC)
#define MMC_NUM_2    (1<<2)
#define DRV2_DEV_CH  (0 + MMC_NUM_0 + (MMC_NUM_1>>1))
#else
#define MMC_NUM_2    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_2 == TFAT_CTRL_MMC)
#if (TFAT_DRIVE_ALLOC_NUM_3 == TFAT_CTRL_MMC)
#define MMC_NUM_3    (1<<3)
#define DRV3_DEV_CH  (0 + MMC_NUM_0 + (MMC_NUM_1>>1) + (MMC_NUM_2>>2))
#else
#define MMC_NUM_3    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_3 == TFAT_CTRL_MMC)
#if (TFAT_DRIVE_ALLOC_NUM_4 == TFAT_CTRL_MMC)
#define MMC_NUM_4    (1<<4)
#define DRV4_DEV_CH  (0 + MMC_NUM_0 + (MMC_NUM_1>>1) + (MMC_NUM_2>>2) + (MMC_NUM_3>>3))
#else
#define MMC_NUM_4    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_4 == TFAT_CTRL_MMC)
#if (TFAT_DRIVE_ALLOC_NUM_5 == TFAT_CTRL_MMC)
#define MMC_NUM_5    (1<<5)
#define DRV5_DEV_CH  (0 + MMC_NUM_0 + (MMC_NUM_1>>1) + (MMC_NUM_2>>2) + (MMC_NUM_3>>3) + (MMC_NUM_4>>4))
#else
#define MMC_NUM_5    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_5 == TFAT_CTRL_MMC)
#if (TFAT_DRIVE_ALLOC_NUM_6 == TFAT_CTRL_MMC)
#define MMC_NUM_6    (1<<6)
#define DRV6_DEV_CH  (0 + MMC_NUM_0 + (MMC_NUM_1>>1) + (MMC_NUM_2>>2) + (MMC_NUM_3>>3) + (MMC_NUM_4>>4) + (MMC_NUM_5>>5))
#else
#define MMC_NUM_6    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_6 == TFAT_CTRL_MMC)
#if (TFAT_DRIVE_ALLOC_NUM_7 == TFAT_CTRL_MMC)
#define MMC_NUM_7    (1<<7)
#define DRV7_DEV_CH  (0 + MMC_NUM_0 + (MMC_NUM_1>>1) + (MMC_NUM_2>>2) + (MMC_NUM_3>>3) + (MMC_NUM_4>>4) + (MMC_NUM_5>>5) + (MMC_NUM_6>>6))
#else
#define MMC_NUM_7    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_7 == TFAT_CTRL_MMC)
#if (TFAT_DRIVE_ALLOC_NUM_8 == TFAT_CTRL_MMC)
#define MMC_NUM_8    (1<<8)
#define DRV8_DEV_CH  (0 + MMC_NUM_0 + (MMC_NUM_1>>1) + (MMC_NUM_2>>2) + (MMC_NUM_3>>3) + (MMC_NUM_4>>4) + (MMC_NUM_5>>5) + (MMC_NUM_6>>6) + (MMC_NUM_7>>7))
#else
#define MMC_NUM_8    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_8 == TFAT_CTRL_MMC)
#if (TFAT_DRIVE_ALLOC_NUM_9 == TFAT_CTRL_MMC)
#define MMC_NUM_9    (1<<9)
#define DRV9_DEV_CH  (0 + MMC_NUM_0 + (MMC_NUM_1>>1) + (MMC_NUM_2>>2) + (MMC_NUM_3>>3) + (MMC_NUM_4>>4) + (MMC_NUM_5>>5) + (MMC_NUM_6>>6) + (MMC_NUM_7>>7) + (MMC_NUM_8>>8))
#else
#define MMC_NUM_9    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_9 == TFAT_CTRL_MMC)

static uint32_t TFAT_DRIVE_MMC_ALLOC = (MMC_NUM_9 | MMC_NUM_8 | MMC_NUM_7 | MMC_NUM_6 | MMC_NUM_5 | MMC_NUM_4 | MMC_NUM_3 | MMC_NUM_2 | MMC_NUM_1 | MMC_NUM_0);

#if TFAT_MMC_DRIVE_NUM != ( (MMC_NUM_9>>9)+(MMC_NUM_8>>8)+(MMC_NUM_7>>7)+(MMC_NUM_6>>6)+(MMC_NUM_5>>5)+(MMC_NUM_4>>4)+(MMC_NUM_3>>3)+(MMC_NUM_2>>2)+(MMC_NUM_1>>1)+MMC_NUM_0 )
#error "Error! Invalid setting for TFAT_MMC_DRIVE_NUM or TFAT_DRIVE_ALLOC_NUM_x in r_tfat_driver_rx_config.h"
#endif

#endif // (TFAT_MMC_DRIVE_NUM > 0)

/* for USB mini */
#if (TFAT_USB_MINI_DRIVE_NUM > 0)
#if (TFAT_DRIVE_ALLOC_NUM_0 == TFAT_CTRL_USB_MINI)
#define USB_MINI_NUM_0    (1)
#define DRV0_DEV_CH  (0)
#else
#define USB_MINI_NUM_0    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_0 == TFAT_CTRL_USB_MINI)
#if (TFAT_DRIVE_ALLOC_NUM_1 == TFAT_CTRL_USB_MINI)
#define USB_MINI_NUM_1    (1<<1)
#define DRV1_DEV_CH  (0 + USB_MINI_NUM_0)
#else
#define USB_MINI_NUM_1    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_1 == TFAT_CTRL_USB_MINI)
#if (TFAT_DRIVE_ALLOC_NUM_2 == TFAT_CTRL_USB_MINI)
#define USB_MINI_NUM_2    (1<<2)
#define DRV2_DEV_CH  (0 + USB_MINI_NUM_0 + (USB_MINI_NUM_1>>1))
#else
#define USB_MINI_NUM_2    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_2 == TFAT_CTRL_USB_MINI)
#if (TFAT_DRIVE_ALLOC_NUM_3 == TFAT_CTRL_USB_MINI)
#define USB_MINI_NUM_3    (1<<3)
#define DRV3_DEV_CH  (0 + USB_MINI_NUM_0 + (USB_MINI_NUM_1>>1) + (USB_MINI_NUM_2>>2))
#else
#define USB_MINI_NUM_3    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_3 == TFAT_CTRL_USB_MINI)
#if (TFAT_DRIVE_ALLOC_NUM_4 == TFAT_CTRL_USB_MINI)
#define USB_MINI_NUM_4    (1<<4)
#define DRV4_DEV_CH  (0 + USB_MINI_NUM_0 + (USB_MINI_NUM_1>>1) + (USB_MINI_NUM_2>>2) + (USB_MINI_NUM_3>>3))
#else
#define USB_MINI_NUM_4    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_4 == TFAT_CTRL_USB_MINI)
#if (TFAT_DRIVE_ALLOC_NUM_5 == TFAT_CTRL_USB_MINI)
#define USB_MINI_NUM_5    (1<<5)
#define DRV5_DEV_CH  (0 + USB_MINI_NUM_0 + (USB_MINI_NUM_1>>1) + (USB_MINI_NUM_2>>2) + (USB_MINI_NUM_3>>3) + (USB_MINI_NUM_4>>4))
#else
#define USB_MINI_NUM_5    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_5 == TFAT_CTRL_USB_MINI)
#if (TFAT_DRIVE_ALLOC_NUM_6 == TFAT_CTRL_USB_MINI)
#define USB_MINI_NUM_6    (1<<6)
#define DRV6_DEV_CH  (0 + USB_MINI_NUM_0 + (USB_MINI_NUM_1>>1) + (USB_MINI_NUM_2>>2) + (USB_MINI_NUM_3>>3) + (USB_MINI_NUM_4>>4) + (USB_MINI_NUM_5>>5))
#else
#define USB_MINI_NUM_6    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_6 == TFAT_CTRL_USB_MINI)
#if (TFAT_DRIVE_ALLOC_NUM_7 == TFAT_CTRL_USB_MINI)
#define USB_MINI_NUM_7    (1<<7)
#define DRV7_DEV_CH  (0 + USB_MINI_NUM_0 + (USB_MINI_NUM_1>>1) + (USB_MINI_NUM_2>>2) + (USB_MINI_NUM_3>>3) + (USB_MINI_NUM_4>>4) + (USB_MINI_NUM_5>>5) + (USB_MINI_NUM_6>>6))
#else
#define USB_MINI_NUM_7    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_7 == TFAT_CTRL_USB_MINI)
#if (TFAT_DRIVE_ALLOC_NUM_8 == TFAT_CTRL_USB_MINI)
#define USB_MINI_NUM_8    (1<<8)
#define DRV8_DEV_CH  (0 + USB_MINI_NUM_0 + (USB_MINI_NUM_1>>1) + (USB_MINI_NUM_2>>2) + (USB_MINI_NUM_3>>3) + (USB_MINI_NUM_4>>4) + (USB_MINI_NUM_5>>5) + (USB_MINI_NUM_6>>6) + (USB_MINI_NUM_7>>7))
#else
#define USB_MINI_NUM_8    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_8 == TFAT_CTRL_USB_MINI)
#if (TFAT_DRIVE_ALLOC_NUM_9 == TFAT_CTRL_USB_MINI)
#define USB_MINI_NUM_9    (1<<9)
#define DRV9_DEV_CH  (0 + USB_MINI_NUM_0 + (USB_MINI_NUM_1>>1) + (USB_MINI_NUM_2>>2) + (USB_MINI_NUM_3>>3) + (USB_MINI_NUM_4>>4) + (USB_MINI_NUM_5>>5) + (USB_MINI_NUM_6>>6) + (USB_MINI_NUM_7>>7) + (USB_MINI_NUM_8>>8))
#else
#define USB_MINI_NUM_9    (0)
#endif // (TFAT_DRIVE_ALLOC_NUM_9 == TFAT_CTRL_USB_MINI)

static uint32_t TFAT_DRIVE_USB_MINI_ALLOC = (USB_MINI_NUM_9 | USB_MINI_NUM_8 | USB_MINI_NUM_7 | USB_MINI_NUM_6 | USB_MINI_NUM_5 | USB_MINI_NUM_4 | USB_MINI_NUM_3 | USB_MINI_NUM_2 | USB_MINI_NUM_1 | USB_MINI_NUM_0);

#if TFAT_USB_MINI_DRIVE_NUM != ( (USB_MINI_NUM_9>>9)+(USB_MINI_NUM_8>>8)+(USB_MINI_NUM_7>>7)+(USB_MINI_NUM_6>>6)+(USB_MINI_NUM_5>>5)+(USB_MINI_NUM_4>>4)+(USB_MINI_NUM_3>>3)+(USB_MINI_NUM_2>>2)+(USB_MINI_NUM_1>>1)+USB_MINI_NUM_0 )
#error "Error! Invalid setting for TFAT_USB_MINI_DRIVE_NUM or TFAT_DRIVE_ALLOC_NUM_x in r_tfat_driver_rx_config.h"
#endif

#endif // (TFAT_USB_MINI_DRIVE_NUM > 0)


#ifndef DRV0_DEV_CH
#define DRV0_DEV_CH  (0)
#endif
#ifndef DRV1_DEV_CH
#define DRV1_DEV_CH  (0)
#endif
#ifndef DRV2_DEV_CH
#define DRV2_DEV_CH  (0)
#endif
#ifndef DRV3_DEV_CH
#define DRV3_DEV_CH  (0)
#endif
#ifndef DRV4_DEV_CH
#define DRV4_DEV_CH  (0)
#endif
#ifndef DRV5_DEV_CH
#define DRV5_DEV_CH  (0)
#endif
#ifndef DRV6_DEV_CH
#define DRV6_DEV_CH  (0)
#endif
#ifndef DRV7_DEV_CH
#define DRV7_DEV_CH  (0)
#endif
#ifndef DRV8_DEV_CH
#define DRV8_DEV_CH  (0)
#endif
#ifndef DRV9_DEV_CH
#define DRV9_DEV_CH  (0)
#endif

#define TFAT_DRIVE_ALLOC_NUM_MAX    (TFAT_DRIVE_NUM_MAX)

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
*******************************************************************************/
static uint8_t drive_alloc_tbl[TFAT_DRIVE_ALLOC_NUM_MAX][2] =
{
    { TFAT_DRIVE_ALLOC_NUM_0, DRV0_DEV_CH },
    { TFAT_DRIVE_ALLOC_NUM_1, DRV1_DEV_CH },
    { TFAT_DRIVE_ALLOC_NUM_2, DRV2_DEV_CH },
    { TFAT_DRIVE_ALLOC_NUM_3, DRV3_DEV_CH },
    { TFAT_DRIVE_ALLOC_NUM_4, DRV4_DEV_CH },
    { TFAT_DRIVE_ALLOC_NUM_5, DRV5_DEV_CH },
    { TFAT_DRIVE_ALLOC_NUM_6, DRV6_DEV_CH },
    { TFAT_DRIVE_ALLOC_NUM_7, DRV7_DEV_CH },
    { TFAT_DRIVE_ALLOC_NUM_8, DRV8_DEV_CH },
    { TFAT_DRIVE_ALLOC_NUM_9, DRV9_DEV_CH },
};

/******************************************************************************
* Function Name : chk_use_usb
* Description   : allocation check
* Arguments     : uint8_t drive : Physical drive number for TFAT module
* Return value  : true : 0x01
******************************************************************************/
#if (TFAT_USB_DRIVE_NUM > 0)
static uint8_t chk_use_usb(uint8_t drive)
{
    return ( ( (TFAT_DRIVE_USB_ALLOC & (0x01 << drive) ) != 0) ?  0x01 : 0x00);
}
#endif // USE_USB

/******************************************************************************
* Function Name : chk_use_sdmem
* Description   : allocation check
* Arguments     : uint8_t drive : Physical drive number for TFAT module
* Return value  : true : 0x01
******************************************************************************/
#if (TFAT_SDMEM_DRIVE_NUM > 0)
static uint8_t chk_use_sdmem(uint8_t drive)
{
    return ( ( (TFAT_DRIVE_SDMEM_ALLOC & (0x01 << drive) ) != 0) ?  0x01 : 0x00);
}
#endif // USE_SDMEM

/******************************************************************************
* Function Name : chk_use_mmc
* Description   : allocation check
* Arguments     : uint8_t drive : Physical drive number for TFAT module
* Return value  : true : 0x01
******************************************************************************/
#if TFAT_MMC_DRIVE_NUM > 0
static uint8_t chk_use_mmc(uint8_t drive)
{
    return ( ( (TFAT_DRIVE_MMC_ALLOC & (0x01 << drive) ) != 0) ?  0x01 : 0x00);
}
#endif // USE_MMC

/******************************************************************************
* Function Name : chk_use_usb_mini
* Description   : allocation check
* Arguments     : uint8_t drive : Physical drive number for TFAT module
* Return value  : true : 0x01
******************************************************************************/
#if (TFAT_USB_MINI_DRIVE_NUM > 0)
static uint8_t chk_use_usb_mini(uint8_t drive)
{
    return ( ( (TFAT_DRIVE_USB_MINI_ALLOC & (0x01 << drive) ) != 0) ?  0x01 : 0x00);
}
#endif // USE_USB

/******************************************************************************
* Function Name : R_tfat_disk_initialize
* Description   : This function initializes the memory medium
*               :    for file operations
* Arguments     : uint8_t  drive        : Physical drive number for FIT module
* Return value  : Status of the memory medium
******************************************************************************/
DSTATUS R_tfat_disk_initialize(uint8_t drive)
{
    DSTATUS ret = TFAT_RES_PARERR;

#if (TFAT_USB_DRIVE_NUM > 0)
    if ( chk_use_usb(drive) )
    {
        ret = R_tfat_usb_disk_initialize( drive_alloc_tbl[drive][1] ); /* function for USB */
    }
#endif

#if (TFAT_SDMEM_DRIVE_NUM > 0)
    if ( chk_use_sdmem(drive) )
    {
        ret = R_tfat_sdmem_disk_initialize( drive_alloc_tbl[drive][1] ); /* function for SDMEM */
    }
#endif

#if (TFAT_USB_MINI_DRIVE_NUM > 0)
    if ( chk_use_usb_mini(drive) )
    {
        ret = R_tfat_usb_mini_disk_initialize( drive_alloc_tbl[drive][1] ); /* function for USB Mini */
    }
#endif

    return  ret;
}

/******************************************************************************
* Function Name : R_tfat_disk_read
* Description   : This function reads data from the specified location
*               :    of the memory medium
* Arguments     : uint8_t  drive        : Physical drive number
*               : uint8_t* buffer       : Pointer to the read data buffer
*               : uint32_t sector_number : uint32_t SectorNumber
*               : uint8_t sector_count   : Number of sectors to read
* Return value  : Result of function execution
******************************************************************************/
DRESULT R_tfat_disk_read (
    uint8_t drive,          /* Physical drive number             */
    uint8_t* buffer,        /* Pointer to the read data buffer   */
    uint32_t sector_number, /* Start sector number               */
    uint8_t sector_count    /* Number of sectors to read         */
)
{
    DRESULT ret = TFAT_RES_PARERR;

#if (TFAT_USB_DRIVE_NUM > 0)
    if ( chk_use_usb(drive) )
    {
        ret = R_tfat_usb_disk_read( drive_alloc_tbl[drive][1], buffer, sector_number, sector_count ); /* function for USB */
    }
#endif

#if (TFAT_SDMEM_DRIVE_NUM > 0)
    if ( chk_use_sdmem(drive) )
    {
        ret = R_tfat_sdmem_disk_read( drive_alloc_tbl[drive][1], buffer, sector_number, sector_count ); /* function for SDMEM */
    }
#endif

#if (TFAT_USB_MINI_DRIVE_NUM > 0)
    if ( chk_use_usb_mini(drive) )
    {
        ret = R_tfat_usb_mini_disk_read( drive_alloc_tbl[drive][1], buffer, sector_number, sector_count ); /* function for USB Mini */
    }
#endif

    return ret;
}

/******************************************************************************
* Function Name : R_tfat_disk_write
* Description   : This function writes data to a specified location
*               :    of the memory medium
* Arguments     : uint8_t Drive : Physical drive number
*               : const uint8_t* buffer       : Pointer to the write data
*               : uint32_t       sector_number : Sector number to write
*               : uint8_t        sector_count  : Number of sectors to write
* Return value  : Result of function execution
******************************************************************************/
DRESULT R_tfat_disk_write (
    uint8_t drive,           /* Physical drive number           */
    const uint8_t* buffer,   /* Pointer to the write data       */
    uint32_t sector_number,  /* Sector number to write          */
    uint8_t sector_count     /* Number of sectors to write      */
)
{
    DRESULT ret = TFAT_RES_PARERR;

#if (TFAT_USB_DRIVE_NUM > 0)
    if ( chk_use_usb(drive) )
    {
        ret = R_tfat_usb_disk_write( drive_alloc_tbl[drive][1], buffer, sector_number, sector_count ); /* function for USB */
    }
#endif

#if (TFAT_SDMEM_DRIVE_NUM > 0)
    if ( chk_use_sdmem(drive) )
    {
        ret = R_tfat_sdmem_disk_write( drive_alloc_tbl[drive][1], buffer, sector_number, sector_count ); /* function for SDMEM */
    }
#endif

#if (TFAT_USB_MINI_DRIVE_NUM > 0)
    if ( chk_use_usb_mini(drive) )
    {
        ret = R_tfat_usb_mini_disk_write( drive_alloc_tbl[drive][1], buffer, sector_number, sector_count ); /* function for USB Mini */
    }
#endif

    return ret;
}

/******************************************************************************
* Function Name : R_tfat_disk_ioctl
* Description   : This function is used to execute memory operations
*               :    other than read\write
* Arguments     : uint8_t drive   : Drive number
*               : uint8_t command : Control command code
*               : void*   buffer  : Data transfer buffer
* Return value  : Result of function execution
******************************************************************************/
DRESULT R_tfat_disk_ioctl (
    uint8_t drive,           /* Drive number             */
    uint8_t command,         /* Control command code     */
    void* buffer             /* Data transfer buffer     */
)
{
    DRESULT ret = TFAT_RES_PARERR;

#if (TFAT_USB_DRIVE_NUM > 0)
    if ( chk_use_usb(drive) )
    {
        ret = R_tfat_usb_disk_ioctl( drive_alloc_tbl[drive][1], command, buffer ); /* function for USB */
    }
#endif

#if (TFAT_SDMEM_DRIVE_NUM > 0)
    if ( chk_use_sdmem(drive) )
    {
        ret = R_tfat_sdmem_disk_ioctl ( drive_alloc_tbl[drive][1], command, buffer ); /* function for SDMEM */
    }
#endif

#if (TFAT_USB_MINI_DRIVE_NUM > 0)
    if ( chk_use_usb_mini(drive) )
    {
        ret = R_tfat_usb_mini_disk_ioctl( drive_alloc_tbl[drive][1], command, buffer ); /* function for USB Mini */
    }
#endif

    return ret;
}

/******************************************************************************
* Function Name : R_tfat_disk_status
* Description   : This function is used to retrieve the current status
*               :    of the disk
* Arguments     : uint8_t drive : Physical drive number
* Return value  : Status of the disk
******************************************************************************/
DSTATUS R_tfat_disk_status (
    uint8_t drive             /* Physical drive number    */
)
{
    DSTATUS ret = TFAT_RES_PARERR;

#if (TFAT_USB_DRIVE_NUM > 0)
    if ( chk_use_usb(drive) )
    {
        ret = R_tfat_usb_disk_status ( drive_alloc_tbl[drive][1] ); /* function for USB */
    }
#endif

#if (TFAT_SDMEM_DRIVE_NUM > 0)
    if ( chk_use_sdmem(drive) )
    {
        ret = R_tfat_sdmem_disk_status ( drive_alloc_tbl[drive][1] ); /* function for SDMEM */
    }
#endif

#if (TFAT_USB_MINI_DRIVE_NUM > 0)
    if ( chk_use_usb_mini(drive) )
    {
        ret = R_tfat_usb_mini_disk_status ( drive_alloc_tbl[drive][1] ); /* function for USB Mini */
    }
#endif

    return ret;
}

/******************************************************************************
* Function Name : R_tfat_get_fattime
* Description   : This function returns the current date and time
* Arguments     : none
* Return value  : uint32_t
* NOTE          : Please DO NOT modify this function. This function
*               :    is used by the FAT library to get the current date
                :    and time during file manipulations.
******************************************************************************/
uint32_t R_tfat_get_fattime (void)
{
    uint32_t tmr;
    SYS_TIME time;

    /* Disable interrupts   */
    R_BSP_InterruptsDisable();

    R_SYS_TIME_GetCurrentTime(&time);

    /* Convert the time to store in FAT entry   */
    tmr =   (((uint32_t)time.year - 60) << 25);
    tmr |=  ((uint32_t)time.month << 21);
    tmr |=  ((uint32_t)time.day << 16);
    tmr |=  ((uint32_t)time.hour << 11);
    tmr |=  ((uint32_t)time.min << 5);
    tmr |=  ((uint32_t)time.sec >> 1);
    /* Enable interrupts    */
    R_BSP_InterruptsEnable();

    return tmr;
}

/******************************************************************************
* Function Name : R_tfat_drv_change_alloc
* Description   : This function is used to change drive allocation.
*               :    of the disk
* Arguments     : TFAT_DRV_NUM      tfat_drv : Physical drive number( in TFAT)
*               : uint8_t dev_type           : device define
*               : uint8_t dev_drv_num        : drive number/device channnel( in device driver)
* Return value  : Result of function execution
******************************************************************************/
DRESULT R_tfat_drv_change_alloc(TFAT_DRV_NUM tfat_drv, uint8_t dev_type, uint8_t dev_drv_num )
{
    if ( TFAT_DRIVE_ALLOC_NUM_MAX <= tfat_drv )
    {
        return TFAT_RES_ERROR;
    }

#if (TFAT_USB_DRIVE_NUM > 0)
    if ( TFAT_CTRL_USB == dev_type )
    {
        TFAT_DRIVE_USB_ALLOC |= (0x01 << tfat_drv);
    }
    else
    {
        TFAT_DRIVE_USB_ALLOC &= ~(0x01 << tfat_drv);
    }
#endif
#if (TFAT_SDMEM_DRIVE_NUM > 0)
    if ( TFAT_CTRL_SDMEM == dev_type )
    {
        TFAT_DRIVE_SDMEM_ALLOC |= (0x01 << tfat_drv);
    }
    else
    {
        TFAT_DRIVE_SDMEM_ALLOC &= ~(0x01 << tfat_drv);
    }
#endif
#if (TFAT_MMC_DRIVE_NUM > 0)
    if ( TFAT_CTRL_MMC == dev_type )
    {
        TFAT_DRIVE_MMC_ALLOC |= (0x01 << tfat_drv);
    }
    else
    {
        TFAT_DRIVE_MMC_ALLOC &= ~(0x01 << tfat_drv);
    }
#endif
#if (TFAT_USB_MINI_DRIVE_NUM > 0)
    if ( TFAT_CTRL_USB_MINI == dev_type )
    {
        TFAT_DRIVE_USB_MINI_ALLOC |= (0x01 << tfat_drv);
    }
    else
    {
        TFAT_DRIVE_USB_MINI_ALLOC &= ~(0x01 << tfat_drv);
    }
#endif

    drive_alloc_tbl[tfat_drv][0] = dev_type;
    drive_alloc_tbl[tfat_drv][1] = dev_drv_num;

    return TFAT_RES_OK;
}

/*******************************************************************************
End  of file
*******************************************************************************/
