/* Dem_Pm_Control_IUMPR_h(v5-5-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_Control_IUMPR/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef DEM_PM_CONTROL_IUMPR_H
#define DEM_PM_CONTROL_IUMPR_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetIUMPRDenCondition
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )                  ConditionId,
    P2VAR( Dem_IumprDenomCondStatusType, AUTOMATIC, AUTOMATIC ) ConditionStatusPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetIUMPRGeneralDenominator
(
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC ) GeneralDenominatorPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetIUMPRIGCycleCounter
(
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC ) IGCycleCounterPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetIUMPRDenCondition
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )      ConditionId,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  ConditionStatus
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetInfoTypeValue
(
    P2VAR( uint8 , AUTOMATIC, DEM_APPL_DATA )   IumprdataPtr,
    P2VAR( uint8 , AUTOMATIC, AUTOMATIC )       BuffSizePtr
);
#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetIUMPRDataByRatioId
(
    VAR( Dem_RatioIdType, AUTOMATIC )       RatioId,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   NumeratorPtr,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   DenominatorPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventIdByRatioId
(
    VAR( Dem_RatioIdType, AUTOMATIC )               RatioId,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC )  EventIdPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetRatioIdByEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_RatioIdType, AUTOMATIC, DEM_APPL_DATA ) RatioIdBufferPtr,
    P2VAR( Dem_RatioIdType, AUTOMATIC, AUTOMATIC ) RatioIdNumPtr
);
FUNC( boolean, DEM_CODE ) Dem_Control_JudgeMinThanCurrentRatio
(
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    CurrentNumerator,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    CurrentDenominator,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    TargetNumerator,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    TargetDenominator
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_RepIUMPRFaultDetect
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioId
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_RepIUMPRDenRelease
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioId
);
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON ) */

#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_PM_CONTROL_IUMPR_H */

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

