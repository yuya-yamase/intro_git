/* Dem_CmnLib_ConfigInfo_h(v5-5-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/CmnLib_ConfigInfo/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_CMNLIB_CONFIGINFO_H
#define DEM_CMNLIB_CONFIGINFO_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../cfg/Dem_Data_Cfg.h"
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes - PreInit section                                    */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>
FUNC( Dem_u08_FailureCounterType, DEM_CODE_TRUST ) Dem_CfgInfoPm_GetFCThreshold
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE_TRUST ) Dem_CfgInfoPm_GetEventAvailable
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
#endif /* DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON */

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE_TRUST ) Dem_CfgInfoUdm_GetEventAvailable
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);
#endif /* DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON */

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*----------------------------------*/
/*  General                         */
/*----------------------------------*/
FUNC( Dem_DTCTranslationFormatType, DEM_CODE ) Dem_CfgInfo_GetTranslationType
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_JudgeAgingRequire
(
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) DTCStatusStPtr,
    VAR( Dem_u08_OpcycUpdateHealingAgingCycleType, AUTOMATIC ) HealingAgingCycleFlag,   /* MISRA DEVIATION */
    VAR( boolean, AUTOMATIC ) PendingRecoveryExecFlag                                   /* MISRA DEVIATION */
);

/*----------------------------------*/
/*  Common : DTC Format             */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_CheckClearParameter
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_CheckDTCSettingParameter
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfo_CheckDTCReadDTCParameter
(
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
FUNC( boolean, DEM_CODE ) Dem_CfgInfo_CheckTrigger
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TargetTrigger,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) TriggerFromCaller
);
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_CfgInfo_CheckObdTrigger
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TargetTrigger,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) TriggerFromCaller,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) UpdatePendingFFDPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

/*----------------------------------*/
/*  CommonMemory                    */
/*----------------------------------*/
FUNC( Dem_EventIdType, DEM_CODE ) Dem_CfgInfoCmn_CnvEventCtrlIndexToEventId
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);

FUNC( Dem_u16_EventPosType, DEM_CODE ) Dem_CfgInfoCmn_GetMaxNumberOfAllMemoryEvent
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoCmn_CnvEventIdToEventCtrlIndex
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC, AUTOMATIC ) EventCtrlIndexPtr
);

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( Dem_u08_MemoryKindType, DEM_CODE ) Dem_CfgInfoCmn_CheckMemoryTypeFromEventCtrlIndex
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE ) Dem_CfgInfoCmn_CnvEventPosToEventCtrlIndex
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos
);
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

FUNC( Dem_u08_OpCycleIndexType, DEM_CODE ) Dem_CfgInfoCmn_GetEventOperationCycleRef
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos
);

FUNC( Dem_u08_OpCycleIndexType, DEM_CODE ) Dem_CfgInfoCmn_GetEventHealingAgingCycleRef
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoCmn_GetDTCStatusAvailabilityMask
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusMaskPtr,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
FUNC( void, DEM_CODE ) Dem_CfgInfoCmm_GetExDataClassRef
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_u16_ExDataClassIndexType, AUTOMATIC, AUTOMATIC ) ExDataClassRefPtr,
    P2VAR( Dem_u16_ExDataClassIndexType, AUTOMATIC, AUTOMATIC ) ExDataClassMaxNumPtr
);

/*----------------------------------*/
/*  PrimaryMemory                   */
/*----------------------------------*/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_GetMaxNumberOfOBDEvent
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_CnvEventIdToEventCtrlIndex
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC, AUTOMATIC ) EventCtrlIndexPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_CnvEventCtrlIndexToEventId
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_CnvEventStrgIndexToEventId
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);

FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetDTCStatusAvailabilityMask
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusMaskPtr
);
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetDTCSeverityAvailabilityMask
(
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityMaskPtr
);

FUNC( Dem_u08_OpCycleIndexType, DEM_CODE ) Dem_CfgInfoPm_GetEventOperationCycleRef
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);

FUNC( Dem_u08_OpCycleIndexType, DEM_CODE ) Dem_CfgInfoPm_GetEventHealingAgingCycleRef
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);

FUNC( Dem_DTCSeverityType, DEM_CODE ) Dem_CfgInfoPm_GetDTCSeverityClass
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetPreFFSupported_ByEvtCtrlIdx
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetPreFFSupported_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif /* DEM_FF_PRESTORAGE_SUPPORT == STD_ON */

FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ClearAllowed_ByEvtCtrlIdx
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ClearAllowed_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

FUNC( void, DEM_CODE ) Dem_CfgInfoPm_TriggerInitMForEFnc
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_InitMonitorReasonType, AUTOMATIC ) InitMonitorReason,
    P2VAR( Std_ReturnType, AUTOMATIC, AUTOMATIC ) ResultOfCallbackPtr
);

FUNC( void, DEM_CODE ) Dem_CfgInfoPm_TriggerEventStatusChangedFnc
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatus
);

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC_P2CONST( AB_83_ConstV Dem_DTCAttributeType, DEM_CONFIG_DATA, DEM_CODE ) Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )
FUNC_P2CONST( AB_83_ConstV Dem_DTCAttributeType, DEM_CONFIG_DATA, DEM_CODE ) Dem_CfgInfoPm_GetDTCAttrTablePtr_PreFF
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /*   ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )    */

/*----------------------------------*/
/*  PrimaryMemory:Similar           */
/*----------------------------------*/
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_CnvEventStrgIndexToSimilarStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC, AUTOMATIC ) SimilarStrgIndexPtr
);
#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_CnvSimilarStrgIndexToEventStrgIndex
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex
);
#endif  /*   ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )   */
#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_OFF )
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_CnvSimilarStrgIndexToEventStrgIndex
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex
);
#endif  /*   ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )      */
#endif  /*   ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_OFF )   */
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )     */

/*----------------------------------*/
/*  PrimaryMemory:Misfire           */
/*----------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC, AUTOMATIC ) MisfireStrgIndexPtr
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_CnvMisfireStrgIndexToEventStrgIndex
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireStrgIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
);
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_GetNextEventStrgIndexAfterEventStrgIndexOfMisfire
( void );
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_GetEventStrgIndex_MisfireEmission
( void );
FUNC( Dem_u16_MisfireStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireEmission
( void );
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_GetEventStrgIndex_MisfireCAT
( void );
FUNC( Dem_u16_MisfireStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_GetMisfireStrgIndex_MisfireCAT
( void );
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) MisfirePairEventStrgIndexPtr
);
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( Dem_EventKindType, DEM_CODE ) Dem_CfgInfoPm_GetEventKindOfMisfire_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( Dem_u08_MisfireObdFFDCylIndexType, DEM_CODE ) Dem_CfgInfoPm_GetObdFFDCylIndexOfMisfire
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
FUNC( Dem_u08_MisfireFFDCylIndexType, DEM_CODE ) Dem_CfgInfoPm_GetFFDCylIndexOfMisfire
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger
);
#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckMisfireEventFirstIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckMisfireEventLastIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif /* ( DEM_ALTIUMPR_SUPPORT == STD_ON ) */
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_CfgInfoPm_MergeMultipleCylinderBit
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_CfgInfoPm_GetMisfireLowestCylinderBitFromCylBit
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);
FUNC( Dem_MisfireCylinderNumberType, DEM_CODE ) Dem_CfgInfoPm_GetMisfireCylinderNumberFromCylBit
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);
FUNC( Dem_MisfireCylinderNumberType, DEM_CODE ) Dem_CfgInfoPm_GetMisfireCylinderNumberByUdsDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue
);
FUNC( Dem_u32_DTCValueType, DEM_CODE ) Dem_CfgInfoPm_GetUdsDTCByMisfireCylinderNumber
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber
);
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
FUNC( Dem_u32_DTCValueType, DEM_CODE ) Dem_CfgInfoPm_GetOBDDTCByMisfireCylinderNumber
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber
);
#endif  /*   ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )       */
FUNC( Dem_u08_MisfireKindType, DEM_CODE ) Dem_CfgInfoPm_GetMisfireType_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/*----------------------------------*/
/*  PrimaryMemory.DTCAttribute      */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetFreezeFrameAndRecNumClass
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) FFClassIndexPtr,
    P2VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC, AUTOMATIC ) FFRecNumClassIndexPtr
);
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetNumOfFreezeFrameRecordClass
(
    P2VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC, AUTOMATIC ) FFRClassConfigureNumPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) FFRClassPerDTCMaxNumPtr
);
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClassForClear
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) ObdFFClassIndexPtr,
    P2VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC, AUTOMATIC ) ObdFFRecNumClassIndexPtr
);
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetOBDFreezeFrameAndRecNumClass
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) ObdFFClassIndexPtr,
    P2VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC, AUTOMATIC ) ObdFFRecNumClassIndexPtr
);
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetNumOfOBDFreezeFrameRecordClass
(
    P2VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC, AUTOMATIC ) FFRClassConfigureNumPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) OBDFFRClassPerDTCMaxNumPtr
);

#endif  /*  ( DEM_OBDFFD_SUPPORT == STD_ON )   */

FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetExDataClassRef
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_u16_ExDataClassIndexType, AUTOMATIC, AUTOMATIC ) ExDataClassRefPtr
);

/*----------------------------------*/
/*  PrimaryMemory.DTCFormat         */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPm_CheckDTCFormat
(
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat
);

/*----------------------------------*/
/*  PrimaryMemory.Calibration       */
/*----------------------------------*/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetEventKindOfOBD_ByEvtCtrlIdx
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCClassPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IsMILIndicatorPtr
);
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckEventKindOfSpecific_ByEvtCtrlIdx
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckEventKindOfSpecific_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )   */

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( Dem_EventKindType, DEM_CODE ) Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )      */

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
FUNC( Dem_u08_EventPriorityType, DEM_CODE ) Dem_CfgInfoPm_GetEventPriority
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF )
#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
FUNC( Dem_u08_EventPriorityType, DEM_CODE ) Dem_CfgInfoPm_GetEventPriority
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON )                */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF ) */

FUNC( Dem_u32_DTCValueType, DEM_CODE ) Dem_CfgInfoPm_GetUdsDTCValue
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
FUNC( Dem_u16_ObdDTCValueType, DEM_CODE ) Dem_CfgInfoPm_GetObdDTCValue
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /*  ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )   */

FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetFCThresholdAdaptable
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetIsMILIndicator
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetIsWIRIndicator
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetIsActiveFault
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#if ( DEM_INDICATOR_USE == STD_ON )
FUNC( Dem_u08_HealingCounterType, DEM_CODE ) Dem_CfgInfoPm_GetHealingThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_INDICATOR_USE == STD_ON )    */
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetAgingAllowed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

FUNC( Dem_u08_AgingCounterType, DEM_CODE ) Dem_CfgInfoPm_GetAgingCycleThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( Dem_u16_WWHOBDTimeAgingCounterType, DEM_CODE ) Dem_CfgInfoPm_GetTimeAgingCounterThreshold
( void );
FUNC( void, DEM_CODE ) Dem_CfgInfoPm_GetB1CounterThresholdAndHold
(
    P2VAR( Dem_u32_B1CounterType, AUTOMATIC, AUTOMATIC ) B1ThresholdPtr,
    P2VAR( Dem_u32_B1CounterType, AUTOMATIC, AUTOMATIC ) B1HoldPtr
);
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetPFCClearPattern
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )  */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
FUNC( Dem_u08_SimilarPendingClearCounterType, DEM_CODE) Dem_CfgInfoPm_GetPendingClearCntThreshold
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex
);
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_GetIUMPROutputNecessary
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
#endif  /* ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )    */
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )  */

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE ) Dem_CfgInfoPm_GetEventNumberOfReadinessGroup
(
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType,
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )    ReadinessGroupIndex
);

FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE ) Dem_CfgInfoPm_GetEventCtrlIndexOfReadinessGroup
(
    VAR( Dem_u08_ReadinessDataPositionIndexType, AUTOMATIC )    CalcType,
    VAR( Dem_u08_ReadinessGroupIndexType, AUTOMATIC )    ReadinessGroupIndex,
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )    EventListIndex
);
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON ) */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_JudgeOutputPendingOBDFFDWithoutCDTC
( void );
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_GetEventNumberOfSameDTCGroup
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_CfgInfoPm_GetNextEventStrgIndexOfSameDTCGroup
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_CheckDelegateEventStrgIndexInSameDTCGroup
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */

/*----------------------------------*/
/*  PrimaryMemory:MI                */
/*----------------------------------*/
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ChkDTCCls_MILONAtConfirmed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ChkDTCCls_WIRbitONAtConfirmed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#if ( DEM_INDICATOR_USE == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ChkDTCCls_WIRbitOFFAtHealing
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_INDICATOR_USE == STD_ON )  */
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ChkDTCCls_AFACBitONAtCycUpd
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ChkDTCCls_UseB1Counter
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */
#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ChkDTCCls_HasContinuousMI
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */
#if ( DEM_PFC_SUPPORT == STD_OFF )
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ChkDTCCls_HasContinuousMI
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */
#endif  /* ( DEM_PFC_SUPPORT == STD_OFF )    */
#if ( DEM_OBD_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_CfgInfoPm_ChkDTCCls_HasMILInd
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */
#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( Dem_u32_B1CounterType, DEM_CODE ) Dem_CfgInfoPm_GetB1CounterThreshold
( void );
FUNC( Dem_u32_B1CounterType, DEM_CODE ) Dem_CfgInfoPm_GetB1CounterHold
( void );
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */

/*----------------------------------*/
/*  PermanentMemory                 */
/*----------------------------------*/
#if ( DEM_OBD_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoPermanentM_CheckDTCOriginAndFormat
(
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat
);
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

/*----------------------------------*/
/*  UserDefinedMemory               */
/*----------------------------------*/
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) UdmEventIndexPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoUdm_CnvEventPosToUdmEventIndex
(
    VAR( Dem_u16_EventPosType, AUTOMATIC ) EventPos,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) UdmEventIndexPtr
);
FUNC( Dem_u16_EventCtrlIndexType, DEM_CODE ) Dem_CfgInfoUdm_CnvUdmEventIndexToEventCtrlIndex
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoUdm_CnvUdmEventIndexToEventId
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
FUNC( Dem_u16_UdmEventStrgIndexType, DEM_CODE ) Dem_CfgInfoUdm_CnvUdmEventIndexToUdmEventStrgIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);
FUNC( Dem_u16_UdmEventIndexType, DEM_CODE ) Dem_CfgInfoUdm_CnvUdmEventStrgIndexToUdmEventIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) UdmStrgEventIndex
);

FUNC( Dem_u16_UdmEventIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetStartUdmEventIndex_InMemory
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);
FUNC( Dem_u16_UdmEventIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetConfigureNumOfUdmEventIndex_InMemory
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoUdm_GetDTCStatusAvailabilityMask_ByDTCOrigin
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusMaskPtr,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_CfgInfoUdm_GetDTCStatusAvailabilityMask
(
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInfoTableIndex
);

FUNC( Dem_u08_OpCycleIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetEventOperationCycleRef
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);
FUNC( Dem_u08_UdmFaultIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetMaxNumberOfEventEntry
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);
FUNC( Dem_u16_UdmFFDIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetMaxNumberOfFreezeFramePerDTC
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);

FUNC( uint8, DEM_CODE ) Dem_CfgInfoUdm_GetUserDefinedMemoryIdentifier
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);
FUNC( Dem_u08_UserDefinedMemoryType, DEM_CODE ) Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByUdmEventIndex
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);
FUNC( Dem_u08_UserDefinedMemoryType, DEM_CODE ) Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByMemKind
(
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInfoTableIndex
);
FUNC( Dem_u08_UserDefinedMemoryType, DEM_CODE ) Dem_CfgInfoUdm_GetUserDefinedMemoryTypeByDTCOrigin
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC, AUTOMATIC ) UdmInfoTableIndexPtr
);
FUNC( Dem_u08_EventDisplacementStrategyType, DEM_CODE ) Dem_CfgInfoUdm_GetEventDisplacementStrategy
(
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInfoTableIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);
FUNC( void, DEM_CODE ) Dem_CfgInfoUdm_TriggerInitMForEFnc
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_InitMonitorReasonType, AUTOMATIC ) InitMonitorReason,
    P2VAR( Std_ReturnType, AUTOMATIC, AUTOMATIC ) ResultOfCallbackPtr
);
FUNC( void, DEM_CODE ) Dem_CfgInfoUdm_TriggerEventStatusChangedFnc
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatus
);

FUNC( void, DEM_CODE ) Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndex
(
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInfoTableIndex,
    P2VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC, AUTOMATIC ) UdmGroupKindIndexStartPtr,
    P2VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC, AUTOMATIC ) UdmGroupKindIndexNumPtr
);

FUNC( Dem_u16_UdmDemMemKindIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex
(
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInfoTableIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);

FUNC( Dem_u08_UserDefinedMemoryType, DEM_CODE ) Dem_CfgInfoUdm_GetDemUserDefinedMemoryInfoTableIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
);

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */


/*----------------------------------*/
/*  UserDefinedMemory.DTCAttribute  */
/*----------------------------------*/
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_CfgInfoUdm_GetFreezeFrameClassRef
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) FFClassIndexPtr
);
FUNC( Dem_u08_UdmMemoryInfoTableIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetMemoryDestination
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);
FUNC( Dem_u16_UdmFFDIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);
FUNC( void, DEM_CODE ) Dem_CfgInfoUdm_GetExDataClassRef
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2VAR( Dem_u16_ExDataClassIndexType, AUTOMATIC, AUTOMATIC ) ExDataClassRefPtr
);
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
FUNC( Dem_u16_TSFFRecClassIndexType, DEM_CODE ) Dem_CfgInfoUdm_GetTimeSeriesFreezeFrameRecordClassRef
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */


/*----------------------------------*/
/*  UserDefinedMemory.DTCFormat     */
/*----------------------------------*/
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoUdm_CnvDTCOriginToInternalInfoTableIndex
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC, AUTOMATIC ) UdmInfoTableIndexPtr
);
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoUdm_CheckClearParameter
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_CfgInfoUdm_CheckDTCOriginAndFormat
(
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

/*----------------------------------*/
/*  UserDefinedMemory.Calibration   */
/*----------------------------------*/
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( Dem_u32_DTCValueType, DEM_CODE ) Dem_CfgInfoUdm_GetUdsDTCValue
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);
FUNC( boolean, DEM_CODE ) Dem_CfgInfoUdm_GetIsWIRIndicator
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);
FUNC( Dem_u08_EventPriorityType, DEM_CODE ) Dem_CfgInfoUdm_GetEventPriority
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
);

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_CMNLIB_CONFIGINFO_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

