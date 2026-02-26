/* Dem_Pm_Similar_h(v5-3-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Dem_Similar/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PM_SIMILAR_H
#define DEM_PM_SIMILAR_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"
#include "./Dem_Pm_Control.h"

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*----------------------------------*/
/*  Dem_Similar                     */
/*----------------------------------*/
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Similar_CheckPassedCondition
(
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Similar_CheckReachedExcessCntThresholdFromTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( boolean, DEM_CODE ) Dem_Similar_CheckExceedanceUsed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

/*----------------------------------*/
/*  Dem_Similar_EventEntry          */
/*----------------------------------*/
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Similar_SaveEventMemoryEntryToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Similar_UpdateEventMemoryEntryFromTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( boolean, AUTOMATIC ) ConsistencyIdUpdateFlg,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);
FUNC( void, DEM_CODE ) Dem_Similar_ClearSimilarRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Similar_SetConsistencyId
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

/*--------------------------------------*/
/*  Dem_Similar_EventEntryMake          */
/*--------------------------------------*/
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Similar_ClearPendingEraseCycCntOfTmp
( void );
FUNC( void, DEM_CODE ) Dem_Similar_SetConditionLatchedToTmp
(
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr
);
FUNC( void, DEM_CODE ) Dem_Similar_JudgeCondition
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfChkSpecificfaultPtr
);
FUNC( void, DEM_CODE ) Dem_Similar_GetConditionStoredflgToTmp
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) SimilarConditionStoredflgPtr
);
FUNC( void, DEM_CODE ) Dem_Similar_GetConditionStoreBeforeDcyToTmp
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) SimilarConditionStoreBeforeDcyPtr
);
FUNC( void, DEM_CODE ) Dem_Similar_GetExceedanceCounterToTmp
(
    P2VAR( Dem_u08_SimilarExceedanceCounterType, AUTOMATIC, AUTOMATIC ) ExceedanceCounterPtr
);

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Similar_ReachedExcessCntThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfChkSpecificfaultPtr
);
FUNC( void, DEM_CODE ) Dem_Similar_NotReachedExcessCntThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr
);
FUNC( void, DEM_CODE ) Dem_Similar_ConditionStoredPending
(
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr
);
FUNC( void, DEM_CODE ) Dem_Similar_ConditionStoredFirstExceedance
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr
);
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   */

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Similar_JudgeConditionWithCheckStored
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfChkSpecificfaultPtr
);
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */

#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )       */

/*--------------------------------------*/
/*  Dem_Similar_EventEntryCompare       */
/*--------------------------------------*/
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Similar_InitCompareResult
( void );
FUNC( void, DEM_CODE ) Dem_Similar_CompareSimilarInfoToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Similar_GetCompareResult
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )       */

/*--------------------------------------------------------------------------*/
/* Dem_Similar_OpCycle                                                      */
/*--------------------------------------------------------------------------*/
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
FUNC( boolean, DEM_CODE) Dem_Similar_CheckSimilarPassedThisDCYFromTmp
( void );
FUNC( void, DEM_CODE) Dem_Similar_PreProccessByCycleStart
( void );
FUNC( void, DEM_CODE) Dem_Similar_ProcessForEventFailed
(
    P2CONST( Dem_ChkBitDTCStatusType, AUTOMATIC, AUTOMATIC ) ChkBitStatusOldPtr
);
FUNC( boolean, DEM_CODE) Dem_Similar_CheckReachedPendingEraseCycCntThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Similar_ClearTmpByCycleStart
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewStatus
);
FUNC( void, DEM_CODE ) Dem_Similar_ChkSpCondToOpCycUpdateQualified
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_ChkSpCondType, AUTOMATIC, AUTOMATIC ) ChkSpCondPtr
);
FUNC( boolean, DEM_CODE) Dem_Similar_CheckPendingRecoveryPossible
(void);
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



#endif /* DEM_PM_SIMILAR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
