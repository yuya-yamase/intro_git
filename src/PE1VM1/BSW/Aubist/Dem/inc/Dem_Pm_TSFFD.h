/* Dem_Pm_TSFFD_h(v5-7-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/Pm_TSFFD/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_PM_TSFFD_H
#define DEM_PM_TSFFD_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_CmnLib_DataCtl_SamplingFFDAccess.h"

#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
#include <Dem_SIT_RangeCheck.h>
#endif /* DEM_SIT_RANGE_CHECK */

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_CaptureAfterTriggeredTSFFFromSample
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) SamplingFFRDataSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u16_TSFFDIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TimeSeriesFreezeFrameTrigger,
    P2CONST( Dem_SamplingFreezeFrameRecordPosType, AUTOMATIC, AUTOMATIC ) SamplingFreezeFrameRecorPosPtr,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) SamplingFreezeFrameRecordDataPtr
);

FUNC( void, DEM_CODE ) Dem_Data_MakeTSFFListRecordList
( void );

#endif  /*  ( DEM_TSFF_PM_SUPPORT == STD_ON )  */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_TSFFD_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
