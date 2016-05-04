
/*
***************************************************************************
** Filename:	test_j1939_can.c
** Author:
** Date:
** Description:	function to configuration the CAN mail box
***************************************************************************
**/
#include "test_j1939_can.h"
#include "can.h"


/***************************************************************************
** Function:	    CAN_MailBoxInit 
** Input:        None 
** Outout:       None
** Description:	This function used to initial the mailbox, 
**              and called in CAN driver initial function. 
***************************************************************************/
void CAN_MailBoxInit(void)
{
    /** Init CAN1 mail box
      - Wait until state ready for use 
     - Set message mask 
     - Set message control word
     - Set message arbitration
     - Set control byte
     - Set message number
    **/
    /** Init CAN2 mail box
      - Wait until state ready for use 
     - Set message mask 
     - Set message control word
     - Set message arbitration
     - Set control byte
     - Set message number
    **/
    /**Initial Message 1***/
    while((canREG2->IF2STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)0x1CEC56F4U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 1U;

    /**Initial Message 2***/
    while((canREG2->IF1STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)0x1CEB56F4U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 2U;

    /**Initial Message 3***/
    while((canREG2->IF2STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x1CECF456U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 3U;

    /**Initial Message 4***/
    while((canREG2->IF1STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x00000456U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 4U;

    /**Initial Message 5***/
    while((canREG2->IF2STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)0x181056F4U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 5U;

    /**Initial Message 6***/
    while((canREG2->IF1STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)0x1C0656F4U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 6U;

    /**Initial Message 7***/
    while((canREG2->IF2STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)0x1C1156F4U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 7U;

    /**Initial Message 8***/
    while((canREG2->IF1STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)0x081E56F4U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 8U;

    /**Initial Message 9***/
    while((canREG2->IF2STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)0x182756F4U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 9U;

    /**Initial Message 10***/
    while((canREG2->IF1STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)0x100956F4U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 10U;

    /**Initial Message 11***/
    while((canREG2->IF2STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)0x181C56F4U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 11U;

    /**Initial Message 12***/
    while((canREG2->IF1STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)0x181356F4U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 12U;

    /**Initial Message 13***/
    while((canREG2->IF2STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)0x101956F4U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 13U;

    /**Initial Message 14***/
    while((canREG2->IF1STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x20000000U | (uint32)((uint32)((uint32)0x123U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 14U;

    /**Initial Message 15***/
    while((canREG2->IF2STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x1812F456U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 15U;

    /**Initial Message 16***/
    while((canREG2->IF1STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x081FF456U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 16U;

    /**Initial Message 17***/
    while((canREG2->IF2STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x1826F456U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 17U;

    /**Initial Message 18***/
    while((canREG2->IF1STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x1808F456U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 18U;

    /**Initial Message 19***/
    while((canREG2->IF2STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x1801F456U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 19U;

    /**Initial Message 20***/
    while((canREG2->IF1STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x100AF456U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 20U;

    /**Initial Message 21***/
    while((canREG2->IF2STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x181DF456U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 21U;

    /**Initial Message 22***/
    while((canREG2->IF1STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF1MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x101AF456U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF1MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF1CMD  = (uint8) 0xF8U;
    canREG2->IF1NO   = 22U;

    /**Initial Message 23***/
    while((canREG2->IF2STAT & 0x80U) ==0x80U)
    {
    }

    canREG2->IF2MSK  = 0xC0000000U | (uint32)((uint32)((uint32)0xFFFFFFFFU & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2ARB  = (uint32)0x80000000U | (uint32)0x40000000U | (uint32)0x00000000U | (uint32)((uint32)((uint32)0x1807F456U & (uint32)0x1FFFFFFFU) << (uint32)0U);
    canREG2->IF2MCTL = 0x00001080U | (uint32)0x00000000U | (uint32)0x00000000U | (uint32)8U;
    canREG2->IF2CMD  = (uint8) 0xF8U;
    canREG2->IF2NO   = 23U;


	while ((canREG2->IF1STAT & 0x80U) ==0x80U)
	{
	}
	canREG2->IF1CMD  = 0x87U;
	while ((canREG2->IF2STAT & 0x80U) ==0x80U)
	{
	}
	canREG2->IF2CMD = 0x17U;
    /** Init CAN3 mail box
      - Wait until state ready for use 
     - Set message mask 
     - Set message control word
     - Set message arbitration
     - Set control byte
     - Set message number
    **/
}
