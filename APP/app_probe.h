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
*                                           uC/Probe
*                                      Application Code
*
* Filename      : app_probe.h
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

#ifndef  APP_PROBE_MODULE_PRESENT
#define  APP_PROBE_MODULE_PRESENT

/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include  <lib_def.h>
#include  <cpu.h>
#include  <app_cfg.h>

/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/

#ifndef  APP_CFG_PROBE_COM_EN
#define  APP_CFG_PROBE_COM_EN                   DEF_DISABLED
#endif


/*
*********************************************************************************************************
*                                      CONDITIONAL INCLUDE FILES
*********************************************************************************************************
*/

#if (APP_CFG_PROBE_COM_EN == DEF_ENABLED)
#include    <probe_com.h>

#if (PROBE_COM_CFG_RS232_EN == DEF_ENABLED)
#include    <probe_rs232.h>
#endif

#if (PROBE_COM_CFG_SERIAL_EN == DEF_ENABLED)
#include    <probe_serial.h>
#endif

#if (PROBE_COM_CFG_TCPIP_EN == DEF_ENABLED)
#include    <probe_tcpip.h>
#endif
#endif


/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   APP_PROBE_MODULE
#define  APP_PROBE_MODULE_EXT
#else
#define  APP_PROBE_MODULE_EXT  extern
#endif


/*
*********************************************************************************************************
*                                                 DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                 MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#if (APP_CFG_PROBE_COM_EN == DEF_ENABLED)
void  App_ProbeInit  (void);
#endif

/*
*********************************************************************************************************
*                                          CONFIGURATION ERRORS
*********************************************************************************************************
*/

#ifndef  APP_CFG_PROBE_COM_EN
#error  "APP_CFG_PROBE_COM_EN                           not #define'd in 'app_cfg.h'     "
#error  "                                   [MUST be  DEF_DISABLED]                      "
#error  "                                   [     ||  DEF_ENABLED ]                      "


#elif   (PROBE_COM_CFG_SERIAL_EN == DEF_ENABLED)

#if     (APP_SERIAL_CFG_TRACE_EN == DEF_ENABLED)
#error  "APP_SERIAL_CFG_TRACE_EN                  illegally #define'd in 'app_cfg.h'     "
#error  "                                   [MUST be  DEF_ENABLED]                      "


#elif  (APP_CFG_TRACE_LEVEL != TRACE_LEVEL_OFF)
#error  "APP_CFG_TRACE_LEVEL                      illegally #define'd in 'app_cfg.h'     "
#error  "                                   [MUST be  TRACE_LEVEL_OFF]                   "

#endif
#endif
#endif
