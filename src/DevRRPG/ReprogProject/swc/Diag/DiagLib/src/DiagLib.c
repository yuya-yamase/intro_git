/* DiagLib_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagLib/CODE                                                */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <ComStack_Types.h>

#include <Gdn.h>
#include <Rte.h>
#include <DiagLib.h>

#include "DiagLib_Local.h"
#include "DiagLib_Cfg.h"
#include "DiagSrv_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGLIB_REQDATA_IDX_RID           (2U)

#define DIAGLIB_SESSION_BIT_DEF           (STD_ON << (DIAG_SESSION_DEF - (uint8)1U))
#define DIAGLIB_SESSION_BIT_PRG           (STD_ON << (DIAG_SESSION_PRG - (uint8)1U))
#define DIAGLIB_SESSION_BIT_EXT           (STD_ON << (DIAG_SESSION_EXT - (uint8)1U))

#define DIAGLIB_API_ID_PENDRESPSENTHOOK   (0x00U)

#define DIAGLIB_E_TMRESET                 (0x80U)

#define DIAGLIB_RID_LENGTH_SKIP_CHK       ((uint16)0xFFFFU)

#define DIAGLIB_SUBFUNCISEXISTSSID_NUM    (sizeof(DiagLib_SubfuncIsExistsSid) / sizeof(DiagLib_SubfuncIsExistsSid[0]))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    Rte_Tm_PredefTimer1us32bitType PendingStartTime;
    uint8 EnableFlag;
} DiagLib_PendingStartTimeType;

typedef struct {
    uint32 Num;
    P2CONST(uint8, TYPEDEF, DIAGLIB_APPL_CONST) TblPtr;
} DiagLib_SubfuncSidInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(uint8, DIAGLIB_CODE_FAST) DiagLib_CheckSessionSupport
(
    P2CONST(Diag_SessionSupportType, AUTOMATIC, DIAGLIB_APPL_CONST) SessionInfo
);
static FUNC(uint8, DIAGLIB_CODE_FAST) DiagLib_CheckSecuritySupport
(
    P2CONST(Diag_SecuritySupportType, AUTOMATIC, DIAGLIB_APPL_CONST) SecurityInfo
);
#if ((REPROG_CFG_SUBMICON_NOUSE == STD_ON) || (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON))
static FUNC(void, DIAGLIB_CODE_FAST) DiagLib_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
);
#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGLIB_START_SEC_VAR
#include <DiagLib_MemMap.h>

static VAR(DiagLib_PendingStartTimeType, DIAGLIB_VAR_CLEARED) DiagLib_PendingStartTime;
static VAR(uint8, DIAGLIB_VAR_CLEARED) DiagLib_TransferMode;

#define DIAGLIB_STOP_SEC_VAR
#include <DiagLib_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGLIB_START_SEC_CST
#include <DiagLib_MemMap.h>

static CONST(uint8, DIAGLIB_CONST) DiagLib_SubfuncIsExistsSid[] = {
     DIAG_SID_DSC
    ,DIAG_SID_ER
    ,DIAG_SID_SA
    ,DIAG_SID_CC
    ,DIAG_SID_ARS
    ,DIAG_SID_TP
    ,DIAG_SID_CDTCS
    ,DIAG_SID_ROE
    ,DIAG_SID_LC
    ,DIAG_SID_DDDI
    ,DIAG_SID_RDTCI
    ,DIAG_SID_RC
};

static CONST(AB_83_ConstV DiagLib_SubfuncSidInfoType, DIAGLIB_CONST) DiagLib_SubfuncSidInfo = {
    DIAGLIB_SUBFUNCISEXISTSSID_NUM,
    &DiagLib_SubfuncIsExistsSid[0]
};

#define DIAGLIB_STOP_SEC_CST
#include <DiagLib_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define DIAGLIB_START_SEC_CODE
#include <DiagLib_MemMap.h>

/******************************************************************************/
/* Function Name | DiagLib_Init                                               */
/* Description   | Initializes DiagLib                                        */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_Init (void)
{
    DiagLib_PendingStartTime.PendingStartTime.StartPoint = 0UL;
    DiagLib_PendingStartTime.EnableFlag = STD_OFF;

    DiagLib_TransferMode = DIAG_TFMODE_NONE;

    return;
}

/******************************************************************************/
/* Function Name | DiagLib_Time                                               */
/* Description   | TimeFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_Time (void)
{
    return;
}

/******************************************************************************/
/* Function Name | DiagLib_SendPosRsp                                         */
/* Description   | Sends positive response                                    */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_SendPosRsp
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGLIB_APPL_DATA) Msg
)
{
    DiagLib_SetSuppressResponseBySid(Msg);

    Gdn_Dcm_Dcp_ProcessingDone(Msg, GDN_DCM_NormalDone);

    return;
}

/******************************************************************************/
/* Function Name | DiagLib_SendNegRsp                                         */
/* Description   | Sends negative response                                    */
/* Preconditions |                                                            */
/* Parameters    | [IN] Nrc : NRC                                             */
/*               | [IN] Msg : Message                                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_SendNegRsp
(
    VAR(uint8, AUTOMATIC) Nrc,
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGLIB_APPL_DATA) Msg
)
{
    VAR(Gdn_Dcm_NegativeResponseInfoType, AUTOMATIC) NegRsp;

    NegRsp.Nrc = Nrc;
    NegRsp.ResponseSuppressInfo[GDN_DCM_AddressKindPhysical] = GDN_FALSE;

    DiagLib_SetFuncAddressSuppressByNrc(&NegRsp);

    Gdn_Dcm_TransmitNegativeResponse(&NegRsp, Msg);

    return;
}

/******************************************************************************/
/* Function Name | DiagLib_SetSuppressResponseBySid                           */
/* Description   | Sets suppress response information by SID                  */
/* Preconditions |                                                            */
/* Parameters    | [INOUT] Msg : Message                                      */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_SetSuppressResponseBySid
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGLIB_APPL_DATA) Msg
)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) Sid;

    Sid = DIAG_GET_SID(Msg);

    Msg->SuppressResponse = DIAG_FALSE;

    for( i = 0UL; i < DiagLib_SubfuncSidInfo.Num; i++ )
    {
        if( Sid == DiagLib_SubfuncSidInfo.TblPtr[i] )
        {
            Msg->SuppressResponse = DIAG_CHECK_SPRMIB(Msg);
            break;
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagLib_SetFuncAddressSuppressByNrc                        */
/* Description   | Sets suppress response information for Functional Address  */
/*               | by Nrc                                                     */
/* Preconditions |                                                            */
/* Parameters    | [INOUT] NegRsp : Negative Response Information             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_SetFuncAddressSuppressByNrc
(
    P2VAR(Gdn_Dcm_NegativeResponseInfoType, AUTOMATIC, DIAGLIB_APPL_DATA) NegRsp
)
{
    NegRsp->ResponseSuppressInfo[GDN_DCM_AddressKindFunctional] = GDN_FALSE;

    if( ( NegRsp->Nrc == DIAG_NRC_SNS ) ||
        ( NegRsp->Nrc == DIAG_NRC_SFNS ) ||
        ( NegRsp->Nrc == DIAG_NRC_ROOR ) ||
        ( NegRsp->Nrc == DIAG_NRC_SFNSIAS ) ||
        ( NegRsp->Nrc == DIAG_NRC_SNSIAS ) )
    {
        NegRsp->ResponseSuppressInfo[GDN_DCM_AddressKindFunctional] = GDN_TRUE;
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagLib_CancelProcessingFinished                           */
/* Description   | Finishes cancel process                                    */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_CancelProcessingFinished
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGLIB_APPL_CONST) Msg
)
{
    Gdn_Dcm_Dcp_ProcessingDone(Msg, GDN_DCM_NormalDone);

    return;
}

/******************************************************************************/
/* Function Name | DiagLib_GetComStatus                                       */
/* Description   | Acquires status of communication                           */
/* Preconditions |                                                            */
/* Return Value  | Status                                                     */
/*               |  DIAG_COM_IDLE                                             */
/*               |  DIAG_COM_BUSY                                             */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_GetComStatus (void)
{
    VAR(gdn_uint8, AUTOMATIC) Stat;
    VAR(uint8, AUTOMATIC) Ret;

    Ret = DIAG_COM_BUSY;

    Stat = Gdn_Dcm_Dcp_GetComStatus();
    if( Stat == GDN_DCM_DCP_COM_IDLE )
    {
        Ret = DIAG_COM_IDLE;
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagLib_GetPendingRspInfo                                  */
/* Description   | Acquires pending response information                      */
/* Preconditions |                                                            */
/* Parameters    | [OUT] Status      : Pending response status                */
/*               |        DIAG_PENDRSP_NO                                     */
/*               |        DIAG_PENDRSP_SENT                                   */
/*               | [OUT] ElapsedTime : Time elapsed after the Pending         */
/*               |                     response transmission                  */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, DIAGLIB_CODE_SLOW) DiagLib_GetPendingRspInfo
(
    P2VAR(uint8, AUTOMATIC, DIAGLIB_APPL_DATA) Status,
    P2VAR(uint32, AUTOMATIC, DIAGLIB_APPL_DATA) ElapsedTime
)
{
    VAR(gdn_uint8, AUTOMATIC) Stat;
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    Stat = Gdn_Dcm_Dcp_GetPendRespStatus();
    if( Stat == GDN_DCM_DCP_PENDRESP_SENT )
    {
        if( DiagLib_PendingStartTime.EnableFlag == (uint8)STD_ON )
        {
            FuncRet = Rte_Tm_GetTimeSpan1us32bit(&DiagLib_PendingStartTime.PendingStartTime, ElapsedTime);
            if( FuncRet == (Std_ReturnType)E_OK )
            {
                *Status = DIAG_PENDRSP_SENT;
                Ret = E_OK;
            }
        }
    }
    else
    {
        *Status = DIAG_PENDRSP_NO;
        Ret = E_OK;
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagLib_GetCurrentPduId                                    */
/* Description   | Acquires current PduId                                     */
/* Preconditions |                                                            */
/* Parameters    | [OUT] PduId : Current PDU ID                               */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, DIAGLIB_CODE_SLOW) DiagLib_GetCurrentPduId
(
    P2VAR(PduIdType, AUTOMATIC, DIAGLIB_APPL_DATA) PduId
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Gdn_Std_ReturnType, AUTOMATIC) GdnResult;

    Ret = E_NOT_OK;

    GdnResult = Gdn_Dcm_Dcp_GetRxPduId(PduId);
    if( GdnResult == GDN_E_OK )
    {
        Ret = E_OK;
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagLib_CheckSidSupport                                    */
/* Description   | Checks SID support information                             */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/* Return Value  | Nrc                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_SNS                                              */
/*               |  DIAG_NRC_SNSIAS                                           */
/*               |  DIAG_NRC_SAD                                              */
/* Notes         | - This function checks the following                       */
/*               |   [ISO 14229-1:2020(E)][Figure 5]                          */
/*               |   - SID supported?                                         */
/*               |   - SID supported in active session?                       */
/*               |   - SID security check OK?                                 */
/******************************************************************************/
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_CheckSidSupport
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGLIB_APPL_CONST) Msg
)
{
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) Sid;
    VAR(uint8, AUTOMATIC) ChkRet;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_SNS;

    if( Msg != NULL_PTR )
    {
        Sid = DIAG_GET_SID(Msg);

        for( i = 0U; i < DiagSrv_SidConfig.SidNum; i++ )
        {
            if( Sid == DiagSrv_SidConfig.InfoPtr[i].Sid )
            {
                Nrc = DIAG_NRC_PR;
                break;
            }
        }

        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DIAG_NRC_SNS;

            if( ( ( Msg->ReqType == DIAG_ADDRESSING_FUNC ) && ( DiagSrv_SidConfig.InfoPtr[i].Addressing.SupportFunc == DIAG_SUPPORT ) ) ||
                ( ( Msg->ReqType == DIAG_ADDRESSING_PHYS ) && ( DiagSrv_SidConfig.InfoPtr[i].Addressing.SupportPhys == DIAG_SUPPORT ) ) )
            {
                Nrc = DIAG_NRC_PR;
            }
        }

        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DIAG_NRC_SNSIAS;

            ChkRet = DiagLib_CheckSessionSupport(&DiagSrv_SidConfig.InfoPtr[i].Session);
            if( ChkRet == DIAG_SUPPORT )
            {
                Nrc = DIAG_NRC_PR;
            }
        }

        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DIAG_NRC_SAD;

            ChkRet = DiagLib_CheckSecuritySupport(&DiagSrv_SidConfig.InfoPtr[i].Security);
            if( ChkRet == DIAG_SUPPORT )
            {
                Nrc = DIAG_NRC_PR;
            }
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagLib_CheckSubfunctionSupport                            */
/* Description   | Checks subfunction support information                     */
/* Preconditions |                                                            */
/* Parameters    | [IN]  Msg           : Message                              */
/*               | [IN]  SubfuncConfig : Subfunction Config                   */
/*               | [OUT] Index         : Config Index                         */
/* Return Value  | Nrc                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_SFNS                                             */
/*               |  DIAG_NRC_IMLOIF                                           */
/*               |  DIAG_NRC_SAD                                              */
/*               |  DIAG_NRC_SFNSIAS                                          */
/* Notes         | - This function checks the following                       */
/*               |   [ISO 14229-1:2020(E)][Figure 6]                          */
/*               |   - Minimum length check                                   */
/*               |   - SubFunction supported ever for the SID?                */
/*               |   - SubFunction supported in active session for the SID?   */
/*               |   - SubFunction security check OK?                         */
/******************************************************************************/
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_CheckSubfunctionSupport
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGLIB_APPL_CONST) Msg,
    P2CONST(Diag_SubfuncConfigType, AUTOMATIC, DIAGLIB_APPL_CONST) SubfuncConfig,
    P2VAR(uint8, AUTOMATIC, DIAGLIB_APPL_DATA) Index
)
{
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) Subfunction;
    VAR(uint8, AUTOMATIC) ChkRet;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_IMLOIF;

    if( ( Msg != NULL_PTR ) && ( SubfuncConfig != NULL_PTR ) && ( Index != NULL_PTR ) &&
        ( Msg->ReqDataLen >= DIAG_SUBFUNCMSG_MIN_SIZE ) )
    {
        Nrc = DIAG_NRC_SFNS;

        Subfunction = DIAG_GET_SUBFUNCTION(Msg);

        for( i = 0U; i < SubfuncConfig->SubfuncNum; i++ )
        {
            if( Subfunction == SubfuncConfig->InfoPtr[i].Subfunc )
            {
                *Index = i;
                Nrc = DIAG_NRC_PR;
                break;
            }
        }

        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DIAG_NRC_SFNSIAS;

            ChkRet = DiagLib_CheckSessionSupport(&SubfuncConfig->InfoPtr[i].Session);
            if( ChkRet == DIAG_SUPPORT )
            {
                Nrc = DIAG_NRC_PR;
            }
        }

        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DIAG_NRC_SAD;

            ChkRet = DiagLib_CheckSecuritySupport(&SubfuncConfig->InfoPtr[i].Security);
            if( ChkRet == DIAG_SUPPORT )
            {
                Nrc = DIAG_NRC_PR;
            }
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagLib_CheckDidSupport                                    */
/* Description   | Checks DID support information                             */
/* Preconditions |                                                            */
/* Parameters    | [IN]  Did       : Did                                      */
/*               | [IN]  DidConfig : Did Config                               */
/*               | [OUT] Index     : Config Index                             */
/* Return Value  | Nrc                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_ROOR                                             */
/*               |  DIAG_NRC_SAD                                              */
/* Notes         | - This function checks the following                       */
/*               |   [ISO 14229-1:2020(E)]                                    */
/*               |   - DID supports in active session                         */
/*               |   - DID security check OK ?                                */
/******************************************************************************/
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_CheckDidSupport
(
    VAR(uint16, AUTOMATIC) Did,
    P2CONST(Diag_DidConfigType, AUTOMATIC, DIAGLIB_APPL_CONST) DidConfig,
    P2VAR(uint8, AUTOMATIC, DIAGLIB_APPL_DATA) Index
)
{
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) ChkRet;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_ROOR;

    if( ( DidConfig != NULL_PTR ) && ( Index != NULL_PTR ) )
    {
        for( i = 0U; i < DidConfig->DidNum; i++ )
        {
            if( Did == DidConfig->InfoPtr[i].Did )
            {
                *Index = i;
                Nrc = DIAG_NRC_PR;
                break;
            }
        }

        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DIAG_NRC_ROOR;

            ChkRet = DiagLib_CheckSessionSupport(&DidConfig->InfoPtr[i].Session);
            if( ChkRet == DIAG_SUPPORT )
            {
                Nrc = DIAG_NRC_PR;
            }
        }

        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DIAG_NRC_SAD;

            ChkRet = DiagLib_CheckSecuritySupport(&DidConfig->InfoPtr[i].Security);
            if( ChkRet == DIAG_SUPPORT )
            {
                Nrc = DIAG_NRC_PR;
            }
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagLib_CheckRidSupport                                    */
/* Description   | Checks RID support information                             */
/* Preconditions |                                                            */
/* Parameters    | [IN]  Msg       : Message                                  */
/*               | [IN]  RidConfig : Rid Config                               */
/*               | [OUT] Index     : Config Index                             */
/* Return Value  | Nrc                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_RCRRP                                            */
/*               |  DIAG_NRC_SFNS                                             */
/*               |  DIAG_NRC_IMLOIF                                           */
/*               |  DIAG_NRC_ROOR                                             */
/*               |  DIAG_NRC_SAD                                              */
/* Notes         | - This function checks the following                       */
/*               |   [ISO 14229-1:2020(E)][Figure 30]                         */
/*               |   - Minimum length  check                                  */
/*               |   - RID supported In active session?                       */
/*               |   - RID security check OK ?                                */
/*               |   - SubFunction supported for routineIdentifier?           */
/*               |   - total length check                                     */
/******************************************************************************/
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_CheckRidSupport
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGLIB_APPL_CONST) Msg,
    P2CONST(Diag_RidConfigType, AUTOMATIC, DIAGLIB_APPL_CONST) RidConfig,
    P2VAR(uint8, AUTOMATIC, DIAGLIB_APPL_DATA) Index
)
{
    VAR(uint16, AUTOMATIC) Rid;
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) Subfunction;
    VAR(uint8, AUTOMATIC) ChkRet;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_IMLOIF;

    if( ( Msg != NULL_PTR ) && ( RidConfig != NULL_PTR ) && ( Index != NULL_PTR ) &&
        ( Msg->ReqDataLen >= DIAG_RIDMSG_MIN_SIZE ) )
    {
        Nrc = DIAG_NRC_ROOR;

        Rid = (uint16)Rte_Rpg_ByteCombine(&Msg->ReqData[DIAGLIB_REQDATA_IDX_RID], sizeof(Rid));

        for( i = 0U; i < RidConfig->RidNum; i++ )
        {
            if( Rid == RidConfig->InfoPtr[i].Rid )
            {
                *Index = i;
                Nrc = DIAG_NRC_PR;
                break;
            }
        }

        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DIAG_NRC_ROOR;

            ChkRet = DiagLib_CheckSessionSupport(&RidConfig->InfoPtr[i].Session);
            if( ChkRet == DIAG_SUPPORT )
            {
                Nrc = DIAG_NRC_PR;
            }
        }

        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DIAG_NRC_SAD;

            ChkRet = DiagLib_CheckSecuritySupport(&RidConfig->InfoPtr[i].Security);
            if( ChkRet == DIAG_SUPPORT )
            {
                Nrc = DIAG_NRC_PR;
            }
        }

        if( Nrc == DIAG_NRC_PR )
        {
            Nrc = DIAG_NRC_SFNS;

            Subfunction = DIAG_GET_SUBFUNCTION(Msg);
            if( Subfunction == RidConfig->InfoPtr[i].Subfunc )
            {
                Nrc = DIAG_NRC_PR;
            }
        }

        if( Nrc == DIAG_NRC_PR )
        {
            if( RidConfig->InfoPtr[i].Length == DIAGLIB_RID_LENGTH_SKIP_CHK )
            {
                Nrc = DIAG_NRC_RCRRP;
            }
            else
            {
                Nrc = DIAG_NRC_IMLOIF;

                if( Msg->ReqDataLen == ( DIAG_RIDMSG_MIN_SIZE + RidConfig->InfoPtr[i].Length ) )
                {
                    Nrc = DIAG_NRC_PR;
                }
            }
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagLib_GetSession                                         */
/* Description   | Acquires session                                           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Session                                                    */
/*               |  DIAG_SESSION_DEF                                          */
/*               |  DIAG_SESSION_PRG                                          */
/*               |  DIAG_SESSION_EXT                                          */
/*               |  DIAG_SESSION_OTH                                          */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_GetSession (void)
{
    VAR(gdn_uint8, AUTOMATIC) SessionBit;
    VAR(uint8, AUTOMATIC) Session;

    Session = DIAG_SESSION_OTH;

    SessionBit = Gdn_Dcm_Dcp_GetSesCtrlTypeBitPattern();

    if( ( SessionBit & (gdn_uint8)DIAGLIB_SESSION_BIT_DEF ) != (gdn_uint8)0U )
    {
        Session = DIAG_SESSION_DEF;
    }
    else if( ( SessionBit & (gdn_uint8)DIAGLIB_SESSION_BIT_PRG ) != (gdn_uint8)0U )
    {
        Session = DIAG_SESSION_PRG;
    }
    else if( ( SessionBit & (gdn_uint8)DIAGLIB_SESSION_BIT_EXT ) != (gdn_uint8)0U )
    {
        Session = DIAG_SESSION_EXT;
    }
    else
    {
        /* No process */
    }

    return Session;
}

/******************************************************************************/
/* Function Name | DiagLib_SetSession                                         */
/* Description   | Sets session                                               */
/* Preconditions |                                                            */
/* Parameters    | [IN] Session : Session                                     */
/*               |       DIAG_SESSION_DEF                                     */
/*               |       DIAG_SESSION_PRG                                     */
/*               |       DIAG_SESSION_EXT                                     */
/*               | [IN] Factor  : Factor                                      */
/*               |       DIAG_CHGSESSION_FACT_INIT                            */
/*               |       DIAG_CHGSESSION_FACT_S3TIMEOUT                       */
/*               |       DIAG_CHGSESSION_FACT_SID10                           */
/*               |       DIAG_CHGSESSION_FACT_OTHER                           */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_SetSession
(
    VAR(uint8, AUTOMATIC) Session,
    VAR(uint8, AUTOMATIC) Factor
)
{
    VAR(gdn_uint8, AUTOMATIC) SessionBit;

    SessionBit = STD_ON << (Session - (uint8)1U);
    Gdn_Dcm_Dsl_SetSesCtrlTypeBitPattern(SessionBit, Factor);

    return;
}

/******************************************************************************/
/* Function Name | DiagLib_GetSecurityLockStatus                              */
/* Description   | Acquires status of security lock                           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Status                                                     */
/*               |  DIAG_SECURITY_LOCK                                        */
/*               |  DIAG_SECURITY_UNLOCK                                      */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_GetSecurityLockStatus (void)
{
    VAR(gdn_uint8, AUTOMATIC) SecLevelMask;
    VAR(gdn_uint8, AUTOMATIC) Pattern;
    VAR(uint8, AUTOMATIC) Status;

    Status = DIAG_SECURITY_LOCK;

    SecLevelMask = ((gdn_uint8)(STD_ON << DiagLib_SecLevelConfig.Num)) - (gdn_uint8)1U;

    Pattern = Gdn_Dcm_Dcp_GetSecurityLevelBitPattern();
    if( ( Pattern & SecLevelMask ) != (gdn_uint8)0x00U )
    {
        Status = DIAG_SECURITY_UNLOCK;
    }

    return Status;
}

/******************************************************************************/
/* Function Name | DiagLib_GetSecurityLockStatusLevel                         */
/* Description   | Acquires status of security lock(Level)                    */
/* Preconditions |                                                            */
/* Parameters    | [IN] Level : Security level                                */
/* Return Value  | Status                                                     */
/*               |  DIAG_SECURITY_LOCK                                        */
/*               |  DIAG_SECURITY_UNLOCK                                      */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_GetSecurityLockStatusLevel
(
    VAR(uint8, AUTOMATIC) Level
)
{
    VAR(gdn_uint8, AUTOMATIC) SecLevelMask;
    VAR(gdn_uint8, AUTOMATIC) Pattern;
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) i;

    Status = DIAG_SECURITY_LOCK;

    for( i = 0U; i < DiagLib_SecLevelConfig.Num; i++ )
    {
        if( Level == DiagLib_SecLevelConfig.InfoPtr[i].SecurityLevel )
        {
            Pattern = Gdn_Dcm_Dcp_GetSecurityLevelBitPattern();
            SecLevelMask = STD_ON << i;
            if( ( Pattern & SecLevelMask ) != (gdn_uint8)0x00U )
            {
                Status = DIAG_SECURITY_UNLOCK;
            }
            break;
        }
    }

    return Status;
}

/******************************************************************************/
/* Function Name | DiagLib_SetSecurityLockAll                                 */
/* Description   | Sets all security status to lock                           */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_SetSecurityLockAll (void)
{
    Gdn_Dcm_Dcp_SetSecurityLevelBitPattern(GDN_DCM_DCP_SECURITY_ALL_LOCK);

    return;
}

/******************************************************************************/
/* Function Name | DiagLib_SetSecurityUnlockAll                               */
/* Description   | Sets all security status to unlock                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_SetSecurityUnlockAll (void)
{
    VAR(gdn_uint8, AUTOMATIC) Status;

    Status = ((gdn_uint8)(STD_ON << DiagLib_SecLevelConfig.Num)) - (gdn_uint8)1U;

    Gdn_Dcm_Dcp_SetSecurityLevelBitPattern(Status);

    return;
}

/******************************************************************************/
/* Function Name | DiagLib_SetSecurityUnlockLevel                             */
/* Description   | Sets security status of specific level to unlock           */
/* Preconditions |                                                            */
/* Parameters    | [IN] Level : Security level                                */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, DIAGLIB_CODE_SLOW) DiagLib_SetSecurityUnlockLevel
(
    VAR(uint8, AUTOMATIC) Level
)
{
    VAR(uint8, AUTOMATIC) i;
    VAR(gdn_uint8, AUTOMATIC) Status;
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = E_NOT_OK;

    for( i = 0U; i < DiagLib_SecLevelConfig.Num; i++ )
    {
        if( Level == DiagLib_SecLevelConfig.InfoPtr[i].SecurityLevel )
        {
            Status = (gdn_uint8)(STD_ON << i);

            Gdn_Dcm_Dcp_SetSecurityLevelBitPattern(Status);
            Ret = E_OK;
            break;
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagLib_GetTransferMode                                    */
/* Description   | Acquires transfer mode                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | TranferMode                                                */
/*               |  DIAG_TFMODE_NONE                                          */
/*               |  DIAG_TFMODE_DL                                            */
/*               |  DIAG_TFMODE_UL                                            */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, DIAGLIB_CODE_SLOW) DiagLib_GetTransferMode (void)
{
    return DiagLib_TransferMode;
}

/******************************************************************************/
/* Function Name | DiagLib_SetTransferMode                                    */
/* Description   | Sets transfer mode                                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : TranferMode                                    */
/*               |       DIAG_TFMODE_NONE                                     */
/*               |       DIAG_TFMODE_DL                                       */
/*               |       DIAG_TFMODE_UL                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_SetTransferMode
(
    VAR(uint8, AUTOMATIC) Mode
)
{
    DiagLib_TransferMode = Mode;

    return;
}

/******************************************************************************/
/* Function Name | DiagLib_EcuReset                                           */
/* Description   | Resets ECU                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_EcuReset (void)
{
    Gdn_Dcm_Dcp_SetServiceDiscard(GDN_ON);

    /* As the result of this function is always OK, there is no need to check the return value. */
    (void)Rte_SchM_Switch_DcmEcuReset(RTE_SCHM_BSWM_ECU_RESET_EXECUTE);

    return;
}

/******************************************************************************/
/* Function Name | DiagLib_GetMNOBL                                           */
/* Description   | Acquires DL max number of block length                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | DL MNOBL                                                   */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint32, DIAGLIB_CODE_SLOW) DiagLib_GetMNOBL (void)
{
    return DiagLib_TransferConfig.DlMaxNumOfBlockLen;
}

/******************************************************************************/
/* Function Name | DiagLib_GetULMNOBL                                         */
/* Description   | Acquires UL max number of block length                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | UL MNOBL                                                   */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint32, DIAGLIB_CODE_SLOW) DiagLib_GetULMNOBL (void)
{
    return DiagLib_TransferConfig.UlMaxNumOfBlockLen;
}

#if ((REPROG_CFG_SUBMICON_NOUSE == STD_ON) || (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON))
/******************************************************************************/
/* Function Name | DiagLib_PendingRspSentHook                                 */
/* Description   | Acquires pending response start time                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_PendingRspSentHook (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    DiagLib_PendingStartTime.PendingStartTime.StartPoint = 0UL;

    FuncRet = Rte_Tm_ResetTimer1us32bit(&DiagLib_PendingStartTime.PendingStartTime);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        DiagLib_PendingStartTime.EnableFlag = STD_ON;
    }
    else
    {
        DiagLib_ReportError(DIAGLIB_API_ID_PENDRESPSENTHOOK, DIAGLIB_E_TMRESET);
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagLib_PendingRspStopHook                                 */
/* Description   | Stops pending response start time                          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGLIB_CODE_SLOW) DiagLib_PendingRspStopHook (void)
{
    DiagLib_PendingStartTime.EnableFlag = STD_OFF;

    return;
}
#endif

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | DiagLib_CheckSessionSupport                                */
/* Description   | Checks session                                             */
/* Preconditions |                                                            */
/* Parameters    | [IN] SessionInfo : Session information                     */
/* Return Value  | Support status                                             */
/*               |  DIAG_SUPPORT                                              */
/*               |  DIAG_NOT_SUPPORT                                          */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGLIB_CODE_FAST) DiagLib_CheckSessionSupport
(
    P2CONST(Diag_SessionSupportType, AUTOMATIC, DIAGLIB_APPL_CONST) SessionInfo
)
{
    VAR(uint8, AUTOMATIC) Ret;
    VAR(uint8, AUTOMATIC) Session;

    Ret = DIAG_NOT_SUPPORT;

    Session = DiagLib_GetSession();
    if( ( ( Session == DIAG_SESSION_DEF ) && ( SessionInfo->SupportDef == DIAG_SUPPORT ) ) ||
        ( ( Session == DIAG_SESSION_PRG ) && ( SessionInfo->SupportPrg == DIAG_SUPPORT ) ) ||
        ( ( Session == DIAG_SESSION_EXT ) && ( SessionInfo->SupportExt == DIAG_SUPPORT ) ) )
    {
        Ret = DIAG_SUPPORT;
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | DiagLib_CheckSecuritySupport                               */
/* Description   | Checks security                                            */
/* Preconditions |                                                            */
/* Parameters    | [IN] SecurityInfo : Security information                   */
/* Return Value  | Support status                                             */
/*               |  DIAG_SUPPORT                                              */
/*               |  DIAG_NOT_SUPPORT                                          */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGLIB_CODE_FAST) DiagLib_CheckSecuritySupport
(
    P2CONST(Diag_SecuritySupportType, AUTOMATIC, DIAGLIB_APPL_CONST) SecurityInfo
)
{
    VAR(uint8, AUTOMATIC) Ret;
    VAR(uint8, AUTOMATIC) LockStat;

    Ret = DIAG_NOT_SUPPORT;

    LockStat = DiagLib_GetSecurityLockStatus();
    if( LockStat == DIAG_SECURITY_LOCK )
    {
        if( SecurityInfo->SupportLock == DIAG_SUPPORT )
        {
            Ret = DIAG_SUPPORT;
        }
    }
    else
    {
        Ret = DIAG_SUPPORT;
    }

    return Ret;
}

#if ((REPROG_CFG_SUBMICON_NOUSE == STD_ON) || (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON))
/******************************************************************************/
/* Function Name | DiagLib_ReportError                                        */
/* Description   | Notifies ECUM of the error information                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] ApiId   : Api ID                                      */
/*               | [IN] ErrorId : Error ID                                    */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, DIAGLIB_CODE_FAST) DiagLib_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
)
{
    VAR(Rte_EcuM_ErrorType, AUTOMATIC) Error;

    Error.ModuleId = RTE_ECUM_MODULE_DIAGLIB;
    Error.ApiId = ApiId;
    Error.ErrorId = ErrorId;

    Rte_EcuM_ReportError(&Error);

    return;
}
#endif

#define DIAGLIB_STOP_SEC_CODE
#include <DiagLib_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

