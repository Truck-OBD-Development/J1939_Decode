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
* Filename      : can_drv.h
* Version       : V2.42.00
* Programmer(s) : E0
* Purpose       : This include file defines the CAN low-level device driver interface.
****************************************************************************************************
*/

#ifndef _CAN_DRV_H_
#define _CAN_DRV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------------------------*/
/*! \brief                          I/O CONTROL FUNCTIONCODES
*
*            This enumeration defines the required functioncode values for the lowlevel
*            device driver function IoCtl().
*/
/*------------------------------------------------------------------------------------------------*/
enum CANDRV_IOCTL_FUNC {
    /*! \brief Set Baudrate
     *
     * This enum value is the functioncode to set the baudrate of the CAN controller interface.
     *
     * The parameter pointer shall point to an CPU_INT32U variable, which holds the baudrate
     * in bit/s.
     */
    CAN_SET_BAUDRATE = 0,
    /*! \brief Enable Bus
     *
     * This enum value is the functioncode to start the CAN controller interface. Most common
     * is to set the CAN controller in active mode.
     *
     * The parameter pointer is not used for this function.
     */
    CAN_START,
    /*! \brief Disable Bus
     *
     * This enum value is the functioncode to stop the CAN controller interface. Most common
     * is to set the CAN controller in passive mode.
     *
     * The parameter pointer is not used for this function.
     */
    CAN_STOP,
    /*! \brief Set Receiver to Standard Identifier
     *
     * This enum value is the functioncode to configure the CAN receiver to receive only
     * CAN standard identifiers.
     *
     * The parameter pointer is not used for this function.
     */
    CAN_RX_STANDARD,
    /*! \brief Set Receiver to Extended Identifier
     *
     * This enum value is the functioncode to configure the CAN receiver to receive only
     * CAN extended identifiers.
     *
     * The parameter pointer is not used for this function.
     */
    CAN_RX_EXTENDED,
    /*! \brief Get TX Buffer Status
     *
     * This enum value is the functioncode to get the status of the current transmit
     * buffer.
     *
     * The parameter pointer shall point to a CPU_INT08U variable, where the status
     * shall be written to.
     */
    CAN_TX_READY,
    /*! \brief Get Node Status
     *
     * This enum value is the functioncode to get the node status from the
     * CAN controller.
    *
    * The parameter pointer shall point to a CPU_INT08U variable, where the status
    * shall be written to.
     */
    CAN_GET_NODE_STATUS,

    /*! \brief Number of Needed IO Function Codes
     *
     * This enum value holds the number of function codes, which are used within the
     * can bus layer.
     */
    CAN_IO_FUNC_N
};

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef _CAN_DRV_H_ */

