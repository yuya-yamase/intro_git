/* Dem_Control_EventStatus_c(v5-9-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_EventStatus/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_Event.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../inc/Dem_Pm_Ind.h"
#include "../../../inc/Dem_Pm_Ind_MI.h"
#include "../../../inc/Dem_Pm_IUMPR.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_OccrDTC.h"
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
/* Function Name | Dem_Control_SetInitializeEventStatus                     */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        specific-event identifier                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG : Operation failed                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetInitializeEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )        /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) isSpecificEvent;
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )               */

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    retTempVal = Dem_CfgInfoPm_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );
    if( retTempVal == DEM_IRT_OK )
    {
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )        /*  [FuncSw]    */
        isSpecificEvent = Dem_CfgInfoPm_CheckEventKindOfSpecific_ByEvtCtrlIdx( eventCtrlIndex );

        if( isSpecificEvent == (boolean)FALSE )
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )               */
        {
            retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_INITILIZE_EVENT_STATUS, eventCtrlIndex, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
            if( retTempVal == DEM_IRT_OK )
            {
                retTempVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_INITILIZE_EVENT_STATUS, eventCtrlIndex, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
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
/* Function Name | Dem_Control_SetAgingEventStatus                          */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        specific-event identifier                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG : Operation failed                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetAgingEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )        /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) isSpecificEvent;
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )               */

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    retTempVal = Dem_CfgInfoPm_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );
    if( retTempVal == DEM_IRT_OK )
    {
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )        /*  [FuncSw]    */
        isSpecificEvent = Dem_CfgInfoPm_CheckEventKindOfSpecific_ByEvtCtrlIdx( eventCtrlIndex );

        if( isSpecificEvent == (boolean)FALSE )
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )               */
        {
            retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_AGING_EVENT_STATUS, eventCtrlIndex, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
            if( retTempVal == DEM_IRT_OK )
            {
                retTempVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_AGING_EVENT_STATUS, eventCtrlIndex, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
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
/* Function Name | Dem_Control_SetNormalizeEventStatus                      */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        specific-event identifier                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG : Operation failed                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetNormalizeEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )        /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) isSpecificEvent;
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )               */

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    retTempVal = Dem_CfgInfoPm_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );
    if( retTempVal == DEM_IRT_OK )
    {
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )        /*  [FuncSw]    */
        isSpecificEvent = Dem_CfgInfoPm_CheckEventKindOfSpecific_ByEvtCtrlIdx( eventCtrlIndex );

        if( isSpecificEvent == (boolean)FALSE )
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )               */
        {
            retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_NORMALIZE_EVENT_STATUS, eventCtrlIndex, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
            if( retTempVal == DEM_IRT_OK )
            {
                retTempVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_NORMALIZE_EVENT_STATUS, eventCtrlIndex, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
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
/* Function Name | Dem_Control_SetActiveFaultEventStatus                    */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventID :                                           */
/*               |        specific-event identifier                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG : Operation failed                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created. based on Dem_Control_SetInitializeEventStatus. */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetActiveFaultEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )        /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) isSpecificEvent;
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )               */

    retVal = DEM_IRT_NG;
    eventCtrlIndex = DEM_EVENTCTRLINDEX_INVALID;

    retTempVal = Dem_CfgInfoPm_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );
    if( retTempVal == DEM_IRT_OK )
    {
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )        /*  [FuncSw]    */
        isSpecificEvent = Dem_CfgInfoPm_CheckEventKindOfSpecific_ByEvtCtrlIdx( eventCtrlIndex );

        if( isSpecificEvent == (boolean)FALSE )
#endif  /*   ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )               */
        {
            retTempVal = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_ACTIVEFAULT_EVENT_STATUS, eventCtrlIndex, DEM_EVENT_STATUS_FAILED );
            if( retTempVal == DEM_IRT_OK )
            {
                retTempVal = Dem_AsyncReq_Enqueue( DEM_ASYNCREQ_ACTIVEFAULT_EVENT_STATUS, eventCtrlIndex, DEM_EVENT_STATUS_FAILED );
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
/* Function Name | Dem_Control_InitializeEventStatus                        */
/* Description   | Asynchronous processing function of InitializeEvent-     */
/*               | Status.                                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       : Index of the event table.             */
/*               | [in] Status      :                                       */
/*               | [in] DataBuffPtr :                                       */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR :   NotifySavedZone                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_InitializeEventStatus
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,                     /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSaveEventMemoryEntryToTmp;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldDTCStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    /* Set return value. */
    /* Fault record is updated, Need re-generate orderlist, Continue asynchronous processing. */
    retVal = ( DEM_ASYNCRET_UPD_FR | DEM_ASYNCRET_NEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    oldDTCStatus        = DEM_DTCSTATUS_BYTE_ALL_OFF;
    newDTCStatus        = DEM_DTCSTATUS_BYTE_ALL_OFF;

    eventCtrlIndex  =   ( Dem_u16_EventCtrlIndexType )Index;
    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );                        /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

    retSaveEventMemoryEntryToTmp = Dem_Control_SaveEventMemoryEntryToTmp( eventStrgIndex );
    if( retSaveEventMemoryEntryToTmp == DEM_IRT_OK )
    {
        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        /* Gets DTCStatus from tmporary */
        Dem_Data_GetDTCStatusFromTmp( &oldDTCStatus );


        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
#if ( DEM_ALTIUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
        Dem_NotifySavedZoneIUMPRUpdate_Enter(); /*  notify start :  AltIUMPR savedzone area will be update.(no IUMPR record.)  */
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )          */
        /*--------------------------------------*/

        Dem_Event_ClearFailedQualificationInfo_NotTestedInCycle( eventCtrlIndex );  /* [UpdRec]AltIUMPR */

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
#if ( DEM_ALTIUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
        Dem_NotifySavedZoneIUMPRUpdate_Exit();  /*  notify end :  AltIUMPR savedzone area will be update.(no IUMPR record.)  */
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )          */
        /*--------------------------------------*/

        /* Bit4 and Bit6 is ON */
        Dem_Data_UpdEvtMemEntryOfTmp_InitializeEvent();             /* [UpdRec]Event/Fault/FFD/OBDFFD/TSFFD */

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
        Dem_DTC_ClearPFCClearCondition( eventStrgIndex );           /* [UpdRec]PFCQuaInfo */
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )          */

        /* Clear the specified data -WIRStatus- */
        Dem_Ind_ClearWIRStatus( eventStrgIndex );


        (void)Dem_Data_GetDTCStatus( eventStrgIndex, &newDTCStatus );   /* no return check required */
        Dem_DTC_TranslateDTCStatusAfterUpdate( eventCtrlIndex, &oldDTCStatus, &newDTCStatus );

        /* Initilize event status completion notification */
        Dem_CfgInfoPm_TriggerEventStatusChangedFnc( eventCtrlIndex, oldDTCStatus, newDTCStatus );

#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )   /*  [FuncSw]    */
        Dem_OccrDTC_UpdateOccrDTCRecord_InitializeEventStatus( eventStrgIndex, oldDTCStatus, newDTCStatus );    /* [UpdRec]OccrDTC */
#endif  /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )            */

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_AgingEventStatus                             */
/* Description   | Asynchronous processing function of AgingEventStatus.    */
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
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_AgingEventStatus
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,                     /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSaveEventMemoryEntryToTmp;
    VAR( Dem_DTCStatusStType, AUTOMATIC ) oldDTCStatus_St;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldDTCStatus;
    VAR( Dem_DTCStatusStType, AUTOMATIC ) newDTCStatus_St;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    /* Set return value. */
    /* Fault record is updated, Need re-generate orderlist, Continue asynchronous processing. */
    retVal = ( DEM_ASYNCRET_UPD_FR | DEM_ASYNCRET_NEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    eventCtrlIndex  =   ( Dem_u16_EventCtrlIndexType )Index;
    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );                        /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

    retSaveEventMemoryEntryToTmp = Dem_Control_SaveEventMemoryEntryToTmp( eventStrgIndex );
    if( retSaveEventMemoryEntryToTmp == DEM_IRT_OK )
    {
        /* Gets DTCStatus from tmporary */
        Dem_Data_GetDTCStatusStructFromTmp( &oldDTCStatus_St );
        oldDTCStatus = oldDTCStatus_St.DTCStatus;

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        /*  update event memory entry : recovery mode.              */
        Dem_Data_UpdEvtMemEntryOfTmp_AgingEvent( oldDTCStatus );                /* [UpdRec]Event/Fault/FFD/OBDFFD/TSFFD */

        if( ( oldDTCStatus & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )     /* statusOfDTC : bit3     */
        {
            Dem_Event_ClearFailedQualificationInfo_nochange( eventCtrlIndex );  /* no update AltIUMPR record.    */

            (void)Dem_DataMngC_GetER_DTCStatusSt( eventStrgIndex, &newDTCStatus_St);   /* no return check required */
            newDTCStatus = newDTCStatus_St.DTCStatus;


#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
            /* Clear the Permanent memory */
            Dem_DTC_ClearPFC( &oldDTCStatus_St, &newDTCStatus_St );
            Dem_DTC_UpdatePermanentMemoryEntryToTmp();
#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */

            Dem_DTC_TranslateDTCStatusAfterUpdate( eventCtrlIndex, &oldDTCStatus, &newDTCStatus );

            /* Aging event status completion notification */
            Dem_CfgInfoPm_TriggerEventStatusChangedFnc( eventCtrlIndex, oldDTCStatus, newDTCStatus );

        }

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_NormalizeEventStatus                         */
/* Description   | Asynchronous processing function of NormalizeEventStatus.*/
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       : Index of the event table.             */
/*               | [in] Status      :                                       */
/*               | [in] DataBuffPtr :                                       */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR    :   NotifySavedZone                     */
/* UpdateRecord  | [UpdRec]AltIUMPR :   NotifySavedZone                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_NormalizeEventStatus
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,                     /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSaveEventMemoryEntryToTmp;
    VAR( Dem_DTCStatusStType, AUTOMATIC ) oldDTCStatus_St;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldDTCStatus;
    VAR( Dem_DTCStatusStType, AUTOMATIC ) newDTCStatus_St;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    /* Set return value. */
    /* Fault record is updated, Need re-generate orderlist, Continue asynchronous processing. */
    retVal = ( DEM_ASYNCRET_UPD_FR | DEM_ASYNCRET_NEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    eventCtrlIndex  =   ( Dem_u16_EventCtrlIndexType )Index;
    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );                        /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */
    retSaveEventMemoryEntryToTmp = Dem_Control_SaveEventMemoryEntryToTmp( eventStrgIndex );
    if( retSaveEventMemoryEntryToTmp == DEM_IRT_OK )
    {
        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        /* Gets DTCStatus from tmporary */
        Dem_Data_GetDTCStatusStructFromTmp( &oldDTCStatus_St );
        oldDTCStatus = oldDTCStatus_St.DTCStatus;

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
        Dem_NotifySavedZoneIUMPRUpdate_Enter(); /*  notify start :  IUMPR/AltIUMPR savedzone area will be update.  */
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )          */
        /*--------------------------------------*/

        Dem_Event_ClearAndPassedQualificationInfo_TestedInCycle( eventCtrlIndex );  /* [UpdRec]AltIUMPR */

        /*  update event memory entry : recovery mode.              */
        Dem_Data_UpdEvtMemEntryOfTmp_NormalizeEvent( oldDTCStatus );                /* [UpdRec]Event/Fault/FFD/OBDFFD/TSFFD */

        (void)Dem_DataMngC_GetER_DTCStatusSt( eventStrgIndex, &newDTCStatus_St);   /* no return check required */
        newDTCStatus = newDTCStatus_St.DTCStatus;

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
        /* Clear the Permanent memory */
        Dem_DTC_ClearPFC( &oldDTCStatus_St, &newDTCStatus_St );
        Dem_DTC_UpdatePermanentMemoryEntryToTmp();
#endif  /*  ( DEM_PFC_SUPPORT == STD_ON )       */

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON ) /*  [FuncSw]    */
        /* IUMPR Count Trigger Update */
        Dem_IUMPR_UpdateEventRelatedNumerator( eventCtrlIndex );               /* [UpdRec]IUMPR */
#endif  /*   ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )        */


        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
        Dem_NotifySavedZoneIUMPRUpdate_Exit();  /*  notify end : IUMPR/AltIUMPR savedzone area will be update.  */
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )          */
        /*--------------------------------------*/


        Dem_DTC_TranslateDTCStatusAfterUpdate( eventCtrlIndex, &oldDTCStatus, &newDTCStatus );

        /* Normalize event status completion notification */
        Dem_CfgInfoPm_TriggerEventStatusChangedFnc( eventCtrlIndex, oldDTCStatus, newDTCStatus );

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_ActiveFaultEventStatus                       */
/* Description   | Asynchronous processing function of ActiveFaultEventStatus.*/
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
/*   v5-9-0      | new created. based on Dem_Control_SetEvent.              */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_ActiveFaultEventStatus
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

    eventId =   Dem_CfgInfoCmn_CnvEventCtrlIndexToEventId( (Dem_u16_EventCtrlIndexType)Index );
    monitorData0 = ( (Dem_MonitorDataType)eventId ) | DEM_MONITORDATA_SETEVENTSTATUS;

    /* SetEvent FAILED with ActiveFaultReqFlag = TRUE */
    retVal  =   Dem_Control_SetEventCommon( (Dem_u16_EventCtrlIndexType)Index, ( Dem_EventStatusType )Status, monitorData0, (boolean)TRUE );

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
