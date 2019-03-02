<#--
  Copyright(C) 2015 Renesas Electronics Corporation
  RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY
  This program must be used solely for the purpose for which it was furnished 
  by Renesas Electronics Corporation. No part of this program may be reproduced
  or disclosed to others, in any form, without the prior written permission of 
  Renesas Electronics Corporation.
-->
<#-- = DECLARE FUNCTION INFORMATION HERE =================== -->
<#assign Function_Base_Name = "R_RTC_PinSet">
<#assign Function_Description = "This function initializes pins for r_rtc_rx module">
<#assign Function_Arg = "none">
<#assign Function_Ret = "none">
<#assign Version = 1.00>

<#-- = DECLARE FUNCTION CONTENT HERE ======================= -->
<#macro initialsection postfix>
<#assign Function_Name = "${Function_Base_Name}${postfix}">
<#include "lib/functionheader.ftl">
void ${Function_Name}()
{
</#macro> 
<#macro peripheralpincode pin>
    /*Set ${pin.pinName} pin */
<#if pin.pinName == "RTCOUT">
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC);
    MPC.${pin.assignedPinName}PFS.BYTE = 0x${pin.pinMPC}U;
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC);
    PORT${pin.portNum}.PMR.BIT.B${pin.pinBitNum} = 1U;
<#else>
    PORT${pin.portNum}.PDR.BIT.B${pin.pinBitNum} = 0U;
    PORT${pin.portNum}.PMR.BIT.B${pin.pinBitNum} = 0U;
</#if>

</#macro>
<#macro channelpincode pin>
</#macro> 
<#macro endsection>
}
</#macro> 

<#macro headerfilesection postfix>
<#assign Function_Name = "${Function_Base_Name}${postfix}">
void ${Function_Base_Name}${postfix}();
</#macro> 

<#-- = END OF FILE ========================================= -->