/* Dem_FFD_FilRecord_c(v5-6-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/FFD_FilRecord/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_FFD.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../cfg/Dem_Data_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_DTC_FILRECORD_SEARCHEVENTCOUNT_INITIAL  ((Dem_u16_FilFFDSearchNumType)0U)
#define DEM_DTC_LOOP_FINDFILREC_MAX                 ((Dem_u16_FilFFDSearchNumType)0xFFFFU)

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

static FUNC( void, DEM_CODE ) Dem_FFD_ClearFilteredRecordSearchInfo
( void );

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFD_CheckSearchFilteredRecordContinuation
( void );

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFD_ExecuteSearchFilteredRecord
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_FilteredRecordSearchInfoType, DEM_VAR_NO_INIT )    Dem_FilteredRecordSearchInfo;
static VAR( Dem_DTCFormatType, DEM_VAR_NO_INIT )   Dem_FreezeFrameRecordFilter;
static VAR( Dem_u16_FilFFDSearchNumType, DEM_VAR_NO_INIT )  Dem_FilteredEventSearchCnt;


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_FFD_SetFreezeFrameRecordFilter                       */
/* Description   | Sets a freeze frame record filter.                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCFormat :                                         */
/*               |        Defines the output-format of the requested DTC v- */
/*               |        alues for the sub-sequent API calls.              */
/*               | [out] NumberOfFilteredRecordsPtr :                       */
/*               |        Number of freeze frame records currently stored - */
/*               |        in the event memory.                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : OK.                                  */
/*               |        DEM_IRT_NG : wrong filter.                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFD_SetFreezeFrameRecordFilter
(
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) NumberOfFilteredRecordsPtr

)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Checks DTCFormat type */
    if( DTCFormat == DEM_DTC_FORMAT_UDS )
    {
        /* Gets the number of FreezeFrame records currently stored in the event memory */
        Dem_Data_GetNumberOfFilteredRecords( NumberOfFilteredRecordsPtr );

        /* Retention of the FreezeFrame record filter */
        Dem_FreezeFrameRecordFilter = DTCFormat;
        Dem_FFD_ClearFilteredRecordSearchInfo();

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        Dem_Misfire_PrepareFilteredRecord();
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )           */

        Dem_FilteredEventSearchCnt = DEM_DTC_FILRECORD_SEARCHEVENTCOUNT_INITIAL;

        retVal  =   DEM_IRT_OK;
    }
    else
    {
        retVal  =   DEM_IRT_NG;     /*  DEM_WRONG_FILTER    */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_FFD_GetNextFilteredRecord                            */
/* Description   | Gets the next freeze frame record number and its associ- */
/*               | ated DTC stored in the event memory.The interface has a- */
/*               | n asynchronous behavior, because NvRAM access might be - */
/*               | required.                                                */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCValuePtr :                                      */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function.If the retur- */
/*               |        n value of the function is other than DEM_FILTER- */
/*               |        ED_OK this parameter does not contain valid data. */
/*               | [out] RecordNumberPtr :                                  */
/*               |        Freeze frame record number of the reported DTC (- */
/*               |        relative addressing).If the return value of the - */
/*               |        function is other than DEM_FILTERED_OK this para- */
/*               |        meter does not contain valid data.                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/*               |        DEM_IRT_PENDING : The requested value is calcula- */
/*               |        ted asynchronously and currently not available.T- */
/*               |        he caller can retry later.Only used by asynchron- */
/*               |        ous interfaces.                                   */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFD_GetNextFilteredRecord
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
)
{
    VAR( boolean, AUTOMATIC ) loopEnd;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultCheckRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_FilFFDSearchNumType, AUTOMATIC ) count;
    VAR( Dem_u16_FilFFDSearchNumType, AUTOMATIC ) searchLoopNumByCycle;
    VAR( Dem_u16_FilFFDSearchNumType, AUTOMATIC ) loopMaxNum;


    retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    loopEnd = (boolean)FALSE;
    searchLoopNumByCycle = Dem_FilFFDSearchLoopNumByCycle;

    loopMaxNum = DEM_DTC_LOOP_FINDFILREC_MAX;

    for( count = (Dem_u16_FilFFDSearchNumType)0U; count < loopMaxNum; count++ )
    {
        /* return pending, if search count exceed configuration value*/
        if( Dem_FilteredEventSearchCnt < searchLoopNumByCycle )
        {
            /* Search processing continuation judgment */
            resultCheckRec = Dem_FFD_CheckSearchFilteredRecordContinuation();

            if( resultCheckRec == DEM_IRT_OK )
            {
                /* Execute the search of the filtered record */
                resultGetRec = Dem_FFD_ExecuteSearchFilteredRecord( DTCValuePtr,RecordNumberPtr );

                if( resultGetRec == DEM_IRT_OK )
                {
                    loopEnd = (boolean)TRUE;
                    retVal = resultGetRec;
                }
            }
            else
            {
                loopEnd = (boolean)TRUE;
            }
            Dem_FilteredEventSearchCnt++;
        }
        else
        {
            /* reset search counter for return pending */
            Dem_FilteredEventSearchCnt = DEM_DTC_FILRECORD_SEARCHEVENTCOUNT_INITIAL;
            retVal = DEM_IRT_PENDING;
            loopEnd = (boolean)TRUE;
        }

        if( loopEnd == (boolean)TRUE )
        {
            break;
        }
    }

    if( retVal != DEM_IRT_OK )
    {
        /* reading filtered record information failed */
        (*DTCValuePtr)     = DEM_DTC_VALUE_MIN;
        (*RecordNumberPtr) = DEM_FFD_RECORD_NUMBER_MIN;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_FFD_InitFiltererdRecordSearchInfo                    */
/* Description   | Initialize the search information of filtered records.   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_FFD_ClearFilteredRecordSearchInfo
( void )
{
    /* initialize of Dem_FilteredRecordSearchInfo */
    Dem_FilteredRecordSearchInfo.OrderOfFaultIndex      = (Dem_u08_OrderIndexType)0U;
    Dem_FilteredRecordSearchInfo.FaultIndex             = DEM_FFD_FAULT_INDEX_MIN;
    Dem_FilteredRecordSearchInfo.ObdRecordNumberIndex   = DEM_FFD_RECORD_INDEX_MIN;
    Dem_FilteredRecordSearchInfo.RecordNumberIndex      = DEM_FFD_RECORD_INDEX_MIN;
    Dem_FilteredRecordSearchInfo.TSFFListIndex          = (Dem_u08_TSFFListPerDTCIndexType)0U;
    Dem_FilteredRecordSearchInfo.TSFFRecIndex           = Dem_TSFFTotalTimeseriesFFRecordNum;
    Dem_FilteredRecordSearchInfo.GetFaultIndexFlag      = (boolean)TRUE;
    Dem_FilteredRecordSearchInfo.FFRecNumStoredIndex    = (Dem_u16_FFRecNumStoredIndexType)0U;
    Dem_FilteredRecordSearchInfo.MisfireCylinderNum     = DEM_MISFIRE_CYL_NUM_INVALID;
#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) /* [FuncSw] */
    Dem_CmbEvt_StartOfCheckOutputFilteredDTC();
#endif  /*  ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_ON ) */
    return;
}

/****************************************************************************/
/* Function Name | Dem_FFD_CheckSearchFilteredRecordContinuation            */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFD_CheckSearchFilteredRecordContinuation
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFaultIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) /* [FuncSw] */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
#endif /* DEM_MISFIRE_EVENT_CONFIGURED -STD_ON- */

    retVal = DEM_IRT_NG;

    /* Check whether it is necessary to get FaultIndex. */
    if( Dem_FilteredRecordSearchInfo.GetFaultIndexFlag == (boolean)TRUE )
    {
        /* Get FaultIndex of the occrrence order. */
        faultIndex = (Dem_u08_FaultIndexType)0U;
        retGetFaultIndex = Dem_Data_GetFaultIndexByOccurrenceOrder( Dem_FilteredRecordSearchInfo.OrderOfFaultIndex, &faultIndex );
        Dem_FilteredRecordSearchInfo.FaultIndex = faultIndex;

        if( retGetFaultIndex == DEM_IRT_OK )
        {
            /* There is FaultIndex. */
            /* The search processing continues. */
            Dem_FilteredRecordSearchInfo.OrderOfFaultIndex      = Dem_FilteredRecordSearchInfo.OrderOfFaultIndex + (Dem_u08_OrderIndexType)1U;
            Dem_FilteredRecordSearchInfo.ObdRecordNumberIndex   = DEM_FFD_RECORD_INDEX_MIN;
            Dem_FilteredRecordSearchInfo.RecordNumberIndex      = DEM_FFD_RECORD_INDEX_MIN;
            Dem_FilteredRecordSearchInfo.TSFFListIndex          = (Dem_u08_TSFFListPerDTCIndexType)0x00U;
            Dem_FilteredRecordSearchInfo.TSFFRecIndex           = Dem_TSFFTotalTimeseriesFFRecordNum;
            Dem_FilteredRecordSearchInfo.GetFaultIndexFlag      = (boolean)FALSE;
            Dem_FilteredRecordSearchInfo.FFRecNumStoredIndex    = (Dem_u16_FFRecNumStoredIndexType)0U;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) /* [FuncSw] */
            resultOfGetEventStrgIndex = Dem_DataMngC_GetFR_EventStrgIndex( faultIndex, &eventStrgIndex );
            if ( resultOfGetEventStrgIndex == DEM_IRT_OK )
            {
                misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );
                if ( misfireEventKind == (boolean)TRUE )
                {
                    Dem_FilteredRecordSearchInfo.MisfireCylinderNum = (Dem_MisfireCylinderNumberType)0U;
                }
                else
                {
                    Dem_FilteredRecordSearchInfo.MisfireCylinderNum = DEM_MISFIRE_CYL_NUM_INVALID;
                }
            }
            else
#endif /* DEM_MISFIRE_EVENT_CONFIGURED -STD_ON- */
            {
                Dem_FilteredRecordSearchInfo.MisfireCylinderNum = DEM_MISFIRE_CYL_NUM_INVALID;
            }

            retVal = DEM_IRT_OK;
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* It is not yet necessary to get FaultIndex. */
        /* The search processing continues. */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_FFD_ExecuteSearchFilteredRecord                      */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [out] DTCValuePtr :                                      */
/*               |                                                          */
/*               | [out] RecordNumberPtr :                                  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_FFD_ExecuteSearchFilteredRecord
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) RecordNumberPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetRec;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) recNum;
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;


    dtcVal  = DEM_DTC_VALUE_MIN;
    recNum  = DEM_FFD_RECORD_NUMBER_MIN;

    /* Gets the filtered record. */
    resultGetRec = Dem_Data_GetFilteredRecord( Dem_FreezeFrameRecordFilter, &Dem_FilteredRecordSearchInfo, &dtcVal, &recNum );

    if( resultGetRec == DEM_IRT_OK )
    {
        *DTCValuePtr = dtcVal;
        *RecordNumberPtr = recNum;
         retVal = DEM_IRT_OK;
    }
    else if( resultGetRec == DEM_IRT_NODATAAVAILABLE )
    {
        /* There is not a filtered record corresponding to FaultIndex. */
        Dem_FilteredRecordSearchInfo.GetFaultIndexFlag = (boolean)TRUE;
        retVal = DEM_IRT_NODATAAVAILABLE;

    }
    else if( resultGetRec == DEM_IRT_PENDING )
    {
         retVal = DEM_IRT_PENDING;
    }
    else
    {
        /* An exceptional error occurred. */
        Dem_FilteredRecordSearchInfo.GetFaultIndexFlag = (boolean)TRUE;
        retVal = DEM_IRT_NG;
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
