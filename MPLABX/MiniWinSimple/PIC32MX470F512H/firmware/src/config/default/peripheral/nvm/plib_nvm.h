/*******************************************************************************
  Non-Volatile Memory Controller(NVM) PLIB.

  Company:
    Microchip Technology Inc.

  File Name:
    plib_nvm.h

  Summary:
    Interface definition of NVM Plib.

  Description:
    This file defines the interface for the NVM Plib.
    It allows user to Program, Erase and lock the on-chip Non Volatile Flash
    Memory.

*******************************************************************************/
// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

#ifndef PLIB_NVM_H
#define PLIB_NVM_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "device.h"     // For device registers and uint32_t
#include <stdbool.h>    // For bool

// DOM-IGNORE-BEGIN
#ifdef __cplusplus // Provide C++ Compatibility

    extern "C" {

#endif

// DOM-IGNORE-END

#define NVM_FLASH_START_ADDRESS    (0x9d000000U)
#define NVM_FLASH_SIZE             (0x80000U)
#define NVM_FLASH_ROWSIZE          (512U)
#define NVM_FLASH_PAGESIZE         (4096U)


typedef enum
{
    /* No error */
    NVM_ERROR_NONE = 0x0,

    /* NVM write error */
    NVM_ERROR_WRITE = _NVMCON_WRERR_MASK,

    /* NVM Low Voltage Detect error */
    NVM_ERROR_LOWVOLTAGE = _NVMCON_LVDERR_MASK,

} NVM_ERROR;

typedef void (*NVM_CALLBACK)( uintptr_t context );

void NVM_Initialize( void );

bool NVM_Read( uint32_t *data, uint32_t length, const uint32_t address );

bool NVM_WordWrite( uint32_t data, uint32_t address );

bool NVM_RowWrite( uint32_t *data, uint32_t address );

bool NVM_PageErase( uint32_t address );

NVM_ERROR NVM_ErrorGet( void );

bool NVM_IsBusy( void );

void NVM_CallbackRegister( NVM_CALLBACK callback, uintptr_t context );

// DOM-IGNORE-BEGIN
#ifdef __cplusplus // Provide C++ Compatibility

    }

#endif

// DOM-IGNORE-END
#endif // PLIB_NVM_H
