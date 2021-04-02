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
 * Copyright (C) 2015(2018) Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_usb_pdriver.c
 * Description  : USB Peripheral driver code.
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 Rename "usb_pstd_buf2fifo"->"usb_pstd_buf_to_fifo" and Function move from"r_usb_plibusbip.c"
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_bitdefine.h"
#include "r_usb_reg_access.h"
#include "r_usb_basic_define.h"

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
#include "r_usb_dmac.h"
#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
/******************************************************************************
Private global variables and functions
******************************************************************************/
#if (BSP_CFG_RTOS_USED == 1)
//static void usb_pstd_interrupt(usb_int_t *);
static void usb_pstd_interrupt(usb_utr_t *);
#else /*(BSP_CFG_RTOS_USED == 1)*/
static void usb_pstd_interrupt (uint16_t type, uint16_t status);
#endif /*(BSP_CFG_RTOS_USED == 1)*/

/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/
uint16_t g_usb_pstd_stall_pipe[USB_MAX_PIPE_NO + 1u];   /* Stall Pipe info */
usb_cb_t g_usb_pstd_stall_cb;                           /* Stall Callback function */
uint16_t g_usb_pstd_config_num = 0;                     /* Current configuration number */
uint16_t g_usb_pstd_alt_num[USB_ALT_NO];                /* Alternate number */
uint16_t g_usb_pstd_remote_wakeup = USB_FALSE;          /* Remote wake up enable flag */
uint16_t g_usb_pstd_remote_wakeup_state;                /* Result for Remote wake up */

uint16_t g_usb_pstd_test_mode_select;                   /* Test mode selectors */
uint16_t g_usb_pstd_test_mode_flag = USB_FALSE;         /* Test mode flag */

uint16_t g_usb_pstd_eptbl_index[2][USB_MAX_EP_NO + 1u]; /* Index of endpoint information table */
uint16_t g_usb_pstd_req_type;                           /* Request type */
uint16_t g_usb_pstd_req_value;                          /* Value */
uint16_t g_usb_pstd_req_index;                          /* Index */
uint16_t g_usb_pstd_req_length;                         /* Length */

uint16_t g_usb_pstd_pipe0_request;

uint16_t g_usb_peri_connected;                          /* Status for USB connect. */

/* Driver registration */
usb_pcdreg_t g_usb_pstd_driver;
usb_setup_t g_usb_pstd_req_reg;                         /* Device Request - Request structure */

/******************************************************************************
Exported global variables
******************************************************************************/


/******************************************************************************
 Renesas Abstracted Peripheral Driver functions
 ******************************************************************************/
#if (BSP_CFG_RTOS_USED == 0)
/******************************************************************************
 Function Name   : usb_pstd_interrupt
 Description     : Analyze the USB Peripheral interrupt event and execute the
                 : appropriate process.
 Arguments       : uint16_t type      : Interrupt type.
                 : uint16_t status    : BRDYSTS register & BRDYENB register.
 Return value    : none
 ******************************************************************************/
static void usb_pstd_interrupt (uint16_t type, uint16_t status)
{
    uint16_t stginfo;

    /* check interrupt status */
    switch (type)
    {
        /* BRDY, BEMP, NRDY */
        case USB_INT_BRDY :
            usb_pstd_brdy_pipe(status);
        break;
        case USB_INT_BEMP :
            usb_pstd_bemp_pipe(status);
        break;
        case USB_INT_NRDY :
            usb_pstd_nrdy_pipe(status);
        break;

            /* Resume */
        case USB_INT_RESM :
            USB_PRINTF0("RESUME int peri\n");

            /* Callback */
            if (USB_NULL != g_usb_pstd_driver.devresume)
            {
                (*g_usb_pstd_driver.devresume)(USB_NULL, USB_NO_ARG, USB_NULL);
            }
            usb_pstd_resume_process();
        break;

            /* VBUS */
        case USB_INT_VBINT :
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
            hw_usb_set_cnen();
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
            if (usb_pstd_chk_vbsts() == USB_ATTACH)
            {
                USB_PRINTF0("VBUS int attach\n");
                usb_pstd_attach_process();    /* USB attach */
            }
            else
            {
                USB_PRINTF0("VBUS int detach\n");
                usb_pstd_detach_process();    /* USB detach */
            }
        break;

            /* SOF */
        case USB_INT_SOFR :

            /* User program */
        break;

            /* DVST */
        case USB_INT_DVST :
            switch ((uint16_t) (status & USB_DVSQ))
            {
                /* Power state  */
                case USB_DS_POWR :
                break;

                    /* Default state  */
                case USB_DS_DFLT :
                    USB_PRINTF0("USB-reset int peri\n");
                    usb_pstd_bus_reset();
                break;

                    /* Address state  */
                case USB_DS_ADDS :
                break;

                    /* Configured state  */
                case USB_DS_CNFG :
                    USB_PRINTF0("Device configuration int peri\n");
                break;

                    /* Power suspend state */
                case USB_DS_SPD_POWR :

                    /* Continue */
                    /* Default suspend state */
                case USB_DS_SPD_DFLT :

                    /* Continue */
                    /* Address suspend state */
                case USB_DS_SPD_ADDR :

                    /* Continue */
                    /* Configured Suspend state */
                case USB_DS_SPD_CNFG :
                    USB_PRINTF0("SUSPEND int peri\n");
                    usb_pstd_suspend_process();
                break;

                    /* Error */
                default :
                break;
            }
        break;

            /* CTRT */
        case USB_INT_CTRT :
            stginfo = (uint16_t) (status & USB_CTSQ);
            if (USB_CS_IDST == stginfo)
            {
                /* check Test mode */
                if (USB_TRUE == g_usb_pstd_test_mode_flag)
                {
                    /* Test mode */
                    usb_pstd_test_mode();
                }
            }
            else
            {
                if (((USB_CS_RDDS == stginfo) || (USB_CS_WRDS == stginfo)) || (USB_CS_WRND == stginfo))
                {
                    /* Save request register */
                    usb_pstd_save_request();
                }
            }

            if ((g_usb_pstd_req_type & USB_BMREQUESTTYPETYPE) == USB_STANDARD)
            {
                /* Switch on the control transfer stage (CTSQ). */
                switch (stginfo)
                {
                    /* Idle or setup stage */
                    case USB_CS_IDST :
                        g_usb_pstd_pipe0_request = USB_OFF;
                        usb_pstd_stand_req0();
                    break;

                    /* Control read data stage */
                    case USB_CS_RDDS :
                        usb_pstd_stand_req1();
                    break;

                    /* Control write data stage */
                    case USB_CS_WRDS :
                        usb_pstd_stand_req2();
                    break;

                    /* Status stage of a control write where there is no data stage. */
                    case USB_CS_WRND :
                        usb_pstd_stand_req3();
                    break;

                    /* Control read status stage */
                    case USB_CS_RDSS :
                        usb_pstd_stand_req4();
                    break;

                    /* Control write status stage */
                    case USB_CS_WRSS :
                        usb_pstd_stand_req5();
                    break;

                    /* Control sequence error */
                    case USB_CS_SQER :
                        usb_pstd_ctrl_end((uint16_t) USB_DATA_ERR);
                    break;

                    /* Illegal */
                    default :
                        usb_pstd_ctrl_end((uint16_t) USB_DATA_ERR);
                    break;
                }
            }
            else
            {
                /* Vender Specific */
                g_usb_pstd_req_reg.type = g_usb_pstd_req_type;
                g_usb_pstd_req_reg.value = g_usb_pstd_req_value;
                g_usb_pstd_req_reg.index = g_usb_pstd_req_index;
                g_usb_pstd_req_reg.length = g_usb_pstd_req_length;

                /* Callback */
                if (USB_NULL != g_usb_pstd_driver.ctrltrans)
                {
                    (*g_usb_pstd_driver.ctrltrans)((usb_setup_t *) &g_usb_pstd_req_reg, stginfo);
                }
            }
        break;

            /* Error */
        case USB_INT_UNKNOWN :
            USB_PRINTF0("pINT_UNKNOWN\n");
        break;
        default :
        break;
    }
}
/******************************************************************************
 End of function usb_pstd_interrupt
 ******************************************************************************/
#endif /*(BSP_CFG_RTOS_USED == 0)*/

#if (BSP_CFG_RTOS_USED == 1)
/******************************************************************************
 Function Name   : usb_pstd_interrupt
 Description     : Analyze the USB Peripheral interrupt event and execute the
 : appropriate process.
 Arguments       : uint16_t type      : Interrupt type.
                 : uint16_t status    : BRDYSTS register & BRDYENB register.
 Return value    : none
 ******************************************************************************/
//static void usb_pstd_interrupt (usb_int_t *p_mess)
static void usb_pstd_interrupt (usb_utr_t *p_mess)
{
    uint16_t    stginfo;
    uint16_t    type;
    uint16_t    status;
#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    uint16_t    fifo_type;

//    fifo_type   = p_mess->fifo_type;
    fifo_type   = p_mess->status;
#endif
//    type        = p_mess->type;
    type        = p_mess->keyword;
    status      = p_mess->status;

    /* check interrupt status */
    switch (type)
    {
        /* BRDY, BEMP, NRDY */
        case USB_INT_BRDY :
            usb_pstd_brdy_pipe(status);
        break;
        case USB_INT_BEMP :
            usb_pstd_bemp_pipe(status);
        break;
        case USB_INT_NRDY :
            usb_pstd_nrdy_pipe(status);
        break;

            /* Resume */
        case USB_INT_RESM :
            USB_PRINTF0("RESUME int peri\n");

            /* Callback */
            if (USB_NULL != g_usb_pstd_driver.devresume)
            {
                (*g_usb_pstd_driver.devresume)(USB_NULL, USB_NO_ARG, USB_NULL);
            }
            usb_pstd_resume_process();
        break;

            /* VBUS */
        case USB_INT_VBINT :
#if defined(BSP_MCU_RX64M) || (BSP_MCU_RX71M)
            hw_usb_set_cnen();
#endif  /* defined(BSP_MCU_RX64M) || (BSP_MCU_RX71M) */
            if (usb_pstd_chk_vbsts() == USB_ATTACH)
            {
                USB_PRINTF0("VBUS int attach\n");
                usb_pstd_attach_process();    /* USB attach */
            }
            else
            {
                USB_PRINTF0("VBUS int detach\n");
                usb_pstd_detach_process();    /* USB detach */
            }
        break;

            /* SOF */
        case USB_INT_SOFR :

            /* User program */
        break;

            /* DVST */
        case USB_INT_DVST :
            switch ((uint16_t) (status & USB_DVSQ))
            {
                /* Power state  */
                case USB_DS_POWR :
                break;

                    /* Default state  */
                case USB_DS_DFLT :
                    USB_PRINTF0("USB-reset int peri\n");
                    usb_pstd_bus_reset();
                break;

                    /* Address state  */
                case USB_DS_ADDS :
                break;

                    /* Configured state  */
                case USB_DS_CNFG :
                    USB_PRINTF0("Device configuration int peri\n");
                break;

                    /* Power suspend state */
                case USB_DS_SPD_POWR :

                    /* Continue */
                    /* Default suspend state */
                case USB_DS_SPD_DFLT :

                    /* Continue */
                    /* Address suspend state */
                case USB_DS_SPD_ADDR :

                    /* Continue */
                    /* Configured Suspend state */
                case USB_DS_SPD_CNFG :
                    USB_PRINTF0("SUSPEND int peri\n");
                    usb_pstd_suspend_process();
                break;

                    /* Error */
                default :
                break;
            }
        break;

            /* CTRT */
        case USB_INT_CTRT :
            stginfo = (uint16_t) (status & USB_CTSQ);
            if (USB_CS_IDST == stginfo)
            {
                /* check Test mode */
                if (USB_TRUE == g_usb_pstd_test_mode_flag)
                {
                    /* Test mode */
                    usb_pstd_test_mode();
                }
            }
            else
            {
                if (((USB_CS_RDDS == stginfo) || (USB_CS_WRDS == stginfo)) || (USB_CS_WRND == stginfo))
                {
                    /* Save request register */
                    usb_pstd_save_request();
                }
            }

            if ((g_usb_pstd_req_type & USB_BMREQUESTTYPETYPE) == USB_STANDARD)
            {
                /* Switch on the control transfer stage (CTSQ). */
                switch (stginfo)
                {
                    /* Idle or setup stage */
                    case USB_CS_IDST :
                        usb_pstd_stand_req0();
                    break;

                    /* Control read data stage */
                    case USB_CS_RDDS :
                        usb_pstd_stand_req1();
                    break;

                    /* Control write data stage */
                    case USB_CS_WRDS :
                        usb_pstd_stand_req2();
                    break;

                    /* Status stage of a control write where there is no data stage. */
                    case USB_CS_WRND :
                        usb_pstd_stand_req3();
                    break;

                    /* Control read status stage */
                    case USB_CS_RDSS :
                        usb_pstd_stand_req4();
                    break;

                    /* Control write status stage */
                    case USB_CS_WRSS :
                        usb_pstd_stand_req5();
                    break;

                    /* Control sequence error */
                    case USB_CS_SQER :
                        usb_pstd_ctrl_end((uint16_t) USB_DATA_ERR);
                    break;

                    /* Illegal */
                    default :
                        usb_pstd_ctrl_end((uint16_t) USB_DATA_ERR);
                    break;
                }
            }
            else
            {
                /* Vender Specific */
                g_usb_pstd_req_reg.type = g_usb_pstd_req_type;
                g_usb_pstd_req_reg.value = g_usb_pstd_req_value;
                g_usb_pstd_req_reg.index = g_usb_pstd_req_index;
                g_usb_pstd_req_reg.length = g_usb_pstd_req_length;

                /* Callback */
                if (USB_NULL != g_usb_pstd_driver.ctrltrans)
                {
                    (*g_usb_pstd_driver.ctrltrans)((usb_setup_t *) &g_usb_pstd_req_reg, stginfo);
                }
            }
        break;

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        case USB_INT_DXFIFO:
            usb_dma_stop_dxfifo(USB_CFG_USE_USBIP, fifo_type);  /* Stop DMA,FIFO access */
            usb_dma_buf2dxfifo_complete(USB_NULL, fifo_type);
        break;
#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

            /* Error */
        case USB_INT_UNKNOWN :
            USB_PRINTF0("pINT_UNKNOWN\n");
        break;
        default :
        break;
    }
}
/******************************************************************************
 End of function usb_pstd_interrupt
 ******************************************************************************/
#endif /*(BSP_CFG_RTOS_USED == 1)*/

/******************************************************************************
 Function Name   : usb_pstd_pcd_task
 Description     : The Peripheral Control Driver(PCD) task.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_pcd_task (void)
{
#if (BSP_CFG_RTOS_USED == 0)
    if (g_usb_pstd_usb_int.wp != g_usb_pstd_usb_int.rp)
    {
        /* Pop Interrupt info */
        usb_pstd_interrupt(g_usb_pstd_usb_int.buf[g_usb_pstd_usb_int.rp].type,
                g_usb_pstd_usb_int.buf[g_usb_pstd_usb_int.rp].status);

        /* Read CountUp */
        g_usb_pstd_usb_int.rp = ((g_usb_pstd_usb_int.rp + 1) % USB_INT_BUFSIZE);
    }
#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
    usb_dma_driver();           /* USB DMA driver */
#endif  /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */
#endif /*(BSP_CFG_RTOS_USED == 0)*/

#if (BSP_CFG_RTOS_USED == 1)
      usb_er_t    err;
//    usb_int_t   *p_mess;
    usb_utr_t   *p_mess;
    
    while(1)
    {
        err = USB_TRCV_MSG(USB_PCD_MBX, (usb_msg_t **)&p_mess, (usb_tm_t)1000);
        if (USB_OK == err)
        {
            switch (p_mess->msginfo)
            {
                case USB_MSG_PCD_INT:
                    usb_pstd_interrupt(p_mess);
                break;

                case USB_MSG_PCD_SUBMITUTR:
                    usb_pstd_set_submitutr(p_mess);
                break;

                case USB_MSG_PCD_TRANSEND1:
                    usb_pstd_forced_termination(p_mess->keyword, (uint16_t)USB_DATA_STOP);
                break;

                case USB_MSG_PCD_REMOTEWAKEUP:
                    usb_pstd_self_clock();
                    usb_pstd_remote_wakeup();
                break;

                default:
                break;
            }
        }
    }
#endif /*(BSP_CFG_RTOS_USED == 1)*/
}
/******************************************************************************
 End of function usb_pstd_pcd_task
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_set_submitutr
 Description     : USB Peripheral Submit utr.
 Arguments       : usb_utr_t *utrmsg    : Pointer to usb_utr_t structure
 Return value    : usb_er_t
 ******************************************************************************/
usb_er_t usb_pstd_set_submitutr (usb_utr_t * utrmsg)
{
    uint16_t pipenum;

    pipenum = utrmsg->keyword;
    g_p_usb_pstd_pipe[pipenum] = utrmsg;

    /* Check state (Configured) */
    if (usb_pstd_chk_configured() == USB_TRUE)
    {
        /* Data transfer */
        if (usb_cstd_get_pipe_dir(USB_NULL, pipenum) == USB_DIR_P_OUT)
        {
            usb_pstd_receive_start(pipenum);    /* Out transfer */
        }
        else
        {
            /* In transfer */
            usb_pstd_send_start(pipenum);
        }
    }
    else
    {
        /* Transfer stop */
        usb_pstd_forced_termination(pipenum, (uint16_t) USB_DATA_ERR);
    }
    return USB_OK;
}
/******************************************************************************
 End of function usb_pstd_set_submitutr
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_clr_alt
 Description     : Zero-clear the alternate table (buffer).
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_clr_alt (void)
{
    uint16_t i;

    for (i = 0; i < USB_ALT_NO; ++i)
    {
        /* Alternate table clear */
        g_usb_pstd_alt_num[i] = 0;
    }
}
/******************************************************************************
 End of function usb_pstd_clr_alt
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_clr_mem
 Description     : Initialize global variables defined for peripheral mode.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_clr_mem (void)
{
    g_usb_pstd_config_num = 0;               /* Configuration number */
    g_usb_pstd_remote_wakeup = USB_FALSE;    /* Remote wake up enable flag */
    usb_pstd_clr_alt();                      /* Alternate setting clear */
}
/******************************************************************************
 End of function usb_pstd_clr_mem
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_set_config_num
 Description     : Set specified configuration number.
 Arguments       : uint16_t value    : Configuration number
 Return value    : none
 ******************************************************************************/
void usb_pstd_set_config_num (uint16_t value)
{
    g_usb_pstd_config_num = value;    /* Set configuration number */
    usb_pstd_clr_alt();               /* Alternate setting clear */
}
/******************************************************************************
 End of function usb_pstd_set_config_num
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_clr_eptbl_index
 Description     : Clear Endpoint Index Table (buffer).
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_clr_eptbl_index (void)
{
    uint16_t i;

    for (i = 0; i <= USB_MAX_EP_NO; ++i)
    {
        /* EndPoint index table clear */
        g_usb_pstd_eptbl_index[0][i] = USB_ERROR;
        g_usb_pstd_eptbl_index[1][i] = USB_ERROR;
    }
}
/******************************************************************************
 End of function usb_pstd_clr_eptbl_index
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_get_interface_num
 Description     : Get interface number
 Arguments       : void
 Return value    : uint16_t         : Number of this interface(bNumInterfaces)
 ******************************************************************************/
uint16_t usb_pstd_get_interface_num (void)
{
    uint16_t num_if = 0;

    /* Get NumInterfaces.        4:bNumInterfaces */
    num_if = *(uint8_t *) (g_usb_pstd_driver.p_configtbl + USB_DEV_B_NUM_INTERFACES);

    return num_if;
}
/******************************************************************************
 End of function usb_pstd_get_interface_num
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_get_alternate_num
 Description     : Get Alternate Setting Number
 Arguments       : void
                 : uint16_t int_num : Interface Number
 Return value    : uint16_t         : Value used to select this alternate (bAlternateSetting)
 ******************************************************************************/
uint16_t usb_pstd_get_alternate_num (uint16_t int_num)
{
    uint16_t i;
    uint16_t alt_num = 0;
    uint8_t * ptr;
    uint16_t length;

    ptr = g_usb_pstd_driver.p_configtbl;
    i = ptr[0];

    /* Interface descriptor[0] */
    ptr = (uint8_t *) ((uint32_t) ptr + ptr[0]);
    length = (uint16_t) (*(uint8_t *) ((uint32_t) g_usb_pstd_driver.p_configtbl + (uint16_t) 2u));
    length |= (uint16_t) ((uint16_t) (*(uint8_t *) ((uint32_t) g_usb_pstd_driver.p_configtbl + (uint16_t) 3u)) << 8u);

    /* Search descriptor table size */
    for (; i < length;)
    {
        /* Descriptor type ? */
        switch (ptr[1])
        {
            /* Interface */
            case USB_DT_INTERFACE :
                if (int_num == ptr[2])
                {
                    /* Alternate number count */
                    alt_num = (uint16_t) ptr[3];
                }
                i += ptr[0];

                /* Interface descriptor[0] */
                ptr = (uint8_t *) ((uint32_t) ptr + ptr[0]);
            break;

                /* Device */
            case USB_DT_DEVICE :

                /* Continue */
                /* Configuration */
            case USB_DT_CONFIGURATION :

                /* Continue */
                /* String */
            case USB_DT_STRING :

                /* Continue */
                /* EndPoint */
            case USB_DT_ENDPOINT :

                /* Continue */
                /* Class, Vendor, else */
            default :
                i += ptr[0];

                /* Interface descriptor[0] */
                ptr = (uint8_t *) ((uint32_t) ptr + ptr[0]);
            break;
        }
    }
    return alt_num;
}
/******************************************************************************
 End of function usb_pstd_get_alternate_num
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_set_eptbl_index
 Description     : Set endpoint index in table (buffer) region based on config-
                 : uration descriptor. In other words, set which endpoints to
                 : use based on specified configuration,
 Arguments       : void
                 : uint16_t int_num : Interface Number.
                 : uint16_t alt_num : Alternate Setting.
 Return value    : none
 ******************************************************************************/
void usb_pstd_set_eptbl_index (uint16_t int_num, uint16_t alt_num)
{
    uint8_t * ptr;
    uint16_t i;
    uint16_t j;
    uint16_t length;
    uint16_t start;
    uint16_t numbers;
    uint16_t ep;
    uint16_t dir;

    /* Configuration descriptor */
    ptr = g_usb_pstd_driver.p_configtbl;
    i = *ptr;
    length = (uint16_t) (*(uint8_t *) ((uint32_t) ptr + (uint32_t) 3u));
    length = (uint16_t) (length << 8);
    length += (uint16_t) (*(uint8_t *) ((uint32_t) ptr + (uint32_t) 2u));
    ptr = (uint8_t *) ((uint32_t) ptr + (*ptr));
    start = 0;
    numbers = 0;
    j = 0;

    for (; i < length;)
    {
        /* Descriptor type ? */
        switch (*(uint8_t *) ((uint32_t) ptr + (uint32_t) 1u))
        {
            /* Interface */
            case USB_DT_INTERFACE :
                if (((*(uint8_t *) ((uint32_t) ptr + (uint32_t) 2u)) == int_num)
                        && ((*(uint8_t *) ((uint32_t) ptr + (uint32_t) 3u)) == alt_num))
                {
                    numbers = *(uint8_t *) ((uint32_t) ptr + (uint32_t) 4u);
                }
                else
                {
                    start += (*(uint8_t *) ((uint32_t) ptr + (uint32_t) 4u));
                }
                i += (*ptr);
                ptr = (uint8_t *) ((uint32_t) ptr + (*ptr));
            break;

                /* Endpoint */
            case USB_DT_ENDPOINT :
                if (j < numbers)
                {
                    ep = (uint16_t) *(uint8_t *) ((uint32_t) ptr + (uint32_t) 2u);
                    if (USB_EP_IN == (ep & USB_EP_DIRMASK))
                    {
                        dir = 1; /* IN */
                    }
                    else
                    {
                        dir = 0; /* OUT */
                    }
                    ep &= (uint16_t) 0x0f;
                    g_usb_pstd_eptbl_index[dir][ep] = (uint8_t) (start + j);
                    ++j;
                }
                i += (*ptr);
                ptr = (uint8_t *) ((uint32_t) ptr + (*ptr));
            break;

                /* Device */
            case USB_DT_DEVICE :

                /* Continue */
                /* Configuration */
            case USB_DT_CONFIGURATION :

                /* Continue */
                /* String */
            case USB_DT_STRING :

                /* Continue */
                /* Class, Vendor, else */
            default :
                i += (*ptr);
                ptr = (uint8_t *) ((uint32_t) ptr + (*ptr));
            break;
        }
    }
}
/******************************************************************************
 End of function usb_pstd_set_eptbl_index
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_chk_remote
 Description     : Check if the RemoteWakeUp bit for the configuration descriptor is set.
 Arguments       : none
 Return value    : uint16_t : remote wakeup status (TRUE/FALSE).
 ******************************************************************************/
uint16_t usb_pstd_chk_remote (void)
{
    uint8_t atr;

    if (0 == g_usb_pstd_config_num)
    {
        return USB_FALSE;
    }

    /* Get Configuration Descriptor - bmAttributes */
    atr = *(uint8_t *) ((uint32_t) g_usb_pstd_driver.p_configtbl + (uint32_t) 7u);

    /* Remote WakeUp check(= D5) */
    if ((atr & USB_CF_RWUPON) == USB_CF_RWUPON)
    {
        return USB_TRUE;
    }
    return USB_FALSE;
}
/******************************************************************************
 End of function usb_pstd_chk_remote
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_get_current_power
 Description     : Find out how the peripheral is powered by looking at the con-
                 : figuration descriptor.
 Arguments       : none
 Return value    : uint8_t : Current power means; self-powered or bus-powered
                 : (GS_SELFPOWERD/GS_BUSPOWERD).
 ******************************************************************************/
uint8_t usb_pstd_get_current_power (void)
{
    /*
     * Please answer the currently power of your system.
     */

    uint8_t tmp;
    uint8_t currentpower;

    /* Standard configuration descriptor */
    tmp = *(uint8_t *) ((uint32_t) g_usb_pstd_driver.p_configtbl + (uint32_t) 7u);
    if ((tmp & USB_CF_SELFP) == USB_CF_SELFP)
    {
        /* Self Powered */
        currentpower = USB_GS_SELFPOWERD;
    }
    else
    {
        /* Bus Powered */
        currentpower = USB_GS_BUSPOWERD;
    }

    /* Check currently powered */

    return currentpower;
}
/******************************************************************************
 End of function usb_pstd_get_current_power
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_fifo_to_buf
 Description     : Request readout from USB FIFO to buffer and process depending
                 : on status; read complete or reading.
 Arguments       : uint16_t pipe     : Pipe no.
                 : uint16_t useport  : FIFO select(USB_CUSE,USB_DMA0,....)
 Return value    : none
 ******************************************************************************/
void usb_pstd_fifo_to_buf(uint16_t pipe, uint16_t useport)
{
    uint16_t end_flag;

    end_flag = USB_ERROR;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return; /* Error */
    }

    end_flag = usb_pstd_read_data(pipe, useport);

    /* Check FIFO access sequence */
    switch (end_flag)
    {
        case USB_READING:

        /* Continue of data read */
        break;

        case USB_READEND:

        /* End of data read */
        usb_pstd_data_end(pipe, (uint16_t)USB_DATA_OK);
        break;

        case USB_READSHRT:

        /* End of data read */
        usb_pstd_data_end(pipe, (uint16_t)USB_DATA_SHT);
        break;

        case USB_READOVER:

        /* Buffer over */
        USB_PRINTF1("### Receive data over PIPE%d\n", pipe);
        usb_pstd_forced_termination(pipe, (uint16_t)USB_DATA_OVR);
        break;

        case USB_FIFOERROR:

        /* FIFO access error */
        USB_PRINTF0("### FIFO access error \n");
        usb_pstd_forced_termination(pipe, (uint16_t)USB_DATA_ERR);
        break;

        default:
        usb_pstd_forced_termination(pipe, (uint16_t)USB_DATA_ERR);
        break;
    }
}
/******************************************************************************
 End of function usb_pstd_fifo_to_buf
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_buf_to_fifo
 Description     : Set USB registers as required to write from data buffer to USB
 : FIFO, to have USB FIFO to write data to bus.
 Arguments       : uint16_t pipe     : Pipe no.
                 : uint16_t useport  : Port no.
 Return value    : none
 ******************************************************************************/
void usb_pstd_buf_to_fifo(uint16_t pipe, uint16_t useport)
{
    uint16_t end_flag;

    if (USB_MAX_PIPE_NO < pipe)
    {
        return; /* Error */
    }

    /* Disable Ready Interrupt */
    hw_usb_clear_brdyenb(USB_NULL,pipe);

    end_flag = usb_pstd_write_data(pipe, useport);

    /* Check FIFO access sequence */
    switch (end_flag)
    {
        case USB_WRITING:
            /* Continue of data write */
            /* Enable Ready Interrupt */
            hw_usb_set_brdyenb(USB_NULL,pipe);

            /* Enable Not Ready Interrupt */
            usb_cstd_nrdy_enable(USB_NULL, pipe);
        break;

        case USB_WRITEEND:
            /* End of data write */
            /* continue */
        case USB_WRITESHRT:
            /* End of data write */
            /* Enable Empty Interrupt */
            hw_usb_set_bempenb(USB_NULL,pipe);

            /* Enable Not Ready Interrupt */
            usb_cstd_nrdy_enable(USB_NULL, pipe);
        break;

        case USB_FIFOERROR:
            /* FIFO access error */
            USB_PRINTF0("### FIFO access error \n");
            usb_pstd_forced_termination(pipe, (uint16_t)USB_DATA_ERR);
        break;

        default:
            usb_pstd_forced_termination(pipe, (uint16_t)USB_DATA_ERR);
        break;
    }
}
/******************************************************************************
 End of function usb_pstd_buf_to_fifo
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_transfer_start
 Description     : Transfer the data of each pipe
                 : Request PCD to transfer data, and the PCD transfers the data
                 : based on the transfer information stored in ptr
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return value    : usb_er_t       : Error info.
 ******************************************************************************/
usb_er_t usb_pstd_transfer_start(usb_utr_t * ptr)
{
    usb_er_t err;
    uint16_t pipenum;

    pipenum = ptr->keyword;
    if (USB_NULL != g_p_usb_pstd_pipe[pipenum])
    {
        /* Get PIPE TYPE */
        if (usb_cstd_get_pipe_type(USB_NULL, pipenum) != USB_ISO)
        {
            USB_PRINTF1("### usb_pstd_transfer_start overlaps %d\n", pipenum);
            return USB_QOVR;
        }
    }

    /* Check state (Configured) */
    if (usb_pstd_chk_configured() != USB_TRUE)
    {
        USB_PRINTF0("### usb_pstd_transfer_start not configured\n");
        return USB_ERROR;
    }

    if (USB_PIPE0 == pipenum)
    {
        USB_PRINTF0("### usb_pstd_transfer_start PIPE0 is not support\n");
        return USB_ERROR;
    }


#if (BSP_CFG_RTOS_USED == 0)
    err = usb_pstd_set_submitutr(ptr);
#else /* BSP_CFG_RTOS_USED == 0 */
    ptr->msghead = (usb_mh_t) USB_NULL;
    ptr->msginfo = USB_MSG_PCD_SUBMITUTR;

    /* Send message */
    err = USB_SND_MSG(USB_PCD_MBX, (usb_msg_t* )ptr);
#endif /* (BSP_CFG_RTOS_USED == 0) */

    return err;
}
/******************************************************************************
 End of function usb_pstd_transfer_start
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_transfer_end
 Description     : Force termination of data transfer of specified pipe. Request
                 : PCD to force termination data transfer, 
                 : and the PCD forced-terminates data transfer.
 Arguments       : uint16_t pipe     : Pipe number.
 Return value    : usb_er_t          : Error info.
 ******************************************************************************/
usb_er_t usb_pstd_transfer_end(uint16_t pipe)
{
#if (BSP_CFG_RTOS_USED == 1)
    usb_utr_t   utr;
#endif /* (BSP_CFG_RTOS_USED == 1) */

    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_ERROR; /* Error */
    }

    if (USB_NULL == g_p_usb_pstd_pipe[pipe])
    {
        USB_PRINTF0("### usb_pstd_transfer_end overlaps\n");
        return USB_ERROR;
    }
    else
    {
#if (BSP_CFG_RTOS_USED == 0)
        usb_pstd_forced_termination(pipe, (uint16_t)USB_DATA_STOP);
#else /* BSP_CFG_RTOS_USED == 0 */
        utr.msghead = (usb_mh_t) USB_NULL;
        utr.msginfo = USB_MSG_PCD_TRANSEND1;
        utr.keyword = pipe;

        /* Send message */
        return USB_SND_MSG(USB_PCD_MBX, (usb_msg_t* )&utr);
#endif /* (BSP_CFG_RTOS_USED == 0) */
    }

    return USB_OK;
}
/******************************************************************************
 End of function usb_pstd_transfer_end
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_change_device_state
 Description     : Change USB Device to the status specified by argument
 Arguments       : uint16_t state            : New device status.
                 : uint16_t keyword          : Pipe number etc.
                 : usb_cb_t complete         : Callback function.
 Return value    : none
 ******************************************************************************/
void usb_pstd_change_device_state(uint16_t state, uint16_t keyword, usb_cb_t complete)
{
    uint16_t pipenum;
#if (BSP_CFG_RTOS_USED == 1)
    static usb_utr_t   utr;
    uint16_t    err;
#endif /* (BSP_CFG_RTOS_USED == 1) */

    pipenum = keyword;
    switch(state)
    {
        case USB_DO_STALL:
            usb_pstd_set_stall(pipenum);
            g_usb_pstd_stall_pipe[pipenum] = USB_TRUE;
            g_usb_pstd_stall_cb = complete;
        break;

        case USB_DO_REMOTEWAKEUP:
#if (BSP_CFG_RTOS_USED == 0)
            usb_pstd_self_clock();
            usb_pstd_remote_wakeup();
#else   /* BSP_CFG_RTOS_USED == 0 */
            utr.msghead = (usb_mh_t) USB_NULL;
            utr.msginfo = USB_MSG_PCD_REMOTEWAKEUP;

            /* Send message */
            err = USB_SND_MSG(USB_PCD_MBX, (usb_msg_t* )&utr);
            if (USB_OK != err)
            {
                g_usb_pstd_remote_wakeup_state = USB_ERROR;
            }

#endif  /* BSP_CFG_RTOS_USED == 0 */
        break;

        case USB_MSG_PCD_DP_ENABLE:
            hw_usb_pset_dprpu();
        break;

        case USB_MSG_PCD_DP_DISABLE:
            hw_usb_pclear_dprpu();
        break;
        
        default:
        break;
    }
}
/******************************************************************************
 End of function usb_pstd_change_device_state
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_driver_registration
 Description     : Register pipe information table, descriptor information table,
                 : callback function, etc. This info is specified by the data in
                 : the structure usb_pcdreg_t.
 Arguments       : usb_pcdreg_t *registinfo     : Class driver structure.
 Return value    : none
 ******************************************************************************/
void usb_pstd_driver_registration(usb_pcdreg_t * registinfo)
{
    usb_pcdreg_t *driver;

    driver = &g_usb_pstd_driver;

    driver->p_devicetbl = registinfo->p_devicetbl;   /* Device descriptor table address */
    driver->p_qualitbl  = registinfo->p_qualitbl;    /* Qualifier descriptor table address */
    driver->p_configtbl = registinfo->p_configtbl;   /* Configuration descriptor table address */
    driver->p_othertbl  = registinfo->p_othertbl;    /* Other configuration descriptor table address */
    driver->p_stringtbl = registinfo->p_stringtbl;   /* String descriptor table address */
    driver->devdefault  = registinfo->devdefault;    /* Device default */
    driver->devconfig   = registinfo->devconfig;     /* Device configured */
    driver->devdetach   = registinfo->devdetach;     /* Device detach */
    driver->devsuspend  = registinfo->devsuspend;    /* Device suspend */
    driver->devresume   = registinfo->devresume;     /* Device resume */
    driver->interface   = registinfo->interface;     /* Interfaced change */
    driver->ctrltrans   = registinfo->ctrltrans;     /* Control transfer */
    driver->num_string  = registinfo->num_string;    /* String descriptor number */
}
/******************************************************************************
 End of function  usb_pstd_driver_registration
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_driver_release
 Description     : Clear the information registered in the structure usb_pcdreg_t.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_driver_release(void)
{
    usb_pcdreg_t *driver;

    driver = &g_usb_pstd_driver;
    driver->p_devicetbl = (uint8_t*)0u;              /* Device descriptor table address */
    driver->p_qualitbl = (uint8_t*)0u;               /* Qualifier descriptor table address */
    driver->p_configtbl = (uint8_t*)0u;              /* Configuration descriptor table address */
    driver->p_othertbl = (uint8_t*)0u;               /* Other configuration descriptor table address */
    driver->p_stringtbl = (uint8_t**)0u;             /* String descriptor table address */
    driver->devdefault = &usb_pstd_dummy_function; /* Device default */
    driver->devconfig = &usb_pstd_dummy_function;  /* Device configured */
    driver->devdetach = &usb_pstd_dummy_function;  /* Device detach */
    driver->devsuspend = &usb_pstd_dummy_function; /* Device suspend */
    driver->devresume = &usb_pstd_dummy_function;  /* Device resume */
    driver->interface = &usb_pstd_dummy_function;  /* Interfaced change */
    driver->ctrltrans = &usb_pstd_dummy_trn;       /* Control transfer */

}/* End of function usb_pstd_driver_release() */

/******************************************************************************
 Function Name   : usb_pstd_dummy_function
 Description     : dummy function
 Arguments       : usb_utr_t    *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t     data1   : Not used
                 : uint16_t     data2   : Not used
 Return value    : none
 ******************************************************************************/
void usb_pstd_dummy_function(usb_utr_t *ptr, uint16_t data1, uint16_t data2)
{
    /* Dummy function */
}
/******************************************************************************
 End of function usb_pstd_dummy_function
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_dummy_trn
 Description     : Class request processing for dummy
 Arguments       : usb_setup_t *preq  ; Class request information
 : uint16_t ctsq        ; Control Stage
 Return value    : none
 ******************************************************************************/
void usb_pstd_dummy_trn(usb_setup_t * preq, uint16_t ctsq)
{
    /* Dummy function */
} /* End of function usb_pstd_dummy_trn */

/******************************************************************************
Function Name   : usb_pstd_device_information
Description     : Get USB Device information such as USB Device status and con-
                : figuration No. etc. 
 Arguments      : usb_utr_t *ptr  : Pointer to usb_utr_t structure.
                : uint16_t *tbl   : Device information storage pointer TBL. This 
                :                   pointer is used to provide the caller with the device's sta-
                :                   tus, speed, configuration and interface number, and the value
                :                   of the remote wakeup flag.
Return value    : none
******************************************************************************/
void usb_pstd_device_information (usb_utr_t *ptr, uint16_t *tbl)
{
    /* Device status */
    tbl[0] = hw_usb_read_intsts() & (uint16_t)(USB_VBSTS|USB_DVSQ);

    /* Speed */
    tbl[1] = usb_cstd_port_speed (ptr);

    /* Configuration number */
    tbl[2] = g_usb_pstd_config_num;

    /* Interface number */
    tbl[3] = usb_pstd_get_interface_num ();

    /* Remote Wakeup Flag */
    tbl[4] = g_usb_pstd_remote_wakeup;
}/* End of function usb_pstd_device_information() */

/******************************************************************************
Function Name   : usb_pstd_set_stall_clr_feature
Description     : Set pipe stall request
Arguments       : usb_utr_t *ptr        : Pointer to usb_utr_t structure.
                : usb_cb_t  complete    : callback function
                : uint16_t  pipe        : pipe number
Return value    : usb_er_t              : Error Info
******************************************************************************/
usb_er_t usb_pstd_set_stall_clr_feature (usb_utr_t *ptr, usb_cb_t complete, uint16_t pipe)
{
    if (USB_MAX_PIPE_NO < pipe)
    {
        return USB_ERROR; /* Error */
    }

    usb_pstd_change_device_state(USB_DO_STALL, pipe, complete);

    return USB_OK;
}
/******************************************************************************
End of function usb_pstd_set_stall_clr_feature
******************************************************************************/

/******************************************************************************
 Function Name   : usb_peri_registration
 Description     : Registration of peripheral Devices Class Driver
 Arguments       : usb_utr_t *ptr : Pointer to usb_utr_t structure.
 Return value    : none
 ******************************************************************************/
void usb_peri_registration(usb_ctrl_t *ctrl, usb_cfg_t *cfg)
{
    usb_pcdreg_t pdriver;

    /* pdriver registration */
    pdriver.p_devicetbl   = cfg->p_usb_reg->p_device;           /* Device descriptor Table address */
    pdriver.p_qualitbl    = cfg->p_usb_reg->p_qualifier;        /* Qualifier descriptor Table address */
    pdriver.p_configtbl   = cfg->p_usb_reg->p_config_f;         /* Configuration descriptor Table address */
    pdriver.p_othertbl    = cfg->p_usb_reg->p_config_h;         /* Other configuration descriptor Table address */
    pdriver.p_stringtbl   = cfg->p_usb_reg->p_string;           /* String descriptor Table address */
    pdriver.num_string    = cfg->p_usb_reg->num_string;         /* Num entry String descriptor */

    pdriver.devdefault  = &usb_peri_devdefault;                 /* Device default */
    pdriver.devconfig   = &usb_peri_configured;                 /* Device configuered */
    pdriver.devdetach   = &usb_peri_detach;                     /* Device detach */
    pdriver.devsuspend  = (usb_cb_t)&usb_peri_suspended;        /* Device suspend */
    pdriver.devresume   = &usb_peri_resume;                     /* Device resume */
    pdriver.interface   = &usb_peri_interface;                  /* Interface changed */
    pdriver.ctrltrans   = (usb_cb_trn_t)&usb_peri_class_request;    /* Control Transfer */

    usb_pstd_driver_registration((usb_pcdreg_t*) &pdriver);
} /* End of function usb_peri_registration() */

/******************************************************************************
 Function Name   : usb_peri_devdefault
 Description     : Descriptor change
 Arguments       : usb_utr_t *ptr       : Pointer to usb_utr_t structure.
                 : uint16_t mode        ; Speed mode
                 : uint16_t data2       ; BC Port Detect Result
 Return value    : none
 ******************************************************************************/
void usb_peri_devdefault (usb_utr_t *ptr, uint16_t mode, uint16_t data2)
{
    uint8_t *ptable;
    uint16_t len;
#if (defined(USB_CFG_PCDC_USE) | defined(USB_CFG_PHID_USE))
    usb_ctrl_t ctrl;
#endif

    usb_peri_detach(ptr, USB_NULL, USB_NULL);

    /* Connect Speed = Hi-Speed? */
    if (USB_HSCONNECT == mode)
    {
        ptable = g_usb_pstd_driver.p_othertbl;

        /* Set Descriptor type.  */
        /* Hi-Speed Mode */
        if (USB_NULL != g_usb_pstd_driver.p_configtbl)
        {
            g_usb_pstd_driver.p_configtbl[1] = USB_DT_OTHER_SPEED_CONF;
        }
        if (USB_NULL != g_usb_pstd_driver.p_othertbl)
        {
            g_usb_pstd_driver.p_othertbl[1] = USB_DT_CONFIGURATION;
        }
    }
    else
    {
        ptable = g_usb_pstd_driver.p_configtbl;

        /* Set Descriptor type. */
        /* Full-Speed Mode */
        if (USB_NULL != g_usb_pstd_driver.p_configtbl)
        {
            g_usb_pstd_driver.p_configtbl[1] = USB_DT_CONFIGURATION;
        }
        if (USB_NULL != g_usb_pstd_driver.p_othertbl)
        {
            g_usb_pstd_driver.p_othertbl[1] = USB_DT_OTHER_SPEED_CONF;
        }
    }

    if (USB_NULL == ptable)
    {
        while (1); /* Error */
    }

    len = (uint16_t) (*(uint8_t*) ((uint32_t) ptable + (uint32_t) 3));
    len = (uint16_t) (len << 8);
    len += (uint16_t) (*(uint8_t*) ((uint32_t) ptable + (uint32_t) 2));

    usb_peri_pipe_info(ptable, mode, len);

#if (defined(USB_CFG_PCDC_USE) | defined(USB_CFG_PHID_USE))
    ctrl.module = USB_CFG_USE_USBIP;
    usb_set_event(USB_STS_DEFAULT, &ctrl);
#endif

} /* End of function usb_peri_devdefault() */

/******************************************************************************
 Function Name   : usb_peri_pipe_info
 Description     : Pipe Information check and EP Table Set
 Arguments       : uint8_t *table   : Check Start Descriptor address
                 : uint16_t speed   : Device connected speed
                 : uint16_t length  : Configuration Descriptor Length
 Return value    : uint16_t : USB_E_OK / USB_E_ERROR
 ******************************************************************************/
uint16_t usb_peri_pipe_info (uint8_t *table, uint16_t speed, uint16_t length)
{
    uint16_t ofdsc;
    uint16_t retval = USB_ERROR;
    uint8_t         test_pipe_no;

    /* Check Endpoint Descriptor */
    ofdsc = table[0];

    while (ofdsc < length)
    {
        /* Endpoint Descriptor */
        if ( USB_DT_ENDPOINT == table[ofdsc + USB_EP_B_DESCRIPTORTYPE])
        {
            /* EP Table pipe Information set */
            test_pipe_no = usb_pstd_set_pipe_table (&table[ofdsc]);
            if (USB_NULL != test_pipe_no)
            {
                retval = USB_OK;
            }
        }
        ofdsc += table[ofdsc];
    }
    return retval;
} /* End of function usb_peri_pipe_info() */

/******************************************************************************
 Function Name   : usb_peri_configured
 Description     : Peripheral Devices Class open function
 Arguments       : usb_utr_t    *ptr        : Not used
                 : uint16_t     data1       : Not used
                 : uint16_t     data2       : Not used
 Return value    : none
 ******************************************************************************/
void usb_peri_configured (usb_utr_t *ptr, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    g_usb_peri_connected = USB_TRUE;
    
    ctrl.module = USB_CFG_USE_USBIP;
    usb_set_event(USB_STS_CONFIGURED, &ctrl);

#if defined(USB_CFG_PMSC_USE)
    usb_pmsc_receive_cbw();
#endif
} /* End of function usb_configured() */

/******************************************************************************
 Function Name   : usb_peri_detach
 Description     : Peripheral Devices Class close function
 Arguments       : usb_utr_t    *ptr        : Not used
                 : uint16_t     data1       : Not used
                 : uint16_t     data2       : Not used
 Return value    : none
 ******************************************************************************/
void usb_peri_detach (usb_utr_t *ptr, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    if(g_usb_peri_connected == USB_TRUE)
    {
        g_usb_peri_connected = USB_FALSE;

        ctrl.module = USB_CFG_USE_USBIP;
        usb_set_event(USB_STS_DETACH, &ctrl);
    }
} /* End of function usb_peri_detach() */

/******************************************************************************
 Function Name   : usb_peri_suspended
 Description     : Peripheral Devices Class suspended function
 Arguments       : usb_utr_t    *ptr        : Not used
                 : uint16_t     data1       : Not used
                 : uint16_t     data2       : Not used
 Return value    : none
 ******************************************************************************/
void usb_peri_suspended(usb_utr_t *ptr, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    ctrl.module = USB_CFG_USE_USBIP;
    usb_set_event(USB_STS_SUSPEND, &ctrl);
} /* End of function usb_suspended() */

/******************************************************************************
 Function Name   : usb_peri_resume
 Description     : Peripheral Devices Class resume function
 Arguments       : usb_utr_t    *ptr        : Not used
                 : uint16_t     data1       : Not used
                 : uint16_t     data2       : Not used
 Return value    : none
 ******************************************************************************/
void usb_peri_resume(usb_utr_t *ptr, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    ctrl.module = USB_CFG_USE_USBIP;
    usb_set_event(USB_STS_RESUME, &ctrl);
} /* End of function usb_peri_resume() */

/******************************************************************************
 Function Name   : usb_peri_interface
 Description     : Peripheral Devices Class set interface function
 Arguments       : usb_utr_t    *ptr        : Not used
                 : uint16_t     data1       : Not used
                 : uint16_t     data2       : Not used
 Return value    : none
 ******************************************************************************/
void usb_peri_interface(usb_utr_t *ptr, uint16_t data1, uint16_t data2)
{
#if defined(USB_CFG_PMSC_USE)
    usb_pmsc_receive_cbw();
#else   /* defined(USB_CFG_PMSC_USE) */
    /* Non processing */
#endif  /* defined(USB_CFG_PMSC_USE) */
} /* End of function usb_peri_interface() */

#if defined(USB_CFG_PVND_USE)
/******************************************************************************
 Function Name   : usb_pvnd_read_complete
 Description     : CallBack Function
 Argument        : usb_utr_t *mess           : Transfer result message
 Return          : none
 ******************************************************************************/
void usb_pvnd_read_complete (usb_utr_t *mess, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    /* Set Receive data length */
    ctrl.size = g_usb_read_request_size[USB_CFG_USE_USBIP][mess->keyword] - mess->tranlen;
    ctrl.pipe = mess->keyword; /* Pipe number setting */
    ctrl.type = USB_PVND; /* Device class setting  */
    switch (mess->status)
    {
        case USB_DATA_OK :
            ctrl.status = USB_SUCCESS;
        break;
        case USB_DATA_SHT :
            ctrl.status = USB_ERR_SHORT;
        break;
        case USB_DATA_OVR :
            ctrl.status = USB_ERR_OVER;
        break;
        case USB_DATA_ERR :
        default :
            ctrl.status = USB_ERR_NG;
        break;
    }
    ctrl.module = USB_CFG_USE_USBIP;
    usb_set_event(USB_STS_READ_COMPLETE, &ctrl);
} /* End of function usb_pvnd_read_complete() */

/******************************************************************************
 Function Name   : usb_pvnd_write_complete
 Description     : CallBack Function
 Argument        : usb_utr_t *mess           : Transfer result message
 Return          : none
 ******************************************************************************/
void usb_pvnd_write_complete (usb_utr_t *mess, uint16_t data1, uint16_t data2)
{
    usb_ctrl_t ctrl;

    ctrl.pipe = mess->keyword; /* Pipe number setting */
    ctrl.type = USB_PVND; /* CDC Control class  */
    if (USB_DATA_NONE == mess->status)
    {
        ctrl.status = USB_SUCCESS;
    }
    else
    {
        ctrl.status = USB_ERR_NG;
    }
    ctrl.module = USB_CFG_USE_USBIP;
    usb_set_event(USB_STS_WRITE_COMPLETE, &ctrl);
} /* End of function usb_pvnd_write_complete() */
#endif /* defined(USB_CFG_PVND_USE) */

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_REPI */

/******************************************************************************
 End  Of File
 ******************************************************************************/
