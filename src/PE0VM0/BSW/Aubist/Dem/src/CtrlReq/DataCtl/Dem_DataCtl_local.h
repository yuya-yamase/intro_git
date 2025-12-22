/* Dem_DataCtl_local_h(v5-7-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_local/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_DATACTL_LOCAL_H
#define DEM_DATACTL_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_CmnLib_DataCtl.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* FFD Index Type.                                                          */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8   Dem_u08_FFDTriggerIndexType;
#define     DEM_FFDTRIGGER_IDX_TFTOC                ((Dem_u08_FFDTriggerIndexType)0U)
#define     DEM_FFDTRIGGER_IDX_PENDING              ((Dem_u08_FFDTriggerIndexType)1U)
#define     DEM_FFDTRIGGER_IDX_CONFIRMED            ((Dem_u08_FFDTriggerIndexType)2U)
#define     DEM_FFDTRIGGER_IDX_FDC_THRESHOLD        ((Dem_u08_FFDTriggerIndexType)3U)
#define     DEM_FFDTRIGGER_IDX_MAX                  ((Dem_u08_FFDTriggerIndexType)4U)


typedef struct
{
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
    boolean  ObdFFRClrFlg[DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM];
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */
    boolean  FFRClrFlg[DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM];
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
    boolean  TSFFLClrFlg[DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM];
#endif /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

} Dem_FFListRecordForClrType;

/* SID19-04 */
typedef struct {

    Dem_u16_EventStrgIndexType              EventStrgIndex;
    boolean                                 UnderClearDTC;
    Dem_UdsStatusByteType                   StatusOfDTC;
    Dem_FaultRecordPartsFFDIndexListStType  FFDIndexListSt;

} Dem_TmpDisabledRecordType;

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
typedef struct {
    Dem_u16_OccrOrderType               OccurrenceOrder;
    Dem_u16_EventStrgIndexType          EventStrgIndex;
    Dem_u08_FFDIndexType                FreezeFrameIndex;
    Dem_u08_EventClassPriorityType      EventClassPriority;
    Dem_u08_EventStatusPriorityType     EventStatusPriority;
} Dem_TmpRecordNumberForOnRetrievalType;
#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*----------------------------------*/
/*  Dem_DataCtl_Clear               */
/*----------------------------------*/

/*----------------------------------*/
/*  Dem_DataCtl_DisableDTCInfo      */
/*----------------------------------*/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_GetTmpDisabledRecordObdFFRIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_GetTmpDisabledRecordFFRIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex
);

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_DataCtl_SaveTmpDisabledRecordPairEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_DataCtl_SaveRecordNumberByPairEvent
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    P2VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC, AUTOMATIC ) NumberOfSaveRecordPtr
);

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataCtl_SaveRecordNumberByPairEventForFilteredRecord
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    P2VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC, AUTOMATIC ) NumberOfSaveRecordPtr
);
#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */

FUNC( void, DEM_CODE ) Dem_DataCtl_ClearDisabledRecordPairEvent
( void );

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataCtl_GetTmpDisabledRecordObdFFRIndexAtPairEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordIndexPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )     */
FUNC( void, DEM_CODE ) Dem_DataCtl_GetTmpDisabledRecordFFRIndexAtPairEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordIndexPtr
);
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )       */

/*----------------------------------*/
/*  Dem_DataCtl_FilteredDTC         */
/*----------------------------------*/

/*----------------------------------*/
/*  Dem_DataCtl_FilteredRecord      */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFilteredRecordSub
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    P2VAR( Dem_FilteredRecordSearchInfoType, AUTOMATIC, DEM_VAR_NO_INIT ) FilteredRecordSearchInfoPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
);

/*----------------------------------*/
/*  Dem_DataCtl_OrderList           */
/*----------------------------------*/

/*----------------------------------*/
/*  Dem_DataCtl_InfoDem             */
/*----------------------------------*/

/*----------------------------------*/
/*  Dem_DataCtl_InfoEvent           */
/*----------------------------------*/

/*----------------------------------*/
/*  Dem_DataCtl_InfoFFRec           */
/*----------------------------------*/

/*----------------------------------*/
/*  Dem_DataCtl_InfoFFD             */
/*----------------------------------*/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFFRTriggerByFFRClassIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,
    P2VAR( Dem_u08_StorageTriggerType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordTriggerPtr
);
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_Data_JudgeOutputOBDFFDTrigger
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) StatusOfDTC,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )     */

/*----------------------------------*/
/*  Dem_DataCtl_InfoFFD_ChkSptFFDRecNum.c   */
/*----------------------------------*/
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetTSFFDInfoByEventAndRecNum
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) StartingRecordNumberPtr,
    P2VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRefIndexPtr,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameClassRefPtr,
    P2VAR( Dem_u08_StorageTriggerType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordTriggerPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) JudgeBeforeTSFFDFlagPtr
);
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )    */

/*----------------------------------*/
/*  Dem_DataCtl_InfoFFD_GetFFDByDTC.c   */
/*----------------------------------*/
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFFDataFromTSFF
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FFDGetInfoType, AUTOMATIC ) FreezeFrameGetInfoType,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DataPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) DataSizePtr
);
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )    */

/*----------------------------------*/
/*  Dem_DataCtl_InfoFFD_GetTSFFD    */
/*----------------------------------*/
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetTSFFRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRefIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) OffsetOfIndex,
    P2VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameRecordPtr
);

#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

/*----------------------------------------------*/
/*  Dem_DataCtl_DisableDTCInfo_RecNumMng.c      */
/*----------------------------------------------*/
FUNC( void, DEM_CODE ) Dem_Data_InitSaveTmpRecordNumber
( void );

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_InitSaveTmpRecordNumberForFilteredRecord
( void );
#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */

FUNC( void, DEM_CODE ) Dem_Data_SortTmpRecordNumber
(
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) NumberOfSaveRecord
);
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_SaveObdRecordNumberByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr,
    P2VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC, AUTOMATIC ) NumberOfSaveRecordPtr
);
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_SaveObdRecordNumberByDTCForFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    P2VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC, AUTOMATIC ) NumberOfSaveRecordPtr
);
#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )      */
FUNC( void, DEM_CODE ) Dem_Data_SaveRecordNumberByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr,
    P2VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC, AUTOMATIC ) NumberOfSaveRecordPtr
);
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_SaveRecordNumberByDTCForFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    P2VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC, AUTOMATIC ) NumberOfSaveRecordPtr
);
#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_SaveTSFFRecordNumberByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr,
    P2VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC, AUTOMATIC ) NumberOfSaveRecordPtr
);
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_SaveTSFFRecordNumberByDTCForFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,      /* MISRA DEVIATION */
    P2VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC, AUTOMATIC ) NumberOfSaveRecordPtr
);
#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )      */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_JudgeOutputFFDByFFDType
(
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) FreezeFrameDataType,
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameRecordIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_StopOutputTSFFDAfterTriggerFFD
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameRecordIndex
);

FUNC( void, DEM_CODE ) Dem_Data_StartOutputTSFFDAfterTSFFD
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) StartingRecordNumber
);
FUNC( void, DEM_CODE ) Dem_Data_StopOutputTSFFDAfterTSFFD
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( boolean, AUTOMATIC ) BeforeTSFFDFlag
);
FUNC( void, DEM_CODE ) Dem_Data_SetAlreadyOutputBeforeTSFFDStatus
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( boolean, AUTOMATIC ) BeforeTSFFDFlag
);
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_InitTmpRecordNumberForOnRetrieval
(
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TmpRecordNumberForOnRetrievalPtr
);
FUNC( void, DEM_CODE ) Dem_Data_SetEventClassPriorityForOnRetrieval
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_TmpRecordNumberForOnRetrievalType, AUTOMATIC, AUTOMATIC ) TmpRecordNumberForOnRetrievalPtr
);
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_Data_SearchNonObdEventStrgIndexByTSFFRTrigger
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) TSFFRecordTrigger,
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) NumberOfSaveRecordForTriggerFFD,
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameRecNumClassPtr
);
FUNC( Dem_u16_TSFFListIndexType, DEM_CODE ) Dem_Data_GetTSFFListIndexByEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TSFFRecClassRefIndex
);
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */
#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_GetDisabledObdRecordNumberIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
);
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_GetDisabledObdRecordNumberIndexForFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
);
#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_GetDisabledRecordNumberIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
);
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_GetDisabledRecordNumberIndexForFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
);
#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( Dem_u16_TSFFListIndexType, DEM_CODE ) Dem_Data_GetDisabledTimeSeriesFreezeFrameListIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TSFFRecClassRefIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TSFFRecordTrigger,
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) NumberOfSaveRecordForTriggerFFD,
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
);
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
FUNC( Dem_u16_TSFFListIndexType, DEM_CODE ) Dem_Data_GetDisabledTimeSeriesFreezeFrameListIndexForFilteredRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TSFFRecClassRefIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TSFFRecordTrigger,
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) NumberOfSaveRecordForTriggerFFD,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
);
#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_DataCtl_CheckOutputRecordByTrigger_OBDFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )     */

FUNC( boolean, DEM_CODE ) Dem_DataCtl_CheckOutputRecordByTrigger_FFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger
);
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )       */

/*----------------------------------*/
/*  Dem_DataCtl_EventEntry04Regist  */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Data_SetEventMemoryUpdatingStatus
(
    VAR( Dem_u08_EventMemoryUpdateStatusType, AUTOMATIC ) UpdatingStatus
);

FUNC( void, DEM_CODE ) Dem_Data_SubtractOneFromNumOfEventMemoryEntries
(
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, AUTOMATIC ) EventMemoryRecordPtr
);

FUNC( void, DEM_CODE ) Dem_Data_ClearEventRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_ClearFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_ClearObdFreezeFrameRecord
(
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, AUTOMATIC ) EventMemoryRecordPtr
);
#endif  /*  ( DEM_OBDFFD_SUPPORT == STD_ON )    */

FUNC( void, DEM_CODE ) Dem_Data_ClearFreezeFrameRecord
(
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, AUTOMATIC ) EventMemoryRecordPtr
);

FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_ClearTargetFFListRecord
(
    P2CONST( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
);

FUNC( void, DEM_CODE ) Dem_Data_ClearTargetFFRecordInFaultRecord
(
    P2CONST( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, AUTOMATIC ) EventMemoryRecordPtr
);

/*----------------------------------*/
/*  Dem_DataCtl_FFDClearPattern.c  */
/*----------------------------------*/
FUNC( boolean, DEM_CODE ) Dem_DataCtl_GetClearTargetFaultRecord
(
    VAR( Dem_u08_FaultRecoveryIndexType, AUTOMATIC ) RecoveryMode,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);

FUNC( boolean, DEM_CODE ) Dem_DataCtl_GetClearTargetFFRecord
(
    VAR( Dem_u08_FaultRecoveryIndexType, AUTOMATIC ) RecoveryMode,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    P2VAR( Dem_FFListRecordForClrType, AUTOMATIC, AUTOMATIC ) ClearFFListRecordPtr
);

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataCtl_ClearTargetMisfCylinderFFD
(
    VAR( Dem_u08_FaultRecoveryIndexType, AUTOMATIC ) RecoveryMode,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )     */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

extern VAR( Dem_TmpRecordNumberByDTCType, DEM_VAR_NO_INIT ) Dem_TmpRecordNumberByDTC[DEM_TOTAL_NUM_OF_RECNUM_PER_DTC];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#endif /* DEM_DATACTL_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
