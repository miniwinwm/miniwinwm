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
 * File Name    : r_rtc.c
 * Description  : RTC module HAL APIs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <string.h>
#include "r_rtc.h"
#include "r_rtc_private.h"
#include "r_rtc_private_api.h"
#include "r_cgc_api.h"
#include "r_cgc.h"



/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define TRUE                            (1)
#define FALSE                           (0)

#define RTC_FIRST_DAY_OF_A_MONTH                (1)
/* Day of week : valid range between 0 to 6. */
#define RTC_DAYS_IN_A_WEEK                      (6)
/* Month : valid range between 0 to 11.*/
#define RTC_MONTHS_IN_A_YEAR                   (11)
#define RTC_LAST_DAY_OF_LEAP_FEB_MONTH         (29)
#define RTC_LAST_DAY_OF_A_MONTH                (31)
#define RTC_YEAR_VALUE_MIN                    (100)
#define RTC_YEAR_VALUE_MAX                    (199)

/* Seconds : valid range between 0 to 59.*/
#define RTC_SECONDS_IN_A_MINUTE                (59)
/* Minute : valid range between 0 to 59. */
#define RTC_MINUTES_IN_A_HOUR                  (59)
/* Hours : valid range between 0 to 23. */
#define RTC_HOURS_IN_A_DAY                     (23)
/* In Zeller algorithm value of (-[Y/100] + [Y/400]) is 15 for Y = 2000 to Y = 2099) */
#define RTC_ZELLER_ALGM_CONST_FIFTEEN          (15)

/* Macro definitions for February and March months */
#define RTC_FEBRUARY_MONTH                     (2U)
#define RTC_MARCH_MONTH                        (3U)

#define RTC_TIME_H_MONTH_OFFSET                 (1)
/*The RTC has a 100 year calendar to match the starting year 2000, year offset(1900) is added like 117 + 1900 = 2017 */
#define RTC_TIME_H_YEAR_OFFSET               (1900)


/* PCLKB/PCLK maximum for Synergy MCUs is 60MHz/32KHz = 0x753
 * As per information received from design group it takes 2 RTC cycle to update RTC status register.
 * Thus timeout value = 2 *  0x753
 */
/** "RTC" in ASCII, used to determine if device is open. */
#define RTC_OPEN               (0x00525443ULL)

#define RTC_REG_UPDATE_TIMEOUT (0xEA6U)

#define RTC_MAX_ERROR_ADJUSTMENT_VALUE (0x3FU)

/** Macro for error logger. */
#ifndef RTC_ERROR_RETURN
/*LDRA_INSPECTED 77 S This macro does not work when surrounded by parentheses. */
#define RTC_ERROR_RETURN(a, err) SSP_ERROR_RETURN((a), (err), &g_module_name[0], &s_rtc_version)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static uint8_t rtc_dec_to_bcd (uint8_t to_convert);
static uint8_t rtc_bcd_to_dec (uint8_t to_convert);
void rtc_alarm_isr (void);
void rtc_period_isr (void);
void rtc_carry_isr (void);

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
#if defined(__GNUC__)
/* This structure is affected by warnings from a GCC compiler bug. This pragma suppresses the warnings in this 
 * structure only. */
/*LDRA_INSPECTED 69 S */
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif
/** Version data structure used by error logger macro. */
static const ssp_version_t s_rtc_version =
{
    .api_version_minor  = RTC_API_VERSION_MINOR,
    .api_version_major  = RTC_API_VERSION_MAJOR,
    .code_version_major = RTC_CODE_VERSION_MAJOR,
    .code_version_minor = RTC_CODE_VERSION_MINOR
};
#if defined(__GNUC__)
/* Restore warning settings for 'missing-field-initializers' to as specified on command line. */
/*LDRA_INSPECTED 69 S */
#pragma GCC diagnostic pop
#endif

/** Name of module used by error logger macro */
#if BSP_CFG_ERROR_LOG != 0
static const char          g_module_name[] = "rtc";
#endif

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/
/** RTC Implementation of Real Time Clock  */
/*LDRA_INSPECTED 27 D This structure must be accessible in user code. It cannot be static. */
const rtc_api_t g_rtc_on_rtc =
{
    .open                   = R_RTC_Open,
    .close                  = R_RTC_Close,
    .configure              = R_RTC_Configure,
    .calendarTimeGet        = R_RTC_CalendarTimeGet,
    .calendarTimeSet        = R_RTC_CalendarTimeSet,
    .calendarAlarmGet       = R_RTC_CalendarAlarmGet,
    .calendarAlarmSet       = R_RTC_CalendarAlarmSet,
    .calendarCounterStart   = R_RTC_CalendarCounterStart,
    .calendarCounterStop    = R_RTC_CalendarCounterStop,
    .irqEnable              = R_RTC_IrqEnable,
    .irqDisable             = R_RTC_IrqDisable,
    .periodicIrqRateSet     = R_RTC_PeriodicIrqRateSet,
    .infoGet                = R_RTC_InfoGet,
    .errorAdjustmentModeSet = R_RTC_ErrorAdjustmentModeSet,
    .errorAdjustmentSet     = R_RTC_ErrorAdjustmentSet,
    .versionGet             = R_RTC_VersionGet
};

#if RTC_CFG_PARAM_CHECKING_ENABLE
/* Number of days in each months start from January to December */
static const uint8_t days_in_months[12] = {31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};
#endif
/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

static ssp_err_t r_rtc_set_clock_source (R_RTC_Type * p_rtc_reg, rtc_instance_ctrl_t *p_ctrl);

static ssp_err_t r_rtc_start_bit_clear (R_RTC_Type * p_rtc_reg);

static ssp_err_t r_rtc_start_bit_set (R_RTC_Type * p_rtc_reg);

static ssp_err_t r_rtc_software_reset (R_RTC_Type * p_rtc_reg);

static ssp_err_t r_rtc_nvic_enable_irq (IRQn_Type nvic_interrupt, uint32_t irq_en);

static ssp_err_t r_rtc_config_rtc_interrupts(fmi_event_info_t *event_info, rtc_instance_ctrl_t * p_ctrl, rtc_cfg_t const * const p_cfg, ssp_feature_t * ssp_feature);

static ssp_err_t r_rtc_enable_alarm_irq(rtc_instance_ctrl_t * p_ctrl, bool interrupt_enable_flag);

static ssp_err_t r_rtc_carry_irq_set (rtc_instance_ctrl_t * p_ctrl, bool carry_irq_enable_flag);

static ssp_err_t r_rtc_periodic_irq_set (rtc_instance_ctrl_t * p_ctrl, bool periodic_irq_enable_flag);

static ssp_err_t r_rtc_alarm_irq_set (rtc_instance_ctrl_t * p_ctrl, bool alarm_irq_enable_flag);

static ssp_err_t r_rtc_hour_mode_set (R_RTC_Type * p_rtc_reg);

#if RTC_CFG_PARAM_CHECKING_ENABLE
static ssp_err_t r_rtc_time_and_date_validate(rtc_time_t * p_time);

static ssp_err_t r_rtc_time_validate(rtc_time_t * p_time);

static ssp_err_t r_rtc_date_validate(rtc_time_t * p_time);

static ssp_err_t r_rtc_alarm_time_and_date_validate(rtc_alarm_time_t * p_time);

static ssp_err_t r_rtc_alarm_time_validate(rtc_alarm_time_t * p_time);

static ssp_err_t r_rtc_alarm_month_and_year_validate(rtc_alarm_time_t * p_time);

static ssp_err_t r_rtc_alarm_dayofmonth_and_dayofweek_validate(rtc_alarm_time_t * p_time);
#endif

static ssp_err_t r_rtc_error_adjustment_mode_set_common (R_RTC_Type * p_rtc_reg, rtc_error_adjustment_mode_t mode);

static ssp_err_t r_rtc_error_adjustment_period_set (R_RTC_Type * p_rtc_reg, rtc_error_adjustment_period_t period);

/*******************************************************************************************************************//**
 * @addtogroup RTC
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  Open the RTC driver.
 *
 *  Implements rtc_api_t::open.
 *
 * Opens and configures the RTC driver module.
 * Configuration includes clock source, and interrupt callback function.
 * If the sub-clock oscillator is the clock source it is started in this function.
 *
 * @retval SSP_SUCCESS          Initialization was successful and RTC has started.
 * @retval SSP_ERR_ASSERTION    Invalid p_api_ctrl or p_cfg pointer.
 * @retval SSP_ERR_HW_LOCKED    Hardware in use
 * @retval SSP_ERR_TIMEOUT      Status check for counter mode or reset timed out
 * @return                      See @ref Common_Error_Codes or functions called by this function for other possible
 *                              return codes. This function calls:
 *                                  * fmi_api_t::productFeatureGet
 **********************************************************************************************************************/
ssp_err_t R_RTC_Open (rtc_ctrl_t * const p_api_ctrl, rtc_cfg_t const * const p_cfg)
{
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) p_api_ctrl;
    ssp_err_t err = SSP_SUCCESS;

    /* Parameter checking */
#if RTC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(p_ctrl);
    SSP_ASSERT(p_cfg);
#endif

    ssp_feature_t ssp_feature;
    ssp_feature.word = 0U;
    ssp_feature.channel = 0U;
    ssp_feature.unit = 0U;
    ssp_feature.id = SSP_IP_RTC;
    fmi_feature_info_t info;
    info.ptr = (void *) NULL;
    err = g_fmi_on_fmi.productFeatureGet(&ssp_feature, &info);
    RTC_ERROR_RETURN(SSP_SUCCESS == err, err);
    p_ctrl->p_reg = info.ptr;
    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;
    fmi_event_info_t event_info;
    event_info.event = (elc_event_t)NULL;
    event_info.irq = (IRQn_Type)NULL;

    /* Attempt to acquire lock for RTC. Prevents re-entrance conflict. */
    err = R_BSP_HardwareLock(&ssp_feature);
    RTC_ERROR_RETURN((SSP_SUCCESS == err), SSP_ERR_HW_LOCKED);
    R_BSP_ModuleStart(&ssp_feature);

    r_rtc_config_rtc_interrupts(&event_info, p_ctrl, p_cfg, &ssp_feature);

    /* Remember the clock source */
    p_ctrl->clock_source = p_cfg->clock_source;
    p_ctrl->carry_isr_triggered = false;
    p_ctrl->suppress_carry_event_callback = false;

    /* Check if the RTC hardware is to be configured */
    if (true == p_cfg->hw_cfg)
    {
        /* Set the clock source of the RTC block according to the UM */
        err = r_rtc_set_clock_source(p_rtc_reg, p_ctrl);
        if (SSP_SUCCESS != err)
        {
            R_BSP_HardwareUnlock(&ssp_feature);
            return err;
        }
    }

    /* Save the passed in callback and context pointers to local storage. These will be used in the ISR. */
    if (p_cfg->p_callback)
    {
        p_ctrl->p_callback  = p_cfg->p_callback;
        p_ctrl->p_context = p_cfg->p_context;
    }

    /** Mark driver as open by initializing it to "RTC" in its ASCII equivalent. */
    p_ctrl->open = RTC_OPEN;
    return err;
}

/*******************************************************************************************************************//**
 * @brief  Close the RTC driver.
 *
 *  Implements rtc_api_t::close
 *
 * @retval SSP_SUCCESS          De-Initialization was successful and RTC driver closed.
 * @retval SSP_ERR_ASSERTION    Invalid p_api_ctrl or p_ctrl->p_reg member pointed by p_api_ctrl pointer.
 * @retval SSP_ERR_NOT_OPEN     Driver not open already for close.
 **********************************************************************************************************************/
ssp_err_t R_RTC_Close (rtc_ctrl_t * const p_api_ctrl)
{
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) p_api_ctrl;
    /* Parameter checking */
#if RTC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(p_ctrl);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
    RTC_ERROR_RETURN(RTC_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    ssp_feature_t ssp_feature;
    ssp_feature.word    = 0U;
    ssp_feature.channel = 0U;
    ssp_feature.unit    = 0U;
    ssp_feature.id      = SSP_IP_RTC;

    R_BSP_ModuleStop(&ssp_feature);

    /** Disable the periodic interrupt, alarm interrupt, carry interrupts, and disable there interrupt priority and vector info. */
    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;
    ssp_vector_info_t * p_vector_info;
    if (SSP_INVALID_VECTOR != p_ctrl->periodic_irq)
    {
        HW_RTC_RTCPeriodicIRQDisable(p_rtc_reg);
        NVIC_DisableIRQ(p_ctrl->periodic_irq);
        R_SSP_VectorInfoGet(p_ctrl->periodic_irq, &p_vector_info);
        *(p_vector_info->pp_ctrl) = NULL;
    }
    if (SSP_INVALID_VECTOR != p_ctrl->alarm_irq)
    {
        HW_RTC_RTCAlarmIRQDisable(p_rtc_reg);
        NVIC_DisableIRQ(p_ctrl->alarm_irq);
        R_SSP_VectorInfoGet(p_ctrl->alarm_irq, &p_vector_info);
        *(p_vector_info->pp_ctrl) = NULL;
    }
    if (SSP_INVALID_VECTOR != p_ctrl->carry_irq)
    {
        HW_RTC_RTCCarryIRQDisable(p_rtc_reg);
        NVIC_DisableIRQ(p_ctrl->carry_irq);
        R_SSP_VectorInfoGet(p_ctrl->carry_irq, &p_vector_info);
        *(p_vector_info->pp_ctrl) = NULL;
    }
    R_BSP_HardwareUnlock(&ssp_feature);
    p_ctrl->open  =  0U;
    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Configure the RTC driver.
 *
 *  Implements rtc_api_t::configure
 *
 * @retval SSP_SUCCESS          RTC was successful configured.
 * @retval SSP_ERR_ASSERTION    Invalid p_api_ctrl or p_ctrl->p_reg member pointed by p_api_ctrl pointer.
 * @retval SSP_ERR_NOT_OPEN     Driver not open already for operation.
 * @retval SSP_ERR_TIMEOUT      Status check for counter mode or reset timed out
 **********************************************************************************************************************/
ssp_err_t R_RTC_Configure (rtc_ctrl_t * const p_api_ctrl, void * const p_extend)
{
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) p_api_ctrl;

    /** Parameter checking */
#if RTC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(p_ctrl);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
    RTC_ERROR_RETURN(RTC_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    ssp_err_t  error = SSP_SUCCESS;
    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;

    /** p_extend is currently not used, reserved for future use */
    SSP_PARAMETER_NOT_USED(p_extend);

    /** Set the clock source of the RTC block according to the UM */
    error = r_rtc_set_clock_source(p_rtc_reg, p_ctrl);
    return error;
}

/*******************************************************************************************************************//**
 * @brief  Set the calendar time.
 *
 *  Implements rtc_api_t::calendarTimeSet.
 *
 * @retval SSP_SUCCESS              Calendar time set operation was successful.
 * @retval SSP_ERR_ASSERTION        Invalid p_api_ctrl, p_time or p_ctrl->p_reg member pointed by p_api_ctrl pointer.
 * @retval SSP_ERR_NOT_OPEN         Driver not open already for operation.
 * @retval SSP_ERR_INVALID_ARGUMENT Invalid time parameter field.
 * @retval SSP_ERR_TIMEOUT          Software reset status check failed.
 **********************************************************************************************************************/
ssp_err_t R_RTC_CalendarTimeSet (rtc_ctrl_t * const p_api_ctrl, rtc_time_t * p_time, bool clock_start)
{
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) p_api_ctrl;
    ssp_err_t err = SSP_SUCCESS;

#if RTC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(p_ctrl);
    SSP_ASSERT(p_time);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
    RTC_ERROR_RETURN(RTC_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    /* Set the START bit to 0 */
    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;
    err = r_rtc_start_bit_clear(p_rtc_reg);
    if (SSP_SUCCESS == err)
    {
        /* Execute an RTC software reset */
        err = r_rtc_software_reset(p_rtc_reg);
        if (SSP_SUCCESS == err)
        {
#if RTC_CFG_PARAM_CHECKING_ENABLE
            /* Verify the seconds, minutes, hours, year ,day of the week, day of the month, month and year are valid values */
            err = r_rtc_time_and_date_validate(p_time);
            RTC_ERROR_RETURN(SSP_SUCCESS == err, err);
#endif
            /* Set the year, month, day of the week, ... */
            HW_RTC_SecondSet(p_rtc_reg, rtc_dec_to_bcd((uint8_t) p_time->tm_sec));
            HW_RTC_MinuteSet(p_rtc_reg, rtc_dec_to_bcd((uint8_t) p_time->tm_min));
            HW_RTC_HourSet(p_rtc_reg, rtc_dec_to_bcd((uint8_t) p_time->tm_hour));
            HW_RTC_DayOfWeekSet(p_rtc_reg, rtc_dec_to_bcd((uint8_t) p_time->tm_wday));
            HW_RTC_DayOfMonthSet(p_rtc_reg, rtc_dec_to_bcd((uint8_t) p_time->tm_mday));
            HW_RTC_MonthSet(p_rtc_reg, rtc_dec_to_bcd((uint8_t) (p_time->tm_mon+1))); /* Add one to match with HW register */
            HW_RTC_YearSet(p_rtc_reg, rtc_dec_to_bcd((uint8_t) (p_time->tm_year-100))); /* Subtract 100 to match with HW register */

            /* Set the START bit to 1 */
            if (clock_start)
            {
                err = r_rtc_start_bit_set(p_rtc_reg);
            }
        }
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief  Get the calendar time. (Should not be called from critical section as it may return incorrect time)
 *
 *  Implements rtc_api_t::calendarTimeGet
 *
 * @retval SSP_SUCCESS          Calendar time get operation was successful.
 * @retval SSP_ERR_ASSERTION    Invalid p_api_ctrl, p_time or p_ctrl->p_reg member pointed by p_api_ctrl pointer.
 * @retval SSP_ERR_NOT_OPEN     Driver not open already for operation.
 * @retval SSP_ERR_TIMEOUT      IRQ enable operation timed out.
 **********************************************************************************************************************/
ssp_err_t R_RTC_CalendarTimeGet (rtc_ctrl_t * const p_api_ctrl, rtc_time_t * p_time)
{
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) p_api_ctrl;
#if RTC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(p_ctrl);
    SSP_ASSERT(p_time);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
    RTC_ERROR_RETURN(RTC_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;
    ssp_err_t err = SSP_SUCCESS;

    uint32_t carry_irq_status = NVIC_GetEnableIRQ((IRQn_Type) p_ctrl->carry_irq);

    if ((uint32_t)0U == carry_irq_status)
    {
        p_ctrl->suppress_carry_event_callback = true;
        err = r_rtc_carry_irq_set(p_ctrl, true);
        RTC_ERROR_RETURN(SSP_SUCCESS == err, err);
    }

    /** Read all the time registers, if a carry irq occurred in-between read again */
    do
    {
        p_ctrl->carry_isr_triggered = false; /** This flag will be set to 'true' in the carry ISR */
        p_time->tm_sec  = (int32_t) rtc_bcd_to_dec(HW_RTC_SecondGet(p_rtc_reg));
        p_time->tm_min  = (int32_t) rtc_bcd_to_dec(HW_RTC_MinuteGet(p_rtc_reg));
        p_time->tm_hour = (int32_t) rtc_bcd_to_dec(HW_RTC_HourGet(p_rtc_reg));
        p_time->tm_wday = (int32_t) rtc_bcd_to_dec(HW_RTC_DayOfWeekGet(p_rtc_reg));
        p_time->tm_mday = (int32_t) rtc_bcd_to_dec(HW_RTC_DayOfMonthGet(p_rtc_reg));
        p_time->tm_mon  = (int32_t) rtc_bcd_to_dec(HW_RTC_MonthGet(p_rtc_reg))-1; /* Subtract one to match with C time.h standards */
        p_time->tm_year = (int32_t) rtc_bcd_to_dec((uint8_t) HW_RTC_YearGet(p_rtc_reg)) + 100; /* Add 100 to match with C time.h standards */
    }
    while (true == p_ctrl->carry_isr_triggered);

    /** Restore the state of carry IRQ. */
    if ((uint32_t)0U == carry_irq_status)
    {
        p_ctrl->suppress_carry_event_callback = false;
        err = r_rtc_carry_irq_set(p_ctrl, false);
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief  Set the calendar alarm time.
 *
 *  Implements rtc_api_t::calendarAlarmSet.
 *
 * @pre The calendar counter must be running before the alarm can be set.
 *
 * @retval SSP_SUCCESS              Calendar alarm time set operation was successful.
 * @retval SSP_ERR_INVALID_ARGUMENT Invalid time parameter field.
 * @retval SSP_ERR_ASSERTION        Invalid p_api_ctrl, p_alarm or p_ctrl->p_reg member pointed by p_api_ctrl pointer.
 * @retval SSP_ERR_NOT_OPEN         Driver not open already for operation.
 **********************************************************************************************************************/
ssp_err_t R_RTC_CalendarAlarmSet (rtc_ctrl_t * const p_api_ctrl, rtc_alarm_time_t * p_alarm, bool interrupt_enable_flag)
{
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) p_api_ctrl;
    ssp_err_t err = SSP_SUCCESS;

#if RTC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(p_ctrl);
    SSP_ASSERT(p_alarm);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
    RTC_ERROR_RETURN(RTC_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    if (SSP_INVALID_VECTOR != p_ctrl->alarm_irq)
    {
        /** Disable the ICU alarm interrupt request */
        NVIC_DisableIRQ(p_ctrl->alarm_irq);
    }

    /** Set alarm time */
    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;
#if RTC_CFG_PARAM_CHECKING_ENABLE
    /** Verify the seconds, minutes, hours, year ,day of the week, day of the month and month are valid values */
    err = r_rtc_alarm_time_and_date_validate(p_alarm);
    RTC_ERROR_RETURN(SSP_SUCCESS == err, err);
#endif

    HW_ALARM_SecondSet(p_rtc_reg, rtc_dec_to_bcd((uint8_t) p_alarm->time.tm_sec), (bool) p_alarm->sec_match);
    HW_ALARM_MinuteSet(p_rtc_reg, rtc_dec_to_bcd((uint8_t) p_alarm->time.tm_min), (bool) p_alarm->min_match);
    HW_ALARM_HourSet(p_rtc_reg, rtc_dec_to_bcd((uint8_t) p_alarm->time.tm_hour), (bool) p_alarm->hour_match);
    HW_ALARM_DayOfWeekSet(p_rtc_reg, (uint8_t) p_alarm->time.tm_wday, (bool) p_alarm->dayofweek_match);
    HW_ALARM_DayOfMonthSet(p_rtc_reg, rtc_dec_to_bcd((uint8_t) p_alarm->time.tm_mday), (bool) p_alarm->mday_match);
    HW_ALARM_MonthSet(p_rtc_reg, rtc_dec_to_bcd((uint8_t) (p_alarm->time.tm_mon+1)), (bool) p_alarm->mon_match); /* Add one to month to match with HW register */
    HW_ALARM_YearSet(p_rtc_reg, rtc_dec_to_bcd((uint8_t) (p_alarm->time.tm_year-100)), (bool) p_alarm->year_match); /* Subtract 100 to match with HW register */

    err = r_rtc_enable_alarm_irq(p_ctrl,interrupt_enable_flag);
    return err;
}

/*******************************************************************************************************************//**
 * @brief  Get the calendar alarm time.
 *
 *  Implements rtc_api_t::calendarAlarmGet
 *
 * @retval SSP_SUCCESS           Calendar alarm time get operation was successful.
 * @retval SSP_ERR_ASSERTION     Invalid p_api_ctrl, p_alarm or p_ctrl->p_reg member pointed by p_api_ctrl pointer.
 * @retval SSP_ERR_NOT_OPEN      Driver not open already for operation.
 **********************************************************************************************************************/
ssp_err_t R_RTC_CalendarAlarmGet (rtc_ctrl_t * const p_api_ctrl, rtc_alarm_time_t * p_alarm)
{
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) p_api_ctrl;
#if RTC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(p_ctrl);
    SSP_ASSERT(p_alarm);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
    RTC_ERROR_RETURN(RTC_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    /** Get the alarm time */
    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;
    p_alarm->time.tm_sec     = rtc_bcd_to_dec(HW_ALARM_SecondGet(p_rtc_reg));
    p_alarm->time.tm_min     = rtc_bcd_to_dec(HW_ALARM_MinuteGet(p_rtc_reg));
    p_alarm->time.tm_hour    = rtc_bcd_to_dec(HW_ALARM_HourGet(p_rtc_reg));
    p_alarm->time.tm_wday    = rtc_bcd_to_dec(HW_ALARM_DayOfWeekGet(p_rtc_reg));
    p_alarm->time.tm_mday    = rtc_bcd_to_dec(HW_ALARM_DayOfMonthGet(p_rtc_reg));
    p_alarm->time.tm_mon     = rtc_bcd_to_dec(HW_ALARM_MonthGet(p_rtc_reg))-(uint8_t)1; /* Subtract one from month to match with C time.h standards */
    p_alarm->time.tm_year    = rtc_bcd_to_dec((uint8_t) HW_ALARM_YearGet(p_rtc_reg)) + (uint8_t)100; /* Add 100 to the year to match with C time.h standards */

    p_alarm->sec_match       = HW_ALARM_SecondMatchGet(p_rtc_reg);
    p_alarm->min_match       = HW_ALARM_MinuteMatchGet(p_rtc_reg);
    p_alarm->hour_match      = HW_ALARM_HourMatchGet(p_rtc_reg);
    p_alarm->dayofweek_match = HW_ALARM_DayOfWeekMatchGet(p_rtc_reg);
    p_alarm->mday_match      = HW_ALARM_DayOfMonthMatchGet(p_rtc_reg);
    p_alarm->mon_match       = HW_ALARM_MonthMatchGet(p_rtc_reg);
    p_alarm->year_match      = HW_ALARM_YearMatchGet(p_rtc_reg);

    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Start the calendar counter.
 *
 *  Implements rtc_api_t::calendarCounterStart.
 *
 * @retval SSP_SUCCESS         Calendar counter started.
 * @retval SSP_ERR_ASSERTION   Invalid p_api_ctrl or p_ctrl->p_reg member pointed by p_api_ctrl pointer.
 * @retval SSP_ERR_NOT_OPEN    Driver not open already for operation.
 * @retval SSP_ERR_TIMEOUT     Start bit not set.
 **********************************************************************************************************************/
ssp_err_t R_RTC_CalendarCounterStart (rtc_ctrl_t * const p_api_ctrl)
{
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) p_api_ctrl;
#if RTC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(p_ctrl);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
    RTC_ERROR_RETURN(RTC_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    /** Set the start bit. */
    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;

    return r_rtc_start_bit_set(p_rtc_reg);
}

/*******************************************************************************************************************//**
 * @brief  Stop the calendar counter.
 *
 *  Implements rtc_api_t::calendarCounterStop.
 *
 * @retval SSP_SUCCESS           Calendar counter stopped.
 * @retval SSP_ERR_ASSERTION     Invalid p_api_ctrl or p_ctrl->p_reg member pointed by p_api_ctrl pointer.
 * @retval SSP_ERR_NOT_OPEN      Driver not open already for operation.
 * @retval SSP_ERR_TIMEOUT       Start bit not cleared.
 **********************************************************************************************************************/
ssp_err_t R_RTC_CalendarCounterStop (rtc_ctrl_t * const p_api_ctrl)
{
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) p_api_ctrl;
#if RTC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(p_ctrl);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
    RTC_ERROR_RETURN(RTC_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    /** Clear the start bit. */

    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;

    return r_rtc_start_bit_clear(p_rtc_reg);
}

/*******************************************************************************************************************//**
 * @brief  Enable the alarm interrupt.
 *
 *  Implements rtc_api_t::interruptEnable.
 *
 * @retval SSP_SUCCESS               Alarm interrupt enabled.
 * @retval SSP_ERR_ASSERTION         Invalid p_api_ctrl or p_ctrl->p_reg member pointed by p_api_ctrl pointer.
 * @retval SSP_ERR_IRQ_BSP_DISABLED  User IRQ parameter not valid.
 * @retval SSP_ERR_INVALID_ARGUMENT  Invalid IRQ event.
 * @retval SSP_ERR_TIMEOUT           IRQ enable operation timed out.
 * @retval SSP_ERR_NOT_OPEN          Driver not open already for operation.
 **********************************************************************************************************************/
ssp_err_t R_RTC_IrqEnable (rtc_ctrl_t * const p_api_ctrl, rtc_event_t event)
{
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) p_api_ctrl;

#if RTC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(p_ctrl);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
    RTC_ERROR_RETURN(RTC_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    ssp_err_t err = SSP_SUCCESS;

    switch (event)
    {
        case RTC_EVENT_ALARM_IRQ:
            RTC_ERROR_RETURN(SSP_INVALID_VECTOR != p_ctrl->alarm_irq, SSP_ERR_IRQ_BSP_DISABLED);
            err = r_rtc_alarm_irq_set(p_ctrl, true);
            break;
        case RTC_EVENT_PERIODIC_IRQ:
            RTC_ERROR_RETURN(SSP_INVALID_VECTOR != p_ctrl->periodic_irq, SSP_ERR_IRQ_BSP_DISABLED);
            err = r_rtc_periodic_irq_set(p_ctrl, true);
            break;
        case RTC_EVENT_CARRY_IRQ:
            RTC_ERROR_RETURN(SSP_INVALID_VECTOR != p_ctrl->carry_irq, SSP_ERR_IRQ_BSP_DISABLED);
            err = r_rtc_carry_irq_set(p_ctrl, true);
            break;
        default:
            err = SSP_ERR_INVALID_ARGUMENT;
            break;
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief  Disable the alarm interrupt.
 *
 *  Implements rtc_api_t::interruptDisable.
 *
 * @retval SSP_SUCCESS               Alarm interrupt disabled.
 * @retval SSP_ERR_ASSERTION         Invalid p_api_ctrl or p_ctrl->p_reg member pointed by p_api_ctrl pointer.
 * @retval SSP_ERR_IRQ_BSP_DISABLED  User IRQ parameter not valid
 * @retval SSP_ERR_INVALID_ARGUMENT  Invalid IRQ event
 * @retval SSP_ERR_TIMEOUT           IRQ disable operation timed out.
 * @retval SSP_ERR_NOT_OPEN          Driver not open already for operation.
 **********************************************************************************************************************/
ssp_err_t R_RTC_IrqDisable (rtc_ctrl_t * const p_api_ctrl, rtc_event_t event)
{
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) p_api_ctrl;
    uint32_t timeout = RTC_REG_UPDATE_TIMEOUT;
    SSP_PARAMETER_NOT_USED(timeout);  /* timeout is only used if interrupts are enabled. */

#if RTC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(p_ctrl);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
    RTC_ERROR_RETURN(RTC_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    ssp_err_t err = SSP_SUCCESS;

    switch (event)
    {
        case RTC_EVENT_ALARM_IRQ:
            RTC_ERROR_RETURN(SSP_INVALID_VECTOR != p_ctrl->alarm_irq, SSP_ERR_IRQ_BSP_DISABLED);
            err = r_rtc_alarm_irq_set(p_ctrl, false);
            break;
        case RTC_EVENT_PERIODIC_IRQ:
            RTC_ERROR_RETURN(SSP_INVALID_VECTOR != p_ctrl->periodic_irq, SSP_ERR_IRQ_BSP_DISABLED);
            err = r_rtc_periodic_irq_set(p_ctrl, false);
            break;
        case RTC_EVENT_CARRY_IRQ:
            RTC_ERROR_RETURN(SSP_INVALID_VECTOR != p_ctrl->carry_irq, SSP_ERR_IRQ_BSP_DISABLED);
            err = r_rtc_carry_irq_set(p_ctrl, false);
            break;
        default:
            err = SSP_ERR_INVALID_ARGUMENT;
            break;
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief  Set the periodic interrupt rate.
 *
 *  Implements rtc_api_t::periodicInterruptRateSet.
 *
 * @retval SSP_SUCCESS               The periodic interrupt rate was successfully set.
 * @retval SSP_ERR_ASSERTION         Invalid p_api_ctrl or p_ctrl->p_reg member pointed by p_api_ctrl pointer.
 * @retval SSP_ERR_TIMEOUT           Periodic interrupt rate get query timed out.
 * @retval SSP_ERR_NOT_OPEN          Driver not open already for operation.
 **********************************************************************************************************************/
ssp_err_t R_RTC_PeriodicIrqRateSet (rtc_ctrl_t * const p_api_ctrl, rtc_periodic_irq_select_t rate)
{
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) p_api_ctrl;
    uint32_t timeout = RTC_REG_UPDATE_TIMEOUT;

#if RTC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(p_ctrl);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
    RTC_ERROR_RETURN(RTC_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;
    HW_RTC_RTCPeriodicInterruptSelect(p_rtc_reg, rate);

    /* wait for the rate to set */
    while ((HW_RTC_RTCPeriodicInterruptRateGet(p_rtc_reg) != rate) && timeout)
    {
        timeout--;
    }

    RTC_ERROR_RETURN(0 != timeout, SSP_ERR_TIMEOUT);

    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief      This function returns information about the driver clock source
 *
 *  Implements rtc_api_t::infoGet
 *
 * @retval SSP_SUCCESS          Get information Successful.
 * @retval SSP_ERR_ASSERTION    Invalid p_api_ctrl, p_rtc_info or p_ctrl->p_reg member pointed by p_api_ctrl pointer.
 * @retval SSP_ERR_NOT_OPEN     Driver not open already for operation.
 **********************************************************************************************************************/
ssp_err_t R_RTC_InfoGet(rtc_ctrl_t * p_api_ctrl, rtc_info_t * p_rtc_info)
{
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) p_api_ctrl;
#if RTC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(NULL != p_ctrl);
    SSP_ASSERT(NULL != p_rtc_info);
    SSP_ASSERT(NULL != p_ctrl->p_reg);
    RTC_ERROR_RETURN(RTC_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif
    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;

    p_rtc_info->clock_source = p_ctrl->clock_source;
    p_rtc_info->status = (rtc_status_t) HW_RTC_CounterStartStopBitGet(p_rtc_reg);

    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief      This function sets time error adjustment mode
 *
 *  Implements rtc_api_t::errorAdjustmentModeSet
 *
 * @retval SSP_SUCCESS                 Time error adjustment mode set successful.
 * @retval SSP_ERR_ASSERTION           Invalid p_api_ctrl or error_adjustment_mode pointer.
 * @retval SSP_ERR_NOT_OPEN            Driver not open for operation.
 * @retval SSP_ERR_UNSUPPORTED         The clock source is not SubClock.
 * @retval SSP_ERR_INVALID_ARGUMENT    Invalid error adjustment period.
 * @retval SSP_ERR_TIMEOUT             Time error adjustment get query timed out.
 **********************************************************************************************************************/
ssp_err_t R_RTC_ErrorAdjustmentModeSet (rtc_ctrl_t * p_api_ctrl,
                                        rtc_error_adjustment_mode_cfg_t *p_error_adjustment_mode)
{
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) p_api_ctrl;

#if RTC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(p_ctrl);
    SSP_ASSERT(p_error_adjustment_mode);
    RTC_ERROR_RETURN(RTC_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;
    ssp_err_t err = SSP_SUCCESS;

    rtc_error_adjustment_mode_t adjustment_mode = p_error_adjustment_mode->adjustment_mode;
    rtc_error_adjustment_period_t adjustment_period = p_error_adjustment_mode->adjustment_period;

    /* Error adjustment is supported only if clock source is sub-clock */
    if (p_ctrl->clock_source != RTC_CLOCK_SOURCE_SUBCLK)
    {
        return SSP_ERR_UNSUPPORTED;
    }

    /* Validate adjustment mode and period */
    if (RTC_ERROR_ADJUSTMENT_MODE_MANUAL == adjustment_mode)
    {
        if (RTC_ERROR_ADJUSTMENT_PERIOD_NONE != adjustment_period)
        {
            return SSP_ERR_INVALID_ARGUMENT;
        }
        err = r_rtc_error_adjustment_mode_set_common(p_rtc_reg, adjustment_mode);
    }
    else
    {
        if (RTC_ERROR_ADJUSTMENT_PERIOD_NONE == adjustment_period)
        {
            return SSP_ERR_INVALID_ARGUMENT;
        }
        err = r_rtc_error_adjustment_mode_set_common(p_rtc_reg, adjustment_mode);
        RTC_ERROR_RETURN(SSP_SUCCESS == err, err);

        err = r_rtc_error_adjustment_period_set(p_rtc_reg, adjustment_period);
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief      This function sets time error adjustment
 *
 *  Implements rtc_api_t::errorAdjustmentSet
 *
 * @retval SSP_SUCCESS                 Time error adjustment successful.
 * @retval SSP_ERR_ASSERTION           Invalid p_api_ctrl or p_error_adjustment_config pointer.
 * @retval SSP_ERR_NOT_OPEN            Driver not open for operation.
 * @retval SSP_ERR_UNSUPPORTED         The clock source is not SubClock.
 * @retval SSP_ERR_INVALID_ARGUMENT    Invalid error adjustment value.
 * @retval SSP_ERR_TIMEOUT             Time error adjustment get query timed out.
 **********************************************************************************************************************/
ssp_err_t R_RTC_ErrorAdjustmentSet (rtc_ctrl_t * p_api_ctrl, rtc_error_adjustment_cfg_t *p_error_adjustment_config)
{
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) p_api_ctrl;

#if RTC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(p_ctrl);
    SSP_ASSERT(p_error_adjustment_config);
    RTC_ERROR_RETURN(RTC_OPEN == p_ctrl->open, SSP_ERR_NOT_OPEN);
#endif

    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;
    uint8_t error_adjustment = 0;
    uint32_t timeout = RTC_REG_UPDATE_TIMEOUT;

    rtc_error_adjustment_t adjustment_type = p_error_adjustment_config->adjustment_type;
    uint8_t adjustment_value = p_error_adjustment_config->adjustment_value;

    /* Error adjustment is supported only if clock source is sub-clock */
    if (p_ctrl->clock_source != RTC_CLOCK_SOURCE_SUBCLK)
    {
        return SSP_ERR_UNSUPPORTED;
    }

    /* Validate adjustment value is within HW range */
    if (adjustment_value <= RTC_MAX_ERROR_ADJUSTMENT_VALUE)
    {
        error_adjustment = (uint8_t) ((uint8_t)(((uint8_t) adjustment_type) << 6U) |
                                     (RTC_MAX_ERROR_ADJUSTMENT_VALUE & adjustment_value));
        HW_RTC_ClkErrorAdjustmentSet(p_rtc_reg, error_adjustment);

        /* wait for the error adjustment to set */
        while ((HW_RTC_ClkErrorAdjustmentGet(p_rtc_reg) != error_adjustment) && timeout)
        {
            timeout--;
        }

        RTC_ERROR_RETURN(0U != timeout, SSP_ERR_TIMEOUT);

        return SSP_SUCCESS;
    }

    return SSP_ERR_INVALID_ARGUMENT;
}

/*******************************************************************************************************************//**
 * @brief      Get driver version based on compile time macros.
 *
 *  Implements rtc_api_t::versionGet
 *
 * @retval     SSP_SUCCESS          Successful close.
 * @retval     SSP_ERR_ASSERTION    The parameter p_version is NULL.
 **********************************************************************************************************************/
ssp_err_t R_RTC_VersionGet (ssp_version_t * p_version)
{
#if RTC_CFG_PARAM_CHECKING_ENABLE
    SSP_ASSERT(p_version);
#endif

    p_version->version_id = s_rtc_version.version_id;

    return SSP_SUCCESS;
}

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief  Clear the start bit
 *
 * @retval SSP_SUCCESS           start bit cleared
 * @retval SSP_ERR_TIMEOUT       start bit not cleared
 **********************************************************************************************************************/
static ssp_err_t r_rtc_start_bit_clear (R_RTC_Type * p_rtc_reg)
{

    uint32_t timeout = RTC_REG_UPDATE_TIMEOUT;

    HW_RTC_CounterStop(p_rtc_reg);

    /* Wait for the START bit to become 0 */
    while ((timeout) && (HW_RTC_CounterStartStopBitGet(p_rtc_reg)))
    {
        timeout--;
    }

    RTC_ERROR_RETURN(0 != timeout, SSP_ERR_TIMEOUT);

    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Set the start bit
 *
 * @retval SSP_SUCCESS           start bit set
 * @retval SSP_ERR_TIMEOUT       start bit not set
 **********************************************************************************************************************/
static ssp_err_t r_rtc_start_bit_set (R_RTC_Type * p_rtc_reg)
{

    uint32_t timeout = RTC_REG_UPDATE_TIMEOUT;

    HW_RTC_CounterStart(p_rtc_reg);

    /* Wait for the START bit to become 0 */
    while (timeout && (!HW_RTC_CounterStartStopBitGet(p_rtc_reg)))
    {
        timeout--;
    }

    RTC_ERROR_RETURN(0 != timeout, SSP_ERR_TIMEOUT);

    return SSP_SUCCESS;
}


/*******************************************************************************************************************//**
 * @brief  Set the hour mode
 *
 * @retval SSP_SUCCESS           hour mode bit set
 * @retval SSP_ERR_TIMEOUT       hour mode bit not set
 **********************************************************************************************************************/

static ssp_err_t r_rtc_hour_mode_set (R_RTC_Type * p_rtc_reg)
{

    uint32_t timeout = RTC_REG_UPDATE_TIMEOUT;

    /* Force RTC into 24 hour mode. */
    HW_RTC_Counter24HourSet(p_rtc_reg);

    /*Wait for the bit to set*/
    while ((timeout) && (!HW_RTC_Counter24HourGet(p_rtc_reg)))
    {
        timeout--;
    }

    RTC_ERROR_RETURN(0U != timeout, SSP_ERR_TIMEOUT);

    return SSP_SUCCESS;

}

/*******************************************************************************************************************//**
 * @brief  Perform a software reset
 *
 * @retval SSP_SUCCESS           software reset complete
 * @retval SSP_ERR_TIMEOUT       software reset not complete
 **********************************************************************************************************************/
static ssp_err_t r_rtc_software_reset (R_RTC_Type * p_rtc_reg)
{

    uint32_t timeout = RTC_REG_UPDATE_TIMEOUT;

    HW_RTC_SWReset(p_rtc_reg);

    /* Wait for the reset bit to become 0 */
    while ((timeout) && (HW_RTC_SWResetBitGet(p_rtc_reg)))
    {
        timeout--;
    }

    RTC_ERROR_RETURN(0 != timeout, SSP_ERR_TIMEOUT);

    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  Set the RTC clock source
 *
 * @retval SSP_SUCCESS           RTC clock source set
 * @retval SSP_ERR_TIMEOUT       status check for counter mode or reset timed out
 **********************************************************************************************************************/
static ssp_err_t r_rtc_set_clock_source (R_RTC_Type * p_rtc_reg, rtc_instance_ctrl_t *p_ctrl)
{
    ssp_err_t         error;
    uint32_t timeout = RTC_REG_UPDATE_TIMEOUT;

    /* Start the sub-clock */
    if (RTC_CLOCK_SOURCE_SUBCLK == p_ctrl->clock_source)
    {
        cgc_clock_cfg_t pll_cfg;
        g_cgc_on_cgc.clockStart(CGC_CLOCK_SUBCLOCK, &pll_cfg);
    }

    /* Select the count source */
    HW_RTC_ClockSourceSet(p_rtc_reg, p_ctrl->clock_source);

    /* Supply 6 clocks of the count source (LOCO, 183us, 32kHZ). */
    if (RTC_CLOCK_SOURCE_SUBCLK == p_ctrl->clock_source)
    {
        /* According to HM a fixed time for stabilization is required for oscillation to become stable after selecting the sub clock operation with the
        SOSTP bit. */
        R_BSP_SoftwareDelay(100U, BSP_DELAY_UNITS_MILLISECONDS);
    }
    else
    {
        R_BSP_SoftwareDelay(190U, BSP_DELAY_UNITS_MICROSECONDS);
    }

    /* Set the START bit to 0 */
    error = r_rtc_start_bit_clear(p_rtc_reg);

    if (SSP_SUCCESS == error)
    {
        /* Set the hour mode bit */
    	error = r_rtc_hour_mode_set(p_rtc_reg);

    	RTC_ERROR_RETURN(SSP_SUCCESS == error, error);

        if (RTC_CLOCK_SOURCE_LOCO == p_ctrl->clock_source)
        {
            /* Always set RFC16 to 0 as per UM */
            HW_RTC_FrequencyRegisterHSet(p_rtc_reg, 0);

            /* Set clock error adjustment values */
            HW_RTC_FrequencyRegisterLSet(p_rtc_reg, (uint16_t) 0x00FFU);
        }

        /* Select count mode */
        HW_RTC_CounterModeSet(p_rtc_reg, RTC_CALENDAR_MODE);

        /* Wait for the CNTMD bit to become 0 */
        while ((timeout) && (HW_RTC_CounterModeGet(p_rtc_reg)))
        {
            timeout--;
        }

        RTC_ERROR_RETURN(0 != timeout, SSP_ERR_TIMEOUT);

        /* Execute RTC software reset */
        error = r_rtc_software_reset(p_rtc_reg);
    }

    return error;
}

/*******************************************************************************************************************//**
 * @brief  check if timeout set else enable passed NVIC interrupt.
 *
 *  Implements a helper function
 *
 * @retval SSP_SUCCESS    Calendar counter stopped.
 **********************************************************************************************************************/
static ssp_err_t r_rtc_nvic_enable_irq (IRQn_Type nvic_interrupt, uint32_t irq_en)
{
    if(((uint32_t) TRUE) == irq_en)
    {
        R_BSP_IrqStatusClear(nvic_interrupt); /* Clear IRQ status */
        NVIC_ClearPendingIRQ(nvic_interrupt); /* Clear Pending IRQ in the NVIC */
        NVIC_EnableIRQ(nvic_interrupt);       /* Enable this interrupt in the NVIC */
    }
    else
    {
        NVIC_DisableIRQ(nvic_interrupt);  /* Disable this interrupt in the NVIC */
    }
    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief  get IRQ from event info to set IRQ priority and control info for IRQ handler .
 *
 *  Implements a helper function
 *
 * @retval SSP_SUCCESS  Successful configuration
 **********************************************************************************************************************/
static ssp_err_t r_rtc_config_rtc_interrupts(fmi_event_info_t *event_info, rtc_instance_ctrl_t * p_ctrl, rtc_cfg_t const * const p_cfg, ssp_feature_t * ssp_feature)
{
    ssp_vector_info_t * p_vector_info;
    g_fmi_on_fmi.eventInfoGet(ssp_feature, SSP_SIGNAL_RTC_PERIOD, event_info);
    p_ctrl->periodic_irq = event_info->irq;
    if (SSP_INVALID_VECTOR != p_ctrl->periodic_irq)
    {
        R_SSP_VectorInfoGet(p_ctrl->periodic_irq, &p_vector_info);
        NVIC_SetPriority(p_ctrl->periodic_irq, p_cfg->periodic_ipl);
        *(p_vector_info->pp_ctrl) = p_ctrl;
    }
    g_fmi_on_fmi.eventInfoGet(ssp_feature, SSP_SIGNAL_RTC_ALARM, event_info);
    p_ctrl->alarm_irq = event_info->irq;
    if (SSP_INVALID_VECTOR != p_ctrl->alarm_irq)
    {
        R_SSP_VectorInfoGet(p_ctrl->alarm_irq, &p_vector_info);
        NVIC_SetPriority(p_ctrl->alarm_irq, p_cfg->alarm_ipl);
        *(p_vector_info->pp_ctrl) = p_ctrl;
    }
    g_fmi_on_fmi.eventInfoGet(ssp_feature, SSP_SIGNAL_RTC_CARRY, event_info);
    p_ctrl->carry_irq = event_info->irq;
    if (SSP_INVALID_VECTOR != p_ctrl->carry_irq)
    {
        R_SSP_VectorInfoGet(p_ctrl->carry_irq, &p_vector_info);
        NVIC_SetPriority(p_ctrl->carry_irq, p_cfg->carry_ipl);
        *(p_vector_info->pp_ctrl) = p_ctrl;
    }
    return SSP_SUCCESS;
}
/*******************************************************************************************************************//**
 * @brief enable alarm irq if valid
 *
 * Implements a helper function
 * @retval SSP_SUCCESS        Alarm IRQ enabled
 * @retval SSP_ERR_TIMEOUT    check for Alarm IRQ enable bit timed out
 **********************************************************************************************************************/
static ssp_err_t r_rtc_enable_alarm_irq(rtc_instance_ctrl_t * p_ctrl, bool interrupt_enable_flag)
{
    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;

    /* Enable the RTC alarm interrupt request */
    if (interrupt_enable_flag)
    {
        uint32_t timeout = RTC_REG_UPDATE_TIMEOUT;
        HW_RTC_RTCAlarmIRQEnable(p_rtc_reg);

        /* wait for the AIE bit to show as set */
        while ((!HW_RTC_RTCAlarmIRQGet(p_rtc_reg)) && timeout)
        {
            timeout--;
        }

        RTC_ERROR_RETURN(0 != timeout, SSP_ERR_TIMEOUT);
    }

    /* Wait for 200us to ensure the alarm registers are updated */
    R_BSP_SoftwareDelay(200U, BSP_DELAY_UNITS_MICROSECONDS);

    if (p_ctrl->alarm_irq != SSP_INVALID_VECTOR)
    {
        /* Set the alarm flag to 0 */
        R_BSP_IrqStatusClear((IRQn_Type) p_ctrl->alarm_irq);

        /* Clear pending IRQ since the alarm interrupt may have been pended in NVIC while the alarm time was being set */
        NVIC_ClearPendingIRQ(p_ctrl->alarm_irq);

        /* Enable the ICU alarm interrupt request */
        NVIC_EnableIRQ(p_ctrl->alarm_irq);
    }
    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Helper function to enable or disable the carry interrupt
 *
 * @retval SSP_SUCCESS
 * @retval SSP_ERR_TIMEOUT
 **********************************************************************************************************************/
static ssp_err_t r_rtc_carry_irq_set (rtc_instance_ctrl_t * p_ctrl, bool carry_irq_enable_flag)
{
    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;
    uint32_t timeout = RTC_REG_UPDATE_TIMEOUT;

    /* Enable the RTC carry interrupt request */
    if (true == carry_irq_enable_flag)
    {
        HW_RTC_RTCCarryIRQEnable(p_rtc_reg);                   /* Enable this interrupt in the RTC block */
        while ((!HW_RTC_RTCCarryIRQGet(p_rtc_reg)) && timeout) /* wait for the bit to set */
        {
            timeout--;
        }
    }
    else
    {
        HW_RTC_RTCCarryIRQDisable(p_rtc_reg);                   /* Disable this interrupt in the RTC block */
        while ((HW_RTC_RTCCarryIRQGet(p_rtc_reg)) && timeout) /* wait for the bit to clear */
        {
            timeout--;
        }
    }
    if (!timeout)
    {
        SSP_ERROR_LOG((SSP_ERR_TIMEOUT), &g_module_name[0], &s_rtc_version);
        return SSP_ERR_TIMEOUT;
    }

    return r_rtc_nvic_enable_irq((IRQn_Type) p_ctrl->carry_irq, (uint32_t) carry_irq_enable_flag);;
}

/*******************************************************************************************************************//**
 * @brief Helper function to enable or disable the periodic interrupt
 *
 * @retval SSP_SUCCESS
 * @retval SSP_ERR_TIMEOUT
 **********************************************************************************************************************/
static ssp_err_t r_rtc_periodic_irq_set (rtc_instance_ctrl_t * p_ctrl, bool periodic_irq_enable_flag)
{
    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;
    uint32_t timeout = RTC_REG_UPDATE_TIMEOUT;

    /* Enable the RTC periodic interrupt request */
    if (true == periodic_irq_enable_flag)
    {
        HW_RTC_RTCPeriodicIRQEnable(p_rtc_reg);                   /* Enable this interrupt in the RTC block */
        while ((!HW_RTC_RTCPeriodicIRQGet(p_rtc_reg)) && timeout) /* wait for the bit to set */
        {
            timeout--;
        }
    }
    else
    {
        HW_RTC_RTCPeriodicIRQDisable(p_rtc_reg);                   /* Disable this interrupt in the RTC block */
        while ((HW_RTC_RTCCarryIRQGet(p_rtc_reg)) && timeout) /* wait for the bit to clear */
        {
            timeout--;
        }
    }
    if (!timeout)
    {

        SSP_ERROR_LOG((SSP_ERR_TIMEOUT), &g_module_name[0], &s_rtc_version);
        return SSP_ERR_TIMEOUT;
    }

    return r_rtc_nvic_enable_irq((IRQn_Type) p_ctrl->periodic_irq, (uint32_t) periodic_irq_enable_flag);;
}

/*******************************************************************************************************************//**
 * @brief Helper function to enable or disable the alarm interrupt
 *
 * @retval SSP_SUCCESS
 * @retval SSP_ERR_TIMEOUT
 **********************************************************************************************************************/
static ssp_err_t r_rtc_alarm_irq_set (rtc_instance_ctrl_t * p_ctrl, bool alarm_irq_enable_flag)
{
    R_RTC_Type * p_rtc_reg = (R_RTC_Type *) p_ctrl->p_reg;
    uint32_t timeout = RTC_REG_UPDATE_TIMEOUT;

    /* Enable the RTC alarm interrupt request */
    if (true == alarm_irq_enable_flag)
    {
        HW_RTC_RTCAlarmIRQEnable(p_rtc_reg);                   /* Enable this interrupt in the RTC block */
        while ((!HW_RTC_RTCAlarmIRQGet(p_rtc_reg)) && timeout) /* wait for the bit to set */
        {
            timeout--;
        }
    }
    else
    {
        HW_RTC_RTCAlarmIRQDisable(p_rtc_reg);                   /* Disable this interrupt in the RTC block */
        while ((HW_RTC_RTCAlarmIRQGet(p_rtc_reg)) && timeout) /* wait for the bit to clear */
        {
            timeout--;
        }
    }
    if (!timeout)
    {
        SSP_ERROR_LOG((SSP_ERR_TIMEOUT), &g_module_name[0], &s_rtc_version);
        return SSP_ERR_TIMEOUT;
    }

    return r_rtc_nvic_enable_irq((IRQn_Type) p_ctrl->alarm_irq, (uint32_t) alarm_irq_enable_flag);;
}

#if RTC_CFG_PARAM_CHECKING_ENABLE
/*******************************************************************************************************************//**
 * @brief validate time and date fields of time parameter fields
 * Checking for seconds, minutes, hours are valid values by calling sub-function time validate.
 * Checking for year, month, day of the week and day of a month are valid values by calling sub-function
 * date validate.
 * @retval SSP_SUCCESS                    validation successful
 * @retval SSP_ERR_INVALID_ARGUMENT       invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static ssp_err_t r_rtc_time_and_date_validate(rtc_time_t * p_time)
{
    ssp_err_t err = SSP_SUCCESS;
    err = r_rtc_time_validate(p_time);
    RTC_ERROR_RETURN(err == SSP_SUCCESS, err);
    err = r_rtc_date_validate(p_time);
    RTC_ERROR_RETURN(err == SSP_SUCCESS, err);
    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief validate time fields of time type parameter
 * Checking for the seconds, minutes, hours values for valid specified range.
 * Seconds 0 to 59.
 * Minutes 0 to 59.
 * Hours   0 to 23.
 * @retval SSP_SUCCESS                    validation successful
 * @retval SSP_ERR_INVALID_ARGUMENT       invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static ssp_err_t r_rtc_time_validate(rtc_time_t * p_time)
{
    ssp_err_t err;
    err = SSP_SUCCESS;
    if (  (p_time->tm_sec  < 0) || (p_time->tm_sec  > RTC_SECONDS_IN_A_MINUTE) ||
          (p_time->tm_min  < 0) || (p_time->tm_min  > RTC_MINUTES_IN_A_HOUR) ||
          (p_time->tm_hour < 0) || (p_time->tm_hour > RTC_HOURS_IN_A_DAY) )
    {
        err = SSP_ERR_INVALID_ARGUMENT;
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief validate date fields of time type parameter
 * validating r_rtc date fields and setting day of a Week using Zeller's congruence.
 * Checking for year, month, day of the week and day of a month are valid values.
 * Leap year validation and Week of the day is calculated and updated in rtc time.
 * Day of week between 0 to 6
 * Day between 1 to 31
 * Month between 0 to 11 as per standard time.h, There's a mismatch between hardware configuration,
 * UM indicates that "A value from 01 through 12 (in BCD) can be specified" for Month Counter register in the RTC.
 * This difference will be taken care in the Set and Get functions.
 *
 * As per HW manual, value of Year is between 0 to 99, the RTC has a 100 year calendar from 2000 to 2099.
 * But as per C standards, tm_year is years since 1900.
 * A sample year set in an application would be like time.tm_year = 2017-1900; (to set year 2017)
 * Since RTC API follows the Date and time structure defined in C standard library <time.h>, the valid value of year is
 * between 100 and 199, which will be internally converted to HW required value.
 *
 * @retval SSP_SUCCESS                    validation successful
 * @retval SSP_ERR_INVALID_ARGUMENT       invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static ssp_err_t r_rtc_date_validate(rtc_time_t * p_time)
{
    uint8_t day_of_week;
    uint8_t num_days_month;
    uint8_t day_of_a_month;
    uint8_t temp_month;
    uint16_t temp_year;

    day_of_a_month   = (uint8_t)p_time->tm_mday;
    temp_month = (uint8_t)(p_time->tm_mon + RTC_TIME_H_MONTH_OFFSET);
    /* The valid value of year is between 100 to 199, The RTC has a 100 year calendar from 2000 to 2099
     * to match the starting year 2000, a sample year offset(1900) is added like 117 + 1900 = 2017*/
    temp_year  = (uint16_t)(p_time->tm_year + RTC_TIME_H_YEAR_OFFSET);

    /* Checking the error condition for year and months values, here valid value of year is between 100 to 199
       and for month 0 to 11*/
    if ( (p_time->tm_year < RTC_YEAR_VALUE_MIN) || (p_time->tm_year > RTC_YEAR_VALUE_MAX) ||
            (p_time->tm_mon < 0) ||(p_time->tm_mon > RTC_MONTHS_IN_A_YEAR) )
    {
        return SSP_ERR_INVALID_ARGUMENT;
    }
    /*For particular valid month, number of days in a month is updated */
    num_days_month = days_in_months[p_time->tm_mon];

    /* Checking for February month and Conditions for Leap year : Every fourth year is a leap year,
       The RTC has a 100 year calendar from 2000 to 2099  */
    if ((RTC_FEBRUARY_MONTH == temp_month) && ((temp_year % 4U) == 0))
    {
        num_days_month = ((uint8_t)RTC_LAST_DAY_OF_LEAP_FEB_MONTH);
    }
    /* Checking for day of a month values for valid range */
    if ((p_time->tm_mday >= RTC_FIRST_DAY_OF_A_MONTH) && (day_of_a_month <= num_days_month))
    {
        /*For the Gregorian calendar, Zeller's congruence formulas is
         * h = ( q + [13(m+1)/5] + Y + [Y/4] - [Y/100] + [Y/400])mod 7 (mod : modulo)
         * h is the day of the week , m is the month (3 = March, 4 = April, 5 = May, ..., 14 = February)
         * Y is year, which is Y - 1 during January and February */
        if (temp_month < RTC_MARCH_MONTH)
        {
            temp_month = (uint8_t)(temp_month + 12U);
            --temp_year;
        }

        day_of_week = (uint8_t)((((uint16_t)p_time->tm_mday) + (uint16_t)((13U * (temp_month + 1U)) / 5U) +
                      (uint16_t)((temp_year + (temp_year / 4U)) - (uint16_t)RTC_ZELLER_ALGM_CONST_FIFTEEN))
                      % (uint16_t)7U);

        /* Day of week between 0 to 6 :- Sunday to Saturday */
        /* d = (h + 6)mod 7 (mod : modulo) */
        p_time->tm_wday = (int32_t)((day_of_week + 6U) % 7U);
        return SSP_SUCCESS;
    }

    return SSP_ERR_INVALID_ARGUMENT;
}

/*******************************************************************************************************************//**
 * @brief Validate alarm time and date of Alarm time type parameter
 * Checking for alarm enable bit with the seconds, minutes, hours are valid values.
 * Checking for alarm enable bit with year, month, day of the week and day of a month are valid values.
 * If alarm enable bit is set for year, month, and day of a month for valid range, Week of the day is
 * calculated and updated in alarm time.
 * @retval SSP_SUCCESS                    validation successful
 * @retval SSP_ERR_INVALID_ARGUMENT       invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static ssp_err_t r_rtc_alarm_time_and_date_validate(rtc_alarm_time_t * p_time)
{
    ssp_err_t err = SSP_SUCCESS;
    err = r_rtc_alarm_time_validate(p_time);
    RTC_ERROR_RETURN(err == SSP_SUCCESS, err);

    /* Checking for alarm enable bit for year, month, day of the month */
    if((TRUE == p_time->year_match) && (TRUE == p_time->mon_match) && (TRUE == p_time->mday_match))
    {
        err = r_rtc_date_validate(&p_time->time);
        RTC_ERROR_RETURN(err == SSP_SUCCESS, err);
    }
    else
    {
        err = r_rtc_alarm_month_and_year_validate(p_time);
        RTC_ERROR_RETURN(err == SSP_SUCCESS, err);
        err = r_rtc_alarm_dayofmonth_and_dayofweek_validate(p_time);
        RTC_ERROR_RETURN(err == SSP_SUCCESS, err);
    }
    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Validate alarm time fields of Alarm time type parameter
 * Checking for alarm enable bit with the seconds, minutes, hours value for valid specified range.
 * Seconds 0 to 59.
 * Minutes 0 to 59.
 * Hours   0 to 23.
 * @retval SSP_SUCCESS                    validation successful
 * @retval SSP_ERR_INVALID_ARGUMENT       invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static ssp_err_t r_rtc_alarm_time_validate(rtc_alarm_time_t * p_time)
{
    ssp_err_t err;
    err = SSP_SUCCESS;
    if ( ((TRUE == p_time->sec_match) &&
            ((p_time->time.tm_sec < 0) || (p_time->time.tm_sec > RTC_SECONDS_IN_A_MINUTE))) ||
            ((TRUE == p_time->min_match) &&
                    ((p_time->time.tm_min < 0) || (p_time->time.tm_min > RTC_MINUTES_IN_A_HOUR))) ||
                    ((TRUE == p_time->hour_match) &&
                            ((p_time->time.tm_hour < 0) || (p_time->time.tm_hour > RTC_HOURS_IN_A_DAY))) )
    {
        err = SSP_ERR_INVALID_ARGUMENT;
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief validate alarm month and year of time type parameter
 * Checking for alarm enable bit with month and year value for valid specified range.
 * Month : 0 to 11.
 * Year  : 100 to 199.
 * Since RTC API follows the Date and time structure defined in C standard library <time.h>, the valid value of year is
 * between 100 to 199.
 * @retval SSP_SUCCESS                    validation successful
 * @retval SSP_ERR_INVALID_ARGUMENT       invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static ssp_err_t r_rtc_alarm_month_and_year_validate(rtc_alarm_time_t * p_time)
{
    ssp_err_t err;
    err = SSP_SUCCESS;
    if ( ((TRUE == p_time->mon_match) &&
            ((p_time->time.tm_mon < 0) || (p_time->time.tm_mon > RTC_MONTHS_IN_A_YEAR))) ||
            ((TRUE == p_time->year_match) &&
                    ((p_time->time.tm_year < RTC_YEAR_VALUE_MIN) || (p_time->time.tm_year > RTC_YEAR_VALUE_MAX))) )
    {
        err = SSP_ERR_INVALID_ARGUMENT;
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief Validate alarm day of a month and day of the week of time type parameter
 * Checking for alarm enable bit with day of a month and day of the week values for valid specified range.
 * Day of a month  : 1 to 31.
 * Day of the week : 0 to 6.
 * If alarm enable bit is set for particular valid month, number of days in a month is updated from that particular
 * month, by default 31 days in a month and for February month days are considered as 29 days in a month.
 *
 * @retval SSP_SUCCESS                    validation successful
 * @retval SSP_ERR_INVALID_ARGUMENT       invalid field in rtc_time_t structure
 **********************************************************************************************************************/
static ssp_err_t r_rtc_alarm_dayofmonth_and_dayofweek_validate(rtc_alarm_time_t * p_time)
{
    ssp_err_t err;
    uint8_t num_days_month;
    uint8_t day_of_a_month;

    day_of_a_month = (uint8_t)p_time->time.tm_mday;
    err = SSP_SUCCESS;

    /* checking for alarm enable bit of valid month */
    if (TRUE == p_time->mon_match)
    {
        /* Checking condition for February month in time.h months start from 0 to 11, for February 1 */
        if ((RTC_FEBRUARY_MONTH - 1U) == p_time->time.tm_mon)
        {
            /*For February month, number of days are considered as 29 days */
            num_days_month = (uint8_t)RTC_LAST_DAY_OF_LEAP_FEB_MONTH;
        }
        else
        {
            /* For valid month, number of days in month is assigned*/
            num_days_month = days_in_months[p_time->time.tm_mon];
        }
    }
    else
    {
        /* default 31 days in a month*/
        num_days_month = (uint8_t)RTC_LAST_DAY_OF_A_MONTH;
    }

    if ( ((TRUE == p_time->mday_match) &&
            ((p_time->time.tm_mday < RTC_FIRST_DAY_OF_A_MONTH) || (day_of_a_month > num_days_month))) ||
            ((TRUE == p_time->dayofweek_match) &&
                    ((p_time->time.tm_wday < 0) || (p_time->time.tm_wday > RTC_DAYS_IN_A_WEEK))) )
    {
        err = SSP_ERR_INVALID_ARGUMENT;
    }
    return err;
}
#endif

/*******************************************************************************************************************//**
 * @brief Helper function to set time error adjustment mode
 *
 * @retval SSP_SUCCESS      time error adjustment mode set successful
 * @retval SSP_ERR_TIMEOUT  check for adjustment mode bit timed out
 **********************************************************************************************************************/
static ssp_err_t r_rtc_error_adjustment_mode_set_common (R_RTC_Type * p_rtc_reg, rtc_error_adjustment_mode_t mode)
{
    uint32_t timeout = RTC_REG_UPDATE_TIMEOUT;

    /* Clear error adjustment before configuring the error adjustment mode as per UM */
    HW_RTC_ClkErrorAdjustmentSet(p_rtc_reg, 0U);

    /* wait for the error adjustment to set */
    while ((0U != HW_RTC_ClkErrorAdjustmentGet(p_rtc_reg)) && timeout)
    {
        timeout--;
    }

    RTC_ERROR_RETURN(0U != timeout, SSP_ERR_TIMEOUT);

    /* Set the error adjustment mode */
    HW_RTC_ClkErrorAdjustmentModeSet(p_rtc_reg, mode);

    while ((mode != HW_RTC_ClkErrorAdjustmentModeGet(p_rtc_reg)) && timeout)
    {
        timeout--;
    }

    RTC_ERROR_RETURN(0U != timeout, SSP_ERR_TIMEOUT);

    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief Helper function to set time error adjustment period
 *
 * @retval SSP_SUCCESS      time error adjustment mode set successful
 * @retval SSP_ERR_TIMEOUT  check for adjustment mode bit timed out
 **********************************************************************************************************************/
static ssp_err_t r_rtc_error_adjustment_period_set (R_RTC_Type * p_rtc_reg, rtc_error_adjustment_period_t period)
{
    uint32_t timeout = RTC_REG_UPDATE_TIMEOUT;

    HW_RTC_ClkErrorAdjustmentPeriodSet(p_rtc_reg, period);

    while ((HW_RTC_ClkErrorAdjustmentPeriodGet(p_rtc_reg) != period) && timeout)
    {
        timeout--;
    }

    RTC_ERROR_RETURN(0U != timeout, SSP_ERR_TIMEOUT);

    return SSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief      RTC Alarm ISR.
 *
 * Saves context if RTOS is used, stops the timer if one-shot mode, clears interrupts, calls callback if one was
 * provided in the open function, and restores context if RTOS is used.
 **********************************************************************************************************************/
/* @cond SKIP */
void rtc_alarm_isr (void)
{
    /* Save context if RTOS is used */
    SF_CONTEXT_SAVE

    ssp_vector_info_t * p_vector_info = NULL;
    R_SSP_VectorInfoGet(R_SSP_CurrentIrqGet(), &p_vector_info);
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) *(p_vector_info->pp_ctrl);

    /* Clear the IR flag in the ICU */
    R_BSP_IrqStatusClear (R_SSP_CurrentIrqGet());

    /* Call the callback routine if one is available */
    if ((NULL != p_ctrl) && (NULL != p_ctrl->p_callback))
    {
        rtc_callback_args_t rtc_context_data;
        rtc_context_data.event     = RTC_EVENT_ALARM_IRQ;
        rtc_context_data.p_context = p_ctrl->p_context;
        p_ctrl->p_callback(&rtc_context_data);
    }

    /* Restore context if RTOS is used */
    SF_CONTEXT_RESTORE
} /* End of function rtc_alarm_isr */

/*******************************************************************************************************************//**
 * @brief      RTC Periodic ISR.
 *
 * Saves context if RTOS is used, stops the timer if one-shot mode, clears interrupts, calls callback if one was
 * provided in the open function, and restores context if RTOS is used.
 **********************************************************************************************************************/
void rtc_period_isr (void)
{
    /* Save context if RTOS is used */
    SF_CONTEXT_SAVE

    ssp_vector_info_t * p_vector_info = NULL;
    R_SSP_VectorInfoGet(R_SSP_CurrentIrqGet(), &p_vector_info);
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) *(p_vector_info->pp_ctrl);

    /* Clear the IR flag in the ICU */
    R_BSP_IrqStatusClear (R_SSP_CurrentIrqGet());

    /* Call the callback routine if one is available */
    if ((NULL != p_ctrl) && (NULL != p_ctrl->p_callback))
    {
        rtc_callback_args_t rtc_context_data;
        rtc_context_data.event     = RTC_EVENT_PERIODIC_IRQ;
        rtc_context_data.p_context = p_ctrl->p_context;
        p_ctrl->p_callback(&rtc_context_data);
    }

    /* Restore context if RTOS is used */
    SF_CONTEXT_RESTORE
} /* End of function rtc_period_isr */

/*******************************************************************************************************************//**
 * @brief      RTC Carry ISR.
 *
 * Saves context if RTOS is used, clears interrupts, calls callback if one was
 * provided in the open function, and restores context if RTOS is used.
 **********************************************************************************************************************/
void rtc_carry_isr (void)
{
    /* Save context if RTOS is used */
    SF_CONTEXT_SAVE

    ssp_vector_info_t * p_vector_info = NULL;
    R_SSP_VectorInfoGet(R_SSP_CurrentIrqGet(), &p_vector_info);
    rtc_instance_ctrl_t * p_ctrl = (rtc_instance_ctrl_t *) *(p_vector_info->pp_ctrl);

    /* Clear the IR flag in the ICU */
    R_BSP_IrqStatusClear (R_SSP_CurrentIrqGet());

    if (NULL != p_ctrl)
    {
        p_ctrl->carry_isr_triggered = true;

        /* Call the callback routine if one is available and carry callback is not suppressed */
        if ((NULL != p_ctrl->p_callback) && (false == p_ctrl->suppress_carry_event_callback))
        {
            rtc_callback_args_t rtc_context_data;
            rtc_context_data.event     = RTC_EVENT_CARRY_IRQ;
            rtc_context_data.p_context = p_ctrl->p_context;
            p_ctrl->p_callback(&rtc_context_data);
        }
    }
    /* Restore context if RTOS is used */
    SF_CONTEXT_RESTORE
} /* End of function rtc_carry_isr */

/* @endcond */

/*******************************************************************************************************************//**
 * @brief      Convert decimal to BCD
 *
 **********************************************************************************************************************/
static uint8_t rtc_dec_to_bcd (uint8_t to_convert)
{
    return (uint8_t) ((((to_convert / (uint8_t) 10) << 4) & (uint8_t) 0xF0) | (to_convert % (uint8_t) 10));
}

/*******************************************************************************************************************//**
 * @brief      Convert  BCD to decimal
 *
 **********************************************************************************************************************/
static uint8_t rtc_bcd_to_dec (uint8_t to_convert)
{
    return (uint8_t) ((((to_convert & (uint8_t) 0xF0) >> 4) * (uint8_t) 10) + (to_convert & (uint8_t) 0x0F));
}
/*******************************************************************************************************************//**
 * @} (end addtpgroup RTC)
 **********************************************************************************************************************/
