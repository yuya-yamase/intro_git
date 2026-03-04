/* ADC-r04-303 */
/************************************************************************************************/
/*																								*/
/*		ADC Driver : Upper layer for RH850U2A/U2B												*/
/*																								*/
/*		Copyright : DENSO CORPORATION															*/
/*																								*/
/************************************************************************************************/
/*==============================================================================================*/
/* include files																				*/
/*==============================================================================================*/
#include "Std_Types.h"
#include "Mcal_SpalCmn.h"

#include "Adc.h"
#include "Adc_Pil.h"
#ifdef ADC_USE_DMA
#include "Dma.h"
#endif
#if (ADC_CFG_DET_REPORT_RUNTIMEERROR==STD_ON)
#include "Det.h"
#endif

/*==============================================================================================*/
/* defines / data types / structs / unions	/ macros											*/
/*==============================================================================================*/

/*--------------------------------------------------------------------------*/
/* defines - DMA															*/
/*--------------------------------------------------------------------------*/
#ifdef ADC_USE_DMA
#define	ADC_DMA_TRANSACTION_SIZE			(u1DMA_TRANSSIZE_2)				/* DR register size						*/
#define	ADC_DMA_MODE_SINGLE					((uint8)DMA_DMAMODE3)			/* mode=3 : single transfer wo reload	*/
#define	ADC_DMA_MODE_STREAMING				((uint8)DMA_DMAMODE5)			/* mode=5 : block transfer with Reload	*/
#endif

/*--------------------------------------------------------------------------*/
/* defines - Run Time Error													*/
/*--------------------------------------------------------------------------*/
#if (ADC_CFG_DET_REPORT_RUNTIMEERROR==STD_ON)
	#define Adc_ReportRunTimeError(aID,eID)	(void)Det_ReportRuntimeError(MCAL_ADC_MODULE_ID, ADC_INSTANCE_ID, aID, eID)
#else
	#define Adc_ReportRunTimeError(aID,eID)							/* empty 	*/
#endif

/*--------------------------------------------------------------------------*/
/* structs																	*/
/*--------------------------------------------------------------------------*/
/* Adc Group information */
typedef struct {
	Adc_StatusType				udStatus;				/* Conversion status							*/
	#if (ADC_CFG_GRP_NOTIF_CAPABILITY==STD_ON)
	boolean						blisNotifyOn;			/* Conversion End Notification On				*/
	#endif
	#ifdef ADC_USE_DMA
	Adc_ValueGroupType*			pudDataBuffer;			/* pointer to result data buffer				*/
	#endif
	#if (defined(ADC_USE_TH))
	Adc_TrackHoldGroupType		udTHGrp;				/* Track and Hold Setting						*/
	#endif
	#ifdef ADC_USE_STREAMING_ACCESS
	Adc_StreamNumSampleType		udStreamingNum;			/* Number of conversions in streaming access mode */
	#endif
} Adc_GrpInfoType;

/*==============================================================================================*/
/* constants																					*/
/*==============================================================================================*/
/*==============================================================================================*/
/* variables																					*/
/*==============================================================================================*/
#define ADC_START_SEC_VAR_NO_INIT_GLOBAL_UNSPECIFIED
#include "Adc_MemMap.h"
/* Adc Group information */
static 	VAR(Adc_GrpInfoType, ADC_VAR_NO_INIT) s_stAdcGrpInfo[ADC_CFG_GRP_SIZE];
#define ADC_STOP_SEC_VAR_NO_INIT_GLOBAL_UNSPECIFIED
#include "Adc_MemMap.h"

/*==============================================================================================*/
/* prototype for local functions																*/
/*==============================================================================================*/
#define ADC_START_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"
/*--------------------------------------------------------------------------*/
/* always available															*/
/*--------------------------------------------------------------------------*/
static FUNC(void, ADC_CODE) Adc_DataInit(void);
static FUNC(void, ADC_CODE) Adc_SetGrpStatus(
	CONST(Adc_GroupType,	ADC_CONST)	t_cudGrp,
	CONST(Adc_StatusType,	ADC_CONST)	t_cudCrntStatus,
	CONST(Adc_StatusType,	ADC_CONST)	t_cudNextStatus
);
#if ((ADC_CFG_START_STOP_GRP_API==STD_ON)||(ADC_CFG_READ_GRP_API==STD_ON)||(ADC_CFG_HW_TRG_API==STD_ON))
static FUNC(void, ADC_CODE) Adc_CnvEndIntrptDisable(
	CONST(Adc_GroupType,	ADC_CONST)	t_cudGrp
);
#endif

/*--------------------------------------------------------------------------*/
/* only when Notify is available											*/
/*--------------------------------------------------------------------------*/
#if (ADC_CFG_GRP_NOTIF_CAPABILITY==STD_ON)
static FUNC(void, ADC_CODE) Adc_SetNotifyFlag(
	CONST(Adc_GroupType, ADC_CONST)	t_cudGrp,
	CONST(boolean, ADC_CONST)		t_cblisNotifyOn
);
static FUNC(boolean, ADC_CODE) Adc_GetNotifyFlag(
	CONST(Adc_GroupType, ADC_CONST)	t_cudGrp
);
static FUNC(void, ADC_CODE) Adc_CnvEndNotify(
	CONST(Adc_GroupType, ADC_CONST) t_cudGrp
);
#endif

#define ADC_STOP_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

/*--------------------------------------------------------------------------*/
/* only when Interrupt is available											*/
/*--------------------------------------------------------------------------*/
#define ADC_START_SEC_CODE_FAST_GLOBAL
#include "Adc_MemMap.h"

#ifdef ADC_USE_CNV_INT
static FUNC(void, ADC_CODE) Adc_ISR_CnvEnd(
	CONST(Adc_GroupType,	ADC_CONST) t_cudGrp
);
#if (defined(ADC_USE_ISR_ADC_HWUNIT0_SG0) || defined(ADC_USE_ISR_DMA_HWUNIT0_SG0))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit0_SG0(void);
#endif
#if (defined(ADC_USE_ISR_ADC_HWUNIT0_SG1) || defined(ADC_USE_ISR_DMA_HWUNIT0_SG1))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit0_SG1(void);
#endif
#if (defined(ADC_USE_ISR_ADC_HWUNIT0_SG2) || defined(ADC_USE_ISR_DMA_HWUNIT0_SG2))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit0_SG2(void);
#endif
#if (defined(ADC_USE_ISR_ADC_HWUNIT0_SG3) || defined(ADC_USE_ISR_DMA_HWUNIT0_SG3))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit0_SG3(void);
#endif
#if (defined(ADC_USE_ISR_ADC_HWUNIT0_SG4) || defined(ADC_USE_ISR_DMA_HWUNIT0_SG4))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit0_SG4(void);
#endif
#if (defined(ADC_USE_ISR_ADC_HWUNIT1_SG0) || defined(ADC_USE_ISR_DMA_HWUNIT1_SG0))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit1_SG0(void);
#endif
#if (defined(ADC_USE_ISR_ADC_HWUNIT1_SG1) || defined(ADC_USE_ISR_DMA_HWUNIT1_SG1))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit1_SG1(void);
#endif
#if (defined(ADC_USE_ISR_ADC_HWUNIT1_SG2) || defined(ADC_USE_ISR_DMA_HWUNIT1_SG2))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit1_SG2(void);
#endif
#if (defined(ADC_USE_ISR_ADC_HWUNIT1_SG3) || defined(ADC_USE_ISR_DMA_HWUNIT1_SG3))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit1_SG3(void);
#endif
#if (defined(ADC_USE_ISR_ADC_HWUNIT1_SG4) || defined(ADC_USE_ISR_DMA_HWUNIT1_SG4))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit1_SG4(void);
#endif
#if (defined(ADC_USE_ISR_ADC_HWUNIT2_SG0) || defined(ADC_USE_ISR_DMA_HWUNIT2_SG0))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit2_SG0(void);
#endif
#if (defined(ADC_USE_ISR_ADC_HWUNIT2_SG1) || defined(ADC_USE_ISR_DMA_HWUNIT2_SG1))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit2_SG1(void);
#endif
#if (defined(ADC_USE_ISR_ADC_HWUNIT2_SG2) || defined(ADC_USE_ISR_DMA_HWUNIT2_SG2))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit2_SG2(void);
#endif
#if (defined(ADC_USE_ISR_ADC_HWUNIT2_SG3) || defined(ADC_USE_ISR_DMA_HWUNIT2_SG3))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit2_SG3(void);
#endif
#if (defined(ADC_USE_ISR_ADC_HWUNIT2_SG4) || defined(ADC_USE_ISR_DMA_HWUNIT2_SG4))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit2_SG4(void);
#endif

#endif

#define ADC_STOP_SEC_CODE_FAST_GLOBAL
#include "Adc_MemMap.h"

/*--------------------------------------------------------------------------*/
/* only when DMA is available												*/
/*--------------------------------------------------------------------------*/
#ifdef ADC_USE_DMA
#define ADC_START_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"
static FUNC(void, ADC_CODE) Adc_SetDataBuffer(
	CONST(Adc_GroupType,					ADC_CONST)		t_cudGrp,
	P2VAR(Adc_ValueGroupType, AUTOMATIC,	ADC_VAR_INIT)	t_pudDataBuffer
);
static FUNC_P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_CODE) Adc_GetDataBuffer(
	CONST(Adc_GroupType, ADC_CONST) t_cudGrp
);

/*--------------------------------------------------------------------------*/
/* only when Streaming Access is available									*/
/*--------------------------------------------------------------------------*/
#ifdef ADC_USE_STREAMING_ACCESS
static FUNC(Adc_StreamNumSampleType, ADC_CODE) Adc_GetCurrentStreamingNum(
	CONST(Adc_GroupType,  ADC_CONST) t_cudGrp
);
#endif

#define ADC_STOP_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"
#endif

/*----------------------------------------------------------------------------------------------*/
/* Public API 																					*/
/*----------------------------------------------------------------------------------------------*/
#define ADC_START_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

/************************************************************************************************/
/* Service name			: Adc_Init																*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		ConfigPtr		: Pointer to configuration set(not supported)							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Initializes the ADC hardware units and driver.						*/
/************************************************************************************************/
FUNC(void, ADC_CODE) Adc_Init(
	P2CONST(Adc_ConfigType, AUTOMATIC, ADC_CONST)	ConfigPtr
)
{
	(void)ConfigPtr;			/* avoid warning	*/
	Adc_Pil_Init();				/* HW Initialize	*/
	#if	(ADC_CFG_GLOBAL_REG_CONTROL == STD_ON)
	Pic2_Init();				/* PIC2 Initialize	*/
	#endif
	Adc_DataInit();				/* SW Initialize	*/
}

/************************************************************************************************/
/* Service name			: Adc_SetupResultBuffer													*/
/* Sync/Async			: Asynchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/*		DataBufferPtr	: sync: pointer to result data buffer									*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: Std_ReturnType														*/
/*		E_OK			: result buffer pointer initialized correctly							*/
/*		E_NOT_OK		: operation failed or development error occured							*/
/* Description			: Initializes ADC driver with the group specific result buffer 			*/
/*						  start address where the conversion results will be stored. 			*/
/*						  The application has to ensure that the application buffer,			*/
/*						  where DataBufferPtr points to, can hold all the conversion results	*/
/*						  of the specified group.												*/
/*						  The initialization with Adc_SetupResultBuffer is required after reset,*/
/*						  before a group conversion can be started.								*/
/************************************************************************************************/
#ifdef ADC_USE_DMA
FUNC(Std_ReturnType, ADC_CODE) Adc_SetupResultBuffer(
	VAR(	Adc_GroupType,					ADC_VAR_INIT)	Group,
	P2VAR(	Adc_ValueGroupType, AUTOMATIC,	ADC_VAR_INIT)	DataBufferPtr
)
{
	VAR(Std_ReturnType, ADC_VAR_NO_INIT)			t_udResult;
	VAR(Adc_StatusType, ADC_VAR_NO_INIT)			t_udCrntStatus;

	ADC_ENTER_CRITICAL_SECTION(ADC_CODE);
	t_udResult		= E_NOT_OK;
	t_udCrntStatus	= Adc_GetGrpStatus(Group);
	if (t_udCrntStatus==ADC_IDLE) {
		Adc_SetDataBuffer(Group, DataBufferPtr);
		t_udResult = E_OK;
	} else {
		Adc_ReportRunTimeError(ADC_AID_SETUP_RESULT_BUFFER,ADC_E_BUSY);		/* SWS_Adc_00433	*/
	}
	ADC_EXIT_CRITICAL_SECTION(ADC_CODE);
	return(t_udResult);
}
#endif

/************************************************************************************************/
/* Service name			: Adc_DeInit															*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Returns all ADC HW Units to a state comparable to						*/
/*						  their power on reset state.											*/
/************************************************************************************************/
#if (ADC_CFG_DEINIT_API==STD_ON)
FUNC(void, ADC_CODE) Adc_DeInit(void)
{
	VAR(boolean,		ADC_VAR_NO_INIT)			t_b1isRunning;

	t_b1isRunning = Adc_IsRunning();
	if (t_b1isRunning ==TRUE) {
		Adc_ReportRunTimeError(ADC_AID_DEINIT,ADC_E_BUSY);		/* SWS_Adc_00112	*/
	} else {
		#ifdef ADC_USE_TH
		Adc_Pil_DisableAllTHTrigger();
		#endif
		Adc_Pil_DisableSGHWTrigger();
		Adc_Pil_ForcedTermination();
		#ifdef ADC_USE_TH
		Adc_Pil_StopAllTrackHold();
		Adc_Pil_DisableAllTHOperation();
		#endif
	}
}
#endif

/************************************************************************************************/
/* Service name			: Adc_StartGroupConversion												*/
/* Sync/Async			: Asynchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Starts the conversion of all channels of the requested 				*/
/*						  ADC Channel group.													*/
/************************************************************************************************/
#if (ADC_CFG_START_STOP_GRP_API==STD_ON)
FUNC(void, ADC_CODE) Adc_StartGroupConversion(
	VAR(Adc_GroupType, ADC_VAR_INIT) Group
)
{
				VAR(Adc_HWUnitType,						ADC_VAR_NO_INIT) 		t_udHWUnit;
				VAR(Adc_SGType,							ADC_VAR_NO_INIT) 		t_udSG;
				VAR(Adc_StatusType,						ADC_VAR_NO_INIT)		t_udCrntStatus;
				VAR(Adc_StatusType,						ADC_VAR_NO_INIT)		t_udNextStatus;
				VAR(Adc_TriggerSourceType,				ADC_VAR_NO_INIT)		t_udTrgMode;
				VAR(Adc_GroupConvModeType,				ADC_VAR_NO_INIT)		t_udCnvMode;
				VAR(uint8,								ADC_VAR_NO_INIT)		t_u1DMAOn;
				VAR(uint8,								ADC_VAR_NO_INIT)		t_u1IntrptUse;
				VAR(uint8,								ADC_VAR_NO_INIT)		t_u1StreamingAcces;
	#ifdef ADC_USE_DMA
				VAR(uint16,								ADC_VAR_NO_INIT)		t_u2CnvChSize;
				VAR(uint8,								ADC_VAR_NO_INIT)		t_u1DMAID;
				VAR(uint8,								ADC_VAR_NO_INIT)		t_u1DMAHalfIntrpt;
				VAR(uint8,								ADC_VAR_NO_INIT)		t_u1DMAEndIntrpt;
	volatile	P2VAR(Adc_ValueGroupType,	AUTOMATIC,	ADC_VAR_NO_INIT)		t_pvdDMADstAdr;
	volatile 	P2VAR(uint16,				AUTOMATIC,	ADC_VAR_NO_INIT)		t_pu2DMASrcAdr;
				VAR(uint16,								ADC_VAR_NO_INIT)		t_u2DMAReloadNum;
	#endif

	ADC_ENTER_CRITICAL_SECTION(ADC_CODE);
	t_udCrntStatus			= Adc_GetGrpStatus(Group);
	t_udNextStatus			= t_udCrntStatus;
	t_udTrgMode				= Adc_GetTriggerSource(Group);
	t_udCnvMode				= Adc_GetGrpCnvMode(Group);
	if (t_udTrgMode==ADC_TRIGG_SRC_SW) {
		if ((t_udCrntStatus==ADC_IDLE) ||
		 ((t_udCnvMode==ADC_ONESHOT_MODE) && (t_udCrntStatus==ADC_STREAM_COMPLETED))) {
			t_udHWUnit		= Adc_GetHWUnitID(Group);
			t_udSG			= Adc_GetSGID(Group);
			t_u1IntrptUse	= Adc_GetIntrptUse(Group);
			#ifdef ADC_USE_DMA
			/* DMA setting	*/
			t_u1DMAOn	= Adc_IsDMAOn(Group);
			if (t_u1DMAOn==STD_ON) {
				/* DMA use	*/
				t_u1DMAID		= Adc_GetDMAID(Group);
				t_pu2DMASrcAdr	= Adc_Pil_GetDRAdr(t_udHWUnit,t_udSG);
				t_pvdDMADstAdr	= Adc_GetDataBuffer(Group);
				t_u2CnvChSize	= Adc_GetCnvChSize(Group);
				t_u2DMAReloadNum= (uint16)ADC_ZERO;
				Dma_SetTransModeTwoStepReload(
					t_u1DMAID,
					ADC_DMA_TRANSACTION_SIZE,
					ADC_DMA_MODE_SINGLE,
					t_pu2DMASrcAdr,
					t_pvdDMADstAdr,
					t_u2CnvChSize,
					t_u2DMAReloadNum
				);
				t_u1DMAHalfIntrpt	= Adc_IsDMAHalfIntrptOn(Group);
				t_u1DMAEndIntrpt	= t_u1IntrptUse;
				Dma_SetInterrupt(t_u1DMAID,t_u1DMAHalfIntrpt,t_u1DMAEndIntrpt);
				Dma_EnableTrans(t_u1DMAID );
			}
			#else
			t_u1DMAOn			= (uint8)STD_OFF;
			#endif
			t_u1StreamingAcces	= (uint8)STD_OFF;
			Adc_Pil_ClearDIR(t_udHWUnit,t_udSG);
			if (t_udCrntStatus==ADC_IDLE) {
				Adc_Pil_SetCnvEndIntrpt(t_udHWUnit,t_udSG,t_u1IntrptUse,t_u1DMAOn,t_u1StreamingAcces);
			}
			Adc_Pil_StartConversion(t_udHWUnit,t_udSG);
			t_udNextStatus 		= ADC_BUSY;
		} else {
			Adc_ReportRunTimeError(ADC_AID_START_GROUP_CONVERSION,ADC_E_BUSY);		/* SWS_Adc_00346/00426	*/
		}
		
	}
	/* update status 	*/
	Adc_SetGrpStatus( Group, t_udCrntStatus, t_udNextStatus );
	ADC_EXIT_CRITICAL_SECTION(ADC_CODE);
}
#endif

/************************************************************************************************/
/* Service name			: Adc_StopGroupConversion												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Stops the conversion of the requested ADC Channel group.				*/
/************************************************************************************************/
#if (ADC_CFG_START_STOP_GRP_API==STD_ON)
FUNC(void, ADC_CODE) Adc_StopGroupConversion(
	VAR(Adc_GroupType, ADC_VAR_INIT) Group
)
{
	VAR(Adc_StatusType,			ADC_VAR_NO_INIT)		t_udCrntStatus;
	VAR(Adc_StatusType, 		ADC_VAR_NO_INIT)		t_udNextStatus;
	VAR(Adc_TriggerSourceType,	ADC_VAR_NO_INIT)		t_udTrgMode;
	VAR(Adc_HWUnitType,			ADC_VAR_NO_INIT) 		t_udHWUnit;
	VAR(Adc_SGType,				ADC_VAR_NO_INIT) 		t_udSG;
	#ifdef ADC_USE_DMA
	VAR(uint8,					ADC_VAR_NO_INIT)		t_u1DMAOn;
	VAR(uint8,					ADC_VAR_NO_INIT)		t_u1DMAID;
	VAR(uint8,					ADC_VAR_NO_INIT)		t_u1DMAHalfIntrpt;
	VAR(uint8,					ADC_VAR_NO_INIT)		t_u1DMAEndIntrpt;
	#endif

	ADC_ENTER_CRITICAL_SECTION(ADC_CODE);
	t_udCrntStatus		= Adc_GetGrpStatus(Group);
	t_udNextStatus		= t_udCrntStatus;
	t_udTrgMode			= Adc_GetTriggerSource(Group);

	if ( ADC_TRIGG_SRC_SW == t_udTrgMode ) {
		if ( ADC_IDLE != t_udCrntStatus ) {
			#ifdef ADC_USE_DMA
			t_u1DMAOn	= Adc_IsDMAOn(Group);
			if (t_u1DMAOn==STD_ON) {
				/* DMA use	*/
				t_u1DMAID			= Adc_GetDMAID(Group);
				t_u1DMAHalfIntrpt	= (uint8)STD_OFF;
				t_u1DMAEndIntrpt	= (uint8)STD_OFF;
				Dma_DisableTrans(t_u1DMAID);
				Dma_SetInterrupt(t_u1DMAID,t_u1DMAHalfIntrpt,t_u1DMAEndIntrpt);
			}
			#endif
			/* interrupt disable			*/
			Adc_CnvEndIntrptDisable(Group);
			/* stop conversion 				*/
			t_udHWUnit	= Adc_GetHWUnitID(Group);
			t_udSG		= Adc_GetSGID(Group);
			Adc_Pil_StopGroupConversion(t_udHWUnit,t_udSG);
			t_udNextStatus = ADC_IDLE;											/* SWS_Adc_00360	*/
			#if (ADC_CFG_GRP_NOTIF_CAPABILITY==STD_ON)
			Adc_SetNotifyFlag(Group,FALSE);										/* SWS_Adc_00155	*/
			#endif
		} else {
			Adc_ReportRunTimeError(ADC_AID_STOP_GROUP_CONVERSION,ADC_E_IDLE);	/* SWS_Adc_00241	*/
		}
	}
	/* update status 	*/
	Adc_SetGrpStatus( Group, t_udCrntStatus, t_udNextStatus );
	ADC_EXIT_CRITICAL_SECTION(ADC_CODE);
}
#endif

/************************************************************************************************/
/* Service name			: Adc_ReadGroup															*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/*		DataBufferPtr	: sync: pointer to result data buffer									*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: Std_ReturnType														*/
/*		E_OK			: results are available and written to the data buffer					*/
/*		E_NOT_OK		: no results are available or development error occured					*/
/* Description			: Reads the group conversion result of the last completed conversion 	*/
/*						  round of the requested group and stores the channel values starting	*/
/*						  at the DataBufferPtr address. The group channel values are stored in 	*/
/*						  ascending channel number order ( in contrast to the storage layout of	*/
/*						  the result buffer if streaming access is configured).					*/
/************************************************************************************************/
#if (ADC_CFG_READ_GRP_API==STD_ON)
FUNC(Std_ReturnType, ADC_CODE) Adc_ReadGroup(
	VAR(Adc_GroupType, ADC_VAR_INIT)					Group,
	P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_VAR_INIT)	DataBufferPtr
)
{
	VAR(Adc_HWUnitType,			ADC_VAR_NO_INIT) 	t_udHWUnit;
	VAR(Adc_SGType,				ADC_VAR_NO_INIT)	t_udSG;
	VAR(Std_ReturnType,			ADC_VAR_NO_INIT)	t_udResult;
	VAR(Adc_StatusType,			ADC_VAR_NO_INIT)	t_udCrntStatus;
	VAR(Adc_StatusType,			ADC_VAR_NO_INIT)	t_udNextStatus;
	VAR(Adc_GroupConvModeType,	ADC_VAR_NO_INIT)	t_udCnvMode;
	VAR(Adc_TriggerSourceType,	ADC_VAR_NO_INIT)	t_udTrigger;
	VAR(uint16,					ADC_VAR_NO_INIT)	t_u2CnvChSize;

	ADC_ENTER_CRITICAL_SECTION(ADC_CODE);
	t_udResult		= E_NOT_OK;
	t_udCrntStatus	= Adc_GetGrpStatus(Group);
	t_udNextStatus	= t_udCrntStatus;
	t_udCnvMode		= Adc_GetGrpCnvMode(Group);
	t_udTrigger		= Adc_GetTriggerSource(Group);
	switch (t_udCrntStatus) {
		case ADC_IDLE:
			Adc_ReportRunTimeError(ADC_AID_READ_GROUP,ADC_E_IDLE);		/* SWS_Adc_00388	*/
			break;
		case ADC_BUSY:
			if (t_udCnvMode==ADC_CONTINUOUS_MODE) {
				t_udResult = E_OK;
			}
			break;
		case ADC_COMPLETED:		/* Not Supported (ASR streaming access is not supported)	*/
			t_udNextStatus = ADC_BUSY;			/* [SWS_Adc_00331]	*/
			break;
		case ADC_STREAM_COMPLETED:
			if (t_udTrigger==ADC_TRIGG_SRC_SW) {
				if (t_udCnvMode==ADC_ONESHOT_MODE) {
					Adc_CnvEndIntrptDisable(Group);
					t_udNextStatus = ADC_IDLE;	/* [SWS_Adc_00330] 	*/
				} else {
					/* ADC_CONTINUOUS_MODE	*/
					t_udNextStatus = ADC_BUSY;	/* [SWS_Adc_00329]	*/
				}
			} else {
				/* ADC_TRIGG_SRC_HW	*/
				t_udNextStatus = ADC_BUSY;		/* [SWS_Adc_00329]	*/
			}
			t_udResult = E_OK;
			break;
		default :		/* nothing	*/
			break;
	}

	/* update data 	*/
	if ( E_OK == t_udResult ) {
		t_udHWUnit		= Adc_GetHWUnitID(Group);
		t_udSG			= Adc_GetSGID(Group);
		t_u2CnvChSize	= Adc_GetCnvChSize(Group);
		Adc_Pil_GetCnvData( t_udHWUnit, t_udSG, t_u2CnvChSize, DataBufferPtr );
	}

	/* update status 	*/
	Adc_SetGrpStatus( Group, t_udCrntStatus, t_udNextStatus );

	ADC_EXIT_CRITICAL_SECTION(ADC_CODE);
	return(t_udResult);
}
#endif

/************************************************************************************************/
/* Service name			: Adc_EnableHardwareTrigger												*/
/* Sync/Async			: Asynchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Enables the hardware trigger for the requested ADC Channel group.		*/
/************************************************************************************************/
#if (ADC_CFG_HW_TRG_API==STD_ON)
FUNC(void, ADC_CODE) Adc_EnableHardwareTrigger(
	VAR(Adc_GroupType, ADC_VAR_INIT) Group
)
{
				VAR(Adc_HWUnitType,						ADC_VAR_NO_INIT) 	t_udHWUnit;
				VAR(Adc_SGType,							ADC_VAR_NO_INIT) 	t_udSG;
				VAR(boolean,							ADC_VAR_NO_INIT)	t_blisHWTriggerOn;
				VAR(uint8,								ADC_VAR_NO_INIT)	t_u1DMAOn;
				VAR(Adc_StatusType,						ADC_VAR_NO_INIT)	t_udCrntStatus;
				VAR(Adc_StatusType,						ADC_VAR_NO_INIT)	t_udNextStatus;
				VAR(uint8,								ADC_VAR_NO_INIT)	t_u1StreamingAcces;
				VAR(uint8,								ADC_VAR_NO_INIT)	t_u1IntrptUse;
				VAR(Adc_TriggerSourceType,				ADC_VAR_NO_INIT)	t_udTrgMode;

	#ifdef ADC_USE_TH
				VAR(Adc_TrackHoldGroupType,				ADC_VAR_NO_INIT)	t_udTHGrp;
	#endif
	#ifdef ADC_USE_DMA
	volatile	P2VAR(Adc_ValueGroupType,	AUTOMATIC,	ADC_VAR_NO_INIT)	t_pvdDMADstAdr;
				VAR(uint8,								ADC_VAR_NO_INIT)	t_u1DMAID;
	volatile	P2VAR(uint16,				AUTOMATIC,	ADC_VAR_NO_INIT)	t_pu2DMASrcAdr;
				VAR(uint16,								ADC_VAR_NO_INIT)	t_u2TransNum;
				VAR(uint16,								ADC_VAR_NO_INIT)	t_u2ReloadNum;
				VAR(uint16,								ADC_VAR_NO_INIT)	t_u2CnvChSize;
				VAR(uint8,								ADC_VAR_NO_INIT)	t_u1DMAMode;
				VAR(uint8,								ADC_VAR_NO_INIT)	t_u1DMAHalfIntrpt;
				VAR(uint8,								ADC_VAR_NO_INIT)	t_u1DMAEndIntrpt;
	#endif
	#ifdef ADC_USE_STREAMING_ACCESS
				VAR(Adc_StreamNumSampleType,			ADC_VAR_NO_INIT)	t_udStreamingNum;
				VAR(Adc_GroupAccessModeType,			ADC_VAR_NO_INIT)	t_udAccessMode;
	#endif

	ADC_ENTER_CRITICAL_SECTION(ADC_CODE);
	#ifdef ADC_USE_STREAMING_ACCESS
	t_udAccessMode		= Adc_GetGrpAccessMode(Group);
	#endif
	t_udCrntStatus	= Adc_GetGrpStatus(Group);
	t_udNextStatus	= t_udCrntStatus;
	t_udHWUnit		= Adc_GetHWUnitID(Group);
	t_udSG			= Adc_GetSGID(Group);
	t_udTrgMode		= Adc_GetTriggerSource(Group);
	if (t_udTrgMode==ADC_TRIGG_SRC_HW) {										/* [SWS_Adc_00120]	*/
		if (t_udCrntStatus==ADC_IDLE) {
			#ifdef ADC_USE_DMA
			/* DMA setting	*/
			t_u1DMAOn	= Adc_IsDMAOn(Group);
			if (t_u1DMAOn==STD_ON) {
				/* DMA use	*/
				t_u1DMAID			= Adc_GetDMAID(Group);
				t_pu2DMASrcAdr		= Adc_Pil_GetDRAdr(t_udHWUnit,t_udSG);
				t_pvdDMADstAdr		= Adc_GetDataBuffer(Group);
				t_u2CnvChSize		= Adc_GetCnvChSize(Group);
				t_u1DMAHalfIntrpt	= Adc_IsDMAHalfIntrptOn(Group);
				#ifdef ADC_USE_STREAMING_ACCESS
				if (t_udAccessMode==ADC_ACCESS_MODE_STREAMING) {
					t_u1DMAMode			= ADC_DMA_MODE_STREAMING;
					t_u1DMAEndIntrpt	= Adc_GetIntrptUse(Group);
					t_udStreamingNum	= Adc_GetCurrentStreamingNum(Group);
					t_u2TransNum		= (uint16)(t_u2CnvChSize*(uint16)t_udStreamingNum);
					t_u2ReloadNum		= t_u2CnvChSize;
					t_u1StreamingAcces	= (uint8)STD_ON;
					t_u1IntrptUse		= (uint8)STD_ON;
				} else {
				#endif
					/* single access	*/
					t_u1DMAMode			= ADC_DMA_MODE_SINGLE;
					t_u2TransNum		= t_u2CnvChSize;
					t_u2ReloadNum		= (uint16)ADC_ZERO;
					t_u1StreamingAcces	= (uint8)STD_OFF;
					t_u1IntrptUse		= Adc_GetIntrptUse(Group);
					t_u1DMAEndIntrpt	= t_u1IntrptUse;
				#ifdef ADC_USE_STREAMING_ACCESS
				}
				#endif

				Dma_SetTransModeTwoStepReload(
					(uint8)t_u1DMAID,
					ADC_DMA_TRANSACTION_SIZE,
					t_u1DMAMode,
					t_pu2DMASrcAdr,
					t_pvdDMADstAdr,
					t_u2TransNum,
					t_u2ReloadNum
				);
				Dma_SetInterrupt(t_u1DMAID,t_u1DMAHalfIntrpt,t_u1DMAEndIntrpt);
				Dma_EnableTrans(t_u1DMAID);
			} else {
			#else
				t_u1DMAOn			= (uint8)STD_OFF;
			#endif
				t_u1StreamingAcces	= (uint8)STD_OFF;
				t_u1IntrptUse		= Adc_GetIntrptUse(Group);
			#ifdef ADC_USE_DMA
			}
			#endif
			t_blisHWTriggerOn = TRUE;
			Adc_Pil_ClearDIR(t_udHWUnit,t_udSG);
			Adc_Pil_SetCnvEndIntrpt(t_udHWUnit,t_udSG,t_u1IntrptUse,t_u1DMAOn,t_u1StreamingAcces);
			#if	(ADC_CFG_GLOBAL_REG_CONTROL == STD_ON)
			Pic2_SetHardwareTrigger(Group,t_blisHWTriggerOn);
			#endif
			#ifdef ADC_USE_TH
			t_udTHGrp = Adc_GetTHGrp(Group);
			if (t_udTHGrp!=ADC_TH_GRP_NONE) {
				/* Track Hold on	*/
				Adc_Pil_StartTrackHold(t_udHWUnit,t_udTHGrp);
			}
			#endif
			Adc_Pil_SetHardwareTrigger(t_udHWUnit,t_udSG,t_blisHWTriggerOn);
			t_udNextStatus = ADC_BUSY;
		} else {
			Adc_ReportRunTimeError(ADC_AID_ENABLE_HARDWARE_TRG,ADC_E_BUSY);		/* SWS_Adc_00349	*/
		}
	} else {
		Adc_ReportRunTimeError(ADC_AID_ENABLE_HARDWARE_TRG,ADC_E_BUSY);			/* SWS_Adc_00321	*/
	}
	/* update status 	*/
	Adc_SetGrpStatus( Group, t_udCrntStatus, t_udNextStatus );
	ADC_EXIT_CRITICAL_SECTION(ADC_CODE);
}
#endif

/************************************************************************************************/
/* Service name			: Adc_DisableHardwareTrigger											*/
/* Sync/Async			: Asynchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Disables the hardware trigger for the requested ADC Channel group.	*/
/************************************************************************************************/
#if (ADC_CFG_HW_TRG_API==STD_ON)
FUNC(void, ADC_CODE) Adc_DisableHardwareTrigger(
	VAR(Adc_GroupType, ADC_VAR_INIT) Group
)
{
	VAR(Adc_HWUnitType,			ADC_VAR_NO_INIT) 	t_udHWUnit;
	VAR(Adc_SGType,				ADC_VAR_NO_INIT) 	t_udSG;
	VAR(boolean,				ADC_VAR_NO_INIT)	t_blisHWTriggerOn;
	VAR(Adc_StatusType,			ADC_VAR_NO_INIT)	t_udCrntStatus;
	VAR(Adc_StatusType,			ADC_VAR_NO_INIT)	t_udNextStatus;
	VAR(Adc_TriggerSourceType,	ADC_VAR_NO_INIT)	t_udTrgMode;
	#ifdef ADC_USE_TH
	VAR(Adc_TrackHoldGroupType,	ADC_VAR_NO_INIT)	t_udTHGrp;
	#endif
	#ifdef ADC_USE_DMA
	VAR(uint8,					ADC_VAR_NO_INIT)	t_u1DMAOn;
	VAR(uint8,					ADC_VAR_NO_INIT)	t_u1DMAID;
	VAR(uint8,					ADC_VAR_NO_INIT)	t_u1DMAHalfIntrpt;
	VAR(uint8,					ADC_VAR_NO_INIT)	t_u1DMAEndIntrpt;
	#endif

	ADC_ENTER_CRITICAL_SECTION(ADC_CODE);
	t_udCrntStatus	= Adc_GetGrpStatus(Group);
	t_udNextStatus	= t_udCrntStatus;
	t_udTrgMode		= Adc_GetTriggerSource(Group);
	if (t_udTrgMode==ADC_TRIGG_SRC_HW ) {			/* [SWS_Adc_00121]	*/
		if ( ADC_IDLE != t_udCrntStatus ) {				
			#ifdef ADC_USE_DMA
			t_u1DMAOn	= Adc_IsDMAOn(Group);
			if (t_u1DMAOn==STD_ON) {
				/* DMA use	*/
				t_u1DMAID			= Adc_GetDMAID(Group);
				t_u1DMAHalfIntrpt	= (uint8)STD_OFF;
				t_u1DMAEndIntrpt	= (uint8)STD_OFF;
				Dma_DisableTrans(t_u1DMAID);
				Dma_SetInterrupt(t_u1DMAID,t_u1DMAHalfIntrpt,t_u1DMAEndIntrpt);
			}
			#endif
			/* interrupt disable			*/
			Adc_CnvEndIntrptDisable(Group);
			/* stop conversion 				*/
			t_blisHWTriggerOn	= FALSE;
			t_udHWUnit			= Adc_GetHWUnitID(Group);
			t_udSG				= Adc_GetSGID(Group);
			#if	(ADC_CFG_GLOBAL_REG_CONTROL == STD_ON)
			Pic2_SetHardwareTrigger(Group,t_blisHWTriggerOn);
			#endif
			Adc_Pil_SetHardwareTrigger(t_udHWUnit,t_udSG,t_blisHWTriggerOn);
			#ifdef ADC_USE_TH
			t_udTHGrp = Adc_GetTHGrp(Group);
			if (t_udTHGrp!=ADC_TH_GRP_NONE) {
				/* Track Hold on	*/
				Adc_Pil_StopTrackHold(t_udHWUnit,t_udTHGrp);
			} 
			#endif
			Adc_Pil_StopGroupConversion(t_udHWUnit,t_udSG);
			t_udNextStatus	= ADC_IDLE;					/* [SWS_Adc_00361]	*/
		} else {
			Adc_ReportRunTimeError(ADC_AID_DISABLE_HARDWARE_TRG,ADC_E_IDLE);	/* SWS_Adc_00304	*/
		}
	}

	/* update status 	*/
	Adc_SetGrpStatus( Group, t_udCrntStatus, t_udNextStatus );
	ADC_EXIT_CRITICAL_SECTION(ADC_CODE);
}
#endif

/************************************************************************************************/
/* Service name			: Adc_EnableGroupNotification											*/
/* Sync/Async			: Asynchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Enable the Conversion End Notifcation									*/
/************************************************************************************************/
#if (ADC_CFG_GRP_NOTIF_CAPABILITY==STD_ON)
FUNC(void, ADC_CODE) Adc_EnableGroupNotification(
	VAR(Adc_GroupType, ADC_VAR_INIT) Group
)
{
	ADC_ENTER_CRITICAL_SECTION(ADC_CODE);
	Adc_SetNotifyFlag( Group, TRUE );	
	ADC_EXIT_CRITICAL_SECTION(ADC_CODE);
}
#endif

/************************************************************************************************/
/* Service name			: Adc_DisableGroupNotification											*/
/* Sync/Async			: Asynchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Disable the Conversion End Notifcation								*/
/************************************************************************************************/
#if (ADC_CFG_GRP_NOTIF_CAPABILITY==STD_ON)
FUNC(void, ADC_CODE) Adc_DisableGroupNotification(
	VAR(Adc_GroupType, ADC_VAR_INIT) Group
)
{
	ADC_ENTER_CRITICAL_SECTION(ADC_CODE);
	Adc_SetNotifyFlag( Group, FALSE );	
	ADC_EXIT_CRITICAL_SECTION(ADC_CODE);
}
#endif

/************************************************************************************************/
/* Service name			: Adc_GetGroupStatus													*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: Adc_StatusType : Conversion status for the requested group.			*/
/* Description			: Returns the conversion status of the requested ADC Channel group.		*/
/************************************************************************************************/
FUNC(Adc_StatusType, ADC_CODE) Adc_GetGroupStatus(
	VAR(Adc_GroupType, ADC_VAR_INIT) Group
)
{
	VAR(Adc_HWUnitType,				ADC_VAR_NO_INIT) 	t_udHWUnit;
	VAR(Adc_SGType,					ADC_VAR_NO_INIT) 	t_udSG;
	VAR(Adc_StatusType, 			ADC_VAR_NO_INIT)	t_udCrntStatus;
	VAR(Adc_StatusType, 			ADC_VAR_NO_INIT)	t_udNextStatus;
	VAR(boolean,					ADC_VAR_NO_INIT)	t_blisComplete;

	/* This API can be called only when ADC_CFG_GRP#x_USE_CNV_INT is STD_OFF and						*/
	/* ADC_CFG_GRP#x_ACCESS_MODE is ADC_ACCESS_MODE_SINGLE.												*/
	/* The implementation does not consider that this API will be called under any other conditions.	*/

	ADC_ENTER_CRITICAL_SECTION(ADC_CODE);
	/* get crnt info	*/
	t_udCrntStatus		= Adc_GetGrpStatus(Group);
	t_udNextStatus		= t_udCrntStatus;

	/* state transition */
	if (t_udCrntStatus==ADC_BUSY) {
		t_udHWUnit			= Adc_GetHWUnitID(Group);
		t_udSG				= Adc_GetSGID(Group);
		t_blisComplete	= Adc_Pil_IsCnvCompleted(t_udHWUnit,t_udSG);
		if (t_blisComplete==(boolean)TRUE) {
			t_udNextStatus = ADC_STREAM_COMPLETED;
		}
	}
	/* update status 	*/
	Adc_SetGrpStatus( Group, t_udCrntStatus, t_udNextStatus );

	ADC_EXIT_CRITICAL_SECTION(ADC_CODE);
	return(t_udNextStatus);
}

#ifdef ADC_USE_STREAMING_ACCESS
/************************************************************************************************/
/* Service name			: Adc_SetStreamingNum													*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: 																		*/
/*		Group					: Numeric ID of requested ADC channel group.					*/
/*		Adc_StreamNumSampleType	: Number of group conversions in streaming access mode.			*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Change the number of conversions in  streaming access mode.			*/
/************************************************************************************************/
FUNC(void, ADC_CODE) Adc_SetStreamingNum(
	VAR(Adc_GroupType,				ADC_VAR_INIT) Group,
	VAR(Adc_StreamNumSampleType,	ADC_VAR_INIT) StreamingNum
)
{
	ADC_ENTER_CRITICAL_SECTION(ADC_CODE);
	s_stAdcGrpInfo[Group].udStreamingNum = StreamingNum;
	ADC_EXIT_CRITICAL_SECTION(ADC_CODE);
}
#endif

#define ADC_STOP_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

/*----------------------------------------------------------------------------------------------*/
/* function from ISR																			*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Service name			: Adc_ISR/DMA_HWUnitn_SGx												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: function from each ISR (Interrupt Service Routines)					*/
/************************************************************************************************/
#define ADC_START_SEC_CODE_FAST_GLOBAL
#include "Adc_MemMap.h"

/* ISR(ADC) */
#ifdef ADC_USE_ISR_ADC_HWUNIT0_SG0
FUNC(void, ADC_CODE) Adc_ISR_HWUnit0_SG0(void) {Adc_Intrpt_HWUnit0_SG0();}	/* ISR(ADC) HWUnit0 SG0	*/
#endif
#ifdef ADC_USE_ISR_ADC_HWUNIT0_SG1
FUNC(void, ADC_CODE) Adc_ISR_HWUnit0_SG1(void) {Adc_Intrpt_HWUnit0_SG1();}	/* ISR(ADC) HWUnit0 SG1	*/
#endif
#ifdef ADC_USE_ISR_ADC_HWUNIT0_SG2
FUNC(void, ADC_CODE) Adc_ISR_HWUnit0_SG2(void) {Adc_Intrpt_HWUnit0_SG2();}	/* ISR(ADC) HWUnit0 SG2	*/
#endif
#ifdef ADC_USE_ISR_ADC_HWUNIT0_SG3
FUNC(void, ADC_CODE) Adc_ISR_HWUnit0_SG3(void) {Adc_Intrpt_HWUnit0_SG3();}	/* ISR(ADC) HWUnit0 SG3	*/
#endif
#ifdef ADC_USE_ISR_ADC_HWUNIT0_SG4
FUNC(void, ADC_CODE) Adc_ISR_HWUnit0_SG4(void) {Adc_Intrpt_HWUnit0_SG4();}	/* ISR(ADC) HWUnit0 SG4	*/
#endif
#ifdef ADC_USE_ISR_ADC_HWUNIT1_SG0
FUNC(void, ADC_CODE) Adc_ISR_HWUnit1_SG0(void) {Adc_Intrpt_HWUnit1_SG0();}	/* ISR(ADC) HWUnit1 SG0	*/
#endif
#ifdef ADC_USE_ISR_ADC_HWUNIT1_SG1
FUNC(void, ADC_CODE) Adc_ISR_HWUnit1_SG1(void) {Adc_Intrpt_HWUnit1_SG1();}	/* ISR(ADC) HWUnit1 SG1	*/
#endif
#ifdef ADC_USE_ISR_ADC_HWUNIT1_SG2
FUNC(void, ADC_CODE) Adc_ISR_HWUnit1_SG2(void) {Adc_Intrpt_HWUnit1_SG2();}	/* ISR(ADC) HWUnit1 SG2	*/
#endif
#ifdef ADC_USE_ISR_ADC_HWUNIT1_SG3
FUNC(void, ADC_CODE) Adc_ISR_HWUnit1_SG3(void) {Adc_Intrpt_HWUnit1_SG3();}	/* ISR(ADC) HWUnit1 SG3	*/
#endif
#ifdef ADC_USE_ISR_ADC_HWUNIT1_SG4
FUNC(void, ADC_CODE) Adc_ISR_HWUnit1_SG4(void) {Adc_Intrpt_HWUnit1_SG4();}	/* ISR(ADC) HWUnit1 SG4	*/
#endif
#ifdef ADC_USE_ISR_ADC_HWUNIT2_SG0
FUNC(void, ADC_CODE) Adc_ISR_HWUnit2_SG0(void) {Adc_Intrpt_HWUnit2_SG0();}	/* ISR(ADC) HWUnit2 SG0	*/
#endif
#ifdef ADC_USE_ISR_ADC_HWUNIT2_SG1
FUNC(void, ADC_CODE) Adc_ISR_HWUnit2_SG1(void) {Adc_Intrpt_HWUnit2_SG1();}	/* ISR(ADC) HWUnit2 SG1	*/
#endif
#ifdef ADC_USE_ISR_ADC_HWUNIT2_SG2
FUNC(void, ADC_CODE) Adc_ISR_HWUnit2_SG2(void) {Adc_Intrpt_HWUnit2_SG2();}	/* ISR(ADC) HWUnit2 SG2	*/
#endif
#ifdef ADC_USE_ISR_ADC_HWUNIT2_SG3
FUNC(void, ADC_CODE) Adc_ISR_HWUnit2_SG3(void) {Adc_Intrpt_HWUnit2_SG3();}	/* ISR(ADC) HWUnit2 SG3	*/
#endif
#ifdef ADC_USE_ISR_ADC_HWUNIT2_SG4
FUNC(void, ADC_CODE) Adc_ISR_HWUnit2_SG4(void) {Adc_Intrpt_HWUnit2_SG4();}	/* ISR(ADC) HWUnit2 SG4	*/
#endif

/* ISR(DMA) */
#ifdef ADC_USE_ISR_DMA_HWUNIT0_SG0
FUNC(void, ADC_CODE) Adc_DMA_HWUnit0_SG0(void) {Adc_Intrpt_HWUnit0_SG0();}	/* ISR(DMA) HWUnit0 SG0	*/
#endif
#ifdef ADC_USE_ISR_DMA_HWUNIT0_SG1
FUNC(void, ADC_CODE) Adc_DMA_HWUnit0_SG1(void) {Adc_Intrpt_HWUnit0_SG1();}	/* ISR(DMA) HWUnit0 SG1	*/
#endif
#ifdef ADC_USE_ISR_DMA_HWUNIT0_SG2
FUNC(void, ADC_CODE) Adc_DMA_HWUnit0_SG2(void) {Adc_Intrpt_HWUnit0_SG2();}	/* ISR(DMA) HWUnit0 SG2	*/
#endif
#ifdef ADC_USE_ISR_DMA_HWUNIT0_SG3
FUNC(void, ADC_CODE) Adc_DMA_HWUnit0_SG3(void) {Adc_Intrpt_HWUnit0_SG3();}	/* ISR(DMA) HWUnit0 SG3	*/
#endif
#ifdef ADC_USE_ISR_DMA_HWUNIT0_SG4
FUNC(void, ADC_CODE) Adc_DMA_HWUnit0_SG4(void) {Adc_Intrpt_HWUnit0_SG4();}	/* ISR(DMA) HWUnit0 SG4	*/
#endif
#ifdef ADC_USE_ISR_DMA_HWUNIT1_SG0
FUNC(void, ADC_CODE) Adc_DMA_HWUnit1_SG0(void) {Adc_Intrpt_HWUnit1_SG0();}	/* ISR(DMA) HWUnit1 SG0	*/
#endif
#ifdef ADC_USE_ISR_DMA_HWUNIT1_SG1
FUNC(void, ADC_CODE) Adc_DMA_HWUnit1_SG1(void) {Adc_Intrpt_HWUnit1_SG1();}	/* ISR(DMA) HWUnit1 SG1	*/
#endif
#ifdef ADC_USE_ISR_DMA_HWUNIT1_SG2
FUNC(void, ADC_CODE) Adc_DMA_HWUnit1_SG2(void) {Adc_Intrpt_HWUnit1_SG2();}	/* ISR(DMA) HWUnit1 SG2	*/
#endif
#ifdef ADC_USE_ISR_DMA_HWUNIT1_SG3
FUNC(void, ADC_CODE) Adc_DMA_HWUnit1_SG3(void) {Adc_Intrpt_HWUnit1_SG3();}	/* ISR(DMA) HWUnit1 SG3	*/
#endif
#ifdef ADC_USE_ISR_DMA_HWUNIT1_SG4
FUNC(void, ADC_CODE) Adc_DMA_HWUnit1_SG4(void) {Adc_Intrpt_HWUnit1_SG4();}	/* ISR(DMA) HWUnit1 SG4	*/
#endif
#ifdef ADC_USE_ISR_DMA_HWUNIT2_SG0
FUNC(void, ADC_CODE) Adc_DMA_HWUnit2_SG0(void) {Adc_Intrpt_HWUnit2_SG0();}	/* ISR(DMA) HWUnit2 SG0	*/
#endif
#ifdef ADC_USE_ISR_DMA_HWUNIT2_SG1
FUNC(void, ADC_CODE) Adc_DMA_HWUnit2_SG1(void) {Adc_Intrpt_HWUnit2_SG1();}	/* ISR(DMA) HWUnit2 SG1	*/
#endif
#ifdef ADC_USE_ISR_DMA_HWUNIT2_SG2
FUNC(void, ADC_CODE) Adc_DMA_HWUnit2_SG2(void) {Adc_Intrpt_HWUnit2_SG2();}	/* ISR(DMA) HWUnit2 SG2	*/
#endif
#ifdef ADC_USE_ISR_DMA_HWUNIT2_SG3
FUNC(void, ADC_CODE) Adc_DMA_HWUnit2_SG3(void) {Adc_Intrpt_HWUnit2_SG3();}	/* ISR(DMA) HWUnit2 SG3	*/
#endif
#ifdef ADC_USE_ISR_DMA_HWUNIT2_SG4
FUNC(void, ADC_CODE) Adc_DMA_HWUnit2_SG4(void) {Adc_Intrpt_HWUnit2_SG4();}	/* ISR(DMA) HWUnit2 SG4	*/
#endif

#define ADC_STOP_SEC_CODE_FAST_GLOBAL
#include "Adc_MemMap.h"

/*--------------------------------------------------------------------------*/
/* only when register check is available  									*/
/*--------------------------------------------------------------------------*/
#define ADC_START_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"
#if (ADC_CFG_REG_CHK==STD_ON)
/************************************************************************************************/
/* Service name			: Adc_Regchk_All														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: uint32																*/
/* 		ADC_REGCHK_OK					: No Error detected										*/
/* 		ADC_REGCHK_NG					: Error detected										*/
/*		(following is available when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check all registers and refresh ones with expected value.				*/
/************************************************************************************************/
FUNC(uint32, ADC_CODE) Adc_Regchk_All(void)
{
	VAR(uint32,	ADC_VAR_NO_INIT)	t_u4ChkResult;

	t_u4ChkResult  = Adc_Pil_Regchk_All();
	#if	(ADC_CFG_GLOBAL_REG_CONTROL == STD_ON)
	t_u4ChkResult |= Pic2_Regchk_All();
	#endif
	return (t_u4ChkResult);
}

/************************************************************************************************/
/* Service name			: Adc_Regchk_Grp														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: uint32																*/
/* 		ADC_REGCHK_OK					: No Error detected										*/
/* 		ADC_REGCHK_NG					: Error detected										*/
/*		(following is available when ADC_CFG_REG_REFRESH is STD_ON)								*/
/* 		ADC_REGCHK_REFRESH_SUCCESS		: Error detected but refresh is success					*/
/* 		ADC_REGCHK_REFRESH_IMPOSSIBLE	: Error detected for unrefreshable register	 			*/
/* 		ADC_REGCHK_REFRESH_FAILED		: Error detected and refresh failed			 			*/
/* Description			: Check Group related registers and refresh ones with expected value.	*/
/************************************************************************************************/
FUNC(uint32, ADC_CODE) Adc_Regchk_Grp(
	VAR(Adc_GroupType,	ADC_VAR_INIT) Group
)
{
	VAR(uint32,	ADC_VAR_NO_INIT)	t_u4ChkResult;

	t_u4ChkResult  = Adc_Pil_Regchk_Grp(Group);
	#if	(ADC_CFG_GLOBAL_REG_CONTROL == STD_ON)
	t_u4ChkResult |= Pic2_Regchk_Grp(Group);
	#endif
	return (t_u4ChkResult);
}
#endif

/*----------------------------------------------------------------------------------------------*/
/* Private API 																					*/
/*----------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* always available															*/
/*--------------------------------------------------------------------------*/

/************************************************************************************************/
/* Service name			: Adc_DataInit															*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Initializes the ADC internal data										*/
/************************************************************************************************/
static FUNC(void, ADC_CODE) Adc_DataInit(void)
{
	VAR(Adc_GroupType,	ADC_VAR_NO_INIT) 	t_udGrp;

	for (t_udGrp=ADC_GRP00;	t_udGrp<(Adc_GroupType)ADC_CFG_GRP_SIZE;t_udGrp++) {
		s_stAdcGrpInfo[t_udGrp].udStatus				= ADC_IDLE;
		#if (ADC_CFG_GRP_NOTIF_CAPABILITY==STD_ON)
		s_stAdcGrpInfo[t_udGrp].blisNotifyOn			= FALSE;
		#endif	
		#ifdef ADC_USE_DMA
		s_stAdcGrpInfo[t_udGrp].pudDataBuffer			= (Adc_ValueGroupType*)NULL_PTR;
		#endif
		#ifdef ADC_USE_STREAMING_ACCESS
		s_stAdcGrpInfo[t_udGrp].udStreamingNum			= Adc_GetStreamingNum(t_udGrp);
		#endif
	}
}

/************************************************************************************************/
/* Service name			: Adc_SetGrpStatus														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/*		Adc_StatusType	: current Group conversion status										*/
/*		Adc_StatusType	: next Group conversion status											*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: set the group conversion status										*/
/************************************************************************************************/
static FUNC(void, ADC_CODE) Adc_SetGrpStatus(
	CONST(Adc_GroupType,  ADC_CONST) t_cudGrp,
	CONST(Adc_StatusType, ADC_CONST) t_cudCrntStatus,
	CONST(Adc_StatusType, ADC_CONST) t_cudNextStatus
)
{
	if (t_cudCrntStatus!=t_cudNextStatus) {
		s_stAdcGrpInfo[t_cudGrp].udStatus = t_cudNextStatus;
	}
}

/************************************************************************************************/
/* Service name			: Adc_CnvEndIntrptDisable												*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Set Group Conversion End interrupt(ADIE) to Disable					*/
/************************************************************************************************/
#if ((ADC_CFG_START_STOP_GRP_API==STD_ON)||(ADC_CFG_READ_GRP_API==STD_ON)||(ADC_CFG_HW_TRG_API==STD_ON))
static FUNC(void, ADC_CODE) Adc_CnvEndIntrptDisable(
	CONST(Adc_GroupType, ADC_CONST) t_cudGrp
)
{
	VAR(Adc_HWUnitType,			ADC_VAR_NO_INIT) 	t_udHWUnit;
	VAR(Adc_SGType,				ADC_VAR_NO_INIT) 	t_udSG;
	VAR(uint8,					ADC_VAR_NO_INIT)	t_u1DMAOn;
	VAR(uint8,					ADC_VAR_NO_INIT)	t_u1IntrptUse;
	VAR(uint8,					ADC_VAR_NO_INIT)	t_u1StreamingAcces;

	t_udHWUnit			= Adc_GetHWUnitID(t_cudGrp);
	t_udSG				= Adc_GetSGID(t_cudGrp);
	t_u1DMAOn			= (uint8)STD_OFF;
	t_u1IntrptUse		= (uint8)STD_OFF;
	t_u1StreamingAcces	= (uint8)STD_OFF;
	Adc_Pil_SetCnvEndIntrpt(t_udHWUnit,t_udSG,t_u1IntrptUse,t_u1DMAOn,t_u1StreamingAcces);
}
#endif

/*--------------------------------------------------------------------------*/
/* only when Notify is available											*/
/*--------------------------------------------------------------------------*/
#if (ADC_CFG_GRP_NOTIF_CAPABILITY==STD_ON)
/************************************************************************************************/
/* Service name			: Adc_SetNotifyFlag														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/*		Notify			: TRUE:Notify on, FALSE:Notify off 										*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: set the Notify flag													*/
/************************************************************************************************/
static FUNC(void, ADC_CODE) Adc_SetNotifyFlag(
	CONST(Adc_GroupType, ADC_CONST)	t_cudGrp,
	CONST(boolean, ADC_CONST)		t_cblisNotifyOn
)
{
	s_stAdcGrpInfo[t_cudGrp].blisNotifyOn = t_cblisNotifyOn;
}

/************************************************************************************************/
/* Service name			: Adc_GetNotifyFlag														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: TRUE:Notif on , FALSE:Notify off										*/
/* Description			: get the Notify flag													*/
/************************************************************************************************/
static FUNC(boolean, ADC_CODE) Adc_GetNotifyFlag(
	CONST(Adc_GroupType, ADC_CONST)	t_cudGrp
)
{
	return(s_stAdcGrpInfo[t_cudGrp].blisNotifyOn);
}

/************************************************************************************************/
/* Service name			: Adc_CnvEndNotify														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: conversion end nofitication call										*/
/************************************************************************************************/
static FUNC(void, ADC_CODE) Adc_CnvEndNotify(
	CONST(Adc_GroupType, ADC_CONST) t_cudGrp
)
{
	VAR(boolean,  ADC_VAR_NO_INIT)		t_blisNotifyOn;
	void								(*t_pvdNotifyFunc)(void);

	t_blisNotifyOn = Adc_GetNotifyFlag(t_cudGrp);
	if (t_blisNotifyOn==TRUE) {
		t_pvdNotifyFunc = Adc_NotifyFunc(t_cudGrp);
		if (NULL_PTR!=t_pvdNotifyFunc) {
			(*t_pvdNotifyFunc)();
		}
	}
}
#endif

#define ADC_STOP_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

/*--------------------------------------------------------------------------*/
/* only when Interrupt is available											*/
/*--------------------------------------------------------------------------*/
#ifdef ADC_USE_CNV_INT

#define ADC_START_SEC_CODE_FAST_GLOBAL
#include "Adc_MemMap.h"
/************************************************************************************************/
/* Service name			: Adc_ISR_CnvEnd														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: function from each ISR (Interrupt Service Routines)					*/
/************************************************************************************************/
static  FUNC(void, ADC_CODE) Adc_ISR_CnvEnd(
	CONST(Adc_GroupType,	ADC_CONST) t_cudGrp
)
{
	VAR(Adc_StatusType, 			ADC_VAR_NO_INIT)	t_udCrntStatus;
	VAR(Adc_StatusType, 			ADC_VAR_NO_INIT)	t_udNextStatus;
	VAR(uint8,						ADC_VAR_NO_INIT)	t_u1IntrptUse;
	VAR(Adc_TriggerSourceType,		ADC_VAR_NO_INIT)	t_udTrgMode;
	#if (defined(ADC_USE_STREAMING_ACCESS) && defined(ADC_USE_DMA))
	VAR(Adc_GroupAccessModeType,	ADC_VAR_NO_INIT)	t_udAccessMode;
	VAR(uint8,						ADC_VAR_NO_INIT)	t_u1DMAOn;
	#endif

	t_u1IntrptUse = Adc_GetIntrptUse(t_cudGrp);
	#if (defined(ADC_USE_STREAMING_ACCESS) && defined(ADC_USE_DMA))
	if (t_u1IntrptUse==STD_OFF) {
		t_udAccessMode	= Adc_GetGrpAccessMode(t_cudGrp);
		if (t_udAccessMode==ADC_ACCESS_MODE_STREAMING) {
			t_u1IntrptUse		= (uint8)STD_ON;
		} else {
			/* single access	*/
			t_u1DMAOn	= Adc_IsDMAOn(t_cudGrp);
			if (t_u1DMAOn==STD_ON) {
				t_u1IntrptUse	= (uint8)STD_ON;
			}
		}
	}
	#endif


	if (t_u1IntrptUse==STD_ON) {
		t_udCrntStatus	= Adc_GetGrpStatus(t_cudGrp);
		t_udTrgMode		= Adc_GetTriggerSource(t_cudGrp);
		if ((t_udCrntStatus==ADC_BUSY)
		 || ((t_udCrntStatus==ADC_STREAM_COMPLETED)&&(t_udTrgMode==ADC_TRIGG_SRC_HW))) {
			t_udNextStatus	= ADC_STREAM_COMPLETED;
			/* update status 	*/
			Adc_SetGrpStatus( t_cudGrp, t_udCrntStatus, t_udNextStatus );
			#if (ADC_CFG_GRP_NOTIF_CAPABILITY==STD_ON)
			/* Notification	*/
			Adc_CnvEndNotify(t_cudGrp);
			#endif
		}
	}
}

#if (defined(ADC_USE_ISR_ADC_HWUNIT0_SG0) || defined(ADC_USE_ISR_DMA_HWUNIT0_SG0))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit0_SG0(void)
{
 	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)		t_udGrp;
	#if		((ADC_CFG_GRP_SIZE>= 1U) && (ADC_CFG_GRP00_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP00_SG==ADC_SG0))
	t_udGrp = ADC_GRP00;
	#elif	((ADC_CFG_GRP_SIZE>= 2U) && (ADC_CFG_GRP01_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP01_SG==ADC_SG0))
	t_udGrp = ADC_GRP01;
	#elif	((ADC_CFG_GRP_SIZE>= 3U) && (ADC_CFG_GRP02_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP02_SG==ADC_SG0))
	t_udGrp = ADC_GRP02;
	#elif	((ADC_CFG_GRP_SIZE>= 4U) && (ADC_CFG_GRP03_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP03_SG==ADC_SG0))
	t_udGrp = ADC_GRP03;
	#elif	((ADC_CFG_GRP_SIZE>= 5U) && (ADC_CFG_GRP04_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP04_SG==ADC_SG0))
	t_udGrp = ADC_GRP04;
	#elif	((ADC_CFG_GRP_SIZE>= 6U) && (ADC_CFG_GRP05_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP05_SG==ADC_SG0))
	t_udGrp = ADC_GRP05;
	#elif	((ADC_CFG_GRP_SIZE>= 7U) && (ADC_CFG_GRP06_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP06_SG==ADC_SG0))
	t_udGrp = ADC_GRP06;
	#elif	((ADC_CFG_GRP_SIZE>= 8U) && (ADC_CFG_GRP07_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP07_SG==ADC_SG0))
	t_udGrp = ADC_GRP07;
	#elif	((ADC_CFG_GRP_SIZE>= 9U) && (ADC_CFG_GRP08_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP08_SG==ADC_SG0))
	t_udGrp = ADC_GRP08;
	#elif	((ADC_CFG_GRP_SIZE>=10U) && (ADC_CFG_GRP09_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP09_SG==ADC_SG0))
	t_udGrp = ADC_GRP09;
	#elif	((ADC_CFG_GRP_SIZE>=11U) && (ADC_CFG_GRP10_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP10_SG==ADC_SG0))
	t_udGrp = ADC_GRP10;
	#elif	((ADC_CFG_GRP_SIZE>=12U) && (ADC_CFG_GRP11_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP11_SG==ADC_SG0))
	t_udGrp = ADC_GRP11;
	#elif	((ADC_CFG_GRP_SIZE>=13U) && (ADC_CFG_GRP12_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP12_SG==ADC_SG0))
	t_udGrp = ADC_GRP12;
	#elif	((ADC_CFG_GRP_SIZE>=14U) && (ADC_CFG_GRP13_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP13_SG==ADC_SG0))
	t_udGrp = ADC_GRP13;
	#elif	((ADC_CFG_GRP_SIZE>=15U) && (ADC_CFG_GRP14_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP14_SG==ADC_SG0))
	t_udGrp = ADC_GRP14;
	#endif
	Adc_ISR_CnvEnd(t_udGrp);
}
#endif

#if (defined(ADC_USE_ISR_ADC_HWUNIT0_SG1) || defined(ADC_USE_ISR_DMA_HWUNIT0_SG1))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit0_SG1(void)
{
 	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)		t_udGrp;
	#if		((ADC_CFG_GRP_SIZE>= 1U) && (ADC_CFG_GRP00_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP00_SG==ADC_SG1))
	t_udGrp = ADC_GRP00;
	#elif	((ADC_CFG_GRP_SIZE>= 2U) && (ADC_CFG_GRP01_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP01_SG==ADC_SG1))
	t_udGrp = ADC_GRP01;
	#elif	((ADC_CFG_GRP_SIZE>= 3U) && (ADC_CFG_GRP02_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP02_SG==ADC_SG1))
	t_udGrp = ADC_GRP02;
	#elif	((ADC_CFG_GRP_SIZE>= 4U) && (ADC_CFG_GRP03_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP03_SG==ADC_SG1))
	t_udGrp = ADC_GRP03;
	#elif	((ADC_CFG_GRP_SIZE>= 5U) && (ADC_CFG_GRP04_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP04_SG==ADC_SG1))
	t_udGrp = ADC_GRP04;
	#elif	((ADC_CFG_GRP_SIZE>= 6U) && (ADC_CFG_GRP05_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP05_SG==ADC_SG1))
	t_udGrp = ADC_GRP05;
	#elif	((ADC_CFG_GRP_SIZE>= 7U) && (ADC_CFG_GRP06_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP06_SG==ADC_SG1))
	t_udGrp = ADC_GRP06;
	#elif	((ADC_CFG_GRP_SIZE>= 8U) && (ADC_CFG_GRP07_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP07_SG==ADC_SG1))
	t_udGrp = ADC_GRP07;
	#elif	((ADC_CFG_GRP_SIZE>= 9U) && (ADC_CFG_GRP08_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP08_SG==ADC_SG1))
	t_udGrp = ADC_GRP08;
	#elif	((ADC_CFG_GRP_SIZE>=10U) && (ADC_CFG_GRP09_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP09_SG==ADC_SG1))
	t_udGrp = ADC_GRP09;
	#elif	((ADC_CFG_GRP_SIZE>=11U) && (ADC_CFG_GRP10_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP10_SG==ADC_SG1))
	t_udGrp = ADC_GRP10;
	#elif	((ADC_CFG_GRP_SIZE>=12U) && (ADC_CFG_GRP11_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP11_SG==ADC_SG1))
	t_udGrp = ADC_GRP11;
	#elif	((ADC_CFG_GRP_SIZE>=13U) && (ADC_CFG_GRP12_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP12_SG==ADC_SG1))
	t_udGrp = ADC_GRP12;
	#elif	((ADC_CFG_GRP_SIZE>=14U) && (ADC_CFG_GRP13_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP13_SG==ADC_SG1))
	t_udGrp = ADC_GRP13;
	#elif	((ADC_CFG_GRP_SIZE>=15U) && (ADC_CFG_GRP14_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP14_SG==ADC_SG1))
	t_udGrp = ADC_GRP14;
	#endif
	Adc_ISR_CnvEnd(t_udGrp);
}
#endif

#if (defined(ADC_USE_ISR_ADC_HWUNIT0_SG2) || defined(ADC_USE_ISR_DMA_HWUNIT0_SG2))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit0_SG2(void)
{
 	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)		t_udGrp;
	#if		((ADC_CFG_GRP_SIZE>= 1U) && (ADC_CFG_GRP00_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP00_SG==ADC_SG2))
	t_udGrp = ADC_GRP00;
	#elif	((ADC_CFG_GRP_SIZE>= 2U) && (ADC_CFG_GRP01_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP01_SG==ADC_SG2))
	t_udGrp = ADC_GRP01;
	#elif	((ADC_CFG_GRP_SIZE>= 3U) && (ADC_CFG_GRP02_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP02_SG==ADC_SG2))
	t_udGrp = ADC_GRP02;
	#elif	((ADC_CFG_GRP_SIZE>= 4U) && (ADC_CFG_GRP03_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP03_SG==ADC_SG2))
	t_udGrp = ADC_GRP03;
	#elif	((ADC_CFG_GRP_SIZE>= 5U) && (ADC_CFG_GRP04_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP04_SG==ADC_SG2))
	t_udGrp = ADC_GRP04;
	#elif	((ADC_CFG_GRP_SIZE>= 6U) && (ADC_CFG_GRP05_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP05_SG==ADC_SG2))
	t_udGrp = ADC_GRP05;
	#elif	((ADC_CFG_GRP_SIZE>= 7U) && (ADC_CFG_GRP06_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP06_SG==ADC_SG2))
	t_udGrp = ADC_GRP06;
	#elif	((ADC_CFG_GRP_SIZE>= 8U) && (ADC_CFG_GRP07_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP07_SG==ADC_SG2))
	t_udGrp = ADC_GRP07;
	#elif	((ADC_CFG_GRP_SIZE>= 9U) && (ADC_CFG_GRP08_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP08_SG==ADC_SG2))
	t_udGrp = ADC_GRP08;
	#elif	((ADC_CFG_GRP_SIZE>=10U) && (ADC_CFG_GRP09_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP09_SG==ADC_SG2))
	t_udGrp = ADC_GRP09;
	#elif	((ADC_CFG_GRP_SIZE>=11U) && (ADC_CFG_GRP10_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP10_SG==ADC_SG2))
	t_udGrp = ADC_GRP10;
	#elif	((ADC_CFG_GRP_SIZE>=12U) && (ADC_CFG_GRP11_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP11_SG==ADC_SG2))
	t_udGrp = ADC_GRP11;
	#elif	((ADC_CFG_GRP_SIZE>=13U) && (ADC_CFG_GRP12_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP12_SG==ADC_SG2))
	t_udGrp = ADC_GRP12;
	#elif	((ADC_CFG_GRP_SIZE>=14U) && (ADC_CFG_GRP13_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP13_SG==ADC_SG2))
	t_udGrp = ADC_GRP13;
	#elif	((ADC_CFG_GRP_SIZE>=15U) && (ADC_CFG_GRP14_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP14_SG==ADC_SG2))
	t_udGrp = ADC_GRP14;
	#endif
	Adc_ISR_CnvEnd(t_udGrp);
}
#endif

#if (defined(ADC_USE_ISR_ADC_HWUNIT0_SG3) || defined(ADC_USE_ISR_DMA_HWUNIT0_SG3))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit0_SG3(void)
{
 	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)		t_udGrp;
	#if		((ADC_CFG_GRP_SIZE>= 1U) && (ADC_CFG_GRP00_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP00_SG==ADC_SG3))
	t_udGrp = ADC_GRP00;
	#elif	((ADC_CFG_GRP_SIZE>= 2U) && (ADC_CFG_GRP01_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP01_SG==ADC_SG3))
	t_udGrp = ADC_GRP01;
	#elif	((ADC_CFG_GRP_SIZE>= 3U) && (ADC_CFG_GRP02_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP02_SG==ADC_SG3))
	t_udGrp = ADC_GRP02;
	#elif	((ADC_CFG_GRP_SIZE>= 4U) && (ADC_CFG_GRP03_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP03_SG==ADC_SG3))
	t_udGrp = ADC_GRP03;
	#elif	((ADC_CFG_GRP_SIZE>= 5U) && (ADC_CFG_GRP04_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP04_SG==ADC_SG3))
	t_udGrp = ADC_GRP04;
	#elif	((ADC_CFG_GRP_SIZE>= 6U) && (ADC_CFG_GRP05_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP05_SG==ADC_SG3))
	t_udGrp = ADC_GRP05;
	#elif	((ADC_CFG_GRP_SIZE>= 7U) && (ADC_CFG_GRP06_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP06_SG==ADC_SG3))
	t_udGrp = ADC_GRP06;
	#elif	((ADC_CFG_GRP_SIZE>= 8U) && (ADC_CFG_GRP07_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP07_SG==ADC_SG3))
	t_udGrp = ADC_GRP07;
	#elif	((ADC_CFG_GRP_SIZE>= 9U) && (ADC_CFG_GRP08_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP08_SG==ADC_SG3))
	t_udGrp = ADC_GRP08;
	#elif	((ADC_CFG_GRP_SIZE>=10U) && (ADC_CFG_GRP09_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP09_SG==ADC_SG3))
	t_udGrp = ADC_GRP09;
	#elif	((ADC_CFG_GRP_SIZE>=11U) && (ADC_CFG_GRP10_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP10_SG==ADC_SG3))
	t_udGrp = ADC_GRP10;
	#elif	((ADC_CFG_GRP_SIZE>=12U) && (ADC_CFG_GRP11_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP11_SG==ADC_SG3))
	t_udGrp = ADC_GRP11;
	#elif	((ADC_CFG_GRP_SIZE>=13U) && (ADC_CFG_GRP12_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP12_SG==ADC_SG3))
	t_udGrp = ADC_GRP12;
	#elif	((ADC_CFG_GRP_SIZE>=14U) && (ADC_CFG_GRP13_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP13_SG==ADC_SG3))
	t_udGrp = ADC_GRP13;
	#elif	((ADC_CFG_GRP_SIZE>=15U) && (ADC_CFG_GRP14_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP14_SG==ADC_SG3))
	t_udGrp = ADC_GRP14;
	#endif
	Adc_ISR_CnvEnd(t_udGrp);
}
#endif

#if (defined(ADC_USE_ISR_ADC_HWUNIT0_SG4) || defined(ADC_USE_ISR_DMA_HWUNIT0_SG4))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit0_SG4(void)
{
 	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)		t_udGrp;
	#if		((ADC_CFG_GRP_SIZE>= 1U) && (ADC_CFG_GRP00_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP00_SG==ADC_SG4))
	t_udGrp = ADC_GRP00;
	#elif	((ADC_CFG_GRP_SIZE>= 2U) && (ADC_CFG_GRP01_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP01_SG==ADC_SG4))
	t_udGrp = ADC_GRP01;
	#elif	((ADC_CFG_GRP_SIZE>= 3U) && (ADC_CFG_GRP02_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP02_SG==ADC_SG4))
	t_udGrp = ADC_GRP02;
	#elif	((ADC_CFG_GRP_SIZE>= 4U) && (ADC_CFG_GRP03_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP03_SG==ADC_SG4))
	t_udGrp = ADC_GRP03;
	#elif	((ADC_CFG_GRP_SIZE>= 5U) && (ADC_CFG_GRP04_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP04_SG==ADC_SG4))
	t_udGrp = ADC_GRP04;
	#elif	((ADC_CFG_GRP_SIZE>= 6U) && (ADC_CFG_GRP05_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP05_SG==ADC_SG4))
	t_udGrp = ADC_GRP05;
	#elif	((ADC_CFG_GRP_SIZE>= 7U) && (ADC_CFG_GRP06_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP06_SG==ADC_SG4))
	t_udGrp = ADC_GRP06;
	#elif	((ADC_CFG_GRP_SIZE>= 8U) && (ADC_CFG_GRP07_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP07_SG==ADC_SG4))
	t_udGrp = ADC_GRP07;
	#elif	((ADC_CFG_GRP_SIZE>= 9U) && (ADC_CFG_GRP08_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP08_SG==ADC_SG4))
	t_udGrp = ADC_GRP08;
	#elif	((ADC_CFG_GRP_SIZE>=10U) && (ADC_CFG_GRP09_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP09_SG==ADC_SG4))
	t_udGrp = ADC_GRP09;
	#elif	((ADC_CFG_GRP_SIZE>=11U) && (ADC_CFG_GRP10_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP10_SG==ADC_SG4))
	t_udGrp = ADC_GRP10;
	#elif	((ADC_CFG_GRP_SIZE>=12U) && (ADC_CFG_GRP11_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP11_SG==ADC_SG4))
	t_udGrp = ADC_GRP11;
	#elif	((ADC_CFG_GRP_SIZE>=13U) && (ADC_CFG_GRP12_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP12_SG==ADC_SG4))
	t_udGrp = ADC_GRP12;
	#elif	((ADC_CFG_GRP_SIZE>=14U) && (ADC_CFG_GRP13_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP13_SG==ADC_SG4))
	t_udGrp = ADC_GRP13;
	#elif	((ADC_CFG_GRP_SIZE>=15U) && (ADC_CFG_GRP14_HWUNIT==ADC_HWUNIT0) && (ADC_CFG_GRP14_SG==ADC_SG4))
	t_udGrp = ADC_GRP14;
	#endif
	Adc_ISR_CnvEnd(t_udGrp);
}
#endif

#if (defined(ADC_USE_ISR_ADC_HWUNIT1_SG0) || defined(ADC_USE_ISR_DMA_HWUNIT1_SG0))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit1_SG0(void)
{
 	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)		t_udGrp;
	#if		((ADC_CFG_GRP_SIZE>= 1U) && (ADC_CFG_GRP00_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP00_SG==ADC_SG0))
	t_udGrp = ADC_GRP00;
	#elif	((ADC_CFG_GRP_SIZE>= 2U) && (ADC_CFG_GRP01_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP01_SG==ADC_SG0))
	t_udGrp = ADC_GRP01;
	#elif	((ADC_CFG_GRP_SIZE>= 3U) && (ADC_CFG_GRP02_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP02_SG==ADC_SG0))
	t_udGrp = ADC_GRP02;
	#elif	((ADC_CFG_GRP_SIZE>= 4U) && (ADC_CFG_GRP03_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP03_SG==ADC_SG0))
	t_udGrp = ADC_GRP03;
	#elif	((ADC_CFG_GRP_SIZE>= 5U) && (ADC_CFG_GRP04_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP04_SG==ADC_SG0))
	t_udGrp = ADC_GRP04;
	#elif	((ADC_CFG_GRP_SIZE>= 6U) && (ADC_CFG_GRP05_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP05_SG==ADC_SG0))
	t_udGrp = ADC_GRP05;
	#elif	((ADC_CFG_GRP_SIZE>= 7U) && (ADC_CFG_GRP06_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP06_SG==ADC_SG0))
	t_udGrp = ADC_GRP06;
	#elif	((ADC_CFG_GRP_SIZE>= 8U) && (ADC_CFG_GRP07_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP07_SG==ADC_SG0))
	t_udGrp = ADC_GRP07;
	#elif	((ADC_CFG_GRP_SIZE>= 9U) && (ADC_CFG_GRP08_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP08_SG==ADC_SG0))
	t_udGrp = ADC_GRP08;
	#elif	((ADC_CFG_GRP_SIZE>=10U) && (ADC_CFG_GRP09_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP09_SG==ADC_SG0))
	t_udGrp = ADC_GRP09;
	#elif	((ADC_CFG_GRP_SIZE>=11U) && (ADC_CFG_GRP10_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP10_SG==ADC_SG0))
	t_udGrp = ADC_GRP10;
	#elif	((ADC_CFG_GRP_SIZE>=12U) && (ADC_CFG_GRP11_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP11_SG==ADC_SG0))
	t_udGrp = ADC_GRP11;
	#elif	((ADC_CFG_GRP_SIZE>=13U) && (ADC_CFG_GRP12_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP12_SG==ADC_SG0))
	t_udGrp = ADC_GRP12;
	#elif	((ADC_CFG_GRP_SIZE>=14U) && (ADC_CFG_GRP13_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP13_SG==ADC_SG0))
	t_udGrp = ADC_GRP13;
	#elif	((ADC_CFG_GRP_SIZE>=15U) && (ADC_CFG_GRP14_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP14_SG==ADC_SG0))
	t_udGrp = ADC_GRP14;
	#endif
	Adc_ISR_CnvEnd(t_udGrp);
}
#endif

#if (defined(ADC_USE_ISR_ADC_HWUNIT1_SG1) || defined(ADC_USE_ISR_DMA_HWUNIT1_SG1))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit1_SG1(void)
{
 	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)		t_udGrp;
	#if		((ADC_CFG_GRP_SIZE>= 1U) && (ADC_CFG_GRP00_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP00_SG==ADC_SG1))
	t_udGrp = ADC_GRP00;
	#elif	((ADC_CFG_GRP_SIZE>= 2U) && (ADC_CFG_GRP01_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP01_SG==ADC_SG1))
	t_udGrp = ADC_GRP01;
	#elif	((ADC_CFG_GRP_SIZE>= 3U) && (ADC_CFG_GRP02_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP02_SG==ADC_SG1))
	t_udGrp = ADC_GRP02;
	#elif	((ADC_CFG_GRP_SIZE>= 4U) && (ADC_CFG_GRP03_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP03_SG==ADC_SG1))
	t_udGrp = ADC_GRP03;
	#elif	((ADC_CFG_GRP_SIZE>= 5U) && (ADC_CFG_GRP04_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP04_SG==ADC_SG1))
	t_udGrp = ADC_GRP04;
	#elif	((ADC_CFG_GRP_SIZE>= 6U) && (ADC_CFG_GRP05_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP05_SG==ADC_SG1))
	t_udGrp = ADC_GRP05;
	#elif	((ADC_CFG_GRP_SIZE>= 7U) && (ADC_CFG_GRP06_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP06_SG==ADC_SG1))
	t_udGrp = ADC_GRP06;
	#elif	((ADC_CFG_GRP_SIZE>= 8U) && (ADC_CFG_GRP07_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP07_SG==ADC_SG1))
	t_udGrp = ADC_GRP07;
	#elif	((ADC_CFG_GRP_SIZE>= 9U) && (ADC_CFG_GRP08_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP08_SG==ADC_SG1))
	t_udGrp = ADC_GRP08;
	#elif	((ADC_CFG_GRP_SIZE>=10U) && (ADC_CFG_GRP09_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP09_SG==ADC_SG1))
	t_udGrp = ADC_GRP09;
	#elif	((ADC_CFG_GRP_SIZE>=11U) && (ADC_CFG_GRP10_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP10_SG==ADC_SG1))
	t_udGrp = ADC_GRP10;
	#elif	((ADC_CFG_GRP_SIZE>=12U) && (ADC_CFG_GRP11_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP11_SG==ADC_SG1))
	t_udGrp = ADC_GRP11;
	#elif	((ADC_CFG_GRP_SIZE>=13U) && (ADC_CFG_GRP12_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP12_SG==ADC_SG1))
	t_udGrp = ADC_GRP12;
	#elif	((ADC_CFG_GRP_SIZE>=14U) && (ADC_CFG_GRP13_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP13_SG==ADC_SG1))
	t_udGrp = ADC_GRP13;
	#elif	((ADC_CFG_GRP_SIZE>=15U) && (ADC_CFG_GRP14_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP14_SG==ADC_SG1))
	t_udGrp = ADC_GRP14;
	#endif
	Adc_ISR_CnvEnd(t_udGrp);
}
#endif

#if (defined(ADC_USE_ISR_ADC_HWUNIT1_SG2) || defined(ADC_USE_ISR_DMA_HWUNIT1_SG2))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit1_SG2(void)
{
 	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)		t_udGrp;
	#if		((ADC_CFG_GRP_SIZE>= 1U) && (ADC_CFG_GRP00_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP00_SG==ADC_SG2))
	t_udGrp = ADC_GRP00;
	#elif	((ADC_CFG_GRP_SIZE>= 2U) && (ADC_CFG_GRP01_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP01_SG==ADC_SG2))
	t_udGrp = ADC_GRP01;
	#elif	((ADC_CFG_GRP_SIZE>= 3U) && (ADC_CFG_GRP02_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP02_SG==ADC_SG2))
	t_udGrp = ADC_GRP02;
	#elif	((ADC_CFG_GRP_SIZE>= 4U) && (ADC_CFG_GRP03_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP03_SG==ADC_SG2))
	t_udGrp = ADC_GRP03;
	#elif	((ADC_CFG_GRP_SIZE>= 5U) && (ADC_CFG_GRP04_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP04_SG==ADC_SG2))
	t_udGrp = ADC_GRP04;
	#elif	((ADC_CFG_GRP_SIZE>= 6U) && (ADC_CFG_GRP05_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP05_SG==ADC_SG2))
	t_udGrp = ADC_GRP05;
	#elif	((ADC_CFG_GRP_SIZE>= 7U) && (ADC_CFG_GRP06_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP06_SG==ADC_SG2))
	t_udGrp = ADC_GRP06;
	#elif	((ADC_CFG_GRP_SIZE>= 8U) && (ADC_CFG_GRP07_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP07_SG==ADC_SG2))
	t_udGrp = ADC_GRP07;
	#elif	((ADC_CFG_GRP_SIZE>= 9U) && (ADC_CFG_GRP08_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP08_SG==ADC_SG2))
	t_udGrp = ADC_GRP08;
	#elif	((ADC_CFG_GRP_SIZE>=10U) && (ADC_CFG_GRP09_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP09_SG==ADC_SG2))
	t_udGrp = ADC_GRP09;
	#elif	((ADC_CFG_GRP_SIZE>=11U) && (ADC_CFG_GRP10_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP10_SG==ADC_SG2))
	t_udGrp = ADC_GRP10;
	#elif	((ADC_CFG_GRP_SIZE>=12U) && (ADC_CFG_GRP11_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP11_SG==ADC_SG2))
	t_udGrp = ADC_GRP11;
	#elif	((ADC_CFG_GRP_SIZE>=13U) && (ADC_CFG_GRP12_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP12_SG==ADC_SG2))
	t_udGrp = ADC_GRP12;
	#elif	((ADC_CFG_GRP_SIZE>=14U) && (ADC_CFG_GRP13_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP13_SG==ADC_SG2))
	t_udGrp = ADC_GRP13;
	#elif	((ADC_CFG_GRP_SIZE>=15U) && (ADC_CFG_GRP14_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP14_SG==ADC_SG2))
	t_udGrp = ADC_GRP14;
	#endif
	Adc_ISR_CnvEnd(t_udGrp);
}
#endif

#if (defined(ADC_USE_ISR_ADC_HWUNIT1_SG3) || defined(ADC_USE_ISR_DMA_HWUNIT1_SG3))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit1_SG3(void)
{
 	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)		t_udGrp;
	#if		((ADC_CFG_GRP_SIZE>= 1U) && (ADC_CFG_GRP00_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP00_SG==ADC_SG3))
	t_udGrp = ADC_GRP00;
	#elif	((ADC_CFG_GRP_SIZE>= 2U) && (ADC_CFG_GRP01_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP01_SG==ADC_SG3))
	t_udGrp = ADC_GRP01;
	#elif	((ADC_CFG_GRP_SIZE>= 3U) && (ADC_CFG_GRP02_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP02_SG==ADC_SG3))
	t_udGrp = ADC_GRP02;
	#elif	((ADC_CFG_GRP_SIZE>= 4U) && (ADC_CFG_GRP03_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP03_SG==ADC_SG3))
	t_udGrp = ADC_GRP03;
	#elif	((ADC_CFG_GRP_SIZE>= 5U) && (ADC_CFG_GRP04_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP04_SG==ADC_SG3))
	t_udGrp = ADC_GRP04;
	#elif	((ADC_CFG_GRP_SIZE>= 6U) && (ADC_CFG_GRP05_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP05_SG==ADC_SG3))
	t_udGrp = ADC_GRP05;
	#elif	((ADC_CFG_GRP_SIZE>= 7U) && (ADC_CFG_GRP06_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP06_SG==ADC_SG3))
	t_udGrp = ADC_GRP06;
	#elif	((ADC_CFG_GRP_SIZE>= 8U) && (ADC_CFG_GRP07_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP07_SG==ADC_SG3))
	t_udGrp = ADC_GRP07;
	#elif	((ADC_CFG_GRP_SIZE>= 9U) && (ADC_CFG_GRP08_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP08_SG==ADC_SG3))
	t_udGrp = ADC_GRP08;
	#elif	((ADC_CFG_GRP_SIZE>=10U) && (ADC_CFG_GRP09_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP09_SG==ADC_SG3))
	t_udGrp = ADC_GRP09;
	#elif	((ADC_CFG_GRP_SIZE>=11U) && (ADC_CFG_GRP10_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP10_SG==ADC_SG3))
	t_udGrp = ADC_GRP10;
	#elif	((ADC_CFG_GRP_SIZE>=12U) && (ADC_CFG_GRP11_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP11_SG==ADC_SG3))
	t_udGrp = ADC_GRP11;
	#elif	((ADC_CFG_GRP_SIZE>=13U) && (ADC_CFG_GRP12_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP12_SG==ADC_SG3))
	t_udGrp = ADC_GRP12;
	#elif	((ADC_CFG_GRP_SIZE>=14U) && (ADC_CFG_GRP13_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP13_SG==ADC_SG3))
	t_udGrp = ADC_GRP13;
	#elif	((ADC_CFG_GRP_SIZE>=15U) && (ADC_CFG_GRP14_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP14_SG==ADC_SG3))
	t_udGrp = ADC_GRP14;
	#endif
	Adc_ISR_CnvEnd(t_udGrp);
}
#endif

#if (defined(ADC_USE_ISR_ADC_HWUNIT1_SG4) || defined(ADC_USE_ISR_DMA_HWUNIT1_SG4))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit1_SG4(void)
{
 	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)		t_udGrp;
	#if		((ADC_CFG_GRP_SIZE>= 1U) && (ADC_CFG_GRP00_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP00_SG==ADC_SG4))
	t_udGrp = ADC_GRP00;
	#elif	((ADC_CFG_GRP_SIZE>= 2U) && (ADC_CFG_GRP01_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP01_SG==ADC_SG4))
	t_udGrp = ADC_GRP01;
	#elif	((ADC_CFG_GRP_SIZE>= 3U) && (ADC_CFG_GRP02_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP02_SG==ADC_SG4))
	t_udGrp = ADC_GRP02;
	#elif	((ADC_CFG_GRP_SIZE>= 4U) && (ADC_CFG_GRP03_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP03_SG==ADC_SG4))
	t_udGrp = ADC_GRP03;
	#elif	((ADC_CFG_GRP_SIZE>= 5U) && (ADC_CFG_GRP04_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP04_SG==ADC_SG4))
	t_udGrp = ADC_GRP04;
	#elif	((ADC_CFG_GRP_SIZE>= 6U) && (ADC_CFG_GRP05_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP05_SG==ADC_SG4))
	t_udGrp = ADC_GRP05;
	#elif	((ADC_CFG_GRP_SIZE>= 7U) && (ADC_CFG_GRP06_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP06_SG==ADC_SG4))
	t_udGrp = ADC_GRP06;
	#elif	((ADC_CFG_GRP_SIZE>= 8U) && (ADC_CFG_GRP07_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP07_SG==ADC_SG4))
	t_udGrp = ADC_GRP07;
	#elif	((ADC_CFG_GRP_SIZE>= 9U) && (ADC_CFG_GRP08_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP08_SG==ADC_SG4))
	t_udGrp = ADC_GRP08;
	#elif	((ADC_CFG_GRP_SIZE>=10U) && (ADC_CFG_GRP09_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP09_SG==ADC_SG4))
	t_udGrp = ADC_GRP09;
	#elif	((ADC_CFG_GRP_SIZE>=11U) && (ADC_CFG_GRP10_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP10_SG==ADC_SG4))
	t_udGrp = ADC_GRP10;
	#elif	((ADC_CFG_GRP_SIZE>=12U) && (ADC_CFG_GRP11_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP11_SG==ADC_SG4))
	t_udGrp = ADC_GRP11;
	#elif	((ADC_CFG_GRP_SIZE>=13U) && (ADC_CFG_GRP12_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP12_SG==ADC_SG4))
	t_udGrp = ADC_GRP12;
	#elif	((ADC_CFG_GRP_SIZE>=14U) && (ADC_CFG_GRP13_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP13_SG==ADC_SG4))
	t_udGrp = ADC_GRP13;
	#elif	((ADC_CFG_GRP_SIZE>=15U) && (ADC_CFG_GRP14_HWUNIT==ADC_HWUNIT1) && (ADC_CFG_GRP14_SG==ADC_SG4))
	t_udGrp = ADC_GRP14;
	#endif
	Adc_ISR_CnvEnd(t_udGrp);
}
#endif

#if (defined(ADC_USE_ISR_ADC_HWUNIT2_SG0) || defined(ADC_USE_ISR_DMA_HWUNIT2_SG0))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit2_SG0(void)
{
 	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)		t_udGrp;
	#if		((ADC_CFG_GRP_SIZE>= 1U) && (ADC_CFG_GRP00_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP00_SG==ADC_SG0))
	t_udGrp = ADC_GRP00;
	#elif	((ADC_CFG_GRP_SIZE>= 2U) && (ADC_CFG_GRP01_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP01_SG==ADC_SG0))
	t_udGrp = ADC_GRP01;
	#elif	((ADC_CFG_GRP_SIZE>= 3U) && (ADC_CFG_GRP02_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP02_SG==ADC_SG0))
	t_udGrp = ADC_GRP02;
	#elif	((ADC_CFG_GRP_SIZE>= 4U) && (ADC_CFG_GRP03_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP03_SG==ADC_SG0))
	t_udGrp = ADC_GRP03;
	#elif	((ADC_CFG_GRP_SIZE>= 5U) && (ADC_CFG_GRP04_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP04_SG==ADC_SG0))
	t_udGrp = ADC_GRP04;
	#elif	((ADC_CFG_GRP_SIZE>= 6U) && (ADC_CFG_GRP05_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP05_SG==ADC_SG0))
	t_udGrp = ADC_GRP05;
	#elif	((ADC_CFG_GRP_SIZE>= 7U) && (ADC_CFG_GRP06_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP06_SG==ADC_SG0))
	t_udGrp = ADC_GRP06;
	#elif	((ADC_CFG_GRP_SIZE>= 8U) && (ADC_CFG_GRP07_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP07_SG==ADC_SG0))
	t_udGrp = ADC_GRP07;
	#elif	((ADC_CFG_GRP_SIZE>= 9U) && (ADC_CFG_GRP08_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP08_SG==ADC_SG0))
	t_udGrp = ADC_GRP08;
	#elif	((ADC_CFG_GRP_SIZE>=10U) && (ADC_CFG_GRP09_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP09_SG==ADC_SG0))
	t_udGrp = ADC_GRP09;
	#elif	((ADC_CFG_GRP_SIZE>=11U) && (ADC_CFG_GRP10_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP10_SG==ADC_SG0))
	t_udGrp = ADC_GRP10;
	#elif	((ADC_CFG_GRP_SIZE>=12U) && (ADC_CFG_GRP11_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP11_SG==ADC_SG0))
	t_udGrp = ADC_GRP11;
	#elif	((ADC_CFG_GRP_SIZE>=13U) && (ADC_CFG_GRP12_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP12_SG==ADC_SG0))
	t_udGrp = ADC_GRP12;
	#elif	((ADC_CFG_GRP_SIZE>=14U) && (ADC_CFG_GRP13_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP13_SG==ADC_SG0))
	t_udGrp = ADC_GRP13;
	#elif	((ADC_CFG_GRP_SIZE>=15U) && (ADC_CFG_GRP14_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP14_SG==ADC_SG0))
	t_udGrp = ADC_GRP14;
	#endif
	Adc_ISR_CnvEnd(t_udGrp);
}
#endif

#if (defined(ADC_USE_ISR_ADC_HWUNIT2_SG1) || defined(ADC_USE_ISR_DMA_HWUNIT2_SG1))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit2_SG1(void)
{
 	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)		t_udGrp;
	#if		((ADC_CFG_GRP_SIZE>= 1U) && (ADC_CFG_GRP00_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP00_SG==ADC_SG1))
	t_udGrp = ADC_GRP00;
	#elif	((ADC_CFG_GRP_SIZE>= 2U) && (ADC_CFG_GRP01_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP01_SG==ADC_SG1))
	t_udGrp = ADC_GRP01;
	#elif	((ADC_CFG_GRP_SIZE>= 3U) && (ADC_CFG_GRP02_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP02_SG==ADC_SG1))
	t_udGrp = ADC_GRP02;
	#elif	((ADC_CFG_GRP_SIZE>= 4U) && (ADC_CFG_GRP03_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP03_SG==ADC_SG1))
	t_udGrp = ADC_GRP03;
	#elif	((ADC_CFG_GRP_SIZE>= 5U) && (ADC_CFG_GRP04_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP04_SG==ADC_SG1))
	t_udGrp = ADC_GRP04;
	#elif	((ADC_CFG_GRP_SIZE>= 6U) && (ADC_CFG_GRP05_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP05_SG==ADC_SG1))
	t_udGrp = ADC_GRP05;
	#elif	((ADC_CFG_GRP_SIZE>= 7U) && (ADC_CFG_GRP06_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP06_SG==ADC_SG1))
	t_udGrp = ADC_GRP06;
	#elif	((ADC_CFG_GRP_SIZE>= 8U) && (ADC_CFG_GRP07_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP07_SG==ADC_SG1))
	t_udGrp = ADC_GRP07;
	#elif	((ADC_CFG_GRP_SIZE>= 9U) && (ADC_CFG_GRP08_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP08_SG==ADC_SG1))
	t_udGrp = ADC_GRP08;
	#elif	((ADC_CFG_GRP_SIZE>=10U) && (ADC_CFG_GRP09_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP09_SG==ADC_SG1))
	t_udGrp = ADC_GRP09;
	#elif	((ADC_CFG_GRP_SIZE>=11U) && (ADC_CFG_GRP10_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP10_SG==ADC_SG1))
	t_udGrp = ADC_GRP10;
	#elif	((ADC_CFG_GRP_SIZE>=12U) && (ADC_CFG_GRP11_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP11_SG==ADC_SG1))
	t_udGrp = ADC_GRP11;
	#elif	((ADC_CFG_GRP_SIZE>=13U) && (ADC_CFG_GRP12_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP12_SG==ADC_SG1))
	t_udGrp = ADC_GRP12;
	#elif	((ADC_CFG_GRP_SIZE>=14U) && (ADC_CFG_GRP13_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP13_SG==ADC_SG1))
	t_udGrp = ADC_GRP13;
	#elif	((ADC_CFG_GRP_SIZE>=15U) && (ADC_CFG_GRP14_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP14_SG==ADC_SG1))
	t_udGrp = ADC_GRP14;
	#endif
	Adc_ISR_CnvEnd(t_udGrp);
}
#endif

#if (defined(ADC_USE_ISR_ADC_HWUNIT2_SG2) || defined(ADC_USE_ISR_DMA_HWUNIT2_SG2))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit2_SG2(void)
{
 	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)		t_udGrp;
	#if		((ADC_CFG_GRP_SIZE>= 1U) && (ADC_CFG_GRP00_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP00_SG==ADC_SG2))
	t_udGrp = ADC_GRP00;
	#elif	((ADC_CFG_GRP_SIZE>= 2U) && (ADC_CFG_GRP01_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP01_SG==ADC_SG2))
	t_udGrp = ADC_GRP01;
	#elif	((ADC_CFG_GRP_SIZE>= 3U) && (ADC_CFG_GRP02_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP02_SG==ADC_SG2))
	t_udGrp = ADC_GRP02;
	#elif	((ADC_CFG_GRP_SIZE>= 4U) && (ADC_CFG_GRP03_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP03_SG==ADC_SG2))
	t_udGrp = ADC_GRP03;
	#elif	((ADC_CFG_GRP_SIZE>= 5U) && (ADC_CFG_GRP04_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP04_SG==ADC_SG2))
	t_udGrp = ADC_GRP04;
	#elif	((ADC_CFG_GRP_SIZE>= 6U) && (ADC_CFG_GRP05_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP05_SG==ADC_SG2))
	t_udGrp = ADC_GRP05;
	#elif	((ADC_CFG_GRP_SIZE>= 7U) && (ADC_CFG_GRP06_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP06_SG==ADC_SG2))
	t_udGrp = ADC_GRP06;
	#elif	((ADC_CFG_GRP_SIZE>= 8U) && (ADC_CFG_GRP07_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP07_SG==ADC_SG2))
	t_udGrp = ADC_GRP07;
	#elif	((ADC_CFG_GRP_SIZE>= 9U) && (ADC_CFG_GRP08_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP08_SG==ADC_SG2))
	t_udGrp = ADC_GRP08;
	#elif	((ADC_CFG_GRP_SIZE>=10U) && (ADC_CFG_GRP09_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP09_SG==ADC_SG2))
	t_udGrp = ADC_GRP09;
	#elif	((ADC_CFG_GRP_SIZE>=11U) && (ADC_CFG_GRP10_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP10_SG==ADC_SG2))
	t_udGrp = ADC_GRP10;
	#elif	((ADC_CFG_GRP_SIZE>=12U) && (ADC_CFG_GRP11_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP11_SG==ADC_SG2))
	t_udGrp = ADC_GRP11;
	#elif	((ADC_CFG_GRP_SIZE>=13U) && (ADC_CFG_GRP12_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP12_SG==ADC_SG2))
	t_udGrp = ADC_GRP12;
	#elif	((ADC_CFG_GRP_SIZE>=14U) && (ADC_CFG_GRP13_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP13_SG==ADC_SG2))
	t_udGrp = ADC_GRP13;
	#elif	((ADC_CFG_GRP_SIZE>=15U) && (ADC_CFG_GRP14_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP14_SG==ADC_SG2))
	t_udGrp = ADC_GRP14;
	#endif
	Adc_ISR_CnvEnd(t_udGrp);
}
#endif

#if (defined(ADC_USE_ISR_ADC_HWUNIT2_SG3) || defined(ADC_USE_ISR_DMA_HWUNIT2_SG3))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit2_SG3(void)
{
 	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)		t_udGrp;
	#if		((ADC_CFG_GRP_SIZE>= 1U) && (ADC_CFG_GRP00_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP00_SG==ADC_SG3))
	t_udGrp = ADC_GRP00;
	#elif	((ADC_CFG_GRP_SIZE>= 2U) && (ADC_CFG_GRP01_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP01_SG==ADC_SG3))
	t_udGrp = ADC_GRP01;
	#elif	((ADC_CFG_GRP_SIZE>= 3U) && (ADC_CFG_GRP02_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP02_SG==ADC_SG3))
	t_udGrp = ADC_GRP02;
	#elif	((ADC_CFG_GRP_SIZE>= 4U) && (ADC_CFG_GRP03_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP03_SG==ADC_SG3))
	t_udGrp = ADC_GRP03;
	#elif	((ADC_CFG_GRP_SIZE>= 5U) && (ADC_CFG_GRP04_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP04_SG==ADC_SG3))
	t_udGrp = ADC_GRP04;
	#elif	((ADC_CFG_GRP_SIZE>= 6U) && (ADC_CFG_GRP05_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP05_SG==ADC_SG3))
	t_udGrp = ADC_GRP05;
	#elif	((ADC_CFG_GRP_SIZE>= 7U) && (ADC_CFG_GRP06_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP06_SG==ADC_SG3))
	t_udGrp = ADC_GRP06;
	#elif	((ADC_CFG_GRP_SIZE>= 8U) && (ADC_CFG_GRP07_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP07_SG==ADC_SG3))
	t_udGrp = ADC_GRP07;
	#elif	((ADC_CFG_GRP_SIZE>= 9U) && (ADC_CFG_GRP08_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP08_SG==ADC_SG3))
	t_udGrp = ADC_GRP08;
	#elif	((ADC_CFG_GRP_SIZE>=10U) && (ADC_CFG_GRP09_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP09_SG==ADC_SG3))
	t_udGrp = ADC_GRP09;
	#elif	((ADC_CFG_GRP_SIZE>=11U) && (ADC_CFG_GRP10_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP10_SG==ADC_SG3))
	t_udGrp = ADC_GRP10;
	#elif	((ADC_CFG_GRP_SIZE>=12U) && (ADC_CFG_GRP11_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP11_SG==ADC_SG3))
	t_udGrp = ADC_GRP11;
	#elif	((ADC_CFG_GRP_SIZE>=13U) && (ADC_CFG_GRP12_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP12_SG==ADC_SG3))
	t_udGrp = ADC_GRP12;
	#elif	((ADC_CFG_GRP_SIZE>=14U) && (ADC_CFG_GRP13_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP13_SG==ADC_SG3))
	t_udGrp = ADC_GRP13;
	#elif	((ADC_CFG_GRP_SIZE>=15U) && (ADC_CFG_GRP14_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP14_SG==ADC_SG3))
	t_udGrp = ADC_GRP14;
	#endif
	Adc_ISR_CnvEnd(t_udGrp);
}
#endif

#if (defined(ADC_USE_ISR_ADC_HWUNIT2_SG4) || defined(ADC_USE_ISR_DMA_HWUNIT2_SG4))
static FUNC(void, ADC_CODE) Adc_Intrpt_HWUnit2_SG4(void)
{
 	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)		t_udGrp;
	#if		((ADC_CFG_GRP_SIZE>= 1U) && (ADC_CFG_GRP00_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP00_SG==ADC_SG4))
	t_udGrp = ADC_GRP00;
	#elif	((ADC_CFG_GRP_SIZE>= 2U) && (ADC_CFG_GRP01_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP01_SG==ADC_SG4))
	t_udGrp = ADC_GRP01;
	#elif	((ADC_CFG_GRP_SIZE>= 3U) && (ADC_CFG_GRP02_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP02_SG==ADC_SG4))
	t_udGrp = ADC_GRP02;
	#elif	((ADC_CFG_GRP_SIZE>= 4U) && (ADC_CFG_GRP03_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP03_SG==ADC_SG4))
	t_udGrp = ADC_GRP03;
	#elif	((ADC_CFG_GRP_SIZE>= 5U) && (ADC_CFG_GRP04_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP04_SG==ADC_SG4))
	t_udGrp = ADC_GRP04;
	#elif	((ADC_CFG_GRP_SIZE>= 6U) && (ADC_CFG_GRP05_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP05_SG==ADC_SG4))
	t_udGrp = ADC_GRP05;
	#elif	((ADC_CFG_GRP_SIZE>= 7U) && (ADC_CFG_GRP06_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP06_SG==ADC_SG4))
	t_udGrp = ADC_GRP06;
	#elif	((ADC_CFG_GRP_SIZE>= 8U) && (ADC_CFG_GRP07_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP07_SG==ADC_SG4))
	t_udGrp = ADC_GRP07;
	#elif	((ADC_CFG_GRP_SIZE>= 9U) && (ADC_CFG_GRP08_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP08_SG==ADC_SG4))
	t_udGrp = ADC_GRP08;
	#elif	((ADC_CFG_GRP_SIZE>=10U) && (ADC_CFG_GRP09_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP09_SG==ADC_SG4))
	t_udGrp = ADC_GRP09;
	#elif	((ADC_CFG_GRP_SIZE>=11U) && (ADC_CFG_GRP10_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP10_SG==ADC_SG4))
	t_udGrp = ADC_GRP10;
	#elif	((ADC_CFG_GRP_SIZE>=12U) && (ADC_CFG_GRP11_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP11_SG==ADC_SG4))
	t_udGrp = ADC_GRP11;
	#elif	((ADC_CFG_GRP_SIZE>=13U) && (ADC_CFG_GRP12_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP12_SG==ADC_SG4))
	t_udGrp = ADC_GRP12;
	#elif	((ADC_CFG_GRP_SIZE>=14U) && (ADC_CFG_GRP13_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP13_SG==ADC_SG4))
	t_udGrp = ADC_GRP13;
	#elif	((ADC_CFG_GRP_SIZE>=15U) && (ADC_CFG_GRP14_HWUNIT==ADC_HWUNIT2) && (ADC_CFG_GRP14_SG==ADC_SG4))
	t_udGrp = ADC_GRP14;
	#endif
	Adc_ISR_CnvEnd(t_udGrp);
}
#endif

#define ADC_STOP_SEC_CODE_FAST_GLOBAL
#include "Adc_MemMap.h"

#endif

/*--------------------------------------------------------------------------*/
/* only when DMA is available												*/
/*--------------------------------------------------------------------------*/
#define ADC_START_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

#ifdef ADC_USE_DMA
/************************************************************************************************/
/* Service name			: Adc_SetDataBuffer														*/
/* Sync/Async			: Asynchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/*		DataBufferPtr	: Async: pointer to result data buffer									*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: Initializes the ADC internal data buffer address.						*/
/************************************************************************************************/
static FUNC(void, ADC_CODE) Adc_SetDataBuffer(
	CONST(Adc_GroupType,					ADC_CONST)		t_cudGrp,
	P2VAR(Adc_ValueGroupType, AUTOMATIC,	ADC_VAR_INIT)	t_pudDataBuffer
)
{
	s_stAdcGrpInfo[t_cudGrp].pudDataBuffer		= t_pudDataBuffer;		/* pointer to result data buffer		*/
}

/************************************************************************************************/
/* Service name			: Adc_GetDataBuffer														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: Adc_ValueGroupType*	: pointer to result data buffer					*/
/* Description			: get the top of data buffer address.									*/
/************************************************************************************************/
static FUNC_P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_CODE) Adc_GetDataBuffer(
	CONST(Adc_GroupType, ADC_CONST) t_cudGrp
)
{
	return(s_stAdcGrpInfo[t_cudGrp].pudDataBuffer);
}

/*--------------------------------------------------------------------------*/
/* only when Streaming Access is available									*/
/*--------------------------------------------------------------------------*/
#ifdef ADC_USE_STREAMING_ACCESS
/************************************************************************************************/
/* Service name			: Adc_GetCurrentStreamingNum											*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Adc_GroupType	: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: The number of conversions in  streaming access mode					*/
/* Description			: Get the number of conversions in  streaming access mode.				*/
/************************************************************************************************/
static FUNC(Adc_StreamNumSampleType, ADC_CODE) Adc_GetCurrentStreamingNum(
	CONST(Adc_GroupType,  ADC_CONST) t_cudGrp
)
{
	return(s_stAdcGrpInfo[t_cudGrp].udStreamingNum);
}
#endif
#endif

/*----------------------------------------------------------------------------------------------*/
/* Private API (public API in ADC module) 														*/
/*----------------------------------------------------------------------------------------------*/
/************************************************************************************************/
/* Service name			: Adc_GetGrpStatus														*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: 																		*/
/*		Adc_StatusType	: Group conversion status												*/
/* Description			: return the group conversion status									*/
/************************************************************************************************/
FUNC(Adc_StatusType, ADC_CODE) Adc_GetGrpStatus(
	CONST(Adc_GroupType, ADC_CONST) t_cudGrp
)
{
	return(s_stAdcGrpInfo[t_cudGrp].udStatus);
}

#if ((ADC_CFG_DEINIT_API==STD_ON)||((ADC_CFG_REG_CHK==STD_ON)&&(ADC_CFG_REG_REFRESH==STD_ON)&&(MCAL_SPAL_TARGET==MCAL_TARGET_RH850U2B)))
/************************************************************************************************/
/* Service name			: Adc_IsRunning															*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Reentrant																*/
/* Parameters (in)		: None																	*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: 																		*/
/*		Adc status		: TRUE: some conversion is active, FALSE:no conversion is active		*/
/* Description			: return the all group conversion status								*/
/************************************************************************************************/
FUNC(boolean, ADC_CODE) Adc_IsRunning(void)
{
	VAR(boolean,		ADC_VAR_NO_INIT)			t_b1isRunning;
	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)			t_udGrp;

	t_b1isRunning = FALSE;
	for (t_udGrp=ADC_GRP00;t_udGrp<(Adc_GroupType)ADC_CFG_GRP_SIZE;t_udGrp++) {
		if (Adc_GetGrpStatus(t_udGrp)!=ADC_IDLE) {
			t_b1isRunning = TRUE;
			break;
		}
	}
	return(t_b1isRunning);
}
#endif

#if ((ADC_CFG_REG_CHK==STD_ON)&&((ADC_CFG_REG_REFRESH==STD_ON)||(defined(ADC_USE_TH))))
/************************************************************************************************/
/* Service name			: Adc_IsHWUnitRunning													*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/* 		Adc_HWUnitType	: HW Unit Number														*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: 																		*/
/*		Adc status		: TRUE: some conversion is active, FALSE:no conversion is active		*/
/* Description			: return the HW Unit conversion status									*/
/************************************************************************************************/
FUNC(boolean, ADC_CODE) Adc_IsHWUnitRunning(
	CONST(Adc_HWUnitType,	ADC_CONST)	t_cudHWUnit
)
{
	VAR(boolean,		ADC_VAR_NO_INIT)	t_b1isRunning;
	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)	t_udGrp;

	t_b1isRunning = FALSE;
	for (t_udGrp=ADC_GRP00;t_udGrp<(Adc_GroupType)ADC_CFG_GRP_SIZE;t_udGrp++) {
		if (t_cudHWUnit==Adc_GetHWUnitID(t_udGrp)) {
			if (Adc_GetGrpStatus(t_udGrp)!=ADC_IDLE) {
				t_b1isRunning = TRUE;
				break;
			}
		}
	}
	return(t_b1isRunning);
}
#endif

#ifdef ADC_USE_TH
/************************************************************************************************/
/* Service name			: Adc_SetTHGrp															*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Adc_TrackHoldGroupType	: Async: Track and Hold Group (None/Grp A/Grp B)				*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: None																	*/
/* Description			: set Track and Hold Group (public API in ADC module)					*/
/************************************************************************************************/
FUNC(void, ADC_CODE) Adc_SetTHGrp(
	P2VAR(Adc_TrackHoldGroupType, AUTOMATIC, ADC_VAR_INIT)	t_pudTHGrp
)
{
	VAR(Adc_GroupType,  ADC_VAR_NO_INIT)	t_udGrp;

	for (t_udGrp=ADC_GRP00;t_udGrp<(Adc_GroupType)ADC_CFG_GRP_SIZE;t_udGrp++) {
		s_stAdcGrpInfo[t_udGrp].udTHGrp = t_pudTHGrp[t_udGrp];
	}
}
#endif

/*--------------------------------------------------------------------------*/
/* only when ((register check or HW Trigger API) and T&H) is available.		*/
/*--------------------------------------------------------------------------*/
/************************************************************************************************/
/* Service name			: Adc_GetTHGrp															*/
/* Sync/Async			: Synchronous															*/
/* Reentrancy			: Non Reentrant															*/
/* Parameters (in)		: 																		*/
/*		Group			: Numeric ID of requested ADC channel group.							*/
/* Parameters (inout)	: None																	*/
/* Parameters (out)		: None																	*/
/* Return value			: Track and Hold Group (None/Grp A/Grp B)								*/
/* Description			: get Track and Hold Group												*/
/************************************************************************************************/
#if (((ADC_CFG_REG_CHK==STD_ON) && (defined(ADC_USE_TH))) || ((ADC_CFG_HW_TRG_API==STD_ON) && (defined(ADC_USE_TH))))
FUNC(Adc_TrackHoldGroupType, ADC_CODE) Adc_GetTHGrp(
	CONST(Adc_GroupType, ADC_CONST) t_cudGrp
)
{
	VAR(Adc_TrackHoldGroupType,  ADC_VAR_NO_INIT)	t_udTHGrp;

	t_udTHGrp = ADC_TH_GRP_NONE;
	if (t_cudGrp<(Adc_GroupType)ADC_CFG_GRP_SIZE) {
		t_udTHGrp = s_stAdcGrpInfo[t_cudGrp].udTHGrp;
	}
	return(t_udTHGrp);
}
#endif

#define ADC_STOP_SEC_CODE_GLOBAL
#include "Adc_MemMap.h"

/*-- End Of File -------------------------------------------------------------------------------*/
