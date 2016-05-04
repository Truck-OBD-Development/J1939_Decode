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
* Filename      : drv_can.h
* Version       : V2.42.00
* Programmer(s) : E0
****************************************************************************************************
*/

#ifndef _DRV_CAN_H_
#define _DRV_CAN_H_

/*
****************************************************************************************************
*                                             INCLUDES
****************************************************************************************************
*/

#include "cpu.h"
#include "drv_can_reg.h"

/*
****************************************************************************************************
*                                             DEFINES
****************************************************************************************************
*/

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    DRIVER NAME
*
* \ingroup  TIRM48_CAN
*
*           Unique driver name for installation and searching.
*/
/*------------------------------------------------------------------------------------------------*/
#define TIRM48_CAN_NAME         "TIRM48:CAN Module"

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    EXTENDED ID FLAG
*
* \ingroup  TIRM48_CAN
*
*           This flag must be set in the CAN identifier to mark an extended ID.
*
* \see      TIRM48_CAN_FRM
*/
/*------------------------------------------------------------------------------------------------*/
#define TIRM48_CAN_EXT_ID_FLAG  0x20000000

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    REMOTE FRAME FLAG
*
* \ingroup  TIRM48_CAN
*
*           This flag must be set in the CAN identifier to mark a remote frame.
*
* \see      TIRM48_CAN_FRM
*/
/*------------------------------------------------------------------------------------------------*/
#define TIRM48_CAN_RTR_ID_FLAG  0x40000000

/*
****************************************************************************************************
*                                            DATA TYPES
****************************************************************************************************
*/

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    DEVICE NAMES
*
* \ingroup  TIRM48_CAN
*
*           This enum defines the available device names for the driver XXXCANInit() function.
*/
/*------------------------------------------------------------------------------------------------*/
enum {
    TIRM48_CAN_DCAN1 = 0,                          /*!< DCAN1                                     */
    TIRM48_CAN_DCAN2,                              /*!< DCAN2                                     */
    TIRM48_CAN_DCAN3,                              /*!< DCAN3                                     */
    TIRM48_CAN_DEV_N                               /*!< Number of devices                         */
};

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    ERROR CODES
*
* \ingroup  TIRM48_CAN
*
*           This enum defines the possible error codes.
*/
/*------------------------------------------------------------------------------------------------*/
enum {
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    NO ERROR
    *
    *           This code is used if everything is OK.
    */
    /*--------------------------------------------------------------------------------------------*/
    TIRM48_CAN_NO_ERR = 0,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    BUS ERROR
    *
    *           This code indicates, that a wrong bus was chosen.
    */
    /*--------------------------------------------------------------------------------------------*/
    TIRM48_CAN_BUS_ERR,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    BUSY ERROR
    *
    *           This code indicates, that a message cannot be sent because the bus is busy.
    */
    /*--------------------------------------------------------------------------------------------*/
    TIRM48_CAN_BUSY_ERR,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    INIT ERROR
    *
    *           This code indicates, that the devices were not initialized because they are not in reset state.
    */
    /*--------------------------------------------------------------------------------------------*/
    TIRM48_CAN_INIT_ERR,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    MODE ERROR
    *
    *           This code indicates, that the device cannot be accessed with the wanted mode.
    */
    /*--------------------------------------------------------------------------------------------*/
    TIRM48_CAN_MODE_ERR,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    OPEN ERROR
    *
    *           This code indicates, that a device cannot be used because it is not opened.
    */
    /*--------------------------------------------------------------------------------------------*/
    TIRM48_CAN_OPEN_ERR,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    CLOSE ERROR
    *
    *           This code indicates, that the device cannot be closed.
    */
    /*--------------------------------------------------------------------------------------------*/
    TIRM48_CAN_CLOSE_ERR,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    FUNCTION CODE ERROR
    *
    *           This code indicates, that the given function code is not valid.
    */
    /*--------------------------------------------------------------------------------------------*/
    TIRM48_CAN_FUNC_ERR,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    ARGUMENT ERROR
    *
    *           This code indicates, that an argument check has failed.
    */
    /*--------------------------------------------------------------------------------------------*/
    TIRM48_CAN_ARG_ERR,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    NO DATA ERROR
    *
    *           This code indicates, that no data is available.
    */
    /*--------------------------------------------------------------------------------------------*/
    TIRM48_CAN_NO_DATA_ERR
};

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    I/O CONTROL FUNCTION CODES
*
* \ingroup  TIRM48_CAN
*
*           This enum defines the available function codes for the driver XXXIoCtl() function.
*/
/*------------------------------------------------------------------------------------------------*/
enum {
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    GET DRIVER IDENT CODE
    *
    *           This standard function code gets the driver identification code.
    *
    *           arg = pointer to local variable (CPU_INT32U *)
    */
    /*--------------------------------------------------------------------------------------------*/
    IO_TIRM48_CAN_GET_IDENT    = 0x0,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    GET DRIVER ERRORCODE
    *
    *           This standard function code gets the driver errorcode.
    *
    *           arg = pointer to local variable (CPU_INT16U *)
    */
    /*--------------------------------------------------------------------------------------------*/
    IO_TIRM48_CAN_GET_ERRNO,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    GET DRIVER NAME
    *
    *           This standard function code gets the (human readable) driver name.
    *
    *           arg = pointer to local variable (char *)
    */
    /*--------------------------------------------------------------------------------------------*/
    IO_TIRM48_CAN_GET_DRVNAME,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    SET BAUDRATE
    *
    *           This function code sets the baudrate.
    *
    *           arg = pointer to local variable (CPU_INT32U *)
    */
    /*--------------------------------------------------------------------------------------------*/
    IO_TIRM48_CAN_SET_BAUDRATE = 0x10,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    ENABLE BUS
    *
    *           This function code starts the CAN controller.
    *
    *           arg = unused
    */
    /*--------------------------------------------------------------------------------------------*/
    IO_TIRM48_CAN_START,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    DISABLE BUS
    *
    *           This function code stops the CAN controller.
    *
    *           arg = unused
    */
    /*--------------------------------------------------------------------------------------------*/
    IO_TIRM48_CAN_STOP,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    SET RECEIVER TO STANDARD IDENTIFIER
    *
    *           This function code configures the CAN receiver to receive only CAN standard
    *           identifiers.
    *
    *           arg = unused
    */
    /*--------------------------------------------------------------------------------------------*/
    IO_TIRM48_CAN_RX_STANDARD,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    SET RECEIVER TO EXTENDED IDENTIFIER
    *
    *           This function code configures the CAN receiver to receive only CAN extended
    *           identifiers.
    *
    *           arg = unused
    */
    /*--------------------------------------------------------------------------------------------*/
    IO_TIRM48_CAN_RX_EXTENDED,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    GET TX READY STATUS
    *
    *           This function code gets the Tx ready status.
    *
    *           0 = Tx not ready
    *           1 = Tx ready
    *
    *           arg = pointer to local variable (CPU_INT08U *)
    */
    /*--------------------------------------------------------------------------------------------*/
    IO_TIRM48_CAN_TX_READY,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    GET NODE STATUS
    *
    *           This function code gets the node status.
    *
    *           0 = Bus active
    *           1 = Error passive state
    *           2 = Bus-off state
    *
    *           arg = pointer to local variable (CPU_INT08U *)
    */
    /*--------------------------------------------------------------------------------------------*/
    IO_TIRM48_CAN_GET_NODE_STATUS,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    SET RX FILTER
    *
    *           This function code sets the acceptance filter for the CAN controller.
    *
    *           arg = pointer to local variable (CPU_INT32U[2])
    *           
    *           array[0] = mask
    *           array[1] = identifier
    */
    /*--------------------------------------------------------------------------------------------*/
    IO_TIRM48_CAN_SET_RX_FILTER,
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    NUMBER OF FUNCTION CODES
    *
    *           Number of function codes.
    */
    /*--------------------------------------------------------------------------------------------*/
    IO_TIRM48_CAN_IO_FUNC_N
};

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    DEVICE CONFIGURATION
*
* \ingroup  TIRM48_CAN
*
*           This structure defines the configuration of a device.
*/
/*------------------------------------------------------------------------------------------------*/
typedef struct {
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    TX MESSAGE BOX
    *
    *           This member holds the number of the Tx message box.
    */
    /*--------------------------------------------------------------------------------------------*/
    CPU_INT08U  TxMsgBox;
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    FIRST RX MESSAGE BOX
    *
    *           This member holds the number of the first Rx message box.
    */
    /*--------------------------------------------------------------------------------------------*/
    CPU_INT08U  RxFirst;
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    LAST RX MESSAGE BOX
    *
    *           This member holds the number of the last Rx message box.
    */
    /*--------------------------------------------------------------------------------------------*/
    CPU_INT08U  RxLast;
} TIRM48_CAN_CFG;

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    DEVICE
*
* \ingroup  TIRM48_CAN
*
*           This structure defines a device.
*/
/*------------------------------------------------------------------------------------------------*/
typedef struct {
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    USE MARKER
    *
    *           This member holds a marker which indicates if this device is in use:
    *           0 = Device idle
    *           1 = Device in use
    */
    /*--------------------------------------------------------------------------------------------*/
    CPU_INT08U      Use;
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    POINTER TO DEVICE CONFIGURATION
    *
    *           This member holds a pointer to the device configuration.
    */
    /*--------------------------------------------------------------------------------------------*/
    TIRM48_CAN_CFG *Cfg;
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    POINTER TO DEVICE REGISTERS
    *
    *           This member holds a pointer to the device registers.
    */
    /*--------------------------------------------------------------------------------------------*/
    TIRM48_CAN_REG *Reg;     
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    BAUDRATE
    *
    *           This member holds the baudrate.
    */
    /*--------------------------------------------------------------------------------------------*/
    CPU_INT32U      Baudrate;
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    BIT SAMPLE POINT
    *
    *           This member holds the bit sample point in 1/10 percent.
    */
    /*--------------------------------------------------------------------------------------------*/
	CPU_INT32U      SamplePoint;
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    RE-SYNCHRONIZATION JUMP WIDTH
    *
    *           This member holds the Re-synchronization Jump Width in 1/10 percent.
    */
    /*--------------------------------------------------------------------------------------------*/
	CPU_INT32U      ResynchJumpWith;
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    PRESCALER DEVIDE FACTOR
    *
    *           This member holds the prescaler devide factor.
    */
    /*--------------------------------------------------------------------------------------------*/
	CPU_INT08U      PRESDIV;
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    RE-SYNCHRONIZATION JUMP WIDTH
    *
    *           This member holds the Re-synchronization Jump Width (StdValue = 1).
    */
    /*--------------------------------------------------------------------------------------------*/
	CPU_INT08U      RJW;
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    PROPAGATION SEGMENT TIME
    *
    *           This member holds the propagation segment time (StdValue = 2).
    */
    /*--------------------------------------------------------------------------------------------*/
	CPU_INT08U      PROPSEG;
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    PHASE BUFFER SEGMENT 1
    *
    *           This member holds the phase buffer segment 1 (StdValue = 7).
    */
    /*--------------------------------------------------------------------------------------------*/
	CPU_INT08U      PSEG1;
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    PHASE BUFFER SEGMENT 2
    *
    *           This member holds the phase buffer segment 2 (StdValue = 7).
    */
    /*--------------------------------------------------------------------------------------------*/
	CPU_INT08U      PSEG2;
} TIRM48_CAN_DEV;

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief    CAN FRAME
*
* \ingroup  TIRM48_CAN
*
*           This structure defines a CAN frame.
*/
/*------------------------------------------------------------------------------------------------*/
typedef struct {
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    CAN IDENTIFIER
    *
    *           This member holds the CAN identifier. NOTE: to differentiate standard and extended
    *           identifiers the following addition to the identifier is implemented:
    *
    *           - bit31:   reserved (always 0)
    *           - bit30:   marks a remote transmission request (1=rtr, 0=data frame)
    *           - bit29:   marks an extended identifier (1=extended, 0=standard)
    *           - bit28-0: the identifier (standard or extended)
    */
    /*--------------------------------------------------------------------------------------------*/
    CPU_INT32U Identifier;
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    CAN PAYLOAD
    *
    *           This member holds up to 8 bytes, which can be handled with a single CAN message.
    */
    /*--------------------------------------------------------------------------------------------*/
    CPU_INT08U Data[8];
    /*--------------------------------------------------------------------------------------------*/
    /*!
    * \brief    CAN DLC
    *
    *           This member holds the number of valid data bytes in the payload.
    */
    /*--------------------------------------------------------------------------------------------*/
    CPU_INT08U DLC;
} TIRM48_CAN_FRM;

/*
****************************************************************************************************
*                                       FUNCTION PROTOTYPES
****************************************************************************************************
*/

CPU_INT16S TIRM48CANInit  (CPU_INT32U arg);
CPU_INT16S TIRM48CANOpen  (CPU_INT16S drv, CPU_INT32U devName, CPU_INT16U mode);
CPU_INT16S TIRM48CANClose (CPU_INT16S devId);
CPU_INT16S TIRM48CANIoCtl (CPU_INT16S devId, CPU_INT16U func, void *arg);
CPU_INT16S TIRM48CANRead  (CPU_INT16S devId, CPU_INT08U *buf, CPU_INT16U size);
CPU_INT16S TIRM48CANWrite (CPU_INT16S devId, CPU_INT08U *buf, CPU_INT16U size);


#endif  /* #ifndef _DRV_CAN_H_ */

