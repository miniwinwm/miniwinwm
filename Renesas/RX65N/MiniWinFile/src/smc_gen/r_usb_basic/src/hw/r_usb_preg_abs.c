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
 * Copyright (C) 2015(2017) Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_usb_preg_abs.c
 * Description  : Call USB Peripheral register access function
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 RX62N/RX630/RX63T-H is added.
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_extern.h"
#include "r_usb_reg_access.h"
#include "r_usb_bitdefine.h"

#if ( (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI )

/******************************************************************************
 Exported global variables (to be accessed by other files)
 ******************************************************************************/
uint16_t g_usb_cstd_suspend_mode = USB_NORMAL_MODE;


/******************************************************************************
 Function Name   : usb_pstd_interrupt_handler
 Description     : Determine which USB interrupt occurred and report results to
                 : the usb_utr_t argument's ipp, type, and status members.
 Arguments       : usb_utr_t *ptr    : Pointer to usb_utr_t structure.
 Return value    : none
 ******************************************************************************/
void usb_pstd_interrupt_handler(uint16_t * type, uint16_t * status)
{
    uint16_t intsts0;
    uint16_t intenb0;
    uint16_t ists0;
    uint16_t brdysts;
    uint16_t brdyenb;
    uint16_t bsts;
    uint16_t nrdysts;
    uint16_t nrdyenb;
    uint16_t nsts;
    uint16_t bempsts;
    uint16_t bempenb;
    uint16_t ests;

    /* Register Save */
#if USB_CFG_USE_USBIP == USB_CFG_IP1
    intsts0 = USB_M1.INTSTS0.WORD;
    brdysts = USB_M1.BRDYSTS.WORD;
    nrdysts = USB_M1.NRDYSTS.WORD;
    bempsts = USB_M1.BEMPSTS.WORD;
    intenb0 = USB_M1.INTENB0.WORD;
    brdyenb = USB_M1.BRDYENB.WORD;
    nrdyenb = USB_M1.NRDYENB.WORD;
    bempenb = USB_M1.BEMPENB.WORD;

#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP1 */

#if USB_CFG_USE_USBIP == USB_CFG_IP0
    intsts0 = USB_M0.INTSTS0.WORD;
    brdysts = USB_M0.BRDYSTS.WORD;
    nrdysts = USB_M0.NRDYSTS.WORD;
    bempsts = USB_M0.BEMPSTS.WORD;
    intenb0 = USB_M0.INTENB0.WORD;
    brdyenb = USB_M0.BRDYENB.WORD;
    nrdyenb = USB_M0.NRDYENB.WORD;
    bempenb = USB_M0.BEMPENB.WORD;

#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP0 */

    *type = USB_INT_UNKNOWN;
    *status = 0;

    /* Interrupt status get */
    ists0 = (uint16_t)(intsts0 & intenb0);
    bsts = (uint16_t)(brdysts & brdyenb);
    nsts = (uint16_t)(nrdysts & nrdyenb);
    ests = (uint16_t)(bempsts & bempenb);

    if ((intsts0 & (USB_VBINT | USB_RESM | USB_SOFR | USB_DVST |
                            USB_CTRT | USB_BEMP | USB_NRDY | USB_BRDY)) == 0u)
    {
        return;
    }

    /***** Processing USB bus signal *****/
    /***** Resume signal *****/
    if ((ists0 & USB_RESM) == USB_RESM)
    {
#if USB_CFG_USE_USBIP == USB_CFG_IP1
        USB_M1.INTSTS0.WORD = (uint16_t)~USB_RESM;

#else   /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        USB_M0.INTSTS0.WORD = (uint16_t)~USB_RESM;

#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        *type = USB_INT_RESM;
    }

    /***** Vbus change *****/
    else if ((ists0 & USB_VBINT) == USB_VBINT)
    {
        /* Status clear */
#if USB_CFG_USE_USBIP == USB_CFG_IP1
        USB_M1.INTSTS0.WORD = (uint16_t)~USB_VBINT;

#else   /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        USB_M0.INTSTS0.WORD = (uint16_t)~USB_VBINT;

#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        *type = USB_INT_VBINT;
    }

    /***** SOFR change *****/
    else if ((ists0 & USB_SOFR) == USB_SOFR)
    {
        /* SOFR Clear */
#if USB_CFG_USE_USBIP == USB_CFG_IP1
        USB_M1.INTSTS0.WORD = (uint16_t)~USB_SOFR;

#else   /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        USB_M0.INTSTS0.WORD = (uint16_t)~USB_SOFR;

#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        *type = USB_INT_SOFR;
    }

    /***** Processing device state *****/
    /***** DVST change *****/
    else if ((ists0 & USB_DVST) == USB_DVST)
    {
        /* DVST clear */
#if USB_CFG_USE_USBIP == USB_CFG_IP1
        USB_M1.INTSTS0.WORD = (uint16_t)~USB_DVST;

#else   /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        USB_M0.INTSTS0.WORD = (uint16_t)~USB_DVST;

#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        *type = USB_INT_DVST;
        *status = intsts0;
    }

    /***** Processing PIPE0 data *****/
    else if ((USB_BRDY == (ists0 & USB_BRDY)) && ((USB_BRDY0) == (bsts & USB_BRDY0)))
    {
#if USB_CFG_USE_USBIP == USB_CFG_IP1
        USB_M1.BRDYSTS.WORD = (uint16_t) ((~USB_BRDY0) & BRDYSTS_MASK);

#else   /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        USB_M0.BRDYSTS.WORD = (uint16_t) ((~USB_BRDY0) & BRDYSTS_MASK);

#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        *type = USB_INT_BRDY;
        *status = USB_BRDY0;
    }
    else if ((USB_BEMP == (ists0 & USB_BEMP)) && (USB_BEMP0 == (ests & USB_BEMP0)))
    {
#if USB_CFG_USE_USBIP == USB_CFG_IP1
        USB_M1.BEMPSTS.WORD = (uint16_t) ((~USB_BEMP0) & BEMPSTS_MASK);

#else   /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        USB_M0.BEMPSTS.WORD = (uint16_t) ((~USB_BEMP0) & BEMPSTS_MASK);

#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        *type = USB_INT_BEMP;
        *status = USB_BEMP0;
    }
    else if ((USB_NRDY == (ists0 & USB_NRDY)) && (USB_NRDY0 == (nsts & USB_NRDY0)))
    {
#if USB_CFG_USE_USBIP == USB_CFG_IP1
        USB_M1.NRDYSTS.WORD = (uint16_t) ((~USB_NRDY0) & NRDYSTS_MASK);

#else   /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        USB_M0.NRDYSTS.WORD = (uint16_t) ((~USB_NRDY0) & NRDYSTS_MASK);

#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        *type = USB_INT_NRDY;
        *status = USB_NRDY0;
    }

    /***** Processing setup transaction *****/
    else if (USB_CTRT == (ists0 & USB_CTRT))
    {
        /* CTSQ bit changes later than CTRT bit for ASSP. */
        /* CTSQ reloading */
        *status = hw_usb_read_intsts();

        /* USB_CTRT clear */
#if USB_CFG_USE_USBIP == USB_CFG_IP1
        USB_M1.INTSTS0.WORD = (uint16_t)~USB_CTRT;

#else   /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        USB_M0.INTSTS0.WORD = (uint16_t)~USB_CTRT;

#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        *type = USB_INT_CTRT;

        if (USB_CS_SQER == (uint8_t)((*status) & USB_CTSQ))
        {
            hw_usb_pclear_sts_valid();
            *type = USB_INT_UNKNOWN;
            *status = 0;
            return;
        }
    }

    /***** Processing PIPE1-MAX_PIPE_NO data *****/
    else if (USB_BRDY == (ists0 & USB_BRDY))
    {
#if USB_CFG_USE_USBIP == USB_CFG_IP1
        USB_M1.BRDYSTS.WORD = (uint16_t) ((~bsts) & BRDYSTS_MASK);

#else   /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        USB_M0.BRDYSTS.WORD = (uint16_t) ((~bsts) & BRDYSTS_MASK);

#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        *type = USB_INT_BRDY;
        *status = bsts;
    }
    else if (USB_BEMP == (ists0 & USB_BEMP))
    {
#if USB_CFG_USE_USBIP == USB_CFG_IP1
        USB_M1.BEMPSTS.WORD = (uint16_t) ((~ests) & BEMPSTS_MASK);

#else   /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        USB_M0.BEMPSTS.WORD = (uint16_t) ((~ests) & BEMPSTS_MASK);

#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        *type = USB_INT_BEMP;
        *status = ests;
    }
    else if (USB_NRDY == (ists0 & USB_NRDY))
    {
#if USB_CFG_USE_USBIP == USB_CFG_IP1
        USB_M1.NRDYSTS.WORD = (uint16_t) ((~nsts) & NRDYSTS_MASK);

#else   /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        USB_M0.NRDYSTS.WORD = (uint16_t) ((~nsts) & NRDYSTS_MASK);

#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP1 */
        *type = USB_INT_NRDY;
        *status = nsts;
    }
    else
    {
        /* Non processing. */
    }
}
/******************************************************************************
 End of function usb_pstd_interrupt_handler
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_save_request
 Description     : Save received USB command.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_save_request(void)
{
    /* Valid clear */
    hw_usb_pclear_sts_valid();

    g_usb_pstd_req_type = hw_usb_read_usbreq();
    g_usb_pstd_req_value = hw_usb_read_usbval();
    g_usb_pstd_req_index = hw_usb_read_usbindx();
    g_usb_pstd_req_length = hw_usb_read_usbleng();
}
/******************************************************************************
 End of function usb_pstd_save_request
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_chk_configured
 Description     : Check if USB Device is in a CONFIGURED state.
 Arguments       : none
 Return value    : Configuration state (YES/NO)
 ******************************************************************************/
uint16_t usb_pstd_chk_configured(void)
{
    uint16_t buf;

    buf = hw_usb_read_intsts();

    /* Device Status - Configured check */
    if ((buf & USB_DVSQ) == USB_DS_CNFG)
    {
        /* Configured */
        return USB_TRUE;
    }
    else
    {
        /* not Configured */
        return USB_FALSE;
    }
}
/******************************************************************************
 End of function usb_pstd_chk_configured
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_remote_wakeup
 Description     : Set the USB peripheral to implement remote wake up.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_remote_wakeup(void)
{
    uint16_t buf;

    g_usb_pstd_remote_wakeup_state = USB_ERROR;

    /* Support remote wakeup ? */
    if (USB_TRUE == g_usb_pstd_remote_wakeup)
    {
        /* RESM interrupt disable */
        hw_usb_pclear_enb_rsme();

        /* RESM status read */
        buf = hw_usb_read_intsts();
        if ((buf & USB_RESM) != (uint16_t)0)
        {
            g_usb_pstd_remote_wakeup_state = USB_QOVR;
            /* RESM status clear */
            hw_usb_pclear_sts_resm();
        }
        else
        {
            if ((buf & USB_DS_SUSP) != (uint16_t)0)
            {
                /* Remote wakeup set */
                hw_usb_pset_wkup();
                g_usb_pstd_remote_wakeup_state = USB_OK;
            }
        }
    }
}
/******************************************************************************
 End of function usb_pstd_remote_wakeup
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_test_mode
 Description     : USB Peripheral test mode function.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_test_mode(void)
{
    switch ((uint16_t)(g_usb_pstd_test_mode_select & USB_TEST_SELECT))
    {
        case USB_TEST_J:

        /* Continue */
        case USB_TEST_K:

        /* Continue */
        case USB_TEST_SE0_NAK:

        /* Continue */
        case USB_TEST_PACKET:
#if defined(BSP_MCU_RX71M)
        hw_usb_set_utst(USB_NULL,0);
        hw_usb_set_utst(USB_NULL,(uint16_t)(g_usb_pstd_test_mode_select >> 8));
#endif  /* defined(BSP_MCU_RX71M) */
        break;
        case USB_TEST_FORCE_ENABLE:

        /* Continue */
        default:
        break;
    }
}
/******************************************************************************
 End of function usb_pstd_test_mode
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_resume_process
 Description     : Set USB registers to implement resume processing.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_resume_process(void)
{
    /* RESM status clear */
    hw_usb_pclear_sts_resm();

    /* RESM interrupt disable */
    hw_usb_pclear_enb_rsme();

}
/******************************************************************************
 End of function usb_pstd_resume_process
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_set_stall
 Description     : Set the specified pipe's PID to STALL.
 Arguments       : uint16_t pipe   : Pipe Number
 Return value    : none
 ******************************************************************************/
void usb_pstd_set_stall(uint16_t pipe)
{
    /* PIPE control reg set */
    hw_usb_set_pid(USB_NULL,pipe, USB_PID_STALL);
}
/******************************************************************************
 End of function usb_pstd_set_stall
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_set_stall_pipe0
 Description     : Set pipe "0" PID to STALL.
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_set_stall_pipe0(void)
{
    /* PIPE control reg set */
    hw_usb_set_pid(USB_NULL,USB_PIPE0, USB_PID_STALL);
}
/******************************************************************************
 End of function usb_pstd_set_stall_pipe0
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_write_fifo
 Description     : Write specified amount of data to specified USB FIFO.
 Arguments       : uint16_t  count       : Write size.
                 : uint16_t  pipemode    : The mode of CPU/DMA(D0)/DMA(D1).
                 : uint16_t  *write_p    : Address of buffer of data to write.
 Return value    : The incremented address of last argument (write_p).
 ******************************************************************************/
uint8_t *usb_pstd_write_fifo(uint16_t count, uint16_t pipemode, uint8_t *write_p)
{
    uint16_t even;
#if ((USB_CFG_USE_USBIP == USB_CFG_IP1) && (!defined(BSP_MCU_RX63N)))
    uint16_t odd;
#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP1 */

#if (USB_CFG_USE_USBIP == USB_CFG_IP0) || defined(BSP_MCU_RX63N) || defined(BSP_MCU_RX62N)
    for (even = (uint16_t)(count >> 1); (0 != even); --even)
    {
        /* 16bit access */
        hw_usb_write_fifo16(USB_NULL,pipemode, *((uint16_t *)write_p));

        /* Renewal write pointer */
        write_p += sizeof(uint16_t);
    }

    if ((count & (uint16_t)0x0001u) != 0u)
    {
        /* 8bit access */
        /* count == odd */
        /* Change FIFO access width */
        hw_usb_set_mbw(USB_NULL,pipemode, USB_MBW_8);

        /* FIFO write */
        hw_usb_write_fifo8(USB_NULL,pipemode, *write_p);

        /* Return FIFO access width */
        hw_usb_set_mbw(USB_NULL,pipemode, USB_MBW_16);

        /* Renewal write pointer */
        write_p++;
    }
#else
    for (even = (uint16_t)(count >> 2); (even != 0); --even)
    {
        /* 32bit access */
        hw_usb_write_fifo32(USB_NULL, pipemode, *((uint32_t *)write_p));

        /* Renewal write pointer */
        write_p += sizeof(uint32_t);
    }
    odd = count % 4;
    if ((odd & (uint16_t)0x0002u) != 0u)
    {
        /* 16bit access */
        /* Change FIFO access width */
        hw_usb_set_mbw(USB_NULL, pipemode, USB_MBW_16);
        /* FIFO write */
        hw_usb_write_fifo16(USB_NULL, pipemode, *((uint16_t *)write_p));

        /* Renewal write pointer */
        write_p += sizeof(uint16_t);
    }
    if ((odd & (uint16_t)0x0001u) != 0u)
    {
        /* 8bit access */
        /* count == odd */
        /* Change FIFO access width */
        hw_usb_set_mbw(USB_NULL, pipemode, USB_MBW_8);

        /* FIFO write */
        hw_usb_write_fifo8(USB_NULL, pipemode, *write_p);

        /* Renewal write pointer */
        write_p++;
    }
    /* Return FIFO access width */
    hw_usb_set_mbw(USB_NULL, pipemode, USB_MBW_32);
#endif
    return write_p;

}
/******************************************************************************
 End of function usb_pstd_write_fifo
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_read_fifo
 Description     : Read specified buffer size from the USB FIFO.
 Arguments       : uint16_t  count       : Read size.
                 : uint16_t  pipemode    : The mode of CPU/DMA(D0)/DMA(D1).
                 : uint16_t  *write_p    : Address of buffer to store the read data.
 Return value    : Pointer to a buffer that contains the data to be read next.
 ******************************************************************************/
uint8_t *usb_pstd_read_fifo(uint16_t count, uint16_t pipemode, uint8_t *read_p)
{
    uint16_t even;
#if ((USB_CFG_USE_USBIP == USB_CFG_IP1) && (!defined(BSP_MCU_RX63N)))
    uint16_t odd;
#endif  /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
    uint32_t odd_byte_data_temp;

#if !((USB_CFG_USE_USBIP == USB_CFG_IP0) || defined(BSP_MCU_RX63N)) || defined(BSP_MCU_RX62N)
#if USB_CFG_ENDIAN != USB_CFG_LITTLE
    uint16_t    i;
#endif  /* USB_CFG_ENDIAN != USB_CFG_LITTLE */
#endif /* !((USB_CFG_USE_USBIP == USB_CFG_IP0) || defined(BSP_MCU_RX63N)) */

#if (USB_CFG_USE_USBIP == USB_CFG_IP0) || defined(BSP_MCU_RX63N) || defined(BSP_MCU_RX62N)
    for (even = (uint16_t)(count >> 1); (0 != even); --even)
    {
        /* 16bit FIFO access */
        *(uint16_t *)read_p= hw_usb_read_fifo16(USB_NULL,pipemode);

        /* Renewal read pointer */
        read_p += sizeof(uint16_t);
    }
    if ((count & (uint16_t)0x0001) != 0)
    {
        /* 16bit FIFO access */
        odd_byte_data_temp = hw_usb_read_fifo16(USB_NULL,pipemode);

        /* Condition compilation by the difference of the little endian */
#if USB_CFG_ENDIAN == USB_CFG_LITTLE
        *read_p = (uint8_t)(odd_byte_data_temp & 0x00ff);
#else   /* USB_CFG_ENDIAN == USB_CFG_LITTLE */
        *read_p = (uint8_t)(odd_byte_data_temp >> 8);
#endif  /* USB_CFG_ENDIAN == USB_CFG_LITTLE */

        /* Renewal read pointer */
        read_p += sizeof(uint8_t);
    }
#else
    for (even = (uint16_t)(count >> 2); (even != 0); --even)
    {
        /* 32bit FIFO access */
        *(uint32_t *)read_p= hw_usb_read_fifo32(USB_NULL, pipemode);

        /* Renewal read pointer */
        read_p += sizeof(uint32_t);
    }
    odd = count % 4;
    if (count < 4)
    {
        odd = count;
    }
    if (odd != 0)
    {
        /* 32bit FIFO access */
        odd_byte_data_temp = hw_usb_read_fifo32(USB_NULL, pipemode);
        /* Condition compilation by the difference of the endian */
#if USB_CFG_ENDIAN == USB_CFG_LITTLE
        do
        {
            *read_p = (uint8_t)(odd_byte_data_temp & 0x000000ff);
            odd_byte_data_temp = odd_byte_data_temp >> 8;
            /* Renewal read pointer */
            read_p += sizeof(uint8_t);
            odd--;
        }while(odd != 0);
#else   /* USB_CFG_ENDIAN == USB_CFG_LITTLE */
        for (i = 0; i < odd; i++)
        {
            *read_p = (uint8_t)( ( odd_byte_data_temp >> (24 -(i*8))) & 0x000000ff );

            /* Renewal read pointer */
            read_p += sizeof(uint8_t);
        }
#endif  /* USB_CFG_ENDIAN == USB_CFG_LITTLE */
    }
#endif
    return read_p;
}
/******************************************************************************
 End of function usb_pstd_read_fifo
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_forced_termination
 Description     : Terminate data transmission and reception.
 Arguments       : uint16_t pipe     : Pipe Number
                 : uint16_t status   : Transfer status type
 Return value    : none
 Note            : In the case of timeout status, it does not call back.
 ******************************************************************************/
void usb_pstd_forced_termination(uint16_t pipe, uint16_t status)
{
    uint16_t useport;

    /* PID = NAK */
    /* Set NAK */
    usb_cstd_set_nak(USB_NULL, pipe);

    /* Disable Interrupt */
    /* Disable Ready Interrupt */
    hw_usb_clear_brdyenb(USB_NULL,pipe);

    /* Disable Not Ready Interrupt */
    hw_usb_clear_nrdyenb(USB_NULL,pipe);

    /* Disable Empty Interrupt */
    hw_usb_clear_bempenb(USB_NULL,pipe);

    usb_cstd_clr_transaction_counter(USB_NULL, pipe);

    /* Pipe number to FIFO port select */
    useport = usb_pstd_pipe2fport(pipe);

    /* Check use FIFO access */
    switch(useport)
    {
        /* CFIFO use */
        case USB_CUSE:
#if USB_CFG_USE_USBIP == USB_CFG_IP1
        hw_usb_set_mbw(USB_NULL, USB_CUSE, USB1_CFIFO_MBW);
#else  /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        hw_usb_set_mbw(USB_NULL, USB_CUSE, USB0_CFIFO_MBW);

#endif /* USB_CFG_USE_USBIP == USB_CFG_IP0 */
        /* Changes the FIFO port by the pipe. */
        usb_cstd_chg_curpipe(USB_NULL, (uint16_t)USB_PIPE0, (uint16_t)USB_CUSE, USB_FALSE);
        break;
        default:
        break;
    }

    /* Do Aclr */
    usb_cstd_do_aclrm(USB_NULL, pipe);

    /* FIFO buffer SPLIT transaction initialized */
    usb_cstd_chg_curpipe(USB_NULL, (uint16_t)USB_PIPE0, (uint16_t)USB_CUSE, USB_NOUSE);
    hw_usb_set_csclr(USB_NULL,pipe);

    /* Call Back */
    if (USB_NULL != g_p_usb_pstd_pipe[pipe])
    {
        /* Transfer information set */
        g_p_usb_pstd_pipe[pipe]->tranlen = g_usb_pstd_data_cnt[pipe];
        g_p_usb_pstd_pipe[pipe]->status = status;
        g_p_usb_pstd_pipe[pipe]->pipectr = hw_usb_read_pipectr(USB_NULL,pipe);

        if (USB_NULL != (g_p_usb_pstd_pipe[pipe]->complete))
        {
            (g_p_usb_pstd_pipe[pipe]->complete)(g_p_usb_pstd_pipe[pipe], USB_NULL, USB_NULL);
        }

        g_p_usb_pstd_pipe[pipe] = (usb_utr_t *)USB_NULL;
    }
}
/******************************************************************************
 End of function usb_pstd_forced_termination
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_interrupt_clock
 Description     : Not processed as the functionality is provided by R8A66597(ASSP).
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_interrupt_clock(void)
{
    if (g_usb_cstd_suspend_mode != USB_NORMAL_MODE)
    {
        hw_usb_set_suspendm(); /* UTMI Normal Mode (Not Suspend Mode) */
        usb_cpu_delay_1us(100);
        g_usb_cstd_suspend_mode = USB_NORMAL_MODE;
    }
}
/******************************************************************************
 End of function usb_pstd_interrupt_clock
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_self_clock
 Description     : Not processed as the functionality is provided by R8A66597(ASSP).
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_self_clock(void)
{
    if (g_usb_cstd_suspend_mode != USB_NORMAL_MODE)
    {
        hw_usb_set_suspendm(); /* UTMI Normal Mode (Not Suspend Mode) */
        usb_cpu_delay_1us(100);
        g_usb_cstd_suspend_mode = USB_NORMAL_MODE;
    }
}
/******************************************************************************
 End of function usb_pstd_self_clock
 ******************************************************************************/

/******************************************************************************
 Function Name   : usb_pstd_stop_clock
 Description     : Not processed as the functionality is provided by R8A66597(ASSP).
 Arguments       : none
 Return value    : none
 ******************************************************************************/
void usb_pstd_stop_clock(void)
{
    g_usb_cstd_suspend_mode = USB_SUSPEND_MODE;
    hw_usb_clear_suspm(); /* UTMI Suspend Mode */
}
/******************************************************************************
 End of function usb_pstd_stop_clock
 ******************************************************************************/
#endif  /* (USB_CFG_MODE & USB_CFG_PERI) == USB_CFG_PERI */

/******************************************************************************
 End of file
 ******************************************************************************/
