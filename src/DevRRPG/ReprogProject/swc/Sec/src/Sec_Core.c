/* Sec_Core_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Sec/Core/CODE                                               */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Rte.h>
#include <WrapCrypto.h>

#include <Sec.h>
#include "Sec_Local.h"
#include "Sec_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define SEC_STAT_IDLE                   ((uint8)0x00U)
#define SEC_STAT_PRE_SEED               ((uint8)0x01U)
#define SEC_STAT_PRE_SEED_FINISH        ((uint8)0x02U)
#define SEC_STAT_SEED                   ((uint8)0x03U)
#define SEC_STAT_SEED_FINISH            ((uint8)0x04U)
#define SEC_STAT_POST_SEED              ((uint8)0x05U)
#define SEC_STAT_PRE_KEY                ((uint8)0x06U)
#define SEC_STAT_PRE_KEY_FINISH         ((uint8)0x07U)
#define SEC_STAT_KEY                    ((uint8)0x08U)
#define SEC_STAT_KEY_FINISH             ((uint8)0x09U)
#define SEC_STAT_POST_KEY               ((uint8)0x0AU)

#define SEC_SECURITY_LEVEL1             ((uint8)0x01U)

#define SEC_SEED_SIZE                   ((uint8)16U)
#define SEC_KEY_SIZE                    ((uint8)16U)

#define SEC_STATUSMATRIXTBL_NUM         (sizeof(Sec_StatusMatrixTbl) / sizeof(Sec_StatusMatrixTbl[0]))

#define SEC_API_ID_INIT                 ((uint8)0x00U)

#define SEC_E_CASE_KEY_SET_FAIL         ((uint8)0x01U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint8 LocalStatus;
    uint8 JobResult;
} Sec_JobInfoType;

typedef struct {
    uint8 LocalStatus;
    uint8 RetStatus;
} Sec_StatusMatrixType;

typedef struct {
    uint32 Num;
    P2CONST(Sec_StatusMatrixType, TYPEDEF, SEC_APPL_CONST) MatrixPtr;
} Sec_StatusMatrixInfoType;

typedef struct {
    P2VAR(uint8, TYPEDEF, SEC_APPL_DATA) SeedPtr;
    uint32 SeedSize;
    P2VAR(uint8, TYPEDEF, SEC_APPL_DATA) KeyPtr;
    uint32 KeySize;
    boolean FirstDataFlag;
} Sec_SeedKeyInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, SEC_CODE_FAST) Sec_Main_ReqGenSeed (void);
static FUNC(void, SEC_CODE_FAST) Sec_Main_PreGenSeed (void);
static FUNC(void, SEC_CODE_FAST) Sec_Main_PostGenSeed (void);
static FUNC(void, SEC_CODE_FAST) Sec_Main_ReqGenKey (void);
static FUNC(void, SEC_CODE_FAST) Sec_Main_PreGenKey (void);
static FUNC(void, SEC_CODE_FAST) Sec_Main_PostGenKey (void);
static FUNC(void, SEC_CODE_FAST) Sec_ClearSecurityInformation (void);
static FUNC(void, SEC_CODE_FAST) Sec_FailureProc (void);
static FUNC(void, SEC_CODE_FAST) Sec_UpdateJobInfo
(
    VAR(uint8, AUTOMATIC) JobResult,
    VAR(uint8, AUTOMATIC) LocalStatus
);
static FUNC(Std_ReturnType, SEC_CODE_FAST) Sec_GetApiAcceptation (void);
static FUNC(void, SEC_CODE_FAST) Sec_ReleaseApiAcceptation (void);
static FUNC(void, SEC_CODE_FAST) Sec_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define SEC_START_SEC_VAR
#include <Sec_MemMap.h>

static VAR(Sec_JobInfoType, SEC_VAR_CLEARED) Sec_JobInfo;
static VAR(Sec_SeedKeyInfoType, SEC_VAR_CLEARED) Sec_SeedKeyInfo;
static VAR(uint8, SEC_VAR_CLEARED) Sec_SecurityLevel;
static VAR(uint8, SEC_VAR_CLEARED) Sec_ApiAcceptingFlg;

#define SEC_STOP_SEC_VAR
#include <Sec_MemMap.h>

#define SEC_START_SEC_VAR_ENCRYPT_SIZE
#include <Sec_MemMap.h>

static VAR(uint32, SEC_VAR_CLEARED) Sec_EncryptSize;

#define SEC_STOP_SEC_VAR_ENCRYPT_SIZE
#include <Sec_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define SEC_START_SEC_CST
#include <Sec_MemMap.h>

static CONST(Sec_StatusMatrixType, SEC_CONST) Sec_StatusMatrixTbl[] = {
     { SEC_STAT_IDLE,            SEC_IDLE }
    ,{ SEC_STAT_PRE_SEED,        SEC_BUSY }
    ,{ SEC_STAT_PRE_SEED_FINISH, SEC_IDLE }
    ,{ SEC_STAT_SEED,            SEC_BUSY }
    ,{ SEC_STAT_SEED_FINISH,     SEC_IDLE }
    ,{ SEC_STAT_POST_SEED,       SEC_BUSY }
    ,{ SEC_STAT_PRE_KEY,         SEC_BUSY }
    ,{ SEC_STAT_PRE_KEY_FINISH,  SEC_IDLE }
    ,{ SEC_STAT_KEY,             SEC_BUSY }
    ,{ SEC_STAT_KEY_FINISH,      SEC_IDLE }
    ,{ SEC_STAT_POST_KEY,        SEC_BUSY }
};
static CONST(AB_83_ConstV Sec_StatusMatrixInfoType, SEC_CONST) Sec_StatusMatrixInfo = {
    SEC_STATUSMATRIXTBL_NUM,
    &Sec_StatusMatrixTbl[0]
};

#define SEC_STOP_SEC_CST
#include <Sec_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define SEC_START_SEC_CODE
#include <Sec_MemMap.h>

/******************************************************************************/
/* Function Name | Sec_Init                                                   */
/* Description   | Initializes Sec                                            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SEC_CODE_SLOW) Sec_Init (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(uint8, AUTOMATIC) ToolAuthKeyData[SEC_CFG_TOOLAUTHKEY_SIZE];

    Sec_ClearSecurityInformation();

    Sec_ApiAcceptingFlg = STD_OFF;

    Sec_UpdateJobInfo(SEC_JOB_OK, SEC_STAT_IDLE);

    Sec_Usr_Init();

    if( Sec_ToolAuthKeyConfig.KeyPreRegistered == (uint8)STD_OFF )
    {
        /* Register ToolAuthenticationKey in CSM */
        Rte_Rpg_MemSet(ToolAuthKeyData, 0U, sizeof(ToolAuthKeyData));
        Sec_Usr_Get_ToolAuthKey(Sec_ToolAuthKeyConfig.ToolAuthKeyPtr,
                                Sec_ToolAuthKeyConfig.ToolAuthKeySize,
                                ToolAuthKeyData);
        FuncRet = WrapCrypto_Set_ToolAuthKey(Sec_ToolAuthKeyConfig.KeyID,
                                            ToolAuthKeyData,
                                            sizeof(ToolAuthKeyData));
        if( FuncRet != (Std_ReturnType)E_OK )
        {
            Sec_ReportError(SEC_API_ID_INIT, SEC_E_CASE_KEY_SET_FAIL);
        }

        Rte_Rpg_MemSet(ToolAuthKeyData, 0U, sizeof(ToolAuthKeyData));
    }

    return;
}

/******************************************************************************/
/* Function Name | Sec_DeInit                                                 */
/* Description   | Deinitializes Sec                                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SEC_CODE_SLOW) Sec_DeInit (void)
{
    Sec_UpdateJobInfo(SEC_JOB_OK, SEC_STAT_IDLE);

    Sec_ApiAcceptingFlg = STD_OFF;

    Sec_ClearSecurityInformation();

    Sec_Usr_DeInit();

    return;
}

/******************************************************************************/
/* Function Name | Sec_Time                                                   */
/* Description   | TimeFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SEC_CODE_SLOW) Sec_Time (void)
{
    Sec_Usr_Time();

    return;
}

/******************************************************************************/
/* Function Name | Sec_MainFunction                                           */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, SEC_CODE_SLOW) Sec_MainFunction (void)
{
    Sec_Usr_MainFunction();

    if( Sec_JobInfo.LocalStatus == SEC_STAT_PRE_SEED )
    {
        Sec_Main_PreGenSeed();
    }
    else if( Sec_JobInfo.LocalStatus == SEC_STAT_SEED )
    {
        Sec_Main_ReqGenSeed();
    }
    else if( Sec_JobInfo.LocalStatus == SEC_STAT_POST_SEED )
    {
        Sec_Main_PostGenSeed();
    }
    else if( Sec_JobInfo.LocalStatus == SEC_STAT_PRE_KEY )
    {
        Sec_Main_PreGenKey();
    }
    else if( Sec_JobInfo.LocalStatus == SEC_STAT_KEY )
    {
        Sec_Main_ReqGenKey();
    }
    else if( Sec_JobInfo.LocalStatus == SEC_STAT_POST_KEY )
    {
        Sec_Main_PostGenKey();
    }
    else
    {
        /* No process */
    }

    return;
}

/******************************************************************************/
/* Function Name | Sec_GetStatus                                              */
/* Description   | Acquires status of job                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Status                                                     */
/*               |  SEC_IDLE                                                  */
/*               |  SEC_BUSY                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, SEC_CODE_SLOW) Sec_GetStatus (void)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) Status;

    Status = SEC_BUSY;

    for( i = 0UL; i < Sec_StatusMatrixInfo.Num; i++ )
    {
        if( Sec_JobInfo.LocalStatus == Sec_StatusMatrixInfo.MatrixPtr[i].LocalStatus )
        {
            Status = Sec_StatusMatrixInfo.MatrixPtr[i].RetStatus;
            break;
        }
    }

    return Status;
}

/******************************************************************************/
/* Function Name | Sec_GetJobResult                                           */
/* Description   | Acquires result of job                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | JobResult                                                  */
/*               |  SEC_JOB_OK                                                */
/*               |  SEC_JOB_FAILED                                            */
/*               |  SEC_JOB_PENDING                                           */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, SEC_CODE_SLOW) Sec_GetJobResult (void)
{
    return Sec_JobInfo.JobResult;
}

/******************************************************************************/
/* Function Name | Sec_ReqPreGenSeed                                          */
/* Description   | Prepares generating seed                                   */
/* Preconditions |                                                            */
/* Parameters    | [IN] Level : Security level                                */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, SEC_CODE_SLOW) Sec_ReqPreGenSeed
(
    VAR(uint8, AUTOMATIC) Level
)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    FuncRet = Sec_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( Sec_JobInfo.LocalStatus == SEC_STAT_IDLE )
        {
            if( Level == SEC_SECURITY_LEVEL1 )
            {
                Sec_SecurityLevel = Level;

                Sec_UpdateJobInfo(SEC_JOB_PENDING, SEC_STAT_PRE_SEED);

                Ret = E_OK;
            }
        }

        if( Ret != (Std_ReturnType)E_OK )
        {
            Sec_FailureProc();
        }

        Sec_ReleaseApiAcceptation();
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Sec_ReqPostGenSeed                                         */
/* Description   | Completes generating seed                                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, SEC_CODE_SLOW) Sec_ReqPostGenSeed (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    FuncRet = Sec_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( Sec_JobInfo.LocalStatus == SEC_STAT_SEED_FINISH )
        {
            Sec_UpdateJobInfo(SEC_JOB_PENDING, SEC_STAT_POST_SEED);

            Ret = E_OK;
        }
        else
        {
            Sec_FailureProc();
        }

        Sec_ReleaseApiAcceptation();
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Sec_ReqGenSeed                                             */
/* Description   | Generates seed                                             */
/* Preconditions |                                                            */
/* Parameters    | [INOUT] SeedInfo : Information of seed                     */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, SEC_CODE_SLOW) Sec_ReqGenSeed
(
    P2CONST(Sec_SeedInfoType, AUTOMATIC, SEC_APPL_CONST) SeedInfo
)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    FuncRet = Sec_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( ( Sec_JobInfo.LocalStatus == SEC_STAT_PRE_SEED_FINISH ) &&
            ( SeedInfo->SeedSize >= SEC_SEED_SIZE ) )
        {
            Sec_SeedKeyInfo.SeedPtr = SeedInfo->Seed;
            Sec_SeedKeyInfo.SeedSize = (uint32)SeedInfo->SeedSize;

            Sec_UpdateJobInfo(SEC_JOB_PENDING, SEC_STAT_SEED);

            Ret = E_OK;
        }
        else
        {
            Sec_FailureProc();
        }

        Sec_ReleaseApiAcceptation();
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Sec_ReqPreGenKey                                           */
/* Description   | Prepares generating key                                    */
/* Preconditions |                                                            */
/* Parameters    | [IN] Level : Security level                                */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, SEC_CODE_SLOW) Sec_ReqPreGenKey
(
    VAR(uint8, AUTOMATIC) Level
)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    FuncRet = Sec_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( Sec_JobInfo.LocalStatus == SEC_STAT_IDLE )
        {
            if( Level == SEC_SECURITY_LEVEL1 )
            {
                Sec_SecurityLevel = Level;

                Sec_UpdateJobInfo(SEC_JOB_PENDING, SEC_STAT_PRE_KEY);

                Ret = E_OK;
            }
        }

        if( Ret != (Std_ReturnType)E_OK )
        {
            Sec_FailureProc();
        }

        Sec_ReleaseApiAcceptation();
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Sec_ReqPostGenKey                                          */
/* Description   | Completes generating key                                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, SEC_CODE_SLOW) Sec_ReqPostGenKey (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    FuncRet = Sec_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( Sec_JobInfo.LocalStatus == SEC_STAT_KEY_FINISH )
        {
            Sec_UpdateJobInfo(SEC_JOB_PENDING, SEC_STAT_POST_KEY);

            Ret = E_OK;
        }
        else
        {
            Sec_FailureProc();
        }

        Sec_ReleaseApiAcceptation();
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | Sec_ReqGenKey                                              */
/* Description   | Generates key                                              */
/* Preconditions |                                                            */
/* Parameters    | [IN]    SeedInfo : Information of seed                     */
/*               | [INOUT] KeyInfo  : Information of key                      */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, SEC_CODE_SLOW) Sec_ReqGenKey
(
    P2CONST(Sec_SeedInfoType, AUTOMATIC, SEC_APPL_CONST) SeedInfo,
    P2CONST(Sec_KeyInfoType, AUTOMATIC, SEC_APPL_CONST) KeyInfo
)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    FuncRet = Sec_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( ( Sec_JobInfo.LocalStatus == SEC_STAT_PRE_KEY_FINISH ) &&
            ( SeedInfo->SeedSize >= SEC_SEED_SIZE ) &&
            ( KeyInfo->KeySize >= SEC_KEY_SIZE ) )
        {
            Sec_SeedKeyInfo.SeedPtr = SeedInfo->Seed;
            Sec_SeedKeyInfo.SeedSize = (uint32)SeedInfo->SeedSize;
            Sec_SeedKeyInfo.KeyPtr = KeyInfo->Key;
            Sec_SeedKeyInfo.KeySize = (uint32)KeyInfo->KeySize;

            Sec_EncryptSize = Sec_SeedKeyInfo.KeySize;

            Sec_UpdateJobInfo(SEC_JOB_PENDING, SEC_STAT_KEY);

            Ret = E_OK;
        }
        else
        {
            Sec_FailureProc();
        }

        Sec_ReleaseApiAcceptation();
    }

    return Ret;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | Sec_Main_ReqGenSeed                                        */
/* Description   | MainFunction of SEC_STAT_SEED                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SEC_CODE_FAST) Sec_Main_ReqGenSeed (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(uint8, AUTOMATIC) ErrFlag;

    ErrFlag = STD_ON;

    if( Sec_SecurityLevel == SEC_SECURITY_LEVEL1 )
    {
        FuncRet = Sec_Usr_GenSeedValue(SEC_GENSEED_GET,
                                        Sec_SeedKeyInfo.SeedPtr,
                                        (uint8)Sec_SeedKeyInfo.SeedSize);
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            Sec_UpdateJobInfo(SEC_JOB_OK, SEC_STAT_SEED_FINISH);

            ErrFlag = STD_OFF;
        }
        else if( FuncRet == SEC_E_PENDING )
        {
            ErrFlag = STD_OFF;
        }
        else
        {
            /* No process */
        }
    }

    if( ErrFlag == (uint8)STD_ON )
    {
        Sec_FailureProc();
    }

    return;
}

/******************************************************************************/
/* Function Name | Sec_Main_PreGenSeed                                        */
/* Description   | MainFunction of SEC_STAT_PRE_SEED                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SEC_CODE_FAST) Sec_Main_PreGenSeed (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = Sec_Usr_GenSeedValue(SEC_GENSEED_START, NULL_PTR, 0U);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        Sec_UpdateJobInfo(SEC_JOB_OK, SEC_STAT_PRE_SEED_FINISH);
    }
    else if( FuncRet == SEC_E_PENDING )
    {
        /* No process */
    }
    else
    {
        Sec_FailureProc();
    }

    return;
}

/******************************************************************************/
/* Function Name | Sec_Main_PostGenSeed                                       */
/* Description   | MainFunction of SEC_STAT_POST_SEED                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SEC_CODE_FAST) Sec_Main_PostGenSeed (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = Sec_Usr_GenSeedValue(SEC_GENSEED_STOP, NULL_PTR, 0U);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        Sec_ClearSecurityInformation();

        Sec_UpdateJobInfo(SEC_JOB_OK, SEC_STAT_IDLE);
    }
    else if( FuncRet == SEC_E_PENDING )
    {
        /* No process */
    }
    else
    {
        Sec_FailureProc();
    }

    return;
}

/******************************************************************************/
/* Function Name | Sec_Main_ReqGenKey                                         */
/* Description   | MainFunction of SEC_STAT_KEY                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SEC_CODE_FAST) Sec_Main_ReqGenKey (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = WrapCrypto_Encrypt(Sec_SeedKeyInfo.FirstDataFlag,
                                Sec_ToolAuthKeyConfig.JobID,
                                Sec_SeedKeyInfo.SeedPtr,
                                Sec_SeedKeyInfo.SeedSize,
                                Sec_SeedKeyInfo.KeyPtr,
                                &Sec_EncryptSize);
    if( (FuncRet == (Std_ReturnType)E_OK) &&
        (Sec_EncryptSize == Sec_SeedKeyInfo.KeySize) )
    {
        Sec_SeedKeyInfo.FirstDataFlag = FALSE;
        Sec_UpdateJobInfo(SEC_JOB_OK, SEC_STAT_KEY_FINISH);
    }
    else if( FuncRet == WRAPCRYPTO_E_PENDING )
    {
        /* No Process */
    }
    else
    {
        Sec_FailureProc();
    }

    return;
}

/******************************************************************************/
/* Function Name | Sec_Main_PreGenKey                                         */
/* Description   | MainFunction of SEC_STAT_PRE_KEY                           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SEC_CODE_FAST) Sec_Main_PreGenKey (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = WrapCrypto_Pre_Encrypt(Sec_ToolAuthKeyConfig.JobID);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        Sec_SeedKeyInfo.FirstDataFlag = TRUE;
        Sec_UpdateJobInfo(SEC_JOB_OK, SEC_STAT_PRE_KEY_FINISH);
    }
    else if( FuncRet == WRAPCRYPTO_E_PENDING )
    {
        /* No Process */
    }
    else
    {
        Sec_FailureProc();
    }

    return;
}

/******************************************************************************/
/* Function Name | Sec_Main_PostGenKey                                        */
/* Description   | MainFunction of SEC_STAT_POST_KEY                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SEC_CODE_FAST) Sec_Main_PostGenKey (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = WrapCrypto_Fin_Encrypt(Sec_ToolAuthKeyConfig.JobID);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        Sec_ClearSecurityInformation();
        Sec_UpdateJobInfo(SEC_JOB_OK, SEC_STAT_IDLE);
    }
    else if( FuncRet == WRAPCRYPTO_E_PENDING )
    {
        /* No Process */
    }
    else
    {
        Sec_FailureProc();
    }

    return;
}

/******************************************************************************/
/* Function Name | Sec_ClearSecurityInformation                               */
/* Description   | Clears security information                                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SEC_CODE_FAST) Sec_ClearSecurityInformation (void)
{
    Sec_SeedKeyInfo.SeedPtr = NULL_PTR;
    Sec_SeedKeyInfo.SeedSize = 0UL;
    Sec_SeedKeyInfo.KeyPtr = NULL_PTR;
    Sec_SeedKeyInfo.KeySize = 0UL;
    Sec_SeedKeyInfo.FirstDataFlag = FALSE;

    Sec_EncryptSize = 0UL;

    Sec_SecurityLevel = 0x00U;

    return;
}

/******************************************************************************/
/* Function Name | Sec_FailureProc                                            */
/* Description   | Failure process                                            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SEC_CODE_FAST) Sec_FailureProc (void)
{
    Sec_ClearSecurityInformation();

    Sec_UpdateJobInfo(SEC_JOB_FAILED, SEC_STAT_IDLE);

    return;
}

/******************************************************************************/
/* Function Name | Sec_UpdateJobInfo                                          */
/* Description   | Updates JobInfo                                            */
/* Preconditions |                                                            */
/* Parameters    | [IN] JobResult   : Result of job                           */
/*               |       SEC_JOB_OK                                           */
/*               |       SEC_JOB_FAILED                                       */
/*               |       SEC_JOB_PENDING                                      */
/*               | [IN] LocalStatus : Local status                            */
/*               |       SEC_STAT_IDLE                                        */
/*               |       SEC_STAT_PRE_SEED                                    */
/*               |       SEC_STAT_PRE_SEED_FINISH                             */
/*               |       SEC_STAT_SEED                                        */
/*               |       SEC_STAT_SEED_FINISH                                 */
/*               |       SEC_STAT_POST_SEED                                   */
/*               |       SEC_STAT_PRE_KEY                                     */
/*               |       SEC_STAT_PRE_KEY_FINISH                              */
/*               |       SEC_STAT_KEY                                         */
/*               |       SEC_STAT_KEY_FINISH                                  */
/*               |       SEC_STAT_POST_KEY                                    */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SEC_CODE_FAST) Sec_UpdateJobInfo
(
    VAR(uint8, AUTOMATIC) JobResult,
    VAR(uint8, AUTOMATIC) LocalStatus
)
{
    VAR(uint8, AUTOMATIC) MaskPattern;

    MaskPattern = Rte_MaskInterruptAll();   /* for JobResult/LocalStatus */
    Sec_JobInfo.JobResult = JobResult;
    Sec_JobInfo.LocalStatus = LocalStatus;
    Rte_UnMaskInterruptAll(MaskPattern);    /* for JobResult/LocalStatus */

    return;
}

/******************************************************************************/
/* Function Name | Sec_GetApiAcceptation                                      */
/* Description   | Acquires the acceptation of executing API                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, SEC_CODE_FAST) Sec_GetApiAcceptation (void)
{
    VAR(uint8, AUTOMATIC) MaskPattern;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    MaskPattern = Rte_MaskInterruptAll();   /* prevent multiple execution */
    if( Sec_ApiAcceptingFlg == (uint8)STD_OFF )
    {
        Sec_ApiAcceptingFlg = STD_ON;
        Ret = E_OK;
    }
    Rte_UnMaskInterruptAll(MaskPattern);    /* prevent multiple execution */

    return Ret;
}

/******************************************************************************/
/* Function Name | Sec_ReleaseApiAcceptation                                  */
/* Description   | Releases the acceptation of executing API                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SEC_CODE_FAST) Sec_ReleaseApiAcceptation (void)
{
    Sec_ApiAcceptingFlg = STD_OFF;

    return;
}

/******************************************************************************/
/* Function Name | Sec_ReportError                                            */
/* Description   | Report the error information                               */
/* Preconditions |                                                            */
/* Parameters    | [IN] ApiId   : API ID                                      */
/*               | [IN] ErrorId : Error ID                                    */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, SEC_CODE_FAST) Sec_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
)
{
    VAR(Rte_EcuM_ErrorType, AUTOMATIC) Error;

    Error.ModuleId = RTE_ECUM_MODULE_SEC;
    Error.ApiId = ApiId;
    Error.ErrorId = ErrorId;

    Rte_EcuM_ReportError(&Error);

    return;
}


#define SEC_STOP_SEC_CODE
#include <Sec_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

