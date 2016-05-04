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
* Filename      : bsp_sys.h
* Version       : V1.00
* Programmer(s) : FF
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                               MODULE
*
* Note(s) : (1) This BSP serial header file is protected from multiple pre-processor inclusion through
*               use of the BSP serial present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_SYS_PRESENT
#define  BSP_SYS_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                           REGISTER DEFINES
*********************************************************************************************************
*/

#define  BSP_SYS_ADDR_SYS1_BASE                    (CPU_INT32U )(0xFFFFFF00u)
#define  BSP_SYS_ADDR_SYS2_BASE                    (CPU_INT32U )(0xFFFFE100u)
#define  BSP_SYS_ADDR_PER_BASE                     (CPU_INT32U )(0xFFFFE000u)

                                                                /* ----------- CLOCK SOURCE DISABLE REGISTERS --------- */
#define  BSP_SYS_REG_CSDIS                       (* (CPU_REG32 *)(BSP_SYS_ADDR_SYS1_BASE + 0x30u))
#define  BSP_SYS_REG_CDDIS                       (* (CPU_REG32 *)(BSP_SYS_ADDR_SYS1_BASE + 0x3Cu))

                                                                /* ----------- CLOCK DOMAIN DISABLE REGISTERS --------- */
#define  BSP_SYS_REG_GHVSR                       (* (CPU_REG32 *)(BSP_SYS_ADDR_SYS1_BASE + 0x48u))
#define  BSP_SYS_REG_VCLKASRC                    (* (CPU_REG32 *)(BSP_SYS_ADDR_SYS1_BASE + 0x4Cu))
#define  BSP_SYS_REG_RCLKSRC                     (* (CPU_REG32 *)(BSP_SYS_ADDR_SYS1_BASE + 0x50u))
#define  BSP_SYS_REG_CSVSTAT                     (* (CPU_REG32 *)(BSP_SYS_ADDR_SYS1_BASE + 0x54u))

#define  BSP_SYS_REG_PLL_CTL1                    (* (CPU_REG32 *)(BSP_SYS_ADDR_SYS1_BASE + 0x70u))
#define  BSP_SYS_REG_PLL_CTL2                    (* (CPU_REG32 *)(BSP_SYS_ADDR_SYS1_BASE + 0x74u))
#define  BSP_SYS_REG_PLL_CTL3                    (* (CPU_REG32 *)(BSP_SYS_ADDR_SYS2_BASE + 0x00u))

#define  BSP_SYS_REG_LPOMONCTL                   (* (CPU_REG32 *)(BSP_SYS_ADDR_SYS1_BASE + 0x88u))

#define  BSP_SYS_REG_CLKCNTRL                    (* (CPU_REG32 *)(BSP_SYS_ADDR_SYS1_BASE + 0xD0u))

#define  BSP_SYS_REG_PLLCTL3                     (* (CPU_REG32 *)(BSP_SYS_ADDR_SYS2_BASE + 0x00u))
#define  BSP_SYS_REG_CLK2CNTRL                   (* (CPU_REG32 *)(BSP_SYS_ADDR_SYS2_BASE + 0x3Cu))
#define  BSP_SYS_REG_VCLKACON1                   (* (CPU_REG32 *)(BSP_SYS_ADDR_SYS2_BASE + 0x40u))

#define  BSP_SYS_REG_PCSPWRDWNSET0               (* (CPU_REG32 *)(BSP_SYS_ADDR_PER_BASE  + 0x60u))
#define  BSP_SYS_REG_PCSPWRDWNSET1               (* (CPU_REG32 *)(BSP_SYS_ADDR_PER_BASE  + 0x64u))

#define  BSP_SYS_REG_PCSPWRDWNCLR0               (* (CPU_REG32 *)(BSP_SYS_ADDR_PER_BASE  + 0x70u))
#define  BSP_SYS_REG_PCSPWRDWNCLR1               (* (CPU_REG32 *)(BSP_SYS_ADDR_PER_BASE  + 0x74u))

#define  BSP_SYS_REG_PSPWRDWNSET0                (* (CPU_REG32 *)(BSP_SYS_ADDR_PER_BASE  + 0x80u))
#define  BSP_SYS_REG_PSPWRDWNSET1                (* (CPU_REG32 *)(BSP_SYS_ADDR_PER_BASE  + 0x84u))
#define  BSP_SYS_REG_PSPWRDWNSET2                (* (CPU_REG32 *)(BSP_SYS_ADDR_PER_BASE  + 0x88u))
#define  BSP_SYS_REG_PSPWRDWNSET3                (* (CPU_REG32 *)(BSP_SYS_ADDR_PER_BASE  + 0x8Cu))

#define  BSP_SYS_REG_PSPWRDWNCLR0                (* (CPU_REG32 *)(BSP_SYS_ADDR_PER_BASE  + 0xA0u))
#define  BSP_SYS_REG_PSPWRDWNCLR1                (* (CPU_REG32 *)(BSP_SYS_ADDR_PER_BASE  + 0xA4u))
#define  BSP_SYS_REG_PSPWRDWNCLR2                (* (CPU_REG32 *)(BSP_SYS_ADDR_PER_BASE  + 0xA8u))
#define  BSP_SYS_REG_PSPWRDWNCLR3                (* (CPU_REG32 *)(BSP_SYS_ADDR_PER_BASE  + 0xACu))


                                                                /* -------------- FLASH CONTROL REGISTERS ------------- */
#define  BSP_SYS_ADDR_FLASH_BASE                    (CPU_INT32U )(0xFFF87000u)
#define  BSP_REG_FRDCNTL                         (* (CPU_REG32 *)(BSP_SYS_ADDR_FLASH_BASE + 0x00))
#define  BSP_BIT_FRDCNTL_PIPE_EN                       DEF_BIT_00
#define  BSP_BIT_FRDCNTL_ASWSTEN                       DEF_BIT_04
#define  BSP_MSK_FRDCNTL_RWAIT                         DEF_BIT_FIELD(4u, 8u)

#define  BSP_REG_FBFALLBACK                      (* (CPU_REG32 *)(BSP_SYS_ADDR_FLASH_BASE + 0x40))
#define  BSP_BIT_FBFALLBACK_SLEEP                      0u
#define  BSP_BIT_FBFALLBACK_STANDBY                    1u
#define  BSP_BIT_FBFALLBACK_ACTIVE                     3u


/*
*********************************************************************************************************
*                                     PERIPHERALS CLOCKS DEFINES
*
* Note(s) : (1) The peripheral's clock #define's use the following standard.
*
*                   #define  BSP_SYS_PER_CLK_NBR_<PER>_<PER_NBR>
*
*                   where,
*
*                   <PER>      Peripheral clock name.
*                   <PER_NBR>  Peripheral clock number identifier.
*
*           (2) The TI RM48 MCU support Power down mode for peripherals memories and peripherals
*               register. For this reason two subsets of clk identifiers are defines to indidually enable/disable
*               the peripheral memory or the peripheral register.
*********************************************************************************************************
*/

                                                                /* ------------- PERIPHERAL MEMORY SELECTS ------------ */
#define  BSP_SYS_PER_CLK_NBR_PCS_SPI_05           5u
#define  BSP_SYS_PER_CLK_NBR_PCS_SPI_03           6u
#define  BSP_SYS_PER_CLK_NBR_PCS_SPI_01           7u
#define  BSP_SYS_PER_CLK_NBR_PCS_CAN_03          13u
#define  BSP_SYS_PER_CLK_NBR_PCS_CAN_02          14u
#define  BSP_SYS_PER_CLK_NBR_PCS_CAN_01          15u
#define  BSP_SYS_PER_CLK_NBR_PCS_ADC_02          29u
#define  BSP_SYS_PER_CLK_NBR_PCS_ADC_01          31u
#define  BSP_SYS_PER_CLK_NBR_PCS_HET_02          34u
#define  BSP_SYS_PER_CLK_NBR_PCS_HET_01          35u
#define  BSP_SYS_PER_CLK_NBR_PCS_HETTU_02        38u
#define  BSP_SYS_PER_CLK_NBR_PCS_HETTU_01        39u

                                                                /* ------------- PERIPHERAL REGISTER SELECTS --------- */
#define  BSP_SYS_PER_CLK_NBR_PS_OFFSET           64u
#define  BSP_SYS_PER_CLK_NBR_PS_MibSPI_05       ( 0u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_SPI_04          ( 1u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_MibSPI_03       ( 1u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_SPI_02          ( 2u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_MibSPI_01       ( 2u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_SCI_00          ( 6u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_LIN_00          ( 6u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_CAN_03          ( 7u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_CAN_02          ( 8u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_CAN_01          ( 8u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_I2C_00          (10u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_ADC_02          (15u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_ADC_01          (15u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_GPIO_00         (16u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_HET_02          (17u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_HET_01          (17u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_HETTU_02        (22u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)
#define  BSP_SYS_PER_CLK_NBR_PS_HETTU_01        (22u + BSP_SYS_PER_CLK_NBR_PS_OFFSET)


/*
*********************************************************************************************************
*                                        SYSTEM CLOCKS DEFINES
*
* Note(s) : (1) The RM48x implements the following clock_domains
*
*                   GCLK      : CPU clock domain.
*                   HCLK      : System bus clock domain.
*                   VCLK      : System peripheral clock domain.
*                   VCLK_PER  : Primary clock for peripherals.
*                   VCLK_02   : VCLK_02 is a second VBUS clock domain used by the NHET
*                               and HET TU peripherals.
*                   VCLK_03   : VCLK_03 is a third VBUS clock domain used by the EMIF
*                               and Ethernet.
*                   AVCLK_01  : Asynchronous clock domain 1.
*                   AVCLK_02  : Asynchronous clock domain 1.
*                   VCLK_SYS  : Primary clock for the VBUS clock domain.
*********************************************************************************************************
*/

#define  BSP_SYS_CLK_NBR_GCLK_00                 0u
#define  BSP_SYS_CLK_NBR_HCLK_00                 1u
#define  BSP_SYS_CLK_NBR_VCLK_PER_00             2u
#define  BSP_SYS_CLK_NBR_VCLK_02                 3u
#define  BSP_SYS_CLK_NBR_VCLK_03                 4u
#define  BSP_SYS_CLK_NBR_AVCLK_01                5u
#define  BSP_SYS_CLK_NBR_AVCLK_02                6u
#define  BSP_SYS_CLK_NBR_RTI_CLK_01              7u
#define  BSP_SYS_CLK_NBR_RTI_CLK_02              8u
#define  BSP_SYS_CLK_NBR_VCLK_SYS_00             9u
#define  BSP_SYS_CLK_NBR_MAX                    10u


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void        BSP_SysInit           (void);
CPU_INT32U  BSP_Sys_CPU_ClkFreqGet(void);
CPU_INT32U  BSP_SysClkFreqGet     (CPU_INT16U  clk_nbr);
CPU_INT32U  BSP_SysPerClkFreqGet  (CPU_INT16U  clk_nbr);
void        BSP_SysPerClkEn       (CPU_INT16U  clk_nbr);
void        BSP_SysPerClkDis      (CPU_INT16U  clk_nbr);


/*
*********************************************************************************************************
*                                              MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */
