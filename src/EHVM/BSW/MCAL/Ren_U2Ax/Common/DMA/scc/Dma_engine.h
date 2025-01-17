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
#define		Bswlib_SearchOneFromRight(data)		((U1)__SCH1R(data) - (U1)1U)

extern void __SYNCP(void);
/************************************************************************************************/
/*	Service name	:	Sync_Pipeline															*/
/*	Reentrancy		:	Concurrency safe														*/
/*	Parameters(in)	:	Register																*/
/*	Return value	:	none																	*/
/*	Caveat			:	Only U1, U2 and U4 type registers are supported. No other use allowed.					*/
/************************************************************************************************/
#define		Bswlib_Sync_Pipeline( data )														\
	do																							\
	{																							\
		if(sizeof(data) != 1){																	\
			if(sizeof(data) != 2){																\
				volatile	U4	t_u4BswLibDummy;												\
				t_u4BswLibDummy = (data);														\
			}else{																				\
				volatile	U2	t_u2BswLibDummy;												\
				t_u2BswLibDummy = (data);														\
			}																					\
		}else{																					\
			volatile	U1	t_u1BswLibDummy;													\
			t_u1BswLibDummy = (data);															\
		}																						\
		__SYNCP();																				\
	}	while(0)

/************************************************************************************************/
/*	Service name	:	Sync_Pipeline_2															*/
/*	Reentrancy		:	Concurrency safe														*/
/*	Parameters(in)	:	Register																*/
/*	Return value	:	none																	*/
/*	Caveat			:	Only U2-type registers are supported. No other use allowed.							*/
/************************************************************************************************/
#define		Bswlib_Sync_Pipeline_2( data )														\
	do																							\
	{																							\
		volatile	U2	t_u2BswLibDummy;														\
		t_u2BswLibDummy = (data);																\
		__SYNCP();																				\
	}	while(0)

/************************************************************************************************/
/*	Service name	:	Sync_Pipeline_4															*/
/*	Reentrancy		:	Concurrency safe														*/
/*	Parameters(in)	:	Register																*/
/*	Return value	:	none																	*/
/*	Caveat			:	Only U4-type registers are supported. No other use allowed.							*/
/************************************************************************************************/
#define		Bswlib_Sync_Pipeline_4( data )														\
	do																							\
	{																							\
		volatile	U4	t_u4BswLibDummy;														\
		t_u4BswLibDummy = (data);																\
		__SYNCP();																				\
	}	while(0)

#endif	/* DMA_ENGINE_H */
/*-- End Of File -------------------------------------------------------------------------------*/
