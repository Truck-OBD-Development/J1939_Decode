
/*
***************************************************************************
** Filename:	test_j1939_tp.h
** Author:
** Date:
** Description:	J1939 transmit protocol
***************************************************************************
**/
#include "DataType.h"
#include "can.h"
#include "test_j1939_can.h"
#ifndef _TEST_J1939_H
#define _TEST_J1939_H

#define J1939_MAX_MESSAGE_LENGTH         170  //1785
#define J1939_MAX_DATA_SIZE              8

#define MAX_NUM_ERRORS                   3


/*
--- Connection Management defines
*/
#define RTS_CONTROL_BYTE            0x10
#define BAM_CONTROL_BYTE            0x20
#define CTS_CONTROL_BYTE            0x11
#define EOM_CONTROL_BYTE            0x13
#define ABORT_CONTROL_BYTE          0xFF
#define RESERVED_BYTE               0xFF
#define CM_PDU_FORMAT               0xEC
#define CM_PDU_DATA                 0xEB
#define CM_PDU_FORMAT_PGN           0xEC00
#define CM_PDU_DATA_PGN             0xEB00


#define CM_PDU_FORMAT               0xEC
#define CM_PDU_DATA                 0xEB
#define CM_PDU_FORMAT_PGN           0xEC00
#define CM_PDU_DATA_PGN             0xEB00

/* State defines */
#define BAM_WAIT_STATE          0
#define TIMER_RESETSTATE        1
#define BAM_START_STATE         2
#define BAM_NEXT_PACKET         3
#define CM_START_STATE          4
#define CM_WAIT_RESPONSE        5
#define ABORT_STATE             6
#define CM_NEXT_PACKET          7
#define CM_NEXT_PACKET_WAIT     8

/* connection timeout define */
#define TP_CM_TIMER        1250    /* 1250ms */
#define TP_CM_KEEP_TIMER   250     /* 250ms timer refresh after receive a keep waiting command */

/* default transport priority */
#define DEFAULT_TRANSPORT_PRIORITY  7

/** define for J1939 CAN message **/
typedef unsigned long PGN_T;

typedef struct
{
   PGN_T PGN ;
   uint8_t data[J1939_MAX_MESSAGE_LENGTH] ;
   uint16_t byte_count ;
   uint8_t priority ;
   uint8_t dest_addr;

} J1939_TX_MESSAGE_T ;

typedef struct
{
   PGN_T PGN ;
   uint8_t  data[J1939_MAX_MESSAGE_LENGTH] ;
   uint16_t byte_count ;
   uint8_t source_addr ;
   uint8_t dest_addr ;
} J1939_RX_MESSAGE_T ;

typedef struct
{
	J1939_TX_MESSAGE_T    tx_msg_ptr ;
	uint16_t              time ;
	int8_t                retry ;
	uint8_t               packet_index ;
	uint8_t               total_packets ;
	uint8_t               packets_ok_to_send;
	uint8_t               state ;
} J1939_TRANSPORT_TX_INFO ;

typedef enum
{
	ENUM_TP_TYPE_RTS      = 16,
	ENUM_TP_TYPE_CTS      = 17,
	ENUM_TP_TYPE_ENDOFACK = 19,
	ENUM_TP_TYPE_ABORT    = 255,
}enum_tp_control_type;

typedef enum
{
	ENUM_CM_TIMEOUT_NORMAL  = 0,
	ENUM_CM_TIMEOUT_ABNORMAL = 1,
}enum_cm_timeout_type;
/** define J1939 transmit step **/
typedef enum
{
	ENUM_J1939_TX_WAIT,
	ENUM_J1939_TX_CM_START,
	ENUM_J1939_TX_CM_WAIT,
	ENUM_J1939_TX_DT,
	ENUM_J1939_WAIT_ACK,
	ENUM_J1939_TX_ERROR,
	ENUM_J1939_TX_DONE,
}enum_j1939_tx_step;


/* API for J1939 TP*/
void J1393_Init(void);
void J1939_Main(uint16_t dt_ms);
void J1939_CAN_Tx(J1939_TX_MESSAGE_T msg);
#endif
