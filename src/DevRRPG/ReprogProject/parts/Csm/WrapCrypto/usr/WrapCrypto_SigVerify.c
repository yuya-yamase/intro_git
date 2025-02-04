/* WrapCrypto_SigVerify_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | WrapCrypto/SigVerify/CODE                                   */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <WrapCrypto.h>
#include <Csm.h>
#include "WrapCrypto_Local.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define WRAPCRYPTO_START_SEC_VAR
#include <WrapCrypto_MemMap.h>

#define WRAPCRYPTO_STOP_SEC_VAR
#include <WrapCrypto_MemMap.h>

#define WRAPCRYPTO_START_SEC_VAR_SIGVERIFY_RET
#include <WrapCrypto_MemMap.h>

/*===== Sample ===============================================================*/
static VAR(Crypto_VerifyResultType, WRAPCRYPTO_VAR_CLEARED) WrapCrypto_VerifyResult;
/*===== Sample ===============================================================*/

#define WRAPCRYPTO_STOP_SEC_VAR_SIGVERIFY_RET
#include <WrapCrypto_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define WRAPCRYPTO_START_SEC_CST
#include <WrapCrypto_MemMap.h>


#define WRAPCRYPTO_STOP_SEC_CST
#include <WrapCrypto_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define WRAPCRYPTO_START_SEC_CODE
#include <WrapCrypto_MemMap.h>

/******************************************************************************/
/* Function Name | WrapCrypto_Pre_SigVerify                                   */
/* Description   | Prepare for signature verification                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] JobId : JobId                                         */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  WRAPCRYPTO_E_PENDING                                      */
/* Notes         | - Please implement signature verification preparation      */
/*               |   process according to Crypto package.                     */
/*               | - If the process has not completed, return                 */
/*               |   WRAPCRYPTO_E_PENDING. In that case, call it again with   */
/*               |   the same arguments.                                      */
/******************************************************************************/
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Pre_SigVerify
(
    VAR(uint32, AUTOMATIC) JobId
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

#if (WRAPCRYPTO_USE_CRYPTO_SW_83_SIGVERIFY == STD_ON)
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(WrapCrypto_JobInfoType, AUTOMATIC) CurrentJob;
    VAR(WrapCrypto_JobInfoType, AUTOMATIC) NextJob;

    Ret = E_NOT_OK;

    CurrentJob.Result = WRAPCRYPTO_JOB_FAILED;
    CurrentJob.Status = WRAPCRYPTO_STAT_IDLE;
    WrapCrypto_GetJobInfo(&CurrentJob);

    if( CurrentJob.Status == WRAPCRYPTO_STAT_IDLE )
    {
        FuncRet = Csm_SignatureVerify(JobId, CRYPTO_OPERATIONMODE_START,
                                    NULL_PTR, 0UL,
                                    NULL_PTR, 0UL,
                                    NULL_PTR);
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            /* Wait callout */
            Ret = WRAPCRYPTO_E_PENDING;

            NextJob.Result = WRAPCRYPTO_JOB_PENDING;
            NextJob.Status = WRAPCRYPTO_STAT_PRE_SIGVERIFY;
            WrapCrypto_UpdateJobInfo(&NextJob);
        }
    }
    else if( CurrentJob.Status == WRAPCRYPTO_STAT_PRE_SIGVERIFY )
    {
        /* Wait callout */
        Ret = WRAPCRYPTO_E_PENDING;
    }
    else if( CurrentJob.Status == WRAPCRYPTO_STAT_RESULT )
    {
        /* Callout result */
        if( CurrentJob.Result == WRAPCRYPTO_JOB_OK )
        {
            Ret = E_OK;
        }

        NextJob.Result = WRAPCRYPTO_JOB_FAILED;
        NextJob.Status = WRAPCRYPTO_STAT_IDLE;
        WrapCrypto_UpdateJobInfo(&NextJob);
    }
    else
    {
        /* No process */
    }
#else
    /* Sample                                       */
    /* This function does nothing because           */
    /* CRYPTO_OPERATIONMODE_START is specified      */
    /* when setting verify data for the first time. */
    Ret = E_OK;
#endif

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | WrapCrypto_SigVerify                                       */
/* Description   | Signature verification                                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] FirstData : 1st verification data                     */
/*               |       TRUE                                                 */
/*               |       FALSE                                                */
/*               | [IN] JobId     : JobId                                     */
/*               | [IN] Data      : Verification data                         */
/*               | [IN] DataSize  : Verification data size                    */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  WRAPCRYPTO_E_PENDING                                      */
/* Notes         | - Please implement signature verification process          */
/*               |   according to Crypto package.                             */
/*               | - If the process has not completed, return                 */
/*               |   WRAPCRYPTO_E_PENDING. In that case, call it again with   */
/*               |   the same arguments.                                      */
/*               | - The pointer arguments are arranged as follows.           */
/*               |    Data : RAM(SBL)/ROM(APL) address to rewrite.            */
/*               |           or, ".B_RAM_FSCDTCT_SIGTARGET_SHARED"            */
/******************************************************************************/
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_SigVerify
(
    VAR(boolean, AUTOMATIC) FirstData,
    VAR(uint32, AUTOMATIC) JobId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) Data,
    VAR(uint32, AUTOMATIC) DataSize
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(Crypto_OperationModeType, AUTOMATIC) Mode;
    VAR(WrapCrypto_JobInfoType, AUTOMATIC) CurrentJob;
    VAR(WrapCrypto_JobInfoType, AUTOMATIC) NextJob;

    Ret = E_NOT_OK;

    CurrentJob.Result = WRAPCRYPTO_JOB_FAILED;
    CurrentJob.Status = WRAPCRYPTO_STAT_IDLE;
    WrapCrypto_GetJobInfo(&CurrentJob);

    if( CurrentJob.Status == WRAPCRYPTO_STAT_IDLE )
    {
#if (WRAPCRYPTO_USE_CRYPTO_SW_83_SIGVERIFY == STD_ON)
        Mode = CRYPTO_OPERATIONMODE_UPDATE;
#else
        /* Sample                                       */
        /* CRYPTO_OPERATIONMODE_START specified         */
        /* when setting verify data for the first time. */
        Mode = CRYPTO_OPERATIONMODE_UPDATE;
        if( FirstData != (boolean)FALSE )
        {
            Mode = CRYPTO_OPERATIONMODE_START;
        }
#endif
        FuncRet = Csm_SignatureVerify(JobId, Mode,
                                    Data, DataSize,
                                    NULL_PTR, 0UL,
                                    NULL_PTR);
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            /* Wait callout */
            Ret = WRAPCRYPTO_E_PENDING;

            NextJob.Result = WRAPCRYPTO_JOB_PENDING;
            NextJob.Status = WRAPCRYPTO_STAT_SIGVERIFY;
            WrapCrypto_UpdateJobInfo(&NextJob);
        }
    }
    else if( CurrentJob.Status == WRAPCRYPTO_STAT_SIGVERIFY )
    {
        /* Wait callout */
        Ret = WRAPCRYPTO_E_PENDING;
    }
    else if( CurrentJob.Status == WRAPCRYPTO_STAT_RESULT )
    {
        /* Callout result */
        if( CurrentJob.Result == WRAPCRYPTO_JOB_OK )
        {
            Ret = E_OK;
        }

        NextJob.Result = WRAPCRYPTO_JOB_FAILED;
        NextJob.Status = WRAPCRYPTO_STAT_IDLE;
        WrapCrypto_UpdateJobInfo(&NextJob);
    }
    else
    {
        /* No process */
    }

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | WrapCrypto_Fin_SigVerify                                   */
/* Description   | Finish for signature verification                          */
/* Preconditions |                                                            */
/* Parameters    | [IN] JobId         : JobId                                 */
/*               | [IN] Signature     : Signature data                        */
/*               | [IN] SignatureSize : Signature data size                   */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  WRAPCRYPTO_E_PENDING                                      */
/*               |  WRAPCRYPTO_E_VERIFY                                       */
/* Notes         | - Please implement signature verification completion       */
/*               |   process according to Crypto package.                     */
/*               | - If the process has not completed, return                 */
/*               |   WRAPCRYPTO_E_PENDING. In that case, call it again with   */
/*               |   the same arguments.                                      */
/*               | - The pointer arguments are arranged as follows.           */
/*               |    Signature : ".B_RAM_FSCDTCT_SIGDATA_SHARED"             */
/******************************************************************************/
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Fin_SigVerify
(
    VAR(uint32, AUTOMATIC) JobId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) Signature,
    VAR(uint32, AUTOMATIC) SignatureSize
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(WrapCrypto_JobInfoType, AUTOMATIC) CurrentJob;
    VAR(WrapCrypto_JobInfoType, AUTOMATIC) NextJob;

    Ret = E_NOT_OK;

    CurrentJob.Result = WRAPCRYPTO_JOB_FAILED;
    CurrentJob.Status = WRAPCRYPTO_STAT_IDLE;
    WrapCrypto_GetJobInfo(&CurrentJob);

    if( CurrentJob.Status == WRAPCRYPTO_STAT_IDLE )
    {
        WrapCrypto_VerifyResult = CRYPTO_E_VER_NOT_OK;

        FuncRet = Csm_SignatureVerify(JobId, CRYPTO_OPERATIONMODE_FINISH,
                                    NULL_PTR, 0UL,
                                    Signature, SignatureSize,
                                    &WrapCrypto_VerifyResult);
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            /* Wait callout */
            Ret = WRAPCRYPTO_E_PENDING;

            NextJob.Result = WRAPCRYPTO_JOB_PENDING;
            NextJob.Status = WRAPCRYPTO_STAT_FIN_SIGVERIFY;
            WrapCrypto_UpdateJobInfo(&NextJob);
        }
    }
    else if( CurrentJob.Status == WRAPCRYPTO_STAT_FIN_SIGVERIFY )
    {
        /* Wait callout */
        Ret = WRAPCRYPTO_E_PENDING;
    }
    else if( CurrentJob.Status == WRAPCRYPTO_STAT_RESULT )
    {
        /* Callout result */
        if( CurrentJob.Result == WRAPCRYPTO_JOB_OK )
        {
            Ret = E_OK;
        }
        else if( CurrentJob.Result == WRAPCRYPTO_JOB_VERIFYERR )
        {
            Ret = WRAPCRYPTO_E_VERIFY;
        }
        else
        {
            /* No process */
        }

        NextJob.Result = WRAPCRYPTO_JOB_FAILED;
        NextJob.Status = WRAPCRYPTO_STAT_IDLE;
        WrapCrypto_UpdateJobInfo(&NextJob);
    }
    else
    {
        /* No process */
    }

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | WrapCrypto_SigVerifyCallout                                */
/* Description   | Callout function for signature verification                */
/* Preconditions |                                                            */
/* Parameters    | [IN] jobId  : JobId                                        */
/*               | [IN] result : Result of Csm_SignatureVerify()              */
/* Return Value  | None                                                       */
/* Notes         | - Please implement callout process according to Crypto     */
/*               |   package.                                                 */
/*               | - This function is set to CsmCallbackFunc in Csm config.   */
/******************************************************************************/
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_SigVerifyCallout
(
    VAR(uint32, AUTOMATIC) jobId,
    VAR(Crypto_ResultType, AUTOMATIC) result
)
{
/*===== Sample ===============================================================*/
    VAR(WrapCrypto_JobInfoType, AUTOMATIC) CurrentJob;
    VAR(WrapCrypto_JobInfoType, AUTOMATIC) NextJob;

    CurrentJob.Result = WRAPCRYPTO_JOB_FAILED;
    CurrentJob.Status = WRAPCRYPTO_STAT_IDLE;
    WrapCrypto_GetJobInfo(&CurrentJob);

    if( ((CurrentJob.Status == WRAPCRYPTO_STAT_PRE_SIGVERIFY) && (result == (Crypto_ResultType)E_OK)) ||
        ((CurrentJob.Status == WRAPCRYPTO_STAT_SIGVERIFY) && (result == (Crypto_ResultType)E_OK)) )
    {
        NextJob.Result = WRAPCRYPTO_JOB_OK;
        NextJob.Status = WRAPCRYPTO_STAT_RESULT;
    }
    else if( (CurrentJob.Status == WRAPCRYPTO_STAT_FIN_SIGVERIFY) && (result == (Crypto_ResultType)E_OK) )
    {
        if( WrapCrypto_VerifyResult == (Crypto_VerifyResultType)CRYPTO_E_VER_OK )
        {
            NextJob.Result = WRAPCRYPTO_JOB_OK;
            NextJob.Status = WRAPCRYPTO_STAT_RESULT;
        }
        else
        {
            NextJob.Result = WRAPCRYPTO_JOB_VERIFYERR;
            NextJob.Status = WRAPCRYPTO_STAT_RESULT;
        }
    }
    else
    {
        NextJob.Result = WRAPCRYPTO_JOB_FAILED;
        NextJob.Status = WRAPCRYPTO_STAT_RESULT;
    }

    WrapCrypto_UpdateJobInfo(&NextJob);
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/


#define WRAPCRYPTO_STOP_SEC_CODE
#include <WrapCrypto_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

