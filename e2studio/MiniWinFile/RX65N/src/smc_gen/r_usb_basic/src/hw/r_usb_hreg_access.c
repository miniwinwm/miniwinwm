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
 * File Name    : r_usb_hreg_access.c
 * Description  : USB IP Host control register access code
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 08.01.2014 1.00 First Release
 *         : 26.12.2014 1.10 RX71M is added
 *         : 30.09.2015 1.11 RX63N/RX631 is added.
 *         : 30.09.2016 1.20 RX65N/RX651 is added.
 *         : 30.09.2017 1.22 RX62N/RX630/RX63T-H is added. and Add "__evenaccess" for I/O reg access local variable.
 *         : 31.03.2018 1.23 Supporting Smart Configurator
 *         : 16.11.2018 1.24 Added '~' before USB_OVRCRE in hw_usb_hclear_enb_ovrcre()
 ***********************************************************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include "r_usb_basic_if.h"
#include "r_usb_typedef.h"
#include "r_usb_bitdefine.h"
#include "r_usb_reg_access.h"
#include "r_usb_extern.h"

#if ( (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST )

/******************************************************************************
 Function Name   : hw_usb_hset_rwupe
 Description     : Set the RWUPE-bit specified port's DVSTCTR0 reg-
                 : ister. When host. To allow detection of remote wake-up from 
                 : a USB Function.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_rwupe (usb_utr_t *ptr)
{
    ptr->ipp->DVSTCTR0.WORD |= USB_RWUPE;
}
/******************************************************************************
 End of function hw_usb_hset_rwupe
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_rwupe
 Description     : Clear the RWUPE-bit specified port's DVSTCTR0 reg-
                 : ister. When host. To prohibit detection of remote wake-up from 
                 : a USB Function.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_rwupe (usb_utr_t *ptr)
{
    ptr->ipp->DVSTCTR0.WORD &= (~USB_RWUPE);
}
/******************************************************************************
 End of function hw_usb_hclear_rwupe
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_resume
 Description     : Set the RESUME-bit specified port's DVSTCTR0 register 
                 : When host. To allow output of resume signal to a USB Function.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_resume (usb_utr_t *ptr)
{
    ptr->ipp->DVSTCTR0.WORD |= USB_RESUME;
}
/******************************************************************************
 End of function hw_usb_hset_resume
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_resume
 Description     : Clear the RESUME-bit specified port's DVSTCTR0 register 
                 : When host. To prohibit output of resume signal to a USB Func-
                 : tion.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_resume (usb_utr_t *ptr)
{
    ptr->ipp->DVSTCTR0.WORD &= (~USB_RESUME);
}
/******************************************************************************
 End of function hw_usb_hset_uact
 ******************************************************************************/
 
/******************************************************************************
 Function Name   : hw_usb_hset_uact
 Description     : Set UACT-bit (USB Bus Enable) specified port's DVSTCTR0 
                 : register. When Host, to output SOF.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_uact (usb_utr_t *ptr)
{
    ptr->ipp->DVSTCTR0.WORD |= USB_UACT;
}
/******************************************************************************
 End of function hw_usb_hset_uact
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_uact
 Description     : Clear UACT-bit (USB Bus Enable) specified port's DVSTCTR0 
                 : register. When Host, to prohibit output SOF.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_uact (usb_utr_t *ptr)
{
    ptr->ipp->DVSTCTR0.WORD &= (~USB_UACT);
}
/******************************************************************************
 End of function hw_usb_hclear_uact
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hwrite_intenb
 Description     : Write the specified data to the specified port's INTENB register.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
                 : uint16_t  data   : Setting value
 Return value    : none
 ******************************************************************************/
void hw_usb_hwrite_intenb (usb_utr_t *ptr, uint16_t data)
{
    ptr->ipp->INTENB1.WORD = data;
}
/******************************************************************************
 End of function hw_usb_hwrite_intenb
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_enb_ovrcre
 Description     : Set specified port's OVRCRE-bit (Overcurrent Input Change Int-
                 : errupt Status Enable) in the INTENB1 register.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_ovrcre (usb_utr_t *ptr)
{
    ptr->ipp->INTENB1.WORD |= USB_OVRCRE;
}
/******************************************************************************
 End of function hw_usb_hset_enb_ovrcre
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_enb_ovrcre
 Description     : Clear the OVRCRE-bit of the specified port's INTENB1 register,
                 : to prohibit VBUS interrupts.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_enb_ovrcre (usb_utr_t *ptr)
{
    ptr->ipp->INTENB1.WORD &= (~USB_OVRCRE);
}
/******************************************************************************
 End of function hw_usb_hclear_enb_ovrcre
 ******************************************************************************/
 
/******************************************************************************
 Function Name   : hw_usb_hset_enb_bchge
 Description     : The BCHGE-bit (USB Bus Change Interrupt Enable) is set in the 
                 : specified port's INTENB1 register. This will cause a BCHG 
                 : interrupt when a change of USB bus state has been detected.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_bchge (usb_utr_t *ptr)
{
    ptr->ipp->INTENB1.WORD |= USB_BCHGE;
}
/******************************************************************************
 End of function hw_usb_hset_enb_bchge
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_enb_bchge
 Description     : The BCHGE-bit (USB Bus Change Interrupt Enable) is cleared in 
                 : the specified port's INTENB1 register.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_enb_bchge (usb_utr_t *ptr)
{
    ptr->ipp->INTENB1.WORD &= (~USB_BCHGE);
}
/******************************************************************************
 End of function hw_usb_hclear_enb_bchge
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_enb_dtche
 Description     : Enable the specified port's DTCHE-interrupt "Disconnection 
                 : Detection" by setting the DTCHE-bit.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_dtche (usb_utr_t *ptr)
{
    ptr->ipp->INTENB1.WORD |= USB_DTCHE;
}
/******************************************************************************
 End of function hw_usb_hset_enb_dtche
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_enb_dtche
 Description     : Disable the specified port's DTCHE-interrupt "Disconnection 
                 : Detection" by clearing the DTCHE-bit.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_enb_dtche (usb_utr_t *ptr)
{
    ptr->ipp->INTENB1.WORD &= (~USB_DTCHE);
}
/******************************************************************************
 End of function hw_usb_hclear_enb_dtche
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_enb_attche
 Description     : Enable the specified port's ATTCHE-interrupt "Connection 
                 : Detection" by setting the ATTCHE-bit.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_attche (usb_utr_t *ptr)
{
    ptr->ipp->INTENB1.WORD |= USB_ATTCHE;
}
/******************************************************************************
 End of function hw_usb_hset_enb_attche
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_enb_attche
 Description     : Disable the specified port's ATTCHE-interrupt "Disconnection 
                 : Detection" by clearing the ATTCHE-bit.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_enb_attche (usb_utr_t *ptr)
{
    ptr->ipp->INTENB1.WORD &= (~USB_ATTCHE);
}
/******************************************************************************
 End of function hw_usb_hclear_enb_attche
 ******************************************************************************/
 
/******************************************************************************
 Function Name   : hw_usb_hset_enb_signe
 Description     : Enable the SIGNE-interrupt "Setup Transaction
                 : Error" by setting the SIGNE-bit.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_signe (usb_utr_t *ptr)
{
    ptr->ipp->INTENB1.WORD |= USB_SIGNE;
}
/******************************************************************************
 End of function hw_usb_hset_enb_signe
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_enb_sacke
 Description     : Enable the SACKE-interrupt "Setup Transaction 
                 : Normal Response" by setting the SACKE-bit.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_sacke (usb_utr_t *ptr)
{
    ptr->ipp->INTENB1.WORD |= USB_SACKE;
}
/******************************************************************************
 End of function hw_usb_hset_enb_sacke
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_enb_pddetinte
 Description     : Enable the PDDETINT-interrupt "Connection Detection for 
                 : Battery Charging Supporting Device" by setting 
                 : the PDDETINTE-bit.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_enb_pddetinte (usb_utr_t *ptr)
{
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    if (ptr->ip == USB_USBIP_1)
    {
        ptr->ipp1->INTENB1.WORD |= USB_PDDETINTE;

    }

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
}
/******************************************************************************
 End of function hw_usb_hset_enb_pddetinte
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hwrite_intsts
 Description     : Write the specified data to the specified port's INTSTS1 reg-
                 : ister.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
                 : uint16_t  data   : Setting value
 Return value    : none
 ******************************************************************************/
void hw_usb_hwrite_intsts (usb_utr_t *ptr, uint16_t data)
{
    ptr->ipp->INTSTS1.WORD = data;
}
/******************************************************************************
 End of function hw_usb_hwrite_intsts
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_sts_ovrcr
 Description     : Clear the specified port's OVRCR-bit; "Overcurrent 
                 : Input Change Interrupt Status".
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_ovrcr (usb_utr_t *ptr)
{
    ptr->ipp->INTSTS1.WORD = (uint16_t) ((~USB_OVRCR) & INTSTS1_MASK);
}
/******************************************************************************
 End of function hw_usb_hclear_sts_ovrcr
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_sts_bchg
 Description     : Clear the specified port's BCHG-bit; "USB Bus Change Interrupt 
                 : Status".
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_bchg (usb_utr_t *ptr)
{
    ptr->ipp->INTSTS1.WORD = (uint16_t) ((~USB_BCHG) & INTSTS1_MASK);
} /* End of function hw_usb_hclear_sts_bchg() */
/******************************************************************************
 End of function hw_usb_hclear_sts_bchg
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_sts_dtch
 Description     : Clear the specified port's DTCH-bit; "USB Disconnection Detec-
                 : tion Interrupt Status".
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_dtch (usb_utr_t *ptr)
{
    ptr->ipp->INTSTS1.WORD = (uint16_t) ((~USB_DTCH) & INTSTS1_MASK);
}
/******************************************************************************
 End of function hw_usb_hclear_sts_dtch
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_sts_attch
 Description     : Clear the specified port's ATTCH-bit; "ATTCH Interrupt Status".
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_attch (usb_utr_t *ptr)
{
    ptr->ipp->INTSTS1.WORD = (uint16_t) ((~USB_ATTCH) & INTSTS1_MASK);
}
/******************************************************************************
 End of function hw_usb_hclear_sts_attch
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_sts_sign
 Description     : Clear the SIGN-bit; "Setup Transaction Error
                 : Interrupt Status".
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_sign (usb_utr_t *ptr)
{
    ptr->ipp->INTSTS1.WORD = (uint16_t) ((~USB_SIGN) & INTSTS1_MASK);
}
/******************************************************************************
 End of function hw_usb_hclear_sts_sign
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hclear_sts_sack
 Description     : Clear the SACK-bit; "Setup Transaction Normal
                 : Response Interrupt Status".
                 : Interrupt Status".
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_sack (usb_utr_t *ptr)
{
    ptr->ipp->INTSTS1.WORD = (uint16_t) ((~USB_SACK) & INTSTS1_MASK);
}
/******************************************************************************
 End of function hw_usb_hclear_sts_sack
 ******************************************************************************/
 
/******************************************************************************
 Function Name   : hw_usb_hclear_sts_pddetint
 Description     : Clear the PDDETINT-bit; "
                 : ".
                 : Interrupt Status".
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hclear_sts_pddetint (usb_utr_t *ptr)
{
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    if (ptr->ip == USB_USBIP_1)
    {
        ptr->ipp1->INTSTS1.WORD = (uint16_t) ((~USB_PDDETINT) & INTSTS1_MASK);

    }

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
}
/******************************************************************************
 End of function hw_usb_hclear_sts_pddetint
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hwrite_usbreq
 Description     : Write bRequest and bmRequestType to USBREQ register.
                 : When Host, the values of bRequest and bmRequestType 
                 : to be transmitted are written. (When Function, the received 
                 : values of bRequest and bmRequestType are stored in USBREQ).
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
                 : uint16_t  data   : Setting value
 Return value    : none
 ******************************************************************************/
void hw_usb_hwrite_usbreq (usb_utr_t *ptr, uint16_t data)
{
    ptr->ipp->USBREQ.WORD = data;
}
/******************************************************************************
 End of function hw_usb_hwrite_usbreq
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_usbval
 Description     : Write the specified 'wValue' to USBVAL register,
                 : to write the USB request. When Host, the value of 
                 : wValue to be transmitted is set. (When Function, the value of 
                 : wValue that has been received is stored in USBREQ.)
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
                 : uint16_t  data   : Setting value
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_usbval (usb_utr_t *ptr, uint16_t data)
{
    ptr->ipp->USBVAL = data;
}
/******************************************************************************
 End of function hw_usb_hset_usbval
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_usbindx
 Description     : Write the specified 'wIndex', the USB request, to USBINDX
                 : register, for host setup requests for control 
                 : transfers.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
                 : uint16_t  data   : Setting value
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_usbindx (usb_utr_t *ptr, uint16_t data)
{
    ptr->ipp->USBINDX = data;
}
/******************************************************************************
 End of function hw_usb_hset_usbindx
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_usbleng
 Description     : Write the specified 'wLength' value to USBINDX register, 
                 : for host setup requests for control.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
                 : uint16_t  data   : Setting value
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_usbleng (usb_utr_t *ptr, uint16_t data)
{
    ptr->ipp->USBLENG = data;
}
/******************************************************************************
 End of function hw_usb_hset_usbleng
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hwrite_dcpctr
 Description     : Write the specified data value to the DCPCTR register.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
                 : uint16_t  data   : Setting value
 Return value    : none
 ******************************************************************************/
void hw_usb_hwrite_dcpctr (usb_utr_t *ptr, uint16_t data)
{
    ptr->ipp->DCPCTR.WORD = data;
}
/******************************************************************************
 End of function hw_usb_hwrite_dcpctr
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_sureq
 Description     : Set te SUREQ-bit in the DCPCTR register 
                 : (Set SETUP packet send when HostController function is selected)
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_sureq (usb_utr_t *ptr)
{
    ptr->ipp->DCPCTR.WORD |= USB_SUREQ;
}
/******************************************************************************
 End of function hw_usb_hset_sureq
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hread_devadd
 Description     : Return the DEVADD register value for the specified USB device 
                 ; address.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
                 : uint16_t  devsel : USB device address value 
 Return value    : DEVADDx content
 ******************************************************************************/
uint16_t hw_usb_hread_devadd (usb_utr_t *ptr, uint16_t devsel)
{
    volatile __evenaccess uint16_t *preg;
    uint16_t devadr;
    uint16_t return_value;

    devadr = devsel >> USB_DEVADDRBIT;

    if (devadr > USB_MAXDEVADDR)
    {
        return USB_ERROR;
    }
    else
    {
        preg = (uint16_t *) &(ptr->ipp->DEVADD0) + devadr;
        return_value = ((*preg) & ((USB_UPPHUB | USB_HUBPORT) | USB_USBSPD));
        return return_value;
    }
}
/******************************************************************************
 End of function hw_usb_hread_devadd
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hrmw_devadd
 Description     : Read-modify-write the specified devsel's DEVADD.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
                 : uint16_t  devsel : USB device address value 
                 : uint16_t  data   : The value to write.
                 : uint16_t  width  : Bit pattern to read-modify-write.
 Return value    : none
 ******************************************************************************/
void hw_usb_hrmw_devadd (usb_utr_t *ptr, uint16_t devsel, uint16_t data, uint16_t width)
{
    volatile __evenaccess uint16_t *preg;
    uint16_t buf;
    uint16_t devadr;

    devadr = devsel >> USB_DEVADDRBIT;

    preg = (uint16_t *) &(ptr->ipp->DEVADD0) + devadr;

    buf = *preg;
    buf &= (~width);
    buf |= (data & width);
    *preg = buf;
}
/******************************************************************************
 End of function hw_usb_hrmw_devadd
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_usbspd
 Description     : Set the DEVADD register's USBSPD for the specified device add-
                 : ress.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
                 : uint16_t  devsel : USB device address value 
                 : uint16_t  data   : The value to write.
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_usbspd (usb_utr_t *ptr, uint16_t devsel, uint8_t data)
{
    volatile __evenaccess uint16_t *preg;
    uint16_t devadr;

    devadr = devsel >> USB_DEVADDRBIT;

    preg = (uint16_t *) &(ptr->ipp->DEVADD0) + devadr;

    (*preg) &= (~USB_USBSPD);
    (*preg) |= data;
}
/******************************************************************************
 End of function hw_usb_hset_usbspd
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_dcpmode
 Description     : Set DCPMODE bit.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_dcpmode (usb_utr_t *ptr)
{
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
    if (ptr->ip == USB_USBIP_1)
    {
        ptr->ipp1->BCCTRL.WORD |= USB_DCPMODE;

    }
#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
}
/******************************************************************************
 End of function hw_usb_hset_dcpmode
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hmodule_init
 Description     : USB module initialization for USB Host mode
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hmodule_init (usb_ctrl_t *p_ctrl)
{
    uint16_t sts;

    if ( USB_IP0 == p_ctrl->module)
    {
        USB_M0.SYSCFG.WORD |= USB_SCKE;
        while ( USB_SCKE != (USB_M0.SYSCFG.WORD & USB_SCKE))
        {
            /* none */
        }

#if defined(BSP_MCU_RX64M)
        USB_M0.PHYSLEW.LONG = 0xE;

#endif  /* defined(BSP_MCU_RX64M) */

#if defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX65N)
        USB_M0.PHYSLEW.LONG = 0x5;

#endif  /* defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX65N) */

        USB_M0.SYSCFG.WORD |= USB_DCFM;

        USB_M0.SYSCFG.WORD |= USB_DRPD;

        sts = usb_chattaring((uint16_t *) &USB_M0.SYSSTS0.WORD);

        USB_M0.SYSCFG.WORD |= USB_USBE;

        USB_M0.CFIFOSEL.WORD  = USB0_CFIFO_MBW;
        USB_M0.D0FIFOSEL.WORD = USB0_D0FIFO_MBW;
        USB_M0.D1FIFOSEL.WORD = USB0_D1FIFO_MBW;

#if USB_CFG_ENDIAN == USB_CFG_BIG
        USB_M0.CFIFOSEL.WORD |= USB_BIGEND;
        USB_M0.D0FIFOSEL.WORD |= USB_BIGEND;
        USB_M0.D1FIFOSEL.WORD |= USB_BIGEND;

#endif  /* USB_CFG_ENDIAN == USB_CFG_BIG */

        switch (sts)
        {
            case USB_FS_JSTS : /* USB device already connected */
            case USB_LS_JSTS :
                USB_M0.DVSTCTR0.WORD |= USB_USBRST;
                usb_cpu_delay_xms((uint16_t) 50); /* Need to wait greater equal 10ms in USB spec */
                USB_M0.DVSTCTR0.WORD &= (~USB_USBRST);
                while ( USB_HSPROC == (USB_M0.DVSTCTR0.WORD & USB_HSPROC))
                {
                    /* HSPROC = 0100b */
                }

                if ( USB_LSMODE == (USB_M0.DVSTCTR0.WORD & USB_RHST))
                {
                    USB_M0.SOFCFG.WORD |= USB_TRNENSEL;
                }

                USB_M0.DVSTCTR0.WORD |= USB_UACT;
            break;

            case USB_SE0 : /* USB device no connected */
                USB_M0.INTENB1.WORD = USB_ATTCH;
            break;

            default :
            break;
        }
        USB_M0.INTSTS1.WORD &= ((~USB_OVRCRE) & INTSTS1_MASK);
        USB_M0.INTENB0.WORD = ((USB_BEMPE | USB_NRDYE) | USB_BRDYE);
        USB_M0.INTENB1.WORD = (USB_OVRCRE | USB_ATTCH);
    }
#if USB_NUM_USBIP == 2
    else
    {
#if defined(BSP_MCU_RX62N)
        USB_M1.SYSCFG.WORD |= USB_SCKE;
        while ( USB_SCKE != (USB_M1.SYSCFG.WORD & USB_SCKE))
        {
            /* none */
        }
#endif /* defined(BSP_MCU_RX62N) */

#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
#if USB_CFG_CLKSEL == USB_CFG_20MHZ
        USB_M1.PHYSET.WORD &= ~USB_CLKSEL;
        USB_M1.PHYSET.WORD |= USB_CLKSEL_20;

#endif  /* USB_CFG_CLKSEL == USB_CFG_20MHZ */

#if USB_CFG_CLKSEL == USB_CFG_OTHER
        USB_M1.PHYSET.WORD |= USB_HSEB;

#else   /* USB_CFG_OTHER == USB_CFG_OTHER */
        USB_M1.PHYSET.WORD |= USB_REPSEL_16;

#endif  /* USB_CFG_OTHER == USB_CFG_OTHER */

        usb_cpu_delay_1us((uint16_t) 1);                    /* wait 1usec */

        USB_M1.PHYSET.WORD &= (~USB_DIRPD);
        usb_cpu_delay_xms(1); /* wait 1msec */

#if ((USB_CFG_CLKSEL == USB_CFG_20MHZ) || (USB_CFG_CLKSEL == USB_CFG_24MHZ))
        USB_M1.PHYSET.WORD &= (~USB_PLLRESET);

#endif  /* (USB_CFG_CLKSEL == USB_CFG_20MHZ) || (USB_CFG_CLKSEL == USB_CFG_24MHZ) */

        USB_M1.LPSTS.WORD |= USB_SUSPENDM;

#if ((USB_CFG_CLKSEL == USB_CFG_20MHZ) || (USB_CFG_CLKSEL == USB_CFG_24MHZ))
        while( USB_PLLLOCK != (USB_M1.PLLSTA.WORD & USB_PLLLOCK ) )
        {
            /* Wait for PLL Lock */
        };

#endif  /* (USB_CFG_CLKSEL == USB_CFG_20MHZ) || (USB_CFG_CLKSEL == USB_CFG_24MHZ) */

        USB_M1.SYSCFG.WORD |= USB_DRPD;

        USB_M1.SYSCFG.WORD |= USB_CNEN;

        USB_M1.BUSWAIT.WORD = (USB_CFG_BUSWAIT | 0x0F00);
        usb_cpu_delay_1us((uint16_t) 1);                    /* wait 1usec */

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */

        USB_M1.SOFCFG.WORD |= USB_INTL;

        USB_M1.SYSCFG.WORD |= USB_DCFM;

#if defined(BSP_MCU_RX62N)
        USB_M1.SYSCFG.WORD |= USB_DRPD;
#endif /* defined(BSP_MCU_RX62N) */

        sts = usb_chattaring( (uint16_t *)&USB_M1.SYSCFG.WORD );

        USB_M1.SYSCFG.WORD |= USB_USBE;

        USB_M1.CFIFOSEL.WORD  = USB1_CFIFO_MBW;
        USB_M1.D0FIFOSEL.WORD = USB1_D0FIFO_MBW;
        USB_M1.D1FIFOSEL.WORD = USB1_D1FIFO_MBW;

#if USB_CFG_ENDIAN ==USB_CFG_BIG
        USB_M1.CFIFOSEL.WORD |= USB_BIGEND;
        USB_M1.D0FIFOSEL.WORD |= USB_BIGEND;
        USB_M1.D1FIFOSEL.WORD |= USB_BIGEND;
#endif
        switch( sts )
        {
            case USB_FS_JSTS: /* USB device already connected */
            case USB_LS_JSTS:
                if (USB_FS_JSTS == sts)
                {
                    USB_M1.SYSCFG.WORD |= USB_HSE;
                }

                USB_M1.DVSTCTR0.WORD |= USB_USBRST;

                usb_cpu_delay_xms((uint16_t)50); /* Need to wait greater equal 10ms in USB spec */

                USB_M1.DVSTCTR0.WORD &= (~USB_USBRST);
                while (USB_HSPROC == (USB_M1.DVSTCTR0.WORD & USB_HSPROC))
                {
                    /* Wait for USB reset handshake in progress */
                };

                if (USB_LSMODE == (USB_M1.DVSTCTR0.WORD & USB_RHST))
                {
                    USB_M1.SOFCFG.WORD |= USB_TRNENSEL;
                }

                USB_M1.DVSTCTR0.WORD |= USB_UACT;
            break;
            case USB_SE0: /* USB device no connected */
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX62N)
                USB_M1.INTENB1.WORD = USB_ATTCH;

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) || defined(BSP_MCU_RX62N) */
            break;
            default:
            break;
        }
        USB_M1.INTSTS1.WORD &= (~USB_OVRCRE & INTSTS1_MASK);
        USB_M1.INTENB0.WORD = (USB_BEMPE | USB_NRDYE | USB_BRDYE);
#if defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M)
        USB_M1.INTENB1.WORD = (USB_OVRCRE | USB_ATTCH);

#endif  /* defined(BSP_MCU_RX64M) || defined(BSP_MCU_RX71M) */
    }
#endif /* USB_NUM_USBIP == 2 */
}
/******************************************************************************
 End of function hw_usb_hmodule_init
 ******************************************************************************/

/******************************************************************************
 Function Name   : hw_usb_hset_trnensel
 Description     : When host, set the TRNENSEL-bit; "Transac-
                 : tion-Enabled Time Select" for low-speed USB communication.
                 : This bit should be set to 0 if USB Function.
 Arguments       : usb_utr_t *ptr   : Pointer to usb_utr_t structure
 Return value    : none
 ******************************************************************************/
void hw_usb_hset_trnensel (usb_utr_t *ptr)
{
    ptr->ipp->SOFCFG.WORD |= USB_TRNENSEL;
}
/******************************************************************************
 End of function hw_usb_hset_trnensel
 ******************************************************************************/

#endif  /* (USB_CFG_MODE & USB_CFG_HOST) == USB_CFG_HOST */

/******************************************************************************
 End of file
 ******************************************************************************/
