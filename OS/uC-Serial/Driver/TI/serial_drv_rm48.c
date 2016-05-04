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
*                                            DEVICE DRIVER
*
*                                        Texas Instruments RM48
*
* Filename      : serial_drv_rm48.c
* Version       : V2.00.01
* Programmer(s) : NB
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <serial.h>
#include  <serial_drv_rm48.h>


/*
*********************************************************************************************************
*                                        REGISTER BIT DEFINES
*********************************************************************************************************
*/

#define  SERIAL_DRV_RM48_BIT_SCIGCR0_RST                DEF_BIT_00

                                                                /* ---------- SCI GLOBAL CONTROL REGISTER 1 ---------- */
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_TX_EN              DEF_BIT_25
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_RX_EN              DEF_BIT_24
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_CONT               DEF_BIT_17
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_LOOP_BACK          DEF_BIT_16
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_STOP_EXT_FRAME     DEF_BIT_13
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_HGEN_CTRL          DEF_BIT_12
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_CTYPE              DEF_BIT_11
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_MBUF_MODE          DEF_BIT_10
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_ADAPT              DEF_BIT_09
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_SLEEP              DEF_BIT_08
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_SWnRST             DEF_BIT_07
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_LINMODE            DEF_BIT_06
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_CLK                DEF_BIT_05
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_STOP               DEF_BIT_04
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_PARITY             DEF_BIT_03
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_PARITY_EN          DEF_BIT_02
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_TIMING_MODE        DEF_BIT_01
#define  SERIAL_DRV_RM48_BIT_SCIGCR1_COMM_MODE          DEF_BIT_00

                                                                /* --------- SCI INTERRUPT REGISTER BIT FIELDS -------- */
#define  SERIAL_DRV_RM48_BIT_INT_BE                     DEF_BIT_31
#define  SERIAL_DRV_RM48_BIT_INT_PBE                    DEF_BIT_30
#define  SERIAL_DRV_RM48_BIT_INT_CE                     DEF_BIT_29
#define  SERIAL_DRV_RM48_BIT_INT_ISFE                   DEF_BIT_28
#define  SERIAL_DRV_RM48_BIT_INT_NRE                    DEF_BIT_27
#define  SERIAL_DRV_RM48_BIT_INT_FE                     DEF_BIT_26
#define  SERIAL_DRV_RM48_BIT_INT_OE                     DEF_BIT_25
#define  SERIAL_DRV_RM48_BIT_INT_PE                     DEF_BIT_24
#define  SERIAL_DRV_RM48_BIT_INT_RX_DMA_ALL             DEF_BIT_18
#define  SERIAL_DRV_RM48_BIT_INT_RX_DMA                 DEF_BIT_16
#define  SERIAL_DRV_RM48_BIT_INT_TX_DMA                 DEF_BIT_15
#define  SERIAL_DRV_RM48_BIT_INT_ID                     DEF_BIT_13
#define  SERIAL_DRV_RM48_BIT_INT_RX                     DEF_BIT_09
#define  SERIAL_DRV_RM48_BIT_INT_TX                     DEF_BIT_08
#define  SERIAL_DRV_RM48_BIT_INT_TOA3WUS                DEF_BIT_07
#define  SERIAL_DRV_RM48_BIT_INT_TOAWUS                 DEF_BIT_06
#define  SERIAL_DRV_RM48_BIT_INT_TIMEOUT                DEF_BIT_04
#define  SERIAL_DRV_RM48_BIT_INT_WAKEUP                 DEF_BIT_01
#define  SERIAL_DRV_RM48_BIT_INT_BRKDT                  DEF_BIT_00

                                                                /* ----------------- SCI FLAGS REGISTER --------------- */
#define  SERIAL_DRV_RM48_BIT_FLAG_BE                    DEF_BIT_31
#define  SERIAL_DRV_RM48_BIT_FLAG_PBE                   DEF_BIT_30
#define  SERIAL_DRV_RM48_BIT_FLAG_CE                    DEF_BIT_29
#define  SERIAL_DRV_RM48_BIT_FLAG_ISFE                  DEF_BIT_28
#define  SERIAL_DRV_RM48_BIT_FLAG_NRE                   DEF_BIT_27
#define  SERIAL_DRV_RM48_BIT_FLAG_FE                    DEF_BIT_26
#define  SERIAL_DRV_RM48_BIT_FLAG_OE                    DEF_BIT_25
#define  SERIAL_DRV_RM48_BIT_FLAG_PE                    DEF_BIT_24
#define  SERIAL_DRV_RM48_BIT_FLAG_ID_RX                 DEF_BIT_14
#define  SERIAL_DRV_RM48_BIT_FLAG_ID_TX                 DEF_BIT_13
#define  SERIAL_DRV_RM48_BIT_FLAG_RXWAKE                DEF_BIT_12
#define  SERIAL_DRV_RM48_BIT_FLAG_TXEMPTY               DEF_BIT_11
#define  SERIAL_DRV_RM48_BIT_FLAG_TXWAKE                DEF_BIT_10
#define  SERIAL_DRV_RM48_BIT_FLAG_RXRDY                 DEF_BIT_09
#define  SERIAL_DRV_RM48_BIT_FLAG_TXRDY                 DEF_BIT_08
#define  SERIAL_DRV_RM48_BIT_FLAG_TOA3WUS               DEF_BIT_07
#define  SERIAL_DRV_RM48_BIT_FLAG_TOAWUS                DEF_BIT_06
#define  SERIAL_DRV_RM48_BIT_FLAG_TIMEOUT               DEF_BIT_04
#define  SERIAL_DRV_RM48_BIT_FLAG_BUSY                  DEF_BIT_03
#define  SERIAL_DRV_RM48_BIT_FLAG_IDLE                  DEF_BIT_02
#define  SERIAL_DRV_RM48_BIT_FLAG_WAKEUP                DEF_BIT_01
#define  SERIAL_DRV_RM48_BIT_FLAG_BRKDT                 DEF_BIT_00

                                                                /* ----------- SCI INTERRUPT VECTOR OFFSET ------------ */
#define  SERIAL_DRV_RM48_MSK_INTVECT                    DEF_BIT_FIELD(4u, 0u)

                                                                /* ----------- SCI FORMAT CONTROL REGISTER ------------ */
#define  SERIAL_DRV_RM48_MSK_SCIFORMAT_LEN              DEF_BIT_FIELD(2u, 16u)
#define  SERIAL_DRV_RM48_MSK_SCIFORMAT_CHAR             DEF_BIT_FIELD(2u,  0u)

#define  SERIAL_DRV_RM48_BIT_SCIFORMAT_CHAR_1           DEF_BIT_MASK(0u, 0u)
#define  SERIAL_DRV_RM48_BIT_SCIFORMAT_CHAR_2           DEF_BIT_MASK(1u, 0u)
#define  SERIAL_DRV_RM48_BIT_SCIFORMAT_CHAR_3           DEF_BIT_MASK(2u, 0u)
#define  SERIAL_DRV_RM48_BIT_SCIFORMAT_CHAR_4           DEF_BIT_MASK(3u, 0u)
#define  SERIAL_DRV_RM48_BIT_SCIFORMAT_CHAR_5           DEF_BIT_MASK(4u, 0u)
#define  SERIAL_DRV_RM48_BIT_SCIFORMAT_CHAR_6           DEF_BIT_MASK(5u, 0u)
#define  SERIAL_DRV_RM48_BIT_SCIFORMAT_CHAR_7           DEF_BIT_MASK(6u, 0u)
#define  SERIAL_DRV_RM48_BIT_SCIFORMAT_CHAR_8           DEF_BIT_MASK(7u, 0u)

                                                                /* -------- SCI FBAUD RATE SELECTION REGISTER --------- */
#define  SERIAL_DRV_RM48_MSK_BRS_PRESCALER              DEF_BIT_FIELD(24u, 0u)
#define  SERIAL_DRV_RM48_MSK_BRS_M                      DEF_BIT_FIELD(4u,  24u)
#define  SERIAL_DRV_RM48_MSK_BRS_U                      DEF_BIT_FIELD(3u,  28u)

                                                                /* -------- SCI FBAUD RATE SELECTION REGISTER --------- */
#define  SERIAL_DRV_RM48_MSK_SCI_DATA_BUF               DEF_BIT_FIELD(8u, 0u)

                                                                /* ------------- INTERRUPT VECTOR OFFSET ------------- */

#define  SERIAL_DRV_RM48_INT_OFF_NONE                    0u
#define  SERIAL_DRV_RM48_INT_OFF_PAR_ERR                 3u
#define  SERIAL_DRV_RM48_INT_OFF_OVERRUN                 9u
#define  SERIAL_DRV_RM48_INT_OFF_BIT_ERR                10u
#define  SERIAL_DRV_RM48_INT_OFF_RX                     11u
#define  SERIAL_DRV_RM48_INT_OFF_TX                     12u

#define  SERIAL_DRV_RM48_BIT_SCIPIO0_LINTX              DEF_BIT_02
#define  SERIAL_DRV_RM48_BIT_SCIPIO0_LINRX              DEF_BIT_01

/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/

typedef  struct  serial_reg {
    CPU_REG32  SCIGCR0;                                         /* SCI Global Control             Register 0.           */
    CPU_REG32  SCIGCR1;                                         /* SCI Global Control             Register 1.           */
    CPU_REG32  SCIGCR2;                                         /* SCI Global Control             Register 2.           */
    CPU_REG32  SCISETINT;                                       /* SCI Set   Interrupt            Register.             */
    CPU_REG32  SCICLEARINT;                                     /* SCI Clear Interrupt            Register.             */
    CPU_REG32  SCISETINTLVL;                                    /* SCI Set Interrupt Level        Register.             */
    CPU_REG32  SCICLEARINTLVL;                                  /* SCI Set Interrupt Clear        Register.             */
    CPU_REG32  SCIFLR;                                          /* SCI Flags                      Register.             */
    CPU_REG32  SCIINTVECT0;                                     /* SCI Interrupt Vector Offset 0  Register.             */
    CPU_REG32  SCIINTVECT1;                                     /* SCI Interrupt Vector Offset 1  Register.             */
    CPU_REG32  SCIFORMAT;                                       /* SCI Format Control             Register.             */
    CPU_REG32  BRS;                                             /* SCI Baud Rate Selection        Register.             */
    CPU_REG32  SCIED;                                           /* Modem Control                  Register.             */
    CPU_REG32  SCIRD;                                           /* Line Status         Register.                        */
    CPU_REG32  SCITD;                                           /* Modem Status        Register.                        */
    CPU_REG32  SCIPIO0;                                         /* SCI pin I/O control Register 0.                      */
    CPU_REG32  SCIPIO1;                                         /* SCI pin I/O control Register 1.                      */
    CPU_REG32  SCIPIO2;                                         /* SCI pin I/O control Register 2.                      */
    CPU_REG32  SCIPIO3;                                         /* SCI pin I/O control Register 3.                      */
    CPU_REG32  SCIPIO4;                                         /* SCI pin I/O control Register 4.                      */
    CPU_REG32  SCIPIO5;                                         /* SCI pin I/O control Register 5.                      */
    CPU_REG32  SCIPIO6;                                         /* SCI pin I/O control Register 6.                      */
    CPU_REG32  SCIPIO7;                                         /* SCI pin I/O control Register 7.                      */
    CPU_REG32  SCIPIO8;                                         /* SCI pin I/O control Register 7.                      */
} SERIAL_REG;


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/
                                                                /* Driver initialization.                               */
static  void        SerialDrv_Init       (SERIAL_ERR     *perr);

                                                                /* Driver open.                                         */
static  void        SerialDrv_Open       (SERIAL_DEV     *pdev,
                                          SERIAL_IF_CFG  *pcfg,
                                          SERIAL_ERR     *perr);

                                                                /* Driver close.                                        */
static  void        SerialDrv_Close      (SERIAL_DEV     *pdev,
                                          SERIAL_ERR     *perr);

                                                                /* Driver receiver start.                               */
static  void        SerialDrv_RxStart    (SERIAL_DEV     *pdev,
                                          SERIAL_ERR     *perr);

                                                                /* Driver receiver stop.                                */
static  void        SerialDrv_RxStop     (SERIAL_DEV     *pdev,
                                          SERIAL_ERR     *perr);

                                                                /* Driver octet receive.                                */
static  void        SerialDrv_RxOctet    (SERIAL_DEV     *pdev,
                                          CPU_INT08U     *pdatum,
                                          SERIAL_ERR     *perr);

                                                                /* Driver transmitter start.                            */
static  void        SerialDrv_TxStart    (SERIAL_DEV     *pdev,
                                          SERIAL_ERR     *perr);

                                                                /* Driver transmitter stop.                             */
static  void        SerialDrv_TxStop     (SERIAL_DEV     *pdev,
                                          SERIAL_ERR     *perr);

                                                                /* Driver octet transmit.                               */
static  void        SerialDrv_TxOctet    (SERIAL_DEV     *pdev,
                                          CPU_INT08U      datum,
                                          SERIAL_ERR     *perr);

                                                                /* Driver ISR handler.                                  */
static  void        SerialDrv_ISR_Handler(SERIAL_DEV     *pdev,
                                          CPU_INT08U      type);


/*
*********************************************************************************************************
*********************************************************************************************************
*                                 SERIAL INTERFACE DEVICE DRIVER API
*********************************************************************************************************
*********************************************************************************************************
*/

SERIAL_DRV_API  SerialDrv_RM48_API = {
    SerialDrv_Init,
    SerialDrv_Open,
    SerialDrv_Close,
    SerialDrv_RxStart,
    SerialDrv_RxStop,
    SerialDrv_RxOctet,
    SerialDrv_TxStart,
    SerialDrv_TxStop,
    SerialDrv_TxOctet,
    SerialDrv_ISR_Handler
};


/*$PAGE*/
/*
*********************************************************************************************************
*********************************************************************************************************
*                                     DRIVER INTERFACE FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          SerialDrv_Init()
*
* Description : Initialize serial device driver.
*
* Argument(s) : perr        Pointer to variable that will receive the return error code from this function :
*
*                               SERIAL_ERR_NONE                 Driver initialized.
*
* Return(s)   : None.
*
* Caller(s)   : Serial_DrvAdd() via 'pdrv_api->Init()'.
*
* Note(s)     : None.
*********************************************************************************************************
*/

static  void  SerialDrv_Init (SERIAL_ERR  *perr)
{
   *perr = SERIAL_ERR_NONE;
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                          SerialDrv_Open()
*
* Description : Open a serial device for communication.
*
* Argument(s) : pdev        Pointer to device.
*
*               pcfg        Pointer to interface configuration.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               SERIAL_ERR_NONE                 Device              opened.
*                               SERIAL_ERR_DRV_OPEN             Device could NOT be opened.
*                               SERIAL_ERR_DRV_INVALID          Device configuration invalid.
*                               SERIAL_ERR_MEM_ALLOC            Memory could NOT be allocated for device
*                                                                   internal data.
*
* Return(s)   : None.
*
* Caller(s)   : Serial_Open() via 'pdev->Drv_API->Open()'.
*
* Note(s)     : (1) Interrupts are assumed to be disabled when this function is called.
*
*               (2) In asynchronous timing mode, the SCI generates a baud clock according to the following
*                   formula:
*
*                                              VCLK_freq
*                       SCICLK_freq      = -------------------
*                                           (P + 1 +  M/16)
*
*                                              SCICLK_Freq
*                       Async Baud Freq  = -------------------
*                                                 16
*
*                       Assuming M = 0,
*
*                                               VCLK_Freq
*                       Async Baud Freq  = ------------------
*                                              16 x(P + 1)
*********************************************************************************************************
*/

static  void  SerialDrv_Open (SERIAL_DEV     *pdev,
                              SERIAL_IF_CFG  *pcfg,
                              SERIAL_ERR     *perr)
{
    SERIAL_BSP_API   *pdev_bsp;
    SERIAL_REG       *reg;
    CPU_BOOLEAN       flow_ctrl;
    CPU_INT32U        clk_freq;
    CPU_INT32U        reg_val;

                                                                /* -------------- BAUD RATE CALCULATION --------------- */
    pdev_bsp = pdev->Dev_Cfg->BSP_API;
    clk_freq = pdev_bsp->ClkFreqGet();                          /* Get the UART peripheral clock                        */

    if (pcfg->Baudrate > clk_freq) {                            /* If baud rate higher than peripheral clock?           */
        *perr =  SERIAL_ERR_DRV_INVALID;
        return;
    }

    if (clk_freq < (8u * pcfg->Baudrate)) {
        *perr = SERIAL_ERR_DRV_INVALID;
        return;
    }
                                                                /* Calculate baud rate preescaler (see note #2).        */
    reg_val = ((clk_freq / (8u * pcfg->Baudrate) - 1u) / 2u);

    if (reg_val > DEF_BIT_FIELD(24u, 0u)) {                     /* Preescaler > Max  allowed value?                     */
        *perr = SERIAL_ERR_DRV_INVALID;
         return;
    }

    pdev_bsp->ClkEn(perr);                                      /* En dev-specific HW clk.                              */
    if (*perr != SERIAL_ERR_NONE) {
         return;
    }

    reg          = (SERIAL_REG *)pdev->Dev_Cfg->BaseAddr;
    reg->SCIGCR0 = DEF_BIT_NONE;                                /* SCI module reset                                     */
    reg->SCIGCR0 = SERIAL_DRV_RM48_BIT_SCIGCR0_RST;

    reg->SCIGCR1 = DEF_BIT_NONE;                                /* Set soft reset.                                      */
    reg->BRS     = reg_val;
    reg_val      = DEF_BIT_NONE;

    switch (pcfg->DataBits) {
        case SERIAL_DATABITS_5:
             reg_val = SERIAL_DRV_RM48_BIT_SCIFORMAT_CHAR_5;
             break;


        case SERIAL_DATABITS_6:
             reg_val = SERIAL_DRV_RM48_BIT_SCIFORMAT_CHAR_6;
             break;


        case SERIAL_DATABITS_7:
             reg_val = SERIAL_DRV_RM48_BIT_SCIFORMAT_CHAR_7;
             break;

        case SERIAL_DATABITS_8:
             reg_val = SERIAL_DRV_RM48_BIT_SCIFORMAT_CHAR_8;
             break;

        default:
             *perr   = SERIAL_ERR_DRV_INVALID;
             break;
    }

    reg->SCICLEARINT    = DEF_BIT_FIELD(32u, 0u);               /* Disable all interrupts.                              */
    reg->SCICLEARINTLVL = DEF_BIT_FIELD(32u, 0u);               /* Map al interrupts to the INT0 line.                  */
    reg->SCIFLR         = DEF_BIT_FIELD(32u, 0u);               /* Clear all pending interrupts.                        */
    reg->SCIFORMAT      = reg_val;

    reg_val               = SERIAL_DRV_RM48_BIT_SCIGCR1_CLK
                          | SERIAL_DRV_RM48_BIT_SCIGCR1_TIMING_MODE;

    switch (pcfg->Parity) {
        case SERIAL_PARITY_ODD:
             DEF_BIT_SET(reg_val, SERIAL_DRV_RM48_BIT_SCIGCR1_PARITY_EN);
             break;

        case SERIAL_PARITY_EVEN:
             DEF_BIT_SET(reg_val, SERIAL_DRV_RM48_BIT_SCIGCR1_PARITY_EN |
                                  SERIAL_DRV_RM48_BIT_SCIGCR1_PARITY);
             break;

        case SERIAL_PARITY_NONE:
             break;

        case SERIAL_PARITY_MARK:
        case SERIAL_PARITY_SPACE:
        default:
            *perr = SERIAL_ERR_DRV_INVALID;
             break;
    }

    switch (pcfg->StopBits) {
        case SERIAL_STOPBITS_1:
             break;

        case SERIAL_STOPBITS_1_5:
            *perr = SERIAL_ERR_DRV_INVALID;
             break;

        case SERIAL_STOPBITS_2:
             DEF_BIT_SET(reg_val, SERIAL_DRV_RM48_BIT_SCIGCR1_STOP);
             break;

        default:
            *perr = SERIAL_ERR_DRV_INVALID;
             break;
    }

    reg->SCIGCR1 = reg_val;

    switch (pcfg->FlowCtrl) {
        case SERIAL_FLOW_CTRL_HARDWARE:
             flow_ctrl = DEF_ENABLED;
             break;

        case SERIAL_FLOW_CTRL_NONE:
        default:
             flow_ctrl = DEF_DISABLED;
             break;
    }

    reg->SCIPIO0 = SERIAL_DRV_RM48_BIT_SCIPIO0_LINTX
                 | SERIAL_DRV_RM48_BIT_SCIPIO0_LINRX;

    reg->SCIPIO7 = DEF_BIT_NONE;
    reg->SCIFLR  = DEF_BIT_FIELD(32u, 0u);
    reg->SCIFLR  = DEF_BIT_NONE;

    pdev_bsp->CfgGPIO(flow_ctrl, perr);                         /* Cfg dev-specific GPIO.                               */

    if (*perr != SERIAL_ERR_NONE) {
         return;
    }

    DEF_BIT_SET(reg->SCIGCR1, SERIAL_DRV_RM48_BIT_SCIGCR1_CONT  |
                              SERIAL_DRV_RM48_BIT_SCIGCR1_RX_EN |
                              SERIAL_DRV_RM48_BIT_SCIGCR1_TX_EN);

    DEF_BIT_SET(reg->SCIGCR1, SERIAL_DRV_RM48_BIT_SCIGCR1_SWnRST);

    pdev_bsp->CfgInt(pdev, perr);                               /* Cfg dev-specific int.                                */

    if (*perr != SERIAL_ERR_NONE) {
         return;
    }
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                          SerialDrv_Close()
*
* Description : Close a serial device for communication.
*
* Argument(s) : pdev        Pointer to device.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               SERIAL_ERR_NONE                 Device closed.
*
* Return(s)   : None.
*
* Caller(s)   : Serial_Close() via 'pdev->Drv_API->Close()'.
*
* Note(s)     : (1) Interrupts are assumed to be disabled when this function is called.
*********************************************************************************************************
*/

static  void  SerialDrv_Close (SERIAL_DEV  *pdev,
                               SERIAL_ERR  *perr)
{
    SERIAL_REG  *reg;

    reg = (SERIAL_REG *)pdev->Dev_Cfg->BaseAddr;

    reg->BRS = DEF_BIT_NONE;
    reg->SCICLEARINT    = DEF_BIT_FIELD(32u, 0u);               /* Disable all interrupts.                              */
    reg->SCICLEARINTLVL = DEF_BIT_FIELD(32u, 0u);               /* Map al interrupts to the INT0 line.                  */
    reg->SCIFLR         = DEF_BIT_FIELD(32u, 0u);               /* Clear all pending interrupts.                        */
    reg->SCIFORMAT      = DEF_BIT_NONE;
    reg->SCIGCR1        = DEF_BIT_NONE;

    pdev->Dev_Cfg->BSP_API->ClkDis(perr);                       /* Dis dev-specific HW clk.                             */
    if (*perr != SERIAL_ERR_NONE) {
         return;
    }

   *perr = SERIAL_ERR_NONE;
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                         SerialDrv_RxStart()
*
* Description : Start receiving data & getting data received interrupts.
*
* Argument(s) : pdev        Pointer to device.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               SERIAL_ERR_NONE                 Device reception started.
*
* Return(s)   : None.
*
* Caller(s)   : Serial_Open(),
*               Serial_IF_RxStart() via 'pdev->Drv_API->RxStart()'.
*
* Note(s)     : (1) Interrupts are assumed to be disabled when this function is called.
*********************************************************************************************************
*/

static  void  SerialDrv_RxStart (SERIAL_DEV  *pdev,
                                 SERIAL_ERR  *perr)
{
    SERIAL_REG  *reg;


    reg            = (SERIAL_REG *)pdev->Dev_Cfg->BaseAddr;
    reg->SCISETINT = SERIAL_DRV_RM48_BIT_INT_RX;

   *perr = SERIAL_ERR_NONE;
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                         SerialDrv_RxStop()
*
* Description : Stop receiving data and data received interrupts.
*
* Argument(s) : pdev        Pointer to device.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               SERIAL_ERR_NONE                 Device reception stopped.
*
* Return(s)   : None.
*
* Caller(s)   : Serial_Close(),
*               Serial_IF_Rx(),
*               Serial_IF_RxStop() via 'pdev->Drv_API->RxStop()'.
*
* Note(s)     : (1) Interrupts are assumed to be disabled when this function is called.
*********************************************************************************************************
*/

static  void  SerialDrv_RxStop (SERIAL_DEV  *pdev,
                                SERIAL_ERR  *perr)
{
    SERIAL_REG  *reg;


    reg              = (SERIAL_REG *)pdev->Dev_Cfg->BaseAddr;
    reg->SCICLEARINT = SERIAL_DRV_RM48_BIT_INT_RX;

   *perr = SERIAL_ERR_NONE;
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                         SerialDrv_RxOctet()
*
* Description : Receive data octet.
*
* Argument(s) : pdev        Pointer to device.
*
*               pdatum      Pointer to variable that will receive the received data octet.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               SERIAL_ERR_NONE                 Device octet     transmitted,
*                               SERIAL_ERR_DRV_IO_ERR           Device octet NOT transmitted.
*
* Return(s)   : None.
*
* Caller(s)   : Serial_IF_Rx() via 'pdrv_api->RxOctet()'.
*
* Note(s)     : (1) Interrupts are assumed to be disabled when this function is called.
*********************************************************************************************************
*/

static  void  SerialDrv_RxOctet (SERIAL_DEV  *pdev,
                                 CPU_INT08U  *pdatum,
                                 SERIAL_ERR  *perr)
{
    SERIAL_REG  *reg;
    CPU_INT32U   reg_val;

    reg     = (SERIAL_REG *)pdev->Dev_Cfg->BaseAddr;
    reg_val = reg->SCIFLR;                                      /* Read SCI flags.                                      */

                                                                /* If the receive data doesn't contain data ...         */
    if (DEF_BIT_IS_CLR(reg_val, SERIAL_DRV_RM48_BIT_FLAG_RXRDY)) {
        *perr = SERIAL_ERR_DRV_IO_ERR;
        return;
    }
                                                                /* Check for Rx errors.                                 */
    if (DEF_BIT_IS_SET_ANY(reg_val, SERIAL_DRV_RM48_BIT_FLAG_PE)) {
         reg->SCIFLR = SERIAL_DRV_RM48_BIT_FLAG_PE;
        *perr        = SERIAL_ERR_DRV_IO_ERR;
        return;
    }

    reg->SCIFLR   = SERIAL_DRV_RM48_BIT_FLAG_RXRDY;
   *pdatum        = (CPU_INT08U)(reg->SCIRD & DEF_INT_08_MASK);
   *perr          = SERIAL_ERR_NONE;
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                         SerialDrv_TxStart()
*
* Description : Start transmitting data & getting data transmitted interrupts.
*
* Argument(s) : pdev        Pointer to device.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               SERIAL_ERR_NONE                 Device transmission started.
*
* Return(s)   : None.
*
* Caller(s)   : Serial_IF_Tx(),
*               Serial_WrStart() via 'pdev->Drv_API->TxStart()'.
*
* Note(s)     : (1) Interrupts are assumed to be disabled when this function is called.
*********************************************************************************************************
*/

static  void  SerialDrv_TxStart (SERIAL_DEV  *pdev,
                                 SERIAL_ERR  *perr)
{
    SERIAL_REG  *reg;


    reg              = (SERIAL_REG *)pdev->Dev_Cfg->BaseAddr;
    reg->SCISETINT   = SERIAL_DRV_RM48_BIT_INT_TX;

   *perr = SERIAL_ERR_NONE;
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                         SerialDrv_TxStop()
*
* Description : Stop transmitting data & getting data transmitted interrupts.
*
* Argument(s) : pdev        Pointer to device.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               SERIAL_ERR_NONE                 Device transmission stopped.
*
* Return(s)   : None.
*
* Caller(s)   : Serial_Close(),
*               Serial_IF_Tx(),
*               Serial_WrStartNext() via 'pdev->Drv_API->TxStop()'.
*
* Note(s)     : (1) Interrupts are assumed to be disabled when this function is called.
*********************************************************************************************************
*/

static  void  SerialDrv_TxStop (SERIAL_DEV  *pdev,
                                SERIAL_ERR  *perr)
{
    SERIAL_REG  *reg;


    reg              = (SERIAL_REG *)pdev->Dev_Cfg->BaseAddr;
    reg->SCICLEARINT = SERIAL_DRV_RM48_BIT_INT_TX;


   *perr = SERIAL_ERR_NONE;
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                         SerialDrv_TxOctet()
*
* Description : Transmit data octet.
*
* Argument(s) : pdev        Pointer to device.
*
*               datum       Data octet to transmit.
*
*               perr        Pointer to variable that will receive the return error code from this function :
*
*                               SERIAL_ERR_NONE                 Device octet     transmitted,
*                               SERIAL_ERR_DRV_IO_ERR           Device octet NOT transmitted.
*
* Return(s)   : None.
*
* Caller(s)   : Serial_IF_Tx()   via      'pdrv_api->TxOctet()',
*               Serial_WrStart() via 'pdev->Drv_API->TxOctet()'.
*
* Note(s)     : (1) Interrupts are assumed to be disabled when this function is called.
*********************************************************************************************************
*/

static  void  SerialDrv_TxOctet (SERIAL_DEV  *pdev,
                                 CPU_INT08U   datum,
                                 SERIAL_ERR  *perr)
{
    SERIAL_REG  *reg;
    CPU_INT32U   reg_val;

    reg     = (SERIAL_REG *)pdev->Dev_Cfg->BaseAddr;
    reg_val = reg->SCIFLR;                                      /*  Read SCI flags.                                     */

    if (DEF_BIT_IS_CLR(reg_val, SERIAL_DRV_RM48_BIT_FLAG_TXRDY)) {
        *perr = SERIAL_ERR_DRV_IO_ERR;
        return;
    }

    reg->SCITD = datum;
   *perr       = SERIAL_ERR_NONE;
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                       SerialDrv_ISR_Handler()
*
* Description : Handle serial interface's device interrupt service routine (ISR) function(s).
*
* Argument(s) : pdev        Pointer to device.
*
*               type        Device  interrupt type(s) to handle :
*
*                               SERIAL_ISR_TYPE_UNKNOWN         Handle unknown device           ISR(s).
*                               SERIAL_ISR_TYPE_RX              Handle device receive           ISR(s).
*                               SERIAL_ISR_TYPE_RX_OVERRUN      Handle device receive  overrun  ISR(s).
*                               SERIAL_ISR_TYPE_TX_RDY          Handle device transmit ready    ISR(s).
*                               SERIAL_ISR_TYPE_TX_COMPLETE     Handle device transmit complete ISR(s).
*                               SERIAL_ISR_TYPE_ERR             Handle device error             ISR(s).
*
* Return(s)   : None.
*
* Caller(s)   : Device driver(s)' Board Support Package (BSP) Interrupt Service Routine (ISR) handler(s).
*
* Note(s)     : None.
*********************************************************************************************************
*/

static  void  SerialDrv_ISR_Handler (SERIAL_DEV  *pdev,
                                     CPU_INT08U   type)
{
    SERIAL_REG  *reg;
    CPU_INT08U       int_off;
    CPU_INT08U   datum;


   (void)&type;

    reg   = (SERIAL_REG      *)pdev->Dev_Cfg->BaseAddr;
    int_off   = reg->SCIINTVECT0 & DEF_BIT_FIELD(5u, 0u);       /* Read te interrupt indentification register           */

    while (int_off != SERIAL_DRV_RM48_INT_OFF_NONE) {
        switch (int_off) {
            case SERIAL_DRV_RM48_INT_OFF_RX:
                 reg->SCIFLR = SERIAL_DRV_RM48_BIT_FLAG_RXRDY;
                 datum       = reg->SCIRD & DEF_BIT_FIELD(8u, 0u);
                 SerialIF_Rx(pdev, datum);
                 break;

            case SERIAL_DRV_RM48_INT_OFF_TX:
                 reg->SCIFLR = SERIAL_DRV_RM48_BIT_FLAG_TXEMPTY
                             | SERIAL_DRV_RM48_BIT_FLAG_TXRDY;
                 SerialIF_Tx(pdev);
                 break;

            case SERIAL_DRV_RM48_INT_OFF_OVERRUN:
            case SERIAL_DRV_RM48_INT_OFF_BIT_ERR:
            case SERIAL_DRV_RM48_INT_OFF_PAR_ERR:

            default:
                 break;

        }
        int_off = reg->SCIINTVECT0 & DEF_BIT_FIELD(5u, 0u);
    }
}
