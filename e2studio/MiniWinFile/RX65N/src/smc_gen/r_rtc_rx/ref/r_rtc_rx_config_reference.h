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
* File Name    : r_rtc_rx_config.h
* Description  : Configures the Real Time Clock (RTC) package for RX MCUs.
************************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           09.09.2013 1.00    First release.
*           16.04.2014 2.00    Updated for new API.
*           03.09.2014 2.10    Added support for RX64M
*           03.12.2014 2.20    Added support for RX113
*           26.01.2015 2.30    Added support for RX71M
*           06.07.2015 2.40    Added support for RX231
*           01.03.2016 2.41    Added support for RX130
*                              Added support for RX230
*                              Added the option of RTC_CFG_DRIVE_CAPACITY_MD for sub-clock drive capacity.
*           01.10.2016 2.50    Added support for RX65N
*           31.07.2017 2.70    Added support for RX65N-2MB and RX130-512KB.
*                              Removed support for RX210 and RX63N/631.
*           20.09.2017 2.71    Fixed issue that an incorrect time is read out when a carry of the RTC counter occurs
*                              while reading the current time.
*                              Fixed issue that count stop occurred at warm start.
*                              - There is no change in this file.
***********************************************************************************************************************/

#ifndef R_RTC_RX_CONFIG_H
#define R_RTC_RX_CONFIG_H

/***********************************************************************************************************************
Configuration Options
***********************************************************************************************************************/

/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING
 * Setting to BSP_CFG_PARAM_CHECKING_ENABLE utilizes the system default setting
 * Setting to 1 includes parameter checking; 0 compiles out parameter checking
 */
#define RTC_CFG_PARAM_CHECKING_ENABLE   (BSP_CFG_PARAM_CHECKING_ENABLE)


/* SPECIFY IF WANT TO CALCULATE DAY OF YEAR FOR R_RTC_Read(); 1-yes, 0=no (compiles out code) */
#define RTC_CFG_CALCULATE_YDAY          (0)


/* SPECIFY SUB-CLOCK OSCILLATOR DRIVE CAPACITY ON RX11x, RX130, RX23x, RX64M or RX71M, RX65N
 * uncomment appropriate level: standard, low, middle, or high
 */

/* Supported by the RX11x, RX130, RX23x, RX64M or RX71M, RX65N */
#define RTC_CFG_DRIVE_CAPACITY_STD

/* Supported by the RX11x, RX130, RX23x, RX64M or RX71M, RX65N */
//#define RTC_CFG_DRIVE_CAPACITY_LO

/* Supported by the RX11x only */
//#define RTC_CFG_DRIVE_CAPACITY_MD
//#define RTC_CFG_DRIVE_CAPACITY_HI


#endif /* R_RTC_RX_CONFIG_H */
