/* Dem_Rc_IUMPRMng_h(v5-5-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Rc_IUMPRMng/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_IUMPRMNG_H
#define DEM_RC_IUMPRMNG_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_IUMPR_SUPPORT == STD_ON )

#include "../cfg/Dem_Cfg.h"
#include "../cfg/Dem_MM_Cfg.h"
#include "../cfg/Dem_NvM_Cfg.h"
#include "../inc/Dem_Mm_MemSync.h"
#include "../usr/Dem_SavedZone_Callout.h"
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define DEM_IUMPRMNG_CONDITION_STATUS_INITVALUE     ((Dem_u08_IUMPRGenDenCondType)0x00U)

#define DEM_IUMPRMNG_DEN_COND_GEN                   ((Dem_u08_IUMPRGenDenCondType)0x01U)
#define DEM_IUMPRMNG_DEN_COND_COLD                  ((Dem_u08_IUMPRGenDenCondType)0x02U)
#define DEM_IUMPRMNG_DEN_COND_EVAP                  ((Dem_u08_IUMPRGenDenCondType)0x04U)
#define DEM_IUMPRMNG_DEN_COND_500MI                 ((Dem_u08_IUMPRGenDenCondType)0x08U)


#define DEM_IUMPRMNG_RTO_COND_NUME_EST              ((Dem_u08_IUMPRRatioCondType)0x01U)
#define DEM_IUMPRMNG_RTO_COND_NUME_ADD              ((Dem_u08_IUMPRRatioCondType)0x02U)
#define DEM_IUMPRMNG_RTO_COND_DEN_EST               ((Dem_u08_IUMPRRatioCondType)0x04U)
#define DEM_IUMPRMNG_RTO_COND_DEN_ADD               ((Dem_u08_IUMPRRatioCondType)0x08U)
#define DEM_IUMPRMNG_RTO_COND_HST_500               ((Dem_u08_IUMPRRatioCondType)0x10U)
#define DEM_IUMPRMNG_RTO_COND_HST_GDN               ((Dem_u08_IUMPRRatioCondType)0x20U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    Dem_u16_IUMPRCycleCounterType    GeneralDenCounter;
    Dem_u16_IUMPRCycleCounterType    IGCycleCounter;
    Dem_u08_IUMPRGenDenCondType     DenominatorCondition;
    Dem_u08_IUMPRGenAddedCondType   GeneralDenAddedCondition;
    Dem_u08_IUMPRGenAddedCondType   IGCycleAddedCondition;
    uint8     Reserve1;
} Dem_IUMPRInfoRecordType;

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
typedef struct
{
    Dem_u16_IUMPRCycleCounterType    DenominatorCounter;
    Dem_u16_IUMPRCycleCounterType    NumeratorCounter;
    Dem_u08_IUMPRRatioCondType  RatioCondition;
    uint8     Reserve1;
    uint8     Reserve2;
    uint8     Reserve3;
} Dem_IUMPRRatioRecordType;
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )        */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE ) Dem_IUMPRMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);

FUNC( void, DEM_CODE ) Dem_IUMPRMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPRMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);

FUNC( void, DEM_CODE ) Dem_IUMPRMng_ClearCondition
( void );

FUNC( void, DEM_CODE ) Dem_IUMPRMng_GetIUMPRDenCondition
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )                  ConditionId,
    P2VAR( Dem_IumprDenomCondStatusType, AUTOMATIC, AUTOMATIC ) ConditionStatusPtr
);

FUNC( void, DEM_CODE ) Dem_IUMPRMng_GetIGCycleCounter
(
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC ) IGCycleCounterPtr
);

FUNC( void, DEM_CODE ) Dem_IUMPRMng_GetIGCycleInformation
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) AddedConditionPtr,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC ) IGCycleCounterPtr
);

FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetIGCycleInformation
(
    VAR( boolean, AUTOMATIC )   AddedCondition,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    IGCycleCounter
);

FUNC( void, DEM_CODE ) Dem_IUMPRMng_GetGeneralDenominator
(
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC ) GenDenCounterPtr
);

FUNC( void, DEM_CODE ) Dem_IUMPRMng_GetGenDenInformation
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) AddedConditionPtr,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC ) GenDenCounterPtr
);

FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetGenDenInformation
(
    VAR( boolean, AUTOMATIC )   AddedCondition,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    GenDenCounter
);

FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetIUMPRDenCondition
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )      ConditionId,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  ConditionStatus
);

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPRMng_GetRatioByRatioId
(
    VAR( Dem_RatioIdType, AUTOMATIC )       RatioId,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   NumeCounterPtr,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   DenCounterPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPRMng_GetRatioInformation
(
    VAR( Dem_RatioIdType, AUTOMATIC )       RatioId,
    P2VAR( Dem_u08_IUMPRRatioCondType, AUTOMATIC, AUTOMATIC )    RatioConditionPtr,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   NumeCounterPtr,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   DenCounterPtr
);

FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetRatioInformation
(
    VAR( Dem_RatioIdType, AUTOMATIC )   RatioId,
    VAR( Dem_u08_IUMPRRatioCondType,  AUTOMATIC )            RatioCondition,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )            NumeCounter,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )            DenCounter
);

FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetRatioNumeAdditionCondition
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioId
);
FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetRatioDenUnlockCondition
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioId
);
#endif  /*   ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )      */


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*------------------------------*/
/*  get record data             */
/*------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPRMng_GetEventIdFromRecordData
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
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_IUMPRNvMStatus[DEM_IUMPR_RECORD_NUM];
extern VAR( Dem_IUMPRCommonRecordType, DEM_VAR_NO_INIT ) Dem_TmpIUMPRMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>



#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )    */

#endif /* DEM_RC_IUMPRMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

