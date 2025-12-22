/* Dem_Control_EventEntry_c(v5-10-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_EventEntry/CODE                               */
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
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_Event.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../inc/Dem_Pm_Ind.h"
#include "../../../inc/Dem_Pm_Ind_MI.h"
#include "../../../inc/Dem_Pm_MonSts.h"
#include "../../../inc/Dem_Pm_PreFFD.h"
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
static FUNC( void, DEM_CODE ) Dem_Control_UpdateEventStatusProcess
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    VAR( boolean, AUTOMATIC ) ActiveFaultReqFlag,
    P2VAR( Dem_UpdEvtCtrlFlagStType, AUTOMATIC, AUTOMATIC ) UpdEvtCtrlFlagStPtr
);
static FUNC( void, DEM_CODE ) Dem_Control_PredictiveFFDProcess
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    P2VAR( Dem_UpdEvtCtrlFlagStType, AUTOMATIC, AUTOMATIC ) UpdEvtCtrlFlagStPtr
);

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
/* Function Name | Dem_Control_SetEventCommon                               */
/* Description   | Asynchronous processing function                         */
/*               |     of SetEventStatusWithMonitorData and SetEventStatus  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex   : Index of the event table.        */
/*               | [in] EventStatus      : Status of the event.             */
/*               | [in] monitorData0     : Monitor test result              */
/*               | [in] ActiveFaultReqFlag :                                */
/* Return Value  | Dem_u08_AsyncExecReturnType :                            */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetEventCommon
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    VAR( boolean, AUTOMATIC ) ActiveFaultReqFlag
)
{
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSaveTemp;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_UpdEvtCtrlFlagStType, AUTOMATIC ) updEvtCtrlFlagSt;

    updEvtCtrlFlagSt.FaultRecordOverwriteFlag        = (boolean)FALSE;
    updEvtCtrlFlagSt.TSFFDeleteFlag                  = (boolean)FALSE;
    updEvtCtrlFlagSt.OldDTCStatusOverwritten         = DEM_DTCSTATUS_BYTE_ALL_OFF;
    updEvtCtrlFlagSt.EventStrgIndexOfFaultRecordOverwritten  =   DEM_EVENTSTRGINDEX_INVALID;

    /* Obtain a temporary area for event registration */
    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );    /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

    retSaveTemp = Dem_Control_SaveEventMemoryEntryToTmp( eventStrgIndex );
    if( retSaveTemp == DEM_IRT_OK )
    {
        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        if( EventStatus != DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED )
        {
            Dem_Control_UpdateEventStatusProcess( EventCtrlIndex, eventStrgIndex, EventStatus, monitorData0, ActiveFaultReqFlag, &updEvtCtrlFlagSt );
        }
        else
        {
            Dem_Control_PredictiveFFDProcess( eventStrgIndex, monitorData0, &updEvtCtrlFlagSt );
        }

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/

    }
    else
    {
        /* When obtaining a temporary area is failure */
    }

    /* Set return value. */
    /* Fault record is updated, No need re-generate orderlist, Continue asynchronous processing. */
    retVal = ( DEM_ASYNCRET_UPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    /*  faultRecordOverwriteFlag    */
    /*      TRUE  : the record has been overwritten. order lists shall be re-generated.     */
    /*      FALSE : the record has not been overwritten. order lists no need re-generate.   */
    if( ( updEvtCtrlFlagSt.FaultRecordOverwriteFlag == (boolean)TRUE ) || ( updEvtCtrlFlagSt.TSFFDeleteFlag == (boolean)TRUE ) )
    {
        if( updEvtCtrlFlagSt.FaultRecordOverwriteFlag == (boolean)TRUE )
        {
#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )   /*  [FuncSw]    */
            /*  set monitor status.                         */
            Dem_MonSts_SetAsyncMonitorStatus_OnOverflow_InEvtStrgGrp( updEvtCtrlFlagSt.EventStrgIndexOfFaultRecordOverwritten );
#endif  /*   ( DEM_TRIGGER_FIM_REPORTS == STD_ON )          */

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
            /*  notify overwritten EventStatus .     */
            Dem_Control_NotifyOverwrittenEventStatus( updEvtCtrlFlagSt.EventStrgIndexOfFaultRecordOverwritten, updEvtCtrlFlagSt.OldDTCStatusOverwritten );
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
        }

        /* Set return value. */
        /* Fault record is updated, Need re-generate orderlist, Continue asynchronous processing. */
        retVal = ( DEM_ASYNCRET_UPD_FR | DEM_ASYNCRET_NEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_UpdateEventStatusProcess                     */
/* Description   | UpdateEventStatus process.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex   : Index of the event table.        */
/*               | [in] EventStrgIndex :                                    */
/*               | [in] EventStatus :                                       */
/*               | [in] monitorData0 :                                      */
/*               | [in] ActiveFaultReqFlag :                                */
/*               | [out] UpdEvtCtrlFlagStPtr :                              */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR    :   NotifySavedZone                     */
/* UpdateRecord  | [UpdRec]AltIUMPR :   NotifySavedZone                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. split from Dem_Control_SetEventCommon(v5-3-0). */
/*   v5-6-0      | no branch changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/*   v5-10-0     | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_UpdateEventStatusProcess
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    VAR( boolean, AUTOMATIC ) ActiveFaultReqFlag,
    P2VAR( Dem_UpdEvtCtrlFlagStType, AUTOMATIC, AUTOMATIC ) UpdEvtCtrlFlagStPtr
)
{
    VAR( Dem_DTCStatusStType, AUTOMATIC ) oldDTCStatusSt;
    VAR( Dem_DTCStatusStType, AUTOMATIC ) newDTCStatusSt;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChangeDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retEventRetntion;
    VAR( Dem_u08_EventQualificationType, AUTOMATIC ) eventQualification;
    VAR( Dem_OrderListOccurredFlagType, AUTOMATIC ) occurFlag;
    VAR( boolean, AUTOMATIC ) faultOccurrenceFlag;
    VAR( boolean, AUTOMATIC ) updateDataFlag;

    retChangeDTC                    = DEM_IRT_NG;
    eventQualification              = DEM_EVENT_QUALIFICATION_NOTQUALIFIED;

    faultOccurrenceFlag             = (boolean)FALSE;
    occurFlag.ConfirmedOccurFlag    = (boolean)FALSE;
    occurFlag.MILOccurFlag          = (boolean)FALSE;

    oldDTCStatusSt.DTCStatus        = DEM_DTCSTATUS_BYTE_ALL_OFF;
    oldDTCStatusSt.ExtendDTCStatus  = DEM_DTCSTATUSEX_BYTE_ALL_OFF;
    oldDTCStatusSt.ExtendDTCStatus2 = DEM_DTCSTATUSEX2_BYTE_ALL_OFF;

    /* Gets DTC status from the temporary domain. */
    Dem_Data_GetDTCStatusStructFromTmp( &oldDTCStatusSt );

    newDTCStatusSt.DTCStatus        = oldDTCStatusSt.DTCStatus;
    newDTCStatusSt.ExtendDTCStatus  = oldDTCStatusSt.ExtendDTCStatus;
    newDTCStatusSt.ExtendDTCStatus2 = oldDTCStatusSt.ExtendDTCStatus2;

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - start.   */
#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_NotifySavedZoneIUMPRUpdate_Enter();      /*  notify start :  IUMPR/AltIUMPR savedzone area will be update.  */
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )          */
    /*--------------------------------------*/

    /*  check failure cycle counter or event occurrence counter increment condition.    */
    if ( EventStatus == DEM_EVENT_STATUS_FAILED )
    {
        if( ( oldDTCStatusSt.ExtendDTCStatus2 & DEM_DTCSTATUSEX2_STATUS_TFTOC_IN_FAILURECYCLE ) != DEM_DTCSTATUSEX2_STATUS_TFTOC_IN_FAILURECYCLE )
        {
            /*  increment failure cycle counter.            */
            Dem_Data_IncrementFailureCounterOfTmp();
        }

#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )  /* [FuncSw] */
        if( ( oldDTCStatusSt.DTCStatus & DEM_UDS_STATUS_TF ) != DEM_UDS_STATUS_TF )     /*  statusOfDTC : bit0  */
        {
            /*  increment event occurrence counter.         */
            Dem_Data_IncrementEventOccurrenceCounterOfTmp();
        }
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )       */
    }
    /*  set qualification info.                 */
    updateDataFlag = Dem_Event_SetQualificationInfo( EventCtrlIndex, EventStatus, &eventQualification );     /* [GUDCHK:CALLER]EventCtrlIndex *//* [UpdRec]AltIUMPR */

    /* When called by ActiveFaultEventStatus, always update event */
    if ( ActiveFaultReqFlag == (boolean)TRUE )
    {
        updateDataFlag = (boolean)TRUE;
    }

    /* Judge whether to update event */
    if( updateDataFlag == (boolean)TRUE )
    {
        /* When there is an event to be updated */
        /* Execute DTC status change processing */
        retChangeDTC = Dem_DTC_ChangeDTCStatus( EventStrgIndex, eventQualification, ActiveFaultReqFlag, &oldDTCStatusSt, &newDTCStatusSt, &occurFlag );
    }

    if( retChangeDTC == DEM_IRT_OK )
    {
        /* When DTC status change is successful */
        if( eventQualification == DEM_EVENT_QUALIFICATION_FAILED )
        {
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
            Dem_Data_SetDTCStatusForFaultRecordOverwrite( newDTCStatusSt.DTCStatus );
#endif  /*   ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )           */
            retEventRetntion = Dem_Control_ProcessEventRetention( &occurFlag, &faultOccurrenceFlag );
            if( ( retEventRetntion == DEM_IRT_NG ) && ( faultOccurrenceFlag == (boolean)FALSE ) )
            {
                Dem_Event_ClearTargetQualificationInfo_NotTestedInCycle( EventCtrlIndex );      /* [GUDCHK:CALLER]EventCtrlIndex *//* [UpdRec]AltIUMPR */
            }

            /* Checks if fault record will be overwritten. */
            UpdEvtCtrlFlagStPtr->FaultRecordOverwriteFlag = Dem_Data_CheckFaultRecordOverwrite( &( UpdEvtCtrlFlagStPtr->EventStrgIndexOfFaultRecordOverwritten ), &( UpdEvtCtrlFlagStPtr->OldDTCStatusOverwritten ) );
        }
        else
        {
            /* PASSED or NOTQUALIFIED */
            retEventRetntion = DEM_IRT_OK;
        }

        /* Update statusOfDTC bit2, bit3, bit7 */
        Dem_DTC_UpdateDTCStatusByRetentionResult( EventStrgIndex, EventStatus, retEventRetntion, occurFlag.ConfirmedOccurFlag, DEM_MISFIRE_CYLINDER_INVALID, &oldDTCStatusSt, &newDTCStatusSt );
        Dem_Control_UpdateEventRelatedData( EventStrgIndex, EventStatus, monitorData0, faultOccurrenceFlag, oldDTCStatusSt.DTCStatus, newDTCStatusSt.DTCStatus, DEM_MISFIRE_CYLINDER_INVALID );

        Dem_Control_UpdateEventMemoryEntryFromTmp( DEM_EVTKINDPTN_PRIMEM_NORMAL, EventStatus );
        UpdEvtCtrlFlagStPtr->TSFFDeleteFlag = Dem_Data_CheckTSFFDeleteByFFROverwritten();
#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )     /*  [FuncSw]    */
        Dem_Control_RemovePrestoredFreezeFrame( EventStrgIndex, EventStatus, oldDTCStatusSt.DTCStatus, newDTCStatusSt.DTCStatus);
#endif  /*   ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )            */

#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
        if ( UpdEvtCtrlFlagStPtr->FaultRecordOverwriteFlag == (boolean)TRUE )
        {
            Dem_IndMI_HoldB1Counter( UpdEvtCtrlFlagStPtr->EventStrgIndexOfFaultRecordOverwritten );
        }
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

        /*  notify DTC status changed.              */
        Dem_DTC_TranslateDTCStatusAfterUpdate( EventCtrlIndex, &oldDTCStatusSt.DTCStatus, &newDTCStatusSt.DTCStatus );      /* [GUDCHK:CALLER]EventCtrlIndex */

#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )   /*  [FuncSw]    */
        Dem_OccrDTC_SetEvent( EventStrgIndex, UpdEvtCtrlFlagStPtr->EventStrgIndexOfFaultRecordOverwritten, oldDTCStatusSt.DTCStatus, newDTCStatusSt.DTCStatus, UpdEvtCtrlFlagStPtr->OldDTCStatusOverwritten, UpdEvtCtrlFlagStPtr->FaultRecordOverwriteFlag );
#endif  /*   ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )          */

        /*  notify EventStatusChanged               */
        Dem_CfgInfoPm_TriggerEventStatusChangedFnc( EventCtrlIndex, oldDTCStatusSt.DTCStatus, newDTCStatusSt.DTCStatus );   /* [GUDCHK:CALLER]EventCtrlIndex */
    }
    else
    {
        /*  no change DTC status.                   */
    }
#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON ) /*  [FuncSw]    */
    /* IUMPR Count Trigger Update */
    Dem_IUMPR_UpdateEventRelatedNumerator( EventCtrlIndex );        /* [GUDCHK:CALLER]EventCtrlIndex *//*[UpdRec]IUMPR */
#endif  /*   ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )        */

#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    Dem_IndMI_UpdateB1RecordBySetEvent( EventStatus, EventStrgIndex, newDTCStatusSt.DTCStatus );    /* [GUDCHK:CALLER]EventCtrlIndex */
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - end.     */
#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_NotifySavedZoneIUMPRUpdate_Exit();  /*  notify end :  IUMPR/AltIUMPR savedzone area will be update.  */
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )          */
    /*--------------------------------------*/

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_PredictiveFFDProcess                         */
/* Description   | PredictiveFFD process.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in]monitorData0 :                                       */
/*               | [out] UpdEvtCtrlFlagStPtr :                              */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_PredictiveFFDProcess
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    P2VAR( Dem_UpdEvtCtrlFlagStType, AUTOMATIC, AUTOMATIC ) UpdEvtCtrlFlagStPtr
)
{
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) tmpStatusOfDTC;
#endif  /*   ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )           */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retEventRetntion;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckStorePredictiveFFD;
    VAR( boolean, AUTOMATIC ) retCheckExistsEventMemoryEntry;
    VAR( boolean, AUTOMATIC ) faultOccurrenceFlag;
    VAR( Dem_OrderListOccurredFlagType, AUTOMATIC ) occurFlag;

    faultOccurrenceFlag             = (boolean)FALSE;
    occurFlag.ConfirmedOccurFlag    = (boolean)FALSE;
    occurFlag.MILOccurFlag          = (boolean)FALSE;

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
    tmpStatusOfDTC = DEM_DTCSTATUS_BYTE_DEFAULT;
    Dem_Data_GetDTCStatusFromTmp( &tmpStatusOfDTC );
    Dem_Data_SetDTCStatusForFaultRecordOverwrite( tmpStatusOfDTC );
#endif  /*   ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )           */

    /* Check if FaultRecord is exists. */
    retCheckExistsEventMemoryEntry = Dem_Data_CheckExistsEventMemoryEntryOfTmp();
    if( retCheckExistsEventMemoryEntry == (boolean)TRUE )
    {
        /* FaultRecord secured. */
        retEventRetntion = DEM_IRT_OK;
        faultOccurrenceFlag = (boolean)TRUE;

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
        Dem_Data_SelectEventEntryOverwrite();
#endif  /*   ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )           */
    }
    else
    {
        /* FaultRecord not secured. */

        /* Bit3 and Bit7 are not turned on in PredictiveFFD Request. */
        /* (occurFlag.ConfirmedOccurFlag & MILOccurFlag is FALSE)  */
        retEventRetntion = Dem_Control_ProcessEventRetention( &occurFlag, &faultOccurrenceFlag );
    }

    if( ( retEventRetntion == DEM_IRT_OK ) && ( faultOccurrenceFlag == (boolean)TRUE ) )
    {
        /* Secure a new FaultRecord or FaultRecord secured. */
        Dem_Control_UpdateEventRelatedData( EventStrgIndex, DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED, monitorData0, faultOccurrenceFlag, DEM_DTCSTATUS_BYTE_DEFAULT, DEM_DTCSTATUS_BYTE_DEFAULT, DEM_MISFIRE_CYLINDER_INVALID );

        /* Check if PredictiveFFD is stored. */
        retCheckStorePredictiveFFD = Dem_Data_CheckStorePredictiveFFDOfTmp( EventStrgIndex );
        if( retCheckStorePredictiveFFD == DEM_IRT_OK )
        {
            /* Checks if fault record will be overwritten. */
            UpdEvtCtrlFlagStPtr->FaultRecordOverwriteFlag = Dem_Data_CheckFaultRecordOverwrite( &( UpdEvtCtrlFlagStPtr->EventStrgIndexOfFaultRecordOverwritten ), &( UpdEvtCtrlFlagStPtr->OldDTCStatusOverwritten ) );

            Dem_Control_UpdateEventMemoryEntryFromTmp( DEM_EVTKINDPTN_PRIMEM_NORMAL, DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED );
            UpdEvtCtrlFlagStPtr->TSFFDeleteFlag = Dem_Data_CheckTSFFDeleteByFFROverwritten();
        }
    }

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )     /*  [FuncSw]    */
    Dem_Control_RemovePrestoredFreezeFrame( EventStrgIndex, DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED, DEM_DTCSTATUS_BYTE_DEFAULT, DEM_DTCSTATUS_BYTE_DEFAULT);
#endif  /* ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )              */

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
