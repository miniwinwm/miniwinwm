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


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** USBX Component                                                        */
/**                                                                       */
/**   SYNERGY Controller Driver                                           */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/**************************************************************************/ 
/*                                                                        */ 
/*  COMPONENT DEFINITION                                   RELEASE        */ 
/*                                                                        */ 
/*    ux_hcd_synergy.h                                     PORTABLE C     */ 
/*                                                           5.7          */ 
/*  AUTHOR                                                                */ 
/*                                                                        */ 
/*    Thierry Giron, Microsoft Corporation                                */
/*                                                                        */ 
/*  DESCRIPTION                                                           */ 
/*                                                                        */ 
/*    This file contains all the header and extern functions used by the  */ 
/*    USBX host synergy Controller.                                       */ 
/*                                                                        */ 
/*  RELEASE HISTORY                                                       */ 
/*                                                                        */ 
/*    DATE              NAME                      DESCRIPTION             */ 
/*                                                                        */ 
/*  10-10-2012     TCRG                     Initial Version 5.6           */ 
/*  06-01-2014     TCRG                     Modified comment(s),          */ 
/*                                            resulting in version 5.7    */ 
/*                                                                        */ 
/**************************************************************************/ 

#ifndef UX_HCD_SYNERGY_H
#define UX_HCD_SYNERGY_H

/*******************************************************************************************************************//**
 * @addtogroup sf_el_ux
 * @{
 **********************************************************************************************************************/

#include "r_transfer_api.h"
#include "sf_el_ux_hcd_hs_cfg.h"

/**Define Synergy generic definitions.  */

#define UX_SYNERGY_CONTROLLER                            (0)
#define UX_SYNERGY_CONTROLLER_S7G2                       (1)
#define UX_SYNERGY_CONTROLLER_S3A7                       (2)

#ifndef UX_SYNERGY_MAX_BULK_PAYLOAD
#define UX_SYNERGY_MAX_BULK_PAYLOAD                      (512)
#endif
#ifndef UX_SYNERGY_MAX_ISO_PAYLOAD
#define UX_SYNERGY_MAX_ISO_PAYLOAD                       (1024)
#endif

#define UX_SYNERGY_MAX_CONTROL_PAYLOAD                   (512)
#define UX_SYNERGY_FRAME_DELAY                           (4UL)
#define UX_SYNERGY_PERIODIC_ENTRY_NB                     (32)
#define UX_SYNERGY_PERIODIC_ENTRY_MASK                   (0x1FU)
#define UX_SYNERGY_ENABLE                                (1UL)
#define UX_SYNERGY_DISABLE                               (0UL)
#define UX_SYNERGY_UNINIT_FAILED                         (0x34)

                                                        
/**Protection against no definition of Synergy controller.   */
#ifdef UX_SYNERGY_CONTROLLER_S7G2
#define UX_SYNERGY_HC_SYSCFG                             (0x00UL)
#define UX_SYNERGY_HC_BUSWAIT                            (0x02UL)
#define UX_SYNERGY_HC_SYSSTS0                            (0x04UL)
#define UX_SYNERGY_HC_PLLSTA                             (0x06UL)
#define UX_SYNERGY_HC_DVSTCTR0                           (0x08UL)
#define UX_SYNERGY_HC_CFIFO                              (0x14UL)
#define UX_SYNERGY_HC_CFIFOH                             (0x16UL)
#define UX_SYNERGY_HC_CFIFOHH                            (0x17UL)
#define UX_SYNERGY_HC_D0FIFO                             (0x18UL)
#define UX_SYNERGY_HC_D1FIFO                             (0x1CUL)
#define UX_SYNERGY_HC_CFIFOSEL                           (0x20UL)
#define UX_SYNERGY_HC_CFIFOCTR                           (0x22UL)
#define UX_SYNERGY_HC_D0FIFOSEL                          (0x28UL)
#define UX_SYNERGY_HC_D0FIFOCTR                          (0x2AUL)
#define UX_SYNERGY_HC_D1FIFOSEL                          (0x2CUL)
#define UX_SYNERGY_HC_D1FIFOCTR                          (0x2EUL)
#define UX_SYNERGY_HC_INTENB0                            (0x30UL)
#define UX_SYNERGY_HC_INTENB1                            (0x32UL)
#define UX_SYNERGY_HC_BRDYENB                            (0x36UL)
#define UX_SYNERGY_HC_NRDYENB                            (0x38UL)
#define UX_SYNERGY_HC_BEMPENB                            (0x3AUL)
#define UX_SYNERGY_HC_SOFCFG                             (0x3CUL)
#define UX_SYNERGY_HC_PHYSET                             (0x3EUL)
#define UX_SYNERGY_HC_INTSTS0                            (0x40UL)
#define UX_SYNERGY_HC_INTSTS1                            (0x42UL)
#define UX_SYNERGY_HC_BRDYSTS                            (0x46UL)
#define UX_SYNERGY_HC_NRDYSTS                            (0x48UL)
#define UX_SYNERGY_HC_BEMPSTS                            (0x4AUL)
#define UX_SYNERGY_HC_FRMNUM                             (0x4CUL)
#define UX_SYNERGY_HC_DVCHGR                             (0x4EUL)
#define UX_SYNERGY_HC_USBADDR                            (0x50UL)
#define UX_SYNERGY_HC_USBREQ                             (0x54UL)
#define UX_SYNERGY_HC_USBVAL                             (0x56UL)
#define UX_SYNERGY_HC_USBINDX                            (0x58UL)
#define UX_SYNERGY_HC_USBLENG                            (0x5AUL)
#define UX_SYNERGY_HC_DCPCFG                             (0x5CUL)
#define UX_SYNERGY_HC_DCPMAXP                            (0x5EUL)
#define UX_SYNERGY_HC_DCPCTR                             (0x60UL)
#define UX_SYNERGY_HC_PIPESEL                            (0x64UL)
#define UX_SYNERGY_HC_PIPECFG                            (0x68UL)
#define UX_SYNERGY_HC_PIPEBUF                            (0x6AUL)
#define UX_SYNERGY_HC_PIPEMAXP                           (0x6CUL)
#define UX_SYNERGY_HC_PIPEPERI                           (0x6EUL)
#define UX_SYNERGY_HC_PIPE1CTR                           (0x70UL)
#define UX_SYNERGY_HC_PIPE2CTR                           (0x72UL)
#define UX_SYNERGY_HC_PIPE3CTR                           (0x74UL)
#define UX_SYNERGY_HC_PIPE4CTR                           (0x76UL)
#define UX_SYNERGY_HC_PIPE5CTR                           (0x78UL)
#define UX_SYNERGY_HC_PIPE6CTR                           (0x7AUL)
#define UX_SYNERGY_HC_PIPE7CTR                           (0x7CUL)
#define UX_SYNERGY_HC_PIPE8CTR                           (0x7EUL)
#define UX_SYNERGY_HC_PIPE9CTR                           (0x80UL)
#define UX_SYNERGY_HC_PIPE1TRE                           (0x90UL)
#define UX_SYNERGY_HC_PIPE1TRN                           (0x92UL)
#define UX_SYNERGY_HC_PIPE2TRE                           (0x94UL)
#define UX_SYNERGY_HC_PIPE2TRN                           (0x96UL)
#define UX_SYNERGY_HC_PIPE3TRE                           (0x98UL)
#define UX_SYNERGY_HC_PIPE3TRN                           (0x9AUL)
#define UX_SYNERGY_HC_PIPE4TRE                           (0x9CUL)
#define UX_SYNERGY_HC_PIPE4TRN                           (0x9EUL)
#define UX_SYNERGY_HC_PIPE5TRE                           (0xA0UL)
#define UX_SYNERGY_HC_PIPE5TRN                           (0xA2UL)
#define UX_SYNERGY_HC_USBMC                              (0xCCUL)
#define UX_SYNERGY_HC_DEVADD0                            (0xD0UL)
#define UX_SYNERGY_HC_DEVADD1                            (0xD2UL)
#define UX_SYNERGY_HC_DEVADD2                            (0xD4UL)
#define UX_SYNERGY_HC_DEVADD3                            (0xD6UL)
#define UX_SYNERGY_HC_DEVADD4                            (0xD8UL)
#define UX_SYNERGY_HC_DEVADD5                            (0xDAUL)
#define UX_SYNERGY_HC_PHYSLEW                            (0xF0UL)
#define UX_SYNERGY_HC_LPSTS                              (0x102UL)

#endif

#define UX_SYNERGY_HC_PFKUSB_ENABLED                     (1U<<4)
#define UX_SYNERGY_HC_PFKUSB_MODE_HOST                   (1)

#define UX_SYNERGY_HC_BUSWAIT_MASK                       (0xFU)

#if defined(BSP_MCU_GROUP_S124) || defined(BSP_MCU_GROUP_S128) || defined(BSP_MCU_GROUP_S1JA)
#define UX_SYNERGY_HC_INTERRUPT_STATUS_MASK              (0xf1U)
#else
#define UX_SYNERGY_HC_INTERRUPT_STATUS_MASK              (0x3ffU)
#endif
/**Register access wait cycles for USBHS controller. 7cycles at Peripheral clock 120MHz */
#define UX_SYNERGY_HC_BUSWAIT_CALC_FREQ_PCLK_CYC         (17142857U)
#define UX_SYNERGY_HC_BUSWAIT_CALC_FREQ_PCLK_CYCX10      (1714288U)

/**Supported USBMCLK frequency for S7G2 and S5D9.  */
#define UX_SYNERGY_HC_MAIN_OSC_24MHz                     (24000000U)
#define UX_SYNERGY_HC_MAIN_OSC_20MHz                     (20000000U)
#define UX_SYNERGY_HC_MAIN_OSC_12MHz                     (12000000U)

/**Define Synergy control register values.  */
#define UX_SYNERGY_HC_SYSCFG_SCKE                        (1U<<10)
#define UX_SYNERGY_HC_SYSCFG_CNEN                        (1U<<8)
#define UX_SYNERGY_HC_SYSCFG_HSE                         (1U<<7)
#define UX_SYNERGY_HC_SYSCFG_DCFM                        (1U<<6)
#define UX_SYNERGY_HC_SYSCFG_DRPD                        (1U<<5)
#define UX_SYNERGY_HC_SYSCFG_DPRPU                       (1U<<4)
#define UX_SYNERGY_HC_SYSCFG_USBE                        (1U<<0)

#define UX_SYNERGY_HC_SYSSTS0_LNST                       (3)
#define UX_SYNERGY_HC_SYSSTS0_IDMON                      (1U<<2)
#define UX_SYNERGY_HC_SYSSTS0_SOFEA                      (1U<<6)
#define UX_SYNERGY_HC_SYSSTS0_HTACT                      (1U<<6)
#define UX_SYNERGY_HC_SYSSTS0_OVCMON                     (0xC0000U)

#define UX_SYNERGY_HC_SYSSTS0_LNST_J_STATE_FS            (1U)
#define UX_SYNERGY_HC_SYSSTS0_LNST_J_STATE_LS            (2U)

#define UX_SYNERGY_HC_PLLSTA_PLLLOCK                     (1U<<0)

#define UX_SYNERGY_HC_DVSTCTR0_HNPBTOA                   (1U<<11)
#define UX_SYNERGY_HC_DVSTCTR0_EXICEN                    (1U<<10)
#define UX_SYNERGY_HC_DVSTCTR0_VBUSEN                    (1U<<9)
#define UX_SYNERGY_HC_DVSTCTR0_WKUP                      (1U<<8)
#define UX_SYNERGY_HC_DVSTCTR0_RWUPE                     (1U<<7)
#define UX_SYNERGY_HC_DVSTCTR0_USBRST                    (1U<<6)
#define UX_SYNERGY_HC_DVSTCTR0_RESUME                    (1U<<5)
#define UX_SYNERGY_HC_DVSTCTR0_UACT                      (1U<<4)
#define UX_SYNERGY_HC_DVSTCTR0_RHST                      (0x7U)

#define UX_SYNERGY_HC_DVSTCTR0_SPEED_LOW                 (1)
#define UX_SYNERGY_HC_DVSTCTR0_SPEED_FULL                (2)
#define UX_SYNERGY_HC_DVSTCTR0_SPEED_HIGH                (3)
#define UX_SYNERGY_HC_DVSTCTR0_RESET_IN_PROGRESS         (4)

#define UX_SYNERGY_HC_CFIFOSEL_RCNT                      (1U<<15)
#define UX_SYNERGY_HC_CFIFOSEL_REW                       (1U<<14)
#define UX_SYNERGY_HC_CFIFOSEL_MBW_8                     (0U<<10)
#define UX_SYNERGY_HC_CFIFOSEL_MBW_16                    (1U<<10)
#define UX_SYNERGY_HC_CFIFOSEL_MBW_32                    (2U<<10)
#define UX_SYNERGY_HC_CFIFOSEL_MBW_MASK                  (3U<<10)
#define UX_SYNERGY_HC_CFIFOSEL_BIGEND                    (1U<<8)
#define UX_SYNERGY_HC_CFIFOSEL_ISEL                      (1U<<5)
#define UX_SYNERGY_HC_CFIFOSEL_CURPIPE_MASK              (0xFU)

#define UX_SYNERGY_HC_DFIFOSEL_RCNT                      (1U<<15)
#define UX_SYNERGY_HC_DFIFOSEL_REW                       (1U<<14)
#define UX_SYNERGY_HC_DFIFOSEL_DCLRM                     (1U<<13)
#define UX_SYNERGY_HC_DFIFOSEL_DREQE                     (1U<<12)
#define UX_SYNERGY_HC_DFIFOSEL_MBW_8                     (0U<<10)
#define UX_SYNERGY_HC_DFIFOSEL_MBW_16                    (1U<<10)
#define UX_SYNERGY_HC_DFIFOSEL_MBW_32                    (2U<<10)
#define UX_SYNERGY_HC_DFIFOSEL_MBW_MASK                  (3U<<10)
#define UX_SYNERGY_HC_DFIFOSEL_BIGEND                    (1U<<8)
#define UX_SYNERGY_HC_DFIFOSEL_CURPIPE_MASK              (0xF)

#define UX_SYNERGY_HC_FIFOCTR_BVAL                       (1U<<15)
#define UX_SYNERGY_HC_FIFOCTR_BCLR                       (1U<<14)
#define UX_SYNERGY_HC_FIFOCTR_FRDY                       (1U<<13)
#define UX_SYNERGY_HC_FIFOCTR_DTLN                       (0xFFF)
                                                    
#define UX_SYNERGY_HC_INTENB0_VBSE                       (1U<<15)
#define UX_SYNERGY_HC_INTENB0_RSME                       (1U<<14)
#define UX_SYNERGY_HC_INTENB0_SOFE                       (1U<<13)
#define UX_SYNERGY_HC_INTENB0_DVSE                       (1U<<12)
#define UX_SYNERGY_HC_INTENB0_CTRE                       (1U<<11)
#define UX_SYNERGY_HC_INTENB0_BEMPE                      (1U<<10)
#define UX_SYNERGY_HC_INTENB0_NRDYE                      (1U<<9)
#define UX_SYNERGY_HC_INTENB0_BRDYE                      (1U<<8)

#define UX_SYNERGY_HC_INTENB1_OVRCRE                     (1U<<15)
#define UX_SYNERGY_HC_INTENB1_BCHGE                      (1U<<14)
#define UX_SYNERGY_HC_INTENB1_DTCHE                      (1U<<12)
#define UX_SYNERGY_HC_INTENB1_ATTCHE                     (1U<<11)
#define UX_SYNERGY_HC_INTENB1_L1RSMENDE                  (1U<<9)
#define UX_SYNERGY_HC_INTENB1_LPSMENDE                   (1U<<8)
#define UX_SYNERGY_HC_INTENB1_EOFERRE                    (1U<<6)
#define UX_SYNERGY_HC_INTENB1_SIGNE                      (1U<<5)
#define UX_SYNERGY_HC_INTENB1_SACKE                      (1U<<4)
#define UX_SYNERGY_HC_INTENB1_PDDETINTE                  (1U<<0)

#define UX_SYNERGY_HC_PIPE0                              (1U<<0)
#define UX_SYNERGY_HC_PIPE1                              (1U<<1)
#define UX_SYNERGY_HC_PIPE2                              (1U<<2)
#define UX_SYNERGY_HC_PIPE3                              (1U<<3)
#define UX_SYNERGY_HC_PIPE4                              (1U<<4)
#define UX_SYNERGY_HC_PIPE5                              (1U<<5)
#define UX_SYNERGY_HC_PIPE6                              (1U<<6)
#define UX_SYNERGY_HC_PIPE7                              (1U<<7)
#define UX_SYNERGY_HC_PIPE8                              (1U<<8)
#define UX_SYNERGY_HC_PIPE9                              (1U<<9)
#define UX_SYNERGY_HC_PIPE_ALL                           (0x3FF)

#define UX_SYNERGY_HC_SOFCFG_TRNENSEL                    (1U<<8)
#define UX_SYNERGY_HC_SOFCFG_BRDYM                       (1U<<6)
#define UX_SYNERGY_HC_SOFCFG_INTL                        (1U<<5)
#define UX_SYNERGY_HC_SOFCFG_EDGESTS                     (1U<<4)

#define UX_SYNERGY_HC_PHYSET_HSEB                        (1U<<15)
#define UX_SYNERGY_HC_PHYSET_REPSTART                    (1U<<11)
#define UX_SYNERGY_HC_PHYSET_REPSEL                      (1U<<8)
#define UX_SYNERGY_HC_PHYSET_CLKSEL_1                    (1U<<5)
#define UX_SYNERGY_HC_PHYSET_CLKSEL_0                    (1U<<4)
#define UX_SYNERGY_HC_PHYSET_CDPEN                       (1U<<3)
#define UX_SYNERGY_HC_PHYSET_PLLRESET                    (1U<<1)
#define UX_SYNERGY_HC_PHYSET_DIRPD                       (1U<<0)


#define UX_SYNERGY_HC_INTSTS0_VBINT                      (1U<<15)
#define UX_SYNERGY_HC_INTSTS0_RESM                       (1U<<14)
#define UX_SYNERGY_HC_INTSTS0_SOFR                       (1U<<13)
#define UX_SYNERGY_HC_INTSTS0_DVST                       (1U<<12)
#define UX_SYNERGY_HC_INTSTS0_CTRT                       (1U<<11)
#define UX_SYNERGY_HC_INTSTS0_BEMP                       (1U<<10)
#define UX_SYNERGY_HC_INTSTS0_NRDY                       (1U<<9)
#define UX_SYNERGY_HC_INTSTS0_BRDY                       (1U<<8)
#define UX_SYNERGY_HC_INTSTS0_VBSTS                      (1U<<7)
#define UX_SYNERGY_HC_INTSTS0_VALID                      (1U<<3)
#define UX_SYNERGY_HC_INTSTS0_CTSQ_MASK                  (7)
#define UX_SYNERGY_HC_INTSTS0_ALL_CLEAR                  (0U)

#define UX_SYNERGY_HC_INTSTS1_OVRCRE                     (1U<<15)
#define UX_SYNERGY_HC_INTSTS1_BCHG                       (1U<<14)
#define UX_SYNERGY_HC_INTSTS1_DTCH                       (1U<<12)
#define UX_SYNERGY_HC_INTSTS1_ATTCH                      (1U<<11)
#define UX_SYNERGY_HC_INTSTS1_EOFERR                     (1U<<6)
#define UX_SYNERGY_HC_INTSTS1_SIGN                       (1U<<5)
#define UX_SYNERGY_HC_INTSTS1_SACK                       (1U<<4)
#define UX_SYNERGY_HC_INTSTS1_ALL_CLEAR                  (0U)

#define UX_SYNERGY_HC_FRMNUM_OVRN                        (1U<<15)
#define UX_SYNERGY_HC_FRMNUM_CRCE                        (1U<<14)
#define UX_SYNERGY_HC_FRMNUM_FRNM_MASK                   (0x7FFU)
 
#define UX_SYNERGY_HC_DCPCFG_DIR                         (1U<<4)

#define UX_SYNERGY_HC_DCPMAXP_DEVADDR_SHIFT              (12U)
#define UX_SYNERGY_HC_DCPMAXP_DEVADDR_MASK               (0xf000U)

#define UX_SYNERGY_HC_DCPCTR_BSTS                        (1U<<15)
#define UX_SYNERGY_HC_DCPCTR_SUREQ                       (1U<<14)
#define UX_SYNERGY_HC_DCPCTR_SUREQCLR                    (1U<<11)
#define UX_SYNERGY_HC_DCPCTR_SQCLR                       (1U<<8)
#define UX_SYNERGY_HC_DCPCTR_SQSET                       (1U<<7)
#define UX_SYNERGY_HC_DCPCTR_SQMON                       (1U<<6)
#define UX_SYNERGY_HC_DCPCTR_PBUSY                       (1U<<5)
#define UX_SYNERGY_HC_DCPCTR_CCPL                        (1U<<2)
#define UX_SYNERGY_HC_DCPCTR_PID_MASK                    (3UL)
#define UX_SYNERGY_HC_DCPCTR_PIDNAK                      (0UL)
#define UX_SYNERGY_HC_DCPCTR_PIDBUF                      (1UL)
#define UX_SYNERGY_HC_DCPCTR_PIDSTALL                    (2UL)
#define UX_SYNERGY_HC_DCPCTR_PIDSTALL2                   (3UL)


#define UX_SYNERGY_HC_PIPECFG_TYPE_MASK                  (0xC000)
#define UX_SYNERGY_HC_PIPECFG_TYPE_BIT_USED              (0)
#define UX_SYNERGY_HC_PIPECFG_TYPE_BULK                  (1U<<14)
#define UX_SYNERGY_HC_PIPECFG_TYPE_INTERRUPT             (2U<<14)
#define UX_SYNERGY_HC_PIPECFG_TYPE_ISOCHRONOUS           (3U<<14)
#define UX_SYNERGY_HC_PIPECFG_BFRE                       (1U<<10)
#define UX_SYNERGY_HC_PIPECFG_DBLB                       (1U<<9)
#define UX_SYNERGY_HC_PIPECFG_CNTMD                      (1U<<8)
#define UX_SYNERGY_HC_PIPECFG_SHTNAK                     (1U<<7)
#define UX_SYNERGY_HC_PIPECFG_DIR                        (1U<<4)
#define UX_SYNERGY_HC_PIPECFG_EPNUM_MASK                 (0xFU)

#define UX_SYNERGY_HC_PIPEBUF_SIZEMASK                   (0x1FU<<10)
#define UX_SYNERGY_HC_PIPEBUF_BUFNMBMASK                 (0xFFU<<10)
#define UX_SYNERGY_HC_PIPEBUF_SHIFT                      (10U)

#define UX_SYNERGY_HC_PIPEMAXP_DEVSELMASK                (0xFU<<12)
#define UX_SYNERGY_HC_PIPEMAXP_DEVSEL_SHIFT              (12U)
#define UX_SYNERGY_HC_PIPEMAXP_MXPSMASK                  (0x7FF)

#define UX_SYNERGY_HC_PIPETRE_TRENB                      (1U<<9)

#define UX_SYNERGY_HC_FIFO_D0                            (0UL)
#define UX_SYNERGY_HC_FIFO_D1                            (1UL)
#define UX_SYNERGY_HC_FIFO_C                             (2UL)

#define UX_SYNERGY_HC_DEVADD_SPEED_LOW                   (1U<<6)
#define UX_SYNERGY_HC_DEVADD_SPEED_FULL                  (2U<<6)
#define UX_SYNERGY_HC_DEVADD_SPEED_HIGH                  (3U<<6)

#define UX_SYNERGY_HC_DEVADD_UPPHUB_SHIFT                (11U)
#define UX_SYNERGY_HC_DEVADD_HUBPORT_SHIFT               (8U)
#define UX_SYNERGY_HC_DEVADD_HUBPORT_BIT_SHIFT           (7U<<8)
#define UX_SYNERGY_HC_USBMC_VDCEN                        (1U<<7)

/**Define Synergy HCOR command/status bitmaps.  */

#define UX_SYNERGY_HC_DCP                                (0)

#define UX_SYNERGY_HC_DCPCTR_DATA1                       (1U<<7)
#define UX_SYNERGY_HC_DCPCTR_DATA0                       (1U<<8)

/**Define Synergy PIPE selection definitions.  */
#define UX_SYNERGY_HC_PIPESEL_NO_PIPE                    0x000f

/**Define Synergy fifo definition.  */
#define UX_SYNERGY_HC_PIPE0_SIZE                         (256)
#define UX_SYNERGY_HC_PIPE_NB_BUFFERS                    (64)


#define UX_SYNERGY_HC_PIPECTR_BSTS                       (1U<<15)
#define UX_SYNERGY_HC_PIPECTR_INBUFM                     (1U<<14)
#define UX_SYNERGY_HC_PIPECTR_ATREPM                     (1U<<10)
#define UX_SYNERGY_HC_PIPECTR_ACLRM                      (1U<<9)
#define UX_SYNERGY_HC_PIPECTR_SQCLR                      (1U<<8)
#define UX_SYNERGY_HC_PIPECTR_SQSET                      (1U<<7)
#define UX_SYNERGY_HC_PIPECTR_SQMON                      (1U<<6)
#define UX_SYNERGY_HC_PIPECTR_PBUSY                      (1U<<5)
#define UX_SYNERGY_HC_PIPECTR_PID_MASK                   (3)
#define UX_SYNERGY_HC_PIPECTR_PIDNAK                     (0)
#define UX_SYNERGY_HC_PIPECTR_PIDBUF                     (1)
#define UX_SYNERGY_HC_PIPECTR_PIDSTALL                   (2)
#define UX_SYNERGY_HC_PIPECTR_PIDSTALL2                  (3)
#define UX_SYNERGY_HC_PIPECTR_DATA1                      (1U<<7)
#define UX_SYNERGY_HC_PIPECTR_DATA0                      (1U<<8)

/**Define Synergy static definition.  */
/** This macro is used for checking the available bandwidth for periodic transfers(Isochronous and Interrupt) */
/** Maximum bandwidth is calculated as {2048byes(2x ISO PIPEs) + 256bytes(4x INT PIPEs)} for high-speed operation.
 */
#define UX_SYNERGY_HC_AVAILABLE_BANDWIDTH                (2304UL)

#define UX_SYNERGY_HC_INIT_DELAY                         (1000)
#define UX_SYNERGY_HC_RESET_RETRY                        (1000)
#define UX_SYNERGY_HC_RESET_DELAY                        (10)
#define UX_SYNERGY_HC_PORT_RESET_RETRY                   (50)
#define UX_SYNERGY_HC_FORCE_PORT_RESET_RETRY             (50)
#define UX_SYNERGY_HC_FORCE_PORT_RESET_DELAY             (1)
#define UX_SYNERGY_HC_CHECK_PORT_RESET_RETRY             (500)
#define UX_SYNERGY_HC_PORT_RESET_DELAY                   (300)
#define UX_SYNERGY_HC_PORT_RESET_RECOVERY_DELAY          (100)

/**Define Synergy initialization values.  */
#define UX_SYNERGY_HC_COMMAND_STATUS_RESET               (0)
#define UX_SYNERGY_HC_INIT_RESET_DELAY                   (10)
#define UX_SYNERGY_HC_MAX_BUF_SIZE                       (64)
#define UX_SYNERGY_HC_BUF_BLOCK_SIZE                     (64)
#define UX_SYNERGY_HC_MAX_BUF_SIZE_PIPE1_to_2_FS         (256)
#define UX_SYNERGY_HC_MAX_BUF_SIZE_PIPE3_to_9_FS         (64)
#define UX_SYNERGY_HC_MAX_BUF_SIZE_PIPE1_to_2_HS         (1024)
#define UX_SYNERGY_HC_MAX_BUF_SIZE_PIPE3_to_5_HS         (512)
#define UX_SYNERGY_HC_MAX_BUF_SIZE_PIPE6_to_9_HS         (64)
#define UX_SYNERGY_HC_MAX_BUF_NUM                        (135)
#define UX_SYNERGY_HC_PIPE1_BUF_START_NUM                (8)

/**Define Synergy FIFO write completion code.  */
#define UX_SYNERGY_HC_FIFO_WRITING                       (2)
#define UX_SYNERGY_HC_FIFO_WRITE_END                     (3)
#define UX_SYNERGY_HC_FIFO_WRITE_SHORT                   (4)
#define UX_SYNERGY_HC_FIFO_WRITE_DMA                     (5)
#define UX_SYNERGY_HC_FIFO_WRITE_ERROR                   (6)

/**Define Synergy FIFO read completion code.  */
#define UX_SYNERGY_HC_FIFO_READING                       (2)
#define UX_SYNERGY_HC_FIFO_READ_END                      (3)
#define UX_SYNERGY_HC_FIFO_READ_SHORT                    (4)
#define UX_SYNERGY_HC_FIFO_READ_DMA                      (5)
#define UX_SYNERGY_HC_FIFO_READ_ERROR                    (6)
#define UX_SYNERGY_HC_FIFO_READ_OVER                     (7)

/**Define Synergy physical endpoint definitions.  */
#define UX_SYNERGY_HC_ED_BRDY                            (0x00000001U)
#define UX_SYNERGY_HC_ED_NRDY                            (0x00000002U)
#define UX_SYNERGY_HC_ED_BEMP                            (0x00000004U)
#define UX_SYNERGY_HC_ED_EOFERR                          (0x00000010U)
#define UX_SYNERGY_HC_ED_SIGN                            (0x00000020U)
#define UX_SYNERGY_HC_ED_SACK                            (0x00000040U)
#define UX_SYNERGY_HC_ED_TIMEOUT                         (0x00000080U)

/**PHY Cross Point Adjustment, note that Hardware Manual to be updated(0xE->0x5) */
#define UX_SYNERGY_HC_PHYSLEW_SLEW_SLEWR00               (1U<<0)
#define UX_SYNERGY_HC_PHYSLEW_SLEW_SLEWR01               (1U<<1)
#define UX_SYNERGY_HC_PHYSLEW_SLEW_SLEWF00               (1U<<2)
#define UX_SYNERGY_HC_PHYSLEW_SLEW_SLEWF01               (1U<<3)

#define UX_SYNERGY_HC_LPSTS_SUSPENDM                     (1U<<14)

/**Define Synergy Root hub states.  */
#define UX_SYNERGY_HC_PORT_ENABLED                       (1)
#define UX_SYNERGY_HC_PORT_DISABLED                      (0)
#define UX_SYNERGY_HC_PORT_INEOFERR                      (3)


/**Define synergy transfer structure*/
typedef struct UX_HCD_SYNERGY_TRANSFER_STRUCT
{
    transfer_instance_t *ux_synergy_transfer_tx;
    transfer_instance_t *ux_synergy_transfer_rx;

} UX_HCD_SYNERGY_TRANSFER;

/**Define Synergy structure.  */
typedef struct UX_HCD_SYNERGY_STRUCT
{

    struct UX_HCD_STRUCT
                    *ux_hcd_synergy_hcd_owner;
    ULONG           ux_hcd_synergy_base;
    ULONG           ux_hcd_synergy_hcor;
    UINT            ux_hcd_synergy_nb_root_hubs;
    ULONG           ux_hcd_synergy_port_status;
    ULONG           ux_hcd_synergy_frame_number;
    ULONG           ux_hcd_synergy_root_hub_device_address;
    struct UX_SYNERGY_ED_STRUCT         
                    *ux_hcd_synergy_ed_list;
    struct UX_SYNERGY_TD_STRUCT         
                    *ux_hcd_synergy_td_list;
    struct UX_SYNERGY_ISO_TD_STRUCT     
                    *ux_hcd_synergy_iso_td_list;
    struct UX_SYNERGY_ED_STRUCT         
                    *ux_hcd_synergy_asynch_head_ed;   
    struct UX_SYNERGY_ED_STRUCT         
                    *ux_hcd_synergy_asynch_current_ed;              
    struct UX_SYNERGY_ED_STRUCT         
                    *ux_hcd_synergy_iso_head_ed;
    struct UX_SYNERGY_ED_STRUCT         
                    *ux_hcd_synergy_iso_current_ed;
    struct UX_SYNERGY_ED_STRUCT
                    *ux_hcd_synergy_interrupt_ed_list[32];
    UINT            ux_hcd_synergy_queue_empty;
    UINT            ux_hcd_synergy_periodic_scheduler_active;
    ULONG           ux_hcd_synergy_number_tds;
    UINT            ux_hcd_synergy_interruptible;
    ULONG           ux_hcd_synergy_interrupt_count;
    ULONG           ux_hcd_synergy_intsts0;
    ULONG           ux_hcd_synergy_intsts1;
    ULONG           ux_synergy_device_attached;
    ULONG           ux_synergy_next_available_bufnum;    ///< will need to implement some type of dynamic buffer management, for now just carve off */
    ULONG           ux_hcd_synergy_ed_irq[10];
    struct UX_SYNERGY_ED_STRUCT  
                    *ux_hcd_synergy_ed_ptr[10];
    UX_HCD_SYNERGY_TRANSFER  ux_hcd_synergy_transfer;
    transfer_cfg_t  ux_hcd_synergy_transfer_cfg_instance_tx;
    transfer_cfg_t  ux_hcd_synergy_transfer_cfg_instance_rx;
    TX_SEMAPHORE    ux_hcd_synergy_semaphore_tx;
    TX_SEMAPHORE    ux_hcd_synergy_semaphore_rx;
    USHORT          remaining_payload_bytes;
    UCHAR           * payload_buffer;


} UX_HCD_SYNERGY;

/**Define SYNERGY Payload Transfer structure */
typedef struct UX_HCD_SYNERGY_PAYLOAD_TRANSFER_STRUCT
{
    UCHAR * payload_buffer;        ///< Destination buffer address 
    ULONG   payload_length;        ///< Payload length to transmit 
    UINT    transfer_block_count;  ////< Number of transfer 
    UCHAR   transfer_width;        ///< Bytes per transfer 
} UX_HCD_SYNERGY_PAYLOAD_TRANSFER;

/** Define SYNERGY fifo structure */
typedef struct UX_HCD_SYNERGY_FIFO_STRUCT
{
    ULONG   fifo_sel;          ///< FIFO type 
    VOID  * fifo_addr;         ///< Selected FIFO address 
    ULONG   fifo_ctrl;         ///< Selected FIFO control 
} UX_HCD_SYNERGY_FIFO;

/**Define Synergy  ED structure.  */

typedef struct UX_SYNERGY_ED_STRUCT
{

    struct UX_SYNERGY_TD_STRUCT        
                    *ux_synergy_ed_tail_td;
    struct UX_SYNERGY_TD_STRUCT        
                    *ux_synergy_ed_head_td;
    struct UX_SYNERGY_ED_STRUCT        
                    *ux_synergy_ed_next_ed;
    struct UX_SYNERGY_ED_STRUCT        
                    *ux_synergy_ed_previous_ed;

    ULONG           ux_synergy_ed_status;
    struct UX_ENDPOINT_STRUCT          
                    *ux_synergy_ed_endpoint;
    ULONG           ux_synergy_ed_toggle;   
    ULONG           ux_synergy_ed_frame;   

    ULONG           ux_synergy_endpoint_index; 
    ULONG           ux_synergy_pipe_index; 
    ULONG           ux_synergy_fifo_index; 

    ULONG           ux_synergy_buffer_size;
    ULONG           ux_synergy_buffer_number;
    USHORT          ux_synergy_devaddm_val;

} UX_SYNERGY_ED;


/**Define Synergy ED bitmap.  */

#define UX_SYNERGY_ED_STATIC                                (0x80000000)
#define UX_SYNERGY_ED_SKIP                                  (0x40000000UL)

/**Define Synergy TD structure.  */

typedef struct UX_SYNERGY_TD_STRUCT
{                                                

    UCHAR *         ux_synergy_td_buffer;
    ULONG           ux_synergy_td_length;
    struct UX_SYNERGY_TD_STRUCT        
                    *ux_synergy_td_next_td;
    struct UX_TRANSFER_STRUCT          
                    *ux_synergy_td_transfer_request;
    struct UX_SYNERGY_TD_STRUCT        
                    *ux_synergy_td_next_td_transfer_request;
    struct UX_SYNERGY_ED_STRUCT        
                    *ux_synergy_td_ed;
    ULONG           ux_synergy_td_actual_length;
    ULONG           ux_synergy_td_status;
    ULONG           ux_synergy_td_direction;
    ULONG           ux_synergy_td_toggle;
    ULONG           ux_synergy_td_transfer_type; 
    ULONG           ux_synergy_td_error_count;

} UX_SYNERGY_TD;


/**Define Synergy TD bitmap.  */

#define UX_SYNERGY_TD_SETUP_PHASE                           (0x00010000)
#define UX_SYNERGY_TD_DATA_PHASE                            (0x00020000)
#define UX_SYNERGY_TD_STATUS_PHASE                          (0x00040000)
#define UX_SYNERGY_TD_OUT                                   (0x00000800)
#define UX_SYNERGY_TD_IN                                    (0x00001000)
#define UX_SYNERGY_TD_TOGGLE_FROM_ED                        (0x80000000)
#define UX_SYNERGY_TD_ACK_PENDING                           (0x00080000)


#define UX_SYNERGY_TD_SETUP_TYPE                            (1)
#define UX_SYNERGY_TD_DATA_TYPE                             (2)
#define UX_SYNERGY_TD_STATUS_TYPE                           (3)
#define UX_SYNERGY_TD_MAX_ERROR                             (3)

/**Define Synergy ISOCHRONOUS TD structure.  */

typedef struct UX_SYNERGY_ISO_TD_STRUCT
{

    UCHAR *         ux_synergy_iso_td_buffer;
    ULONG           ux_synergy_iso_td_length;
    struct UX_SYNERGY_ISO_TD_STRUCT    
                    *ux_synergy_iso_td_next_td;
    struct UX_TRANSFER_STRUCT          
                    *ux_synergy_iso_td_transfer_request;
    struct UX_SYNERGY_ISO_TD_STRUCT    
                    *ux_synergy_iso_td_next_td_transfer_request;
    struct UX_SYNERGY_ED_STRUCT        
                    *ux_synergy_iso_td_ed;
    ULONG           ux_synergy_iso_td_actual_length;
    ULONG           ux_synergy_iso_td_status;
    ULONG           ux_synergy_iso_td_direction;
    
} UX_SYNERGY_ISO_TD;

/*******************************************************************************************************************//**
 * @} (end defgroup sf_el_ux)
 **********************************************************************************************************************/

/* Define Synergy function prototypes.  */

VOID    ux_hcd_synergy_asynch_queue_process(UX_HCD_SYNERGY *hcd_synergy);
VOID    ux_hcd_synergy_asynch_schedule(UX_HCD_SYNERGY *hcd_synergy);
UINT    ux_hcd_synergy_asynchronous_endpoint_create(UX_HCD_SYNERGY *hcd_synergy, UX_ENDPOINT *endpoint);
UINT    ux_hcd_synergy_asynchronous_endpoint_destroy(UX_HCD_SYNERGY *hcd_synergy, UX_ENDPOINT *endpoint);
UINT    ux_hcd_synergy_control_endpoint_create(UX_HCD_SYNERGY *hcd_synergy, UX_ENDPOINT *endpoint);
UINT    ux_hcd_synergy_bulk_endpoint_create(UX_HCD_SYNERGY *hcd_synergy, UX_ENDPOINT *endpoint);
UINT    ux_hcd_synergy_control_td_add(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
UINT    ux_hcd_synergy_bulk_int_td_add(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
UINT    ux_hcd_synergy_iso_td_add(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
UINT    ux_hcd_synergy_controller_disable(UX_HCD_SYNERGY *hcd_synergy);
UX_SYNERGY_ED       *ux_hcd_synergy_ed_obtain(UX_HCD_SYNERGY *hcd_synergy);
VOID    ux_hcd_synergy_ed_td_clean(UX_SYNERGY_ED *ed);
UINT    ux_hcd_synergy_endpoint_reset(UX_HCD_SYNERGY *hcd_synergy, UX_ENDPOINT *endpoint);
UINT    ux_hcd_synergy_entry(UX_HCD *hcd, UINT function, VOID *parameter);
UINT    ux_hcd_synergy_frame_number_get(UX_HCD_SYNERGY *hcd_synergy, ULONG *frame_number);
VOID    ux_hcd_synergy_frame_number_set(UX_HCD_SYNERGY *hcd_synergy, ULONG frame_number);
ULONG   ux_hcd_synergy_register_read(UX_HCD_SYNERGY *hcd_synergy, ULONG synergy_register);
VOID    ux_hcd_synergy_register_write(UX_HCD_SYNERGY *hcd_synergy, ULONG synergy_register, USHORT register_value);
VOID    ux_hcd_synergy_register_clear(UX_HCD_SYNERGY *hcd_synergy, ULONG synergy_register, USHORT register_value);
VOID    ux_hcd_synergy_register_status_clear(UX_HCD_SYNERGY *hcd_synergy, ULONG synergy_register, USHORT value);
VOID    ux_hcd_synergy_register_set(UX_HCD_SYNERGY *hcd_synergy, ULONG synergy_register, USHORT register_value);
UINT    ux_hcd_synergy_initialize(UX_HCD *hcd);
UINT    ux_hcd_synergy_interrupt_endpoint_create(UX_HCD_SYNERGY *hcd_synergy, UX_ENDPOINT *endpoint);
VOID    ux_hcd_synergy_interrupt_handler(UINT hcd_index);
VOID    ux_hcd_synergy_iso_queue_process(UX_HCD_SYNERGY *hcd_synergy);
VOID    ux_hcd_synergy_iso_schedule(UX_HCD_SYNERGY *hcd_synergy);
UINT    ux_hcd_synergy_isochronous_endpoint_create(UX_HCD_SYNERGY *hcd_synergy, UX_ENDPOINT *endpoint);
UX_SYNERGY_ISO_TD   * ux_hcd_synergy_isochronous_td_obtain(UX_HCD_SYNERGY *hcd_synergy);
UX_SYNERGY_ED       * ux_hcd_synergy_least_traffic_list_get(UX_HCD_SYNERGY *hcd_synergy);
UINT    ux_hcd_synergy_periodic_endpoint_destroy(UX_HCD_SYNERGY *hcd_synergy, UX_ENDPOINT *endpoint);
VOID    ux_hcd_synergy_periodic_schedule(UX_HCD_SYNERGY *hcd_synergy);
UINT    ux_hcd_synergy_periodic_tree_create(UX_HCD_SYNERGY *hcd_synergy);
UINT    ux_hcd_synergy_port_disable(UX_HCD_SYNERGY *hcd_synergy, ULONG port_index);
UINT    ux_hcd_synergy_port_enable(UX_HCD_SYNERGY *hcd_synergy, ULONG port_index);
UINT    ux_hcd_synergy_port_reset(UX_HCD_SYNERGY *hcd_synergy, ULONG port_index);
UINT    ux_hcd_synergy_port_resume(UX_HCD_SYNERGY *hcd_synergy, UINT port_index);
ULONG   ux_hcd_synergy_port_status_get(UX_HCD_SYNERGY *hcd_synergy, ULONG port_index);
UINT    ux_hcd_synergy_port_suspend(UX_HCD_SYNERGY *hcd_synergy, ULONG port_index);
UINT    ux_hcd_synergy_power_down_port(UX_HCD_SYNERGY *hcd_synergy, ULONG port_index);
UINT    ux_hcd_synergy_power_on_port(UX_HCD_SYNERGY *hcd_synergy, ULONG port_index);
VOID    ux_hcd_synergy_power_root_hubs(UX_HCD_SYNERGY *hcd_synergy);
UINT    ux_hcd_synergy_td_add(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
UX_SYNERGY_TD       * ux_hcd_synergy_regular_td_obtain(UX_HCD_SYNERGY *hcd_synergy);
UINT    ux_hcd_synergy_request_bulk_transfer(UX_HCD_SYNERGY *hcd_synergy, UX_TRANSFER *transfer_request);
UINT    ux_hcd_synergy_request_control_transfer(UX_HCD_SYNERGY *hcd_synergy, UX_TRANSFER *transfer_request);
UINT    ux_hcd_synergy_request_interrupt_transfer(UX_HCD_SYNERGY *hcd_synergy, UX_TRANSFER *transfer_request);
UINT    ux_hcd_synergy_request_isochronous_transfer(UX_HCD_SYNERGY *hcd_synergy, UX_TRANSFER *transfer_request);
UINT    ux_hcd_synergy_request_transfer(UX_HCD_SYNERGY *hcd_synergy, UX_TRANSFER *transfer_request);
UINT    ux_hcd_synergy_transfer_abort(UX_HCD_SYNERGY *hcd_synergy, UX_TRANSFER *transfer_request);
ULONG   ux_hcd_synergy_fifo_port_change(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed, ULONG direction);
VOID    ux_hcd_synergy_current_endpoint_change(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed, ULONG direction);
ULONG   ux_hcd_synergy_data_buffer_size(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
UINT    ux_hcd_synergy_buffer_write(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
UINT    ux_hcd_synergy_fifod_write(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
UINT    ux_hcd_synergy_fifoc_write(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
UINT    ux_hcd_synergy_fifo_read(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
UINT    ux_hcd_synergy_buffer_read(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
VOID    ux_hcd_synergy_buffer_ready_interrupt(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed, ULONG flag);
VOID    ux_hcd_synergy_buffer_empty_interrupt(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed, ULONG flag);
VOID    ux_hcd_synergy_endpoint_nak_set(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
VOID    ux_hcd_synergy_asynch_queue_process_bemp(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
VOID    ux_hcd_synergy_asynch_queue_process_nrdy(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
VOID    ux_hcd_synergy_asynch_queue_process_brdy(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
VOID    ux_hcd_synergy_asynch_queue_process_sign(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
VOID    ux_hcd_synergy_iso_queue_process_bemp(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
VOID    ux_hcd_synergy_iso_queue_process_nrdy(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
VOID    ux_hcd_synergy_iso_queue_process_brdy(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed);
VOID    ux_hcd_synergy_buffer_notready_interrupt(UX_HCD_SYNERGY *hcd_synergy, UX_SYNERGY_ED *ed, ULONG flag);
UINT    ux_hcd_synergy_initialize_transfer_support(UX_HCD *hcd, const UX_HCD_SYNERGY_TRANSFER *p_transfer_instance);
VOID    ux_hcd_synergy_fifo_write_software_copy(UX_HCD_SYNERGY *hcd_synergy,
                                    ULONG payload_length, UCHAR *payload_buffer, VOID * fifo_addr, ULONG fifo_sel);
VOID    ux_hcd_synergy_fifo_write_software_copy_remaining_bytes(UX_HCD_SYNERGY *hcd_synergy,
                                    ULONG payload_length, UCHAR *payload_buffer, VOID * fifo_addr);
UINT ux_hcd_synergy_disable(ULONG ux_hcd_io);
UINT ux_hcd_synergy_uninitialize(ULONG ux_hcd_io);
UINT ux_hcd_synergy_uninitialize_transfer_support(UX_HCD_SYNERGY *hcd_synergy);
/*******************************************************************************************************************//**
 * @brief: This function is used to calculate timer ticks for the specified number of milliseconds.
 *
 * @param [in] time_ms   Time in milliseconds
 * @return timer ticks
 **********************************************************************************************************************/
__STATIC_INLINE ULONG ux_ms_to_ticks(ULONG time_ms)
{
    return (((time_ms * TX_TIMER_TICKS_PER_SECOND) / 1000U) + 1U);
}

#endif

