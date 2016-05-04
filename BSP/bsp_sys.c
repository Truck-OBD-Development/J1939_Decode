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
* Filename      : bsp_sys.c
* Version       : V1.00
* Programmer(s) : FF
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDES
*********************************************************************************************************
*/

#include <cpu_core.h>
#include <bsp_cfg.h>
#include <bsp_sys.h>
#include <bsp_int.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

                                                                /* --------------------- CLOCK SOURCES ---------------- */
#define  BSP_SYS_CLK_SRC_NBR_OSCIN                         0u
#define  BSP_SYS_CLK_SRC_NBR_FM_PLL                        1u
#define  BSP_SYS_CLK_SRC_NBR_EXT_CLK1                      3u
#define  BSP_SYS_CLK_SRC_NBR_CLK_80K                       4u
#define  BSP_SYS_CLK_SRC_NBR_CLK_100M                      5u
#define  BSP_SYS_CLK_SRC_NBR_CLK_FPLL                      6u
#define  BSP_SYS_CLK_SRC_NBR_EXT_CLK2                      7u

#define  BSP_SYS_CLK_SRC_FREQ_CLK_80K                  80000u
#define  BSP_SYS_CLK_SRC_FREQ_CLK_10M                8000000u


#define  BSP_BIT_PLLCTL1_BYPASSONSLIP                      2u
#define  BSP_BIT_PLLCTL1_REFCLKDIV                         5u
#define  BSP_BIT_PLLCTL1_PLLMUL                          119u

#define  BSP_BIT_PLLCTL2_SPREADINGRATE                   255u
#define  BSP_BIT_PLLCTL2_ODPLL                             1u
#define  BSP_BIT_PLLCTL2_SPREADAMOUNT                     61u

#define  BSP_BIT_PLLCTL3_ODPLL                             1u
#define  BSP_BIT_PLLCTL3_PLLMUL                            9u


#define  BSP_BIT_SYS_LPOMONCTL_BIASEN              DEF_BIT_24
#define  BSP_BIT_SYS_LPOMONCTL_HTRIMVAL_6592               8u
#define  BSP_BIT_SYS_LPOMONCTL_LTRIMVAL_6086               8u

#define  BSP_BIT_SYS_CLKCNTRL_PENA                 DEF_BIT_08

#define  BSP_SYS_PER_CLK_NBR_PS_MAX                       32u   /* Maximum number of peripheral selects (PS) signals.   */
#define  BSP_SYS_PER_CLK_NBR_QUAD                          4u
                                                                /* Number of periphrelas selects per registers          */
#define  BSP_SYS_PER_CLK_NBR_PS_PER_REG       (BSP_SYS_PER_CLK_NBR_PS_MAX / \
                                               BSP_SYS_PER_CLK_NBR_QUAD)


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  CPU_INT32U  BSP_Sys_PLL_MainFreqGet(void);
static  CPU_INT32U  BSP_Sys_PLL_FlexFreqGet(void);
static  CPU_INT32U  BSP_Sys_SrcClkFreqGet  (CPU_INT08U  src);


/*
*********************************************************************************************************
*                                         BSP SYSTEM INITIALIZATION
*
* Description : This function should be called early in the BSP initialization process.
*
* Arguments   : None
*
* Return(s)   : None.
*
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

void  BSP_SysInit (void)
{
#if 0
    CPU_REG32   reg_to;
    CPU_INT32U  region_access;
    CPU_INT08U  region_nbr;
    CPU_INT32U  region_size;
    CPU_INT32U  region_addr;
#endif


    CPU_IntDis();                                               /* Disable all interrupts.                              */
    BSP_IntInit();                                              /* Initialize Interrupt controller module.              */

#if 0
                                                                /* ------------ FLASH MEMORY INITIALIZATION ----------- */
    BSP_REG_FRDCNTL       = BSP_BIT_FRDCNTL_PIPE_EN             /* ... Enable Pipeline mode.                            */
                          | BSP_BIT_FRDCNTL_ASWSTEN             /* ... Address setup wait state enable.                 */
                          | (2 << 8u);                          /* ... Random/data Read Wait State.                     */

    BSP_REG_FBFALLBACK    = BSP_BIT_FBFALLBACK_ACTIVE           /* ... Seet al bank in fallback active mode.            */
                          | (BSP_BIT_FBFALLBACK_ACTIVE << 2u)
                          | (BSP_BIT_FBFALLBACK_ACTIVE << 4u)
                          | (BSP_BIT_FBFALLBACK_ACTIVE << 6u);

    BSP_SYS_REG_LPOMONCTL = BSP_BIT_SYS_LPOMONCTL_BIASEN        /* Configure the LPO clock monitor control register.    */
                          | (BSP_BIT_SYS_LPOMONCTL_HTRIMVAL_6592 << 8u)
                          | BSP_BIT_SYS_LPOMONCTL_LTRIMVAL_6086;

    BSP_SYS_REG_PLL_CTL1  = DEF_BIT_NONE                        /* Configure FMzPLL.                                    */
                          | (BSP_BIT_PLLCTL1_BYPASSONSLIP  << 29u)
                          | (BSP_BIT_PLLCTL1_REFCLKDIV     << 16u)
                          | (BSP_BIT_PLLCTL1_PLLMUL        << 8u );

    BSP_SYS_REG_PLL_CTL2  = DEF_BIT_NONE
                          | (BSP_BIT_PLLCTL2_SPREADINGRATE << 22u)
                          | (BSP_BIT_PLLCTL2_ODPLL         << 9u )
                          | BSP_BIT_PLLCTL2_SPREADAMOUNT;

    BSP_SYS_REG_PLL_CTL3  = (BSP_BIT_PLLCTL3_ODPLL  << 22u)
                          | (BSP_BIT_PLLCTL3_PLLMUL << 8u );

    DEF_BIT_CLR(BSP_SYS_REG_CSDIS, DEF_BIT_01);                 /* Enable FMzPLL domain clock.                          */

    reg_to = 0xFFFFu;                                           /* Wait until the clock domain is set.                  */
    while ((reg_to > 0u) &&
          (DEF_BIT_IS_CLR_ANY(BSP_SYS_REG_CSVSTAT, (DEF_BIT_00 | DEF_BIT_01)))) {
       reg_to--;
    }

    if (reg_to != 0u) {                                         /* If the FMzPLL clock is valid? ...                    */
                                                                /* ... Set the FMzPLL as source clock (see note #2a)    */
        BSP_SYS_REG_GHVSR    =  BSP_SYS_CLK_SRC_NBR_FM_PLL
                             | (BSP_SYS_CLK_SRC_NBR_FM_PLL << 24u)
                             | (BSP_SYS_CLK_SRC_NBR_FM_PLL << 16u);
                                                                /* ... Set the Peripheral clock source.                 */
        BSP_SYS_REG_VCLKASRC = ((0xFFFFu)      )
                             | ((0xFFFFu) << 8u);
    }

    BSP_SYS_REG_CLKCNTRL = (1u << 24u)
                         | (1u << 16u)
                         | BSP_BIT_SYS_CLKCNTRL_PENA;           /* Enable peripheral bit.                               */

                                                                /* ----------------- CONFIGURE MPU ------------------- */
    region_nbr    = 0u;                                         /* Configure default R4 MPU region for RAM/FLASH       */
    region_access = CPU_ARM_MPU_ACCESS_TYPE_NORMAL_OI_NONE
                  | CPU_ARM_MPU_ACCESS_PERM_USER_FULL
                  | CPU_ARM_MPU_ACCESS_SHARE;

    region_addr   = 0x00000000u;
    region_size   = (3 * 1024u * 1024u);              // Micrium: (16 * 1024u);

    CPU_MPU_RegionEn(region_nbr,
                     region_addr,
                     DEF_BIT_NONE,
                     region_size - 1u,
                     region_access);

                                                                /* Configure the EMIF MPU region to be strongly ...     */
                                                                /* ... ordered                                          */
    region_nbr++;
    region_access = CPU_ARM_MPU_ACCESS_TYPE_STRONG_ORDERED
                  | CPU_ARM_MPU_ACCESS_PERM_USER_FULL;

    region_addr   = 0x60000000u;
    region_size   = (256u * 1024u * 1024);
    CPU_MPU_RegionEn(region_nbr,
                     region_addr,
                     DEF_BIT_NONE,
                     region_size - 1u,
                     region_access);

                                                                /* Cfg. peripheral frame1 & System module MPU region... */
                                                                /* ...  to be strongly ordered                          */
    region_nbr++;
    region_access = CPU_ARM_MPU_ACCESS_TYPE_STRONG_ORDERED
                  | CPU_ARM_MPU_ACCESS_PERM_USER_FULL;
    region_addr   = 0xFF000000u;
    region_size   = (16u * 1024u * 1024);
    CPU_MPU_RegionEn(region_nbr,
                     region_addr,
                     DEF_BIT_NONE,
                     region_size - 1u,
                     region_access);

                                                                /* Cfg. peripheral frame2 MPU region to be strongly...  */
                                                                /* ... ordered                                          */
    region_nbr++;
    region_access = CPU_ARM_MPU_ACCESS_TYPE_STRONG_ORDERED
                  | CPU_ARM_MPU_ACCESS_PERM_USER_FULL;
    region_addr   = 0xFC000000u;
    region_size   = (16u * 1024u * 1024);
    CPU_MPU_RegionEn(region_nbr,
                     region_addr,
                     DEF_BIT_NONE,
                     region_size - 1u,
                     region_access);

                                                                /* Configure R4 MPU region for RAM and Flash           */
    region_nbr++;
    region_access = CPU_ARM_MPU_ACCESS_TYPE_NORMAL_OI_NONE
                  | CPU_ARM_MPU_ACCESS_PERM_USER_FULL
                  | CPU_ARM_MPU_ACCESS_SHARE;
    region_addr   = 0x08000000u;
    region_size   = (256u * 1024u);                      /// Micrium: (512u * 1024u * 1024);
    CPU_MPU_RegionEn(region_nbr,
                     region_addr,
                     DEF_BIT_NONE,
                     region_size - 1u,
                     region_access);

    CPU_MPU_En();
#endif
}


/*
*********************************************************************************************************
*                                       BSP_Sys_CPU_ClkFreqGet()
*
* Description : Return CPU clock frequency.
*
* Argument(s) : None.
*
* Return(s)   : The CPU frequency in Hertz.
*
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

CPU_INT32U  BSP_Sys_CPU_ClkFreqGet (void)
{
    CPU_INT08U  clk_src;
    CPU_INT32U  cpu_freq;


    clk_src  = BSP_SYS_REG_GHVSR & DEF_BIT_FIELD(4u, 0u);
    cpu_freq = 0u;

    cpu_freq = BSP_Sys_SrcClkFreqGet(clk_src);

    return (cpu_freq);
}


/*
*********************************************************************************************************
*                                         BSP_SysClkFreqGet()
*
* Description : Return system clock frequency.
*
* Argument(s) : clk_nbr     System clock number. (See 'bsp_sys.h' for clock descriptions)
*
*                   BSP_SYS_CLK_NBR_GCLK_00
*                   BSP_SYS_CLK_NBR_HCLK_00
*                   BSP_SYS_CLK_NBR_VCLK_PER_00
*                   BSP_SYS_CLK_NBR_VCLK_02
*                   BSP_SYS_CLK_NBR_VCLK_03
*                   BSP_SYS_CLK_NBR_AVCLK_01
*                   BSP_SYS_CLK_NBR_AVCLK_02
*                   BSP_SYS_CLK_NBR_RTI_CLK_01
*                   BSP_SYS_CLK_NBR_RTI_CLK_02
*                   BSP_SYS_CLK_NBR_VCLK_SYS_00
*
* Return(s)   : The system clock frequency.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U  BSP_SysClkFreqGet (CPU_INT16U  clk_nbr)
{
    CPU_INT32U  sys_clk_freq;
    CPU_INT08U  clk_src;
    CPU_INT08U  clk_div;


    clk_div = 1u;
    clk_src = 0u;

    switch (clk_nbr) {
        case BSP_SYS_CLK_NBR_RTI_CLK_01:
             clk_src = (BSP_SYS_REG_RCLKSRC      ) & DEF_BIT_FIELD(4u, 0u);
             clk_div = (BSP_SYS_REG_RCLKSRC >> 8u) & DEF_BIT_FIELD(2u, 0u);
             clk_div = DEF_BIT(clk_div);
             break;

        case BSP_SYS_CLK_NBR_RTI_CLK_02:
             clk_src = (BSP_SYS_REG_RCLKSRC >> 16u) & DEF_BIT_FIELD(4u, 0u);
             clk_div = (BSP_SYS_REG_RCLKSRC >> 24u) & DEF_BIT_FIELD(2u, 0u);
             clk_div = DEF_BIT(clk_div);
             break;

        case BSP_SYS_CLK_NBR_AVCLK_01:
             clk_src = BSP_SYS_REG_VCLKASRC & DEF_BIT_FIELD(4u, 0u);
             break;

        case BSP_SYS_CLK_NBR_AVCLK_02:
             clk_src = (BSP_SYS_REG_VCLKASRC >> 8u) & DEF_BIT_FIELD(4u, 0u);
             break;

        case BSP_SYS_CLK_NBR_GCLK_00:
        case BSP_SYS_CLK_NBR_HCLK_00:
        case BSP_SYS_CLK_NBR_VCLK_SYS_00:
        case BSP_SYS_CLK_NBR_VCLK_PER_00:
        case BSP_SYS_CLK_NBR_VCLK_02:
        case BSP_SYS_CLK_NBR_VCLK_03:
             break;

        default:
             return (0u);
    }

    if (clk_src > BSP_SYS_CLK_SRC_NBR_EXT_CLK2) {
        clk_nbr = BSP_SYS_CLK_NBR_VCLK_PER_00;
    }

    switch (clk_nbr) {
        case BSP_SYS_CLK_NBR_GCLK_00:
        case BSP_SYS_CLK_NBR_HCLK_00:
        case BSP_SYS_CLK_NBR_VCLK_SYS_00:
        case BSP_SYS_CLK_NBR_VCLK_PER_00:
        case BSP_SYS_CLK_NBR_VCLK_02:
        case BSP_SYS_CLK_NBR_VCLK_03:
             clk_src = BSP_SYS_REG_GHVSR & DEF_BIT_FIELD(4u, 0u);

             if ((clk_nbr == BSP_SYS_CLK_NBR_VCLK_SYS_00) ||
                 (clk_nbr == BSP_SYS_CLK_NBR_VCLK_PER_00)) {
                 clk_div  = (BSP_SYS_REG_CLKCNTRL >> 16u) & DEF_BIT_FIELD(4u, 0u);
                 clk_div += 1u;
             }

             if (clk_nbr == BSP_SYS_CLK_NBR_VCLK_02) {
                 clk_div  = (BSP_SYS_REG_CLKCNTRL >> 24u) & DEF_BIT_FIELD(4u, 0u);
                 clk_div += 1u;
             }

             if (clk_nbr == BSP_SYS_CLK_NBR_VCLK_03) {
                 clk_div  = (BSP_SYS_REG_CLK2CNTRL) & DEF_BIT_FIELD(4u, 0u);
                 clk_div += 1u;
             }
             break;

        default:
            break;
    }

    sys_clk_freq  = BSP_Sys_SrcClkFreqGet(clk_src);
    sys_clk_freq /= clk_div;

    return (sys_clk_freq);
}


/*
*********************************************************************************************************
*                                      BSP_Sys_PLL_MainFreqGet()
*
* Description : Return the frequency of the FMzPLL (Frequency modulated zero-pin).
*
* Argument(s) : None.
*
* Return(s)   : FMzPLL frequency in hertz (Hz).
*
* Caller(s)   : BSP_Sys_SrcClkFreqGet()
*
* Note(s)     : (1) The FMZPLL module can be operated in either modulation or non-modulation mode.
*
*                   (a) #### Only non-modulation mode is supported in this function.
*
*               (2) The FMzPLL frequency is determined by:
*
*                               Foscin         NF
*                    Fpll =  ------------ x --------
*                                NR          OD x R
*
*                                          NF
*                    Fpll =  Fint_clk x --------
*                                        OD x R
*                    where:
*
*                    NR = The Prescale divider (1 to 64) divides the PLL input (CLKIN) for use as internal
*                         clock (INTCLK).
*
*                    NF = The multiplier has a range of 92 to 184.
*
*                    OD = Postscale divider.
*
*                     R = Postcale divider.
*********************************************************************************************************
*/

static  CPU_INT32U  BSP_Sys_PLL_MainFreqGet (void)
{
    CPU_INT08U  pll_div;
    CPU_INT16U  pll_mul;
    CPU_INT32U  reg_val_0;
    CPU_INT32U  reg_val_1;
    CPU_INT32U  pll_freq;


    reg_val_0 = BSP_SYS_REG_PLL_CTL1;
    reg_val_1 = BSP_SYS_REG_PLL_CTL2;

    pll_freq  = BSP_CFG_SYS_EXT_CLK_FREQ;                       /* Foscin = Main XTAL.                                  */
                                                                /* Read the prescaler divider.                          */
    pll_div   = ((reg_val_0 >> 16u) & DEF_BIT_FIELD(6u, 0u))
              + 1u;

    pll_freq /= pll_div;                                        /* Calculate Fintclk = Foscin / NR.                     */


    pll_mul   = reg_val_0 & DEF_BIT_FIELD(16u, 0u);             /* Read the multiplier value.                           */

    pll_mul   =  (pll_mul / 256u ) + 1u;
    pll_freq  = ((pll_freq * pll_mul) + 1000)/ 1000u;           /* Calculate (Fintclk * NF) term.                       */

    pll_freq *= 1000u;                                          /* Round up the clock value.                            */

    pll_div   = (reg_val_0 >> 4u);                              /* Read the postscale dividers (OD, R).                 */

    pll_div   = (((reg_val_1 >> 9u) & DEF_BIT_FIELD(3u, 0u)) + 1u);
    pll_freq /= pll_div;

    pll_div   = (((reg_val_0 >> 24u) & DEF_BIT_FIELD(5u, 0u)) + 1u);
    pll_freq /= pll_div;                                        /* Calculate the PLL output frequency.                  */

    return (pll_freq);
}


/*
*********************************************************************************************************
*                                       BSP_Sys_SrcClkFreqGet()
*
* Description : Return the frequency of the FPLL (Flexray phase-locked loop) module.
*
* Argument(s) : None.
*
* Return(s)   : FPLL clock.
*
* Caller(s)   : BSP_SYS_SrcClkFreqGet()
*
* Note(s)     : (1) The FPLL frequency is determined by:
*
*                               Foscin         NF
*                    Fpll =  ------------ x --------
*                                NR             R
*
*                                          NF
*                    Fpll =  Fint_clk x --------
*                                          R
*                    where:
*
*                    NR = The Prescale divider has a range of 1 to 2, it  divides the PLL input
*                         (CLKIN) for use as internal clock (INTCLK).
*
*                    NF = The multiplier has a range of 1 to 15.
*
*                     R = Postcale divider has a range of 1 to 8.
*********************************************************************************************************
*/

static  CPU_INT32U  BSP_Sys_PLL_FlexFreqGet (void)
{
    CPU_INT08U  pll_div;
    CPU_INT16U  pll_mul;
    CPU_INT32U  reg_val;
    CPU_INT64U  pll_freq;


    reg_val  = BSP_SYS_REG_PLL_CTL3;

    pll_freq = BSP_CFG_SYS_EXT_CLK_FREQ;                        /* Foscin = Main XTAL.                                  */

    pll_mul    = reg_val & DEF_BIT_FIELD(16u, 0u);              /* Read the multiplier value.                           */
    pll_freq  *= pll_mul;                                       /* Calculate (Fintclk * NF) term.                       */
    pll_freq >>= 8;
    pll_freq  += BSP_CFG_SYS_EXT_CLK_FREQ;

    pll_div    = (reg_val >> 16) & DEF_BIT_FIELD(8u, 0);        /* Read the postscale divider  (R).                     */
    pll_div++;

    if (pll_div > 0x3F) {
        return (0);
    }

    pll_freq /= pll_div;                                        /* Calculate the PLL output frequency.                  */

    return ((CPU_INT32U)pll_freq);
}


/*
*********************************************************************************************************
*                                       BSP_Sys_SrcClkFreqGet()
*
* Description : Return the clock for a specific clk source.
*
* Argument(s) : clk_src     clock source.
*
*                   BSP_SYS_CLK_SRC_NBR_OSCIN       Maiin oscillator.
*                   BSP_SYS_CLK_SRC_NBR_FM_PLL      Main PLL
*                   BSP_SYS_CLK_SRC_NBR_CLK_80K     Low-frequency output.
*                   BSP_SYS_CLK_SRC_FREQ_CLK_10M    High-frequnecy output.
*                   BSP_SYS_CLK_SRC_NBR_CLK_FPLL    Dedicated PLL for the FlexRay protocol.
*
* Return(s)   : Source clock frequency in hertz (Hz).
*
* Caller(s)   : Application.
*
* Note(s)     : None.
*********************************************************************************************************
*/

static  CPU_INT32U  BSP_Sys_SrcClkFreqGet(CPU_INT08U  clk_src)
{
    CPU_INT32U  clk_src_freq;


    clk_src_freq = 0;

    switch (clk_src) {
        case BSP_SYS_CLK_SRC_NBR_OSCIN:
             clk_src_freq = BSP_CFG_SYS_EXT_CLK_FREQ;
             break;

        case BSP_SYS_CLK_SRC_NBR_FM_PLL:
             clk_src_freq = BSP_Sys_PLL_MainFreqGet();
             break;

        case BSP_SYS_CLK_SRC_NBR_CLK_80K:
             clk_src_freq = BSP_SYS_CLK_SRC_FREQ_CLK_80K;
             break;

        case BSP_SYS_CLK_SRC_NBR_CLK_100M:
             clk_src_freq = BSP_SYS_CLK_SRC_FREQ_CLK_10M;
             break;

        case BSP_SYS_CLK_SRC_NBR_CLK_FPLL:
             clk_src_freq = BSP_Sys_PLL_FlexFreqGet();
             break;

        default:
             break;
    }

    return (clk_src_freq);
}


/*
*********************************************************************************************************
*                                          BSP_SysPerClkEn()
*
* Description : Enable a peripheral clock.
*
* Argument(s) : clk_nbr     Peripheral clock number.
*
* Return(s)   : None.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Peripheral clk number are defined in 'bsp_sys.h'.
*
*                       BSP_SYS_PER_CLK_NBR_XX where XX is the peripheral name.
*********************************************************************************************************
*/

void  BSP_SysPerClkEn (CPU_INT16U  clk_nbr)
{
    CPU_INT08U  reg_off;
    CPU_INT08U  quad_off;


    if (clk_nbr < BSP_SYS_PER_CLK_NBR_PS_OFFSET) {               /* Peripheral Memory address.                           */
        if (clk_nbr <= BSP_SYS_PER_CLK_NBR_PCS_ADC_01) {
            BSP_SYS_REG_PCSPWRDWNCLR0 = DEF_BIT(clk_nbr);
        } else {
            BSP_SYS_REG_PCSPWRDWNCLR1 = DEF_BIT(clk_nbr);
        }
    } else {
       clk_nbr  -= BSP_SYS_PER_CLK_NBR_PS_OFFSET;                /* Peripheral register.                                 */
       reg_off   = clk_nbr / BSP_SYS_PER_CLK_NBR_PS_PER_REG;
       quad_off  = clk_nbr % BSP_SYS_PER_CLK_NBR_PS_PER_REG;
       quad_off *= BSP_SYS_PER_CLK_NBR_QUAD;

       switch (reg_off) {
           case 0:
                BSP_SYS_REG_PSPWRDWNCLR0 = DEF_BIT_FIELD(BSP_SYS_PER_CLK_NBR_QUAD, (quad_off));
                break;

           case 1:
                BSP_SYS_REG_PSPWRDWNCLR1 = DEF_BIT_FIELD(BSP_SYS_PER_CLK_NBR_QUAD, (quad_off));
                break;

           case 2:
                BSP_SYS_REG_PSPWRDWNCLR2 = DEF_BIT_FIELD(BSP_SYS_PER_CLK_NBR_QUAD, (quad_off));
                break;

           case 3:
                BSP_SYS_REG_PSPWRDWNCLR3 = DEF_BIT_FIELD(BSP_SYS_PER_CLK_NBR_QUAD, (quad_off));
                break;

           default:
                break;
       }
    }
}


/*
*********************************************************************************************************
*                                         BSP_SysPerClkDis()
*
* Description : Disable a peripheral clock.
*
* Argument(s) : clk_nbr     Peripheral clock number.
*
* Return(s)   : None.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) Peripheral clk number are defined in 'bsp_sys.h'.
*
*                       BSP_SYS_PER_CLK_NBR_XX where XX is the peripheral name.
*********************************************************************************************************
*/

void  BSP_SysPerClkDis (CPU_INT16U  clk_nbr)
{
    CPU_INT08U  quad_off;
    CPU_INT08U  reg_off;


    if (clk_nbr < BSP_SYS_PER_CLK_NBR_PS_OFFSET) {              /* Peripheral Memory address.                           */
        if (clk_nbr <= BSP_SYS_PER_CLK_NBR_PCS_ADC_01) {
            BSP_SYS_REG_PCSPWRDWNSET0 = DEF_BIT(clk_nbr);
        } else {
            BSP_SYS_REG_PCSPWRDWNSET1 = DEF_BIT(clk_nbr);
        }
    } else {
       clk_nbr  -= BSP_SYS_PER_CLK_NBR_PS_OFFSET;               /* Peripheral register.                                 */
       reg_off   = clk_nbr / BSP_SYS_PER_CLK_NBR_PS_PER_REG;
       quad_off  = clk_nbr % BSP_SYS_PER_CLK_NBR_PS_PER_REG;
       quad_off *= BSP_SYS_PER_CLK_NBR_QUAD;

       switch (reg_off) {
           case 0:
                BSP_SYS_REG_PSPWRDWNSET0 = DEF_BIT_FIELD(BSP_SYS_PER_CLK_NBR_QUAD, (quad_off * BSP_SYS_PER_CLK_NBR_QUAD));
                break;

           case 1:
                BSP_SYS_REG_PSPWRDWNSET1 = DEF_BIT_FIELD(BSP_SYS_PER_CLK_NBR_QUAD, (quad_off * BSP_SYS_PER_CLK_NBR_QUAD));
                break;

           case 2:
                BSP_SYS_REG_PSPWRDWNSET2 = DEF_BIT_FIELD(BSP_SYS_PER_CLK_NBR_QUAD, (quad_off * BSP_SYS_PER_CLK_NBR_QUAD));
                break;

           case 3:
                BSP_SYS_REG_PSPWRDWNSET3 = DEF_BIT_FIELD(BSP_SYS_PER_CLK_NBR_QUAD, (quad_off * BSP_SYS_PER_CLK_NBR_QUAD));
                break;

           default:
                break;
       }
    }
}


/*
*********************************************************************************************************
*                                        BSP_SysPerClkFreqGet()
*
* Description : Return peripheral clock frequency.
*
* Argument(s) : clk_nbr     Peripheral clock number. (see 'BSP_SysPerClkDis()' note #1).
*
* Return(s)   : The peripheral clock frequency.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) All peripherals clocks are clocked from the following system clocks:
*
*                       BSP_SYS_CLK_NBR_VCLK_00
*                       BSP_SYS_CLK_NBR_VCLK_02
*                       BSP_SYS_CLK_NBR_AVCLK_01
*                       BSP_SYS_CLK_NBR_AVCLK_02
*                       BSP_SYS_CLK_NBR_RTI_CLK_01
*                       BSP_SYS_CLK_NBR_RTI_CLK_02
*
*********************************************************************************************************
*/

CPU_INT32U  BSP_SysPerClkFreqGet (CPU_INT16U  clk_nbr)
{

    CPU_INT32U  per_clk_freq;

    switch (clk_nbr) {
        case BSP_SYS_PER_CLK_NBR_PCS_SPI_05:
        case BSP_SYS_PER_CLK_NBR_PCS_SPI_03:
        case BSP_SYS_PER_CLK_NBR_PCS_SPI_01:
        case BSP_SYS_PER_CLK_NBR_PS_MibSPI_05:
        case BSP_SYS_PER_CLK_NBR_PS_SPI_04:
        case BSP_SYS_PER_CLK_NBR_PS_SPI_02:
        case BSP_SYS_PER_CLK_NBR_PS_LIN_00:
        case BSP_SYS_PER_CLK_NBR_PCS_ADC_01:
        case BSP_SYS_PER_CLK_NBR_PCS_ADC_02:
        case BSP_SYS_PER_CLK_NBR_PS_ADC_01:
        case BSP_SYS_PER_CLK_NBR_PS_GPIO_00:
             per_clk_freq = BSP_SysClkFreqGet(BSP_SYS_CLK_NBR_VCLK_PER_00);
             break;

        case BSP_SYS_PER_CLK_NBR_PCS_HET_01:
        case BSP_SYS_PER_CLK_NBR_PCS_HET_02:
        case BSP_SYS_PER_CLK_NBR_PCS_HETTU_01:
        case BSP_SYS_PER_CLK_NBR_PCS_HETTU_02:
        case BSP_SYS_PER_CLK_NBR_PS_HET_01:
        case BSP_SYS_PER_CLK_NBR_PS_HETTU_01:
             per_clk_freq = BSP_SysClkFreqGet(BSP_SYS_CLK_NBR_VCLK_02);
             break;

        case BSP_SYS_PER_CLK_NBR_PCS_CAN_03:
        case BSP_SYS_PER_CLK_NBR_PCS_CAN_02:
        case BSP_SYS_PER_CLK_NBR_PCS_CAN_01:
        case BSP_SYS_PER_CLK_NBR_PS_CAN_03:
        case BSP_SYS_PER_CLK_NBR_PS_CAN_01:
             per_clk_freq = BSP_SysClkFreqGet(BSP_SYS_CLK_NBR_AVCLK_01);
             break;

        default:
             break;
    }

    return ((CPU_INT32U)(per_clk_freq));
}
