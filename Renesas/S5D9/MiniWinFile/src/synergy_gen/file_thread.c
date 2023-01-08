/* generated thread source file - do not edit */
#include "file_thread.h"

TX_THREAD file_thread;
void file_thread_create(void);
static void file_thread_func(ULONG thread_input);
static uint8_t file_thread_stack[4096] BSP_PLACE_IN_SECTION_V2(".stack.file_thread") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_rtc) && !defined(SSP_SUPPRESS_ISR_RTC)
SSP_VECTOR_DEFINE(rtc_alarm_isr, RTC, ALARM);
#endif
#endif
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_rtc) && !defined(SSP_SUPPRESS_ISR_RTC)
SSP_VECTOR_DEFINE(rtc_period_isr, RTC, PERIOD);
#endif
#endif
#if (12) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_rtc) && !defined(SSP_SUPPRESS_ISR_RTC)
SSP_VECTOR_DEFINE( rtc_carry_isr, RTC, CARRY);
#endif
#endif
rtc_instance_ctrl_t g_rtc_ctrl;
const rtc_cfg_t g_rtc_cfg =
{ .clock_source = RTC_CLOCK_SOURCE_LOCO,
  .hw_cfg = true,
  .error_adjustment_value = 0,
  .error_adjustment_type = RTC_ERROR_ADJUSTMENT_NONE,
  .p_callback = NULL,
  .p_context = &g_rtc,
  .alarm_ipl = (BSP_IRQ_DISABLED),
  .periodic_ipl = (BSP_IRQ_DISABLED),
  .carry_ipl = (12), };
/* Instance structure to use this module. */
const rtc_instance_t g_rtc =
{ .p_ctrl = &g_rtc_ctrl, .p_cfg = &g_rtc_cfg, .p_api = &g_rtc_on_rtc };
TX_EVENT_FLAGS_GROUP g_usb_plug_events;
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void file_thread_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_g_usb_plug_events;
    err_g_usb_plug_events = tx_event_flags_create (&g_usb_plug_events, (CHAR*) "USB Plug Event Flags");
    if (TX_SUCCESS != err_g_usb_plug_events)
    {
        tx_startup_err_callback (&g_usb_plug_events, 0);
    }

    UINT err;
    err = tx_thread_create (&file_thread, (CHAR*) "File Thread", file_thread_func, (ULONG) NULL, &file_thread_stack,
                            4096, 1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&file_thread, 0);
    }
}

static void file_thread_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    file_thread_entry ();
}
