/* generated thread header file - do not edit */
#ifndef FILE_THREAD_H_
#define FILE_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void file_thread_entry(void);
                #else
extern void file_thread_entry(void);
#endif
#include "r_rtc.h"
#include "r_rtc_api.h"
#ifdef __cplusplus
extern "C" {
#endif
/** RTC on RTC Instance. */
extern const rtc_instance_t g_rtc;
#ifndef NULL
void NULL(rtc_callback_args_t *p_args);
#endif
extern TX_EVENT_FLAGS_GROUP g_usb_plug_events;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* FILE_THREAD_H_ */
