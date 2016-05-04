/*
*********************************************************************************************************
*                                         uC/Probe Communication
*
*                         (c) Copyright 2007-2008; Micrium, Inc.; Weston, FL
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
*                                              uC/Probe
*
*                                        Communication: Serial
*
* Filename      : probe_usb_os.c
* Version       : V2.20
* Programmer(s) : BAN
* Note(s)       : (1) This file is the uC/OS-II layer for the uC/Probe Serial Communication Module.
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <probe_com.h>
#include  <probe_serial.h>
#include  <os.h>

#if (PROBE_COM_CFG_SERIAL_EN == DEF_ENABLED)

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  PROBE_SERIAL_CFG_TASK_STK_SIZE_PCT_FULL             90u
#define  PROBE_SERIAL_CFG_TASK_STK_SIZE_LIMIT       (PROBE_SERIAL_CFG_TASK_STK_SIZE     * (100u - PROBE_SERIAL_CFG_TASK_STK_SIZE_PCT_FULL))    / 100u

/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


static  OS_TCB   ProbeSerial_OS_TaskTCB;                        /* Probe serial task TCB.                               */
                                                                /* Probe serial task stack.                             */
static  CPU_STK  ProbeSerial_OS_TaskStk[PROBE_SERIAL_CFG_TASK_STK_SIZE];


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  ProbeSerial_OS_Task (void *p_arg);                /* Probe serial task.                                   */


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            ProbeSerial_OS_Init()
*
* Description : Initialize the serial task for Probe communication.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : ProbeSerial_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  ProbeSerial_OS_Init (void)
{
    OS_ERR  os_err;

   
    OSTaskCreate((OS_TCB     *)&ProbeSerial_OS_TaskTCB,
                 (CPU_CHAR   *)"Probe Serial",
                 (OS_TASK_PTR ) ProbeSerial_OS_Task, 
                 (void       *) 0,
                 (OS_PRIO     ) PROBE_SERIAL_CFG_TASK_PRIO,
                 (CPU_STK    *)&ProbeSerial_OS_TaskStk[0],
                 (CPU_STK_SIZE)PROBE_SERIAL_CFG_TASK_STK_SIZE_LIMIT,
                 (CPU_STK_SIZE) PROBE_SERIAL_CFG_TASK_STK_SIZE,
                 (OS_MSG_QTY  ) 0u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&os_err);
    
    (void)os_err;
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                             LOCAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          ProbeSerial_OS_Task()
*
* Description : Task which waits for packets to be received, formalates responses, and begins transmission.
*
* Argument(s) : p_arg        Argument passed to 'ProbeSerial_OS_Task()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  ProbeSerial_OS_Task (void *p_arg)
{
    ProbeSerial_Task(p_arg);
}




#endif
