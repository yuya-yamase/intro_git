/* Dem_CmnLib_DataCtl_TSFFD_h(v5-5-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/CmnLib_DataCtl_TSFFD/HEADER                           */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_CMNLIB_DATACTL_TSFFD_H
#define DEM_CMNLIB_DATACTL_TSFFD_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_NvM_Cfg.h"
#include "../inc/Dem_CmnLib_DataCtl.h"

#if ( DEM_TSFF_SUPPORT == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define DEM_TSFFLIST_AFTTRGRECNUM_INVALID   ((uint8)0xFFU)

#define DEM_INVALID_VACANT_TSFFLIST_INDEX                (DEM_TSFFLISTINDEX_INVALID)
#define DEM_INVALID_TSFF_RECORD_INDEX                    (DEM_TSFFLISTINDEX_INVALID)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Record for list of time-series freeze frame */
typedef struct
{
    Dem_u08_FaultIndexType  FaultIndex;                             /* Fault index for fault record list */
    uint8   NumberOfStoredAfterTriggeredRecord;     /* The number of stored time-series freeze frame records after triggered. */
} Dem_TimeSeriesFreezeFrameListType;

/* Record for list of time-series freeze frame to control */
typedef struct
{
    Dem_u16_TSFFListIndexType   CurrentIndex[DEM_TSFF_MAX_NUM_OF_DTC_FOR_TSFF]; /* The current index for time-series freeze frame list records. */
    Dem_u16_TSFFListIndexType   VacantTimeSeriesFreezeFrameListRecordRef;       /* The vacant reference of time-series freeze frame list records. */
} Dem_TimeSeriesFreezeFrameCtrlType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE ) Dem_Data_InitTSFFD_AfterRecordCheckComplete
( void );
FUNC( void, DEM_CODE ) Dem_Data_InitSmplFFRecordList
(
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) SamplingRecMemIndex
);
FUNC( void, DEM_CODE ) Dem_Data_InitTSFFListRecordList
(
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) SamplingRecMemIndex
);
FUNC( void, DEM_CODE ) Dem_Data_InitTSFFListRecord
(
    P2VAR( Dem_TimeSeriesFreezeFrameListType, AUTOMATIC, DEM_VAR_NO_INIT ) TimeSeriesFreezeFrameListRecordPtr
);
FUNC( void, DEM_CODE ) Dem_Data_InitTSFFCtrlRecordList
(
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) SamplingRecMemIndex
);
FUNC( void, DEM_CODE ) Dem_Data_SaveTSFFListRecordList
(
    P2VAR( Dem_TimeSeriesFreezeFrameListType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameListRecordListPtr
);
FUNC( void, DEM_CODE ) Dem_Data_UpdateNumberOfStoredAfterTriggeredRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListRecordIndex,
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameBindTableRef,
    P2CONST( Dem_TimeSeriesFreezeFrameListType, AUTOMATIC, AUTOMATIC ) TimeSeriesFreezeFrameListRecordListPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_UpdateVacantTSFFListRecordRef
(
    VAR( Dem_u16_TSFFRecClassIndexType, AUTOMATIC ) TimeSeriesFreezeFrameBindTableRef
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

extern VAR( Dem_TimeSeriesFreezeFrameListType, DEM_VAR_NO_INIT ) Dem_TimeSeriesFreezeFrameListRecordList[DEM_TSFF_TOTAL_DTC_NUM];
extern VAR( Dem_TimeSeriesFreezeFrameCtrlType, DEM_VAR_NO_INIT ) Dem_TimeSeriesFreezeFrameCtrlRecordList[DEM_TSFF_RECORD_CLASS_CONFIGURE_NUM];

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#endif  /* ( DEM_TSFF_SUPPORT == STD_ON )   */

#endif /* DEM_CMNLIB_DATACTL_TSFFD_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
