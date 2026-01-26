/* Dem_Control_EventEntry_PriMemCmn_c(v5-5-0)                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_EventEntry_PriMemCmn/CODE                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../inc/Dem_Pm_PreFFD.h"
#include "../../../usr/Dem_NotifyOverwrittenEventStatus_Callout.h"
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

static FUNC( Dem_u08_FFValidTriggerType, DEM_CODE ) Dem_Control_CheckTriggerByDTCStatus
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatus
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
/* Function Name | Dem_Control_ProcessEventRetention                        */
/* Description   | Sets Fault Event infomation to RAM.                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] OccurFlagPtr :                                      */
/*               |        When it shift to "Confirmed", TRUE is set.        */
/*               |        When it shift to "MIL", TRUE is set.              */
/*               | [out] FaultOccurrenceFlagPtr :                           */
/*               |        When temporary memory was changed, TRUE is set.   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : set of event was successful          */
/*               |        DEM_IRT_NG : set of event was failed              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ProcessEventRetention
(
    P2CONST( Dem_OrderListOccurredFlagType, AUTOMATIC, AUTOMATIC ) OccurFlagPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )      FaultOccurrenceFlagPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )         retSetFaultInfo;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )         retVal;

    retVal = DEM_IRT_NG;

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_Data_SelectEventEntryOverwrite();
#endif  /*   ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )           */

    retSetFaultInfo = Dem_Data_SetFaultInfo( OccurFlagPtr, FaultOccurrenceFlagPtr );

    if( retSetFaultInfo == DEM_IRT_OK )
    {
        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Control_UpdateEventRelatedData                       */
/* Description   | Update Data Related Fault Event.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        index of the event table                          */
/*               | [in] EventStatus :                                       */
/*               |        status of Event.                                  */
/*               | [in] monitorData0 :                                      */
/*               |        Monitor test result                               */
/*               | [in] FaultOccurrenceFlagPtr :                            */
/*               |        Trouble outbreak state flag                       */
/*               |          TRUE    : there is trouble.                     */
/*               |          FALSE   : there is no trouble.                  */
/*               | [in] OldDTCStatus :                                      */
/*               |        status of DTC before translation.                 */
/*               | [in] NewDTCStatus :                                      */
/*               |        status of DTC after translation.                  */
/*               | [in] MisfireCylinder :                                   */
/*               |        Misfire cylinder.                                 */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_UpdateEventRelatedData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )    EventStrgIndex,
    VAR( Dem_EventStatusType, AUTOMATIC )       EventStatus,
    VAR( Dem_MonitorDataType, AUTOMATIC )       monitorData0,
    VAR( boolean, AUTOMATIC )                   FaultOccurrenceFlag,
    VAR( Dem_UdsStatusByteType, AUTOMATIC )     OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC )     NewDTCStatus,
    VAR( Dem_MisfireCylinderType, AUTOMATIC )   MisfireCylinder
)
{
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) triggerCondition;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newStatus;

    if( FaultOccurrenceFlag == (boolean)TRUE )
    {
        if( EventStatus != DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED )
        {
            oldStatus = OldDTCStatus;
            newStatus = NewDTCStatus;

            /*------------------------------------------*/
            /*  convert to output statusOfDTC.          */
            /*------------------------------------------*/
            Dem_DTC_CnvUpdateDTCStatus_ForOutput( &oldStatus, &newStatus );
            triggerCondition = Dem_Control_CheckTriggerByDTCStatus( oldStatus, newStatus );
        }
        else
        {
            /* A trigger condition by predictive */
            triggerCondition = DEM_VALID_TRIGGER_FDC_THRESHOLD;
        }

        Dem_Data_CaptureFreezeFrame( EventStrgIndex, monitorData0, triggerCondition, MisfireCylinder );
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Control_SaveEventMemoryEntryToTmp                    */
/* Description   | Initializes clear info.                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The Saving is successful.            */
/*               |        DEM_IRT_NG : The Saving is failed.                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SaveEventMemoryEntryToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSaveEventTemp;
#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSavePFCTemp;
#endif  /*  ( DEM_PFC_SUPPORT == STD_OFF )          */

    retVal = DEM_IRT_NG;

    retSaveEventTemp = Dem_Data_SaveEventMemoryEntryToTmp( EventStrgIndex );
    if ( retSaveEventTemp == DEM_IRT_OK )
    {
#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
        retSavePFCTemp = Dem_DTC_SavePermanentMemoryEntryToTmp( EventStrgIndex );
        if ( retSavePFCTemp == DEM_IRT_OK )
#endif  /*  ( DEM_PFC_SUPPORT == STD_OFF )          */
        {
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_UpdateEventMemoryEntryFromTmp                */
/* Description   | Initializes clear info.                                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | This Function is in CheckClearDTCStatus exclusive sec..  */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_UpdateEventMemoryEntryFromTmp
(
    VAR( Dem_u08_EventKindPtnType, AUTOMATIC ) EventKindPattern     /* MISRA DEVIATION */
)
{

    Dem_Data_UpdateEventMemoryEntryFromTmp();

#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
    if ( EventKindPattern == DEM_EVTKINDPTN_PRIMEM_SPECIFIC )
    {
        Dem_DTC_UpdateSpecificPermanentMemoryEntryToTmp();
    }
    else
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */
    {
        /*  DEM_EVTKINDPTN_PRIMEM_NORMAL          */
        Dem_DTC_UpdatePermanentMemoryEntryToTmp();
    }
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )      */

    return ;
}


#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_NotifyOverwrittenEventStatus                 */
/* Description   | Nofify DTC status changed for Overwritten event.         */
/* Preconditions | Fault Record overwrite occurred.                         */
/* Parameters    | [in] EventStrgIndexOverwritten :                         */
/*               | [in] OldDTCStatusOverwritten :                           */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_NotifyOverwrittenEventStatus
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndexOverwritten,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatusOverwritten
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldDTCStatusTmp;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatusTmp;

    /*  get current statusofDTC.        */
    (void)Dem_Data_GetDTCStatus( EventStrgIndexOverwritten, &statusOfDTC );     /* no return check required */

    oldDTCStatusTmp =   OldDTCStatusOverwritten;
    newDTCStatusTmp =   statusOfDTC;

    /*------------------------------------------*/
    /*  convert to output statusOfDTC.          */
    /*------------------------------------------*/
    Dem_DTC_CnvUpdateDTCStatus_ForOutput( &oldDTCStatusTmp, &newDTCStatusTmp );

    eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( EventStrgIndexOverwritten );          /*  get EventCtrlIndex of EventStorageGroup max number  */
    eventCtrlIndex      =   Dem_CmbEvt_GetDelegateEventCtrlIndex_InEvtStrgGrp( EventStrgIndexOverwritten );    /*  get Delegate EventCtrlIndex                         */

    /*  set all qualification in event storage group to DEM_EVENT_QUALIFICATION_NOTQUALIFIED.   */
    for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
    {
        /*  convert event id.           */
        (void)Dem_CfgInfoPm_CnvEventCtrlIndexToEventId( eventCtrlIndex, &eventId );   /* no return check required */        /* [GUD:RET:DEM_IRT_OK]eventCtrlIndex */

        /*  Nofify DTC status changed for Overwritten event.        */
        Dem_NotifyOverwrittenEventStatus( eventId, oldDTCStatusTmp, newDTCStatusTmp );

        /*  get next Index.         */
        eventCtrlIndex  =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );
    }

    return ;
}
#endif /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_RemovePrestoredFreezeFrame                   */
/* Description   | Update Data Related Fault Event.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        index of the event table                          */
/*               | [in] EventStatus :                                       */
/*               |        status of Event.                                  */
/*               | [in] OldDTCStatus :                                      */
/*               |        status of DTC before translation.                 */
/*               | [in] NewDTCStatus :                                      */
/*               |        status of DTC after translation.                  */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Control_RemovePrestoredFreezeFrame
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )    EventStrgIndex,
    VAR( Dem_EventStatusType, AUTOMATIC )       EventStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC )     OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC )     NewDTCStatus
)
{
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) triggerCondition;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newStatus;
    VAR( boolean, AUTOMATIC ) enableRemoving;

    oldStatus = OldDTCStatus;
    newStatus = NewDTCStatus;

    /*------------------------------------------*/
    /*  convert to output statusOfDTC.          */
    /*------------------------------------------*/
    Dem_DTC_CnvUpdateDTCStatus_ForOutput( &oldStatus, &newStatus );

    enableRemoving = Dem_DTC_CheckRemovePrestoredFF( oldStatus, newStatus );
    if( enableRemoving == (boolean)FALSE )
    {
        if( EventStatus != DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED )
        {
            triggerCondition = Dem_Control_CheckTriggerByDTCStatus( oldStatus, newStatus );
        }
        else
        {
            /* A trigger condition by predictive */
            triggerCondition = DEM_VALID_TRIGGER_FDC_THRESHOLD;
        }

        enableRemoving = Dem_PreFFD_CheckTriggerToRemovePreFFD( EventStrgIndex, triggerCondition );
    }

    if( enableRemoving == (boolean)TRUE )
    {
        Dem_PreFFD_RemovePrestoredFreezeFrame( EventStrgIndex );
    }

    return ;
}
#endif  /* ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )          */

/****************************************************************************/
/* Function Name | Dem_Control_CheckTriggerByDTCStatus                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] OldDTCStatus :                                      */
/*               |        The last DTC status.                              */
/*               | [in] NewDTCStatus :                                      */
/*               |        This DTC status.                                  */
/* Return Value  | Dem_u08_FFValidTriggerType                               */
/*               |        An effective trigger condition.                   */
/*               |        The return value is the value that performed an   */
/*               |        OR-operation in the following macro.If a trigger  */
/*               |        condition is detected, macro and the DEM_VALID_T- */
/*               |        RIGGER_NONEOR operation corresponding to the tri- */
/*               |        gger condition are carried out.                   */
/*               |        DEM_VALID_TRIGGER_NONE :                          */
/*               |        DEM_VALID_TRIGGER_CONFIRMED :                     */
/*               |        DEM_VALID_TRIGGER_PENDING :                       */
/*               |        DEM_VALID_TRIGGER_TFTOC :                         */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_DTC_CheckTriggerByDTCStatus(v5-3-0).     */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_FFValidTriggerType, DEM_CODE ) Dem_Control_CheckTriggerByDTCStatus
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatus,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatus
)
{
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) retVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newStatus;

    retVal = DEM_VALID_TRIGGER_NONE;

    /*******************************************************/
    /* Judgment of the trigger condition by confirmed bit  */
    /*******************************************************/
    oldStatus = ( OldDTCStatus & ((Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC) );
    newStatus = ( NewDTCStatus & ((Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC) );

    if( newStatus > oldStatus )
    {
        /* A trigger condition by confirmed bit is concluded */
        retVal = DEM_VALID_TRIGGER_CONFIRMED;
    }

    /*******************************************************/
    /* Judgment of the trigger condition by pending bit    */
    /*******************************************************/
    oldStatus = ( OldDTCStatus & ((Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC) );
    newStatus = ( NewDTCStatus & ((Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC) );

    if( newStatus > oldStatus )
    {
        /* A trigger condition by pending bit is concluded */
        retVal |= DEM_VALID_TRIGGER_PENDING;
    }

    /*************************************************************************/
    /* Judgment of the trigger condition by TestFailedThisOperationCycle bit */
    /**************************************************************************/
    oldStatus = ( OldDTCStatus & ((Dem_UdsStatusByteType)DEM_UDS_STATUS_TFTOC) );
    newStatus = ( NewDTCStatus & ((Dem_UdsStatusByteType)DEM_UDS_STATUS_TFTOC) );

    if( newStatus > oldStatus )
    {
        /* A trigger condition by test failed this operation cycle bit is concluded */
        retVal |= DEM_VALID_TRIGGER_TFTOC;
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
