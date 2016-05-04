
/*
***************************************************************************
** Filename:	test_j1939_can.h
** Author:
** Date:
** Description:	mailbox index define 
***************************************************************************
**/
/***************************************************************************
*** MailBox for CAN1 Definition *******************************************/

/***************************************************************************
*** MailBox for CAN2 Definition *******************************************/
#define  MAILBOX_CM_BCM_TO_CHG         1
#define  MAILBOX_DT_BCM_TO_CHG         2
#define  MAILBOX_CM_CHG_TO_BCM         3
#define  MAILBOX_TP_TRIG               4
#define  MAILBOX_MSG_BCL               5
#define  MAILBOX_MSG_BCP               6
#define  MAILBOX_MSG_BCS               7
#define  MAILBOX_MSG_BEM               8
#define  MAILBOX_MSG_BHM               9
#define  MAILBOX_MSG_BRO               10
#define  MAILBOX_MSG_BSD               11
#define  MAILBOX_MSG_BSM               12
#define  MAILBOX_MSG_BST               13
#define  MAILBOX_MSG_DEBUG             14
#define  MAILBOX_MSG_CCS               15
#define  MAILBOX_MSG_CEM               16
#define  MAILBOX_MSG_CHM               17
#define  MAILBOX_MSG_CML               18
#define  MAILBOX_MSG_CRM               19
#define  MAILBOX_MSG_CRO               20
#define  MAILBOX_MSG_CSD               21
#define  MAILBOX_MSG_CST               22
#define  MAILBOX_MSG_CTS               23

/***************************************************************************
*** MailBox for CAN3 Definition *******************************************/


/***************************************************************************
*** API fucntion define  **************************************************/
void CAN_MailBoxInit(void);

