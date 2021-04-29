/*

MIT License

Copyright (c) John Blaiklock 2019 miniwin Embedded Window Manager

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef APP_H
#define APP_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include <stdint.h>
#include "miniwin.h"
#include "app.h"

/****************
*** CONSTANTS ***
****************/

#define SPI_LCD_TOUCH_BASE					SPI0					/**< SPI peripheral to use for touch/LCD */
#define SPI_LCD_CHIP_SEL					0						/**< LCD CS/ line on SPI0 */
#define SPI_TOUCH_CHIP_SEL					1						/**< Touch screen CS/ line on SPI0 */
#define TOUCH_RECAL_PIN						PIO_PD0_IDX				/**< Pin for touch screen recalibration request */
#define TOUCH_T_IRQ_PIN						PIO_PD1_IDX				/**< Pin for touch T_IRQ/ line */
#define LCD_RESET_PIN						PIO_PD2_IDX				/**< Pin for LCD RESET line */
#define LCD_DC_PIN							PIO_PD3_IDX				/**< Pin for LCD DC line */
#define MAX_FILENAME_LENGTH					12						/**< Maximum length of a file name in eight dot three format */
#define MAX_FOLDER_AND_FILENAME_LENGTH		128						/**< Maximum length of a file name and its path */
#define SIMULATED_RTC												/**< Simulates RTC from miniwn tick timer for DUE boards with no RTC crystal */

/************
*** TYPES ***
************/

/*************************
*** EXTERNAL VARIABLES ***
*************************/

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Function called from main to perform application initializations
 */
void app_init(void);

/**
 * Function called from main to perform application main loop processing
 */
void app_main_loop_process(void);

/**
 * Transfer data to/from SPI_LCD_TOUCH_BASE SPI device 
 *
 * @param tx_buf Buffer holding data to send
 * @param rx_buf Buffer to hold data received
 * @size Length of data in tx_buf
 * @note rx_buf must be at least size bytes long
 * @note The CS/ line must already be set                                                               
 */
void spi_transfer(const uint8_t *tx_buf, uint8_t *rx_buf, size_t size);

/**
 * Send data to SPI_LCD_TOUCH_BASE SPI device 
 *
 * @param tx_buf Buffer holding data to send
 * @size Length of data in tx_buf
 * @note The CS/ line must already be set                                                               
 */
void spi_send(const uint8_t *tx_buf, size_t size);

/**
 * Find all the entries in the folder of the given path
 *
 * @param path Pointer to path text. Path separators are '/'. Must not end in '/' apart from root.
 * @param list_box_settings_entries The returned entries data which has the text and an icon filled in for each entry
 * @param folders_only If true find only folders
 * @param max_entries The maximum number of entries to look for
 * @param file_entry_icon Pointer to the icon to use for a file entry
 * @param folder_entry_icon Pointer to the icon to use for a folder entry
 * @return The number of entries found
 * @note This function is required if MW_DIALOG_FILE_CHOOSER is defined
 */
uint8_t find_folder_entries(char *path,
 		mw_ui_list_box_entry *list_box_settings_entries,
 		bool folders_only,
 		uint8_t max_entries,
 		const uint8_t *file_entry_icon,
 		const uint8_t *folder_entry_icon);

/**
 * Get all the children (but not sub-children) of a folder from the file system
 * and add them to the folder node in the tree structure
 *
 * @param tree Pointer to tree structure
 * @param start_folder_handle The folder node handle in the tree structure
 * @note The path used to interrogate the folder in the file system is the path of the
 *       folder node in the folder structure
 */
void app_populate_tree_from_file_system(struct mw_tree_container_t *tree,
 		mw_handle_t start_folder_handle);

/**
 * Accessor to the root folder path which comes from the FatFS module and is stored in
 * app source file
 *
 * @return Pointer to the root path
 */
char *app_get_root_folder_path(void);

/**
 * Open an input file for reading
 *
 * @param path_and_filename The path and name of the file to open
 * @return true if opened else false
 */
bool app_file_open(char *path_and_filename);

/**
 * Create an output file for writing
 *
 * @param path_and_filename The path and name of the file to create
 * @return true if created else false
 */
bool app_file_create(char *path_and_filename);

/**
 * Gets the size of the opened file
 *
 * @return size in bytes
 */
uint32_t app_file_size(void);

/**
 * Read a single byte from a file
 *
 * @return the byte read
 */
uint8_t app_file_getc(void);

/**
 * Seek to a position in a file
 *
 * @param position Position from start
 * @return 0 if success otherwise non-zero
 */
uint32_t app_file_seek(uint32_t position);

/**
 * Read from open file
 *
 * @param buffer Destination buffer to read in to
 * @param count Number of bytes to read
 */
void app_file_read(uint8_t *buffer, uint32_t count);

/**
 * Write to open file
 *
 * @param buffer Buffer containing bytes to write
 * @param count Number of bytes to write
 */
void app_file_write(uint8_t *buffer, uint32_t count);

/**
 * Close an open file
 */
void app_file_close(void);

/**
 * Get the date and time from hardware
 *
 * @return The date and time, year in xxxx format, date 1-31, month 1-12
 */
mw_time_t app_get_time_date(void);

/**
 * Set the date and time from hardware
 *
 * @param new_time The date and time, year in xxxx format, date 1-31, month 1-12
 */
void app_set_time_date(mw_time_t new_time);

/** 
 * Called by MiniWin tick counter to update real time for file system for Due boards with no RTC crystal fitted
 */
void update_real_time(void);

#ifdef __cplusplus
}
#endif

#endif
