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
 * File Name    : bsp_qspi.c
 * Description  : QSPI initialization.
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @addtogroup BSP_PK9M_QSPI
 * @brief QSPI initialization
 *
 * This file contains code that initializes the QSPI flash controller connected to a N25Q256A Micron Serial NOR Flash
 * Memory mounted on a PK-S5D9 development board.
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "bsp_api.h"

#if defined(BSP_BOARD_S5D9_PK)

/***********************************************************************************************************************
 * Configuration parameters
 **********************************************************************************************************************/

/* Number of bytes to be used for the address (3 or 4) */
#define BSP_PRV_QSPI_NUM_ADDRESS_BYTES 3U
#if BSP_PRV_QSPI_NUM_ADDRESS_BYTES != 3U
#error BSP_PRV_QSPI_NUM_ADDRESS_BYTES must be equal to 3
#endif

/* XIP entry and exit confirmation codes for the flash device */
#define BSP_PRV_QSPI_W25Q64FV_XIP_ENTRY_CODE (0x20U) // was 0
#define BSP_PRV_QSPI_W25Q64FV_XIP_EXIT_CODE  (0xffU)

/* Number of dummy clocks to set on the flash device for FAST READ operations */
#define BSP_PRV_QSPI_W25Q64FV_NUM_DUMMY_CLOCKS (6U)

/* QSSL high between cycles */
#define BSP_PRV_QSPI_N25Q256A_DE_SELECT_DELAY (4U)

/* Read mode to operate the device in */
#define BSP_PRV_QSPI_READ_MODE QSPI_READMODE_FAST_QUAD_IO

/* Enter XIP mode after bsp_qspi_init is called. */
#define BSP_PRV_QSPI_XIP_MODE_AFTER_INIT (1U)

/* Is prefetch used for ROM access mode */
#define BSP_PRV_QSPI_ROM_PREFTECH_MODE (1U)

/* QSPI Clock rate */
#define BSP_PRV_QSPI_CLOCK_RATE QSPI_CLK_DIV2  ///< QSPI CLK runs at 60.00 MHz if PCLKA is set to 120MHz


/* Flash device page size */
#define BSP_PRV_QSPI_W25Q64FV_PAGE_SIZE (256U)

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* Device flag status */
static W25Q64FV_flag_status_1 flag_status1 = {.status = 0U};
static W25Q64FV_flag_status_2 flag_status2 = {.status = 0U};

/* Device ID and characteristics */
static qspi_characteristics device_characteristics =
{
    0U, 0U, 0U
};


/* Flash Erase sizes */
static uint32_t w25q64fv_flash_erase_sizes[] =
{
    4096U,           ///< 4KB
    32768U,          ///< 32kB
    65536U,          ///< 64KB
    8388608U         ///< 8MB
};

/* Flash erase commands */
static uint8_t w25q64fv_erase_commands[]=
{
    0x20U,     ///< QSPI COMMAND SUBSECTOR_ERASE
    0x52U,     ///< QSPI COMMAND BLOCK_ERASE
    0xD8U,     ///< QSPI_COMMAND SECTOR_ERASE
    0xC7U      ///< QSPI_COMMAND CHIP_ERASE
};

/*******************************************************************************************************************//**
 * @brief   Reset the flash device
 **********************************************************************************************************************/
static void bsp_qspi_device_reset ()
{
    /* send 0xFF to device to take the device out of XIP, If a warm reset occurred */
    /* and the QSPI device was previously in XIP (continuous access) mode */
    R_QSPI->SFMCOM        = BSP_PRV_QSPI_W25Q64FV_XIP_EXIT_CODE;
    R_QSPI->SFMCMD_b.DCOM = 1U;    /* Close the SPI bus cycle */

    /* Reset the flash device. */
    R_QSPI->SFMCOM        = QSPI_COMMAND_RESET_ENABLE; /* Write the command */
    R_QSPI->SFMCMD_b.DCOM = 1U;                         /* Close the SPI bus cycle */
    R_QSPI->SFMCOM        = QSPI_COMMAND_RESET_MEMORY; /* Write the command */
    R_QSPI->SFMCMD_b.DCOM = 1U;                         /* Close the SPI bus cycle */
}


/*******************************************************************************************************************//**
 * @brief   Enter or exit XIP mode
 *
 * @param[in]  enter_mode  0 = exit XIP mode, 1 = enter XIP mode
 *
 **********************************************************************************************************************/
static void bsp_qspi_xip_mode (bool enter_mode)
{
    volatile uint32_t i = 0;
    volatile uint32_t timeout;

    SSP_PARAMETER_NOT_USED(i);

    R_QSPI->SFMCMD_b.DCOM = 0U;

    if (enter_mode)
    {
        R_QSPI->SFMSDC_b.SFMXD  = BSP_PRV_QSPI_W25Q64FV_XIP_ENTRY_CODE;                        /* Set the XIP entry
                                                                                                * confirmation
                                                                                                * code */

        R_QSPI->SFMSDC_b.SFMXEN = true;                                                        /* Enter XIP mode in QSPI
                                                                                                * controller */
        i                       = *(volatile uint32_t *) BSP_PRV_QSPI_DEVICE_PHYSICAL_ADDRESS;


        /* Wait for the controller to enter XIP mode */
        timeout = 0xfffU;
        while (0U == R_QSPI->SFMSDC_b.SFMXST)
        {
            timeout--;
            if (0U == timeout)
            {
                return;
            }
        }
    }
    else
    {
        R_QSPI->SFMSDC_b.SFMXD  = BSP_PRV_QSPI_W25Q64FV_XIP_EXIT_CODE;                         /* Set the XIP exit
                                                                                                * confirmation
                                                                                                * code */
        R_QSPI->SFMSDC_b.SFMXEN = false;                                                       /* Exit XIP mode in the
                                                                                                * QSPI
                                                                                                * controller
                                                                                                * block */
        i                       = *(volatile uint32_t *) BSP_PRV_QSPI_DEVICE_PHYSICAL_ADDRESS; /* Read from the device
                                                                                                * to
                                                                                                * set the
                                                                                                * code */


        /* Wait for the controller to exit XIP mode */
        timeout = 0xfffU;
        while (R_QSPI->SFMSDC_b.SFMXST)
        {
            timeout--;
            if (0U == timeout)
            {
                return;
            }
        }
    }
}

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @brief   Initializes QSPI.
 *
 * This function initializes QSPI and Micron Serial Flash Memory device on the board.
 *
 * @note This function is executed once after reset.
 **********************************************************************************************************************/
void bsp_qspi_init (void)
{
    bool     write_in_progress;
    /* enable clocks to the QSPI block */
    R_MSTP->MSTPCRB_b.MSTPB6 = 0U;

    /* Initialized unused bits */
    R_QSPI->SFMSPC = 0x10U;
    R_QSPI->SFMCST = 0U;
    R_QSPI->SFMSIC = 0U;
    R_QSPI->SFMPMD = 0U;
    R_QSPI->SFMCNT1 = 0U;

    /* Set the SPI clock rate */
    R_QSPI->SFMSKC_b.SFMDV = BSP_PRV_QSPI_CLOCK_RATE;

    /* enter direct communication mode */
    R_QSPI->SFMCMD_b.DCOM = 1U;

    /* Reset the flash device - SW command */
    bsp_qspi_device_reset();

    /* Reset takes 30uS */
    R_BSP_SoftwareDelay(35U, BSP_DELAY_UNITS_MICROSECONDS);

    /* Read the ID of the device. Confirm it is the correct device. */
    R_QSPI->SFMCOM                         = QSPI_COMMAND_READ_ID;  /* Write the command */
    device_characteristics.manufacturer_id = R_QSPI->SFMCOM_b.SFMD; /* Read the manufacturer ID */
    device_characteristics.memory_type     = R_QSPI->SFMCOM_b.SFMD; /* Read the memory type */
    device_characteristics.memory_capacity = R_QSPI->SFMCOM_b.SFMD; /* Read the memory capacity */
    R_QSPI->SFMCMD_b.DCOM                  = 1U;                     /* Close the SPI bus cycle */

    if ((BSP_PRV_QSPI_MANUFACTURER_ID != device_characteristics.manufacturer_id) ||
        (BSP_PRV_QSPI_MEMORY_TYPE != device_characteristics.memory_type) ||
        (BSP_PRV_QSPI_MEMORY_CAPACITY != device_characteristics.memory_capacity))
    {
        device_characteristics.manufacturer_id = 0U;
        device_characteristics.memory_type     = 0U;
        device_characteristics.memory_capacity = 0U;
        return;
    }

    /* Read the status of the device */
    R_QSPI->SFMCOM  = QSPI_COMMAND_READ_STATUS_REGISTER_1;  /* Write the command */
    flag_status1.status    = R_QSPI->SFMCOM_b.SFMD;                /* Read the flags */
    R_QSPI->SFMCMD_b.DCOM = 1U;                                    /* Close the SPI bus cycle */

    R_QSPI->SFMCOM  = QSPI_COMMAND_READ_STATUS_REGISTER_2;  /* Write the command */
    flag_status2.status    = R_QSPI->SFMCOM_b.SFMD;                /* Read the flags */
    R_QSPI->SFMCMD_b.DCOM = 1U;                                    /* Close the SPI bus cycle */

    /* Set the number of dummy cycles in QSPI peripheral */
    R_QSPI->SFMSDC_b.SFMDN = BSP_PRV_QSPI_W25Q64FV_NUM_DUMMY_CLOCKS - 2U;

    /* Micron QSPI needs 50ns de-select  (QSSL high between cycles) for nonREAD commands */
    /* (20ns for a read command) Need 3 and a bit clock (i.e. 4) cycles at 60MHz */
    R_QSPI->SFMSSC_b.SFMSW = BSP_PRV_QSPI_N25Q256A_DE_SELECT_DELAY;

    /* We need to set the QE bit to 1 in the W25Q64FV status register, to enable QUAD IO mode */
    /* Since the part on the S7-SK board is W25Q64FVSSIG, QE default state is 0               */
    /* Set the QE bit as a volatile write, for speed, and not to affect the write endurance of */
    /* Status Register non-volatile bits, and so the device is in the default state */
    /* at power up.  */

    /* Write Enable For Volatile Status Register */
    R_QSPI->SFMCOM  = QSPI_COMMAND_WE_FOR_VOLATILE_SR;  /* Write the command */
    R_QSPI->SFMCMD_b.DCOM = 1U;

    flag_status2.qe = 1U;                               /* set bit 2 (S9), QE = 1 */

    /* Write Status Register */
    R_QSPI->SFMCOM  = QSPI_COMMAND_WRITE_STATUS_REGISTER;  /* Write the command */
    R_QSPI->SFMCOM  = flag_status1.status;                /* Write the Status Register 1 back */
    R_QSPI->SFMCOM  = flag_status2.status;                /* Write the Status Register 2 back, set bit 2 (S9), QE = 1 */
    R_QSPI->SFMCMD_b.DCOM = 1U;                              /* Close the SPI bus cycle */

    /* Disable Write */
    R_QSPI->SFMCOM  = QSPI_COMMAND_WRITE_DISABLE;           /* Write the command */
    R_QSPI->SFMCMD_b.DCOM = 1U;                              /* Close the SPI bus cycle */

    /* Set the read mode */
    R_QSPI->SFMSMD_b.SFMRM = BSP_PRV_QSPI_READ_MODE;
    /* End, set QE bit 1 */

    /* Re-Read the status of the device, with updated settings */
    R_QSPI->SFMCOM  = QSPI_COMMAND_READ_STATUS_REGISTER_1;  /* Write the command */
    flag_status1.status    = R_QSPI->SFMCOM_b.SFMD;                /* Read the flags */
    R_QSPI->SFMCMD_b.DCOM = 1U;                                    /* Close the SPI bus cycle */

    R_QSPI->SFMCOM  = QSPI_COMMAND_READ_STATUS_REGISTER_2;  /* Write the command */
    flag_status2.status    = R_QSPI->SFMCOM_b.SFMD;                /* Read the flags */
    R_QSPI->SFMCMD_b.DCOM = 1U;                                    /* Close the SPI bus cycle */

    /* To make sure the 3-byte addressing is selected as default */
    if(QSPI_MEMORY_CAPACITY_ACCESS_16MB < device_characteristics.memory_capacity)
    {
        /* Enter 4-byte addressing mode */
        R_QSPI->SFMCOM        = QSPI_COMMAND_WRITE_ENABLE;             /* Enable writing */
        R_QSPI->SFMCMD_b.DCOM = 1U;
        R_QSPI->SFMCOM        = QSPI_COMMAND_ENTER_4BYTE_ADDRESS_MODE; /* Set 4-byte accessing mode */
        R_QSPI->SFMCMD_b.DCOM = 1U;
        do
        {
            bsp_qspi_status_get(&write_in_progress);
        } while (write_in_progress);
        R_QSPI->SFMSAC_b.SFMAS  = 3U; /* Set qspi control register for 4-byte accessing mode */
        R_QSPI->SFMSAC_b.SFM4BC = 1U;

        /* Exit 4-byte addressing mode to make sure QSPI is in 3-byte addressing mode*/
        R_QSPI->SFMCOM        = QSPI_COMMAND_WRITE_ENABLE;             /* Enable writing */
        R_QSPI->SFMCMD_b.DCOM = 1U;
        R_QSPI->SFMCOM        = QSPI_COMMAND_EXIT_4BYTE_ADDRESS_MODE; /* Set 4-byte accessing mode */
        R_QSPI->SFMCMD_b.DCOM = 1U;
        do
        {
            bsp_qspi_status_get(&write_in_progress);
        } while (write_in_progress);
        R_QSPI->SFMSAC_b.SFMAS  = 2U; /* Set qspi control register for 3-byte accessing mode */
        R_QSPI->SFMSAC_b.SFM4BC = 0U;
    }

#if   BSP_PRV_QSPI_ROM_PREFTECH_MODE
    R_QSPI->SFMSMD_b.SFMPFE = 1U;
#endif

#if BSP_PRV_QSPI_XIP_MODE_AFTER_INIT
    /* Enable XIP mode on the flash device */
    bsp_qspi_xip_enter();
#endif

    /* Enter ROM access mode */
    R_QSPI->SFMCMD_b.DCOM = 0U;
}

/*******************************************************************************************************************//**
 * @brief   Enter XIP mode
 *
 * This function enters XIP mode in both the QSPI controller block and on the flash device.
 *
 **********************************************************************************************************************/
void bsp_qspi_xip_enter (void)
{
    /* Check there is no serial transfer in progress */
    while (R_QSPI->SFMCST_b.COMBSY == 1U)
    {
    }
    /* Set the Mode bit in the Dummy Cycle to enter Continuous Read mode */
    bsp_qspi_xip_mode(true);
}

/*******************************************************************************************************************//**
 * @brief   Exit XIP mode
 *
 * This function exits XIP mode in both the QSPI controller block and on the flash device.
 *
 **********************************************************************************************************************/
void bsp_qspi_xip_exit (void)
{
    /* Check there is no serial transfer in progress */
    while (R_QSPI->SFMCST_b.COMBSY == 1U)
    {
    }
    /* Set the Mode bit in the Dummy Cycle to exit Continuous Read mode */
    bsp_qspi_xip_mode(false);
}

/*******************************************************************************************************************//**
 * @brief   Get the status from the QSPI device.
 *
 * This function reads the status byte from the device and returns the write status. Used by write and erase operations
 * in the QSPI module driver.
 *
 * @param[in]  p_write_in_progress  Pointer to a boolean that indicates if a write or erase is in progress.
 *
 **********************************************************************************************************************/
void bsp_qspi_status_get (bool * p_write_in_progress)
{
    /* Send command to read status */
    R_QSPI->SFMCOM = QSPI_COMMAND_READ_STATUS_REGISTER_1;

    /* Read the device status register */
    flag_status1.status = R_QSPI->SFMCOM_b.SFMD;

    /* Close the SPI bus cycle */
    R_QSPI->SFMCMD_b.DCOM = 1U;

    *p_write_in_progress = (bool)(1U == flag_status1.busy);
}


/*******************************************************************************************************************//**
 * @brief   Get the current configuration of the QSPI device.
 *
 * This function reads the volatile and non-volatile registers of the device and returns portions of these to the QSPI
 * module driver for use in direct communication mode.
 *
 * @param[out] num_address_bytes      Number of bytes used for the address - 3 bytes or 4 bytes
 * @param[out] spi_mode               SPI mode used - 0 = Extended, 1 = Dual, 2 = Quad
 *
 **********************************************************************************************************************/
void bsp_qspi_config_get (uint8_t  * p_manufacturer_id,
                          uint8_t  * p_memory_type,
                          uint8_t  * p_memory_capacity,
                          uint32_t * p_max_eraseable_size,
                          uint32_t * p_num_address_bytes,
                          uint32_t * p_spi_mode,
                          uint32_t * p_page_size,
                          bool     * p_xip_mode)
{
    bool write_in_progress = true;

    *p_manufacturer_id    = device_characteristics.manufacturer_id;
    *p_memory_type        = device_characteristics.memory_type;
    *p_memory_capacity    = device_characteristics.memory_capacity;
    *p_max_eraseable_size = 4U; /* 4k bytes */

    /* 4-byte addressing mode entry */
    if((4U == *p_num_address_bytes) && (QSPI_MEMORY_CAPACITY_ACCESS_16MB < *p_memory_capacity))
    {
        R_QSPI->SFMCOM        = QSPI_COMMAND_WRITE_ENABLE;             /* Enable writing */
        R_QSPI->SFMCMD_b.DCOM = 1U;
        R_QSPI->SFMCOM        = QSPI_COMMAND_ENTER_4BYTE_ADDRESS_MODE; /* Set 4-byte accessing mode */
        R_QSPI->SFMCMD_b.DCOM = 1U;
        do
        {
            bsp_qspi_status_get(&write_in_progress);
        } while (write_in_progress);
        R_QSPI->SFMSAC_b.SFMAS  = 3U; /* Set qspi control register for 4-byte accessing mode */
        R_QSPI->SFMSAC_b.SFM4BC = 1U;
    }
    /* Invalid addressing mode */
    else if((4U == *p_num_address_bytes) && (QSPI_MEMORY_CAPACITY_ACCESS_16MB > *p_memory_capacity))
    {
        *p_num_address_bytes = 0U; /* Invalid address byte */
    }

    *p_spi_mode           = (uint32_t) QSPI_EXTENDED_SPI_PROTOCOL;
    *p_page_size          = BSP_PRV_QSPI_W25Q64FV_PAGE_SIZE;
#if BSP_PRV_QSPI_XIP_MODE_AFTER_INIT
    *p_xip_mode           = true;
#else
    *p_xip_mode           = false;
#endif
}
/*******************************************************************************************************************//**
 * @brief   Get the supported erase sizes of Flash.
 *
 * QSPI Flash erase sizes are arranged in acceding order.Function returns the address of the ordered array of
 * erase size to upper layer.
 *
 **********************************************************************************************************************/
void bsp_qspi_erase_sizes_get(uint32_t ** pp_sizes, uint8_t *p_len)
{
    *pp_sizes = &w25q64fv_flash_erase_sizes[0];

    *p_len = (uint8_t)(sizeof(w25q64fv_flash_erase_sizes)/sizeof(w25q64fv_flash_erase_sizes[0]));

}
/*******************************************************************************************************************//**
 * @brief   Get erase command based on index value.
 *
 * QSPI Flash erase size commands are arranged in a acceding order.
 *
 **********************************************************************************************************************/
void bsp_qspi_erase_command_get(uint8_t *p_erase_command, uint8_t index)
{
    *p_erase_command = w25q64fv_erase_commands[index];
}
#endif /* if defined(BSP_BOARD_S5D9_PK) */

/** @} (end addtogroup BSP_PK9M_QSPI) */
