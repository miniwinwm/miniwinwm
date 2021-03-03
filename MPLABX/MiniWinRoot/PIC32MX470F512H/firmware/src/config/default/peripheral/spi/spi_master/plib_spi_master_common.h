/*******************************************************************************
  SPI PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_spi_master_common.h

  Summary:
    SPI PLIB Master Common Header File

  Description:
    This file has prototype of all the interfaces which are common for all the
    SPI peripherals.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2018-2019 Microchip Technology Inc. and its subsidiaries.
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

#ifndef PLIB_SPI_MASTER_COMMON_H
#define PLIB_SPI_MASTER_COMMON_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


/* Provide C++ Compatibility */
#ifdef __cplusplus

    extern "C" {

#endif

/****************************** SPI${SPI_INDEX?string} Interface *********************************/

typedef enum
{
    SPI_CLOCK_PHASE_TRAILING_EDGE = 0x00000000,
    SPI_CLOCK_PHASE_LEADING_EDGE = 0x00000100,

    /* Force the compiler to reserve 32-bit space for each enum value */
    SPI_CLOCK_PHASE_INVALID = 0xFFFFFFFF

}SPI_CLOCK_PHASE;

typedef enum
{
    SPI_CLOCK_POLARITY_IDLE_LOW = 0x00000000,
    SPI_CLOCK_POLARITY_IDLE_HIGH = 0x00000040,

    /* Force the compiler to reserve 32-bit space for each enum value */
    SPI_CLOCK_POLARITY_INVALID = 0xFFFFFFFF

}SPI_CLOCK_POLARITY;

typedef enum
{
    SPI_DATA_BITS_8 = 0x00000000,
    SPI_DATA_BITS_16 = 0x00000400,
    SPI_DATA_BITS_32 = 0x00000800,

    /* Force the compiler to reserve 32-bit space for each enum value */
    SPI_DATA_BITS_INVALID = 0xFFFFFFFF

}SPI_DATA_BITS;

typedef struct
{
    uint32_t    clockFrequency;
    SPI_CLOCK_PHASE clockPhase;
    SPI_CLOCK_POLARITY clockPolarity;
    SPI_DATA_BITS   dataBits;

}SPI_TRANSFER_SETUP;

typedef  void (*SPI_CALLBACK) (uintptr_t context);

// *****************************************************************************
// *****************************************************************************
// Section: Local: **** Do Not Use ****
// *****************************************************************************
// *****************************************************************************

typedef struct
{
    void*                   txBuffer;
    void*                   rxBuffer;
    size_t                  txSize;
    size_t                  rxSize;
    size_t                  dummySize;
    size_t                  rxCount;
    size_t                  txCount;
    bool                    transferIsBusy;
    SPI_CALLBACK            callback;
    uintptr_t               context;

} SPI_OBJECT ;

/* Provide C++ Compatibility */
#ifdef __cplusplus

    }

#endif

#endif // PLIB_SPI_MASTER_COMMON_H