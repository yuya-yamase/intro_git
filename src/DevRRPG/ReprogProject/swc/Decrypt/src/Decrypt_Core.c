/* Decrypt_Core_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Decrypt/Core/CODE                                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Rte.h>
#include <WrapCrypto.h>

#include <Decrypt.h>
#include "Decrypt_Local.h"
#include "Decrypt_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DECRYPT_E_PENDING                       ((Std_ReturnType)0x02U)

#define DECRYPT_STAT_IDLE                       ((uint8)0x00U)
#define DECRYPT_STAT_PRE_DECODE                 ((uint8)0x11U)
#define DECRYPT_STAT_PRE_DECODE_FINISH          ((uint8)0x12U)
#define DECRYPT_STAT_DECODE                     ((uint8)0x21U)
#define DECRYPT_STAT_DECODE_FINISH              ((uint8)0x22U)
#define DECRYPT_STAT_POST_DECODE                ((uint8)0x31U)

#define DECRYPT_MAX_DATA_LENGTH                 ((uint32)256UL)

#define DECRYPT_IV_SET_PHASE_UNREGISTERED       ((uint8)0U)
#define DECRYPT_IV_SET_PHASE_REGISTERED         ((uint8)1U)

#define DECRYPT_STATUSMATRIXTBL_NUM             (sizeof(Decrypt_StatusMatrixTbl) / sizeof(Decrypt_StatusMatrixTbl[0]))

#define DECRYPT_API_ID_INIT                     ((uint8)0x00U)

#define DECRYPT_E_CASE_KEY_SET_FAIL             ((uint8)0x01U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint8 LocalStatus;
    uint8 JobResult;
} Decrypt_JobInfoType;

typedef struct {
    uint8 LocalStatus;
    uint8 RetStatus;
} Decrypt_StatusMatrixType;

typedef struct {
    P2CONST(uint8, TYPEDEF, DECRYPT_APPL_CONST) CiphertextPtr;
    P2VAR(uint8, TYPEDEF, DECRYPT_APPL_DATA) PlaintextPtr;
    uint32 RemainSize;
    uint32 RequestSize;
    boolean FirstDataFlag;
} Decrypt_DecInfoType;

typedef struct {
    Decrypt_NonceInfoType NonceInfo;
    uint8 IVSetPhase;
} Decrypt_NonceDataInfoType;

typedef struct {
    uint32 Num;
    P2CONST(Decrypt_StatusMatrixType, TYPEDEF, DECRYPT_APPL_CONST) MatrixPtr;
} Decrypt_StatusMatrixInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, DECRYPT_CODE_FAST) Decrypt_Main_ReqPreDecode (void);
static FUNC(void, DECRYPT_CODE_FAST) Decrypt_Main_ReqPostDecode (void);
static FUNC(void, DECRYPT_CODE_FAST) Decrypt_Main_ReqDecode (void);
static FUNC(Std_ReturnType, DECRYPT_CODE_FAST) Decrypt_PreDecode_NonceSet (void);
static FUNC(Std_ReturnType, DECRYPT_CODE_FAST) Decrypt_PreDecode_DecryptStart (void);
static FUNC(void, DECRYPT_CODE_FAST) Decrypt_ClearDecInformation (void);
static FUNC(void, DECRYPT_CODE_FAST) Decrypt_FailureProc (void);
static FUNC(void, DECRYPT_CODE_FAST) Decrypt_UpdateJobInfo
(
    VAR(uint8, AUTOMATIC) JobResult,
    VAR(uint8, AUTOMATIC) LocalStatus
);
static FUNC(Std_ReturnType, DECRYPT_CODE_FAST) Decrypt_GetApiAcceptation (void);
static FUNC(void, DECRYPT_CODE_FAST) Decrypt_ReleaseApiAcceptation (void);
static FUNC(void, DECRYPT_CODE_FAST) Decrypt_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DECRYPT_START_SEC_VAR
#include <Decrypt_MemMap.h>

static VAR(Decrypt_JobInfoType, DECRYPT_VAR_CLEARED) Decrypt_JobInfo;
static VAR(Decrypt_DecInfoType, DECRYPT_VAR_CLEARED) Decrypt_DecInfo;
static VAR(Decrypt_NonceDataInfoType, DECRYPT_VAR_CLEARED) Decrypt_NonceDataInfo;
static VAR(uint8, DECRYPT_VAR_CLEARED) Decrypt_ApiAcceptingFlg;

#define DECRYPT_STOP_SEC_VAR
#include <Decrypt_MemMap.h>

#define DECRYPT_START_SEC_VAR_CIPHERTEXT
#include <Decrypt_MemMap.h>

static VAR(uint8, DECRYPT_VAR_CLEARED) Decrypt_Ciphertext[DECRYPT_MAX_DATA_LENGTH];

#define DECRYPT_STOP_SEC_VAR_CIPHERTEXT
#include <Decrypt_MemMap.h>

#define DECRYPT_START_SEC_VAR_PLAINTEXT
#include <Decrypt_MemMap.h>

static VAR(uint8, DECRYPT_VAR_CLEARED) Decrypt_Plaintext[DECRYPT_MAX_DATA_LENGTH];

#define DECRYPT_STOP_SEC_VAR_PLAINTEXT
#include <Decrypt_MemMap.h>

#define DECRYPT_START_SEC_VAR_PLAINTEXTSIZE
#include <Decrypt_MemMap.h>

static VAR(uint32, DECRYPT_VAR_CLEARED) Decrypt_PlaintextSize;

#define DECRYPT_STOP_SEC_VAR_PLAINTEXTSIZE
#include <Decrypt_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DECRYPT_START_SEC_CST
#include <Decrypt_MemMap.h>

static CONST(Decrypt_StatusMatrixType, DECRYPT_CONST) Decrypt_StatusMatrixTbl[] = {
     { DECRYPT_STAT_IDLE,              DECRYPT_IDLE }
    ,{ DECRYPT_STAT_PRE_DECODE,        DECRYPT_BUSY }
    ,{ DECRYPT_STAT_PRE_DECODE_FINISH, DECRYPT_IDLE }
    ,{ DECRYPT_STAT_DECODE,            DECRYPT_BUSY }
    ,{ DECRYPT_STAT_DECODE_FINISH,     DECRYPT_IDLE }
    ,{ DECRYPT_STAT_POST_DECODE,       DECRYPT_BUSY }
};
static CONST(AB_83_ConstV Decrypt_StatusMatrixInfoType, DECRYPT_CONST) Decrypt_StatusMatrixInfo = {
    DECRYPT_STATUSMATRIXTBL_NUM,
    &Decrypt_StatusMatrixTbl[0]
};

#define DECRYPT_STOP_SEC_CST
#include <Decrypt_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define DECRYPT_START_SEC_CODE
#include <Decrypt_MemMap.h>

/******************************************************************************/
/* Function Name | Decrypt_Init                                               */
/* Description   | Initializes Decrypt                                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DECRYPT_CODE_SLOW) Decrypt_Init (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(uint8, AUTOMATIC) SystemKeyData[DECRYPT_CFG_SYSTEMKEY_SIZE];

    Decrypt_ClearDecInformation();

    Decrypt_ApiAcceptingFlg = STD_OFF;

    Decrypt_UpdateJobInfo(DECRYPT_JOB_OK, DECRYPT_STAT_IDLE);

    if( Decrypt_SystemKeyConfig.KeyPreRegistered == (uint8)STD_OFF )
    {
        /* Register SystemKey in CSM */
        Rte_Rpg_MemSet(SystemKeyData, 0U, sizeof(SystemKeyData));
        Decrypt_Usr_Get_SystemKey(Decrypt_SystemKeyConfig.SystemKeyPtr,
                                Decrypt_SystemKeyConfig.SystemKeySize,
                                SystemKeyData);
        FuncRet = WrapCrypto_Set_SystemKey(Decrypt_SystemKeyConfig.KeyID,
                                            SystemKeyData,
                                            sizeof(SystemKeyData));
        if( FuncRet != (Std_ReturnType)E_OK )
        {
            Decrypt_ReportError(DECRYPT_API_ID_INIT, DECRYPT_E_CASE_KEY_SET_FAIL);
        }

        Rte_Rpg_MemSet(SystemKeyData, 0U, sizeof(SystemKeyData));
    }

    return;
}

/******************************************************************************/
/* Function Name | Decrypt_DeInit                                             */
/* Description   | Deinitializes Decrypt                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DECRYPT_CODE_SLOW) Decrypt_DeInit (void)
{
    Decrypt_UpdateJobInfo(DECRYPT_JOB_OK, DECRYPT_STAT_IDLE);

    Decrypt_ApiAcceptingFlg = STD_OFF;

    Decrypt_ClearDecInformation();

    return;
}

/******************************************************************************/
/* Function Name | Decrypt_Time                                               */
/* Description   | TimeFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DECRYPT_CODE_SLOW) Decrypt_Time (void)
{
    return;
}

/******************************************************************************/
/* Function Name | Decrypt_MainFunction                                       */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DECRYPT_CODE_SLOW) Decrypt_MainFunction (void)
{
    if( Decrypt_JobInfo.LocalStatus == DECRYPT_STAT_PRE_DECODE )
    {
        Decrypt_Main_ReqPreDecode();
    }
    else if( Decrypt_JobInfo.LocalStatus == DECRYPT_STAT_DECODE )
    {
        Decrypt_Main_ReqDecode();
    }
    else if( Decrypt_JobInfo.LocalStatus == DECRYPT_STAT_POST_DECODE )
    {
        Decrypt_Main_ReqPostDecode();
    }
    else
    {
        /* No process */
    }

    return;
}

/******************************************************************************/
/* Function Name | Decrypt_GetStatus                                          */
/* Description   | Acquires status of job                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Status                                                     */
/*               |  DECRYPT_IDLE                                              */
/*               |  DECRYPT_BUSY                                              */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DECRYPT_CODE_SLOW) Decrypt_GetStatus (void)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) Status;

    Status = DECRYPT_BUSY;

    for( i = 0UL; i < Decrypt_StatusMatrixInfo.Num; i++ )
    {
        if( Decrypt_JobInfo.LocalStatus == Decrypt_StatusMatrixInfo.MatrixPtr[i].LocalStatus )
        {
            Status = Decrypt_StatusMatrixInfo.MatrixPtr[i].RetStatus;
            break;
        }
    }

    return Status;
}

/******************************************************************************/
/* Function Name | Decrypt_GetJobResult                                       */
/* Description   | Acquires result of job                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | JobResult                                                  */
/*               |  DECRYPT_JOB_OK                                            */
/*               |  DECRYPT_JOB_FAILED                                        */
/*               |  DECRYPT_JOB_PENDING                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DECRYPT_CODE_SLOW) Decrypt_GetJobResult (void)
{
    return Decrypt_JobInfo.JobResult;
}

/******************************************************************************/
/* Function Name | Decrypt_ReqPreDecode                                       */
/* Description   | Prepares decoding                                          */
/* Preconditions |                                                            */
/* Parameters    | [IN] NonceInfo : Information of nonce                      */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DECRYPT_CODE_SLOW) Decrypt_ReqPreDecode
(
    P2CONST(Decrypt_NonceInfoType, AUTOMATIC, DECRYPT_APPL_CONST) NonceInfo
)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = Decrypt_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( Decrypt_JobInfo.LocalStatus == DECRYPT_STAT_IDLE )
        {
            Decrypt_NonceDataInfo.IVSetPhase = DECRYPT_IV_SET_PHASE_UNREGISTERED;
            Decrypt_NonceDataInfo.NonceInfo.Nonce = NonceInfo->Nonce;
            Decrypt_NonceDataInfo.NonceInfo.NonceSize = NonceInfo->NonceSize;

            Decrypt_UpdateJobInfo(DECRYPT_JOB_PENDING, DECRYPT_STAT_PRE_DECODE);
        }
        else
        {
            Decrypt_FailureProc();
        }

        Decrypt_ReleaseApiAcceptation();
    }

    return;
}

/******************************************************************************/
/* Function Name | Decrypt_ReqPostDecode                                      */
/* Description   | Completes decoding                                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DECRYPT_CODE_SLOW) Decrypt_ReqPostDecode (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = Decrypt_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( Decrypt_JobInfo.LocalStatus == DECRYPT_STAT_DECODE_FINISH )
        {
            Decrypt_UpdateJobInfo(DECRYPT_JOB_PENDING, DECRYPT_STAT_POST_DECODE);
        }
        else
        {
            Decrypt_FailureProc();
        }

        Decrypt_ReleaseApiAcceptation();
    }

    return;
}

/******************************************************************************/
/* Function Name | Decrypt_ReqDecode                                          */
/* Description   | Requests decoding                                          */
/* Preconditions |                                                            */
/* Parameters    | [IN]  SrcAddr  : Start address of ciphertext               */
/*               | [OUT] DestAddr : Start address of plaintext                */
/*               | [IN]  Size     : Decoding size                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DECRYPT_CODE_SLOW) Decrypt_ReqDecode
(
    P2CONST(uint8, AUTOMATIC, DECRYPT_APPL_CONST) SrcAddr,
    P2VAR(uint8, AUTOMATIC, DECRYPT_APPL_DATA) DestAddr,
    VAR(uint16, AUTOMATIC) Size
)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = Decrypt_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( ( Decrypt_JobInfo.LocalStatus == DECRYPT_STAT_PRE_DECODE_FINISH ) ||
            ( Decrypt_JobInfo.LocalStatus == DECRYPT_STAT_DECODE_FINISH ) )
        {
            Decrypt_DecInfo.CiphertextPtr = SrcAddr;
            Decrypt_DecInfo.PlaintextPtr = DestAddr;
            Decrypt_DecInfo.RemainSize = Size;

            Decrypt_DecInfo.RequestSize = DECRYPT_MAX_DATA_LENGTH;
            if( Decrypt_DecInfo.RequestSize > Decrypt_DecInfo.RemainSize )
            {
                Decrypt_DecInfo.RequestSize = Decrypt_DecInfo.RemainSize;
            }

            /* Copy ciphertext to aligned buffer */
            Rte_Rpg_MemCopy(Decrypt_Ciphertext,
                            Decrypt_DecInfo.CiphertextPtr,
                            Decrypt_DecInfo.RequestSize);

            Decrypt_PlaintextSize = Decrypt_DecInfo.RequestSize;

            Decrypt_UpdateJobInfo(DECRYPT_JOB_PENDING, DECRYPT_STAT_DECODE);
        }
        else
        {
            Decrypt_FailureProc();
        }

        Decrypt_ReleaseApiAcceptation();
    }

    return;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | Decrypt_Main_ReqPreDecode                                  */
/* Description   | MainFunction of DECRYPT_STAT_PRE_DECODE                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DECRYPT_CODE_FAST) Decrypt_Main_ReqPreDecode (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(uint8, AUTOMATIC) ErrFlag;

    ErrFlag = STD_OFF;

    if( Decrypt_NonceDataInfo.IVSetPhase == DECRYPT_IV_SET_PHASE_UNREGISTERED )
    {
        FuncRet = Decrypt_PreDecode_NonceSet();
        if( (FuncRet != (Std_ReturnType)E_OK) && (FuncRet != DECRYPT_E_PENDING) )
        {
            ErrFlag = STD_ON;
        }
    }

    if( (ErrFlag == (uint8)STD_OFF) &&
        (Decrypt_NonceDataInfo.IVSetPhase == DECRYPT_IV_SET_PHASE_REGISTERED) )
    {
        FuncRet = Decrypt_PreDecode_DecryptStart();
        if( (FuncRet != (Std_ReturnType)E_OK) && (FuncRet != DECRYPT_E_PENDING) )
        {
            ErrFlag = STD_ON;
        }
    }

    if( ErrFlag == (uint8)STD_ON )
    {
        Decrypt_FailureProc();
    }

    return;
}

/******************************************************************************/
/* Function Name | Decrypt_Main_ReqPostDecode                                 */
/* Description   | MainFunction of DECRYPT_STAT_POST_DECODE                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DECRYPT_CODE_FAST) Decrypt_Main_ReqPostDecode (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = WrapCrypto_Fin_Decrypt(Decrypt_SystemKeyConfig.JobID);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        Decrypt_ClearDecInformation();
        Decrypt_UpdateJobInfo(DECRYPT_JOB_OK, DECRYPT_STAT_IDLE);
    }
    else if( FuncRet == WRAPCRYPTO_E_PENDING )
    {
        /* No process */
    }
    else
    {
        Decrypt_FailureProc();
    }

    return;
}

/******************************************************************************/
/* Function Name | Decrypt_Main_ReqDecode                                     */
/* Description   | MainFunction of DECRYPT_STAT_DECODE                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DECRYPT_CODE_FAST) Decrypt_Main_ReqDecode (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = WrapCrypto_Decrypt(Decrypt_DecInfo.FirstDataFlag,
                                Decrypt_SystemKeyConfig.JobID,
                                Decrypt_Ciphertext,
                                Decrypt_DecInfo.RequestSize,
                                Decrypt_Plaintext,
                                &Decrypt_PlaintextSize);
    if( (FuncRet == (Std_ReturnType)E_OK) &&
        (Decrypt_DecInfo.RequestSize == Decrypt_PlaintextSize) &&
        (Decrypt_DecInfo.RemainSize >= Decrypt_PlaintextSize) )
    {
        Decrypt_DecInfo.FirstDataFlag = FALSE;

        /* Copy the plaintext of aligned buffer */
        Rte_Rpg_MemCopy(Decrypt_DecInfo.PlaintextPtr,
                        Decrypt_Plaintext,
                        Decrypt_PlaintextSize);

        Decrypt_DecInfo.CiphertextPtr = &Decrypt_DecInfo.CiphertextPtr[Decrypt_PlaintextSize];
        Decrypt_DecInfo.PlaintextPtr = &Decrypt_DecInfo.PlaintextPtr[Decrypt_PlaintextSize];
        Decrypt_DecInfo.RemainSize -= Decrypt_PlaintextSize;

        if( Decrypt_DecInfo.RemainSize != 0UL )
        {
            /* To next ciphertext */
            Decrypt_DecInfo.RequestSize = DECRYPT_MAX_DATA_LENGTH;
            if( Decrypt_DecInfo.RequestSize > Decrypt_DecInfo.RemainSize )
            {
                Decrypt_DecInfo.RequestSize = Decrypt_DecInfo.RemainSize;
            }

            /* Copy ciphertext to aligned buffer */
            Rte_Rpg_MemCopy(Decrypt_Ciphertext,
                            Decrypt_DecInfo.CiphertextPtr,
                            Decrypt_DecInfo.RequestSize);

            Decrypt_PlaintextSize = Decrypt_DecInfo.RequestSize;

            Decrypt_UpdateJobInfo(DECRYPT_JOB_PENDING, DECRYPT_STAT_DECODE);
        }
        else
        {
            /* All ciphertexts complete */
            Decrypt_UpdateJobInfo(DECRYPT_JOB_OK, DECRYPT_STAT_DECODE_FINISH);
        }
    }
    else if( FuncRet == WRAPCRYPTO_E_PENDING )
    {
        /* No process */
    }
    else
    {
        Decrypt_FailureProc();
    }

    return;
}

/******************************************************************************/
/* Function Name | Decrypt_PreDecode_NonceSet                                 */
/* Description   | Set nonce                                                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  DECRYPT_E_PENDING                                         */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, DECRYPT_CODE_FAST) Decrypt_PreDecode_NonceSet (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = WrapCrypto_Set_Nonce(Decrypt_SystemKeyConfig.KeyID,
                                Decrypt_NonceDataInfo.NonceInfo.Nonce,
                                (uint32)Decrypt_NonceDataInfo.NonceInfo.NonceSize);
    if( Ret == (Std_ReturnType)E_OK )
    {
        Decrypt_NonceDataInfo.IVSetPhase = DECRYPT_IV_SET_PHASE_REGISTERED;
    }
    else if( Ret == WRAPCRYPTO_E_PENDING )
    {
        Ret = DECRYPT_E_PENDING;
    }
    else
    {
        Ret = E_NOT_OK;
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Decrypt_PreDecode_DecryptStart                             */
/* Description   | Start decryption                                           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/*               |  DECRYPT_E_PENDING                                         */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, DECRYPT_CODE_FAST) Decrypt_PreDecode_DecryptStart (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = WrapCrypto_Pre_Decrypt(Decrypt_SystemKeyConfig.JobID);
    if( Ret == (Std_ReturnType)E_OK )
    {
        Decrypt_DecInfo.FirstDataFlag = TRUE;
        Decrypt_UpdateJobInfo(DECRYPT_JOB_OK, DECRYPT_STAT_PRE_DECODE_FINISH);
    }
    else if( Ret == WRAPCRYPTO_E_PENDING )
    {
        Ret = DECRYPT_E_PENDING;
    }
    else
    {
        Ret = E_NOT_OK;
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Decrypt_ClearDecInformation                                */
/* Description   | Clears decoding information                                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DECRYPT_CODE_FAST) Decrypt_ClearDecInformation (void)
{
    Decrypt_DecInfo.CiphertextPtr = NULL_PTR;
    Decrypt_DecInfo.PlaintextPtr = NULL_PTR;
    Decrypt_DecInfo.RemainSize = 0UL;
    Decrypt_DecInfo.RequestSize = 0UL;
    Decrypt_DecInfo.FirstDataFlag = FALSE;

    Rte_Rpg_MemSet(Decrypt_Ciphertext, 0U, sizeof(Decrypt_Ciphertext));
    Rte_Rpg_MemSet(Decrypt_Plaintext, 0U, sizeof(Decrypt_Plaintext));

    Decrypt_PlaintextSize = 0UL;

    Decrypt_NonceDataInfo.NonceInfo.Nonce = NULL_PTR;
    Decrypt_NonceDataInfo.NonceInfo.NonceSize = 0U;
    Decrypt_NonceDataInfo.IVSetPhase = DECRYPT_IV_SET_PHASE_UNREGISTERED;

    return;
}

/******************************************************************************/
/* Function Name | Decrypt_FailureProc                                        */
/* Description   | Failure process                                            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DECRYPT_CODE_FAST) Decrypt_FailureProc (void)
{
    Decrypt_ClearDecInformation();

    Decrypt_UpdateJobInfo(DECRYPT_JOB_FAILED, DECRYPT_STAT_IDLE);

    return;
}

/******************************************************************************/
/* Function Name | Decrypt_UpdateJobInfo                                      */
/* Description   | Updates JobInfo                                            */
/* Preconditions |                                                            */
/* Parameters    | [IN] JobResult   : Result of job                           */
/*               |       DECRYPT_JOB_OK                                       */
/*               |       DECRYPT_JOB_FAILED                                   */
/*               |       DECRYPT_JOB_PENDING                                  */
/*               | [IN] LocalStatus : Local status                            */
/*               |       DECRYPT_STAT_IDLE                                    */
/*               |       DECRYPT_STAT_PRE_DECODE                              */
/*               |       DECRYPT_STAT_PRE_DECODE_FINISH                       */
/*               |       DECRYPT_STAT_DECODE                                  */
/*               |       DECRYPT_STAT_DECODE_FINISH                           */
/*               |       DECRYPT_STAT_POST_DECODE                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DECRYPT_CODE_FAST) Decrypt_UpdateJobInfo
(
    VAR(uint8, AUTOMATIC) JobResult,
    VAR(uint8, AUTOMATIC) LocalStatus
)
{
    VAR(uint8, AUTOMATIC) MaskPattern;

    MaskPattern = Rte_MaskInterruptAll();   /* for JobResult/LocalStatus */
    Decrypt_JobInfo.JobResult = JobResult;
    Decrypt_JobInfo.LocalStatus = LocalStatus;
    Rte_UnMaskInterruptAll(MaskPattern);    /* for JobResult/LocalStatus */

    return;
}

/******************************************************************************/
/* Function Name | Decrypt_GetApiAcceptation                                  */
/* Description   | Acquires the acceptation of executing API                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, DECRYPT_CODE_FAST) Decrypt_GetApiAcceptation (void)
{
    VAR(uint8, AUTOMATIC) MaskPattern;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    MaskPattern = Rte_MaskInterruptAll();   /* prevent multiple execution */
    if( Decrypt_ApiAcceptingFlg == (uint8)STD_OFF )
    {
        Decrypt_ApiAcceptingFlg = STD_ON;
        Ret = E_OK;
    }
    Rte_UnMaskInterruptAll(MaskPattern);    /* prevent multiple execution */

    return Ret;
}

/******************************************************************************/
/* Function Name | Decrypt_ReleaseApiAcceptation                              */
/* Description   | Releases the acceptation of executing API                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DECRYPT_CODE_FAST) Decrypt_ReleaseApiAcceptation (void)
{
    Decrypt_ApiAcceptingFlg = STD_OFF;

    return;
}

/******************************************************************************/
/* Function Name | Decrypt_ReportError                                        */
/* Description   | Report the error information                               */
/* Preconditions |                                                            */
/* Parameters    | [IN] ApiId   : API ID                                      */
/*               | [IN] ErrorId : Error ID                                    */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DECRYPT_CODE_FAST) Decrypt_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
)
{
    VAR(Rte_EcuM_ErrorType, AUTOMATIC) Error;

    Error.ModuleId = RTE_ECUM_MODULE_DECRYPT;
    Error.ApiId = ApiId;
    Error.ErrorId = ErrorId;

    Rte_EcuM_ReportError(&Error);

    return;
}


#define DECRYPT_STOP_SEC_CODE
#include <Decrypt_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*  v2.00       :2024/05/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

