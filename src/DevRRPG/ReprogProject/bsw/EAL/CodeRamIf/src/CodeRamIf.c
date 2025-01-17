/* CodeRamIf_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | CodeRamIf/CODE                                              */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <CodeRamIf.h>
#include "CodeRamIf_Local.h"
#include "CodeRamIf_Cfg.h"

#include <Sys.h>
#include <EcuM.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define CODERAMIF_ERROR_NOT_REPORT      (0x00U)
#define CODERAMIF_ERROR_REPORT          ((uint8)0x01U)

#define CODERAMIF_E_API_ID_INIT         (0x00U)

#define CODERAMIF_E_CASE_STATUS_FAIL    (0x80U)

#define CODERAMIF_LOCAL_UNINIT          ((uint8)0x00U)
#define CODERAMIF_LOCAL_IDLE            ((uint8)0x01U)
#define CODERAMIF_LOCAL_READY           ((uint8)0x02U)
#define CODERAMIF_LOCAL_BUSY            ((uint8)0x03U)
#define CODERAMIF_LOCAL_UPDATEIDLE      ((uint8)0x04U)
#define CODERAMIF_LOCAL_UPDATEREADY     ((uint8)0x05U)
#define CODERAMIF_LOCAL_UPDATEWRITING   ((uint8)0x06U)
#define CODERAMIF_LOCAL_UPDATECOMPLETE  ((uint8)0x07U)

#define CODERAMIF_INVALID_ADDR          (0xFFFFFFFFUL)
#define CODERAMIF_INVALID_SIZE          (0UL)

#define CODERAMIF_ADJUST_ENDADDR        (1UL)

#define CODERAMIF_GET_STATUS_TBL_NUM    ((uint8)8U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint8 LocalStatus;
    CodeRamIf_JobResultType JobResult;
} CodeRamIf_JobInfoType;

typedef struct {
    uint32 DestAddr;
    P2CONST(uint8, TYPEDEF, CODERAMIF_APPL_CONST) SrcAddr;
    uint32 TotalSize;
    uint32 UpdateSize;
} CodeRamIf_WriteDataType;

typedef struct {
    P2VAR(uint8, TYPEDEF, CODERAMIF_APPL_DATA) DestAddr;
    uint32 SrcAddr;
    uint32 Size;
} CodeRamIf_ReadDataType;

typedef struct {
    uint8 LocalStatus;
    CodeRamIf_StatusType JobStatus;
} CodeRamIf_GetStatusInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, CODERAMIF_CODE_FAST) CodeRamIf_Sub_Write (void);
static FUNC(void, CODERAMIF_CODE_FAST) CodeRamIf_Sub_Read (void);
static FUNC(void, CODERAMIF_CODE_FAST) CodeRamIf_Sub_Fail
(
    VAR(uint8, AUTOMATIC) ReportReq,
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define CODERAMIF_START_SEC_VAR
#include <CodeRamIf_MemMap.h>

static VAR(CodeRamIf_JobInfoType, CODERAMIF_VAR_CLEARED) CodeRamIf_JobInfo;
static VAR(CodeRamIf_WriteDataType, CODERAMIF_VAR_CLEARED) CodeRamIf_WriteData;
static VAR(CodeRamIf_ReadDataType, CODERAMIF_VAR_CLEARED) CodeRamIf_ReadData;

#define CODERAMIF_STOP_SEC_VAR
#include <CodeRamIf_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define CODERAMIF_START_SEC_CST
#include <CodeRamIf_MemMap.h>

static CONST(AB_83_ConstV CodeRamIf_GetStatusInfoType, CODERAMIF_CONST) CodeRamIf_GetStatusTbl[CODERAMIF_GET_STATUS_TBL_NUM] = {
     { CODERAMIF_LOCAL_UNINIT,          CODERAMIF_UNINIT            }
    ,{ CODERAMIF_LOCAL_IDLE,            CODERAMIF_IDLE              }
    ,{ CODERAMIF_LOCAL_READY,           CODERAMIF_BUSY              }
    ,{ CODERAMIF_LOCAL_BUSY,            CODERAMIF_BUSY              }
    ,{ CODERAMIF_LOCAL_UPDATEIDLE,      CODERAMIF_UPDATEIDLE        }
    ,{ CODERAMIF_LOCAL_UPDATEREADY,     CODERAMIF_UPDATEBUSY        }
    ,{ CODERAMIF_LOCAL_UPDATEWRITING,   CODERAMIF_UPDATEBUSY        }
    ,{ CODERAMIF_LOCAL_UPDATECOMPLETE,  CODERAMIF_UPDATECOMPLETE    }
};

#define CODERAMIF_STOP_SEC_CST
#include <CodeRamIf_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define CODERAMIF_START_SEC_CODE
#include <CodeRamIf_MemMap.h>

/******************************************************************************/
/* Function Name | CodeRamIf_WriteStart                                       */
/* Description   | Request to start writing                                   */
/* Preconditions |                                                            */
/* Parameters    | [IN] DestAddr  : Destination address                       */
/*               | [IN] TotalSize : Total write size                          */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CODERAMIF_CODE_SLOW) CodeRamIf_WriteStart
(
    VAR(uint32, AUTOMATIC) DestAddr,
    VAR(uint32, AUTOMATIC) TotalSize
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_NOT_OK;

    if( CODERAMIF_LOCAL_IDLE == CodeRamIf_JobInfo.LocalStatus )
    {
        if( 0UL != TotalSize )
        {
            CodeRamIf_JobInfo.LocalStatus = CODERAMIF_LOCAL_UPDATEIDLE;

            CodeRamIf_WriteData.DestAddr = DestAddr;
            CodeRamIf_WriteData.TotalSize = TotalSize;

            Result = E_OK;
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CodeRamIf_WriteUpdate                                      */
/* Description   | Request to update writing                                  */
/* Preconditions |                                                            */
/* Parameters    | [IN] SrcAddr : Source address                              */
/*               | [IN] Size    : Write size                                  */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CODERAMIF_CODE_SLOW) CodeRamIf_WriteUpdate
(
    P2CONST(uint8, AUTOMATIC, CODERAMIF_APPL_CONST) SrcAddr,
    VAR(uint32, AUTOMATIC) Size
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_NOT_OK;

    if( CODERAMIF_LOCAL_UPDATEIDLE == CodeRamIf_JobInfo.LocalStatus )
    {
        if( NULL_PTR != SrcAddr )
        {
            if( 0UL != Size )
            {
                if( CodeRamIf_WriteData.TotalSize >= Size )
                {
                    CodeRamIf_JobInfo.LocalStatus = CODERAMIF_LOCAL_UPDATEREADY;

                    CodeRamIf_WriteData.SrcAddr = SrcAddr;
                    CodeRamIf_WriteData.UpdateSize = Size;

                    CodeRamIf_JobInfo.JobResult = CODERAMIF_JOB_PENDING;

                    Result = E_OK;
                }
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CodeRamIf_WriteFinish                                      */
/* Description   | Request to finish writing                                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, CODERAMIF_CODE_SLOW) CodeRamIf_WriteFinish (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_NOT_OK;

    if( CODERAMIF_LOCAL_UPDATECOMPLETE == CodeRamIf_JobInfo.LocalStatus )
    {
        CodeRamIf_JobInfo.LocalStatus = CODERAMIF_LOCAL_IDLE;

        Result = E_OK;
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CodeRamIf_Read                                             */
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
FUNC(Std_ReturnType, CODERAMIF_CODE_SLOW) CodeRamIf_Read
(
    VAR(uint32, AUTOMATIC) SrcAddr,
    P2VAR(uint8, AUTOMATIC, CODERAMIF_APPL_DATA) DestAddr,
    VAR(uint32, AUTOMATIC) Size
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_NOT_OK;

    if( CODERAMIF_LOCAL_IDLE == CodeRamIf_JobInfo.LocalStatus )
    {
        if( NULL_PTR != DestAddr )
        {
            if( 0UL != Size )
            {
                CodeRamIf_JobInfo.LocalStatus = CODERAMIF_LOCAL_READY;

                CodeRamIf_ReadData.DestAddr = DestAddr;
                CodeRamIf_ReadData.SrcAddr = SrcAddr;
                CodeRamIf_ReadData.Size = Size;

                CodeRamIf_JobInfo.JobResult = CODERAMIF_JOB_PENDING;

                Result = E_OK;
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | CodeRamIf_GetStatus                                        */
/* Description   | Get job status                                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | JobStatus                                                  */
/*               |  CODERAMIF_UNINIT                                          */
/*               |  CODERAMIF_IDLE                                            */
/*               |  CODERAMIF_BUSY                                            */
/*               |  CODERAMIF_UPDATEIDLE                                      */
/*               |  CODERAMIF_UPDATEBUSY                                      */
/*               |  CODERAMIF_UPDATECOMPLETE                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(CodeRamIf_StatusType, CODERAMIF_CODE_SLOW) CodeRamIf_GetStatus (void)
{
    VAR(CodeRamIf_StatusType, AUTOMATIC) JobStatus;
    VAR(uint8, AUTOMATIC) i;

    /* If it does not match the table, CodeRamIf returns an abnormal value, */
    /* and then MemM detects an error.                                      */
    JobStatus = (CodeRamIf_StatusType)CodeRamIf_JobInfo.LocalStatus;

    for( i = 0U; i < CODERAMIF_GET_STATUS_TBL_NUM; i++ )
    {
        if( CodeRamIf_JobInfo.LocalStatus == CodeRamIf_GetStatusTbl[i].LocalStatus )
        {
            JobStatus = CodeRamIf_GetStatusTbl[i].JobStatus;
            break;
        }
    }

    return JobStatus;
}

/******************************************************************************/
/* Function Name | CodeRamIf_GetJobResult                                     */
/* Description   | Get job result                                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | JobResult                                                  */
/*               |  CODERAMIF_JOB_OK                                          */
/*               |  CODERAMIF_JOB_FAILED                                      */
/*               |  CODERAMIF_JOB_PENDING                                     */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(CodeRamIf_JobResultType, CODERAMIF_CODE_SLOW) CodeRamIf_GetJobResult (void)
{
    return CodeRamIf_JobInfo.JobResult;
}

/******************************************************************************/
/* Function Name | CodeRamIf_Init                                             */
/* Description   | Initialize CodeRamIf                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CODERAMIF_CODE_SLOW) CodeRamIf_Init (void)
{
    if( (CODERAMIF_LOCAL_UNINIT == CodeRamIf_JobInfo.LocalStatus) ||
            (CODERAMIF_LOCAL_IDLE == CodeRamIf_JobInfo.LocalStatus) )
    {
        CodeRamIf_WriteData.DestAddr = CODERAMIF_INVALID_ADDR;
        CodeRamIf_WriteData.SrcAddr = NULL_PTR;
        CodeRamIf_WriteData.TotalSize = CODERAMIF_INVALID_SIZE;
        CodeRamIf_WriteData.UpdateSize = CODERAMIF_INVALID_SIZE;

        CodeRamIf_ReadData.DestAddr = NULL_PTR;
        CodeRamIf_ReadData.SrcAddr = CODERAMIF_INVALID_ADDR;
        CodeRamIf_ReadData.Size = CODERAMIF_INVALID_SIZE;

        CodeRamIf_JobInfo.LocalStatus = CODERAMIF_LOCAL_IDLE;
        CodeRamIf_JobInfo.JobResult = CODERAMIF_JOB_OK;
    }
    else
    {
        CodeRamIf_Sub_Fail(CODERAMIF_ERROR_REPORT, CODERAMIF_E_API_ID_INIT, CODERAMIF_E_CASE_STATUS_FAIL);
    }

    return;
}

/******************************************************************************/
/* Function Name | CodeRamIf_MainFunction                                     */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CODERAMIF_CODE_SLOW) CodeRamIf_MainFunction (void)
{
    if( (CODERAMIF_LOCAL_READY == CodeRamIf_JobInfo.LocalStatus) ||
            (CODERAMIF_LOCAL_BUSY == CodeRamIf_JobInfo.LocalStatus) )
    {
        CodeRamIf_Sub_Read();
    }
    else if( (CODERAMIF_LOCAL_UPDATEREADY == CodeRamIf_JobInfo.LocalStatus) ||
                 (CODERAMIF_LOCAL_UPDATEWRITING == CodeRamIf_JobInfo.LocalStatus) )
    {
        CodeRamIf_Sub_Write();
    }
    else
    {
        /* No process */
    }

    return;
}

/******************************************************************************/
/* Function Name | CodeRamIf_DeInit                                           */
/* Description   | Deinitialize CodeRamIf                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, CODERAMIF_CODE_SLOW) CodeRamIf_DeInit (void)
{
    CodeRamIf_WriteData.DestAddr = 0x00000000UL;
    CodeRamIf_WriteData.SrcAddr = NULL_PTR;
    CodeRamIf_WriteData.TotalSize = CODERAMIF_INVALID_SIZE;
    CodeRamIf_WriteData.UpdateSize = CODERAMIF_INVALID_SIZE;

    CodeRamIf_ReadData.DestAddr = NULL_PTR;
    CodeRamIf_ReadData.SrcAddr = 0x00000000UL;
    CodeRamIf_ReadData.Size = CODERAMIF_INVALID_SIZE;

    CodeRamIf_JobInfo.LocalStatus = CODERAMIF_LOCAL_UNINIT;
    CodeRamIf_JobInfo.JobResult = CODERAMIF_JOB_OK;

    return;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/
/******************************************************************************/
/* Function Name | CodeRamIf_Sub_Write                                        */
/* Description   | Write in target area that was requested by                 */
/*               | CodeRamIf_WriteStart and CodeRamIf_WriteUpdate             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CODERAMIF_CODE_FAST) CodeRamIf_Sub_Write (void)
{
    VAR(uint32, AUTOMATIC) TargetSize;

    if( CodeRamIf_WriteData.UpdateSize < CodeRamIf_Cfg_Data.WriteSize )
    {
        TargetSize = CodeRamIf_WriteData.UpdateSize;
    }
    else
    {
        TargetSize = CodeRamIf_Cfg_Data.WriteSize;
    }

    Rpg_MemCopy((uint8*)CodeRamIf_WriteData.DestAddr, CodeRamIf_WriteData.SrcAddr, TargetSize);

    MemBarrier8((const uint8*)(CodeRamIf_WriteData.DestAddr + (TargetSize - CODERAMIF_ADJUST_ENDADDR)));    /* no wrap around */

    CodeRamIf_WriteData.DestAddr += TargetSize;     /* no wrap around */
    CodeRamIf_WriteData.SrcAddr = &CodeRamIf_WriteData.SrcAddr[TargetSize];
    CodeRamIf_WriteData.TotalSize -= TargetSize;    /* no wrap around */
    CodeRamIf_WriteData.UpdateSize -= TargetSize;   /* no wrap around */

    if( 0UL == CodeRamIf_WriteData.TotalSize )
    {
        CodeRamIf_JobInfo.JobResult = CODERAMIF_JOB_OK;
        CodeRamIf_JobInfo.LocalStatus = CODERAMIF_LOCAL_UPDATECOMPLETE;
    }
    else if( 0UL == CodeRamIf_WriteData.UpdateSize )
    {
        CodeRamIf_JobInfo.JobResult = CODERAMIF_JOB_OK;
        CodeRamIf_JobInfo.LocalStatus = CODERAMIF_LOCAL_UPDATEIDLE;
    }
    else
    {
        CodeRamIf_JobInfo.LocalStatus = CODERAMIF_LOCAL_UPDATEWRITING;
    }

    return;
}

/******************************************************************************/
/* Function Name | CodeRamIf_Sub_Read                                         */
/* Description   | Read target area that was requested by CodeRamIf_Read      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CODERAMIF_CODE_FAST) CodeRamIf_Sub_Read (void)
{
    VAR(uint32, AUTOMATIC) TargetSize;

    if( CodeRamIf_ReadData.Size < CodeRamIf_Cfg_Data.ReadSize )
    {
        TargetSize = CodeRamIf_ReadData.Size;
    }
    else
    {
        TargetSize = CodeRamIf_Cfg_Data.ReadSize;
    }

    Rpg_MemCopy(CodeRamIf_ReadData.DestAddr, (const uint8*)CodeRamIf_ReadData.SrcAddr, TargetSize);

    CodeRamIf_ReadData.DestAddr = &CodeRamIf_ReadData.DestAddr[TargetSize];
    CodeRamIf_ReadData.SrcAddr += TargetSize;   /* no wrap around */
    CodeRamIf_ReadData.Size -= TargetSize;      /* no wrap around */

    if( 0UL == CodeRamIf_ReadData.Size )
    {
        CodeRamIf_JobInfo.JobResult = CODERAMIF_JOB_OK;
        CodeRamIf_JobInfo.LocalStatus = CODERAMIF_LOCAL_IDLE;
    }
    else
    {
        CodeRamIf_JobInfo.LocalStatus = CODERAMIF_LOCAL_BUSY;
    }

    return;
}

/******************************************************************************/
/* Function Name | CodeRamIf_Sub_Fail                                         */
/* Description   | Set the information to failed and notify EcuM of the error */
/*               | information                                                */
/* Preconditions |                                                            */
/* Parameters    | [IN] ReportReq                                             */
/*               |       CODERAMIF_ERROR_REPORT     : Call EcuM_ReportError   */
/*               |       CODERAMIF_ERROR_NOT_REPORT : Do not call             */
/*               |                                    EcuM_ReportError        */
/*               | [IN] ApiId   : API ID                                      */
/*               | [IN] ErrorId : Error ID                                    */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, CODERAMIF_CODE_FAST) CodeRamIf_Sub_Fail
(
    VAR(uint8, AUTOMATIC) ReportReq,
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
)
{
    VAR(EcuM_ErrorType, AUTOMATIC) ErrorInfo;

    CodeRamIf_JobInfo.JobResult = CODERAMIF_JOB_FAILED;
    CodeRamIf_JobInfo.LocalStatus = CODERAMIF_LOCAL_IDLE;

    if( CODERAMIF_ERROR_REPORT == ReportReq )
    {
        ErrorInfo.ModuleId = ECUM_MODULE_CODERAMIF;
        ErrorInfo.ApiId = ApiId;
        ErrorInfo.ErrorId = ErrorId;
        EcuM_ReportError(&ErrorInfo);
    }

    return;
}

#define CODERAMIF_STOP_SEC_CODE
#include <CodeRamIf_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2019/02/12 :Update                                rel.AUBASS */
/*  v3.00       :2022/06/07 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

