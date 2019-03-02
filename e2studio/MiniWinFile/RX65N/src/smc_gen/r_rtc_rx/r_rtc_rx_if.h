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
* Copyright (C) 2013-2017 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_rtc_rx_if.h
* Description  : API Interface for the Real Time Clock (RTC) peripheral on RX MCUs.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           09.09.2013 1.00    First release.
*           16.04.2014 2.00    Updated for new API.
*           03.09.2014 2.10    Added support for RX64M.
*           03.12.2014 2.20    Added support for RX113.
*           22.01.2015 2.30    Added support for RX71M.
*           06.07.2015 2.40    Added support for RX231.
*           01.03.2016 2.41    Added support for RX130.
*                              Added support for RX230.
*           01.10.2016 2.50    Added support for RX65N
*           31.07.2017 2.70    Added support for RX65N-2MB and RX130-512KB.
*                              Removed support for RX210 and RX63N/631.
*                              Removed definitions related to RX210, RX63N/631
*                              from conditional expressions of preprocessor.
*           20.09.2017 2.71    Fixed issue that an incorrect time is read out when a carry of the RTC counter occurs
*                              while reading the current time.
*                              Fixed issue that count stop occurred at warm start.
*                              - Update the minor version of RTC FIT module.
*           11.12.2017 2.72    Update the version of RTC FIT module.
*           03.12.2018 2.73    Changed Minor version to '73' for update of xml file.
***********************************************************************************************************************/

#ifndef RTC_RX_INTERFACE_HEADER_FILE
#define RTC_RX_INTERFACE_HEADER_FILE

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"
#include "r_rtc_rx_config.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Version Number of API. */
#define RTC_RX_VERSION_MAJOR        (2)
#define RTC_RX_VERSION_MINOR        (73)


/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/* R_RTC_Open() PARAMETERS */

typedef enum e_rtc_output
{
    RTC_OUTPUT_OFF,
    RTC_OUTPUT_1_HZ,
    RTC_OUTPUT_64_HZ,
    RTC_OUTPUT_END_ENUM
} rtc_output_t;

typedef enum e_rtc_periodic
{
    RTC_PERIODIC_OFF    = 0,
    RTC_PERIODIC_256_HZ = 6,
    RTC_PERIODIC_128_HZ = 7,
    RTC_PERIODIC_64_HZ  = 8,
    RTC_PERIODIC_32_HZ  = 9,
    RTC_PERIODIC_16_HZ  = 10,
    RTC_PERIODIC_8_HZ   = 11,
    RTC_PERIODIC_4_HZ   = 12,
    RTC_PERIODIC_2_HZ   = 13,
    RTC_PERIODIC_1_HZ   = 14,
    RTC_PERIODIC_2_SEC  = 15,
} rtc_periodic_t;

typedef void (*rtc_cb_func_t)(void *p_args);

typedef struct
{
    rtc_cb_func_t   p_callback;         // For alarm and periodic interrupts
    rtc_output_t    output_freq;
    rtc_periodic_t  periodic_freq;
    uint8_t         periodic_priority;  // INT priority; 0=disable. 1=low, 15=high
    bool            set_time;           // true if want time argument applied
} rtc_init_t;

/* If <time.h> is not included, or is not available in the compiler, the tm_t structure is duplicated here */
#if (!defined(_TIME_H) && !defined(__time_h__))
typedef struct
{
    int tm_sec;     /* Seconds (0-59) */
    int tm_min;     /* Minute (0-59) */
    int tm_hour;    /* Hour (0-23) */
    int tm_mday;    /* Day of the month (1-31) */
    int tm_mon;     /* Month (0-11, 0=January) */
    int tm_year;    /* Year since 1900 (100-199, 100=2000)*/
    int tm_wday;    /* Day of the week (0-6, 0=Sunday) */
    int tm_yday;    /* Day of the year (0-365) */
    int tm_isdst;   /* Daylight Savings enabled (>0), disabled (=0), or unknown (<0)*/
} tm_t;
#endif


/* CALLBACK EVENTS */

typedef enum
{
    RTC_EVT_ALARM,
    RTC_EVT_PERIODIC
} rtc_cb_evt_t;


/* R_RTC_Control() PARAMETERS */

/* commands */
typedef enum
{
    RTC_CMD_SET_OUTPUT,
    RTC_CMD_SET_PERIODIC,
    RTC_CMD_SET_CURRENT_TIME,
    RTC_CMD_SET_ALARM_TIME,
    RTC_CMD_ENABLE_ALARM,
    RTC_CMD_START_COUNTERS,
    RTC_CMD_STOP_COUNTERS,
    RTC_CMD_PARTIAL_RESET,          // primarily output clock, alarms and capture registers
#if !defined(BSP_MCU_RX11_ALL) && !defined(BSP_MCU_RX130)
    RTC_CMD_CONFIG_CAPTURE,         // configure capture pin; RX230, RX231, RX64M, RX65N, RX71M
    RTC_CMD_CHECK_PIN0_CAPTURE,     // see if capture event occurred; load time if yes
    RTC_CMD_CHECK_PIN1_CAPTURE,
    RTC_CMD_CHECK_PIN2_CAPTURE,
    RTC_CMD_DISABLE_CAPTURE,
#endif
    RTC_CMD_END_ENUM
} rtc_cmd_t;

/* for RTC_CMD_SET_PERIODIC */
typedef struct
{
    rtc_periodic_t  frequency;
    uint8_t         int_priority;   // INT priority; 0=disable, 1=low, 15=high
} rtc_periodic_cfg_t;

/* for RTC_CMD_ENABLE_ALARM */
typedef struct
{
    uint8_t     int_priority;       // INT priority; 0=disable, 1=low, 15=high

    /* set to true to cause alarm when all enabled alarm fields match current time */
    bool        sec;
    bool        min;
    bool        hour;
    bool        wday;
    bool        mday;
    bool        mon;
    bool        year;
} rtc_alarm_ctrl_t;

/* for RTC_CMD_CONFIG_CAPTURE */
typedef enum
{
    RTC_PIN_0 = 0,
    RTC_PIN_1 = 1,
    RTC_PIN_2 = 2,
    RTC_NUM_PINS = 3
} rtc_pin_t;

typedef enum
{
    RTC_EDGE_OFF = 0,
    RTC_EDGE_RISING = 1,
    RTC_EDGE_FALLING = 2,
    RTC_EDGE_BOTH = 3,
    RTC_EDGE_END_ENUM
} rtc_edge_t;

typedef enum
{
    RTC_FILTER_OFF = 0,
    RTC_FILTER_DIV1 = 2,
    RTC_FILTER_DIV32 = 3
} rtc_filter_t;

typedef struct
{
    rtc_pin_t       pin;
    rtc_edge_t      edge;
    rtc_filter_t    filter;     // noise filter
} rtc_capture_cfg_t;


/* RTC API ERROR/RETURN CODES */

typedef enum
{
    RTC_SUCCESS = 0,
    RTC_ERR_ALREADY_OPEN,      // Multiple calls to Open
    RTC_ERR_NOT_OPENED,        // Open not called
    RTC_ERR_BAD_PARAM,         // Missing or invalid parameter specified
    RTC_ERR_MISSING_CALLBACK,  // No callback function and Periodic or Alarm INTs requested
    RTC_ERR_TIME_FORMAT,       // Improper time format (field out of range)
    RTC_ERR_NO_CAPTURE         // Capture event did not occur
}rtc_err_t;


/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
rtc_err_t R_RTC_Open (rtc_init_t * p_init, tm_t *p_current_time);
rtc_err_t R_RTC_Control (rtc_cmd_t cmd, void *p_args);
rtc_err_t R_RTC_Read (tm_t *p_current_time, tm_t *p_alarm_time);
void      R_RTC_Close (void);
uint32_t  R_RTC_GetVersion (void);

#endif /* RTC_RX_INTERFACE_HEADER_FILE */
