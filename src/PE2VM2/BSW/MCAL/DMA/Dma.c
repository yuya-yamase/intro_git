/* Dma-r04-3000-0100-a-v01 */
/************************************************************************************************/
/*																								*/
/*		MCAL DMA Driver																			*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Dma.h"

#include	"Dma_engine.h"

#include	"reg_dma.h"

#include	"pil_dmac.h"
#include	"pil_dts.h"

#include	"Dma_Cfg.h"

/*==============================================================================================*/
/*	prototypes																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	constants																					*/
/*==============================================================================================*/
#define DMA_START_SEC_RODATA_CONST
#include "Dma_MemMap.h"

extern	const	Dma_UserConfigType	cstDma_UcfgData;

#define DMA_STOP_SEC_RODATA_CONST
#include "Dma_MemMap.h"
/*==============================================================================================*/
/*	variables																					*/
/*==============================================================================================*/
#define DMA_START_SEC_BSS_VAR_NO_INIT
#include "Dma_MemMap.h"

//extern Dma_ChannelDataType		stDma_Notification[];

#define DMA_STOP_SEC_BSS_VAR_NO_INIT
#include "Dma_MemMap.h"

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#define DMA_START_SEC_TEXT_CODE
#include "Dma_MemMap.h"
/*----------------------------------------------------------------------------------------------*/
/* API Functions                                                                                */
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/*	DMA Trans Enable with DMA Request Clear Function											*/
/*	return		: void																			*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_EnableTrans( U1 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	U1		t_u1ChannelID;				/* DMA Ch No */
	U1		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;
	
	if( t_u1DmaType == (U1)DMA_DTS )
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		Pil_Dts_EnableTrans( t_u1ChannelID );
	}
	else
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
		Pil_Dmac_EnableTrans( t_u1ChannelID, t_u1DmaType );
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Trans Disable Function																	*/
/*	return		: void																			*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_DisableTrans( U1 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	U1		t_u1ChannelID;				/* DTS  Ch No */
	U1		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (U1)DMA_DTS )
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		Pil_Dts_DisableTrans( t_u1ChannelID );
	}
	else
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
		Pil_Dmac_DisableTrans( t_u1ChannelID, t_u1DmaType );
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Trans Mode Set Function																	*/
/*	return		: void																			*/
/*	parameters	: ChannelDataID																	*/
/*				: TransSize (SIZE_1/SIZE_2/SIZE_4)												*/
/*				: DmaMode (0-2)																	*/
/*				: SrcAdr(Async) (Pointer to Source Adrress)										*/
/*				: DestAdr(Async) (Pointer to Destination Adrress)								*/
/*				: TransNum (Trans number)														*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_SetTransMode( U1 t_u1ChDataID, U1 t_u1TransSize, U1 t_u1DmaMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	U1		t_u1ChannelID;				/* DMA Ch No */
	U1		t_u1DmaType;				/* DMA Type */
	U1		t_u1DmaReqNum;				/* DMA Hardware Factors */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (U1)DMA_DTS )
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		Pil_Dts_SetTransMode( t_u1ChannelID, t_u1TransSize, t_u1DmaMode, t_pcvdSrcAdr, t_pcvdDestAdr, t_u2TransNum );
	}
	else
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
		t_u1DmaReqNum = (U1)(t_pcstChDataConfig->u2DmaReq & u2DMA_DMAC_GROUP_REQ_MASK);
		Pil_Dmac_SetTransMode( t_u1ChannelID, t_u1DmaType, t_u1TransSize, t_u1DmaMode, t_pcvdSrcAdr, t_pcvdDestAdr, t_u2TransNum, t_u1DmaReqNum );
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Trans Mode (Two Level Reload) Set Function												*/
/*	return		: void																			*/
/*	parameters	: ChannelDataID																	*/
/*				: TransSize (SIZE_1/SIZE_2/SIZE_4)												*/
/*				: DmaMode (3-5)																	*/
/*				: SrcAdr(Async) (Pointer to Source Adrress)										*/
/*				: DestAdr(Async) (Pointer to Destination Adrress)								*/
/*				: TransNum (Number of transfers to the second stage)							*/
/*				: AddrReloadCnt (Number of transfers until first reload(If not mode5,specify 0))*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_SetTransModeTwoStepReload( U1 t_u1ChDataID, U1 t_u1TransSize, U1 t_u1DmaMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum, U2 t_u2AddrReloadCnt )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	U1		t_u1ChannelID;				/* DMA Ch No */
	U1		t_u1DmaType;				/* DMA Type */
	U1		t_u1DmaReqNum;				/* DMA Hardware Factors */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (U1)DMA_DTS )
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		Pil_Dts_SetTransModeTwoStepReload( t_u1ChannelID, t_u1TransSize, t_u1DmaMode, t_pcvdSrcAdr, t_pcvdDestAdr, t_u2TransNum, t_u2AddrReloadCnt );
	}
	else
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
		t_u1DmaReqNum = (U1)(t_pcstChDataConfig->u2DmaReq & u2DMA_DMAC_GROUP_REQ_MASK);
		Pil_Dmac_SetTransModeTwoStepReload( t_u1ChannelID, t_u1DmaType, t_u1TransSize, t_u1DmaMode, t_pcvdSrcAdr, t_pcvdDestAdr, t_u2TransNum, t_u2AddrReloadCnt, t_u1DmaReqNum );
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Interrupt E/D Set Function																*/
/*	return		: void																			*/
/*	parameters	: ChannelDataID																	*/
/*				: HalfIe (ON/OFF)""																*/
/*				: EndIe (ON/OFF)""																*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_SetInterrupt( U1 t_u1ChDataID, U1 t_u1HalfIe, U1 t_u1EndIe )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	Dma_ChannelDataType*		t_pstChDataType;
	U1		t_u1ChannelID;				/* DMA Ch No */
	U1		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;
	t_pstChDataType = t_pcstChDataConfig->pstChDataType;
	
	if( t_u1DmaType == (U1)DMA_DTS )
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		
		DMA_ENTER_CRITICAL_SECTION();
		if( t_u1EndIe == (U1)DMA_ON )
		{
			if( t_pstChDataType->u1DmaNotificationRequest == (U1)DMA_OFF )
			{
				t_pstChDataType->u1DmaNotificationRequest = (U1)DMA_ON;
				Pil_Dts_ClearMatchStatus( t_u1ChannelID );	/* Clear interrupt request flag */
			}
		}
		else
		{
			t_pstChDataType->u1DmaNotificationRequest = (U1)DMA_OFF;
		}
		
		Pil_Dts_SetInterrupt( t_u1ChannelID, t_u1HalfIe, t_u1EndIe );
		DMA_EXIT_CRITICAL_SECTION();
	}
	else
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
		
		DMA_ENTER_CRITICAL_SECTION();
		if( t_u1EndIe == (U1)DMA_ON )
		{
			if( t_pstChDataType->u1DmaNotificationRequest == (U1)DMA_OFF )
			{
				t_pstChDataType->u1DmaNotificationRequest = (U1)DMA_ON;
				Pil_Dmac_ClearMatchStatus( t_u1ChannelID, t_u1DmaType );	/* Clear interrupt request flag */
			}
		}
		else
		{
			t_pstChDataType->u1DmaNotificationRequest = (U1)DMA_OFF;
		}

		Pil_Dmac_SetInterrupt( t_u1ChannelID, t_u1DmaType, t_u1EndIe );
		DMA_EXIT_CRITICAL_SECTION();
	}
	
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Destination Adrress Get Function														*/
/*	return		: Destination Address															*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
void*	Dma_GetDestinationAddress( U1 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	void*	t_pRet;
	U1		t_u1ChannelID;				/* DTS  Ch No */
	U1		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (U1)DMA_DTS )
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		t_pRet = Pil_Dts_GetDestinationAddress( t_u1ChannelID );
	}
	else
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
		t_pRet = Pil_Dmac_GetDestinationAddress( t_u1ChannelID, t_u1DmaType );
	}

	return ( t_pRet );
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Trans Count Get Function																*/
/*	return		: Trans Count																	*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
U2		Dma_GetTransCount( U1 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	U2		t_u2Ret;
	U1		t_u1ChannelID;				/* DTS  Ch No */
	U1		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (U1)DMA_DTS )
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		t_u2Ret = Pil_Dts_GetTransCount( t_u1ChannelID );
	}
	else
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
		t_u2Ret = Pil_Dmac_GetTransCount( t_u1ChannelID, t_u1DmaType );
	}

	return ( t_u2Ret );
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Trans Count Reset Function																*/
/*	return		: none																			*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_ResetTransCount( U1 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	U1		t_u1ChannelID;				/* DMA Ch No */
	U1		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (U1)DMA_DTS )
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		Pil_Dts_ResetTransCount( t_u1ChannelID );
	}
	else
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
		Pil_Dmac_ResetTransCount( t_u1ChannelID, t_u1DmaType );
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Trans Status Get Function																*/
/*	return		: Trans Status ( =0:IDLE / !=0:BUSY)											*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
U1		Dma_GetTransStatus( U1 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	U1		t_u1Ret;
	U1		t_u1ChannelID;				/* DMA Ch No */
	U1		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (U1)DMA_DTS )
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		t_u1Ret = Pil_Dts_GetTransStatus( t_u1ChannelID );
	}
	else
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
		t_u1Ret = Pil_Dmac_GetTransStatus( t_u1ChannelID, t_u1DmaType );
	}

	return ( t_u1Ret );
}


/*----------------------------------------------------------------------------------------------*/
/*	DMA Error Check Function																	*/
/*	return		: Error Status																	*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
ZORN	Dma_CheckDmaError( U1 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	ZORN	t_udRet;
	U1		t_u1ChannelID;				/* DMA Ch No */
	U1		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (U1)DMA_DTS )
	{
		t_udRet = Pil_Dts_CheckDmaError();
	}
	else
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
		t_udRet = Pil_Dmac_CheckDmaError( t_u1ChannelID, t_u1DmaType );
	}

	return ( t_udRet );
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Error Status Clear Function																*/
/*	return		: none																			*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_ClearDmaError( U1 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	U1		t_u1ChannelID;				/* DMA Ch No */
	U1		t_u1DmaType;				/* DMA Type */
	U1		t_u1DmaHwCh;				/* DMA HwCh */
	U1		t_u1ChDataNum;				/* Number of DMA logical CH numbers */
	U1		i;

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;
	t_u1ChDataNum = cstDma_UcfgData.u1ChDataNum;

	if( t_u1DmaType == (U1)DMA_DTS )
	{
		/* If an error occurs in multiple CHs, the transfer error flag can be cleared by clearing all CHs. */
		for( i = (U1)0; i < (U1)t_u1ChDataNum; i++ )
		{
			t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[(U1)i]);
			t_u1DmaType = t_pcstChDataConfig->u1DmaType;
			if( t_u1DmaType == (U1)DMA_DTS )
			{
				t_u1DmaHwCh = (U1)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
				Pil_Dts_ClearDmaError( t_u1DmaHwCh );
			}
		}
	}
	else
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
		Pil_Dmac_ClearDmaError( t_u1ChannelID, t_u1DmaType );
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Reload Status Get Function																*/
/*	return		: void																			*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
U1	Dma_GetReloadStatus( U1 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	U1		t_u1ChannelID;				/* DMA Ch No */
	U1		t_u1DmaType;				/* DMA Type */
	U1		t_u1dRet;

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	t_u1dRet = Pil_Dmac_GetReloadStatus( t_u1ChannelID, t_u1DmaType );

	return ( t_u1dRet );
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Reload Status Clear Function															*/
/*	return		: void																			*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_ClearReloadStatus( U1 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	U1		t_u1ChannelID;				/* DMA Ch No */
	U1		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	Pil_Dmac_ClearReloadStatus( t_u1ChannelID, t_u1DmaType );
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Transfer completed state Function														*/
/*	return		: Transfer end state (FALSE:in progress / TRUE:transfer completed)				*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
U1		Dma_IsTransferCompleted( U1 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	U1		t_u1Ret;
	U1		t_u1ChannelID;				/* DMA Ch No */
	U1		t_u1DmaType;				/* DMA Type */

	/* GET CH INFORMATION FROM DMA LOGIC CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (U1)DMA_DTS )
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		t_u1Ret = Pil_Dts_IsTransferCompleted( t_u1ChannelID );
	}
	else
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
		t_u1Ret = Pil_Dmac_IsTransferCompleted( t_u1ChannelID, t_u1DmaType );
	}

	return ( t_u1Ret );
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Transfer end flag Clear Function														*/
/*	return		: void																			*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_ClearTransferEndFlag( U1 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	U1		t_u1ChannelID;				/* DMA Ch No */
	U1		t_u1DmaType;				/* DMA Type */

	/* GET CH INFORMATION FROM DMA LOGIC CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;
	
	if( t_u1DmaType == (U1)DMA_DTS )
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		Pil_Dts_ClearMatchStatus( t_u1ChannelID );
	}
	else
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
		Pil_Dmac_ClearMatchStatus( t_u1ChannelID, t_u1DmaType );
	}
}

/*----------------------------------------------------------------------------------------------*/
/* Scheduled / Event Functions																	*/
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/*	Initialization Function																		*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_Init( void )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	U2		t_u2DmaReqNum;				/* DMA Hardware Factors */
	U1		t_u1ChannelID;				/* DMA Ch No */
	U1		t_u1DmaType;				/* DMA Type */
	U1		t_u1PriLevel;				/* DMA Priority */
	U1		t_u1ChDataNum;				/* Number of DMA logical CH numbers */
	S4		i;

	t_u1ChDataNum = cstDma_UcfgData.u1ChDataNum;			/* Number of DMA logical CH numbers */

	/* DTS/sDMAC */
	/*	Pil_Dts_SetInitPriorityAllCh()";"*/	/* DTS Priority Settings *//* Set priority only for the CH to be used. */
	Pil_Dts_EnableIntcInterrupt();	/* Allow DTS interrupt mask set */

	for( i = (S4)0; i < (S4)t_u1ChDataNum; i++ )
	{
		/* Get CH information from DMA logic CH */
		t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[i]);
		t_u1DmaType = t_pcstChDataConfig->u1DmaType;
		/* Ram Init */
		t_pcstChDataConfig->pstChDataType->u1DmaNotificationRequest = (U1)DMA_OFF;

		/* Get DMA factor from DMA logic CH */
		if(t_u1DmaType == (U1)DMA_DTS)
		{
			t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
			t_u2DmaReqNum = t_pcstChDataConfig->u2DmaReq;

			Pil_Dts_SetTransReqGroup(t_u2DmaReqNum);

			/*Pil_Dts_ClearRam( t_u1ChannelID )";"*/				/* DTS RAM CLEAR *//* Comment it out, hoping to clear it with a flash option byte. */
			t_u1PriLevel = t_pcstChDataConfig->u1PriLevel;
			Pil_Dts_SetPriority( t_u1ChannelID, t_u1PriLevel );		/* Prioritize(Channel) */
		}
		else
		{
			t_u2DmaReqNum = t_pcstChDataConfig->u2DmaReq;

			Pil_Dmac_SetTransReqGroup( t_u2DmaReqNum, t_u1DmaType );
			/*Pil_Dmac_ClearRam()";"*/								/* sDMAC RAM CLEAR *//* Comment it out, hoping to clear it with a flash option byte */
		}
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	De-Initialization Function																	*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_DeInit( void )
{
	/* All DMA transfer requests disabled */
	/* DTS */
	Pil_Dts_DisableTransAll();

	/* sDMAC */
	Pil_Dmac_DisableTransAll();
	
	/* Set DTS interrupts to disabled. */
	Pil_Dts_DisableIntcInterrupt();

}

#if ( DMA_CFG_REG_CHK == STD_ON ) 
/*----------------------------------------------------------------------------------------------*/
/*	Regchk Function																				*/
/*	return		: Check Result																	*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
U4	Dma_Regchk_All( void )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	S4		i;
	U1		t_u1DmaType;				/* DMA Type */
	U1		t_u1ChDataNum;				/* Number of DMA logical CH numbers */
	U4		t_u4RegError; 				/* Register error status */

	t_u1ChDataNum = cstDma_UcfgData.u1ChDataNum;			/* Number of DMA logical CH numbers */

#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
	/* Check DMAC Redundant Channel Select Register */ 
	t_u4RegError = Pil_Dmac_CheckRCHSReg();

	/* Check DTS INTC Register for interrupt enabling */ 
	t_u4RegError |= Pil_Dts_CheckIntcReg();	
#else
	t_u4RegError = Pil_Dts_CheckIntcReg();	
#endif
	for( i = (S4)0; (i < (S4)t_u1ChDataNum); i++ )
	{
		/* Get CH information from DMA logic CH */
		t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[i]);
		t_u1DmaType = t_pcstChDataConfig->u1DmaType;

		/* Check DMA request group for each DMA logic CH */
		if(t_u1DmaType == (U1)DMA_DTS)
		{
			t_u4RegError |= Pil_Dts_CheckTransReqGroup(t_pcstChDataConfig->u2DmaReq);
		}
		else
		{
			t_u4RegError |= Pil_Dmac_CheckTransReqGroup( t_pcstChDataConfig->u2DmaReq, t_u1DmaType );
		}
	}

	return(t_u4RegError);
}
#endif

/*----------------------------------------------------------------------------------------------*/
/*	Interrupt Function																			*/
/*	return		: none																			*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_Interrupt( U1 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;

	/* GET CH INFORMATION FROM DMA LOGIC CH */
	t_pcstChDataConfig	= &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);

	if (t_pcstChDataConfig->pvdNotification != NULL_PTR)
	{
		(t_pcstChDataConfig->pvdNotification)();
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Set Master Channel Function																*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_SetMasterCh( void )
{
	/* Set SPID on all channels with the idea of functional safety. */
	Pil_Dts_SetMasterCh();	/* DTS Master CH Settings */
}

/*==============================================================================================*/
/*	Local Functions																				*/
/*==============================================================================================*/

#define DMA_STOP_SEC_TEXT_CODE
#include "Dma_MemMap.h"
/*-- End Of File -------------------------------------------------------------------------------*/
