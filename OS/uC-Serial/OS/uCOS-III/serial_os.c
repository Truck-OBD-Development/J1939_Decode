/*
*********************************************************************************************************
*                                     SERIAL (BYTE) COMMUNICATION
*
*                         (c) Copyright 2007-2009; Micrium, Inc.; Weston, FL
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
*
*                                       OPERATING SYSTEM LAYER
*                                          Micrium uC/OS-III
*
* Filename      : serial_os.c
* Version       : V2.00.01
* Programmer(s) : FGK
*                 FT
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <serial.h>
#include  <serial_os.h>
#include  <os.h>

/*
*********************************************************************************************************
*                                              DEFINES
*********************************************************************************************************
*/

#define  SERIAL_OS_MAX_NBR_SEM                  ((4u + SERIAL_CFG_TX_DESC_NBR) * SERIAL_CFG_MAX_NBR_IF)


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  MEM_POOL  OS_SemPool;


/*$PAGE*/
/*
*********************************************************************************************************
*                                           SerialOS_Init()
*
* Description : Initialize OS layer.
*
* Argument(s) : perr        Pointer to variable that will receive the return error code from this function :
*
*                               SERIAL_OS_ERR_NONE          Initialization of OS layer successful.
*                               SERIAL_OS_ERR_INIT          Initialization of OS layer failed.
*
* Return(s)   : None.
*
* Caller(s)   : Serial_Init().
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  SerialOS_Init (SERIAL_ERR  *perr)
{
    LIB_ERR     lib_err;
    CPU_SIZE_T  octects_reqd;


    Mem_PoolCreate((MEM_POOL    *)&OS_SemPool,
                   (void        *) 0,
                   (CPU_SIZE_T   ) 0u,
                   (CPU_SIZE_T   ) SERIAL_OS_MAX_NBR_SEM,
                   (CPU_SIZE_T   ) sizeof(OS_SEM),
                   (CPU_SIZE_T   ) 1u,
                   (CPU_SIZE_T  *)&octects_reqd,
                   (LIB_ERR     *)&lib_err);

    if (lib_err != LIB_MEM_ERR_NONE) {
       *perr = SERIAL_OS_ERR_INIT;
        return;
    }

   *perr = SERIAL_OS_ERR_NONE;
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                        SerialOS_SemCreate()
*
* Description : Create a semaphore.
*
* Argument(s) : cnt         Initial value for the semaphore.
*
* Return(s)   : Pointer to semaphore, if NO errors.
*               Pointer to NULL,      otherwise.
*
* Caller(s)   : Serial_Wr().
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  *SerialOS_SemCreate (CPU_INT16U  cnt)
{
    OS_SEM   *psem;
    LIB_ERR   lib_err;
    OS_ERR    os_err;


    psem = (OS_SEM *)Mem_PoolBlkGet((MEM_POOL    *)&OS_SemPool,
                                    (CPU_SIZE_T   ) sizeof(OS_SEM),
                                    (LIB_ERR     *)&lib_err);

    if (lib_err != LIB_MEM_ERR_NONE) {
        return ((void *)0);
    }

    OSSemCreate((OS_SEM      *)psem,
                (CPU_CHAR    *)0,
                (OS_SEM_CTR   )cnt,
                (OS_ERR      *)&os_err);

    if (os_err != OS_ERR_NONE) {
        Mem_PoolBlkFree((MEM_POOL  *)&OS_SemPool,
                        (void      *) psem,
                        (LIB_ERR   *)&lib_err);
        return ((void *)0);
    }

    return ((void *)psem);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                          SerialOS_SemDel()
*
* Description : Delete a semaphore.
*
* Argument(s) : psem        Pointer to semaphore to delete.
*
* Return(s)   : None.
*
* Caller(s)   : Serial_WrCallback().
*
* Note(s)     : (1) Always delete the semaphore even if tasks are pending on it.
*
*               (2) MUST NOT be called within a critical section.
*********************************************************************************************************
*/

void  SerialOS_SemDel (void  *psem)
{
    LIB_ERR  lib_err;
    OS_ERR   os_err;


    OSSemPendAbort((OS_SEM  *)psem,
                   (OS_OPT   )OS_OPT_PEND_ABORT_ALL,
                   (OS_ERR  *)&os_err);

    OSSemDel((OS_SEM  *)psem,
             (OS_OPT   )OS_OPT_DEL_ALWAYS,
             (OS_ERR  *)&os_err);

    Mem_PoolBlkFree((MEM_POOL  *)&OS_SemPool,
                    (void      *) psem,
                    (LIB_ERR   *)&lib_err);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                         SerialOS_SemWait()
*
* Description : Wait for a semaphore to become available.
*
* Argument(s) : psem        Pointer to semaphore to wait.
*
*               timeout_ms  Optional timeout period in milliseconds. If specified 0, wait indefinitely.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               SERIAL_OS_ERR_NONE              The wait on semaphore was successful.
*                               SERIAL_OS_ERR_TIMEOUT           Semaphore not recv'd within specified 'timeout'.
*                               SERIAL_OS_ERR_SIGNAL            Waiting on semaphore could not be performed.
*
* Return(s)   : None.
*
* Caller(s)   : Serial_Wr().
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  SerialOS_SemWait (void        *psem,
                        CPU_INT32U   timeout_ms,
                        SERIAL_ERR  *perr)
{
    OS_TICK  ticks;
    OS_ERR   os_err;


    ticks = (timeout_ms * OSCfg_TickRate_Hz + (DEF_TIME_NBR_mS_PER_SEC - 1u)) / DEF_TIME_NBR_mS_PER_SEC;

    (void)OSSemPend((OS_SEM   *) psem,
                    (OS_TICK   ) ticks,
                    (OS_OPT    ) OS_OPT_PEND_BLOCKING,
                    (CPU_TS   *) 0,
                    (OS_ERR   *)&os_err);

    switch (os_err) {
        case OS_ERR_NONE:
            *perr = SERIAL_OS_ERR_NONE;
             break;

        case OS_ERR_TIMEOUT:
            *perr = SERIAL_OS_ERR_TIMEOUT;
             break;

        default:
            *perr = SERIAL_OS_ERR_SIGNAL;
             break;
    }
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                        SerialOS_SemTryLock()
*
* Description : Try to acquire semaphore if available.
*
* Argument(s) : psem        Pointer to semaphore to acquire.
*
* Return(s)   : DEF_OK,   if semaphore acquired.
*               DEF_FAIL, otherwise.
*
* Caller(s)   : Serial_WrAsync().
*
* Note(s)     : None.
*********************************************************************************************************
*/

CPU_BOOLEAN  SerialOS_SemTryLock (void  *psem)
{
    OS_ERR  os_err;


    (void)OSSemPend((OS_SEM   *) psem,
                    (OS_TICK   ) 0u,
                    (OS_OPT    ) OS_OPT_PEND_NON_BLOCKING,
                    (CPU_TS   *) 0,
                    (OS_ERR   *)&os_err);

    if (os_err != OS_ERR_NONE) {
        return (DEF_FAIL);
    }

    return (DEF_OK);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                        SerialOS_SemSignal()
*
* Description : Signal a semaphore.
*
* Argument(s) : psem        Pointer to semaphore to signal.
*
* Return(s)   : DEF_OK,   if semaphore signaled.
*               DEF_FAIL, otherwise.
*
* Caller(s)   : Serial_WrCallback().
*
* Note(s)     : None.
*********************************************************************************************************
*/

CPU_BOOLEAN  SerialOS_SemSignal (void  *psem)
{
    OS_ERR  os_err;


    (void)OSSemPost((OS_SEM  *)psem,
                    (OS_OPT   )OS_OPT_POST_1,
                    (OS_ERR  *)&os_err);

    if (os_err != OS_ERR_NONE) {
        return (DEF_FAIL);
    }

    return (DEF_OK);
}
