/* Dem_NotifyOverwrittenEventStatus_Callout_c(v5-3-0)                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Misfire_NotifyDTCStatus_Callout/CODE                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_NotifyOverwrittenEventStatus_Callout.h"

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_NotifyOverwrittenEventStatus                         */
/* Description   | Notify overwritten Event status.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId        : Overwritten Event Id.              */
/*               | [in] DTCStatusOld   : DTC status.                        */
/*               | [in] DTCStatusNew   : DTC status.                        */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE_CALLOUT ) Dem_NotifyOverwrittenEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusOld,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusNew
)
{
    return ;
}

#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>


#endif /* ( DEM_EVENT_DISPLACEMENT_CALLOUT_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
