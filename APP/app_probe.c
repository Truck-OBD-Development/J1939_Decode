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
* Filename      : app_probe.c
* Version       : V1.00
* Programmer(s) : FT
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/
#define  APP_PROBE_MODULE
#include <app_probe.h>


/*
*********************************************************************************************************
*                                                 ENABLE
*********************************************************************************************************
*/

#if (APP_CFG_PROBE_COM_EN == DEF_ENABLED)

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                    LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         App_ProbeInit()
*
* Description : Initialize all uC/Probe modules.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Note(s)     : none
*********************************************************************************************************
*/


void  App_ProbeInit (void)
{
#if (APP_CFG_PROBE_COM_EN    == DEF_ENABLED) && \
    (PROBE_COM_CFG_SERIAL_EN == DEF_ENABLED)
    SERIAL_IF_CFG  uart_cfg;
#endif

#if (APP_CFG_PROBE_COM_EN == DEF_ENABLED)
    APP_TRACE_INFO(("Initializing uC/Probe ... \n\r"));
    ProbeCom_Init();                                            /* Initialize the uC/Probe communications module            */

#if ((PROBE_COM_CFG_SERIAL_EN == DEF_ENABLED    )  && \
     (APP_SERIAL_CFG_TRACE_EN == DEF_DISABLED   )  && \
     (APP_CFG_TRACE_LEVEL     == TRACE_LEVEL_OFF))
    uart_cfg.Baudrate = SERIAL_BAUDRATE_115200;
    uart_cfg.DataBits = SERIAL_DATABITS_8;
    uart_cfg.StopBits = SERIAL_STOPBITS_1;
    uart_cfg.Parity   = SERIAL_PARITY_NONE;
    uart_cfg.FlowCtrl = SERIAL_FLOW_CTRL_NONE;

    ProbeSerial_Init((CPU_CHAR      *)APP_CFG_PROBE_SERIAL_PORT_NAME,
                     (SERIAL_IF_CFG *)&uart_cfg);
#endif


#if (PROBE_COM_CFG_TCPIP_EN == DEF_ENABLED)
    ProbeTCPIP_Init();
#endif
#endif
}

#endif
