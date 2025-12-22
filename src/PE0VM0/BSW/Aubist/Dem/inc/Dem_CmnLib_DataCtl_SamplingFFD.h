/* Dem_CmnLib_DataCtl_SamplingFFD_h(v5-3-0)                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/CmnLib_DataCtl_SamplingFFD/HEADER                     */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_CMNLIB_DATACTL_SAMPLINGFFD_H
#define DEM_CMNLIB_DATACTL_SAMPLINGFFD_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_NvM_Cfg.h"

#if ( DEM_TSFF_SUPPORT == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Record for list of sampling freeze frame */
typedef struct
{
    Dem_u16_SmpTSFFDIndexType  CurrentIndex;       /* Index current in sampling freeze frame records */
} Dem_SamplingFreezeFrameListType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_SampleFreezeFrame
(
    VAR( Dem_u16_SmpTSFFRecClassIndexType, AUTOMATIC ) SamplingFreezeFrameTableRef
);

FUNC( void, DEM_CODE ) Dem_Data_CaptureAfterTriggeredTimeSeriesFreezeFrame
(
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameRecordClassRef
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

extern VAR( Dem_SamplingFreezeFrameListType, DEM_VAR_NO_INIT ) Dem_SamplingFreezeFrameListRecordList[DEM_TSFF_SAMPLING_FF_CLASS_CONFIGURE_NUM];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#endif  /* ( DEM_TSFF_SUPPORT == STD_ON ) */

#endif /* DEM_CMNLIB_DATACTL_SAMPLINGFFD_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
