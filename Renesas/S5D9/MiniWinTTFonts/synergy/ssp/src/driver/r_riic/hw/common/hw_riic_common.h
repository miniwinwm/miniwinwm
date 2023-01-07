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
/**********************************************************************************************************************
* File Name    : hw_riic_common.h
* Description  : LLD implementation of the RIIC hardware
***********************************************************************************************************************/

#ifndef HW_RIIC_COMMON_H
#define HW_RIIC_COMMON_H

/**********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "bsp_api.h"
#include "r_riic_cfg.h"
#include "r_riic.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/** The timeout interrupt enable bit */
#define RIIC_TMO_EN_BIT     (0x01)
/** The arbitration loss detection interrupt enable bit */
#define RIIC_ALD_EN_BIT     (0x02)
/** The start condition detection interrupt enable bit */
#define RIIC_STR_EN_BIT     (0x04)
/** The stop condition detection interrupt enable bit */
#define RIIC_STP_EN_BIT     (0x08)
/** The NAK reception interrupt enable bit */
#define RIIC_NAK_EN_BIT     (0x10)
/** The receive data full interrupt enable bit */
#define RIIC_RXI_EN_BIT     (0x20)
/** The transmit end interrupt enable bit */
#define RIIC_TEI_EN_BIT     (0x40)
/** The transmit data empty interrupt enable bit */
#define RIIC_TXI_EN_BIT     (0x80)

/** The ELC_EVENT offset per channel */
#define RIIC_ELC_EVENT_OFFSET_PER_CHANNEL  (0x05)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/** Hardware errors and events that can occur on the RIIC */
typedef enum e_riic_err_event
{
    RIIC_ERR_EVENT_NONE = 0,
    RIIC_ERR_EVENT_TIMEOUT = 1,
    RIIC_ERR_EVENT_ARBITRATION_LOSS = 2,
    RIIC_ERR_EVENT_START = 4,
    RIIC_ERR_EVENT_STOP = 8,
    RIIC_ERR_EVENT_NACK = 16
} riic_err_t;


typedef enum e_timeout_option
{
    RIIC_TIMEOUT_OFF,
    RIIC_TIMEOUT_ON_SCL_HIGH,
    RIIC_TIMEOUT_ON_SCL_LOW,
    RIIC_TIMEOUT_ON_BOTH
}riic_timeout_t;

/***********************************************************************************************************************
Private function prototypes
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Private Functions
***********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Enable or disable output of SDA/SCL.
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   enable  True when enabling SDA/SCL pins, otherwise disable SDA/SCL pin output
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_Output          (R_IIC0_Type * p_riic_reg, bool     const   enable)
{
    p_riic_reg->ICCR1_b.ICE = enable;

    /* Give time for value to be updated */
    volatile uint8_t dummy;
    dummy  = p_riic_reg->ICCR1_b.ICE;
    dummy  = p_riic_reg->ICCR1_b.ICE;
    dummy  = p_riic_reg->ICCR1_b.ICE;
    SSP_PARAMETER_NOT_USED(dummy);
}

/*******************************************************************************************************************//**
 * Set whether the peripheral is in the reset state.
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   enable  True when enabling SDA/SCL pins, otherwise disable SDA/SCL pin output
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_Reset           (R_IIC0_Type * p_riic_reg, bool     const   enable)
{
    p_riic_reg->ICCR1_b.IICRST = enable;

    /* Give time for value to be updated */
    volatile uint8_t dummy;
    dummy  = p_riic_reg->ICCR1_b.IICRST;
    dummy  = p_riic_reg->ICCR1_b.IICRST;
    dummy  = p_riic_reg->ICCR1_b.IICRST;
    SSP_PARAMETER_NOT_USED(dummy);
}

/*******************************************************************************************************************//**
 * Sets the communications rate of the specified RIIC block.
 * @param   p_riic_reg  Base address of the hardware registers
 * @param   highCount   The number of counts to spend with the clock line at high level
 * @param   lowCount    The number of counts to spend with the clock line at low level
 * @param   refClock    The setting that chooses the divisor for the reference clock
 * @param   fmplus      Whether to enable or disable Fm+ mode
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_ClockCfg        (R_IIC0_Type * p_riic_reg,
                                                 uint8_t    const highCount,
                                                 uint8_t    const lowCount,
                                                 uint8_t    const refClock,
                                                 bool       const fmplus)
{
    /* Set the number of counts that the clock remains high */
    p_riic_reg->ICBRH_b.BRH = (uint8_t)(0x1F & highCount);

    /* Set the number of counts that the clock remains low */
    p_riic_reg->ICBRL_b.BRL = (uint8_t)(0x1F & lowCount);

    /* Set the internal reference clock source for generating IIC clock */
    p_riic_reg->ICMR1_b.CKS = (uint8_t)(0x7 & refClock);

    /* Set whether the Fm+ slope control circuit is used */
    p_riic_reg->ICFER_b.FMPE = fmplus;
}

/*******************************************************************************************************************//**
 * Enable/disable slope control circuit
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   timeout         timeout type
 * @param   timeout mode    short mode or long mode
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_TimeoutCfg (R_IIC0_Type * p_riic_reg, riic_timeout_t timeout, riic_timeout_mode_t timeout_mode)
{
   if(RIIC_TIMEOUT_OFF != timeout)
   {
       if(RIIC_TIMEOUT_ON_SCL_HIGH == timeout)
       {
           p_riic_reg->ICMR2_b.TMOH = 1;
       }
       else if(RIIC_TIMEOUT_ON_SCL_LOW== timeout)
       {
           p_riic_reg->ICMR2_b.TMOL = 1;
       }
       else
       {
           p_riic_reg->ICMR2_b.TMOH = 1;
           p_riic_reg->ICMR2_b.TMOL = 1;
       }

       p_riic_reg->ICMR2_b.TMOS = (RIIC_TIMEOUT_MODE_SHORT == timeout_mode);

       /* Enable timeout function */
       p_riic_reg->ICFER_b.TMOE = 1;
   }
   else
   {
       /* Disable timeout function */
       p_riic_reg->ICFER_b.TMOE = 0;
   }
}


/*******************************************************************************************************************//**
 * Enables/Disables the timeout function of the specified RIIC block.
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   enable          True when enabling, otherwise disable
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_TimeoutEnable      (R_IIC0_Type * p_riic_reg, bool enable)
{
    if (true == enable)
    {
        /* Enable timeout function */
        p_riic_reg->ICFER_b.TMOE = 1;
    }
    else
    {
        /* Disable timeout function */
        p_riic_reg->ICFER_b.TMOE = 0;
    }
}

/*******************************************************************************************************************//**
 * Function for disabling features of the peripheral that are not supported.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_NoSupport       (R_IIC0_Type * p_riic_reg)
{
    /* Disable SDA delay features */
    p_riic_reg->ICMR2 &= 0x0F;

    /* Disable noise filter, wait, and SMBus features */
    p_riic_reg->ICMR3 = 0x00;
    p_riic_reg->ICFER_b.NFE = 0;
}

/*******************************************************************************************************************//**
 * Sets up features on the specified RIIC block for master mode.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_SetupMaster     (R_IIC0_Type * p_riic_reg)
{
    /* Enable master arbitration loss detection */
    p_riic_reg->ICFER_b.MALE  = 1;

    /* Enable suspending transfer when NACK received */
    p_riic_reg->ICFER_b.NACKE = 1;
}

/*******************************************************************************************************************//**
 * Signals the specified RIIC block to send the start condition.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_SendStart       (R_IIC0_Type * p_riic_reg)
{
    /* Request RIIC to issue the start condition */
    p_riic_reg->ICCR2_b.ST = 1;
}

/*******************************************************************************************************************//**
 * Read one byte from the specified RIIC block.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_RIIC_ReadByte        (R_IIC0_Type * p_riic_reg)
{
    while (!p_riic_reg->ICSR2_b.RDRF);
    return p_riic_reg->ICDRR;
}

/*******************************************************************************************************************//**
 * Write one byte to the specified RIIC block.
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   byte            Data need to be written in data register
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_WriteByte       (R_IIC0_Type * p_riic_reg, uint8_t  const   byte)
{
    p_riic_reg->ICDRT = byte;
}

/*******************************************************************************************************************//**
 * Signals the specified RIIC block to send the stop condition.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_SendStop        (R_IIC0_Type * p_riic_reg)
{
    /* Request RIIC to issue the stop condition */
    p_riic_reg->ICCR2_b.SP = 1;

    /* Give time for value to be updated */
    volatile uint8_t dummy;
    dummy  = p_riic_reg->ICCR2;
    dummy  = p_riic_reg->ICCR2;
    dummy  = p_riic_reg->ICCR2;
    SSP_PARAMETER_NOT_USED(dummy);
}

/*******************************************************************************************************************//**
 * Signals the specified RIIC block to send the restart condition.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_SendRestart     (R_IIC0_Type * p_riic_reg)
{
    /* Request RIIC to issue the restart condition */
    p_riic_reg->ICCR2_b.RS = 1;
}

/*******************************************************************************************************************//**
 * Sets whether errors in the specified RIIC block should cause interrupts.
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   enable          True when enabling errors, otherwise disable error reporting
 * @param   irq             Pointer to IRQ for this signal, set here
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_ErrIntEn        (R_IIC0_Type * p_riic_reg, IRQn_Type irq,  bool     const   enable)
{
    if (enable)
    {
        p_riic_reg->ICIER |=  (RIIC_TMO_EN_BIT | RIIC_ALD_EN_BIT | RIIC_NAK_EN_BIT | RIIC_STR_EN_BIT | RIIC_STP_EN_BIT);

        NVIC_EnableIRQ(irq);
    }
    else
    {
        p_riic_reg->ICIER &= (uint8_t)~(RIIC_TMO_EN_BIT | RIIC_ALD_EN_BIT | RIIC_NAK_EN_BIT | RIIC_STR_EN_BIT | RIIC_STP_EN_BIT);

        NVIC_DisableIRQ(irq);
    }
}

/*******************************************************************************************************************//**
 * Sets whether receive data register becoming full should cause an interrupt from the specified RIIC block.
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   enable          True when enabling, otherwise disable
 * @param   irq             Pointer to IRQ for this signal, set here
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_RxFullIntEn     (R_IIC0_Type * p_riic_reg, IRQn_Type irq, bool     const   enable)
{
    if (enable)
    {
        p_riic_reg->ICIER |=  RIIC_RXI_EN_BIT;

        NVIC_EnableIRQ(irq);
    }
    else
    {
        p_riic_reg->ICIER &= (uint8_t)~RIIC_RXI_EN_BIT;

        NVIC_DisableIRQ(irq);
    }
}

/*******************************************************************************************************************//**
 * Sets whether transmit finishing should cause an interrupt from the specified RIIC block.
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   enable          True when enabling, otherwise disable
 * @param   irq             Pointer to IRQ for this signal, set here
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_TxEndIntEn      (R_IIC0_Type * p_riic_reg, IRQn_Type irq, bool     const   enable)
{
    if (enable)
    {
        p_riic_reg->ICIER |=  RIIC_TEI_EN_BIT;

        NVIC_EnableIRQ(irq);
    }
    else
    {
        p_riic_reg->ICIER &= (uint8_t)~RIIC_TEI_EN_BIT;

        NVIC_DisableIRQ(irq);
    }
}

/*******************************************************************************************************************//**
 * Sets whether transmit data register becoming empty should cause an interrupt from the specified RIIC block.
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   enable          True when enabling, otherwise disable
 * @param   irq             Pointer to IRQ for this signal, set here
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_TxEmptyIntEn    (R_IIC0_Type * p_riic_reg, IRQn_Type irq, bool     const   enable)
{
    if (enable)
    {
        p_riic_reg->ICIER |=  RIIC_TXI_EN_BIT;

        NVIC_EnableIRQ(irq);
    }
    else
    {
        p_riic_reg->ICIER &= (uint8_t)~RIIC_TXI_EN_BIT;

        NVIC_DisableIRQ(irq);
    }
}

/*******************************************************************************************************************//**
 * Disables all interrupt generation from the specified RIIC block.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_DisableInts     (R_IIC0_Type * p_riic_reg)
{
    p_riic_reg->ICIER = 0x00;
}

/*******************************************************************************************************************//**
 * Clears the transmit end interrupt.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_ClearTxEnd      (R_IIC0_Type * p_riic_reg)
{
    p_riic_reg->ICSR2_b.TEND = 0;

    /* Give time for value to be updated */
    volatile uint8_t dummy;
    dummy  = p_riic_reg->ICSR2_b.TEND;
    dummy  = p_riic_reg->ICSR2_b.TEND;
    dummy  = p_riic_reg->ICSR2_b.TEND;
    SSP_PARAMETER_NOT_USED(dummy);
}

/*******************************************************************************************************************//**
 * Clears all interrupts.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_ClearIrqs       (R_IIC0_Type * p_riic_reg)
{
    volatile uint8_t dummy;

    /* Perform a dummy read before clear */
    dummy  = p_riic_reg->ICSR2;
    p_riic_reg->ICSR2 = 0x00;
    SSP_PARAMETER_NOT_USED(dummy);
}

/*******************************************************************************************************************//**
 * Returns true when this channel is the master using the bus.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE bool    HW_RIIC_ActiveMaster    (R_IIC0_Type * p_riic_reg)
{
    return (1 == p_riic_reg->ICCR2_b.MST);
}

/*******************************************************************************************************************//**
 * Returns true when the SDA line is being held low.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE bool    HW_RIIC_SDALow          (R_IIC0_Type * p_riic_reg)
{
    return (0 == p_riic_reg->ICCR1_b.SDAI);
}

/*******************************************************************************************************************//**
 * Forces an extra clock cycle to be output according to the configured rate.
 *
 * @see HW_RIIC_ExtraClockDone
 *
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_ExtraClock      (R_IIC0_Type * p_riic_reg)
{
    p_riic_reg->ICCR1_b.CLO = 1;

    /* Give time for value to be updated */
    volatile uint8_t dummy;
    dummy  = p_riic_reg->ICCR1_b.CLO;
    dummy  = p_riic_reg->ICCR1_b.CLO;
    dummy  = p_riic_reg->ICCR1_b.CLO;
    SSP_PARAMETER_NOT_USED(dummy);
}

/*******************************************************************************************************************//**
 * Returns true when the extra clock cycle output has finished.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE bool    HW_RIIC_ExtraClockDone  (R_IIC0_Type * p_riic_reg)
{
    return (0 == p_riic_reg->ICCR1_b.CLO);
}

/*******************************************************************************************************************//**
 * Returns a bitfield of the errors that were recorded on the channel and then clears the hardware status.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_RIIC_GetAndClearErrsEvents (R_IIC0_Type * p_riic_reg)
{
    uint8_t errs_events = 0;

    /** Clear all the event flags except the receive data full, transmit end and transmit data empty flags*/
    if (p_riic_reg->ICSR2_b.TMOF)
    {
        errs_events |= RIIC_ERR_EVENT_TIMEOUT;
        p_riic_reg->ICSR2_b.TMOF = 0;
    }
    if (p_riic_reg->ICSR2_b.AL)
    {
        errs_events |= RIIC_ERR_EVENT_ARBITRATION_LOSS;
        p_riic_reg->ICSR2_b.AL = 0;
    }
    if (p_riic_reg->ICSR2_b.NACKF)
    {
        errs_events |= RIIC_ERR_EVENT_NACK;
        p_riic_reg->ICSR2_b.NACKF = 0;
    }
    if (p_riic_reg->ICSR2_b.START)
    {
        errs_events |= RIIC_ERR_EVENT_START;
        p_riic_reg->ICSR2_b.START = 0;
    }
    if (p_riic_reg->ICSR2_b.STOP)
    {
        errs_events |= RIIC_ERR_EVENT_STOP;
        p_riic_reg->ICSR2_b.STOP = 0;
    }

    return errs_events;
}

/*******************************************************************************************************************//**
 * Returns true when a requested stop condition has not yet been issued.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE bool    HW_RIIC_StopPending     (R_IIC0_Type * p_riic_reg)
{
    return (1 == p_riic_reg->ICCR2_b.SP);
}

/*******************************************************************************************************************//**
 * Returns true when the internal timer has timed out.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE bool    HW_RIIC_TimedOut        (R_IIC0_Type * p_riic_reg)
{
    return (1 == p_riic_reg->ICSR2_b.TMOF);
}

/*******************************************************************************************************************//**
 * Returns the number of data bits left in the current byte transfer.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE uint8_t HW_RIIC_BitsPending     (R_IIC0_Type * p_riic_reg)
{
    uint8_t bits = p_riic_reg->ICMR1_b.BC;

    if (bits == 0)
    {
        bits = 8;
    }

    return ++bits;
}

/*******************************************************************************************************************//**
 * Ensures the SDA pin is not being driven low by the peripheral.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_SDARelease      (R_IIC0_Type * p_riic_reg)
{
    /* Clear the SOWP bit and set SDAO to stop driving SDA */
    p_riic_reg->ICCR1_b.SOWP = 0;
    p_riic_reg->ICCR1_b.SDAO = 1;
    // ??? p_riic_reg->ICCR1 = (uint8_t)(p_riic_reg->ICCR1 & (uint8_t)0xEF) | (uint8_t)0x04;
}

/*******************************************************************************************************************//**
 * Sets the wait bit so the hardware knows when to perform wait processing.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_SetWait         (R_IIC0_Type * p_riic_reg)
{
    p_riic_reg->ICMR3_b.WAIT = 1;
}

/*******************************************************************************************************************//**
 * Clear the wait bit so the hardware knows when to perform wait processing.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_ClrWait         (R_IIC0_Type * p_riic_reg)
{
    p_riic_reg->ICMR3_b.WAIT = 0;
}

/*******************************************************************************************************************//**
 * Clear the stop bit before issuing the stop signal.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_ClrStop         (R_IIC0_Type * p_riic_reg)
{
    p_riic_reg->ICSR2_b.STOP = 0;
}

/*******************************************************************************************************************//**
 * Clear the STOP and NACKF bits for processing next transfer operation.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_ClrStopNackf         (R_IIC0_Type * p_riic_reg)
{
    p_riic_reg->ICSR2_b.NACKF = 0;
    p_riic_reg->ICSR2_b.STOP  = 0;
}

/*******************************************************************************************************************//**
 * Sets the acknowledge bit when getting ready to signal the slave to stop transmitting.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_SetNACKTransmission   (R_IIC0_Type * p_riic_reg)
{
    p_riic_reg->ICMR3_b.ACKWP = 1;

    /* Give time for value to be updated */
    volatile uint8_t dummy;
    dummy  = p_riic_reg->ICMR3_b.ACKWP;
    dummy  = p_riic_reg->ICMR3_b.ACKWP;
    dummy  = p_riic_reg->ICMR3_b.ACKWP;
    SSP_PARAMETER_NOT_USED(dummy);

    p_riic_reg->ICMR3_b.ACKBT = 1;
}

/*******************************************************************************************************************//**
 * Sets the acknowledge bit when getting ready to signal the slave to stop transmitting.
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void    HW_RIIC_SetACKTransmission    (R_IIC0_Type * p_riic_reg)
{
    p_riic_reg->ICMR3_b.ACKWP = 1;

    /* Give time for value to be updated */
    volatile uint8_t dummy;
    dummy  = p_riic_reg->ICMR3_b.ACKWP;
    dummy  = p_riic_reg->ICMR3_b.ACKWP;
    dummy  = p_riic_reg->ICMR3_b.ACKWP;
    SSP_PARAMETER_NOT_USED(dummy);

    p_riic_reg->ICMR3_b.ACKBT = 0;
}

/*******************************************************************************************************************//**
* @brief     This function returns the address of the write register
* @param   p_riic_reg      Base address of the hardware registers
***********************************************************************************************************************/
__STATIC_INLINE uint8_t volatile const * HW_RIIC_WriteAddrGet (R_IIC0_Type * p_riic_reg)
{
        return (uint8_t volatile const *) (&(p_riic_reg->ICDRT));
}  /* End of function HW_RIIC_WriteAddrGet() */

/*******************************************************************************************************************//**
* @brief     This function returns the address of the read register
* @param   p_riic_reg      Base address of the hardware registers
***********************************************************************************************************************/
__STATIC_INLINE uint8_t volatile const * HW_RIIC_ReadAddrGet (R_IIC0_Type * p_riic_reg)
{
        return (uint8_t volatile const *) (&(p_riic_reg->ICDRR));
}  /* End of function HW_RIIC_ReadAddrGet() */

/*******************************************************************************************************************//**
 * Enables the transmission end interrupt.
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   irq             Pointer to IRQ for this signal, set here
 **********************************************************************************************************************/
__STATIC_INLINE void HW_RIIC_EnableTENDIRQ(R_IIC0_Type * p_riic_reg, IRQn_Type irq)
{
    /* Clear any pending TEND interrupts */
    R_BSP_IrqStatusClear(irq);
    NVIC_ClearPendingIRQ(irq);

    /* Enable the TXEND interrupt */
    HW_RIIC_TxEndIntEn(p_riic_reg, irq, true);
}

/*******************************************************************************************************************//**
* @brief     This function returns the status of IIC bus
* @param   p_riic_reg      Base address of the hardware registers
***********************************************************************************************************************/
__STATIC_INLINE bool HW_RIIC_BusBusy(R_IIC0_Type * p_riic_reg)
{
    return (1U == p_riic_reg->ICCR2_b.BBSY);
}

/*******************************************************************************************************************//**
 *Set the BRCL value
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   brcl_val        bit rate counter low value to be set
 **********************************************************************************************************************/
__STATIC_INLINE void  HW_RIIC_SetICBRL      (R_IIC0_Type * p_riic_reg, uint8_t brcl_val)
{
    /* Set the number of counts that the clock remains low, bit 7 to 5 should be written as 1 */
    p_riic_reg->ICBRL = (uint8_t)(0xE0 | brcl_val);
}

/*******************************************************************************************************************//**
 *Set the BRCH value
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   brcl_val        bit rate counter low value to be set
 **********************************************************************************************************************/
__STATIC_INLINE void  HW_RIIC_SetICBRH      (R_IIC0_Type * p_riic_reg, uint8_t brch_val)
{
    /* Set the number of counts that the clock remains high, bit 7 to 5 should be written as 1 */
    p_riic_reg->ICBRH = (uint8_t)(0xE0 | brch_val);
}

/*******************************************************************************************************************//**
 * Set internal reference clock
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   clock_source    Internal reference clock source
 **********************************************************************************************************************/
__STATIC_INLINE void   HW_RIIC_SetCKS      (R_IIC0_Type * p_riic_reg, uint8_t clock_source)
{
    /* Set the internal reference clock source for generating IIC clock */
    p_riic_reg->ICMR1_b.CKS = (uint8_t)(clock_source & 0x7U);
}

/*******************************************************************************************************************//**
 * Enable/disable Master arbitration loss detection
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   enable          Enable or disable
 **********************************************************************************************************************/
__STATIC_INLINE void   HW_RIIC_EnableMALE (R_IIC0_Type * p_riic_reg, bool enable)
{
    p_riic_reg->ICFER_b.MALE = enable;
}

/*******************************************************************************************************************//**
 * Enable/disable NACK arbitration loss detection
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   enable          Enable or disable
 **********************************************************************************************************************/
__STATIC_INLINE void   HW_RIIC_EnableNALE (R_IIC0_Type * p_riic_reg, bool enable)
{
    p_riic_reg->ICFER_b.NALE = enable;
}

/*******************************************************************************************************************//**
 * Enable/disable Slave arbitration loss detection
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   enable          Enable or disable
 **********************************************************************************************************************/
__STATIC_INLINE void   HW_RIIC_EnableSALE (R_IIC0_Type * p_riic_reg, bool enable)
{
    p_riic_reg->ICFER_b.SALE = enable;
}

/*******************************************************************************************************************//**
 * Enable/disable NACK Receptions suspend
 * @param   p_riic_reg      Base address of the hardware registers
 * @param   enable          Enable or disable
 **********************************************************************************************************************/
__STATIC_INLINE void   HW_RIIC_EnableNACKE (R_IIC0_Type * p_riic_reg, bool enable)
{
    p_riic_reg->ICFER_b.NACKE = enable;
}

/*******************************************************************************************************************//**
 * Enable/disable Digital noise filter
 * @param   p_riic_reg          Base address of the hardware registers
 * @param   num_filter_stages   Number of filter stages
 **********************************************************************************************************************/
__STATIC_INLINE void   HW_RIIC_EnableNFE (R_IIC0_Type * p_riic_reg, uint8_t num_filter_stages)
{
   if (0 < num_filter_stages)
   {
       p_riic_reg->ICMR3_b.NF = ((num_filter_stages - 0x01U) & 0x03U);
       p_riic_reg->ICFER_b.NFE = 0x01U;
   }
   else
    {
       p_riic_reg->ICMR3_b.NF = 0;
       p_riic_reg->ICFER_b.NFE = 0;
    }
}

/*******************************************************************************************************************//**
 * Enable fast mode plus slope circuit
 * @param   p_riic_reg      Base address of the hardware registers
 **********************************************************************************************************************/
__STATIC_INLINE void   HW_RIIC_FMPSlopeCircuit(R_IIC0_Type * p_riic_reg, bool enable)
{
    p_riic_reg->ICFER_b.FMPE = enable;
}

/*******************************************************************************************************************//**
* This function sets the SDA output delay in the I2C Mode Register 2 (ICMR2).
* @param   p_riic_reg       Base address of the hardware registers
* @param   delay            add delay to the SDA output up to 7 cycles
***********************************************************************************************************************/
__STATIC_INLINE void   HW_RIIC_DataOutputDelay (R_IIC0_Type * p_riic_reg, uint32_t const delay)
{
    p_riic_reg->ICMR2_b.SDDL = (uint8_t)(delay & 0x07);
}

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* HW_RIIC_COMMON_H */
