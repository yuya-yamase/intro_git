/* Dem_Pm_Control_h(v5-10-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Pm_Control/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PM_CONTROL_H
#define DEM_PM_CONTROL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_Pm_DataCtl.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )

/*----------------------------------*/
/*  Dem_Control_Specific            */
/*----------------------------------*/
typedef struct {
    boolean  TestFailed;
    boolean  TestNotCompThisHealingCycle;    /* retCheckTestNotCompThisHealingCycle */
    boolean  TestFailedThisHealingCycle;     /* retCheckTestFailedThisHealingCycle */
    boolean  TestNotCompThisAgingCycle;    /* retCheckTestNotCompThisAgingCycle */
    boolean  TestFailedThisAgingCycle;     /* retCheckTestFailedThisAgingCycle */
    boolean  ConfirmedDTC;              /* retCheckConfirmedDTC */
    boolean  PendingDTC;                /* retCheckPendingDTC */
    boolean  WirStatus;                 /* retCheckWIRStatus */
    boolean  IndicatorStatus;           /*  */
}Dem_ChkBitDTCStatusType;

typedef struct {
    boolean  Healing;                   /* chkSpCondHealing */
    boolean  Aging;                     /* chkSpCondAging */
}Dem_ChkSpCondType;

#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )           */

/*--------------------------------------------------------------------------*/
/* Function Prototypes - PreInit section                                    */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE_TRUST ) Dem_Control_PreInitDTCSettingStatus       /*  PreInit section     */
( void );

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*----------------------------------*/
/*  Dem_Control_Clear               */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Control_StartClearDTC_PrimaryMemory
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ClearRAM_PrimaryMemory
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup
);
FUNC( void, DEM_CODE ) Dem_Control_EndClearDTC_PrimaryMemory
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_u08_ClearCompleteType, AUTOMATIC ) ClearResult
);
FUNC( void, DEM_CODE ) Dem_Control_PrepareClear_PrimaryMemory
( void );

/*----------------------------------*/
/*  Dem_Control_DTCSetting          */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_DisableDTCSetting
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_EnableDTCSetting
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetDTCSettingStatusForIF
(
    P2VAR( Dem_DTCSettingStatusType, AUTOMATIC, AUTOMATIC ) DTCSettingStatusPtr
);
FUNC( void, DEM_CODE ) Dem_Control_InitDTCSettingStatus
( void );

FUNC( void, DEM_CODE ) Dem_Control_DTCSettingProcess
( void );
FUNC( void, DEM_CODE ) Dem_Control_DTCSettingStatus_RefreshRAM
( void );

FUNC( Dem_u08_DTCSettingStatusType, DEM_CODE ) Dem_Control_GetDTCSettingStatus
( void );

/*----------------------------------*/
/*  Dem_Control_DisableDTCInfo      */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Control_InitDTCRecordUpdateInfo
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_DisableDTCRecordUpdate
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);

FUNC( void, DEM_CODE ) Dem_Control_EnableDTCRecordUpdate
( void );
FUNC( Dem_u08_DTCRecordUpdateStatusType, DEM_CODE ) Dem_Control_GetDTCRecordUpdateStatus_PrimaryMemory
( void );

/*----------------------------------*/
/*  Dem_Control_EventEntry          */
/*----------------------------------*/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetEventCommon
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    VAR( boolean, AUTOMATIC ) ActiveFaultReqFlag
);

/*----------------------------------*/
/*  Dem_Control_FCThreshold.c       */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEventFailureCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_u08_FailureCounterType, AUTOMATIC ) FailureCycleCounterThreshold
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ResetEventFailureCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventFailureCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC )                           EventId,
    P2VAR( Dem_u08_FailureCounterType, AUTOMATIC, AUTOMATIC )   FailureCycleCounterThresholdPtr
);

/*----------------------------------*/
/*  Dem_Control_EventEntry          */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetInitializeEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetAgingEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetNormalizeEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetActiveFaultEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);

/*----------------------------------*/
/*  Dem_Control_EventInfo           */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetStatusOfDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetHealingCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_u08_HealingCounterType, AUTOMATIC, AUTOMATIC ) HealingCounterPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetAgingCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_u08_AgingCounterType, AUTOMATIC, AUTOMATIC ) AgingCounterPtr
);
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetAgingTime
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_u16_WWHOBDTimeAgingCounterType, AUTOMATIC, AUTOMATIC ) AgingTimePtr
);
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */

#if ( DEM_OBD_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventKind
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_EventKindType, AUTOMATIC, AUTOMATIC ) EventKindPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCClassPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IsMILIndicatorPtr
);
#endif /* ( DEM_OBD_SUPPORT == STD_ON ) */
#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetConfirmedDTCOrder
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) OrderPtr
);
#endif /* ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON ) */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetFaultOccurrenceDTCOrder
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) OrderPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetActiveFault
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ActiveFaultPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventFailureCycleCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_u08_FailureCounterType, AUTOMATIC, AUTOMATIC ) FailureCounterPtr
);
#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventOccurrenceCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_u08_EventOccurrenceCounterType, AUTOMATIC, AUTOMATIC ) OccurrenceCounterPtr
);
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )   */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventIdListByFaultRecordOrder
(
    VAR( Dem_u08_EventListModeType, AUTOMATIC ) EventListMode,
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA ) EventIdBufferPtr,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdNumPtr
);
#if ( DEM_OBD_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventIdListByConfirmedOrder
(
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA ) EventIdBufferPtr,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdNumPtr
);
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetUDSDTCByConfirmedDTCOrder
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) UDSDTCBufferPtr,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) UDSDTCNumPtr
);
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */

/*----------------------------------*/
/*  Dem_Control_EvtAvl              */
/*----------------------------------*/
#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEvtAvl
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( boolean, AUTOMATIC ) AvailableStatus
);
#endif  /* ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON ) */

/*----------------------------------*/
/*  Dem_Control_FFDInfo             */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventFreezeFrameData
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u16_DIDNumberType, AUTOMATIC ) DataID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufferSizePtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetSizeOfFreezeFrameByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC, AUTOMATIC ) SizeOfFreezeFramePtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetFreezeFrameDataByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
);

/*----------------------------------*/
/*  Dem_Control_FilteredDTC         */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetDTCFilter
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( boolean, AUTOMATIC ) FilterWithSeverity,
    VAR( Dem_DTCSeverityType, AUTOMATIC ) DTCSeverityMask,
    VAR( boolean, AUTOMATIC ) FilterForFaultDetectionCounter
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNumberOfFilteredDTC
(
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) NumberOfFilteredDTCPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNumberOfFilteredDTCAndSeverity
(
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) NumberOfFilteredDTCAndSeverityPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNextFilteredDTC
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNextFilteredDTCAndSeverity
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
);

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetDTCFilterForReadiness
(
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) ReadinessGroupId
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNumberOfFilteredDTCForReadiness
(
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) NumberOfFilteredDTCForReadinessPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNextFilteredDTCForReadiness
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )  */

/*----------------------------------*/
/*  Dem_Control_FilteredEDR         */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEDRNumberFilter
(
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNumberOfEDRNumFilteredDTC
(
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) NumberOfEDRNumFilteredDTCPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNextEDRNumFilteredDTC
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);

/*----------------------------------*/
/*  Dem_Control_FilteredRecord      */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetFreezeFrameRecordFilter
(
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) NumberOfFilteredRecordsPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNextFilteredRecord
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
);

/*----------------------------------*/
/*  Dem_Control_OpCycleUpdCommon    */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Control_UpdateEventMemEntryByOpCycle_PrimaryMemory
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos,
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) NeedGenOrderListPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ExecHealingPtr
);

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( Dem_u16_WWHOBDTimeAgingCounterType, DEM_CODE ) Dem_Control_GetTimeSinceEngineStartSinceLastDCY
( void );

FUNC( void, DEM_CODE ) Dem_Control_JudgeAndGetTimeSinceEngineStartSinceLastDCY
(
    VAR( Dem_u08_OpCycleKindIndexType, AUTOMATIC ) ThisCycleKindIndex
);
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

/*----------------------------------*/
/*  Dem_Control_IUMPR               */
/*----------------------------------*/
#if ( DEM_IUMPR_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Control_InitIUMPRInfo
( void );
FUNC( void, DEM_CODE ) Dem_Control_UpdateIUMPRProcess
( void );
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )  */


/*----------------------------------*/
/*  Dem_Control_PrestoreFFD         */
/*----------------------------------*/
#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_PrestoreFreezeFrame
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ClearPrestoredFreezeFrame
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
#endif  /* - DEM_FF_PRESTORAGE_SUPPORT == STD_ON -  */

/*----------------------------------*/
/*  Dem_Control_PID                 */
/*----------------------------------*/
#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Control_InitPIDInfo
( void );
FUNC( void, DEM_CODE ) Dem_Control_UpdatePIDProcess
( void );
#endif  /* ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON ) */


/*----------------------------------*/
/*  Dem_Control_StoredData          */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Control_InitDTCStoredDataStatus
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_StartDTCStoredData
( void );
FUNC( void, DEM_CODE ) Dem_Control_EndDTCStoredData
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetSizeOfDTCStoredDataByRecNum
(
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) StoredDataSizePtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetDTCStoredDataByRecNum
(
    VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u32_StoredDataRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_StoredDataRecordNumberType, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
);
FUNC( Dem_u08_DTCStoredDataStatusType, DEM_CODE ) Dem_Control_GetDTCStoredDataStatus
( void );

/*----------------------------------*/
/*  Dem_Control_MonSts              */
/*----------------------------------*/
#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetMonitorStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_MonitorStatusType, AUTOMATIC, AUTOMATIC ) MonitorStatusPtr
);
#endif /* ( DEM_TRIGGER_FIM_REPORTS == STD_ON ) */

/*----------------------------------*/
/*  Dem_Control_OccrDTC             */
/*----------------------------------*/
#if ( DEM_TRIGGER_DCM_REPORTS == STD_ON )
FUNC( void, DEM_CODE ) Dem_Control_DTCStatusChangedNotification
(
    VAR( boolean, AUTOMATIC ) TriggerNotification
);
#endif  /*   ( DEM_TRIGGER_DCM_REPORTS == STD_ON )  */
#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetDTCByOccurrenceTime
(
    VAR( Dem_DTCRequestType, AUTOMATIC ) DTCRequest,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr
);
#endif  /*   ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )  */

/*----------------------------------*/
/*  Dem_Control_EDRInfo             */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventExtendedData
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
);
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetCylinderExtendedData
(
    VAR(Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
);
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetSizeOfExtendedDataRecordByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) SizeOfExtendedDataRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetExtendedDataRecordByDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr,
    P2VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC, AUTOMATIC ) NextExtendedDataNumberPtr
);

/*--------------------------------------*/
/*  Dem_Control_EventUdsStatusHistory   */
/*--------------------------------------*/
#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ResetEventUdsStatusHistory
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC ) UDSStatusHistoryByte
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEventUdsStatusHistory
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC ) UDSStatusHistoryByte
);
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_PM_CONTROL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

