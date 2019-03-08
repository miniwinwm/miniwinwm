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
* Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/**********************************************************************************************************************
* File Name    : r_sys_time_rx_private.h
* Description  : Functions for using SYSTEM TIME on RX devices.
***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           30.11.2016 1.00    Initial Release.
***********************************************************************************************************************/

#ifndef SYS_TIME_PRIVATE_H
#define SYS_TIME_PRIVATE_H

/*****************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include "platform.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define SYS_TIME_SECOND_OF_MIN  (60UL)
#define SYS_TIME_SECOND_OF_HOUR (60UL*60UL)
#define SYS_TIME_SECOND_OF_DAY  (60UL*60UL*24UL)
#define SYS_TIME_SECOND_OF_YEAR (60UL*60UL*24UL*365UL)
#define SYS_TIME_SECOND_OF_LEAP_YEAR (60UL*60UL*24UL*366UL)

#define SYS_TIME_INTERVAL_LIMIT (600UL)
#define SYS_TIME_REGISTERED_PROCESS_LIMIT (30UL)

typedef struct time_offset_tbl
{
    uint8_t time_offset_code[16];
    int32_t offset;
} time_offset_tbl_t;

typedef struct proccess_list
{
    callback_from_sys_time_t function_pointer;
    uint8_t registered_flag;
    uint32_t interval;
    uint32_t interval_initial;
} process_list_t;

#if defined (_UNIT_TEST)
#define SYS_TIME_STATIC
#else
#define SYS_TIME_STATIC static
#endif

#endif /* SYS_TIME_PRIVATE_H */
