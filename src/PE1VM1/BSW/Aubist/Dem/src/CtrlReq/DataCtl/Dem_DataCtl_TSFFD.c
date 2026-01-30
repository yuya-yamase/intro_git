/* Dem_DataCtl_TSFFD_c(v5-7-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_TSFFD/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )

#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Pm_TSFFD.h"

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
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_Data_MakeTSFFListRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Data_CaptureAfterTriggeredTSFFFromSample             */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/*               | [in] FaultIndex :                                        */
/*               |        The index of the faul record list.                */
/*               | [in] TimeSeriesFreezeFrameRecordIndex :                  */
/*               |        The index of the time series freeze frame record  */
/*               |        list.                                             */
/*               | [in] TimeSeriesFreezeFrameTrigger :                      */
/*               |        The trigger of the time series freeze frame reco- */
/*               |        rd .                                              */
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
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_CaptureAfterTriggeredTSFFFromSample
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) SamplingFFRDataSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TimeSeriesFreezeFrameTrigger,
    P2CONST( Dem_SamplingFreezeFrameRecordPosType, AUTOMATIC, AUTOMATIC ) SamplingFreezeFrameRecorPosPtr,       /* [PRMCHK:CALLER] */
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) SamplingFreezeFrameRecordDataPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFaultRecord;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSetTSFFRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChkExistTrigger;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) triggerFFDIndex;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) triggerFFDConsistencyId;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;

    retVal = DEM_IRT_NG;

    retGetFaultRecord = Dem_DataMngC_GetFaultRecord( FaultIndex, &faultRecord );
    if( retGetFaultRecord == DEM_IRT_OK )
    {
        eventStrgIndex = faultRecord.EventStrgIndex;
        dtcAttributePtr =   Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF( eventStrgIndex );    /* [GUD:RET:Not NULL_PTR]dtcAttributePtr */

        if ( dtcAttributePtr != NULL_PTR )                                              /* [GUD:if]dtcAttributePtr */
        {
            retChkExistTrigger = Dem_FFDMng_CheckToExistTriggerFFD( TimeSeriesFreezeFrameTrigger, dtcAttributePtr, &faultRecord, &triggerFFDIndex );    /* [GUD]dtcAttributePtr */
            if( retChkExistTrigger == DEM_IRT_OK )
            {
                triggerFFDConsistencyId = Dem_FFDMng_GetFFDConsystencyId( triggerFFDIndex );

                SchM_Enter_Dem_EventMemory();

                resultOfSetTSFFRec = Dem_DataMngC_SetAfterTimeSeriesFreezeFrameRecord( TimeSeriesFreezeFrameRecordIndex, eventStrgIndex, triggerFFDConsistencyId, (Dem_u08_FFStoredStatusType)SamplingFreezeFrameRecordDataPtr[SamplingFreezeFrameRecorPosPtr->RecordStatus], &SamplingFreezeFrameRecordDataPtr[SamplingFreezeFrameRecorPosPtr->DataStart] );   /* [GUDCHK:CALLER]SamplingFreezeFrameRecorPosPtr *//* [ARYCHK] SamplingFFRDataSize / 1 / SamplingFreezeFrameRecorPosPtr->RecordStatus *//* [ARYCHK] SamplingFFRDataSize / 1 / SamplingFreezeFrameRecorPosPtr->DataStart */

                SchM_Exit_Dem_EventMemory();

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
/* Function Name | Dem_Data_MakeTSFFListRecordList                          */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_MakeTSFFListRecordList
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;

    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    for( eventStrgIndex = (Dem_u16_EventStrgIndexType)0U; eventStrgIndex < eventStorageNum; eventStrgIndex++ )
    {
        resultOfGetFaultRec = DEM_IRT_NG;
        faultIndex = DEM_FAULTINDEX_INITIAL;

        resultOfGetFaultIndex = Dem_DataMngC_GetER_FaultIndex( eventStrgIndex, &faultIndex );       /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */

        if( resultOfGetFaultIndex == DEM_IRT_OK )
        {
            resultOfGetFaultRec = Dem_DataMngC_GetFaultRecord( faultIndex, &faultRecord );
        }

        if( resultOfGetFaultRec == DEM_IRT_OK )
        {
            Dem_Data_MakeTSFFListRecord( eventStrgIndex, faultIndex, &faultRecord );
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Data_MakeTSFFListRecord                              */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |                                                          */
/*               | [in] FaultIndex :                                        */
/*               |                                                          */
/*               | [in] FaultRecordPtr :                                    */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Data_MakeTSFFListRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
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
        dtcAttributePtr    =   Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF( EventStrgIndex );           /* [GUD]EventStrgIndex *//* [GUD:RET:Not NULL_PTR]dtcAttributePtr */

        if ( dtcAttributePtr != NULL_PTR )                                              /* [GUD:if]dtcAttributePtr */
        {
            for( tsFFListIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; tsFFListIndex < tsffRecordClassNumPerDTCMaxNum; tsFFListIndex++ ) /* [GUD:for]tsFFListIndex */
            {
                tsFFRecClassRef = dtcAttributePtr->DemTimeSeriesFreezeFrameRecordClassRef[tsFFListIndex];                               /* [GUD]dtcAttributePtr *//* [GUD]tsFFListIndex *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / tsFFListIndex */

                if( tsFFRecClassRef != DEM_TSFF_RECORD_CLASS_REF_INVALID )                                                              /* [GUD:if]tsFFRecClassRef */
                {
                    tsFFListRecIndex = FaultRecordPtr->TimeSeriesFreezeFrameListIndex[tsFFListIndex];                                   /* [GUD]tsFFListIndex *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / tsFFListIndex */

                    if( tsFFListRecIndex < tsffTotalDTCNum )                                                                            /* [GUD:if]tsFFListRecIndex */
                    {
                        Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecIndex].FaultIndex = FaultIndex;                              /* [GUD]tsFFListRecIndex */

                        Dem_TimeSeriesFreezeFrameListRecordList[tsFFListRecIndex].NumberOfStoredAfterTriggeredRecord = DEM_TSFFLIST_AFTTRGRECNUM_INVALID;   /* [GUD]tsFFListRecIndex */

                        (void)Dem_Data_UpdateVacantTSFFListRecordRef( tsFFRecClassRef );/* no return check required */                  /* [GUD]tsFFRecClassRef */
                    }
                }
            }
        }
    }

    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
