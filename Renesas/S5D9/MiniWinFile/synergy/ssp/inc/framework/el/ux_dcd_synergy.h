/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/


/** ************************************************************************/
/** ************************************************************************/
/**                                                                       */ 
/** USBX Component                                                        */ 
/**                                                                       */
/**   SYNERGY Controller Driver                                           */
/**                                                                       */
/** ************************************************************************/
/** ************************************************************************/

/** ************************************************************************/ 
/*                                                                        */ 
/*  COMPONENT DEFINITION                                   RELEASE        */ 
/*                                                                        */ 
/*    ux_dcd_synergy.h                                    PORTABLE C      */ 
/*                                                           5.6          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This file defines the equivalences for the SYNERGY RENESAS          */ 
/*    USB device controller.                                              */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  10-10-2012     TCRG                     Initial Version 5.6           */ 
/*                                                                        */ 
/** ************************************************************************/ 

#ifndef UX_DCD_SYNERGY_H
#define UX_DCD_SYNERGY_H

/** *****************************************************************************************************************//** 
 * @ingroup SF_Library
 * @addtogroup sf_el_ux USBX Framework
 * 
 * @brief RTOS-integrated USBX adaptation framework for Synergy. Implements USB HOST and DEVICE low level device drivers.
 *
 * @{
 **********************************************************************************************************************/

#include "r_transfer_api.h"

/** Define SYNERGY generic equivalences.  */

#define UX_DCD_SYNERGY_SLAVE_CONTROLLER                         (0x80U)
#if defined(BSP_MCU_GROUP_S124) || defined(BSP_MCU_GROUP_S128) || defined(BSP_MCU_GROUP_S1JA)
#define UX_DCD_SYNERGY_MAX_ED                                   (7U)
#else
#define UX_DCD_SYNERGY_MAX_ED                                   (10U)
#endif
#define UX_DCD_SYNERGY_ENABLE                                   (1U)
#define UX_DCD_SYNERGY_DISABLE                                  (0U)
#define UX_DCD_SYNERGY_MAX_BULK_PAYLOAD                         (512U)
#define UX_DCD_SYNERGY_MAX_CONTROL_PAYLOAD                      (512U)
#define UX_DCD_SYNERGY_MAX_BUF_SIZE                             (64U)
#define UX_DCD_SYNERGY_MAX_BUF_NUM                              (127U)

#if defined(BSP_MCU_GROUP_S124) || defined(BSP_MCU_GROUP_S128) || defined(BSP_MCU_GROUP_S1JA)
#define UX_DCD_SYNERGY_MIN_PIPE                                 (4UL)
#define UX_DCD_SYNERGY_MAX_PIPE                                 (7UL)
#else
#define UX_DCD_SYNERGY_MIN_PIPE                                 (1UL)
#define UX_DCD_SYNERGY_MAX_PIPE                                 (9UL)
#endif


/** Define SYNERGY HCOR register mapping.  */

#define UX_SYNERGY_DCD_SYSCFG                                   (0x00UL)
#define UX_SYNERGY_DCD_BUSWAIT                                  (0x02UL)
#define UX_SYNERGY_DCD_SYSSTS                                   (0x04UL)
#define UX_SYNERGY_DCD_PLLSTA                                   (0x06UL)
#define UX_SYNERGY_DCD_DVSTCTR                                  (0x08UL)
#define UX_SYNERGY_DCD_CFIFO                                    (0x14UL)
#define UX_SYNERGY_DCD_CFIFOH                                   (0x16UL)
#define UX_SYNERGY_DCD_CFIFOHH                                  (0x17UL)
#define UX_SYNERGY_DCD_D0FIFO                                   (0x18UL)
#define UX_SYNERGY_DCD_D0FIFOH                                  (0x1AUL)
#define UX_SYNERGY_DCD_D0FIFOHH                                 (0x1BUL)
#define UX_SYNERGY_DCD_D1FIFO                                   (0x1CUL)
#define UX_SYNERGY_DCD_D1FIFOH                                  (0x1EUL)
#define UX_SYNERGY_DCD_D1FIFOHH                                 (0x1FUL)
#define UX_SYNERGY_DCD_CFIFOSEL                                 (0x20UL)
#define UX_SYNERGY_DCD_CFIFOCTR                                 (0x22UL)
#define UX_SYNERGY_DCD_D0FIFOSEL                                (0x28UL)
#define UX_SYNERGY_DCD_D0FIFOCTR                                (0x2AUL)
#define UX_SYNERGY_DCD_D1FIFOSEL                                (0x2CUL)
#define UX_SYNERGY_DCD_D1FIFOCTR                                (0x2EUL)
#define UX_SYNERGY_DCD_INTENB0                                  (0x30UL)
#define UX_SYNERGY_DCD_INTENB1                                  (0x32UL)
#define UX_SYNERGY_DCD_BRDYENB                                  (0x36UL)
#define UX_SYNERGY_DCD_NRDYENB                                  (0x38UL)
#define UX_SYNERGY_DCD_BEMPENB                                  (0x3AUL)
#define UX_SYNERGY_DCD_SOFCFG                                   (0x3CUL)
#define UX_SYNERGY_DCD_PHYSET                                   (0x3EUL)
#define UX_SYNERGY_DCD_INTSTS0                                  (0x40UL)
#define UX_SYNERGY_DCD_INTSTS1                                  (0x42UL)
#define UX_SYNERGY_DCD_BRDYSTS                                  (0x46UL)
#define UX_SYNERGY_DCD_NRDYSTS                                  (0x48UL)
#define UX_SYNERGY_DCD_BEMPSTS                                  (0x4AUL)
#define UX_SYNERGY_DCD_FRMNUM                                   (0x4CUL)

#define UX_SYNERGY_DCD_DVCHGR                                   (0x4EUL)

#define UX_SYNERGY_DCD_USBADDR                                  (0x50UL)
#define UX_SYNERGY_DCD_USBREQ                                   (0x54UL)
#define UX_SYNERGY_DCD_USBVAL                                   (0x56UL)
#define UX_SYNERGY_DCD_USBINDX                                  (0x58UL)
#define UX_SYNERGY_DCD_USBLENG                                  (0x5AUL)
#define UX_SYNERGY_DCD_DCPCFG                                   (0x5CUL)
#define UX_SYNERGY_DCD_DCPMAXP                                  (0x5EUL)
#define UX_SYNERGY_DCD_DCPCTR                                   (0x60UL)
#define UX_SYNERGY_DCD_PIPESEL                                  (0x64UL)
#define UX_SYNERGY_DCD_PIPECFG                                  (0x68UL)
#define UX_SYNERGY_DCD_PIPEBUF                                  (0x6AUL)

#define UX_SYNERGY_DCD_PIPEMAXP                                 (0x6CUL)
#define UX_SYNERGY_DCD_PIPEPERI                                 (0x6EUL)
#define UX_SYNERGY_DCD_PIPE1CTR                                 (0x70UL)
#define UX_SYNERGY_DCD_PIPE2CTR                                 (0x72UL)
#define UX_SYNERGY_DCD_PIPE3CTR                                 (0x74UL)
#define UX_SYNERGY_DCD_PIPE4CTR                                 (0x76UL)
#define UX_SYNERGY_DCD_PIPE5CTR                                 (0x78UL)
#define UX_SYNERGY_DCD_PIPE6CTR                                 (0x7AUL)
#define UX_SYNERGY_DCD_PIPE7CTR                                 (0x7CUL)
#define UX_SYNERGY_DCD_PIPE8CTR                                 (0x7EUL)
#define UX_SYNERGY_DCD_PIPE9CTR                                 (0x80UL)
#define UX_SYNERGY_DCD_PIPE1TRE                                 (0x90UL)
#define UX_SYNERGY_DCD_PIPE1TRN                                 (0x92UL)
#define UX_SYNERGY_DCD_PIPE2TRE                                 (0x94UL)
#define UX_SYNERGY_DCD_PIPE2TRN                                 (0x96UL)
#define UX_SYNERGY_DCD_PIPE3TRE                                 (0x98UL)
#define UX_SYNERGY_DCD_PIPE3TRN                                 (0x9AUL)
#define UX_SYNERGY_DCD_PIPE4TRE                                 (0x9CUL)
#define UX_SYNERGY_DCD_PIPE4TRN                                 (0x9EUL)
#define UX_SYNERGY_DCD_PIPE5TRE                                 (0xA0UL)
#define UX_SYNERGY_DCD_PIPE5TRN                                 (0xA2UL)
#define UX_SYNERGY_DCD_USBMC                                    (0xCCUL)
#define UX_SYNERGY_DCD_DEVADD0                                  (0xD0UL)
#define UX_SYNERGY_DCD_DEVADD1                                  (0xD2UL)
#define UX_SYNERGY_DCD_DEVADD2                                  (0xD4UL)
#define UX_SYNERGY_DCD_DEVADD3                                  (0xD6UL)
#define UX_SYNERGY_DCD_DEVADD4                                  (0xD8UL)
#define UX_SYNERGY_DCD_DEVADD5                                  (0xDAUL)
#define UX_SYNERGY_DCD_PHYSLEW                                  (0xF0UL)
#define UX_SYNERGY_DCD_LPSTS                                    (0x102UL)

#if defined(BSP_MCU_GROUP_S124) || defined(BSP_MCU_GROUP_S128) || defined(BSP_MCU_GROUP_S1JA)
#define UX_SYNERGY_DCD_UCKSEL                                   (0xC4U)
#endif

#define UX_SYNERGY_DCD_BUSWAIT_DEFAULT_VAL                      (0xFU)
#define UX_SYNERGY_DCD_BUSWAIT_MASK                             (0xFU)
/** Register access wait cycles for USBHS controller. 7cycles at Peripheral clock 120MHz */
#define UX_SYNERGY_DCD_BUSWAIT_CALC_FREQ_PCLK_CYC               (17142857U)
#define UX_SYNERGY_DCD_BUSWAIT_CALC_FREQ_PCLK_CYCx10            (1714288U)

/** Supported USBMCLK frequency for S7G2 and S5D9.  */
#define UX_SYNERGY_DCD_MAIN_OSC_24MHz                            (24000000U)
#define UX_SYNERGY_DCD_MAIN_OSC_20MHz                            (20000000U)
#define UX_SYNERGY_DCD_MAIN_OSC_12MHz                            (12000000U)

/** Define SYNERGY control register values.  */
#define UX_SYNERGY_DCD_SYSCFG_SCKE                              (1U<<10)
#define UX_SYNERGY_DCD_SYSCFG_CNEN                              (1U<<8)
#define UX_SYNERGY_DCD_SYSCFG_HSE                               (1U<<7)
#define UX_SYNERGY_DCD_SYSCFG_DCFM                              (1U<<6)
#define UX_SYNERGY_DCD_SYSCFG_DRPD                              (1U<<5)
#define UX_SYNERGY_DCD_SYSCFG_DPRPU                             (1U<<4)
#define UX_SYNERGY_DCD_SYSCFG_DMRPU                             (1U<<3)
#define UX_SYNERGY_DCD_SYSCFG_USBE                              (1)

#define UX_SYNERGY_DCD_SYSSTS_LNST                              (3)
#define UX_SYNERGY_DCD_SYSSTS_SOFEN                             (0x20U)

#define UX_SYNERGY_DCD_DVSTCTR_UACKEY0                          (1U<<15)
#define UX_SYNERGY_DCD_DVSTCTR_UACKEY1                          (1U<<12)
#define UX_SYNERGY_DCD_DVSTCTR_WKUP                             (1U<<8)
#define UX_SYNERGY_DCD_DVSTCTR_RWUPE                            (1U<<7)
#define UX_SYNERGY_DCD_DVSTCTR_USBRST                           (1U<<6)
#define UX_SYNERGY_DCD_DVSTCTR_RESUME                           (1U<<5)
#define UX_SYNERGY_DCD_DVSTCTR_UACT                             (1U<<4)
#define UX_SYNERGY_DCD_DVSTCTR_RHST                             (0x7U)

#define UX_SYNERGY_DCD_DVSTCTR_SPEED_LOW                        (1)
#define UX_SYNERGY_DCD_DVSTCTR_SPEED_FULL                       (2)
#define UX_SYNERGY_DCD_DVSTCTR_SPEED_HIGH                       (3)
#define UX_SYNERGY_DCD_DVSTCTR_RESET_IN_PROGRESS                (4)

#define UX_SYNERGY_DCD_TESTMODE_HOSTPCC                         (1U<<15)

#define UX_SYNERGY_DCD_DXFBCFG_DFACC                            (0U<<12)

#define UX_SYNERGY_DCD_CFIFOSEL_RCNT                            (1U<<15)
#define UX_SYNERGY_DCD_CFIFOSEL_REW                             (1U<<14)
#define UX_SYNERGY_DCD_CFIFOSEL_MBW_8                           (0U<<10)
#define UX_SYNERGY_DCD_CFIFOSEL_MBW_16                          (1U<<10)
#define UX_SYNERGY_DCD_CFIFOSEL_MBW_32                          (2U<<10)
#define UX_SYNERGY_DCD_CFIFOSEL_MBW_MASK                        (3U<<10)
#define UX_SYNERGY_DCD_CFIFOSEL_BIGEND                          (1U<<8)
#define UX_SYNERGY_DCD_CFIFOSEL_ISEL                            (1U<<5)
#define UX_SYNERGY_DCD_CFIFOSEL_CURPIPE_MASK                    (0xFU)

#define UX_SYNERGY_DCD_DFIFOSEL_RCNT                            (1U<<15)
#define UX_SYNERGY_DCD_DFIFOSEL_REW                             (1U<<14)
#define UX_SYNERGY_DCD_DFIFOSEL_DCLRM                           (1U<<13)
#define UX_SYNERGY_DCD_DFIFOSEL_DREQE                           (1U<<12)
#define UX_SYNERGY_DCD_DFIFOSEL_MBW_8                           (0U<<10)
#define UX_SYNERGY_DCD_DFIFOSEL_MBW_16                          (1U<<10)
#define UX_SYNERGY_DCD_DFIFOSEL_MBW_32                          (2U<<10)
#define UX_SYNERGY_DCD_DFIFOSEL_MBW_MASK                        (3U<<10)
#define UX_SYNERGY_DCD_DFIFOSEL_BIGEND                          (1U<<8)
#define UX_SYNERGY_DCD_DFIFOSEL_CURPIPE_MASK                    (0xFU)

#define UX_SYNERGY_DCD_FIFOCTR_BVAL                             (1U<<15)
#define UX_SYNERGY_DCD_FIFOCTR_BCLR                             (1U<<14)
#define UX_SYNERGY_DCD_FIFOCTR_FRDY                             (1U<<13)
#define UX_SYNERGY_DCD_FIFOCTR_DTLN                             (0xFFFU)
                                                        
#define UX_SYNERGY_DCD_INTENB0_VBSE                             (1U<<15)
#define UX_SYNERGY_DCD_INTENB0_RSME                             (1U<<14)
#define UX_SYNERGY_DCD_INTENB0_SOFE                             (1U<<13)
#define UX_SYNERGY_DCD_INTENB0_DVSE                             (1U<<12)
#define UX_SYNERGY_DCD_INTENB0_CTRE                             (1U<<11)
#define UX_SYNERGY_DCD_INTENB0_BEMPE                            (1U<<10)
#define UX_SYNERGY_DCD_INTENB0_NRDYE                            (1U<<9)
#define UX_SYNERGY_DCD_INTENB0_BRDYE                            (1U<<8)

#define UX_SYNERGY_DCD_INTENB1_BCHGE                            (1U<<14)
#define UX_SYNERGY_DCD_INTENB1_DTCHE                            (1U<<12)
#define UX_SYNERGY_DCD_INTENB1_ATTCHE                           (1U<<11)
#define UX_SYNERGY_DCD_INTENB1_EOFERRE                          (1U<<6)
#define UX_SYNERGY_DCD_INTENB1_SIGNE                            (1U<<5)
#define UX_SYNERGY_DCD_INTENB1_SACKE                            (1U<<4)

#define UX_SYNERGY_DCD_PIPE0                                    (1U<<0)
#define UX_SYNERGY_DCD_PIPE1                                    (1U<<1)
#define UX_SYNERGY_DCD_PIPE2                                    (1U<<2)
#define UX_SYNERGY_DCD_PIPE3                                    (1U<<3)
#define UX_SYNERGY_DCD_PIPE4                                    (1U<<4)
#define UX_SYNERGY_DCD_PIPE5                                    (1U<<5)
#define UX_SYNERGY_DCD_PIPE6                                    (1U<<6)
#define UX_SYNERGY_DCD_PIPE7                                    (1U<<7)
#define UX_SYNERGY_DCD_PIPE8                                    (1U<<8)
#define UX_SYNERGY_DCD_PIPE9                                    (1U<<9)
#define UX_SYNERGY_DCD_PIPE_ALL                                 (0x3FFU)

#define UX_SYNERGY_DCD_SOFCFG_TRNENSEL                          (1U<<8)
#define UX_SYNERGY_DCD_SOFCFG_BRDYM                             (1U<<6)
#define UX_SYNERGY_DCD_SOFCFG_INIT                              (1U<<5)

#define UX_SYNERGY_DCD_PHYSET_HSEB                              (1U<<15)
#define UX_SYNERGY_DCD_PHYSET_REPSTART                          (1U<<11)
#define UX_SYNERGY_DCD_PHYSET_REPSEL                            (1U<<8)
#define UX_SYNERGY_DCD_PHYSET_CLKSEL_1                          (1U<<5)
#define UX_SYNERGY_DCD_PHYSET_CLKSEL_0                          (1U<<4)
#define UX_SYNERGY_DCD_PHYSET_CDPEN                             (1U<<3)
#define UX_SYNERGY_DCD_PHYSET_PLLRESET                          (1U<<1)
#define UX_SYNERGY_DCD_PHYSET_DIRPD                             (1U<<0)

#define UX_SYNERGY_DCD_INTSTS0_VBINT                            (USHORT)(1U<<15)
#define UX_SYNERGY_DCD_INTSTS0_RESM                             (USHORT)(1U<<14)
#define UX_SYNERGY_DCD_INTSTS0_SOFR                             (1U<<13)
#define UX_SYNERGY_DCD_INTSTS0_DVST                             (USHORT)(1U<<12)
#define UX_SYNERGY_DCD_INTSTS0_CTRT                             (USHORT)(1U<<11)
#define UX_SYNERGY_DCD_INTSTS0_BEMP                             (1U<<10)
#define UX_SYNERGY_DCD_INTSTS0_NRDY                             (1U<<9)
#define UX_SYNERGY_DCD_INTSTS0_BRDY                             (1U<<8)
#define UX_SYNERGY_DCD_INTSTS0_VBSTS                            (1U<<7)
#define UX_SYNERGY_DCD_INTSTS0_DVSQ_MASK                        (7U<<4)
#define UX_SYNERGY_DCD_INTSTS0_VALID                            (USHORT)(1U<<3)
#define UX_SYNERGY_DCD_INTSTS0_CTSQ_MASK                        (7U)

#define UX_SYNERGY_DCD_INTSTS0_DVSQ_POWERED                     (0x0000U)
#define UX_SYNERGY_DCD_INTSTS0_DVSQ_DEFAULT                     (0x0010U)
#define UX_SYNERGY_DCD_INTSTS0_DVSQ_ADDRESS                     (0x0020U)
#define UX_SYNERGY_DCD_INTSTS0_DVSQ_CONFIGURED                  (0x0030U)
#define UX_SYNERGY_DCD_INTSTS0_DVSQ_SUSPENDED_POWERED           (0x0040U)
#define UX_SYNERGY_DCD_INTSTS0_DVSQ_SUSPENDED_DEFAULT           (0x0050U)
#define UX_SYNERGY_DCD_INTSTS0_DVSQ_SUSPENDED_ADDRESS           (0x0060U)
#define UX_SYNERGY_DCD_INTSTS0_DVSQ_SUSPENDED_CONFIGURED        (0x0070U)

#define UX_SYNERGY_DCD_INTSTS0_CTSQ_SETUP                       (0x0000U)
#define UX_SYNERGY_DCD_INTSTS0_CTSQ_CRDS                        (0x0001U)
#define UX_SYNERGY_DCD_INTSTS0_CTSQ_CRSS                        (0x0002U)
#define UX_SYNERGY_DCD_INTSTS0_CTSQ_CWDS                        (0x0003U)
#define UX_SYNERGY_DCD_INTSTS0_CTSQ_CWSS                        (0x0004U)
#define UX_SYNERGY_DCD_INTSTS0_CTSQ_CWNDSS                      (0x0005U)
#define UX_SYNERGY_DCD_INTSTS0_CTSQ_CTSE                        (0x0006U)

#define UX_SYNERGY_DCD_INTSTS1_BCHG                             (1U<<14)
#define UX_SYNERGY_DCD_INTSTS1_DTCH                             (1U<<12)
#define UX_SYNERGY_DCD_INTSTS1_ATTCH                            (1U<<11)
#define UX_SYNERGY_DCD_INTSTS1_EOFERR                           (1U<<6)
#define UX_SYNERGY_DCD_INTSTS1_SIGN                             (1U<<5)
#define UX_SYNERGY_DCD_INTSTS1_SACK                             (1U<<4)

#define UX_SYNERGY_DCD_FRMNUM_OVRN                              (1U<<15)
#define UX_SYNERGY_DCD_FRMNUM_CRCE                              (1U<<14)
#define UX_SYNERGY_DCD_FRMNUM_FRNM_MASK                         (0x7FF)
 
#define UX_SYNERGY_DCD_DCPCFG_DIR                               (1U<<4)
#define UX_SYNERGY_DCD_DCPCFG_SHTNAK                            (1U<<7)
#define UX_SYNERGY_DCD_DCPCFG_CNTMD                             (1U<<8)

#define UX_SYNERGY_DCD_DCPMAXP_DEVADDR_SHIFT                    (12)
#define UX_SYNERGY_DCD_DCPMAXP_DEVADDR_MASK                     (0xF000U)

#define UX_SYNERGY_DCD_DCPCTR_BSTS                              (1U<<15)
#define UX_SYNERGY_DCD_DCPCTR_INBUFM                            (1U<<14)
#define UX_SYNERGY_DCD_DCPCTR_CSCLR                             (1U<<13)
#define UX_SYNERGY_DCD_DCPCTR_CSSTS                             (1U<<12)
#define UX_SYNERGY_DCD_DCPCTR_SUREQCLR                          (1U<<11)
#define UX_SYNERGY_DCD_DCPCTR_SQCLR                             (1U<<8)
#define UX_SYNERGY_DCD_DCPCTR_SQSET                             (1U<<7)
#define UX_SYNERGY_DCD_DCPCTR_SQMON                             (1U<<6)
#define UX_SYNERGY_DCD_DCPCTR_PBUSY                             (1U<<5)
#define UX_SYNERGY_DCD_DCPCTR_PINGE                             (1U<<4)
#define UX_SYNERGY_DCD_DCPCTR_CCPL                              (1U<<2)
#define UX_SYNERGY_DCD_DCPCTR_PID_MASK                          (3U)
#define UX_SYNERGY_DCD_DCPCTR_PIDNAK                            (0)
#define UX_SYNERGY_DCD_DCPCTR_PIDBUF                            (1U)
#define UX_SYNERGY_DCD_DCPCTR_PIDSTALL                          (2U)
#define UX_SYNERGY_DCD_DCPCTR_PIDSTALL2                         (3U)


#define UX_SYNERGY_DCD_PIPECFG_TYPE_MASK                        (0xC000U)
#define UX_SYNERGY_DCD_PIPECFG_TYPE_BIT_USED                    (0)
#define UX_SYNERGY_DCD_PIPECFG_TYPE_BULK                        (1U<<14)
#define UX_SYNERGY_DCD_PIPECFG_TYPE_INTERRUPT                   (2U<<14)
#define UX_SYNERGY_DCD_PIPECFG_TYPE_ISOCHRONOUS                 (3U<<14)
#define UX_SYNERGY_DCD_PIPECFG_BFRE                             (1U<<10)
#define UX_SYNERGY_DCD_PIPECFG_DBLB                             (1U<<9)
#define UX_SYNERGY_DCD_PIPECFG_CNTMD                            (1U<<8)
#define UX_SYNERGY_DCD_PIPECFG_SHTNAK                           (1U<<7)
#define UX_SYNERGY_DCD_PIPECFG_DIR                              (1U<<4)
#define UX_SYNERGY_DCD_PIPECFG_EPNUM_MASK                       (0xFU)

#define UX_SYNERGY_DCD_PIPEBUF_SIZEMASK                         (0x1FU<<10)
#define UX_SYNERGY_DCD_PIPEBUF_BUFNMBMASK                       (0xFFU<<10)
#define UX_SYNERGY_DCD_PIPEBUF_SHIFT                            (10)

#define UX_SYNERGY_DCD_PIPEMAXP_DEVSELMASK                      (0xFU<<12)
#define UX_SYNERGY_DCD_PIPEMAXP_DEVSEL_SHIFT                    (12)
#define UX_SYNERGY_DCD_PIPEMAXP_MXPSMASK                        (0x7FF)

#define UX_SYNERGY_DCD_PIPE1TRE_TRCLR                           (1U<<8)
#define UX_SYNERGY_DCD_PIPE1TRE_TRENB                           (1U<<9)

#define UX_SYNERGY_DCD_FIFO_D0                                  (0UL)
#define UX_SYNERGY_DCD_FIFO_D1                                  (1UL)
#define UX_SYNERGY_DCD_FIFO_C0                                  (2UL)
#define UX_SYNERGY_DCD_FIFO_C1                                  (3UL)
#define UX_SYNERGY_DCD_FIFO_CD                                  (4UL)
#define UX_SYNERGY_DCD_FIFO_MAX_TRY                             (8UL)


#define UX_SYNERGY_DCD_DEVADDX_SPEED_LOW                        (1U<<6)
#define UX_SYNERGY_DCD_DEVADDX_SPEED_FULL                       (2U<<6)
#define UX_SYNERGY_DCD_DEVADDX_SPEED_HIGH                       (3U<<6)
#define UX_SYNERGY_DCD_DEVADDX_UPPHUB_SHIFT                     (11)
#define UX_SYNERGY_DCD_DEVADDX_HUBPORT_SHIFT                    (8)
#define UX_SYNERGY_DCD_USBMC_VDCEN                              (1U<<7)

/** Define synergy command/status bitmaps.  */

#define UX_SYNERGY_DCD_DCP                                      (0)

#define UX_SYNERGY_DCD_DCPCTR_DATA1                             (1U<<7)
#define UX_SYNERGY_DCD_DCPCTR_DATA0                             (1U<<8)

/** Define synergy PIPE selection definitions.  */
#define UX_SYNERGY_DCD_PIPESEL_NO_PIPE                          (0x000FU)
#define UX_SYNERGY_DCD_PIPESEL_NO_PIPE_USHORT			        (0x0FU)

#define UX_SYNERGY_DCD_UCKSEL_UCKSELC                           (1)

/** Define synergy fifo definition.  */
#define UX_SYNERGY_DCD_PIPE0_SIZE                               (256U)
#define UX_SYNERGY_DCD_PIPE_NB_BUFFERS                          (64)

#define UX_SYNERGY_DCD_PIPECTR_INBUFM                           (1U<<14)
#define UX_SYNERGY_DCD_PIPECTR_BSTS                             (1U<<15)
#define UX_SYNERGY_DCD_PIPECTR_CSCLR                            (1U<<13)
#define UX_SYNERGY_DCD_PIPECTR_CSSTS                            (1U<<12)
#define UX_SYNERGY_DCD_PIPECTR_ATREPM                           (1U<<11)
#define UX_SYNERGY_DCD_PIPECTR_ACLRM                            (1U<<9)
#define UX_SYNERGY_DCD_PIPECTR_SQCLR                            (1U<<8)
#define UX_SYNERGY_DCD_PIPECTR_SQSET                            (1U<<7)
#define UX_SYNERGY_DCD_PIPECTR_SQMON                            (1U<<6)
#define UX_SYNERGY_DCD_PIPECTR_PBUSY                            (1U<<5)
#define UX_SYNERGY_DCD_PIPECTR_PID_MASK                         (3U)
#define UX_SYNERGY_DCD_PIPECTR_PIDNAK                           (0U)
#define UX_SYNERGY_DCD_PIPECTR_PIDBUF                           (1U)
#define UX_SYNERGY_DCD_PIPECTR_PIDSTALL                         (2U)
#define UX_SYNERGY_DCD_PIPECTR_PIDSTALL2                        (3U)
#define UX_SYNERGY_DCD_PIPECTR_DATA1                            (1U<<7)
#define UX_SYNERGY_DCD_PIPECTR_DATA0                            (1U<<8)

/** Define synergy initialization values.  */

#define UX_SYNERGY_DCD_COMMAND_STATUS_RESET                     (0)
#define UX_SYNERGY_DCD_INIT_RESET_DELAY                         (10)
#define UX_SYNERGY_DCD_MAX_BUF_SIZE                             (64)
#define UX_SYNERGY_DCD_MAX_BUF_NUM                              (135UL)
#define UX_SYNERGY_DCD_PIPE1_BUF_START_NUM                      (8UL)
#define UX_SYNERGY_DCD_PIPE6_BUF_START_NUM                      (4UL)

/** Define synergy FIFO write completion code.  */
#define UX_SYNERGY_DCD_FIFO_WRITING                             (2U)
#define UX_SYNERGY_DCD_FIFO_WRITE_END                           (3U)
#define UX_SYNERGY_DCD_FIFO_WRITE_SHORT                         (4U)
#define UX_SYNERGY_DCD_FIFO_WRITE_DMA                           (5U)
#define UX_SYNERGY_DCD_FIFO_WRITE_ERROR                         (6U)
#define UX_SYNERGY_DCD_TIMEOUT_ERROR                            (13U)

/** Define synergy FIFO read completion code.  */
#define UX_SYNERGY_DCD_FIFO_READING                             (2U)
#define UX_SYNERGY_DCD_FIFO_READ_END                            (3U)
#define UX_SYNERGY_DCD_FIFO_READ_SHORT                          (4U)
#define UX_SYNERGY_DCD_FIFO_READ_DMA                            (5U)
#define UX_SYNERGY_DCD_FIFO_READ_ERROR                          (6U)
#define UX_SYNERGY_DCD_FIFO_READ_OVER                           (7U)

/** Define synergy physical endpoint definitions.  */
#define UX_SYNERGY_DCD_ED_BRDY                                  (0x00000001U)
#define UX_SYNERGY_DCD_ED_NRDY                                  (0x00000002U)
#define UX_SYNERGY_DCD_ED_BEMP                                  (0x00000004U)
#define UX_SYNERGY_DCD_ED_EOFERR                                (0x00000010U)
#define UX_SYNERGY_DCD_ED_SIGN                                  (0x00000020U)
#define UX_SYNERGY_DCD_ED_SACK                                  (0x00000040U)

/** PHY Cross Point Adjustment, note that Hardware Manual to be updated(0xE->0x5) */
#define UX_SYNERGY_DCD_PHYSLEW_SLEW_SLEWR00                     (1U<<0)
#define UX_SYNERGY_DCD_PHYSLEW_SLEW_SLEWR01                     (1U<<1)
#define UX_SYNERGY_DCD_PHYSLEW_SLEW_SLEWF00                     (1U<<2)
#define UX_SYNERGY_DCD_PHYSLEW_SLEW_SLEWF01                     (1U<<3)

#define UX_SYNERGY_DCD_LPSTS_SUSPENDM                           (1U<<14)
/** Define USB SYNERGY physical endpoint status definition.  */

#define UX_DCD_SYNERGY_ED_STATUS_UNUSED                         (0U)
#define UX_DCD_SYNERGY_ED_STATUS_USED                           (1U)
#define UX_DCD_SYNERGY_ED_STATUS_TRANSFER                       (2U)
#define UX_DCD_SYNERGY_ED_STATUS_STALLED                        (4U)

/** Define USB SYNERGY physical endpoint state machine definition.  */

#define UX_DCD_SYNERGY_ED_STATE_IDLE                            (0U)
#define UX_DCD_SYNERGY_ED_STATE_DATA_TX                         (1U)
#define UX_DCD_SYNERGY_ED_STATE_DATA_RX                         (2U)
#define UX_DCD_SYNERGY_ED_STATE_STATUS_TX                       (3U)
#define UX_DCD_SYNERGY_ED_STATE_STATUS_RX                       (4U)

#define UX_DCD_SYNERGY_FIFO_FOR_DMA_FREE                        (0U)
#define UX_DCD_SYNERGY_FIFO_FOR_DMA_USED                        (1U)
#define UX_DCD_SYNERGY_TX_SEMAPHORE_NAME_LENGTH                 (14U)
#define UX_DCD_SYNERGY_UNINIT_FAILED                            (0x34)
#define UX_DCD_SYNERGY_CDC_INTERFACE                            (0x0A)
#define UX_DCD_SYNERGY_MSC_INTERFACE                            (0x08)
#define UX_DCD_SYNERGY_CDC_CONTROL_INTERFACE                    (0x02)

/** Define USB SYNERGY physical endpoint structure.  */

typedef struct UX_DCD_SYNERGY_ED_STRUCT 
{

    ULONG           ux_dcd_synergy_ed_status;
    ULONG           ux_dcd_synergy_ed_state;
    ULONG           ux_dcd_synergy_ed_index;
    ULONG           ux_dcd_synergy_ed_fifo_index;
    ULONG           ux_dcd_synergy_ed_payload_length;
    ULONG           ux_dcd_synergy_ed_packet_length;
    ULONG           ux_dcd_synergy_ed_actual_length;
    UCHAR           *ux_dcd_synergy_ed_payload_address;
    ULONG           ux_dcd_synergy_ed_buffer_number;
    ULONG           ux_dcd_synergy_ed_buffer_size;
    struct UX_SLAVE_ENDPOINT_STRUCT             
                    *ux_dcd_synergy_ed_endpoint;
    /** Each pipe to have its own transfer request semaphore */
    TX_SEMAPHORE    ux_dcd_synergy_ep_slave_transfer_request_semaphore;
    bool            ux_dcd_synergy_transfer_request_status;

} UX_DCD_SYNERGY_ED;

/** Define SYNERGY Transfer structure */
typedef struct UX_DCD_SYNERGY_TRANSFER_STRUCT
{
    transfer_instance_t *ux_synergy_transfer_tx;
    transfer_instance_t *ux_synergy_transfer_rx;

} UX_DCD_SYNERGY_TRANSFER;

/** Define SYNERGY Payload Transfer structure */
typedef struct UX_DCD_SYNERGY_PAYLOAD_TRANSFER_STRUCT
{
    UCHAR * payload_buffer;     ///< Destination buffer address 
    ULONG   payload_length;     ///< Payload length to transmit 
    UINT    transfer_times;     ///< Number of transfer 
    UINT    transfer_width;     ///< Bytes per transfer 
    UINT    transfer_blocks;    ///< Number of blocks of above width * times 
} UX_DCD_SYNERGY_PAYLOAD_TRANSFER;

/** Define USB SYNERGY DCD structure definition.  */

typedef struct UX_DCD_SYNERGY_STRUCT
{                                            
    
    struct UX_SLAVE_DCD_STRUCT
                    *ux_dcd_synergy_dcd_owner;
    struct UX_DCD_SYNERGY_ED_STRUCT                    
                    ux_dcd_synergy_ed[UX_DCD_SYNERGY_MAX_ED];
    ULONG           ux_dcd_synergy_pipe[UX_DCD_SYNERGY_MAX_PIPE+1];     ///< "+1" is added to support total number of pipes  e.g.S1 series supports 0-7(total 8) pipes, as "UX_DCD_SYNERGY_MAX_PIPE" is defined as 7  
    ULONG           ux_dcd_synergy_base;
    ULONG           ux_dcd_synergy_next_available_bufnum;
    ULONG           ux_dcd_synergy_debug;
    UX_DCD_SYNERGY_TRANSFER  ux_dcd_synergy_transfer;
    transfer_cfg_t  ux_dcd_synergy_transfer_cfg_tx;
    transfer_cfg_t  ux_dcd_synergy_transfer_cfg_rx;
    volatile bool   ux_dcd_synergy_dma_done_tx;
    volatile bool   ux_dcd_synergy_dma_done_rx;
    volatile UINT   ux_dcd_synergy_dma_packets;
    TX_SEMAPHORE    dma_tx_completion_semaphore;
    TX_SEMAPHORE    dma_rx_completion_semaphore;
    ULONG           read_pipe_number;
    /** This variable determines the D0 FIFO is used for DMA or not */
    UINT            ux_dcd_synergy_D0_fifo_state;
    /** This variable determines the D1 FIFO is used for DMA or not */
    UINT            ux_dcd_synergy_D1_fifo_state;
    ULONG           ux_dcd_synergy_number_of_dma_ep_packets;
    UCHAR           ux_dcd_synergy_using_dma;
    ULONG           ux_dcd_synergy_dma_ep_index;

} UX_DCD_SYNERGY;

/** *****************************************************************************************************************//** 
 * @} (end defgroup sf_el_ux)
 **********************************************************************************************************************/
/* Define USB SYNERGY DCD prototypes.  */

UINT    ux_dcd_synergy_address_set(UX_DCD_SYNERGY *dcd_synergy,ULONG address);
UINT    ux_dcd_synergy_endpoint_create(UX_DCD_SYNERGY *dcd_synergy, UX_SLAVE_ENDPOINT *endpoint);
UINT    ux_dcd_synergy_endpoint_destroy(UX_DCD_SYNERGY *dcd_synergy, UX_SLAVE_ENDPOINT *endpoint);
UINT    ux_dcd_synergy_endpoint_reset(UX_DCD_SYNERGY *dcd_synergy, UX_SLAVE_ENDPOINT *endpoint);
UINT    ux_dcd_synergy_endpoint_stall(UX_DCD_SYNERGY *dcd_synergy, UX_SLAVE_ENDPOINT *endpoint);
UINT    ux_dcd_synergy_endpoint_status(UX_DCD_SYNERGY *dcd_synergy, ULONG endpoint_index);
UINT    ux_dcd_synergy_frame_number_get(UX_DCD_SYNERGY *dcd_synergy, ULONG *frame_number);
UINT    ux_dcd_synergy_function(UX_SLAVE_DCD *dcd, UINT function, VOID *parameter);
UINT    ux_dcd_synergy_initialize(ULONG dcd_io);
UINT    ux_dcd_synergy_initialize_transfer_support(ULONG dcd_io, UX_DCD_SYNERGY_TRANSFER * p_transfer_instance);
UINT    ux_dcd_synergy_initialize_complete(VOID);
VOID    ux_dcd_synergy_interrupt_handler(VOID);
VOID    ux_dcd_synergy_register_clear(UX_DCD_SYNERGY *dcd_synergy, ULONG synergy_register, USHORT value);
ULONG   ux_dcd_synergy_register_read(UX_DCD_SYNERGY *dcd_synergy, ULONG synergy_register);
VOID    ux_dcd_synergy_register_set(UX_DCD_SYNERGY *dcd_synergy, ULONG synergy_register, USHORT value);
VOID    ux_dcd_synergy_register_write(UX_DCD_SYNERGY *dcd_synergy, ULONG synergy_register, USHORT value);
UINT    ux_dcd_synergy_state_change(UX_DCD_SYNERGY *dcd_synergy, ULONG state);
UINT    ux_dcd_synergy_transfer_callback(UX_DCD_SYNERGY *dcd_synergy, UX_SLAVE_TRANSFER *transfer_request,
                                        ULONG interrupt_status, ULONG ctsq_mask);
UINT    ux_dcd_synergy_transfer_request(UX_DCD_SYNERGY *dcd_synergy, UX_SLAVE_TRANSFER *transfer_request);
UINT    ux_dcd_synergy_buffer_read(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed);
UINT    ux_dcd_synergy_fifo_read(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed);
VOID    ux_dcd_synergy_buffer_notready_interrupt(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed, ULONG flag);
VOID    ux_dcd_synergy_buffer_empty_interrupt(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed, ULONG flag);
VOID    ux_dcd_synergy_buffer_ready_interrupt(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed, ULONG flag);
ULONG   ux_dcd_synergy_fifo_port_change(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed, ULONG direction);
UINT    ux_dcd_synergy_fifod_write(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed);
UINT    ux_dcd_synergy_fifoc_write(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed);
UINT    ux_dcd_synergy_buffer_write(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed);
ULONG   ux_dcd_synergy_data_buffer_size(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed);
VOID    ux_dcd_synergy_endpoint_nak_set(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed);
VOID    ux_dcd_synergy_current_endpoint_change(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed, ULONG direction);
VOID    ux_dcd_synergy_fifo_write_software_copy (UX_DCD_SYNERGY *dcd_synergy,
                                        UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload, VOID * p_fifo, ULONG  fifo_sel);
VOID    ux_dcd_synergy_fifo_write_last_bytes(UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload, VOID * p_fifo,
                                              ULONG  usb_base);
VOID    ux_dcd_synergy_write_dma_set(UX_DCD_SYNERGY *dcd_synergy,
                                        UX_DCD_SYNERGY_PAYLOAD_TRANSFER * p_payload, ULONG fifo_sel);
VOID    ux_dcd_synergy_fifo_write_dma_start(UX_DCD_SYNERGY * dcd_synergy, UCHAR * payload_buffer, VOID * p_fifo);
UINT    ux_dcd_synergy_transfer_abort(UX_DCD_SYNERGY *dcd_synergy, UX_SLAVE_TRANSFER *transfer_request);
/* New functions for DMA read and write */
UINT    ux_dcd_synergy_fifo_read_dma(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed, UINT dma_bytes_to_transfer);
UINT    ux_dcd_synergy_fifod_write_dma(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed, UINT dma_bytes_to_transfer);
VOID    ux_dcd_synergy_usb_status_register_clear(UX_DCD_SYNERGY *dcd_synergy, ULONG synergy_register, USHORT value);
UINT    ux_dcd_synergy_fifoc_read(UX_DCD_SYNERGY *dcd_synergy, UX_DCD_SYNERGY_ED *ed);
VOID    ux_dcd_synergy_disconnect(VOID);
UINT    ux_dcd_synergy_uninitialize (ULONG dcd_io);
UINT    ux_dcd_synergy_uninitialize_transfer_support (ULONG dcd_io);
UINT    ux_dcd_synergy_remote_wakeup(UX_DCD_SYNERGY *dcd_synergy,  ULONG *parameter);
#endif

