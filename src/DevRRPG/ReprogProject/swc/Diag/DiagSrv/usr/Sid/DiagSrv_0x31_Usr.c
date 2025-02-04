/* DiagSrv_0x31_Usr_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x31/Usr/CODE                                       */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagSrv_Local.h>
#include "DiagSrv_0x31.h"

/*===== Sample ===============================================================*/
#include <Rte.h>
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
#define DIAGSRV_0X31_USR_STAT_IDLE              ((uint8)0x00U)
#define DIAGSRV_0X31_USR_STAT_PRE_ERASE         ((uint8)0x01U)
#define DIAGSRV_0X31_USR_STAT_CHECK_DATA        ((uint8)0x02U)
#define DIAGSRV_0X31_USR_STAT_CHECK_VALID       ((uint8)0x03U)
#define DIAGSRV_0X31_USR_STAT_GET_APLVER        ((uint8)0x04U)

#define DIAGSRV_0X31_USR_APLVER_ADDR            ((uint8 *)0x00FFFDE0UL)
#define DIAGSRV_0X31_USR_APLVER_LOW_4           ((uint8)4U)

#define DIAGSRV_0X31_USR_STATUSMATRIXTBL_NUM    (sizeof(DiagSrv_0x31_Usr_StatusMatrixTbl) / sizeof(DiagSrv_0x31_Usr_StatusMatrixTbl[0]))
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
typedef struct {
    uint8 LocalStatus;
    uint8 JobResult;
} DiagSrv_0x31_Usr_JobInfoType;

typedef struct {
    uint8 LocalStatus;
    uint8 RetStatus;
} DiagSrv_0x31_Usr_StatusMatrixType;

typedef struct {
    uint32 Num;
    P2CONST(DiagSrv_0x31_Usr_StatusMatrixType, TYPEDEF, DIAGSRV_APPL_CONST) MatrixPtr;
} DiagSrv_0x31_Usr_StatusMatrixInfoType;

typedef struct {
    P2VAR(uint8, TYPEDEF, DIAGSRV_APPL_DATA) CheckResultPtr;
    P2VAR(uint8, TYPEDEF, DIAGSRV_APPL_DATA) AplVer;
    uint8 AplVerSize;
} DiagSrv_0x31_Usr_InfoType;
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
/*===== Sample ===============================================================*/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_UpdateJobInfo
(
    VAR(uint8, AUTOMATIC) JobResult,
    VAR(uint8, AUTOMATIC) LocalStatus
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_Time_CheckValidateApl (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_Time_GetAplVersion (void);
/*===== Sample ===============================================================*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

/*===== Sample ===============================================================*/
static VAR(DiagSrv_0x31_Usr_JobInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Usr_Job;
static VAR(DiagSrv_0x31_Usr_InfoType, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Usr_Info;
/*===== Sample ===============================================================*/

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

/*===== Sample ===============================================================*/
static CONST(DiagSrv_0x31_Usr_StatusMatrixType, DIAGSRV_CONST) DiagSrv_0x31_Usr_StatusMatrixTbl[] = {
     { DIAGSRV_0X31_USR_STAT_IDLE,          DIAGSRV_0X31_USR_IDLE }
    ,{ DIAGSRV_0X31_USR_STAT_PRE_ERASE,     DIAGSRV_0X31_USR_BUSY }
    ,{ DIAGSRV_0X31_USR_STAT_CHECK_DATA,    DIAGSRV_0X31_USR_BUSY }
    ,{ DIAGSRV_0X31_USR_STAT_CHECK_VALID,   DIAGSRV_0X31_USR_BUSY }
    ,{ DIAGSRV_0X31_USR_STAT_GET_APLVER,    DIAGSRV_0X31_USR_BUSY }
};
static CONST(AB_83_ConstV DiagSrv_0x31_Usr_StatusMatrixInfoType, DIAGSRV_CONST) DiagSrv_0x31_Usr_StatusMatrixInfo = {
    DIAGSRV_0X31_USR_STATUSMATRIXTBL_NUM,
    &DiagSrv_0x31_Usr_StatusMatrixTbl[0]
};
/*===== Sample ===============================================================*/

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define DIAGSRV_START_SEC_CODE
#include <DiagSrv_MemMap.h>

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Usr_Init                                      */
/* Description   | Initialize                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_Init (void)
{
/*===== Sample ===============================================================*/
    DiagSrv_0x31_Usr_UpdateJobInfo(DIAGSRV_0X31_USR_JOB_FAILED, DIAGSRV_0X31_USR_STAT_IDLE);

    DiagSrv_0x31_Usr_Info.CheckResultPtr = NULL_PTR;
    DiagSrv_0x31_Usr_Info.AplVer         = NULL_PTR;
    DiagSrv_0x31_Usr_Info.AplVerSize     = 0U;
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Usr_Time                                      */
/* Description   | Time function                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_Time (void)
{
/*===== Sample ===============================================================*/
    if( DiagSrv_0x31_Usr_Job.LocalStatus == DIAGSRV_0X31_USR_STAT_PRE_ERASE )
    {
        DiagSrv_0x31_Usr_UpdateJobInfo(DIAGSRV_0X31_USR_JOB_OK, DIAGSRV_0X31_USR_STAT_IDLE);
    }
    else if( DiagSrv_0x31_Usr_Job.LocalStatus == DIAGSRV_0X31_USR_STAT_CHECK_DATA )
    {
        DiagSrv_0x31_Usr_UpdateJobInfo(DIAGSRV_0X31_USR_JOB_OK, DIAGSRV_0X31_USR_STAT_IDLE);
    }
    else if( DiagSrv_0x31_Usr_Job.LocalStatus == DIAGSRV_0X31_USR_STAT_CHECK_VALID )
    {
        DiagSrv_0x31_Usr_Time_CheckValidateApl();
        DiagSrv_0x31_Usr_UpdateJobInfo(DIAGSRV_0X31_USR_JOB_OK, DIAGSRV_0X31_USR_STAT_IDLE);
    }
    else if( DiagSrv_0x31_Usr_Job.LocalStatus == DIAGSRV_0X31_USR_STAT_GET_APLVER )
    {
        DiagSrv_0x31_Usr_Time_GetAplVersion();
        DiagSrv_0x31_Usr_UpdateJobInfo(DIAGSRV_0X31_USR_JOB_OK, DIAGSRV_0X31_USR_STAT_IDLE);
    }
    else
    {
        /* No process */
    }
/*===== Sample ===============================================================*/

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Usr_GetStatus                                 */
/* Description   | Acquires status of job                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Status                                                     */
/*               |  DIAGSRV_0X31_USR_IDLE                                     */
/*               |  DIAGSRV_0X31_USR_BUSY                                     */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_GetStatus (void)
{
/*===== Sample ===============================================================*/
    VAR(uint32, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) Status;

    Status = DIAGSRV_0X31_USR_BUSY;

    for( i = 0UL; i < DiagSrv_0x31_Usr_StatusMatrixInfo.Num; i++ )
    {
        if( DiagSrv_0x31_Usr_Job.LocalStatus == DiagSrv_0x31_Usr_StatusMatrixInfo.MatrixPtr[i].LocalStatus )
        {
            Status = DiagSrv_0x31_Usr_StatusMatrixInfo.MatrixPtr[i].RetStatus;
            break;
        }
    }

    return Status;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Usr_GetJobResult                              */
/* Description   | Acquires result of job                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | JobResult                                                  */
/*               |  DIAGSRV_0X31_USR_JOB_OK                                   */
/*               |  DIAGSRV_0X31_USR_JOB_FAILED                               */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_GetJobResult (void)
{
/*===== Sample ===============================================================*/
    return DiagSrv_0x31_Usr_Job.JobResult;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Usr_ReqPreErase                               */
/* Description   | Pre-erase hook(Async)                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] RewriteAreaNum : Rewrite area number                  */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_ReqPreErase
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    if( DiagSrv_0x31_Usr_Job.LocalStatus == DIAGSRV_0X31_USR_STAT_IDLE )
    {
        DiagSrv_0x31_Usr_UpdateJobInfo(DIAGSRV_0X31_USR_JOB_FAILED, DIAGSRV_0X31_USR_STAT_PRE_ERASE);

        Ret = E_OK;
    }

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Usr_ReqPostCheckData                          */
/* Description   | Post-CheckData hook(Async)                                 */
/* Preconditions |                                                            */
/* Parameters    | [IN] RewriteAreaNum      : Rewrite area number             */
/*               | [IN] CheckTypeIdentifier : checkTypeIdentifier             */
/*               |       DIAGSRV_0X31_CHECKTYPE_SIG                           */
/*               |       DIAGSRV_0X31_CHECKTYPE_CRC                           */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_ReqPostCheckData
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum,
    VAR(uint8, AUTOMATIC) CheckTypeIdentifier
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    if( DiagSrv_0x31_Usr_Job.LocalStatus == DIAGSRV_0X31_USR_STAT_IDLE )
    {
        DiagSrv_0x31_Usr_UpdateJobInfo(DIAGSRV_0X31_USR_JOB_FAILED, DIAGSRV_0X31_USR_STAT_CHECK_DATA);

        Ret = E_OK;
    }

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Usr_ReqCheckValidateApl                       */
/* Description   | Requests checking validateApplication(Async)               */
/* Preconditions |                                                            */
/* Parameters    | [OUT] CheckResult : Checking validateApplication result    */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_ReqCheckValidateApl
(
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) CheckResult
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    if( DiagSrv_0x31_Usr_Job.LocalStatus == DIAGSRV_0X31_USR_STAT_IDLE )
    {
        DiagSrv_0x31_Usr_Info.CheckResultPtr = CheckResult;

        DiagSrv_0x31_Usr_UpdateJobInfo(DIAGSRV_0X31_USR_JOB_FAILED, DIAGSRV_0X31_USR_STAT_CHECK_VALID);

        Ret = E_OK;
    }

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Usr_ReqGetAplVersion                          */
/* Description   | Acquires application version(Async)                        */
/* Preconditions |                                                            */
/* Parameters    | [OUT] AplVer     : Application version                     */
/*               | [IN]  AplVerSize : Application version size                */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | Even if no version information validation is required,     */
/*               | need to set any version.                                   */
/******************************************************************************/
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_ReqGetAplVersion
(
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) AplVer,
    VAR(uint8, AUTOMATIC) AplVerSize
)
{
/*===== Sample ===============================================================*/
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    if( DiagSrv_0x31_Usr_Job.LocalStatus == DIAGSRV_0X31_USR_STAT_IDLE )
    {
        DiagSrv_0x31_Usr_Info.AplVer     = AplVer;
        DiagSrv_0x31_Usr_Info.AplVerSize = AplVerSize;

        DiagSrv_0x31_Usr_UpdateJobInfo(DIAGSRV_0X31_USR_JOB_FAILED, DIAGSRV_0X31_USR_STAT_GET_APLVER);

        Ret = E_OK;
    }

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Usr_CompareAplVersion                         */
/* Description   | Compare application version                                */
/* Preconditions |                                                            */
/* Parameters    | [IN] OldAplVer  : Old application version                  */
/*               | [IN] NewAplVer  : New application version                  */
/*               | [IN] AplVerSize : Application version size                 */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | - Please implement the process to compare versions(*).     */
/*               |    * : NewAplVer >= OldAplVer                              */
/*               | - If no version information validation is required, do not */
/*               |   compare and return E_OK.                                 */
/******************************************************************************/
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_CompareAplVersion
(
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) OldAplVer,
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) NewAplVer,
    VAR(uint8, AUTOMATIC) AplVerSize
)
{
/*===== Sample ===============================================================*/
    VAR(uint32, AUTOMATIC) OldVerNum;
    VAR(uint32, AUTOMATIC) NewVerNum;
    VAR(uint8, AUTOMATIC) ComparePos;
    VAR(uint8, AUTOMATIC) EncryptFlag;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    if( OldAplVer != NULL_PTR )
    {
        /* Sample                                                          */
        /* If the Encryption Flag is OFF, skipping version validation.     */
        /* If the Encryption Flag is ON, compares the lower 4 byte values. */
        EncryptFlag = DiagSrv_GetEncryptionFlag();
        if( EncryptFlag == DIAGSRV_ENCRYPTIONFLAG_OFF )
        {
            Ret = E_OK;
        }
        else
        {
            if( AplVerSize >= DIAGSRV_0X31_USR_APLVER_LOW_4 )
            {
                ComparePos = AplVerSize - DIAGSRV_0X31_USR_APLVER_LOW_4;
                OldVerNum = Rte_Rpg_ByteCombine(&OldAplVer[ComparePos], sizeof(OldVerNum));
                NewVerNum = Rte_Rpg_ByteCombine(&NewAplVer[ComparePos], sizeof(NewVerNum));

                if( OldVerNum <= NewVerNum )
                {
                    Ret = E_OK;
                }
            }
        }
    }
    else
    {
        Ret = E_OK;
    }

    return Ret;
/*===== Sample ===============================================================*/
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/
/*===== Sample ===============================================================*/
/******************************************************************************/
/* Function Name | DiagSrv_0x31_Usr_UpdateJobInfo                             */
/* Description   | Update job information                                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] JobResult   : Result of job                           */
/*               |       DIAGSRV_0X31_USR_JOB_OK                              */
/*               |       DIAGSRV_0X31_USR_JOB_FAILED                          */
/*               | [IN] LocalStatus : Status of job                           */
/*               |       DIAGSRV_0X31_USR_STAT_IDLE                           */
/*               |       DIAGSRV_0X31_USR_STAT_PRE_ERASE                      */
/*               |       DIAGSRV_0X31_USR_STAT_CHECK_DATA                     */
/*               |       DIAGSRV_0X31_USR_STAT_CHECK_VALID                    */
/*               |       DIAGSRV_0X31_USR_STAT_GET_APLVER                     */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_UpdateJobInfo
(
    VAR(uint8, AUTOMATIC) JobResult,
    VAR(uint8, AUTOMATIC) LocalStatus
)
{
    DiagSrv_0x31_Usr_Job.JobResult = JobResult;
    DiagSrv_0x31_Usr_Job.LocalStatus = LocalStatus;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Usr_Time_CheckValidateApl                     */
/* Description   | Checks validate application                                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_Time_CheckValidateApl (void)
{
    P2CONST(DiagSrv_RewriteAreaStatusType, AUTOMATIC, DIAGSRV_APPL_CONST) RewriteAreaStatus;
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) CheckResult;

    CheckResult = DIAGSRV_0X31_USR_VALID_OK;

    RewriteAreaStatus = DiagSrv_GetRewriteAreaStatusInfo();

    for( i = 0U; i < RewriteAreaStatus->StatusInfoNum; i++ )
    {
        /* Has the writing of all areas been completed? */
        if( RewriteAreaStatus->StatusInfoPtr[i].Status != DIAGSRV_LBSTAT_REWRITING_OK )
        {
            CheckResult = DIAGSRV_0X31_USR_VALID_NG;
            break;
        }
    }

    if( CheckResult == DIAGSRV_0X31_USR_VALID_NG )
    {
        /* Did RPRG start from APL enabled state? */
        if( (RewriteAreaStatus->BootInfoPtr->ExtendedBootMode == DIAGSRV_EXT_BOOT_MODE_APL) ||
            (RewriteAreaStatus->BootInfoPtr->ExtendedBootMode == DIAGSRV_EXT_BOOT_MODE_STAYINBOOT) )
        {
            CheckResult = DIAGSRV_0X31_USR_ALREADY_VALID;

            for( i = 0U; i < RewriteAreaStatus->StatusInfoNum; i++ )
            {
                /* Hasn't the writing of all areas started? */
                if( RewriteAreaStatus->StatusInfoPtr[i].Status != DIAGSRV_LBSTAT_BEFORE_REWRITING )
                {
                    CheckResult = DIAGSRV_0X31_USR_VALID_NG;
                    break;
                }
            }
        }
    }

    *DiagSrv_0x31_Usr_Info.CheckResultPtr = CheckResult;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Usr_Time_GetAplVersion                        */
/* Description   | Gets application version                                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Usr_Time_GetAplVersion (void)
{
    VAR(uint8, AUTOMATIC) EncryptFlag;

    /* Sample                                                               */
    /* If the Encryption Flag is OFF, fixed value 0 is the written version. */
    /* If the Encryption Flag is ON, read the version of the APL area.      */
    EncryptFlag = DiagSrv_GetEncryptionFlag();
    if( EncryptFlag == DIAGSRV_ENCRYPTIONFLAG_OFF )
    {
        Rte_Rpg_MemSet(DiagSrv_0x31_Usr_Info.AplVer,
                        0U,
                        (uint32)DiagSrv_0x31_Usr_Info.AplVerSize);
    }
    else
    {
        Rte_Rpg_MemCopy(DiagSrv_0x31_Usr_Info.AplVer,
                        DIAGSRV_0X31_USR_APLVER_ADDR,
                        (uint32)DiagSrv_0x31_Usr_Info.AplVerSize);
    }

    return;
}
/*===== Sample ===============================================================*/

#define DIAGSRV_STOP_SEC_CODE
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

