/* Dem_UdmDataCtl_EventEntry02Make_Fault_c(v5-9-0)                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_EventEntry02Make_Fault/CODE                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"


#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Udm_Data.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"
#include "Dem_UdmDataCtl_EventEntry_local.h"
#include "Dem_UdmDataCtl_EvtDisplacement_local.h"
#include "Dem_UdmDataCtl_EventEntry_TSFFD_local.h"

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetNewFaultOccurrenceToTmp
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )      FaultRecordOverwriteFlagPtr,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) UdmEventIndexOverwrittenPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) OldDTCStatusAtOverwrittenPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusAtOverwrittenPtr,
    P2VAR( Dem_u16_TSFFListIndexType, AUTOMATIC, AUTOMATIC ) TSFFListIndexOverwrittenPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u08_UdmFaultIndexType, DEM_VAR_NO_INIT ) Dem_UdmData_SearchFRIndex[ DEM_USER_DEFINED_MEMORY_NUM ];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DataMng_InitSearchFRIndex                            */
/* Description   | Set SearchFaultRecordIndex                               */
/*               |  format.                                                 */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_InitSearchFRIndex
( void )
{
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    for( udmGroupKindIndex = (Dem_u16_UdmDemMemKindIndexType)0U; udmGroupKindIndex < userDefinedMemoryNum; udmGroupKindIndex++ )    /* [GUD:for]udmGroupKindIndex */
    {
        Dem_UdmData_SearchFRIndex[ udmGroupKindIndex ] = (Dem_u08_UdmFaultIndexType)0U;         /* [GUD]udmGroupKindIndex */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_GetSearchFRIndex                             */
/* Description   | Get SearchFaultRecordIndex                               */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/* Return Value  | Dem_u08_UdmFaultIndexType                                */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_UdmFaultIndexType, DEM_CODE ) Dem_UdmData_GetSearchFRIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex      /* [PRMCHK:CALLER] */
)
{
    return Dem_UdmData_SearchFRIndex[ UdmGroupKindIndex ];      /* [GUDCHK:CALLER]UdmGroupKindIndex */
}

/****************************************************************************/
/* Function Name | Dem_UdmData_SetSearchFRIndex                             */
/* Description   | Set SearchFaultRecordIndex                               */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/*               | [in] UdmSearchFaultIndex :                               */
/*               |        The udm fault index corresponding to the specific */
/*               |         udm fault record.                                */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_SetSearchFRIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,     /* [PRMCHK:CALLER] */
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmSearchFaultIndex
)
{
    Dem_UdmData_SearchFRIndex[ UdmGroupKindIndex ] = UdmSearchFaultIndex;   /* [GUDCHK:CALLER]UdmGroupKindIndex */

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_ReplaceSearchFRIndex                         */
/* Description   | Set SearchFaultRecordIndex                               */
/*               |  format.                                                 */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The index for Dem_UserDefinedMemoryTable[].       */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_ReplaceSearchFRIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex      /* [PRMCHK:CALLER] */
)
{
    Dem_UdmData_SearchFRIndex[ UdmGroupKindIndex ] = Dem_UdmFaultMngC_GetEmptyFaultIndex( UdmGroupKindIndex, (Dem_u08_UdmFaultIndexType)0U );   /* [GUDCHK:CALLER]UdmGroupKindIndex */

    Dem_UdmEventMngC_ResetLastOfFaultOccurrenceOrder( UdmGroupKindIndex );

    return;
}



/****************************************************************************/
/* Function Name | Dem_UdmData_SetFaultInfo                                 */
/* Description   | Sets the fault record related information of the event - */
/*               | memory entry of the temporary domain.                    */
/* Preconditions | none                                                     */
/* Parameters    | [out] FaultOccurrenceFlagPtr :                           */
/*               |        When temporary memory was changed, TRUE is set.   */
/*               | [out]  FaultRecordOverwriteFlagPtr                       */
/*               |              FALSE : overwrite isn't occurred.           */
/*               |              TRUE  : overwrite occurred.                 */
/*               | [out]  UdmEventIndexOverwrittenPtr                       */
/*               |              overwritten event.                          */
/*               | [out]  OldDTCStatusAtOverwrittenPtr                      */
/*               |              statusOfDTC of overwritten event.           */
/*               | [out]  NewDTCStatusAtOverwrittenPtr                      */
/*               |              statusOfDTC of overwritten event.           */
/*               | [out]  TSFFListIndexOverwrittenPtr                       */
/*               |              TimeSeriesFreezeFrameListIndex of overwrit- */
/*               |              ten event.                                  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Fault record related information se- */
/*               |        tting succeeds or has been already set.           */
/*               |        DEM_IRT_NG : Event memory overflows and occurs.   */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetFaultInfo
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )      FaultOccurrenceFlagPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )      FaultRecordOverwriteFlagPtr,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) UdmEventIndexOverwrittenPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) OldDTCStatusAtOverwrittenPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusAtOverwrittenPtr,
    P2VAR( Dem_u16_TSFFListIndexType, AUTOMATIC, AUTOMATIC ) TSFFListIndexOverwrittenPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                     retSetFaultInfo;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                     retVal;

    retVal                      = DEM_IRT_NG;
    *FaultOccurrenceFlagPtr     = (boolean)FALSE;
    *TSFFListIndexOverwrittenPtr = DEM_TSFFLISTINDEX_INVALID;

    /* Checks whether the fault index is valid. */
    if( Dem_UdmTmpEventMemoryEntry.EventRecord.UdmFaultIndex == DEM_UDMFAULTINDEX_INITIAL )
    {
        /* Information related to the occurrence of a new failure is set in the event memory entry of the temporary area. */
        retSetFaultInfo = Dem_UdmData_SetNewFaultOccurrenceToTmp( FaultRecordOverwriteFlagPtr, UdmEventIndexOverwrittenPtr, OldDTCStatusAtOverwrittenPtr, NewDTCStatusAtOverwrittenPtr, TSFFListIndexOverwrittenPtr );
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
        retVal = DEM_IRT_OK;
        *FaultOccurrenceFlagPtr         = (boolean)TRUE;
        *FaultRecordOverwriteFlagPtr    = (boolean)FALSE;
    }

    /* Returns with the result. */
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_SetNewFaultOccurrenceToTmp                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [out]  FaultRecordOverwriteFlagPtr                       */
/*               |              FALSE : overwrite isn't occurred.           */
/*               |              TRUE  : overwrite occurred.                 */
/*               | [out]  UdmEventIndexOverwrittenPtr                       */
/*               |              overwritten event.                          */
/*               | [out]  OldDTCStatusAtOverwrittenPtr                      */
/*               |              statusOfDTC of overwritten event.           */
/*               | [out]  NewDTCStatusAtOverwrittenPtr                      */
/*               |              statusOfDTC of overwritten event.           */
/*               | [out]  TSFFListIndexOverwrittenPtr                       */
/*               |              TimeSeriesFreezeFrameListIndex of overwrit- */
/*               |              ten event.                                  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SetNewFaultOccurrenceToTmp
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )      FaultRecordOverwriteFlagPtr,
    P2VAR( Dem_u16_UdmEventIndexType, AUTOMATIC, AUTOMATIC ) UdmEventIndexOverwrittenPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) OldDTCStatusAtOverwrittenPtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) NewDTCStatusAtOverwrittenPtr,
    P2VAR( Dem_u16_TSFFListIndexType, AUTOMATIC, AUTOMATIC ) TSFFListIndexOverwrittenPtr
)
{
    VAR( Dem_UdmFaultRecordType, AUTOMATIC ) udmFaultRecordOverwritten;
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )  /* [FuncSw] */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retJudgeOverwriteTSFFRecord;
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultIndex;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) numberEventEntryUserDefined;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) failRecordNum;

    retVal = DEM_IRT_NG;

    udmGroupKindIndex = Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex;       /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */

    /*  overwrite occur flag.       */
    *FaultRecordOverwriteFlagPtr    =   (boolean)FALSE;

    *TSFFListIndexOverwrittenPtr = DEM_TSFFLISTINDEX_INVALID;

    /* MAX RecordNum for each Selection ID */
    numberEventEntryUserDefined = Dem_CfgInfoUdm_GetMaxNumberOfEventEntry( udmGroupKindIndex );                                     /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */

    if( Dem_UdmTmpEventMemoryEntry.EventMemoryRecord.NumberOfEventMemoryEntries < numberEventEntryUserDefined )
    {
        udmFaultIndex = Dem_UdmFaultMngC_GetEmptyFaultIndex( udmGroupKindIndex, Dem_UdmData_SearchFRIndex[ udmGroupKindIndex ] );   /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */
        failRecordNum = Dem_UdmFaultMngC_GetFaultRecordNum( udmGroupKindIndex );                                                    /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */

        if( udmFaultIndex >= failRecordNum )
        {
            Dem_UdmData_SearchFRIndex[udmGroupKindIndex] = failRecordNum;                                                           /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */
        }
        else
        {
            /* Set FaultIndex, EventIndex, and NumberEntries to TmpEventMemoryEntry. */
            Dem_UdmTmpEventMemoryEntry.EventRecord.UdmFaultIndex = udmFaultIndex;
            Dem_UdmTmpEventMemoryEntry.FaultRecord.UdmEventIndex = Dem_UdmTmpEventMemoryEntry.UdmEventIndex;
            Dem_UdmTmpEventMemoryEntry.FaultRecord.UdmFaultOccurrenceOrder = Dem_UdmTmpEventMemoryEntry.EventMemoryRecord.LastOfFaultOccurrenceOrder;
            Dem_UdmTmpEventMemoryEntry.EventMemoryRecord.NumberOfEventMemoryEntries = Dem_UdmTmpEventMemoryEntry.EventMemoryRecord.NumberOfEventMemoryEntries + (Dem_u08_OrderIndexType)1U;
            Dem_UdmTmpEventMemoryEntry.EventMemoryRecord.LastOfFaultOccurrenceOrder = Dem_UdmTmpEventMemoryEntry.EventMemoryRecord.LastOfFaultOccurrenceOrder + (Dem_u16_OccrOrderType)1U;
            retVal = DEM_IRT_OK;

            Dem_UdmData_SearchFRIndex[udmGroupKindIndex] = udmFaultIndex + (Dem_u08_UdmFaultIndexType)1U;                           /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */
        }
    }
    else
    {
        /* get udm info table index */
        udmInfoTableIndex = Dem_CfgInfoUdm_GetDemUserDefinedMemoryInfoTableIndex( udmGroupKindIndex );                              /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */

        /*  overwrite judge                 */
        retVal  =   Dem_UdmData_SetEventDisplacement( udmInfoTableIndex, Dem_UdmTmpEventMemoryEntry.UdmEventIndex, UdmEventIndexOverwrittenPtr, OldDTCStatusAtOverwrittenPtr, NewDTCStatusAtOverwrittenPtr );   /* [GUD:RET:DEM_IRT_OK]UdmEventIndexOverwrittenPtr, OldDTCStatusAtOverwrittenPtr, NewDTCStatusAtOverwrittenPtr */
        if ( retVal == DEM_IRT_OK )
        {
            udmFaultIndex = DEM_UDMFAULTINDEX_INITIAL;
            (void)Dem_UdmEventMngC_GetER_FaultIndex( *UdmEventIndexOverwrittenPtr, &udmFaultIndex );    /* no return check required */

            Dem_UdmTmpEventMemoryEntry.EventRecord.UdmFaultIndex = udmFaultIndex;
            Dem_UdmTmpEventMemoryEntry.FaultRecord.UdmEventIndex = Dem_UdmTmpEventMemoryEntry.UdmEventIndex;
            Dem_UdmTmpEventMemoryEntry.FaultRecord.UdmFaultOccurrenceOrder = Dem_UdmTmpEventMemoryEntry.EventMemoryRecord.LastOfFaultOccurrenceOrder;
            Dem_UdmTmpEventMemoryEntry.EventMemoryRecord.LastOfFaultOccurrenceOrder = Dem_UdmTmpEventMemoryEntry.EventMemoryRecord.LastOfFaultOccurrenceOrder + (Dem_u16_OccrOrderType)1U;

            (void)Dem_UdmFaultMngC_GetRecord( udmGroupKindIndex, udmFaultIndex, &udmFaultRecordOverwritten );  /* no return check required */   /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */

#ifndef JGXSTACK
            /* Starts exclusion. */
            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveEnterFnc();          /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */
#else   /* JGXSTACK */
            Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */

            Dem_UdmData_ClearFreezeFrameRecord( udmGroupKindIndex, *UdmEventIndexOverwrittenPtr, &udmFaultRecordOverwritten, &(Dem_UdmTmpEventMemoryEntry.EventMemoryRecord) ); /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )  /* [FuncSw] */
            /* Clears the time series freeze frame records indexed by time series freeze frame list index in the retrieved fault record. */
            Dem_UdmData_ClearTimeSeriesFreezeFrameRecords( udmGroupKindIndex, *UdmEventIndexOverwrittenPtr, &udmFaultRecordOverwritten );   /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

#ifndef JGXSTACK
            /* Finishes exclusion. */
            Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveExitFnc();           /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */
#else   /* JGXSTACK */
            Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )  /* [FuncSw] */
            Dem_UdmData_ClearOverwriteTSFFList( udmFaultRecordOverwritten.TimeSeriesFreezeFrameListIndex, *UdmEventIndexOverwrittenPtr );

            retJudgeOverwriteTSFFRecord = Dem_UdmData_JudgeOverwriteTSFFRecord( udmFaultRecordOverwritten.TimeSeriesFreezeFrameListIndex, *UdmEventIndexOverwrittenPtr, Dem_UdmTmpEventMemoryEntry.UdmEventIndex );
            if( retJudgeOverwriteTSFFRecord == DEM_IRT_OK )
            {
                *TSFFListIndexOverwrittenPtr = udmFaultRecordOverwritten.TimeSeriesFreezeFrameListIndex;
            }

#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

            /*  overwrite occurred.         */
            *FaultRecordOverwriteFlagPtr    =   (boolean)TRUE;
        }
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
