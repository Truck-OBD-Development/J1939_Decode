/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*               This file is provided as an example on how to use Micrium products.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only. This file can be modified as
*               required to meet the end-product requirements.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                       APPLICATION CONFIGURATION
*
*                                          Texas Instruments
*                                 RM48x Hercules Development Kit(HDK)
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : FF
*********************************************************************************************************
*/

#ifndef  APP_CFG_H
#define  APP_CFG_H


/*
*********************************************************************************************************
*                                                INCLUDE
*********************************************************************************************************
*/

#include  <cpu.h>


/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/

#define  APP_CFG_PROBE_COM_EN                       DEF_ENABLED
#define  APP_CFG_SERIAL_EN                          DEF_ENABLED


/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_PRIO                3u
#define  APP_CFG_TASK_OBJ0_PRIO                 4u
#define  APP_CFG_TASK_OBJ1_PRIO                 5u
#define  APP_CFG_TASK_EQ0_PRIO                  7u
#define  APP_CFG_TASK_EQ1_PRIO                  8u


/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_STK_SIZE            256u
#define  APP_CFG_TASK_EQ_STK_SIZE               512u
#define  APP_CFG_TASK_OBJ_STK_SIZE              256u


/*
*********************************************************************************************************
*                                            TASK STACK SIZES LIMIT
*********************************************************************************************************
*/

#define  APP_CFG_TASK_START_STK_SIZE_PCT_FULL             90u
#define  APP_CFG_TASK_START_STK_SIZE_LIMIT       (APP_CFG_TASK_START_STK_SIZE     * (100u - APP_CFG_TASK_START_STK_SIZE_PCT_FULL))    / 100u


/*
*********************************************************************************************************
*                                                 uC/SERIAL
*
* Note(s) : (1) Configure SERIAL_CFG_MAX_NBR_IF to the number of interfaces (i.e., UARTs) that will be
*               present.
*
*           (2) Configure SERIAL_CFG_RD_BUF_EN to enable/disable read buffer functionality.  The serial
*               core stores received data in the read buffer until the user requests it, providing a
*               reliable guarantee against receive overrun.
*
*           (3) Configure SERIAL_CFG_WR_BUF_EN to enable/disable write buffer functionality.  The serial
*               core stores line driver transmit data in the write buffer while the serial interface is
*               transmitting application data.
*
*           (4) Configure SERIAL_CFG_ARG_CHK_EXT_EN to enable/disable extended argument checking
*               functionality.
*
*           (5) Configure SERIAL_CFG_TX_DESC_NBR to allow multiple transmit operations (i.e., Serial_Wr,
*               Serial_WrAsync) to be queued.
*********************************************************************************************************
*/

#define  SERIAL_CFG_MAX_NBR_IF                            2u    /* See Note #1.                                         */

#define  SERIAL_CFG_RD_BUF_EN                    DEF_DISABLED   /* See Note #2.                                         */

#define  SERIAL_CFG_WR_BUF_EN                    DEF_DISABLED   /* See Note #3.                                         */

#define  SERIAL_CFG_ARG_CHK_EXT_EN               DEF_DISABLED   /* See Note #4.                                         */

#define  SERIAL_CFG_TX_DESC_NBR                            1    /* See Note #5.                                         */


/*
*********************************************************************************************************
*                                    uC/SERIAL APPLICATION CONFIGURATION
*********************************************************************************************************
*/

#define  APP_SERIAL_CFG_TRACE_EN                DEF_DISABLED
#define  APP_SERIAL_CFG_TRACE_PORT_NAME         "SCI1"


/*
*********************************************************************************************************
*                                       uC/PROBE APPLICATION CONFIGURATION
*********************************************************************************************************
*/

#define  APP_CFG_PROBE_SERIAL_PORT_NAME         "SCI1"


/*
*********************************************************************************************************
*                                     TRACE / DEBUG CONFIGURATION
*********************************************************************************************************
*/

#ifndef  TRACE_LEVEL_OFF
#define  TRACE_LEVEL_OFF                                   0
#endif

#ifndef  TRACE_LEVEL_INFO
#define  TRACE_LEVEL_INFO                                  1
#endif

#ifndef  TRACE_LEVEL_DBG
#define  TRACE_LEVEL_DBG                                   2
#endif

#include  <stdio.h>
void  App_SerPrintf  (CPU_CHAR *format, ...);
#define  APP_CFG_TRACE_LEVEL                    TRACE_LEVEL_OFF
#define  APP_CFG_TRACE                          App_SerPrintf

#define  APP_TRACE_INFO(x)                     ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_INFO)  ? (void)(APP_CFG_TRACE x) : (void)0)
#define  APP_TRACE_DBG(x)                      ((APP_CFG_TRACE_LEVEL >= TRACE_LEVEL_DBG)   ? (void)(APP_CFG_TRACE x) : (void)0)


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of Application configuration include             */
