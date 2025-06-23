/* ------------------------------------------------------------------------ */
/* file name   : LIB_memcpy.c                                              */
/* ------------------------------------------------------------------------ */
#include <Std_Types.h>
#include <LIB.h>
/* ------------------------------------------------------------------------ */
/* word size */
#define D_CPY_1WORD_SIZE	(sizeof(uint32))
#define D_CPY_2WORD_SIZE	(2U * D_CPY_1WORD_SIZE)
#define D_CPY_3WORD_SIZE	(3U * D_CPY_1WORD_SIZE)
#define D_CPY_4WORD_SIZE	(4U * D_CPY_1WORD_SIZE)
#define D_CPY_5WORD_SIZE	(5U * D_CPY_1WORD_SIZE)
#define D_CPY_6WORD_SIZE	(6U * D_CPY_1WORD_SIZE)
#define D_CPY_7WORD_SIZE	(7U * D_CPY_1WORD_SIZE)
#define D_CPY_8WORD_SIZE	(8U * D_CPY_1WORD_SIZE)
/* word */
#define D_CPY_1WORD			(1U)
#define D_CPY_2WORD			(2U)
#define D_CPY_4WORD			(4U)
#define D_CPY_8WORD			(8U)
/* byte */
#define D_CPY_0BYTE			(0U)
#define D_CPY_1BYTE			(1U)
#define D_CPY_2BYTE			(2U)
#define D_CPY_3BYTE			(3U)
/* bit */
#define D_CPY_1BYTE_BIT		(8U)
#define D_CPY_4BYTE_BIT		(32U)
/* threshold for word copy */
#define D_CPY_WORDCOPY_THRESHOLD	D_CPY_4WORD_SIZE
/* ------------------------------------------------------------------------ */
#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
#define D_CPY_WORD_1ST(off, var)		((var) >> (                   D_CPY_1BYTE_BIT * (off)) )
#define D_CPY_WORD_2ND(off, var)		((var) << (D_CPY_4BYTE_BIT - (D_CPY_1BYTE_BIT * (off))))
#else
#define D_CPY_WORD_1ST(off, var)		((var) >> (D_CPY_4BYTE_BIT - (D_CPY_1BYTE_BIT * (off))))
#define D_CPY_WORD_2ND(off, var)		((var) << (                   D_CPY_1BYTE_BIT * (off)) )
#endif
/* ------------------------------------------------------------------------ */
/* #define LIB_START_SEC_CODE */
/* #include <LIB_MemMap.h> */

static void LIB_memcpy_offset_0(uint8 dst[], const uint8 src[], uint32 *cp_byte, uint32 word);
static void LIB_memcpy_offset_n(uint8 dst[], const uint8 src[], uint32 *cp_byte, uint32 word, uint32 offset);
/* ------------------------------------------------------------------------ */
void LIB_memcpy (uint8 dst[], const uint8 src[], uint32 size)
{
	uint32	cp_byte = D_CPY_0BYTE;
	uint32	rest_byte;
	uint32	cp_word;
	uint32	offset;
	uint8	tmp0;
	uint8	tmp1;
	uint8	tmp2;
	uint8	tmp3;


	if (size >= D_CPY_WORDCOPY_THRESHOLD)
	{
		/* adjust dst to word alignment */
		offset = ((uint32)dst) % D_CPY_1WORD_SIZE;
		switch (offset)
		{
		case D_CPY_1BYTE:
			tmp0 = src[ D_CPY_0BYTE ];
			tmp1 = src[ D_CPY_1BYTE ];
			tmp2 = src[ D_CPY_2BYTE ];

			dst[ D_CPY_0BYTE ] = tmp0;
			dst[ D_CPY_1BYTE ] = tmp1;
			dst[ D_CPY_2BYTE ] = tmp2;

			cp_byte = D_CPY_3BYTE;
			break;

		case D_CPY_2BYTE:
			tmp0 = src[ D_CPY_0BYTE ];
			tmp1 = src[ D_CPY_1BYTE ];

			dst[ D_CPY_0BYTE ] = tmp0;
			dst[ D_CPY_1BYTE ] = tmp1;

			cp_byte = D_CPY_2BYTE;
			break;

		case D_CPY_3BYTE:
			tmp0 = src[ D_CPY_0BYTE ];

			dst[ D_CPY_0BYTE ] = tmp0;

			cp_byte = D_CPY_1BYTE;
			break;

		case D_CPY_0BYTE:
		default:
			/* nothing to do */
			break;
		}

		/* word copy depend on src's offset */
		offset = ((uint32)&(src[ cp_byte ])) % D_CPY_1WORD_SIZE;
		if (offset != D_CPY_0BYTE)
		{
			tmp0 = src[ cp_byte           ];
			tmp1 = src[ cp_byte + D_CPY_1BYTE ];
			tmp2 = src[ cp_byte + D_CPY_2BYTE ];
			tmp3 = src[ cp_byte + D_CPY_3BYTE ];

			dst[ cp_byte           ] = tmp0;
			dst[ cp_byte + D_CPY_1BYTE ] = tmp1;
			dst[ cp_byte + D_CPY_2BYTE ] = tmp2;
			dst[ cp_byte + D_CPY_3BYTE ] = tmp3;

			cp_byte += D_CPY_1WORD_SIZE;

			/* calcurate copy word num */
			cp_word = (size - cp_byte) / D_CPY_1WORD_SIZE;

			LIB_memcpy_offset_n(dst, src, &cp_byte, cp_word, offset);
		}
		else
		{
			/* calcurate copy word num */
			cp_word = (size - cp_byte) / D_CPY_1WORD_SIZE;

			LIB_memcpy_offset_0(dst, src, &cp_byte, cp_word);
		}

		rest_byte = size - cp_byte;
	}
	else
	{
		/* copy the word */
		for (rest_byte = size; rest_byte >= D_CPY_1WORD_SIZE; rest_byte -= D_CPY_1WORD_SIZE)
		{
			tmp0 = src[ cp_byte           ];
			tmp1 = src[ cp_byte + D_CPY_1BYTE ];
			tmp2 = src[ cp_byte + D_CPY_2BYTE ];
			tmp3 = src[ cp_byte + D_CPY_3BYTE ];

			dst[ cp_byte           ] = tmp0;
			dst[ cp_byte + D_CPY_1BYTE ] = tmp1;
			dst[ cp_byte + D_CPY_2BYTE ] = tmp2;
			dst[ cp_byte + D_CPY_3BYTE ] = tmp3;

			cp_byte += D_CPY_1WORD_SIZE;
		}
	}

	/* copy the byte */
	for (; rest_byte > D_CPY_0BYTE; rest_byte --)
	{
		tmp0 = src[ cp_byte ];

		dst[ cp_byte ] = tmp0;

		cp_byte ++;
	}
}
/* ------------------------------------------------------------------------ */
static void LIB_memcpy_offset_0 (uint8 dst[], const uint8 src[], uint32 *cp_byte, uint32 word)
{
	uint32	byte = *cp_byte;
	uint32	tmp0;
	uint32	tmp1;
	uint32	tmp2;
	uint32	tmp3;
	uint32	tmp4;
	uint32	tmp5;
	uint32	tmp6;
	uint32	tmp7;


	/* 8word copy */
	for (; word >= D_CPY_8WORD; word -= D_CPY_8WORD)
	{
		tmp0 = *(const uint32*)(&src[ byte                ]);
		tmp1 = *(const uint32*)(&src[ byte + D_CPY_1WORD_SIZE ]);
		tmp2 = *(const uint32*)(&src[ byte + D_CPY_2WORD_SIZE ]);
		tmp3 = *(const uint32*)(&src[ byte + D_CPY_3WORD_SIZE ]);
		tmp4 = *(const uint32*)(&src[ byte + D_CPY_4WORD_SIZE ]);
		tmp5 = *(const uint32*)(&src[ byte + D_CPY_5WORD_SIZE ]);
		tmp6 = *(const uint32*)(&src[ byte + D_CPY_6WORD_SIZE ]);
		tmp7 = *(const uint32*)(&src[ byte + D_CPY_7WORD_SIZE ]);
		
		*(uint32*)(&dst[ byte                ]) = tmp0;
		*(uint32*)(&dst[ byte + D_CPY_1WORD_SIZE ]) = tmp1;
		*(uint32*)(&dst[ byte + D_CPY_2WORD_SIZE ]) = tmp2;
		*(uint32*)(&dst[ byte + D_CPY_3WORD_SIZE ]) = tmp3;
		*(uint32*)(&dst[ byte + D_CPY_4WORD_SIZE ]) = tmp4;
		*(uint32*)(&dst[ byte + D_CPY_5WORD_SIZE ]) = tmp5;
		*(uint32*)(&dst[ byte + D_CPY_6WORD_SIZE ]) = tmp6;
		*(uint32*)(&dst[ byte + D_CPY_7WORD_SIZE ]) = tmp7;

		byte += D_CPY_8WORD_SIZE;
	}

	/* 4word copy */
	if (word >= D_CPY_4WORD)
	{
		tmp0 = *(const uint32*)(&src[ byte                ]);
		tmp1 = *(const uint32*)(&src[ byte + D_CPY_1WORD_SIZE ]);
		tmp2 = *(const uint32*)(&src[ byte + D_CPY_2WORD_SIZE ]);
		tmp3 = *(const uint32*)(&src[ byte + D_CPY_3WORD_SIZE ]);

		*(uint32*)(&dst[ byte                ]) = tmp0;
		*(uint32*)(&dst[ byte + D_CPY_1WORD_SIZE ]) = tmp1;
		*(uint32*)(&dst[ byte + D_CPY_2WORD_SIZE ]) = tmp2;
		*(uint32*)(&dst[ byte + D_CPY_3WORD_SIZE ]) = tmp3;

		byte += D_CPY_4WORD_SIZE;
		word -= D_CPY_4WORD;
	}

	/* 2word copy */
	if (word >= D_CPY_2WORD)
	{
		tmp0 = *(const uint32*)(&src[ byte                ]);
		tmp1 = *(const uint32*)(&src[ byte + D_CPY_1WORD_SIZE ]);

		*(uint32*)(&dst[ byte                ]) = tmp0;
		*(uint32*)(&dst[ byte + D_CPY_1WORD_SIZE ]) = tmp1;

		byte += D_CPY_2WORD_SIZE;
		word -= D_CPY_2WORD;
	}

	/* 1word copy */
	if (word >= D_CPY_1WORD)
	{
		tmp0 = *(const uint32*)(&src[ byte                ]);

		*(uint32*)(&dst[ byte                ]) = tmp0;

		byte += D_CPY_1WORD_SIZE;
	}

	*cp_byte = byte;
}
/* ------------------------------------------------------------------------ */
static void LIB_memcpy_offset_n (uint8 dst[], const uint8 src[], uint32 *cp_byte, uint32 word, uint32 offset)
{
	uint32	byte = *cp_byte;
	uint32	tmp0;
	uint32	tmp1;
	uint32	tmp2;
	uint32	tmp3;
	uint32	tmp4;
	uint32	tmp5;
	uint32	tmp6;
	uint32	tmp7;
	uint32	tmp8;


	tmp0 = *(const uint32 *)(&src[ byte - offset ]);

	/* 8word copy */
	for (; word > D_CPY_8WORD; word -= D_CPY_8WORD)
	{
		tmp1 = *(const uint32 *)(&src[ (byte - offset) + D_CPY_1WORD_SIZE ]);
		tmp2 = *(const uint32 *)(&src[ (byte - offset) + D_CPY_2WORD_SIZE ]);
		tmp3 = *(const uint32 *)(&src[ (byte - offset) + D_CPY_3WORD_SIZE ]);
		tmp4 = *(const uint32 *)(&src[ (byte - offset) + D_CPY_4WORD_SIZE ]);
		tmp5 = *(const uint32 *)(&src[ (byte - offset) + D_CPY_5WORD_SIZE ]);
		tmp6 = *(const uint32 *)(&src[ (byte - offset) + D_CPY_6WORD_SIZE ]);
		tmp7 = *(const uint32 *)(&src[ (byte - offset) + D_CPY_7WORD_SIZE ]);
		tmp8 = *(const uint32 *)(&src[ (byte - offset) + D_CPY_8WORD_SIZE ]);

		*(uint32*)(&dst[ byte                    ]) = D_CPY_WORD_1ST(offset, tmp0) | D_CPY_WORD_2ND(offset, tmp1);
		*(uint32*)(&dst[ byte + D_CPY_1WORD_SIZE ]) = D_CPY_WORD_1ST(offset, tmp1) | D_CPY_WORD_2ND(offset, tmp2);
		*(uint32*)(&dst[ byte + D_CPY_2WORD_SIZE ]) = D_CPY_WORD_1ST(offset, tmp2) | D_CPY_WORD_2ND(offset, tmp3);
		*(uint32*)(&dst[ byte + D_CPY_3WORD_SIZE ]) = D_CPY_WORD_1ST(offset, tmp3) | D_CPY_WORD_2ND(offset, tmp4);
		*(uint32*)(&dst[ byte + D_CPY_4WORD_SIZE ]) = D_CPY_WORD_1ST(offset, tmp4) | D_CPY_WORD_2ND(offset, tmp5);
		*(uint32*)(&dst[ byte + D_CPY_5WORD_SIZE ]) = D_CPY_WORD_1ST(offset, tmp5) | D_CPY_WORD_2ND(offset, tmp6);
		*(uint32*)(&dst[ byte + D_CPY_6WORD_SIZE ]) = D_CPY_WORD_1ST(offset, tmp6) | D_CPY_WORD_2ND(offset, tmp7);
		*(uint32*)(&dst[ byte + D_CPY_7WORD_SIZE ]) = D_CPY_WORD_1ST(offset, tmp7) | D_CPY_WORD_2ND(offset, tmp8);

		byte += D_CPY_8WORD_SIZE;
		tmp0  = tmp8;
	}

	/* 4word copy */
	if (word > D_CPY_4WORD)
	{
		tmp1 = *(const uint32 *)(&src[ (byte - offset) + D_CPY_1WORD_SIZE ]);
		tmp2 = *(const uint32 *)(&src[ (byte - offset) + D_CPY_2WORD_SIZE ]);
		tmp3 = *(const uint32 *)(&src[ (byte - offset) + D_CPY_3WORD_SIZE ]);
		tmp4 = *(const uint32 *)(&src[ (byte - offset) + D_CPY_4WORD_SIZE ]);

		*(uint32*)(&dst[ byte                    ]) = D_CPY_WORD_1ST(offset, tmp0) | D_CPY_WORD_2ND(offset, tmp1);
		*(uint32*)(&dst[ byte + D_CPY_1WORD_SIZE ]) = D_CPY_WORD_1ST(offset, tmp1) | D_CPY_WORD_2ND(offset, tmp2);
		*(uint32*)(&dst[ byte + D_CPY_2WORD_SIZE ]) = D_CPY_WORD_1ST(offset, tmp2) | D_CPY_WORD_2ND(offset, tmp3);
		*(uint32*)(&dst[ byte + D_CPY_3WORD_SIZE ]) = D_CPY_WORD_1ST(offset, tmp3) | D_CPY_WORD_2ND(offset, tmp4);

		byte += D_CPY_4WORD_SIZE;
		word -= D_CPY_4WORD;
		tmp0  = tmp4;
	}

	/* 2word copy */
	if (word > D_CPY_2WORD)
	{
		tmp1 = *(const uint32 *)(&src[ (byte - offset) + D_CPY_1WORD_SIZE ]);
		tmp2 = *(const uint32 *)(&src[ (byte - offset) + D_CPY_2WORD_SIZE ]);

		*(uint32*)(&dst[ byte                    ]) = D_CPY_WORD_1ST(offset, tmp0) | D_CPY_WORD_2ND(offset, tmp1);
		*(uint32*)(&dst[ byte + D_CPY_1WORD_SIZE ]) = D_CPY_WORD_1ST(offset, tmp1) | D_CPY_WORD_2ND(offset, tmp2);

		byte += D_CPY_2WORD_SIZE;
		word -= D_CPY_2WORD;
		tmp0  = tmp2;
	}

	/* 1word copy */
	if (word > D_CPY_1WORD)
	{
		tmp1 = *(const uint32 *)(&src[(byte - offset) + D_CPY_1WORD_SIZE ]);

		*(uint32*)(&dst[ byte                    ]) = D_CPY_WORD_1ST(offset, tmp0) | D_CPY_WORD_2ND(offset, tmp1);

		byte += D_CPY_1WORD_SIZE;
	}

	*cp_byte = byte;
}
/* ------------------------------------------------------------------------ */
/* #define LIB_STOP_SEC_CODE */
/* #include <LIB_MemMap.h> */
/* ------------------------------------------------------------------------ */
