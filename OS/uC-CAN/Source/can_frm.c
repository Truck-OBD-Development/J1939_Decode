/*
****************************************************************************************************
*                                               uC/CAN
*                                       The Embedded CAN suite
*
*                          (c) Copyright 2003-2015; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               uC/CAN is provided in source form to registered licensees ONLY.  It is 
*               illegal to distribute this source code to any third party unless you receive 
*               written permission by an authorized Micrium representative.  Knowledge of 
*               the source code may NOT be used to develop a similar product.
*
*               Please help us continue to provide the Embedded community with the finest 
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
****************************************************************************************************
*/

/*
****************************************************************************************************
* Filename      : can_frm.c
* Version       : V2.42.00
* Programmer(s) : E0
* Purpose       : This source file implements the common CAN frame handling.
****************************************************************************************************
*/

/*
****************************************************************************************************
*                                             INCLUDES
****************************************************************************************************
*/
#include "can_frm.h"
#include "can_cfg.h"
#include "can_err.h"
/*
****************************************************************************************************
*                                             DEFINES
****************************************************************************************************
*/

/*
****************************************************************************************************
*                                              MACROS
****************************************************************************************************
*/

/*
****************************************************************************************************
*                                            LOCAL DATA
****************************************************************************************************
*/

/*
****************************************************************************************************
*                                            GOBAL DATA
****************************************************************************************************
*/

/*
****************************************************************************************************
*                                            FUNCTIONS
****************************************************************************************************
*/
/*lint --e{717} use of do {} while (0) */

/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      WRITE VALUE INTO CAN FRAME
* \ingroup  UCCAN
*
*           This function copies a given value with a given width into the frame at the
*           given position. If width or position is out of range, no changes in the
*           frame was done.
*
* \note     Current limitation of this function: data width must be 1,2 or 4. The position range
*           depends on the data width:
*           - if width is byte (1), the position range is: 0..7
*           - if width is word (2), the position range is: 0..6
*           - if width is long (4), the position range is: 0..4
*
* \param    frm               Pointer to CAN frame
*
* \param    value             Value to be inserted into CAN frame
*
* \param    width             Number of bytes, which shall be copied to the CAN frame
*                             { range: 1, 2 or 4 }
*
* \param    pos               Position of first byte, which is used in the CAN frame
*                             { range: 0..7 }
*/
/*------------------------------------------------------------------------------------------------*/
void CanFrmSet(CANFRM *frm, CPU_INT32U value, CPU_INT08U width, CPU_INT08U pos)
{
    CPU_INT08U  coding;                               /* Local: coding of payload bytes           */
    CPU_INT08U  *data;                                /* Local: pointer to payload                */
#if CANSIG_GRANULARITY == CAN_CFG_BIT
    CPU_INT16U  i;                                    /* Local: loop variable                     */
    CPU_INT16U  byte;                                 /* Local: index to data in canframe         */
    CPU_INT16U  bits;                                 /* Local: index to bit inside byte          */
    CPU_INT08U  datamask;                             /* Local: bitmask for databyte              */
    CPU_INT32U  valuemask;                            /* Local: bitmask for value parameter       */
#endif


#if CANFRM_ARG_CHK_EN > 0
    if (frm == NULL_PTR) {                            /* if frame is an invalid pointer           */
        can_errnum = CAN_ERR_NULLPTR;
        return;
    }

  #if CANSIG_GRANULARITY == CAN_CFG_BYTE              /* BYTE GRANULARITY                         */
    if ((width != 1u) && (width != 2u) && (width != 4u)) {
        can_errnum = CAN_ERR_FRMWIDTH;
        return;
    }
  #else                                               /* BIT GRANULARITY                          */
    if ((width + (pos & ~CANFRM_CODING_MSK)) > 64u) {
        can_errnum = CAN_ERR_FRMWIDTH;
        return;
    }
  #endif
#endif
                                                      /*------------------------------------------*/
    coding = (pos & CANFRM_CODING_MSK);               /* get the coding bits out of position      */
    pos    = pos & (CPU_INT08U)(~CANFRM_CODING_MSK);  /* clear coding bits in position            */

                                                      /*------------------------------------------*/
#if CANSIG_GRANULARITY == CAN_CFG_BYTE                /* BYTE GRANULARITY                         */
                                                      /*------------------------------------------*/

    if (width == 1u) {                                /* see, if width indicates 'byte'           */
        if (pos <= 7u) {                              /* yes: see, if position is in range        */
            data  = frm->Data + pos;                  /* calculate byte pointer to given position */
            *data = (CPU_INT08U)(value);              /* copy byte to CAN frame payload           */
        }
    } else if (width == 2u) {                         /* otherwise see, if width indicates 'word' */
        if (pos <= 6u) {                              /* yes: see, if position is in range        */
            data = frm->Data + pos;                   /* calculate byte pointer to given position */
                                                      /*------------------------------------------*/
            if (coding == CANFRM_BIG_ENDIAN) {        /* see, if big endian in payload            */
                *data   = (CPU_INT08U)(value >> 8);   /* yes: copy MSB                            */
                 data++;
                *data   = (CPU_INT08U)(value);        /*      copy LSB                            */
            } else {                                  /* otherwise: little endian in payload      */
                *data   = (CPU_INT08U)(value);        /* yes: copy LSB                            */
                 data++;
                *data   = (CPU_INT08U)(value >> 8);   /*      copy MSB                            */
            }
        }
    } else if (width == 4u) {                         /* otherwise see, if width indicates 'long' */
        if (pos <= 4u) {                              /* yes: see, if position is in range        */
            data = frm->Data + pos;                   /* calculate byte pointer to given position */
                                                      /*------------------------------------------*/
            if (coding == CANFRM_BIG_ENDIAN) {        /* see, if big endian in payload           */
                *data = (CPU_INT08U)(value >> 24);    /* yes: copy MSB of HW                      */
                 data++;
                *data = (CPU_INT08U)(value >> 16);    /*      copy LSB of HW                      */
                 data++;
                *data = (CPU_INT08U)(value >> 8);     /*      copy MSB of LW                      */
                 data++;
                *data   = (CPU_INT08U)(value);        /*      copy LSB of LW                      */
            } else {                                  /* otherwise: little endian in payload     */
                *data = (CPU_INT08U)(value);          /* yes: copy LSB of LW                      */
                 data++;
                *data = (CPU_INT08U)(value >> 8);     /*      copy MSB of LW                      */
                 data++;
                *data = (CPU_INT08U)(value >> 16);    /*      copy LSB of HW                      */
                 data++;
                *data   = (CPU_INT08U)(value >> 24);  /*      copy MSB of HW                      */
            }
        }
    } else {
                                                      /* should not be reached                    */
    }
                                                      /*------------------------------------------*/
#else                                                 /* BIT BRANULARITY                          */
                                                      /*------------------------------------------*/


    if ((width <= 32u) &&                             /* conditions to set bits in frame          */
       ((width + pos) <= 64u)) {

        valuemask = 1u;                               /* set mask for first bit                   */
        byte = pos / 8u;                              /* get byte out of pos                      */
        data = frm->Data + byte;
                                                      /*------------------------------------------*/
        if (coding == CANFRM_BIG_ENDIAN) {            /* check endianess                          */
          if (((pos % 8u) == 7u) &&                   /* check if we can copy bytes               */
                ((width % 8u) == 0u)) {
                while (width > 0u) {
                    width -= 8u;
                    *data = (CPU_INT08U)(value >> width);
                     data++;
                }
            } else {
                valuemask = valuemask << (width - 1u);
                for (i=0u; i<width; i++) {            /* copy single bits                         */
                    bits = (pos % 8u);                /* get bit position inside byte             */
                    datamask = 1u << bits;            /* prepare mask for data                    */
                    if ((value & valuemask) != 0u) {  /* set bit                                  */
                        *data = *data | datamask;
                    } else {                          /* clear  bit                               */
                        *data = *data & ~datamask;
                    }
                    valuemask = valuemask >> 1u;      /* prepare mask for next bit in value       */
                    if (bits == 0u) {                 /* calc new byte pos each time bit is 0     */
                        pos += 16u;
                        data++;
                    }
                    pos--;
                }
            }
        }
        else {
            if (((pos % 8u) == 0u) &&                 /* check if we can copy bytes               */
                ((width % 8u) == 0u)) {
                while (width > 0u) {
                  *data++ = (CPU_INT08U)(value);
                    value = value >> 8u;
                    width -= 8u;
                }
            }
            else {                                    /* little endian                            */
                for (i=0u; i<width; i++) {            /* copy single bits                         */
                    bits = (pos % 8u);                /* get bit position inside byte             */
                    if (bits == 0u) {                 /* calc new byte pos each time bit is 0     */
                        byte = pos / 8u;              /* get byte out of pos                      */
                        data = frm->Data + byte;
                    }
                    datamask = 1u << bits;            /* prepare mask for data                    */
                    if ((value & valuemask) != 0u) {  /* set bit                                  */
                        *data |= datamask;
                    } else {                          /* clear  bit                               */
                        *data &= ~datamask;
                    }
                    valuemask = valuemask << 1u;      /* prepare mask for next bit in value       */
                    pos++;
                }
            }
        }
    }
#endif
}


/*------------------------------------------------------------------------------------------------*/
/*!
* \brief                      READ VALUE OUT OF CAN FRAME
* \ingroup UCCAN
*
*           This function returns the value with a given bitwidth out of the frame at
*           the given position.  If width or position is out of range, the return value
*           is 0.
*
* \note     Current limitation of this function:  data width must be 1,2 or 4. The position range
*           depends on the data width:
*           - if width is byte (1), the position range is: 0..7
*           - if width is word (2), the position range is: 0..6
*           - if width is long (4), the position range is: 0..4
*
* \param    frm               Pointer to CAN frame
*
* \param    width             Number of bytes, which shall be copied from the CAN frame
*                             { range: 1, 2 or 4 }
*
* \param    pos               Position of first byte, which is copied out of the CAN frame
*                             { range: 0..7 }
*
* \return   Value, constructed out of the CAN frame payload, 0xffffffff on error
*/
/*------------------------------------------------------------------------------------------------*/
CPU_INT32U CanFrmGet(CANFRM *frm, CPU_INT08U width, CPU_INT08U pos)
{
    CPU_INT32U  result = (CPU_INT32U)0L;              /* Local: function result                   */
    CPU_INT08U  coding;                               /* Local: coding of payload bytes           */
    CPU_INT08U *data;                                 /* Local: pointer to payload data           */
#if CANSIG_GRANULARITY == CAN_CFG_BIT
    CPU_INT16U i;                                     /* Local: loop variable                     */
    CPU_INT16U byte;                                  /* Local: index to data in canframe         */
    CPU_INT16U bits;                                  /* Local: index to bit inside byte          */
    CPU_INT08U  datamask;                             /* Local: bitmask for databyte              */
    CPU_INT32U resultmask = 1;                        /* Local: bitmask for result return value   */
    CPU_INT32U temp;                                  /* Local: temporary variable                */
#endif

#if CANFRM_ARG_CHK_EN > 0
    if (frm == NULL_PTR) {                            /* if frame is an invalid pointer           */
        can_errnum = CAN_ERR_NULLPTR;
        return 0xFFFFFFFFu;
    }

#if CANSIG_GRANULARITY == CAN_CFG_BYTE
    if ((width != 1u) && (width != 2u) && (width != 4u)) {
        can_errnum = CAN_ERR_FRMWIDTH;
        return 0xFFFFFFFFu;
    }
#else
    if ((width < 1u) || (width > 32u)) {
        can_errnum = CAN_ERR_FRMWIDTH;
        return 0xFFFFFFFFu;
    }
#endif

#endif
                                                      /*------------------------------------------*/
    coding = (pos & CANFRM_CODING_MSK);               /* get the coding bits out of position      */
    pos    = pos & (CPU_INT08U)(~CANFRM_CODING_MSK);  /* clear coding bits in position            */

                                                      /*------------------------------------------*/
#if CANSIG_GRANULARITY == CAN_CFG_BYTE                /* BYTE GRANULARITY                         */
                                                      /*------------------------------------------*/

    if (width == 1u) {                                /* see, if width indicates 'byte'           */
        if (pos <= 7u) {                              /* yes: see, if position is in range        */
            data   = frm->Data + pos;                 /* calculate byte pointer to given position */
            result = (CPU_INT32U)*data;               /* get byte from CAN frame payload          */
        }
    } else if (width == 2u) {                         /* otherwise see, if width indicates 'word' */
        if (pos <= 6u) {                              /* yes: see, if position is in range        */
            data = frm->Data + pos;                   /* calculate byte pointer to given position */
                                                      /*------------------------------------------*/
            if (coding == CANFRM_BIG_ENDIAN) {        /* see, if big endian in payload            */
                result  = (CPU_INT32U)(*data) << 8u;  /* yes: get MSB                             */
                data++;
                result |= (CPU_INT32U)(*data);        /*      get LSB                             */
            } else {                                  /* otherwise: little endian in payload      */
                result  = (CPU_INT32U)(*data);        /* yes: get LSB                             */
                data++;
                result |= (CPU_INT32U)(*data) << 8u;  /*      get MSB                             */
            }
        }
    } else if (width == 4u) {                         /* otherwise see, if width indicates 'long' */
        if (pos <= 4u) {                              /* yes: see, if position is in range        */
            data = frm->Data + pos;                   /* calculate byte pointer to given position */
                                                      /*------------------------------------------*/
            if (coding == CANFRM_BIG_ENDIAN) {        /* see, if big endian in payload            */
                result  = (CPU_INT32U)(*data) << 24;  /* yes: get MSB of HW                       */
                data++;
                result |= (CPU_INT32U)(*data) << 16;  /*      get LSB of HW                       */
                data++;
                result |= (CPU_INT32U)(*data) << 8;   /*      get MSB of LW                       */
                data++;
                result |= (CPU_INT32U)(*data);        /*      get LSB of LW                       */
            } else {                                  /* otherwise: big endian in payload         */
                result  = (CPU_INT32U)(*data);        /* yes: get LSB of LW                       */
                data++;
                result |= (CPU_INT32U)(*data) << 8;   /*      get MSB of LW                       */
                data++;
                result |= (CPU_INT32U)(*data) << 16;  /*      get LSB of HW                       */
                data++;
                result |= (CPU_INT32U)(*data) << 24;  /*      get MSB of HW                       */
            }
        }
    } else {
                                                      /* should not be reached                    */
    }
                                                      /*------------------------------------------*/
#else                                                 /* BIT BRANULARITY                          */
                                                      /*------------------------------------------*/

    if ((width <= 32) &&                              /* conditions to get bits out of frame      */
       ((width + pos) <= 64)) {

        result = 0;
        byte = pos / 8;                               /* get byte out of pos                      */
        data = frm->Data + byte;
                                                      /*------------------------------------------*/
        if (coding == CANFRM_BIG_ENDIAN) {            /* check endianess                    */
            if (((pos % 8) == 7) &&                   /* check if we can copy bytes               */
                ((width % 8) == 0)) {
                while (width > 0) {
                    result = result << 8;
                    result |= (CPU_INT32U) *data++;
                    width -= 8;
                }
            }
            else {
                for (i=0;i<width;i++) {               /* copy single bits                         */
                    bits = (pos % 8);                 /* get bit position inside byte             */
                    result = result << 1;
                    datamask = 1 << bits;             /* prepare mask for data                    */
                    if ((*data & datamask) != 0) {    /* set bit                                  */
                        result++;
                    }
                    if (bits == 0) {                  /* calc new byte pos each time bit is 0     */
                        pos += 16;
                        data++;
                    }
                    pos--;
                }
            }
        }
        else {                                        /* little endian */
            if (((pos % 8) == 0) &&                   /* check if we can copy bytes               */
                ((width % 8) == 0)) {
                i = 0;
                while (width > i) {
                    temp = (CPU_INT32U) *data++;
                    result |= (temp << i);
                    i += 8;
                }
            }
            else {                                    /*------------------------------------------*/
                for (i=0;i<width;i++) {               /* copy single bits                         */
                    bits = (pos % 8);                 /* get bit position inside byte             */
                    if (bits == 0) {                  /* calc new byte pos each time bit is 0     */
                        byte = pos / 8;               /* get byte out of bit position             */
                        data = frm->Data + byte;
                    }
                    datamask = 1 << bits;             /* prepare mask for data                    */
                    if ((*data & datamask) != 0) {    /* set bit                                  */
                        result |= resultmask;
                    }
                    pos++;
                    resultmask = resultmask << 1;
                }
            }
        }
    }
#endif
    return(result);                                   /* return function result                   */
}
