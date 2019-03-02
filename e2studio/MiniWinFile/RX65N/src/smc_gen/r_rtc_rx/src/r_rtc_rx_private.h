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
* File Name    : r_rtc_rx_private.h
* Description  : Internal definitions for the Real Time Clock (RTC) peripheral driver on RX MCUs.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           09.09.2013 1.00    First release.
*           16.04.2014 2.00    Updated for new API.
*           03.09.2014 2.10    Added support for RX64M.
*           03.12.2014 2.20    Added support for RX113.
*           22.01.2015 2.30    Added support for RX71M.
*           20.07.2015 2.40    Added support for RX231.
*           01.03.2016 2.41    Added support for RX130.
*                              Added support for RX230.
*                              Added the option of RTC_CFG_DRIVE_CAPACITY_MD for sub-clock drive capacity.
*                              Added the definition of RTC_CAPTURE_EDGE_MASK to mask the capture register.
*                              Added the rtc_enable_ints function.
*           01.10.2016 2.50    Added support for RX65N
*                              The specification has been changed as follows:
*                              Added the RTC_INT_ENABLE definition as a setting of the RCR1 register.
*                              When the following conditions are met, a build error occurs to notify the user.
*                              - RX63N or RX631 is selected as the target MCU.
*                              - More than two sub-clock drive capacity values are selected.
*           31.07.2017 2.70    Added support for RX65N-2MB and RX130-512KB.
*                              Removed support for RX210 and RX63N/631.
*                              Added definition of RTC_DUMMY_READ for dummy read processing after register setting.
*                              Fixed the contents of RTC_DRIVE_CAPACITY definition (removed the shift process).
*                              Changed return type of rtc_bcd_to_dec function from uint8_t type to int type.
*           20.09.2017 2.71    Fixed issue that an incorrect time is read out when a carry of the RTC counter occurs
*                              while reading the current time.
*                              - Changed the value of RTC_INT_ENABLE definition from 0x05 to 0x07.
*                                By this way, the carry interrupt enable bit (RCR1.CIE) becomes enabled,
*                                it detects the carry during reading of the current time and reads again.
***********************************************************************************************************************/

#ifndef R_RTC_PRIVATE_H
#define R_RTC_PRIVATE_H

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Need rtc_cb_func_t */
#include "r_rtc_rx_if.h"
#include "r_rtc_rx_config.h"


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define RTC_COUNTER_STOP        (0)
#define RTC_COUNTER_START       (1)

#define RTC_CAPTURE_ENABLE_MASK (0x80)
#define RTC_CAPTURE_EVENT_MASK  (0x04)
#define RTC_CAPTURE_EDGE_MASK   (0x03)

#define RTC_INT_ENABLE          (0x07)  /* Enable the AIE bit, the CIE bit and the PIE bit. */
                                        /* The carry interrupt (CIE bit) is used to read the current time. */
#define RTC_DUMMY_READ          (3)     /* Three times of dummy read */


#if !defined(RTC_CFG_DRIVE_CAPACITY_LO) && !defined(RTC_CFG_DRIVE_CAPACITY_MD) && !defined(RTC_CFG_DRIVE_CAPACITY_HI) && !defined(RTC_CFG_DRIVE_CAPACITY_STD)
    #error "ERROR - A drive capacity #define must be uncommented in r_rtc_rx_config.h"
#endif

#if defined(RTC_CFG_DRIVE_CAPACITY_LO) && defined(RTC_CFG_DRIVE_CAPACITY_STD)
    #error "ERROR - Only one drive capacity #define may be uncommented in r_rtc_rx_config.h"
#endif
#if defined(RTC_CFG_DRIVE_CAPACITY_LO) && defined(RTC_CFG_DRIVE_CAPACITY_HI)
    #error "ERROR - Only one drive capacity #define may be uncommented in r_rtc_rx_config.h"
#endif
#if defined(RTC_CFG_DRIVE_CAPACITY_LO) && defined(RTC_CFG_DRIVE_CAPACITY_MD)
    #error "ERROR - Only one drive capacity #define may be uncommented in r_rtc_rx_config.h"
#endif
#if defined(RTC_CFG_DRIVE_CAPACITY_HI) && defined(RTC_CFG_DRIVE_CAPACITY_STD)
    #error "ERROR - Only one drive capacity #define may be uncommented in r_rtc_rx_config.h"
#endif
#if defined(RTC_CFG_DRIVE_CAPACITY_HI) && defined(RTC_CFG_DRIVE_CAPACITY_MD)
    #error "ERROR - Only one drive capacity #define may be uncommented in r_rtc_rx_config.h"
#endif
#if defined(RTC_CFG_DRIVE_CAPACITY_MD) && defined(RTC_CFG_DRIVE_CAPACITY_STD)
    #error "ERROR - Only one drive capacity #define may be uncommented in r_rtc_rx_config.h"
#endif

#ifdef BSP_MCU_RX11_ALL
    #if defined(RTC_CFG_DRIVE_CAPACITY_LO)
        #define RTC_DRIVE_CAPACITY      (2)
    #elif defined(RTC_CFG_DRIVE_CAPACITY_MD)
        #define RTC_DRIVE_CAPACITY      (0)
    #elif defined(RTC_CFG_DRIVE_CAPACITY_HI)
        #define RTC_DRIVE_CAPACITY      (1)
    #elif defined(RTC_CFG_DRIVE_CAPACITY_STD)
        #define RTC_DRIVE_CAPACITY      (4)
    #endif
#else /* RX130, RX230, RX231, RX64M, RX65N, RX71M */
    #if defined(RTC_CFG_DRIVE_CAPACITY_LO)
        #define RTC_DRIVE_CAPACITY      (1)
    #elif defined(RTC_CFG_DRIVE_CAPACITY_STD)
        #define RTC_DRIVE_CAPACITY      (6)
    #elif defined(RTC_CFG_DRIVE_CAPACITY_MD)
        #error "ERROR - RTC_CFG_DRIVE_CAPACITY_MD in r_rtc_rx_config.h is invalid selection for MCU."
    #elif defined(RTC_CFG_DRIVE_CAPACITY_HI)
        #error "ERROR - RTC_CFG_DRIVE_CAPACITY_HI in r_rtc_rx_config.h is invalid selection for MCU."
    #endif
#endif


/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct            /* RTC Control Block */
{
    bool            initialized;
    rtc_cb_func_t   p_callback;
} rtc_ctrl_t;

typedef struct  /* maps to portion of st_rtc in iodefine.h */
{
    uint8_t     rtccr;
    uint8_t     pad;
} rtc_cap_ctrl_t;

typedef struct  /* maps to portion of st_rtc in iodefine.h */
{
    uint8_t     rseccp;
    uint8_t     pad_a;
    uint8_t     rmincp;
    uint8_t     pad_b;
    uint8_t     rhrcp;
    uint8_t     pad_c[3];
    uint8_t     rdaycp;
    uint8_t     pad_d;
    uint8_t     rmoncp;
    uint8_t     pad_e[5];
} rtc_cap_time_t;


/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/

#if !defined(BSP_MCU_RX11_ALL) && !defined(BSP_MCU_RX130)
extern volatile rtc_cap_ctrl_t  *g_pcap_ctrl;
extern volatile rtc_cap_time_t  *g_pcap_time;
void            rtc_config_capture(rtc_capture_cfg_t *p_capture);
rtc_err_t       rtc_check_capture(rtc_pin_t pin, tm_t *p_time);
void            rtc_disable_capture(rtc_pin_t pin);
#endif

void     rtc_init(void);
void     rtc_set_output(rtc_output_t output_freq);
void     rtc_set_periodic(rtc_periodic_t freq, uint8_t priority);
void     rtc_set_current_time (tm_t * p_current);
void     rtc_set_alarm_time(tm_t * p_alarm);
void     rtc_read_current (tm_t * p_current);
void     rtc_enable_alarms(rtc_alarm_ctrl_t *p_alm_ctrl);
void     rtc_read_alarm(tm_t * p_alarm);
void     rtc_reset(void);
void     rtc_counter_run(const uint8_t bit_value);
void     rtc_disable_ints(void);
void     rtc_enable_ints(void);
int  rtc_bcd_to_dec(uint8_t to_convert);
uint8_t  rtc_dec_to_bcd(uint8_t to_convert);


#endif /* R_RTC_PRIVATE_H */

