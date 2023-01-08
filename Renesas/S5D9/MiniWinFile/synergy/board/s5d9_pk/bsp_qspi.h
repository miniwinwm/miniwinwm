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

/***********************************************************************************************************************
 * File Name    : bsp_qspi.h
 * Description  : Configures QSPI bus and device access.
 **********************************************************************************************************************/



/*******************************************************************************************************************//**
 * @ingroup BSP_BOARD_PK_S5D9
 * @defgroup BSP_PK9M_QSPI Board QSPI
 * @brief QSPI configuration setup for this board.
 *
 * This is code specific to the PK-S5D9 board.
 *
 * @{
 **********************************************************************************************************************/

#ifndef BSP_QSPI_H_
#define BSP_QSPI_H_
/** Common macro for SSP header files. There is also a corresponding SSP_FOOTER macro at the end of this file. */
SSP_HEADER

/* This QSPI header file requires this be included here. */
#include <stdint.h>
#include <stdbool.h>

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* ID and type information for the W25Q64FV Windbond Serial NOR Flash Memory */
#define BSP_PRV_QSPI_MANUFACTURER_ID 0xEFU
#define BSP_PRV_QSPI_MEMORY_TYPE     0x40U
#define BSP_PRV_QSPI_MEMORY_CAPACITY 0x17U

/* Hex equivalent value for 16MB flash memory */
#define QSPI_MEMORY_CAPACITY_ACCESS_16MB 0x18U

/** Physical address the QSPI device is mapped to */
#define BSP_PRV_QSPI_DEVICE_PHYSICAL_ADDRESS (0x60000000)

/** When page program uses multiple data lines, the address is on one line. */
#define QSPI_PAGE_PROGRAM_ADDRESS_ONE_LINE     (0x1U)

/** When page program uses multiple data lines, the data is on 4 lines. */
#define QSPI_PAGE_PROGRAM_DATA_LINES           (0x4U)

/** Quad input fast program command. */
#define QSPI_COMMAND_PAGE_PROGRAM_QUAD         (0x32U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Reference cycle selects. Resultant QSPI clock is PCLKA divided down by the following: (W25Q64FV Windbond Serial NOR Flash Memory) */
typedef enum e_qspi_clk
{
    /** Reset Operations */
    QSPI_CLK_DIV2,         ///< ie. QSPI CLK runs at 60.00 MHz when PCLKA is set to 120MHz
    QSPI_CLK_DIV3,         ///< ie. QSPI CLK runs at 40.00 MHz when PCLKA is set to 120MHz
    QSPI_CLK_DIV4,         ///< ie. QSPI CLK runs at  30.00 MHz when PCLKA is set to 120MHz
    QSPI_CLK_DIV5,         ///< ie. QSPI CLK runs at  24.00 MHz when PCLKA is set to 120MHz
    QSPI_CLK_DIV6,         ///< ie. QSPI CLK runs at  20.00 MHz when PCLKA is set to 120MHz
    QSPI_CLK_DIV7,         ///< ie. QSPI CLK runs at  17.14 MHz when PCLKA is set to 120MHz
    QSPI_CLK_DIV8,         ///< ie. QSPI CLK runs at  15.00 MHz when PCLKA is set to 120MHz
    QSPI_CLK_DIV9,         ///< ie. QSPI CLK runs at  13.33 MHz when PCLKA is set to 120MHz
    QSPI_CLK_DIV10,        ///< ie. QSPI CLK runs at  12.00 MHz when PCLKA is set to 120MHz
} qspi_clk;

/** Available QSPI read modes for Winbond W25Q64FV quad SPI flash device */
typedef enum e_qspi_readmode
{
    /** Reset Operations */
    QSPI_READMODE_STANDARD,         ///< Standard
    QSPI_READMODE_FAST,             ///< Fast read
    QSPI_READMODE_FAST_DUAL_OUTPUT, ///< Fast Read Dual Output
    QSPI_READMODE_FAST_DUAL_IO,     ///< Fast Read Dual I/O
    QSPI_READMODE_FAST_QUAD_OUTPUT, ///< Fast Read Quad Output
    QSPI_READMODE_FAST_QUAD_IO,     ///< Fast Read Quad I/O
} qspi_readmode;

/** Available QSPI commands for the Winbond W25Q64FV quad SPI flash device */
typedef enum e_qspi_command
{
    /** Reset Operations */
    QSPI_COMMAND_RESET_ENABLE              = 0x66U,         ///< Enable reset
    QSPI_COMMAND_RESET_MEMORY              = 0x99U,         ///< Reset memory

    /** Read Operations */
    QSPI_COMMAND_READ                      = 0x03U,         ///< Read memory
    QSPI_COMMAND_4BYTE_READ                = 0x00U,         ///<not used>

    /** Write Operations */
    QSPI_COMMAND_WRITE_ENABLE              = 0x06U,         ///< Write Enable
    QSPI_COMMAND_WRITE_DISABLE             = 0x04U,         ///< Write Disable
    QSPI_COMMAND_PAGE_PROGRAM              = 0x02U,         ///< Program a page in Quad I/O mode
    QSPI_COMMAND_4BYTE_PAGE_PROGRAM        = 0x00U,         ///<not used>
    QSPI_COMMAND_WE_FOR_VOLATILE_SR        = 0x50U,         /// Write Enable for volatile Status Register

    /** Register Operations */
    QSPI_COMMAND_READ_STATUS_REGISTER_1    = 0x05U,         ///< Read Status register 1 (S7..S0)
    QSPI_COMMAND_WRITE_STATUS_REGISTER     = 0x01U,         ///< Write Status register 1 (S7..S0)
    QSPI_COMMAND_READ_STATUS_REGISTER_2    = 0x35U,         ///< Read Status register 2 (S15..S8)


    QSPI_COMMAND_READ_ID                   = 0x9FU,         ///< Read the chip ID

    /** Erase Operations */
    QSPI_COMMAND_SECTOR_ERASE              = 0xD8U,         ///< Erase a sector (64K)
    QSPI_COMMAND_4BYTE_SECTOR_ERASE        = 0x00U,         ///<not used>
    QSPI_COMMAND_SUBSECTOR_ERASE           = 0x20U,         ///< Erase a subsector (4K)
    QSPI_COMMAND_CHIP_ERASE                = 0xC7U,         ///< Erase the entire chip

    /** XIP COMMAND */
    QSPI_COMMAND_ENTER_QPI_MODE            = 0x38U,         ///< Enter Quad Peripheral Interface mode
    QSPI_COMMAND_EXIT_QPI_MODE             = 0xFFU,

    /** 4-BYTE ADDRESS MODE Operations */
    QSPI_COMMAND_ENTER_4BYTE_ADDRESS_MODE  = 0xB7,         ///< 4-byte address mode entry command
    QSPI_COMMAND_EXIT_4BYTE_ADDRESS_MODE   = 0xE9,         ///< 4-byte address mode exit command
} qspi_command;

/** flag status registers for the W25Q64FV Windbond quad SPI flash device */
typedef struct st_W25Q64FV_flag_status_1
{
    /*LDRA_INSPECTED 381 S Anonymous structures and unions are allowed in SSP code. */
    union
    {
        uint8_t    status;
        /*LDRA_INSPECTED 381 S Anonymous structures and unions are allowed in SSP code. */
        struct
        {
            uint8_t busy    : 1;    ///< Erase/Write in progress (busy = 1)
            uint8_t wel     : 1;    ///< Write Latch Enable (Set to 1 after write enable, 0 write disable)
            uint8_t bp      : 3;    ///< Block Protection bits, 1=protected, 0= unprotected
            uint8_t tb      : 1;    ///< Top/Bottom block protect Top=0, Bottom=1
            uint8_t sec     : 1;    ///< Sector Protect Bit
            uint8_t srp0    : 1;    ///< Status Register Protect Bit
         };
    };
} W25Q64FV_flag_status_1;

typedef struct st_W25Q64FV_flag_status_2
{
    /*LDRA_INSPECTED 381 S Anonymous structures and unions are allowed in SSP code. */
    union
    {
        uint8_t    status;
        /*LDRA_INSPECTED 381 S Anonymous structures and unions are allowed in SSP code. */
        struct
        {
            uint8_t srp1    : 1;    ///< Status Register Protect Bit
            uint8_t qe      : 1;    ///< Quad Enable (1=enabled)
            uint8_t         : 1;    ///< unused
            uint8_t lb      : 3;    ///< Security Register Lock Bits
            uint8_t cmp     : 1;    ///< Complement Protect Bit
            uint8_t sus     : 1;    ///< Erase/Program Suspend status Bit
         };
    };
} W25Q64FV_flag_status_2;

typedef struct st_W25Q64FV_flag_status_3
{
    /*LDRA_INSPECTED 381 S Anonymous structures and unions are allowed in SSP code. */
    union
    {
        uint8_t    status;
        /*LDRA_INSPECTED 381 S Anonymous structures and unions are allowed in SSP code. */
        struct
        {
            uint8_t         : 2;    ///<
            uint8_t wps     : 1;    ///< Write Protect Selection
            uint8_t         : 2;    ///<
            uint8_t drv     : 2;    ///< Drive Strength
                                    /// 0 - 100%
                                    /// 1 - 75%
                                    /// 2 - 50%
                                    /// 3 - 25% (default)
            uint8_t hold    : 1;    ///< Hold/Reset function
         };
    };
} W25Q64FV_flag_status_3;

typedef enum qspi_protocol
{
    QSPI_EXTENDED_SPI_PROTOCOL = 0U,
    QSPI_DUAL_SPI_PROTOCOL     = 1U,
    QSPI_QUAD_SPI_PROTOCOL     = 2U,
} qspi_protocol;

/** characteristics of the flash device */
typedef struct st_qspi_characteristics
{
    uint8_t  manufacturer_id;           ///< Manufacturer ID
    uint8_t  memory_type;               ///< Memory type
    uint8_t  memory_capacity;           ///< Memory capacity
} qspi_characteristics;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
void bsp_qspi_init (void);

void bsp_qspi_status_get (bool * p_write_in_progress);

void bsp_qspi_xip_enter (void);

void bsp_qspi_xip_exit (void);
void bsp_qspi_config_get (uint8_t  * p_manufacturer_id,
                          uint8_t  * p_memory_type,
                          uint8_t  * p_memory_capacity,
                          uint32_t * p_max_eraseable_size,
                          uint32_t * p_num_address_bytes,
                          uint32_t * p_spi_mode,
                          uint32_t * p_page_size,
                          bool     * p_xip_mode);

void bsp_qspi_erase_sizes_get(uint32_t ** pp_sizes, uint8_t *p_len);
void bsp_qspi_erase_command_get(uint8_t *p_erase_command, uint8_t index);

/** Common macro for SSP header files. There is also a corresponding SSP_HEADER macro at the top of this file. */
SSP_FOOTER
#endif /* BSP_QSPI_H_ */
/** @} (end defgroup BSP_PK9M_QSPI) */
