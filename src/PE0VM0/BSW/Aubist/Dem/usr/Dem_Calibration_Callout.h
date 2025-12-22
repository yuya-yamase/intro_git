/* Dem_Calibration_Callout_h(v5-10-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Calibration_Callout/HEADER                            */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_CALIBRATION_CALLOUT_H
#define DEM_CALIBRATION_CALLOUT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DEM_CALIB_FAILURECYCLECNT_THRESHOLD_DEF                 ((Dem_u08_FailureCounterType)1U)
#define     DEM_CALIB_HEALINGCYCLECNT_THRESHOLD_DEF                 ((Dem_u08_HealingCounterType)3U)
#define     DEM_CALIB_AGINGCYCLECNT_THRESHOLD_DEF                   ((Dem_u08_AgingCounterType)40U)
#define     DEM_CALIB_SIMPENDINGCLEARCYCLECNT_THRESHOLD_DEF         ((Dem_u08_SimilarPendingClearCounterType)80U)
#define     DEM_CALIB_TIMEAGINGCNT_THRESHOLD_DEF                    ((Dem_u16_WWHOBDTimeAgingCounterType)12000U)
#define     DEM_CALIB_B1CNT_THRESHOLD_DEF                           ((Dem_u32_B1CounterType)4000U)
#define     DEM_CALIB_B1CNT_HOLD_DEF                                ((Dem_u32_B1CounterType)3800U)

#define     DEM_CALIB_UDSDTCVALUE_MASK                  ((Dem_u32_DTCValueType)0x00FFFFFFU)
#define     DEM_CALIB_UDSDTCVALUE_DEF                   ((Dem_u32_DTCValueType)0x00000001U)
#define     DEM_CALIB_OBDDTCVALUE_DEF                   ((Dem_u16_ObdDTCValueType)0x0000U)

#define     DEM_CALIB_READINESS_EVT_ALWAYS_COMPLETE                 ((Dem_EventIdType)0x8000U)
#define     DEM_CALIB_READINESS_EVT_DUPLICATE_DTC                   ((Dem_EventIdType)0x4000U)

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions(CODE_TRUST)                                           */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT_TRUST
#include <Dem_MemMap.h>

FUNC( Dem_u08_FailureCounterType, DEM_CODE_CALLOUT_TRUST ) Dem_Calib_GetFailureCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE_CALLOUT_TRUST ) Dem_Calib_GetEventAvailable
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
#endif  /* ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )     */

#define DEM_STOP_SEC_CODE_CALLOUT_TRUST
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE_CALLOUT ) Dem_Calib_GetEventKind
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_EventKindType, AUTOMATIC, AUTOMATIC ) EventKindPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCClassPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IsMILIndicatorPtr
);
FUNC( boolean, DEM_CODE_CALLOUT ) Dem_Calib_GetIsWIRIndicator
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
FUNC( boolean, DEM_CODE_CALLOUT ) Dem_Calib_GetIsActiveFault
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);

#if ( DEM_EVENTPRIORITY_CALLOUT_SUPPORT == STD_ON )
FUNC( Dem_u08_EventPriorityType, DEM_CODE_CALLOUT ) Dem_Calib_GetEventPriority
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
#endif  /* ( DEM_EVENTPRIORITY_CALLOUT_SUPPORT == STD_ON )                */

#if ( DEM_INDICATOR_USE == STD_ON )
FUNC( Dem_u08_HealingCounterType, DEM_CODE_CALLOUT ) Dem_Calib_GetHealingCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
#endif  /* ( DEM_INDICATOR_USE == STD_ON )      */

FUNC( boolean, DEM_CODE_CALLOUT ) Dem_Calib_GetAgingAllowed
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);

FUNC( Dem_u08_AgingCounterType, DEM_CODE_CALLOUT ) Dem_Calib_GetAgingCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
FUNC( Dem_u16_WWHOBDTimeAgingCounterType, DEM_CODE_CALLOUT ) Dem_Calib_GetTimeAgingCounterThreshold
( void );
FUNC( void, DEM_CODE_CALLOUT ) Dem_Calib_GetB1CounterThresholdAndHold
(
    P2VAR( Dem_u32_B1CounterType, AUTOMATIC, AUTOMATIC ) B1ThresholdPtr,
    P2VAR( Dem_u32_B1CounterType, AUTOMATIC, AUTOMATIC ) B1HoldPtr
);
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

FUNC( Dem_u32_DTCValueType, DEM_CODE_CALLOUT ) Dem_Calib_GetUdsDTCValue
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);

#if ( DEM_OBD_SUPPORT == STD_ON )
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
FUNC( Dem_u16_ObdDTCValueType, DEM_CODE_CALLOUT ) Dem_Calib_GetObdDTCValue
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
#endif  /*  ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )   */
#endif  /*  ( DEM_OBD_SUPPORT == STD_ON )   */

#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE_CALLOUT ) Dem_Calib_GetPFCClearPattern
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )  */

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE_CALLOUT ) Dem_Calib_GetIUMPROutputNecessary
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )  */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
FUNC( Dem_u08_SimilarPendingClearCounterType, DEM_CODE_CALLOUT ) Dem_Calib_GetSimilarPendingClearCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
FUNC( uint16, DEM_CODE_CALLOUT ) Dem_Calib_GetEventNumberOfReadinessGroup
(
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) ReadinessGroupId
);

FUNC( Dem_EventIdType, DEM_CODE_CALLOUT ) Dem_Calib_GetEventIdOfReadinessGroup
(
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) ReadinessGroupId,
    VAR( uint16, AUTOMATIC ) EventNumberInReadinessGroup
);
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON ) */

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
FUNC( uint16, DEM_CODE ) Dem_Calib_GetEventNumberOfSameDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue
);
FUNC( Dem_EventIdType, DEM_CODE ) Dem_Calib_GetNextEventIdOfSameDTC
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
FUNC( boolean, DEM_CODE ) Dem_Calib_CheckDelegateEventIdOfSameDTC
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>


#endif /* DEM_CALIBRATION_BY_CALLOUT_SUPPORT -STD_ON- */

#endif /* DEM_CALIBRATION_CALLOUT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
