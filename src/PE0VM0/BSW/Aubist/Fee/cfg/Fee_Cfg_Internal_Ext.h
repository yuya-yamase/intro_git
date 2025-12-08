/* Fee_Cfg_Internal_Ext.h v2-0-0                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/CFG/INTERNAL/EXT/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_CFG_INTERNAL_EXT_H
#define FEE_CFG_INTERNAL_EXT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../inc/Fee_ExConst.h"
#include "../inc/Fee_Mpu_Dev_Const.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    uint16  u2UseDataIdNum;
    uint8  u1BlockNum;
    uint16  u2MaxReadNum;
    uint8  u1AreaStartBlockNum;
    uint8  u1AreaLastBlockNum;
    uint16 u2RcrdDataAreaStartAddr;
    uint8 u1RcrdRetryNum;
    uint16 u2IntentRbldBlockId;
} Fee_AreaInfType;

typedef struct {
    uint8                          u1ProcessStatus;
    uint8                          u1MainStatus;
    uint8                          u1SubStatus;
    uint8                          u1SubSubStatus;
    uint8                          u1Result;
    uint8                          u1AreaNum;
    uint32                          u4BlockCount;
    uint32                          u4FailCount;
    uint32                          u4SrchRemainCount;
    uint32                          u4MoveSrcAddress;
    uint32                          u4ReadSrchAddress;
    uint32                          u4WriteLastRecMngAbsAddr;
    uint32                          u4WriteLastRecDatAbsAddr;
    uint32                          u4MainTimerCnt;
    uint32                          u4DFCTimerCnt;
    uint8                          u1MainBlockNo;
    uint8                          u1SubBlockNo;
    uint8                          u1MainBlockStatus;
    uint8                          u1SubBlockStatus;
    uint16                          u2DATA_ID;
    uint16                          u2MovDataId;
    uint8                          u1LastWritePosFlag;
    P2CONST(AB_83_ConstV Fee_AreaInfType, AUTOMATIC, TYPEDEF) ptstAreaInf;
    P2CONST( uint8, AUTOMATIC, TYPEDEF       ) ptu1ReqWriteAddr;
    P2VAR  ( uint8, AUTOMATIC, FEE_APPL_DATA ) ptu1ReqReadAddr;
    uint16                          u2ReqDataLen;
    uint16                          u2MovDataLen;
} Fee_CpuDtfType;

typedef struct {
    uint8  u1BlockNo;
    uint8  u1BlockStatus;
} Fee_LwpBlockInfType;

typedef struct {
    Fee_LwpBlockInfType stMainBlockInfo;
    Fee_LwpBlockInfType stSubBlockInfo;
    uint8              u1SetKind;
    uint32              u4WriteLastRecMngAbsAddr;
    uint32              u4WriteLastRecDatAbsAddr;
} Fee_LwpInfType;

typedef struct {
    uint8  u1BlockNo;
    uint8  u1BlockStatus;
} Fee_UseBlockType;

/*--------------------------------------------------------------------------*/
/* externs                                                                  */
/*--------------------------------------------------------------------------*/
#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)

#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>
extern  VAR(uint16, FEE_VAR_NO_INIT) Fee_RecordPosTBL[];
#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>
extern CONST(AB_83_ConstV uint16, FEE_CONFIG_DATA) Fee_RecordPosTBLSize;
#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>
extern  VAR(uint16, FEE_VAR_NO_INIT) Fee_RecordPosTBLMrr[];
#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>
extern CONST(AB_83_ConstV uint16, FEE_CONFIG_DATA) Fee_RecordPosTBLMrrSize;
#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>
extern VAR(uint8, FEE_VAR_NO_INIT) Fee_RecordPosTBLValidFlag[]; 
#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>
extern CONST(AB_83_ConstV uint8, FEE_CONFIG_DATA) Fee_RecordPosTBLValidFlagSize;
#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>


#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>
extern VAR(uint8, FEE_VAR_NO_INIT) Fee_RecordPosTBLValidFlagMrr[];
#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>
extern CONST(AB_83_ConstV uint8, FEE_CONFIG_DATA) Fee_RecordPosTBLValidFlagMrrSize;
#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>

#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */


#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

extern VAR( Fee_CpuDtfType, FEE_VAR_NO_INIT ) Fee_CpuDtfInfo;

#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
extern VAR( Fee_CpuDtfType, FEE_VAR_NO_INIT ) Fee_CpuDtfInfoSub;
#endif /* FEE_USE_REDUNDANCY_RAM == STD_ON */

#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>


#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>
extern VAR(Fee_LwpInfType, FEE_VAR_NO_INIT) Fee_LastWPosInfo1[];
#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>
extern CONST(AB_83_ConstV uint32, FEE_CONFIG_DATA) Fee_LastWPosInfo1Size;
#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>


#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>
extern VAR(Fee_LwpInfType, FEE_VAR_NO_INIT) Fee_LastWPosInfo2[];
#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>
extern CONST(AB_83_ConstV uint32, FEE_CONFIG_DATA) Fee_LastWPosInfo2Size;
#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>
extern VAR(Fee_UseBlockType, FEE_VAR_NO_INIT) Fee_UseBlockInfo[];
#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>
extern CONST(AB_83_ConstV uint32, FEE_CONFIG_DATA) Fee_UseBlockInfoSize;
#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>

#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>
extern VAR(Fee_UseBlockType, FEE_VAR_NO_INIT) Fee_UseBlockInfoSub[];
#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>
extern CONST(AB_83_ConstV uint32, FEE_CONFIG_DATA) Fee_UseBlockInfoSubSize;
#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>
#endif /* FEE_USE_REDUNDANCY_RAM == STD_ON */


#define FEE_START_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>

extern CONST( AB_83_ConstV uint8,  FEE_CONFIG_DATA ) Fee_DatasetSelectionBits;
extern CONST( AB_83_ConstV uint16, FEE_CONFIG_DATA ) Fee_MaxCalcCheckSumBytes;
extern CONST( AB_83_ConstV uint8,  FEE_CONFIG_DATA ) Fee_IntentRebuildEnable;

#if (FEE_RECORDPOSTBL_ENABLE == STD_ON) 

extern CONST( AB_83_ConstV uint16, FEE_CONFIG_DATA ) Fee_DatasetIndexMask;

#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */ 

extern CONST(AB_83_ConstV uint32, FEE_CONFIG_DATA) Fee_MaxBlankCheckNumber;
extern CONST(AB_83_ConstV uint16, FEE_CONFIG_DATA) Fee_ChkFreesPace_Record_Num;
extern CONST(AB_83_ConstV uint8, FEE_CONFIG_DATA) Fee_AreaNumber;
extern CONST(AB_83_ConstV uint32, FEE_CONFIG_DATA) Fee_LmtWriteTime;
extern CONST(AB_83_ConstV uint32, FEE_CONFIG_DATA) Fee_LmtIdReadTime;
extern CONST(AB_83_ConstV uint32, FEE_CONFIG_DATA) Fee_HwlmtInitTime;
extern CONST(AB_83_ConstV uint32, FEE_CONFIG_DATA) Fee_LmtRebuildTime;
extern CONST(AB_83_ConstV Fee_AreaInfType, FEE_CONFIG_DATA) Fee_AreaInfTBL[];
extern CONST(AB_83_ConstV uint8, FEE_CONFIG_DATA)  Fee_AreaInfTBLSize;

#if (FEE_RECORDPOSTBL_ENABLE == STD_ON)

extern CONST(AB_83_ConstV uint16, FEE_CONFIG_DATA) Fee_OffsetPos[];
extern CONST(AB_83_ConstV uint8,  FEE_CONFIG_DATA) Fee_OffsetPosSize;

#endif /* FEE_RECORDPOSTBL_ENABLE == STD_ON */

#define FEE_STOP_SEC_CONST_CONFIG_32
#include <Fee_MemMap.h>

#endif /* FEE_CFG_INTERNAL_EXT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/07/24                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
