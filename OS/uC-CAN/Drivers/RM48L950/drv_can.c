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
* Filename      : drv_can.c
* Version       : V2.42.00
* Programmer(s) : E0
****************************************************************************************************
*/

/*
****************************************************************************************************
*                                             INCLUDES
****************************************************************************************************
*/

#include "drv_def.h"
#include "can_bsp.h"
#include "drv_can.h"
#include "can_bus.h"

/*
****************************************************************************************************
*                                             DEFINES
****************************************************************************************************
*/

/*
****************************************************************************************************
*                                   INTERNAL FUNCTION PROTOTYPES
****************************************************************************************************
*/

static void TIRM48CAN_SetBitTimingReg (TIRM48_CAN_DEV  *dev);

/*
****************************************************************************************************
*                                            LOCAL DATA
****************************************************************************************************
*/

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    DRIVER IDENTIFICATION CODE
*
* \ingroup  TIRM48_CAN
*
*           This constant holds the unique driver identification code.
*/
/*------------------------------------------------------------------------------------------------*/
static const CPU_INT32U DrvIdent = 0x243F1A01;

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    DRIVER ERROR CODE
*
* \ingroup  TIRM48_CAN
*
*           This variable holds the detailed error code if an error is detected.
*/
/*------------------------------------------------------------------------------------------------*/
static CPU_INT16U DrvError;

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    DEVICE CONFIGURATION TABLE
*
* \ingroup  TIRM48_CAN
*
*           This table holds the configuration of the devices.
*/
/*------------------------------------------------------------------------------------------------*/
static const TIRM48_CAN_CFG CanCfgTbl[TIRM48_CAN_DEV_N] = {
    {1, 2, 64},
    {1, 2, 64},
    {1, 2, 32}                                        /* DCAN3 only has 32 message boxes          */
};

#if CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_BIG
/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    BYTE ORDER
*
* \ingroup  TIRM48_CAN
*
*           Byte order for big endian.
*/
/*------------------------------------------------------------------------------------------------*/
static const CPU_INT08U CanByteOrder[] = {3, 2, 1, 0, 7, 6, 5, 4};
#endif

/*
****************************************************************************************************
*                                           GLOBAL DATA
****************************************************************************************************
*/

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    DEVICE TABLE
*
* \ingroup  TIRM48_CAN
*
*           This table holds the devices.
*/
/*------------------------------------------------------------------------------------------------*/
TIRM48_CAN_DEV CanDevTbl[TIRM48_CAN_DEV_N] = {{0}};

/*
****************************************************************************************************
*                                            FUNCTIONS
****************************************************************************************************
*/

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    CAN INITIALIZATION
*
* \ingroup  TIRM48_CAN
*
*           Initializes the CAN device with the given device name.
*
* \param    arg  the CAN device name
*
* \return   error code (0 if OK, -1 if an error occurred)
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S TIRM48CANInit (CPU_INT32U  arg)
{
    TIRM48_CAN_DEV *dev;
    CPU_INT16S      result;
    CPU_INT08U      i;
    
    
#if TIRM48_CAN_ARG_CHK_CFG > 0
    if (arg >= TIRM48_CAN_DEV_N) {
        DrvError = TIRM48_CAN_INIT_ERR;
        return (-1);
    }
#endif

    DrvError = TIRM48_CAN_NO_ERR;
    
    dev      = &CanDevTbl[arg];   
    dev->Use = 0;
    dev->Cfg = (TIRM48_CAN_CFG *)&CanCfgTbl[arg];
    
    if (arg == TIRM48_CAN_DCAN1) {
        dev->Reg = (TIRM48_CAN_REG *)TIRM48_CAN_REG_BASE_ADDR_DCAN1;
    } else if (arg == TIRM48_CAN_DCAN2) {
        dev->Reg = (TIRM48_CAN_REG *)TIRM48_CAN_REG_BASE_ADDR_DCAN2;
    } else if (arg == TIRM48_CAN_DCAN3) {
        dev->Reg = (TIRM48_CAN_REG *)TIRM48_CAN_REG_BASE_ADDR_DCAN3;
    }

    dev->Baudrate        = TIRM48_CAN_DEF_BAUDRATE;
    dev->SamplePoint     = TIRM48_CAN_DEF_SP;
    dev->ResynchJumpWith = TIRM48_CAN_DEF_RJW;
 
    result = TIRM48CAN_BSP_CalcBitTimingReg(dev);     /* Calculate bit timing register values     */
    if (result != TIRM48_CAN_NO_ERR) {
        DrvError = TIRM48_CAN_INIT_ERR;
        return (-1);
    }
    
    TIRM48CAN_BSP_PinCfg(arg);                        /* Set pin configuration                    */
    
    dev->Reg->CTL  = (TIRM48_CAN_REG_CTL_INIT_SET |   /* Enter init mode                          */
                      TIRM48_CAN_REG_CTL_CCE_SET  |   /* Configuration change enable              */
                      TIRM48_CAN_REG_CTL_PMD_DIS);    /* Parity function disabled                 */    
    while ((dev->Reg->CTL & TIRM48_CAN_REG_CTL_INIT_SET)
                         != TIRM48_CAN_REG_CTL_INIT_SET) {
    }
    
    TIRM48CAN_SetBitTimingReg(dev);                   /* Set bit timing register values           */
    
    dev->Reg->CTL &= ~TIRM48_CAN_REG_CTL_CCE_SET;     /* Configuration change disable             */
    
    for (i = 0; i < 4; i++) {                         /* Set interrupt multiplexer registers      */
        dev->Reg->INTMUXx[i] = 0;                     /* Use interrrupt line 0                    */
    }      
                                                      /* Configure Rx message boxes               */
    dev->Reg->IFx[0].MSK   = TIRM48_CAN_REG_IF_MSK_MXTD_SET;   /* Use extended ID for filtering   */
    dev->Reg->IFx[0].ARB   = TIRM48_CAN_REG_IF_ARB_MSGVAL_SET; /* Set message valid               */
    dev->Reg->IFx[0].MCTL  = TIRM48_CAN_REG_IF_MCTL_UMASK_SET; /* Use acceptance mask             */
#if TIRM48_CAN_RX_INTERRUPT_EN > 0
    dev->Reg->IFx[0].MCTL |= TIRM48_CAN_REG_IF_MCTL_RXIE_SET;  /* Enable Rx interrupt             */
#endif
    dev->Reg->IFx[0].CMD = 0xF0;                      /* WR, Mask, Arb, Control                   */
    for (i = dev->Cfg->RxFirst; i < dev->Cfg->RxLast; i++) {
        dev->Reg->IFx[0].NBR = i;
        while ((dev->Reg->IFx[0].STAT & TIRM48_CAN_REG_IF_STAT_BUSY_SET)
                                     == TIRM48_CAN_REG_IF_STAT_BUSY_SET) {
        }
    }
    dev->Reg->IFx[0].MCTL |= TIRM48_CAN_REG_IF_MCTL_EOB_SET;
    dev->Reg->IFx[0].NBR   = i;
    while ((dev->Reg->IFx[0].STAT & TIRM48_CAN_REG_IF_STAT_BUSY_SET)
                                 == TIRM48_CAN_REG_IF_STAT_BUSY_SET) {
    }
                                                      /* Configure Tx message box                 */
    dev->Reg->IFx[0].MSK  = 0;
    dev->Reg->IFx[0].ARB  = TIRM48_CAN_REG_IF_ARB_DIR_SET;
    dev->Reg->IFx[0].MCTL = 0;
    dev->Reg->IFx[0].CMD  = 0xF0;                     /* WR, Mask, Arb, Control                   */
    dev->Reg->IFx[0].NBR  = dev->Cfg->TxMsgBox;
    while ((dev->Reg->IFx[0].STAT & TIRM48_CAN_REG_IF_STAT_BUSY_SET)
                                 == TIRM48_CAN_REG_IF_STAT_BUSY_SET) {
    }

#if TIRM48_CAN_NS_INTERRUPT_EN > 0
    dev->Reg->CTL |= TIRM48_CAN_REG_CTL_EIE_SET;      /* Enable error interrupt                   */
#endif

#if ((TIRM48_CAN_RX_INTERRUPT_EN > 0) || \
     (TIRM48_CAN_TX_INTERRUPT_EN > 0) || \
     (TIRM48_CAN_NS_INTERRUPT_EN > 0))
    dev->Reg->CTL |= TIRM48_CAN_REG_CTL_IE0_SET;      /* Enable interrupt line 0                  */
    TIRM48CAN_BSP_IntCfg(arg);                        /* Configure interrupts                     */
#endif

    dev->Reg->TIOC = TIRM48_CAN_REG_TIOC_FUNC_SET;    /* Set Tx pin to functional mode            */
    dev->Reg->RIOC = TIRM48_CAN_REG_RIOC_FUNC_SET;    /* Set Rx pin to functional mode            */
    
    return (0);                                       /* Return function result                   */
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    OPEN CAN DEVICE
*
* \ingroup  TIRM48_CAN
*
*           Unlocks the device, i.e. IoCtl/Read/Write-function will take effect.
*
* \param    drv      the bus node name which must be used by the interrupt routine to access the
*                    CAN bus layer.
* \param    devName  the CAN device name
* \param    mode     the mode in which the CAN device will be used
*
* \return   the device identifier for further access or -1 if an error occurred
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S TIRM48CANOpen (CPU_INT16S  drv,
                          CPU_INT32U  devName,
                          CPU_INT16U  mode)
{
    TIRM48_CAN_DEV *dev;
    CPU_INT16S      result;
    CPU_SR_ALLOC();
    

#if TIRM48_CAN_ARG_CHK_CFG > 0
    if (devName >= TIRM48_CAN_DEV_N) {
        DrvError = TIRM48_CAN_BUS_ERR;
        return (-1);
    }
    if (mode != DEV_RW) {
        DrvError = TIRM48_CAN_MODE_ERR;
        return (-1);
    }
#else
    (void)mode;                                       /* Prevent compiler warning                 */
#endif

    dev = &CanDevTbl[devName];
    
    CPU_CRITICAL_ENTER();
    if (dev->Use == 0) {
        dev->Use = 1;
#if ((TIRM48_CAN_RX_INTERRUPT_EN > 0) || \
     (TIRM48_CAN_TX_INTERRUPT_EN > 0) || \
     (TIRM48_CAN_NS_INTERRUPT_EN > 0))
        TIRM48CAN_BSP_SetDevIds(drv,
                                devName);
#else
        (void)drv;                                    /* Prevent compiler warning                 */
#endif
        result   = (CPU_INT16S)devName;
    } else {
        DrvError = TIRM48_CAN_OPEN_ERR;
        result   = -1;
    }
    CPU_CRITICAL_EXIT();

    return (result);                                  /* Return function result                   */
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    CLOSE CAN DEVICE
*
* \ingroup  TIRM48_CAN
*
*           Locks the device, i.e. IoCtl/Read/Write-function will have no effect.
*
* \param    devId  the device identifier, returned by XXXCANOpen()
*
* \return   error code (0 if OK, -1 if an error occurred)
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S TIRM48CANClose (CPU_INT16S  devId)
{
    TIRM48_CAN_DEV *dev;
    CPU_INT16S      result;
    CPU_SR_ALLOC();
    
    
#if TIRM48_CAN_ARG_CHK_CFG > 0
    if ((devId <  0) ||
        (devId >= TIRM48_CAN_DEV_N)) {
        DrvError = TIRM48_CAN_BUS_ERR;
        return (-1);
    }
#endif

    dev = &CanDevTbl[devId];

    CPU_CRITICAL_ENTER();
    if (dev->Use == 1) {
        dev->Use = 0;
        result   = TIRM48_CAN_NO_ERR;
    } else {
        DrvError = TIRM48_CAN_CLOSE_ERR;
        result   = -1;
    }
    CPU_CRITICAL_EXIT();

    return (result);                                  /* Return function result                   */
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    CAN I/O CONTROL
*
* \ingroup  TIRM48_CAN
*
*           This function performs a special action on the opened device. The function code func
*           defines what the caller wants to do. Description of function codes as defined in
*           header file.
*
* \param    devId  device identifier, returned by XXXCANOpen()
* \param    func   function code
* \param    argp   argument list, specific to the function code
*
* \return   error code (0 if OK, -1 if an error occurred)
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S TIRM48CANIoCtl (CPU_INT16S  devId,
                           CPU_INT16U  func,
                           void       *argp)
{
    TIRM48_CAN_DEV *dev;
    CPU_INT08U      i;
    CPU_INT32U      regVal;
    CPU_INT32U      regIdx;
    CPU_INT32U      bitIdx;
    CPU_INT32U      mask;
    CPU_INT32U      canId;    
    CPU_INT16S      result = 0;
    CPU_SR_ALLOC();
    
    result = TIRM48_CAN_NO_ERR;

#if TIRM48_CAN_ARG_CHK_CFG > 0
    if ((devId <  0) ||
        (devId >= TIRM48_CAN_DEV_N)) {
        DrvError = TIRM48_CAN_BUS_ERR;
        return (-1);
    }
#endif

    dev = &CanDevTbl[devId];

    if (dev->Use == 0) {
        DrvError = TIRM48_CAN_OPEN_ERR;
        return (-1);
    }

    CPU_CRITICAL_ENTER();

    switch (func) {
                                                      /*------------------------------------------*/
        case IO_TIRM48_CAN_GET_IDENT:                 /* GET DRIVER IDENT CODE                    */
                                                      /*------------------------------------------*/
            (*(CPU_INT32U*)argp) = DrvIdent;
            break;
                                                      /*------------------------------------------*/
        case IO_TIRM48_CAN_GET_ERRNO:                 /* GET DRIVER ERRORCODE                     */
                                                      /*------------------------------------------*/
            (*(CPU_INT16U*)argp) = DrvError;
            break;
                                                      /*------------------------------------------*/
        case IO_TIRM48_CAN_GET_DRVNAME:               /* GET DRIVER NAME                          */
                                                      /*------------------------------------------*/
            (*(CPU_INT08U**)argp) = (CPU_INT08U *)TIRM48_CAN_NAME;
            break;
                                                      /*------------------------------------------*/
        case IO_TIRM48_CAN_SET_BAUDRATE:              /* SET BAUDRATE                             */
                                                      /*------------------------------------------*/
            dev->Baudrate = *(CPU_INT32U *)argp;

            result = TIRM48CAN_BSP_CalcBitTimingReg(dev);
            if (result == TIRM48_CAN_NO_ERR) {
                dev->Reg->CTL |=  (TIRM48_CAN_REG_CTL_INIT_SET |
                                   TIRM48_CAN_REG_CTL_CCE_SET);
                while ((dev->Reg->CTL & TIRM48_CAN_REG_CTL_INIT_SET)
                                     != TIRM48_CAN_REG_CTL_INIT_SET) {
                }
                TIRM48CAN_SetBitTimingReg(dev);
                dev->Reg->CTL &= ~(TIRM48_CAN_REG_CTL_INIT_SET |
                                   TIRM48_CAN_REG_CTL_CCE_SET);
                while ((dev->Reg->CTL & TIRM48_CAN_REG_CTL_INIT_SET)
                                     == TIRM48_CAN_REG_CTL_INIT_SET) {
                }                
            } else {
                DrvError = TIRM48_CAN_ARG_ERR;
                result   = -1;
            }
            break;
                                                      /*------------------------------------------*/
        case IO_TIRM48_CAN_START:                     /* ENABLE BUS                               */
                                                      /*------------------------------------------*/
            dev->Reg->CTL &= ~TIRM48_CAN_REG_CTL_INIT_SET;
            while ((dev->Reg->CTL & TIRM48_CAN_REG_CTL_INIT_SET) 
                                 == TIRM48_CAN_REG_CTL_INIT_SET) {
            }
            break;
                                                      /*------------------------------------------*/
        case IO_TIRM48_CAN_STOP:                      /* DISABLE BUS                              */
                                                      /*------------------------------------------*/
            while (dev->Reg->TXRQX != 0) {            /* Wait while transmission is pending       */
            }
            dev->Reg->CTL |=  TIRM48_CAN_REG_CTL_INIT_SET;
            while ((dev->Reg->CTL & TIRM48_CAN_REG_CTL_INIT_SET) 
                                 != TIRM48_CAN_REG_CTL_INIT_SET) {
            }
            break;
                                                      /*------------------------------------------*/
        case IO_TIRM48_CAN_RX_STANDARD:               /* SET RECEIVER TO STANDARD IDENTIFIER      */
                                                      /*------------------------------------------*/
            for (i = dev->Cfg->RxFirst; i <= dev->Cfg->RxLast; i++) {
                dev->Reg->IFx[0].CMD  =  0x20;        /* RD, Arb                                  */
                dev->Reg->IFx[0].NBR  =  i;
                while ((dev->Reg->IFx[0].STAT & TIRM48_CAN_REG_IF_STAT_BUSY_SET)
                                             == TIRM48_CAN_REG_IF_STAT_BUSY_SET) {
                }
                dev->Reg->IFx[0].ARB &= ~TIRM48_CAN_REG_IF_ARB_XTD_SET;
                dev->Reg->IFx[0].CMD  =  0xA0;        /* WR, Arb                                  */
                dev->Reg->IFx[0].NBR  =  i;
                while ((dev->Reg->IFx[0].STAT & TIRM48_CAN_REG_IF_STAT_BUSY_SET)
                                             == TIRM48_CAN_REG_IF_STAT_BUSY_SET) {
                }
            }
            break;
                                                      /*------------------------------------------*/
        case IO_TIRM48_CAN_RX_EXTENDED:               /* SET RECEIVER TO EXTENDED IDENTIFIER      */
                                                      /*------------------------------------------*/
            for (i = dev->Cfg->RxFirst; i <= dev->Cfg->RxLast; i++) {
                dev->Reg->IFx[0].CMD  = 0x20;         /* RD, Arb                                  */
                dev->Reg->IFx[0].NBR  = i;
                while ((dev->Reg->IFx[0].STAT & TIRM48_CAN_REG_IF_STAT_BUSY_SET)
                                             == TIRM48_CAN_REG_IF_STAT_BUSY_SET) {
                }
                dev->Reg->IFx[0].ARB |= TIRM48_CAN_REG_IF_ARB_XTD_SET;
                dev->Reg->IFx[0].CMD  = 0xA0;         /* WR, Arb                                  */
                dev->Reg->IFx[0].NBR  = i;
                while ((dev->Reg->IFx[0].STAT & TIRM48_CAN_REG_IF_STAT_BUSY_SET)
                                             == TIRM48_CAN_REG_IF_STAT_BUSY_SET) {
                }
            }
            break;
                                                      /*------------------------------------------*/                                    
        case IO_TIRM48_CAN_TX_READY:                  /* GET TX READY STATUS                      */
                                                      /*------------------------------------------*/
            regIdx = (dev->Cfg->TxMsgBox - 1) >> 5;
            bitIdx = 1 << ((dev->Cfg->TxMsgBox - 1) & 0x1F);
            if ((dev->Reg->TXRQx[regIdx] & bitIdx) != 0) {
                (*(CPU_INT08U*)argp) = 0; 
            } else {
                (*(CPU_INT08U*)argp) = 1;
            }
            break;
                                                      /*------------------------------------------*/
        case IO_TIRM48_CAN_GET_NODE_STATUS:           /* GET NODE STATUS                          */
                                                      /*------------------------------------------*/
            regVal = dev->Reg->ES;
            if ((regVal & TIRM48_CAN_REG_ES_BOFF_SET)           /* Bus-off state                  */
                       == TIRM48_CAN_REG_ES_BOFF_SET) {
                (*(CPU_INT08U *)argp) = 2;
            } else if ((regVal & TIRM48_CAN_REG_ES_EPASS_SET)   /* Error passive state            */
                              == TIRM48_CAN_REG_ES_EPASS_SET) {
                (*(CPU_INT08U *)argp) = 1;
            } else {                                            /* Bus active                     */
                (*(CPU_INT08U *)argp) = 0;
            }
            break;
                                                      /*------------------------------------------*/
        case IO_TIRM48_CAN_SET_RX_FILTER:             /* SET RX FILTER                            */
                                                      /*------------------------------------------*/
            mask  = ((CPU_INT32U*)argp)[0];
            canId = ((CPU_INT32U*)argp)[1];
            
            if (canId > 0x7FF) {                      /* Extended ID                              */
                dev->Reg->IFx[0].MSK = mask & 0x1FFFFFFF;
                dev->Reg->IFx[0].ARB = ((canId & 0x1FFFFFFF) |
                                        TIRM48_CAN_REG_IF_ARB_XTD_SET);
            } else {                                  /* Standard ID                              */
                dev->Reg->IFx[0].MSK = (mask & 0x7FF) << 18;
                dev->Reg->IFx[0].ARB = canId << 18;
            }
            
            dev->Reg->IFx[0].MSK |= TIRM48_CAN_REG_IF_MSK_MXTD_SET;
            dev->Reg->IFx[0].ARB |= TIRM48_CAN_REG_IF_ARB_MSGVAL_SET;
            
            for (i = dev->Cfg->RxFirst; i <= dev->Cfg->RxLast; i++) {
                dev->Reg->IFx[0].CMD = 0xE0;          /* WR, Mask, Arb                            */
                dev->Reg->IFx[0].NBR = i;
                while ((dev->Reg->IFx[0].STAT & TIRM48_CAN_REG_IF_STAT_BUSY_SET)
                                             == TIRM48_CAN_REG_IF_STAT_BUSY_SET) {
                }
            }
            break;       
                                                      /*------------------------------------------*/
        default:                                      /* WRONG FUNCTION CODE                      */
                                                      /*------------------------------------------*/
            DrvError = TIRM48_CAN_FUNC_ERR;
            result   = -1;
            break;
    }
    
    CPU_CRITICAL_EXIT();
    
    return (result);                                  /* Return function result                   */
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    CAN READ DATA
*
* \ingroup  TIRM48_CAN
*
*           Read a received CAN frame from a message buffer. The buffer must have space for only
*           one CAN frame.
*
* \param    devId  device identifier, returned by XXXCANOpen()
* \param    buf    pointer to CAN frame
* \param    size   CAN frame size
*
* \return   error code (CAN frame size if OK, -1 if an error occurred)
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S TIRM48CANRead (CPU_INT16S  devId,
                          CPU_INT08U *buf,
                          CPU_INT16U  size)
{
    TIRM48_CAN_DEV *dev;
    TIRM48_CAN_FRM *frm;
    CPU_INT08U      i;
    CPU_INT32U      regIdx;
    CPU_INT32U      bitIdx;
    CPU_SR_ALLOC();
    
    
#if TIRM48_CAN_ARG_CHK_CFG > 0
    if ((devId <  0) ||
        (devId >= TIRM48_CAN_DEV_N)) {
        DrvError = TIRM48_CAN_BUS_ERR;
        return (-1);
    }
    if (buf == (CPU_INT08U *)0) {
        DrvError = TIRM48_CAN_ARG_ERR;
        return (-1);
    }
    if (size != sizeof(TIRM48_CAN_FRM)) {
        DrvError = TIRM48_CAN_ARG_ERR;
        return (-1);
    }
#endif

    dev = &CanDevTbl[devId];
    
    if (dev->Use == 0) {
        DrvError = TIRM48_CAN_OPEN_ERR;
        return (-1);
    }

    frm = (TIRM48_CAN_FRM *)buf;
       
    CPU_CRITICAL_ENTER();
    
    for (i = dev->Cfg->RxFirst; i <= dev->Cfg->RxLast; i++) {
        regIdx = (i - 1) >> 5;
        bitIdx = 1 << ((i - 1) & 0x1F);
        if ((dev->Reg->NWDATx[regIdx] & bitIdx) != 0) {
            break;
        }
    }
    
    if (i > dev->Cfg->RxLast) {
        CPU_CRITICAL_EXIT();
        DrvError = TIRM48_CAN_NO_DATA_ERR;
        return (-1);
    }
    
    dev->Reg->IFx[0].CMD = 0x3F;                      /* RD, Arb, Control, ClrIntPnd, NewDat, Data A, Data B */
    dev->Reg->IFx[0].NBR = i;    
    while ((dev->Reg->IFx[0].STAT & TIRM48_CAN_REG_IF_STAT_BUSY_SET)
                                 == TIRM48_CAN_REG_IF_STAT_BUSY_SET) {
    }
    
    if ((dev->Reg->IFx[0].ARB & TIRM48_CAN_REG_IF_ARB_XTD_SET)      /* Extended ID                */
                             == TIRM48_CAN_REG_IF_ARB_XTD_SET) {
        frm->Identifier  = ((dev->Reg->IFx[0].ARB & 0x1FFFFFFF) |
                            TIRM48_CAN_EXT_ID_FLAG);
    } else {                                                        /* Standard ID                */
        frm->Identifier  = ((dev->Reg->IFx[0].ARB >> 18) & 0x7FF);
    }
    
    if ((dev->Reg->IFx[0].ARB & TIRM48_CAN_REG_IF_ARB_DIR_SET)      /* Remote frame               */
                             == TIRM48_CAN_REG_IF_ARB_DIR_SET) {
        frm->Identifier |= TIRM48_CAN_RTR_ID_FLAG;
    }
    
    frm->DLC = dev->Reg->IFx[0].MCTL & 0x0F;          /* Get DLC                                  */
    
    for (i = 0; i < frm->DLC; i++) {                  /* Get data                                 */
#if CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_LITTLE
        frm->Data[i] = dev->Reg->IFx[0].DATx[i]; 
#else
        frm->Data[i] = dev->Reg->IFx[0].DATx[CanByteOrder[i]];
#endif
    }
    
    CPU_CRITICAL_EXIT();
    
    return (size);                                    /* Return function result                   */
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    CAN WRITE DATA
*
* \ingroup  TIRM48_CAN
*
*           Write a CAN frame to a message buffer. The buffer must contain only one CAN frame.
*
* \param    devId  device identifier, returned by XXXCANOpen()
* \param    buf    pointer to CAN frame
* \param    size   CAN frame size
*
* \return   error code (CAN frame size if OK, -1 if an error occurred)
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT16S TIRM48CANWrite (CPU_INT16S  devId,
                           CPU_INT08U *buf,
                           CPU_INT16U  size)
{
    TIRM48_CAN_DEV *dev;
    TIRM48_CAN_FRM *frm;
    CPU_INT08U      i;
    CPU_INT32U      regIdx;
    CPU_INT32U      bitIdx;
    CPU_SR_ALLOC();

#if TIRM48_CAN_ARG_CHK_CFG > 0
    if ((devId <  0) ||
        (devId >= TIRM48_CAN_DEV_N)) {
        DrvError = TIRM48_CAN_BUS_ERR;
        return (-1);
    }
    if (buf == (CPU_INT08U *)0) {
        DrvError = TIRM48_CAN_ARG_ERR;
        return (-1);
    }
    if (size != sizeof(TIRM48_CAN_FRM)) {
        DrvError = TIRM48_CAN_ARG_ERR;
        return (-1);
    }
#endif

    dev = &CanDevTbl[devId];
    
    if (dev->Use == 0) {
        DrvError = TIRM48_CAN_OPEN_ERR;
        return (-1);
    }
    
    frm = (TIRM48_CAN_FRM *)buf;

    CPU_CRITICAL_ENTER();
    
    regIdx = (dev->Cfg->TxMsgBox - 1) >> 5;
    bitIdx = 1 << ((dev->Cfg->TxMsgBox - 1) & 0x1F);
    if ((dev->Reg->TXRQx[regIdx] & bitIdx) != 0) {
        CPU_CRITICAL_EXIT(); 
        DrvError = TIRM48_CAN_BUSY_ERR;
        return (-1);
    }
    
    if (frm->Identifier > 0x7FF) {                    /* Extended ID                              */
        dev->Reg->IFx[0].ARB = ((frm->Identifier & 0x1FFFFFFF) |
                                TIRM48_CAN_REG_IF_ARB_XTD_SET);
    } else {                                          /* Standard ID                              */
        dev->Reg->IFx[0].ARB = frm->Identifier << 18;
    }    
    dev->Reg->IFx[0].ARB |= (TIRM48_CAN_REG_IF_ARB_MSGVAL_SET |
                             TIRM48_CAN_REG_IF_ARB_DIR_SET);
    
    if (frm->DLC > 8) {                               /* Limit DLC to 8 bytes                     */
        frm->DLC = 8;
    }
    
    dev->Reg->IFx[0].MCTL  = (frm->DLC |              /* Set DLC                                  */
                              TIRM48_CAN_REG_IF_MCTL_EOB_SET);
#if TIRM48_CAN_TX_INTERRUPT_EN > 0
    dev->Reg->IFx[0].MCTL |=  TIRM48_CAN_REG_IF_MCTL_TXIE_SET;
#endif
    
    for (i = 0; i < frm->DLC; i++) {                  /* Set data                                 */
#if CPU_CFG_ENDIAN_TYPE == CPU_ENDIAN_TYPE_LITTLE
        dev->Reg->IFx[0].DATx[i]               = frm->Data[i];
#else
        dev->Reg->IFx[0].DATx[CanByteOrder[i]] = frm->Data[i];
#endif
    }

    dev->Reg->IFx[0].CMD = 0xB7;                      /* WR, Arb, Control, TxRqst, Data A, Data B */
    dev->Reg->IFx[0].NBR = dev->Cfg->TxMsgBox;                            
    while ((dev->Reg->IFx[0].STAT & TIRM48_CAN_REG_IF_STAT_BUSY_SET)
                                 == TIRM48_CAN_REG_IF_STAT_BUSY_SET) {
    }

    CPU_CRITICAL_EXIT();

    return (size);                                    /* Return function result                   */
}

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    SET BIT TIMING REGISTER VALUES
*
* \ingroup  TIRM48_CAN
*
*           Set bit timing register values.
*
* \param    dev  pointer to device
*/
/*------------------------------------------------------------------------------------------------*/
static void TIRM48CAN_SetBitTimingReg (TIRM48_CAN_DEV *dev)
{
    dev->Reg->BTR = ((dev->PSEG2 << 12) |
                     (dev->PSEG1 <<  8) |
                     (dev->RJW   <<  6) |
                     (dev->PRESDIV));
}
