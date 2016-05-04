/*
*********************************************************************************************************
*                                     SERIAL (BYTE) COMMUNICATION
*
*                         (c) Copyright 2007-2014; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                     SERIAL (BYTE) COMMUNICATION
*                                          DEVICE DRIVER BSP
*
*                                          Texas Instruments
*                                 RM48x Hercules Development Kit(HDK)
*
* Filename      : serial_bsp_rm48.h
* Version       : V2.00.01
* Programmer(s) : NB
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               SERIAL_BSP_TEMPLATE present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef   SERIAL_BSP_RM48_PRESENT
#define   SERIAL_BSP_RM48_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <bsp.h>

#include  <serial.h>
#include  <serial_drv_rm48.h>


/*
*********************************************************************************************************
*                                           SERIAL DEVICES
*********************************************************************************************************
*/

extern  SERIAL_DEV_CFG  SerialDevCfg_RM48_SCI1;


/*$PAGE*/
/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/


#endif                                                          /* End of SERIAL_BSP_TEMPLATE module include.           */
