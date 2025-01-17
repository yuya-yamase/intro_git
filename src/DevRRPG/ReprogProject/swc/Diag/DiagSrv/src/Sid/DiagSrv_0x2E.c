/* DiagSrv_0x2E_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x2E/CODE                                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagLib.h>
#include <Rte.h>

#include <DiagSrv.h>
#include "DiagSrv_0x2E.h"
#include "DiagSrv_0x2E_Cfg.h"
#include "DiagSrv_Local.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Data Length */
#define DIAGSRV_0X2E_DATA_RECORD_MIN_LEN        ((uint16)1U)
#define DIAGSRV_0X2E_RSP_LEN                    ((uint16)3U)

/* Message Parameter Position */
#define DIAGSRV_0X2E_SID_POS                    ((uint8)0U)
#define DIAGSRV_0X2E_DID_H_POS                  ((uint8)1U)
#define DIAGSRV_0X2E_DID_L_POS                  ((uint8)2U)
#define DIAGSRV_0X2E_DATA_RECORD_POS            ((uint8)3U)

/* DID */
#define DIAGSRV_0X2E_DID_NONCE                  ((uint16)0xF050U)
#define DIAGSRV_0X2E_DID_FINGERPRINT_0          ((uint16)0xF120U)
#define DIAGSRV_0X2E_DID_FINGERPRINT_31         ((uint16)0xF13FU)

/* DID Type */
#define DIAGSRV_0X2E_DIDTYPE_NONCE              ((uint8)0x01U)
#define DIAGSRV_0X2E_DIDTYPE_FINGERPRINT        ((uint8)0x02U)

/* Other */
#define DIAGSRV_0X2E_MASK_DID_TO_REWRITEAREANUM ((uint16)0x001FU)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x2E_CheckReqMsg
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg,
    P2VAR(uint16, AUTOMATIC, DIAGSRV_APPL_DATA) Did,
    P2VAR(uint16, AUTOMATIC, DIAGSRV_APPL_DATA) DataLength
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x2E_CheckRewriteStatus
(
    VAR(uint16, AUTOMATIC) Did
);
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x2E_CheckDidType
(
    VAR(uint16, AUTOMATIC) Did
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x2E_SetReqData
(
    VAR(uint16, AUTOMATIC) Did,
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) SrcDataAddr,
    VAR(uint16, AUTOMATIC) DataLength
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x2E_SetNonceData
(
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) SrcDataAddr,
    VAR(uint8, AUTOMATIC) NextRewriteStatus
);
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x2E_SetFingerPrintData
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum,
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) SrcDataAddr,
    VAR(uint8, AUTOMATIC) NextRewriteStatus
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

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
/* Function Name | DiagSrv_0x2E_Init                                          */
/* Description   | Initialize                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x2E_Init (void)
{
    /* No process */
    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x2E_Time                                          */
/* Description   | Time function                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x2E_Time (void)
{
    /* No process */
    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x2E_Processing                                    */
/* Description   | Processing function                                        */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x2E_Processing
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
)
{
    VAR(uint16, AUTOMATIC) Did;
    VAR(uint16, AUTOMATIC) DataLength;
    VAR(uint8, AUTOMATIC) Nrc;

    Did = 0U;
    DataLength = 0U;

    Nrc = DiagSrv_0x2E_CheckReqMsg(Msg, &Did, &DataLength);
    if( Nrc == DIAG_NRC_PR )
    {
        Nrc = DiagSrv_0x2E_CheckRewriteStatus(Did);
    }

    if( Nrc == DIAG_NRC_PR )
    {
        DiagSrv_0x2E_SetReqData(Did, &(Msg->ReqData[DIAGSRV_0X2E_DATA_RECORD_POS]), DataLength);

        Msg->ResData[DIAGSRV_0X2E_SID_POS]   = DIAG_MAKE_POSRSP_SID(Msg);
        Msg->ResData[DIAGSRV_0X2E_DID_H_POS] = Msg->ReqData[DIAGSRV_0X2E_DID_H_POS];
        Msg->ResData[DIAGSRV_0X2E_DID_L_POS] = Msg->ReqData[DIAGSRV_0X2E_DID_L_POS];
        Msg->ResDataLen = DIAGSRV_0X2E_RSP_LEN;

        DiagLib_SendPosRsp(Msg);
    }
    else
    {
        DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_IDLE);

        DiagLib_SendNegRsp(Nrc, Msg);
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x2E_Confirmation                                  */
/* Description   | Confirmation function                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] Status : Transmission complete status                 */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x2E_Confirmation
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
/* Function Name | DiagSrv_0x2E_CheckReqMsg                                   */
/* Description   | Check NRC of request message                               */
/* Preconditions |                                                            */
/* Parameters    | [IN]  Msg        : Message                                 */
/*               | [OUT] Did        : Did                                     */
/*               | [OUT] DataLength : Data length                             */
/* Return Value  | NRC                                                        */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x2E_CheckReqMsg
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg,
    P2VAR(uint16, AUTOMATIC, DIAGSRV_APPL_DATA) Did,
    P2VAR(uint16, AUTOMATIC, DIAGSRV_APPL_DATA) DataLength
)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Index;
    VAR(uint16, AUTOMATIC) MinLength;
    VAR(uint16, AUTOMATIC) MaxLength;

    Nrc = DIAG_NRC_IMLOIF;
    MinLength = DIAG_DIDMSG_MIN_SIZE + DIAGSRV_0X2E_DATA_RECORD_MIN_LEN;
    if( Msg->ReqDataLen >= MinLength )
    {
        /* Get DID from Msg */
        *Did = (uint16)Rte_Rpg_ByteCombine(&Msg->ReqData[DIAGSRV_0X2E_DID_H_POS], sizeof(*Did));

        Index = 0U;
        Nrc = DiagLib_CheckDidSupport(*Did, &DiagSrv_0x2E_DidConfig, &Index);

        if( Nrc != DIAG_NRC_ROOR )
        {
            MaxLength = DIAG_DIDMSG_MIN_SIZE + (DiagSrv_0x2E_DidConfig.InfoPtr[Index].Length);
            if( MaxLength < Msg->ReqDataLen )
            {
                Nrc = DIAG_NRC_IMLOIF;
            }
            else if( Nrc == DIAG_NRC_PR )
            {
                *DataLength = DiagSrv_0x2E_DidConfig.InfoPtr[Index].Length;
            }
            else
            {
                /* No process */
            }
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x2E_CheckRewriteStatus                            */
/* Description   | Check NRC of rewrite status                                */
/* Preconditions |                                                            */
/* Parameters    | [IN]  Did : DID                                            */
/* Return Value  | NRC                                                        */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x2E_CheckRewriteStatus
(
    VAR(uint16, AUTOMATIC) Did
)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) RewriteStatus;
    VAR(uint8, AUTOMATIC) DidType;

    Nrc = DIAG_NRC_CNC;

    RewriteStatus = DiagSrv_GetRewriteStatus();
    DidType = DiagSrv_0x2E_CheckDidType(Did);

    if( DidType == DIAGSRV_0X2E_DIDTYPE_FINGERPRINT )
    {
        if( (RewriteStatus == DIAGSRV_REWRITESTAT_IDLE) ||
            (RewriteStatus == DIAGSRV_REWRITESTAT_DATA_CHECK) )
        {
            Nrc = DIAG_NRC_PR;
        }
    }
    else if( DidType == DIAGSRV_0X2E_DIDTYPE_NONCE )
    {
        if( RewriteStatus == DIAGSRV_REWRITESTAT_FINGER_RECV )
        {
            Nrc = DIAG_NRC_PR;
        }
    }
    else
    {
        /* No process */
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x2E_CheckDidType                                  */
/* Description   | Return DID Type from DID                                   */
/* Preconditions |                                                            */
/* Parameters    | [IN] Did : DID                                             */
/* Return Value  | DID type                                                   */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x2E_CheckDidType
(
    VAR(uint16, AUTOMATIC) Did
)
{
    VAR(uint8, AUTOMATIC) DidType;

    DidType = 0U;

    if( DIAGSRV_0X2E_DID_NONCE == Did )
    {
        DidType = DIAGSRV_0X2E_DIDTYPE_NONCE;
    }
    else if( (DIAGSRV_0X2E_DID_FINGERPRINT_0 <= Did) && (Did <= DIAGSRV_0X2E_DID_FINGERPRINT_31) )
    {
        DidType = DIAGSRV_0X2E_DIDTYPE_FINGERPRINT;
    }
    else
    {
        /* No process */
    }

    return DidType;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x2E_SetReqData                                    */
/* Description   | Set Request Data                                           */
/* Preconditions |                                                            */
/* Parameters    | [IN] Did         : DID                                     */
/*               | [IN] SrcDataAddr : Source data address                     */
/*               | [IN] DataLength  : Data length                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x2E_SetReqData
(
    VAR(uint16, AUTOMATIC) Did,
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) SrcDataAddr,
    VAR(uint16, AUTOMATIC) DataLength
)
{
    VAR(uint8, AUTOMATIC) RewriteAreaNum;
    VAR(uint8, AUTOMATIC) DidType;

    DidType = DiagSrv_0x2E_CheckDidType(Did);

    if( DidType == DIAGSRV_0X2E_DIDTYPE_NONCE )
    {
        DiagSrv_0x2E_SetNonceData(SrcDataAddr, DIAGSRV_REWRITESTAT_READY);
    }
    else if( DidType == DIAGSRV_0X2E_DIDTYPE_FINGERPRINT )
    {
        RewriteAreaNum = (uint8)(Did & DIAGSRV_0X2E_MASK_DID_TO_REWRITEAREANUM);
        DiagSrv_0x2E_SetFingerPrintData(RewriteAreaNum, SrcDataAddr, DIAGSRV_REWRITESTAT_FINGER_RECV);
    }
    else
    {
        /* No process */
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x2E_SetNonceData                                  */
/* Description   | Set nonce data and update rewrite status                   */
/* Preconditions |                                                            */
/* Parameters    | [IN] SrcDataAddr       : Source data address of nonce      */
/*               | [IN] NextRewriteStatus : Next rewrite status               */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x2E_SetNonceData
(
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) SrcDataAddr,
    VAR(uint8, AUTOMATIC) NextRewriteStatus
)
{
    DiagSrv_SetNonceTempArea(SrcDataAddr);
    DiagSrv_SetRewriteStatus(NextRewriteStatus);

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x2E_SetFingerPrintData                            */
/* Description   | Set fingerprint data and update rewrite status             */
/* Preconditions |                                                            */
/* Parameters    | [IN] RewriteAreaNum    : Rewrite area number               */
/*               | [IN] SrcDataAddr       : Source data address of fingerprint*/
/*               | [IN] NextRewriteStatus : Next rewrite status               */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x2E_SetFingerPrintData
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum,
    P2CONST(uint8, AUTOMATIC, DIAGSRV_APPL_CONST) SrcDataAddr,
    VAR(uint8, AUTOMATIC) NextRewriteStatus
)
{
    DiagSrv_SetRewriteAreaNumber(RewriteAreaNum);
    DiagSrv_SetFingerprintTempArea(SrcDataAddr);
    DiagSrv_SetRewriteStatus(NextRewriteStatus);
    DiagSrv_EnableChangePrgSession();

    return;
}

#define DIAGSRV_STOP_SEC_CODE
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/03/01 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

