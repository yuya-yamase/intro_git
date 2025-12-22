/* Dem_DataMng_RecDt_TSFFD_c(v5-10-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_DataMng_RecDt_TSFFD_c/CODE                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "Dem_DataMng_local.h"
#include "Dem_DataMng_FreezeFrame.h"
#include "Dem_DataMng_GetRecordData.h"

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_ClearTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
);
static FUNC( void, DEM_CODE ) Dem_TSFFDMng_VerifiedRecord
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListRecordIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) TriggerFFDConsystencyId,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumOfBeforeTSFFRecord,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) TSFFListIndexInitFlg
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_TSFFDMng_VerifiedBeforeTSFFD
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListRecordIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) TriggerFFDConsystencyId,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumOfBeforeTSFFRecord,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFreezeFrameStoredCntPtr
);
static FUNC( void, DEM_CODE ) Dem_TSFFDMng_VerifiedAfterTSFFD
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListRecordIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) TriggerFFDConsystencyId,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumOfBeforeTSFFRecord,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFreezeFrameStoredCntPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_TSFFDMng_CheckConsistency
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) TriggerFFDConsystencyId
);

static FUNC( void, DEM_CODE ) Dem_TSFFDMng_GetFFDConsistencyInfo
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) FirstBlockCIdPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) LastBlockCIdPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) FirstBlockEventStrgIndexPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) LastBlockEventStrgIndexPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_TSFFDMng_VerifyChecksum
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
);

#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
static FUNC( Dem_u16_FFCheckSumType, DEM_CODE ) Dem_TSFFDMng_GetChecksum
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
);
#endif /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON ) */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_TSFFDMng_InitMirrorMemory
( void );
#endif /*   ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_TSFFDNvMStatus[DEM_TSFF_RECORD_LIST_NUM];
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*  if DEM_NVM_SYNC_PROCESS_ENABLE is STD_OFF, these valiables are set but never used.  */
VAR( Dem_TSFFRecordType, DEM_VAR_NO_INIT ) Dem_TmpTSFFDMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

VAR(Dem_TSFFRecordType, DEM_VAR_SAVED_ZONE ) Dem_TimeSeriesFreezeFrameRecordList[DEM_TSFF_RECORD_LIST_NUM];

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DataMngC_SetBeforeTimeSeriesFreezeFrameRecord        */
/* Description   | Set the captured FreezeFrame data, fault occurrence ind- */
/*               | ex, and storage status of the time series FreezeFrame r- */
/*               | ecord specified in the time series FreezeFrame record l- */
/*               | ist corresponding to the designated time series FreezeF- */
/*               | rame index.(for Dem_DataCtl subunit)                     */
/* Preconditions |                                                          */
/* Parameters    | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        Time Series FreezeFrame Index.                    */
/*               | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [in] ConsistencyId :                                     */
/*               |        The ID for consistency between with trigger FFD.  */
/*               | [in] SamplingFreezeFrameRecordDataStartPtr :             */
/*               |        The pointer of data start of the sampling freeze  */
/*               |        frame record.                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_SetBeforeTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) SamplingFreezeFrameRecordDataStartPtr
)
{
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffTotalTimeseriesFFRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) tsFFRecordMaxLength;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindTSFFD;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    tsffTotalTimeseriesFFRecordNum = Dem_TSFFTotalTimeseriesFFRecordNum;

    if( TimeSeriesFreezeFrameIndex < tsffTotalTimeseriesFFRecordNum )                           /* [GUD:if]TimeSeriesFreezeFrameIndex */
    {
        tsFFRecordMaxLength = Dem_TSFFRecordMaxLength;

        /* Dealing with the writing of TSFFD outside the exclusive section */
        /* In the case of before TSFFD, save in not stored state to be temporary */
#ifndef DEM_SIT_RANGE_CHECK
        Dem_DataMng_SetCapturedFreezeFrame( &Dem_TimeSeriesFreezeFrameDataPosTable, ConsistencyId, EventStrgIndex, DEM_FFD_NOT_STORED, SamplingFreezeFrameRecordDataStartPtr, tsFFRecordMaxLength, Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data );  /* [GUD]TimeSeriesFreezeFrameIndex */
#else   /* DEM_SIT_RANGE_CHECK */
        Dem_DataMng_SetCapturedFreezeFrame( DEM_TSFF_STORED_FORMAT_SIZE, &Dem_TimeSeriesFreezeFrameDataPosTable, ConsistencyId, EventStrgIndex, DEM_FFD_NOT_STORED, SamplingFreezeFrameRecordDataStartPtr, tsFFRecordMaxLength, Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data );  /* [GUD]TimeSeriesFreezeFrameIndex */
#endif  /* DEM_SIT_RANGE_CHECK */
        /* Change Dem_TSFFDNvMStatus */
        recMngCmnKindTSFFD = Dem_RecMngCmnKindTSFFD;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindTSFFD, ( Dem_u16_RecordIndexType )TimeSeriesFreezeFrameIndex );
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_SetAfterTimeSeriesFreezeFrameRecord         */
/* Description   | Set the captured FreezeFrame data, fault occurrence ind- */
/*               | ex, and storage status of the time series FreezeFrame r- */
/*               | ecord specified in the time series FreezeFrame record l- */
/*               | ist corresponding to the designated time series FreezeF- */
/*               | rame index.(for Dem_DataCtl subunit)                     */
/* Preconditions |                                                          */
/* Parameters    | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        Time Series FreezeFrame Index.                    */
/*               | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the specific ev- */
/*               |        ent record.                                       */
/*               | [in] ConsistencyId :                                     */
/*               |        The ID for consistency between with trigger FFD.  */
/*               | [in] SamplingRecordStatus :                              */
/*               |        The record status of the sampling freeze frame r- */
/*               |        ecord.                                            */
/*               | [in] SamplingFreezeFrameRecordDataStartPtr :             */
/*               |        The pointer of data start of the sampling freeze  */
/*               |        frame record.                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_SetAfterTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId,
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) SamplingRecordStatus,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) SamplingFreezeFrameRecordDataStartPtr
)
{
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffTotalTimeseriesFFRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) tsFFRecordMaxLength;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindTSFFD;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    tsffTotalTimeseriesFFRecordNum = Dem_TSFFTotalTimeseriesFFRecordNum;

    if( TimeSeriesFreezeFrameIndex < tsffTotalTimeseriesFFRecordNum )                           /* [GUD:if]TimeSeriesFreezeFrameIndex */
    {
        tsFFRecordMaxLength = Dem_TSFFRecordMaxLength;

#ifndef DEM_SIT_RANGE_CHECK
        Dem_DataMng_SetCapturedFreezeFrame( &Dem_TimeSeriesFreezeFrameDataPosTable, ConsistencyId, EventStrgIndex, SamplingRecordStatus, SamplingFreezeFrameRecordDataStartPtr, tsFFRecordMaxLength, Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data );    /* [GUD]TimeSeriesFreezeFrameIndex */
#else   /* DEM_SIT_RANGE_CHECK */
        Dem_DataMng_SetCapturedFreezeFrame( DEM_TSFF_STORED_FORMAT_SIZE, &Dem_TimeSeriesFreezeFrameDataPosTable, ConsistencyId, EventStrgIndex, SamplingRecordStatus, SamplingFreezeFrameRecordDataStartPtr, tsFFRecordMaxLength, Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data );    /* [GUD]TimeSeriesFreezeFrameIndex */
#endif  /* DEM_SIT_RANGE_CHECK */
        /* Change Dem_TSFFDNvMStatus */
        recMngCmnKindTSFFD = Dem_RecMngCmnKindTSFFD;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindTSFFD, ( Dem_u16_RecordIndexType )TimeSeriesFreezeFrameIndex );
        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_GetRecordStatusOfTimeSeriesFreezeFrameRecord*/
/* Description   | Get the storage status from the FreezeFrame record list- */
/*               |  data corresponding to the designated time series Freez- */
/*               | eFrame index.                                            */
/* Preconditions |                                                          */
/* Parameters    | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        Time Series FreezeFrame Index.                    */
/* Return Value  | Dem_u08_FFStoredStatusType                               */
/*               |        DEM_FFD_NOT_STORED : Not Stored                   */
/*               |        DEM_FFD_STORED     : Stored                       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FFStoredStatusType, DEM_CODE ) Dem_DataMngC_GetRecordStatusOfTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) recordStatus;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffTotalTimeseriesFFRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;

    recordStatus = DEM_FFD_NOT_STORED;
    tsffTotalTimeseriesFFRecordNum = Dem_TSFFTotalTimeseriesFFRecordNum;

    if( TimeSeriesFreezeFrameIndex < tsffTotalTimeseriesFFRecordNum )                           /* [GUD:if]TimeSeriesFreezeFrameIndex */
    {
        posRecordStatus = Dem_TimeSeriesFreezeFrameDataPosTable.RecordStatus;                                   /* [GUD:CFG]posRecordStatus */
        recordStatus = Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posRecordStatus];   /* [GUD]TimeSeriesFreezeFrameIndex *//* [GUD]posRecordStatus */
    }
    else
    {
        /* No process */
    }
    return recordStatus;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_SetRecordStatusToStoredOfBeforeTSFFD        */
/* Description   | Set the storage status to stored from the FreezeFrame r- */
/*               | ecord list data corresponding to the designated before - */
/*               | time series FreezeFrame index.                           */
/* Preconditions |                                                          */
/* Parameters    | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        Time Series FreezeFrame Index.                    */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMngC_SetRecordStatusToStoredOfBeforeTSFFD
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
)
{
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffTotalTimeseriesFFRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;

    tsffTotalTimeseriesFFRecordNum = Dem_TSFFTotalTimeseriesFFRecordNum;

    if( TimeSeriesFreezeFrameIndex < tsffTotalTimeseriesFFRecordNum )                           /* [GUD:if]TimeSeriesFreezeFrameIndex */
    {
        posRecordStatus = Dem_TimeSeriesFreezeFrameDataPosTable.RecordStatus;                                   /* [GUD:CFG]posRecordStatus */
        Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posRecordStatus] = DEM_FFD_STORED; /* [GUD]TimeSeriesFreezeFrameIndex *//* [GUD]posRecordStatus */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_ClearTimeSeriesFreezeFrameRecord            */
/* Description   | Get the data body of the time series FreezeFrameList re- */
/*               | cord from the FreezeFrameList record list corresponding- */
/*               |  to the specified FreezeFrameList index.                 */
/* Preconditions |                                                          */
/* Parameters    | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        Time Series FreezeFrame Index.                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_ClearTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffTotalTimeseriesFFRecordNum;

    retVal = DEM_IRT_NG;
    tsffTotalTimeseriesFFRecordNum = Dem_TSFFTotalTimeseriesFFRecordNum;

    if( TimeSeriesFreezeFrameIndex < tsffTotalTimeseriesFFRecordNum )                           /* [GUD:if]TimeSeriesFreezeFrameIndex */
    {
        (void)Dem_DataMng_ClearTimeSeriesFreezeFrameRecord( TimeSeriesFreezeFrameIndex );   /* no return check required */

        retVal = DEM_IRT_OK;
    }
    else
    {
        /* No process */
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMngC_GetTimeSeriesFreezeFrameRecord              */
/* Description   | To get the time-series FreezeFrame record at the specif- */
/*               | ied position from the time series FreezeFrame record li- */
/*               | st.(for Dem_DataCtl subunit)                             */
/* Preconditions |                                                          */
/* Parameters    | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        Time Series FreezeFrame Index.                    */
/*               | [out] TimeSeriesFreezeFrameRecordPtr :                   */
/*               |        Time Series FreezeFrame Record pointer.(for Dem_- */
/*               |        DataCtl subunit)                                  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMngC_GetTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameRecordPtr
)
{
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffTotalTimeseriesFFRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstCid;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;
    tsffTotalTimeseriesFFRecordNum = Dem_TSFFTotalTimeseriesFFRecordNum;

    if( TimeSeriesFreezeFrameIndex < tsffTotalTimeseriesFFRecordNum )                                   /* [GUD:if]TimeSeriesFreezeFrameIndex */
    {
        posFirstCid = Dem_TimeSeriesFreezeFrameDataPosTable.FirstCID;                                   /* [GUD:CFG]posFirstCid */
        posFirstEventStrgIndexUpper = Dem_TimeSeriesFreezeFrameDataPosTable.FirstEventStrgIndexUpper;   /* [GUD:CFG]posFirstEventStrgIndexUpper */
        posFirstEventStrgIndexLower = Dem_TimeSeriesFreezeFrameDataPosTable.FirstEventStrgIndexLower;   /* [GUD:CFG]posFirstEventStrgIndexLower */
        posRecordStatus = Dem_TimeSeriesFreezeFrameDataPosTable.RecordStatus;                           /* [GUD:CFG]posRecordStatus */
        posDataStart = Dem_TimeSeriesFreezeFrameDataPosTable.DataStart;                                 /* [GUD:CFG]posDataStart */

        TimeSeriesFreezeFrameRecordPtr->ConsistencyId = Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posFirstCid];      /* [GUD]TimeSeriesFreezeFrameIndex *//* [GUD]posFirstCid */
        eventStrgIndex = (Dem_u16_EventStrgIndexType)Dem_UtlMem_ConvertByteData( Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posFirstEventStrgIndexUpper], Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posFirstEventStrgIndexLower] );/* [GUD]TimeSeriesFreezeFrameIndex *//* [GUD]posFirstEventStrgIndexUpper *//* [GUD]posFirstEventStrgIndexLower */
        TimeSeriesFreezeFrameRecordPtr->EventStrgIndex = eventStrgIndex;
        TimeSeriesFreezeFrameRecordPtr->RecordStatus = Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posRecordStatus];   /* [GUD]TimeSeriesFreezeFrameIndex *//* [GUD]posRecordStatus */
        TimeSeriesFreezeFrameRecordPtr->DataPtr = &Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posDataStart];          /* [GUD]TimeSeriesFreezeFrameIndex *//* [GUD]posDataStart */

        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DataMng_ClearTimeSeriesFreezeFrameRecord             */
/* Description   | Initializes the fault index and the record status of the */
/*               | specified record of time-series freeze frame record list.*/
/* Preconditions |                                                          */
/* Parameters    | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        The FreezeFrame index corresponding to the speci- */
/*               |        fic FreezeFrame record.                           */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_ClearTimeSeriesFreezeFrameRecord
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex
)
{
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffTotalTimeseriesFFRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posRecordStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( uint8, AUTOMATIC ) eventStrgIndexUpper;
    VAR( uint8, AUTOMATIC ) eventStrgIndexLower;

    retVal = DEM_IRT_OK;
    tsffTotalTimeseriesFFRecordNum = Dem_TSFFTotalTimeseriesFFRecordNum;

    /* Checks the range of the specified index.*/
    if( TimeSeriesFreezeFrameIndex < tsffTotalTimeseriesFFRecordNum )                                   /* [GUD:if]TimeSeriesFreezeFrameIndex */
    {
        posFirstEventStrgIndexUpper = Dem_TimeSeriesFreezeFrameDataPosTable.FirstEventStrgIndexUpper;   /* [GUD:CFG]posFirstEventStrgIndexUpper */
        posFirstEventStrgIndexLower = Dem_TimeSeriesFreezeFrameDataPosTable.FirstEventStrgIndexLower;   /* [GUD:CFG]posFirstEventStrgIndexLower */
        posLastEventStrgIndexUpper = Dem_TimeSeriesFreezeFrameDataPosTable.LastEventStrgIndexUpper;     /* [GUD:CFG]posLastEventStrgIndexUpper */
        posLastEventStrgIndexLower = Dem_TimeSeriesFreezeFrameDataPosTable.LastEventStrgIndexLower;     /* [GUD:CFG]posLastEventStrgIndexLower */
        posRecordStatus = Dem_TimeSeriesFreezeFrameDataPosTable.RecordStatus;                           /* [GUD:CFG]posRecordStatus */

        /* Sets "not stored" to the record status of the specified time-series freeze frame record. */
        Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posRecordStatus] = DEM_FFD_NOT_STORED;                 /* [GUD]TimeSeriesFreezeFrameIndex *//* [GUD]posRecordStatus */

        /* Sets the initial value to the event index of the specified time-series freeze frame record. */
        Dem_UtlMem_SplitByteData( (uint16)DEM_EVENTSTRGINDEX_INVALID, &eventStrgIndexUpper, &eventStrgIndexLower );
        Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posFirstEventStrgIndexUpper] = eventStrgIndexUpper;    /* [GUD]TimeSeriesFreezeFrameIndex *//* [GUD]posFirstEventStrgIndexUpper */
        Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posFirstEventStrgIndexLower] = eventStrgIndexLower;    /* [GUD]TimeSeriesFreezeFrameIndex *//* [GUD]posFirstEventStrgIndexLower */
        Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posLastEventStrgIndexUpper] = eventStrgIndexUpper;     /* [GUD]TimeSeriesFreezeFrameIndex *//* [GUD]posLastEventStrgIndexUpper */
        Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posLastEventStrgIndexLower] = eventStrgIndexLower;     /* [GUD]TimeSeriesFreezeFrameIndex *//* [GUD]posLastEventStrgIndexLower */
    }
    else
    {
        retVal = DEM_IRT_NG;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_TSFFDMng_Init                                        */
/* Description   | Init process of TSFFD.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_TSFFDMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffTotalTimeseriesFFRecordNum;

    tsffTotalTimeseriesFFRecordNum = Dem_TSFFTotalTimeseriesFFRecordNum;

    for( tsffIndex = (Dem_u16_TSFFDIndexType)0U; tsffIndex < tsffTotalTimeseriesFFRecordNum; tsffIndex++ )  /* [GUD:for]tsffIndex */
    {
        Dem_TSFFDNvMStatus[ tsffIndex ] = DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED;                               /* [GUD]tsffIndex */
    }

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_TSFFDMng_InitMirrorMemory();
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

    return;
}

/****************************************************************************/
/* Function Name | Dem_TSFFDMng_InitSavedZone                               */
/* Description   | Initialize savedzone process of TSFFD.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |          Initialize savedzone type                       */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_TSFFDMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffTotalTimeseriesFFRecordNum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) tsffStoredFormatSize;

    tsffTotalTimeseriesFFRecordNum = Dem_TSFFTotalTimeseriesFFRecordNum;
    tsffStoredFormatSize = Dem_TSFFStoredFormatSize;

    for( tsffIndex = (Dem_u16_TSFFDIndexType)0U; tsffIndex < tsffTotalTimeseriesFFRecordNum; tsffIndex++ )                      /* [GUD:for]tsffIndex */
    {
        Dem_UtlMem_SetMemory( &Dem_TimeSeriesFreezeFrameRecordList[tsffIndex].Data[0], DEM_FFD_INITIAL, tsffStoredFormatSize ); /* [GUD]tsffIndex */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_TSFFDMng_DataVerify                                  */
/* Description   | Verifies TSFFD data.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_TSFFDMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    /* No Process */
    return DEM_IRT_OK;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_TSFFDMng_SetRecordMirror                             */
/* Description   | Copy to the Mirror Memory.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_TSFFDMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) tsffdStorageFormatsize;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) tsffdDataIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffTotalTimeseriesFFRecordNum;

    tsffdStorageFormatsize = Dem_TSFFStoredFormatSize;
    tsffTotalTimeseriesFFRecordNum = Dem_TSFFTotalTimeseriesFFRecordNum;

    if( BlockMirrorPtr->RecordDataOffset == (Dem_u16_RecordDataSizeType)0U )
    {
        if( BlockMirrorPtr->RecordIndex < tsffTotalTimeseriesFFRecordNum )          /* [GUD:if]BlockMirrorPtr->RecordIndex */
        {
            /* copy data to mirror area. */
            Dem_UtlMem_CopyMemory( &Dem_TmpTSFFDMirror.Data[0], &(Dem_TimeSeriesFreezeFrameRecordList[BlockMirrorPtr->RecordIndex].Data[0]), tsffdStorageFormatsize );  /* [GUD]BlockMirrorPtr->RecordIndex */
        }
    }

    tsffdDataIndex = Dem_TSFFRecordNvBlockSize * BlockMirrorPtr->RecordDataOffset;
    if( tsffdDataIndex < tsffdStorageFormatsize )                                   /* [GUD:if]tsffdDataIndex */
    {
        BlockMirrorPtr->MirrorPtr = &Dem_TmpTSFFDMirror.Data[ tsffdDataIndex ];     /* [GUD]tsffdDataIndex */
    }

    return;
}

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/****************************************************************************/
/* Function Name | Dem_TSFFDMng_Verified                                    */
/* Description   | Make time series freeze frame verified.                  */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex : event index.                       */
/*               | [in] FaultIndex : Fault index.                           */
/*               | [in] FaultRecordPtr : Fault record.                      */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_TSFFDMng_Verified
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex             /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) indexOfTSFFListIndex;
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListRecIndex;
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) tsffRecordClassNumPerDTCMaxNum;
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) tsFFRecClassRef;
    VAR( Dem_u08_TSFFClassIndexType, AUTOMATIC ) tsFFClassRef;
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) numOfBeforeTSFFRecord;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) triggerFreezeFrameIndex;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) tsFFTrigger;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) triggerFFDConsystencyId;
    VAR( Dem_FaultRecordPtrForCtlType, AUTOMATIC ) faultRecordPtrCtl;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retChkExistTrigger;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindFault;
    VAR( boolean, AUTOMATIC ) tsFFListIndexInitFlg;
    VAR( boolean, AUTOMATIC ) setNvMWriteFlg;

    tsffRecordClassNumPerDTCMaxNum = Dem_TSFFRecordClassNumPerDTCMaxNum;
    setNvMWriteFlg = (boolean)FALSE;

    dtcAttributePtr    =   Dem_CfgInfoPm_GetDTCAttrTablePtr_TSFF( EventStrgIndex ); /* [GUD:RET:Not NULL_PTR]dtcAttributePtr */

    if ( dtcAttributePtr != NULL_PTR )                                              /* [GUD:if]dtcAttributePtr */
    {
        for( indexOfTSFFListIndex = (Dem_u08_TSFFListPerDTCIndexType)0U; indexOfTSFFListIndex < tsffRecordClassNumPerDTCMaxNum; indexOfTSFFListIndex++ )    /* [GUD:for]indexOfTSFFListIndex */
        {
            tsFFListRecIndex = DEM_INVALID_VACANT_TSFFLIST_INDEX;
            (void)Dem_DataMngC_GetFR_TSFFListIndex( FaultIndex, indexOfTSFFListIndex, &tsFFListRecIndex );    /* no return check required */    /* [GUD]indexOfTSFFListIndex */
            if( tsFFListRecIndex != DEM_INVALID_TSFF_RECORD_INDEX )
            {
                tsFFRecClassRef = dtcAttributePtr->DemTimeSeriesFreezeFrameRecordClassRef[indexOfTSFFListIndex];                            /* [GUD]dtcAttributePtr *//* [GUD]indexOfTSFFListIndex *//* [GUD:CFG:IF_GUARDED: indexOfTSFFListIndex ]tsFFRecClassRef *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / indexOfTSFFListIndex */
                tsFFTrigger = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameTrigger;                                    /* [GUD]tsFFRecClassRef */

                (void)Dem_DataMngC_GetFaultRecordAddress_TSFF( FaultIndex, &faultRecordPtrCtl );        /* no return check required */
                retChkExistTrigger = Dem_FFDMng_CheckToExistTriggerFFD( tsFFTrigger, dtcAttributePtr, faultRecordPtrCtl.FaultRecordPtr, &triggerFreezeFrameIndex ); /* [GUD]dtcAttributePtr */

                if( retChkExistTrigger == DEM_IRT_OK )
                {
                    triggerFFDConsystencyId = Dem_FFDMng_GetFFDConsystencyId( triggerFreezeFrameIndex );
                    tsFFClassRef = Dem_TSFFRecordClassTable[tsFFRecClassRef].DemTimeSeriesFreezeFrameClassRef;                              /* [GUD]tsFFRecClassRef *//* [GUD:CFG:IF_GUARDED: tsFFRecClassRef ]tsFFClassRef */
                    numOfBeforeTSFFRecord = Dem_TSFFClassTable[tsFFClassRef].DemNumberOfBeforeTriggeredRecord;                              /* [GUD]tsFFClassRef */
                    tsFFListIndexInitFlg = (boolean)FALSE;
                    Dem_TSFFDMng_VerifiedRecord( tsFFListRecIndex, triggerFFDConsystencyId, numOfBeforeTSFFRecord, EventStrgIndex, &tsFFListIndexInitFlg );
                }
                else
                {
                    tsFFListIndexInitFlg = (boolean)TRUE;
                }

                if( tsFFListIndexInitFlg == (boolean)TRUE )
                {
                    Dem_DataMng_InitSpecificTSFFListRecordData( FaultIndex, indexOfTSFFListIndex ); /* [GUDCHK:CALLER]FaultIndex *//* [GUD]indexOfTSFFListIndex */
                    setNvMWriteFlg = (boolean)TRUE;
                }
            }
        }

        if( setNvMWriteFlg == (boolean)TRUE )
        {
            recMngCmnKindFault = Dem_RecMngCmnKindFault;
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindFault, ( Dem_u16_RecordIndexType )FaultIndex );
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_TSFFDMng_VerifiedRecord                              */
/* Description   | Make time series freeze frame record verified.           */
/* Preconditions |                                                          */
/* Parameters    | [in] TimeSeriesFreezeFrameListRecordIndex :              */
/*               |        The index of TimeSeriesFreezeFrmaeList record co- */
/*               |        rresponding to fault record.                      */
/*               | [in] TriggerFFDConsystencyId :                           */
/*               |        The consistency Id of trigger FFD                 */
/*               | [in] NumOfBeforeTSFFRecord :                             */
/*               |        The number of before TSFFD                        */
/*               | [in] EventStrgIndex :                                    */
/*               |        The event index                                   */
/*               | [out] TSFFListIndexInitFlg :                             */
/*               |        The TSFFList index of fault record initializatio- */
/*               |        n flag                                            */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_TSFFDMng_VerifiedRecord
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListRecordIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) TriggerFFDConsystencyId,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumOfBeforeTSFFRecord,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) TSFFListIndexInitFlg
)
{
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsffTotalDTCNum;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFreezeFrameStoredCnt;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVerifyBeforeTSFFD;

    tsffTotalDTCNum = Dem_TSFFTotalDTCNum;

    if( TimeSeriesFreezeFrameListRecordIndex < tsffTotalDTCNum )                            /* [GUD:if]TimeSeriesFreezeFrameListRecordIndex */
    {
        tsFreezeFrameStoredCnt = (Dem_u16_TSFFDIndexType)0U;
        retVerifyBeforeTSFFD = Dem_TSFFDMng_VerifiedBeforeTSFFD( TimeSeriesFreezeFrameListRecordIndex, TriggerFFDConsystencyId, NumOfBeforeTSFFRecord, EventStrgIndex, &tsFreezeFrameStoredCnt );   /* [GUD]TimeSeriesFreezeFrameListRecordIndex */

        if( retVerifyBeforeTSFFD == DEM_IRT_OK )
        {
            Dem_TSFFDMng_VerifiedAfterTSFFD( TimeSeriesFreezeFrameListRecordIndex, TriggerFFDConsystencyId, NumOfBeforeTSFFRecord, EventStrgIndex, &tsFreezeFrameStoredCnt );                       /* [GUD]TimeSeriesFreezeFrameListRecordIndex */
        }

        if( tsFreezeFrameStoredCnt == (Dem_u16_TSFFDIndexType)0U )
        {
            *TSFFListIndexInitFlg = (boolean)TRUE;
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_TSFFDMng_VerifiedBeforeTSFFD                         */
/* Description   | Make time series freeze frame record verified.           */
/* Preconditions |                                                          */
/* Parameters    | [in] TimeSeriesFreezeFrameListRecordIndex :              */
/*               |        The index of TimeSeriesFreezeFrmaeList record co- */
/*               |        rresponding to fault record.                      */
/*               | [in] TriggerFFDConsystencyId :                           */
/*               |        The consistency Id of trigger FFD                 */
/*               | [in] NumOfBeforeTSFFRecord :                             */
/*               |        The number of before TSFFD                        */
/*               | [in] EventStrgIndex :                                    */
/*               |        The event index                                   */
/*               | [out] TSFreezeFrameStoredCntPtr :                        */
/*               |        Counter of valid time series freeze frame data    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_TSFFDMng_VerifiedBeforeTSFFD
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListRecordIndex,   /* [PRMCHK:CALLER] */
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) TriggerFFDConsystencyId,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumOfBeforeTSFFRecord,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFreezeFrameStoredCntPtr
)
{
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecIndex;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) recordStatus;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecStartIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) beforeTSFFRecEndIndex;
    VAR( boolean, AUTOMATIC ) existStoredTSFFDFlg;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) verifyNGIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVerifyRecord;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_OK;

    if( NumOfBeforeTSFFRecord > (Dem_u08_NumOfTSFFType)0U )
    {
        tsFFRecStartIndex = Dem_TimeSeriesFreezeFrameTable[TimeSeriesFreezeFrameListRecordIndex].DemStartIndex; /* [GUDCHK:CALLER]TimeSeriesFreezeFrameListRecordIndex *//* [GUD:CFG:IF_GUARDED: TimeSeriesFreezeFrameListRecordIndex ]tsFFRecStartIndex */
        beforeTSFFRecEndIndex = ( tsFFRecStartIndex + NumOfBeforeTSFFRecord ) - (Dem_u16_TSFFDIndexType)1U;

        verifyNGIndex = DEM_TSFFDINDEX_INVALID;
        existStoredTSFFDFlg = (boolean)FALSE;

        for( tsFFRecIndex = tsFFRecStartIndex; tsFFRecIndex <= beforeTSFFRecEndIndex; tsFFRecIndex++ )          /* [GUD:for]tsFFRecIndex */
        {
            recordStatus = Dem_DataMngC_GetRecordStatusOfTimeSeriesFreezeFrameRecord( tsFFRecIndex );           /* [GUD]tsFFRecIndex */
            if( recordStatus == DEM_FFD_STORED )
            {
                retVerifyRecord = Dem_TSFFDMng_CheckConsistency( tsFFRecIndex, EventStrgIndex, TriggerFFDConsystencyId );

                if( retVerifyRecord == DEM_IRT_OK )
                {
                    existStoredTSFFDFlg = (boolean)TRUE;
                    *TSFreezeFrameStoredCntPtr = *TSFreezeFrameStoredCntPtr + (Dem_u16_TSFFDIndexType)1U;
                    Dem_TSFFDNvMStatus[ tsFFRecIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;                      /* [GUD]tsFFRecIndex */
                }
                else
                {
                    verifyNGIndex = tsFFRecIndex;
                }
            }
            else
            {
                if( existStoredTSFFDFlg == (boolean)TRUE )
                {
                    verifyNGIndex = tsFFRecIndex;
                }
            }

            if( verifyNGIndex != DEM_TSFFDINDEX_INVALID )
            {
                retVal = DEM_IRT_NG;
                break;
            }
        }

        if( retVal == DEM_IRT_NG )
        {
            /* revert before TSFFD NvMstatus to not verified status */
            for( tsFFRecIndex = tsFFRecStartIndex; tsFFRecIndex < verifyNGIndex; tsFFRecIndex++ )       /* [GUD:for]tsFFRecIndex */
            {
                Dem_TSFFDNvMStatus[ tsFFRecIndex ] = DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED;                /* [GUD]tsFFRecIndex */
            }

            *TSFreezeFrameStoredCntPtr = (Dem_u16_TSFFDIndexType)0U;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_TSFFDMng_VerifiedAfterTSFFD                          */
/* Description   | Make time series freeze frame record verified.           */
/* Preconditions |                                                          */
/* Parameters    | [in] TimeSeriesFreezeFrameListRecordIndex :              */
/*               |        The index of TimeSeriesFreezeFrmaeList record co- */
/*               |        rresponding to fault record.                      */
/*               | [in] TriggerFFDConsystencyId :                           */
/*               |        The consistency Id of trigger FFD                 */
/*               | [in] NumOfBeforeTSFFRecord :                             */
/*               |        The number of before TSFFD                        */
/*               | [in] EventStrgIndex :                                    */
/*               |        The event index                                   */
/*               | [out] TSFreezeFrameStoredCntPtr :                        */
/*               |        Counter of valid time series freeze frame data    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_TSFFDMng_VerifiedAfterTSFFD
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListRecordIndex,   /* [PRMCHK:CALLER] */
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) TriggerFFDConsystencyId,
    VAR( Dem_u08_NumOfTSFFType, AUTOMATIC ) NumOfBeforeTSFFRecord,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u16_TSFFDIndexType, AUTOMATIC, AUTOMATIC ) TSFreezeFrameStoredCntPtr
)
{
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) afterTSFFRecStartIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecEndIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsFFRecIndex;
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) recordStatus;
    VAR( boolean, AUTOMATIC ) loopEndFlg;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVerifyRecord;

    afterTSFFRecStartIndex = Dem_TimeSeriesFreezeFrameTable[TimeSeriesFreezeFrameListRecordIndex].DemStartIndex + NumOfBeforeTSFFRecord;    /* [GUDCHK:CALLER]TimeSeriesFreezeFrameListRecordIndex *//* [GUD:CFG:IF_GUARDED: TimeSeriesFreezeFrameListRecordIndex ]afterTSFFRecStartIndex */
    tsFFRecEndIndex = Dem_TimeSeriesFreezeFrameTable[TimeSeriesFreezeFrameListRecordIndex].DemEndIndex;                                     /* [GUDCHK:CALLER]TimeSeriesFreezeFrameListRecordIndex *//* [GUD:CFG:IF_GUARDED: TimeSeriesFreezeFrameListRecordIndex ]tsFFRecEndIndex */

    loopEndFlg = (boolean)FALSE;

    for( tsFFRecIndex = afterTSFFRecStartIndex; tsFFRecIndex <= tsFFRecEndIndex; tsFFRecIndex++ )       /* [GUD:for]tsFFRecIndex */
    {
        recordStatus = Dem_DataMngC_GetRecordStatusOfTimeSeriesFreezeFrameRecord( tsFFRecIndex );       /* [GUD]tsFFRecIndex */
        if( recordStatus == DEM_FFD_STORED )
        {
            retVerifyRecord = Dem_TSFFDMng_CheckConsistency( tsFFRecIndex, EventStrgIndex, TriggerFFDConsystencyId );
            if( retVerifyRecord == DEM_IRT_OK )
            {
                *TSFreezeFrameStoredCntPtr = *TSFreezeFrameStoredCntPtr + (Dem_u16_TSFFDIndexType)1U;
                Dem_TSFFDNvMStatus[ tsFFRecIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;                  /* [GUD]tsFFRecIndex */
            }
            else
            {
                loopEndFlg = (boolean)TRUE;
            }
        }
        else
        {
            loopEndFlg = (boolean)TRUE;
        }

        if( loopEndFlg == (boolean)TRUE  )
        {
            break;
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_TSFFDMng_CheckConsistency                            */
/* Description   | Make time series freeze frame record verified.           */
/* Preconditions |                                                          */
/* Parameters    | [in] TimeSeriesFreezeFrameListRecordIndex :              */
/*               |        The index of TimeSeriesFreezeFrmaeList record co- */
/*               |        rresponding to fault record.                      */
/*               | [in] EventStrgIndex : The event index                    */
/*               | [in] TriggerFFDConsystencyId :                           */
/*               |               The consystency id of trigger freeze frame */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_TSFFDMng_CheckConsistency
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) TriggerFFDConsystencyId
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) firstBlockEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) lastBlockEventStrgIndex;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) firstBlockCId;
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) lastBlockCId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    Dem_TSFFDMng_GetFFDConsistencyInfo( TimeSeriesFreezeFrameIndex, &firstBlockCId, &lastBlockCId, &firstBlockEventStrgIndex, &lastBlockEventStrgIndex );   /* [GUDCHK:CALLER]TimeSeriesFreezeFrameIndex */

    if( EventStrgIndex == firstBlockEventStrgIndex )
    {
        if( TriggerFFDConsystencyId == firstBlockCId )
        {
            if( firstBlockEventStrgIndex == lastBlockEventStrgIndex )
            {
                if( firstBlockCId == lastBlockCId )
                {
                    retVal = Dem_TSFFDMng_VerifyChecksum( TimeSeriesFreezeFrameIndex );     /* [GUDCHK:CALLER]TimeSeriesFreezeFrameIndex */
                }
            }
        }
    }

    return retVal;
}


#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_TSFFDMng_VerifyChecksum                              */
/* Description   | verify checksum of TSFFD record                          */
/* Preconditions |                                                          */
/* Parameters    | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |       The time series freeze frame index                 */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This checksum is consistency.        */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_TSFFDMng_VerifyChecksum
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) registeredChecksum;
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) calculatedChecksum;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) tsFFRecordMaxLength;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posDataStart;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    tsFFRecordMaxLength = Dem_TSFFRecordMaxLength;
    posDataStart = Dem_TimeSeriesFreezeFrameDataPosTable.DataStart;             /* [GUD:CFG]posDataStart */
    retVal = DEM_IRT_NG;

    registeredChecksum = Dem_TSFFDMng_GetChecksum( TimeSeriesFreezeFrameIndex );    /* [GUDCHK:CALLER]TimeSeriesFreezeFrameIndex */
    calculatedChecksum = Dem_UtlMem_Checksum( &Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posDataStart], tsFFRecordMaxLength );   /* [GUDCHK:CALLER]TimeSeriesFreezeFrameIndex *//* [GUD]posDataStart */

    if( registeredChecksum == calculatedChecksum )
    {
        retVal = DEM_IRT_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_TSFFDMng_GetChecksum                                 */
/* Description   | get checksum in TSFFD record                             */
/* Preconditions |                                                          */
/* Parameters    | [in] TimeSeriesFreezeFrameIndex : The freeze frame index */
/* Return Value  | uin16 :                                                  */
/*               |       The checksum value                                 */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u16_FFCheckSumType, DEM_CODE ) Dem_TSFFDMng_GetChecksum
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex     /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posChecksumLower;
    VAR( uint8, AUTOMATIC ) checksumUpper;
    VAR( uint8, AUTOMATIC ) checksumLower;
    VAR( Dem_u16_FFCheckSumType, AUTOMATIC ) checksum;

    posChecksumUpper = Dem_TimeSeriesFreezeFrameDataPosTable.ChecksumUpper;     /* [GUD:CFG]posChecksumUpper */
    posChecksumLower = Dem_TimeSeriesFreezeFrameDataPosTable.ChecksumLower;     /* [GUD:CFG]posChecksumLower */

    checksumUpper = Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posChecksumUpper]; /* [GUDCHK:CALLER]TimeSeriesFreezeFrameIndex *//* [GUD]posChecksumUpper */
    checksumLower = Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posChecksumLower]; /* [GUDCHK:CALLER]TimeSeriesFreezeFrameIndex *//* [GUD]posChecksumLower */

    checksum = (Dem_u16_FFCheckSumType)checksumUpper << DEM_DATAMNG_CHECKSUM_SHIFT;
    checksum |= (Dem_u16_FFCheckSumType)checksumLower;

    return checksum;
}
#endif /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON ) */


#if ( DEM_FF_CHECKSUM_SUPPORT == STD_OFF )
/****************************************************************************/
/* Function Name | Dem_TSFFDMng_VerifyChecksum                              */
/* Description   | verify checksum of TSFFD record                          */
/* Preconditions |                                                          */
/* Parameters    | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |       The time series freeze frame index                 */
/* Return Value  | Dem_u08_InternalReturnType :                             */
/*               |       DEM_IRT_OK  : This checksum is consistency.        */
/*               |       DEM_IRT_NG  : This checksum is inconsistency.      */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_TSFFDMng_VerifyChecksum
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex    /* MISRA DEVIATION */
)
{
    return DEM_IRT_OK;
}
#endif /* ( DEM_FF_CHECKSUM_SUPPORT == STD_OFF ) */


/****************************************************************************/
/* Function Name | Dem_TSFFDMng_GetTSFFDConsistencyInfo                     */
/* Description   | check consistency of FFD record                          */
/* Preconditions |                                                          */
/* Parameters    | [in] TimeSeriesFreezeFrameIndex :                        */
/*               |        The Time Series FreezeFrame Index                 */
/*               | [out] FirstBlockCIdPtr :                                 */
/*               |        The pointer of ConsistencyId of first block       */
/*               | [out] LastBlockCIdPtr :                                  */
/*               |        The pointer of ConsistencyId of last block        */
/*               | [out] FirstBlockEventStrgIndexPtr :                      */
/*               |        The pointer of EventStrgIndex of first block      */
/*               | [out] LastBlockEventStrgIndexPtr :                       */
/*               |        The pointer of EventStrgIndex of last block       */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_TSFFDMng_GetFFDConsistencyInfo
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,        /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) FirstBlockCIdPtr,
    P2VAR( Dem_u08_ConsistencyIdType, AUTOMATIC, AUTOMATIC ) LastBlockCIdPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) FirstBlockEventStrgIndexPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) LastBlockEventStrgIndexPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstCid;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastCid;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) firstEventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) lastEventStrgIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posFirstEventStrgIndexLower;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexUpper;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) posLastEventStrgIndexLower;

    posFirstCid = Dem_TimeSeriesFreezeFrameDataPosTable.FirstCID;                                   /* [GUD:CFG]posFirstCid */
    posLastCid = Dem_TimeSeriesFreezeFrameDataPosTable.LastCID;                                     /* [GUD:CFG]posLastCid */
    posFirstEventStrgIndexUpper = Dem_TimeSeriesFreezeFrameDataPosTable.FirstEventStrgIndexUpper;   /* [GUD:CFG]posFirstEventStrgIndexUpper */
    posFirstEventStrgIndexLower = Dem_TimeSeriesFreezeFrameDataPosTable.FirstEventStrgIndexLower;   /* [GUD:CFG]posFirstEventStrgIndexLower */
    posLastEventStrgIndexUpper = Dem_TimeSeriesFreezeFrameDataPosTable.LastEventStrgIndexUpper;     /* [GUD:CFG]posLastEventStrgIndexUpper */
    posLastEventStrgIndexLower = Dem_TimeSeriesFreezeFrameDataPosTable.LastEventStrgIndexLower;     /* [GUD:CFG]posLastEventStrgIndexLower */


    *FirstBlockCIdPtr = (Dem_u08_ConsistencyIdType)Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posFirstCid];   /* [GUDCHK:CALLER]TimeSeriesFreezeFrameIndex *//* [GUD]posFirstCid */
    *LastBlockCIdPtr = (Dem_u08_ConsistencyIdType)Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posLastCid];     /* [GUDCHK:CALLER]TimeSeriesFreezeFrameIndex *//* [GUD]posLastCid */
    firstEventStrgIndex = (Dem_u16_EventStrgIndexType)Dem_UtlMem_ConvertByteData( Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posFirstEventStrgIndexUpper], Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posFirstEventStrgIndexLower] );   /* [GUDCHK:CALLER]TimeSeriesFreezeFrameIndex *//* [GUD]posFirstEventStrgIndexUpper *//* [GUD]posFirstEventStrgIndexLower */
    *FirstBlockEventStrgIndexPtr = firstEventStrgIndex;
    lastEventStrgIndex = (Dem_u16_EventStrgIndexType)Dem_UtlMem_ConvertByteData( Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posLastEventStrgIndexUpper], Dem_TimeSeriesFreezeFrameRecordList[TimeSeriesFreezeFrameIndex].Data[posLastEventStrgIndexLower] );      /* [GUDCHK:CALLER]TimeSeriesFreezeFrameIndex *//* [GUD]posLastEventStrgIndexUpper *//* [GUD]posLastEventStrgIndexLower */
    *LastBlockEventStrgIndexPtr = lastEventStrgIndex;

    return;
}


/****************************************************************************/
/* Function Name | Dem_TSFFDMng_ClearAllNotVerifiedRecord                   */
/* Description   | Clear not verrified record.                              */
/* Preconditions |                                                          */
/* Parameters    | [in/out] ClearRecordIndexPtr :                           */
/*               |          target record index                             */
/*               | [in/out] RestOfProcessableNumPtr :                       */
/*               |          rest number of Processable Record               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : Completed.                    */
/*               |          DEM_IRT_PENDING : Continue.                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_TSFFDMng_ClearAllNotVerifiedRecord
(
    P2VAR( Dem_u16_RecordIndexType, AUTOMATIC, AUTOMATIC ) ClearRecordIndexPtr,
    P2VAR( Dem_u32_TotalRecordNumType, AUTOMATIC, AUTOMATIC ) RestOfProcessableNumPtr
)
{
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffTotalTimeseriesFFRecordNum;
    VAR( Dem_u32_TotalRecordNumType, AUTOMATIC ) loopCount;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    tsffTotalTimeseriesFFRecordNum = Dem_TSFFTotalTimeseriesFFRecordNum;
    loopCount = (Dem_u16_TSFFDIndexType)0U;
    retVal = DEM_IRT_OK;

    for( tsffIndex = (Dem_u16_TSFFDIndexType)( *ClearRecordIndexPtr ); tsffIndex < tsffTotalTimeseriesFFRecordNum; tsffIndex++ )    /* [GUD:for]tsffIndex */
    {
        if( loopCount < *RestOfProcessableNumPtr )
        {
            if( Dem_TSFFDNvMStatus[ tsffIndex ] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED )                                             /* [GUD]tsffIndex */
            {
                (void)Dem_DataMng_ClearTimeSeriesFreezeFrameRecord( tsffIndex );   /* no return check required */                   /* [GUD]tsffIndex */
                Dem_TSFFDNvMStatus[ tsffIndex ] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;                                                 /* [GUD]tsffIndex */
            }
            loopCount = loopCount + (Dem_u32_TotalRecordNumType)1U;
        }
        else
        {
            *ClearRecordIndexPtr = (Dem_u16_RecordIndexType)tsffIndex;
            retVal = DEM_IRT_PENDING;
            break;
        }
    }

    if( tsffIndex >= tsffTotalTimeseriesFFRecordNum )
    {
        *RestOfProcessableNumPtr = ( *RestOfProcessableNumPtr ) - loopCount;  /* no wrap around */
    }

    return retVal;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_TSFFDMng_InitMirrorMemory                            */
/* Description   | Initialize the Mirror Memory.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_TSFFDMng_InitMirrorMemory
( void )
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) tsffStoredFormatSize;

    tsffStoredFormatSize = Dem_TSFFStoredFormatSize;
    Dem_UtlMem_SetMemory( &Dem_TmpTSFFDMirror.Data[0], DEM_FFD_INITIAL, tsffStoredFormatSize );

    return;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_TSFFDMng_GetEventIdFromRecordData                    */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RecordFieldIndex :                                 */
/*               | [in]  RecordIndex :                                      */
/*               | [out] EventIdPtr  :                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_TSFFDMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) timeSeriesFreezeFrameIndex;

    eventStrgIndex              =   DEM_EVENTSTRGINDEX_INVALID;
    timeSeriesFreezeFrameIndex  =   ( Dem_u16_TSFFDIndexType )RecordIndex;

    retVal  =   Dem_DataMng_GetEventStrgIndexFromTSFFDRecord( timeSeriesFreezeFrameIndex, &eventStrgIndex );
    if ( retVal == DEM_IRT_OK )
    {
        retVal  =   Dem_DataMng_GetEventIdFromEventStrgIndex( eventStrgIndex, EventIdPtr );
    }

    return retVal;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* (DEM_TSFF_PM_SUPPORT    STD_ON) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
