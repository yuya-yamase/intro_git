/* Dem_Rc_OccrDTCMng_h(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Rc_OccrDTCMng/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_OCCRDTCMNG_H
#define DEM_RC_OCCRDTCMNG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON )
#include <Dem/Dem_Common.h>
#include "../cfg/Dem_Cfg.h"
#include "../cfg/Dem_MM_Cfg.h"
#include "../cfg/Dem_NvM_Cfg.h"
#include "../inc/Dem_Mm_MemSync.h"
#include "../inc/Dem_Rc_DataMng.h"
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

FUNC( void, DEM_CODE ) Dem_OccrDTCMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OccrDTCMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_DataVerify_AfterRecordCheckComplete
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) LastConfirmedEventStrgIndex
);
#if ( DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_SetMostRecentConfirmedData
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_UpdNvMType, AUTOMATIC ) UpdateNvMMode
);
#endif  /* ( DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT == STD_ON )  */
#if ( DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT == STD_OFF )
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_SetMostRecentConfirmedDataAtSetEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
#endif  /* ( DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT == STD_OFF ) */

FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_OccrDTCMng_GetMostRecentConfirmedData
( void );

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*------------------------------*/
/*  get record data             */
/*------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OccrDTCMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#if ( DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT == STD_OFF )
FUNC( void, DEM_CODE ) Dem_OccrDTCMng_UpdateRecord
( void );
FUNC( boolean, DEM_CODE ) Dem_OccrDTCMng_ClearMostRecentConfirmedData_EventStrgIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( boolean, DEM_CODE ) Dem_OccrDTCMng_ClearMostRecentConfirmedData_AllDTC
( void );
FUNC( boolean, DEM_CODE ) Dem_OccrDTCMng_ClearMostRecentConfirmedData_ObdDTC
( void );
#endif  /* ( DEM_DTC_OCCURRENCE_TIME_UPDATEATAGING_SUPPORT == STD_OFF )   */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_OccrDTCNvMStatus;
extern VAR( Dem_OccrDTCRecordType, DEM_VAR_NO_INIT ) Dem_TmpOccrDTCMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#endif /* ( DEM_DTC_OCCURRENCE_TIME_SUPPORT == STD_ON ) */

#endif /* DEM_RC_OCCRDTCMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
