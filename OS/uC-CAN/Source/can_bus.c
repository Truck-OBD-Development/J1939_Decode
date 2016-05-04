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
* Filename      : can_bus.c
* Version       : V2.42.00
* Programmer(s) : E0
* Purpose       : This source file implements the functions for the buffered CAN bus management layer.
****************************************************************************************************
*/

/*
****************************************************************************************************
*                                             INCLUDES
****************************************************************************************************
*/

#include "can_bus.h"                                  /* can bus handling functions               */
#include "can_frm.h"                                  /* can frame definitions                    */
#include "can_err.h"                                  /* can error codes                          */
/*
****************************************************************************************************
*                                            GOBAL DATA
****************************************************************************************************
*/
volatile CPU_INT16S can_errnum = CAN_ERR_NONE;        /* latest CAN error code                    */

#if CANBUS_EN > 0
/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      CAN BUS DATA
* \ingroup  UCCAN
*
*           Allocation of global can bus management table
*/
/*------------------------------------------------------------------------------------------------*/
CANBUS_DATA CanBusTbl[CANBUS_N];

static CPU_INT08U CanBus_IsInitialized = 0u;          /* marker for: CanBus module is initialized */

/*
****************************************************************************************************
*                                    LOCAL FUNCTION PROTOTYPES
****************************************************************************************************
*/

static void CanBusCpy (void *dst, void *src, CPU_INT08U size);

/*
****************************************************************************************************
*                                            FUNCTIONS
****************************************************************************************************
*/
/*lint --e{717} use of do {} while (0) */

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      COPY FRAME TO BUFFER OR VICE VERSA
* \ingroup  UCCAN
*
*           Auxillary routine to replace std-lib-functions like memcpy.
*           passed arguments are checked by calling functions
*
* \param    dst               pointer to destination object
* \param    src               pointer to source object
* \param    size              size in byte to be copied
*
* \return   void
*/
/*------------------------------------------------------------------------------------------------*/
static void CanBusCpy (void *dst, void *src, CPU_INT08U size)
{
    CPU_INT32U   i;                                   /* Local: loop variable                     */
    CPU_INT08U  *psrc = (CPU_INT08U *)src;            /* Local: source pointer                    */
    CPU_INT08U  *pdst = (CPU_INT08U *)dst;            /* Local: destination pointer               */

    for (i=0u; i<size; i++) {
        *pdst = *psrc;
        pdst++;                                       /*lint !e960 increment ok                   */
        psrc++;                                       /*lint !e960 increment ok                   */
    }
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      INITIALIZE CAN BUS MANAGEMENT
* \ingroup  UCCAN
*
*           Initializes the CAN bus management. This includes the creation of all needed OS-service
*           components. The needed components are dependened on the configuration of the
*           CAN bus management mode.
*
* \note     This function has the standard device driver interface, decribed in the porting
*           chapter of the user manual. This allows the CAN bus handling via the standard
*           device driver interface.
*
* \param    arg               Not used
*
* \return   Errorcode, if an error is detected, otherwise CAN_ERR_NONE for successful initialization.
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanBusInit(CPU_INT32U arg)
{
    CANBUS_DATA *bus    = &(CanBusTbl[0]);            /* Local: pointer to bus #1                 */
    CPU_INT32U   i;                                   /* Local: loop variable                     */
    CPU_INT16S   err;                                 /* Local: errorcode of CANOS initialization */
    CPU_INT16S   result = CAN_ERR_NONE;               /* Local: function result                   */
                                                      /*------------------------------------------*/
    (void)arg;                                        /* unused; prevent compiler warning         */
    if (CanBus_IsInitialized == 0u) {
        err = CANOS_Init();                           /* Initialize OS specific services          */
        if (err != CAN_ERR_NONE) {                    /* See, if services are initialized         */
            can_errnum = err;
            return err;                               /* set function result to 'error'           */
        } else {                                      /* otherwise, build free list:              */
            for (i=0u; i<CANBUS_N; i++) {             /* loop through all CAN busses in table     */
                bus->RxTimeout = 0u;                  /* set timeout to 0 (Rx in blocking mode)   */
                bus->TxTimeout = 0u;                  /* set timeout to 0 (Tx in blocking mode)   */
                bus->Dev       = 0;                   /* clear device identifier                  */
                bus->Cfg       = NULL_PTR;            /* clear pointer to bus configuration       */
                bus->BufRxRd   = 0u;                  /* set receive read location to buffer      */
                bus->BufRxWr   = 0u;                  /* set receive write location to buffer     */
                bus->BufTxRd   = 0u;                  /* set transmit read location to buffer     */
                bus->BufTxWr   = 0u;                  /* set transmit write location to buffer    */
#if CANBUS_STAT_EN > 0
                bus->RxLost    = 0u;                  /* clear counter for lost RX frames         */
                bus->TxLost    = 0u;                  /* clear counter for lost TX frames         */
                bus->RxOk      = 0u;                  /* clear counter for received RX frames     */
                bus->TxOk      = 0u;                  /* clear counter for transmitted TX frames  */
#endif  /* CANBUS_STAT_EN > 0 */

                bus++;                                /*lint !e960 switch bus to next bus in table*/
            }
            CanBus_IsInitialized = 1u;                /* mark bus initialized                     */
        }
    }                                                 /*------------------------------------------*/
    return result;                                    /* return function result                   */
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      CAN BUS I/O CONTROL
* \ingroup  UCCAN
*
*           This function performs a special action on the opened device. The functioncode
*           func defines what the caller want to do. The following functioncodes are
*           allowed:
*
*           - CANBUS_RESET:          Reinitialize the CAN bus; all pending transmissions
*                                    will be canceled and received messages will be lost.
*
*           - CANBUS_FLUSH_TX:       Remove all entries out of the TX queue
*
*           - CANBUS_FLUSH_RX:       Remove all entries out of the RX queue
*
*           - CANBUS_SET_TX_TIMEOUT: Set TX timeout value
*
*           - CANBUS_SET_RX_TIMEOUT: Set RX timeout value
*
* \note     This function has the standard device driver interface, decribed in the porting
*           chapter of the user manual. This allows the CAN bus handling via the standard
*           device driver interface.
*
* \param    busId             Bus identifier
*
* \param    func              function code
*
* \param    argp              Pointer to argument, specific to the function code
*
* \return   Errorcode, if an error is detected, otherwise CAN_ERR_NONE for successful operation.
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanBusIoCtl(CPU_INT16S busId, CPU_INT16U func, void *argp)
{
    CPU_INT16S   result = CAN_ERR_UNKNOWN;            /* Local: function result                   */
    CANBUS_DATA *bus;                                 /* Local: pointer to bus data               */
    CANBUS_PARA *cfg;                                 /* Local: pointer to bus configuration      */
    CPU_INT16U   drvfunc;                             /* Local: translated driver function code   */
    CPU_SR_ALLOC();                                   /* LocaL: Storage for CPU status register   */
                                                      /*------------------------------------------*/

#if CANBUS_ARG_CHK_EN > 0
                                                      /* is busId out of range?                   */
    if ((busId < 0) || ((CPU_INT16U)busId >= CANBUS_N)) {
        can_errnum = CAN_ERR_BUSID;
        return CAN_ERR_BUSID;
    }
    if (CanBusTbl[busId].Cfg == NULL_PTR) {           /* is bus not enabled?                      */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
#endif /* CANBUS_ARG_CHK_EN > 0 */

    bus = &CanBusTbl[busId];                          /* set pointer to bus data                  */
    cfg = bus->Cfg;                                   /* yes: set pointer to bus configuration    */

    switch (func) {                                   /* Switch to selected function code         */
                                                      /*------------------------------------------*/
        case CANBUS_RESET:                            /*            Reset CAN bus                 */
                                                      /*------------------------------------------*/
            result = cfg->Close(bus->Dev);            /* Close opened CAN bus                     */
            if (result != CAN_ERR_NONE) {
                break;
            }
            result = cfg->Init(cfg->DriverDevName);   /* Reinitialize the CAN bus                 */
            if (result != CAN_ERR_NONE) {
                break;
            }
                                                      /* Open configured can bus                  */
            bus->Dev = cfg->Open((CPU_INT16S)cfg->BusNodeName,
                                 cfg->DriverDevName,
                                 DEV_RW);
            if (bus->Dev >= 0) {                      /* See, if bus can be opened                */
                drvfunc = cfg->Io[CAN_SET_BAUDRATE];
                result = cfg->IoCtl(bus->Dev, drvfunc, /* Set can bus timing with:                 */
                           (void*)&(cfg->Baudrate));  /*   configured baudrate                    */
                if (result != CAN_ERR_NONE) {
                    break;
                }
                                                      /* see, if Ext.Ids on receiver are enabled  */
                if (cfg->Extended == CAN_TRUE) {
                    result = cfg->IoCtl(bus->Dev,     /* Set receiver to extended format ids      */
                                     cfg->Io[CAN_RX_EXTENDED],
                                     0);
                    if (result != CAN_ERR_NONE) {
                        break;
                    }
                }
                result = cfg->IoCtl(bus->Dev,         /* Enable can bus communication             */
                                 cfg->Io[CAN_START], 0);
                if (result != CAN_ERR_NONE) {
                    break;
                }
                result = CAN_ERR_NONE;                /* successfull can bus initialisation       */
            }
            else {
                result = CAN_ERR_OPEN;
            }
            break;
                                                      /*------------------------------------------*/
        case CANBUS_FLUSH_TX:                         /*           Flush tx queue                 */
                                                      /*------------------------------------------*/
            CPU_CRITICAL_ENTER();                     /* disable all interrupts                   */
            bus->BufTxRd = bus->BufTxWr;              /* buffer is empty when read = write ptr    */
            CANOS_ResetTx(busId);
            CPU_CRITICAL_EXIT();                      /* enable all interrupts                    */
            result       = CAN_ERR_NONE;              /* indicate successful operation            */
            break;
                                                      /*------------------------------------------*/
        case CANBUS_FLUSH_RX:                         /*           Flush rx queue                 */
                                                      /*------------------------------------------*/
            CPU_CRITICAL_ENTER();                     /* disable all interrupts                   */
            bus->BufRxRd = bus->BufRxWr;              /* buffer is empty when read = write ptr    */
            CANOS_ResetRx(busId);
            CPU_CRITICAL_EXIT();                      /* enable all interrupts                    */
            result       = CAN_ERR_NONE;              /* indicate successful operation            */
            break;
                                                      /*------------------------------------------*/
        case CANBUS_SET_RX_TIMEOUT:                   /*           Set RX timeout                 */
                                                      /*------------------------------------------*/
            if (argp != NULL_PTR) {                   /* see, if argument pointer is valid        */
                bus->RxTimeout = *(CPU_INT16U*)argp;  /* set new timeout value                    */
                result = CAN_ERR_NONE;                /* indicate successful operation            */
            }
            else {
                result = CAN_ERR_NULLPTR;             /* indicate an error                        */
            }
            break;
                                                      /*------------------------------------------*/
        case CANBUS_SET_TX_TIMEOUT:                   /*           Set TX timeout                 */
                                                      /*------------------------------------------*/
            if (argp != NULL_PTR) {                   /* see, if argument pointer is valid        */
                bus->TxTimeout = *(CPU_INT16U*)argp;  /* set new timeout value                    */
                result = CAN_ERR_NONE;                /* indicate successful operation            */
            }
            else {
                result = CAN_ERR_NULLPTR;             /* indicate an error                        */
            }
            break;
                                                      /*------------------------------------------*/
        default:                                      /*        Unsupported function code         */
            result = CAN_ERR_IOCTRLFUNC;              /* indicate successful operation            */
                                                      /*------------------------------------------*/
            break;                                    /* don't indicate successful operation      */
    }                                                 /*------------------------------------------*/

    CANSetErrRegister(result);
    return(result);                                   /* return function result                   */
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      RECEIVE CAN FRAME
* \ingroup  UCCAN
*
*           This function is called by the application to obtain a frame from the opened
*           CAN bus. The function will wait for a frame to be received on the CAN bus or
*           until the configured timeout is reached.
*
* \note     This function has the standard device driver interface, decribed in the porting
*           chapter of the user manual. This allows the CAN bus handling via the standard
*           device driver interface.
*
* \param    busId             Bus identifier
*
* \param    buffer            Pointer to CAN frame in format CANFRM
*
* \param    size              Size of CAN frame
*
* \return   Errorcode CAN_ERR_UNKNOWN, if an error is detected, otherwise size of can frame
*           for successful reading.
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanBusRead(CPU_INT16S busId, void *buffer, CPU_INT16U size)
{
    CANFRM      *frm;                                 /* Local: Pointer to received can frame     */
    CANBUS_DATA *bus;                                 /* Local: Pointer to bus data               */
    CPU_INT16S   result = CAN_ERR_UNKNOWN;            /* Local: Function result                   */
    CPU_INT08U   frx;                                 /* Local: indication for 'frame received'   */
    CPU_SR_ALLOC();                                   /* LocaL: Storage for CPU status register   */
                                                      /*------------------------------------------*/

#if CANBUS_ARG_CHK_EN > 0
    if ((busId < 0) || ((CPU_INT16U)busId >= CANBUS_N)) { /* is busId out of range?               */
        can_errnum = CAN_ERR_BUSID;
        return (CAN_ERR_BUSID);
    }
    if (buffer == NULL_PTR) {                         /* does buffer points to valid address ?    */
        can_errnum = CAN_ERR_NULLPTR;
        return (CAN_ERR_NULLPTR);
    }
    if (size != sizeof(CANFRM)) {                     /* is size invalid?                         */
        can_errnum = CAN_ERR_FRMSIZE;
        return (CAN_ERR_FRMSIZE);
    }
#endif /* CANBUS_ARG_CHK_EN > 0 */

    bus = &CanBusTbl[busId];                          /* set pointer to bus data                  */
    frx = CANOS_PendRxFrame (bus->RxTimeout, busId);  /* wait for a CAN frame from RX-ISR         */
    if (frx != 0u) {                                  /* See if frame received within timeout     */
        frm = &bus->BufRx[bus->BufRxRd];              /* get next read location from ringbuffer   */
                                                      /* copy can frame to buffer                */
        CanBusCpy(buffer,(void *)frm, (CPU_INT08U)sizeof(CANFRM));
        CPU_CRITICAL_ENTER();                         /* disable all interrupts                   */
        bus->BufRxRd++;                               /* increment next read location             */
        if (bus->BufRxRd >= CANBUS_RX_QSIZE) {        /* see, if end of buffer reached            */
            bus->BufRxRd = 0u;                        /* yes: reset to start of buffer            */
        }
        CPU_CRITICAL_EXIT();                          /* disable all interrupts                   */
        result = (CPU_INT16S)sizeof(CANFRM);          /* set received byte counter                */
    }

#if CANBUS_STAT_EN > 0
    if (result == (CPU_INT16S)sizeof(CANFRM)) {       /* see, if no error occurs                  */
        bus->RxOk++;                                  /* increment receive counter                */
    }                                                 /* Failure: we can't get a memory partition */
#endif /* CANBUS_STAT_EN > 0 */

                                                      /*------------------------------------------*/
    CANSetErrRegister(result);
    return (result);                                  /* return function result                   */
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      SEND CAN FRAME
* \ingroup  UCCAN
*
*           This function is called by the application to send a CAN frame on the opened
*           CAN bus. The function will wait for the buffer to empty out if the buffer is
*           full. The function returns to the application if the buffer doesn't empty
*           within the configured timeout. A timeout value of 0 (standard) means, that
*           the calling function will wait forever for the buffer to empty out.
*
* \note     This function has the standard device driver interface, decribed in the porting
*           chapter of the user manual. This allows the CAN bus handling via the standard
*           device driver interface.
*
* \param    busId             Bus identifier
*
* \param    buffer            Pointer to CAN frame in format CANFRM
*
* \param    size              Size of CAN frame
*
* \return   Errorcode CAN_ERR_UNKNOWN, if an error is detected, otherwise size of can frame for
*           successful writing.
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanBusWrite(CPU_INT16S busId, void *buffer, CPU_INT16U size)
{
    CANFRM      *frm;                                 /* Local: current CAN frame                 */
    CANBUS_PARA *cfg;                                 /* Local: Pointer to bus configuration      */
    CANBUS_DATA *bus;                                 /* Local: Pointer to bus data               */
    CPU_INT16S   result;                              /* Local: Function result                   */
    CPU_INT08U   txstatus;                            /* Local: Status of device tx buffer        */
    CPU_INT08U   ftx;                                 /* Local: transmit frame buffer available   */
    CPU_SR_ALLOC();                                   /* LocaL: Storage for CPU status register   */
                                                      /*------------------------------------------*/

#if CANBUS_ARG_CHK_EN > 0
    if ((busId < 0) || ((CPU_INT16U)busId >= CANBUS_N)) { /* is busId out of range?               */
        can_errnum = CAN_ERR_BUSID;
        return CAN_ERR_BUSID;
    }
    if (CanBusTbl[busId].Cfg == NULL_PTR) {           /* is bus not enabled?                      */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
    if (buffer == NULL_PTR) {                         /* does buffer points to valid address ?    */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
    if (size != sizeof(CANFRM)) {                     /* is size invalid?                         */
        can_errnum = CAN_ERR_FRMSIZE;
        return CAN_ERR_FRMSIZE;
    }
#endif /* CANBUS_ARG_CHK_EN > 0 */

    bus = &CanBusTbl[busId];                          /* set pointer to bus data                  */
    cfg = bus->Cfg;                                   /* set pointer to bus configuration         */
    ftx = CANOS_PendTxFrame(bus->TxTimeout, busId);   /* check space in transmit buffer           */

    CPU_CRITICAL_ENTER();                             /* disable all interrupts                   */
    result = cfg->IoCtl(bus->Dev,                     /* get CAN bus device tx buffer status      */
                        cfg->Io[CAN_TX_READY],
                        (void*)&txstatus);
    CANSetErrRegister(result);
                                                      /* see if canbus tx buffer is ready/idle    */
    if (txstatus == (CPU_INT08U)CAN_TRUE) {           /*lint !e644 txstatus set by IoCtl          */
        result = cfg->Write(bus->Dev, buffer,         /* write can frame to can bus interface     */
                            (CPU_INT16U)sizeof(CANFRM));
        CPU_CRITICAL_EXIT();                          /* enable all interrupts                    */
        CANSetErrRegister(result);

        CANOS_PostTxFrame(busId);                     /* release transmit buffer reservation      */
    }
#if CANBUS_TX_HANDLER_EN > 0                          /* use buffer only when tx IRQ is enabled   */
    else {                                            /* otherwise: tx interrupt is enabled       */
        if (ftx != 0u) {                              /* see if we have space in transmit buffer  */
            frm = &bus->BufTx[bus->BufTxWr];          /* get next write location                  */
            bus->BufTxWr++;                           /* set write location to next buffer entry  */
            if (bus->BufTxWr >= CANBUS_TX_QSIZE) {    /* see, if buffer end is reached            */
                bus->BufTxWr = 0u;                    /* yes: wrap around to start of buffer      */
            }
            CanBusCpy((void *)frm,                    /* copy buffer to can frame memory          */
                       buffer,
                       (CPU_INT08U)sizeof(CANFRM));
            result = CAN_ERR_NONE;                    /* indicate successful transmission         */
        } else {                                      /* otherwise: buffer is full                */
            result = CAN_ERR_UNKNOWN;                 /* indicate error during transmission       */
        }
        CPU_CRITICAL_EXIT();                          /* enable all interrupts                    */
    }
#else
    else {
        CPU_CRITICAL_EXIT();                          /* enable all interrupts                    */
        CANOS_PostTxFrame(busId);                     /* release transmit buffer reservation      */
    }
#endif

#if CANBUS_STAT_EN > 0
    if (result < CAN_ERR_NONE) {                      /* otherwise: no queue/message buffer free  */
        bus->TxLost++;                                /* no: increment transmission lost counter  */
    }
#endif /* CANBUS_STAT_EN > 0 */

                                                      /*------------------------------------------*/
    CANSetErrRegister(result);
    return(result);                                   /* return function result                   */
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      ENABLE CAN BUS
* \ingroup  UCCAN
*
*           This function checks, if a empty CAN bus data element is available. If yes, this
*           element is initialized with the CAN bus configuration.
*           The CAN bus driver is used to initialize the CAN bus with the defined
*           baudrate and set the CAN bus in active state. Therefore the bus is ready for
*           communication.
*
* \note     The configured CAN bus controller will be opened with the lowlevel device driver
*           and not closed at the end of the creation. This is done to ensure, that no other
*           function/task tries to use the CAN controller. In other words: this implementation
*           of the CAN bus management needs exclusive access to the CAN controller.
*
* \param    cfg               Configuration of CAN bus
*
* \return   Errorcode, if an error is detected, otherwise CAN_ERR_NONE for successful creation.
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanBusEnable(CANBUS_PARA *cfg)
{
    CPU_INT16S   result;                              /* Local: function result                   */
    CANBUS_DATA *bus;                                 /* Local: pointer to bus data               */
                                                      /*------------------------------------------*/

#if CANBUS_ARG_CHK_EN > 0
    if (cfg == NULL_PTR) {                            /* is cfg a valid pointer?                  */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
    if (cfg->BusNodeName > CANBUS_N) {                /* if BusNodeName is out of range           */
        can_errnum = CAN_ERR_BUSID;
        return CAN_ERR_BUSID;
    }
    if (cfg->Init == NULL_PTR) {                      /* is Init() a valid pointer?               */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
    if (cfg->Open == NULL_PTR) {                      /* is Open() a valid pointer?               */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
    if (cfg->Close == NULL_PTR) {                     /* is Close() a valid pointer?              */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
    if (cfg->IoCtl == NULL_PTR) {                     /* is IoCtl() a valid pointer?              */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
    if (cfg->Read == NULL_PTR) {                      /* is Read() a valid pointer?               */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
    if (cfg->Write == NULL_PTR) {                     /* is Write() a valid pointer?              */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
#endif /* CANBUS_ARG_CHK_EN > 0 */

                                                      /*------------------------------------------*/
    bus = &(CanBusTbl[cfg->BusNodeName]);             /* get element from bus table               */
    if (bus->Cfg == NULL_PTR) {                       /* this should be disabled                  */
        bus->Cfg      = cfg;                          /* link configuration to this element       */
        result = cfg->Init(cfg->DriverDevName);       /* Initialize the CAN bus                   */
        if (result != CAN_ERR_NONE) {
            can_errnum = result;
            return result;
        }
                                                      /* Open configured can bus                  */
        bus->Dev      = cfg->Open((CPU_INT16S)cfg->BusNodeName,
                                  cfg->DriverDevName,
                                  DEV_RW);
        if (bus->Dev >= 0) {                          /* See, if bus can be opened                */
            if (cfg->Extended == CAN_TRUE) {          /* see, if Ext.Ids on receiver are enabled  */
                result = cfg->IoCtl(bus->Dev,         /* Set receiver to extended format ids      */
                                    cfg->Io[CAN_RX_EXTENDED], 0);
                CANSetErrRegister(result);
            }

            if (cfg->Baudrate != 0u) {                /* see, if baudrate is configured           */

                result = cfg->IoCtl(bus->Dev,         /* Set bus timing with configured baudrate  */
                                    cfg->Io[CAN_SET_BAUDRATE],
                                    (void*)&cfg->Baudrate);
                if (result != CAN_ERR_NONE) {         /* if baudrate wasn't configured return     */
                    can_errnum = result;
                    return result;
                }

                result = cfg->IoCtl(bus->Dev,         /* Enable can bus communication             */
                                    cfg->Io[CAN_START], 0);
            }
            return result;                            /* return the result                        */
        } else {                                      /* otherwise: opening bus not possible      */

            bus->Cfg      = NULL_PTR;                 /* remove link to given configuration       */
            bus->Dev      = 0;                        /* clear device                             */
            can_errnum = CAN_ERR_OPEN;
            return CAN_ERR_OPEN;
        }
    }                                                 /*------------------------------------------*/
    can_errnum = CAN_ERR_ENABLE;
    return CAN_ERR_ENABLE;                            /* return function result                   */
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      DISABLE CAN BUS
* \ingroup  UCCAN
*
*           This function checks, if a CAN bus data element is in use. If yes, the linked
*           CAN bus will be closed with the lowlevel device driver, e.g. the bus will be
*           closed. After successful operation the configuration of this element is removed.
*
* \param    busId             Bus identifier
*
* \return   Errorcode, if an error is detected, otherwise CAN_ERR_NONE for successful deletion.
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S CanBusDisable(CPU_INT16S busId)
{
    CANBUS_DATA *bus;                                 /* Local: pointer to bus data               */
    CANBUS_PARA *cfg;                                 /* Local: pointer to bus configuration      */
    CPU_INT16S   err;                                 /* Local: errorcode of device driver        */
                                                      /*------------------------------------------*/
#if CANBUS_ARG_CHK_EN > 0

    if ((busId < 0) || ((CPU_INT16U)busId >= CANBUS_N)) {  /* is busId out of range?              */
        can_errnum = CAN_ERR_BUSID;
        return CAN_ERR_BUSID;
    }
    if (CanBusTbl[busId].Cfg == NULL_PTR) {           /* is bus not enabled?                      */
        can_errnum = CAN_ERR_NULLPTR;
        return CAN_ERR_NULLPTR;
    }
#endif /* CANBUS_ARG_CHK_EN > 0 */

    bus = &CanBusTbl[busId];                          /* set pointer to bus data                  */
    cfg = bus->Cfg;                                   /* yes: set pointer to bus configuration    */
    err = cfg->IoCtl(bus->Dev,                        /* Try to disable can bus communication     */
                     cfg->Io[CAN_STOP], 0);
    CANSetErrRegister(err);
                                                      /*------------------------------------------*/
    if (err == CAN_ERR_NONE) {
        err = cfg->Close(bus->Dev);                       /* Close the CAN bus                        */
        bus->Cfg = NULL_PTR;                              /* remove link to bus configuration         */
        CANSetErrRegister(err);
    }
    return CAN_ERR_NONE;                              /* return function result                   */
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      CAN TX INTERRUPT HANDLER
* \ingroup  UCCAN
*
*           The calling interrupt vector has to pass the bus identifier as a parameter to
*           the handler.
*
* \param    busId             Bus identifier
*/
/*------------------------------------------------------------------------------------------------*/
#if CANBUS_TX_HANDLER_EN > 0
void CanBusTxHandler(CPU_INT16S busId)
{
    CANFRM      *frm;                                 /* Local: current CAN frame                 */
    CANBUS_PARA *cfg;                                 /* Local: pointer to bus configuration      */
    CANBUS_DATA *bus;                                 /* Local: pointer to bus data               */
    CPU_INT16S   err;
    CPU_SR_ALLOC();                                   /* LocaL: Storage for CPU status register   */
                                                      /*------------------------------------------*/

#if CANBUS_ARG_CHK_EN > 0
    if ((busId < 0) || ((CPU_INT16U)busId >= CANBUS_N)) { /* is busId out of range?               */
        can_errnum = CAN_ERR_BUSID;
        return;
    }
    if (CanBusTbl[busId].Cfg == NULL_PTR) {           /* is bus not enabled?                      */
        can_errnum = CAN_ERR_NULLPTR;
        return;
    }
#endif /* CANBUS_ARG_CHK_EN > 0 */

    bus = &CanBusTbl[busId];                          /* set pointer to bus data                  */
    cfg = bus->Cfg;                                   /* set pointer to bus configuration         */

#if CANBUS_STAT_EN > 0
    bus->TxOk++;                                      /* increment transmission counter           */
#endif /* CANBUS_STAT_EN > 0 */

    CPU_CRITICAL_ENTER();                             /* disable all interrupts                   */
    if (bus->BufTxRd != bus->BufTxWr) {               /* see, if buffer contains pending frames   */
        frm = &bus->BufTx[bus->BufTxRd];              /* get next frame out of transmit buffer    */
        bus->BufTxRd++;                               /* set next read location to next entry     */
        if (bus->BufTxRd >= CANBUS_TX_QSIZE) {        /* see, if buffer end is reached            */
            bus->BufTxRd = 0u;                        /* wrap around to start of ringbuffer       */
        }
        err = cfg->Write(bus->Dev, (void *)frm,       /* write can frame to can bus interface     */
                   (CPU_INT16U)sizeof(CANFRM));
        CPU_CRITICAL_EXIT();                          /* allow all interrupts                     */
        CANSetErrRegister(err);

        CANOS_PostTxFrame(busId);                     /* release transmit buffer reservation      */
    } else {
        CPU_CRITICAL_EXIT();                          /* allow all interrupts                     */
    }
}
#endif  /* CANBUS_TX_HANDLER_EN > 0 */

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      CAN RX INTERRUPT HANDLER
* \ingroup  UCCAN
*
*           The calling interrupt vector has to pass the bus identifier as a parameter to
*           the handler.
*
* \param    busId             Bus identifier
*/
/*------------------------------------------------------------------------------------------------*/
#if CANBUS_RX_HANDLER_EN > 0
void CanBusRxHandler(CPU_INT16S busId)
{
    CANFRM      *frm;                                 /* Local: current CAN frame                 */
    CANFRM       dummyfrm;                            /* Local: current CAN frame                 */
    CANBUS_PARA *cfg;                                 /* Local: pointer to bus configuration      */
    CANBUS_DATA *bus;                                 /* Local: pointer to bus data               */
    CPU_INT16S   err;                                 /* Local: os errorcode                      */
    CPU_INT16S   consumed = 0;                        /* Local: return value of hook              */
    CPU_INT16U   rxnext;                              /* Local: next potential receive location   */
    CPU_SR_ALLOC();                                   /* LocaL: Storage for CPU status register   */
                                                      /*------------------------------------------*/
#if CANBUS_ARG_CHK_EN > 0
    if ((busId < 0) || ((CPU_INT16U)busId >= CANBUS_N)) { /* is busId out of range?               */
        can_errnum = CAN_ERR_BUSID;
        return;
    }
    if (CanBusTbl[busId].Cfg == NULL_PTR) {           /* is bus not enabled?                      */
        can_errnum = CAN_ERR_NULLPTR;
        return;
    }
#endif /* CANBUS_ARG_CHK_EN > 0 */

    bus = &CanBusTbl[busId];                          /* set pointer to bus data                  */
    cfg = bus->Cfg;                                   /* set pointer to bus configuration         */

    CPU_CRITICAL_ENTER();                             /* disable all interrupts                   */
    frm = &bus->BufRx[bus->BufRxWr];                  /* get next receive buffer frame entry      */
    rxnext = bus->BufRxWr + 1u;                       /* calc write location to next receiption   */
    if (rxnext >= CANBUS_RX_QSIZE) {                  /* see, if en of buffer is reached          */
        rxnext = 0u;                                  /* wrap around to start of buffer           */
    }
    if (rxnext != bus->BufRxRd) {                     /* see, if no buffer overrun occurs         */

        err = cfg->Read(bus->Dev, (void *)frm,        /* read can frame from can bus interface    */
                       (CPU_INT16U)sizeof(CANFRM));
        CANSetErrRegister(err);
        CPU_CRITICAL_EXIT();                          /* allow all interrupts                     */

#if CANBUS_HOOK_RX_EN == 1
        consumed = CanBusRxHook(busId, (void *)frm);
#endif /* CANBUS_HOOK_RX_EN == 1 */

        if (consumed == 0) {                          /* see, if CAN frame is not consumed        */
            CPU_CRITICAL_ENTER();                     /* disable all interrupts                   */
            bus->BufRxWr = rxnext;                    /* set next location in buffer              */
            CPU_CRITICAL_EXIT();                      /* allow all interrupts                     */

            CANOS_PostRxFrame(busId);                 /* signal a new CAN frame in receive buffer */
        }
    } else {                                          /* otherwise: no buffer available           */
        CPU_CRITICAL_EXIT();                          /* allow all interrupts                     */
#if CANBUS_RX_READ_ALWAYS_EN > 0
        err = cfg->Read(bus->Dev, (void *)&dummyfrm,  /* read can frame from can bus interface    */
                       (CPU_INT16U)sizeof(CANFRM));
        CANSetErrRegister(err);
        err = 0;                                      /* set err to 0 to indicated that the       */
                                                      /* frame is lost                            */
#endif /* CANBUS_RX_READ_ALWAYS_EN > 0 */
    }

#if CANBUS_STAT_EN > 0
    if (err != (CPU_INT16S)sizeof(CANFRM)) {          /* see, if an error occurs                  */
        bus->RxLost++;                                /* Increment receive CAN frame lost counter */
    }
#endif /* CANBUS_STAT_EN > 0 */
}
#endif /* CANBUS_RX_HANDLER_EN > 0 */

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      CAN STATUS-CHANGE INTERRUPT HANDLER
* \ingroup  UCCAN
*
*           The calling interrupt vector has to pass the bus identifier as a parameter to
*           the handler.
*
* \param    busId             Bus identifier
*/
/*------------------------------------------------------------------------------------------------*/
#if CANBUS_NS_HANDLER_EN > 0
void CanBusNSHandler(CPU_INT16S busId)
{

#if CANBUS_ARG_CHK_EN > 0

    if ((busId < 0) || ((CPU_INT16U)busId >= CANBUS_N)) {  /* is busId out of range?              */
        can_errnum = CAN_ERR_BUSID;
        return;                                       /* yes: no further actions - ignore request */
    }
    if (CanBusTbl[busId].Cfg == NULL_PTR) {           /* is bus not enabled?                      */
        can_errnum = CAN_ERR_NULLPTR;
        return;
    }
#endif /* CANBUS_ARG_CHK_EN > 0 */

#if CANBUS_HOOK_NS_EN == 1
    CanBusNSHook    (busId);
#endif
}
#endif  /* CANBUS_NS_HANDLER_EN > 0 */

#endif  /* CANBUS_EN > 0 */

