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
* Filename      : bsp_int.h
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

#ifndef  BSP_INT_PRESENT
#define  BSP_INT_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                          INTERRUPT SOURCES
*********************************************************************************************************
*/

#define  BSP_INT_ID_ESM_00_HIGH               0u                /* Error Signal Module High Level interrupt.            */
#define  BSP_INT_ID_RSVD_00                   1u                /* Non-Maskable Interrupt(NMI).                         */
#define  BSP_INT_ID_RTI_XX_CMP_00             2u                /* RTI compare  interrupt 0.                            */
#define  BSP_INT_ID_RTI_XX_CMP_01             3u                /* RTI compare  interrupt 1.                            */
#define  BSP_INT_ID_RTI_XX_CMP_02             4u                /* RTI compare  interrupt 2.                            */
#define  BSP_INT_ID_RTI_XX_CMP_03             5u                /* RTI compare  interrupt 3.                            */
#define  BSP_INT_ID_RTI_XX_OVF_00             6u                /* RTI overflow interrupt 0.                            */
#define  BSP_INT_ID_RTI_XX_OVF_01             7u                /* RTI overflow interrupt 1.                            */
#define  BSP_INT_ID_RTI_XX_TIMEBASE           8u                /* RTI timebase.                                        */
#define  BSP_INT_ID_GPIO_00_INTA              9u                /* GPIO interrupt A.                                    */
#define  BSP_INT_ID_HET_01_LVL_00            10u                /* NHET1 level 0 interrupt.                             */
#define  BSP_INT_ID_HET_00_TULVL_00          11u                /* HET Transfer Unit level 0 interrupt.                 */
#define  BSP_INT_ID_SPI_01_LVL_00            12u                /* MIBSPI 1 level 0 interrupt.                          */
#define  BSP_INT_ID_LIN_01_LVL_00            13u                /* LIN 1 level 0 interrupt.                             */
#define  BSP_INT_ID_ADC_01_EVENT_GRP         14u                /* MIBADC 1 event group interrupt.                      */
#define  BSP_INT_ID_ADC_01_SW_GRP_01         15u                /* MIBADC 1 SW group 1 interrupt.                       */
#define  BSP_INT_ID_CAN_01_LVL_00            16u                /* DCAN 1 level 0 interrupt.                            */
#define  BSP_INT_ID_SPI_02_LVL_00            17u                /* MIBSPI 2 level 0 interrupt.                          */
#define  BSP_INT_ID_RSVD_01                  18u                /* Reserved.                                            */
#define  BSP_INT_ID_CRC_00                   19u                /* Cyclic Redundancy Check interrupt                    */
#define  BSP_INT_ID_ESM_LOW                  20u                /* Error Signal Module  low-level interrupt.            */
#define  BSP_INT_ID_SYSTEM_00                21u                /* System Software interrupt.                           */
#define  BSP_INT_ID_PMU_00                   22u                /* PMU interrupt.                                       */
#define  BSP_INT_ID_GPIO_00_INTB             23u                /* GPIO interrupt B.                                    */
#define  BSP_INT_ID_HET_00_LVL_01            24u                /* NHET level 1 interrupt.                              */
#define  BSP_INT_ID_HETTU_00_LVL_01          25u                /* HET Transfer Unit level 1 interrupt.                 */
#define  BSP_INT_ID_SPI_01_LVL_01            26u                /* MIBSPI 1 level 1 interrupt.                          */
#define  BSP_INT_ID_LIN_01_LVL_01            27u                /* LIN 1 level 1 interrupt.                             */
#define  BSP_INT_ID_ADC_01_SW_GRP_02         28u                /* MIBADC 1 SW group 2 interrupt.                       */
#define  BSP_INT_ID_CAN_01_LVL_01            29u                /* DCAN 1 level 1 interrupt.                            */
#define  BSP_INT_ID_SPI_02_LVL_01            30u                /* MIBSPI 2 level 1 interrupt.                          */
#define  BSP_INT_ID_ADC_01_MAG               31u                /* MIBADC 1 magnitude interrupt.                        */
#define  BSP_INT_ID_RSVD_02                  32u                /* Non-Maskable Interrupt(NMI).                         */
#define  BSP_INT_ID_DMA_FRAME_XFER_COMP      33u                /* DMA Frame Transfer Complete interrupt group A.       */
#define  BSP_INT_ID_DMA_FRAME_LAST_START     34u                /* DMA Last Frame Started interrupt to group A.         */
#define  BSP_INT_ID_CAN_02_LVL_00            35u                /* DCAN 2 level 0 interrupt.                            */
#define  BSP_INT_ID_DMM_00_LVL_00            36u                /* Data Modification Module level 0 interrupt.          */
#define  BSP_INT_ID_SPI_03_LVL_00            37u                /* MIBSPI 3 level 0 interrupt.                          */
#define  BSP_INT_ID_SPI_03_LVL_01            38u                /* MIBSPI 3 level 1 interrupt.                          */
#define  BSP_INT_ID_DMA_00_BLK_HALF_COMP     39u                /* DMA Half Block Complete interrupt to group A.        */
#define  BSP_INT_ID_DMA_00_BLK_XFER_COMP     40u                /* DMA Block Transfer complete interrupt to group B.    */
#define  BSP_INT_ID_EMIF_00_AEMIFINT3        41u                /* AEMIF interrupt level 3.                             */
#define  BSP_INT_ID_CAN_02_LVL_01            42u                /* DCAN 2 level 1 interrupt.                            */
#define  BSP_INT_ID_DMM_00_LVL_01            43u                /* Data Modification module level 1 interrupt.          */
#define  BSP_INT_ID_CAN_01_IF_03             44u                /* DCAN 1 interface 3 interrupt.                        */
#define  BSP_INT_ID_CAN_03_LVL_00            45u                /* DCAN 3 level 0 interrupt.                            */
#define  BSP_INT_ID_CAN_02_IF_03             46u                /* DCAN 2 interface 3 interrupt.                        */
#define  BSP_INT_ID_FPU_00                   47u                /* Floating Point unit interrupt.                       */
#define  BSP_INT_ID_RSVD_03                  48u                /* Non-Maskable Interrupt(NMI).                         */
#define  BSP_INT_ID_SPI_04_LVL_00            49u                /* MIBSPI 4 level 0 interrupt.                          */
#define  BSP_INT_ID_ADC_02_EVENT_GRP         50u                /* MIBADC 2 event group interrupt.                      */
#define  BSP_INT_ID_ADC_02_SW_GRP_01         51u                /* MIBADC 2 software group 1 interrupt.                 */
#define  BSP_INT_ID_RSVD_04                  52u                /* Non-Maskable Interrupt(NMI).                         */
#define  BSP_INT_ID_SPI_05_LVL_00            53u                /* MIBSPI 5 level 0 interrupt.                          */
#define  BSP_INT_ID_SPI_04_LVL_01            54u                /* MIBSPI 4 level 1 interrupt.                          */
#define  BSP_INT_ID_CAN_03_LVL_01            55u                /* DCAN 3 level 1 interrupt.                            */
#define  BSP_INT_ID_SPI_05_LVL_01            56u                /* MIBSPI 5 level 1 interrupt.                          */
#define  BSP_INT_ID_ADC_02_SW_GRP_02         57u                /* MIBADC 2 Software group 2 interrupt.                 */
#define  BSP_INT_ID_RSVD_05                  58u                /* Non-Maskable Interrupt(NMI).                         */
#define  BSP_INT_ID_ADC_02_MAG               59u                /* MIBADC 2 magnitude interrupt.                        */
#define  BSP_INT_ID_CAN_03_IF_03             60u                /* DCAN 3 interface 3 interrupt.                        */
#define  BSP_INT_ID_FMC_00                   61u                /* FSM_DONE interrupt.                                  */
#define  BSP_INT_ID_RSVD_06                  62u                /* Non-Maskable Interrupt(NMI).                         */
#define  BSP_INT_ID_HET_02_LVL_00            63u                /* NHET level 0 interrupt.                              */
#define  BSP_INT_ID_SCI_00_LVL_00            64u                /* SCI level 0 interrupt.                               */
#define  BSP_INT_ID_HET_00_TULVL_02          65u                /* HET Transfer Unit level 2 interrupt.                 */
#define  BSP_INT_ID_I2C_00_LVL_00            66u                /* I2C level 0 interrupt.                               */
#define  BSP_INT_ID_USBH_OHCI                67u                /* USB Host OHCI interrupt.                             */
#define  BSP_INT_ID_USBD_IRQISOON            68u                /* USB Device ISOON IRQ                                 */
#define  BSP_INT_ID_USBD_IRQGENION           69u                /* USB Device GENION IRQ                                */
#define  BSP_INT_ID_USBD_IRQNONISOON         70u                /* USB Device NONISOON IRQ                              */
#define  BSP_INT_ID_USBD_DSWAKEREQON         71u                /* USB Device DSWAKEREQON                               */
#define  BSP_INT_ID_USBD_USBRESETO           72u                /* USB Device USBRESETO                                 */
#define  BSP_INT_ID_HET_02_LVL_01            73u                /* NHET2 level 1 interrupt.                             */
#define  BSP_INT_ID_SCI_00_LVL_01            74u                /* SCI level 1 interrupt.                               */
#define  BSP_INT_ID_HETTU_02_LVL_01          75u                /* HET Transfer Unit level 1 interrupt.                 */
#define  BSP_INT_ID_ETHER_C0MISCPULSE        76u                /* Ethernet C0 Miscelaneous pulse.                      */
#define  BSP_INT_ID_ETHER_C0TXPULSE          77u                /* Ethernet C0 TX pulse.                                */
#define  BSP_INT_ID_ETHER_C0THRESHPULSE      78u                /* Ethernet C0 threshold pulse.                         */
#define  BSP_INT_ID_ETHER_C0RXPULSE          79u                /* Ethernet C0 RX pulse.                                */
#define  BSP_INT_ID_HWAG1                    80u                /* HWA1 interrupt.                                      */
#define  BSP_INT_ID_HWAG2                    81u                /* HWA2 interrupt.                                      */
#define  BSP_INT_ID_DCC1                     82u                /* DCC done interrupt.                                  */
#define  BSP_INT_ID_DCC2                     83u                /* DCC2 done interrupt.                                 */
#define  BSP_INT_ID_RSVD_07                  84u                /* Non-Maskable Interrupt(NMI).                         */
#define  BSP_INT_ID_RSVD_08                  85u                /* Non-Maskable Interrupt(NMI).                         */
#define  BSP_INT_ID_RSVD_09                  86u                /* Non-Maskable Interrupt(NMI).                         */
#define  BSP_INT_ID_RSVD_10                  87u                /* Non-Maskable Interrupt(NMI).                         */
#define  BSP_INT_ID_HWAG1_INT                88u                /* HWA1 interrupt.                                      */
#define  BSP_INT_ID_HWAG2_INT                89u                /* HWA2 interrupt.                                      */
#define  BSP_INT_ID_RSVD_11                  90u                /* Non-Maskable Interrupt(NMI).                         */
#define  BSP_INT_ID_RSVD_12                  91u                /* Non-Maskable Interrupt(NMI).                         */
#define  BSP_INT_ID_RSVD_13                  92u                /* Non-Maskable Interrupt(NMI).                         */
#define  BSP_INT_ID_RSVD_14                  93u                /* Non-Maskable Interrupt(NMI).                         */
#define  BSP_INT_ID_RSVD_15                  94u                /* Non-Maskable Interrupt(NMI).                         */
#define  BSP_INT_ID_RSVD_16                  95u                /* Non-Maskable Interrupt(NMI).                         */

#define  BSP_INT_ID_MAX                      96u                /* # interrupts sources.                                */


/*
*********************************************************************************************************
*                                          INTERRUPT CHANNELS
*********************************************************************************************************
*/

#define  BSP_INT_CH_00                        0u
#define  BSP_INT_CH_01                        1u
#define  BSP_INT_CH_02                        2u
#define  BSP_INT_CH_03                        3u
#define  BSP_INT_CH_04                        4u
#define  BSP_INT_CH_05                        5u
#define  BSP_INT_CH_06                        6u
#define  BSP_INT_CH_07                        7u
#define  BSP_INT_CH_08                        8u
#define  BSP_INT_CH_09                        9u
#define  BSP_INT_CH_10                       10u
#define  BSP_INT_CH_11                       11u
#define  BSP_INT_CH_12                       12u
#define  BSP_INT_CH_13                       13u
#define  BSP_INT_CH_14                       14u
#define  BSP_INT_CH_15                       15u
#define  BSP_INT_CH_16                       16u
#define  BSP_INT_CH_17                       17u
#define  BSP_INT_CH_18                       18u
#define  BSP_INT_CH_19                       19u
#define  BSP_INT_CH_20                       20u
#define  BSP_INT_CH_21                       21u
#define  BSP_INT_CH_22                       22u
#define  BSP_INT_CH_23                       23u
#define  BSP_INT_CH_24                       24u
#define  BSP_INT_CH_25                       25u
#define  BSP_INT_CH_26                       26u
#define  BSP_INT_CH_27                       27u
#define  BSP_INT_CH_28                       28u
#define  BSP_INT_CH_29                       29u
#define  BSP_INT_CH_30                       30u
#define  BSP_INT_CH_31                       31u
#define  BSP_INT_CH_32                       32u
#define  BSP_INT_CH_33                       33u
#define  BSP_INT_CH_34                       34u
#define  BSP_INT_CH_35                       35u
#define  BSP_INT_CH_36                       36u
#define  BSP_INT_CH_37                       37u
#define  BSP_INT_CH_38                       38u
#define  BSP_INT_CH_39                       39u
#define  BSP_INT_CH_40                       40u
#define  BSP_INT_CH_41                       41u
#define  BSP_INT_CH_42                       42u
#define  BSP_INT_CH_43                       43u
#define  BSP_INT_CH_44                       44u
#define  BSP_INT_CH_45                       45u
#define  BSP_INT_CH_46                       46u
#define  BSP_INT_CH_47                       47u
#define  BSP_INT_CH_48                       48u
#define  BSP_INT_CH_49                       49u
#define  BSP_INT_CH_50                       50u
#define  BSP_INT_CH_51                       51u
#define  BSP_INT_CH_52                       52u
#define  BSP_INT_CH_53                       53u
#define  BSP_INT_CH_54                       54u
#define  BSP_INT_CH_55                       55u
#define  BSP_INT_CH_56                       56u
#define  BSP_INT_CH_57                       57u
#define  BSP_INT_CH_58                       58u
#define  BSP_INT_CH_59                       59u
#define  BSP_INT_CH_60                       60u
#define  BSP_INT_CH_61                       61u
#define  BSP_INT_CH_62                       62u
#define  BSP_INT_CH_63                       63u
#define  BSP_INT_CH_64                       64u
#define  BSP_INT_CH_65                       65u
#define  BSP_INT_CH_66                       66u
#define  BSP_INT_CH_67                       67u
#define  BSP_INT_CH_68                       68u
#define  BSP_INT_CH_69                       69u
#define  BSP_INT_CH_70                       70u
#define  BSP_INT_CH_71                       71u
#define  BSP_INT_CH_72                       72u
#define  BSP_INT_CH_73                       73u
#define  BSP_INT_CH_74                       74u
#define  BSP_INT_CH_75                       75u
#define  BSP_INT_CH_76                       76u
#define  BSP_INT_CH_77                       77u
#define  BSP_INT_CH_78                       78u
#define  BSP_INT_CH_79                       79u
#define  BSP_INT_CH_80                       80u
#define  BSP_INT_CH_81                       81u
#define  BSP_INT_CH_82                       82u
#define  BSP_INT_CH_83                       83u
#define  BSP_INT_CH_84                       84u
#define  BSP_INT_CH_85                       85u
#define  BSP_INT_CH_86                       86u
#define  BSP_INT_CH_87                       87u
#define  BSP_INT_CH_88                       88u
#define  BSP_INT_CH_89                       89u
#define  BSP_INT_CH_90                       90u
#define  BSP_INT_CH_91                       91u
#define  BSP_INT_CH_92                       92u
#define  BSP_INT_CH_93                       93u
#define  BSP_INT_CH_94                       94u
#define  BSP_INT_CH_95                       95u

#define  BSP_INT_CH_MAX                      96u


/*
*********************************************************************************************************
*                                           INTERRUPT TYPES
*********************************************************************************************************
*/

#define  BSP_INT_SRC_TYPE_IRQ                 0u
#define  BSP_INT_SRC_TYPE_FIQ                 1u


/*
*********************************************************************************************************
*                                              PROTOTYPES
*********************************************************************************************************
*/

void         BSP_IntInit      (void);                           /* Initialize interrupt controller.                     */

void         BSP_IntEn        (CPU_INT08U     src_ch);          /* Enable a interrupt channel.                          */

void         BSP_IntDis       (CPU_INT08U     src_ch);          /* Disable a interrupt channel.                         */

void         BSP_IntDisAll    (void);                           /* Disable all interrupt channel.                       */

CPU_BOOLEAN  BSP_IntVectSet   (CPU_INT08U     src_nbr,          /* Set interrupt request into a interrupt channel.      */
                               CPU_INT08U     src_ch,
                               CPU_INT08U     src_type,
                               CPU_FNCT_VOID  isr_fnct);

CPU_BOOLEAN  BSP_IntVectClr   (CPU_INT08U     src_ch);          /* Unintall interrupt handler of an interrupt channel.  */

void         BSP_IntHandlerSrc(CPU_INT16U     src_id);          /* Global interrupt handler.                            */


/*
*********************************************************************************************************
*                                              MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */
