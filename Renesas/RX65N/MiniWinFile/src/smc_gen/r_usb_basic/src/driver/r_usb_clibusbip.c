/**********************************************************************************************************************
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
 * Copyright (C) 2015(2018) Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_usb_clibusbip.c
 * Description  : USB IP Host and Peripheral low level library
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 16.11.2018 1.24 Supporting RTOS Thread safe
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_bitdefine.h"
#include "r_usb_reg_access.h"

#if defined(USB_CFG_HCDC_USE)
#include "r_usb_hcdc_if.h"

#endif /* defined(USB_CFG_PCDC_USE) */

#if defined(USB_CFG_HHID_USE)
#include "r_usb_hhid_if.h"

#endif /* defined(USB_CFG_HMSC_USE) */

#if defined(USB_CFG_HMSC_USE)
#include "r_usb_hmsc_if.h"

#endif /* defined(USB_CFG_HMSC_USE) */

#if defined(USB_CFG_PCDC_USE)
#include "r_usb_pcdc_if.h"

#endif /* defined(USB_CFG_PCDC_USE) */

#if defined(USB_CFG_PMSC_USE)
#include "r_usb_pmsc_if.h"

#endif /* defined(USB_CFG_PMSC_USE) */

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
#include "r_usb_dmac.h"
#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

/******************************************************************************
 Macro definitions
 *****************************************************************************/
#define USB_TMO_VAL     3000

/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/
extern uint16_t g_usb_usbmode;

#if (BSP_CFG_RTOS_USED == 1)
extern  usb_callback_t  *g_usb_apl_callback;
#endif /*(BSP_CFG_RTOS_USED == 1)*/

#if defined(USB_CFG_HMSC_USE)
    extern uint8_t g_drive_search_lock;
    extern uint8_t g_drive_search_que[];
    extern uint8_t g_drive_search_que_cnt;

#endif /* defined(USB_CFG_HMSC_USE) */

/******************************************************************************
 Private global variables and functions
 *****************************************************************************/
#if (BSP_CFG_RTOS_USED == 1)
SemaphoreHandle_t    g_usb_semaphore_hdl[USB_NUM_USBIP];
uint8_t              g_usb_semaphore_holder[USB_NUM_USBIP];
#endif  /* (BSP_CFG_RTOS_USED == 1) */

/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/
#if (BSP_CFG_RTOS_USED == 1)
usb_hdl_t     g_usb_cur_task_hdl[USB_NUM_USBIP];
#endif
/******************************************************************************
 Renesas Abstracted Driver API functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_nrdy_enable
 Description     : Enable NRDY interrupt of the specified pipe.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t pipe  : Pipe number.
 Return value    : none
 ******************************************************************************/
void usb_cstd_nrdy_enable (usb_utr_t *ptr, uint16_t pipe)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return; /* Error */
    }

    /* Enable NRDY */
    hw_usb_set_nrdyenb(ptr, pipe);
}
/******************************************************************************
 End of function usb_cstd_nrdy_enable
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_get_pid
 Description     : Fetch specified pipe's PID.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t pipe  : Pipe number.
 Return value    : uint16_t PID-bit status
 ******************************************************************************/
uint16_t usb_cstd_get_pid (usb_utr_t *ptr, uint16_t pipe)
{
    uint16_t buf;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_NULL; /* Error */
    }

    /* PIPE control reg read */
    buf = hw_usb_read_pipectr(ptr, pipe);
    return (uint16_t) (buf & USB_PID);
}
/******************************************************************************
 End of function usb_cstd_get_pid
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_get_maxpacket_size
 Description     : Fetch MaxPacketSize of the specified pipe.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t pipe  : Pipe number.
 Return value    : uint16_t MaxPacketSize
 ******************************************************************************/
uint16_t usb_cstd_get_maxpacket_size (usb_utr_t *ptr, uint16_t pipe)
{
    uint16_t size;
    uint16_t buffer;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_NULL; /* Error */
    }

    if (USB_PIPE0 == pipe)
    {
        buffer = hw_usb_read_dcpmaxp(ptr);
    }
    else
    {
        /* Pipe select */
        hw_usb_write_pipesel(ptr, pipe);
        buffer = hw_usb_read_pipemaxp(ptr);
    }

    /* Max Packet Size */
    size = (uint16_t) (buffer & USB_MXPS);

    return size;
}
/******************************************************************************
 End of function usb_cstd_get_maxpacket_size
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_get_pipe_dir
 Description     : Get PIPE DIR
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t pipe  : Pipe number.
 Return value    : uint16_t pipe direction.
 ******************************************************************************/
uint16_t usb_cstd_get_pipe_dir (usb_utr_t *ptr, uint16_t pipe)
{
    uint16_t buffer;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_NULL; /* Error */
    }

    /* Pipe select */
    hw_usb_write_pipesel(ptr, pipe);

    /* Read Pipe direction */
    buffer = hw_usb_read_pipecfg(ptr);
    return (uint16_t) (buffer & USB_DIRFIELD);
}
/******************************************************************************
 End of function usb_cstd_get_pipe_dir
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_get_pipe_type
 Description     : Fetch and return PIPE TYPE.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t pipe  : Pipe number.
 Return value    : uint16_t pipe type
 ******************************************************************************/
uint16_t usb_cstd_get_pipe_type (usb_utr_t *ptr, uint16_t pipe)
{
    uint16_t buffer;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_NULL; /* Error */
    }

    /* Pipe select */
    hw_usb_write_pipesel(ptr, pipe);

    /* Read Pipe direction */
    buffer = hw_usb_read_pipecfg(ptr);
    return (uint16_t) (buffer & USB_TYPFIELD);
}
/******************************************************************************
 End of function usb_cstd_get_pipe_type
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_do_aclrm
 Description     : Set the ACLRM-bit (Auto Buffer Clear Mode) of the specified 
                 : pipe.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t pipe  : Pipe number.
 Return value    : none
 ******************************************************************************/
void usb_cstd_do_aclrm (usb_utr_t *ptr, uint16_t pipe)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return; /* Error */
    }

    /* Control ACLRM */
    hw_usb_set_aclrm(ptr, pipe);
    hw_usb_clear_aclrm(ptr, pipe);
}
/******************************************************************************
 End of function usb_cstd_do_aclrm
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_set_buf
 Description     : Set PID (packet ID) of the specified pipe to BUF.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t pipe  : Pipe number.
 Return value    : none
 ******************************************************************************/
void usb_cstd_set_buf (usb_utr_t *ptr, uint16_t pipe)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return; /* Error */
    }

    /* PIPE control reg set */
    hw_usb_set_pid(ptr, pipe, USB_PID_BUF);
}
/******************************************************************************
 End of function usb_cstd_set_buf
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_clr_stall
 Description     : Set up to NAK the specified pipe, and clear the STALL-bit set
                 : to the PID of the specified pipe.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t pipe  : Pipe number.
 Return value    : none
 Note            : PID is set to NAK.
 ******************************************************************************/
void usb_cstd_clr_stall (usb_utr_t *ptr, uint16_t pipe)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return; /* Error */
    }

    /* Set NAK */
    usb_cstd_set_nak(ptr, pipe);

    /* Clear STALL */
    hw_usb_clear_pid(ptr, pipe, USB_PID_STALL);
}
/******************************************************************************
 End of function usb_cstd_clr_stall
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_port_speed
 Description     : Get USB-speed of the specified port.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 :Return value   : uint16_t  : HSCONNECT, Hi-Speed
                 :           : FSCONNECT : Full-Speed
                 :           : LSCONNECT : Low-Speed
                 :           : NOCONNECT : not connect
 ******************************************************************************/
uint16_t usb_cstd_port_speed (usb_utr_t *ptr)
{
    uint16_t buf;
    uint16_t conn_inf;

    buf = hw_usb_read_dvstctr(ptr);

    /* Reset handshake status get */
    buf = (uint16_t) (buf & USB_RHST);

    switch (buf)
    {
        /* Get port speed */
        case USB_HSMODE :
            conn_inf = USB_HSCONNECT;
        break;
        case USB_FSMODE :
            conn_inf = USB_FSCONNECT;
        break;
        case USB_LSMODE :
            conn_inf = USB_LSCONNECT;
        break;
        case USB_HSPROC :
            conn_inf = USB_NOCONNECT;
        break;
        default :
            conn_inf = USB_NOCONNECT;
        break;
    }

    return (conn_inf);
}
/******************************************************************************
 End of function usb_cstd_port_speed
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_set_event
 Description     : Set event.
 Arguments       : uint16_t     event       : event code.
                 : usb_ctrl_t   *p_ctrl     : control structure for USB API.
 Return value    : none
 ******************************************************************************/
void usb_set_event (uint16_t event, usb_ctrl_t *p_ctrl)
{
#if (BSP_CFG_RTOS_USED == 1)
    static uint16_t     count = 0;

    p_ctrl->event = event;
    g_usb_cstd_event[count] = *p_ctrl;

    switch (event)
    {
        case    USB_STS_DEFAULT :
        case    USB_STS_CONFIGURED :     
        case    USB_STS_BC :
        case    USB_STS_OVERCURRENT :
        case    USB_STS_NOT_SUPPORT :
            (*g_usb_apl_callback)(&g_usb_cstd_event[count], (usb_hdl_t)USB_NULL, USB_OFF);
        break;  

        case    USB_STS_DETACH :
            if (USB_HOST == g_usb_usbmode)
            {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
                (*g_usb_apl_callback)(&g_usb_cstd_event[count], (usb_hdl_t)USB_NULL, USB_OFF);
                if (g_usb_semaphore_holder[p_ctrl->module] == p_ctrl->address)
                {
                    usb_cstd_rel_semaphore(p_ctrl);
                }
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
            }
            else
            {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
                (*g_usb_apl_callback)(&g_usb_cstd_event[count], (usb_hdl_t)USB_NULL, USB_OFF);
                usb_cstd_rel_semaphore(p_ctrl);
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
            }
        break;
 
        case    USB_STS_REQUEST :
            (*g_usb_apl_callback)(&g_usb_cstd_event[count], (usb_hdl_t)USB_NULL, USB_ON);
        break;

        case    USB_STS_SUSPEND :
            if (USB_HOST == g_usb_usbmode)
            {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
                (*g_usb_apl_callback)(&g_usb_cstd_event[count], g_usb_cur_task_hdl[p_ctrl->module], USB_OFF);
                usb_cstd_rel_semaphore(p_ctrl);
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
            }
            else
            {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
                (*g_usb_apl_callback)(&g_usb_cstd_event[count], (usb_hdl_t)USB_NULL, USB_OFF);
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
            }
        break;

        case    USB_STS_RESUME :
            if (USB_HOST == g_usb_usbmode)
            {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
                (*g_usb_apl_callback)(&g_usb_cstd_event[count], g_usb_cur_task_hdl[p_ctrl->module], USB_OFF);
                usb_cstd_rel_semaphore(p_ctrl);
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
            }
            else
            {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
                (*g_usb_apl_callback)(&g_usb_cstd_event[count], (usb_hdl_t)USB_NULL, USB_OFF);
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
            }
        break;

        case    USB_STS_REQUEST_COMPLETE :
            if (USB_HOST == g_usb_usbmode)
            {
#if ((USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST)
                (*g_usb_apl_callback)(&g_usb_cstd_event[count], g_usb_cur_task_hdl[p_ctrl->module], USB_OFF);
                usb_cstd_rel_semaphore(p_ctrl);
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
            }
            else
            {
#if ((USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI)
                if (0 == p_ctrl->setup.length)
                {
                    /* Processing for USB request has the no data stage */
                    (*g_usb_apl_callback)(&g_usb_cstd_event[count], (usb_hdl_t)USB_NULL, USB_OFF);
                }
                else
                {
                    /* Processing for USB request has the data state */
                    (*g_usb_apl_callback)(&g_usb_cstd_event[count], g_usb_cur_task_hdl[p_ctrl->module], USB_OFF);
                    usb_cstd_rel_semaphore(p_ctrl);
                }
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
            }
        break;

        case    USB_STS_READ_COMPLETE :
        case    USB_STS_WRITE_COMPLETE :
#if defined(USB_CFG_HMSC_USE)       
        case    USB_STS_MSC_CMD_COMPLETE:
#endif /* defined(USB_CFG_HMSC_USE) */
            (*g_usb_apl_callback)(&g_usb_cstd_event[count], g_usb_cur_task_hdl[p_ctrl->module], USB_OFF);
            usb_cstd_rel_semaphore(p_ctrl);
        break;

        default :
            /* Do Nothing */
        break;
    }

    count = ((count + 1) % USB_EVENT_MAX);
#else /* (BSP_CFG_RTOS_USED == 1) */
    g_usb_cstd_event.code[g_usb_cstd_event.write_pointer] = event;
    g_usb_cstd_event.ctrl[g_usb_cstd_event.write_pointer] = *p_ctrl;
    g_usb_cstd_event.write_pointer++;
    if (g_usb_cstd_event.write_pointer >= USB_EVENT_MAX)
    {
        g_usb_cstd_event.write_pointer = 0;
    }
#endif /*(BSP_CFG_RTOS_USED == 1)*/
} /* End of function usb_set_event() */


#if (BSP_CFG_RTOS_USED == 1)
/******************************************************************************
 Function Name   : usb_cstd_get_semaphore
 Description     : Getting semaphore processing for the thread safe function
 Arguments       : usbip_no     : USB Module Number (0 or 1)
 Return value    : usb_er_t     : USB_OK / USB_ERROR
 ******************************************************************************/
usb_err_t usb_cstd_get_semaphore (usb_ctrl_t *p_ctrl)
{
#if (USB_CFG_MULTIPLE_TASKS == USB_CFG_ENABLE)
    BaseType_t      retval = pdFAIL;
    uint8_t         usbip_no = p_ctrl->module;

    retval = xSemaphoreTake(g_usb_semaphore_hdl[usbip_no], USB_TMO_VAL);

    if (pdPASS == retval)
    {
        g_usb_cur_task_hdl[usbip_no] = xTaskGetCurrentTaskHandle();
        g_usb_semaphore_holder[usbip_no] = p_ctrl->address;
        return USB_SUCCESS;
    }

    return USB_ERR_NG;
#else   /* (USB_CFG_MULTIPLE_TASKS == USB_CFG_ENABLE) */
    return USB_SUCCESS;
#endif  /* (USB_CFG_MULTIPLE_TASKS == USB_CFG_ENABLE) */
}
/******************************************************************************
 End of function usb_cstd_get_semaphore
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_rel_semaphore
 Description     : Releasing semaphore processing for the thread safe function
 Arguments       : usbip_no     : USB Module Number (0 or 1)
 Return value    : usb_er_t     : USB_OK / USB_ERROR
 ******************************************************************************/
usb_err_t usb_cstd_rel_semaphore (usb_ctrl_t *p_ctrl)
{
#if (USB_CFG_MULTIPLE_TASKS == USB_CFG_ENABLE)
    BaseType_t      retval = pdFAIL;
    uint8_t         usbip_no = p_ctrl->module;

    if ((UBaseType_t)0 == uxSemaphoreGetCount(g_usb_semaphore_hdl[usbip_no]))
    {
        retval = xSemaphoreGive(g_usb_semaphore_hdl[usbip_no]);
    }

    if (pdPASS == retval)
    {
        g_usb_cur_task_hdl[usbip_no] = (usb_hdl_t)USB_NULL;
        g_usb_semaphore_holder[usbip_no] = 0;
        return USB_SUCCESS;
    }

    return USB_ERR_NG;
#else
    return USB_SUCCESS;
#endif
}
/******************************************************************************
 End of function usb_cstd_rel_semaphore
 ******************************************************************************/
#endif  /* (BSP_CFG_RTOS_USED == 1) */


#if (BSP_CFG_RTOS_USED == 0)
/******************************************************************************
 Function Name   : usb_cstd_usb_task
 Description     : USB driver main loop processing.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_cstd_usb_task (void)
{
    if ( USB_HOST == g_usb_usbmode)
    {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
#if defined(USB_CFG_HMSC_USE)
        do
        {
#endif /* defined(USB_CFG_HMSC_USE) */
        usb_cstd_scheduler(); /* Scheduler */
        if (USB_FLGSET == usb_cstd_check_schedule()) /* Check for any task processing requests flags. */
        {
#if (BSP_CFG_RTOS_USED == 0)
            /** Use only in non-OS. In RTOS, the kernel will schedule these tasks, no polling. **/
            usb_hstd_hcd_task((usb_vp_int_t) 0); /* HCD Task */
            usb_hstd_mgr_task((usb_vp_int_t) 0); /* MGR Task */
            usb_hhub_task((usb_vp_int_t) 0); /* HUB Task */
#endif /* (BSP_CFG_RTOS_USED == 0) */
#if defined(USB_CFG_HCDC_USE) || defined(USB_CFG_HHID_USE) || defined(USB_CFG_HMSC_USE) || defined(USB_CFG_HVND_USE)

            usb_class_task();

#endif  /* defined(USB_CFG_HCDC_USE)||defined(USB_CFG_HHID_USE)||defined(USB_CFG_HMSC_USE)||defined(USB_CFG_HVND_USE) */
        }
#if defined(USB_CFG_HMSC_USE)
    }
    while (USB_FALSE != g_drive_search_lock);

#endif /* defined(USB_CFG_HMSC_USE) */
#endif /*( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )*/
    }
    else
    {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        usb_pstd_pcd_task();
#if defined(USB_CFG_PMSC_USE)
        usb_pmsc_task();
#endif /* defined(USB_CFG_PMSC_USE) */
#endif /*( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )*/
    }
} /* End of function usb_cstd_usb_task() */

/******************************************************************************
 Function Name   : usb_class_task
 Description     : Each device class task processing
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_class_task (void)
{
#if defined(USB_CFG_HMSC_USE)
    usb_utr_t utr;
    uint16_t addr;

#if (BSP_CFG_RTOS_USED == 0)
    usb_hmsc_task();                /* USB Host MSC driver task */
    usb_hmsc_strg_drive_task();     /* HSTRG Task */
#endif /* (BSP_CFG_RTOS_USED == 0) */

    if (USB_FALSE == g_drive_search_lock)
    {
        if (g_drive_search_que_cnt > 0)
        {
            g_drive_search_lock = g_drive_search_que[0];

            utr.ip = USB_IP0;
            if ((g_drive_search_lock & USB_IP_MASK) == USBA_ADDRESS_OFFSET)
            {
                utr.ip = USB_IP1;
            }

            addr = g_drive_search_lock & USB_ADDRESS_MASK;
            utr.ipp = usb_hstd_get_usb_ip_adr(utr.ip); /* Get the USB IP base address. */

            /* Storage drive search. */
            usb_hmsc_strg_drive_search(&utr, addr, (usb_cb_t) usb_hmsc_drive_complete);
        }
    }
#endif /* defined(USB_CFG_HMSC_USE) */
#if defined(USB_CFG_HCDC_USE)
#if (BSP_CFG_RTOS_USED == 0)
    usb_hcdc_task((usb_vp_int_t) 0); /* USB Host CDC driver task */
#endif /* (BSP_CFG_RTOS_USED == 0) */
#endif /* defined(USB_CFG_HCDC_USE) */
#if defined(USB_CFG_HHID_USE)
#if (BSP_CFG_RTOS_USED == 0)
    usb_hhid_task((usb_vp_int_t) 0); /* USB Host CDC driver task */
#endif /* (BSP_CFG_RTOS_USED == 0) */

#endif /* defined(USB_CFG_HHID_USE) */

} /* End of function usb_class_task */
#endif /*(BSP_CFG_RTOS_USED == 0)*/

/******************************************************************************
 End  Of File
 ******************************************************************************/
