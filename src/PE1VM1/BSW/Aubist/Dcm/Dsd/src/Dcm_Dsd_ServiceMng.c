/* Dcm_Dsd_ServiceMng_c(v5-3-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsd_ServiceMng/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include "../../Dsd/inc/Dcm_Dsd_ServiceMng.h"
#include "../../Dsd/inc/Dcm_Dsd_Main.h"
#include "../../Dsd/inc/Dcm_Dsd_MsgChk.h"
#include <Dcm/Dcm_Dsd_SendMng.h>
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Dsp_Main.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSD_RESP_OFFSET      ((uint8)0x40U)    /* ID offset of the response message */
#define DCM_DSD_NEXT_POS_SID     ((uint8)0x01U)    /* The next position of SID          */
#define DCM_DSD_NEXT_POS_SUBFUNC ((uint8)0x02U)    /* The next position of SubFunction  */
#define DCM_DSD_KEEPALIVE_LEN    ((uint8)0x02U)    /* Length of Keep-Alive message      */
#define DCM_DSD_KEEPALIVE_SID    ((uint8)0x3EU)    /* SID value of Keep-Alive message   */
#define DCM_DSD_KEEPALIVE_SF     ((uint8)0x80U)    /* SF value of Keep-Alive message    */
#define DCM_DSD_INVALIDSID       ((uint8)0x00U)    /* Invalid SID value                 */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(void, DCM_CODE) Dcm_Dsd_ServiceMng_InitMsgCntxt
(
    const PduIdType u2PduId,
    const uint8  u1ReqType,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptRxInfo,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptTxInfo
);
static FUNC(void, DCM_CODE) Dcm_Dsd_ServiceMng_ExecService
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    P2CONST(AB_83_ConstV Dcm_Dsd_ServiceType, AUTOMATIC, DCM_APPL_CONST) ptService
);
static FUNC(void, DCM_CODE) Dcm_Dsd_ServiceMng_ExecSubService
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    P2CONST(AB_83_ConstV Dcm_Dsd_ServiceType, AUTOMATIC, DCM_APPL_CONST) ptService
);
static FUNC(uint8, DCM_CODE) Dcm_Dsd_ServiceMng_GetSvTbIdx
(
    const PduIdType u2PduId
);
static FUNC(void, DCM_CODE) Dcm_Dsd_ServiceMng_ClrMsgCntxt
(void);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/* The domain that holds SID during service practice */
static VAR(uint8, DCM_VAR_NO_INIT) Dcm_Dsd_u1SID;
/* Function pointer of the implement service/subfunction */
static VAR(Dcm_Dsd_ServiceFuncType, DCM_VAR_NO_INIT) Dcm_Dsd_ptServiceFunc;
/* Transmit and receive management area */
static VAR(Dcm_MsgContextType, DCM_VAR_NO_INIT) Dcm_Dsd_stMsgContext;
/* Size of SID and the subfunction plant area of acknowledgement data */
static VAR(uint8, DCM_VAR_NO_INIT) Dcm_Dsd_u1PosRspOffsetLen;

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
/* Function Name | Dcm_Dsd_ServiceMng_Init                                  */
/* Description   | This function initializes Dsd_ServiceMng.                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsd_ServiceMng_Init
(void)
{

    Dcm_Dsd_u1SID = (uint8)0U;
    Dcm_Dsd_ServiceMng_ClrRunning();

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsd_DataIndicationFunctionality                      */
/* Description   | This function notifies you of the reception of           */
/*               | the message.                                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptDataIndInfo : Datas for Searching ServiceTable    */
/*               | [in/out] ptRxInfo : DCM reception buffer                 */
/*               | [in/out] ptTxInfo : DCM sending buffer                   */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsd_DataIndicationFunctionality
(
    P2CONST(Dcm_Dsd_DataIndicationType, AUTOMATIC, DCM_APPL_DATA) ptDataIndInfo,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptRxInfo,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptTxInfo
)
{
    Std_ReturnType u1_Result;
    boolean b_ExistSubfunction;
    uint8 u1_ServiceTableIdx;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pt_MsgContext;
    Dcm_Dsd_ServiceCheckType st_ServiceInfo;
    P2CONST(AB_83_ConstV Dcm_Dsd_ServiceTableType, AUTOMATIC, DCM_APPL_CONST) pt_ServiceTable;

    u1_ErrorCode = DCM_DSD_NRC_INVALID;
    b_ExistSubfunction = (boolean)FALSE;

    Dcm_Dsd_ServiceMng_InitMsgCntxt(ptDataIndInfo->u2PduId, ptDataIndInfo->u1ReqType, ptRxInfo, ptTxInfo);
    pt_MsgContext = &Dcm_Dsd_stMsgContext;
    Dcm_Dsd_SendMng_ClrStoredData();

    pt_MsgContext->idContext = pt_MsgContext->reqData[0];
    Dcm_Dsd_ServiceMng_SetSID(pt_MsgContext->reqData[0]);

    u1_Result = Dcm_Dsd_MsgChk_ReqVerify(pt_MsgContext->reqData[0], pt_MsgContext, (DCM_DSD_REQVFY_CHKMANUFACTURER | DCM_DSD_REQVFY_CHKSERVICE), &u1_ErrorCode);
    if( u1_Result == (Std_ReturnType)E_OK )
    {
        /* Get Service Addr */
        u1_ServiceTableIdx = Dcm_Dsd_ServiceMng_GetSvTbIdx(ptDataIndInfo->u2PduId);
        pt_ServiceTable = &Dcm_Dsd_stConfigSet.stServiceTable[u1_ServiceTableIdx];

        st_ServiceInfo.ptServiceTable = pt_ServiceTable;
        st_ServiceInfo.ptService = NULL_PTR;

        u1_ErrorCode = DCM_DSD_NRC_INVALID;
        u1_Result = Dcm_Dsd_MsgChk_ChkSID(pt_MsgContext, &st_ServiceInfo, &b_ExistSubfunction, &u1_ErrorCode);
        if( u1_Result == (Std_ReturnType)E_OK )
        {
            u1_ErrorCode = DCM_DSD_NRC_INVALID;
            u1_Result = Dcm_Dsd_MsgChk_ReqVerify(pt_MsgContext->reqData[0], pt_MsgContext, (DCM_DSD_REQVFY_CHKSUPPLIER | DCM_DSD_REQVFY_CHKSERVICE), &u1_ErrorCode);
            if( u1_Result == (Std_ReturnType)E_OK )
            {
                if( b_ExistSubfunction == (boolean)FALSE )
                {
                    Dcm_Dsd_ServiceMng_ExecService(pt_MsgContext, st_ServiceInfo.ptService);
                }
                else
                {
                    Dcm_Dsd_ServiceMng_ExecSubService(pt_MsgContext, st_ServiceInfo.ptService);
                }
            }
            else if( u1_Result == (Std_ReturnType)E_NOT_OK )
            {
                Dcm_Dsp_NotifiedWrongReq(pt_MsgContext->reqData[0], u1_ErrorCode);
                Dcm_ExternalSetNegResponse(pt_MsgContext, u1_ErrorCode);
                Dcm_ExternalProcessingDone(pt_MsgContext);
            }
            else
            {
                Dcm_Dsp_NotifiedWrongReq(pt_MsgContext->reqData[0], DCM_DSD_NRC_INVALID);
                Dcm_Dsd_SendMng_SendNoResNeg(pt_MsgContext);
            }
        }
        else
        {
            if( u1_ErrorCode == (Dcm_NegativeResponseCodeType)DCM_E_SERVICENOTSUPPORTED )
            {
                Dcm_Dsp_NotifiedWrongReq(DCM_DSD_INVALIDSID, u1_ErrorCode);
            }
            else
            {
                Dcm_Dsp_NotifiedWrongReq(pt_MsgContext->reqData[0], u1_ErrorCode);
            }
            Dcm_ExternalSetNegResponse(pt_MsgContext, u1_ErrorCode);
            Dcm_ExternalProcessingDone(pt_MsgContext);
        }
    }
    else if( u1_Result == (Std_ReturnType)E_NOT_OK )
    {
        Dcm_Dsp_NotifiedWrongReq(DCM_DSD_INVALIDSID, u1_ErrorCode);
        Dcm_ExternalSetNegResponse(pt_MsgContext, u1_ErrorCode);
        Dcm_ExternalProcessingDone(pt_MsgContext);
    }
    else
    {
        Dcm_Dsp_NotifiedWrongReq(DCM_DSD_INVALIDSID, DCM_DSD_NRC_INVALID);
        Dcm_Dsd_SendMng_SendNoResNeg(pt_MsgContext);
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsd_CancelService                                    */
/* Description   | This function cancels service.                           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsd_CancelService
(void)
{
    if( Dcm_Dsd_ptServiceFunc != NULL_PTR )
    {
        Dcm_Dsd_ServiceMng_ClrMsgCntxt();
#ifndef JGXSTACK
        (void)Dcm_Dsd_ptServiceFunc(DCM_CANCEL, (const Dcm_MsgContextType *)&Dcm_Dsd_stMsgContext);     /* no return check required */
#else /* JGXSTACK */
        (void)Dcm_Stack_CancelServiceFunc(DCM_CANCEL, (const Dcm_MsgContextType *)&Dcm_Dsd_stMsgContext);/* no return check required */                                                            /* no return check required */
#endif /* JGXSTACK */
    }
    else
    {
        /* No process */
    }

    Dcm_Dsd_SendMng_ClrStoredData();
    Dcm_Dsd_ServiceMng_ClrRunning();

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsd_ServiceMng_GetMsgCntxt                           */
/* Description   | This function gets a transmit and receive management     */
/*               | address.                                                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dcm_MsgContextType *                                     */
/*               |        DataPointer : Transmit and receive management     */
/*               |                      address                             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC_P2VAR(Dcm_MsgContextType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsd_ServiceMng_GetMsgCntxt
(void)
{
    return &Dcm_Dsd_stMsgContext;
}


/****************************************************************************/
/* Function Name | Dcm_Dsd_ServiceMng_SetSID                                */
/* Description   | This function sets ServiceID.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1SID : ServiceID                                   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsd_ServiceMng_SetSID
(
    const uint8 u1SID
)
{
    Dcm_Dsd_u1SID = u1SID;
    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsd_GetSID                                           */
/* Description   | This function gets ServiceID.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | uint8                                                    */
/*               |        0x00U-0xFFU : ServiceID                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint8, DCM_CODE) Dcm_Dsd_GetSID
(void)
{
    return Dcm_Dsd_u1SID;
}


/****************************************************************************/
/* Function Name | Dcm_Dsd_GetDirectSID                                     */
/* Description   | This function gets ServiceID.                            */
/* Preconditions | ptRxBuff != NULL_PTR                                     */
/* Parameters    | [in] ptRxBuff    : DCM reception buffer                  */
/*               |                                                          */
/* Return Value  | uint8                                                    */
/*               |        0x00U-0xFFU : ServiceID                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint8, DCM_CODE) Dcm_Dsd_GetDirectSID
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA ) ptRxBuff
)
{
    uint8 u1_Sid;

    u1_Sid = ptRxBuff[0];

    return u1_Sid;
}


/****************************************************************************/
/* Function Name | Dcm_Dsd_ServiceMng_IsRunning                             */
/* Description   | This function judges the running state of                */
/*               | the service / subfunction.                               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        True :  Under service execution                   */
/*               |        False : Service non-execution                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_Dsd_ServiceMng_IsRunning
(void)
{
    boolean b_Result;

    b_Result = (boolean)FALSE;

    if( Dcm_Dsd_ptServiceFunc != NULL_PTR )
    {
        b_Result = (boolean)TRUE;
    }
    else
    {
        /* No process */
    }

    return b_Result;
}


/****************************************************************************/
/* Function Name | Dcm_Dsd_ServiceMng_ClrRunning                            */
/* Description   | This function clears the running state of the service.   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsd_ServiceMng_ClrRunning
(void)
{
    Dcm_Dsd_ptServiceFunc = NULL_PTR;
    Dcm_Dsd_u1PosRspOffsetLen = (uint8)0U;

    Dcm_Dsd_ServiceMng_ClrMsgCntxt();

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsd_ServiceMng_GetOffsetLen                          */
/* Description   | This function acquires the offset head (plant region     */
/*               | size of the SID/ subfunction) of the response message.   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | uint8                                                    */
/*               |        0x00U-0x02U : Offset Length                       */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(uint8, DCM_CODE) Dcm_Dsd_ServiceMng_GetOffsetLen
(void)
{
    return Dcm_Dsd_u1PosRspOffsetLen;
}

/****************************************************************************/
/* Function Name | Dcm_Dsd_ServiceMng_ExecForceRP                           */
/* Description   | This function notifies the DSP of the response of        */
/*               | service re-notification NRC 0x78 upon completion of      */
/*               | forced response pending.                                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsd_ServiceMng_ExecForceRP
(void)
{
    if( Dcm_Dsd_ptServiceFunc != NULL_PTR )
    {
#ifndef JGXSTACK
        (void)Dcm_Dsd_ptServiceFunc(DCM_FORCE_RCRRP_OK, (const Dcm_MsgContextType *)&Dcm_Dsd_stMsgContext);     /* no return check required */
#else /* JGXSTACK */
        (void)Dcm_Stack_ForceRCRRPServiceFunc(DCM_FORCE_RCRRP_OK, (const Dcm_MsgContextType *)&Dcm_Dsd_stMsgContext);/* no return check required */
#endif /* JGXSTACK */
    }
    else
    {
        /* No process */
    }
    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsd_isKeepAliveMsg                                   */
/* Description   | This function checks reception Message is Keep-Alive     */
/*               | Message or not                                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1ReqType    : Request address type                 */
/*               | [in] ptRxInfo     : DCM reception buffer                 */
/* Return Value  | boolean                                                  */
/*               |        TRUE       : Keep-Alive Message                   */
/*               |        FALSE      : not Keep-Alive Message               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsd_isKeepAliveMsg
(
    const uint8 u1ReqType,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptRxInfo
)
{
    boolean b_Result;

    b_Result = (boolean)FALSE;
    if( u1ReqType == DCM_DSL_ADDINFO_FUNC )
    {
        if( ptRxInfo->SduLength == DCM_DSD_KEEPALIVE_LEN )
        {
            if( ptRxInfo->SduDataPtr[DCM_DSD_RX_SID_OFFSET] == DCM_DSD_KEEPALIVE_SID )
            {
                if( ptRxInfo->SduDataPtr[DCM_DSD_RX_SF_OFFSET] == DCM_DSD_KEEPALIVE_SF )
                {
                    b_Result = (boolean)TRUE;
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
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }

    return b_Result;

}

#if ( ( DCM_SUPPORT_SID28 == STD_ON ) || ( DCM_SUPPORT_SID85 == STD_ON ) || ( DCM_PERIODIC_SEND_USE == STD_ON ) )
/****************************************************************************/
/* Function Name | Dcm_Dsd_ChkServiceSupported                              */
/* Description   | This function checks specified Service is supported in   */
/*               | configulation which determined by PduID and Session type */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1Sid         : Service ID                          */
/*               | [in] u2RxPduId     : Rx PDU ID                           */
/*               | [in] u1SesCtrlType : Session type                        */
/* Return Value  | boolean                                                  */
/*               |        E_OK        : Service is supported                */
/*               |        E_NOT_OK    : Service is not supported            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_ChkServiceSupported
(
    const uint8 u1Sid,
    const PduIdType u2RxPduId,
    const Dcm_SesCtrlType u1SesCtrlType
)
{
    P2CONST(AB_83_ConstV uint16, AUTOMATIC, DCM_APPL_CONST) pt_SvcIdxTable;
    uint8 u1_ServiceTableIdx;
    uint8 u1_SvcNum;
    uint8 u1_SvcCnt;
    uint8 u1_SesCnt;
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;

    u1_ServiceTableIdx = Dcm_Dsd_ServiceMng_GetSvTbIdx(u2RxPduId);
    u1_SvcNum = Dcm_Dsd_stConfigSet.stServiceTable[u1_ServiceTableIdx].u1ServiceNum;
    pt_SvcIdxTable = Dcm_Dsd_stConfigSet.stServiceTable[u1_ServiceTableIdx].ptServiceIdx;

    for( u1_SvcCnt = (uint8)0U; u1_SvcCnt < u1_SvcNum; u1_SvcCnt++ )
    {
        if( Dcm_Dsd_stService[pt_SvcIdxTable[u1_SvcCnt]].u1Id != u1Sid )
        {
             /* No process */
        }
        else
        {
            if( Dcm_Dsd_stService[pt_SvcIdxTable[u1_SvcCnt]].ptSessionLevelRef != NULL_PTR )
            {
                for( u1_SesCnt = (uint8)0U; u1_SesCnt < Dcm_Dsd_stService[pt_SvcIdxTable[u1_SvcCnt]].u1SessionLevelNum; u1_SesCnt++ )
                {
                    if( Dcm_Dsd_stService[pt_SvcIdxTable[u1_SvcCnt]].ptSessionLevelRef[u1_SesCnt] != u1SesCtrlType )
                    {
                        /* No process */
                    }
                    else
                    {
                        u1_RetVal = E_OK;
                        break;
                    }
                }
            }
            else
            {
                u1_RetVal = E_OK;
            }
            break;
        }
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID28 == STD_ON || DCM_SUPPORT_SID85 == STD_ON || DCM_PERIODIC_SEND_USE == STD_ON */


#if ( DCM_SID86_ROE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsd_ChkRoeServiceSupported                           */
/* Description   | This function checks specified Service is supported in   */
/*               | configulation which determined by PduID and Session type */
/*               | for ROE ServiceToRespondToRecord Data                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1Sid         : Service ID                          */
/* Parameters    | [in] u1Para1       : Service Parameter1                  */
/*               | [in] u2RxPduId     : Rx PDU ID                           */
/* Return Value  | boolean                                                  */
/*               |        E_OK        : Service is supported                */
/*               |        E_NOT_OK    : Service is not supported            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_ChkRoeServiceSupported
(
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA )  ptServToResp,
    const   uint32                              u4ServToRespToRecLen,
    const   PduIdType                           u2RxPduId
)
{
    Dcm_Dsd_ServiceCheckType    st_ServiceInfo;
    Dcm_Dsd_SubServiceCheckType st_SubServiceInfo;
    Std_ReturnType              u1_RetVal;
    Std_ReturnType              u1_ChkSesSid;
    Std_ReturnType              u1_ChkSesSubFunc;
    uint8                       u1_ServiceTableIdx;
    boolean                     b_SubFunc;

    u1_RetVal           = (Std_ReturnType)E_NOT_OK;
    u1_ChkSesSubFunc    = (Std_ReturnType)E_NOT_OK;
    b_SubFunc           = (boolean)FALSE;

    u1_ServiceTableIdx  = Dcm_Dsd_ServiceMng_GetSvTbIdx( u2RxPduId );
    st_ServiceInfo.ptServiceTable   = &Dcm_Dsd_stConfigSet.stServiceTable[u1_ServiceTableIdx];
    st_ServiceInfo.ptService        = NULL_PTR;

    /* Check ServiceId Process Block */
    u1_ChkSesSid = Dcm_Dsd_MsgChk_ChkRoeSrvSupSid( ptServToResp, u4ServToRespToRecLen, &st_ServiceInfo, &b_SubFunc );

    if( u1_ChkSesSid == (Std_ReturnType)E_OK )
    {
        /* The Session Check of Target SID is OK */
        if( b_SubFunc == (boolean)TRUE )
        {
            st_SubServiceInfo.ptService     = st_ServiceInfo.ptService;
            st_SubServiceInfo.ptSubService  = NULL_PTR;
            u1_ChkSesSubFunc    = Dcm_Dsd_MsgChk_ChkRoeSrvSupSubFunc( ptServToResp, u4ServToRespToRecLen, &st_SubServiceInfo);
        }
        else
        {
            u1_ChkSesSubFunc    = (Std_ReturnType)E_OK;
        }
    }
    
    if( u1_ChkSesSubFunc == (Std_ReturnType)E_OK )
    {
        u1_RetVal               = (Std_ReturnType)E_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_SID86_ROE_USE == STD_ON */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsd_ServiceMng_InitMsgCntxt                          */
/* Description   | This function sets designation parameter in              */
/*               | the transmit and receive management area.                */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduId   : Reception PduId                         */
/*               | [in] u1ReqType : Request address type                    */
/*               | [in] ptRxInfo  : DCM reception buffer                    */
/*               | [in] ptTxInfo  : DCM sending buffer                      */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsd_ServiceMng_InitMsgCntxt
(
    const PduIdType u2PduId,
    const uint8 u1ReqType,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptRxInfo,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptTxInfo
)
{
    Dcm_Dsd_stMsgContext.reqData = ptRxInfo->SduDataPtr;
    Dcm_Dsd_stMsgContext.reqDataLen = ptRxInfo->SduLength;
    Dcm_Dsd_stMsgContext.resData = ptTxInfo->SduDataPtr;
    Dcm_Dsd_stMsgContext.resDataLen = (uint32)0U;
    Dcm_Dsd_stMsgContext.msgAddInfo.reqType = u1ReqType;
    Dcm_Dsd_stMsgContext.msgAddInfo.suppressPosResponse = STD_OFF;
    Dcm_Dsd_stMsgContext.resMaxDataLen = ptTxInfo->SduLength;
    Dcm_Dsd_stMsgContext.idContext = (uint8)0U;
    Dcm_Dsd_stMsgContext.dcmRxPduId = u2PduId;

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsd_ServiceMng_ExecService                           */
/* Description   | This function will put service into practice.            */
/* Preconditions | none                                                     */
/* Parameters    | [in/out] ptMsgContext : Transmit and receive management  */
/*               |                         address                          */
/*               | [in] ptService : Address to service item of config       */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsd_ServiceMng_ExecService
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    P2CONST(AB_83_ConstV Dcm_Dsd_ServiceType, AUTOMATIC, DCM_APPL_CONST) ptService
)
{
    ptMsgContext->resData[0] = (ptMsgContext->reqData[0] | DCM_DSD_RESP_OFFSET);

    ptMsgContext->reqData = &ptMsgContext->reqData[DCM_DSD_NEXT_POS_SID];
    ptMsgContext->reqDataLen--; /* no wrap around */

    ptMsgContext->resData = &ptMsgContext->resData[DCM_DSD_NEXT_POS_SID];
    ptMsgContext->resMaxDataLen -= DCM_DSD_NEXT_POS_SID;    /* no wrap around */
    Dcm_Dsd_u1PosRspOffsetLen = DCM_DSD_NEXT_POS_SID;

    if( ptService->ptFnc != NULL_PTR )
    {
        Dcm_Dsd_ptServiceFunc = ptService->ptFnc;
#if ( DCM_PAGEDBUFFER_ENABLED == STD_ON )
        Dcm_Dsp_ServiceInit();
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */
#ifndef JGXSTACK
        (void)Dcm_Dsd_ptServiceFunc(DCM_INITIAL, (const Dcm_MsgContextType *)ptMsgContext);     /* no return check required */
#else /* JGXSTACK */
        (void)Dcm_Stack_InitialServiceFunc(DCM_INITIAL, (const Dcm_MsgContextType *)ptMsgContext);/* no return check required */
#endif /* JGXSTACK */
    }
    else
    {
        Dcm_Dsd_SendMng_SendNoResNeg(ptMsgContext);
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsd_ServiceMng_ExecSubService                        */
/* Description   | This function will put a subfunction into practice.      */
/* Preconditions | none                                                     */
/* Parameters    | [in/out] ptMsgContext : Transmit and receive management  */
/*               |                         address                          */
/*               | [in] ptService : Address to service item of config       */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsd_ServiceMng_ExecSubService
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    P2CONST(AB_83_ConstV Dcm_Dsd_ServiceType, AUTOMATIC, DCM_APPL_CONST) ptService
)
{
    Std_ReturnType u1_Result;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    Dcm_Dsd_SubServiceCheckType  st_SubServiceInfo;

    u1_ErrorCode = DCM_DSD_NRC_INVALID;
    st_SubServiceInfo.ptService = ptService;
    st_SubServiceInfo.ptSubService = NULL_PTR;

    u1_Result = Dcm_Dsd_MsgChk_ChkSubfunction(ptMsgContext, &st_SubServiceInfo, &u1_ErrorCode);
    if( u1_Result == (Std_ReturnType)E_OK )
    {
        ptMsgContext->resData[0] = (ptMsgContext->reqData[0] | DCM_DSD_RESP_OFFSET);

        ptMsgContext->reqData = &ptMsgContext->reqData[DCM_DSD_NEXT_POS_SID];
        ptMsgContext->reqDataLen--; /* no wrap around */

        u1_ErrorCode = DCM_DSD_NRC_INVALID;
        u1_Result = Dcm_Dsd_MsgChk_ReqVerify(Dcm_Dsd_u1SID, ptMsgContext, (DCM_DSD_REQVFY_CHKMANUFACTURER | DCM_DSD_REQVFY_CHKSUBFUNCTION), &u1_ErrorCode);
        if( u1_Result == (Std_ReturnType)E_OK )
        {
            u1_ErrorCode = DCM_DSD_NRC_INVALID;
            u1_Result = Dcm_Dsd_MsgChk_ReqVerify(Dcm_Dsd_u1SID, ptMsgContext, (DCM_DSD_REQVFY_CHKSUPPLIER | DCM_DSD_REQVFY_CHKSUBFUNCTION), &u1_ErrorCode);
            if( u1_Result == (Std_ReturnType)E_OK )
            {

                ptMsgContext->msgAddInfo.suppressPosResponse = STD_OFF;
                if( (ptMsgContext->reqData[0] & DCM_DSD_SUPPRESS_BIT) == DCM_DSD_SUPPRESS_BIT )
                {
                    ptMsgContext->msgAddInfo.suppressPosResponse = STD_ON;
                }
                ptMsgContext->reqData[0] &= DCM_DSD_SUPPRESS_BITMASK;

                ptMsgContext->resData[DCM_DSD_NEXT_POS_SID] = ptMsgContext->reqData[0];

                ptMsgContext->reqData = &ptMsgContext->reqData[DCM_DSD_NEXT_POS_SID];
                ptMsgContext->reqDataLen--; /* no wrap around */

                ptMsgContext->resData = &ptMsgContext->resData[DCM_DSD_NEXT_POS_SUBFUNC];
                ptMsgContext->resMaxDataLen -= DCM_DSD_NEXT_POS_SUBFUNC;    /* no wrap around */
                Dcm_Dsd_u1PosRspOffsetLen = DCM_DSD_NEXT_POS_SUBFUNC;

                /* ptFnc is always valid, so NULL check is not performed */
                Dcm_Dsd_ptServiceFunc = st_SubServiceInfo.ptSubService->ptFnc;
#if ( DCM_PAGEDBUFFER_ENABLED == STD_ON )
                Dcm_Dsp_ServiceInit();
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */
#ifndef JGXSTACK
                (void)Dcm_Dsd_ptServiceFunc(DCM_INITIAL, (const Dcm_MsgContextType *)ptMsgContext);     /* no return check required */
#else /* JGXSTACK */
                (void)Dcm_Stack_InitialSubServiceFunc(DCM_INITIAL, (const Dcm_MsgContextType *)ptMsgContext);/* no return check required */
#endif /* JGXSTACK */
            }
            else if( u1_Result == (Std_ReturnType)E_NOT_OK )
            {
                Dcm_Dsp_NotifiedWrongReq(Dcm_Dsd_u1SID, u1_ErrorCode);
                Dcm_ExternalSetNegResponse(ptMsgContext, u1_ErrorCode);
                Dcm_ExternalProcessingDone(ptMsgContext);
            }
            else
            {
                Dcm_Dsp_NotifiedWrongReq(Dcm_Dsd_u1SID, DCM_DSD_NRC_INVALID);
                Dcm_Dsd_SendMng_SendNoResNeg(ptMsgContext);
            }
        }
        else if( u1_Result == (Std_ReturnType)E_NOT_OK )
        {
            Dcm_Dsp_NotifiedWrongReq(Dcm_Dsd_u1SID, u1_ErrorCode);
            Dcm_ExternalSetNegResponse(ptMsgContext, u1_ErrorCode);
            Dcm_ExternalProcessingDone(ptMsgContext);
        }
        else
        {
            Dcm_Dsp_NotifiedWrongReq(Dcm_Dsd_u1SID, DCM_DSD_NRC_INVALID);
            Dcm_Dsd_SendMng_SendNoResNeg(ptMsgContext);
        }
    }
    else
    {
        Dcm_Dsp_NotifiedWrongReq(ptMsgContext->reqData[0], u1_ErrorCode);
        Dcm_ExternalSetNegResponse(ptMsgContext, u1_ErrorCode);
        Dcm_ExternalProcessingDone(ptMsgContext);
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsd_ServiceMng_GetSvTbIdx                            */
/* Description   | This function acquires an index of container             */
/*               | DcmDsdServiceTable.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduId      : RX PDU ID                            */
/*               |                                                          */
/* Return Value  | uint8                                                    */
/*               |       0x00U-DCM_D_SERVICETABLE_NUM : Index of DcmDsdSe-  */
/*               |       rviceTable                                         */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(uint8, DCM_CODE) Dcm_Dsd_ServiceMng_GetSvTbIdx
(
    const PduIdType u2PduId
)
{
    uint8 u1_Result;
    uint8 u1_Cnt;
    uint8 u1_ServiceTableNum;

    u1_Result = (uint8)0U;
    u1_ServiceTableNum = Dcm_Dsd_u1Servicetable_Num;

    for( u1_Cnt = (uint8)0U; u1_Cnt < u1_ServiceTableNum; u1_Cnt++ )     /* MISRA DEVIATION */
    {
        if( Dcm_Dsd_stConfigSet.stServiceTable[u1_Cnt].u2Id == u2PduId )
        {
            u1_Result = u1_Cnt;
            break;
        }
        else
        {
            /* No process */
        }
    }
    return u1_Result;
}


/****************************************************************************/
/* Function Name | Dcm_Dsd_ServiceMng_ClrMsgCntxt                           */
/* Description   | This function acquires an index of container             */
/*               | DcmDsdServiceTable.                                      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | uint8                                                    */
/*               |       0x00U-DCM_D_SERVICETABLE_NUM : Index of DcmDsdSe-  */
/*               |       rviceTable                                         */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsd_ServiceMng_ClrMsgCntxt
(void)
{
    Dcm_Dsd_stMsgContext.reqData = NULL_PTR;
    Dcm_Dsd_stMsgContext.reqDataLen = (uint32)0U;
    Dcm_Dsd_stMsgContext.resData = NULL_PTR;
    Dcm_Dsd_stMsgContext.resDataLen = (uint32)0U;
    Dcm_Dsd_stMsgContext.msgAddInfo.reqType = (uint8)0U;
    Dcm_Dsd_stMsgContext.msgAddInfo.suppressPosResponse = STD_OFF;
    Dcm_Dsd_stMsgContext.resMaxDataLen = (uint32)0U;
    Dcm_Dsd_stMsgContext.idContext = (uint8)0U;
    Dcm_Dsd_stMsgContext.dcmRxPduId = (uint16)0U;

    return ;

}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-2-0         :2019-01-29                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
