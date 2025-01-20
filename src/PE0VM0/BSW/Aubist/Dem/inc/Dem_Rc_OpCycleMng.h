/* Dem_Rc_OpCycleMng_h(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/OpCycleMng_OBD/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_OPCYCLEMNG_H
#define DEM_RC_OPCYCLEMNG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"


#include <Dem/Dem_Common.h>
#include "../cfg/Dem_MM_Cfg.h"
#include "../cfg/Dem_NvM_Cfg.h"
#include "../inc/Dem_Mm_MemSync.h"
#include "../usr/Dem_SavedZone_Callout.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
#define DEM_OPCYCMNG_UPD_RAM                        ( DEM_UPDNVM_UPD_RAMONLY ) /*  update RAM only                 */
#define DEM_OPCYCMNG_UPD_NVM_RAMDIFF                ( DEM_UPDNVM_UPD_NVM_RAMDIFF ) /*  update NvM if RAM difference.   */
#define DEM_OPCYCMNG_UPD_NVM_FORCE                  ( DEM_UPDNVM_UPD_NVM_FORCE ) /*  update NvM force.               */
#endif /* DEM_CYCLEQUALIFIED_SUPPORT -STD_ON- */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
FUNC( Dem_OperationCycleStateType, DEM_CODE ) Dem_OpCycleMng_GetCycleState
(
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) CycleQualifiedIndex
);


#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_OpCycleMng_ClearCycleState
(
    VAR( Dem_u08_UpdNvMType, AUTOMATIC ) UpdateNvMMode
);
FUNC( void, DEM_CODE ) Dem_OpCycleMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_OpCycleMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OpCycleMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_OpCycleMng_SetCycleState
(
    VAR( Dem_u08_CycleQualifiedIndexType, AUTOMATIC ) CycleQualifiedIndex,
    VAR( Dem_OperationCycleStateType, AUTOMATIC ) CycleState
);

#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_OpCycleMng_SetPFCCycleClearConditionCheckStatus
(
    VAR( Dem_u08_PFCClearCondCheckStatusType, AUTOMATIC ) PFCClearConditionCheckStatus
);
FUNC( Dem_u08_PFCClearCondCheckStatusType, DEM_CODE ) Dem_OpCycleMng_GetPFCCycleClearConditionCheckStatus
( void );
#endif  /*( DEM_PFC_SUPPORT == STD_ON ) */


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_OpCycleMng_CopyOpCycleStatusToMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*------------------------------*/
/*  get record data             */
/*------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_OpCycleMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#endif /* DEM_CYCLEQUALIFIED_SUPPORT -STD_ON- */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_CYCLEQUALIFIED_SUPPORT == STD_ON )
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT )                    Dem_OpCycleNvMStatus;
extern VAR( Dem_OpCycleRecordType, DEM_VAR_NO_INIT )    Dem_OpCycleRecordMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */
#endif /* DEM_CYCLEQUALIFIED_SUPPORT -STD_ON- */


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>



#endif /* DEM_RC_OPCYCLEMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
