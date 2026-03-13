/* Dem_FuncTypes_h(v5-9-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/FuncTypes/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef DEM_FUNCTYPES_H
#define DEM_FUNCTYPES_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem/Dem_Types.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_TRUST          /*  PreInit section                     */
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE_TRUST ) Dem_PreInit                  /*  PreInit section     */
( void );

#define DEM_STOP_SEC_CODE_TRUST           /*  PreInit section                     */
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------*/
/*  Dem_Main                            */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_Init
(
    P2CONST( Dem_ConfigType, AUTOMATIC, DEM_APPL_CONST ) ConfigPtr
);
FUNC( void, DEM_CODE ) Dem_Shutdown
( void );
FUNC( Dem_ModeType, DEM_CODE ) Dem_GetMode
( void );
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_ExpireNvMSyncIdleTaskTime
( void );
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )            */

/*--------------------------------------*/
/*  Dem_If                              */
/*--------------------------------------*/
#if ( DEM_VERSION_INFO_API == STD_ON )
FUNC( void, DEM_CODE ) Dem_GetVersionInfo
(
    P2VAR( Std_VersionInfoType, AUTOMATIC, DEM_APPL_DATA ) versioninfo
);
#endif /* DEM_VERSION_INFO_API -STD_ON- */
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus
);
#if  ( DEM_MONITORDATA_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetEventStatusWithMonitorData
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData1
);
#endif /* (DEM_MONITORDATA_SUPPORT == STD_ON) */
#if  ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetEventFailedWithSyncFreezeFrame
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId    /* port defined argument */
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetUserDefinedMemoryIdentifier
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) MemoryIdentifierPtr
);
#endif /* (DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON) */
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetWIRStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    VAR( boolean, AUTOMATIC ) WIRStatus
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventUdsStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA ) UDSStatusByte
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventUdsStatusHistory
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC, DEM_APPL_DATA ) UDSStatusHistoryBytePtr
);

FUNC( Std_ReturnType, DEM_CODE ) Dem_GetDTCOfEvent
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTCOfEvent
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_ClearDTC
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventFreezeFrameDataEx
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    VAR( uint8, AUTOMATIC ) RecordNumber,
    VAR( uint16, AUTOMATIC ) DataId,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBuffer,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) BufSize
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventExtendedDataRecordEx
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    VAR( uint8, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBuffer,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) BufSize
);
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetCylinderExtendedDataRecordEx
(
    VAR(Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    VAR( uint8, AUTOMATIC ) RecordNumber,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBufferPtr,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) BufSizePtr
);
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetNumberOfEventMemoryEntries
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,    /* port defined argument */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) NumberOfEventMemoryEntries
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_RestartOperationCycle
(
    VAR( uint8, AUTOMATIC ) OperationCycleId    /* port defined argument */
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetIndicatorStatus
(
    VAR( uint8, AUTOMATIC ) IndicatorId,    /* port defined argument */
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA ) IndicatorStatus
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetIndicatorStatusByEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    VAR( uint8, AUTOMATIC ) IndicatorId,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, DEM_APPL_DATA ) IndicatorStatusPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetEventAvailable
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    VAR( boolean, AUTOMATIC ) AvailableStatus
);
FUNC( Dem_ReturnControlDTCSettingType, DEM_CODE ) Dem_DisableDTCSetting
(
    VAR( uint32, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
);
FUNC( Dem_ReturnControlDTCSettingType, DEM_CODE ) Dem_EnableDTCSetting
(
    VAR( uint32, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetDTCSettingStatus
(
    P2VAR( Dem_DTCSettingStatusType, AUTOMATIC, DEM_APPL_DATA ) DTCSettingStatusPtr
);
#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetMonitorStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( Dem_MonitorStatusType, AUTOMATIC, DEM_APPL_DATA ) MonitorStatus
);
#endif /* DEM_TRIGGER_FIM_REPORTS -STD_ON- */
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetEventFailureCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    VAR( uint8, AUTOMATIC ) FailureCycleCounterThreshold
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_ResetEventFailureCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId    /* port defined argument */
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventFailureCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) FailureCycleCounterThresholdPtr
);

FUNC( Std_ReturnType, DEM_CODE ) Dem_InitializeEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId    /* port defined argument */
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_AgingEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId    /* port defined argument */
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_NormalizeEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId    /* port defined argument */
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_ActiveFaultEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId    /* port defined argument */
);
#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_PrestoreFreezeFrame
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId    /* port defined argument */
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_ClearPrestoredFreezeFrame
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId    /* port defined argument */
);
#endif /* DEM_FF_PRESTORAGE_SUPPORT -STD_ON- */
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetHealingCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) HealingCounterPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetAgingCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) AgingCounterPtr
);
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetAgingTime
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) AgingTimePtr
);
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetActiveFault
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( boolean, AUTOMATIC, DEM_APPL_DATA ) ActiveFaultPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetFaultOccurrenceDTCOrder
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) OrderPtr
);
#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetConfirmedDTCOrder
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) OrderPtr
);
#endif  /* ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )    */
#if  ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetUserDefinedMemoryFreezeFrameRecordNumber
(
    VAR( uint32, AUTOMATIC ) DTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RecordNumBufferPtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) RecordNumPtr
);
#endif /* (DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON) */

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_ResetEventUdsStatusHistory
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC ) UDSStatusHistoryByte
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetEventUdsStatusHistory
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC ) UDSStatusHistoryByte
);
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetRecordInfoByNvMBlockId
(
    VAR( Dem_BlockIdType, AUTOMATIC ) BlockId,
    P2VAR( Dem_RecordKindType, AUTOMATIC, DEM_APPL_DATA ) RecordKindPtr,
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA ) EventIdPtr
);
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventFailureCycleCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) FailureCycleCounterPtr
);
#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventOccurrenceCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) OccurrenceCounterPtr
);
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )   */
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventIdWithPendingDTC
(
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA ) EventIdBufferPtr,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) EventIdNumPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventIdWithActiveFaultDTC
(
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA ) EventIdBufferPtr,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) EventIdNumPtr
);
#if ( DEM_OBD_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventIdWithConfirmedDTC
(
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA ) EventIdBufferPtr,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) EventIdNumPtr
);
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetUDSDTCByConfirmedDTCOrder
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) UDSDTCBufferPtr,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) UDSDTCNumPtr
);
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */

/*--------------------------------------*/
/*  Dem_If_OBD                          */
/*--------------------------------------*/
#if ( DEM_PID_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPID01
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID01value
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPID1C
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID1Cvalue
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPID21
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPID30
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID30value
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPID31
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPID41
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID41value
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPID4D
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPID4E
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfPIDF501
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PIDF501value
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetDataOfPID21
(
    P2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetDataOfPID31
(
    P2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetDataOfPID4D
(
    P2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetDataOfPID4E
(
    P2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
);
#endif /* DEM_PID_SUPPORT -STD_ON- */
#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetCycleQualified
(
    VAR( uint8, AUTOMATIC ) OperationCycleId    /* port defined argument */
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetCycleQualified
(
    VAR( uint8, AUTOMATIC ) OperationCycleId,    /* port defined argument */
    P2VAR( boolean, AUTOMATIC, DEM_APPL_DATA ) IsQualified
);
#endif  /* ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )     */

#if ( DEM_OBD_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventKind
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( Dem_EventKindType, AUTOMATIC, DEM_APPL_DATA ) EventKindPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, DEM_APPL_DATA ) DTCClassPtr,
    P2VAR( boolean, AUTOMATIC, DEM_APPL_DATA ) IsMILIndicatorPtr
);
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )        */

#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetPermanentUDSDTC
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) PermanentDTCBufferPtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PermanentDTCNumPtr
);
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetPermanentOBDDTC
(
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) PermanentDTCBufferPtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PermanentDTCNumPtr
);
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )             */
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetClearPFCCycleQualified
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( boolean, AUTOMATIC, DEM_APPL_DATA ) PassedCycleQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, DEM_APPL_DATA ) DrivingConditionQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, DEM_APPL_DATA ) PFCCycleQualifiedPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_CheckExistPermanentDTCByEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( boolean, AUTOMATIC, DEM_APPL_DATA ) IsPermanentDTCPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventIdWithPermanentDTC
(
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA ) EventIdBufferPtr,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) EventIdNumPtr
);

#if ( DEM_PFC_RECORD_SUPPRESSION_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_DisablePFCRecordUpdate
( void );
FUNC( Std_ReturnType, DEM_CODE ) Dem_EnablePFCRecordUpdate
( void );
#endif /* DEM_PFC_RECORD_SUPPRESSION_SUPPORT -STD_ON- */
FUNC( Std_ReturnType, DEM_CODE ) Dem_ClearAllPFC
( void );
#endif /* DEM_PFC_SUPPORT -STD_ON- */

#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetDTCOfOBDFreezeFrame
(
    VAR( uint8, AUTOMATIC ) FrameNumber,
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) DTC
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfOBDFreezeFrame
(
    VAR( uint8, AUTOMATIC ) PID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBuffer,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) BufSize
);
#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON )         */

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetEventDisabled
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId    /* port defined argument */
);
#endif /* DEM_PID_READINESS_SUPPORT -STD_ON- */

#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_ReadDataOfAltIUMPRDenominator
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DenominatorPtr
);
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )    */

/*--------------------------------------*/
/*  Dem_If_DTR_OBD                      */
/*--------------------------------------*/
#if ( DEM_DTR_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetDTR
(
    VAR( uint16, AUTOMATIC ) DTRId,    /* port defined argument */
    VAR( sint32, AUTOMATIC ) TestResult,
    VAR( sint32, AUTOMATIC ) LowerLimit,
    VAR( sint32, AUTOMATIC ) UpperLimit,
    VAR( Dem_DTRControlType, AUTOMATIC ) Ctrlval
);
#if ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetDTR
(
    VAR( uint16, AUTOMATIC ) DTRId,    /* port defined argument */
    P2VAR( sint32, AUTOMATIC, DEM_APPL_DATA ) TestResultPtr,
    P2VAR( sint32, AUTOMATIC, DEM_APPL_DATA ) LowerLimitPtr,
    P2VAR( sint32, AUTOMATIC, DEM_APPL_DATA ) UpperLimitPtr,
    P2VAR( Dem_DTRControlType, AUTOMATIC, DEM_APPL_DATA ) CtrlvalPtr
);
#endif /* DEM_DTR_RAWDATASTORAGE_SUPPORT -STD_ON- */
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetDTRConvertInfo
(
    VAR( uint16, AUTOMATIC ) DTRId,    /* port defined argument */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DtrMidPtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DtrTidPtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DtrUasidPtr,
    P2VAR( sint32, AUTOMATIC, DEM_APPL_DATA ) CompuN0DivD0Ptr,
    P2VAR( sint32, AUTOMATIC, DEM_APPL_DATA ) CompuN1DivD0Ptr
);
#endif /* DEM_DTR_SUPPORT -STD_ON- */

/*--------------------------------------*/
/*  Dem_If_IUMPR_OBD                    */
/*--------------------------------------*/
#if ( DEM_IUMPR_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetIUMPRDenCondition
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC ) ConditionId,
    P2VAR( Dem_IumprDenomCondStatusType, AUTOMATIC, DEM_APPL_DATA ) ConditionStatus
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetIUMPRDenCondition
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )  ConditionId,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC ) ConditionStatus
);
#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_RepIUMPRDenRelease
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioID    /* port defined argument */
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_RepIUMPRFaultDetect
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioID    /* port defined argument */
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetIUMPRDataByRatioId
(
    VAR( Dem_RatioIdType, AUTOMATIC )           RatioID,    /* port defined argument */
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA )   NumeratorPtr,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA )   DenominatorPtr
);
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )        */
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetIUMPRGeneralDenominator
(
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) GeneralDenominatorPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetIUMPRIGCycleCounter
(
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) IGCycleCounterPtr
);
#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetIUMPRInfoTypeValue
(
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   IumprDataBufferPtr,
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   IumprDataBufferSizePtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetEventIdByRatioId
(
    VAR( Dem_RatioIdType, AUTOMATIC )                   RatioID,    /* port defined argument */
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA )  EventIdPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetRatioIdByEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( Dem_RatioIdType, AUTOMATIC, DEM_APPL_DATA ) RatioIdBufferPtr,
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) RatioIdNumPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_JudgeMinimumRatioThanCurrentRatio
(
    VAR( uint16, AUTOMATIC )    CurrentNumerator,
    VAR( uint16, AUTOMATIC )    CurrentDenominator,
    VAR( uint16, AUTOMATIC )    TargetNumerator,
    VAR( uint16, AUTOMATIC )    TargetDenominator,
    P2VAR( boolean, AUTOMATIC, DEM_APPL_DATA ) JudgeResultPtr
);

#endif  /*   ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )      */

#endif /* DEM_IUMPR_SUPPORT -STD_ON- */

/*--------------------------------------*/
/*  Dem_If_MOBD                         */
/*--------------------------------------*/
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetSpecificEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, DEM_APPL_DATA ) SpecificConditionPtr
);
#endif /* DEM_SPECIFIC_EVENT_SUPPORT -STD_ON- */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetCurrentFailedCylinder
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, DEM_APPL_DATA ) CylinderPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetFailedCylinderAtThisOC
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, DEM_APPL_DATA ) CylinderPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetFailedCylinderSinceLastClear
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, DEM_APPL_DATA ) CylinderPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetFailedCylinder
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, DEM_APPL_DATA ) CylinderPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetExceedanceUsedForMisfireEmission
(
    VAR( boolean, AUTOMATIC ) ExceedanceUsedStatus
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetCylinderDTCStatus
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA ) UDSStatusBytePtr
);
#endif /* DEM_MISFIRE_EVENT_CONFIGURED -STD_ON- */
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetPendingClearCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PendingClearCounterPtr
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetSimilarCondition
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( Dem_SimilarConditionValueType, AUTOMATIC, DEM_APPL_DATA ) SimilarConditionArrayPtr,
    P2VAR( Dem_SimilarConditionStatusType, AUTOMATIC, DEM_APPL_DATA ) SimilarConditionStatusPtr
);
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetExceedanceCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ExceedanceCounterPtr
);
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )   */


/*--------------------------------------*/
/*  Dem_If_WWHOBD                       */
/*--------------------------------------*/
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( Std_ReturnType, DEM_CODE ) Dem_SetMILAtShortMI
(
    VAR( boolean, AUTOMATIC ) MILStatus
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetB1Counter
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) B1Counter
);
FUNC( Std_ReturnType, DEM_CODE ) Dem_GetB1CounterByEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,    /* port defined argument */
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) B1CounterPtr
);


#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_FUNCTYPES_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
