/* IdsM_Cfg_Fixed_h_v2-0-1                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | IdsM/HEADER                                                */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef IDSM_CFG_FIXED_H
#define IDSM_CFG_FIXED_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <IdsM.h>
#include "../cfg/IdsM_Cfg.h"
#include "./IdsM_General.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define IDSM_EVENTFRAME_SIZE  (8U)

#if ( IDSM_CFG_USE_FILTERCHAIN == STD_ON )
#define IDSM_FILTER_CHAINS    (4U)
#endif /* ( IDSM_CFG_USE_FILTERCHAIN == STD_ON ) */
#if (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ))
#define IDSM_GLOBAL_RATEFILS  (2U)
#endif /* (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
typedef uint8 IdsM_CtxDataBuffStatusType;

typedef struct {
    uint16  u2CtxDataBuffSize;
    uint16  u2CtxDataBuffNum;
    P2VAR(volatile IdsM_CtxDataBuffStatusType, IDSM_CONFIG_DATA, IDSM_VAR_NO_INIT) ptCtxDataStatus;
    P2VAR(volatile uint8, IDSM_CONFIG_DATA, IDSM_VAR_NO_INIT) ptCtxData;
} IdsMCtxDataBuffType;

typedef struct {
    P2CONST(AB_83_ConstV IdsMCtxDataBuffType, IDSM_CONFIG_DATA, IDSM_CONFIG_DATA) ptCData;
} IdsMCtxDataBuffAcssType;

typedef struct {
    P2CONST(AB_83_ConstV IdsMCtxDataBuffAcssType, IDSM_CONFIG_DATA, IDSM_CONFIG_DATA) ptCBox;
    uint16  u2CBNum;
    uint16  u2Dummy;
} IdsMCtxDataBoxAcssType;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */

typedef struct {
#if ( IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE )
    IdsM_TimestampType  udTimestamp;
#endif /* ( IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE ) */
    IdsM_SecurityEventIdType    udSEvId;
    uint16  u2Count;
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
    uint16  u2CtxDataSize;
    uint16  u2Dummy;
    uint16  u2TableIndex;
    uint16  u2RecordIndex;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
} IdsMEventBuffType;

#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
typedef struct {
#if ( IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE )
    IdsM_TimestampType  udTimestamp; 
#endif /* ( IDSM_CFG_USE_TIMESTAMP != IDSM_TS_OPT_NONE ) */
    uint16  u2Count;
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
    uint16  u2CtxDataSize;
    uint16  u2TableIndex;
    uint16  u2RecordIndex;
#else
    uint16  u2Dummy;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
} IdsMAggreFilTmpType;
#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */

#if ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )
typedef struct {
    uint16  u2EveThreCount;
    uint16  u2Dummy;
} IdsMThreFilTmpType;
#endif /* ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) */

#if ( IDSM_CFG_USE_FIL_NTH == STD_ON )
typedef struct {
    uint16  u2NthFilSEvCnt;
    uint16  u2Dummy;
} IdsMNthFilTmpType;
#endif /* ( IDSM_CFG_USE_FIL_NTH == STD_ON ) */

typedef struct {
    IdsMEventBuffType   stEventInfo;
    boolean             bIdsRQSEvGet;
    boolean             bDemQSEvGet;
    uint16              u2Dummy;
} IdsMQSEvBuffType;

#if ( IDSM_CFG_USE_FIL_RATELMT == STD_ON )
typedef struct {
    uint32     u4RateLimitTimeInterval;
    uint16     u2RateLimitMaxEve;
    uint16     u2Dummy;
} IdsMFilEveRateLimitType;
#endif /* ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) */

#if ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )
typedef struct {
    uint32     u4TrafficLimitTimeInterval;
    uint16     u2TrafficLimitMaxByte;
    uint16     u2Dummy;
} IdsMFilTrafficLimitType;
#endif /* ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ) */

typedef struct {
    uint16                          u2ExternalEventId;
    IdsM_Filters_ReportingModeType  udReportModeFilter;
    uint8                           u1SensorInstanceId;
    boolean                         bSinkDem;
    boolean                         bSinkIdsR;
    uint16                          u2FilterChainRef;
    uint16                          u2AggreFilDataRef;
    uint16                          u2ThreFilDataRef;
    uint16                          u2NthFilDataRef;
#if ( IDSM_CFG_USE_DEM == STD_ON )
    Dem_EventIdType                 udDemEventId;
    uint16                          u2DemBuffSize;
#endif /* (IDSM_CFG_USE_DEM == STD_ON ) */
    uint16                          u2Dummy;
} IdsMEventType;

typedef struct {
    P2CONST(AB_83_ConstV IdsMEventType, IDSM_CONFIG_DATA, IDSM_CONFIG_DATA) ptConfig;
    uint16                 u2ConfigNum;
    uint16                 u2Dummy;
} IdsMEventAcssType;

#if ( IDSM_CFG_USE_FILTERCHAIN == STD_ON )
#if ( IDSM_CFG_USE_FIL_BLKSTATE == STD_ON )
typedef struct {
    uint16  u2BlkStateRef;
    uint16  u2Dummy;
} IdsMBlkStateFilType;
#endif /* ( IDSM_CFG_USE_FIL_BLKSTATE == STD_ON ) */

#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
typedef struct {
    uint8   u1CtxDataSourceSelector;
    uint8   u1Dummy1;
    uint8   u1Dummy2;
    uint8   u1Dummy3;
    uint32  u4AggreTimeInterval;
} IdsMEveAggreFilType;
#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */

#if ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )
typedef struct {
    uint16  u2EveThreNumber;
    uint16  u2Dummy;
    uint32  u4EventThresholdTimeInterval;
} IdsMEveThresholdFilType;
#endif /* ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) */

#if ( IDSM_CFG_USE_FIL_NTH == STD_ON )
typedef struct {
    uint16  u2NthParam;
    uint16  u2Dummy;
} IdsMFwdEveryNthFilType;
#endif /* ( IDSM_CFG_USE_FIL_NTH == STD_ON ) */

typedef struct {
#if ( IDSM_CFG_USE_FIL_BLKSTATE == STD_ON )
    IdsMBlkStateFilType      stBlkStateFil;
#endif /* ( IDSM_CFG_USE_FIL_BLKSTATE == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
    IdsMEveAggreFilType       stEveAggreFil;
#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )
    IdsMEveThresholdFilType  stEveThreFil;
#endif /* ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_NTH == STD_ON )
    IdsMFwdEveryNthFilType   stEveNthFil;
#endif /* ( IDSM_CFG_USE_FIL_NTH == STD_ON ) */
} IdsMFilterChainType;

typedef struct {
    P2CONST(AB_83_ConstV IdsMFilterChainType, IDSM_CONFIG_DATA, IDSM_CONFIG_DATA) ptConfig;
    uint16                      u2ConfigNum;
    uint16                      u2Dummy;
} IdsMFilterChainAcssType;
#endif /* ( IDSM_CFG_USE_FILTERCHAIN == STD_ON ) */

typedef struct {
    P2VAR(volatile IdsMEventBuffType, IDSM_CONFIG_DATA, IDSM_VAR_NO_INIT) ptEventBuff;
    uint16              u2ConfigNum;
    uint16              u2Dummy;
}IdsMEventBuffAcssType;

#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
typedef struct {
    P2VAR(volatile IdsMAggreFilTmpType, IDSM_CONFIG_DATA, IDSM_VAR_NO_INIT) ptTmp;
    uint16                  u2ConfigNum;
    uint16                  u2Dummy;
}IdsMAggreFilTmpAcssType;
#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */

#if ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )
typedef struct {
    P2VAR(volatile IdsMThreFilTmpType, IDSM_CONFIG_DATA, IDSM_VAR_NO_INIT) ptTmp;
    uint16                  u2ConfigNum;
    uint16                  u2Dummy;
}IdsMThreFilTmpAcssType;
#endif /* ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) */

#if ( IDSM_CFG_USE_FIL_NTH == STD_ON )
typedef struct {
    P2VAR(volatile IdsMNthFilTmpType, IDSM_CONFIG_DATA, IDSM_VAR_NO_INIT) ptTmp;
    uint16                  u2ConfigNum;
    uint16                  u2Dummy;
}IdsMNthFilTmpAcssType;
#endif /* ( IDSM_CFG_USE_FIL_NTH == STD_ON ) */

typedef struct {
    P2VAR(volatile IdsMQSEvBuffType, IDSM_CONFIG_DATA, IDSM_VAR_NO_INIT) ptQSEvBuff;
    uint16              u2ConfigNum;
    uint16              u2Dummy;
}IdsMQSEvBuffAcssType;

#if ( IDSM_CFG_USE_IDSR == STD_ON )
typedef struct {
    P2VAR(uint8, IDSM_CONFIG_DATA, IDSM_VAR_NO_INIT) ptIdsRTxBuff;
    uint16  u2BuffSize;
    uint16  u2Dummy;
}IdsMIdsRTxBuffAcssType;
#endif /* ( IDSM_CFG_USE_IDSR == STD_ON ) */

#if ( IDSM_CFG_USE_DEM == STD_ON )
typedef struct {
    P2VAR(uint8, IDSM_CONFIG_DATA, IDSM_VAR_NO_INIT) ptDemTxBuff;
    uint16  u2BuffSize;
    uint16  u2Dummy;
}IdsMDemTxBuffAcssType;
#endif /* ( IDSM_CFG_USE_DEM == STD_ON ) */

#if ( IDSM_CFG_USE_IDSR == STD_ON )
typedef P2FUNC(Std_ReturnType, IDSM_APPL_CODE, IdsM_TxCalloutType)
(
    P2CONST(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) ptData,
    VAR(uint16, AUTOMATIC) u2DataSize
);
#endif /* ( IDSM_CFG_USE_IDSR == STD_ON ) */

typedef P2FUNC(void, IDSM_APPL_CODE, IdsM_QSEvErrCalloutType)
(
    P2CONST(uint8, AUTOMATIC, IDSM_VAR_NO_INIT) ptEventFrame,
    P2CONST(IdsM_TimestampType, AUTOMATIC, IDSM_VAR_NO_INIT) ptTimestamp,
    P2CONST(volatile uint8, AUTOMATIC, IDSM_VAR_NO_INIT) ptContextData,
    VAR(uint16, AUTOMATIC) u2ContextDataSize,
    VAR(IdsM_Ab_ErrorStatusType, AUTOMATIC) udQSEvError
);

typedef P2FUNC(void, IDSM_APPL_CODE, IdsM_ParamErrCalloutType)
(
    VAR(IdsM_SecurityEventIdType, AUTOMATIC) udSecurityEventId,
    VAR(IdsM_Ab_ErrorStatusType, AUTOMATIC) udParamError
);

typedef P2FUNC(void, IDSM_APPL_CODE, IdsM_RamErrCalloutType)
(
    VAR(IdsM_Ab_ErrorStatusType, AUTOMATIC) udRamErr
);

typedef struct {
    IdsMEventBuffType       stSEvData;
    uint16                  u2Index;
    uint16                  u2Dummy;
}IdsMFilterFuncParamType;

#if (( IDSM_CFG_USE_FILTERCHAIN == STD_ON ) || ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ))
typedef P2FUNC(IdsM_FilterResultType, IDSM_CODE, IdsM_FilterFuncType )
(
    P2CONST(IdsMFilterFuncParamType, AUTOMATIC,IDSM_APPL_CONST) ptFilFuncParam,
    P2VAR(uint16, AUTOMATIC, IDSM_APPL_DATA) ptTableIndex,
    P2VAR(uint16, AUTOMATIC, IDSM_APPL_DATA) ptRecordIndex
);
#endif /* (( IDSM_CFG_USE_FILTERCHAIN == STD_ON ) || ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )) */

#if ( IDSM_CFG_USE_FILTERCHAIN == STD_ON )
typedef struct {
    IdsM_FilterFuncType    ptFunc[ IDSM_FILTER_CHAINS ];
} IdsMFilChainFuncTblType;

typedef struct {
    P2CONST(AB_83_ConstV IdsMFilChainFuncTblType, IDSM_CONFIG_DATA, IDSM_CONFIG_DATA) ptConfig;
    uint16                  u2ConfigNum;
    uint16                  u2Dummy;
} IdsMFilChainFuncTblAcssType;
#endif /* ( IDSM_CFG_USE_FILTERCHAIN == STD_ON ) */

#if (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ))
typedef struct {
    IdsM_FilterFuncType    ptFunc[ IDSM_GLOBAL_RATEFILS ];
} IdsMGlobalRateFilFuncTblType;
#endif /* (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )) */

#if (( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ))
typedef struct {
#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
    uint32  u4AggreFilTimeCnt;
#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )
    uint32  u4ThresholdFilTimeCnt;
#endif /* ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) */
} IdsMFilChainTmpType;
#endif /* (( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )) */

#if (( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ))
typedef struct {
    P2VAR(volatile IdsMFilChainTmpType, IDSM_CONFIG_DATA, IDSM_VAR_NO_INIT) ptTmp;
    uint16    u2ConfigNum;
    uint16    u2Dummy;
} IdsMFilChainTmpAcssType;
#endif /* (( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )) */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define IDSM_START_SEC_VAR_NO_INIT
#include <IdsM_MemMap.h>

#if ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON )
extern VAR(volatile IdsMEventBuffType, IDSM_VAR_NO_INIT) IdsM_Cfg_InterBuff_EveBuffFull;
#endif /* ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) */
#if ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON )
extern VAR(volatile IdsMEventBuffType, IDSM_VAR_NO_INIT) IdsM_Cfg_InterBuff_CtxBuffFull;
#endif /* ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) */
#if ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON )
extern VAR(volatile IdsMEventBuffType, IDSM_VAR_NO_INIT) IdsM_Cfg_InterBuff_TrafficLimit;
#endif /* ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ) */

#define IDSM_STOP_SEC_VAR_NO_INIT
#include <IdsM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define IDSM_START_SEC_CONST_CONFIG
#include <IdsM_MemMap.h>

extern CONST(AB_83_ConstV uint16, IDSM_CONFIG_DATA) IdsM_Cfg_u2InstanceId;
extern CONST(AB_83_ConstV IdsMEventBuffAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_EventBuffAcss;
#if ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON )
extern CONST(AB_83_ConstV IdsMAggreFilTmpAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_AggreFilTmpAcss;
#endif /* ( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )
extern CONST(AB_83_ConstV IdsMThreFilTmpAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_ThreFilTmpAcss;
#endif /* ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_NTH == STD_ON )
extern CONST(AB_83_ConstV IdsMNthFilTmpAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_NthFilTmpAcss;
#endif /* ( IDSM_CFG_USE_FIL_NTH == STD_ON ) */
extern CONST(AB_83_ConstV IdsMQSEvBuffAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_QSEvBuffAcss;
#if ( IDSM_CFG_USE_IDSR == STD_ON )
extern CONST(AB_83_ConstV IdsMIdsRTxBuffAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_IdsRTxBuffAcss;
#endif /* ( IDSM_CFG_USE_IDSR == STD_ON ) */
#if ( IDSM_CFG_USE_DEM == STD_ON )
extern CONST(AB_83_ConstV IdsMDemTxBuffAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_DemTxBuffAcss;
#endif /* ( IDSM_CFG_USE_DEM == STD_ON ) */
#if ( IDSM_CFG_USE_CTXDATA == STD_ON )
extern CONST(AB_83_ConstV IdsMCtxDataBoxAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_CtxDataBoxAcss;
#endif /* ( IDSM_CFG_USE_CTXDATA == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_RATELMT == STD_ON )
extern CONST(AB_83_ConstV IdsMFilEveRateLimitType, IDSM_CONFIG_DATA)  IdsM_Cfg_FilEveRateLimit;
#endif /* ( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) */
#if ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )
extern CONST(AB_83_ConstV IdsMFilTrafficLimitType, IDSM_CONFIG_DATA) IdsM_Cfg_FilTrafficLimit;
#endif /* ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ) */
extern CONST(AB_83_ConstV IdsMEventAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_EventAcss;
#if ( IDSM_CFG_USE_FILTERCHAIN == STD_ON )
extern CONST(AB_83_ConstV IdsMFilterChainAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_FilterChainAcss;
#endif /* ( IDSM_CFG_USE_FILTERCHAIN == STD_ON ) */
extern CONST(AB_83_ConstV boolean, IDSM_CONFIG_DATA) IdsM_Cfg_bDevErroDetect;
extern CONST(AB_83_ConstV boolean, IDSM_CONFIG_DATA) IdsM_Cfg_bDiagnosticSupport;
extern CONST(AB_83_ConstV boolean, IDSM_CONFIG_DATA) IdsM_Cfg_bSignatureSupport;
extern CONST(AB_83_ConstV boolean, IDSM_CONFIG_DATA) IdsM_Cfg_bVersionInfoApi;
#if ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR )
extern CONST(AB_83_ConstV uint16, IDSM_CONFIG_DATA) IdsM_Cfg_u2StbMSyncTimeBaseRef;
#endif /* ( IDSM_CFG_USE_TIMESTAMP == IDSM_TS_OPT_AUTOSAR ) */
#if ( IDSM_CFG_USE_IDSR == STD_ON )
extern CONST(AB_83_ConstV uint16, IDSM_CONFIG_DATA) IdsM_Cfg_u2IfTxHandleId;
extern CONST(AB_83_ConstV uint16, IDSM_CONFIG_DATA) IdsM_Cfg_u2IfTxPduRef;
extern CONST(AB_83_ConstV uint32, IDSM_CONFIG_DATA) IdsM_Cfg_u4TxPduRTimeOut;
extern CONST(AB_83_ConstV IdsM_TxCalloutType, IDSM_CONFIG_DATA) IdsM_Cfg_ptIdsRTxCalloutFunc;
#endif /* ( IDSM_CFG_USE_IDSR == STD_ON ) */
extern CONST(AB_83_ConstV IdsM_QSEvErrCalloutType, IDSM_CONFIG_DATA) IdsM_Cfg_ptQSEvErrCalloutFunc;
#if ( IDSM_CFG_DEM_BUFF_PADDING == STD_ON )
extern CONST(AB_83_ConstV uint8, IDSM_CONFIG_DATA) IdsM_Cfg_u1DemBuffPaddingData;
#endif /* ( IDSM_CFG_DEM_BUFF_PADDING == STD_ON ) */
extern CONST(AB_83_ConstV IdsM_ParamErrCalloutType, IDSM_CONFIG_DATA) IdsM_Cfg_ptParamErrCalloutFunc;
extern CONST(AB_83_ConstV IdsM_RamErrCalloutType, IDSM_CONFIG_DATA) IdsM_Cfg_ptRamErrCalloutFunc;
extern CONST(AB_83_ConstV uint16, IDSM_CONFIG_DATA) IdsM_Cfg_u2CtxDataBuffMaxSize;
#if ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON )
extern CONST(AB_83_ConstV IdsM_SecurityEventIdType, IDSM_CONFIG_DATA) IdsM_Cfg_udEveFullId;
#endif /* ( IDSM_CFG_USE_INTSEV_EVEBUFFUL == STD_ON ) */
#if ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON )
extern CONST(AB_83_ConstV IdsM_SecurityEventIdType, IDSM_CONFIG_DATA) IdsM_Cfg_udCtxFullId;
#endif /* ( IDSM_CFG_USE_INTSEV_CTXBUFFUL == STD_ON ) */
#if ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON )
extern CONST(AB_83_ConstV IdsM_SecurityEventIdType, IDSM_CONFIG_DATA) IdsM_Cfg_udTrafficExceedId;
#endif /* ( IDSM_CFG_USE_INTSEV_TRAFFICLMIT == STD_ON ) */
#if ( IDSM_CFG_USE_FILTERCHAIN == STD_ON )
extern CONST(AB_83_ConstV IdsMFilChainFuncTblAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_FilChainFuncTblAcss;
#endif /* ( IDSM_CFG_USE_FILTERCHAIN == STD_ON ) */
#if (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON ))
extern CONST(AB_83_ConstV IdsMGlobalRateFilFuncTblType, IDSM_CONFIG_DATA) IdsM_Cfg_GlobalRateFilFuncTbl;
#endif /* (( IDSM_CFG_USE_FIL_RATELMT == STD_ON ) || ( IDSM_CFG_USE_FIL_TRAFFICLMT == STD_ON )) */
#if (( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON ))
extern CONST(AB_83_ConstV IdsMFilChainTmpAcssType, IDSM_CONFIG_DATA) IdsM_Cfg_FilChainTmpAcss;
#endif /* (( IDSM_CFG_USE_FIL_AGGREGATION == STD_ON ) || ( IDSM_CFG_USE_FIL_THRESHOLD == STD_ON )) */

#define IDSM_STOP_SEC_CONST_CONFIG
#include <IdsM_MemMap.h>

#endif /* IDSM_CFG_FIXED_H */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2022/11/30                                                  */
/*  v2-0-1     :2023/02/24                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/

