/* Dma-rA4-3000-0100-a-v01 */
/************************************************************************************************/
/*																								*/
/*		MCAL DMA Desc Driver																	*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

#ifndef DMA_DESC_H
#define DMA_DESC_H

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Std_Types.h"
#include	"Dma_DescCfg.h"

/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
#define DMA_DESCMODE0                   (0) /* DMA_DESC Mode 0   */
#define DMA_DESCMODE1                   (1) /* DMA_DESC Mode 1   */
#define DMA_DESCMODE2                   (2) /* DMA_DESC Mode 2   */
#define DMA_DESCMODE_NUM                (3) /* DMA_DESC Mode Num */

#define u2_DMAC_DESC_RAM_DBR_OFFSET     ((U2)5)
#define	u2_DMAC_DESC_RAM_ADDR_0_0	    ((U2)0U)
#define	u2_DMAC_DESC_RAM_ADDR_0_1	    ((U2)64U)
#define	u2_DMAC_DESC_RAM_ADDR_0_2	    ((U2)128U)
#define	u2_DMAC_DESC_RAM_ADDR_0_3	    ((U2)192U)
#define	u2_DMAC_DESC_RAM_ADDR_0_4	    ((U2)256U)
#define	u2_DMAC_DESC_RAM_ADDR_0_5	    ((U2)320U)
#define	u2_DMAC_DESC_RAM_ADDR_0_6	    ((U2)384U)
#define	u2_DMAC_DESC_RAM_ADDR_0_7	    ((U2)448U)
#define	u2_DMAC_DESC_RAM_ADDR_0_8	    ((U2)512U)
#define	u2_DMAC_DESC_RAM_ADDR_0_9	    ((U2)576U)
#define	u2_DMAC_DESC_RAM_ADDR_0_10	    ((U2)640U)
#define	u2_DMAC_DESC_RAM_ADDR_0_11	    ((U2)704U)
#define	u2_DMAC_DESC_RAM_ADDR_0_12	    ((U2)768U)
#define	u2_DMAC_DESC_RAM_ADDR_0_13	    ((U2)832U)
#define	u2_DMAC_DESC_RAM_ADDR_0_14	    ((U2)896U)
#define	u2_DMAC_DESC_RAM_ADDR_0_15	    ((U2)960U)

/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
/*----------------------------------------------------------------------------------------------*/
/*	DMA Trans Mode (Double Buffer Reload) Set Function											*/
/*	return		: void																			*/
/*	parameters	: ChannelDataID																	*/
/*				: TransSize (SIZE_1/SIZE_2/SIZE_4)												*/
/*				: DescMode (0-2)																	*/
/*				: SrcAdr(Async) (Pointer to Source Adrress)										*/
/*				: DestAdr(Async) (Pointer to Destination Adrress)								*/
/*				: TransNum (Number of transfers to the second stage)							*/
/*				: ReloadPtr (Descriptor pointer reloaded at first								*/
/*----------------------------------------------------------------------------------------------*/
void	Dma_SetTransModeDoubleBufferReload( U1 t_u1ChDataID, U1 t_u1TransSize, U1 t_u1DescMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum, U2 t_u2ReloadPtr );

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
void	Dma_ReloadDataUpdate( U1 t_u1ChDataID, U1 t_u1TransSize, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum, U2 t_u2ReloadPtr );
#endif /* DMA_DESC_H */
/*-- End Of File -------------------------------------------------------*/
