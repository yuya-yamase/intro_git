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
#define		u1PIL_DTS_MODE_NUM			((uint8)7U)
#define		u1PIL_DTSCT_NUM				((uint8)4U)

typedef	union
{
	uint16	u2Data;
	struct
	{
		uint16	b3RegCh:3;      /* preferred channel number in the register */
		uint16	b4RegNum:4;     /* Register  Number */
		uint16  b3Group:3;      /* Group number */ 
		uint16  b6Dummy:6;
	}stDiv;
}Pil_Dts_RequestGroupType;

/*---------------------*/
/* DTS Data Definition */
/*---------------------*/
/* DTS SPID */
#define		u4PIL_DTS_SPIDNUM			((uint32)29U)					/* SPID value 29 fixed */

/* Number of shifts when obtaining PINT register number */
#define		u1PIL_DTS_SHIFT_NUM			((uint8)5U)

/* To get the bit position of the PINTCLR register */
#define		u1PIL_DTS_PINTBITMASK			((uint8)0x1fU)
#define		u4PIL_DTS_PINTBITSIFT			((uint32)0x01U)

/* Number of INTC control registers (transfer complete/transfer count matching interrupts) held by DTS */
#define		s4PIL_DTS_INT_NUM			((sint32)8U)

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
static volatile const	uint32		cu4PIL_DTS_MODE_TABLE[u1PIL_DTS_MODE_NUM] = {
	(uint32)((uint32)DMA_DTTCT_TRM_0	* (uint32)DMA_DTTCT_TRM_BLOCK1			+
			 (uint32)DMA_DTTCT_RLD1M_0	* (uint32)DMA_DTTCT_RLD1M_DISABLE		+
			 (uint32)DMA_DTTCT_RLD2M_0	* (uint32)DMA_DTTCT_RLD2M_DISABLE		+
			 (uint32)DMA_DTTCT_DACM_0	* (uint32)DMA_DTTCT_DACM_ADDR_INC		+
			 (uint32)DMA_DTTCT_SACM_0	* (uint32)DMA_DTTCT_SACM_ADDR_FIX),			/* mode=0 : e.g. for RAM clear */
	(uint32)((uint32)DMA_DTTCT_TRM_0	* (uint32)DMA_DTTCT_TRM_SINGLE			+
			 (uint32)DMA_DTTCT_RLD1M_0	* (uint32)DMA_DTTCT_RLD1M_DISABLE		+
			 (uint32)DMA_DTTCT_RLD2M_0	* (uint32)DMA_DTTCT_RLD2M_DISABLE		+
			 (uint32)DMA_DTTCT_DACM_0	* (uint32)DMA_DTTCT_DACM_ADDR_INC		+
			 (uint32)DMA_DTTCT_SACM_0	* (uint32)DMA_DTTCT_SACM_ADDR_FIX),			/* mode=1 : e.g. for SPI(SCI) Receive, A/D Gated(No Reload) */
	(uint32)((uint32)DMA_DTTCT_TRM_0	* (uint32)DMA_DTTCT_TRM_SINGLE			+
			 (uint32)DMA_DTTCT_RLD1M_0	* (uint32)DMA_DTTCT_RLD1M_DISABLE		+
			 (uint32)DMA_DTTCT_RLD2M_0	* (uint32)DMA_DTTCT_RLD2M_DISABLE		+
			 (uint32)DMA_DTTCT_DACM_0	* (uint32)DMA_DTTCT_DACM_ADDR_FIX		+
			 (uint32)DMA_DTTCT_SACM_0	* (uint32)DMA_DTTCT_SACM_ADDR_INC),			/* mode=2 : e.g. for SPI(SCI) Send */
	(uint32)((uint32)DMA_DTTCT_TRM_0	* (uint32)DMA_DTTCT_TRM_BLOCK1			+
			 (uint32)DMA_DTTCT_RLD1M_0	* (uint32)DMA_DTTCT_RLD1M_BOTH_RELOAD	+
			 (uint32)DMA_DTTCT_RLD2M_0	* (uint32)DMA_DTTCT_RLD2M_DISABLE		+
			 (uint32)DMA_DTTCT_DACM_0	* (uint32)DMA_DTTCT_DACM_ADDR_INC		+
			 (uint32)DMA_DTTCT_SACM_0	* (uint32)DMA_DTTCT_SACM_ADDR_INC),			/* mode=3 : e.g. for A/D Scan */
	(uint32)((uint32)DMA_DTTCT_TRM_0	* (uint32)DMA_DTTCT_TRM_SINGLE			+
			 (uint32)DMA_DTTCT_RLD1M_0	* (uint32)DMA_DTTCT_RLD1M_BOTH_RELOAD	+
			 (uint32)DMA_DTTCT_RLD2M_0	* (uint32)DMA_DTTCT_RLD2M_DISABLE		+
			 (uint32)DMA_DTTCT_DACM_0	* (uint32)DMA_DTTCT_DACM_ADDR_INC		+
			 (uint32)DMA_DTTCT_SACM_0	* (uint32)DMA_DTTCT_SACM_ADDR_FIX),			/* mode=4 : e.g. for A/D Gated(Reload) */
	(uint32)((uint32)DMA_DTTCT_TRM_0	* (uint32)DMA_DTTCT_TRM_BLOCK2			+
			 (uint32)DMA_DTTCT_RLD1M_0	* (uint32)DMA_DTTCT_RLD1M_BOTH_RELOAD	+
			 (uint32)DMA_DTTCT_RLD2M_0	* (uint32)DMA_DTTCT_RLD2M_SRC_ADR_RELOAD+
			 (uint32)DMA_DTTCT_DACM_0	* (uint32)DMA_DTTCT_DACM_ADDR_INC		+
			 (uint32)DMA_DTTCT_SACM_0	* (uint32)DMA_DTTCT_SACM_ADDR_INC),			/* mode=5 : e.g. for A/D GatedMulti */
	(uint32)((uint32)DMA_DTTCT_TRM_0	* (uint32)DMA_DTTCT_TRM_SINGLE			+
			 (uint32)DMA_DTTCT_RLD1M_0	* (uint32)DMA_DTTCT_RLD1M_DISABLE		+
			 (uint32)DMA_DTTCT_RLD2M_0	* (uint32)DMA_DTTCT_RLD2M_DISABLE		+
			 (uint32)DMA_DTTCT_DACM_0	* (uint32)DMA_DTTCT_DACM_ADDR_FIX		+
			 (uint32)DMA_DTTCT_SACM_0	* (uint32)DMA_DTTCT_SACM_ADDR_FIX)			/* mode=6 : e.g. for SPI(Dummy) Send  Receive */
};

/* DTS Priority CH */
typedef	union
{
	uint8		u1Ch;					/* CH Number */
	struct							/* Bit Access */
	{
		uint8	b4RegCh			:4;		/* Preferred CH */
		uint8	b4RegNum		:4;		/* Priority setting number position */
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
void	Pil_Dts_EnableTrans( uint8 t_u1ChannelID )
{
	/* Transfer request clear */	
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSC.u4Data = (uint32)DMA_DTFSC_DRQC * (uint32)DMA_DTFSC_DRQC_TRANS_REQ_CLEAR;

	Reg_DTS.unDTSCTL1.u4Data = (uint32)DMA_DTSCTL1_DTSUST * (uint32)DMA_DTSCTL1_DTSUST_START;

	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSL.u4Data = (uint32)DMA_DTFSL_REQEN * (uint32)DMA_DTFSL_REQEN_TRANS_ENABLE;
	
	Bswlib_Sync_Pipeline_4( Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSL.u4Data );
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Trans Disable Function																	*/
/*	return		: void																			*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_DisableTrans( uint8 t_u1ChannelID )
{
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSL.u4Data = (uint32)DMA_DTFSL_REQEN * (uint32)DMA_DTFSL_REQEN_TRANS_DISABLE;	/* DMA transfer request disabled(not interrupted) */

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
void	Pil_Dts_SetTransMode( uint8 t_u1ChannelID, uint8 t_u1TransSize, uint8 t_u1DmaMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, uint16 t_u2TransNum )
{
	uint32		t_u4Dttct;		/* DTTCT register setting value */
	uint32		t_u4Mode;
	uint32		t_u4RegCM;


	/* DI_ALL()";" */ /* There is no use case for calling Enable, SetInterrupt, or this function from a high-priority task during SetTransMode execution for the same DTS channel, so there is no need to call the function for blocking interrupts. */

	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSL.u4Data = (uint32)DMA_DTFSL_REQEN * (uint32)DMA_DTFSL_REQEN_TRANS_DISABLE;	/* DMA transfer request disabled(not interrupted) */

	Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTSA = (uint32)((volatile const uint32*)t_pcvdSrcAdr);				/* Source address settings */
	Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTDA = (uint32)((volatile const uint32*)t_pcvdDestAdr);				/* Destination address configuration */
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTC.u4Data = (uint32)t_u2TransNum;
				/*	The following processing is commented out (QAC compatible) because the calculation result is fixed at t_u2TransNum */
				/*	(uint32)DMA_DTTC_ARC_0		* (uint32)DMA_DTTC_ARC_NOUSE	+	""*/		/* Address reload count:0 */
				/*	(uint32)DMA_DTTC_TRC_0		* t_u2TransNum";"					*/			/* Number of transfers setting */
	
	/* Transfer count compare setting based on errata TN-RH8-B0442A/J workaround 1*/
	/* As SetMasterCh and SetTransMode will not be called at the same time, DI_ALL  and EI_ALL are not used for RMW */
	
	t_u4RegCM = (uint32)(Reg_DTS.unDTSCM[t_u1ChannelID].u4Data & (uint32)(~(uint32)DMA_DTSCM_CMC));
	Reg_DTS.unDTSCM[t_u1ChannelID].u4Data = (uint32)(t_u4RegCM | (uint32)(((uint32)t_u2TransNum >> (uint32)1) + (uint32)1));	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
	
	
	/* Transfer Control Register (DTTCT) settings */
	t_u4Dttct = Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTCT.u4Data;
	t_u4Dttct &= (uint32)((uint32)DMA_DTTCT_CCE + (uint32)DMA_DTTCT_TCE);				/* CCE, TCE set current value */
	t_u4Mode = cu4PIL_DTS_MODE_TABLE[t_u1DmaMode];
	t_u4Dttct |= (uint32)(t_u4Mode +											/* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
			/*	The following processing is commented out (QAC compatible) because the result of the calculation is fixed at 0. */
			/*	(uint32)DMA_DTTCT_ESE		* (uint32)DMA_DTTCT_ESE_CONTINUE	+	""*/		/* Do not abort DMA transfer on DMA transfer error. */
			/*	(uint32)DMA_DTTCT_CHNSEL_0	* (uint32)DMA_DTTCT_CHNSEL_CH0		+	""*/		/* Channel to chain to */
			/*	(uint32)DMA_DTTCT_CHNE_0	* (uint32)DMA_DTTCT_CHNE_DISABLE	+	""*/		/* Chain function disabled */
				(uint32)DMA_DTTCT_DS_0		* t_u1TransSize);							/* Transfer data size setting */	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTCT.u4Data = t_u4Dttct;

	/* When Reload Function 1 is ON	*/
	if( (t_u4Dttct & (uint32)DMA_DTTCT_RLD1M) != (uint32)( (uint32)DMA_DTTCT_RLD1M_0 * (uint32)DMA_DTTCT_RLD1M_DISABLE ) )
	{
		Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTRSA = (uint32)((volatile const uint32*)t_pcvdSrcAdr); 	/* Set reload source address  */
		Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTRDA = (uint32)((volatile const uint32*)t_pcvdDestAdr);	/* Set reload destination address */
		Reg_DTS.stDTS_CH[t_u1ChannelID].unDTRTC.u4Data = (uint32)t_u2TransNum;
				/*	The following processing is commented out (QAC compatible) because the calculation result is fixed at the value of t_u2TransNum. */
				/*	(uint32)DMA_DTRTC_RARC_0	* (uint32)DMA_DTRTC_RARC_NOUSE	+ "" */			/* Reload Address reload count: 0 */
				/*	(uint32)DMA_DTRTC_RTRC_0	* t_u2TransNum ";" 			  */			/* Reload/Setting the number of transfers */
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
void	Pil_Dts_SetTransModeTwoStepReload( uint8 t_u1ChannelID, uint8 t_u1TransSize, uint8 t_u1DmaMode, volatile const void* t_pcvdSrcAdr, volatile const void* t_pcvdDestAdr, uint16 t_u2TransNum, uint16 t_u2AddrReloadCnt )
{
	uint32		t_u4Dttct;		/* DTTCT register setting value */
	uint32		t_u4Mode;
	uint32		t_u4RegCM;


	/* DI_ALL()";" */ /* There is no use case for calling Enable, SetInterrupt, or this function from a high-priority task during SetTransMode execution for the same DTS channel, so there is no need to call the function for blocking interrupts. */

	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSL.u4Data = (uint32)DMA_DTFSL_REQEN * (uint32)DMA_DTFSL_REQEN_TRANS_DISABLE;	/* DMA transfer request disabled(not interrupted) */

	Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTSA = (uint32)((volatile const uint32*)t_pcvdSrcAdr);		/* Source address settings */
	Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTDA = (uint32)((volatile const uint32*)t_pcvdDestAdr);		/* Destination address configuration */
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTC.u4Data = 
				(uint32)(((uint32)DMA_DTTC_ARC_0		* (uint32)t_u2AddrReloadCnt)	+(uint32)t_u2TransNum);		/* Address reload count settings */		/* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
				/*	The following processing is commented out (QAC compatible) because the calculation result is fixed at the value of t_u2TransNum. */
				/*	(uint32)DMA_DTTC_TRC_0		* t_u2TransNum";" */					/* Number of transfers setting */
	
	/* Transfer count compare setting based on errata TN-RH8-B0442A/J workaround 1*/
	/* As SetMasterCh and SetTransMode will not be called at the same time, DI_ALL  and EI_ALL are not used for RMW */
		
	t_u4RegCM = (uint32)(Reg_DTS.unDTSCM[t_u1ChannelID].u4Data & (uint32)(~(uint32)DMA_DTSCM_CMC));
	Reg_DTS.unDTSCM[t_u1ChannelID].u4Data = (uint32)(t_u4RegCM | (uint32)(((uint32)t_u2TransNum >> (uint32)1) + (uint32)1));	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
	

	/* Transfer Control Register (DTTCT) settings */
	t_u4Dttct = Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTCT.u4Data;
	t_u4Dttct &= (uint32)((uint32)DMA_DTTCT_CCE + (uint32)DMA_DTTCT_TCE);				/* CCE, TCE set current value */
	t_u4Mode = cu4PIL_DTS_MODE_TABLE[t_u1DmaMode];
	t_u4Dttct |= (uint32)(t_u4Mode +												/* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
			/*	The following processing is commented out (QAC compatible) because the result of the calculation is fixed at 0. */
			/*	(uint32)DMA_DTTCT_ESE		* (uint32)DMA_DTTCT_ESE_CONTINUE	+ ""*/	/* Do not abort DMA transfer when DMA transfer error occurs */
			/*	(uint32)DMA_DTTCT_CHNSEL_0	* (uint32)DMA_DTTCT_CHNSEL_CH0		+ ""*/	/* Channel to chain to */
			/*	(uint32)DMA_DTTCT_CHNE_0	* (uint32)DMA_DTTCT_CHNE_DISABLE	+ ""*/	/* Chain function disabled */
				(uint32)DMA_DTTCT_DS_0		* (uint32)t_u1TransSize);						/* Transfer data size setting */	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTCT.u4Data = t_u4Dttct;

	/* When either of the reload functions 1 or 2 is ON	*/
	if( (t_u4Dttct & ((uint32)DMA_DTTCT_RLD1M + (uint32)DMA_DTTCT_RLD2M)) !=
			(uint32)( ( (uint32)DMA_DTTCT_RLD1M_0 * (uint32)DMA_DTTCT_RLD1M_DISABLE ) + ( (uint32)DMA_DTTCT_RLD2M_0 * (uint32)DMA_DTTCT_RLD2M_DISABLE ) ) )
	{
		Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTRSA = (uint32)((volatile const uint32*)t_pcvdSrcAdr); 	/* Set reload source address */
		Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTRDA = (uint32)((volatile const uint32*)t_pcvdDestAdr);	/* Set reload destination address */
		Reg_DTS.stDTS_CH[t_u1ChannelID].unDTRTC.u4Data = 
					(uint32)(((uint32)DMA_DTRTC_RARC_0	* (uint32)t_u2AddrReloadCnt)	+ (uint32)t_u2TransNum);	/* Reload Address reload count settings */	/* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
					/* The following processing is commented out (QAC compatible) because the calculation result is fixed at the value of t_u2TransNum */
					/*	(uint32)DMA_DTRTC_RTRC_0	* t_u2TransNum";" */					/* Reload Number of transfers setting */
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
void	Pil_Dts_SetInterrupt( uint8 t_u1ChannelID, uint8 t_u1HalfIe, uint8 t_u1EndIe )
{
	uint32		t_u4Reg;

	t_u4Reg = ((uint32)DMA_DTTCT_CCE * t_u1HalfIe) + ((uint32)DMA_DTTCT_TCE * t_u1EndIe);	/* justification for QAC warning 3384(3383): it is not wrap-around within a configuration range */ /* EDET_INT30 */

	/* DI_ALL()";" *//* There is no use case for calling SetTransMode, or this function from a high-priority task, so there is no need to call the function for blocking interrupts. */
	t_u4Reg |= (uint32)( Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTCT.u4Data & (uint32)(~((uint32)DMA_DTTCT_CCE + (uint32)DMA_DTTCT_TCE) ));
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTCT.u4Data = t_u4Reg;

	Bswlib_Sync_Pipeline_4( Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTCT.u4Data );
	/* EI_ALL()";" */
}

#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
/*----------------------------------------------------------------------------------------------*/
/*	DTS Intc Interrupt Enable Set Function														*/
/*	return		: void																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_EnableIntcInterrupt( void )
{
	sint32		i;
	
	for( i = (sint32)0; i < s4PIL_DTS_INT_NUM; i++ )
	{
		Pil_Intc2_SetInterrupt( (uint16)i + (uint16)INTC_CH_DTS_CH31TO0, DMA_ON );
	}
}
#endif

#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
/*----------------------------------------------------------------------------------------------*/
/*	DTS Intc Interrupt Disable Set Function														*/
/*	return		: void																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_DisableIntcInterrupt( void )
{
	sint32		i;
	
	for( i = (sint32)0; i < s4PIL_DTS_INT_NUM; i++ )
	{
		Pil_Intc2_SetInterrupt( (uint16)i + (uint16)INTC_CH_DTS_CH31TO0, DMA_OFF );
	}
}
#endif

/*----------------------------------------------------------------------------------------------*/
/*	DTS Transfer completed state Function														*/
/*	return		: Transfer end flag ( =0:transfer not complete / =1:transfer complete)			*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
uint8		Pil_Dts_IsTransferCompleted( uint8 t_u1ChannelID )
{
	uint32				t_u4Dtfst;
	uint8				t_u1Ret;

	t_u1Ret = (uint8)FALSE;

	t_u4Dtfst = Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFST.u4Data;
	if(( t_u4Dtfst & (uint32)DMA_DTFST_TC ) != (uint32)DMA_DTFST_TC_NOTCOMPLETE )
	{
		t_u1Ret = (uint8)TRUE;
	}

	return( t_u1Ret );
}

/*----------------------------------------------------------------------------------------------*/
/*	Compare Match Status Clear Function															*/
/*	return		: void																			*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_ClearMatchStatus( uint8 t_u1ChannelID )
{
	volatile uint32                 t_u4Reg;
	uint32                          t_u4ClrBit;
	uint8                          t_u1PintId;

	/* Get the appropriate PINT register number and bit position to clear. */
	t_u1PintId = ( t_u1ChannelID >> u1PIL_DTS_SHIFT_NUM );
	t_u4ClrBit = ( u4PIL_DTS_PINTBITSIFT << (t_u1ChannelID & u1PIL_DTS_PINTBITMASK) );

	DMA_ENTER_CRITICAL_SECTION();
		/* Clear transfer count match flag and transfer complete flag */
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSC.u4Data = ((uint32)DMA_DTFSC_CCC * (uint32)DMA_DTFSC_CCC_COMPARE_CLEAR) + ((uint32)DMA_DTFSC_TCC * (uint32)DMA_DTFSC_TCC_COMPLETE_CLEAR);
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
void*	Pil_Dts_GetDestinationAddress( uint8 t_u1ChannelID )
{
	uint32* t_pu4DestAdr;
	
	t_pu4DestAdr = (uint32*)Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTDA;
	
	return( (void*)t_pu4DestAdr);
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Trans Count Get Function																*/
/*	return		: Trans Count																	*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
uint16		Pil_Dts_GetTransCount( uint8 t_u1ChannelID )
{
	return( (uint16)Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTC.u4Data );	/* Retrieve only the lower 2 bytes (TRC bits) */
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Trans Count Reset Function																*/
/*	return		: none																			*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_ResetTransCount( uint8 t_u1ChannelID )
{
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTC.u4Data = (uint32)0;
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Trans Status Get Function																*/
/*	return		: Trans Status ( =0:IDLE / =1:BUSY)												*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
uint8		Pil_Dts_GetTransStatus( uint8 t_u1ChannelID )
{
	uint32				t_u4Dtssts;
	uint8				t_u1TransStat;

	t_u1TransStat = (uint8)DMA_DTSSTS_DTSACT_IDLE;

	t_u4Dtssts = Reg_DTS.unDTSSTS.u4Data;
	if(  (( t_u4Dtssts & (uint32)DMA_DTSSTS_DTSACT ) != (uint32)DMA_DTSSTS_DTSACT_IDLE )							/* If there is a channel that is DMA forwarding and */
	  && ((( t_u4Dtssts & (uint32)DMA_DTSSTS_DTSACH ) >> DMA_DTSSTS_DTSACH_OFFSET ) == (uint32)t_u1ChannelID ))		/*  the channel is t_u1ChannelID */ 
	{
		t_u1TransStat = (uint8)DMA_DTSSTS_DTSACT_BUSY;
	}

	return( t_u1TransStat );
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Error Check Function																	*/
/*	return		: Error Status																	*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
sint32	Pil_Dts_CheckDmaError( void )
{
	uint32 t_u4ErrFlag;
	/* Check if any of the DTS CHs are experiencing DMA transfer errors */
	/* The DTSERCH bit that holds the CH of the error occurrence indicates the first CH at the time of the error occurrence in E1MS2,*/
	/*  but the microcomputer specification has changed to indicate the minimum CH of the error occurrence in E2x. */
	t_u4ErrFlag = (Reg_DTS.unDTSER.u4Data & (uint32)DMA_DTSER_DTSER);

	return ( (sint32)t_u4ErrFlag );
}

/*----------------------------------------------------------------------------------------------*/
/*	DTS Error Status Clear Function																*/
/*	return		: none																			*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_ClearDmaError( uint8 t_u1ChannelID )
{
	/* Clear transfer error flag for specified CH */
	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTFSC.u4Data = (uint32)DMA_DTFSC_ERC	* (uint32)DMA_DTFSC_ERC_TRANS_ERR_CLEAR;
}

#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
/*----------------------------------------------------------------------------------------------*/
/*	DTS  Set  Transfer Request Group Function													*/
/*	return		: none																			*/
/*	parameters	: Request group number (0-767)													*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_SetTransReqGroup( uint16 t_u2RequestGroup )
{
	Pil_Dts_RequestGroupType t_udRequestGroup;
	uint32 t_u4GroupData;
	uint8 t_u1RegChannel;
	uint8 t_u1Register;

	t_udRequestGroup.u2Data = t_u2RequestGroup;
	t_u1RegChannel = (uint8)t_udRequestGroup.stDiv.b3RegCh;
	t_u1Register = (uint8)t_udRequestGroup.stDiv.b4RegNum;
	t_u4GroupData = (uint32)t_udRequestGroup.stDiv.b3Group;

	t_u4GroupData = (uint32)(t_u4GroupData << (uint32)((uint32)t_u1RegChannel * (uint32)DMA_DTS_SEL_BIT_NUM));		/* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
	Reg_DMATRGSEL.unDTSSEL[t_u1Register].u4Data |= t_u4GroupData;

}
#endif

#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
#if ( DMA_CFG_REG_CHK == STD_ON )
/*----------------------------------------------------------------------------------------------*/
/*	Service name	:	CheckTransReqGroup														*/
/*	Parameters (in)	:	Request group number (0-767)											*/
/*	Return value	:	Register error Status													*/
/*----------------------------------------------------------------------------------------------*/
uint32	Pil_Dts_CheckTransReqGroup( uint16 t_u2RequestGroup )
{
	Pil_Dts_RequestGroupType t_udRequestGroup;
	uint32 t_u4GroupData;
	uint32 t_u4DtsSelReg;
	uint8 t_u1RegChannel;
	uint8 t_u1Register;
	uint32 t_u4Ret;

	t_u4Ret = DMA_REGCHK_OK;

	t_udRequestGroup.u2Data = t_u2RequestGroup;
	t_u1RegChannel = (uint8)t_udRequestGroup.stDiv.b3RegCh;
	t_u1Register = (uint8)t_udRequestGroup.stDiv.b4RegNum;
	t_u4GroupData = (uint32)t_udRequestGroup.stDiv.b3Group;

	t_u4DtsSelReg = (uint32)((Reg_DMATRGSEL.unDTSSEL[t_u1Register].u4Data >> ((uint32)((uint32)t_u1RegChannel * (uint32)DMA_DTS_SEL_BIT_NUM)))& (uint32)DMA_DTSSEL_SEL0 ); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */

	if (t_u4DtsSelReg != t_u4GroupData)
	{
#if ( DMA_CFG_REG_REFRESH == STD_ON )
		/* Rewrite */
		Reg_DMATRGSEL.unDTSSEL[t_u1Register].u4Data &= (uint32)(~(uint32)((uint32)DMA_DTSSEL_SEL0 << (uint32)((uint32)t_u1RegChannel * (uint32)DMA_DTS_SEL_BIT_NUM))); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
		Pil_Dts_SetTransReqGroup(t_u2RequestGroup);
		/* ReCheck */
		t_u4DtsSelReg = (uint32)((Reg_DMATRGSEL.unDTSSEL[t_u1Register].u4Data >> ((uint32)((uint32)t_u1RegChannel * (uint32)DMA_DTS_SEL_BIT_NUM)))& (uint32)DMA_DTSSEL_SEL0 ); /* justification for QAC warning 3383: it is not wrap-around within a configuration range */ /* EDET_INT30 */
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
uint32	Pil_Dts_CheckIntcReg( void )
{
	sint32	i;
	uint32	t_u4Ret;
	uint8	t_u1IntEnable;

	t_u4Ret = DMA_REGCHK_OK;

	for( i = (sint32)0; (i < s4PIL_DTS_INT_NUM); i++ )
	{
		t_u1IntEnable = Pil_Intc2_GetInterrupt((uint16)((uint16)i + (uint16)INTC_CH_DTS_CH31TO0)); 
		
		if ( t_u1IntEnable != (uint8)DMA_ON )
		{	
#if ( DMA_CFG_REG_REFRESH == STD_ON )
			/* Rewrite */
			Pil_Intc2_SetInterrupt( (uint16)i + (uint16)INTC_CH_DTS_CH31TO0, DMA_ON );
			/* ReCheck */
			t_u1IntEnable = Pil_Intc2_GetInterrupt((uint16)((uint16)i + (uint16)INTC_CH_DTS_CH31TO0)); 

			if ( t_u1IntEnable != (uint8)DMA_ON )
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
#endif

/*----------------------------------------------------------------------------------------------*/
/*	DTS  Ram Clear Function																		*/
/*	return		: none																			*/
/*	parameters	: DTS Channel (0-127)															*/
/*----------------------------------------------------------------------------------------------*/
/*void	Pil_Dts_ClearRam( uint8 t_u1ChannelID )""*/
/*{*/

	/* Comment out the following, in hopes of initializing with a flash option byte */

	/* DTS */
	/* DTSRAM Initialization(It may be referred to before setting DTSRAM, so uniformly initialize it with Init.) */
/*	Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTSA = (uint32)0";"*/
/*	Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTDA = (uint32)0";"*/
/*	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTC.u4Data = (uint32)0";"*/
/*	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTTCT.u4Data = (uint32)0";"*/
/*	Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTRSA = (uint32)0";"*/
/*	Reg_DTS.stDTS_CH[t_u1ChannelID].u4DTRDA = (uint32)0";"*/
/*	Reg_DTS.stDTS_CH[t_u1ChannelID].unDTRTC.u4Data = (uint32)0";"*/

/*}*/

#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
/*----------------------------------------------------------------------------------------------*/
/*	DTS  Set Master Channel Function															*/
/*	return		: none																			*/
/*	parameters	: none															*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_SetMasterCh( void )
{
	sint32		i;

	/* Set the same SPID as the default to 29. */
	/* Reconfigure because the option byte sets 0. */
	for( i = (sint32)0; i < (sint32)DMA_DTS_CH_NUM; i++ )
	{
		Reg_DTS.unDTSCM[i].u4Data = (uint32)( ( (uint32)DMA_DTSCM_SPID_0 * u4PIL_DTS_SPIDNUM ) );
	}
}
#endif

#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
/*----------------------------------------------------------------------------------------------*/
/*	DTS  Set Priority Function																	*/
/*	return		: none																			*/
/*	parameters	: DTS Channel (0-127)															*/
/*				: DTS Priority Level (0-3)														*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_SetPriority( uint8 t_u1ChannelID, uint8 t_u1PriLevel )
{
	Pil_Dts_ChDiv		t_unDtsChDiv;

	t_unDtsChDiv.u1Ch = t_u1ChannelID;
	Reg_DTS.unDTSPR[t_unDtsChDiv.stBit.b4RegNum].u4Data |= (uint32)(((uint32)1 << (uint32)(t_unDtsChDiv.stBit.b4RegCh * (uint32)2)) * (uint32)t_u1PriLevel);	/* justification for QAC warning 3384(3383): it is not wrap-around within a configuration range */ /* EDET_INT30 */

}
#endif

/*----------------------------------------------------------------------------------------------*/
/*	DTS  Set Init Priority All Channel Function													*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
/*void	Pil_Dts_SetInitPriorityAllCh( void )""*/
/*{*/
/*	sint32		i";"*/

	/* Set All Channels to Priority 2 */
/*	for( i = (sint32)0; i < (sint32)DMA_DTS_PRI_NUM; i++ )""*/
/*	{*/
/*		Reg_DTS.unDTSPR[i].u4Data = (uint32)DMA_DTSPR_PR_ALL2";"*/
/*	}*/
/*}*/

#if ( DMA_CFG_GLOBAL_REG_CONTROL == STD_ON )
/*----------------------------------------------------------------------------------------------*/
/*	DTS  Disable Trans All Function																*/
/*	return		: none																			*/
/*	parameters	: none																			*/
/*----------------------------------------------------------------------------------------------*/
void	Pil_Dts_DisableTransAll( void )
{
	sint32		i;

	/* All DMA transfer requests disabled */
	/* DTS */
	for( i = (sint32)0; i < (sint32)DMA_DTS_CH_NUM; i++ )
	{
		Reg_DTS.stDTS_CH[i].unDTFSL.u4Data = (uint32)DMA_DTFSL_REQEN * (uint32)DMA_DTFSL_REQEN_TRANS_DISABLE;	/* DMA transfer request disabled */
	}
}
#endif

/*==============================================================================================*/
/*	Local Functions																				*/
/*==============================================================================================*/

#define DMA_STOP_SEC_TEXT_CODE
#include "Dma_MemMap.h"
/*-- End Of File -------------------------------------------------------------------------------*/
