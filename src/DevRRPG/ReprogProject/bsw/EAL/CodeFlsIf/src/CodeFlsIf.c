/* CodeFlsIf_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CodeFlsIf/CODE                                              */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <CodeFlsIf.h>
#include "CodeFlsIf_Ucfg.h"
#include "CodeFlsIf_Local.h"
#include "CodeFlsIf_Cfg.h"

#include <CodeFls.h>
#include <Sys.h>
#include <SchM.h>
#include <EcuM.h>
#include <Rte.h>
#include <ReprogOpt.h>
#if ( ( REPROG_CFG_SMALL_RAM_USE == STD_ON ) && ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) ) )
#include <Gdn.h>
#include <Gdn_Dcm_Dcp.h>
#endif


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define CODEFLSIF_REQ_MODE_NONE         (0x00U)
#define CODEFLSIF_REQ_MODE_ERASE        ((uint8)0x11U)
#define CODEFLSIF_REQ_MODE_WRITE        ((uint8)0x22U)
#define CODEFLSIF_REQ_MODE_READ         ((uint8)0x33U)
#define CODEFLSIF_REQ_MODE_WRITECHECK   ((uint8)0x44U)
#define CODEFLSIF_REQ_MODE_SWITCHREQ    ((uint8)0x55U)

#define CODEFLSIF_LOCAL_UNINIT          ((uint8)0x00U)
#define CODEFLSIF_LOCAL_IDLE            ((uint8)0x01U)
#define CODEFLSIF_LOCAL_READY           ((uint8)0x02U)
#define CODEFLSIF_LOCAL_BUSY            ((uint8)0x03U)
#define CODEFLSIF_LOCAL_UPDATEIDLE      ((uint8)0x04U)
#define CODEFLSIF_LOCAL_UPDATEREADY     ((uint8)0x05U)
#define CODEFLSIF_LOCAL_UPDATEWRITING   ((uint8)0x06U)
#define CODEFLSIF_LOCAL_UPDATECOMPLETE  ((uint8)0x07U)

#define CODEFLSIF_REQ_SKIPINFO_NUM      ((uint8)2U)
#define CODEFLSIF_SAVE_SKIPINFO_NUM     (32U)

#define CODEFLSIF_SKIPDATA_SIZE         (4UL)

#define CODEFLSIF_SKIPDATAINDEX_MASK    ((uint8)(CODEFLSIF_SKIPDATA_SIZE - 1UL))

#define CODEFLSIF_SKIPINFO_NONE         ((uint8)0U)

#define CODEFLSIF_RESET_WRITEBUFF_INDEX (0x00000000UL)

#define CODEFLSIF_PADDING_DATA          (0xFFU)

#define CODEFLSIF_ADJUST_ENDADDR        (1UL)

#define CODEFLSIF_ADJUST_ALIGNCHECK     (1UL)

#define CODEFLSIF_WRITEBUFF_NOT_FULL    (0x00U)
#define CODEFLSIF_WRITEBUFF_FULL        ((uint8)0x01U)

#define CODEFLSIF_TARGETAREA_NOT_SKIP   ((uint8)0x00U)
#define CODEFLSIF_TARGETAREA_SKIP       (0x01U)

#define CODEFLSIF_ERROR_NOT_REPORT      (0x00U)
#define CODEFLSIF_ERROR_REPORT          ((uint8)0x01U)

#define CODEFLSIF_E_API_ID_INIT         (0x00U)
#define CODEFLSIF_E_API_ID_MAINFUNC     (0x01U)
#define CODEFLSIF_E_API_ID_ERASEREQ     (0x02U)
#define CODEFLSIF_E_API_ID_ERASECHK     (0x03U)
#define CODEFLSIF_E_API_ID_WRITEREQ     (0x04U)
#define CODEFLSIF_E_API_ID_WRITECHK     (0x05U)
#define CODEFLSIF_E_API_ID_WRITABLEREQ  (0x06U)
#define CODEFLSIF_E_API_ID_WRITABLECHK  (0x07U)
#define CODEFLSIF_E_API_ID_SWITCHREQ    (0x08U)
#define CODEFLSIF_E_API_ID_SWITCHCHK    (0x09U)

#define CODEFLSIF_E_CASE_FLSSTATUS_FAIL (0x80U)
#define CODEFLSIF_E_CASE_STATUS_FAIL    (0x81U)
#define CODEFLSIF_E_CASE_FLSRESULT_FAIL (0x82U)
#define CODEFLSIF_E_CASE_REQMODE_FAIL   (0x83U)
#define CODEFLSIF_E_CASE_STARTCTRL_FAIL (0x84U)
#define CODEFLSIF_E_CASE_VALUECHK_FAIL  (0x85U)
#define CODEFLSIF_E_CASE_BLOCKINFO_FAIL (0x86U)
#define CODEFLSIF_E_CASE_ERASEADDR_FAIL (0x87U)
#define CODEFLSIF_E_CASE_ERASESIZE_FAIL (0x88U)
#define CODEFLSIF_E_CASE_WRITEADDRFAIL  (0x89U)
#define CODEFLSIF_E_CASE_PREHOOK_FAIL   (0x8AU)
#define CODEFLSIF_E_CASE_POSTHOOK_FAIL  (0x8BU)

#define CODEFLSIF_INVALID_ADDR          (0xFFFFFFFFUL)
#define CODEFLSIF_INVALID_SIZE          (0UL)
#define CODEFLSIF_INVALID_SKIPINDEX     (0x00U)
#define CODEFLSIF_INVALID_SKIPDATA      (0x00U)

#define CODEFLSIF_VALID_ALIGN           (0x00000000UL)

#define CODEFLSIF_E_PENDING             ((Std_ReturnType)0x02U)

#define CODEFLSIF_GET_STATUS_TBL_NUM    ((uint8)8U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint32 TargetAddr;
    uint32 Size;
} CodeFlsIf_EraseDataType;

typedef struct {
    uint32 DestAddr;
    P2CONST(uint8, TYPEDEF, CODEFLSIF_APPL_CONST) SrcAddr;
    uint32 TotalSize;
    uint32 UpdateSize;
    uint32 WriteBuffIndex;
    uint8 WriteBuff[CODEFLSIF_CFG_WRITESIZE];
    uint32 SaveSetUserDataSize;
} CodeFlsIf_WriteDataType;

typedef struct {
    P2VAR(uint8, TYPEDEF, CODEFLSIF_APPL_DATA) DestAddr;
    uint32 SrcAddr;
    uint32 Size;
} CodeFlsIf_ReadDataType;

typedef struct {
    uint32 TargetAddr;
    P2CONST(uint8, TYPEDEF, CODEFLSIF_APPL_CONST) SrcAddr;
    uint32 DataSize;
} CodeFlsIf_WritableCheckDataType;

typedef struct {
    uint32 Addr;
    uint8 Data[CODEFLSIF_SKIPDATA_SIZE];
} CodeFlsIf_InternalSkipInfoType;

typedef struct {
    CodeFlsIf_InternalSkipInfoType SkipInfo[CODEFLSIF_REQ_SKIPINFO_NUM];
    uint8 SkipNum;
} CodeFlsIf_RequestSkipInfoType;

typedef struct {
    CodeFlsIf_InternalSkipInfoType SkipInfo[CODEFLSIF_SAVE_SKIPINFO_NUM];
    uint8 SkipNum;
} CodeFlsIf_SaveSkipInfoType;

typedef struct {
    uint8 LocalStatus;
    CodeFlsIf_JobResultType JobResult;
    uint8 ReqMode;
} CodeFlsIf_JobInfoType;

typedef struct {
    uint8 LocalStatus;
    CodeFlsIf_StatusType JobStatus;
} CodeFlsIf_GetStatusInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_EraseReq (void);
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_EraseCompleteChk (void);
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_WriteReq (void);
static FUNC(uint8, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_WriteSetWriteBuff
(
    P2VAR(uint32, AUTOMATIC, CODEFLSIF_APPL_DATA) SetUserDataSize
);
static FUNC(uint8, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_WriteIsSkipArea
(
    VAR(uint32, AUTOMATIC) DestAddr,
    P2VAR(uint8, AUTOMATIC, CODEFLSIF_APPL_DATA) SkipIndex
);
static FUNC(Std_ReturnType, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_WriteReqWriteFls (void);
static FUNC(Std_ReturnType, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_WriteSaveSkipInfo
(
    VAR(uint8, AUTOMATIC) SkipIndex
);
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_WriteCompleteChk (void);
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_Read (void);
static FUNC(uint8, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_ReadIsSkipArea
(
    VAR(uint32, AUTOMATIC) SrcAddr,
    VAR(uint32, AUTOMATIC) ReadSize,
    P2VAR(uint8, AUTOMATIC, CODEFLSIF_APPL_DATA) SkipIndex
);
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_ReadCopySkipData
(
    VAR(uint32, AUTOMATIC) CopySize,
    VAR(uint8, AUTOMATIC) SkipIndex
);
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_SwitchReq (void);
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_SwitchCmpltChk (void);
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_WriteChkReq (void);
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_WriteChkCmpltChk (void);
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_Fail
(
    VAR(uint8, AUTOMATIC) ReportReq,
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define CODEFLSIF_START_SEC_VAR
#include <CodeFlsIf_MemMap.h>

static VAR(CodeFlsIf_JobInfoType, CODEFLSIF_VAR_CLEARED) CodeFlsIf_JobInfo;
static VAR(CodeFlsIf_EraseDataType, CODEFLSIF_VAR_CLEARED) CodeFlsIf_EraseData;
static VAR(CodeFlsIf_WriteDataType, CODEFLSIF_VAR_CLEARED) CodeFlsIf_WriteData;
static VAR(CodeFlsIf_ReadDataType, CODEFLSIF_VAR_CLEARED) CodeFlsIf_ReadData;
static VAR(CodeFlsIf_WritableCheckDataType, CODEFLSIF_VAR_CLEARED) CodeFlsIf_WritableCheckData;
static VAR(CodeFlsIf_RequestSkipInfoType, CODEFLSIF_VAR_CLEARED) CodeFlsIf_RequestSkipInfo;
static VAR(CodeFlsIf_SaveSkipInfoType, CODEFLSIF_VAR_CLEARED) CodeFlsIf_SaveSkipInfo;
static VAR(CodeFlsIf_EraseDataType, CODEFLSIF_VAR_CLEARED) CodeFlsIf_EraseDataMirror;
static VAR(uint32, CODEFLSIF_VAR_CLEARED) CodeFlsIf_WriteDestAddrMirror;
static VAR(uint8, CODEFLSIF_VAR_CLEARED) CodeFlsIf_PostHookPendingFlg;

#define CODEFLSIF_STOP_SEC_VAR
#include <CodeFlsIf_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define CODEFLSIF_START_SEC_CST
#include <CodeFlsIf_MemMap.h>

static CONST(AB_83_ConstV CodeFlsIf_GetStatusInfoType, CODEFLSIF_CONST) CodeFlsIf_GetStatusTbl[CODEFLSIF_GET_STATUS_TBL_NUM] = {
     { CODEFLSIF_LOCAL_UNINIT,          CODEFLSIF_UNINIT            }
    ,{ CODEFLSIF_LOCAL_IDLE,            CODEFLSIF_IDLE              }
    ,{ CODEFLSIF_LOCAL_READY,           CODEFLSIF_BUSY              }
    ,{ CODEFLSIF_LOCAL_BUSY,            CODEFLSIF_BUSY              }
    ,{ CODEFLSIF_LOCAL_UPDATEIDLE,      CODEFLSIF_UPDATEIDLE        }
    ,{ CODEFLSIF_LOCAL_UPDATEREADY,     CODEFLSIF_UPDATEBUSY        }
    ,{ CODEFLSIF_LOCAL_UPDATEWRITING,   CODEFLSIF_UPDATEBUSY        }
    ,{ CODEFLSIF_LOCAL_UPDATECOMPLETE,  CODEFLSIF_UPDATECOMPLETE    }
};

#define CODEFLSIF_STOP_SEC_CST
#include <CodeFlsIf_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define CODEFLSIF_START_SEC_CODE
#include <CodeFlsIf_MemMap.h>

/******************************************************************************/
/* Function Name | CodeFlsIf_Erase                                            */
/* Description   | Request to erase                                           */
/* Preconditions |                                                            */
/* Parameters    | [IN] TargetAddr : Erase address                            */
/*               | [IN] TargetSize : Erase size                               */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CODEFLSIF_CODE_SLOW) CodeFlsIf_Erase
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(CodeFls_BlockInfoType, AUTOMATIC) BlockInfo;

    Result = E_NOT_OK;

    if( CODEFLSIF_LOCAL_IDLE == CodeFlsIf_JobInfo.LocalStatus )
    {
        if( 0UL != TargetSize )
        {
            BlockInfo.Addr = CODEFLSIF_INVALID_ADDR;
            BlockInfo.Size = CODEFLSIF_INVALID_SIZE;
            FuncRet = CodeFls_GetBlockInfo(TargetAddr, &BlockInfo);
            if( (Std_ReturnType)E_OK == FuncRet )
            {
                if( BlockInfo.Addr == TargetAddr )
                {
                    FuncRet = CodeFls_GetBlockInfo(TargetAddr + (TargetSize - CODEFLSIF_ADJUST_ENDADDR), &BlockInfo);   /* no wrap around */
                    if( (Std_ReturnType)E_OK == FuncRet )
                    {
                        if( (BlockInfo.Addr + (BlockInfo.Size - CODEFLSIF_ADJUST_ALIGNCHECK)) ==    /* no wrap around */
                                (TargetAddr + (TargetSize - CODEFLSIF_ADJUST_ALIGNCHECK)) )         /* no wrap around */
                        {
                            CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_READY;

                            CodeFlsIf_EraseData.TargetAddr = TargetAddr;
                            CodeFlsIf_EraseDataMirror.TargetAddr = CodeFlsIf_EraseData.TargetAddr;

                            CodeFlsIf_EraseData.Size = TargetSize;
                            CodeFlsIf_EraseDataMirror.Size = CodeFlsIf_EraseData.Size;

                            CodeFlsIf_JobInfo.ReqMode = CODEFLSIF_REQ_MODE_ERASE;

                            CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_PENDING;

                            Result = E_OK;
                        }
                    }
                }
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_WriteStart                                       */
/* Description   | Request to start writing                                   */
/* Preconditions |                                                            */
/* Parameters    | [IN] DestAddr  : Destination address                       */
/*               | [IN] TotalSize : Total write size                          */
/*               | [IN] SkipNum   : Number of skip informations               */
/*               | [IN] SkipInfo  : Skip information                          */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CODEFLSIF_CODE_SLOW) CodeFlsIf_WriteStart
(
    VAR(uint32, AUTOMATIC) DestAddr,
    VAR(uint32, AUTOMATIC) TotalSize,
    VAR(uint8, AUTOMATIC) SkipNum,
    P2CONST(CodeFlsIf_SkipInfoType, AUTOMATIC, CODEFLSIF_APPL_CONST) SkipInfo
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(uint8, AUTOMATIC) Cnt;

    Result = E_NOT_OK;

    if( CODEFLSIF_LOCAL_IDLE == CodeFlsIf_JobInfo.LocalStatus )
    {
        if( 0UL != TotalSize )
        {
            if( CODEFLSIF_VALID_ALIGN == (DestAddr & (CodeFlsIf_Cfg_Data.WriteSize - CODEFLSIF_ADJUST_ALIGNCHECK)) )    /* no wrap around */
            {
                if( CODEFLSIF_SKIPINFO_NONE == SkipNum )
                {
                    CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_UPDATEIDLE;

                    CodeFlsIf_WriteData.DestAddr = DestAddr;
                    CodeFlsIf_WriteDestAddrMirror = CodeFlsIf_WriteData.DestAddr;

                    CodeFlsIf_WriteData.TotalSize = TotalSize;

                    CodeFlsIf_RequestSkipInfo.SkipNum = SkipNum;

                    CodeFlsIf_JobInfo.ReqMode = CODEFLSIF_REQ_MODE_WRITE;

                    Result = E_OK;
                }
                else if( (CODEFLSIF_REQ_SKIPINFO_NUM >= SkipNum) && (NULL_PTR != SkipInfo) )
                {
                    for( Cnt = 0U; Cnt < SkipNum; Cnt++ )
                    {
                        if( CODEFLSIF_VALID_ALIGN !=
                                (SkipInfo[Cnt].SkipAddr & (CodeFlsIf_Cfg_Data.WriteSize - CODEFLSIF_ADJUST_ALIGNCHECK) ))   /* no wrap around */
                        {
                            break;
                        }
                    }

                    if( Cnt == SkipNum )
                    {
                        CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_UPDATEIDLE;

                        for( Cnt = 0U; Cnt < SkipNum; Cnt++ )
                        {
                            CodeFlsIf_RequestSkipInfo.SkipInfo[Cnt].Addr = SkipInfo[Cnt].SkipAddr;

                            Rpg_MemCopy(&CodeFlsIf_RequestSkipInfo.SkipInfo[Cnt].Data[0],
                                            (const uint8*)&SkipInfo[Cnt].ExpectedValue,
                                            CODEFLSIF_SKIPDATA_SIZE);
                        }

                        CodeFlsIf_WriteData.DestAddr = DestAddr;
                        CodeFlsIf_WriteDestAddrMirror = CodeFlsIf_WriteData.DestAddr;

                        CodeFlsIf_WriteData.TotalSize = TotalSize;

                        CodeFlsIf_RequestSkipInfo.SkipNum = SkipNum;

                        CodeFlsIf_JobInfo.ReqMode = CODEFLSIF_REQ_MODE_WRITE;

                        Result = E_OK;
                    }
                }
                else
                {
                    /* SkipNum is invalid value */
                }
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_WriteUpdate                                      */
/* Description   | Request to update writing                                  */
/* Preconditions |                                                            */
/* Parameters    | [IN] SrcAddr : Source address                              */
/*               | [IN] Size    : Write size                                  */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CODEFLSIF_CODE_SLOW) CodeFlsIf_WriteUpdate
(
    P2CONST(uint8, AUTOMATIC, CODEFLSIF_APPL_CONST) SrcAddr,
    VAR(uint32, AUTOMATIC) Size
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_NOT_OK;

    if( CODEFLSIF_LOCAL_UPDATEIDLE == CodeFlsIf_JobInfo.LocalStatus )
    {
        if( NULL_PTR != SrcAddr )
        {
            if( 0UL != Size )
            {
                if( CodeFlsIf_WriteData.TotalSize >= Size )
                {
                    CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_UPDATEREADY;

                    CodeFlsIf_WriteData.SrcAddr = SrcAddr;
                    CodeFlsIf_WriteData.UpdateSize = Size;
                    CodeFlsIf_WriteData.SaveSetUserDataSize = CODEFLSIF_INVALID_SIZE;

                    CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_PENDING;

                    Result = E_OK;
                }
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_WriteFinish                                      */
/* Description   | Request to finish writing                                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CODEFLSIF_CODE_SLOW) CodeFlsIf_WriteFinish (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_NOT_OK;

    if( CODEFLSIF_LOCAL_UPDATECOMPLETE == CodeFlsIf_JobInfo.LocalStatus )
    {
        CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_IDLE;
        CodeFlsIf_JobInfo.ReqMode = CODEFLSIF_REQ_MODE_NONE;

        Result = E_OK;
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Read                                             */
/* Description   | Request to read                                            */
/* Preconditions |                                                            */
/* Parameters    | [IN]  SrcAddr  : Source address                            */
/*               | [OUT] DestAddr : Destination address                       */
/*               | [IN]  Size     : Read size                                 */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CODEFLSIF_CODE_SLOW) CodeFlsIf_Read
(
    VAR(uint32, AUTOMATIC) SrcAddr,
    P2VAR(uint8, AUTOMATIC, CODEFLSIF_APPL_DATA) DestAddr,
    VAR(uint32, AUTOMATIC) Size
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_NOT_OK;

    if( CODEFLSIF_LOCAL_IDLE == CodeFlsIf_JobInfo.LocalStatus )
    {
        if( NULL_PTR != DestAddr )
        {
            if( 0UL != Size )
            {
                CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_READY;

                CodeFlsIf_ReadData.DestAddr = DestAddr;
                CodeFlsIf_ReadData.SrcAddr = SrcAddr;
                CodeFlsIf_ReadData.Size = Size;

                CodeFlsIf_JobInfo.ReqMode = CODEFLSIF_REQ_MODE_READ;
                CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_PENDING;

                Result = E_OK;
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_WritableCheck                                    */
/* Description   | Request to check writable                                  */
/* Preconditions |                                                            */
/* Parameters    | [IN] TargetAddr : Target address                           */
/*               | [IN] SrcAddr    : Source address                           */
/*               | [IN] DataSize   : Data size                                */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CODEFLSIF_CODE_SLOW) CodeFlsIf_WritableCheck
(
    VAR(uint32,AUTOMATIC) TargetAddr,
    P2CONST(uint8, AUTOMATIC, CODEFLSIF_APPL_CONST) SrcAddr,
    VAR(uint32,AUTOMATIC) DataSize
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_NOT_OK;

    if( CODEFLSIF_LOCAL_IDLE == CodeFlsIf_JobInfo.LocalStatus )
    {
        if( NULL_PTR != SrcAddr )
        {
            if( 0UL != DataSize )
            {
                CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_READY;

                CodeFlsIf_WritableCheckData.TargetAddr = TargetAddr;
                CodeFlsIf_WritableCheckData.SrcAddr = SrcAddr;
                CodeFlsIf_WritableCheckData.DataSize = DataSize;

                CodeFlsIf_JobInfo.ReqMode = CODEFLSIF_REQ_MODE_WRITECHECK;
                CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_PENDING;

                Result = E_OK;
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_SwitchValidArea                                  */
/* Description   | Request to switch valid area                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CODEFLSIF_CODE_SLOW) CodeFlsIf_SwitchValidArea (void)
{
    CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_READY;

    CodeFlsIf_JobInfo.ReqMode = CODEFLSIF_REQ_MODE_SWITCHREQ;
    CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_PENDING;

    return;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_GetStatus                                        */
/* Description   | Get job status                                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | JobStatus                                                  */
/*               |  CODEFLSIF_UNINIT                                          */
/*               |  CODEFLSIF_IDLE                                            */
/*               |  CODEFLSIF_BUSY                                            */
/*               |  CODEFLSIF_UPDATEIDLE                                      */
/*               |  CODEFLSIF_UPDATEBUSY                                      */
/*               |  CODEFLSIF_UPDATECOMPLETE                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(CodeFlsIf_StatusType, CODEFLSIF_CODE_SLOW) CodeFlsIf_GetStatus (void)
{
    VAR(CodeFlsIf_StatusType, AUTOMATIC) JobStatus;
    VAR(uint8, AUTOMATIC) i;

    /* If it does not match the table, CodeFlsIf returns an abnormal value, */
    /* and then MemM detects an error.                                      */
    JobStatus = (CodeFlsIf_StatusType)CodeFlsIf_JobInfo.LocalStatus;

    for( i = 0U; i < CODEFLSIF_GET_STATUS_TBL_NUM; i++ )
    {
        if( CodeFlsIf_JobInfo.LocalStatus == CodeFlsIf_GetStatusTbl[i].LocalStatus )
        {
            JobStatus = CodeFlsIf_GetStatusTbl[i].JobStatus;
            break;
        }
    }

    return JobStatus;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_GetJobResult                                     */
/* Description   | Get job result                                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | JobResult                                                  */
/*               |  CODEFLSIF_JOB_OK                                          */
/*               |  CODEFLSIF_JOB_FAILED                                      */
/*               |  CODEFLSIF_JOB_PENDING                                     */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(CodeFlsIf_JobResultType, CODEFLSIF_CODE_SLOW) CodeFlsIf_GetJobResult (void)
{
    return CodeFlsIf_JobInfo.JobResult;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Init                                             */
/* Description   | Initialize CodeFlsIf                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CODEFLSIF_CODE_SLOW) CodeFlsIf_Init (void)
{
    VAR(uint8, AUTOMATIC) Cnt;

    if( (CODEFLSIF_LOCAL_UNINIT == CodeFlsIf_JobInfo.LocalStatus) || (CODEFLSIF_LOCAL_IDLE == CodeFlsIf_JobInfo.LocalStatus) )
    {
        CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_IDLE;
        CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_OK;
        CodeFlsIf_JobInfo.ReqMode = CODEFLSIF_REQ_MODE_NONE;

        CodeFlsIf_EraseData.TargetAddr = CODEFLSIF_INVALID_ADDR;
        CodeFlsIf_EraseDataMirror.TargetAddr = CodeFlsIf_EraseData.TargetAddr;

        CodeFlsIf_EraseData.Size = CODEFLSIF_INVALID_SIZE;
        CodeFlsIf_EraseDataMirror.Size = CodeFlsIf_EraseData.Size;

        CodeFlsIf_WriteData.DestAddr = CODEFLSIF_INVALID_ADDR;
        CodeFlsIf_WriteDestAddrMirror = CodeFlsIf_WriteData.DestAddr;

        CodeFlsIf_WriteData.SrcAddr = NULL_PTR;
        CodeFlsIf_WriteData.TotalSize = CODEFLSIF_INVALID_SIZE;
        CodeFlsIf_WriteData.UpdateSize = CODEFLSIF_INVALID_SIZE;
        CodeFlsIf_WriteData.WriteBuffIndex = CODEFLSIF_RESET_WRITEBUFF_INDEX;
        CodeFlsIf_WriteData.SaveSetUserDataSize = CODEFLSIF_INVALID_SIZE;

        CodeFlsIf_ReadData.DestAddr = NULL_PTR;
        CodeFlsIf_ReadData.SrcAddr = CODEFLSIF_INVALID_ADDR;
        CodeFlsIf_ReadData.Size = CODEFLSIF_INVALID_SIZE;

        CodeFlsIf_WritableCheckData.TargetAddr = CODEFLSIF_INVALID_ADDR;
        CodeFlsIf_WritableCheckData.SrcAddr = NULL_PTR;
        CodeFlsIf_WritableCheckData.DataSize = CODEFLSIF_INVALID_SIZE;

        for( Cnt = 0U; Cnt < CODEFLSIF_REQ_SKIPINFO_NUM; Cnt++ )
        {
            CodeFlsIf_RequestSkipInfo.SkipInfo[Cnt].Addr = CODEFLSIF_INVALID_ADDR;
            Rpg_MemSet(&CodeFlsIf_RequestSkipInfo.SkipInfo[Cnt].Data[0], CODEFLSIF_INVALID_SKIPDATA, CODEFLSIF_SKIPDATA_SIZE);
        }
        CodeFlsIf_RequestSkipInfo.SkipNum = CODEFLSIF_SKIPINFO_NONE;

        CodeFlsIf_SaveSkipInfo.SkipNum = CODEFLSIF_SKIPINFO_NONE;

        CodeFlsIf_PostHookPendingFlg = STD_OFF;
    }
    else
    {
        CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_REPORT, CODEFLSIF_E_API_ID_INIT, CODEFLSIF_E_CASE_STATUS_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_MainFunction                                     */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CODEFLSIF_CODE_SLOW) CodeFlsIf_MainFunction (void)
{
    if( CODEFLSIF_LOCAL_READY == CodeFlsIf_JobInfo.LocalStatus )
    {
        if( CODEFLSIF_REQ_MODE_ERASE == CodeFlsIf_JobInfo.ReqMode )
        {
            CodeFlsIf_Sub_EraseReq();
        }
        else if( CODEFLSIF_REQ_MODE_READ == CodeFlsIf_JobInfo.ReqMode )
        {
            CodeFlsIf_Sub_Read();
        }
        else if( CODEFLSIF_REQ_MODE_WRITECHECK == CodeFlsIf_JobInfo.ReqMode )
        {
            CodeFlsIf_Sub_WriteChkReq();
        }
        else if( CODEFLSIF_REQ_MODE_SWITCHREQ == CodeFlsIf_JobInfo.ReqMode )
        {
            CodeFlsIf_Sub_SwitchReq();
        }
        else
        {
            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_REPORT, CODEFLSIF_E_API_ID_MAINFUNC, CODEFLSIF_E_CASE_REQMODE_FAIL);
        }
    }
    else if( CODEFLSIF_LOCAL_BUSY == CodeFlsIf_JobInfo.LocalStatus )
    {
        if( CODEFLSIF_REQ_MODE_ERASE == CodeFlsIf_JobInfo.ReqMode )
        {
            CodeFlsIf_Sub_EraseCompleteChk();
        }
        else if( CODEFLSIF_REQ_MODE_READ == CodeFlsIf_JobInfo.ReqMode )
        {
            CodeFlsIf_Sub_Read();
        }
        else if( CODEFLSIF_REQ_MODE_WRITECHECK == CodeFlsIf_JobInfo.ReqMode )
        {
            CodeFlsIf_Sub_WriteChkCmpltChk();
        }
        else if( CODEFLSIF_REQ_MODE_SWITCHREQ == CodeFlsIf_JobInfo.ReqMode )
        {
            CodeFlsIf_Sub_SwitchCmpltChk();
        }
        else
        {
            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_REPORT, CODEFLSIF_E_API_ID_MAINFUNC, CODEFLSIF_E_CASE_REQMODE_FAIL);
        }
    }
    else if( CODEFLSIF_LOCAL_UPDATEREADY == CodeFlsIf_JobInfo.LocalStatus )
    {
        if( CODEFLSIF_REQ_MODE_WRITE == CodeFlsIf_JobInfo.ReqMode )
        {
            CodeFlsIf_Sub_WriteReq();
        }
        else
        {
            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_REPORT, CODEFLSIF_E_API_ID_MAINFUNC, CODEFLSIF_E_CASE_REQMODE_FAIL);
        }
    }
    else if( CODEFLSIF_LOCAL_UPDATEWRITING == CodeFlsIf_JobInfo.LocalStatus )
    {
        if( CODEFLSIF_REQ_MODE_WRITE == CodeFlsIf_JobInfo.ReqMode )
        {
            CodeFlsIf_Sub_WriteCompleteChk();
        }
        else
        {
            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_REPORT, CODEFLSIF_E_API_ID_MAINFUNC, CODEFLSIF_E_CASE_REQMODE_FAIL);
        }
    }
    else
    {
        /* No process */
    }

    return;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_DeInit                                           */
/* Description   | Deinitialize CodeFlsIf                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CODEFLSIF_CODE_SLOW) CodeFlsIf_DeInit (void)
{
    VAR(uint8, AUTOMATIC) Cnt;

    CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_UNINIT;
    CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_OK;
    CodeFlsIf_JobInfo.ReqMode = CODEFLSIF_REQ_MODE_NONE;

    CodeFlsIf_EraseData.TargetAddr = 0x00000000UL;
    CodeFlsIf_EraseDataMirror.TargetAddr = 0x00000000UL;

    CodeFlsIf_EraseData.Size = CODEFLSIF_INVALID_SIZE;
    CodeFlsIf_EraseDataMirror.Size = CODEFLSIF_INVALID_SIZE;

    CodeFlsIf_WriteData.DestAddr = 0x00000000UL;
    CodeFlsIf_WriteDestAddrMirror = 0x00000000UL;

    CodeFlsIf_WriteData.SrcAddr = NULL_PTR;
    CodeFlsIf_WriteData.TotalSize = CODEFLSIF_INVALID_SIZE;
    CodeFlsIf_WriteData.UpdateSize = CODEFLSIF_INVALID_SIZE;
    CodeFlsIf_WriteData.WriteBuffIndex = CODEFLSIF_RESET_WRITEBUFF_INDEX;
    CodeFlsIf_WriteData.SaveSetUserDataSize = CODEFLSIF_INVALID_SIZE;

    CodeFlsIf_ReadData.DestAddr = NULL_PTR;
    CodeFlsIf_ReadData.SrcAddr = 0x00000000UL;
    CodeFlsIf_ReadData.Size = CODEFLSIF_INVALID_SIZE;

    CodeFlsIf_WritableCheckData.TargetAddr = 0x00000000UL;
    CodeFlsIf_WritableCheckData.SrcAddr = NULL_PTR;
    CodeFlsIf_WritableCheckData.DataSize = CODEFLSIF_INVALID_SIZE;

    for( Cnt = 0U; Cnt < CODEFLSIF_REQ_SKIPINFO_NUM; Cnt++ )
    {
        CodeFlsIf_RequestSkipInfo.SkipInfo[Cnt].Addr = 0x00000000UL;
        Rpg_MemSet(&CodeFlsIf_RequestSkipInfo.SkipInfo[Cnt].Data[0], CODEFLSIF_INVALID_SKIPDATA, CODEFLSIF_SKIPDATA_SIZE);
    }
    CodeFlsIf_RequestSkipInfo.SkipNum = CODEFLSIF_SKIPINFO_NONE;

    CodeFlsIf_SaveSkipInfo.SkipNum = CODEFLSIF_SKIPINFO_NONE;

    CodeFlsIf_PostHookPendingFlg = STD_OFF;

    return;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_ReprogComplete                                   */
/* Description   | Request to complete reprogramming                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CODEFLSIF_CODE_SLOW) CodeFlsIf_ReprogComplete (void)
{
    CodeFlsIf_SaveSkipInfo.SkipNum = CODEFLSIF_SKIPINFO_NONE;

    return;
}

#if ( REPROG_CFG_GETBLOCKINFO_USE == STD_ON )
/******************************************************************************/
/* Function Name | CodeFlsIf_GetBlockInfo                                     */
/* Description   | Acquire block information about address and size           */
/* Preconditions |                                                            */
/* Parameters    | [IN]  Addr      : Address                                  */
/*               | [OUT] BlockInfo : Block information                        */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CODEFLSIF_CODE_SLOW) CodeFlsIf_GetBlockInfo
(
    VAR(uint32, AUTOMATIC) Addr,
    P2VAR(CodeFlsIf_BlockInfoType, AUTOMATIC, CODEFLSIF_APPL_DATA) BlockInfo
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(CodeFls_BlockInfoType, AUTOMATIC) CodeFlsBlock;

    Result = E_NOT_OK;

    CodeFlsBlock.Addr = 0UL;
    CodeFlsBlock.Size = 0UL;

    FuncRet = CodeFls_GetBlockInfo(Addr, &CodeFlsBlock);
    if( (Std_ReturnType)E_OK == FuncRet )
    {
        BlockInfo->Addr = CodeFlsBlock.Addr;
        BlockInfo->Size = CodeFlsBlock.Size;
        Result = E_OK;
    }

    return Result;
}
#endif

/******************************************************************************/
/* Function Name | CodeFlsIf_GetNextWriteAddr                                 */
/* Description   | Acquires next write address                                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NextWriteAddr                                              */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint32, CODEFLSIF_CODE_SLOW) CodeFlsIf_GetNextWriteAddr (void)
{
    return CodeFlsIf_WriteData.DestAddr;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/
/******************************************************************************/
/* Function Name | CodeFlsIf_Sub_EraseReq                                     */
/* Description   | Request CodeFls to erase                                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_EraseReq (void)
{
    VAR(CodeFls_BlockInfoType, AUTOMATIC) BlockInfo;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
#if ( ( REPROG_CFG_SMALL_RAM_USE == STD_ON ) && ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) ) )
    VAR(gdn_uint8, AUTOMATIC) ComStatus;
    VAR(gdn_uint8, AUTOMATIC) PendRespStatus;
#endif

#if ( ( REPROG_CFG_SMALL_RAM_USE == STD_ON ) && ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) ) )
    ComStatus = Gdn_Dcm_Dcp_GetComStatus();
    PendRespStatus = Gdn_Dcm_Dcp_GetPendRespStatus();

    if( (ComStatus == GDN_DCM_DCP_COM_IDLE) && (PendRespStatus == GDN_DCM_DCP_PENDRESP_SENT) )
    {
#endif
        if( CodeFlsIf_EraseData.TargetAddr == CodeFlsIf_EraseDataMirror.TargetAddr )
        {
            if( CodeFlsIf_EraseData.Size == CodeFlsIf_EraseDataMirror.Size )
            {
                BlockInfo.Addr = CODEFLSIF_INVALID_ADDR;
                BlockInfo.Size = CODEFLSIF_INVALID_SIZE;
                FuncRet = CodeFls_GetBlockInfo(CodeFlsIf_EraseData.TargetAddr, &BlockInfo);
                if( (Std_ReturnType)E_OK == FuncRet )
                {
                    FuncRet = Rte_RpgEvtHk_PreCodeFlsCtrl(RTE_RPGEVTHK_CODEFLSCTRL_ERASE,
                                                            CodeFlsIf_EraseData.TargetAddr,
                                                            BlockInfo.Size);
                    if( (Std_ReturnType)E_OK == FuncRet )
                    {
                        CodeFlsIf_PostHookPendingFlg = STD_OFF;

                        SchM_StartFlsCtrl();

                        FuncRet = CodeFls_StartCtrl(CODEFLS_REQ_ERASE, CodeFlsIf_EraseData.TargetAddr, BlockInfo.Size);
                        if( (Std_ReturnType)E_OK == FuncRet )
                        {
                            CodeFls_Erase(CodeFlsIf_EraseData.TargetAddr, BlockInfo.Size);

                            CodeFlsIf_EraseData.TargetAddr += BlockInfo.Size;   /* no wrap around */
                            CodeFlsIf_EraseDataMirror.TargetAddr = CodeFlsIf_EraseData.TargetAddr;

                            CodeFlsIf_EraseData.Size -= BlockInfo.Size;         /* no wrap around */
                            CodeFlsIf_EraseDataMirror.Size = CodeFlsIf_EraseData.Size;

                            CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_BUSY;
                        }
                        else
                        {
                            SchM_FinishFlsCtrl();

                            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_ERASEREQ, CODEFLSIF_E_CASE_STARTCTRL_FAIL);
                        }
                    }
                    else if( RTE_RPGEVTHK_E_PENDING == FuncRet )
                    {
                        /* No process */
                    }
                    else
                    {
                        CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_ERASEREQ, CODEFLSIF_E_CASE_PREHOOK_FAIL);
                    }
                }
                else
                {
                    CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_ERASEREQ, CODEFLSIF_E_CASE_BLOCKINFO_FAIL);
                }
            }
            else
            {
                CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_REPORT, CODEFLSIF_E_API_ID_ERASEREQ, CODEFLSIF_E_CASE_ERASESIZE_FAIL);
            }
        }
        else
        {
            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_REPORT, CODEFLSIF_E_API_ID_ERASEREQ, CODEFLSIF_E_CASE_ERASEADDR_FAIL);
        }
#if ( ( REPROG_CFG_SMALL_RAM_USE == STD_ON ) && ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) ) )
    }
#endif

    return;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Sub_EraseCompleteChk                             */
/* Description   | Wait for completion of erasing                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_EraseCompleteChk (void)
{
    VAR(uint8, AUTOMATIC) CodeFlsStatus;
    VAR(uint8, AUTOMATIC) CodeFlsJobResult;
    VAR(uint8, AUTOMATIC) HookFlg;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    HookFlg = STD_OFF;

    if( (uint8)STD_ON == CodeFlsIf_PostHookPendingFlg )
    {
        HookFlg = STD_ON;
    }
    else
    {
        CodeFlsStatus = CodeFls_GetJobStatus();
        if( CODEFLS_IDLE == CodeFlsStatus )
        {
            CodeFlsJobResult = CodeFls_GetJobResult();

            CodeFls_EndCtrl();

            SchM_FinishFlsCtrl();

            if( CODEFLS_JOB_OK == CodeFlsJobResult )
            {
                HookFlg = STD_ON;
            }
            else
            {
                CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_ERASECHK, CODEFLSIF_E_CASE_FLSRESULT_FAIL);
            }
        }
        else if( CODEFLS_BUSY == CodeFlsStatus )
        {
            /* No process */
        }
        else
        {
            CodeFls_EndCtrl();

            SchM_FinishFlsCtrl();

            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_REPORT, CODEFLSIF_E_API_ID_ERASECHK, CODEFLSIF_E_CASE_FLSSTATUS_FAIL);
        }
    }

    if( (uint8)STD_ON == HookFlg )
    {
        CodeFlsIf_PostHookPendingFlg = STD_OFF;

        FuncRet = Rte_RpgEvtHk_PostCodeFlsCtrl();
        if( (Std_ReturnType)E_OK == FuncRet )
        {
            if( CodeFlsIf_EraseData.Size == CodeFlsIf_EraseDataMirror.Size )
            {
                if( 0UL == CodeFlsIf_EraseData.Size)
                {
                    CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_OK;
                    CodeFlsIf_JobInfo.ReqMode = CODEFLSIF_REQ_MODE_NONE;
                    CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_IDLE;
                }
                else
                {
                    CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_READY;
                }
            }
            else
            {
                CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_REPORT, CODEFLSIF_E_API_ID_ERASECHK, CODEFLSIF_E_CASE_ERASESIZE_FAIL);
            }
        }
        else if( RTE_RPGEVTHK_E_PENDING == FuncRet )
        {
            CodeFlsIf_PostHookPendingFlg = STD_ON;
        }
        else
        {
            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_ERASECHK, CODEFLSIF_E_CASE_POSTHOOK_FAIL);
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Sub_WriteReq                                     */
/* Description   | Request CodeFls to write or save skip information          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_WriteReq (void)
{
    VAR(uint8, AUTOMATIC) SkipIndex;
    VAR(uint8, AUTOMATIC) WriteRemainFlg;
    VAR(uint8, AUTOMATIC) WriteBuffResult;
    VAR(uint8, AUTOMATIC) IsSkipTargetArea;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(uint32, AUTOMATIC) SetUserDataSize;
#if ( ( REPROG_CFG_SMALL_RAM_USE == STD_ON ) && ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) ) )
    VAR(gdn_uint8, AUTOMATIC) ComStatus;
    VAR(gdn_uint8, AUTOMATIC) PendRespStatus;
#endif

#if ( ( REPROG_CFG_SMALL_RAM_USE == STD_ON ) && ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) ) )
    ComStatus = Gdn_Dcm_Dcp_GetComStatus();
    PendRespStatus = Gdn_Dcm_Dcp_GetPendRespStatus();

    if( (ComStatus == GDN_DCM_DCP_COM_IDLE) && (PendRespStatus == GDN_DCM_DCP_PENDRESP_SENT) )
    {
#endif
        if( CodeFlsIf_WriteData.DestAddr == CodeFlsIf_WriteDestAddrMirror )
        {
            SkipIndex = CODEFLSIF_INVALID_SKIPINDEX;
            SetUserDataSize = CODEFLSIF_INVALID_SIZE;

            do
            {
                WriteRemainFlg = STD_OFF;

                WriteBuffResult = CodeFlsIf_Sub_WriteSetWriteBuff(&SetUserDataSize);
                if( CODEFLSIF_WRITEBUFF_FULL == WriteBuffResult )
                {
                    IsSkipTargetArea = CodeFlsIf_Sub_WriteIsSkipArea(CodeFlsIf_WriteData.DestAddr, &SkipIndex);
                    if( CODEFLSIF_TARGETAREA_NOT_SKIP == IsSkipTargetArea )
                    {
                        FuncRet = CodeFlsIf_Sub_WriteReqWriteFls();
                        if( (Std_ReturnType)E_OK == FuncRet )
                        {
                            CodeFlsIf_WriteData.DestAddr += CodeFlsIf_Cfg_Data.WriteSize;   /* no wrap around */
                            CodeFlsIf_WriteDestAddrMirror = CodeFlsIf_WriteData.DestAddr;

                            CodeFlsIf_WriteData.TotalSize -= SetUserDataSize;               /* no wrap around */

                            CodeFlsIf_WriteData.SaveSetUserDataSize = CODEFLSIF_INVALID_SIZE;

                            CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_UPDATEWRITING;
                        }
                        else if( CODEFLSIF_E_PENDING == FuncRet )
                        {
                            CodeFlsIf_WriteData.SaveSetUserDataSize = SetUserDataSize;
                        }
                        else
                        {
                            /* No process */
                        }
                    }
                    else
                    {
                        FuncRet = CodeFlsIf_Sub_WriteSaveSkipInfo(SkipIndex);
                        if( (Std_ReturnType)E_OK == FuncRet )
                        {
                            CodeFlsIf_WriteData.DestAddr += CodeFlsIf_Cfg_Data.WriteSize;   /* no wrap around */
                            CodeFlsIf_WriteDestAddrMirror = CodeFlsIf_WriteData.DestAddr;

                            CodeFlsIf_WriteData.TotalSize -= SetUserDataSize;               /* no wrap around */

                            if( 0UL == CodeFlsIf_WriteData.TotalSize )
                            {
                                CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_OK;
                                CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_UPDATECOMPLETE;
                            }
                            else if( 0UL == CodeFlsIf_WriteData.UpdateSize )
                            {
                                CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_OK;
                                CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_UPDATEIDLE;
                            }
                            else
                            {
                                WriteRemainFlg = STD_ON;
                            }
                        }
                    }
                }
                else
                {
                    /* The update size specified by CodeFlsIf_WriteUpdate has copied but not reached CodeFlsIf_Cfg_Data.WriteSize */
                    CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_OK;
                    CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_UPDATEIDLE;
                }
            }
            while( (uint8)STD_ON == WriteRemainFlg );
        }
        else
        {
            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_REPORT, CODEFLSIF_E_API_ID_WRITEREQ, CODEFLSIF_E_CASE_WRITEADDRFAIL);
        }
#if ( ( REPROG_CFG_SMALL_RAM_USE == STD_ON ) && ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) ) )
    }
#endif

    return;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Sub_WriteSetWriteBuff                            */
/* Description   | Set the data to write buffer                               */
/* Preconditions |                                                            */
/* Parameters    | [OUT] SetUserDataSize : Size of user data in write buffer  */
/* Return Value  | Result                                                     */
/*               |  CODEFLSIF_WRITEBUFF_NOT_FULL                              */
/*               |  CODEFLSIF_WRITEBUFF_FULL                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_WriteSetWriteBuff
(
    P2VAR(uint32, AUTOMATIC, CODEFLSIF_APPL_DATA) SetUserDataSize
)
{
    VAR(uint32, AUTOMATIC) CopySize;
    VAR(uint8, AUTOMATIC) WriteBuffResult;

    if( CODEFLSIF_INVALID_SIZE != CodeFlsIf_WriteData.SaveSetUserDataSize )
    {
        *SetUserDataSize = CodeFlsIf_WriteData.SaveSetUserDataSize;
        WriteBuffResult = CODEFLSIF_WRITEBUFF_FULL;
    }
    else
    {
        if( (CodeFlsIf_Cfg_Data.WriteSize - CodeFlsIf_WriteData.WriteBuffIndex) > CodeFlsIf_WriteData.UpdateSize )  /* no wrap around */
        {
            CopySize = CodeFlsIf_WriteData.UpdateSize;
        }
        else
        {
            CopySize = CodeFlsIf_Cfg_Data.WriteSize - CodeFlsIf_WriteData.WriteBuffIndex;   /* no wrap around */
        }

        Rpg_MemCopy(&CodeFlsIf_WriteData.WriteBuff[CodeFlsIf_WriteData.WriteBuffIndex], CodeFlsIf_WriteData.SrcAddr, CopySize);

        CodeFlsIf_WriteData.SrcAddr = &CodeFlsIf_WriteData.SrcAddr[CopySize];
        CodeFlsIf_WriteData.UpdateSize -= CopySize;     /* no wrap around */
        CodeFlsIf_WriteData.WriteBuffIndex += CopySize; /* no wrap around */
        *SetUserDataSize = CodeFlsIf_WriteData.WriteBuffIndex;

        if( CodeFlsIf_Cfg_Data.WriteSize > CodeFlsIf_WriteData.WriteBuffIndex )
        {
            if( 0UL == (CodeFlsIf_WriteData.TotalSize - CodeFlsIf_WriteData.WriteBuffIndex) )   /* no wrap around */
            {
                /* The total size specified by CodeFlsIf_WriteStart has copied but not reached CodeFlsIf_Cfg_Data.WriteSize */
                CopySize = CodeFlsIf_Cfg_Data.WriteSize - CodeFlsIf_WriteData.WriteBuffIndex;   /* no wrap around */
                Rpg_MemSet(&CodeFlsIf_WriteData.WriteBuff[CodeFlsIf_WriteData.WriteBuffIndex], CODEFLSIF_PADDING_DATA, CopySize);

                CodeFlsIf_WriteData.WriteBuffIndex += CopySize; /* no wrap around */
            }
        }

        if( CodeFlsIf_Cfg_Data.WriteSize > CodeFlsIf_WriteData.WriteBuffIndex )
        {
            WriteBuffResult = CODEFLSIF_WRITEBUFF_NOT_FULL;
        }
        else
        {
            CodeFlsIf_WriteData.WriteBuffIndex = CODEFLSIF_RESET_WRITEBUFF_INDEX;

            WriteBuffResult = CODEFLSIF_WRITEBUFF_FULL;
        }
    }

    return WriteBuffResult;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Sub_WriteIsSkipArea                              */
/* Description   | Judge the area is target area for skip                     */
/* Preconditions |                                                            */
/* Parameters    | [IN]  DestAddr  : Destination address                      */
/*               | [OUT] SkipIndex : Index of skip information                */
/* Return Value  | Result                                                     */
/*               |  CODEFLSIF_TARGETAREA_NOT_SKIP                             */
/*               |  CODEFLSIF_TARGETAREA_SKIP                                 */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_WriteIsSkipArea
(
    VAR(uint32, AUTOMATIC) DestAddr,
    P2VAR(uint8, AUTOMATIC, CODEFLSIF_APPL_DATA) SkipIndex
)
{
    VAR(uint8, AUTOMATIC) IsSkipTargetArea;
    VAR(uint8, AUTOMATIC) Cnt;

    IsSkipTargetArea = CODEFLSIF_TARGETAREA_NOT_SKIP;

    for( Cnt = 0U; Cnt < CodeFlsIf_RequestSkipInfo.SkipNum; Cnt++ )
    {
        if( CodeFlsIf_RequestSkipInfo.SkipInfo[Cnt].Addr == DestAddr )
        {
            IsSkipTargetArea = CODEFLSIF_TARGETAREA_SKIP;

            *SkipIndex = Cnt;

            break;
        }
    }

    return IsSkipTargetArea;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Sub_WriteReqWriteFls                             */
/* Description   | Request CodeFls to write                                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  CODEFLSIF_E_PENDING                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_WriteReqWriteFls (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Result = E_NOT_OK;

    FuncRet = Rte_RpgEvtHk_PreCodeFlsCtrl(RTE_RPGEVTHK_CODEFLSCTRL_WRITE,
                                            CodeFlsIf_WriteData.DestAddr,
                                            CodeFlsIf_Cfg_Data.WriteSize);
    if( (Std_ReturnType)E_OK == FuncRet )
    {
        CodeFlsIf_PostHookPendingFlg = STD_OFF;
        SchM_StartFlsCtrl();

        if( CodeFlsIf_WriteData.DestAddr == CodeFlsIf_WriteDestAddrMirror )
        {
            FuncRet = CodeFls_StartCtrl(CODEFLS_REQ_WRITE, CodeFlsIf_WriteData.DestAddr, CodeFlsIf_Cfg_Data.WriteSize);
            if( (Std_ReturnType)E_OK == FuncRet )
            {
                CodeFls_Write(CodeFlsIf_WriteData.DestAddr,
                                    (const uint8*)&CodeFlsIf_WriteData.WriteBuff[0],
                                    CodeFlsIf_Cfg_Data.WriteSize);

                Result = E_OK;
            }
            else
            {
                SchM_FinishFlsCtrl();

                CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_WRITEREQ, CODEFLSIF_E_CASE_STARTCTRL_FAIL);
            }
        }
        else
        {
            SchM_FinishFlsCtrl();

            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_REPORT, CODEFLSIF_E_API_ID_WRITEREQ, CODEFLSIF_E_CASE_WRITEADDRFAIL);
        }
    }
    else if( RTE_RPGEVTHK_E_PENDING == FuncRet )
    {
        Result = CODEFLSIF_E_PENDING;
    }
    else
    {
        CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_WRITEREQ, CODEFLSIF_E_CASE_PREHOOK_FAIL);
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Sub_WriteSaveSkipInfo                            */
/* Description   | Save skip information                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN]  SkipIndex  : Index of skip information               */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_WriteSaveSkipInfo
(
    VAR(uint8, AUTOMATIC) SkipIndex
)
{
    VAR(uint32, AUTOMATIC) Cnt;
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(uint8, AUTOMATIC) SkipDataIndex;

    Result = E_NOT_OK;

    for( Cnt = 0UL; Cnt < CodeFlsIf_Cfg_Data.WriteSize; Cnt++ )
    {
        SkipDataIndex = (uint8)(Cnt & CODEFLSIF_SKIPDATAINDEX_MASK);
        if( CodeFlsIf_RequestSkipInfo.SkipInfo[SkipIndex].Data[SkipDataIndex] != CodeFlsIf_WriteData.WriteBuff[Cnt] )
        {
            break;
        }
    }

    if( CodeFlsIf_Cfg_Data.WriteSize == Cnt )
    {
        CodeFlsIf_SaveSkipInfo.SkipInfo[CodeFlsIf_SaveSkipInfo.SkipNum].Addr = CodeFlsIf_RequestSkipInfo.SkipInfo[SkipIndex].Addr;

        Rpg_MemCopy(&CodeFlsIf_SaveSkipInfo.SkipInfo[CodeFlsIf_SaveSkipInfo.SkipNum].Data[0],
                        (const uint8*)&CodeFlsIf_RequestSkipInfo.SkipInfo[SkipIndex].Data[0],
                        CODEFLSIF_SKIPDATA_SIZE);

        CodeFlsIf_SaveSkipInfo.SkipNum++;   /* no wrap around */

        Result = E_OK;
    }
    else
    {
        CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_WRITEREQ, CODEFLSIF_E_CASE_VALUECHK_FAIL);
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Sub_WriteCompleteChk                             */
/* Description   | Wait for completion of writing                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_WriteCompleteChk (void)
{
    VAR(uint8, AUTOMATIC) CodeFlsStatus;
    VAR(uint8, AUTOMATIC) CodeFlsJobResult;
    VAR(uint8, AUTOMATIC) HookFlg;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    HookFlg = STD_OFF;

    if( (uint8)STD_ON == CodeFlsIf_PostHookPendingFlg )
    {
        HookFlg = STD_ON;
    }
    else
    {
        CodeFlsStatus = CodeFls_GetJobStatus();
        if( CODEFLS_IDLE == CodeFlsStatus )
        {
            CodeFlsJobResult = CodeFls_GetJobResult();

            CodeFls_EndCtrl();

            SchM_FinishFlsCtrl();

            if( CODEFLS_JOB_OK == CodeFlsJobResult )
            {
                HookFlg = STD_ON;
            }
            else
            {
                CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_WRITECHK, CODEFLSIF_E_CASE_FLSRESULT_FAIL);
            }
        }
        else if( CODEFLS_BUSY == CodeFlsStatus )
        {
            /* No process */
        }
        else
        {
            CodeFls_EndCtrl();

            SchM_FinishFlsCtrl();

            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_REPORT, CODEFLSIF_E_API_ID_WRITECHK, CODEFLSIF_E_CASE_FLSSTATUS_FAIL);
        }
    }

    if( (uint8)STD_ON == HookFlg )
    {
        CodeFlsIf_PostHookPendingFlg = STD_OFF;

        FuncRet = Rte_RpgEvtHk_PostCodeFlsCtrl();
        if( (Std_ReturnType)E_OK == FuncRet )
        {
            if( 0UL == CodeFlsIf_WriteData.TotalSize )
            {
                CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_OK;
                CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_UPDATECOMPLETE;
            }
            else if( 0UL == CodeFlsIf_WriteData.UpdateSize )
            {
                CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_OK;
                CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_UPDATEIDLE;
            }
            else
            {
                CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_UPDATEREADY;
            }
        }
        else if( RTE_RPGEVTHK_E_PENDING == FuncRet )
        {
            CodeFlsIf_PostHookPendingFlg = STD_ON;
        }
        else
        {
            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_WRITECHK, CODEFLSIF_E_CASE_POSTHOOK_FAIL);
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Sub_Read                                         */
/* Description   | Read target area that was requested by CodeFlsIf_Read      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_Read (void)
{
    VAR(uint32, AUTOMATIC) TargetSize;
    VAR(uint32, AUTOMATIC) SkipStartOffsetSize;
    VAR(uint32, AUTOMATIC) CopySkipDataSize;
    VAR(uint8, AUTOMATIC) IsSkipTargetArea;
    VAR(uint8, AUTOMATIC) SkipIndex;

    SkipIndex = CODEFLSIF_INVALID_SKIPINDEX;

    if( CodeFlsIf_Cfg_Data.ReadSize > CodeFlsIf_ReadData.Size )
    {
        TargetSize = CodeFlsIf_ReadData.Size;
    }
    else
    {
        TargetSize = CodeFlsIf_Cfg_Data.ReadSize;
    }

    do
    {
        IsSkipTargetArea = CodeFlsIf_Sub_ReadIsSkipArea(CodeFlsIf_ReadData.SrcAddr, TargetSize, &SkipIndex);
        if( CODEFLSIF_TARGETAREA_NOT_SKIP == IsSkipTargetArea )
        {
            Rpg_MemCopy(CodeFlsIf_ReadData.DestAddr, (const uint8*)CodeFlsIf_ReadData.SrcAddr, TargetSize);

            CodeFlsIf_ReadData.DestAddr = &CodeFlsIf_ReadData.DestAddr[TargetSize];
            CodeFlsIf_ReadData.SrcAddr += TargetSize;   /* no wrap around */
            CodeFlsIf_ReadData.Size -= TargetSize;      /* no wrap around */

            TargetSize = 0UL;
        }
        else
        {
            if( CodeFlsIf_SaveSkipInfo.SkipInfo[SkipIndex].Addr > CodeFlsIf_ReadData.SrcAddr )
            {
                /* Non skip area exist between the read address and the start address of skip area */
                SkipStartOffsetSize = CodeFlsIf_SaveSkipInfo.SkipInfo[SkipIndex].Addr - CodeFlsIf_ReadData.SrcAddr; /* no wrap around */
                Rpg_MemCopy(CodeFlsIf_ReadData.DestAddr, (const uint8*)CodeFlsIf_ReadData.SrcAddr, SkipStartOffsetSize);

                CodeFlsIf_ReadData.DestAddr = &CodeFlsIf_ReadData.DestAddr[SkipStartOffsetSize];
                CodeFlsIf_ReadData.SrcAddr += SkipStartOffsetSize;  /* no wrap around */
                CodeFlsIf_ReadData.Size -= SkipStartOffsetSize;     /* no wrap around */

                TargetSize -= SkipStartOffsetSize;                  /* no wrap around */
            }

            if( ((CodeFlsIf_SaveSkipInfo.SkipInfo[SkipIndex].Addr + CodeFlsIf_Cfg_Data.WriteSize) - CodeFlsIf_ReadData.SrcAddr) >   /* no wrap around */
                    TargetSize )
            {
                /* The remain size of skip area less than the read size */
                CopySkipDataSize = TargetSize;
            }
            else
            {
                CopySkipDataSize =
                    (CodeFlsIf_SaveSkipInfo.SkipInfo[SkipIndex].Addr + CodeFlsIf_Cfg_Data.WriteSize) - CodeFlsIf_ReadData.SrcAddr;  /* no wrap around */
            }

            CodeFlsIf_Sub_ReadCopySkipData(CopySkipDataSize, SkipIndex);

            CodeFlsIf_ReadData.DestAddr = &CodeFlsIf_ReadData.DestAddr[CopySkipDataSize];
            CodeFlsIf_ReadData.SrcAddr += CopySkipDataSize; /* no wrap around */
            CodeFlsIf_ReadData.Size -= CopySkipDataSize;    /* no wrap around */

            TargetSize -= CopySkipDataSize;                 /* no wrap around */
        }
    }
    while( 0UL < TargetSize );

    if( 0UL == CodeFlsIf_ReadData.Size )
    {
        CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_OK;
        CodeFlsIf_JobInfo.ReqMode = CODEFLSIF_REQ_MODE_NONE;
        CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_IDLE;
    }
    else
    {
        CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_BUSY;
    }

    return;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Sub_ReadIsSkipArea                               */
/* Description   | Judge the area is skipped area                             */
/* Preconditions |                                                            */
/* Parameters    | [IN]  SrcAddr   : Source address                           */
/*               | [IN]  ReadSize  : Read size                                */
/*               | [OUT] SkipIndex : Index of skip information                */
/* Return Value  | Result                                                     */
/*               |  CODEFLSIF_TARGETAREA_NOT_SKIP                             */
/*               |  CODEFLSIF_TARGETAREA_SKIP                                 */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_ReadIsSkipArea
(
    VAR(uint32, AUTOMATIC) SrcAddr,
    VAR(uint32, AUTOMATIC) ReadSize,
    P2VAR(uint8, AUTOMATIC, CODEFLSIF_APPL_DATA) SkipIndex
)
{
    VAR(uint32, AUTOMATIC) SkipAreaStartAddr;
    VAR(uint32, AUTOMATIC) SkipAreaEndAddr;
    VAR(uint8, AUTOMATIC) IsSkipTargetArea;
    VAR(uint8, AUTOMATIC) Cnt;

    IsSkipTargetArea = CODEFLSIF_TARGETAREA_NOT_SKIP;

    for( Cnt = 0U; Cnt < CodeFlsIf_SaveSkipInfo.SkipNum; Cnt++ )
    {
        SkipAreaStartAddr = CodeFlsIf_SaveSkipInfo.SkipInfo[Cnt].Addr;
        SkipAreaEndAddr = SkipAreaStartAddr + (CodeFlsIf_Cfg_Data.WriteSize - CODEFLSIF_ADJUST_ENDADDR);                    /* no wrap around */
        if( ((SrcAddr <= SkipAreaStartAddr) && (SkipAreaStartAddr <= (SrcAddr + (ReadSize - CODEFLSIF_ADJUST_ENDADDR)))) || /* no wrap around */
                ((SkipAreaStartAddr < SrcAddr) && (SrcAddr <= SkipAreaEndAddr)) )
        {
            IsSkipTargetArea = CODEFLSIF_TARGETAREA_SKIP;

            *SkipIndex = Cnt;

            break;
        }
    }

    return IsSkipTargetArea;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Sub_ReadCopySkipData                             */
/* Description   | Copy skip data                                             */
/* Preconditions |                                                            */
/* Parameters    | [IN] CopySize  : Copy size                                 */
/*               | [IN] SkipIndex : Index of skip information                 */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_ReadCopySkipData
(
    VAR(uint32, AUTOMATIC) CopySize,
    VAR(uint8, AUTOMATIC) SkipIndex
)
{
    VAR(uint32, AUTOMATIC) Cnt;
    VAR(uint8, AUTOMATIC) SkipDataIndex;

    for( Cnt = 0UL; Cnt < CopySize; Cnt++ )
    {
        SkipDataIndex = (uint8)((CodeFlsIf_ReadData.SrcAddr + Cnt) & CODEFLSIF_SKIPDATAINDEX_MASK); /* no wrap around */

        CodeFlsIf_ReadData.DestAddr[Cnt] = CodeFlsIf_SaveSkipInfo.SkipInfo[SkipIndex].Data[SkipDataIndex];
    }

    return;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Sub_WriteChkReq                                  */
/* Description   | Request CodeFls to check writable                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_WriteChkReq (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
#if ( ( REPROG_CFG_SMALL_RAM_USE == STD_ON ) && ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) ) )
    VAR(gdn_uint8, AUTOMATIC) ComStatus;
    VAR(gdn_uint8, AUTOMATIC) PendRespStatus;
#endif

#if ( ( REPROG_CFG_SMALL_RAM_USE == STD_ON ) && ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) ) )
    ComStatus = Gdn_Dcm_Dcp_GetComStatus();
    PendRespStatus = Gdn_Dcm_Dcp_GetPendRespStatus();

    if( (ComStatus == GDN_DCM_DCP_COM_IDLE) && (PendRespStatus == GDN_DCM_DCP_PENDRESP_SENT) )
    {
#endif
        FuncRet = Rte_RpgEvtHk_PreCodeFlsCtrl(RTE_RPGEVTHK_CODEFLSCTRL_WRITABLECHECK,
                                                CodeFlsIf_WritableCheckData.TargetAddr,
                                                CodeFlsIf_WritableCheckData.DataSize);
        if( (Std_ReturnType)E_OK == FuncRet )
        {
            CodeFlsIf_PostHookPendingFlg = STD_OFF;
            SchM_StartFlsCtrl();

            FuncRet = CodeFls_StartCtrl(CODEFLS_REQ_WRITABLECHECK,
                                            CodeFlsIf_WritableCheckData.TargetAddr,
                                            CodeFlsIf_WritableCheckData.DataSize);
            if( (Std_ReturnType)E_OK == FuncRet )
            {
                CodeFls_WritableCheck(CodeFlsIf_WritableCheckData.TargetAddr,
                                            CodeFlsIf_WritableCheckData.SrcAddr,
                                            CodeFlsIf_WritableCheckData.DataSize);

                CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_BUSY;
            }
            else
            {
                SchM_FinishFlsCtrl();

                CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_WRITABLEREQ, CODEFLSIF_E_CASE_STARTCTRL_FAIL);
            }
        }
        else if( RTE_RPGEVTHK_E_PENDING == FuncRet )
        {
            /* No process */
        }
        else
        {
            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_WRITABLEREQ, CODEFLSIF_E_CASE_PREHOOK_FAIL);
        }
#if ( ( REPROG_CFG_SMALL_RAM_USE == STD_ON ) && ( ( REPROG_CFG_SUBMICON_NOUSE == STD_ON ) || ( REPROG_CFG_SUBMICON_USE_MAIN == STD_ON ) ) )
    }
#endif

    return;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Sub_WriteChkCmpltChk                             */
/* Description   | Wait for completion of the checking writable               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_WriteChkCmpltChk (void)
{
    VAR(uint8, AUTOMATIC) CodeFlsStatus;
    VAR(uint8, AUTOMATIC) CodeFlsJobResult;
    VAR(uint8, AUTOMATIC) HookFlg;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    HookFlg = STD_OFF;

    if( (uint8)STD_ON == CodeFlsIf_PostHookPendingFlg )
    {
        HookFlg = STD_ON;
    }
    else
    {
        CodeFlsStatus = CodeFls_GetJobStatus();
        if( CODEFLS_IDLE == CodeFlsStatus )
        {
            CodeFlsJobResult = CodeFls_GetJobResult();

            CodeFls_EndCtrl();

            SchM_FinishFlsCtrl();

            if( CODEFLS_JOB_OK == CodeFlsJobResult )
            {
                HookFlg = STD_ON;
            }
            else
            {
                CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_WRITABLECHK, CODEFLSIF_E_CASE_FLSRESULT_FAIL);
            }
        }
        else if( CODEFLS_BUSY == CodeFlsStatus )
        {
            /* No process */
        }
        else
        {
            CodeFls_EndCtrl();

            SchM_FinishFlsCtrl();

            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_REPORT, CODEFLSIF_E_API_ID_WRITABLECHK, CODEFLSIF_E_CASE_FLSSTATUS_FAIL);
        }
    }

    if( (uint8)STD_ON == HookFlg )
    {
        CodeFlsIf_PostHookPendingFlg = STD_OFF;

        FuncRet = Rte_RpgEvtHk_PostCodeFlsCtrl();
        if( (Std_ReturnType)E_OK == FuncRet )
        {
            CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_OK;
            CodeFlsIf_JobInfo.ReqMode = CODEFLSIF_REQ_MODE_NONE;
            CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_IDLE;
        }
        else if( RTE_RPGEVTHK_E_PENDING == FuncRet )
        {
            CodeFlsIf_PostHookPendingFlg = STD_ON;
        }
        else
        {
            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_WRITABLECHK, CODEFLSIF_E_CASE_POSTHOOK_FAIL);
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Sub_SwitchReq                                    */
/* Description   | Request CodeFls to switch valid area                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_SwitchReq (void)
{
#if ( REPROGOPT_DOUBLEMAP_TYPE == REPROGOPT_DOUBLEMAP_REWRITE_INVALID )
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = Rte_RpgEvtHk_PreCodeFlsCtrl(RTE_RPGEVTHK_CODEFLSCTRL_SWITCHVALIDAREA,
                                            0UL,
                                            0UL);
    if( (Std_ReturnType)E_OK == FuncRet )
    {
        CodeFlsIf_PostHookPendingFlg = STD_OFF;
        SchM_StartFlsCtrl();

        FuncRet = CodeFls_StartCtrl(CODEFLS_REQ_SWITCHVALIDAREA, 0UL, 0UL);
        if( (Std_ReturnType)E_OK == FuncRet )
        {
            CodeFls_SwitchValidArea();
            CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_BUSY;
        }
        else
        {
            SchM_FinishFlsCtrl();

            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_SWITCHREQ, CODEFLSIF_E_CASE_STARTCTRL_FAIL);
        }
    }
    else if( RTE_RPGEVTHK_E_PENDING == FuncRet )
    {
        /* No process */
    }
    else
    {
        CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_SWITCHREQ, CODEFLSIF_E_CASE_PREHOOK_FAIL);
    }
#else
    CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_REPORT, CODEFLSIF_E_API_ID_SWITCHREQ, CODEFLSIF_E_CASE_REQMODE_FAIL);
#endif

    return;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Sub_SwitchCmpltChk                               */
/* Description   | Wait for completion of the switching valid area            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_SwitchCmpltChk (void)
{
    VAR(uint8, AUTOMATIC) CodeFlsStatus;
    VAR(uint8, AUTOMATIC) CodeFlsJobResult;
    VAR(uint8, AUTOMATIC) HookFlg;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    HookFlg = STD_OFF;

    if( (uint8)STD_ON == CodeFlsIf_PostHookPendingFlg )
    {
        HookFlg = STD_ON;
    }
    else
    {
        CodeFlsStatus = CodeFls_GetJobStatus();
        if( CODEFLS_IDLE == CodeFlsStatus )
        {
            CodeFlsJobResult = CodeFls_GetJobResult();

            CodeFls_EndCtrl();

            SchM_FinishFlsCtrl();

            if( CODEFLS_JOB_OK == CodeFlsJobResult )
            {
                HookFlg = STD_ON;
            }
            else
            {
                CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_SWITCHCHK, CODEFLSIF_E_CASE_FLSRESULT_FAIL);
            }
        }
        else if( CODEFLS_BUSY == CodeFlsStatus )
        {
            /* No process */
        }
        else
        {
            CodeFls_EndCtrl();

            SchM_FinishFlsCtrl();

            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_REPORT, CODEFLSIF_E_API_ID_SWITCHCHK, CODEFLSIF_E_CASE_FLSSTATUS_FAIL);
        }
    }

    if( (uint8)STD_ON == HookFlg )
    {
        CodeFlsIf_PostHookPendingFlg = STD_OFF;

        FuncRet = Rte_RpgEvtHk_PostCodeFlsCtrl();
        if( (Std_ReturnType)E_OK == FuncRet )
        {
            CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_OK;
            CodeFlsIf_JobInfo.ReqMode = CODEFLSIF_REQ_MODE_NONE;
            CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_IDLE;
        }
        else if( RTE_RPGEVTHK_E_PENDING == FuncRet )
        {
            CodeFlsIf_PostHookPendingFlg = STD_ON;
        }
        else
        {
            CodeFlsIf_Sub_Fail(CODEFLSIF_ERROR_NOT_REPORT, CODEFLSIF_E_API_ID_SWITCHCHK, CODEFLSIF_E_CASE_POSTHOOK_FAIL);
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | CodeFlsIf_Sub_Fail                                         */
/* Description   | Set the information to failed and notify EcuM of the error */
/*               | information                                                */
/* Preconditions |                                                            */
/* Parameters    | [IN] ReportReq                                             */
/*               |       CODEFLSIF_ERROR_REPORT    : Call EcuM_ReportError    */
/*               |       CODEFLSIF_ERROR_NOT_REPORT: Do not Call              */
/*               |                                   EcuM_ReportError         */
/*               | [IN] ApiId   : API ID                                      */
/*               | [IN] ErrorId : Error ID                                    */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CODEFLSIF_CODE_FAST) CodeFlsIf_Sub_Fail
(
    VAR(uint8, AUTOMATIC) ReportReq,
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
)
{
    VAR(EcuM_ErrorType, AUTOMATIC) ErrorInfo;

    CodeFlsIf_JobInfo.JobResult = CODEFLSIF_JOB_FAILED;
    CodeFlsIf_JobInfo.ReqMode = CODEFLSIF_REQ_MODE_NONE;
    CodeFlsIf_JobInfo.LocalStatus = CODEFLSIF_LOCAL_IDLE;

    if( CODEFLSIF_ERROR_REPORT == ReportReq )
    {
        ErrorInfo.ModuleId = ECUM_MODULE_CODEFLSIF;
        ErrorInfo.ApiId = ApiId;
        ErrorInfo.ErrorId = ErrorId;
        EcuM_ReportError(&ErrorInfo);
    }

    return;
}

#define CODEFLSIF_STOP_SEC_CODE
#include <CodeFlsIf_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/02/12 :Update                                rel.AUBASS */
/*  v3.00       :2022/07/05 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

