/* Dcm_Dsd_SendMng_c(v5-10-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsd_SendMng/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsd/inc/Dcm_Dsd_Main.h"
#include <Dcm/Dcm_Dsd_SendMng.h>
#include "../../Dsd/inc/Dcm_Dsd_ServiceMng.h"
#include <Dcm/Dcm_Dsd_Main_Callout.h>
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm/Dcm_Main_EvtDistr.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
#define DCM_DSD_PAGEDBUFFER_MSGMAXLEN       ((Dcm_MsgLenType)0xFFFFFFFFUL)
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */
#define DCM_DSD_OBD_SID_MAX                             ((uint8)0x0FU)
#if ( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
#define DCM_DSD_DIAGNOSTICSESSIONCONTROL                ((uint8)0x10U)
#define DCM_DSD_ECURESET                                ((uint8)0x11U)
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
static FUNC(void, DCM_CODE) Dcm_Dsd_SendMng_SendResponse
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);

static FUNC(boolean, DCM_CODE) Dcm_Dsd_SendMng_IsSuppressNegInSpecific
(
    const uint8 u1SID,
    const Dcm_NegativeResponseCodeType u1Nrc,
    const uint16 u2ConnectionId
);

static FUNC(boolean, DCM_CODE) Dcm_Dsd_SendMng_IsSuppressNegResInFuncAddr
(void);

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
static FUNC(Dcm_Dsl_ResponseSettingType, DCM_CODE) Dcm_Dsd_SendMng_GetPositiveResponseKind
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR(Dcm_NegativeResponseCodeType, DCM_VAR_NO_INIT) Dcm_Dsd_u1ErrorCode;

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
static VAR(boolean, DCM_VAR_NO_INIT) Dcm_Dsd_bUpdatePageFlag;
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

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
/* Function Name | Dcm_ExternalSetNegResponse                               */
/* Description   | This function transmits the Negative Response Code to    */
/*               | DSL as a final response.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptMsgContext : pointer to the message context       */
/*               |        -                                                 */
/*               | [in] ErrorCode : Negative Response Code                  */
/*               |                                                          */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_ExternalSetNegResponse
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,    /* MISRA DEVIATION */
    Dcm_NegativeResponseCodeType ErrorCode
)
{
    uint8 u1_SID;

    u1_SID = Dcm_Dsd_GetSID();

    if( ErrorCode == DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING )
    {
        Dcm_Dsl_SendForcePendingResponse(u1_SID);
    }
    else
    {
        Dcm_Dsd_u1ErrorCode = ErrorCode;

        Dcm_Dsl_WriteNRCData(u1_SID, Dcm_Dsd_u1ErrorCode);
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_ExternalProcessingDone                               */
/* Description   | This function transmits the positive response, negative  */
/*               | response, or no response to DSL as a final response.     */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptMsgContext : pointer to the message context       */
/*               |        -                                                 */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_ExternalProcessingDone
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext     /* MISRA DEVIATION */
)
{
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pt_DsdMsgContext;

    pt_DsdMsgContext = Dcm_Dsd_ServiceMng_GetMsgCntxt();

    pt_DsdMsgContext->reqDataLen = pMsgContext->reqDataLen;
    pt_DsdMsgContext->resDataLen = pMsgContext->resDataLen + Dcm_Dsd_ServiceMng_GetOffsetLen(); /* no wrap around */
    pt_DsdMsgContext->msgAddInfo = pMsgContext->msgAddInfo;
    pt_DsdMsgContext->idContext = pMsgContext->idContext;
    pt_DsdMsgContext->dcmRxPduId = pMsgContext->dcmRxPduId;

    Dcm_Dsd_SendMng_SendResponse(pt_DsdMsgContext);

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsd_SendMng_Init                                     */
/* Description   | This function provides the service of setting the NRC in */
/*               | DSD module to the initial number.                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsd_SendMng_Init
(void)
{
    Dcm_Dsd_SendMng_ClrStoredData();

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsd_DataConfirmationFunctionality                    */
/* Description   | This function conducts a process of diciding whether to  */
/*               | transmit a response confirmation message to DSP or not.  */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1ConfirmationStatus : indicates the response       */
/*               |  transmission process has finished successfully or not   */
/*               |                                                          */
/*               | [in] bIsSendForcedPending : indicates whether this       */
/*               | function is call for NRC0x78 or not                      */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : this value is always returned.             */
/*               |        E_NOT_OK :                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_DataConfirmationFunctionality
(
    const Dcm_ConfirmationStatusType u1ConfirmationStatus,
    const boolean bIsSendForcedPending
)
{
    P2CONST(AB_83_ConstV Dcm_Dsd_ConfirmationFuncType, AUTOMATIC, DCM_APPL_CONST) pt_MfrConfNotify;
    P2CONST(AB_83_ConstV Dcm_Dsd_ConfirmationFuncType, AUTOMATIC, DCM_APPL_CONST) pt_SplrConfNotify;
    Std_ReturnType u1_RetVal;
    uint8 u1_SID;
    uint8 u1_MfrConfCnt;
    uint8 u1_SplrConfCnt;
    uint8 u1_MfrConfNum;
    uint8 u1_SplrConfNum;
    boolean b_SIDRunning;
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pt_MsgContext;
    Dcm_ProtocolType u1_ActiveProtocolType;
    uint16 u2_ConnectionId;
    uint16 u2_TesterSourceAddress;

    u1_ActiveProtocolType   = DCM_NO_ACTIVE_PROTOCOL;
    u2_ConnectionId         = DCM_DSD_CONID_INVALID;
    u2_TesterSourceAddress  = DCM_DSD_TESTER_INVALID;
    u1_RetVal = E_OK;

    (void)Dcm_GetActiveProtocol( &u1_ActiveProtocolType, &u2_ConnectionId, &u2_TesterSourceAddress ); /* no return check required */

    if( bIsSendForcedPending == (boolean)FALSE )
    {
        pt_MsgContext = Dcm_Dsd_ServiceMng_GetMsgCntxt();

        b_SIDRunning = Dcm_Dsd_ServiceMng_IsRunning();
        if( b_SIDRunning == (boolean)TRUE )
        {
            DspInternal_DcmConfirmation(pt_MsgContext->idContext, u2_ConnectionId, u1ConfirmationStatus);
        }
        else
        {
            /* No process */
        }

        u1_SID = Dcm_Dsd_GetSID();

        if( Dcm_Dsd_stConfigSet.bReqMfrNotifyEnabled == (boolean)TRUE )
        {
            if( Dcm_Dsd_stConfigSet.ptMfrConfNotify != NULL_PTR )
            {
                u1_MfrConfNum = Dcm_Dsd_u1Mfrconfnotify_Num;
                pt_MfrConfNotify = Dcm_Dsd_stConfigSet.ptMfrConfNotify;
                for( u1_MfrConfCnt = (uint8)0; u1_MfrConfCnt < u1_MfrConfNum; u1_MfrConfCnt++ )     /* MISRA DEVIATION */
                {
#ifndef JGXSTACK
                    (void)pt_MfrConfNotify[u1_MfrConfCnt](u1_SID, pt_MsgContext->msgAddInfo.reqType, u2_ConnectionId, u1ConfirmationStatus, u1_ActiveProtocolType, u2_TesterSourceAddress);       /* no return check required */
#else /* JGXSTACK */
                    /* user-defined */
#endif /* JGXSTACK */
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

        if( Dcm_Dsd_stConfigSet.bReqSplrNotifyEnabled == (boolean)TRUE )
        {
            if( Dcm_Dsd_stConfigSet.ptSplrConfNotify != NULL_PTR )
            {
                u1_SplrConfNum = Dcm_Dsd_u1Splrconfnotify_Num;
                pt_SplrConfNotify = Dcm_Dsd_stConfigSet.ptSplrConfNotify;
                for( u1_SplrConfCnt = (uint8)0; u1_SplrConfCnt < u1_SplrConfNum; u1_SplrConfCnt++ )     /* MISRA DEVIATION */
                {
#ifndef JGXSTACK
                    (void)pt_SplrConfNotify[u1_SplrConfCnt](u1_SID, pt_MsgContext->msgAddInfo.reqType, u2_ConnectionId, u1ConfirmationStatus, u1_ActiveProtocolType, u2_TesterSourceAddress);     /* no return check required */
#else /* JGXSTACK */
                    /* user-defined */
#endif /* JGXSTACK */
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

        Dcm_Dsd_ServiceMng_ClrRunning();
        Dcm_Dsd_SendMng_ClrStoredData();
    }
    else
    {
        Dcm_Dsd_ServiceMng_ExecForceRP();
    }
    return u1_RetVal;
}

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsd_SendMng_ClrStoredData                            */
/* Description   | This function provides the service of setting the NRC in */
/*               | DSD module to the initial number.                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsd_SendMng_ClrStoredData
(void)
{
    Dcm_Dsd_u1ErrorCode = DCM_DSD_NRC_INVALID;

    Dcm_Dsd_bUpdatePageFlag = (boolean)TRUE;

    return;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

#if( DCM_PAGEDBUFFER_ENABLED == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsd_SendMng_ClrStoredData                            */
/* Description   | This function provides the service of setting the NRC in */
/*               | DSD module to the initial number.                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsd_SendMng_ClrStoredData
(void)
{
    Dcm_Dsd_u1ErrorCode = DCM_DSD_NRC_INVALID;

    return;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_OFF */

/****************************************************************************/
/* Function Name | Dcm_Dsd_SendMng_SendNoResNeg                             */
/* Description   | This function signals negative no response.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptMsgContext : pointer to the message context       */
/*               |                                                          */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsd_SendMng_SendNoResNeg
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    uint8 u1_SID;

    u1_SID = Dcm_Dsd_GetSID();
    /* NRC is not required for no response, but negative response data is set for data consistency. */
    Dcm_Dsl_WriteNRCData(u1_SID, DCM_E_GENERALREJECT);
    Dcm_Dsl_TransmitFunctionality(ptMsgContext, DCM_DSL_SET_NO_RESPONSE_NEG);

    return;
}

/****************************************************************************/
/* Function Name | Dcm_SendNegativeNoResponse                               */
/* Description   | This function signals negative no response.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptMsgContext : pointer to the message context       */
/*               |                                                          */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_SendNegativeNoResponse
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Dcm_Dsd_SendMng_SendNoResNeg(ptMsgContext);

    return;
}

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | DsdInternal_StartPagedProcessing                         */
/* Description   | This function starts PagedBuffer processing.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptMsgContext : pointer to the message context       */
/*               |                                                          */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) DsdInternal_StartPagedProcessing
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pt_DsdMsgContext;
    uint8                                               u1_OffsetLen;
    uint8                                               u1_ResponseKind;
    uint8                                               u1_SID;

    pt_DsdMsgContext = Dcm_Dsd_ServiceMng_GetMsgCntxt();
    u1_OffsetLen     = Dcm_Dsd_ServiceMng_GetOffsetLen();

    u1_ResponseKind = Dcm_Dsd_SendMng_GetPositiveResponseKind(pt_DsdMsgContext);
    if( u1_ResponseKind == DCM_DSL_SET_POSITIVE_RESPONSE )
    {
        if( pMsgContext->resDataLen > (DCM_DSD_PAGEDBUFFER_MSGMAXLEN - u1_OffsetLen) )
        {
            u1_SID = Dcm_Dsd_GetSID();
            Dcm_Dsp_NotifiedWrongReq(u1_SID, DCM_E_RESPONSETOOLONG);
            Dcm_Dsl_WriteNRCData(u1_SID, DCM_E_RESPONSETOOLONG);
            DspInternal_CancelPagedBufferProcessing();
            Dcm_Dsl_TransmitFunctionality(pMsgContext, DCM_DSL_SET_NEGATIVE_RESPONSE);
        }
        else
        {
            pt_DsdMsgContext->resDataLen = pMsgContext->resDataLen + u1_OffsetLen;
            Dcm_Dsd_bUpdatePageFlag      = (boolean)FALSE;
            (void)DspInternal_DcmUpdatePage(pt_DsdMsgContext->resData, DCM_DSD_UPDATEPAGE_INITIAL_ACT);    /* no return check required */
        }
    }
    else
    {
        DspInternal_CancelPagedBufferProcessing();
        Dcm_Dsl_TransmitFunctionality(pt_DsdMsgContext, DCM_DSL_SET_NO_RESPONSE_POS);
    }

    return;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | DsdInternal_ProcessPage                                  */
/* Description   | This function sends data acquired with PagedBuffer.      */
/* Preconditions | none                                                     */
/* Parameters    | [in] FilledPageLen : The length of the filled page       */
/*               |                                                          */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) DsdInternal_ProcessPage
(
    Dcm_MsgLenType FilledPageLen
)
{
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pt_DsdMsgContext;
    Dcm_MsgContextType                                  st_DsdMsgContext;

    pt_DsdMsgContext = Dcm_Dsd_ServiceMng_GetMsgCntxt();

    if( Dcm_Dsd_bUpdatePageFlag == (boolean)FALSE )
    {
        /* Set the total length of the response message in st_DsdMsgContext.resDataLen. */
        /* This value is used to transmit to Dsl. */
        st_DsdMsgContext.resDataLen   = pt_DsdMsgContext->resDataLen;

        /* The following setting is QAC warning measures. */
        st_DsdMsgContext.reqData      = pt_DsdMsgContext->reqData;
        st_DsdMsgContext.reqDataLen   = pt_DsdMsgContext->reqDataLen;
        st_DsdMsgContext.resData      = pt_DsdMsgContext->resData;
        st_DsdMsgContext.msgAddInfo   = pt_DsdMsgContext->msgAddInfo;
        st_DsdMsgContext.resMaxDataLen= pt_DsdMsgContext->resMaxDataLen;
        st_DsdMsgContext.idContext    = pt_DsdMsgContext->idContext;
        st_DsdMsgContext.dcmRxPduId   = pt_DsdMsgContext->dcmRxPduId;

        /* Set the value obtained by adding the offset length to the page length to pt_DsdMsgContext->resDataLen. */
        /* Dsl uses Dcm_Dsd_GetResponseDataLength to get this value. */
        pt_DsdMsgContext->resDataLen  = FilledPageLen + Dcm_Dsd_ServiceMng_GetOffsetLen();  /* no wrap around */

        Dcm_Dsd_bUpdatePageFlag       = (boolean)TRUE;

        Dcm_Dsl_TransmitFunctionality(&st_DsdMsgContext, DCM_DSL_SET_POSITIVE_RESPONSE);
    }
    else
    {
        pt_DsdMsgContext->resDataLen  = FilledPageLen;
        Dcm_Dsl_TransmitFunctionality(pt_DsdMsgContext, DCM_DSL_SET_POSITIVE_RESPONSE);
    }

    return ;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsd_UpdatePage                                       */
/* Description   | This function gets the next data of PagedBuffer.         */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptResData : Pointer to response data                */
/*               | [in] u4ResMaxDataLen : Response Max Data Length          */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |     E_OK : Data acquisition success                      */
/*               |     E_NOT_OK : Data acquisition failure                  */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsd_UpdatePage
(
    Dcm_MsgType     ptResData,
    Dcm_MsgLenType  u4ResMaxDataLen
)
{
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pt_DsdMsgContext;
    Std_ReturnType                                      u1_RetVal;

    pt_DsdMsgContext                = Dcm_Dsd_ServiceMng_GetMsgCntxt();
    pt_DsdMsgContext->resData       = ptResData;
    pt_DsdMsgContext->resMaxDataLen = u4ResMaxDataLen;
    pt_DsdMsgContext->resDataLen    = (Dcm_MsgLenType)0U;

    u1_RetVal = DspInternal_DcmUpdatePage(pt_DsdMsgContext->resData, pt_DsdMsgContext->resMaxDataLen);

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsd_CancelPagedBufferProcessing                      */
/* Description   | This function aborts PagedBuffer processing.             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsd_CancelPagedBufferProcessing
(void)
{
    DspInternal_CancelPagedBufferProcessing();
    Dcm_Dsd_ServiceMng_ClrRunning();
    Dcm_Dsd_SendMng_ClrStoredData();

    return;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsd_GetResponseDataLength                            */
/* Description   | This function gets Response Data Length.                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dcm_MsgLenType                                           */
/*               |   0-65535 : Response Data Length                         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Dcm_MsgLenType, DCM_CODE) Dcm_Dsd_GetResponseDataLength
(void)
{
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pt_DsdMsgContext;

    pt_DsdMsgContext = Dcm_Dsd_ServiceMng_GetMsgCntxt();

    return pt_DsdMsgContext->resDataLen;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsd_IsSuppressNegMsg                                 */
/* Description   | This function determines whether or not to suppress      */
/*               |  negative response messages derived from Dsl.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1SID          : Service ID                         */
/* Parameters    | [in] u1Nrc          : Nrc                                */
/*               | [in] u2ConnectionId : Connection ID                      */
/* Return Value  | boolean                                                  */
/*               |    TRUE :  Suppresses response messages                  */
/*               |    FALSE:  Other                                         */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_Dsd_IsSuppressNegMsg
(
    const uint8 u1SID,
    const Dcm_NegativeResponseCodeType u1Nrc,
    const uint16 u2ConnectionId
)
{
    boolean                         b_RetSuppressNrc;
    boolean                         b_RetVal;
    boolean                         b_Suppress;

    /* Inital Return Value is Not Suppress Response Message                 */
    b_RetVal            = (boolean)FALSE;
    b_Suppress          = (boolean)FALSE;

    if( Dcm_M_General.bRespondAllRequest == (boolean)TRUE )
    {
        /* No Proccess */
    }
    else
    {
        if( (u1SID & DCM_DSD_NORES_RANGE_MASK) == DCM_DSD_NORES_RANGE_MASK )
        {
            /* No response signal is sent because the SID is a response.    */
            b_Suppress = (boolean)TRUE;
        }
    }
    
    if( b_Suppress == (boolean)FALSE )
    {
        b_RetSuppressNrc   = Dcm_Dsd_SendMng_IsSuppressNegInSpecific( u1SID,
                                                                      u1Nrc,
                                                                      u2ConnectionId );
        if( b_RetSuppressNrc == (boolean)TRUE )
        {
            b_Suppress = (boolean)TRUE;
        }
    }

    if( b_Suppress == (boolean)TRUE )
    {
        b_RetVal = (boolean)TRUE;
        
    }

    return b_RetVal;
}


#if( DCM_SID86_ROE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsd_RoeSendReq                                       */
/* Description   | This function sends the ROE intermediate response and    */
/*               | final response.                                          */
/* Preconditions | none                                                     */
/* Parameters    | [In] ptMsgContext : Transmit and receive management      */
/*               |                     address.                             */
/*               | [in] u2ConnectionId : Connection ID(ClientIndex)         */
/*               |                                                          */
/* Return Value  | Dcm_StatusType                                           */
/*               |      E_OK                   : Success                    */
/*               |      DCM_E_ROE_NOT_ACCEPTED : Busy(should retry)         */
/* Notes         | Important: The user should reserve the area for          */
/*               |            transmitted data.                             */
/****************************************************************************/
FUNC( Dcm_StatusType, DCM_CODE ) Dcm_Dsd_RoeSendReq
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint16 u2ConnectionId
)
{
    Dcm_Dsl_ResponseSettingType u1_ResponseKind;
    Std_ReturnType        u1_RetVal;
    Std_ReturnType        u1_RetDslVal;

    u1_RetVal       = (Dcm_StatusType)DCM_E_OK;
    u1_ResponseKind = DCM_DSL_SET_POSITIVE_RESPONSE;

    Dcm_Dsd_ServiceMng_SetSID( ptMsgContext->idContext );
    u1_RetDslVal = Dcm_Dsl_RoeSendReq( ptMsgContext, u2ConnectionId, u1_ResponseKind );
    if( u1_RetDslVal == (Dcm_StatusType)DCM_E_ROE_NOT_ACCEPTED )
    {
            u1_RetVal   = (Dcm_StatusType)DCM_E_ROE_NOT_ACCEPTED;
    }

    return u1_RetVal;
}
#endif /* DCM_SID86_ROE_USE == STD_ON */


#if ( DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsd_ProvideDiagComData                               */
/* Description   | This function provide diag communication data.           */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptMsgContext : pointer to the message context       */
/*               | [in] u1ResponseKind : Response kind                      */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsd_ProvideDiagComData
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    const uint8 u1ResponseKind
)
{
    Dcm_ConfirmationStatusType  u1_ConfirmationStatus;
    uint8                       u1_Sid;
    uint8                       u1_SubFunc;

    u1_ConfirmationStatus = DCM_RES_NEG_OK;

    if( ( u1ResponseKind == DCM_DSL_SET_POSITIVE_RESPONSE   ) ||
        ( u1ResponseKind == DCM_DSL_SET_NO_RESPONSE_POS     )   ) 
    {
        u1_ConfirmationStatus = DCM_RES_POS_OK;
        /* When sending a response across resets, it is necessary to set    */
        /* response suppression in Dsd.                                     */
        u1_Sid = ptMsgContext->reqData[DCM_DSD_RX_SID_OFFSET];
        if( ( u1_Sid == DCM_DSD_DIAGNOSTICSESSIONCONTROL ) ||
            ( u1_Sid == DCM_DSD_ECURESET                 )   )
        {
            u1_SubFunc = ptMsgContext->reqData[DCM_DSD_RX_SF_OFFSET];
            if( ( u1_SubFunc & DCM_DSD_SUPPRESS_BIT ) == DCM_DSD_SUPPRESS_BIT )
            {
                 ptMsgContext->msgAddInfo.suppressPosResponse = STD_ON;
            }
        }
    }

    (void)Dcm_ProvideDiagComData( u1_ConfirmationStatus, ptMsgContext );

    return;
}
#endif /* DCM_DIAG_COM_DATA_PROVIDE_USE == STD_ON */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dcm_Dsd_SendMng_SendResponse                             */
/* Description   | This function conducts a process of diciding which kind  */
/*               | of response message should be transmitted to DSL         */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptMsgContext : pointer to the message context       */
/*               |        -                                                 */
/* Return Value  | void                                                     */
/*               |         :                                                */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsd_SendMng_SendResponse
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    uint16  u2_ConnectionId;
    uint8   u1_JdgSuppress;
    uint8   u1_SID;
    boolean b_FuncAddrNoResponse;
    boolean b_PendingOccured;
    boolean b_RetSuppressResponse;
    boolean b_SIDRangeErr;
    boolean b_SupressforNegRes;

    b_SIDRangeErr    = (boolean)FALSE;
    u1_SID           = Dcm_Dsd_GetSID();

    if( Dcm_M_General.bRespondAllRequest != (boolean)TRUE )
    {
        if( ( u1_SID & DCM_DSD_NORES_RANGE_MASK ) == DCM_DSD_NORES_RANGE_MASK )
        {
            if( Dcm_Dsd_u1ErrorCode == DCM_DSD_NRC_INVALID )
            {
                Dcm_Dsl_TransmitFunctionality(ptMsgContext, DCM_DSL_SET_NO_RESPONSE_POS);
            }
            else
            {
                Dcm_Dsl_TransmitFunctionality(ptMsgContext, DCM_DSL_SET_NO_RESPONSE_NEG);
            }
            b_SIDRangeErr = (boolean)TRUE;
        }
    }

    if( b_SIDRangeErr == (boolean)FALSE )
    {
        b_PendingOccured = Dcm_Dsl_IsResponsePendingOccured();

        if( Dcm_Dsd_u1ErrorCode == DCM_DSD_NRC_INVALID )
        {
            u1_JdgSuppress = DCM_DSL_SET_POSITIVE_RESPONSE;

            if( b_PendingOccured == (boolean)FALSE )
            {
                if( ptMsgContext->msgAddInfo.suppressPosResponse == (uint8)STD_OFF )
                {
                    /* No process */
                }
                else
                {
                    u1_JdgSuppress = DCM_DSL_SET_NO_RESPONSE_POS;
                }
            }
        }
        else
        {
            u1_JdgSuppress = DCM_DSL_SET_NEGATIVE_RESPONSE;
            b_SupressforNegRes = (boolean)FALSE;
            /* process whether suppress NegRes in FuncAddr */
            if( ptMsgContext->msgAddInfo.reqType == DCM_DSL_ADDINFO_FUNC )
            {
                if( b_PendingOccured == (boolean)FALSE )
                {
                    b_FuncAddrNoResponse = Dcm_Dsd_SendMng_IsSuppressNegResInFuncAddr();
                    if( b_FuncAddrNoResponse == (boolean)TRUE )
                    {
                        b_SupressforNegRes = (boolean)TRUE;
                    }
                }
            }
            
            if( b_SupressforNegRes == (boolean)FALSE )
            {
                /* process whether suppress NegRes in OBD System */
                (void)Dcm_GetActiveProtocol( NULL_PTR,            /* no return check required */
                                             &u2_ConnectionId,
                                             NULL_PTR );
                b_RetSuppressResponse = Dcm_Dsd_SendMng_IsSuppressNegInSpecific( u1_SID,
                                                                                 Dcm_Dsd_u1ErrorCode,
                                                                                 u2_ConnectionId );
                if( b_RetSuppressResponse == (boolean)TRUE )
                {
                    b_SupressforNegRes = (boolean)TRUE;
                }
            }
            
            if( b_SupressforNegRes == (boolean)TRUE )
            {
                u1_JdgSuppress = DCM_DSL_SET_NO_RESPONSE_NEG;
            }
        }
        Dcm_Dsl_TransmitFunctionality(ptMsgContext, u1_JdgSuppress);
    }
    else
    {
        /* No process */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsd_SendMng_IsSuppressNegInSpecific                  */
/* Description   | This function suppresses response messages in specific.  */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1SID           : Service ID                        */
/* Parameters    | [in] u1Nrc           : Nrc                               */
/* Parameters    | [in] u2ConnectionId  : Connection ID                     */
/* Return Value  | boolean                                                  */
/*               |     TRUE:  suppresses response messages in specific      */
/*               |    FALSE:  Other                                         */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_Dsd_SendMng_IsSuppressNegInSpecific
(
    const uint8 u1SID,                          /* MISRA DEVIATION */
    const Dcm_NegativeResponseCodeType u1Nrc,
    const uint16 u2ConnectionId
)
{
    uint8   u1_SupportObdSystem;
    uint8   u1_ProtocolGroup;
    boolean b_NoSuppressNegResIMLOIFToOBDClient;
    boolean b_NoSuppressNegResToUDSClient;
    boolean b_SuppressResponse;
    
    b_SuppressResponse = (boolean)FALSE;
    u1_SupportObdSystem = Dcm_Dsd_u1SupportObdSystem;
    
    if( u1_SupportObdSystem == DCM_DSD_OBDSYS_ON_UDS )
    {
        /* checks negative response of OBD excluding NRC 0x11,12,21,22,24,31,72,78 */
        u1_ProtocolGroup = Dcm_Dsl_GetActiveProtocolGroup( u2ConnectionId );
        if( u1_ProtocolGroup == DCM_DSL_OBD_PROTOCOL )
        {
            if( ( u1Nrc == (uint8)DCM_E_SERVICENOTSUPPORTED ) ||                       /* 0x11 */
                ( u1Nrc == (uint8)DCM_E_SUBFUNCTIONNOTSUPPORTED ) ||                   /* 0x12 */
                ( u1Nrc == (uint8)DCM_E_BUSYREPEATREQUEST ) ||                         /* 0x21 */
                ( u1Nrc == (uint8)DCM_E_CONDITIONSNOTCORRECT ) ||                      /* 0x22 */
                ( u1Nrc == (uint8)DCM_E_REQUESTSEQUENCEERROR ) ||                      /* 0x24 */
                ( u1Nrc == (uint8)DCM_E_REQUESTOUTOFRANGE ) ||                         /* 0x31 */
                ( u1Nrc == (uint8)DCM_E_GENERALPROGRAMMINGFAILURE ) ||                 /* 0x72 */
                ( u1Nrc == (uint8)DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING ) )    /* 0x78 */
            {
                /* No process */
            }
            else if( u1Nrc == (uint8)DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT )      /* 0x13 */
            {
                /* checks negative response of OBD excluding NRC 0x13 */
                b_NoSuppressNegResIMLOIFToOBDClient = Dcm_Dsd_bNoSuppressNegResIMLOIFToOBDClient;
                if( b_NoSuppressNegResIMLOIFToOBDClient == (boolean)TRUE )
                {
                    /* No process */
                }
                else
                {
                    b_SuppressResponse = (boolean)TRUE;
                }
            }
            else
            {
                b_SuppressResponse = (boolean)TRUE;
            }
        }
    }
    else if( u1_SupportObdSystem == DCM_DSD_OBDSYS_ON_EDS )
    {
        /* checks negative response of OBD excluding NRC 0x21 and NRC 0x22 */
        if( u1SID <= DCM_DSD_OBD_SID_MAX )
        {
            u1_ProtocolGroup = Dcm_Dsl_GetActiveProtocolGroup( u2ConnectionId );
            if( u1_ProtocolGroup == DCM_DSL_UDS_PROTOCOL )
            {
                b_NoSuppressNegResToUDSClient = Dcm_Dsd_bNoSuppressNegResToUDSClient;
                if( b_NoSuppressNegResToUDSClient == (boolean)TRUE )
                {
                    /* No process */
                }
                else
                {
                    /* NRC 0x21 and NRC 0x22 */
                    if( ( u1Nrc == (uint8)DCM_E_BUSYREPEATREQUEST ) ||
                        ( u1Nrc == (uint8)DCM_E_CONDITIONSNOTCORRECT ) )
                    {
                        /* No process */
                    }
                    else
                    {
                        b_SuppressResponse = (boolean)TRUE;
                    }
                }
            }
            else
            {
                /* NRC 0x21 and NRC 0x22 */
                if( ( u1Nrc == (uint8)DCM_E_BUSYREPEATREQUEST ) ||
                    ( u1Nrc == (uint8)DCM_E_CONDITIONSNOTCORRECT ) )
                {
                    /* No process */
                }
                else
                {
                    b_SuppressResponse = (boolean)TRUE;
                }
            }
        }
    }
    else /* DCM_DSD_OBDSYS_NONOBD */
    {
        /* No process */
    }

    return b_SuppressResponse;
}

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsd_SendMng_GetPositiveResponseKind                  */
/* Description   | This function gets the response type.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptMsgContext : pointer to the message context       */
/*               |                                                          */
/* Return Value  | Dcm_Dsl_ResponseSettingType                              */
/*               |   DCM_DSL_SET_POSITIVE_RESPONSE : Positive response      */
/*               |   DCM_DSL_SET_NO_RESPONSE_POS   : Positive no response   */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Dcm_Dsl_ResponseSettingType, DCM_CODE) Dcm_Dsd_SendMng_GetPositiveResponseKind
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    uint8                       u1_SID;
    Dcm_Dsl_ResponseSettingType u1_ResponseKind;
    boolean                     b_PendingOccured;
    boolean                     b_SIDRangeErr;

    b_SIDRangeErr    = (boolean)FALSE;
    u1_ResponseKind  = DCM_DSL_SET_POSITIVE_RESPONSE;

    if( Dcm_M_General.bRespondAllRequest == (boolean)FALSE )
    {
        u1_SID = Dcm_Dsd_GetSID();
        if( (u1_SID & DCM_DSD_NORES_RANGE_MASK) == DCM_DSD_NORES_RANGE_MASK )
        {
            u1_ResponseKind  = DCM_DSL_SET_NO_RESPONSE_POS;
            b_SIDRangeErr    = (boolean)TRUE;
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

    if( b_SIDRangeErr == (boolean)FALSE )
    {
        b_PendingOccured = Dcm_Dsl_IsResponsePendingOccured();
        if( b_PendingOccured == (boolean)FALSE )
        {
            if( ptMsgContext->msgAddInfo.suppressPosResponse == (uint8)STD_OFF )
            {
                /* No process */
            }
            else
            {
                u1_ResponseKind = DCM_DSL_SET_NO_RESPONSE_POS;
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

    return u1_ResponseKind;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsd_SendMng_IsSuppressNegResInFuncAddr               */
/* Description   | This function suppresses certain negative response by    */
/*               | function address.                                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |     TRUE:  Suppress negative response message            */
/*               |    FALSE:  Other                                         */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_NO_SURPRESS_7E7F == STD_OFF )
static FUNC(boolean, DCM_CODE) Dcm_Dsd_SendMng_IsSuppressNegResInFuncAddr
(void)
{
    boolean b_SuppressResponse;

    b_SuppressResponse = FALSE;
    if( (Dcm_Dsd_u1ErrorCode != (uint8)DCM_E_SERVICENOTSUPPORTED) &&
      (Dcm_Dsd_u1ErrorCode != (uint8)DCM_E_SUBFUNCTIONNOTSUPPORTED) &&
      (Dcm_Dsd_u1ErrorCode != (uint8)DCM_E_REQUESTOUTOFRANGE) &&
      (Dcm_Dsd_u1ErrorCode != (uint8)DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION) &&
      (Dcm_Dsd_u1ErrorCode != (uint8)DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION) )
    {
        /* No process */
    }
    else
    {
        b_SuppressResponse = TRUE;
    }

    return b_SuppressResponse;
}
#endif /* DCM_NO_SURPRESS_7E7F == STD_OFF */

#if ( DCM_NO_SURPRESS_7E7F == STD_ON )
static FUNC(boolean, DCM_CODE) Dcm_Dsd_SendMng_IsSuppressNegResInFuncAddr
(void)
{
    boolean b_SuppressResponse;

    b_SuppressResponse = FALSE;
    if( (Dcm_Dsd_u1ErrorCode != (uint8)DCM_E_SERVICENOTSUPPORTED) &&
      (Dcm_Dsd_u1ErrorCode != (uint8)DCM_E_SUBFUNCTIONNOTSUPPORTED) &&
      (Dcm_Dsd_u1ErrorCode != (uint8)DCM_E_REQUESTOUTOFRANGE))
    {
        /* No process */
    }
    else
    {
        b_SuppressResponse = TRUE;
    }

    return b_SuppressResponse;
}
#endif /* DCM_NO_SURPRESS_7E7F == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-2-0         :2019-01-29                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-4-0         :2023-06-28                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
