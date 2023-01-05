/* generated common source file - do not edit */
#include "common_data.h"
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
}
