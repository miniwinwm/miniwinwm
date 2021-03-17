/*******************************************************************************
  GPIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.h

  Summary:
    GPIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (GPIO) module.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#ifndef PLIB_GPIO_H
#define PLIB_GPIO_H

#include <device.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************


/*** Macros for LCD_RESET pin ***/
#define LCD_RESET_Set()               (LATASET = (1<<5))
#define LCD_RESET_Clear()             (LATACLR = (1<<5))
#define LCD_RESET_Toggle()            (LATAINV= (1<<5))
#define LCD_RESET_OutputEnable()      (TRISACLR = (1<<5))
#define LCD_RESET_InputEnable()       (TRISASET = (1<<5))
#define LCD_RESET_Get()               ((PORTA >> 5) & 0x1)
#define LCD_RESET_PIN                  GPIO_PIN_RA5

/*** Macros for D0 pin ***/
#define D0_Set()               (LATCSET = (1<<1))
#define D0_Clear()             (LATCCLR = (1<<1))
#define D0_Toggle()            (LATCINV= (1<<1))
#define D0_OutputEnable()      (TRISCCLR = (1<<1))
#define D0_InputEnable()       (TRISCSET = (1<<1))
#define D0_Get()               ((PORTC >> 1) & 0x1)
#define D0_PIN                  GPIO_PIN_RC1

/*** Macros for D1 pin ***/
#define D1_Set()               (LATCSET = (1<<2))
#define D1_Clear()             (LATCCLR = (1<<2))
#define D1_Toggle()            (LATCINV= (1<<2))
#define D1_OutputEnable()      (TRISCCLR = (1<<2))
#define D1_InputEnable()       (TRISCSET = (1<<2))
#define D1_Get()               ((PORTC >> 2) & 0x1)
#define D1_PIN                  GPIO_PIN_RC2

/*** Macros for D2 pin ***/
#define D2_Set()               (LATCSET = (1<<3))
#define D2_Clear()             (LATCCLR = (1<<3))
#define D2_Toggle()            (LATCINV= (1<<3))
#define D2_OutputEnable()      (TRISCCLR = (1<<3))
#define D2_InputEnable()       (TRISCSET = (1<<3))
#define D2_Get()               ((PORTC >> 3) & 0x1)
#define D2_PIN                  GPIO_PIN_RC3

/*** Macros for D3 pin ***/
#define D3_Set()               (LATCSET = (1<<4))
#define D3_Clear()             (LATCCLR = (1<<4))
#define D3_Toggle()            (LATCINV= (1<<4))
#define D3_OutputEnable()      (TRISCCLR = (1<<4))
#define D3_InputEnable()       (TRISCSET = (1<<4))
#define D3_Get()               ((PORTC >> 4) & 0x1)
#define D3_PIN                  GPIO_PIN_RC4

/*** Macros for PLK pin ***/
#define PLK_Set()               (LATBSET = (1<<4))
#define PLK_Clear()             (LATBCLR = (1<<4))
#define PLK_Toggle()            (LATBINV= (1<<4))
#define PLK_OutputEnable()      (TRISBCLR = (1<<4))
#define PLK_InputEnable()       (TRISBSET = (1<<4))
#define PLK_Get()               ((PORTB >> 4) & 0x1)
#define PLK_PIN                  GPIO_PIN_RB4

/*** Macros for D6 pin ***/
#define D6_Set()               (LATASET = (1<<9))
#define D6_Clear()             (LATACLR = (1<<9))
#define D6_Toggle()            (LATAINV= (1<<9))
#define D6_OutputEnable()      (TRISACLR = (1<<9))
#define D6_InputEnable()       (TRISASET = (1<<9))
#define D6_Get()               ((PORTA >> 9) & 0x1)
#define D6_PIN                  GPIO_PIN_RA9

/*** Macros for LCD_DC pin ***/
#define LCD_DC_Set()               (LATASET = (1<<1))
#define LCD_DC_Clear()             (LATACLR = (1<<1))
#define LCD_DC_Toggle()            (LATAINV= (1<<1))
#define LCD_DC_OutputEnable()      (TRISACLR = (1<<1))
#define LCD_DC_InputEnable()       (TRISASET = (1<<1))
#define LCD_DC_Get()               ((PORTA >> 1) & 0x1)
#define LCD_DC_PIN                  GPIO_PIN_RA1

/*** Macros for TS_IRQ pin ***/
#define TS_IRQ_Set()               (LATFSET = (1<<12))
#define TS_IRQ_Clear()             (LATFCLR = (1<<12))
#define TS_IRQ_Toggle()            (LATFINV= (1<<12))
#define TS_IRQ_OutputEnable()      (TRISFCLR = (1<<12))
#define TS_IRQ_InputEnable()       (TRISFSET = (1<<12))
#define TS_IRQ_Get()               ((PORTF >> 12) & 0x1)
#define TS_IRQ_PIN                  GPIO_PIN_RF12

/*** Macros for LCD_CS pin ***/
#define LCD_CS_Set()               (LATFSET = (1<<2))
#define LCD_CS_Clear()             (LATFCLR = (1<<2))
#define LCD_CS_Toggle()            (LATFINV= (1<<2))
#define LCD_CS_OutputEnable()      (TRISFCLR = (1<<2))
#define LCD_CS_InputEnable()       (TRISFSET = (1<<2))
#define LCD_CS_Get()               ((PORTF >> 2) & 0x1)
#define LCD_CS_PIN                  GPIO_PIN_RF2

/*** Macros for D4 pin ***/
#define D4_Set()               (LATASET = (1<<3))
#define D4_Clear()             (LATACLR = (1<<3))
#define D4_Toggle()            (LATAINV= (1<<3))
#define D4_OutputEnable()      (TRISACLR = (1<<3))
#define D4_InputEnable()       (TRISASET = (1<<3))
#define D4_Get()               ((PORTA >> 3) & 0x1)
#define D4_PIN                  GPIO_PIN_RA3

/*** Macros for D5 pin ***/
#define D5_Set()               (LATASET = (1<<4))
#define D5_Clear()             (LATACLR = (1<<4))
#define D5_Toggle()            (LATAINV= (1<<4))
#define D5_OutputEnable()      (TRISACLR = (1<<4))
#define D5_InputEnable()       (TRISASET = (1<<4))
#define D5_Get()               ((PORTA >> 4) & 0x1)
#define D5_PIN                  GPIO_PIN_RA4

/*** Macros for SCL1 pin ***/
#define SCL1_Get()               ((PORTA >> 14) & 0x1)
#define SCL1_PIN                  GPIO_PIN_RA14

/*** Macros for SDA1 pin ***/
#define SDA1_Get()               ((PORTA >> 15) & 0x1)
#define SDA1_PIN                  GPIO_PIN_RA15

/*** Macros for VS pin ***/
#define VS_Set()               (LATDSET = (1<<3))
#define VS_Clear()             (LATDCLR = (1<<3))
#define VS_Toggle()            (LATDINV= (1<<3))
#define VS_OutputEnable()      (TRISDCLR = (1<<3))
#define VS_InputEnable()       (TRISDSET = (1<<3))
#define VS_Get()               ((PORTD >> 3) & 0x1)
#define VS_PIN                  GPIO_PIN_RD3

/*** Macros for HS pin ***/
#define HS_Set()               (LATDSET = (1<<4))
#define HS_Clear()             (LATDCLR = (1<<4))
#define HS_Toggle()            (LATDINV= (1<<4))
#define HS_OutputEnable()      (TRISDCLR = (1<<4))
#define HS_InputEnable()       (TRISDSET = (1<<4))
#define HS_Get()               ((PORTD >> 4) & 0x1)
#define HS_PIN                  GPIO_PIN_RD4

/*** Macros for TS_CS pin ***/
#define TS_CS_Set()               (LATDSET = (1<<5))
#define TS_CS_Clear()             (LATDCLR = (1<<5))
#define TS_CS_Toggle()            (LATDINV= (1<<5))
#define TS_CS_OutputEnable()      (TRISDCLR = (1<<5))
#define TS_CS_InputEnable()       (TRISDSET = (1<<5))
#define TS_CS_Get()               ((PORTD >> 5) & 0x1)
#define TS_CS_PIN                  GPIO_PIN_RD5

/*** Macros for D7 pin ***/
#define D7_Set()               (LATASET = (1<<6))
#define D7_Clear()             (LATACLR = (1<<6))
#define D7_Toggle()            (LATAINV= (1<<6))
#define D7_OutputEnable()      (TRISACLR = (1<<6))
#define D7_InputEnable()       (TRISASET = (1<<6))
#define D7_Get()               ((PORTA >> 6) & 0x1)
#define D7_PIN                  GPIO_PIN_RA6

/*** Macros for S1 pin ***/
#define S1_Set()               (LATGSET = (1<<12))
#define S1_Clear()             (LATGCLR = (1<<12))
#define S1_Toggle()            (LATGINV= (1<<12))
#define S1_OutputEnable()      (TRISGCLR = (1<<12))
#define S1_InputEnable()       (TRISGSET = (1<<12))
#define S1_Get()               ((PORTG >> 12) & 0x1)
#define S1_PIN                  GPIO_PIN_RG12

/*** Macros for LED1 pin ***/
#define LED1_Set()               (LATESET = (1<<3))
#define LED1_Clear()             (LATECLR = (1<<3))
#define LED1_Toggle()            (LATEINV= (1<<3))
#define LED1_OutputEnable()      (TRISECLR = (1<<3))
#define LED1_InputEnable()       (TRISESET = (1<<3))
#define LED1_Get()               ((PORTE >> 3) & 0x1)
#define LED1_PIN                  GPIO_PIN_RE3


// *****************************************************************************
/* GPIO Port

  Summary:
    Identifies the available GPIO Ports.

  Description:
    This enumeration identifies the available GPIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/

typedef enum
{
    GPIO_PORT_A = 0,
    GPIO_PORT_B = 1,
    GPIO_PORT_C = 2,
    GPIO_PORT_D = 3,
    GPIO_PORT_E = 4,
    GPIO_PORT_F = 5,
    GPIO_PORT_G = 6,
} GPIO_PORT;

// *****************************************************************************
/* GPIO Port Pins

  Summary:
    Identifies the available GPIO port pins.

  Description:
    This enumeration identifies the available GPIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/

typedef enum
{
    GPIO_PIN_RA0 = 0,
    GPIO_PIN_RA1 = 1,
    GPIO_PIN_RA2 = 2,
    GPIO_PIN_RA3 = 3,
    GPIO_PIN_RA4 = 4,
    GPIO_PIN_RA5 = 5,
    GPIO_PIN_RA6 = 6,
    GPIO_PIN_RA7 = 7,
    GPIO_PIN_RA9 = 9,
    GPIO_PIN_RA10 = 10,
    GPIO_PIN_RA14 = 14,
    GPIO_PIN_RA15 = 15,
    GPIO_PIN_RB0 = 16,
    GPIO_PIN_RB1 = 17,
    GPIO_PIN_RB2 = 18,
    GPIO_PIN_RB3 = 19,
    GPIO_PIN_RB4 = 20,
    GPIO_PIN_RB5 = 21,
    GPIO_PIN_RB6 = 22,
    GPIO_PIN_RB7 = 23,
    GPIO_PIN_RB8 = 24,
    GPIO_PIN_RB9 = 25,
    GPIO_PIN_RB10 = 26,
    GPIO_PIN_RB11 = 27,
    GPIO_PIN_RB12 = 28,
    GPIO_PIN_RB13 = 29,
    GPIO_PIN_RB14 = 30,
    GPIO_PIN_RB15 = 31,
    GPIO_PIN_RC1 = 33,
    GPIO_PIN_RC2 = 34,
    GPIO_PIN_RC3 = 35,
    GPIO_PIN_RC4 = 36,
    GPIO_PIN_RC12 = 44,
    GPIO_PIN_RC13 = 45,
    GPIO_PIN_RC14 = 46,
    GPIO_PIN_RC15 = 47,
    GPIO_PIN_RD0 = 48,
    GPIO_PIN_RD1 = 49,
    GPIO_PIN_RD2 = 50,
    GPIO_PIN_RD3 = 51,
    GPIO_PIN_RD4 = 52,
    GPIO_PIN_RD5 = 53,
    GPIO_PIN_RD9 = 57,
    GPIO_PIN_RD10 = 58,
    GPIO_PIN_RD11 = 59,
    GPIO_PIN_RD12 = 60,
    GPIO_PIN_RD13 = 61,
    GPIO_PIN_RD14 = 62,
    GPIO_PIN_RD15 = 63,
    GPIO_PIN_RE0 = 64,
    GPIO_PIN_RE1 = 65,
    GPIO_PIN_RE2 = 66,
    GPIO_PIN_RE3 = 67,
    GPIO_PIN_RE4 = 68,
    GPIO_PIN_RE5 = 69,
    GPIO_PIN_RE6 = 70,
    GPIO_PIN_RE7 = 71,
    GPIO_PIN_RE8 = 72,
    GPIO_PIN_RE9 = 73,
    GPIO_PIN_RF0 = 80,
    GPIO_PIN_RF1 = 81,
    GPIO_PIN_RF2 = 82,
    GPIO_PIN_RF3 = 83,
    GPIO_PIN_RF4 = 84,
    GPIO_PIN_RF5 = 85,
    GPIO_PIN_RF8 = 88,
    GPIO_PIN_RF12 = 92,
    GPIO_PIN_RF13 = 93,
    GPIO_PIN_RG0 = 96,
    GPIO_PIN_RG1 = 97,
    GPIO_PIN_RG6 = 102,
    GPIO_PIN_RG7 = 103,
    GPIO_PIN_RG8 = 104,
    GPIO_PIN_RG9 = 105,
    GPIO_PIN_RG12 = 108,
    GPIO_PIN_RG13 = 109,
    GPIO_PIN_RG14 = 110,
    GPIO_PIN_RG15 = 111,

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
    GPIO_PIN_NONE = -1

} GPIO_PIN;


void GPIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t GPIO_PortRead(GPIO_PORT port);

void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value);

uint32_t GPIO_PortLatchRead ( GPIO_PORT port );

void GPIO_PortSet(GPIO_PORT port, uint32_t mask);

void GPIO_PortClear(GPIO_PORT port, uint32_t mask);

void GPIO_PortToggle(GPIO_PORT port, uint32_t mask);

void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void GPIO_PinWrite(GPIO_PIN pin, bool value)
{
    GPIO_PortWrite((GPIO_PORT)(pin>>4), (uint32_t)(0x1) << (pin & 0xF), (uint32_t)(value) << (pin & 0xF));
}

static inline bool GPIO_PinRead(GPIO_PIN pin)
{
    return (bool)(((GPIO_PortRead((GPIO_PORT)(pin>>4))) >> (pin & 0xF)) & 0x1);
}

static inline bool GPIO_PinLatchRead(GPIO_PIN pin)
{
    return (bool)((GPIO_PortLatchRead((GPIO_PORT)(pin>>4)) >> (pin & 0xF)) & 0x1);
}

static inline void GPIO_PinToggle(GPIO_PIN pin)
{
    GPIO_PortToggle((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinSet(GPIO_PIN pin)
{
    GPIO_PortSet((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinClear(GPIO_PIN pin)
{
    GPIO_PortClear((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinInputEnable(GPIO_PIN pin)
{
    GPIO_PortInputEnable((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinOutputEnable(GPIO_PIN pin)
{
    GPIO_PortOutputEnable((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_GPIO_H
