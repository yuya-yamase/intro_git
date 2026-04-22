/* Dem_Pm_Misfire_h(v5-9-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_Misfire_h/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PM_MISFIRE_H
#define DEM_PM_MISFIRE_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"
#include "Dem_Pm_Control.h"
#include "Dem_Pm_DataCtl.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions(PreInit section)                                      */
/****************************************************************************/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE_TRUST ) Dem_Misfire_PreInit        /*  PreInit section     */
( void );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )     */

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*----------------------------------*/
/*  Dem_Misfire                     */
/*----------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_Init
( void );
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_Init_AfterRecordCheckComplete
( void );
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */
FUNC( void, DEM_CODE ) Dem_Misfire_InitTmpEventMemoryEntry
( void );
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_MergeWIRBitAtIndicatorBlinking_CAT
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusPtr
);
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_CheckReachedExcessCntThresholdFromTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Misfire_UpdateCylinderInfo
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_EventQualificationType, AUTOMATIC ) EventQualification,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);
FUNC( void, DEM_CODE ) Dem_Misfire_LatchCylinderStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Misfire_JudgeCylinderStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Misfire_SetExceedanceUsedForMisfireEmission
(
    VAR( boolean, AUTOMATIC ) ExceedanceUsedStatus
);
FUNC( boolean, DEM_CODE ) Dem_Misfire_GetExceedanceUsedForMisfireEmission
( void );

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_UpdateObdFFDInfo
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )     */
FUNC( void, DEM_CODE ) Dem_Misfire_UpdateFFDInfo
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_Misfire_GetPendingStoreOfEmission
( void );

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_CheckConfirmedFaultOfCAT
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */

#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_SetObdRecordNumberIndexSyncStatus
(
    VAR( boolean, AUTOMATIC ) ObdRecordNumberIndexSyncStatus
);
FUNC( boolean, DEM_CODE ) Dem_Misfire_GetObdRecordNumberIndexSyncStatus
( void );
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */
#endif  /* ( DEM_OBDONUDS_SUPPORT == STD_ON )                 */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_Misfire_JudgeClearableObdFreezeFrame
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )                 */

#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */

/*----------------------------------*/
/*  Dem_Misfire_GetCylinder         */
/*----------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetCurrentFailedCylinder
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, AUTOMATIC ) CylinderPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetFailedCylinderAtThisOC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, AUTOMATIC ) CylinderPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetFailedCylinderSinceLastClear
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, AUTOMATIC ) CylinderPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetFailedCylinder
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, AUTOMATIC ) CylinderPtr
);
FUNC( Dem_UdsStatusByteType, DEM_CODE ) Dem_Misfire_GetCylinderDTCStatus
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNum
);
FUNC( void, DEM_CODE ) Dem_Misfire_SetFilteredDTCForCylinderForEDR
(
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
);
#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_SetFilteredDTCForCylinderForReadiness
( void );
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetNextFilterdDTCForCylinder
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);

/*----------------------------------*/
/*  Dem_Misfire_MIL                 */
/*----------------------------------*/
FUNC( Dem_u08_MisfireIndStatusType, DEM_CODE ) Dem_Misfire_GetMILStatus
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind
);

/*----------------------------------*/
/*  Dem_Misfire_local               */
/*----------------------------------*/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit6Cylinder
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind
);

#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/*----------------------------------*/
/*  Dem_Misfire_FilDTC              */
/*----------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/* SID19-02,SID19-42 related */
FUNC( void, DEM_CODE ) Dem_Misfire_SetFilteredDTC
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( Dem_DTCKindType, AUTOMATIC ) DTCKind,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetFilteredUdsDTCAndSeverity
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
);
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetFilteredEdsDTC
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr
);
#endif  /*   ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )        */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetFilteredUdsDTCAndSeverity_AtEmiRelDTC
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
);
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )     */

/*----------------------------------*/
/*  Dem_Misfire_FilRecord           */
/*----------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/* SID19-03 */
FUNC( void, DEM_CODE ) Dem_Misfire_PrepareFilteredRecord
( void );

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_OFF )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_Misfire_CheckOutputFilteredObdFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger,
    P2VAR( Dem_MisfireCylinderNumberType, AUTOMATIC, AUTOMATIC ) MisfireCylinderNumberOutputPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )     */
FUNC( boolean, DEM_CODE ) Dem_Misfire_CheckOutputFilteredFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger,
    P2VAR( Dem_MisfireCylinderNumberType, AUTOMATIC, AUTOMATIC ) MisfireCylinderNumberOutputPtr
);
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_OFF ) */

#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */


/*----------------------------------*/
/*  Dem_Misfire_StoredFFDInfo       */
/*----------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_Misfire_CheckOutputOBDFFDConditionByTrigger
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */
FUNC( boolean, DEM_CODE ) Dem_Misfire_CheckOutputFFDConditionByTrigger
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger,
    P2VAR( Dem_MisfireCylinderNumberType, AUTOMATIC, AUTOMATIC ) MisfireCylinderNumberTypePtr
);
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */


/*----------------------------------*/
/*  MIL related                     */
/*----------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )
FUNC( void, DEM_CODE )  Dem_Misfire_GetIndStatusByEventStrgIndex_CAT
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_IndicatorStatusType, AUTOMATIC, AUTOMATIC ) IndicatorStatusPtr
);
#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_OFF )   */
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */

#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */


/*----------------------------------*/
/*  Dem_Misfire_SID0x01             */
/*----------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#if ( DEM_WWH_OBD_SUPPORT == STD_OFF )
/* SID01 */
FUNC( void, DEM_CODE ) Dem_Misfire_GetNumOfConfirmedCylAndMIL
(
    P2VAR( Dem_MisfireCylinderNumberType, AUTOMATIC, AUTOMATIC ) DTCNumPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) MILStatusPtr
);
#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_OFF )                 */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

/*----------------------------------*/
/*  Dem_Misfire_SID0x02             */
/*----------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
/* SID02 */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetEdsDTCOfOBDFreezeFrame
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr
);
#endif  /*   ( DEM_OBDONEDS_SUPPORT == STD_ON )                 */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

/*----------------------------------*/
/*  Dem_Misfire_EventEntry          */
/*----------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_CheckSetEventCylinder
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    CONST( Dem_MisfireCylinderType, DEM_APPL_DATA ) MisfireCylinder
);
FUNC( void, DEM_CODE ) Dem_Misfire_ExtractAvailableCylinder
(
    P2VAR( Dem_MisfireCylinderType, AUTOMATIC, AUTOMATIC ) MisfireCylinderPtr
);
FUNC( void, DEM_CODE ) Dem_Misfire_SaveEventMemoryEntryToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Misfire_UpdateEventMemoryEntryFromTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( boolean, AUTOMATIC ) ConsistencyIdUpdateFlg,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);
FUNC( void, DEM_CODE ) Dem_Misfire_ClearMisfireInfoOfEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/*--------------------------------------*/
/*  Dem_Misfire_EventEntryMake          */
/*--------------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_GetExceedanceCounterToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_MisfExceedanceCounterType, AUTOMATIC, AUTOMATIC ) ExceedanceCounterPtr
);

#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_GetFirstAccumConfirmedCylToTmp
(
    P2VAR( Dem_MisfireCylinderType, AUTOMATIC, AUTOMATIC ) FirstAccumConfirmedCylPtr
);
FUNC( void, DEM_CODE ) Dem_Misfire_GetAccumConfirmedCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_MisfireCylinderType, AUTOMATIC, AUTOMATIC ) AccumConfirmedCylPtr
);
#endif /* ( DEM_PFC_SUPPORT == STD_ON ) */

FUNC( void, DEM_CODE ) Dem_Misfire_RestoreCylinderToTmp_OnOverflow
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */

/*--------------------------------------*/
/*  Dem_Misfire_EventEntryCompare       */
/*--------------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_CompareMisfireInfoToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Misfire_InitCompareResultMisfireRecord
( void );
FUNC( void, DEM_CODE ) Dem_Misfire_InitCompareResultMisfireComRecord
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetCompareResult
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */

/*--------------------------------------------------------------------------*/
/* Dem_Misfire_OpCycle                                                      */
/*--------------------------------------------------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_ChkSpCondToOpCycUpdateQualified
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_ChkSpCondType, AUTOMATIC, AUTOMATIC ) ChkSpCondPtr
);
FUNC( void, DEM_CODE ) Dem_Misfire_ClearTmpByCycleStart
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatus,
    P2CONST( Dem_ChkBitDTCStatusType, AUTOMATIC, AUTOMATIC ) ChkOldBitStatusPtr
);
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_ClearDataRelatedAllObdFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Misfire_ClearDataRelatedObdFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

FUNC( void, DEM_CODE ) Dem_Misfire_ClearDataRelatedAllFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Misfire_ClearDataRelatedFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger
);

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_ProcessPendingFaultRecovery
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
);
FUNC( void, DEM_CODE ) Dem_Misfire_ProcessForEventFailed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_ChkBitDTCStatusType, AUTOMATIC, AUTOMATIC ) ChkOldBitStatusPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
);
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */

#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */

/*--------------------------------------------------------------------------*/
/* Dem_Misfire_PFC                                                          */
/*--------------------------------------------------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_UpdatePermanentMemoryEntryToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

FUNC( void, DEM_CODE ) Dem_Misfire_SavePermanentMemoryEntryToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

FUNC( void, DEM_CODE ) Dem_Misfire_ClearTmpPermanentMemoryEntry
( void );

FUNC( void, DEM_CODE ) Dem_Misfire_UpdatePermanentCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);

FUNC( void, DEM_CODE ) Dem_Misfire_ClearPermanentCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

FUNC( void, DEM_CODE ) Dem_Misfire_UpdatePermanentCylByOrder
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Misfire_UpdateAccumPermanentCylToTmp
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
);

FUNC( void, DEM_CODE ) Dem_Misfire_GetPermanentUDSDTC
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) PermanentDTCBufferPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) PermanentDTCNumPtr
);
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_GetPermanentOBDDTC
(
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) PermanentDTCBufferPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) PermanentDTCNumPtr
);
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )     */

#if ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_SetFilteredDTCForPFC
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetFilteredPFC
(
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
#endif /* ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON ) */

#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */


/*--------------------------------------------------------------------------*/
/* Dem_Misfire_StoredData                                                   */
/*--------------------------------------------------------------------------*/
#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_InitOutputStoredData
( void );
FUNC( boolean, DEM_CODE ) Dem_Misfire_CheckOutputStoredData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Misfire_CompletedOutputStoredData
( void );
FUNC( void, DEM_CODE ) Dem_Misfire_GetDTCAndStatusOfStoredData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */


/*--------------------------------------------------------------------------*/
/* Dem_Misfire_ConfirmedOrderCylinder                                       */
/*--------------------------------------------------------------------------*/
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_ClearConfirmedOrderCylListToTmp
( void );
FUNC( void, DEM_CODE ) Dem_Misfire_SetConfirmedOrderCylinder
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetConfirmedUDSDTCAndOrder
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireConfirmedOrderIndex,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) ConfirmedDTCPtr,
    P2VAR( Dem_u16_OccrOrderType, AUTOMATIC, AUTOMATIC ) ConfirmedOccurrenceOrderPtr
);
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_PM_MISFIRE_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
