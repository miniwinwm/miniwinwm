/* generated thread source file - do not edit */
#include "miniwin_thread.h"

TX_THREAD miniwin_thread;
void miniwin_thread_create(void);
static void miniwin_thread_func(ULONG thread_input);
static uint8_t miniwin_thread_stack[2048] BSP_PLACE_IN_SECTION_V2(".stack.miniwin_thread") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_display) && !defined(SSP_SUPPRESS_ISR_GLCD)
SSP_VECTOR_DEFINE(glcdc_line_detect_isr, GLCDC, LINE_DETECT);
#endif
#endif
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_display) && !defined(SSP_SUPPRESS_ISR_GLCD)
SSP_VECTOR_DEFINE(glcdc_underflow_1_isr, GLCDC, UNDERFLOW_1);
#endif
#endif
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_display) && !defined(SSP_SUPPRESS_ISR_GLCD)
SSP_VECTOR_DEFINE(glcdc_underflow_2_isr, GLCDC, UNDERFLOW_2);
#endif
#endif

/** Display frame buffer */
#if (false)
        uint8_t g_display_fb_background[2][((256 * 320) * DISPLAY_BITS_PER_PIXEL_INPUT0) >> 3] BSP_ALIGN_VARIABLE_V2(64) BSP_PLACE_IN_SECTION_V2(".bss");
        #else
/** Graphics screen1 is specified not to be used when starting */
#endif
#if (true)
        uint8_t g_display_fb_foreground[1][((240 * 320) * DISPLAY_BITS_PER_PIXEL_INPUT1) >> 3] BSP_ALIGN_VARIABLE_V2(64) BSP_PLACE_IN_SECTION_V2(".bss");
        #else
/** Graphics screen2 is specified not to be used when starting */
#endif

#if (false)
        /** Display CLUT buffer to be used for updating CLUT */
        static uint32_t CLUT_buffer[256];

        /** Display CLUT configuration(only used if using CLUT format) */
        display_clut_cfg_t g_display_clut_cfg_glcd =
        {
            .p_base              = (uint32_t *)CLUT_buffer,
            .start               = 0,   /* User have to update this setting when using */
            .size                = 256  /* User have to update this setting when using */
        };
        #else
/** CLUT is specified not to be used */
#endif

#if (false | false | false)
        /** Display interface configuration */
        static const display_gamma_correction_t g_display_gamma_cfg =
        {
            .r =
            {
                .enable      = false,
                .gain        = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                .threshold   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
            },
            .g =
            {
                .enable      = false,
                .gain        = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                .threshold   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
            },
            .b =
            {
                .enable      = false,
                .gain        = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                .threshold   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
            }
        };
        #endif

/** Display device extended configuration */
static const glcd_cfg_t g_display_extend_cfg =
{ .tcon_hsync = GLCD_TCON_PIN_2,
  .tcon_vsync = GLCD_TCON_PIN_1,
  .tcon_de = GLCD_TCON_PIN_0,
  .correction_proc_order = GLCD_CORRECTION_PROC_ORDER_BRIGHTNESS_CONTRAST2GAMMA,
  .clksrc = GLCD_CLK_SRC_INTERNAL,
  .clock_div_ratio = GLCD_PANEL_CLK_DIVISOR_32,
  .dithering_mode = GLCD_DITHERING_MODE_TRUNCATE,
  .dithering_pattern_A = GLCD_DITHERING_PATTERN_11,
  .dithering_pattern_B = GLCD_DITHERING_PATTERN_11,
  .dithering_pattern_C = GLCD_DITHERING_PATTERN_11,
  .dithering_pattern_D = GLCD_DITHERING_PATTERN_11 };

/** Display control block instance */
glcd_instance_ctrl_t g_display_ctrl;

/** Display interface configuration */
const display_cfg_t g_display_cfg =
        {
        /** Input1(Graphics1 screen) configuration */
        .input[0
                  ] =
                  {
#if (false)
                .p_base              = (uint32_t *)&g_display_fb_background[0],
                #else
                    .p_base = NULL,
#endif
                    .hsize = 240,
                    .vsize = 320, .hstride = 256, .format = DISPLAY_IN_FORMAT_16BITS_RGB565, .line_descending_enable =
                            false,
                    .lines_repeat_enable = false, .lines_repeat_times = 0 },

          /** Input2(Graphics2 screen) configuration */
          .input[1
                  ] =
                  {
#if (true)
                .p_base              = (uint32_t *)&g_display_fb_foreground[0],
                #else
                    .p_base = NULL,
#endif
                    .hsize = 240,
                    .vsize = 320, .hstride = 240, .format = DISPLAY_IN_FORMAT_32BITS_RGB888, .line_descending_enable =
                            false,
                    .lines_repeat_enable = false, .lines_repeat_times = 0 },

          /** Input1(Graphics1 screen) layer configuration */
          .layer[0] =
          { .coordinate =
          { .x = 0, .y = 0 },
            .bg_color =
            { .byte =
            { .a = 255, .r = 255, .g = 255, .b = 255 } },
            .fade_control = DISPLAY_FADE_CONTROL_NONE, .fade_speed = 0 },

          /** Input2(Graphics2 screen) layer configuration */
          .layer[1] =
          { .coordinate =
          { .x = 0, .y = 0 },
            .bg_color =
            { .byte =
            { .a = 255, .r = 255, .g = 255, .b = 255 } },
            .fade_control = DISPLAY_FADE_CONTROL_NONE, .fade_speed = 0 },

          /** Output configuration */
          .output =
                  { .htiming =
                  { .total_cyc = 320, .display_cyc = 240, .back_porch = 6, .sync_width = 4, .sync_polarity =
                            DISPLAY_SIGNAL_POLARITY_LOACTIVE },
                    .vtiming =
                    { .total_cyc = 328, .display_cyc = 320, .back_porch = 4, .sync_width = 4, .sync_polarity =
                              DISPLAY_SIGNAL_POLARITY_LOACTIVE },
                    .format = DISPLAY_OUT_FORMAT_16BITS_RGB565, .endian = DISPLAY_ENDIAN_LITTLE, .color_order =
                            DISPLAY_COLOR_ORDER_RGB,
                    .data_enable_polarity = DISPLAY_SIGNAL_POLARITY_HIACTIVE, .sync_edge =
                            DISPLAY_SIGNAL_SYNC_EDGE_RISING,
                    .bg_color =
                    { .byte =
                    { .a = 255, .r = 0, .g = 0, .b = 0 } },
                    .brightness =
                    { .enable = false, .r = 512, .g = 512, .b = 512 },
                    .contrast =
                    { .enable = false, .r = 128, .g = 128, .b = 128 },
#if (false | false | false)
                .p_gamma_correction  = (display_gamma_correction_t *)(&g_display_gamma_cfg),
#else
                    .p_gamma_correction = NULL,
#endif
                    .dithering_on = false },

          /** Display device callback function pointer */
          .p_callback = NULL,
          .p_context = (void*) &g_display,

          /** Display device extended configuration */
          .p_extend = (void*) (&g_display_extend_cfg),

          .line_detect_ipl = (BSP_IRQ_DISABLED),
          .underflow_1_ipl = (BSP_IRQ_DISABLED), .underflow_2_ipl = (BSP_IRQ_DISABLED), };

#if (false)
        /** Display on GLCD run-time configuration(for the graphics1 screen) */
        display_runtime_cfg_t g_display_runtime_cfg_bg =
        {
            .input =
            {
                #if (false)
                .p_base              = (uint32_t *)&g_display_fb_background[0],
                #else
                .p_base              = NULL,
                #endif
                .hsize               = 240,
                .vsize               = 320,
                .hstride             = 256,
                .format              = DISPLAY_IN_FORMAT_16BITS_RGB565,
                .line_descending_enable = false,
                .lines_repeat_enable = false,
                .lines_repeat_times  = 0
            },
            .layer =
            {
                .coordinate = {
                        .x           = 0,
                        .y           = 0
                },
                .bg_color            =
                {
                    .byte            =
                    {
                        .a           = 255,
                        .r           = 255,
                        .g           = 255,
                        .b           = 255
                    }
                },
                .fade_control        = DISPLAY_FADE_CONTROL_NONE,
                .fade_speed          = 0
            }
        };
#endif
#if (true)
        /** Display on GLCD run-time configuration(for the graphics2 screen) */
        display_runtime_cfg_t g_display_runtime_cfg_fg =
        {
            .input =
            {
                #if (true)
                .p_base              = (uint32_t *)&g_display_fb_foreground[0],
                #else
                .p_base              = NULL,
                #endif
                .hsize               = 240,
                .vsize               = 320,
                .hstride             = 240,
                .format              = DISPLAY_IN_FORMAT_32BITS_RGB888,
                .line_descending_enable = false,
                .lines_repeat_enable = false,
                .lines_repeat_times  = 0
             },
            .layer =
            {
                .coordinate = {
                        .x           = 0,
                        .y           = 0
                },
                .bg_color            =
                {
                    .byte            =
                    {
                        .a           = 255,
                        .r           = 255,
                        .g           = 255,
                        .b           = 255
                    }
                },
                .fade_control        = DISPLAY_FADE_CONTROL_NONE,
                .fade_speed          = 0
            }
        };
#endif

/* Instance structure to use this module. */
const display_instance_t g_display =
{ .p_ctrl = &g_display_ctrl, .p_cfg = (display_cfg_t*) &g_display_cfg, .p_api = (display_api_t*) &g_display_on_glcd };
#if (3) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irq0) && !defined(SSP_SUPPRESS_ISR_ICU9)
SSP_VECTOR_DEFINE( icu_irq_isr, ICU, IRQ9);
#endif
#endif
static icu_instance_ctrl_t g_external_irq0_ctrl;
static const external_irq_cfg_t g_external_irq0_cfg =
{ .channel = 9,
  .trigger = EXTERNAL_IRQ_TRIG_FALLING,
  .filter_enable = true,
  .pclk_div = EXTERNAL_IRQ_PCLK_DIV_BY_64,
  .autostart = true,
  .p_callback = NULL,
  .p_context = &g_external_irq0,
  .p_extend = NULL,
  .irq_ipl = (3), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irq0 =
{ .p_ctrl = &g_external_irq0_ctrl, .p_cfg = &g_external_irq0_cfg, .p_api = &g_external_irq_on_icu };
sf_external_irq_instance_ctrl_t g_sf_external_irq0_ctrl;
const sf_external_irq_cfg_t g_sf_external_irq0_cfg =
{ .event = SF_EXTERNAL_IRQ_EVENT_SEMAPHORE_PUT, .p_lower_lvl_irq = &g_external_irq0, };
/* Instance structure to use this module. */
const sf_external_irq_instance_t g_sf_external_irq0 =
{ .p_ctrl = &g_sf_external_irq0_ctrl, .p_cfg = &g_sf_external_irq0_cfg, .p_api = &g_sf_external_irq_on_sf_external_irq };
/** Get driver cfg from bus and use all same settings except slave address and addressing mode. */
const i2c_cfg_t g_sf_i2c_device0_i2c_cfg =
{ .channel = g_sf_i2c_bus0_CHANNEL,
  .rate = g_sf_i2c_bus0_RATE,
  .slave = 0x48,
  .addr_mode = I2C_ADDR_MODE_7BIT,
  .sda_delay = g_sf_i2c_bus0_SDA_DELAY,
  .p_transfer_tx = g_sf_i2c_bus0_P_TRANSFER_TX,
  .p_transfer_rx = g_sf_i2c_bus0_P_TRANSFER_RX,
  .p_callback = g_sf_i2c_bus0_P_CALLBACK,
  .p_context = g_sf_i2c_bus0_P_CONTEXT,
  .rxi_ipl = g_sf_i2c_bus0_RXI_IPL,
  .txi_ipl = g_sf_i2c_bus0_TXI_IPL,
  .tei_ipl = g_sf_i2c_bus0_TEI_IPL,
  .eri_ipl = g_sf_i2c_bus0_ERI_IPL,
  .p_extend = g_sf_i2c_bus0_P_EXTEND, };

sf_i2c_instance_ctrl_t g_sf_i2c_device0_ctrl =
{ .p_lower_lvl_ctrl = &g_i2c_ctrl, };
const sf_i2c_cfg_t g_sf_i2c_device0_cfg =
{ .p_bus = (sf_i2c_bus_t*) &g_sf_i2c_bus0, .p_lower_lvl_cfg = &g_sf_i2c_device0_i2c_cfg, };
/* Instance structure to use this module. */
const sf_i2c_instance_t g_sf_i2c_device0 =
{ .p_ctrl = &g_sf_i2c_device0_ctrl, .p_cfg = &g_sf_i2c_device0_cfg, .p_api = &g_sf_i2c_on_sf_i2c };
sf_touch_panel_chip_sx8654_instance_ctrl_t g_touch_panel_chip_sx8654_ctrl;
const sf_touch_panel_chip_on_sx8654_cfg_t g_touch_panel_chip_sx8654_cfg_extend =
{ .pin = IOPORT_PORT_06_PIN_09,
  .p_lower_lvl_framewrk = &g_sf_i2c_device0,
  .p_lower_lvl_irq = &g_sf_external_irq0,
  .hsize_pixels = 240,
  .vsize_pixels = 320 };
const sf_touch_panel_chip_cfg_t g_touch_panel_chip_sx8654_cfg =
{ .p_extend = &g_touch_panel_chip_sx8654_cfg_extend };
const sf_touch_panel_chip_instance_t g_touch_panel_chip_sx8654 =
{ .p_ctrl = &g_touch_panel_chip_sx8654_ctrl, .p_cfg = &g_touch_panel_chip_sx8654_cfg, .p_api =
          &g_sf_touch_panel_chip_sx8654 };
#if defined(__ICCARM__)
            #define g_sf_touch_panel_v2_err_callback_WEAK_ATTRIBUTE
            #pragma weak g_sf_touch_panel_v2_err_callback  = g_sf_touch_panel_v2_err_callback_internal
            #elif defined(__GNUC__)
            #define g_sf_touch_panel_v2_err_callback_WEAK_ATTRIBUTE   __attribute__ ((weak, alias("g_sf_touch_panel_v2_err_callback_internal")))
            #endif
void g_sf_touch_panel_v2_err_callback(void *p_instance, void *p_data)
g_sf_touch_panel_v2_err_callback_WEAK_ATTRIBUTE;
sf_touch_panel_v2_instance_ctrl_t g_sf_touch_panel_v2_ctrl;
const sf_touch_panel_v2_extend_cfg_t g_sf_touch_panel_v2_cfg_extend =
{ .p_chip = &g_touch_panel_chip_sx8654 };
const sf_touch_panel_v2_cfg_t g_sf_touch_panel_v2_cfg =
{ .hsize_pixels = 240,
  .vsize_pixels = 320,
  .priority = 3,
  .update_hz = 10,
  .p_extend = &g_sf_touch_panel_v2_cfg_extend,
  .rotation_angle = 0,
  .p_callback = touch_panel_v2_callback,
  .p_context = &g_sf_touch_panel_v2 };

/* Instance structure to use this module. */
const sf_touch_panel_v2_instance_t g_sf_touch_panel_v2 =
{ .p_ctrl = &g_sf_touch_panel_v2_ctrl, .p_cfg = &g_sf_touch_panel_v2_cfg, .p_api =
          &g_sf_touch_panel_v2_on_sf_touch_panel_v2 };
/*******************************************************************************************************************//**
 * @brief      Initialization function that the user can choose to have called automatically during thread entry.
 *             The user can call this function at a later time if desired using the prototype below.

 *             - void g_sf_touch_panel_v2_err_callback(void * p_instance, void * p_data)
 *
 * @param[in]  p_instance arguments used to identify which instance caused the error and p_data Callback arguments
 used to identify what error caused the callback.
 **********************************************************************************************************************/
void g_sf_touch_panel_v2_err_callback_internal(void *p_instance, void *p_data);
void g_sf_touch_panel_v2_err_callback_internal(void *p_instance, void *p_data)
{
    /** Suppress compiler warning for not using parameters. */
    SSP_PARAMETER_NOT_USED (p_instance);
    SSP_PARAMETER_NOT_USED (p_data);
    /** An error has occurred. Please check function arguments for more information. */
    BSP_CFG_HANDLE_UNRECOVERABLE_ERROR (0);
}
/*******************************************************************************************************************//**
 * @brief     This is sf touch panel initialization function. User Can call this function in the application 
 if required with the below mentioned prototype.
 *            - void sf_touch_panel_v2_init(void)
 **********************************************************************************************************************/
void sf_touch_panel_v2_init(void)
{
    ssp_err_t ssp_err_g_sf_touch_panel_v2;
    ssp_err_g_sf_touch_panel_v2 = g_sf_touch_panel_v2.p_api->open (g_sf_touch_panel_v2.p_ctrl,
                                                                   g_sf_touch_panel_v2.p_cfg);
    if (SSP_SUCCESS != ssp_err_g_sf_touch_panel_v2)
    {
        g_sf_touch_panel_v2_err_callback ((void*) &g_sf_touch_panel_v2, &ssp_err_g_sf_touch_panel_v2);
    }
    if (1)
    {
        ssp_err_g_sf_touch_panel_v2 = g_sf_touch_panel_v2.p_api->start (g_sf_touch_panel_v2.p_ctrl);
        if (SSP_SUCCESS != ssp_err_g_sf_touch_panel_v2)
        {
            g_sf_touch_panel_v2_err_callback ((void*) &g_sf_touch_panel_v2, &ssp_err_g_sf_touch_panel_v2);
        }
    }
}
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_transfer1) && !defined(SSP_SUPPRESS_ISR_DTCELC_EVENT_SCI0_RXI)
#define DTC_ACTIVATION_SRC_ELC_EVENT_SCI0_RXI
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

dtc_instance_ctrl_t g_transfer1_ctrl;
transfer_info_t g_transfer1_info =
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
const transfer_cfg_t g_transfer1_cfg =
{ .p_info = &g_transfer1_info,
  .activation_source = ELC_EVENT_SCI0_RXI,
  .auto_enable = false,
  .p_callback = NULL,
  .p_context = &g_transfer1,
  .irq_ipl = (BSP_IRQ_DISABLED) };
/* Instance structure to use this module. */
const transfer_instance_t g_transfer1 =
{ .p_ctrl = &g_transfer1_ctrl, .p_cfg = &g_transfer1_cfg, .p_api = &g_transfer_on_dtc };
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_transfer0) && !defined(SSP_SUPPRESS_ISR_DTCELC_EVENT_SCI0_TXI)
#define DTC_ACTIVATION_SRC_ELC_EVENT_SCI0_TXI
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

dtc_instance_ctrl_t g_transfer0_ctrl;
transfer_info_t g_transfer0_info =
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
const transfer_cfg_t g_transfer0_cfg =
{ .p_info = &g_transfer0_info,
  .activation_source = ELC_EVENT_SCI0_TXI,
  .auto_enable = false,
  .p_callback = NULL,
  .p_context = &g_transfer0,
  .irq_ipl = (BSP_IRQ_DISABLED) };
/* Instance structure to use this module. */
const transfer_instance_t g_transfer0 =
{ .p_ctrl = &g_transfer0_ctrl, .p_cfg = &g_transfer0_cfg, .p_api = &g_transfer_on_dtc };
#if !defined(SSP_SUPPRESS_ISR_g_lcd_spi) && !defined(SSP_SUPPRESS_ISR_SCI0)
SSP_VECTOR_DEFINE_CHAN(sci_spi_rxi_isr, SCI, RXI, 0);
#endif
#if !defined(SSP_SUPPRESS_ISR_g_lcd_spi) && !defined(SSP_SUPPRESS_ISR_SCI0)
SSP_VECTOR_DEFINE_CHAN(sci_spi_txi_isr, SCI, TXI, 0);
#endif
#if !defined(SSP_SUPPRESS_ISR_g_lcd_spi) && !defined(SSP_SUPPRESS_ISR_SCI0)
SSP_VECTOR_DEFINE_CHAN(sci_spi_tei_isr, SCI, TEI, 0);
#endif
#if !defined(SSP_SUPPRESS_ISR_g_lcd_spi) && !defined(SSP_SUPPRESS_ISR_SCI0)
SSP_VECTOR_DEFINE_CHAN(sci_spi_eri_isr, SCI, ERI, 0);
#endif
sci_spi_instance_ctrl_t g_lcd_spi_ctrl;

/** SPI extended configuration */
const sci_spi_extended_cfg g_lcd_spi_cfg_extend =
{ .bitrate_modulation = true };

const spi_cfg_t g_lcd_spi_cfg =
{ .channel = 0, .operating_mode = SPI_MODE_MASTER, .clk_phase = SPI_CLK_PHASE_EDGE_EVEN, .clk_polarity =
          SPI_CLK_POLARITY_HIGH,
  .mode_fault = SPI_MODE_FAULT_ERROR_DISABLE, .bit_order = SPI_BIT_ORDER_MSB_FIRST, .bitrate = 100000,
#define SYNERGY_NOT_DEFINED (1)             
#if (SYNERGY_NOT_DEFINED == g_transfer0)
                .p_transfer_tx       = NULL,
#else
  .p_transfer_tx = &g_transfer0,
#endif
#if (SYNERGY_NOT_DEFINED == g_transfer1)
                .p_transfer_rx       = NULL,
#else
  .p_transfer_rx = &g_transfer1,
#endif
#undef SYNERGY_NOT_DEFINED	
  .p_callback = g_lcd_spi_callback,
  .p_context = (void*) &g_lcd_spi, .rxi_ipl = (3), .txi_ipl = (3), .tei_ipl = (3), .eri_ipl = (3), .p_extend =
          &g_lcd_spi_cfg_extend, };
/* Instance structure to use this module. */
const spi_instance_t g_lcd_spi =
{ .p_ctrl = &g_lcd_spi_ctrl, .p_cfg = &g_lcd_spi_cfg, .p_api = &g_spi_on_sci };
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_flash_miniwin) && !defined(SSP_SUPPRESS_ISR_FLASH)
SSP_VECTOR_DEFINE(fcu_frdyi_isr, FCU, FRDYI);
#endif
#endif
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_flash_miniwin) && !defined(SSP_SUPPRESS_ISR_FLASH)
SSP_VECTOR_DEFINE(fcu_fiferr_isr, FCU, FIFERR);
#endif
#endif
flash_hp_instance_ctrl_t g_flash_miniwin_ctrl;
const flash_cfg_t g_flash_miniwin_cfg =
{ .data_flash_bgo = false,
  .p_callback = NULL,
  .p_context = &g_flash_miniwin,
  .irq_ipl = (BSP_IRQ_DISABLED),
  .err_irq_ipl = (BSP_IRQ_DISABLED), };
/* Instance structure to use this module. */
const flash_instance_t g_flash_miniwin =
{ .p_ctrl = &g_flash_miniwin_ctrl, .p_cfg = &g_flash_miniwin_cfg, .p_api = &g_flash_on_flash_hp };
#if (3) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_miniwin_timer) && !defined(SSP_SUPPRESS_ISR_GPT0)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 0);
#endif
#endif
static gpt_instance_ctrl_t g_miniwin_timer_ctrl;
static const timer_on_gpt_cfg_t g_miniwin_timer_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_miniwin_timer_cfg =
{ .mode = TIMER_MODE_PERIODIC, .period = 50, .unit = TIMER_UNIT_PERIOD_MSEC, .duty_cycle = 50, .duty_cycle_unit =
          TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 0, .autostart = true, .p_callback = g_miniwin_timer_callback, .p_context = &g_miniwin_timer, .p_extend =
          &g_miniwin_timer_extend,
  .irq_ipl = (3), };
/* Instance structure to use this module. */
const timer_instance_t g_miniwin_timer =
{ .p_ctrl = &g_miniwin_timer_ctrl, .p_cfg = &g_miniwin_timer_cfg, .p_api = &g_timer_on_gpt };
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void miniwin_thread_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */

    UINT err;
    err = tx_thread_create (&miniwin_thread, (CHAR*) "MiniWin Thread", miniwin_thread_func, (ULONG) NULL,
                            &miniwin_thread_stack, 2048, 3, 3, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&miniwin_thread, 0);
    }
}

static void miniwin_thread_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */
    /** Call initialization function if user has selected to do so. */
#if (1)
    sf_touch_panel_v2_init ();
#endif

    /* Enter user code for this thread. */
    miniwin_thread_entry ();
}
