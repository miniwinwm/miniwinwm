/***********************************************************************************************************************
 * Copyright [2015-2021] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
 * 
 * This file is part of Renesas SynergyTM Software Package (SSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas SSP license agreement. Unless otherwise agreed in an SSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * File Name    : r_rtc.h
 * Description  : Main header file for the RTC HAL API
 **********************************************************************************************************************/


/*******************************************************************************************************************//**
 * @ingroup HAL_Library
 * @defgroup RTC RTC
 * @brief Driver for the Realtime Clock (RTC).
 *
 * This module supports the Real Time Clock (RTC).  It implements
 * the following interfaces:
 *   - @ref RTC_API
 * @{
 **********************************************************************************************************************/

#ifndef R_RTC_H
#define R_RTC_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"
#include "r_rtc_cfg.h"
#include "r_rtc_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RTC_CODE_VERSION_MAJOR (2U)
#define RTC_CODE_VERSION_MINOR (0U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/** Counting mode */
typedef enum e_rtc_count_mode
{
    RTC_CALENDAR_MODE = 0,          ///< Calender count mode
    RTC_BINARY_MODE   = 1           ///< Binary count mode
} rtc_count_mode_t;

/** Channel control block. DO NOT INITIALIZE.  Initialization occurs when rtc_api_t::open is called */
typedef struct st_rtc_ctrl
{

    void                  * p_reg;                         ///< Pointer to register base address
    void                 (* p_callback)(rtc_callback_args_t * cb_data); ///< Called from the ISR.
    void const            * p_context;                     ///< Passed to the callback.
    uint32_t                open;                          ///< Whether or not driver is open
    IRQn_Type               alarm_irq;                     ///< Alarm IRQ number
    IRQn_Type               periodic_irq;                  ///< Periodic IRQ number
    IRQn_Type               carry_irq;                     ///< Carry IRQ number
    rtc_clock_source_t      clock_source;                  ///< Clock source for the RTC block
    bool                    suppress_carry_event_callback; ///< carry event callback will be suppressed if set
    volatile bool           carry_isr_triggered;           ///< Was the carry isr triggered
} rtc_instance_ctrl_t;

/**********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/
/** @cond INC_HEADER_DEFS_SEC */
/** Filled in Interface API structure for this Instance. */
extern const rtc_api_t g_rtc_on_rtc;
/** @endcond */

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif // R_RTC_H

/*******************************************************************************************************************//**
 * @} (end defgroup RTC)
 **********************************************************************************************************************/
