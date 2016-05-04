
/*
***************************************************************************
** Filename:	test_j1939_common.c
** Author:
** Date:
** Description:
***************************************************************************
**/


#include "test_j1939_common.h"


/*************************************************************************/
/* Defines                                                               */
/*************************************************************************/



/*************************************************************************/
/* static variables                                                      */
/*************************************************************************/



/*************************************************************************/
/* local function                                                        */
/*************************************************************************/


/*************************************************************************/
/* functions                                                             */
/*************************************************************************/

struct_can_sig InitializeCanSignal(const struct_can_sig_consts *c)
{

    struct_can_sig s;

    s.sigdef = c;
    s.eng = 0.0F;

    return (s);

}


/*************************************************************************/
void RawToEng_sig(struct_can_sig* s, uint16_t raw)
{

    struct_can_sig_consts c;

    c = *(*s).sigdef;

    (*s).eng       = 0.0F;


    (*s).eng = c.factor * ((float32_t) raw) + c.offset;


}


/*************************************************************************/
uint16_t EngToRaw_sig(const struct_can_sig s)
{
    int32_t                     result  = 0U;
    struct_can_sig_consts       c       = *s.sigdef;
    float32_t                   tmp     = 0.0F;



	tmp = s.eng;
	tmp += c.factor / 2.0F;     /* add half of a factor to avoid trunc error */

	if ( tmp > c.max )          /* Check for out-of-range high */
	{
		tmp = c.max;
	}

	if ( tmp < c.min )          /* Check for out-of-range high */
	{
		tmp = c.min;
	}

	/*Convert to Raw */
	result = (int32_t)((tmp - c.offset) / c.factor);

	if ( c.is_signed && (tmp < 0.0F) )
	{
		result += 0xFFFF & ((0x1 << (0x1F & c.length)) - 1);
	}

	if ( result < 0 )           /* Check for out-of-range low */
	{
		result = 0;
	}

    return ((uint16_t)result);
}

/*************************************************************************/
uint32_t canUnPack32(const struct_can_sig_consts *sig, uint8_t *b)
{
      uint32_t  value32     = 0;
      uint32_t  maskValue   = ((uint32_t)1 << sig->length) - 1;
      uint8_t   byteIndex   = (uint8_t)(sig->startBit >> 3);

      if(sig->byteOrder == 0)
      {
    	  value32 |= (uint32_t)b[byteIndex];
    	  value32 |= ((uint32_t)b[byteIndex - 1] << 8);
    	  value32 |= ((uint32_t)b[byteIndex - 2] << 16);
    	  value32 |= ((uint32_t)b[byteIndex - 3] << 24);

      }
      else
      {
    	  value32 |= (uint32_t)b[byteIndex];
    	  value32 |= ((uint32_t)b[byteIndex + 1] << 8);
    	  value32 |= ((uint32_t)b[byteIndex + 2] << 16);
    	  value32 |= ((uint32_t)b[byteIndex + 3] << 24);
      }
      value32 = value32 >> (sig->startBit % 8);

      value32 = value32 & maskValue;

      return value32;
}


/*************************************************************************/
uint16_t canUnPack16(const struct_can_sig_consts *sig, uint8_t *b)
{
      uint32_t  value32     = 0;
      uint16_t  maskValue   = (uint16_t)((1 << sig->length) - 1);
      uint8_t   byteIndex   = (uint8_t)(sig->startBit >> 3);

      if(sig->byteOrder == 0)
      {
         value32 |= (uint32_t)b[byteIndex];
    	 value32 |= ((uint32_t)b[byteIndex - 1] << 8);
    	 value32 |= ((uint32_t)b[byteIndex - 2] << 16);

      }
      else
      {
    	  value32 |= (uint32_t)b[byteIndex];
    	  value32 |= ((uint32_t)b[byteIndex + 1] << 8);
    	  value32 |= ((uint32_t)b[byteIndex + 2] << 16);
      }
      value32 = value32 >> (sig->startBit % 8);
      value32 &= maskValue;

      return (uint16_t)value32;
}


/*************************************************************************/
uint8_t canUnPack8(const struct_can_sig_consts *sig, uint8_t *b)
{
      uint16_t  value16     = 0;
      uint8_t   maskValue   = (uint8_t)((1 << sig->length) - 1);
      uint8_t   byteIndex   = (uint8_t)(sig->startBit >> 3);
      if(sig->byteOrder == 0)
      {
         value16 |= (uint16_t)b[byteIndex];
         value16 |= ((uint16_t)b[byteIndex - 1] << 8);
      }
      else
      {
    	  value16 |= (uint16_t)b[byteIndex];
    	  value16 |= ((uint16_t)b[byteIndex + 1] << 8);
      }
      value16 = (uint16_t)(value16 >> (sig->startBit % 8));
      value16 &= maskValue;

      return (uint8_t)value16;
}

/*************************************************************************/
uint8_t canPack32(const struct_can_sig_consts *c, uint32_t value, uint8_t *b)
{
    struct_can_sig_consts   sig = *c;
    uint8_t     result      = TRUE;
    uint32_t    value32     = (uint32_t)value;
    uint32_t    maskValue   = ((uint32_t)1 << sig.length) - 1;
    uint8_t     byteIndex;

    if ( value > maskValue )
    {   /* Exceeds specified size */
        result = FALSE;
    }
    else
    {
        value32 = value32 & maskValue;
        value32 = value32 << (sig.startBit % 8);

        byteIndex = (uint8_t)(sig.startBit >> 3);
        if(sig.byteOrder == 0)
		{
			b[byteIndex]     |= value32 & 0xFF;

			if ( byteIndex > 0 )
			{
				b[byteIndex - 1] |= (value32 >> 8) & 0xFF;
			}

			if ( byteIndex > 2 )
			{
				b[byteIndex - 2] |= (value32 >> 16) & 0xFF;
			}

			if ( byteIndex > 3 )
			{
				b[byteIndex - 3] |= (value32 >> 24) & 0xFF;
			}
		}
        else
        {
        	b[byteIndex] |= value32 & 0xFF;
        	if ( byteIndex < 98 )
        	{
        		b[byteIndex + 1] |= (value32 >> 8) & 0xFF;
        	}
        	if ( byteIndex < 97 )
        	{
        		b[byteIndex + 2] |= (value32 >> 16) & 0xFF;
        	}
        	if ( byteIndex < 99 )
        	{
        		b[byteIndex + 3] |= (value32 >> 24) & 0xFF;
        	}
        }
    }

    return(result);
}


/*************************************************************************/
uint8_t canPack16(const struct_can_sig_consts *c, uint16_t value, uint8_t *b)
{
    struct_can_sig_consts sig = *c;
    uint8_t     result      = TRUE;
    uint32_t    value16     = (uint32_t)value;
    uint32_t    maskValue   = ((uint32_t)1 << sig.length) - 1;
    uint8_t     byteIndex;

    if ( value > maskValue )
    {   /* Exceeds specified size */
        result = FALSE;
    }
    else
    {
        value16 = value16 & maskValue;
        value16 = value16 << (sig.startBit % 8);

        byteIndex = (uint8_t)(sig.startBit >> 3);

        if(sig.byteOrder == 0)
        {
			b[byteIndex]     |= value16 & 0xFF;

			if ( byteIndex > 0 )
			{
				b[byteIndex - 1] |= (value16 >> 8) & 0xFF;
			}

			if ( byteIndex > 1 )
			{
				b[byteIndex - 2] |= (value16 >> 16) & 0xFF;
			}
        }
        else
        {
        	b[byteIndex] |= value16 & 0xFF;
        	if ( byteIndex < 99 )
        	{
        		b[byteIndex + 1] |= (value16 >> 8) & 0xFF;
        	}
        	if ( byteIndex < 98 )
        	{
        		b[byteIndex + 2] |= (value16 >> 16) & 0xFF;
        	}
        }
    }
    return(result);
}


/*************************************************************************/
uint8_t canPack8(const struct_can_sig_consts *c, uint8_t value, uint8_t *b)
{
    struct_can_sig_consts sig = *c;
    uint8_t     result      = TRUE;
    uint16_t    value8      = (uint8_t)value;
    uint16_t    maskValue   = (uint16_t)(((uint16_t)1 << sig.length) - 1);
    uint8_t     byteIndex;

    if ( value > maskValue )
    {   /* Exceeds specified size */
        result = FALSE;
    }
    else
    {
        value8 = (uint8_t)(value8 & maskValue);
        value8 = (uint8_t)(value8 << (sig.startBit % 8));

        byteIndex = (uint8_t)(sig.startBit >> 3);

		if(sig.byteOrder == 0)
		{
			b[byteIndex] |= value8 & 0xFF;

			if ( byteIndex > 0 )
			{
				b[byteIndex - 1] |= (value8 >> 8) & 0xFF;
			}
        }
		else
		{
			b[byteIndex] |= value8 & 0xFF;
			if ( byteIndex < 98 )
			{
				b[byteIndex + 1] |= (value8 >> 8) & 0xFF;
			}
		}
    }

    return(result);
}


/*************************************************************************/
float32_t Get_SigVal(struct_can_sig sig)
{
    float32_t result;
    
    result = sig.eng;
    
    return(result);
}

/*************************************************************************/
void SetEngVal(struct_can_sig* s, float32_t eng)
{
	/* check eng range */
    if(eng > (*s).sigdef->max)
    {
    	eng = (*s).sigdef->max;
    }
    else if (eng < (*s).sigdef->min)
    {
    	eng = (*s).sigdef->min;
    }
    else
    {
         /* do noting */
    }
    (*s).eng = eng;
}




/*************************************************************************/
uint16_t LoopMe(uint16_t value, uint16_t limit)
{

    if ( ++value > limit )
    {
        value = 0;
    }

    return(value);

}


/*************************************************************************/
float32_t abs_f32(const float32_t value)
{
    float32_t result = value;

    if ( value < 0.0F )
    {
        result = -value;
    }

    return(result);
}



