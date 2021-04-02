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
 * File Name    : r_usb_creg_abs.c
 * Description  : Call USB register access function
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 26.01.2017 1.22 usb_cstd_chg_curpipe is fixed.(Add process for USB_D0USE/USB_D1USE.)
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

/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
uint16_t g_usb_hstd_use_pipe[USB_NUM_USBIP];

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 Function Name   : usb_cstd_get_buf_size
 Description     : Return buffer size, or max packet size, of specified pipe.
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t pipe     : Pipe number.
 Return value    : uint16_t          : FIFO buffer size or max packet size.
 ******************************************************************************/
uint16_t usb_cstd_get_buf_size (usb_utr_t *ptr, uint16_t pipe)
{
    uint16_t size;
    uint16_t buffer;

    if (USB_PIPE0 == pipe)
    {
        buffer = hw_usb_read_dcpcfg(ptr);
        if ((buffer & USB_CNTMDFIELD) == USB_CFG_CNTMDON)
        {
            /* Continuation transmit */
            /* Buffer Size */
            size = USB_PIPE0BUF;
        }
        else
        {
            /* Not continuation transmit */
            buffer = hw_usb_read_dcpmaxp(ptr);

            /* Max Packet Size */
            size = (uint16_t) (buffer & USB_MAXP);
        }
    }
    else
    {
        /* Pipe select */
        hw_usb_write_pipesel(ptr, pipe);

#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
        /* Read CNTMD */
        buffer = hw_usb_read_pipecfg(ptr);
        if ((buffer & USB_CNTMDFIELD) == USB_CFG_CNTMDON)
        {
            buffer = hw_usb_read_pipebuf(ptr);

            /* Buffer Size */
            size = (uint16_t)((uint16_t)((buffer >> USB_BUFSIZE_BIT) + 1) * USB_PIPEXBUF);
        }
        else
        {
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
        buffer = hw_usb_read_pipemaxp(ptr);

        /* Max Packet Size */
        size = (uint16_t) (buffer & USB_MXPS);
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    }
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
    }
    return size;
}
/******************************************************************************
 End of function usb_cstd_get_buf_size
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_pipe_init
 Description     : Initialization of registers associated with specified pipe.
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t pipe     : Pipe Number
 Return value    : none
 ******************************************************************************/
void usb_cstd_pipe_init (usb_utr_t *ptr, uint16_t pipe)
{
    uint16_t    useport = USB_CUSE;
    uint16_t    ip_no;

    if (USB_NULL == ptr)
    {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        g_p_usb_pstd_pipe[pipe] = (usb_utr_t *)USB_NULL;
        useport = usb_pstd_pipe2fport(pipe);
        ip_no = USB_CFG_USE_USBIP;
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }
    else
    {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
        g_p_usb_hstd_pipe[ptr->ip][pipe] = (usb_utr_t*) USB_NULL;
        useport = usb_hstd_pipe2fport(ptr, pipe);
        ip_no = ptr->ip;
#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    /* Interrupt Disable */
    /* Ready         Int Disable */
    hw_usb_clear_brdyenb(ptr, pipe);

    /* NotReady      Int Disable */
    hw_usb_clear_nrdyenb(ptr, pipe);

    /* Empty/SizeErr Int Disable */
    hw_usb_clear_bempenb(ptr, pipe);

    /* PID=NAK & clear STALL */
    usb_cstd_clr_stall(ptr, pipe);

    /* PIPE Configuration */
    hw_usb_write_pipesel(ptr, pipe);

#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
    /* Update use pipe no info */
    if (USB_NULL != g_usb_pipe_table[ip_no][pipe].pipe_cfg)
    {
        g_usb_hstd_use_pipe[ptr->ip] |= ((uint16_t) 1 << pipe);
    }
    else
    {
        g_usb_hstd_use_pipe[ptr->ip] &= (~((uint16_t) 1 << pipe));
    }

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

    if ((USB_D0DMA == useport) || (USB_D1DMA == useport))
    {
        g_usb_pipe_table[ip_no][pipe].pipe_cfg |= USB_BFREON;
    }

    hw_usb_write_pipecfg(ptr, g_usb_pipe_table[ip_no][pipe].pipe_cfg);

#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    if (USB_IP1 == ip_no)
    {
        hw_usb_write_pipebuf(ptr, g_usb_pipe_table[ip_no][pipe].pipe_buf);
    }
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
    hw_usb_write_pipemaxp(ptr, g_usb_pipe_table[ip_no][pipe].pipe_maxp);
    hw_usb_write_pipeperi(ptr, g_usb_pipe_table[ip_no][pipe].pipe_peri);

    /* FIFO buffer DATA-PID initialized */
    hw_usb_write_pipesel(ptr, USB_PIPE0);

    /* SQCLR */
    hw_usb_set_sqclr(ptr, pipe);

    /* ACLRM */
    usb_cstd_do_aclrm(ptr, pipe);

    /* CSSTS */
    hw_usb_set_csclr(ptr, pipe);

    /* Interrupt status clear */
    /* Ready         Int Clear */
    hw_usb_clear_sts_brdy(ptr, pipe);

    /* NotReady      Int Clear */
    hw_usb_clear_status_nrdy(ptr, pipe);

    /* Empty/SizeErr Int Clear */
    hw_usb_clear_status_bemp(ptr, pipe);
}
/******************************************************************************
 End of function usb_cstd_pipe_init
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_clr_pipe_cnfg
 Description     : Clear specified pipe configuration register.
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t pipe_no  : pipe number
 Return value    : none
 ******************************************************************************/
void usb_cstd_clr_pipe_cnfg (usb_utr_t *ptr, uint16_t pipe_no)
{
    if (USB_NULL == ptr)
    {
#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )
        g_p_usb_pstd_pipe[pipe_no] = (usb_utr_t *)USB_NULL;

#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */
    }
    else
    {
#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )
        g_p_usb_hstd_pipe[ptr->ip][pipe_no] = (usb_utr_t*) USB_NULL;

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */
    }

    /* PID=NAK & clear STALL */
    usb_cstd_clr_stall(ptr, pipe_no);

    /* Interrupt disable */
    /* Ready         Int Disable */
    hw_usb_clear_brdyenb(ptr, pipe_no);

    /* NotReady      Int Disable */
    hw_usb_clear_nrdyenb(ptr, pipe_no);

    /* Empty/SizeErr Int Disable */
    hw_usb_clear_bempenb(ptr, pipe_no);

    /* PIPE Configuration */
    usb_cstd_chg_curpipe(ptr, (uint16_t) USB_PIPE0, (uint16_t) USB_CUSE, USB_FALSE);
    hw_usb_write_pipesel(ptr, pipe_no);
    hw_usb_write_pipecfg(ptr, 0);

#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    hw_usb_write_pipebuf(ptr, 0);

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
    hw_usb_write_pipemaxp(ptr, 0);
    hw_usb_write_pipeperi(ptr, 0);
    hw_usb_write_pipesel(ptr, 0);

    /* FIFO buffer DATA-PID initialized */
    /* SQCLR */
    hw_usb_set_sqclr(ptr, pipe_no);

    /* ACLRM */
    usb_cstd_do_aclrm(ptr, pipe_no);

    /* CSSTS */
    hw_usb_set_csclr(ptr, pipe_no);
    usb_cstd_clr_transaction_counter(ptr, pipe_no);

    /* Interrupt status clear */
    /* Ready         Int Clear */
    hw_usb_clear_sts_brdy(ptr, pipe_no);

    /* NotReady      Int Clear */
    hw_usb_clear_status_nrdy(ptr, pipe_no);

    /* Empty/SizeErr Int Clear */
    hw_usb_clear_status_bemp(ptr, pipe_no);
}
/******************************************************************************
 End of function usb_cstd_clr_pipe_cnfg
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_set_nak
 Description     : Set up to NAK the specified pipe.
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t pipe     : Pipe Number
 Return value    : none
 ******************************************************************************/
void usb_cstd_set_nak (usb_utr_t *ptr, uint16_t pipe)
{
    uint16_t buf;
    uint16_t n;

    /* Set NAK */
    hw_usb_clear_pid(ptr, pipe, (uint16_t) USB_PID_BUF);

    /* The state of PBUSY continues while transmitting the packet when it is a detach. */
    /* 1ms comes off when leaving because the packet duration might not exceed 1ms.  */
    /* Whether it is PBUSY release or 1ms passage can be judged. */
    for (n = 0; n < 0xFFFFu; ++n)
    {
        /* PIPE control reg read */
        buf = hw_usb_read_pipectr(ptr, pipe);
        if ((uint16_t) (buf & USB_PBUSY) == 0)
        {
            n = 0xFFFEu;
        }
    }
}
/******************************************************************************
 End of function usb_cstd_set_nak
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_is_set_frdy
 Description     : Changes the specified FIFO port by the specified pipe.
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t pipe     : Pipe Number
                 : uint16_t fifosel  : FIFO select
                 : uint16_t isel     : ISEL bit status
 Return value    : FRDY status
 ******************************************************************************/
uint16_t usb_cstd_is_set_frdy (usb_utr_t *ptr, uint16_t pipe, uint16_t fifosel, uint16_t isel)
{
    uint16_t buffer;
    uint16_t i;

    /* Changes the FIFO port by the pipe. */
    usb_cstd_chg_curpipe(ptr, pipe, fifosel, isel);

    for (i = 0; i < 4; i++)
    {
        buffer = hw_usb_read_fifoctr(ptr, fifosel);

        if ((uint16_t) (buffer & USB_FRDY) == USB_FRDY)
        {
            return (buffer);
        } USB_PRINTF1("*** FRDY wait pipe = %d\n", pipe);

        /* Caution!!!
         * Depending on the external bus speed of CPU, you may need to wait
         * for 100ns here.
         * For details, please look at the data sheet.   */
        /***** The example of reference. *****/
        buffer = hw_usb_read_syscfg(ptr);
        buffer = hw_usb_read_syssts(ptr);

        /*************************************/
    }
    return (USB_FIFOERROR);
}
/******************************************************************************
 End of function usb_cstd_is_set_frdy
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_chg_curpipe
 Description     : Switch FIFO and pipe number.
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t pipe     : Pipe number.
                 : uint16_t fifosel  : FIFO selected (CPU, D0, D1..)
                 : uint16_t isel     : CFIFO Port Access Direction.(Pipe1 to 9:Set to 0)
 Return value    : none
 ******************************************************************************/
void usb_cstd_chg_curpipe (usb_utr_t *ptr, uint16_t pipe, uint16_t fifosel, uint16_t isel)
{
    uint16_t buffer;

    /* Select FIFO */
    switch (fifosel)
    {
        /* CFIFO use */
        case USB_CUSE :

            /* ISEL=1, CURPIPE=0 */
            hw_usb_rmw_fifosel(ptr, USB_CUSE, ((USB_RCNT | isel) | pipe), ((USB_RCNT | USB_ISEL) | USB_CURPIPE));
            do
            {
                buffer = hw_usb_read_fifosel(ptr, USB_CUSE);
            } while ((buffer & (uint16_t) (USB_ISEL | USB_CURPIPE)) != (uint16_t) (isel | pipe));
        break;

#if ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE))
        /* D0FIFO use */
        case USB_D0USE :
        /* D0FIFO DMA */
        case USB_D0DMA:
            /* D0FIFO pipe select */
            hw_usb_set_curpipe( ptr, USB_D0DMA, pipe );
            do
            {
                buffer = hw_usb_read_fifosel( ptr, USB_D0DMA );
            }
            while( (uint16_t)(buffer & USB_CURPIPE) != pipe );
        break;

        /* D1FIFO use */
        case USB_D1USE :
        /* D1FIFO DMA */
        case USB_D1DMA:
            /* D1FIFO pipe select */
            hw_usb_set_curpipe( ptr, USB_D1DMA, pipe );

            do
            {
                buffer = hw_usb_read_fifosel( ptr, USB_D1DMA );
            }
            while( (uint16_t)(buffer & USB_CURPIPE) != pipe );
        break;
#endif    /* ((USB_CFG_DTC == USB_CFG_ENABLE) || (USB_CFG_DMA == USB_CFG_ENABLE)) */

        default :
        break;
    }
}
/******************************************************************************
 End of function usb_cstd_chg_curpipe
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_set_transaction_counter
 Description     : Set specified Pipe Transaction Counter Register.
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t trnreg   : Pipe number
                 : uint16_t trncnt   : Transaction counter
 Return value    : none
 ******************************************************************************/
void usb_cstd_set_transaction_counter (usb_utr_t *ptr, uint16_t trnreg, uint16_t trncnt)
{
    hw_usb_set_trclr(ptr, trnreg);
    hw_usb_write_pipetrn(ptr, trnreg, trncnt);
    hw_usb_set_trenb(ptr, trnreg);
}
/******************************************************************************
 End of function usb_cstd_set_transaction_counter
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_cstd_clr_transaction_counter
 Description     : Clear specified Pipe Transaction Counter Register.
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
                 : uint16_t trnreg   : Pipe Number
 Return value    : none
 ******************************************************************************/
void usb_cstd_clr_transaction_counter (usb_utr_t *ptr, uint16_t trnreg)
{
    hw_usb_clear_trenb(ptr, trnreg);
    hw_usb_set_trclr(ptr, trnreg);
}
/******************************************************************************
 End of function usb_cstd_clr_transaction_counter
 ******************************************************************************/

/******************************************************************************
 End of file
 ******************************************************************************/

