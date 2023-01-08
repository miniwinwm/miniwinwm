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
 * File Name    : hw_rtc_common.h
 * Description  : Real-Time Clock (RTC) Module hardware common header file.
 **********************************************************************************************************************/

#ifndef HW_RTC_COMMON_H
#define HW_RTC_COMMON_H

/**********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define RTC_RHRCNT_HOUR_MASK (0x3f)
#define COMPARE_ENB_BIT      (7U)
/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Set the RTC clock source
 * @param  clock_source    The clock source
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_ClockSourceSet (R_RTC_Type * p_rtc_reg, rtc_clock_source_t clock_source)
{
    p_rtc_reg->RCR4_b.RCKSEL = clock_source;
}

/*******************************************************************************************************************//**
 * Get the RTC clock source
 * @return  The clock source
 **********************************************************************************************************************/
__STATIC_INLINE rtc_clock_source_t HW_RTC_ClockSourceGet (R_RTC_Type * p_rtc_reg)
{
    return (rtc_clock_source_t) p_rtc_reg->RCR4_b.RCKSEL;
}

/*******************************************************************************************************************//**
 * Start the counter
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_CounterStart (R_RTC_Type * p_rtc_reg)
{
    p_rtc_reg->RCR2_b.START = 1U;
}

/*******************************************************************************************************************//**
 * Stopt the counter
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_CounterStop (R_RTC_Type * p_rtc_reg)
{
    p_rtc_reg->RCR2_b.START = 0U;
}

/*******************************************************************************************************************//**
 * Get the state of the start bit
 * @return  The start bit
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_RTC_CounterStartStopBitGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RCR2_b.START;
}

/*******************************************************************************************************************//**
 * Set the lower half of the frequency
 * @param  value    The lower half of the frequency
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_FrequencyRegisterLSet (R_RTC_Type * p_rtc_reg, uint16_t value)
{
    p_rtc_reg->RFRL = value & 0x1ffU;
}

/*******************************************************************************************************************//**
 * Set the upper half of the frequency
 * @param  value    The upper half of the frequency
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_FrequencyRegisterHSet (R_RTC_Type * p_rtc_reg, uint16_t value)
{
    p_rtc_reg->RFRH = value & 0x01U;
}

/*******************************************************************************************************************//**
 * Get the lower half of the frequency
 * @return  The lower half of the frequency
 **********************************************************************************************************************/
__STATIC_INLINE uint16_t HW_RTC_FrequencyRegisterLGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RFRL;
}

/*******************************************************************************************************************//**
 * Set the counter mode
 * @param  mode    The counter mode
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_CounterModeSet (R_RTC_Type * p_rtc_reg, rtc_count_mode_t mode)
{
    p_rtc_reg->RCR2_b.CNTMD = mode;
}

/*******************************************************************************************************************//**
 * Get the counter mode
 * @return    The counter mode
 **********************************************************************************************************************/
__STATIC_INLINE rtc_count_mode_t HW_RTC_CounterModeGet (R_RTC_Type * p_rtc_reg)
{
    return (rtc_count_mode_t) p_rtc_reg->RCR2_b.CNTMD;
}

/*******************************************************************************************************************//**
 * Set the 24 hour mode
**********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_Counter24HourSet (R_RTC_Type * p_rtc_reg)
{
    p_rtc_reg->RCR2_b.HR24 = 1;

}

/*******************************************************************************************************************//**
 * Get the 24 hour mode
**********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_RTC_Counter24HourGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RCR2_b.HR24;
}

/*******************************************************************************************************************//**
 * Perform a software reset
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_SWReset (R_RTC_Type * p_rtc_reg)
{
    p_rtc_reg->RCR2_b.RESET = 1;
}

/*******************************************************************************************************************//**
 * Get the state of the reset bit
 * @return    the state of the reset bit
 **********************************************************************************************************************/
__STATIC_INLINE bool HW_RTC_SWResetBitGet (R_RTC_Type * p_rtc_reg)
{
    return (bool) p_rtc_reg->RCR2_b.RESET;
}

/*******************************************************************************************************************//**
 * Set the seconds field
 * @param  second    the seconds field
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_SecondSet (R_RTC_Type * p_rtc_reg, uint8_t second)
{
    p_rtc_reg->RSECCNT = second;
}

/*******************************************************************************************************************//**
 * Set the minute field
 * @param  minute    the minute field
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_MinuteSet (R_RTC_Type * p_rtc_reg, uint8_t minute)
{
    p_rtc_reg->RMINCNT = minute;
}

/*******************************************************************************************************************//**
 * Set the hour field
 * @param  hour    the hour field
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_HourSet (R_RTC_Type * p_rtc_reg, uint8_t hour)
{
    p_rtc_reg->RHRCNT = hour & RTC_RHRCNT_HOUR_MASK;
}

/*******************************************************************************************************************//**
 * Set the PM bit
 * @return      the PM bit
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_PMSet (R_RTC_Type * p_rtc_reg, bool PM_bit)
{
    p_rtc_reg->RHRCNT_b.PM = (uint8_t) PM_bit;
}

/*******************************************************************************************************************//**
 * Set the dayofweek field
 * @param  dayofweek    the dayofweek field
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_DayOfWeekSet (R_RTC_Type * p_rtc_reg, uint8_t dayofweek)
{
    p_rtc_reg->RWKCNT = dayofweek;
}

/*******************************************************************************************************************//**
 * Set the dayofmonth field
 * @param  dayofmonth    the dayofmonth field
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_DayOfMonthSet (R_RTC_Type * p_rtc_reg, uint8_t dayofmonth)
{
    p_rtc_reg->RDAYCNT = dayofmonth;
}

/*******************************************************************************************************************//**
 * Set the month field
 * @param  month    the month field
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_MonthSet (R_RTC_Type * p_rtc_reg, uint8_t month)
{
    p_rtc_reg->RMONCNT =    month;
}

/*******************************************************************************************************************//**
 * Set the year field
 * @param  year    the year field
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_YearSet (R_RTC_Type * p_rtc_reg, uint8_t year)
{
    p_rtc_reg->RYRCNT = year;
}

/*******************************************************************************************************************//**
 * Get the second field
 * @return      the second field
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_RTC_SecondGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RSECCNT;
}

/*******************************************************************************************************************//**
 * Get the minute field
 * @return      the minute field
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_RTC_MinuteGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RMINCNT;
}

/*******************************************************************************************************************//**
 * Get the hour field
 * @return      the hour field
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_RTC_HourGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RHRCNT & RTC_RHRCNT_HOUR_MASK;
}

/*******************************************************************************************************************//**
 * Get the PM bit
 * @return      the PM bit
 **********************************************************************************************************************/
__STATIC_INLINE bool HW_RTC_PMGet (R_RTC_Type * p_rtc_reg)
{
    return (bool) p_rtc_reg->RHRCNT_b.PM;
}

/*******************************************************************************************************************//**
 * Get the dayofweek field
 * @return      the dayofweek field
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_RTC_DayOfWeekGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RWKCNT;
}

/*******************************************************************************************************************//**
 * Get the dayofmonth field
 * @return      the dayofmonth field
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_RTC_DayOfMonthGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RDAYCNT;
}

/*******************************************************************************************************************//**
 * Get the month field
 * @return      the month field
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_RTC_MonthGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RMONCNT;
}

/*******************************************************************************************************************//**
 * Get the year field
 * @return      the year field
 **********************************************************************************************************************/
__STATIC_INLINE uint16_t HW_RTC_YearGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RYRCNT;
}

/*******************************************************************************************************************//**
 * Set the alarm second field
 * @param  second     the alarm second field
 * @param  match_flag the alarm flag for this field
 **********************************************************************************************************************/
__STATIC_INLINE void HW_ALARM_SecondSet (R_RTC_Type * p_rtc_reg, uint8_t second, bool match_flag)
{
    volatile uint8_t field;
    if (true == match_flag)
    {
        field = second | (uint8_t) (match_flag << COMPARE_ENB_BIT);
    }
    else
    {
        field = 0U;
    }
    p_rtc_reg->RSECAR = field;
}

/*******************************************************************************************************************//**
 * Set the alarm minute field
 * @param  minute     the alarm minute field
 * @param  match_flag the alarm flag for this field
 **********************************************************************************************************************/
__STATIC_INLINE void HW_ALARM_MinuteSet (R_RTC_Type * p_rtc_reg, uint8_t minute, bool match_flag)
{
    volatile uint8_t field;
    if (true == match_flag)
    {
        field = minute | (uint8_t) (match_flag << COMPARE_ENB_BIT);
    }
    else
    {
        field = 0U;
    }
    p_rtc_reg->RMINAR = field;
}

/*******************************************************************************************************************//**
 * Set the alarm hour field
 * @param  hour       the alarm hour field
 * @param  match_flag the alarm flag for this field
 **********************************************************************************************************************/
__STATIC_INLINE void HW_ALARM_HourSet (R_RTC_Type * p_rtc_reg, uint8_t hour, bool match_flag)
{
    volatile uint8_t field;

    if (true == match_flag)
    {
        field = hour | (uint8_t) (match_flag << COMPARE_ENB_BIT);
    }
    else
    {
        field = 0U;
    }
    p_rtc_reg->RHRAR = field;
}

/*******************************************************************************************************************//**
 * Set the alarm dayofweek field
 * @param  dayofweek  the alarm dayofweek field
 * @param  match_flag the alarm flag for this field
 **********************************************************************************************************************/
__STATIC_INLINE void HW_ALARM_DayOfWeekSet (R_RTC_Type * p_rtc_reg, uint8_t dayofweek, bool match_flag)
{
    volatile uint8_t field;
    if (true == match_flag)
    {
        field = dayofweek | (uint8_t) (match_flag << COMPARE_ENB_BIT);
    }
    else
    {
        field = 0U;
    }
    p_rtc_reg->RWKAR = field;
}

/*******************************************************************************************************************//**
 * Set the alarm dayofmonth field
 * @param  dayofmonth the alarm dayofmonth field
 * @param  match_flag the alarm flag for this field
 **********************************************************************************************************************/
__STATIC_INLINE void HW_ALARM_DayOfMonthSet (R_RTC_Type * p_rtc_reg, uint8_t dayofmonth, bool match_flag)
{
    volatile uint8_t field;
    if (true == match_flag)
    {
        field = dayofmonth | (uint8_t) (match_flag << COMPARE_ENB_BIT);
    }
    else
    {
        field = 1U;
    }
    p_rtc_reg->RDAYAR = field;
}

/*******************************************************************************************************************//**
 * Set the alarm month field
 * @param  month      the alarm month field
 * @param  match_flag the alarm flag for this field
 **********************************************************************************************************************/
__STATIC_INLINE void HW_ALARM_MonthSet (R_RTC_Type * p_rtc_reg, uint8_t month, bool match_flag)
{
    volatile uint8_t field;
    if (true == match_flag)
    {
        field = month | (uint8_t) (match_flag << COMPARE_ENB_BIT);
    }
    else
    {
        field = 0U;
    }
    p_rtc_reg->RMONAR = field;
}

/*******************************************************************************************************************//**
 * Set the alarm year field
 * @param  year       the alarm year field
 * @param  match_flag the alarm flag for this field
 **********************************************************************************************************************/
__STATIC_INLINE void HW_ALARM_YearSet (R_RTC_Type * p_rtc_reg, uint8_t year, bool match_flag)
{
    volatile uint8_t field;

    field = (true == match_flag) ? year : 0U;
    p_rtc_reg->RYRAR =  field;
    p_rtc_reg->RYRAREN_b.ENB = (bool) (match_flag);
}

/*******************************************************************************************************************//**
 * Get the alarm second field
 * @return      the alarm second field
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_ALARM_SecondGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RSECAR & 0x7f;
}

/*******************************************************************************************************************//**
 * Get the alarm minute field
 * @return      the alarm minute field
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_ALARM_MinuteGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RMINAR & 0x7f;
}

/*******************************************************************************************************************//**
 * Get the alarm hour field
 * @return      the alarm hour field
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_ALARM_HourGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RHRAR & 0x7f;
}

/*******************************************************************************************************************//**
 * Get the alarm dayofweek field
 * @return      the alarm dayofweek field
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_ALARM_DayOfWeekGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RWKAR & 0x7f;
}

/*******************************************************************************************************************//**
 * Get the alarm dayofmonth field
 * @return      the alarm dayofmonth field
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_ALARM_DayOfMonthGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RDAYAR & 0x7f;
}

/*******************************************************************************************************************//**
 * Get the alarm month field
 * @return      the alarm month field
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_ALARM_MonthGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RMONAR & 0x7f;
}

/*******************************************************************************************************************//**
 * Get the alarm year field
 * @return      the alarm year field
 **********************************************************************************************************************/
__STATIC_INLINE uint16_t HW_ALARM_YearGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RYRAR;
}

/*******************************************************************************************************************//**
 * Get the alarm second ENB field
 * @return      the alarm second ENB field
 **********************************************************************************************************************/
__STATIC_INLINE bool HW_ALARM_SecondMatchGet (R_RTC_Type * p_rtc_reg)
{
    return (bool) p_rtc_reg->RSECAR_b.ENB;
}

/*******************************************************************************************************************//**
 * Get the alarm minute ENB field
 * @return      the alarm minute ENB field
 **********************************************************************************************************************/
__STATIC_INLINE bool HW_ALARM_MinuteMatchGet (R_RTC_Type * p_rtc_reg)
{
    return (bool) p_rtc_reg->RMINAR_b.ENB;
}

/*******************************************************************************************************************//**
 * Get the alarm hour ENB field
 * @return      the alarm hour ENB field
 **********************************************************************************************************************/
__STATIC_INLINE bool HW_ALARM_HourMatchGet (R_RTC_Type * p_rtc_reg)
{
    return (bool) p_rtc_reg->RHRAR_b.ENB;
}

/*******************************************************************************************************************//**
 * Get the alarm dayofweek ENB field
 * @return      the alarm dayofweek ENB field
 **********************************************************************************************************************/
__STATIC_INLINE bool HW_ALARM_DayOfWeekMatchGet (R_RTC_Type * p_rtc_reg)
{
    return (bool) p_rtc_reg->RWKAR_b.ENB;
}

/*******************************************************************************************************************//**
 * Get the alarm dayofmonth ENB field
 * @return      the alarm dayofmonth ENB field
 **********************************************************************************************************************/
__STATIC_INLINE bool HW_ALARM_DayOfMonthMatchGet (R_RTC_Type * p_rtc_reg)
{
    return (bool) p_rtc_reg->RDAYAR_b.ENB;
}

/*******************************************************************************************************************//**
 * Get the alarm month ENB field
 * @return      the alarm month ENB field
 **********************************************************************************************************************/
__STATIC_INLINE bool HW_ALARM_MonthMatchGet (R_RTC_Type * p_rtc_reg)
{
    return (bool) p_rtc_reg->RMONAR_b.ENB;
}

/*******************************************************************************************************************//**
 * Get the alarm year ENB field
 * @return      the alarm year ENB field
 **********************************************************************************************************************/
__STATIC_INLINE bool HW_ALARM_YearMatchGet (R_RTC_Type * p_rtc_reg)
{
    return (bool) p_rtc_reg->RYRAREN_b.ENB;
}

/*******************************************************************************************************************//**
 * Set the clock error adjustment mode
 * @param  adjustment_mode       the clock error adjustment mode
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_ClkErrorAdjustmentModeSet (R_RTC_Type * p_rtc_reg,
                                                       rtc_error_adjustment_mode_t adjustment_mode)
{
    p_rtc_reg->RCR2_b.AADJE = adjustment_mode;
}

/*******************************************************************************************************************//**
 * Get the clock error adjustment mode
 * @return      the clock error adjustment mode
 **********************************************************************************************************************/
__STATIC_INLINE rtc_error_adjustment_mode_t HW_RTC_ClkErrorAdjustmentModeGet (R_RTC_Type * p_rtc_reg)
{
    return (rtc_error_adjustment_mode_t) p_rtc_reg->RCR2_b.AADJE;
}

/*******************************************************************************************************************//**
 * Set the clock error adjustment period
 * @param  adjustment_period       the clock error adjustment period
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_ClkErrorAdjustmentPeriodSet (R_RTC_Type * p_rtc_reg,
                                                         rtc_error_adjustment_period_t adjustment_period)
{
    p_rtc_reg->RCR2_b.AADJP = adjustment_period;
}

/*******************************************************************************************************************//**
 * Get the clock error adjustment period
 * @return      the clock error adjustment period
 **********************************************************************************************************************/
__STATIC_INLINE rtc_error_adjustment_period_t HW_RTC_ClkErrorAdjustmentPeriodGet (R_RTC_Type * p_rtc_reg)
{
    return (rtc_error_adjustment_period_t) p_rtc_reg->RCR2_b.AADJP;
}

/*******************************************************************************************************************//**
 * Set the clock error adjustment
 * @param  error_adjustment       the clock error adjustment
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_ClkErrorAdjustmentSet (R_RTC_Type * p_rtc_reg, uint8_t error_adjustment)
{
    p_rtc_reg->RADJ = error_adjustment;
}

/*******************************************************************************************************************//**
 * Get the clock error adjustment
 * @return      the clock error adjustment
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_RTC_ClkErrorAdjustmentGet (R_RTC_Type * p_rtc_reg)
{
    return p_rtc_reg->RADJ;
}

/*******************************************************************************************************************//**
 * Get the state of the carry interrupt enable bit
 * @return      the carry interrupt enable bit
 **********************************************************************************************************************/
__STATIC_INLINE bool HW_RTC_RTCCarryIRQGet (R_RTC_Type * p_rtc_reg)
{
    return (bool) p_rtc_reg->RCR1_b.CIE;
}

/*******************************************************************************************************************//**
 * Disable the carry interrupt
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_RTCCarryIRQDisable (R_RTC_Type * p_rtc_reg)
{
    p_rtc_reg->RCR1_b.CIE = 0U;
}

/*******************************************************************************************************************//**
 * Enable the carry interrupt
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_RTCCarryIRQEnable (R_RTC_Type * p_rtc_reg)
{
    p_rtc_reg->RCR1_b.CIE = 1U;
}

/*******************************************************************************************************************//**
 * Get the state of the alarm interrupt enable bit
 * @return      the alarm interrupt enable bit
 **********************************************************************************************************************/
__STATIC_INLINE bool HW_RTC_RTCAlarmIRQGet (R_RTC_Type * p_rtc_reg)
{
    return (bool) p_rtc_reg->RCR1_b.AIE;
}

/*******************************************************************************************************************//**
 * Disable the alarm interrupt
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_RTCAlarmIRQDisable (R_RTC_Type * p_rtc_reg)
{
    p_rtc_reg->RCR1_b.AIE = 0U;
}

/*******************************************************************************************************************//**
 * Enable the alarm interrupt
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_RTCAlarmIRQEnable (R_RTC_Type * p_rtc_reg)
{
    p_rtc_reg->RCR1_b.AIE = 1U;
}

/*******************************************************************************************************************//**
 * Get the state of the periodic interrupt enable bit
 * @return      the periodic interrupt enable bit
 **********************************************************************************************************************/
__STATIC_INLINE bool HW_RTC_RTCPeriodicIRQGet (R_RTC_Type * p_rtc_reg)
{
    return (bool) p_rtc_reg->RCR1_b.PIE;
}

/*******************************************************************************************************************//**
 * Disable the periodic interrupt
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_RTCPeriodicIRQDisable (R_RTC_Type * p_rtc_reg)
{
    p_rtc_reg->RCR1_b.PIE = 0U;
}

/*******************************************************************************************************************//**
 * Enable the periodic interrupt
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_RTCPeriodicIRQEnable (R_RTC_Type * p_rtc_reg)
{
    p_rtc_reg->RCR1_b.PIE = 1U;
}

/*******************************************************************************************************************//**
 * Set the rate of the periodic interrupt
 * @param  rate       the rate of the periodic interrupt
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RTC_RTCPeriodicInterruptSelect (R_RTC_Type * p_rtc_reg, rtc_periodic_irq_select_t rate)
{
    p_rtc_reg->RCR1_b.PES = rate;
}

/*******************************************************************************************************************//**
 * Get the rate of the periodic interrupt
 * @param  rate       the rate of the periodic interrupt
 **********************************************************************************************************************/
__STATIC_INLINE rtc_periodic_irq_select_t HW_RTC_RTCPeriodicInterruptRateGet (R_RTC_Type * p_rtc_reg)
{
    return (rtc_periodic_irq_select_t) p_rtc_reg->RCR1_b.PES;
}

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* HW_RTC_COMMON_H */
