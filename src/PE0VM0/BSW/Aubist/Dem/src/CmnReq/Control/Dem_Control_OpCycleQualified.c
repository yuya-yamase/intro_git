/* Dem_Control_OpCycleQualified_c(v5-5-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_OpCycleQualified/CODE                         */
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
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_OpCycle.h"
#include "../../../inc/Dem_CmnLib_Control.h"

#include "../../../inc/Dem_CmnIf_Control.h"
#include "../../../usr/Dem_SavedZone_Callout.h"
#include "Dem_Control_cmn_local.h"

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

#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_SetCycleQualified                            */
/* Description   | Set the operation cycle to qualified.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleId : Operation cycle identifier.      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |    DEM_IRT_OK : Success.                                 */
/*               |    DEM_IRT_NG : Failed.                                  */
/* Notes         | This function is in SW-C main process.                   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetCycleQualified
(
    VAR( Dem_u08_OperationCycleIdType, AUTOMATIC ) OperationCycleId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) setCycleQualifiedIndex;

    retVal = DEM_IRT_NG;

    retTempVal = Dem_OpCycle_CheckQualifiedCycleValue( OperationCycleId );
    if( retTempVal == DEM_IRT_OK )
    {
        setCycleQualifiedIndex = (Dem_u16_AsyncReqItemAType)Dem_OpCycle_CnvOpCycleIdToCycleQualifiedIndex( OperationCycleId );

        retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_SET_CYCLEQUALIFIED, setCycleQualifiedIndex, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
        if( retTempVal == DEM_IRT_OK )
        {
            retVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_SET_CYCLEQUALIFIED, setCycleQualifiedIndex, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
        }
        else
        {
            /* When the result of request condition judgment is not OK */
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
/* Function Name | Dem_Control_GetCycleQualified                            */
/* Description   | Get the qualification of a specific operation cycle.     */
/* Preconditions | none                                                     */
/* Parameters    | [in] OperationCycleId : Operation cycle identifier.      */
/*               | [out] CycleQualifiedPtr : Pointer of qualification data. */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |    DEM_IRT_OK : Success.                                 */
/*               |    DEM_IRT_NG : Failed.                                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetCycleQualified
(
    VAR( Dem_u08_OperationCycleIdType, AUTOMATIC ) OperationCycleId,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) CycleQualifiedPtr
)
{
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) cycleState;
    VAR( boolean, AUTOMATIC ) cycleQualified;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) cycleQualifiedIndex;

    retVal = DEM_IRT_NG;
    cycleQualified = (boolean)FALSE;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retTempVal = Dem_OpCycle_CheckQualifiedCycleValue( OperationCycleId );
        if( retTempVal == DEM_IRT_OK )
        {
            cycleQualifiedIndex =   Dem_OpCycle_CnvOpCycleIdToCycleQualifiedIndex( OperationCycleId );

            cycleState = Dem_OpCycle_GetCycleStartNoticeFlag( cycleQualifiedIndex );
            if( cycleState == DEM_CYCLE_NOTIFY_START )
            {
                cycleQualified = (boolean)TRUE;
            }

            *CycleQualifiedPtr = cycleQualified;
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_SetCycleQualifiedProcess                     */
/* Description   | Asynchronous processing function of SetCycleQualified.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       : Operation cycle identifier.           */
/*               | [in] Status      :                                       */
/*               | [in] DataBuffPtr :                                       */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetCycleQualifiedProcess
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

    Dem_OpCycle_SetCycleStartNoticeFlag( ( Dem_u08_CycleQualifiedIndexType )Index, DEM_CYCLE_NOTIFY_START );

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - end.     */
    Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
    /*--------------------------------------*/

    return retVal;
}
#endif /* DEM_CYCLEQUALIFIED_SUPPORT -STD_ON- */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
