/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_glcdc_rx_pinset.c
* Version      : 1.0.2
* Device(s)    : R5F565NEDxFB
* Tool-Chain   : RXC toolchain
* Description  : Setting of port and mpc registers
* Creation Date: 2019-02-10
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_glcdc_rx_pinset.h"
#include "platform.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: R_GLCDC_PinSet
* Description  : This function initializes pins for r_glcdc_rx module
* Arguments    : none
* Return Value : none
***********************************************************************************************************************/
void R_GLCDC_PinSet()
{
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC);

    /* Set LCD_CLK pin */
    MPC.PB5PFS.BYTE = 0x25U;
    PORTB.PMR.BIT.B5 = 1U;

    /* Set LCD_TCON0 pin */
    MPC.PB4PFS.BYTE = 0x25U;
    PORTB.PMR.BIT.B4 = 1U;

    /* Set LCD_TCON2 pin */
    MPC.PB2PFS.BYTE = 0x25U;
    PORTB.PMR.BIT.B2 = 1U;

    /* Set LCD_TCON3 pin */
    MPC.PB1PFS.BYTE = 0x25U;
    PORTB.PMR.BIT.B1 = 1U;

    /* Set LCD_DATA0 pin */
    MPC.PB0PFS.BYTE = 0x25U;
    PORTB.PMR.BIT.B0 = 1U;

    /* Set LCD_DATA1 pin */
    MPC.PA7PFS.BYTE = 0x25U;
    PORTA.PMR.BIT.B7 = 1U;

    /* Set LCD_DATA2 pin */
    MPC.PA6PFS.BYTE = 0x25U;
    PORTA.PMR.BIT.B6 = 1U;

    /* Set LCD_DATA3 pin */
    MPC.PA5PFS.BYTE = 0x25U;
    PORTA.PMR.BIT.B5 = 1U;

    /* Set LCD_DATA4 pin */
    MPC.PA4PFS.BYTE = 0x25U;
    PORTA.PMR.BIT.B4 = 1U;

    /* Set LCD_DATA5 pin */
    MPC.PA3PFS.BYTE = 0x25U;
    PORTA.PMR.BIT.B3 = 1U;

    /* Set LCD_DATA6 pin */
    MPC.PA2PFS.BYTE = 0x25U;
    PORTA.PMR.BIT.B2 = 1U;

    /* Set LCD_DATA7 pin */
    MPC.PA1PFS.BYTE = 0x25U;
    PORTA.PMR.BIT.B1 = 1U;

    /* Set LCD_DATA8 pin */
    MPC.PA0PFS.BYTE = 0x25U;
    PORTA.PMR.BIT.B0 = 1U;

    /* Set LCD_DATA9 pin */
    MPC.PE7PFS.BYTE = 0x25U;
    PORTE.PMR.BIT.B7 = 1U;

    /* Set LCD_DATA10 pin */
    MPC.PE6PFS.BYTE = 0x25U;
    PORTE.PMR.BIT.B6 = 1U;

    /* Set LCD_DATA11 pin */
    MPC.PE5PFS.BYTE = 0x25U;
    PORTE.PMR.BIT.B5 = 1U;

    /* Set LCD_DATA12 pin */
    MPC.PE4PFS.BYTE = 0x25U;
    PORTE.PMR.BIT.B4 = 1U;

    /* Set LCD_DATA13 pin */
    MPC.PE3PFS.BYTE = 0x25U;
    PORTE.PMR.BIT.B3 = 1U;

    /* Set LCD_DATA14 pin */
    MPC.PE2PFS.BYTE = 0x25U;
    PORTE.PMR.BIT.B2 = 1U;

    /* Set LCD_DATA15 pin */
    MPC.PE1PFS.BYTE = 0x25U;
    PORTE.PMR.BIT.B1 = 1U;

    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC);
}

