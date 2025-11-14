/* Fee_Record_Internal.h v2-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/RECORD/INTERNAL/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_RECORD_INTERNAL_H
#define FEE_RECORD_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Fee_Common.h"
#include "Fee_ExConst.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_SRCH_REMAIN_CNT_OFFSET  (1U)    /* Offset for calculating the search end address from the number of times the search can be processed */

#define FEE_OVER_MAXRETRYNUM_OFFSET (1U)    /* Offset when judging maximum number of retries exceeded */

#define FEE_RECORD_ROUNDUP_CALC_ADDNUM_VAL    (1U)
#define FEE_RECORD_ROUNDUP_CALC_MASKNUM_VAL   (0xFFFFU)

#define FEE_RECORD_VAL_ZERO_FOR_CHECK_MULTIPLE  (0U)

#define FEE_RECORD_MASKNUM_00_TO_07_BIT         (0x000000FFU)
#define FEE_RECORD_MASKNUM_08_TO_15_BIT         (0x0000FF00U)
#define FEE_RECORD_SHIFTNUM_8_BIT               (8U)

/* State values for writing record state change. */
#define FEE_RECORD_STATE_INVALID            (0x0000U)
#define FEE_RECORD_STATE_WWAITDS            (0x0001U)
#define FEE_RECORD_STATE_WWAITIDADDR        (0x0002U)
#define FEE_RECORD_STATE_WWAITXFLAG         (0x0004U)
#define FEE_RECORD_STATE_WWAITDATACS        (0x0008U)
#define FEE_RECORD_STATE_WWAITWC            (0x0010U)
#define FEE_RECORD_STATE_WWAITDSFAIL        (0x0020U)
#define FEE_RECORD_STATE_WWAITHALFWC        (0x0040U)
#define FEE_RECORD_STATE_SWAITRECPOSTBL     (0x0100U)
#define FEE_RECORD_STATE_SWAITCALCSTBL      (0x0200U)
#define FEE_RECORD_STATE_SWAITSRCHDAT       (0x0400U)
#define FEE_RECORD_STATE_SWAITCALCSSRCH     (0x0800U)

#define FEE_RECORD_CHECKSUM_INIT_VAL_ZERO       (0U)
#define FEE_RECORD_COMPLETELEN_INIT_VAL_ZERO    (0U)
#define FEE_RECORD_WRITEDATALEN_VAL_ZERO        (0U)

/* Flag patterns for requesting MngDfc to write. */
#define FEE_RECORD_MNGDFC_WFLAG_BASIC   (( FEE_CWFLG_ERRSTOP | FEE_CWFLG_DFCERRCHK ) | FEE_CWFLG_VRFYERRCHK )
#define FEE_RECORD_MNGDFC_WFLAG_DS      ( FEE_CWFLG_NONE )
#if ( FEE_HALFWORD_WRITE_USE == STD_ON ) 
#define FEE_RECORD_MNGDFC_WFLAG_WC_1ST  (( FEE_CWFLG_ERRSTOP | FEE_CWFLG_DFCERRCHK ))
#endif /* FEE_HALFWORD_WRITE_USE */ 
#define FEE_RECORD_MNGDFC_WFLAG_WC      ( FEE_CWFLG_VOLMINCHK | FEE_CWFLG_ERRSTOP | FEE_CWFLG_DFCERRCHK | FEE_CWFLG_VRFYERRCHK )

/* The range of value for Fee_Record_DataMatchResult. */
/*      MATCH    : 0x00U                              */
/*      MISMATCH : Other than 0x00U                   */
#define FEE_RECORD_DATA_CMP_MATCH           ( 0x00U )
#define FEE_RECORD_DATA_CMP_INI_MISMATCH    ( 0xFFU )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef union{
    uint32 au4StrageForAlignment[FEE_DFLASH_ONE_TIME_WRITE_SIZE/FEE_BYTE_NUM_04];
    uint8  au1RecordData[FEE_DFLASH_ONE_TIME_WRITE_SIZE];
} Fee_Record_DFlashAccessDataType;

typedef struct{
    uint32 DataAddr;
    uint32 XFlagAddr;
    uint32 DataRecordLen;
} Fee_Record_RecordInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC( void, FEE_CODE )
Fee_Record_SrchSpcMngArea(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) ptstCPUDTFInfo,
    P2VAR  ( uint32,         AUTOMATIC, TYPEDEF         ) ptu4WriteLastRecMngAbsAddr
);

FUNC( void, FEE_CODE )
Fee_Record_SrchSpcDatArea(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) ptstCPUDTFInfo,
    P2VAR  ( uint32,         AUTOMATIC, TYPEDEF )         ptu4WriteLastRecDatAbsAddr
);

/* Record write status management (idle) */
FUNC(uint32, FEE_CODE) Fee_WriteRecord_DoIdle( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );
/* Record write status management (searching for write location) */
FUNC(uint32, FEE_CODE) Fee_WriteRecord_DoSrchWritePosMng( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );
/* Record write status management (start search for write record position (data)) */
FUNC(uint32, FEE_CODE) Fee_WriteRecord_DoStartSrchPosDat( P2VAR(Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT) ptstCPUDTFInfo );
/* Record write status management (searching write record position (data)) */
FUNC(uint32, FEE_CODE) Fee_WriteRecord_DoSrchWritePosDat( P2VAR(Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT) ptstCPUDTFInfo );
/* Record write status management (preparing to retrieve old data) */
FUNC(uint32, FEE_CODE) Fee_WriteRecord_DoPrepSrchOldRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT) ptstCPUDTFInfo );
/* Record write status management (old data retrieval) */
FUNC(uint32, FEE_CODE) Fee_WriteRecord_DoSrchOldRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );
/* Record write status management (writing data) */
FUNC(uint32, FEE_CODE) Fee_WriteRecord_DoWriteNewRecord( P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo );

FUNC( uint32, FEE_CODE )
Fee_QuitWriteProcessSuccess(
    P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo
);

FUNC( uint32, FEE_CODE )
Fee_QuitWriteProcessFailure(
    P2VAR(Fee_CpuDtfType, AUTOMATIC, TYPEDEF) ptstCPUDTFInfo
);

FUNC( uint16, FEE_CODE )
Fee_Record_GetRoundUpLen(
    uint16  InputDataLen, 
    uint8   RoundUpNum
);
FUNC( uint16, FEE_CODE )
Fee_Record_GetDataAreaRcrdLen(
    uint16  InputDataLen
);

FUNC( void, FEE_CODE )
Fee_Record_StateWtWtStart(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    uint32 SrcReadOldRecordResult
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateWtWtExec(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( void, FEE_CODE )
Fee_Record_StateScOdStart( void );

FUNC( uint32, FEE_CODE )
Fee_Record_StateScOdExec(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult, 
    P2VAR( boolean,        AUTOMATIC, TYPEDEF )         DstChkDiffData
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateWtWtEsubWaitDS(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateWtWtEsubWaitDataCs(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateWtWtEsubWaitHalfWC(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateWtWtEsubWaitWC(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( void, FEE_CODE )
Fee_Record_StateWtCmActWtDS(
    uint32 TgtRcrdMngInfoAddr
);

FUNC( void, FEE_CODE )
Fee_Record_StateWtWtActWtIdAddr(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( void, FEE_CODE )
Fee_Record_StateWtMvActWtIdAddr(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( void, FEE_CODE )
Fee_Record_StateWtCmActWtXFlag( void );

FUNC( void, FEE_CODE )
Fee_Record_StateWtWtActWtDatCs(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( void, FEE_CODE )
Fee_Record_StateWtMvActWtDatCs(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( void, FEE_CODE )
Fee_Record_StateWtCmActWtWc(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    uint16 WriteOptFlag
);

#if ( FEE_HALFWORD_WRITE_USE == STD_ON ) 
FUNC( void, FEE_CODE )
Fee_Record_StateWtCmActWtWc1st(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( void, FEE_CODE )
Fee_Record_StateWtCmActWtWc2nd(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);
#endif /* FEE_HALFWORD_WRITE_USE */ 

FUNC( void, FEE_CODE )
Fee_Record_StateWtCmActShiftRec(
    uint16 WriteDataLen,
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo
);

FUNC( void, FEE_CODE )
Fee_Record_StateWtCmActQuit( void );

FUNC( void, FEE_CODE )
Fee_Record_StateWtCmAsubWtIdAddr(
    uint16  BlockNumber,
    uint16  DataAddress,
    uint32  TargetAddress
);

FUNC( void, FEE_CODE )
Fee_Record_StateWtCmAsubWtDatCs(
    uint16 TargetLen,
    P2CONST( uint8, AUTOMATIC, TYPEDEF ) DataAddr
);

FUNC( uint16, FEE_CODE )
Fee_Record_StateWtCmAsubCalWtDatLen(
    uint16 TargetLen,
    uint16 CompleteWriteLen
);

FUNC( void, FEE_CODE )
Fee_Record_StateWtCmAsubWtCom(
    uint32                                  TargetAbsAddr,
    P2CONST( uint8, AUTOMATIC, TYPEDEF )    WriteDataAddr,
    uint16                                  WriteLength,
    uint16                                  WriteOffset,
    uint16                                  WriteOptFlag
);

FUNC( void, FEE_CODE )
Fee_Record_StateWtCmAsubMkRecInfo(
    uint16 DataLen,
    uint32 LastRecordDataAddr
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScOdActRecPosTbl(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF         ) DstSrchResult
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScOdActCalCSTbl(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF         ) DstSrchResult
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScOdActSrchDat(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF         ) DstSrchResult
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScOdActCalCSSrch(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF         ) DstSrchResult
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScRdActRecPosTbl(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF         ) DstSrchResult
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScRdActCalCSTbl(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF         ) DstSrchResult
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScRdActSrchDat(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScRdActCalCSSrch(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScMsActSrchDat (
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScMsActCalCS(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScMdActRecPosTbl(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR( uint32,         AUTOMATIC, TYPEDEF         ) DstSrchResult
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScMdActSrchDat (
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo, 
    P2VAR( uint32,         AUTOMATIC, TYPEDEF )         DstSrchResult
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScOdAsubCalCSChkDat(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR  ( boolean,        AUTOMATIC, TYPEDEF         ) DstCheckResult
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScRdAsubCalCSCpyDat(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR  ( boolean,        AUTOMATIC, TYPEDEF         ) DstCheckResult
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScMsAsubCalCS(
    P2CONST( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) CPUDTFInfo,
    P2VAR  ( boolean,        AUTOMATIC, TYPEDEF         ) DstCheckResult
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScCmAsubSrchId(
    uint16 TargetId,
    uint16 DataLength,
    uint8  TargetSector,
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) ptstCPUDTFInfo
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScCmAsubSrchValid(
    P2VAR( Fee_CpuDtfType, AUTOMATIC, FEE_VAR_NO_INIT ) ptstCPUDTFInfo
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScCmAsubChkAddr(
    uint32 TgtRcrdMngInfoAddr,
    uint16 DataLength
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScCmAsubRdChkDS(
    uint32 TgtRcrdMngInfoAddr
);

FUNC( uint16, FEE_CODE )
Fee_Record_StateScCmAsubCalOneTimeCSSize (
    uint16 CompleteLen,
    uint16 DataLen
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScCmAsubCalCSIdAddr(
    uint32 MngRecAddr
);

FUNC( boolean, FEE_CODE )
Fee_Record_StateScCmAsubCmpCS (
    uint32 ExpectValue,
    uint32 RecordDataAreaAbsAddr,
    uint16 DataLen
);

FUNC( boolean, FEE_CODE )
Fee_Record_StateScCmAsubChkId(
    uint16 BlockNumber,
    uint8  AreaNo
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScCmAsubGetRecPos(
    uint8  AreaNo,
    uint8  TargetSector,
    uint16 BlockNumber,
    uint16 DataLength,
    P2VAR( uint32, AUTOMATIC, TYPEDEF ) DstRecordPos
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScCmAsubChkFlash(
    uint32 RecMngAbsAddr,
    uint16 BlockNumber,
    uint16 DataLength
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateScCmAsubCalcCS(
    P2CONST(uint8, AUTOMATIC, TYPEDEF) TargetAddressPtr,
    uint16                             Length
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateCmCmAsubCalcMngAddrCS(
    uint32 MngRecAddr
);

FUNC( uint32, FEE_CODE )
Fee_Record_StateCmCmAsubGetDatRecFromMngRec(
    uint32 MngRecAddr,
    uint8  SectorNo
);

FUNC( void, FEE_CODE )
Fee_Record_StateCmCmAsubSetRecPos(
    uint8  AreaNo,
    uint8  SectorNo,
    uint16 BlockNumber,
    uint32 MngAbsAddr
);

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

extern VAR( uint8,  FEE_VAR_NO_INIT ) Fee_Record_DataMatchResult;
extern VAR( uint16, FEE_VAR_NO_INIT ) Fee_Record_State;
extern VAR( uint16, FEE_VAR_NO_INIT ) Fee_Record_CompleteLen;
extern VAR( uint32, FEE_VAR_NO_INIT ) Fee_Record_CheckSumVal;
extern VAR( uint32, FEE_VAR_NO_INIT ) Fee_Record_ReadOldRcrdResult;
extern VAR( Fee_Record_DFlashAccessDataType, FEE_VAR_NO_INIT ) Fee_Record_Buffer;
extern VAR( Fee_Record_RecordInfoType,       FEE_VAR_NO_INIT ) Fee_Record_RecordInfo;

#if ( FEE_USE_REDUNDANCY_RAM == STD_ON )
/* Redundancy Data */
extern VAR( uint8,  FEE_VAR_NO_INIT ) Fee_Record_DataMatchResultSub;
extern VAR( uint16, FEE_VAR_NO_INIT ) Fee_Record_StateSub;
extern VAR( uint16, FEE_VAR_NO_INIT ) Fee_Record_CompleteLenSub;
extern VAR( uint32, FEE_VAR_NO_INIT ) Fee_Record_CheckSumValSub;
extern VAR( uint32, FEE_VAR_NO_INIT ) Fee_Record_ReadOldRcrdResultSub;
extern VAR( Fee_Record_DFlashAccessDataType, FEE_VAR_NO_INIT ) Fee_Record_BufferSub;
extern VAR( Fee_Record_RecordInfoType,       FEE_VAR_NO_INIT ) Fee_Record_RecordInfoSub;
#endif /* FEE_USE_REDUNDANCY_RAM == STD_ON */

#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* FEE_RECORD_INTERNAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/11/18                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
