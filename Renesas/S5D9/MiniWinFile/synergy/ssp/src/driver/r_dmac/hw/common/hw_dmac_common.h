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
 * File Name    : hw_dmac_common.h
 * Description  : DMAC register access functions
 **********************************************************************************************************************/

#ifndef HW_DMAC_COMMON_H
#define HW_DMAC_COMMON_H

/**********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"



/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/


/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private Functions
 **********************************************************************************************************************/

__STATIC_INLINE void HW_DMAC_TransferEnableDisable (R_DMAC0_Type * p_dmac_regs, dmac_transfer_enable_t enable_disable)
{
    p_dmac_regs->DMCNT_b.DTE = enable_disable;
}

__STATIC_INLINE elc_event_t HW_ICU_DmacEventGet (R_ICU_Type * p_icu_regs, IRQn_Type irq)
{
    return (elc_event_t) p_icu_regs->IELSRn_b[irq].IELS;
}

__STATIC_INLINE void HW_ICU_DmacEnable (R_ICU_Type * p_icu_regs, uint8_t ch, elc_event_t event)
{
    p_icu_regs->DELSRn[ch].DELSRn_b.DELS = event;
}

__STATIC_INLINE elc_event_t HW_ICU_DmacEnableGet (R_ICU_Type * p_icu_regs, uint8_t ch)
{
    return (elc_event_t) p_icu_regs->DELSRn[ch].DELSRn_b.DELS;
}

__STATIC_INLINE void HW_DMAC_DestAddrUpdateModeSet (R_DMAC0_Type * p_dmac_regs, transfer_addr_mode_t mode)
{
    p_dmac_regs->DMAMD_b.DM = mode;
}

__STATIC_INLINE void HW_DMAC_SrcAddrUpdateModeSet (R_DMAC0_Type * p_dmac_regs, transfer_addr_mode_t mode)
{
    p_dmac_regs->DMAMD_b.SM = mode;
}

__STATIC_INLINE void HW_DMAC_DestExtendedRepeatAreaSet (R_DMAC0_Type * p_dmac_regs, dmac_extended_repeat_area_t size)
{
    p_dmac_regs->DMAMD_b.DARA = size;
}

__STATIC_INLINE void HW_DMAC_SrcExtendedRepeatAreaSet (R_DMAC0_Type * p_dmac_regs, dmac_extended_repeat_area_t size)
{
    p_dmac_regs->DMAMD_b.SARA = size;
}

__STATIC_INLINE void HW_DMAC_TransferRequestSourceSet (R_DMAC0_Type * p_dmac_regs, dmac_transfer_request_source_t src)
{
    p_dmac_regs->DMTMD_b.DCTG = src;
}

__STATIC_INLINE void HW_DMAC_TransferSizeSet (R_DMAC0_Type * p_dmac_regs, transfer_size_t size)
{
    p_dmac_regs->DMTMD_b.SZ = size;
}

__STATIC_INLINE transfer_size_t HW_DMAC_TransferSizeGet (R_DMAC0_Type * p_dmac_regs)
{
    return (transfer_size_t) p_dmac_regs->DMTMD_b.SZ;
}

__STATIC_INLINE void HW_DMAC_RepeatAreaSet (R_DMAC0_Type * p_dmac_regs, transfer_repeat_area_t repeat_area)
{
    p_dmac_regs->DMTMD_b.DTS = repeat_area;
}

__STATIC_INLINE void HW_DMAC_ModeSet (R_DMAC0_Type * p_dmac_regs, transfer_mode_t mode)
{
    p_dmac_regs->DMTMD_b.MD = mode;
}

__STATIC_INLINE transfer_mode_t HW_DMAC_ModeGet (R_DMAC0_Type * p_dmac_regs)
{
    return (transfer_mode_t) p_dmac_regs->DMTMD_b.MD;
}

__STATIC_INLINE void HW_DMAC_SrcStartAddrSet (R_DMAC0_Type * p_dmac_regs, void const * volatile p_src)
{
    /* This is the source start address pointer, but it is represented by a uint32_t in the iodefine file.
     * Casting it to uint32_t. */
    p_dmac_regs->DMSAR = (uint32_t) p_src;
}

__STATIC_INLINE void const * HW_DMAC_SrcStartAddrGet (R_DMAC0_Type * p_dmac_regs)
{
    /* This is the source start address pointer, but it is represented by a uint32_t in the iodefine file.
     * Casting it to pointer. */
    return (void const *) p_dmac_regs->DMSAR;
}

__STATIC_INLINE void HW_DMAC_DestStartAddrSet (R_DMAC0_Type * p_dmac_regs, void * volatile p_dest)
{
    /* This is the destination start address pointer, but it is represented by a uint32_t in the iodefine file.
     * Casting it to uint32_t. */
    p_dmac_regs->DMDAR = (uint32_t) p_dest;
}

__STATIC_INLINE void const * HW_DMAC_DestStartAddrGet (R_DMAC0_Type * p_dmac_regs)
{
    /* This is the destination start address pointer, but it is represented by a uint32_t in the iodefine file.
     * Casting it to pointer. */
    return (void const *) p_dmac_regs->DMDAR;
}

__STATIC_INLINE void HW_DMAC_TransferNumberSet (R_DMAC0_Type * p_dmac_regs, uint16_t length)
{
    p_dmac_regs->DMCRA_b.DMCRAL = length;
}

__STATIC_INLINE uint16_t HW_DMAC_TransferNumberGet (R_DMAC0_Type * p_dmac_regs)
{
    return (uint16_t) (p_dmac_regs->DMCRA_b.DMCRAL);
}

__STATIC_INLINE void HW_DMAC_TransferReloadSet (R_DMAC0_Type * p_dmac_regs, uint16_t length)
{
    /* Note: There is a warning here for GCC that will go away if length is cast to uint8_t.  The length parameter
     * is set into a 10 bit bitfield (DMCRAH), and casting to uint8_t will result in a change of value.  For this
     * reason, the warning is explicitly ignored in this case.
     */
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wconversion"
#endif
    p_dmac_regs->DMCRA_b.DMCRAH = length;
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
}

__STATIC_INLINE void HW_DMAC_BlockNumberSet (R_DMAC0_Type * p_dmac_regs, uint16_t num_blocks)
{
    p_dmac_regs->DMCRB = num_blocks;
}

__STATIC_INLINE uint16_t HW_DMAC_BlockNumberGet (R_DMAC0_Type * p_dmac_regs)
{
    return (p_dmac_regs->DMCRB);
}

__STATIC_INLINE void HW_DMAC_TransferEndInterruptClear (R_DMAC0_Type * p_dmac_regs)
{
    p_dmac_regs->DMSTS_b.DTIF = 0U;
}

/*******************************************************************************************************************//**
 * Clears interrupts for specified channel at ICU.
 * @param  irq_num       The channel corresponds to the hardware channel number.
 **********************************************************************************************************************/
__STATIC_INLINE void HW_DMAC_ICUInterruptClear (IRQn_Type irq_num)
{
    R_ICU->IELSRn_b[irq_num].IR = 0U;
}

__STATIC_INLINE void HW_DMAC_TransferEndInterruptEnable (R_DMAC0_Type * p_dmac_regs)
{
    p_dmac_regs->DMINT_b.DTIE = 1U;
}

__STATIC_INLINE void HW_DMAC_EachInterruptEnable (R_DMAC0_Type * p_dmac_regs, transfer_irq_t irq)
{
    p_dmac_regs->DMINT_b.RPTIE = irq;
    p_dmac_regs->DMINT_b.ESIE = irq;
}

__STATIC_INLINE void HW_DMAC_TransferEndInterruptDisable (R_DMAC0_Type * p_dmac_regs)
{
    p_dmac_regs->DMINT_b.DTIE = 0U;
}

__STATIC_INLINE void HW_DMAC_SoftwareStart (R_DMAC0_Type * p_dmac_regs)
{
    p_dmac_regs->DMREQ_b.SWREQ = 1U;
}

__STATIC_INLINE void HW_DMAC_SoftwareStop (R_DMAC0_Type * p_dmac_regs)
{
    p_dmac_regs->DMREQ_b.SWREQ = 0U;
}

__STATIC_INLINE void HW_DMAC_SoftwareStartAutoClear (R_DMAC0_Type * p_dmac_regs, transfer_start_mode_t autoclear)
{
    p_dmac_regs->DMREQ_b.CLRS = autoclear;
}

__STATIC_INLINE bool HW_DMAC_StatusGet (R_DMAC0_Type * p_dmac_regs)
{
    return (bool) (p_dmac_regs->DMSTS_b.ACT & 1U);
}

__STATIC_INLINE void HW_DMAC_Enable (R_DMA_Type * p_dma_regs)
{
    SSP_PARAMETER_NOT_USED(p_dma_regs);
    R_DMA->DMAST_b.DMST = 1U;
}

__STATIC_INLINE void HW_ICU_DmacClear (R_ICU_Type * p_icu_regs, uint8_t ch)
{
    p_icu_regs->DELSRn[ch].DELSRn_b.IR = 0U;
}

/** Sets the user provided offset value in DMOFR register. */
__STATIC_INLINE void HW_DMAC_OffsetSet (R_DMAC0_Type * p_dmac_regs, int32_t offset_in_byte)
{
    if(offset_in_byte < 0)
    {
        /** 2's complement of offset value with maximum allowed value. Masking bits [31:25] of DMOFR register
         * as per hardware specification.*/
        p_dmac_regs->DMOFR = (uint32_t) (((~((-1L) * (offset_in_byte))) + 1L) & 0x01FFFFFF);
    }
    else
    {
        p_dmac_regs->DMOFR = (uint32_t) (offset_in_byte);
    }
}
/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* HW_DMAC_COMMON_H */
