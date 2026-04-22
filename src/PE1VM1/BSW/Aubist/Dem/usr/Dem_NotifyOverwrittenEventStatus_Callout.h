/* Dem_NotifyOverwrittenEventStatus_Callout_h(v5-3-0)                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/NotifyOverwrittenEventStatus_Callout/HEADER           */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_NOTIFYOVRWRTTNEVENTSTATUS_CALLOUT_H
#define DEM_NOTIFYOVRWRTTNEVENTSTATUS_CALLOUT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_EVENT_DISPLACEMENT_CALLOUT_SUPPORT == STD_ON )
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
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifyOverwrittenEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusOld,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusNew
);

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


#endif /* ( DEM_EVENT_DISPLACEMENT_CALLOUT_SUPPORT == STD_ON ) */


#endif /* DEM_NOTIFYOVRWRTTNEVENTSTATUS_CALLOUT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
