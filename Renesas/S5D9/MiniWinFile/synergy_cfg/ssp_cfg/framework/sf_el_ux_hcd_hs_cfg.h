/* generated configuration header file - do not edit */
#ifndef SF_EL_UX_HCD_HS_CFG_H_
#define SF_EL_UX_HCD_HS_CFG_H_
#include "sf_el_ux_cfg.h"

#if (0)
            #define UX_SYNERGY_MAX_BULK_PAYLOAD (0)
            #define UX_SYNERGY_MAX_ISO_PAYLOAD  (0)
            #endif

#define UX_SYNERGY_BULK_PIPE_START_INDEX (1UL)

#if defined(UX_HOST_VBUS_ENABLE_LOW)
            #if !defined(UX_HOST_HS_VBUS_ENABLE_LOW)
            #define UX_HOST_HS_VBUS_ENABLE_LOW
            #endif
            #endif

#if (1)
#if !defined(UX_HOST_HS_VBUS_ENABLE_LOW)
#define UX_HOST_HS_VBUS_ENABLE_LOW
#endif
#endif
#if ( defined(BSP_BOARD_S7G2_SK) || defined(BSP_BOARD_S5D9_PK) || defined(BSP_BOARD_S5D9_ASK) )
            #ifndef UX_HOST_HS_VBUS_ENABLE_LOW
            #define UX_HOST_HS_VBUS_ENABLE_LOW
            #endif
            #endif

#if ((1) == 0)
            #define UX_HOST_DISABLE_HS 
            #endif

#if (SF_EL_UX_HCD_CFG_HS_IRQ_IPL == BSP_IRQ_DISABLED)
#undef SF_EL_UX_HCD_CFG_HS_IRQ_IPL
#define SF_EL_UX_HCD_CFG_HS_IRQ_IPL      (3)
#define UX_HCD_SYNERY_USE_USBHS
#endif
#endif /* SF_EL_UX_HCD_HS_CFG_H_ */
