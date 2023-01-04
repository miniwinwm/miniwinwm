/***********************************************************************************************************************
 * Copyright [2015-2021] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
 * 
 * This file is part of Renesas SynergyTM Software Package (SSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas SSP license agreement. Unless otherwise agreed in an SSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
 **********************************************************************************************************************/

/*********************************************************************************************************************
 * File Name    : hw_sci_spi_private.h
 * @brief    SCI HAL driver for SPI
 ********************************************************************************************************************/
#ifndef HW_SCI_SPI_PRIVATE_H
#define HW_SCI_SPI_PRIVATE_H


/*********************************************************************************************************************
 * Includes
 ********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "bsp_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER


/* Public interface header file for this module. */

/*********************************************************************************************************************
 * Macro definitions
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * Typedef definitions
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * Private function prototypes
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * Private global variables
 ********************************************************************************************************************/

/*********************************************************************************************************************
 * Private Functions
 ********************************************************************************************************************/
/*****************************************************************************************************************//**
 * @brief     This function selects Simple SPI mode
 * @param[in] channel   SCI channel
 * @retval    void
 * @note      Channel number is not checked in this function, caller function must check it.
 ********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_SPIModeSelect (R_SCI0_Type * p_sci_reg)
{
    /* Set the SCMR.SMIF to 0 (0: Asynchronous, clock synchronous, simple SPI, I2C mode) */
    /* Set the SIMR1.IICM bit to 0 (0: Asynchronous, clock synchronous, simple SPI mode) */
    /* Set the SMR.CM bit to 1 (1: Clock synchronous or SPI mode) */
    /* Set the SPMR.SSE bit to 1 (1: Enable SSn# pin function in SPI mode) */

    p_sci_reg->SCMR_b.SMIF  = 0U;
    p_sci_reg->SIMR1_b.IICM = 0U;
    p_sci_reg->SMR_b.CM     = 1U;
    p_sci_reg->SPMR_b.SSE   = 0U; //set it to single master, not control the SSE pin
}  /* End of function HW_SCI_SPIModeSelect() */

/*******************************************************************************************************************//**
* Sets the SPI Mode Register (SPMR) for SPI mode operation.
* @param[in] channel    SCI Channel number
* @param[in] modeval    SPI mode register setting
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_SPIModeSet (R_SCI0_Type * p_sci_reg, uint8_t modeval)
{
    p_sci_reg->SPMR = modeval;
}  /* End of function HW_SCI_SPIModeSet() */

/*******************************************************************************************************************//**
* Clears the SPI Mode Register (SPMR) Mode Fault Error bit.
* @param[in] channel    SCI Channel number
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_SPIModeFaultClear (R_SCI0_Type * p_sci_reg)
{
    p_sci_reg->SPMR_b.MFF = 0U;
}  /* End of function HW_SCI_SPIClearModeFault() */

/*******************************************************************************************************************//**
* Checks the SPI Mode Register (SPMR) Mode Fault Error bit.
* @param[in] channel    SCI Channel number
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE bool HW_SCI_SPIModeFaultCheck (R_SCI0_Type * p_sci_reg)
{
    return (1U == p_sci_reg->SPMR_b.MFF);
}  /* End of function HW_SCI_SPIClearModeFault() */

/*******************************************************************************************************************//**
* This function reads master/slave status from SPMR register.
* @param[in] channel    SCI Channel number
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE bool HW_SCI_SPIMasterCheck (R_SCI0_Type * p_sci_reg)
{
    return (0U == p_sci_reg->SPMR_b.MSS);
}  /* End of function HW_SCI_SPIMasterGet() */

/*******************************************************************************************************************//**
* @brief     This function returns the address of the write register
* @param[in] channel     SCI channel
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE uint8_t volatile const * HW_SCI_SPIWriteAddrGet (R_SCI0_Type * p_sci_reg)
{
        return (uint8_t volatile const *) (&(p_sci_reg->TDR));
}  /* End of function HW_SCI_SPIWriteAddrGet() */

/*******************************************************************************************************************//**
* @brief     This function returns the address of the read register
* @param[in] channel     SCI channel
* @note      Channel number is not checked in this function, caller function must check it.
***********************************************************************************************************************/
__STATIC_INLINE uint8_t volatile const * HW_SCI_SPIReadAddrGet (R_SCI0_Type * p_sci_reg)
{
        return (uint8_t volatile const *) (&(p_sci_reg->RDR));
}  /* End of function HW_SCI_SPIReadAddrGet() */

/*******************************************************************************************************************//**
 * Enables transmit interrupt.
 * @param   channel     The hardware channel to access
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_TxIrqEnable(R_SCI0_Type * p_reg)
{
    p_reg->SCR_b.TIE = 1U;
}

/*******************************************************************************************************************//**
 * Enables receive interrupt.
 * @param   channel     The hardware channel to access
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_RxIrqEnable(R_SCI0_Type * p_reg)
{
    p_reg->SCR_b.RIE = 1U;
}

/*******************************************************************************************************************//**
 * Enables transmit end interrupt.
 * @param   channel     The hardware channel to access
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_TeIrqEnable(R_SCI0_Type * p_reg)
{
    p_reg->SCR_b.TEIE = 1U;
}

/*******************************************************************************************************************//**
 * Disables transmit interrupt.
 * @param   channel     The hardware channel to access
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_TxIrqDisable(R_SCI0_Type * p_reg)
{
    p_reg->SCR_b.TIE = 0U;
}

/*******************************************************************************************************************//**
 * Disables receive interrupt.
 * @param   channel     The hardware channel to access
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_RxIrqDisable(R_SCI0_Type * p_reg)
{
    p_reg->SCR_b.RIE = 0U;
}

/*******************************************************************************************************************//**
 * Disables transmit end interrupt.
 * @param   channel     The hardware channel to access
 **********************************************************************************************************************/
__STATIC_INLINE void HW_SCI_TeIrqDisable(R_SCI0_Type * p_reg)
{
    p_reg->SCR_b.TEIE = 0U;
}

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER
#endif /* HW_SCI_SPI_PRIVATE_H */
