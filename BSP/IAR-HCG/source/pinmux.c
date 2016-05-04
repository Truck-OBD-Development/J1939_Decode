/** @file pinmux.c 
*   @brief PINMUX Driver Implementation File
*   @date 03.Apr.2015
*   @version 04.04.00
*
*/

/* 
* Copyright (C) 2009-2015 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* Include Files */

#include "reg_system.h"
#include "pinmux.h"

/*LDRA_INSPECTWINDOW 50 */
/*SAFETYMCUSW 125 S MR: 19.13 REVIEWED " Needs usage of ## in the macro " */
/*SAFETYMCUSW 76 S MR: 19.12 REVIEWED " Needs usage of multiple ## in the macro " */
/*SAFETYMCUSW 78 S MR: 19.10 REVIEWED " Macro parameter used for concatenation " */
/*SAFETYMCUSW 78 S MR: 19.10 REVIEWED " Macro parameter used for concatenation " */
/*SAFETYMCUSW 78 S MR: 19.10 REVIEWED " Macro parameter used for concatenation " */
/*SAFETYMCUSW 78 S MR: 19.10 REVIEWED " Macro parameter used for concatenation " */
/*SAFETYMCUSW 78 S MR: 19.10 REVIEWED " Macro parameter used for concatenation " */
/*SAFETYMCUSW 76 S MR: 19.12 REVIEWED " Needs usage of multiple ## in the macro " */
/*SAFETYMCUSW 76 S MR: 19.12 REVIEWED " Needs usage of multiple ## in the macro " */
/*SAFETYMCUSW 76 S MR: 19.12 REVIEWED " Needs usage of multiple ## in the macro " */
/*SAFETYMCUSW 76 S MR: 19.12 REVIEWED " Needs usage of multiple ## in the macro " */
/*SAFETYMCUSW 76 S MR: 19.12 REVIEWED " Needs usage of multiple ## in the macro " */
/*SAFETYMCUSW 76 S MR: 19.12 REVIEWED " Needs usage of multiple ## in the macro " */
/*SAFETYMCUSW 76 S MR: 19.12 REVIEWED " Needs usage of multiple ## in the macro " */
#define PINMUX_SET(REG, BALLID, MUX)                                \
            (pinMuxReg->PINMMR##REG = (pinMuxReg->PINMMR##REG & PINMUX_BALL_##BALLID##_MASK) | (PINMUX_BALL_##BALLID##_##MUX))

/*SAFETYMCUSW 125 S MR: 19.13 REVIEWED " Needs usage of ## in the macro " */
/*SAFETYMCUSW 78 S MR: 19.10 REVIEWED " Macro parameter used for concatenation " */
#define PINMUX_GATE_EMIF_CLK_ENABLE(state)      \
            (pinMuxReg->PINMMR29 = (pinMuxReg->PINMMR29 & PINMUX_GATE_EMIF_CLK_MASK) | (PINMUX_GATE_EMIF_CLK_##state))

/*SAFETYMCUSW 125 S MR: 19.13 REVIEWED " Needs usage of ## in the macro " */
/*SAFETYMCUSW 78 S MR: 19.10 REVIEWED " Macro parameter used for concatenation " */
#define PINMUX_GIOB_DISABLE_HET2_ENABLE(state)  \
            (pinMuxReg->PINMMR29 = (pinMuxReg->PINMMR29 & PINMUX_GIOB_DISABLE_HET2_MASK) | (PINMUX_GIOB_DISABLE_HET2_##state))
            
/*SAFETYMCUSW 125 S MR: 19.13 REVIEWED " Needs usage of ## in the macro " */
/*SAFETYMCUSW 78 S MR: 19.10 REVIEWED " Macro parameter used for concatenation " */ 
#define PINMUX_ALT_ADC_TRIGGER_SELECT(num)  \
            (pinMuxReg->PINMMR30 = (pinMuxReg->PINMMR30 & PINMUX_ALT_ADC_TRIGGER_MASK) | (PINMUX_ALT_ADC_TRIGGER_##num))
            
/*SAFETYMCUSW 125 S MR: 19.13 REVIEWED " Needs usage of ## in the macro " */
/*SAFETYMCUSW 78 S MR: 19.10 REVIEWED " Macro parameter used for concatenation " */ 
#define PINMUX_ETHERNET_SELECT(interface)   \
            (pinMuxReg->PINMMR29 = (pinMuxReg->PINMMR29 & PINMUX_ETHERNET_MASK) | (PINMUX_ETHERNET_##interface))

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* SourceId : PINMUX_SourceId_001 */
/* DesignId : PINMUX_DesignId_001 */
/* Requirements : HL_SR325 */
void muxInit(void){

/* USER CODE BEGIN (1) */
/* USER CODE END */

    /* Enable Pin Muxing */
    kickerReg->KICKER0 = 0x83E70B13U;
    kickerReg->KICKER1 = 0x95A4F1E0U;
    
/* USER CODE BEGIN (2) */
/* USER CODE END */

    pinMuxReg->PINMMR0 =    PINMUX_BALL_W10_GIOB_3 | PINMUX_BALL_A5_GIOA_0 | PINMUX_BALL_C3_MIBSPI3NCS_3 | PINMUX_BALL_B2_MIBSPI3NCS_2;
    
    pinMuxReg->PINMMR1 =    PINMUX_BALL_C2_GIOA_1 | PINMUX_BALL_E3_HET1_11 | PINMUX_BALL_E5_ETMDATA_20 | PINMUX_BALL_F5_ETMDATA_21;
    
    pinMuxReg->PINMMR2 =    PINMUX_BALL_C1_GIOA_2 | PINMUX_BALL_G5_ETMDATA_22 | PINMUX_BALL_E1_GIOA_3 | PINMUX_BALL_B5_GIOA_5;
    
    pinMuxReg->PINMMR3 =    PINMUX_BALL_K5_ETMDATA_23 | PINMUX_BALL_B3_HET1_22 | PINMUX_BALL_H3_GIOA_6 | PINMUX_BALL_L5_ETMDATA_24;
    
    pinMuxReg->PINMMR4 =    PINMUX_BALL_M1_GIOA_7 | PINMUX_BALL_M5_ETMDATA_25 | PINMUX_BALL_V2_HET1_01 | PINMUX_BALL_U1_HET1_03;
    
    pinMuxReg->PINMMR5 =    PINMUX_BALL_K18_HET1_0 | PINMUX_BALL_W5_HET1_02 | PINMUX_BALL_V6_HET1_05 | PINMUX_BALL_N5_ETMDATA_26;
    
    pinMuxReg->PINMMR6 =    PINMUX_BALL_T1_HET1_07 | PINMUX_BALL_P5_ETMDATA_27 | PINMUX_BALL_V7_HET1_09 | PINMUX_BALL_R5_ETMDATA_28;
    
    pinMuxReg->PINMMR7 =    PINMUX_BALL_R6_ETMDATA_29 | PINMUX_BALL_V5_MIBSPI3NCS_1 | PINMUX_BALL_W3_HET1_06 | PINMUX_BALL_R7_ETMDATA_30;
    
    pinMuxReg->PINMMR8 =    PINMUX_BALL_N2_HET1_13 | PINMUX_BALL_G3_MIBSPI1NCS_2 | PINMUX_BALL_N1_HET1_15 | PINMUX_BALL_R8_ETMDATA_31;
    
    pinMuxReg->PINMMR9 = ((~(pinMuxReg->PINMMR9 >> 18U) & 0x00000001U ) << 18U) | PINMUX_BALL_R9_ETMTRACECLKIN | PINMUX_BALL_W9_MIBSPI3NENA | PINMUX_BALL_V10_MIBSPI3NCS_0 | PINMUX_BALL_J3_MIBSPI1NCS_3;
    
    pinMuxReg->PINMMR10 =   PINMUX_BALL_N19_AD1EVT | PINMUX_BALL_N15_ETMDATA_19 | PINMUX_BALL_N17_EMIF_nCS_0 | PINMUX_BALL_M15_ETMDATA_18;
    
    pinMuxReg->PINMMR11 =   PINMUX_BALL_K17_EMIF_nCS_3 | PINMUX_BALL_M17_EMIF_nCS_4 | PINMUX_BALL_L15_ETMDATA_17 | PINMUX_BALL_P1_HET1_24;
    
    pinMuxReg->PINMMR12 =   PINMUX_BALL_A14_HET1_26 | PINMUX_BALL_K15_ETMDATA_16 | PINMUX_BALL_G19_MIBSPI1NENA | PINMUX_BALL_H18_MIBSPI5NENA;
    
    pinMuxReg->PINMMR13 =   PINMUX_BALL_J18_MIBSPI5SOMI_0 | PINMUX_BALL_J19_MIBSPI5SIMO_0 | PINMUX_BALL_H19_MIBSPI5CLK | PINMUX_BALL_R2_MIBSPI1NCS_0;
    
    pinMuxReg->PINMMR14 =   PINMUX_BALL_E18_HET1_08 | PINMUX_BALL_K19_HET1_28 | PINMUX_BALL_D17_EMIF_nWE | PINMUX_BALL_D16_EMIF_BA_1;
    
    pinMuxReg->PINMMR15 =   PINMUX_BALL_C17_EMIF_ADDR_21 | PINMUX_BALL_C16_EMIF_ADDR_20 | PINMUX_BALL_C15_EMIF_ADDR_19 | PINMUX_BALL_D15_EMIF_ADDR_18;
    
    pinMuxReg->PINMMR16 =   PINMUX_BALL_E13_ETMDATA_12 | PINMUX_BALL_C14_EMIF_ADDR_17 | PINMUX_BALL_D14_EMIF_ADDR_16 | PINMUX_BALL_E12_ETMDATA_13;
    
    pinMuxReg->PINMMR17 =   PINMUX_BALL_D19_HET1_10 | PINMUX_BALL_E11_ETMDATA_14 | PINMUX_BALL_B4_HET1_12 | PINMUX_BALL_E9_ETMDATA_08;
    
    pinMuxReg->PINMMR18 =   PINMUX_BALL_C13_EMIF_ADDR_15 | PINMUX_BALL_A11_HET1_14 | PINMUX_BALL_C12_EMIF_ADDR_14 | PINMUX_BALL_M2_GIOB_0;
    
    pinMuxReg->PINMMR19 =   PINMUX_BALL_E8_ETMDATA_09 | PINMUX_BALL_B11_HET1_30 | PINMUX_BALL_E10_ETMDATA_15 | PINMUX_BALL_E7_ETMDATA_10;
    
    pinMuxReg->PINMMR20 =   PINMUX_BALL_C11_EMIF_ADDR_13 | PINMUX_BALL_C10_EMIF_ADDR_12 | PINMUX_BALL_F3_MIBSPI1NCS_1 | PINMUX_BALL_C9_EMIF_ADDR_11;
    
    pinMuxReg->PINMMR21 =   PINMUX_BALL_D5_EMIF_ADDR_1 | PINMUX_BALL_K2_GIOB_1 | PINMUX_BALL_C8_EMIF_ADDR_10 | PINMUX_BALL_C7_EMIF_ADDR_9;
    
    pinMuxReg->PINMMR22 =   PINMUX_BALL_D4_EMIF_ADDR_0 | PINMUX_BALL_C5_EMIF_ADDR_7 | PINMUX_BALL_C4_EMIF_ADDR_6 | PINMUX_BALL_E6_ETMDATA_11;
    
    pinMuxReg->PINMMR23 = ((~(pinMuxReg->PINMMR5 >> 1U) & 0x00000001U ) << 8U) | ((~(pinMuxReg->PINMMR5 >> 9U) & 0x00000001U ) << 16U) | ((~(pinMuxReg->PINMMR5 >> 17U) & 0x00000001U ) << 24U) | PINMUX_BALL_C6_EMIF_ADDR_8;
    
    pinMuxReg->PINMMR24 = ((~(pinMuxReg->PINMMR4 >> 17U) & 0x00000001U ) << 0U) | ((~(pinMuxReg->PINMMR4 >> 25U) & 0x00000001U ) << 8U) | ((~(pinMuxReg->PINMMR20 >> 17U) & 0x00000001U ) << 16U) | ((~(pinMuxReg->PINMMR8 >> 9U) & 0x00000001U ) << 24U);
    
    /*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "LDRA Tool issue" */
    pinMuxReg->PINMMR25 = ((~(pinMuxReg->PINMMR12 >> 17U) & 0x00000001U ) << 8U) | ((~(pinMuxReg->PINMMR7 >> 9U) & 0x00000001U ) << 16U) | ((~(pinMuxReg->PINMMR0 >> 26U) & 0x00000001U ) << 24U);
    
    /*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "LDRA Tool issue" */
    pinMuxReg->PINMMR26 = ((~(pinMuxReg->PINMMR0 >> 18U) & 0x00000001U ) << 0U) | ((~(pinMuxReg->PINMMR9 >> 10U) & 0x00000001U ) << 8U) | PINMUX_BALL_W6_MIBSPI5NCS_2 | PINMUX_BALL_T12_MIBSPI5NCS_3;
    
    pinMuxReg->PINMMR27 = PINMUX_BALL_E19_MIBSPI5NCS_0 | PINMUX_BALL_B6_MIBSPI5NCS_1 | PINMUX_BALL_E16_MIBSPI5SIMO_1 | PINMUX_BALL_H17_MIBSPI5SIMO_2;
    
    pinMuxReg->PINMMR28 = PINMUX_BALL_G17_MIBSPI5SIMO_3 | PINMUX_BALL_E17_MIBSPI5SOMI_1 | PINMUX_BALL_H16_MIBSPI5SOMI_2 | PINMUX_BALL_G16_MIBSPI5SOMI_3;
    
    pinMuxReg->PINMMR29 = PINMUX_BALL_D3_SPI2NENA;
    
    PINMUX_GATE_EMIF_CLK_ENABLE(OFF);
    PINMUX_GIOB_DISABLE_HET2_ENABLE(OFF);
    PINMUX_ALT_ADC_TRIGGER_SELECT(1);
    PINMUX_ETHERNET_SELECT(RMII);
    
    
/* USER CODE BEGIN (3) */
/* USER CODE END */
    
    /* Disable Pin Muxing */
    kickerReg->KICKER0 = 0x00000000U;
    kickerReg->KICKER1 = 0x00000000U;
    
/* USER CODE BEGIN (4) */
/* USER CODE END */
}

/** @fn void pinmuxGetConfigValue(pinmux_config_reg_t *config_reg, config_value_type_t type)
*   @brief Get the initial or current values of the configuration registers
*
*   @param[in] *config_reg: pointer to the struct to which the initial or current 
*                           value of the configuration registers need to be stored
*   @param[in] type:    whether initial or current value of the configuration registers need to be stored
*                       - InitialValue: initial value of the configuration registers will be stored 
*                                       in the struct pointed by config_reg
*                       - CurrentValue: initial value of the configuration registers will be stored 
*                                       in the struct pointed by config_reg
*
*   This function will copy the initial or current value (depending on the parameter 'type') 
*   of the configuration registers to the struct pointed by config_reg
*
*/
/* SourceId : PINMUX_SourceId_002 */
/* DesignId : PINMUX_DesignId_002 */
/* Requirements : HL_SR328 */
void pinmuxGetConfigValue(pinmux_config_reg_t *config_reg, config_value_type_t type)
{
    if (type == InitialValue)
    {/* Do not pass Initial Value as parameter */
    }
    else
    {
    /*SAFETYMCUSW 134 S MR:12.2 <APPROVED> "LDRA Tool issue" */
        config_reg->CONFIG_PINMMR0  = pinMuxReg->PINMMR0;
        config_reg->CONFIG_PINMMR1  = pinMuxReg->PINMMR1;
        config_reg->CONFIG_PINMMR2  = pinMuxReg->PINMMR2;
        config_reg->CONFIG_PINMMR3  = pinMuxReg->PINMMR3;
        config_reg->CONFIG_PINMMR4  = pinMuxReg->PINMMR4;
        config_reg->CONFIG_PINMMR5  = pinMuxReg->PINMMR5;
        config_reg->CONFIG_PINMMR6  = pinMuxReg->PINMMR6;
        config_reg->CONFIG_PINMMR7  = pinMuxReg->PINMMR7;
        config_reg->CONFIG_PINMMR8  = pinMuxReg->PINMMR8;
        config_reg->CONFIG_PINMMR9  = pinMuxReg->PINMMR9;
        config_reg->CONFIG_PINMMR10 = pinMuxReg->PINMMR10;
        config_reg->CONFIG_PINMMR11 = pinMuxReg->PINMMR11;
        config_reg->CONFIG_PINMMR12 = pinMuxReg->PINMMR12;
        config_reg->CONFIG_PINMMR13 = pinMuxReg->PINMMR13;
        config_reg->CONFIG_PINMMR14 = pinMuxReg->PINMMR14;
        config_reg->CONFIG_PINMMR15 = pinMuxReg->PINMMR15;
        config_reg->CONFIG_PINMMR16 = pinMuxReg->PINMMR16;
        config_reg->CONFIG_PINMMR17 = pinMuxReg->PINMMR17;
        config_reg->CONFIG_PINMMR18 = pinMuxReg->PINMMR18;
        config_reg->CONFIG_PINMMR19 = pinMuxReg->PINMMR19;
        config_reg->CONFIG_PINMMR20 = pinMuxReg->PINMMR20;
        config_reg->CONFIG_PINMMR21 = pinMuxReg->PINMMR21;
        config_reg->CONFIG_PINMMR22 = pinMuxReg->PINMMR22;
        config_reg->CONFIG_PINMMR23 = pinMuxReg->PINMMR23;
        config_reg->CONFIG_PINMMR24 = pinMuxReg->PINMMR24;
        config_reg->CONFIG_PINMMR25 = pinMuxReg->PINMMR25;
        config_reg->CONFIG_PINMMR26 = pinMuxReg->PINMMR26;
        config_reg->CONFIG_PINMMR27 = pinMuxReg->PINMMR27;
        config_reg->CONFIG_PINMMR28 = pinMuxReg->PINMMR28;
        config_reg->CONFIG_PINMMR29 = pinMuxReg->PINMMR29;
        config_reg->CONFIG_PINMMR30 = pinMuxReg->PINMMR30;
    }
}

/* USER CODE BEGIN (5) */
/* USER CODE END */
