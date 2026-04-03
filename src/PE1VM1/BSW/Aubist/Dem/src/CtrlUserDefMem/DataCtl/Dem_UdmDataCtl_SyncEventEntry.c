/* Dem_UdmDataCtl_SyncEventEntry_c(v5-9-0)                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_SyncEventeEntry/CODE                       */
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
#include "../../../inc/Dem_CmnLib_DataCtl_CaptureFreezeFrameClass.h"
#include "../../../inc/Dem_Utl.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_Udm_Data.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"
#include "Dem_UdmDataCtl_SyncEventEntry_local.h"
#include "Dem_UdmDataCtl_local.h"

#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
#include <Dem_SIT_RangeCheck.h>
#endif /* DEM_SIT_RANGE_CHECK */

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SaveNonObdFreezeFrameRecordToSyncTmp
( void );
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetNewFaultOccurrenceToSyncTmp
( void );
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetFFRecordIndexToSyncTmp
( void );
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetNextFFRecordIndexToSyncTmp
(
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) EmptyIndexOfFreezeFrameRecords
);
static FUNC( void, DEM_CODE ) Dem_UdmData_CaptureFreezeFrameDataToSyncTmp
(
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr
);
static FUNC( void, DEM_CODE ) Dem_UdmData_InitTmpSyncMemoryWithoutRecord
( void );
static FUNC( void, DEM_CODE ) Dem_UdmData_StoreEventMemoryEntryFromSyncTmp
( void );
static FUNC( void, DEM_CODE ) Dem_UdmData_StoreFreezeFrameRecordFromSyncTmp
( void );

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Saved temporary area of event memory entry                               */
/****************************************************************************/

static VAR( Dem_UserDefMemTmpSyncEventMemoryEntryType, DEM_VAR_NO_INIT ) Dem_UdmTmpSyncEventMemoryEntry;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_UdmData_SaveEventMemoryEntryToSyncTmp                */
/* Description   | Saves an event memory entry specified by event index to  */
/*               |  temporary area.                                         */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventIndex :                                        */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SaveEventMemoryEntryToSyncTmp
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex       /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSaveFFRec;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    retVal = DEM_IRT_OK;
    resultOfGetFaultRec = DEM_IRT_NG;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    Dem_UdmData_InitTmpSyncMemoryWithoutRecord();

    Dem_UdmTmpSyncEventMemoryEntry.UdmEventIndex = UdmEventIndex;

    /* Get udm group index. */
    udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );               /* [GUDCHK:CALLER]UdmEventIndex *//* [GUD:RET:IF_GUARDED: UdmEventIndex ]udmInfoTableIndex */
    Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, UdmEventIndex );

    if( Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex < userDefinedMemoryNum )   /* [GUD:if]Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex */
    {
        /* Exclude StatusOfDTC update process by Dem_RestartOperationCycle(Dem_MainFunction) */
#ifndef JGXSTACK
        Dem_UdmExcFncTable[Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex].ExclusiveEnterFnc();       /* [GUD]Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex */
#else   /* JGXSTACK */
        Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */

        (void)Dem_UdmEventMngC_GetRecord( UdmEventIndex, &Dem_UdmTmpSyncEventMemoryEntry.EventRecord );     /* no return check required */

#ifndef JGXSTACK
        Dem_UdmExcFncTable[Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex].ExclusiveExitFnc();        /* [GUD]Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex */
#else   /* JGXSTACK */
        Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */

        if( Dem_UdmTmpSyncEventMemoryEntry.EventRecord.UdmFaultIndex != DEM_UDMFAULTINDEX_INITIAL )
        {
            resultOfGetFaultRec = Dem_UdmFaultMngC_GetRecord( Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex, Dem_UdmTmpSyncEventMemoryEntry.EventRecord.UdmFaultIndex, &Dem_UdmTmpSyncEventMemoryEntry.FaultRecord );    /* [GUD]Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex */
            if( resultOfGetFaultRec != DEM_IRT_OK )
            {
                retVal = DEM_IRT_NG;
            }
        }
        else
        {
            Dem_UdmFaultMng_InitCtlRecordData( &Dem_UdmTmpSyncEventMemoryEntry.FaultRecord );
        }

        if( resultOfGetFaultRec == DEM_IRT_OK )
        {
            resultOfSaveFFRec = Dem_UdmData_SaveNonObdFreezeFrameRecordToSyncTmp();
            if( resultOfSaveFFRec != DEM_IRT_OK )
            {
                retVal = DEM_IRT_NG;
            }
        }

        if( retVal == DEM_IRT_OK )
        {
            Dem_UdmEventMngC_GetEventMemoryRecord( Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex, &Dem_UdmTmpSyncEventMemoryEntry.EventMemoryRecord );   /* [GUD]Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex */

            /* Saves the number of event memory entries before being updated. */
            Dem_UdmTmpSyncEventMemoryEntry.BeforeNumberOfEventMemoryEntries = Dem_UdmTmpSyncEventMemoryEntry.EventMemoryRecord.NumberOfEventMemoryEntries;
        }
    }
    else
    {
        retVal = DEM_IRT_NG;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_SaveNonObdFreezeFrameRecordToSyncTmp         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SaveNonObdFreezeFrameRecordToSyncTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetNextFFInfo;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFRec;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) startFreezeFrameRecordIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberFreezeFrameRecords;
    VAR( Dem_UdmNextFreezeFrameType, AUTOMATIC ) udmNextFreezeFrameInfo;

    retVal = DEM_IRT_NG;

    startFreezeFrameRecordIndex = Dem_UdmTmpSyncEventMemoryEntry.FaultRecord.RecordNumberIndex;
    if( startFreezeFrameRecordIndex != DEM_UDMFFRECINDEX_INITIAL )
    {
        udmGroupKindIndex = Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex;
        maxNumberFreezeFrameRecords = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( Dem_UdmTmpSyncEventMemoryEntry.UdmEventIndex );

        udmNextFreezeFrameInfo.FreezeFrameRecordIndex = DEM_UDMFFRECINDEX_INITIAL;
        udmNextFreezeFrameInfo.OccurrenceOrder = DEM_UDMOCCURRENCEORDER_INITIAL;
        udmNextFreezeFrameInfo.CidUdmFreezeFrameRecords = DEM_CONSISTENCY_INITIAL;

        resultOfGetNextFFInfo = Dem_UdmFFDMng_GetNextFreezeFrameInfo( (boolean)FALSE, udmGroupKindIndex, startFreezeFrameRecordIndex, maxNumberFreezeFrameRecords, &udmNextFreezeFrameInfo );
        if( resultOfGetNextFFInfo == DEM_IRT_OK )
        {
            /* Gets FaultIndex of the specified index for non-OBD FreezeFrameRecord. */
            resultOfGetFFRec = Dem_UdmFFDMng_GetMngInfo( Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex, udmNextFreezeFrameInfo.FreezeFrameRecordIndex, &Dem_UdmTmpSyncEventMemoryEntry.FFRMngInfo );
            if( resultOfGetFFRec == DEM_IRT_OK )
            {
                Dem_UdmTmpSyncEventMemoryEntry.OldestFreezeFrameRecordIndex = udmNextFreezeFrameInfo.FreezeFrameRecordIndex;
                Dem_UdmTmpSyncEventMemoryEntry.FFRMngInfo.OccurrenceOrder = udmNextFreezeFrameInfo.OccurrenceOrder;
                Dem_UdmTmpSyncEventMemoryEntry.FFRMngInfo.CidUdmFreezeFrameRecords = udmNextFreezeFrameInfo.CidUdmFreezeFrameRecords;

                retVal = DEM_IRT_OK;
            }
        }
    }
    else
    {
        retVal = DEM_IRT_OK;
    }


    return retVal;

}

/****************************************************************************/
/* Function Name | Dem_UdmData_SetDTCStatusToSyncTmp                        */
/* Description   | Sets the specified value to the UDS DTC status byte in - */
/*               | event memory entry of temporary area.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCStatus :                                         */
/*               |        The UDS DTC status byte which will set.           */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_SetDTCStatusToSyncTmp
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatus
)
{
    /* Sets the specified DTCStatus to StatusOfDTC of the event memory entry of temporary area. */
    Dem_UdmTmpSyncEventMemoryEntry.EventRecord.StatusOfDTC = DTCStatus;

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_GetDTCStatusFromSyncTmp                      */
/* Description   | Gets the UDS DTC status byte from the event memory entr- */
/*               | y of temporary area.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCStatusPtr :                                     */
/*               |        The UDS DTC status byte which has been retrieved. */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_GetDTCStatusFromSyncTmp
(
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    /* Stores StatusOfDTC of the event memory entry of temporary area to the specified parameter. */
    *DTCStatusPtr = Dem_UdmTmpSyncEventMemoryEntry.EventRecord.StatusOfDTC;

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_SetFaultInfoForSyncEventEntry                */
/* Description   | Sets the fault record related information of the event - */
/*               | memory entry of the temporary domain.                    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Fault record related information se- */
/*               |        tting succeeds or has been already set.           */
/*               |        DEM_IRT_NG : Event memory overflows and occurs.   */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetFaultInfoForSyncEventEntry
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSetFaultInfo;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    /* Checks whether the fault index is valid. */
    if( Dem_UdmTmpSyncEventMemoryEntry.EventRecord.UdmFaultIndex == DEM_UDMFAULTINDEX_INITIAL )
    {
        /* Information related to the occurrence of a new failure is set in the event memory entry of the temporary area. */
        retSetFaultInfo = Dem_UdmData_SetNewFaultOccurrenceToSyncTmp();
        if( retSetFaultInfo == DEM_IRT_OK )
        {
            /* Store the comparison result here because the difference in Fault Record only appears when a new failure occurs. */
            Dem_UdmTmpSyncEventMemoryEntry.ResultOfComparingFaultRecords = DEM_IRT_NG;
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
/* Function Name | Dem_UdmData_SetNewFaultOccurrenceToSyncTmp               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetNewFaultOccurrenceToSyncTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) searchUdmFaultIndex;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultIndex;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) numberEventEntryUserDefined;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) failRecordNum;

    retVal = DEM_IRT_NG;

    udmGroupKindIndex = Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex;

    /* MAX RecordNum for each Selection ID */
    numberEventEntryUserDefined = Dem_CfgInfoUdm_GetMaxNumberOfEventEntry( udmGroupKindIndex );         /* [GUDCHK:SETVAL]Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex */

    if( Dem_UdmTmpSyncEventMemoryEntry.EventMemoryRecord.NumberOfEventMemoryEntries < numberEventEntryUserDefined )
    {
        searchUdmFaultIndex = Dem_UdmData_GetSearchFRIndex( udmGroupKindIndex );                        /* [GUDCHK:SETVAL]Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex */
        udmFaultIndex = Dem_UdmFaultMngC_GetEmptyFaultIndex( udmGroupKindIndex, searchUdmFaultIndex );  /* [GUDCHK:SETVAL]Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex */
        failRecordNum = Dem_UdmFaultMngC_GetFaultRecordNum( udmGroupKindIndex );                        /* [GUDCHK:SETVAL]Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex */

        if( udmFaultIndex >= failRecordNum )
        {
            /* RAM garbled countermeasures */
            Dem_UdmData_SetSearchFRIndex( udmGroupKindIndex, failRecordNum );                           /* [GUDCHK:SETVAL]Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex */
        }
        else
        {
            /* Set FaultIndex, EventIndex, and NumberEntries to TmpEventMemoryEntry. */
            Dem_UdmTmpSyncEventMemoryEntry.EventRecord.UdmFaultIndex = udmFaultIndex;
            Dem_UdmTmpSyncEventMemoryEntry.FaultRecord.UdmEventIndex = Dem_UdmTmpSyncEventMemoryEntry.UdmEventIndex;
            /* UdmFaultOccurrenceOrder and LastOfFaultOccurrenceOrder are unused data in synchronous processing, but the same processing as asynchronous processing */
            Dem_UdmTmpSyncEventMemoryEntry.FaultRecord.UdmFaultOccurrenceOrder = Dem_UdmTmpSyncEventMemoryEntry.EventMemoryRecord.LastOfFaultOccurrenceOrder;
            Dem_UdmTmpSyncEventMemoryEntry.EventMemoryRecord.NumberOfEventMemoryEntries = Dem_UdmTmpSyncEventMemoryEntry.EventMemoryRecord.NumberOfEventMemoryEntries + (Dem_u08_OrderIndexType)1U;
            Dem_UdmTmpSyncEventMemoryEntry.EventMemoryRecord.LastOfFaultOccurrenceOrder = Dem_UdmTmpSyncEventMemoryEntry.EventMemoryRecord.LastOfFaultOccurrenceOrder + (Dem_u16_OccrOrderType)1U;
            retVal = DEM_IRT_OK;

            searchUdmFaultIndex = udmFaultIndex + (Dem_u08_UdmFaultIndexType)1U;
            Dem_UdmData_SetSearchFRIndex( udmGroupKindIndex, searchUdmFaultIndex );
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_CaptureNonObdFreezeFrameToSyncTmp            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventIndex :                                        */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] monitorData0 :                                      */
/*               |        Monitor test result                               */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_CaptureNonObdFreezeFrameToSyncTmp
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSet;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;

    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA) freezeFrameClassPtr;

    /* Checks the reference of freeze frame class. */
    Dem_CfgInfoUdm_GetFreezeFrameClassRef( UdmEventIndex, &freezeFrameClassRef );

    if( freezeFrameClassRef != DEM_FFCLASSINDEX_INVALID )                               /* [GUD:if]freezeFrameClassRef */
    {
        /* Holds the FreezeFrameClass table pointed to */
        /* by the FreezeFrameClass table list Index of the held DTCAttribute table. */
        freezeFrameClassPtr = &Dem_FreezeFrameClassTable[ freezeFrameClassRef ];        /* [GUD]freezeFrameClassRef */

        /* Gets the temporary freeze frame record in corresponding to */
        /* the specific freeze frame record class index. */
        resultOfSet = Dem_UdmData_SetFFRecordIndexToSyncTmp();

        /* Checks the result of retrieve the temporary freeze frame record. */
        if( resultOfSet == DEM_IRT_OK )
        {
            Dem_UdmData_CaptureFreezeFrameDataToSyncTmp( monitorData0, freezeFrameClassPtr );
        }
    }


    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_SetFFRecordIndexToSyncTmp                    */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetFFRecordIndexToSyncTmp
( void )
{
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) emptyIndexOfFreezeFrameRecords;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberFreezeFrameUserDefinedPerDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetRecordStatus;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) recordStatus;

    retVal = DEM_IRT_NG;

    if( Dem_UdmTmpSyncEventMemoryEntry.EventRecord.UdmFaultIndex == DEM_UDMFAULTINDEX_INITIAL )
    {
        /* No Process */
    }
    else
    {
        if( Dem_UdmTmpSyncEventMemoryEntry.FaultRecord.RecordNumberIndex == DEM_UDMFFRECINDEX_INITIAL )
        {
            maxNumberFreezeFrameUserDefinedPerDTC = Dem_CfgInfoUdm_GetMaxNumberOfFreezeFramePerDTC( Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex );
            emptyIndexOfFreezeFrameRecords = Dem_UdmTmpSyncEventMemoryEntry.EventRecord.UdmFaultIndex * maxNumberFreezeFrameUserDefinedPerDTC;

            retVal = Dem_UdmData_SetNextFFRecordIndexToSyncTmp( emptyIndexOfFreezeFrameRecords );
        }
        else
        {
            /* After the second time, at the time of failure */
            recordStatus = DEM_FFD_NOT_STORED;
            retGetRecordStatus = Dem_UdmFFDMng_GetRecordStatus( Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex, Dem_UdmTmpSyncEventMemoryEntry.OldestFreezeFrameRecordIndex, &recordStatus );
            if( retGetRecordStatus == DEM_IRT_OK )
            {
                if( recordStatus != DEM_FFD_STORED )
                {
                    Dem_UdmTmpSyncEventMemoryEntry.EventMemoryRecord.NumberOfFreezeFrameRecords = Dem_UdmTmpSyncEventMemoryEntry.EventMemoryRecord.NumberOfFreezeFrameRecords + (Dem_u16_UdmFFDIndexType)1U;
                }
            }

            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_SetNextFFRecordIndexToSyncTmp                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EmptyIndexOfFreezeFrameRecords :                    */
/*               |         The empty index of freeeze frame records.        */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetNextFFRecordIndexToSyncTmp
(
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) EmptyIndexOfFreezeFrameRecords
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetNextFFInfo;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFFDRecordNum;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberFreezeFrameRecords;
    VAR( Dem_UdmNextFreezeFrameType, AUTOMATIC ) udmNextFreezeFrameInfo;

    retVal = DEM_IRT_NG;
    udmFFDRecordNum = Dem_UdmFFDMng_GetFFDRecordNum( Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex );

    if( EmptyIndexOfFreezeFrameRecords < udmFFDRecordNum )
    {
        maxNumberFreezeFrameRecords = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( Dem_UdmTmpSyncEventMemoryEntry.UdmEventIndex );

        udmNextFreezeFrameInfo.FreezeFrameRecordIndex = DEM_UDMFFRECINDEX_INITIAL;
        udmNextFreezeFrameInfo.OccurrenceOrder = DEM_UDMOCCURRENCEORDER_INITIAL;
        udmNextFreezeFrameInfo.CidUdmFreezeFrameRecords = DEM_CONSISTENCY_INITIAL;

        resultOfGetNextFFInfo = Dem_UdmFFDMng_GetNextFreezeFrameInfo( (boolean)TRUE, Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex, EmptyIndexOfFreezeFrameRecords, maxNumberFreezeFrameRecords, &udmNextFreezeFrameInfo );
        if( resultOfGetNextFFInfo == DEM_IRT_OK )
        {
            Dem_UdmTmpSyncEventMemoryEntry.FFRMngInfo.CidUdmFreezeFrameRecords = Dem_UtlCid_CalcConsistencyId( udmNextFreezeFrameInfo.CidUdmFreezeFrameRecords );

            Dem_UdmTmpSyncEventMemoryEntry.OldestFreezeFrameRecordIndex = EmptyIndexOfFreezeFrameRecords;
            Dem_UdmTmpSyncEventMemoryEntry.FFRMngInfo.OccurrenceOrder = udmNextFreezeFrameInfo.OccurrenceOrder;

            Dem_UdmTmpSyncEventMemoryEntry.FaultRecord.RecordNumberIndex = EmptyIndexOfFreezeFrameRecords;

            Dem_UdmTmpSyncEventMemoryEntry.EventMemoryRecord.NumberOfFreezeFrameRecords = Dem_UdmTmpSyncEventMemoryEntry.EventMemoryRecord.NumberOfFreezeFrameRecords + (Dem_u16_UdmFFDIndexType)1U;

            Dem_UdmTmpSyncEventMemoryEntry.StorageOfFFDAtFirstTimeFlag  = (boolean)TRUE;

            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_CaptureFreezeFrameDataToSyncTmp              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventIndex :                                        */
/*               |        The index for Dem_EventRecordList.                */
/*               | [in] monitorData0 :                                      */
/*               |         Monitor test result                              */
/*               | [in] FreezeFrameClassPtr :                               */
/*               |        The pointer of DemFreezeFrameClass.               */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmData_CaptureFreezeFrameDataToSyncTmp
(
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) ffDataPtr;

    /* Set the event Index of the event memory entry of temporary area to the event Index of the freeze frame record. */
    Dem_UdmTmpSyncEventMemoryEntry.FFRMngInfo.UdmEventIndex = Dem_UdmTmpSyncEventMemoryEntry.UdmEventIndex;

    /* Set "stored" to the record status of the freeze frame record. */
    Dem_UdmTmpSyncEventMemoryEntry.FFRMngInfo.RecordStatus = DEM_FFD_STORED;

    /* Delete RecordStatus and UdmFaultIndex in FFD to be written */
#ifndef JGXSTACK
    Dem_UdmExcFncTable[Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex].ExclusiveEnterFnc();   /* [GUDCHK:SETVAL]Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex */
#else   /* JGXSTACK */
    Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */

    Dem_UdmFFDMng_InitRecord( Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex, Dem_UdmTmpSyncEventMemoryEntry.OldestFreezeFrameRecordIndex );

#ifndef JGXSTACK
    Dem_UdmExcFncTable[Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex].ExclusiveExitFnc();    /* [GUDCHK:SETVAL]Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex */
#else   /* JGXSTACK */
    Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */

    /* Get start address of real data area of FFD */
    ffDataPtr = Dem_UdmFFDMng_GetFreezeFrameStartDataPtr( Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex, Dem_UdmTmpSyncEventMemoryEntry.OldestFreezeFrameRecordIndex );
    if( ffDataPtr != NULL_PTR )
    {
        eventCtrlIndex = Dem_CfgInfoUdm_CnvUdmEventIndexToEventCtrlIndex( Dem_UdmTmpSyncEventMemoryEntry.UdmEventIndex );

        /* Store capture data in the freeze frame record data */
#ifndef DEM_SIT_RANGE_CHECK
        Dem_Data_CaptureFreezeFrameClass( eventCtrlIndex, FreezeFrameClassPtr, ffDataPtr, monitorData0 );
#else   /* DEM_SIT_RANGE_CHECK */
        Dem_Data_CaptureFreezeFrameClass( DEM_SIT_R_CHK_UDM_FF_DATA_SIZE( Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex ), eventCtrlIndex, FreezeFrameClassPtr, ffDataPtr , monitorData0 );
#endif  /* DEM_SIT_RANGE_CHECK */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_UpdateEventMemoryEntryFromSyncTmp            */
/* Description   | Updates the event memory entry from temporary area.      */
/* Preconditions | None                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_UpdateEventMemoryEntryFromSyncTmp
( void )
{
    /* Compares the event memory entry corresponding to the event index of temporary area from temporary area. */
    Dem_UdmTmpSyncEventMemoryEntry.ResultOfComparingEventRecords = Dem_UdmEventMngC_CompareEventRecord( Dem_UdmTmpSyncEventMemoryEntry.UdmEventIndex, &Dem_UdmTmpSyncEventMemoryEntry.EventRecord );

    /* ResultOfComparingFaultRecords is already set when FaultRecord is newly acquired */

    /* Stores the event memory entry from the event memory entry of temporary area. */
    Dem_UdmData_StoreEventMemoryEntryFromSyncTmp();

    return ;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_InitTmpSyncMemoryWithoutRecord               */
/* Description   | Initialization of temporary event memory entries.        */
/*               | (excluding records)                                      */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*               |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmData_InitTmpSyncMemoryWithoutRecord
( void )
{
    /* Initializes the freeze frame record list for non-OBD. */

    /* Initializes the oldest freeze frame record ndex. */
    Dem_UdmTmpSyncEventMemoryEntry.OldestFreezeFrameRecordIndex = DEM_UDMFFRECINDEX_INITIAL;

    /* Initializes the number of event memory entries before being updated. */
    Dem_UdmTmpSyncEventMemoryEntry.BeforeNumberOfEventMemoryEntries = DEM_NUMOFEVTMEMENT_INITIAL;

    /* Initializes the result of comparing each records with no differences. */
    Dem_UdmTmpSyncEventMemoryEntry.ResultOfComparingEventRecords  = DEM_IRT_OK;
    Dem_UdmTmpSyncEventMemoryEntry.ResultOfComparingFaultRecords  = DEM_IRT_OK;

    /* Initializes the flag for storage of FFD at first time. */
    Dem_UdmTmpSyncEventMemoryEntry.StorageOfFFDAtFirstTimeFlag  = (boolean)FALSE;

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_StoreEventMemoryEntryFromSyncTmp             */
/* Description   | Store the event memory entry from temporary area corres- */
/*               | ponding to the event index of temporary area.            */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmData_StoreEventMemoryEntryFromSyncTmp
( void )
{
    /* When the storage of FFD at the first time, FFD other than the first time shall be cleared. */
    if( Dem_UdmTmpSyncEventMemoryEntry.StorageOfFFDAtFirstTimeFlag == (boolean)TRUE )
    {
        Dem_UdmFFDMng_ClearFFDOtherThanTheFirstTime( Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex, Dem_UdmTmpSyncEventMemoryEntry.UdmEventIndex, Dem_UdmTmpSyncEventMemoryEntry.OldestFreezeFrameRecordIndex );
    }

#ifndef JGXSTACK
    /* Starts exclusion. */
    Dem_UdmExcFncTable[Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex].ExclusiveEnterFnc();   /* [GUDCHK:SETVAL]Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex */
#else   /* JGXSTACK */
    Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */

    /* Updates the freeze frame record from temporary area's one. */
    Dem_UdmData_StoreFreezeFrameRecordFromSyncTmp();

    /* Updates the event record from temporary area's one. */
    if( Dem_UdmTmpSyncEventMemoryEntry.ResultOfComparingEventRecords == DEM_IRT_NG )
    {
        (void)Dem_UdmEventMngC_SetEventRecord( Dem_UdmTmpSyncEventMemoryEntry.UdmEventIndex,  &Dem_UdmTmpSyncEventMemoryEntry.EventRecord ); /* no return check required */
    }

    if( Dem_UdmTmpSyncEventMemoryEntry.ResultOfComparingFaultRecords == DEM_IRT_NG )
    {
        (void)Dem_UdmFaultMngC_SetFaultRecord( Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex, Dem_UdmTmpSyncEventMemoryEntry.EventRecord.UdmFaultIndex, &Dem_UdmTmpSyncEventMemoryEntry.FaultRecord );    /* no return check required *//* [GUDCHK:SETVAL]Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex */
    }

    Dem_UdmEventMngC_SetEventMemoryRecord( Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex, &Dem_UdmTmpSyncEventMemoryEntry.EventMemoryRecord );   /* [GUDCHK:SETVAL]Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex */

#ifndef JGXSTACK
    /* Finishes exclusion. */
    Dem_UdmExcFncTable[Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex].ExclusiveExitFnc();    /* [GUDCHK:SETVAL]Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex */
#else   /* JGXSTACK */
    Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_StoreFreezeFrameRecordFromSyncTmp            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  |                                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmData_StoreFreezeFrameRecordFromSyncTmp
( void )
{
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) recordNumberIndex;

    recordNumberIndex = Dem_UdmTmpSyncEventMemoryEntry.OldestFreezeFrameRecordIndex;

    if( recordNumberIndex != DEM_UDMFFRECINDEX_INITIAL )
    {
        /* Since the actual data has already been written directly, write only the management data */
        Dem_UdmFFDMng_SetMngInfo( Dem_UdmTmpSyncEventMemoryEntry.UdmGroupKindIndex, recordNumberIndex, &Dem_UdmTmpSyncEventMemoryEntry.FFRMngInfo );
    }


    return ;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

