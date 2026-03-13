/* Dem_CmnLib_DataCtl_FFDOutputJudge_h(v5-7-0)                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/CmnLib_DataCtl_FFDOutputJudge/HEADER                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_CMNLIB_DATACTL_FFDOUTPUTJUDGE_H
#define DEM_CMNLIB_DATACTL_FFDOUTPUTJUDGE_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../cfg/Dem_Data_Cfg.h"
#include "../usr/Dem_FFDOutputJudge_Callout.h"

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
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( boolean, DEM_CODE ) Dem_Data_SetFFDOutputJudge
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) FreezeFrameDataSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    P2CONST( AB_83_ConstV Dem_DidClassType, AUTOMATIC, DEM_CONFIG_DATA ) DidClassPtr,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) FreezeFrameDataPtr,
    P2VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameDataOffsetPtr
);

#if ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Data_AddFFDOutputJudgeSize
(
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) DidClassIndex,
    P2VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) AddedDataSizePtr
);
#endif  /* ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )       */

FUNC( boolean, DEM_CODE ) Dem_Data_GetFFDOutputAllow
(
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) DidClassIndex,
    VAR( uint8, AUTOMATIC ) FFDOutputJudge,
    P2VAR( Dem_u32_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameDataOffsetPtr
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


#endif /* DEM_CMNLIB_DATACTL_FFDOUTPUTJUDGE_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
