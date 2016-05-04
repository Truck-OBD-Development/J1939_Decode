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
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : FF
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include  <bsp.h>
#include  <bsp_int.h>
#include  <bsp_sys.h>


/*
*********************************************************************************************************
*                                             GPIO DEFINES
*********************************************************************************************************
*/

#define  BSP_GPIO_PORTA_LED_01   DEF_BIT_17
#define  BSP_GPIO_PORTA_LED_02   DEF_BIT_31
#define  BSP_GPIO_PORTA_LED_03   DEF_BIT_00
#define  BSP_GPIO_PORTA_LED_04   DEF_BIT_25
#define  BSP_GPIO_PORTA_LED_05   DEF_BIT_18
#define  BSP_GPIO_PORTA_LED_06   DEF_BIT_29

#define  BSP_GPIO_PORTA_LED_GRP (BSP_GPIO_PORTA_LED_01 | \
                                 BSP_GPIO_PORTA_LED_02 | \
                                 BSP_GPIO_PORTA_LED_03 | \
                                 BSP_GPIO_PORTA_LED_04 | \
                                 BSP_GPIO_PORTA_LED_05 | \
                                 BSP_GPIO_PORTA_LED_06)

#define  BSP_GPIO_PORTB_PB_00    DEF_BIT_07
#define  BSP_GPIO_PORTB_PB_GRP   BSP_GPIO_PORTB_PB_00



/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
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


/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
**                                         GLOBAL FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             BSP_LowLevelInit()
*
* Description : System Low Level Init (PLLs, External Memories, Boot loaders, etc).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Startup Code.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LowLevelInit (void)
{

}


/*
*********************************************************************************************************
*                                          BSP INITIALIZATION
*
* Description : Board Support package initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : main()
*
* Note(s)     : (1) This function initializes all peripherals that don't require OS services or modules
*                   that need to be initialized before the OS is initialized (e.g External memories).
*
*               (2) FMzPLL is the source for GCLK/HCLK,VCLK, VCLK2.
*********************************************************************************************************
*/

void  BSP_Init (void)
{
    BSP_SysInit();
                                                                /* ---------------- LEDs INITIALIZATION --------------- */
    DEF_BIT_SET(BSP_GPIO_REG_HETDIR, BSP_GPIO_PORTA_LED_GRP);   /* Pins set as OUTPUT                                   */
}


/*
*********************************************************************************************************
*                                                 BSP_LED_Off()
*
* Description : Turn OFF any or all the LEDs on the board.
*
* Argument(s) : led    The ID of the LED to control:
*
*                           0    turn OFF all LEDs on the board.
*                           1    turn OFF LED1 on the board.
*                           2    turn OFF LED2 on the board.
*                           3    turn OFF LED3 on the board.
*                           4    turn OFF LED4 on the board.
*                           5    turn OFF LED5 on the board.
*                           6    turn OFF LED6 on the board.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Off (CPU_INT08U  led)
{
    switch (led) {
        case 0u:
        	 BSP_GPIO_REG_HETDCLR = BSP_GPIO_PORTA_LED_GRP;
             break;

        case 1u:
             BSP_GPIO_REG_HETDCLR = BSP_GPIO_PORTA_LED_01;
             break;

        case 2u:
        	 BSP_GPIO_REG_HETDCLR = BSP_GPIO_PORTA_LED_02;
             break;

        case 3u:
        	 BSP_GPIO_REG_HETDCLR = BSP_GPIO_PORTA_LED_03;
             break;

        case 4u:
        	 BSP_GPIO_REG_HETDCLR = BSP_GPIO_PORTA_LED_04;
             break;

        case 5u:
        	 BSP_GPIO_REG_HETDCLR = BSP_GPIO_PORTA_LED_05;
             break;

        case 6u:
        	 BSP_GPIO_REG_HETDCLR = BSP_GPIO_PORTA_LED_06;
             break;

        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                                 BSP_LED_On()
*
* Description : Turn ON any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*                           0    turn ON all LEDs on the board.
*                           1    turn ON LED1 on the board.
*                           2    turn ON LED2 on the board.
*                           3    turn ON LED3 on the board.
*                           4    turn ON LED4 on the board.
*                           5    turn ON LED5 on the board.
*                           6    turn ON LED6 on the board.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_On (CPU_INT08U  led)
{
    switch (led) {
        case 0u:
        	 BSP_GPIO_REG_HETDSET = BSP_GPIO_PORTA_LED_GRP;
             break;

        case 1u:
        	 BSP_GPIO_REG_HETDSET = BSP_GPIO_PORTA_LED_01;
             break;

        case 2u:
        	 BSP_GPIO_REG_HETDSET = BSP_GPIO_PORTA_LED_02;
             break;

        case 3u:
        	 BSP_GPIO_REG_HETDSET = BSP_GPIO_PORTA_LED_03;
             break;

        case 4u:
        	 BSP_GPIO_REG_HETDSET = BSP_GPIO_PORTA_LED_04;
             break;

        case 5u:
        	 BSP_GPIO_REG_HETDSET = BSP_GPIO_PORTA_LED_05;
             break;

        case 6u:
        	 BSP_GPIO_REG_HETDSET = BSP_GPIO_PORTA_LED_06;
             break;

        default:
             break;
    }
}


/*
*********************************************************************************************************
*                                                 BSP_LED_Toggle()
*
* Description : Toggles any or all the LEDs on the board.
*
* Argument(s) : led   The ID of the LED to control:
*
*                       0    toggle all LEDs on the board
*                       1    toggle LED1
*                       2    toggle LED2
*                       3    toggle LED3
*                       4    toggle LED4
*                       5    toggle LED5
*                       6    toggle LED6
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Toggle (CPU_INT08U  led)
{
    CPU_INT32U  pins_clr;
    CPU_INT32U  pins_set;
    CPU_INT32U  port_val;


    port_val = BSP_GPIO_REG_HETDOUT;
    switch (led) {
        case 0u:
             pins_clr  = ( port_val) & BSP_GPIO_PORTA_LED_GRP;
             pins_set  = (~port_val) & BSP_GPIO_PORTA_LED_GRP;

             BSP_GPIO_REG_HETDSET = pins_set;
             BSP_GPIO_REG_HETDCLR = pins_clr;
             break;

        case 1u:
             pins_clr  = ( port_val) & BSP_GPIO_PORTA_LED_01;
             pins_set  = (~port_val) & BSP_GPIO_PORTA_LED_01;

             BSP_GPIO_REG_HETDSET = pins_set;
             BSP_GPIO_REG_HETDCLR = pins_clr;
             break;

        case 2u:
             pins_clr  = ( port_val) & BSP_GPIO_PORTA_LED_02;
             pins_set  = (~port_val) & BSP_GPIO_PORTA_LED_02;

             BSP_GPIO_REG_HETDSET = pins_set;
             BSP_GPIO_REG_HETDCLR = pins_clr;
             break;

        case 3u:
             pins_clr  = ( port_val) & BSP_GPIO_PORTA_LED_03;
             pins_set  = (~port_val) & BSP_GPIO_PORTA_LED_03;

             BSP_GPIO_REG_HETDSET = pins_set;
             BSP_GPIO_REG_HETDCLR = pins_clr;
             break;

        case 4u:
             pins_clr  = ( port_val) & BSP_GPIO_PORTA_LED_04;
             pins_set  = (~port_val) & BSP_GPIO_PORTA_LED_04;

             BSP_GPIO_REG_HETDSET = pins_set;
             BSP_GPIO_REG_HETDCLR = pins_clr;
             break;

        case 5u:
             pins_clr  = ( port_val) & BSP_GPIO_PORTA_LED_05;
             pins_set  = (~port_val) & BSP_GPIO_PORTA_LED_05;

             BSP_GPIO_REG_HETDSET = pins_set;
             BSP_GPIO_REG_HETDCLR = pins_clr;
             break;

        case 6u:
             pins_clr  = ( port_val) & BSP_GPIO_PORTA_LED_06;
             pins_set  = (~port_val) & BSP_GPIO_PORTA_LED_06;

             BSP_GPIO_REG_HETDSET = pins_set;
             BSP_GPIO_REG_HETDCLR = pins_clr;
             break;

        default:
             break;
    }
}
