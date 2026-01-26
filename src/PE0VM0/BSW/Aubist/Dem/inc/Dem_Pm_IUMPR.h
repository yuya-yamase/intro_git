/* Dem_Pm_IUMPR_h(v5-5-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_IUMPR/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef Dem_PM_IUMPR_H
#define Dem_PM_IUMPR_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>


#include <Dem/Dem_Common.h>
#include "../cfg/Dem_Cfg.h"
#include "../cfg/Dem_IUMPR_Cfg.h"

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

#if ( DEM_IUMPR_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_IUMPR_Init
( void );

FUNC( void, DEM_CODE ) Dem_IUMPR_ClearIUMPRCondition
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_GetIUMPRDenCondition
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC ) ConditionId,
    P2VAR( Dem_IumprDenomCondStatusType, AUTOMATIC, AUTOMATIC ) ConditionStatusPtr
);
FUNC( void, DEM_CODE ) Dem_IUMPR_GetGeneralDenominator
(
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC ) GeneralDenominatorPtr
);

FUNC( void, DEM_CODE ) Dem_IUMPR_GetIGCycleCounter
(
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC ) IGCycleCounterPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_GetInitInfoTypeValue
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA )        IumprdataPtr,
    P2VAR( uint8 , AUTOMATIC, AUTOMATIC )           BuffSizePtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_GetInfoTypeValue
(
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA )        IumprdataPtr,
    P2VAR( uint8 , AUTOMATIC, AUTOMATIC )           BuffSizePtr
);
FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateIUMPRProcess
(
    VAR( boolean, AUTOMATIC )              FirstTime,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ProcessCompletePtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_CheckCondSettingParameter
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )      ConditionId,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  ConditionStatus
);

FUNC( void, DEM_CODE ) Dem_IUMPR_SetIUMPRDenCondition
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )      ConditionId,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  ConditionStatus
);

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateEventRelatedNumerator
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )    EventCtrlIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_GetDataByRatioId
(
    VAR( Dem_RatioIdType, AUTOMATIC )       RatioId,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   NumeratorPtr,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   DenominatorPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_GetEventIdByRatioId
(
    VAR( Dem_RatioIdType, AUTOMATIC )               RatioId,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC )  EventIdPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_GetRatioIdByEventId
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )    EventCtrlIndex,
    P2VAR( Dem_RatioIdType, AUTOMATIC, DEM_APPL_DATA ) RatioIdBufferPtr,
    P2VAR( Dem_RatioIdType, AUTOMATIC, AUTOMATIC ) RatioIdNumPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_CheckFaultDetectCondition
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioId
);

FUNC( void, DEM_CODE ) Dem_IUMPR_RepIUMPRFaultDetect
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioId
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_CheckLockReleaseCondition
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioId
);

FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateDenUnlockCondition
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioId
);
FUNC( boolean, DEM_CODE ) Dem_IUMPR_JudgeMinThanCurrentRatio
(
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    CurrentNumerator,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    CurrentDenominator,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    TargetNumerator,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    TargetDenominator
);
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON ) */

#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON ) */



#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



#endif /* Dem_Pm_IUMPR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

