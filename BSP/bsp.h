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
*
*                                          Texas Instruments
*                                 RM48x Hercules Development Kit(HDK)
*
*
* Filename      : bsp.h
* Version       : V1.00
* Programmer(s) : FF
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_PRESENT
#define  BSP_PRESENT


/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <cpu_core.h>

#include  <lib_def.h>
#include  <lib_ascii.h>


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/


#ifdef   BSP_MODULE
#define  BSP_EXT
#else
#define  BSP_EXT  extern
#endif


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/

                                                                /* ----------- N2HET CONTROL REGISTERS --------- */
#define  BSP_GPIO_HET_ADDR_REG_BASE                (CPU_INT32U )(0xFFF7B800)
#define  BSP_GPIO_REG_HETDIR                    (* (CPU_REG32 *)(BSP_GPIO_HET_ADDR_REG_BASE + 0x4C))
#define  BSP_GPIO_REG_HETDOUT                   (* (CPU_REG32 *)(BSP_GPIO_HET_ADDR_REG_BASE + 0x54))
#define  BSP_GPIO_REG_HETDSET                   (* (CPU_REG32 *)(BSP_GPIO_HET_ADDR_REG_BASE + 0x58))
#define  BSP_GPIO_REG_HETDCLR                   (* (CPU_REG32 *)(BSP_GPIO_HET_ADDR_REG_BASE + 0x5C))

                                                                /* --------------- IOMM REGISTER DEFINES -------------- */
#define  BSP_IOMM_REG_BASE_ADDR                    (CPU_INT32U )(0xFFFFEA00u)
#define  BSP_IOMM_REG_KICK0                (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x0038u))
#define  BSP_IOMM_REG_KICK1                (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x003Cu))
#define  BSP_IOMM_REG_PINMMR00             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x0110u))
#define  BSP_IOMM_REG_PINMMR01             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x0114u))
#define  BSP_IOMM_REG_PINMMR02             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x0118u))
#define  BSP_IOMM_REG_PINMMR03             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x011Cu))
#define  BSP_IOMM_REG_PINMMR04             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x0120u))
#define  BSP_IOMM_REG_PINMMR06             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x0128u))
#define  BSP_IOMM_REG_PINMMR07             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x012Cu))
#define  BSP_IOMM_REG_PINMMR08             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x0130u))
#define  BSP_IOMM_REG_PINMMR10             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x0138u))
#define  BSP_IOMM_REG_PINMMR11             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x013Cu))
#define  BSP_IOMM_REG_PINMMR12             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x0140u))
#define  BSP_IOMM_REG_PINMMR13             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x0144u))
#define  BSP_IOMM_REG_PINMMR14             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x0148u))
#define  BSP_IOMM_REG_PINMMR17             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x0154u))
#define  BSP_IOMM_REG_PINMMR18             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x0158u))
#define  BSP_IOMM_REG_PINMMR19             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x015Cu))
#define  BSP_IOMM_REG_PINMMR20             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x0160u))
#define  BSP_IOMM_REG_PINMMR21             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x0164u))
#define  BSP_IOMM_REG_PINMMR29             (*(CPU_REG32 *)(BSP_IOMM_REG_BASE_ADDR + 0x0184u))


/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  BSP_Init        (void);
void  BSP_LowLevelInit(void);

void  BSP_LED_Toggle  (CPU_INT08U  led);
void  BSP_LED_On      (CPU_INT08U  led);
void  BSP_LED_Off     (CPU_INT08U  led);


/*
*********************************************************************************************************
*                                          CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */
