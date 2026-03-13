/* Dem_DataCtl_EventEntry02Make_Fault_c(v5-8-0)                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_EventEntry02Make_Fault/CODE                   */
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
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Rc_OdrLst.h"
#include "../../../inc/Dem_Pm_DataEeo.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

#include "Dem_DataCtl_local.h"
#include "Dem_DataCtl_EventEntry_local.h"

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Data_SetNewFaultInfo
(
    P2CONST( Dem_OrderListOccurredFlagType, AUTOMATIC, AUTOMATIC ) OccurFlagPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetEventDisplacement
( void );

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_SetObdFaultRecOverwritten
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FaultRecordPtr
);
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */

static FUNC( void, DEM_CODE ) Dem_Data_SetFaultRecOverwritten
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FaultRecordPtr
);

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
static FUNC( void, AUTOMATIC ) Dem_Data_Copy_FaultRecordOverwritten
( void );
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_SetFaultRecordTSFFRemove
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FaultRecordPtr
);
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )     */

static FUNC( void, DEM_CODE ) Dem_Data_SetFaultRecOverwrite
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) FaultOccurrenceOrder,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetNewFaultOccurrenceToTmp
( void );

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetNewConfirmedFaultOccurrenceToTmp
(
    VAR( boolean, AUTOMATIC ) ConfirmedOccurFlag
);

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_SetNextConfirmedFaultOccurrenceOrderToTmp
( void );
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )  */

static FUNC( Dem_u08_InternalReturnType, DEM_CODE) Dem_Data_UpdateFaultInfo
(
    P2CONST( Dem_OrderListOccurredFlagType, AUTOMATIC, AUTOMATIC ) OccurFlagPtr
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
/* Function Name | Dem_Data_SetFaultInfo                                    */
/* Description   | Sets the fault record related information of the event - */
/*               | memory entry of the temporary domain.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] OccurFlagPtr :                                      */
/*               |        When it shift to "Confirmed", TRUE is set.        */
/*               |        When it shift to "MIL", TRUE is set.              */
/*               | [out] FaultOccurrenceFlagPtr :                           */
/*               |        When temporary memory was changed, TRUE is set.   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Fault record related information se- */
/*               |        tting succeeds or has been already set.           */
/*               |        DEM_IRT_NG : Event memory overflows and occurs.   */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetFaultInfo
(
    P2CONST( Dem_OrderListOccurredFlagType, AUTOMATIC, AUTOMATIC ) OccurFlagPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )      FaultOccurrenceFlagPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                     retSetFaultInfo;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                     retVal;

    retVal                      = DEM_IRT_NG;
    *FaultOccurrenceFlagPtr     = (boolean)FALSE;

    /* Checks whether the fault index is valid. */
    if( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex == DEM_FAULTINDEX_INITIAL )
    {
        /* Information related to the occurrence of a new failure is set in the event memory entry of the temporary area. */
        retSetFaultInfo = Dem_Data_SetNewFaultInfo( OccurFlagPtr );
        if( retSetFaultInfo == DEM_IRT_OK )
        {
            *FaultOccurrenceFlagPtr = (boolean)TRUE;
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* No Process */
        }
    }
    else
    {
        retVal = Dem_Data_UpdateFaultInfo( OccurFlagPtr );

        *FaultOccurrenceFlagPtr = (boolean)TRUE;
    }

    /* Returns with the result. */
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_SetNewFaultInfo                                 */
/* Description   | Save to new primary area (temporary) before setting RAM  */
/* Preconditions |                                                          */
/* Parameters    | [in] OccurFlagPtr : Occurred flag pointer.               */
/*               |        ConfirmedOccurFlag.                               */
/*               |        MILOccurFlag.                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetNewFaultInfo
(
    P2CONST( Dem_OrderListOccurredFlagType, AUTOMATIC, AUTOMATIC ) OccurFlagPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;

    /* Information related to the occurrence of a new failure is set in the event memory entry of the temporary area. */
    retVal = Dem_Data_SetNewFaultOccurrenceToTmp();

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )   /*  [FuncSw]    */
    /* Checks the result of setting of new failure. */
    if( retVal == DEM_IRT_OK )
    {
        retVal = Dem_Data_SetNewConfirmedFaultOccurrenceToTmp( OccurFlagPtr->ConfirmedOccurFlag );
    }
#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )  */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )     /*  [FuncSw]    */
    if( retVal == DEM_IRT_OK )
    {
        retVal = Dem_Data_SetNewMILOccurrenceToTmp( OccurFlagPtr->MILOccurFlag );
    }
#endif  /*   ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )    */

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_SetNewFaultOccurrenceToTmp                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetNewFaultOccurrenceToTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetting;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) occurrenceOrder;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;

    retVal = DEM_IRT_NG;
    failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;

    if( Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfEventMemoryEntries < failRecordNum )  /* [GUD:if]Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfEventMemoryEntries */
    {
        orderListIndex = Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfEventMemoryEntries;  /* [GUD]orderListIndex( == Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfEventMemoryEntries ) */
        faultIndex = DEM_FAULTINDEX_INITIAL;
        occurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;

        resultOfGetting = Dem_OdrLst_Fault_GetOccrOrderValue( orderListIndex, &faultIndex, &occurrenceOrder );  /* [GUD]orderListIndex *//* [GUD:RET:DEM_IRT_OK] faultIndex *//* [GUD:RET:DEM_IRT_OK] occurrenceOrder */

        if( resultOfGetting == DEM_IRT_OK )
        {
            Dem_TmpEventMemoryEntry.EventRecord.FaultIndex = faultIndex;                                        /* [GUD]faultIndex */

            Dem_TmpEventMemoryEntry.FaultRecord.EventStrgIndex = Dem_TmpEventMemoryEntry.EventStrgIndex;

            Dem_TmpEventMemoryEntry.FaultRecord.OccurrenceOrder = occurrenceOrder;                              /* [GUD]occurrenceOrder */

            Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfEventMemoryEntries++;

            retVal = DEM_IRT_OK;
        }
        else
        {
            /* No Process */
        }

        /* Saves the result of retrieving of registering fault location. */
        Dem_TmpEventMemoryEntry.ResultOfGetFaultRegistLocation = resultOfGetting;

    }
    else
    {
        retVal = Dem_Data_SetEventDisplacement();
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_SetEventDisplacement                            */
/* Description   | Sets fault record which to be overwritten and which to   */
/*               | overwrite.                                               */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The fault record will be overwritten */
/*               |        DEM_IRT_NG : The fault record will not be overwr- */
/*               |                     itten                                */
/*               |                                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetEventDisplacement
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRecord;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetNextOrder;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) faultOccurrenceOrder;
    VAR( Dem_FaultRecordPtrForCtlType, AUTOMATIC ) faultRecordPtrCtl;
    VAR( Dem_EventEntryOverwriteFaultInfoType, AUTOMATIC ) eeoFaultInfo;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    /* Sets return value to the fault record will not be overwritten. */
    retVal = DEM_IRT_NG;

    /* Gets event priority by event index of temporary area. */
    eeoFaultInfo.EventPriority = Dem_CfgInfoPm_GetEventPriority( Dem_TmpEventMemoryEntry.EventStrgIndex );  /* [GUDCHK:SETVAL]Dem_TmpEventMemoryEntry.EventStrgIndex */
    eeoFaultInfo.StatusOfDTC = Dem_EventDisplacement.DTCStatusForFaultRecordOverwrite;
    eeoFaultInfo.EventStrgIndex = Dem_TmpEventMemoryEntry.EventStrgIndex;

    /* Gets a fault index to overwrite fault record. */
    faultIndex = Dem_DcEeo_GetFaultIndexOfFaultRecordOverwrite( &eeoFaultInfo );

    resultOfGetFaultRecord = Dem_DataMngC_GetFaultRecordAddress( faultIndex, &faultRecordPtrCtl );

    if( resultOfGetFaultRecord == DEM_IRT_OK )
    {
        eventStorageNum = Dem_PrimaryMemEventStorageNum;
        eventStrgIndex  = faultRecordPtrCtl.FaultRecordPtr->EventStrgIndex;
        if ( eventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]eventStrgIndex */
        {
            /* Gets a fault occurrencd order from fault order list. */
            resultOfGetNextOrder = Dem_OdrLst_Fault_GetNextOccurrenceOrder( &faultOccurrenceOrder );

            if( resultOfGetNextOrder == DEM_IRT_OK )
            {

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
                Dem_Data_SetObdFaultRecOverwritten( faultIndex, faultRecordPtrCtl.FaultRecordPtr );
#endif  /*   ( DEM_OBDFFD_SUPPORT == STD_ON )          */

                Dem_Data_SetFaultRecOverwritten( faultIndex, faultRecordPtrCtl.FaultRecordPtr );

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) /* [FuncSw] */
                Dem_Data_Copy_FaultRecordOverwritten();
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /*  [FuncSw]    */
                Dem_Data_SetFaultRecordTSFFRemove( faultIndex, faultRecordPtrCtl.FaultRecordPtr );
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )         */
                Dem_Data_SetFaultRecOverwrite( faultIndex, faultOccurrenceOrder, eventStrgIndex );

                /* Retains next fault occurrence order due to add one to next occurrence order when storing from temporary area to RAM, */
                Dem_EventDisplacement.NextFaultOccurrenceOrder = faultOccurrenceOrder;

                /* Sets return value to the fault record will be overwritten. */
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
/****************************************************************************/
/* Function Name | Dem_Data_SetEventDisplacement                            */
/* Description   | Sets fault record which to be overwritten and which to   */
/*               | overwrite.                                               */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : The fault record will be overwritten */
/*               |        DEM_IRT_NG : The fault record will not be overwr- */
/*               |                     itten                                */
/*               |                                                          */
/* Notes         | -                                                        */
/****************************************************************************/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetEventDisplacement
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Sets return value to the fault record will not be overwritten. */
    retVal = DEM_IRT_NG;

    return retVal;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_OFF ) */


#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_SetObdFaultRecOverwritten                       */
/* Description   | Sets fault record which to be overwritten for OBD.       */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex : Dem_FaultRecordList array's index      */
/*               | [in] FaultRecordPtr : The fault record to overwrite      */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_SetObdFaultRecOverwritten
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FaultRecordPtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) indexOfRecordNumberIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;

    obdFFRClassPerDTCMaxNum = Dem_CfgInfoPm_GetOBDFFRClassPerDTCMaxNum();
    obdFFDRecordNum = Dem_CfgInfoPm_GetObdFFDRecordNum();

    for( indexOfRecordNumberIndex = (Dem_u08_FFListIndexType)0U; indexOfRecordNumberIndex < obdFFRClassPerDTCMaxNum; indexOfRecordNumberIndex++ )                           /* [GUD:for]indexOfRecordNumberIndex */
    {
        if( FaultRecordPtr->ObdRecordNumberIndex[indexOfRecordNumberIndex] < obdFFDRecordNum )                                                                              /* [GUD]indexOfRecordNumberIndex *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / indexOfRecordNumberIndex */
        {
            Dem_EventDisplacement.ObdFaultRecordOverwritten[indexOfRecordNumberIndex].FaultIndex = FaultIndex;                                                              /* [GUD]indexOfRecordNumberIndex */
            Dem_EventDisplacement.ObdFaultRecordOverwritten[indexOfRecordNumberIndex].EventStrgIndex = FaultRecordPtr->EventStrgIndex;                                      /* [GUD]indexOfRecordNumberIndex */
            Dem_EventDisplacement.ObdFaultRecordOverwritten[indexOfRecordNumberIndex].RecordNumberIndex = FaultRecordPtr->ObdRecordNumberIndex[indexOfRecordNumberIndex];   /* [GUD]indexOfRecordNumberIndex *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / indexOfRecordNumberIndex */
        }
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_Data_SetFaultRecOverwritten                          */
/* Description   | Sets fault record which to be overwritten.               */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex : Dem_FaultRecordList array's index      */
/*               | [in] FaultRecordPtr : The fault record which to be       */
/*               |                       overwritten                        */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SetFaultRecOverwritten
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FaultRecordPtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) indexOfRecordNumberIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

    for( indexOfRecordNumberIndex = (Dem_u08_FFListIndexType)0U; indexOfRecordNumberIndex < nonOBDFFRClassPerDTCMaxNum; indexOfRecordNumberIndex++ )                /* [GUD:for]indexOfRecordNumberIndex */
    {
        if( FaultRecordPtr->RecordNumberIndex[indexOfRecordNumberIndex] < nonObdFFDRecordNum )                                                                      /* [GUD]indexOfRecordNumberIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / indexOfRecordNumberIndex */
        {
            Dem_EventDisplacement.FaultRecordOverwritten[indexOfRecordNumberIndex].FaultIndex = FaultIndex;                                                         /* [GUD]indexOfRecordNumberIndex */
            Dem_EventDisplacement.FaultRecordOverwritten[indexOfRecordNumberIndex].EventStrgIndex = FaultRecordPtr->EventStrgIndex;                                 /* [GUD]indexOfRecordNumberIndex */
            Dem_EventDisplacement.FaultRecordOverwritten[indexOfRecordNumberIndex].RecordNumberIndex = FaultRecordPtr->RecordNumberIndex[indexOfRecordNumberIndex]; /* [GUD]indexOfRecordNumberIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / indexOfRecordNumberIndex */
        }
    }

    return;
}

#if ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_Copy_FaultRecordOverwritten                     */
/* Description   | copy FaultRecordOverwritten from EventDisplacement       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, AUTOMATIC ) Dem_Data_Copy_FaultRecordOverwritten
( void )
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) loopIndex;

    nonOBDFFRClassPerDTCMaxNum = (Dem_u08_FFDIndexType)Dem_NonOBDFFRClassPerDTCMaxNum;

    for ( loopIndex = (Dem_u08_FFDIndexType)0U; loopIndex < nonOBDFFRClassPerDTCMaxNum; loopIndex++ )   /* [GUD:for]loopIndex */
    {
        /* Copy from EventDisplacement */
        Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[loopIndex].FaultIndex = Dem_EventDisplacement.FaultRecordOverwritten[loopIndex].FaultIndex;               /* [GUD]loopIndex */
        Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[loopIndex].EventStrgIndex = Dem_EventDisplacement.FaultRecordOverwritten[loopIndex].EventStrgIndex;       /* [GUD]loopIndex */
        Dem_Data_CopyEventDisplacement_FaultRecordOverwritten[loopIndex].RecordNumberIndex = Dem_EventDisplacement.FaultRecordOverwritten[loopIndex].RecordNumberIndex; /* [GUD]loopIndex */
    }
}
#endif /* ( DEM_MAX_NUM_OF_FREEZE_FRAME_TRIGGER_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Data_SetFaultRecordTSFFRemove                        */
/* Description   | Sets fault record which to remove time-series freeze     */
/*               | frame.                                                   */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex : Dem_FaultRecordList array's index      */
/*               | [in] FaultRecordPtr : The fault record which to be       */
/*               |                       overwritten                        */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_SetFaultRecordTSFFRemove
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,    /* MISRA DEVIATION */
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FaultRecordPtr
)
{
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) indexOfTSFFListIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;

    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;
    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;

    for( indexOfTSFFListIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; indexOfTSFFListIndex < tsffRecordClassNumPerDTCMaxNum; indexOfTSFFListIndex++ )    /* [GUD:for]indexOfTSFFListIndex */
    {
        if( FaultRecordPtr->TimeSeriesFreezeFrameListIndex[indexOfTSFFListIndex] < tsffTotalDTCNum )                                                    /* [GUD]indexOfTSFFListIndex *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / indexOfTSFFListIndex */
        {
            Dem_EventDisplacement.FaultRecordTSFFRemove[indexOfTSFFListIndex] = FaultRecordPtr->TimeSeriesFreezeFrameListIndex[indexOfTSFFListIndex];   /* [GUD]indexOfTSFFListIndex *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / indexOfTSFFListIndex */
        }
    }

    return;
}
#endif /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_Data_SetFaultRecOverwrite                            */
/* Description   | Sets fault record which to overwrite.                    */
/* Preconditions |                                                          */
/* Parameters    | [in] FaultIndex : Dem_FaultRecordList array's index      */
/*               | [in] FaultOccurrenceOrder : Order for fault occurrence   */
/*               | [in] FaultRecordPtr : The fault record which to be       */
/*               |                       overwritten                        */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_SetFaultRecOverwrite
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) FaultOccurrenceOrder,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;

    Dem_EventDisplacement.EventStrgIndexOfFaultRecordOverwritten = EventStrgIndex;

    /*  get overwritten statusofDTC.    */
    (void)Dem_DataMngC_GetER_StatusOfDTC( Dem_EventDisplacement.EventStrgIndexOfFaultRecordOverwritten, &statusOfDTC ); /* no return check required */
    Dem_EventDisplacement.DTCStatusAtFaultRecordOverwritten  =   statusOfDTC;

    /*  overwrite fault record.         */
    Dem_TmpEventMemoryEntry.EventRecord.FaultIndex = FaultIndex;

    Dem_DataMngC_InitFaultCtlRecordData( &Dem_TmpEventMemoryEntry.FaultRecord );

    Dem_TmpEventMemoryEntry.FaultRecord.EventStrgIndex = Dem_TmpEventMemoryEntry.EventStrgIndex;
    Dem_TmpEventMemoryEntry.FaultRecord.OccurrenceOrder = FaultOccurrenceOrder;

    return;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_SetNewConfirmedFaultOccurrenceToTmp             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ConfirmedOccurFlag                                       */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SetNewConfirmedFaultOccurrenceToTmp
(
    VAR( boolean, AUTOMATIC ) ConfirmedOccurFlag
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetting;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) confirmedOccurrenceOrder;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) failRecordNum;

    if ( ConfirmedOccurFlag == (boolean)TRUE )
    {
        retVal = DEM_IRT_NG;
        failRecordNum = (Dem_u08_OrderIndexType)Dem_FailRecordNum;

        if( Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfConfirmedDTCs < failRecordNum )
        {
            orderListIndex = Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfConfirmedDTCs;
            confirmedOccurrenceOrder = DEM_FAIL_OCCURRENCE_NUM_INVALID;
            resultOfGetting = Dem_OdrLst_Confirmed_GetOccrOrderValue( orderListIndex, &confirmedOccurrenceOrder );
            if( resultOfGetting == DEM_IRT_OK )
            {
                Dem_TmpEventMemoryEntry.FaultRecord.ConfirmedOccurrenceOrder = confirmedOccurrenceOrder;
                Dem_TmpEventMemoryEntry.EventMemoryRecordList.NumberOfConfirmedDTCs++;
                retVal = DEM_IRT_OK;
            }
            Dem_TmpEventMemoryEntry.ResultOfGetConfirmedFaultRegistLocation = resultOfGetting;
        }
        else
        {
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /* [FuncSw] */
            Dem_Data_SetNextConfirmedFaultOccurrenceOrderToTmp();
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */
            retVal = DEM_IRT_OK;
        }
    }
    else
    {
        retVal = DEM_IRT_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Data_SetNextConfirmedFaultOccurrenceOrder            */
/* Description   | Gets next confirmed fault occurrence order and retains.  */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_SetNextConfirmedFaultOccurrenceOrderToTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetNextOrder;
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) confirmedOccurrenceOrder;

    /* Gets a confirmed fault occurrencd order from confirmed fault order list. */
    resultOfGetNextOrder = Dem_OdrLst_Confirmed_GetNextOccurrenceOrder( &confirmedOccurrenceOrder );

    if( resultOfGetNextOrder == DEM_IRT_OK )
    {
        /* Retains the confirmed fault occurrence order due to add one to next occurrence order when storing from temporary area to RAM, */
        Dem_EventDisplacement.NextConfirmedFaultOccurrenceOrder = confirmedOccurrenceOrder;

        /* Retains the confirmed fault occurrence order to fault record of temporary area. */
        Dem_TmpEventMemoryEntry.FaultRecord.ConfirmedOccurrenceOrder = confirmedOccurrenceOrder;
    }

    return;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )  */


/****************************************************************************/
/* Function Name | Dem_Data_CheckExistsEventMemoryEntryOfTmp                */
/* Description   | Event memory information registration judgment of the    */
/*               | temporary area.                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE : Exist of the event memory entry.           */
/*               |        FALSE : No exist of the event memory entry.       */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_Data_CheckExistsEventMemoryEntryOfTmp
( void )
{
    VAR( boolean, AUTOMATIC ) retVal;

    if( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex != DEM_FAULTINDEX_INITIAL )
    {
        retVal = (boolean)TRUE;
    }
    else
    {
        retVal = (boolean)FALSE;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_SetAgingCounterToTmp                            */
/* Description   | Set aging counter in the temporary area.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] AgingCounter : Aging counter.                       */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SetAgingCounterToTmp
(
    VAR( Dem_u08_AgingCounterType, AUTOMATIC ) AgingCounter
)
{
    Dem_TmpEventMemoryEntry.FaultRecord.AgingCounter = AgingCounter;

    return;
}

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_SetTimeAgingCounterToTmp                        */
/* Description   | Set time aging counter in the temporary area.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] TimeAgingCounter : Time Aging counter.              */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Data_SetAgingCounterToTmp.     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SetTimeAgingCounterToTmp
(
    VAR( Dem_u16_WWHOBDTimeAgingCounterType, AUTOMATIC ) TimeAgingCounter
)
{
    Dem_TmpEventMemoryEntry.FaultRecord.TimeAgingCounter = TimeAgingCounter;

    return;
}
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Data_UpdateFaultInfo                                 */
/* Description   | Save to update primary area (temporary) before setting R-*/
/*               | AM                                                       */
/* Preconditions |                                                          */
/* Parameters    | [in] OccurFlagPtr : Occurred flag pointer.               */
/*               |        ConfirmedOccurFlag.                               */
/*               |        MILOccurFlag.                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_UpdateFaultInfo
(
    P2CONST( Dem_OrderListOccurredFlagType, AUTOMATIC, AUTOMATIC ) OccurFlagPtr    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;
#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retValNewOccurrence;
#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )  */

    retVal = DEM_IRT_OK;

#if ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )   /*  [FuncSw]    */
    retValNewOccurrence = Dem_Data_SetNewConfirmedFaultOccurrenceToTmp( OccurFlagPtr->ConfirmedOccurFlag );
    if( retValNewOccurrence != DEM_IRT_OK )
    {
        retVal = DEM_IRT_NG;
    }
#endif  /*   ( DEM_ORDERTYPE_CONFIRMED_USE == STD_ON )  */

#if ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )     /*  [FuncSw]    */
    if( retVal == DEM_IRT_OK )
    {
        retVal = Dem_Data_SetNewMILOccurrenceToTmp( OccurFlagPtr->MILOccurFlag );
    }
#endif  /*   ( DEM_PFC_ORDER_MIL_SUPPORT == STD_ON )    */

    /* Clear AgingCount */
    Dem_TmpEventMemoryEntry.FaultRecord.AgingCounter        = DEM_AGING_COUNT_INITIAL_VALUE;

#if ( DEM_WWH_OBD_SUPPORT == STD_ON ) /* [FuncSw] */
    /* Clear TimeAgingCount */
    Dem_TmpEventMemoryEntry.FaultRecord.TimeAgingCounter    = DEM_TIME_AGING_COUNT_INITIAL_VALUE;
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

    /* Clear HealingCount */
    Dem_TmpEventMemoryEntry.FaultRecord.HealingCounter      = DEM_HEALING_COUNT_INITIAL_VALUE;

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Data_GetAgingCounterFromTmp                          */
/* Description   | Get aging counter from the temporary area.               */
/* Preconditions | none                                                     */
/* Parameters    | [out] AgingCounterPtr : Aging counter.                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Aging counter get success.           */
/*               |        DEM_IRT_NG : Aging counter get failure.           */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetAgingCounterFromTmp
(
    P2VAR( Dem_u08_AgingCounterType, AUTOMATIC, AUTOMATIC ) AgingCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    if( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex != DEM_FAULTINDEX_INITIAL )
    {
        *AgingCounterPtr    = Dem_TmpEventMemoryEntry.FaultRecord.AgingCounter;
         retVal             = DEM_IRT_OK;
    }

    return retVal;
}

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetTimeAgingCounterFromTmp                      */
/* Description   | Get time aging counter from the temporary area.          */
/* Preconditions | none                                                     */
/* Parameters    | [out] TimeAgingCounterPtr : Time aging counter.          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Time aging counter get success.      */
/*               |        DEM_IRT_NG : Time aging counter get failure.      */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Data_GetAgingCounterFromTmp.   */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetTimeAgingCounterFromTmp
(
    P2VAR( Dem_u16_WWHOBDTimeAgingCounterType, AUTOMATIC, AUTOMATIC ) TimeAgingCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    if( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex != DEM_FAULTINDEX_INITIAL )
    {
        *TimeAgingCounterPtr    = Dem_TmpEventMemoryEntry.FaultRecord.TimeAgingCounter;
         retVal                 = DEM_IRT_OK;
    }

    return retVal;
}
#endif /* ( DEM_WWH_OBD_SUPPORT == STD_ON ) */

#if ( DEM_INDICATOR_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_SetHealingCounterToTmp                          */
/* Description   | Set MIL lighting state healing counter in the            */
/*               | temporary area.                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] HealingCounter : MIL lighting state healing counter */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SetHealingCounterToTmp
(
    VAR( Dem_u08_HealingCounterType, AUTOMATIC ) HealingCounter
)
{
    Dem_TmpEventMemoryEntry.FaultRecord.HealingCounter = HealingCounter;

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_GetHealingCounterFromTmp                        */
/* Description   | Get MIL lighting state healing counter from the          */
/*               | temporary area.                                          */
/* Preconditions | none                                                     */
/* Parameters    | [out] HealingCounterPtr : MIL lighting state healing     */
/*               |                           counter                        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Get success of MIL lighting state    */
/*               |                     healing counter.                     */
/*               |        DEM_IRT_NG : Get failure of MIL lighting state    */
/*               |                     healing counter.                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetHealingCounterFromTmp
(
    P2VAR( Dem_u08_HealingCounterType, AUTOMATIC, AUTOMATIC ) HealingCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    if( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex != DEM_FAULTINDEX_INITIAL )
    {
        *HealingCounterPtr          = Dem_TmpEventMemoryEntry.FaultRecord.HealingCounter;
        retVal                      = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}
#endif  /* ( DEM_INDICATOR_USE == STD_ON )  */

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_SetDTCStatusForFaultRecordOverwrite             */
/* Description   | Sets the specified DTC Status to the temporary area.     */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCStatusForFaultRecordOverwrite : New DTC Status. */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SetDTCStatusForFaultRecordOverwrite
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusForFaultRecordOverwrite
)
{
    Dem_EventDisplacement.DTCStatusForFaultRecordOverwrite = DTCStatusForFaultRecordOverwrite;

    return;
}
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-09-26                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
