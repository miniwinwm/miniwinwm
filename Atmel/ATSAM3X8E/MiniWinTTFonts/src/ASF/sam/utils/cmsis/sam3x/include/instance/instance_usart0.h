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

#ifndef _SAM3XA_USART0_INSTANCE_
#define _SAM3XA_USART0_INSTANCE_

/* ========== Register definition for USART0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_USART0_CR          (0x40098000U) /**< \brief (USART0) Control Register */
#define REG_USART0_MR          (0x40098004U) /**< \brief (USART0) Mode Register */
#define REG_USART0_IER          (0x40098008U) /**< \brief (USART0) Interrupt Enable Register */
#define REG_USART0_IDR          (0x4009800CU) /**< \brief (USART0) Interrupt Disable Register */
#define REG_USART0_IMR          (0x40098010U) /**< \brief (USART0) Interrupt Mask Register */
#define REG_USART0_CSR          (0x40098014U) /**< \brief (USART0) Channel Status Register */
#define REG_USART0_RHR          (0x40098018U) /**< \brief (USART0) Receiver Holding Register */
#define REG_USART0_THR          (0x4009801CU) /**< \brief (USART0) Transmitter Holding Register */
#define REG_USART0_BRGR          (0x40098020U) /**< \brief (USART0) Baud Rate Generator Register */
#define REG_USART0_RTOR          (0x40098024U) /**< \brief (USART0) Receiver Time-out Register */
#define REG_USART0_TTGR          (0x40098028U) /**< \brief (USART0) Transmitter Timeguard Register */
#define REG_USART0_FIDI          (0x40098040U) /**< \brief (USART0) FI DI Ratio Register */
#define REG_USART0_NER          (0x40098044U) /**< \brief (USART0) Number of Errors Register */
#define REG_USART0_IF          (0x4009804CU) /**< \brief (USART0) IrDA Filter Register */
#define REG_USART0_MAN          (0x40098050U) /**< \brief (USART0) Manchester Encoder Decoder Register */
#define REG_USART0_LINMR          (0x40098054U) /**< \brief (USART0) LIN Mode Register */
#define REG_USART0_LINIR          (0x40098058U) /**< \brief (USART0) LIN Identifier Register */
#define REG_USART0_WPMR          (0x400980E4U) /**< \brief (USART0) Write Protect Mode Register */
#define REG_USART0_WPSR          (0x400980E8U) /**< \brief (USART0) Write Protect Status Register */
#define REG_USART0_RPR          (0x40098100U) /**< \brief (USART0) Receive Pointer Register */
#define REG_USART0_RCR          (0x40098104U) /**< \brief (USART0) Receive Counter Register */
#define REG_USART0_TPR          (0x40098108U) /**< \brief (USART0) Transmit Pointer Register */
#define REG_USART0_TCR          (0x4009810CU) /**< \brief (USART0) Transmit Counter Register */
#define REG_USART0_RNPR          (0x40098110U) /**< \brief (USART0) Receive Next Pointer Register */
#define REG_USART0_RNCR          (0x40098114U) /**< \brief (USART0) Receive Next Counter Register */
#define REG_USART0_TNPR          (0x40098118U) /**< \brief (USART0) Transmit Next Pointer Register */
#define REG_USART0_TNCR          (0x4009811CU) /**< \brief (USART0) Transmit Next Counter Register */
#define REG_USART0_PTCR          (0x40098120U) /**< \brief (USART0) Transfer Control Register */
#define REG_USART0_PTSR          (0x40098124U) /**< \brief (USART0) Transfer Status Register */
#else
#define REG_USART0_CR (*(WoReg*)0x40098000U) /**< \brief (USART0) Control Register */
#define REG_USART0_MR (*(RwReg*)0x40098004U) /**< \brief (USART0) Mode Register */
#define REG_USART0_IER (*(WoReg*)0x40098008U) /**< \brief (USART0) Interrupt Enable Register */
#define REG_USART0_IDR (*(WoReg*)0x4009800CU) /**< \brief (USART0) Interrupt Disable Register */
#define REG_USART0_IMR (*(RoReg*)0x40098010U) /**< \brief (USART0) Interrupt Mask Register */
#define REG_USART0_CSR (*(RoReg*)0x40098014U) /**< \brief (USART0) Channel Status Register */
#define REG_USART0_RHR (*(RoReg*)0x40098018U) /**< \brief (USART0) Receiver Holding Register */
#define REG_USART0_THR (*(WoReg*)0x4009801CU) /**< \brief (USART0) Transmitter Holding Register */
#define REG_USART0_BRGR (*(RwReg*)0x40098020U) /**< \brief (USART0) Baud Rate Generator Register */
#define REG_USART0_RTOR (*(RwReg*)0x40098024U) /**< \brief (USART0) Receiver Time-out Register */
#define REG_USART0_TTGR (*(RwReg*)0x40098028U) /**< \brief (USART0) Transmitter Timeguard Register */
#define REG_USART0_FIDI (*(RwReg*)0x40098040U) /**< \brief (USART0) FI DI Ratio Register */
#define REG_USART0_NER (*(RoReg*)0x40098044U) /**< \brief (USART0) Number of Errors Register */
#define REG_USART0_IF (*(RwReg*)0x4009804CU) /**< \brief (USART0) IrDA Filter Register */
#define REG_USART0_MAN (*(RwReg*)0x40098050U) /**< \brief (USART0) Manchester Encoder Decoder Register */
#define REG_USART0_LINMR (*(RwReg*)0x40098054U) /**< \brief (USART0) LIN Mode Register */
#define REG_USART0_LINIR (*(RwReg*)0x40098058U) /**< \brief (USART0) LIN Identifier Register */
#define REG_USART0_WPMR (*(RwReg*)0x400980E4U) /**< \brief (USART0) Write Protect Mode Register */
#define REG_USART0_WPSR (*(RoReg*)0x400980E8U) /**< \brief (USART0) Write Protect Status Register */
#define REG_USART0_RPR (*(RwReg*)0x40098100U) /**< \brief (USART0) Receive Pointer Register */
#define REG_USART0_RCR (*(RwReg*)0x40098104U) /**< \brief (USART0) Receive Counter Register */
#define REG_USART0_TPR (*(RwReg*)0x40098108U) /**< \brief (USART0) Transmit Pointer Register */
#define REG_USART0_TCR (*(RwReg*)0x4009810CU) /**< \brief (USART0) Transmit Counter Register */
#define REG_USART0_RNPR (*(RwReg*)0x40098110U) /**< \brief (USART0) Receive Next Pointer Register */
#define REG_USART0_RNCR (*(RwReg*)0x40098114U) /**< \brief (USART0) Receive Next Counter Register */
#define REG_USART0_TNPR (*(RwReg*)0x40098118U) /**< \brief (USART0) Transmit Next Pointer Register */
#define REG_USART0_TNCR (*(RwReg*)0x4009811CU) /**< \brief (USART0) Transmit Next Counter Register */
#define REG_USART0_PTCR (*(WoReg*)0x40098120U) /**< \brief (USART0) Transfer Control Register */
#define REG_USART0_PTSR (*(RoReg*)0x40098124U) /**< \brief (USART0) Transfer Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM3XA_USART0_INSTANCE_ */
