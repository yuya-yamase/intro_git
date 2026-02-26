/* Dem_Control_EventUdsStatusHistory_c(v5-5-0)                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_EventUdsStatusHistory/CODE                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#if ( DEM_PID_READINESS_SUPPORT == STD_ON )

#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Event.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_Rc_DataMng.h"

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
/* Function Name | Dem_Control_ResetEventUdsStatusHistory                   */
/* Description   | Reset event history.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        event ID                                          */
/*               | [in] UDSStatusHistoryByte :                              */
/*               |        UDSStatusHistory byte mask                        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ResetEventUdsStatusHistory
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC ) UDSStatusHistoryByte
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC ) udsStatusHistory;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    /*  get eventCtrlIndex(PrimaryMemory)   */
    retTempVal = Dem_CfgInfoPm_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );
    if( retTempVal == DEM_IRT_OK )
    {
        /*  check parameter         */
        udsStatusHistory    =   UDSStatusHistoryByte;
        udsStatusHistory    =   udsStatusHistory & ( DEM_UDS_STATUS_HISTORY_CDTC | DEM_UDS_STATUS_HISTORY_PASSED );
        if ( udsStatusHistory != (Dem_UdsStatusHistoryByteType)0U )
        {
            retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_RESET_EVENTUDSSTATUSHISTORY, (Dem_u16_AsyncReqItemAType)eventCtrlIndex, (Dem_u08_AsyncReqItemBType)udsStatusHistory );
            if( retTempVal == DEM_IRT_OK )
            {
                retTempVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_RESET_EVENTUDSSTATUSHISTORY, (Dem_u16_AsyncReqItemAType)eventCtrlIndex, (Dem_u08_AsyncReqItemBType)udsStatusHistory );
                if( retTempVal == DEM_IRT_OK )
                {
                    retVal = DEM_IRT_OK;
                }
            }
        }
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_SetEventUdsStatusHistory                     */
/* Description   | Sets event history.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId :                                           */
/*               |        event ID                                          */
/*               | [in] UDSStatusHistoryByte :                              */
/*               |        UDSStatusHistory byte mask                        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEventUdsStatusHistory
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC ) UDSStatusHistoryByte
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC ) udsStatusHistory;

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    /*  get eventCtrlIndex(PrimaryMemory)   */
    retTempVal = Dem_CfgInfoPm_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );
    if( retTempVal == DEM_IRT_OK )
    {
        /*  check parameter         */
        udsStatusHistory    =   UDSStatusHistoryByte;
        udsStatusHistory    =   udsStatusHistory & ( DEM_UDS_STATUS_HISTORY_CDTC | DEM_UDS_STATUS_HISTORY_PASSED );
        if ( udsStatusHistory != (Dem_UdsStatusHistoryByteType)0U )
        {
            retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_SET_EVENTUDSSTATUSHISTORY, (Dem_u16_AsyncReqItemAType)eventCtrlIndex, (Dem_u08_AsyncReqItemBType)udsStatusHistory );
            if( retTempVal == DEM_IRT_OK )
            {
                retTempVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_SET_EVENTUDSSTATUSHISTORY, (Dem_u16_AsyncReqItemAType)eventCtrlIndex, (Dem_u08_AsyncReqItemBType)udsStatusHistory );
                if( retTempVal == DEM_IRT_OK )
                {
                    retVal = DEM_IRT_OK;
                }
            }
        }
    }
    return retVal;
}


/*--------------------------------------------------------------------------*/
/* Unit Internal functions -process-                                        */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Control_ResetEventUdsStatusHistoryProcess            */
/* Description   | Asynchronous processing function of ResetEventUdsStatusHistory.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       : Index of the event table.             */
/*               | [in] Status      : Status of the event.                  */
/*               | [in] DataBuffPtr :                                       */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_Control_AsyncReq.h.   */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_ResetEventUdsStatusHistoryProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC )       extendStatusOfDTCOld;
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC )       extendStatusOfDTCNew;
    VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC )  udsStatusHistory;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retGetVal;

    /* Set return value. */
    /* Fault record is not updated, No need re-generate orderlist, Continue asynchronous processing. */
    retVal = ( DEM_ASYNCRET_NOUPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    eventCtrlIndex  =   (Dem_u16_EventCtrlIndexType)Index;
    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );                        /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

    /* Get ExtendStatusOfDTC, StatusOfDTC From Event Record */
    retGetVal = Dem_DataMngC_GetER_ExtendDTCStatus( eventStrgIndex, &extendStatusOfDTCOld );

    if ( retGetVal == DEM_IRT_OK )
    {
        /*  get mask value          */
        udsStatusHistory        =   (Dem_UdsStatusHistoryByteType)Status & ( DEM_UDS_STATUS_HISTORY_CDTC | DEM_UDS_STATUS_HISTORY_PASSED );

        /*  bit off.                */
        extendStatusOfDTCNew    =   extendStatusOfDTCOld & ~udsStatusHistory;

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        /*  change value ?          */
        if ( extendStatusOfDTCNew != extendStatusOfDTCOld )
        {
            /*  change value.               */
            Dem_DataMngC_SetER_ExtendDTCStatus( eventStrgIndex, extendStatusOfDTCNew );

        }
        /*  reset qualification .       */
        Dem_Event_ClearFailedQualificationInfo_nochange( eventCtrlIndex );

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_SetEventUdsStatusHistoryProcess              */
/* Description   | Asynchronous processing function of SetEventUdsStatusHistory.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       : Index of the event table.             */
/*               | [in] Status      : Status of the event.                  */
/*               | [in] DataBuffPtr :                                       */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_Control_AsyncReq.h.   */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetEventUdsStatusHistoryProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC )       extendStatusOfDTCOld;
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC )       extendStatusOfDTCNew;
    VAR( Dem_UdsStatusHistoryByteType, AUTOMATIC )  udsStatusHistory;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )    retGetVal;

    /* Set return value. */
    /* Fault record is not updated, No need re-generate orderlist, Continue asynchronous processing. */
    retVal = ( DEM_ASYNCRET_NOUPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    eventCtrlIndex  =   (Dem_u16_EventCtrlIndexType)Index;
    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );                        /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

    /* Get ExtendStatusOfDTC, StatusOfDTC From Event Record */
    retGetVal = Dem_DataMngC_GetER_ExtendDTCStatus( eventStrgIndex, &extendStatusOfDTCOld );

    if ( retGetVal == DEM_IRT_OK )
    {
        /*  get mask value          */
        udsStatusHistory        =   (Dem_UdsStatusHistoryByteType)Status & ( DEM_UDS_STATUS_HISTORY_CDTC | DEM_UDS_STATUS_HISTORY_PASSED );

        /*  bit on.                 */
        extendStatusOfDTCNew    =   extendStatusOfDTCOld | udsStatusHistory;

        /*  change value ?          */
        if ( extendStatusOfDTCNew != extendStatusOfDTCOld )
        {
            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - start.   */
            Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
            /*--------------------------------------*/

            /*  change value.               */
            Dem_DataMngC_SetER_ExtendDTCStatus( eventStrgIndex, extendStatusOfDTCNew );

            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - end.     */
            Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
            /*--------------------------------------*/
        }
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
