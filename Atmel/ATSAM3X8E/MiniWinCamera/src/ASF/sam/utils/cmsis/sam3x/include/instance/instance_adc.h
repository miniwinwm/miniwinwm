/**
 * \file
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef _SAM3XA_ADC_INSTANCE_
#define _SAM3XA_ADC_INSTANCE_

/* ========== Register definition for ADC peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_ADC_CR               (0x400C0000U) /**< \brief (ADC) Control Register */
#define REG_ADC_MR               (0x400C0004U) /**< \brief (ADC) Mode Register */
#define REG_ADC_SEQR1            (0x400C0008U) /**< \brief (ADC) Channel Sequence Register 1 */
#define REG_ADC_SEQR2            (0x400C000CU) /**< \brief (ADC) Channel Sequence Register 2 */
#define REG_ADC_CHER             (0x400C0010U) /**< \brief (ADC) Channel Enable Register */
#define REG_ADC_CHDR             (0x400C0014U) /**< \brief (ADC) Channel Disable Register */
#define REG_ADC_CHSR             (0x400C0018U) /**< \brief (ADC) Channel Status Register */
#define REG_ADC_LCDR             (0x400C0020U) /**< \brief (ADC) Last Converted Data Register */
#define REG_ADC_IER              (0x400C0024U) /**< \brief (ADC) Interrupt Enable Register */
#define REG_ADC_IDR              (0x400C0028U) /**< \brief (ADC) Interrupt Disable Register */
#define REG_ADC_IMR              (0x400C002CU) /**< \brief (ADC) Interrupt Mask Register */
#define REG_ADC_ISR              (0x400C0030U) /**< \brief (ADC) Interrupt Status Register */
#define REG_ADC_OVER             (0x400C003CU) /**< \brief (ADC) Overrun Status Register */
#define REG_ADC_EMR              (0x400C0040U) /**< \brief (ADC) Extended Mode Register */
#define REG_ADC_CWR              (0x400C0044U) /**< \brief (ADC) Compare Window Register */
#define REG_ADC_CGR              (0x400C0048U) /**< \brief (ADC) Channel Gain Register */
#define REG_ADC_COR              (0x400C004CU) /**< \brief (ADC) Channel Offset Register */
#define REG_ADC_CDR              (0x400C0050U) /**< \brief (ADC) Channel Data Register */
#define REG_ADC_ACR              (0x400C0094U) /**< \brief (ADC) Analog Control Register */
#define REG_ADC_WPMR             (0x400C00E4U) /**< \brief (ADC) Write Protect Mode Register */
#define REG_ADC_WPSR             (0x400C00E8U) /**< \brief (ADC) Write Protect Status Register */
#define REG_ADC_RPR              (0x400C0100U) /**< \brief (ADC) Receive Pointer Register */
#define REG_ADC_RCR              (0x400C0104U) /**< \brief (ADC) Receive Counter Register */
#define REG_ADC_RNPR             (0x400C0110U) /**< \brief (ADC) Receive Next Pointer Register */
#define REG_ADC_RNCR             (0x400C0114U) /**< \brief (ADC) Receive Next Counter Register */
#define REG_ADC_PTCR             (0x400C0120U) /**< \brief (ADC) Transfer Control Register */
#define REG_ADC_PTSR             (0x400C0124U) /**< \brief (ADC) Transfer Status Register */
#else
#define REG_ADC_CR      (*(WoReg*)0x400C0000U) /**< \brief (ADC) Control Register */
#define REG_ADC_MR      (*(RwReg*)0x400C0004U) /**< \brief (ADC) Mode Register */
#define REG_ADC_SEQR1   (*(RwReg*)0x400C0008U) /**< \brief (ADC) Channel Sequence Register 1 */
#define REG_ADC_SEQR2   (*(RwReg*)0x400C000CU) /**< \brief (ADC) Channel Sequence Register 2 */
#define REG_ADC_CHER    (*(WoReg*)0x400C0010U) /**< \brief (ADC) Channel Enable Register */
#define REG_ADC_CHDR    (*(WoReg*)0x400C0014U) /**< \brief (ADC) Channel Disable Register */
#define REG_ADC_CHSR    (*(RoReg*)0x400C0018U) /**< \brief (ADC) Channel Status Register */
#define REG_ADC_LCDR    (*(RoReg*)0x400C0020U) /**< \brief (ADC) Last Converted Data Register */
#define REG_ADC_IER     (*(WoReg*)0x400C0024U) /**< \brief (ADC) Interrupt Enable Register */
#define REG_ADC_IDR     (*(WoReg*)0x400C0028U) /**< \brief (ADC) Interrupt Disable Register */
#define REG_ADC_IMR     (*(RoReg*)0x400C002CU) /**< \brief (ADC) Interrupt Mask Register */
#define REG_ADC_ISR     (*(RoReg*)0x400C0030U) /**< \brief (ADC) Interrupt Status Register */
#define REG_ADC_OVER    (*(RoReg*)0x400C003CU) /**< \brief (ADC) Overrun Status Register */
#define REG_ADC_EMR     (*(RwReg*)0x400C0040U) /**< \brief (ADC) Extended Mode Register */
#define REG_ADC_CWR     (*(RwReg*)0x400C0044U) /**< \brief (ADC) Compare Window Register */
#define REG_ADC_CGR     (*(RwReg*)0x400C0048U) /**< \brief (ADC) Channel Gain Register */
#define REG_ADC_COR     (*(RwReg*)0x400C004CU) /**< \brief (ADC) Channel Offset Register */
#define REG_ADC_CDR     (*(RoReg*)0x400C0050U) /**< \brief (ADC) Channel Data Register */
#define REG_ADC_ACR     (*(RwReg*)0x400C0094U) /**< \brief (ADC) Analog Control Register */
#define REG_ADC_WPMR    (*(RwReg*)0x400C00E4U) /**< \brief (ADC) Write Protect Mode Register */
#define REG_ADC_WPSR    (*(RoReg*)0x400C00E8U) /**< \brief (ADC) Write Protect Status Register */
#define REG_ADC_RPR     (*(RwReg*)0x400C0100U) /**< \brief (ADC) Receive Pointer Register */
#define REG_ADC_RCR     (*(RwReg*)0x400C0104U) /**< \brief (ADC) Receive Counter Register */
#define REG_ADC_RNPR    (*(RwReg*)0x400C0110U) /**< \brief (ADC) Receive Next Pointer Register */
#define REG_ADC_RNCR    (*(RwReg*)0x400C0114U) /**< \brief (ADC) Receive Next Counter Register */
#define REG_ADC_PTCR    (*(WoReg*)0x400C0120U) /**< \brief (ADC) Transfer Control Register */
#define REG_ADC_PTSR    (*(RoReg*)0x400C0124U) /**< \brief (ADC) Transfer Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM3XA_ADC_INSTANCE_ */
