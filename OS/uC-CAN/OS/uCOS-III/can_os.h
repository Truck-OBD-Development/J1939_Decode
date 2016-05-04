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
* Filename      : can_os.h
* Version       : V2.42.00
* Programmer(s) : E0
****************************************************************************************************
*/

#ifndef _CAN_OS_H_
#define _CAN_OS_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "can_frm.h"                                  /* CAN Frame handling                       */
#include "can_cfg.h"                                  /* CAN Configuration defines                */
#include "os.h"                                       /* RTOS: µC/OS-III services                 */


/*------------------------------------------------------------------------------------------------*/
/*! \brief                                OS: NO ERROR
*
*            This errorcode indicates 'no error detected'.
*/
/*------------------------------------------------------------------------------------------------*/
#define CANOS_NO_ERR      (CPU_INT08U)0


/*------------------------------------------------------------------------------------------------*/
/*                                     FUNCTION PROTOTYPES                                        */
/*------------------------------------------------------------------------------------------------*/

CPU_INT16S CANOS_Init          (void);

CPU_INT08U CANOS_PendRxFrame   (CPU_INT16U timeout, CPU_INT16S busId);
void       CANOS_PostRxFrame   (CPU_INT16S busId);
void       CANOS_ResetRx       (CPU_INT16S busId);

CPU_INT08U CANOS_PendTxFrame   (CPU_INT16U timeout, CPU_INT16S busId);
void       CANOS_PostTxFrame   (CPU_INT16S busId);
void       CANOS_ResetTx       (CPU_INT16S busId);

CPU_INT32U CANOS_GetTime       (void);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef _CAN_OS_H */
