/* Dma-r04-3000-0200-b-v00 */
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

/*==============================================================================================*/
/*	variables																					*/
/*==============================================================================================*/

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
void	Dma_EnableTrans( uint8 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	uint8		t_u1ChannelID;				/* DMA Ch No */
	uint8		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;
	
	if( t_u1DmaType == (uint8)DMA_DTS )
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		Pil_Dts_EnableTrans( t_u1ChannelID );
	}
	else
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh);
		Pil_Dmac_EnableTrans( t_u1ChannelID, t_u1DmaType );
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Trans Disable Function																	*/
/*	return		: void																			*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_DisableTrans( uint8 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	uint8		t_u1ChannelID;				/* DTS  Ch No */
	uint8		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (uint8)DMA_DTS )
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		Pil_Dts_DisableTrans( t_u1ChannelID );
	}
	else
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh);
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
void	Dma_SetTransMode( uint8 t_u1ChDataID, uint8 t_u1TransSize, uint8 t_u1DmaMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, uint16 t_u2TransNum )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	uint8		t_u1ChannelID;				/* DMA Ch No */
	uint8		t_u1DmaType;				/* DMA Type */
	uint8		t_u1DmaReqNum;				/* DMA Hardware Factors */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (uint8)DMA_DTS )
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		Pil_Dts_SetTransMode( t_u1ChannelID, t_u1TransSize, t_u1DmaMode, t_pcvdSrcAdr, t_pcvdDestAdr, t_u2TransNum );
	}
	else
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh);
		t_u1DmaReqNum = (uint8)(t_pcstChDataConfig->u2DmaReq & u2DMA_DMAC_GROUP_REQ_MASK);
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
void	Dma_SetTransModeTwoStepReload( uint8 t_u1ChDataID, uint8 t_u1TransSize, uint8 t_u1DmaMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, uint16 t_u2TransNum, uint16 t_u2AddrReloadCnt )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	uint8		t_u1ChannelID;				/* DMA Ch No */
	uint8		t_u1DmaType;				/* DMA Type */
	uint8		t_u1DmaReqNum;				/* DMA Hardware Factors */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (uint8)DMA_DTS )
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		Pil_Dts_SetTransModeTwoStepReload( t_u1ChannelID, t_u1TransSize, t_u1DmaMode, t_pcvdSrcAdr, t_pcvdDestAdr, t_u2TransNum, t_u2AddrReloadCnt );
	}
	else
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh);
		t_u1DmaReqNum = (uint8)(t_pcstChDataConfig->u2DmaReq & u2DMA_DMAC_GROUP_REQ_MASK);
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
void	Dma_SetInterrupt( uint8 t_u1ChDataID, uint8 t_u1HalfIe, uint8 t_u1EndIe )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	Dma_ChannelDataType*		t_pstChDataType;
	uint8		t_u1ChannelID;				/* DMA Ch No */
	uint8		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;
	t_pstChDataType = t_pcstChDataConfig->pstChDataType;
	
	if( t_u1DmaType == (uint8)DMA_DTS )
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		
		DMA_ENTER_CRITICAL_SECTION();
		if( t_u1EndIe == (uint8)DMA_ON )
		{
			if( t_pstChDataType->u1DmaNotificationRequest == (uint8)DMA_OFF )
			{
				t_pstChDataType->u1DmaNotificationRequest = (uint8)DMA_ON;
				Pil_Dts_ClearMatchStatus( t_u1ChannelID );	/* Clear interrupt request flag */
			}
		}
		else
		{
			t_pstChDataType->u1DmaNotificationRequest = (uint8)DMA_OFF;
		}
		
		Pil_Dts_SetInterrupt( t_u1ChannelID, t_u1HalfIe, t_u1EndIe );
		DMA_EXIT_CRITICAL_SECTION();
	}
	else
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh);
		
		DMA_ENTER_CRITICAL_SECTION();
		if( t_u1EndIe == (uint8)DMA_ON )
		{
			if( t_pstChDataType->u1DmaNotificationRequest == (uint8)DMA_OFF )
			{
				t_pstChDataType->u1DmaNotificationRequest = (uint8)DMA_ON;
				Pil_Dmac_ClearMatchStatus( t_u1ChannelID, t_u1DmaType );	/* Clear interrupt request flag */
			}
		}
		else
		{
			t_pstChDataType->u1DmaNotificationRequest = (uint8)DMA_OFF;
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
void*	Dma_GetDestinationAddress( uint8 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	void*	t_pRet;
	uint8		t_u1ChannelID;				/* DTS  Ch No */
	uint8		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (uint8)DMA_DTS )
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		t_pRet = Pil_Dts_GetDestinationAddress( t_u1ChannelID );
	}
	else
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh);
		t_pRet = Pil_Dmac_GetDestinationAddress( t_u1ChannelID, t_u1DmaType );
	}

	return ( t_pRet );
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Trans Count Get Function																*/
/*	return		: Trans Count																	*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
uint16		Dma_GetTransCount( uint8 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	uint16		t_u2Ret;
	uint8		t_u1ChannelID;				/* DTS  Ch No */
	uint8		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (uint8)DMA_DTS )
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		t_u2Ret = Pil_Dts_GetTransCount( t_u1ChannelID );
	}
	else
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh);
		t_u2Ret = Pil_Dmac_GetTransCount( t_u1ChannelID, t_u1DmaType );
	}

	return ( t_u2Ret );
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Trans Count Reset Function																*/
/*	return		: none																			*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_ResetTransCount( uint8 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	uint8		t_u1ChannelID;				/* DMA Ch No */
	uint8		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (uint8)DMA_DTS )
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		Pil_Dts_ResetTransCount( t_u1ChannelID );
	}
	else
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh);
		Pil_Dmac_ResetTransCount( t_u1ChannelID, t_u1DmaType );
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Trans Status Get Function																*/
/*	return		: Trans Status ( =0:IDLE / !=0:BUSY)											*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
uint8		Dma_GetTransStatus( uint8 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	uint8		t_u1Ret;
	uint8		t_u1ChannelID;				/* DMA Ch No */
	uint8		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (uint8)DMA_DTS )
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		t_u1Ret = Pil_Dts_GetTransStatus( t_u1ChannelID );
	}
	else
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh);
		t_u1Ret = Pil_Dmac_GetTransStatus( t_u1ChannelID, t_u1DmaType );
	}

	return ( t_u1Ret );
}


/*----------------------------------------------------------------------------------------------*/
/*	DMA Error Check Function																	*/
/*	return		: Error Status																	*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
sint32	Dma_CheckDmaError( uint8 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	sint32	t_udRet;
	uint8		t_u1ChannelID;				/* DMA Ch No */
	uint8		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (uint8)DMA_DTS )
	{
		t_udRet = Pil_Dts_CheckDmaError();
	}
	else
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh);
		t_udRet = Pil_Dmac_CheckDmaError( t_u1ChannelID, t_u1DmaType );
	}

	return ( t_udRet );
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Error Status Clear Function																*/
/*	return		: none																			*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_ClearDmaError( uint8 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	uint8		t_u1ChannelID;				/* DMA Ch No */
	uint8		t_u1DmaType;				/* DMA Type */
	uint8		t_u1DmaHwCh;				/* DMA HwCh */
	uint8		t_u1ChDataNum;				/* Number of DMA logical CH numbers */
	uint8		i;

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;
	t_u1ChDataNum = cstDma_UcfgData.u1ChDataNum;

	if( t_u1DmaType == (uint8)DMA_DTS )
	{
		/* If an error occurs in multiple CHs, the transfer error flag can be cleared by clearing all CHs. */
		for( i = (uint8)0; i < (uint8)t_u1ChDataNum; i++ )
		{
			t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[(uint8)i]);
			t_u1DmaType = t_pcstChDataConfig->u1DmaType;
			if( t_u1DmaType == (uint8)DMA_DTS )
			{
				t_u1DmaHwCh = (uint8)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
				Pil_Dts_ClearDmaError( t_u1DmaHwCh );
			}
		}
	}
	else
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh);
		Pil_Dmac_ClearDmaError( t_u1ChannelID, t_u1DmaType );
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Reload Status Get Function																*/
/*	return		: void																			*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
uint8	Dma_GetReloadStatus( uint8 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	uint8		t_u1ChannelID;				/* DMA Ch No */
	uint8		t_u1DmaType;				/* DMA Type */
	uint8		t_u1dRet;

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	t_u1dRet = Pil_Dmac_GetReloadStatus( t_u1ChannelID, t_u1DmaType );

	return ( t_u1dRet );
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Reload Status Clear Function															*/
/*	return		: void																			*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_ClearReloadStatus( uint8 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	uint8		t_u1ChannelID;				/* DMA Ch No */
	uint8		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	Pil_Dmac_ClearReloadStatus( t_u1ChannelID, t_u1DmaType );
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Transfer completed state Function														*/
/*	return		: Transfer end state (FALSE:in progress / TRUE:transfer completed)				*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
uint8		Dma_IsTransferCompleted( uint8 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	uint8		t_u1Ret;
	uint8		t_u1ChannelID;				/* DMA Ch No */
	uint8		t_u1DmaType;				/* DMA Type */

	/* GET CH INFORMATION FROM DMA LOGIC CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType == (uint8)DMA_DTS )
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		t_u1Ret = Pil_Dts_IsTransferCompleted( t_u1ChannelID );
	}
	else
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh);
		t_u1Ret = Pil_Dmac_IsTransferCompleted( t_u1ChannelID, t_u1DmaType );
	}

	return ( t_u1Ret );
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Transfer end flag Clear Function														*/
/*	return		: void																			*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_ClearTransferEndFlag( uint8 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	uint8		t_u1ChannelID;				/* DMA Ch No */
	uint8		t_u1DmaType;				/* DMA Type */

	/* GET CH INFORMATION FROM DMA LOGIC CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;
	
	if( t_u1DmaType == (uint8)DMA_DTS )
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
		Pil_Dts_ClearMatchStatus( t_u1ChannelID );
	}
	else
	{
		t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh);
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
#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
	uint16		t_u2DmaReqNum;				/* DMA Hardware Factors */
	uint8		t_u1ChannelID;				/* DMA Ch No */
	uint8		t_u1DmaType;				/* DMA Type */
	uint8		t_u1PriLevel;				/* DMA Priority */
#endif
	uint8		t_u1ChDataNum;				/* Number of DMA logical CH numbers */
	sint32		i;

	t_u1ChDataNum = cstDma_UcfgData.u1ChDataNum;			/* Number of DMA logical CH numbers */

	/* DTS/sDMAC */
	/*	Pil_Dts_SetInitPriorityAllCh()";"*/	/* DTS Priority Settings *//* Set priority only for the CH to be used. */
#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
	Pil_Dts_EnableIntcInterrupt();	/* Allow DTS interrupt mask set */
#endif

	for( i = (sint32)0; i < (sint32)t_u1ChDataNum; i++ )
	{
		/* Get CH information from DMA logic CH */
		t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[i]);
#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
		t_u1DmaType = t_pcstChDataConfig->u1DmaType;
#endif
		/* Ram Init */
		t_pcstChDataConfig->pstChDataType->u1DmaNotificationRequest = (uint8)DMA_OFF;

#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
		/* Get DMA factor from DMA logic CH */
		if(t_u1DmaType == (uint8)DMA_DTS)
		{
			t_u1ChannelID = (uint8)(t_pcstChDataConfig->u2HwCh & u2DMA_DTS_GROUP_REQ_MASK);
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
#endif
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
#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
	Pil_Dts_DisableTransAll();
#endif

	/* sDMAC */
#if (( DMA_CFG_DMA0_ACCESS == STD_ON ) || ( DMA_CFG_DMA1_ACCESS == STD_ON ))
	Pil_Dmac_DisableTransAll();
#endif
	
	/* Set DTS interrupts to disabled. */
#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
	Pil_Dts_DisableIntcInterrupt();
#endif

}

#if ( ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON ) \
  ||  ( DMA_CFG_DMA0_ACCESS == STD_ON ) \
  ||  ( DMA_CFG_DMA1_ACCESS == STD_ON ) )
#if ( DMA_CFG_REG_CHK == STD_ON )
/*----------------------------------------------------------------------------------------------*/
/*	Regchk Function																				*/
/*	return		: Check Result																	*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
uint32	Dma_Regchk_All( void )
{
#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	sint32		i;
	uint8		t_u1DmaType;				/* DMA Type */
	uint8		t_u1ChDataNum;				/* Number of DMA logical CH numbers */
#endif
	uint32		t_u4RegError; 				/* Register error status */

	t_u4RegError = DMA_REGCHK_OK + DMA_REGCHK_RESULT_DUMMY_BIT;

#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
	t_u1ChDataNum = cstDma_UcfgData.u1ChDataNum;			/* Number of DMA logical CH numbers */

#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
	/* Check DMAC Redundant Channel Select Register */ 
	t_u4RegError |= Pil_Dmac_CheckRCHSReg();
#endif
	/* Check DTS INTC Register for interrupt enabling */ 
	t_u4RegError |= Pil_Dts_CheckIntcReg();	

	for( i = (sint32)0; (i < (sint32)t_u1ChDataNum); i++ )
	{
		/* Get CH information from DMA logic CH */
		t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[i]);
		t_u1DmaType = t_pcstChDataConfig->u1DmaType;

		/* Check DMA request group for each DMA logic CH */
		if(t_u1DmaType == (uint8)DMA_DTS)
		{
			t_u4RegError |= Pil_Dts_CheckTransReqGroup(t_pcstChDataConfig->u2DmaReq);
		}
		else
		{
			t_u4RegError |= Pil_Dmac_CheckTransReqGroup( t_pcstChDataConfig->u2DmaReq, t_u1DmaType );
		}
	}
	/* Check DTS SPID */
	t_u4RegError |= Pil_Dts_CheckReg_ASIL();
#endif

#if (( DMA_CFG_DMA0_ACCESS == STD_ON ) || ( DMA_CFG_DMA1_ACCESS == STD_ON ))
	/* Check DMAC SPID */ 
	t_u4RegError |= Pil_Dmac_CheckReg_ASIL();
#endif

	t_u4RegError &= ~DMA_REGCHK_RESULT_DUMMY_BIT;

	return(t_u4RegError);
}
#endif
#endif

/*----------------------------------------------------------------------------------------------*/
/*	Interrupt Function																			*/
/*	return		: none																			*/
/*	parameters	: ChannelDataID																	*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_Interrupt( uint8 t_u1ChDataID )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;

	/* GET CH INFORMATION FROM DMA LOGIC CH */
	t_pcstChDataConfig	= &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);

	if (t_pcstChDataConfig->pvdNotification != NULL_PTR)
	{
		(t_pcstChDataConfig->pvdNotification)();
	}
}

#if ( ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON ) \
  ||  ( DMA_CFG_DMA0_ACCESS == STD_ON ) \
  ||  ( DMA_CFG_DMA1_ACCESS == STD_ON ) )
/*----------------------------------------------------------------------------------------------*/
/*	DMA Set Master Channel Function																*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_SetMasterCh( void )
{
	/* Set SPID on all channels with the idea of functional safety. */
#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
	Pil_Dts_SetMasterCh();	/* DTS Master CH Settings */
#endif

#if (( DMA_CFG_DMA0_ACCESS == STD_ON ) || ( DMA_CFG_DMA1_ACCESS == STD_ON ))
	Pil_Dmac_SetSpidAllCh();  /* To set SPIDs for DMAC channels */
#endif
}
#endif

/*==============================================================================================*/
/*	Local Functions																				*/
/*==============================================================================================*/

#define DMA_STOP_SEC_TEXT_CODE
#include "Dma_MemMap.h"
/*-- End Of File -------------------------------------------------------------------------------*/
