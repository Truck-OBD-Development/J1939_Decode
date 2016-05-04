
/*
***************************************************************************
** Filename:	test_j1939_tp.c
** Author:
** Date:
** Description:	J1939 transmit protocol
***************************************************************************
**/
#include "Datatype.h"
#include "test_j1939_tp.h"
#include "can.h"



/*************************************************************************/
/* Defines                                                               */
/*************************************************************************/




/*************************************************************************/
/* static variables                                                      */
/*************************************************************************/
static J1939_TRANSPORT_TX_INFO tx_msg;




/*************************************************************************/
/* local function                                                        */
/*************************************************************************/
static enum_cm_timeout_type J1939_RefreshCMTimer(uint16_t dt_ms);
static void J1939_CM_Start(void);
static void J1939_next_DT_Packet(void);
static void J1939_CAN_TP_Rx(void);
static void J1939_SendAbort(void);

/*************************************************************************/
/* functions                                                             */
/*************************************************************************/


/*************************************************************************
** Function: J1393_Init
** Parameter(In):  None
** Parameter(Out):
** Description:
**************************************************************************/
void J1393_Init(void)
{
    tx_msg.state = ENUM_J1939_TX_WAIT;
    tx_msg.time = 0;
    tx_msg.retry = 0;
    tx_msg.total_packets = 0;
    tx_msg.packet_index = 0;
    tx_msg.packets_ok_to_send = 0;
}


/*************************************************************************
** Function: J1393_Init
** Parameter(In):  None
** Parameter(Out):
** Description:
**************************************************************************/
static enum_cm_timeout_type J1939_RefreshCMTimer(uint16_t dt_ms)
{
	enum_cm_timeout_type result;
	if((ENUM_J1939_TX_CM_WAIT == tx_msg.state)||(ENUM_J1939_WAIT_ACK == tx_msg.state))
	{
		if(tx_msg.time > dt_ms)
		{
			/* timer OK */
			tx_msg.time = tx_msg.time - dt_ms;
			result = ENUM_CM_TIMEOUT_NORMAL;
		}
		else
		{
			/* CM timeout */
			tx_msg.time = 0u;
			result = ENUM_CM_TIMEOUT_ABNORMAL;
		}

	}
	else
	{
		result = ENUM_CM_TIMEOUT_NORMAL;
	}
	return result;
}

/*************************************************************************
** Function: J1939_CM_Start
** Parameter(In):  None
** Parameter(Out):
** Description:
**************************************************************************/
static void J1939_CM_Start(void)
{
	uint8_t buf[J1939_MAX_DATA_SIZE];
	uint32_t pgn_num;
	J1939_TX_MESSAGE_T msg= tx_msg.tx_msg_ptr;

    pgn_num = msg.PGN;
	/* initial RTS data */
    buf[0] = ENUM_TP_TYPE_RTS;
    buf[1] = (uint8_t) msg.byte_count ;
    buf[2] = (uint8_t) ((msg.byte_count)>>8);
    buf[3] = tx_msg.total_packets;
    buf[4] = RESERVED_BYTE;
    buf[7] = (uint8_t)((pgn_num>>16) & 0xff);  /* MSB */
    buf[6] = (uint8_t)(pgn_num>>8 & 0xff);
    buf[5] = (uint8_t)(pgn_num & 0xff);   /* LSB */

    canTransmit(canREG2,MAILBOX_CM_BCM_TO_CHG,buf);

	/* reset the connection timer and wait CTS message */
	tx_msg.time = TP_CM_TIMER;
	tx_msg.state = ENUM_J1939_TX_CM_WAIT;

}

/*************************************************************************
** Function: J1939_next_DT_Packet
** Parameter(In):  None
** Parameter(Out):
** Description:
**************************************************************************/
static void J1939_next_DT_Packet(void)
{
	uint16_t data_index;
    uint8_t buf[J1939_MAX_DATA_SIZE];
    int8_t i;
    if(tx_msg.packets_ok_to_send > 0)
    {
        tx_msg.packets_ok_to_send--;
        data_index = (uint16_t)(tx_msg.packet_index*7u);

        buf[0] = (uint8_t)(1u + tx_msg.packet_index);

        /* copy the data to buffer */
        for(i  = 0; i<7; i++)
        {
             buf[i+1] = tx_msg.tx_msg_ptr.data[data_index + i];
        }

        if(tx_msg.packet_index == (tx_msg.total_packets - 1u))
        {  /* last packet of the message */

            if ( data_index > tx_msg.tx_msg_ptr.byte_count - 7 )
            {   /* the last packet */
                i = tx_msg.tx_msg_ptr.byte_count - data_index - 7 ;

                for (    ; i < 0  ; i++ )
                {/* fill the reset byte with reserved */
                    buf[i+J1939_MAX_DATA_SIZE] = RESERVED_BYTE ;
                }
            }
            else
            {
                /* no need to fill blank */
            }
    		/* go to transmit end  */

			tx_msg.packets_ok_to_send = 0;
			tx_msg.packet_index = 0;
			tx_msg.time = TP_CM_TIMER;
			tx_msg.state = ENUM_J1939_WAIT_ACK; /* wait the next CTS or ACK message s*/
        }
        else
        {
            /* still have messages to be sent */
    		tx_msg.packet_index++;
    		tx_msg.state = ENUM_J1939_TX_DT;
        }
    	/* send out the packet */
        canTransmit(canREG2,MAILBOX_DT_BCM_TO_CHG,buf);
    }
    else
    {
        /* no message need to send */
        /* go to wait an other CTS or ACK message after this packet sent */
        tx_msg.packets_ok_to_send = 0;
        tx_msg.packet_index = 0;
        tx_msg.time = TP_CM_TIMER;
        tx_msg.state = ENUM_J1939_WAIT_ACK; /* wait the next CTS or ACK message s*/
    }

}

/*************************************************************************
** Function: J1939_SendAbort
** Parameter(In):  None
** Parameter(Out):
** Description:
**************************************************************************/

static void J1939_SendAbort(void)
{
	uint8_t buf[J1939_MAX_DATA_SIZE];
	uint32_t pgn_num;
	J1939_TX_MESSAGE_T msg= tx_msg.tx_msg_ptr;

    pgn_num = msg.PGN;
	/* initial RTS data */
    buf[0] = ENUM_TP_TYPE_ABORT;
    buf[1] = RESERVED_BYTE;
    buf[2] = RESERVED_BYTE;
    buf[3] = RESERVED_BYTE;
    buf[4] = RESERVED_BYTE;
    buf[7] = (uint8_t)((pgn_num>>16) & 0xff);  /* MSB */
    buf[6] = (uint8_t)(pgn_num>>8 & 0xff);
    buf[5] = (uint8_t)(pgn_num & 0xff);   /* LSB */

    canTransmit(canREG2,MAILBOX_CM_BCM_TO_CHG,buf);
	/* go to transmit end */
	tx_msg.state = ENUM_J1939_TX_DONE;

}
/*************************************************************************
** Function: CPDE_J1939_Init
** Parameter(In):  None
** Parameter(Out):
** Description:initialize J1939 stack
**************************************************************************/
void J1939_Main(uint16_t dt_ms)
{
	/* read J1939 TP CAN message */
	J1939_CAN_TP_Rx();

	/* J1939 tp state machine */
	switch (tx_msg.state)
	{
		case ENUM_J1939_TX_WAIT:
    		/* buffer is NULL, do nothing */
    		break;
		case ENUM_J1939_TX_CM_START:
    		/* send out TP_CM message for mutil frame transmit */
    		J1939_CM_Start();
    		break;
		case ENUM_J1939_TX_CM_WAIT:
    		/* wait feedback to transmit TP_DT messages */
    		if(ENUM_CM_TIMEOUT_ABNORMAL == J1939_RefreshCMTimer(1))
    		{
    			/* connection timeout */
    			tx_msg.state = ENUM_J1939_TX_ERROR;
    		}
    		else
    		{
    			/* keep waiting */
    		}

		break;
		case ENUM_J1939_TX_DT:
    		/* transimit TP_DT message*/
			J1939_next_DT_Packet();
    		break;
        case ENUM_J1939_WAIT_ACK:
            if(ENUM_CM_TIMEOUT_ABNORMAL == J1939_RefreshCMTimer(1))
            {
                /* connection timeout */
                tx_msg.state = ENUM_J1939_TX_ERROR;
            }
            else
            {
                /* keep waiting the end of ack message */
            }
            break;
		case ENUM_J1939_TX_ERROR:
    		/* error */
			J1939_SendAbort();
    		break;
		case ENUM_J1939_TX_DONE:
			tx_msg.packets_ok_to_send = 0;
			tx_msg.packet_index = 0;
			tx_msg.time = TP_CM_TIMER;
    		tx_msg.state = ENUM_J1939_TX_WAIT;
    		break;
        default:
            break;
	}
}



/*************************************************************************
** Function: CPDE_J1939_Init
** Parameter(In):  None
** Parameter(Out):
** Description:initialize J1939 stack
**************************************************************************/
void J1939_CAN_Tx(J1939_TX_MESSAGE_T msg)
{
	uint16_t len;
	if(msg.byte_count <= J1939_MAX_DATA_SIZE)
	{
		/* create signal frame ID */
		/* do nothing */
		/* use LLD CAN driver directly */
	}
	else if(msg.byte_count <= J1939_MAX_MESSAGE_LENGTH)
	{
		/* check whether transmit buffer can be used */
		if(tx_msg.state == ENUM_J1939_TX_WAIT)
		{
            /* buffer is OK */
			/* prepare to send messages */
            /* copy the can message need to transimit to the buffer*/

            tx_msg.tx_msg_ptr = msg;
            tx_msg.state = ENUM_J1939_TX_CM_START;
            tx_msg.retry = 0;
            tx_msg.packets_ok_to_send = 0;
            tx_msg.packet_index = 0;
            tx_msg.time = TP_CM_TIMER;

			/* calculate toltal packet */
            len = msg.byte_count;
            tx_msg.total_packets = 0;
            while(len >= 7)
            {
                tx_msg.total_packets++;
                len -= 7;
            }
            tx_msg.total_packets++;    /* add the last packet */

		}
		else
		{
			/* buffer cann't be used, wait next period */
		}
	}
	else
	{

	}
}


/*************************************************************************
** Function: CPDE_J1939_CAN_Rx
** Parameter(In):  None
** Parameter(Out):
** Description:initialize J1939 stack
**************************************************************************/
static void J1939_CAN_TP_Rx(void)
{
	uint8_t buf[J1939_MAX_DATA_SIZE];
	uint8_t j1939_TpControlType;
	uint32_t pgn_receive;
	if(TRUE == canGetData(canREG2,MAILBOX_CM_CHG_TO_BCM,buf))
	{

		/* transport protocol connection management message received */

		j1939_TpControlType = buf[0];    /* control type: RTS, CTS, ENDOFACK,...*/
		/* check pdu number received */
		pgn_receive = (uint32_t)((buf[7]<<16)&0xFF0000)+(uint32_t)((buf[6]<<8)&0xFF00)+(uint32_t)((buf[5])&0xFF);
        if(pgn_receive == tx_msg.tx_msg_ptr.PGN)
            {   /* check pgn */
    		    switch(j1939_TpControlType)
        		{
        			case ENUM_TP_TYPE_RTS:
            			/* connection request, no need to process in fast charge project */
            			/* do nothing */
            			break;
        			case ENUM_TP_TYPE_CTS:
            			/* connection response */
            			if((ENUM_J1939_TX_CM_WAIT == tx_msg.state) || (ENUM_J1939_WAIT_ACK == tx_msg.state))
            			{
            				/* transimit stay in waiting step */
            				if(0x00u == buf[1])
            				{
            					/* refersh connection timer */
            					tx_msg.time = TP_CM_KEEP_TIMER;
            				}
            				else
            				{
                                if(0)//buf[2]+buf[1] > (tx_msg.total_packets+1))
                                { /* outof range */
                                    tx_msg.retry ++;
                                    if(tx_msg.retry >= MAX_NUM_ERRORS)
                                    {  /* wait for the other CTS message for MAX_NUM_ERRORS */
                                        tx_msg.state = ENUM_J1939_TX_ERROR;
                                    }
            						else
                                    {
                                        /* wait another CTS message */
                                    }
                                }
                                else
                                { /* response parameter OK */
                                    tx_msg.packets_ok_to_send = buf[1];
                                    tx_msg.packet_index  = (uint8_t)(buf[2] - 1);
                                    tx_msg.state = ENUM_J1939_TX_DT;
                                }

            				}
            			}
            			else
            			{
            				/* do nothing */
            			}
            			break;
        			case ENUM_TP_TYPE_ENDOFACK:
            			if(ENUM_J1939_WAIT_ACK == tx_msg.state)
            			{
            				tx_msg.state = ENUM_J1939_TX_DONE;
            			}
            			else
            			{
            				/* do nothing */
            			}
            			break;
        			case ENUM_TP_TYPE_ABORT:
            			break;
        			default:
            			break;
        		}
        }
        else
        {
            /* do nothing */
        }

	}
	else
	{

	}
}
