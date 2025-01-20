/* DiagSrv_0x37_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x37/CODE                                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <CmpDecmp.h>
#include <Decrypt.h>
#include <DiagLib.h>
#include <RpgLib.h>
#include <RpgMfr.h>
#include <RpgSpp.h>

#include <DiagSrv.h>
#include "DiagSrv_0x36.h"
#include "DiagSrv_0x37.h"
#include "DiagSrv_0x37_Cfg.h"
#include "DiagSrv_Local.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Job Status */
#define DIAGSRV_0X37_STAT_IDLE              ((uint8)0x00U)
#define DIAGSRV_0X37_STAT_RECEPTION         ((uint8)0x01U)
#define DIAGSRV_0X37_STAT_WAIT_POSTDECODE   ((uint8)0x02U)
#define DIAGSRV_0X37_STAT_WAIT_POSTDECMP    ((uint8)0x03U)

/* Data Length */
#define DIAGSRV_0x37_SID_LEN                ((uint8)1U)
#define DIAGSRV_0X37_RSP_DATA_LEN           ((uint8)1U)

/* Message Parameter Position */
#define DIAGSRV_0x37_SID_POS                ((uint8)0U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x37_ClearInfo (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x37_Time_Reception (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x37_Time_PostDecode (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x37_Time_PostDecompress (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x37_CheckMsg (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x37_PostTransferProcess (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x37_PostDecompress (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x37_PostDecode (void);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x37_CheckCondition (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x37_PostTransferProcessSuccess (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x37_SendPosRsp (void);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x37_SendNegRsp
(
    VAR(uint8, AUTOMATIC) Nrc
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x37_Status;
static P2VAR(Diag_MsgContextType, DIAGSRV_VAR_CLEARED, DIAGSRV_APPL_DATA) DiagSrv_0x37_Msg;

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
/* Function Name | DiagSrv_0x37_Init                                          */
/* Description   | Initialize                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x37_Init (void)
{
    DiagSrv_0x37_ClearInfo();

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x37_Time                                          */
/* Description   | Time function                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x37_Time (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_RCRRP;
    if( DiagSrv_0x37_Status != DIAGSRV_0X37_STAT_IDLE )
    {
        if( DiagSrv_0x37_Status == DIAGSRV_0X37_STAT_RECEPTION )
        {
            Nrc = DiagSrv_0x37_Time_Reception();
        }
        else if( DiagSrv_0x37_Status == DIAGSRV_0X37_STAT_WAIT_POSTDECODE )
        {
            Nrc = DiagSrv_0x37_Time_PostDecode();
        }
        else if( DiagSrv_0x37_Status == DIAGSRV_0X37_STAT_WAIT_POSTDECMP )
        {
            Nrc = DiagSrv_0x37_Time_PostDecompress();
        }
        else
        {
            /* No process */
        }

        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DiagSrv_0x37_CheckCondition();
        }

        if( Nrc == DIAG_NRC_RCRRP )
        {
            /* No process */
        }
        else if( Nrc == DIAG_NRC_PR )
        {
            DiagSrv_0x37_PostTransferProcessSuccess();

            DiagSrv_0x37_SendPosRsp();
        }
        else
        {
            DiagSrv_0x37_SendNegRsp(Nrc);
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x37_Processing                                    */
/* Description   | Processing function                                        */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x37_Processing
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
)
{
    DiagSrv_0x37_Status = DIAGSRV_0X37_STAT_RECEPTION;
    DiagSrv_0x37_Msg = Msg;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x37_Confirmation                                  */
/* Description   | Confirmation function                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] Status : Transmission complete status                 */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x37_Confirmation
(
    VAR(uint8, AUTOMATIC) Status
)
{
    /* No process */
    return;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | DiagSrv_0x37_ClearInfo                                     */
/* Description   | Clear information function                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x37_ClearInfo (void)
{
    DiagSrv_0x37_Status = DIAGSRV_0X37_STAT_IDLE;
    DiagSrv_0x37_Msg = NULL_PTR;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x37_Time_Reception                                */
/* Description   | Time of DIAGSRV_0X37_STAT_RECEPTION                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_RSE                                              */
/*               |  DIAG_NRC_IMLOIF                                           */
/*               |  DIAG_NRC_GPF                                              */
/*               |  other(Depends on SID 0x36)                                */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x37_Time_Reception (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DiagSrv_0x36_GetProcessStatus();
    if( Nrc == DIAG_NRC_RCRRP )
    {
        /* No process */
    }
    else if( Nrc == DIAG_NRC_PR )
    {
        Nrc = DiagSrv_0x37_CheckMsg();
        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DiagSrv_0x37_PostTransferProcess();
        }
    }
    else
    {
        /* No process */
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x37_Time_PostDecode                               */
/* Description   | Time of DIAGSRV_0X37_STAT_WAIT_POSTDECODE                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x37_Time_PostDecode (void)
{
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) JobResult;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_RCRRP;

    Status = Decrypt_GetStatus();
    if( Status == DECRYPT_IDLE )
    {
        Nrc = DIAG_NRC_GPF;

        JobResult = Decrypt_GetJobResult();
        if( JobResult == DECRYPT_JOB_OK )
        {
            Nrc = DIAG_NRC_PR;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x37_Time_PostDecompress                           */
/* Description   | Time of DIAGSRV_0X37_STAT_WAIT_POSTDECMP                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x37_Time_PostDecompress (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DiagSrv_0x37_PostDecompress();
    if( Nrc == DIAG_NRC_PR )
    {
        Nrc = DiagSrv_0x37_PostDecode();
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x37_CheckMsg                                      */
/* Description   | Check request message                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RSE                                              */
/*               |  DIAG_NRC_IMLOIF                                           */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x37_CheckMsg (void)
{
    VAR(uint16, AUTOMATIC) MsgDataLen;
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) RewriteStatus;

    Nrc = DIAG_NRC_RSE;

    RewriteStatus = DiagSrv_GetRewriteStatus();
    if( (RewriteStatus == DIAGSRV_REWRITESTAT_SBL_DL_END) ||
        (RewriteStatus == DIAGSRV_REWRITESTAT_DATA_DL_END) )
    {
        MsgDataLen = DIAGSRV_0x37_SID_LEN + DiagSrv_0x37_Config.ParameterSize;
        if( DiagSrv_0x37_Msg->ReqDataLen == MsgDataLen )
        {
            Nrc = DIAG_NRC_PR;
        }
        else
        {
            Nrc = DIAG_NRC_IMLOIF;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x37_PostTransferProcess                           */
/* Description   | Post-transfer processing                                   */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x37_PostTransferProcess (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Nrc = DIAG_NRC_GPF;

    FuncRet = RpgLib_WriteMemFinish();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        Nrc = DiagSrv_0x37_PostDecompress();
        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DiagSrv_0x37_PostDecode();
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x37_PostDecompress                                */
/* Description   | Post-processing of decompression                           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_GPF                                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x37_PostDecompress (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) CompressionMode;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Nrc = DIAG_NRC_PR;

    CompressionMode = DiagSrv_GetCompressionMode();
    if( CompressionMode == (uint8)STD_ON )
    {
        FuncRet = CmpDecmp_PostDecompress();
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            /* No process */
        }
        else if( FuncRet == CMPDECMP_E_PENDING )
        {
            DiagSrv_0x37_Status = DIAGSRV_0X37_STAT_WAIT_POSTDECMP;
            Nrc = DIAG_NRC_RCRRP;
        }
        else
        {
            Nrc = DIAG_NRC_GPF;
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x37_PostDecode                                    */
/* Description   | Post-processing of decryption                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x37_PostDecode (void)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) CipherTextMode;

    Nrc = DIAG_NRC_PR;

    CipherTextMode = DiagSrv_GetCipherTextMode();
    if( CipherTextMode == (uint8)STD_ON )
    {
        Decrypt_ReqPostDecode();

        DiagSrv_0x37_Status = DIAGSRV_0X37_STAT_WAIT_POSTDECODE;

        Nrc = DIAG_NRC_RCRRP;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x37_CheckCondition                                */
/* Description   | Check condition                                            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  other(Depends on UserCustom)                              */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x37_CheckCondition (void)
{
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = RpgMfr_MsgCheckCondition(DiagSrv_0x37_Msg);
    if( Nrc == DIAG_NRC_PR )
    {
        Nrc = RpgSpp_MsgCheckCondition(DiagSrv_0x37_Msg);
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x37_PostTransferProcessSuccess                    */
/* Description   | Successful post-transfer processing                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x37_PostTransferProcessSuccess (void)
{
    VAR(uint8, AUTOMATIC) RewriteStatus;

    DiagLib_SetTransferMode(DIAG_TFMODE_NONE);

    RewriteStatus = DiagSrv_GetRewriteStatus();
    if( RewriteStatus == DIAGSRV_REWRITESTAT_SBL_DL_END )
    {
        DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_SBL_DL_COMPLETE);
    }
    else if( RewriteStatus == DIAGSRV_REWRITESTAT_DATA_DL_END )
    {
        DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_DATA_DL_COMPLETE);
    }
    else
    {
        /* No process */
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x37_SendPosRsp                                    */
/* Description   | Send positive response                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x37_SendPosRsp (void)
{
    DiagSrv_0x37_Msg->ResData[DIAGSRV_0x37_SID_POS] = DIAG_MAKE_POSRSP_SID(DiagSrv_0x37_Msg);
    DiagSrv_0x37_Msg->ResDataLen = DIAGSRV_0X37_RSP_DATA_LEN;

    DiagLib_SendPosRsp(DiagSrv_0x37_Msg);

    DiagSrv_0x37_ClearInfo();

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x37_SendNegRsp                                    */
/* Description   | Send negative response                                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] Nrc : NRC                                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x37_SendNegRsp
(
    VAR(uint8, AUTOMATIC) Nrc
)
{
    VAR(uint8, AUTOMATIC) RewriteAreaNum;

    RewriteAreaNum = DiagSrv_GetRewriteAreaNumber();

    DiagSrv_SetRewriteAreaStatus(RewriteAreaNum, DIAGSRV_LBSTAT_REWRITING_NG);

    DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_IDLE);

    DiagLib_SendNegRsp(Nrc, DiagSrv_0x37_Msg);

    DiagSrv_0x37_ClearInfo();

    return;
}

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

