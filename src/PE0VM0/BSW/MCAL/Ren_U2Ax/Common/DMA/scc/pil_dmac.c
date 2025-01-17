/* pil_dmac-r04-3000-0100-a-v01 */
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
#define		u1PIL_DMAC_MODE_NUM			((U1)7U)
#define		u1PIL_DMAC_DMAC0			((U1)0U)
#define		u1PIL_DMAC_TRANSSIZE_NUM	((U1)7U)
#define		u1PIL_DMAC_TRANSSIZE_1		((U1)1U)					/* 1byte  */
#define		u1PIL_DMAC_TRANSSIZE_2		((U1)2U)					/* 2byte  */
#define		u1PIL_DMAC_TRANSSIZE_4		((U1)4U)					/* 4byte  */
#define		u1PIL_DMAC_TRANSSIZE_8		((U1)8U)					/* 8byte  */
#define		u1PIL_DMAC_TRANSSIZE_16		((U1)16U)					/* 16byte */
#define		u1PIL_DMAC_TRANSSIZE_32		((U1)32U)					/* 32byte */
#define		u1PIL_DMAC_TRANSSIZE_64		((U1)64U)					/* 64byte */
#define		u1PIL_DMAC_TRANSMODE_2		((U1)2U)					/* Mode 2 Transfer */
#define		u2PIL_DMAC_DESRAM_ADDR_CH0	((U2)0U)					/* DMAC descriptor CH0 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH1	((U2)64U)					/* DMAC descriptor CH1 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH2	((U2)128U)					/* DMAC descriptor CH2 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH3	((U2)192U)					/* DMAC descriptor CH3 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH4	((U2)256U)					/* DMAC descriptor CH4 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH5	((U2)320U)					/* DMAC descriptor CH5 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH6	((U2)384U)					/* DMAC descriptor CH6 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH7	((U2)448U)					/* DMAC descriptor CH7 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH8	((U2)512U)					/* DMAC descriptor CH8 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH9	((U2)576U)					/* DMAC descriptor CH9 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH10	((U2)640U)					/* DMAC descriptor CH10 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH11	((U2)704U)					/* DMAC descriptor CH11 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH12	((U2)768U)					/* DMAC descriptor CH12 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH13	((U2)832U)					/* DMAC descriptor CH13 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH14	((U2)896U)					/* DMAC descriptor CH14 Pointer value of the head address */
#define		u2PIL_DMAC_DESRAM_ADDR_CH15	((U2)960U)					/* DMAC descriptor CH15 Pointer value of the head address */

typedef	union
{
	U2	u2Data;
	struct
	{
		U2	b4RegReqSigNum:4;   /* preferred request signal number in the register */
		U2	b4RegNum:4;			/* Register  Number */
		U2  b2Group:2; 			/* Group number */ 
		U2  b6Dummy:6;
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
static volatile const	U4		cu4PIL_DMAC_MODE_TABLE[u1PIL_DMAC_MODE_NUM] = {
	(U4)((U4)DMA_TMR_DM_0	*	(U4)DMA_TMR_DM_INCREMENT		+
		 (U4)DMA_TMR_SM_0	*	(U4)DMA_TMR_SM_FIX),				/* mode=0 : e.g. for RAM clear */
	(U4)((U4)DMA_TMR_DM_0	*	(U4)DMA_TMR_DM_INCREMENT		+
		 (U4)DMA_TMR_SM_0	*	(U4)DMA_TMR_SM_FIX),				/* mode=1 : e.g. for SPI(SCI) Receive, A/D Gated(No Reload) */
	(U4)((U4)DMA_TMR_DM_0	*	(U4)DMA_TMR_DM_FIX				+
		 (U4)DMA_TMR_SM_0	*	(U4)DMA_TMR_SM_INCREMENT),			/* mode=2 : e.g. for SPI(SCI) Send */
	(U4)((U4)DMA_TMR_DM_0	*	(U4)DMA_TMR_DM_INCREMENT		+
		 (U4)DMA_TMR_SM_0	*	(U4)DMA_TMR_SM_INCREMENT),			/* mode=3 : e.g. for A/D Scan */
	(U4)((U4)DMA_TMR_DM_0	*	(U4)DMA_TMR_DM_INCREMENT		+
		 (U4)DMA_TMR_SM_0	*	(U4)DMA_TMR_SM_FIX),				/* mode=4 : e.g. for A/D Gated(Reload) */
	(U4)((U4)DMA_TMR_DM_0	*	(U4)DMA_TMR_DM_INCREMENT		+
		 (U4)DMA_TMR_SM_0	*	(U4)DMA_TMR_SM_INCREMENT),			/* mode=5 : e.g. for A/D GatedMulti */
	(U4)((U4)DMA_TMR_DM_0	*	(U4)DMA_TMR_DM_FIX				+
		 (U4)DMA_TMR_SM_0	*	(U4)DMA_TMR_SM_FIX)					/* mode=6 : e.g. for SPI(Dummy) Send  Receive */
};

static volatile const U2 cu2Pil_Dmac0_IntcChannelID[DMA_DMAC_CH_NUM] = {
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
static volatile const U2 cu2Pil_Dmac1_IntcChannelID[DMA_DMAC_CH_NUM] = {
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
static volatile const	U1		cu1PIL_DMAC_TransSize[u1PIL_DMAC_TRANSSIZE_NUM] =
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
static volatile const	U2		cu2PIL_DMAC_DescriptorAdrrpNum[DMA_DMAC_CH_NUM] =
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
void	Pil_Dmac_EnableTrans( U1 t_u1ChannelID, U1 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	/* (4)  Transfer Status Clear */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data  =(U4)((U4)DMA_CHFCR_OVFC * (U4)DMA_CHFCR_OVFC_CLEAR + 
																(U4)DMA_CHFCR_DRQC * (U4)DMA_CHFCR_DRQC_CLEAR + 
																(U4)DMA_CHFCR_CAEC * (U4)DMA_CHFCR_CAEC_CLEAR + 
																(U4)DMA_CHFCR_DSEC * (U4)DMA_CHFCR_DSEC_CLEAR + 
																(U4)DMA_CHFCR_TEC  * (U4)DMA_CHFCR_TEC_CLEAR);

	/* DMA channel-stop register setting(Refresh) */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHSTP.u2Data = (U2)((U2)DMA_CHSTP_STP * (U2)DMA_CHSTP_STP_RESTART);

	/* DMA operation register setting */
	t_pstRegDmac->unOR.u2Data  =	(U2)((U2)DMA_OR_DME * (U2)DMA_OR_DME_TRANS_ENABLE +
												(U2)DMA_OR_PR_0 * (U2)DMA_OR_PR_CH);

	/* (5)  DMAC channel operation enable setting */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data |= (U2)((U2)DMA_CHCR_DE * (U2)DMA_CHCR_DE_ENABLE);
	Bswlib_Sync_Pipeline_2(t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data);			/* dummy read */
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Trans Disable Function																*/
/*	return		: void																			*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_DisableTrans( U1 t_u1ChannelID, U1 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data =(U4)((U4)DMA_CHFCR_DEC * (U4)DMA_CHFCR_DEC_CLEAR		+	/* DMA transfer request disabled */
															(U4)DMA_CHFCR_DPEC * (U4)DMA_CHFCR_DPEC_CLEAR);		/* Descriptor invalidation */
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
void	Pil_Dmac_SetTransMode( U1 t_u1ChannelID, U1 t_u1DmaType, U1 t_u1TransSize, U1 t_u1DmaMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum, U1 t_u1DmaReqNum )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;
	U4		t_u4Tmr;			/* TMR register setting value */
	U4		t_u4Rs;				/* RS register setting value */
	U2		t_u2Chcr;			/* CHCR register setting value */

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	/* DI_ALL()";" */ /* No interrupts are required because there is no use case for calling Enable, SetInterrupt, this function	*/
	                /*  from a high-priority task during SetTransMode for the same DMAC channel.								*/

	/* DMA channel master configuration is designed to be performed by ErrH, and DMAC requires no configuration process */
	/* because of the initial value expectations. 																		*/

    /* (1)  DMAC channel operation disabled setting */
	/* Clear the DE bit in the DMA channel control register following UM's DMA channel setup procedure. */
	/* The BUSY flag of the status is never set because API restrictions prevent calls to this API during DMA transfers. */
	/* So there's no logic to make sure the BUSY flag is cleared. */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data = (U4)((U4)DMA_CHFCR_DEC * (U4)DMA_CHFCR_DEC_CLEAR);

	/* (2)  Setting transfer information */
	/* In setting the transfer information of DMAC, set the following registers */
	/* DMAC source address register(DMAjSAR_n) */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4SAR = (U4)((volatile const U4*)t_pcvdSrcAdr);		/* Source address settings */
	/* DMAC destination address register(DMAjDAR_n) */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4DAR = (U4)((volatile const U4*)t_pcvdDestAdr);		/* Destination Address Configuration */
	/* DMAC transfer size register(DMAjTSR_n) */
	/* Find the transfer size setting from the transfer size */ /* Overall transfer size */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4TSR = (U4)( (U4)cu1PIL_DMAC_TransSize[t_u1TransSize] * (U4)t_u2TransNum ); /* justification for QAC warning 3384: it is not wrap-around within a configuration range */
	/* DMAC transfer mode register(DMAjTMR_n) */
	t_u4Tmr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unTMR.u4Data & ( (U4)~( (U4)DMA_TMR_TRS	+	(U4)DMA_TMR_DM	+	
					(U4)DMA_TMR_SM	+	(U4)DMA_TMR_SLM	+	(U4)DMA_TMR_PRI	+	(U4)DMA_TMR_DTS	+	(U4)DMA_TMR_STS ) ) );
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unTMR.u4Data = (U4)( t_u4Tmr |(U4)( (U4)DMA_TMR_TRS * (U4)DMA_TMR_TRS_HARDWARE_REQ		+	/* TRS=1:Hard request */ /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
				cu4PIL_DMAC_MODE_TABLE[t_u1DmaMode]					+		/* MODE setting table */
				(U4)DMA_TMR_SLM_0	*	(U4)DMA_TMR_SLM_NORMAL			+	/* SLM=0000:Normal mode(Slow mode not supported) */
				(U4)DMA_TMR_PRI_0	*	(U4)DMA_TMR_PRI_DISABLE			+		/* PRI=0:Channel request priority disabled */    /* justification for QAC warning 3384: it is not wrap-around within a configuration range */
				(U4)DMA_TMR_DTS_0	*	t_u1TransSize				+		/* DTS=Destination Transfer Size */         /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
				/* DMA_TMR_STS_0 is BIT0 and the result of multiplication is the same as t_u1TransSize. */
				/* Fix for QAC compatibility										*/
				/*(U4)DMA_TMR_STS_0	*	t_u1TransSize ) )";"	*/
				(U4)t_u1TransSize ) );											/* STS=Source Transfer Size */

	/* (3)  Setting DMA Transfer Requests */
	/* DMAC Resource Selection Register(DMAjRS_n) ※When using hardware transfer request mode */
	t_u4Rs = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unRS.u4Data;
	t_u4Rs &= (U4)( ~( (U4)DMA_RS_TC + (U4)DMA_RS_TL + (U4)DMA_RS_PLE + (U4)DMA_RS_DRQI + (U4)DMA_RS_RS ) );
	if ( t_u1DmaMode == (U1)DMA_DMAMODE0 )
	{	/* On block transfer */
		t_u4Rs |= ( ( (U4)DMA_RS_TL_0		*	(U4)DMA_RS_TL_TSR )				+		/* TL=010: DMAjTSR_ n.Transfer size specified by TSR  */
					( (U4)DMA_RS_PLE		*	(U4)DMA_RS_PLE_DISABLE )		+		/* PRT= Preload function not disabled so no setting required */
					( (U4)DMA_RS_DRQI		*	(U4)DMA_RS_DRQI_DISABLE )		+		/* PLE=0: Disabled */
					(U4)t_u1DmaReqNum );												/* Hardware factor number */
					/* ( (U4)DMA_RS_RS_0		*	(U4)t_u1DmaReqNum ) );	*/			/* Hardware factor number */
	}
	else
	{	/* On single transfer */
		t_u4Rs |= ( ( (U4)DMA_RS_TC_0		*	(U4)1U )						+		/* TC=1: Transfers per hardware request */
					( (U4)DMA_RS_TL_0		*	(U4)DMA_RS_TL_STS )				+		/* TL=000: DMAjTMR_n.STS x DMAjRS_ n.Transfer size specified by TC  */
					( (U4)DMA_RS_PLE		*	(U4)DMA_RS_PLE_DISABLE )		+		/* PRT= Preload function not disabled so no setting required */
					( (U4)DMA_RS_DRQI		*	(U4)DMA_RS_DRQI_DISABLE )		+		/* PLE=0: Disabled */
					(U4)t_u1DmaReqNum  );												/* Hardware factor number */
					/*( (U4)DMA_RS_RS_0		*	(U4)t_u1DmaReqNum ) );		*/			/* Hardware factor number */
	}
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unRS.u4Data = t_u4Rs;

	/* Since SetTransMode does not support transfer modes 3 and later, the DMA transfer completion interrupt is enabled and the descriptor end interrupt is disabled. */
	/* The AND with the inverted value is temporarily held to hold settings other than the specified bit.(It is an intended cast and can never be negative.) */
	t_u2Chcr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data & ( (U2)~( (U2)DMA_CHCR_DSIE + (U2)DMA_CHCR_IE + (U2)DMA_CHCR_DPE + (U2)DMA_CHCR_CAEE + (U2)DMA_CHCR_CAIE ) ) );
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data = (U2)( t_u2Chcr | (U2)(	(U2)DMA_CHCR_DSIE	* (U2)DMA_CHCR_DSIE_DISABLE	+		/* Descriptor End Interrupt Disabled */
																			(U2)DMA_CHCR_IE		* (U2)DMA_CHCR_IE_ENABLE	+	/* DMA Transfer Completion Interrupt Enabled */
																			(U2)DMA_CHCR_DPE	* (U2)DMA_CHCR_DPE_DISABLE 	+	/* Descriptor operation disabled */
																			(U2)DMA_CHCR_CAEE	* (U2)DMA_CHCR_CAEE_DISABLE	+	/* Channel address error notification disabled */
																			(U2)DMA_CHCR_CAIE	* (U2)DMA_CHCR_CAIE_DISABLE ));	/* Channel Address Error Interrupt Disabled */
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
void	Pil_Dmac_SetTransModeTwoStepReload( U1 t_u1ChannelID, U1 t_u1DmaType, U1 t_u1TransSize, U1 t_u1DmaMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum, U2 t_u2AddrReloadCnt, U1 t_u1DmaReqNum )
{
	/* Settings other than mode = 3 are currently not guaranteed to work, and the argument AddrReloadCnt is unused, but intentionally kept to match the interface of E1MS2. */

	volatile Reg_Dma_Type*	t_pstRegDmac;
	volatile Reg_Dram_Type*	t_pstRegDmacDesRAM;
	U4		t_u4Tmr;			/* TMR register setting value */
	U4		t_u4Rs;				/* RS register setting value */
	U2		t_u2Chcr;			/* CHCR register setting value */
	U4		t_u4Dpptr;			/* Dpptr register setting value */
	U4		t_u4Dpcr;			/* Dpcr register setting value */
	U2		t_u2DesCnt;			/* Descriptor counters */

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];
	t_pstRegDmacDesRAM = (volatile Reg_Dram_Type*)cstPil_DmacDesRAM_Reg[t_u1DmaType];		/* Discriptor RAM */

	/* DI_ALL()";" */ /* No interrupts are required because there is no use case for calling Enable, SetInterrupt, this function */
	                /* from a high-priority task during SetTransMode for the same DMAC channel.								   */

	/* DMA channel master configuration is designed to be performed by ErrH, and DMAC requires no configuration process */
	/* because of the initial value expectations. 																		*/

	/* (1)  DMAC channel operation disabled setting */
	/* Clear the DE bit in the DMA channel control register following UM's DMA channel setup procedure. */
	/* The BUSY flag of the status is never set because API restrictions prevent calls to this API during DMA transfers. */
	/* So there's no logic to make sure the BUSY flag is cleared. */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data = (U4)((U4)DMA_CHFCR_DEC * (U4)DMA_CHFCR_DEC_CLEAR);

	/* (2)  Setting transfer information */
	/* In setting the transfer information of DMAC, set the following registers */
	/* DMAC source address register(DMAjSAR_n) */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4SAR = (U4)((volatile const U4*)t_pcvdSrcAdr);		/* Source address settings */
	/* DMAC destination address register(DMAjDAR_n) */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4DAR = (U4)((volatile const U4*)t_pcvdDestAdr);		/* Destination Address Configuration */
	/* DMAC transfer size register(DMAjTSR_n) */
	/* Find the transfer size setting from the transfer size */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4TSR = ( (U4)cu1PIL_DMAC_TransSize[t_u1TransSize] * (U4)t_u2TransNum );	/* Overall transfer siz */		/* justification for QAC warning 3384: it is not wrap-around within a configuration range */
	/* DMAC transfer mode register(DMAjTMR_n) */
	t_u4Tmr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unTMR.u4Data & ( (U4)~( (U4)DMA_TMR_TRS	+	(U4)DMA_TMR_DM	+	
					(U4)DMA_TMR_SM	+	(U4)DMA_TMR_SLM	+	(U4)DMA_TMR_PRI	+	(U4)DMA_TMR_DTS	+	(U4)DMA_TMR_STS ) ) );
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unTMR.u4Data = (U4)( t_u4Tmr | (U4)( (U4)DMA_TMR_TRS * (U4)DMA_TMR_TRS_HARDWARE_REQ		+	/* TRS=1:Hard request */ /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
				cu4PIL_DMAC_MODE_TABLE[t_u1DmaMode]					+		/* MODE setting table */
				(U4)DMA_TMR_SLM_0	*	(U4)DMA_TMR_SLM_NORMAL			+		/* SLM=0000:Normal mode(Slow mode not supported) */
				(U4)DMA_TMR_PRI_0	*	(U4)DMA_TMR_PRI_DISABLE			+		/* PRI=0:Channel request priority disable */	/* justification for QAC warning 3384: it is not wrap-around within a configuration range */
				(U4)DMA_TMR_DTS_0	*	t_u1TransSize				+			/* DTS=Destination Transfer Size */	  /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
				/* Since DMA_TMR_STS_0 is BIT0, the result of multiplication is the same as t_u1TransSize 	*/
				/* Fix for QAC compatibility												*/
				/* (U4)DMA_TMR_STS_0	*	t_u1TransSize ) )";"	*/
				(U4)t_u1TransSize ) );											/* STS=Source Transfer Size */

	/* (3)  Setting DMA Transfer Requests */
	/* DMAC Resource Selection Register(DMAjRS_n) ※When using hardware transfer request mode */
	t_u4Rs = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unRS.u4Data & ( (U4)~( (U4)DMA_RS_TL + (U4)DMA_RS_PLE + (U4)DMA_RS_DRQI + (U4)DMA_RS_RS ) ) ) ;
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unRS.u4Data = (U4)( t_u4Rs | (U4)(	(U4)DMA_RS_TL_0	*	(U4)DMA_RS_TL_TSR		+	/* TL=010:Transfer size specified by DMAjTSR_n.TSR  */
				(U4)DMA_RS_PLE		*	(U4)DMA_RS_PLE_DISABLE			+			/* PLE=0:Preload function disabled */
				(U4)DMA_RS_DRQI		*	(U4)DMA_RS_DRQI_DISABLE			+		/* DRQI=0:DRQ initialization disabled */  /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
				/* Since DMA_RS_RS_0 is BIT0, the result of multiplication is the same as t_u1DmaReqNum */
				/* Fix for QAC compatibility											*/
				/* (U4)DMA_RS_RS_0		*	t_u1DmaReqNum ))";"	*/
				(U4)t_u1DmaReqNum ));										/* Hardware factor number */

	if(t_u1DmaMode > u1PIL_DMAC_TRANSMODE_2)
	{
		/* Only transfer mode 3 supported */

		/* Descriptor Settings */
		t_u4Dpcr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unDPCR.u4Data & ( (U4)~( (U4)DMA_DPCR_UPF ) ) );		/* Clear the settings of UPF 0 to UPF 10, which are valid bits */
		t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unDPCR.u4Data =  (U4)( t_u4Dpcr |
																(U4)( (U4)DMA_DPCR_UPF_0 * (U4)DMA_DPCR_UPF_SAR_ENABLE +	/* Source address register update flag */
																(U4)DMA_DPCR_UPF_1 * (U4)DMA_DPCR_UPF_DAR_ENABLE +			/* Destination address register update flag */
																(U4)DMA_DPCR_UPF_2 * (U4)DMA_DPCR_UPF_TSR_ENABLE +			/* Transfer size register update flag */
																(U4)DMA_DPCR_UPF_3 * (U4)DMA_DPCR_UPF_TMR_ENABLE ) );		/* Transfer mode register update flag */

		t_u2DesCnt=cu2PIL_DMAC_DescriptorAdrrpNum[t_u1ChannelID];			/* Initializing the descriptor counter */

		/* Descriptor Memory Settings */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = (U4)((volatile const U4*)t_pcvdSrcAdr);	/* DMAC source address register */
		t_u2DesCnt++;    /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = (U4)((volatile const U4*)t_pcvdDestAdr);	/* DMAC destination address register */
		t_u2DesCnt++;    /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = (U4)( (U4)cu1PIL_DMAC_TransSize[t_u1TransSize] * (U4)t_u2TransNum );	/* DMAC transfer size register */	/* justification for QAC warning 3384: it is not wrap-around within a configuration range */
		t_u2DesCnt++;	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unTMR.u4Data;				/* DMAC transfer mode register */
		t_u2DesCnt++;	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
		t_u4Dpptr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unDPPTR.u4Data & ( (U4)~( (U4)DMA_DPPTR_DIE + (U4)DMA_DPPTR_PTR + (U4)DMA_DPPTR_CF ) ) );
		t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unDPPTR.u4Data = (U4)( t_u4Dpptr |								/* Descriptor pointer register */
						(U4)( (U4)DMA_DPPTR_DIE	*	(U4)DMA_DPPTR_DIE_ENABLE	+								/* Descriptor End Interrupt Enabled */ /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
						(U4)DMA_DPPTR_PTR_0 *	cu2PIL_DMAC_DescriptorAdrrpNum[t_u1ChannelID]	+			/* Address pointer of next descriptor */	/* justification for QAC warning 3384: it is not wrap-around within a configuration range */
						(U4)DMA_DPPTR_CF	*	(U4)DMA_DPPTR_CF_ENABLE ) );								/* Descriptor continuation flag */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unDPPTR.u4Data;	/* Address pointer of descriptor */

		/* Setting the start of a descriptor */
		/* Transfer mode 3 disables the DMA transfer completion interrupt and enables the descriptor end interrupt. */
		/* The AND with the inverted value is temporarily held to hold settings other than the specified bit.(It is an intended cast and can never be negative.) */
		t_u2Chcr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data & ( (U2)~( (U2)DMA_CHCR_DPE + (U2)DMA_CHCR_DSIE + (U2)DMA_CHCR_IE + (U2)DMA_CHCR_DPB + (U2)DMA_CHCR_CAEE + (U2)DMA_CHCR_CAIE ) ) );
		t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data = (U2)( t_u2Chcr |(U2) (	(U2)DMA_CHCR_DPE	*	(U2)DMA_CHCR_DPE_ENABLE			+	/* Descriptor Action Enabled */
																				(U2)DMA_CHCR_DSIE	*	(U2)DMA_CHCR_DSIE_ENABLE		+	/* Descriptor End Interrupt Enabled */
																				(U2)DMA_CHCR_IE		*	(U2)DMA_CHCR_IE_DISABLE			+	/* DMA Transfer Completion Interrupt Disabled */
																				(U2)DMA_CHCR_DPB	*	(U2)DMA_CHCR_DPB_REGISTER_SET	+  	/* Start DMA transfer by register setting */
																				(U2)DMA_CHCR_CAEE	*	(U2)DMA_CHCR_CAEE_DISABLE		+	/* Channel address error notification disabled */
																				(U2)DMA_CHCR_CAIE	*	(U2)DMA_CHCR_CAIE_DISABLE ));		/* Channel address error interrupt disabled */
	}
	else
	{
		/* DMA transfer completion interrupt is enabled except for transfer mode 3, and descriptor end interrupt is disabled. */
		/* In order to retain settings other than the specified bit, it is kept temporarily by taking AND with the inverted value. (Intended cast, never negative) */
		t_u2Chcr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data & ( (U2)~( (U2)DMA_CHCR_DSIE + (U2)DMA_CHCR_IE + (U2)DMA_CHCR_DPE + (U2)DMA_CHCR_CAEE + (U2)DMA_CHCR_CAIE ) ) );
		t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data = (U2)( t_u2Chcr|(U2)(	(U2)DMA_CHCR_DSIE	* (U2)DMA_CHCR_DSIE_DISABLE		+		/* Descriptor End Interrupt Disabled */
																				(U2)DMA_CHCR_IE		* (U2)DMA_CHCR_IE_ENABLE		+			/* DMA transfer completion interrupt enabled */
																				(U2)DMA_CHCR_DPE	* (U2)DMA_CHCR_DPE_DISABLE 		+		/* Descriptor operation disabled */
																				(U2)DMA_CHCR_CAEE	* (U2)DMA_CHCR_CAEE_DISABLE		+		/* Channel address error notification disabled */
																				(U2)DMA_CHCR_CAIE	* (U2)DMA_CHCR_CAIE_DISABLE ));			/* Channel address error interrupt disabled */
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
void	Pil_Dmac_SetInterrupt( U1 t_u1ChannelID, U1 t_u1DmaType, U1 t_u1EndIe )
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
U1		Pil_Dmac_IsTransferCompleted( U1 t_u1ChannelID, U1 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;
	U4		t_u4Chsta;
	U1		t_u1Ret;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	t_u1Ret = (U1)FALSE;

	t_u4Chsta = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHSTA.u4Data;

	if( (t_u4Chsta & (U4)DMA_CHSTA_TE) != (U4)DMA_CHSTA_TE_RUNNING )
	{
		t_u1Ret = (U1)TRUE;
	}

	return( t_u1Ret );
}

/*----------------------------------------------------------------------------------------------*/
/*	Compare Match Status Clear Function															*/
/*	return		: void																			*/
/*	parameters	: DMAC Channel(0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_ClearMatchStatus( U1 t_u1ChannelID, U1 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;

	DMA_ENTER_CRITICAL_SECTION();
	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];
	
	/* The interrupt request flag is cleared by clearing the DSE and TE flags. */
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data = (U4)((U4)DMA_CHFCR_DSEC * (U4)DMA_CHFCR_DSEC_CLEAR +
															(U4)DMA_CHFCR_TEC  * (U4)DMA_CHFCR_TEC_CLEAR);
	Bswlib_Sync_Pipeline_4( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data );
	DMA_EXIT_CRITICAL_SECTION();
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Destination Adrress Get Function														*/
/*	return		: Destination Address															*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
void*	Pil_Dmac_GetDestinationAddress( U1 t_u1ChannelID, U1 t_u1DmaType )
{

	volatile Reg_Dma_Type*	t_pstRegDmac;
	U4* t_pu4DestAdr;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];
	t_pu4DestAdr = (U4*)(t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4DAR);

	return ( (void*)t_pu4DestAdr);
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Trans Count Get Function																*/
/*	return		: Trans Count																	*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
U2		Pil_Dmac_GetTransCount( U1 t_u1ChannelID, U1 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;
	U2		t_u2Count;
	U4		t_u4Chsta;
	U1		t_u1TmrSts;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	/* Calculate number of transfers from DMA transfer size register and transfer size per transfer */
	t_u1TmrSts = (U1)(t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unTMR.stBit.b4STS);
	t_u2Count = (U2)( (t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4TSR + (U4)(cu1PIL_DMAC_TransSize[t_u1TmrSts] - (U4)1)) >> (U4)t_u1TmrSts );  /* justification for QAC warning 3384: it is not wrap-around within a configuration range */

	t_u4Chsta = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHSTA.u4Data;

	/* If the number of transfers remaining is 0 and the cycle is running, 1 is added and returned. */
	/* Even if the calculated transfer count is 0, the cycle execution may not be completed. */
	if ( ( t_u2Count == (U2)0 )
  	&& ( ( t_u4Chsta & (U4)DMA_CHSTA_BUSY ) != (U4)DMA_CHSTA_BUSY_IDLE  ) )
	{
		t_u2Count++;     /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
	}

	return( t_u2Count );
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Trans Count Reset Function															*/
/*	return		: none																			*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_ResetTransCount( U1 t_u1ChannelID, U1 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4TSR = (U4)0;
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Trans Status Get Function																*/
/*	return		: Trans Status ( =0:IDLE / =1:BUSY)												*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
U1		Pil_Dmac_GetTransStatus( U1 t_u1ChannelID, U1 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;
	U4		t_u4Chsta;
	U1		t_u1TransStat;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	t_u1TransStat = (U1)DMA_CHSTA_BUSY_IDLE;

	t_u4Chsta = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHSTA.u4Data;

	if( (t_u4Chsta & (U4)DMA_CHSTA_BUSY) != (U4)DMA_CHSTA_BUSY_IDLE )
	{
		t_u1TransStat = (U1)DMA_CHSTA_BUSY_BUSY;
	}

	return( t_u1TransStat );
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Error Check Function																	*/
/*	return		: Error Status																	*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
ZORN	Pil_Dmac_CheckDmaError( U1 t_u1ChannelID, U1 t_u1DmaType )
{
	/* Check if specified DMAC CH has an address error */
	volatile Reg_Dma_Type*	t_pstRegDmac;
	U4	t_u4Rtn;			/* Status values */

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	t_u4Rtn = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHSTA.u4Data & (U4)DMA_CHSTA_CAE;

	return ( (ZORN)t_u4Rtn );
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Error Status Clear Function															*/
/*	return		: none																			*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_ClearDmaError( U1 t_u1ChannelID, U1 t_u1DmaType )
{
	/* Clear address error flag for specified DMAC CH */
	volatile Reg_Dma_Type*	t_pstRegDmac;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data = ( (U4)DMA_CHFCR_DEC * (U4)DMA_CHFCR_DEC_CLEAR ) +	/* DMA transfer request disabled */
															( (U4)DMA_CHFCR_CAEC * (U4)DMA_CHFCR_CAEC_CLEAR );	/* Clear the address error flag */
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Reload Status Get Function															*/
/*	return		: Trans Status ( =0:RUN / =1:STOP)												*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
U1		Pil_Dmac_GetReloadStatus( U1 t_u1ChannelID, U1 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;
	U4		t_u4Chsta;
	U1		t_u1TransStat;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	t_u1TransStat = (U1)DMA_CHSTA_DSE_RUNNING;

	t_u4Chsta = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHSTA.u4Data;

	if( (t_u4Chsta & (U4)DMA_CHSTA_DSE) != (U4)( (U4)DMA_CHSTA_DSE * (U4)DMA_CHSTA_DSE_RUNNING ) )
	{
		t_u1TransStat = (U1)DMA_CHSTA_DSE_STOP;
	}

	return( t_u1TransStat );
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Reload Step End Flag Clear  Function 													*/
/*	return		: void																			*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_ClearReloadStatus( U1 t_u1ChannelID, U1 t_u1DmaType )
{
	volatile Reg_Dma_Type*	t_pstRegDmac;

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_Dmac_Reg[t_u1DmaType];

	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHFCR.u4Data = (U4)((U4)DMA_CHFCR_DSEC * (U4)DMA_CHFCR_DSEC_CLEAR);
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC SET Transfer Request Group Function													*/
/*	return		: none																			*/
/*	parameters	: Request group number (0-1023)													*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_SetTransReqGroup( U2 t_u2RequestGroup, U1 t_u1DmaType)
{
	Pil_Dmac_RequestGroupType t_udRequestGroup;
	U4 t_u4GroupData;
	U4 t_u4DmacSelReg;
	U1 t_u1RegReqSig;
	U1 t_u1Register;

	t_udRequestGroup.u2Data = t_u2RequestGroup;
	t_u1RegReqSig = (U1)t_udRequestGroup.stDiv.b4RegReqSigNum;
	t_u1Register = (U1)t_udRequestGroup.stDiv.b4RegNum;
	t_u4GroupData = (U4)t_udRequestGroup.stDiv.b2Group;

	t_u4GroupData = (U4)(t_u4GroupData << (U4)((U4)t_u1RegReqSig * (U4)DMA_DMAC_SEL_BIT_NUM));  /* justification for QAC warning 3383: it is not wrap-around within a configuration range */

	t_u4DmacSelReg = (U4)(Reg_DMATRGSEL.unDMACSEL[t_u1DmaType][t_u1Register].u4Data & (U4)(~(U4)((U4)DMA_DMACSEL_SEL0 << ((U4)t_u1RegReqSig * (U4)DMA_DMAC_SEL_BIT_NUM)))); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
	Reg_DMATRGSEL.unDMACSEL[t_u1DmaType][t_u1Register].u4Data = (U4)(t_u4DmacSelReg | t_u4GroupData);

}

#if ( DMA_CFG_REG_CHK == STD_ON ) 
/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Check Transfer Request Group Function													*/
/*	return		: Register error Status(NG(1) / OK(0))											*/
/*	parameters	: Request group number (0-1023)													*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*----------------------------------------------------------------------------------------------*/
U4	Pil_Dmac_CheckTransReqGroup( U2 t_u2RequestGroup, U1 t_u1DmaType)
{
	Pil_Dmac_RequestGroupType t_udRequestGroup;
	U4 t_u4GroupData;
	U4 t_u4DmacSelReg;
	U1 t_u1RegReqSig;
	U1 t_u1Register;
	U4 t_u4Ret;

	t_u4Ret = DMA_REGCHK_OK;

	t_udRequestGroup.u2Data = t_u2RequestGroup;
	t_u1RegReqSig = (U1)t_udRequestGroup.stDiv.b4RegReqSigNum;
	t_u1Register = (U1)t_udRequestGroup.stDiv.b4RegNum;
	t_u4GroupData = (U4)t_udRequestGroup.stDiv.b2Group;

	t_u4DmacSelReg = (U4)((Reg_DMATRGSEL.unDMACSEL[t_u1DmaType][t_u1Register].u4Data >> (U4)((U4)t_u1RegReqSig * (U4)DMA_DMAC_SEL_BIT_NUM))& (U4)DMA_DMACSEL_SEL0); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */

	if((t_u4DmacSelReg != t_u4GroupData))
	{
#if ( DMA_CFG_REG_REFRESH == STD_ON ) 
		/* Rewrite */
		Pil_Dmac_SetTransReqGroup(t_u2RequestGroup,t_u1DmaType);
		/* ReCheck */
		t_u4DmacSelReg = (U4)((Reg_DMATRGSEL.unDMACSEL[t_u1DmaType][t_u1Register].u4Data >> (U4)((U4)t_u1RegReqSig * (U4)DMA_DMAC_SEL_BIT_NUM))& (U4)DMA_DMACSEL_SEL0); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
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
U4		Pil_Dmac_CheckRCHSReg( void )
{
	U4 t_u4Ret;
	
	t_u4Ret = DMA_REGCHK_OK;
	
	if((Reg_DMAC0.unRCHS.u4Data != (U4)0U))
	{
#if ( DMA_CFG_REG_REFRESH == STD_ON ) 
		/* Rewrite */
		Reg_DMAC0.unRCHS.u4Data = (U4)0U;
		/* ReCheck */
		if((Reg_DMAC0.unRCHS.u4Data != (U4)0U))
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
	if((Reg_DMAC1.unRCHS.u4Data != (U4)0U))
	{
#if ( DMA_CFG_REG_REFRESH == STD_ON ) 
		/* Rewrite */
		Reg_DMAC1.unRCHS.u4Data = (U4)0U;
		/* ReCheck */
		if((Reg_DMAC1.unRCHS.u4Data != (U4)0U))
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

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC  RAM Clear Function																	*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
/*void	Pil_Dmac_ClearRam( void )""*/
/*{*/
/*	S4		i";"*/

	/* Descriptor RAM */
/*	for( i = (S4)0; i < (S4)DMA_DMAC_DESCRIPTOR_NUM; i++ )""*/
/*	{*/
/*		Reg_DesRAM0.u4DesRAM[i] = (U4)0";"*/
/*		Reg_DesRAM1.u4DesRAM[i] = (U4)0";"*/
/*	}*/

/*}*/

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC  Set Master Channel Function															*/
/*	return		: none																			*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*----------------------------------------------------------------------------------------------*/
/*void	Pil_Dmac_SetMasterCh( U1 t_u1ChannelID )""*/
/*{*/
	/* Set the SPID that the DMAC acting as the bus master calls itself. */
	/* No setting required because the guard setting of the guard control register is used with no effect. */
	/*Reg_DMAC0.unCM[t_u1ChannelID].u4Data = ( (U4)DMA_CM_SPID_0 * u4PIL_DMAC0_SPIDNUM ) + ( (U4)DMA_CM_UM * DMA_CM_UM_USER )";"*/
	/*Reg_DMAC1.unCM[t_u1ChannelID].u4Data = ( (U4)DMA_CM_SPID_0 * u4PIL_DMAC1_SPIDNUM ) + ( (U4)DMA_CM_UM * DMA_CM_UM_USER )";"*/
/*}*/

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC  Disable Trans All Function															*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_DisableTransAll( void )
{
	S4		i;

	/* All DMA transfers disabled */
	/* sDMAC */
	for( i = (S4)0; i < (S4)DMA_DMAC_CH_NUM; i++ )
	{
		Reg_DMAC0.stDMAC_CH[i].unCHFCR.u4Data = ( ( (U4)DMA_CHFCR_DPEC * (U4)DMA_CHFCR_DPEC_CLEAR )		+	/* Descriptor invalidation */
												( (U4)DMA_CHFCR_DEC * (U4)DMA_CHFCR_DEC_CLEAR ) );			/* DMA Enable Clear */
		#if ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) || ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) && (MCAL_PKG_TARGET != MCAL_PKG_U2B6_292PIN)))
		Reg_DMAC1.stDMAC_CH[i].unCHFCR.u4Data = ( ( (U4)DMA_CHFCR_DPEC * (U4)DMA_CHFCR_DPEC_CLEAR )		+	/* Descriptor invalidation */
												( (U4)DMA_CHFCR_DEC * (U4)DMA_CHFCR_DEC_CLEAR ) );			/* DMA Enable Clear */
		#endif
	}
}

/*==============================================================================================*/
/*	Local Functions																				*/
/*==============================================================================================*/

#define DMA_STOP_SEC_TEXT_CODE
#include "Dma_MemMap.h"
/*-- End Of File -------------------------------------------------------------------------------*/
