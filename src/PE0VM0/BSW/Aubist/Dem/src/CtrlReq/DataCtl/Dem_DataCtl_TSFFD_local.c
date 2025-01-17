/* Dem_DataCtl_TSFFD_local_c(v5-5-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_TSFFD_local/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_CmnLib_DataCtl_SamplingFFD.h"
#include "../../../inc/Dem_CmnLib_DataCtl_SamplingFFDAccess.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "Dem_DataCtl_local.h"
#include "Dem_DataCtl_TSFFD_local.h"
#include "Dem_DataCtl_EventEntry_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )

#define DEM_CONFIGURE_MINIMUM_NUM_OF_FAULT_RECORD         ((Dem_u08_FaultIndexType)1U)

#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_Data_ClearTSFFROverwritten
( void );
static FUNC( void, DEM_CODE ) Dem_Data_ClearTSFFRFaultRecordOverwritten
( void );
static FUNC( void, DEM_CODE ) Dem_Data_ClearTSFFRFFROverwritten
( void );
static FUNC( void, DEM_CODE ) Dem_Data_ClearTSFFListRecordOverwritten
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TimeSeriesFreezeFramePerDTCIndex,
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) DTCAttributePtr
);
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_CaptureTSFFFromSample
(
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) SamplingFreezeFrameRef,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumberOfBeforeTriggeredRecord,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameTableRef,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) TriggerFFDConsistencyId
);

static FUNC( void, DEM_CODE ) Dem_Data_GenerateTSFFLRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_TimeSeriesFreezeFrameListType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameListRecordListPtr
);

#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_Data_JudgeStoreTSFFRecord
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger
);
static FUNC( boolean, DEM_CODE ) Dem_Data_GetJudgeResultStoreTSFFRecord
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger
);
#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */

#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )
static VAR( boolean, DEM_VAR_NO_INIT ) Dem_Data_JudgeStoreConfirmedTSFFRecordFlg;
#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )

/****************************************************************************/
/* Function Name | Dem_Data_PrepareStoreTSFFRecordFromSample                */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_PrepareStoreTSFFRecordFromSample
( void )
{
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsFFRecClassRefIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) tsffTrigger;
    VAR( boolean, AUTOMATIC ) readDataElementAllowed;
#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) retJudgeStoreTSFFRecord;
#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */


    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;
    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;
    failRecordNum = Dem_FailRecordNum;

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /* [FuncSw] */
    Dem_Data_ClearTSFFROverwritten();
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */

    /* If number of fault occurrence has been got over the maximum number of event memory entries, no need to carry out the following process. */
    if( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex < failRecordNum )
    {
        dtcAttributePtr    =   Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF( Dem_TmpEventMemoryEntry.EventStrgIndex );           /* [GUD:RET:Not NULL_PTR]dtcAttributePtr */

        if ( dtcAttributePtr != NULL_PTR )                                              /* [GUD:if]dtcAttributePtr */
        {
            for( tsFFRecClassRefIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; tsFFRecClassRefIndex < tsffRecordClassNumPerDTCMaxNum; tsFFRecClassRefIndex++ )    /* [GUD:for]tsFFRecClassRefIndex */
            {
                tsFFRecClassRef = dtcAttributePtr->DemTimeSeriesFreezeFrameRecordClassRef[tsFFRecClassRefIndex];    /* [GUD]dtcAttributePtr *//* [GUD]tsFFRecClassRefIndex */

                if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )                                          /* [GUD:if]tsFFRecClassRef */
                {
                    tsffTrigger = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameTrigger;        /* [GUD]tsFFRecClassRef */

#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     /*  [FuncSw]    */
                    retJudgeStoreTSFFRecord = Dem_Data_JudgeStoreTSFFRecord( tsffTrigger );
                    if( retJudgeStoreTSFFRecord == (boolean)TRUE)
#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */
                    {

                        readDataElementAllowed = Dem_CfgInfo_CheckTrigger( tsffTrigger, Dem_TmpEventMemoryEntry.Trigger );

                        if( readDataElementAllowed == (boolean)TRUE)
                        {
                            if( Dem_TmpEventMemoryEntry.FaultRecord.TimeSeriesFreezeFrameListIndex[tsFFRecClassRefIndex] < tsffTotalDTCNum )            /* [GUD]tsFFRecClassRefIndex */
                            {
                                tsFFListRecIndex = Dem_TmpEventMemoryEntry.FaultRecord.TimeSeriesFreezeFrameListIndex[tsFFRecClassRefIndex];            /* [GUD]tsFFRecClassRefIndex */
                            }
                            else
                            {
                                tsFFListRecIndex = Dem_TimeSeriesFreezeFrameCtrlRecordList[tsFFRecClassRef].VacantTimeSeriesFreezeFrameListRecordRef;   /* [GUD]tsFFRecClassRef */
                            }

                            /* Dealing with the writing of TSFFD outside the exclusive section */
                            /* Temporarily clear the area of TSFFD to be registered */
                            Dem_Data_ClearTSFFRecord( tsFFListRecIndex );
                        }
                    }
                }
            }
        }
    }
    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_StoreTSFFRecordFromSample                       */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_StoreTSFFRecordFromSample
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfCaptureTimsSeries;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfUpdataVacantTSFFListRecRef;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsFFRecClassRefIndex;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfBeforeTriggeredRecord;
    VAR( boolean, AUTOMATIC ) readDataElementAllowed;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) samplingFFRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) tsffTrigger;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChkExistTrigger;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) triggerFFDIndex;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) triggerFFDConsistencyId;
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;
#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC ) retJudgeStoreTSFFRecord;
#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */

    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;
    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;
    failRecordNum = Dem_FailRecordNum;

    /* If number of fault occurrence has been got over the maximum number of event memory entries, no need to carry out the following process. */
    if( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex < failRecordNum )
    {
        dtcAttributePtr    =   Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF( Dem_TmpEventMemoryEntry.EventStrgIndex );           /* [GUD:RET:Not NULL_PTR]dtcAttributePtr */

        if ( dtcAttributePtr != NULL_PTR )                                              /* [GUD:if]dtcAttributePtr */
        {
            for( tsFFRecClassRefIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; tsFFRecClassRefIndex < tsffRecordClassNumPerDTCMaxNum; tsFFRecClassRefIndex++ )    /* [GUD:for]tsFFRecClassRefIndex */
            {
                tsFFRecClassRef = dtcAttributePtr->DemTimeSeriesFreezeFrameRecordClassRef[tsFFRecClassRefIndex];    /* [GUD]dtcAttributePtr *//* [GUD]tsFFRecClassRefIndex */

                if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )                                          /* [GUD:if]tsFFRecClassRef */
                {
                    tsffTrigger = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameTrigger;        /* [GUD]tsFFRecClassRef */
#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     /*  [FuncSw]    */
                    retJudgeStoreTSFFRecord = Dem_Data_GetJudgeResultStoreTSFFRecord( tsffTrigger );
                    if( retJudgeStoreTSFFRecord == (boolean)TRUE)
#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */
                    {

                        readDataElementAllowed = Dem_CfgInfo_CheckTrigger( tsffTrigger, Dem_TmpEventMemoryEntry.Trigger );

                        if( readDataElementAllowed == (boolean)TRUE)
                        {
                            resultOfUpdataVacantTSFFListRecRef = DEM_IRT_NG;

                            samplingFFRef = Dem_SamplingFreezeFrameBindTable[tsFFRecClassRef].DemSamplingFreezeFrameRef;            /* [GUD]tsFFRecClassRef */

                            tsFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameClassRef;              /* [GUD]tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED: tsFFRecClassRef ]tsFFClassRef */

                            numberOfBeforeTriggeredRecord = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfBeforeTriggeredRecord;      /* [GUD]tsFFClassRef */

                            if( Dem_TmpEventMemoryEntry.FaultRecord.TimeSeriesFreezeFrameListIndex[tsFFRecClassRefIndex] < tsffTotalDTCNum )    /* [GUD]tsFFRecClassRefIndex */
                            {
                                tsFFListRecIndex = Dem_TmpEventMemoryEntry.FaultRecord.TimeSeriesFreezeFrameListIndex[tsFFRecClassRefIndex];    /* [GUD]tsFFRecClassRefIndex */
                            }
                            else
                            {
                                tsFFListRecIndex = Dem_TimeSeriesFreezeFrameCtrlRecordList[tsFFRecClassRef].VacantTimeSeriesFreezeFrameListRecordRef;   /* [GUD]tsFFRecClassRef */
                            }

                            retChkExistTrigger = Dem_FFDMng_CheckToExistTriggerFFD( tsffTrigger, dtcAttributePtr, &Dem_TmpEventMemoryEntry.FaultRecord, &triggerFFDIndex ); /* [GUD]dtcAttributePtr */
                            if( retChkExistTrigger == DEM_IRT_OK )
                            {
                                triggerFFDConsistencyId = Dem_FFDMng_GetFFDConsystencyId( triggerFFDIndex );

                                resultOfCaptureTimsSeries = Dem_Data_CaptureTSFFFromSample( samplingFFRef, numberOfBeforeTriggeredRecord, tsFFListRecIndex, triggerFFDConsistencyId );  /* [GUD:RET:DEM_IRT_OK] tsFFListRecIndex */

                                if( resultOfCaptureTimsSeries == DEM_IRT_OK )
                                {
                                    Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecIndex].FaultIndex = Dem_TmpEventMemoryEntry.EventRecord.FaultIndex;  /* [GUD]tsFFListRecIndex */

                                    Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecIndex].NumberOfStoredAfterTriggeredRecord = (uint8)0U;               /* [GUD]tsFFListRecIndex */

                                    resultOfUpdataVacantTSFFListRecRef = Dem_Data_UpdateVacantTSFFListRecordRef( tsFFRecClassRef );
                                }

                                if( resultOfUpdataVacantTSFFListRecRef == DEM_IRT_OK )
                                {
                                    Dem_TmpEventMemoryEntry.FaultRecord.TimeSeriesFreezeFrameListIndex[tsFFRecClassRefIndex] = tsFFListRecIndex;            /* [GUD]tsFFRecClassRefIndex */

                                }
                            }
                        }
                    }
                }
            }
            /* Dealing with the writing of TSFFD outside the exclusive section */
            /* Set the data of TSFFD in fault record */
            SchM_Enter_Dem_EventMemory();
            Dem_DataMng_SetTSFFListRecord_Ctl( Dem_TmpEventMemoryEntry.EventRecord.FaultIndex, &Dem_TmpEventMemoryEntry.FaultRecord );
            SchM_Exit_Dem_EventMemory();
        }
    }

    return;
}

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_ClearTSFFROverwritten                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_ClearTSFFROverwritten
( void )
{
    if ( Dem_EventDisplacement.EventStrgIndexOfFaultRecordOverwritten != DEM_EVENTSTRGINDEX_INVALID )
    {
        Dem_Data_ClearTSFFRFaultRecordOverwritten();
    }
    Dem_Data_ClearTSFFRFFROverwritten();

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_ClearTSFFRFaultRecordOverwritten                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_ClearTSFFRFaultRecordOverwritten
( void )
{
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) frTSFFRemoveIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffListIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;

    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;
    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;

    eventStorageNum =   Dem_PrimaryMemEventStorageNum;
    eventStrgIndex  =   Dem_EventDisplacement.EventStrgIndexOfFaultRecordOverwritten;
    if ( eventStrgIndex < eventStorageNum )                                             /* [GUD:if]eventStrgIndex */
    {
        dtcAttributePtr    =   Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF( eventStrgIndex ); /* [GUD]eventStrgIndex *//* [GUD:RET:Not NULL_PTR]dtcAttributePtr */

        if ( dtcAttributePtr != NULL_PTR )                                              /* [GUD:if]dtcAttributePtr */
        {
            for( frTSFFRemoveIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; frTSFFRemoveIndex < tsffRecordClassNumPerDTCMaxNum; frTSFFRemoveIndex++ ) /* [GUD:for]frTSFFRemoveIndex */
            {
                tsffListIndex = Dem_EventDisplacement.FaultRecordTSFFRemove[frTSFFRemoveIndex];                                 /* [GUD]frTSFFRemoveIndex */

                if( tsffListIndex < tsffTotalDTCNum )                                                                           /* [GUD:if]tsffListIndex */
                {
                    /* In case the time-series freeze frame record list index is valid. */

                    /* Clears time-series freeze frame record not reused in the fault record overwritten. */
                    /* Not check return value, as tsffListIndex is valid. */
                    Dem_Data_ClearTSFFRecord( tsffListIndex );                                                                  /* [GUD]tsffListIndex */

                    Dem_Data_ClearTSFFListRecordOverwritten( tsffListIndex, frTSFFRemoveIndex, dtcAttributePtr );               /* [GUD]tsffListIndex *//* [GUD]dtcAttributePtr */
                }
            }
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_ClearTSFFRFFROverwritten                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_ClearTSFFRFFROverwritten
( void )
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) frOverwrittenIndex;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) frTSFFRemoveIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffListIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;
    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;
    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    for( frOverwrittenIndex = (Dem_u08_FFListIndexType)0U; frOverwrittenIndex < nonOBDFFRClassPerDTCMaxNum; frOverwrittenIndex++ )  /* [GUD:for]frOverwrittenIndex */
    {
        eventStrgIndex  =   Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].EventStrgIndex;    /* [GUD]frOverwrittenIndex */
        if ( eventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]eventStrgIndex */
        {
            dtcAttributePtr    =   Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF( eventStrgIndex ); /* [GUD]eventStrgIndex *//* [GUD:RET:Not NULL_PTR]dtcAttributePtr */

            if ( dtcAttributePtr != NULL_PTR )                                              /* [GUD:if]dtcAttributePtr */
            {
                for( frTSFFRemoveIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; frTSFFRemoveIndex < tsffRecordClassNumPerDTCMaxNum; frTSFFRemoveIndex++ ) /* [GUD:for]frTSFFRemoveIndex */
                {
                    tsffListIndex = Dem_EventDisplacement.FaultRecordOverwritten[frOverwrittenIndex].TimeSeriesFreezeFrameListIndex[frTSFFRemoveIndex]; /* [GUD]frOverwrittenIndex *//* [GUD]frTSFFRemoveIndex */
                    if( tsffListIndex < tsffTotalDTCNum )                                                               /* [GUD:if]tsffListIndex */
                    {
                        /* In case the time-series freeze frame record list index is valid. */

                        /* Clears time-series freeze frame record not reused in the freeze frame record overwritten. */
                        /* Not check return value, as tsffListIndex is valid. */
                        Dem_Data_ClearTSFFRecord( tsffListIndex );                                                      /* [GUD]tsffListIndex */

                        Dem_Data_ClearTSFFListRecordOverwritten( tsffListIndex, frTSFFRemoveIndex, dtcAttributePtr );   /* [GUD]tsffListIndex *//* [GUD]dtcAttributePtr */
                    }
                }
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_ClearTSFFListRecordOverwritten                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] TimeSeriesFreezeFrameListIndex :                    */
/*               |                                                          */
/*               | [in] TimeSeriesFreezeFramePerDTCIndex :                  */
/*               |                                                          */
/*               | [in] DTCAttributePtr :                                   */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_ClearTSFFListRecordOverwritten
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListIndex,             /* [PRMCHK:CALLER] */
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TimeSeriesFreezeFramePerDTCIndex,     /* [PRMCHK:CALLER] */
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) DTCAttributePtr
)
{
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;

    Dem_Data_InitTSFFListRecord( &Dem_TimeSeriesFreezeFrameListRecordList[TimeSeriesFreezeFrameListIndex] );        /* [GUDCHK:CALLER]TimeSeriesFreezeFrameListIndex */

    tsFFRecClassRef = DTCAttributePtr->DemTimeSeriesFreezeFrameRecordClassRef[TimeSeriesFreezeFramePerDTCIndex];    /* [GUDCHK:CALLER]TimeSeriesFreezeFramePerDTCIndex */
    (void)Dem_Data_UpdateVacantTSFFListRecordRef( tsFFRecClassRef );    /* no return check required */

    return;
}

#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_Data_CaptureTSFFFromSample                           */
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
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_CaptureTSFFFromSample
(
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) SamplingFreezeFrameRef,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumberOfBeforeTriggeredRecord,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameTableRef,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) TriggerFFDConsistencyId
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSetTSFFRec;
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) samplingFreezeFrameMemoryRef;
    VAR( Dem_u16_SmpTSFFDIndexType, AUTOMATIC ) loopCnt;
    VAR( Dem_u16_SmpTSFFDIndexType, AUTOMATIC ) samplingFFRecIndex;
    VAR( Dem_u16_SmpTSFFDIndexType, AUTOMATIC ) numberOfSamplingFFRec;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecIndex;
    VAR( Dem_u16_SmpTSFFDIndexType, AUTOMATIC ) tsffTotalSamplingFFRecordNum;
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) tsffSamplingFFClassConfigureNum;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_SamplingFreezeFrameRecordPosType, AUTOMATIC ) samplingFFRPos;
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) samplingFreezeFrameRecordDataPtr;

    retVal = DEM_IRT_OK;
    tsffTotalSamplingFFRecordNum = Dem_TSFFTotalSamplingFFRecordNum;
    tsffSamplingFFClassConfigureNum = Dem_TSFFSamplingFFClassConfigureNum;
    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;

    if( SamplingFreezeFrameRef >= tsffSamplingFFClassConfigureNum )                             /* [GUD:if]SamplingFreezeFrameRef */
    {
        retVal = DEM_IRT_NG;
    }
    else if( TimeSeriesFreezeFrameTableRef >= tsffTotalDTCNum )                                 /* [GUD:if]TimeSeriesFreezeFrameTableRef */
    {
        retVal = DEM_IRT_NG;
    }
    else if( Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameRef].CurrentIndex >= tsffTotalSamplingFFRecordNum )   /* [GUD]SamplingFreezeFrameRef */
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
        samplingFreezeFrameMemoryRef = Dem_SamplingFFRecordPrimaryMemory;
        Dem_Data_GetSamplingFreezeFrameRecordPosition( samplingFreezeFrameMemoryRef, &samplingFFRPos );             /* [GUD]samplingFreezeFrameMemoryRef *//* [GUD:OUT:IF_GUARDED: samplingFreezeFrameMemoryRef ] &samplingFFRPos */

        for( loopCnt = (Dem_u16_SmpTSFFDIndexType)0U; loopCnt < NumberOfBeforeTriggeredRecord; loopCnt++ )
        {
            if( ( Dem_SamplingFreezeFrameTable[SamplingFreezeFrameRef].DemStartIndex + loopCnt ) <= Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameRef].CurrentIndex )    /* [GUD]SamplingFreezeFrameRef */
            {
                samplingFFRecIndex = ( Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameRef].CurrentIndex - loopCnt );                                  /* [GUD]SamplingFreezeFrameRef */
            }
            else
            {
                samplingFFRecIndex = ( ( Dem_SamplingFreezeFrameListRecordList[SamplingFreezeFrameRef].CurrentIndex + numberOfSamplingFFRec ) - loopCnt );      /* [GUD]SamplingFreezeFrameRef */
            }

            tsFFRecIndex = ( Dem_TimeSeriesFreezeFrameTable[TimeSeriesFreezeFrameTableRef].DemStartIndex + ( (Dem_u16_TSFFDIndexType)NumberOfBeforeTriggeredRecord - (Dem_u16_TSFFDIndexType)loopCnt - (Dem_u16_TSFFDIndexType)1U ) );  /* [GUD]TimeSeriesFreezeFrameTableRef */

            samplingFreezeFrameRecordDataPtr = Dem_Data_GetSamplingFreezeFrameRecordDataPtr( samplingFreezeFrameMemoryRef, samplingFFRecIndex );        /* [GUD:RET:Not NULL_PTR ] samplingFreezeFrameMemoryRef */
            if( samplingFreezeFrameRecordDataPtr != NULL_PTR )
            {
                resultOfSetTSFFRec = Dem_DataMngC_SetBeforeTimeSeriesFreezeFrameRecord( tsFFRecIndex, Dem_TmpEventMemoryEntry.FaultRecord.EventStrgIndex, TriggerFFDConsistencyId, &samplingFreezeFrameRecordDataPtr[samplingFFRPos.DataStart] );   /* [GUD]samplingFFRPos */

                if( resultOfSetTSFFRec != DEM_IRT_OK )
                {
                    retVal = DEM_IRT_NG;
                }
            }
        }

        /* Dealing with the writing of TSFFD outside the exclusive section */
        /* Change what was temporarily not stored to stored */
        SchM_Enter_Dem_EventMemory();
        for( loopCnt = (Dem_u16_SmpTSFFDIndexType)0U; loopCnt < NumberOfBeforeTriggeredRecord; loopCnt++ )      /* [GUD:for]loopCnt */
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
                if( samplingFreezeFrameRecordDataPtr[samplingFFRPos.RecordStatus] == DEM_FFD_STORED )                           /* [GUD]samplingFFRPos */
                {
                    Dem_DataMngC_SetRecordStatusToStoredOfBeforeTSFFD( tsFFRecIndex );
                }
            }
        }
        SchM_Exit_Dem_EventMemory();

    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_Data_ClearTSFFListRecord                             */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] FaultRecordPtr :                                    */
/*               |                                                          */
/*               | [in] RequestKindForDataMM :                              */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_ClearTSFFListRecord
(
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
)
{
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) indexOfTSFFListIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;

    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;

    for( indexOfTSFFListIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; indexOfTSFFListIndex < tsffRecordClassNumPerDTCMaxNum; indexOfTSFFListIndex++ )    /* [GUD:for]indexOfTSFFListIndex */
    {
        tsFFListRecIndex = FaultRecordPtr->TimeSeriesFreezeFrameListIndex[indexOfTSFFListIndex];                                                        /* [GUD]indexOfTSFFListIndex */

        if( tsFFListRecIndex != DEM_INVALID_TSFF_RECORD_INDEX )             /* [GUD:if]tsFFListRecIndex */
        {
            Dem_Data_ClearTSFFRecord( tsFFListRecIndex );                   /* [GUD]tsFFListRecIndex */

        }
        else
        {
            /* No process */
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_ClearTSFFRecord                                 */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] TimeSeriesFreezeFrameListRecordIndex :              */
/*               |                                                          */
/*               | [in] RequestKindForDataMM :                              */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_ClearTSFFRecord
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListRecordIndex
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) recordStatus;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;

    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;
    failRecordNum = Dem_FailRecordNum;

    if( TimeSeriesFreezeFrameListRecordIndex < tsffTotalDTCNum )        /* [GUD:if]TimeSeriesFreezeFrameListRecordIndex */
    {
        if( Dem_TimeSeriesFreezeFrameListRecordList[TimeSeriesFreezeFrameListRecordIndex].FaultIndex < failRecordNum )  /* [GUD]TimeSeriesFreezeFrameListRecordIndex */
        {
            for( tsFFRecIndex = Dem_TimeSeriesFreezeFrameTable[TimeSeriesFreezeFrameListRecordIndex].DemStartIndex; tsFFRecIndex <= Dem_TimeSeriesFreezeFrameTable[TimeSeriesFreezeFrameListRecordIndex].DemEndIndex; tsFFRecIndex++ )  /* [GUD]TimeSeriesFreezeFrameListRecordIndex */ /* [GUD:for]tsFFRecIndex */
            {
                recordStatus = Dem_DataMngC_GetRecordStatusOfTimeSeriesFreezeFrameRecord( tsFFRecIndex );               /* [GUD]tsFFRecIndex */

                if( recordStatus == DEM_FFD_STORED )
                {
                    (void)Dem_DataMngC_ClearTimeSeriesFreezeFrameRecord( tsFFRecIndex );    /* no return check required */  /* [GUD]tsFFRecIndex */

                }
            }

            /* Initializing of the time-series freeze frame list record is executed, */
            /* after sets request for time-series freeze frame list record updating. */
        }
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_GenerateTSFFLRecordList                         */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GenerateTSFFLRecordList
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) samplingFreezeFrameMemoryRef;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;
    VAR( Dem_TimeSeriesFreezeFrameListType, AUTOMATIC ) timeSeriesFreezeFrameListRecordList[DEM_TSFF_TOTAL_DTC_NUM];

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    Dem_Data_SaveTSFFListRecordList( timeSeriesFreezeFrameListRecordList );

    /* Initializes time-series freeze frame related memory. */
    samplingFreezeFrameMemoryRef = Dem_SamplingFFRecordPrimaryMemory;
    Dem_Data_InitTSFFListRecordList( samplingFreezeFrameMemoryRef );
    Dem_Data_InitTSFFCtrlRecordList( samplingFreezeFrameMemoryRef );

    for( eventStrgIndex = (Dem_u16_EventStrgIndexType)0U; eventStrgIndex < eventStorageNum; eventStrgIndex++ )  /* [GUD:for]eventStrgIndex */
    {
        resultOfGetFaultRec = DEM_IRT_NG;
        faultIndex = DEM_FAULTINDEX_INITIAL;

        resultOfGetFaultIndex = Dem_DataMngC_GetER_FaultIndex( eventStrgIndex, &faultIndex );                   /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */

        if( resultOfGetFaultIndex == DEM_IRT_OK )
        {
            resultOfGetFaultRec = Dem_DataMngC_GetFaultRecord( faultIndex, &faultRecord );
        }

        if( resultOfGetFaultRec == DEM_IRT_OK )
        {
            Dem_Data_GenerateTSFFLRecord( eventStrgIndex, faultIndex, &faultRecord, timeSeriesFreezeFrameListRecordList );
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_GenerateTSFFLRecord                             */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |                                                          */
/*               | [in] FaultIndex :                                        */
/*               |                                                          */
/*               | [in] FaultRecordPtr :                                    */
/*               |                                                          */
/*               | [in] TimeSeriesFreezeFrameListRecordListPtr :            */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_GenerateTSFFLRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_TimeSeriesFreezeFrameListType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameListRecordListPtr
)
{
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsFFListIndex;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;

    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;
    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;
    failRecordNum = Dem_FailRecordNum;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if( EventStrgIndex >= eventStorageNum )     /* [GUD:if]EventStrgIndex */
    {
        /* No process */
    }
    else if( FaultIndex >= failRecordNum )      /* [GUD:if]FaultIndex */
    {
        /* No process */
    }
    else
    {
        dtcAttributePtr    =   Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF( EventStrgIndex ); /* [GUD]EventStrgIndex *//* [GUD:RET:Not NULL_PTR]dtcAttributePtr */

        if ( dtcAttributePtr != NULL_PTR )                                              /* [GUD:if]dtcAttributePtr */
        {
            for( tsFFListIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; tsFFListIndex < tsffRecordClassNumPerDTCMaxNum; tsFFListIndex++ ) /* [GUD:for]tsFFListIndex */
            {
                tsFFRecClassRef = dtcAttributePtr->DemTimeSeriesFreezeFrameRecordClassRef[tsFFListIndex];                               /* [GUD]dtcAttributePtr *//* [GUD]tsFFListIndex */

                if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )                                                              /* [GUD:if]tsFFRecClassRef */
                {
                    tsFFListRecIndex = FaultRecordPtr->TimeSeriesFreezeFrameListIndex[tsFFListIndex];                                   /* [GUD]tsFFListIndex */

                    if( tsFFListRecIndex < tsffTotalDTCNum )                                                                            /* [GUD:if]tsFFListRecIndex */
                    {
                        Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecIndex].FaultIndex = FaultIndex;                              /* [GUD]tsFFListRecIndex */

                        Dem_Data_UpdateNumberOfStoredAfterTriggeredRecord( FaultIndex, tsFFListRecIndex, tsFFRecClassRef, TimeSeriesFreezeFrameListRecordListPtr ); /* [GUD]tsFFListRecIndex *//* [GUD]tsFFRecClassRef */

                        (void)Dem_Data_UpdateVacantTSFFListRecordRef( tsFFRecClassRef );/* no return check required */                  /* [GUD]tsFFRecClassRef */
                    }
                }
            }
        }
    }

    return;

}

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_DeleteTSFFListByFFRTrigger                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_DeleteTSFFListByFFRTrigger
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FRNotOverwrittenIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex       /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFRTrigger;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) freezeFrameRecordTrigger;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsFFListIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;

    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;

    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;
    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;

    resultOfGetFFRTrigger = Dem_Data_GetFFRTriggerByFFRClassIndex( EventStrgIndex, FRNotOverwrittenIndex, &freezeFrameRecordTrigger );  /* [GUDCHK:CALLER]FRNotOverwrittenIndex *//* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
    if( resultOfGetFFRTrigger == DEM_IRT_OK )
    {
        /* The DTCAttribute table indicated by the DTCAttribute table list Index of the held DTC table is held. */
        dtcAttributePtr    =   Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF( EventStrgIndex ); /* [GUD]EventStrgIndex *//* [GUD:RET:Not NULL_PTR]dtcAttributePtr */

        if ( dtcAttributePtr != NULL_PTR )                                              /* [GUD:if]dtcAttributePtr */
        {
            resultOfGetFaultRec = Dem_DataMngC_GetFaultRecord( FaultIndex, &faultRecord );
            if( resultOfGetFaultRec == DEM_IRT_OK )
            {
                for( tsFFListIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; tsFFListIndex < tsffRecordClassNumPerDTCMaxNum; tsFFListIndex++ ) /* [GUD:for]tsFFListIndex */
                {
                    tsFFRecClassRef = dtcAttributePtr->DemTimeSeriesFreezeFrameRecordClassRef[tsFFListIndex];                               /* [GUD]tsFFListIndex */

                    if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )                                                              /* [GUD:if]tsFFRecClassRef */
                    {
                        tsFFListRecIndex = faultRecord.TimeSeriesFreezeFrameListIndex[tsFFListIndex];                                       /* [GUD]tsFFListIndex */

                        if( tsFFListRecIndex < tsffTotalDTCNum )                                                                            /* [GUD:if]tsFFListRecIndex */
                        {
                            if( Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameTrigger == freezeFrameRecordTrigger )     /* [GUD]tsFFRecClassRef */
                            {
                                Dem_EventDisplacement.FaultRecordOverwritten[FreezeFrameRecordClassIndex].TimeSeriesFreezeFrameListIndex[tsFFListIndex] = tsFFListRecIndex; /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex *//* [GUD]tsFFListIndex */
                                Dem_EventDisplacement.TSFFDeleteByFFROverwritten = (boolean)TRUE;
                            }
                        }
                    }

                }
            }
        }
    }

    return;
}

#endif  /* (DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON ) */


#if ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_JudgeStoreTSFFRecord                            */
/* Description   | Judge TSFFD can be stored.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] Trigger : TSFFD store trigger                       */
/* Return Value  | boolean                                                  */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Data_JudgeStoreTSFFRecord
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger
)
{
    VAR( boolean, AUTOMATIC ) retJudgeStore;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) numOfConfirmedDTCs;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;
    VAR( Dem_u08_TSFFStorePatternType, AUTOMATIC ) tsffStorePattern;

    Dem_Data_JudgeStoreConfirmedTSFFRecordFlg = (boolean)TRUE;

    retJudgeStore = (boolean)TRUE;
    tsffStorePattern = Dem_TSFFStorePattern;
    if( tsffStorePattern == DEM_TSFFD_STORE_PATTERN2 )
    {
        if( Trigger == DEM_TRIGGER_ON_CONFIRMED )
        {
            failRecordNum = Dem_FailRecordNum;
            if( failRecordNum > DEM_CONFIGURE_MINIMUM_NUM_OF_FAULT_RECORD )
            {
                numOfConfirmedDTCs = Dem_DataMngC_GetNumberOfConfirmedDTCs();
                if( numOfConfirmedDTCs > (Dem_u08_OrderIndexType)0U )
                {
                    retJudgeStore = (boolean)FALSE;
                }
            }
            Dem_Data_JudgeStoreConfirmedTSFFRecordFlg = retJudgeStore;
        }
    }

    return retJudgeStore;

}
/****************************************************************************/
/* Function Name | Dem_Data_GetJudgeResultStoreTSFFRecord                   */
/* Description   | Judge TSFFD can be stored.                               */
/* Preconditions | that function Dem_Data_JudgeStoreTSFFRecord has been ex- */
/*               | ecuted                                                   */
/* Parameters    | [in] Trigger : TSFFD store trigger                       */
/* Return Value  | boolean                                                  */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_Data_GetJudgeResultStoreTSFFRecord
(
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) Trigger
)
{
    VAR( boolean, AUTOMATIC ) retJudgeStore;
    VAR( Dem_u08_TSFFStorePatternType, AUTOMATIC ) tsffStorePattern;

    retJudgeStore = (boolean)TRUE;
    tsffStorePattern = Dem_TSFFStorePattern;
    if( tsffStorePattern == DEM_TSFFD_STORE_PATTERN2 )
    {
        if( Trigger == DEM_TRIGGER_ON_CONFIRMED )
        {
            retJudgeStore = Dem_Data_JudgeStoreConfirmedTSFFRecordFlg;
        }
    }

    return retJudgeStore;
}
#endif  /* ( DEM_DTCSTOREDDATA_DEMINTERNAL_SUPPORT == STD_ON )     */


#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
