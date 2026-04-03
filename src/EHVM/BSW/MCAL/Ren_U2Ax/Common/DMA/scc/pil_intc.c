/* pil_intc_r04-3000-0100-a-v00 */
/************************************************************************************************/
/*																								*/
/*		PIL INTC																				*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Dma.h"
#include	"Dma_engine.h"

#include	"pil_intc.h"	/* own-header */

/*==============================================================================================*/
/*	prototypes																					*/
/*==============================================================================================*/
static	void	Pil_Intc_SetEimk( uint16 t_u2IntcIntNo, uint8 t_u1IntMask);

/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/


/*==============================================================================================*/
/*	constants																					*/
/*==============================================================================================*/
#define DMA_START_SEC_RODATA_CONST
#include "Dma_MemMap.h"
#define DMA_STOP_SEC_RODATA_CONST
#include "Dma_MemMap.h"

/*==============================================================================================*/
/*	variables																					*/
/*==============================================================================================*/
#define DMA_START_SEC_BSS_VAR_NO_INIT
#include "Dma_MemMap.h"
#define DMA_STOP_SEC_BSS_VAR_NO_INIT
#include "Dma_MemMap.h"

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#define DMA_START_SEC_TEXT_CODE
#include "Dma_MemMap.h"

/*----------------------------------------------------------------------------------------------*/
/* API Functions																				*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/*	Interrupt Set Function																		*/
/*	return		: none																			*/
/*	parameters	: IntcChannel(32-1023)															*/
/*				: Ie (ON:Interrupt Enable / OFF:Interrupt Disable)								*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Intc2_SetInterrupt( uint16 t_u2IntcChannel, uint8 t_u1Ie )
{
	uint8		t_u1IntMask;

	if(t_u1Ie == (uint8)DMA_ON)
	{
		t_u1IntMask = (uint8)INTC_EIC_EIMK * (uint8)INTC_EIC_EIMK_ENABLE;				/* Interrupt mask (EIMK) is OFF when interrupts are enabled */
	}
	else
	{
		t_u1IntMask = (uint8)INTC_EIC_EIMK * (uint8)INTC_EIC_EIMK_DISABLE;			/* Interrupt mask (EIMK) is ON when interrupts are disabled */
	}

	Pil_Intc_SetEimk( t_u2IntcChannel, t_u1IntMask);
}

#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
#if ( DMA_CFG_REG_CHK == STD_ON )
/*----------------------------------------------------------------------------------------------*/
/*	Interrupt Enable/Disable Status Get Function												*/
/*	return		: Interrupt Enable or Disable (ON:Enable, OFF:Disable)							*/
/*	parameters	: IntcChannel (32-1023)															*/
/*----------------------------------------------------------------------------------------------*/
uint8	Pil_Intc2_GetInterrupt( uint16 t_u2IntcChannel )
{
	uint16			t_u2IntEimk;
	uint8			t_u1Result;

	t_u2IntEimk = (uint16)(Reg_PIL_INTC2.unEIC[ t_u2IntcChannel ].u2Data & (uint16)INTC_EIC_EIMK);

	if( t_u2IntEimk == (uint16)INTC_EIC_EIMK_ENABLE )
	{
		t_u1Result = (uint8)DMA_ON;	/* interrupts are enabled is ON */
	}
	else
	{
		t_u1Result = (uint8)DMA_OFF;	/* interrupts are disabled is OFF */
	}

	return ( t_u1Result );
}
#endif
#endif

/*==============================================================================================*/
/*	Local Functions																				*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/*	Set Interrupt Mask Bit Function																*/
/*	return		: none																			*/
/*	parameters	: IntcChannel (0-1023)															*/
/*				: IntMask (0x00:Enable  / 0x80:Disable)											*/
/*----------------------------------------------------------------------------------------------*/
static	void	Pil_Intc_SetEimk( uint16 t_u2IntcIntNo, uint8 t_u1IntMask)
{
	uint8		t_u1EIC;

	DMA_ENTER_CRITICAL_SECTION();

	t_u1EIC = Reg_PIL_INTC2.unEIC[ t_u2IntcIntNo ].u1Data[0];				/* Get EIC byte 0 (0-7bit) */

	if( (t_u1EIC & (uint8)INTC_EIC_EIMK) != t_u1IntMask )					/* Request and EIMK have different values */
	{
		t_u1EIC = ((t_u1EIC & (uint8)~(uint8)INTC_EIC_EIMK) | t_u1IntMask);	/* Set t_u1IntMask to EIMK (position 7th bit) */
	
		Reg_PIL_INTC2.unEIC[ t_u2IntcIntNo ].u1Data[0] = t_u1EIC;
		Bswlib_Sync_Pipeline_2( Reg_PIL_INTC2.unEIC[ t_u2IntcIntNo ].u2Data );
	}
	
	DMA_EXIT_CRITICAL_SECTION();

	
}

#define DMA_STOP_SEC_TEXT_CODE
#include "Dma_MemMap.h"
/*-- End Of File -------------------------------------------------------------------------------*/
