/* Dem_Control_SpecificEventEntry_c(v5-10-0)                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_SpecificEventEntry/CODE                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )

#include "../../../cfg/Dem_Misfire_Cfg.h"
#include "../../../cfg/Dem_Similar_Cfg.h"
#include "../../../inc/Dem_CmnLib_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../inc/Dem_CmnLib_Control_AsyncReq.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_OpCycle.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Control_Specific.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_Event.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../inc/Dem_Pm_IUMPR.h"
#include "../../../inc/Dem_Pm_MonSts.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "../../../inc/Dem_Rc_SimilarMng.h"
#include "../../../inc/Dem_Utl_Similar.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../usr/Dem_SavedZone_Callout.h"
#include "Dem_Control_local.h"

#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
#include <Dem_SIT_RangeCheck.h>
#endif /* DEM_SIT_RANGE_CHECK */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_SPCEVT_DATABUF_EVENTSTATUS          DEM_ASYNCDATAQUE_EVENTSTATUS_POS
#define DEM_SPCEVT_DATABUF_MISFIRECYLINDER_0    ((uint8)( DEM_ASYNCDATAQUE_EVENTSTATUS_POS + (uint8)1U ))
#define DEM_SPCEVT_DATABUF_MISFIRECYLINDER_1    ((uint8)( DEM_ASYNCDATAQUE_EVENTSTATUS_POS + (uint8)2U ))
#define DEM_SPCEVT_DATABUF_MISFIRECONDITION     ((uint8)( DEM_ASYNCDATAQUE_EVENTSTATUS_POS + (uint8)3U ))
#define DEM_SPCEVT_DATABUF_SIMILARCONDITION     ((uint8)( DEM_ASYNCDATAQUE_EVENTSTATUS_POS + (uint8)4U ))

#define DEM_SPCEVT_BITSHIFT_8                   (8U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*------------------------------------------------------*/
/*  update temporary area flag structure                */
/*------------------------------------------------------*/
typedef struct
{
    boolean UpdateTmpAreaFlag;
    boolean UpdateTmpAreaSpecificFlag;
    boolean UpdateTmpAreaMisfirePFCFlag;

} Dem_UpdateTmpAreaStType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_Control_SetSpecificEventProcessSub
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr,
    P2VAR( Dem_UpdEvtCtrlFlagStType, AUTOMATIC, AUTOMATIC ) UpdEvtCtrlFlagStPtr
);
static FUNC( void, DEM_CODE ) Dem_Control_UpdateSpecificEventStatusProcess
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr,
    VAR( boolean, AUTOMATIC ) ResultOfCheckSpecificFault,
    P2VAR( Dem_UpdEvtCtrlFlagStType, AUTOMATIC, AUTOMATIC ) UpdEvtCtrlFlagStPtr,
    P2VAR( Dem_UpdateTmpAreaStType, AUTOMATIC, AUTOMATIC ) UpdateTmpAreaStPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckSpecificTypeSetEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfCheckSpecificfaultPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckSpecificTypeSetEvent_Failed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfCheckSpecificfaultPtr
);

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckEmissionFailedCondition
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfCheckSpecificfaultPtr
);
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckCATFailedCondition
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfCheckSpecificfaultPtr
);
static FUNC( boolean, DEM_CODE ) Dem_Control_CheckSpecificFault
( void );
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )       */
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )       */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckSimilarFailedCondition
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfCheckSpecificfaultPtr
);
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

static FUNC( void, DEM_CODE ) Dem_Control_ConvertSpecificEventReqData
(
    P2CONST( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr,
    P2VAR( Dem_EventStatusType, AUTOMATIC, AUTOMATIC ) EventStatusPtr,
    P2VAR( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr
);
static FUNC( void, DEM_CODE ) Dem_Control_SetSpecificEventReqData
(
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, DEM_APPL_DATA ) SpecificConditionPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckEventStatusForSpecificEvent
(
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus
);
static FUNC( void, DEM_CODE ) Dem_Control_SpecificPredictiveFFDProcess
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr,
    P2VAR( Dem_UpdEvtCtrlFlagStType, AUTOMATIC, AUTOMATIC ) UpdEvtCtrlFlagStPtr
);
#if ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Control_UpdateProgressEngine1000RPM
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus
);
#endif  /* ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON )          */

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
/* Function Name | Dem_Control_SetSpecificEventStatus                       */
/* Description   | Set Specific event status.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventId     : Event identifier.                     */
/*               | [in] EventStatus : Monitor test result.                  */
/*               | [in] SpecificConditionPtr : Specific condition of event. */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetSpecificEventStatus
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, DEM_APPL_DATA ) SpecificConditionPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckEventStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( boolean, AUTOMATIC ) isSpecificEvent;
    VAR( uint8, AUTOMATIC ) data[DEM_ASYNCDATAQUE_ITEMSIZE_MAX];
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckMisfireCylinder;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    retVal = DEM_IRT_NG;

    retTempVal = Dem_CfgInfoPm_CnvEventIdToEventCtrlIndex( EventId, &eventCtrlIndex );
    if( retTempVal == DEM_IRT_OK )
    {
        /* Judges SpecifcEvent */
        isSpecificEvent = Dem_CfgInfoPm_CheckEventKindOfSpecific_ByEvtCtrlIdx( eventCtrlIndex );

        /*  OK : primary normal events and user defined memory events   */
        /*  NG : primary specific events                                */
        if( isSpecificEvent == (boolean)TRUE )
        {
            /* SpcificEvent */

            retCheckEventStatus = Dem_Control_CheckEventStatusForSpecificEvent( EventStatus );
            if( retCheckEventStatus == DEM_IRT_OK )
            {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                retCheckMisfireCylinder = Dem_Misfire_CheckSetEventCylinder( eventCtrlIndex, EventStatus, SpecificConditionPtr->MisfireInfo.MisfireCylinder );
                if( retCheckMisfireCylinder == DEM_IRT_OK )
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
                {
                    /* Judges request condition */
                    checkStatus = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_SPEC_EVENT, eventCtrlIndex, EventStatus );
                    if( checkStatus == DEM_IRT_OK )
                    {
                        /* Converts SpecificCondition for data buffer */
                        Dem_Control_SetSpecificEventReqData( EventStatus, SpecificConditionPtr, &data[0] );/* [ARYCHK] DEM_ASYNCDATAQUE_ITEMSIZE_MAX / 1 / 0 */

                        retVal = Dem_AsyncReq_EnqueueWithData( DEM_ASYNCREQ_SPEC_EVENT, eventCtrlIndex, &data[0] );/* [GUD:FixVal]DEM_ASYNCREQ_SPEC_EVENT *//* [ARYCHK] DEM_ASYNCDATAQUE_ITEMSIZE_MAX / 1 / 0 */
                    }
                }
            }
        }
        else
        {
            /* StandardEvent */

            /* Judges request condition */
            checkStatus = Dem_AsyncReq_JudgeReqCondition( DEM_ASYNCREQ_SPEC_EVENT, eventCtrlIndex, EventStatus );
            if( checkStatus == DEM_IRT_OK )
            {
                /*  call normal eventstatus function.       */
                retVal  =   Dem_Control_SetEventStatus( EventId, EventStatus );
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_SetSpecificEventProcess                      */
/* Description   | Asynchronous processing function of SetSpecificEvent-    */
/*               | Status.                                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       : Index of the event table.             */
/*               | [in] Status      :                                       */
/*               | [in] DataBuffPtr : Specific condition data of the event. */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR    :   NotifySavedZone                     */
/* UpdateRecord  | [UpdRec]AltIUMPR :   NotifySavedZone                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetSpecificEventProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,                     /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSaveTemp;
    VAR( Dem_EventStatusType, AUTOMATIC ) eventStatus;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_SpecificEventConditionType, AUTOMATIC ) specificCondition;
    VAR( Dem_UpdEvtCtrlFlagStType, AUTOMATIC ) updEvtCtrlFlagSt;

    eventCtrlIndex  =   ( Dem_u16_EventCtrlIndexType )Index;
    eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( eventCtrlIndex );                        /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

    updEvtCtrlFlagSt.FaultRecordOverwriteFlag        = (boolean)FALSE;
    updEvtCtrlFlagSt.TSFFDeleteFlag                  = (boolean)FALSE;
    updEvtCtrlFlagSt.OldDTCStatusOverwritten         = DEM_DTCSTATUS_BYTE_ALL_OFF;
    updEvtCtrlFlagSt.EventStrgIndexOfFaultRecordOverwritten  =   DEM_EVENTSTRGINDEX_INVALID;

    /* Convert from DataBuffer to request data */
    Dem_Control_ConvertSpecificEventReqData( DataBuffPtr, &eventStatus, &specificCondition );

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - start.   */
    Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
    /*--------------------------------------*/

#if ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON ) /*  [FuncSw]    */
    Dem_Control_UpdateProgressEngine1000RPM( eventStrgIndex, eventStatus );
#endif  /* ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON )          */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Misfire_ExtractAvailableCylinder( &(specificCondition.MisfireInfo.MisfireCylinder) );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    /* Obtain a temporary area for event registration */
    retSaveTemp = Dem_Control_SaveSpecificEventMemoryEntryToTmp( eventStrgIndex );
    if( retSaveTemp == DEM_IRT_OK )
    {
        if( eventStatus != DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED )
        {
            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - start.   */
#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
            Dem_NotifySavedZoneIUMPRUpdate_Enter(); /*  notify start :  savedzone area will be update.  */
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )          */
            /*--------------------------------------*/

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            /* Latch cylinder DTCStatus */
            Dem_Misfire_LatchCylinderStatus( eventStrgIndex );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

            Dem_Control_SetSpecificEventProcessSub( eventCtrlIndex, eventStrgIndex, eventStatus, &specificCondition, &updEvtCtrlFlagSt );   /* [UpdRec]AltIUMPR *//* [UpdRec]more */

#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )     /*  [FuncSw]    */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            Dem_Misfire_SetConfirmedOrderCylinder( eventStrgIndex );
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON ) /*  [FuncSw]    */
            /* IUMPR Count Trigger Update */
            Dem_IUMPR_UpdateEventRelatedNumerator( eventCtrlIndex );    /* [UpdRec]IUMPR */
#endif  /*   ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )        */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            /* Judge cylinder DTCStatus */
            Dem_Misfire_JudgeCylinderStatus( eventStrgIndex );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - end.     */
#if ( DEM_IUMPR_SUPPORT == STD_ON ) /*  [FuncSw]    */
            Dem_NotifySavedZoneIUMPRUpdate_Exit();  /*  notify end :  savedzone area will be update.  */
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )          */
            /*--------------------------------------*/

        }
        else
        {
            updEvtCtrlFlagSt.EventStrgIndexOfFaultRecordOverwritten  =   DEM_EVENTSTRGINDEX_INVALID;
            Dem_Control_SpecificPredictiveFFDProcess( eventCtrlIndex, eventStrgIndex, &specificCondition, &updEvtCtrlFlagSt );
        }
    }
    else
    {
        /* When obtaining a temporary area is failure */
    }

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - end.     */
    Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
    /*--------------------------------------*/

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
            /*  set monitor status.                 */
            Dem_MonSts_SetAsyncMonitorStatus_OnOverflow_InEvtStrgGrp( updEvtCtrlFlagSt.EventStrgIndexOfFaultRecordOverwritten );
#endif  /*   ( DEM_TRIGGER_FIM_REPORTS == STD_ON )          */

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
            /*  notify overwritten EventStatus.     */
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
/* Function Name | Dem_Control_SetSpecificEventProcessSub                   */
/* Description   | Asynchronous processing function of SetSpecificEvent-    */
/*               | Status.                                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex       : Index of the event table.    */
/*               | [in] EventStrgIndex       : Index of the event table.    */
/*               | [in] EventStatus      :                                  */
/*               | [in] SpecificConditionPtr :                              */
/*               | [out] UpdEvtCtrlFlagStPtr :                              */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/* UpdateRecord  | [UpdRec]PFCMisfire   :   NotifySavedZone                 */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_SetSpecificEventProcessSub
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr,
    P2VAR( Dem_UpdEvtCtrlFlagStType, AUTOMATIC, AUTOMATIC ) UpdEvtCtrlFlagStPtr
)
{
    VAR( Dem_UpdateTmpAreaStType, AUTOMATIC ) updateTmpAreaSt;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckSpecificTypeSetEvent;
    VAR( boolean, AUTOMATIC ) resultOfCheckSpecificfault;

    updateTmpAreaSt.UpdateTmpAreaFlag           = (boolean)FALSE;
    updateTmpAreaSt.UpdateTmpAreaSpecificFlag   = (boolean)FALSE;
    updateTmpAreaSt.UpdateTmpAreaMisfirePFCFlag = (boolean)FALSE;

    retCheckSpecificTypeSetEvent = Dem_Control_CheckSpecificTypeSetEvent( EventStrgIndex, EventStatus, SpecificConditionPtr, &resultOfCheckSpecificfault );
    if( retCheckSpecificTypeSetEvent == DEM_IRT_OK )
    {
        Dem_Control_UpdateSpecificEventStatusProcess( EventCtrlIndex, EventStrgIndex, EventStatus, SpecificConditionPtr, resultOfCheckSpecificfault, UpdEvtCtrlFlagStPtr, &updateTmpAreaSt );   /* [UpdRec]AltIUMPR */
    }
    else
    {
        /* Failed: less than ExcessCntThreshold for misfire event */
        /* Clear the AgingCounter and HealingCounter of temporary area */
        Dem_Data_SetAgingCounterToTmp( DEM_AGING_COUNT_INITIAL_VALUE );
#if ( DEM_INDICATOR_USE == STD_ON )             /*  [FuncSw]    */
        Dem_Data_SetHealingCounterToTmp( DEM_HEALING_COUNT_INITIAL_VALUE );
#endif  /*   ( DEM_INDICATOR_USE == STD_ON )        */
        /* Update EventMemoryEntry, Misfire, Similar */
        updateTmpAreaSt.UpdateTmpAreaFlag   =   (boolean)TRUE;
    }
    if ( updateTmpAreaSt.UpdateTmpAreaFlag == (boolean)TRUE )
    {
        Dem_Data_UpdateEventMemoryEntryFromTmp();        /* Update EventMemoryEntry, Misfire, Similar */
    }
    if ( updateTmpAreaSt.UpdateTmpAreaSpecificFlag == (boolean)TRUE )
    {
        Dem_Data_UpdateSpecificEventMemoryEntryFromTmp( EventStrgIndex );        /* Update Misfire, Similar */
    }

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
#if ( DEM_PFC_SUPPORT == STD_ON )               /*  [FuncSw]    */
    if ( updateTmpAreaSt.UpdateTmpAreaMisfirePFCFlag == (boolean)TRUE )
    {
        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - start.     */
        Dem_NotifySavedZonePermanentUpdate_Enter();         /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------------------*/

        Dem_Misfire_UpdatePermanentMemoryEntryToTmp( EventStrgIndex );        /* Update permanent cylinder *//*[UpdRec]PFCMisfire */

        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - end.       */
        Dem_NotifySavedZonePermanentUpdate_Exit();          /*  notify end :  savedzone area will be update.  */
        /*--------------------------------------------------*/
    }
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )                      */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    return;
}

/****************************************************************************/
/* Function Name | Dem_Control_UpdateSpecificEventStatusProcess             */
/* Description   | UpdateEventStatus process.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] EventStrgIndex :                                    */
/*               | [in] EventStatus :                                       */
/*               | [in] SpecificConditionPtr :                              */
/*               | [in] ResultOfCheckSpecificFault :                        */
/*               | [out] UpdEvtCtrlFlagStPtr :                              */
/*               | [out] UpdateTmpAreaStPtr :                               */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. split from Dem_Control_SetSpecificEventProcessSub(v5-3-0). */
/*   v5-6-0      | no branch changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_UpdateSpecificEventStatusProcess
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr,
    VAR( boolean, AUTOMATIC ) ResultOfCheckSpecificFault,
    P2VAR( Dem_UpdEvtCtrlFlagStType, AUTOMATIC, AUTOMATIC ) UpdEvtCtrlFlagStPtr,
    P2VAR( Dem_UpdateTmpAreaStType, AUTOMATIC, AUTOMATIC ) UpdateTmpAreaStPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChangeDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retEventRetntion;
    VAR( Dem_u08_EventQualificationType, AUTOMATIC ) eventQualification;
    VAR( boolean, AUTOMATIC ) updateDataFlag;
    VAR( boolean, AUTOMATIC ) faultOccurrenceFlag;
    VAR( Dem_OrderListOccurredFlagType, AUTOMATIC ) occurFlag;
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( boolean, AUTOMATIC ) updateTmpAreaFlag;
    VAR( boolean, AUTOMATIC ) updateTmpAreaSpecificFlag;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
#if ( DEM_PFC_SUPPORT == STD_ON )               /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) updateTmpAreaMisfirePFCFlag;
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )                      */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) tmpOldExtendDTCStatus;
    VAR( Dem_u08_DTCStatusExType, AUTOMATIC ) tmpNewExtendDTCStatus;

    VAR( Dem_DTCStatusStType, AUTOMATIC ) tmpDTCStatusSt;
    VAR( Dem_DTCStatusStType, AUTOMATIC ) oldDTCStatusSt;
    VAR( Dem_DTCStatusStType, AUTOMATIC ) newDTCStatusSt;

    updateTmpAreaFlag           = (boolean)FALSE;
    updateTmpAreaSpecificFlag   = (boolean)FALSE;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
#if ( DEM_PFC_SUPPORT == STD_ON )               /*  [FuncSw]    */
    updateTmpAreaMisfirePFCFlag = (boolean)FALSE;
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )                      */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    retChangeDTC                    = DEM_IRT_NG;
    eventQualification              = DEM_EVENT_QUALIFICATION_NOTQUALIFIED;
    faultOccurrenceFlag             = (boolean)FALSE;
    occurFlag.ConfirmedOccurFlag    = (boolean)FALSE;
    occurFlag.MILOccurFlag          = (boolean)FALSE;

    tmpOldExtendDTCStatus = DEM_DTCSTATUSEX_BYTE_ALL_OFF;
    tmpNewExtendDTCStatus = DEM_DTCSTATUSEX_BYTE_ALL_OFF;

    oldDTCStatusSt.DTCStatus        = DEM_DTCSTATUS_BYTE_ALL_OFF;
    oldDTCStatusSt.ExtendDTCStatus  = DEM_DTCSTATUSEX_BYTE_ALL_OFF;
    oldDTCStatusSt.ExtendDTCStatus2 = DEM_DTCSTATUSEX2_BYTE_ALL_OFF;

    newDTCStatusSt.DTCStatus        = DEM_DTCSTATUS_BYTE_ALL_OFF;
    newDTCStatusSt.ExtendDTCStatus  = DEM_DTCSTATUSEX_BYTE_ALL_OFF;
    newDTCStatusSt.ExtendDTCStatus2 = DEM_DTCSTATUSEX2_BYTE_ALL_OFF;

    /* Execute event status setting processing */
    updateDataFlag = Dem_Event_SetQualificationInfo_Specific( EventCtrlIndex, EventStatus, &eventQualification );    /* [UpdRec]AltIUMPR */

    if( ResultOfCheckSpecificFault == (boolean)TRUE )
    {
        /*  check failure cycle counter increment condition.    */
        if ( EventStatus == DEM_EVENT_STATUS_FAILED )
        {
            /*  increment failure cycle counter.            */
            Dem_Data_IncrementFailureCounterOfTmp();
            updateTmpAreaFlag   = (boolean)TRUE;
        }
        Dem_Data_GetDTCStatusStructFromTmp( &tmpDTCStatusSt );
        tmpOldExtendDTCStatus = tmpDTCStatusSt.ExtendDTCStatus;
        tmpNewExtendDTCStatus = Dem_DTC_ExDTC_SetPredictiveFaultBit( tmpOldExtendDTCStatus );
        tmpDTCStatusSt.ExtendDTCStatus  =   tmpNewExtendDTCStatus;
        Dem_Data_SetDTCStatusStructToTmp( &tmpDTCStatusSt );
    }

    /* Gets DTC status from the temporary domain. */
    Dem_Data_GetDTCStatusStructFromTmp( &oldDTCStatusSt );

#if ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )  /* [FuncSw] */
    /* check event occurrence counter increment condition.  */
    if ( EventStatus == DEM_EVENT_STATUS_FAILED )
    {
        if( ( oldDTCStatusSt.DTCStatus & DEM_UDS_STATUS_TF ) != DEM_UDS_STATUS_TF )     /*  statusOfDTC : bit0  */
        {
            /* increment event occurrence counter.  */
            Dem_Data_IncrementEventOccurrenceCounterOfTmp();
            updateTmpAreaFlag   = (boolean)TRUE;
        }
    }
#endif  /* ( DEM_GETOCCURRENCECOUNTER_SUPPORT == STD_ON )       */

    if( updateDataFlag == (boolean)TRUE )
    {
        /* When there is an event to be updated */
        /* Execute DTC status change processing */
        retChangeDTC = Dem_DTC_ChangeDTCStatus( EventStrgIndex, eventQualification, (boolean)FALSE, &oldDTCStatusSt, &newDTCStatusSt, &occurFlag );
    }
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    /* If misfire event, update cylinder Infomation */
    Dem_Misfire_UpdateCylinderInfo( EventStrgIndex, eventQualification, newDTCStatusSt.DTCStatus, SpecificConditionPtr->MisfireInfo.MisfireCylinder );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    if( retChangeDTC == DEM_IRT_OK )
    {
        updateTmpAreaFlag           = (boolean)FALSE;
        /* When DTC status change is successful */
        if( eventQualification == DEM_EVENT_QUALIFICATION_FAILED )
        {
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            Dem_Similar_ClearPendingEraseCycCntOfTmp();                /* Clear pending erase cycle counter of temporary area */
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */

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
            retEventRetntion = DEM_IRT_OK;                /* PASSED or NOTQUALIFIED */
        }
        eventId =   ((Dem_EventIdType)0x0000U);
        (void)Dem_CfgInfoPm_CnvEventCtrlIndexToEventId( EventCtrlIndex, &eventId ); /* no return check required */                          /* [GUD:RET:DEM_IRT_OK]EventCtrlIndex */
        monitorData0 = ( (Dem_MonitorDataType)eventId ) | DEM_MONITORDATA_SPECIFICEVENTSTATUS;            /* Calc monitorData */

        /* Update statusOfDTC bit2, bit3, bit7 */
        Dem_DTC_UpdateDTCStatusByRetentionResult( EventStrgIndex, EventStatus, retEventRetntion, occurFlag.ConfirmedOccurFlag, SpecificConditionPtr->MisfireInfo.MisfireCylinder, &oldDTCStatusSt,  &newDTCStatusSt );
        Dem_Control_UpdateEventRelatedData( EventStrgIndex, EventStatus, monitorData0, faultOccurrenceFlag, oldDTCStatusSt.DTCStatus, newDTCStatusSt.DTCStatus, SpecificConditionPtr->MisfireInfo.MisfireCylinder );
        Dem_Control_UpdateEventMemoryEntryFromTmp( DEM_EVTKINDPTN_PRIMEM_SPECIFIC, EventStatus );
        UpdEvtCtrlFlagStPtr->TSFFDeleteFlag = Dem_Data_CheckTSFFDeleteByFFROverwritten();
#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )     /*  [FuncSw]    */
        Dem_Control_RemovePrestoredFreezeFrame( EventStrgIndex, EventStatus, oldDTCStatusSt.DTCStatus, newDTCStatusSt.DTCStatus );
#endif  /*   ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )                */

        Dem_DTC_TranslateDTCStatusAfterUpdate( EventCtrlIndex, &oldDTCStatusSt.DTCStatus, &newDTCStatusSt.DTCStatus );
        Dem_CfgInfoPm_TriggerEventStatusChangedFnc( EventCtrlIndex, oldDTCStatusSt.DTCStatus, newDTCStatusSt.DTCStatus );
    }
    else
    {
        /* When DTC status change is failure */
        if( tmpOldExtendDTCStatus != tmpNewExtendDTCStatus )
        {
            updateTmpAreaFlag   =   (boolean)TRUE;                /* Update EventMemoryEntry, Misfire, Similar */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
#if ( DEM_PFC_SUPPORT == STD_ON )               /*  [FuncSw]    */
            updateTmpAreaMisfirePFCFlag =   (boolean)TRUE;                /* Update permanent cylinder */
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )                      */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
        }
        else
        {
            /* Update Misfire, Similar */
            updateTmpAreaSpecificFlag   =   (boolean)TRUE;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
#if ( DEM_PFC_SUPPORT == STD_ON )               /*  [FuncSw]    */
            updateTmpAreaMisfirePFCFlag =   (boolean)TRUE;
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )                      */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
        }
    }
    UpdateTmpAreaStPtr->UpdateTmpAreaFlag           =   updateTmpAreaFlag;
    UpdateTmpAreaStPtr->UpdateTmpAreaSpecificFlag   =   updateTmpAreaSpecificFlag;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
#if ( DEM_PFC_SUPPORT == STD_ON )               /*  [FuncSw]    */
    UpdateTmpAreaStPtr->UpdateTmpAreaMisfirePFCFlag =   updateTmpAreaMisfirePFCFlag;
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )                      */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_SaveSpecificEventMemoryEntryToTmp            */
/* Description   | Saves an specific event memory entry by event index to   */
/*               |  temporary area.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The Saving is successful.            */
/*               |        DEM_IRT_NG : The Saving is failed.                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SaveSpecificEventMemoryEntryToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSaveEventTemp;
#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSavePFCTemp;
#endif  /*  ( DEM_PFC_SUPPORT == STD_ON )          */

    retVal = DEM_IRT_NG;

    retSaveEventTemp = Dem_Data_SaveEventMemoryEntryToTmp( EventStrgIndex );
    if( retSaveEventTemp == DEM_IRT_OK )
    {
#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
        retSavePFCTemp = Dem_DTC_SavePermanentMemoryEntryToTmp( EventStrgIndex );
        if( retSavePFCTemp == DEM_IRT_OK )
#endif  /*  ( DEM_PFC_SUPPORT == STD_ON )          */
        {
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
             Dem_Similar_SaveEventMemoryEntryToTmp( EventStrgIndex );
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )           */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
             Dem_Misfire_SaveEventMemoryEntryToTmp( EventStrgIndex );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

             retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_Control_CheckSpecificTypeSetEvent                    */
/* Description   | Check set event for specific event.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Parameters    | [in] EventStatus :                                       */
/* Parameters    | [in] SpecificConditionPtr :                              */
/* Parameters    | [out] ResultOfCheckSpecificfaultPtr :                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckSpecificTypeSetEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfCheckSpecificfaultPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    if( EventStatus == DEM_EVENT_STATUS_PASSED )
    {
        /* EVENT_STATUS_PASSED */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        /* Similar condition check at the time of passed */
        Dem_Similar_CheckPassedCondition( &SpecificConditionPtr->SimilarConditionArray[0] );/* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / 0 */
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */

        retVal = DEM_IRT_OK;
        *ResultOfCheckSpecificfaultPtr = (boolean)FALSE;
    }
    else
    {
        /* EVENT_STATUS_FAILED */
        retVal  =   Dem_Control_CheckSpecificTypeSetEvent_Failed( EventStrgIndex, SpecificConditionPtr, ResultOfCheckSpecificfaultPtr );
    }

    return retVal;
}


#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_CheckSpecificTypeSetEvent_Failed             */
/* Description   | Check set event for specific event.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Parameters    | [in] EventStatus :                                       */
/* Parameters    | [in] SpecificConditionPtr :                              */
/* Parameters    | [out] ResultOfCheckSpecificfaultPtr :                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckSpecificTypeSetEvent_Failed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfCheckSpecificfaultPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;

    /* EVENT_STATUS_FAILED */
    eventKind   =   Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp( EventStrgIndex );
    if (( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
    {
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        /* MisfireEvent */
        if (( eventKind & DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT )
        {
            /* CAT */
            retVal = Dem_Control_CheckCATFailedCondition( EventStrgIndex, SpecificConditionPtr, ResultOfCheckSpecificfaultPtr );
        }
        else
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */
        {
            /* Emission */
            retVal = Dem_Control_CheckEmissionFailedCondition( EventStrgIndex, SpecificConditionPtr, ResultOfCheckSpecificfaultPtr );
        }
    }
    else
    {
        /* Other than MisfireEvent */
        retVal = Dem_Control_CheckSimilarFailedCondition( EventStrgIndex, &SpecificConditionPtr->SimilarConditionArray[0], ResultOfCheckSpecificfaultPtr );/* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / 0 */
    }
    return retVal;
}
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Control_CheckSpecificTypeSetEvent_Failed             */
/* Description   | Check set event for specific event.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Parameters    | [in] EventStatus :                                       */
/* Parameters    | [in] SpecificConditionPtr :                              */
/* Parameters    | [out] ResultOfCheckSpecificfaultPtr :                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckSpecificTypeSetEvent_Failed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfCheckSpecificfaultPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_EventKindType, AUTOMATIC ) eventKind;

    /* EVENT_STATUS_FAILED */
    eventKind   =   Dem_CfgInfoPm_GetEventKindOfSpecific_InEvtStrgGrp( EventStrgIndex );
    if (( eventKind & DEM_EVTKIND_TYPE_MISFIRE_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_EVENT )
    {
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        /* MisfireEvent */
        if (( eventKind & DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) == DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT )
        {
            /* CAT */
            retVal = Dem_Control_CheckCATFailedCondition( EventStrgIndex, SpecificConditionPtr, ResultOfCheckSpecificfaultPtr );
        }
        else
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */
        {
            /* Emission */
            retVal = Dem_Control_CheckEmissionFailedCondition( EventStrgIndex, SpecificConditionPtr, ResultOfCheckSpecificfaultPtr );
        }
    }
    else
    {
        retVal  =   DEM_IRT_NG;
    }

    return retVal;
}
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_OFF )  */
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Control_CheckSpecificTypeSetEvent_Failed             */
/* Description   | Check set event for specific event.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Parameters    | [in] EventStatus :                                       */
/* Parameters    | [in] SpecificConditionPtr :                              */
/* Parameters    | [out] ResultOfCheckSpecificfaultPtr :                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckSpecificTypeSetEvent_Failed
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfCheckSpecificfaultPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* EVENT_STATUS_FAILED */
    retVal = Dem_Control_CheckSimilarFailedCondition( EventStrgIndex, &SpecificConditionPtr->SimilarConditionArray[0], ResultOfCheckSpecificfaultPtr );/* [ARYCHK] DEM_SIT_R_CHK_SIMILAR_CONDITION_ARRAY_SIZE / 1 / 0 */

    return retVal;
}
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_OFF )  */


#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_CheckEmissionFailedCondition                 */
/* Description   | Check failed condition for Emission.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Parameters    | [in] SpecificConditionPtr :                              */
/* Parameters    | [out] ResultOfCheckSpecificfaultPtr :                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckEmissionFailedCondition
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfCheckSpecificfaultPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChkExcessCond;
    VAR( boolean, AUTOMATIC ) retCheckPredictiveFaultStatus;
    VAR( Dem_DTCStatusStType, AUTOMATIC ) dtcStatusSt;

    *ResultOfCheckSpecificfaultPtr = (boolean)FALSE;
    retVal = DEM_IRT_NG;

    Dem_Data_GetDTCStatusStructFromTmp( &dtcStatusSt );
    retCheckPredictiveFaultStatus = Dem_DTC_CheckExtendDTCStatus( dtcStatusSt.ExtendDTCStatus, DEM_DTCSTATUSEX_STATUS_PREDICTIVE_FAULT );
    if( retCheckPredictiveFaultStatus == (boolean)FALSE )
    {
        /* No failure has occurred. */

        if( SpecificConditionPtr->MisfireInfo.MisfireCondition == DEM_MISFIRE_WITHIN_FIRST1000RPM )
        {
            /* Within First1000RPM */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            /* Latch the similar condition */
            Dem_Similar_SetConditionLatchedToTmp( &SpecificConditionPtr->SimilarConditionArray[0] );/* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / 0 */
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */

            *ResultOfCheckSpecificfaultPtr = (boolean)TRUE;
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* After First1000RPM */

            /* Check the excess counter threshold exceeded */
            retChkExcessCond = Dem_Misfire_CheckReachedExcessCntThresholdFromTmp( EventStrgIndex );
            if( retChkExcessCond == DEM_IRT_OK )
            {
                /* Reached excess counter threshold */
                *ResultOfCheckSpecificfaultPtr = (boolean)TRUE;
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                Dem_Similar_ReachedExcessCntThreshold( EventStrgIndex, &SpecificConditionPtr->SimilarConditionArray[0], ResultOfCheckSpecificfaultPtr );/* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / 0 */
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
                retVal = DEM_IRT_OK;
            }
            else
            {
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                /* Not reached excess counter threshold */
                Dem_Similar_NotReachedExcessCntThreshold( EventStrgIndex, &SpecificConditionPtr->SimilarConditionArray[0] );/* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / 0 */
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
            }
        }
    }
    else
    {
        /* Failure has occurred. */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_CheckCATFailedCondition                      */
/* Description   | Check failed condition for CAT.                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Parameters    | [in] SpecificConditionPtr :                              */
/* Parameters    | [out] ResultOfCheckSpecificfaultPtr :                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckCATFailedCondition
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfCheckSpecificfaultPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChkExcessCond;
    VAR( boolean, AUTOMATIC ) retCheckPredictiveFaultStatus;
    VAR( boolean, AUTOMATIC ) specificFault;
    VAR( Dem_DTCStatusStType, AUTOMATIC ) dtcStatusSt;

    *ResultOfCheckSpecificfaultPtr = (boolean)FALSE;
    retVal = DEM_IRT_NG;

    Dem_Data_GetDTCStatusStructFromTmp( &dtcStatusSt );
    retCheckPredictiveFaultStatus = Dem_DTC_CheckExtendDTCStatus( dtcStatusSt.ExtendDTCStatus, DEM_DTCSTATUSEX_STATUS_PREDICTIVE_FAULT );

    if( retCheckPredictiveFaultStatus == (boolean)FALSE )
    {
       /* No failure has occurred. */

       if( ( dtcStatusSt.DTCStatus & DEM_UDS_STATUS_WIR )== DEM_UDS_STATUS_WIR )    /*  statusOfDTC : bit7  */
       {
           /* Bit7:ON */
           *ResultOfCheckSpecificfaultPtr = (boolean)TRUE;
           retVal = DEM_IRT_OK;
       }
       else
       {
           /* Bit7:OFF */
           specificFault = Dem_Control_CheckSpecificFault();
           if( specificFault == (boolean)TRUE )
           {
               /* Similar condition update to the previous DCY or pending failure of Emission */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
               /* Latch the similar condition */
               Dem_Similar_SetConditionLatchedToTmp( &SpecificConditionPtr->SimilarConditionArray[0] );/* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / 0 */
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */

               *ResultOfCheckSpecificfaultPtr = (boolean)TRUE;
               retVal = DEM_IRT_OK;

           }
           else
           {
               /* No similar condition update to the previous DCY and No pending failure of Emission */

               if( ( dtcStatusSt.DTCStatus & DEM_UDS_STATUS_PDTC ) == DEM_UDS_STATUS_PDTC ) /*  statusOfDTC : bit2  */
               {
                   /* Bit2:ON */
                   /* Judge similar condition with similar condtion stored check */
                    *ResultOfCheckSpecificfaultPtr = (boolean)TRUE;
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                   Dem_Similar_JudgeConditionWithCheckStored( EventStrgIndex, &SpecificConditionPtr->SimilarConditionArray[0], ResultOfCheckSpecificfaultPtr );/* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / 0 */
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
                   retVal = DEM_IRT_OK;
               }
               else
               {
                   /* Bit2:OFF */
                   if( SpecificConditionPtr->MisfireInfo.MisfireCondition == DEM_MISFIRE_DURING_FTPCYCLE )
                   {
                       /* During FTPCycle */

                       /* Check the excess counter threshold exceeded */
                       retChkExcessCond = Dem_Misfire_CheckReachedExcessCntThresholdFromTmp( EventStrgIndex );
                       if( retChkExcessCond == DEM_IRT_OK )
                       {
                           /* Reached excess counter threshold */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                           /* Store similar condition of Pending */
                           Dem_Similar_ConditionStoredPending( &SpecificConditionPtr->SimilarConditionArray[0] );/* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / 0 */
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
                           *ResultOfCheckSpecificfaultPtr = (boolean)TRUE;
                           retVal = DEM_IRT_OK;
                       }
                       else
                       {
                           /* Not reached excess counter threshold */
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                           /* Store similar condition of first exceedance */
                           Dem_Similar_ConditionStoredFirstExceedance( EventStrgIndex, &SpecificConditionPtr->SimilarConditionArray[0] );/* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / 0 */
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
                       }
                   }
                   else
                   {
                       /* Outof FTPCycle */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                       /* Latch the similar condition */
                       Dem_Similar_SetConditionLatchedToTmp( &SpecificConditionPtr->SimilarConditionArray[0] );/* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / 0 */
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */

                       *ResultOfCheckSpecificfaultPtr = (boolean)TRUE;
                       retVal = DEM_IRT_OK;
                   }
               }
           }
       }
    }
    else
    {
        /* Failure has occurred. */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_CheckSpecificFault                           */
/* Description   | Check specific fault.                                    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE :                                            */
/*               |        FALSE :                                           */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Control_CheckSpecificFault
( void )
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) pendingFault;
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) similarConditionStoreBeforeDcy;
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */

    retVal = (boolean)FALSE;

    pendingFault    =   Dem_Misfire_GetPendingStoreOfEmission();
    if( pendingFault == (boolean)TRUE )
    {
        /* Pending failure of Emission */
        retVal = (boolean)TRUE;
    }

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Similar_GetConditionStoreBeforeDcyToTmp( &similarConditionStoreBeforeDcy );
    if( similarConditionStoreBeforeDcy == (boolean)TRUE )
    {
        /* Similar condition update to the previous DCY */
        retVal = (boolean)TRUE;
    }
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */

    return retVal;
}
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )     */
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )       */

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_CheckSimilarFailedCondition                  */
/* Description   | Check failed condition for Similar.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] SimilarConditionPtr :                               */
/*               | [out] ResultOfCheckSpecificfaultPtr :                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckSimilarFailedCondition
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionPtr,    /* MISRA DEVIATION */
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ResultOfCheckSpecificfaultPtr
)
{
    VAR( boolean, AUTOMATIC ) retCheckPredictiveFaultStatus;
    VAR( boolean, AUTOMATIC ) chkGetSimilarCondStored;
    VAR( boolean, AUTOMATIC ) similarConditionStoreBeforeDcy;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChkExcessCond;
    VAR( Dem_DTCStatusStType, AUTOMATIC ) dtcStatusSt;

    retVal = DEM_IRT_OK;
    *ResultOfCheckSpecificfaultPtr = (boolean)FALSE;

    Dem_Data_GetDTCStatusStructFromTmp( &dtcStatusSt );
    retCheckPredictiveFaultStatus = Dem_DTC_CheckExtendDTCStatus( dtcStatusSt.ExtendDTCStatus, DEM_DTCSTATUSEX_STATUS_PREDICTIVE_FAULT );

    if( retCheckPredictiveFaultStatus == (boolean)FALSE )
    {
        /* No failure has occurred. */

        /* Check the excess counter threshold exceeded */
        retChkExcessCond = Dem_Similar_CheckReachedExcessCntThresholdFromTmp( EventStrgIndex );
        if( retChkExcessCond == DEM_IRT_OK )
        {
            /* Reached excess counter threshold */

            Dem_Similar_GetConditionStoredflgToTmp( &chkGetSimilarCondStored );
            if( chkGetSimilarCondStored == (boolean)TRUE )
            {
                Dem_Similar_GetConditionStoreBeforeDcyToTmp( &similarConditionStoreBeforeDcy );
                if( similarConditionStoreBeforeDcy == (boolean)TRUE )
                {
                    /* Similar condition update to the previous DCY */
                    *ResultOfCheckSpecificfaultPtr = (boolean)TRUE;
                }
                else
                {
                    /* No similar condition update to the previous DCY */
                    /* Judge similar condition */
                    Dem_Similar_JudgeCondition( EventStrgIndex, SimilarConditionPtr, ResultOfCheckSpecificfaultPtr );
               }
            }
            else
            {
                /* Latch the similar condition */
                Dem_Similar_SetConditionLatchedToTmp( SimilarConditionPtr );

                *ResultOfCheckSpecificfaultPtr = (boolean)TRUE;
            }
        }
        else
        {
            /* Not reached excess counter threshold */
            retVal = DEM_IRT_NG;
        }
    }
    else
    {
        /* Failure has occurred. */
        /* No process */
    }

    return retVal;
}
#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )   */


/****************************************************************************/
/* Function Name | Dem_Control_ConvertSpecificEventReqData                  */
/* Description   | Convert specific event requeest data.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] DataBuffPtr : The pointer of the data buffer.       */
/*               | [out] EventStatusPtr :                                   */
/*               | [out] SpecificConditionPtr :                             */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_ConvertSpecificEventReqData
(
    P2CONST( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr,
    P2VAR( Dem_EventStatusType, AUTOMATIC, AUTOMATIC ) EventStatusPtr,
    P2VAR( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr
)
{
    /* EventStatus */
    *EventStatusPtr = (Dem_EventStatusType)DataBuffPtr[DEM_SPCEVT_DATABUF_EVENTSTATUS];/* [ARYCHK] DEM_ASYNCDATAQUE_SPEC_EVENT_ITEMSIZE / 1 / DEM_SPCEVT_DATABUF_EVENTSTATUS */

    /* MisfireCylinder */
    SpecificConditionPtr->MisfireInfo.MisfireCylinder = (Dem_MisfireCylinderType) ( ( (uint16)DataBuffPtr[DEM_SPCEVT_DATABUF_MISFIRECYLINDER_0] )               |/* [ARYCHK] DEM_ASYNCDATAQUE_SPEC_EVENT_ITEMSIZE / 1 / DEM_SPCEVT_DATABUF_MISFIRECYLINDER_0 */
                                                                                      (uint16)( ( (uint16)DataBuffPtr[DEM_SPCEVT_DATABUF_MISFIRECYLINDER_1] ) << DEM_SPCEVT_BITSHIFT_8 ) );/* [ARYCHK] DEM_ASYNCDATAQUE_SPEC_EVENT_ITEMSIZE / 1 / DEM_SPCEVT_DATABUF_MISFIRECYLINDER_1 */

    /* MisfireCondition */
    SpecificConditionPtr->MisfireInfo.MisfireCondition = (Dem_MisfireConditionType)DataBuffPtr[DEM_SPCEVT_DATABUF_MISFIRECONDITION];/* [ARYCHK] DEM_ASYNCDATAQUE_SPEC_EVENT_ITEMSIZE / 1 / DEM_SPCEVT_DATABUF_MISFIRECONDITION */

    /* SimilarCondition */
    Dem_UtlSimilar_CnvBinaryToSimilarConditionArray( &SpecificConditionPtr->SimilarConditionArray[0], &DataBuffPtr[DEM_SPCEVT_DATABUF_SIMILARCONDITION] );/* [ARYCHK] DEM_SIT_R_CHK_SIMILAR_CONDITION_ARRAY_SIZE / 1 / 0 *//* [ARYCHK] DEM_ASYNCDATAQUE_SPEC_EVENT_ITEMSIZE / 1 / DEM_SPCEVT_DATABUF_SIMILARCONDITION */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_SetSpecificEventReqData                      */
/* Description   | Set specific event request data.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStatus : Monitor test result..                 */
/*               | [in] SpecificConditionPtr : Specific condition of event. */
/*               | [out] DataBuffPtr : The pointer of the data buffer.      */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_SetSpecificEventReqData
(
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, DEM_APPL_DATA ) SpecificConditionPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
)
{
    VAR( uint8, AUTOMATIC )  dummyIndex;
    VAR( uint8, AUTOMATIC ) dummyItemSize;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) misfireCylinder;

    dummyIndex = (uint8)(DEM_SPCEVT_DATABUF_SIMILARCONDITION + Dem_AsyncDataQueSpecEventSimilarItemSize);
    dummyItemSize = DEM_ASYNCDATAQUE_ITEMSIZE_MAX - Dem_AsyncDataQueSpecEventItemSize;

    /* EventStatus */
    DataBuffPtr[DEM_SPCEVT_DATABUF_EVENTSTATUS] = EventStatus;/* [ARYCHK] DEM_ASYNCDATAQUE_ITEMSIZE_MAX / 1 / DEM_SPCEVT_DATABUF_EVENTSTATUS */

    /* MisfireCylinder */
    misfireCylinder = SpecificConditionPtr->MisfireInfo.MisfireCylinder;
    DataBuffPtr[DEM_SPCEVT_DATABUF_MISFIRECYLINDER_0] = (uint8)( misfireCylinder );/* [ARYCHK] DEM_ASYNCDATAQUE_ITEMSIZE_MAX / 1 / DEM_SPCEVT_DATABUF_MISFIRECYLINDER_0 */
    DataBuffPtr[DEM_SPCEVT_DATABUF_MISFIRECYLINDER_1] = (uint8)( ((uint16)misfireCylinder) >> DEM_SPCEVT_BITSHIFT_8);/* [ARYCHK] DEM_ASYNCDATAQUE_ITEMSIZE_MAX / 1 / DEM_SPCEVT_DATABUF_MISFIRECYLINDER_1 */
    /* MisfireCondition */
    DataBuffPtr[DEM_SPCEVT_DATABUF_MISFIRECONDITION] = SpecificConditionPtr->MisfireInfo.MisfireCondition;/* [ARYCHK] DEM_ASYNCDATAQUE_ITEMSIZE_MAX / 1 / DEM_SPCEVT_DATABUF_MISFIRECONDITION */

    /* SimilarCondition */
    Dem_UtlSimilar_CnvSimilarConditionArrayToBinary( &DataBuffPtr[DEM_SPCEVT_DATABUF_SIMILARCONDITION], &SpecificConditionPtr->SimilarConditionArray[0] );/* [ARYCHK] DEM_ASYNCDATAQUE_ITEMSIZE_MAX / 1 / DEM_SPCEVT_DATABUF_SIMILARCONDITION *//* [ARYCHK] DEM_SIT_R_CHK_SIMILAR_CONDITION_ARRAY_SIZE / 1 / 0 */

    /* Dummy */
    if( dummyItemSize != (uint16)0U )
    {
        Dem_UtlMem_SetMemory( &DataBuffPtr[dummyIndex], (uint8)0U, (uint16)dummyItemSize );/* [ARYCHK] DEM_ASYNCDATAQUE_ITEMSIZE_MAX / 1 / dummyIndex */
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Control_CheckEventStatusForSpecificEvent             */
/* Description   | Check event status.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStatus :                                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckEventStatusForSpecificEvent
(
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    retVal = DEM_IRT_NG;

    switch( EventStatus )
    {
        case DEM_EVENT_STATUS_PASSED:
        case DEM_EVENT_STATUS_FAILED:
        case DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED:
            retVal = DEM_IRT_OK;
            break;
        default:
            /* Out of range */
            break;
    }
    return retVal;

}


/****************************************************************************/
/* Function Name | Dem_Control_SpecificPredictiveFFDProcess                 */
/* Description   | PredictiveFFD process.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               | [in] EventStrgIndex :                                    */
/*               | [in] SpecificConditionPtr :                              */
/*               | [out] UpdEvtCtrlFlagStPtr :                              */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_SpecificPredictiveFFDProcess
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( Dem_SpecificEventConditionType, AUTOMATIC, AUTOMATIC ) SpecificConditionPtr,
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
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;

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
        /* Calc monitorData */
        eventId =   ((Dem_EventIdType)0x0000U);
        (void)Dem_CfgInfoPm_CnvEventCtrlIndexToEventId( EventCtrlIndex, &eventId ); /* no return check required */                          /* [GUD:RET:DEM_IRT_OK]EventCtrlIndex */
        monitorData0 = ( (Dem_MonitorDataType)eventId ) | DEM_MONITORDATA_SPECIFICEVENTSTATUS;

        /* Secure a new FaultRecord or FaultRecord secured. */
        Dem_Control_UpdateEventRelatedData( EventStrgIndex, DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED, monitorData0, faultOccurrenceFlag, DEM_DTCSTATUS_BYTE_DEFAULT, DEM_DTCSTATUS_BYTE_DEFAULT, SpecificConditionPtr->MisfireInfo.MisfireCylinder );

        /* Check if PredictiveFFD is stored. */
        retCheckStorePredictiveFFD = Dem_Data_CheckStorePredictiveFFDOfTmp( EventStrgIndex );
        if( retCheckStorePredictiveFFD == DEM_IRT_OK )
        {
            /* Checks if fault record will be overwritten. */
            UpdEvtCtrlFlagStPtr->FaultRecordOverwriteFlag = Dem_Data_CheckFaultRecordOverwrite( &( UpdEvtCtrlFlagStPtr->EventStrgIndexOfFaultRecordOverwritten ), &( UpdEvtCtrlFlagStPtr->OldDTCStatusOverwritten) );

            Dem_Control_UpdateEventMemoryEntryFromTmp( DEM_EVTKINDPTN_PRIMEM_SPECIFIC, DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED );
            UpdEvtCtrlFlagStPtr->TSFFDeleteFlag = Dem_Data_CheckTSFFDeleteByFFROverwritten();
        }
    }

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )     /*  [FuncSw]    */
    Dem_Control_RemovePrestoredFreezeFrame( EventStrgIndex, DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED, DEM_DTCSTATUS_BYTE_DEFAULT, DEM_DTCSTATUS_BYTE_DEFAULT);
#endif  /*   ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )            */

    return ;
}

#if ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_UpdateProgressEngine1000RPM                  */
/* Description   | update progress engine 1000rpm .                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Control_UpdateProgressEngine1000RPM
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfireEmissionEventStrgIndex;
    misfireEmissionEventStrgIndex   =   Dem_CfgInfoPm_GetEventStrgIndex_MisfireEmission();

    if ( EventStrgIndex == misfireEmissionEventStrgIndex )
    {
        if( ( EventStatus == DEM_EVENT_STATUS_FAILED ) || ( EventStatus == DEM_EVENT_STATUS_PASSED ) )
        {
            /*  update progress engine rpm condition.    */
            Dem_OpCycle_UpdateProgressEngine1000RPM();
        }
    }
    return ;
}
#endif  /* ( DEM_CHECK_4000RPMOCCURRED_BY_EMISSION_SUPPORT == STD_ON )          */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_SPECIFIC_EVENT_SUPPORT -STD_ON- */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
