/* Dma-rA4-3000-0100-a-v01 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/U2A : DMA Desc Extension Interface                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Dma.h"
#include    "Dma_Desc.h"
#include    "pil_dmac_desc.h"

/*==============================================================================================*/
/*	prototypes																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	constants																					*/
/*==============================================================================================*/
extern	const	Dma_UserConfigType	cstDma_UcfgData;

/*==============================================================================================*/
/*	variables																					*/
/*==============================================================================================*/
/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#pragma ghs section text=".DMA_DESC_TEXT_CODE"

/*----------------------------------------------------------------------------------------------*/
/*	DMA Trans Mode (Double Buffer Reload) Set Function											*/
/*	return		: void																			*/
/*	parameters	: ChannelDataID																	*/
/*				: TransSize (SIZE_1/SIZE_2/SIZE_4)												*/
/*				: DescMode (0-2)																*/
/*				: SrcAdr(Async) (Pointer to Source Adrress)										*/
/*				: DestAdr(Async) (Pointer to Destination Adrress)								*/
/*				: TransNum (Number of transfers to the second stage)							*/
/*				: ReloadPtr (Descriptor pointer reloaded at first(ex:u2_DMAC_DESC_PTR_CH_P_0))	*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_SetTransModeDoubleBufferReload( U1 t_u1ChDataID, U1 t_u1TransSize, U1 t_u1DescMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum, U2 t_u2ReloadPtr )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	U1		t_u1ChannelID;				/* DMA Ch No */
	U1		t_u1DmaType;				/* DMA Type */
	U1		t_u1DmaReqNum;				/* DMA Hardware Factors */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType != (U1)DMA_DTS )
	{
		t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
		t_u1DmaReqNum = (U1)(t_pcstChDataConfig->u2DmaReq & u2DMA_DMAC_GROUP_REQ_MASK);
		Pil_Dmac_SetTransModeDoubleBufferReload( t_u1ChannelID, t_u1DmaType, t_u1TransSize, t_u1DescMode, t_pcvdSrcAdr, t_pcvdDestAdr, t_u2TransNum, t_u2ReloadPtr, t_u1DmaReqNum );
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	DMA Reload Data Update Function																*/
/*	return		: void																			*/
/*	parameters	: ChannelDataID																	*/
/*				: TransSize (SIZE_1/SIZE_2/SIZE_4)												*/
/*				: SrcAdr(Async) (Pointer to Source Adrress)										*/
/*				: DestAdr(Async) (Pointer to Destination Adrress)								*/
/*				: TransNum (Number of transfers until second reload)							*/
/*				: ReloadPtr (Descriptor pointer reloaded at first								*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_ReloadDataUpdate( U1 t_u1ChDataID, U1 t_u1TransSize, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum, U2 t_u2ReloadPtr )
{
	const	Dma_ChDataDefType*	t_pcstChDataConfig;
	U1		t_u1ChannelID;				/* DMA Ch No */
	U1		t_u1DmaType;				/* DMA Type */

	/* Get CH information from DMA logic CH */
	t_pcstChDataConfig = &(cstDma_UcfgData.pstChDataConfig[t_u1ChDataID]);
	t_u1ChannelID = (U1)(t_pcstChDataConfig->u2HwCh);
	t_u1DmaType = t_pcstChDataConfig->u1DmaType;

	if( t_u1DmaType != (U1)DMA_DTS )
	{
		Pil_Dmac_ReloadDataUpdate( t_u1ChannelID, t_u1DmaType, t_u1TransSize, t_pcvdSrcAdr, t_pcvdDestAdr, t_u2TransNum, t_u2ReloadPtr );
	}
}

/*==============================================================================================*/
/*	Local Functions																				*/
/*==============================================================================================*/

#pragma ghs section text=default
/*-- End Of File -------------------------------------------------------------------------------*/
