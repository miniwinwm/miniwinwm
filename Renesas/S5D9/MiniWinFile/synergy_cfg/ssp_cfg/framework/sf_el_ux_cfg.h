/* generated configuration header file - do not edit */
#ifndef SF_EL_UX_CFG_H_
#define SF_EL_UX_CFG_H_
#if (0)
            #if !defined(UX_HOST_VBUS_ENABLE_LOW)
            #define UX_HOST_VBUS_ENABLE_LOW
            #endif
            #if ( defined(BSP_BOARD_S7G2_SK) || defined(BSP_BOARD_S5D9_PK) || defined(BSP_BOARD_S5D9_ASK) )
            #ifndef UX_HOST_VBUS_ENABLE_LOW
            #define UX_HOST_VBUS_ENABLE_LOW
            #endif
            #endif
            #endif

#if ((BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED)
            #define UX_HCD_SYNERY_USE_USBHS
            #define UX_DCD_SYNERY_USE_USBHS
            #endif

#define SF_EL_UX_HCD_CFG_HS_IRQ_IPL      (BSP_IRQ_DISABLED)
#define SF_EL_UX_DCD_CFG_HS_IRQ_IPL      (BSP_IRQ_DISABLED)
#define SF_EL_UX_HCD_CFG_FS_IRQ_IPL      (BSP_IRQ_DISABLED)
#define SF_EL_UX_DCD_CFG_FS_IRQ_IPL      (BSP_IRQ_DISABLED)
#endif /* SF_EL_UX_CFG_H_ */
