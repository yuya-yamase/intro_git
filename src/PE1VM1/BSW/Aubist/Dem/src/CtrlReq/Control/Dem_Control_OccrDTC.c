/* Dem_Control_OccrDTC_c(v5-3-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_OccrDTC/CODE                                  */
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
#include "../../../inc/Dem_Pm_OccrDTC.h"
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

#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_GetDTCByOccurrenceTime                       */
/* Description   | Get DTC By Occurrence Time                               */
/* Preconditions | none                                                     */
/* Parameters    | [in]  DTCRequest  :                                      */
/*               |          DEM_MOST_RECENT_FAILED_DTC                      */
/*               |          DEM_MOST_REC_DET_CONFIRMED_DTC                  */
/*               | [out] DTCValuePtr :                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : not stored          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetDTCByOccurrenceTime
(
    VAR( Dem_DTCRequestType, AUTOMATIC ) DTCRequest,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Check if the status is initialization complete */
    retVal = Dem_Control_ChkAfterCompleteInit();
    if( retVal == DEM_IRT_OK )
    {
        retVal = Dem_OccrDTC_GetDTCByOccurrenceTime( DTCRequest, DTCValuePtr );
    }

    return retVal;
}
#endif  /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )    */

#if ( DEM_TRIGGER_DCM_REPORTS == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_DTCStatusChangedNotification                 */
/* Description   | DTCStatus Changed Notification                           */
/* Preconditions | none                                                     */
/* Parameters    | [in]  TriggerNotification  :                             */
/*               |        TRUE  : Request Trigger Start                     */
/*               |        FALSE : Request Trigger Stop                      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_DTCStatusChangedNotification
(
    VAR( boolean, AUTOMATIC ) TriggerNotification
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;

    retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_NOTIFY_DTC_STATUS_CHANGED, DEM_ASYNCREQ_PARAM_INDEX_INVALID, (Dem_u08_AsyncReqItemBType)TriggerNotification );
    if( retTempVal == DEM_IRT_OK )
    {
        (void)Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_NOTIFY_DTC_STATUS_CHANGED, DEM_ASYNCREQ_PARAM_INDEX_INVALID, (Dem_u08_AsyncReqItemBType)TriggerNotification );     /* no return check required */
    }
    else
    {
        /* When the result of request condition judgment is not OK */
        /* No process */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Control_NotifyDTCStatusChanged                       */
/* Description   | Asynchronous processing function of DcmControlDTCStatus- */
/*               | ChangedNotification.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       :                                       */
/*               | [in] Status      : Trigger notification.                 */
/*               | [in] DataBuffPtr :                                       */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_CmnLib_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_NotifyDTCStatusChanged
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,                     /* MISRA DEVIATION */
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;

    /* Set return value. */
    /* Fault record is not updated, No need re-generate orderlist, Continue asynchronous processing. */
    retVal = ( DEM_ASYNCRET_NOUPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    Dem_OccrDTC_ReqNotifyDTCStatusChanged( (boolean)Status );

    return retVal;
}
#endif  /* ( DEM_TRIGGER_DCM_REPORTS == STD_ON )    */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
