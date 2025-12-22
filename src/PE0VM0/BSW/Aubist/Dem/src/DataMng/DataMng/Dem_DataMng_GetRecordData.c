/* Dem_DataMng_GetRecordData_c(v5-8-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataMng_GetRecordData/CODE                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "Dem_DataMng_GetRecordData.h"

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

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMng_GetEventIdFromEventStrgIndex                 */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RecordIndex :                                      */
/*               | [out] EventIdPtr  :                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_GetEventIdFromEventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;

    retVal  =   DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    if ( EventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]EventStrgIndex */
    {
        retVal  =   Dem_CfgInfoPm_CnvEventStrgIndexToEventId( EventStrgIndex, EventIdPtr );
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DataMng_GetEventStrgIndexFromFaultRecord             */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  FaultIndex :                                       */
/*               | [out] EventStrgIndexPtr  :                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_GetEventStrgIndexFromFaultRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) failRecordNum;

    retVal = DEM_IRT_NG;
    failRecordNum = Dem_FailRecordNum;

    if( FaultIndex < failRecordNum )
    {
        retVal  =   Dem_DataMngC_GetFR_EventStrgIndex( FaultIndex, EventStrgIndexPtr );
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DataMng_GetEventStrgIndexFromFFDRecord               */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  FreezeFrameIndex :                                 */
/*               | [out] EventStrgIndexPtr  :                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_GetEventStrgIndexFromFFDRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retRecord;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) nonObdFFDRecordNum;
    VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC ) freezeFrameRecord;

    retVal = DEM_IRT_NG;
    nonObdFFDRecordNum = Dem_NonObdFFDRecordNum;

    if( FreezeFrameIndex < nonObdFFDRecordNum )
    {
        retRecord   =   Dem_DataMngC_GetFreezeFrameRecord( FreezeFrameIndex, &freezeFrameRecord );
        if ( retRecord == DEM_IRT_OK )
        {
            if ( freezeFrameRecord.RecordStatus == DEM_FFD_STORED )
            {
                *EventStrgIndexPtr  =   freezeFrameRecord.EventStrgIndex;
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMng_GetEventStrgIndexFromObdFFDRecord            */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  FreezeFrameIndex :                                 */
/*               | [out] EventStrgIndexPtr  :                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_GetEventStrgIndexFromObdFFDRecord
(
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) FreezeFrameIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retRecord;
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) obdFFDRecordNum;
    VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC ) freezeFrameRecord;

    retVal = DEM_IRT_NG;
    obdFFDRecordNum = Dem_CfgInfoPm_GetObdFFDRecordNum();

    if( FreezeFrameIndex < obdFFDRecordNum )
    {
        retRecord   =   Dem_DataMngC_GetObdFreezeFrameRecord( FreezeFrameIndex, &freezeFrameRecord );
        if ( retRecord == DEM_IRT_OK )
        {
            if ( freezeFrameRecord.RecordStatus == DEM_FFD_STORED )
            {
                *EventStrgIndexPtr  =   freezeFrameRecord.EventStrgIndex;
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataMng_GetEventStrgIndexFromTSFFDRecord             */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  TimeSeriesFreezeFrameIndex :                       */
/*               | [out] EventStrgIndexPtr  :                               */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_GetEventStrgIndexFromTSFFDRecord
(
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retRecord;
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) tsffTotalTimeseriesFFRecordNum;
    VAR( Dem_FreezeFrameRecordMngType, AUTOMATIC ) freezeFrameRecord;

    retVal = DEM_IRT_NG;
    tsffTotalTimeseriesFFRecordNum = Dem_TSFFTotalTimeseriesFFRecordNum;

    if( TimeSeriesFreezeFrameIndex < tsffTotalTimeseriesFFRecordNum )
    {
        retRecord   =   Dem_DataMngC_GetTimeSeriesFreezeFrameRecord( TimeSeriesFreezeFrameIndex, &freezeFrameRecord );
        if ( retRecord == DEM_IRT_OK )
        {
            if ( freezeFrameRecord.RecordStatus == DEM_FFD_STORED )
            {
                *EventStrgIndexPtr  =   freezeFrameRecord.EventStrgIndex;
                retVal = DEM_IRT_OK;
            }
        }
    }

    return retVal;
}
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
