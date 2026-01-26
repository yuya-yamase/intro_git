/* Dem_Control_IUMPR_c(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_IUMPR/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )

#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_Control_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Control_IUMPR.h"
#include "../../../inc/Dem_Pm_IUMPR.h"
#include "../../../usr/Dem_SavedZone_Callout.h"
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
/* Function Name | Dem_Control_GetIUMPRDataByRatioId                        */
/* Description   | Get numerator and denominator for IUMPR.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioID :                                           */
/*               |          Ratio Identifier reporting that a respective    */
/*               |          monitor could have found a fault.               */
/*               | [out] NumeratorPtr  : Numerator.                         */
/*               | [out] DenominatorPtr : Denominator.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetIUMPRDataByRatioId
(
    VAR( Dem_RatioIdType, AUTOMATIC )       RatioId,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   NumeratorPtr,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   DenominatorPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retVal = Dem_IUMPR_GetDataByRatioId( RatioId, NumeratorPtr, DenominatorPtr );
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetEventIdByRatioId                          */
/* Description   | Get EventId for IUMPR.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioID :                                           */
/*               |          Ratio Identifier reporting that a respective    */
/*               |          monitor could have found a fault.               */
/*               | [out] EventIdPtr   : EventId.                            */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Control_GetIUMPRDataByRatioId. */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventIdByRatioId
(
    VAR( Dem_RatioIdType, AUTOMATIC )               RatioId,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC )  EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     checkStatus;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterInit();
    if( checkStatus == DEM_IRT_OK )
    {
        retVal = Dem_IUMPR_GetEventIdByRatioId( RatioId, EventIdPtr );
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetRatioIdByEventId                          */
/* Description   | Get RatioId list by EventId.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        Identification of an event by assigned EventId    */
/*               | [out] RatioIdBufferPtr :  RatioId list.                  */
/*               | [in/out] RatioIdNumPtr :  RatioId list number.           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : buffer overflow.       */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Control_GetIUMPRDataByRatioId. */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetRatioIdByEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( Dem_RatioIdType, AUTOMATIC, DEM_APPL_DATA ) RatioIdBufferPtr,
    P2VAR( Dem_RatioIdType, AUTOMATIC, AUTOMATIC ) RatioIdNumPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retResult;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     checkStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC )     eventCtrlIndex;
    VAR( boolean, AUTOMATIC ) eventOBDKind;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_Control_ChkAfterInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Get eventCtrlIndex with available check */
        retResult = Dem_Control_GetEventCtrlIndexFromEventId( EventId, &eventCtrlIndex );   /* [GUD:RET:DEM_IRT_OK] eventCtrlIndex */

        /* If the Event is Within Range */
        if( retResult == DEM_IRT_OK )
        {
            eventOBDKind    =   Dem_CfgInfoPm_CheckEventKindOfOBD_ByEvtCtrlIdx( eventCtrlIndex );   /* [GUD]eventCtrlIndex */
            if( eventOBDKind == (boolean)TRUE ) /*  OBD     */
            {
                retVal = Dem_IUMPR_GetRatioIdByEventId( eventCtrlIndex, RatioIdBufferPtr, RatioIdNumPtr );  /* [GUD]eventCtrlIndex */
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_JudgeMinThanCurrentRatio                     */
/* Description   | Compare Ratio [para1/para2] > [para3/para4].             */
/* Preconditions | none                                                     */
/* Parameters    | [in] CurrentNumerator   : Current Numerator.             */
/*               | [in] CurrentDenominator : Current Denominator.           */
/*               | [in] TargetNumerator    : Target Numerator.              */
/*               | [in] TargetDenominator  : Target Denominator.            */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Current >  Target .                       */
/*               |        FALSE : Current <= Target.                        */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_JudgeMinimumRatioThanCurrentRatio. */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Control_JudgeMinThanCurrentRatio
(
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    CurrentNumerator,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    CurrentDenominator,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    TargetNumerator,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    TargetDenominator
)
{
    VAR( boolean, AUTOMATIC ) retVal;

    retVal  =   Dem_IUMPR_JudgeMinThanCurrentRatio( CurrentNumerator, CurrentDenominator, TargetNumerator, TargetDenominator );

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_RepIUMPRFaultDetect                          */
/* Description   | Service for reporting that faults are possibly found     */
/*               | because all conditions are fullfilled.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioID :                                           */
/*               |          Ratio Identifier reporting that a respective    */
/*               |          monitor could have found a fault                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_RepIUMPRFaultDetect
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     checkCond;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_REP_IUMPR_FAULTDETECT, DEM_ASYNCREQ_PARAM_INDEX_INVALID, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
    if( checkStatus == DEM_IRT_OK )
    {
        checkCond = Dem_IUMPR_CheckFaultDetectCondition( RatioId );

        if( checkCond == DEM_IRT_OK )
        {
            retVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_REP_IUMPR_FAULTDETECT, (uint16)RatioId, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_RepIUMPRDenRelease                           */
/* Description   | Service is used to release a denominator of a specific   */
/*               | monitor.                                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioId :                                           */
/*               |          Ratio Identifier reporting that specific        */
/*               |          denominator is released                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_RepIUMPRDenRelease
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     checkCond;

    retVal = DEM_IRT_NG;

    checkStatus = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_REP_IUMPR_DENRELEASE, DEM_ASYNCREQ_PARAM_INDEX_INVALID, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
    if( checkStatus == DEM_IRT_OK )
    {
        checkCond = Dem_IUMPR_CheckLockReleaseCondition( RatioId );

        if( checkCond == DEM_IRT_OK )
        {
            retVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_REP_IUMPR_DENRELEASE, (uint16)RatioId, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_NotifyIUMPRDenRelease                        */
/* Description   | Asynchronous processing function of RepIUMPRDenRelease.  */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       : Ratio Identifier.                     */
/*               | [in] Status      :                                       */
/*               | [in] DataBuffPtr :                                       */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_CmnLib_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_NotifyIUMPRDenRelease
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,                     /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( Dem_RatioIdType, AUTOMATIC ) ratioId;

    /* Set return value. */
    /* Fault record is not updated, No need re-generate orderlist, Continue asynchronous processing. */
    retVal = ( DEM_ASYNCRET_NOUPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    ratioId = (Dem_RatioIdType)Index;

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - start.   */
    Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
    /*--------------------------------------*/

    Dem_IUMPR_UpdateDenUnlockCondition( ratioId );

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - end.     */
    Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
    /*--------------------------------------*/

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_NotifyIUMPRFaultDetect                       */
/* Description   | Asynchronous processing function of RepIUMPRFaultDetect. */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       : Ratio Identifier.                     */
/*               | [in] Status      :                                       */
/*               | [in] DataBuffPtr :                                       */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_CmnLib_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_NotifyIUMPRFaultDetect
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,                     /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( Dem_RatioIdType, AUTOMATIC ) ratioId;

    /* Set return value. */
    /* Fault record is not updated, No need re-generate orderlist, Continue asynchronous processing. */
    retVal = ( DEM_ASYNCRET_NOUPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    ratioId = (Dem_RatioIdType)Index;

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - start.   */
    Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
    /*--------------------------------------*/

    Dem_IUMPR_RepIUMPRFaultDetect( ratioId );

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - end.     */
    Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
    /*--------------------------------------*/

    return retVal;
}




#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
