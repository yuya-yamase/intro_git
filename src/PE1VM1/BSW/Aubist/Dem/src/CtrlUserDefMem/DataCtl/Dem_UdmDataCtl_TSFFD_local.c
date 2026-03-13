/* Dem_UdmDataCtl_TSFFD_local_c(v5-5-0)                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_TSFFD_local/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataCtl_SamplingFFDAccess.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_Rc_UdmMng_rc.h"
#include "../../../inc/Dem_Utl.h"
#include "Dem_UdmDataCtl_local.h"
#include "Dem_UdmDataCtl_TSFFD_local.h"
#include "Dem_UdmDataCtl_EventEntry_local.h"

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

static FUNC( void, DEM_CODE ) Dem_UdmData_GetTSFFListStartAndEndIndex
(
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRef,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) CurrentIndexPos,
    P2VAR( Dem_u16_TSFFListIndexType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameListStartIndexPtr,
    P2VAR( Dem_u16_TSFFListIndexType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameListEndIndexPtr
);

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

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
/* Function Name | Dem_UdmData_ClearTSFFRecord                              */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        User defined memory talbe Index.                  */
/*               | [in] TimeSeriesFreezeFrameListRecordIndex :              */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_ClearTSFFRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListRecordIndex
)
{
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultRecordNum;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) recordStatus;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;

    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;
    udmFaultRecordNum = Dem_UdmFaultMngC_GetFaultRecordNum( UdmGroupKindIndex );

    if( TimeSeriesFreezeFrameListRecordIndex < tsffTotalDTCNum )        /* [GUD:if]TimeSeriesFreezeFrameListRecordIndex */
    {
        if( Dem_TimeSeriesFreezeFrameListRecordList[TimeSeriesFreezeFrameListRecordIndex].FaultIndex < udmFaultRecordNum )      /* [GUD]TimeSeriesFreezeFrameListRecordIndex */
        {
            for( tsFFRecIndex = Dem_TimeSeriesFreezeFrameTable[TimeSeriesFreezeFrameListRecordIndex].DemStartIndex; tsFFRecIndex <= Dem_TimeSeriesFreezeFrameTable[TimeSeriesFreezeFrameListRecordIndex].DemEndIndex; tsFFRecIndex++ )      /* [GUD]TimeSeriesFreezeFrameListRecordIndex */
            {
                recordStatus = Dem_UdmTSFFDMng_GetRecordStatus( UdmGroupKindIndex, tsFFRecIndex );

                if( recordStatus == DEM_FFD_STORED )
                {
                    (void)Dem_UdmTSFFDMng_ClearTimeSeriesFreezeFrameRecord( UdmGroupKindIndex, tsFFRecIndex );   /* no return check required */
                }
            }

            /* Initializing of the time-series freeze frame list record is executed, */
            /* after sets request for time-series freeze frame list record updating. */
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_InitCurrentIndexOfTSFFListRecord             */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] TimeSeriesFreezeFrameRecordClassRef :               */
/*               | [in] TimeSeriesFreezeFrameListIndex :                    */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_InitCurrentIndexOfTSFFListRecord
(
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRef,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetCurrentIndexPos;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) currentIndexPos;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecStartIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecEndIndex;

    currentIndexPos = DEM_NUMOFTSFF_INVALID;

    resultOfGetCurrentIndexPos = Dem_UdmData_GetCurrentIndexPosOfTSFFListRecord( TimeSeriesFreezeFrameRecordClassRef, TimeSeriesFreezeFrameListIndex, &currentIndexPos );   /* [GUD:RET:DEM_IRT_OK]TimeSeriesFreezeFrameRecordClassRef *//* [GUD:RET:DEM_IRT_OK]currentIndexPos */
    if( resultOfGetCurrentIndexPos == DEM_IRT_OK )
    {
        Dem_UdmData_GetTSFFListStartAndEndIndex( TimeSeriesFreezeFrameRecordClassRef, currentIndexPos, &tsFFListRecStartIndex, &tsFFListRecEndIndex );  /* [GUD]TimeSeriesFreezeFrameRecordClassRef *//* [GUD]currentIndexPos */

        Dem_TimeSeriesFreezeFrameCtrlRecordList[TimeSeriesFreezeFrameRecordClassRef].CurrentIndex[currentIndexPos] = tsFFListRecEndIndex;               /* [GUD]TimeSeriesFreezeFrameRecordClassRef *//* [GUD]currentIndexPos */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_UpdateCurrentIndexOfTSFFListRecord           */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] TimeSeriesFreezeFrameRecordClassRef :               */
/*               | [in] TimeSeriesFreezeFrameListIndex :                    */
/*               |                                                          */
/* Return Value  | Dem_u16_TSFFListIndexType                                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_TSFFListIndexType, DEM_CODE ) Dem_UdmData_UpdateCurrentIndexOfTSFFListRecord
(
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRef,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetCurrentIndexPos;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) currentIndexPos;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecStartIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecEndIndex;

    currentIndexPos = DEM_NUMOFTSFF_INVALID;
    tsFFListRecIndex = DEM_TSFFLISTINDEX_INVALID;

    resultOfGetCurrentIndexPos = Dem_UdmData_GetCurrentIndexPosOfTSFFListRecord( TimeSeriesFreezeFrameRecordClassRef, TimeSeriesFreezeFrameListIndex, &currentIndexPos );   /* [GUD:RET:DEM_IRT_OK]TimeSeriesFreezeFrameRecordClassRef *//* [GUD:RET:DEM_IRT_OK]currentIndexPos */
    if( resultOfGetCurrentIndexPos == DEM_IRT_OK )
    {
        Dem_UdmData_GetTSFFListStartAndEndIndex( TimeSeriesFreezeFrameRecordClassRef, currentIndexPos, &tsFFListRecStartIndex, &tsFFListRecEndIndex );  /* [GUD]TimeSeriesFreezeFrameRecordClassRef *//* [GUD]currentIndexPos */

        Dem_TimeSeriesFreezeFrameCtrlRecordList[TimeSeriesFreezeFrameRecordClassRef].CurrentIndex[currentIndexPos] = Dem_TimeSeriesFreezeFrameCtrlRecordList[TimeSeriesFreezeFrameRecordClassRef].CurrentIndex[currentIndexPos] + (Dem_u16_TSFFListIndexType)1U;    /* [GUD]TimeSeriesFreezeFrameRecordClassRef *//* [GUD]currentIndexPos */
        if( Dem_TimeSeriesFreezeFrameCtrlRecordList[TimeSeriesFreezeFrameRecordClassRef].CurrentIndex[currentIndexPos] > tsFFListRecEndIndex )          /* [GUD]TimeSeriesFreezeFrameRecordClassRef *//* [GUD]currentIndexPos */
        {
            Dem_TimeSeriesFreezeFrameCtrlRecordList[TimeSeriesFreezeFrameRecordClassRef].CurrentIndex[currentIndexPos] = tsFFListRecStartIndex;         /* [GUD]TimeSeriesFreezeFrameRecordClassRef *//* [GUD]currentIndexPos */
        }

        tsFFListRecIndex = Dem_TimeSeriesFreezeFrameCtrlRecordList[TimeSeriesFreezeFrameRecordClassRef].CurrentIndex[currentIndexPos];                  /* [GUD]TimeSeriesFreezeFrameRecordClassRef *//* [GUD]currentIndexPos */
    }

    return tsFFListRecIndex;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_GetTSFFListStartAndEndIndex                  */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] TimeSeriesFreezeFrameRecordClassRef :               */
/*               | [in] TimeSeriesFreezeFrameListIndex :                    */
/*               |                                                          */
/* Return Value  | Dem_u16_TSFFListIndexType                                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmData_GetTSFFListStartAndEndIndex
(
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRef,        /* [PRMCHK:CALLER] */
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) CurrentIndexPos,
    P2VAR( Dem_u16_TSFFListIndexType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameListStartIndexPtr,
    P2VAR( Dem_u16_TSFFListIndexType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameListEndIndexPtr
)
{
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) stepIndex;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsffClassRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecStartIndex;

    tsffClassRef = Dem_TSFFRecordClassTable[TimeSeriesFreezeFrameRecordClassRef].DemTimeSeriesFreezeFrameClassRef;  /* [GUDCHK:CALLER]TimeSeriesFreezeFrameRecordClassRef *//* [GUD:CFG:IF_GUARDED:TimeSeriesFreezeFrameRecordClassRef]tsffClassRef */
    stepIndex = Dem_TSFFClassTable[tsffClassRef].DemNumberOfTimeSeriesFreezeFramePerDTC;                            /* [GUDCHK:CALLER]TimeSeriesFreezeFrameRecordClassRef */
    tsFFListRecStartIndex = Dem_TimeSeriesFreezeFrameBindTable[TimeSeriesFreezeFrameRecordClassRef].DemStartIndex + (Dem_u16_TSFFListIndexType)( (Dem_u16_TSFFListIndexType)stepIndex * (Dem_u16_TSFFListIndexType)CurrentIndexPos );/* [GUDCHK:CALLER]TimeSeriesFreezeFrameRecordClassRef */
    (*TimeSeriesFreezeFrameListStartIndexPtr) = tsFFListRecStartIndex;
    (*TimeSeriesFreezeFrameListEndIndexPtr) = ( tsFFListRecStartIndex + (Dem_u16_TSFFListIndexType)stepIndex ) - (Dem_u16_TSFFListIndexType)1U;

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_SetCurrentIndexOfTSFFCtrlRecord              */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |                                                          */
/*               | [in] TimeSeriesFreezeFrameRecordClassRef :               */
/*               |                                                          */
/*               | [in] UdmFaultRecordPtr :                                 */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_SetCurrentIndexOfTSFFCtrlRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRef,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) UdmFaultRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetCurrentIndexPos;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) latestOffsetOfTSFFListIndex;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) currentIndexPos;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) currentIndexOfTSFFSets;

    latestOffsetOfTSFFListIndex = Dem_UdmFFDMng_GetLatestOffsetOfTSFFListIndex( UdmGroupKindIndex, UdmEventIndex, UdmFaultRecordPtr->RecordNumberIndex );
    if( latestOffsetOfTSFFListIndex != DEM_NUMOFTSFF_INVALID )
    {
        currentIndexOfTSFFSets = UdmFaultRecordPtr->TimeSeriesFreezeFrameListIndex +latestOffsetOfTSFFListIndex;

        currentIndexPos = DEM_NUMOFTSFF_INVALID;
        resultOfGetCurrentIndexPos = Dem_UdmData_GetCurrentIndexPosOfTSFFListRecord( TimeSeriesFreezeFrameRecordClassRef, UdmFaultRecordPtr->TimeSeriesFreezeFrameListIndex, &currentIndexPos );    /* [GUD:RET:DEM_IRT_OK]TimeSeriesFreezeFrameRecordClassRef *//* [GUD:RET:DEM_IRT_OK]currentIndexPos */
        if( resultOfGetCurrentIndexPos == DEM_IRT_OK )
        {
            Dem_TimeSeriesFreezeFrameCtrlRecordList[TimeSeriesFreezeFrameRecordClassRef].CurrentIndex[currentIndexPos] = currentIndexOfTSFFSets;    /* [GUD]TimeSeriesFreezeFrameRecordClassRef *//* [GUD]currentIndexPos */
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_GetCurrentIndexPosOfTSFFListRecord           */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] TimeSeriesFreezeFrameRecordClassRef :               */
/*               | [in] TimeSeriesFreezeFrameListIndex :                    */
/*               | [out] CurrentIndexPosPtr :                               */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] TimeSeriesFreezeFrameRecordClassRef */
/* VariableGuard | [GUD:RET:DEM_IRT_OK] CurrentIndexPosPtr                  */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetCurrentIndexPosOfTSFFListRecord
(
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRef,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListIndex,
    P2VAR( Dem_u08_NumOfTSFFType, AUTOMATIC, AUTOMATIC ) CurrentIndexPosPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) stepIndex;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) loopLimit;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) loopCount;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsffClassRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) startTSFFListRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsffRecordClassConfigureNum;

    retVal = DEM_IRT_NG;
    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;
    tsffRecordClassConfigureNum = Dem_TSFFRecordClassConfigureNum;

    if( TimeSeriesFreezeFrameRecordClassRef < tsffRecordClassConfigureNum )         /* [GUD:if]TimeSeriesFreezeFrameRecordClassRef */
    {
        tsffClassRef = Dem_TSFFRecordClassTable[TimeSeriesFreezeFrameRecordClassRef].DemTimeSeriesFreezeFrameClassRef;  /* [GUD]TimeSeriesFreezeFrameRecordClassRef *//* [GUD:CFG:IF_GUARDED:TimeSeriesFreezeFrameRecordClassRef]tsffClassRef */
        stepIndex = Dem_TSFFClassTable[tsffClassRef].DemNumberOfTimeSeriesFreezeFramePerDTC;    /* [GUD]tsffClassRef */
        loopLimit = Dem_TSFFClassTable[tsffClassRef].DemNumberOfDTCForTimeSeriesFreezeFrame;    /* [GUD]tsffClassRef */

        if( TimeSeriesFreezeFrameListIndex < tsffTotalDTCNum )
        {
            startTSFFListRecIndex = TimeSeriesFreezeFrameListIndex;
        }
        else
        {
            /* No time-series freeze frame recorded yet. */
            startTSFFListRecIndex = Dem_TimeSeriesFreezeFrameCtrlRecordList[TimeSeriesFreezeFrameRecordClassRef].VacantTimeSeriesFreezeFrameListRecordRef;  /* [GUD]TimeSeriesFreezeFrameRecordClassRef */
        }

        if( startTSFFListRecIndex < tsffTotalDTCNum )
        {
            for( loopCount = (Dem_u08_NumOfTSFFType)0U; loopCount < loopLimit; loopCount++ )    /* [GUD:for]loopCount */
            {
                tsFFListRecIndex = ( (Dem_u16_TSFFListIndexType)stepIndex * (Dem_u16_TSFFListIndexType)loopCount ) + Dem_TimeSeriesFreezeFrameBindTable[TimeSeriesFreezeFrameRecordClassRef].DemStartIndex; /* [GUD]TimeSeriesFreezeFrameRecordClassRef */
                if( startTSFFListRecIndex == tsFFListRecIndex )
                {
                    (*CurrentIndexPosPtr) = loopCount;      /* [GUD]loopCount */
                    retVal = DEM_IRT_OK;

                    break;
                }
            }
        }
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
