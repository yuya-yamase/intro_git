/* Dem_Pm_Control_Specific_h(v5-5-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_Control_Specific/HEADER                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef DEM_PM_CONTROL_SPECIFIC_H
#define DEM_PM_CONTROL_SPECIFIC_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"


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

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetSpecificEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, DEM_APPL_DATA ) SpecificConditionPtr
);
#endif /* DEM_SPECIFIC_EVENT_SUPPORT -STD_ON- */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Control_SetExceedanceUsedForMisfireEmission
(
    VAR( boolean, AUTOMATIC ) ExceedanceUsedStatus
);
#endif /* DEM_MISFIRE_EVENT_CONFIGURED -STD_ON- */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetPendingClearCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_u08_HealingCounterType, AUTOMATIC, AUTOMATIC ) PendingClearCounterPtr
);
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetExceedanceCounter
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventID,
    P2VAR( Dem_u08_ExceedanceCounterType, AUTOMATIC, AUTOMATIC ) ExceedanceCounterPtr
);
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON ) */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_PM_CONTROL_SPECIFIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
