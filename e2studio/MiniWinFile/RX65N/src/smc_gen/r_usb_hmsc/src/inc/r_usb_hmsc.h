/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2014(2018) Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_usb_hmsc.h
 * Description  : USB Host MSC header file
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 26.01.2017 1.21 USB_HMSC_STRG_SECTSIZE is added.
 *         : 30.09.2017 1.22 Add HMSC driver use API functions.
 *         : 31.03.2018 1.23 Supporting Smart Configurator 
 ***********************************************************************************************************************/

#ifndef R_USB_HMSC_LOCAL_H
#define R_USB_HMSC_LOCAL_H

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_typedef.h"      /* type define */

/*****************************************************************************
 Macro definitions
 ******************************************************************************/
/* Host Sample Task */
#define USB_HMSC_TSK        (USB_TID_6)           /* Task ID */
#define USB_HMSC_MBX        (USB_HMSC_TSK)        /* Mailbox ID */
#define USB_HMSC_MPL        (USB_HMSC_TSK)        /* Memorypool ID */

/* Host Sample Task */
#define USB_HSTRG_TSK       (USB_TID_7)           /* Task ID */
#define USB_HSTRG_MBX       (USB_HSTRG_TSK)       /* Mailbox ID */
#define USB_HSTRG_MPL       (USB_HSTRG_TSK)       /* Memorypool ID */

//#define USB_HMSC_REQ_MBX    (USB_TID_8)
#define USB_HMSC_REQ_MBX    (USB_TID_7)

#define USB_MAXSTRAGE       (4)

/* CBW definitions */
#define     USB_MSC_CBWLENGTH       (31)
#define     USB_MSC_CBWCB_LENGTH    (12)

/* CPU bit endian select (BIT_LITTLE:little, BIT_BIG:big) */
#if USB_CFG_ENDIAN == USB_CFG_BIG
#define    USB_MSC_CBW_SIGNATURE   ((uint32_t)0x55534243)
#else   /* USB_CFG_ENDIAN == USB_CFG_BIG */
#define    USB_MSC_CBW_SIGNATURE   ((uint32_t)0x43425355)
#endif  /* USB_CFG_ENDIAN == USB_CFG_BIG */

/* CSW definitions */
#define     USB_MSC_CSW_LENGTH      (13)
/* CPU bit endian select (BIT_LITTLE:little, BIT_BIG:big) */
#if USB_CFG_ENDIAN == USB_CFG_BIG
#define    USB_MSC_CSW_SIGNATURE   ((uint32_t)0x55534253)
#else   /* USB_CFG_ENDIAN == USB_CFG_BIG */
#define    USB_MSC_CSW_SIGNATURE   ((uint32_t)0x53425355)
#endif  /* USB_CFG_ENDIAN == USB_CFG_BIG */

/* subClass code */
#define USB_ATAPI_MMC5                      ((uint8_t)0x02)
#define USB_ATAPI                           ((uint8_t)0x05)
#define USB_SCSI                            ((uint8_t)0x06)

/* Protocol code */
#define USB_BOTP                            ((uint8_t)0x50)

/* Message code */
#define USB_MSG_HMSC_NO_DATA                ((uint16_t)0x501)
#define USB_MSG_HMSC_DATA_IN                ((uint16_t)0x502)
#define USB_MSG_HMSC_DATA_OUT               ((uint16_t)0x503)
#define USB_MSG_HMSC_CSW_PHASE_ERR          ((uint16_t)0x505)
#define USB_MSG_HMSC_CBW_ERR                ((uint16_t)0x506)

#define USB_MSG_HMSC_STRG_DRIVE_SEARCH      ((uint16_t)0x601)
#define USB_MSG_HMSC_STRG_DRIVE_SEARCH_END  ((uint16_t)0x602)
#define USB_MSG_HMSC_STRG_USER_COMMAND      ((uint16_t)0x605)
#define USB_MSG_HMSC_STRG_RW_END            ((uint16_t)0x606)

/* Class Request Buffer Size */
#define USB_HMSC_CLSDATASIZE                (256)
#define USB_HMSC_STRG_SECTSIZE              (512) /* 512 bytes per sector */

#define R_usb_hmsc_ref_drv_no  usb_hmsc_ref_drvno
#define R_USB_HmscGetDevSts    usb_hmsc_get_dev_sts

/*****************************************************************************
 Typedef definitions
 ******************************************************************************/

typedef struct
{
    uint8_t reserved7 :7;
    uint8_t cbw_dir :1;
} usb_msc_bm_cbw_flags_t;

typedef struct
{
    uint8_t bcbw_lun :4;
    uint8_t reserved4 :4;
} usb_msc_bcbw_lun_t;

typedef struct
{
    uint8_t bcbwcb_length :5;
    uint8_t reserved3 :3;
} usb_msc_bcbwcb_length_t;

/* CBW Structure define.    */
typedef struct
{
    uint32_t                    dcbw_signature;
    uint32_t                    dcbw_tag;
    uint8_t                     dcbw_dtl_lo;
    uint8_t                     dcbw_dtl_ml;
    uint8_t                     dcbw_dtl_mh;
    uint8_t                     dcbw_dtl_hi;
    usb_msc_bm_cbw_flags_t      bm_cbw_flags;
    usb_msc_bcbw_lun_t          bcbw_lun;
    usb_msc_bcbwcb_length_t     bcbwcb_length;

    /* uint8_t cbwcb[(16 + (64 - 31))];  : DTC Receive Size dummy (MAX Packet size = 64Byte)
       uint8_t cbwcb[(16 + (512 - 31))]; : DTC Receive Size dummy (MAX Packet size = 512Byte) */
/*    uint8_t    cbwcb[(16 + (64 - 31))];*/
    uint8_t    cbwcb[(16 + (512 - 31))];
} usb_msc_cbw_t;

/* CSW Structure define define. */
typedef struct
{
    uint32_t dcsw_signature;
    uint32_t dcsw_tag;
    uint8_t  dcsw_data_residue_lo;
    uint8_t  dcsw_data_residue_ml;
    uint8_t  dcsw_data_residue_mh;
    uint8_t  dcsw_data_residue_hi;
    uint8_t  dcsw_status;

    /* uint8_t  dummy[(64 - 13)];      DTC Receive Size dummy (MAX Packet size = 64Byte)
     * uint8_t  dummy[(512-13)];         DTC Receive Size dummy (MAX Packet size = 512Byte) */
/*    uint8_t  dummy[(64 - 13)];*/
    uint8_t  dummy[(512 - 13)];
} usb_msc_csw_t;

/* Structure for DRIVE No. */
typedef struct
{
    uint16_t use_flag; /* USE flag */
    uint16_t ip; /* IP No. */
    uint16_t devadr; /* Device address */
} drive_management_t;

/* ERROR CODE */
typedef enum
{
    USB_HMSC_OK            = (uint16_t) 0,
    USB_HMSC_STALL         = (uint16_t) -1,
    USB_HMSC_CBW_ERR       = (uint16_t) -2, /* CBW error */
    USB_HMSC_DAT_RD_ERR    = (uint16_t) -3, /* Data IN error */
    USB_HMSC_DAT_WR_ERR    = (uint16_t) -4, /* Data OUT error */
    USB_HMSC_CSW_ERR       = (uint16_t) -5, /* CSW error */
    USB_HMSC_CSW_PHASE_ERR = (uint16_t) -6, /* Phase error */
    USB_HMSC_SUBMIT_ERR    = (uint16_t) -7, /* Submit error */
}g_usb_hmsc_error_t;

/* CSW STATUS */
typedef enum
{
    USB_MSC_CSW_OK = (uint16_t) 0x00, USB_MSC_CSW_NG = (uint16_t) 0x01, USB_MSC_CSW_PHASE_ERR = (uint16_t) 0x02
}usb_gcmsc_cswsts_t;


/*****************************************************************************
 Private global variables and functions
 ******************************************************************************/
/* HMSC driver */
extern usb_utr_t g_usb_hmsc_class_control[USB_NUM_USBIP];
extern uint8_t g_usb_hmsc_class_data[USB_NUM_USBIP][USB_HMSC_CLSDATASIZE];
extern drive_management_t g_usb_hmsc_drvno_tbl[USB_MAXSTRAGE];
extern uint16_t g_usb_hmsc_in_pipe[USB_NUM_USBIP][USB_MAXSTRAGE];
extern uint16_t g_usb_hmsc_out_pipe[USB_NUM_USBIP][USB_MAXSTRAGE];
extern usb_msc_cbw_t g_usb_hmsc_cbw[USB_NUM_USBIP][USB_MAXSTRAGE];
extern usb_msc_csw_t g_usb_hmsc_csw[USB_NUM_USBIP][USB_MAXSTRAGE];
extern uint32_t g_usb_hmsc_csw_tag_no[USB_NUM_USBIP][USB_MAXSTRAGE];
extern uint8_t g_usb_hmsc_sub_class[USB_NUM_USBIP][USB_MAXSTRAGE];
extern uint8_t g_usb_hmsc_tmp_sub_class[USB_NUM_USBIP];
extern uint8_t *g_p_usb_hmsc_device_table[USB_NUM_USBIP];
extern uint8_t *g_p_usb_hmsc_config_table[USB_NUM_USBIP];
extern uint8_t *g_p_usb_hmsc_interface_table[USB_NUM_USBIP];
extern uint16_t g_usb_hmsc_devaddr[USB_NUM_USBIP];
extern uint16_t g_usb_hmsc_init_seq[USB_NUM_USBIP];

extern uint16_t g_usb_hmsc_speed[USB_NUM_USBIP];
extern uint16_t g_usb_hmsc_in_pipectr[USB_NUM_USBIP][USB_MAXSTRAGE];
extern uint16_t g_usb_hmsc_out_pipectr[USB_NUM_USBIP][USB_MAXSTRAGE];

/* Storage Driver */
extern uint16_t g_usb_hmsc_strg_process[USB_NUM_USBIP];
extern uint16_t g_usb_hmsc_drive_search_seq[USB_NUM_USBIP];

/*****************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/

uint16_t usb_hmsc_pipe_info (usb_utr_t *ptr, uint8_t *table, uint16_t msgnum, uint16_t speed, uint16_t length);

/* HMSC driver */
void usb_hmsc_task (void);
void usb_hmsc_set_els_cbw (usb_utr_t *ptr, uint8_t *data, uint32_t trans_byte, uint16_t side);
void usb_hmsc_set_rw_cbw (usb_utr_t *ptr, uint16_t command, uint32_t secno, uint16_t seccnt, uint32_t trans_byte,
        uint16_t side);
void usb_hmsc_clr_data (uint16_t len, uint8_t *buf);
uint16_t usb_hmsc_no_data (usb_utr_t *ptr, uint16_t side);
uint16_t usb_hmsc_data_in (usb_utr_t *ptr, uint16_t side, uint8_t *buff, uint32_t size);
uint16_t usb_hmsc_data_out (usb_utr_t *ptr, uint16_t side, uint8_t *buff, uint32_t size);

void usb_hmsc_smp_drive2_addr (uint16_t side, usb_utr_t *devadr);
void usb_hmsc_message_retry (uint16_t id, usb_utr_t *mess);

/* Storage Driver */
void usb_hmsc_strg_drive_search_act (usb_utr_t *mess);
void usb_hmsc_strg_specified_path (usb_utr_t *mess);
void usb_hmsc_strg_check_result (usb_utr_t *mess, uint16_t data1, uint16_t data2);

#if (BSP_CFG_RTOS_USED)
uint16_t usb_hmsc_get_string_info(usb_utr_t *mess, uint16_t addr, uint16_t string);
uint16_t usb_hmsc_trans_wait_tmo(uint16_t tmo);
void usb_hmsc_trans_result(usb_utr_t *mess, uint16_t data1, uint16_t data2);
uint16_t usb_hmsc_req_trans_wait_tmo(uint16_t tmo);
void usb_hmsc_req_trans_result(usb_utr_t *mess, uint16_t data1, uint16_t data2);
#endif /* (BSP_CFG_RTOS_USED) */

uint16_t usb_hmsc_strg_read_sector (usb_utr_t *ptr, uint16_t side, uint8_t *buff, uint32_t secno,
                                   uint16_t seccnt, uint32_t trans_byte);
uint16_t usb_hmsc_strg_write_sector (usb_utr_t *ptr, uint16_t side, uint8_t *buff, uint32_t secno,
                                   uint16_t seccnt, uint32_t trans_byte);
uint16_t usb_hmsc_get_dev_sts (uint16_t side);
uint16_t usb_hmsc_strg_user_command (usb_utr_t *ptr, uint16_t side, uint16_t command, uint8_t *buff,
                                    usb_cb_t complete);
uint16_t usb_hmsc_request_sense (usb_utr_t *ptr, uint16_t side, uint8_t *buff);
usb_er_t usb_hmsc_mass_storage_reset (usb_utr_t *ptr, uint16_t addr, usb_cb_t complete);
uint16_t usb_hmsc_strg_drive_open (usb_utr_t *ptr, uint16_t addr, uint16_t *side);
uint16_t usb_hmsc_strg_drive_close (usb_utr_t *ptr, uint16_t side);
uint16_t usb_hmsc_ref_drvno (uint16_t devadr);
usb_er_t usb_hmsc_get_max_unit (usb_utr_t *ptr, uint16_t addr, uint8_t *buff, usb_cb_t complete);
uint16_t usb_hmsc_inquiry (usb_utr_t *ptr, uint16_t side, uint8_t *buff);
uint16_t usb_hmsc_read_format_capacity (usb_utr_t *ptr, uint16_t side, uint8_t *buff);
uint16_t usb_hmsc_read_capacity (usb_utr_t *ptr, uint16_t side, uint8_t *buff);
uint16_t usb_hmsc_test_unit (usb_utr_t *ptr, uint16_t side);
uint16_t usb_hmsc_read10 (usb_utr_t *ptr, uint16_t side, uint8_t *buff, uint32_t secno, uint16_t seccnt,
                           uint32_t trans_byte);
void usb_hmsc_class_check (usb_utr_t *ptr, uint16_t **table);
uint16_t usb_hmsc_alloc_drvno (uint16_t devadr);
uint16_t usb_hmsc_free_drvno (uint16_t side);
uint16_t usb_hmsc_write10 (usb_utr_t *ptr, uint16_t side, uint8_t *buff, uint32_t secno, uint16_t seccnt,
                            uint32_t trans_byte);
uint16_t usb_hmsc_prevent_allow (usb_utr_t *ptr, uint16_t side, uint8_t *buff);
uint16_t usb_hmsc_mode_select10 (usb_utr_t *ptr, uint16_t side, uint8_t *buff);
uint16_t usb_hmsc_mode_sense10 (usb_utr_t *ptr, uint16_t side, uint8_t *buff);

#endif  /* R_USB_HMSC_LOCAL_H */
/******************************************************************************
 End  Of File
 ******************************************************************************/
