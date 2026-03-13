/* Dem_DataCtl_EventEntry_RecordUpdate_c(v5-9-0)                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_EventEntry_RecordUpdate/CODE                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "../../../inc/Dem_Pm_PreFFD.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_MonSts.h"
#include "../../../inc/Dem_Pm_Ind_MI.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "Dem_DataCtl_local.h"
#include "Dem_DataCtl_EventEntry_local.h"
#include "Dem_DataCtl_TSFFD_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_SetResultOfCmpObdFFRToTmp
(
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
);
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */

static FUNC( void, DEM_CODE ) Dem_Data_SetResultOfCmpFFRToTmp
(
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
);

static FUNC( void, DEM_CODE ) Dem_Data_LatchTmpEventMemoryData
(
    P2VAR( Dem_TmpEventMemoryEntryType, AUTOMATIC, DEM_VAR_NO_INIT ) TmpEventMemoryEntryStPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_EventRecordForCtlType, AUTOMATIC, AUTOMATIC ) EventRecordPtr,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, AUTOMATIC ) EventMemoryRecordPtr
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
/* Function Name | Dem_Data_UpdEvtMemEntryOfTmp_InitializeEvent             */
/* Description   | Clear trouble information, the freeze-frame of the       */
/*               | appointed event.                                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_UpdEvtMemEntryOfTmp_InitializeEvent
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retClearFaultRecord;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_EventRecordForCtlType, AUTOMATIC ) eventRecord;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;
    VAR( Dem_EventMemoryRecordType, AUTOMATIC ) eventMemoryRecord;

    /* Initialization of the automatic variable. */
    Dem_Data_LatchTmpEventMemoryData( &Dem_TmpEventMemoryEntry, &eventStrgIndex, &eventRecord, &faultRecord, &eventMemoryRecord );

    Dem_Data_SetResultOfCmpFFRToTmp( &faultRecord );

    /* Starts exclusion. */
    SchM_Enter_Dem_EventMemory();

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )     /*  [FuncSw]    */
    /*------------------------------------------*/
    /*  clear PreFFD.                           */
    /*------------------------------------------*/
    /* Removes pre-stored freeze frame corresponding to the event index. */
    /* PrestoreFreezeFrame exclusive section is controlled in this function. */
    Dem_PreFFD_RemovePrestoredFreezeFrame( eventStrgIndex );
#endif  /*   ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )            */

    /*------------------------------------------*/
    /*  clear freezeframe record.               */
    /*------------------------------------------*/
    Dem_Data_ClearFreezeFrameRecord( &faultRecord, &eventMemoryRecord );
#if ( DEM_OBDFFD_SUPPORT == STD_ON )        /*  [FuncSw]    */
    Dem_Data_ClearObdFreezeFrameRecord( &faultRecord, &eventMemoryRecord );
#endif  /*( DEM_OBDFFD_SUPPORT == STD_ON )                 */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )  /*  [FuncSw]    */
    Dem_Data_ClearTSFFListRecord( &faultRecord );
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )           */

    /*------------------------------------------*/
    /*  clear fault record.                     */
    /*------------------------------------------*/
    retClearFaultRecord = Dem_Data_ClearFaultRecord( eventRecord.FaultIndex );


    /*------------------------------------------*/
    /*  clear event record.                     */
    /*------------------------------------------*/
    Dem_DataMngC_InitEventCtlRecordData( &eventRecord );

    /*  set all clear event record.             */
    (void)Dem_DataMngC_SetEventRecord( eventStrgIndex, &eventRecord );  /* no return check required */

    /*------------------------------------------*/
    /*  decrement entry number.                 */
    /*------------------------------------------*/
    if( retClearFaultRecord == DEM_IRT_OK )
    {
        /* Subtracts 1 from number of event memory entries of event memory record of primary memory. */
        Dem_Data_SubtractOneFromNumOfEventMemoryEntries( &eventMemoryRecord );
    }

    /*----------------------------------------------------------------------------------------------------------*/
    /*  clear misfire record data.                                                                              */
    /*  Specific events(Similar/Misfire) aren't support Dem_InitializeEventStatus().                            */
    /*  so, no call following function.                                                                         */
    /*      Dem_Misfire_ClearDataRelatedAllFFD( eventStrgIndex )                                                */
    /*      Dem_Misfire_ClearDataRelatedAllObdFFD( eventStrgIndex )                                             */
    /*----------------------------------------------------------------------------------------------------------*/

    /*--------------------------------------------------------------------------------------------------------------*/
    /*  Specific events(Similar/Misfire) aren't support Dem_InitializeEventStatus().                                */
    /*  so, no call Dem_Similar_UpdateEventMemoryEntryFromTmp() and Dem_Misfire_UpdateEventMemoryEntryFromTmp().    */
    /*--------------------------------------------------------------------------------------------------------------*/


    /*--------------------------------------------------*/
    /*  Finishes exclusion.                             */
    /*--------------------------------------------------*/
    SchM_Exit_Dem_EventMemory();

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
    /*------------------------------------------*/
    /*  update B1 record.                       */
    /*------------------------------------------*/
    Dem_IndMI_HoldB1Counter( eventStrgIndex );      /* [GUDCHK:SETVAL]Dem_TmpEventMemoryEntry.EventStrgIndex */
#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_ON )      */

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_UpdEvtMemEntryOfTmp_NormalizeEvent              */
/* Description   | recovery faule record data.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus                                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no branch changed.                                       */
/*   v5-8-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_UpdEvtMemEntryOfTmp_NormalizeEvent
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_EventRecordForCtlType, AUTOMATIC ) eventRecord;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;
    VAR( Dem_EventMemoryRecordType, AUTOMATIC ) eventMemoryRecord;
    VAR( Dem_FFListRecordForClrType, AUTOMATIC ) clearFFListRecord;

    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) remainFFDCnt;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retClearFaultRecord;
    VAR( boolean, AUTOMATIC ) updateFFDRecInfo;
    VAR( boolean, AUTOMATIC ) judgeClearFaultFlag;
    VAR( boolean, AUTOMATIC ) clearFaultRecordFlag;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    /* Initialization of the automatic variable. */
    Dem_Data_LatchTmpEventMemoryData( &Dem_TmpEventMemoryEntry, &eventStrgIndex, &eventRecord, &faultRecord, &eventMemoryRecord );

    failRecordNum           =   Dem_FailRecordNum;
    clearFaultRecordFlag    =   (boolean)FALSE;

    /* Compares the event record corresponding to the event index of temporary area from temporary area. */
    Dem_Data_CompareEventMemoryEntryToTmp();

    if( eventRecord.FaultIndex < failRecordNum )
    {
        /*  get clear FFD index in fault record.    */
        updateFFDRecInfo    =   Dem_DataCtl_GetClearTargetFFRecord( DEM_RECOVERYTYPE_NORMALIZE, eventStrgIndex, DTCStatus, &clearFFListRecord );    /* [GUDCHK:SETVAL]Dem_TmpEventMemoryEntry.EventStrgIndex */
    }

    /*--------------------------------------------------*/
    /*  Starts exclusion.                               */
    /*--------------------------------------------------*/
    SchM_Enter_Dem_EventMemory();

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )     /*  [FuncSw]    */
    /* Removes pre-stored freeze frame corresponding to the event index. */
    /* PrestoreFreezeFrame exclusive section is controlled in this function. */
    Dem_PreFFD_RemovePrestoredFreezeFrame( eventStrgIndex );
#endif  /*   ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )            */

    if( eventRecord.FaultIndex < failRecordNum )
    {
        /*--------------------------------------*/
        /*  A) clear fault record.              */
        /*  -> clearFaultRecordFlag == TRUE.    */
        /*  B) update fault record.             */
        /*  -> clearFaultRecordFlag == FALSE.   */
        /*--------------------------------------*/
        if ( updateFFDRecInfo == (boolean)TRUE )
        {
            Dem_Data_ClearTargetFFRecordInFaultRecord( &clearFFListRecord, &faultRecord, &eventMemoryRecord );
        }

        /*  clear FFD record index in fault record.     */
        /*  get count of remain FFD record index.       */
        remainFFDCnt    =   Dem_Data_ClearTargetFFListRecord( &clearFFListRecord, &faultRecord );

        /*--------------------------------------------------*/
        /*  judge clear fault record.                       */
        /*--------------------------------------------------*/
        judgeClearFaultFlag     =   Dem_DataCtl_GetClearTargetFaultRecord( DEM_RECOVERYTYPE_NORMALIZE, DTCStatus );

        if ( judgeClearFaultFlag == (boolean)TRUE )
        {
            if ( remainFFDCnt == ( Dem_u08_FFDIndexType )0U )
            {
                clearFaultRecordFlag    =   (boolean)TRUE;
            }
        }
    }
    else
    {
        /*--------------------------------------*/
        /*  C) update event record only.        */
        /*--------------------------------------*/
        clearFaultRecordFlag    =   (boolean)TRUE;
    }

    /*------------------------------------------*/
    /*  update event record.                    */
    /*------------------------------------------*/
    /* In the case of Normalized, bit0,1,2,3,4,6,7 of statusOfDTC are set to 0. */
    eventRecord.StatusOfDTC          = Dem_DTC_SetNormalizeDTCStatus( eventRecord.StatusOfDTC );
    eventRecord.ExtendStatusOfDTC    = Dem_DTC_ExDTC_SetNormalizeExDTCStatus( eventRecord.ExtendStatusOfDTC );
    eventRecord.ExtendStatusOfDTC2   = Dem_DTC_ExDTC2_SetNormalizeExDTCStatus( eventRecord.ExtendStatusOfDTC2 );
    eventRecord.ExtendStatusOfDTC2   = Dem_DTC_ExDTC2_ResetContMIHistAndIndAtCycleStartBit( eventRecord.ExtendStatusOfDTC2 );
    if( ( DTCStatus & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )     /* statusOfDTC : bit3     */
    {
        eventRecord.ExtendStatusOfDTC2   = Dem_DTC_ExDTC2_SetAgingHistory( eventRecord.ExtendStatusOfDTC2 );
    }
    eventRecord.FailureCounter  =   DEM_FAILURECYCLE_COUNT_INITIAL_VALUE;

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )   /*  [FuncSw]    */
    /* When the executed asynchronous processing function is the notification target of MonitorStatus. */
    Dem_MonSts_SetAsyncUpdateMode( DEM_MONSTS_ASYNCUPD_AGING );
#endif  /*  ( DEM_TRIGGER_FIM_REPORTS == STD_ON )           */

    /* Do not change the following data                                 */
    /*   eventRecord.ClearId                                            */

    if ( clearFaultRecordFlag == (boolean)TRUE )
    {
        /*--------------------------------------*/
        /*  A) clear fault record.              */
        /*  C) update event record only.        */
        /*--------------------------------------*/
        /*  clear fault record.             */
        retClearFaultRecord         =   Dem_Data_ClearFaultRecord( eventRecord.FaultIndex );

        /*  clear fault record in event record.     */
        eventRecord.FaultIndex      =   DEM_FAULTINDEX_INITIAL;

        /*  update event record.                    */
        (void)Dem_DataMngC_SetEventRecord( eventStrgIndex, &eventRecord );  /* no return check required */

        /*------------------------------------------*/
        /*  decrement entry number.                 */
        /*------------------------------------------*/
        if( retClearFaultRecord == DEM_IRT_OK )
        {
            /*--------------------------------------*/
            /*  A) clear fault record.              */
            /*--------------------------------------*/
            /* Subtracts 1 from number of event memory entries of event memory record of primary memory. */
            Dem_Data_SubtractOneFromNumOfEventMemoryEntries( &eventMemoryRecord );
        }

        /*----------------------------------------------------------------------------------------------------------*/
        /*  clear misfire record data.                                                                              */
        /*  Specific events(Similar/Misfire) aren't support Dem_NormalizeEventStatus().                             */
        /*  so, no call following function.                                                                         */
        /*      Dem_Misfire_ClearDataRelatedAllFFD( eventStrgIndex )                                                */
        /*      Dem_Misfire_ClearDataRelatedAllObdFFD( eventStrgIndex )                                             */
        /*----------------------------------------------------------------------------------------------------------*/

    }
    else
    {
        /*--------------------------------------*/
        /*  B) update fault record.             */
        /*--------------------------------------*/
        /*  update fault record.(healing/aging counter) */
        faultRecord.ConfirmedOccurrenceOrder    = DEM_FAIL_OCCURRENCE_NUM_INVALID;
        faultRecord.MILOccurrenceOrder          = DEM_FAIL_OCCURRENCE_NUM_INVALID;

        /*----------------------------------------------------------------------------------------------------------*/
        /*  Reset Aging/Healing counter threshold at bit3 of DTCStatus is ON.(set value to Threshold.)              */
        /*                                                                                                          */
        /*  There is no case where FreezeFrame remains and bit3 changes ON to OFF.                                  */
        /*  Because TFTOC trigger and FDCThreshold trigger FreezeFrame are also deleted in bit3 changed ON to OFF.  */
        /*                                                                                                          */
        /*  If due to the addition of requirements, there are add pattern in which FreezeFrame remains              */
        /*  when bit3 changes from ON to OFF, it is necessary to call the following function:                       */
        /*                                                                                                          */
        /*      if( ( DTCStatus & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC ) :                                  */
        /*          faultRecord.AgingCounter     = Dem_CfgInfoPm_GetAgingCycleThreshold( eventStrgIndex );          */
        /*          faultRecord.TimeAgingCounter = Dem_CfgInfoPm_GetTimeAgingCounterThreshold();                    */
        /*          faultRecord.HealingCounter   = DEM_HEALING_COUNT_INITIAL_VALUE;                                 */
        /*----------------------------------------------------------------------------------------------------------*/

        /* Do not change the following data                                 */
        /*   faultRecord.EventStrgIndex                                     */
        /*   faultRecord.OccurrenceOrder                                    */

        /* Update a record(contain consistencyId) corresponding to an FaultIndex.                  */
        Dem_DataMngC_SetFaultRecord_WithUpdateConsistencyID( eventRecord.FaultIndex, &faultRecord, &consistencyId );

        /*  update event record.                    */
        Dem_DataMngC_SetEventRecord_AtUpdateFaultRecord( eventStrgIndex, &eventRecord, consistencyId );

        /* Sets the event memory record of primary memory. */
        Dem_DataMngC_SetEventMemoryRecord( &eventMemoryRecord );

        /*----------------------------------------------------------------------------------------------------------*/
        /*  clear misfire record data.                                                                              */
        /*  Specific events(Similar/Misfire) aren't support Dem_NormalizeEventStatus().                             */
        /*  so, no call following function.                                                                         */
        /*      Dem_DataCtl_ClearTargetMisfCylinderFFD( DEM_RECOVERYTYPE_NORMALIZE, eventStrgIndex, DTCStatus )     */
        /*----------------------------------------------------------------------------------------------------------*/

    }

    /*--------------------------------------------------------------------------------------------------------------*/
    /*  Specific events(Similar/Misfire) aren't support Dem_NormalizeEventStatus().                                 */
    /*  so, no call Dem_Similar_UpdateEventMemoryEntryFromTmp() and Dem_Misfire_UpdateEventMemoryEntryFromTmp().    */
    /*--------------------------------------------------------------------------------------------------------------*/

    /*--------------------------------------------------*/
    /*  Finishes exclusion.                             */
    /*--------------------------------------------------*/
    SchM_Exit_Dem_EventMemory();

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )  /*  [FuncSw]    */
        /*  update B1 record.                       */
    Dem_IndMI_ClearB1Counter( eventStrgIndex );     /* [GUDCHK:SETVAL]Dem_TmpEventMemoryEntry.EventStrgIndex */
#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_ON )      */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Data_UpdEvtMemEntryOfTmp_AgingEvent                  */
/* Description   | recovery faule record data.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus                                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no branch changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_UpdEvtMemEntryOfTmp_AgingEvent
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_EventRecordForCtlType, AUTOMATIC ) eventRecord;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;
    VAR( Dem_EventMemoryRecordType, AUTOMATIC ) eventMemoryRecord;
    VAR( Dem_FFListRecordForClrType, AUTOMATIC ) clearFFListRecord;

    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) remainFFDCnt;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retClearFaultRecord;
    VAR( boolean, AUTOMATIC ) updateFFDRecInfo;
    VAR( boolean, AUTOMATIC ) judgeClearFaultFlag;
    VAR( boolean, AUTOMATIC ) clearFaultRecordFlag;
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) consistencyIdUpdateFlg;
    consistencyIdUpdateFlg  =   (boolean)FALSE;
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */

    /* Initialization of the automatic variable. */
    Dem_Data_LatchTmpEventMemoryData( &Dem_TmpEventMemoryEntry, &eventStrgIndex, &eventRecord, &faultRecord, &eventMemoryRecord );

    clearFaultRecordFlag    =   (boolean)FALSE;
    consistencyId           =   DEM_CONSISTENCY_INITIAL;

    /*------------------------------------------------------*/
    /*  Aging action is execute only bit3 is ON.            */
    /*------------------------------------------------------*/
    if( ( DTCStatus & DEM_UDS_STATUS_CDTC ) == DEM_UDS_STATUS_CDTC )     /* statusOfDTC : bit3     */
    {
        /*  get clear FFD index in fault record.    */
        updateFFDRecInfo    =   Dem_DataCtl_GetClearTargetFFRecord( DEM_RECOVERYTYPE_AGING, eventStrgIndex, DTCStatus, &clearFFListRecord );    /* [GUDCHK:SETVAL]Dem_TmpEventMemoryEntry.EventStrgIndex */

        /*--------------------------------------------------*/
        /*  Starts exclusion.                               */
        /*--------------------------------------------------*/
        SchM_Enter_Dem_EventMemory();

        if ( updateFFDRecInfo == (boolean)TRUE )
        {
            Dem_Data_ClearTargetFFRecordInFaultRecord( &clearFFListRecord, &faultRecord, &eventMemoryRecord );
        }

        /*  clear FFD record index in fault record.     */
        /*  get count of remain FFD record index.       */
        remainFFDCnt    =   Dem_Data_ClearTargetFFListRecord( &clearFFListRecord, &faultRecord );

        /*--------------------------------------------------*/
        /*  judge clear fault record.                       */
        /*--------------------------------------------------*/
        judgeClearFaultFlag     =   Dem_DataCtl_GetClearTargetFaultRecord( DEM_RECOVERYTYPE_AGING, DTCStatus );

        if ( judgeClearFaultFlag == (boolean)TRUE )
        {
            if ( remainFFDCnt == ( Dem_u08_FFDIndexType )0U )
            {
                clearFaultRecordFlag    =   (boolean)TRUE;
            }
        }

        /*------------------------------------------*/
        /*  update event record.                    */
        /*------------------------------------------*/
        /* In the case of Aging, a deletion mode resets bit3 and bit7 of statusOfDTC. */
        eventRecord.StatusOfDTC             = Dem_DTC_ResetConfirmedDTCAndWIRStatus_AtAging( eventRecord.StatusOfDTC );
        eventRecord.ExtendStatusOfDTC       = Dem_DTC_ExDTC_ResetIndicatorBit( eventRecord.ExtendStatusOfDTC );    /*  Reset IndicatorStatus bit.          */
        eventRecord.ExtendStatusOfDTC2      = Dem_DTC_ExDTC2_SetAgingHistory( eventRecord.ExtendStatusOfDTC2 );
        eventRecord.ExtendStatusOfDTC2      = Dem_DTC_ExDTC2_ResetContMIHistAndIndAtCycleStartBit( eventRecord.ExtendStatusOfDTC2 );

        if( ( DTCStatus & DEM_UDS_STATUS_PDTC ) == (Dem_UdsStatusByteType)0U )     /* statusOfDTC : bit2 : OFF     */
        {
            eventRecord.FailureCounter  =   DEM_FAILURECYCLE_COUNT_INITIAL_VALUE;
        }

        /* Do not change the following data                                 */
        /*   eventRecord.ClearId                                            */
#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )   /*  [FuncSw]    */
        /* When the executed asynchronous processing function is the notification target of MonitorStatus. */
        Dem_MonSts_SetAsyncUpdateMode( DEM_MONSTS_ASYNCUPD_AGING );
#endif  /*  ( DEM_TRIGGER_FIM_REPORTS == STD_ON )           */

        if ( clearFaultRecordFlag == (boolean)TRUE )
        {
            retClearFaultRecord = DEM_IRT_NG;
            if( eventRecord.FaultIndex != DEM_FAULTINDEX_INITIAL )
            {
                /*  clear fault record.             */
                retClearFaultRecord         =   Dem_Data_ClearFaultRecord( eventRecord.FaultIndex );

                /*  clear fault record in event record.     */
                eventRecord.FaultIndex      =   DEM_FAULTINDEX_INITIAL;
            }
            else
            {
                /*  reach this route only with forced aging.  */
            }

            /*  update event record.                    */
            (void)Dem_DataMngC_SetEventRecord( eventStrgIndex, &eventRecord );  /* no return check required */

            /*------------------------------------------*/
            /*  decrement entry number.                 */
            /*------------------------------------------*/
            if( retClearFaultRecord == DEM_IRT_OK )
            {
                /* Subtracts 1 from number of event memory entries of event memory record of primary memory. */
                Dem_Data_SubtractOneFromNumOfEventMemoryEntries( &eventMemoryRecord );
            }

            /*------------------------------------------*/
            /*  clear misfire record data.              */
            /*------------------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            Dem_Misfire_ClearDataRelatedAllFFD( eventStrgIndex );
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
            Dem_Misfire_ClearDataRelatedAllObdFFD( eventStrgIndex );
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
        }
        else
        {
            if( eventRecord.FaultIndex != DEM_FAULTINDEX_INITIAL )
            {
                /*  update fault record.(healing/aging counter) */
                faultRecord.ConfirmedOccurrenceOrder    = DEM_FAIL_OCCURRENCE_NUM_INVALID;
                faultRecord.MILOccurrenceOrder          = DEM_FAIL_OCCURRENCE_NUM_INVALID;
                faultRecord.AgingCounter                = Dem_CfgInfoPm_GetAgingCycleThreshold( eventStrgIndex );
#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
                faultRecord.TimeAgingCounter            = Dem_CfgInfoPm_GetTimeAgingCounterThreshold();
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */
#if ( DEM_INDICATOR_USE == STD_ON ) /*  [FuncSw]    */
                faultRecord.HealingCounter              = DEM_HEALING_COUNT_INITIAL_VALUE;
#endif  /* ( DEM_INDICATOR_USE == STD_ON )          */

                /* Do not change the following data                                 */
                /*   faultRecord.EventStrgIndex                                     */
                /*   faultRecord.OccurrenceOrder                                    */

                /* Update a record(contain consistencyId) corresponding to an FaultIndex.                  */
                Dem_DataMngC_SetFaultRecord_WithUpdateConsistencyID( eventRecord.FaultIndex, &faultRecord, &consistencyId );

                /*  update event record.                    */
                Dem_DataMngC_SetEventRecord_AtUpdateFaultRecord( eventStrgIndex, &eventRecord, consistencyId );
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
                consistencyIdUpdateFlg  =   (boolean)TRUE;
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */
            }
            else
            {
                /*  no update consistency id, because similar or misfire event is not reach this route.  */
                /*  update event record.                    */
                (void)Dem_DataMngC_SetEventRecord( eventStrgIndex, &eventRecord );   /* no return check required */
            }

            /* Sets the event memory record of primary memory. */
            Dem_DataMngC_SetEventMemoryRecord( &eventMemoryRecord );

            /*------------------------------------------*/
            /*  clear misfire record data.              */
            /*------------------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            Dem_DataCtl_ClearTargetMisfCylinderFFD( DEM_RECOVERYTYPE_AGING, eventStrgIndex, DTCStatus );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
        }
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
        /* Store Specific Event Memory from temporary area's one. */
        /* Called individually because it is an exclusive section. */
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        Dem_Similar_CompareSimilarInfoToTmp( eventStrgIndex );
        Dem_Similar_UpdateEventMemoryEntryFromTmp( eventStrgIndex, consistencyIdUpdateFlg, consistencyId );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        Dem_Misfire_CompareMisfireInfoToTmp( eventStrgIndex );
        Dem_Misfire_UpdateEventMemoryEntryFromTmp( eventStrgIndex, consistencyIdUpdateFlg, consistencyId );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */

        /*--------------------------------------------------*/
        /*  Finishes exclusion.                             */
        /*--------------------------------------------------*/
        SchM_Exit_Dem_EventMemory();

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )  /*  [FuncSw]    */
        /*  update B1 record.                       */
        Dem_IndMI_ClearB1Counter( eventStrgIndex );     /* [GUDCHK:SETVAL]Dem_TmpEventMemoryEntry.EventStrgIndex */
#endif  /*   ( DEM_WWH_OBD_SUPPORT == STD_ON )      */
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Data_UpdEvtMemEntryOfTmp_PendingOFFEvent             */
/* Description   | recovery faule record data.                              */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus                                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no branch changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_UpdEvtMemEntryOfTmp_PendingOFFEvent
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    VAR( Dem_EventRecordForCtlType, AUTOMATIC ) eventRecord;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;
    VAR( Dem_EventMemoryRecordType, AUTOMATIC ) eventMemoryRecord;
    VAR( Dem_FFListRecordForClrType, AUTOMATIC ) clearFFListRecord;

    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) remainFFDCnt;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retClearFaultRecord;
    VAR( boolean, AUTOMATIC ) updateFFDRecInfo;
    VAR( boolean, AUTOMATIC ) judgeClearFaultFlag;
    VAR( boolean, AUTOMATIC ) clearFaultRecordFlag;
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) consistencyIdUpdateFlg;
    VAR( boolean, AUTOMATIC ) isSpecificEvent;

    consistencyIdUpdateFlg  =   (boolean)FALSE;
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */

    /* Initialization of the automatic variable. */
    Dem_Data_LatchTmpEventMemoryData( &Dem_TmpEventMemoryEntry, &eventStrgIndex, &eventRecord, &faultRecord, &eventMemoryRecord );

    clearFaultRecordFlag    =   (boolean)FALSE;
    consistencyId           =   DEM_CONSISTENCY_INITIAL;

    /*  get clear FFD index in fault record.    */
    updateFFDRecInfo    =   Dem_DataCtl_GetClearTargetFFRecord( DEM_RECOVERYTYPE_PENDINGOFF, eventStrgIndex, DTCStatus, &clearFFListRecord );   /* [GUDCHK:SETVAL]Dem_TmpEventMemoryEntry.EventStrgIndex */

    /*--------------------------------------------------*/
    /*  Starts exclusion.                               */
    /*--------------------------------------------------*/
    SchM_Enter_Dem_EventMemory();

    if ( updateFFDRecInfo == (boolean)TRUE )
    {
        Dem_Data_ClearTargetFFRecordInFaultRecord( &clearFFListRecord, &faultRecord, &eventMemoryRecord );
    }

    /*  clear FFD record index in fault record.     */
    /*  get count of remain FFD record index.       */
    remainFFDCnt    =   Dem_Data_ClearTargetFFListRecord( &clearFFListRecord, &faultRecord );

    /*--------------------------------------------------*/
    /*  judge clear fault record.                       */
    /*--------------------------------------------------*/
    judgeClearFaultFlag     =   Dem_DataCtl_GetClearTargetFaultRecord( DEM_RECOVERYTYPE_PENDINGOFF, DTCStatus );

    if ( judgeClearFaultFlag == (boolean)TRUE )
    {
        if ( remainFFDCnt == ( Dem_u08_FFDIndexType )0U )
        {
            clearFaultRecordFlag    =   (boolean)TRUE;
        }
    }

    /*------------------------------------------*/
    /*  update event record.                    */
    /*------------------------------------------*/
    /*  PendingOFF                  */
    eventRecord.StatusOfDTC          = Dem_DTC_ResetPendingDTCBit( eventRecord.StatusOfDTC );
    /*   eventRecord.ExtendStatusOfDTC  :   no change                   */
    /*   eventRecord.ExtendStatusOfDTC2 :   no change                   */

    /*  clear failurecounter.(by bit2 is OFF)   */
    eventRecord.FailureCounter      =   DEM_FAILURECYCLE_COUNT_INITIAL_VALUE;

    /* Do not change the following data                                 */
    /*   eventRecord.ClearId                                            */

    if ( clearFaultRecordFlag == (boolean)TRUE )
    {
        retClearFaultRecord = DEM_IRT_NG;

        if( eventRecord.FaultIndex != DEM_FAULTINDEX_INITIAL )
        {
            /*  clear fault record.             */
            retClearFaultRecord         =   Dem_Data_ClearFaultRecord( eventRecord.FaultIndex );

            /*  clear fault record in event record.     */
            eventRecord.FaultIndex      =   DEM_FAULTINDEX_INITIAL;
        }
        else
        {
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
            isSpecificEvent =   Dem_CfgInfoPm_CheckEventKindOfSpecific_InEvtStrgGrp( eventStrgIndex );
            if ( isSpecificEvent == (boolean)TRUE )
            {
                consistencyIdUpdateFlg  =   (boolean)TRUE;
                Dem_DataMng_UpdateEventRecordConsistencyId( eventStrgIndex, &consistencyId );
            }
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */
        }

        /*  update event record.                    */
        (void)Dem_DataMngC_SetEventRecord( eventStrgIndex, &eventRecord );  /* no return check required */

        /*------------------------------------------*/
        /*  decrement entry number.                 */
        /*------------------------------------------*/
        if( retClearFaultRecord == DEM_IRT_OK )
        {
            /* Subtracts 1 from number of event memory entries of event memory record of primary memory. */
            Dem_Data_SubtractOneFromNumOfEventMemoryEntries( &eventMemoryRecord );
        }

        /*------------------------------------------*/
        /*  clear misfire record data.              */
        /*------------------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        Dem_Misfire_ClearDataRelatedAllFFD( eventStrgIndex );
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
        Dem_Misfire_ClearDataRelatedAllObdFFD( eventStrgIndex );
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    }
    else
    {
        if( eventRecord.FaultIndex != DEM_FAULTINDEX_INITIAL )
        {
            /* Do not change the following data                                 */
            /*   faultRecord.ConfirmedOccurrenceOrder                           */
            /*   faultRecord.MILOccurrenceOrder                                 */
            /*   faultRecord.AgingCounter                                       */
            /*   faultRecord.TimeAgingCounter                                   */
            /*   faultRecord.HealingCounter                                     */
            /*   faultRecord.EventStrgIndex                                     */
            /*   faultRecord.OccurrenceOrder                                    */

            /* Update a record(contain consistencyId) corresponding to an FaultIndex.                  */
            Dem_DataMngC_SetFaultRecord_WithUpdateConsistencyID( eventRecord.FaultIndex, &faultRecord, &consistencyId );

            /*  update event record.                    */
            Dem_DataMngC_SetEventRecord_AtUpdateFaultRecord( eventStrgIndex, &eventRecord, consistencyId );
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
            consistencyIdUpdateFlg  =   (boolean)TRUE;
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */
        }
        else
        {
#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
            isSpecificEvent =   Dem_CfgInfoPm_CheckEventKindOfSpecific_InEvtStrgGrp( eventStrgIndex );
            if ( isSpecificEvent == (boolean)TRUE )
            {
                consistencyIdUpdateFlg  =   (boolean)TRUE;
                Dem_DataMng_UpdateEventRecordConsistencyId( eventStrgIndex, &consistencyId );
            }
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */
            /*  update event record.                    */
            (void)Dem_DataMngC_SetEventRecord( eventStrgIndex, &eventRecord );   /* no return check required */
        }

        /* Sets the event memory record of primary memory. */
        Dem_DataMngC_SetEventMemoryRecord( &eventMemoryRecord );

        /*------------------------------------------*/
        /*  clear misfire record data.              */
        /*------------------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        Dem_DataCtl_ClearTargetMisfCylinderFFD( DEM_RECOVERYTYPE_PENDINGOFF, eventStrgIndex, DTCStatus );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    }

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
    /* Store Specific Event Memory from temporary area's one. */
    /* Called individually because it is an exclusive section. */
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Similar_CompareSimilarInfoToTmp( eventStrgIndex );
    Dem_Similar_UpdateEventMemoryEntryFromTmp( eventStrgIndex, consistencyIdUpdateFlg, consistencyId );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Misfire_CompareMisfireInfoToTmp( eventStrgIndex );
    Dem_Misfire_UpdateEventMemoryEntryFromTmp( eventStrgIndex, consistencyIdUpdateFlg, consistencyId );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */

    /*--------------------------------------------------*/
    /*  Finishes exclusion.                             */
    /*--------------------------------------------------*/
    SchM_Exit_Dem_EventMemory();

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_UpdEvtMemEntryOfTmp_PendingOFFAndAgingEvent     */
/* Description   | recovery faule record data.                              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_UpdEvtMemEntryOfTmp_PendingOFFAndAgingEvent
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retClearFaultRecord;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_EventRecordForCtlType, AUTOMATIC ) eventRecord;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;
    VAR( Dem_EventMemoryRecordType, AUTOMATIC ) eventMemoryRecord;

    /* Initialization of the automatic variable. */
    Dem_Data_LatchTmpEventMemoryData( &Dem_TmpEventMemoryEntry, &eventStrgIndex, &eventRecord, &faultRecord, &eventMemoryRecord );

    retClearFaultRecord = DEM_IRT_NG;

    Dem_Data_SetResultOfCmpFFRToTmp( &faultRecord );

    /* Starts exclusion. */
    SchM_Enter_Dem_EventMemory();

    if( eventRecord.FaultIndex != DEM_FAULTINDEX_INITIAL )
    {
        /*------------------------------------------*/
        /*  clear freezeframe record.               */
        /*------------------------------------------*/
        Dem_Data_ClearFreezeFrameRecord( &faultRecord, &eventMemoryRecord );
#if ( DEM_OBDFFD_SUPPORT == STD_ON )        /*  [FuncSw]    */
        Dem_Data_ClearObdFreezeFrameRecord( &faultRecord, &eventMemoryRecord );
#endif  /*( DEM_OBDFFD_SUPPORT == STD_ON )                 */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )  /*  [FuncSw]    */
        Dem_Data_ClearTSFFListRecord( &faultRecord );
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )           */

        /*------------------------------------------*/
        /*  clear fault record.                     */
        /*------------------------------------------*/
        retClearFaultRecord         =   Dem_Data_ClearFaultRecord( eventRecord.FaultIndex );

        /*------------------------------------------*/
        /*  update event record.                    */
        /*------------------------------------------*/
        /*  clear fault record in event record.     */
        eventRecord.FaultIndex      =   DEM_FAULTINDEX_INITIAL;
    }
    else
    {
       /* no reach this route, because aging and pendingOff is not occur without a fault record. */
    }

    /*  update status of DTC.                   */
    eventRecord.StatusOfDTC             = Dem_DTC_ResetConfirmedDTCAndPendingDTCStatus_AtAging( eventRecord.StatusOfDTC );   /* statusOfDTC : bit2,3 : OFF     */
    /*   eventRecord.ExtendStatusOfDTC  :   no change                   */

    /*  set aging history.(by Aging.)           */
    eventRecord.ExtendStatusOfDTC2      = Dem_DTC_ExDTC2_SetAgingHistory( eventRecord.ExtendStatusOfDTC2 );

    /*  clear failurecounter.(by bit2 is OFF)   */
    eventRecord.FailureCounter  =   DEM_FAILURECYCLE_COUNT_INITIAL_VALUE;

    /* Do not change the following data                                 */
    /*   eventRecord.ClearId                                            */

#if ( DEM_TRIGGER_FIM_REPORTS == STD_ON )   /*  [FuncSw]    */
    /* When the executed asynchronous processing function is the notification target of MonitorStatus. */
    Dem_MonSts_SetAsyncUpdateMode( DEM_MONSTS_ASYNCUPD_AGING );
#endif  /*  ( DEM_TRIGGER_FIM_REPORTS == STD_ON )           */

    /*  update event record.                    */
    (void)Dem_DataMngC_SetEventRecord( eventStrgIndex, &eventRecord );  /* no return check required */

    /*------------------------------------------*/
    /*  decrement entry number.                 */
    /*------------------------------------------*/
    if( retClearFaultRecord == DEM_IRT_OK )
    {
        /* Subtracts 1 from number of event memory entries of event memory record of primary memory. */
        Dem_Data_SubtractOneFromNumOfEventMemoryEntries( &eventMemoryRecord );
    }

    /*------------------------------------------*/
    /*  clear misfire record data.              */
    /*------------------------------------------*/
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Misfire_ClearDataRelatedAllFFD( eventStrgIndex );
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    Dem_Misfire_ClearDataRelatedAllObdFFD( eventStrgIndex );
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
    /* Store Specific Event Memory from temporary area's one. */
    /* Called individually because it is an exclusive section. */
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Similar_CompareSimilarInfoToTmp( eventStrgIndex );
    Dem_Similar_UpdateEventMemoryEntryFromTmp( eventStrgIndex, (boolean)FALSE, DEM_CONSISTENCY_INITIAL );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Misfire_CompareMisfireInfoToTmp( eventStrgIndex );
    Dem_Misfire_UpdateEventMemoryEntryFromTmp( eventStrgIndex, (boolean)FALSE, DEM_CONSISTENCY_INITIAL );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */

    /*--------------------------------------------------*/
    /*  Finishes exclusion.                             */
    /*--------------------------------------------------*/
    SchM_Exit_Dem_EventMemory();

    return ;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_SetResultOfCmpObdFFRToTmp                       */
/* Description   | Sets the array of ResultOfComparingObdFFRecords of temp- */
/*               | orary event memory entry.                                */
/* Parameters    | [in] FaultRecordPtr : Fault record.                      */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SetResultOfCmpObdFFRToTmp
(
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;

    obdFFRClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();

    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < obdFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )     /* [GUD:for] freezeFrameRecordIndex */
    {
        /* Checks the OBD record number index corresponding to the loop counter of retrieved the OBD freeze frame list.  */
        if( FaultRecordPtr->ObdRecordNumberIndex[freezeFrameRecordIndex] != DEM_FFRECINDEX_INITIAL  )                                           /* [GUD] freezeFrameRecordIndex *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / freezeFrameRecordIndex */
        {
            Dem_Data_SetResultOfCmpObdFFRecordToTmp( freezeFrameRecordIndex, DEM_IRT_NG );                                                      /* [GUD] freezeFrameRecordIndex */
        }
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Data_SetResultOfCmpFFRToTmp                          */
/* Description   | Sets the array of ResultOfComparingFFRecords of tempora- */
/*               | ry event memory entry.                                   */
/* Parameters    | [in] FaultRecordPtr : Fault record.                      */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SetResultOfCmpFFRToTmp
(
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_Data_SetResultOfCmpObdFFRToTmp( FaultRecordPtr );
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )  /* [GUD:for] freezeFrameRecordIndex */
    {
        /* Checks the record number index corresponding to the loop counter of retrieved the freeze frame list.  */
        if( FaultRecordPtr->RecordNumberIndex[freezeFrameRecordIndex] != DEM_FFRECINDEX_INITIAL  )                                              /* [GUD] freezeFrameRecordIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / freezeFrameRecordIndex */
        {
            Dem_Data_SetResultOfCmpFFRecordToTmp( freezeFrameRecordIndex, DEM_IRT_NG );                                                         /* [GUD] freezeFrameRecordIndex */
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_LatchTmpEventMemoryData                         */
/* Description   | latch Dem_TmpEventMemoryEntry data.                      */
/* Parameters    | [in]  TmpEventMemoryEntryStPtr    :                      */
/*               | [out] EventStrgIndexPtr    :                             */
/*               | [out] EventRecordPtr       :                             */
/*               | [out] FaultRecordPtr       :                             */
/*               | [out] EventMemoryRecordPtr :                             */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_LatchTmpEventMemoryData
(
    P2VAR( Dem_TmpEventMemoryEntryType, AUTOMATIC, DEM_VAR_NO_INIT ) TmpEventMemoryEntryStPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_EventRecordForCtlType, AUTOMATIC, AUTOMATIC ) EventRecordPtr,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_EventMemoryRecordType, AUTOMATIC, AUTOMATIC ) EventMemoryRecordPtr
)
{
    *EventStrgIndexPtr  = TmpEventMemoryEntryStPtr->EventStrgIndex;       /* [GUDCHK:SETVAL]Dem_TmpEventMemoryEntry.EventStrgIndex */

    Dem_DataMngC_CopyEventCtlRecordData( EventRecordPtr, &( TmpEventMemoryEntryStPtr->EventRecord ) );
    Dem_DataMngC_CopyFaultRecord( FaultRecordPtr, &( TmpEventMemoryEntryStPtr->FaultRecord ) );
    Dem_DataMngC_CopyEventMemoryRecord( EventMemoryRecordPtr, &( TmpEventMemoryEntryStPtr->EventMemoryRecordList ) );

    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
