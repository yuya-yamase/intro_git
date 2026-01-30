/* Dem_DataCtl_TSFFD_local_h(v5-3-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_TSFFD_local/HEADER                            */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_DATACTL_TSFFD_LOCAL_H
#define DEM_DATACTL_TSFFD_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"

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

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_PrepareStoreTSFFRecordFromSample
( void );
FUNC( void, DEM_CODE ) Dem_Data_StoreTSFFRecordFromSample
( void );
FUNC( void, DEM_CODE ) Dem_Data_ClearTSFFListRecord
(
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
);
FUNC( void, DEM_CODE ) Dem_Data_GenerateTSFFLRecordList
( void );
FUNC( void, DEM_CODE ) Dem_Data_ClearTSFFRecord
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TimeSeriesFreezeFrameListRecordIndex
);
#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_DeleteTSFFListByFFRTrigger
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FRNotOverwrittenIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex
);
#endif  /* ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )   */
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#endif  /* DEM_DATACTL_TSFFD_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
