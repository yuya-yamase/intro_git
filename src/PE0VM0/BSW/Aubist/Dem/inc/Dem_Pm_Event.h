/* Dem_Pm_Event_h(v5-3-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Pm_Event/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PM_EVENT_H
#define DEM_PM_EVENT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

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

FUNC( void, DEM_CODE_TRUST ) Dem_Event_PreInitEventFailureCycleCounterThreshold   /*  PreInit section     */
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
/*  Dem_Event_QualificationInfo     */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Event_InitQualification
( void );
FUNC( boolean, DEM_CODE ) Dem_Event_SetQualificationInfo
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2VAR( Dem_u08_EventQualificationType, AUTOMATIC, AUTOMATIC ) EventQualificationPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IsPassedToPassedPtr
);

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( boolean, DEM_CODE ) Dem_Event_SetQualificationInfo_Specific
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2VAR( Dem_u08_EventQualificationType, AUTOMATIC, AUTOMATIC ) EventQualificationPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IsPassedToPassedPtr
);
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )     */

FUNC( void, DEM_CODE ) Dem_Event_ClearTargetQualificationInfo_NotTestedInCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
FUNC( void, DEM_CODE ) Dem_Event_ClearTargetQualificationInfoAtOpCycUpd_NotTestedInCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u08_OpcycUpdateFailureCycleType, AUTOMATIC ) FailureCycleFlag
);

FUNC( void, DEM_CODE ) Dem_Event_ClearFailedQualificationInfo_NotTestedInCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
FUNC( void, DEM_CODE ) Dem_Event_ClearFailedQualificationInfo_nochange
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
FUNC( void, DEM_CODE ) Dem_Event_ClearAndPassedQualificationInfo_TestedInCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
FUNC( void, DEM_CODE ) Dem_Event_ClearQualificationInfo_NotTestedInCycle_InEvtStrg
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Event_ClearQualificationInfo_nochange_InEvtStrg
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /*   ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )   */

/*----------------------------------*/
/*  Dem_Event_FCThreshold           */
/*----------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Event_SetEventFailureCycleCounterThreshold
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u08_FailureCounterType, AUTOMATIC ) FailureCycleCounterThreshold
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Event_ResetEventFailureCycleCounterThreshold
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
FUNC( Dem_u08_FailureCounterType, DEM_CODE ) Dem_Event_GetEventFailureCycleCounterThreshold
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )                EventStrgIndex
);



#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



#endif /* DEM_PM_EVENT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
