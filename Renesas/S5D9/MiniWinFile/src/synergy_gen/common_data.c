/* generated common source file - do not edit */
#include "common_data.h"
#define UX_HOST_INITIALIZE
#define USB_HOST_STORAGE_CLASS_REGISTER
#define FX_COMMON_INITIALIZE (1)
/*******************************************************************************************************************//**
 * @brief     Initialization function that the user can choose to have called automatically during thread entry.
 *            The user can call this function at a later time if desired using the prototype below.
 *            - void fx_common_init0(void)
 **********************************************************************************************************************/
void fx_common_init0(void)
{
    /** Initialize the FileX system. */
    fx_system_initialize ();
}
#if defined(__ICCARM__)
        #define ux_v2_err_callback_WEAK_ATTRIBUTE
        #pragma weak ux_v2_err_callback  = ux_v2_err_callback_internal
        #elif defined(__GNUC__)
        #define ux_v2_err_callback_WEAK_ATTRIBUTE   __attribute__ ((weak, alias("ux_v2_err_callback_internal")))
        #endif
void ux_v2_err_callback(void *p_instance, void *p_data)
ux_v2_err_callback_WEAK_ATTRIBUTE;
/* memory pool allocation used by USBX system. */
CHAR g_ux_pool_memory[63488] =
{ 0 };
/*******************************************************************************************************************//**
 * @brief      This is a weak example initialization error function.  It should be overridden by defining a user  function 
 *             with the prototype below.
 *             - void ux_v2_err_callback(void * p_instance, void * p_data)
 *
 * @param[in]  p_instance arguments used to identify which instance caused the error and p_data Callback arguments used to identify what error caused the callback.
 **********************************************************************************************************************/
void ux_v2_err_callback_internal(void *p_instance, void *p_data);
void ux_v2_err_callback_internal(void *p_instance, void *p_data)
{
    /** Suppress compiler warning for not using parameters. */
    SSP_PARAMETER_NOT_USED (p_instance);
    SSP_PARAMETER_NOT_USED (p_data);

    /** An error has occurred. Please check function arguments for more information. */
    BSP_CFG_HANDLE_UNRECOVERABLE_ERROR (0);
}

#ifdef UX_HOST_INITIALIZE

#ifdef USB_HOST_STORAGE_CLASS_REGISTER

/* A semaphore for synchronizing to the USB media storage mount timing. */
static TX_SEMAPHORE ux_host_storage_semaphore_insertion;

/* Temporary storage place for the pointer to a USBX Host Mass Storage Class Instance. */
static UX_HOST_CLASS_STORAGE *g_ux_new_host_storage_instance;

/* Function prototype for the function to notify changes happened to the USBX Host Class Mass Storage. */
static UINT ux_system_host_storage_change_function(ULONG event, VOID *instance);

/*******************************************************************************************************************//**
 * @brief      This is the function to register the USBX Host Class Mass Storage.
 **********************************************************************************************************************/
void ux_host_stack_class_register_storage(void)
{
    UINT status;
    status = ux_host_stack_class_register (_ux_system_host_class_storage_name, ux_host_class_storage_entry);
    if (UX_SUCCESS != status)
    {
        ux_v2_err_callback (NULL, &status);
    }

    /* Create semaphores used for the USB Mass Storage Media Initialization. */

    if (ux_host_storage_semaphore_insertion.tx_semaphore_id != ((ULONG) 0x53454D41))
    {
        status = tx_semaphore_create (&ux_host_storage_semaphore_insertion, "ux_host_storage_semaphore_insertion", 0);
        if (TX_SUCCESS != status)
        {
            ux_v2_err_callback (NULL, &status);
        }
    }
}

/*******************************************************************************************************************//**
 * @brief      This is the function to notify changes happened to the USBX Host Class Mass Storage.
 * @param[in]  event      Event code from happened to the USBX Host system.
 * @param[in]  instance   Pointer to a USBX Host class instance, which occurs a event.
 * @retval     USBX error code
 **********************************************************************************************************************/
static UINT ux_system_host_storage_change_function(ULONG event, VOID *instance)
{
    if (UX_DEVICE_INSERTION == event) /* Check if there is a device insertion. */
    {
        g_ux_new_host_storage_instance = instance;

        /* Put the semaphore for a USBX Mass Storage Media insertion. */
        tx_semaphore_put (&ux_host_storage_semaphore_insertion);
    }
    else if (UX_DEVICE_REMOVAL == event) /* Check if there is a device removal. */
    {
        g_ux_new_host_storage_instance = NULL;
    }
    return UX_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief      This is the function to get the FileX Media Control Block for a USB Mass Storage device.
 * @param[in]      new_instance     Pointer to a USBX Host Mass Storage Class instance.
 * @param[in/out]  p_storage_media  Pointer of the pointer to save an instance of the USBX Host Mass Storage Media.
 * @param[in/out]  p_fx_media       Pointer of the pointer to save an instance of FileX Media Control Block.
 * @retval     UX_HOST_CLASS_INSTANCE_UNKNOWN  The instance provided was not for a valid Mass Storage device.
 **********************************************************************************************************************/
UINT ux_system_host_storage_fx_media_get(UX_HOST_CLASS_STORAGE *instance, UX_HOST_CLASS_STORAGE_MEDIA **p_storage_media,
        FX_MEDIA **p_fx_media)
{
    UINT error = UX_SUCCESS;
    UX_HOST_CLASS *p_host_class;
    UX_HOST_CLASS_STORAGE_MEDIA *p_storage_media_local;
    FX_MEDIA *p_fx_media_local;
    int index;

    /** Get the USBX Host Mass Storage Class. */
    ux_host_stack_class_get (_ux_system_host_class_storage_name, &p_host_class);

    /** Get the pointer to a media attached to the class container for USB Host Mass Storage. */
    p_storage_media_local = (UX_HOST_CLASS_STORAGE_MEDIA*) p_host_class->ux_host_class_media;

    /** Get the pointer to a FileX Media Control Block. */
    for (index = 0; index < UX_HOST_CLASS_STORAGE_MAX_MEDIA; index++)
    {
        p_fx_media_local = &p_storage_media_local->ux_host_class_storage_media;
        if (p_fx_media_local->fx_media_driver_info != instance)
        {
            /* None of FileX Media Control Blocks matched to this USBX Host Mass Storage Instance. */
            p_storage_media_local++;
        }
        else
        {
            /* Found a FileX Media Control Block used for this USBX Host Mass Storage Instance. */
            break;
        }
    }
    if (UX_HOST_CLASS_STORAGE_MAX_MEDIA == index)
    {
        error = UX_HOST_CLASS_INSTANCE_UNKNOWN;
    }
    else
    {
        *p_storage_media = p_storage_media_local;
        *p_fx_media = p_fx_media_local;
    }

    return error;
}
#endif /* USB_HOST_STORAGE_CLASS_REGISTER */

/*******************************************************************************************************************//**
 * @brief      This is the function to notify a USB event from the USBX Host system.
 * @param[in]  event     Event code from happened to the USBX Host system.
 * @param[in]  usb_class Pointer to a USBX Host class, which occurs a event.
 * @param[in]  instance  Pointer to a USBX Host class instance, which occurs a event.
 * @retval     USBX error code
 **********************************************************************************************************************/
UINT ux_system_host_change_function(ULONG event, UX_HOST_CLASS *host_class, VOID *instance)
{
    UINT status = UX_SUCCESS;
    SSP_PARAMETER_NOT_USED (event);
    SSP_PARAMETER_NOT_USED (host_class);
    SSP_PARAMETER_NOT_USED (instance);

#if !defined(usb_host_plug_event_notification)
    /* Call user function back for USBX Host Class event notification. */
    status = usb_host_plug_event_notification (event, host_class, instance);
    if (UX_SUCCESS != status)
    {
        return status;
    }
#endif

#ifdef USB_HOST_STORAGE_CLASS_REGISTER
    /* Check the class container if it is for a USBX Host Mass Storage class. */
    if (UX_SUCCESS
            == _ux_utility_memory_compare (_ux_system_host_class_storage_name, host_class,
                                           _ux_utility_string_length_get (_ux_system_host_class_storage_name)))
    {
        status = ux_system_host_storage_change_function (event, instance);
    }
#endif
    return status;
}
#endif

#ifdef USB_HOST_HID_CLASS_REGISTER
            /* Function prototype to register USBX Host HID Clients to the USBX Host system. */
            static void ux_host_class_hid_clients_register(void);
#endif

/*******************************************************************************************************************//**
 * @brief     Initialization function that the user can choose to have called automatically during thread entry.
 *            The user can call this function at a later time if desired using the prototype below.
 *            - void ux_common_init0(void)
 **********************************************************************************************************************/
void ux_common_init0(void)
{
    UINT status_ux_init;

    /** Initialize the USBX system. */
    status_ux_init = ux_system_initialize ((CHAR*) g_ux_pool_memory, 63488, UX_NULL, 0);
    if (UX_SUCCESS != status_ux_init)
    {
        ux_v2_err_callback (NULL, &status_ux_init);
    }

#ifdef UX_HOST_INITIALIZE
    /** Initialize the USBX Host stack. */
    status_ux_init = ux_host_stack_initialize (ux_system_host_change_function);
    if (UX_SUCCESS != status_ux_init)
    {
        ux_v2_err_callback (NULL, &status_ux_init);
    }

    /** Register USB Host classes. */
#ifdef USB_HOST_HUB_CLASS_REGISTER
                status_ux_init =  ux_host_stack_class_register(_ux_system_host_class_hub_name, ux_host_class_hub_entry);
                if (UX_SUCCESS != status_ux_init)
                {
                    ux_v2_err_callback(NULL,&status_ux_init);
                }
#endif

#ifdef USB_HOST_CDC_ACM_CLASS_REGISTER
                status_ux_init =  ux_host_stack_class_register(_ux_system_host_class_cdc_acm_name, ux_host_class_cdc_acm_entry);
                if (UX_SUCCESS != status_ux_init)
                {
                    ux_v2_err_callback(NULL,&status_ux_init);
                }
#endif

#ifdef USB_HOST_HID_CLASS_REGISTER
                status_ux_init =  ux_host_stack_class_register(_ux_system_host_class_hid_name, ux_host_class_hid_entry);
                if (UX_SUCCESS != status_ux_init)
                {
                    ux_v2_err_callback(NULL,&status_ux_init);
                }
            
                ux_host_class_hid_clients_register ();
#endif

#ifdef USB_HOST_STORAGE_CLASS_REGISTER
    ux_host_stack_class_register_storage ();
#endif

#ifdef USB_HOST_VIDEO_CLASS_REGISTER
                status_ux_init =  ux_host_stack_class_register(_ux_system_host_class_video_name, ux_host_class_video_entry);
                if (UX_SUCCESS != status_ux_init)
                {
                    ux_v2_err_callback(NULL,&status_ux_init);
                }
#endif

#ifdef USB_HOST_AUDIO_CLASS_REGISTER
                status_ux_init =  ux_host_stack_class_register(_ux_system_host_class_audio_name, ux_host_class_audio_entry);
                if (UX_SUCCESS != status_ux_init)
                {
                    ux_v2_err_callback(NULL,&status_ux_init);
                }
#endif

#ifdef USB_HOST_PRINTER_CLASS_REGISTER
                status_ux_init =  ux_host_stack_class_register(_ux_system_host_class_printer_name, _ux_host_class_printer_entry);
                if (UX_SUCCESS != status_ux_init)
                {
                    ux_v2_err_callback(NULL,&status_ux_init);
                }
#endif

#endif /* UX_HOST_INITIALIZE */
}
#if (2) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_transfer3) && !defined(SSP_SUPPRESS_ISR_DMACELC_EVENT_ELC_SOFTWARE_EVENT_1)
SSP_VECTOR_DEFINE_CHAN(dmac_int_isr, DMAC, INT, 1);
#endif
#endif
dmac_instance_ctrl_t g_transfer3_ctrl;
transfer_info_t g_transfer3_info =
{ .dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
  .repeat_area = TRANSFER_REPEAT_AREA_DESTINATION,
  .irq = TRANSFER_IRQ_EACH,
  .chain_mode = TRANSFER_CHAIN_MODE_DISABLED,
  .src_addr_mode = TRANSFER_ADDR_MODE_FIXED,
  .size = TRANSFER_SIZE_1_BYTE,
  .mode = TRANSFER_MODE_BLOCK,
  .p_dest = (void*) NULL,
  .p_src = (void const*) NULL,
  .num_blocks = 0,
  .length = 0, };
const transfer_on_dmac_cfg_t g_transfer3_extend =
{ .channel = 1, .offset_byte = 0, };
const transfer_cfg_t g_transfer3_cfg =
{ .p_info = &g_transfer3_info, .activation_source = ELC_EVENT_ELC_SOFTWARE_EVENT_1, .auto_enable = false, .p_callback =
          NULL,
  .p_context = &g_transfer3, .irq_ipl = (2), .p_extend = &g_transfer3_extend, };
/* Instance structure to use this module. */
const transfer_instance_t g_transfer3 =
{ .p_ctrl = &g_transfer3_ctrl, .p_cfg = &g_transfer3_cfg, .p_api = &g_transfer_on_dmac };
#if (2) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_transfer2) && !defined(SSP_SUPPRESS_ISR_DMACELC_EVENT_ELC_SOFTWARE_EVENT_0)
SSP_VECTOR_DEFINE_CHAN(dmac_int_isr, DMAC, INT, 0);
#endif
#endif
dmac_instance_ctrl_t g_transfer2_ctrl;
transfer_info_t g_transfer2_info =
{ .dest_addr_mode = TRANSFER_ADDR_MODE_FIXED,
  .repeat_area = TRANSFER_REPEAT_AREA_SOURCE,
  .irq = TRANSFER_IRQ_EACH,
  .chain_mode = TRANSFER_CHAIN_MODE_DISABLED,
  .src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
  .size = TRANSFER_SIZE_1_BYTE,
  .mode = TRANSFER_MODE_BLOCK,
  .p_dest = (void*) NULL,
  .p_src = (void const*) NULL,
  .num_blocks = 0,
  .length = 0, };
const transfer_on_dmac_cfg_t g_transfer2_extend =
{ .channel = 0, .offset_byte = 0, };
const transfer_cfg_t g_transfer2_cfg =
{ .p_info = &g_transfer2_info, .activation_source = ELC_EVENT_ELC_SOFTWARE_EVENT_0, .auto_enable = false, .p_callback =
          NULL,
  .p_context = &g_transfer2, .irq_ipl = (2), .p_extend = &g_transfer2_extend, };
/* Instance structure to use this module. */
const transfer_instance_t g_transfer2 =
{ .p_ctrl = &g_transfer2_ctrl, .p_cfg = &g_transfer2_cfg, .p_api = &g_transfer_on_dmac };
/***********************************************************************************************************************
 * Registers Interrupt Vector for USBHS Controller.
 **********************************************************************************************************************/
#if (SF_EL_UX_HCD_CFG_HS_IRQ_IPL != BSP_IRQ_DISABLED)
            /* USBHS ISR vector registering. */
            #if !defined(SSP_SUPPRESS_ISR_g_sf_el_ux_hcd_hs_0) && !defined(SSP_SUPPRESS_ISR_USB)
            #if !defined(UX_DCD_SYNERGY_USBHS_VECTOR)
            SSP_VECTOR_DEFINE_UNIT(usbhs_usb_int_resume_isr, USB, HS, USB_INT_RESUME, 0);
            #endif
            #endif
            #endif

#undef SYNERGY_NOT_DEFINED
#define SYNERGY_NOT_DEFINED (1)
/***********************************************************************************************************************
 * The definition of wrapper interface for USBX Synergy Port HCD Driver.
 **********************************************************************************************************************/
static UINT g_sf_el_ux_hcd_hs_0_initialize(UX_HCD *hcd)
{
#if ((SYNERGY_NOT_DEFINED != g_transfer2) && (SYNERGY_NOT_DEFINED != g_transfer3))
    /* DMA support */
    UX_HCD_SYNERGY_TRANSFER hcd_transfer;
    hcd_transfer.ux_synergy_transfer_tx = (transfer_instance_t*) &g_transfer2;
    hcd_transfer.ux_synergy_transfer_rx = (transfer_instance_t*) &g_transfer3;
    return (UINT) ux_hcd_synergy_initialize_transfer_support (hcd, (UX_HCD_SYNERGY_TRANSFER*) &hcd_transfer);
#else
                /* Non DMA support */
                return (UINT)ux_hcd_synergy_initialize(hcd);
            #endif
} /* End of function g_sf_el_ux_hcd_hs_0_initialize() */
#undef SYNERGY_NOT_DEFINED
#if defined(__ICCARM__)
              #define g_ux_host_0_err_callback_WEAK_ATTRIBUTE
              #pragma weak g_ux_host_0_err_callback  = g_ux_host_0_err_callback_internal
              #elif defined(__GNUC__)
              #define g_ux_host_0_err_callback_WEAK_ATTRIBUTE   __attribute__ ((weak, alias("g_ux_host_0_err_callback_internal")))
              #endif
void g_ux_host_0_err_callback(void *p_instance, void *p_data)
g_ux_host_0_err_callback_WEAK_ATTRIBUTE;
/*******************************************************************************************************************//**
 * @brief      This is a weak example initialization error function.  It should be overridden by defining a user  function 
 *             with the prototype below.
 *             - void g_ux_host_0_err_callback(void * p_instance, void * p_data)
 *
 * @param[in]  p_instance arguments used to identify which instance caused the error and p_data Callback arguments used to identify what error caused the callback.
 **********************************************************************************************************************/
void g_ux_host_0_err_callback_internal(void *p_instance, void *p_data);
void g_ux_host_0_err_callback_internal(void *p_instance, void *p_data)
{
    /** Suppress compiler warning for not using parameters. */
    SSP_PARAMETER_NOT_USED (p_instance);
    SSP_PARAMETER_NOT_USED (p_data);

    /** An error has occurred. Please check function arguments for more information. */
    BSP_CFG_HANDLE_UNRECOVERABLE_ERROR (0);
}
/*******************************************************************************************************************//**
 * @brief     Initialization function that the user can choose to have called automatically during thread entry.
 *            The user can call this function at a later time if desired using the prototype below.
 *            - void ux_host_init0(void)
 **********************************************************************************************************************/
void ux_host_init0(void)
{
    /** Register a USB host controller. */
    UINT status_g_ux_host_0 = ux_host_stack_hcd_register ((UCHAR*) "g_sf_el_ux_hcd_hs_0",
                                                          g_sf_el_ux_hcd_hs_0_initialize, R_USBHS_BASE,
                                                          UX_SYNERGY_CONTROLLER);
    if (UX_SUCCESS != status_g_ux_host_0)
    {
        g_ux_host_0_err_callback (NULL, &status_g_ux_host_0);
    }
}
/* Pointer to a USBX Host Mass Storage Class Instance */
UX_HOST_CLASS_STORAGE *g_ux_host_class_storage0;
/* A pointer to FileX Media Control Block for a USB flash device. */
FX_MEDIA *g_fx_media0_ptr;

/* Pointer to a USBX Host Mass Storage Class Media. */
UX_HOST_CLASS_STORAGE_MEDIA *g_ux_host_class_storage0_media;

#if defined(__ICCARM__)
            #define g_fx_media0_err_callback_failed_to_get_fx_media_WEAK_ATTRIBUTE
            #pragma weak g_fx_media0_err_callback_failed_to_get_fx_media  = g_fx_media0_err_callback_failed_to_get_fx_media_internal
            #elif defined(__GNUC__)
            #define g_fx_media0_err_callback_failed_to_get_fx_media_WEAK_ATTRIBUTE __attribute__ ((weak, alias("g_fx_media0_err_callback_failed_to_get_fx_media_internal")))
            #endif
void g_fx_media0_err_callback_failed_to_get_fx_media(void *p_instance, void *p_data)
g_fx_media0_err_callback_failed_to_get_fx_media_WEAK_ATTRIBUTE;

/* Function prototype for the weak initialization error function. */
void g_fx_media0_err_callback_failed_to_get_fx_media_internal(void *p_instance, void *p_data);

/*******************************************************************************************************************//**
 * @brief      This is a weak example initialization error function.  It should be overridden by defining a user function
 *             with the prototype below.
 *             - void g_fx_media0_err_callback_failed_to_get_fx_media(void * p_instance, void * p_data)
 *
 * @param[in]  p_instance  Not used.
 * @param[in]  p_data      Not used.
 **********************************************************************************************************************/
void g_fx_media0_err_callback_failed_to_get_fx_media_internal(void *p_instance, void *p_data)
{
    /** Suppress compiler warning for not using parameters. */
    SSP_PARAMETER_NOT_USED (p_instance);
    SSP_PARAMETER_NOT_USED (p_data);

    /** A FileX media control block for a USB mass storage device was not found. */
    BSP_CFG_HANDLE_UNRECOVERABLE_ERROR (0);
}

/*******************************************************************************************************************//**
 * @brief      This is the function to get g_fx_media0 for a USB Mass Storage device.
 **********************************************************************************************************************/
void fx_media_init_function0(void)
{
    /** Suspend the thread until a USB Mass Storage Device inserted. */
    UINT err_g_fx_media0_semaphore_get = tx_semaphore_get (&ux_host_storage_semaphore_insertion, 1000);
    if (TX_SUCCESS != err_g_fx_media0_semaphore_get)
    {
        g_fx_media0_err_callback_failed_to_get_fx_media (&ux_host_storage_semaphore_insertion,
                                                         &err_g_fx_media0_semaphore_get);
    }

    /** Initialize the FileX Media Control Block g_fx_media0 for a USB Mass Storage device. */
    /** Get the pointer to a USBX Host Mass Storage Instance. */
    g_ux_host_class_storage0 = g_ux_new_host_storage_instance;

    /** Initialize the FileX Media Control Block g_fx_media0 for a USB Mass Storage device. */
    UINT err_g_fx_media0_get = ux_system_host_storage_fx_media_get (g_ux_new_host_storage_instance,
                                                                    &g_ux_host_class_storage0_media, &g_fx_media0_ptr);
    if (UX_SUCCESS != err_g_fx_media0_get)
    {
        g_fx_media0_err_callback_failed_to_get_fx_media (&g_fx_media0_ptr, &err_g_fx_media0_get);
    }
}
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_transfer5) && !defined(SSP_SUPPRESS_ISR_DTCELC_EVENT_IIC2_RXI)
#define DTC_ACTIVATION_SRC_ELC_EVENT_IIC2_RXI
#if defined(DTC_ACTIVATION_SRC_ELC_EVENT_ELC_SOFTWARE_EVENT_0) && !defined(DTC_VECTOR_DEFINED_SOFTWARE_EVENT_0)
SSP_VECTOR_DEFINE(elc_software_event_isr, ELC, SOFTWARE_EVENT_0);
#define DTC_VECTOR_DEFINED_SOFTWARE_EVENT_0
#endif
#if defined(DTC_ACTIVATION_SRC_ELC_EVENT_ELC_SOFTWARE_EVENT_1) && !defined(DTC_VECTOR_DEFINED_SOFTWARE_EVENT_1)
SSP_VECTOR_DEFINE(elc_software_event_isr, ELC, SOFTWARE_EVENT_1);
#define DTC_VECTOR_DEFINED_SOFTWARE_EVENT_1
#endif
#endif
#endif

dtc_instance_ctrl_t g_transfer5_ctrl;
transfer_info_t g_transfer5_info =
{ .dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
  .repeat_area = TRANSFER_REPEAT_AREA_DESTINATION,
  .irq = TRANSFER_IRQ_END,
  .chain_mode = TRANSFER_CHAIN_MODE_DISABLED,
  .src_addr_mode = TRANSFER_ADDR_MODE_FIXED,
  .size = TRANSFER_SIZE_1_BYTE,
  .mode = TRANSFER_MODE_NORMAL,
  .p_dest = (void*) NULL,
  .p_src = (void const*) NULL,
  .num_blocks = 0,
  .length = 0, };
const transfer_cfg_t g_transfer5_cfg =
{ .p_info = &g_transfer5_info,
  .activation_source = ELC_EVENT_IIC2_RXI,
  .auto_enable = false,
  .p_callback = NULL,
  .p_context = &g_transfer5,
  .irq_ipl = (BSP_IRQ_DISABLED) };
/* Instance structure to use this module. */
const transfer_instance_t g_transfer5 =
{ .p_ctrl = &g_transfer5_ctrl, .p_cfg = &g_transfer5_cfg, .p_api = &g_transfer_on_dtc };
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_transfer4) && !defined(SSP_SUPPRESS_ISR_DTCELC_EVENT_IIC2_TXI)
#define DTC_ACTIVATION_SRC_ELC_EVENT_IIC2_TXI
#if defined(DTC_ACTIVATION_SRC_ELC_EVENT_ELC_SOFTWARE_EVENT_0) && !defined(DTC_VECTOR_DEFINED_SOFTWARE_EVENT_0)
SSP_VECTOR_DEFINE(elc_software_event_isr, ELC, SOFTWARE_EVENT_0);
#define DTC_VECTOR_DEFINED_SOFTWARE_EVENT_0
#endif
#if defined(DTC_ACTIVATION_SRC_ELC_EVENT_ELC_SOFTWARE_EVENT_1) && !defined(DTC_VECTOR_DEFINED_SOFTWARE_EVENT_1)
SSP_VECTOR_DEFINE(elc_software_event_isr, ELC, SOFTWARE_EVENT_1);
#define DTC_VECTOR_DEFINED_SOFTWARE_EVENT_1
#endif
#endif
#endif

dtc_instance_ctrl_t g_transfer4_ctrl;
transfer_info_t g_transfer4_info =
{ .dest_addr_mode = TRANSFER_ADDR_MODE_FIXED,
  .repeat_area = TRANSFER_REPEAT_AREA_SOURCE,
  .irq = TRANSFER_IRQ_END,
  .chain_mode = TRANSFER_CHAIN_MODE_DISABLED,
  .src_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
  .size = TRANSFER_SIZE_1_BYTE,
  .mode = TRANSFER_MODE_NORMAL,
  .p_dest = (void*) NULL,
  .p_src = (void const*) NULL,
  .num_blocks = 0,
  .length = 0, };
const transfer_cfg_t g_transfer4_cfg =
{ .p_info = &g_transfer4_info,
  .activation_source = ELC_EVENT_IIC2_TXI,
  .auto_enable = false,
  .p_callback = NULL,
  .p_context = &g_transfer4,
  .irq_ipl = (BSP_IRQ_DISABLED) };
/* Instance structure to use this module. */
const transfer_instance_t g_transfer4 =
{ .p_ctrl = &g_transfer4_ctrl, .p_cfg = &g_transfer4_cfg, .p_api = &g_transfer_on_dtc };
#if !defined(SSP_SUPPRESS_ISR_g_i2c) && !defined(SSP_SUPPRESS_ISR_IIC2)
SSP_VECTOR_DEFINE_CHAN(iic_rxi_isr, IIC, RXI, 2);
#endif
#if !defined(SSP_SUPPRESS_ISR_g_i2c) && !defined(SSP_SUPPRESS_ISR_IIC2)
SSP_VECTOR_DEFINE_CHAN(iic_txi_isr, IIC, TXI, 2);
#endif
#if !defined(SSP_SUPPRESS_ISR_g_i2c) && !defined(SSP_SUPPRESS_ISR_IIC2)
SSP_VECTOR_DEFINE_CHAN(iic_tei_isr, IIC, TEI, 2);
#endif
#if !defined(SSP_SUPPRESS_ISR_g_i2c) && !defined(SSP_SUPPRESS_ISR_IIC2)
SSP_VECTOR_DEFINE_CHAN(iic_eri_isr, IIC, ERI, 2);
#endif
riic_instance_ctrl_t g_i2c_ctrl;
const riic_extended_cfg g_i2c_extend =
{ .timeout_mode = RIIC_TIMEOUT_MODE_SHORT, };
const i2c_cfg_t g_i2c_cfg =
        { .channel = 2, .rate = I2C_RATE_FAST, .slave = 0, .addr_mode = I2C_ADDR_MODE_7BIT, .sda_delay = 0,
#define SYNERGY_NOT_DEFINED (1)            
#if (SYNERGY_NOT_DEFINED == g_transfer4)
                .p_transfer_tx       = NULL,
#else
          .p_transfer_tx = &g_transfer4,
#endif
#if (SYNERGY_NOT_DEFINED == g_transfer5)
                .p_transfer_rx       = NULL,
#else
          .p_transfer_rx = &g_transfer5,
#endif
#undef SYNERGY_NOT_DEFINED	
          .p_callback = NULL,
          .p_context = (void*) &g_i2c, .rxi_ipl = (3), .txi_ipl = (3), .tei_ipl = (3), .eri_ipl = (3), .p_extend =
                  &g_i2c_extend, };
/* Instance structure to use this module. */
const i2c_master_instance_t g_i2c =
{ .p_ctrl = &g_i2c_ctrl, .p_cfg = &g_i2c_cfg, .p_api = &g_i2c_master_on_riic };
static TX_MUTEX sf_bus_mutex_g_sf_i2c_bus0;
static TX_EVENT_FLAGS_GROUP sf_bus_eventflag_g_sf_i2c_bus0;
static sf_i2c_instance_ctrl_t *sf_curr_ctrl_g_sf_i2c_bus0;
static sf_i2c_instance_ctrl_t *sf_curr_bus_ctrl_g_sf_i2c_bus0;
sf_i2c_bus_t g_sf_i2c_bus0 =
{ .p_bus_name = (uint8_t*) "g_sf_i2c_bus0",
  .channel = 2,
  .p_lock_mutex = &sf_bus_mutex_g_sf_i2c_bus0,
  .p_sync_eventflag = &sf_bus_eventflag_g_sf_i2c_bus0,
  .pp_curr_ctrl = (sf_i2c_ctrl_t**) &sf_curr_ctrl_g_sf_i2c_bus0,
  .p_lower_lvl_api = (i2c_api_master_t*) &g_i2c_master_on_riic,
  .device_count = 0,
  .pp_curr_bus_ctrl = (sf_i2c_ctrl_t**) &sf_curr_bus_ctrl_g_sf_i2c_bus0, };
const cgc_instance_t g_cgc =
{ .p_api = &g_cgc_on_cgc, .p_cfg = NULL };
const ioport_instance_t g_ioport =
{ .p_api = &g_ioport_on_ioport, .p_cfg = NULL };
const elc_instance_t g_elc =
{ .p_api = &g_elc_on_elc, .p_cfg = NULL };
/* Instance structure to use this module. */
const fmi_instance_t g_fmi =
{ .p_api = &g_fmi_on_fmi };
void g_common_init(void)
{
    /** Call initialization function if user has selected to do so. */
#if FX_COMMON_INITIALIZE
    fx_common_init0 ();
#endif
    /** Call initialization function if user has selected to do so. */
#if (1)
    ux_common_init0 ();
#endif
    /** Call initialization function if user has selected to do so. */
#if (1)
    ux_host_init0 ();
#endif

#if (0)
            /** Call FileX Media Control Block initialization function. Can call at later time as well. */
            fx_media_init_function0();
#endif
}
