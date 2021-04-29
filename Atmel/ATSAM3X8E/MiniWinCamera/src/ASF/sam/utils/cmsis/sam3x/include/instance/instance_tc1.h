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

#ifndef _SAM3XA_TC1_INSTANCE_
#define _SAM3XA_TC1_INSTANCE_

/* ========== Register definition for TC1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_TC1_CCR0           (0x40084000U) /**< \brief (TC1) Channel Control Register (channel = 0) */
#define REG_TC1_CMR0           (0x40084004U) /**< \brief (TC1) Channel Mode Register (channel = 0) */
#define REG_TC1_SMMR0          (0x40084008U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 0) */
#define REG_TC1_CV0            (0x40084010U) /**< \brief (TC1) Counter Value (channel = 0) */
#define REG_TC1_RA0            (0x40084014U) /**< \brief (TC1) Register A (channel = 0) */
#define REG_TC1_RB0            (0x40084018U) /**< \brief (TC1) Register B (channel = 0) */
#define REG_TC1_RC0            (0x4008401CU) /**< \brief (TC1) Register C (channel = 0) */
#define REG_TC1_SR0            (0x40084020U) /**< \brief (TC1) Status Register (channel = 0) */
#define REG_TC1_IER0           (0x40084024U) /**< \brief (TC1) Interrupt Enable Register (channel = 0) */
#define REG_TC1_IDR0           (0x40084028U) /**< \brief (TC1) Interrupt Disable Register (channel = 0) */
#define REG_TC1_IMR0           (0x4008402CU) /**< \brief (TC1) Interrupt Mask Register (channel = 0) */
#define REG_TC1_CCR1           (0x40084040U) /**< \brief (TC1) Channel Control Register (channel = 1) */
#define REG_TC1_CMR1           (0x40084044U) /**< \brief (TC1) Channel Mode Register (channel = 1) */
#define REG_TC1_SMMR1          (0x40084048U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 1) */
#define REG_TC1_CV1            (0x40084050U) /**< \brief (TC1) Counter Value (channel = 1) */
#define REG_TC1_RA1            (0x40084054U) /**< \brief (TC1) Register A (channel = 1) */
#define REG_TC1_RB1            (0x40084058U) /**< \brief (TC1) Register B (channel = 1) */
#define REG_TC1_RC1            (0x4008405CU) /**< \brief (TC1) Register C (channel = 1) */
#define REG_TC1_SR1            (0x40084060U) /**< \brief (TC1) Status Register (channel = 1) */
#define REG_TC1_IER1           (0x40084064U) /**< \brief (TC1) Interrupt Enable Register (channel = 1) */
#define REG_TC1_IDR1           (0x40084068U) /**< \brief (TC1) Interrupt Disable Register (channel = 1) */
#define REG_TC1_IMR1           (0x4008406CU) /**< \brief (TC1) Interrupt Mask Register (channel = 1) */
#define REG_TC1_CCR2           (0x40084080U) /**< \brief (TC1) Channel Control Register (channel = 2) */
#define REG_TC1_CMR2           (0x40084084U) /**< \brief (TC1) Channel Mode Register (channel = 2) */
#define REG_TC1_SMMR2          (0x40084088U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 2) */
#define REG_TC1_CV2            (0x40084090U) /**< \brief (TC1) Counter Value (channel = 2) */
#define REG_TC1_RA2            (0x40084094U) /**< \brief (TC1) Register A (channel = 2) */
#define REG_TC1_RB2            (0x40084098U) /**< \brief (TC1) Register B (channel = 2) */
#define REG_TC1_RC2            (0x4008409CU) /**< \brief (TC1) Register C (channel = 2) */
#define REG_TC1_SR2            (0x400840A0U) /**< \brief (TC1) Status Register (channel = 2) */
#define REG_TC1_IER2           (0x400840A4U) /**< \brief (TC1) Interrupt Enable Register (channel = 2) */
#define REG_TC1_IDR2           (0x400840A8U) /**< \brief (TC1) Interrupt Disable Register (channel = 2) */
#define REG_TC1_IMR2           (0x400840ACU) /**< \brief (TC1) Interrupt Mask Register (channel = 2) */
#define REG_TC1_BCR            (0x400840C0U) /**< \brief (TC1) Block Control Register */
#define REG_TC1_BMR            (0x400840C4U) /**< \brief (TC1) Block Mode Register */
#define REG_TC1_QIER           (0x400840C8U) /**< \brief (TC1) QDEC Interrupt Enable Register */
#define REG_TC1_QIDR           (0x400840CCU) /**< \brief (TC1) QDEC Interrupt Disable Register */
#define REG_TC1_QIMR           (0x400840D0U) /**< \brief (TC1) QDEC Interrupt Mask Register */
#define REG_TC1_QISR           (0x400840D4U) /**< \brief (TC1) QDEC Interrupt Status Register */
#define REG_TC1_FMR            (0x400840D8U) /**< \brief (TC1) Fault Mode Register */
#define REG_TC1_WPMR           (0x400840E4U) /**< \brief (TC1) Write Protect Mode Register */
#else
#define REG_TC1_CCR0  (*(WoReg*)0x40084000U) /**< \brief (TC1) Channel Control Register (channel = 0) */
#define REG_TC1_CMR0  (*(RwReg*)0x40084004U) /**< \brief (TC1) Channel Mode Register (channel = 0) */
#define REG_TC1_SMMR0 (*(RwReg*)0x40084008U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 0) */
#define REG_TC1_CV0   (*(RoReg*)0x40084010U) /**< \brief (TC1) Counter Value (channel = 0) */
#define REG_TC1_RA0   (*(RwReg*)0x40084014U) /**< \brief (TC1) Register A (channel = 0) */
#define REG_TC1_RB0   (*(RwReg*)0x40084018U) /**< \brief (TC1) Register B (channel = 0) */
#define REG_TC1_RC0   (*(RwReg*)0x4008401CU) /**< \brief (TC1) Register C (channel = 0) */
#define REG_TC1_SR0   (*(RoReg*)0x40084020U) /**< \brief (TC1) Status Register (channel = 0) */
#define REG_TC1_IER0  (*(WoReg*)0x40084024U) /**< \brief (TC1) Interrupt Enable Register (channel = 0) */
#define REG_TC1_IDR0  (*(WoReg*)0x40084028U) /**< \brief (TC1) Interrupt Disable Register (channel = 0) */
#define REG_TC1_IMR0  (*(RoReg*)0x4008402CU) /**< \brief (TC1) Interrupt Mask Register (channel = 0) */
#define REG_TC1_CCR1  (*(WoReg*)0x40084040U) /**< \brief (TC1) Channel Control Register (channel = 1) */
#define REG_TC1_CMR1  (*(RwReg*)0x40084044U) /**< \brief (TC1) Channel Mode Register (channel = 1) */
#define REG_TC1_SMMR1 (*(RwReg*)0x40084048U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 1) */
#define REG_TC1_CV1   (*(RoReg*)0x40084050U) /**< \brief (TC1) Counter Value (channel = 1) */
#define REG_TC1_RA1   (*(RwReg*)0x40084054U) /**< \brief (TC1) Register A (channel = 1) */
#define REG_TC1_RB1   (*(RwReg*)0x40084058U) /**< \brief (TC1) Register B (channel = 1) */
#define REG_TC1_RC1   (*(RwReg*)0x4008405CU) /**< \brief (TC1) Register C (channel = 1) */
#define REG_TC1_SR1   (*(RoReg*)0x40084060U) /**< \brief (TC1) Status Register (channel = 1) */
#define REG_TC1_IER1  (*(WoReg*)0x40084064U) /**< \brief (TC1) Interrupt Enable Register (channel = 1) */
#define REG_TC1_IDR1  (*(WoReg*)0x40084068U) /**< \brief (TC1) Interrupt Disable Register (channel = 1) */
#define REG_TC1_IMR1  (*(RoReg*)0x4008406CU) /**< \brief (TC1) Interrupt Mask Register (channel = 1) */
#define REG_TC1_CCR2  (*(WoReg*)0x40084080U) /**< \brief (TC1) Channel Control Register (channel = 2) */
#define REG_TC1_CMR2  (*(RwReg*)0x40084084U) /**< \brief (TC1) Channel Mode Register (channel = 2) */
#define REG_TC1_SMMR2 (*(RwReg*)0x40084088U) /**< \brief (TC1) Stepper Motor Mode Register (channel = 2) */
#define REG_TC1_CV2   (*(RoReg*)0x40084090U) /**< \brief (TC1) Counter Value (channel = 2) */
#define REG_TC1_RA2   (*(RwReg*)0x40084094U) /**< \brief (TC1) Register A (channel = 2) */
#define REG_TC1_RB2   (*(RwReg*)0x40084098U) /**< \brief (TC1) Register B (channel = 2) */
#define REG_TC1_RC2   (*(RwReg*)0x4008409CU) /**< \brief (TC1) Register C (channel = 2) */
#define REG_TC1_SR2   (*(RoReg*)0x400840A0U) /**< \brief (TC1) Status Register (channel = 2) */
#define REG_TC1_IER2  (*(WoReg*)0x400840A4U) /**< \brief (TC1) Interrupt Enable Register (channel = 2) */
#define REG_TC1_IDR2  (*(WoReg*)0x400840A8U) /**< \brief (TC1) Interrupt Disable Register (channel = 2) */
#define REG_TC1_IMR2  (*(RoReg*)0x400840ACU) /**< \brief (TC1) Interrupt Mask Register (channel = 2) */
#define REG_TC1_BCR   (*(WoReg*)0x400840C0U) /**< \brief (TC1) Block Control Register */
#define REG_TC1_BMR   (*(RwReg*)0x400840C4U) /**< \brief (TC1) Block Mode Register */
#define REG_TC1_QIER  (*(WoReg*)0x400840C8U) /**< \brief (TC1) QDEC Interrupt Enable Register */
#define REG_TC1_QIDR  (*(WoReg*)0x400840CCU) /**< \brief (TC1) QDEC Interrupt Disable Register */
#define REG_TC1_QIMR  (*(RoReg*)0x400840D0U) /**< \brief (TC1) QDEC Interrupt Mask Register */
#define REG_TC1_QISR  (*(RoReg*)0x400840D4U) /**< \brief (TC1) QDEC Interrupt Status Register */
#define REG_TC1_FMR   (*(RwReg*)0x400840D8U) /**< \brief (TC1) Fault Mode Register */
#define REG_TC1_WPMR  (*(RwReg*)0x400840E4U) /**< \brief (TC1) Write Protect Mode Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM3XA_TC1_INSTANCE_ */
