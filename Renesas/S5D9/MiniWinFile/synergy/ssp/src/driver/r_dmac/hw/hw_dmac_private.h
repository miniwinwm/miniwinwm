/***********************************************************************************************************************
 * Copyright [2015-2021] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
 * 
 * This file is part of Renesas SynergyTM Software Package (SSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas SSP license agreement. Unless otherwise agreed in an SSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * File Name    : hw_dmac_private.h
 * Description  : DMAC register access function prototypes.
 **********************************************************************************************************************/

#ifndef HW_DMAC_PRIVATE_H
#define HW_DMAC_PRIVATE_H

/**********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "r_dmac.h"
#include "bsp_api.h"

/* Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER


/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/
typedef enum e_dmac_transfer_enable
{
    DMAC_TRANSFER_DISABLE = 0,
    DMAC_TRANSFER_ENABLE  = 1
} dmac_transfer_enable_t;

/** Select transfer request source (activates transfer). */
typedef enum e_dmac_transfer_request_source
{
    DMAC_TRANSFER_REQUEST_SOURCE_SOFTWARE,   ///< Start transfer in software
    DMAC_TRANSFER_REQUEST_SOURCE_INTERRUPT   ///< Start transfer by interrupt source
} dmac_transfer_request_source_t;

/** Extended repeat area. */
typedef enum e_dmac_extended_repeat_area
{
    DMAC_EXTENDED_REPEAT_AREA_NONE       = 0,     ///< Extended repeat area unused
    DMAC_EXTENDED_REPEAT_AREA_2_BYTES    = 1,     ///< 2 byte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_4_BYTES    = 2,     ///< 4 byte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_8_BYTES    = 3,     ///< 8 byte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_16_BYTES   = 4,     ///< 16 byte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_32_BYTES   = 5,     ///< 32 byte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_64_BYTES   = 6,     ///< 64 byte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_128_BYTES  = 7,     ///< 128 byte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_256_BYTES  = 8,     ///< 256 byte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_512_BYTES  = 9,     ///< 512 byte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_1_KBYTE    = 10,    ///< 1 kilobyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_2_KBYTES   = 11,    ///< 2 kilobyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_4_KBYTES   = 12,    ///< 4 kilobyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_8_KBYTES   = 13,    ///< 8 kilobyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_16_KBYTES  = 14,    ///< 16 kilobyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_32_KBYTES  = 15,    ///< 32 kilobyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_64_KBYTES  = 16,    ///< 64 kilobyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_128_KBYTES = 17,    ///< 128 kilobyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_256_KBYTES = 18,    ///< 256 kilobyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_512_KBYTES = 19,    ///< 512 kilobyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_1_MBYTE    = 20,    ///< 1 megabyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_2_MBYTES   = 21,    ///< 2 megabyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_4_MBYTES   = 22,    ///< 4 megabyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_8_MBYTES   = 23,    ///< 8 megabyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_16_MBYTES  = 24,    ///< 16 megabyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_32_MBYTES  = 25,    ///< 32 megabyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_64_MBYTES  = 26,    ///< 64 megabyte extended repeat area
    DMAC_EXTENDED_REPEAT_AREA_128_MBYTES = 27     ///< 128 megabyte extended repeat area
} dmac_extended_repeat_area_t;

/**********************************************************************************************************************
 * Function Prototypes
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
/* Select implementation based on BSP here */
#include "common/hw_dmac_common.h"

/* Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER

#endif /* HW_DMAC_PRIVATE_H */

/*******************************************************************************************************************//**
 * @} (end addtogroup DMAC)
 **********************************************************************************************************************/
