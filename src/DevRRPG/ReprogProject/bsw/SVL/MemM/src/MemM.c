/* MemM_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | MemM/CODE                                                   */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <MemM.h>
#include "MemM_Local.h"
#include "MemM_Cfg.h"
#include "MemM_Ucfg.h"

#include <Tm.h>
#include <CodeFlsIf.h>
#include <ExtCodeFlsIf.h>
#include <CodeRamIf.h>
#include <Sys.h>
#include <MemErrM.h>
#include <EcuM.h>
#include <ReprogOpt.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define MEMM_REQ_MODE_NONE                  (0x00U)
#define MEMM_REQ_MODE_ERASE                 ((uint8)0x11U)
#define MEMM_REQ_MODE_WRITE                 ((uint8)0x22U)
#define MEMM_REQ_MODE_READ                  ((uint8)0x33U)
#define MEMM_REQ_MODE_RPGCOMPLETE           ((uint8)0x44U)

#define MEMM_ERASE_PHASE_IDLE               (0x00U)
#define MEMM_ERASE_PHASE_READY              ((uint8)0x11U)
#define MEMM_ERASE_PHASE_GRNT_WRITECHK      ((uint8)0x22U)
#define MEMM_ERASE_PHASE_GRNT_EXEC          ((uint8)0x33U)
#define MEMM_ERASE_PHASE_ERASE_EXEC         ((uint8)0x44U)

#define MEMM_RPGCMPLT_PHASE_IDLE            (0x00U)
#define MEMM_RPGCMPLT_PHASE_WRITE_READY     ((uint8)0x11U)
#define MEMM_RPGCMPLT_PHASE_WRITE_EXEC      ((uint8)0x22U)
#define MEMM_RPGCMPLT_PHASE_READ_EXEC       ((uint8)0x33U)
#define MEMM_RPGCMPLT_PHASE_SWITCH_EXEC     ((uint8)0x44U)

#define MEMM_GRNT_AREA_SIZE_MIN             (0x00000004UL)
#define MEMM_GRNT_DATA_NUM                  (MEMM_CFG_GRNT_AREA_SIZE / MEMM_GRNT_AREA_SIZE_MIN)

#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
#define MEMM_EXECUTE_GRNT_TARGET_NONE       ((uint8)0x00U)
#define MEMM_EXECUTE_GRNT_TARGET_ON         ((uint8)0xFFU)
#else
#define MEMM_EXECUTE_GRNT_TARGET_NONE       (0x00000000UL)
#define MEMM_EXECUTE_GRNT_TARGET_BITON      (0x00000001UL)
#endif

#define MEMM_WRITE_GRNT_SKIP_NONE           (0x00U)

#define MEMM_ERROR_NOT_REPORT               (0x00U)
#define MEMM_ERROR_REPORT                   ((uint8)0x01U)

#define MEMM_E_API_ID_INIT                  (0x00U)
#define MEMM_E_API_ID_MAINFUNC              (0x01U)
#define MEMM_E_API_ID_ERASE                 (0x02U)
#define MEMM_E_API_ID_ERASE_WRITABLEREQ     (0x03U)
#define MEMM_E_API_ID_ERASE_WRITABLECHK     (0x04U)
#define MEMM_E_API_ID_ERASE_GRNTREQ         (0x05U)
#define MEMM_E_API_ID_ERASE_GRNTCHK         (0x06U)
#define MEMM_E_API_ID_ERASEREQ              (0x07U)
#define MEMM_E_API_ID_ERASECHK              (0x08U)
#define MEMM_E_API_ID_WRITE                 (0x09U)
#define MEMM_E_API_ID_READ                  (0x0AU)
#define MEMM_E_API_ID_RPGCMPLT              (0x0BU)
#define MEMM_E_API_ID_RPGCMPLT_WRITEREQ     (0x0CU)
#define MEMM_E_API_ID_RPGCMPLT_WRITECHK     (0x0DU)
#define MEMM_E_API_ID_RPGCOMPLETE_READCHK   (0x0EU)
#define MEMM_E_API_ID_RPGCOMPLETE_SWITCHCHK (0x0FU)

#define MEMM_E_CASE_STATUS_FAIL             (0x80U)
#define MEMM_E_CASE_REQMODE_FAIL            (0x81U)
#define MEMM_E_CASE_PHASE_FAIL              (0x82U)
#define MEMM_E_CASE_GRNTACTION_FAIL         (0x83U)
#define MEMM_E_CASE_DEVICETYPE_FAIL         (0x84U)
#define MEMM_E_CASE_TIMEOUT                 (0x85U)
#define MEMM_E_CASE_IFSTATUS_FAIL           (0x86U)
#define MEMM_E_CASE_APICALL_NG              (0x87U)
#define MEMM_E_CASE_IFRESULT_FAIL           (0x88U)
#define MEMM_E_CASE_VERIFY_NG               (0x89U)
#define MEMM_E_CASE_GRNTTARGETAREA_FAIL     (0x8AU)
#define MEMM_E_CASE_AREAINDEX_FAIL          (0x8BU)
#define MEMM_E_CASE_ERASEDATA_FAIL          (0x8CU)

#define MEMM_INVALID_MEMORY_AREA_INDEX      (0U)
#define MEMM_INVALID_START_POINT            (0UL)

#define MEMM_ADJUST_ENDADDR                 (1UL)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
    uint8 ExecuteGrntTargetAreaInfo[MEMM_UCFG_MEMORY_AREA_NUM];
#else
    uint32 ExecuteGrntTargetAreaInfo;
#endif
    MemM_StatusType JobStatus;
    MemM_JobResultType JobResult;
    uint8 ReqMode;
    uint8 ErasePhase;
    uint8 ReprogCompletePhase;
} MemM_JobInfoType;

typedef struct {
    uint32 Addr;
    uint32 Size;
} MemM_EraseType;

typedef struct {
    uint32 MemoryId;
    uint32 VirtualAddr;
    uint32 Size;
    uint32 PhysicalAddr;
    uint8 AreaIndex;
} MemM_MemoryAreaChkType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_Erase (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_EraseWritableChkReq (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_EraseWritableCmpltChk (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_EraseGrntReq (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_EraseGrntCompleteChk (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_EraseReq (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_EraseCompleteChk (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_EraseCompleteChkRom (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_EraseCompleteChkExtRom (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_Write (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_WriteCompleteChk (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_WriteCompleteChkRom (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_WriteCompleteChkExtRom (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_WriteCompleteChkRam (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_Read (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_ReadCompleteChk (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_ReadCompleteChkRom (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_ReadCompleteChkExtRom (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_ReadCompleteChkRam (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_RpgCmplt (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_RpgCmpltWriteReq (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_RpgCmpltWriteCmpltChk (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_RpgCmpltReadCmpltChk (void);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_RpgCmpltSwitchCmpltChk (void);
static FUNC(Std_ReturnType, MEMM_CODE_FAST) MemM_Sub_CheckArea
(
    P2VAR(MemM_MemoryAreaChkType, AUTOMATIC, MEMM_APPL_DATA) CheckAreaData
);
static FUNC(Std_ReturnType, MEMM_CODE_FAST) MemM_Sub_ChangeStatus (void);
static FUNC(Std_ReturnType, MEMM_CODE_FAST) MemM_Sub_CheckTimeOut (void);
static FUNC(Std_ReturnType, MEMM_CODE_FAST) MemM_Sub_GetTimeOutValue
(
    P2VAR(uint32, AUTOMATIC, MEMM_APPL_DATA) TimeOutValue
);
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_Fail
(
    VAR(uint8, AUTOMATIC) ReportReq,
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define MEMM_START_SEC_VAR
#include <MemM_MemMap.h>

static VAR(MemM_JobInfoType, MEMM_VAR_CLEARED) MemM_JobInfo;
static VAR(Tm_PredefTimer1us32bitType, MEMM_VAR_CLEARED) MemM_TimerInstance;
static VAR(MemM_EraseType, MEMM_VAR_CLEARED) MemM_EraseData;
static VAR(uint32, MEMM_VAR_CLEARED) MemM_GrntAreaData[MEMM_GRNT_DATA_NUM];
static VAR(uint8, MEMM_VAR_CLEARED) MemM_MemoryAreaIndex;
static VAR(MemM_JobInfoType, MEMM_VAR_CLEARED) MemM_JobInfoMirror;
static VAR(MemM_EraseType, MEMM_VAR_CLEARED) MemM_EraseDataMirror;
static VAR(uint8, MEMM_VAR_CLEARED) MemM_MemoryAreaIndexMirror;

#define MEMM_STOP_SEC_VAR
#include <MemM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define MEMM_START_SEC_CST
#include <MemM_MemMap.h>

#define MEMM_STOP_SEC_CST
#include <MemM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define MEMM_START_SEC_CODE
#include <MemM_MemMap.h>

/******************************************************************************/
/* Function Name | MemM_Erase                                                 */
/* Description   | Request to erase                                           */
/* Preconditions |                                                            */
/* Parameters    | [IN] MemoryId   : Memory ID                                */
/*               | [IN] TargetAddr : Erase address                            */
/*               | [IN] TargetSize : Erase size                               */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, MEMM_CODE_SLOW) MemM_Erase
(
    VAR(uint32, AUTOMATIC) MemoryId,
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize
)
{
    VAR(MemM_MemoryAreaChkType, AUTOMATIC) MemoryAreaChkData;
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Result = E_NOT_OK;

    if( MEMM_IDLE == MemM_JobInfo.JobStatus )
    {
        MemoryAreaChkData.MemoryId = MemoryId;
        MemoryAreaChkData.VirtualAddr = TargetAddr;
        MemoryAreaChkData.Size = TargetSize;
        MemoryAreaChkData.PhysicalAddr = MEMM_INVALID_ADDR;
        MemoryAreaChkData.AreaIndex = MEMM_INVALID_MEMORY_AREA_INDEX;

        FuncRet = MemM_Sub_CheckArea(&MemoryAreaChkData);
        if( (Std_ReturnType)E_OK == FuncRet )
        {
            FuncRet = Tm_ResetTimer1us32bit(&MemM_TimerInstance);
            if( (Std_ReturnType)E_OK == FuncRet )
            {
                MemM_JobInfo.JobStatus = MEMM_BUSY;

                MemM_EraseData.Addr = MemoryAreaChkData.PhysicalAddr;
                MemM_EraseDataMirror.Addr = MemM_EraseData.Addr;

                MemM_EraseData.Size = MemoryAreaChkData.Size;
                MemM_EraseDataMirror.Size = MemM_EraseData.Size;

                MemM_MemoryAreaIndex = MemoryAreaChkData.AreaIndex;
                MemM_MemoryAreaIndexMirror = MemM_MemoryAreaIndex;

                MemM_JobInfo.ReqMode = MEMM_REQ_MODE_ERASE;
                MemM_JobInfo.ErasePhase = MEMM_ERASE_PHASE_READY;
                MemM_JobInfo.JobResult = MEMM_JOB_PENDING;

                Result = E_OK;
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | MemM_WriteStart                                            */
/* Description   | Request CodeFlsIf,ExtCodeFlsIf,CodeRamIf to start writing  */
/* Preconditions |                                                            */
/* Parameters    | [IN] MemoryId  : Memory ID                                 */
/*               | [IN] DestAddr  : Destination address                       */
/*               | [IN] TotalSize : Total write size                          */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, MEMM_CODE_SLOW) MemM_WriteStart
(
    VAR(uint32, AUTOMATIC) MemoryId,
    VAR(uint32, AUTOMATIC) DestAddr,
    VAR(uint32, AUTOMATIC) TotalSize
)
{
    VAR(MemM_MemoryAreaChkType, AUTOMATIC) MemoryAreaChkData;
    VAR(CodeFlsIf_SkipInfoType, AUTOMATIC) SkipInfo[MEMM_GRNT_AREA_NUM];
    VAR(uint32, AUTOMATIC) Cnt;
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(uint8, AUTOMATIC) SkipNum;

    Result = E_NOT_OK;

    if( MEMM_IDLE == MemM_JobInfo.JobStatus )
    {
        MemoryAreaChkData.MemoryId = MemoryId;
        MemoryAreaChkData.VirtualAddr = DestAddr;
        MemoryAreaChkData.Size = TotalSize;
        MemoryAreaChkData.PhysicalAddr = MEMM_INVALID_ADDR;
        MemoryAreaChkData.AreaIndex = MEMM_INVALID_MEMORY_AREA_INDEX;

        FuncRet = MemM_Sub_CheckArea(&MemoryAreaChkData);
        if( (Std_ReturnType)E_OK == FuncRet )
        {
            switch( MemM_Cfg_Data.MemoryAreaData[MemoryAreaChkData.AreaIndex].TargetDevice )
            {
                case MEMM_DEVICE_TYPE_CODEFLS:
                    SkipNum = MEMM_WRITE_GRNT_SKIP_NONE;

                    for( Cnt = 0UL; Cnt < MEMM_GRNT_AREA_NUM; Cnt++ )
                    {
                        if( MEMM_WRITE_GRNT_AREA_SKIP ==
                                MemM_Cfg_Data.GrntData[MemM_Cfg_Data.GrntMode].ReqWriteData.SkipData[Cnt].SkipReq )
                        {
                            SkipInfo[Cnt].SkipAddr = MemM_Cfg_Data.MemoryAreaData[MemoryAreaChkData.AreaIndex].GrntAddr[Cnt];
                            SkipInfo[Cnt].ExpectedValue =
                                MemM_Cfg_Data.GrntData[MemM_Cfg_Data.GrntMode].ReqWriteData.SkipData[Cnt].ExpectedValue;
                            SkipNum++;  /* no wrap around */
                        }
                        else
                        {
                           SkipInfo[Cnt].SkipAddr = MEMM_INVALID_ADDR;
                           SkipInfo[Cnt].ExpectedValue = MEMM_INVALID_GRNT_VALUE;
                        }
                    }

                    FuncRet = CodeFlsIf_WriteStart(MemoryAreaChkData.PhysicalAddr,
                                                       TotalSize,
                                                       SkipNum,
                                                       (const CodeFlsIf_SkipInfoType*)&SkipInfo[0]);
                    break;

                case MEMM_DEVICE_TYPE_EXTCODEFLS:
                    FuncRet = ExtCodeFlsIf_WriteStart(MemoryAreaChkData.PhysicalAddr, TotalSize);
                    break;

                case MEMM_DEVICE_TYPE_CODERAM:
                    FuncRet = CodeRamIf_WriteStart(MemoryAreaChkData.PhysicalAddr, TotalSize);
                    break;

                default:
                    FuncRet = E_NOT_OK;
                    break;
            }

            if( (Std_ReturnType)E_OK == FuncRet )
            {
                MemM_JobInfo.JobStatus = MEMM_UPDATEIDLE;
                MemM_MemoryAreaIndex = MemoryAreaChkData.AreaIndex;
                MemM_MemoryAreaIndexMirror = MemM_MemoryAreaIndex;
                MemM_JobInfo.ReqMode = MEMM_REQ_MODE_WRITE;

                Result = E_OK;
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | MemM_WriteUpdate                                           */
/* Description   | Request CodeFlsIf,ExtCodeFlsIf,CodeRamIf to update writing */
/* Preconditions |                                                            */
/* Parameters    | [IN] SrcAddr : Source address                              */
/*               | [IN] Size    : Write size                                  */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, MEMM_CODE_SLOW) MemM_WriteUpdate
(
    P2CONST(uint8, AUTOMATIC, MEMM_APPL_CONST) SrcAddr,
    VAR(uint32, AUTOMATIC) Size
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Result = E_NOT_OK;

    if( MEMM_UPDATEIDLE == MemM_JobInfo.JobStatus )
    {
        if( (NULL_PTR != SrcAddr) && (0UL != Size) )
        {
            FuncRet = Tm_ResetTimer1us32bit(&MemM_TimerInstance);
            if( (Std_ReturnType)E_OK == FuncRet )
            {
                if( MemM_MemoryAreaIndex == MemM_MemoryAreaIndexMirror )
                {
                    switch( MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
                    {
                        case MEMM_DEVICE_TYPE_CODEFLS:
                            FuncRet = CodeFlsIf_WriteUpdate(SrcAddr, Size);
                            break;

                        case MEMM_DEVICE_TYPE_EXTCODEFLS:
                            FuncRet = ExtCodeFlsIf_WriteUpdate(SrcAddr, Size);
                            break;

                        case MEMM_DEVICE_TYPE_CODERAM:
                            FuncRet = CodeRamIf_WriteUpdate(SrcAddr, Size);
                            break;

                        default:
                            FuncRet = E_NOT_OK;
                            break;
                    }

                    if( (Std_ReturnType)E_OK == FuncRet )
                    {
                        MemM_JobInfo.JobStatus = MEMM_UPDATEBUSY;
                        MemM_JobInfo.JobResult = MEMM_JOB_PENDING;

                        Result = E_OK;
                    }
                }
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | MemM_WriteFinish                                           */
/* Description   | Request CodeFlsIf,ExtCodeFlsIf,CodeRamIf to finish writing */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, MEMM_CODE_SLOW) MemM_WriteFinish (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Result = E_NOT_OK;

    if( MEMM_UPDATECOMPLETE == MemM_JobInfo.JobStatus )
    {
        if( MemM_MemoryAreaIndex == MemM_MemoryAreaIndexMirror )
        {
            switch( MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
            {
                case MEMM_DEVICE_TYPE_CODEFLS:
                    FuncRet = CodeFlsIf_WriteFinish();
                    break;

                case MEMM_DEVICE_TYPE_EXTCODEFLS:
                    FuncRet = ExtCodeFlsIf_WriteFinish();
                    break;

                case MEMM_DEVICE_TYPE_CODERAM:
                    FuncRet = CodeRamIf_WriteFinish();
                    break;

                default:
                    FuncRet = E_NOT_OK;
                    break;
            }

            if( (Std_ReturnType)E_OK == FuncRet )
            {
                MemM_JobInfo.JobStatus = MEMM_IDLE;
                MemM_JobInfo.ReqMode = MEMM_REQ_MODE_NONE;

                Result = E_OK;
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | MemM_Read                                                  */
/* Description   | Request CodeFlsIf,ExtCodeFlsIf,CodeRamIf to read           */
/* Preconditions |                                                            */
/* Parameters    | [IN]  MemoryId : Memory ID                                 */
/*               | [IN]  SrcAddr  : Source address                            */
/*               | [OUT] DestAddr : Destination address                       */
/*               | [IN]  Size     : Read size                                 */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, MEMM_CODE_SLOW) MemM_Read
(
    VAR(uint32, AUTOMATIC) MemoryId,
    VAR(uint32, AUTOMATIC) SrcAddr,
    P2VAR(uint8, AUTOMATIC, MEMM_APPL_DATA) DestAddr,
    VAR(uint32, AUTOMATIC) Size
)
{
    VAR(MemM_MemoryAreaChkType, AUTOMATIC) MemoryAreaChkData;
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Result = E_NOT_OK;

    FuncRet = MemM_Sub_ChangeStatus();
    if( (Std_ReturnType)E_OK == FuncRet )
    {
        if( NULL_PTR != DestAddr )
        {
            MemoryAreaChkData.MemoryId = MemoryId;
            MemoryAreaChkData.VirtualAddr = SrcAddr;
            MemoryAreaChkData.Size = Size;
            MemoryAreaChkData.PhysicalAddr = MEMM_INVALID_ADDR;
            MemoryAreaChkData.AreaIndex = MEMM_INVALID_MEMORY_AREA_INDEX;

            FuncRet = MemM_Sub_CheckArea(&MemoryAreaChkData);
            if( (Std_ReturnType)E_OK == FuncRet )
            {
                FuncRet = Tm_ResetTimer1us32bit(&MemM_TimerInstance);
                if( (Std_ReturnType)E_OK == FuncRet )
                {
                    switch( MemM_Cfg_Data.MemoryAreaData[MemoryAreaChkData.AreaIndex].TargetDevice )
                    {
                        case MEMM_DEVICE_TYPE_CODEFLS:
                            FuncRet = CodeFlsIf_Read(MemoryAreaChkData.PhysicalAddr, DestAddr, Size);
                            break;

                        case MEMM_DEVICE_TYPE_EXTCODEFLS:
                            FuncRet = ExtCodeFlsIf_Read(MemoryAreaChkData.PhysicalAddr, DestAddr, Size);
                            break;

                        case MEMM_DEVICE_TYPE_CODERAM:
                            FuncRet = CodeRamIf_Read(MemoryAreaChkData.PhysicalAddr, DestAddr, Size);
                            break;

                        default:
                            FuncRet = E_NOT_OK;
                            break;
                    }

                    if( (Std_ReturnType)E_OK == FuncRet )
                    {
                        /* In this case, Jobstatus was already updated */
                        MemM_MemoryAreaIndex = MemoryAreaChkData.AreaIndex;
                        MemM_MemoryAreaIndexMirror = MemM_MemoryAreaIndex;

                        MemM_JobInfo.ReqMode = MEMM_REQ_MODE_READ;
                        MemM_JobInfo.JobResult = MEMM_JOB_PENDING;

                        Result = E_OK;
                    }
                    else
                    {
                        MemM_JobInfo.JobStatus = MEMM_IDLE;
                    }
                }
                else
                {
                    MemM_JobInfo.JobStatus = MEMM_IDLE;
                }
            }
            else
            {
                MemM_JobInfo.JobStatus = MEMM_IDLE;
            }
        }
        else
        {
            MemM_JobInfo.JobStatus = MEMM_IDLE;
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | MemM_GetStatus                                             */
/* Description   | Get job status                                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | JobStatus                                                  */
/*               |  MEMM_UNINIT                                               */
/*               |  MEMM_IDLE                                                 */
/*               |  MEMM_BUSY                                                 */
/*               |  MEMM_UPDATEIDLE                                           */
/*               |  MEMM_UPDATEBUSY                                           */
/*               |  MEMM_UPDATECOMPLETE                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(MemM_StatusType, MEMM_CODE_SLOW) MemM_GetStatus (void)
{
    return MemM_JobInfo.JobStatus;
}

/******************************************************************************/
/* Function Name | MemM_GetJobResult                                          */
/* Description   | Get job result                                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | JobResult                                                  */
/*               |  MEMM_JOB_OK                                               */
/*               |  MEMM_JOB_FAILED                                           */
/*               |  MEMM_JOB_PENDING                                          */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(MemM_JobResultType, MEMM_CODE_SLOW) MemM_GetJobResult (void)
{
    return MemM_JobInfo.JobResult;
}

/******************************************************************************/
/* Function Name | MemM_Init                                                  */
/* Description   | Initialize MemM                                            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, MEMM_CODE_SLOW) MemM_Init (void)
{
#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
    VAR(uint32, AUTOMATIC) Cnt;
#endif

    if( (MEMM_UNINIT == MemM_JobInfo.JobStatus) || (MEMM_IDLE == MemM_JobInfo.JobStatus) )
    {
#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
        for( Cnt = 0UL; Cnt < MemM_Cfg_Data.MemoryAreaNum; Cnt++ )
        {
            MemM_JobInfo.ExecuteGrntTargetAreaInfo[Cnt] = MEMM_EXECUTE_GRNT_TARGET_NONE;
            MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo[Cnt] = MemM_JobInfo.ExecuteGrntTargetAreaInfo[Cnt];
        }
#else
        MemM_JobInfo.ExecuteGrntTargetAreaInfo = MEMM_EXECUTE_GRNT_TARGET_NONE;
        MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo = MemM_JobInfo.ExecuteGrntTargetAreaInfo;
#endif

        MemM_JobInfo.JobStatus = MEMM_IDLE;
        MemM_JobInfoMirror.JobStatus = MemM_JobInfo.JobStatus;

        MemM_JobInfo.JobResult = MEMM_JOB_OK;
        MemM_JobInfoMirror.JobResult = MemM_JobInfo.JobResult;

        MemM_JobInfo.ReqMode = MEMM_REQ_MODE_NONE;
        MemM_JobInfoMirror.ReqMode = MemM_JobInfo.ReqMode;

        MemM_JobInfo.ErasePhase = MEMM_ERASE_PHASE_IDLE;
        MemM_JobInfoMirror.ErasePhase = MemM_JobInfo.ErasePhase;

        MemM_JobInfo.ReprogCompletePhase = MEMM_RPGCMPLT_PHASE_IDLE;
        MemM_JobInfoMirror.ReprogCompletePhase = MemM_JobInfo.ReprogCompletePhase;

        MemM_MemoryAreaIndex = MEMM_INVALID_MEMORY_AREA_INDEX;
        MemM_MemoryAreaIndexMirror = MemM_MemoryAreaIndex;

        MemM_TimerInstance.StartPoint = MEMM_INVALID_START_POINT;

        MemM_EraseData.Addr = MEMM_INVALID_ADDR;
        MemM_EraseDataMirror.Addr = MemM_EraseData.Addr;

        MemM_EraseData.Size = MEMM_INVALID_SIZE;
        MemM_EraseDataMirror.Size = MemM_EraseData.Size;

    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_INIT, MEMM_E_CASE_STATUS_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_MainFunction                                          */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, MEMM_CODE_SLOW) MemM_MainFunction (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    if( (MEMM_BUSY == MemM_JobInfo.JobStatus) || (MEMM_UPDATEBUSY == MemM_JobInfo.JobStatus) )
    {
        FuncRet = MemM_Sub_CheckTimeOut();
        if( (Std_ReturnType)E_OK == FuncRet )
        {
            if( MEMM_BUSY == MemM_JobInfo.JobStatus )
            {
                if( MEMM_REQ_MODE_ERASE == MemM_JobInfo.ReqMode )
                {
                    MemM_Sub_Erase();
                }
                else if( MEMM_REQ_MODE_READ == MemM_JobInfo.ReqMode )
                {
                    MemM_Sub_Read();
                }
                else if( MEMM_REQ_MODE_RPGCOMPLETE == MemM_JobInfo.ReqMode )
                {
                    MemM_Sub_RpgCmplt();
                }
                else
                {
                    MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_MAINFUNC, MEMM_E_CASE_REQMODE_FAIL);
                }
            }
            else
            {
                if( MEMM_REQ_MODE_WRITE == MemM_JobInfo.ReqMode )
                {
                    MemM_Sub_Write();
                }
                else
                {
                    MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_MAINFUNC, MEMM_E_CASE_REQMODE_FAIL);
                }
            }
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_MAINFUNC, MEMM_E_CASE_TIMEOUT);
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_DeInit                                                */
/* Description   | Deinitialize MemM                                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, MEMM_CODE_SLOW) MemM_DeInit (void)
{
#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
    VAR(uint32, AUTOMATIC) Cnt;

    for( Cnt = 0UL; Cnt < MemM_Cfg_Data.MemoryAreaNum; Cnt++ )
    {
        MemM_JobInfo.ExecuteGrntTargetAreaInfo[Cnt] = MEMM_EXECUTE_GRNT_TARGET_NONE;
        MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo[Cnt] = MemM_JobInfo.ExecuteGrntTargetAreaInfo[Cnt];
    }
#else
    MemM_JobInfo.ExecuteGrntTargetAreaInfo = MEMM_EXECUTE_GRNT_TARGET_NONE;
    MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo = MEMM_EXECUTE_GRNT_TARGET_NONE;
#endif

    MemM_JobInfo.JobStatus = MEMM_UNINIT;
    MemM_JobInfoMirror.JobStatus = MEMM_UNINIT;

    MemM_JobInfo.JobResult = MEMM_JOB_OK;
    MemM_JobInfoMirror.JobResult = MEMM_JOB_OK;

    MemM_JobInfo.ReqMode = MEMM_REQ_MODE_NONE;
    MemM_JobInfoMirror.ReqMode = MEMM_REQ_MODE_NONE;

    MemM_JobInfo.ErasePhase = MEMM_ERASE_PHASE_IDLE;
    MemM_JobInfoMirror.ErasePhase = MEMM_ERASE_PHASE_IDLE;

    MemM_JobInfo.ReprogCompletePhase = MEMM_RPGCMPLT_PHASE_IDLE;
    MemM_JobInfoMirror.ReprogCompletePhase = MEMM_RPGCMPLT_PHASE_IDLE;

    MemM_MemoryAreaIndex = MEMM_INVALID_MEMORY_AREA_INDEX;
    MemM_MemoryAreaIndexMirror = MEMM_INVALID_MEMORY_AREA_INDEX;

    MemM_TimerInstance.StartPoint = MEMM_INVALID_START_POINT;

    MemM_EraseData.Addr = 0x00000000UL;
    MemM_EraseDataMirror.Addr = 0x00000000UL;

    MemM_EraseData.Size = MEMM_INVALID_SIZE;
    MemM_EraseDataMirror.Size = MEMM_INVALID_SIZE;

    return;
}

/******************************************************************************/
/* Function Name | MemM_ReprogComplete                                        */
/* Description   | Request CodeFlsIf to complete reprogramming                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, MEMM_CODE_SLOW) MemM_ReprogComplete (void)
{
    VAR(uint32, AUTOMATIC) Cnt;
#if ( MEMM_CFG_EXPAND_AREANUM_USE != STD_ON )
    VAR(uint32, AUTOMATIC) Checkbit;
#endif
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Result = E_NOT_OK;

    if( MEMM_IDLE == MemM_JobInfo.JobStatus )
    {
#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
        for( Cnt = 0UL; Cnt < MemM_Cfg_Data.MemoryAreaNum; Cnt++ )
        {
            if( MemM_JobInfo.ExecuteGrntTargetAreaInfo[Cnt] != MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo[Cnt] )
            {
                break;
            }
        }

        if( MemM_Cfg_Data.MemoryAreaNum == Cnt )
        {
            for( Cnt = 0UL; Cnt < MemM_Cfg_Data.MemoryAreaNum; Cnt++ )
            {
                if( MEMM_EXECUTE_GRNT_TARGET_NONE != MemM_JobInfo.ExecuteGrntTargetAreaInfo[Cnt] )
                {
                    break;
                }
            }

            if( MemM_Cfg_Data.MemoryAreaNum > Cnt )
            {
#else
        if( MemM_JobInfo.ExecuteGrntTargetAreaInfo == MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo )
        {
            if( MEMM_EXECUTE_GRNT_TARGET_NONE != MemM_JobInfo.ExecuteGrntTargetAreaInfo )
            {
#endif
                CodeFlsIf_ReprogComplete();

#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
                MemM_MemoryAreaIndex = (uint8)Cnt;
                MemM_MemoryAreaIndexMirror = MemM_MemoryAreaIndex;
#else
                for( Cnt = 0UL; Cnt < MemM_Cfg_Data.MemoryAreaNum; Cnt++ )
                {
                    Checkbit = MemM_JobInfo.ExecuteGrntTargetAreaInfo >> Cnt;
                    Checkbit &= MEMM_EXECUTE_GRNT_TARGET_BITON;
                    if( MEMM_EXECUTE_GRNT_TARGET_BITON == Checkbit )
                    {
                        MemM_MemoryAreaIndex = (uint8)Cnt;
                        MemM_MemoryAreaIndexMirror = MemM_MemoryAreaIndex;
                        break;
                    }
                }

                if( MemM_Cfg_Data.MemoryAreaNum > Cnt )
                {
#endif
                FuncRet = Tm_ResetTimer1us32bit(&MemM_TimerInstance);
                if( (Std_ReturnType)E_OK == FuncRet )
                {
                    MemM_JobInfo.JobStatus = MEMM_BUSY;
                    MemM_JobInfo.ReqMode = MEMM_REQ_MODE_RPGCOMPLETE;
                    MemM_JobInfo.ReprogCompletePhase = MEMM_RPGCMPLT_PHASE_WRITE_READY;
                    MemM_JobInfo.JobResult = MEMM_JOB_PENDING;

                    Result = E_OK;
                }
#if ( MEMM_CFG_EXPAND_AREANUM_USE != STD_ON )
                }
#endif
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | MemM_CnvPhysicalAddr                                       */
/* Description   | Convert virtual address into physical address              */
/* Preconditions |                                                            */
/* Parameters    | [IN]  MemoryId     : Memory ID                             */
/*               | [IN]  VirtualAddr  : Virtual address                       */
/*               | [OUT] PhysicalAddr : Physical address                      */
/*               | [OUT] DeviceType   : Device type                           */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, MEMM_CODE_SLOW) MemM_CnvPhysicalAddr
(
    VAR(uint32, AUTOMATIC) MemoryId,
    VAR(uint32, AUTOMATIC) VirtualAddr,
    P2VAR(uint32, AUTOMATIC, MEMM_APPL_DATA) PhysicalAddr,
    P2VAR(uint8, AUTOMATIC, MEMM_APPL_DATA) DeviceType
)
{
    VAR(uint32, AUTOMATIC) Cnt;
    VAR(uint32, AUTOMATIC) PermittedStartAddr;
    VAR(uint32, AUTOMATIC) PermittedEndAddr;
    VAR(uint32, AUTOMATIC) AddrOffset;
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_NOT_OK;

    if( NULL_PTR != PhysicalAddr )
    {
        for( Cnt = 0UL; Cnt < MemM_Cfg_Data.MemoryAreaNum; Cnt++ )
        {
            if( MemM_Cfg_Data.MemoryAreaData[Cnt].MemoryId == MemoryId )
            {
                PermittedStartAddr = MemM_Cfg_Data.MemoryAreaData[Cnt].VirtualAddr;
                PermittedEndAddr = PermittedStartAddr + (MemM_Cfg_Data.MemoryAreaData[Cnt].Size - MEMM_ADJUST_ENDADDR); /* no wrap around */

                if( (PermittedStartAddr <= VirtualAddr) && (VirtualAddr <= PermittedEndAddr) )
                {
                    AddrOffset = VirtualAddr - PermittedStartAddr;
                    *PhysicalAddr = MemM_Cfg_Data.MemoryAreaData[Cnt].PhysicalAddr + AddrOffset;    /* no wrap around */
                    *DeviceType = MemM_Cfg_Data.MemoryAreaData[Cnt].TargetDevice;
                    Result = E_OK;
                    break;
                }
            }
        }
    }

    return Result;
}

#if ( REPROG_CFG_GETBLOCKINFO_USE == STD_ON )
/******************************************************************************/
/* Function Name | MemM_GetBlockInfo                                          */
/* Description   | Acquire block information about address and size           */
/* Preconditions |                                                            */
/* Parameters    | [IN]  MemoryId  : Memory ID                                */
/*               | [IN]  Addr      : Address                                  */
/*               | [OUT] BlockInfo : Block information                        */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, MEMM_CODE_SLOW) MemM_GetBlockInfo
(
    VAR(uint32, AUTOMATIC) MemoryId,
    VAR(uint32, AUTOMATIC) Addr,
    P2VAR(MemM_BlockInfoType, AUTOMATIC, MEMM_APPL_DATA) BlockInfo
)
{
    VAR(uint32, AUTOMATIC) Cnt;
    VAR(uint32, AUTOMATIC) PermittedStartAddr;
    VAR(uint32, AUTOMATIC) PermittedEndAddr;
    VAR(uint32, AUTOMATIC) AddrOffset;
    VAR(uint32, AUTOMATIC) TargetPhysicalAddr;
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(CodeFlsIf_BlockInfoType, AUTOMATIC) CodeFlsIfBlock;
    VAR(ExtCodeFlsIf_BlockInfoType, AUTOMATIC) ExtCodeFlsIfBlock;

    Result = E_NOT_OK;

    if( NULL_PTR != BlockInfo )
    {
        for( Cnt = 0UL; Cnt < MemM_Cfg_Data.MemoryAreaNum; Cnt++ )
        {
            if( MemM_Cfg_Data.MemoryAreaData[Cnt].MemoryId == MemoryId )
            {
                PermittedStartAddr = MemM_Cfg_Data.MemoryAreaData[Cnt].VirtualAddr;
                PermittedEndAddr = PermittedStartAddr + (MemM_Cfg_Data.MemoryAreaData[Cnt].Size - MEMM_ADJUST_ENDADDR); /* no wrap around */

                if( (PermittedStartAddr <= Addr) && (Addr <= PermittedEndAddr) )
                {
                    break;
                }
            }
        }

        if( Cnt < MemM_Cfg_Data.MemoryAreaNum )
        {
            AddrOffset = Addr - MemM_Cfg_Data.MemoryAreaData[Cnt].VirtualAddr;                  /* no wrap around */
            TargetPhysicalAddr = MemM_Cfg_Data.MemoryAreaData[Cnt].PhysicalAddr + AddrOffset;   /* no wrap around */

            if( MEMM_DEVICE_TYPE_CODEFLS == MemM_Cfg_Data.MemoryAreaData[Cnt].TargetDevice )
            {
                CodeFlsIfBlock.Addr = 0UL;
                CodeFlsIfBlock.Size = 0UL;

                FuncRet = CodeFlsIf_GetBlockInfo(TargetPhysicalAddr, &CodeFlsIfBlock);
                if( (Std_ReturnType)E_OK == FuncRet )
                {
                    BlockInfo->Addr = CodeFlsIfBlock.Addr;
                    BlockInfo->Size = CodeFlsIfBlock.Size;
                }
            }
            else if( MEMM_DEVICE_TYPE_EXTCODEFLS == MemM_Cfg_Data.MemoryAreaData[Cnt].TargetDevice )
            {
                ExtCodeFlsIfBlock.Addr = 0UL;
                ExtCodeFlsIfBlock.Size = 0UL;

                FuncRet = ExtCodeFlsIf_GetBlockInfo(TargetPhysicalAddr, &ExtCodeFlsIfBlock);
                if( (Std_ReturnType)E_OK == FuncRet )
                {
                    BlockInfo->Addr = ExtCodeFlsIfBlock.Addr;
                    BlockInfo->Size = ExtCodeFlsIfBlock.Size;
                }
            }
            else
            {
                FuncRet = E_NOT_OK;
            }

            if( (Std_ReturnType)E_OK == FuncRet )
            {
                AddrOffset = BlockInfo->Addr - MemM_Cfg_Data.MemoryAreaData[Cnt].PhysicalAddr;  /* no wrap around */
                BlockInfo->Addr = MemM_Cfg_Data.MemoryAreaData[Cnt].VirtualAddr + AddrOffset;   /* no wrap around */

                Result = E_OK;
            }
        }
    }

    return Result;
}
#endif

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/
/******************************************************************************/
/* Function Name | MemM_Sub_Erase                                             */
/* Description   | Distribute to subfunction in erasing phase                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_Erase (void)
{
#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
    VAR(uint32, AUTOMATIC) Cnt;
#endif

    if( MEMM_ERASE_GRNTACT_ERASE == MemM_Cfg_Data.GrntData[MemM_Cfg_Data.GrntMode].ReqEraseData.Action )
    {
        if( MEMM_ERASE_PHASE_READY == MemM_JobInfo.ErasePhase )
        {
#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
            for( Cnt = 0UL; Cnt < MemM_Cfg_Data.MemoryAreaNum; Cnt++ )
            {
                if( MemM_JobInfo.ExecuteGrntTargetAreaInfo[Cnt] != MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo[Cnt] )
                {
                    break;
                }
            }

#if ( MEMM_CFG_NONERASE_GRNTAREA_USE == STD_ON )
            if( (MemM_Cfg_Data.MemoryAreaNum == Cnt) &&
                (MemM_EraseData.Addr == MemM_EraseDataMirror.Addr) )
            {
                for( Cnt = 0UL; Cnt < MemM_Cfg_Data.MemoryAreaNum; Cnt++ )
                {
                    if( MEMM_EXECUTE_GRNT_TARGET_ON == MemM_JobInfo.ExecuteGrntTargetAreaInfo[Cnt] )
                    {
                        break;
                    }
                }

                if( (MemM_Cfg_Data.MemoryAreaNum == Cnt) &&
                    (MEMM_INVALID_ADDR != MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].GrntAddr[MEMM_GRNT_AREA_1ST]) &&
                    (MemM_EraseData.Addr != MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].GrntAddr[MEMM_GRNT_AREA_1ST]) )
#else
            if( MemM_Cfg_Data.MemoryAreaNum == Cnt )
            {
                for( Cnt = 0UL; Cnt < MemM_Cfg_Data.MemoryAreaNum; Cnt++ )
                {
                    if( MEMM_EXECUTE_GRNT_TARGET_ON == MemM_JobInfo.ExecuteGrntTargetAreaInfo[Cnt] )
                    {
                        break;
                    }
                }

                if( MemM_Cfg_Data.MemoryAreaNum == Cnt )
#endif
#else
#if ( MEMM_CFG_NONERASE_GRNTAREA_USE == STD_ON )
            if( (MemM_JobInfo.ExecuteGrntTargetAreaInfo == MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo) &&
                (MemM_EraseData.Addr == MemM_EraseDataMirror.Addr) )
            {
                if( (MEMM_EXECUTE_GRNT_TARGET_NONE == MemM_JobInfo.ExecuteGrntTargetAreaInfo) &&
                    (MEMM_INVALID_ADDR != MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].GrntAddr[MEMM_GRNT_AREA_1ST]) &&
                    (MemM_EraseData.Addr != MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].GrntAddr[MEMM_GRNT_AREA_1ST]) )

#else
            if( MemM_JobInfo.ExecuteGrntTargetAreaInfo == MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo )
            {
                if( MEMM_EXECUTE_GRNT_TARGET_NONE == MemM_JobInfo.ExecuteGrntTargetAreaInfo )
#endif
#endif
                {
                    MemM_Sub_EraseGrntReq();
                }
                else
                {
                    MemM_Sub_EraseReq();
                }
            }
            else
            {
                MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASE, MEMM_E_CASE_GRNTTARGETAREA_FAIL);
            }
        }
        else if( MEMM_ERASE_PHASE_GRNT_EXEC == MemM_JobInfo.ErasePhase )
        {
            MemM_Sub_EraseGrntCompleteChk();
        }
        else if( MEMM_ERASE_PHASE_ERASE_EXEC == MemM_JobInfo.ErasePhase )
        {
            MemM_Sub_EraseCompleteChk();
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASE, MEMM_E_CASE_PHASE_FAIL);
        }
    }
    else if( MEMM_ERASE_GRNTACT_WRITE == MemM_Cfg_Data.GrntData[MemM_Cfg_Data.GrntMode].ReqEraseData.Action )
    {
        if( MEMM_ERASE_PHASE_READY == MemM_JobInfo.ErasePhase )
        {
            MemM_Sub_EraseWritableChkReq();
        }
        else if( MEMM_ERASE_PHASE_GRNT_WRITECHK == MemM_JobInfo.ErasePhase )
        {
            MemM_Sub_EraseWritableCmpltChk();
        }
        else if( MEMM_ERASE_PHASE_GRNT_EXEC == MemM_JobInfo.ErasePhase )
        {
            MemM_Sub_EraseGrntCompleteChk();
        }
        else if( MEMM_ERASE_PHASE_ERASE_EXEC == MemM_JobInfo.ErasePhase )
        {
            MemM_Sub_EraseCompleteChk();
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASE, MEMM_E_CASE_PHASE_FAIL);
        }
    }
    else if( MEMM_ERASE_GRNTACT_NONE == MemM_Cfg_Data.GrntData[MemM_Cfg_Data.GrntMode].ReqEraseData.Action )
    {
        if( MEMM_ERASE_PHASE_READY == MemM_JobInfo.ErasePhase )
        {
            MemM_Sub_EraseReq();
        }
        else if( MEMM_ERASE_PHASE_ERASE_EXEC == MemM_JobInfo.ErasePhase )
        {
            MemM_Sub_EraseCompleteChk();
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASE, MEMM_E_CASE_PHASE_FAIL);
        }
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASE, MEMM_E_CASE_GRNTACTION_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_EraseWritableChkReq                               */
/* Description   | Request CodeFlsIf to check writable                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_EraseWritableChkReq (void)
{
    VAR(uint32, AUTOMATIC) TargetAddr;
    VAR(uint32, AUTOMATIC) Cnt;
    VAR(uint8, AUTOMATIC) AddrStoredIndex;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    if( MemM_MemoryAreaIndex == MemM_MemoryAreaIndexMirror )
    {
        AddrStoredIndex = MemM_Cfg_Data.GrntData[MemM_Cfg_Data.GrntMode].ReqEraseData.TargetArea;
        TargetAddr = MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].GrntAddr[AddrStoredIndex];

        for( Cnt = 0UL; Cnt < MEMM_GRNT_DATA_NUM; Cnt++ )
        {
            MemM_GrntAreaData[Cnt] = MemM_Cfg_Data.GrntData[MemM_Cfg_Data.GrntMode].ReqEraseData.WriteValue;
        }

        FuncRet = CodeFlsIf_WritableCheck(TargetAddr, (const uint8*)&MemM_GrntAreaData[0], MemM_Cfg_Data.GrntAreaSize);
        if( (Std_ReturnType)E_OK == FuncRet )
        {
            MemM_JobInfo.ErasePhase = MEMM_ERASE_PHASE_GRNT_WRITECHK;
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_ERASE_WRITABLEREQ, MEMM_E_CASE_APICALL_NG);
        }
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASE_WRITABLEREQ, MEMM_E_CASE_AREAINDEX_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_EraseWritableCmpltChk                             */
/* Description   | Wait for completion of the checking writable               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_EraseWritableCmpltChk (void)
{
    VAR(CodeFlsIf_StatusType, AUTOMATIC) CodeFlsIfState;
    VAR(CodeFlsIf_JobResultType, AUTOMATIC) CodeFlsIfJobResult;

    CodeFlsIfState = CodeFlsIf_GetStatus();
    if( CODEFLSIF_IDLE == CodeFlsIfState )
    {
        CodeFlsIfJobResult = CodeFlsIf_GetJobResult();
        if( CODEFLSIF_JOB_OK == CodeFlsIfJobResult )
        {
            MemM_Sub_EraseGrntReq();
        }
        else
        {
            /* In this case, Flash status was already updated */
            MemM_Sub_EraseReq();
        }
    }
    else if( CODEFLSIF_BUSY == CodeFlsIfState )
    {
        /* No process */
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASE_WRITABLECHK, MEMM_E_CASE_IFSTATUS_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_EraseGrntReq                                      */
/* Description   | Request CodeFlsIf to guarantee(guarantee means taking      */
/*               | measures for the case that a power supply is cut off in    */
/*               | reprogramming)                                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_EraseGrntReq (void)
{
    VAR(uint32, AUTOMATIC) TargetAddr;
    VAR(uint8, AUTOMATIC) AddrStoredIndex;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    if( MEMM_ERASE_GRNTACT_ERASE == MemM_Cfg_Data.GrntData[MemM_Cfg_Data.GrntMode].ReqEraseData.Action )
    {
        if( MemM_MemoryAreaIndex == MemM_MemoryAreaIndexMirror )
        {
            TargetAddr = MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].GrntAddr[MEMM_GRNT_AREA_1ST];
            FuncRet = CodeFlsIf_Erase(TargetAddr, MemM_Cfg_Data.GrntBlockSize);
            if( (Std_ReturnType)E_OK == FuncRet )
            {
                MemM_JobInfo.ErasePhase = MEMM_ERASE_PHASE_GRNT_EXEC;
            }
            else
            {
                MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_ERASE_GRNTREQ, MEMM_E_CASE_APICALL_NG);
            }
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASE_GRNTREQ, MEMM_E_CASE_AREAINDEX_FAIL);
        }
    }
    else if( MEMM_ERASE_GRNTACT_WRITE == MemM_Cfg_Data.GrntData[MemM_Cfg_Data.GrntMode].ReqEraseData.Action )
    {
        if( MemM_MemoryAreaIndex == MemM_MemoryAreaIndexMirror )
        {
            AddrStoredIndex = MemM_Cfg_Data.GrntData[MemM_Cfg_Data.GrntMode].ReqEraseData.TargetArea;
            TargetAddr = MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].GrntAddr[AddrStoredIndex];
            FuncRet = CodeFlsIf_WriteStart(TargetAddr, MemM_Cfg_Data.GrntAreaSize, MEMM_WRITE_GRNT_SKIP_NONE, NULL_PTR);
            if( (Std_ReturnType)E_OK == FuncRet )
            {
                /* Since the previous CodeFlsIf_WriteStart() was E_OK,                 */
                /* the following CodeFlsIf_WriteUpdate() call will not cause an error. */
                /* Therefore, the return value is not checked.                         */
                (void)CodeFlsIf_WriteUpdate((const uint8*)&MemM_GrntAreaData[0], MemM_Cfg_Data.GrntAreaSize);

                MemM_JobInfo.ErasePhase = MEMM_ERASE_PHASE_GRNT_EXEC;
            }
            else
            {
                MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_ERASE_GRNTREQ, MEMM_E_CASE_APICALL_NG);
            }
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASE_GRNTREQ, MEMM_E_CASE_AREAINDEX_FAIL);
        }
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASE_GRNTREQ, MEMM_E_CASE_GRNTACTION_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_EraseGrntCompleteChk                              */
/* Description   | Wait for completion of guarantee                           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_EraseGrntCompleteChk (void)
{
    VAR(CodeFlsIf_StatusType, AUTOMATIC) CodeFlsIfState;
    VAR(CodeFlsIf_JobResultType, AUTOMATIC) CodeFlsIfJobResult;

    if( MEMM_ERASE_GRNTACT_ERASE == MemM_Cfg_Data.GrntData[MemM_Cfg_Data.GrntMode].ReqEraseData.Action )
    {
        CodeFlsIfState = CodeFlsIf_GetStatus();
        if( CODEFLSIF_IDLE == CodeFlsIfState )
        {
            CodeFlsIfJobResult = CodeFlsIf_GetJobResult();
            if( CODEFLSIF_JOB_OK == CodeFlsIfJobResult )
            {
                MemM_Sub_EraseReq();
            }
            else
            {
                MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_ERASE_GRNTCHK, MEMM_E_CASE_IFRESULT_FAIL);
            }
        }
        else if( CODEFLSIF_BUSY == CodeFlsIfState )
        {
            /* No process */
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASE_GRNTCHK, MEMM_E_CASE_IFSTATUS_FAIL);
        }
    }
    else if( MEMM_ERASE_GRNTACT_WRITE == MemM_Cfg_Data.GrntData[MemM_Cfg_Data.GrntMode].ReqEraseData.Action )
    {
        CodeFlsIfState = CodeFlsIf_GetStatus();
        if( CODEFLSIF_UPDATECOMPLETE == CodeFlsIfState )
        {
            /* Since the previous CodeFlsIf_GetStatus() was CODEFLSIF_UPDATECOMPLETE, */
            /* the following CodeFlsIf_WriteFinish() call will not cause an error.    */
            /* Therefore, the return value is not checked.                            */
            (void)CodeFlsIf_WriteFinish();

            CodeFlsIfJobResult = CodeFlsIf_GetJobResult();
            if( CODEFLSIF_JOB_OK == CodeFlsIfJobResult )
            {
                MemM_Sub_EraseReq();
            }
            else
            {
                MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_ERASE_GRNTCHK, MEMM_E_CASE_IFRESULT_FAIL);
            }
        }
        else if( CODEFLSIF_UPDATEBUSY == CodeFlsIfState )
        {
            /* No process */
        }
        else if( CODEFLSIF_IDLE == CodeFlsIfState )
        {
            CodeFlsIfJobResult = CodeFlsIf_GetJobResult();
            if( CODEFLSIF_JOB_FAILED == CodeFlsIfJobResult )
            {
                MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_ERASE_GRNTCHK, MEMM_E_CASE_IFRESULT_FAIL);
            }
            else
            {
                MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASE_GRNTCHK, MEMM_E_CASE_IFRESULT_FAIL);
            }
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASE_GRNTCHK, MEMM_E_CASE_IFSTATUS_FAIL);
        }
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASE_GRNTCHK, MEMM_E_CASE_GRNTACTION_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_EraseReq                                          */
/* Description   | Request CodeFlsIf,ExtCodeFlsIf to erase                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_EraseReq (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    if( MemM_MemoryAreaIndex == MemM_MemoryAreaIndexMirror )
    {
        if( MEMM_DEVICE_TYPE_CODEFLS == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
        {
            if( (MemM_EraseData.Addr == MemM_EraseDataMirror.Addr) && (MemM_EraseData.Size == MemM_EraseDataMirror.Size) )
            {
                FuncRet = CodeFlsIf_Erase(MemM_EraseData.Addr, MemM_EraseData.Size);
                if( (Std_ReturnType)E_OK == FuncRet )
                {
                    MemM_JobInfo.ErasePhase = MEMM_ERASE_PHASE_ERASE_EXEC;
                }
                else
                {
                    MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_ERASEREQ, MEMM_E_CASE_APICALL_NG);
                }
            }
            else
            {
                MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASEREQ, MEMM_E_CASE_ERASEDATA_FAIL);
            }
        }
        else if( MEMM_DEVICE_TYPE_EXTCODEFLS == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
        {
            if( (MemM_EraseData.Addr == MemM_EraseDataMirror.Addr) && (MemM_EraseData.Size == MemM_EraseDataMirror.Size) )
            {
                FuncRet = ExtCodeFlsIf_Erase(MemM_EraseData.Addr, MemM_EraseData.Size);
                if( (Std_ReturnType)E_OK == FuncRet )
                {
                    MemM_JobInfo.ErasePhase = MEMM_ERASE_PHASE_ERASE_EXEC;
                }
                else
                {
                    MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_ERASEREQ, MEMM_E_CASE_APICALL_NG);
                }
            }
            else
            {
                MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASEREQ, MEMM_E_CASE_ERASEDATA_FAIL);
            }
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASEREQ, MEMM_E_CASE_DEVICETYPE_FAIL);
        }
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASEREQ, MEMM_E_CASE_AREAINDEX_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_EraseCompleteChk                                  */
/* Description   | Wait for completion of erasing                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_EraseCompleteChk (void)
{
    if( MemM_MemoryAreaIndex == MemM_MemoryAreaIndexMirror )
    {
        if( MEMM_DEVICE_TYPE_CODEFLS == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
        {
            MemM_Sub_EraseCompleteChkRom();
        }
        else if( MEMM_DEVICE_TYPE_EXTCODEFLS == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
        {
            MemM_Sub_EraseCompleteChkExtRom();
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASECHK, MEMM_E_CASE_DEVICETYPE_FAIL);
        }
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASECHK, MEMM_E_CASE_AREAINDEX_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_EraseCompleteChkRom                               */
/* Description   | Wait for completion of erasing[DeviceType:ROM]             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_EraseCompleteChkRom (void)
{
#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
    VAR(uint32, AUTOMATIC) Cnt;
#endif
    VAR(CodeFlsIf_StatusType, AUTOMATIC) CodeFlsIfState;
    VAR(CodeFlsIf_JobResultType, AUTOMATIC) CodeFlsIfJobResult;
    VAR(uint8, AUTOMATIC) MaskLevel;

    CodeFlsIfState = CodeFlsIf_GetStatus();
    if( CODEFLSIF_IDLE == CodeFlsIfState )
    {
        CodeFlsIfJobResult = CodeFlsIf_GetJobResult();
        if( CODEFLSIF_JOB_OK == CodeFlsIfJobResult )
        {
#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
            for( Cnt = 0UL; Cnt < MemM_Cfg_Data.MemoryAreaNum; Cnt++ )
            {
                if( MemM_JobInfo.ExecuteGrntTargetAreaInfo[Cnt] != MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo[Cnt] )
                {
                    break;
                }
            }

            if( MemM_Cfg_Data.MemoryAreaNum == Cnt )
#else
            if( MemM_JobInfo.ExecuteGrntTargetAreaInfo == MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo )
#endif
            {
                MaskLevel = MaskInterruptAll();

                MemM_JobInfo.JobResult = MEMM_JOB_OK;

#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
#if ( MEMM_CFG_NONERASE_GRNTAREA_USE == STD_ON )
                if( MEMM_INVALID_ADDR != MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].GrntAddr[MEMM_GRNT_AREA_1ST] )
                {
                    MemM_JobInfo.ExecuteGrntTargetAreaInfo[MemM_MemoryAreaIndex] = MEMM_EXECUTE_GRNT_TARGET_ON;
                    MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo[MemM_MemoryAreaIndex] = MemM_JobInfo.ExecuteGrntTargetAreaInfo[MemM_MemoryAreaIndex];
                }
#else
                MemM_JobInfo.ExecuteGrntTargetAreaInfo[MemM_MemoryAreaIndex] = MEMM_EXECUTE_GRNT_TARGET_ON;
                MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo[MemM_MemoryAreaIndex] = MemM_JobInfo.ExecuteGrntTargetAreaInfo[MemM_MemoryAreaIndex];
#endif
#else
#if ( MEMM_CFG_NONERASE_GRNTAREA_USE == STD_ON )
                if( MEMM_INVALID_ADDR != MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].GrntAddr[MEMM_GRNT_AREA_1ST] )
                {
                    MemM_JobInfo.ExecuteGrntTargetAreaInfo |= MEMM_EXECUTE_GRNT_TARGET_BITON << MemM_MemoryAreaIndex;
                    MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo = MemM_JobInfo.ExecuteGrntTargetAreaInfo;
                }
#else
                MemM_JobInfo.ExecuteGrntTargetAreaInfo |= MEMM_EXECUTE_GRNT_TARGET_BITON << MemM_MemoryAreaIndex;
                MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo = MemM_JobInfo.ExecuteGrntTargetAreaInfo;
#endif
#endif

                MemM_JobInfo.ErasePhase = MEMM_ERASE_PHASE_IDLE;
                MemM_JobInfo.ReqMode = MEMM_REQ_MODE_NONE;
                MemM_JobInfo.JobStatus = MEMM_IDLE;

                UnMaskInterruptAll(MaskLevel);
            }
            else
            {
                MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASECHK, MEMM_E_CASE_GRNTTARGETAREA_FAIL);
            }
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_ERASECHK, MEMM_E_CASE_IFRESULT_FAIL);
        }
    }
    else if( CODEFLSIF_BUSY == CodeFlsIfState )
    {
        /* No process */
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASECHK, MEMM_E_CASE_IFSTATUS_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_EraseCompleteChkExtRom                            */
/* Description   | Wait for completion of erasing[DeviceType:ExtROM]          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_EraseCompleteChkExtRom (void)
{
#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
    VAR(uint32, AUTOMATIC) Cnt;
#endif
    VAR(ExtCodeFlsIf_StatusType, AUTOMATIC) ExtCodeFlsIfState;
    VAR(ExtCodeFlsIf_JobResultType, AUTOMATIC) ExtCodeFlsIfJobResult;
    VAR(uint8, AUTOMATIC) MaskLevel;

    ExtCodeFlsIfState = ExtCodeFlsIf_GetStatus();
    if( EXTCODEFLSIF_IDLE == ExtCodeFlsIfState )
    {
        ExtCodeFlsIfJobResult = ExtCodeFlsIf_GetJobResult();
        if( EXTCODEFLSIF_JOB_OK == ExtCodeFlsIfJobResult )
        {
#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
            for( Cnt = 0UL; Cnt < MemM_Cfg_Data.MemoryAreaNum; Cnt++ )
            {
                if( MemM_JobInfo.ExecuteGrntTargetAreaInfo[Cnt] != MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo[Cnt] )
                {
                    break;
                }
            }

            if( MemM_Cfg_Data.MemoryAreaNum == Cnt )
#else
            if( MemM_JobInfo.ExecuteGrntTargetAreaInfo == MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo )
#endif
            {
                MaskLevel = MaskInterruptAll();

                MemM_JobInfo.JobResult = MEMM_JOB_OK;

#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
#if ( MEMM_CFG_NONERASE_GRNTAREA_USE == STD_ON )
                if( MEMM_INVALID_ADDR != MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].GrntAddr[MEMM_GRNT_AREA_1ST] )
                {
                    MemM_JobInfo.ExecuteGrntTargetAreaInfo[MemM_MemoryAreaIndex] = MEMM_EXECUTE_GRNT_TARGET_ON;
                    MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo[MemM_MemoryAreaIndex] = MemM_JobInfo.ExecuteGrntTargetAreaInfo[MemM_MemoryAreaIndex];
                }
#else
                MemM_JobInfo.ExecuteGrntTargetAreaInfo[MemM_MemoryAreaIndex] = MEMM_EXECUTE_GRNT_TARGET_ON;
                MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo[MemM_MemoryAreaIndex] = MemM_JobInfo.ExecuteGrntTargetAreaInfo[MemM_MemoryAreaIndex];
#endif
#else
#if ( MEMM_CFG_NONERASE_GRNTAREA_USE == STD_ON )
                if( MEMM_INVALID_ADDR != MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].GrntAddr[MEMM_GRNT_AREA_1ST] )
                {
                    MemM_JobInfo.ExecuteGrntTargetAreaInfo |= MEMM_EXECUTE_GRNT_TARGET_BITON << MemM_MemoryAreaIndex;
                    MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo = MemM_JobInfo.ExecuteGrntTargetAreaInfo;
                }
#else
                MemM_JobInfo.ExecuteGrntTargetAreaInfo |= MEMM_EXECUTE_GRNT_TARGET_BITON << MemM_MemoryAreaIndex;
                MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo = MemM_JobInfo.ExecuteGrntTargetAreaInfo;
#endif
#endif

                MemM_JobInfo.ErasePhase = MEMM_ERASE_PHASE_IDLE;
                MemM_JobInfo.ReqMode = MEMM_REQ_MODE_NONE;
                MemM_JobInfo.JobStatus = MEMM_IDLE;

                UnMaskInterruptAll(MaskLevel);
            }
            else
            {
                MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASECHK, MEMM_E_CASE_GRNTTARGETAREA_FAIL);
            }
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_ERASECHK, MEMM_E_CASE_IFRESULT_FAIL);
        }
    }
    else if( EXTCODEFLSIF_BUSY == ExtCodeFlsIfState )
    {
        /* No process */
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_ERASECHK, MEMM_E_CASE_IFSTATUS_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_Write                                             */
/* Description   | Distribute to subfunction in writing phase                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_Write (void)
{
    MemM_Sub_WriteCompleteChk();
}

/******************************************************************************/
/* Function Name | MemM_Sub_WriteCompleteChk                                  */
/* Description   | Wait for completion of writing                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_WriteCompleteChk (void)
{
    if( MemM_MemoryAreaIndex == MemM_MemoryAreaIndexMirror )
    {
        if( MEMM_DEVICE_TYPE_CODEFLS == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
        {
            MemM_Sub_WriteCompleteChkRom();
        }
        else if( MEMM_DEVICE_TYPE_EXTCODEFLS == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
        {
            MemM_Sub_WriteCompleteChkExtRom();
        }
        else if( MEMM_DEVICE_TYPE_CODERAM == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
        {
            MemM_Sub_WriteCompleteChkRam();
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_WRITE, MEMM_E_CASE_DEVICETYPE_FAIL);
        }
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_WRITE, MEMM_E_CASE_AREAINDEX_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_WriteCompleteChkRom                               */
/* Description   | Wait for completion of writing[DeviceType:ROM]             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_WriteCompleteChkRom (void)
{
    VAR(CodeFlsIf_StatusType, AUTOMATIC) CodeFlsIfState;
    VAR(CodeFlsIf_JobResultType, AUTOMATIC) CodeFlsIfJobResult;
    VAR(uint8, AUTOMATIC) MaskLevel;

    CodeFlsIfState = CodeFlsIf_GetStatus();
    if( CODEFLSIF_UPDATEIDLE == CodeFlsIfState )
    {
        CodeFlsIfJobResult = CodeFlsIf_GetJobResult();
        if( CODEFLSIF_JOB_OK == CodeFlsIfJobResult )
        {
            MaskLevel = MaskInterruptAll();

            MemM_JobInfo.JobResult = MEMM_JOB_OK;
            MemM_JobInfo.JobStatus = MEMM_UPDATEIDLE;

            UnMaskInterruptAll(MaskLevel);
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_WRITE, MEMM_E_CASE_IFRESULT_FAIL);
        }
    }
    else if( CODEFLSIF_UPDATECOMPLETE == CodeFlsIfState )
    {
        CodeFlsIfJobResult = CodeFlsIf_GetJobResult();
        if( CODEFLSIF_JOB_OK == CodeFlsIfJobResult )
        {
            MaskLevel = MaskInterruptAll();

            MemM_JobInfo.JobResult = MEMM_JOB_OK;
            MemM_JobInfo.JobStatus = MEMM_UPDATECOMPLETE;

            UnMaskInterruptAll(MaskLevel);
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_WRITE, MEMM_E_CASE_IFRESULT_FAIL);
        }
    }
    else if( CODEFLSIF_UPDATEBUSY == CodeFlsIfState )
    {
        /* No process */
    }
    else if( CODEFLSIF_IDLE == CodeFlsIfState )
    {
        CodeFlsIfJobResult = CodeFlsIf_GetJobResult();
        if( CODEFLSIF_JOB_FAILED == CodeFlsIfJobResult )
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_WRITE, MEMM_E_CASE_IFRESULT_FAIL);
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_WRITE, MEMM_E_CASE_IFRESULT_FAIL);
        }
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_WRITE, MEMM_E_CASE_IFSTATUS_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_WriteCompleteChkExtRom                            */
/* Description   | Wait for completion of writing[DeviceType:ExtROM]          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_WriteCompleteChkExtRom (void)
{
    VAR(ExtCodeFlsIf_StatusType, AUTOMATIC) ExtCodeFlsIfState;
    VAR(ExtCodeFlsIf_JobResultType, AUTOMATIC) ExtCodeFlsIfJobResult;
    VAR(uint8, AUTOMATIC) MaskLevel;

    ExtCodeFlsIfState = ExtCodeFlsIf_GetStatus();
    if( EXTCODEFLSIF_UPDATEIDLE == ExtCodeFlsIfState )
    {
        ExtCodeFlsIfJobResult = ExtCodeFlsIf_GetJobResult();
        if( EXTCODEFLSIF_JOB_OK == ExtCodeFlsIfJobResult )
        {
            MaskLevel = MaskInterruptAll();

            MemM_JobInfo.JobResult = MEMM_JOB_OK;
            MemM_JobInfo.JobStatus = MEMM_UPDATEIDLE;

            UnMaskInterruptAll(MaskLevel);
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_WRITE, MEMM_E_CASE_IFRESULT_FAIL);
        }
    }
    else if( EXTCODEFLSIF_UPDATECOMPLETE == ExtCodeFlsIfState )
    {
        ExtCodeFlsIfJobResult = ExtCodeFlsIf_GetJobResult();
        if( EXTCODEFLSIF_JOB_OK == ExtCodeFlsIfJobResult )
        {
            MaskLevel = MaskInterruptAll();

            MemM_JobInfo.JobResult = MEMM_JOB_OK;
            MemM_JobInfo.JobStatus = MEMM_UPDATECOMPLETE;

            UnMaskInterruptAll(MaskLevel);
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_WRITE, MEMM_E_CASE_IFRESULT_FAIL);
        }
    }
    else if( EXTCODEFLSIF_UPDATEBUSY == ExtCodeFlsIfState )
    {
        /* No process */
    }
    else if( EXTCODEFLSIF_IDLE == ExtCodeFlsIfState )
    {
        ExtCodeFlsIfJobResult = ExtCodeFlsIf_GetJobResult();
        if( EXTCODEFLSIF_JOB_FAILED == ExtCodeFlsIfJobResult )
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_WRITE, MEMM_E_CASE_IFRESULT_FAIL);
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_WRITE, MEMM_E_CASE_IFRESULT_FAIL);
        }
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_WRITE, MEMM_E_CASE_IFSTATUS_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_WriteCompleteChkRam                               */
/* Description   | Wait for completion of writing[DeviceType:RAM]             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_WriteCompleteChkRam (void)
{
    VAR(CodeRamIf_StatusType, AUTOMATIC) CodeRamIfState;
    VAR(CodeRamIf_JobResultType, AUTOMATIC) CodeRamIfJobResult;
    VAR(uint8, AUTOMATIC) MaskLevel;

    CodeRamIfState = CodeRamIf_GetStatus();
    if( CODERAMIF_UPDATEIDLE == CodeRamIfState )
    {
        CodeRamIfJobResult = CodeRamIf_GetJobResult();
        if( CODERAMIF_JOB_OK == CodeRamIfJobResult )
        {
            MaskLevel = MaskInterruptAll();

            MemM_JobInfo.JobResult = MEMM_JOB_OK;
            MemM_JobInfo.JobStatus = MEMM_UPDATEIDLE;

            UnMaskInterruptAll(MaskLevel);
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_WRITE, MEMM_E_CASE_IFRESULT_FAIL);
        }
    }
    else if( CODERAMIF_UPDATECOMPLETE == CodeRamIfState )
    {
        CodeRamIfJobResult = CodeRamIf_GetJobResult();
        if( CODERAMIF_JOB_OK == CodeRamIfJobResult )
        {
            MaskLevel = MaskInterruptAll();

            MemM_JobInfo.JobResult = MEMM_JOB_OK;
            MemM_JobInfo.JobStatus = MEMM_UPDATECOMPLETE;

            UnMaskInterruptAll(MaskLevel);
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_WRITE, MEMM_E_CASE_IFRESULT_FAIL);
        }
    }
    else if( CODERAMIF_UPDATEBUSY == CodeRamIfState )
    {
        /* No process */
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_WRITE, MEMM_E_CASE_IFSTATUS_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_Read                                              */
/* Description   | Distribute to subfunction in reading phase                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_Read (void)
{
    MemM_Sub_ReadCompleteChk();
}

/******************************************************************************/
/* Function Name | MemM_Sub_ReadCompleteChk                                   */
/* Description   | Wait for completion of reading                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_ReadCompleteChk (void)
{
    if( MemM_MemoryAreaIndex == MemM_MemoryAreaIndexMirror )
    {
        if( MEMM_DEVICE_TYPE_CODEFLS == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
        {
            MemM_Sub_ReadCompleteChkRom();
        }
        else if( MEMM_DEVICE_TYPE_EXTCODEFLS == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
        {
            MemM_Sub_ReadCompleteChkExtRom();
        }
        else if( MEMM_DEVICE_TYPE_CODERAM == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
        {
            MemM_Sub_ReadCompleteChkRam();
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_READ, MEMM_E_CASE_DEVICETYPE_FAIL);
        }
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_READ, MEMM_E_CASE_AREAINDEX_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_ReadCompleteChkRom                                */
/* Description   | Wait for completion of reading[DeviceType:ROM]             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_ReadCompleteChkRom (void)
{
    VAR(CodeFlsIf_StatusType, AUTOMATIC) CodeFlsIfState;
    VAR(CodeFlsIf_JobResultType, AUTOMATIC) CodeFlsIfJobResult;
    VAR(uint8, AUTOMATIC) MaskLevel;

    CodeFlsIfState = CodeFlsIf_GetStatus();
    if( CODEFLSIF_IDLE == CodeFlsIfState )
    {
        CodeFlsIfJobResult = CodeFlsIf_GetJobResult();
        if( CODEFLSIF_JOB_OK == CodeFlsIfJobResult )
        {
            MaskLevel = MaskInterruptAll();

            MemM_JobInfo.JobResult = MEMM_JOB_OK;
            MemM_JobInfo.ReqMode = MEMM_REQ_MODE_NONE;
            MemM_JobInfo.JobStatus = MEMM_IDLE;

            UnMaskInterruptAll(MaskLevel);
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_READ, MEMM_E_CASE_IFRESULT_FAIL);
        }
    }
    else if( CODEFLSIF_BUSY == CodeFlsIfState )
    {
        /* No process */
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_READ, MEMM_E_CASE_IFSTATUS_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_ReadCompleteChkExtRom                             */
/* Description   | Wait for completion of reading[DeviceType:ExtROM]          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_ReadCompleteChkExtRom (void)
{
    VAR(ExtCodeFlsIf_StatusType, AUTOMATIC) ExtCodeFlsIfState;
    VAR(ExtCodeFlsIf_JobResultType, AUTOMATIC) ExtCodeFlsIfJobResult;
    VAR(uint8, AUTOMATIC) MaskLevel;

    ExtCodeFlsIfState = ExtCodeFlsIf_GetStatus();
    if( EXTCODEFLSIF_IDLE == ExtCodeFlsIfState )
    {
        ExtCodeFlsIfJobResult = ExtCodeFlsIf_GetJobResult();
        if( EXTCODEFLSIF_JOB_OK == ExtCodeFlsIfJobResult )
        {
            MaskLevel = MaskInterruptAll();

            MemM_JobInfo.JobResult = MEMM_JOB_OK;
            MemM_JobInfo.ReqMode = MEMM_REQ_MODE_NONE;
            MemM_JobInfo.JobStatus = MEMM_IDLE;

            UnMaskInterruptAll(MaskLevel);
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_READ, MEMM_E_CASE_IFRESULT_FAIL);
        }
    }
    else if( EXTCODEFLSIF_BUSY == ExtCodeFlsIfState )
    {
        /* No process */
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_READ, MEMM_E_CASE_IFSTATUS_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_ReadCompleteChkRam                                */
/* Description   | Wait for completion of reading[DeviceType:RAM]             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_ReadCompleteChkRam (void)
{
    VAR(CodeRamIf_StatusType, AUTOMATIC) CodeRamIfState;
    VAR(CodeRamIf_JobResultType, AUTOMATIC) CodeRamIfJobResult;
    VAR(uint8, AUTOMATIC) MaskLevel;

    CodeRamIfState = CodeRamIf_GetStatus();
    if( CODERAMIF_IDLE == CodeRamIfState )
    {
        CodeRamIfJobResult = CodeRamIf_GetJobResult();
        if( CODERAMIF_JOB_OK == CodeRamIfJobResult )
        {
            MaskLevel = MaskInterruptAll();

            MemM_JobInfo.JobResult = MEMM_JOB_OK;
            MemM_JobInfo.ReqMode = MEMM_REQ_MODE_NONE;
            MemM_JobInfo.JobStatus = MEMM_IDLE;

            UnMaskInterruptAll(MaskLevel);
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_READ, MEMM_E_CASE_IFRESULT_FAIL);
        }
    }
    else if( CODERAMIF_BUSY == CodeRamIfState )
    {
        /* No process */
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_READ, MEMM_E_CASE_IFSTATUS_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_RpgCmplt                                          */
/* Description   | Distribute to subfunction in reprogramming complete phase  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_RpgCmplt (void)
{
    if( MEMM_RPGCMPLT_PHASE_WRITE_READY == MemM_JobInfo.ReprogCompletePhase )
    {
        MemM_Sub_RpgCmpltWriteReq();
    }
    else if( MEMM_RPGCMPLT_PHASE_WRITE_EXEC == MemM_JobInfo.ReprogCompletePhase )
    {
        MemM_Sub_RpgCmpltWriteCmpltChk();
    }
    else if( MEMM_RPGCMPLT_PHASE_READ_EXEC == MemM_JobInfo.ReprogCompletePhase )
    {
        MemM_Sub_RpgCmpltReadCmpltChk();
    }
    else if( MEMM_RPGCMPLT_PHASE_SWITCH_EXEC == MemM_JobInfo.ReprogCompletePhase )
    {
        MemM_Sub_RpgCmpltSwitchCmpltChk();
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_RPGCMPLT, MEMM_E_CASE_PHASE_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_RpgCmpltWriteReq                                  */
/* Description   | Request CodeFlsIf to start writing for reprogramming       */
/*               | completion                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_RpgCmpltWriteReq (void)
{
    VAR(uint32, AUTOMATIC) Cnt;
    VAR(uint32, AUTOMATIC) TargetAddr;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    for( Cnt = 0UL; Cnt < MEMM_GRNT_DATA_NUM; Cnt++ )
    {
        MemM_GrntAreaData[Cnt] = MemM_Cfg_Data.GrntData[MemM_Cfg_Data.GrntMode].ReqRpgCompleteData.WriteValue;
    }

    if( MemM_MemoryAreaIndex == MemM_MemoryAreaIndexMirror )
    {
        TargetAddr = MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].GrntAddr[MEMM_GRNT_AREA_1ST];
        FuncRet = CodeFlsIf_WriteStart(TargetAddr, MemM_Cfg_Data.GrntAreaSize, MEMM_WRITE_GRNT_SKIP_NONE, NULL_PTR);
        if( (Std_ReturnType)E_OK == FuncRet )
        {
            /* Since the previous CodeFlsIf_WriteStart() was E_OK,                 */
            /* the following CodeFlsIf_WriteUpdate() call will not cause an error. */
            /* Therefore, the return value is not checked.                         */
            (void)CodeFlsIf_WriteUpdate((const uint8*)&MemM_GrntAreaData[0], MemM_Cfg_Data.GrntAreaSize);

            MemM_JobInfo.ReprogCompletePhase = MEMM_RPGCMPLT_PHASE_WRITE_EXEC;
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_RPGCMPLT_WRITEREQ, MEMM_E_CASE_APICALL_NG);
        }
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_RPGCMPLT_WRITEREQ, MEMM_E_CASE_AREAINDEX_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_RpgCmpltWriteCmpltChk                             */
/* Description   | Wait for completion of writing for reprogramming           */
/*               | completion                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_RpgCmpltWriteCmpltChk (void)
{
    VAR(uint32, AUTOMATIC) TargetAddr;
    VAR(CodeFlsIf_StatusType, AUTOMATIC) CodeFlsIfState;
    VAR(CodeFlsIf_JobResultType, AUTOMATIC) CodeFlsIfJobResult;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    CodeFlsIfState = CodeFlsIf_GetStatus();
    if( CODEFLSIF_UPDATECOMPLETE == CodeFlsIfState )
    {
        /* Since the previous CodeFlsIf_GetStatus() was CODEFLSIF_UPDATECOMPLETE, */
        /* the following CodeFlsIf_WriteFinish() call will not cause an error.    */
        /* Therefore, the return value is not checked.                            */
        (void)CodeFlsIf_WriteFinish();

        CodeFlsIfJobResult = CodeFlsIf_GetJobResult();
        if( CODEFLSIF_JOB_OK == CodeFlsIfJobResult )
        {
            Rpg_MemSet((uint8*)&MemM_GrntAreaData[0], 0U, MEMM_CFG_GRNT_AREA_SIZE);

            MemErrM_ClearErrorInfo();

            if( MemM_MemoryAreaIndex == MemM_MemoryAreaIndexMirror )
            {
                TargetAddr = MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].GrntAddr[MEMM_GRNT_AREA_1ST];
                FuncRet = CodeFlsIf_Read(TargetAddr, (uint8*)&MemM_GrntAreaData[0], MEMM_CFG_GRNT_AREA_SIZE);
                if( (Std_ReturnType)E_OK == FuncRet )
                {
                    MemM_JobInfo.ReprogCompletePhase = MEMM_RPGCMPLT_PHASE_READ_EXEC;
                }
                else
                {
                    MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_RPGCMPLT_WRITECHK, MEMM_E_CASE_APICALL_NG);
                }
            }
            else
            {
                MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_RPGCMPLT_WRITECHK, MEMM_E_CASE_AREAINDEX_FAIL);
            }
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_RPGCMPLT_WRITECHK, MEMM_E_CASE_IFRESULT_FAIL);
        }
    }
    else if( CODEFLSIF_UPDATEBUSY == CodeFlsIfState )
    {
        /* No process */
    }
    else if( CODEFLSIF_IDLE == CodeFlsIfState )
    {
        CodeFlsIfJobResult = CodeFlsIf_GetJobResult();
        if( CODEFLSIF_JOB_FAILED == CodeFlsIfJobResult )
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_RPGCMPLT_WRITECHK, MEMM_E_CASE_IFRESULT_FAIL);
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_RPGCMPLT_WRITECHK, MEMM_E_CASE_IFRESULT_FAIL);
        }
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_RPGCMPLT_WRITECHK, MEMM_E_CASE_IFSTATUS_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_RpgCmpltReadCmpltChk                              */
/* Description   | Check whether reprogramming was completed certainly        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_RpgCmpltReadCmpltChk (void)
{
    VAR(uint32, AUTOMATIC) Cnt;
#if ( MEMM_CFG_EXPAND_AREANUM_USE != STD_ON )
    VAR(uint32, AUTOMATIC) Checkbit;
#endif
    VAR(uint32, AUTOMATIC) ExpectedGrantValue;
    VAR(CodeFlsIf_StatusType, AUTOMATIC) CodeFlsIfState;
    VAR(CodeFlsIf_JobResultType, AUTOMATIC) CodeFlsIfJobResult;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(Std_ReturnType, AUTOMATIC) VerifyResult;
    VAR(uint8, AUTOMATIC) MaskLevel;

    CodeFlsIfState = CodeFlsIf_GetStatus();
    if( CODEFLSIF_IDLE == CodeFlsIfState )
    {
        VerifyResult = E_NOT_OK;

        CodeFlsIfJobResult = CodeFlsIf_GetJobResult();
        if( CODEFLSIF_JOB_OK == CodeFlsIfJobResult )
        {
            FuncRet = MemErrM_CheckErrorInfo();
            if( (Std_ReturnType)E_OK == FuncRet )
            {
                ExpectedGrantValue = MemM_Cfg_Data.GrntData[MemM_Cfg_Data.GrntMode].ReqRpgCompleteData.WriteValue;
                for( Cnt = 0UL; Cnt < MEMM_GRNT_DATA_NUM; Cnt++ )
                {
                    if( ExpectedGrantValue != MemM_GrntAreaData[Cnt] )
                    {
                        break;
                    }
                }

                /* Keyword Stamp or Flash Status is written appropriately */
                if( MEMM_GRNT_DATA_NUM == Cnt )
                {
                    VerifyResult = E_OK;
                }
                else
                {
                    MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_RPGCOMPLETE_READCHK, MEMM_E_CASE_VERIFY_NG);
                }
            }
            else
            {
                MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_RPGCOMPLETE_READCHK, MEMM_E_CASE_VERIFY_NG);
            }
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_RPGCOMPLETE_READCHK, MEMM_E_CASE_IFRESULT_FAIL);
        }

        if( (Std_ReturnType)E_OK == VerifyResult )
        {
            if( MEMM_GRNT_MODE_KEYWORDSTAMP == MemM_Cfg_Data.GrntMode )
            {
#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
                for( Cnt = 0UL; Cnt < MemM_Cfg_Data.MemoryAreaNum; Cnt++ )
                {
                    MemM_JobInfo.ExecuteGrntTargetAreaInfo[Cnt] = MEMM_EXECUTE_GRNT_TARGET_NONE;
                    MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo[Cnt] = MemM_JobInfo.ExecuteGrntTargetAreaInfo[Cnt];
                }
#else
                MemM_JobInfo.ExecuteGrntTargetAreaInfo = MEMM_EXECUTE_GRNT_TARGET_NONE;
                MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo = MemM_JobInfo.ExecuteGrntTargetAreaInfo;
#endif

                if( ReprogOpt_DoubleMapConfig == (uint8)REPROGOPT_DOUBLEMAP_REWRITE_INVALID )
                {
                    CodeFlsIf_SwitchValidArea();
                    MemM_JobInfo.ReprogCompletePhase = MEMM_RPGCMPLT_PHASE_SWITCH_EXEC;
                }
                else
                {
                    MaskLevel = MaskInterruptAll();

                    MemM_JobInfo.JobResult = MEMM_JOB_OK;
                    MemM_JobInfo.ReprogCompletePhase = MEMM_RPGCMPLT_PHASE_IDLE;
                    MemM_JobInfo.ReqMode = MEMM_REQ_MODE_NONE;
                    MemM_JobInfo.JobStatus = MEMM_IDLE;

                    UnMaskInterruptAll(MaskLevel);
                }
            }
            else
            {
#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
                for( Cnt = 0UL; Cnt < MemM_Cfg_Data.MemoryAreaNum; Cnt++ )
                {
                    if( MemM_JobInfo.ExecuteGrntTargetAreaInfo[Cnt] != MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo[Cnt] )
                    {
                        break;
                    }
                }

                if( MemM_Cfg_Data.MemoryAreaNum == Cnt)
#else
                if( MemM_JobInfo.ExecuteGrntTargetAreaInfo == MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo )
#endif
                {
                    if( MemM_MemoryAreaIndex == MemM_MemoryAreaIndexMirror )
                    {
#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
                        MemM_JobInfo.ExecuteGrntTargetAreaInfo[MemM_MemoryAreaIndex] = MEMM_EXECUTE_GRNT_TARGET_NONE;
                        MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo[MemM_MemoryAreaIndex] = MemM_JobInfo.ExecuteGrntTargetAreaInfo[MemM_MemoryAreaIndex];
#else
                        MemM_JobInfo.ExecuteGrntTargetAreaInfo &=
                            ~(MEMM_EXECUTE_GRNT_TARGET_BITON << MemM_MemoryAreaIndex);
                        MemM_JobInfoMirror.ExecuteGrntTargetAreaInfo = MemM_JobInfo.ExecuteGrntTargetAreaInfo;
#endif

                        for( Cnt = 0UL; Cnt < MemM_Cfg_Data.MemoryAreaNum; Cnt++ )
                        {
#if ( MEMM_CFG_EXPAND_AREANUM_USE == STD_ON )
                            if( MEMM_EXECUTE_GRNT_TARGET_ON == MemM_JobInfo.ExecuteGrntTargetAreaInfo[Cnt] )
#else
                            Checkbit = MemM_JobInfo.ExecuteGrntTargetAreaInfo >> Cnt;
                            Checkbit &= MEMM_EXECUTE_GRNT_TARGET_BITON;
                            if( MEMM_EXECUTE_GRNT_TARGET_BITON == Checkbit )
#endif
                            {
                                break;
                            }
                        }

                        if( MemM_Cfg_Data.MemoryAreaNum > Cnt)
                        {
                            MemM_MemoryAreaIndex = (uint8)Cnt;
                            MemM_MemoryAreaIndexMirror = MemM_MemoryAreaIndex;

                            MemM_JobInfo.ReprogCompletePhase = MEMM_RPGCMPLT_PHASE_WRITE_READY;
                        }
                        else
                        {
                            if( ReprogOpt_DoubleMapConfig == (uint8)REPROGOPT_DOUBLEMAP_REWRITE_INVALID )
                            {
                                CodeFlsIf_SwitchValidArea();
                                MemM_JobInfo.ReprogCompletePhase = MEMM_RPGCMPLT_PHASE_SWITCH_EXEC;
                            }
                            else
                            {
                                MaskLevel = MaskInterruptAll();

                                MemM_JobInfo.JobResult = MEMM_JOB_OK;
                                MemM_JobInfo.ReprogCompletePhase = MEMM_RPGCMPLT_PHASE_IDLE;
                                MemM_JobInfo.ReqMode = MEMM_REQ_MODE_NONE;
                                MemM_JobInfo.JobStatus = MEMM_IDLE;

                                UnMaskInterruptAll(MaskLevel);
                            }
                        }
                    }
                    else
                    {
                        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_RPGCOMPLETE_READCHK, MEMM_E_CASE_AREAINDEX_FAIL);
                    }
                }
                else
                {
                    MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_RPGCOMPLETE_READCHK, MEMM_E_CASE_GRNTTARGETAREA_FAIL);
                }
            }
        }
    }
    else if( CODEFLSIF_BUSY == CodeFlsIfState )
    {
        /* No process */
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_RPGCOMPLETE_READCHK, MEMM_E_CASE_IFSTATUS_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_RpgCmpltSwitchCmpltChk                            */
/* Description   | Check whether switching valid area was completed certainly */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_RpgCmpltSwitchCmpltChk (void)
{
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(CodeFlsIf_StatusType, AUTOMATIC) CodeFlsIfState;
    VAR(CodeFlsIf_JobResultType, AUTOMATIC) CodeFlsIfJobResult;

    CodeFlsIfState = CodeFlsIf_GetStatus();
    if( CODEFLSIF_IDLE == CodeFlsIfState )
    {
        CodeFlsIfJobResult = CodeFlsIf_GetJobResult();
        if( CODEFLSIF_JOB_OK == CodeFlsIfJobResult )
        {
            MaskLevel = MaskInterruptAll();

            MemM_JobInfo.JobResult = MEMM_JOB_OK;
            MemM_JobInfo.ReprogCompletePhase = MEMM_RPGCMPLT_PHASE_IDLE;
            MemM_JobInfo.ReqMode = MEMM_REQ_MODE_NONE;
            MemM_JobInfo.JobStatus = MEMM_IDLE;

            UnMaskInterruptAll(MaskLevel);
        }
        else
        {
            MemM_Sub_Fail(MEMM_ERROR_NOT_REPORT, MEMM_E_API_ID_RPGCOMPLETE_SWITCHCHK, MEMM_E_CASE_IFRESULT_FAIL);
        }
    }
    else if( CODEFLSIF_BUSY == CodeFlsIfState )
    {
        /* No process */
    }
    else
    {
        MemM_Sub_Fail(MEMM_ERROR_REPORT, MEMM_E_API_ID_RPGCOMPLETE_SWITCHCHK, MEMM_E_CASE_IFSTATUS_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | MemM_Sub_CheckArea                                         */
/* Description   | Check whether the information of target area is correct    */
/* Preconditions |                                                            */
/* Parameters    | [INOUT] CheckAreaData : Information of target area         */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, MEMM_CODE_FAST) MemM_Sub_CheckArea
(
    P2VAR(MemM_MemoryAreaChkType, AUTOMATIC, MEMM_APPL_DATA) CheckAreaData
)
{
    VAR(uint32, AUTOMATIC) Cnt;
    VAR(uint32, AUTOMATIC) PermittedStartAddr;
    VAR(uint32, AUTOMATIC) PermittedEndAddr;
    VAR(uint32, AUTOMATIC) AddrOffset;
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_NOT_OK;

    for( Cnt = 0UL; Cnt < MemM_Cfg_Data.MemoryAreaNum; Cnt++ )
    {
        if( MemM_Cfg_Data.MemoryAreaData[Cnt].MemoryId == CheckAreaData->MemoryId )
        {
            PermittedStartAddr = MemM_Cfg_Data.MemoryAreaData[Cnt].VirtualAddr;
            PermittedEndAddr = PermittedStartAddr + (MemM_Cfg_Data.MemoryAreaData[Cnt].Size - MEMM_ADJUST_ENDADDR); /* no wrap around */

            /* Check whether target start address is correct */
            if( (PermittedStartAddr <= CheckAreaData->VirtualAddr) && (CheckAreaData->VirtualAddr <= PermittedEndAddr) )
            {
                /* Check whether target size is correct */
                if( (0UL < CheckAreaData->Size) && (CheckAreaData->Size <=
                        ((PermittedEndAddr + MEMM_ADJUST_ENDADDR) - CheckAreaData->VirtualAddr)) )                  /* no wrap around */
                {
                    AddrOffset = CheckAreaData->VirtualAddr - MemM_Cfg_Data.MemoryAreaData[Cnt].VirtualAddr;        /* no wrap around */
                    CheckAreaData->PhysicalAddr = MemM_Cfg_Data.MemoryAreaData[Cnt].PhysicalAddr + AddrOffset;      /* no wrap around */
                    CheckAreaData->AreaIndex = (uint8)Cnt;
                    Result = E_OK;
                    break;
                }
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | MemM_Sub_ChangeStatus                                      */
/* Description   | Change JobStatus                                           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, MEMM_CODE_FAST) MemM_Sub_ChangeStatus (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(uint8, AUTOMATIC) MaskLevel;

    Result = E_NOT_OK;

    MaskLevel = MaskInterruptAll();

    if( MEMM_IDLE == MemM_JobInfo.JobStatus )
    {
        MemM_JobInfo.JobStatus = MEMM_BUSY;

        Result = E_OK;
    }

    UnMaskInterruptAll(MaskLevel);

    return Result;
}

/******************************************************************************/
/* Function Name | MemM_Sub_CheckTimeOut                                      */
/* Description   | Check whether timeout occurred                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, MEMM_CODE_FAST) MemM_Sub_CheckTimeOut (void)
{
    VAR(uint32, AUTOMATIC) TimeLimit;
    VAR(uint32, AUTOMATIC) TimeSpan;
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Result = E_NOT_OK;

    TimeLimit = 0UL;
    FuncRet = MemM_Sub_GetTimeOutValue(&TimeLimit);
    if( (Std_ReturnType)E_OK == FuncRet )
    {
        TimeSpan = 0UL;
        FuncRet = Tm_GetTimeSpan1us32bit((const Tm_PredefTimer1us32bitType*)&MemM_TimerInstance, &TimeSpan);
        if( (Std_ReturnType)E_OK == FuncRet )
        {
            if( TimeLimit >= TimeSpan )
            {
                Result = E_OK;
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | MemM_Sub_GetTimeOutValue                                   */
/* Description   | Get TimeoutValue                                           */
/* Preconditions |                                                            */
/* Parameters    | [OUT] TimeOutValue                                         */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, MEMM_CODE_FAST) MemM_Sub_GetTimeOutValue
(
    P2VAR(uint32, AUTOMATIC, MEMM_APPL_DATA) TimeOutValue
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_NOT_OK;

    if( MEMM_REQ_MODE_ERASE == MemM_JobInfo.ReqMode )
    {
        if( MemM_MemoryAreaIndex == MemM_MemoryAreaIndexMirror )
        {
            if( MEMM_DEVICE_TYPE_CODEFLS == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
            {
                *TimeOutValue = MemM_Cfg_Data.TimerData->EraseTimerData.TimeOutValueCodeFls;
                Result = E_OK;
            }
            else if( MEMM_DEVICE_TYPE_EXTCODEFLS == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
            {
                *TimeOutValue = MemM_Cfg_Data.TimerData->EraseTimerData.TimeOutValueExtCodeFls;
                Result = E_OK;
            }
            else
            {
                /* No process. As MemM_MainFunction call MemM_Sub_Fail, this function does not call MemM_Sub_Fail */
            }
        }
        else
        {
            /* No process. As MemM_MainFunction call MemM_Sub_Fail, this function does not call MemM_Sub_Fail */
        }
    }
    else if( MEMM_REQ_MODE_WRITE == MemM_JobInfo.ReqMode )
    {
        if( MemM_MemoryAreaIndex == MemM_MemoryAreaIndexMirror )
        {
            if( MEMM_DEVICE_TYPE_CODEFLS == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice)
            {
                *TimeOutValue = MemM_Cfg_Data.TimerData->WriteTimerData.TimeOutValueCodeFls;
                Result = E_OK;
            }
            else if( MEMM_DEVICE_TYPE_EXTCODEFLS == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
            {
                *TimeOutValue = MemM_Cfg_Data.TimerData->WriteTimerData.TimeOutValueExtCodeFls;
                Result = E_OK;
            }
            else if( MEMM_DEVICE_TYPE_CODERAM == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
            {
                *TimeOutValue = MemM_Cfg_Data.TimerData->WriteTimerData.TimeOutValueCodeRam;
                Result = E_OK;
            }
            else
            {
                /* No process. As MemM_MainFunction call MemM_Sub_Fail, this function does not call MemM_Sub_Fail */
            }
        }
        else
        {
            /* No process. As MemM_MainFunction call MemM_Sub_Fail, this function does not call MemM_Sub_Fail */
        }
    }
    else if( MEMM_REQ_MODE_READ == MemM_JobInfo.ReqMode )
    {
        if( MemM_MemoryAreaIndex == MemM_MemoryAreaIndexMirror )
        {
            if( MEMM_DEVICE_TYPE_CODEFLS == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice)
            {
                *TimeOutValue = MemM_Cfg_Data.TimerData->ReadTimerData.TimeOutValueCodeFls;
                Result = E_OK;
            }
            else if( MEMM_DEVICE_TYPE_EXTCODEFLS == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
            {
                *TimeOutValue = MemM_Cfg_Data.TimerData->ReadTimerData.TimeOutValueExtCodeFls;
                Result = E_OK;
            }
            else if( MEMM_DEVICE_TYPE_CODERAM == MemM_Cfg_Data.MemoryAreaData[MemM_MemoryAreaIndex].TargetDevice )
            {
                *TimeOutValue = MemM_Cfg_Data.TimerData->ReadTimerData.TimeOutValueCodeRam;
                Result = E_OK;
            }
            else
            {
                /* No process. As MemM_MainFunction call MemM_Sub_Fail, this function does not call MemM_Sub_Fail */
            }
        }
        else
        {
            /* No process. As MemM_MainFunction call MemM_Sub_Fail, this function does not call MemM_Sub_Fail */
        }
    }
    else if( MEMM_REQ_MODE_RPGCOMPLETE == MemM_JobInfo.ReqMode )
    {
        *TimeOutValue = MemM_Cfg_Data.TimerData->RpgCmpltTimerData.TimeOutValue;
        Result = E_OK;
    }
    else
    {
        /* No process. As MemM_MainFunction call MemM_Sub_Fail, this function does not call MemM_Sub_Fail */
    }

    return Result;
}

/******************************************************************************/
/* Function Name | MemM_Sub_Fail                                              */
/* Description   | Set the information to failed and notify EcuM of the error */
/*               | information                                                */
/* Preconditions |                                                            */
/* Parameters    | [IN] ReportReq                                             */
/*               |       MEMM_ERROR_REPORT     : Call EcuM_ReportError        */
/*               |       MEMM_ERROR_NOT_REPORT : Do not call EcuM_ReportError */
/*               | [IN] ApiId   : API ID                                      */
/*               | [IN] ErrorId : Error ID                                    */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, MEMM_CODE_FAST) MemM_Sub_Fail
(
    VAR(uint8, AUTOMATIC) ReportReq,
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
)
{
    VAR(EcuM_ErrorType, AUTOMATIC) ErrorInfo;
    VAR(uint8, AUTOMATIC) MaskLevel;

    MaskLevel = MaskInterruptAll();

    MemM_JobInfo.JobResult = MEMM_JOB_FAILED;
    MemM_JobInfo.ErasePhase = MEMM_ERASE_PHASE_IDLE;
    MemM_JobInfo.ReprogCompletePhase = MEMM_RPGCMPLT_PHASE_IDLE;
    MemM_JobInfo.ReqMode = MEMM_REQ_MODE_NONE;
    MemM_JobInfo.JobStatus = MEMM_IDLE;

    UnMaskInterruptAll(MaskLevel);

    if( MEMM_ERROR_REPORT == ReportReq )
    {
        ErrorInfo.ModuleId = ECUM_MODULE_MEMM;
        ErrorInfo.ApiId = ApiId;
        ErrorInfo.ErrorId = ErrorId;
        EcuM_ReportError(&ErrorInfo);
    }

    return;
}

#define MEMM_STOP_SEC_CODE
#include <MemM_MemMap.h>


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

