/* DiagSrv_0x31_Erase_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x31/Erase/CODE                                     */
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


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Service 0x31 Status */
#define DIAGSRV_0X31_ERASE_STAT_IDLE                ((uint8)0x00U)
#define DIAGSRV_0X31_ERASE_STAT_WAIT_HOOK_PRE_ERASE ((uint8)0x01U)
#define DIAGSRV_0X31_ERASE_STAT_WAIT_READ_VER       ((uint8)0x02U)
#define DIAGSRV_0X31_ERASE_STAT_WAIT_ERASE_TEMPVER  ((uint8)0x03U)
#define DIAGSRV_0X31_ERASE_STAT_WAIT_WRITE_TEMPVER  ((uint8)0x04U)
#define DIAGSRV_0X31_ERASE_STAT_WAIT_INVALID_APL    ((uint8)0x05U)
#define DIAGSRV_0X31_ERASE_STAT_WAIT_ERASE_MEM      ((uint8)0x06U)

/* eraseMemory addressAndLengthFormatIdentifier Parameter */
#define DIAGSRV_0X31_ERASE_ALFID_VALUE              ((uint8)0x44U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint32 EndAddr;
    uint32 CurrentBlockTopAddr;
    uint32 CurrentBlockSize;
} DiagSrv_0x31_Erase_AreaInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_ClearInfo (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_Time_PreErase (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_Time_ReadVerInfo (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_Time_EraseTmpVer (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_Time_WriteTmpVer (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_Time_EraseMemory (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_CheckCondition (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_InvalidApl (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_EraseMemory (void);
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_EraseBlock
(
    VAR(uint32, AUTOMATIC) EraseAddr
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_EndProcess
(
    VAR(uint8, AUTOMATIC) Nrc
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Erase_JobStatus;
static VAR(DiagSrv_0x31_Erase_AreaInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Erase_AreaInfo;
static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Erase_VerInfo[DIAGSRV_0X31_VERSIONINFO_MAX_SIZE];

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
/* Function Name | DiagSrv_0x31_Erase_Init                                    */
/* Description   | Initialize                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_Init (void)
{
    DiagSrv_0x31_Erase_ClearInfo();

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Erase_Time                                    */
/* Description   | Time function                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_Time (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_RCRRP;

    if( DiagSrv_0x31_Erase_JobStatus != DIAGSRV_0X31_ERASE_STAT_IDLE )
    {
        Nrc = DIAG_NRC_GPF;

        if( DiagSrv_0x31_Erase_JobStatus == DIAGSRV_0X31_ERASE_STAT_WAIT_HOOK_PRE_ERASE )
        {
            Nrc = DiagSrv_0x31_Erase_Time_PreErase();
        }
        else if( DiagSrv_0x31_Erase_JobStatus == DIAGSRV_0X31_ERASE_STAT_WAIT_READ_VER )
        {
            Nrc = DiagSrv_0x31_Erase_Time_ReadVerInfo();
        }
        else if( DiagSrv_0x31_Erase_JobStatus == DIAGSRV_0X31_ERASE_STAT_WAIT_ERASE_TEMPVER )
        {
            Nrc = DiagSrv_0x31_Erase_Time_EraseTmpVer();
        }
        else if( DiagSrv_0x31_Erase_JobStatus == DIAGSRV_0X31_ERASE_STAT_WAIT_WRITE_TEMPVER )
        {
            Nrc = DiagSrv_0x31_Erase_Time_WriteTmpVer();
        }
        else if( (DiagSrv_0x31_Erase_JobStatus == DIAGSRV_0X31_ERASE_STAT_WAIT_INVALID_APL) ||
                (DiagSrv_0x31_Erase_JobStatus == DIAGSRV_0X31_ERASE_STAT_WAIT_ERASE_MEM) )
        {
            Nrc = DiagSrv_0x31_Erase_Time_EraseMemory();
        }
        else
        {
            /* No process */
        }

        DiagSrv_0x31_Erase_EndProcess(Nrc);
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Erase_Processing                              */
/* Description   | Processing function                                        */
/* Preconditions |                                                            */
/* Notes         | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_CNC                                              */
/*               |  DIAG_NRC_ROOR                                             */
/*               |  DIAG_NRC_GPF                                              */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_Processing (void)
{
    VAR(uint32, AUTOMATIC) EraseAddr;
    VAR(uint32, AUTOMATIC) EraseSize;
    VAR(uint8, AUTOMATIC) RewriteAreaNum;
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DiagSrv_0x31_Erase_CheckCondition();
    if( Nrc == DIAG_NRC_RCRRP )
    {
        if( DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_ERASE_ALFID_POS] != DIAGSRV_0X31_ERASE_ALFID_VALUE )
        {
            Nrc = DIAG_NRC_ROOR;
        }
    }

    if( Nrc == DIAG_NRC_RCRRP )
    {
        RewriteAreaNum = DiagSrv_GetRewriteAreaNumber();
        if( RewriteAreaNum == DIAGSRV_REWRITEAREA_INVALID )
        {
            Nrc = DIAG_NRC_GPF;
        }
    }

    if( Nrc == DIAG_NRC_RCRRP )
    {
        EraseAddr = Rte_Rpg_ByteCombine(&DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_ERASE_ADDR_POS],
                                        sizeof(EraseAddr));
        EraseSize = Rte_Rpg_ByteCombine(&DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_ERASE_SIZE_POS],
                                        sizeof(EraseSize));

        Ret = DiagSrv_CheckRewriteArea(RewriteAreaNum, EraseAddr, EraseSize);
        if( Ret != (Std_ReturnType)E_OK )
        {
            Nrc = DIAG_NRC_ROOR;
        }
    }

    if( Nrc == DIAG_NRC_RCRRP )
    {
        Nrc = DiagSrv_0x31_MsgCheckCondition();
    }

    if( Nrc == DIAG_NRC_RCRRP )
    {
        Nrc = DIAG_NRC_GPF;

        Ret = DiagSrv_0x31_Usr_ReqPreErase(RewriteAreaNum);
        if( Ret == (Std_ReturnType)E_OK )
        {
            DiagSrv_0x31_Erase_JobStatus = DIAGSRV_0X31_ERASE_STAT_WAIT_HOOK_PRE_ERASE;
            Nrc = DIAG_NRC_RCRRP;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Erase_ClearInfo                               */
/* Description   | Clear information                                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_ClearInfo (void)
{
    DiagSrv_0x31_Erase_JobStatus = DIAGSRV_0X31_ERASE_STAT_IDLE;

    DiagSrv_0x31_Erase_AreaInfo.EndAddr = 0UL;
    DiagSrv_0x31_Erase_AreaInfo.CurrentBlockTopAddr = 0UL;
    DiagSrv_0x31_Erase_AreaInfo.CurrentBlockSize = 0UL;

    Rte_Rpg_MemSet(DiagSrv_0x31_Erase_VerInfo, 0U, sizeof(DiagSrv_0x31_Erase_VerInfo));

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Erase_Time_PreErase                           */
/* Description   | Time of DIAGSRV_0X31_ERASE_STAT_WAIT_HOOK_PRE_ERASE        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_Time_PreErase (void)
{
    VAR(uint32, AUTOMATIC) MemoryId;
    VAR(uint32, AUTOMATIC) VerAddr;
    VAR(uint8, AUTOMATIC) VerSize;
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
            MemoryId = RPGLIB_MEMORYID_0;
            if( ReprogOpt_DoubleMapConfig == (uint8)REPROGOPT_DOUBLEMAP_REWRITE_INVALID )
            {
                MemoryId = RPGLIB_MEMORYID_1;   /* Valid area */
            }

            VerAddr = 0UL;
            VerSize = 0U;
            DiagSrv_GetVersionAreaInfo(&VerAddr, &VerSize);

            Ret = RpgLib_ReqMemRead(MemoryId,
                                    DiagSrv_0x31_Erase_VerInfo,
                                    VerAddr,
                                    (uint32)VerSize);
            if( Ret == (Std_ReturnType)E_OK )
            {
                DiagSrv_0x31_Erase_JobStatus = DIAGSRV_0X31_ERASE_STAT_WAIT_READ_VER;
                Nrc = DIAG_NRC_RCRRP;
            }
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
/* Function Name | DiagSrv_0x31_Erase_Time_ReadVerInfo                        */
/* Description   | Time of DIAGSRV_0X31_ERASE_STAT_WAIT_READ_VER              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_Time_ReadVerInfo (void)
{
    VAR(RpgLib_MemBlockInfoType, AUTOMATIC) BlockInfo;
    VAR(uint32, AUTOMATIC) VerAddr;
    VAR(uint32, AUTOMATIC) TempVerAddr;
    VAR(uint8, AUTOMATIC) VerSize;
    VAR(uint8, AUTOMATIC) TempVerSize;
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DIAG_NRC_GPF;

    Status = RpgLib_GetStatus();
    if( Status == RPGLIB_IDLE )
    {
        JobResult = RpgLib_GetJobResult();
        if( JobResult == RPGLIB_JOB_OK )
        {
            VerAddr = 0UL;
            VerSize = 0U;
            DiagSrv_GetVersionAreaInfo(&VerAddr, &VerSize);

            Ret = DiagSrv_0x31_CheckVersionData(DiagSrv_0x31_Erase_VerInfo,
                                                VerSize);
            if( Ret == (Std_ReturnType)E_OK )
            {
                TempVerAddr = 0UL;
                TempVerSize = 0U;
                DiagSrv_GetTempVersionAreaInfo(&TempVerAddr, &TempVerSize);

                BlockInfo.BlockTopAddr = 0UL;
                BlockInfo.BlockSize = 0UL;

                Ret = RpgLib_GetMemBlockInfo(RPGLIB_MEMORYID_0,
                                            TempVerAddr,
                                            &BlockInfo);
                if( Ret == (Std_ReturnType)E_OK )
                {
                    Ret = RpgLib_ReqMemBlockErase(RPGLIB_MEMORYID_0, &BlockInfo);
                    if( Ret == (Std_ReturnType)E_OK )
                    {
                        DiagSrv_0x31_Erase_JobStatus = DIAGSRV_0X31_ERASE_STAT_WAIT_ERASE_TEMPVER;
                        Nrc = DIAG_NRC_RCRRP;
                    }
                }
            }
            else
            {
                /* If version information area read fails,           */
                /* temporary version information area is not updated */
                /* and processing continues.                         */
                Nrc = DiagSrv_0x31_Erase_InvalidApl();
            }
        }
        else
        {
            /* If version information area read fails,           */
            /* temporary version information area is not updated */
            /* and processing continues.                         */
            Nrc = DiagSrv_0x31_Erase_InvalidApl();
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
/* Function Name | DiagSrv_0x31_Erase_Time_EraseTmpVer                        */
/* Description   | Time of DIAGSRV_0X31_ERASE_STAT_WAIT_ERASE_TEMPVER         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_Time_EraseTmpVer (void)
{
    VAR(uint32, AUTOMATIC) TempVerAddr;
    VAR(uint8, AUTOMATIC) TempVerSize;
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DIAG_NRC_GPF;

    Status = RpgLib_GetStatus();
    if( Status == RPGLIB_IDLE )
    {
        JobResult = RpgLib_GetJobResult();
        if( JobResult == RPGLIB_JOB_OK )
        {
            TempVerAddr = 0UL;
            TempVerSize = 0U;
            DiagSrv_GetTempVersionAreaInfo(&TempVerAddr, &TempVerSize);

            Ret = RpgLib_WriteMemStart(RPGLIB_MEMORYID_0,
                                        TempVerAddr,
                                        (uint32)TempVerSize);
            if( Ret == (Std_ReturnType)E_OK )
            {
                Ret = RpgLib_ReqWriteMemUpdate(DiagSrv_0x31_Erase_VerInfo,
                                                (uint32)TempVerSize);
                if( Ret == (Std_ReturnType)E_OK )
                {
                    DiagSrv_0x31_Erase_JobStatus = DIAGSRV_0X31_ERASE_STAT_WAIT_WRITE_TEMPVER;
                    Nrc = DIAG_NRC_RCRRP;
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
/* Function Name | DiagSrv_0x31_Erase_Time_WriteTmpVer                        */
/* Description   | Time of DIAGSRV_0X31_ERASE_STAT_WAIT_WRITE_TEMPVER         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_Time_WriteTmpVer (void)
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
                Nrc = DiagSrv_0x31_Erase_InvalidApl();
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
/* Function Name | DiagSrv_0x31_Erase_Time_EraseMemory                        */
/* Description   | The following time                                         */
/*               |  - DIAGSRV_0X31_ERASE_STAT_WAIT_INVALID_APL                */
/*               |  - DIAGSRV_0X31_ERASE_STAT_WAIT_ERASE_MEM                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_Time_EraseMemory (void)
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
            Nrc = DiagSrv_0x31_Erase_EraseMemory();
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
/* Function Name | DiagSrv_0x31_Erase_CheckCondition                          */
/* Description   | Check condition error and resend request                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_CNC                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_CheckCondition (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) RewriteStatus;

    Nrc = DIAG_NRC_CNC;

    RewriteStatus = DiagSrv_GetRewriteStatus();
    if( RewriteStatus == DIAGSRV_REWRITESTAT_SBL_DL_CHECK )
    {
        Nrc = DIAG_NRC_RCRRP;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Erase_InvalidApl                              */
/* Description   | Invalid application                                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_InvalidApl (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) RewriteAreaNum;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DIAG_NRC_GPF;

    RewriteAreaNum = DiagSrv_GetRewriteAreaNumber();
    if( RewriteAreaNum != DIAGSRV_REWRITEAREA_INVALID )
    {
        Ret = RpgLib_ReqInvalidApl(RPGLIB_MEMORYID_0);
        if( Ret == (Std_ReturnType)E_OK )
        {
            DiagSrv_SetRewriteAreaStatus(RewriteAreaNum, DIAGSRV_LBSTAT_IN_REWRITING);

            DiagSrv_0x31_Erase_JobStatus = DIAGSRV_0X31_ERASE_STAT_WAIT_INVALID_APL;
            Nrc = DIAG_NRC_RCRRP;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Erase_EraseMemory                             */
/* Description   | Erase memory                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_EraseMemory (void)
{
    VAR(uint32, AUTOMATIC) EraseAddr;
    VAR(uint32, AUTOMATIC) EraseSize;
    VAR(uint32, AUTOMATIC) EraseEndNextAddr;
    VAR(uint8, AUTOMATIC) RewriteAreaNum;
    VAR(uint8, AUTOMATIC) ExecEraseFlag;
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Nrc = DIAG_NRC_GPF;
    ExecEraseFlag = STD_OFF;

    if( DiagSrv_0x31_Erase_JobStatus == DIAGSRV_0X31_ERASE_STAT_WAIT_INVALID_APL )
    {
        RewriteAreaNum = DiagSrv_GetRewriteAreaNumber();
        if( RewriteAreaNum != DIAGSRV_REWRITEAREA_INVALID )
        {
            EraseAddr = 0UL;
            EraseSize = 0UL;
            DiagSrv_GetRewriteAreaInfo(RewriteAreaNum, &EraseAddr, &EraseSize);

            EraseEndNextAddr = EraseAddr + EraseSize;   /* no wrap around */
            if( EraseEndNextAddr > 0UL )
            {
                DiagSrv_0x31_Erase_AreaInfo.EndAddr = EraseEndNextAddr - 1UL;

                ExecEraseFlag = STD_ON;
            }
        }
    }
    else    /* DIAGSRV_0X31_ERASE_STAT_WAIT_ERASE_MEM */
    {
        EraseAddr = DiagSrv_0x31_Erase_AreaInfo.CurrentBlockTopAddr + DiagSrv_0x31_Erase_AreaInfo.CurrentBlockSize; /* no wrap around */
        if( EraseAddr > DiagSrv_0x31_Erase_AreaInfo.EndAddr )
        {
            /* End erase memory */
            DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_ERASE);

            DiagSrv_0x31_Erase_JobStatus = DIAGSRV_0X31_ERASE_STAT_IDLE;
            Nrc = DIAG_NRC_PR;
        }
        else
        {
            ExecEraseFlag = STD_ON;
        }
    }

    if( ExecEraseFlag == (uint8)STD_ON )
    {
        Ret = DiagSrv_0x31_Erase_EraseBlock(EraseAddr);
        if( Ret == (Std_ReturnType)E_OK )
        {
            DiagSrv_0x31_Erase_JobStatus = DIAGSRV_0X31_ERASE_STAT_WAIT_ERASE_MEM;
            Nrc = DIAG_NRC_RCRRP;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Erase_EraseBlock                              */
/* Description   | Erase memory block                                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] EraseAddr : Erase address                             */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_EraseBlock
(
    VAR(uint32, AUTOMATIC) EraseAddr
)
{
    VAR(RpgLib_MemBlockInfoType, AUTOMATIC) BlockInfo;
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    BlockInfo.BlockTopAddr = 0UL;
    BlockInfo.BlockSize = 0UL;

    FuncRet = RpgLib_GetMemBlockInfo(RPGLIB_MEMORYID_0, EraseAddr, &BlockInfo);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        FuncRet = RpgLib_ReqMemBlockErase(RPGLIB_MEMORYID_0, &BlockInfo);
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            DiagSrv_0x31_Erase_AreaInfo.CurrentBlockTopAddr = BlockInfo.BlockTopAddr;
            DiagSrv_0x31_Erase_AreaInfo.CurrentBlockSize = BlockInfo.BlockSize;

            Ret = E_OK;
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Erase_EndProcess                              */
/* Description   | End processing                                             */
/* Preconditions |                                                            */
/* Parameters    | [IN] Nrc : NRC                                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Erase_EndProcess
(
    VAR(uint8, AUTOMATIC) Nrc
)
{
    if( Nrc != DIAG_NRC_RCRRP )
    {
        DiagSrv_0x31_Erase_ClearInfo();
    }

    return;
}


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
