/* Dem_Pm_DataCtl_h(v5-5-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Pm_DataCtl/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PM_DATACTL_H
#define DEM_PM_DATACTL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Data_Cfg.h"
#include "Dem_Rc_DataMng.h"

#include "Dem_Pm_DataEeo.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    boolean ConfirmedOccurFlag;
    boolean MILOccurFlag;
} Dem_OrderListOccurredFlagType;

typedef struct
{
    Dem_u08_FFDIndexType                TriggerFFDIndex;
    Dem_u08_StorageTriggerType          TriggerFFDStorageTrigger;
    Dem_u08_ConsistencyIdType           TriggerFFDConsistencyId;
    Dem_u08_FFRecordNumberType          StartRecordNumber;
    boolean                             TriggerFFDExistStatus;
    boolean                             JudgeOutputTSFFDFlag;
    boolean                             AlreadyOutputBeforeTSFFDStatus;
} Dem_TmpCheckRecordDataType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*----------------------------------*/
/*  Dem_DataCtl                     */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_DataCtl_Init
( void );
FUNC( void, DEM_CODE ) Dem_DataCtl_Init_AfterRecordCheckComplete
( void );

#if ( DEM_INDICATOR_USE == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_SetHealingCounterToTmp
(
    VAR( Dem_u08_HealingCounterType, AUTOMATIC ) HealingCounter
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetHealingCounterFromTmp
(
    P2VAR( Dem_u08_HealingCounterType, AUTOMATIC, AUTOMATIC ) HealingCounterPtr
);
#endif  /* ( DEM_INDICATOR_USE == STD_ON )  */

FUNC( void, DEM_CODE ) Dem_Data_SetNumOfFaultAndFFD
( void );

/*----------------------------------*/
/*  Dem_DataCtl_Clear               */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Data_RequestFixedClear
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

/*----------------------------------*/
/*  Dem_DataCtl_DisableDTCInfo      */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Data_SaveDisabledRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber
);
FUNC( void, DEM_CODE ) Dem_Data_ClearDisabledRecord
( void );
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_Data_GetDTCStatusOfDisabledRecord
( void );
FUNC( boolean, DEM_CODE ) Dem_Data_GetIsUnderClearDTCOfDisabledRecord
( void );
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_DataCtl_GetEventStrgIndexOfDisabledRecordPairEvent
( void );
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )       */

/*------------------------------------------*/
/*  Dem_DataCtl_DisableDTCInfo_RecNumMng    */
/*------------------------------------------*/
FUNC( Dem_u32_FFDOutputTotalSizeType, DEM_CODE ) Dem_Data_GetSizeOfAllStoredFreezeFrame
( void );

/*----------------------------------*/
/*  Dem_DataCtl_EventEntry          */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SaveEventMemoryEntryToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Data_UpdateEventMemoryEntryFromTmp
( void );
FUNC( boolean, DEM_CODE ) Dem_Data_CheckFaultRecordOverwrite
(
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusAtOverwrittenPtr
);
FUNC( boolean, DEM_CODE ) Dem_Data_CheckTSFFDeleteByFFROverwritten
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_CheckStorePredictiveFFDOfTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

/*----------------------------------*/
/*  Dem_DataCtl_EventEntry_RecordUpdate     */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Data_UpdEvtMemEntryOfTmp_InitializeEvent
( void );
FUNC( void, DEM_CODE ) Dem_Data_UpdEvtMemEntryOfTmp_NormalizeEvent
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
FUNC( void, DEM_CODE ) Dem_Data_UpdEvtMemEntryOfTmp_AgingEvent
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
FUNC( void, DEM_CODE ) Dem_Data_UpdEvtMemEntryOfTmp_PendingOFFEvent
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
);
FUNC( void, DEM_CODE ) Dem_Data_UpdEvtMemEntryOfTmp_PendingOFFAndAgingEvent
( void );

/*----------------------------------*/
/*  Dem_DataCtl_EventEntry02Clear   */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Data_ClearSearchFFDIndex
( void );

/*--------------------------------------*/
/*  Dem_DataCtl_EventEntry02Make_Event  */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_Data_GetDTCStatusFromTmp
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
FUNC( void, DEM_CODE ) Dem_Data_SetDTCStatusStructToTmp
(
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr
);
FUNC( void, DEM_CODE ) Dem_Data_GetDTCStatusStructFromTmp
(
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr
);
FUNC( void, DEM_CODE ) Dem_Data_InitFailureCounterOfTmp
( void );
FUNC( void, DEM_CODE ) Dem_Data_GetFailureCounterFromTmp
(
    P2VAR( Dem_u08_FailureCounterType, AUTOMATIC, AUTOMATIC ) FailureCounterPtr,
    P2VAR( Dem_u08_FailureCounterType, AUTOMATIC, AUTOMATIC ) FailureCounterThresholdPtr
);
FUNC( void, DEM_CODE ) Dem_Data_IncrementFailureCounterOfTmp
( void );
FUNC( void, DEM_CODE ) Dem_Data_IncrementEventOccurrenceCounterOfTmp
( void );

/*--------------------------------------*/
/*  Dem_DataCtl_EventEntry02Make_Fault  */
/*--------------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetFaultInfo
(
    P2CONST( Dem_OrderListOccurredFlagType, AUTOMATIC, AUTOMATIC ) OccurFlagPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) FaultOccurrenceFlagPtr
);
FUNC( boolean, DEM_CODE ) Dem_Data_CheckExistsEventMemoryEntryOfTmp
( void );
FUNC( void, DEM_CODE ) Dem_Data_SetAgingCounterToTmp
(
    VAR( Dem_u08_AgingCounterType, AUTOMATIC ) AgingCounter
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetAgingCounterFromTmp
(
    P2VAR( Dem_u08_AgingCounterType, AUTOMATIC, AUTOMATIC ) AgingCounterPtr
);
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_SetDTCStatusForFaultRecordOverwrite
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusForFaultRecordOverwrite
);
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    */

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_SetTimeAgingCounterToTmp
(
    VAR( Dem_u16_WWHOBDTimeAgingCounterType, AUTOMATIC ) TimeAgingCounter
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetTimeAgingCounterFromTmp
(
    P2VAR( Dem_u16_WWHOBDTimeAgingCounterType, AUTOMATIC, AUTOMATIC ) TimeAgingCounterPtr
);
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

/*--------------------------------------*/
/*  Dem_DataCtl_EventEntry02Make_FFD    */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_Data_CaptureFreezeFrame
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) Trigger,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);

/*----------------------------------*/
/*  Dem_DataCtl_EventEntry04Regist  */
/*----------------------------------*/
FUNC( Dem_u08_EventMemoryUpdateStatusType, DEM_CODE ) Dem_Data_GetEventMemoryUpdatingStatus
( void );

/*----------------------------------*/
/*  Dem_DataCtl_EvtDisplacement     */
/*----------------------------------*/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_SelectEventEntryOverwrite
( void );

FUNC( void, DEM_CODE ) Dem_Data_GetEventPriorityAndStatusOfDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventEntryOverwriteType, AUTOMATIC, AUTOMATIC ) EventEntryOverwritePtr
);
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )     */

/*----------------------------------*/
/*  Dem_DataCtl_FilteredDTC         */
/*----------------------------------*/
#if ( DEM_OBD_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFilteredObdDTC
(
    P2VAR( Dem_u08_OrderIndexType, AUTOMATIC, AUTOMATIC ) FaultSearchIndexPtr,
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) FilterdEventStrgIndexPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
);
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

/*----------------------------------*/
/*  Dem_DataCtl_FilteredRecord      */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Data_GetNumberOfFilteredRecords
(
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) NumberOfFilteredRecordsPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFilteredRecord
(
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) ObdRecordNumberIndexPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) RecordNumberIndexPtr,
    P2VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC, AUTOMATIC ) TSFFListIndexPtr,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFFRecIndexPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
);

/*----------------------------------*/
/*  Dem_DataCtl_GetTSFFD_local      */
/*----------------------------------*/
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetTSFFRecordFromTSFFList
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) OffsetOfIndex,
    P2VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameRecordPtr
);
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )     */

/*----------------------------------*/
/*  Dem_DataCtl_InfoEvent           */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetDTCStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetNumberOfEventMemoryEntries
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u08_OrderIndexType, AUTOMATIC, AUTOMATIC ) NumberOfEventMemoryEntriesPtr
);

/*----------------------------------*/
/*  Dem_DataCtl_InfoFFD             */
/*----------------------------------*/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetObdFreezeFrameData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FFDGetInfoType, AUTOMATIC ) FreezeFrameGetInfoType,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DataPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) DataSizePtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFreezeFrameData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FFDGetInfoType, AUTOMATIC ) FreezeFrameGetInfoType,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DataPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) DataSizePtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_CheckSupportedFreezeFrameRecordNumber
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) FreezeFrameDataType      /* MISRA DEVIATION */
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetEventFreezeFrameData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FreezeFrameDataType, AUTOMATIC ) FreezeFrameDataType,
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) DataID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr
);
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
#if ( DEM_OBDFFD_DID_SUPPORT == STD_OFF )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFFRecordByPidData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_PIDNumberType, AUTOMATIC ) PID,
    VAR( Dem_u08_DtElNumPerDIDIndexType, AUTOMATIC ) DataElementIndexOfPID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr
);
#endif  /* ( DEM_OBDFFD_DID_SUPPORT == STD_OFF )       */
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )      */

FUNC( void, DEM_CODE ) Dem_Data_ResetSearchStartPosition
( void );

FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_Data_SearchTargetEventStrgIndexFromRecordNumber
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber
);
FUNC( void, DEM_CODE ) Dem_Data_SetNextRecordNumber
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
);

#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_GetConfirmedTriggerNonOBDFFDIndex
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameClassRefPtr
);
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( Dem_u16_TSFFListIndexType, DEM_CODE ) Dem_Data_GetConfirmedTriggerBeforeTSFFListIndexAndInfo
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) NumberOfBeforeTriggeredRecordPtr,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameClassRefPtr
);
#endif  /* (DEM_TSFF_PM_SUPPORT == STD_ON) */
#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */


/*----------------------------------*/
/*  Dem_DataCtl_OrderList           */
/*----------------------------------*/
#if ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF )
FUNC( void, DEM_CODE ) Dem_Data_AllClearFaultOrderList
( void );
#endif  /* ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF ) */
FUNC( void, DEM_CODE ) Dem_Data_GenerateFaultOrderList
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFaultIndexByOccurrenceOrder
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderIndex,
    P2VAR( Dem_u08_FaultIndexType, AUTOMATIC, AUTOMATIC ) FaultIndexPtr
);

/*--------------------------------------*/
/*  Dem_DataCtl_OrderList_Confirmed     */
/*--------------------------------------*/
#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )

#if ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF )
FUNC( void, DEM_CODE ) Dem_Data_AllClearConfirmedFaultOrderList
( void );
#endif  /* ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF ) */
FUNC( void, DEM_CODE ) Dem_Data_GenerateConfirmedFaultOrderList
( void );

#endif  /* ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )    */

/*----------------------------------*/
/*  Dem_DataCtl_OrderList_MIL       */
/*----------------------------------*/
#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
#if ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF )
FUNC( void, DEM_CODE ) Dem_Data_AllClearMILFaultOrderList
( void );
#endif  /* ( DEM_CLEAR_EVENT_NOT_ALLOWED_SUPPORT == STD_OFF ) */
FUNC( void, DEM_CODE ) Dem_Data_GenerateMILFaultOrderList
( void );
#endif  /*   ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )        */

/*---------------------------------------*/
/*  Dem_DataCtl_SpecificEventEntry.c     */
/*---------------------------------------*/
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_UpdateSpecificEventMemoryEntryFromTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_DATACTL_H */

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
/****************************************************************************/

/**** End of File ***********************************************************/
