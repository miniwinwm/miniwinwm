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

#ifndef R_RTC_PRIVATE_API_H
#define R_RTC_PRIVATE_API_H

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/***********************************************************************************************************************
 * Private Instance API Functions. DO NOT USE! Use functions through Interface API structure instead.
 **********************************************************************************************************************/
ssp_err_t R_RTC_Open (rtc_ctrl_t * const p_ctrl, rtc_cfg_t const * const p_cfg);
ssp_err_t R_RTC_Close (rtc_ctrl_t * const p_ctrl);
ssp_err_t R_RTC_Configure (rtc_ctrl_t * const p_ctrl, void * const p_extend);
ssp_err_t R_RTC_CalendarTimeSet (rtc_ctrl_t * p_ctrl, rtc_time_t * p_time, bool clock_start);
ssp_err_t R_RTC_CalendarTimeGet (rtc_ctrl_t * p_ctrl, rtc_time_t * p_time);
ssp_err_t R_RTC_CalendarAlarmSet (rtc_ctrl_t * p_ctrl, rtc_alarm_time_t * p_alarm, bool interrupt_enable_flag);
ssp_err_t R_RTC_CalendarAlarmGet (rtc_ctrl_t * p_ctrl, rtc_alarm_time_t * p_alarm);
ssp_err_t R_RTC_CalendarCounterStart (rtc_ctrl_t * p_ctrl);
ssp_err_t R_RTC_CalendarCounterStop (rtc_ctrl_t * p_ctrl);
ssp_err_t R_RTC_IrqEnable (rtc_ctrl_t * p_ctrl, rtc_event_t event);
ssp_err_t R_RTC_IrqDisable (rtc_ctrl_t * p_ctrl, rtc_event_t event);
ssp_err_t R_RTC_PeriodicIrqRateSet (rtc_ctrl_t * const p_ctrl, rtc_periodic_irq_select_t rate);
ssp_err_t R_RTC_InfoGet(rtc_ctrl_t * p_ctrl, rtc_info_t * p_rtc_info);
ssp_err_t R_RTC_VersionGet (ssp_version_t * version);
ssp_err_t R_RTC_ErrorAdjustmentModeSet (rtc_ctrl_t * p_api_ctrl,
                                        rtc_error_adjustment_mode_cfg_t *p_error_adjustment_mode);
ssp_err_t R_RTC_ErrorAdjustmentSet (rtc_ctrl_t * p_api_ctrl, rtc_error_adjustment_cfg_t *p_error_adjustment_config);

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* R_RTC_PRIVATE_API_H */
