/* Dem_Rc_IndMIMng_h(v5-10-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Rc_IndMIMng/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_INDMIMNG_H
#define DEM_RC_INDMIMNG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_WWH_OBD_SUPPORT == STD_ON )
#include "../cfg/Dem_Cfg.h"
#include "../cfg/Dem_MM_Cfg.h"
#include "../cfg/Dem_NvM_Cfg.h"
#include "../inc/Dem_Mm_MemSync.h"
#include "../usr/Dem_SavedZone_Callout.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_B1COUNTER_FACTORY_DEFAULT                     ((Dem_u32_B1CounterType)0xFFFFFFFFU)
#define DEM_B1CLEARCYCLECOUNTER_FACTORY_DEFAULT           ((Dem_u08_B1ClearCycleCounterType)0xFFU)
#define DEM_B1COUNTER_OUTPUT_MAX                          ((Dem_u32_B1CounterType)0x0000FFFFU)

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


/*------------------------------*/
/*  for Set/Get data            */
/*------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMIMng_SetB1Counter
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex,
    VAR( Dem_u32_B1CounterType, AUTOMATIC ) B1Counter
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMIMng_GetB1Counter
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr,
    P2VAR( Dem_u32_B1CounterType, AUTOMATIC, AUTOMATIC ) B1CounterPtr
);


/*------------------------------*/
/*  for Function Table          */
/*------------------------------*/
FUNC( void, DEM_CODE ) Dem_IndMIMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_IndMIMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMIMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMIMng_GetEmptyRecordIndex
(
    P2VAR( Dem_u16_IndMIIndexType, AUTOMATIC, AUTOMATIC ) IndMIIndexPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMIMng_GetNextEmptyRecordIndex
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) StartIndex,
    P2VAR( Dem_u16_IndMIIndexType, AUTOMATIC, AUTOMATIC ) IndMIIndexPtr
);
FUNC( void, DEM_CODE ) Dem_IndMIMng_RegistB1CounterRecord
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex,
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
FUNC( void, DEM_CODE ) Dem_IndMIMng_ClearB1CounterRecord
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex
);
FUNC( void, DEM_CODE ) Dem_IndMIMng_HoldB1Counter
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex
);
FUNC( void, DEM_CODE ) Dem_IndMIMng_UpdateClearId
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMIMng_GetB1ClearCycleCounter
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex,
    P2VAR( Dem_u08_B1ClearCycleCounterType, AUTOMATIC, AUTOMATIC ) B1ClearCycleCounterPtr
);
FUNC( void, DEM_CODE ) Dem_IndMIMng_SetB1ClearCycleCounter
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex,
    VAR( Dem_u08_B1ClearCycleCounterType, AUTOMATIC ) B1ClearCycleCounter
);
FUNC( void, DEM_CODE ) Dem_IndMIMng_ClearB1ClearCycleCounter
(
    VAR( Dem_u16_IndMIIndexType, AUTOMATIC ) IndMIIndex
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_IndMIMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IndMIMng_GetEventIdFromRecordData
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

/*------------------------------*/
/*  for Function Table          */
/*------------------------------*/
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_IndMINvMStatus[ DEM_INDMIB1COUNTER_RECORD_NUM ];
extern VAR( Dem_IndMIB1CounterRecordType, DEM_VAR_NO_INIT ) Dem_TmpIndMIB1CounterMirror;
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#endif  /* ( DEM_WWH_OBD_SUPPORT == STD_ON )    */

#endif /* DEM_RC_INDMIMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

