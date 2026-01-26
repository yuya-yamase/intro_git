/* Dem_Pm_Control_Misfire_h(v5-5-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_Control_Misfire/HEADER                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef DEM_PM_CONTROL_MISFIRE_H
#define DEM_PM_CONTROL_MISFIRE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )

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

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetCurrentFailedCylinder
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, AUTOMATIC ) CylinderPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetFailedCylinderAtThisOC
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, AUTOMATIC ) CylinderPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetFailedCylinderSinceLastClear
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, AUTOMATIC ) CylinderPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetFailedCylinder
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_MisfireCylinderStatusType, AUTOMATIC, AUTOMATIC ) CylinderPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetCylinderDTCStatus
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) UDSStatusBytePtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

#endif /* DEM_PM_CONTROL_MISFIRE_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

