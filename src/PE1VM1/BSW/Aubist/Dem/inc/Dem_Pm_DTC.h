/* Dem_Pm_DTC_h(v5-10-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/Pm_DTC/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_PM_DTC_H
#define DEM_PM_DTC_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_CmnLib_DTC_DTCStatus.h"
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
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_ChangeDTCStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_EventQualificationType, AUTOMATIC ) EventQualification,
    VAR( boolean, AUTOMATIC ) ActiveFaultReqFlag,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr,
    P2VAR( Dem_OrderListOccurredFlagType, AUTOMATIC, AUTOMATIC ) OccurFlagPtr
);

FUNC( void, DEM_CODE ) Dem_DTC_TranslateDTCStatusAfterUpdate
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) OldDTCStatusPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusPtr
);
FUNC( void, DEM_CODE ) Dem_DTC_SetFilteredDTC
(
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr
);

#if ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_SearchFilteredPFC
(
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
#endif /* ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON ) */
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_SearchFilteredEdsDTC_byOrderList
(
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
#endif /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON ) */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_SearchFilteredDTCAndSeverity
(
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
);
#if ( DEM_OBD_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_SearchFilteredDTCAndSeverity_byOrderList
(
    P2CONST( Dem_SetDTCFilterType, AUTOMATIC, AUTOMATIC ) DTCFilterPtr,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
);
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )    */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusOfEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusAndUdsDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusAndUdsDTC_forFilDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( boolean, AUTOMATIC ) FilterWithSeverity,
    VAR( Dem_DTCSeverityType, AUTOMATIC ) DTCSeverityMask,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusByUdsDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_TranslateDTCStatusForOutput
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_TranslateDTCStatusForOutputByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
FUNC( void, DEM_CODE ) Dem_DTC_TranslateDTCStatusForOutput_NoMergeWIRBit
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
FUNC( void, DEM_CODE ) Dem_DTC_UpdateDTCStatusByRetentionResult
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) EventRetentionResult,
    VAR( boolean, AUTOMATIC ) ConfirmedOccurFlag,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder,
    CONSTP2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) OldDTCStatusStPtr,
    P2VAR( Dem_DTCStatusStType, AUTOMATIC, AUTOMATIC ) NewDTCStatusStPtr
);

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_SetDTCFilterForReadiness
(
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) ReadinessGroupId
);

FUNC( void, DEM_CODE ) Dem_DTC_RestartSetDTCFilterForReadiness
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetNextFilteredDTCForReadiness
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

FUNC( boolean, DEM_CODE ) Dem_DTC_JudgeDTCClearTarget
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);


#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )
/* Dem_DTC_PreFFD.c */
FUNC( boolean, DEM_CODE ) Dem_DTC_CheckRemovePrestoredFF
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatus
);
#endif  /* ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )      */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusByDTC
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetDTCStatusByDTCAndSeverity
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) TargetEventStrgIndex,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusMask,
    VAR( boolean, AUTOMATIC ) FilterWithSeverity,
    VAR( Dem_DTCSeverityType, AUTOMATIC ) DTCSeverityMask,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCSeverityPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_PM_DTC_H */

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
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
