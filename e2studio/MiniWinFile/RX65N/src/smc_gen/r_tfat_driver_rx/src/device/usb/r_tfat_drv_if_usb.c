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
* Copyright (C) 2014(2015) Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name    : r_tfat_drv_if_usb.c
* Description  : TFAT driver Interface for USB.
*******************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 01.12.2014 1.00     First Release
*              : 22.06.2015 1.02     Added support MCU RX231.
*              : 01.04.2016 1.03     Updated the xml file.
*              : 30.09.2016 x.xx      Added support MCU RX65N.
*******************************************************************************/

/******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include "r_tfat_drv_if_dev.h"
#include "r_tfat_driver_rx_config.h"

#if (TFAT_USB_DRIVE_NUM > 0)

#include "r_usb_basic_if.h"
#include "r_tfat_lib.h"             /* TFAT define */
#include "r_usb_hmsc_if.h"          /* version info. */

/* version info. */
#ifndef USB_VERSION_MAJOR
#include "r_usb_if.h" /* version info. */
#endif
#ifndef RX_USB_HMSC_API_VERSION_MAJOR
#include "r_usb_hmsc.h" /* version info. */
#endif

#ifdef BSP_MCU_RX62N
#define TFAT_DRV_USB_API_TYPE2
//#define TFAT_DRV_USB_API_TYPE3  /* for USB v2.30 */
#else
#if (RX_USB_HMSC_API_VERSION_MAJOR == 1) && (RX_USB_HMSC_API_VERSION_MINOR == 00)
#define TFAT_DRV_USB_API_TYPE1
#elif (USB_VERSION_MAJOR == 1) && (USB_VERSION_MINOR <= 19) && (RX_USB_HMSC_API_VERSION_MAJOR == 1) && (RX_USB_HMSC_API_VERSION_MINOR <= 10)
#define TFAT_DRV_USB_API_TYPE2
#else
#define TFAT_DRV_USB_API_TYPE3
#endif
#endif

#if defined(TFAT_DRV_USB_API_TYPE1) || defined(TFAT_DRV_USB_API_TYPE2)
#include "r_usb_hatapi_define.h"    /* Peripheral ATAPI Device extern */
#include "r_usb_hmsc_extern.h"
#include "r_usb_hmsc_api.h"
#include "r_usb_hmsc_config.h"
#else


#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_hmsc.h"
#endif

#ifdef TFAT_DRV_USB_API_TYPE1

#define usb_hmsc_smp_drive2_addr    usb_hmsc_SmpDrive2Addr

#define R_USB_HmscStrgReadSector    R_usb_hmsc_StrgReadSector
#define USB_FALSE   USB_DETACHED
#define R_USB_HmscStrgWriteSector   R_usb_hmsc_StrgWriteSector
//#define USB_TRCV_MSG              R_USB_TRCV_MSG
#define USB_REL_BL                  R_USB_REL_BLK
#define usb_cstd_check_schedule     R_usb_cstd_CheckSchedule
#define usb_hstd_hcd_task           R_usb_hstd_HcdTask
#define usb_hstd_mgr_task           R_usb_hstd_MgrTask
#define usb_hhub_task               R_usb_hhub_Task
#define R_USB_HmscTask              usb_hmsc_Task
#define usb_cstd_scheduler          R_usb_cstd_Scheduler

typedef USB_UTR_t usb_utr_t;
typedef USB_MH_t usb_mh_t;
typedef USB_MSG_t usb_msg_t;
typedef USB_VP_INT usb_vp_int_t;

#elif defined(TFAT_DRV_USB_API_TYPE2)

#define usb_hmsc_smp_drive2_addr    usb_hmsc_SmpDrive2Addr

#define R_USB_HmscStrgReadSector    R_usb_hmsc_StrgReadSector
#define USB_FALSE   USB_DETACHED
#define R_USB_HmscStrgWriteSector   R_usb_hmsc_StrgWriteSector
//#define USB_TRCV_MSG                R_USB_TRCV_MSG
#define USB_REL_BL                  R_USB_REL_BLK
#define usb_cstd_check_schedule     R_usb_cstd_CheckSchedule
#define usb_hstd_hcd_task           R_usb_hstd_HcdTask
#define usb_hstd_mgr_task           R_usb_hstd_MgrTask
#define usb_hhub_task               R_usb_hhub_Task
#define R_USB_HmscTask              usb_hmsc_Task
#define usb_cstd_scheduler          R_usb_cstd_Scheduler

typedef USB_UTR_t usb_utr_t;
typedef USB_MH_t usb_mh_t;
typedef USB_MSG_t usb_msg_t;
typedef USB_VP_INT usb_vp_int_t;

#else /* TFAT_DRV_USB_API_TYPE3 */
extern void usb_hmsc_smp_drive2_addr (uint16_t side, usb_utr_t *devadr);
#endif

/*******************************************************************************
Macro definitions
*******************************************************************************/

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/

/******************************************************************************
Private global variables and functions
*******************************************************************************/
static void R_usb_hmsc_WaitLoop (void);
static uint16_t g_usb_hmsc_tfatSecSize = 512;

#ifdef TFAT_DRV_USB_API_TYPE1
usb_utr_t tfat_ptr;
#endif

/******************************************************************************
* Function Name : R_tfat_usb_disk_initialize
* Description   : This function initializes the memory medium
*               :    for file operations
* Arguments     : uint8_t  drive        : Physical drive number
* Return value  : Status of the memory medium
******************************************************************************/
DSTATUS R_tfat_usb_disk_initialize (uint8_t pdrv)
{
    return TFAT_RES_OK;
}

/******************************************************************************
* Function Name : R_tfat_usb_disk_read
* Description   : This function reads data from the specified location
*               :    of the memory medium
* Arguments     : uint8_t  drive        : Physical drive number
*               : uint8_t* buff         : Pointer to the read data buffer
*               : uint32_t sector_number : uint32_t SectorNumber
*               : uint8_t count         : Number of sectors to read
* Return value  : Result of function execution
******************************************************************************/
DRESULT R_tfat_usb_disk_read (
    uint8_t drive,              /* Physical drive number            */
    uint8_t* buff,              /* Pointer to the read data buffer  */
    uint32_t sector_number,     /* Start sector number              */
    uint8_t count               /* Number of sectors to read        */
)
{
    uint16_t res[10];
    usb_utr_t *mess;
    uint16_t err;
    uint32_t tran_byte;
#ifndef TFAT_DRV_USB_API_TYPE1
    usb_utr_t tfat_ptr;
#endif

    /* set transfer length */
    tran_byte = (uint32_t) count * g_usb_hmsc_tfatSecSize;

#ifdef TFAT_DRV_USB_API_TYPE1
    usb_hmsc_smp_drive2_addr(drive);             /* Drive no. -> USB IP no. and IO Reg Base address */
#else
    usb_hmsc_smp_drive2_addr(drive, &tfat_ptr); /* Drive no. -> USB IP no. and IO Reg Base address */
#endif
    /* Check Detach */
#if defined(TFAT_DRV_USB_API_TYPE1) || defined(TFAT_DRV_USB_API_TYPE2)
    R_usb_hstd_DeviceInformation(&tfat_ptr, tfat_ptr.keyword, (uint16_t *)res);         /* Get device connect state */
    if ( USB_FALSE == res[1] )
#else
    if (USB_FALSE == R_USB_HmscGetDevSts(drive))
#endif
    {
        return TFAT_RES_ERROR;
    }

    /* read function */
    err = R_USB_HmscStrgReadSector(&tfat_ptr, (uint16_t) drive, buff, sector_number, (uint16_t) count, tran_byte);
    if ( USB_OK != err)
    {
        return TFAT_RES_ERROR;
    }

    /* Wait USB read sequence(READ10) */
    do
    {
        /* Check Detach */
#if defined(TFAT_DRV_USB_API_TYPE1) || defined(TFAT_DRV_USB_API_TYPE2)
        R_usb_hstd_DeviceInformation(&tfat_ptr, tfat_ptr.keyword, (uint16_t *)res); /* Get device connect state */
#else
        res[1] = R_USB_HmscGetDevSts(drive);
#endif
        R_usb_hmsc_WaitLoop(); /* Task Schedule */
        err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t** ) & mess, (uint16_t )0); /* Receive read complete msg */
    }
    while ((err != USB_OK) && (res[1] != USB_FALSE));

    if (err == USB_OK)
    { /* Complete R_USB_HmscStrgReadSector() */
        err = mess->result; /* Set result for R_USB_HmscStrgReadSector() */
        USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t )mess);
    }
    else
    { /* Device detach */
        R_usb_hmsc_WaitLoop(); /* Task Schedule */
        err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t** ) & mess, (uint16_t )0); /* Receive read complete msg */
        if ( USB_OK == err)
        {
            USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t )mess);
        }
        err = USB_ERROR;
    }

    if (err != USB_OK)
    {
        return TFAT_RES_ERROR;
    }
    return TFAT_RES_OK;
}

/******************************************************************************
* Function Name : R_tfat_usb_disk_write
* Description   : This function writes data to a specified location
*               :    of the memory medium
* Arguments     : uint8_t Drive : Physical drive number
*               : const uint8_t* buffer       : Pointer to the write data
*               : uint32_t       sector_number : Sector number to write
*               : uint8_t        sector_count  : Number of sectors to write
* Return value  : Result of function execution
******************************************************************************/
DRESULT R_tfat_usb_disk_write (
    uint8_t drive,          /* Physical drive number           */
    const uint8_t* buff,    /* Pointer to the write data       */
    uint32_t sector,        /* Sector number to write          */
    uint8_t count           /* Number of sectors to write      */
)
{
    uint16_t res[10];
    usb_utr_t *mess;
    uint16_t err;
    uint32_t tran_byte;
#ifndef TFAT_DRV_USB_API_TYPE1
    usb_utr_t tfat_ptr;
#endif

    /* set transfer length */
    tran_byte = (uint32_t) count * g_usb_hmsc_tfatSecSize;
#ifdef TFAT_DRV_USB_API_TYPE1
    usb_hmsc_smp_drive2_addr(drive);             /* Drive no. -> USB IP no. and IO Reg Base address */
#else
    usb_hmsc_smp_drive2_addr(drive, &tfat_ptr); /* Drive no. -> USB IP no. and IO Reg Base address */
#endif

    /* Check Detach */
#if defined(TFAT_DRV_USB_API_TYPE1) || defined(TFAT_DRV_USB_API_TYPE2)
    R_usb_hstd_DeviceInformation(&tfat_ptr, tfat_ptr.keyword, (uint16_t *)res);         /* Get device connect state */
    if ( USB_FALSE == res[1] )
#else
    if (USB_FALSE == R_USB_HmscGetDevSts(drive))
#endif
    {
        return TFAT_RES_ERROR;
    }

    /* write function */
    err = R_USB_HmscStrgWriteSector(&tfat_ptr, (uint16_t) drive, (uint8_t *) buff, sector, (uint16_t) count,
                                    tran_byte);
    if ( USB_OK != err)
    {
        return TFAT_RES_ERROR;
    }

    /* Wait USB write sequence(WRITE10) */
    do
    {
        /* Check Detach */
#if defined(TFAT_DRV_USB_API_TYPE1) || defined(TFAT_DRV_USB_API_TYPE2)
        R_usb_hstd_DeviceInformation(&tfat_ptr, tfat_ptr.keyword, (uint16_t *)res); /* Get device connect state */
#else
        res[1] = R_USB_HmscGetDevSts(drive);
#endif
        R_usb_hmsc_WaitLoop(); /* Task Schedule */
        err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t** ) & mess, (uint16_t )0); /* Receive write complete msg */
    }
    while ((err != USB_OK) && (res[1] != USB_FALSE));

    if ( USB_OK == err)
    { /* Complete R_USB_HmscStrgWriteSector() */
        err = mess->result; /* Set result for R_USB_HmscStrgWriteSector() */
        USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t )mess);
    }
    else
    { /* Device detach */
        R_usb_hmsc_WaitLoop(); /* Task Schedule */
        err = USB_TRCV_MSG(USB_HSTRG_MBX, (usb_msg_t** ) & mess, (uint16_t )0); /* Receive write complete msg */
        if (err == USB_OK)
        {
            USB_REL_BLK(USB_HSTRG_MPL, (usb_mh_t )mess);
        }
        err = USB_ERROR;
    }

    if (err != USB_OK)
    {
        return TFAT_RES_ERROR;
    }
    return TFAT_RES_OK;
}

/******************************************************************************
* Function Name : R_tfat_usb_disk_ioctl
* Description   : This function is used to execute memory operations
*               :    other than read\write
* Arguments     : uint8_t drive   : Drive number
*               : uint8_t command : Control command code
*               : void*   buffer  : Data transfer buffer
* Return value  : Result of function execution
******************************************************************************/
DRESULT R_tfat_usb_disk_ioctl (
    uint8_t drive,          /* Drive number             */
    uint8_t command,        /* Control command code     */
    void* buffer            /* Data transfer buffer     */
)
{

    /*  Please put the code for R_tfat_disk_ioctl driver interface
     function over here.  */
    /*  Please refer the application note for details.  */
    return TFAT_RES_OK;
}

/******************************************************************************
* Function Name : R_tfat_usb_disk_status
* Description   : This function is used to retrieve the current status
*               :    of the disk
* Arguments     : uint8_t drive : Physical drive number
* Return value  : Status of the disk
******************************************************************************/
DSTATUS R_tfat_usb_disk_status (uint8_t drive /* Physical drive number    */
                               )
{
    /*  Please put the code for R_tfat_disk_status driver interface
     function over here.  */
    /*  Please refer the application note for details.  */
    return TFAT_RES_OK;
}

/******************************************************************************
Function Name   : R_usb_hmsc_WaitLoop
Description     : Hmsc wait loop function
Arguments       : none
Return value    : none
******************************************************************************/
void R_usb_hmsc_WaitLoop (void)
{
    if (usb_cstd_check_schedule() == USB_FLGSET)
    {
        usb_hstd_hcd_task((usb_vp_int_t) 0);
        usb_hstd_mgr_task((usb_vp_int_t) 0);
        usb_hhub_task((usb_vp_int_t) 0);
        R_USB_HmscTask(); /* HMSC Task */
    }
    usb_cstd_scheduler();
}

#endif // (TFAT_USB_DRIVE_NUM > 0)
/******************************************************************************
End  of file
******************************************************************************/
