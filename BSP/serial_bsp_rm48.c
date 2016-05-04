/*
*********************************************************************************************************
*                                     SERIAL (BYTE) COMMUNICATION
*
*                         (c) Copyright 2007-2014; Micrium, Inc.; Weston, FL
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
*                                          DEVICE DRIVER BSP
*
*                                          Texas Instruments
*                                 RM48x Hercules Development Kit(HDK)
*
* Filename      : serial_bsp_rm48.c
* Version       : V2.00.01
* Programmer(s) : NB
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <serial_bsp_rm48.h>
#include  <bsp_int.h>
#include  <bsp_sys.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define  SERIAL_INT_CH_LIN_01_LVL_00                    13u
                                                                /* ----------- REGISTER BASE SPECIFICATIONS ----------- */
#define  SERIAL_BSP_RM48_SCI1_BASE     ((void *)0xFFF7E400)


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void        SerialBSP_RM48_SCI1_ClkEn      (SERIAL_ERR   *perr);
static  void        SerialBSP_RM48_SCI1_ClkDis     (SERIAL_ERR   *perr);
static  void        SerialBSP_RM48_SCI1_CfgGPIO    (CPU_BOOLEAN   flow_ctrl,
                                                    SERIAL_ERR   *perr);
static  void        SerialBSP_RM48_SCI1_CfgInt     (SERIAL_DEV   *pdev,
                                                    SERIAL_ERR   *perr);
static  CPU_INT32U  SerialBSP_RM48_SCI1_ClkFreqGet (void);

static  void        SerialBSP_RM48_SCI1_IntHandler (void *p_arg);


/*
*********************************************************************************************************
*                                   SERIAL INTERFACE DEVICE BSP API
*********************************************************************************************************
*/

static  SERIAL_BSP_API  SerialBSP_RM48_SCI1 = {
    SerialBSP_RM48_SCI1_ClkEn,
    SerialBSP_RM48_SCI1_ClkDis,
    SerialBSP_RM48_SCI1_CfgGPIO,
    SerialBSP_RM48_SCI1_CfgInt,
    SerialBSP_RM48_SCI1_ClkFreqGet
};


/*
*********************************************************************************************************
*********************************************************************************************************
*                                      SERIAL INTERFACE DEVICES
*********************************************************************************************************
*********************************************************************************************************
*/

SERIAL_DEV_CFG  SerialDevCfg_RM48_SCI1 = {
     SERIAL_BSP_RM48_SCI1_BASE,
    &SerialDrv_RM48_API,
    &SerialBSP_RM48_SCI1
};

/*
*********************************************************************************************************
*                                   SERIAL INTERFACE DEVICE POINTER
*
* Note(s) : (1) A serial interface device pointer is required to be passed to the serial interface device
*               driver api ISR_Handler().
*********************************************************************************************************
*/

static  SERIAL_DEV  *SerialBSP_RM48_SCI1_DevPtr;


/*$PAGE*/
/*
*********************************************************************************************************
*                                       SerialBSP_RM48_SCI1_ClkEn()
*
* Description : Enable device/peripheral clock.
*
* Argument(s) : perr        Pointer to variable that will receive the return error code from this function :
*
*                               SERIAL_ERR_NONE                 Device/peripheral clock enabled successfully.
*
* Return(s)   : none.
*
* Caller(s)   : SerialDrv_Open() via 'pdev->BSP_API->ClkEn()'.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  SerialBSP_RM48_SCI1_ClkEn (SERIAL_ERR  *perr)
{
    BSP_SysPerClkEn(BSP_SYS_PER_CLK_NBR_PS_LIN_00);

   *perr = SERIAL_ERR_NONE;
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                     SerialBSP_RM48_SCI1_ClkDis()
*
* Description : Disable device/peripheral clock.
*
* Argument(s) : perr        Pointer to variable that will receive the return error code from this function :
*
*                               SERIAL_ERR_NONE                 Device/peripheral clock disabled successfully.
*
* Return(s)   : none.
*
* Caller(s)   : SerialDrv_Close() via 'pdev->BSP_API->ClkDis()'.
*
* Note(s)     : none.
*********************************************************************************************************
*/


static  void  SerialBSP_RM48_SCI1_ClkDis (SERIAL_ERR  *perr)
{
    BSP_SysPerClkDis(BSP_SYS_PER_CLK_NBR_PS_LIN_00);

   *perr = SERIAL_ERR_NONE;
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                     SerialBSP_RM48_SCI1_CfgGPIO()
*
* Description : Configure device/peripheral input/output pins.
*
* Argument(s) : flow_ctrl   Flow control enabled.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               SERIAL_ERR_NONE                 Device/peripheral GPIO configured successfully.
*                               SERIAL_ERR_DRV_INVALID          Device configuration invalid.
*
* Return(s)   : none.
*
* Caller(s)   : SerialDrv_Open() via 'pdev->BSP_API->CfgGPIO()'.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  SerialBSP_RM48_SCI1_CfgGPIO (CPU_BOOLEAN   flow_ctrl,
                                           SERIAL_ERR   *perr)
{
    (void)&flow_ctrl;

   *perr = SERIAL_ERR_NONE;
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                       SerialBSP_RM48_SCI1_CfgInt()
*
* Description : Configure device/peripheral interrupt.
*
* Argument(s) : pdev        Pointer to device.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               SERIAL_ERR_NONE                 Device/peripheral interrupt configured successfully.
*
* Return(s)   : none.
*
* Caller(s)   : SerialDrv_Open() via 'pdev->BSP_API->CfgInt()'.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  SerialBSP_RM48_SCI1_CfgInt (SERIAL_DEV  *pdev,
                                          SERIAL_ERR  *perr)
{
    CPU_BOOLEAN  status;


    SerialBSP_RM48_SCI1_DevPtr = pdev;

                                                                /* Set handler interrupt request into interrupt channel */
    status = BSP_IntVectSet((CPU_INT08U   )BSP_INT_ID_LIN_01_LVL_00,
                            (CPU_INT08U   )SERIAL_INT_CH_LIN_01_LVL_00,
                            (CPU_INT08U   )BSP_INT_SRC_TYPE_IRQ,
                            (CPU_FNCT_VOID)SerialBSP_RM48_SCI1_IntHandler);

    if (status != DEF_OK) {
        return;
    }

    BSP_IntEn(SERIAL_INT_CH_LIN_01_LVL_00);                     /* Enable VIM interrupt channel                         */

   *perr = SERIAL_ERR_NONE;
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                    SerialBSP_RM48_SCI1_ClkFreqGet()
*
* Description : Get peripheral clock frequency.
*
* Argument(s) : none.
*
* Return(s)   : Peripheral clock frequency, in Hz.
*
* Caller(s)   : SerialDrv_Open() via 'pdev->BSP_API->ClkFreqGet()'.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  CPU_INT32U  SerialBSP_RM48_SCI1_ClkFreqGet (void)
{
    CPU_INT32U  clk_freq;


    clk_freq = BSP_SysPerClkFreqGet(BSP_SYS_PER_CLK_NBR_PS_LIN_00);

    return (clk_freq);
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                     SerialBSP_RM48_SCI1_IntHandler()
*
* Description : Handle serial port interrupt.
*
* Argument(s) : p_arg     Pointer to the Interrupt ISR argument..
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  SerialBSP_RM48_SCI1_IntHandler (void  *p_arg)
{
    SERIAL_DEV      *pdev;
    SERIAL_DEV_CFG  *pdev_cfg;


    pdev     = (SERIAL_DEV     *)SerialBSP_RM48_SCI1_DevPtr;
    pdev_cfg = (SERIAL_DEV_CFG *)&SerialDevCfg_RM48_SCI1;
    pdev_cfg->Drv_API->ISR_Handler(pdev, SERIAL_ISR_TYPE_UNKNOWN);
}
