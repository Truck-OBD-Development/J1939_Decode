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
* Filename      : can_msg.c
* Version       : V2.42.00
* Programmer(s) : E0
* Purpose       : This source file implements the common CAN message component.
****************************************************************************************************
*/

/*
****************************************************************************************************
*                                             INCLUDES
****************************************************************************************************
*/
#include "can_msg.h"                                  /* CAN message handling functions           */
#include "can_frm.h"                                  /* CAN frame handling functions             */
#include "can_sig.h"                                  /* CAN signal handling functions            */
#include "can_err.h"                                  /* CAN error codes                          */


/*
****************************************************************************************************
*                                            GOBAL DATA
****************************************************************************************************
*/

#if CANMSG_EN > 0
/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      CAN MESSAGE DATA
*
*           Allocation of global can message table
*/
/*------------------------------------------------------------------------------------------------*/
static CANMSG_DATA CanMsgTbl[CANMSG_N] = {0u};


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      LIST OF FREE CAN MESSAGES
*
*           Root Pointer to linked list of free CAN messages.
*/
/*------------------------------------------------------------------------------------------------*/
static CANMSG_DATA *CanMsgFreeLst;


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      LIST OF USED CAN MESSAGES
*
*           Root Pointer to linked list of used CAN messages.
*/
/*------------------------------------------------------------------------------------------------*/
static CANMSG_DATA *CanMsgUsedLst;


/*
****************************************************************************************************
*                                            FUNCTIONS
****************************************************************************************************
*/
/*lint --e{717} use of do {} while (0) */
/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      INITIALISE CAN MESSAGES
*
*           This function will initialize the CAN message data structure in the following
*           way: all data structures will be linked together and the id will be set to
*           the corresponding index in the data list array.
*
* \note     This function has the standard device driver interface, decribed in the porting
*           chapter of the user manual. This allows the CAN message handling via the standard
*           device driver interface.
*
* \param    arg               Not used
*
* \return   Errorcode -1, if an error is detected, otherwise 0 for successful initialization.
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanMsgInit(CPU_INT32U arg)
{
    CANMSG_DATA *msg    = &CanMsgTbl[0];              /* Local: pointer to message                */
    CPU_INT16U   i;                                   /* Local: loop variable                     */
                                                      /*------------------------------------------*/
    (void)arg;                                        /* unused; prevent compiler warning         */
    for (i=0u; i<CANMSG_N; i++) {                     /* loop through all CAN messages in list    */
        msg->Id  = i;                                 /* set id of message                        */
        msg->Cfg = NULL_PTR;                          /* clear pointer to message configuration   */

        if ((i+1u) < CANMSG_N) {                      /* see, if next message is in range         */
                                                      /* link next message to actual message      */
            msg->Next = &CanMsgTbl[i+1u];
        } else {                                      /* otherwise next message is out of range   */
            msg->Next = NULL_PTR;                     /* mark end of linked message list          */
            break;
        }
        msg++;                                        /*lint !e960 switch message to next message */
    }
    CanMsgFreeLst = CanMsgTbl;                        /* set free list pointer to complete list   */
    CanMsgUsedLst = NULL_PTR;                         /* set used list pointer to empty list      */

    return CAN_ERR_NONE;
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      OPEN A CAN MESSAGE
*
*           Searches the CAN message with the given CAN identifier in the used list and
*           returns the unique message identifier.
*
* \param    drvId             unused
*
* \param    devName           The message identifier
*
* \param    mode              unused
*
* \return   The message identifier for further access or -1 if an error occurs.
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanMsgOpen(CPU_INT16S drvId, CPU_INT32U devName, CPU_INT16U mode)
{
    CPU_INT16S   result = CAN_ERR_NULLMSG;            /* Local: Function result                   */
    CANMSG_DATA *msg;                                 /* Local: Pointer to CAN message            */
                                                      /*------------------------------------------*/
    (void)drvId;                                      /* unused; prevent compiler warning         */
    (void)mode;                                       /* unused; prevent compiler warning         */

    msg = CanMsgUsedLst;                              /* set can message pointer                  */
    while (msg != NULL_PTR) {                         /*   identifier is found or end reached     */
        if (msg->Cfg->Identifier == devName) {        /* see, if identifier is equal to devname   */
            result = (CPU_INT16S)msg->Id;             /* indicate, that configuration is found    */
            break;
        }                                             /* otherwise, identifier is not correct     */
        msg = msg->Next;                              /* set config pointer to next configuration */
    }

    CANSetErrRegister(result);
    return result;                                    /* Return function result (paraId)          */
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      MESSAGE I/O CONTROL
*
*           This function allows to control special features of a CAN message.
*
* \param    msgId             Unique message identifier
*
* \param    func              Functioncode
*
* \param    argp              Pointer to argument, specific to the function code
*
* \return   Errorcode: 0 on success, -1 on error
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanMsgIoCtl(CPU_INT16S msgId, CPU_INT16U func, void *argp)
{
    CPU_INT16S   result = CAN_ERR_IOCTRLFUNC;         /* Local: Function result                   */
    CANMSG_PARA *cfg;                                 /* Local: Pointer to CAN message config     */
    CANMSG_DATA *msg;                                 /* Local: Pointer to CAN message            */
    CANMSG_LINK *lnk;                                 /* Local: Pointer to CAN signal link        */
    CPU_INT08U   status;                              /* Local: Status of CAN signal              */
    CPU_INT08U   len;                                 /* Local: Number of linked signals          */
    CPU_BOOLEAN  sumStatus;                           /* Local: Summarized CAN signal status      */
    CPU_INT32U   i;                                   /* Local: loop variable                     */
                                                      /*------------------------------------------*/

#if CANMSG_ARG_CHK_EN > 0

    if ((msgId < 0) || ((CPU_INT16U)msgId >= CANMSG_N)) { /* is msgId out of range?               */
        can_errnum = CAN_ERR_MSGID;
        return CAN_ERR_MSGID;
    }
    if (CanMsgTbl[msgId].Cfg == NULL_PTR) {           /* is message created?                      */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
    if (argp == NULL_PTR) {                           /* is argument pointer invalid?             */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
#endif /* CANMSG_ARG_CHK_EN > 0 */

    msg = &CanMsgTbl[msgId];                          /* set can message pointer                  */
    cfg = msg->Cfg;                                   /* set can message config pointer           */

    switch (func) {                                   /* Select function with functioncode        */
                                                      /*------------------------------------------*/
        case CANMSG_IS_CHANGED:                       /*           CHECK FOR CHANGE               */
                                                      /*------------------------------------------*/
            sumStatus = CAN_FALSE;                    /* reset flag to 'unchanged'                */
            status    =  CANSIG_UNUSED;               /* set status to unused                     */
            lnk       = &cfg->SigLst[0];              /* set can link pointer to first link       */
            len       =  cfg->SigNum;                 /* get length of link list                  */
            for (i=0u; i<len; i++) {                  /* until last used signal link reached:     */
                result = CanSigIoCtl((CPU_INT16S)lnk->Id,/* get configured signal status with     */
                        (CPU_INT16U)CANSIG_GET_STATUS,/*   functioncode for getting status        */
                        (void*)&status);
                CANSetErrRegister(result);
                                                      /* see, if signal was changed               */
                if (status == CANSIG_CHANGED) {
                    sumStatus = CAN_TRUE;             /* indicate, that message is changed        */
                    break;                            /* break loop, because message is changed   */
                }
                lnk++;                                /*lint !e960 set pointer to next signal link*/
            }
            *((CPU_BOOLEAN *)argp) = sumStatus;       /* indicate, that message is changed        */
            result = CAN_ERR_NONE;                    /* okay, status calculated                  */
            break;
                                                      /*------------------------------------------*/
        default:                                      /*          UNUSED FUNCTION CODE            */
                                                      /*------------------------------------------*/
            break;                                    /* don't set result to success              */
    }                                                 /*------------------------------------------*/

    CANSetErrRegister(result);
    return (result);                                  /* return function result                   */
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      CAN MESSAGE READ
*
*           This function constructs a CAN frame out of the linked signals. If there are
*           no linked signals (or the signals are not in use), the corresponding bytes
*           will be 0.
*
* \param    msgId             Unique message identifier
*
* \param    buffer            Pointer to CAN frame of type CANFRM
*
* \param    size              Size of buffer (must be equal to sizeof(CANFRM))
*
* \return   Number of bytes in CAN frame or -1 if an error was detected
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanMsgRead(CPU_INT16S msgId, void *buffer, CPU_INT16U size)
{
    CPU_INT16S   result;                              /* Local: function result (signal counter)  */
    CANSIG_VAL_T value  = 0u;                         /* Local: signal value (up to 32 bits)      */
    CANFRM      *frm    = (CANFRM *)buffer;           /* Local: constructed CAN frame             */
    CANMSG_PARA *cfg;                                 /* Local: Pointer to CAN message config     */
    CANMSG_DATA *msg;                                 /* Local: Pointer to CAN message            */
    CANMSG_LINK *lnk;                                 /* Local: Pointer to CAN signal link        */
    CPU_INT08U   width  = 0u;                         /* Local: bit width of signal               */
    CPU_INT32U   i;                                   /* Local: loop variable                     */
    CPU_SR_ALLOC();                                   /* LocaL: Storage for CPU status register   */
                                                      /*------------------------------------------*/

#if CANMSG_ARG_CHK_EN > 0

    if ((msgId < 0) || ((CPU_INT16U)msgId >= CANMSG_N)) { /* is msgId out of range?               */
        can_errnum = CAN_ERR_MSGID;
        return CAN_ERR_MSGID;
    }
    if (CanMsgTbl[msgId].Cfg == NULL_PTR) {           /* is message not created?                  */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
    if (size != sizeof(CANFRM)) {                     /* is size equal sizeof(CANFRM)?            */
        can_errnum = CAN_ERR_FRMSIZE;
        return CAN_ERR_FRMSIZE;
    }
    if (buffer == NULL_PTR) {                         /* is buffer an invalid pointer?            */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
#endif /* CANMSG_ARG_CHK_EN > 0 */

    CPU_CRITICAL_ENTER();                             /* disable interrupts                       */
    msg = &CanMsgTbl[msgId];                          /* set can message pointer                  */
    cfg = msg->Cfg;                                   /* set can message config pointer           */
    frm->Identifier = cfg->Identifier;                /* set message identifier as configured     */
    frm->DLC = cfg->DLC;                              /* set message DLC as configured            */
    for (i=0u; i<8u; i++) {                           /* reset all data bytes to 0                */
        frm->Data[i] = 0u;
    }
                                                      /*------------------------------------------*/
    lnk = &cfg->SigLst[0];                            /* set can link pointer to first link       */
    for (i=0u; i<cfg->SigNum; i++) {                  /* until last used signal link reached:     */
        result = CanSigIoCtl((CPU_INT16S)lnk->Id,     /* get configured signal width with         */
                    (CPU_INT16U)CANSIG_GET_WIDTH,     /*   functioncode for getting width         */
                    (void*)&width);                   /*   pointer to result variable             */
        CANSetErrRegister(result);

        result = CanSigRead((CPU_INT16S)lnk->Id,      /* read signal value with                   */
                   (void *)&value,                    /*   pointer to value                       */
                   CANSIG_MAX_WIDTH);                 /*   with needed number of bytes            */
        CANSetErrRegister(result);
                                                      /* build frame can signal datas             */

        CanFrmSet(frm, value, width, lnk->Pos);
        lnk++;                                        /*lint !e960 set pointer to next signal link*/
    }
    CPU_CRITICAL_EXIT();                              /* enable interrupts                        */
                                                      /*------------------------------------------*/
    return ((CPU_INT16S)sizeof(CANFRM));              /* Return (number of bytes)                 */
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      CAN MESSAGE WRITE
*
*           This function destructs a CAN frame into the linked signals.
*
* \param    msgId             Unique message identifier
*
* \param    buffer            Pointer to CAN frame of type CANFRM
*
* \param    size              Size of buffer (must be equal to sizeof(CANFRM))
*
* \return   Number of bytes or -1 if an error was detected
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanMsgWrite(CPU_INT16S msgId, void *buffer, CPU_INT16U size)
{
    CANSIG_VAL_T value  = 0u;                         /* Local: signal value (up to 32 bits)      */
    CPU_INT16S   result;                              /* Local: function result (signal counter)  */
    CANFRM      *frm    = (CANFRM *)buffer;           /* Local: constructed CAN frame             */
    CANMSG_PARA *cfg;                                 /* Local: Pointer to CAN message config     */
    CANMSG_DATA *msg;                                 /* Local: Pointer to CAN message            */
    CANMSG_LINK *lnk;                                 /* Local: Pointer to CAN signal link        */
    CPU_INT08U   width;                               /* Local: bit width of signal               */
    CPU_INT32U   i;                                   /* Local: loop variable                     */

#if CPU_CFG_CRITICAL_METHOD == CPU_CRITICAL_METHOD_STATUS_LOCAL
    CPU_SR cpu_sr;                                    /* LocaL: Storage for CPU status register   */
#endif                                                /*------------------------------------------*/

#if CANMSG_ARG_CHK_EN > 0

    if ((msgId < 0) || ((CPU_INT16U)msgId >= CANMSG_N)) { /* is msgId out of range?               */
        can_errnum = CAN_ERR_MSGID;
        return CAN_ERR_MSGID;
    }
    if (CanMsgTbl[msgId].Cfg == NULL_PTR) {           /* is message not created?                  */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
    if (size != sizeof(CANFRM)) {                     /* is size equal sizeof(CANFRM)?            */
        can_errnum = CAN_ERR_FRMSIZE;
        return CAN_ERR_FRMSIZE;
    }
    if (buffer == NULL_PTR) {                         /* is buffer an invalid pointer?            */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
#endif /* CANMSG_ARG_CHK_EN > 0 */

    CPU_CRITICAL_ENTER();                             /* disable interrupts                       */
    msg = &CanMsgTbl[msgId];                          /* set can message pointer                  */
    cfg = msg->Cfg;                                   /* set can message config pointer           */
    lnk = &cfg->SigLst[0];                            /* set can link pointer to first link       */
    for (i=0u; i<cfg->SigNum;i++) {                   /* until last used signal link reached:     */
        result = CanSigIoCtl((CPU_INT16S)lnk->Id,     /* get configured signal width with         */
                    (CPU_INT16U)CANSIG_GET_WIDTH,     /*   functioncode for getting width         */
                    (void*)&width);                   /*   pointer to result variable             */
        CANSetErrRegister(result);

        value = (CANSIG_VAL_T)CanFrmGet(frm,          /* get value out of CAN frame               */
                                        width,
                                        lnk->Pos);    /*lint !e644 width is initialized           */
        result = CanSigWrite((CPU_INT16S)lnk->Id,     /* write signal value with                  */
                    (void *)&value,                   /*   pointer to value                       */
                    CANSIG_MAX_WIDTH);                /*   with needed number of bytes            */
        CANSetErrRegister(result);

        lnk++;                                        /*lint !e960 set pointer to next link       */
    }
    CPU_CRITICAL_EXIT();                              /* enable interrupts                        */
                                                      /*------------------------------------------*/
    return ((CPU_INT16S)sizeof(CANFRM));              /* Return number of bytes                   */
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      CREATE CAN MESSAGE
*
*           This function checks, if a free CAN message is available. If yes, this message
*           is set in front of the used list and initialized with the configured message data.
*
* \param    cfg               Configuration of CAN message
*
* \return   The message identifier or an errorcode: -1
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanMsgCreate(CANMSG_PARA *cfg)
{
    CPU_INT16S   result = CAN_ERR_MSGCREATE;          /* Local: function result                   */
    CANMSG_DATA *msg;                                 /* Local: Pointer to message                */
    CPU_SR_ALLOC();                                   /* LocaL: Storage for CPU status register   */
                                                      /*------------------------------------------*/

#if CANMSG_ARG_CHK_EN > 0
    CPU_INT16U   sigId;                               /* Local: Signal identifier                 */
    CPU_INT08U   use = CANSIG_UNUSED;                 /* Local: Signal use-status                 */
    CPU_INT08U   n;                                   /* Local: Loop through signal list          */
                                                      /*------------------------------------------*/

    if (cfg == NULL_PTR) {                            /* is cfg a valid pointer?                  */
        can_errnum = CAN_ERR_NULLPTR;
        return (result);
    }
    for (n=0u; n<cfg->SigNum; n++) {                  /* are all linked signals in use?           */
        sigId = cfg->SigLst[n].Id;
        result = CanSigIoCtl((CPU_INT16S)sigId,       /* get signal status                        */
                          (CPU_INT16U)CANSIG_GET_STATUS,
                          &use);
        if (result < CAN_ERR_NONE) {
            can_errnum = result;
            return result;
        }
        if (use == CANSIG_UNUSED) {
            can_errnum = CAN_ERR_MSGUNUSED;
            return CAN_ERR_MSGUNUSED;
        }
    }
#endif /* CANMSG_ARG_CHK_EN > 0 */

    CPU_CRITICAL_ENTER();                             /* disable interrupts                       */
    if (CanMsgFreeLst != 0) {                         /* see, if a free message is available      */
        msg           = CanMsgFreeLst;                /* yes: get first element from free list    */
        CanMsgFreeLst = msg->Next;                    /* set free list root to next element       */

        msg->Cfg      = cfg;                          /* link configuration to this element       */

        msg->Next     = CanMsgUsedLst;                /* put element in front of used list        */
        CanMsgUsedLst = msg;                          /* set used list to new first element       */

        result = (CPU_INT16S)msg->Id;                 /* return id of created message             */
    }
    CPU_CRITICAL_EXIT();                              /* enable interrupts                        */
                                                      /*------------------------------------------*/
    CANSetErrRegister(result);
    return result;                                    /* Return function result                   */
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      DELETE CAN MESSAGE
*
*           This function checks, if a CAN message is in use. If yes, the CAN message will
*           be removed from the used list and put back to the free list.
*
* \param    msgId             Unique message identifier
*
* \return   Errorcode -1, if an error is detected, otherwise 0 for successful deletion.
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanMsgDelete(CPU_INT16S msgId)
{
    CANMSG_DATA *msg;                                 /* Local: pointer to message data           */
    CANMSG_DATA *previous;                            /* Local: pointer to previous used message  */
    CPU_SR_ALLOC();                                   /* LocaL: Storage for CPU status register   */
                                                      /*------------------------------------------*/

#if CANMSG_ARG_CHK_EN > 0

    if ((msgId < 0) || ((CPU_INT16U)msgId >= CANMSG_N)) { /* is msgId out of range?               */
        can_errnum = CAN_ERR_MSGID;
        return CAN_ERR_MSGID;
    }
    if (CanMsgTbl[msgId].Cfg == NULL_PTR) {           /* is message not created?                  */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
#endif /* CANMSG_ARG_CHK_EN > 0 */

    CPU_CRITICAL_ENTER();                             /* disable interrupts                       */
    msg = &CanMsgTbl[msgId];                          /* set pointer to message data              */
    msg->Cfg = NULL_PTR;                              /* mark message as 'unused'                 */
                                                      /*------------------------------------------*/
    if (CanMsgUsedLst == msg) {                       /* see, if message is root of used list     */
        CanMsgUsedLst = msg->Next;                    /* update root to next element in used list */
    } else {                                          /* otherwise: signal is within the list     */
        previous = CanMsgUsedLst;                     /* set previous message pointer to lst root */
        while (previous->Next != msg) {               /* go through list until previous pointer   */
            previous = previous->Next;                /*   is in front of message pointer         */
        }
        previous->Next = msg->Next;                   /* remove message out of list               */
    }
    msg->Next     = CanMsgFreeLst;                    /* Link message data in front of free list  */
    CanMsgFreeLst = msg;                              /* Update root pointer of free list         */
    CPU_CRITICAL_EXIT();                              /* leave critical section                   */
                                                      /*------------------------------------------*/
    return CAN_ERR_NONE;                              /* return function result                   */
}


#endif /* CANMSG_EN > 0 */

