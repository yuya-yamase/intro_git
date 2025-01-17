/* DiagSrv_0x31_Validate_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x31/Validate/CODE                                  */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagSrv.h>
#include <RpgLib.h>
#include <Rte.h>
#include <ReprogOpt.h>

#include "DiagSrv_0x31.h"
#include "DiagSrv_0x31_Cfg.h"
#include "DiagSrv_Local.h"
#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
#include "DiagSrv_SubMicon_Core_Cfg.h"
#endif


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Service 0x31 validateApplication Status */
#define DIAGSRV_0X31_VALID_STAT_IDLE                ((uint8)0x00U)
#define DIAGSRV_0X31_VALID_STAT_WAIT_CHK_APL        ((uint8)0x01U)
#define DIAGSRV_0X31_VALID_STAT_WAIT_GET_NEWVER     ((uint8)0x02U)
#define DIAGSRV_0X31_VALID_STAT_WAIT_READ_OLDVER    ((uint8)0x03U)
#define DIAGSRV_0X31_VALID_STAT_WAIT_WRITE_NEWVER   ((uint8)0x04U)
#define DIAGSRV_0X31_VALID_STAT_WAIT_VALID_APL      ((uint8)0x05U)

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
#define DIAGSRV_0X31_VALID_STAT_SUBM_REQ            ((uint8)0x06U)
#define DIAGSRV_0X31_VALID_STAT_SUBM_WAIT           ((uint8)0x07U)

#define DIAGSRV_0X31_VALID_SUBM_REQDATA_SIZE        (DIAG_RIDMSG_MIN_SIZE)
#define DIAGSRV_0X31_VALID_SUBM_RSPDATA_SIZE        (DIAGSRV_0X31_RESPLEN_VALID)

#define DIAGSRV_0X31_VALID_SUBM_GET_MICONID(index)  (DiagSrv_SubMRewriteConfig.AreaPtr[(index)].MiconId)
#endif


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_ClearInfo (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_Time_UsrCheck (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_Time_GetNewVer (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_Time_ReadOldVer (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_Time_WriteNewVer (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_Time_ValidApl (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_CheckValidateResult (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_GetNewVer (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_WriteNewVer (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_EndProcess
(
    VAR(uint8, AUTOMATIC) Nrc
);

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_SubM_Time_Req (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_SubM_Time_Wait (void);
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_SubM_CheckRsp (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_SubM_ValidateContinue (void);
#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Valid_JobStatus;
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Valid_Usr_ValidateResult;
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Valid_NewVer[DIAGSRV_0X31_VERSIONINFO_MAX_SIZE];
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Valid_OldVer[DIAGSRV_0X31_VERSIONINFO_MAX_SIZE];

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Valid_SubM_Index;
static VAR(Rte_SubMiconIf_ReqInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Valid_SubM_ReqInfo;
static VAR(Rte_SubMiconIf_RespInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Valid_SubM_RspInfo;
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Valid_SubM_ValidateResult;
#endif

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
/* Function Name | DiagSrv_0x31_Valid_Init                                    */
/* Description   | Initialize                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_Init (void)
{
    DiagSrv_0x31_Valid_ClearInfo();

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Valid_Time                                    */
/* Description   | Time function                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_Time (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_RCRRP;

    if( DiagSrv_0x31_Valid_JobStatus != DIAGSRV_0X31_VALID_STAT_IDLE )
    {
        Nrc = DIAG_NRC_GPF;

        if( DiagSrv_0x31_Valid_JobStatus == DIAGSRV_0X31_VALID_STAT_WAIT_CHK_APL )
        {
            Nrc = DiagSrv_0x31_Valid_Time_UsrCheck();
        }
        else if( DiagSrv_0x31_Valid_JobStatus == DIAGSRV_0X31_VALID_STAT_WAIT_GET_NEWVER )
        {
            Nrc = DiagSrv_0x31_Valid_Time_GetNewVer();
        }
        else if( DiagSrv_0x31_Valid_JobStatus == DIAGSRV_0X31_VALID_STAT_WAIT_READ_OLDVER )
        {
            Nrc = DiagSrv_0x31_Valid_Time_ReadOldVer();
        }
        else if( DiagSrv_0x31_Valid_JobStatus == DIAGSRV_0X31_VALID_STAT_WAIT_WRITE_NEWVER )
        {
            Nrc = DiagSrv_0x31_Valid_Time_WriteNewVer();
        }
        else if( DiagSrv_0x31_Valid_JobStatus == DIAGSRV_0X31_VALID_STAT_WAIT_VALID_APL )
        {
            Nrc = DiagSrv_0x31_Valid_Time_ValidApl();
        }
#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
        else if( DiagSrv_0x31_Valid_JobStatus == DIAGSRV_0X31_VALID_STAT_SUBM_REQ )
        {
            Nrc = DiagSrv_0x31_Valid_SubM_Time_Req();
        }
        else if( DiagSrv_0x31_Valid_JobStatus == DIAGSRV_0X31_VALID_STAT_SUBM_WAIT )
        {
            Nrc = DiagSrv_0x31_Valid_SubM_Time_Wait();
        }
#endif
        else
        {
            /* No process */
        }

        DiagSrv_0x31_Valid_EndProcess(Nrc);
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Valid_Processing                              */
/* Description   | Processing function                                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_Processing (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) RewriteStatus;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DiagSrv_0x31_MsgCheckCondition();
    if( Nrc == DIAG_NRC_RCRRP )
    {
        RewriteStatus = DiagSrv_GetRewriteStatus();
        if( RewriteStatus == DIAGSRV_REWRITESTAT_VALIDATE )
        {
            DiagSrv_0x31_Valid_Usr_ValidateResult = DIAGSRV_0X31_USR_ALREADY_VALID;

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
            DiagSrv_0x31_Valid_SubM_Index = DiagSrv_SubMRewriteConfig.MiconNum - (uint8)1U;
            DiagSrv_0x31_Valid_SubM_ValidateResult = DIAGSRV_0X31_APLSTATUS_PRESENT;

            DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_SUBM_REQ;
            Nrc = DIAG_NRC_RCRRP;
#else
            DiagSrv_0x31_ApplicationStatusValue = DIAGSRV_0X31_APLSTATUS_PRESENT;
            DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_IDLE;
            Nrc = DIAG_NRC_PR;
#endif
        }
        else
        {
            Ret = DiagSrv_0x31_Usr_ReqCheckValidateApl(&DiagSrv_0x31_Valid_Usr_ValidateResult);
            if( Ret == (Std_ReturnType)E_OK )
            {
                DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_WAIT_CHK_APL;
            }
            else
            {
                Nrc = DIAG_NRC_GPF;
            }
        }
    }

    DiagSrv_0x31_Valid_EndProcess(Nrc);

    return Nrc;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Valid_ClearInfo                               */
/* Description   | Clear information                                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_ClearInfo (void)
{
    DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_IDLE;
    DiagSrv_0x31_Valid_Usr_ValidateResult = DIAGSRV_0X31_USR_VALID_NG;

    Rte_Rpg_MemSet(DiagSrv_0x31_Valid_NewVer, 0U, sizeof(DiagSrv_0x31_Valid_NewVer));
    Rte_Rpg_MemSet(DiagSrv_0x31_Valid_OldVer, 0U, sizeof(DiagSrv_0x31_Valid_OldVer));

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
    DiagSrv_0x31_Valid_SubM_Index = 0U;
    DiagSrv_0x31_Valid_SubM_ReqInfo.ReqData = NULL_PTR;
    DiagSrv_0x31_Valid_SubM_ReqInfo.ReqDataSize = 0U;
    DiagSrv_0x31_Valid_SubM_RspInfo.RespData = NULL_PTR;
    DiagSrv_0x31_Valid_SubM_RspInfo.RespDataSize = 0U;
    DiagSrv_0x31_Valid_SubM_ValidateResult = DIAGSRV_0X31_APLSTATUS_NOT_PRESENT;
#endif

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Valid_Time_UsrCheck                           */
/* Description   | Time of DIAGSRV_0X31_VALID_STAT_WAIT_CHK_APL               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_Time_UsrCheck (void)
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
#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
            DiagSrv_0x31_Valid_SubM_Index = DiagSrv_SubMRewriteConfig.MiconNum - (uint8)1U;
            DiagSrv_0x31_Valid_SubM_ValidateResult = DIAGSRV_0X31_APLSTATUS_PRESENT;

            DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_SUBM_REQ;
            Nrc = DIAG_NRC_RCRRP;
#else
            Nrc = DiagSrv_0x31_Valid_CheckValidateResult();
#endif
        }
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
/* Function Name | DiagSrv_0x31_Valid_Time_GetNewVer                          */
/* Description   | Time of DIAGSRV_0X31_VALID_STAT_WAIT_GET_NEWVER            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_Time_GetNewVer (void)
{
    VAR(uint32, AUTOMATIC) OldVerAddr;
    VAR(uint8, AUTOMATIC) OldVerSize;
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DIAG_NRC_GPF;

    Status = DiagSrv_0x31_Usr_GetStatus();
    if( Status == DIAGSRV_0X31_USR_IDLE )
    {
        JobResult = DiagSrv_0x31_Usr_GetJobResult();
        if( JobResult == DIAGSRV_0X31_USR_JOB_OK )
        {
            OldVerAddr = 0UL;
            OldVerSize = 0U;
            DiagSrv_GetTempVersionAreaInfo(&OldVerAddr, &OldVerSize);

            Ret = RpgLib_ReqMemRead(RPGLIB_MEMORYID_0,
                                    DiagSrv_0x31_Valid_OldVer,
                                    OldVerAddr,
                                    (uint32)OldVerSize);
            if( Ret == (Std_ReturnType)E_OK )
            {
                DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_WAIT_READ_OLDVER;
                Nrc = DIAG_NRC_RCRRP;
            }
        }
        else
        {
            DiagSrv_0x31_ApplicationStatusValue = DIAGSRV_0X31_APLSTATUS_NOT_PRESENT;
            DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_IDLE;
            Nrc = DIAG_NRC_PR;
        }
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
/* Function Name | DiagSrv_0x31_Valid_Time_ReadOldVer                         */
/* Description   | Time of DIAGSRV_0X31_VALID_STAT_WAIT_READ_OLDVER           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_Time_ReadOldVer (void)
{
    VAR(uint32, AUTOMATIC) VerAddr;
    VAR(uint32, AUTOMATIC) OldVerAddr;
    VAR(uint8, AUTOMATIC) VerSize;
    VAR(uint8, AUTOMATIC) OldVerSize;
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) OldVerPtr;

    Nrc = DIAG_NRC_GPF;

    Status = RpgLib_GetStatus();
    if( Status == RPGLIB_IDLE )
    {
        OldVerPtr = NULL_PTR;

        JobResult = RpgLib_GetJobResult();
        if( JobResult == RPGLIB_JOB_OK )
        {
            OldVerAddr = 0UL;
            OldVerSize = 0U;
            DiagSrv_GetTempVersionAreaInfo(&OldVerAddr, &OldVerSize);

            Ret = DiagSrv_0x31_CheckVersionData(DiagSrv_0x31_Valid_OldVer,
                                                OldVerSize);
            if( Ret == (Std_ReturnType)E_OK )
            {
                OldVerPtr = DiagSrv_0x31_Valid_OldVer;
            }
        }

        VerAddr = 0UL;
        VerSize = 0U;
        DiagSrv_GetVersionAreaInfo(&VerAddr, &VerSize);

        Ret = DiagSrv_0x31_Usr_CompareAplVersion(OldVerPtr, DiagSrv_0x31_Valid_NewVer, VerSize);
        if( Ret == (Std_ReturnType)E_OK )
        {
            /* OldVer <= NewVer */
            Nrc = DiagSrv_0x31_Valid_WriteNewVer();
        }
        else
        {
            /* OldVer > NewVer */
            DiagSrv_0x31_ApplicationStatusValue = DIAGSRV_0X31_APLSTATUS_NOT_PRESENT;
            DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_IDLE;
            Nrc = DIAG_NRC_PR;
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
/* Function Name | DiagSrv_0x31_Valid_Time_WriteNewVer                        */
/* Description   | Time of DIAGSRV_0X31_VALID_STAT_WAIT_WRITE_NEWVER          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_Time_WriteNewVer (void)
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
                Ret = RpgLib_ReqValidApl();
                if( Ret == (Std_ReturnType)E_OK )
                {
                    DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_WAIT_VALID_APL;
                    Nrc = DIAG_NRC_RCRRP;
                }
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
/* Function Name | DiagSrv_0x31_Valid_Time_ValidApl                           */
/* Description   | Time of DIAGSRV_0X31_VALID_STAT_WAIT_VALID_APL             */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_Time_ValidApl (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;

    Nrc = DIAG_NRC_GPF;

    Status = RpgLib_GetStatus();
    if( Status == RPGLIB_IDLE )
    {
        JobResult = RpgLib_GetJobResult();
        if( JobResult == RPGLIB_JOB_OK )
        {
            DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_VALIDATE);

            DiagSrv_0x31_ApplicationStatusValue = DIAGSRV_0X31_APLSTATUS_PRESENT;
            DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_IDLE;
            Nrc = DIAG_NRC_PR;
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
/* Function Name | DiagSrv_0x31_Valid_CheckValidateResult                     */
/* Description   | Check validate result                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_CheckValidateResult (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) RewriteStatus;

    Nrc = DIAG_NRC_GPF;

    if( DiagSrv_0x31_Valid_Usr_ValidateResult == DIAGSRV_0X31_USR_VALID_OK )
    {
        RewriteStatus = DiagSrv_GetRewriteStatus();
        if( RewriteStatus == DIAGSRV_REWRITESTAT_DATA_CHECK )
        {
            /* MainMicon == Valid OK */
            Nrc = DiagSrv_0x31_Valid_GetNewVer();
        }
        else
        {
            DiagSrv_0x31_ApplicationStatusValue = DIAGSRV_0X31_APLSTATUS_NOT_PRESENT;
            DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_IDLE;
            Nrc = DIAG_NRC_PR;
        }
    }
    else if( DiagSrv_0x31_Valid_Usr_ValidateResult == DIAGSRV_0X31_USR_VALID_NG )
    {
        /* MainMicon == Valid NG */
        DiagSrv_0x31_ApplicationStatusValue = DIAGSRV_0X31_APLSTATUS_NOT_PRESENT;
        DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_IDLE;
        Nrc = DIAG_NRC_PR;
    }
    else if( DiagSrv_0x31_Valid_Usr_ValidateResult == DIAGSRV_0X31_USR_ALREADY_VALID )
    {
        /* MainMicon == APL exist */
        DiagSrv_0x31_ApplicationStatusValue = DIAGSRV_0X31_APLSTATUS_PRESENT;
        DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_IDLE;
        Nrc = DIAG_NRC_PR;
    }
    else
    {
        /* No process */
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Valid_GetNewVer                               */
/* Description   | Gets new application version information                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_GetNewVer (void)
{
    VAR(uint32, AUTOMATIC) VerAddr;
    VAR(uint8, AUTOMATIC) VerSize;
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DIAG_NRC_GPF;

    VerAddr = 0UL;
    VerSize = 0U;
    DiagSrv_GetVersionAreaInfo(&VerAddr, &VerSize);

    Ret = DiagSrv_0x31_Usr_ReqGetAplVersion(DiagSrv_0x31_Valid_NewVer, VerSize);
    if( Ret == (Std_ReturnType)E_OK )
    {
        DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_WAIT_GET_NEWVER;
        Nrc = DIAG_NRC_RCRRP;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Valid_WriteNewVer                             */
/* Description   | Writes new application version information                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_WriteNewVer (void)
{
    VAR(uint32, AUTOMATIC) VerAddr;
    VAR(uint8, AUTOMATIC) VerSize;
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DIAG_NRC_GPF;

    VerAddr = 0UL;
    VerSize = 0U;
    DiagSrv_GetVersionAreaInfo(&VerAddr, &VerSize);

    Ret = RpgLib_WriteMemStart(RPGLIB_MEMORYID_0,
                                VerAddr,
                                (uint32)VerSize);
    if( Ret == (Std_ReturnType)E_OK )
    {
        Ret = RpgLib_ReqWriteMemUpdate(DiagSrv_0x31_Valid_NewVer,
                                    (uint32)VerSize);
        if( Ret == (Std_ReturnType)E_OK )
        {
            DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_WAIT_WRITE_NEWVER;
            Nrc = DIAG_NRC_RCRRP;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Valid_EndProcess                              */
/* Description   | End processing                                             */
/* Preconditions |                                                            */
/* Parameters    | [IN] Nrc : NRC                                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_EndProcess
(
    VAR(uint8, AUTOMATIC) Nrc
)
{
    P2CONST(DiagSrv_RewriteAreaStatusType, AUTOMATIC, DIAGSRV_APPL_CONST) RewriteAreaStatus;

    if( Nrc != DIAG_NRC_RCRRP )
    {
        if( Nrc == DIAG_NRC_PR )
        {
            if( (DiagSrv_0x31_ApplicationStatusValue == DIAGSRV_0X31_APLSTATUS_NOT_PRESENT) &&
                (ReprogOpt_DoubleMapConfig == (uint8)REPROGOPT_DOUBLEMAP_REWRITE_INVALID) )
            {
                RewriteAreaStatus = DiagSrv_GetRewriteAreaStatusInfo();
                if( (RewriteAreaStatus->BootInfoPtr->ExtendedBootMode == DIAGSRV_EXT_BOOT_MODE_APL) ||
                    (RewriteAreaStatus->BootInfoPtr->ExtendedBootMode == DIAGSRV_EXT_BOOT_MODE_STAYINBOOT) )
                {
                    /* APL exists for DoubleMap */
                    DiagSrv_0x31_ApplicationStatusValue = DIAGSRV_0X31_APLSTATUS_PRESENT;
                }
            }

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
            if( (DiagSrv_0x31_ApplicationStatusValue == DIAGSRV_0X31_APLSTATUS_PRESENT) &&
                (DiagSrv_0x31_Valid_SubM_ValidateResult != DIAGSRV_0X31_APLSTATUS_PRESENT) )
            {
                /* APL exists in MainMicon, but does not exist in SubMicon */
                DiagSrv_0x31_ApplicationStatusValue = DIAGSRV_0X31_APLSTATUS_NOT_PRESENT;
            }
#endif
        }
        else
        {
            DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_IDLE;
        }

        DiagSrv_0x31_Valid_ClearInfo();
    }

    return;
}

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
/******************************************************************************/
/* Function Name | DiagSrv_0x31_Valid_SubM_Time_Req                           */
/* Description   | Time of DIAGSRV_0X31_VALID_STAT_SUBM_REQ                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_MAIN   */
/*               | is defined.                                                */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_SubM_Time_Req (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) MiconId;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DIAG_NRC_GPF;

    MiconId = DIAGSRV_0X31_VALID_SUBM_GET_MICONID(DiagSrv_0x31_Valid_SubM_Index);

    DiagSrv_0x31_Valid_SubM_ReqInfo.ReqData      = &DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_SID_POS];
    DiagSrv_0x31_Valid_SubM_ReqInfo.ReqDataSize  = DIAGSRV_0X31_VALID_SUBM_REQDATA_SIZE;
    DiagSrv_0x31_Valid_SubM_RspInfo.RespData     = &DiagSrv_0x31_Msg->ResData[DIAGSRV_0X31_SID_POS];
    DiagSrv_0x31_Valid_SubM_RspInfo.RespDataSize = DIAGSRV_0X31_VALID_SUBM_RSPDATA_SIZE;

    Ret = Rte_SubMiconIf_Main_RequestService(MiconId,
                                            &DiagSrv_0x31_Valid_SubM_ReqInfo,
                                            &DiagSrv_0x31_Valid_SubM_RspInfo,
                                            RTE_SUBMICONIF_INITIAL);
    if( Ret == RTE_SUBMICONIF_E_PENDING )
    {
        DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_SUBM_WAIT;
        Nrc = DIAG_NRC_RCRRP;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Valid_SubM_Time_Wait                          */
/* Description   | Time of DIAGSRV_0X31_VALID_STAT_SUBM_WAIT                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_MAIN   */
/*               | is defined.                                                */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_SubM_Time_Wait (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) MiconId;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DIAG_NRC_GPF;

    MiconId = DIAGSRV_0X31_VALID_SUBM_GET_MICONID(DiagSrv_0x31_Valid_SubM_Index);

    Ret = Rte_SubMiconIf_Main_RequestService(MiconId,
                                            &DiagSrv_0x31_Valid_SubM_ReqInfo,
                                            &DiagSrv_0x31_Valid_SubM_RspInfo,
                                            RTE_SUBMICONIF_PENDING);
    if( Ret == (Std_ReturnType)E_OK )
    {
        Ret = DiagSrv_0x31_Valid_SubM_CheckRsp();
        if( Ret == (Std_ReturnType)E_OK )
        {
            Nrc = DiagSrv_0x31_Valid_SubM_ValidateContinue();
        }
    }
    else if( Ret == RTE_SUBMICONIF_E_PENDING )
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
/* Function Name | DiagSrv_0x31_Valid_SubM_CheckRsp                           */
/* Description   | Response information check                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_MAIN   */
/*               | is defined.                                                */
/******************************************************************************/
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_SubM_CheckRsp (void)
{
    VAR(uint16, AUTOMATIC) RspRid;
    VAR(uint8, AUTOMATIC) CheckRspSID;
    VAR(uint8, AUTOMATIC) CheckRspSubfunc;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    if( DiagSrv_0x31_Valid_SubM_RspInfo.RespDataSize == DIAGSRV_0X31_VALID_SUBM_RSPDATA_SIZE )
    {
        CheckRspSID = DIAG_MAKE_POSRSP_SID(DiagSrv_0x31_Msg);
        if( DiagSrv_0x31_Valid_SubM_RspInfo.RespData[DIAGSRV_0X31_SID_POS] == CheckRspSID )
        {
            CheckRspSubfunc = DIAG_GET_SUBFUNCTION(DiagSrv_0x31_Msg);
            if( DiagSrv_0x31_Valid_SubM_RspInfo.RespData[DIAGSRV_0X31_SUBFUNC_POS] == CheckRspSubfunc )
            {
                RspRid = (uint16)Rte_Rpg_ByteCombine(&DiagSrv_0x31_Valid_SubM_RspInfo.RespData[DIAGSRV_0X31_RID_H_POS],
                                                    sizeof(RspRid));
                if( RspRid == DIAGSRV_0X31_RID_VALIDATE )
                {
                    if( DiagSrv_0x31_Valid_SubM_RspInfo.RespData[DIAGSRV_0X31_ROUTINEINFO_POS] == DIAGSRV_0X31_ROUTINEINFO_VALUE )
                    {
                        if( DiagSrv_0x31_Valid_SubM_RspInfo.RespData[DIAGSRV_0X31_APLSTATUS_POS] != DIAGSRV_0X31_APLSTATUS_PRESENT )
                        {
                            DiagSrv_0x31_Valid_SubM_ValidateResult = DIAGSRV_0X31_APLSTATUS_NOT_PRESENT;
                        }

                        Ret = E_OK;
                    }
                }
            }
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Valid_SubM_ValidateContinue                   */
/* Description   | continue Sub-microcontroller validateApplication           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_MAIN   */
/*               | is defined.                                                */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Valid_SubM_ValidateContinue (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) NextMiconId;

    Nrc = DIAG_NRC_GPF;

    if( DiagSrv_0x31_Valid_SubM_Index > (uint8)0U )
    {
        DiagSrv_0x31_Valid_SubM_Index--;

        NextMiconId = DIAGSRV_0X31_VALID_SUBM_GET_MICONID(DiagSrv_0x31_Valid_SubM_Index);
        if( NextMiconId == DIAGSRV_SUBM_ID_MAIN )
        {
            Nrc = DiagSrv_0x31_Valid_CheckValidateResult();
        }
        else
        {
            DiagSrv_0x31_Valid_JobStatus = DIAGSRV_0X31_VALID_STAT_SUBM_REQ;
            Nrc = DIAG_NRC_RCRRP;
        }
    }

    return Nrc;
}

#endif


#define DIAGSRV_STOP_SEC_CODE
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2023/01/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/
