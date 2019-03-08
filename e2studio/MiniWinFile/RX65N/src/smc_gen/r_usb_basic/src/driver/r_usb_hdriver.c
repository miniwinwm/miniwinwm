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
 * File Name    : r_usb_hdriver.c
 * Description  : USB Host Control Driver
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 26.01.2017 1.21 Support DMAC Technical Update for RX71M/RX64M USBA.
 *         : 30.09.2017 1.22 Rename "usb_hstd_buf2fifo"->"usb_hstd_buf_to_fifo" and Function move from"r_usb_hlibusbip.c"
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 16.11.2018 1.24 Supporting RTOS Thread safe
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/
#include <string.h>

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

#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
#define USB_RESPONCE_COUNTER_VALUE     (6000u)
#endif /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

/******************************************************************************
 Private global variables and functions
 ******************************************************************************/
static uint16_t usb_shstd_clr_stall_pipe[USB_NUM_USBIP];
static uint16_t usb_shstd_clr_stall_request[USB_NUM_USBIP][5];  
static usb_utr_t usb_shstd_clr_stall_ctrl[USB_NUM_USBIP];

#if (BSP_CFG_RTOS_USED == 0)
static usb_cb_t usb_shstd_clr_stall_call;
#endif /* (BSP_CFG_RTOS_USED == 0) */

static usb_er_t usb_hstd_set_submitutr (usb_utr_t *ptr);
static void usb_hstd_set_retransfer (usb_utr_t *ptr, uint16_t pipe);
#if (BSP_CFG_RTOS_USED == 0)
static void usb_hstd_clr_stall_result (usb_utr_t *ptr, uint16_t data1, uint16_t data2);
#endif /* (BSP_CFG_RTOS_USED == 0) */

/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/
/* Device driver (registration) */
usb_hcdreg_t g_usb_hstd_device_drv[USB_NUM_USBIP][USB_MAXDEVADDR + 1u];

/* Root port, status, config num, interface class, speed, */
uint16_t g_usb_hstd_device_info[USB_NUM_USBIP][USB_MAXDEVADDR + 1u][8u];
uint16_t g_usb_hstd_remort_port[USB_NUM_USBIP];

/* Control transfer stage management */
uint16_t g_usb_hstd_ctsq[USB_NUM_USBIP];

/* Manager mode */
uint16_t g_usb_hstd_mgr_mode[USB_NUM_USBIP];

/* DEVSEL & DCPMAXP (Multiple device) */
uint16_t g_usb_hstd_dcp_register[USB_NUM_USBIP][USB_MAXDEVADDR + 1u];

/* Device address */
uint16_t g_usb_hstd_device_addr[USB_NUM_USBIP];

/* Reset handshake result */
uint16_t g_usb_hstd_device_speed[USB_NUM_USBIP];

/* Device driver number */
uint16_t g_usb_hstd_device_num[USB_NUM_USBIP];

/* Ignore count */
uint16_t g_usb_hstd_ignore_cnt[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1u];

/* USB data transfer */
/* PIPEn Buffer counter */
uint32_t g_usb_hstd_data_cnt[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1u];

/* PIPEn Buffer pointer(8bit) */
uint8_t *g_p_usb_hstd_data[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1u];

/* Message pipe */
usb_utr_t *g_p_usb_hstd_pipe[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1u];

/* Hi-speed enable */
uint16_t g_usb_hstd_hs_enable[USB_NUM_USBIP];
usb_ctrl_trans_t g_usb_ctrl_request[USB_NUM_USBIP][USB_MAXDEVADDR + 1];

uint16_t g_usb_hstd_pipe_request[USB_NUM_USBIP][USB_MAX_PIPE_NO + 1u];

/* Pipe number of USB Host transfer.(Read pipe/Write pipe) */
const uint8_t g_usb_pipe_host[] =
{
/* READ pipe *//* WRITE pipe */
/* IN pipe *//* OUT pipe */
#if defined(USB_CFG_HCDC_USE)
        USB_CFG_HCDC_BULK_IN, USB_CFG_HCDC_BULK_OUT,    /* HCDC: Address 1 */
        USB_CFG_HCDC_BULK_IN, USB_CFG_HCDC_BULK_OUT,    /* HCDC: Address 2 using Hub */
        USB_CFG_HCDC_BULK_IN2, USB_CFG_HCDC_BULK_OUT2,  /* HCDC: Address 3 using Hub */
        USB_NULL, USB_NULL,
#else
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
#endif

#if defined(USB_CFG_HCDC_USE)
        USB_CFG_HCDC_INT_IN, USB_NULL,                  /* HCDCC: Address 1 */
        USB_CFG_HCDC_INT_IN, USB_NULL,                  /* HCDCC: Address 2 using Hub */
        USB_CFG_HCDC_INT_IN2, USB_NULL,                 /* HCDCC: Address 3 using Hub */
        USB_NULL, USB_NULL,
#else
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
#endif

#if defined(USB_CFG_HHID_USE)
        USB_CFG_HHID_INT_IN, USB_CFG_HHID_INT_OUT,      /* HCDC: Address 1 */
        USB_CFG_HHID_INT_IN, USB_CFG_HHID_INT_OUT,      /* HCDC: Address 2 using Hub */
        USB_CFG_HHID_INT_IN2, USB_NULL,                 /* HCDC: Address 3 using Hub */
        USB_CFG_HHID_INT_IN3, USB_NULL,                 /* HCDC: Address 4 using Hub */
#else
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
        USB_NULL, USB_NULL,
#endif

};

#if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
extern uint16_t g_usb_hstd_response_counter[];
#endif /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

/******************************************************************************
 Renesas USB Host Driver functions
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_dev_descriptor
 Description     : Returns buffer header pointer to fetch device descriptor.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : uint8_t *      : Device Descriptor Pointer
 ******************************************************************************/
uint8_t *usb_hstd_dev_descriptor (usb_utr_t *ptr)
{
    return (uint8_t *) &g_usb_hstd_device_descriptor[ptr->ip];
}
/******************************************************************************
 End of function usb_hstd_dev_descriptor
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_con_descriptor
 Description     : Returns buffer header pointer that includes the configuration 
                 : descriptor.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : uint8_t *      : Configuration Descriptor Pointer
 ******************************************************************************/
uint8_t *usb_hstd_con_descriptor (usb_utr_t *ptr)
{
    return (uint8_t *) &g_usb_hstd_config_descriptor[ptr->ip];
}
/******************************************************************************
 End of function usb_hstd_con_descriptor
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_transfer_start_req
 Description     : Send a request for data transfer to HCD (Host Control Driver) 
                 : using the specified pipe.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : usb_er_t       : USB_OK/USB_QOVR/USB_ERROR
 ******************************************************************************/
usb_er_t usb_hstd_transfer_start_req (usb_utr_t *ptr)
{
    usb_er_t err;
    uint16_t pipenum;
    uint16_t devsel;
    uint16_t connect_inf;

    pipenum = ptr->keyword;

#if (BSP_CFG_RTOS_USED == 0)
    if (USB_MAX_PIPE_NO < pipenum)
    {
        return USB_ERROR;
    }

    if (USB_ON == g_usb_hstd_pipe_request[ptr->ip][pipenum])
    {
        return USB_QOVR;
    }
#endif /* (BSP_CFG_RTOS_USED == 0) */

    /* Pipe Transfer Process check */
    if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][pipenum])
    {
        /* Check PIPE TYPE */
        if (usb_cstd_get_pipe_type(ptr, pipenum) != USB_TYPFIELD_ISO)
        {
            USB_PRINTF1("### usb_hstd_transfer_start_req overlaps %d\n", pipenum);
            return USB_QOVR;
        }
    }

    if (USB_PIPE0 == pipenum)
    {
        devsel = (uint16_t) (ptr->p_setup[4] << USB_DEVADDRBIT);
    }
    else
    {
        /* Get device address from pipe number */
        devsel = usb_hstd_get_devsel(ptr, pipenum);
    }
    if ((USB_DEVICE_0 == devsel) && (USB_PIPE0 != pipenum))
    {
        USB_PRINTF1("### usb_hstd_transfer_start_req not configured %x\n", devsel);
        return USB_ERROR;
    }

    /* Get device speed from device address */
    connect_inf = usb_hstd_get_dev_speed(ptr, devsel);
    if (USB_NOCONNECT == connect_inf)
    {
        USB_PRINTF1("### usb_hstd_transfer_start_req not connect %x\n", devsel);
        return USB_ERROR;
    }

    ptr->msghead = (usb_mh_t) USB_NULL;
    ptr->msginfo = USB_MSG_HCD_SUBMITUTR;

    /* Send message */
    err = USB_SND_MSG(USB_HCD_MBX, (usb_msg_t* )ptr);
#if (BSP_CFG_RTOS_USED == 0)
    if (USB_OK == err)
    {
        g_usb_hstd_pipe_request[ptr->ip][pipenum] = USB_ON;
    }
    else
    {
        USB_PRINTF1("### usb_hstd_transfer_start_req snd_msg error (%ld)\n", err);
    }
#endif /* (BSP_CFG_RTOS_USED == 0) */
    return err;
}
/******************************************************************************
 End of function usb_hstd_transfer_start_req
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_device_resume
 Description     : Send request for RESUME signal output to USB device to MGR task.
 Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 Argument        : uint16_t  devaddr    : Device Address
 Return          : none
 ******************************************************************************/
void usb_hstd_device_resume (usb_utr_t *ptr, uint16_t devaddr)
{
    usb_hstd_mgr_snd_mbx(ptr, (uint16_t) USB_MSG_HCD_RESUME, devaddr, (uint16_t) 0u);
}
/******************************************************************************
 End of function usb_hstd_device_resume
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_hcd_snd_mbx
 Description     : Send specified message to HCD (Host Control Driver) task.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t  msginfo : Message info..
                 : uint16_t  dat     : Pipe no.
                 : uint16_t  *adr    : Address.
                 : usb_cb_t  callback: Callback function pointer.
 Return          : usb_er_t          : USB_OK etc.
 ******************************************************************************/
usb_er_t usb_hstd_hcd_snd_mbx (usb_utr_t *ptr, uint16_t msginfo, uint16_t dat, uint16_t *adr, usb_cb_t callback)
{
    usb_mh_t p_blf;
    usb_er_t err;
    usb_er_t err2;
    usb_hcdinfo_t *hp;

    /* Get memory pool blk */
    err = USB_PGET_BLK(USB_HCD_MPL, &p_blf);
    if (USB_OK == err)
    {
        hp = (usb_hcdinfo_t*) p_blf;
        hp->msghead = (usb_mh_t) USB_NULL;
        hp->msginfo = msginfo;
        hp->keyword = dat;
        hp->p_tranadr = adr;
        hp->complete = callback;
        hp->ipp = ptr->ipp;
        hp->ip = ptr->ip;

        /* Send message */
        err = USB_SND_MSG(USB_HCD_MBX, (usb_msg_t* )p_blf);
        if (USB_OK != err)
        {
            USB_PRINTF1("### hHcdSndMbx snd_msg error (%ld)\n", err);
            err2 = USB_REL_BLK(USB_HCD_MPL, (usb_mh_t )p_blf);
            if (USB_OK != err2)
            {
                USB_PRINTF1("### hHcdSndMbx rel_blk error (%ld)\n", err2);
            }
        }
    }
    else
    {
        USB_PRINTF1("### hHcdSndMbx pget_blk error (%ld)\n", err);
    }
    return err;
}
/******************************************************************************
 End of function usb_hstd_hcd_snd_mbx
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_mgr_snd_mbx
 Description     : Send the message to MGR(Manager) task
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t msginfo  : Message info.
                 : uint16_t dat      : Port no.
                 : uint16_t res      : Result
 Return          : none
 ******************************************************************************/
void usb_hstd_mgr_snd_mbx (usb_utr_t *ptr, uint16_t msginfo, uint16_t dat, uint16_t res)
{
    usb_mh_t p_blf;
    usb_er_t err;
    usb_er_t err2;
    usb_mgrinfo_t *mp;

    /* Get memory pool blk */
    err = USB_PGET_BLK(USB_MGR_MPL, &p_blf);
    if (USB_OK == err)
    {
        mp = (usb_mgrinfo_t *) p_blf;
        mp->msghead = (usb_mh_t) USB_NULL;
        mp->msginfo = msginfo;
        mp->keyword = dat;
        mp->result = res;
        mp->ipp = ptr->ipp;
        mp->ip = ptr->ip;

        /* Send message */
        err = USB_SND_MSG(USB_MGR_MBX, (usb_msg_t * )p_blf);
        if (USB_OK != err)
        {
            USB_PRINTF1("### hMgrSndMbx snd_msg error (%ld)\n", err);
            err2 = USB_REL_BLK(USB_MGR_MPL, (usb_mh_t )p_blf);
            if (USB_OK != err2)
            {
                USB_PRINTF1("### hMgrSndMbx rel_blk error (%ld)\n", err2);
            }
        }
    }
    else
    {
        USB_PRINTF1("### hMgrSndMbx pget_blk error (%ld)\n", err);
    }
}
/******************************************************************************
 End of function usb_hstd_mgr_snd_mbx
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_hcd_rel_mpl
 Description     : Release the secured memory block.
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t n        : Error no.
 Return          : none
 ******************************************************************************/
void usb_hstd_hcd_rel_mpl (usb_utr_t *ptr, uint16_t n)
{
    usb_er_t err;

    /* Memory Pool Release */
    err = USB_REL_BLK(USB_HCD_MPL, (usb_mh_t )ptr);
    if (USB_OK != err)
    {
        USB_PRINTF1("### USB HCD rel_blk error: %d\n", n);
    }
}
/******************************************************************************
 End of function usb_hstd_hcd_rel_mpl
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_suspend
 Description     : Request suspend for USB device.
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 Return          : none
 ******************************************************************************/
void usb_hstd_suspend (usb_utr_t *ptr)
{
    usb_hcdinfo_t* hp;

    /* Control transfer idle stage ? */
    if (USB_IDLEST == g_usb_hstd_ctsq[ptr->ip])
    {
        /* USB suspend process */
        usb_hstd_suspend_process(ptr);
        usb_hstd_chk_clk(ptr, (uint16_t) USB_SUSPENDED); /* Check clock */
        hp = (usb_hcdinfo_t*) ptr; /* Callback */
        if (USB_NULL == hp->complete)   /* Check Callback function */
        {
            while(1)
            {
                /* Error Stop */
            }
        }
        (hp->complete)(ptr, USB_NULL, ptr->msginfo);
    }
    else
    {
        /* 1ms wait */
        usb_cpu_delay_xms((uint16_t) 1);

        /* Change device state request */
        usb_hstd_hcd_snd_mbx(ptr, ptr->msginfo, USB_NULL, (uint16_t*) 0, &usb_hstd_status_result);
    }
}
/******************************************************************************
 End of function usb_hstd_suspend
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_set_submitutr
 Description     : Submit utr: Get the device address via the specified pipe num-
                 : ber and do a USB transfer.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : usb_er_t       : USB_OK
 ******************************************************************************/
static usb_er_t usb_hstd_set_submitutr (usb_utr_t *ptr)
{
    uint16_t pipenum;
    uint16_t devsel;
    uint16_t connect_inf;
    uint16_t end_flag;
    usb_utr_t *pp;

    pipenum = ptr->keyword;
    g_p_usb_hstd_pipe[ptr->ip][pipenum] = ptr;

#if (BSP_CFG_RTOS_USED == 0)
    g_usb_hstd_pipe_request[ptr->ip][pipenum] = USB_OFF;
#endif /* (BSP_CFG_RTOS_USED == 0) */

    /* Get device address from pipe number */
    if (USB_PIPE0 == pipenum)
    {
        devsel = (uint16_t) (ptr->p_setup[4] << USB_DEVADDRBIT);
    }
    else
    {
        /* Get device address from pipe number */
        devsel = usb_hstd_get_devsel(ptr, pipenum);
    }
    if ((USB_DEVICE_0 == devsel) && (USB_PIPE0 != pipenum))
    {
        /* End of data transfer (IN/OUT) */
        usb_hstd_forced_termination(ptr, pipenum, (uint16_t) USB_DATA_ERR);
        return USB_OK;
    }

    /* Get device speed from device address */
    connect_inf = usb_hstd_get_dev_speed(ptr, devsel);
    if (USB_NOCONNECT == connect_inf)
    {
        if (USB_PIPE0 == pipenum)
        {
            /* Control Read/Write End */
            usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR);
        }
        else
        {
            /* End of data transfer (IN/OUT) */
            usb_hstd_forced_termination(ptr, pipenum, (uint16_t) USB_DATA_ERR);
        }
        return USB_OK;
    }

    /* Control Transfer */
    if (USB_PIPE0 == pipenum)
    {
        /* Control transfer idle stage ? */
        if (USB_IDLEST == g_usb_hstd_ctsq[ptr->ip])
        {
            usb_hstd_setup_start(ptr);
        }

        /* Control Read Data */
        else if (USB_DATARDCNT == g_usb_hstd_ctsq[ptr->ip])
        {
            pp = g_p_usb_hstd_pipe[ptr->ip][USB_PIPE0];
            usb_hstd_ctrl_read_start(ptr, pp->tranlen, (uint8_t*) pp->p_tranadr); /* Control read start */
        }

        /* Control Write Data */
        else if (USB_DATAWRCNT == g_usb_hstd_ctsq[ptr->ip])
        {
            pp = g_p_usb_hstd_pipe[ptr->ip][USB_PIPE0];

            /* Control write start */
            end_flag = usb_hstd_ctrl_write_start(ptr, pp->tranlen, (uint8_t*) pp->p_tranadr);
            if (USB_FIFOERROR == end_flag)
            {
                USB_PRINTF0("### FIFO access error \n");
                usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR); /* Control Read/Write End */
            }
        }
        else
        {
            USB_PRINTF0("### Control transfer sequence error \n");

            /* Control Read/Write End */
            usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR);
        }
    }
    else
    {
        usb_hstd_set_retransfer(ptr, pipenum); /* Data Transfer */
    }
    return USB_OK;
}
/******************************************************************************
 End of function usb_hstd_set_submitutr
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_set_retransfer
 Description     : Start IN/OUT transfer based on the specified pipe.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t  pipe : Pipe number
 Return          : none
 ******************************************************************************/
static void usb_hstd_set_retransfer (usb_utr_t *ptr, uint16_t pipe)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return; /* Error */
    }

    /* Data Transfer */
    if (usb_cstd_get_pipe_dir(ptr, pipe) == USB_DIR_H_IN)
    {
        /* IN Transfer */
        usb_hstd_receive_start(ptr, pipe);
    }
    else
    {
        /* OUT Transfer */
        usb_hstd_send_start(ptr, pipe);
    }
}
/******************************************************************************
 End of function usb_hstd_set_retransfer
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_bus_int_disable
 Description     : Disable USB Bus Interrupts OVRCR, ATTCH, DTCH, and BCHG.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : none
 ******************************************************************************/
void usb_hstd_bus_int_disable (usb_utr_t *ptr)
{
    /* ATTCH interrupt disable */
    usb_hstd_attch_disable(ptr);

    /* DTCH     interrupt disable */
    usb_hstd_dtch_disable(ptr);

    /* BCHG     interrupt disable */
    usb_hstd_bchg_disable(ptr);
}
/******************************************************************************
 End of function usb_hstd_bus_int_disable
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_interrupt
 Description     : Execute appropriate process depending on which USB interrupt 
                 : occurred.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : none
 ******************************************************************************/
static void usb_hstd_interrupt (usb_utr_t *ptr)
{
    uint16_t intsts;
    uint16_t end_flag;
    usb_utr_t *pp;
#if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
    usb_compliance_t disp_param;
#endif /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */

    intsts = ptr->keyword;

    /*    bitsts = ptr->status;*/
    switch (intsts)
    {

        /***** Processing PIPE0-MAX_PIPE_NO data *****/
        case USB_INT_BRDY :
            usb_hstd_brdy_pipe(ptr);
        break;
        case USB_INT_BEMP :
            usb_hstd_bemp_pipe(ptr);
        break;
        case USB_INT_NRDY :
            usb_hstd_nrdy_pipe(ptr);
        break;

            /***** Processing Setup transaction *****/
        case USB_INT_SACK :
            switch (g_usb_hstd_ctsq[ptr->ip])
            {
                case USB_SETUPRD :

                    /* Next stage to Control read data */
                    /* continue */
                case USB_SETUPRDCNT :

                    /* Next stage to Control read data */
                    pp = g_p_usb_hstd_pipe[ptr->ip][USB_PIPE0];

                    /* Control read start */
                    usb_hstd_ctrl_read_start(ptr, pp->tranlen, (uint8_t*) pp->p_tranadr);
                break;
                case USB_SETUPWR :

                    /* Next stage to Control Write data */
                    /* continue */
                case USB_SETUPWRCNT :

                    /* Next stage to Control Write data */
                    pp = g_p_usb_hstd_pipe[ptr->ip][USB_PIPE0];

                    /* Control write start */
                    end_flag = usb_hstd_ctrl_write_start(ptr, pp->tranlen, (uint8_t*) pp->p_tranadr);
                    if (USB_FIFOERROR == end_flag)
                    {
                        USB_PRINTF0("### FIFO access error \n");

                        /* Control Read/Write End */
                        usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR);
                    }
                break;
                case USB_SETUPNDC :

                    /* Next stage to Control write no data */
                    usb_hstd_status_start(ptr);
                break;
                default :
                break;
            }
        break;
        case USB_INT_SIGN :
            USB_PRINTF0("***SIGN\n");
#if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
            disp_param.status = USB_CT_SETUP_ERR;
            disp_param.pid    = USB_NULL;
            disp_param.vid    = USB_NULL;
            usb_compliance_disp ((void *)&disp_param);
#endif /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
            /* Ignore count */
            g_usb_hstd_ignore_cnt[ptr->ip][USB_PIPE0]++;
            USB_PRINTF2("### IGNORE Pipe %d is %d times (Setup) \n", USB_PIPE0, g_usb_hstd_ignore_cnt[ptr->ip][USB_PIPE0]);
            if (USB_PIPEERROR == g_usb_hstd_ignore_cnt[ptr->ip][USB_PIPE0])
            {
                /* Setup Device Ignore count over */
                usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_ERR);
            }
            else
            {
                /* Interrupt enable */
                /* 5ms wait */
                usb_cpu_delay_xms((uint16_t) 5u);

                /* Status Clear */
                hw_usb_hclear_sts_sign(ptr);
                hw_usb_hclear_sts_sack(ptr);

                /* Setup Ignore,Setup Acknowledge enable */
                hw_usb_hset_enb_signe(ptr);
                hw_usb_hset_enb_sacke(ptr);

                /* SETUP request send */
                /* Send SETUP request */
                hw_usb_hset_sureq(ptr);
            }
        break;

            /***** Processing rootport0 *****/
        case USB_INT_OVRCR0 :

            /* Port0 OVCR interrupt function */
            usb_hstd_ovrcr0function(ptr);
        break;
        case USB_INT_EOFERR0 :

            /* User program */
        break;
        case USB_INT_ATTCH0 :

            /* Port0 ATCH interrupt function */
            usb_hstd_attach_process(ptr);
        break;
        case USB_INT_BCHG0 :
            USB_PRINTF0("BCHG int port0\n");

            /* Port0 BCHG interrupt function */
            usb_hstd_bchg0function(ptr);
        break;
        case USB_INT_DTCH0 :
            USB_PRINTF0("DTCH int port0\n");

            /* USB detach process */
            usb_hstd_detach_process(ptr);
        break;

#if USB_CFG_BC == USB_CFG_ENABLE
        case USB_INT_PDDETINT0:
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
            /* Port0 PDDETINT interrupt function */
            if (USB_IP1 == ptr->ip)
            {
                usb_hstd_pddetint_process(ptr);
            }

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
        break;
#endif  /* USB_CFG_BC == USB_CFG_ENABLE */

        case USB_INT_VBINT :

            /* User program */
            hw_usb_clear_enb_vbse(ptr);
        break;
        case USB_INT_SOFR :
#if USB_CFG_COMPLIANCE == USB_CFG_ENABLE
            g_usb_hstd_response_counter[ptr->ip]++;
            if (USB_RESPONCE_COUNTER_VALUE == g_usb_hstd_response_counter[ptr->ip])
            {
                hw_usb_clear_enb_sofe( ptr );
                disp_param.status = USB_CT_NORES;
                disp_param.pid    = USB_NULL;
                disp_param.vid    = USB_NULL;
                usb_compliance_disp ((void *)&disp_param);
                usb_hstd_ctrl_end(ptr, (uint16_t)USB_DATA_STOP);
            }
#else  /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
            /* User program */
            hw_usb_clear_enb_sofe(ptr);

#endif /* USB_CFG_COMPLIANCE == USB_CFG_ENABLE */
        break;

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        case USB_INT_DXFIFO:
            usb_dma_stop_dxfifo(ptr->ip, ptr->status);  /* Stop DMA,FIFO access */
            usb_dma_buf2dxfifo_complete(ptr, ptr->status);
        break;
#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

            /*** ERROR ***/
        case USB_INT_UNKNOWN :
            USB_PRINTF0("hINT_UNKNOWN\n");
        break;
        default :
            USB_PRINTF1("hINT_default %X\n", intsts);
        break;
    }
}
/******************************************************************************
 End of function usb_hstd_interrupt
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_clr_feature
 Description     : Send ClearFeature command to the connected USB device.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t addr     : Device address.
                 : uint16_t epnum    : Endpoint number.
                 : usb_cb_t complete : Callback function.
 Return value    : uint16_t          : Error info.
 ******************************************************************************/
usb_er_t usb_hstd_clr_feature (usb_utr_t *ptr, uint16_t addr, uint16_t epnum, usb_cb_t complete)
{
    usb_er_t ret_code;

    if (0xFF == epnum)
    {
        /* ClearFeature(Device) */
        usb_shstd_clr_stall_request[ptr->ip][0] = USB_CLEAR_FEATURE | USB_HOST_TO_DEV | USB_STANDARD | USB_DEVICE;
        usb_shstd_clr_stall_request[ptr->ip][1] = USB_DEV_REMOTE_WAKEUP;
        usb_shstd_clr_stall_request[ptr->ip][2] = (uint16_t) 0x0000;
    }
    else
    {
        /* ClearFeature(endpoint) */
        usb_shstd_clr_stall_request[ptr->ip][0] = USB_CLEAR_FEATURE | USB_HOST_TO_DEV | USB_STANDARD | USB_ENDPOINT;
        usb_shstd_clr_stall_request[ptr->ip][1] = USB_ENDPOINT_HALT;
        usb_shstd_clr_stall_request[ptr->ip][2] = epnum;
    }
    usb_shstd_clr_stall_request[ptr->ip][3] = (uint16_t) 0x0000;
    usb_shstd_clr_stall_request[ptr->ip][4] = addr;

    usb_shstd_clr_stall_ctrl[ptr->ip].p_tranadr = USB_NULL;
    usb_shstd_clr_stall_ctrl[ptr->ip].complete = complete;
    usb_shstd_clr_stall_ctrl[ptr->ip].tranlen = 0;
    usb_shstd_clr_stall_ctrl[ptr->ip].keyword = USB_PIPE0;
    usb_shstd_clr_stall_ctrl[ptr->ip].p_setup = usb_shstd_clr_stall_request[ptr->ip];
    usb_shstd_clr_stall_ctrl[ptr->ip].segment = USB_TRAN_END;

    usb_shstd_clr_stall_ctrl[ptr->ip].ip = ptr->ip;
    usb_shstd_clr_stall_ctrl[ptr->ip].ipp = ptr->ipp;

    ret_code = usb_hstd_transfer_start_req(&usb_shstd_clr_stall_ctrl[ptr->ip]);


#if (BSP_CFG_RTOS_USED == 1)
    if (USB_QOVR == ret_code)
    {
        /** Submit overlap error **/
        /** Retry **/
        do
        {
            usb_cpu_delay_xms((uint16_t)2);
            ret_code = usb_hstd_transfer_start(&usb_shstd_clr_stall_ctrl[ptr->ip]);
        } while (USB_QOVR == ret_code);
    }

    if (USB_OK == ret_code)
    {
        ret_code = class_trans_wait_tmo(ptr, (uint16_t)3000);
    }
#endif /* (BSP_CFG_RTOS_USED == 1) */
    return ret_code;
}
/******************************************************************************
 End of function usb_hstd_clr_feature
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_clr_stall
 Description     : Clear Stall
 Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
                 : uint16_t pipe        : Pipe number.
                 : usb_cb_t complete    : Callback function
 Return value    : uint16_t             : Error info.
 ******************************************************************************/
usb_er_t usb_hstd_clr_stall (usb_utr_t *ptr, uint16_t pipe, usb_cb_t complete)
{
    usb_er_t err;
    uint8_t dir_ep;
    uint16_t devsel;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_ERROR; /* Error */
    }

    dir_ep = usb_hstd_pipe_to_epadr(ptr, pipe);
    devsel = usb_hstd_get_device_address(ptr, pipe);

    err = usb_hstd_clr_feature(ptr, (uint16_t) (devsel >> USB_DEVADDRBIT), (uint16_t) dir_ep, complete);
#if (BSP_CFG_RTOS_USED == 1)
    if (USB_OK == err)
    {
        usb_cstd_clr_stall(ptr, usb_shstd_clr_stall_pipe[ptr->ip]);
        hw_usb_set_sqclr(ptr, usb_shstd_clr_stall_pipe[ptr->ip]); /* SQCLR */
    }
#endif /* (BSP_CFG_RTOS_USED == 1) */
    return err;
}/* End of function usb_hstd_clr_stall() */
/******************************************************************************
 End of function usb_hstd_clr_stall
 ******************************************************************************/

#if (BSP_CFG_RTOS_USED == 0)
/******************************************************************************
 Function Name   : usb_hstd_clr_stall_result
 Description     : Callback function to notify HCD task that usb_hstd_clr_stall function is completed
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t  data1  : Not Use
                 : uint16_t  data2  : Not Use
 Return value    : none
 ******************************************************************************/
static void usb_hstd_clr_stall_result (usb_utr_t *ptr, uint16_t data1, uint16_t data2)
{
    usb_mh_t p_blf;
    usb_er_t err;
    usb_er_t err2;
    usb_utr_t *up;

    /* Get memory pool blk */
    err = USB_PGET_BLK(USB_HCD_MPL, &p_blf);
    if (USB_OK == err)
    {
        up = (usb_utr_t*) p_blf;
        up->msghead = (usb_mh_t) USB_NULL;
        up->msginfo = USB_MSG_HCD_CLR_STALL_RESULT;
        up->status = ptr->status;

        up->ipp = ptr->ipp;
        up->ip = ptr->ip;

        /* Send message */
        err = USB_SND_MSG(USB_HCD_MBX, (usb_msg_t* )p_blf);
        if (USB_OK != err)
        {
            USB_PRINTF1("### hHcdSndMbx snd_msg error (%ld)\n", err);
            err2 = USB_REL_BLK(USB_HCD_MPL, (usb_mh_t )p_blf);
            if (USB_OK != err2)
            {
                USB_PRINTF1("### hHcdSndMbx rel_blk error (%ld)\n", err2);
            }
        }
    }
    else
    {
        USB_PRINTF1("### hHcdSndMbx pget_blk error (%ld)\n", err);
    }
}
/******************************************************************************
 End of function usb_hstd_clr_stall_result
 ******************************************************************************/
#endif /* (BSP_CFG_RTOS_USED == 0) */

/******************************************************************************
 Function Name   : usb_hstd_hcd_task
 Description     : USB Host Control Driver Task.
 Argument        : usb_vp_int_t stacd  : Task Start Code.
 Return          : none
 ******************************************************************************/
void usb_hstd_hcd_task (usb_vp_int_t stacd)
{
    usb_utr_t *p_mess;
    usb_utr_t *ptr;
    usb_er_t err;
    uint16_t rootport;
    uint16_t pipenum;
    uint16_t msginfo;
    uint16_t connect_inf;
#if (BSP_CFG_RTOS_USED == 0)
    uint16_t retval;
#endif /* (BSP_CFG_RTOS_USED == 0) */
    usb_hcdinfo_t* hp;

#if (BSP_CFG_RTOS_USED == 1)
    while (1)
    {
#endif /* (BSP_CFG_RTOS_USED == 1) */
    /* Receive message */
    err = USB_TRCV_MSG(USB_HCD_MBX, (usb_msg_t** )&p_mess, (usb_tm_t )10000);
    if (USB_OK != err)
    {
#if (BSP_CFG_RTOS_USED == 1)
        continue;
#else /* (BSP_CFG_RTOS_USED == 1) */
        return;
#endif /* (BSP_CFG_RTOS_USED == 1 */
    }
    else
    {
        ptr = (usb_utr_t *) p_mess;
        hp = (usb_hcdinfo_t*) p_mess;
        rootport = ptr->keyword;
        pipenum = ptr->keyword;

        /* Branch Hcd Task receive Message Command */
        msginfo = ptr->msginfo;
        switch (msginfo)
        {
            case USB_MSG_HCD_INT :

                /* USB INT */
                usb_hstd_interrupt(ptr);
            break;

            case USB_MSG_HCD_SUBMITUTR :

                /* USB Submit utr */
                usb_hstd_set_submitutr(ptr);
            break;

            case USB_MSG_HCD_ATTACH :

                /* USB attach / detach */
                usb_hstd_attach_process(ptr);

                if (USB_NULL == hp->complete)   /* Check Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                /* Callback */
                (hp->complete)(ptr, rootport, USB_MSG_HCD_ATTACH);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
            break;

            case USB_MSG_HCD_ATTACH_MGR :

                /* USB attach / detach */
                usb_hstd_attach_process(ptr);
                connect_inf = usb_cstd_port_speed(ptr);

                if (USB_NULL == hp->complete)   /* Check Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                /* Callback */
                (hp->complete)(ptr, rootport, connect_inf);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
            break;

            case USB_MSG_HCD_DETACH :

                /* USB detach process */
                usb_hstd_detach_process(ptr);

                if (USB_NULL == hp->complete)   /* Check Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                /* Callback */
                (hp->complete)(ptr, rootport, USB_MSG_HCD_DETACH);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
            break;

            case USB_MSG_HCD_DETACH_MGR :
                hw_usb_clear_dvstctr(ptr, (USB_RWUPE | USB_USBRST | USB_RESUME | USB_UACT));

                usb_cpu_delay_xms(1);

                /* interrupt disable */
                usb_hstd_attch_disable(ptr);
                usb_hstd_dtch_disable(ptr);
                usb_hstd_bchg_disable(ptr);
                if (USB_NULL == hp->complete)   /* Check Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                (hp->complete)(ptr, USB_NULL, USB_MSG_HCD_DETACH_MGR);
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
            break;

            case USB_MSG_HCD_USBRESET :

                /* USB bus reset */
                usb_hstd_bus_reset(ptr);

                /* Check current port speed */
                connect_inf = usb_cstd_port_speed(ptr);

                if (USB_NULL == hp->complete)   /* Check Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                /* Callback */
                (hp->complete)(ptr, USB_NULL, connect_inf);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
            break;

            case USB_MSG_HCD_REMOTE :

                /* Suspend device */
                g_usb_hstd_remort_port[ptr->ip] = USB_SUSPENDED;
                usb_hstd_suspend(ptr);

                if (USB_NULL == hp->complete)   /* Check Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                /* CallBack */
                (hp->complete)(ptr, USB_NULL, USB_MSG_HCD_REMOTE);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
            break;

            case USB_MSG_HCD_SUSPEND :
                usb_hstd_suspend(ptr); /* Suspend device */
                if (USB_NULL == hp->complete)   /* Check Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                (hp->complete)(ptr, rootport, USB_MSG_HCD_SUSPEND);
                usb_hstd_hcd_rel_mpl(ptr, msginfo); /* Release Memory Block */
            break;

            case USB_MSG_HCD_RESUME :
                usb_hstd_resume_process(ptr); /* USB resume */
                if (USB_NULL == hp->complete)   /* Check Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                (hp->complete)(ptr, rootport, USB_MSG_HCD_RESUME); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo); /* Release Memory Block */
            break;

            case USB_MSG_HCD_VBON :

                usb_hstd_ovrcr_enable(ptr); /* Interrupt Enable */

                usb_hstd_vbus_control(ptr, (uint16_t) USB_VBON); /* USB VBUS control ON */
#if USB_CFG_BC == USB_CFG_DISABLE
                /* 100ms wait */
                usb_cpu_delay_xms((uint16_t) 100u);

#endif /* USB_CFG_BC == USB_CFG_DISABLE */

                if (USB_NULL == hp->complete)   /* Check Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                (hp->complete)(ptr, rootport, USB_MSG_HCD_VBON); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo); /* Release Memory Block */
            break;

            case USB_MSG_HCD_VBOFF :
                usb_hstd_vbus_control(ptr, (uint16_t) USB_VBOFF); /* USB VBUS control OFF */
                usb_hstd_ovrcr_disable(ptr);

                usb_cpu_delay_xms((uint16_t) 100u); /* 100ms wait */
                if (USB_NULL == hp->complete)   /* Check Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                (hp->complete)(ptr, rootport, USB_MSG_HCD_VBOFF); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo); /* Release Memory Block */
            break;

            case USB_MSG_HCD_CLR_STALLBIT :
                usb_cstd_clr_stall(ptr, pipenum); /* STALL */
                if (USB_NULL == hp->complete)   /* Check Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                (hp->complete)(ptr, (uint16_t) USB_NO_ARG, (uint16_t) USB_MSG_HCD_CLR_STALLBIT); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo); /* Release Memory Block */
            break;

            case USB_MSG_HCD_SQTGLBIT :
                pipenum = ptr->keyword & USB_PIPENM;
                usb_hstd_do_sqtgl(ptr, pipenum, ptr->keyword); /* SQ toggle */
                if (USB_NULL == hp->complete)   /* Check Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                (hp->complete)(ptr, (uint16_t) USB_NO_ARG, (uint16_t) USB_MSG_HCD_SQTGLBIT); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo); /* Release Memory Block */
            break;

            case USB_MSG_HCD_CLR_STALL :
#if (BSP_CFG_RTOS_USED == 1)
                usb_shstd_clr_stall_pipe[ptr->ip] = pipenum;
                err = usb_hstd_clr_stall(ptr, pipenum, (usb_cb_t) &class_trans_result);
                (hp->complete)(ptr, (uint16_t)err, USB_MSG_HCD_CLR_STALL);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
#else /* (BSP_CFG_RTOS_USED == 1) */
                usb_shstd_clr_stall_call = hp->complete;
                usb_shstd_clr_stall_pipe[ptr->ip] = pipenum;
                err = usb_hstd_clr_stall(ptr, pipenum, (usb_cb_t) &usb_hstd_clr_stall_result);
                if ( USB_QOVR == err)
                {
                    USB_WAI_MSG(USB_HCD_MBX, ptr, 1000); /* Retry */
                }
                else
                {
                    /* Release Memory Block */
                    usb_hstd_hcd_rel_mpl(ptr, msginfo);
                }
#endif /* (BSP_CFG_RTOS_USED == 1) */
            break;
            case USB_MSG_HCD_CLR_STALL_RESULT :
#if (BSP_CFG_RTOS_USED == 1)
                /** Do nothing when running in RTOS
                 * The result will be checked immediately after issuing a "USB_MSG_HCD_CLR_STALL" request. **/
#else /* (BSP_CFG_RTOS_USED == 1) */
                ptr = (usb_utr_t*) p_mess;
                retval = ptr->status;

                if (USB_DATA_TMO == retval)
                {
                    USB_PRINTF0("*** Standard Request Timeout error !\n");
                }
                else if (USB_DATA_STALL == retval)
                {
                    USB_PRINTF0("*** Standard Request STALL !\n");
                }
                else if (USB_CTRL_END != retval)
                {
                    USB_PRINTF0("*** Standard Request error !\n");
                }
                else
                {
                    usb_cstd_clr_stall(ptr, usb_shstd_clr_stall_pipe[ptr->ip]);
                    hw_usb_set_sqclr(ptr, usb_shstd_clr_stall_pipe[ptr->ip]); /* SQCLR */
                }
                if (USB_NULL == usb_shstd_clr_stall_call)   /* Check Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                (*usb_shstd_clr_stall_call)(ptr, retval, USB_MSG_HCD_CLR_STALL);

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
#endif /* (BSP_CFG_RTOS_USED == 1) */
            break;

            case USB_MSG_HCD_CLRSEQBIT :
                hw_usb_set_sqclr(ptr, pipenum); /* SQCLR */
                if (USB_NULL == hp->complete)   /* Check Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                (hp->complete)(ptr, (uint16_t) USB_NO_ARG, (uint16_t) USB_MSG_HCD_CLRSEQBIT); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
            break;

            case USB_MSG_HCD_SETSEQBIT :
                hw_usb_set_sqset(ptr, pipenum); /* SQSET */
                if (USB_NULL == hp->complete)   /* Check Callback function */
                {
                    while(1)
                    {
                        /* Error Stop */
                    }
                }
                (hp->complete)(ptr, (uint16_t) USB_NO_ARG, (uint16_t) USB_MSG_HCD_SETSEQBIT); /* Callback */
                usb_hstd_hcd_rel_mpl(ptr, msginfo); /* Release Memory Block */
            break;

            case USB_MSG_HCD_TRANSEND1 :

                /* Pipe Transfer Process check */
                if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][pipenum])
                {
                    /* Control Transfer stop */
                    if (USB_PIPE0 == pipenum)
                    {
                        /* Control Read/Write End */
                        usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_TMO);
                    }
                    else
                    {
                        /* Transfer stop */
                        usb_hstd_forced_termination(ptr, pipenum, (uint16_t) USB_DATA_TMO);
                    }
                }
                else
                {
                    USB_PRINTF1("### Host not transfer %d\n",pipenum);
                }

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
            break;

            case USB_MSG_HCD_TRANSEND2 :

                /* Pipe Transfer Process check */
                if (USB_NULL != g_p_usb_hstd_pipe[ptr->ip][pipenum])
                {
                    /* Control Transfer stop */
                    if (USB_PIPE0 == pipenum)
                    {
                        /* Control Read/Write End */
                        usb_hstd_ctrl_end(ptr, (uint16_t) USB_DATA_STOP);
                    }
                    else
                    {
                        /* Transfer stop */
                        usb_hstd_forced_termination(ptr, pipenum, (uint16_t) USB_DATA_STOP);
                    }
                }
                else
                {
                    USB_PRINTF1("### Host not transfer %d\n",pipenum);
                }

                /* Release Memory Block */
                usb_hstd_hcd_rel_mpl(ptr, msginfo);
            break;

            case USB_MSG_HCD_D1FIFO_INT :
            break;

            case USB_MSG_HCD_RESM_INT :
            break;

            default :
            break;
        }
    }
#if (BSP_CFG_RTOS_USED == 1)
    } /* End of while(1) */
#endif /* (BSP_CFG_RTOS_USED == 1) */
}
/******************************************************************************
 End of function usb_hstd_hcd_task
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_send_start
 Description     : Start data transmission using CPU/DMA transfer to USB host/
                 : /device.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t pipe  : Pipe no.
 Return value    : none
 ******************************************************************************/
void usb_hstd_send_start (usb_utr_t *ptr, uint16_t pipe)
{
    usb_utr_t *pp;
    uint32_t length;
    uint16_t useport;
#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    uint16_t dma_ch;
#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

    if (USB_MAX_PIPE_NO < pipe)
    {
        return; /* Error */
    }

    /* Evacuation pointer */
    pp = g_p_usb_hstd_pipe[ptr->ip][pipe];
    length = pp->tranlen;

    /* Check transfer count */
    if (USB_TRAN_CONT == pp->segment)
    {
        /* Sequence toggle */
        usb_hstd_do_sqtgl(ptr, pipe, pp->pipectr);
    }

    usb_cstd_select_nak(ptr, pipe); /* Select NAK */
    g_usb_hstd_data_cnt[ptr->ip][pipe] = length; /* Set data count */
    g_p_usb_hstd_data[ptr->ip][pipe] = (uint8_t*) pp->p_tranadr; /* Set data pointer */
    g_usb_hstd_ignore_cnt[ptr->ip][pipe] = (uint16_t) 0; /* Ignore count clear */

    hw_usb_clear_status_bemp(ptr, pipe); /* BEMP Status Clear */
    hw_usb_clear_sts_brdy(ptr, pipe); /* BRDY Status Clear */

    useport = usb_hstd_pipe2fport(ptr, pipe);/* Pipe number to FIFO port select */

    /* Check use FIFO access */
    switch (useport)
    {

        case USB_CUSE : /* CFIFO use */

            /* Buffer to FIFO data write */
            usb_hstd_buf_to_fifo(ptr, pipe, useport);
            usb_cstd_set_buf(ptr, pipe); /* Set BUF */

        break;

        case USB_D0USE : /* D0FIFO use */

            /* D0 FIFO access is NG */
            USB_PRINTF1("### USB-ITRON is not support(SND-D0USE:pipe%d)\n", pipe);
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);

        break;

            /* D1FIFO use */
        case USB_D1USE :

            /* Buffer to FIFO data write */
            usb_hstd_buf_to_fifo(ptr, pipe, useport);
            usb_cstd_set_buf(ptr, pipe); /* Set BUF */

        break;

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        /* D0FIFO DMA */
        case USB_D0DMA:
        /* D1FIFO DMA */
        case USB_D1DMA:
            if (USB_IP0 == ptr->ip)
            {
                dma_ch = USB_CFG_USB0_DMA_TX;
            }
            else
            {
                dma_ch = USB_CFG_USB1_DMA_TX;
            }
            usb_dma_set_ch_no(ptr->ip, useport, dma_ch);
            /* Setting for use PIPE number */
            g_usb_cstd_dma_pipe[ptr->ip][dma_ch] = pipe;
            /* Buffer size */
            g_usb_cstd_dma_fifo[ptr->ip][dma_ch] = usb_cstd_get_buf_size(ptr, pipe);
            /* Check data count */
            if (g_usb_hstd_data_cnt[ptr->ip][pipe] <= g_usb_cstd_dma_fifo[ptr->ip][dma_ch])
            {
                /* Transfer data size */
                g_usb_cstd_dma_size[ptr->ip][dma_ch] = g_usb_hstd_data_cnt[ptr->ip][pipe];
                /* Enable Empty Interrupt */
                hw_usb_set_bempenb(ptr, pipe);
            }
            else
            {
                /* Data size == FIFO size */
                g_usb_cstd_dma_size[ptr->ip][dma_ch] = (g_usb_hstd_data_cnt[ptr->ip][pipe]
                        - (g_usb_hstd_data_cnt[ptr->ip][pipe] % g_usb_cstd_dma_fifo[ptr->ip][dma_ch]));
            }

            usb_cstd_buf2dxfifo_start_dma( ptr, pipe, useport );

            /* Set BUF */
            usb_cstd_set_buf(ptr, pipe);
        break;
#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

        default :

            /* Access is NG */
            USB_PRINTF1("### USB-ITRON is not support(SND-else:pipe%d)\n", pipe);
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);

        break;
    }
}
/******************************************************************************
 End of function usb_hstd_send_start
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_fifo_to_buf
 Description     : Request readout from USB FIFO to buffer and process depending
                 : on status; read complete or reading.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
                 : uint16_t pipe  : Pipe no.
 Return value    : none
 ******************************************************************************/
void usb_hstd_fifo_to_buf (usb_utr_t *ptr, uint16_t pipe, uint16_t useport)
{
    uint16_t end_flag;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return; /* Error */
    }

    /* Ignore count clear */
    g_usb_hstd_ignore_cnt[ptr->ip][pipe] = (uint16_t) 0;
    end_flag = USB_ERROR;

    end_flag = usb_hstd_read_data(ptr, pipe, useport);

    /* Check FIFO access sequence */
    switch (end_flag)
    {
        case USB_READING :

            /* Continue of data read */

        break;

        case USB_READEND :

            /* End of data read */
            usb_hstd_data_end(ptr, pipe, (uint16_t) USB_DATA_OK);

        break;

        case USB_READSHRT :

            /* End of data read */
            usb_hstd_data_end(ptr, pipe, (uint16_t) USB_DATA_SHT);

        break;

        case USB_READOVER :

            /* Buffer over */
            USB_PRINTF1("### Receive data over PIPE%d\n",pipe);
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_OVR);

        break;

        case USB_FIFOERROR :

            /* FIFO access error */
            USB_PRINTF0("### FIFO access error \n");
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);

        break;

        default :
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);
        break;
    }
}
/******************************************************************************
 End of function usb_hstd_fifo_to_buf
 ******************************************************************************/

 /******************************************************************************
 Function Name   : usb_hstd_buf_to_fifo
 Description     : Set USB registers as required to write from data buffer to USB 
                 : FIFO, to have USB FIFO to write data to bus.
 Arguments       : usb_utr_t    *ptr : Pointer to usb_utr_t structure.
                 : uint16_t pipe     : Pipe no.
                 : uint16_t useport  : Port no.
 Return value    : none
 ******************************************************************************/
void usb_hstd_buf_to_fifo (usb_utr_t *ptr, uint16_t pipe, uint16_t useport)
{
    uint16_t end_flag;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return; /* Error */
    }

    /* Disable Ready Interrupt */
    hw_usb_clear_brdyenb(ptr, pipe);

    /* Ignore count clear */
    g_usb_hstd_ignore_cnt[ptr->ip][pipe] = (uint16_t) 0;

    end_flag = usb_hstd_write_data(ptr, pipe, useport);

    /* Check FIFO access sequence */
    switch (end_flag)
    {
        case USB_WRITING :

            /* Continue of data write */
            /* Enable Ready Interrupt */
            hw_usb_set_brdyenb(ptr, pipe);

            /* Enable Not Ready Interrupt */
            usb_cstd_nrdy_enable(ptr, pipe);

        break;

        case USB_WRITEEND :

            /* End of data write */
            /* continue */

        case USB_WRITESHRT :

            /* End of data write */
            /* Enable Empty Interrupt */
            hw_usb_set_bempenb(ptr, pipe);

            /* Enable Not Ready Interrupt */
            usb_cstd_nrdy_enable(ptr, pipe);

        break;
        case USB_FIFOERROR :

            /* FIFO access error */
            USB_PRINTF0("### FIFO access error \n");
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);

        break;
        default :
            usb_hstd_forced_termination(ptr, pipe, (uint16_t) USB_DATA_ERR);
        break;
    }
}
/******************************************************************************
 End of function usb_hstd_buf_to_fifo
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_class_request_complete
 Description     : Class request transfer complete
 Arguments       : usb_utr_t *mess  : Pointer to usb_utr_t structure.
                 : uint16_t  data1  : Not used.
                 : uint16_t  data2  : Not used.
 Return          : none
 ******************************************************************************/
void usb_class_request_complete (usb_utr_t *mess, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    if (USB_CTRL_END == mess->status) /* Check usb receive status */
    {
        ctrl.status = USB_ACK;
    }
    else if (USB_DATA_STALL == mess->status) /* Check usb receive status */
    {
        ctrl.status = USB_STALL;
    }
    else
    {
        ctrl.status = USB_ERROR;
    }
    ctrl.type = USB_REQUEST;
    ctrl.module = mess->ip; /* Module number setting */
    ctrl.setup.type = mess->p_setup[0];
    ctrl.pipe = USB_PIPE0;
    ctrl.setup.value = mess->p_setup[1];
    ctrl.setup.index = mess->p_setup[2];
    ctrl.setup.length = mess->p_setup[3];
    ctrl.address = mess->p_setup[4];
    ctrl.size = ctrl.setup.length - g_usb_hstd_data_cnt[mess->ip][USB_PIPE0];
    usb_set_event(USB_STS_REQUEST_COMPLETE, &ctrl); /* Set Event()  */
}
/******************************************************************************
 End of function usb_class_request_complete
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_transfer_end
 Description     : Request HCD to force termination of data transfer.
 Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
                 : uint16_t pipe        : Pipe number
                 : uint16_t status      : Data transfer status
 Return          : usb_err_t error code : USB_OK etc
 ******************************************************************************/
usb_er_t usb_hstd_transfer_end (usb_utr_t *ptr, uint16_t pipe, uint16_t status)
{
    uint16_t msg;
    usb_er_t err;

#if (BSP_CFG_RTOS_USED == 0)
    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_ERROR; /* Error */
    }

    if (USB_ON == g_usb_hstd_pipe_request[ptr->ip][pipe])
    {
        return USB_ERROR;
    }
#endif /* (BSP_CFG_RTOS_USED == 0) */

    if (USB_NULL == g_p_usb_hstd_pipe[ptr->ip][pipe])
    {
        USB_PRINTF1("### usb_hstd_transfer_end overlaps %d\n", pipe);
        return USB_QOVR;
    }

    if (USB_DATA_TMO == status)
    {
        msg = USB_MSG_HCD_TRANSEND1;
    }
    else
    {
        msg = USB_MSG_HCD_TRANSEND2;
    }

    err = usb_hstd_hcd_snd_mbx(ptr, msg, pipe, (uint16_t*) 0, &usb_hstd_dummy_function);
    return err;
}
/******************************************************************************
 End of function usb_hstd_transfer_end
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_driver_registration
 Description     : The HDCD information registered in the class driver structure
                 : is registered in HCD.
 Arguments       : usb_utr_t *ptr           : Pointer to usb_utr_t structure.
                 : usb_hcdreg_t *callback   : Pointer to usb_hcdreg_t structure
 Return          : none
 ******************************************************************************/
void usb_hstd_driver_registration (usb_utr_t *ptr, usb_hcdreg_t *callback)
{
    usb_hcdreg_t *driver;

    if (g_usb_hstd_device_num[ptr->ip] <= USB_MAXDEVADDR)
    {
        driver = &g_usb_hstd_device_drv[ptr->ip][g_usb_hstd_device_num[ptr->ip]];

        driver->rootport = USB_NOPORT; /* Root port */
        driver->devaddr = USB_NODEVICE; /* Device address */
        driver->devstate = USB_DETACHED; /* Device state */
        driver->ifclass = callback->ifclass; /* Interface Class */
        driver->p_tpl = callback->p_tpl; /* Target peripheral list */
        driver->classinit = callback->classinit; /* Driver init */
        driver->classcheck = callback->classcheck; /* Driver check */
        driver->devconfig = callback->devconfig; /* Device configured */
        driver->devdetach = callback->devdetach; /* Device detach */
        driver->devsuspend = callback->devsuspend; /* Device suspend */
        driver->devresume = callback->devresume; /* Device resume */

        if (USB_NULL == driver->classinit)   /* Check Callback function */
        {
            while(1)
            {
                /* Error Stop */
            }
        }
        /* Initialized device driver */
        (*driver->classinit)(ptr, driver->devaddr, (uint16_t) USB_NO_ARG);

        g_usb_hstd_device_num[ptr->ip]++;
        USB_PRINTF1("*** Registration driver 0x%02x\n",driver->ifclass);
    }
    else
    {
        USB_PRINTF0("### Registration device driver over\n");
    }
}
/******************************************************************************
 End of function usb_hstd_driver_registration
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_driver_release
 Description     : Release the Device Class Driver.
 Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
                 : uint8_t   devclass   : Interface class
 Return          : none
 ******************************************************************************/
void usb_hstd_driver_release (usb_utr_t *ptr, uint8_t devclass)
{
    usb_hcdreg_t *driver;
    uint16_t i;
    uint16_t flg;

    if (USB_IFCLS_NOT == devclass)
    {
        /* Device driver number */
        g_usb_hstd_device_num[ptr->ip] = 0;
    }
    else
    {
        for (flg = 0u, i = 0u
        ; (i < (USB_MAXDEVADDR + 1u)) && (0u == flg); i++)
        {
            driver = &g_usb_hstd_device_drv[ptr->ip][i];
            if (driver->ifclass == devclass)
            {

                driver->rootport = USB_NOPORT; /* Root port */
                driver->devaddr = USB_NODEVICE; /* Device address */
                driver->devstate = USB_DETACHED; /* Device state */

                /* Interface Class : NO class */
                driver->ifclass = (uint16_t) USB_IFCLS_NOT;

                g_usb_hstd_device_num[ptr->ip]--;
                USB_PRINTF1("*** Release class %d driver ***\n",devclass);
                flg = 1u; /* break; */
            }
        }
    }
}
/******************************************************************************
 End of function usb_hstd_driver_release
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_set_pipe_info
 Description     : Copy information of pipe information table from source
                 :  (2nd argument) to destination (1st argument)
 Argument        : usb_pipe_table_t *dst_ep_tbl      : DEF_EP table pointer(destination)
                 : usb_pipe_table_t *src_ep_tbl      : DEF_EP table pointer(source)
 Return          : none
 ******************************************************************************/
void usb_hstd_set_pipe_info (uint16_t ip_no, uint16_t pipe_no, usb_pipe_table_reg_t *src_ep_tbl)
{
    g_usb_pipe_table[ip_no][pipe_no].use_flag  = USB_TRUE;
    g_usb_pipe_table[ip_no][pipe_no].pipe_cfg  = src_ep_tbl->pipe_cfg;
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    if (USB_IP1 == ip_no)
    {
        g_usb_pipe_table[ip_no][pipe_no].pipe_buf  = src_ep_tbl->pipe_buf;
    }
#endif /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
    g_usb_pipe_table[ip_no][pipe_no].pipe_maxp = src_ep_tbl->pipe_maxp;
    g_usb_pipe_table[ip_no][pipe_no].pipe_peri = src_ep_tbl->pipe_peri;
}
/******************************************************************************
 End of function usb_hstd_set_pipe_info
 ******************************************************************************/


#if (BSP_CFG_RTOS_USED == 0)
/******************************************************************************
 Function Name   : usb_hstd_return_enu_mgr
 Description     : Continuous enumeration is requested to MGR task (API for nonOS)
 Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
                 : uint16_t cls_result  : class check result
 Return          : none
 ******************************************************************************/
void usb_hstd_return_enu_mgr (usb_utr_t *ptr, uint16_t cls_result)
{
    g_usb_hstd_check_enu_result[ptr->ip] = cls_result;
    usb_hstd_mgr_snd_mbx(ptr, USB_MSG_MGR_SUBMITRESULT, USB_PIPE0, USB_CTRL_END);
}
/******************************************************************************
 End of function usb_hstd_return_enu_mgr
 ******************************************************************************/

#endif  /* (BSP_CFG_RTOS_USED == 0) */

/******************************************************************************
 Function Name   : usb_hstd_change_device_state
 Description     : Request to change the status of the connected USB Device
 Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
                 : usb_cb_t complete    : callback function pointer
                 : uint16_t msginfo     : Message Info
                 : uint16_t member      : Device address/pipe number
 Return          : usb_err_t            : USB_OK etc
 ******************************************************************************/
usb_er_t usb_hstd_change_device_state (usb_utr_t *ptr, usb_cb_t complete, uint16_t msginfo, uint16_t member)
{
    usb_mh_t p_blf;
    usb_er_t err;
    usb_er_t err2;
    usb_hcdinfo_t *hp;

    switch (msginfo)
    {
        /* USB_MSG_HCD_CLR_STALL */
        case USB_DO_CLR_STALL :
            err = usb_hstd_hcd_snd_mbx(ptr, USB_MSG_HCD_CLR_STALL, member, (uint16_t*) 0, complete);
        break;

            /* USB_MSG_HCD_SQTGLBIT */
        case USB_DO_SET_SQTGL :
            err = usb_hstd_hcd_snd_mbx(ptr, USB_MSG_HCD_SETSEQBIT, member, (uint16_t*) 0, complete);
        break;

            /* USB_MSG_HCD_CLRSEQBIT */
        case USB_DO_CLR_SQTGL :
            err = usb_hstd_hcd_snd_mbx(ptr, USB_MSG_HCD_CLRSEQBIT, member, (uint16_t*) 0, complete);
        break;

        default :

            /* Get memory pool blk */
            err = USB_PGET_BLK(USB_MGR_MPL, &p_blf);
            if (err == USB_SUCCESS)
            {
                USB_PRINTF2("*** member%d : msginfo=%d ***\n", member, msginfo);
                hp = (usb_hcdinfo_t*) p_blf;
                hp->msghead = (usb_mh_t) USB_NULL;
                hp->msginfo = msginfo;
                hp->keyword = member;
                hp->complete = complete;

                hp->ipp = ptr->ipp;
                hp->ip = ptr->ip;

                /* Send message */
                err = USB_SND_MSG(USB_MGR_MBX, (usb_msg_t* )p_blf);
                if (err != USB_SUCCESS)
                {
                    USB_PRINTF1("### hMgrChangeDeviceState snd_msg error (%ld)\n", err);
                    err2 = USB_REL_BLK(USB_MGR_MPL, (usb_mh_t )p_blf);
                    if (err2 != USB_SUCCESS)
                    {
                        USB_PRINTF1("### hMgrChangeDeviceState rel_blk error (%ld)\n", err2);
                    }
                }
            }
            else
            {
                USB_PRINTF1("### hMgrChangeDeviceState pget_blk error (%ld)\n", err);
                err = USB_ERROR;
            }
        break;
    }
    return err;
}
/******************************************************************************
 End of function usb_hstd_change_device_state
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_hcd_open
 Description     : Start HCD(Host Control Driver) task
 Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
 Return          : usb_err_t            : USB_OK etc
 ******************************************************************************/
usb_err_t usb_hstd_hcd_open (usb_utr_t *ptr)
{
    static uint8_t is_init = USB_NO;
    uint16_t i;
    uint16_t j;
    usb_err_t err = USB_SUCCESS;

    if (USB_MAXDEVADDR < USB_DEVICEADDR)
    {
        USB_PRINTF0("Device address error\n");

        /* >yes no process */
        return USB_ERR_NG;
    }

    /* Global Init */
    if (USB_NO == is_init)
    {
#if (BSP_CFG_RTOS_USED == 0)
        usb_shstd_clr_stall_call = 0;
#endif /* (BSP_CFG_RTOS_USED == 0) */


        usb_shstd_clr_stall_pipe[0] = 0;
        memset((void *)&usb_shstd_clr_stall_ctrl[0], 0, sizeof(usb_utr_t));
        memset((void *)usb_shstd_clr_stall_request[0], 0, (5*2));
#if (USB_NUM_USBIP == 2)
        usb_shstd_clr_stall_pipe[1] = 0;
        memset((void *)&usb_shstd_clr_stall_ctrl[1], 0, sizeof(usb_utr_t));
        memset((void *)usb_shstd_clr_stall_request[1], 0, (5*2));
#endif
        is_init = USB_YES;
    }


    for (i =0; i< (USB_MAXDEVADDR + 1); i++)
    {
        memset((void *)&g_usb_hstd_device_drv[ptr->ip][i], 0, sizeof(usb_hcdreg_t));
        memset((void *)&g_usb_hstd_device_info[ptr->ip][i], 0, (8 * 2));
        g_usb_hstd_dcp_register[ptr->ip][i] = 0;
        memset((void *)&g_usb_ctrl_request[ptr->ip][i], 0, sizeof(usb_ctrl_trans_t));
    }

    for (i =0; i< (USB_MAX_PIPE_NO + 1); i++)
    {
        g_usb_hstd_data_cnt[ptr->ip][i] = 0;
        g_p_usb_hstd_data[ptr->ip][i] = 0;
        g_usb_hstd_ignore_cnt[ptr->ip][i] = 0;
        g_usb_hstd_pipe_request[ptr->ip][i] = 0;
    }

    g_usb_hstd_device_addr[ptr->ip] = 0;
    g_usb_hstd_device_speed[ptr->ip] = 0;
    g_usb_hstd_device_num[ptr->ip] = 0;

    /* Control transfer stage management */
    g_usb_hstd_ctsq[ptr->ip] = USB_IDLEST;

    g_usb_hstd_remort_port[ptr->ip] = USB_DEFAULT;

    for (i = USB_PIPE0; i <= USB_MAX_PIPE_NO; i++)
    {
        g_p_usb_hstd_pipe[j][i] = (usb_utr_t*) USB_NULL;
    }

#if USB_CFG_BC == USB_CFG_ENABLE
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    if (USB_IP1 == ptr->ip)
    {
        g_usb_hstd_bc[ptr->ip].state = USB_BC_STATE_INIT;
    }

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
#endif  /* USB_CFG_BC == USB_CFG_ENABLE */

    USB_PRINTF0("*** Install USB-HCD ***\n");

    usb_cstd_set_task_pri(USB_HCD_TSK, USB_PRI_1);

    return err;
}
/******************************************************************************
 End of function usb_hstd_hcd_open
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_dummy_function
 Description     : Dummy function
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t data1    : Not used.
                 : uint16_t data2    : Not used.
 Return value    : none
 ******************************************************************************/
void usb_hstd_dummy_function (usb_utr_t *ptr, uint16_t data1, uint16_t data2)
{
    /* None */
}
/******************************************************************************
 End of function usb_hstd_dummy_function
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_suspend_complete
 Description     : usb_hstd_change_device_state callback (Suspend)
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t data1   : Not used.
                 : uint16_t data2   : Not used.
 Return value    : none
 ******************************************************************************/
void usb_hstd_suspend_complete (usb_utr_t *ptr, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;
    
    g_usb_change_device_state[ptr->ip] &= (~(1 << USB_STS_SUSPEND));

    ctrl.module     = ptr->ip;      /* USB Module Number */
    ctrl.address    = 1;            /* Device Address Number */

    usb_set_event(USB_STS_SUSPEND, &ctrl);
}
/******************************************************************************
 End of function usb_hstd_suspend_complete
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_resume_complete
 Description     : usb_hstd_change_device_state callback (Resume)
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure.
                 : uint16_t data1   : Not used.
                 : uint16_t data2   : Not used.
 Return value    : none
 ******************************************************************************/
void usb_hstd_resume_complete (usb_utr_t *ptr, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    g_usb_change_device_state[ptr->ip] &= (~(1 << USB_STS_RESUME));

    ctrl.module     = ptr->ip;
    ctrl.address    = 1;

    usb_set_event(USB_STS_RESUME, &ctrl);
}/* End of function usb_hstd_resume_complete */


/******************************************************************************
 Function Name  : usb_hstd_device_information
 Description    : Get the status of the connected USB Device
 Arguments      : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
                : uint16_t devaddr  : Device address
                : uint16_t *tbl     : Table Pointer
 Return         : None
******************************************************************************/
void usb_hstd_device_information (usb_utr_t *ptr, uint16_t devaddr, uint16_t *tbl)
{
    uint16_t    i, port, *p;

    if( devaddr == 0 )
    {
        for( p = tbl, i = 0; i < 8; ++i )
        {
            *p++ = USB_NOPORT;
        }

        port = g_usb_hstd_device_info[ptr->ip][devaddr][0];
        tbl[0] = port;
        tbl[1] = g_usb_hstd_mgr_mode[ptr->ip];
        tbl[4] = g_usb_hstd_device_info[ptr->ip][devaddr][4];

    }
    else
    {
        for( i = 0; i < 8; ++i )
        {
            tbl[i] = g_usb_hstd_device_info[ptr->ip][devaddr][i];
        }
    }
    tbl[8] = g_usb_hstd_mgr_mode[ptr->ip];
}
/******************************************************************************
 End of function usb_hstd_device_information
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_host_registration
 Description     : sample registration.
 Argument        : usb_utr_t    *ptr   : Pointer to usb_utr_t structure.
 Return          : none
 ******************************************************************************/
void usb_host_registration (usb_utr_t *ptr)
{

#if defined(USB_CFG_HCDC_USE)
    usb_hcdc_registration(ptr);

#endif /* defined(USB_CFG_PCDC_USE) */

#if defined(USB_CFG_HHID_USE)
    usb_hhid_registration(ptr);

#endif /* defined(USB_CFG_HMSC_USE) */

#if defined(USB_CFG_HMSC_USE)
    usb_hmsc_registration(ptr);

#endif /* defined(USB_CFG_HMSC_USE) */

#if defined(USB_CFG_HVND_USE)
    usb_hvendor_registration(ptr);

#endif /* defined(USB_CFG_HVND_USE) */
}
/******************************************************************************
 End of function usb_host_registration
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_transfer_start
 Description     : Send a request for data transfer to HCD (Host Control Driver) 
                 : using the specified pipe.
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return          : usb_er_t       : USB_OK/USB_QOVR/USB_ERROR
 ******************************************************************************/
usb_er_t usb_hstd_transfer_start (usb_utr_t *ptr)
{
    usb_er_t        err;

    /* Check enumeration  */
    if( ptr->keyword == USB_PIPE0 )
    {
        if (USB_DEFAULT == g_usb_hstd_mgr_mode[ptr->ip])
        {
            return USB_QOVR;
        }
    }

    err = usb_hstd_transfer_start_req( ptr );

    return err;
}
/******************************************************************************
 End of function usb_hstd_transfer_start
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_hstd_connect_err_event_set
 Description     : Set event for "USB_STS_NOT_SUPPORT"
 Arguments       : uint16_t ip_no  : IP no.(USB_IP0/USB_IP1)
 Return          : none
 ******************************************************************************/
void usb_hstd_connect_err_event_set(uint16_t ip_no)
{
    usb_ctrl_t ctrl;

    ctrl.address = g_usb_hstd_device_addr[ip_no];       /* usb device address */
    ctrl.module = ip_no;                                /* module number setting */
    usb_set_event(USB_STS_NOT_SUPPORT, &ctrl);          /* set event()  */
}
/******************************************************************************
 End of function usb_hstd_connect_err_event_set
 ******************************************************************************/

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 End  Of File
 ******************************************************************************/

