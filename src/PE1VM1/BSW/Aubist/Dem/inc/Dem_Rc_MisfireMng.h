/* Dem_Rc_MisfireMng_h(v5-6-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Rc_MisfireMng/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_MISFIREMNG_H
#define DEM_RC_MISFIREMNG_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Cfg.h"

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../cfg/Dem_NvM_Cfg.h"
#include "../cfg/Dem_Misfire_Cfg.h"
#include "../usr/Dem_SavedZone_Callout.h"
#include "Dem_Mm_MemSync.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_MISFIRE_CYLINDER_FACTORY_DEFAULT            ((Dem_MisfireCylinderType)0xFFFFU)

#define DEM_MISFIRE_EXCEEDANCECOUNTER_INIT               ((Dem_u08_MisfExceedanceCounterType)0x00U)
#define DEM_MISFIRE_EXCOUNTER_FACTORY_DEFAULT            ((Dem_u08_MisfExceedanceCounterType)0xFFU)

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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_MisfireRecordDataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_MisfireComRecordDataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_MisfireRecordInitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_MisfireComRecordInitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_GetAllMisfireRecordList
(
    P2VAR( Dem_MisfireRecordType, AUTOMATIC, AUTOMATIC ) MisfireRecordPtr
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetMisfireRecordList
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    P2CONST( Dem_MisfireRecordType, AUTOMATIC, AUTOMATIC ) MisfireRecordPtr
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_ClearMisfireRecordList
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_CompareMisfireRecord
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    P2CONST( Dem_MisfireRecordType, AUTOMATIC, AUTOMATIC ) CheckMisfireRecordPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_CompareMisfireComRecord
(
    P2CONST( Dem_MisfireComRecordType, AUTOMATIC, AUTOMATIC ) CheckMisfireComRecordPtr
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetConsistencyIdOfMisfireRecord
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetConsistencyIdOfMisfireComForEmission
(
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetConsistencyIdOfMisfireComForCAT
(
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetExceedanceCounter
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_MisfExceedanceCounterType, AUTOMATIC ) ExceedanceCounter
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_GetExceedanceCounter
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    P2VAR( Dem_u08_MisfExceedanceCounterType, AUTOMATIC, AUTOMATIC ) ExceedanceCounterPtr
);
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetFailedCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
);
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetAccumCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
);
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetAFCylThisOC
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
);
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetAccumPendingCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
);
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetAccumConfirmedCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
);
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetAFCySinceClear
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
);
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetATNCCySinceClear
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
);
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetObdFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex
);
FUNC( Dem_u08_MisfireKindType, DEM_CODE ) Dem_MisfireMng_GetMisfireKindOfObdFFD
(
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_InitObdFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_InitMisfireKindOfObdFFD
(
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetMisfireKindOfObdFFD
(
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex,
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) MisfireType
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex
);
FUNC( Dem_u08_MisfireKindType, DEM_CODE ) Dem_MisfireMng_GetMisfireKindOfFFD
(
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex
);
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )
FUNC( Dem_MisfireCylinderNumberType, DEM_CODE ) Dem_MisfireMng_GetConfirmedOrderCyl
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireConfirmedOrderIndex
);
FUNC( Dem_u16_OccrOrderType, DEM_CODE ) Dem_MisfireMng_GetConfirmedOccurrenceOrder
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireConfirmedOrderIndex
);
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */
FUNC( void, DEM_CODE ) Dem_MisfireMng_InitFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_InitMisfireKindOfFFD
(
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetMisfireKindOfFFD
(
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex,
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) MisfireType
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_GetMisfireComRecord
(
    P2VAR( Dem_MisfireComRecordType, AUTOMATIC, AUTOMATIC ) MisfireComRecordPtr
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetMisfireComRecord
(
    P2CONST( Dem_MisfireComRecordType, AUTOMATIC, AUTOMATIC ) MisfireComRecordPtr
);
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )     /*  [FuncSw]    */
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetConfirmedOrderCyl
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) ConfirmedOrderCylIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) ConfirmedOrderCyl,
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) ConfirmedOccurrenceOrder
);
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */
FUNC( void, DEM_CODE ) Dem_MisfireMng_ClearMisfireComRecord
(void);
FUNC( void, DEM_CODE ) Dem_MisfireMng_MisfireRecordInit
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_MisfireComRecordInit
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetMisfireRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetMisfireComRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_PFCMisfireComRecordDataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_PFCMisfireComRecordInit
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_PFCMisfireComRecordInitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_PFCMisfireComDataVerify
(
    VAR( boolean, AUTOMATIC ) ExistMisfireRecordflg,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ClearMisfirePFCRecordflgPtr
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_GetPFCMisfireComRecord
(
    P2VAR( Dem_PFCMisfireComRecordType, AUTOMATIC, AUTOMATIC ) PFCMisfireComRecordPtr
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetPFCMisfireComRecord
(
    P2CONST( Dem_PFCMisfireComRecordType, AUTOMATIC, AUTOMATIC ) PFCMisfireComRecordPtr
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_ClearPFCMisfireComRecord
( void );

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetPFCMisfireComRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */
#endif /* ( DEM_PFC_SUPPORT == STD_ON ) */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*------------------------------*/
/*  get record data             */
/*------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_MisfireCom_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_PFCMisfireCom_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )  */
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_MisfireNvMStatus[DEM_MISFIRE_RECORD_LIST_NUM];
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_MisfireComNvMStatus;
/*  if DEM_NVM_SYNC_PROCESS_ENABLE is STD_OFF, these valiables are set but never used.  */
extern VAR( Dem_MisfireRecordType, DEM_VAR_NO_INIT ) Dem_TmpMisfireMirror;
extern VAR( Dem_MisfireComRecordType, DEM_VAR_NO_INIT ) Dem_TmpMisfireComMirror;

#if ( DEM_PFC_SUPPORT == STD_ON )
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_PFCMisfireComNvMStatus;
extern VAR( Dem_PFCMisfireComRecordType, DEM_VAR_NO_INIT ) Dem_TmpPFCMisfireComMirror;
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )  */
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */

#endif /* DEM_RC_MISFIREMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

