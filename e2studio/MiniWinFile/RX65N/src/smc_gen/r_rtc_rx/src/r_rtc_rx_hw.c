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
* File Name    : r_rtc_rx_hw.c
* Description  : Main driver code for the Real Time Clock (RTC) peripheral on RX MCUs.
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
*                              Added the rtc_enable_ints function in order to enable the interrupt
*                              regardless of the cold start or warm start. (rtc_init function)
*                              Fixed the issue of initial setting procedure for the time capture.
*                              (rtc_config_capture function)
*           01.10.2016 2.50    Added support for RX65N.
*                              The setting of the carry interrupt enable bit (RCR1.CIE) specified by
*                              the rtc_enable_ints function has been changed from "enabled" to "disabled".
*                              Additionally, the way to set the RCR1 register has been changed from setting
*                              by an immediate value to setting by the RTC_INT_ENABL definition.
*           31.07.2017 2.70    Added support for RX65N-2MB and RX130-512KB.
*                              Removed support for RX210 and RX63N/631.
*                              Removed definitions related to RX210, RX63N/631
*                              from conditional expressions of preprocessor.
*                              Fixed an issue where "0" is set to RCR3.RTCEN bit
*                              at the beginning of rtc_init function processing.
*                              Fixed an infinite loop problem in verify processing after register setting,
*                              when calling R_RTC_Open function without oscillating sub-clock.
*                              Addition of dummy read processing after register setting
*                              in rtc_set_current_time function and rtc_set_alarm_time function.
*           20.09.2017 2.71    Fixed issue that an incorrect time is read out when a carry of the RTC counter occurs
*                              while reading the current time.
*                              Fixed issue that count stop occurred at warm start.
*                              - There is no change in this file.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "platform.h"
#include "r_rtc_rx_if.h"
#include "r_rtc_rx_config.h"
#include "r_rtc_rx_private.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define RTC_INT_MASK    (0x07)

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
#if !defined(BSP_MCU_RX11_ALL) && !defined(BSP_MCU_RX130)
volatile rtc_cap_ctrl_t *g_pcap_ctrl = (rtc_cap_ctrl_t *) &RTC.RTCCR0.BYTE;
volatile rtc_cap_time_t *g_pcap_time = (rtc_cap_time_t *) &RTC.RSECCP0.BYTE;
#endif


/***********************************************************************************************************************
* Function Name: rtc_init
* Description  : This function sets the registers to a known state when cold started. Almost all RTC bits have an
*                unknown value at power up.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void rtc_init (void)
{
    /* Set sub-clock drive capacity */
    RTC.RCR3.BIT.RTCDV = RTC_DRIVE_CAPACITY;
    while (RTC_DRIVE_CAPACITY != RTC.RCR3.BIT.RTCDV)
    {
        /* Confirm that it has changed, it's slow. */
        nop();
    }

    /* Enable the sub-clock for RTC */
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX65N) || defined(BSP_MCU_RX71M)
    RTC.RCR4.BIT.RCKSEL = 1;            // use main clock
#endif
    RTC.RCR3.BIT.RTCEN = 0;             // disable sub-clock
    while (0 != RTC.RCR3.BIT.RTCEN)
    {
        /* Confirm that it has changed */
        nop();
    }

    /* Wait for six the sub-clock cycles */
    R_BSP_SoftwareDelay((uint32_t) 184, (bsp_delay_units_t) BSP_DELAY_MICROSECS); //Approx.184us (32768Hz * 6cycles = 183.10...us)

    /* Confirm that it has changed */
    while (0x00u != RTC.RCR1.BYTE)
    {
        /* Disable RTC interrupts */
        RTC.RCR1.BYTE = 0x00u;
    }

    /* Stop RTC counter */
    rtc_counter_run(RTC_COUNTER_STOP);

    RTC.RFRH.WORD = 0x0001U;
    RTC.RFRL.WORD = 0x6e35U;

    /* Confirm that it has changed */
    while (0 != RTC.RCR2.BIT.CNTMD)
    {
        /* Set RTC to calendar mode */
        RTC.RCR2.BIT.CNTMD = 0;
    }

    /* Clear alarms, capture, adjustment registers, and output enable */
    rtc_reset();

    /* Insure ICU RTC interrupts disabled */
    IEN(RTC,PRD) = 0;
    IEN(RTC,ALM) = 0;
    IEN(RTC,CUP) = 0;

    return;
}
/**********************************************************************************************************************
End of function rtc_init
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: rtc_set_periodic
* Description  : This function sets the periodic frequency arguments in the RTC. Arguments are checked
*                prior to calling this function. The ICU interrupts are enabled if RTC_PERIODIC_OFF is
*                not specified.
* Arguments    : freq
*                   - frequency; from enum
*                priority
*                   - interrupt priority; 0 to 15
* Return Value : None
***********************************************************************************************************************/
void rtc_set_periodic (rtc_periodic_t freq, uint8_t priority)
{
    uint8_t tmp;

    /* NOTE: arguments validated before entering this routine */

    /* Set frequency */
    /* Note: Off can be any one of several values. It may not match the "off" value written. */
    tmp = RTC.RCR1.BIT.PES;
    if (RTC.RCR1.BIT.PES != freq)           // if setting needs to change
    {
        RTC.RCR1.BIT.PES = freq;            // write the setting
        while (RTC.RCR1.BIT.PES == tmp)     // loop while setting has not changed
        {
            /* Confirm that it has changed */
            nop();
        }
    }


    /* Set interrupts */
    if (RTC_PERIODIC_OFF == freq)
    {
        IEN(RTC,PRD) = 0;
    }
    else
    {
        IR(RTC,PRD)  = 0;
        IPR(RTC,PRD) = priority;
        IEN(RTC,PRD) = 1;
    }

    return;
}
/**********************************************************************************************************************
End of function rtc_set_periodic
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: rtc_set_output
* Description  : This function selects the output clock frequency
*                and turns the output clock output on or off.
* Arguments    : output_freq
*                   - output frequency; from enum
* Return Value : None
***********************************************************************************************************************/
void rtc_set_output (rtc_output_t output_freq)
{
    uint8_t counter_state;


    /* NOTE: valid output_freq verified before entering this routine */

    counter_state = RTC.RCR2.BIT.START;         // save start bit/counter state

    rtc_counter_run(RTC_COUNTER_STOP);          // set start bit to 0/stop counters
    RTC.RCR2.BIT.RTCOE = 0;                     // disable output

    if (RTC_OUTPUT_OFF != output_freq)
    {
        RTC.RCR1.BIT.RTCOS = (uint8_t) ((RTC_OUTPUT_64_HZ == output_freq) ? 1 : 0); // set bit for 64Hz or 1 Hz operation
        RTC.RCR2.BIT.RTCOE = 1;                 // enable output
    }

    rtc_counter_run(counter_state);             // restore start bit setting/counter state
    return;
}
/**********************************************************************************************************************
End of function rtc_set_output
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: rtc_set_current_time
* Description  : This function stops the counters, sets the current time,
*                then returns the counters to its previous state.
* Arguments    : p_current
*                   - structure pointer to current date/time
* Return Value : None
***********************************************************************************************************************/
void rtc_set_current_time (tm_t * p_current)
{
    uint8_t clock_state;
    volatile uint8_t dummy_byte;
    volatile uint16_t dummy_word;
    volatile uint8_t i;

    /* Note the clock state */
    clock_state = RTC.RCR2.BIT.START;

    /* Stop RTC counter */
    rtc_counter_run(RTC_COUNTER_STOP);

    /* Set for 24-hour mode. */
    RTC.RCR2.BIT.HR24 = 1;

    /* Set time */
    /* Set seconds. (0-59) */
    RTC.RSECCNT.BYTE = rtc_dec_to_bcd((uint8_t) p_current->tm_sec);
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RSECCNT.BYTE;
    }

    /* Set minutes (0-59) */
    RTC.RMINCNT.BYTE = rtc_dec_to_bcd((uint8_t) p_current->tm_min);
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RMINCNT.BYTE;
    }

    /* Set hours. (0-23) */
    RTC.RHRCNT.BYTE = rtc_dec_to_bcd((uint8_t) p_current->tm_hour);
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RHRCNT.BYTE;
    }

    /* Set the date */
    /* Day of the week (0-6, 0=Sunday) */
    RTC.RWKCNT.BYTE = rtc_dec_to_bcd((uint8_t) p_current->tm_wday);
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RWKCNT.BYTE;
    }

    /* Day of the month (1-31) */
    RTC.RDAYCNT.BYTE = rtc_dec_to_bcd((uint8_t) p_current->tm_mday);
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RDAYCNT.BYTE;
    }

    /* Month. (1-12, 1=January) */
    RTC.RMONCNT.BYTE = rtc_dec_to_bcd((uint8_t) (p_current->tm_mon + 1));
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RMONCNT.BYTE;
    }

    /* Year. (00-99) */
    RTC.RYRCNT.WORD = (uint16_t) (rtc_dec_to_bcd((uint8_t) ((p_current->tm_year + 1900) % 100)));
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_word = RTC.RYRCNT.WORD;
    }

    /* Restore the clock */
    rtc_counter_run(clock_state);

    return;
}
/**********************************************************************************************************************
End of function rtc_set_current_time
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: rtc_set_alarm_time
* Description  : This function disables all alarms in the ICU, sets the alarm date/time,
*                then restores the ICU alarms to its previous state.
* Arguments    : p_alarm
*                   - structure pointer to alarm date/time
* Return Value :
***********************************************************************************************************************/
void rtc_set_alarm_time (tm_t *p_alarm)
{
    uint8_t state;
    volatile uint8_t dummy_byte;
    volatile uint16_t dummy_word;
    volatile uint8_t i;

    state = IEN(RTC,ALM);
    IEN(RTC,ALM) = 0;

    /* Set time */
    /* Set seconds. (0-59) */
    RTC.RSECAR.BYTE &= 0x80u;
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RSECAR.BYTE;
    }

    RTC.RSECAR.BYTE |= rtc_dec_to_bcd((uint8_t) p_alarm->tm_sec);
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RSECAR.BYTE;
    }

    /* Set minutes (0-59) */
    RTC.RMINAR.BYTE &= 0x80u;
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RMINAR.BYTE;
    }

    RTC.RMINAR.BYTE |= rtc_dec_to_bcd((uint8_t) p_alarm->tm_min);
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RMINAR.BYTE;
    }

    /* Set hours. (0-23) */
    RTC.RHRAR.BYTE &= 0x80u;
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RHRAR.BYTE;
    }

    RTC.RHRAR.BYTE |= rtc_dec_to_bcd((uint8_t) p_alarm->tm_hour);
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RHRAR.BYTE;
    }

    /* Set the date */
    /* Day of the week (0-6, 0=Sunday) */
    RTC.RWKAR.BYTE &= 0x80u;
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RWKAR.BYTE;
    }

    RTC.RWKAR.BYTE |= rtc_dec_to_bcd((uint8_t) p_alarm->tm_wday);
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RWKAR.BYTE;
    }

    /* Day of the month (1-31) */
    RTC.RDAYAR.BYTE &= 0x80u;
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RDAYAR.BYTE;
    }

    RTC.RDAYAR.BYTE |= rtc_dec_to_bcd((uint8_t) p_alarm->tm_mday);
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RDAYAR.BYTE;
    }

    /* Month. (1-12, 1=January) */
    RTC.RMONAR.BYTE &= 0x80u;
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RMONAR.BYTE;
    }

    RTC.RMONAR.BYTE |= rtc_dec_to_bcd((uint8_t) (p_alarm->tm_mon + 1));
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_byte = RTC.RMONAR.BYTE;
    }

    /* Year. (00-99) */
    RTC.RYRAR.WORD = (uint16_t) (rtc_dec_to_bcd((uint8_t) ((p_alarm->tm_year + 1900) % 100)));
    for (i = 0; i < RTC_DUMMY_READ; i++)
    {
        dummy_word = RTC.RYRAR.WORD;
    }

    IEN(RTC,ALM) = state;
    return;
}
/**********************************************************************************************************************
End of function rtc_set_alarm_time
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: rtc_enable_alarms
* Description  : This function sets the alarm bit for each available alarm field.
* Arguments    : p_alm_ctrl
*                   - pointer to alarm control structure
* Return Value : None
***********************************************************************************************************************/
void rtc_enable_alarms (rtc_alarm_ctrl_t *p_alm_ctrl)
{
    IEN(RTC,ALM) = 0;

    /* Alarm time enable setting */
    RTC.RSECAR.BIT.ENB  = (uint8_t)((true == p_alm_ctrl->sec) ? 1 : 0);
    RTC.RMINAR.BIT.ENB  = (uint8_t)((true == p_alm_ctrl->min) ? 1 : 0);
    RTC.RHRAR.BIT.ENB   = (uint8_t)((true == p_alm_ctrl->hour) ? 1 : 0);
    RTC.RDAYAR.BIT.ENB  = (uint8_t)((true == p_alm_ctrl->mday) ? 1 : 0);
    RTC.RMONAR.BIT.ENB  = (uint8_t)((true == p_alm_ctrl->mon) ? 1 : 0);
    RTC.RYRAREN.BIT.ENB = (uint8_t)((true == p_alm_ctrl->year) ? 1 : 0);
    RTC.RWKAR.BIT.ENB   = (uint8_t)((true == p_alm_ctrl->wday) ? 1 : 0);

    if (1 == RTC.RWKAR.BIT.ENB) // dummy read for waiting until set the value of RTC
    {
        nop();
    }

    /* Alarm time setting definite waiting */
    R_BSP_SoftwareDelay((uint32_t)16, (bsp_delay_units_t)BSP_DELAY_MILLISECS);  //Approx.16ms (1/64Hz = 15.625ms)

    IR(RTC,ALM)  = 0;
    IPR(RTC,ALM) = p_alm_ctrl->int_priority;
    IEN(RTC,ALM) = 1;

    return;
}
/**********************************************************************************************************************
End of function rtc_enable_alarms
***********************************************************************************************************************/


#if !defined(BSP_MCU_RX11_ALL) && !defined(BSP_MCU_RX130)
/***********************************************************************************************************************
* Function Name: rtc_config_capture
* Description  : This function configures the capture facility for the specified pin.
* Arguments    : p_capture
*                   - pointer to configuration structure (already checked for valid data)
* Return Value : None
***********************************************************************************************************************/
void rtc_config_capture (rtc_capture_cfg_t *p_capture)
{
    uint8_t byte;

    /*  The time capture event input enable */
    g_pcap_ctrl[p_capture->pin].rtccr = RTC_CAPTURE_ENABLE_MASK;
    while (RTC_CAPTURE_ENABLE_MASK != g_pcap_ctrl[p_capture->pin].rtccr)
    {
        /* Confirm that it has changed */
        nop();
    }

    /* Noise Filter setting */
    byte = (uint8_t) (((uint8_t) p_capture->filter) << 4);
    g_pcap_ctrl[p_capture->pin].rtccr |= byte;
    while ((g_pcap_ctrl[p_capture->pin].rtccr & 0x30) != byte)
    {
        /* Confirm that it has changed */
        nop();
    }

    /* Waiting for noise filter set time. */
    if (RTC_FILTER_DIV1 == p_capture->filter)
    {
        /* 3 period of the sampling period is 91.5us. (Approx. 92us) */
        R_BSP_SoftwareDelay((uint32_t) 92, (bsp_delay_units_t) BSP_DELAY_MICROSECS);
    }
    else if (RTC_FILTER_DIV32 == p_capture->filter)
    {
        /* 3 period of the sampling period is 2.92ms. (Approx. 3ms) */
        R_BSP_SoftwareDelay((uint32_t) 3, (bsp_delay_units_t) BSP_DELAY_MILLISECS);
    }
    else
    {
        /* RTC_FILTER_OFF */
    }

    /*  Edge detection setting */
    byte = (uint8_t) (p_capture->edge);
    g_pcap_ctrl[p_capture->pin].rtccr |= byte;
    while ((g_pcap_ctrl[p_capture->pin].rtccr & 0x03) != byte)
    {
        /* Confirm that it has changed */
        nop();
    }

    return;
}
/**********************************************************************************************************************
End of function rtc_config_capture
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: rtc_check_capture
* Description  : This function checks to see if a capture event has occurred.
*                If yes, the time of the event is loaded.
* Arguments    : pin
*                   - pin number to check event on (RTCIC0, RTCIC1 or RTCIC2)
*                p_time
*                   - pointer to time structure to load date/time into if event occurred
* Return Value : RTC_SUCCESS
*                   - capture event detected; time retrieved
*                RTC_ERR_NO_CAPTURE
*                   - capture event not detected
*                RTC_ERR_BAD_PARAM
*                   - invalid pin number
***********************************************************************************************************************/
rtc_err_t rtc_check_capture (rtc_pin_t pin, tm_t *p_time)
{
    volatile rtc_cap_time_t *pregs;
    uint8_t tmp;

#if (RTC_CFG_PARAM_CHECKING_ENABLE)
    if (pin >= RTC_NUM_PINS)
    {
        return RTC_ERR_BAD_PARAM;
    }
#endif

    if (g_pcap_ctrl[pin].rtccr & RTC_CAPTURE_EVENT_MASK)
    {
        pregs = &g_pcap_time[pin];

        tmp = (uint8_t) (g_pcap_ctrl[pin].rtccr & (~RTC_CAPTURE_EVENT_MASK)); //Save settings

        /* Event detection disable */
        g_pcap_ctrl[pin].rtccr &= (~RTC_CAPTURE_EDGE_MASK);

        /* READ TIME */
        /* mask off unknown bits and hour am/pm field */
        p_time->tm_sec  = rtc_bcd_to_dec((uint8_t) (pregs->rseccp & 0x7F));
        p_time->tm_min  = rtc_bcd_to_dec((uint8_t) (pregs->rmincp & 0x7F));
        p_time->tm_hour = rtc_bcd_to_dec((uint8_t) (pregs->rhrcp & 0x3F));
        p_time->tm_mday = rtc_bcd_to_dec((uint8_t) (pregs->rdaycp & 0x3F));
        p_time->tm_mon  = rtc_bcd_to_dec(pregs->rmoncp) - 1;


        /* CLEAR EVENT (must be loop) */
        do
        {
            g_pcap_ctrl[pin].rtccr &= (~RTC_CAPTURE_EVENT_MASK);
        } while (0 != (g_pcap_ctrl[pin].rtccr & RTC_CAPTURE_EVENT_MASK));

        g_pcap_ctrl[pin].rtccr = tmp;                //write back settings
        while ((g_pcap_ctrl[pin].rtccr & (~RTC_CAPTURE_EVENT_MASK)) != tmp)
        {
            /* Confirm that it has changed */
            nop();
        }

        return RTC_SUCCESS;
    }
    else
    {
        return RTC_ERR_NO_CAPTURE;
    }
}
/**********************************************************************************************************************
End of function rtc_check_capture
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: rtc_disable_capture
* Description  : This function disables the capture facility for the specified pin.
* Arguments    : pin
*                   - pin number to disable capture for (0, 1, 2)
* Return Value : None
***********************************************************************************************************************/
void rtc_disable_capture (rtc_pin_t pin)
{

    /* valid pin checked prior to entry */
    g_pcap_ctrl[pin].rtccr = 0;

    while (0 != g_pcap_ctrl[pin].rtccr)
    {
        /* Confirm that it has changed */
        nop();
    }
}
/**********************************************************************************************************************
End of function rtc_disable_capture
***********************************************************************************************************************/

#endif /* not RX11x, RX130 */


/***********************************************************************************************************************
* Function Name: rtc_read_current
* Description  : This function retrieves the current date/time. If a carry interrupt is detected
*                (occurs on a second interval) while reading the values are read again.
* Arguments    : p_current
*                   - pointer to time structure for loading current date/time
* Return Value : None
***********************************************************************************************************************/
void rtc_read_current (tm_t *p_current)
{

    uint16_t bcd_years; // Used for converting year.

    do
    {
        /* Clear carry flag in ICU */
        ICU.IR[IR_RTC_CUP].BIT.IR = 0;

        /* Read and convert RTC registers; mask off unknown bits and hour am/pm. */
        /* Seconds. (0-59) */
        p_current->tm_sec  = rtc_bcd_to_dec((uint8_t) (RTC.RSECCNT.BYTE & 0x7fu));

        /* Minutes. (0-59) */
        p_current->tm_min  = rtc_bcd_to_dec((uint8_t) (RTC.RMINCNT.BYTE & 0x7fu));

        /* Hours. (0-23) */
        p_current->tm_hour = rtc_bcd_to_dec((uint8_t) (RTC.RHRCNT.BYTE & 0x3fu));

        /* Day of the month (1-31) */
        p_current->tm_mday = rtc_bcd_to_dec(RTC.RDAYCNT.BYTE);

        /* Months since January (0-11) */
        p_current->tm_mon  = rtc_bcd_to_dec(RTC.RMONCNT.BYTE) - 1;

        /* Years since 2000 */
        bcd_years = (uint16_t) RTC.RYRCNT.WORD;

        /* years years since 1900 (100-199) */
        p_current->tm_year = rtc_bcd_to_dec((uint8_t) (bcd_years & 0xFF)) + 100;

        /* Days since Sunday (0-6) */
        p_current->tm_wday = (int) (RTC.RWKCNT.BYTE & 0x07u);

    } while (1 == ICU.IR[IR_RTC_CUP].BIT.IR); //Reread if carry occurs during read

    return;
}
/**********************************************************************************************************************
End of function rtc_read_current
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: rtc_read_alarm
* Description  : This function reads the alarm date/time and clears the alarm interrupt flag.
* Arguments    : p_alarm
*                   - time structure pointer for loading alarm date/time
* Return Value : None
***********************************************************************************************************************/
void rtc_read_alarm (tm_t *p_alarm)
{
    /* Used for converting year. */
    uint16_t bcd_years;

    /* Clear flag in ICU */
    ICU.IR[IR_RTC_CUP].BIT.IR = 0;

    /* Read and convert RTC registers; mask off unknown bits and hour am/pm. */
    /* Seconds. (0-59) */
    p_alarm->tm_sec  = rtc_bcd_to_dec((uint8_t) (RTC.RSECAR.BYTE & 0x7fu));

    /* Minutes. (0-59) */
    p_alarm->tm_min  = rtc_bcd_to_dec((uint8_t) (RTC.RMINAR.BYTE & 0x7fu));

    /* Hours. (0-23) */
    p_alarm->tm_hour = rtc_bcd_to_dec((uint8_t) (RTC.RHRAR.BYTE & 0x3fu));

    /* Day of the month (1-31) */
    p_alarm->tm_mday = rtc_bcd_to_dec((uint8_t) (RTC.RDAYAR.BYTE & 0x3fu));

    /* Months since January (0-11) */
    p_alarm->tm_mon  = rtc_bcd_to_dec((uint8_t) (RTC.RMONAR.BYTE & 0x1fu)) - 1;

    /* Years since 2000 (100-199)*/
    bcd_years = (uint16_t) RTC.RYRAR.WORD;

    /* RTC only supports years 0-99; years since 1900 */
    p_alarm->tm_year = rtc_bcd_to_dec((uint8_t) (bcd_years & 0xFF)) + 100;

    /* Days since Sunday (0-6) */
    p_alarm->tm_wday = (int) (RTC.RWKAR.BYTE & 0x07u);

    return;
}
/**********************************************************************************************************************
End of function rtc_read_alarm
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: rtc_counter_run
* Description  : Starts or stops the RTC counter.
* Arguments    : action
*                   - 0 to stop, 1 to start
* Return Value : None
***********************************************************************************************************************/
void rtc_counter_run (const uint8_t action)
{

    /* START bit is updated in synchronization with the next count source. */
    while (RTC.RCR2.BIT.START != action)
    {
        RTC.RCR2.BIT.START = action;
    }

    return;
}
/**********************************************************************************************************************
End of function rtc_counter_run
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: rtc_reset
* Description  : This function sets the RTC Software Reset bit and waits for the reset to complete.
*                The reset affects the output clock enable, alarm and capture registers.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void rtc_reset (void)
{

    RTC.RCR2.BIT.RESET = 1;

    while (0 != RTC.RCR2.BIT.RESET)
    {
        /* Wait for reset to happen before continuing.*/
        nop();
    }

    return;
}
/**********************************************************************************************************************
End of function rtc_reset
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: rtc_disable_ints
* Description  : This function disables the RTC and ICU interrupts.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void rtc_disable_ints (void)
{

    /* Disable ICU interrupts */
    IEN(RTC,PRD) = 0;
    IEN(RTC,ALM) = 0;
    IEN(RTC,CUP) = 0;

    /* Disable RTC interrupts */
    while ((RTC.RCR1.BYTE & RTC_INT_MASK) != 0)
    {
        RTC.RCR1.BYTE &= (~RTC_INT_MASK);
    }

    /* Clear interrupts request flag */
    IR(RTC,PRD) = 0;
    IR(RTC,ALM) = 0;
    IR(RTC,CUP) = 0;

    return;
}
/**********************************************************************************************************************
End of function rtc_disable_ints
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: rtc_enable_ints
* Description  : This function enables the RTC interrupts.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void rtc_enable_ints (void)
{

    /* Enable RTC interrupts (PIE, CIE and AIE), not ICU yet */
    RTC.RCR1.BYTE = RTC_INT_ENABLE;
    while (RTC_INT_ENABLE != RTC.RCR1.BYTE)
    {
        /* Confirm that it has changed */
        nop();
    }

    return;
}
/**********************************************************************************************************************
End of function rtc_enable_ints
***********************************************************************************************************************/

