/* DiagSrv_0x31_Check_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x31/Check/CODE                                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagSrv.h>
#include <PrgChk.h>
#include <FscDtct.h>
#include <Rte.h>
#include <ReprogOpt.h>

#include "DiagSrv_lib_Cfg.h"
#include "DiagSrv_0x31.h"
#include "DiagSrv_0x31_Cfg.h"
#include "DiagSrv_Local.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Service 0x31 Status */
#define DIAGSRV_0X31_CHK_STAT_IDLE                  ((uint8)0x00U)
#define DIAGSRV_0X31_CHK_STAT_WAIT_CANCEL_FSCDTCT   ((uint8)0x01U)
#define DIAGSRV_0X31_CHK_STAT_WAIT_PRGCHK           ((uint8)0x02U)
#define DIAGSRV_0X31_CHK_STAT_WAIT_FSCDTCT          ((uint8)0x03U)
#define DIAGSRV_0X31_CHK_STAT_WAIT_POST_FSCDTCT     ((uint8)0x04U)
#define DIAGSRV_0X31_CHK_STAT_WAIT_WRITE_RPRGDATA   ((uint8)0x05U)
#define DIAGSRV_0X31_CHK_STAT_WAIT_READ_RPRGDATA    ((uint8)0x06U)
#define DIAGSRV_0X31_CHK_STAT_WAIT_HOOK_CHECK       ((uint8)0x07U)

/* Data Length */
#define DIAGSRV_0X31_CHK_CRC_SIZE                   ((uint16)0x0004U)

/* Bit Calculation */
#define DIAGSRV_0X31_CHK_BIT_SHIFT_8                ((uint8)8U)

#define DIAGSRV_0X31_CHK_VAL_0XFF                   ((uint8)0xFFU)

#define DIAGSRV_0X31_CHK_CONDMATRIX_SBL_NUM         (sizeof(DiagSrv_0x31_Chk_CondMatrix_SblTbl) / sizeof(DiagSrv_0x31_Chk_CondMatrix_SblTbl[0]))
#define DIAGSRV_0X31_CHK_CONDMATRIX_APL_NUM         (sizeof(DiagSrv_0x31_Chk_CondMatrix_AplTbl) / sizeof(DiagSrv_0x31_Chk_CondMatrix_AplTbl[0]))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint32 Addr;
    uint32 Size;
} DiagSrv_0x31_Chk_AreaInfoType;

typedef DiagSrv_0x31_Chk_AreaInfoType   DiagSrv_0x31_Chk_RprgDataAreaInfoType;

typedef struct {
    uint8 RewriteStatus;
    uint8 Nrc;
} DiagSrv_0x31_Chk_CondMatrixType;

typedef struct {
    uint8  MatrixNum;
    P2CONST(DiagSrv_0x31_Chk_CondMatrixType, TYPEDEF, DIAGSRV_APPL_CONST) MatrixPtr;
} DiagSrv_0x31_Chk_CondMatrixInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_ClearInfo (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_Time_PrgChk (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_Time_FscDtct (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_Time_WriteRprgData (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_Time_ReadRprgData (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_Time_PostHook (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_CheckCondition (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_CheckIdLength (void);
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_GetCheckArea (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_SigVerify (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_ReqSigVerify (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_PostSigVerify (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_CalcCrc (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_PostCalcCrc (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_PostCheck (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_WriteRprgData (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_MakeRprgData (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_ReadRprgData (void);
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_VerifyRprgData (void);
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_CompareMemory
(
    CONST(uint8, AUTOMATIC) Buf1[],
    CONST(uint8, AUTOMATIC) Buf2[],
    VAR(uint16, AUTOMATIC) Len
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_EndProcess
(
    VAR(uint8, AUTOMATIC) Nrc
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Chk_JobStatus;
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Chk_CheckType;
static VAR(DiagSrv_0x31_Chk_AreaInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Chk_AreaInfo;
static VAR(DiagSrv_0x31_Chk_RprgDataAreaInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Chk_RprgDataAreaInfo;
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Chk_CrcBuff[DIAGSRV_0X31_CHK_CRC_SIZE];
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Chk_RprgDataBuff[DIAGSRV_CFG_RPRGDATA_SIZE];

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

static CONST(DiagSrv_0x31_Chk_CondMatrixType, DIAGSRV_CONST) DiagSrv_0x31_Chk_CondMatrix_SblTbl[] = {
     { DIAGSRV_REWRITESTAT_SBL_DL_COMPLETE,     DIAG_NRC_RCRRP }
    ,{ DIAGSRV_REWRITESTAT_SBL_DL_CHECK,        DIAG_NRC_PR    }
};
static CONST(AB_83_ConstV DiagSrv_0x31_Chk_CondMatrixInfoType, DIAGSRV_CONST) DiagSrv_0x31_Chk_CondMatrix_Sbl = {
    DIAGSRV_0X31_CHK_CONDMATRIX_SBL_NUM,
    &DiagSrv_0x31_Chk_CondMatrix_SblTbl[0]
};
static CONST(DiagSrv_0x31_Chk_CondMatrixType, DIAGSRV_CONST) DiagSrv_0x31_Chk_CondMatrix_AplTbl[] = {
     { DIAGSRV_REWRITESTAT_DATA_DL_COMPLETE,    DIAG_NRC_RCRRP }
    ,{ DIAGSRV_REWRITESTAT_DATA_CHECK,          DIAG_NRC_PR    }
};
static CONST(AB_83_ConstV DiagSrv_0x31_Chk_CondMatrixInfoType, DIAGSRV_CONST) DiagSrv_0x31_Chk_CondMatrix_Apl = {
    DIAGSRV_0X31_CHK_CONDMATRIX_APL_NUM,
    &DiagSrv_0x31_Chk_CondMatrix_AplTbl[0]
};

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define DIAGSRV_START_SEC_CODE
#include <DiagSrv_MemMap.h>

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_Init                                      */
/* Description   | Initialize                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_Init (void)
{
    DiagSrv_0x31_Chk_ClearInfo();

    Rte_Rpg_MemSet(DiagSrv_0x31_Chk_CrcBuff, 0U, sizeof(DiagSrv_0x31_Chk_CrcBuff));
    Rte_Rpg_MemSet(DiagSrv_0x31_Chk_RprgDataBuff, 0U, sizeof(DiagSrv_0x31_Chk_RprgDataBuff));

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_Time                                      */
/* Description   | Time function                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Nrc                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_Time (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) RewriteAreaNum;
    VAR(uint8, AUTOMATIC) RewriteAreaStatus;

    Nrc = DIAG_NRC_RCRRP;

    if( DiagSrv_0x31_Chk_JobStatus != DIAGSRV_0X31_CHK_STAT_IDLE )
    {
        Nrc = DIAG_NRC_GPF;

        if( DiagSrv_0x31_Chk_JobStatus == DIAGSRV_0X31_CHK_STAT_WAIT_PRGCHK )
        {
            Nrc = DiagSrv_0x31_Chk_Time_PrgChk();
        }
        else if( (DiagSrv_0x31_Chk_JobStatus == DIAGSRV_0X31_CHK_STAT_WAIT_FSCDTCT) ||
                (DiagSrv_0x31_Chk_JobStatus == DIAGSRV_0X31_CHK_STAT_WAIT_POST_FSCDTCT) ||
                (DiagSrv_0x31_Chk_JobStatus == DIAGSRV_0X31_CHK_STAT_WAIT_CANCEL_FSCDTCT) )
        {
            Nrc = DiagSrv_0x31_Chk_Time_FscDtct();
        }
        else if( DiagSrv_0x31_Chk_JobStatus == DIAGSRV_0X31_CHK_STAT_WAIT_WRITE_RPRGDATA )
        {
            Nrc = DiagSrv_0x31_Chk_Time_WriteRprgData();
        }
        else if( DiagSrv_0x31_Chk_JobStatus == DIAGSRV_0X31_CHK_STAT_WAIT_READ_RPRGDATA )
        {
            Nrc = DiagSrv_0x31_Chk_Time_ReadRprgData();
        }
        else if( DiagSrv_0x31_Chk_JobStatus == DIAGSRV_0X31_CHK_STAT_WAIT_HOOK_CHECK )
        {
            Nrc = DiagSrv_0x31_Chk_Time_PostHook();
        }
        else
        {
            /* No process */
        }

        if( Nrc == DIAG_NRC_PR )
        {
            if( DiagSrv_0x31_Rid == DIAGSRV_0X31_RID_CHECK_APL )
            {
                RewriteAreaNum = DiagSrv_GetRewriteAreaNumber();
                if( RewriteAreaNum != DIAGSRV_REWRITEAREA_INVALID )
                {
                    RewriteAreaStatus = DIAGSRV_LBSTAT_REWRITING_NG;

                    if( DiagSrv_0x31_CheckMemoryStatus.CheckStatus == DIAGSRV_0X31_CHECKSTATUS_SUCCESS )
                    {
                        RewriteAreaStatus = DIAGSRV_LBSTAT_REWRITING_OK;
                    }

                    DiagSrv_SetRewriteAreaStatus(RewriteAreaNum, RewriteAreaStatus);
                }
                else
                {
                    Nrc = DIAG_NRC_GPF;
                }
            }
        }

        DiagSrv_0x31_Chk_EndProcess(Nrc);
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_Processing                                */
/* Description   | Processing function                                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_CNC                                              */
/*               |  DIAG_NRC_ROOR                                             */
/*               |  DIAG_NRC_GPF                                              */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_Processing (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DiagSrv_0x31_Chk_CheckCondition();
    if( Nrc == DIAG_NRC_PR )
    {
        /* resend */
        DiagSrv_0x31_CheckMemoryStatus.CheckStatus = DIAGSRV_0X31_CHECKSTATUS_SUCCESS;
        DiagSrv_0x31_CheckMemoryStatus.FailedCause = DIAGSRV_0X31_FAILEDCAUSE_NOFAILED;
    }
    else if( Nrc == DIAG_NRC_RCRRP )
    {
        Nrc = DiagSrv_0x31_Chk_CheckIdLength();
        if( Nrc == DIAG_NRC_RCRRP )
        {
            Nrc = DiagSrv_0x31_MsgCheckCondition();
            if( Nrc == DIAG_NRC_RCRRP )
            {
                Ret = DiagSrv_0x31_Chk_GetCheckArea();
                if( Ret != (Std_ReturnType)E_OK )
                {
                    Nrc = DIAG_NRC_GPF;
                }
            }
        }

        if( Nrc == DIAG_NRC_RCRRP )
        {
            if( DiagSrv_0x31_Chk_CheckType == DIAGSRV_0X31_CHECKTYPE_SIG )
            {
                /* "DiagSrv_0x31_Chk_JobStatus" is updated with DiagSrv_0x31_Chk_SigVerify(). */
                DiagSrv_0x31_Chk_SigVerify();
            }
            else
            {
                /* If check type is CRC, signature process is cancelled. */
                FscDtct_ReqPostSigVerify(NULL_PTR, 0U);

                DiagSrv_0x31_Chk_JobStatus = DIAGSRV_0X31_CHK_STAT_WAIT_CANCEL_FSCDTCT;
            }
        }
    }
    else
    {
        /* No process */
    }

    return Nrc;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_ClearInfo                                 */
/* Description   | Clear information                                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_ClearInfo (void)
{
    DiagSrv_0x31_Chk_JobStatus = DIAGSRV_0X31_CHK_STAT_IDLE;

    DiagSrv_0x31_Chk_CheckType = DIAGSRV_0X31_CHECKTYPE_SIG;

    DiagSrv_0x31_Chk_AreaInfo.Addr = 0UL;
    DiagSrv_0x31_Chk_AreaInfo.Size = 0UL;

    DiagSrv_0x31_Chk_RprgDataAreaInfo.Addr = 0UL;
    DiagSrv_0x31_Chk_RprgDataAreaInfo.Size = 0UL;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_Time_PrgChk                               */
/* Description   | Time of DIAGSRV_0X31_CHK_STAT_WAIT_PRGCHK                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_Time_PrgChk (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;

    Nrc = DIAG_NRC_RCRRP;

    Status = PrgChk_GetStatus();
    if( Status == PRGCHK_IDLE )
    {
        JobResult = PrgChk_GetJobResult();
        if( JobResult == PRGCHK_JOB_OK )
        {
            Nrc = DiagSrv_0x31_Chk_PostCalcCrc();
        }
        else
        {
            Nrc = DIAG_NRC_GPF;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_Time_FscDtct                              */
/* Description   | The following time                                         */
/*               |  - DIAGSRV_0X31_CHK_STAT_WAIT_FSCDTCT                      */
/*               |  - DIAGSRV_0X31_CHK_STAT_WAIT_POST_FSCDTCT                 */
/*               |  - DIAGSRV_0X31_CHK_STAT_WAIT_CANCEL_FSCDTCT               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_Time_FscDtct (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;

    Nrc = DIAG_NRC_RCRRP;

    Status = FscDtct_GetStatus();
    if( Status == FSCDTCT_IDLE )
    {
        Nrc = DIAG_NRC_GPF;

        if( DiagSrv_0x31_Chk_JobStatus != DIAGSRV_0X31_CHK_STAT_WAIT_CANCEL_FSCDTCT )
        {
            JobResult = FscDtct_GetJobResult();
            if( JobResult == FSCDTCT_JOB_OK )
            {
                if( DiagSrv_0x31_Chk_JobStatus == DIAGSRV_0X31_CHK_STAT_WAIT_FSCDTCT )
                {
                    /* This route comes in the following cases.                                                 */
                    /*  - Parallel disable                                                                      */
                    /*    (ReprogOpt_ParallelConfig == STD_OFF)                                                 */
                    /*  - Parallel enable and EXTCODEFLS                                                        */
                    /*    (ReprogOpt_ParallelConfig == STD_ON && DeviceType == RTE_MEMM_DEVICE_TYPE_EXTCODEFLS) */
                    DiagSrv_0x31_Chk_PostSigVerify();

                    /* "DiagSrv_0x31_Chk_JobStatus" is updated with DiagSrv_0x31_Chk_PostSigVerify(). */
                    Nrc = DIAG_NRC_RCRRP;
                }
                else    /* DIAGSRV_0X31_CHK_STAT_WAIT_POST_FSCDTCT */
                {
                    DiagSrv_0x31_CheckMemoryStatus.CheckStatus = DIAGSRV_0X31_CHECKSTATUS_SUCCESS;
                    DiagSrv_0x31_CheckMemoryStatus.FailedCause = DIAGSRV_0X31_FAILEDCAUSE_NOFAILED;

                    /* "DiagSrv_0x31_Chk_JobStatus" is updated with DiagSrv_0x31_Chk_PostCheck(). */
                    Nrc = DIAG_NRC_PR;
                }
            }
            else if( JobResult == FSCDTCT_JOB_VERIFYERR )
            {
                if( DiagSrv_0x31_Chk_JobStatus == DIAGSRV_0X31_CHK_STAT_WAIT_POST_FSCDTCT )
                {
                    DiagSrv_0x31_CheckMemoryStatus.CheckStatus = DIAGSRV_0X31_CHECKSTATUS_FAILED;
                    DiagSrv_0x31_CheckMemoryStatus.FailedCause = DIAGSRV_0X31_FAILEDCAUSE_VERIFY_ERROR;

                    /* "DiagSrv_0x31_Chk_JobStatus" is updated with DiagSrv_0x31_Chk_PostCheck(). */
                    Nrc = DIAG_NRC_PR;
                }
            }
            else
            {
                /* No process */
            }
        }
        else    /* DIAGSRV_0X31_CHK_STAT_WAIT_CANCEL_FSCDTCT */
        {
            /* FscDtct_GetJobResult() is not called,   */
            /* because result of cancel is not needed. */
            if( DiagSrv_0x31_Chk_CheckType == DIAGSRV_0X31_CHECKTYPE_CRC )
            {
                Nrc = DiagSrv_0x31_Chk_CalcCrc();
            }
        }
    }

    if( Nrc == DIAG_NRC_PR )
    {
        Nrc = DiagSrv_0x31_Chk_PostCheck();
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_Time_WriteRprgData                        */
/* Description   | Time of DIAGSRV_0X31_CHK_STAT_WAIT_WRITE_RPRGDATA          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_Time_WriteRprgData (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DIAG_NRC_GPF;

    Status = RpgLib_GetStatus();
    if( Status == RPGLIB_UPDATECOMPLETE )
    {
        JobResult = RpgLib_GetJobResult();
        if( JobResult == RPGLIB_JOB_OK )
        {
            Ret = RpgLib_WriteMemFinish();
            if( Ret == (Std_ReturnType)E_OK )
            {
                Nrc = DiagSrv_0x31_Chk_ReadRprgData();
            }
        }
    }
    else if( Status == RPGLIB_UPDATEBUSY )
    {
        Nrc = DIAG_NRC_RCRRP;
    }
    else
    {
        /* No process */
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_Time_ReadRprgData                         */
/* Description   | Time of DIAGSRV_0X31_CHK_STAT_WAIT_READ_RPRGDATA           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_Time_ReadRprgData (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;
    VAR(uint8, AUTOMATIC) RewriteAreaNum;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DIAG_NRC_GPF;

    Status = RpgLib_GetStatus();
    if( Status == RPGLIB_IDLE )
    {
        JobResult = RpgLib_GetJobResult();
        if( JobResult == RPGLIB_JOB_OK )
        {
            Ret = DiagSrv_0x31_Chk_VerifyRprgData();
            if( Ret == (Std_ReturnType)E_OK )
            {
                RewriteAreaNum = DiagSrv_GetRewriteAreaNumber();
                if( RewriteAreaNum != DIAGSRV_REWRITEAREA_INVALID )
                {
                    Ret = DiagSrv_0x31_Usr_ReqPostCheckData(RewriteAreaNum,
                                                            DiagSrv_0x31_Chk_CheckType);
                    if( Ret == (Std_ReturnType)E_OK )
                    {
                        DiagSrv_0x31_Chk_JobStatus = DIAGSRV_0X31_CHK_STAT_WAIT_HOOK_CHECK;
                        Nrc = DIAG_NRC_RCRRP;
                    }
                }
            }
        }
    }
    else if( Status == RPGLIB_BUSY )
    {
        Nrc = DIAG_NRC_RCRRP;
    }
    else
    {
        /* No process */
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_Time_PostHook                             */
/* Description   | Time of DIAGSRV_0X31_CHK_STAT_WAIT_HOOK_CHECK              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_Time_PostHook (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;

    Nrc = DIAG_NRC_GPF;

    Status = DiagSrv_0x31_Usr_GetStatus();
    if( Status == DIAGSRV_0X31_USR_IDLE )
    {
        JobResult = DiagSrv_0x31_Usr_GetJobResult();
        if( JobResult == DIAGSRV_0X31_USR_JOB_OK )
        {
            DiagSrv_0x31_CheckMemoryStatus.CheckStatus = DIAGSRV_0X31_CHECKSTATUS_SUCCESS;
            DiagSrv_0x31_CheckMemoryStatus.FailedCause = DIAGSRV_0X31_FAILEDCAUSE_NOFAILED;

            DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_DATA_CHECK);
        }
        else
        {
            DiagSrv_0x31_CheckMemoryStatus.CheckStatus = DIAGSRV_0X31_CHECKSTATUS_FAILED;
            DiagSrv_0x31_CheckMemoryStatus.FailedCause = DIAGSRV_0X31_FAILEDCAUSE_GENERAL;
        }

        DiagSrv_0x31_Chk_JobStatus = DIAGSRV_0X31_CHK_STAT_IDLE;
        Nrc = DIAG_NRC_PR;
    }
    else if( Status == DIAGSRV_0X31_USR_BUSY )
    {
        Nrc = DIAG_NRC_RCRRP;
    }
    else
    {
        /* No process */
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_CheckCondition                            */
/* Description   | Check condition error and resend request                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_CNC                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_CheckCondition (void)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) RewriteStatus;

    Nrc = DIAG_NRC_CNC;

    RewriteStatus = DiagSrv_GetRewriteStatus();

    if( DiagSrv_0x31_Rid == DIAGSRV_0X31_RID_CHECK_SBL )
    {
        for( i = 0UL; i < DiagSrv_0x31_Chk_CondMatrix_Sbl.MatrixNum; i++ )
        {
            if( RewriteStatus == DiagSrv_0x31_Chk_CondMatrix_Sbl.MatrixPtr[i].RewriteStatus )
            {
                Nrc = DiagSrv_0x31_Chk_CondMatrix_Sbl.MatrixPtr[i].Nrc;
                break;
            }
        }
    }
    else
    {
        for( i = 0UL; i < DiagSrv_0x31_Chk_CondMatrix_Apl.MatrixNum; i++ )
        {
            if( RewriteStatus == DiagSrv_0x31_Chk_CondMatrix_Apl.MatrixPtr[i].RewriteStatus )
            {
                Nrc = DiagSrv_0x31_Chk_CondMatrix_Apl.MatrixPtr[i].Nrc;
                break;
            }
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_CheckIdLength                             */
/* Description   | Check request id and length                                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_ROOR                                             */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_CheckIdLength (void)
{
    VAR(uint16, AUTOMATIC) CheckDataLength;
    VAR(uint8, AUTOMATIC) CheckTypeId;
    VAR(uint8, AUTOMATIC) EncryptFlag;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_ROOR;

    CheckTypeId = DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_CHK_ID_POS];
    CheckDataLength = (uint16)Rte_Rpg_ByteCombine(&DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_CHK_DATALEN_POS],
                                                sizeof(CheckDataLength));

    if( (CheckTypeId == DIAGSRV_0X31_CHECKTYPE_SIG) &&
        (CheckDataLength == DiagSrv_0x31_Config.SignatureSize) )
    {
        /* singnature */
        DiagSrv_0x31_Chk_CheckType = DIAGSRV_0X31_CHECKTYPE_SIG;

        Nrc = DIAG_NRC_RCRRP;
    }
    else if( (CheckTypeId == DIAGSRV_0X31_CHECKTYPE_CRC) &&
            (CheckDataLength == DIAGSRV_0X31_CHK_CRC_SIZE) )
    {
        EncryptFlag = DiagSrv_GetEncryptionFlag();
        if( EncryptFlag == DIAGSRV_ENCRYPTIONFLAG_OFF )
        {
            /* crc */
            DiagSrv_0x31_Chk_CheckType = DIAGSRV_0X31_CHECKTYPE_CRC;

            Nrc = DIAG_NRC_RCRRP;
        }
    }
    else
    {
        /* No process */
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_GetCheckArea                              */
/* Description   | Get address and size of area to check                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_GetCheckArea (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(uint8, AUTOMATIC) RewriteStatus;
    VAR(uint8, AUTOMATIC) RewriteAreaNum;

    Ret = E_NOT_OK;

    RewriteStatus = DiagSrv_GetRewriteStatus();
    if( RewriteStatus == DIAGSRV_REWRITESTAT_DATA_DL_COMPLETE )
    {
        RewriteAreaNum = DiagSrv_GetRewriteAreaNumber();
        if( RewriteAreaNum != DIAGSRV_REWRITEAREA_INVALID )
        {
            DiagSrv_GetRewriteAreaInfo(RewriteAreaNum,
                                    &DiagSrv_0x31_Chk_AreaInfo.Addr,
                                    &DiagSrv_0x31_Chk_AreaInfo.Size);
            Ret = E_OK;
        }
    }
    else
    {
        /* DIAGSRV_REWRITESTAT_SBL_DL_COMPLETE */
        DiagSrv_GetSblAreaInfo(&DiagSrv_0x31_Chk_AreaInfo.Addr,
                            &DiagSrv_0x31_Chk_AreaInfo.Size);
        Ret = E_OK;
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_SigVerify                                 */
/* Description   | Start Signature Verify                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_SigVerify (void)
{
    VAR(uint8, AUTOMATIC) DeviceType;

    if( ReprogOpt_ParallelConfig == (uint8)STD_ON )
    {
        DeviceType = DiagSrv_GetWriteDeviceType();
        if( (DeviceType == DIAGSRV_DEVICE_TYPE_CODEFLS) || (DeviceType == DIAGSRV_DEVICE_TYPE_CODERAM) )
        {
            DiagSrv_0x31_Chk_PostSigVerify();
        }
        else
        {
            DiagSrv_0x31_Chk_ReqSigVerify();
        }
    }
    else
    {
        DiagSrv_0x31_Chk_ReqSigVerify();
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_ReqSigVerify                              */
/* Description   | Request Signature Verify                                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_ReqSigVerify (void)
{
    FscDtct_ReqSigVerify(DiagSrv_0x31_Chk_AreaInfo.Addr, DiagSrv_0x31_Chk_AreaInfo.Size);

    DiagSrv_0x31_Chk_JobStatus = DIAGSRV_0X31_CHK_STAT_WAIT_FSCDTCT;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_PostSigVerify                             */
/* Description   | Post Signature Verify                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_PostSigVerify (void)
{
    VAR(uint16, AUTOMATIC) DataLength;

    DataLength = (uint16)Rte_Rpg_ByteCombine(&DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_CHK_DATALEN_POS],
                                            sizeof(DataLength));

    FscDtct_ReqPostSigVerify(&DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_CHK_DATA_POS],
                            (uint32)DataLength);

    DiagSrv_0x31_Chk_JobStatus = DIAGSRV_0X31_CHK_STAT_WAIT_POST_FSCDTCT;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_CalcCrc                                   */
/* Description   | Start CRC calculation                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_CalcCrc (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DIAG_NRC_GPF;

    Ret = PrgChk_PreCalcValue();
    if( Ret == (Std_ReturnType)E_OK )
    {
        Ret = PrgChk_ReqCalcValue(DiagSrv_0x31_Chk_AreaInfo.Addr,
                                DiagSrv_0x31_Chk_AreaInfo.Size,
                                DiagSrv_0x31_Chk_CrcBuff,
                                sizeof(DiagSrv_0x31_Chk_CrcBuff));
        if( Ret == (Std_ReturnType)E_OK )
        {
            DiagSrv_0x31_Chk_JobStatus = DIAGSRV_0X31_CHK_STAT_WAIT_PRGCHK;
            Nrc = DIAG_NRC_RCRRP;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_PostCalcCrc                               */
/* Description   | Post CRC calculation                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_PostCalcCrc (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DIAG_NRC_GPF;

    Ret = PrgChk_PostCalcValue();
    if( Ret == (Std_ReturnType)E_OK )
    {
        Ret = DiagSrv_0x31_Chk_CompareMemory(&DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_CHK_DATA_POS],
                                            DiagSrv_0x31_Chk_CrcBuff,
                                            sizeof(DiagSrv_0x31_Chk_CrcBuff));
        if( Ret == (Std_ReturnType)E_OK )
        {
            /* CRC match */
            DiagSrv_0x31_CheckMemoryStatus.CheckStatus = DIAGSRV_0X31_CHECKSTATUS_SUCCESS;
            DiagSrv_0x31_CheckMemoryStatus.FailedCause = DIAGSRV_0X31_FAILEDCAUSE_NOFAILED;
        }
        else
        {
            /* CRC unmatch */
            DiagSrv_0x31_CheckMemoryStatus.CheckStatus = DIAGSRV_0X31_CHECKSTATUS_FAILED;
            DiagSrv_0x31_CheckMemoryStatus.FailedCause = DIAGSRV_0X31_FAILEDCAUSE_VERIFY_ERROR;
        }

        Nrc = DiagSrv_0x31_Chk_PostCheck();
    }

    Rte_Rpg_MemSet(DiagSrv_0x31_Chk_CrcBuff, 0U, sizeof(DiagSrv_0x31_Chk_CrcBuff));

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_PostCheck                                 */
/* Description   | End of check process                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_PostCheck (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) RewriteStatus;

    Nrc = DIAG_NRC_PR;

    RewriteStatus = DiagSrv_GetRewriteStatus();
    if( RewriteStatus == DIAGSRV_REWRITESTAT_DATA_DL_COMPLETE )
    {
        if( DiagSrv_0x31_CheckMemoryStatus.CheckStatus == DIAGSRV_0X31_CHECKSTATUS_SUCCESS )
        {
            Nrc = DiagSrv_0x31_Chk_WriteRprgData();
        }
        else
        {
            DiagSrv_0x31_Chk_JobStatus = DIAGSRV_0X31_CHK_STAT_IDLE;

            if( DiagSrv_0x31_Config.RoutineStatusForceSuccess == DIAG_SUPPORT )
            {
                DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_DATA_CHECK);
            }
        }
    }
    else    /* DIAGSRV_REWRITESTAT_SBL_DL_COMPLETE */
    {
        DiagSrv_0x31_Chk_JobStatus = DIAGSRV_0X31_CHK_STAT_IDLE;

        if( (DiagSrv_0x31_CheckMemoryStatus.CheckStatus == DIAGSRV_0X31_CHECKSTATUS_SUCCESS) ||
            (DiagSrv_0x31_Config.RoutineStatusForceSuccess == DIAG_SUPPORT) )
        {
            DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_SBL_DL_CHECK);
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_WriteRprgData                             */
/* Description   | Start write RPRG data                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_WriteRprgData (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) RewriteAreaNum;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DIAG_NRC_GPF;

    RewriteAreaNum = DiagSrv_GetRewriteAreaNumber();
    if( RewriteAreaNum != DIAGSRV_REWRITEAREA_INVALID )
    {
        DiagSrv_GetRprgDataAreaInfo(RewriteAreaNum,
                                    &DiagSrv_0x31_Chk_RprgDataAreaInfo.Addr,
                                    &DiagSrv_0x31_Chk_RprgDataAreaInfo.Size);

        Ret = RpgLib_WriteMemStart(RPGLIB_MEMORYID_0,
                                    DiagSrv_0x31_Chk_RprgDataAreaInfo.Addr,
                                    DiagSrv_0x31_Chk_RprgDataAreaInfo.Size);
        if( Ret == (Std_ReturnType)E_OK )
        {
            DiagSrv_0x31_Chk_MakeRprgData();

            Ret = RpgLib_ReqWriteMemUpdate(DiagSrv_0x31_Chk_RprgDataBuff, sizeof(DiagSrv_0x31_Chk_RprgDataBuff));
            if( Ret == (Std_ReturnType)E_OK )
            {
                DiagSrv_0x31_Chk_JobStatus = DIAGSRV_0X31_CHK_STAT_WAIT_WRITE_RPRGDATA;
                Nrc = DIAG_NRC_RCRRP;
            }
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_MakeRprgData                              */
/* Description   | Make RPRG data                                             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_MakeRprgData (void)
{
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) TempAddr;
    VAR(uint16, AUTOMATIC) DataLength;

    Rte_Rpg_MemSet(DiagSrv_0x31_Chk_RprgDataBuff,
                DIAGSRV_0X31_CHK_VAL_0XFF,
                sizeof(DiagSrv_0x31_Chk_RprgDataBuff));

    /* Finger length */
    DiagSrv_0x31_Chk_RprgDataBuff[0] = (uint8)(DIAGSRV_CFG_FINGERPRINT_SIZE >> DIAGSRV_0X31_CHK_BIT_SHIFT_8);
    DiagSrv_0x31_Chk_RprgDataBuff[1] = (uint8)DIAGSRV_CFG_FINGERPRINT_SIZE;

    /* Finger data */
    TempAddr = DiagSrv_GetFingerprintTempArea();
    Rte_Rpg_MemCopy(&DiagSrv_0x31_Chk_RprgDataBuff[DIAGSRV_CFG_RPRGDATA_FINGERPRINT_POS],
                    TempAddr,
                    (uint32)DIAGSRV_CFG_FINGERPRINT_SIZE);

    /* Signature length */
    DataLength = (uint16)Rte_Rpg_ByteCombine(&DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_CHK_DATALEN_POS],
                                            sizeof(DataLength));
    Rte_Rpg_MemCopy(&DiagSrv_0x31_Chk_RprgDataBuff[DIAGSRV_CFG_RPRGDATA_SIGNATURESIZE_POS],
                    &DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_CHK_DATALEN_POS],
                    sizeof(DataLength));

    /* Signature data */
    Rte_Rpg_MemCopy(&DiagSrv_0x31_Chk_RprgDataBuff[DIAGSRV_CFG_RPRGDATA_SIGNATURE_POS],
                    &DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_CHK_DATA_POS],
                    (uint32)DataLength);

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_ReadRprgData                              */
/* Description   | Start read RPRG data                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_ReadRprgData (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DIAG_NRC_GPF;

    Rte_Rpg_MemSet(DiagSrv_0x31_Chk_RprgDataBuff, 0U, sizeof(DiagSrv_0x31_Chk_RprgDataBuff));

    Ret = RpgLib_ReqMemRead(RPGLIB_MEMORYID_0,
                            DiagSrv_0x31_Chk_RprgDataBuff,
                            DiagSrv_0x31_Chk_RprgDataAreaInfo.Addr,
                            DiagSrv_0x31_Chk_RprgDataAreaInfo.Size);
    if( Ret == (Std_ReturnType)E_OK )
    {
        DiagSrv_0x31_Chk_JobStatus = DIAGSRV_0X31_CHK_STAT_WAIT_READ_RPRGDATA;
        Nrc = DIAG_NRC_RCRRP;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_VerifyRprgData                            */
/* Description   | Verify RPRG data                                           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result of verify                                           */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_VerifyRprgData (void)
{
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) TempAddr;
    VAR(uint16, AUTOMATIC) DataLength;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    /* Finger length */
    DataLength = (uint16)Rte_Rpg_ByteCombine(&DiagSrv_0x31_Chk_RprgDataBuff[0],
                                            sizeof(DataLength));
    if( DataLength == DIAGSRV_CFG_FINGERPRINT_SIZE )
    {
        Ret = E_OK;
    }

    if( Ret == (Std_ReturnType)E_OK )
    {
        /* Finger data */
        TempAddr = DiagSrv_GetFingerprintTempArea();
        Ret = DiagSrv_0x31_Chk_CompareMemory(&DiagSrv_0x31_Chk_RprgDataBuff[DIAGSRV_CFG_RPRGDATA_FINGERPRINT_POS],
                                            TempAddr,
                                            DIAGSRV_CFG_FINGERPRINT_SIZE);
    }

    if( Ret == (Std_ReturnType)E_OK )
    {
        /* Signature length */
        DataLength = (uint16)Rte_Rpg_ByteCombine(&DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_CHK_DATALEN_POS],
                                                sizeof(DataLength));
        Ret = DiagSrv_0x31_Chk_CompareMemory(&DiagSrv_0x31_Chk_RprgDataBuff[DIAGSRV_CFG_RPRGDATA_SIGNATURESIZE_POS],
                                            &DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_CHK_DATALEN_POS],
                                            sizeof(DataLength));
    }

    if( Ret == (Std_ReturnType)E_OK )
    {
        /* Signature data */
        Ret = DiagSrv_0x31_Chk_CompareMemory(&DiagSrv_0x31_Chk_RprgDataBuff[DIAGSRV_CFG_RPRGDATA_SIGNATURE_POS],
                                            &DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_CHK_DATA_POS],
                                            DataLength);
    }

    DiagSrv_ClearFingerprintTempArea();
    Rte_Rpg_MemSet(DiagSrv_0x31_Chk_RprgDataBuff, 0U, sizeof(DiagSrv_0x31_Chk_RprgDataBuff));

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_CompareMemory                             */
/* Description   | Compare memory                                             */
/* Preconditions |                                                            */
/* Parameters    | [IN] Buf1 : Buffer1                                        */
/*               | [IN] Buf2 : Buffer2                                        */
/*               | [IN] Len  : Length                                         */
/* Return Value  | Result of compare                                          */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_CompareMemory
(
    CONST(uint8, AUTOMATIC) Buf1[],
    CONST(uint8, AUTOMATIC) Buf2[],
    VAR(uint16, AUTOMATIC) Len
)
{
    VAR(uint16, AUTOMATIC) Index;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_OK;

    for( Index = 0U; Index < Len; Index++ )
    {
        if( Buf1[Index] != Buf2[Index] )
        {
            Ret = E_NOT_OK;
            break;
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Chk_EndProcess                                */
/* Description   | End processing                                             */
/* Preconditions |                                                            */
/* Parameters    | [IN] Nrc : NRC                                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Chk_EndProcess
(
    VAR(uint8, AUTOMATIC) Nrc
)
{
    if( Nrc != DIAG_NRC_RCRRP )
    {
        DiagSrv_0x31_Chk_ClearInfo();
    }

    return;
}

#define DIAGSRV_STOP_SEC_CODE
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/07/05 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/
