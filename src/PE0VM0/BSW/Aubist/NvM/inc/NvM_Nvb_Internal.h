/* NvM_Nvb_Internal.h v2-1-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/NVB/INTERNAL/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_NVB_INTERNAL_H
#define     NVM_NVB_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <MemIf.h>
#include "../cfg/NvM_Cfg.h"
#include "NvM_Lib.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* OperationId */
#define NVM_NVB_OPERATION_NONE               (NVM_RND_NUM_UINT32_30)

/* Internal main status */
#define NVM_NVB_IDLING                       (NVM_RND_NUM_UINT32_20)
#define NVM_NVB_RUNNING_ACTIVE               (NVM_RND_NUM_UINT32_21)
#define NVM_NVB_RUNNING_NORMAL_WAITING       (NVM_RND_NUM_UINT32_22)
#define NVM_NVB_RUNNING_CANCEL_WAITING       (NVM_RND_NUM_UINT32_23)

/* OperationId serial number */
#define NVM_NVB_OPERATIONID_SER_READ         (0x00000000U)
#define NVM_NVB_OPERATIONID_SER_WRITE        (0x00000001U)

#define NVM_NVB_OPERATIONID_SER_INVALID      (0xFFFFFFFFU)

/* Internal sub status */
/* Common */
#define NVM_NVB_SUB_INVALID                  (NVM_RND_NUM_UINT32_00)

/* Read operation */
#define NVM_NVB_SUB_RD_NTV_RSP               (NVM_RND_NUM_UINT32_01)
#define NVM_NVB_SUB_RD_RDT_RPR_RD_MAIN_RSP   (NVM_RND_NUM_UINT32_02)
#define NVM_NVB_SUB_RD_RDT_RPR_RD_SUB_RSP    (NVM_RND_NUM_UINT32_03)
#define NVM_NVB_SUB_RD_RDT_RPR_WT_MAIN_RSP   (NVM_RND_NUM_UINT32_04)
#define NVM_NVB_SUB_RD_RDT_RPR_WT_SUB_RSP    (NVM_RND_NUM_UINT32_05)

/* Write operation */
#define NVM_NVB_SUB_WT_NTV_RSP               (NVM_RND_NUM_UINT32_01)
#define NVM_NVB_SUB_WT_RDT_RPR_RD_MAIN_RSP   (NVM_RND_NUM_UINT32_02)
#define NVM_NVB_SUB_WT_RDT_RPR_RD_SUB_RSP    (NVM_RND_NUM_UINT32_03)
#define NVM_NVB_SUB_WT_RDT_RPR_WT_MAIN_RSP   (NVM_RND_NUM_UINT32_04)
#define NVM_NVB_SUB_WT_RDT_RPR_WT_SUB_RSP    (NVM_RND_NUM_UINT32_05)
#define NVM_NVB_SUB_WT_RDT_WT_MAIN_RSP       (NVM_RND_NUM_UINT32_06)
#define NVM_NVB_SUB_WT_RDT_WT_SUB_RSP        (NVM_RND_NUM_UINT32_07)

/* Internal sub status */
#define NVM_NVB_SUB_COMMON_SEQ_00            (0U)
#define NVM_NVB_SUB_COMMON_SEQ_01            (1U)
#define NVM_NVB_SUB_COMMON_SEQ_02            (2U)
#define NVM_NVB_SUB_COMMON_SEQ_03            (3U)
#define NVM_NVB_SUB_COMMON_SEQ_04            (4U)
#define NVM_NVB_SUB_COMMON_SEQ_05            (5U)
#define NVM_NVB_SUB_COMMON_SEQ_06            (6U)
#define NVM_NVB_SUB_INVALID_SEQ              (0xFFU)

#define NVM_NVB_SUB_COMMON_NUM               (7U)

/* For MemIf access */
#define NVM_NVB_OFFSET_NONE                  (0x00U)

#define NVM_NVB_DUMMY_DEVICE_ID              (0x00U)

#define NVM_NVB_DATA_INDEX_NATIVE            (0x00U)
#define NVM_NVB_DATA_INDEX_REDUNDANT_MAIN    (0x00U)
#define NVM_NVB_DATA_INDEX_REDUNDANT_SUB     (0x01U)

/* MemIf job invalid infomation */
#define NVM_NVB_MEMIF_BLOCK_NUMBER_INVALID   (0xFFFFU)
#define NVM_NVB_MEMIF_JOB_INVALID            (0xFFU)
#define NVM_NVB_MEMIF_LEVEL_INVALID          (0xFFU)

/* Repair need */
#define NVM_NVB_RPR_NEED_UNNEED              (0x00U)
#define NVM_NVB_RPR_NEED_NEED_MAIN           (0x01U)
#define NVM_NVB_RPR_NEED_NEED_SUB            (0x02U)
#define NVM_NVB_RPR_NEED_UNKNOWN             (0x03U)
#define NVM_NVB_RPR_NEED_NODATA              (0x04U)
#define NVM_NVB_RPR_NEED_INVALID             (0xFFU)

/* Pair num of MemIf read result for main and sub. */
#define NVM_NVB_MEMIF_RESULT_PAIR_NUM        (0x06U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef uint32 NvM_Nvb_MainStatusType;
typedef uint32 NvM_Nvb_SubStatusType;

typedef P2FUNC( NvM_Nvb_MainStatusType, NVM_CODE, NvM_Nvb_ActFuncType )( void );

typedef struct {
    NvM_Nvb_ActFuncType NvM_Nvb_OperationStartFuncPtr;
    P2CONST( AB_83_ConstV uint16,              NVM_CONST, NVM_CONST ) OperationExecFuncNumPtr;
    P2CONST( AB_83_ConstV NvM_Nvb_ActFuncType, NVM_CONST, NVM_CONST ) OperationExecFuncPtrTblAddr;
    NvM_Nvb_ActFuncType NvM_Nvb_CancelFuncPtr;
} NvM_Nvb_OperationActTblType;

typedef struct {
    MemIf_JobResultType MemIfMainResult;
    MemIf_JobResultType MemIfSubResult;
    uint8               RepairNeed;
} NvM_Nvb_MemIfRsltToRprNeedTblType;

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CONST_32
#include <NvM_MemMap.h>

extern CONST( AB_83_ConstV NvM_Lib_ValueConvertPairType,            NVM_CONST ) NvM_Nvb_ConvertOperationIdPair[NVM_NVB_OPERATION_NUM];
extern CONST( AB_83_ConstV NvM_Lib_ValueConvertTableType,           NVM_CONST ) NvM_Nvb_ConvertOperationIdTable;
extern CONST( AB_83_ConstV NvM_Lib_ValueConvertPairType,            NVM_CONST ) NvM_Nvb_SubStatusBitToSeqNumPair[NVM_NVB_SUB_COMMON_NUM];
extern CONST( AB_83_ConstV NvM_Lib_ValueConvertTableType,           NVM_CONST ) NvM_Nvb_SubStatusBitToSeqNumTbl;
extern CONST( AB_83_ConstV NvM_Nvb_ActFuncType,                     NVM_CONST ) NvM_Nvb_RdOpeExecFuncPtrTbl[];
extern CONST( AB_83_ConstV uint16,                                  NVM_CONST ) NvM_Nvb_RdOpeExecFuncPtrTblSize;
extern CONST( AB_83_ConstV NvM_Nvb_ActFuncType,                     NVM_CONST ) NvM_Nvb_WtOpeExecFuncPtrTbl[];
extern CONST( AB_83_ConstV uint16,                                  NVM_CONST ) NvM_Nvb_WtOpeExecFuncPtrTblSize;
extern CONST( AB_83_ConstV NvM_Nvb_OperationActTblType,             NVM_CONST ) NvM_Nvb_OperationActTbl[NVM_NVB_OPERATION_NUM];

#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
extern CONST( AB_83_ConstV NvM_Nvb_MemIfRsltToRprNeedTblType,       NVM_CONST ) NvM_Nvb_MemIfRsltToRprNeedTbl[NVM_NVB_MEMIF_RESULT_PAIR_NUM];
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */

#define NVM_STOP_SEC_CONST_32
#include <NvM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

extern VAR( NvM_Nvb_MainStatusType,                             NVM_VAR_NO_INIT )               NvM_Nvb_MainStatus;
extern VAR( NvM_Nvb_SubStatusType,                              NVM_VAR_NO_INIT )               NvM_Nvb_SubStatus;
extern VAR( NvM_RequestResultType,                              NVM_VAR_NO_INIT )               NvM_Nvb_OperationResult;
extern VAR( NvM_Nvb_OperationInformationType,                   NVM_VAR_NO_INIT )               NvM_Nvb_ExecuteOperationInfo;

#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
extern VAR( MemIf_JobResultType,                                NVM_VAR_NO_INIT )               NvM_Nvb_MainResult;
extern VAR( uint8,                                              NVM_VAR_NO_INIT )               NvM_Nvb_MainDataBuffer[NVM_MAX_REDUNDANT_BLOCK_LENGTH];
extern VAR( uint8,                                              NVM_VAR_NO_INIT )               NvM_Nvb_SubDataBuffer[NVM_MAX_REDUNDANT_BLOCK_LENGTH];
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */

#define NVM_STOP_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_Nvb_StoreReqInfo(
    P2CONST( NvM_Nvb_OperationInformationType, AUTOMATIC, TYPEDEF ) OperationInfo
);

FUNC( void, NVM_CODE )
NvM_Nvb_StateChangeAct(
    uint8 CallMode,
    uint32 SerialOperationId
);

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_StateChangeActForWait(
    uint32 SerialOperationId,
    NvM_Nvb_MainStatusType MainStatusCurrent
);

FUNC( NvM_Nvb_MainStatusType, NVM_CODE ) NvM_Nvb_ActCancel( void );

FUNC( Std_ReturnType, NVM_CODE )
NvM_Nvb_ChkExecBlockId( void );

FUNC( MemIf_JobResultType, NVM_CODE )
NvM_Nvb_GetMhaProcessingResult(
    NvM_BlockIdType BlockId
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Nvb_RequestReadBlock(
    NvM_BlockIdType BlockId,
    uint8 DataIndex,
    uint16 BlockOffset,
    P2VAR( uint8, AUTOMATIC, TYPEDEF ) DataBufferPtr,
    uint16 Length
);

FUNC( Std_ReturnType, NVM_CODE )
NvM_Nvb_RequestWriteBlock(
    NvM_BlockIdType BlockId,
    uint8 DataIndex,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) DataBufferPtr
);

FUNC( uint16, NVM_CODE )
NvM_Nvb_MakeBlockNumber(
    NvM_BlockIdType BlockId,
    uint8 DataIndex
);

/* Read operation's action function.   */

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActStartRd( void );

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActRdNtvRsp( void );

#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActRdRdtRprRdMainRsp( void );

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActRdRdtRprRdSubRsp( void );

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActRdRdtRprWtMainRsp( void );

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActRdRdtRprWtSubRsp( void );

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_SubActRdRprReadSubStart( void );

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_SubActRdExecRepairStart(
    uint8 RprNeed
);
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */


/* Write operation's action function.  */

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActStartWt( void );

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActWtNtvRsp( void );

#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActWtRdtRprRdMainRsp( void );

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActWtRdtRprRdSubRsp( void );

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActWtRdtRprWtMainRsp( void );

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActWtRdtRprWtSubRsp( void );

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActWtRdtWtMainRsp( void );

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_ActWtRdtWtSubRsp( void );

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_SubActWtRprReadSubStart( void );

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_SubActWtExecRepairStart(
    uint8 RprNeed
);

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_SubActWtRprWriteEnd( void );

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_SubActWtWriteProcessStart(
    uint8 RprNeed
);

#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */


/* Common action function.             */

FUNC( NvM_Nvb_MainStatusType, NVM_CODE )
NvM_Nvb_SubActOperationEnd(
    NvM_RequestResultType OperationResult
);


/* Internal miscellaneous function.    */

FUNC( void, NVM_CODE )
NvM_Nvb_ChkProductErrMemIfRead(
    NvM_BlockIdType BlockId
);

FUNC( void, NVM_CODE )
NvM_Nvb_ChkProductErrMemIfWrite(
    NvM_BlockIdType BlockId
);

FUNC( void, NVM_CODE )
NvM_Nvb_EvtFinishedMemIfReadJob(
    NvM_BlockIdType BlockId,
    MemIf_JobResultType MemIfJobResult
);

FUNC( void, NVM_CODE )
NvM_Nvb_EvtFinishedMemIfWriteJob(
    NvM_BlockIdType BlockId,
    MemIf_JobResultType MemIfJobResult
);

#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
FUNC( uint8, NVM_CODE )
NvM_Nvb_JudgeRepairNeed(
    MemIf_JobResultType                  MainResult,
    MemIf_JobResultType                  SubResult,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) DataBufferMainPtr,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) DataBufferSubPtr,
    uint16                               DataLength
);
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */


#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_NVB_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/01/09                                              */
/*  1-2-0          :2019/08/29                                              */
/*  2-1-0          :2022/07/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
