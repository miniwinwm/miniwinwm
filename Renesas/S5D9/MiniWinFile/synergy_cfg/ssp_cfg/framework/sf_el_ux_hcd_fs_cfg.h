/* generated configuration header file - do not edit */
#ifndef SF_EL_UX_HCD_FS_CFG_H_
#define SF_EL_UX_HCD_FS_CFG_H_
#include "sf_el_ux_cfg.h"

#if defined(UX_HOST_VBUS_ENABLE_LOW)
            #if !defined(UX_HOST_FS_VBUS_ENABLE_LOW)
            #define UX_HOST_FS_VBUS_ENABLE_LOW
            #endif
            #endif

#if (0)
            #if !defined(UX_HOST_FS_VBUS_ENABLE_LOW)
            #define UX_HOST_FS_VBUS_ENABLE_LOW
            #endif
            #endif
#if ( defined(BSP_BOARD_S7G2_SK) || defined(BSP_BOARD_S5D9_PK) || defined(BSP_BOARD_S5D9_ASK) )
            #ifndef UX_HOST_FS_VBUS_ENABLE_LOW
            #define UX_HOST_FS_VBUS_ENABLE_LOW
            #endif
            #endif

#if (SF_EL_UX_HCD_CFG_FS_IRQ_IPL == BSP_IRQ_DISABLED)
#undef SF_EL_UX_HCD_CFG_FS_IRQ_IPL
#define SF_EL_UX_HCD_CFG_FS_IRQ_IPL      (BSP_IRQ_DISABLED)
#endif

#if (0)
            #if ( defined(BSP_MCU_GROUP_S3A7) || defined(BSP_MCU_GROUP_S3A3) || defined(BSP_MCU_GROUP_S3A6) )
            #ifndef UX_HCD_FS_LDO_ENABLE
            #define UX_HCD_FS_LDO_ENABLE
            #endif
            #endif
            #endif
#endif /* SF_EL_UX_HCD_FS_CFG_H_ */
