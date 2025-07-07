/* DiagSrv_0x27_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x27/CODE                                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Sec.h>
#include <Rte.h>
#include <DiagLib.h>

#include <DiagSrv.h>
#include "DiagSrv_0x27.h"
#include "DiagSrv_0x27_Cfg.h"
#include "DiagSrv_Local.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_0X27_JOB_STAT_IDLE              ((uint8)0x01U)
#define DIAGSRV_0X27_JOB_STAT_PRE_SEED          ((uint8)0x12U)
#define DIAGSRV_0X27_JOB_STAT_SEED              ((uint8)0x14U)
#define DIAGSRV_0X27_JOB_STAT_POST_SEED         ((uint8)0x18U)
#define DIAGSRV_0X27_JOB_STAT_PRE_KEY           ((uint8)0x22U)
#define DIAGSRV_0X27_JOB_STAT_KEY               ((uint8)0x24U)
#define DIAGSRV_0X27_JOB_STAT_POST_KEY          ((uint8)0x28U)

#define DIAGSRV_0X27_E_PENDING                  ((Std_ReturnType)0x02U)
#define DIAGSRV_0X27_E_NO_RES                   ((Std_ReturnType)0x03U)

#define DIAGSRV_0X27_ENTRYPRM_APDLYTM_INDEX     ((uint8)12U)
#define DIAGSRV_0X27_ENTRYPRM_APDLYTM_LEN       ((uint8)2U)

#define DIAGSRV_0X27_SEED_NONE                  ((uint8)0U)
#define DIAGSRV_0X27_DLYTM_CLEAR                ((uint16)0U)
#define DIAGSRV_0X27_DLYTM_NOT_SUPPORT          ((uint16)0U)
#define DIAGSRV_0X27_SUBFUNC_SEED_MASK          ((uint8)0x01U)
#define DIAGSRV_0X27_ATTCNT_MAX                 ((uint8)255U)
#define DIAGSRV_0X27_ATTCNT_NOT_SUPPORT         ((uint8)0U)
#define DIAGSRV_0X27_USEC_TO_MSEC               ((uint32)1000UL)
#define DIAGSRV_0X27_CURRENT_SECLEVEL           (DiagSrv_0x27_SecLevInfoIndex + (uint8)1U)

#define DIAGSRV_0X27_SID_POS                    ((uint8)0U)
#define DIAGSRV_0X27_SUBFUNC_POS                ((uint8)1U)
#define DIAGSRV_0X27_REQ_KEY_POS                ((uint8)2U)

#define DIAGSRV_0X27_RES_MSG_SENDKEY_LEN        ((uint16)2U)

#define DIAGSRV_0X27_API_ID_INIT                ((uint8)0x00U)
#define DIAGSRV_0X27_API_ID_CHECK_DELAYTIMER    ((uint8)0x01U)
#define DIAGSRV_0X27_API_ID_POST_GENERATE_KEY   ((uint8)0x02U)

#define DIAGSRV_0X27_E_CASE_TM_FAIL             ((uint8)0x01U)

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    Rte_Tm_PredefTimer1us32bitType  DelayTimer;
    uint16  ApDelayTimer;
    uint8   DelayTimerActFlg;
    uint8   AttCnt;
    uint8   SeedValidFlg;
    Sec_SeedInfoType    SeedInfo;
    Sec_KeyInfoType     KeyInfo;
} DiagSrv_0x27_SaveInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x27_Processing_requestSeed
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg,
    VAR(uint8, AUTOMATIC) Index,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Nrc
);
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x27_Processing_sendKey
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg,
    VAR(uint8, AUTOMATIC) Index,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Nrc
);
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x27_Time_PreGenerateSeed
(
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Nrc
);
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x27_Time_GenerateSeed
(
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Nrc
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x27_Time_PostGenerateSeed (void);
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x27_Time_PreGenerateKey
(
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Nrc
);
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x27_Time_GenerateKey
(
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Nrc
);
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x27_Time_PostGenerateKey
(
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Nrc
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x27_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x27_SearchSecLevInfo
(
    VAR(uint8, AUTOMATIC) SecurityAccessType
);
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x27_CheckDelayTimer
(
    P2VAR(DiagSrv_0x27_SaveInfoType, AUTOMATIC, DIAGSRV_APPL_DATA) SaveInfo,
    P2CONST(DiagSrv_0x27_SecLevelInfoConfigType, AUTOMATIC, DIAGSRV_APPL_CONST) SecLevelInfo,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Nrc
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x27_MakePosRsp_requestSeed
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg,
    P2CONST(Sec_SeedInfoType, AUTOMATIC, DIAGSRV_APPL_CONST) SeedInfo
);

/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x27_LastrequestSeed;
static VAR(DiagSrv_0x27_SaveInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_0x27_SaveInfo[DIAGSRV_CFG_0X27_SUPPORT_SECLEVEL_NUM];
static P2VAR(Diag_MsgContextType, DIAGSRV_VAR_CLEARED, DIAGSRV_APPL_DATA) DiagSrv_0x27_Msg;
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x27_JobStatus;
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x27_SecLevInfoIndex;

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define DIAGSRV_START_SEC_CODE
#include <DiagSrv_MemMap.h>

/******************************************************************************/
/* Function Name | DiagSrv_0x27_Init                                          */
/* Description   | Initialize                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x27_Init (void)
{
    VAR(uint8, AUTOMATIC) BootMode;
    P2CONST(Rte_UsrSoftIf_EntryParamType, AUTOMATIC, DIAGSRV_APPL_CONST) Param;
    VAR(Std_ReturnType, AUTOMATIC) TmRet;
    VAR(uint8, AUTOMATIC) Index;

    BootMode = Rte_EcuM_GetBootMode();
    if( BootMode == RTE_ECUM_START_AP_ENTRY )
    {
        Param = Rte_UsrSoftIf_GetEntryParam();
    }

    for( Index = 0U; Index < DiagSrv_0x27_SecLevelConfig.Num; Index++ )
    {
        DiagSrv_0x27_SaveInfo[Index].DelayTimer.StartPoint = (uint32)DIAGSRV_0X27_DLYTM_CLEAR;
        DiagSrv_0x27_SaveInfo[Index].ApDelayTimer = DIAGSRV_0X27_DLYTM_CLEAR;
        DiagSrv_0x27_SaveInfo[Index].DelayTimerActFlg = STD_OFF;
        DiagSrv_0x27_SaveInfo[Index].AttCnt = 0U;
        DiagSrv_0x27_SaveInfo[Index].SeedValidFlg = STD_OFF;
        DiagSrv_0x27_SaveInfo[Index].SeedInfo.Seed = DiagSrv_0x27_SecLevelConfig.InfoPtr[Index].SeedPtr;
        DiagSrv_0x27_SaveInfo[Index].SeedInfo.SeedSize = DiagSrv_0x27_SecLevelConfig.InfoPtr[Index].SeedSize;
        DiagSrv_0x27_SaveInfo[Index].KeyInfo.Key = DiagSrv_0x27_SecLevelConfig.InfoPtr[Index].KeyPtr;
        DiagSrv_0x27_SaveInfo[Index].KeyInfo.KeySize = DiagSrv_0x27_SecLevelConfig.InfoPtr[Index].KeySize;

/*      Rte_Rpg_MemSet(DiagSrv_0x27_SaveInfo[Index].SeedInfo.Seed, 0U, (uint32)DiagSrv_0x27_SaveInfo[Index].SeedInfo.SeedSize); */ /* @@@ */
        Rte_Rpg_MemSet(DiagSrv_0x27_SaveInfo[Index].SeedInfo.Seed, 0x5aU, (uint32)DiagSrv_0x27_SaveInfo[Index].SeedInfo.SeedSize); /* @@@ */
        Rte_Rpg_MemSet(DiagSrv_0x27_SaveInfo[Index].KeyInfo.Key, 0U, (uint32)DiagSrv_0x27_SaveInfo[Index].KeyInfo.KeySize);

        if( DiagSrv_0x27_SecLevelConfig.InfoPtr[Index].DelayTimer != DIAGSRV_0X27_DLYTM_NOT_SUPPORT )
        {
            if( BootMode == RTE_ECUM_START_AP_ENTRY )
            {
                DiagSrv_0x27_SaveInfo[Index].ApDelayTimer = (uint16)Rte_Rpg_ByteCombine(
                                &Param->EntryParam[DIAGSRV_0X27_ENTRYPRM_APDLYTM_INDEX],
                                DIAGSRV_0X27_ENTRYPRM_APDLYTM_LEN);
            }

            if( (BootMode != RTE_ECUM_START_AP_ENTRY) ||
                (DiagSrv_0x27_SaveInfo[Index].ApDelayTimer != DIAGSRV_0X27_DLYTM_CLEAR) )
            {
                if( DiagSrv_0x27_SecLevelConfig.InfoPtr[Index].DelayTimer > DiagSrv_0x27_SaveInfo[Index].ApDelayTimer )
                {
                    TmRet = Rte_Tm_ResetTimer1us32bit(&DiagSrv_0x27_SaveInfo[Index].DelayTimer);
                    if( TmRet != (Std_ReturnType)E_OK )
                    {
                        DiagSrv_0x27_ReportError(DIAGSRV_0X27_API_ID_INIT, DIAGSRV_0X27_E_CASE_TM_FAIL);
                        break;
                    }
                    DiagSrv_0x27_SaveInfo[Index].DelayTimerActFlg = STD_ON;
                }
                else
                {
                    DiagSrv_0x27_SaveInfo[Index].ApDelayTimer = DIAGSRV_0X27_DLYTM_CLEAR;
                }
            }
        }
    }

    DiagSrv_0x27_Msg = NULL_PTR;
    DiagSrv_0x27_SecLevInfoIndex = 0U;
    DiagSrv_0x27_LastrequestSeed = DIAGSRV_0X27_SEED_NONE;
    DiagSrv_0x27_JobStatus = DIAGSRV_0X27_JOB_STAT_IDLE;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x27_Time                                          */
/* Description   | Time function                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x27_Time (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) SecStatus;
    VAR(uint8, AUTOMATIC) SecJobResult;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    if( DiagSrv_0x27_JobStatus != DIAGSRV_0X27_JOB_STAT_IDLE )
    {
        Ret = DIAGSRV_0X27_E_PENDING;
        Nrc = DIAG_NRC_PR;

#if 0	/* @@@ */
        SecStatus = Sec_GetStatus();
        if( SecStatus == SEC_IDLE )
        {
            SecJobResult = Sec_GetJobResult();
            if( SecJobResult != SEC_JOB_OK )
            {
                Nrc = DIAG_NRC_GR;
                Ret = E_NOT_OK;
            }
            else
            {
#endif	/* @@@ */
                if( DiagSrv_0x27_JobStatus == DIAGSRV_0X27_JOB_STAT_PRE_SEED )
                {
/*                    Ret = DiagSrv_0x27_Time_PreGenerateSeed(&Nrc);*//* @@@ */
                    DiagSrv_0x27_Time_PostGenerateSeed(); /* @@@ */
                    Ret = E_OK; /* @@@ */
                }
                else if( DiagSrv_0x27_JobStatus == DIAGSRV_0X27_JOB_STAT_SEED )
                {
                    Ret = DiagSrv_0x27_Time_GenerateSeed(&Nrc);
                }
                else if( DiagSrv_0x27_JobStatus == DIAGSRV_0X27_JOB_STAT_POST_SEED )
                {
                    DiagSrv_0x27_Time_PostGenerateSeed();
                    Ret = E_OK;
                }
                else if( DiagSrv_0x27_JobStatus == DIAGSRV_0X27_JOB_STAT_PRE_KEY )
                {
/*                    Ret = DiagSrv_0x27_Time_PreGenerateKey(&Nrc);*//* @@@ */
                    Ret = DiagSrv_0x27_Time_PostGenerateKey(&Nrc); /* @@@ */
                }
                else if( DiagSrv_0x27_JobStatus == DIAGSRV_0X27_JOB_STAT_KEY )
                {
                    Ret = DiagSrv_0x27_Time_GenerateKey(&Nrc);
                }
                else /* if( DiagSrv_0x27_JobStatus == DIAGSRV_0X27_JOB_STAT_POST_KEY ) */
                {
                    Ret = DiagSrv_0x27_Time_PostGenerateKey(&Nrc);
                }
#if 0 /* @@@ */
            }
        }
#endif /* @@@ */

        if( Ret == (Std_ReturnType)E_OK )
        {
            DiagLib_SendPosRsp(DiagSrv_0x27_Msg);
            DiagSrv_0x27_Msg = NULL_PTR;
        }
        else if( Ret == DIAGSRV_0X27_E_PENDING )
        {
            /* No process */
        }
        else if( Ret == DIAGSRV_0X27_E_NO_RES )
        {
            /* No process(execute reset process) */
        }
        else
        {
            DiagSrv_0x27_JobStatus = DIAGSRV_0X27_JOB_STAT_IDLE;
            DiagLib_SendNegRsp(Nrc, DiagSrv_0x27_Msg);
            DiagSrv_0x27_Msg = NULL_PTR;
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x27_Processing                                    */
/* Description   | Processing function                                        */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x27_Processing
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
)
{
    VAR(uint8, AUTOMATIC) Subfunc;
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Index;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;
    Index = 0U;
    Nrc = DiagLib_CheckSubfunctionSupport(Msg,
                                          &DiagSrv_0x27_SubfuncConfig,
                                          &Index);

    if( Nrc == DIAG_NRC_PR )
    {
        Subfunc = DIAG_GET_SUBFUNCTION(Msg);
        if( (Subfunc & DIAGSRV_0X27_SUBFUNC_SEED_MASK) == DIAGSRV_0X27_SUBFUNC_SEED_MASK )
        {
            Ret = DiagSrv_0x27_Processing_requestSeed(Msg, Index, &Nrc);
        }
        else
        {
            Ret = DiagSrv_0x27_Processing_sendKey(Msg, Index, &Nrc);
        }
    }

    if( Ret == (Std_ReturnType)E_OK )
    {
        DiagLib_SendPosRsp(Msg);
    }
    else if( Ret == DIAGSRV_0X27_E_PENDING )
    {
        DiagSrv_0x27_Msg = Msg;
    }
    else if( Ret == DIAGSRV_0X27_E_NO_RES )
    {
        /* No process(execute reset process) */
    }
    else
    {
        DiagSrv_0x27_LastrequestSeed = DIAGSRV_0X27_SEED_NONE;
        DiagLib_SendNegRsp(Nrc, Msg);
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x27_Confirmation                                  */
/* Description   | Confirmation function                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] Status : Transmission complete status                 */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x27_Confirmation
(
    VAR(uint8, AUTOMATIC) Status
)
{
    /* No process */
    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x27_NotifyChangeSession                           */
/* Description   | Notify change session function                             */
/* Preconditions |                                                            */
/* Parameters    | [IN] OldSession : Before the changes                       */
/*               | [IN] NewSession : After the changes                        */
/*               | [IN] Factor     : Change factor                            */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x27_NotifyChangeSession
(
    VAR(uint8, AUTOMATIC) OldSession,
    VAR(uint8, AUTOMATIC) NewSession,
    VAR(uint8, AUTOMATIC) Factor
)
{
    DiagSrv_0x27_LastrequestSeed = DIAGSRV_0X27_SEED_NONE;
    DiagLib_SetSecurityLockAll();

    return;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/


/******************************************************************************/
/* Function Name | DiagSrv_0x27_Processing_requestSeed                        */
/* Description   | Processing function of requestSeed                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg   : Message                                       */
/*               | [IN] Index : DiagSrv_0x27_SubfuncInfoConfig index          */
/*               | [OUT] Nrc  : NRC                                           */
/* Return Value  | Result                                                     */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x27_Processing_requestSeed
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg,
    VAR(uint8, AUTOMATIC) Index,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Nrc
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) SecRet;
    VAR(uint8, AUTOMATIC) Subfunc;
    P2VAR(DiagSrv_0x27_SaveInfoType, AUTOMATIC, DIAGSRV_APPL_DATA) SaveInfoPtr;
    P2CONST(DiagSrv_0x27_SecLevelInfoConfigType, AUTOMATIC, DIAGSRV_APPL_CONST) SecLevelInfoConfigPtr;
    VAR(uint8, AUTOMATIC) LockStatus;

    Ret = E_NOT_OK;
    *Nrc = DIAG_NRC_IMLOIF;
    DiagSrv_0x27_LastrequestSeed = DIAGSRV_0X27_SEED_NONE;

    if( Msg->ReqDataLen == (DIAG_SUBFUNCMSG_MIN_SIZE + DiagSrv_0x27_SubfuncConfig.InfoPtr[Index].Length) )
    {
        *Nrc = RpgMfr_MsgCheckCondition(Msg);
        if( *Nrc == DIAG_NRC_PR )
        {
            *Nrc = RpgSpp_MsgCheckCondition(Msg);
        }
    }

    if( *Nrc == DIAG_NRC_PR )
    {
        Subfunc = DIAG_GET_SUBFUNCTION(Msg);
        DiagSrv_0x27_SecLevInfoIndex = DiagSrv_0x27_SearchSecLevInfo(Subfunc);
        SaveInfoPtr = &DiagSrv_0x27_SaveInfo[DiagSrv_0x27_SecLevInfoIndex];
        SecLevelInfoConfigPtr = &DiagSrv_0x27_SecLevelConfig.InfoPtr[DiagSrv_0x27_SecLevInfoIndex];

        Ret = DiagSrv_0x27_CheckDelayTimer(SaveInfoPtr, SecLevelInfoConfigPtr, Nrc);
        if( Ret == (Std_ReturnType)E_OK )
        {
            Ret = DIAGSRV_0X27_E_PENDING;

            LockStatus = DiagLib_GetSecurityLockStatusLevel(DIAGSRV_0X27_CURRENT_SECLEVEL);
            if( LockStatus == DIAG_SECURITY_UNLOCK )
            {
                Ret = E_OK;
            }
            else
            {
                if( SecLevelInfoConfigPtr->StaticSeed == DIAG_SUPPORT )
                {
                    if( SaveInfoPtr->SeedValidFlg == (uint8)STD_ON )
                    {
                        DiagSrv_0x27_LastrequestSeed = Subfunc;
                        Ret = E_OK;
                    }
                }
            }

            if( Ret == DIAGSRV_0X27_E_PENDING )
            {
#if 0	/* @@@ */
                SecRet = Sec_ReqPreGenSeed(DIAGSRV_0X27_CURRENT_SECLEVEL);
                if( SecRet != (Std_ReturnType)E_OK )
                {
                    *Nrc = DIAG_NRC_GR;
                    Ret = E_NOT_OK;
                }
                else
                {
                    DiagSrv_0x27_JobStatus = DIAGSRV_0X27_JOB_STAT_PRE_SEED;
                }
#else	/* @@@ */
                DiagSrv_0x27_JobStatus = DIAGSRV_0X27_JOB_STAT_PRE_SEED; /* @@@ */
#endif	/* @@@ */
            }
            else /* ( Ret == (Std_ReturnType)E_OK ) */
            {
                DiagSrv_0x27_MakePosRsp_requestSeed(Msg, &SaveInfoPtr->SeedInfo);
            }
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x27_Processing_sendKey                            */
/* Description   | Processing function of sendkey                             */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg   : Message                                       */
/*               | [IN] Index : DiagSrv_0x27_SubfuncInfoConfig index          */
/*               | [OUT] Nrc  : NegativeResponseCode                          */
/* Return Value  | Result                                                     */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x27_Processing_sendKey
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg,
    VAR(uint8, AUTOMATIC) Index,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Nrc
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) SecRet;
    VAR(uint8, AUTOMATIC) Subfunc;
    P2VAR(DiagSrv_0x27_SaveInfoType, AUTOMATIC, DIAGSRV_APPL_DATA) SaveInfoPtr;
    P2CONST(DiagSrv_0x27_SecLevelInfoConfigType, AUTOMATIC, DIAGSRV_APPL_CONST) SecLevelInfoConfigPtr;

    Ret = E_NOT_OK;
    *Nrc = DIAG_NRC_RSE;

    Subfunc = DIAG_GET_SUBFUNCTION(Msg);
    if( (uint8)(DiagSrv_0x27_LastrequestSeed + (uint8)1U) == Subfunc )
    {
        if( Msg->ReqDataLen != (DIAG_SUBFUNCMSG_MIN_SIZE + DiagSrv_0x27_SubfuncConfig.InfoPtr[Index].Length) )
        {
            *Nrc = DIAG_NRC_IMLOIF;
        }
        else
        {
            *Nrc = RpgMfr_MsgCheckCondition(Msg);
            if( *Nrc == DIAG_NRC_PR )
            {
                *Nrc = RpgSpp_MsgCheckCondition(Msg);
            }
        }
    }

    if( ((*Nrc == DIAG_NRC_RSE) && (DiagSrv_0x27_LastrequestSeed != DIAGSRV_0X27_SEED_NONE)) || 
        (*Nrc == DIAG_NRC_IMLOIF) )
    {
        SecLevelInfoConfigPtr = &DiagSrv_0x27_SecLevelConfig.InfoPtr[DiagSrv_0x27_SecLevInfoIndex];
        if( SecLevelInfoConfigPtr->AttCnt != DIAGSRV_0X27_ATTCNT_NOT_SUPPORT )
        {
            SaveInfoPtr = &DiagSrv_0x27_SaveInfo[DiagSrv_0x27_SecLevInfoIndex];
            if( SaveInfoPtr->AttCnt < DIAGSRV_0X27_ATTCNT_MAX )
            {
                SaveInfoPtr->AttCnt++;
            }
        }
    }
    else if( *Nrc == DIAG_NRC_PR )
    {
        Ret = DIAGSRV_0X27_E_PENDING;

#if 0	/* @@@ */
        SecRet = Sec_ReqPreGenKey(DIAGSRV_0X27_CURRENT_SECLEVEL);
        if( SecRet != (Std_ReturnType)E_OK )
        {
            *Nrc = DIAG_NRC_GR;
            Ret = E_NOT_OK;
        }
        else
        {
            DiagSrv_0x27_JobStatus = DIAGSRV_0X27_JOB_STAT_PRE_KEY;
        }
#else	/* @@@ */
        DiagSrv_0x27_JobStatus = DIAGSRV_0X27_JOB_STAT_PRE_KEY; /* @@@ */
#endif	/* @@@ */
    }
    else
    {
        /* No process */
    }

    DiagSrv_0x27_LastrequestSeed = DIAGSRV_0X27_SEED_NONE;

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x27_Time_PreGenerateSeed                          */
/* Description   | Time function of generating seed preprocessing             */
/* Preconditions |                                                            */
/* Parameters    | [OUT] Nrc : NRC                                            */
/* Return Value  | Result                                                     */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x27_Time_PreGenerateSeed
(
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Nrc
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) SecRet;
    P2CONST(DiagSrv_0x27_SaveInfoType, AUTOMATIC, DIAGSRV_APPL_CONST) SaveInfoPtr;

    Ret = E_NOT_OK;
    *Nrc = DIAG_NRC_GR;
    SaveInfoPtr = &DiagSrv_0x27_SaveInfo[DiagSrv_0x27_SecLevInfoIndex];

    SecRet = Sec_ReqGenSeed(&SaveInfoPtr->SeedInfo);
    if( SecRet == (Std_ReturnType)E_OK )
    {
        DiagSrv_0x27_JobStatus = DIAGSRV_0X27_JOB_STAT_SEED;
        *Nrc = DIAG_NRC_PR;
        Ret = DIAGSRV_0X27_E_PENDING;
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x27_Time_GenerateSeed                             */
/* Description   | Time function of generating seed processing                */
/* Preconditions |                                                            */
/* Parameters    | [OUT] Nrc : NRC                                            */
/* Return Value  | Result                                                     */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x27_Time_GenerateSeed
(
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Nrc
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) SecRet;

    Ret = E_NOT_OK;
    *Nrc = DIAG_NRC_GR;

    SecRet = Sec_ReqPostGenSeed();
    if( SecRet == (Std_ReturnType)E_OK )
    {
        DiagSrv_0x27_JobStatus = DIAGSRV_0X27_JOB_STAT_POST_SEED;
        *Nrc = DIAG_NRC_PR;
        Ret = DIAGSRV_0X27_E_PENDING;
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x27_Time_PostGenerateSeed                         */
/* Description   | Time function of generating seed postprocessing            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x27_Time_PostGenerateSeed (void)
{
    P2VAR(DiagSrv_0x27_SaveInfoType, AUTOMATIC, DIAGSRV_APPL_DATA) SaveInfoPtr;
    P2CONST(DiagSrv_0x27_SecLevelInfoConfigType, AUTOMATIC, DIAGSRV_APPL_CONST) SecLevelInfoConfigPtr;

    SaveInfoPtr = &DiagSrv_0x27_SaveInfo[DiagSrv_0x27_SecLevInfoIndex];
    SecLevelInfoConfigPtr = &DiagSrv_0x27_SecLevelConfig.InfoPtr[DiagSrv_0x27_SecLevInfoIndex];

    DiagSrv_0x27_MakePosRsp_requestSeed(DiagSrv_0x27_Msg, &SaveInfoPtr->SeedInfo);

    if( SecLevelInfoConfigPtr->StaticSeed == DIAG_SUPPORT )
    {
        SaveInfoPtr->SeedValidFlg = STD_ON;
    }

    DiagSrv_0x27_LastrequestSeed = DIAG_GET_SUBFUNCTION(DiagSrv_0x27_Msg);
    DiagSrv_0x27_JobStatus = DIAGSRV_0X27_JOB_STAT_IDLE;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x27_Time_PreGenerateKey                           */
/* Description   | Time function of generating key preprocessing              */
/* Preconditions |                                                            */
/* Parameters    | [OUT] Nrc : NRC                                            */
/* Return Value  | Result                                                     */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x27_Time_PreGenerateKey
(
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Nrc
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) SecRet;
    P2CONST(DiagSrv_0x27_SaveInfoType, AUTOMATIC, DIAGSRV_APPL_CONST) SaveInfoPtr;

    Ret = E_NOT_OK;
    *Nrc = DIAG_NRC_GR;
    SaveInfoPtr = &DiagSrv_0x27_SaveInfo[DiagSrv_0x27_SecLevInfoIndex];

    SecRet = Sec_ReqGenKey(&SaveInfoPtr->SeedInfo, &SaveInfoPtr->KeyInfo);
    if( SecRet == (Std_ReturnType)E_OK )
    {
        DiagSrv_0x27_JobStatus = DIAGSRV_0X27_JOB_STAT_KEY;
        *Nrc = DIAG_NRC_PR;
        Ret = DIAGSRV_0X27_E_PENDING;
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x27_Time_GenerateKey                              */
/* Description   | Time function of generating key processing                 */
/* Preconditions |                                                            */
/* Parameters    | [OUT] Nrc : NRC                                            */
/* Return Value  | Result                                                     */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x27_Time_GenerateKey
(
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Nrc
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) SecRet;

    Ret = E_NOT_OK;
    *Nrc = DIAG_NRC_GR;

    SecRet = Sec_ReqPostGenKey();
    if( SecRet == (Std_ReturnType)E_OK )
    {
        DiagSrv_0x27_JobStatus = DIAGSRV_0X27_JOB_STAT_POST_KEY;
        *Nrc = DIAG_NRC_PR;
        Ret = DIAGSRV_0X27_E_PENDING;
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x27_Time_PostGenerateKey                          */
/* Description   | Time function of generating key postprocessing             */
/* Preconditions |                                                            */
/* Parameters    | [OUT] Nrc : NRC                                            */
/* Return Value  | Result                                                     */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x27_Time_PostGenerateKey
(
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Nrc
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) DiagLibRet;
    VAR(Std_ReturnType, AUTOMATIC) TmRet;
    P2VAR(DiagSrv_0x27_SaveInfoType, AUTOMATIC, DIAGSRV_APPL_DATA) SaveInfoPtr;
    P2CONST(DiagSrv_0x27_SecLevelInfoConfigType, AUTOMATIC, DIAGSRV_APPL_CONST) SecLevelInfoConfigPtr;
    VAR(uint8, AUTOMATIC) Index;

    *Nrc = DIAG_NRC_PR;
    Ret = E_OK;
    SaveInfoPtr = &DiagSrv_0x27_SaveInfo[DiagSrv_0x27_SecLevInfoIndex];
#if 0	/* @@@ */
    for( Index = 0U; Index < SaveInfoPtr->KeyInfo.KeySize; Index++ )
    {
        if( SaveInfoPtr->KeyInfo.Key[Index] != DiagSrv_0x27_Msg->ReqData[DIAGSRV_0X27_REQ_KEY_POS+Index] )
        {
            Ret = E_NOT_OK;
            break;
        }
    }
#endif	/* @@@ */

    Rte_Rpg_MemSet(SaveInfoPtr->KeyInfo.Key, 0U, (uint32)SaveInfoPtr->KeyInfo.KeySize);

    if( Ret == (Std_ReturnType)E_OK )
    {
        Rte_Rpg_MemSet(SaveInfoPtr->SeedInfo.Seed, 0U, (uint32)SaveInfoPtr->SeedInfo.SeedSize);
        SaveInfoPtr->AttCnt = 0U;
        SaveInfoPtr->SeedValidFlg = (uint8)STD_OFF;
        DiagSrv_0x27_JobStatus = DIAGSRV_0X27_JOB_STAT_IDLE;

        DiagLibRet = DiagLib_SetSecurityUnlockLevel(DIAGSRV_0X27_CURRENT_SECLEVEL);
        if( DiagLibRet != (Std_ReturnType)E_OK )
        {
            *Nrc = DIAG_NRC_GR;
            Ret = E_NOT_OK;
        }
        else
        {
            DiagSrv_0x27_Msg->ResData[DIAGSRV_0X27_SID_POS] = DIAG_MAKE_POSRSP_SID(DiagSrv_0x27_Msg);
            DiagSrv_0x27_Msg->ResData[DIAGSRV_0X27_SUBFUNC_POS] = DIAG_GET_SUBFUNCTION(DiagSrv_0x27_Msg);
            DiagSrv_0x27_Msg->ResDataLen = DIAGSRV_0X27_RES_MSG_SENDKEY_LEN;
        }
    }
    else
    {
        SecLevelInfoConfigPtr = &DiagSrv_0x27_SecLevelConfig.InfoPtr[DiagSrv_0x27_SecLevInfoIndex];
        if( SecLevelInfoConfigPtr->AttCnt != DIAGSRV_0X27_ATTCNT_NOT_SUPPORT )
        {
            if( SaveInfoPtr->AttCnt < DIAGSRV_0X27_ATTCNT_MAX )
            {
                SaveInfoPtr->AttCnt++;
            }
            if( SecLevelInfoConfigPtr->AttCnt <= SaveInfoPtr->AttCnt )
            {
                *Nrc = DIAG_NRC_ENOA;
                if( SecLevelInfoConfigPtr->DelayTimer != DIAGSRV_0X27_DLYTM_NOT_SUPPORT )
                {
                    TmRet = Rte_Tm_ResetTimer1us32bit(&SaveInfoPtr->DelayTimer);
                    if( TmRet != (Std_ReturnType)E_OK )
                    {
                        DiagSrv_0x27_ReportError(DIAGSRV_0X27_API_ID_POST_GENERATE_KEY, DIAGSRV_0X27_E_CASE_TM_FAIL);
                        Ret = DIAGSRV_0X27_E_NO_RES;
                    }
                    else
                    {
                        SaveInfoPtr->DelayTimerActFlg = STD_ON;
                    }
                }
            }
            else
            {
                *Nrc = DIAG_NRC_IK;
            }
        }
        else
        {
            *Nrc = DIAG_NRC_IK;
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x27_ReportError                                   */
/* Description   | Report the error information                               */
/* Preconditions |                                                            */
/* Parameters    | [IN] ApiId   : API ID                                      */
/*               | [IN] ErrorId : Error ID                                    */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x27_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
)
{
    VAR(Rte_EcuM_ErrorType, AUTOMATIC) Error;

    Error.ModuleId = (RTE_ECUM_MODULE_DIAGSRV | DIAG_SID_SA);
    Error.ApiId = ApiId;
    Error.ErrorId = ErrorId;

    Rte_EcuM_ReportError(&Error);

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x27_SearchSecLevInfo                              */
/* Description   | Search DiagSrv_0x27_SecLevelConfig index satisfied request */
/* Preconditions |                                                            */
/* Parameters    | [IN] SecurityAccessType : request security access type     */
/* Return Value  | DiagSrv_0x27_SecLevelConfig index                          */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x27_SearchSecLevInfo
(
    VAR(uint8, AUTOMATIC) SecurityAccessType
)
{
    VAR(uint8, AUTOMATIC) Index;

    for( Index = 0U; Index < DiagSrv_0x27_SecLevelConfig.Num ; Index++ )
    {
        if( DiagSrv_0x27_SecLevelConfig.InfoPtr[Index].SecurityAccessType == SecurityAccessType )
        {
            break;
        }
    }

    return Index;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x27_CheckDelayTimer                               */
/* Description   | Check DelayTimer for requestSeed                           */
/* Preconditions |                                                            */
/* Parameters    | [INOUT] SaveInfo  : Internal processing information        */
/*               | [IN] SecLevelInfo : SecLevelInfoConfig                     */
/*               | [OUT] Nrc         : NRC                                    */
/* Return Value  | Result                                                     */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x27_CheckDelayTimer
(
    P2VAR(DiagSrv_0x27_SaveInfoType, AUTOMATIC, DIAGSRV_APPL_DATA) SaveInfo,
    P2CONST(DiagSrv_0x27_SecLevelInfoConfigType, AUTOMATIC, DIAGSRV_APPL_CONST) SecLevelInfo,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Nrc
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) TmRet;
    VAR(uint32, AUTOMATIC) TimeSpan;
    VAR(uint32, AUTOMATIC) ElapseTime;
    VAR(uint32, AUTOMATIC) DelayTimer;

    Ret = E_OK;
    *Nrc = DIAG_NRC_PR;

    if( SaveInfo->DelayTimerActFlg == (uint8)STD_ON )
    {
        TimeSpan = 0UL;
        TmRet = Rte_Tm_GetTimeSpan1us32bit(&SaveInfo->DelayTimer, &TimeSpan);
        if( TmRet != (Std_ReturnType)E_OK )
        {
            DiagSrv_0x27_ReportError(DIAGSRV_0X27_API_ID_CHECK_DELAYTIMER, DIAGSRV_0X27_E_CASE_TM_FAIL);
            Ret = DIAGSRV_0X27_E_NO_RES;
        }
        else
        {
            ElapseTime = Rte_Rpg_Div_u32(TimeSpan, DIAGSRV_0X27_USEC_TO_MSEC);
            ElapseTime = ElapseTime + (uint32)SaveInfo->ApDelayTimer;   /* no wrap around */
            DelayTimer = (uint32)SecLevelInfo->DelayTimer;
            if( DelayTimer > ElapseTime )
            {
                *Nrc = DIAG_NRC_RTDNE;
                Ret = E_NOT_OK;
            }
            else
            {
                SaveInfo->DelayTimer.StartPoint = (uint32)DIAGSRV_0X27_DLYTM_CLEAR;
                SaveInfo->DelayTimerActFlg = STD_OFF;
                SaveInfo->ApDelayTimer = DIAGSRV_0X27_DLYTM_CLEAR;
            }
        }
    }

    return Ret;
}


/******************************************************************************/
/* Function Name | DiagSrv_0x27_MakePosRsp_requestSeed                        */
/* Description   | Set Positive Response of requestSeed                       */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg      : Message                                    */
/*               | [IN] SeedInfo : Seed information                           */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x27_MakePosRsp_requestSeed
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg,
    P2CONST(Sec_SeedInfoType, AUTOMATIC, DIAGSRV_APPL_CONST) SeedInfo
)
{
    Msg->ResData[DIAGSRV_0X27_SID_POS] = DIAG_MAKE_POSRSP_SID(Msg);
    Msg->ResData[DIAGSRV_0X27_SUBFUNC_POS] = DIAG_GET_SUBFUNCTION(Msg);
    Rte_Rpg_MemCopy(&Msg->ResData[DIAG_SUBFUNCMSG_MIN_SIZE], &SeedInfo->Seed[0], (uint32)SeedInfo->SeedSize);
    Msg->ResDataLen = DIAG_SUBFUNCMSG_MIN_SIZE + SeedInfo->SeedSize;

    return;
}

#define DIAGSRV_STOP_SEC_CODE
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/06/07 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/
