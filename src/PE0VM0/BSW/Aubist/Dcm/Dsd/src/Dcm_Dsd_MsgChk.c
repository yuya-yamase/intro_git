/* Dcm_Dsd_MsgChk_c(v5-5-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsd_MsgChk/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsd/inc/Dcm_Dsd_MsgChk.h"
#include "../../Dsd/inc/Dcm_Dsd_ServiceMng.h"
#include <Dcm/Dcm_Dsl_Ctrl.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSD_DIAGNOSTICSESSIONCONTROL    ((uint8)0x10U)
#define DCM_DSD_ROUTINECONTROL              ((uint8)0x31U)
#define DCM_DSD_LEAST_LENGTH                ((Dcm_MsgLenType)0x02U)
#define DCM_DSD_IND_REQDATALEN_MAX          ((Dcm_MsgLenType)65535U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_MsgChk_ChkSession
(
    P2CONST(AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST) ptSession,
    const uint8 u1SessionLevelNum
);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_MsgChk_ChkSecurity
(
    P2CONST(AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST) ptSecurity,
    const uint8 u1SecurityLevelNum
);
#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


/****************************************************************************/
/* Function Name | Dcm_Dsd_MsgChk_ChkSID                                    */
/* Description   | This function checks whether the received SID is valid   */
/*               | or not.                                                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptMsgContext : pointer to the message context       */
/*               |                                                          */
/*               | [in/out] ptServiceInfo : contains the starting point of  */
/*               | SID search and variable to set the searching result      */
/*               |                                                          */
/*               | [out] ptsubfunc : indicates the received SID has a       */
/*               | subfunction or not                                       */
/*               |                                                          */
/*               | [out] ptErrorCode : pointer to the NRC                   */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK :  SID check finished without NRC            */
/*               |        E_NOT_OK : SID check finished with NRC            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_MsgChk_ChkSID
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    P2VAR(Dcm_Dsd_ServiceCheckType, AUTOMATIC, DCM_APPL_DATA) ptServiceInfo,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA) ptsubfunc,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    P2CONST( AB_83_ConstV uint16, AUTOMATIC, DCM_APPL_CONST ) pt_ServiceIdx;
    P2CONST( AB_83_ConstV Dcm_Dsd_ServiceType, AUTOMATIC, DCM_APPL_CONST ) pt_Service;
    P2CONST( AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST ) pt_SessionLevelRef;
    P2CONST( AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST ) pt_SecurityLevelRef;
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_RetChkSes;
    Std_ReturnType u1_RetChkSec;
    uint16 u2_ServSrchCnt;
    uint16 u2_ServiceIdx;
    uint8 u1_SessionLevelNum;
    uint8 u1_SecurityLevelNum;

    *ptsubfunc = (boolean)FALSE;
    *ptErrorCode = DCM_DSD_NRC_INVALID;
    u1_RetVal = E_NOT_OK;
    ptServiceInfo->ptService = NULL_PTR;

    pt_ServiceIdx = ptServiceInfo->ptServiceTable->ptServiceIdx;
    for( u2_ServSrchCnt = (uint16)0; u2_ServSrchCnt < ptServiceInfo->ptServiceTable->u1ServiceNum; u2_ServSrchCnt++ )
    {
        u2_ServiceIdx = pt_ServiceIdx[u2_ServSrchCnt];
        pt_Service = &Dcm_Dsd_stService[u2_ServiceIdx];
        if( ptMsgContext->reqData[0] == pt_Service->u1Id )
        {
            ptServiceInfo->ptService = pt_Service;
            break;
        }
        else
        {
            /* No process */
        }
    }

    if( ptServiceInfo->ptService != NULL_PTR )
    {
        if( ptServiceInfo->ptService->bSubfuncAvail == (boolean)TRUE )
        {
            if( ptServiceInfo->ptService->u1Id == DCM_DSD_ROUTINECONTROL )
            {
                /* No process */
            }
            else
            {
                *ptsubfunc = (boolean)TRUE;
            }
        }
        else
        {
            /* No process */
        }

        pt_SessionLevelRef = ptServiceInfo->ptService->ptSessionLevelRef;
        u1_SessionLevelNum = ptServiceInfo->ptService->u1SessionLevelNum;
        u1_RetChkSes = Dcm_Dsd_MsgChk_ChkSession(pt_SessionLevelRef, u1_SessionLevelNum);
        if( u1_RetChkSes == (Std_ReturnType)E_OK )
        {
            pt_SecurityLevelRef = ptServiceInfo->ptService->ptSecurityLevelRef;
            u1_SecurityLevelNum = ptServiceInfo->ptService->u1SecurityLevelNum;
            u1_RetChkSec = Dcm_Dsd_MsgChk_ChkSecurity(pt_SecurityLevelRef, u1_SecurityLevelNum);
            if( u1_RetChkSec == (Std_ReturnType)E_OK )
            {
                u1_RetVal = E_OK;
            }
            else
            {
                *ptErrorCode = DCM_E_SECURITYACCESSDENIED;
            }
        }
        else
        {
            *ptErrorCode = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
        }
    }
    else
    {
        *ptErrorCode = DCM_E_SERVICENOTSUPPORTED;
    }
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsd_MsgChk_ChkSubfunction                            */
/* Description   | This function checks whether the subfunction of the SID  */
/*               | is valid or not.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptMsgContext : pointer to the message context       */
/*               |                                                          */
/*               | [in/out] ptSubServiceInfo : contains the starting point  */
/*               | of subfunction search and variable to set the searching  */
/*               | result                                                   */
/*               |                                                          */
/*               | [out] ptErrorCode  : pointer to the NRC                  */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Subfunction check finished without NRC     */
/*               |        E_NOT_OK : Subfunction check finished with NRC    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_MsgChk_ChkSubfunction
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    P2VAR(Dcm_Dsd_SubServiceCheckType, AUTOMATIC, DCM_APPL_DATA) ptSubServiceInfo,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ptErrorCode
)
{
    P2CONST( AB_83_ConstV Dcm_Dsd_SubServiceType, AUTOMATIC, DCM_APPL_CONST ) pt_SubServ;
    P2CONST( AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST ) pt_SessionLevelRef;
    P2CONST( AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST ) pt_SecurityLevelRef;
    Std_ReturnType u1_RetVal;
    Std_ReturnType u1_RetChkSes;
    Std_ReturnType u1_RetChkSec;
    uint8 u1_SubfSrchCnt;
    uint8 u1_SubFunctionWithoutSuprmib;
    uint8 u1_SessionLevelNum;
    uint8 u1_SecurityLevelNum;

    *ptErrorCode = DCM_DSD_NRC_INVALID;
    u1_RetVal = E_NOT_OK;
    ptSubServiceInfo->ptSubService = NULL_PTR;
    u1_SubFunctionWithoutSuprmib = ptMsgContext->reqData[1] & DCM_DSD_SUPPRESS_BITMASK;
    pt_SubServ = ptSubServiceInfo->ptService->ptSubService;

    if( ptMsgContext->reqDataLen >= DCM_DSD_LEAST_LENGTH )
    {
        for( u1_SubfSrchCnt = (uint8)0; u1_SubfSrchCnt < ptSubServiceInfo->ptService->u1SubServiceNum; u1_SubfSrchCnt++ )
        {
            if( pt_SubServ[u1_SubfSrchCnt].ptFnc != NULL_PTR )
            {
                if( u1_SubFunctionWithoutSuprmib == pt_SubServ[u1_SubfSrchCnt].u1Id )
                {
                    ptSubServiceInfo->ptSubService = &pt_SubServ[u1_SubfSrchCnt];
                    break;
                }
                else
                {
                    /* No process */
                }
            }
            else
            {
                /* No process */
            }
        }

        if( ptSubServiceInfo->ptSubService != NULL_PTR )
        {
            pt_SessionLevelRef = ptSubServiceInfo->ptSubService->ptSessionLevelRef;
            u1_SessionLevelNum = ptSubServiceInfo->ptSubService->u1SessionLevelNum;
            u1_RetChkSes = Dcm_Dsd_MsgChk_ChkSession(pt_SessionLevelRef, u1_SessionLevelNum);
            if( u1_RetChkSes == (Std_ReturnType)E_OK )
            {
                pt_SecurityLevelRef = ptSubServiceInfo->ptSubService->ptSecurityLevelRef;
                u1_SecurityLevelNum = ptSubServiceInfo->ptSubService->u1SecurityLevelNum;
                u1_RetChkSec = Dcm_Dsd_MsgChk_ChkSecurity(pt_SecurityLevelRef, u1_SecurityLevelNum);
                if( u1_RetChkSec == (Std_ReturnType)E_OK )
                {
                    u1_RetVal = E_OK;
                }
                else
                {
                    *ptErrorCode = DCM_E_SECURITYACCESSDENIED;
                }
            }
            else
            {
                *ptErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION;
            }
        }
        else
        {
            *ptErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        }
    }
    else
    {
        *ptErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsd_MsgChk_ReqVerify                                 */
/* Description   | This function will put SwC definitions call-out          */
/*               | function (Xxx_Indication) into practice.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1SID :        ServiceID                            */
/*               |                                                          */
/*               | [in] ptMsgContext : Transmit and receive management      */
/*               |                     address                              */
/*               | [in] u1ExecMode :   Execute Mode                         */
/*               |                                                          */
/*               | [out] ptErrorCode : Address to the plant area of         */
/*               |                     the error code                       */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Verification success                       */
/*               |        E_NOT_OK : Verification failure                   */
/*               |        E_REQUEST_NOT_ACCEPTED : Request Not Accepted     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_MsgChk_ReqVerify
(
    const uint8 u1SID,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint8 u1ExecMode,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Dcm_MsgType pt_ReqData;
    Std_ReturnType u1_RetVal;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    Std_ReturnType u1_ReqNotifyRetVal;
    boolean b_ReqNotifyEnabled;
    boolean b_IsErrorCodeConfigured;
    P2CONST(AB_83_ConstV Dcm_Dsd_IndicationFuncType, AUTOMATIC, DCM_APPL_CONST) pt_ReqNotifyFunc;
    Dcm_MsgLenType u4_ReqDataLen;
    uint8 u1_ReqNotifyNum;
    uint8 u1_ReqType;
    uint8 u1_ReqNotifyCounter;
    Dcm_ProtocolType u1_ActiveProtocolType;
    uint16 u2_ConnectionId;
    uint16 u2_TesterSourceAddress;

    *ptErrorCode = DCM_DSD_NRC_INVALID;
    u1_ActiveProtocolType   = DCM_NO_ACTIVE_PROTOCOL;
    u2_ConnectionId         = DCM_DSD_CONID_INVALID;
    u2_TesterSourceAddress  = DCM_DSD_TESTER_INVALID;
    u1_RetVal = E_OK;

    (void)Dcm_GetActiveProtocol( &u1_ActiveProtocolType, &u2_ConnectionId, &u2_TesterSourceAddress ); /* no return check required */

    if( ( u1ExecMode & DCM_DSD_REQVFY_CHKSUPPLIER ) == DCM_DSD_REQVFY_CHKSUPPLIER )
    {
        b_ReqNotifyEnabled = Dcm_Dsd_stConfigSet.bReqSplrNotifyEnabled;
    }
    else
    {
        b_ReqNotifyEnabled = Dcm_Dsd_stConfigSet.bReqMfrNotifyEnabled;
    }

    if( b_ReqNotifyEnabled == (boolean)TRUE )
    {
        if( ( u1ExecMode & DCM_DSD_REQVFY_CHKSUPPLIER ) == DCM_DSD_REQVFY_CHKSUPPLIER )
        {
            u1_ReqNotifyNum = Dcm_Dsd_u1Splrindnotify_Num;
            pt_ReqNotifyFunc = Dcm_Dsd_stConfigSet.ptSplrIndNotify;
        }
        else
        {
            u1_ReqNotifyNum = Dcm_Dsd_u1Mfrindnotify_Num;
            pt_ReqNotifyFunc = Dcm_Dsd_stConfigSet.ptMfrIndNotify;
        }

        if( pt_ReqNotifyFunc != NULL_PTR )
        {
            if( ( u1ExecMode & DCM_DSD_REQVFY_CHKSUBFUNCTION ) == DCM_DSD_REQVFY_CHKSUBFUNCTION )
            {
                pt_ReqData = &ptMsgContext->reqData[0];
                u4_ReqDataLen = ptMsgContext->reqDataLen;
                u1_ReqType = ( ptMsgContext->msgAddInfo.reqType | DCM_DSD_REQVFY_SF_BIT );
            }
            else
            {
                pt_ReqData = &ptMsgContext->reqData[1];
                u4_ReqDataLen = ptMsgContext->reqDataLen-(uint32)1U;    /* no wrap around */
                u1_ReqType = ptMsgContext->msgAddInfo.reqType;
            }

            if( u4_ReqDataLen > DCM_DSD_IND_REQDATALEN_MAX )
            {
                u4_ReqDataLen = DCM_DSD_IND_REQDATALEN_MAX;
            }
            else
            {
                /* No process */
            }

            b_IsErrorCodeConfigured = (boolean)FALSE;

            for( u1_ReqNotifyCounter=(uint8)0U; u1_ReqNotifyCounter<u1_ReqNotifyNum; u1_ReqNotifyCounter++ )    /* MISRA DEVIATION */
            {
                u1_ErrorCode = DCM_DSD_NRC_INVALID;
#ifndef JGXSTACK
                u1_ReqNotifyRetVal = ( pt_ReqNotifyFunc[u1_ReqNotifyCounter] )( u1SID, pt_ReqData, u4_ReqDataLen, u1_ReqType, u2_ConnectionId, &u1_ErrorCode, u1_ActiveProtocolType, u2_TesterSourceAddress );
#else /* JGXSTACK */
                u1_ReqNotifyRetVal = E_OK;
                /* user-defined */
#endif /* JGXSTACK */
                if( u1_ReqNotifyRetVal == (Std_ReturnType)E_OK )
                {
                    /* No process */
                }
                else
                {
                    if( u1_ReqNotifyRetVal == (Std_ReturnType)E_NOT_OK )
                    {
                        if( b_IsErrorCodeConfigured == (boolean)FALSE )
                        {
                            u1_RetVal = u1_ReqNotifyRetVal;
                            *ptErrorCode = u1_ErrorCode;
                            b_IsErrorCodeConfigured = (boolean)TRUE;    /* MISRA DEVIATION */
                        }
                        else
                        {
                            /* No process */
                        }
                    }
                    else
                    {
                        u1_RetVal = u1_ReqNotifyRetVal;
                        *ptErrorCode = u1_ErrorCode;
                        break;
                    }
                }
            }

        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }
    return u1_RetVal ;
}


#if( DCM_SID86_ROE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsd_MsgChk_ChkRoeSrvSupSid                           */
/* Description   | This function checks specified Service is supported in   */
/*               | configulation which determined by PduID and Session type */
/*               | for ROE ServiceToRespondToRecord Service ID Data         */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptServToResp  : Pointer of ServToRespToRec          */
/*               | [in] u4ServToRespToRecLen : Length of ServToRespToRec    */
/*               | [inout] ptServiceInfo : Service Info                     */
/*               | [out] ptSubFunc : SubFunc Presence                       */
/* Return Value  | boolean                                                  */
/*               |        E_OK        : Service is supported                */
/*               |        E_NOT_OK    : Service is not supported            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_MsgChk_ChkRoeSrvSupSid
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA )                      ptServToResp,
    const   uint32                                                  u4ServToRespToRecLen,
    P2VAR(Dcm_Dsd_ServiceCheckType, AUTOMATIC, DCM_APPL_DATA)       ptServiceInfo,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA)                        ptSubfunc
)
{
    P2CONST( AB_83_ConstV uint16, AUTOMATIC, DCM_APPL_CONST ) pt_ServiceIdx;
    Std_ReturnType              u1_RetVal;
    uint8                       u1_ServSrchCnt;
    uint8                       u1_Sid;
    uint16                      u2_ServiceIdx;

    *ptSubfunc                  = (boolean)FALSE;
    u1_RetVal                   = (Std_ReturnType)E_NOT_OK;
    ptServiceInfo->ptService    = NULL_PTR;

    if( u4ServToRespToRecLen > (uint8)0U )
    {
        u1_Sid                  = ptServToResp[DCM_DSD_RX_SID_OFFSET];
        pt_ServiceIdx = ptServiceInfo->ptServiceTable->ptServiceIdx;
        for( u1_ServSrchCnt = (uint8)0U; u1_ServSrchCnt < ptServiceInfo->ptServiceTable->u1ServiceNum; u1_ServSrchCnt++ )
        {
            u2_ServiceIdx = pt_ServiceIdx[u1_ServSrchCnt];
            if( u1_Sid == Dcm_Dsd_stService[u2_ServiceIdx].u1Id )
            {
                ptServiceInfo->ptService = &Dcm_Dsd_stService[u2_ServiceIdx];
                break;
            }
        }
    }

    if( ptServiceInfo->ptService != NULL_PTR )
    {
        /* Target SID is Supported */
        if( ptServiceInfo->ptService->bSubfuncAvail == (boolean)TRUE )
        {
            if( ptServiceInfo->ptService->u1Id != DCM_DSD_ROUTINECONTROL )
            {
                *ptSubfunc = (boolean)TRUE;
            }
        }

         u1_RetVal           = (Std_ReturnType)E_OK;
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsd_MsgChk_ChkRoeSrvSupSubFunc                       */
/* Description   | This function checks specified Service is supported in   */
/*               | configulation which determined by PduID and Session type */
/*               | for ROE ServiceToRespondToRecord SubFunc Data            */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptServToResp  : Pointer of ServToRespToRec          */
/*               | [in] u4ServToRespToRecLen : Length of ServToRespToRec    */
/*               | [inout] ptSubServiceInfo : SubServiceInfo                */
/* Return Value  | boolean                                                  */
/*               |        E_OK        : Service SubFunc is supported        */
/*               |        E_NOT_OK    : Service SubFunc is not supported    */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_MsgChk_ChkRoeSrvSupSubFunc
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA )                      ptServToResp,
    const   uint32                                                  u4ServToRespToRecLen,
    P2VAR(Dcm_Dsd_SubServiceCheckType, AUTOMATIC, DCM_APPL_DATA)    ptSubServiceInfo
)
{
    P2CONST(AB_83_ConstV Dcm_Dsd_SubServiceType, AUTOMATIC, DCM_APPL_CONST) pt_SubServ;
    Std_ReturnType      u1_RetVal;
    uint8               u1_SubfSrchCnt;
    uint8               u1_SubFunction;

    u1_RetVal           = (Std_ReturnType)E_NOT_OK;
    pt_SubServ          = ptSubServiceInfo->ptService->ptSubService;
    ptSubServiceInfo->ptSubService = NULL_PTR;

    if( u4ServToRespToRecLen >= DCM_DSD_LEAST_LENGTH )
    {
        u1_SubFunction  = ptServToResp[DCM_DSD_RX_SF_OFFSET];

        /* Check suppressPosResponseMessageIndicationBit equal 0 */
        if( (uint8)(u1_SubFunction & DCM_DSD_SUPPRESS_BIT) == (uint8)0U )
        {
            for( u1_SubfSrchCnt = (uint8)0U; u1_SubfSrchCnt < ptSubServiceInfo->ptService->u1SubServiceNum; u1_SubfSrchCnt++ )
            {
                if( pt_SubServ[u1_SubfSrchCnt].ptFnc != NULL_PTR )
                {
                    if( u1_SubFunction == pt_SubServ[u1_SubfSrchCnt].u1Id )
                    {
                        ptSubServiceInfo->ptSubService = &pt_SubServ[u1_SubfSrchCnt];
                        break;
                    }
                }
            }
        }
    }

    if( ptSubServiceInfo->ptSubService != NULL_PTR )
    {
        /* Target SID and SubFunction is Supported */
        u1_RetVal   = (Std_ReturnType)E_OK;
    }

    return u1_RetVal;
}

#endif /* DCM_SID86_ROE_USE == STD_ON */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dcm_Dsd_MsgChk_ChkSession                                */
/* Description   | This function searches the session of through configs.   */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptSession : Address to session table of config      */
/*               | [in] u1SessionLevelNum : Number of registered sessions   */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Completed check with session support       */
/*               |        E_NOT_OK : Check completed without session        */
/*               |                   support                                */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_MsgChk_ChkSession
(
    P2CONST(AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST) ptSession,
    const uint8 u1SessionLevelNum
)
{
    Std_ReturnType u1_RetVal;
    uint8 u1_SesSrchCnt;
    Dcm_SesCtrlType u1_SesCtrlType;

    u1_RetVal = E_NOT_OK;
    u1_SesCtrlType = DCM_DEFAULT_SESSION;

    if( ptSession != NULL_PTR )
    {
        (void)Dcm_GetSesCtrlType(&u1_SesCtrlType);      /* no return check required */

        for( u1_SesSrchCnt = (uint8)0; u1_SesSrchCnt <  u1SessionLevelNum; u1_SesSrchCnt++ )
        {
            if( u1_SesCtrlType == ptSession[u1_SesSrchCnt] )
            {
                u1_RetVal = E_OK;

                break;
            }
            else
            {
                /* No process */
            }
        }
    }
    else
    {
        u1_RetVal = E_OK;
    }
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsd_MsgChk_ChkSecurity                               */
/* Description   | This function searches the security of through configs.  */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptSecurity : Address to security table of config    */
/*               | [in] u1SecurityLevelNum : Number of registered security  */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Completed check with session support       */
/*               |        E_NOT_OK : Check completed without session        */
/*               |                   support                                */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_MsgChk_ChkSecurity
(
    P2CONST(AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST) ptSecurity,
    const uint8 u1SecurityLevelNum
)
{
    Std_ReturnType u1_RetVal;
    uint8 u1_SecSrchCnt;
    Dcm_SecLevelType u1_SecLevel;

    u1_RetVal = E_NOT_OK;
    u1_SecLevel = DCM_SEC_LEV_LOCKED;

    if( ptSecurity != NULL_PTR )
    {
        (void)Dcm_GetSecurityLevel(&u1_SecLevel);       /* no return check required */

        for( u1_SecSrchCnt = (uint8)0; u1_SecSrchCnt < u1SecurityLevelNum; u1_SecSrchCnt++ )
        {
            if( u1_SecLevel == ptSecurity[u1_SecSrchCnt] )
            {
                u1_RetVal = E_OK;

                break;
            }
            else
            {
                /* No process */
            }
        }
    }
    else
    {
        u1_RetVal = E_OK;
    }
    return u1_RetVal;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
