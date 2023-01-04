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
 * File Name    : hw_icu_common.h
 * Description  : ICU register access functions.
 **********************************************************************************************************************/

#ifndef HW_ICU_COMMON_H
#define HW_ICU_COMMON_H

/**********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
/* Register definitions */
#include "bsp_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro Definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Prototypes
 **********************************************************************************************************************/
static inline void HW_ICU_DivisorSet (R_ICU_Type * p_icu_reg, uint8_t ch, external_irq_pclk_div_t pclk_divisor)
{
    p_icu_reg->IRQCRn_b[ch].FCLKSEL = pclk_divisor;
}

static inline uint8_t HW_ICU_DivisorGet (R_ICU_Type * p_icu_reg, uint8_t ch)
{
    return p_icu_reg->IRQCRn_b[ch].FCLKSEL;
}

static inline void HW_ICU_FilterDisable (R_ICU_Type * p_icu_reg, uint8_t ch)
{
    p_icu_reg->IRQCRn_b[ch].FLTEN = 0U;
}

static inline void HW_ICU_FilterEnable (R_ICU_Type * p_icu_reg, uint8_t ch)
{
    p_icu_reg->IRQCRn_b[ch].FLTEN = 1U;
}

static inline void HW_ICU_FilterSet(R_ICU_Type * p_icu_reg, uint8_t ch,const bool enable)
{
    p_icu_reg->IRQCRn_b[ch].FLTEN = enable;
}

static inline uint8_t HW_ICU_FilterGet (R_ICU_Type * p_icu_reg, uint8_t ch)
{
    return p_icu_reg->IRQCRn_b[ch].FLTEN;
}

static inline uint8_t HW_ICU_TriggerGet (R_ICU_Type * p_icu_reg, uint8_t ch)
{
    return p_icu_reg->IRQCRn_b[ch].IRQMD;
}

static inline void HW_ICU_TriggerSet (R_ICU_Type * p_icu_reg, uint8_t ch, external_irq_trigger_t trigger)
{
    p_icu_reg->IRQCRn_b[ch].IRQMD = trigger;
}

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* HW_GPT_COMMON_H */
