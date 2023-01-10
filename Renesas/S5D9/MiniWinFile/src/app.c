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

/***************
*** INCLUDES ***
***************/

#include "file_thread.h"
#include "miniwin.h"
#include "app.h"

/****************
*** CONSTANTS ***
****************/

#define EVENT_USB_PLUG_IN           (1UL << 0)
#define EVENT_USB_PLUG_OUT          (1UL << 1)

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

volatile bool media_inserted;
static FX_FILE my_file;

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

/**********************
*** LOCAL FUNCTIONS ***
**********************/

UINT usb_host_plug_event_notification(ULONG usb_event, UX_HOST_CLASS * host_class, VOID * instance);

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

void app_init(void)
{
    rtc_time_t time;

    (void)g_rtc.p_api->open(g_rtc.p_ctrl, g_rtc.p_cfg);

    // set the rtc to 1 jan 2020 0:0:0
    time.tm_hour = 0;
    time.tm_min = 0;
    time.tm_sec = 0;
    time.tm_year = 120;
    time.tm_mon = 0;
    time.tm_mday = 1;

    (void)g_rtc.p_api->calendarTimeSet(g_rtc.p_ctrl, &time, true);
}

void app_main_loop_process(void)
{
}

UINT usb_host_plug_event_notification(ULONG usb_event, UX_HOST_CLASS *host_class, VOID *instance)
{
    /* variable to hold the UX calls return values */
    UINT ux_return;

    UX_HOST_CLASS_STORAGE_MEDIA *p_ux_host_class_storage_media;

    /* check if host_class is for Mass Storage class */
    if (_ux_utility_memory_compare(
            _ux_system_host_class_storage_name,
            host_class,
            _ux_utility_string_length_get(_ux_system_host_class_storage_name)) == UX_SUCCESS)
    {
        /* get the pointer to the media */
        ux_return = ux_system_host_storage_fx_media_get(instance, &p_ux_host_class_storage_media, &g_fx_media0_ptr);

        if (ux_return != UX_SUCCESS)
        {
            /* This is a simple error handling - it holds the
               application execution. In a more realistic scenarios
               a more robust and complex error handling solution should
               be provided. */
            tx_thread_sleep(TX_WAIT_FOREVER);
        }

        /* check the usb_event type */
        switch (usb_event)
        {
            case EVENT_USB_PLUG_IN:
                /* notify the insertion of a USB Mass Storage device */
                media_inserted = true;
                tx_event_flags_set(&g_usb_plug_events, EVENT_USB_PLUG_IN, TX_OR);
                break;

            case EVENT_USB_PLUG_OUT:
                media_inserted = false;
                /* notify the removal of a USB Mass Storage device */
                tx_event_flags_set(&g_usb_plug_events, EVENT_USB_PLUG_OUT, TX_OR);
                break;

            default:
                /* ignore this unsupported event */
                break;
        }
    }

    return UX_SUCCESS;
}

bool app_file_open(char *path_and_filename)
{
    bool success = false;

    if (media_inserted)
    {
        if (fx_file_open(g_fx_media0_ptr, &my_file, path_and_filename, FX_OPEN_FOR_READ) == FX_SUCCESS)
        {
            success = true;
        }
    }

    return success;
}

bool app_file_create(char *path_and_filename)
{
    bool success = false;

    if (media_inserted)
    {
        if (fx_file_open(g_fx_media0_ptr, &my_file, path_and_filename, FX_OPEN_FOR_READ) == FX_SUCCESS)
        {
            /* file already exists so close and delete it */
            (void)fx_file_close(&my_file);
            (void)fx_file_delete(g_fx_media0_ptr, path_and_filename);
        }

        /* create and open file */
        if (fx_file_create(g_fx_media0_ptr, path_and_filename) == FX_SUCCESS)
        {
            if (fx_file_open(g_fx_media0_ptr, &my_file, path_and_filename, FX_OPEN_FOR_WRITE) == FX_SUCCESS)
            {
                success = true;
            }
        }
    }

    return success;
}

uint32_t app_file_size(void)
{
    uint32_t size = 0UL;

    if (media_inserted)
    {
        size = (uint32_t)my_file.fx_file_current_file_size;
    }

    return size;
}

uint8_t app_file_getc(void)
{
    uint8_t byte = 0U;
    ULONG read_size;

    if (media_inserted)
    {
        (void)fx_file_read(&my_file, &byte, (ULONG)1, &read_size);
    }

    return byte;
}

void app_file_read(uint8_t *buffer, uint32_t count)
{
    ULONG read_size;

    if (media_inserted)
    {
        (void)fx_file_read(&my_file, buffer, (ULONG)count, &read_size);
    }
}

void app_file_write(uint8_t *buffer, uint32_t count)
{
    if (media_inserted)
    {
        (void)fx_file_write(&my_file, buffer, (ULONG)count);
    }
}

uint32_t app_file_seek(uint32_t position)
{
    if (media_inserted)
    {
        return (uint32_t)fx_file_seek(&my_file, (ULONG)position);
    }

    return 1UL;
}

void app_file_close(void)
{
    if (media_inserted)
    {
        (void)fx_file_close(&my_file);
        (void)fx_media_flush(g_fx_media0_ptr);
    }
}

char *app_get_root_folder_path(void)
{
    return ("/");
}

void app_populate_tree_from_file_system(struct mw_tree_container_t *tree,
        mw_handle_t start_folder_handle)
{
    char entry_name[MAX_FOLDER_AND_FILENAME_LENGTH];
    uint8_t node_flags;
    UINT result;
    UINT attributes;
    bool first = true;

    if (media_inserted)
    {
        /* check pointer parameter */
        if (tree == NULL)
        {
            MW_ASSERT((bool)false, "Null pointer");

            return;
        }

        mw_tree_container_get_node_path(tree, start_folder_handle, entry_name, MAX_FOLDER_AND_FILENAME_LENGTH);

        if (strlen(entry_name) == (size_t)0)
        {
            return;
        }

        /* strip off terminating '/' for FileX folders unless root path */
        if (strlen(entry_name) > (size_t)1)
        {
            entry_name[strlen(entry_name) - 1U] = '\0';
        }

        /* set folder look into */
        (void)fx_directory_default_set(g_fx_media0_ptr, entry_name);

        /* open the folder */
        for (;;)
        {
            /* read a folder item */
            if (first)
            {
                first = false;
                result = fx_directory_first_full_entry_find(g_fx_media0_ptr, entry_name, &attributes,
                    NULL, NULL, NULL, NULL, NULL, NULL, NULL);
                if (result == FX_NO_MORE_ENTRIES)
                {
                    /* break on error or end of folder */
                    break;
                }
            }
            else
            {
                result = fx_directory_next_full_entry_find(g_fx_media0_ptr, entry_name, &attributes,
                    NULL, NULL, NULL, NULL, NULL, NULL, NULL);
                if (result == FX_NO_MORE_ENTRIES)
                {
                    /* break on error or end of folder */
                    break;
                }
            }

            /* ignore if it's a hidden, system or volume entry*/
            if ((attributes & FX_HIDDEN) || (attributes & FX_SYSTEM) || (attributes & FX_VOLUME))
            {
                continue;
            }


            /* ignore if it's . or .. */
            if ((strlen(entry_name) == (size_t)1 && entry_name[0] == '.') ||
                    (strlen(entry_name) == (size_t)2 && strcmp(entry_name, "..") == 0))
            {
                continue;
            }

            node_flags = 0U;
            if (attributes & FX_DIRECTORY)
            {
                node_flags = MW_TREE_CONTAINER_NODE_IS_FOLDER;
            }

            (void)mw_tree_container_add_node(tree,
                    start_folder_handle,
                    entry_name,
                    node_flags);
        }
    }
}

uint8_t find_folder_entries(char *path,
        mw_ui_list_box_entry *list_box_settings_entries,
        bool folders_only,
        uint8_t max_entries,
        const uint8_t *file_entry_icon,
        const uint8_t *folder_entry_icon)
{
    uint8_t entries = 0U;
    bool first = true;
    UINT result;
    char entry_name[MAX_FOLDER_AND_FILENAME_LENGTH];
    UINT attributes;

    if (media_inserted)
    {
        /* check pointer parameter */
        if (path == NULL)
        {
            MW_ASSERT((bool)false, "Null pointer");

            return 0U;
        }

        /* check path string not empty */
        if (strlen(path) == (size_t)0)
        {
            return 0U;
        }

        /* strip off terminating '/' for FileX folders unless root path */
        if (strlen(path) > (size_t)1)
        {
            path[strlen(path) - 1U] = '\0';
        }

        (void)fx_directory_default_set(g_fx_media0_ptr, path);

        for (;;)
        {
            /* read a folder item */
            if (first)
            {
                first = false;
                result = fx_directory_first_full_entry_find(g_fx_media0_ptr, entry_name, &attributes,
                    NULL, NULL, NULL, NULL, NULL, NULL, NULL);
                if (result == FX_NO_MORE_ENTRIES)
                {
                    return 0U;
                }
            }
            else
            {
                result = fx_directory_next_full_entry_find(g_fx_media0_ptr, entry_name, &attributes,
                    NULL, NULL, NULL, NULL, NULL, NULL, NULL);
                if (result == FX_NO_MORE_ENTRIES)
                {
                    break;
                }
            }

            /* ignore if it's a hidden, system or volumeentry*/
            if ((attributes & FX_HIDDEN) || (attributes & FX_SYSTEM) || (attributes & FX_VOLUME))
            {
                continue;
            }

            /* ignore if not a folder and we want directories only */
            if (folders_only && (attributes & FX_DIRECTORY))
            {
                continue;
            }

            /* ignore if it's . or .. */
            if ((strlen(entry_name) == (size_t)1 && entry_name[0] == '.') ||
                    (strlen(entry_name) == (size_t)2 && strcmp(entry_name, "..") == 0))
            {
                continue;
            }

            (void)mw_util_safe_strcpy(list_box_settings_entries[entries].label, MAX_FILENAME_LENGTH + 1U, entry_name);
            if (attributes & FX_DIRECTORY)
            {
                /* it is a folder */
                list_box_settings_entries[entries].icon = folder_entry_icon;
            }
            else
            {
                /* it is a file. */
                list_box_settings_entries[entries].icon = file_entry_icon;
            }
            entries++;
            if (entries == max_entries)
            {
                break;
            }
        }

        /* replace terminating '/' unless root folder */
        if (strlen(path) != (size_t)1)
        {
            path[strlen(path)] = '/';
        }
    }

    return entries;
}

mw_time_t app_get_time_date(void)
{
    mw_time_t time_now;
    rtc_time_t time;

    (void)g_rtc.p_api->calendarTimeGet(g_rtc.p_ctrl, &time);

    time_now.tm_hour = (uint8_t)time.tm_hour;
    time_now.tm_min = (uint8_t)time.tm_min;
    time_now.tm_sec = (uint8_t)time.tm_sec;
    time_now.tm_year = (uint16_t)time.tm_year + 1900U;
    time_now.tm_mon = (uint8_t)time.tm_mon + 1U;
    time_now.tm_mday = (uint8_t)time.tm_mday;

    return (time_now);
}

void app_set_time_date(mw_time_t new_time)
{
    rtc_time_t time;

    time.tm_hour = (int)new_time.tm_hour;
    time.tm_min = (int)new_time.tm_min;
    time.tm_sec = (int)new_time.tm_sec;
    time.tm_year = (int)new_time.tm_year - 1900;
    time.tm_mon = (int)new_time.tm_mon - 1;
    time.tm_mday = (int)new_time.tm_mday;

    (void)fx_system_time_set((UINT)new_time.tm_hour, (UINT)new_time.tm_min, (UINT)new_time.tm_sec);
    (void)fx_system_date_set((UINT)new_time.tm_year, (UINT)new_time.tm_mon, (UINT)new_time.tm_mday);
    (void)g_rtc.p_api->calendarTimeSet(g_rtc.p_ctrl, &time, true);
}
