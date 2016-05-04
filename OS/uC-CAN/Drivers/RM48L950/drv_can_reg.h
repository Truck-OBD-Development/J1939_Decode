/*
****************************************************************************************************
*                                               uC/CAN
*                                       The Embedded CAN suite
*
*                          (c) Copyright 2003-2015; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/CAN is provided in source form to registered licensees ONLY.  It is 
*               illegal to distribute this source code to any third party unless you receive 
*               written permission by an authorized Micrium representative.  Knowledge of 
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest 
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
****************************************************************************************************
*/

/*
****************************************************************************************************
* Filename      : drv_can_reg.h
* Version       : V2.42.00
* Programmer(s) : E0
****************************************************************************************************
*/

#ifndef _DRV_CAN_REG_H_
#define _DRV_CAN_REG_H_

/*
****************************************************************************************************
*                                             INCLUDES
****************************************************************************************************
*/

#include "cpu.h"

/*
****************************************************************************************************
*                                             DEFINES
****************************************************************************************************
*/

#define TIRM48_CAN_REG_BASE_ADDR_DCAN1       0xFFF7DC00
#define TIRM48_CAN_REG_BASE_ADDR_DCAN2       0xFFF7DE00
#define TIRM48_CAN_REG_BASE_ADDR_DCAN3       0xFFF7E000

/* CAN Control Register */
#define TIRM48_CAN_REG_CTL_INIT_SET          0x00000001
#define TIRM48_CAN_REG_CTL_IE0_SET           0x00000002
#define TIRM48_CAN_REG_CTL_EIE_SET           0x00000008
#define TIRM48_CAN_REG_CTL_CCE_SET           0x00000040
#define TIRM48_CAN_REG_CTL_PMD_DIS           0x00001400

/* Error and Status Register */
#define TIRM48_CAN_REG_ES_EPASS_SET          0x00000020
#define TIRM48_CAN_REG_ES_BOFF_SET           0x00000080

/* Interrupt Register */
#define TIRM48_CAN_REG_INT_ERR               0x00008000

/* IF1/IF2 Command Registers */
//#define TIRM48_CAN_REG_IF_CMD_WR_SET         0x00800000
//#define TIRM48_CAN_REG_IF_CMD_MASK_SET       0x00400000
//#define TIRM48_CAN_REG_IF_CMD_ARB_SET        0x00200000
//#define TIRM48_CAN_REG_IF_CMD_CONTROL_SET    0x00100000
//#define TIRM48_CAN_REG_IF_CMD_CLRINTPND_SET  0x00080000
//#define TIRM48_CAN_REG_IF_CMD_TXRQST_SET     0x00040000
//#define TIRM48_CAN_REG_IF_CMD_NEWDAT_SET     0x00040000
//#define TIRM48_CAN_REG_IF_CMD_DATA_SET       0x00020000
//#define TIRM48_CAN_REG_IF_CMD_DATB_SET       0x00010000

#define TIRM48_CAN_REG_IF_STAT_BUSY_SET      0x80

/* IF1/IF2 Mask Registers */
#define TIRM48_CAN_REG_IF_MSK_MXTD_SET       0x80000000

/* IF1/IF2 Arbitration Registers */
#define TIRM48_CAN_REG_IF_ARB_MSGVAL_SET     0x80000000
#define TIRM48_CAN_REG_IF_ARB_XTD_SET        0x40000000
#define TIRM48_CAN_REG_IF_ARB_DIR_SET        0x20000000

/* IF1/IF2 Message Control Registers */
#define TIRM48_CAN_REG_IF_MCTL_DLC_MASK      0x0000000F
#define TIRM48_CAN_REG_IF_MCTL_EOB_SET       0x00000080
#define TIRM48_CAN_REG_IF_MCTL_RXIE_SET      0x00000400
#define TIRM48_CAN_REG_IF_MCTL_TXIE_SET      0x00000800
#define TIRM48_CAN_REG_IF_MCTL_UMASK_SET     0x00001000

/* CAN TX IO Control Register */
#define TIRM48_CAN_REG_TIOC_FUNC_SET         0x00000008

/* CAN RX IO Control Register */
#define TIRM48_CAN_REG_RIOC_FUNC_SET         0x00000008

/*
****************************************************************************************************
*                                            DATA TYPES
****************************************************************************************************
*/

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    TIRM48 CAN MESSAGE INTERFACE REGISTERS
*
* \ingroup  TIRM48_CAN
*
*           This structure defines the TIRM48 CAN message interface registers.
*/
/*------------------------------------------------------------------------------------------------*/
typedef volatile struct {
#if CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_LITTLE
    CPU_INT08U  NBR;                                  /*!< Command Register, Message Number       */
    CPU_INT08U  STAT;                                 /*!< Command Register, Status               */
    CPU_INT08U  CMD;                                  /*!< Command Register, Command              */
    CPU_INT08U  RES1;                                 /*!< Command Register, Reserved             */
#else
    CPU_INT08U  RES1;                                 /*!< Command Register, Reserved             */
    CPU_INT08U  CMD;                                  /*!< Command Register, Command              */
    CPU_INT08U  STAT;                                 /*!< Command Register, Status               */
    CPU_INT08U  NBR;                                  /*!< Command Register, Message Number       */
#endif
    CPU_INT32U  MSK;                                  /*!< Mask Registers                         */
    CPU_INT32U  ARB;                                  /*!< Arbitration Registers                  */
    CPU_INT32U  MCTL;                                 /*!< Message Control Registers              */
    CPU_INT08U  DATx[8];                              /*!< Data A and Data B Registers            */
    CPU_INT32U  RES2;                                 /*!< Reserved                               */
    CPU_INT32U  RES3;                                 /*!< Reserved                               */
} TIRM48_CAN_IF;

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    TIRM48 CAN REGISTERS
*
* \ingroup  TIRM48_CAN
*
*           This structure defines the TIRM48 CAN registers.
*/
/*------------------------------------------------------------------------------------------------*/
typedef volatile struct {
    CPU_INT32U     CTL;                               /*!< CAN Control Register                   */
    CPU_INT32U     ES;                                /*!< Error and Status Register              */
    CPU_INT32U     ERRC;                              /*!< Error Counter Register                 */
    CPU_INT32U     BTR;                               /*!< Bit Timing Register                    */
    CPU_INT32U     INT;                               /*!< Interrupt Register                     */
    CPU_INT32U     TEST;                              /*!< Test Register                          */
    CPU_INT32U     RES_0x18;                          /*!< 0x18 Reserved                          */
    CPU_INT32U     PERR;                              /*!< Parity Error Code Register             */
    CPU_INT32U     RES_0x20_0x7C[24];                 /*!< 0x20 - 0x7C Reserved                   */
    CPU_INT32U     ABOTR;                             /*!< Auto-Bus-On Time Register              */
    CPU_INT32U     TXRQX;                             /*!< Transmission Request X Register        */
    CPU_INT32U     TXRQx[4];                          /*!< Transmission Request Registers         */
    CPU_INT32U     NWDATX;                            /*!< New Data X Register                    */
    CPU_INT32U     NWDATx[4];                         /*!< New Data Registers                     */
    CPU_INT32U     INTPNDX;                           /*!< Interrupt Pending X Register           */
    CPU_INT32U     INTPNDx[4];                        /*!< Interrupt Pending Registers            */
    CPU_INT32U     MSGVALX;                           /*!< Message Valid X Register               */
    CPU_INT32U     MSGVALx[4];                        /*!< Message Valid Registers                */
    CPU_INT32U     RES_0xD4;                          /*!< 0xD4 Reserved                          */
    CPU_INT32U     INTMUXx[4];                        /*!< Interrupt Multiplexer Registers        */
    CPU_INT32U     RES_0xE8_0xFC[6];                  /*!< 0xE8 - 0xFC Reserved                   */
    TIRM48_CAN_IF  IFx[2];                            /*!< Message Interface Registers            */
    CPU_INT32U     IF3OBS;                            /*!< IF3 Observation Register               */
    CPU_INT32U     IF3MSK;                            /*!< IF3 Mask Register                      */
    CPU_INT32U     IF3ARB;                            /*!< IF3 Arbitration Register               */
    CPU_INT32U     IF3MCTL;                           /*!< IF3 Message Control Register           */
    CPU_INT32U     IF3DATA;                           /*!< IF3 Data A Register                    */
    CPU_INT32U     IF3DATB;                           /*!< IF3 Data B Register                    */
    CPU_INT32U     RES_0x158_0x15C[2];                /*!< 0x158 - 0x15C Reserved                 */
    CPU_INT32U     IF3UPD[4];                         /*!< IF3 Update Enable Registers            */    
    CPU_INT32U     RES_0x170_0x1DC[28];               /*!< 0x170 - 0x1DC Reserved                 */    
    CPU_INT32U     TIOC;                              /*!< CAN TX IO Control Register             */
    CPU_INT32U     RIOC;                              /*!< CAN RX IO Control Register             */    
} TIRM48_CAN_REG;


#endif  /* #ifndef _DRV_CAN_REG_H_ */

