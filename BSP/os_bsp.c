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
*
*                                    MICRIUM BOARD SUPPORT PACKAGE
*                                          Texas Instruments
*                                 RM48x Hercules Development Kit(HDK)
*
* Filename      : os_bsp.c
* Version       : V1.00
* Programmer(s) : FF
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDES
*********************************************************************************************************
*/

#include  <bsp_cfg.h>

#include  <os.h>

#include  <cpu_core.h>
#include  <bsp_sys.h>
#include  <bsp_int.h>
#include  <os_bsp.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

                                                                /* --------------- RTI CONTROL REGISTER --------------- */
#define  BSP_TMR_ADDR_REG_BASE                     (CPU_INT32U )(0xFFFFFC00u)
#define  BSP_TMR_REG_RTIGCCTRL                  (* (CPU_REG32 *)(BSP_TMR_ADDR_REG_BASE + 0x00u))
#define  BSP_TMR_REG_RTICOMPCTRL                (* (CPU_REG32 *)(BSP_TMR_ADDR_REG_BASE + 0x0Cu))
#define  BSP_TMR_REG_RTIFRC1                    (* (CPU_REG32 *)(BSP_TMR_ADDR_REG_BASE + 0x30u))
#define  BSP_TMR_REG_RTICPUC1                   (* (CPU_REG32 *)(BSP_TMR_ADDR_REG_BASE + 0x38u))
#define  BSP_TMR_REG_RTICOMP1                   (* (CPU_REG32 *)(BSP_TMR_ADDR_REG_BASE + 0x58u))
#define  BSP_TMR_REG_RTIUDCP1                   (* (CPU_REG32 *)(BSP_TMR_ADDR_REG_BASE + 0x5Cu))
#define  BSP_TMR_REG_RTISETINTENA               (* (CPU_REG32 *)(BSP_TMR_ADDR_REG_BASE + 0x80u))
#define  BSP_TMR_REG_RTIINTFLAG                 (* (CPU_REG32 *)(BSP_TMR_ADDR_REG_BASE + 0x88u))

#define  BSP_TMR_VAL_RTICPUC0_DFLT                     255u

#define  BSP_RTICOMPCTRL_COMPSEL1                DEF_BIT_04
#define  BSP_RTIGCTRL_CNT1EN                     DEF_BIT_01
#define  BSP_RTISETINTENA_SETINT1                DEF_BIT_01
#define  BSP_RTIINTFLAG_INT1                     DEF_BIT_01

#define  BSP_INT_CH_RTI_XX_CMP_01                        3u


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  OS_BSP_TickISR_Handler(void  *p_arg);


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                     INITIALIZE TICKER INTERRUPT
*
* Description : Initialize the the tick interrupt.
*
* Argument(s) : tick_rate      Number of ticks per second.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none
*********************************************************************************************************
*/

void  OS_BSP_TickInit (CPU_INT32U  tick_rate)
{
    CPU_INT32U   rti_clk_freq;
    CPU_INT32U   match_val;
    CPU_BOOLEAN  status;
    CPU_SR_ALLOC();


    rti_clk_freq = BSP_SysClkFreqGet(BSP_SYS_CLK_NBR_RTI_CLK_01);

    if (rti_clk_freq < tick_rate) {
        return;
    }

    rti_clk_freq  /= (BSP_TMR_VAL_RTICPUC0_DFLT + 1u);
    match_val      = ((((2u * rti_clk_freq) / tick_rate) + 1u) / 2u);

    CPU_CRITICAL_ENTER();

    BSP_TMR_REG_RTICPUC1 = BSP_TMR_VAL_RTICPUC0_DFLT;           /* Set the default compare up counter value.            */
    BSP_TMR_REG_RTICOMP1 = match_val;                           /* Set the match value in the compare 1 register.       */
    BSP_TMR_REG_RTIUDCP1 = match_val;                           /* Set the update value.                                */
                                                                /* Value will be compared with RTIFRC1                  */
    DEF_BIT_SET(BSP_TMR_REG_RTICOMPCTRL, BSP_RTICOMPCTRL_COMPSEL1);
    DEF_BIT_CLR(BSP_TMR_REG_RTIGCCTRL, BSP_RTIGCTRL_CNT1EN);    /* Disable the timer.                                   */
    BSP_TMR_REG_RTIFRC1      = 0u;                              /* Clear the counter.                                   */
    BSP_TMR_REG_RTISETINTENA = BSP_RTISETINTENA_SETINT1;        /* Enable interrupt on match 1.                         */

    CPU_CRITICAL_EXIT();

                                                                /* Set handler interrupt request into interrupt channel */
    status = BSP_IntVectSet((CPU_INT08U   )BSP_INT_ID_RTI_XX_CMP_01,
                            (CPU_INT08U   )BSP_INT_CH_RTI_XX_CMP_01,
                            (CPU_INT08U   )BSP_INT_SRC_TYPE_IRQ,
                            (CPU_FNCT_VOID)OS_BSP_TickISR_Handler);

    if (status != DEF_OK) {
        return;
    }

    DEF_BIT_SET(BSP_TMR_REG_RTIGCCTRL, BSP_RTIGCTRL_CNT1EN);    /* Start timer                                          */

    BSP_IntEn(BSP_INT_CH_RTI_XX_CMP_01);                        /* Enable VIM interrupt channel                         */
}


/*
*********************************************************************************************************
*                                 INITIALIZE TICKER INTERRUPT HANDLER
*
* Description: Tick interrupt handler.
*
* Arguments  : 'p_arg'  Pointer to interrupt handler argument.
*
* Return(s)   : None.
*
* Caller(s)   : None.
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  OS_BSP_TickISR_Handler (void  *p_arg)
{
    (void)p_arg;

    BSP_TMR_REG_RTIINTFLAG = BSP_RTIINTFLAG_INT1;               /* Timer interrupt clear                                */
    OSTimeTick();
}


/*
*********************************************************************************************************
*                                          ARM INTERRUPT/EXCEPTION HANDLER
*
* Description : Handle ARM exceptions.
*
* Argument(s) : src_id     ARM exception source identifier:
*
*                                  OS_CPU_ARM_EXCEPT_RESET             0x00
*                                  OS_CPU_ARM_EXCEPT_UNDEF_INSTR       0x01
*                                  OS_CPU_ARM_EXCEPT_SWI               0x02
*                                  OS_CPU_ARM_EXCEPT_ABORT_PREFETCH    0x03
*                                  OS_CPU_ARM_EXCEPT_ABORT_DATA        0x04
*                                  OS_CPU_ARM_EXCEPT_RSVD              0x05
*                                  OS_CPU_ARM_EXCEPT_IRQ               0x06
*                                  OS_CPU_ARM_EXCEPT_FIQ               0x07
*
* Return(s)   : none.
*
* Caller(s)   : OS_CPU_ARM_ExceptHndlr(), which is declared in os_cpu_a.s.
*
* Note(s)     : (1) Only OS_CPU_ARM_EXCEPT_IRQ exceptions handler is implemented. For the rest of the
*                   exception a infinite loop is implemented for debuging pruposes. This behavior should
*                   be replaced with another behavior (reboot, etc).
*
*               (2) OS_CPU_ARM_EXCEPT_FIQ implemented in Cortex-R4F is Non-maskable Fast Interrupt(NMFI).
*                   Once FIQ is enabled (by clearing F bit in CPSR, it can NOT be disabled by setting F bit
*                   in CPSR. Only a reset or an FIQ will be able to set the F bit in CPSR. Therefore, when
*                   using FIQ interrupts make sure that there are NO OS services calls being done from its
*                   ISRs because FIQ interrupt must be NON-KERNEL aware.
*********************************************************************************************************
*/

void  OS_CPU_ExceptHndlr (CPU_INT32U  src_id)
{
    switch (src_id) {
        case OS_CPU_ARM_EXCEPT_IRQ:
             BSP_IntHandlerSrc((CPU_INT16U)src_id);
             break;


        case OS_CPU_ARM_EXCEPT_RESET:
        case OS_CPU_ARM_EXCEPT_UNDEF_INSTR:
        case OS_CPU_ARM_EXCEPT_SWI:
        case OS_CPU_ARM_EXCEPT_DATA_ABORT:
        case OS_CPU_ARM_EXCEPT_PREFETCH_ABORT:
        case OS_CPU_ARM_EXCEPT_ADDR_ABORT:
        case OS_CPU_ARM_EXCEPT_FIQ:
        default:
             while (DEF_TRUE) {
                 ;
             }
    }
}
