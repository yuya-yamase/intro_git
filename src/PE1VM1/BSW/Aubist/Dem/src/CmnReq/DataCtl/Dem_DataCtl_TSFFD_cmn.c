/* Dem_DataCtl_TSFFD_cmn_c(v5-7-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_TSFFD_cmn/CODE                                */
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
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_TSFFD.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_Udm_Data.h"
#include "Dem_DataCtl_SamplingFFRecordTable.h"

#if ( DEM_TSFF_SUPPORT == STD_ON )

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

static FUNC( void, DEM_CODE ) Dem_Data_InitAllSmplFFRecordList
( void );
static FUNC( void, DEM_CODE ) Dem_Data_InitSmplFFListRecordList
( void );
static FUNC( void, DEM_CODE ) Dem_Data_InitSmplFFListRecord
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) EndIndex,
    P2VAR( Dem_SamplingFreezeFrameListType, AUTOMATIC, DEM_VAR_NO_INIT ) SamplingFreezeFrameListRecordPtr
);
static FUNC( void, DEM_CODE ) Dem_Data_InitAllTSFFListRecordList
( void );
static FUNC( void, DEM_CODE ) Dem_Data_InitAllTSFFCtrlRecordList
( void );
static FUNC( void, DEM_CODE ) Dem_Data_InitTSFFCtrlRecord
(
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameBindIndex
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

VAR( Dem_TimeSeriesFreezeFrameListType, DEM_VAR_NO_INIT ) Dem_TimeSeriesFreezeFrameListRecordList[DEM_TSFF_TOTAL_DTC_NUM];
VAR( Dem_TimeSeriesFreezeFrameCtrlType, DEM_VAR_NO_INIT ) Dem_TimeSeriesFreezeFrameCtrlRecordList[DEM_TSFF_RECORD_CLASS_CONFIGURE_NUM];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Data_InitTSFFD_AfterRecordCheckComplete              */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_InitTSFFD_AfterRecordCheckComplete
( void )
{
    Dem_Data_InitAllSmplFFRecordList();
    Dem_Data_InitSmplFFListRecordList();
    Dem_Data_InitAllTSFFListRecordList();
    Dem_Data_InitAllTSFFCtrlRecordList();
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /* [FuncSw] */
    Dem_Data_MakeTSFFListRecordList();
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */
#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )  /* [FuncSw] */
    Dem_UdmData_MakeTSFFListRecordList();
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */
    return ;
}


/****************************************************************************/
/* Function Name | Dem_Data_InitAllSmplFFRecordList                         */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_InitAllSmplFFRecordList
( void )
{
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) samplingRecMemIndex;
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) samplingFFRecordMemoryNum;

    samplingFFRecordMemoryNum = Dem_SamplingFFRecordMemoryNum;

    for( samplingRecMemIndex = (Dem_u16_SmpRecMemIndexType)0U; samplingRecMemIndex < samplingFFRecordMemoryNum; samplingRecMemIndex++ ) /* [GUD:for]samplingRecMemIndex */
    {
        Dem_Data_InitSmplFFRecordList( samplingRecMemIndex );   /* [GUD]samplingRecMemIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_InitSmplFFRecordList                            */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] SamplingRecMemIndex :                               */
/*               |      The index for sampling freeze frame memory table.   */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_InitSmplFFRecordList
(
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) SamplingRecMemIndex            /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) ffdStoredFormatSize;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) ffdRecordIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) ffdRecordNum;
    P2VAR( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) samplingFreezeFrameRecordDataPtr;

    ffdStoredFormatSize = Dem_SamplingFreezeFrameRecordTable[SamplingRecMemIndex].DemFFDStoredFormatSize;   /* [GUDCHK:CALLER]SamplingRecMemIndex */
    ffdRecordNum = Dem_SamplingFreezeFrameRecordTable[SamplingRecMemIndex].DemFFDRecordNum;                 /* [GUDCHK:CALLER]SamplingRecMemIndex */

    for( ffdRecordIndex = (Dem_u16_TSFFDIndexType)0U; ffdRecordIndex < ffdRecordNum; ffdRecordIndex++ )                             /* [GUD:for]ffdRecordIndex */
    {
        samplingFreezeFrameRecordDataPtr = Dem_Data_GetSamplingFreezeFrameRecordDataPtr( SamplingRecMemIndex, ffdRecordIndex );     /* [GUD:RET:Not NULL_PTR ] SamplingRecMemIndex */
        if( samplingFreezeFrameRecordDataPtr != NULL_PTR )
        {
            Dem_UtlMem_SetMemory( samplingFreezeFrameRecordDataPtr, DEM_FFD_INITIAL, ffdStoredFormatSize );
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_InitSmplFFListRecordList                        */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_InitSmplFFListRecordList
( void )
{
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) samplingFFListRecIndex;
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) tsffSamplingFFClassConfigureNum;
    VAR( Dem_u16_SmpTSFFDIndexType, AUTOMATIC ) demEndIndex;

    tsffSamplingFFClassConfigureNum = Dem_TSFFSamplingFFClassConfigureNum;
    for( samplingFFListRecIndex = (Dem_u16_SmpTSFFRecClassIndexType)0U; samplingFFListRecIndex < tsffSamplingFFClassConfigureNum; samplingFFListRecIndex++ )    /* [GUD:for]samplingFFListRecIndex */
    {
        demEndIndex = Dem_SamplingFreezeFrameTable[samplingFFListRecIndex].DemEndIndex;                                     /* [GUD]samplingFFListRecIndex */
        Dem_Data_InitSmplFFListRecord( demEndIndex, &Dem_SamplingFreezeFrameListRecordList[samplingFFListRecIndex] );       /* [GUD]samplingFFListRecIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_InitSmplFFListRecord                            */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EndIndex :                                          */
/*               |                                                          */
/*               | [out] SamplingFreezeFrameListRecordPtr :                 */
/*               |                 &Dem_SamplingFreezeFrameListRecordList[] */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_InitSmplFFListRecord
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) EndIndex,
    P2VAR( Dem_SamplingFreezeFrameListType, AUTOMATIC, DEM_VAR_NO_INIT ) SamplingFreezeFrameListRecordPtr
)
{
    SamplingFreezeFrameListRecordPtr->CurrentIndex = EndIndex;

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_InitAllTSFFListRecordList                       */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_InitAllTSFFListRecordList
( void )
{
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) samplingRecMemIndex;
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) samplingFFRecordMemoryNum;

    samplingFFRecordMemoryNum = Dem_SamplingFFRecordMemoryNum;

    for( samplingRecMemIndex = (Dem_u16_SmpRecMemIndexType)0U; samplingRecMemIndex < samplingFFRecordMemoryNum; samplingRecMemIndex++ ) /* [GUD:for]samplingRecMemIndex */
    {
        Dem_Data_InitTSFFListRecordList( samplingRecMemIndex );                                                                         /* [GUD]samplingRecMemIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_InitTSFFListRecordList                          */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] SamplingRecMemIndex :                               */
/*               |      The index for sampling freeze frame memory table.   */
/*               |                                                          */
/* Return Value  | void                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_InitTSFFListRecordList
(
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) SamplingRecMemIndex
)
{
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) samplingFreezeFrameMemoryRef;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) samplingFFBindIndex;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecordClassConfigureNum;
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) samplingFreezeFrameRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecStartIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecEndIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;

    tsFFRecordClassConfigureNum = Dem_TSFFRecordClassConfigureNum;

    for( samplingFFBindIndex = (Dem_u16_TSFFRecClassIndexType)0U; samplingFFBindIndex < tsFFRecordClassConfigureNum; samplingFFBindIndex++ )    /* [GUD:for]samplingFFBindIndex */
    {
        samplingFreezeFrameRef = Dem_SamplingFreezeFrameBindTable[samplingFFBindIndex].DemSamplingFreezeFrameRef;                               /* [GUD]samplingFFBindIndex *//* [GUD:CFG:IF_GUARDED: samplingFFBindIndex ]samplingFreezeFrameRef */
        samplingFreezeFrameMemoryRef = Dem_SamplingFreezeFrameTable[samplingFreezeFrameRef].DemSamplingFreezeFrameMemoryRef;                    /* [GUD]samplingFreezeFrameRef */
        if( samplingFreezeFrameMemoryRef == SamplingRecMemIndex )
        {
            tsFFListRecStartIndex = Dem_TimeSeriesFreezeFrameBindTable[samplingFFBindIndex].DemStartIndex;                                      /* [GUD]samplingFFBindIndex */
            tsFFListRecEndIndex = Dem_TimeSeriesFreezeFrameBindTable[samplingFFBindIndex].DemEndIndex;                                          /* [GUD]samplingFFBindIndex */
            for( tsFFListRecIndex = tsFFListRecStartIndex; tsFFListRecIndex <= tsFFListRecEndIndex; tsFFListRecIndex++)                         /* [GUD:for]tsFFListRecIndex */
            {
                Dem_Data_InitTSFFListRecord( &Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecIndex] );                                      /* [GUD]tsFFListRecIndex */
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_InitTSFFListRecord                              */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [out] TimeSeriesFreezeFrameListRecordPtr :               */
/*               |               &Dem_TimeSeriesFreezeFrameListRecordList[] */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_InitTSFFListRecord
(
    P2VAR( Dem_TimeSeriesFreezeFrameListType, AUTOMATIC, DEM_VAR_NO_INIT ) TimeSeriesFreezeFrameListRecordPtr
)
{
    TimeSeriesFreezeFrameListRecordPtr->FaultIndex = DEM_FAULTINDEX_INITIAL;

    TimeSeriesFreezeFrameListRecordPtr->NumberOfStoredAfterTriggeredRecord = 0U;

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_InitAllTSFFCtrlRecordList                       */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_InitAllTSFFCtrlRecordList
( void )
{
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) samplingRecMemIndex;
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) samplingFFRecordMemoryNum;

    samplingFFRecordMemoryNum = Dem_SamplingFFRecordMemoryNum;

    for( samplingRecMemIndex = (Dem_u16_SmpRecMemIndexType)0U; samplingRecMemIndex < samplingFFRecordMemoryNum; samplingRecMemIndex++ ) /* [GUD:for]samplingRecMemIndex */
    {
        Dem_Data_InitTSFFCtrlRecordList( samplingRecMemIndex );                                                                         /* [GUD]samplingRecMemIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_InitTSFFCtrlRecordList                          */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] SamplingRecMemIndex :                               */
/*               |      The index for sampling freeze frame memory table.   */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_InitTSFFCtrlRecordList
(
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) SamplingRecMemIndex
)
{
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) samplingFreezeFrameMemoryRef;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) samplingFFBindIndex;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecordClassConfigureNum;
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) samplingFreezeFrameRef;

    tsFFRecordClassConfigureNum = Dem_TSFFRecordClassConfigureNum;

    for( samplingFFBindIndex = (Dem_u16_TSFFRecClassIndexType)0U; samplingFFBindIndex < tsFFRecordClassConfigureNum; samplingFFBindIndex++ )    /* [GUD:for]samplingFFBindIndex */
    {
        samplingFreezeFrameRef = Dem_SamplingFreezeFrameBindTable[samplingFFBindIndex].DemSamplingFreezeFrameRef;                               /* [GUD]samplingFFBindIndex */
        samplingFreezeFrameMemoryRef = Dem_SamplingFreezeFrameTable[samplingFreezeFrameRef].DemSamplingFreezeFrameMemoryRef;                    /* [GUD]samplingFFBindIndex */
        if( samplingFreezeFrameMemoryRef == SamplingRecMemIndex )
        {
            Dem_Data_InitTSFFCtrlRecord( samplingFFBindIndex );                                                                                 /* [GUD]samplingFFBindIndex */
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_InitTSFFCtrlRecord                              */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] TimeSeriesFreezeFrameBindIndex :                    */
/*               |      The index for time-series freeze frame bind table.  */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_InitTSFFCtrlRecord
(
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameBindIndex          /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) tsFFMaxNumOfDTCForTSFF;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) indexOfCurrentIndexArray;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) currentIndexLimit;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) stepIndex;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsffClassRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecStartIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecEndIndex;

    tsFFMaxNumOfDTCForTSFF = Dem_TSFFMaxNumOfDTCForTSFF;
    tsffClassRef = Dem_TSFFRecordClassTable[TimeSeriesFreezeFrameBindIndex].DemTimeSeriesFreezeFrameClassRef;           /* [GUDCHK:CALLER]TimeSeriesFreezeFrameBindIndex *//* [GUD:CFG:IF_GUARDED: TimeSeriesFreezeFrameBindIndex ]tsffClassRef */
    stepIndex = Dem_TSFFClassTable[tsffClassRef].DemNumberOfTimeSeriesFreezeFramePerDTC;                                /* [GUDCHK:CALLER]TimeSeriesFreezeFrameBindIndex */
    currentIndexLimit = Dem_TSFFClassTable[tsffClassRef].DemNumberOfDTCForTimeSeriesFreezeFrame;                        /* [GUDCHK:CALLER]TimeSeriesFreezeFrameBindIndex */
    tsFFListRecStartIndex = Dem_TimeSeriesFreezeFrameBindTable[TimeSeriesFreezeFrameBindIndex].DemStartIndex;           /* [GUDCHK:CALLER]TimeSeriesFreezeFrameBindIndex */

    for( indexOfCurrentIndexArray = (Dem_u08_NumOfTSFFType)0U; indexOfCurrentIndexArray < tsFFMaxNumOfDTCForTSFF; indexOfCurrentIndexArray++ )  /* [GUD:for]indexOfCurrentIndexArray */
    {
        if( indexOfCurrentIndexArray < currentIndexLimit )
        {
            tsFFListRecStartIndex = tsFFListRecStartIndex + (Dem_u16_TSFFListIndexType)( (Dem_u16_TSFFListIndexType)stepIndex * (Dem_u16_TSFFListIndexType)indexOfCurrentIndexArray );
            tsFFListRecEndIndex = ( tsFFListRecStartIndex + (Dem_u16_TSFFListIndexType)stepIndex ) - (Dem_u16_TSFFListIndexType)1U;
            Dem_TimeSeriesFreezeFrameCtrlRecordList[TimeSeriesFreezeFrameBindIndex].CurrentIndex[indexOfCurrentIndexArray] = tsFFListRecEndIndex;   /* [GUDCHK:CALLER]TimeSeriesFreezeFrameBindIndex *//* [GUD]indexOfCurrentIndexArray */
        }
        else
        {
            /* if unused area, set invalid data. */
            Dem_TimeSeriesFreezeFrameCtrlRecordList[TimeSeriesFreezeFrameBindIndex].CurrentIndex[indexOfCurrentIndexArray] = DEM_TSFFLISTINDEX_INVALID; /* [GUDCHK:CALLER]TimeSeriesFreezeFrameBindIndex */
        }
    }

    Dem_TimeSeriesFreezeFrameCtrlRecordList[TimeSeriesFreezeFrameBindIndex].VacantTimeSeriesFreezeFrameListRecordRef = Dem_TimeSeriesFreezeFrameBindTable[TimeSeriesFreezeFrameBindIndex].DemStartIndex;    /* [GUDCHK:CALLER]TimeSeriesFreezeFrameBindIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_SaveTSFFListRecordList                          */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [out] TimeSeriesFreezeFrameListRecordListPtr :           */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SaveTSFFListRecordList
(
    P2VAR( Dem_TimeSeriesFreezeFrameListType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameListRecordListPtr
)
{
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;

    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;

    for( tsFFListRecIndex = ( Dem_u16_TSFFListIndexType )0U; tsFFListRecIndex < tsffTotalDTCNum; tsFFListRecIndex++ )   /* [GUD:for]tsFFListRecIndex */
    {
        TimeSeriesFreezeFrameListRecordListPtr[tsFFListRecIndex].FaultIndex = Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecIndex].FaultIndex;                                                 /* [GUD]tsFFListRecIndex *//* [ARYCHK] DEM_TSFF_TOTAL_DTC_NUM / 1 / tsFFListRecIndex */
        TimeSeriesFreezeFrameListRecordListPtr[tsFFListRecIndex].NumberOfStoredAfterTriggeredRecord = Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecIndex].NumberOfStoredAfterTriggeredRecord; /* [GUD]tsFFListRecIndex *//* [ARYCHK] DEM_TSFF_TOTAL_DTC_NUM / 1 / tsFFListRecIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_UpdateNumberOfStoredAfterTriggeredRecord        */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] FaultIndex :                                        */
/*               | [in] TSFFListRecordIndex :                               */
/*               | [in] TimeSeriesFreezeFrameBindTableRef :                 */
/*               | [in] TimeSeriesFreezeFrameListRecordListPtr :            */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_UpdateNumberOfStoredAfterTriggeredRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListRecordIndex,
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameBindTableRef,
    P2CONST( Dem_TimeSeriesFreezeFrameListType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameListRecordListPtr
)
{
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsffClassRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecStoreLimit;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecStoreIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecSavedIndex;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsffRecordClassConfigureNum;

    tsffRecordClassConfigureNum = Dem_TSFFRecordClassConfigureNum;

    if( TimeSeriesFreezeFrameBindTableRef < tsffRecordClassConfigureNum )   /* [GUD:if]TimeSeriesFreezeFrameBindTableRef */
    {
        tsffClassRef = Dem_TSFFRecordClassTable[TimeSeriesFreezeFrameBindTableRef].DemTimeSeriesFreezeFrameClassRef;                    /* [GUD]TimeSeriesFreezeFrameBindTableRef *//* [GUD:CFG:IF_GUARDED: TimeSeriesFreezeFrameBindTableRef ]tsffClassRef */
        tsFFListRecStoreLimit = TSFFListRecordIndex + Dem_TSFFClassTable[tsffClassRef].DemNumberOfTimeSeriesFreezeFramePerDTC;          /* [GUD]tsffClassRef */

        for( tsFFListRecStoreIndex = TSFFListRecordIndex; tsFFListRecStoreIndex < tsFFListRecStoreLimit; tsFFListRecStoreIndex++ )      /* [GUD:for]tsFFListRecStoreIndex */
        {
            Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecStoreIndex].NumberOfStoredAfterTriggeredRecord = DEM_TSFFLIST_AFTTRGRECNUM_INVALID;  /* [GUD]tsFFListRecStoreIndex */
        }

        tsFFListRecStoreIndex = TSFFListRecordIndex;

        for( tsFFListRecSavedIndex = Dem_TimeSeriesFreezeFrameBindTable[TimeSeriesFreezeFrameBindTableRef].DemStartIndex; tsFFListRecSavedIndex <= Dem_TimeSeriesFreezeFrameBindTable[TimeSeriesFreezeFrameBindTableRef].DemEndIndex; tsFFListRecSavedIndex++ ) /* [GUD:for]tsFFListRecSavedIndex */
        {
            if( TimeSeriesFreezeFrameListRecordListPtr[tsFFListRecSavedIndex].FaultIndex == FaultIndex )        /* [GUD]tsFFListRecSavedIndex *//* [ARYCHK] DEM_TSFF_TOTAL_DTC_NUM / 1 / tsFFListRecSavedIndex */
            {
                Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecStoreIndex].FaultIndex = FaultIndex;         /* [GUD]tsFFListRecStoreIndex */
                Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecStoreIndex].NumberOfStoredAfterTriggeredRecord = TimeSeriesFreezeFrameListRecordListPtr[tsFFListRecSavedIndex].NumberOfStoredAfterTriggeredRecord;   /* [GUD]tsFFListRecStoreIndex *//* [GUD]tsFFListRecSavedIndex *//* [ARYCHK] DEM_TSFF_TOTAL_DTC_NUM / 1 / tsFFListRecSavedIndex */

                tsFFListRecStoreIndex = tsFFListRecStoreIndex + (Dem_u16_TSFFListIndexType)1U;
                if( tsFFListRecStoreIndex >= tsFFListRecStoreLimit )                                            /* [GUD:if]tsFFListRecStoreIndex */
                {
                    break;
                }
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_UpdateVacantTSFFListRecordRef                   */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] TimeSeriesFreezeFrameBindTableRef :                 */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_UpdateVacantTSFFListRecordRef
(
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameBindTableRef
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) stepIndex;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) loopLimit;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) loopCount;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsffClassRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsffRecordClassConfigureNum;

    retVal = DEM_IRT_OK;
    tsffRecordClassConfigureNum = Dem_TSFFRecordClassConfigureNum;

    if( TimeSeriesFreezeFrameBindTableRef >= tsffRecordClassConfigureNum )      /* [GUD:if]TimeSeriesFreezeFrameBindTableRef */
    {
        retVal = DEM_IRT_NG;
    }
    else
    {
        tsffClassRef = Dem_TSFFRecordClassTable[TimeSeriesFreezeFrameBindTableRef].DemTimeSeriesFreezeFrameClassRef;    /* [GUD]TimeSeriesFreezeFrameBindTableRef *//* [GUD:CFG:IF_GUARDED: TimeSeriesFreezeFrameBindTableRef ]tsffClassRef */
        stepIndex = Dem_TSFFClassTable[tsffClassRef].DemNumberOfTimeSeriesFreezeFramePerDTC;                            /* [GUD]tsffClassRef */
        loopLimit = Dem_TSFFClassTable[tsffClassRef].DemNumberOfDTCForTimeSeriesFreezeFrame;                            /* [GUD]tsffClassRef */

        for( loopCount = (Dem_u08_NumOfTSFFType)0U; loopCount < loopLimit; loopCount++ )                                /* [GUD:for]loopCount */
        {
            tsFFListRecIndex = ( (Dem_u16_TSFFListIndexType)stepIndex * (Dem_u16_TSFFListIndexType)loopCount ) + Dem_TimeSeriesFreezeFrameBindTable[TimeSeriesFreezeFrameBindTableRef].DemStartIndex;   /* [GUD]TimeSeriesFreezeFrameBindTableRef *//* [GUD:CFG:IF_GUARDED: TimeSeriesFreezeFrameBindTableRef ]tsFFListRecIndex */

            if( Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecIndex].FaultIndex == DEM_FAULTINDEX_INITIAL )        /* [GUD]tsFFListRecIndex */
            {
                break;
            }
            else
            {
                /* No process */
            }
        }

        if( loopCount < loopLimit )
        {
            Dem_TimeSeriesFreezeFrameCtrlRecordList[TimeSeriesFreezeFrameBindTableRef].VacantTimeSeriesFreezeFrameListRecordRef = tsFFListRecIndex;                     /* [GUD]TimeSeriesFreezeFrameBindTableRef */
        }
        else
        {
            Dem_TimeSeriesFreezeFrameCtrlRecordList[TimeSeriesFreezeFrameBindTableRef].VacantTimeSeriesFreezeFrameListRecordRef = DEM_INVALID_VACANT_TSFFLIST_INDEX;    /* [GUD]TimeSeriesFreezeFrameBindTableRef */
        }
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_TSFF_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
