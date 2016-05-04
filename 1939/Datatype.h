/*
***************************************************************************
**
** Copyright 2015 LETV, Inc. All rights reserved.
**
** LETV Proprietary Information.
** This document contains proprietary and confidential information and is
** tendered for information and evaluation purposes only; no copy or other
** use or dissemination by a third party can be made of this information
** without the express written permission of LETV.
**
***************************************************************************
*/

/*
***************************************************************************
** Filename:	Datatype.h
** Author:
** Date:
** Description:	J1939 transmit protocol
***************************************************************************
**/
#include "stdint.h"


#ifndef _DATATYPE_H

#define  _DATATYPE_H

/*** Define MISRA C datatype ***/
/*
typedef signed char 				int8_t;
typedef unsigned char 				uint8_t;
typedef volatile signed char 		vint8_t;
typedef volatile unsigned char 		vuint8_t;
typedef signed short 				int16_t;
typedef unsigned short 				uint16_t;
typedef volatile signed short 		vint16_t;
typedef volatile unsigned short 	vuint16_t;
typedef signed long int 			int32_t;
typedef unsigned long int 			uint32_t;
typedef volatile signed long int 	vint32_t;
typedef volatile unsigned long int 	vuint32_t;
*/
typedef float 						float32_t;
typedef long double 				float64_t;
typedef unsigned char                     bool_t;


#ifndef  FALSE
#define     FALSE   0U
#endif

#ifndef TRUE
#define     TRUE    1U
#endif

#ifndef NULL
#define NULL 0
#endif


/*** CAN signal data define ****/

typedef struct
{
    uint16_t         startBit;   /* bit, Motorola signal start bit */
    uint8_t         length;     /* bits, signal length */
    float32_t       factor;     /* units/bit, resolution */
    float32_t       offset;     /* units, offset */
    float32_t       min;        /* units, minimum allowed value */
    float32_t       max;        /* units, maximum allowed value */
	uint8_t         is_signed;  /* flag, signed value */
    uint8_t	    byteOrder;  /* byte order, Motorola or Intel format */
} struct_can_sig_consts;

typedef struct
{
    float32_t                   eng;        /* engineering value     */
    const struct_can_sig_consts *sigdef;    /* pointer to signal constants definition */
} struct_can_sig;


#endif
