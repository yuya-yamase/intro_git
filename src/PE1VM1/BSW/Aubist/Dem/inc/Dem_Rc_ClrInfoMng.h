/* Dem_Rc_ClrInfoMng_h(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Rc_ClrInfoMng/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_CLRINFOMNG_H
#define DEM_RC_CLRINFOMNG_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"
#include "../cfg/Dem_MM_Cfg.h"
#include "../cfg/Dem_NvM_Cfg.h"
#include "../inc/Dem_Mm_MemSync.h"
#include "../usr/Dem_SavedZone_Callout.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_CLRINFO_RECORD_INITIAL                     ((Dem_u08_ClearIdType)0xFFU)

#define DEM_CLRINFO_RECORD_MAX_VALUE                   ((DEM_CLRINFO_RECORD_INITIAL - (Dem_u08_ClearIdType)0x01U))



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

FUNC( void, DEM_CODE ) Dem_ClrInfoMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);

FUNC( void, DEM_CODE ) Dem_ClrInfoMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);

FUNC( void, DEM_CODE ) Dem_ClrInfoMng_Init_AfterNvBlockReadComplete
( void );

/*------------------------------*/
/*  DataVerify                  */
/*------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ClrInfoMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);

/*------------------------------*/
/*  for Clear process           */
/*------------------------------*/
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_StartClearDTC
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
#endif  /*   ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )      */
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_UpdateClearID
(
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) DTCGroup,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ClrInfoMng_GetNvClearResult
( void );

/*------------------------------*/
/*  for other Record Unit       */
/*------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ClrInfoMng_GetNvmReadResult
( void );

FUNC( Dem_u08_ClearIdType, DEM_CODE ) Dem_ClrInfoMng_GetClearID
( void );

FUNC( Dem_u08_ClearIdType, DEM_CODE ) Dem_ClrInfoMng_GetObdClearID
( void );
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
FUNC( Dem_u08_ClearIdType, DEM_CODE ) Dem_ClrInfoMng_GetUdmClearID
(
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) UdmInternalInfoTableIndex
);
#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */
/*------------------------------*/
/*  for NvM                     */
/*------------------------------*/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_NvMReadError
( void );
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_SetNvClearResult
(
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) Result
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/*------------------------------*/
/*  Refresh RAM                 */
/*------------------------------*/
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_RefreshRAM
( void );

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*------------------------------*/
/*  get record data             */
/*------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_ClrInfoMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_ClrInfoNvMStatus;
extern VAR( Dem_ClrInfoRecordType, DEM_VAR_NO_INIT ) Dem_ClrInfoMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#endif /* DEM_RC_CLRINFOMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

