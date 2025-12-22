/* Dem_DataCtl_EventEntry04Regist_c(v5-9-0)                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_EventEntry04Regist/CODE                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Rc_OdrLst.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_Control.h"
#include "../../../inc/Dem_Pm_Event.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_Similar.h"
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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_StoreEventRecordFromTmp
( void );

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_StoreEventRecordOverwrittenFromTmp
( void );
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_StoreFaultRecordFromTmp
( void );

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_StoreFaultRecordOverwrittenFromTmp
( void );

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_StoreObdFaultRecordOverwrittenFromTmp
( void );
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

static FUNC( void, DEM_CODE ) Dem_Data_StoreNonObdFaultRecordOverwrittenFromTmp
( void );

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_StoreTSFFLOverwrittenFromTmp
( void );
#endif /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

static FUNC( void, DEM_CODE ) Dem_Data_UpdateNextFaultOccurrenceOrderFromTmp
( void );

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_UpdateNextConfirmedFaultOccurrenceOrderFromTmp
( void );
#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )  */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_UpdateNextMILFaultOccurrenceOrderFromTmp
( void );
#endif /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) */

#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_StoreObdFreezeFrameRecordFromTmp
( void );

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_StoreObdFFROverwriteFromTmp
( void );
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

static FUNC( void, DEM_CODE ) Dem_Data_StoreFreezeFrameRecordFromTmp
( void );

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_StoreFFROverwriteFromTmp
( void );
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

static FUNC( void, DEM_CODE ) Dem_Data_StoreEventMemoryRecordFromTmp
( void );

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_RemoveNonObdFreezeFrame
( void );
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_SetPairObdFFRecordIndex
( void );
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON ) */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_NotifyMILFaultRegistComplete
( void );
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )      */

static FUNC( void, DEM_CODE ) Dem_Data_NotifyFaultRegistComplete
( void );

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_NotifyConfirmedFaultRegistComplete
( void );
#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )   */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u08_EventMemoryUpdateStatusType, DEM_VAR_NO_INIT ) Dem_EventMemoryUpdatingStatus;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Data_StoreEventMemoryEntryFromTmp                    */
/* Description   | Store the event memory entry from temporary area corres- */
/*               | ponding to the event index of temporary area.            */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_StoreEventMemoryEntryFromTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfStoreEventRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfStoreFaultRec;

    Dem_Data_SetEventMemoryUpdatingStatus( DEM_EVENT_MEMORY_UPDATING );

    /* Starts exclusion. */
    SchM_Enter_Dem_EventMemory();

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /* [FuncSw]    */
    /* Updates the OBD freeze frame record from temporary area's one. */
    Dem_Data_StoreObdFreezeFrameRecordFromTmp();
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )            */

    /* Updates the freeze frame record from temporary area's one. */
    Dem_Data_StoreFreezeFrameRecordFromTmp();

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /* [FuncSw]   */
    Dem_Data_PrepareStoreTSFFRecordFromSample();
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )           */

    /* Updates the event record from temporary area's one. */
    resultOfStoreEventRec = Dem_Data_StoreEventRecordFromTmp();

    /* Checks the result of updating the event record. */
    if( resultOfStoreEventRec == DEM_IRT_OK )
    {
        /* Updating the event record was successful. */

        /* Updates the fault record from temporary area's one. */
        resultOfStoreFaultRec = Dem_Data_StoreFaultRecordFromTmp();

        /* Checks the result of updating the fault record. */
        if( resultOfStoreFaultRec == DEM_IRT_OK )
        {
            /* Updating the fault record was successful. */

            /* Updates the event memory record from temporary area's one. */
            Dem_Data_StoreEventMemoryRecordFromTmp();
        }
        else
        {
            /* In case that there is no fault (the invalid fault index was given).  */
            /* no processing. */
        }
    }
    else
    {
        /* In case that the invalid event index was given. */
        /* no processing. */
    }

#if ( DEM_OBDONUDS_SUPPORT == STD_ON )              /*  [FuncSw]    */
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Data_SetPairObdFFRecordIndex();
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )    */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON )                */

    /* Store Specific Event Memory from temporary area's one. */
    /* Called individually because it is an exclusive section. */
#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Similar_UpdateEventMemoryEntryFromTmp( Dem_TmpEventMemoryEntry.EventStrgIndex, Dem_TmpEventMemoryEntry.ConsistencyIdUpdatedFlg, Dem_TmpEventMemoryEntry.ConsistencyId );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Misfire_UpdateEventMemoryEntryFromTmp( Dem_TmpEventMemoryEntry.EventStrgIndex, Dem_TmpEventMemoryEntry.ConsistencyIdUpdatedFlg, Dem_TmpEventMemoryEntry.ConsistencyId );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    /* Finishes exclusion. */
    SchM_Exit_Dem_EventMemory();

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
    /* Checking number of DTCs to store freeze frame */
    /* And remove non-OBD freeze frame if necessary */
    Dem_Data_RemoveNonObdFreezeFrame();
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
    Dem_Data_SetEventMemoryUpdatingStatus( DEM_EVENT_MEMORY_NOT_UPDATING );

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /* [FuncSw]   */
    /* Updates the time-series freeze frame record from sampling freeze frame record list. */
    Dem_Data_StoreTSFFRecordFromSample();
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_Data_GetEventMemoryUpdatingStatus                    */
/* Description   | get Event Memory updating state                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_EventMemoryUpdateStatusType                      */
/*               |        DEM_EVENT_MEMORY_UPDATING  :  updating            */
/*               |        DEM_EVENT_MEMORY_NOT_UPDATING :  other            */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_EventMemoryUpdateStatusType, DEM_CODE ) Dem_Data_GetEventMemoryUpdatingStatus
( void )
{
    return Dem_EventMemoryUpdatingStatus;
}

/****************************************************************************/
/* Function Name | Dem_Data_SetEventMemoryUpdatingStatus                    */
/* Description   | set Event Memory updating state                          */
/* Preconditions | none                                                     */
/* Parameters    | Dem_u08_EventMemoryUpdateStatusType :                    */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SetEventMemoryUpdatingStatus
(
    VAR( Dem_u08_EventMemoryUpdateStatusType, AUTOMATIC ) UpdatingStatus
)
{
    Dem_EventMemoryUpdatingStatus = UpdatingStatus;
    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_StoreEventRecordFromTmp                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_StoreEventRecordFromTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSetEventRec;

    retVal = DEM_IRT_NG;

    if( Dem_TmpEventMemoryEntry.ResultOfComparingEventRecords == DEM_IRT_NG )
    {
        /* In the event record, there was difference between RAM and temporary. */

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /* [FuncSw] */
        Dem_Data_StoreEventRecordOverwrittenFromTmp();
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

        if( Dem_TmpEventMemoryEntry.ConsistencyIdUpdatedFlg == (boolean)TRUE )
        {
            Dem_DataMng_SetEventRecordConsistencyId( Dem_TmpEventMemoryEntry.EventStrgIndex, Dem_TmpEventMemoryEntry.ConsistencyId );
        }

        resultOfSetEventRec = Dem_DataMngC_SetEventRecord( Dem_TmpEventMemoryEntry.EventStrgIndex, &Dem_TmpEventMemoryEntry.EventRecord );
        if( resultOfSetEventRec == DEM_IRT_OK )
        {
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* No Process */
        }
    }
    else
    {
        if( Dem_TmpEventMemoryEntry.ConsistencyIdUpdatedFlg == (boolean)TRUE )
        {
            Dem_DataMng_SetEventRecordConsistencyId( Dem_TmpEventMemoryEntry.EventStrgIndex, Dem_TmpEventMemoryEntry.ConsistencyId );
        }

        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_StoreEventRecordOverwrittenFromTmp              */
/* Description   | If event displacement has been occurred, sets invalid    */
/*               | value to fault index of event record which to be         */
/*               | overwritten.                                             */
/*               | At that time, according to the configuration, reset      */
/*               | StatusOfDTC bit2, bit3, bit7.                            */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_StoreEventRecordOverwrittenFromTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetEventRec;
    VAR( Dem_EventRecordForCtlType, AUTOMATIC ) eventRecord;

    /* Sets invalid value to fault index of event record which to be overwritten. */

    /* Gets event record which to be overwritten. */
    resultOfGetEventRec = Dem_DataMngC_GetEventRecord( Dem_EventDisplacement.EventStrgIndexOfFaultRecordOverwritten, &eventRecord );

    if( resultOfGetEventRec == DEM_IRT_OK )
    {
        /* Sets invalid value to fault index of event record which to be overwritten. */
        eventRecord.FaultIndex = DEM_FAULTINDEX_INITIAL;

        /*----------------------------------------------*/
        /*  Update statusOfDTC at Overflow occurred.    */
        /*----------------------------------------------*/
        eventRecord.StatusOfDTC = Dem_DTC_ResetAllConfirmedDTCStatus_OnOverflow( eventRecord.StatusOfDTC );

        /*  Reset IndicatorStatus bit.          */
        eventRecord.ExtendStatusOfDTC = Dem_DTC_ExDTC_ResetIndicatorBit_OnOverflow( eventRecord.ExtendStatusOfDTC );

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
        eventRecord.ExtendStatusOfDTC = Dem_DTC_ExDTC_ResetPredictiveFaultBit_OnOverflow( eventRecord.ExtendStatusOfDTC );
#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )             */

        /*  Reset ActiveFaultAtCycleStart bit.          */
        /*  Reset ContinuousExp bit                     */
        eventRecord.ExtendStatusOfDTC2 = Dem_DTC_ExDTC2_ResetContMIHistAndIndAtCycleStartBit_OnOverflow( eventRecord.ExtendStatusOfDTC2 );

        /*==============================================================================*/
        /*  Misfire events are not overwritten. so, no update misfire cylinder status.  */
        /*==============================================================================*/

        /*  clear all qualification in event storage group.     */
        Dem_Event_ClearQualificationInfo_nochange_InEvtStrg( Dem_EventDisplacement.EventStrgIndexOfFaultRecordOverwritten );

        /* Not check return value, as event index of fault record is valid. */
        (void)Dem_DataMngC_SetEventRecord( Dem_EventDisplacement.EventStrgIndexOfFaultRecordOverwritten, &eventRecord );    /* no return check required *//* [UpdRec]Event */
    }

    return;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_Data_StoreFaultRecordFromTmp                         */
/* Description   | Update(Store) the fault record from temporary area.      */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_StoreFaultRecordFromTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSetFaultRec;

    retVal = DEM_IRT_OK;

    if( Dem_TmpEventMemoryEntry.ResultOfComparingFaultRecords == DEM_IRT_NG )
    {
        /* In the fault record, there was difference between RAM and temporary. */

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /* [FuncSw] */
        Dem_Data_StoreFaultRecordOverwrittenFromTmp();
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

        Dem_DataMng_SetFaultRecordConsistencyId( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex, Dem_TmpEventMemoryEntry.ConsistencyId );

        resultOfSetFaultRec = Dem_DataMngC_SetFaultRecord( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex, &Dem_TmpEventMemoryEntry.FaultRecord );

        if( resultOfSetFaultRec == DEM_IRT_OK )
        {
            Dem_Data_NotifyFaultRegistComplete();

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )   /* [FuncSw] */
            Dem_Data_NotifyConfirmedFaultRegistComplete();
#endif  /* ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )        */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )    /* [FuncSw] */
            Dem_Data_NotifyMILFaultRegistComplete();
#endif  /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )  */
        }
        else
        {
            retVal = DEM_IRT_NG;
        }
    }
    else
    {
        if( Dem_TmpEventMemoryEntry.ConsistencyIdUpdatedFlg == (boolean)TRUE )
        {
            Dem_DataMng_SetFaultRecordConsistencyId( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex, Dem_TmpEventMemoryEntry.ConsistencyId );
        }
    }

    return retVal;
}


#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_StoreFaultRecordOverwrittenFromTmp              */
/* Description   | If freeze frame record displacement has been occurred,   */
/*               | sets invalid value to freeze frame record index of fault */
/*               | record which to be overwritten.                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_StoreFaultRecordOverwrittenFromTmp
( void )
{
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /* [FuncSw] */
    Dem_Data_StoreObdFaultRecordOverwrittenFromTmp();
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */
    Dem_Data_StoreNonObdFaultRecordOverwrittenFromTmp();
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /* [FuncSw] */
    Dem_Data_StoreTSFFLOverwrittenFromTmp();
#endif /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

    Dem_Data_UpdateNextFaultOccurrenceOrderFromTmp();

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )   /* [FuncSw] */
    Dem_Data_UpdateNextConfirmedFaultOccurrenceOrderFromTmp();
#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )      */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )    /* [FuncSw] */
    Dem_Data_UpdateNextMILFaultOccurrenceOrderFromTmp();
#endif /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) */

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_StoreObdFaultRecordOverwrittenFromTmp           */
/* Description   | If OBD freeze frame record displacement has been occurr- */
/*               | ed, sets invalid value to OBD freeze frame record index  */
/*               | of fault record which to be overwritten.                 */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_StoreObdFaultRecordOverwrittenFromTmp
( void )
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) frOverwrittenIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ffrIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;

    obdFFRClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();
    failRecordNum = Dem_FailRecordNum;

    for( frOverwrittenIndex = (Dem_u08_FFListIndexType)0U; frOverwrittenIndex < obdFFRClassPerDTCMaxNum; frOverwrittenIndex++ ) /* [GUD:for] frOverwrittenIndex */
    {
        faultIndex = Dem_EventDisplacement.ObdFaultRecordOverwritten[frOverwrittenIndex].FaultIndex;                            /* [GUD] frOverwrittenIndex */

        if( faultIndex < failRecordNum )                                                                                        /* [GUD:if] faultIndex */
        {
            if( faultIndex != Dem_TmpEventMemoryEntry.EventRecord.FaultIndex )
            {
                /* In case the fault index is valid. */
                ffrIndex = Dem_EventDisplacement.ObdFaultRecordOverwritten[frOverwrittenIndex].RecordNumberIndex;               /* [GUD] frOverwrittenIndex */

                eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
                consistencyId = DEM_CONSISTENCY_INITIAL;
                /* Initializes freeze frame record index in the fault record which to be overwritten. */
                Dem_DataMngC_InitObdRecordNumberIndexFFROverwritten( faultIndex, ffrIndex, &eventStrgIndex, &consistencyId );

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                Dem_Similar_SetConsistencyId( eventStrgIndex, consistencyId );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
            }
        }
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Data_StoreNonObdFaultRecordOverwrittenFromTmp        */
/* Description   | If freeze frame record displacement has been occurred,   */
/*               | sets invalid value to freeze frame record index of fault */
/*               | record which to be overwritten.                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_StoreNonObdFaultRecordOverwrittenFromTmp
( void )
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) frOverwrittenIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ffrIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    failRecordNum = Dem_FailRecordNum;

    for( frOverwrittenIndex = (Dem_u08_FFListIndexType)0U; frOverwrittenIndex < nonOBDFFRClassPerDTCMaxNum; frOverwrittenIndex++ )  /* [GUD:for] frOverwrittenIndex */
    {
        faultIndex = Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].FaultIndex;                                   /* [GUD] frOverwrittenIndex */

        if( faultIndex < failRecordNum )                                                                                            /* [GUD:if] faultIndex */
        {
            if( faultIndex != Dem_TmpEventMemoryEntry.EventRecord.FaultIndex )
            {
                /* In case the fault index is valid. */
                ffrIndex = Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].RecordNumberIndex;                      /* [GUD] frOverwrittenIndex */

                eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
                consistencyId = DEM_CONSISTENCY_INITIAL;
                /* Initializes freeze frame record index in the fault record which to be overwritten. */
                Dem_DataMngC_InitRecordNumberIndexFFROverwritten( faultIndex, ffrIndex, &eventStrgIndex, &consistencyId );

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                Dem_Similar_SetConsistencyId( eventStrgIndex, consistencyId );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_StoreTSFFLOverwrittenFromTmp                    */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_StoreTSFFLOverwrittenFromTmp
( void )
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) frOverwrittenIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) indexOfTSFFListIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffListIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;

    failRecordNum = Dem_FailRecordNum;
    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;
    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;

    /* FreezeFrameRecord Overwritten */
    for( frOverwrittenIndex = (Dem_u08_FFListIndexType)0U; frOverwrittenIndex < nonOBDFFRClassPerDTCMaxNum; frOverwrittenIndex++ )  /* [GUD:for] frOverwrittenIndex */
    {
        faultIndex = Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].FaultIndex;                                   /* [GUD] frOverwrittenIndex */

        if( faultIndex < failRecordNum )                                                                                            /* [GUD:if] faultIndex */
        {
            if( faultIndex != Dem_TmpEventMemoryEntry.EventRecord.FaultIndex )
            {
                for( indexOfTSFFListIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; indexOfTSFFListIndex < tsffRecordClassNumPerDTCMaxNum; indexOfTSFFListIndex++ )    /* [GUD:for] indexOfTSFFListIndex */
                {
                    tsffListIndex = Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].TimeSeriesFreezeFrameListIndex[indexOfTSFFListIndex];      /* [GUD] frOverwrittenIndex *//* [GUD] indexOfTSFFListIndex */
                    if( tsffListIndex < tsffTotalDTCNum )                                                                           /* [GUD:if] tsffListIndex */
                    {

                        eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
                        consistencyId = DEM_CONSISTENCY_INITIAL;
                        /* In case the time-series freeze frame record list index is valid. */
                        Dem_DataMngC_InitTimeSeriesFreezeFrameListIndexFFROverwritten( faultIndex, tsffListIndex, &eventStrgIndex, &consistencyId );

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                        Dem_Similar_SetConsistencyId( eventStrgIndex, consistencyId );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */
                    }
                }
            }
        }
    }

    return;
}
#endif /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_Data_UpdateNextFaultOccurrenceOrderFromTmp           */
/* Description   | If freeze frame record displacement has been occurred,   */
/*               | update next fault occurrence order.                      */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_UpdateNextFaultOccurrenceOrderFromTmp
( void )
{
    if( Dem_EventDisplacement.NextFaultOccurrenceOrder != DEM_FAIL_OCCURRENCE_NUM_INVALID )
    {
        if( Dem_EventDisplacement.NextFaultOccurrenceOrder == Dem_TmpEventMemoryEntry.FaultRecord.OccurrenceOrder )
        {
            Dem_OdrLst_Fault_UpdateNextOccurrenceOrder( Dem_EventDisplacement.NextFaultOccurrenceOrder );
        }
    }

    return;
}


#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_UpdateNextConfirmedFaultOccurrenceOrderFromTmp  */
/* Description   | If freeze frame record displacement has been occurred,   */
/*               | update next confirmed fault occurrence order.            */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_UpdateNextConfirmedFaultOccurrenceOrderFromTmp
( void )
{
    if( Dem_EventDisplacement.NextConfirmedFaultOccurrenceOrder != DEM_FAIL_OCCURRENCE_NUM_INVALID )
    {
        if( Dem_EventDisplacement.NextConfirmedFaultOccurrenceOrder == Dem_TmpEventMemoryEntry.FaultRecord.ConfirmedOccurrenceOrder )
        {
            Dem_OdrLst_Confirmed_UpdateNextOccurrenceOrder( Dem_EventDisplacement.NextConfirmedFaultOccurrenceOrder );
        }
    }

    return;
}
#endif  /*  ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )   */


#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_UpdateNextMILFaultOccurrenceOrderFromTmp        */
/* Description   | If freeze frame record displacement has been occurred,   */
/*               | update next MIL fault occurrence order.                  */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_UpdateNextMILFaultOccurrenceOrderFromTmp
( void )
{
    if( Dem_EventDisplacement.NextMILFaultOccurrenceOrder != DEM_FAIL_OCCURRENCE_NUM_INVALID )
    {
        if( Dem_EventDisplacement.NextMILFaultOccurrenceOrder == Dem_TmpEventMemoryEntry.FaultRecord.MILOccurrenceOrder )
        {
            Dem_OdrLst_MIL_UpdateNextOccurrenceOrder( Dem_EventDisplacement.NextMILFaultOccurrenceOrder );
        }
    }

    return;
}
#endif /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_StoreObdFreezeFrameRecordFromTmp                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_StoreObdFreezeFrameRecordFromTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSetFFRec;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassNumPerDTCMaxNum;

    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdRecordNumberIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;

    obdFFRClassNumPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();
    obdFFDRecordNum = Dem_CfgInfoPm_GetObdFFDRecordNum();

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /* [FuncSw] */
    Dem_Data_StoreObdFFROverwriteFromTmp();
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < obdFFRClassNumPerDTCMaxNum; freezeFrameRecordIndex++ )  /* [GUD:for] freezeFrameRecordIndex */
    {
        obdRecordNumberIndex = Dem_TmpEventMemoryEntry.FaultRecord.ObdRecordNumberIndex[freezeFrameRecordIndex];    /* [GUD] freezeFrameRecordIndex */

        if( obdRecordNumberIndex < obdFFDRecordNum )                                                                /* [GUD:if] obdRecordNumberIndex */
        {
            if( Dem_TmpEventMemoryEntry.ResultOfComparingObdFFRecords[freezeFrameRecordIndex] == DEM_IRT_NG )       /* [GUD] freezeFrameRecordIndex */
            {
                /* In the freeze frame record, there was difference between RAM and temporary. */

                resultOfSetFFRec = Dem_DataMngC_SetObdFreezeFrameRecord( obdRecordNumberIndex, &Dem_TmpEventMemoryEntry.ObdFreezeFrameRecordList[freezeFrameRecordIndex] ); /* [GUD] freezeFrameRecordIndex */

                if( resultOfSetFFRec != DEM_IRT_OK )
                {
                    break;
                }
            }
        }
    }

    return ;
}


#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_StoreObdFFROverwriteFromTmp                     */
/* Description   | If freeze frame record which reuse from fault record to  */
/*               | be overwritten remained, clear it.                       */
/*               | If freeze frame record which reuse from fault record not */
/*               | to be overwritten exists, store it.                      */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | This function is not called from a misfire events.       */
/*               | Normally, it is necessary to call Dem_DataMngC_ClearObdFreezeFrameRecord() */
/*               | before calling Dem_Misfire_JudgeClearableObdFreezeFrame(),*/
/*               | but there is no need to call it. Because this function   */
/*               | is not called from a misfire events.                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_StoreObdFFROverwriteFromTmp
( void )
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) frOverwrittenIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ffrIndex;

    obdFFRClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();
    obdFFDRecordNum = Dem_CfgInfoPm_GetObdFFDRecordNum();

    for( frOverwrittenIndex = (Dem_u08_FFListIndexType)0U; frOverwrittenIndex < obdFFRClassPerDTCMaxNum; frOverwrittenIndex++ ) /* [GUD:for] frOverwrittenIndex */
    {
        faultIndex = Dem_EventDisplacement.ObdFaultRecordOverwritten[frOverwrittenIndex].FaultIndex;                            /* [GUD] frOverwrittenIndex */

        /* Dem_TmpEventMemoryEntry.EventRecord.FaultIndex is guaranteed. */

        if( faultIndex == Dem_TmpEventMemoryEntry.EventRecord.FaultIndex )
        {
            /* In case which the fault index indicates a fault record which to be overwritten. */

            ffrIndex = Dem_EventDisplacement.ObdFaultRecordOverwritten[frOverwrittenIndex].RecordNumberIndex;                   /* [GUD] frOverwrittenIndex */

            if( ffrIndex < obdFFDRecordNum )                                                                                    /* [GUD:if] ffrIndex */
            {
                /* In case the freeze frame record index is valid. */

                /* Clears freeze frame record not reused in the fault record overwritten. */
                /* Not check return value, as ffrIndex is valid. */
                (void)Dem_DataMngC_ClearObdFreezeFrameRecord( ffrIndex );   /* no return check required */
                Dem_DataMngM_UpdateSearchObdFFDIndex( ffrIndex );

                if( Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfObdFreezeFrameRecords > (Dem_u08_FFDIndexType)0U )
                {
                    Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfObdFreezeFrameRecords--;
                }
            }
        }
    }

    return;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */


/****************************************************************************/
/* Function Name | Dem_Data_StoreFreezeFrameRecordFromTmp                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_StoreFreezeFrameRecordFromTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSetFFRec;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;

    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) recordNumberIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /* [FuncSw] */
    Dem_Data_StoreFFROverwriteFromTmp();
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

    for( freezeFrameRecordIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordIndex < nonOBDFFRClassPerDTCMaxNum; freezeFrameRecordIndex++ )  /* [GUD:for] freezeFrameRecordIndex */
    {
        recordNumberIndex = Dem_TmpEventMemoryEntry.FaultRecord.RecordNumberIndex[freezeFrameRecordIndex];                                      /* [GUD] freezeFrameRecordIndex */

        if( recordNumberIndex < nonObdFFDRecordNum )                                                                                            /* [GUD:if] recordNumberIndex */
        {
            if( Dem_TmpEventMemoryEntry.ResultOfComparingFFRecords[freezeFrameRecordIndex] == DEM_IRT_NG )                                      /* [GUD] freezeFrameRecordIndex */
            {
                /* In the freeze frame record, there was difference between RAM and temporary. */

                resultOfSetFFRec = Dem_DataMngC_SetFreezeFrameRecord( recordNumberIndex, &Dem_TmpEventMemoryEntry.FreezeFrameRecordList[freezeFrameRecordIndex] );  /* [GUD] freezeFrameRecordIndex */

                if( resultOfSetFFRec != DEM_IRT_OK )
                {
                    break;
                }
            }
        }
    }

    return ;
}

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_StoreFFROverwriteFromTmp                        */
/* Description   | If freeze frame record which reuse from fault record to  */
/*               | be overwritten remained, clear it.                       */
/*               | If freeze frame record which reuse from fault record not */
/*               | to be overwritten exists, store it.                      */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_StoreFFROverwriteFromTmp
( void )
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) frOverwrittenIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ffrIndex;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

    for( frOverwrittenIndex = (Dem_u08_FFListIndexType)0U; frOverwrittenIndex < nonOBDFFRClassPerDTCMaxNum; frOverwrittenIndex++ )  /* [GUD:for] frOverwrittenIndex */
    {
        faultIndex = Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].FaultIndex;              /* [GUD] frOverwrittenIndex */

        /* Dem_TmpEventMemoryEntry.EventRecord.FaultIndex is guaranteed. */

        if( faultIndex == Dem_TmpEventMemoryEntry.EventRecord.FaultIndex )
        {
            /* In case which the fault index indicates a fault record which to be overwritten. */

            ffrIndex = Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[frOverwrittenIndex].RecordNumberIndex;     /* [GUD] frOverwrittenIndex */

            if( ffrIndex < nonObdFFDRecordNum )
            {
                /* In case the freeze frame record index is valid. */

                /* Clears freeze frame record not reused in the fault record overwritten. */
                /* Not check return value, as ffrIndex is valid. */
                (void)Dem_DataMngC_ClearFreezeFrameRecord( ffrIndex );  /* no return check required */
                Dem_DataMngM_UpdateSearchFFDIndex( ffrIndex );

                if( Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfFreezeFrameRecords > (Dem_u08_FFDIndexType)0U )
                {
                    Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfFreezeFrameRecords--;
                }
            }
        }
    }

    return;
}
#endif  /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */
#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_Data_StoreFFROverwriteFromTmp                        */
/* Description   | If freeze frame record which reuse from fault record to  */
/*               | be overwritten remained, clear it.                       */
/*               | If freeze frame record which reuse from fault record not */
/*               | to be overwritten exists, store it.                      */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_StoreFFROverwriteFromTmp
( void )
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) frOverwrittenIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ffrIndex;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

    for( frOverwrittenIndex = (Dem_u08_FFListIndexType)0U; frOverwrittenIndex < nonOBDFFRClassPerDTCMaxNum; frOverwrittenIndex++ )  /* [GUD:for] frOverwrittenIndex */
    {
        faultIndex = Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].FaultIndex;               /* [GUD] frOverwrittenIndex */

        /* Dem_TmpEventMemoryEntry.EventRecord.FaultIndex is guaranteed. */

        if( faultIndex == Dem_TmpEventMemoryEntry.EventRecord.FaultIndex )
        {
            /* In case which the fault index indicates a fault record which to be overwritten. */

            ffrIndex = Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].RecordNumberIndex;      /* [GUD] frOverwrittenIndex */

            if( ffrIndex < nonObdFFDRecordNum )
            {
                /* In case the freeze frame record index is valid. */

                /* Clears freeze frame record not reused in the fault record overwritten. */
                /* Not check return value, as ffrIndex is valid. */
                (void)Dem_DataMngC_ClearFreezeFrameRecord( ffrIndex );  /* no return check required */
                Dem_DataMngM_UpdateSearchFFDIndex( ffrIndex );

                if( Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfFreezeFrameRecords > (Dem_u08_FFDIndexType)0U )
                {
                    Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfFreezeFrameRecords--;
                }
            }
        }
    }

    return;
}
#endif  /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_OFF ) */
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_Data_StoreEventMemoryRecordFromTmp                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_StoreEventMemoryRecordFromTmp
( void )
{
    Dem_DataMngC_SetEventMemoryRecord( &Dem_TmpEventMemoryEntry.EventMemoryRecordList );

    return ;
}

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/*************************************************************************************/
/* Function Name | Dem_Data_RemoveNonObdFreezeFrame                                  */
/* Description   | When more than maxNumberOfDTCToStoreFreezeFrame FFRs are stored,  */
/*               | remove excess FFRs.                                               */
/* Preconditions |                                                                   */
/* Parameters    | none                                                              */
/* Return Value  | none                                                              */
/* Notes         |                                                                   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*************************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_RemoveNonObdFreezeFrame
( void )
{
    VAR( boolean, AUTOMATIC ) dummyAllObdDTCFreezeFlag;
    VAR( uint8, AUTOMATIC ) numberOfDTCsToStoreFreezeFrame;
    VAR( Dem_u08_MaxNumberOfDTCToStoreFreezeFrameType, AUTOMATIC ) maxNumberOfDTCToStoreFreezeFrame;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) loopIndex;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) ffrIndex;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFaultRecord;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) consistencyId;
    VAR( Dem_EventMemoryRecordType, AUTOMATIC ) eventMemoryRecord;
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )    /* [FuncSw] */
    VAR( boolean, AUTOMATIC ) tsffExistFlag;
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;
    maxNumberOfDTCToStoreFreezeFrame = Dem_MaxNumberOfDTCToStoreFreezeFrame;
    numberOfDTCsToStoreFreezeFrame = Dem_DataMngC_GetNumberOfDTCsToStoreFreezeFrame( &dummyAllObdDTCFreezeFlag );

    if ( (Dem_u08_MaxNumberOfDTCToStoreFreezeFrameType)numberOfDTCsToStoreFreezeFrame > maxNumberOfDTCToStoreFreezeFrame )
    {
        faultIndex = Dem_DcEeo_GetFaultIndexOfLowestPriorityNonOBDDTCtoStoreFreezeFrame();
        if ( faultIndex != (Dem_u08_FaultIndexType)DEM_FAULTINDEX_INITIAL )
        {
            retGetFaultRecord = Dem_DataMngC_GetFaultRecord( faultIndex, &faultRecord );
            if( retGetFaultRecord == DEM_IRT_OK )
            {
                Dem_DataMngC_GetEventMemoryRecord( &eventMemoryRecord );

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )    /* [FuncSw] */
                Dem_Data_ClearTSFFListRecord( &faultRecord );
                tsffExistFlag = Dem_DataMngC_InitTimeSeriesFreezeFrameListIndexRemoveNonObdFreeze( faultIndex );
                if ( tsffExistFlag == (boolean)TRUE)
                {
                    Dem_EventDisplacement.TSFFDeleteByFFROverwritten = (boolean)TRUE;
                }
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

                for ( loopIndex = (Dem_u08_FFListIndexType)0U; loopIndex < nonOBDFFRClassPerDTCMaxNum; loopIndex++ )    /* [GUD:for] loopIndex */
                {
                    ffrIndex = faultRecord.RecordNumberIndex[loopIndex];                                                /* [GUD] loopIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / loopIndex */
                    if ( ffrIndex < nonObdFFDRecordNum )
                    {
                        eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
                        consistencyId = DEM_CONSISTENCY_INITIAL;

                        /* Initializes freeze frame record index in the fault record which to be overwritten. */
                        Dem_DataMngC_InitRecordNumberIndexFFROverwritten( faultIndex, ffrIndex, &eventStrgIndex, &consistencyId );

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                        Dem_Similar_SetConsistencyId( eventStrgIndex, consistencyId );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */

                        (void)Dem_DataMngC_ClearFreezeFrameRecord( ffrIndex ); /* no return check required */
                        Dem_DataMngM_UpdateSearchFFDIndex( ffrIndex );

                        if( eventMemoryRecord.NumberOfFreezeFrameRecords > (uint16)0U )
                        {
                            /* Decrement the number of freeze frame records. */
                            eventMemoryRecord.NumberOfFreezeFrameRecords--;
                        }
                    }
                }
                Dem_DataMngC_SetEventMemoryRecord( &eventMemoryRecord );
            }
        }
    }
    return ;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_SetPairObdFFRecordIndex                         */
/* Description   | Set pair obd freeze frame record index                   */
/* Preconditions |                                                          */
/* Parameters    | [in] Trigger :                                           */
/*               |        The trigger for capture.                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Update                               */
/*               |        DEM_IRT_NG : Don't update                         */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SetPairObdFFRecordIndex
( void )
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetMisfirePairEvent;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) pairFaultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( boolean, AUTOMATIC ) misfObdRecordNumberIndexSyncStatus;

    misfObdRecordNumberIndexSyncStatus   =   Dem_Misfire_GetObdRecordNumberIndexSyncStatus();
    if( misfObdRecordNumberIndexSyncStatus == (boolean)TRUE )
    {
        /*  sync ObdRecordNumberIndex. copy ObdRecordNumberIndex[] to pair fault record.    */
        resultGetMisfirePairEvent= Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( Dem_TmpEventMemoryEntry.EventStrgIndex, &misfirePairEventStrgIndex );
        if( resultGetMisfirePairEvent == DEM_IRT_OK )
        {
            resultOfGetFaultIndex = Dem_DataMngC_GetER_FaultIndex( misfirePairEventStrgIndex, &pairFaultIndex );    /* [GUD:RET:DEM_IRT_OK] misfirePairEventStrgIndex */
            if( resultOfGetFaultIndex == DEM_IRT_OK )
            {
                failRecordNum = Dem_FailRecordNum;
                if( pairFaultIndex < failRecordNum )
                {
                    Dem_DataMngC_CopyFR_AllObdRecordNumberIndex( pairFaultIndex, Dem_TmpEventMemoryEntry.EventRecord.FaultIndex );
                }
            }
        }
    }

    return;
}
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */
#endif /* ( DEM_OBDONUDS_SUPPORT == STD_ON ) */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_NotifyMILFaultRegistComplete                    */
/* Description   | Notification of MIL record registration completion       */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*               | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_NotifyMILFaultRegistComplete
( void )
{
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;

    /* When the retrieving of registering MIL fault location has been only succeeded, continue storing. */
    if( Dem_TmpEventMemoryEntry.ResultOfGetMILFaultRegistLocation == DEM_IRT_OK )
    {
        orderListIndex = (Dem_u08_OrderIndexType)Dem_TmpEventMemoryEntry.BeforeNumberOfObdMILDTCs;

        /* Notifies completion of fault registration. */
        Dem_OdrLst_MIL_RegistComplete( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex, orderListIndex, Dem_TmpEventMemoryEntry.FaultRecord.MILOccurrenceOrder );
    }

    return ;
}
#endif /* ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Data_NotifyFaultRegistComplete                       */
/* Description   | Notification of Fault record registration completion     */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*               | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_NotifyFaultRegistComplete
( void )
{
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;

    /* When the retrieving of registering fault location has been only succeeded, continue storing. */
    if( Dem_TmpEventMemoryEntry.ResultOfGetFaultRegistLocation == DEM_IRT_OK )
    {
        /* Provides the number of event memory entries before being updated. */
        orderListIndex = Dem_TmpEventMemoryEntry.BeforeNumberOfEventMemoryEntries;

        /* Notifies completion of fault registration. */
        Dem_OdrLst_Fault_RegistComplete( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex, orderListIndex, Dem_TmpEventMemoryEntry.FaultRecord.OccurrenceOrder );
    }
    return ;
}

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_NotifyConfirmedFaultRegistComplete              */
/* Description   | Notification of ConfirmedFault record registration       */
/*               | completion                                               */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*               | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_NotifyConfirmedFaultRegistComplete
( void )
{
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;

    /* When the retrieving of registering confirmed fault location has been only succeeded, continue storing. */
    if( Dem_TmpEventMemoryEntry.ResultOfGetConfirmedFaultRegistLocation == DEM_IRT_OK )
    {
        /* Provides the number of event memory entries before being updated. */
        orderListIndex = (Dem_u08_OrderIndexType)Dem_TmpEventMemoryEntry.BeforeNumberOfConfirmedDTCs;

        /* completion of fault registration. */
        Dem_OdrLst_Confirmed_RegistComplete( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex, orderListIndex, Dem_TmpEventMemoryEntry.FaultRecord.ConfirmedOccurrenceOrder );
    }
    return ;
}
#endif  /* ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )     */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
