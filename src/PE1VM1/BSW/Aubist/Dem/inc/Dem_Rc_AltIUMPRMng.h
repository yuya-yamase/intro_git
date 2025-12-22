/* Dem_Rc_AltIUMPRMng_h(v5-10-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Rc_AltIUMPRMng/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef DEM_RC_ALTIUMPRMNG_H
#define DEM_RC_ALTIUMPRMNG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )
#include <Dem/Dem_Common.h>
#include "../cfg/Dem_Cfg.h"
#include "../cfg/Dem_MM_Cfg.h"
#include "../cfg/Dem_NvM_Cfg.h"
#include "../cfg/Dem_AltIUMPR_Cfg.h"
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

FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AltIUMPRMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);

FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_SetTestCompleteThisCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u08_AltIUMPRTestCompletedThisCycleType, AUTOMATIC ) TestCompleteThisCycle
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AltIUMPRMng_GetTestCompleteThisCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_u08_AltIUMPRTestCompletedThisCycleType, AUTOMATIC, AUTOMATIC ) TestCompleteThisCyclePtr
);

FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_GetDenominator
(
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DenominatorPtr
);
FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_IncNumeratorCounts
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_IncNumeratorCountsForCylinder
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC )  MisfireCylinderNum
);
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AltIUMPRMng_GetNumeratorAndRatio
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) NumeratorPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) RatioPtr
);
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AltIUMPRMng_GetNumeratorAndRatioForCylinder
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC )  MisfireCylinderNum,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) NumeratorPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) RatioPtr
);
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_IncDenominatorProccess
( void );

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*------------------------------*/
/*  get record data             */
/*------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AltIUMPRMng_GetEventIdFromRecordData
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
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_AltIUMPRNvMStatus[ DEM_ALTIUMPR_RECORD_NUM ];
extern VAR( Dem_AltIUMPRRecordType, DEM_VAR_NO_INIT ) Dem_TmpAltIUMPRMirror;
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* ( DEM_ALTIUMPR_SUPPORT == STD_ON ) */

#endif /* DEM_RC_ALTIUMPRMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

