/* WrapCrypto_Decrypt_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | WrapCrypto/Decrypt/CODE                                     */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <WrapCrypto.h>
#include <Csm.h>
#include "WrapCrypto_Local.h"

/*===== Sample ===============================================================*/
#include <Sys.h>
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
#if (WRAPCRYPTO_USE_CRYPTO_SW_83_DECRYPT != STD_ON)
#define WRAPCRYPTO_DECRYPT_DUMMY_BUFF_SIZE      ((uint8)16U)
#endif
/*===== Sample ===============================================================*/


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

#define WRAPCRYPTO_START_SEC_VAR_DECRYPT_DUMMY_BUFF
#include <WrapCrypto_MemMap.h>

/*===== Sample ===============================================================*/
#if (WRAPCRYPTO_USE_CRYPTO_SW_83_DECRYPT != STD_ON)
static VAR(uint8, WRAPCRYPTO_VAR_CLEARED) WrapCrypto_DummyBuffer[WRAPCRYPTO_DECRYPT_DUMMY_BUFF_SIZE];
#endif
/*===== Sample ===============================================================*/

#define WRAPCRYPTO_STOP_SEC_VAR_DECRYPT_DUMMY_BUFF
#include <WrapCrypto_MemMap.h>

#define WRAPCRYPTO_START_SEC_VAR_DECRYPT_DUMMY_SIZE
#include <WrapCrypto_MemMap.h>

/*===== Sample ===============================================================*/
#if (WRAPCRYPTO_USE_CRYPTO_SW_83_DECRYPT != STD_ON)
static VAR(uint32, WRAPCRYPTO_VAR_CLEARED) WrapCrypto_DummyResultSize;
#endif
/*===== Sample ===============================================================*/

#define WRAPCRYPTO_STOP_SEC_VAR_DECRYPT_DUMMY_SIZE
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
/* Function Name | WrapCrypto_Pre_Decrypt                                     */
/* Description   | Prepare for decryption                                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] JobId : JobId                                         */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  WRAPCRYPTO_E_PENDING                                      */
/* Notes         | - Please implement decryption preparation process          */
/*               |   according to Crypto package.                             */
/*               | - If the process has not completed, return                 */
/*               |   WRAPCRYPTO_E_PENDING. In that case, call it again with   */
/*               |   the same arguments.                                      */
/******************************************************************************/
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Pre_Decrypt
(
    VAR(uint32, AUTOMATIC) JobId
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

#if (WRAPCRYPTO_USE_CRYPTO_SW_83_DECRYPT == STD_ON)
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(WrapCrypto_JobInfoType, AUTOMATIC) CurrentJob;
    VAR(WrapCrypto_JobInfoType, AUTOMATIC) NextJob;

    Ret = E_NOT_OK;

    CurrentJob.Result = WRAPCRYPTO_JOB_FAILED;
    CurrentJob.Status = WRAPCRYPTO_STAT_IDLE;
    WrapCrypto_GetJobInfo(&CurrentJob);

    if( CurrentJob.Status == WRAPCRYPTO_STAT_IDLE )
    {
        FuncRet = Csm_Decrypt(JobId, CRYPTO_OPERATIONMODE_START,
                            NULL_PTR, 0UL,
                            NULL_PTR, NULL_PTR);
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            /* Wait callout */
            Ret = WRAPCRYPTO_E_PENDING;

            NextJob.Result = WRAPCRYPTO_JOB_PENDING;
            NextJob.Status = WRAPCRYPTO_STAT_PRE_DECRYPT;
            WrapCrypto_UpdateJobInfo(&NextJob);
        }
    }
    else if( CurrentJob.Status == WRAPCRYPTO_STAT_PRE_DECRYPT )
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
/* Function Name | WrapCrypto_Decrypt                                         */
/* Description   | Decryption                                                 */
/* Preconditions |                                                            */
/* Parameters    | [IN]    FirstData      : 1st verification data             */
/*               |          TRUE                                              */
/*               |          FALSE                                             */
/*               | [IN]    JobId          : JobId                             */
/*               | [IN]    Ciphertext     : Ciphertext                        */
/*               | [IN]    CiphertextSize : Ciphertext size                   */
/*               | [OUT]   Plaintext      : Plaintext                         */
/*               | [INOUT] PlaintextSize  : IN  : Plaintext buffer size       */
/*               |                          OUT : Decrypted plaintext size    */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  WRAPCRYPTO_E_PENDING                                      */
/* Notes         | - Please implement decryption process according to         */
/*               |   Crypto package.                                          */
/*               | - If the process has not completed, return                 */
/*               |   WRAPCRYPTO_E_PENDING. In that case, call it again with   */
/*               |   the same arguments.                                      */
/*               | - The pointer arguments are arranged as follows.           */
/*               |    Ciphertext    : ".B_RAM_DECRYPT_CIPHER_SHARED"          */
/*               |    Plaintext     : ".B_RAM_DECRYPT_PLAIN_SHARED"           */
/*               |    PlaintextSize : ".B_RAM_DECRYPT_PLAINSIZE_SHARED"       */
/******************************************************************************/
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Decrypt
(
    VAR(boolean, AUTOMATIC) FirstData,
    VAR(uint32, AUTOMATIC) JobId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) Ciphertext,
    VAR(uint32, AUTOMATIC) CiphertextSize,
    P2VAR(uint8, AUTOMATIC, WRAPCRYPTO_APPL_DATA) Plaintext,
    P2VAR(uint32, AUTOMATIC, WRAPCRYPTO_APPL_DATA) PlaintextSize
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
#if (WRAPCRYPTO_USE_CRYPTO_SW_83_DECRYPT == STD_ON)
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
        FuncRet = Csm_Decrypt(JobId, Mode,
                            Ciphertext, CiphertextSize,
                            Plaintext, PlaintextSize);
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            /* Wait callout */
            Ret = WRAPCRYPTO_E_PENDING;

            NextJob.Result = WRAPCRYPTO_JOB_PENDING;
            NextJob.Status = WRAPCRYPTO_STAT_DECRYPT;
            WrapCrypto_UpdateJobInfo(&NextJob);
        }
    }
    else if( CurrentJob.Status == WRAPCRYPTO_STAT_DECRYPT )
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
/* Function Name | WrapCrypto_Fin_Decrypt                                     */
/* Description   | Finish for decryption                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] JobId : JobId                                         */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  WRAPCRYPTO_E_PENDING                                      */
/* Notes         | - Please implement decryption completion process according */
/*               |   to Crypto package.                                       */
/*               | - If the process has not completed, return                 */
/*               |   WRAPCRYPTO_E_PENDING. In that case, call it again with   */
/*               |   the same arguments.                                      */
/******************************************************************************/
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Fin_Decrypt
(
    VAR(uint32, AUTOMATIC) JobId
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(WrapCrypto_JobInfoType, AUTOMATIC) CurrentJob;
    VAR(WrapCrypto_JobInfoType, AUTOMATIC) NextJob;
    P2VAR(uint8, AUTOMATIC, WRAPCRYPTO_APPL_DATA) ResultPtr;
    P2VAR(uint32, AUTOMATIC, WRAPCRYPTO_APPL_DATA) ResultLengthPtr;

    Ret = E_NOT_OK;

    CurrentJob.Result = WRAPCRYPTO_JOB_FAILED;
    CurrentJob.Status = WRAPCRYPTO_STAT_IDLE;
    WrapCrypto_GetJobInfo(&CurrentJob);

    if( CurrentJob.Status == WRAPCRYPTO_STAT_IDLE )
    {
#if (WRAPCRYPTO_USE_CRYPTO_SW_83_DECRYPT == STD_ON)
        ResultPtr = NULL_PTR;
        ResultLengthPtr = NULL_PTR;
#else
        /* Sample                                                     */
        /* When specifying CRYPTO_OPERATIONMODE_FINISH,               */
        /* do not specify NULL_PTR for resultPtr and resultLengthPtr. */
        Rpg_MemSet(WrapCrypto_DummyBuffer, 0U, sizeof(WrapCrypto_DummyBuffer));
        WrapCrypto_DummyResultSize = sizeof(WrapCrypto_DummyBuffer);

        ResultPtr = WrapCrypto_DummyBuffer;
        ResultLengthPtr = &WrapCrypto_DummyResultSize;
#endif
        FuncRet = Csm_Decrypt(JobId, CRYPTO_OPERATIONMODE_FINISH,
                            NULL_PTR, 0UL,
                            ResultPtr, ResultLengthPtr);
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            /* Wait callout */
            Ret = WRAPCRYPTO_E_PENDING;

            NextJob.Result = WRAPCRYPTO_JOB_PENDING;
            NextJob.Status = WRAPCRYPTO_STAT_FIN_DECRYPT;
            WrapCrypto_UpdateJobInfo(&NextJob);
        }
    }
    else if( CurrentJob.Status == WRAPCRYPTO_STAT_FIN_DECRYPT )
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
/* Function Name | WrapCrypto_DecryptCallout                                  */
/* Description   | Callout function for decryption                            */
/* Preconditions |                                                            */
/* Parameters    | [IN] jobId  : JobId                                        */
/*               | [IN] result : Result of Csm_Decrypt()                      */
/* Return Value  | None                                                       */
/* Notes         | - Please implement callout process according to Crypto     */
/*               |   package.                                                 */
/*               | - This function is set to CsmCallbackFunc in Csm config.   */
/******************************************************************************/
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_DecryptCallout
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

    if( ((CurrentJob.Status == WRAPCRYPTO_STAT_PRE_DECRYPT) && (result == (Crypto_ResultType)E_OK)) ||
        ((CurrentJob.Status == WRAPCRYPTO_STAT_DECRYPT) && (result == (Crypto_ResultType)E_OK)) ||
        ((CurrentJob.Status == WRAPCRYPTO_STAT_FIN_DECRYPT) && (result == (Crypto_ResultType)E_OK)) )
    {
        NextJob.Result = WRAPCRYPTO_JOB_OK;
        NextJob.Status = WRAPCRYPTO_STAT_RESULT;
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

