/* pil_dmac-r04-3000-0200-b-v00 */
/************************************************************************************************/
/*																								*/
/*		PIL sDMAC Driver																		*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Dma.h"
#include	"Dma_engine.h"
#include	"Mcal_SpalCmn.h"
#include	"pil_dmac.h"
#include	"pil_intc.h"

#include	"reg_dma.h"


/*==============================================================================================*/
/*	prototypes																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
#define		u1PIL_DMAC_MODE_NUM			((uint8)7U)
#define		u1PIL_DMAC_DMAC0			((uint8)0U)
#define		u1PIL_DMAC_TRANSSIZE_NUM	((uint8)7U)
#define		u1PIL_DMAC_TRANSSIZE_1		((uint8)1U)					/* 1byte  */
#define		u1PIL_DMAC_TRANSSIZE_2		((uint8)2U)					/* 2byte  */
#define		u1PIL_DMAC_TRANSSIZE_4		((uint8)4U)					/* 4byte  */
#define		u1PIL_DMAC_TRANSSIZE_8		((uint8)8U)					/* 8byte  */
#define		u1PIL_DMAC_TRANSSIZE_16		((uint8)16U)				/* 16byte */
#define		u1PIL_DMAC_TRANSSIZE_32		((uint8)32U)				/* 32byte */
#define		u1PIL_DMAC_TRANSSIZE_64		((uint8)64U)				/* 64byte */
#define		u1PIL_DMAC_TRANSMODE_2		((uint8)2U)					/* Mode 2 Transfer */
#define		u2PIL_DMAC_DESRAM_ADDR_CH0	((uint16)0U)				/* DMAC descriptor CH0 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH1	((uint16)64U)				/* DMAC descriptor CH1 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH2	((uint16)128U)				/* DMAC descriptor CH2 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH3	((uint16)192U)				/* DMAC descriptor CH3 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH4	((uint16)256U)				/* DMAC descriptor CH4 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH5	((uint16)320U)				/* DMAC descriptor CH5 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH6	((uint16)384U)				/* DMAC descriptor CH6 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH7	((uint16)448U)				/* DMAC descriptor CH7 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH8	((uint16)512U)				/* DMAC descriptor CH8 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH9	((uint16)576U)				/* DMAC descriptor CH9 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH10	((uint16)640U)				/* DMAC descriptor CH10 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH11	((uint16)704U)				/* DMAC descriptor CH11 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH12	((uint16)768U)				/* DMAC descriptor CH12 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH13	((uint16)832U)				/* DMAC descriptor CH13 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH14	((uint16)896U)				/* DMAC descriptor CH14 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH15	((uint16)960U)				/* DMAC descriptor CH15 Pointer value of the head address */

typedef	union
{
	uint16	u2Data;
	struct
	{
		uint16	b4RegReqSigNum:4;   /* preferred request signal number in the register */
		uint16	b4RegNum:4;			/* Register  Number */
		uint16  b2Group:2; 			/* Group number */ 
		uint16  b6Dummy:6;
	}stDiv;
}Pil_Dmac_RequestGroupType;

/*==============================================================================================*/
/*	constants																					*/
/*==============================================================================================*/
#define DMA_START_SEC_RODATA_CONST
#include "Dma_MemMap.h"

/* MODE setting table *******************************/
/* mode= 0: Dst Addr increased, Src Addr fixed 		*/
/* mode= 1: Dst Addr increased, Src Addr fixed 		*/
/* mode= 2: Dst Addr fixed, Src Addr increased 		*/
/* mode= 3: Dst Addr increased, Src Addr increased 	*/
/* mode= 4: Dst Addr increased, Src Addr fixed 		*/
/* mode= 5: Dst Addr increased, Src Addr increased 	*/
/* mode= 6: Dst Addr fixed, Src Addr fixed			*/
/****************************************************/
static volatile const	uint32		cu4PIL_DMAC_MODE_TABLE[u1PIL_DMAC_MODE_NUM] = {
	(uint32)((uint32)DMA_TMR_DM_0	*	(uint32)DMA_TMR_DM_INCREMENT		+
			 (uint32)DMA_TMR_SM_0	*	(uint32)DMA_TMR_SM_FIX),				/* mode=0 : e.g. for RAM clear */
	(uint32)((uint32)DMA_TMR_DM_0	*	(uint32)DMA_TMR_DM_INCREMENT		+
			 (uint32)DMA_TMR_SM_0	*	(uint32)DMA_TMR_SM_FIX),				/* mode=1 : e.g. for SPI(SCI) Receive, A/D Gated(No Reload) */
	(uint32)((uint32)DMA_TMR_DM_0	*	(uint32)DMA_TMR_DM_FIX				+
			 (uint32)DMA_TMR_SM_0	*	(uint32)DMA_TMR_SM_INCREMENT),			/* mode=2 : e.g. for SPI(SCI) Send */
	(uint32)((uint32)DMA_TMR_DM_0	*	(uint32)DMA_TMR_DM_INCREMENT		+
			 (uint32)DMA_TMR_SM_0	*	(uint32)DMA_TMR_SM_INCREMENT),			/* mode=3 : e.g. for A/D Scan */
	(uint32)((uint32)DMA_TMR_DM_0	*	(uint32)DMA_TMR_DM_INCREMENT		+
			 (uint32)DMA_TMR_SM_0	*	(uint32)DMA_TMR_SM_FIX),				/* mode=4 : e.g. for A/D Gated(Reload) */
	(uint32)((uint32)DMA_TMR_DM_0	*	(uint32)DMA_TMR_DM_INCREMENT		+
			 (uint32)DMA_TMR_SM_0	*	(uint32)DMA_TMR_SM_INCREMENT),			/* mode=5 : e.g. for A/D GatedMulti */
	(uint32)((uint32)DMA_TMR_DM_0	*	(uint32)DMA_TMR_DM_FIX				+
			 (uint32)DMA_TMR_SM_0	*	(uint32)DMA_TMR_SM_FIX)					/* mode=6 : e.g. for SPI(Dummy) Send  Receive */
};

static volatile const uint16 cu2Pil_Dmac0_IntcChannelID[DMA_DMAC_CH_NUM] = {
	DMA_INTC2_INTSDMAC0CH0
	,DMA_INTC2_INTSDMAC0CH1
	,DMA_INTC2_INTSDMAC0CH2
	,DMA_INTC2_INTSDMAC0CH3
	,DMA_INTC2_INTSDMAC0CH4
	,DMA_INTC2_INTSDMAC0CH5
	,DMA_INTC2_INTSDMAC0CH6
	,DMA_INTC2_INTSDMAC0CH7
	,DMA_INTC2_INTSDMAC0CH8
	,DMA_INTC2_INTSDMAC0CH9
	,DMA_INTC2_INTSDMAC0CH10
	,DMA_INTC2_INTSDMAC0CH11
	,DMA_INTC2_INTSDMAC0CH12
	,DMA_INTC2_INTSDMAC0CH13
	,DMA_INTC2_INTSDMAC0CH14
	,DMA_INTC2_INTSDMAC0CH15
};

#if ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) || ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) && (MCAL_PKG_TARGET != MCAL_PKG_U2B6_292PIN)))
static volatile const uint16 cu2Pil_Dmac1_IntcChannelID[DMA_DMAC_CH_NUM] = {
	DMA_INTC2_INTSDMAC1CH0
	,DMA_INTC2_INTSDMAC1CH1
	,DMA_INTC2_INTSDMAC1CH2
	,DMA_INTC2_INTSDMAC1CH3
	,DMA_INTC2_INTSDMAC1CH4
	,DMA_INTC2_INTSDMAC1CH5
	,DMA_INTC2_INTSDMAC1CH6
	,DMA_INTC2_INTSDMAC1CH7
	,DMA_INTC2_INTSDMAC1CH8
	,DMA_INTC2_INTSDMAC1CH9
	,DMA_INTC2_INTSDMAC1CH10
	,DMA_INTC2_INTSDMAC1CH11
	,DMA_INTC2_INTSDMAC1CH12
	,DMA_INTC2_INTSDMAC1CH13
	,DMA_INTC2_INTSDMAC1CH14
	,DMA_INTC2_INTSDMAC1CH15
};
#endif

/* Addresses are not sequential, so they correspond in tables */
static volatile Reg_Dma_Type* const cstPil_Dmac_Reg[DMA_DMAC_UNIT_NUM] = {
		&Reg_DMAC0
		#if ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) || ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) && (MCAL_PKG_TARGET != MCAL_PKG_U2B6_292PIN)))
		,&Reg_DMAC1
		#endif
};

static volatile Reg_Dram_Type* const cstPil_DmacDesRAM_Reg[DMA_DMAC_UNIT_NUM] = {
		&Reg_DesRAM0
		#if ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) || ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) && (MCAL_PKG_TARGET != MCAL_PKG_U2B6_292PIN)))
		,&Reg_DesRAM1		
		#endif
};
/* DMAC source transfer size */
static volatile const	uint8		cu1PIL_DMAC_TransSize[u1PIL_DMAC_TRANSSIZE_NUM] =
{
	u1PIL_DMAC_TRANSSIZE_1
	,u1PIL_DMAC_TRANSSIZE_2
	,u1PIL_DMAC_TRANSSIZE_4
	,u1PIL_DMAC_TRANSSIZE_8
	,u1PIL_DMAC_TRANSSIZE_16
	,u1PIL_DMAC_TRANSSIZE_32
	,u1PIL_DMAC_TRANSSIZE_64
};

/* DMAC descriptor address pointer value(Leading address pointer value per channel) */
static volatile const	uint16		cu2PIL_DMAC_DescriptorAdrrpNum[DMA_DMAC_CH_NUM] =
{
	u2PIL_DMAC_DESRAM_ADDR_CH0		/* CH0 */
	,u2PIL_DMAC_DESRAM_ADDR_CH1		/* CH1 */
	,u2PIL_DMAC_DESRAM_ADDR_CH2		/* CH2 */
	,u2PIL_DMAC_DESRAM_ADDR_CH3		/* CH3 */
	,u2PIL_DMAC_DESRAM_ADDR_CH4		/* CH4 */
	,u2PIL_DMAC_DESRAM_ADDR_CH5		/* CH5 */
	,u2PIL_DMAC_DESRAM_ADDR_CH6		/* CH6 */
	,u2PIL_DMAC_DESRAM_ADDR_CH7		/* CH7 */
	,u2PIL_DMAC_DESRAM_ADDR_CH8		/* CH8 */
	,u2PIL_DMAC_DESRAM_ADDR_CH9		/* CH9 */
	,u2PIL_DMAC_DESRAM_ADDR_CH10	/* CH10 */
	,u2PIL_DMAC_DESRAM_ADDR_CH11	/* CH11 */
	,u2PIL_DMAC_DESRAM_ADDR_CH12	/* CH12 */
	,u2PIL_DMAC_DESRAM_ADDR_CH13	/* CH13 */
	,u2PIL_DMAC_DESRAM_ADDR_CH14	/* CH14 */
	,u2PIL_DMAC_DESRAM_ADDR_CH15	/* CH15 */
};

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
/* API Functions                                                                                */
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Trans Enable with DMA Request Clear Function											*/
/*	return		: void																			*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_EnableTrans( uint8 t_u1ChannelID, uint8 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	/* (4)  Transfer Status Clear */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data  =(uint32)((uint32)DMA_CHFCR_OVFC * (uint32)DMA_CHFCR_OVFC_CLEAR + 
																(uint32)DMA_CHFCR_DRQC * (uint32)DMA_CHFCR_DRQC_CLEAR + 
																(uint32)DMA_CHFCR_CAEC * (uint32)DMA_CHFCR_CAEC_CLEAR + 
																(uint32)DMA_CHFCR_DSEC * (uint32)DMA_CHFCR_DSEC_CLEAR + 
																(uint32)DMA_CHFCR_TEC  * (uint32)DMA_CHFCR_TEC_CLEAR);

	/* DMA channel-stop register setting(Refresh) */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHSTP.u2Data = (uint16)((uint16)DMA_CHSTP_STP * (uint16)DMA_CHSTP_STP_RESTART);

	/* DMA operation register setting */
	t_pstRegDmac->unOR.u2Data  =	(uint16)((uint16)DMA_OR_DME * (uint16)DMA_OR_DME_TRANS_ENABLE +
												(uint16)DMA_OR_PR_0 * (uint16)DMA_OR_PR_CH);

	/* (5)  DMAC channel operation enable setting */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data |= (uint16)((uint16)DMA_CHCR_DE * (uint16)DMA_CHCR_DE_ENABLE);
	Bswlib_Sync_Pipeline_2(t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data);			/* dummy read */
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Trans Disable Function																*/
/*	return		: void																			*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_DisableTrans( uint8 t_u1ChannelID, uint8 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data =(uint32)((uint32)DMA_CHFCR_DEC * (uint32)DMA_CHFCR_DEC_CLEAR		+	/* DMA transfer request disabled */
															(uint32)DMA_CHFCR_DPEC * (uint32)DMA_CHFCR_DPEC_CLEAR);		/* Descriptor invalidation */
	Bswlib_Sync_Pipeline_4(t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data);				/* dummy read */
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Trans Mode Set Function																*/
/*	return		: void																			*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*				: TransSize (SIZE_1/SIZE_2/SIZE_4)												*/
/*				: DmaMode (0-2)																	*/
/*				: SrcAdr(Async) (Pointer to Source Adrress)										*/
/*				: DestAdr(Async) (Pointer to Destination Adrress)								*/
/*				: TransNum (Trans number)														*/
/*				: DmaReqNum (Reqest number)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_SetTransMode( uint8 t_u1ChannelID, uint8 t_u1DmaType, uint8 t_u1TransSize, uint8 t_u1DmaMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, uint16 t_u2TransNum, uint8 t_u1DmaReqNum )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;
	uint32		t_u4Tmr;			/* TMR register setting value */
	uint32		t_u4Rs;				/* RS register setting value */
	uint16		t_u2Chcr;			/* CHCR register setting value */

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	/* DI_ALL()";" */ /* No interrupts are required because there is no use case for calling Enable, SetInterrupt, this function	*/
	                /*  from a high-priority task during SetTransMode for the same DMAC channel.								*/

	/* DMA channel master configuration is designed to be performed by ErrH, and DMAC requires no configuration process */
	/* because of the initial value expectations. 																		*/

    /* (1)  DMAC channel operation disabled setting */
	/* Clear the DE bit in the DMA channel control register following UM's DMA channel setup procedure. */
	/* The BUSY flag of the status is never set because API restrictions prevent calls to this API during DMA transfers. */
	/* So there's no logic to make sure the BUSY flag is cleared. */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data = (uint32)((uint32)DMA_CHFCR_DEC * (uint32)DMA_CHFCR_DEC_CLEAR);

	/* (2)  Setting transfer information */
	/* In setting the transfer information of DMAC, set the following registers */
	/* DMAC source address register(DMAjSAR_n) */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4SAR = (uint32)((volatile const uint32*)t_pcvdSrcAdr);		/* Source address settings */
	/* DMAC destination address register(DMAjDAR_n) */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4DAR = (uint32)((volatile const uint32*)t_pcvdDestAdr);		/* Destination Address Configuration */
	/* DMAC transfer size register(DMAjTSR_n) */
	/* Find the transfer size setting from the transfer size */ /* Overall transfer size */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4TSR = (uint32)( (uint32)cu1PIL_DMAC_TransSize[t_u1TransSize] * (uint32)t_u2TransNum ); /* justification for QAC warning 3384: it is not wrap-around within a configuration range */ /* EDET_INT30 */
	/* DMAC transfer mode register(DMAjTMR_n) */
	t_u4Tmr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unTMR.u4Data & ( (uint32)~( (uint32)DMA_TMR_TRS	+	(uint32)DMA_TMR_DM	+	
					(uint32)DMA_TMR_SM	+	(uint32)DMA_TMR_SLM	+	(uint32)DMA_TMR_PRI	+	(uint32)DMA_TMR_DTS	+	(uint32)DMA_TMR_STS ) ) );
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unTMR.u4Data = (uint32)( t_u4Tmr |(uint32)( (uint32)DMA_TMR_TRS * (uint32)DMA_TMR_TRS_HARDWARE_REQ		+	/* TRS=1:Hard request */ /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
				cu4PIL_DMAC_MODE_TABLE[t_u1DmaMode]					+		/* MODE setting table */
				(uint32)DMA_TMR_SLM_0	*	(uint32)DMA_TMR_SLM_NORMAL			+	/* SLM=0000:Normal mode(Slow mode not supported) */
				(uint32)DMA_TMR_PRI_0	*	(uint32)DMA_TMR_PRI_DISABLE			+		/* PRI=0:Channel request priority disabled */    /* justification for QAC warning 3384: it is not wrap-around within a configuration range */ /* EDET_INT30 */
				(uint32)DMA_TMR_DTS_0	*	t_u1TransSize				+		/* DTS=Destination Transfer Size */         /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
				/* DMA_TMR_STS_0 is BIT0 and the result of multiplication is the same as t_u1TransSize. */
				/* Fix for QAC compatibility										*/
				/*(uint32)DMA_TMR_STS_0	*	t_u1TransSize ) )";"	*/
				(uint32)t_u1TransSize ) );											/* STS=Source Transfer Size */

	/* (3)  Setting DMA Transfer Requests */
	/* DMAC Resource Selection Register(DMAjRS_n) When using hardware transfer request mode */
	t_u4Rs = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unRS.u4Data;
	t_u4Rs &= (uint32)( ~( (uint32)DMA_RS_TC + (uint32)DMA_RS_TL + (uint32)DMA_RS_PLE + (uint32)DMA_RS_DRQI + (uint32)DMA_RS_RS ) );
	if ( t_u1DmaMode == (uint8)DMA_DMAMODE0 )
	{	/* On block transfer */
		t_u4Rs |= ( ( (uint32)DMA_RS_TL_0		*	(uint32)DMA_RS_TL_TSR )				+		/* TL=010: DMAjTSR_ n.Transfer size specified by TSR  */
					( (uint32)DMA_RS_PLE		*	(uint32)DMA_RS_PLE_DISABLE )		+		/* PRT= Preload function not disabled so no setting required */
					( (uint32)DMA_RS_DRQI		*	(uint32)DMA_RS_DRQI_DISABLE )		+		/* PLE=0: Disabled */ /* EDET_INT30 */
					(uint32)t_u1DmaReqNum );												/* Hardware factor number */
					/* ( (uint32)DMA_RS_RS_0		*	(uint32)t_u1DmaReqNum ) );	*/			/* Hardware factor number */
	}
	else
	{	/* On single transfer */
		t_u4Rs |= ( ( (uint32)DMA_RS_TC_0		*	(uint32)1U )						+		/* TC=1: Transfers per hardware request */
					( (uint32)DMA_RS_TL_0		*	(uint32)DMA_RS_TL_STS )				+		/* TL=000: DMAjTMR_n.STS x DMAjRS_ n.Transfer size specified by TC  */
					( (uint32)DMA_RS_PLE		*	(uint32)DMA_RS_PLE_DISABLE )		+		/* PRT= Preload function not disabled so no setting required */
					( (uint32)DMA_RS_DRQI		*	(uint32)DMA_RS_DRQI_DISABLE )		+		/* PLE=0: Disabled */ /* EDET_INT30 */
					(uint32)t_u1DmaReqNum  );												/* Hardware factor number */
					/*( (uint32)DMA_RS_RS_0		*	(uint32)t_u1DmaReqNum ) );		*/			/* Hardware factor number */
	}
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unRS.u4Data = t_u4Rs;

	/* Since SetTransMode does not support transfer modes 3 and later, the DMA transfer completion interrupt is enabled and the descriptor end interrupt is disabled. */
	/* The AND with the inverted value is temporarily held to hold settings other than the specified bit.(It is an intended cast and can never be negative.) */
	t_u2Chcr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data & ( (uint16)~( (uint16)DMA_CHCR_DSIE + (uint16)DMA_CHCR_IE + (uint16)DMA_CHCR_DPE + (uint16)DMA_CHCR_CAEE + (uint16)DMA_CHCR_CAIE ) ) );
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data = (uint16)( t_u2Chcr | (uint16)(	(uint16)DMA_CHCR_DSIE	* (uint16)DMA_CHCR_DSIE_DISABLE	+		/* Descriptor End Interrupt Disabled */
																			(uint16)DMA_CHCR_IE		* (uint16)DMA_CHCR_IE_ENABLE	+	/* DMA Transfer Completion Interrupt Enabled */
																			(uint16)DMA_CHCR_DPE	* (uint16)DMA_CHCR_DPE_DISABLE 	+	/* Descriptor operation disabled */
																			(uint16)DMA_CHCR_CAEE	* (uint16)DMA_CHCR_CAEE_DISABLE	+	/* Channel address error notification disabled */
																			(uint16)DMA_CHCR_CAIE	* (uint16)DMA_CHCR_CAIE_DISABLE ));	/* Channel Address Error Interrupt Disabled */
	/* EI_ALL()";" */
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Trans Mode (Two Level Reload) Set Function											*/
/*	return		: void																			*/
/*	parameters	: DMAC ChannelID (0-15) 														 */
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*				: TransSize (SIZE_1/SIZE_2/SIZE_4)												*/
/*				: DmaMode (3-5)																	*/
/*				: SrcAdr(Async) (Pointer to Source Adrress)										*/
/*				: DestAdr(Async) (Pointer to Destination Adrress)								*/
/*				: TransNum (Number of transfers until second reload)							*/
/*				: AddrReloadCnt (Number of transfers until first reload(If not mode5, specify 0)) */
/*				: DmaReqNum (Reqest number)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_SetTransModeTwoStepReload( uint8 t_u1ChannelID, uint8 t_u1DmaType, uint8 t_u1TransSize, uint8 t_u1DmaMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, uint16 t_u2TransNum, uint16 t_u2AddrReloadCnt, uint8 t_u1DmaReqNum )
{
	/* Settings other than mode = 3 are currently not guaranteed to work, and the argument AddrReloadCnt is unused, but intentionally kept to match the interface of E1MS2. */

	volatile Reg_Dma_Type*	t_pstRegDmac;
	volatile Reg_Dram_Type*	t_pstRegDmacDesRAM;
	uint32		t_u4Tmr;			/* TMR register setting value */
	uint32		t_u4Rs;				/* RS register setting value */
	uint16		t_u2Chcr;			/* CHCR register setting value */
	uint32		t_u4Dpptr;			/* Dpptr register setting value */
	uint32		t_u4Dpcr;			/* Dpcr register setting value */
	uint16		t_u2DesCnt;			/* Descriptor counters */

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];
	t_pstRegDmacDesRAM = (volatile Reg_Dram_Type*)cstPil_DmacDesRAM_Reg[t_u1DmaType];		/* Descriptor RAM */

	/* DI_ALL()";" */ /* No interrupts are required because there is no use case for calling Enable, SetInterrupt, this function */
	                /* from a high-priority task during SetTransMode for the same DMAC channel.								   */

	/* DMA channel master configuration is designed to be performed by ErrH, and DMAC requires no configuration process */
	/* because of the initial value expectations. 																		*/

	/* (1)  DMAC channel operation disabled setting */
	/* Clear the DE bit in the DMA channel control register following UM's DMA channel setup procedure. */
	/* The BUSY flag of the status is never set because API restrictions prevent calls to this API during DMA transfers. */
	/* So there's no logic to make sure the BUSY flag is cleared. */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data = (uint32)((uint32)DMA_CHFCR_DEC * (uint32)DMA_CHFCR_DEC_CLEAR);

	/* (2)  Setting transfer information */
	/* In setting the transfer information of DMAC, set the following registers */
	/* DMAC source address register(DMAjSAR_n) */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4SAR = (uint32)((volatile const uint32*)t_pcvdSrcAdr);		/* Source address settings */
	/* DMAC destination address register(DMAjDAR_n) */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4DAR = (uint32)((volatile const uint32*)t_pcvdDestAdr);		/* Destination Address Configuration */
	/* DMAC transfer size register(DMAjTSR_n) */
	/* Find the transfer size setting from the transfer size */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4TSR = ( (uint32)cu1PIL_DMAC_TransSize[t_u1TransSize] * (uint32)t_u2TransNum );	/* Overall transfer siz */		/* justification for QAC warning 3384: it is not wrap-around within a configuration range */ /* EDET_INT30 */
	/* DMAC transfer mode register(DMAjTMR_n) */
	t_u4Tmr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unTMR.u4Data & ( (uint32)~( (uint32)DMA_TMR_TRS	+	(uint32)DMA_TMR_DM	+	
					(uint32)DMA_TMR_SM	+	(uint32)DMA_TMR_SLM	+	(uint32)DMA_TMR_PRI	+	(uint32)DMA_TMR_DTS	+	(uint32)DMA_TMR_STS ) ) );
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unTMR.u4Data = (uint32)( t_u4Tmr | (uint32)( (uint32)DMA_TMR_TRS * (uint32)DMA_TMR_TRS_HARDWARE_REQ		+	/* TRS=1:Hard request */ /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
				cu4PIL_DMAC_MODE_TABLE[t_u1DmaMode]					+		/* MODE setting table */
				(uint32)DMA_TMR_SLM_0	*	(uint32)DMA_TMR_SLM_NORMAL			+		/* SLM=0000:Normal mode(Slow mode not supported) */
				(uint32)DMA_TMR_PRI_0	*	(uint32)DMA_TMR_PRI_DISABLE			+		/* PRI=0:Channel request priority disable */	/* justification for QAC warning 3384: it is not wrap-around within a configuration range */ /* EDET_INT30 */
				(uint32)DMA_TMR_DTS_0	*	t_u1TransSize				+			/* DTS=Destination Transfer Size */	  /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
				/* Since DMA_TMR_STS_0 is BIT0, the result of multiplication is the same as t_u1TransSize 	*/
				/* Fix for QAC compatibility												*/
				/* (uint32)DMA_TMR_STS_0	*	t_u1TransSize ) )";"	*/
				(uint32)t_u1TransSize ) );											/* STS=Source Transfer Size */

	/* (3)  Setting DMA Transfer Requests */
	/* DMAC Resource Selection Register(DMAjRS_n) When using hardware transfer request mode */
	t_u4Rs = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unRS.u4Data & ( (uint32)~( (uint32)DMA_RS_TL + (uint32)DMA_RS_PLE + (uint32)DMA_RS_DRQI + (uint32)DMA_RS_RS ) ) ) ;
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unRS.u4Data = (uint32)( t_u4Rs | (uint32)(	(uint32)DMA_RS_TL_0	*	(uint32)DMA_RS_TL_TSR		+	/* TL=010:Transfer size specified by DMAjTSR_n.TSR  */
				(uint32)DMA_RS_PLE		*	(uint32)DMA_RS_PLE_DISABLE			+			/* PLE=0:Preload function disabled */
				(uint32)DMA_RS_DRQI		*	(uint32)DMA_RS_DRQI_DISABLE			+		/* DRQI=0:DRQ initialization disabled */  /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
				/* Since DMA_RS_RS_0 is BIT0, the result of multiplication is the same as t_u1DmaReqNum */
				/* Fix for QAC compatibility											*/
				/* (uint32)DMA_RS_RS_0		*	t_u1DmaReqNum ))";"	*/
				(uint32)t_u1DmaReqNum ));										/* Hardware factor number */

	if(t_u1DmaMode > u1PIL_DMAC_TRANSMODE_2)
	{
		/* Only transfer mode 3 supported */

		/* Descriptor Settings */
		t_u4Dpcr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unDPCR.u4Data & ( (uint32)~( (uint32)DMA_DPCR_UPF ) ) );		/* Clear the settings of UPF 0 to UPF 10, which are valid bits */
		t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unDPCR.u4Data =  (uint32)( t_u4Dpcr |
																(uint32)( (uint32)DMA_DPCR_UPF_0 * (uint32)DMA_DPCR_UPF_SAR_ENABLE +	/* Source address register update flag */
																(uint32)DMA_DPCR_UPF_1 * (uint32)DMA_DPCR_UPF_DAR_ENABLE +			/* Destination address register update flag */
																(uint32)DMA_DPCR_UPF_2 * (uint32)DMA_DPCR_UPF_TSR_ENABLE +			/* Transfer size register update flag */
																(uint32)DMA_DPCR_UPF_3 * (uint32)DMA_DPCR_UPF_TMR_ENABLE ) );		/* Transfer mode register update flag */

		t_u2DesCnt=cu2PIL_DMAC_DescriptorAdrrpNum[t_u1ChannelID];			/* Initializing the descriptor counter */

		/* Descriptor Memory Settings */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = (uint32)((volatile const uint32*)t_pcvdSrcAdr);	/* DMAC source address register */
		t_u2DesCnt++;    /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = (uint32)((volatile const uint32*)t_pcvdDestAdr);	/* DMAC destination address register */
		t_u2DesCnt++;    /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = (uint32)( (uint32)cu1PIL_DMAC_TransSize[t_u1TransSize] * (uint32)t_u2TransNum );	/* DMAC transfer size register */	/* justification for QAC warning 3384: it is not wrap-around within a configuration range */ /* EDET_INT30 */
		t_u2DesCnt++;	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unTMR.u4Data;				/* DMAC transfer mode register */
		t_u2DesCnt++;	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
		t_u4Dpptr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unDPPTR.u4Data & ( (uint32)~( (uint32)DMA_DPPTR_DIE + (uint32)DMA_DPPTR_PTR + (uint32)DMA_DPPTR_CF ) ) );
		t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unDPPTR.u4Data = (uint32)( t_u4Dpptr |								/* Descriptor pointer register */
						(uint32)( (uint32)DMA_DPPTR_DIE	*	(uint32)DMA_DPPTR_DIE_ENABLE	+								/* Descriptor End Interrupt Enabled */ /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
						(uint32)DMA_DPPTR_PTR_0 *	cu2PIL_DMAC_DescriptorAdrrpNum[t_u1ChannelID]	+			/* Address pointer of next descriptor */	/* justification for QAC warning 3384: it is not wrap-around within a configuration range */ /* EDET_INT30 */
						(uint32)DMA_DPPTR_CF	*	(uint32)DMA_DPPTR_CF_ENABLE ) );								/* Descriptor continuation flag */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unDPPTR.u4Data;	/* Address pointer of descriptor */

		/* Setting the start of a descriptor */
		/* Transfer mode 3 disables the DMA transfer completion interrupt and enables the descriptor end interrupt. */
		/* The AND with the inverted value is temporarily held to hold settings other than the specified bit.(It is an intended cast and can never be negative.) */
		t_u2Chcr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data & ( (uint16)~( (uint16)DMA_CHCR_DPE + (uint16)DMA_CHCR_DSIE + (uint16)DMA_CHCR_IE + (uint16)DMA_CHCR_DPB + (uint16)DMA_CHCR_CAEE + (uint16)DMA_CHCR_CAIE ) ) );
		t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data = (uint16)( t_u2Chcr |(uint16) (	(uint16)DMA_CHCR_DPE	*	(uint16)DMA_CHCR_DPE_ENABLE			+	/* Descriptor Action Enabled */
																				(uint16)DMA_CHCR_DSIE	*	(uint16)DMA_CHCR_DSIE_ENABLE		+	/* Descriptor End Interrupt Enabled */
																				(uint16)DMA_CHCR_IE		*	(uint16)DMA_CHCR_IE_DISABLE			+	/* DMA Transfer Completion Interrupt Disabled */
																				(uint16)DMA_CHCR_DPB	*	(uint16)DMA_CHCR_DPB_REGISTER_SET	+  	/* Start DMA transfer by register setting */
																				(uint16)DMA_CHCR_CAEE	*	(uint16)DMA_CHCR_CAEE_DISABLE		+	/* Channel address error notification disabled */
																				(uint16)DMA_CHCR_CAIE	*	(uint16)DMA_CHCR_CAIE_DISABLE ));		/* Channel address error interrupt disabled */
	}

	/* EI_ALL()";" */
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Interrupt E/D Set Function															*/
/*	return		: void																			*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*				: EndIe (ON/OFF)""																*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_SetInterrupt( uint8 t_u1ChannelID, uint8 t_u1DmaType, uint8 t_u1EndIe )
{
	if( t_u1DmaType == u1PIL_DMAC_DMAC0 )
	{
		Pil_Intc2_SetInterrupt( cu2Pil_Dmac0_IntcChannelID[t_u1ChannelID], t_u1EndIe );
	}
#if ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) || ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) && (MCAL_PKG_TARGET != MCAL_PKG_U2B6_292PIN)))
	else
	{
		Pil_Intc2_SetInterrupt( cu2Pil_Dmac1_IntcChannelID[t_u1ChannelID], t_u1EndIe );
	}
#endif	
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Transfer completed state Function														*/
/*	return		: rans Completed Status (TRUE / FALSE)											*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
uint8		Pil_Dmac_IsTransferCompleted( uint8 t_u1ChannelID, uint8 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;
	uint32		t_u4Chsta;
	uint8		t_u1Ret;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	t_u1Ret = (uint8)FALSE;

	t_u4Chsta = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHSTA.u4Data;

	if( (t_u4Chsta & (uint32)DMA_CHSTA_TE) != (uint32)DMA_CHSTA_TE_RUNNING )
	{
		t_u1Ret = (uint8)TRUE;
	}

	return( t_u1Ret );
}

/*----------------------------------------------------------------------------------------------*/
/*	Compare Match Status Clear Function															*/
/*	return		: void																			*/
/*	parameters	: DMAC Channel(0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_ClearMatchStatus( uint8 t_u1ChannelID, uint8 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;

	DMA_ENTER_CRITICAL_SECTION();
	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];
	
	/* The interrupt request flag is cleared by clearing the DSE and TE flags. */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data = (uint32)((uint32)DMA_CHFCR_DSEC * (uint32)DMA_CHFCR_DSEC_CLEAR +
															(uint32)DMA_CHFCR_TEC  * (uint32)DMA_CHFCR_TEC_CLEAR);
	Bswlib_Sync_Pipeline_4( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data );
	DMA_EXIT_CRITICAL_SECTION();
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Destination Adrress Get Function														*/
/*	return		: Destination Address															*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
void*	Pil_Dmac_GetDestinationAddress( uint8 t_u1ChannelID, uint8 t_u1DmaType )
{

	volatile Reg_Dma_Type*	t_pstRegDmac;
	uint32* t_pu4DestAdr;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];
	t_pu4DestAdr = (uint32*)(t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4DAR);

	return ( (void*)t_pu4DestAdr);
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Trans Count Get Function																*/
/*	return		: Trans Count																	*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
uint16		Pil_Dmac_GetTransCount( uint8 t_u1ChannelID, uint8 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;
	uint16		t_u2Count;
	uint32		t_u4Chsta;
	uint8		t_u1TmrSts;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	/* Calculate number of transfers from DMA transfer size register and transfer size per transfer */
	t_u1TmrSts = (uint8)(t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unTMR.stBit.b4STS);
	t_u2Count = (uint16)( (t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4TSR + (uint32)(cu1PIL_DMAC_TransSize[t_u1TmrSts] - (uint32)1)) >> (uint32)t_u1TmrSts );  /* justification for QAC warning 3384: it is not wrap-around within a configuration range */ /* EDET_INT30 */

	t_u4Chsta = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHSTA.u4Data;

	/* If the number of transfers remaining is 0 and the cycle is running, 1 is added and returned. */
	/* Even if the calculated transfer count is 0, the cycle execution may not be completed. */
	if ( ( t_u2Count == (uint16)0 )
  	&& ( ( t_u4Chsta & (uint32)DMA_CHSTA_BUSY ) != (uint32)DMA_CHSTA_BUSY_IDLE  ) )
	{
		t_u2Count++;     /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
	}

	return( t_u2Count );
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Trans Count Reset Function															*/
/*	return		: none																			*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_ResetTransCount( uint8 t_u1ChannelID, uint8 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4TSR = (uint32)0;
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Trans Status Get Function																*/
/*	return		: Trans Status ( =0:IDLE / =1:BUSY)												*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
uint8		Pil_Dmac_GetTransStatus( uint8 t_u1ChannelID, uint8 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;
	uint32		t_u4Chsta;
	uint8		t_u1TransStat;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	t_u1TransStat = (uint8)DMA_CHSTA_BUSY_IDLE;

	t_u4Chsta = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHSTA.u4Data;

	if( (t_u4Chsta & (uint32)DMA_CHSTA_BUSY) != (uint32)DMA_CHSTA_BUSY_IDLE )
	{
		t_u1TransStat = (uint8)DMA_CHSTA_BUSY_BUSY;
	}

	return( t_u1TransStat );
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Error Check Function																	*/
/*	return		: Error Status																	*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
sint32	Pil_Dmac_CheckDmaError( uint8 t_u1ChannelID, uint8 t_u1DmaType )
{
	/* Check if specified DMAC CH has an address error */
	volatile Reg_Dma_Type*	t_pstRegDmac;
	uint32	t_u4Rtn;			/* Status values */

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	t_u4Rtn = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHSTA.u4Data & (uint32)DMA_CHSTA_CAE;

	return ( (sint32)t_u4Rtn );
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Error Status Clear Function															*/
/*	return		: none																			*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_ClearDmaError( uint8 t_u1ChannelID, uint8 t_u1DmaType )
{
	/* Clear address error flag for specified DMAC CH */
	volatile Reg_Dma_Type*	t_pstRegDmac;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data = ( (uint32)DMA_CHFCR_DEC * (uint32)DMA_CHFCR_DEC_CLEAR ) +	/* DMA transfer request disabled */
															( (uint32)DMA_CHFCR_CAEC * (uint32)DMA_CHFCR_CAEC_CLEAR );	/* Clear the address error flag */
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Reload Status Get Function															*/
/*	return		: Trans Status ( =0:RUN / =1:STOP)												*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
uint8		Pil_Dmac_GetReloadStatus( uint8 t_u1ChannelID, uint8 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;
	uint32		t_u4Chsta;
	uint8		t_u1TransStat;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	t_u1TransStat = (uint8)DMA_CHSTA_DSE_RUNNING;

	t_u4Chsta = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHSTA.u4Data;

	if( (t_u4Chsta & (uint32)DMA_CHSTA_DSE) != (uint32)( (uint32)DMA_CHSTA_DSE * (uint32)DMA_CHSTA_DSE_RUNNING ) )
	{
		t_u1TransStat = (uint8)DMA_CHSTA_DSE_STOP;
	}

	return( t_u1TransStat );
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Reload Step End Flag Clear  Function 													*/
/*	return		: void																			*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_ClearReloadStatus( uint8 t_u1ChannelID, uint8 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data = (uint32)((uint32)DMA_CHFCR_DSEC * (uint32)DMA_CHFCR_DSEC_CLEAR);
}

#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
/*----------------------------------------------------------------------------------------------*/
/*	sDMAC SET Transfer Request Group Function													*/
/*	return		: none																			*/
/*	parameters	: Request group number (0-1023)													*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_SetTransReqGroup( uint16 t_u2RequestGroup, uint8 t_u1DmaType)
{
	Pil_Dmac_RequestGroupType t_udRequestGroup;
	uint32 t_u4GroupData;
	uint32 t_u4DmacSelReg;
	uint8 t_u1RegReqSig;
	uint8 t_u1Register;

	t_udRequestGroup.u2Data = t_u2RequestGroup;
	t_u1RegReqSig = (uint8)t_udRequestGroup.stDiv.b4RegReqSigNum;
	t_u1Register = (uint8)t_udRequestGroup.stDiv.b4RegNum;
	t_u4GroupData = (uint32)t_udRequestGroup.stDiv.b2Group;

	t_u4GroupData = (uint32)(t_u4GroupData << (uint32)((uint32)t_u1RegReqSig * (uint32)DMA_DMAC_SEL_BIT_NUM));  /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */

	t_u4DmacSelReg = (uint32)(Reg_DMATRGSEL.unDMACSEL[t_u1DmaType][t_u1Register].u4Data & (uint32)(~(uint32)((uint32)DMA_DMACSEL_SEL0 << ((uint32)t_u1RegReqSig * (uint32)DMA_DMAC_SEL_BIT_NUM)))); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
	Reg_DMATRGSEL.unDMACSEL[t_u1DmaType][t_u1Register].u4Data = (uint32)(t_u4DmacSelReg | t_u4GroupData);

}
#endif

#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
#if ( DMA_CFG_REG_CHK == STD_ON )
/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Check Transfer Request Group Function													*/
/*	return		: Register error Status(NG(1) / OK(0))											*/
/*	parameters	: Request group number (0-1023)													*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
uint32	Pil_Dmac_CheckTransReqGroup( uint16 t_u2RequestGroup, uint8 t_u1DmaType)
{
	Pil_Dmac_RequestGroupType t_udRequestGroup;
	uint32 t_u4GroupData;
	uint32 t_u4DmacSelReg;
	uint8 t_u1RegReqSig;
	uint8 t_u1Register;
	uint32 t_u4Ret;

	t_u4Ret = DMA_REGCHK_OK;

	t_udRequestGroup.u2Data = t_u2RequestGroup;
	t_u1RegReqSig = (uint8)t_udRequestGroup.stDiv.b4RegReqSigNum;
	t_u1Register = (uint8)t_udRequestGroup.stDiv.b4RegNum;
	t_u4GroupData = (uint32)t_udRequestGroup.stDiv.b2Group;

	t_u4DmacSelReg = (uint32)((Reg_DMATRGSEL.unDMACSEL[t_u1DmaType][t_u1Register].u4Data >> (uint32)((uint32)t_u1RegReqSig * (uint32)DMA_DMAC_SEL_BIT_NUM))& (uint32)DMA_DMACSEL_SEL0); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */

	if((t_u4DmacSelReg != t_u4GroupData))
	{
#if ( DMA_CFG_REG_REFRESH == STD_ON )
		/* Rewrite */
		Pil_Dmac_SetTransReqGroup(t_u2RequestGroup,t_u1DmaType);
		/* ReCheck */
		t_u4DmacSelReg = (uint32)((Reg_DMATRGSEL.unDMACSEL[t_u1DmaType][t_u1Register].u4Data >> (uint32)((uint32)t_u1RegReqSig * (uint32)DMA_DMAC_SEL_BIT_NUM))& (uint32)DMA_DMACSEL_SEL0); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
		if((t_u4DmacSelReg != t_u4GroupData))
		{
			/* Register Fix */
			t_u4Ret |= DMA_REGCHK_REFRESH_FAILED;
		}
		else
		{
			/* Corrected */
			t_u4Ret |= DMA_REGCHK_REFRESH_SUCCESS;
		}
#else
		/* No Rewrite */
		t_u4Ret = DMA_REGCHK_NG;
#endif
	}

	return (t_u4Ret);
}

#if (MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B)
/*----------------------------------------------------------------------------------------------*/
/*	Service name	:	Check DMAC Redundant Channel Select Register							*/
/*	Parameters (in)	:	None																	*/
/*	Return value	:	Register error Status													*/
/*----------------------------------------------------------------------------------------------*/
uint32		Pil_Dmac_CheckRCHSReg( void )
{
	uint32 t_u4Ret;
	
	t_u4Ret = DMA_REGCHK_OK;
	
	if((Reg_DMAC0.unRCHS.u4Data != (uint32)0U))
	{
#if ( DMA_CFG_REG_REFRESH == STD_ON )
		/* Rewrite */
		Reg_DMAC0.unRCHS.u4Data = (uint32)0U;
		/* ReCheck */
		if((Reg_DMAC0.unRCHS.u4Data != (uint32)0U))
		{
			/* Register Fix */
			t_u4Ret |= DMA_REGCHK_REFRESH_FAILED;
		}
		else
		{
			/* Corrected */
			t_u4Ret |= DMA_REGCHK_REFRESH_SUCCESS;
		}
#else
		/* No Rewrite */
		t_u4Ret = DMA_REGCHK_NG;
#endif
	}	
		
#if (MCAL_PKG_TARGET != MCAL_PKG_U2B6_292PIN)
	if((Reg_DMAC1.unRCHS.u4Data != (uint32)0U))
	{
#if ( DMA_CFG_REG_REFRESH == STD_ON )
		/* Rewrite */
		Reg_DMAC1.unRCHS.u4Data = (uint32)0U;
		/* ReCheck */
		if((Reg_DMAC1.unRCHS.u4Data != (uint32)0U))
		{
			/* Register Fix */
			t_u4Ret |= DMA_REGCHK_REFRESH_FAILED;
		}
		else
		{
			/* Corrected */
			t_u4Ret |= DMA_REGCHK_REFRESH_SUCCESS;
		}
#else
		/* No Rewrite */
		t_u4Ret |= DMA_REGCHK_NG;
#endif
	}		
#endif
	return (t_u4Ret);
}
#endif
#endif
#endif

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC  RAM Clear Function																	*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
/*void	Pil_Dmac_ClearRam( void )""*/
/*{*/
/*	sint32		i";"*/

	/* Descriptor RAM */
/*	for( i = (sint32)0; i < (sint32)DMA_DMAC_DESCRIPTOR_NUM; i++ )""*/
/*	{*/
/*		Reg_DesRAM0.u4DesRAM[i] = (uint32)0";"*/
/*		Reg_DesRAM1.u4DesRAM[i] = (uint32)0";"*/
/*	}*/

/*}*/

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC  Set Master Channel Function															*/
/*	return		: none																			*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*----------------------------------------------------------------------------------------------*/
/*void	Pil_Dmac_SetMasterCh( uint8 t_u1ChannelID )""*/
/*{*/
	/* Set the SPID that the DMAC acting as the bus master calls itself. */
	/* No setting required because the guard setting of the guard control register is used with no effect. */
	/*Reg_DMAC0.unCM[t_u1ChannelID].u4Data = ( (uint32)DMA_CM_SPID_0 * u4PIL_DMAC0_SPIDNUM ) + ( (uint32)DMA_CM_UM * DMA_CM_UM_USER )";"*/
	/*Reg_DMAC1.unCM[t_u1ChannelID].u4Data = ( (uint32)DMA_CM_SPID_0 * u4PIL_DMAC1_SPIDNUM ) + ( (uint32)DMA_CM_UM * DMA_CM_UM_USER )";"*/
/*}*/

#if (( DMA_CFG_DMA0_ACCESS == STD_ON ) || ( DMA_CFG_DMA1_ACCESS == STD_ON ))
/*----------------------------------------------------------------------------------------------*/
/*	sDMAC  Set SPID for all Channels															*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_SetSpidAllCh(void)
{
	sint32		i;

	/* Set configured SPID value for all the channels */
	for( i = (sint32)0; i < (sint32)DMA_DMAC_CH_NUM; i++ )
	{
#if ( DMA_CFG_DMA0_ACCESS == STD_ON )
		Reg_DMAC0.unCM[i].u4Data = (uint32)( (uint32)DMA_CM_SPID_0 * (uint32)cu1Pil_Dma_Ucfg_Dmac0_ChSpidTable[i] ); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
#endif

#if ( DMA_CFG_DMA1_ACCESS == STD_ON )
		#if ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) || ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) && (MCAL_PKG_TARGET != MCAL_PKG_U2B6_292PIN)))
		Reg_DMAC1.unCM[i].u4Data = (uint32)( (uint32)DMA_CM_SPID_0 * (uint32)cu1Pil_Dma_Ucfg_Dmac1_ChSpidTable[i] ); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
		#endif
#endif
	}
}
#endif

#if (( DMA_CFG_DMA0_ACCESS == STD_ON ) || ( DMA_CFG_DMA1_ACCESS == STD_ON ))
#if ( DMA_CFG_REG_CHK == STD_ON )
/*----------------------------------------------------------------------------------------------*/
/*	DMAC ASIL Register Check Function															*/
/*	return		: Diagnosis result																*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
uint32	Pil_Dmac_CheckReg_ASIL(void)
{
	sint32		i;
	uint32  	t_u4SpidMask;
	uint32		t_u4Ret;

	t_u4Ret = DMA_REGCHK_OK;

	/* Set configured SPID value for all the channels */
	for( i = (sint32)0; i < (sint32)DMA_DMAC_CH_NUM; i++ )
	{
#if ( DMA_CFG_DMA0_ACCESS == STD_ON )
		t_u4SpidMask = (uint32)((uint32)DMA_CM_SPID_0 * (uint32)cu1Pil_Dma_Ucfg_Dmac0_ChSpidTable[i]); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */

		if ( t_u4SpidMask != (uint32)(Reg_DMAC0.unCM[i].u4Data & (uint32)DMA_CM_SPID ) )
		{
			t_u4Ret = DMA_REGCHK_NG;
			break;
		}
#endif

#if ( DMA_CFG_DMA1_ACCESS == STD_ON )
	#if ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) || ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) && (MCAL_PKG_TARGET != MCAL_PKG_U2B6_292PIN)))
		t_u4SpidMask = (uint32)((uint32)DMA_CM_SPID_0 * (uint32)cu1Pil_Dma_Ucfg_Dmac1_ChSpidTable[i]); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */

		if ( t_u4SpidMask != (uint32)(Reg_DMAC1.unCM[i].u4Data & (uint32)DMA_CM_SPID ) )
		{
			t_u4Ret = DMA_REGCHK_NG;
			break;
		}
	#endif
#endif
	}

	return (t_u4Ret);
}
#endif
#endif

#if (( DMA_CFG_DMA0_ACCESS == STD_ON ) || ( DMA_CFG_DMA1_ACCESS == STD_ON ))
/*----------------------------------------------------------------------------------------------*/
/*	sDMAC  Disable Trans All Function															*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_DisableTransAll( void )
{
	sint32		i;

	/* All DMA transfers disabled */
	/* sDMAC */
	for( i = (sint32)0; i < (sint32)DMA_DMAC_CH_NUM; i++ )
	{
#if ( DMA_CFG_DMA0_ACCESS == STD_ON )
		Reg_DMAC0.stDMAC_CH[i].unCHFCR.u4Data = ( ( (uint32)DMA_CHFCR_DPEC * (uint32)DMA_CHFCR_DPEC_CLEAR )		+	/* Descriptor invalidation */
												( (uint32)DMA_CHFCR_DEC * (uint32)DMA_CHFCR_DEC_CLEAR ) );			/* DMA Enable Clear */
#endif
#if ( DMA_CFG_DMA1_ACCESS == STD_ON )
		#if ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) || ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) && (MCAL_PKG_TARGET != MCAL_PKG_U2B6_292PIN)))
		Reg_DMAC1.stDMAC_CH[i].unCHFCR.u4Data = ( ( (uint32)DMA_CHFCR_DPEC * (uint32)DMA_CHFCR_DPEC_CLEAR )		+	/* Descriptor invalidation */
												( (uint32)DMA_CHFCR_DEC * (uint32)DMA_CHFCR_DEC_CLEAR ) );			/* DMA Enable Clear */
		#endif
#endif
	}
}
#endif

/*==============================================================================================*/
/*	Local Functions																				*/
/*==============================================================================================*/

#define DMA_STOP_SEC_TEXT_CODE
#include "Dma_MemMap.h"
/*-- End Of File -------------------------------------------------------------------------------*/
