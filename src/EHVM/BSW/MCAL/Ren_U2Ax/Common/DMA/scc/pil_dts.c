/* pil_dts-r04-3000-0100-a-v01 */
/************************************************************************************************/
/*																								*/
/*		PIL DTS Driver																			*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/

/*==============================================================================================*/
/*	include files																				*/
/*==============================================================================================*/
#include	"Dma.h"
#include	"Dma_engine.h"

#include	"pil_intc.h"
#include	"pil_dts.h"

#include	"reg_dma.h"

/*==============================================================================================*/
/*	prototypes																					*/
/*==============================================================================================*/

/*==============================================================================================*/
/*	defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/
#define		u1PIL_DTS_MODE_NUM			((U1)7U)
#define		u1PIL_DTSCT_NUM				((U1)4U)

typedef	union
{
	U2	u2Data;
	struct
	{
		U2	b3RegCh:3;      /* preferred channel number in the register */
		U2	b4RegNum:4;     /* Register  Number */
		U2  b3Group:3;      /* Group number */ 
		U2  b6Dummy:6;
	}stDiv;
}Pil_Dts_RequestGroupType;

/*---------------------*/
/* DTS Data Definition */
/*---------------------*/
/* DTS SPID */
#define		u4PIL_DTS_SPIDNUM			((U4)29U)					/* SPID value 29 fixed */

/* Number of shifts when obtaining PINT register number */
#define		u1PIL_DTS_SHIFT_NUM			((U1)5U)

/* To get the bit position of the PINTCLR register */
#define		u1PIL_DTS_PINTBITMASK			((U1)0x1fU)
#define		u4PIL_DTS_PINTBITSIFT			((U4)0x01U)

/* Number of INTC control registers (transfer complete/transfer count matching interrupts) held by DTS */
#define		s4PIL_DTS_INT_NUM			((S4)8U)

/*==============================================================================================*/
/*	constants																					*/
/*==============================================================================================*/
#define DMA_START_SEC_RODATA_CONST
#include "Dma_MemMap.h"


/* MODE setting table *******************************************************************/
/* mode= 0: Block1, Reload1OFF, Reload2OFF,    Dst Addr increased, Src Addr fixed 	*/
/* mode= 1: Single, Reload1OFF, Reload2OFF,    Dst Addr increased, Src Addr fixed 	*/
/* mode= 2: Single, Reload1OFF, Reload2OFF,    Dst Addr fixed, Src Addr increased 	*/
/* mode= 3: Block1, Reload1BOTH, Reload2OFF,    Dst Addr increased, Src Addr increased */
/* mode= 4: Single, Reload1BOTH, Reload2OFF,    Dst Addr increased, Src Addr fixed 	*/
/* mode= 5: Block2, Reload1BOTH, Reload2SrcAddr, Dst Addr increased, SrcAddr increased */
/* mode= 6: Single, Reload1OFF, Reload2OFF,    Dst Addr fixed, Src Addr fixed			*/
/****************************************************************************************/
static volatile const	U4		cu4PIL_DTS_MODE_TABLE[u1PIL_DTS_MODE_NUM] = {
	(U4)((U4)DMA_DTTCT_TRM_0	* (U4)DMA_DTTCT_TRM_BLOCK1			+
		 (U4)DMA_DTTCT_RLD1M_0	* (U4)DMA_DTTCT_RLD1M_DISABLE		+
		 (U4)DMA_DTTCT_RLD2M_0	* (U4)DMA_DTTCT_RLD2M_DISABLE		+
		 (U4)DMA_DTTCT_DACM_0	* (U4)DMA_DTTCT_DACM_ADDR_INC		+
		 (U4)DMA_DTTCT_SACM_0	* (U4)DMA_DTTCT_SACM_ADDR_FIX),			/* mode=0 : e.g. for RAM clear */
	(U4)((U4)DMA_DTTCT_TRM_0	* (U4)DMA_DTTCT_TRM_SINGLE			+
		 (U4)DMA_DTTCT_RLD1M_0	* (U4)DMA_DTTCT_RLD1M_DISABLE		+
		 (U4)DMA_DTTCT_RLD2M_0	* (U4)DMA_DTTCT_RLD2M_DISABLE		+
		 (U4)DMA_DTTCT_DACM_0	* (U4)DMA_DTTCT_DACM_ADDR_INC		+
		 (U4)DMA_DTTCT_SACM_0	* (U4)DMA_DTTCT_SACM_ADDR_FIX),			/* mode=1 : e.g. for SPI(SCI) Receive, A/D Gated(No Reload) */
	(U4)((U4)DMA_DTTCT_TRM_0	* (U4)DMA_DTTCT_TRM_SINGLE			+
		 (U4)DMA_DTTCT_RLD1M_0	* (U4)DMA_DTTCT_RLD1M_DISABLE		+
		 (U4)DMA_DTTCT_RLD2M_0	* (U4)DMA_DTTCT_RLD2M_DISABLE		+
		 (U4)DMA_DTTCT_DACM_0	* (U4)DMA_DTTCT_DACM_ADDR_FIX		+
		 (U4)DMA_DTTCT_SACM_0	* (U4)DMA_DTTCT_SACM_ADDR_INC),			/* mode=2 : e.g. for SPI(SCI) Send */
	(U4)((U4)DMA_DTTCT_TRM_0	* (U4)DMA_DTTCT_TRM_BLOCK1			+
		 (U4)DMA_DTTCT_RLD1M_0	* (U4)DMA_DTTCT_RLD1M_BOTH_RELOAD	+
		 (U4)DMA_DTTCT_RLD2M_0	* (U4)DMA_DTTCT_RLD2M_DISABLE		+
		 (U4)DMA_DTTCT_DACM_0	* (U4)DMA_DTTCT_DACM_ADDR_INC		+
		 (U4)DMA_DTTCT_SACM_0	* (U4)DMA_DTTCT_SACM_ADDR_INC),			/* mode=3 : e.g. for A/D Scan */
	(U4)((U4)DMA_DTTCT_TRM_0	* (U4)DMA_DTTCT_TRM_SINGLE			+
		 (U4)DMA_DTTCT_RLD1M_0	* (U4)DMA_DTTCT_RLD1M_BOTH_RELOAD	+
		 (U4)DMA_DTTCT_RLD2M_0	* (U4)DMA_DTTCT_RLD2M_DISABLE		+
		 (U4)DMA_DTTCT_DACM_0	* (U4)DMA_DTTCT_DACM_ADDR_INC		+
		 (U4)DMA_DTTCT_SACM_0	* (U4)DMA_DTTCT_SACM_ADDR_FIX),			/* mode=4 : e.g. for A/D Gated(Reload) */
	(U4)((U4)DMA_DTTCT_TRM_0	* (U4)DMA_DTTCT_TRM_BLOCK2			+
		 (U4)DMA_DTTCT_RLD1M_0	* (U4)DMA_DTTCT_RLD1M_BOTH_RELOAD	+
		 (U4)DMA_DTTCT_RLD2M_0	* (U4)DMA_DTTCT_RLD2M_SRC_ADR_RELOAD+
		 (U4)DMA_DTTCT_DACM_0	* (U4)DMA_DTTCT_DACM_ADDR_INC		+
		 (U4)DMA_DTTCT_SACM_0	* (U4)DMA_DTTCT_SACM_ADDR_INC),			/* mode=5 : e.g. for A/D GatedMulti */
	(U4)((U4)DMA_DTTCT_TRM_0	* (U4)DMA_DTTCT_TRM_SINGLE			+
		 (U4)DMA_DTTCT_RLD1M_0	* (U4)DMA_DTTCT_RLD1M_DISABLE		+
		 (U4)DMA_DTTCT_RLD2M_0	* (U4)DMA_DTTCT_RLD2M_DISABLE		+
		 (U4)DMA_DTTCT_DACM_0	* (U4)DMA_DTTCT_DACM_ADDR_FIX		+
		 (U4)DMA_DTTCT_SACM_0	* (U4)DMA_DTTCT_SACM_ADDR_FIX)			/* mode=6 : e.g. for SPI(Dummy) Send  Receive */
};

/* DTS Priority CH */
typedef	union
{
	U1		u1Ch;					/* CH Number */
	struct							/* Bit Access */
	{
		U1	b4RegCh			:4;		/* Preferred CH */
		U1	b4RegNum		:4;		/* Priority setting number position */
	}stBit;
}Pil_Dts_ChDiv;

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
/*	DTS Trans Enable with DTS Request Clear Function											*/
/*	return		: void																			*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_EnableTrans( U1 t_u1ChannelID )
{
	/* Transfer request clear */	
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSC.u4Data = (U4)DMA_DTFSC_DRQC * (U4)DMA_DTFSC_DRQC_TRANS_REQ_CLEAR;

	Reg_DTS.unDTSCTL1.u4Data = (U4)DMA_DTSCTL1_DTSUST * (U4)DMA_DTSCTL1_DTSUST_START;

	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSL.u4Data = (U4)DMA_DTFSL_REQEN * (U4)DMA_DTFSL_REQEN_TRANS_ENABLE;
	
	Bswlib_Sync_Pipeline_4( Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSL.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Trans Disable Function																	*/
/*	return		: void																			*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_DisableTrans( U1 t_u1ChannelID )
{
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSL.u4Data = (U4)DMA_DTFSL_REQEN * (U4)DMA_DTFSL_REQEN_TRANS_DISABLE;	/* DMA transfer request disabled(not interrupted) */

	Bswlib_Sync_Pipeline_4( Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSL.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Trans Mode Set Function																	*/
/*	return		: void																			*/
/*	parameters	: DTS Channel (0-127)															*/
/*				: TransSize (SIZE_1/SIZE_2/SIZE_4)												*/
/*				: DmaMode (0-5)																	*/
/*				: SrcAdr(Async) (Pointer to Source Adrress)										*/
/*				: DestAdr(Async) (Pointer to Destination Adrress)								*/
/*				: TransNum (Trans number)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_SetTransMode( U1 t_u1ChannelID, U1 t_u1TransSize, U1 t_u1DmaMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum )
{
	U4		t_u4Dttct;		/* DTTCT register setting value */
	U4		t_u4Mode;
	U4		t_u4RegCM;


	/* DI_ALL()";" */ /* There is no use case for calling Enable, SetInterrupt, or this function from a high-priority task during SetTransMode execution for the same DTS channel, so there is no need to call the function for blocking interrupts. */

	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSL.u4Data = (U4)DMA_DTFSL_REQEN * (U4)DMA_DTFSL_REQEN_TRANS_DISABLE;	/* DMA transfer request disabled(not interrupted) */

	Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTSA = (U4)((volatile const U4*)t_pcvdSrcAdr);				/* Source address settings */
	Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTDA = (U4)((volatile const U4*)t_pcvdDestAdr);				/* Destination address configuration */
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTC.u4Data = (U4)t_u2TransNum;
				/*	The following processing is commented out (QAC compatible) because the calculation result is fixed at t_u2TransNum */
				/*	(U4)DMA_DTTC_ARC_0		* (U4)DMA_DTTC_ARC_NOUSE	+	""*/		/* Address reload count:0 */
				/*	(U4)DMA_DTTC_TRC_0		* t_u2TransNum";"					*/			/* Number of transfers setting */
	
	/* Transfer count compare setting based on errata TN-RH8-B0442A/J workaround 1*/
	/* As SetMasterCh and SetTransMode will not be called at the same time, DI_ALL  and EI_ALL are not used for RMW */
	
	t_u4RegCM = (U4)(Reg_DTS.unDTSCM[t_u1ChannelID].u4Data & (U4)(~(U4)DMA_DTSCM_CMC));
	Reg_DTS.unDTSCM[t_u1ChannelID].u4Data = (U4)(t_u4RegCM | (U4)(((U4)t_u2TransNum >> (U4)1) + (U4)1));	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
	
	
	/* Transfer Control Register (DTTCT) settings */
	t_u4Dttct = Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTCT.u4Data;
	t_u4Dttct &= (U4)((U4)DMA_DTTCT_CCE + (U4)DMA_DTTCT_TCE);				/* CCE, TCE set current value */
	t_u4Mode = cu4PIL_DTS_MODE_TABLE[t_u1DmaMode];
	t_u4Dttct |= (U4)(t_u4Mode +											/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
			/*	The following processing is commented out (QAC compatible) because the result of the calculation is fixed at 0. */
			/*	(U4)DMA_DTTCT_ESE		* (U4)DMA_DTTCT_ESE_CONTINUE	+	""*/		/* Do not abort DMA transfer on DMA transfer error. */
			/*	(U4)DMA_DTTCT_CHNSEL_0	* (U4)DMA_DTTCT_CHNSEL_CH0		+	""*/		/* Channel to chain to */
			/*	(U4)DMA_DTTCT_CHNE_0	* (U4)DMA_DTTCT_CHNE_DISABLE	+	""*/		/* Chain function disabled */
				(U4)DMA_DTTCT_DS_0		* t_u1TransSize);							/* Transfer data size setting */	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTCT.u4Data = t_u4Dttct;

	/* When Reload Function 1 is ON	*/
	if( (t_u4Dttct & (U4)DMA_DTTCT_RLD1M) != (U4)( (U4)DMA_DTTCT_RLD1M_0 * (U4)DMA_DTTCT_RLD1M_DISABLE ) )
	{
		Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTRSA = (U4)((volatile const U4*)t_pcvdSrcAdr); 	/* Set reload source address  */
		Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTRDA = (U4)((volatile const U4*)t_pcvdDestAdr);	/* Set reload destination address */
		Reg_DTS.stDTS_CH[t_u1ChannelID].unDTRTC.u4Data = (U4)t_u2TransNum;
				/*	The following processing is commented out (QAC compatible) because the calculation result is fixed at the value of t_u2TransNum. */
				/*	(U4)DMA_DTRTC_RARC_0	* (U4)DMA_DTRTC_RARC_NOUSE	+ "" */			/* Reload Address reload count: 0 */
				/*	(U4)DMA_DTRTC_RTRC_0	* t_u2TransNum ";" 			  */			/* Reload/Setting the number of transfers */
	}

	/* EI_ALL()";" */
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Trans Mode (Two Level Reload) Set Function												*/
/*	return		: void																			*/
/*	parameters	: DTS Channel (0-127)															*/
/*				: TransSize (SIZE_1/SIZE_2/SIZE_4)												*/
/*				: DmaMode (0-5)																	*/
/*				: SrcAdr(Async) (Pointer to Source Adrress)										*/
/*				: DestAdr(Async) (Pointer to Destination Adrress)								*/
/*				: TransNum (Number of transfers until second reload)							*/
/*				: AddrReloadCnt (Number of transfers until first reload(0 if not mode5))		*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_SetTransModeTwoStepReload( U1 t_u1ChannelID, U1 t_u1TransSize, U1 t_u1DmaMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, U2 t_u2TransNum, U2 t_u2AddrReloadCnt )
{
	U4		t_u4Dttct;		/* DTTCT register setting value */
	U4		t_u4Mode;
	U4		t_u4RegCM;


	/* DI_ALL()";" */ /* There is no use case for calling Enable, SetInterrupt, or this function from a high-priority task during SetTransMode execution for the same DTS channel, so there is no need to call the function for blocking interrupts. */

	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSL.u4Data = (U4)DMA_DTFSL_REQEN * (U4)DMA_DTFSL_REQEN_TRANS_DISABLE;	/* DMA transfer request disabled(not interrupted) */

	Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTSA = (U4)((volatile const U4*)t_pcvdSrcAdr);		/* Source address settings */
	Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTDA = (U4)((volatile const U4*)t_pcvdDestAdr);		/* Destination address configuration */
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTC.u4Data = 
				(U4)(((U4)DMA_DTTC_ARC_0		* (U4)t_u2AddrReloadCnt)	+(U4)t_u2TransNum);		/* Address reload count settings */		/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
				/*	The following processing is commented out (QAC compatible) because the calculation result is fixed at the value of t_u2TransNum. */
				/*	(U4)DMA_DTTC_TRC_0		* t_u2TransNum";" */					/* Number of transfers setting */
	
	/* Transfer count compare setting based on errata TN-RH8-B0442A/J workaround 1*/
	/* As SetMasterCh and SetTransMode will not be called at the same time, DI_ALL  and EI_ALL are not used for RMW */
		
	t_u4RegCM = (U4)(Reg_DTS.unDTSCM[t_u1ChannelID].u4Data & (U4)(~(U4)DMA_DTSCM_CMC));
	Reg_DTS.unDTSCM[t_u1ChannelID].u4Data = (U4)(t_u4RegCM | (U4)(((U4)t_u2TransNum >> (U4)1) + (U4)1));	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
	

	/* Transfer Control Register (DTTCT) settings */
	t_u4Dttct = Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTCT.u4Data;
	t_u4Dttct &= (U4)((U4)DMA_DTTCT_CCE + (U4)DMA_DTTCT_TCE);				/* CCE, TCE set current value */
	t_u4Mode = cu4PIL_DTS_MODE_TABLE[t_u1DmaMode];
	t_u4Dttct |= (U4)(t_u4Mode +												/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
			/*	The following processing is commented out (QAC compatible) because the result of the calculation is fixed at 0. */
			/*	(U4)DMA_DTTCT_ESE		* (U4)DMA_DTTCT_ESE_CONTINUE	+ ""*/	/* Do not abort DMA transfer when DMA transfer error occurs */
			/*	(U4)DMA_DTTCT_CHNSEL_0	* (U4)DMA_DTTCT_CHNSEL_CH0		+ ""*/	/* Channel to chain to */
			/*	(U4)DMA_DTTCT_CHNE_0	* (U4)DMA_DTTCT_CHNE_DISABLE	+ ""*/	/* Chain function disabled */
				(U4)DMA_DTTCT_DS_0		* (U4)t_u1TransSize);						/* Transfer data size setting */	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTCT.u4Data = t_u4Dttct;

	/* When either of the reload functions 1 or 2 is ON	*/
	if( (t_u4Dttct & ((U4)DMA_DTTCT_RLD1M + (U4)DMA_DTTCT_RLD2M)) !=
			(U4)( ( (U4)DMA_DTTCT_RLD1M_0 * (U4)DMA_DTTCT_RLD1M_DISABLE ) + ( (U4)DMA_DTTCT_RLD2M_0 * (U4)DMA_DTTCT_RLD2M_DISABLE ) ) )
	{
		Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTRSA = (U4)((volatile const U4*)t_pcvdSrcAdr); 	/* Set reload source address */
		Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTRDA = (U4)((volatile const U4*)t_pcvdDestAdr);	/* Set reload destination address */
		Reg_DTS.stDTS_CH[t_u1ChannelID].unDTRTC.u4Data = 
					(U4)(((U4)DMA_DTRTC_RARC_0	* (U4)t_u2AddrReloadCnt)	+ (U4)t_u2TransNum);	/* Reload Address reload count settings */	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
					/* The following processing is commented out (QAC compatible) because the calculation result is fixed at the value of t_u2TransNum */
					/*	(U4)DMA_DTRTC_RTRC_0	* t_u2TransNum";" */					/* Reload Number of transfers setting */
	}

	/* EI_ALL()";" */
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Interrupt E/D Set Function																*/
/*	return		: void																			*/
/*	parameters	: DTS Channel (0-127)															*/
/*				: HalfIe (ON/OFF)""																*/
/*				: EndIe (ON/OFF)""																*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_SetInterrupt( U1 t_u1ChannelID, U1 t_u1HalfIe, U1 t_u1EndIe )
{
	U4		t_u4Reg;

	t_u4Reg = ((U4)DMA_DTTCT_CCE * t_u1HalfIe) + ((U4)DMA_DTTCT_TCE * t_u1EndIe);	/* justification for QAC warning 3384(3383): it is not wrap-around within a configuration range */

	/* DI_ALL()";" *//* There is no use case for calling SetTransMode, or this function from a high-priority task, so there is no need to call the function for blocking interrupts. */
	t_u4Reg |= (U4)( Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTCT.u4Data & (U4)(~((U4)DMA_DTTCT_CCE + (U4)DMA_DTTCT_TCE) ));
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTCT.u4Data = t_u4Reg;

	Bswlib_Sync_Pipeline_4( Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTCT.u4Data );
	/* EI_ALL()";" */
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Intc Interrupt Enable Set Function														*/
/*	return		: void																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_EnableIntcInterrupt( void )
{
	S4		i;
	
	for( i = (S4)0; i < s4PIL_DTS_INT_NUM; i++ )
	{
		Pil_Intc2_SetInterrupt( (U2)i + (U2)INTC_CH_DTS_CH31TO0, DMA_ON );
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Intc Interrupt Disable Set Function														*/
/*	return		: void																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_DisableIntcInterrupt( void )
{
	S4		i;
	
	for( i = (S4)0; i < s4PIL_DTS_INT_NUM; i++ )
	{
		Pil_Intc2_SetInterrupt( (U2)i + (U2)INTC_CH_DTS_CH31TO0, DMA_OFF );
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Transfer completed state Function														*/
/*	return		: Transfer end flag ( =0:transfer not complete / =1:transfer complete)			*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
U1		Pil_Dts_IsTransferCompleted( U1 t_u1ChannelID )
{
	U4				t_u4Dtfst;
	U1				t_u1Ret;

	t_u1Ret = (U1)FALSE;

	t_u4Dtfst = Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFST.u4Data;
	if(( t_u4Dtfst & (U4)DMA_DTFST_TC ) != (U4)DMA_DTFST_TC_NOTCOMPLETE )
	{
		t_u1Ret = (U1)TRUE;
	}

	return( t_u1Ret );
}

/*----------------------------------------------------------------------------------------------*/
/*	Compare Match Status Clear Function															*/
/*	return		: void																			*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_ClearMatchStatus( U1 t_u1ChannelID )
{
	volatile U4                 t_u4Reg;
	U4                          t_u4ClrBit;
	U1                          t_u1PintId;

	/* Get the appropriate PINT register number and bit position to clear. */
	t_u1PintId = ( t_u1ChannelID >> u1PIL_DTS_SHIFT_NUM );
	t_u4ClrBit = ( u4PIL_DTS_PINTBITSIFT << (t_u1ChannelID & u1PIL_DTS_PINTBITMASK) );

	DMA_ENTER_CRITICAL_SECTION();
		/* Clear transfer count match flag and transfer complete flag */
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSC.u4Data = ((U4)DMA_DTFSC_CCC * (U4)DMA_DTFSC_CCC_COMPARE_CLEAR) + ((U4)DMA_DTFSC_TCC * (U4)DMA_DTFSC_TCC_COMPLETE_CLEAR);
	Bswlib_Sync_Pipeline_4( Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSC.u4Data );

	/* Clear the interrupt request flag by clearing the PINT register (transfer completion interrupt) */
	t_u4Reg = Reg_INTIF.unPINT[t_u1PintId].u4Data;	/* Dummy read */
	Reg_INTIF.unPINTCLR[t_u1PintId].u4Data = t_u4ClrBit;
	Bswlib_Sync_Pipeline_4( Reg_INTIF.unPINT[t_u1PintId].u4Data ); 
	
	/* Clear the interrupt request flag by clearing the PINT register (transfer count matching interrupt) */
	t_u4Reg = Reg_INTIF.unPINT[t_u1PintId + u1PIL_DTSCT_NUM].u4Data;	/* Dummy read */
	Reg_INTIF.unPINTCLR[t_u1PintId + u1PIL_DTSCT_NUM].u4Data = t_u4ClrBit;
	Bswlib_Sync_Pipeline_4( Reg_INTIF.unPINT[t_u1PintId + u1PIL_DTSCT_NUM].u4Data ); 
	DMA_EXIT_CRITICAL_SECTION();
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Destination Adrress Get Function														*/
/*	return		: Destination Address															*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
void*	Pil_Dts_GetDestinationAddress( U1 t_u1ChannelID )
{
	U4* t_pu4DestAdr;
	
	t_pu4DestAdr = (U4*)Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTDA;
	
	return( (void*)t_pu4DestAdr);
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Trans Count Get Function																*/
/*	return		: Trans Count																	*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
U2		Pil_Dts_GetTransCount( U1 t_u1ChannelID )
{
	return( (U2)Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTC.u4Data );	/* Retrieve only the lower 2 bytes (TRC bits) */
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Trans Count Reset Function																*/
/*	return		: none																			*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_ResetTransCount( U1 t_u1ChannelID )
{
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTC.u4Data = (U4)0;
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Trans Status Get Function																*/
/*	return		: Trans Status ( =0:IDLE / =1:BUSY)												*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
U1		Pil_Dts_GetTransStatus( U1 t_u1ChannelID )
{
	U4				t_u4Dtssts;
	U1				t_u1TransStat;

	t_u1TransStat = (U1)DMA_DTSSTS_DTSACT_IDLE;

	t_u4Dtssts = Reg_DTS.unDTSSTS.u4Data;
	if(  (( t_u4Dtssts & (U4)DMA_DTSSTS_DTSACT ) != (U4)DMA_DTSSTS_DTSACT_IDLE )							/* If there is a channel that is DMA forwarding and */
	  && ((( t_u4Dtssts & (U4)DMA_DTSSTS_DTSACH ) >> DMA_DTSSTS_DTSACH_OFFSET ) == (U4)t_u1ChannelID ))		/*  the channel is t_u1ChannelID */ 
	{
		t_u1TransStat = (U1)DMA_DTSSTS_DTSACT_BUSY;
	}

	return( t_u1TransStat );
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Error Check Function																	*/
/*	return		: Error Status																	*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
ZORN	Pil_Dts_CheckDmaError( void )
{
	U4 t_u4ErrFlag;
	/* Check if any of the DTS CHs are experiencing DMA transfer errors */
	/* The DTSERCH bit that holds the CH of the error occurrence indicates the first CH at the time of the error occurrence in E1MS2,*/
	/*  but the microcomputer specification has changed to indicate the minimum CH of the error occurrence in E2x. */
	t_u4ErrFlag = (Reg_DTS.unDTSER.u4Data & (U4)DMA_DTSER_DTSER);

	return ( (ZORN)t_u4ErrFlag );
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Error Status Clear Function																*/
/*	return		: none																			*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_ClearDmaError( U1 t_u1ChannelID )
{
	/* Clear transfer error flag for specified CH */
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSC.u4Data = (U4)DMA_DTFSC_ERC	* (U4)DMA_DTFSC_ERC_TRANS_ERR_CLEAR;
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS  Set  Transfer Request Group Function													*/
/*	return		: none																			*/
/*	parameters	: Request group number (0-767)													*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_SetTransReqGroup( U2 t_u2RequestGroup )
{
	Pil_Dts_RequestGroupType t_udRequestGroup;
	U4 t_u4GroupData;
	U1 t_u1RegChannel;
	U1 t_u1Register;

	t_udRequestGroup.u2Data = t_u2RequestGroup;
	t_u1RegChannel = (U1)t_udRequestGroup.stDiv.b3RegCh;
	t_u1Register = (U1)t_udRequestGroup.stDiv.b4RegNum;
	t_u4GroupData = (U4)t_udRequestGroup.stDiv.b3Group;

	t_u4GroupData = (U4)(t_u4GroupData << (U4)((U4)t_u1RegChannel * (U4)DMA_DTS_SEL_BIT_NUM));		/* justification for QAC warning 3383: it is not wrap-around within a configuration range */
	Reg_DMATRGSEL.unDTSSEL[t_u1Register].u4Data |= t_u4GroupData;

}

#if ( DMA_CFG_REG_CHK == STD_ON ) 
/*----------------------------------------------------------------------------------------------*/
/*	Service name	:	CheckTransReqGroup														*/
/*	Parameters (in)	:	Request group number (0-767)											*/
/*	Return value	:	Register error Status													*/
/*----------------------------------------------------------------------------------------------*/
U4	Pil_Dts_CheckTransReqGroup( U2 t_u2RequestGroup )
{
	Pil_Dts_RequestGroupType t_udRequestGroup;
	U4 t_u4GroupData;
	U4 t_u4DtsSelReg;
	U1 t_u1RegChannel;
	U1 t_u1Register;
	U4 t_u4Ret;

	t_u4Ret = DMA_REGCHK_OK;

	t_udRequestGroup.u2Data = t_u2RequestGroup;
	t_u1RegChannel = (U1)t_udRequestGroup.stDiv.b3RegCh;
	t_u1Register = (U1)t_udRequestGroup.stDiv.b4RegNum;
	t_u4GroupData = (U4)t_udRequestGroup.stDiv.b3Group;

	t_u4DtsSelReg = (U4)((Reg_DMATRGSEL.unDTSSEL[t_u1Register].u4Data >> ((U4)((U4)t_u1RegChannel * (U4)DMA_DTS_SEL_BIT_NUM)))& (U4)DMA_DTSSEL_SEL0 ); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */

	if (t_u4DtsSelReg != t_u4GroupData)
	{
#if ( DMA_CFG_REG_REFRESH == STD_ON ) 
		/* Rewrite */
		Reg_DMATRGSEL.unDTSSEL[t_u1Register].u4Data &= (U4)(~(U4)((U4)DMA_DTSSEL_SEL0 << (U4)((U4)t_u1RegChannel * (U4)DMA_DTS_SEL_BIT_NUM))); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
		Pil_Dts_SetTransReqGroup(t_u2RequestGroup);
		/* ReCheck */
		t_u4DtsSelReg = (U4)((Reg_DMATRGSEL.unDTSSEL[t_u1Register].u4Data >> ((U4)((U4)t_u1RegChannel * (U4)DMA_DTS_SEL_BIT_NUM)))& (U4)DMA_DTSSEL_SEL0 ); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */
		if((t_u4DtsSelReg != t_u4GroupData))
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

/*----------------------------------------------------------------------------------------------*/
/*	Service name	:	Check DTS INTC Register for interrupt enabling							*/
/*	Parameters (in)	:	None																	*/
/*	Return value	:	Register error Status													*/
/*----------------------------------------------------------------------------------------------*/
U4	Pil_Dts_CheckIntcReg( void )
{
	S4	i;
	U4	t_u4Ret;
	U1	t_u1IntEnable;

	t_u4Ret = DMA_REGCHK_OK;

	for( i = (S4)0; (i < s4PIL_DTS_INT_NUM); i++ )
	{
		t_u1IntEnable = Pil_Intc2_GetInterrupt((U2)((U2)i + (U2)INTC_CH_DTS_CH31TO0)); 
		
		if ( t_u1IntEnable != (U1)DMA_ON )
		{	
#if ( DMA_CFG_REG_REFRESH == STD_ON ) 
			/* Rewrite */
			Pil_Intc2_SetInterrupt( (U2)i + (U2)INTC_CH_DTS_CH31TO0, DMA_ON );
			/* ReCheck */
			t_u1IntEnable = Pil_Intc2_GetInterrupt((U2)((U2)i + (U2)INTC_CH_DTS_CH31TO0)); 

			if ( t_u1IntEnable != (U1)DMA_ON )
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
			break;
#endif
		}
	}

	return (t_u4Ret);
}
#endif

/*----------------------------------------------------------------------------------------------*/
/*	DTS  Ram Clear Function																		*/
/*	return		: none																			*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
/*void	Pil_Dts_ClearRam( U1 t_u1ChannelID )""*/
/*{*/

	/* Comment out the following, in hopes of initializing with a flash option byte */

	/* DTS */
	/* DTSRAM Initialization(It may be referred to before setting DTSRAM, so uniformly initialize it with Init.) */
/*	Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTSA = (U4)0";"*/
/*	Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTDA = (U4)0";"*/
/*	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTC.u4Data = (U4)0";"*/
/*	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTCT.u4Data = (U4)0";"*/
/*	Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTRSA = (U4)0";"*/
/*	Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTRDA = (U4)0";"*/
/*	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTRTC.u4Data = (U4)0";"*/

/*}*/

/*----------------------------------------------------------------------------------------------*/
/*	DTS  Set Master Channel Function															*/
/*	return		: none																			*/
/*	parameters	: none															*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_SetMasterCh( void )
{
	S4		i;

	/* Set the same SPID as the default to 29. */
	/* ※Reconfigure because the option byte sets 0. */
	for( i = (S4)0; i < (S4)DMA_DTS_CH_NUM; i++ )
	{
		Reg_DTS.unDTSCM[i].u4Data = (U4)( ( (U4)DMA_DTSCM_SPID_0 * u4PIL_DTS_SPIDNUM ) );
	}
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS  Set Priority Function																	*/
/*	return		: none																			*/
/*	parameters	: DTS Channel (0-127)															*/
/*				: DTS Priority Level (0-3)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_SetPriority( U1 t_u1ChannelID, U1 t_u1PriLevel )
{
	Pil_Dts_ChDiv		t_unDtsChDiv;

	t_unDtsChDiv.u1Ch = t_u1ChannelID;
	Reg_DTS.unDTSPR[t_unDtsChDiv.stBit.b4RegNum].u4Data |= (U4)(((U4)1 << (U4)(t_unDtsChDiv.stBit.b4RegCh * (U4)2)) * (U4)t_u1PriLevel);	/* justification for QAC warning 3384(3383): it is not wrap-around within a configuration range */

}

/*----------------------------------------------------------------------------------------------*/
/*	DTS  Set Init Priority All Channel Function													*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
/*void	Pil_Dts_SetInitPriorityAllCh( void )""*/
/*{*/
/*	S4		i";"*/

	/* Set All Channels to Priority 2 */
/*	for( i = (S4)0; i < (S4)DMA_DTS_PRI_NUM; i++ )""*/
/*	{*/
/*		Reg_DTS.unDTSPR[i].u4Data = (U4)DMA_DTSPR_PR_ALL2";"*/
/*	}*/
/*}*/

/*----------------------------------------------------------------------------------------------*/
/*	DTS  Disable Trans All Function																*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_DisableTransAll( void )
{
	S4		i;

	/* All DMA transfer requests disabled */
	/* DTS */
	for( i = (S4)0; i < (S4)DMA_DTS_CH_NUM; i++ )
	{
		Reg_DTS.stDTS_CH[i].unDTFSL.u4Data = (U4)DMA_DTFSL_REQEN * (U4)DMA_DTFSL_REQEN_TRANS_DISABLE;	/* DMA transfer request disabled */
	}
}

/*==============================================================================================*/
/*	Local Functions																				*/
/*==============================================================================================*/

#define DMA_STOP_SEC_TEXT_CODE
#include "Dma_MemMap.h"
/*-- End Of File -------------------------------------------------------------------------------*/
