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
*                                      Communication: Serial
*
* Filename      : probe_serial.c
* Version       : V2.20
* Programmer(s) : BAN
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define   PROBE_SERIAL_MODULE
#include  <probe_serial.h>

#if (PROBE_COM_CFG_SERIAL_EN == DEF_ENABLED)

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  CPU_INT08U     ProbeSerial_RxBuf[PROBE_SERIAL_CFG_RX_BUF_SIZE + 1];

static  CPU_INT08U     ProbeSerial_TxBuf[PROBE_SERIAL_CFG_TX_BUF_SIZE + 1];

static  SERIAL_IF_NBR  ProbeSerial_SerialIF_Nbr;


/*
*********************************************************************************************************
*                                        LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           ProbeSerial_Init()
*
* Description : Initialize the serial communication module.
*
* Argument(s) : ser_id          Serial port ID.
*               pser_cfg        Pointer to serial port configuration.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  ProbeSerial_Init (CPU_CHAR       *pser_name,
                        SERIAL_IF_CFG  *pser_cfg)
{
    SERIAL_ERR  err;


    ProbeSerial_SerialIF_Nbr = Serial_Open((CPU_CHAR      *) pser_name,
                                           (SERIAL_IF_CFG *) pser_cfg,
                                           (SERIAL_ERR    *)&err);
    if (err != SERIAL_ERR_NONE) {
        return;
    }
    
    Serial_SetLineDrv((SERIAL_IF_NBR        ) ProbeSerial_SerialIF_Nbr,
                      (SERIAL_LINE_DRV_API *)&SerialLine_Probe,
                      (SERIAL_ERR          *)&err);

    if (err != SERIAL_ERR_NONE) {
        return;
    }


    ProbeSerial_OS_Init();
}


/*
*********************************************************************************************************
*                                           ProbeSerial_Task()
*
* Description : Server for the uC/Probe Serial Communication Module.
*
* Argument(s) : p_arg           The argument passed to 'ProbeSerial_Task()' by  'ProbeSerial_OS_Task()'.
*
* Return(s)   : none.
*
* Caller(s)   : ProbeSerial_OS_Task().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  ProbeSerial_Task (void *p_arg)
{
    SERIAL_IF_NBR  if_nbr;
    CPU_SIZE_T     rx_len;
    CPU_SIZE_T     tx_len;
    SERIAL_ERR     ser_err;


    (void)p_arg;                                                /* Prevent compiler warning.                            */

    if_nbr = ProbeSerial_SerialIF_Nbr;

    while (DEF_TRUE)  {
        rx_len = Serial_Rd((SERIAL_IF_NBR  ) if_nbr,
                           (void          *)&ProbeSerial_RxBuf[0],
                           (CPU_SIZE_T     )(PROBE_SERIAL_CFG_RX_BUF_SIZE + 1),
                           (CPU_INT32U     )0u,
                           (SERIAL_ERR    *)&ser_err);

        if (rx_len > 0) {
            if (ser_err == SERIAL_ERR_LINE_END) {
                                                                /* Parse the packet and formulate a response.           */
                tx_len = ProbeCom_ParseRxPkt((void       *)&ProbeSerial_RxBuf[0],
                                             (void       *)&ProbeSerial_TxBuf[0],
                                             (CPU_SIZE_T  ) rx_len,
                                             (CPU_SIZE_T  ) PROBE_SERIAL_CFG_TX_BUF_SIZE);

                Serial_Wr((SERIAL_IF_NBR  ) if_nbr,
                          (void          *)&ProbeSerial_TxBuf[0],
                          (CPU_SIZE_T     ) tx_len,
                          (CPU_INT32U     ) 0u,
                          (SERIAL_ERR    *)&ser_err);

                (void)ser_err;
            }
        }
    }
}


#endif
