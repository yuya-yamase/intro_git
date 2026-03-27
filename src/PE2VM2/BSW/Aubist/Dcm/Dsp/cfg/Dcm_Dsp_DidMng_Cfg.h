/* Dcm_Dsp_DidMng_Cfg_h(v5-6-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_DidMng_Cfg/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_DSP_DIDMNG_CFG_H
#define DCM_DSP_DIDMNG_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_Main.h>
#include <Dcm/Dcm_Dsp_DidMng_ChkSuptDid_Callout.h>
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* DummyData */
#define DCM_P_DIDMNG_DUMMY ((uint16)0U)

/* DcmDspDataFreezeCurrentStateFnc Sync */
#define DCM_P_DATA_SYNC_FCS_FNC_N (uint16)0U
#define DCM_P_DATA_SYNC_FCS_FNC_T (DCM_P_DATA_SYNC_FCS_FNC_N + (uint16)1U)
/* DcmDspDataFreezeCurrentStateFnc Async */
#define DCM_P_DATA_ASYNC_FCS_FNC_N (uint16)0U
#define DCM_P_DATA_ASYNC_FCS_FNC_T (DCM_P_DATA_ASYNC_FCS_FNC_N + (uint16)1U)

/* DcmDspDataReadFnc Sync */
#define DCM_P_DATA_SYNC_READ_FNC_N (uint16)0U
#define DCM_P_DATA_SYNC_READ_FNC_T (DCM_P_DATA_SYNC_READ_FNC_N + (uint16)1U)
/* DcmDspDataReadFnc Async */
#define DCM_P_DATA_ASYNC_READ_FNC_N (uint16)0U
#define DCM_P_DATA_ASYNC_READ_FNC_T (DCM_P_DATA_ASYNC_READ_FNC_N + (uint16)1U)
/* DcmDspDataReadFnc Async Err */
#define DCM_P_DATA_ASYNC_ERR_READ_FNC_N (uint16)0U
#define DCM_P_DATA_ASYNC_ERR_READ_FNC_T (DCM_P_DATA_ASYNC_ERR_READ_FNC_N + (uint16)1U)

/* DcmDspDataResetToDefaultFnc Sync */
#define DCM_P_DATA_SYNC_RTD_FNC_N (uint16)0U
#define DCM_P_DATA_SYNC_RTD_FNC_T (DCM_P_DATA_SYNC_RTD_FNC_N + (uint16)1U)
/* DcmDspDataResetToDefaultFnc Async */
#define DCM_P_DATA_ASYNC_RTD_FNC_N (uint16)0U
#define DCM_P_DATA_ASYNC_RTD_FNC_T (DCM_P_DATA_ASYNC_RTD_FNC_N + (uint16)1U)

/* DcmDspDataReturnControlToEcuFnc Aubist */
#define DCM_P_DATA_RCTECU_FNC_N (uint16)0U
#define DCM_P_DATA_RCTECU_FNC_T (DCM_P_DATA_RCTECU_FNC_N + (uint16)1U)

/* DcmDspDataShortTermAdjustmentFnc Sync */
#define DCM_P_DATA_SYNC_STA_FNC_N (uint16)0U
#define DCM_P_DATA_SYNC_STA_FNC_T (DCM_P_DATA_SYNC_STA_FNC_N + (uint16)1U)
/* DcmDspDataShortTermAdjustmentFnc Async */
#define DCM_P_DATA_ASYNC_STA_FNC_N (uint16)0U
#define DCM_P_DATA_ASYNC_STA_FNC_T (DCM_P_DATA_ASYNC_STA_FNC_N + (uint16)1U)

/* DcmDspData */

/* DcmDspDidXXXXXXSecurityLevelRef */

/* DcmDspDidXXXXXXSessionRef */

/* DcmDspDidControl */

/* DcmDspDidRead */

/* DcmDspDidWrite */

/* DcmDspDidInfo */

/* DcmDspDidSignal */

/* DcmDspDid */
#define DCM_P_DID_N (uint16)0U
#define DCM_P_DID_T (DCM_P_DID_N + (uint16)1U)

/* DcmDspDidRange */
#define DCM_P_DIDRANGE_N (uint16)0U
#define DCM_P_DIDRANGE_T (DCM_P_DIDRANGE_N + (uint16)1U)

/* DcmDspDDDid */
#define DCM_P_DDDID_N (uint16)0U
#define DCM_P_DDDID_T (DCM_P_DDDID_N + (uint16)1U)

/* DcmDspSourceElement */

/* DcmDspReadMemoryRangeSecurityLevelRef */

/* DcmDspReadMemoryRangeSessionLevelRef */

/* DcmDspWriteMemoryRangeSecurityLevelRef */

/* DcmDspWriteMemoryRangeSessionLevelRef */

/* DcmDspReadMemoryRange */

/* DcmDspWriteMemoryRange */

/* DcmDspALFId */

/* DcmDspMemoryId */

/* SID 0x2C */
#define DCM_P_SID2C_RES_MAX_DATA_LENGTH (uint16)0U

/* Source Did Data Size Max */
#define DCM_P_SOURCE_DID_MAX_DATA_SIZE (uint16)1U

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/* -----------------------------FUNCTION TYPE----------------------------- */

/*------------*/
/* DcmDspData */
/*------------*/
/* DcmDspDataConditionCheckReadFnc--------------------- */
typedef CONSTP2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_Data_ConditionCheckReadFuncType)
(
    Dcm_OpStatusType OpStatus,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
);

/* DcmDspDataEcuSignal--------------------------------- */
typedef CONSTP2FUNC( void, DCM_CODE_CALLOUT, Dcm_Dsp_Data_IoHwAb_Dcm_FuncType)
(
    uint8 action,
    uint8 controlSignal
);

/* DcmDspDataFreezeCurrentStateFnc--------------------- */
/* Sync */
typedef P2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_Data_Sync_FreezeCurrentStateFuncType)
(
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
);
/* Async */
typedef P2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_Data_Async_FreezeCurrentStateFuncType)
(
    Dcm_OpStatusType OpStatus,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
);

/* DcmDspDataGetScalingInfoFnc------------------------- */
typedef CONSTP2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_Data_GetScalingInfoFuncType)
(
    Dcm_OpStatusType OpStatus,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ScalingInfo,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
);

/* DcmDspDataReadDataLengthFnc------------------------- */
typedef CONSTP2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_Data_ReadDataLengthFuncType)
(
    Dcm_OpStatusType OpStatus,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) DataLength
);

/* DcmDspDataReadEcuSignal----------------------------- */
typedef CONSTP2FUNC( void, DCM_CODE_CALLOUT, Dcm_Dsp_Data_IoHwAb_Dcm_Read_FuncType)
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) controlSignal
);

/* DcmDspDataReadFnc----------------------------------- */
/* Sync */
typedef P2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_Data_Sync_ReadFuncType)
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) Data
);
/* Async */
typedef P2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_Data_Async_ReadFuncType)
(
    Dcm_OpStatusType OpStatus,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) Data
);
/* Async Err */
typedef P2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_Data_AsyncErr_ReadFuncType)
(
    Dcm_OpStatusType OpStatus,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) Data,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
);

/* DcmDspDataResetToDefaultFnc------------------------- */
/* Sync */
typedef P2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_Data_Sync_ResetToDefaultFuncType)
(
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
);
/* Async */
typedef P2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_Data_Async_ResetToDefaultFuncType)
(
    Dcm_OpStatusType OpStatus,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
);

/* DcmDspDataReturnControlToEcuFnc--------------------- */
/* Aubist */
typedef P2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_Data_ReturnControlToECUFuncType)
(
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
);

/* DcmDspDataShortTermAdjustmentFnc-------------------- */
/* Sync */
typedef P2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_Data_Sync_ShortTermAdjustmentFuncType)
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ControlStateInfo,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
);
/* Async */
typedef P2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_Data_Async_ShortTermAdjustmentFuncType)
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ControlStateInfo,
    Dcm_OpStatusType OpStatus,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
);

/* DcmDspDataWriteFnc---------------------------------- */
typedef CONSTP2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_Data_WriteFuncType)
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) Data,
    uint16 DataLength,
    Dcm_OpStatusType OpStatus,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
);

/*-----------*/
/* DcmDspDid */
/*-----------*/
/* DcmDspDidCheckControlParamFnc----------------------- */
typedef CONSTP2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_Did_CheckControlParamFncType)
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ControlStateInfo,
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ControlMaskInfo
);

/*---------------*/
/* DcmDspDidInfo */
/*---------------*/
/* DcmDspDidInfoModeRuleFnc---------------------------- */
typedef CONSTP2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_DidInfo_ModeRuleFncType)
(
    const uint16 u2DID,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
);

/*----------------*/
/* DcmDspDidRange */
/*----------------*/
/* DcmDspDidRangeIsDidAvailableFnc--------------------- */
typedef CONSTP2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_DidRange_AvailFuncType)
(
    uint16 DID,
    Dcm_OpStatusType OpStatus,
    P2VAR( Dcm_DidSupportedType, AUTOMATIC, DCM_APPL_DATA ) supported
);

/* DcmDspDidRangeReadDataLengthFnc--------------------- */
typedef CONSTP2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_DidRange_ReadLenFuncType)
(
    uint16 DID,
    Dcm_OpStatusType OpStatus,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) DataLength
);

/* DcmDspDidRangeReadDidFnc---------------------------- */
typedef CONSTP2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_DidRange_ReadFuncType)
(
    uint16 DID,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) Data,
    Dcm_OpStatusType OpStatus,
    uint32 DataBufferLength,
    P2VAR( uint32, AUTOMATIC, DCM_APPL_DATA ) DataLength,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
);

/* DcmDspDidRangeWriteDidFnc--------------------------- */
typedef CONSTP2FUNC( Std_ReturnType, DCM_CODE_CALLOUT, Dcm_Dsp_DidRange_WriteFuncType)
(
    uint16 DID,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) Data,
    Dcm_OpStatusType OpStatus,
    uint16 DataLength,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ErrorCode
);

/* -----------------------------TABLE TYPE----------------------------- */

/* DcmDspData */
typedef struct
{
    uint16                                      u2ReturnControlToEcuFnc;
    uint16                                      u2ResetToDefaultFnc;
    uint16                                      u2FreezeCurrentStateFnc;
    uint16                                      u2ShortTermAdjustmentFnc;
    uint16                                      u2ReadFnc;
    uint16                                      u2Size;
    uint8                                       u1Type;
    uint8                                       u1UsePort;
}Dcm_Dsp_DataType;

/* DcmDspDidInfo */
typedef struct
{
    P2CONST( AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST ) ptSecurityLevelRef;
    P2CONST( AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST ) ptSessionRef;
    uint8                                       u1SecurityLevelNum;
    uint8                                       u1SessionNum;
    boolean                                     bResetToDefault;
    boolean                                     bFreezeCurrentState;
    boolean                                     bShortTermAdjustment;
}Dcm_Dsp_DidInfoControlType;

typedef struct
{
    Dcm_Dsp_DidInfo_ModeRuleFncType             ptModeRuleFnc;
    P2CONST( AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST ) ptSecurityLevelRef;
    P2CONST( AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST ) ptSessionRef;
    uint8                                       u1SecurityLevelNum;
    uint8                                       u1SessionNum;
    boolean                                     bUsePort;
}Dcm_Dsp_DidInfoRWType;

typedef struct
{
    P2CONST( AB_83_ConstV Dcm_Dsp_DidInfoControlType, AUTOMATIC, DCM_APPL_CONST ) ptControl;
    P2CONST( AB_83_ConstV Dcm_Dsp_DidInfoRWType, AUTOMATIC, DCM_APPL_CONST ) ptRead;
    P2CONST( AB_83_ConstV Dcm_Dsp_DidInfoRWType, AUTOMATIC, DCM_APPL_CONST ) ptWrite;
    uint8                                       u1DDDIDMaxElements;
    boolean                                     bDynamicallyDefined;
}Dcm_Dsp_DidInfoType;

/* DcmDspDid */
typedef struct
{
    P2CONST( AB_83_ConstV Dcm_Dsp_DataType, AUTOMATIC, DCM_APPL_CONST ) ptDataRef;
    uint16                                      u2DataPos;
}Dcm_Dsp_DidSignalType;

typedef struct
{
    P2CONST( AB_83_ConstV Dcm_Dsp_DidInfoType, AUTOMATIC, DCM_APPL_CONST ) ptInfoRef;
    P2CONST( AB_83_ConstV Dcm_Dsp_DidSignalType, AUTOMATIC, DCM_APPL_CONST ) ptSignal;
    Dcm_Dsp_Did_CheckControlParamFncType        pCheckControlParamFnc;
    uint16                                      u2Identifier;
    uint8                                       u1SignalNum;
    boolean                                     bUsePort;
    boolean                                     bUsed;
}Dcm_Dsp_DidType;

typedef struct
{
    uint32                                      u4MemAddr;
    uint32                                      u4MemSize;
    uint16                                      u2SourceDid;
    uint8                                       u1Position;
    uint8                                       u1Size;
    uint8                                       u1MemId;
    uint8                                       u1SourceElementId;
}Dcm_Dsp_SourceElementType;

typedef struct
{
    CONSTP2VAR( AB_83_ConstV Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA ) ptSourceElementRef;
    const uint16                                u2DDDid;
}Dcm_Dsp_DDDidType;

/* DcmDspDidRange */
typedef struct
{
    Dcm_Dsp_DidRange_AvailFuncType              ptIsDidAvailableFnc;
    Dcm_Dsp_DidRange_ReadLenFuncType            ptReadDataLengthFnc;
    Dcm_Dsp_DidRange_ReadFuncType               ptReadDidFnc;
    Dcm_Dsp_DidRange_WriteFuncType              ptWriteDidFnc;
    P2CONST( AB_83_ConstV Dcm_Dsp_DidInfoType, AUTOMATIC, DCM_APPL_CONST ) ptInfoRef;
    uint16                                      u2IdentifierLowerLimit;
    uint16                                      u2IdentifierUpperLimit;
    boolean                                     bHasGaps;
    boolean                                     bUsePort;
}Dcm_Dsp_DidRangeType;

/* DcmDspMemory */
typedef struct
{
    P2CONST( AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST ) ptMemoryRangeSecurityLevelRef;
    P2CONST( AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST ) ptMemoryRangeSessionLevelRef;
    uint32                                      u4MemoryRangeHigh;
    uint32                                      u4MemoryRangeLow;
    uint8                                       u1MemoryRangeSecurityLevelNum;
    uint8                                       u1MemoryRangeSessionLevelNum;
}Dcm_Dsp_MemoryRangeInfoType;

typedef struct
{
    P2CONST( AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST ) ptSupportedALFId;
    uint8                                       u1SupportedALFIdNum;
}Dcm_Dsp_ALFIdType;

typedef struct
{
    P2CONST( AB_83_ConstV Dcm_Dsp_MemoryRangeInfoType, AUTOMATIC, DCM_APPL_CONST ) ptReadMemoryRangeInfo;
    P2CONST( AB_83_ConstV Dcm_Dsp_MemoryRangeInfoType, AUTOMATIC, DCM_APPL_CONST ) ptWriteMemoryRangeInfo;
    uint8                                       u1ReadMemoryRangeInfoNum;
    uint8                                       u1WriteMemoryRangeInfoNum;
    uint8                                       u1MemoryIdValue;
    boolean                                     bMemoryIdValueFlag;
}Dcm_Dsp_MemoryIdInfoType;

typedef struct
{
    P2CONST( AB_83_ConstV Dcm_Dsp_ALFIdType, AUTOMATIC, DCM_APPL_CONST ) ptALFId;
    P2CONST( AB_83_ConstV Dcm_Dsp_MemoryIdInfoType, AUTOMATIC, DCM_APPL_CONST ) ptMemoryIdInfo;
    uint8                                       u1MemoryIdInfoNum;
}Dcm_Dsp_MemoryType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if ( DCM_SUPPORT_SID2C == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_SetSourceDID
(
    const uint16 u2DDDidIndex,
    const uint8 u1SourceDidIndex,
    P2CONST(Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA) ptSourceElement
);
#endif /* DCM_SUPPORT_SID2C == STD_ON */
#if ( DCM_SUPPORT_SID2C == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_SetNumOfSrcDid
(
    const uint16 u2DDDidIndex,
    const uint8 u1NumOfSourceDid
);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ClrNumOfSrcElm
(
    const uint16 u2DDDidIndex
);
#endif /* DCM_SUPPORT_SID2C == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_ClrAllNumOfSrcElm
(
    void
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON  */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetNumOfSrcDid
(
    const uint16 u2DDDidIndex,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptNumOfSourceDid
);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_GetSourceDID
(
    const uint16 u2DDDidIndex,
    const uint8 u1SourceDidIndex,
    P2VAR( Dcm_Dsp_SourceElementType, AUTOMATIC, DCM_APPL_DATA) ptSourceElement
);
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_DidMng_CheckSupportedDid
(
    uint16 u2Did,
    Dcm_DidRequestType u1ReqType,
    uint16 u2PduId
);
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
extern VAR( uint8, DCM_VAR_NO_INIT ) DcmDspDDDidNumOfSourceElement[ DCM_P_DDDID_T ];
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/* -----------------------------VALUE TABLE----------------------------- */
#define DCM_START_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#if ( DCM_SUPPORT_SID2F == STD_ON )
extern CONST( AB_83_ConstV Dcm_Dsp_Data_Sync_FreezeCurrentStateFuncType, DCM_CONFIG_DATA ) DcmDspDataSyncFreezeCurrentStateFuncTbl[ DCM_P_DATA_SYNC_FCS_FNC_T ];
extern CONST( AB_83_ConstV Dcm_Dsp_Data_Async_FreezeCurrentStateFuncType, DCM_CONFIG_DATA ) DcmDspDataAsyncFreezeCurrentStateFuncTbl[ DCM_P_DATA_ASYNC_FCS_FNC_T ];
extern CONST( AB_83_ConstV Dcm_Dsp_Data_Sync_ReadFuncType, DCM_CONFIG_DATA ) DcmDspDataSyncReadFuncTbl[ DCM_P_DATA_SYNC_READ_FNC_T ];
extern CONST( AB_83_ConstV Dcm_Dsp_Data_Async_ReadFuncType, DCM_CONFIG_DATA ) DcmDspDataAsyncReadFuncTbl[ DCM_P_DATA_ASYNC_READ_FNC_T ];
extern CONST( AB_83_ConstV Dcm_Dsp_Data_AsyncErr_ReadFuncType, DCM_CONFIG_DATA ) DcmDspDataAsyncErrReadFuncTbl[ DCM_P_DATA_ASYNC_ERR_READ_FNC_T ];
extern CONST( AB_83_ConstV Dcm_Dsp_Data_Sync_ResetToDefaultFuncType, DCM_CONFIG_DATA ) DcmDspDataSyncResetToDefaultFuncTbl[ DCM_P_DATA_SYNC_RTD_FNC_T ];
extern CONST( AB_83_ConstV Dcm_Dsp_Data_Async_ResetToDefaultFuncType, DCM_CONFIG_DATA ) DcmDspDataAsyncResetToDefaultFuncTbl[ DCM_P_DATA_ASYNC_RTD_FNC_T ];
extern CONST( AB_83_ConstV Dcm_Dsp_Data_ReturnControlToECUFuncType, DCM_CONFIG_DATA ) DcmDspDataReturnControlToECUFuncTbl[ DCM_P_DATA_RCTECU_FNC_T ];
extern CONST( AB_83_ConstV Dcm_Dsp_Data_Sync_ShortTermAdjustmentFuncType, DCM_CONFIG_DATA ) DcmDspDataSyncShortTermAdjustmentFuncTbl[ DCM_P_DATA_SYNC_STA_FNC_T ];
extern CONST( AB_83_ConstV Dcm_Dsp_Data_Async_ShortTermAdjustmentFuncType, DCM_CONFIG_DATA ) DcmDspDataAsyncShortTermAdjustmentFuncTbl[ DCM_P_DATA_ASYNC_STA_FNC_T ];
#endif /* DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
extern CONST( AB_83_ConstV Dcm_Dsp_DidType, DCM_CONFIG_DATA ) DcmDspDidTbl[ DCM_P_DID_T ];
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
extern CONST( AB_83_ConstV Dcm_Dsp_DDDidType, DCM_CONFIG_DATA ) DcmDspDDDidTbl[ DCM_P_DDDID_T ];
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
extern CONST( AB_83_ConstV Dcm_Dsp_DidRangeType, DCM_CONFIG_DATA ) DcmDspDidRangeTbl[ DCM_P_DIDRANGE_T ];
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_SEND_USE == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) || ( DCM_SUPPORT_SID3D == STD_ON ) )
extern CONST( AB_83_ConstV Dcm_Dsp_MemoryType, DCM_CONFIG_DATA ) DcmDspMemory;
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON || DCM_SUPPORT_SID3D == STD_ON */

#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
extern CONST( AB_83_ConstV boolean, DCM_CONFIG_DATA ) Dcm_P_DIDMNG_bChk_Per_Source_Did;
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_DIDMNG_u2DidNumber;
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */
#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_DIDMNG_u2DidRangeNumber;
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID23 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_DIDMNG_u2DDDidNumber;
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID23 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */

#if ( DCM_SUPPORT_SID2F == STD_ON )
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Sync_Fcs_Fnc_T;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Async_Fcs_Fnc_T;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Sync_Read_Fnc_T;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Async_Read_Fnc_T;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Async_Err_Read_FNC_T;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Sync_RTD_Fnc_T;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Async_RTD_Fnc_T;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_RCTECU_Fnc_T;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Sync_STA_Fnc_T;
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Data_Async_STA_Fnc_T;
#endif /* DCM_SUPPORT_SID2F == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Did_T;
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */
#if ( ( DCM_M_USE_VINDATAIDENTIFIER == STD_ON ) || ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Didrange_T;
#endif /* DCM_M_USE_VINDATAIDENTIFIER == STD_ON || DCM_PERIODIC_DDDID_USE == STD_ON || DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_PERIODIC_SEND_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) || ( DCM_SUPPORT_SID2E == STD_ON ) || ( DCM_SUPPORT_SID2F == STD_ON ) )
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Dddid_T;
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_PERIODIC_SEND_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON || DCM_SUPPORT_SID2E == STD_ON || DCM_SUPPORT_SID2F == STD_ON */
#if ( DCM_SUPPORT_SID2C == STD_ON )
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Sid2c_Res_Max_Data_Length;
#endif /* DCM_SUPPORT_SID2C == STD_ON */
#if ( ( DCM_PERIODIC_DDDID_USE == STD_ON ) || ( DCM_SUPPORT_SID22 == STD_ON ) || ( DCM_SUPPORT_SID2C == STD_ON ) )
extern CONST( AB_83_ConstV uint16, DCM_CONFIG_DATA ) Dcm_P_u2Source_Did_Max_Data_Size;
#endif /* DCM_PERIODIC_DDDID_USE == STD_ON || DCM_SUPPORT_SID22 == STD_ON || DCM_SUPPORT_SID2C == STD_ON */

#define DCM_STOP_SEC_CONST_CONFIG
#include <Dcm_MemMap.h>

#endif /* DCM_DSP_DIDMNG_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-08-20                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-6-0         :2024-02-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
