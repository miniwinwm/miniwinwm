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

#ifndef _SAM3XA_UART_INSTANCE_
#define _SAM3XA_UART_INSTANCE_

/* ========== Register definition for UART peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#define REG_UART_CR            (0x400E0800U) /**< \brief (UART) Control Register */
#define REG_UART_MR            (0x400E0804U) /**< \brief (UART) Mode Register */
#define REG_UART_IER           (0x400E0808U) /**< \brief (UART) Interrupt Enable Register */
#define REG_UART_IDR           (0x400E080CU) /**< \brief (UART) Interrupt Disable Register */
#define REG_UART_IMR           (0x400E0810U) /**< \brief (UART) Interrupt Mask Register */
#define REG_UART_SR            (0x400E0814U) /**< \brief (UART) Status Register */
#define REG_UART_RHR           (0x400E0818U) /**< \brief (UART) Receive Holding Register */
#define REG_UART_THR           (0x400E081CU) /**< \brief (UART) Transmit Holding Register */
#define REG_UART_BRGR          (0x400E0820U) /**< \brief (UART) Baud Rate Generator Register */
#define REG_UART_RPR           (0x400E0900U) /**< \brief (UART) Receive Pointer Register */
#define REG_UART_RCR           (0x400E0904U) /**< \brief (UART) Receive Counter Register */
#define REG_UART_TPR           (0x400E0908U) /**< \brief (UART) Transmit Pointer Register */
#define REG_UART_TCR           (0x400E090CU) /**< \brief (UART) Transmit Counter Register */
#define REG_UART_RNPR          (0x400E0910U) /**< \brief (UART) Receive Next Pointer Register */
#define REG_UART_RNCR          (0x400E0914U) /**< \brief (UART) Receive Next Counter Register */
#define REG_UART_TNPR          (0x400E0918U) /**< \brief (UART) Transmit Next Pointer Register */
#define REG_UART_TNCR          (0x400E091CU) /**< \brief (UART) Transmit Next Counter Register */
#define REG_UART_PTCR          (0x400E0920U) /**< \brief (UART) Transfer Control Register */
#define REG_UART_PTSR          (0x400E0924U) /**< \brief (UART) Transfer Status Register */
#else
#define REG_UART_CR   (*(WoReg*)0x400E0800U) /**< \brief (UART) Control Register */
#define REG_UART_MR   (*(RwReg*)0x400E0804U) /**< \brief (UART) Mode Register */
#define REG_UART_IER  (*(WoReg*)0x400E0808U) /**< \brief (UART) Interrupt Enable Register */
#define REG_UART_IDR  (*(WoReg*)0x400E080CU) /**< \brief (UART) Interrupt Disable Register */
#define REG_UART_IMR  (*(RoReg*)0x400E0810U) /**< \brief (UART) Interrupt Mask Register */
#define REG_UART_SR   (*(RoReg*)0x400E0814U) /**< \brief (UART) Status Register */
#define REG_UART_RHR  (*(RoReg*)0x400E0818U) /**< \brief (UART) Receive Holding Register */
#define REG_UART_THR  (*(WoReg*)0x400E081CU) /**< \brief (UART) Transmit Holding Register */
#define REG_UART_BRGR (*(RwReg*)0x400E0820U) /**< \brief (UART) Baud Rate Generator Register */
#define REG_UART_RPR  (*(RwReg*)0x400E0900U) /**< \brief (UART) Receive Pointer Register */
#define REG_UART_RCR  (*(RwReg*)0x400E0904U) /**< \brief (UART) Receive Counter Register */
#define REG_UART_TPR  (*(RwReg*)0x400E0908U) /**< \brief (UART) Transmit Pointer Register */
#define REG_UART_TCR  (*(RwReg*)0x400E090CU) /**< \brief (UART) Transmit Counter Register */
#define REG_UART_RNPR (*(RwReg*)0x400E0910U) /**< \brief (UART) Receive Next Pointer Register */
#define REG_UART_RNCR (*(RwReg*)0x400E0914U) /**< \brief (UART) Receive Next Counter Register */
#define REG_UART_TNPR (*(RwReg*)0x400E0918U) /**< \brief (UART) Transmit Next Pointer Register */
#define REG_UART_TNCR (*(RwReg*)0x400E091CU) /**< \brief (UART) Transmit Next Counter Register */
#define REG_UART_PTCR (*(WoReg*)0x400E0920U) /**< \brief (UART) Transfer Control Register */
#define REG_UART_PTSR (*(RoReg*)0x400E0924U) /**< \brief (UART) Transfer Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM3XA_UART_INSTANCE_ */
