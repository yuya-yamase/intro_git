/* Dem_Rc_DTRMng_h(v5-5-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Rc_DTRMng/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_DTRMNG_H
#define DEM_RC_DTRMNG_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"

#if ( DEM_DTR_SUPPORT == STD_ON )
#include "../cfg/Dem_MM_Cfg.h"
#include "../cfg/Dem_NvM_Cfg.h"
#include "../inc/Dem_Mm_MemSync.h"
#include "../usr/Dem_SavedZone_Callout.h"
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

FUNC( void, DEM_CODE ) Dem_DTRMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_DTRMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);

FUNC( void, DEM_CODE ) Dem_DTRMng_SetDTRRecordData
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRId,
    P2CONST( Dem_DtrDataType, AUTOMATIC, AUTOMATIC ) DtrDataPtr
);

FUNC( Dem_u08_DTRTidIndexType, DEM_CODE ) Dem_DTRMng_GetNumTIDsOfOBDMID
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRIdIndex,
    VAR( Dem_u08_DTRTidIndexType, AUTOMATIC ) DemDtrTidNum
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTRMng_GetDTRRecordData
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRId,
    P2VAR( Dem_DtrDataType, AUTOMATIC, AUTOMATIC ) DtrDataPtr
);

#if ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTRMng_GetDTR
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRId,
    P2VAR( Dem_DtrDataType, AUTOMATIC, AUTOMATIC ) DtrDataPtr
);
#endif  /* ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON ) */

FUNC( void, DEM_CODE ) Dem_DTRMng_ClearDTRRecordData
( void );

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_DTRMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTRMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*------------------------------*/
/*  get record data             */
/*------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTRMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
#endif  /*   ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )  */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_DTRNvMStatus[DEM_DTR_RECORD_NUM];
extern VAR( Dem_DtrRecordType, DEM_VAR_NO_INIT ) Dem_TmpDTRMirror;

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#endif  /* ( DEM_DTR_SUPPORT == STD_ON )    */

#endif /* DEM_RC_DTRMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

