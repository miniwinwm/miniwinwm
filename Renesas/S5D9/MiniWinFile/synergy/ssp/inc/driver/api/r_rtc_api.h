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
 * File Name    : r_rtc_api.h
 * Description  : RTC Interface
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @ingroup Interface_Library
 * @defgroup RTC_API RTC Interface
 * @brief Interface for accessing the Realtime Clock.
 *
 * Related SSP architecture topics:
 *  - @ref ssp-interfaces
 *  - @ref ssp-predefined-layers
 *  - @ref using-ssp-modules
 *
 * RTC description: @ref HALRTCInterface
 *
 * @{
 **********************************************************************************************************************/

#ifndef DRV_RTC_API_H
#define DRV_RTC_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
/* Register definitions, common services and error codes. */
#include "bsp_api.h"
/** Use of time structure, tm */
#include <time.h>

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RTC_API_VERSION_MAJOR (2U)
#define RTC_API_VERSION_MINOR (0U)

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
/** Events that can trigger a callback function */
typedef enum e_rtc_event
{
    RTC_EVENT_ALARM_IRQ,       ///< Real Time Clock ALARM IRQ
    RTC_EVENT_PERIODIC_IRQ,    ///< Real Time Clock PERIODIC IRQ
    RTC_EVENT_CARRY_IRQ        ///< Real Time Clock CARRY IRQ
} rtc_event_t;

/** Callback function parameter data */
typedef struct st_rtc_callback_args
{
    rtc_event_t   event;       ///< The event can be used to identify what caused the callback (compare match or error).
    void const  * p_context;   ///< Placeholder for user data.  Set in r_timer_t::open function in ::timer_cfg_t.
} rtc_callback_args_t;

/** Clock source for the RTC block */
typedef enum e_rtc_count_source
{
    RTC_CLOCK_SOURCE_SUBCLK = 0,   ///< Sub-clock oscillator
    RTC_CLOCK_SOURCE_LOCO   = 1    ///< Low power On Chip Oscillator
} rtc_clock_source_t;

/** RTC run state */
typedef enum e_rtc_status
{
    RTC_STATUS_STOPPED = 0,   ///< RTC counter is stopped
    RTC_STATUS_RUNNING = 1    ///< RTC counter is running
} rtc_status_t;

/** Time error adjustment settings */
typedef enum e_rtc_error_adjustment
{
    RTC_ERROR_ADJUSTMENT_NONE               = 0, ///< Adjustment is not performed
    RTC_ERROR_ADJUSTMENT_ADD_PRESCALER      = 1, ///< Adjustment is performed by the addition to the prescaler
    RTC_ERROR_ADJUSTMENT_SUBTRACT_PRESCALER = 2, ///< Adjustment is performed by the subtraction from the prescaler
} rtc_error_adjustment_t;

/** Time error adjustment value configuration */
typedef struct st_rtc_error_adjustment_cfg
{
    rtc_error_adjustment_t      adjustment_type;       ///< Time error adjustment type setting
    uint8_t                     adjustment_value;      ///< Time error adjustment value
} rtc_error_adjustment_cfg_t;

/** Time error adjustment mode settings */
typedef enum e_rtc_error_adjustment_mode
{
    RTC_ERROR_ADJUSTMENT_MODE_MANUAL         = 0, ///< Adjustment mode is set to manual
    RTC_ERROR_ADJUSTMENT_MODE_AUTOMATIC      = 1, ///< Adjustment mode is set to automatic
} rtc_error_adjustment_mode_t;

/** Time error adjustment period settings */
typedef enum e_rtc_error_adjustment_period
{
    RTC_ERROR_ADJUSTMENT_PERIOD_1_MINUTE       = 0, ///< Adjustment period is set to every one minute
    RTC_ERROR_ADJUSTMENT_PERIOD_10_SECOND      = 1, ///< Adjustment period is set to every ten second
    RTC_ERROR_ADJUSTMENT_PERIOD_NONE         = 2, ///< Adjustment period not supported in manual mode
} rtc_error_adjustment_period_t;

/** Time error adjustment mode and period configuration */
typedef struct st_rtc_error_adjustment_mode_cfg
{
    rtc_error_adjustment_mode_t      adjustment_mode;        ///< Time error adjustment mode setting
    rtc_error_adjustment_period_t    adjustment_period;      ///< Time error adjustment period setting
} rtc_error_adjustment_mode_cfg_t;

/** Periodic Interrupt select */
typedef enum e_rtc_periodic_irq_select
{
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_256_SECOND = 6, ///< A periodic irq is generated every 1/256 second
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_128_SECOND,     ///< A periodic irq is generated every 1/128 second
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_64_SECOND,      ///< A periodic irq is generated every 1/64 second
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_32_SECOND,      ///< A periodic irq is generated every 1/32 second
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_16_SECOND,      ///< A periodic irq is generated every 1/16 second
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_8_SECOND,       ///< A periodic irq is generated every 1/8 second
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_4_SECOND,       ///< A periodic irq is generated every 1/4 second
    RTC_PERIODIC_IRQ_SELECT_1_DIV_BY_2_SECOND,       ///< A periodic irq is generated every 1/2 second
    RTC_PERIODIC_IRQ_SELECT_1_SECOND,                ///< A periodic irq is generated every 1 second
    RTC_PERIODIC_IRQ_SELECT_2_SECONDS,               ///< A periodic irq is generated every 2 seconds
} rtc_periodic_irq_select_t;

/** Date and time structure defined in C standard library <time.h> */
typedef struct tm rtc_time_t;

/** Alarm time setting structure */
typedef struct st_rtc_alarm_time
{
    rtc_time_t  time;            ///< Time structure
    bool        sec_match;       ///< Enable the alarm based on a match of the seconds field
    bool        min_match;       ///< Enable the alarm based on a match of the minutes field
    bool        hour_match;      ///< Enable the alarm based on a match of the hours field
    bool        mday_match;      ///< Enable the alarm based on a match of the days field
    bool        mon_match;       ///< Enable the alarm based on a match of the months field
    bool        year_match;      ///< Enable the alarm based on a match of the years field
    bool        dayofweek_match; ///< Enable the alarm based on a match of the dayofweek field
} rtc_alarm_time_t;

/** RTC Information Structure for information returned by  infoGet() */
typedef struct st_rtc_info
{
   rtc_clock_source_t      clock_source;        ///< Clock source for the RTC block
   rtc_status_t status;                         ///< RTC run status
} rtc_info_t;

/** User configuration structure, used in open function */
typedef struct st_rtc_cfg
{
    rtc_clock_source_t      clock_source;              ///< Clock source for the RTC block
    bool                    hw_cfg;                    ///< Initialize RTC in Open()
    uint32_t                error_adjustment_value;    ///< Value of the prescaler for error adjustment
    rtc_error_adjustment_t  error_adjustment_type;     ///< How the prescaler value is applied
    uint8_t                 alarm_ipl;                 ///< Alarm interrupt priority
    uint8_t                 periodic_ipl;              ///< Periodic interrupt priority
    uint8_t                 carry_ipl;                 ///< Carry interrupt priority
    void                 (* p_callback)(rtc_callback_args_t * p_args); ///< Called from the ISR.
    void const            * p_context;                 ///< Passed to the callback.
    void const            * p_extend;                  ///< RTC hardware dependant configuration.
} rtc_cfg_t;

/** RTC control block.  Allocate an instance specific control block to pass into the RTC API calls.
 * @par Implemented as
 * - rtc_instance_ctrl_t
 */
typedef void rtc_ctrl_t;

/** RTC driver structure. General RTC functions implemented at the HAL layer follow this API. */
typedef struct st_rtc_api
{
    /** Open the RTC driver.
     * @par Implemented as
     * - R_RTC_Open()
     *
     * @param[in] p_ctrl     Pointer to RTC device handle
     * @param[in] p_cfg      Pointer to the configuration structure
     */
    ssp_err_t (* open)(rtc_ctrl_t * const p_ctrl, rtc_cfg_t const * const p_cfg);

    /** Close the RTC driver.
     * @par Implemented as
     * - R_RTC_Close()
     *
     * @param[in] p_ctrl     Pointer to RTC device handle.
     */
    ssp_err_t (* close)(rtc_ctrl_t * const p_ctrl);

    /** Configure the RTC driver.
     * @par Implemented as
     * - R_RTC_Configure()
     *
     * @param[in] p_ctrl     Pointer to RTC device handle.
     * @param[in] p_extend   Currently not implemented, pass NULL.
     */
    ssp_err_t (* configure)(rtc_ctrl_t * const p_ctrl, void * const p_extend);

    /** Set the calendar time.
     * @par Implemented as
     * - R_RTC_CalendarTimeSet()
     *
     * @param[in] p_ctrl      Pointer to RTC device handle
     * @param[in] p_time      Pointer to a time structure that contains the time to set
     * @param[in] clock_start Flag that starts the clock right after it is set
     */
    ssp_err_t (* calendarTimeSet)(rtc_ctrl_t * const p_ctrl, rtc_time_t * p_time, bool clock_start);

    /** Get the calendar time.
     * @par Implemented as
     * - R_RTC_CalendarTimeGet()
     *
     * @param[in] p_ctrl      Pointer to RTC device handle
     * @param[out] p_time     Pointer to a time structure that contains the time to get
     */
    ssp_err_t (* calendarTimeGet)(rtc_ctrl_t * const p_ctrl, rtc_time_t * p_time);

    /** Set the calendar alarm time.
     * @par Implemented as
     * - R_RTC_CalendarAlarmSet()
     *
     * @param[in] p_ctrl                 Pointer to RTC device handle
     * @param[in] p_alarm                Pointer to an alarm structure that contains the alarm time to set
     * @param[in] irq_enable_flag        Enable the ALARM irq if set
     */
    ssp_err_t (* calendarAlarmSet)(rtc_ctrl_t * const p_ctrl, rtc_alarm_time_t * p_alarm, bool irq_enable_flag);

    /** Get the calendar alarm time.
     * @par Implemented as
     * - R_RTC_CalendarAlarmGet()
     *
     * @param[in] p_ctrl       Pointer to RTC device handle
     * @param[out] p_alarm     Pointer to an alarm structure to fill up with the alarm time
     */
    ssp_err_t (* calendarAlarmGet)(rtc_ctrl_t * const p_ctrl, rtc_alarm_time_t * p_alarm);

    /** Start the calendar counter.
     * @par Implemented as
     * - R_RTC_CalendarCounterStart()
     *
     * @param[in] p_ctrl       Pointer to RTC device handle
     */
    ssp_err_t (* calendarCounterStart)(rtc_ctrl_t * const p_ctrl);

    /** Stop the calendar counter.
     * @par Implemented as
     * - R_RTC_CalendarCounterStop()
     *
     * @param[in] p_ctrl       Pointer to RTC device handle
     */
    ssp_err_t (* calendarCounterStop)(rtc_ctrl_t * const p_ctrl);

    /** Enable the alarm irq.
     * @par Implemented as
     * - R_RTC_IrqEnable()
     *
     * @param[in] p_ctrl       Pointer to RTC device handle
     */
    ssp_err_t (* irqEnable)(rtc_ctrl_t * const p_ctrl, rtc_event_t irq);

    /** Disable the alarm irq.
     * @par Implemented as
     * - R_RTC_IrqDisable()
     *
     * @param[in] p_ctrl       Pointer to RTC device handle
     */
    ssp_err_t (* irqDisable)(rtc_ctrl_t * const p_ctrl, rtc_event_t irq);

    /** Set the periodic irq rate
     * @par Implemented as
     * - R_RTC_PeriodicIrqRateSet()
     *
     * @param[in] p_ctrl       Pointer to RTC device handle
     * @param[in] rate         Rate of periodic interrupts
     */
    ssp_err_t (* periodicIrqRateSet)(rtc_ctrl_t * const p_ctrl, rtc_periodic_irq_select_t rate);

    /** Return the currently configure clock source for the RTC
         *
         * @par Implemented as
         *  - R_RTC_InfoGet()
         *
         * @param[in]   p_ctrl       Pointer to control handle structure
         * @param[out]  p_rtc_info   Pointer to RTC information structure
         */
    ssp_err_t (* infoGet) (rtc_ctrl_t * p_ctrl, rtc_info_t * p_rtc_info);

    /** Set time error adjustment mode.
     *
     * @par Implemented as
     *  - R_RTC_ErrorAdjustmentModeSet()
     *
     * @param[in]   p_ctrl                    Pointer to control handle structure
     * @param[in]   p_error_adjustment_mode   Pointer to error adjustment mode configuration structure
     */
    ssp_err_t (* errorAdjustmentModeSet) (rtc_ctrl_t * p_ctrl,
                                          rtc_error_adjustment_mode_cfg_t *p_error_adjustment_mode);

    /** Set time error adjustment.
     *
     * @par Implemented as
     *  - R_RTC_ErrorAdjustmentSet()
     *
     * @param[in]   p_ctrl                      Pointer to control handle structure
     * @param[in]   p_error_adjustment_config   Pointer to error adjustment structure
     */
    ssp_err_t (* errorAdjustmentSet) (rtc_ctrl_t * p_ctrl, rtc_error_adjustment_cfg_t *p_error_adjustment_config);

    /** Gets version and stores it in provided pointer p_version.
     * @par Implemented as
     * - R_RTC_VersionGet()
     *
     * @param[out]  p_version  Code and API version used
     */
    ssp_err_t (* versionGet)(ssp_version_t * version);

} rtc_api_t;

/** This structure encompasses everything that is needed to use an instance of this interface. */
typedef struct st_rtc_instance
{
    rtc_ctrl_t      * p_ctrl;    ///< Pointer to the control structure for this instance
    rtc_cfg_t const * p_cfg;     ///< Pointer to the configuration structure for this instance
    rtc_api_t const * p_api;     ///< Pointer to the API structure for this instance
} rtc_instance_t;

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* DRV_RTC_API_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup RTC_API)
 **********************************************************************************************************************/
