/* WrapCrypto_Encrypt_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | WrapCrypto/Encrypt/CODE                                     */
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
/* Function Name | WrapCrypto_Pre_Encrypt                                     */
/* Description   | Prepare for encryption                                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] JobId : JobId                                         */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  WRAPCRYPTO_E_PENDING                                      */
/* Notes         | - Please implement encryption preparation process          */
/*               |   according to Crypto package.                             */
/*               | - If the process has not completed, return                 */
/*               |   WRAPCRYPTO_E_PENDING. In that case, call it again with   */
/*               |   the same arguments.                                      */
/******************************************************************************/
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Pre_Encrypt
(
    VAR(uint32, AUTOMATIC) JobId
)
{
/*===== Sample ===============================================================*/
    return E_OK;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | WrapCrypto_Encrypt                                         */
/* Description   | Encryption                                                 */
/* Preconditions |                                                            */
/* Parameters    | [IN]    FirstData      : 1st verification data             */
/*               |          TRUE                                              */
/*               |          FALSE                                             */
/*               | [IN]    JobId          : JobId                             */
/*               | [IN]    Plaintext      : Plaintext                         */
/*               | [IN]    PlaintextSize  : Plaintext size                    */
/*               | [OUT]   Ciphertext     : Ciphertext                        */
/*               | [INOUT] CiphertextSize : IN  : Ciphertext buffer size      */
/*               |                          OUT : Encrypted ciphertext size   */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  WRAPCRYPTO_E_PENDING                                      */
/* Notes         | - Please implement encryption process according to         */
/*               |   Crypto package.                                          */
/*               | - If the process has not completed, return                 */
/*               |   WRAPCRYPTO_E_PENDING. In that case, call it again with   */
/*               |   the same arguments.                                      */
/*               | - The pointer arguments are arranged as follows.           */
/*               |    Plaintext      : ".B_RAM_DIAGSRV_SEED_SHARED"           */
/*               |    Ciphertext     : ".B_RAM_DIAGSRV_KEY_SHARED"            */
/*               |    CiphertextSize : ".B_RAM_SEC_ENCRYPTSIZE_SHARED"        */
/******************************************************************************/
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Encrypt
(
    VAR(boolean, AUTOMATIC) FirstData,
    VAR(uint32, AUTOMATIC) JobId,
    P2CONST(uint8, AUTOMATIC, WRAPCRYPTO_APPL_CONST) Plaintext,
    VAR(uint32, AUTOMATIC) PlaintextSize,
    P2VAR(uint8, AUTOMATIC, WRAPCRYPTO_APPL_DATA) Ciphertext,
    P2VAR(uint32, AUTOMATIC, WRAPCRYPTO_APPL_DATA) CiphertextSize
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
        FuncRet = Csm_Encrypt(JobId, CRYPTO_OPERATIONMODE_SINGLECALL,
                            Plaintext, PlaintextSize,
                            Ciphertext, CiphertextSize);
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            /* Wait callout */
            Ret = WRAPCRYPTO_E_PENDING;

            NextJob.Result = WRAPCRYPTO_JOB_PENDING;
            NextJob.Status = WRAPCRYPTO_STAT_ENCRYPT;
            WrapCrypto_UpdateJobInfo(&NextJob);
        }
    }
    else if( CurrentJob.Status == WRAPCRYPTO_STAT_ENCRYPT )
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
/* Function Name | WrapCrypto_Fin_Encrypt                                     */
/* Description   | Finish for encryption                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] JobId : JobId                                         */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  WRAPCRYPTO_E_PENDING                                      */
/* Notes         | - Please implement encryption completion process according */
/*               |   to Crypto package.                                       */
/*               | - If the process has not completed, return                 */
/*               |   WRAPCRYPTO_E_PENDING. In that case, call it again with   */
/*               |   the same arguments.                                      */
/******************************************************************************/
FUNC(Std_ReturnType, WRAPCRYPTO_CODE_SLOW) WrapCrypto_Fin_Encrypt
(
    VAR(uint32, AUTOMATIC) JobId
)
{
/*===== Sample ===============================================================*/
    return E_OK;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | WrapCrypto_EncryptCallout                                  */
/* Description   | Callout function for encryption                            */
/* Preconditions |                                                            */
/* Parameters    | [IN] jobId  : JobId                                        */
/*               | [IN] result : Result of Csm_Encrypt()                      */
/* Return Value  | None                                                       */
/* Notes         | - Please implement callout process according to Crypto     */
/*               |   package.                                                 */
/*               | - This function is set to CsmCallbackFunc in Csm config.   */
/******************************************************************************/
FUNC(void, WRAPCRYPTO_CODE_SLOW) WrapCrypto_EncryptCallout
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

    if( (CurrentJob.Status == WRAPCRYPTO_STAT_ENCRYPT) && (result == (Crypto_ResultType)E_OK) )
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

