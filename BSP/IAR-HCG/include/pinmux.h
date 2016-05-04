/** @file pinmux.h
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


#ifndef __PINMUX_H__
#define __PINMUX_H__

#include "reg_pinmux.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PINMUX_BALL_A5_SHIFT                     8U
#define PINMUX_BALL_A11_SHIFT                    8U
#define PINMUX_BALL_A14_SHIFT                    0U
#define PINMUX_BALL_B2_SHIFT                     24U
#define PINMUX_BALL_B3_SHIFT                     8U
#define PINMUX_BALL_B4_SHIFT                     16U
#define PINMUX_BALL_B5_SHIFT                     24U
#define PINMUX_BALL_B6_SHIFT                     8U
#define PINMUX_BALL_B11_SHIFT                    8U
#define PINMUX_BALL_C1_SHIFT                     0U
#define PINMUX_BALL_C2_SHIFT                     0U
#define PINMUX_BALL_C3_SHIFT                     16U
#define PINMUX_BALL_C4_SHIFT                     16U
#define PINMUX_BALL_C5_SHIFT                     8U
#define PINMUX_BALL_C6_SHIFT                     0U
#define PINMUX_BALL_C7_SHIFT                     24U
#define PINMUX_BALL_C8_SHIFT                     16U
#define PINMUX_BALL_C9_SHIFT                     24U
#define PINMUX_BALL_C10_SHIFT                    8U
#define PINMUX_BALL_C11_SHIFT                    0U
#define PINMUX_BALL_C12_SHIFT                    16U
#define PINMUX_BALL_C13_SHIFT                    0U
#define PINMUX_BALL_C14_SHIFT                    8U
#define PINMUX_BALL_C15_SHIFT                    16U
#define PINMUX_BALL_C16_SHIFT                    8U
#define PINMUX_BALL_C17_SHIFT                    0U
#define PINMUX_BALL_D3_SHIFT                     0U
#define PINMUX_BALL_D4_SHIFT                     0U
#define PINMUX_BALL_D5_SHIFT                     0U
#define PINMUX_BALL_D14_SHIFT                    16U
#define PINMUX_BALL_D15_SHIFT                    24U
#define PINMUX_BALL_D16_SHIFT                    24U
#define PINMUX_BALL_D17_SHIFT                    16U
#define PINMUX_BALL_D19_SHIFT                    0U
#define PINMUX_BALL_E1_SHIFT                     16U
#define PINMUX_BALL_E3_SHIFT                     8U
#define PINMUX_BALL_E5_SHIFT                     16U
#define PINMUX_BALL_E6_SHIFT                     24U
#define PINMUX_BALL_E7_SHIFT                     24U
#define PINMUX_BALL_E8_SHIFT                     0U
#define PINMUX_BALL_E9_SHIFT                     24U
#define PINMUX_BALL_E10_SHIFT                    16U
#define PINMUX_BALL_E11_SHIFT                    8U
#define PINMUX_BALL_E12_SHIFT                    24U
#define PINMUX_BALL_E13_SHIFT                    0U
#define PINMUX_BALL_E16_SHIFT                    16U
#define PINMUX_BALL_E17_SHIFT                    8U
#define PINMUX_BALL_E18_SHIFT                    0U
#define PINMUX_BALL_E19_SHIFT                    0U
#define PINMUX_BALL_F3_SHIFT                     16U
#define PINMUX_BALL_F5_SHIFT                     24U
#define PINMUX_BALL_G3_SHIFT                     8U
#define PINMUX_BALL_G5_SHIFT                     8U
#define PINMUX_BALL_G16_SHIFT                    24U
#define PINMUX_BALL_G17_SHIFT                    0U
#define PINMUX_BALL_G19_SHIFT                    16U
#define PINMUX_BALL_H3_SHIFT                     16U
#define PINMUX_BALL_H16_SHIFT                    16U
#define PINMUX_BALL_H17_SHIFT                    24U
#define PINMUX_BALL_H18_SHIFT                    24U
#define PINMUX_BALL_H19_SHIFT                    16U
#define PINMUX_BALL_J3_SHIFT                     24U
#define PINMUX_BALL_J18_SHIFT                    0U
#define PINMUX_BALL_J19_SHIFT                    8U
#define PINMUX_BALL_K2_SHIFT                     8U
#define PINMUX_BALL_K5_SHIFT                     0U
#define PINMUX_BALL_K15_SHIFT                    8U
#define PINMUX_BALL_K17_SHIFT                    0U
#define PINMUX_BALL_K18_SHIFT                    0U
#define PINMUX_BALL_K19_SHIFT                    8U
#define PINMUX_BALL_L5_SHIFT                     24U
#define PINMUX_BALL_L15_SHIFT                    16U
#define PINMUX_BALL_M1_SHIFT                     0U
#define PINMUX_BALL_M2_SHIFT                     24U
#define PINMUX_BALL_M5_SHIFT                     8U
#define PINMUX_BALL_M15_SHIFT                    24U
#define PINMUX_BALL_M17_SHIFT                    8U
#define PINMUX_BALL_N1_SHIFT                     16U
#define PINMUX_BALL_N2_SHIFT                     0U
#define PINMUX_BALL_N5_SHIFT                     24U
#define PINMUX_BALL_N15_SHIFT                    8U
#define PINMUX_BALL_N17_SHIFT                    16U
#define PINMUX_BALL_N19_SHIFT                    0U
#define PINMUX_BALL_P1_SHIFT                     24U
#define PINMUX_BALL_P5_SHIFT                     8U
#define PINMUX_BALL_R2_SHIFT                     24U
#define PINMUX_BALL_R5_SHIFT                     24U
#define PINMUX_BALL_R6_SHIFT                     0U
#define PINMUX_BALL_R7_SHIFT                     24U
#define PINMUX_BALL_R8_SHIFT                     24U
#define PINMUX_BALL_R9_SHIFT                     0U
#define PINMUX_BALL_T1_SHIFT                     0U
#define PINMUX_BALL_T12_SHIFT                    24U
#define PINMUX_BALL_U1_SHIFT                     24U
#define PINMUX_BALL_V2_SHIFT                     16U
#define PINMUX_BALL_V5_SHIFT                     8U
#define PINMUX_BALL_V6_SHIFT                     16U
#define PINMUX_BALL_V7_SHIFT                     16U
#define PINMUX_BALL_V10_SHIFT                    16U
#define PINMUX_BALL_W3_SHIFT                     16U
#define PINMUX_BALL_W5_SHIFT                     8U
#define PINMUX_BALL_W6_SHIFT                     16U
#define PINMUX_BALL_W9_SHIFT                     8U
#define PINMUX_BALL_W10_SHIFT                    0U

#define PINMUX_GATE_EMIF_CLK_SHIFT               8U
#define PINMUX_GIOB_DISABLE_HET2_SHIFT           16U
#define PINMUX_ALT_ADC_TRIGGER_SHIFT             0U
#define PINMUX_ETHERNET_SHIFT                    24U

#define PINMUX_BALL_A5_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_A5_SHIFT))
#define PINMUX_BALL_A11_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_A11_SHIFT))
#define PINMUX_BALL_A14_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_A14_SHIFT))
#define PINMUX_BALL_B2_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_B2_SHIFT))
#define PINMUX_BALL_B3_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_B3_SHIFT))
#define PINMUX_BALL_B4_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_B4_SHIFT))
#define PINMUX_BALL_B5_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_B5_SHIFT))
#define PINMUX_BALL_B6_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_B6_SHIFT))
#define PINMUX_BALL_B11_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_B11_SHIFT))
#define PINMUX_BALL_C1_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_C1_SHIFT))
#define PINMUX_BALL_C2_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_C2_SHIFT))
#define PINMUX_BALL_C3_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_C3_SHIFT))
#define PINMUX_BALL_C4_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_C4_SHIFT))
#define PINMUX_BALL_C5_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_C5_SHIFT))
#define PINMUX_BALL_C6_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_C6_SHIFT))
#define PINMUX_BALL_C7_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_C7_SHIFT))
#define PINMUX_BALL_C8_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_C8_SHIFT))
#define PINMUX_BALL_C9_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_C9_SHIFT))
#define PINMUX_BALL_C10_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_C10_SHIFT))
#define PINMUX_BALL_C11_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_C11_SHIFT))
#define PINMUX_BALL_C12_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_C12_SHIFT))
#define PINMUX_BALL_C13_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_C13_SHIFT))
#define PINMUX_BALL_C14_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_C14_SHIFT))
#define PINMUX_BALL_C15_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_C15_SHIFT))
#define PINMUX_BALL_C16_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_C16_SHIFT))
#define PINMUX_BALL_C17_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_C17_SHIFT))
#define PINMUX_BALL_D3_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_D3_SHIFT))
#define PINMUX_BALL_D4_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_D4_SHIFT))
#define PINMUX_BALL_D5_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_D5_SHIFT))
#define PINMUX_BALL_D14_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_D14_SHIFT))
#define PINMUX_BALL_D15_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_D15_SHIFT))
#define PINMUX_BALL_D16_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_D16_SHIFT))
#define PINMUX_BALL_D17_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_D17_SHIFT))
#define PINMUX_BALL_D19_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_D19_SHIFT))
#define PINMUX_BALL_E1_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_E1_SHIFT))
#define PINMUX_BALL_E3_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_E3_SHIFT))
#define PINMUX_BALL_E5_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_E5_SHIFT))
#define PINMUX_BALL_E6_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_E6_SHIFT))
#define PINMUX_BALL_E7_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_E7_SHIFT))
#define PINMUX_BALL_E8_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_E8_SHIFT))
#define PINMUX_BALL_E9_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_E9_SHIFT))
#define PINMUX_BALL_E10_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_E10_SHIFT))
#define PINMUX_BALL_E11_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_E11_SHIFT))
#define PINMUX_BALL_E12_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_E12_SHIFT))
#define PINMUX_BALL_E13_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_E13_SHIFT))
#define PINMUX_BALL_E16_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_E16_SHIFT))
#define PINMUX_BALL_E17_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_E17_SHIFT))
#define PINMUX_BALL_E18_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_E18_SHIFT))
#define PINMUX_BALL_E19_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_E19_SHIFT))
#define PINMUX_BALL_F3_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_F3_SHIFT))
#define PINMUX_BALL_F5_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_F5_SHIFT))
#define PINMUX_BALL_G3_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_G3_SHIFT))
#define PINMUX_BALL_G5_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_G4_SHIFT))
#define PINMUX_BALL_G16_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_G16_SHIFT))
#define PINMUX_BALL_G17_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_G17_SHIFT))
#define PINMUX_BALL_G19_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_G19_SHIFT))
#define PINMUX_BALL_H3_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_H3_SHIFT))
#define PINMUX_BALL_H16_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_H16_SHIFT))
#define PINMUX_BALL_H17_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_H17_SHIFT))
#define PINMUX_BALL_H18_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_H18_SHIFT))
#define PINMUX_BALL_H19_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_H19_SHIFT))
#define PINMUX_BALL_J3_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_J3_SHIFT))
#define PINMUX_BALL_J18_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_J18_SHIFT))
#define PINMUX_BALL_J19_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_J19_SHIFT))
#define PINMUX_BALL_K2_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_K2_SHIFT))
#define PINMUX_BALL_K5_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_K4_SHIFT))
#define PINMUX_BALL_K15_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_K15_SHIFT))
#define PINMUX_BALL_K17_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_K17_SHIFT))
#define PINMUX_BALL_K18_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_K18_SHIFT))
#define PINMUX_BALL_K19_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_K19_SHIFT))
#define PINMUX_BALL_L5_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_L4_SHIFT))
#define PINMUX_BALL_L15_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_L15_SHIFT))
#define PINMUX_BALL_M1_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_M1_SHIFT))
#define PINMUX_BALL_M2_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_M2_SHIFT))
#define PINMUX_BALL_M5_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_M4_SHIFT))
#define PINMUX_BALL_M15_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_M15_SHIFT))
#define PINMUX_BALL_M17_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_M17_SHIFT))
#define PINMUX_BALL_N1_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_N1_SHIFT))
#define PINMUX_BALL_N2_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_N2_SHIFT))
#define PINMUX_BALL_N5_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_N4_SHIFT))
#define PINMUX_BALL_N15_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_N15_SHIFT))
#define PINMUX_BALL_N17_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_N17_SHIFT))
#define PINMUX_BALL_N19_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_N19_SHIFT))
#define PINMUX_BALL_P1_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_P1_SHIFT))
#define PINMUX_BALL_P5_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_P4_SHIFT))
#define PINMUX_BALL_R2_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_R2_SHIFT))
#define PINMUX_BALL_R5_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_R5_SHIFT))
#define PINMUX_BALL_R6_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_R6_SHIFT))
#define PINMUX_BALL_R7_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_R7_SHIFT))
#define PINMUX_BALL_R8_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_R8_SHIFT))
#define PINMUX_BALL_R9_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_R9_SHIFT))
#define PINMUX_BALL_T1_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_T1_SHIFT))
#define PINMUX_BALL_T12_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_T12_SHIFT))
#define PINMUX_BALL_U1_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_U1_SHIFT))
#define PINMUX_BALL_V2_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_V2_SHIFT))
#define PINMUX_BALL_V5_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_V5_SHIFT))
#define PINMUX_BALL_V6_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_V6_SHIFT))
#define PINMUX_BALL_V7_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_V7_SHIFT))
#define PINMUX_BALL_V10_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_V10_SHIFT))
#define PINMUX_BALL_W3_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_W3_SHIFT))
#define PINMUX_BALL_W5_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_W5_SHIFT))
#define PINMUX_BALL_W6_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_W6_SHIFT))
#define PINMUX_BALL_W9_MASK                     (~(uint32)((uint32)0xFFU << PINMUX_BALL_W9_SHIFT))
#define PINMUX_BALL_W10_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_BALL_W10_SHIFT))

#define PINMUX_GATE_EMIF_CLK_MASK               (~(uint32)((uint32)0xFFU << PINMUX_GATE_EMIF_CLK_SHIFT))
#define PINMUX_GIOB_DISABLE_HET2_MASK           (~(uint32)((uint32)0xFFU << PINMUX_GIOB_DISABLE_HET2_SHIFT))
#define PINMUX_ALT_ADC_TRIGGER_MASK             (~(uint32)((uint32)0xFFU << PINMUX_ALT_ADC_TRIGGER_SHIFT))
#define PINMUX_ETHERNET_MASK                    (~(uint32)((uint32)0xFFU << PINMUX_ETHERNET_SHIFT))



#define PINMUX_BALL_A5_GIOA_0                   ((uint32)((uint32)0x1U <<  PINMUX_BALL_A5_SHIFT))
#define PINMUX_BALL_A5_OHCI_PRT_RcvDpls_1       ((uint32)((uint32)0x2U <<  PINMUX_BALL_A5_SHIFT))
#define PINMUX_BALL_A5_W2FC_RXDPI               ((uint32)((uint32)0x4U <<  PINMUX_BALL_A5_SHIFT))

#define PINMUX_BALL_A11_HET1_14                 ((uint32)((uint32)0x1U <<  PINMUX_BALL_A11_SHIFT))
#define PINMUX_BALL_A11_OHCI_RCFG_txSe0_0       ((uint32)((uint32)0x2U <<  PINMUX_BALL_A11_SHIFT))

#define PINMUX_BALL_A14_HET1_26                 ((uint32)((uint32)0x1U <<  PINMUX_BALL_A14_SHIFT))
#define PINMUX_BALL_A14_MII_RXD_1               ((uint32)((uint32)0x2U <<  PINMUX_BALL_A14_SHIFT))
#define PINMUX_BALL_A14_RMII_RXD_1              ((uint32)((uint32)0x4U <<  PINMUX_BALL_A14_SHIFT))

#define PINMUX_BALL_B2_MIBSPI3NCS_2             ((uint32)((uint32)0x1U <<  PINMUX_BALL_B2_SHIFT))
#define PINMUX_BALL_B2_I2C_SDA                  ((uint32)((uint32)0x2U <<  PINMUX_BALL_B2_SHIFT))
#define PINMUX_BALL_B2_HET1_27                  ((uint32)((uint32)0x4U <<  PINMUX_BALL_B2_SHIFT))

#define PINMUX_BALL_B3_HET1_22                  ((uint32)((uint32)0x1U <<  PINMUX_BALL_B3_SHIFT))
#define PINMUX_BALL_B3_OHCI_RCFG_txSe0_1        ((uint32)((uint32)0x2U <<  PINMUX_BALL_B3_SHIFT))
#define PINMUX_BALL_B3_W2FC_SE0O                ((uint32)((uint32)0x4U <<  PINMUX_BALL_B3_SHIFT))

#define PINMUX_BALL_B4_HET1_12                  ((uint32)((uint32)0x1U <<  PINMUX_BALL_B4_SHIFT))
#define PINMUX_BALL_B4_MII_CRS                  ((uint32)((uint32)0x2U <<  PINMUX_BALL_B4_SHIFT))
#define PINMUX_BALL_B4_RMII_CRS_DV              ((uint32)((uint32)0x4U <<  PINMUX_BALL_B4_SHIFT))

#define PINMUX_BALL_B5_GIOA_5                   ((uint32)((uint32)0x1U <<  PINMUX_BALL_B5_SHIFT))
#define PINMUX_BALL_B5_EXTCLKIN                 ((uint32)((uint32)0x2U <<  PINMUX_BALL_B5_SHIFT))

#define PINMUX_BALL_B6_MIBSPI5NCS_1             ((uint32)((uint32)0x1U <<  PINMUX_BALL_B6_SHIFT))
#define PINMUX_BALL_B6_DMM_DATA_6               ((uint32)((uint32)0x2U <<  PINMUX_BALL_B6_SHIFT))

#define PINMUX_BALL_B11_HET1_30                 ((uint32)((uint32)0x1U <<  PINMUX_BALL_B11_SHIFT))
#define PINMUX_BALL_B11_MII_RX_DV               ((uint32)((uint32)0x2U <<  PINMUX_BALL_B11_SHIFT))
#define PINMUX_BALL_B11_OHCI_RCFG_speed_0       ((uint32)((uint32)0x4U <<  PINMUX_BALL_B11_SHIFT))

#define PINMUX_BALL_C1_GIOA_2                   ((uint32)((uint32)0x1U <<  PINMUX_BALL_C1_SHIFT))
#define PINMUX_BALL_C1_OHCI_RCFG_txdPls_1       ((uint32)((uint32)0x2U <<  PINMUX_BALL_C1_SHIFT))
#define PINMUX_BALL_C1_W2FC_TXDO                ((uint32)((uint32)0x4U <<  PINMUX_BALL_C1_SHIFT))
#define PINMUX_BALL_C1_HET2_0                   ((uint32)((uint32)0x8U <<  PINMUX_BALL_C1_SHIFT))

#define PINMUX_BALL_C2_GIOA_1                   ((uint32)((uint32)0x1U <<  PINMUX_BALL_C2_SHIFT))
#define PINMUX_BALL_C2_OHCI_PRT_RcvDmns_1       ((uint32)((uint32)0x2U <<  PINMUX_BALL_C2_SHIFT))
#define PINMUX_BALL_C2_W2FC_RXDMI               ((uint32)((uint32)0x4U <<  PINMUX_BALL_C2_SHIFT))

#define PINMUX_BALL_C3_MIBSPI3NCS_3             ((uint32)((uint32)0x1U <<  PINMUX_BALL_C3_SHIFT))
#define PINMUX_BALL_C3_I2C_SCL                  ((uint32)((uint32)0x2U <<  PINMUX_BALL_C3_SHIFT))
#define PINMUX_BALL_C3_HET1_29                  ((uint32)((uint32)0x4U <<  PINMUX_BALL_C3_SHIFT))

#define PINMUX_BALL_C4_EMIF_ADDR_6              ((uint32)((uint32)0x1U <<  PINMUX_BALL_C4_SHIFT))
#define PINMUX_BALL_C4_RTP_DATA_13              ((uint32)((uint32)0x2U <<  PINMUX_BALL_C4_SHIFT))
#define PINMUX_BALL_C4_HET2_11                  ((uint32)((uint32)0x4U <<  PINMUX_BALL_C4_SHIFT))

#define PINMUX_BALL_C5_EMIF_ADDR_7              ((uint32)((uint32)0x1U <<  PINMUX_BALL_C5_SHIFT))
#define PINMUX_BALL_C5_RTP_DATA_12              ((uint32)((uint32)0x2U <<  PINMUX_BALL_C5_SHIFT))
#define PINMUX_BALL_C5_HET2_13                  ((uint32)((uint32)0x4U <<  PINMUX_BALL_C5_SHIFT))

#define PINMUX_BALL_C6_EMIF_ADDR_8              ((uint32)((uint32)0x1U <<  PINMUX_BALL_C6_SHIFT))
#define PINMUX_BALL_C6_RTP_DATA_11              ((uint32)((uint32)0x2U <<  PINMUX_BALL_C6_SHIFT))
#define PINMUX_BALL_C6_HET2_15                  ((uint32)((uint32)0x4U <<  PINMUX_BALL_C6_SHIFT))

#define PINMUX_BALL_C7_EMIF_ADDR_9              ((uint32)((uint32)0x1U <<  PINMUX_BALL_C7_SHIFT))
#define PINMUX_BALL_C7_RTP_DATA_10              ((uint32)((uint32)0x2U <<  PINMUX_BALL_C7_SHIFT))

#define PINMUX_BALL_C8_EMIF_ADDR_10             ((uint32)((uint32)0x1U <<  PINMUX_BALL_C8_SHIFT))
#define PINMUX_BALL_C8_RTP_DATA_09              ((uint32)((uint32)0x2U <<  PINMUX_BALL_C8_SHIFT))

#define PINMUX_BALL_C9_EMIF_ADDR_11             ((uint32)((uint32)0x1U <<  PINMUX_BALL_C9_SHIFT))
#define PINMUX_BALL_C9_RTP_DATA_08              ((uint32)((uint32)0x2U <<  PINMUX_BALL_C9_SHIFT))

#define PINMUX_BALL_C10_EMIF_ADDR_12            ((uint32)((uint32)0x1U <<  PINMUX_BALL_C10_SHIFT))
#define PINMUX_BALL_C10_RTP_DATA_06             ((uint32)((uint32)0x2U <<  PINMUX_BALL_C10_SHIFT))

#define PINMUX_BALL_C11_EMIF_ADDR_13            ((uint32)((uint32)0x1U <<  PINMUX_BALL_C11_SHIFT))
#define PINMUX_BALL_C11_RTP_DATA_05             ((uint32)((uint32)0x2U <<  PINMUX_BALL_C11_SHIFT))

#define PINMUX_BALL_C12_EMIF_ADDR_14            ((uint32)((uint32)0x1U <<  PINMUX_BALL_C12_SHIFT))
#define PINMUX_BALL_C12_RTP_DATA_04             ((uint32)((uint32)0x2U <<  PINMUX_BALL_C12_SHIFT))

#define PINMUX_BALL_C13_EMIF_ADDR_15            ((uint32)((uint32)0x1U <<  PINMUX_BALL_C13_SHIFT))
#define PINMUX_BALL_C13_RTP_DATA_03             ((uint32)((uint32)0x2U <<  PINMUX_BALL_C13_SHIFT))

#define PINMUX_BALL_C14_EMIF_ADDR_17            ((uint32)((uint32)0x1U <<  PINMUX_BALL_C14_SHIFT))
#define PINMUX_BALL_C14_RTP_DATA_01             ((uint32)((uint32)0x2U <<  PINMUX_BALL_C14_SHIFT))

#define PINMUX_BALL_C15_EMIF_ADDR_19            ((uint32)((uint32)0x1U <<  PINMUX_BALL_C15_SHIFT))
#define PINMUX_BALL_C15_RTP_nENA                ((uint32)((uint32)0x2U <<  PINMUX_BALL_C15_SHIFT))

#define PINMUX_BALL_C16_EMIF_ADDR_20            ((uint32)((uint32)0x1U <<  PINMUX_BALL_C16_SHIFT))
#define PINMUX_BALL_C16_RTP_nSYNC               ((uint32)((uint32)0x2U <<  PINMUX_BALL_C16_SHIFT))

#define PINMUX_BALL_C17_EMIF_ADDR_21            ((uint32)((uint32)0x1U <<  PINMUX_BALL_C17_SHIFT))
#define PINMUX_BALL_C17_RTP_CLK                 ((uint32)((uint32)0x2U <<  PINMUX_BALL_C17_SHIFT))

#define PINMUX_BALL_D3_SPI2NENA                 ((uint32)((uint32)0x1U <<  PINMUX_BALL_D3_SHIFT))
#define PINMUX_BALL_D3_SPI2NCS_1                ((uint32)((uint32)0x2U <<  PINMUX_BALL_D3_SHIFT))

#define PINMUX_BALL_D4_EMIF_ADDR_0              ((uint32)((uint32)0x1U <<  PINMUX_BALL_D4_SHIFT))
#define PINMUX_BALL_D4_HET2_1                   ((uint32)((uint32)0x2U <<  PINMUX_BALL_D4_SHIFT))

#define PINMUX_BALL_D5_EMIF_ADDR_1              ((uint32)((uint32)0x1U <<  PINMUX_BALL_D5_SHIFT))
#define PINMUX_BALL_D5_HET2_3                   ((uint32)((uint32)0x2U <<  PINMUX_BALL_D5_SHIFT))

#define PINMUX_BALL_D14_EMIF_ADDR_16            ((uint32)((uint32)0x1U <<  PINMUX_BALL_D14_SHIFT))
#define PINMUX_BALL_D14_RTP_DATA_02             ((uint32)((uint32)0x2U <<  PINMUX_BALL_D14_SHIFT))

#define PINMUX_BALL_D15_EMIF_ADDR_18            ((uint32)((uint32)0x1U <<  PINMUX_BALL_D15_SHIFT))
#define PINMUX_BALL_D15_RTP_DATA_0              ((uint32)((uint32)0x2U <<  PINMUX_BALL_D15_SHIFT))

#define PINMUX_BALL_D16_EMIF_BA_1               ((uint32)((uint32)0x1U <<  PINMUX_BALL_D16_SHIFT))
#define PINMUX_BALL_D16_HET2_5                  ((uint32)((uint32)0x2U <<  PINMUX_BALL_D16_SHIFT))

#define PINMUX_BALL_D17_EMIF_nWE                ((uint32)((uint32)0x1U <<  PINMUX_BALL_D17_SHIFT))
#define PINMUX_BALL_D17_EMIF_RNW                ((uint32)((uint32)0x2U <<  PINMUX_BALL_D17_SHIFT))

#define PINMUX_BALL_D19_HET1_10                 ((uint32)((uint32)0x1U <<  PINMUX_BALL_D19_SHIFT))
#define PINMUX_BALL_D19_MII_TX_CLK              ((uint32)((uint32)0x2U <<  PINMUX_BALL_D19_SHIFT))
#define PINMUX_BALL_D19_OHCI_RCFG_txEnL_0       ((uint32)((uint32)0x4U <<  PINMUX_BALL_D19_SHIFT))
#define PINMUX_BALL_D19_MII_TX_AVCLK4           ((uint32)((uint32)0x8U <<  PINMUX_BALL_D19_SHIFT))

#define PINMUX_BALL_E1_GIOA_3                   ((uint32)((uint32)0x1U <<  PINMUX_BALL_E1_SHIFT))
#define PINMUX_BALL_E1_HET2_2                   ((uint32)((uint32)0x2U <<  PINMUX_BALL_E1_SHIFT))

#define PINMUX_BALL_E3_HET1_11                  ((uint32)((uint32)0x1U <<  PINMUX_BALL_E3_SHIFT))
#define PINMUX_BALL_E3_MIBSPI3NCS_4             ((uint32)((uint32)0x2U <<  PINMUX_BALL_E3_SHIFT))
#define PINMUX_BALL_E3_HET2_18                  ((uint32)((uint32)0x4U <<  PINMUX_BALL_E3_SHIFT))
#define PINMUX_BALL_E3_OHCI_PRT_OvrCurrent_1    ((uint32)((uint32)0x8U <<  PINMUX_BALL_E3_SHIFT))
#define PINMUX_BALL_E3_W2FC_VBUSI               ((uint32)((uint32)0x10U <<  PINMUX_BALL_E3_SHIFT))

#define PINMUX_BALL_E5_ETMDATA_20               ((uint32)((uint32)0x1U <<  PINMUX_BALL_E5_SHIFT))
#define PINMUX_BALL_E5_EMIF_DATA_4              ((uint32)((uint32)0x2U <<  PINMUX_BALL_E5_SHIFT))

#define PINMUX_BALL_E6_ETMDATA_11               ((uint32)((uint32)0x1U <<  PINMUX_BALL_E6_SHIFT))
#define PINMUX_BALL_E6_EMIF_ADDR_2              ((uint32)((uint32)0x2U <<  PINMUX_BALL_E6_SHIFT))

#define PINMUX_BALL_E7_ETMDATA_10               ((uint32)((uint32)0x1U <<  PINMUX_BALL_E7_SHIFT))
#define PINMUX_BALL_E7_EMIF_ADDR_3              ((uint32)((uint32)0x2U <<  PINMUX_BALL_E7_SHIFT))

#define PINMUX_BALL_E8_ETMDATA_09               ((uint32)((uint32)0x1U <<  PINMUX_BALL_E8_SHIFT))
#define PINMUX_BALL_E8_EMIF_ADDR_4              ((uint32)((uint32)0x2U <<  PINMUX_BALL_E8_SHIFT))

#define PINMUX_BALL_E9_ETMDATA_08               ((uint32)((uint32)0x1U <<  PINMUX_BALL_E9_SHIFT))
#define PINMUX_BALL_E9_EMIF_ADDR_5              ((uint32)((uint32)0x2U <<  PINMUX_BALL_E9_SHIFT))

#define PINMUX_BALL_E10_ETMDATA_15              ((uint32)((uint32)0x1U <<  PINMUX_BALL_E10_SHIFT))
#define PINMUX_BALL_E10_EMIF_nDQM_0             ((uint32)((uint32)0x2U <<  PINMUX_BALL_E10_SHIFT))

#define PINMUX_BALL_E11_ETMDATA_14              ((uint32)((uint32)0x1U <<  PINMUX_BALL_E11_SHIFT))
#define PINMUX_BALL_E11_EMIF_nDQM_1             ((uint32)((uint32)0x2U <<  PINMUX_BALL_E11_SHIFT))

#define PINMUX_BALL_E12_ETMDATA_13              ((uint32)((uint32)0x1U <<  PINMUX_BALL_E12_SHIFT))
#define PINMUX_BALL_E12_EMIF_nOE                ((uint32)((uint32)0x2U <<  PINMUX_BALL_E12_SHIFT))

#define PINMUX_BALL_E13_ETMDATA_12              ((uint32)((uint32)0x1U <<  PINMUX_BALL_E13_SHIFT))
#define PINMUX_BALL_E13_EMIF_BA_0               ((uint32)((uint32)0x2U <<  PINMUX_BALL_E13_SHIFT))

#define PINMUX_BALL_E16_MIBSPI5SIMO_1           ((uint32)((uint32)0x1U <<  PINMUX_BALL_E16_SHIFT))
#define PINMUX_BALL_E16_DMM_DATA_9              ((uint32)((uint32)0x2U <<  PINMUX_BALL_E16_SHIFT))

#define PINMUX_BALL_E17_MIBSPI5SOMI_1           ((uint32)((uint32)0x1U <<  PINMUX_BALL_E17_SHIFT))
#define PINMUX_BALL_E17_DMM_DATA_13             ((uint32)((uint32)0x2U <<  PINMUX_BALL_E17_SHIFT))

#define PINMUX_BALL_E18_HET1_08                 ((uint32)((uint32)0x1U <<  PINMUX_BALL_E18_SHIFT))
#define PINMUX_BALL_E18_MIBSPI1SIMO_1           ((uint32)((uint32)0x2U <<  PINMUX_BALL_E18_SHIFT))
#define PINMUX_BALL_E18_MII_TXD_3               ((uint32)((uint32)0x4U <<  PINMUX_BALL_E18_SHIFT))
#define PINMUX_BALL_E18_OHCI_PRT_OvrCurrent_0   ((uint32)((uint32)0x8U <<  PINMUX_BALL_E18_SHIFT))

#define PINMUX_BALL_E19_MIBSPI5NCS_0            ((uint32)((uint32)0x1U <<  PINMUX_BALL_E19_SHIFT))
#define PINMUX_BALL_E19_DMM_DATA_5              ((uint32)((uint32)0x2U <<  PINMUX_BALL_E19_SHIFT))

#define PINMUX_BALL_F3_MIBSPI1NCS_1             ((uint32)((uint32)0x1U <<  PINMUX_BALL_F3_SHIFT))
#define PINMUX_BALL_F3_HET1_17                  ((uint32)((uint32)0x2U <<  PINMUX_BALL_F3_SHIFT))
#define PINMUX_BALL_F3_MII_COL                  ((uint32)((uint32)0x4U <<  PINMUX_BALL_F3_SHIFT))
#define PINMUX_BALL_F3_OHCI_RCFG_suspend_0      ((uint32)((uint32)0x8U <<  PINMUX_BALL_F3_SHIFT))

#define PINMUX_BALL_F5_ETMDATA_21               ((uint32)((uint32)0x1U <<  PINMUX_BALL_F5_SHIFT))
#define PINMUX_BALL_F5_EMIF_DATA_5              ((uint32)((uint32)0x2U <<  PINMUX_BALL_F5_SHIFT))

#define PINMUX_BALL_G3_MIBSPI1NCS_2             ((uint32)((uint32)0x1U <<  PINMUX_BALL_G3_SHIFT))
#define PINMUX_BALL_G3_HET1_19                  ((uint32)((uint32)0x2U <<  PINMUX_BALL_G3_SHIFT))
#define PINMUX_BALL_G3_MDIO                     ((uint32)((uint32)0x4U <<  PINMUX_BALL_G3_SHIFT))

#define PINMUX_BALL_G5_ETMDATA_22               ((uint32)((uint32)0x1U <<  PINMUX_BALL_G5_SHIFT))
#define PINMUX_BALL_G5_EMIF_DATA_6              ((uint32)((uint32)0x2U <<  PINMUX_BALL_G5_SHIFT))

#define PINMUX_BALL_G16_MIBSPI5SOMI_3           ((uint32)((uint32)0x1U <<  PINMUX_BALL_G16_SHIFT))
#define PINMUX_BALL_G16_DMM_DATA_15             ((uint32)((uint32)0x2U <<  PINMUX_BALL_G16_SHIFT))

#define PINMUX_BALL_G17_MIBSPI5SIMO_3           ((uint32)((uint32)0x1U <<  PINMUX_BALL_G17_SHIFT))
#define PINMUX_BALL_G17_DMM_DATA_11             ((uint32)((uint32)0x2U <<  PINMUX_BALL_G17_SHIFT))

#define PINMUX_BALL_G19_MIBSPI1NENA             ((uint32)((uint32)0x1U <<  PINMUX_BALL_G19_SHIFT))
#define PINMUX_BALL_G19_HET1_23                 ((uint32)((uint32)0x2U <<  PINMUX_BALL_G19_SHIFT))
#define PINMUX_BALL_G19_MII_RXD_2               ((uint32)((uint32)0x4U <<  PINMUX_BALL_G19_SHIFT))
#define PINMUX_BALL_G19_OHCI_PRT_RcvDpls_0      ((uint32)((uint32)0x8U <<  PINMUX_BALL_G19_SHIFT))

#define PINMUX_BALL_H3_GIOA_6                   ((uint32)((uint32)0x1U <<  PINMUX_BALL_H3_SHIFT))
#define PINMUX_BALL_H3_HET2_4                   ((uint32)((uint32)0x2U <<  PINMUX_BALL_H3_SHIFT))

#define PINMUX_BALL_H16_MIBSPI5SOMI_2           ((uint32)((uint32)0x1U <<  PINMUX_BALL_H16_SHIFT))
#define PINMUX_BALL_H16_DMM_DATA_14             ((uint32)((uint32)0x2U <<  PINMUX_BALL_H16_SHIFT))

#define PINMUX_BALL_H17_MIBSPI5SIMO_2           ((uint32)((uint32)0x1U <<  PINMUX_BALL_H17_SHIFT))
#define PINMUX_BALL_H17_DMM_DATA_10             ((uint32)((uint32)0x2U <<  PINMUX_BALL_H17_SHIFT))

#define PINMUX_BALL_H18_MIBSPI5NENA             ((uint32)((uint32)0x1U <<  PINMUX_BALL_H18_SHIFT))
#define PINMUX_BALL_H18_DMM_DATA_7              ((uint32)((uint32)0x2U <<  PINMUX_BALL_H18_SHIFT))
#define PINMUX_BALL_H18_MII_RXD_3               ((uint32)((uint32)0x4U <<  PINMUX_BALL_H18_SHIFT))
#define PINMUX_BALL_H18_OHCI_PRT_RcvDmns_0      ((uint32)((uint32)0x8U <<  PINMUX_BALL_H18_SHIFT))

#define PINMUX_BALL_H19_MIBSPI5CLK              ((uint32)((uint32)0x1U <<  PINMUX_BALL_H19_SHIFT))
#define PINMUX_BALL_H19_DMM_DATA_4              ((uint32)((uint32)0x2U <<  PINMUX_BALL_H19_SHIFT))
#define PINMUX_BALL_H19_MII_TXEN                ((uint32)((uint32)0x4U <<  PINMUX_BALL_H19_SHIFT))
#define PINMUX_BALL_H19_RMII_TXEN               ((uint32)((uint32)0x8U <<  PINMUX_BALL_H19_SHIFT))

#define PINMUX_BALL_J3_MIBSPI1NCS_3             ((uint32)((uint32)0x1U <<  PINMUX_BALL_J3_SHIFT))
#define PINMUX_BALL_J3_HET1_21                  ((uint32)((uint32)0x2U <<  PINMUX_BALL_J3_SHIFT))

#define PINMUX_BALL_J18_MIBSPI5SOMI_0           ((uint32)((uint32)0x1U <<  PINMUX_BALL_J18_SHIFT))
#define PINMUX_BALL_J18_DMM_DATA_12             ((uint32)((uint32)0x2U <<  PINMUX_BALL_J18_SHIFT))
#define PINMUX_BALL_J18_MII_TXD_0               ((uint32)((uint32)0x4U <<  PINMUX_BALL_J18_SHIFT))
#define PINMUX_BALL_J18_RMII_TXD_0              ((uint32)((uint32)0x8U <<  PINMUX_BALL_J18_SHIFT))

#define PINMUX_BALL_J19_MIBSPI5SIMO_0           ((uint32)((uint32)0x1U <<  PINMUX_BALL_J19_SHIFT))
#define PINMUX_BALL_J19_DMM_DATA_8              ((uint32)((uint32)0x2U <<  PINMUX_BALL_J19_SHIFT))
#define PINMUX_BALL_J19_MII_TXD_1               ((uint32)((uint32)0x4U <<  PINMUX_BALL_J19_SHIFT))
#define PINMUX_BALL_J19_RMII_TXD_1              ((uint32)((uint32)0x8U <<  PINMUX_BALL_J19_SHIFT))

#define PINMUX_BALL_K2_GIOB_1                   ((uint32)((uint32)0x1U <<  PINMUX_BALL_K2_SHIFT))
#define PINMUX_BALL_K2_OHCI_RCFG_PrtPower_0     ((uint32)((uint32)0x2U <<  PINMUX_BALL_K2_SHIFT))

#define PINMUX_BALL_K5_ETMDATA_23               ((uint32)((uint32)0x1U <<  PINMUX_BALL_K5_SHIFT))
#define PINMUX_BALL_K5_EMIF_DATA_7              ((uint32)((uint32)0x2U <<  PINMUX_BALL_K5_SHIFT))

#define PINMUX_BALL_K15_ETMDATA_16              ((uint32)((uint32)0x1U <<  PINMUX_BALL_K15_SHIFT))
#define PINMUX_BALL_K15_EMIF_DATA_0             ((uint32)((uint32)0x2U <<  PINMUX_BALL_K15_SHIFT))

#define PINMUX_BALL_K17_EMIF_nCS_3              ((uint32)((uint32)0x1U <<  PINMUX_BALL_K17_SHIFT))
#define PINMUX_BALL_K17_RTP_DATA_14             ((uint32)((uint32)0x2U <<  PINMUX_BALL_K17_SHIFT))
#define PINMUX_BALL_K17_HET2_9                  ((uint32)((uint32)0x4U <<  PINMUX_BALL_K17_SHIFT))

#define PINMUX_BALL_K18_HET1_0                  ((uint32)((uint32)0x1U <<  PINMUX_BALL_K18_SHIFT))
#define PINMUX_BALL_K18_SPI4CLK                 ((uint32)((uint32)0x2U <<  PINMUX_BALL_K18_SHIFT))

#define PINMUX_BALL_K19_HET1_28                 ((uint32)((uint32)0x1U <<  PINMUX_BALL_K19_SHIFT))
#define PINMUX_BALL_K19_MII_RXCLK               ((uint32)((uint32)0x2U <<  PINMUX_BALL_K19_SHIFT))
#define PINMUX_BALL_K19_RMII_REFCLK             ((uint32)((uint32)0x4U <<  PINMUX_BALL_K19_SHIFT))
#define PINMUX_BALL_K19_MII_RX_AVCLK4           ((uint32)((uint32)0x8U <<  PINMUX_BALL_K19_SHIFT))

#define PINMUX_BALL_L5_ETMDATA_24               ((uint32)((uint32)0x1U <<  PINMUX_BALL_L5_SHIFT))
#define PINMUX_BALL_L5_EMIF_DATA_8              ((uint32)((uint32)0x2U <<  PINMUX_BALL_L5_SHIFT))

#define PINMUX_BALL_L15_ETMDATA_17              ((uint32)((uint32)0x1U <<  PINMUX_BALL_L15_SHIFT))
#define PINMUX_BALL_L15_EMIF_DATA_1             ((uint32)((uint32)0x2U <<  PINMUX_BALL_L15_SHIFT))

#define PINMUX_BALL_M1_GIOA_7                   ((uint32)((uint32)0x1U <<  PINMUX_BALL_M1_SHIFT))
#define PINMUX_BALL_M1_HET2_6                   ((uint32)((uint32)0x2U <<  PINMUX_BALL_M1_SHIFT))

#define PINMUX_BALL_M2_GIOB_0                   ((uint32)((uint32)0x1U <<  PINMUX_BALL_M2_SHIFT))
#define PINMUX_BALL_M2_OHCI_RCFG_txDpls_0       ((uint32)((uint32)0x2U <<  PINMUX_BALL_M2_SHIFT))

#define PINMUX_BALL_M5_ETMDATA_25               ((uint32)((uint32)0x1U <<  PINMUX_BALL_M5_SHIFT))
#define PINMUX_BALL_M5_EMIF_DATA_9              ((uint32)((uint32)0x2U <<  PINMUX_BALL_M5_SHIFT))

#define PINMUX_BALL_M15_ETMDATA_18              ((uint32)((uint32)0x1U <<  PINMUX_BALL_M15_SHIFT))
#define PINMUX_BALL_M15_EMIF_DATA_2             ((uint32)((uint32)0x2U <<  PINMUX_BALL_M15_SHIFT))

#define PINMUX_BALL_M17_EMIF_nCS_4              ((uint32)((uint32)0x1U <<  PINMUX_BALL_M17_SHIFT))
#define PINMUX_BALL_M17_RTP_DATA_07             ((uint32)((uint32)0x2U <<  PINMUX_BALL_M17_SHIFT))

#define PINMUX_BALL_N1_HET1_15                  ((uint32)((uint32)0x1U <<  PINMUX_BALL_N1_SHIFT))
#define PINMUX_BALL_N1_MIBSPI1NCS_4             ((uint32)((uint32)0x2U <<  PINMUX_BALL_N1_SHIFT))

#define PINMUX_BALL_N2_HET1_13                  ((uint32)((uint32)0x1U <<  PINMUX_BALL_N2_SHIFT))
#define PINMUX_BALL_N2_SCITX                    ((uint32)((uint32)0x2U <<  PINMUX_BALL_N2_SHIFT))

#define PINMUX_BALL_N5_ETMDATA_26               ((uint32)((uint32)0x1U <<  PINMUX_BALL_N5_SHIFT))
#define PINMUX_BALL_N5_EMIF_DATA_10             ((uint32)((uint32)0x2U <<  PINMUX_BALL_N5_SHIFT))

#define PINMUX_BALL_N15_ETMDATA_19              ((uint32)((uint32)0x1U <<  PINMUX_BALL_N15_SHIFT))
#define PINMUX_BALL_N15_EMIF_DATA_3             ((uint32)((uint32)0x2U <<  PINMUX_BALL_N15_SHIFT))

#define PINMUX_BALL_N17_EMIF_nCS_0              ((uint32)((uint32)0x1U <<  PINMUX_BALL_N17_SHIFT))
#define PINMUX_BALL_N17_RTP_DATA_15             ((uint32)((uint32)0x2U <<  PINMUX_BALL_N17_SHIFT))
#define PINMUX_BALL_N17_HET2_7                  ((uint32)((uint32)0x4U <<  PINMUX_BALL_N17_SHIFT))

#define PINMUX_BALL_N19_AD1EVT                  ((uint32)((uint32)0x1U <<  PINMUX_BALL_N19_SHIFT))
#define PINMUX_BALL_N19_MII_RX_ER               ((uint32)((uint32)0x2U <<  PINMUX_BALL_N19_SHIFT))
#define PINMUX_BALL_N19_RMII_RX_ER              ((uint32)((uint32)0x4U <<  PINMUX_BALL_N19_SHIFT))

#define PINMUX_BALL_P1_HET1_24                  ((uint32)((uint32)0x1U <<  PINMUX_BALL_P1_SHIFT))
#define PINMUX_BALL_P1_MIBSPI1NCS_5             ((uint32)((uint32)0x2U <<  PINMUX_BALL_P1_SHIFT))
#define PINMUX_BALL_P1_MII_RXD_0                ((uint32)((uint32)0x4U <<  PINMUX_BALL_P1_SHIFT))
#define PINMUX_BALL_P1_RMII_RXD_0               ((uint32)((uint32)0x8U <<  PINMUX_BALL_P1_SHIFT))

#define PINMUX_BALL_P5_ETMDATA_27               ((uint32)((uint32)0x1U <<  PINMUX_BALL_P5_SHIFT))
#define PINMUX_BALL_P5_EMIF_DATA_11             ((uint32)((uint32)0x2U <<  PINMUX_BALL_P5_SHIFT))

#define PINMUX_BALL_R2_MIBSPI1NCS_0             ((uint32)((uint32)0x1U <<  PINMUX_BALL_R2_SHIFT))
#define PINMUX_BALL_R2_MIBSPI1SOMI_1            ((uint32)((uint32)0x2U <<  PINMUX_BALL_R2_SHIFT))
#define PINMUX_BALL_R2_MII_TXD_2                ((uint32)((uint32)0x4U <<  PINMUX_BALL_R2_SHIFT))
#define PINMUX_BALL_R2_OHCI_PRT_RcvData_0       ((uint32)((uint32)0x8U <<  PINMUX_BALL_R2_SHIFT))

#define PINMUX_BALL_R5_ETMDATA_28               ((uint32)((uint32)0x1U <<  PINMUX_BALL_R5_SHIFT))
#define PINMUX_BALL_R5_EMIF_DATA_12             ((uint32)((uint32)0x2U <<  PINMUX_BALL_R5_SHIFT))

#define PINMUX_BALL_R6_ETMDATA_29               ((uint32)((uint32)0x1U <<  PINMUX_BALL_R6_SHIFT))
#define PINMUX_BALL_R6_EMIF_DATA_13             ((uint32)((uint32)0x2U <<  PINMUX_BALL_R6_SHIFT))

#define PINMUX_BALL_R7_ETMDATA_30               ((uint32)((uint32)0x1U <<  PINMUX_BALL_R7_SHIFT))
#define PINMUX_BALL_R7_EMIF_DATA_14             ((uint32)((uint32)0x2U <<  PINMUX_BALL_R7_SHIFT))

#define PINMUX_BALL_R8_ETMDATA_31               ((uint32)((uint32)0x1U <<  PINMUX_BALL_R8_SHIFT))
#define PINMUX_BALL_R8_EMIF_DATA_15             ((uint32)((uint32)0x2U <<  PINMUX_BALL_R8_SHIFT))

#define PINMUX_BALL_R9_ETMTRACECLKIN            ((uint32)((uint32)0x1U <<  PINMUX_BALL_R9_SHIFT))
#define PINMUX_BALL_R9_EXTCLKIN2                ((uint32)((uint32)0x2U <<  PINMUX_BALL_R9_SHIFT))

#define PINMUX_BALL_T1_HET1_07                  ((uint32)((uint32)0x1U <<  PINMUX_BALL_T1_SHIFT))
#define PINMUX_BALL_T1_OHCI_RCFG_PrtPower_1     ((uint32)((uint32)0x2U <<  PINMUX_BALL_T1_SHIFT))
#define PINMUX_BALL_T1_W2FC_GZO                 ((uint32)((uint32)0x4U <<  PINMUX_BALL_T1_SHIFT))
#define PINMUX_BALL_T1_HET2_14                  ((uint32)((uint32)0x8U <<  PINMUX_BALL_T1_SHIFT))

#define PINMUX_BALL_T12_MIBSPI5NCS_3            ((uint32)((uint32)0x1U <<  PINMUX_BALL_T12_SHIFT))
#define PINMUX_BALL_T12_DMM_DATA_3              ((uint32)((uint32)0x2U <<  PINMUX_BALL_T12_SHIFT))

#define PINMUX_BALL_U1_HET1_03                  ((uint32)((uint32)0x1U <<  PINMUX_BALL_U1_SHIFT))
#define PINMUX_BALL_U1_SPI4NCS_0                ((uint32)((uint32)0x2U <<  PINMUX_BALL_U1_SHIFT))
#define PINMUX_BALL_U1_OHCI_RCFG_speed_1        ((uint32)((uint32)0x4U <<  PINMUX_BALL_U1_SHIFT))
#define PINMUX_BALL_U1_W2FC_PUENON              ((uint32)((uint32)0x8U <<  PINMUX_BALL_U1_SHIFT))
#define PINMUX_BALL_U1_HET2_10                  ((uint32)((uint32)0x10U <<  PINMUX_BALL_U1_SHIFT))

#define PINMUX_BALL_V2_HET1_01                  ((uint32)((uint32)0x1U <<  PINMUX_BALL_V2_SHIFT))
#define PINMUX_BALL_V2_SPI4NENA                 ((uint32)((uint32)0x2U <<  PINMUX_BALL_V2_SHIFT))
#define PINMUX_BALL_V2_OHCI_RCFG_txEnL_1        ((uint32)((uint32)0x4U <<  PINMUX_BALL_V2_SHIFT))
#define PINMUX_BALL_V2_W2FC_PUENO               ((uint32)((uint32)0x8U <<  PINMUX_BALL_V2_SHIFT))
#define PINMUX_BALL_V2_HET2_8                   ((uint32)((uint32)0x10U <<  PINMUX_BALL_V2_SHIFT))

#define PINMUX_BALL_V5_MIBSPI3NCS_1             ((uint32)((uint32)0x1U <<  PINMUX_BALL_V5_SHIFT))
#define PINMUX_BALL_V5_HET1_25                  ((uint32)((uint32)0x2U <<  PINMUX_BALL_V5_SHIFT))
#define PINMUX_BALL_V5_MDCLK                    ((uint32)((uint32)0x4U <<  PINMUX_BALL_V5_SHIFT))

#define PINMUX_BALL_V6_HET1_05                  ((uint32)((uint32)0x1U <<  PINMUX_BALL_V6_SHIFT))
#define PINMUX_BALL_V6_SPI4SOMI                 ((uint32)((uint32)0x2U <<  PINMUX_BALL_V6_SHIFT))
#define PINMUX_BALL_V6_HET2_12                  ((uint32)((uint32)0x4U <<  PINMUX_BALL_V6_SHIFT))

#define PINMUX_BALL_V7_HET1_09                  ((uint32)((uint32)0x1U <<  PINMUX_BALL_V7_SHIFT))
#define PINMUX_BALL_V7_HET2_16                  ((uint32)((uint32)0x2U <<  PINMUX_BALL_V7_SHIFT))
#define PINMUX_BALL_V7_OHCI_RCFG_suspend_1      ((uint32)((uint32)0x4U <<  PINMUX_BALL_V7_SHIFT))
#define PINMUX_BALL_V7_W2FC_SUSPENDO            ((uint32)((uint32)0x8U <<  PINMUX_BALL_V7_SHIFT))

#define PINMUX_BALL_V10_MIBSPI3NCS_0            ((uint32)((uint32)0x1U <<  PINMUX_BALL_V10_SHIFT))
#define PINMUX_BALL_V10_AD2EVT                  ((uint32)((uint32)0x2U <<  PINMUX_BALL_V10_SHIFT))
#define PINMUX_BALL_V10_GIOB_2                  ((uint32)((uint32)0x4U <<  PINMUX_BALL_V10_SHIFT))

#define PINMUX_BALL_W3_HET1_06                  ((uint32)((uint32)0x1U <<  PINMUX_BALL_W3_SHIFT))
#define PINMUX_BALL_W3_SCIRX                    ((uint32)((uint32)0x2U <<  PINMUX_BALL_W3_SHIFT))

#define PINMUX_BALL_W5_HET1_02                  ((uint32)((uint32)0x1U <<  PINMUX_BALL_W5_SHIFT))
#define PINMUX_BALL_W5_SPI4SIMO                 ((uint32)((uint32)0x2U <<  PINMUX_BALL_W5_SHIFT))

#define PINMUX_BALL_W6_MIBSPI5NCS_2             ((uint32)((uint32)0x1U <<  PINMUX_BALL_W6_SHIFT))
#define PINMUX_BALL_W6_DMM_DATA_2               ((uint32)((uint32)0x2U <<  PINMUX_BALL_W6_SHIFT))

#define PINMUX_BALL_W9_MIBSPI3NENA              ((uint32)((uint32)0x1U <<  PINMUX_BALL_W9_SHIFT))
#define PINMUX_BALL_W9_MIBSPI3NCS_5             ((uint32)((uint32)0x2U <<  PINMUX_BALL_W9_SHIFT))
#define PINMUX_BALL_W9_HET1_31                  ((uint32)((uint32)0x4U <<  PINMUX_BALL_W9_SHIFT))

#define PINMUX_BALL_W10_GIOB_3                  ((uint32)((uint32)0x1U <<  PINMUX_BALL_W10_SHIFT))
#define PINMUX_BALL_W10_OHCI_PRT_RcvData_1      ((uint32)((uint32)0x2U <<  PINMUX_BALL_W10_SHIFT))
#define PINMUX_BALL_W10_W2FC_RXDI               ((uint32)((uint32)0x4U <<  PINMUX_BALL_W10_SHIFT))

#define PINMUX_GATE_EMIF_CLK_ON                 ((uint32)((uint32)0x0 <<  PINMUX_GATE_EMIF_CLK_SHIFT))
#define PINMUX_GIOB_DISABLE_HET2_ON             ((uint32)((uint32)0x1U <<  PINMUX_GIOB_DISABLE_HET2_SHIFT))
#define PINMUX_GATE_EMIF_CLK_OFF                ((uint32)((uint32)0x1U <<  PINMUX_GATE_EMIF_CLK_SHIFT))
#define PINMUX_GIOB_DISABLE_HET2_OFF            ((uint32)((uint32)0x0 <<  PINMUX_GIOB_DISABLE_HET2_SHIFT))
#define PINMUX_ALT_ADC_TRIGGER_1                ((uint32)((uint32)0x1U <<  PINMUX_ALT_ADC_TRIGGER_SHIFT))
#define PINMUX_ALT_ADC_TRIGGER_2                ((uint32)((uint32)0x2U <<  PINMUX_ALT_ADC_TRIGGER_SHIFT))
#define PINMUX_ETHERNET_MII                     ((uint32)((uint32)0x0 <<  PINMUX_ETHERNET_SHIFT))
#define PINMUX_ETHERNET_RMII                    ((uint32)((uint32)0x1U <<  PINMUX_ETHERNET_SHIFT))

typedef struct pinmux_config_reg
{
    uint32 CONFIG_PINMMR0;
    uint32 CONFIG_PINMMR1;
    uint32 CONFIG_PINMMR2;
    uint32 CONFIG_PINMMR3;
    uint32 CONFIG_PINMMR4;
    uint32 CONFIG_PINMMR5;
    uint32 CONFIG_PINMMR6;
    uint32 CONFIG_PINMMR7;
    uint32 CONFIG_PINMMR8;
    uint32 CONFIG_PINMMR9;
    uint32 CONFIG_PINMMR10;
    uint32 CONFIG_PINMMR11;
    uint32 CONFIG_PINMMR12;
    uint32 CONFIG_PINMMR13;
    uint32 CONFIG_PINMMR14;
    uint32 CONFIG_PINMMR15;
    uint32 CONFIG_PINMMR16;
    uint32 CONFIG_PINMMR17;
    uint32 CONFIG_PINMMR18;
    uint32 CONFIG_PINMMR19;
    uint32 CONFIG_PINMMR20;
    uint32 CONFIG_PINMMR21;
    uint32 CONFIG_PINMMR22;
    uint32 CONFIG_PINMMR23;
    uint32 CONFIG_PINMMR24;
    uint32 CONFIG_PINMMR25;
    uint32 CONFIG_PINMMR26;
    uint32 CONFIG_PINMMR27;
    uint32 CONFIG_PINMMR28;
    uint32 CONFIG_PINMMR29;
    uint32 CONFIG_PINMMR30;
}pinmux_config_reg_t;


/**
 *  @defgroup IOMM IOMM
 *  @brief I/O Multiplexing and Control Module.
 *
 *  The IOMM contains memory-mapped registers (MMR) that control device-specific multiplexed functions.
 *  The safety and diagnostic features of the IOMM are:
 *  - Kicker mechanism to protect the MMRs from accidental writes
 *  - Master-id checker to only allow the CPU to write to the MMRs
 *  - Error indication for access violations
 *
 *  Related Files
 *   - reg_pinmux.h
 *   - pinmux.h
 *   - pinmux.c
 *  @addtogroup IOMM
 *  @{
 */

/** @fn void muxInit(void)
*   @brief Initializes the PINMUX Driver
*
*   This function initializes the PINMUX module and configures the selected
*   pinmux settings as per the user selection in the GUI
*/
void muxInit(void);
void pinmuxGetConfigValue(pinmux_config_reg_t *config_reg, config_value_type_t type);
/* USER CODE BEGIN (0) */
/* USER CODE END */

/**@}*/
#ifdef __cplusplus
}
#endif /*extern "C" */
#endif
