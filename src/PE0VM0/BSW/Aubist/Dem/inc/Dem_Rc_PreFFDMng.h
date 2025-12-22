/* Dem_Rc_PreFFDMng_h(v5-5-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Rc_PreFFDMng/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_PREFFDMNG_H
#define DEM_RC_PREFFDMNG_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )
#include "../cfg/Dem_MM_Cfg.h"
#include "../cfg/Dem_NvM_Cfg.h"
#include "../inc/Dem_Mm_MemSync.h"
#include "../usr/Dem_SavedZone_Callout.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_FF_PADDING_DATA                                     ((uint8)0xFFU)
#define DEM_PREFFD_INDEX_INVALID              ((Dem_u08_PreFFDIndexType)0xFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef struct
{
    Dem_u16_EventStrgIndexType                      EventStrgIndex;
    P2VAR( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE ) DataPtr;
} Dem_PreFFRecordMngType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE ) Dem_PreFFDMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_PreFFDMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFDMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);

FUNC( void, DEM_CODE ) Dem_PreFFDMng_InitFreezeFrameRecord
(
    P2VAR( Dem_PreFFRecordMngType, AUTOMATIC, AUTOMATIC ) PreFFRecordMngPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFDMng_GetFreezeFrameRecord
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex,
    P2VAR( Dem_PreFFRecordMngType, AUTOMATIC, AUTOMATIC ) PreFFRecordMngPtr
);

FUNC( void, DEM_CODE ) Dem_PreFFDMng_SetEventStrgIndex
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON)
FUNC( void, DEM_CODE ) Dem_PreFFDMng_SetChecksum
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex
);
#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON) */

FUNC( void, DEM_CODE ) Dem_PreFFDMng_SetUpdateRequest
(
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) PreFFRecordIndex
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_PreFFDMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*------------------------------*/
/*  get record data             */
/*------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFDMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_PreFFDNvMStatus[DEM_PREFF_RECORD_LIST_NUM];
extern VAR( Dem_PreFFRecordType, DEM_VAR_NO_INIT ) Dem_TmpPreFFDMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#endif  /* DEM_FF_PRESTORAGE_SUPPORT -STD_ON-    */

#endif /* DEM_RC_PREFFDMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

