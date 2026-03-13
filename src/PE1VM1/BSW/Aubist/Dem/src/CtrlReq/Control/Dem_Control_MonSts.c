/* Dem_Control_MonSts_c(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_MonSts/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_MonSts.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "Dem_Control_local.h"

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


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Control_GetMonitorStatus                             */
/* Description   | Get MonitorStatus                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in]  EventId                                            */
/*               | [out] MonitorStatusPtr                                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : success                               */
/*               |       DEM_IRT_NG                                         */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetMonitorStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_MonitorStatusType, AUTOMATIC, AUTOMATIC ) MonitorStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_MonitorStatusType, AUTOMATIC ) monitorStatus;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    retTempVal = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );                              /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */
    if( retTempVal == DEM_IRT_OK )
    {
        monitorStatus = Dem_MonSts_GetMonitorStatus( eventCtrlIndex );  /* [GUD] eventCtrlIndex */
        (*MonitorStatusPtr) = monitorStatus;
        retVal = DEM_IRT_OK;
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* ( DEM_TRIGGER_FIM_REPORTS == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
