/* Dem_UdmControl_EventEntry_c(v5-5-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmControl_EventEntry/CODE                            */
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
#include "../../../inc/Dem_Udm_Control.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_Udm_Data.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"
#include "../../../usr/Dem_SavedZone_Callout.h"
#include "../../../usr/Dem_NotifyOverwrittenEventStatus_Callout.h"

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

static FUNC( void, DEM_CODE ) Dem_UdmControl_NotifyOverwrittenEventStatus
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndexOverwritten,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatusOverwritten,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatusOverwritten
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
/* Function Name | Dem_UdmControl_SetEventCommon                            */
/* Description   | Asynchronous processing function                         */
/*               |     of SetEventFailedWithSyncFreezeFrame                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex       : Index of the event table.    */
/*               | [in] EventStatus          : EventStatus                  */
/*               | [in] monitorData0         : Monitor test result          */
/* Return Value  | Dem_u08_AsyncExecReturnType :                            */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_UdmControl_SetEventCommon
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_EventStatusType, AUTOMATIC ) EventStatus,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSaveTemp;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retEventRetntion;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retTempVal;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldDTCStatus;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldDTCStatus2;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatus;
    VAR( boolean, AUTOMATIC ) faultOccurrenceFlag;
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) ffdCaptureFlag;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) triggerTestFailed;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberFreezeFrameRecords;

    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListIndexOverwritten;
    VAR( boolean, AUTOMATIC )      faultRecordOverwriteFlag;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldDtcStatusAtOverwritten;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDtcStatusAtOverwritten;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndexOverwritten;

    retTempVal = Dem_CfgInfoUdm_CnvEventCtrlIndexToUdmEventIndex( EventCtrlIndex, &udmEventIndex );     /* [GUD:RET:DEM_IRT_OK] udmEventIndex */

    if( retTempVal == DEM_IRT_OK )  /* [GUD:RET:DEM_IRT_OK]udmEventIndex */
    {
        if (( EventStatus == DEM_EVENT_STATUS_FAILED ) || ( EventStatus == DEM_EVENT_STATUS_FAILED_TO_PASSED ))
        {
            faultOccurrenceFlag             = (boolean)FALSE;
            ffdCaptureFlag      =   (boolean)FALSE;
            oldDTCStatus       = DEM_DTCSTATUS_BYTE_ALL_OFF;
            newDTCStatus       = DEM_DTCSTATUS_BYTE_ALL_OFF;

            faultRecordOverwriteFlag    =   (boolean)FALSE;
            udmEventIndexOverwritten    =   DEM_UDMEVENTINDEX_INVALID;
            oldDtcStatusAtOverwritten   =   DEM_DTCSTATUS_BYTE_ALL_OFF;
            newDtcStatusAtOverwritten   =   DEM_DTCSTATUS_BYTE_ALL_OFF;
            tsFFListIndexOverwritten    =   DEM_TSFFLISTINDEX_INVALID;

            /* Obtain a temporary area for event registration */
            retSaveTemp = Dem_UdmData_SaveEventMemoryEntryToTmp( udmEventIndex );                       /* [GUD] udmEventIndex */

            if( retSaveTemp == DEM_IRT_OK )
            {
                    /* Gets DTC status from the temporary domain. */
                Dem_UdmData_GetDTCStatusFromTmp( &oldDTCStatus );

                /* When there is an event to be updated */
                /* Execute DTC status change processing */
                Dem_UdmDTC_ChangeDTCStatus_ToFailed( udmEventIndex, oldDTCStatus, &newDTCStatus );      /* [GUD] udmEventIndex */

                /*--------------------------------------*/
                /*  notify SAVED_ZONE update - start.   */
                Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
                /*--------------------------------------*/
                {
                    /* When DTC status change is successful */
                    retEventRetntion = Dem_UdmData_SetFaultInfo( &faultOccurrenceFlag, &faultRecordOverwriteFlag, &udmEventIndexOverwritten, &oldDtcStatusAtOverwritten, &newDtcStatusAtOverwritten, &tsFFListIndexOverwritten );

                    /* Update statusOfDTC bit2, bit3, bit7 */
                    Dem_UdmDTC_UpdateDTCStatusByRetentionResult( retEventRetntion, &newDTCStatus );

                    /* get maxNumberFreezeFrameRecords in event. */
                    maxNumberFreezeFrameRecords = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( udmEventIndex );       /* [GUD] udmEventIndex */

                    if ( maxNumberFreezeFrameRecords > (Dem_u16_UdmFFDIndexType)0U )
                    {
                        /*  set related data(freezeFrame) to temporary area.    */
                        /*  check change trigger : testFailed bit.      */
                        triggerTestFailed   =   oldDTCStatus ^ newDTCStatus;
                        if (( triggerTestFailed & DEM_UDS_STATUS_TF ) == DEM_UDS_STATUS_TF )
                        {
                            if ( ( newDTCStatus & DEM_UDS_STATUS_TF ) == DEM_UDS_STATUS_TF )
                            {
                                /*  OFF => ON trigger                   */
                                ffdCaptureFlag  =   (boolean)TRUE;
                            }
                        }
                    }

                    if ( EventStatus == DEM_EVENT_STATUS_FAILED_TO_PASSED )
                    {
                        /*  changed to passed.                                      */
                        oldDTCStatus2   =   newDTCStatus;
                        Dem_UdmDTC_ChangeDTCStatus_ToPassed( oldDTCStatus2, &newDTCStatus );
                    }

                    /* Set NewDTCStatus to temporary area */
                    Dem_UdmData_SetDTCStatusToTmp( newDTCStatus );

                    /*  set related data(freezeFrame) to temporary area.    */
                    if ( faultOccurrenceFlag == (boolean)TRUE )
                    {
                        if ( ffdCaptureFlag == (boolean)TRUE )
                        {
                            Dem_UdmData_CaptureFreezeFrame( udmEventIndex, monitorData0 );
                        }
                    }

                    /*  update data : temporary area to saved_zone area.    */
                    Dem_UdmData_UpdateEventMemoryEntryFromTmp( faultRecordOverwriteFlag, udmEventIndexOverwritten, newDtcStatusAtOverwritten, tsFFListIndexOverwritten );

                    /*  notify DTC status changed.              */
                    Dem_UdmDTC_TranslateDTCStatusAfterUpdate( udmEventIndex, &oldDTCStatus, &newDTCStatus );        /* [GUD] udmEventIndex */

                    /*  notify EventStatusChanged               */
                    Dem_CfgInfoUdm_TriggerEventStatusChangedFnc( udmEventIndex, oldDTCStatus, newDTCStatus );       /* [GUD] udmEventIndex */
                }
                /*--------------------------------------*/
                /*  notify SAVED_ZONE update - end.     */
                Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
                /*--------------------------------------*/

                if ( faultRecordOverwriteFlag == (boolean)TRUE )
                {
                    /*  overwritten                     */
                    Dem_UdmControl_NotifyOverwrittenEventStatus( udmEventIndexOverwritten, oldDtcStatusAtOverwritten, newDtcStatusAtOverwritten );
                }

            }
            else
            {
                /* When obtaining a temporary area is failure */
            }
        }
        else
        {
            /*----------------------------------*/
            /*  DEM_EVENT_STATUS_PASSED.        */
            /*----------------------------------*/
            /*  get current statusOfDTC         */
            ( void )Dem_UdmEventMngC_GetER_StatusOfDTC( udmEventIndex, &oldDTCStatus ); /* no return check required */  /* [GUD] udmEventIndex */

            /*  update DTC status               */
            Dem_UdmDTC_ChangeDTCStatus_ToPassed( oldDTCStatus, &newDTCStatus );

            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - start.   */
            Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
            /*--------------------------------------*/
            {
                /*  set new DTC status to record.   */
                Dem_UdmEventMngC_SetER_StatusOfDTC( udmEventIndex, newDTCStatus );                                      /* [GUD] udmEventIndex */

                /*  notify DTC status changed.              */
                Dem_UdmDTC_TranslateDTCStatusAfterUpdate( udmEventIndex, &oldDTCStatus, &newDTCStatus );                /* [GUD] udmEventIndex */

                /*  notify EventStatusChanged               */
                Dem_CfgInfoUdm_TriggerEventStatusChangedFnc( udmEventIndex, oldDTCStatus, newDTCStatus );               /* [GUD] udmEventIndex */
            }

            /*--------------------------------------*/
            /*  notify SAVED_ZONE update - end.     */
            Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
            /*--------------------------------------*/

        }
    }
    /* Set return value. */
    /* Fault record is No updated, No need re-generate orderlist, Continue asynchronous processing. */
    retVal = ( DEM_ASYNCRET_NOUPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    return retVal;

}


/*--------------------------------------------------------------------------*/
/* Unit Internal functions -data-                                           */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_UdmControl_GetNumberOfEventMemoryEntries             */
/* Description   | Gets NumberOfEventMemoryEntries from event memory relat- */
/*               | ed record.                                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCOrigin :                                         */
/*               |        select the source memory the number of entries s- */
/*               |        hall be read from                                 */
/*               | [out] NumberOfEventMemoryEntriesPtr :                    */
/*               |        Number of entries currently stored in the reques- */
/*               |        ted event memory                                  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful             */
/*               |        DEM_IRT_NG : Operation failed                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmControl_GetNumberOfEventMemoryEntries
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin,
    P2VAR( Dem_u08_OrderIndexType, AUTOMATIC, AUTOMATIC ) NumberOfEventMemoryEntriesPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retResult;
    VAR( Dem_UdmEventMemoryRecordType, AUTOMATIC ) eventMemoryRecord;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) numberOfEventMemoryEntries;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndexStart;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndexNum;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndexEnd;

    retVal  =   DEM_IRT_NG;
    numberOfEventMemoryEntries = ( Dem_u08_OrderIndexType )0U;

    /* Get udmInfoTableIndex from DTC Origin. */
    retResult = Dem_CfgInfoUdm_CnvDTCOriginToInternalInfoTableIndex( DTCOrigin, &udmInfoTableIndex );    /* [GUD:RET:DEM_IRT_OK]udmInfoTableIndex */

    if ( retResult == DEM_IRT_OK )
    {
        Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndex( udmInfoTableIndex, &udmGroupKindIndexStart, &udmGroupKindIndexNum );     /* [GUD]udmInfoTableIndex */
        udmGroupKindIndexEnd = udmGroupKindIndexStart + udmGroupKindIndexNum;

        for( udmGroupKindIndex = udmGroupKindIndexStart; udmGroupKindIndex < udmGroupKindIndexEnd; udmGroupKindIndex++ )    /* [GUD:for]udmGroupKindIndex */
        {
#ifndef     JGXSTACK
            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveEnterFnc();                          /* [GUD]udmGroupKindIndex */
#else       /* JGXSTACK */
            Dem_UdmExcEnterFnc_ForStack();
#endif      /* JGXSTACK */

            /* Get Record. */
            Dem_UdmEventMngC_GetEventMemoryRecord( udmGroupKindIndex, &eventMemoryRecord );     /* [GUD]udmGroupKindIndex */

#ifndef     JGXSTACK
            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveExitFnc();                           /* [GUD]udmGroupKindIndex */
#else       /* JGXSTACK */
            Dem_UdmExcExitFnc_ForStack();
#endif      /* JGXSTACK */

            /* Set NumberOfEventMemoryEntries per udm group. */
            numberOfEventMemoryEntries = numberOfEventMemoryEntries + eventMemoryRecord.NumberOfEventMemoryEntries;
        }
        /* Set NumberOfEventMemoryEntries. */
        *NumberOfEventMemoryEntriesPtr = numberOfEventMemoryEntries;

        retVal = DEM_IRT_OK;

    }

    return retVal;

}

/****************************************************************************/
/* Function Name | Dem_UdmControl_NotifyOverwrittenEventStatus              */
/* Description   | Nofify DTC status changed for Overwritten event.         */
/* Preconditions | Fault Record overwrite occurred.                         */
/* Parameters    | [in] UdmEventIndexOverwritten :                          */
/*               | [in] OldDTCStatusOverwritten :                           */
/*               | [in] NewDTCStatusOverwritten :                           */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmControl_NotifyOverwrittenEventStatus
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndexOverwritten,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) OldDTCStatusOverwritten,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) NewDTCStatusOverwritten
)
{
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) oldDTCStatusTmp;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) newDTCStatusTmp;

    oldDTCStatusTmp =   OldDTCStatusOverwritten;
    newDTCStatusTmp =   NewDTCStatusOverwritten;

    /*------------------------------------------*/
    /*  convert to output statusOfDTC.          */
    /*------------------------------------------*/
    Dem_DTC_CnvUpdateDTCStatus_ForOutput( &oldDTCStatusTmp, &newDTCStatusTmp );

    /*  convert event id.           */
    (void)Dem_CfgInfoUdm_CnvUdmEventIndexToEventId( UdmEventIndexOverwritten, &eventId );   /* no return check required */

    /*  Nofify DTC status changed for Overwritten event.        */
    Dem_NotifyOverwrittenEventStatus( eventId, oldDTCStatusTmp, newDTCStatusTmp );

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
