/* Dem_DataMng_FreezeFrame_h(v5-7-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/DataMng_FreezeFrame/HEADER                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_DATAMNG_FREEZEFRAME_H
#define DEM_DATAMNG_FREEZEFRAME_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Rc_DataMng.h"

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
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataMng_SetCapturedFreezeFrame
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) StorageFormatDataSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    P2CONST( AB_83_ConstV Dem_FreezeFrameDataPosType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameDataPosTablePtr,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyID,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFStoredStatusType, AUTOMATIC ) RecordStatus,
    P2CONST( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) CapturedDataPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) CapturedDataSize,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) StorageFormatDataPtr
);


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



#endif  /* DEM_DATAMNG_FREEZEFRAME_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
