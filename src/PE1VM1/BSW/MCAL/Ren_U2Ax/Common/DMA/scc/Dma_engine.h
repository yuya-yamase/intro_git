/************************************************************************************************/
/*																								*/
/*		Common definitions needed to build engine DMA modules in a standard environment							*/
/*																								*/
/************************************************************************************************/

#ifndef DMA_ENGINE_H
#define DMA_ENGINE_H

/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include "reg_dma.h"

/*==============================================================================================*/
/* defines / data types / structs / unions / macros												*/
/*==============================================================================================*/
/* Excerpt from Std_Lib.h */
extern	unsigned int	__SCH1R(unsigned int val);

/* Excerpt from BswLib.h */
#define		Bswlib_SearchOneFromRight(data)		((uint8)__SCH1R(data) - (uint8)1U)

extern void __SYNCP(void);
/************************************************************************************************/
/*	Service name	:	Sync_Pipeline															*/
/*	Reentrancy		:	Concurrency safe														*/
/*	Parameters(in)	:	Register																*/
/*	Return value	:	none																	*/
/*	Caveat			:	Only uint8, uint16 and uint32 type registers are supported. 			*/
/*						No other use allowed.													*/
/************************************************************************************************/
#define		Bswlib_Sync_Pipeline( data )														\
	do																							\
	{																							\
		if(sizeof(data) != 1){																	\
			if(sizeof(data) != 2){																\
				volatile	uint32	t_u4BswLibDummy;											\
				t_u4BswLibDummy = (data);														\
			}else{																				\
				volatile	uint16	t_u2BswLibDummy;											\
				t_u2BswLibDummy = (data);														\
			}																					\
		}else{																					\
			volatile	uint8	t_u1BswLibDummy;												\
			t_u1BswLibDummy = (data);															\
		}																						\
		__SYNCP();																				\
	}	while(0)

/************************************************************************************************/
/*	Service name	:	Sync_Pipeline_2															*/
/*	Reentrancy		:	Concurrency safe														*/
/*	Parameters(in)	:	Register																*/
/*	Return value	:	none																	*/
/*	Caveat			:	Only uint16-type registers are supported. No other use allowed.			*/
/************************************************************************************************/
#define		Bswlib_Sync_Pipeline_2( data )														\
	do																							\
	{																							\
		volatile	uint16	t_u2BswLibDummy;													\
		t_u2BswLibDummy = (data);																\
		__SYNCP();																				\
	}	while(0)

/************************************************************************************************/
/*	Service name	:	Sync_Pipeline_4															*/
/*	Reentrancy		:	Concurrency safe														*/
/*	Parameters(in)	:	Register																*/
/*	Return value	:	none																	*/
/*	Caveat			:	Only uint32-type registers are supported. No other use allowed.			*/
/************************************************************************************************/
#define		Bswlib_Sync_Pipeline_4( data )														\
	do																							\
	{																							\
		volatile	uint32	t_u4BswLibDummy;													\
		t_u4BswLibDummy = (data);																\
		__SYNCP();																				\
	}	while(0)

#endif	/* DMA_ENGINE_H */
/*-- End Of File -------------------------------------------------------------------------------*/
