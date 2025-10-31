/* pil_dmac-rA4-3000-0100-a-v01 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/U2A : DMA Desc Extension Interface                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Dma_Desc.h"
#include	"pil_dmac_desc.h"

#include	"reg_dma.h"

/*==============================================================================================*/
/*	prototypes																					*/
/*==============================================================================================*/
/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
#define		u1PIL_DMAC_DESC_MODE_NUM			((U1)DMA_DESCMODE_NUM)
#define		u1PIL_DMAC_DESC_TRANSSIZE_NUM	    ((U1)7U)
#define		u1PIL_DMAC_DESC_TRANSSIZE_1		    ((U1)1U)	                   /* 1byte  */
#define		u1PIL_DMAC_DESC_TRANSSIZE_2		    ((U1)2U)	                   /* 2byte  */
#define		u1PIL_DMAC_DESC_TRANSSIZE_4		    ((U1)4U)	                   /* 4byte  */
#define		u1PIL_DMAC_DESC_TRANSSIZE_8		    ((U1)8U)	                   /* 8byte  */
#define		u1PIL_DMAC_DESC_TRANSSIZE_16		((U1)16U)	                   /* 16byte */
#define		u1PIL_DMAC_DESC_TRANSSIZE_32		((U1)32U)	                   /* 32byte */
#define		u1PIL_DMAC_DESC_TRANSSIZE_64		((U1)64U)	                   /* 64byte */
#define		u1PIL_DMAC_DESC_TRANSMODE_2		    ((U1)2U)	                   /* Mode 2 Transfer */
#define		u2PIL_DMAC_DESC_DESRAM_ADDR_CH0	    (u2_DMAC_DESC_RAM_ADDR_0_0)	   /* DMAC descriptor CH0  Pointer value of the head address */
#define		u2PIL_DMAC_DESC_DESRAM_ADDR_CH1	    (u2_DMAC_DESC_RAM_ADDR_0_1)	   /* DMAC descriptor CH1  Pointer value of the head address */
#define		u2PIL_DMAC_DESC_DESRAM_ADDR_CH2	    (u2_DMAC_DESC_RAM_ADDR_0_2)	   /* DMAC descriptor CH2  Pointer value of the head address */
#define		u2PIL_DMAC_DESC_DESRAM_ADDR_CH3	    (u2_DMAC_DESC_RAM_ADDR_0_3)	   /* DMAC descriptor CH3  Pointer value of the head address */
#define		u2PIL_DMAC_DESC_DESRAM_ADDR_CH4	    (u2_DMAC_DESC_RAM_ADDR_0_4)	   /* DMAC descriptor CH4  Pointer value of the head address */
#define		u2PIL_DMAC_DESC_DESRAM_ADDR_CH5	    (u2_DMAC_DESC_RAM_ADDR_0_5)	   /* DMAC descriptor CH5  Pointer value of the head address */
#define		u2PIL_DMAC_DESC_DESRAM_ADDR_CH6	    (u2_DMAC_DESC_RAM_ADDR_0_6)	   /* DMAC descriptor CH6  Pointer value of the head address */
#define		u2PIL_DMAC_DESC_DESRAM_ADDR_CH7	    (u2_DMAC_DESC_RAM_ADDR_0_7)	   /* DMAC descriptor CH7  Pointer value of the head address */
#define		u2PIL_DMAC_DESC_DESRAM_ADDR_CH8	    (u2_DMAC_DESC_RAM_ADDR_0_8)	   /* DMAC descriptor CH8  Pointer value of the head address */
#define		u2PIL_DMAC_DESC_DESRAM_ADDR_CH9	    (u2_DMAC_DESC_RAM_ADDR_0_9)	   /* DMAC descriptor CH9  Pointer value of the head address */
#define		u2PIL_DMAC_DESC_DESRAM_ADDR_CH10	(u2_DMAC_DESC_RAM_ADDR_0_10)   /* DMAC descriptor CH10 Pointer value of the head address */
#define		u2PIL_DMAC_DESC_DESRAM_ADDR_CH11	(u2_DMAC_DESC_RAM_ADDR_0_11)   /* DMAC descriptor CH11 Pointer value of the head address */
#define		u2PIL_DMAC_DESC_DESRAM_ADDR_CH12	(u2_DMAC_DESC_RAM_ADDR_0_12)   /* DMAC descriptor CH12 Pointer value of the head address */
#define		u2PIL_DMAC_DESC_DESRAM_ADDR_CH13	(u2_DMAC_DESC_RAM_ADDR_0_13)   /* DMAC descriptor CH13 Pointer value of the head address */
#define		u2PIL_DMAC_DESC_DESRAM_ADDR_CH14	(u2_DMAC_DESC_RAM_ADDR_0_14)   /* DMAC descriptor CH14 Pointer value of the head address */
#define		u2PIL_DMAC_DESC_DESRAM_ADDR_CH15	(u2_DMAC_DESC_RAM_ADDR_0_15)   /* DMAC descriptor CH15 Pointer value of the head address */   
/*==============================================================================================*/
/*	constants																					*/
/*==============================================================================================*/
#pragma ghs section rodata=".DMA_DESC_RODATA_CONST"

/* MODE setting table *******************************/
/* mode= 0: Dst Addr fixed, Src Addr increased		*/
/* mode= 1: Dst Addr fixed, Src Addr increased		*/
/* mode= 2: Dst Addr fixed, Src Addr fixed			*/
/****************************************************/
static volatile const	U4		cu4PIL_DMAC_DESC_MODE_TABLE[u1PIL_DMAC_DESC_MODE_NUM] = {
	(U4)((U4)DMA_TMR_DM_0	*	(U4)DMA_TMR_DM_FIX				+
		 (U4)DMA_TMR_SM_0	*	(U4)DMA_TMR_SM_INCREMENT),			/* mode=0 : e.g. for Sound data Send to CH P, disable descriptor step end interrupt */
	(U4)((U4)DMA_TMR_DM_0	*	(U4)DMA_TMR_DM_FIX				+
		 (U4)DMA_TMR_SM_0	*	(U4)DMA_TMR_SM_INCREMENT),			/* mode=1 : e.g. for Sound data Send to CH N, enable descriptor step end interrupt */
	(U4)((U4)DMA_TMR_DM_0	*	(U4)DMA_TMR_DM_FIX				+
		 (U4)DMA_TMR_SM_0	*	(U4)DMA_TMR_SM_FIX)					/* mode=2 : e.g. for Sound rewrite trigger Send */

};

/* The following static tables use the tables from the standard MCAL's pil_dmac.c.*/
/* Addresses are not sequential, so they correspond in tables */
static volatile Reg_Dma_Type* const cstPil_DMAC_DESC_Reg[DMA_DMAC_UNIT_NUM] = {
		&Reg_DMAC0
		#if ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) || ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) && (MCAL_PKG_TARGET != MCAL_PKG_U2B6_292PIN)))
		,&Reg_DMAC1
		#endif
};

static volatile Reg_Dram_Type* const cstPil_DMAC_DESC_DesRAM_Reg[DMA_DMAC_UNIT_NUM] = {
		&Reg_DesRAM0
		#if ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2A) || ((MCAL_SPAL_TARGET == MCAL_TARGET_RH850U2B) && (MCAL_PKG_TARGET != MCAL_PKG_U2B6_292PIN)))
		,&Reg_DesRAM1		
		#endif
};
/* DMAC source transfer size */
static volatile const	U1		cu1PIL_DMAC_DESC_TransSize[u1PIL_DMAC_DESC_TRANSSIZE_NUM] =
{
	u1PIL_DMAC_DESC_TRANSSIZE_1
	,u1PIL_DMAC_DESC_TRANSSIZE_2
	,u1PIL_DMAC_DESC_TRANSSIZE_4
	,u1PIL_DMAC_DESC_TRANSSIZE_8
	,u1PIL_DMAC_DESC_TRANSSIZE_16
	,u1PIL_DMAC_DESC_TRANSSIZE_32
	,u1PIL_DMAC_DESC_TRANSSIZE_64
};

/* DMAC descriptor address pointer value(Leading address pointer value per channel) */
static volatile const	U2		cu2PIL_DMAC_DESC_DescriptorAdrrpNum[DMA_DMAC_CH_NUM] =
{
	u2PIL_DMAC_DESC_DESRAM_ADDR_CH0		    /* CH0  */
	,u2PIL_DMAC_DESC_DESRAM_ADDR_CH1		/* CH1  */
	,u2PIL_DMAC_DESC_DESRAM_ADDR_CH2		/* CH2  */
	,u2PIL_DMAC_DESC_DESRAM_ADDR_CH3		/* CH3  */
	,u2PIL_DMAC_DESC_DESRAM_ADDR_CH4		/* CH4  */
	,u2PIL_DMAC_DESC_DESRAM_ADDR_CH5		/* CH5  */
	,u2PIL_DMAC_DESC_DESRAM_ADDR_CH6		/* CH6  */
	,u2PIL_DMAC_DESC_DESRAM_ADDR_CH7		/* CH7  */
	,u2PIL_DMAC_DESC_DESRAM_ADDR_CH8		/* CH8  */
	,u2PIL_DMAC_DESC_DESRAM_ADDR_CH9		/* CH9  */
	,u2PIL_DMAC_DESC_DESRAM_ADDR_CH10	    /* CH10 */
	,u2PIL_DMAC_DESC_DESRAM_ADDR_CH11	    /* CH11 */
	,u2PIL_DMAC_DESC_DESRAM_ADDR_CH12	    /* CH12 */
	,u2PIL_DMAC_DESC_DESRAM_ADDR_CH13	    /* CH13 */
	,u2PIL_DMAC_DESC_DESRAM_ADDR_CH14	    /* CH14 */
	,u2PIL_DMAC_DESC_DESRAM_ADDR_CH15	    /* CH15 */
};

#pragma ghs section rodata=default
/*==============================================================================================*/
/*	variables																					*/
/*==============================================================================================*/
/*==============================================================================================*/
/* functions																					*/
/*==============================================================================================*/
#pragma ghs section text=".DMA_DESC_TEXT_CODE"

/*----------------------------------------------------------------------------------------------*/
/* API Functions                                                                                */
/*----------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Trans Mode (Double buffer Reload) Set Function										*/
/*	return		: void																			*/
/*	parameters	: DMAC ChannelID (0-15) 														*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*				: TransSize (SIZE_1/SIZE_2/SIZE_4)												*/
/*				: DmaMode (0-2)																	*/
/*				: SrcAdr(Async) (Pointer to Source Adrress)										*/
/*				: DestAdr(Async) (Pointer to Destination Adrress)								*/
/*				: TransNum (Number of transfers until second reload)							*/
/*				: ReloadPtr (Descriptor pointer reloaded at first								*/
/*				: DmaReqNum (Reqest number)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_SetTransModeDoubleBufferReload( U1 t_u1ChannelID, U1 t_u1DmaType, U1 t_u1TransSize, U1 t_u1DescMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum, U2 t_u2ReloadPtr, U1 t_u1DmaReqNum )
{
	/* Settings except 0,1 or 2 are currently not guaranteed to work */

	volatile Reg_Dma_Type*	t_pstRegDmac;
	volatile Reg_Dram_Type*	t_pstRegDmacDesRAM;
	U4		t_u4Tmr;			/* TMR register setting value */
	U4		t_u4Rs;				/* RS register setting value */
	U2		t_u2Chcr;			/* CHCR register setting value */
	U4		t_u4Dpptr;			/* Dpptr register setting value */
	U4		t_u4Dpcr;			/* Dpcr register setting value */
	U2		t_u2DesCnt;			/* Descriptor counters */
	U2		t_u2DesIntFlg;		/* Descriptor step end interrupt flag (u2) */

	t_pstRegDmac = (volatile Reg_Dma_Type*)cstPil_DMAC_DESC_Reg[t_u1DmaType];
	t_pstRegDmacDesRAM = (volatile Reg_Dram_Type*)cstPil_DMAC_DESC_DesRAM_Reg[t_u1DmaType];		/* Discriptor RAM */

	/* DI_ALL()";" */ /* No interrupts are required because there is no use case for calling Enable, SetInterrupt, this function */
	                  /* from a high-priority task during SetTransMode for the same DMAC channel.								 */

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
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].u4TSR = ( (U4)cu1PIL_DMAC_DESC_TransSize[t_u1TransSize] * (U4)t_u2TransNum );	/* Overall transfer siz */		     /* justification for QAC warning 3384: it is not wrap-around within a configuration range */
	/* DMAC transfer mode register(DMAjTMR_n) */
	t_u4Tmr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unTMR.u4Data & ( (U4)~( (U4)DMA_TMR_TRS	+	(U4)DMA_TMR_DM	+	
					(U4)DMA_TMR_SM	+	(U4)DMA_TMR_SLM	+	(U4)DMA_TMR_PRI	+	(U4)DMA_TMR_DTS	+	(U4)DMA_TMR_STS ) ) );
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unTMR.u4Data = (U4)( t_u4Tmr | (U4)( (U4)DMA_TMR_TRS * (U4)DMA_TMR_TRS_HARDWARE_REQ		+	/* TRS=1:Hard request */ /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
				cu4PIL_DMAC_DESC_MODE_TABLE[t_u1DescMode]			+	    /* MODE setting table */
				(U4)DMA_TMR_SLM_0	*	(U4)DMA_TMR_SLM_NORMAL		+		/* SLM=0000:Normal mode(Slow mode not supported) */
				(U4)DMA_TMR_PRI_0	*	(U4)DMA_TMR_PRI_DISABLE		+		/* PRI=0:Channel request priority disable */	/* justification for QAC warning 3384: it is not wrap-around within a configuration range */
				(U4)DMA_TMR_DTS_0	*	t_u1TransSize				+		/* DTS=Destination Transfer Size */	            /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
				/* Since DMA_TMR_STS_0 is BIT0, the result of multiplication is the same as t_u1TransSize 	*/
				/* Fix for QAC compatibility												                */
				/* (U4)DMA_TMR_STS_0	*	t_u1TransSize ) )";"	*/
				(U4)t_u1TransSize ) );											/* STS=Source Transfer Size */

	/* (3)  Setting DMA Transfer Requests */
	/* DMAC Resource Selection Register(DMAjRS_n), When using hardware transfer request mode */
	t_u4Rs = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unRS.u4Data;
	t_u4Rs &= (U4)( ~( (U4)DMA_RS_TC + (U4)DMA_RS_TL + (U4)DMA_RS_PLE + (U4)DMA_RS_DRQI + (U4)DMA_RS_RS ) );
	if ( (t_u1DescMode == (U1)DMA_DESCMODE0) || (t_u1DescMode == (U1)DMA_DESCMODE1) || (t_u1DescMode == (U1)DMA_DESCMODE2) )
	{	/* On single transfer */
		t_u4Rs |= ( ( (U4)DMA_RS_TC_0		*	(U4)1U )						+		/* TC=1: Transfers per hardware request */
					( (U4)DMA_RS_TL_0		*	(U4)DMA_RS_TL_STS )				+		/* TL=000: DMAjTMR_n.STS x DMAjRS_n.Transfer size specified by TC  */
					( (U4)DMA_RS_PLE		*	(U4)DMA_RS_PLE_DISABLE )		+		/* PRT= Preload function not disabled so no setting required */
					( (U4)DMA_RS_DRQI		*	(U4)DMA_RS_DRQI_DISABLE )		+		/* PLE=0: Disabled */
					(U4)t_u1DmaReqNum  );												/* Hardware factor number */
					/*( (U4)DMA_RS_RS_0		*	(U4)t_u1DmaReqNum ) );		*/			/* Hardware factor number */
	}
	else
	{	/* On block transfer */
		t_u4Rs |= ( ( (U4)DMA_RS_TL_0		*	(U4)DMA_RS_TL_TSR )				+		/* TL=010: DMAjTSR_ n.Transfer size specified by TSR  */
					( (U4)DMA_RS_PLE		*	(U4)DMA_RS_PLE_DISABLE )		+		/* PRT= Preload function not disabled so no setting required */
					( (U4)DMA_RS_DRQI		*	(U4)DMA_RS_DRQI_DISABLE )		+		/* PLE=0: Disabled */
					(U4)t_u1DmaReqNum );												/* Hardware factor number */
					/* ( (U4)DMA_RS_RS_0		*	(U4)t_u1DmaReqNum ) );	*/			/* Hardware factor number */
	}
	t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unRS.u4Data = t_u4Rs;

	if ( (t_u1DescMode == (U1)DMA_DESCMODE0) || (t_u1DescMode == (U1)DMA_DESCMODE1) || (t_u1DescMode == (U1)DMA_DESCMODE2) )
	{
		/* Only transfer mode 0, 1 and 2 are supported */

		/* Descriptor Settings */
		t_u4Dpcr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unDPCR.u4Data & ( (U4)~( (U4)DMA_DPCR_UPF ) ) );		        /* Clear the settings of UPF 0 to UPF 10, which are valid bits */
		t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unDPCR.u4Data =  (U4)( t_u4Dpcr |
																(U4)( (U4)DMA_DPCR_UPF_0 * (U4)DMA_DPCR_UPF_SAR_ENABLE +	/* Source address register update flag */
																(U4)DMA_DPCR_UPF_1       * (U4)DMA_DPCR_UPF_DAR_ENABLE +	/* Destination address register update flag */
																(U4)DMA_DPCR_UPF_2       * (U4)DMA_DPCR_UPF_TSR_ENABLE +	/* Transfer size register update flag */
																(U4)DMA_DPCR_UPF_3       * (U4)DMA_DPCR_UPF_TMR_ENABLE ) );	/* Transfer mode register update flag */

		t_u2DesCnt=cu2PIL_DMAC_DESC_DescriptorAdrrpNum[t_u1ChannelID];			/* Initializing the descriptor counter */

		if (t_u1DescMode == DMA_DESCMODE1)
		{
			t_u2DesIntFlg = (U2)DMA_DPPTR_DIE_ENABLE;
		}
		else
		{
			t_u2DesIntFlg = (U2)DMA_DPPTR_DIE_DISABLE;
		}

		t_u4Dpptr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unDPPTR.u4Data & ( (U4)~( (U4)DMA_DPPTR_DIE + (U4)DMA_DPPTR_PTR + (U4)DMA_DPPTR_CF ) ) );
		t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unDPPTR.u4Data = (U4)( t_u4Dpptr | /* Descriptor pointer register */
						(U4)( (U4)DMA_DPPTR_DIE	*	t_u2DesIntFlg	+			  /* Descriptor End Interrupt Enabled */     /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
						(U4)DMA_DPPTR_PTR_0     *	t_u2ReloadPtr	+				  /* Address pointer of next descriptor */   /* justification for QAC warning 3384: it is not wrap-around within a configuration range */
						(U4)DMA_DPPTR_CF	    *	(U4)DMA_DPPTR_CF_ENABLE ) );	  /* Descriptor continuation flag */

		/* 1st Descriptor Memory Settings */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = (U4)((volatile const U4*)t_pcvdSrcAdr);	/* DMAC source address register */
		t_u2DesCnt++;    /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = (U4)((volatile const U4*)t_pcvdDestAdr);	/* DMAC destination address register */
		t_u2DesCnt++;    /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = (U4)( (U4)cu1PIL_DMAC_DESC_TransSize[t_u1TransSize] * (U4)t_u2TransNum );	/* DMAC transfer size register */	/* justification for QAC warning 3384: it is not wrap-around within a configuration range */
		t_u2DesCnt++;	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unTMR.u4Data;				/* DMAC transfer mode register */
		t_u2DesCnt++;	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
		t_u4Dpptr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unDPPTR.u4Data & ( (U4)~( (U4)DMA_DPPTR_DIE + (U4)DMA_DPPTR_PTR + (U4)DMA_DPPTR_CF ) ) );
		t_u4Dpptr |=	(U4)( (U4)DMA_DPPTR_DIE	  *	t_u2DesIntFlg	   +		  /* Descriptor End Interrupt Enabled */    /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
						      (U4)DMA_DPPTR_PTR_0 *	( t_u2DesCnt + 1 ) +          /* Address pointer of next descriptor */  /* justification for QAC warning 3384: it is not wrap-around within a configuration range */
						      (U4)DMA_DPPTR_CF	  *	(U4)DMA_DPPTR_CF_ENABLE );	  /* Descriptor continuation flag */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = t_u4Dpptr;					  /* Address pointer of descriptor */
		t_u2DesCnt++;

		/* 2nd Descriptor Memory Settings */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = (U4)((volatile const U4*)t_pcvdSrcAdr);	/* DMAC source address register */
		t_u2DesCnt++;    /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = (U4)((volatile const U4*)t_pcvdDestAdr);	/* DMAC destination address register */
		t_u2DesCnt++;    /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = (U4)( (U4)cu1PIL_DMAC_DESC_TransSize[t_u1TransSize] * (U4)t_u2TransNum );	/* DMAC transfer size register */	/* justification for QAC warning 3384: it is not wrap-around within a configuration range */
		t_u2DesCnt++;	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unTMR.u4Data;				            /* DMAC transfer mode register */
		t_u2DesCnt++;	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
		t_u4Dpptr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unDPPTR.u4Data & ( (U4)~( (U4)DMA_DPPTR_DIE    + (U4)DMA_DPPTR_PTR + (U4)DMA_DPPTR_CF ) ) );
		t_u4Dpptr |=	(U4)( (U4)DMA_DPPTR_DIE	  *	t_u2DesIntFlg	                                        +		/* Descriptor End Interrupt Enabled */   /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
						      (U4)DMA_DPPTR_PTR_0 *	( cu2PIL_DMAC_DESC_DescriptorAdrrpNum[t_u1ChannelID])	+		/* Address pointer of next descriptor */ /* justification for QAC warning 3384: it is not wrap-around within a configuration range */
						      (U4)DMA_DPPTR_CF	  *	(U4)DMA_DPPTR_CF_ENABLE );										/* Descriptor continuation flag */
		t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = t_u4Dpptr;													    /* Address pointer of descriptor */

		/* Setting the start of a descriptor */
		/* Transfer mode 3 disables the DMA transfer completion interrupt and enables the descriptor end interrupt. */
		/* The AND with the inverted value is temporarily held to hold settings other than the specified bit.(It is an intended cast and can never be negative.) */
		t_u2Chcr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data & ( (U2)~( (U2)DMA_CHCR_DPE + (U2)DMA_CHCR_DSIE + (U2)DMA_CHCR_IE + (U2)DMA_CHCR_DPB + (U2)DMA_CHCR_CAEE + (U2)DMA_CHCR_CAIE ) ) );
		t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data = (U2)( t_u2Chcr |(U2) ( (U2)DMA_CHCR_DPE	* (U2)DMA_CHCR_DPE_ENABLE	+	/* Descriptor Action Enabled */
																				      (U2)DMA_CHCR_DSIE	* t_u2DesIntFlg				+	/* Descriptor End Interrupt Enabled */
																				      (U2)DMA_CHCR_IE	* (U2)DMA_CHCR_IE_DISABLE	+	/* DMA Transfer Completion Interrupt Disabled */
																				      (U2)DMA_CHCR_DPB	* (U2)DMA_CHCR_DPB_AFTER_CH	+	/* Start DMA transfer after the channel configuration is copied from the descriptor memory. */
																				      (U2)DMA_CHCR_CAEE	* (U2)DMA_CHCR_CAEE_DISABLE	+	/* Channel address error notification disabled */
																				      (U2)DMA_CHCR_CAIE	* (U2)DMA_CHCR_CAIE_DISABLE ));	/* Channel address error interrupt disabled */
	}        
	else
	{
		/* DMA transfer completion interrupt is enabled except for transfer mode 3, and descriptor end interrupt is disabled. */
		/* In order to retain settings other than the specified bit, it is kept temporarily by taking AND with the inverted value. (Intended cast, never negative) */
		t_u2Chcr = ( t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data & ( (U2)~( (U2)DMA_CHCR_DSIE + (U2)DMA_CHCR_IE + (U2)DMA_CHCR_DPE + (U2)DMA_CHCR_CAEE + (U2)DMA_CHCR_CAIE ) ) );
		t_pstRegDmac->stDMAC_CH[t_u1ChannelID].unCHCR.u2Data = (U2)( t_u2Chcr|(U2)(	(U2)DMA_CHCR_DSIE	* (U2)DMA_CHCR_DSIE_DISABLE		+		/* Descriptor End Interrupt Disabled */
																				    (U2)DMA_CHCR_IE		* (U2)DMA_CHCR_IE_ENABLE		+	    /* DMA transfer completion interrupt enabled */
																				    (U2)DMA_CHCR_DPE	* (U2)DMA_CHCR_DPE_DISABLE 		+		/* Descriptor operation disabled */
																				    (U2)DMA_CHCR_CAEE	* (U2)DMA_CHCR_CAEE_DISABLE		+		/* Channel address error notification disabled */
																				    (U2)DMA_CHCR_CAIE	* (U2)DMA_CHCR_CAIE_DISABLE ));			/* Channel address error interrupt disabled */
	}

	/* EI_ALL()";" */
}

/*----------------------------------------------------------------------------------------------*/
/*	sDMAC Reload Data Update Function 															*/
/*	return		: void																			*/
/*	parameters	: DMAC ChannelID (0-15)															*/
/*				: DMAC Type (DMAC0/DMAC1)														*/
/*				: TransSize (SIZE_1/SIZE_2/SIZE_4)												*/
/*				: SrcAdr(Async) (Pointer to Source Adrress)										*/
/*				: DestAdr(Async) (Pointer to Destination Adrress)								*/
/*				: TransNum (Number of transfers until second reload)							*/
/*				: ReloadPtr (Descriptor pointer to update)										*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dmac_ReloadDataUpdate( U1 t_u1ChannelID, U1 t_u1DmaType, U1 t_u1TransSize, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum, U2 t_u2ReloadPtr )
{
	volatile Reg_Dram_Type*	t_pstRegDmacDesRAM;
	U2		t_u2DesCnt;			/* Descriptor counters */

	t_pstRegDmacDesRAM = (volatile Reg_Dram_Type*)cstPil_DMAC_DESC_DesRAM_Reg[t_u1DmaType];		/* Discriptor RAM */

	t_u2DesCnt = t_u2ReloadPtr;

	/* Descriptor Memory Settings */
	/* Pil_Dmac_SetTransModeTwoStepReload L445~L459から移植 */
	t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = (U4)((volatile const U4*)t_pcvdSrcAdr);	/* DMAC source address register */
	t_u2DesCnt++;    /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
	t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = (U4)((volatile const U4*)t_pcvdDestAdr);	/* DMAC destination address register */
	t_u2DesCnt++;    /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
	t_pstRegDmacDesRAM->u4DesRAM[t_u2DesCnt] = (U4)( (U4)cu1PIL_DMAC_DESC_TransSize[t_u1TransSize] * (U4)t_u2TransNum );	/* DMAC transfer size register */	/* justification for QAC warning 3384: it is not wrap-around within a configuration range */
	t_u2DesCnt++;	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
}

/*==============================================================================================*/
/*	Local Functions																				*/
/*==============================================================================================*/

#pragma ghs section text=default
/*-- End Of File -------------------------------------------------------------------------------*/
