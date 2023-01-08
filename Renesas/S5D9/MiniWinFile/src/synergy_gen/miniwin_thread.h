/* generated thread header file - do not edit */
#ifndef MINIWIN_THREAD_H_
#define MINIWIN_THREAD_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void miniwin_thread_entry(void);
                #else
extern void miniwin_thread_entry(void);
#endif
#include "r_glcd.h"
#include "r_display_api.h"
#include "r_icu.h"
#include "r_external_irq_api.h"
#include "sf_external_irq.h"
#include "sf_i2c.h"
#include "sf_i2c_api.h"
#include "sf_touch_panel_chip_sx8654.h"
#include "sf_touch_panel_v2.h"
#include "sf_touch_panel_v2_api.h"
#include "r_dtc.h"
#include "r_transfer_api.h"
#include "r_sci_spi.h"
#include "r_spi_api.h"
#include "r_flash_hp.h"
#include "r_flash_api.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#ifdef __cplusplus
extern "C" {
#endif
/* Display on GLCD Instance. */
extern const display_instance_t g_display;
extern display_runtime_cfg_t g_display_runtime_cfg_fg;
extern display_runtime_cfg_t g_display_runtime_cfg_bg;
#if (false)
            extern display_clut_cfg_t g_display_clut_cfg_glcd;
            #endif
#ifndef NULL
void NULL(display_callback_args_t *p_args);
#endif
#if (false)
            #define DISPLAY_IN_FORMAT_16BITS_RGB565_0
            #if defined (DISPLAY_IN_FORMAT_32BITS_RGB888_0) || defined (DISPLAY_IN_FORMAT_32BITS_ARGB8888_0)
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (32)
            #elif defined (DISPLAY_IN_FORMAT_16BITS_RGB565_0) || defined (DISPLAY_IN_FORMAT_16BITS_ARGB1555_0) || defined (DISPLAY_IN_FORMAT_16BITS_ARGB4444_0)
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (16)
            #elif defined (DISPLAY_IN_FORMAT_CLUT8_0)
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (8)
            #elif defined (DISPLAY_IN_FORMAT_CLUT4_0)
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (4)
            #else
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (1)
            #endif
            extern uint8_t g_display_fb_background[2][((256 * 320) * DISPLAY_BITS_PER_PIXEL_INPUT0) >> 3];
            #endif
#if (true)
            #define DISPLAY_IN_FORMAT_32BITS_RGB888_1
            #if defined (DISPLAY_IN_FORMAT_32BITS_RGB888_1) || defined (DISPLAY_IN_FORMAT_32BITS_ARGB8888_1)
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (32)
            #elif defined (DISPLAY_IN_FORMAT_16BITS_RGB565_1) || defined (DISPLAY_IN_FORMAT_16BITS_ARGB1555_1) || defined (DISPLAY_IN_FORMAT_16BITS_ARGB4444_1)
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (16)
            #elif defined (DISPLAY_IN_FORMAT_CLUT8_1)
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (8)
            #elif defined (DISPLAY_IN_FORMAT_CLUT4_1)
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (4)
            #else
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (1)
            #endif
            extern uint8_t g_display_fb_foreground[1][((240 * 320) * DISPLAY_BITS_PER_PIXEL_INPUT1) >> 3];
            #endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irq0;
#ifndef NULL
void NULL(external_irq_callback_args_t *p_args);
#endif
/** SF External IRQ on SF External IRQ Instance. */
extern const sf_external_irq_instance_t g_sf_external_irq0;
/* SF I2C on SF I2C Instance. */
extern const sf_i2c_instance_t g_sf_i2c_device0;
extern const sf_touch_panel_chip_instance_t g_touch_panel_chip_sx8654;
extern const sf_touch_panel_chip_api_t g_sf_touch_panel_chip_sx8654;
/** SF Touch Panel V2 on SF Touch Panel V2 Instance. */
extern const sf_touch_panel_v2_instance_t g_sf_touch_panel_v2;
void g_sf_touch_panel_v2_err_callback(void *p_instance, void *p_data);
#ifndef touch_panel_v2_callback
void touch_panel_v2_callback(sf_touchpanel_v2_callback_args_t *p_args);
#endif			
void sf_touch_panel_v2_init(void);
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer1;
#ifndef NULL
void NULL(transfer_callback_args_t *p_args);
#endif
/* Transfer on DTC Instance. */
extern const transfer_instance_t g_transfer0;
#ifndef NULL
void NULL(transfer_callback_args_t *p_args);
#endif
extern const spi_cfg_t g_lcd_spi_cfg;
/** SPI on SCI Instance. */
extern const spi_instance_t g_lcd_spi;
extern sci_spi_instance_ctrl_t g_lcd_spi_ctrl;
extern const sci_spi_extended_cfg g_lcd_spi_cfg_extend;

#ifndef g_lcd_spi_callback
void g_lcd_spi_callback(spi_callback_args_t *p_args);
#endif

#define SYNERGY_NOT_DEFINED (1)            
#if (SYNERGY_NOT_DEFINED == g_transfer0)
    #define g_lcd_spi_P_TRANSFER_TX (NULL)
#else
#define g_lcd_spi_P_TRANSFER_TX (&g_transfer0)
#endif
#if (SYNERGY_NOT_DEFINED == g_transfer1)
    #define g_lcd_spi_P_TRANSFER_RX (NULL)
#else
#define g_lcd_spi_P_TRANSFER_RX (&g_transfer1)
#endif
#undef SYNERGY_NOT_DEFINED

#define g_lcd_spi_P_EXTEND (&g_lcd_spi_cfg_extend)
/* Flash on Flash HP Instance */
extern const flash_instance_t g_flash_miniwin;
#ifndef NULL
void NULL(flash_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_miniwin_timer;
#ifndef g_miniwin_timer_callback
void g_miniwin_timer_callback(timer_callback_args_t *p_args);
#endif
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* MINIWIN_THREAD_H_ */
