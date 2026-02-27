/* Dem_Control_FCThreshold_c(v5-5-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_FCThreshold/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Event.h"
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
/* Function Name | Dem_Control_SetEventFailureCycleCounterThreshold         */
/* Description   | Sets FailureCycleCounterThreshold in RAM-Data.           */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        specific-event identifier                         */
/*               | [in] FailureCycleCounterThreshold :                      */
/*               |        counter values of FailureCycleCounterThreshold    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : A change of the                      */
/*               |        FailureCycleCounterThreshold succeeded.           */
/*               |        DEM_IRT_NG : A change of the                      */
/*               |        FailureCycleCounterThreshold failed.              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEventFailureCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC )           EventId,
    VAR( Dem_u08_FailureCounterType, AUTOMATIC )                     FailureCycleCounterThreshold
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                     retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSetEventCyC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                     checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterPreInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Gets event index */
        retGetEventId = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );                               /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */

        if( retGetEventId == DEM_IRT_OK )
        {
            retSetEventCyC = Dem_Event_SetEventFailureCycleCounterThreshold( eventCtrlIndex, FailureCycleCounterThreshold );
            if( retSetEventCyC == DEM_IRT_OK )
            {
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_ResetEventFailureCycleCounterThreshold       */
/* Description   | Reset FailureCycleCounterThreshold in RAM-Data.          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        specific-event identifier                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : A change of the                      */
/*               |        FailureCycleCounterThreshold succeeded.           */
/*               |        DEM_IRT_NG : A change of the                      */
/*               |        FailureCycleCounterThreshold failed.              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ResetEventFailureCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC )           EventId
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )     eventCtrlIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSetEventCyC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterPreInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Gets event index */
        retGetEventId = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );                               /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */

        if( retGetEventId == DEM_IRT_OK )
        {
            retSetEventCyC = Dem_Event_ResetEventFailureCycleCounterThreshold( eventCtrlIndex );
            if( retSetEventCyC == DEM_IRT_OK )
            {
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_GetEventFailureCycleCounterThreshold         */
/* Description   | Sets FailureCycleCounterThreshold in RAM-Data.           */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        specific-event identifier                         */
/*               | [out] FailureCycleCounterThresholdPtr :                  */
/*               |        counter values of FailureCycleCounterThreshold    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : A change of the                      */
/*               |        FailureCycleCounterThreshold succeeded.           */
/*               |        DEM_IRT_NG : A change of the                      */
/*               |        FailureCycleCounterThreshold failed.              */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Control_SetEventFailureCycleCounterThreshold. */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventFailureCycleCounterThreshold
(
    VAR( Dem_EventIdType, AUTOMATIC )                           EventId,
    P2VAR( Dem_u08_FailureCounterType, AUTOMATIC, AUTOMATIC )   FailureCycleCounterThresholdPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetEventId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterPreInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Gets event index */
        retGetEventId = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );   /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */

        if( retGetEventId == DEM_IRT_OK )
        {
            eventStrgIndex = Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );   /* [GUD]eventCtrlIndex *//* [GUD:RET:IF_GUARDED: eventCtrlIndex ]eventStrgIndex */

            *FailureCycleCounterThresholdPtr = Dem_Event_GetEventFailureCycleCounterThreshold( eventStrgIndex );    /* [GUD]eventStrgIndex */
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
