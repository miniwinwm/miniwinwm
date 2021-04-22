/**
 * \file
 *
 * \brief All USB VIDs and PIDs from Atmel USB applications
 *
 * Copyright (c) 2009-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _USB_ATMEL_H_
#define _USB_ATMEL_H_

/**
 * \defgroup usb_group USB Stack
 *
 * This stack includes the USB Device Stack, USB Host Stack and common
 * definitions.
 * @{
 */

//! @}

/**
 * \ingroup usb_group
 * \defgroup usb_atmel_ids_group Atmel USB Identifiers
 *
 * This module defines Atmel PID and VIDs constants.
 *
 * @{
 */

//! \name Vendor Identifier assigned by USB org to ATMEL
#define  USB_VID_ATMEL                             0x03EB


//! \name Product Identifier assigned by ATMEL to AVR applications
//! @{

//! \name The range from 2000h to 20FFh is reserved to the old PID for C51, MEGA, and others.
//! @{
#define  USB_PID_ATMEL_MEGA_HIDGENERIC             0x2013
#define  USB_PID_ATMEL_MEGA_HIDKEYBOARD            0x2017
#define  USB_PID_ATMEL_MEGA_CDC                    0x2018
#define  USB_PID_ATMEL_MEGA_AUDIO_IN               0x2019
#define  USB_PID_ATMEL_MEGA_MS                     0x201A
#define  USB_PID_ATMEL_MEGA_AUDIO_IN_OUT           0x201B
#define  USB_PID_ATMEL_MEGA_HIDMOUSE               0x201C
#define  USB_PID_ATMEL_MEGA_HIDMOUSE_CERTIF_U4     0x201D
#define  USB_PID_ATMEL_MEGA_CDC_MULTI              0x201E
#define  USB_PID_ATMEL_MEGA_MS_HIDMS_HID_USBKEY    0x2022
#define  USB_PID_ATMEL_MEGA_MS_HIDMS_HID_STK525    0x2023
#define  USB_PID_ATMEL_MEGA_MS_2                   0x2029
#define  USB_PID_ATMEL_MEGA_MS_HIDMS               0x202A
#define  USB_PID_ATMEL_MEGA_MS_3                   0x2032
#define  USB_PID_ATMEL_MEGA_LIBUSB                 0x2050
//! @}

//! \name The range 2100h to 21FFh is reserved to PIDs for AVR Tools.
//! @{
#define  USB_PID_ATMEL_XPLAINED                    0x2122
#define  USB_PID_ATMEL_XMEGA_USB_ZIGBIT_2_4GHZ     0x214A
#define  USB_PID_ATMEL_XMEGA_USB_ZIGBIT_SUBGHZ     0x214B
//! @}

//! \name The range 2300h to 23FFh is reserved to PIDs for demo from ASF1.7=>
//! @{
#define  USB_PID_ATMEL_UC3_ENUM                    0x2300
#define  USB_PID_ATMEL_UC3_MS                      0x2301
#define  USB_PID_ATMEL_UC3_MS_SDRAM_LOADER         0x2302
#define  USB_PID_ATMEL_UC3_EVK1100_CTRLPANEL       0x2303
#define  USB_PID_ATMEL_UC3_HID                     0x2304
#define  USB_PID_ATMEL_UC3_EVK1101_CTRLPANEL_HID   0x2305
#define  USB_PID_ATMEL_UC3_EVK1101_CTRLPANEL_HID_MS 0x2306
#define  USB_PID_ATMEL_UC3_CDC                     0x2307
#define  USB_PID_ATMEL_UC3_AUDIO_MICRO             0x2308
#define  USB_PID_ATMEL_UC3_CDC_DEBUG               0x2310 // Virtual Com (debug interface) on EVK11xx
#define  USB_PID_ATMEL_UC3_AUDIO_SPEAKER_MICRO     0x2311
#define  USB_PID_ATMEL_UC3_CDC_MSC                 0x2312
//! @}

//! \name The range 2400h to 24FFh is reserved to PIDs for ASF applications
//! @{
#define  USB_PID_ATMEL_ASF_HIDMOUSE                0x2400
#define  USB_PID_ATMEL_ASF_HIDKEYBOARD             0x2401
#define  USB_PID_ATMEL_ASF_HIDGENERIC              0x2402
#define  USB_PID_ATMEL_ASF_MSC                     0x2403
#define  USB_PID_ATMEL_ASF_CDC                     0x2404
#define  USB_PID_ATMEL_ASF_PHDC                    0x2405
#define  USB_PID_ATMEL_ASF_HIDMTOUCH               0x2406
#define  USB_PID_ATMEL_ASF_MSC_HIDMOUSE            0x2420
#define  USB_PID_ATMEL_ASF_MSC_HIDS_CDC            0x2421
#define  USB_PID_ATMEL_ASF_MSC_HIDKEYBOARD         0x2422
#define  USB_PID_ATMEL_ASF_VENDOR_CLASS            0x2423
#define  USB_PID_ATMEL_ASF_MSC_CDC                 0x2424
#define  USB_PID_ATMEL_ASF_TWO_CDC                 0x2425
#define  USB_PID_ATMEL_ASF_SEVEN_CDC               0x2426
#define  USB_PID_ATMEL_ASF_XPLAIN_BC_POWERONLY     0x2430
#define  USB_PID_ATMEL_ASF_XPLAIN_BC_TERMINAL      0x2431
#define  USB_PID_ATMEL_ASF_XPLAIN_BC_TOUCH         0x2432
#define  USB_PID_ATMEL_ASF_AUDIO_SPEAKER           0x2433
#define  USB_PID_ATMEL_ASF_XMEGA_B1_XPLAINED       0x2434
//! @}

//! \name The range 2F00h to 2FFFh is reserved to official PIDs for AVR bootloaders
//! Note, !!!! don't use this range for demos or examples !!!!
//! @{
#define  USB_PID_ATMEL_DFU_ATXMEGA64C3             0x2FD6
#define  USB_PID_ATMEL_DFU_ATXMEGA128C3            0x2FD7
#define  USB_PID_ATMEL_DFU_ATXMEGA16C4             0x2FD8
#define  USB_PID_ATMEL_DFU_ATXMEGA32C4             0x2FD9
#define  USB_PID_ATMEL_DFU_ATXMEGA256C3            0x2FDA
#define  USB_PID_ATMEL_DFU_ATXMEGA384C3            0x2FDB
#define  USB_PID_ATMEL_DFU_ATUCL3_L4               0x2FDC
#define  USB_PID_ATMEL_DFU_ATXMEGA64A4U            0x2FDD
#define  USB_PID_ATMEL_DFU_ATXMEGA128A4U           0x2FDE

#define  USB_PID_ATMEL_DFU_ATXMEGA64B3             0x2FDF
#define  USB_PID_ATMEL_DFU_ATXMEGA128B3            0x2FE0
#define  USB_PID_ATMEL_DFU_ATXMEGA64B1             0x2FE1
#define  USB_PID_ATMEL_DFU_ATXMEGA256A3BU          0x2FE2
#define  USB_PID_ATMEL_DFU_ATXMEGA16A4U            0x2FE3
#define  USB_PID_ATMEL_DFU_ATXMEGA32A4U            0x2FE4
#define  USB_PID_ATMEL_DFU_ATXMEGA64A3U            0x2FE5
#define  USB_PID_ATMEL_DFU_ATXMEGA128A3U           0x2FE6
#define  USB_PID_ATMEL_DFU_ATXMEGA192A3U           0x2FE7
#define  USB_PID_ATMEL_DFU_ATXMEGA64A1U            0x2FE8
#define  USB_PID_ATMEL_DFU_ATUC3D                  0x2FE9
#define  USB_PID_ATMEL_DFU_ATXMEGA128B1            0x2FEA
#define  USB_PID_ATMEL_DFU_AT32UC3C                0x2FEB
#define  USB_PID_ATMEL_DFU_ATXMEGA256A3U           0x2FEC
#define  USB_PID_ATMEL_DFU_ATXMEGA128A1U           0x2FED
#define  USB_PID_ATMEL_DFU_ATMEGA8U2               0x2FEE
#define  USB_PID_ATMEL_DFU_ATMEGA16U2              0x2FEF
#define  USB_PID_ATMEL_DFU_ATMEGA32U2              0x2FF0
#define  USB_PID_ATMEL_DFU_AT32UC3A3               0x2FF1
#define  USB_PID_ATMEL_DFU_ATMEGA32U6              0x2FF2
#define  USB_PID_ATMEL_DFU_ATMEGA16U4              0x2FF3
#define  USB_PID_ATMEL_DFU_ATMEGA32U4              0x2FF4
#define  USB_PID_ATMEL_DFU_AT32AP7200              0x2FF5
#define  USB_PID_ATMEL_DFU_AT32UC3B                0x2FF6
#define  USB_PID_ATMEL_DFU_AT90USB82               0x2FF7
#define  USB_PID_ATMEL_DFU_AT32UC3A                0x2FF8
#define  USB_PID_ATMEL_DFU_AT90USB64               0x2FF9
#define  USB_PID_ATMEL_DFU_AT90USB162              0x2FFA
#define  USB_PID_ATMEL_DFU_AT90USB128              0x2FFB
// 2FFCh to 2FFFh used by C51 family products
//! @}

//! @}

//! @}


#endif // _USB_ATMEL_H_
