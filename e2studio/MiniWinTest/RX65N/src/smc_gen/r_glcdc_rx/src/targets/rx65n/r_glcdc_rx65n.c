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
 * Copyright (C) 2017 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_glcdc_rx65n.c
 * Version      : 1.00
 * Description  : Internal function program using in GLCDC API functions.
 ************************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version   Description
 *         : 24.02.2017 1.00      First Release
***********************************************************************************************************************/
/***********************************************************************************************************************
 Includes <System Includes> , "Project Includes"
 ************************************************************************************************************************/
#include "../../r_glcdc_private.h"

/***********************************************************************************************************************
 Imported global variables and functions (from other files)
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 ***********************************************************************************************************************/

/*******************************************************************************
 * Outline      : Interrupt setting.
 * Function Name: r_glcdc_interrupt_setting
 * Description  : Graphic 1 underflow, Graphic 2 underflow, Graphic 2 line detection
 *                interrupt setting.
 * Arguments    : p_interrupt -
 *                  Enable or disable of each interrupt.
 * Return Value : none
 * Note         : none
 *******************************************************************************/
void r_glcdc_interrupt_setting(glcdc_interrupt_cfg_t const * const p_interrupt)
{
    bsp_int_ctrl_t grpal1;

    grpal1.ipl = GLCDC_CFG_INTERRUPT_PRIORITY_LEVEL;

    if (true == p_interrupt->vpos_enable)
    {
        /* INTEN - Interrupt Request Enable Control Register
        b31:b3 Reserved   - These bits are read as 0. Writing to these bits have no effect.
        b2     GR2UFINTEN - GR2UF Interrupt Enable.
        b1     GR1UFINTEN - GR1UF Interrupt Enable.
        b0     VPOSINTEN  - VPOS Interrupt Enable. - Enable VPOS interrupt request. */
        GLCDC.INTEN.BIT.VPOSINTEN = 1;

        /* GENAL1 - Group AL1 Interrupt Request Enable Register
        b8 EN8 - Interrupt Request Enable 8 - Interrupt request is enabled. */
        EN(GLCDC,VPOS) = 1;
    }
    else
    {
        /* INTEN - Interrupt Request Enable Control Register
        b0 VPOSINTEN  - VPOS Interrupt Enable. - Disable VPOS interrupt request. */
        GLCDC.INTEN.BIT.VPOSINTEN = 0;

        /* GENAL1 - Group AL1 Interrupt Request Enable Register
        b8 EN8 - Interrupt Request Enable 8 - Interrupt request is disabled. */
        EN(GLCDC,VPOS) = 0;

        /* GRPAL1 - Group AL1 Interrupt Request Register
        b8 IS8 - Interrupt Status Flag 8. */
        while (0 != IS(GLCDC,VPOS))
        {
            nop();
        }
    }

    if (true == p_interrupt->gr1uf_enable)
    {
        /* INTEN - Interrupt Request Enable Control Register
        b1 GR1UFINTEN - GR1UF Interrupt enable. */
        GLCDC.INTEN.BIT.GR1UFINTEN = 1;

        /* GENAL1 - Group AL1 Interrupt Request Enable Register
        b9 EN9 - Interrupt Request Enable 9 - Interrupt request is enabled. */
        EN(GLCDC,GR1UF) = 1;
    }
    else
    {
        /* INTEN - Interrupt Request Enable Control Register
        b1 GR1UFINTEN - GR1UF Interrupt disable. */
        GLCDC.INTEN.BIT.GR1UFINTEN = 0;

        /* GENAL1 - Group AL1 Interrupt Request Enable Register
        b9 EN9 - Interrupt Request Enable 9 - Interrupt request is disabled. */
        EN(GLCDC,GR1UF) = 0;

        /* GRPAL1 - Group AL1 Interrupt Request Register
        b9 IS9 - Interrupt Status Flag 9. */
        while (0 != IS(GLCDC,GR1UF))
        {
            nop();
        }
    }

    if (true == p_interrupt->gr2uf_enable)
    {
        /* INTEN - Interrupt Request Enable Control Register
        b2 GR2UFINTEN - GR2UF Interrupt enable. */
        GLCDC.INTEN.BIT.GR2UFINTEN = 1;

        /* GENAL1 - Group AL1 Interrupt Request Enable Register
        b10 EN10 - Interrupt Request Enable 10 - Interrupt request is enabled. */
        EN(GLCDC,GR2UF) = 1;
    }
    else
    {
        /* INTEN - Interrupt Request Enable Control Register
        b2 GR2UFINTEN - GR2UF Interrupt disable. */
        GLCDC.INTEN.BIT.GR2UFINTEN = 0;

        /* GENAL1 - Group AL1 Interrupt Request Enable Register
        b10 EN10 - Interrupt Request Enable 10 - Interrupt request is disabled. */
        EN(GLCDC,GR2UF) = 0;

        /* GRPAL1 - Group AL1 Interrupt Request Register
        b10 IS10 - Interrupt Status Flag 10. */
        while (0 != IS(GLCDC,GR2UF))
        {
            nop();
        }
    }

    /* Set GROUPAL1 interrupt request to enable, if GLCDC interrupt parameter is enabled
       Set GROUPAL1 interrupt request to disable, if GLCDC interrupt parameter is disabled */
    if ((true == p_interrupt->vpos_enable) || (true == p_interrupt->gr1uf_enable) || (true == p_interrupt->gr2uf_enable))
    {
        R_BSP_InterruptControl(BSP_INT_SRC_AL1_GLCDC_VPOS, BSP_INT_CMD_GROUP_INTERRUPT_ENABLE, (void *) &grpal1.ipl);
    }
    else
    {
        R_BSP_InterruptControl(BSP_INT_SRC_AL1_GLCDC_VPOS, BSP_INT_CMD_GROUP_INTERRUPT_DISABLE, NULL);
    }

} /* End of function r_glcdc_interrupt_setting() */

/* End of File */
