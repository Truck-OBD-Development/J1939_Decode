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
* Filename      : can_err.h
* Version       : V2.42.00
* Programmer(s) : E0
* Purpose       : This include file holds the error codes and error macro used in the uC/CAN layers.
****************************************************************************************************
*/

#ifndef CAN_ERR__H
#define CAN_ERR__H

#ifdef __cplusplus
extern "C" {
#endif


/****************************************************************************/
/* uC/CAN global error variable (contains latest CAN error code             */
/****************************************************************************/
extern volatile CPU_INT16S can_errnum;

/****************************************************************************/
/* uC/CAN error codes                                                       */
/****************************************************************************/
#define CAN_ERR_NONE         0
#define CAN_ERR_NULLPTR     -1
#define CAN_ERR_SIGMOD      -4
#define CAN_ERR_BUSID       -10
#define CAN_ERR_FRMSIZE     -11
#define CAN_ERR_OPEN        -12
#define CAN_ERR_ENABLE      -14
#define CAN_ERR_IOCTRLFUNC  -15
#define CAN_ERR_NULLMSG     -17
#define CAN_ERR_MSGID       -18
#define CAN_ERR_MSGUNUSED   -19
#define CAN_ERR_MSGCREATE   -20
#define CAN_ERR_SIGID       -21
#define CAN_ERR_NULLSIGCFG  -22
#define CAN_ERR_CANSIZE     -23
#define CAN_ERR_BUFFSIZE    -24
#define CAN_ERR_SIGCREATE   -25
#define CAN_ERR_FRMWIDTH    -26
#define CAN_ERR_BUSINIT     -27
#define CAN_ERR_OSINIT      -240
#define CAN_ERR_OSFREE      -241
#define CAN_ERR_OSQUEUE     -242
#define CAN_ERR_OSALLOC     -244
#define CAN_ERR_OSSEM       -245
#define CAN_ERR_OSQPEND     -246
#define CAN_ERR_NOFRM       -247
#define CAN_ERR_OSSEMPEND   -248
#define CAN_ERR_OSSEMPOST   -248
#define CAN_ERR_OSQACCEPT   -249
#define CAN_ERR_UNKNOWN     -255

/****************************************************************************/
/* uC/CAN macros                                                            */
/****************************************************************************/
/*lint –emacro( {717}, CANSetErrRegister ) */
#define CANSetErrRegister(errorcode)     do { if (errorcode < CAN_ERR_NONE) {can_errnum = errorcode;} } while (0)

#ifdef __cplusplus
}
#endif

#endif /* CAN_ERR__H */

