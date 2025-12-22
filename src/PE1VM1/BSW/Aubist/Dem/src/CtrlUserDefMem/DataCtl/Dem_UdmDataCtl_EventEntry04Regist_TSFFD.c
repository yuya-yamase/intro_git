/* Dem_UdmDataCtl_EventEntry04Regist_TSFFD_c(v5-7-0)                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_EventEntry04Regist_TSFFD/CODE              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataCtl_SamplingFFD.h"
#include "../../../inc/Dem_CmnLib_DataCtl_SamplingFFDAccess.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_Rc_UdmMng_rc.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"
#include "../../../inc/Dem_Utl.h"
#include "Dem_UdmDataCtl_local.h"
#include "Dem_UdmDataCtl_TSFFD_local.h"
#include "Dem_UdmDataCtl_EventEntry_local.h"
#include "Dem_UdmDataCtl_EventEntry_TSFFD_local.h"

#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
#include <Dem_SIT_RangeCheck.h>
#endif  /* DEM_SIT_RANGE_CHECK */

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_CaptureTSFFFromSample
(
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) SamplingFreezeFrameRef,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumberOfBeforeTriggeredRecord,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameTableRef,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) TriggerFFDConsistencyId
);

static FUNC( void, DEM_CODE ) Dem_UdmData_ClearTSFFListRecordOtherThanTheFirstTime
(
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameClassRef,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) StartTSFFListIndex
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
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_UdmData_JudgeOverwriteTSFFRecord                     */
/* Description   | Judge if TSFFD can overwrite                             */
/* Preconditions |                                                          */
/* Parameters    | [in]  TSFFListIndexOverwritten : overwritten TSFFListIn- */
/*               | dex.                                                     */
/*               | [in]  UdmEventIndexOverwritten : overwritten event.      */
/*               | [in]  UdmEventIndexOverwrite : overwrite event.          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Can be overwritten.                  */
/*               |        DEM_IRT_NG : Cannot be overwritten.               */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_JudgeOverwriteTSFFRecord
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndexOverwritten,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndexOverwritten,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndexOverwrite
)
{
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRefOverwritten;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRefOverwrite;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;

    if( TSFFListIndexOverwritten < tsffTotalDTCNum )
    {
        tsFFRecClassRefOverwritten = Dem_CfgInfoUdm_GetTimeSeriesFreezeFrameRecordClassRef( UdmEventIndexOverwritten );
        if( tsFFRecClassRefOverwritten != DEM_TSFF_RECORD_CLASS_REF_INVALID )
        {
            tsFFRecClassRefOverwrite = Dem_CfgInfoUdm_GetTimeSeriesFreezeFrameRecordClassRef( UdmEventIndexOverwrite );
            if( tsFFRecClassRefOverwrite != DEM_TSFF_RECORD_CLASS_REF_INVALID )
            {
                if( tsFFRecClassRefOverwritten == tsFFRecClassRefOverwrite )
                {
                    retVal = DEM_IRT_OK;
                }
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_ClearOverwriteTSFFList                       */
/* Description   | Clear overwrite Dem_TimeSeriesFreezeFrameListRecordList- */
/*               | [] and update Dem_VacantTimeSeriesFreezeFrameListRecord- */
/*               | RefList[]                                                */
/* Preconditions |                                                          */
/* Parameters    | [in]  TSFFListIndexOverwritten : overwritten TSFFListIn- */
/*               | dex.                                                     */
/*               | [in]  UdmEventIndexOverwritten : overwritten event.      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_ClearOverwriteTSFFList
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndexOverwritten,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndexOverwritten        /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRefOverwritten;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsffRecordClassConfigureNum;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecEndIndex;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfTSFFPerDTC;

    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;

    if( TSFFListIndexOverwritten < tsffTotalDTCNum )                            /* [GUD:if]TSFFListIndexOverwritten */
    {
        tsffRecordClassConfigureNum = Dem_TSFFRecordClassConfigureNum;
        tsFFRecClassRefOverwritten = Dem_CfgInfoUdm_GetTimeSeriesFreezeFrameRecordClassRef( UdmEventIndexOverwritten ); /* [GUDCHK:CALLER]UdmEventIndexOverwritten *//* [GUD:RET:Not DEM_TSFF_RECORD_CLASS_REF_INVALID ] tsFFRecClassRefOverwritten */
        if( tsFFRecClassRefOverwritten < tsffRecordClassConfigureNum )          /* [GUD:if]tsFFRecClassRefOverwritten */
        {
            tsFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRefOverwritten].DemTimeSeriesFreezeFrameClassRef;   /* [GUD]tsFFRecClassRefOverwritten *//* [GUD:CFG:IF_GUARDED:tsFFRecClassRefOverwritten]tsFFClassRef */
            numberOfTSFFPerDTC = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfTimeSeriesFreezeFramePerDTC;           /* [GUD]tsFFClassRef */

            tsFFListRecEndIndex = ( TSFFListIndexOverwritten + (Dem_u16_TSFFListIndexType)numberOfTSFFPerDTC ) - (Dem_u16_TSFFListIndexType)1U;
            if( tsFFListRecEndIndex < tsffTotalDTCNum )
            {
                for( tsFFListRecIndex = TSFFListIndexOverwritten; tsFFListRecIndex <= tsFFListRecEndIndex; tsFFListRecIndex++)  /* [GUD:for]tsFFListRecIndex */
                {
                    Dem_Data_InitTSFFListRecord( &Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecIndex] );                  /* [GUD]tsFFListRecIndex */
                }
            }
            (void)Dem_Data_UpdateVacantTSFFListRecordRef( tsFFRecClassRefOverwritten );     /* no return check required */  /* [GUD]tsFFRecClassRefOverwritten */
            Dem_UdmData_InitCurrentIndexOfTSFFListRecord( tsFFRecClassRefOverwritten, TSFFListIndexOverwritten );           /* [GUD]tsFFRecClassRefOverwritten */
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_PrepareStoreTSFFRecordFromSample             */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in]  TSFFListIndexOverwritten                           */
/*               |              TimeSeriesFreezeFrameListIndex of overwrit- */
/*               |              ten event.                                  */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_PrepareStoreTSFFRecordFromSample
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndexOverwritten
)
{
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) offsetOfTSFFListIndex;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) startTSFFListRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) currentUdmFreezeFrameRecordIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) startUdmFreezeFrameRecordIndex;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) faultRecordNum;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    udmGroupKindIndex = Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex;

    if( udmGroupKindIndex < userDefinedMemoryNum )  /* [GUD:if]udmGroupKindIndex */
    {
        faultRecordNum = Dem_UdmFaultMngC_GetFaultRecordNum( udmGroupKindIndex );     /* [GUD]udmGroupKindIndex */

        /* If number of fault occurrence has been got over the maximum number of event memory entries, no need to carry out the following process. */
        if( Dem_UdmTmpEventMemoryEntry.EventRecord.UdmFaultIndex < faultRecordNum )                 /* [GUD:if]Dem_UdmTmpEventMemoryEntry.EventRecord.UdmFaultIndex */
        {
            tsFFRecClassRef = Dem_CfgInfoUdm_GetTimeSeriesFreezeFrameRecordClassRef( Dem_UdmTmpEventMemoryEntry.UdmEventIndex );    /* [GUD:RET:Not DEM_TSFF_RECORD_CLASS_REF_INVALID ] tsFFRecClassRef */

            if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )
            {
                /* if just captured trigger FFD. */
                if( Dem_UdmTmpEventMemoryEntry.ResultOfComparingFFRecords == DEM_IRT_NG )
                {
                    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;

                    if( TSFFListIndexOverwritten == DEM_TSFFLISTINDEX_INVALID )
                    {
                        startTSFFListRecIndex = Dem_UdmTmpEventMemoryEntry.FaultRecord.TimeSeriesFreezeFrameListIndex;
                        if( startTSFFListRecIndex >= tsffTotalDTCNum )
                        {
                            /* No time-series freeze frame recorded yet. */
                            startTSFFListRecIndex = Dem_TimeSeriesFreezeFrameCtrlRecordList[tsFFRecClassRef].VacantTimeSeriesFreezeFrameListRecordRef;  /* [GUD]tsFFRecClassRef */
                        }
                    }
                    else
                    {
                        startTSFFListRecIndex = TSFFListIndexOverwritten;
                    }

                    tsFFListRecIndex = Dem_UdmData_UpdateCurrentIndexOfTSFFListRecord( tsFFRecClassRef, startTSFFListRecIndex );                        /* [GUD]tsFFRecClassRef */
                    if( tsFFListRecIndex != DEM_TSFFLISTINDEX_INVALID )
                    {
                        /* Saves the current index for time-series freeze frame list record list. */
                        Dem_UdmTmpEventMemoryEntry.TSFFListCurrenctIndex = tsFFListRecIndex;

                        /* Dealing with the writing of TSFFD outside the exclusive section */
                        /* Temporarily clear the area of TSFFD to be registered */
                        Dem_UdmData_ClearTSFFRecord( udmGroupKindIndex, tsFFListRecIndex );

                        currentUdmFreezeFrameRecordIndex = Dem_UdmTmpEventMemoryEntry.OldestFreezeFrameRecordIndex;
                        startUdmFreezeFrameRecordIndex = Dem_UdmTmpEventMemoryEntry.FaultRecord.RecordNumberIndex;

                        if ( startUdmFreezeFrameRecordIndex != DEM_UDMFFRECINDEX_INITIAL )
                        {
                            offsetOfTSFFListIndex = (Dem_u08_NumOfTSFFType)( tsFFListRecIndex - startTSFFListRecIndex );

                            Dem_UdmFFDMng_ClearAndSetOffsetOfTSFFListIndex( udmGroupKindIndex, Dem_UdmTmpEventMemoryEntry.UdmEventIndex, currentUdmFreezeFrameRecordIndex, startUdmFreezeFrameRecordIndex, offsetOfTSFFListIndex );

                            Dem_UdmTmpEventMemoryEntry.FreezeFrameRecord.OffsetOfTSFFListIndex = offsetOfTSFFListIndex;
                        }
                    }
                }
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_StoreTSFFRecordFromSample                    */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in]  TSFFListIndexOverwritten                           */
/*               |              TimeSeriesFreezeFrameListIndex of overwrit- */
/*               |              ten event.                                  */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_StoreTSFFRecordFromSample
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndexOverwritten        /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfCaptureTSFF;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfUpdataVacantTSFFListRecRef;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfBeforeTriggeredRecord;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) faultRecordNum;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) triggerFFDConsistencyId;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) samplingFFRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;

    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;
    faultRecordNum = Dem_UdmFaultMngC_GetFaultRecordNum( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex );

    /* If number of fault occurrence has been got over the maximum number of event memory entries, no need to carry out the following process. */
    if( Dem_UdmTmpEventMemoryEntry.EventRecord.UdmFaultIndex < faultRecordNum )
    {
        tsFFRecClassRef = Dem_CfgInfoUdm_GetTimeSeriesFreezeFrameRecordClassRef( Dem_UdmTmpEventMemoryEntry.UdmEventIndex );    /* [GUD:RET:Not DEM_TSFF_RECORD_CLASS_REF_INVALID ] tsFFRecClassRef */

        if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )
        {
            /* if just captured trigger FFD. */
            if( Dem_UdmTmpEventMemoryEntry.ResultOfComparingFFRecords == DEM_IRT_NG )
            {
                resultOfUpdataVacantTSFFListRecRef = DEM_IRT_NG;

                samplingFFRef = Dem_SamplingFreezeFrameBindTable[tsFFRecClassRef].DemSamplingFreezeFrameRef;                    /* [GUD]tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED tsFFRecClassRef]samplingFFRef  */

                tsFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameClassRef;                      /* [GUD]tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED tsFFRecClassRef]tsFFClassRef  */

                numberOfBeforeTriggeredRecord = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfBeforeTriggeredRecord;              /* [GUD]tsFFClassRef */

                if( TSFFListIndexOverwritten == DEM_TSFFLISTINDEX_INVALID )
                {
                    tsFFListRecIndex = Dem_UdmTmpEventMemoryEntry.TSFFListCurrenctIndex;            /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.TSFFListCurrenctIndex */
                }
                else
                {
                    /* overwrite of TSFFD */
                    tsFFListRecIndex = TSFFListIndexOverwritten;                                    /* [GUDCHK:CALLER]TSFFListIndexOverwritten */
                }

                triggerFFDConsistencyId = Dem_UdmFFDMng_GetFFDConsystencyId( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex, Dem_UdmTmpEventMemoryEntry.OldestFreezeFrameRecordIndex );

                resultOfCaptureTSFF = Dem_UdmData_CaptureTSFFFromSample( samplingFFRef, numberOfBeforeTriggeredRecord, tsFFListRecIndex, triggerFFDConsistencyId ); /* [GUD:RET:DEM_IRT_OK] tsFFListRecIndex */

                if( resultOfCaptureTSFF == DEM_IRT_OK )
                {
                    Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecIndex].FaultIndex = Dem_UdmTmpEventMemoryEntry.EventRecord.UdmFaultIndex;    /* [GUD]tsFFListRecIndex */

                    Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecIndex].NumberOfStoredAfterTriggeredRecord = (uint8)0U;                       /* [GUD]tsFFListRecIndex */

                    resultOfUpdataVacantTSFFListRecRef = Dem_Data_UpdateVacantTSFFListRecordRef( tsFFRecClassRef );
                }

                if( resultOfUpdataVacantTSFFListRecRef == DEM_IRT_OK )
                {
                    if( Dem_UdmTmpEventMemoryEntry.FaultRecord.TimeSeriesFreezeFrameListIndex >= tsffTotalDTCNum )
                    {
                        Dem_UdmTmpEventMemoryEntry.FaultRecord.TimeSeriesFreezeFrameListIndex = tsFFListRecIndex;                                   /* [GUD]tsFFListRecIndex */
                    }

                    /* When the storage of FFD at the first time, FFD other than the first time shall be cleared. */
                    if( Dem_UdmTmpEventMemoryEntry.StorageOfFFDAtFirstTimeFlag == (boolean)TRUE )
                    {
                        Dem_UdmData_ClearTSFFListRecordOtherThanTheFirstTime( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex, tsFFClassRef, tsFFListRecIndex );   /* [GUD]tsFFClassRef *//* [GUD]tsFFListRecIndex */
                    }
                }
            }
        }
        /* Dealing with the writing of TSFFD outside the exclusive section */
        /* Set the data of TSFFD in fault record */
#ifndef JGXSTACK
        /* Starts exclusion. */
        Dem_UdmExcFncTable[ Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex ].ExclusiveEnterFnc();      /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */
#else   /* JGXSTACK */
        Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */

        (void)Dem_UdmFaultMngC_SetTSFFListIndex( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex, Dem_UdmTmpEventMemoryEntry.EventRecord.UdmFaultIndex, &Dem_UdmTmpEventMemoryEntry.FaultRecord );  /* no return check required */

#ifndef JGXSTACK
        /* Finishes exclusion. */
        Dem_UdmExcFncTable[ Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex ].ExclusiveExitFnc();       /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */
#else   /* JGXSTACK */
        Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */

    }


    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_CaptureTSFFFromSample                        */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] SamplingFreezeFrameRef :                            */
/*               |                                                          */
/*               | [in] NumberOfBeforeTriggeredRecord :                     */
/*               |                                                          */
/*               | [in] TimeSeriesFreezeFrameTableRef :                     */
/*               |                                                          */
/*               | [in] TriggerFFDConsistencyId :                           */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] TimeSeriesFreezeFrameTableRef       */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_CaptureTSFFFromSample
(
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) SamplingFreezeFrameRef,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumberOfBeforeTriggeredRecord,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameTableRef,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) TriggerFFDConsistencyId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) samplingFreezeFrameMemoryRef;
    VAR( Dem_u16_SmpTSFFDIndexType, AUTOMATIC ) loopCnt;
    VAR( Dem_u16_SmpTSFFDIndexType, AUTOMATIC ) samplingFFRecIndex;
    VAR( Dem_u16_SmpTSFFDIndexType, AUTOMATIC ) numberOfSamplingFFRec;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecIndex;
    VAR( Dem_u16_SmpTSFFDIndexType, AUTOMATIC ) ffdRecordNum;
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) tsffSamplingFFClassConfigureNum;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_SamplingFreezeFrameRecordPosType, AUTOMATIC ) samplingFFRPos;
    P2VAR( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) samplingFreezeFrameRecordDataPtr;

    tsffSamplingFFClassConfigureNum = Dem_TSFFSamplingFFClassConfigureNum;

    if( SamplingFreezeFrameRef >= tsffSamplingFFClassConfigureNum )         /* [GUD:if]SamplingFreezeFrameRef */
    {
        retVal = DEM_IRT_NG;
    }
    else
    {
        tsffTotalDTCNum = Dem_TSFFTotalDTCNum;

        samplingFreezeFrameMemoryRef = Dem_SamplingFreezeFrameTable[SamplingFreezeFrameRef].DemSamplingFreezeFrameMemoryRef;    /* [GUD]SamplingFreezeFrameRef *//* [GUD:CFG:IF_GUARDED: SamplingFreezeFrameRef ]samplingFreezeFrameMemoryRef */
        ffdRecordNum = Dem_Data_GetSamplingFFDRecordNum( samplingFreezeFrameMemoryRef );                                        /* [GUD]samplingFreezeFrameMemoryRef */

        if( TimeSeriesFreezeFrameTableRef >= tsffTotalDTCNum )                                                                                                      /* [GUD:if]TimeSeriesFreezeFrameTableRef */
        {
            retVal = DEM_IRT_NG;
        }
        else if( Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameRef].CurrentIndex >= ffdRecordNum )                                                       /* [GUD]SamplingFreezeFrameRef */
        {
            retVal = DEM_IRT_NG;
        }
        else if( Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameRef].CurrentIndex < Dem_SamplingFreezeFrameTable[SamplingFreezeFrameRef].DemStartIndex )  /* [GUD]SamplingFreezeFrameRef */
        {
            retVal = DEM_IRT_NG;
        }
        else if( Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameRef].CurrentIndex > Dem_SamplingFreezeFrameTable[SamplingFreezeFrameRef].DemEndIndex )    /* [GUD]SamplingFreezeFrameRef */
        {
            retVal = DEM_IRT_NG;
        }
        else
        {
            numberOfSamplingFFRec = ( ( Dem_SamplingFreezeFrameTable[SamplingFreezeFrameRef].DemEndIndex - Dem_SamplingFreezeFrameTable[SamplingFreezeFrameRef].DemStartIndex ) + (Dem_u16_SmpTSFFDIndexType)1U );  /* [GUD]SamplingFreezeFrameRef */
            Dem_Data_GetSamplingFreezeFrameRecordPosition( samplingFreezeFrameMemoryRef, &samplingFFRPos );         /* [GUD]samplingFreezeFrameMemoryRef *//* [GUD:OUT:IF_GUARDED: samplingFreezeFrameMemoryRef ] &samplingFFRPos */

            for( loopCnt = (Dem_u16_SmpTSFFDIndexType)0U; loopCnt < NumberOfBeforeTriggeredRecord; loopCnt++ )
            {
                if( ( Dem_SamplingFreezeFrameTable[SamplingFreezeFrameRef].DemStartIndex + loopCnt ) <= Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameRef].CurrentIndex )    /* [GUD]SamplingFreezeFrameRef */
                {
                    samplingFFRecIndex = ( Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameRef].CurrentIndex - loopCnt );                                                      /* [GUD]SamplingFreezeFrameRef */
                }
                else
                {
                    samplingFFRecIndex = ( ( Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameRef].CurrentIndex + numberOfSamplingFFRec ) - loopCnt );                          /* [GUD]SamplingFreezeFrameRef */
                }

                tsFFRecIndex = ( Dem_TimeSeriesFreezeFrameTable[TimeSeriesFreezeFrameTableRef].DemStartIndex + ( (Dem_u16_TSFFDIndexType)NumberOfBeforeTriggeredRecord - (Dem_u16_TSFFDIndexType)loopCnt - (Dem_u16_TSFFDIndexType)1U ) );  /* [GUD]TimeSeriesFreezeFrameTableRef */

                samplingFreezeFrameRecordDataPtr = Dem_Data_GetSamplingFreezeFrameRecordDataPtr( samplingFreezeFrameMemoryRef, samplingFFRecIndex );    /* [GUD:RET:Not NULL_PTR ] samplingFreezeFrameMemoryRef */
                if( samplingFreezeFrameRecordDataPtr != NULL_PTR )
                {
                    (void)Dem_UdmTSFFDMng_SetBeforeTimeSeriesFreezeFrameRecord( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex, Dem_UdmTmpEventMemoryEntry.OldestFreezeFrameRecordIndex, tsFFRecIndex, Dem_UdmTmpEventMemoryEntry.UdmEventIndex, TriggerFFDConsistencyId, &samplingFreezeFrameRecordDataPtr[samplingFFRPos.DataStart] );/* no return check required */ /* [GUD]samplingFFRPos.DataStart *//* [ARYCHK] (Dem_SamplingFreezeFrameRecordTable[samplingFreezeFrameMemoryRef].DemFFDStoredFormatSize) / 1 / samplingFFRPos.DataStart */
                }
            }

            /* Dealing with the writing of TSFFD outside the exclusive section */
            /* Change what was temporarily not stored to stored */
#ifndef JGXSTACK
            /* Starts exclusion. */
            Dem_UdmExcFncTable[ Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex ].ExclusiveEnterFnc();      /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */
#else   /* JGXSTACK */
            Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */

            for( loopCnt = (Dem_u16_SmpTSFFDIndexType)0U; loopCnt < NumberOfBeforeTriggeredRecord; loopCnt++ )                                          /* [GUD:for]loopCnt */
            {
                if( ( Dem_SamplingFreezeFrameTable[SamplingFreezeFrameRef].DemStartIndex + loopCnt ) <= Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameRef].CurrentIndex )        /* [GUD]SamplingFreezeFrameRef */
                {
                    samplingFFRecIndex = ( Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameRef].CurrentIndex - loopCnt );                              /* [GUD]SamplingFreezeFrameRef */
                }
                else
                {
                    samplingFFRecIndex = ( ( Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameRef].CurrentIndex + numberOfSamplingFFRec ) - loopCnt );  /* [GUD]SamplingFreezeFrameRef */
                }

                tsFFRecIndex = ( Dem_TimeSeriesFreezeFrameTable[TimeSeriesFreezeFrameTableRef].DemStartIndex + ( (Dem_u16_TSFFDIndexType)NumberOfBeforeTriggeredRecord - (Dem_u16_TSFFDIndexType)loopCnt - (Dem_u16_TSFFDIndexType)1U ) );  /* [GUD]TimeSeriesFreezeFrameTableRef */
                samplingFreezeFrameRecordDataPtr = Dem_Data_GetSamplingFreezeFrameRecordDataPtr( samplingFreezeFrameMemoryRef, samplingFFRecIndex );    /* [GUD:RET:Not NULL_PTR ] samplingFreezeFrameMemoryRef */
                if( samplingFreezeFrameRecordDataPtr != NULL_PTR )
                {
                    if( samplingFreezeFrameRecordDataPtr[samplingFFRPos.RecordStatus] == DEM_FFD_STORED )               /* [GUD]samplingFFRPos.RecordStatus *//* [ARYCHK] (Dem_SamplingFreezeFrameRecordTable[samplingFreezeFrameMemoryRef].DemFFDStoredFormatSize) / 1 / samplingFFRPos.RecordStatus */
                    {
                        Dem_UdmTSFFDMng_SetRecordStatus( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex, tsFFRecIndex );
                    }
                }
            }
#ifndef JGXSTACK
            /* Finishes exclusion. */
            Dem_UdmExcFncTable[ Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex ].ExclusiveExitFnc();       /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */
#else   /* JGXSTACK */
            Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */

            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_ClearTSFFListRecordOtherThanTheFirstTime     */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |                                                          */
/*               | [in] TimeSeriesFreezeFrameClassRef :                     */
/*               |                                                          */
/*               | [in] StartTSFFListIndex :                                */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmData_ClearTSFFListRecordOtherThanTheFirstTime
(
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameClassRef,     /* [PRMCHK:CALLER] */
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) StartTSFFListIndex                  /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfTimeSeriesFreezeFramePerDTC;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) loopCount;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecStartIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecEndIndex;

    numberOfTimeSeriesFreezeFramePerDTC = Dem_TSFFClassTable[TimeSeriesFreezeFrameClassRef].DemNumberOfTimeSeriesFreezeFramePerDTC; /* [GUDCHK:CALLER]TimeSeriesFreezeFrameClassRef *//* [GUD:CFG:IF_GUARDED:TimeSeriesFreezeFrameClassRef]numberOfTimeSeriesFreezeFramePerDTC */

    for ( loopCount = (Dem_u16_TSFFListIndexType)1U; loopCount < numberOfTimeSeriesFreezeFramePerDTC; loopCount++ )
    {
        tsFFListRecIndex = StartTSFFListIndex + loopCount;                                              /* [GUDCHK:CALLER]TimeSeriesFreezeFrameClassRef *//* [GUDCHK:CALLER]StartTSFFListIndex */

        tsFFRecStartIndex = Dem_TimeSeriesFreezeFrameTable[tsFFListRecIndex].DemStartIndex;             /* [GUDCHK:CALLER]TimeSeriesFreezeFrameClassRef *//* [GUDCHK:CALLER]StartTSFFListIndex */
        tsFFRecEndIndex = Dem_TimeSeriesFreezeFrameTable[tsFFListRecIndex].DemEndIndex;                 /* [GUDCHK:CALLER]TimeSeriesFreezeFrameClassRef *//* [GUDCHK:CALLER]StartTSFFListIndex */

        Dem_UdmTSFFDMng_ClearTSFFList( UdmGroupKindIndex, tsFFRecStartIndex, tsFFRecEndIndex );

        Dem_Data_InitTSFFListRecord( &Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecIndex] );      /* [GUDCHK:CALLER]TimeSeriesFreezeFrameClassRef *//* [GUDCHK:CALLER]StartTSFFListIndex */
    }

    /* To update VacantTimeSeriesFreezeFrameListRecordRef in Dem_TimeSeriesFreezeFrameCtrlRecordList[], */
    /* Dem_Data_UpdateVacantTSFFListRecordRef() already called in Dem_UdmData_StoreTSFFRecordFromSample(). */

    /* Dem_TimeSeriesFreezeFrameCtrlRecordList[].CurrentIndex[] is setting already at caller of this function, */
    /* so Dem_UdmData_InitCurrentIndexOfTSFFListRecord() is must not call in this function. */

    return;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
