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
*                                    MICRIUM BOARD SUPPORT PACKAGE
*
*                                          Texas Instruments
*                                 RM48x Hercules Development Kit(HDK)
*
* Filename      : bsp_cfg.h
* Version       : V1.00
* Programmer(s) : FF
*********************************************************************************************************
*/

#ifndef  BSP_CFG_H
#define  BSP_CFG_H


/*
*********************************************************************************************************
*                                            MODULES ENABLE
*********************************************************************************************************
*/

#define  BSP_CFG_CAN_EN                     0    /* Enable (1) or Disable (0) uC/CAN                   */
#define  BSP_CFG_CAN_OPEN_EN                0    /* Enable (1) or Disable (0) uC/CANopen               */
#define  BSP_CFG_FS_EN                      0    /* Enable (1) or Disable (0) uC/FS                    */
#define  BSP_CFG_GUI_EN                     0    /* Enable (1) or Disable (0) uC/GUI                   */
#define  BSP_CFG_MBM_EN                     0    /* Enable (1) or Disable (0) uC/Modbus-Master         */
#define  BSP_CFG_MBS_EN                     0    /* Enable (1) or Disable (0) uC/Modbus-Slave          */
#define  BSP_CFG_NET_EN                     0    /* Enable (1) or Disable (0) uC/TCP-IP                */
#define  BSP_CFG_OS2_EN                     0    /* Enable (1) or Disable (0) uC/OS-II                 */
#define  BSP_CFG_OS3_EN                     1    /* Enable (1) or Disable (0) uC/OS-III                */
#define  BSP_CFG_USBD_EN                    0    /* Enable (1) or Disable (0) uC/USB-D                 */
#define  BSP_CFG_USBH_EN                    0    /* Enable (1) or Disable (0) uC/USB-H                 */

/*
*********************************************************************************************************
*                                        INTERRUPT VECTOR TABLE
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          CLOCK MANAGEMENT
*********************************************************************************************************
*/

#define  BSP_CFG_SYS_EXT_CLK_FREQ    16000000uL

/*
*********************************************************************************************************
*                                        BOARD SPECIFIC BSPs
*********************************************************************************************************
*/

#define  BSP_CFG_SER_EN                     0    /* Enable (1) or Disable (0) Serial port BSP          */

#endif
