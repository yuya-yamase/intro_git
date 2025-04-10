/* ------------------------------------------------------------------------ */
/* file name   : LIB_memset.c                                              */
/* ------------------------------------------------------------------------ */
#include <Std_Types.h>
#include <LIB.h>
/* ------------------------------------------------------------------------ */
/* word size */
#define D_SET_1WORD_SIZE	(sizeof(uint32))
#define D_SET_2WORD_SIZE	(2U * D_SET_1WORD_SIZE)
#define D_SET_3WORD_SIZE	(3U * D_SET_1WORD_SIZE)
#define D_SET_4WORD_SIZE	(4U * D_SET_1WORD_SIZE)
#define D_SET_5WORD_SIZE	(5U * D_SET_1WORD_SIZE)
#define D_SET_6WORD_SIZE	(6U * D_SET_1WORD_SIZE)
#define D_SET_7WORD_SIZE	(7U * D_SET_1WORD_SIZE)
#define D_SET_8WORD_SIZE	(8U * D_SET_1WORD_SIZE)
/* word */
#define D_SET_1WORD			(1U)
#define D_SET_2WORD			(2U)
#define D_SET_4WORD			(4U)
#define D_SET_8WORD			(8U)
/* byte */
#define D_SET_0BYTE			(0U)
#define D_SET_1BYTE			(1U)
#define D_SET_2BYTE			(2U)
#define D_SET_3BYTE			(3U)
/* threshold for word copy */
#define D_SET_WORDFILL_THRESHOLD	D_SET_4WORD_SIZE

#define LIB_START_SEC_CODE
#include <LIB_MemMap.h>
/* ------------------------------------------------------------------------ */
static void LIB_memset_4(uint8 dst[], uint8 data, uint32 *set_byte, uint32 word);
/* ------------------------------------------------------------------------ */
void LIB_memset (uint8 dst[], uint8 data, uint32 size)
{
	uint32	set_byte = D_SET_0BYTE;
	uint32	word;
	uint32	offset;


	if (size >= D_SET_WORDFILL_THRESHOLD)
	{
		/* adjust dst to word alignment */
		offset = ((uint32)dst) % D_SET_1WORD_SIZE;
		switch (offset)
		{
		case D_SET_1BYTE:
			dst[ D_SET_0BYTE ] = data;
			dst[ D_SET_1BYTE ] = data;
			dst[ D_SET_2BYTE ] = data;

			set_byte = D_SET_3BYTE;
			break;

		case D_SET_2BYTE:
			dst[ D_SET_0BYTE ] = data;
			dst[ D_SET_1BYTE ] = data;

			set_byte = D_SET_2BYTE;
			break;

		case D_SET_3BYTE:
			dst[ D_SET_0BYTE ] = data;

			set_byte = D_SET_1BYTE;
			break;

		case D_SET_0BYTE:
		default:
			/* nothing to do */
			break;
		}

		/* calcurate fill word num */
		word = (size - set_byte) / D_SET_1WORD_SIZE;

		LIB_memset_4(dst, data, &set_byte, word);
	}

	/* fill the byte */
	for (; set_byte < size; set_byte ++)
	{
		dst[ set_byte ] = data;
	}
}
/* ------------------------------------------------------------------------ */
static void LIB_memset_4 (uint8 dst[], uint8 data, uint32 *set_byte, uint32 word)
{
	uint32	byte = *set_byte;
	uint32	tmp  = ( ((uint32)data << 24U)
				   | ((uint32)data << 16U)
				   | ((uint32)data <<  8U)
				   | ((uint32)data       )
				   );

	/* 8word fill */
	for (; word >= D_SET_8WORD; word -= D_SET_8WORD)
	{
		*(uint32*)(&dst[ byte                    ]) = tmp;
		*(uint32*)(&dst[ byte + D_SET_1WORD_SIZE ]) = tmp;
		*(uint32*)(&dst[ byte + D_SET_2WORD_SIZE ]) = tmp;
		*(uint32*)(&dst[ byte + D_SET_3WORD_SIZE ]) = tmp;
		*(uint32*)(&dst[ byte + D_SET_4WORD_SIZE ]) = tmp;
		*(uint32*)(&dst[ byte + D_SET_5WORD_SIZE ]) = tmp;
		*(uint32*)(&dst[ byte + D_SET_6WORD_SIZE ]) = tmp;
		*(uint32*)(&dst[ byte + D_SET_7WORD_SIZE ]) = tmp;

		byte += D_SET_8WORD_SIZE;
	}

	/* 4word fill */
	if (word >= D_SET_4WORD)
	{
		*(uint32*)(&dst[ byte                    ]) = tmp;
		*(uint32*)(&dst[ byte + D_SET_1WORD_SIZE ]) = tmp;
		*(uint32*)(&dst[ byte + D_SET_2WORD_SIZE ]) = tmp;
		*(uint32*)(&dst[ byte + D_SET_3WORD_SIZE ]) = tmp;

		byte += D_SET_4WORD_SIZE;
		word -= D_SET_4WORD;
	}

	/* 2word fill */
	if (word >= D_SET_2WORD)
	{
		*(uint32*)(&dst[ byte                    ]) = tmp;
		*(uint32*)(&dst[ byte + D_SET_1WORD_SIZE ]) = tmp;

		byte += D_SET_2WORD_SIZE;
		word -= D_SET_2WORD;
	}

	/* 1word fill */
	if (word >= D_SET_1WORD)
	{
		*(uint32*)(&dst[ byte                    ]) = tmp;

		byte += D_SET_1WORD_SIZE;
	}

	*set_byte = byte;
}
/* ------------------------------------------------------------------------ */
#define LIB_STOP_SEC_CODE
#include <LIB_MemMap.h>
/* ------------------------------------------------------------------------ */
