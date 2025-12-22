/* Dem_Control_Readiness_c(v5-5-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_Readiness/CODE                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../inc/Dem_CmnLib_Control_AsyncReq.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Pm_PID.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

#include "Dem_Control_local.h"

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
#include "../../../inc/Dem_Pm_Control_OBD.h"

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
/* Function Name | Dem_Control_SetEvtDisable                                */
/* Description   | Set the Disable status of a specific Event.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        Identification of an event by assigned EventId.   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation was failed.                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEvtDisable
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    retTempVal = Dem_CfgInfoPm_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );
    if( retTempVal == DEM_IRT_OK )
    {
        retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_SET_EVENTDISABLED, (Dem_u16_AsyncReqItemAType)eventCtrlIndex, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
        if( retTempVal == DEM_IRT_OK )
        {

            retTempVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_SET_EVENTDISABLED, (Dem_u16_AsyncReqItemAType)eventCtrlIndex, DEM_ASYNCREQ_PARAM_STATUS_INVALID);
            if( retTempVal == DEM_IRT_OK )
            {
                retVal = DEM_IRT_OK;
            }
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_SetEventDisabled                             */
/* Description   | Asynchronous processing function of SetEventDisabled.    */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       : Index of the event table.             */
/*               | [in] Status      :                                       */
/*               | [in] DataBuffPtr :                                       */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetEventDisabled
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,                     /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;

    /* Set return value. */
    /* Fault record is not updated, No need re-generate orderlist, Continue asynchronous processing. */
    retVal = ( DEM_ASYNCRET_NOUPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - start.   */
    Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
    /*--------------------------------------*/

    Dem_PID_SetEventDisable( (Dem_u16_EventCtrlIndexType)Index );

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - end.     */
    Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
    /*--------------------------------------*/

    return retVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/




#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
