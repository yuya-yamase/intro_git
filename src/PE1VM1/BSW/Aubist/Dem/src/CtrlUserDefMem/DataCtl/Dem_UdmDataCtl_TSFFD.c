/* Dem_UdmDataCtl_TSFFD_c(v5-7-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_TSFFD/CODE                                 */
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
#include "../../../inc/Dem_Rc_UdmEventRecordTable.h"
#include "../../../inc/Dem_Rc_UdmFaultRecordTable.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"
#include "Dem_UdmDataCtl_TSFFD_local.h"

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

static FUNC( void, DEM_CODE ) Dem_UdmData_MakeTSFFListRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) UdmFaultRecordPtr
);

static FUNC( void, DEM_CODE ) Dem_UdmData_GenerateTSFFLRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) UdmFaultRecordPtr,
    P2VAR( Dem_TimeSeriesFreezeFrameListType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameListRecordListPtr
);

static FUNC( boolean, DEM_CODE ) Dem_UdmData_CheckTSFFRecordStored
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListRecIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumberOfBeforeTriggeredRecord,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumberOfAfterTriggeredRecord
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
/* Function Name | Dem_UdmData_CaptureAfterTriggeredTSFFFromSample          */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               |        The index of the user defined table.              */
/*               | [in] UdmFaultIndex :                                     */
/*               |        The index of the udm faul record list.            */
/*               | [in] TimeSeriesFreezeFrameRecordIndex :                  */
/*               |        The index of the time series freeze frame record  */
/*               |        list.                                             */
/*               | [in] OffsetOfTimeSeriesFreezeFrameTableIndexPerDTC :     */
/*               |        Offset of the index of the time series freeze fr- */
/*               |        ame table per DTC.                                */
/*               | [in] SamplingFreezeFrameRecordPosPtr :                   */
/*               |        The pointer of position information for sampling  */
/*               |        freeze frame record.                              */
/*               | [out] SamplingFreezeFrameRecordDataPtr :                 */
/*               |        The pointer of data array of the sampling freeze  */
/*               |        frame record.                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_CaptureAfterTriggeredTSFFFromSample
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) SamplingFFRDataSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,     /* [PRMCHK:CALLER] */
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordIndex,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) OffsetOfTimeSeriesFreezeFrameTableIndexPerDTC,
    P2CONST( Dem_SamplingFreezeFrameRecordPosType, AUTOMATIC, AUTOMATIC ) SamplingFreezeFrameRecorPosPtr,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) SamplingFreezeFrameRecordDataPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFaultRecord;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSetTSFFRec;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) triggerFFDConsistencyId;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameRecordIndex;
    VAR( Dem_UdmFaultRecordType, AUTOMATIC ) udmFaultRecord;

    retVal = DEM_IRT_NG;

    retGetFaultRecord = Dem_UdmFaultMngC_GetRecord( UdmGroupKindIndex, UdmFaultIndex, &udmFaultRecord );                        /* [GUDCHK:CALLER]UdmGroupKindIndex */
    if( retGetFaultRecord == DEM_IRT_OK )
    {
        if( udmFaultRecord.RecordNumberIndex != DEM_UDMFFRECINDEX_INITIAL )
        {
            udmFreezeFrameRecordIndex = Dem_UdmFFDMng_GetFFRIndexByOffsetOfTSFFListIndex( UdmGroupKindIndex, udmFaultRecord.UdmEventIndex, udmFaultRecord.RecordNumberIndex, OffsetOfTimeSeriesFreezeFrameTableIndexPerDTC );/* [GUDCHK:CALLER]UdmGroupKindIndex */
            if( udmFreezeFrameRecordIndex != DEM_UDMFFDINDEX_INVALID )
            {
                triggerFFDConsistencyId = Dem_UdmFFDMng_GetFFDConsystencyId( UdmGroupKindIndex, udmFreezeFrameRecordIndex );    /* [GUDCHK:CALLER]UdmGroupKindIndex */

#ifndef JGXSTACK
                /* Starts exclusion. */
                Dem_UdmExcFncTable[ UdmGroupKindIndex ].ExclusiveEnterFnc();    /* [GUDCHK:CALLER]UdmGroupKindIndex */
#else   /* JGXSTACK */
                Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */

                resultOfSetTSFFRec = Dem_UdmTSFFDMng_SetAfterTimeSeriesFreezeFrameRecord( UdmGroupKindIndex, udmFreezeFrameRecordIndex, TimeSeriesFreezeFrameRecordIndex, udmFaultRecord.UdmEventIndex, triggerFFDConsistencyId, (Dem_u08_FFStoredStatusType)SamplingFreezeFrameRecordDataPtr[SamplingFreezeFrameRecorPosPtr->RecordStatus], &SamplingFreezeFrameRecordDataPtr[SamplingFreezeFrameRecorPosPtr->DataStart] );    /* [GUDCHK:CALLER]UdmGroupKindIndex *//* [ARYCHK] SamplingFFRDataSize / 1 / SamplingFreezeFrameRecorPosPtr->RecordStatus *//* [ARYCHK] SamplingFFRDataSize / 1 / SamplingFreezeFrameRecorPosPtr->DataStart */

#ifndef JGXSTACK
            /* Finishes exclusion. */
                Dem_UdmExcFncTable[ UdmGroupKindIndex ].ExclusiveExitFnc();     /* [GUDCHK:CALLER]UdmGroupKindIndex */
#else   /* JGXSTACK */
                Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */

                if( resultOfSetTSFFRec == DEM_IRT_OK )
                {
                    retVal = DEM_IRT_OK;
                }
            }
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_MakeTSFFListRecordList                       */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_MakeTSFFListRecordList
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventStrgIndex;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) eventRecordNum;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    P2VAR( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmEventRecordPtr;
    VAR( Dem_UdmFaultRecordType, AUTOMATIC ) udmFaultRecord;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    for( udmGroupKindIndex = (Dem_u16_UdmDemMemKindIndexType)0U; udmGroupKindIndex < userDefinedMemoryNum; udmGroupKindIndex++ )    /* [GUD:for]udmGroupKindIndex */
    {
        eventRecordNum = Dem_UdmEventRecordTable[udmGroupKindIndex].DemEventRecordNum;                                              /* [GUD]udmGroupKindIndex */

        for( udmEventStrgIndex = (Dem_u16_UdmEventStrgIndexType)0U; udmEventStrgIndex < eventRecordNum; udmEventStrgIndex++ )       /* [GUD:for]udmEventStrgIndex */
        {
            resultOfGetFaultRec = DEM_IRT_NG;

            udmEventRecordPtr = Dem_UdmEventMng_GetEventRecordPtr( udmGroupKindIndex, udmEventStrgIndex );  /* [GUD]udmGroupKindIndex *//* [GUD:RET:Not NULL_PTR] udmEventRecordPtr */
            if( udmEventRecordPtr != NULL_PTR )
            {
                resultOfGetFaultRec = Dem_UdmFaultMngC_GetRecord( udmGroupKindIndex, udmEventRecordPtr->UdmFaultIndex, &udmFaultRecord );   /* [GUD]udmGroupKindIndex */
            }

            if( resultOfGetFaultRec == DEM_IRT_OK )
            {
                if ( udmFaultRecord.RecordNumberIndex != DEM_UDMFFRECINDEX_INITIAL )
                {
                    udmEventIndex = Dem_CfgInfoUdm_CnvUdmEventStrgIndexToUdmEventIndex( udmGroupKindIndex, udmEventStrgIndex );             /* [GUD]udmGroupKindIndex *//* [GUD:for]udmEventStrgIndex *//* [GUD:RET:IF_GUARDED:udmGroupKindIndex/udmEventStrgIndex] udmEventIndex */

                    Dem_UdmData_MakeTSFFListRecord( udmGroupKindIndex, udmEventIndex, udmEventRecordPtr->UdmFaultIndex, &udmFaultRecord );  /* [GUD]udmGroupKindIndex *//* [GUD]udmEventIndex */
                }
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_MakeTSFFListRecord                           */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |                                                          */
/*               | [in] UdmEventIndex :                                     */
/*               |                                                          */
/*               | [in] UdmFaultIndex :                                     */
/*               |                                                          */
/*               | [in] UdmFaultRecordPtr :                                 */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmData_MakeTSFFListRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,         /* [PRMCHK:CALLER] */
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,                  /* [PRMCHK:CALLER] */
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) UdmFaultRecordPtr
)
{
    VAR( boolean, AUTOMATIC ) isTSFFStored;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfBeforeTriggeredRecord;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfAfterTriggeredRecord;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) faultRecordNum;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecLimit;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;

    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;
    faultRecordNum = Dem_UdmFaultRecordTable[UdmGroupKindIndex].DemFaultRecordNum;  /* [GUDCHK:CALLER]UdmGroupKindIndex */

    if( UdmFaultIndex >= faultRecordNum )
    {
        /* No process */
    }
    else
    {
        tsFFRecClassRef = Dem_CfgInfoUdm_GetTimeSeriesFreezeFrameRecordClassRef( UdmEventIndex );   /* [GUDCHK:CALLER]UdmEventIndex */
        if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )                                  /* [GUD:if]tsFFRecClassRef */
        {
            if( UdmFaultRecordPtr->TimeSeriesFreezeFrameListIndex < tsffTotalDTCNum )
            {
                tsFFListRecIndex = UdmFaultRecordPtr->TimeSeriesFreezeFrameListIndex;
                tsFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameClassRef;              /* [GUD]tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED: tsFFRecClassRef ]tsFFClassRef */
                tsFFListRecLimit = tsFFListRecIndex + (Dem_u16_TSFFListIndexType)Dem_TSFFClassTable[tsFFClassRef].DemNumberOfTimeSeriesFreezeFramePerDTC;       /* [GUD]tsFFClassRef */
                if( tsFFListRecLimit <= tsffTotalDTCNum )
                {
                    numberOfBeforeTriggeredRecord = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfBeforeTriggeredRecord;                                          /* [GUD]tsFFClassRef */
                    numberOfAfterTriggeredRecord = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfAfterTriggeredRecord;                                            /* [GUD]tsFFClassRef */

                    for( ; tsFFListRecIndex < tsFFListRecLimit ; tsFFListRecIndex++ )                                                                           /* [GUD:for]tsFFListRecIndex */
                    {
                        isTSFFStored = Dem_UdmData_CheckTSFFRecordStored( UdmGroupKindIndex, tsFFListRecIndex, numberOfBeforeTriggeredRecord, numberOfAfterTriggeredRecord );
                        if( isTSFFStored == (boolean)TRUE )
                        {
                            Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecIndex].FaultIndex = (Dem_u08_FaultIndexType)UdmFaultIndex;                       /* [GUD]tsFFListRecIndex */

                            Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecIndex].NumberOfStoredAfterTriggeredRecord = DEM_TSFFLIST_AFTTRGRECNUM_INVALID;   /* [GUD]tsFFListRecIndex */

                            (void)Dem_Data_UpdateVacantTSFFListRecordRef( tsFFRecClassRef );/* no return check required */
                        }
                    }

                    Dem_UdmData_SetCurrentIndexOfTSFFCtrlRecord( UdmGroupKindIndex, UdmEventIndex, tsFFRecClassRef, UdmFaultRecordPtr );
                }
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_GenerateTSFFLRecordList                      */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_GenerateTSFFLRecordList
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) udmEventStrgIndex;
    VAR( Dem_u16_UdmEventStrgIndexType, AUTOMATIC ) eventRecordNum;
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventIndex;
    P2VAR( Dem_UdmEventRecordType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) udmEventRecordPtr;
    VAR( Dem_UdmFaultRecordType, AUTOMATIC ) udmFaultRecord;
    VAR( Dem_TimeSeriesFreezeFrameListType, AUTOMATIC ) timeSeriesFreezeFrameListRecordList[DEM_TSFF_TOTAL_DTC_NUM];

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    Dem_Data_SaveTSFFListRecordList( timeSeriesFreezeFrameListRecordList );

    if( UdmGroupKindIndex < userDefinedMemoryNum )                                                              /* [GUD:if]UdmGroupKindIndex */
    {
        /* Initializes time-series freeze frame related memory. */
        Dem_Data_InitTSFFListRecordList( ( Dem_u16_SmpRecMemIndexType )UdmGroupKindIndex );                                                 /* [GUD]UdmGroupKindIndex */
        Dem_Data_InitTSFFCtrlRecordList( ( Dem_u16_SmpRecMemIndexType )UdmGroupKindIndex );                                                 /* [GUD]UdmGroupKindIndex */

        eventRecordNum = Dem_UdmEventRecordTable[UdmGroupKindIndex].DemEventRecordNum;                                                      /* [GUD]UdmGroupKindIndex */

        for( udmEventStrgIndex = (Dem_u16_UdmEventStrgIndexType)0U; udmEventStrgIndex < eventRecordNum; udmEventStrgIndex++ )               /* [GUD:for]udmEventStrgIndex */
        {
            resultOfGetFaultRec = DEM_IRT_NG;

            udmEventRecordPtr = Dem_UdmEventMng_GetEventRecordPtr( UdmGroupKindIndex, udmEventStrgIndex );                                  /* [GUD:RET:Not NULL_PTR] udmEventRecordPtr */
            if( udmEventRecordPtr != NULL_PTR )
            {
                resultOfGetFaultRec = Dem_UdmFaultMngC_GetRecord( UdmGroupKindIndex, udmEventRecordPtr->UdmFaultIndex, &udmFaultRecord );   /* [GUD]UdmGroupKindIndex */
            }

            if( resultOfGetFaultRec == DEM_IRT_OK )
            {
                if ( udmFaultRecord.RecordNumberIndex != DEM_UDMFFRECINDEX_INITIAL )
                {
                    udmEventIndex = Dem_CfgInfoUdm_CnvUdmEventStrgIndexToUdmEventIndex( UdmGroupKindIndex, udmEventStrgIndex );             /* [GUD]UdmGroupKindIndex *//* [GUD]udmEventStrgIndex */

                    Dem_UdmData_GenerateTSFFLRecord( UdmGroupKindIndex, udmEventIndex, udmEventRecordPtr->UdmFaultIndex, &udmFaultRecord, timeSeriesFreezeFrameListRecordList );    /* [GUD]UdmGroupKindIndex *//* [GUD]udmEventStrgIndex */
                }
            }
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_GenerateTSFFLRecord                          */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |                                                          */
/*               | [in] UdmEventIndex :                                     */
/*               |                                                          */
/*               | [in] UdmFaultIndex :                                     */
/*               |                                                          */
/*               | [in] UdmFaultRecordPtr :                                 */
/*               |                                                          */
/*               | [in] TimeSeriesFreezeFrameListRecordListPtr :            */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmData_GenerateTSFFLRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,     /* [PRMCHK:CALLER] */
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) UdmFaultRecordPtr,
    P2VAR( Dem_TimeSeriesFreezeFrameListType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameListRecordListPtr
)
{
    VAR( boolean, AUTOMATIC ) isTSFFStored;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) faultRecordNum;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfBeforeTriggeredRecord;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numberOfAfterTriggeredRecord;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecLimit;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;

    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;
    faultRecordNum = Dem_UdmFaultRecordTable[UdmGroupKindIndex].DemFaultRecordNum;      /* [GUDCHK:CALLER]UdmGroupKindIndex */

    if( UdmFaultIndex >= faultRecordNum )
    {
        /* No process */
    }
    else
    {
        tsFFRecClassRef = Dem_CfgInfoUdm_GetTimeSeriesFreezeFrameRecordClassRef( UdmEventIndex );
        if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )                                          /* [GUD:if]tsFFRecClassRef */
        {
            if( UdmFaultRecordPtr->TimeSeriesFreezeFrameListIndex < tsffTotalDTCNum )
            {
                tsFFListRecIndex = UdmFaultRecordPtr->TimeSeriesFreezeFrameListIndex;
                tsFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameClassRef;  /* [GUD]tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED: tsFFRecClassRef ]tsFFClassRef */
                tsFFListRecLimit = tsFFListRecIndex + (Dem_u16_TSFFListIndexType)Dem_TSFFClassTable[tsFFClassRef].DemNumberOfTimeSeriesFreezeFramePerDTC;   /* [GUD]tsFFClassRef */
                if( tsFFListRecLimit <= tsffTotalDTCNum )
                {
                    numberOfBeforeTriggeredRecord = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfBeforeTriggeredRecord;                          /* [GUD]tsFFClassRef */
                    numberOfAfterTriggeredRecord = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfAfterTriggeredRecord;                            /* [GUD]tsFFClassRef */

                    for( ; tsFFListRecIndex < tsFFListRecLimit ; tsFFListRecIndex++ )                                                           /* [GUD:for]tsFFListRecIndex */
                    {
                        isTSFFStored = Dem_UdmData_CheckTSFFRecordStored( UdmGroupKindIndex, tsFFListRecIndex, numberOfBeforeTriggeredRecord, numberOfAfterTriggeredRecord );
                        if( isTSFFStored == (boolean)TRUE )
                        {
                            Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecIndex].FaultIndex = (Dem_u08_FaultIndexType)UdmFaultIndex;       /* [GUD]tsFFListRecIndex */

                            Dem_Data_UpdateNumberOfStoredAfterTriggeredRecord( (Dem_u08_FaultIndexType)UdmFaultIndex, tsFFListRecIndex, tsFFRecClassRef, TimeSeriesFreezeFrameListRecordListPtr );

                            (void)Dem_Data_UpdateVacantTSFFListRecordRef( tsFFRecClassRef );/* no return check required */
                        }
                    }

                    Dem_UdmData_SetCurrentIndexOfTSFFCtrlRecord( UdmGroupKindIndex, UdmEventIndex, tsFFRecClassRef, UdmFaultRecordPtr );
                }
            }
        }
    }

    return;

}


/****************************************************************************/
/* Function Name | Dem_UdmData_CheckTSFFRecordStored                        */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |                                                          */
/*               | [in] TSFFListRecIndex :                                  */
/*               |                                                          */
/*               | [in] NumberOfBeforeTriggeredRecord :                     */
/*               |                                                          */
/*               | [in] NumberOfAfterTriggeredRecord :                      */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |        FALSE : Not Stored                                */
/*               |        TRUE  : Stored                                    */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_UdmData_CheckTSFFRecordStored
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListRecIndex,       /* [PRMCHK:CALLER] */
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumberOfBeforeTriggeredRecord,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumberOfAfterTriggeredRecord
)
{
    VAR( boolean, AUTOMATIC ) isTSFFStored;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) mostRecentBeforeTSFFRecordStatus;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) mostRecentAfterTSFFRecordStatus;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) mostRecentBeforeTSFFRecIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) mostRecentAfterTSFFRecIndex;

    isTSFFStored = (boolean)FALSE;
    mostRecentBeforeTSFFRecordStatus = DEM_FFD_NOT_STORED;
    mostRecentAfterTSFFRecordStatus = DEM_FFD_NOT_STORED;

    if( NumberOfBeforeTriggeredRecord > (Dem_u08_NumOfTSFFType)0U )
    {
        mostRecentBeforeTSFFRecIndex = ( Dem_TimeSeriesFreezeFrameTable[TSFFListRecIndex].DemStartIndex + (Dem_u16_TSFFDIndexType)NumberOfBeforeTriggeredRecord ) - (Dem_u16_TSFFDIndexType)1U; /* [GUDCHK:CALLER]TSFFListRecIndex */
        mostRecentBeforeTSFFRecordStatus = Dem_UdmTSFFDMng_GetRecordStatus( UdmGroupKindIndex, mostRecentBeforeTSFFRecIndex );
    }

    if( NumberOfAfterTriggeredRecord > (Dem_u08_NumOfTSFFType)0U )
    {
        mostRecentAfterTSFFRecIndex = Dem_TimeSeriesFreezeFrameTable[TSFFListRecIndex].DemStartIndex + (Dem_u16_TSFFDIndexType)NumberOfBeforeTriggeredRecord;       /* [GUDCHK:CALLER]TSFFListRecIndex */
        mostRecentAfterTSFFRecordStatus = Dem_UdmTSFFDMng_GetRecordStatus( UdmGroupKindIndex, mostRecentAfterTSFFRecIndex );
    }

    if( mostRecentBeforeTSFFRecordStatus == DEM_FFD_STORED )
    {
        isTSFFStored = (boolean)TRUE;
    }
    else if( mostRecentAfterTSFFRecordStatus == DEM_FFD_STORED )
    {
        isTSFFStored = (boolean)TRUE;
    }
    else
    {
        /* No process */
    }

    return isTSFFStored;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
