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
* Filename      : probe_serial.h
* Version       : V2.20
* Programmer(s) : BAN
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               PROBE_SERIAL present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  PROBE_SERIAL_PRESENT                                   /* See Note #1.                                         */
#define  PROBE_SERIAL_PRESENT


/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef    PROBE_SERIAL_MODULE
#define   PROBE_SERIAL_EXT
#else
#define   PROBE_SERIAL_EXT  extern
#endif


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include  <probe_com.h>

#include  <serial.h>
#include  <serial_line_probe.h>


#if (PROBE_COM_CFG_SERIAL_EN == DEF_ENABLED)

/*
*********************************************************************************************************
*                                                 DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  ProbeSerial_Init     (CPU_CHAR       *pser_name,
                            SERIAL_IF_CFG  *pser_cfg);

void  ProbeSerial_Task     (void           *p_arg);


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*                                    DEFINED IN OS'S probe_serial_os.c
*********************************************************************************************************
*/

void  ProbeSerial_OS_Init  (void);


/*
*********************************************************************************************************
*                                        CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  PROBE_SERIAL_CFG_TASK_PRIO
#error  "PROBE_SERIAL_CFG_TASK_PRIO            not #define'd in 'probe_com_cfg.h'   "
#endif

#ifndef  PROBE_SERIAL_CFG_TASK_STK_SIZE
#error  "PROBE_SERIAL_CFG_TASK_STK_SIZE         not #define'd in 'probe_com_cfg.h'  "
#endif
#endif



#ifndef  PROBE_SERIAL_CFG_RX_BUF_SIZE
#error  "PROBE_SERIAL_CFG_RX_BUF_SIZE          not #define'd in 'probe_com_cfg.h'   "
#error  "                                [MUST be  >= 32   ]                        "
#error  "                                [     &&  <= 65535]                        "

#elif  ((PROBE_SERIAL_CFG_RX_BUF_SIZE > 65535) || \
        (PROBE_SERIAL_CFG_RX_BUF_SIZE < 32   ))
#error  "PROBE_SERIAL_CFG_RX_BUF_SIZE     illegally #define'd in 'probe_com_cfg.h'  "
#error  "                                 [MUST be  >= 32   ]                       "
#error  "                                 [     &&  <= 65535]                       "
#endif



#ifndef  PROBE_SERIAL_CFG_TX_BUF_SIZE
#error  "PROBE_SERIAL_CFG_TX_BUF_SIZE           not #define'd in 'probe_com_cfg.h'  "
#error  "                                [MUST be  >= 32   ]                        "
#error  "                                [     &&  <= 65535]                        "

#elif  ((PROBE_SERIAL_CFG_TX_BUF_SIZE > 65535) || \
        (PROBE_SERIAL_CFG_TX_BUF_SIZE < 32   ))
#error  "PROBE_SERIAL_CFG_TX_BUF_SIZE     illegally #define'd in 'probe_com_cfg.h'  "
#error  "                                [MUST be  >= 32   ]                        "
#error  "                                [     &&  <= 65535]                        "

#endif


/*
*********************************************************************************************************
*                                              MODULE END
*
* Note(s) : See 'MODULE  Note #1'.
*********************************************************************************************************
*/

#endif                                                          /* End of PROBE_COM_RS232 module include (see Note #1). */
