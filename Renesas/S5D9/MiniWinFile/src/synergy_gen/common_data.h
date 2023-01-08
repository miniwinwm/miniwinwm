/* generated common header file - do not edit */
#ifndef COMMON_DATA_H_
#define COMMON_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "fx_api.h"
#include "r_dmac.h"
#include "r_transfer_api.h"
#include "ux_api.h"
#include "ux_host_class_storage.h"
#include "r_dtc.h"
#include "r_transfer_api.h"
#include "r_riic.h"
#include "r_i2c_api.h"
#include "r_i2c_api.h"
#include "sf_i2c.h"
#include "sf_i2c_api.h"
#include "r_cgc.h"
#include "r_cgc_api.h"
#include "r_ioport.h"
#include "r_ioport_api.h"
#include "r_elc.h"
#include "r_elc_api.h"
#include "r_fmi.h"
#include "r_fmi_api.h"
#ifdef __cplusplus
extern "C" {
#endif
void fx_common_init0(void);
#include "ux_api.h"

/* USBX Host Stack initialization error callback function. User can override the function if needed. */
void ux_v2_err_callback(void *p_instance, void *p_data);

#if !defined(usb_host_plug_event_notification)
/* User Callback for Host Event Notification (Only valid for USB Host). */
extern UINT usb_host_plug_event_notification(ULONG event, UX_HOST_CLASS *host_class, VOID *instance);
#endif

#if !defined(NULL)
/* User Callback for Device Event Notification (Only valid for USB Device). */
extern UINT NULL(ULONG event);
#endif

#ifdef UX_HOST_CLASS_STORAGE_H
            /* Utility function to get the pointer to a FileX Media Control Block for a USB Mass Storage device. */
            UINT ux_system_host_storage_fx_media_get(UX_HOST_CLASS_STORAGE * instance, UX_HOST_CLASS_STORAGE_MEDIA ** p_storage_media, FX_MEDIA ** p_fx_media);
#endif
void ux_common_init0(void);

/* Function prototype for the function to register the USBX Host Class Mass Storage. */
void ux_host_stack_class_register_storage(void);
/* Function prototype for the function to notify a USB event from the USBX Host system. */
UINT ux_system_host_change_function(ULONG event, UX_HOST_CLASS *host_class, VOID *instance);
/* memory pool allocation used by USBX system. */
extern CHAR g_ux_pool_memory[];
/* Transfer on DMAC Instance. */
extern const transfer_instance_t g_transfer3;
#ifndef NULL
void NULL(transfer_callback_args_t *p_args);
#endif
/* Transfer on DMAC Instance. */
extern const transfer_instance_t g_transfer2;
#ifndef NULL
void NULL(transfer_callback_args_t *p_args);
#endif
#include "ux_api.h"
#include "ux_hcd_synergy.h"
#include "sf_el_ux_hcd_hs_cfg.h"
void g_ux_host_0_err_callback(void *p_instance, void *p_data);
void ux_host_init0(void);
#include "ux_api.h"
#include "ux_host_class_storage.h"

/* Pointer to a USBX Host Mass Storage Class Instance */
extern UX_HOST_CLASS_STORAGE *g_ux_host_class_storage0;
/* A pointer to FileX Media Control Block for a USB flash device */
extern FX_MEDIA *g_fx_media0_ptr;

/* Pointer to a USBX Host Mass Storage Class Media */
extern UX_HOST_CLASS_STORAGE_MEDIA *g_ux_host_class_storage0_media;

/* Macro to dereference a pointer to FileX Media Control Block for a USB flash device */
#define  g_fx_media0 (*(FX_MEDIA*)g_fx_media0_ptr)

/* The function prototype of getting g_fx_media0 for a USB Mass Storage device. */
void fx_media_init_function0(void);

/* FileX media initialization error callback function for USBX Host Mass Storage. User can override the function if needed. */
void g_fx_media0_err_callback_failed_to_get_fx_media(void *p_instance, void *p_data);
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer5;
#ifndef NULL
void NULL(transfer_callback_args_t *p_args);
#endif
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer4;
#ifndef NULL
void NULL(transfer_callback_args_t *p_args);
#endif
extern const i2c_cfg_t g_i2c_cfg;
/** I2C on RIIC Instance. */
extern const i2c_master_instance_t g_i2c;
#ifndef NULL
void NULL(i2c_callback_args_t *p_args);
#endif

extern riic_instance_ctrl_t g_i2c_ctrl;
extern const riic_extended_cfg g_i2c_extend;
#define SYNERGY_NOT_DEFINED (1)            
#if (SYNERGY_NOT_DEFINED == g_transfer4)
    #define g_i2c_P_TRANSFER_TX (NULL)
#else
#define g_i2c_P_TRANSFER_TX (&g_transfer4)
#endif
#if (SYNERGY_NOT_DEFINED == g_transfer5)
    #define g_i2c_P_TRANSFER_RX (NULL)
#else
#define g_i2c_P_TRANSFER_RX (&g_transfer5)
#endif
#undef SYNERGY_NOT_DEFINED
#define g_i2c_P_EXTEND (&g_i2c_extend)
extern sf_i2c_bus_t g_sf_i2c_bus0;
extern i2c_api_master_t const g_i2c_master_on_riic;

#define g_sf_i2c_bus0_CHANNEL        (2)
#define g_sf_i2c_bus0_RATE           (I2C_RATE_FAST)
#define g_sf_i2c_bus0_SLAVE          (0)
#define g_sf_i2c_bus0_ADDR_MODE      (I2C_ADDR_MODE_7BIT)          
#define g_sf_i2c_bus0_SDA_DELAY      (0)  
#define g_sf_i2c_bus0_P_CALLBACK     (NULL)
#define g_sf_i2c_bus0_P_CONTEXT      (&g_i2c)
#define g_sf_i2c_bus0_RXI_IPL        ((3))
#define g_sf_i2c_bus0_TXI_IPL        ((3))
#define g_sf_i2c_bus0_TEI_IPL        ((3))            
#define g_sf_i2c_bus0_ERI_IPL        ((3))

/** These are obtained by macros in the I2C driver XMLs. */
#define g_sf_i2c_bus0_P_TRANSFER_TX  (g_i2c_P_TRANSFER_TX)
#define g_sf_i2c_bus0_P_TRANSFER_RX  (g_i2c_P_TRANSFER_RX)            
#define g_sf_i2c_bus0_P_EXTEND       (g_i2c_P_EXTEND)
/** CGC Instance */
extern const cgc_instance_t g_cgc;
/** IOPORT Instance */
extern const ioport_instance_t g_ioport;
/** ELC Instance */
extern const elc_instance_t g_elc;
/** FMI on FMI Instance. */
extern const fmi_instance_t g_fmi;
void g_common_init(void);
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* COMMON_DATA_H_ */
