/* Dem_Event_QualificationInfo_local_h(v5-9-0)                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Event_QualificationInfo_local/HEADER                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_EVENT_QUALIFICATIONINFO_LOCAL_H
#define DEM_EVENT_QUALIFICATIONINFO_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../cfg/Dem_Cfg.h"

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

#if ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Event_ClearPassedBit_InStrgGrp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_Event_SavePassedTgtBit_ByEvtCtrlIdx
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) TargetEventCtrlIndex,
    VAR( boolean, AUTOMATIC ) PassedBit
);
FUNC( void, DEM_CODE ) Dem_Event_SavePassedAllBit_fromQualification
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) TargetEventCtrlIndex
);
#endif  /* ( DEM_COMBINEDEVENT_ONSTORAGE_SUPPORT == STD_ON ) */



#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

extern VAR( Dem_u08_EventQualificationType, DEM_VAR_NO_INIT ) Dem_EventQualificationList[ DEM_PRIMEM_EVENT_NUM ];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#endif /* DEM_EVENT_QUALIFICATIONINFO_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
