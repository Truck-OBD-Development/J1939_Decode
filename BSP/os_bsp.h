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
* Filename      : os_bsp.h
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

#ifndef  OS_BSP_PRESENT
#define  OS_BSP_PRESENT


/*
*********************************************************************************************************
*                                                      PROTOTYPES
*
* Note(s): (1) 'OS_BSP_TickInit()' Initialize the tick interrupt.
*********************************************************************************************************
*/

void  OS_BSP_TickInit (CPU_INT32U  tick_rate);


/*
*********************************************************************************************************
*                                              MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */
