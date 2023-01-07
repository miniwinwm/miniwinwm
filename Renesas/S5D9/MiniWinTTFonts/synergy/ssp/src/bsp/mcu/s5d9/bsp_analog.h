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
/***********************************************************************************************************************
* File Name    : bsp_analog.h
* Description  : Analog pin connections available on this MCU.
***********************************************************************************************************************/

#ifndef BSP_ANALOG_H_
#define BSP_ANALOG_H_

/*******************************************************************************************************************//**
 * @ingroup BSP_MCU_S5D9
 * @defgroup BSP_MCU_ANALOG_S5D9 Analog Connections
 *
 * This group contains a list of enumerations that can be used with the @ref ANALOG_CONNECT_API.
 *
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "../all/bsp_common_analog.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
/** List of analog connections that can be made on S5D9
 * @note This list may change based on device. This list is for S5D9.
 * */
typedef enum e_analog_connect
{
    /* Connections for ACMPHS channel 0 VCMP input. */
    /* AN017 = P502 */
    /** Connect ACMPHS0 IVCMP to PORT5 P502. */
    ANALOG_CONNECT_ACMPHS0_IVCMP_TO_PORT5_P502      = ANALOG_CONNECT_DEFINE(ACMPHS, 0, CMPSEL0, IVCMP0, FLAG_CLEAR),
    /** Connect ACMPHS0 IVCMP to DAC121 DA. */
    ANALOG_CONNECT_ACMPHS0_IVCMP_TO_DAC121_DA       = ANALOG_CONNECT_DEFINE(ACMPHS, 0, CMPSEL0, IVCMP1, FLAG_CLEAR),
    /* AN000 = P000 */
    /** Connect ACMPHS0 IVCMP to PORT0 P000. */
    ANALOG_CONNECT_ACMPHS0_IVCMP_TO_PORT0_P000      = ANALOG_CONNECT_DEFINE(ACMPHS, 0, CMPSEL0, IVCMP2, FLAG_CLEAR),
    /** Connect ACMPHS0 IVCMP to ADC0 PGA0. */
    ANALOG_CONNECT_ACMPHS0_IVCMP_TO_ADC0_PGA0       = ANALOG_CONNECT_DEFINE(ACMPHS, 0, CMPSEL0, IVCMP3, FLAG_CLEAR),

    /* Connections for ACMPHS channel 0 VREF input. */
    /* AN016 = P500 */
    /** Connect ACMPHS0 IVREF to PORT5 P500. */
    ANALOG_CONNECT_ACMPHS0_IVREF_TO_PORT5_P500      = ANALOG_CONNECT_DEFINE(ACMPHS, 0, CMPSEL1, IVREF0, FLAG_CLEAR),
    /* AN116 = P501 */
    /** Connect ACMPHS0 IVREF to PORT5 P501. */
    ANALOG_CONNECT_ACMPHS0_IVREF_TO_PORT5_P501      = ANALOG_CONNECT_DEFINE(ACMPHS, 0, CMPSEL1, IVREF1, FLAG_CLEAR),
    /* ANALOG0_VREF is the internal reference voltage. */
    /** Connect ACMPHS0 IVREF to ANALOG0 VREF. */
    ANALOG_CONNECT_ACMPHS0_IVREF_TO_ANALOG0_VREF    = ANALOG_CONNECT_DEFINE(ACMPHS, 0, CMPSEL1, IVREF2, FLAG_SET),
    /** Connect ACMPHS0 IVREF to DAC120 DA. */
    ANALOG_CONNECT_ACMPHS0_IVREF_TO_DAC120_DA       = ANALOG_CONNECT_DEFINE(ACMPHS, 0, CMPSEL1, IVREF3, FLAG_CLEAR),

    /* Connections for ACMPHS channel 1 VCMP input. */
    /* AN017 = P502 */
    /** Connect ACMPHS1 IVCMP to PORT5 P502. */
    ANALOG_CONNECT_ACMPHS1_IVCMP_TO_PORT5_P502      = ANALOG_CONNECT_DEFINE(ACMPHS, 1, CMPSEL0, IVCMP0, FLAG_CLEAR),
    /** Connect ACMPHS1 IVCMP to DAC121 DA. */
    ANALOG_CONNECT_ACMPHS1_IVCMP_TO_DAC121_DA       = ANALOG_CONNECT_DEFINE(ACMPHS, 1, CMPSEL0, IVCMP1, FLAG_CLEAR),
    /* AN001 = P001 */
    /** Connect ACMPHS1 IVCMP to PORT0 P001. */
    ANALOG_CONNECT_ACMPHS1_IVCMP_TO_PORT0_P001      = ANALOG_CONNECT_DEFINE(ACMPHS, 1, CMPSEL0, IVCMP2, FLAG_CLEAR),
    /** Connect ACMPHS1 IVCMP to ADC0 PGA1. */
    ANALOG_CONNECT_ACMPHS1_IVCMP_TO_ADC0_PGA1       = ANALOG_CONNECT_DEFINE(ACMPHS, 1, CMPSEL0, IVCMP3, FLAG_CLEAR),

    /* Connections for ACMPHS channel 1 VREF input. */
    /* AN016 = P500 */
    /** Connect ACMPHS1 IVREF to PORT5 P500. */
    ANALOG_CONNECT_ACMPHS1_IVREF_TO_PORT5_P500      = ANALOG_CONNECT_DEFINE(ACMPHS, 1, CMPSEL1, IVREF0, FLAG_CLEAR),
    /* AN116 = P501 */
    /** Connect ACMPHS1 IVREF to PORT5 P501. */
    ANALOG_CONNECT_ACMPHS1_IVREF_TO_PORT5_P501      = ANALOG_CONNECT_DEFINE(ACMPHS, 1, CMPSEL1, IVREF1, FLAG_CLEAR),
    /* ANALOG0_VREF is the internal reference voltage. */
    /** Connect ACMPHS1 IVREF to ANALOG0 VREF. */
    ANALOG_CONNECT_ACMPHS1_IVREF_TO_ANALOG0_VREF    = ANALOG_CONNECT_DEFINE(ACMPHS, 1, CMPSEL1, IVREF2, FLAG_SET),
    /** Connect ACMPHS1 IVREF to DAC120 DA. */
    ANALOG_CONNECT_ACMPHS1_IVREF_TO_DAC120_DA       = ANALOG_CONNECT_DEFINE(ACMPHS, 1, CMPSEL1, IVREF3, FLAG_CLEAR),

    /* Connections for ACMPHS channel 2 VCMP input. */
    /* AN017 = P502 */
    /** Connect ACMPHS2 IVCMP to PORT5 P502. */
    ANALOG_CONNECT_ACMPHS2_IVCMP_TO_PORT5_P502      = ANALOG_CONNECT_DEFINE(ACMPHS, 2, CMPSEL0, IVCMP0, FLAG_CLEAR),
    /** Connect ACMPHS2 IVCMP to DAC121 DA. */
    ANALOG_CONNECT_ACMPHS2_IVCMP_TO_DAC121_DA       = ANALOG_CONNECT_DEFINE(ACMPHS, 2, CMPSEL0, IVCMP1, FLAG_CLEAR),
    /* AN002 = P002 */
    /** Connect ACMPHS2 IVCMP to PORT0 P002. */
    ANALOG_CONNECT_ACMPHS2_IVCMP_TO_PORT0_P002      = ANALOG_CONNECT_DEFINE(ACMPHS, 2, CMPSEL0, IVCMP2, FLAG_CLEAR),
    /** Connect ACMPHS2 IVCMP to ADC0 PGA2. */
    ANALOG_CONNECT_ACMPHS2_IVCMP_TO_ADC0_PGA2       = ANALOG_CONNECT_DEFINE(ACMPHS, 2, CMPSEL0, IVCMP3, FLAG_CLEAR),

    /* Connections for ACMPHS channel 2 VREF input. */
    /* AN016 = P500 */
    /** Connect ACMPHS2 IVREF to PORT5 P500. */
    ANALOG_CONNECT_ACMPHS2_IVREF_TO_PORT5_P500      = ANALOG_CONNECT_DEFINE(ACMPHS, 2, CMPSEL1, IVREF0, FLAG_CLEAR),
    /* AN116 = P501 */
    /** Connect ACMPHS2 IVREF to PORT5 P501. */
    ANALOG_CONNECT_ACMPHS2_IVREF_TO_PORT5_P501      = ANALOG_CONNECT_DEFINE(ACMPHS, 2, CMPSEL1, IVREF1, FLAG_CLEAR),
    /* ANALOG0_VREF is the internal reference voltage. */
    /** Connect ACMPHS2 IVREF to ANALOG0 VREF. */
    ANALOG_CONNECT_ACMPHS2_IVREF_TO_ANALOG0_VREF    = ANALOG_CONNECT_DEFINE(ACMPHS, 2, CMPSEL1, IVREF2, FLAG_SET),
    /** Connect ACMPHS2 IVREF to DAC120 DA. */
    ANALOG_CONNECT_ACMPHS2_IVREF_TO_DAC120_DA       = ANALOG_CONNECT_DEFINE(ACMPHS, 2, CMPSEL1, IVREF3, FLAG_CLEAR),

    /* Connections for ACMPHS channel 3 VCMP input. */
    /* AN017 = P502 */
    /** Connect ACMPHS3 IVCMP to PORT5 P502. */
    ANALOG_CONNECT_ACMPHS3_IVCMP_TO_PORT5_P502      = ANALOG_CONNECT_DEFINE(ACMPHS, 3, CMPSEL0, IVCMP0, FLAG_CLEAR),
    /** Connect ACMPHS3 IVCMP to DAC121 DA. */
    ANALOG_CONNECT_ACMPHS3_IVCMP_TO_DAC121_DA       = ANALOG_CONNECT_DEFINE(ACMPHS, 3, CMPSEL0, IVCMP1, FLAG_CLEAR),
    /* AN100 = P004 */
    /** Connect ACMPHS3 IVCMP to PORT0 P004. */
    ANALOG_CONNECT_ACMPHS3_IVCMP_TO_PORT0_P004      = ANALOG_CONNECT_DEFINE(ACMPHS, 3, CMPSEL0, IVCMP2, FLAG_CLEAR),
    /** Connect ACMPHS3 IVCMP to ADC1 PGA3. */
    ANALOG_CONNECT_ACMPHS3_IVCMP_TO_ADC1_PGA3       = ANALOG_CONNECT_DEFINE(ACMPHS, 3, CMPSEL0, IVCMP3, FLAG_CLEAR),

    /* Connections for ACMPHS channel 3 VREF input. */
    /* AN016 = P500 */
    /** Connect ACMPHS3 IVREF to PORT5 P500. */
    ANALOG_CONNECT_ACMPHS3_IVREF_TO_PORT5_P500      = ANALOG_CONNECT_DEFINE(ACMPHS, 3, CMPSEL1, IVREF0, FLAG_CLEAR),
    /* AN116 = P501 */
    /** Connect ACMPHS3 IVREF to PORT5 P501. */
    ANALOG_CONNECT_ACMPHS3_IVREF_TO_PORT5_P501      = ANALOG_CONNECT_DEFINE(ACMPHS, 3, CMPSEL1, IVREF1, FLAG_CLEAR),
    /* ANALOG0_VREF is the internal reference voltage. */
    /** Connect ACMPHS3 IVREF to ANALOG0 VREF. */
    ANALOG_CONNECT_ACMPHS3_IVREF_TO_ANALOG0_VREF    = ANALOG_CONNECT_DEFINE(ACMPHS, 3, CMPSEL1, IVREF2, FLAG_SET),
    /** Connect ACMPHS3 IVREF to DAC120 DA. */
    ANALOG_CONNECT_ACMPHS3_IVREF_TO_DAC120_DA       = ANALOG_CONNECT_DEFINE(ACMPHS, 3, CMPSEL1, IVREF3, FLAG_CLEAR),

    /* Connections for ACMPHS channel 4 VCMP input. */
    /* AN017 = P502 */
    /** Connect ACMPHS4 IVCMP to PORT5 P502. */
    ANALOG_CONNECT_ACMPHS4_IVCMP_TO_PORT5_P502      = ANALOG_CONNECT_DEFINE(ACMPHS, 4, CMPSEL0, IVCMP0, FLAG_CLEAR),
    /** Connect ACMPHS4 IVCMP to DAC121 DA. */
    ANALOG_CONNECT_ACMPHS4_IVCMP_TO_DAC121_DA       = ANALOG_CONNECT_DEFINE(ACMPHS, 4, CMPSEL0, IVCMP1, FLAG_CLEAR),
    /* AN101 = P005 */
    /** Connect ACMPHS4 IVCMP to PORT0 P005. */
    ANALOG_CONNECT_ACMPHS4_IVCMP_TO_PORT0_P005      = ANALOG_CONNECT_DEFINE(ACMPHS, 4, CMPSEL0, IVCMP2, FLAG_CLEAR),
    /** Connect ACMPHS4 IVCMP to ADC1 PGA4. */
    ANALOG_CONNECT_ACMPHS4_IVCMP_TO_ADC1_PGA4       = ANALOG_CONNECT_DEFINE(ACMPHS, 4, CMPSEL0, IVCMP3, FLAG_CLEAR),

    /* Connections for ACMPHS channel 4 VREF input. */
    /* AN016 = P500 */
    /** Connect ACMPHS4 IVREF to PORT5 P500. */
    ANALOG_CONNECT_ACMPHS4_IVREF_TO_PORT5_P500      = ANALOG_CONNECT_DEFINE(ACMPHS, 4, CMPSEL1, IVREF0, FLAG_CLEAR),
    /* AN116 = P501 */
    /** Connect ACMPHS4 IVREF to PORT5 P501. */
    ANALOG_CONNECT_ACMPHS4_IVREF_TO_PORT5_P501      = ANALOG_CONNECT_DEFINE(ACMPHS, 4, CMPSEL1, IVREF1, FLAG_CLEAR),
    /* ANALOG0_VREF is the internal reference voltage. */
    /** Connect ACMPHS4 IVREF to ANALOG0 VREF. */
    ANALOG_CONNECT_ACMPHS4_IVREF_TO_ANALOG0_VREF    = ANALOG_CONNECT_DEFINE(ACMPHS, 4, CMPSEL1, IVREF2, FLAG_SET),
    /** Connect ACMPHS4 IVREF to DAC120 DA. */
    ANALOG_CONNECT_ACMPHS4_IVREF_TO_DAC120_DA       = ANALOG_CONNECT_DEFINE(ACMPHS, 4, CMPSEL1, IVREF3, FLAG_CLEAR),

    /* Connections for ACMPHS channel 5 VCMP input. */
    /* AN017 = P502 */
    /** Connect ACMPHS5 IVCMP to PORT5 P502. */
    ANALOG_CONNECT_ACMPHS5_IVCMP_TO_PORT5_P502      = ANALOG_CONNECT_DEFINE(ACMPHS, 5, CMPSEL0, IVCMP0, FLAG_CLEAR),
    /** Connect ACMPHS5 IVCMP to DAC121 DA. */
    ANALOG_CONNECT_ACMPHS5_IVCMP_TO_DAC121_DA       = ANALOG_CONNECT_DEFINE(ACMPHS, 5, CMPSEL0, IVCMP1, FLAG_CLEAR),
    /* AN102 = P006 */
    /** Connect ACMPHS5 IVCMP to PORT0 P006. */
    ANALOG_CONNECT_ACMPHS5_IVCMP_TO_PORT0_P006      = ANALOG_CONNECT_DEFINE(ACMPHS, 5, CMPSEL0, IVCMP2, FLAG_CLEAR),
    /** Connect ACMPHS5 IVCMP to ADC1 PGA5. */
    ANALOG_CONNECT_ACMPHS5_IVCMP_TO_ADC1_PGA5       = ANALOG_CONNECT_DEFINE(ACMPHS, 5, CMPSEL0, IVCMP3, FLAG_CLEAR),

    /* Connections for ACMPHS channel 5 VREF input. */
    /* AN016 = P500 */
    /** Connect ACMPHS5 IVREF to PORT5 P500. */
    ANALOG_CONNECT_ACMPHS5_IVREF_TO_PORT5_P500      = ANALOG_CONNECT_DEFINE(ACMPHS, 5, CMPSEL1, IVREF0, FLAG_CLEAR),
    /* AN116 = P501 */
    /** Connect ACMPHS5 IVREF to PORT5 P501. */
    ANALOG_CONNECT_ACMPHS5_IVREF_TO_PORT5_P501      = ANALOG_CONNECT_DEFINE(ACMPHS, 5, CMPSEL1, IVREF1, FLAG_CLEAR),
    /* ANALOG0_VREF is the internal reference voltage. */
    /** Connect ACMPHS5 IVREF to ANALOG0 VREF. */
    ANALOG_CONNECT_ACMPHS5_IVREF_TO_ANALOG0_VREF    = ANALOG_CONNECT_DEFINE(ACMPHS, 5, CMPSEL1, IVREF2, FLAG_SET),
    /** Connect ACMPHS5 IVREF to DAC120 DA. */
    ANALOG_CONNECT_ACMPHS5_IVREF_TO_DAC120_DA       = ANALOG_CONNECT_DEFINE(ACMPHS, 5, CMPSEL1, IVREF3, FLAG_CLEAR),

} analog_connect_t;

/** @} (end defgroup BSP_MCU_ANALOG_S5D9) */

#endif /* BSP_ANALOG_H_ */
