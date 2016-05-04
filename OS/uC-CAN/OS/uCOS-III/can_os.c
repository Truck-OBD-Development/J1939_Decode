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
* Filename      : can_os.c
* Version       : V2.42.00
* Programmer(s) : E0
* Note(s)       : This include file declares all operating system specific symbolic constants.
*                 Per default, this file implements the operating specific functions for µC/OS-III.
****************************************************************************************************
*/

#include "can_os.h"                                   /* CAN OS abstraction layer                 */
#include "can_err.h"                                  /* CAN error codes                          */

/*
****************************************************************************************************
*                                            GOBAL DATA
****************************************************************************************************
*/

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                     CAN BUS SEMAPHORES
* \ingroup  UCCAN
*
*           Allocation of semaphores for the buffering ressources. The following
*           implementation is an implementation for µC/OS-III.
*/
/*------------------------------------------------------------------------------------------------*/
OS_SEM    CANOS_TxSem[CANBUS_N];
OS_SEM    CANOS_RxSem[CANBUS_N];

/*------------------------------------------------------------------------------------------------*/
/*! \brief                              OS INITIALIZATION
*
*            This function shall create and initialize all needed OS objects like semaphores,
*            queues, etc..
*
* \note      This function is a wrapper around the wanted operating system. The following
*            implementation is an implementation for µC/OS-III.
*
* \return    Errorcode CANOS_INIT_ERR if any OS object creation/initialization is failed. If all
*            objects are sucessfully initialized, the return value shall be CANOS_NO_ERR.
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CANOS_Init(void)
{
    CPU_INT08U i;                                     /* Local: loop variable                     */
    CPU_INT16U err;                                   /* Local: Errorcode of OS function          */
                                                      /*------------------------------------------*/
    for (i=0u; i < CANBUS_N; i++) {                   /* loop through all busses                  */
        OSSemCreate (&CANOS_TxSem[i],                 /* Initialize TX counting semaphore         */
                     "CANOS_TxSem",
                     (CANBUS_TX_QSIZE - 1u),
                     &err);

        if (err != OS_ERR_NONE) {                     /* Check result                             */
            can_errnum = CAN_ERR_OSSEM;
            return CAN_ERR_OSSEM;                     /* and leave initialization with errorcode  */
        }
        OSSemCreate (&CANOS_RxSem[i],                 /* Initialize RX counting semaphore         */
                     "CANOS_RxSem",
                     0u,
                     &err);

        if (err != OS_ERR_NONE) {                     /* Check result                             */
            can_errnum = CAN_ERR_OSSEM;
            return CAN_ERR_OSSEM;                     /* and leave initialization with errorcode  */
        }
    }                                                 /*------------------------------------------*/
    return CAN_ERR_NONE;                              /* return function result                   */
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      RESET RX SEMAPHORE
*
*           This function resets the receive semaphore.
*
* \param     busId     identifies CAN bus
*/
/*------------------------------------------------------------------------------------------------*/
void CANOS_ResetRx(CPU_INT16S busId)
{
    CPU_INT16U err;                                   /* Local: Errorcode of OS function          */
                                                      /*------------------------------------------*/
#if CANOS_ARG_CHK_EN > 0
    if ((busId < 0) || ((CPU_INT16U)busId >= CANBUS_N)) { /* is busId out of range?               */
        can_errnum = CAN_ERR_BUSID;
        return;
    }
#endif

    OSSemSet(&CANOS_RxSem[(CPU_INT16U)busId], 0u, &err); /* reset semaphore counter value         */
    if (err != CANOS_NO_ERR) {                        /* see, if no error is detected             */
        can_errnum = CAN_ERR_OSSEM;                   /* set error indication                     */
    }
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      RESET TX SEMAPHORE
*
*           This function resets the transmit semaphore.
*
* \param     busId     identifies CAN bus
*/
/*------------------------------------------------------------------------------------------------*/
void CANOS_ResetTx(CPU_INT16S busId)
{
    CPU_INT16U err;                                   /* Local: Errorcode of OS function          */
                                                      /*------------------------------------------*/
#if CANOS_ARG_CHK_EN > 0
    if ((busId < 0) || ((CPU_INT16U)busId >= CANBUS_N)) { /* is busId out of range?             */
        can_errnum = CAN_ERR_BUSID;
        return;
    }
#endif

    OSSemSet(&CANOS_TxSem[(CPU_INT16U)busId],         /* reset semaphore counter value            */
             CANBUS_TX_QSIZE - 1u,
             &err);
    if (err != CANOS_NO_ERR) {                        /* see, if no error is detected             */
        can_errnum = CAN_ERR_OSSEM;                   /* set error indication                     */
    }
}

/*------------------------------------------------------------------------------------------------*/
/*! \brief                          WAIT FOR CAN FRAME IN RX BUFFER
*
*            This function shall wait for a CAN frame within the CAN receive buffer.
*            If a timeout of 0 ticks is given, this function shall wait forever, otherwise
*            this function shall wait for maximal timeout ticks.
*
* \note      This function is a wrapper around the wanted operating system. The following
*            implementation is an implementation for µC/OS-III.
*
* \param     timeout   Timeout in OS time ticks
* \param     busId     identifies CAN bus
*
* \return    Indication of a received frame:
*            1 = at least one frame is received
*            0 = no frame received until timeout
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT08U CANOS_PendRxFrame(CPU_INT16U timeout, CPU_INT16S busId)
{
    CPU_INT08U result;                                /* Local: Function result                   */
    CPU_INT16U err;                                   /* Local: Errorcode of OS function          */
                                                      /*------------------------------------------*/
#if CANOS_ARG_CHK_EN > 0
    if ((busId < 0) || ((CPU_INT16U)busId >= CANBUS_N)) { /* is busId out of range?               */
        can_errnum = CAN_ERR_BUSID;
        return (0);
    }
#endif

    OSSemPend (&CANOS_RxSem[(CPU_INT16U)busId],       /* Wait for a received frame with timeout   */
               timeout,
               OS_OPT_PEND_BLOCKING,
               (CPU_TS *)0,
               &err);

    if (err == CANOS_NO_ERR) {                        /* see, if no error is detected             */
        result     = 1u;                              /* yes: there a frame in receive buffer     */
    } else {                                          /* otherwise: an error is detected          */
        can_errnum = CAN_ERR_OSSEMPEND;               /* set error indication                     */
        result     = 0u;                              /* no frame in receive buffer               */
    }
    return (result);                                  /* return function result                   */
}

/*------------------------------------------------------------------------------------------------*/
/*! \brief                          SIGNAL A CAN FRAME IN RX BUFFER
*
*            This function shall check for a CAN frame within the CAN receive buffer.
*
* \note      This function is a wrapper around the wanted operating system. The following
*            implementation is an implementation for µC/OS-III.
*
* \param     busId     identifies CAN bus
*/
/*------------------------------------------------------------------------------------------------*/
void CANOS_PostRxFrame(CPU_INT16S busId)
{
    CPU_INT16U err;                                   /* Local: OS error code                     */
                                                      /*------------------------------------------*/
#if CANOS_ARG_CHK_EN > 0
    if ((busId < 0) || ((CPU_INT16U)busId >= CANBUS_N)) {  /* is busId out of range?              */
        can_errnum = CAN_ERR_BUSID;
    }
#endif

    OSSemPost (&CANOS_RxSem[(CPU_INT16U)busId],       /* signal a received frame                  */
               OS_OPT_POST_ALL,
               &err);

    if (err != CAN_ERR_NONE) {                        /* see, if no error is detected             */
        can_errnum = CAN_ERR_OSSEMPOST;               /* set error indication                     */
    }
}

/*------------------------------------------------------------------------------------------------*/
/*! \brief                         ALLOCATE CAN FRAME FOR TRANSMISSION
*
*            This function shall wait for a free space within the transmit buffer.
*            If a timeout of 0 ticks is given, this function shall wait forever, otherwise
*            this function shall wait for maximal timeout ticks.
*
* \note      This function is a wrapper around the wanted operating system. The following
*            implementation is an implementation for µC/OS-III.
*
* \param     timeout   Timeout in OS time ticks
* \param     busId     identifies CAN bus
+
* \return    Indication of transmit buffer status:
*            1 = space for a frame is found
*            0 = no space for a frame until timeout
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT08U CANOS_PendTxFrame(CPU_INT16U timeout, CPU_INT16S busId)
{
    CPU_INT08U result;                                /* Local: Pointer to allocated CAN frame    */
    CPU_INT16U err;                                   /* Local: OS errorcode                      */
                                                      /*------------------------------------------*/
#if CANOS_ARG_CHK_EN > 0
    if ((busId < 0) || ((CPU_INT16U)busId >= CANBUS_N)) { /* is busId out of range?               */
        can_errnum = CAN_ERR_BUSID;
        return (0u);
    }
#endif

    OSSemPend (&CANOS_TxSem[(CPU_INT16U)busId],       /* Get semaphore for memory partition       */
               timeout,
               OS_OPT_PEND_BLOCKING,
               (CPU_TS *)0,
               &err);

    if (err == CANOS_NO_ERR) {                        /* see, if no error is detected             */
        result     = 1u;                              /* yes: space for frame in transmit buffer  */
    } else {                                          /* otherwise: an error is detected          */
        can_errnum = CAN_ERR_OSSEMPEND;               /* set error indication                     */
        result     = 0u;                              /* no free space in transmit buffer         */
    }
    return (result);                                  /* return function result                   */
}

/*------------------------------------------------------------------------------------------------*/
/*! \brief                         RELEASE RESERVATION IN TX BUFFER
*
*            This function shall release a CAN frame reservation within the CAN transmit buffer.
*
* \note      This function is a wrapper around the wanted operating system. The following
*            implementation is an implementation for µC/OS-III.
*
* \param     busId     identifies CAN bus
*/
/*------------------------------------------------------------------------------------------------*/
void CANOS_PostTxFrame(CPU_INT16S busId)
{
    CPU_INT16U err;                                   /* Local: OS error code                     */
                                                      /*------------------------------------------*/
#if CANOS_ARG_CHK_EN > 0
    if ((busId < 0) || ((CPU_INT16U)busId >= CANBUS_N)) { /* is busId out of range?               */
        can_errnum = CAN_ERR_BUSID;
    }
#endif

    OSSemPost (&CANOS_TxSem[(CPU_INT16U)busId],       /* release transmit buffer ressource        */
               OS_OPT_POST_ALL,
               &err);

    if (err != CAN_ERR_NONE) {                        /* see, if no error is detected             */
        can_errnum = CAN_ERR_OSSEMPOST;               /* set error indication                     */
    }
}

/*------------------------------------------------------------------------------------------------*/
/*! \brief                          GET TIME FROM OS
*
*            This function shall receive a time from the underlying OS. The time value will have
*            the resolution and format of the OS.
*
* \note      This function is a wrapper around the wanted operating system. The following
*            implementation is an implementation for µC/OS-III.
*
* \return    32 bit value that represent a time value.
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT32U CANOS_GetTime(void)
{
    CPU_INT16U err;                                   /* Local: OS error code                     */

    return OSTimeGet(&err);
}
