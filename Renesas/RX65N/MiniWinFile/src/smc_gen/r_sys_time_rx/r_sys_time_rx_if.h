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
* Copyright (C) 2013-2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_sys_time_rx_if.h
* Description  : Functions for using SYSTEM TIME on RX devices.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           25.09.2013 1.00    Initial Release
***********************************************************************************************************************/

#ifndef SYS_TIME_IF_H
#define SYS_TIME_IF_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Version Number of API. */
#define SYS_TIME_VERSION_MAJOR  (1)
#define SYS_TIME_VERSION_MINOR  (00)

#define SYS_TIME_UTC_MINUS_1200 "UTC-12:00"
#define SYS_TIME_UTC_MINUS_1100 "UTC-11:00"
#define SYS_TIME_UTC_MINUS_1000 "UTC-10:00"
#define SYS_TIME_UTC_MINUS_0930 "UTC-09:30"
#define SYS_TIME_UTC_MINUS_0900 "UTC-09:00"
#define SYS_TIME_UTC_MINUS_0800 "UTC-08:00"
#define SYS_TIME_UTC_MINUS_0700 "UTC-07:00"
#define SYS_TIME_UTC_MINUS_0600 "UTC-06:00"
#define SYS_TIME_UTC_MINUS_0500 "UTC-05:00"
#define SYS_TIME_UTC_MINUS_0400 "UTC-04:00"
#define SYS_TIME_UTC_MINUS_0330 "UTC-03:30"
#define SYS_TIME_UTC_MINUS_0300 "UTC-03:00"
#define SYS_TIME_UTC_MINUS_0200 "UTC-02:00"
#define SYS_TIME_UTC_MINUS_0100 "UTC-01:00"
#define SYS_TIME_UTC "UTC"
#define SYS_TIME_UTC_PLUS_0100 "UTC+01:00"
#define SYS_TIME_UTC_PLUS_0200 "UTC+02:00"
#define SYS_TIME_UTC_PLUS_0300 "UTC+03:00"
#define SYS_TIME_UTC_PLUS_0330 "UTC+03:30"
#define SYS_TIME_UTC_PLUS_0400 "UTC+04:00"
#define SYS_TIME_UTC_PLUS_0430 "UTC+04:30"
#define SYS_TIME_UTC_PLUS_0500 "UTC+05:00"
#define SYS_TIME_UTC_PLUS_0530 "UTC+05:30"
#define SYS_TIME_UTC_PLUS_0545 "UTC+05:45"
#define SYS_TIME_UTC_PLUS_0600 "UTC+06:00"
#define SYS_TIME_UTC_PLUS_0630 "UTC+06:30"
#define SYS_TIME_UTC_PLUS_0700 "UTC+07:00"
#define SYS_TIME_UTC_PLUS_0800 "UTC+08:00"
#define SYS_TIME_UTC_PLUS_0830 "UTC+08:30"
#define SYS_TIME_UTC_PLUS_0845 "UTC+08:45"
#define SYS_TIME_UTC_PLUS_0900 "UTC+09:00"
#define SYS_TIME_UTC_PLUS_0930 "UTC+09:30"
#define SYS_TIME_UTC_PLUS_1000 "UTC+10:00"
#define SYS_TIME_UTC_PLUS_1030 "UTC+10:30"
#define SYS_TIME_UTC_PLUS_1100 "UTC+11:00"
#define SYS_TIME_UTC_PLUS_1200 "UTC+12:00"
#define SYS_TIME_UTC_PLUS_1245 "UTC+12:45"
#define SYS_TIME_UTC_PLUS_1300 "UTC+13:00"
#define SYS_TIME_UTC_PLUS_1400 "UTC+14:00"

/*****************************************************************************
Typedef definitions
******************************************************************************/
typedef enum e_sys_time_err
{
    SYS_TIME_SUCCESS = 0,           /* Normally terminated. */
    SYS_TIME_BAD_CHANNEL,           /* Non-existent channel number. */
    SYS_TIME_BAD_INTERVAL,          /* Bad interval parameter is specified. */
    SYS_TIME_BAD_TIME_OFFSET,       /* Bad time offset is set. */
    SYS_TIME_BAD_FUNCTION_POINTER,  /* Bad function pointer is set. */
    SYS_TIME_BAD_SYS_TIME,          /* Bad system timer value is input */
    SYS_TIME_ALREADY_STARTED,       /* System timer is already started. */
    SYS_TIME_NOT_STARTED,           /* System timer is not started. */
    SYS_TIME_FULL_REGISTERED,       /* All register table is used. */
    SYS_TIME_ALREADY_REGISTERED,    /* Specified function pointer has been already registered. */
} sys_time_err_t;

typedef struct sys_time_
{
    uint32_t sec;
    uint32_t min;
    uint32_t hour;
    uint32_t day;
    uint32_t month;
    uint32_t year;
    uint32_t unix_time;
    uint8_t time_zone[16];
} SYS_TIME;

typedef void (*callback_from_sys_time_t)(void);

/*****************************************************************************
Public Functions
******************************************************************************/
sys_time_err_t R_SYS_TIME_Open(void);
sys_time_err_t R_SYS_TIME_GetCurrentTime(SYS_TIME *sys_time);
sys_time_err_t R_SYS_TIME_SetCurrentTime(SYS_TIME *sys_time);
sys_time_err_t R_SYS_TIME_ConvertUnixTimeToSystemTime(uint32_t unix_time, SYS_TIME *sys_time, uint8_t *time_offset);
sys_time_err_t R_SYS_TIME_RegisterPeriodicCallback(callback_from_sys_time_t function_pointer, uint32_t interval);
sys_time_err_t R_SYS_TIME_UnregisterPeriodicCallback(callback_from_sys_time_t function_pointer);
bool R_SYS_TIME_IsPeriodicCallbackRegistered(callback_from_sys_time_t function_pointer);
sys_time_err_t R_SYS_TIME_Close(void);
uint32_t R_SYS_TIME_GetVersion(void);

#endif /* SYS_TIME_IF_H */

