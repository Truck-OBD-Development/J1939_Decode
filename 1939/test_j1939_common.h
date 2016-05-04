
/*
***************************************************************************
** Filename:	test_j1939_common.h
** Author:
** Date:
** Description:
***************************************************************************
**/
#include "DataType.h"


#ifndef _TEST_COMMON_H
#define _TEST_COMMON_H


/*************************************************************************/
/* Defines                                                               */
/*************************************************************************/



/*************************************************************************/
/* API functions                                                         */
/*************************************************************************/
struct_can_sig InitializeCanSignal(const struct_can_sig_consts *c);
void RawToEng_sig(struct_can_sig* s, uint16_t raw);
uint16_t EngToRaw_sig(const struct_can_sig s);
uint32_t canUnPack32(const struct_can_sig_consts *sig, uint8_t *b);
uint16_t canUnPack16(const struct_can_sig_consts *sig, uint8_t *b);
uint8_t canUnPack8(const struct_can_sig_consts *sig, uint8_t *b);
uint8_t canPack32(const struct_can_sig_consts *c, uint32_t value, uint8_t *b);
uint8_t canPack16(const struct_can_sig_consts *c, uint16_t value, uint8_t *b);
uint8_t canPack8(const struct_can_sig_consts *c, uint8_t value, uint8_t *b);
float32_t Get_SigVal(struct_can_sig sig);
void SetEngVal(struct_can_sig* s, float32_t eng);
uint16_t LoopMe(uint16_t value, uint16_t limit);
float32_t abs_f32(const float32_t value);
#endif
