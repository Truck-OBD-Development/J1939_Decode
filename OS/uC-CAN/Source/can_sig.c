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
* Filename      : can_sig.c
* Version       : V2.42.00
* Programmer(s) : E0
* Purpose       : This source file implements the common CAN signal component.
****************************************************************************************************
*/


/*
****************************************************************************************************
*                                             INCLUDES
****************************************************************************************************
*/
#include "can_sig.h"                                  /* CAN signal handling functions            */
#include "can_os.h"                                   /* CAN OS abstraction definitions           */
#include "can_err.h"

#if CANSIG_EN > 0


/*
****************************************************************************************************
*                                            GOBAL DATA
****************************************************************************************************
*/

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                     CAN SIGNALS
* \ingroup  UCCAN
*
*           Constant allocation of can signals.
*/
/*------------------------------------------------------------------------------------------------*/
#if CANSIG_STATIC_CONFIG == 1
extern CANSIG_PARA CanSig[CANSIG_N];
#endif

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                     CAN SIGNAL DATA
* \ingroup  UCCAN
*
*           Allocation of global can signal table
*/
/*------------------------------------------------------------------------------------------------*/
extern CANSIG_DATA CanSigTbl[CANSIG_N];

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                     LIST OF FREE CAN SIGNALS
* \ingroup  UCCAN
*
*           Root Pointer to linked list of free CAN signals.
*/
/*------------------------------------------------------------------------------------------------*/
#if CANSIG_STATIC_CONFIG == 0
static CANSIG_DATA *CanSigFreeLst;

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                     LIST OF USED CAN SIGNALS
* \ingroup  UCCAN
*
*           Root Pointer to linked list of used CAN signals.
*/
/*------------------------------------------------------------------------------------------------*/
static CANSIG_DATA *CanSigUsedLst;
#endif
/*
****************************************************************************************************
*                                            FUNCTIONS
****************************************************************************************************
*/
/*lint --e{717} use of do {} while (0) */

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                     INITIALISE CAN SIGNALS
* \ingroup   UCCAN
*
*            This function will initialize the CAN signal data structures in the following way:
*            all data structures will be linked to the free signal list and the id will be set to
*            the corresponding index in the data list array.
* \note      if a static configuration is selected the CAN signal data structure is initialized
*            once with a constant configuration.
*
* \note      This function has the standard device driver interface, decribed in the porting
*            chapter of the user manual. This allows the CAN bus handling via the standard
*            device driver interface.
*
* \param     arg           not used
*
* \return    CAN_OK.
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanSigInit(CPU_INT32U arg)
{
#if CANSIG_STATIC_CONFIG == 0
    CANSIG_DATA *sig1   = &CanSigTbl[0];              /* Local: pointer to signal #1              */
    CANSIG_DATA *sig2   = &CanSigTbl[1];              /* Local: pointer to signal #2              */
    CPU_INT16U   i;                                   /* Local: loop variable                     */
                                                      /*------------------------------------------*/
    (void)arg;                                        /* unused; prevent compiler warning         */
    for (i=0; i<CANSIG_N; i++ ) {                     /* loop through all CAN signals in list     */
        sig1->Id     = i;                             /* set id of signal #1                      */
        sig1->Status = CANSIG_UNUSED;                 /* set status of signal #1 to 'unused'      */
        sig1->Value  = 0;                             /* clear value                              */
        sig1->Cfg    = NULL_PTR;                      /* clear pointer to signal configuration    */

        if(i < (CANSIG_N - 1)) {                      /* see, if signal #2 is in range            */
            sig1->Next = sig2;                        /* link signal #2 to signal #1              */
        } else {                                      /* otherwise: signal #2 out of range        */
            sig1->Next = NULL_PTR;                    /* mark end of linked signal list           */
        }
        sig1++;                                       /* switch signal #1 to next signal          */
        sig2++;                                       /* switch signal #2 to next signal          */
    }
    CanSigFreeLst = CanSigTbl;                        /* set free list pointer to complete list   */
    CanSigUsedLst = NULL_PTR;                         /* set used list pointer to empty list      */

#else
    CPU_INT32U   i;                                   /* Local: loop variable                     */
                                                      /*------------------------------------------*/
    (void)arg;                                        /* unused; prevent compiler warning         */
    for (i=0u; i<CANSIG_N; i++ ) {                    /* loop through all CAN signals in list     */
        CanSigTbl[i].Cfg    = &CanSig[i];             /* copy signal configuration             */
        CanSigTbl[i].Value  = CanSig[i].Value;        /* set initial value                        */
        CanSigTbl[i].Status = CANSIG_UNCHANGED;       /* set status of signal to 'unused'         */
    }
#endif
    return CAN_ERR_NONE;
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                     SIGNAL I/O CONTROL
* \ingroup   UCCAN
*
*            This function performs a special action on the opened device. The functioncode
*            defines what the caller want to do. The following functioncodes are allowed:
*
*            - CANSIG_GET_WIDTH:          Get the argument pointer width (CPU_INT08U *) and
*                                         set the content to the signal width.
*
*            - CANSIG_GET_STATUS:         Get the argument pointer status (CPU_INT08U *) and
*                                         set the content to the signal status.
*
* \param     sigId         Unique signal identifier
*
* \param     func          The functioncode
*
* \param     argp          Pointer to argument, specific to the function code
*
* \return    CAN_ERROR, if an error is detected, otherwise CAN_OK for successful deletion.
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanSigIoCtl(CPU_INT16S sigId, CPU_INT16U func, void *argp)
{
    CPU_INT16S   result;                              /* Local: Function result                   */
    CANSIG_DATA *sig;                                 /* Local: Pointer to signal                 */
    CPU_SR_ALLOC();                                   /* LocaL: Storage for CPU status register   */
                                                      /*------------------------------------------*/

#if CANSIG_ARG_CHK_EN > 0

    if ((sigId < 0) || ((CPU_INT16U)sigId >= CANSIG_N)) {  /* is sigId out of range?              */
        can_errnum = CAN_ERR_SIGID;
        return CAN_ERR_SIGID;
    }
    if (argp == NULL_PTR) {                           /* is argument pointer valid?               */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
#endif /* CANSIG_ARG_CHK_EN > 0 */

    result = CAN_ERR_NONE;                            /* indicate successful operation            */
    CPU_CRITICAL_ENTER();                             /* disable interrupts                       */
    sig = &CanSigTbl[sigId];                          /* set pointer to addressed signal          */

    switch (func) {                                   /* Perform actions acc. functioncode:       */
                                                      /*------------------------------------------*/
        case CANSIG_GET_WIDTH:                        /* Get signal width                         */
                                                      /*------------------------------------------*/
            if (sig->Cfg != NULL_PTR) {               /* see, if signal is created                */
                *((CPU_INT08U *)argp) =               /* Set width to configured width            */
                     sig->Cfg->Width;
            }
            else {
                result = CAN_ERR_NULLSIGCFG;
            }
            break;
                                                      /*------------------------------------------*/
        case CANSIG_GET_STATUS:                       /* Get signal status                        */
                                                      /*------------------------------------------*/
            *((CPU_INT08U *)argp) = sig->Status;      /* Set status to current signal status      */
            break;
#if CANSIG_STATIC_CONFIG == 0
                                                      /*------------------------------------------*/
        case CANSIG_GET_TIMESTAMP:                    /* Get signal timestamp                     */
                                                      /*------------------------------------------*/
            *((CPU_INT32U *)argp) = sig->TimeStamp;   /* Set timestamp to current signal timestamp */
            break;
                                                      /*------------------------------------------*/
        case CANSIG_GET_TIME_SINCE_UPDATE:            /* Get time since last update               */
                                                      /*------------------------------------------*/
            *((CPU_INT32U *)argp) = CANOS_GetTime() -
                                    sig->TimeStamp;
            break;
                                                      /*------------------------------------------*/
        case CANSIG_DISABLE_TIMESTAMP:                /* Disable Timestamp                        */
                                                      /*------------------------------------------*/
            sig->Status |= CANSIG_NO_TIMESTAMP;
            break;
                                                      /*------------------------------------------*/
        case CANSIG_ENABLE_TIMESTAMP:                 /* Enable Timestamp                         */
                                                      /*------------------------------------------*/
            sig->Status &= (CPU_INT08U) ~CANSIG_NO_TIMESTAMP;
            break;
                                                      /*------------------------------------------*/
        case CANSIG_SET_TIMESTAMP:                    /* Set Timestamp                            */
                                                      /*------------------------------------------*/
            sig->TimeStamp = *((CPU_INT32U *)argp);
            break;
#endif
                                                      /*------------------------------------------*/
        case CANSIG_SET_WRITE_PROTECTION:             /* Set write protection                     */
                                                      /*------------------------------------------*/
            if ((*(CPU_INT08U*)argp) == CANSIG_PROT_RO) {
                sig->Status |= CANSIG_PROT_RO;
            } else {
                sig->Status &= (CPU_INT08U) ~CANSIG_PROT_RO;
            }
            break;
                                                      /*------------------------------------------*/
        case CANSIG_GET_WRITE_PROTECTION:             /* Get Write protection                     */
                                                      /*------------------------------------------*/
            *((CPU_INT08U *)argp) =
                (sig->Status & CANSIG_PROT_RO);
            break;
                                                      /*------------------------------------------*/
        default:                                      /* Unsupported function code                */
                                                      /*------------------------------------------*/
            result = CAN_ERR_IOCTRLFUNC;
            break;                                    /* don't set result value to no error       */
    }                                                 /*------------------------------------------*/
    CPU_CRITICAL_EXIT();                              /* allow interrupts                         */

    CANSetErrRegister(result);
    return (result);                                  /* return function result                   */
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                     WRITE CAN SIGNAL
* \ingroup   UCCAN
*
*            Updates a CAN signal after checking, that this signal is in use.
*
* \param     sigId         unique signal identifier
*
* \param     buffer        Pointer to value
*
* \param     size          Size of CAN signal
*
* \return    CAN_ERROR, if an error is detected, otherwise it returns 1,2 or 4.
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanSigWrite(CPU_INT16S sigId, void *buffer, CPU_INT16U size)
{
    CANSIG_DATA *sig;                                 /* Local: Pointer to can signal             */
    CANSIG_VAL_T value;                               /* Local: the signal value                  */
    CPU_SR_ALLOC();                                   /* LocaL: Storage for CPU status register   */
                                                      /*------------------------------------------*/

#if CANSIG_ARG_CHK_EN > 0

    if ((sigId < 0) || ((CPU_INT16U)sigId >= CANSIG_N)) { /* is sigId out of range?               */
        can_errnum = CAN_ERR_SIGID;
        return CAN_ERR_SIGID;
    }
    if (CanSigTbl[sigId].Cfg == NULL_PTR) {           /* is signal not created?                   */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
    if (buffer == NULL_PTR) {                         /* is buffer an invalid pointer?            */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
#endif /* CANSIG_ARG_CHK_EN > 0 */

    CPU_CRITICAL_ENTER();                             /* disable interrupts                       */
    sig = &CanSigTbl[sigId];                          /* Set pointer to addressed can signal      */
    if ((sig->Status & CANSIG_PROT_RO) == 0u) {       /* check if write protection is enabled     */
                                                      /*------------------------------------------*/

        switch (size) {                               /* is size valid?                       */
            case 1:                                   /* check for byte access                */
                value  = (CANSIG_VAL_T)               /* get a byte in local value            */
                         (*(CPU_INT08U*)buffer);
                break;

            case 2:                                   /* otherwise check for word access      */
                value  = (CANSIG_VAL_T)               /* get a word in local value            */
                         (*(CPU_INT16U*)buffer);
                break;

            case 4:                                   /* otherwise long access                */
                value  = (CANSIG_VAL_T)               /* get a long in local value            */
                         (*(CPU_INT32U*)buffer);
                break;

            default:
                can_errnum = CAN_ERR_CANSIZE;
                CPU_CRITICAL_EXIT();                  /* allow interrupts                    */
                return CAN_ERR_CANSIZE;               /* No, return error                    */
        }                                             /*------------------------------------------*/
        sig->Status &= CANSIG_CLR_STATUS;             /* clear status bits                        */
        sig->Status |= CANSIG_UPDATED;                /* mark signal as updated                   */
#if CANSIG_STATIC_CONFIG == 0
        if ((sig->Status &                            /* check if timestamping is enabled         */
            CANSIG_NO_TIMESTAMP) == 0) {
            sig->TimeStamp = CANOS_GetTime();         /* set timestamp of signal                  */
        }
#endif                                                /*------------------------------------------*/
        if (value != sig->Value) {                    /* check, that signal value has changed     */
#if CANSIG_CALLBACK_EN > 0
            if(sig->Cfg->CallbackFct != NULL_PTR) {   /* see, if a callback function is defined   */
                sig->Cfg->CallbackFct((void*)sig,     /* call the callback function                */
                                      &value,
                                      CANSIG_CALLBACK_WRITE_ID);
            }
#endif /* CANSIG_CALLBACK_EN > 0 */
                                                      /* store new value in signal                */
            sig->Value  = value;
            sig->Status &= CANSIG_CLR_STATUS;         /* clear status bits                        */
            sig->Status |= CANSIG_CHANGED;            /* mark signal as changed                   */
        }                                             /*------------------------------------------*/
    }
    CPU_CRITICAL_EXIT();                              /* allow interrupts                         */


    return (CPU_INT16S)size;                          /* return function result                   */
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                     READ CAN SIGNAL
* \ingroup   UCCAN
*
*            Reads a CAN signal after checking, that this signal is in use.
*
* \param     sigId         unique signal identifier
*
* \param     buffer        Pointer to value
*
* \param     size          Size of buffer in bytes
*
* \return    CAN_ERROR, if an error is detected, otherwise it returns 1,2 or 4.
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanSigRead(CPU_INT16S sigId, void *buffer, CPU_INT16U size)
{
    CANSIG_VAL_T value;                               /* Local: signal value                      */
    CANSIG_DATA *sig;                                 /* Local: pointer to can signal             */
    CPU_SR_ALLOC();                                   /* LocaL: Storage for CPU status register   */
                                                      /*------------------------------------------*/

#if CANSIG_ARG_CHK_EN > 0

    if ((sigId < 0) || ((CPU_INT16U)sigId >= CANSIG_N)) { /* is sigId out of range?               */
        can_errnum = CAN_ERR_SIGID;
        return CAN_ERR_SIGID;
    }
    if (CanSigTbl[sigId].Cfg == NULL_PTR) {           /* is signal not created?                   */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
    if (buffer == NULL_PTR) {                         /* is buffer an invalid pointer?            */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }

    switch (size) {                                   /* is size valid?                           */
        case 1:
        case 2:
        case 4:
            break;
        default:
            can_errnum = CAN_ERR_CANSIZE;
            return CAN_ERR_CANSIZE;                    /* No, return error                        */
    }
#endif /* CANSIG_ARG_CHK_EN > 0 */

    sig = &CanSigTbl[sigId];                          /* Set pointer to addressed can signal      */
                                                      /*------------------------------------------*/
#if CANSIG_CALLBACK_EN > 0
    if(sig->Cfg->CallbackFct != NULL_PTR) {           /* see, if a callback function is defined   */
        sig->Cfg->CallbackFct((void*)sig,             /* call the callback function               */
                              NULL_PTR,
                              CANSIG_CALLBACK_READ_ID);
    }
#endif /* CANSIG_CALLBACK_EN > 0 */
    CPU_CRITICAL_ENTER();                             /* disable interrupts                       */
    value       = sig->Value;                         /* Get signal value                         */

    sig->Status &= CANSIG_CLR_STATUS;                 /* clear status bits                        */
    sig->Status |= CANSIG_UNCHANGED;                  /* mark signal as 'unchanged'               */
    CPU_CRITICAL_EXIT();                              /* enable interrupts                        */
                                                      /*------------------------------------------*/
    if (size == 1u) {                                 /* check for byte access                    */
        *(CPU_INT08U*)buffer = (CPU_INT08U)value;     /* write a byte to given buffer             */
    } else if (size == 2u) {                          /* otherwise check for word access          */
        *(CPU_INT16U*)buffer = (CPU_INT16U)value;     /* write a word to given buffer             */
    } else {                                          /* otherwise long access                    */
        *(CPU_INT32U*)buffer = (CPU_INT32U)value;     /* write a long to given buffer             */
    }                                                 /*------------------------------------------*/

    return (CPU_INT16S)size;                          /* return size as result                    */
}


#if CANSIG_STATIC_CONFIG == 0
/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                     CREATE CAN SIGNAL
* \ingroup   UCCAN
*
*            This function checks, if a free CAN signal is available. If yes, this signal is
*            set in front of the used list and initialized with the configured signal data.
*
* \param     cfg           Configuration of CAN signal
*
* \return    The signal identifier or an errorcode: CAN_ERROR
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanSigCreate(CANSIG_PARA *cfg)
{
    CPU_INT16S   result = CAN_ERR_SIGCREATE;          /* Local: function result                   */
    CANSIG_DATA *sig;                                 /* Local: Pointer to signal                 */
    CPU_SR_ALLOC();                                   /* LocaL: Storage for CPU status register   */
                                                      /*------------------------------------------*/

#if CANSIG_ARG_CHK_EN > 0
    if (cfg == NULL_PTR) {                            /* is cfg a valid pointer?                  */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
#endif /* CANSIG_ARG_CHK_EN > 0 */

    CPU_CRITICAL_ENTER();                             /* disable interrupts                       */
    if (CanSigFreeLst != NULL_PTR) {                  /* see, if a free signal is available       */
        sig           = CanSigFreeLst;                /* yes: get first element from free list    */
        CanSigFreeLst = sig->Next;                    /* set free list root to next element       */
                                                      /*------------------------------------------*/
        sig->Cfg      = cfg;                          /* link configuration to this element       */
        sig->Status   = cfg->Status;                  /* copy initial status from config          */
        sig->Value    = cfg->Value;                   /* copy initial value from config           */
                                                      /*------------------------------------------*/
        sig->Next     = CanSigUsedLst;                /* put element in front of used list        */
        CanSigUsedLst = sig;                          /* set used list to new first element       */
                                                      /*------------------------------------------*/
        result        = (CPU_INT16S)sig->Id;          /* return id of created signal              */
    }                                                 /*------------------------------------------*/
    CPU_CRITICAL_EXIT();                              /* enable interrupts                        */

    CANSetErrRegister(result);
    return result;                                    /* Return function result                   */
}
#endif

#if (CANSIG_STATIC_CONFIG == 0) && (CANSIG_USE_DELETE == 1)
/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                     DELETE CAN SIGNAL
* \ingroup   UCCAN
*
*            This function checks, if a CAN signal is in use. If yes, the CAN signal will be
*            removed from the used list and put back to the free list.
*
* \param     sigId         Signal identifier
*
* \return    CAN_ERROR, if an error is detected, otherwise CAN_ERR_NONE for successful deletion.
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanSigDelete(CPU_INT16S sigId)
{
    CANSIG_DATA *sig;                                 /* Local: pointer to signal data            */
    CANSIG_DATA *previous;                            /* Local: pointer to previous used signal   */
    CPU_SR_ALLOC();                                   /* LocaL: Storage for CPU status register   */
                                                      /*------------------------------------------*/

#if CANSIG_ARG_CHK_EN > 0

    if ((sigId < 0) || ((CPU_INT16U)sigId >= CANSIG_N)) { /* is sigId out of range?               */
        can_errnum = CAN_ERR_SIGID;
        return CAN_ERR_SIGID;
    }
    if (CanSigTbl[sigId].Cfg == NULL_PTR) {           /* is signal not created?                   */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
#endif /* CANSIG_ARG_CHK_EN > 0 */

    CPU_CRITICAL_ENTER();                             /* disable interrupts                       */
    sig = &CanSigTbl[sigId];                          /* set pointer to signal data               */
    sig->Status = CANSIG_UNUSED;                      /* mark signal as 'unused'                  */
    sig->Cfg    = NULL_PTR;                           /* remove link to signal parameter          */
                                                      /*------------------------------------------*/
    if (CanSigUsedLst == sig) {                       /* see, if signal is root of used list      */
        CanSigUsedLst = sig->Next;                    /* update root to next element in used list */
    } else {                                          /* otherwise: signal is within the list     */
        previous = CanSigUsedLst;                     /* set previous signal pointer to list root */
        while (previous->Next != sig) {               /* go through list until previous pointer   */
            previous = previous->Next;                /*   is in front of signal pointer          */
        }
    }
    previous->Next = sig->Next;                       /* remove signal out of list                */
    sig->Next     = CanSigFreeLst;                    /* Link signal data in front of free list   */
    CanSigFreeLst = sig;                              /* Update root pointer of free list         */
    CPU_CRITICAL_EXIT();                              /* enable interrupts                        */
                                                      /*------------------------------------------*/

    return CAN_ERR_NONE;                              /* return successful function result        */
}
#endif

#endif  /* CANSIG_EN > 0 */

