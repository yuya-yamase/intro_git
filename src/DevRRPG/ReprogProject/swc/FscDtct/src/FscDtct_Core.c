/* FscDtct_Core_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | FscDtct/Core/CODE                                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <RpgLib.h>
#include <Rte.h>
#include <WrapCrypto.h>

#include <FscDtct.h>
#include "FscDtct_Local.h"
#include "FscDtct_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define FSCDTCT_STAT_IDLE                       ((uint8)0x00U)
#define FSCDTCT_STAT_PRE_VERIFY                 ((uint8)0x11U)
#define FSCDTCT_STAT_PRE_VERIFY_FINISH          ((uint8)0x12U)
#define FSCDTCT_STAT_READ_EXTROM                ((uint8)0x21U)
#define FSCDTCT_STAT_VERIFY                     ((uint8)0x22U)
#define FSCDTCT_STAT_VERIFY_FINISH              ((uint8)0x23U)
#define FSCDTCT_STAT_POST_VERIFY                ((uint8)0x31U)

#define FSCDTCT_READBUF_SIZE                    ((uint32)512UL)
#define FSCDTCT_SIGVERIFY_MAX_SIZE              ((uint32)4096UL)

#define FSCDTCT_STATUSMATRIXTBL_NUM             (sizeof(FscDtct_StatusMatrixTbl) / sizeof(FscDtct_StatusMatrixTbl[0]))

#define FSCDTCT_API_ID_INIT                     ((uint8)0x00U)

#define FSCDTCT_E_CASE_KEY_SET_FAIL             ((uint8)0x01U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint8 LocalStatus;
    uint8 JobResult;
} FscDtct_JobInfoType;

typedef struct {
    uint8 LocalStatus;
    uint8 RetStatus;
} FscDtct_StatusMatrixType;

typedef struct {
    uint32 Num;
    P2CONST(FscDtct_StatusMatrixType, TYPEDEF, FSCDTCT_APPL_CONST) MatrixPtr;
} FscDtct_StatusMatrixInfoType;

typedef struct {
    uint32 TargetAddr;
    uint32 TargetRemainSize;
    uint8 TargetDevice;
    boolean FirstDataFlag;
} FscDtct_SigVerifyInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_Main_ReqPreSigVerify (void);
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_Main_ReqSigVerify (void);
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_Main_ReqReadExtRom (void);
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_Main_ReqPostSigVerify (void);
static FUNC(Std_ReturnType, FSCDTCT_CODE_FAST) FscDtct_ReadExtRom (void);
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_ClearSignatureVerifyInformation (void);
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_FailureProc (void);
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_UpdateJobInfo
(
    VAR(uint8, AUTOMATIC) JobResult,
    VAR(uint8, AUTOMATIC) LocalStatus
);
static FUNC(Std_ReturnType, FSCDTCT_CODE_FAST) FscDtct_GetApiAcceptation (void);
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_ReleaseApiAcceptation (void);
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define FSCDTCT_START_SEC_VAR
#include <FscDtct_MemMap.h>

static VAR(FscDtct_SigVerifyInfoType, FSCDTCT_VAR_CLEARED) FscDtct_SigVerifyInfo;
static VAR(FscDtct_JobInfoType, FSCDTCT_VAR_CLEARED) FscDtct_JobInfo;
static VAR(uint8, FSCDTCT_VAR_CLEARED) FscDtct_ApiAcceptingFlg;

#define FSCDTCT_STOP_SEC_VAR
#include <FscDtct_MemMap.h>

#define FSCDTCT_START_SEC_VAR_SIG_TARGET
#include <FscDtct_MemMap.h>

static VAR(uint8, FSCDTCT_VAR_CLEARED) FscDtct_ReadMemBuf[FSCDTCT_READBUF_SIZE];

#define FSCDTCT_STOP_SEC_VAR_SIG_TARGET
#include <FscDtct_MemMap.h>

#define FSCDTCT_START_SEC_VAR_SIG_DATA
#include <FscDtct_MemMap.h>

static VAR(uint8, FSCDTCT_VAR_CLEARED) FscDtct_SigData[FSCDTCT_CFG_SIGNATURE_SIZE];

#define FSCDTCT_STOP_SEC_VAR_SIG_DATA
#include <FscDtct_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define FSCDTCT_START_SEC_CST
#include <FscDtct_MemMap.h>

static CONST(FscDtct_StatusMatrixType, FSCDTCT_CONST) FscDtct_StatusMatrixTbl[] = {
     { FSCDTCT_STAT_IDLE,               FSCDTCT_IDLE    }
    ,{ FSCDTCT_STAT_PRE_VERIFY,         FSCDTCT_BUSY    }
    ,{ FSCDTCT_STAT_PRE_VERIFY_FINISH,  FSCDTCT_IDLE    }
    ,{ FSCDTCT_STAT_READ_EXTROM,        FSCDTCT_BUSY    }
    ,{ FSCDTCT_STAT_VERIFY,             FSCDTCT_BUSY    }
    ,{ FSCDTCT_STAT_VERIFY_FINISH,      FSCDTCT_IDLE    }
    ,{ FSCDTCT_STAT_POST_VERIFY,        FSCDTCT_BUSY    }
};

static CONST(AB_83_ConstV FscDtct_StatusMatrixInfoType, FSCDTCT_CONST) FscDtct_StatusMatrixInfo = {
    FSCDTCT_STATUSMATRIXTBL_NUM,
    &FscDtct_StatusMatrixTbl[0]
};

#define FSCDTCT_STOP_SEC_CST
#include <FscDtct_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define FSCDTCT_START_SEC_CODE
#include <FscDtct_MemMap.h>

/******************************************************************************/
/* Function Name | FscDtct_Init                                               */
/* Description   | Initializes FscDtct                                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, FSCDTCT_CODE_SLOW) FscDtct_Init (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(uint8, AUTOMATIC) SignatureKeyData[FSCDTCT_CFG_SIGNATUREKEY_SIZE];

    FscDtct_ClearSignatureVerifyInformation();
    FscDtct_UpdateJobInfo(FSCDTCT_JOB_OK, FSCDTCT_STAT_IDLE);

    FscDtct_ApiAcceptingFlg = STD_OFF;

    if( FscDtct_SignatureKeyConfig.KeyPreRegistered == (uint8)STD_OFF )
    {
        /* Register Signature Verification Key in CSM */
        Rte_Rpg_MemSet(SignatureKeyData, 0U, sizeof(SignatureKeyData));
        FscDtct_Usr_Get_SignatureKey(FscDtct_SignatureKeyConfig.SignatureKeyPtr,
                                    FscDtct_SignatureKeyConfig.SignatureKeySize,
                                    SignatureKeyData);
        FuncRet = WrapCrypto_Set_SigVerifyKey(FscDtct_SignatureKeyConfig.KeyID,
                                            SignatureKeyData,
                                            sizeof(SignatureKeyData));
        if( FuncRet != (Std_ReturnType)E_OK )
        {
            FscDtct_ReportError(FSCDTCT_API_ID_INIT, FSCDTCT_E_CASE_KEY_SET_FAIL);
        }

        Rte_Rpg_MemSet(SignatureKeyData, 0U, sizeof(SignatureKeyData));
    }

    return;
}

/******************************************************************************/
/* Function Name | FscDtct_DeInit                                             */
/* Description   | Deinitializes FscDtct                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, FSCDTCT_CODE_SLOW) FscDtct_DeInit (void)
{
    FscDtct_UpdateJobInfo(FSCDTCT_JOB_OK, FSCDTCT_STAT_IDLE);
    FscDtct_ClearSignatureVerifyInformation();

    FscDtct_ApiAcceptingFlg = STD_OFF;

    return;
}

/******************************************************************************/
/* Function Name | FscDtct_Time                                               */
/* Description   | TimeFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, FSCDTCT_CODE_SLOW) FscDtct_Time (void)
{
    return;
}

/******************************************************************************/
/* Function Name | FscDtct_MainFunction                                       */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, FSCDTCT_CODE_SLOW) FscDtct_MainFunction (void)
{
    if( FscDtct_JobInfo.LocalStatus == FSCDTCT_STAT_PRE_VERIFY )
    {
        FscDtct_Main_ReqPreSigVerify();
    }
    else if( FscDtct_JobInfo.LocalStatus == FSCDTCT_STAT_VERIFY )
    {
        FscDtct_Main_ReqSigVerify();
    }
    else if( FscDtct_JobInfo.LocalStatus == FSCDTCT_STAT_READ_EXTROM )
    {
        FscDtct_Main_ReqReadExtRom();
    }
    else if( FscDtct_JobInfo.LocalStatus == FSCDTCT_STAT_POST_VERIFY )
    {
        FscDtct_Main_ReqPostSigVerify();
    }
    else
    {
        /* No process */
    }

    return;
}

/******************************************************************************/
/* Function Name | FscDtct_GetStatus                                          */
/* Description   | Acquires status of job                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Status                                                     */
/*               |  FSCDTCT_IDLE                                              */
/*               |  FSCDTCT_BUSY                                              */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, FSCDTCT_CODE_SLOW) FscDtct_GetStatus (void)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) Status;

    Status = FSCDTCT_BUSY;

    for( i = 0UL; i < FscDtct_StatusMatrixInfo.Num; i++ )
    {
        if( FscDtct_JobInfo.LocalStatus == FscDtct_StatusMatrixInfo.MatrixPtr[i].LocalStatus )
        {
            Status = FscDtct_StatusMatrixInfo.MatrixPtr[i].RetStatus;
            break;
        }
    }

    return Status;
}

/******************************************************************************/
/* Function Name | FscDtct_GetJobResult                                       */
/* Description   | Acquires result of job                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | JobResult                                                  */
/*               |  FSCDTCT_JOB_OK                                            */
/*               |  FSCDTCT_JOB_FAILED                                        */
/*               |  FSCDTCT_JOB_PENDING                                       */
/*               |  FSCDTCT_JOB_VERIFYERR                                     */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, FSCDTCT_CODE_SLOW) FscDtct_GetJobResult (void)
{
    return FscDtct_JobInfo.JobResult;
}

/******************************************************************************/
/* Function Name | FscDtct_ReqPreSigVerify                                    */
/* Description   | Prepares Signature Verify                                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, FSCDTCT_CODE_SLOW) FscDtct_ReqPreSigVerify (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = FscDtct_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( FscDtct_JobInfo.LocalStatus == FSCDTCT_STAT_IDLE )
        {
            FscDtct_UpdateJobInfo(FSCDTCT_JOB_PENDING, FSCDTCT_STAT_PRE_VERIFY);
        }
        else
        {
            FscDtct_FailureProc();
        }

        FscDtct_ReleaseApiAcceptation();
    }

    return;
}

/******************************************************************************/
/* Function Name | FscDtct_ReqPostSigVerify                                   */
/* Description   | Completes Signature Verify                                 */
/* Preconditions |                                                            */
/* Parameters    | [IN] SignatureAddr : Signature address                     */
/*               | [IN] SignatureSize : Signature size                        */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, FSCDTCT_CODE_SLOW) FscDtct_ReqPostSigVerify
(
    P2CONST(uint8, AUTOMATIC, FSCDTCT_APPL_CONST) SignatureAddr,
    VAR(uint32, AUTOMATIC) SignatureSize
)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = FscDtct_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( (FscDtct_JobInfo.LocalStatus == FSCDTCT_STAT_VERIFY_FINISH) &&
            ((SignatureAddr != NULL_PTR) && (SignatureSize == sizeof(FscDtct_SigData))) )
        {
            /* Copy signature to aligned buffer */
            Rte_Rpg_MemCopy(FscDtct_SigData, SignatureAddr, sizeof(FscDtct_SigData));

            FscDtct_UpdateJobInfo(FSCDTCT_JOB_PENDING, FSCDTCT_STAT_POST_VERIFY);
        }
        else
        {
            /* Status error or cancel(called at SignatureAddr=NULL_PTR, SignatureSize=0) */
            FscDtct_FailureProc();
        }

        FscDtct_ReleaseApiAcceptation();
    }

    return;
}

/******************************************************************************/
/* Function Name | FscDtct_ReqSigVerify                                       */
/* Description   | Requests SignatureVerify                                   */
/* Preconditions |                                                            */
/* Parameters    | [IN] TargetAddress : Target address                        */
/*               | [IN] TargetSize    : Target size                           */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, FSCDTCT_CODE_SLOW) FscDtct_ReqSigVerify
(
    VAR(uint32, AUTOMATIC) TargetAddress,
    VAR(uint32, AUTOMATIC) TargetSize
)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(uint8, AUTOMATIC) ErrFlag;

    FuncRet = FscDtct_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        ErrFlag = STD_ON;

        if( (FscDtct_JobInfo.LocalStatus == FSCDTCT_STAT_PRE_VERIFY_FINISH) ||
            (FscDtct_JobInfo.LocalStatus == FSCDTCT_STAT_VERIFY_FINISH) )
        {
            FuncRet = RpgLib_CnvPhysicalAddr(RPGLIB_MEMORYID_0,
                                            TargetAddress,
                                            &FscDtct_SigVerifyInfo.TargetAddr,
                                            &FscDtct_SigVerifyInfo.TargetDevice);
            if( FuncRet == (Std_ReturnType)E_OK )
            {
                FscDtct_SigVerifyInfo.TargetRemainSize = TargetSize;

                if( FscDtct_SigVerifyInfo.TargetDevice == RPGLIB_DEVICE_TYPE_EXTCODEFLS )
                {
                    /* ExtROM cannot be verified directly, so read the data to RAM. */
                    FscDtct_SigVerifyInfo.TargetAddr = TargetAddress;

                    FuncRet = FscDtct_ReadExtRom();
                    if( FuncRet == (Std_ReturnType)E_OK )
                    {
                        FscDtct_UpdateJobInfo(FSCDTCT_JOB_PENDING, FSCDTCT_STAT_READ_EXTROM);
                        ErrFlag = STD_OFF;
                    }
                }
                else
                {
                    FscDtct_UpdateJobInfo(FSCDTCT_JOB_PENDING, FSCDTCT_STAT_VERIFY);
                    ErrFlag = STD_OFF;
                }
            }
        }

        if( ErrFlag == (uint8)STD_ON )
        {
            FscDtct_FailureProc();
        }

        FscDtct_ReleaseApiAcceptation();
    }

    return;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | FscDtct_Main_ReqPreSigVerify                               */
/* Description   | MainFunction of FSCDTCT_STAT_PRE_VERIFY                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_Main_ReqPreSigVerify (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = WrapCrypto_Pre_SigVerify(FscDtct_SignatureKeyConfig.JobID);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        FscDtct_SigVerifyInfo.FirstDataFlag = TRUE;
        FscDtct_UpdateJobInfo(FSCDTCT_JOB_OK, FSCDTCT_STAT_PRE_VERIFY_FINISH);
    }
    else if( FuncRet == WRAPCRYPTO_E_PENDING )
    {
        /* No Process */
    }
    else
    {
        FscDtct_FailureProc();
    }

    return;
}

/******************************************************************************/
/* Function Name | FscDtct_Main_ReqSigVerify                                  */
/* Description   | MainFunction of FSCDTCT_STAT_VERIFY                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_Main_ReqSigVerify (void)
{
    P2CONST(uint8, AUTOMATIC, FSCDTCT_APPL_CONST) RequestAddr;
    VAR(uint32, AUTOMATIC) RequestSize;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    RequestSize = FscDtct_SigVerifyInfo.TargetRemainSize;

    if( FscDtct_SigVerifyInfo.TargetDevice == RPGLIB_DEVICE_TYPE_EXTCODEFLS )
    {
        if( FscDtct_SigVerifyInfo.TargetRemainSize >= sizeof(FscDtct_ReadMemBuf) )
        {
            RequestSize = sizeof(FscDtct_ReadMemBuf);
        }
        RequestAddr = FscDtct_ReadMemBuf;
    }
    else
    {
        if( FscDtct_SigVerifyInfo.TargetRemainSize >= FSCDTCT_SIGVERIFY_MAX_SIZE )
        {
            RequestSize = FSCDTCT_SIGVERIFY_MAX_SIZE;
        }
        RequestAddr = (const uint8 *)FscDtct_SigVerifyInfo.TargetAddr;
    }

    FuncRet = WrapCrypto_SigVerify(FscDtct_SigVerifyInfo.FirstDataFlag,
                                FscDtct_SignatureKeyConfig.JobID,
                                RequestAddr,
                                RequestSize);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        FscDtct_SigVerifyInfo.FirstDataFlag = FALSE;
        FscDtct_SigVerifyInfo.TargetAddr += RequestSize;        /* no wrap around */
        FscDtct_SigVerifyInfo.TargetRemainSize -= RequestSize;  /* no wrap around */

        if( FscDtct_SigVerifyInfo.TargetRemainSize == (uint32)0UL )
        {
            FscDtct_UpdateJobInfo(FSCDTCT_JOB_OK, FSCDTCT_STAT_VERIFY_FINISH);
        }
        else
        {
            if( FscDtct_SigVerifyInfo.TargetDevice == RPGLIB_DEVICE_TYPE_EXTCODEFLS )
            {
                /* ExtROM cannot be verified directly, so read the data to RAM. */
                FuncRet = FscDtct_ReadExtRom();
                if( FuncRet == (Std_ReturnType)E_OK )
                {
                    FscDtct_UpdateJobInfo(FSCDTCT_JOB_PENDING, FSCDTCT_STAT_READ_EXTROM);
                }
                else
                {
                    FscDtct_FailureProc();
                }
            }
            else
            {
                FscDtct_UpdateJobInfo(FSCDTCT_JOB_PENDING, FSCDTCT_STAT_VERIFY);
            }
        }
    }
    else if( FuncRet == WRAPCRYPTO_E_PENDING )
    {
        /* No Process */
    }
    else
    {
        FscDtct_FailureProc();
    }

    return;
}

/******************************************************************************/
/* Function Name | FscDtct_Main_ReqReadExtRom                                 */
/* Description   | MainFunction of FSCDTCT_STAT_READ_EXTROM                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_Main_ReqReadExtRom (void)
{
    VAR(uint8, AUTOMATIC) RpgLibStatus;
    VAR(uint8, AUTOMATIC) RpgLibJobResult;
    VAR(uint8, AUTOMATIC) ErrFlag;

    ErrFlag = STD_ON;

    RpgLibStatus = RpgLib_GetStatus();
    if( RpgLibStatus == RPGLIB_IDLE )
    {
        RpgLibJobResult = RpgLib_GetJobResult();
        if( RpgLibJobResult == RPGLIB_JOB_OK )
        {
            FscDtct_UpdateJobInfo(FSCDTCT_JOB_PENDING, FSCDTCT_STAT_VERIFY);
            ErrFlag = STD_OFF;
        }
    }
    else if( RpgLibStatus == RPGLIB_BUSY )
    {
        ErrFlag = STD_OFF;
    }
    else
    {
        /* No process */
    }

    if( ErrFlag == (uint8)STD_ON )
    {
        FscDtct_FailureProc();
    }

    return;
}

/******************************************************************************/
/* Function Name | FscDtct_Main_ReqPostSigVerify                              */
/* Description   | MainFunction of FSCDTCT_STAT_POST_VERIFY                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_Main_ReqPostSigVerify (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = WrapCrypto_Fin_SigVerify(FscDtct_SignatureKeyConfig.JobID,
                                FscDtct_SigData,
                                sizeof(FscDtct_SigData));
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        FscDtct_ClearSignatureVerifyInformation();
        FscDtct_UpdateJobInfo(FSCDTCT_JOB_OK, FSCDTCT_STAT_IDLE);
    }
    else if( FuncRet == WRAPCRYPTO_E_PENDING )
    {
        /* No process */
    }
    else if( FuncRet == WRAPCRYPTO_E_VERIFY )
    {
        FscDtct_ClearSignatureVerifyInformation();
        FscDtct_UpdateJobInfo(FSCDTCT_JOB_VERIFYERR, FSCDTCT_STAT_IDLE);
    }
    else
    {
        FscDtct_FailureProc();
    }

    return;
}

/******************************************************************************/
/* Function Name | FscDtct_ReadExtRom                                         */
/* Description   | Read ExtCodeFls                                            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, FSCDTCT_CODE_FAST) FscDtct_ReadExtRom (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(uint32, AUTOMATIC) ReadSize;

    ReadSize = FscDtct_SigVerifyInfo.TargetRemainSize;
    if( ReadSize >= sizeof(FscDtct_ReadMemBuf) )
    {
        ReadSize = sizeof(FscDtct_ReadMemBuf);
    }

    Ret = RpgLib_ReqMemRead(RPGLIB_MEMORYID_0,
                            FscDtct_ReadMemBuf,
                            FscDtct_SigVerifyInfo.TargetAddr,
                            ReadSize);

    return Ret;
}

/******************************************************************************/
/* Function Name | FscDtct_ClearSignatureVerifyInformation                    */
/* Description   | Clears Signature verification information                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_ClearSignatureVerifyInformation (void)
{
    FscDtct_SigVerifyInfo.TargetAddr = 0UL;
    FscDtct_SigVerifyInfo.TargetRemainSize = 0UL;
    FscDtct_SigVerifyInfo.TargetDevice = RPGLIB_DEVICE_TYPE_CODEFLS;
    FscDtct_SigVerifyInfo.FirstDataFlag = FALSE;

    Rte_Rpg_MemSet(FscDtct_ReadMemBuf, 0U, sizeof(FscDtct_ReadMemBuf));
    Rte_Rpg_MemSet(FscDtct_SigData, 0U, sizeof(FscDtct_SigData));

    return;
}

/******************************************************************************/
/* Function Name | FscDtct_FailureProc                                        */
/* Description   | Failure process                                            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_FailureProc (void)
{
    FscDtct_ClearSignatureVerifyInformation();

    FscDtct_UpdateJobInfo(FSCDTCT_JOB_FAILED, FSCDTCT_STAT_IDLE);

    return;
}

/******************************************************************************/
/* Function Name | FscDtct_UpdateJobInfo                                      */
/* Description   | Updates JobInfo                                            */
/* Preconditions |                                                            */
/* Parameters    | [IN] JobResult   : Result of job                           */
/*               |       FSCDTCT_JOB_OK                                       */
/*               |       FSCDTCT_JOB_FAILED                                   */
/*               |       FSCDTCT_JOB_PENDING                                  */
/*               |       FSCDTCT_JOB_VERIFYERR                                */
/*               | [IN] LocalStatus : Local status                            */
/*               |       FSCDTCT_STAT_IDLE                                    */
/*               |       FSCDTCT_STAT_PRE_VERIFY                              */
/*               |       FSCDTCT_STAT_PRE_VERIFY_FINISH                       */
/*               |       FSCDTCT_STAT_READ_EXTROM                             */
/*               |       FSCDTCT_STAT_VERIFY                                  */
/*               |       FSCDTCT_STAT_VERIFY_FINISH                           */
/*               |       FSCDTCT_STAT_POST_VERIFY                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_UpdateJobInfo
(
    VAR(uint8, AUTOMATIC) JobResult,
    VAR(uint8, AUTOMATIC) LocalStatus
)
{
    VAR(uint8, AUTOMATIC) MaskPattern;

    MaskPattern = Rte_MaskInterruptAll();   /* for JobResult/LocalStatus */
    FscDtct_JobInfo.JobResult = JobResult;
    FscDtct_JobInfo.LocalStatus = LocalStatus;
    Rte_UnMaskInterruptAll(MaskPattern);    /* for JobResult/LocalStatus */

    return;
}

/******************************************************************************/
/* Function Name | FscDtct_GetApiAcceptation                                  */
/* Description   | Acquires the acceptation of executing API                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, FSCDTCT_CODE_FAST) FscDtct_GetApiAcceptation (void)
{
    VAR(uint8, AUTOMATIC) MaskPattern;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    MaskPattern = Rte_MaskInterruptAll();   /* prevent multiple execution */
    if( FscDtct_ApiAcceptingFlg == (uint8)STD_OFF )
    {
        FscDtct_ApiAcceptingFlg = STD_ON;
        Ret = E_OK;
    }
    Rte_UnMaskInterruptAll(MaskPattern);    /* prevent multiple execution */

    return Ret;
}

/******************************************************************************/
/* Function Name | FscDtct_ReleaseApiAcceptation                              */
/* Description   | Releases the acceptation of executing API                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_ReleaseApiAcceptation (void)
{
    FscDtct_ApiAcceptingFlg = STD_OFF;

    return;
}

/******************************************************************************/
/* Function Name | FscDtct_ReportError                                        */
/* Description   | Report the error information                               */
/* Preconditions |                                                            */
/* Parameters    | [IN] ApiId   : API ID                                      */
/*               | [IN] ErrorId : Error ID                                    */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, FSCDTCT_CODE_FAST) FscDtct_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
)
{
    VAR(Rte_EcuM_ErrorType, AUTOMATIC) Error;

    Error.ModuleId = RTE_ECUM_MODULE_FSCDTCT;
    Error.ApiId = ApiId;
    Error.ErrorId = ErrorId;

    Rte_EcuM_ReportError(&Error);

    return;
}

#define FSCDTCT_STOP_SEC_CODE
#include <FscDtct_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

