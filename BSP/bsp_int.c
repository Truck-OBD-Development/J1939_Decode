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
*                                         INTERRUPT MANAGMENT
*                                          Texas Instruments
*                                 RM48x Hercules Development Kit(HDK)
*
* Filename      : bsp_int.c
* Version       : V1.00
* Programmer(s) : NB
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include   <cpu_core.h>
#include   <lib_def.h>
#include   <bsp_int.h>

#include   <os.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


#define  BSP_INT_ADDR_REG_BASE             (CPU_ADDR  )0xFFFFFE00u

#define  BSP_INT_REG_IRQ_INDEX          (*(CPU_REG32 *)(BSP_INT_ADDR_REG_BASE + 0x00u))
#define  BSP_INT_REG_FIQ_INDEX          (*(CPU_REG32 *)(BSP_INT_ADDR_REG_BASE + 0x04u))
#define  BSP_INT_REG_FIRQPR0            (*(CPU_REG32 *)(BSP_INT_ADDR_REG_BASE + 0x10u))
#define  BSP_INT_REG_FIRQPR1            (*(CPU_REG32 *)(BSP_INT_ADDR_REG_BASE + 0x14u))
#define  BSP_INT_REG_FIRQPR2            (*(CPU_REG32 *)(BSP_INT_ADDR_REG_BASE + 0x18u))
#define  BSP_INT_REG_REQENASET0         (*(CPU_REG32 *)(BSP_INT_ADDR_REG_BASE + 0x30u))
#define  BSP_INT_REG_REQENASET1         (*(CPU_REG32 *)(BSP_INT_ADDR_REG_BASE + 0x34u))
#define  BSP_INT_REG_REQENASET2         (*(CPU_REG32 *)(BSP_INT_ADDR_REG_BASE + 0x38u))
#define  BSP_INT_REG_REQENACLR0         (*(CPU_REG32 *)(BSP_INT_ADDR_REG_BASE + 0x40u))
#define  BSP_INT_REG_REQENACLR1         (*(CPU_REG32 *)(BSP_INT_ADDR_REG_BASE + 0x44u))
#define  BSP_INT_REG_REQENACLR2         (*(CPU_REG32 *)(BSP_INT_ADDR_REG_BASE + 0x48u))
#define  BSP_INT_REG_IRQVECREG          (*(CPU_REG32 *)(BSP_INT_ADDR_REG_BASE + 0x70u))
#define  BSP_INT_REG_CHANCTRL(prio)     (*(CPU_REG32 *)(BSP_INT_ADDR_REG_BASE + 0x80u + ((prio) * 4u)))

#define  BSP_INT_ADDR_INT_TBL             (CPU_ADDR   )(0xFFF82000u)


/*
*********************************************************************************************************
*                                           LOCAL CONSTANTS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           LOCAL DATA TYPES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            LOCAL MACRO's
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  BSP_IntHandlerDummy(void);


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           LOCAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             BSP_IntDis()
*
* Description : Disable a VIM interrupt channel.
*
* Argument(s) : src_ch    Interrupt source channel where interrupt request is mapped.
*
* Return(s)   : None.
*
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  BSP_IntDis (CPU_INT08U  src_ch)
{
    if ((src_ch == BSP_INT_CH_00) ||
        (src_ch == BSP_INT_CH_01)) {
        return;                                                 /* Channel 0 and 1 are always enabled                   */
    }

    if (src_ch > BSP_INT_CH_MAX - 1u) {
        return;
    }

    if (src_ch < BSP_INT_CH_32) {                               /* VIM channels 2 to 31                                 */
        BSP_INT_REG_REQENACLR0 = DEF_BIT(src_ch);
    } else if (src_ch < BSP_INT_CH_64) {                        /* VIM channels 32 to 63                                */
        BSP_INT_REG_REQENACLR1 = DEF_BIT(src_ch - BSP_INT_CH_32);
    } else {                                                    /* VIM channels 64 to 95                                */
        BSP_INT_REG_REQENACLR2 = DEF_BIT(src_ch - BSP_INT_CH_64);
    }
}


/*
*********************************************************************************************************
*                                           BSP_IntDisAll()
*
* Description : Disable all VIM interrupt channels.
*
* Argument(s) : None.
*
* Return(s)   : None.
*
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  BSP_IntDisAll (void)
{
    BSP_INT_REG_REQENACLR0 = DEF_BIT_FIELD(30u, 0u);            /* Disable all interrupts channels.                     */
    BSP_INT_REG_REQENACLR1 = DEF_BIT_FIELD(32u, 0u);
    BSP_INT_REG_REQENACLR2 = DEF_BIT_FIELD(32u, 0u);
}


/*
*********************************************************************************************************
*                                             BSP_IntEn()
*
* Description : Enable a VIM interrupt channel.
*
* Argument(s) : src_ch    Interrupt source channel where interrupt request is mapped.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntEn (CPU_INT08U  src_ch)
{
    if ((src_ch == BSP_INT_CH_00) ||
        (src_ch == BSP_INT_CH_01)) {
        return;                                                 /* Channel 0 and 1 are always enabled                   */
    }

    if (src_ch > BSP_INT_CH_MAX - 1u) {
        return;
    }

    if (src_ch < BSP_INT_CH_32) {                               /* VIM channels 2 to 31                                 */
        BSP_INT_REG_REQENASET0 = DEF_BIT(src_ch);
    } else if (src_ch < BSP_INT_CH_64) {                        /* VIM channels 32 to 63                                */
        BSP_INT_REG_REQENASET1 = DEF_BIT(src_ch - BSP_INT_CH_32);
    } else {                                                    /* VIM channels 64 to 95                                */
        BSP_INT_REG_REQENASET2 = DEF_BIT(src_ch - BSP_INT_CH_64);
    }
}


/*
*********************************************************************************************************
*                                            BSP_IntInit()
*
* Description : Initiailze all interrupt controllers.
*                   (1) Disable all interrupts.
*                   (2) Clear all pending interrupts.
*                   (3) Initialize all vector interrupt tables.
*                   (4) Install all shared interrupt handlers.
*
* Argument(s) : None.
*
* Return(s)   : None.
*
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  BSP_IntInit (void)
{
    BSP_INT_REG_REQENACLR0 = DEF_BIT_FIELD(30u, 0u);            /* Disable all pending interrupts                       */
    BSP_INT_REG_REQENACLR1 = DEF_BIT_FIELD(32u, 0u);
    BSP_INT_REG_REQENACLR2 = DEF_BIT_FIELD(32u, 0u);
}


/*
*********************************************************************************************************
*                                           BSP_IntVectSet()
*
* Description : Map an interrupt source request to a VIM interrupt channel.
*
* Argument(s) : src_nbr    Interrupt source number.
*
*               src_ch     VIM Interrupt source channel.
*
*               src_type   Interrupt source type:
*                              BSP_INT_SRC_TYPE_IRQ           Normal Interrupt request.
*                              BSP_INT_SRC_TYPE_FIQ           Fast   Interrupt request.
*
* Return(s)   : DEF_OK,    if the interrupt source was mapped
*               DEF_FAIL,  otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : 1) The VIM channels work as a priority scheme for this processor, which means that mapping
*                  INT2 request to VIM channel 2 and 4, and mapping INT3 request to channel 3, it is possible
*                  for the software to change the priority dynamically by changing the ENABLE register
*                  (REQENASET and REQENACLR). When VIM channel 2 is enabled, the priority is as follow:
*                      1. INT0
*                      2. INT1
*                      3. INT2
*                      4. INT3
*
*                  Disabling channel 2, the priority becomes:
*                      1. INT0
*                      2. INT1
*                      3. INT3
*                      4. INT2
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_IntVectSet (CPU_INT08U     src_nbr,
                             CPU_INT08U     src_ch,
                             CPU_INT08U     src_type,
                             CPU_FNCT_VOID  isr_fnct)
{
    CPU_FNCT_VOID  *p_vect_tbl;
    CPU_INT08U      prio_reg_nbr;
    CPU_INT08U      prio_off;
    CPU_INT32U      prio_mask;
    CPU_INT32U      reg_val;
    CPU_SR_ALLOC();


    if (src_ch > BSP_INT_CH_MAX - 2u) {                         /* Channel 95 is not programmable.                      */
        return (DEF_FAIL);
    }

    p_vect_tbl             = (CPU_FNCT_VOID *)BSP_INT_ADDR_INT_TBL;
    p_vect_tbl[src_ch + 1] = (CPU_FNCT_VOID  )isr_fnct;         /* Add 1 to account for phantom vector                  */

    CPU_CRITICAL_ENTER();

    if (src_type == BSP_INT_SRC_TYPE_IRQ) {                     /* ---------------- CFG IRQ INTERRUPTS ---------------- */
        if (src_ch < BSP_INT_CH_32) {                           /* VIM channels 2 to 31                                 */
            DEF_BIT_CLR(BSP_INT_REG_FIRQPR0, DEF_BIT(src_ch));
        } else if (src_ch < BSP_INT_CH_64) {                    /* VIM channels 32 to 63                                */
            DEF_BIT_CLR(BSP_INT_REG_FIRQPR1, DEF_BIT(src_ch - BSP_INT_CH_32));
        } else {                                                /* VIM channels 64 to 95                                */
            DEF_BIT_CLR(BSP_INT_REG_FIRQPR2, DEF_BIT(src_ch - BSP_INT_CH_64));
        }

    } else {                                                    /* ---------------- CFG FIQ INTERRUPTS ---------------- */
        if (src_ch < BSP_INT_CH_32) {                           /* VIM channels 2 to 31                                 */
            DEF_BIT_SET(BSP_INT_REG_FIRQPR0, DEF_BIT(src_ch));
        } else if (src_ch < BSP_INT_CH_64) {                    /* VIM channels 32 to 63                                */
            DEF_BIT_SET(BSP_INT_REG_FIRQPR1, DEF_BIT(src_ch - BSP_INT_CH_32));
        } else {                                                /* VIM channels 64 to 95                                */
            DEF_BIT_SET(BSP_INT_REG_FIRQPR2, DEF_BIT(src_ch - BSP_INT_CH_64));
        }
    }

    prio_reg_nbr = src_ch / 4u;                                 /* See Note #1.                                         */
    prio_off     = 3u - (src_ch % 4u);
    reg_val      = src_nbr << (prio_off * 8u);
    prio_mask    = ~(0x000000FFu << (prio_off * 8u));

    BSP_INT_REG_CHANCTRL(prio_reg_nbr) &= prio_mask;
    BSP_INT_REG_CHANCTRL(prio_reg_nbr) |= reg_val;

    CPU_CRITICAL_EXIT();

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                           BSP_IntVectClr()
*
* Description : Un-intall an interrupt handler from vector table according to its interrupt channel.
*
* Argument(s) : src_ch      VIM Interrupt source channel.
*
* Return(s)   : DEF_OK,     If the vector was unregistered successfully.
*               DEF_FAIL,   otherwise.
*
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_IntVectClr (CPU_INT08U  src_ch)
{
    CPU_INT08U      prio_reg_nbr;
    CPU_INT08U      prio_off;
    CPU_INT32U      prio_mask;
    CPU_INT32U      reg_val;
    CPU_FNCT_VOID  *p_vect_tbl;


    if (src_ch > BSP_INT_CH_MAX - 2u) {                        /* Channel 95 is not programmable                        */
        return (DEF_FAIL);
    }

    p_vect_tbl             = (CPU_FNCT_VOID *)BSP_INT_ADDR_INT_TBL;
    p_vect_tbl[src_ch + 1] = (CPU_FNCT_VOID  )BSP_IntHandlerDummy; /* Add 1 to account for phantom vector               */

    prio_reg_nbr = src_ch / 4u;
    prio_off     = 3u - (src_ch % 4u);
    reg_val      = src_ch << (prio_off * 8u);
    prio_mask    = ~(0x000000FFu << (prio_off * 8u));

    BSP_INT_REG_CHANCTRL(prio_reg_nbr) &= prio_mask;
    BSP_INT_REG_CHANCTRL(prio_reg_nbr) |= reg_val;

    return (DEF_OK);
}


/*
*********************************************************************************************************
*                                         BSP_IntHandlerSrc()
*
* Description : Global interrupt handler.
*
* Argument(s) : src_id       Interrupt request Exception ID.
*
*                               CPU_ARM_EXCEPT_IRQ   Interrupt request.
*                               CPU_ARM_EXCEPT_FIQ   Fast interrupt request.
* Return(s)   : None.
*
* Caller(s)   : Application.
*
* Note(s)     : 1) The FIQ implemented in Cortex-R4F is Non-maskable Fast Interrupt(NMFI). Once FIQ is
*                  enable (by clearing F bit in CPSR, it can NOT be disabled by setting F bit in CPSR.
*                  Only a reset or an FIQ will be able to set the F bit in CPSR. Therefore, when using
*                  FIQ interrupts make sure that there are no OS services calls being done from its ISRs
*********************************************************************************************************
*/

void  BSP_IntHandlerSrc (CPU_INT16U  src_id)
{
    CPU_FNCT_VOID  isr_fnct;
    CPU_REG32      *p_vim_tbl;
    CPU_INT32U      ch_ix;
    CPU_INT32U      pend_reg_0;
    CPU_INT32U      pend_reg_1;
    CPU_INT32U      pend_reg_2;
    CPU_INT32U      pend_mask;

    switch (src_id) {
        case OS_CPU_ARM_EXCEPT_IRQ:
             ch_ix     = (CPU_INT32U     )BSP_INT_REG_IRQ_INDEX;
             p_vim_tbl = (CPU_REG32     *)BSP_INT_ADDR_INT_TBL;
             isr_fnct  = (CPU_FNCT_VOID  )p_vim_tbl[ch_ix];

             if (isr_fnct != (CPU_FNCT_VOID)0) {
                 pend_reg_0 = BSP_INT_REG_REQENACLR0;           /* Store interrupt state                                */
                 pend_reg_1 = BSP_INT_REG_REQENACLR1;
                 pend_reg_2 = BSP_INT_REG_REQENACLR2;
                 ch_ix--;
                 if (ch_ix <= 31) {                             /* Dis. all interrupts of lower priority than current   */
                     pend_mask = 0xFFFFFFFF << ch_ix;
                     BSP_INT_REG_REQENACLR0 = pend_mask;
                     BSP_INT_REG_REQENACLR1 = 0xFFFFFFFF;
                     BSP_INT_REG_REQENACLR2 = 0xFFFFFFFF;
                 } else if (ch_ix <= 63) {
                     pend_mask = 0xFFFFFFFF << (ch_ix - 32);
                     BSP_INT_REG_REQENACLR1 = pend_mask;
                     BSP_INT_REG_REQENACLR2 = 0xFFFFFFFF;
                 } else {
                     pend_mask = 0xFFFFFFFF << (ch_ix - 64);
                     BSP_INT_REG_REQENACLR2 = pend_mask;
                 }
                 CPU_IntEn();                                   /* Enable high-priority interrupts                      */
                 (*isr_fnct)();                                 /* Invoke ISR                                           */
                 CPU_IntDis();                                  /* Disable interrupts                                   */
                 BSP_INT_REG_REQENASET0 = pend_reg_0;           /* Restore original interrupt state                     */
                 BSP_INT_REG_REQENASET1 = pend_reg_1;
                 BSP_INT_REG_REQENASET2 = pend_reg_2;
             }
             break;

        case OS_CPU_ARM_EXCEPT_FIQ:                             /* See Note #1.                                         */
        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                       BSP_IntHandlerDummy()
*
* Description : Dummy interrupt handler.
*
* Argument(s) : None.
*
* Return(s)   : None.
*
* Caller(s)   : BSP_IntHandlerSrc().
*
* Note(s)     : None.
*********************************************************************************************************
*/

static  void  BSP_IntHandlerDummy(void)
{
    while (DEF_TRUE) {
        ;
    }
}
