/* Dem_Calibration_Callout_c(v5-5-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Calibration_Callout/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_CALIBRATION_BY_CALLOUT_SUPPORT == STD_ON )

#include "Dem_Calibration_Callout.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

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
/****************************************************************************/
/* External Functions(CODE_TRUST)                                           */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT_TRUST
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Calib_GetFailureCycleCounterThreshold                */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :  Event Id.                               */
/* Return Value  | Dem_u08_FailureCounterType                               */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_FailureCounterType, DEM_CODE_CALLOUT_TRUST ) Dem_Calib_GetFailureCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    return DEM_CALIB_FAILURECYCLECNT_THRESHOLD_DEF;
}

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Calib_GetEventAvailable                              */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :  Event Id.                               */
/* Return Value  | boolean                                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE_CALLOUT_TRUST ) Dem_Calib_GetEventAvailable
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    return (boolean)TRUE;
}
#endif  /*   ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )       */


#define DEM_STOP_SEC_CODE_CALLOUT_TRUST
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Calib_GetEventKind                                   */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :  Event Id.                               */
/*               | [out] EventKindPtr :                                     */
/*               |        Pointer to the area to get Event Kind.            */
/*               | [out] DTCClassPtr :                                      */
/*               |        Pointer to the area to get DTC Class.             */
/*               | [out] IsMILIndicatorPtr :                                */
/*               |        Pointer to the area to get MIL flag exist.        */
/*               |        When it Event Use "MIL" Ind, TRUE is set.         */
/*               |        When it Event no Use "MIL"Ind, FALSE is set.      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_Calib_GetEventKind
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_EventKindType, AUTOMATIC, AUTOMATIC ) EventKindPtr,
    P2VAR( Dem_DTCSeverityType, AUTOMATIC, AUTOMATIC ) DTCClassPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IsMILIndicatorPtr
)
{
    *EventKindPtr        =   DEM_EVTKIND_TYPE_NON_OBD_EVENT;
    *DTCClassPtr         =   DEM_SEVERITY_NO_SEVERITY;
    *IsMILIndicatorPtr   =   (boolean)FALSE;
    return;
}

/****************************************************************************/
/* Function Name | Dem_Calib_GetIsWIRIndicator                              */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :  Event Id.                               */
/* Return Value  | boolean                                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE_CALLOUT ) Dem_Calib_GetIsWIRIndicator
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    return (boolean)FALSE;
}

/****************************************************************************/
/* Function Name | Dem_Calib_GetIsActiveFault                               */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :  Event Id.                               */
/* Return Value  | boolean                                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE_CALLOUT ) Dem_Calib_GetIsActiveFault
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    return (boolean)FALSE;
}

#if ( DEM_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Calib_GetEventPriority                               */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :  Event Id.                               */
/* Return Value  | Dem_u08_EventPriorityType                                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_EventPriorityType, DEM_CODE_CALLOUT ) Dem_Calib_GetEventPriority
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    return DEM_PRIORITY_NONOBD_DEFAULT;
}
#endif  /* ( DEM_OBD_SUPPORT == STD_ON )                */
#if ( DEM_OBD_SUPPORT == STD_OFF )
#if ( DEM_EVENT_DISPLACEMENT_CALLOUT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Calib_GetEventPriority                               */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :  Event Id.                               */
/* Return Value  | Dem_u08_EventPriorityType                                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_EventPriorityType, DEM_CODE_CALLOUT ) Dem_Calib_GetEventPriority
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    return DEM_PRIORITY_NONOBD_DEFAULT;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_CALLOUT_SUPPORT == STD_ON ) */
#endif  /* ( DEM_OBD_SUPPORT == STD_OFF )               */

#if ( DEM_INDICATOR_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Calib_GetHealingCycleCounterThreshold                */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :  Event Id.                               */
/* Return Value  | Dem_u08_HealingCounterType                               */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_HealingCounterType, DEM_CODE_CALLOUT ) Dem_Calib_GetHealingCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    return DEM_CALIB_HEALINGCYCLECNT_THRESHOLD_DEF;
}
#endif  /*   ( DEM_INDICATOR_USE == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_Calib_GetAgingAllowed                                */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :  Event Id.                               */
/* Return Value  | boolean                                                  */
/*               |                          TRUE  : allowed.                */
/*               |                          FALSE : not allowed.            */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE_CALLOUT ) Dem_Calib_GetAgingAllowed
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    return (boolean)TRUE;
}

/****************************************************************************/
/* Function Name | Dem_Calib_GetAgingCycleCounterThreshold                  */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :  Event Id.                               */
/* Return Value  | Dem_u08_AgingCounterType                                 */
/*               |        Aging cycle counter threshold.                    */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_AgingCounterType, DEM_CODE_CALLOUT ) Dem_Calib_GetAgingCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    return DEM_CALIB_AGINGCYCLECNT_THRESHOLD_DEF;
}

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Calib_GetTimeAgingCounterThreshold                   */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u16_WWHOBDTimeAgingCounterType                       */
/*               |        Time aging counter threshold.                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u16_WWHOBDTimeAgingCounterType, DEM_CODE_CALLOUT ) Dem_Calib_GetTimeAgingCounterThreshold
( void )
{
    return  DEM_CALIB_TIMEAGINGCNT_THRESHOLD_DEF;
}

/****************************************************************************/
/* Function Name | Dem_Calib_GetB1CounterThresholdAndHold                   */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [out] B1ThresholdPtr : B1 counter threshold.             */
/*               | [out] B1HoldPtr      : B1 counter Hold.                  */
/* Return Value  | void                                                     */
/* Notes         | LSB : 3minutes.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_Calib_GetB1CounterThresholdAndHold
(
    P2VAR( Dem_u32_B1CounterType, AUTOMATIC, AUTOMATIC ) B1ThresholdPtr,
    P2VAR( Dem_u32_B1CounterType, AUTOMATIC, AUTOMATIC ) B1HoldPtr
)
{
    *B1ThresholdPtr = DEM_CALIB_B1CNT_THRESHOLD_DEF;
    *B1HoldPtr      = DEM_CALIB_B1CNT_HOLD_DEF;
    return;
}


#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Calib_GetUdsDTCValue                                 */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :  Event Id.                               */
/* Return Value  | Dem_u32_DTCValueType                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u32_DTCValueType, DEM_CODE_CALLOUT ) Dem_Calib_GetUdsDTCValue
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    Dem_u32_DTCValueType    dtc;

    dtc =   DEM_CALIB_UDSDTCVALUE_DEF;

    return dtc;
}

#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Calib_GetObdDTCValue                                 */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :  Event Id.                               */
/* Return Value  | Dem_u16_ObdDTCValueType                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u16_ObdDTCValueType, DEM_CODE_CALLOUT ) Dem_Calib_GetObdDTCValue
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    Dem_u16_ObdDTCValueType dtc;

    dtc =   DEM_CALIB_OBDDTCVALUE_DEF;

    return dtc;
}
#endif  /*  ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )   */

#if ( DEM_PFC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Calib_GetPFCClearPattern                             */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :  Event Id.                               */
/* Return Value  | boolean                                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE_CALLOUT ) Dem_Calib_GetPFCClearPattern
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    return (boolean)FALSE;
}
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )  */

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Calib_GetIUMPROutputNecessary                        */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :  Event Id.                               */
/* Return Value  | boolean                                                  */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE_CALLOUT ) Dem_Calib_GetIUMPROutputNecessary
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    return (boolean)TRUE;
}
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )  */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Calib_GetSimilarPendingClearCounterThreshold         */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :  Event Id.                               */
/* Return Value  | Dem_u08_SimilarPendingClearCounterType                   */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_SimilarPendingClearCounterType, DEM_CODE_CALLOUT ) Dem_Calib_GetSimilarPendingClearCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    return DEM_CALIB_SIMPENDINGCLEARCYCLECNT_THRESHOLD_DEF;
}
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Calib_GetEventNumberOfReadinessGroup                 */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] ReadinessGroupId  :                                 */
/*               |        Readiness Group Id.                               */
/* Return Value  | uint16                                                   */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( uint16, DEM_CODE_CALLOUT ) Dem_Calib_GetEventNumberOfReadinessGroup
(
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) ReadinessGroupId
)
{
    return ( uint16 )0U;
}

/****************************************************************************/
/* Function Name | Dem_Calib_GetEventIdOfReadinessGroup                     */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] ReadinessGroupId  :                                 */
/*               |        Readiness Group Id.                               */
/*               | [in] uint16  :                                           */
/*               |        Specifies the order from the beginning in the sp- */
/*               |        ecified readiness group.                          */
/* Return Value  | Dem_EventIdType                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_EventIdType, DEM_CODE_CALLOUT ) Dem_Calib_GetEventIdOfReadinessGroup
(
    VAR( Dem_u08_ReadinessGroupIdType, AUTOMATIC ) ReadinessGroupId,
    VAR( uint16, AUTOMATIC ) EventNumberInReadinessGroup
)
{
    return DEM_EVENTID_INVALID;
}
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON ) */

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Calib_GetEventNumberOfSameDTC                        */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCValue  :                                         */
/*               |        DTCValue.                                         */
/* Return Value  | uint16                                                   */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( uint16, DEM_CODE ) Dem_Calib_GetEventNumberOfSameDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue
)
{
    return ( uint16 )1U;
}

/****************************************************************************/
/* Function Name | Dem_Calib_GetNextEventIdOfSameDTC                        */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :                                          */
/*               |        EventId.                                          */
/* Return Value  | Dem_EventIdType                                          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_EventIdType, DEM_CODE ) Dem_Calib_GetNextEventIdOfSameDTC
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    return EventId;
}

/****************************************************************************/
/* Function Name | Dem_Calib_CheckDelegateEventIdOfSameDTC                  */
/* Description   | get calibration data.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId  :                                          */
/*               |        EventId.                                          */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : it's delegate EventId.                    */
/*               |        FALSE : it's not delegate EventId.                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Calib_CheckDelegateEventIdOfSameDTC
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    return (boolean)TRUE;
}

#endif  /* ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

#endif /* DEM_CALIBRATION_BY_CALLOUT_SUPPORT -STD_ON- */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
