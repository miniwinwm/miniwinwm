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
 * Copyright (C) 2014(2018) Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_usb_hinthandler_usbip1.c
 * Description  : USB IP1 Host interrupt handler code
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"

#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
#if USB_NUM_USBIP == 2
/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/
extern usb_utr_t g_usb_cstd_int_msg[][USB_INTMSGMAX]; /* Interrupt message */
extern uint16_t g_usb_cstd_int_msg_cnt[]; /* Interrupt message count */


/******************************************************************************
 Renesas Abstracted common Interrupt handler functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb2_hstd_usb_handler
 Description     : USB2 interrupt routine. Analyze which USB interrupt occurred 
                 : and send message to PCD/HCD task.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb2_hstd_usb_handler(void)
{
    usb_utr_t *ptr;
    usb_er_t err;

    /* Initial pointer */
    ptr = &g_usb_cstd_int_msg[1][g_usb_cstd_int_msg_cnt[1]];
    ptr->ip = USB_USBIP_1;
    ptr->ipp = usb_hstd_get_usb_ip_adr(ptr->ip);

    /* Host Function */
    /* Host Interrupt handler */
    usb_hstd_interrupt_handler(ptr);
    ptr->msghead = (usb_mh_t)USB_NULL;
    /* Send message */
    err = USB_ISND_MSG(USB_HCD_MBX, (usb_msg_t*)ptr);
    if (err != USB_OK)
    {
        /*USB_PRINTF1("### lib_UsbHandler DEF2 isnd_msg error (%ld)\n", err);*/
    }

    /* Renewal Message count  */
    g_usb_cstd_int_msg_cnt[1]++;
    if (g_usb_cstd_int_msg_cnt[1] == USB_INTMSGMAX)
    {
        g_usb_cstd_int_msg_cnt[1] = 0;
    }
}

#endif  /* #if USB_NUM_USBIP == 2 */
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 End  Of File
 ******************************************************************************/
