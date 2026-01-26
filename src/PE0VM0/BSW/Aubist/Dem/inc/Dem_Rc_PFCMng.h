/* Dem_Rc_PFCMng_h(v5-5-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Rc_PFCMng/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RCC_PFCMNG_H
#define DEM_RCC_PFCMNG_H


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
#if ( DEM_PFC_SUPPORT == STD_ON )

#define DEM_PFC_RECORD_INDEX_INITIAL               ((Dem_u08_PFCIndexType)0xFFU)

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
#define DEM_DTC_PFC_RESERVE_INITIAL_VALUE          ((uint8)0x00U)
#endif  /*  ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   */

#define DEM_PFC_QUABIT_PASSEDCYCLEQUALIFIED        ((Dem_u08_PFCCycQuaInfoType)0x08U)
#define DEM_PFC_QUABIT_DRIVINGCONDITIONQUALIFIED   ((Dem_u08_PFCCycQuaInfoType)0x04U)
#define DEM_PFC_QUABIT_PFCCYCLEQUALIFIED           ((Dem_u08_PFCCycQuaInfoType)0x02U)
#define DEM_PFC_QUALIFIEDINFO_INITIAL              ((Dem_u08_PFCCycQuaInfoType)0x00U)
#define DEM_PFC_QUALIFIEDINFO_FACTORY_DEFAULT      ((Dem_u08_PFCCycQuaInfoType)0xFFU)

#define DEM_PFC_DTCVALUE_INITIAL                   ((Dem_u32_DTCValueType)0xFFFFFFFFU)

#endif /* ( DEM_PFC_SUPPORT == STD_ON ) */

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

#if ( DEM_PFC_SUPPORT == STD_ON )

FUNC( void, DEM_CODE ) Dem_PFCMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);

FUNC( void, DEM_CODE ) Dem_PFCMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);

FUNC( void, DEM_CODE ) Dem_PFCMng_SetPFCRecordData
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_GetPFCRecordData
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_GetPFCRecordIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_PFCIndexType, AUTOMATIC, AUTOMATIC ) PFCRecordIndexPtr
);

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_OFF )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_GetNextSpacePFCRecordIndex
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) BasePFCRecordIndex,
    P2VAR( Dem_u08_PFCIndexType, AUTOMATIC, AUTOMATIC ) PFCRecordIndexPtr
);
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_OFF ) */

FUNC( void, DEM_CODE ) Dem_PFCMng_SetAllPFCCycleQualified
( void );

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_GetCycleQualifiedInfo
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    P2VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC, AUTOMATIC ) CycleQualifiedInfoPtr
);

FUNC( void, DEM_CODE ) Dem_PFCMng_SetCycleQualifiedInfo
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC ) CycleQualifiedInfo
);

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_GetStoredMisfireSpaceEventStrgIndex
(
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) StoredMisFirePFCMisFireEventStrgIndexPtr
);
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */

/*----------------------------------*/
/*  for Update NvM                  */
/*----------------------------------*/
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )

FUNC( void, DEM_CODE ) Dem_PFCMng_CopyToMirrorMemory
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);

#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

/*==========================================*/
/*  PFC QualifiedInfo                       */
/*==========================================*/

/*----------------------------------*/
/*  for PFCMng                      */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_GetDtcValue
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DtcValuePtr
);

FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_SetDtcValue
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DtcValue
);

FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_GetClearID
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    P2VAR( Dem_u08_ClearIdType, AUTOMATIC, AUTOMATIC ) ClearIDPtr
);

FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_SetClearID
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID
);

FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_GetCycleQualifiedInfo
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    P2VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC, AUTOMATIC ) CycleQualifiedInfoPtr
);

FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_SetCycleQualifiedInfo
(
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) PFCRecordIndex,
    VAR( Dem_u08_PFCCycQuaInfoType, AUTOMATIC ) CycleQualifiedInfo
);

/*----------------------------------*/
/*  for Initialize                  */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_QuaInfo_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);


/*----------------------------------*/
/*  for Update NvM                  */
/*----------------------------------*/
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_PFCMng_QuaInfo_CopyToMirrorMemory
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);

#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*------------------------------*/
/*  get record data             */
/*------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFCMng_QuaInfo_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

#endif /* ( DEM_PFC_SUPPORT == STD_ON ) */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_PFC_SUPPORT == STD_ON )
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_PFCNvMStatus[DEM_PFC_RECORD_NUM];
extern VAR( Dem_PFCRecordType, DEM_VAR_NO_INIT ) Dem_TmpPFCMirror;

extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_PFCQuaInfoNvMStatus[DEM_PFC_RECORD_NUM];
extern VAR( Dem_PFCQuaInfoRecordType, DEM_VAR_NO_INIT ) Dem_TmpPFCQuaInfoMirror;

#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */
#endif /* ( DEM_PFC_SUPPORT == STD_ON ) */


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>



#endif /* DEM_RC_PFCMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

