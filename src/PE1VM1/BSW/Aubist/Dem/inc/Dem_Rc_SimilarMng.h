/* Dem_Rc_SimilarMng_h(v5-9-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Rc_SimilarMng/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_SIMILARMNG_H
#define DEM_RC_SIMILARMNG_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
#include "../cfg/Dem_NvM_Cfg.h"
#include "../cfg/Dem_Similar_Cfg.h"
#include "../usr/Dem_SavedZone_Callout.h"
#include "Dem_Mm_MemSync.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_SIMILAR_CONDITION_FACTORY_DEFAULT          ((Dem_SimilarConditionValueType)0xFFFFFFFFU)
#define DEM_SIMILAR_PENDINGERASECYCCOUNTER_INIT        ((Dem_u08_SimilarPendingClearCounterType)0x00U)
#define DEM_SIMILAR_COUNTER_FACTORY_DEFAULT            ((Dem_u08_SimilarPendingClearCounterType)0xFFU)
#define DEM_SIMILAR_EXCEEDANCECOUNTER_INIT             ((Dem_u08_SimilarExceedanceCounterType)0x00U)
#define DEM_SIMILAR_EXCEEDANCECOUNTER_FACTORY_DEFAULT  ((Dem_u08_SimilarExceedanceCounterType)0xFFU)

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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_GetSimilarRecordList
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    P2VAR( Dem_SimilarRecordType, AUTOMATIC, AUTOMATIC ) SimilarRecordPtr
);
FUNC( void, DEM_CODE ) Dem_SimilarMng_SetSimilarRecordList
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    P2CONST( Dem_SimilarRecordType, AUTOMATIC, AUTOMATIC ) SimilarRecordPtr
);
FUNC( void, DEM_CODE ) Dem_SimilarMng_ClearSimilarRecordList
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex
);
FUNC( void, DEM_CODE ) Dem_SimilarMng_SetConsistencyId
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);
FUNC( void, DEM_CODE ) Dem_SimilarMng_SetExceedanceCounter
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    VAR( Dem_u08_SimilarExceedanceCounterType, AUTOMATIC ) ExceedanceCounter
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_GetExceedanceCounter
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    P2VAR( Dem_u08_SimilarExceedanceCounterType, AUTOMATIC, AUTOMATIC ) ExceedanceCounterPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_GetPendingClearCounter
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    P2VAR( Dem_u08_SimilarPendingClearCounterType, AUTOMATIC, AUTOMATIC ) PendingClearCounterPtr
);
FUNC( void, DEM_CODE ) Dem_SimilarMng_GetSimilarConditionStoredflg
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) SimilarConditionStoredflgPtr
);
FUNC( void, DEM_CODE ) Dem_SimilarMng_GetSimilarConditionStoredList
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    P2VAR( Dem_SimilarConditionValueType, AUTOMATIC, DEM_APPL_DATA ) SimilarConditionArrayPtr
);
FUNC( void, DEM_CODE ) Dem_SimilarMng_GetSimilarConditionLatchedList
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    P2VAR( Dem_SimilarConditionValueType, AUTOMATIC, DEM_APPL_DATA ) SimilarConditionArrayPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_CompareSimilarRecord
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    P2CONST( Dem_SimilarRecordType, AUTOMATIC, AUTOMATIC ) CheckSimilarRecordPtr
);
FUNC( void, DEM_CODE ) Dem_SimilarMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_SimilarMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_SimilarMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */



#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*------------------------------*/
/*  get record data             */
/*------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_GetEventIdFromRecordData
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
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_SimilarNvMStatus[DEM_SIMILAR_RECORD_LIST_NUM];
extern VAR( Dem_SimilarRecordType, DEM_VAR_NO_INIT ) Dem_TmpSimilarMirror;
#endif  /*  ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )    */

#endif /* DEM_RC_SIMILARMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

