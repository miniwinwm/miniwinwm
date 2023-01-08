/* generated configuration header file - do not edit */
#ifndef UX_USER_H_
#define UX_USER_H_
#if (SYNERGY_NOT_DEFINED)
        #include "ux_src_user.h"
        #endif
#if (SYNERGY_NOT_DEFINED)
        #include "ux_device_class_storage_user.h"
        #endif
#if (1)
#include "ux_host_class_storage_user.h"
#endif
#if (SYNERGY_NOT_DEFINED)
        #include "ux_host_class_hid_user.h"
        #endif
#if (SYNERGY_NOT_DEFINED)
        #include "ux_device_class_hid_user.h"
        #endif

/*  Generic USBX Project constants follow.  */

#define UX_DISABLE_INCLUDE_SOURCE_CODE

#ifdef TX_ENABLE_EVENT_TRACE
        #ifndef UX_TRACE_INSERT_MACROS
        #define UX_TRACE_INSERT_MACROS
        #endif
        #endif

#if defined(BSP_MCU_GROUP_S124) || defined(BSP_MCU_GROUP_S128) || defined(BSP_MCU_GROUP_S1JA)
        /* Apply Device Only configuration for small foot print Synergy parts to reduce memory size used by USBX. */
        #ifndef UX_SYSTEM_DEVICE_ONLY
        #define UX_SYSTEM_DEVICE_ONLY
        #endif
        #ifndef UX_DEVICE_SIDE_ONLY
        #define UX_DEVICE_SIDE_ONLY
        #endif
        #endif

#ifndef UX_MAX_CLASS_DRIVER
#define UX_MAX_CLASS_DRIVER                                 8
#endif

#ifndef UX_MAX_SLAVE_CLASS_DRIVER
#define UX_MAX_SLAVE_CLASS_DRIVER                           3
#endif

#ifndef UX_MAX_HCD
#define UX_MAX_HCD                                          2
#endif

#ifndef UX_MAX_DEVICES
#define UX_MAX_DEVICES                                      8
#endif

#ifndef UX_MAX_TD
#define UX_MAX_TD                                           128
#endif

#ifndef UX_MAX_ISO_TD
#define UX_MAX_ISO_TD                                       128
#endif

#ifndef UX_THREAD_STACK_SIZE
#ifdef UX_SYSTEM_DEVICE_ONLY
        #define UX_THREAD_STACK_SIZE                                512
        #else
#define UX_THREAD_STACK_SIZE                                1024
#endif
#endif

#ifndef UX_MAX_SLAVE_LUN
#define UX_MAX_SLAVE_LUN                                    2
#endif

#ifndef UX_MAX_HOST_LUN
#define UX_MAX_HOST_LUN                                     16
#endif

#ifndef UX_SLAVE_REQUEST_DATA_MAX_LENGTH
#ifdef UX_SYSTEM_DEVICE_ONLY
        #define UX_SLAVE_REQUEST_DATA_MAX_LENGTH                    512
        #else
#define UX_SLAVE_REQUEST_DATA_MAX_LENGTH                    4096
#endif
#endif
#endif /* UX_USER_H_ */
