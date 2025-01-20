/* DiagSrv_0x31_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x31/CODE                                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagLib.h>
#include <DiagSrv.h>
#include <RpgMfr.h>
#include <RpgSpp.h>
#include <Rte.h>

#include "DiagSrv_0x31.h"
#include "DiagSrv_0x31_Cfg.h"
#include "DiagSrv_Local.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Service 0x31 Status */
#define DIAGSRV_0X31_STAT_IDLE              ((uint8)0x00U)
#define DIAGSRV_0X31_STAT_ERASE             ((uint8)0x01U)
#define DIAGSRV_0X31_STAT_CHKMEM            ((uint8)0x02U)
#define DIAGSRV_0X31_STAT_VALIDATE          ((uint8)0x03U)

#define DIAGSRV_0X31_VERSION_INVALID        ((uint8)0xFFU)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_ClearInfo (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_CheckVariableMsgLength
(
    VAR(uint16, AUTOMATIC) Rid
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_EndProcess
(
    VAR(uint8, AUTOMATIC) Nrc
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_SendPosRsp (void);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

P2VAR(Diag_MsgContextType, DIAGSRV_VAR_CLEARED, DIAGSRV_APPL_DATA) DiagSrv_0x31_Msg;
VAR(DiagSrv_0x31_CheckMemoryStatusType, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_CheckMemoryStatus;
VAR(uint16, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_Rid;
VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_ApplicationStatusValue;

static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x31_JobStatus;

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
/* Function Name | DiagSrv_0x31_Init                                          */
/* Description   | Initialize                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Init (void)
{
    DiagSrv_0x31_ClearInfo();

    DiagSrv_0x31_Erase_Init();
    DiagSrv_0x31_Chk_Init();
    DiagSrv_0x31_Valid_Init();

    DiagSrv_0x31_Usr_Init();

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Time                                          */
/* Description   | Time function                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Time (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    DiagSrv_0x31_Usr_Time();

    if( DiagSrv_0x31_JobStatus != DIAGSRV_0X31_STAT_IDLE )
    {
        Nrc = DIAG_NRC_GPF;

        if( DiagSrv_0x31_JobStatus == DIAGSRV_0X31_STAT_ERASE )
        {
            Nrc = DiagSrv_0x31_Erase_Time();
        }
        else if( DiagSrv_0x31_JobStatus == DIAGSRV_0X31_STAT_CHKMEM )
        {
            Nrc = DiagSrv_0x31_Chk_Time();
        }
        else if( DiagSrv_0x31_JobStatus == DIAGSRV_0X31_STAT_VALIDATE )
        {
            Nrc = DiagSrv_0x31_Valid_Time();
        }
        else
        {
            /* No process */
        }

        if( Nrc != DIAG_NRC_RCRRP )
        {
            DiagSrv_0x31_EndProcess(Nrc);
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Processing                                    */
/* Description   | Processing function                                        */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Processing
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) RidIndex;

    DiagSrv_0x31_Msg = Msg;

    RidIndex = 0U;

    Nrc = DiagLib_CheckRidSupport(DiagSrv_0x31_Msg, &DiagSrv_0x31_RidConfig, &RidIndex);
    if( Nrc == DIAG_NRC_RCRRP )
    {
        Nrc = DiagSrv_0x31_CheckVariableMsgLength(DiagSrv_0x31_RidConfig.InfoPtr[RidIndex].Rid);
    }

    if( Nrc == DIAG_NRC_PR )
    {
        DiagSrv_0x31_Rid = DiagSrv_0x31_RidConfig.InfoPtr[RidIndex].Rid;
        if( DiagSrv_0x31_Rid == DIAGSRV_0X31_RID_ERASE )
        {
            Nrc = DiagSrv_0x31_Erase_Processing();
            if( Nrc == DIAG_NRC_RCRRP )
            {
                DiagSrv_0x31_JobStatus = DIAGSRV_0X31_STAT_ERASE;
            }
        }
        else if( (DiagSrv_0x31_Rid == DIAGSRV_0X31_RID_CHECK_SBL) || (DiagSrv_0x31_Rid == DIAGSRV_0X31_RID_CHECK_APL) )
        {
            Nrc = DiagSrv_0x31_Chk_Processing();
            if( Nrc == DIAG_NRC_RCRRP )
            {
                DiagSrv_0x31_JobStatus = DIAGSRV_0X31_STAT_CHKMEM;
            }
        }
        else    /* DIAGSRV_0X31_RID_VALIDATE */
        {
            Nrc = DiagSrv_0x31_Valid_Processing();
            if( Nrc == DIAG_NRC_RCRRP )
            {
                DiagSrv_0x31_JobStatus = DIAGSRV_0X31_STAT_VALIDATE;
            }
        }
    }

    if( Nrc != DIAG_NRC_RCRRP )
    {
        DiagSrv_0x31_EndProcess(Nrc);
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_Confirmation                                  */
/* Description   | Confirmation function                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] Status : Transmission complete status                 */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_Confirmation
(
    VAR(uint8, AUTOMATIC) Status
)
{
    /* No process */
    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_MsgCheckCondition                             */
/* Description   | Processing check message condition                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_MsgCheckCondition (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = RpgMfr_MsgCheckCondition(DiagSrv_0x31_Msg);
    if( Nrc == DIAG_NRC_PR )
    {
        Nrc = RpgSpp_MsgCheckCondition(DiagSrv_0x31_Msg);
        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DIAG_NRC_RCRRP;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_CheckVersionData                              */
/* Description   | Check Version                                              */
/* Preconditions |                                                            */
/* Parameters    | [IN] Version     : Version                                 */
/*               | [IN] VersionSize : Version size                            */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, DIAGSRV_CODE_FAST) DiagSrv_0x31_CheckVersionData
(
    CONST(uint8, AUTOMATIC) Version[],
    VAR(uint8, AUTOMATIC) VersionSize
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(uint8, AUTOMATIC) i;

    Ret = E_NOT_OK;

    for( i = 0U; i < VersionSize; i++ )
    {
        if( Version[i] != DIAGSRV_0X31_VERSION_INVALID )
        {
            Ret = E_OK;
            break;
        }
    }

    return Ret;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | DiagSrv_0x31_ClearInfo                                     */
/* Description   | Clear information                                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_ClearInfo (void)
{
    DiagSrv_0x31_JobStatus = DIAGSRV_0X31_STAT_IDLE;

    DiagSrv_0x31_Msg = NULL_PTR;
    DiagSrv_0x31_Rid = 0U;

    DiagSrv_0x31_CheckMemoryStatus.CheckStatus = DIAGSRV_0X31_CHECKSTATUS_FAILED;
    DiagSrv_0x31_CheckMemoryStatus.FailedCause = DIAGSRV_0X31_FAILEDCAUSE_GENERAL;

    DiagSrv_0x31_ApplicationStatusValue = DIAGSRV_0X31_APLSTATUS_NOT_PRESENT;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_CheckVariableMsgLength                        */
/* Description   | Variable message size check                                */
/* Preconditions |                                                            */
/* Parameters    | [IN] Rid : RID                                             */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_IMLOIF                                           */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x31_CheckVariableMsgLength
(
    VAR(uint16, AUTOMATIC) Rid
)
{
    VAR(uint16, AUTOMATIC) CheckDataLength;
    VAR(uint16, AUTOMATIC) TotalLength;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_IMLOIF;

    if( (Rid == DIAGSRV_0X31_RID_CHECK_SBL) || (Rid == DIAGSRV_0X31_RID_CHECK_APL) )
    {
        if( DiagSrv_0x31_Msg->ReqDataLen >= DIAGSRV_0X31_CHK_MSG_MIN_LEN )
        {
            CheckDataLength = (uint16)Rte_Rpg_ByteCombine(&DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_CHK_DATALEN_POS],
                                                        sizeof(CheckDataLength));

            TotalLength = DIAGSRV_0X31_CHK_MSG_MIN_LEN + CheckDataLength;
            if( DiagSrv_0x31_Msg->ReqDataLen == TotalLength )
            {
                Nrc = DIAG_NRC_PR;
            }
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_EndProcess                                    */
/* Description   | End processing                                             */
/* Preconditions |                                                            */
/* Parameters    | [IN] Nrc : NRC                                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_EndProcess
(
    VAR(uint8, AUTOMATIC) Nrc
)
{
    VAR(uint8, AUTOMATIC) RewriteAreaNum;

    if( Nrc == DIAG_NRC_PR )
    {
        DiagSrv_0x31_SendPosRsp();
    }
    else
    {
        RewriteAreaNum = DiagSrv_GetRewriteAreaNumber();
        if( RewriteAreaNum != DIAGSRV_REWRITEAREA_INVALID )
        {
            DiagSrv_SetRewriteAreaStatus(RewriteAreaNum, DIAGSRV_LBSTAT_REWRITING_NG);
        }

        DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_IDLE);

        DiagLib_SendNegRsp(Nrc, DiagSrv_0x31_Msg);
    }

    DiagSrv_0x31_ClearInfo();

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x31_SendPosRsp                                    */
/* Description   | Send positive response                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x31_SendPosRsp (void)
{
    DiagSrv_0x31_Msg->ResData[DIAGSRV_0X31_SID_POS]         = DIAG_MAKE_POSRSP_SID(DiagSrv_0x31_Msg);
    DiagSrv_0x31_Msg->ResData[DIAGSRV_0X31_SUBFUNC_POS]     = DIAG_GET_SUBFUNCTION(DiagSrv_0x31_Msg);
    DiagSrv_0x31_Msg->ResData[DIAGSRV_0X31_RID_H_POS]       = DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_RID_H_POS];
    DiagSrv_0x31_Msg->ResData[DIAGSRV_0X31_RID_L_POS]       = DiagSrv_0x31_Msg->ReqData[DIAGSRV_0X31_RID_L_POS];
    DiagSrv_0x31_Msg->ResData[DIAGSRV_0X31_ROUTINEINFO_POS] = DIAGSRV_0X31_ROUTINEINFO_VALUE;

    if( DiagSrv_0x31_Rid == DIAGSRV_0X31_RID_ERASE )
    {
        DiagSrv_0x31_Msg->ResDataLen = DIAGSRV_0X31_RESPLEN_ERASE;
    }
    else if( (DiagSrv_0x31_Rid == DIAGSRV_0X31_RID_CHECK_SBL) || (DiagSrv_0x31_Rid == DIAGSRV_0X31_RID_CHECK_APL) )
    {
        if( DiagSrv_0x31_Config.RoutineStatusForceSuccess == DIAG_SUPPORT )
        {
            DiagSrv_0x31_Msg->ResData[DIAGSRV_0X31_CHECKSTATUS_POS] = DIAGSRV_0X31_CHECKSTATUS_SUCCESS;
            DiagSrv_0x31_Msg->ResData[DIAGSRV_0X31_FAILEDCAUSE_POS] = DIAGSRV_0X31_FAILEDCAUSE_NOFAILED;
        }
        else
        {
            DiagSrv_0x31_Msg->ResData[DIAGSRV_0X31_CHECKSTATUS_POS] = DiagSrv_0x31_CheckMemoryStatus.CheckStatus;
            DiagSrv_0x31_Msg->ResData[DIAGSRV_0X31_FAILEDCAUSE_POS] = DiagSrv_0x31_CheckMemoryStatus.FailedCause;
        }

        DiagSrv_0x31_Msg->ResDataLen = DIAGSRV_0X31_RESPLEN_CHECK;

        if( DiagSrv_0x31_CheckMemoryStatus.CheckStatus != DIAGSRV_0X31_CHECKSTATUS_SUCCESS )
        {
            DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_IDLE);
        }
    }
    else    /* DIAGSRV_0X31_RID_VALIDATE */
    {
        if( DiagSrv_0x31_Config.RoutineStatusForceSuccess == DIAG_SUPPORT )
        {
            DiagSrv_0x31_Msg->ResData[DIAGSRV_0X31_APLSTATUS_POS] = DIAGSRV_0X31_APLSTATUS_PRESENT;
        }
        else
        {
            DiagSrv_0x31_Msg->ResData[DIAGSRV_0X31_APLSTATUS_POS] = DiagSrv_0x31_ApplicationStatusValue;
        }

        DiagSrv_0x31_Msg->ResDataLen = DIAGSRV_0X31_RESPLEN_VALID;
    }

    DiagLib_SendPosRsp(DiagSrv_0x31_Msg);

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
