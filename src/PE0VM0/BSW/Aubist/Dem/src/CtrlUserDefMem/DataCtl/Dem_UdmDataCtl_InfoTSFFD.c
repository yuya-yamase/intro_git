/* Dem_UdmDataCtl_InfoTSFFD_c(v5-5-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_InfoTSFFD/CODE                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataCtl_FFDOutputJudge.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_Rc_UdmMng_rc.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"
#include "Dem_UdmDataCtl_InfoTSFFD.h"

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetTSFFDInfoByEventAndRecNum
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) StartingRecordNumberPtr,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameClassRefPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetSavedTSFFRecordNumber
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) *UdmTmpTSFFRecordNumberPPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetTSFFRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) OffsetOfRecordNumber,
    P2CONST( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmTmpTSFFRecordNumberPtr,
    P2VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameRecordPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetTSFFRecordFromTSFFList
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) OffsetOfRecordNumber,
    P2CONST( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmTmpTSFFRecordNumberPtr,
    P2VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameRecordPtr
);

static FUNC( void, DEM_CODE ) Dem_UdmData_SaveTSFFRecordNumberByTSFFListIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) StartingRecordNumber,
    P2VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC, AUTOMATIC ) UdmTmpTSFFRecordNumberIndexPtr
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

VAR( Dem_UdmTmpRecordNumberByDTCType, DEM_VAR_NO_INIT ) Dem_UdmTmpTSFFRecordNumber[DEM_UDM_MAX_NUMBER_TSFF_PER_DTC];

static VAR( Dem_u16_UdmFFDIndexType, DEM_VAR_NO_INIT ) Dem_UdmSearchTSFFStartPositionIndex;
static VAR( Dem_u16_UdmFFDIndexType, DEM_VAR_NO_INIT ) Dem_UdmStoredTSFFCount;
static VAR( Dem_u08_FFRecordNumberType, DEM_VAR_NO_INIT ) Dem_UdmStoredTSFFRecordNumber;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_UdmData_GetFFDataFromTSFF                            */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |                                                          */
/*               | [in] RecordNumber :                                      */
/*               |                                                          */
/*               | [in] OutputResult :                                      */
/*               |                                                          */
/*               | [out] DataPtr :                                          */
/*               |                                                          */
/*               | [in/out] DataSizePtr :                                   */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/*               |        DEM_IRT_WRONG_RECORDNUMBER :                      */
/*               |        DEM_IRT_WRONG_BUFFERSIZE :                        */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetFFDataFromTSFF
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FFDGetInfoType, AUTOMATIC ) FreezeFrameGetInfoType,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DataPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) DataSizePtr
)
{
    VAR( boolean, AUTOMATIC ) retUdmDTCClerTarget;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSFFInfo;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetSavedRecNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSFFRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfEditFFRec;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) startingRecordNumber;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) offsetOfRecordNumber;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameClassPtr;
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) udmTmpTSFFRecordNumberPtr;
    VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC ) tsFFRecord;

    retVal = DEM_IRT_NG;
    eventConfigureNum = Dem_UdmEventConfigureNum;

    if( UdmEventIndex < eventConfigureNum )         /* [GUD:if]UdmEventIndex */
    {
        startingRecordNumber = (Dem_u08_FFRecordNumberType)0U;
        freezeFrameClassRef = DEM_FFCLASSINDEX_INVALID;

        resultOfGetTSFFInfo = Dem_UdmData_GetTSFFDInfoByEventAndRecNum( UdmEventIndex, RecordNumber, &startingRecordNumber, &freezeFrameClassRef ); /* [GUD:RET:DEM_IRT_OK] freezeFrameClassRef */
        if( resultOfGetTSFFInfo == DEM_IRT_OK )
        {
            resultOfGetSavedRecNum = Dem_UdmData_GetSavedTSFFRecordNumber( RecordNumber, &udmTmpTSFFRecordNumberPtr );
            if( resultOfGetSavedRecNum == DEM_IRT_OK )
            {
                offsetOfRecordNumber = RecordNumber - startingRecordNumber;

                resultOfGetTSFFRec = Dem_UdmData_GetTSFFRecord( UdmEventIndex, offsetOfRecordNumber, ( P2CONST( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) )udmTmpTSFFRecordNumberPtr, &tsFFRecord );
                if( resultOfGetTSFFRec == DEM_IRT_OK )
                {
                    retUdmDTCClerTarget = Dem_UdmDTC_JudgeUdmDTCClearTarget( UdmEventIndex );
                    if( retUdmDTCClerTarget == (boolean)FALSE )
                    {
                        freezeFrameClassPtr = &Dem_FreezeFrameClassTable[freezeFrameClassRef];          /* [GUD]freezeFrameClassRef */

                        resultOfEditFFRec = Dem_Data_EditFreezeFrameRecord( RecordNumber, FreezeFrameGetInfoType, tsFFRecord.DataPtr, freezeFrameClassPtr, DataPtr, DataSizePtr );

                        retVal = resultOfEditFFRec;
                    }
                    else
                    {
                        retVal = DEM_IRT_OK;
                        *DataSizePtr = (Dem_u16_FFDStoredIndexType)0U;
                    }
                }
                else
                {
                    retVal = DEM_IRT_OK;
                    *DataSizePtr = (Dem_u16_FFDStoredIndexType)0U;
                }
            }
            else
            {
                retVal = DEM_IRT_OK;
                *DataSizePtr = (Dem_u16_FFDStoredIndexType)0U;
            }
        }
        else
        {
            retVal = DEM_IRT_WRONG_RECORDNUMBER;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_GetTSFFDInfoByEventAndRecNum                 */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |                                                          */
/*               | [in] RecordNumber :                                      */
/*               |                                                          */
/*               | [out] StartingRecordNumberPtr :                          */
/*               |                                                          */
/*               | [out] FreezeFrameClassRefPtr :                           */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_WRONG_RECORDNUMBER :                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] RecordNumber                        */
/* VariableGuard | [GUD:RET:DEM_IRT_OK] FreezeFrameClassRefPtr              */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetTSFFDInfoByEventAndRecNum
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) StartingRecordNumberPtr,
    P2VAR( Dem_u16_FFClassIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameClassRefPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfTSFFRecords;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfTSFFPerDTC;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) countOfTSFFPerDTC;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) startingRecordNumber;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) endingRecordNumber;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) stepNumberToNextStartingRecord;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) eventConfigureNum;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u16_SmpTSFFCPerTSFFIndexType, AUTOMATIC ) samplingFFClassRef;

    retVal = DEM_IRT_WRONG_RECORDNUMBER;
    eventConfigureNum = Dem_UdmEventConfigureNum;

    if( UdmEventIndex < eventConfigureNum )         /* [GUD:if]UdmEventIndex */
    {
        tsFFRecClassRef = Dem_CfgInfoUdm_GetTimeSeriesFreezeFrameRecordClassRef( UdmEventIndex );           /* [GUD]UdmEventIndex */

        if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )                                          /* [GUD:if]tsFFRecClassRef */
        {
            tsFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameClassRef;      /* [GUD]tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED: tsFFRecClassRef ]tsFFClassRef */

            numberOfTSFFRecords = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfBeforeTriggeredRecord + Dem_TSFFClassTable[tsFFClassRef].DemNumberOfAfterTriggeredRecord; /* [GUD]tsFFClassRef */
            numberOfTSFFPerDTC = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfTimeSeriesFreezeFramePerDTC;                                                               /* [GUD]tsFFClassRef */

            startingRecordNumber = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemStartingRecordNumber;                       /* [GUD]tsFFRecClassRef */
            endingRecordNumber = ( startingRecordNumber + numberOfTSFFRecords ) - (Dem_u08_FFRecordNumberType)1U;
            stepNumberToNextStartingRecord = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemStepNumberToNextStartingRecord;   /* [GUD]tsFFRecClassRef */

            samplingFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemSamplingFreezeFrameClassRef;                  /* [GUD]tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED: tsFFRecClassRef ]samplingFFClassRef */

            for( countOfTSFFPerDTC = (Dem_u08_NumOfTSFFType)0U; countOfTSFFPerDTC < numberOfTSFFPerDTC; countOfTSFFPerDTC++ )
            {
                if( RecordNumber >= startingRecordNumber )
                {
                    if( RecordNumber <= endingRecordNumber )
                    {
                        (*StartingRecordNumberPtr) = startingRecordNumber;
                        (*FreezeFrameClassRefPtr) = Dem_TSFFClassTable[tsFFClassRef].Dem_SamplingFreezeFrameClass[samplingFFClassRef].DemFreezeFrameClassRef;   /* [GUD]tsFFClassRef *//* [GUD]samplingFFClassRef */

                        retVal = DEM_IRT_OK;

                        break;
                    }
                }

                startingRecordNumber = startingRecordNumber + stepNumberToNextStartingRecord;
                endingRecordNumber = endingRecordNumber + stepNumberToNextStartingRecord;
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_GetSavedTSFFRecordNumber                     */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordNumber :                                      */
/*               |                                                          */
/*               | [out] UdmTmpTSFFRecordNumberPPtr :                       */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetSavedTSFFRecordNumber
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) *UdmTmpTSFFRecordNumberPPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) cidUdmFreezeFrameRecords;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC )  udmMaxNumberTsffPerDTC;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC )  udmTmpTSFFRecordNumberIndex;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )  udmMaxNumberFFPerDTC;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC )  udmTmpRecordNumberIndex;
    VAR( Dem_u32_UdmOccurrenceOrderType, AUTOMATIC ) occurrenceOrder;

    retVal = DEM_IRT_NG;
    udmMaxNumberTsffPerDTC = Dem_UdmMaxNumberTsffPerDTC;

    for( udmTmpTSFFRecordNumberIndex = (Dem_u16_UdmFFDIndexType)0U; udmTmpTSFFRecordNumberIndex < udmMaxNumberTsffPerDTC; udmTmpTSFFRecordNumberIndex++ )   /* [GUD:for]udmTmpTSFFRecordNumberIndex */
    {
        if( RecordNumber == Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].RecordNumber )                          /* [GUD]udmTmpTSFFRecordNumberIndex */
        {
            occurrenceOrder = Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].OccurrenceOrder;                      /* [GUD]udmTmpTSFFRecordNumberIndex */
            cidUdmFreezeFrameRecords = Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].CidUdmFreezeFrameRecords;    /* [GUD]udmTmpTSFFRecordNumberIndex */
            tsFFListIndex = Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].TimeSeriesFreezeFrameListIndex;         /* [GUD]udmTmpTSFFRecordNumberIndex */

            break;
        }
    }

    if( udmTmpTSFFRecordNumberIndex < udmMaxNumberTsffPerDTC )          /* [GUD:if]udmTmpTSFFRecordNumberIndex */
    {
        udmMaxNumberFFPerDTC = Dem_UdmMaxNumberFFPerDTC;

        for( udmTmpRecordNumberIndex = (Dem_u16_FFRecNumStoredIndexType)0U; udmTmpRecordNumberIndex < udmMaxNumberFFPerDTC; udmTmpRecordNumberIndex++ ) /* [GUD:for]udmTmpRecordNumberIndex */
        {
            if( tsFFListIndex == Dem_UdmTmpRecordNumberByDTC[udmTmpRecordNumberIndex].TimeSeriesFreezeFrameListIndex )      /* [GUD]udmTmpRecordNumberIndex */
            {
                if( occurrenceOrder == Dem_UdmTmpRecordNumberByDTC[udmTmpRecordNumberIndex].OccurrenceOrder )               /* [GUD]udmTmpRecordNumberIndex */
                {
                    if( cidUdmFreezeFrameRecords == Dem_UdmTmpRecordNumberByDTC[udmTmpRecordNumberIndex].CidUdmFreezeFrameRecords )     /* [GUD]udmTmpRecordNumberIndex */
                    {
                        (*UdmTmpTSFFRecordNumberPPtr) = &Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex];                       /* [GUD]udmTmpTSFFRecordNumberIndex */
                        retVal = DEM_IRT_OK;
                    }
                }

                break;
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_GetTSFFRecord                                */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |                                                          */
/*               | [in] OffsetOfRecordNumber :                              */
/*               |                                                          */
/*               | [in] UdmTmpTSFFRecordNumberPtr :                         */
/*               |                                                          */
/*               | [out] TimeSeriesFreezeFrameRecordPtr :                   */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetTSFFRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,              /* [PRMCHK:CALLER] */
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) OffsetOfRecordNumber,
    P2CONST( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmTmpTSFFRecordNumberPtr,
    P2VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSFFRec;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultIndex;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfTSFF;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListIndexLimit;
    VAR( Dem_UdmFaultRecordType, AUTOMATIC ) udmFaultRecord;

    retVal = DEM_IRT_NG;
    resultOfGetFaultRec = DEM_IRT_NG;
    udmFaultIndex = DEM_FAULTINDEX_INITIAL;
    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    /* Get udm group index. */
    udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );               /* [GUDCHK:CALLER]UdmEventIndex *//* [GUD:RET:IF_GUARDED: UdmEventIndex ]udmInfoTableIndex */
    udmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, UdmEventIndex );

    if( udmGroupKindIndex < userDefinedMemoryNum )  /* [GUD:if]udmGroupKindIndex */
    {
#ifndef JGXSTACK
        /* Starts exclusion. */
        Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveEnterFnc();      /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
        Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */

        resultOfGetFaultIndex = Dem_UdmEventMngC_GetER_FaultIndex( UdmEventIndex, &udmFaultIndex );     /* [GUD:RET:DEM_IRT_OK] UdmEventIndex */

        if( resultOfGetFaultIndex == DEM_IRT_OK )
        {
            if( udmFaultIndex != DEM_FAULTINDEX_INITIAL )
            {
                resultOfGetFaultRec = Dem_UdmFaultMngC_GetRecord( udmGroupKindIndex, udmFaultIndex, &udmFaultRecord );      /* [GUD]udmGroupKindIndex */
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            /* No process */
        }

        if( resultOfGetFaultRec == DEM_IRT_OK )
        {
            tsFFRecClassRef = Dem_CfgInfoUdm_GetTimeSeriesFreezeFrameRecordClassRef( UdmEventIndex );       /* [GUD]UdmEventIndex   *//* [GUD:RET:IF_GUARDED: UdmEventIndex ] tsFFRecClassRef */
            tsFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameClassRef;      /* [GUD]tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED: tsFFRecClassRef ] tsFFClassRef */

            if ( udmFaultRecord.TimeSeriesFreezeFrameListIndex != DEM_TSFFLISTINDEX_INVALID )
            {
                numberOfTSFF = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfTimeSeriesFreezeFramePerDTC * Dem_TSFFClassTable[tsFFClassRef].DemNumberOfDTCForTimeSeriesFreezeFrame;   /* [GUD]tsFFClassRef */
                tsFFListIndexLimit = udmFaultRecord.TimeSeriesFreezeFrameListIndex + (Dem_u16_TSFFListIndexType)numberOfTSFF;

                if( UdmTmpTSFFRecordNumberPtr->TimeSeriesFreezeFrameListIndex >= udmFaultRecord.TimeSeriesFreezeFrameListIndex )
                {
                    if( UdmTmpTSFFRecordNumberPtr->TimeSeriesFreezeFrameListIndex < tsFFListIndexLimit )
                    {
                        resultOfGetTSFFRec = Dem_UdmData_GetTSFFRecordFromTSFFList( udmGroupKindIndex, UdmTmpTSFFRecordNumberPtr->TimeSeriesFreezeFrameListIndex, OffsetOfRecordNumber, UdmTmpTSFFRecordNumberPtr, TimeSeriesFreezeFrameRecordPtr );        /* [GUD]udmGroupKindIndex */
                        if( resultOfGetTSFFRec == DEM_IRT_OK )
                        {
                            if( UdmTmpTSFFRecordNumberPtr->OccurrenceOrder == TimeSeriesFreezeFrameRecordPtr->OccurrenceOrder )
                            {
                                if( UdmTmpTSFFRecordNumberPtr->CidUdmFreezeFrameRecords == TimeSeriesFreezeFrameRecordPtr->CidUdmFreezeFrameRecords )
                                {
                                    retVal = DEM_IRT_OK;
                                }
                                else
                                {
                                    /* No process */
                                }
                            }
                            else
                            {
                                /* No process */
                            }
                        }
                        else
                        {
                            /* No process */
                        }
                    }
                }
            }
        }
        else
        {
            /* No process */
        }

#ifndef JGXSTACK
        /* Finishes exclusion. */
        Dem_UdmExcFncTable[udmGroupKindIndex].ExclusiveExitFnc();       /* [GUD]udmGroupKindIndex */
#else   /* JGXSTACK */
        Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_GetTSFFRecordFromTSFFList                    */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |                                                          */
/*               | [in] TimeSeriesFreezeFrameRecordClassRefIndex :          */
/*               |                                                          */
/*               | [in] OffsetOfRecordNumber :                              */
/*               |                                                          */
/*               | [in] UdmTmpTSFFRecordNumberPtr :                         */
/*               |                                                          */
/*               | [out] TimeSeriesFreezeFrameRecordPtr :                   */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetTSFFRecordFromTSFFList
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) OffsetOfRecordNumber,
    P2CONST( Dem_UdmTmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) UdmTmpTSFFRecordNumberPtr,
    P2VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSFFRec;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultRecordNum;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;

    retVal = DEM_IRT_NG;
    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;
    udmFaultRecordNum = Dem_UdmFaultMngC_GetFaultRecordNum( UdmGroupKindIndex );

    if( TimeSeriesFreezeFrameListIndex < tsffTotalDTCNum )                      /* [GUD:if]TimeSeriesFreezeFrameListIndex */
    {
        if( Dem_TimeSeriesFreezeFrameListRecordList[TimeSeriesFreezeFrameListIndex].FaultIndex < udmFaultRecordNum )                    /* [GUD]TimeSeriesFreezeFrameListIndex */
        {
            tsFFRecIndex = ( Dem_TimeSeriesFreezeFrameTable[TimeSeriesFreezeFrameListIndex].DemStartIndex + OffsetOfRecordNumber );     /* [GUD]TimeSeriesFreezeFrameListIndex */
            if( tsFFRecIndex <= Dem_TimeSeriesFreezeFrameTable[TimeSeriesFreezeFrameListIndex].DemEndIndex )                            /* [GUD]TimeSeriesFreezeFrameListIndex */
            {
                if( UdmTmpTSFFRecordNumberPtr->FreezeFrameDataIndex == tsFFRecIndex )
                {
                    resultOfGetTSFFRec = Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecord( UdmGroupKindIndex, tsFFRecIndex, TimeSeriesFreezeFrameRecordPtr );
                    if( resultOfGetTSFFRec == DEM_IRT_OK )
                    {
                        retVal = DEM_IRT_OK;
                    }
                    else
                    {
                        /* No process */
                    }
                }
                else
                {
                    /* No process */
                }
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }


    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_SetNextTSFFRecordNumber                      */
/* Description   | Return the next requested RecordNumber.                  */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordNumber :                                      */
/*               |        The record number corresponding to the specified  */
/*               | [out] NextRecordNumberPtr :                              */
/*               |        This parameter contains a pointer that points to  */
/*               |        the buffer, to which the next required Record nu- */
/*               |        mber will be written.                             */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_SetNextTSFFRecordNumber
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) NextRecordNumberPtr
)
{
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) saveRecNumIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmMaxNumberTsffPerDTC;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) searchStartPositionIndex;

    udmMaxNumberTsffPerDTC = Dem_UdmMaxNumberTsffPerDTC;

    searchStartPositionIndex = Dem_UdmMaxNumberTsffPerDTC;

    *NextRecordNumberPtr = DEM_RECORDNUMBER_NEXT_NONE;

    for( saveRecNumIndex =  Dem_UdmSearchTSFFStartPositionIndex; saveRecNumIndex < udmMaxNumberTsffPerDTC; saveRecNumIndex++ )  /* [GUD:for]saveRecNumIndex */
    {
        if( DEM_FFD_TYPE_INVALID != Dem_UdmTmpTSFFRecordNumber[saveRecNumIndex].FreezeFrameDataType )       /* [GUD]saveRecNumIndex */
        {
            if( Dem_UdmTmpTSFFRecordNumber[saveRecNumIndex].RecordStatus == DEM_FFD_STORED )                /* [GUD]saveRecNumIndex */
            {
                if( RecordNumber < Dem_UdmTmpTSFFRecordNumber[saveRecNumIndex].RecordNumber )               /* [GUD]saveRecNumIndex */
                {
                    *NextRecordNumberPtr = Dem_UdmTmpTSFFRecordNumber[saveRecNumIndex].RecordNumber;        /* [GUD]saveRecNumIndex */
                    searchStartPositionIndex = saveRecNumIndex + (Dem_u16_UdmFFDIndexType)1U;
                    break;
                }
            }
        }
    }

    Dem_UdmSearchTSFFStartPositionIndex = searchStartPositionIndex;

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_GetTSFFStoredRecordNumber                    */
/* Description   | get stored number of TSFFD.                              */
/* Preconditions |                                                          */
/* Parameters    | [out] Dem_u08_FFRecordNumberType                         */
/* Return Value  | Dem_u16_UdmFFDIndexType                                  */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u16_UdmFFDIndexType, DEM_CODE ) Dem_UdmData_GetTSFFStoredRecordNumber
(
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, AUTOMATIC ) UdmStoredTSFFRecordNumberPtr
)
{
    *UdmStoredTSFFRecordNumberPtr   =   Dem_UdmStoredTSFFRecordNumber;
    return Dem_UdmStoredTSFFCount;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_ResetTSFFSearchStartPosition                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_ResetTSFFSearchStartPosition
( void )
{
    Dem_UdmSearchTSFFStartPositionIndex = (Dem_u16_UdmFFDIndexType)0U;
    return ;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_InitTSFFRecordNumber                         */
/* Description   | Initializes the time-series FFD record number informati- */
/*               | on.                                                      */
/* Preconditions |                                                          */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_InitTSFFRecordNumber
( void )
{
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC )  udmMaxNumberTsffPerDTC;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC )  udmTmpTSFFRecordNumberIndex;

    Dem_UdmSearchTSFFStartPositionIndex = (Dem_u16_UdmFFDIndexType)0U;
    Dem_UdmStoredTSFFCount              = (Dem_u16_UdmFFDIndexType)0U;
    Dem_UdmStoredTSFFRecordNumber       = DEM_FFRECNUM_INVALID;

    udmMaxNumberTsffPerDTC = Dem_UdmMaxNumberTsffPerDTC;

    for( udmTmpTSFFRecordNumberIndex = (Dem_u16_UdmFFDIndexType)0U; udmTmpTSFFRecordNumberIndex < udmMaxNumberTsffPerDTC; udmTmpTSFFRecordNumberIndex++ )   /* [GUD:for]udmTmpTSFFRecordNumberIndex */
    {
        Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].OccurrenceOrder = (Dem_u32_UdmOccurrenceOrderType)0U;/* Because sort items of array to backward. *//* [GUD]udmTmpTSFFRecordNumberIndex */
        Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].FreezeFrameDataIndex = (Dem_u16_AllFFDIndexType)DEM_UDMFFDINDEX_INVALID;    /* [GUD]udmTmpTSFFRecordNumberIndex */
        Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].TimeSeriesFreezeFrameListIndex = DEM_TSFFLISTINDEX_INVALID;                 /* [GUD]udmTmpTSFFRecordNumberIndex */
        Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].CidUdmFreezeFrameRecords = DEM_CONSISTENCY_INITIAL;                         /* [GUD]udmTmpTSFFRecordNumberIndex */
        Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].RecordNumber = DEM_RECORDNUMBER_NEXT_NONE;                                  /* [GUD]udmTmpTSFFRecordNumberIndex */
        Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].FreezeFrameDataType = DEM_FFD_TYPE_INVALID;                                 /* [GUD]udmTmpTSFFRecordNumberIndex */
        Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].RecordStatus = DEM_FFD_NOT_STORED;                                          /* [GUD]udmTmpTSFFRecordNumberIndex */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_SaveTSFFRecordNumber                         */
/* Description   | Geta the time-series FFD record number information.      */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               | [in] UdmEventIndex                                       */
/*               |        The event ID for retrieving.                      */
/*               | [in] UdmFaultRecordPtr :                                 */
/*               |      Dem_TmpDisabledRecord.FaultRecord pointer.          */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_SaveTSFFRecordNumber
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) UdmFaultRecordPtr
)
{
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) startingRecordNumber;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) stepNumberToNextStartingRecord;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsffRecordClassConfigureNum;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberFreezeFrameRecords;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC )  udmTmpTSFFRecordNumberIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmTmpRecordNumberByDTCIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC )  udmMaxNumberTsffPerDTC;

    tsffRecordClassConfigureNum = Dem_TSFFRecordClassConfigureNum;
    tsFFRecClassRef = Dem_CfgInfoUdm_GetTimeSeriesFreezeFrameRecordClassRef( UdmEventIndex );
    if( tsFFRecClassRef < tsffRecordClassConfigureNum )                                                                 /* [GUD:if]tsFFRecClassRef */
    {
        startingRecordNumber = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemStartingRecordNumber;                       /* [GUD]tsFFRecClassRef */
        stepNumberToNextStartingRecord = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemStepNumberToNextStartingRecord;   /* [GUD]tsFFRecClassRef */

        maxNumberFreezeFrameRecords = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( UdmEventIndex );

        udmMaxNumberTsffPerDTC = Dem_UdmMaxNumberTsffPerDTC;
        udmTmpTSFFRecordNumberIndex = (Dem_u16_UdmFFDIndexType)0U;

        tsffTotalDTCNum = Dem_TSFFTotalDTCNum;
        if( UdmFaultRecordPtr->TimeSeriesFreezeFrameListIndex < tsffTotalDTCNum )
        {
            /* In case there are storage of TSFFD. */

            /* Numbering record numbers by using TimeSeriesFreezeFrameListIndex of the sorted Dem_UdmTmpRecordNumberByDTC[] (it means the oldest) as tsFFListIndex. */

            for( udmTmpRecordNumberByDTCIndex = (Dem_u16_UdmFFDIndexType)0U; udmTmpRecordNumberByDTCIndex < maxNumberFreezeFrameRecords; udmTmpRecordNumberByDTCIndex++ )   /* [GUD:for]udmTmpRecordNumberByDTCIndex */
            {
                tsFFListIndex = Dem_UdmTmpRecordNumberByDTC[udmTmpRecordNumberByDTCIndex].TimeSeriesFreezeFrameListIndex;   /* [GUD]udmTmpRecordNumberByDTCIndex */
                if( tsFFListIndex < tsffTotalDTCNum )                                                                       /* [GUD:if]tsFFListIndex */
                {
                    Dem_UdmData_SaveTSFFRecordNumberByTSFFListIndex( UdmGroupKindIndex, tsFFListIndex, startingRecordNumber, &udmTmpTSFFRecordNumberIndex );    /* [GUD]tsFFListIndex *//* [GUD]udmTmpTSFFRecordNumberIndex */

                    startingRecordNumber = startingRecordNumber + stepNumberToNextStartingRecord;
                    if ( udmTmpTSFFRecordNumberIndex >= udmMaxNumberTsffPerDTC )                                            /* [GUD:if]udmTmpTSFFRecordNumberIndex */
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            /* In case there are no storage of TSFFD. */

            /* No process */
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_SaveTSFFRecordNumberByTSFFListIndex          */
/* Description   | Geta the time-series FFD record number information.      */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        The index for Dem_UserDefinedMemoryTable.         */
/*               | [in] TSFFListIndex :                                     */
/*               |        The index for Dem_TimeSeriesFreezeFrameTable.     */
/*               | [in] StartingRecordNumber :                              */
/*               |        The starting record number for each TSFFD.        */
/*               | [out] UdmTmpTSFFRecordNumberIndexPtr :                   */
/*               |        The index for Dem_UdmTmpTSFFRecordNumber.         */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmData_SaveTSFFRecordNumberByTSFFListIndex
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndex,                              /* [PRMCHK:CALLER] */
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) StartingRecordNumber,
    P2VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC, AUTOMATIC ) UdmTmpTSFFRecordNumberIndexPtr   /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetTSFFD;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC )  udmTmpTSFFRecordNumberIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmTSFFRecStartIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmTSFFRecEndIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmTSFFRecCount;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmTSFFRecLimit;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmTSFFRecIndex;
    VAR( Dem_UdmFreezeFrameRecordMngType, AUTOMATIC ) udmTSFFRecord;

    udmTmpTSFFRecordNumberIndex = (*UdmTmpTSFFRecordNumberIndexPtr);                                    /* [GUDCHK:CALLER]*UdmTmpTSFFRecordNumberIndexPtr */

    udmTSFFRecStartIndex = Dem_TimeSeriesFreezeFrameTable[TSFFListIndex].DemStartIndex;                 /* [GUDCHK:CALLER]TSFFListIndex */
    udmTSFFRecEndIndex = Dem_TimeSeriesFreezeFrameTable[TSFFListIndex].DemEndIndex;                     /* [GUDCHK:CALLER]TSFFListIndex */
    udmTSFFRecLimit = ( udmTSFFRecEndIndex - udmTSFFRecStartIndex ) + (Dem_u16_UdmFFDIndexType)1U;

    for( udmTSFFRecCount = (Dem_u16_UdmFFDIndexType)0U; udmTSFFRecCount < udmTSFFRecLimit; udmTSFFRecCount++ )
    {
        udmTSFFRecIndex = udmTSFFRecStartIndex + udmTSFFRecCount;

        Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].FreezeFrameDataIndex = (Dem_u16_AllFFDIndexType)udmTSFFRecIndex;                        /* [GUDCHK:CALLER]*UdmTmpTSFFRecordNumberIndexPtr */
        Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].RecordNumber = (Dem_u08_FFRecordNumberType)( StartingRecordNumber + udmTSFFRecCount );  /* [GUDCHK:CALLER]*UdmTmpTSFFRecordNumberIndexPtr */
        Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].FreezeFrameDataType = DEM_FFD_TYPE_TSFFD;                                               /* [GUDCHK:CALLER]*UdmTmpTSFFRecordNumberIndexPtr */

        resultOfGetTSFFD = Dem_UdmTSFFDMng_GetTimeSeriesFreezeFrameRecord( UdmGroupKindIndex, udmTSFFRecIndex, &udmTSFFRecord );
        if( resultOfGetTSFFD == DEM_IRT_OK )
        {
            if( udmTSFFRecord.RecordStatus == DEM_FFD_STORED )
            {
                Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].OccurrenceOrder = udmTSFFRecord.OccurrenceOrder;                                /* [GUDCHK:CALLER]*UdmTmpTSFFRecordNumberIndexPtr */
                Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].TimeSeriesFreezeFrameListIndex = TSFFListIndex;                                 /* [GUDCHK:CALLER]*UdmTmpTSFFRecordNumberIndexPtr */
                Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].CidUdmFreezeFrameRecords = udmTSFFRecord.CidUdmFreezeFrameRecords;              /* [GUDCHK:CALLER]*UdmTmpTSFFRecordNumberIndexPtr */
                Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].RecordStatus = DEM_FFD_STORED;                                                  /* [GUDCHK:CALLER]*UdmTmpTSFFRecordNumberIndexPtr */
                Dem_UdmStoredTSFFCount          =   Dem_UdmStoredTSFFCount + (Dem_u16_UdmFFDIndexType)1U;
                if ( Dem_UdmStoredTSFFRecordNumber == DEM_FFRECNUM_INVALID )
                {
                    Dem_UdmStoredTSFFRecordNumber   =   Dem_UdmTmpTSFFRecordNumber[udmTmpTSFFRecordNumberIndex].RecordNumber;                           /* [GUDCHK:CALLER]*UdmTmpTSFFRecordNumberIndexPtr */
                }

                udmTmpTSFFRecordNumberIndex = udmTmpTSFFRecordNumberIndex + (Dem_u16_UdmFFDIndexType)1U;
            }
        }
    }

    (*UdmTmpTSFFRecordNumberIndexPtr) = udmTmpTSFFRecordNumberIndex;

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_GetAllTSFFRecordNumber                       */
/* Description   | get all record number.                                   */
/* Preconditions |                                                          */
/* Parameters    | [out] RecordNumBufferPtr :                               */
/*               |        the buffer, to which the freeze frame data recor- */
/*               |        d shall be written to                             */
/*               | [in/out] RecordNumPtr :                                  */
/*               |        the actual number of written data bytes           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Size successfully returned           */
/*               |        DEM_IRT_WRONG_BUFFERSIZE : provided buffer size - */
/*               |        to small                                          */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetAllTSFFRecordNumber
(
    P2VAR( Dem_u08_FFRecordNumberType, AUTOMATIC, DEM_APPL_DATA ) RecordNumBufferPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) RecordNumPtr
)
{
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC )    saveRecNumIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC )    udmMaxNumberTsffPerDTC;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) recordStatus;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) recordNumber;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( uint8, AUTOMATIC ) recordNumBuffMax;
    VAR( uint8, AUTOMATIC ) recordNumCnt;

    recordNumBuffMax    =   *RecordNumPtr;
    recordNumCnt        =   (Dem_u08_FFRecordNumberType)0U;

    udmMaxNumberTsffPerDTC = Dem_UdmMaxNumberTsffPerDTC;

    retVal  =   DEM_IRT_OK;

    /*------------------------------*/
    /*  timeseries freeze frame     */
    /*------------------------------*/
    for( saveRecNumIndex =  Dem_UdmSearchTSFFStartPositionIndex; saveRecNumIndex < udmMaxNumberTsffPerDTC; saveRecNumIndex++ )  /* [GUD:for]saveRecNumIndex */
    {
        if( DEM_FFD_TYPE_INVALID != Dem_UdmTmpTSFFRecordNumber[saveRecNumIndex].FreezeFrameDataType )                           /* [GUD]saveRecNumIndex */
        {
            recordStatus =   Dem_UdmTmpTSFFRecordNumber[saveRecNumIndex].RecordStatus;                                          /* [GUD]saveRecNumIndex */

            /*  record is stored.               */
            if ( recordStatus == DEM_FFD_STORED )
            {
                recordNumber    =   Dem_UdmTmpTSFFRecordNumber[saveRecNumIndex].RecordNumber;                                   /* [GUD]saveRecNumIndex */

                /*  check : remain buffer size          */
                if ( recordNumCnt < recordNumBuffMax )                          /* [GUD:if]recordNumCnt */
                {
                    RecordNumBufferPtr[ recordNumCnt ]    =   recordNumber;     /* [GUD]recordNumCnt */
                    recordNumCnt    =   recordNumCnt + (uint8)1U;
                }
                else
                {
                    /*  buffer is too small.            */
                    retVal  =   DEM_IRT_WRONG_BUFFERSIZE;
                    break;
                }
            }
        }
    }
    if ( retVal == DEM_IRT_OK )
    {
        *RecordNumPtr   =   recordNumCnt;
    }
    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
