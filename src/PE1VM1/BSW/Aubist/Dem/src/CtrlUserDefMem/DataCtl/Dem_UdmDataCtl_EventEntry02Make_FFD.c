/* Dem_UdmDataCtl_EventEntry02Make_FFD_c(v5-9-0)                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_EventEntry02Make_FFD/CODE                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_DataCtl_CaptureFreezeFrameClass.h"
#include "../../../inc/Dem_Utl.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_Udm_Data.h"
#include "Dem_UdmDataCtl_EventEntry_local.h"

#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
#include <Dem_SIT_RangeCheck.h>
#endif  /* DEM_SIT_RANGE_CHECK */

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

static FUNC( void, DEM_CODE ) Dem_UdmData_CaptureNonObdFreezeFrameToTmp
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetFFRecordIndexToTmp
( void );

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetNextFFRecordIndexToTmp
(
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) EmptyIndexOfFreezeFrameRecords
);

static FUNC( void, DEM_CODE ) Dem_UdmData_CaptureFreezeFrameDataToTmp
(
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr
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
/* Function Name | Dem_UdmData_CaptureFreezeFrame                           */
/* Description   | Captures a freeze frame corresponding to specified even- */
/*               | t index and calls callback function "ReadDataElement".   */
/* Preconditions | The specified event index corresponding to the event ID  */
/*               |  has been already retrieved.                             */
/* Parameters    | [in] EventIndex :                                        */
/*               |        The event index corresponding to the event ID.    */
/*               | [in] monitorData0 :                                      */
/*               |        Monitor test result                               */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_CaptureFreezeFrame
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0
)
{
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) eventConfigureNum;

    eventConfigureNum = Dem_UdmEventConfigureNum;

    /* Checks the specified event ID be within the range. */
    if( UdmEventIndex < eventConfigureNum )     /* [GUD:if]UdmEventIndex */
    {
        /* Within the range. */

        /* Captures freeze frame to the event memory entry of temporary area. */
        Dem_UdmData_CaptureNonObdFreezeFrameToTmp( UdmEventIndex, monitorData0 );   /* [GUD]UdmEventIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_CaptureNonObdFreezeFrameToTmp                */
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
static FUNC( void, DEM_CODE ) Dem_UdmData_CaptureNonObdFreezeFrameToTmp
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

    if( freezeFrameClassRef != DEM_FFCLASSINDEX_INVALID )                           /* [GUD:if]freezeFrameClassRef */
    {
        /* Holds the FreezeFrameClass table pointed to */
        /* by the FreezeFrameClass table list Index of the held DTCAttribute table. */
        freezeFrameClassPtr = &Dem_FreezeFrameClassTable[ freezeFrameClassRef ];    /* [GUD]freezeFrameClassRef */

        resultOfSet = Dem_UdmData_SetFFRecordIndexToTmp();

        /* Checks the result of set the temporary freeze frame record. */
        if( resultOfSet == DEM_IRT_OK )
        {
            Dem_UdmData_SetResultOfCmpFFRecordToTmp( DEM_IRT_NG );

            Dem_UdmData_CaptureFreezeFrameDataToTmp( monitorData0, freezeFrameClassPtr );
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_SetFFRecordIndexToTmp                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetFFRecordIndexToTmp
( void )
{
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) emptyIndexOfFreezeFrameRecords;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberFreezeFrameUserDefinedPerDTC;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetRecordStatus;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) recordStatus;


    retVal = DEM_IRT_NG;

    if( Dem_UdmTmpEventMemoryEntry.EventRecord.UdmFaultIndex == DEM_UDMFAULTINDEX_INITIAL )
    {
        /* No Process */
    }
    else
    {
        if( Dem_UdmTmpEventMemoryEntry.FaultRecord.RecordNumberIndex == DEM_UDMFFRECINDEX_INITIAL )
        {
            maxNumberFreezeFrameUserDefinedPerDTC = Dem_CfgInfoUdm_GetMaxNumberOfFreezeFramePerDTC( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex );
            emptyIndexOfFreezeFrameRecords = Dem_UdmTmpEventMemoryEntry.EventRecord.UdmFaultIndex * maxNumberFreezeFrameUserDefinedPerDTC;

            retVal = Dem_UdmData_SetNextFFRecordIndexToTmp( emptyIndexOfFreezeFrameRecords );
        }
        else
        {
            /* After the second time, at the time of failure */
            recordStatus = DEM_FFD_NOT_STORED;
            retGetRecordStatus = Dem_UdmFFDMng_GetRecordStatus( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex, Dem_UdmTmpEventMemoryEntry.OldestFreezeFrameRecordIndex, &recordStatus );
            if( retGetRecordStatus == DEM_IRT_OK )
            {
                if( recordStatus != DEM_FFD_STORED )
                {
                    Dem_UdmTmpEventMemoryEntry.EventMemoryRecord.NumberOfFreezeFrameRecords = Dem_UdmTmpEventMemoryEntry.EventMemoryRecord.NumberOfFreezeFrameRecords + (Dem_u16_UdmFFDIndexType)1U;
                }
            }

            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_SetNextFFRecordIndexToTmp                    */
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
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetNextFFRecordIndexToTmp
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
    udmFFDRecordNum = Dem_UdmFFDMng_GetFFDRecordNum( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex );

    if( EmptyIndexOfFreezeFrameRecords < udmFFDRecordNum )
    {
        maxNumberFreezeFrameRecords = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( Dem_UdmTmpEventMemoryEntry.UdmEventIndex );

        udmNextFreezeFrameInfo.FreezeFrameRecordIndex = DEM_UDMFFRECINDEX_INITIAL;
        udmNextFreezeFrameInfo.OccurrenceOrder = DEM_UDMOCCURRENCEORDER_INITIAL;
        udmNextFreezeFrameInfo.CidUdmFreezeFrameRecords = DEM_CONSISTENCY_INITIAL;

        resultOfGetNextFFInfo = Dem_UdmFFDMng_GetNextFreezeFrameInfo( (boolean)TRUE, Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex, EmptyIndexOfFreezeFrameRecords, maxNumberFreezeFrameRecords, &udmNextFreezeFrameInfo );  /* [GUD:RET:DEM_IRT_OK]udmNextFreezeFrameInfo */
        if( resultOfGetNextFFInfo == DEM_IRT_OK )
        {
            Dem_UdmTmpEventMemoryEntry.FreezeFrameRecord.CidUdmFreezeFrameRecords = Dem_UtlCid_CalcConsistencyId( udmNextFreezeFrameInfo.CidUdmFreezeFrameRecords );

            Dem_UdmTmpEventMemoryEntry.OldestFreezeFrameRecordIndex = EmptyIndexOfFreezeFrameRecords;
            Dem_UdmTmpEventMemoryEntry.FreezeFrameRecord.OccurrenceOrder = udmNextFreezeFrameInfo.OccurrenceOrder;

            Dem_UdmTmpEventMemoryEntry.FaultRecord.RecordNumberIndex = EmptyIndexOfFreezeFrameRecords;

            Dem_UdmTmpEventMemoryEntry.EventMemoryRecord.NumberOfFreezeFrameRecords = Dem_UdmTmpEventMemoryEntry.EventMemoryRecord.NumberOfFreezeFrameRecords + (Dem_u16_UdmFFDIndexType)1U;

            Dem_UdmTmpEventMemoryEntry.StorageOfFFDAtFirstTimeFlag  = (boolean)TRUE;

            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_CaptureFreezeFrameDataToTmp                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] monitorData0 :                                      */
/*               |         Monitor test result                              */
/*               | [in] FreezeFrameClassPtr :                               */
/*               |        The pointer of DemFreezeFrameClass.               */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmData_CaptureFreezeFrameDataToTmp
(
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr
)
{
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;

    /* Set the event Index of the event memory entry of temporary area to the event Index of the freeze frame record. */
    Dem_UdmTmpEventMemoryEntry.FreezeFrameRecord.UdmEventIndex = Dem_UdmTmpEventMemoryEntry.UdmEventIndex;

    /* Set "stored" to the record status of the freeze frame record. */
    Dem_UdmTmpEventMemoryEntry.FreezeFrameRecord.RecordStatus = DEM_FFD_STORED;

    eventCtrlIndex = Dem_CfgInfoUdm_CnvUdmEventIndexToEventCtrlIndex( Dem_UdmTmpEventMemoryEntry.UdmEventIndex );

    /* Store capture data in the freeze frame record data */
#ifndef DEM_SIT_RANGE_CHECK
    Dem_Data_CaptureFreezeFrameClass( eventCtrlIndex, FreezeFrameClassPtr, Dem_UdmTmpEventMemoryEntry.FreezeFrameRecord.Data , monitorData0 );
#else   /* DEM_SIT_RANGE_CHECK */
    Dem_Data_CaptureFreezeFrameClass( Dem_UdmFFDMaxLength, eventCtrlIndex, FreezeFrameClassPtr, Dem_UdmTmpEventMemoryEntry.FreezeFrameRecord.Data , monitorData0 );
#endif  /* DEM_SIT_RANGE_CHECK */

    return;
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
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
