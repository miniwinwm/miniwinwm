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
* Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/**********************************************************************************************************************
* File Name    : r_sys_time_rx.c
* Description  : Functions for using SYSTEM TIME on RX devices.
***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           30.11.2016 1.00    Initial Release.
***********************************************************************************************************************/

/*****************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/
#include <string.h>
#include "platform.h"
#include "r_cmt_rx_if.h"
#include "r_sys_time_rx_if.h"
#include "r_sys_time_rx_private.h"

/*****************************************************************************
Private global variables and functions
******************************************************************************/
static const uint8_t year_data[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const time_offset_tbl_t time_offset_tbl[] =
{
    {   "UTC-12:00" ,   -43200  },
    {   "UTC-11:00" ,   -39600  },
    {   "UTC-10:00" ,   -36000  },
    {   "UTC-09:30" ,   -30600  },
    {   "UTC-09:00" ,   -32400  },
    {   "UTC-08:00" ,   -28800  },
    {   "UTC-07:00" ,   -25200  },
    {   "UTC-06:00" ,   -21600  },
    {   "UTC-05:00" ,   -18000  },
    {   "UTC-04:00" ,   -14400  },
    {   "UTC-03:30" ,   -9000   },
    {   "UTC-03:00" ,   -10800  },
    {   "UTC-02:00" ,   -7200   },
    {   "UTC-01:00" ,   -3600   },
    {   "UTC"       ,   0       },
    {   "UTC+01:00" ,   3600    },
    {   "UTC+02:00" ,   7200    },
    {   "UTC+03:00" ,   10800   },
    {   "UTC+03:30" ,   12600   },
    {   "UTC+04:00" ,   14400   },
    {   "UTC+04:30" ,   16200   },
    {   "UTC+05:00" ,   18000   },
    {   "UTC+05:30" ,   19800   },
    {   "UTC+05:45" ,   20700   },
    {   "UTC+06:00" ,   21600   },
    {   "UTC+06:30" ,   23400   },
    {   "UTC+07:00" ,   25200   },
    {   "UTC+08:00" ,   28800   },
    {   "UTC+08:30" ,   30600   },
    {   "UTC+08:45" ,   31500   },
    {   "UTC+09:00" ,   32400   },
    {   "UTC+09:30" ,   34200   },
    {   "UTC+10:00" ,   36000   },
    {   "UTC+10:30" ,   37800   },
    {   "UTC+11:00" ,   39600   },
    {   "UTC+12:00" ,   43200   },
    {   "UTC+12:45" ,   45900   },
    {   "UTC+13:00" ,   46800   },
    {   "UTC+14:00" ,   50400   },
};

SYS_TIME_STATIC SYS_TIME sys_time_private;
SYS_TIME_STATIC uint32_t sys_time_opened_flag = 0;
SYS_TIME_STATIC uint32_t sys_time_cmt_channel;
SYS_TIME_STATIC process_list_t process_list[SYS_TIME_REGISTERED_PROCESS_LIMIT];

SYS_TIME_STATIC void sys_time_process(void *pdata);
SYS_TIME_STATIC bool is_leap_year(uint32_t year);

/*****************************************************************************
* Function Name: R_SYS_TIME_Open
* Description  : Start the system timer operation using CMT timer channel.
* Arguments    : none
* Return Value : SYS_TIME_SUCCESS -
*                    Normally terminated.
*                SYS_TIME_BAD_CHANNEL -
*                    Non-existent channel number.
*                SYS_TIME_ALREADY_STARTED -
*                    System timer is already started.
******************************************************************************/
sys_time_err_t R_SYS_TIME_Open(void)
{
    sys_time_err_t return_code;
    int i;

    if(0 == sys_time_opened_flag)
    {
        memset(&sys_time_private, 0, sizeof(SYS_TIME));
        if(true == R_CMT_CreatePeriodic(100, sys_time_process, &sys_time_cmt_channel))
        {
            sys_time_opened_flag = 1;
            return_code = SYS_TIME_SUCCESS;

            for(i = 0; i < SYS_TIME_REGISTERED_PROCESS_LIMIT; i++)
            {
                process_list[i].function_pointer = (callback_from_sys_time_t)FIT_NO_FUNC;
                process_list[i].registered_flag = 0;
            }
        }
        else
        {
            return_code = SYS_TIME_BAD_CHANNEL;
        }
    }
    else
    {
        return_code = SYS_TIME_ALREADY_STARTED;
    }
    return return_code;
}

/*****************************************************************************
* Function Name: R_SYS_TIME_GetCurrentTime
* Description  : Get current time from system timer.
* Arguments    : sys_time -
*                    SYS_TIME variables pointer.
* Return Value : SYS_TIME_SUCCESS -
*                    Normally terminated.
******************************************************************************/
sys_time_err_t R_SYS_TIME_GetCurrentTime(SYS_TIME *sys_time)
{
    sys_time_err_t return_code = SYS_TIME_SUCCESS;
    memcpy(sys_time, &sys_time_private, sizeof(SYS_TIME));
    return return_code;
}

/*****************************************************************************
* Function Name: R_SYS_TIME_SetCurrentTime
* Description  : Set current time to system timer.
* Arguments    : sys_time -
*                    SYS_TIME variables.
* Return Value : SYS_TIME_SUCCESS -
*                    Normally terminated.
*                SYS_TIME_BAD_SYS_TIME -
*                    Bad time offset is set.
******************************************************************************/
sys_time_err_t R_SYS_TIME_SetCurrentTime(SYS_TIME *sys_time)
{
    sys_time_err_t return_code = SYS_TIME_SUCCESS;
    int i;
    uint8_t sys_time_check_ok_flag = 0;
    uint32_t tmp_day;
    uint32_t pdata;

    R_CMT_Control(sys_time_cmt_channel, CMT_RX_CMD_PAUSE, &pdata);

    if(sys_time->sec < 60)
    {
        if(sys_time->min < 60)
        {
            if(sys_time->hour < 24)
            {
                if(is_leap_year(sys_time->year))
                {
                    tmp_day = year_data[sys_time->month - 1];
                    if(sys_time->month == 2)
                    {
                        tmp_day++;
                    }
                    if(sys_time->day >= 1 && sys_time->day <= tmp_day)
                    {
                        if(sys_time->month >= 1 && sys_time->month <= 12)
                        {
                            if(sys_time->year >= 1970)
                            {
                                sys_time_check_ok_flag = 1;
                            }
                        }
                    }
                }
                else
                {
                    if(sys_time->day >= 1 && sys_time->day <= year_data[sys_time->month - 1])
                    {
                        if(sys_time->month >= 1 && sys_time->month <= 12)
                        {
                            if(sys_time->year >= 1970)
                            {
                                sys_time_check_ok_flag = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    if(sys_time_check_ok_flag)
    {
        sys_time->unix_time = 0;
        sys_time->unix_time += sys_time->sec;
        sys_time->unix_time += sys_time->min * SYS_TIME_SECOND_OF_MIN;
        sys_time->unix_time += sys_time->hour * SYS_TIME_SECOND_OF_HOUR;
        sys_time->unix_time += (sys_time->day - 1) * SYS_TIME_SECOND_OF_DAY;
        for(i = 1; i < sys_time->month; i++)
        {
            sys_time->unix_time += SYS_TIME_SECOND_OF_DAY * year_data[i - 1];
        }

        if(true == is_leap_year(sys_time->year) && (sys_time->month >= 3) )
        {
            sys_time->unix_time += SYS_TIME_SECOND_OF_DAY;
        }

        for(i = 1970UL; i < sys_time->year; i++)
        {
            if(true == is_leap_year(i))
            {
                sys_time->unix_time += SYS_TIME_SECOND_OF_LEAP_YEAR;
            }
            else
            {
                sys_time->unix_time += SYS_TIME_SECOND_OF_YEAR;
            }
        }
        R_SYS_TIME_ConvertUnixTimeToSystemTime(sys_time->unix_time, sys_time, SYS_TIME_UTC);
        memcpy(&sys_time_private, sys_time, sizeof(SYS_TIME));
    }
    else
    {
        return_code = SYS_TIME_BAD_SYS_TIME;
    }
    R_CMT_Control(sys_time_cmt_channel, CMT_RX_CMD_RESUME, &pdata);

    return return_code;
}

/*****************************************************************************
* Function Name: R_SYS_TIME_ConvertUnixTimeToSystemTime
* Description  : Convert unix time to time zone.
* Arguments    : unix_time -
*                    Estimation seconds from 01/01/1970 00:00:00.
*                sys_time -
*                    System timer data.
*                time_offset -
*                    Time offset code like "UTC-12:00", exception is "UTC" that means "UTC+-00:00"
* Return Value : SYS_TIME_SUCCESS -
*                    Normally terminated.
*                SYS_TIME_BAD_TIME_OFFSET -
*                    Bad time offset is set.
******************************************************************************/
sys_time_err_t R_SYS_TIME_ConvertUnixTimeToSystemTime(uint32_t unix_time, SYS_TIME *sys_time, uint8_t *time_offset)
{
    sys_time_err_t return_code;
    int i;
    uint32_t tmp_unix_time;
    uint32_t tmp_year = 1970, tmp_month = 1;
    int32_t offset;
    uint32_t pdata;

    R_CMT_Control(sys_time_cmt_channel, CMT_RX_CMD_PAUSE, &pdata);

    for(i = 0; i < sizeof(time_offset_tbl) / sizeof(time_offset_tbl_t); i++)
    {
        if(!strcmp((char*)time_offset, (char*)time_offset_tbl[i].time_offset_code))
        {
            offset = time_offset_tbl[i].offset;
            strcpy((char *)sys_time->time_zone, (char *)time_offset);
            break;
        }
    }

    if(i != sizeof(time_offset_tbl) / sizeof(time_offset_tbl_t))
    {

        tmp_unix_time = unix_time + offset;
        sys_time->unix_time = tmp_unix_time;

        /* calculate the year */
        if(tmp_unix_time >= SYS_TIME_SECOND_OF_YEAR)
        {
            while(1)
            {
                if(is_leap_year(tmp_year))
                {
                    tmp_unix_time -= SYS_TIME_SECOND_OF_LEAP_YEAR;
                }
                else
                {
                    tmp_unix_time -= SYS_TIME_SECOND_OF_YEAR;
                }
                tmp_year++;

                if(is_leap_year(tmp_year))
                {
                    if(tmp_unix_time < SYS_TIME_SECOND_OF_LEAP_YEAR)
                    {
                        break;
                    }
                }
                else
                {
                    if(tmp_unix_time < SYS_TIME_SECOND_OF_YEAR)
                    {
                        break;
                    }
                }
            }
        }
        sys_time->year = tmp_year;

        /* calculate the month */
        for(i = 0; i < sizeof(year_data); i++)
        {
            if(is_leap_year(tmp_year) && (tmp_month == 2))
            {
                if(tmp_unix_time < SYS_TIME_SECOND_OF_DAY * 29)
                {
                    break;
                }
                tmp_unix_time -= SYS_TIME_SECOND_OF_DAY;

            }
            if(tmp_unix_time >= SYS_TIME_SECOND_OF_DAY * year_data[i])
            {
                tmp_unix_time -= SYS_TIME_SECOND_OF_DAY * year_data[i];
                tmp_month++;
            }
            else
            {
                break;
            }
        }
        sys_time->month = tmp_month;

        /* calculate the day */
        sys_time->day = (tmp_unix_time / SYS_TIME_SECOND_OF_DAY) + 1;
        tmp_unix_time -= (sys_time->day - 1) * SYS_TIME_SECOND_OF_DAY;

        /* calculate the hour */
        sys_time->hour = tmp_unix_time / SYS_TIME_SECOND_OF_HOUR;
        tmp_unix_time -= sys_time->hour * SYS_TIME_SECOND_OF_HOUR;

        /* calculate the minute */
        sys_time->min = tmp_unix_time / SYS_TIME_SECOND_OF_MIN;
        tmp_unix_time -= sys_time->min * SYS_TIME_SECOND_OF_MIN;

        /* store the remain second */
        sys_time->sec = tmp_unix_time;

        return_code = SYS_TIME_SUCCESS;
    }
    else
    {
        return_code = SYS_TIME_BAD_TIME_OFFSET;
    }
    R_CMT_Control(sys_time_cmt_channel, CMT_RX_CMD_RESUME, &pdata);
    return return_code;
}

/*****************************************************************************
* Function Name: R_SYS_TIME_RegisterPeriodicCallback
* Description  : Register the periodic callback function.
* Arguments    : function_pointer -
*                    User function pointer to register the callback.
*                interval -
*                    Callback interval. Interval unit is 10ms.
* Return Value : SYS_TIME_SUCCESS -
*                    Normally terminated.
*                SYS_TIME_BAD_FUNCTION_POINTER -
*                    Bad function pointer is set.
*                SYS_TIME_BAD_INTERVAL -
*                    Bad interval parameter is specified.
*                SYS_TIME_FULL_REGISTERED -
*                    All register table is used.
*                SYS_TIME_ALREADY_REGISTERED -
*                    Specified function pointer has been already registered.
******************************************************************************/
sys_time_err_t R_SYS_TIME_RegisterPeriodicCallback(callback_from_sys_time_t function_pointer, uint32_t interval)
{
    sys_time_err_t return_code;
    int i;

    if((function_pointer != (callback_from_sys_time_t)0UL) && (function_pointer != (callback_from_sys_time_t)0xffffffffUL))
    {
        if((interval <= SYS_TIME_INTERVAL_LIMIT) && (0 != interval))
        {
            if(false == R_SYS_TIME_IsPeriodicCallbackRegistered(function_pointer))
            {
                for(i = 0; i < SYS_TIME_REGISTERED_PROCESS_LIMIT; i++)
                {
                    if((0 == process_list[i].registered_flag))
                    {
                        process_list[i].registered_flag = 1;
                        process_list[i].interval = interval;
                        process_list[i].interval_initial = interval;
                        process_list[i].function_pointer = (callback_from_sys_time_t)function_pointer;
                        return_code = SYS_TIME_SUCCESS;
                        break;
                    }
                }
                if(i >= SYS_TIME_REGISTERED_PROCESS_LIMIT)
                {
                    return_code = SYS_TIME_FULL_REGISTERED;
                }
            }
            else
            {
                return_code = SYS_TIME_ALREADY_REGISTERED;
            }
        }
        else
        {
            return_code = SYS_TIME_BAD_INTERVAL;
        }
    }
    else
    {
        return_code = SYS_TIME_BAD_FUNCTION_POINTER;
    }

    return return_code;
}

/*****************************************************************************
* Function Name: R_SYS_TIME_UnregisterPeriodicCallback
* Description  : Register the periodic callback function.
* Arguments    : function_pointer -
*                    User function pointer to unregister the callback.
* Return Value : SYS_TIME_SUCCESS -
*                    Normally terminated.
*                SYS_TIME_BAD_FUNCTION_POINTER -
*                    Bad function pointer is set.
******************************************************************************/
sys_time_err_t R_SYS_TIME_UnregisterPeriodicCallback(callback_from_sys_time_t function_pointer)
{
    sys_time_err_t return_code;
    int i;

    for(i = 0; i < SYS_TIME_REGISTERED_PROCESS_LIMIT; i++)
    {
        if(1 == process_list[i].registered_flag)
        {
            if(function_pointer == process_list[i].function_pointer)
            {
                process_list[i].registered_flag = 0;
                process_list[i].function_pointer = (callback_from_sys_time_t)FIT_NO_FUNC;
                return_code = SYS_TIME_SUCCESS;
                break;
            }
        }
    }

    if(i == SYS_TIME_REGISTERED_PROCESS_LIMIT)
    {
        return_code = SYS_TIME_BAD_FUNCTION_POINTER;
    }
    return return_code;
}


/*****************************************************************************
* Function Name: R_SYS_TIME_IsPeriodicCallbackRegistered
* Description  : Confirm the priodic callback is registered.
* Arguments    : function_pointer -
*                    User function pointer to confirm the callback is registered.
* Return Value : boolean(true/false).
******************************************************************************/
bool R_SYS_TIME_IsPeriodicCallbackRegistered(callback_from_sys_time_t function_pointer)
{
    bool return_code;
    int i;

    for(i = 0; i < SYS_TIME_REGISTERED_PROCESS_LIMIT; i++)
    {
        if(1 == process_list[i].registered_flag)
        {
            if(function_pointer == process_list[i].function_pointer)
            {
                return_code = true;
                break;
            }
        }
    }

    if(i == SYS_TIME_REGISTERED_PROCESS_LIMIT)
    {
        return_code = false;
    }
    return return_code;
}

/*****************************************************************************
* Function Name: R_SYS_TIME_Close
* Description  : Close the all callback process.
* Arguments    : none
* Return Value : SYS_TIME_SUCCESS -
*                    Normally terminated.
*                SYS_TIME_BAD_CHANNEL -
*                    Non-existent channel number.
*                SYS_TIME_NOT_STARTED -
*                    System timer is not started.
******************************************************************************/
sys_time_err_t R_SYS_TIME_Close(void)
{
    sys_time_err_t return_code;

    if(1 == sys_time_opened_flag)
    {
        if(true == R_CMT_Stop(sys_time_cmt_channel))
        {
            sys_time_opened_flag = 0;
            return_code = SYS_TIME_SUCCESS;
        }
        else
        {
            return_code = SYS_TIME_BAD_CHANNEL;
        }
    }
    else
    {
        return_code = SYS_TIME_NOT_STARTED;
    }
    return return_code;
}

/*****************************************************************************
* Function Name: R_SYS_TIME_GetVersion
* Description  : Returns the version of this module. The version number is
*                encoded such that the top two bytes are the major version
*                number and the bottom two bytes are the minor version number.
* Arguments    : none
* Return Value : version number
******************************************************************************/
#pragma inline(R_SYS_TIME_GetVersion)
uint32_t  R_SYS_TIME_GetVersion(void)
{
    uint32_t const version = (SYS_TIME_VERSION_MAJOR << 16) | SYS_TIME_VERSION_MINOR;
    return version;
}

/*****************************************************************************
* Function Name: sys_time_process
* Description  : Internal function for system timer module.
*                This function calles user callback in CMT interrupt context.
* Arguments    : pdata -
*                    Channel number from CMT module.
* Return Value : none
******************************************************************************/
SYS_TIME_STATIC void sys_time_process(void *pdata)
{
    static int32_t _1s_timer;
    uint8_t n;
    int i;

    R_BSP_InterruptsEnable();

    /* callback process phase */
    for(i = 0; i < SYS_TIME_REGISTERED_PROCESS_LIMIT; i++)
    {
        if(1 == process_list[i].registered_flag)
        {
            process_list[i].interval--;
            if(process_list[i].interval == 0)
            {
                process_list[i].interval = process_list[i].interval_initial;
                if(process_list[i].function_pointer != (callback_from_sys_time_t)FIT_NO_FUNC)
                {
                    process_list[i].function_pointer();
                }
            }
        }
    }

    /* update system timer phase */
    _1s_timer++;
    if((_1s_timer % 100) == 0)
    {
        _1s_timer = 0;
        sys_time_private.unix_time++;
        if (++sys_time_private.sec >= 60)
        {
            sys_time_private.sec = 0;
            if (++sys_time_private.min >= 60)
            {
                sys_time_private.min = 0;
                if (++sys_time_private.hour >= 24)
                {
                    sys_time_private.hour = 0;
                    n = year_data[sys_time_private.month - 1];
                    if ((n == 28) && (is_leap_year(sys_time_private.year)))
                    {
                        n++;
                    }
                    if (++sys_time_private.day > n)
                    {
                        sys_time_private.day = 1;
                        if (++sys_time_private.month > 12)
                        {
                            sys_time_private.month = 1;
                            sys_time_private.year++;
                        }
                    }
                }
            }
        }
    }
}

/*****************************************************************************
* Function Name: is_leap_year
* Description  : Internal function for system timer module.
*                This function confirms the argument is leap year or not.
* Arguments    : year -
*                    A.D. value.
* Return Value : bool(true/false)
******************************************************************************/
SYS_TIME_STATIC bool is_leap_year(uint32_t year)
{
    uint8_t return_value = 0;
    if((year % 4) == 0)
    {
        if(((year % 100) == 0) && ((year % 400) != 0))
        {
            return_value = 0;
        }
        else
        {
            return_value = 1;
        }
    }
    return return_value;
}
