/* pil_dmac-rA4-3000-0100-a-v01 */
/************************************************************************************************/
/*																								*/
/*		PIL sDMAC Desc Driver   																*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef DMACDESC_H
#define DMACDESC_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Mcal_SpalCmn.h"

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Trans Mode (Double buffer Reload) Set Function										*/
/*	return			: void																		*/
/*	parameters		: DMAC ChannelID (0-15) 													*/
/*					: DMAC Type (DMAC0/DMAC1)													*/
/*					: TransSize (SIZE_1/SIZE_2/SIZE_4)											*/
/*					: DmaMode (7-8)																*/
/*					: SrcAdr(Async) (Pointer to Source Adrress)									*/
/*					: DestAdr(Async) (Pointer to Destination Adrress)							*/
/*					: TransNum (Number of transfers until second reload)						*/
/*					: ReloadPtr (Descriptor pointer reloaded at first							*/
/*					: DmaReqNum (Reqest number)													*/
/*	Return value	: none																		*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_SetTransModeDoubleBufferReload( U1 t_u1ChannelID, U1 t_u1DmaType, U1 t_u1TransSize, U1 t_u1DescMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum, U2 t_u2ReloadPtr, U1 t_u1DmaReqNum );

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Reload Data Update Function 															*/
/*	return			: void																		*/
/*	parameters		: DMAC ChannelID (0-15)														*/
/*					: DMAC Type (DMAC0/DMAC1)													*/
/*					: TransSize (SIZE_1/SIZE_2/SIZE_4)											*/
/*					: SrcAdr(Async) (Pointer to Source Adrress)									*/
/*					: DestAdr(Async) (Pointer to Destination Adrress)							*/
/*					: TransNum (Number of transfers until second reload)						*/
/*					: ReloadPtr (Descriptor pointer to update)									*/
/*	Return value	: none																		*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_ReloadDataUpdate( U1 t_u1ChannelID, U1 t_u1DmaType, U1 t_u1TransSize, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum, U2 t_u2ReloadPtr );



#endif /* DMACDESC_H */
/*-- End Of File -------------------------------------------------------*/
