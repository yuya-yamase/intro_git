/* Dcm_Dsl_TxMsg_c(v5-8-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_TxMsg/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsl/inc/Dcm_Dsl_TxMsg.h"
#include "../../Dsl/usr/Dcm_Dsl_TxMsg_Connector.h"
#include "../../Dsl/inc/Dcm_Dsl_TxAbt.h"

#include "../../Dsl/inc/Dcm_Dsl_CommHandling.h"
#include "../../Dsl/inc/Dcm_Dsl_Ctrl_local.h"
#include "../../Dsl/inc/Dcm_Dsl_Main.h"
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm/Dcm_Main_TmrSrv.h>

#include <Dcm.h>
#include <SchM_Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_SINGLE_CLIENT  ((uint8)0x01U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_TransmitCore
(
    const uint16 u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo
);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_CopyTxDataCore
(
    PduIdType                                              uvTxPduId,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA)   ptInfo,
    P2CONST(AB_83_DcmRetryInfoType, AUTOMATIC, DCM_APPL_DATA) ptRetry,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) ptAvailableData
);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_Copy
(
    const uint16                                           u2PduMapIndex,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA)   ptInfo,
    P2CONST(AB_83_DcmRetryInfoType, AUTOMATIC, DCM_APPL_DATA) ptRetry,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) ptAvailableData
);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_CopyRetry
(
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA)   ptInfo,
    P2CONST(AB_83_DcmRetryInfoType, AUTOMATIC, DCM_APPL_DATA) ptRetry,
    P2VAR(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA)        ptTxBuf,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) ptRemaindLength
);

static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_Query
(
    const uint16                                           u2PduMapIndex,
    P2CONST(AB_83_DcmRetryInfoType, AUTOMATIC, DCM_APPL_DATA) ptRetry,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) ptAvailableData
);

static FUNC(void, DCM_CODE) Dcm_Dsl_TxMsg_StartFsTimer
(void);

static FUNC(void, DCM_CODE) Dcm_Dsl_TxMsg_StopFsTimer
(void);

static FUNC(PduIdType, DCM_CODE) Dcm_Dsl_TxMsg_GetTxPduID
(
    const uint16 u2PduMapIndex
);

static FUNC(uint16, DCM_CODE) Dcm_Dsl_TxMsg_GetPduMapIndexByTxConfPduID
(
    const PduIdType uvTxConfPduId
);

static FUNC(boolean, DCM_CODE) Dcm_Dsl_TxMsg_IsExtendedPduLength
(
    const uint16 u2PduMapIndex
);

static FUNC(boolean, DCM_CODE) Dcm_Dsl_TxMsg_IsNoResPduID
(
    const uint16 u2PduMapIndex
);

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
static FUNC(AB_83_DcmPduLengthType, DCM_CODE) Dcm_Dsl_TxMsg_GetMaximumResponseSize
(
    const uint16 u2PduMapIndex
);
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
static VAR(AB_83_DcmPduLengthType, DCM_VAR_NO_INIT) Dcm_Dsl_u4AvailableDataLength;
static VAR(boolean, DCM_VAR_NO_INIT) Dcm_Dsl_bFirstPageOfPagedBuffer;
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
/* Function Name | Dcm_Dsl_TxMsg_Init                                       */
/* Description   | This function initializes Dsl_TxMsg.                     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsl_TxMsg_Init
(void)
{
    Dcm_Dsl_u4AvailableDataLength       = (AB_83_DcmPduLengthType)0U;
    Dcm_Dsl_bFirstPageOfPagedBuffer     = (boolean)FALSE;
    return ;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_StopTimer                                  */
/* Description   | This function stops sending time register by a lump.     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxMsg_StopTimer
(void)
{
    Dcm_Dsl_TxMsg_StopFsTimer();
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_Abort                                      */
/* Description   | This function aborts Dsl Tx Unit processing.             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxMsg_Abort
(void)
{
    Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_TXFSTIMER, (uint32)0U);
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxFailSafeTOCbk                                  */
/* Description   | This function performs a process in TxFailsafe time out. */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1TimerId : not use                                 */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxFailSafeTOCbk
(
    const uint8 u1TimerId /* MISRA DEVIATION */
)
{
    uint16 u2_PduIDNum_Cnt;
    uint16 u2_PduIdNumMax;

    u2_PduIdNumMax = Dcm_Dsl_u2PduIdNum;

    for( u2_PduIDNum_Cnt = (uint16)0U ; u2_PduIDNum_Cnt < u2_PduIdNumMax ; u2_PduIDNum_Cnt++ )
    {
        Dcm_Dsl_TxAbt_FailSafeTO(u2_PduIDNum_Cnt);
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_CopyTxData                                           */
/* Description   | This function is called to acquire the transmit data of  */
/*               | an I-PDU segment (N-PDU).                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] id    : Identification of the transmitted I-PDU.    */
/*               | [in] info  : Provides the destination buffer             */
/*               |               and the number of bytes to be copied.      */
/*               | [in] retry : This parameter is used to acknowledge       */
/*               |              transmitted data or to retransmit data      */
/*               |              after transmission problems.                */
/*               | [out] availableDataPtr : Indicates the remaining number  */
/*               |              of bytes that are available in the upper    */
/*               |              layer module's Tx buffer.                   */
/* Return Value  | BufReq_ReturnType                                        */
/*               | BUFREQ_OK       : Data has been copied to the transmit   */
/*               |                   buffer completely as requested.        */
/*               | BUFREQ_E_NOT_OK : Data has not been copied. Request      */
/*               |                   failed.                                */
/*               | BUFREQ_E_BUSY   : Request could not be fulfilled         */
/* Notes         | Handle this function in context of PduR                  */
/****************************************************************************/
FUNC(BufReq_ReturnType, DCM_CODE) Dcm_CopyTxData
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
    P2CONST(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) retry,
    P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) availableDataPtr
)
{
    BufReq_ReturnType               u1_Retval;
    AB_83_DcmPduInfoType            st_Info;
    AB_83_DcmRetryInfoType          st_Retry;
    AB_83_DcmPduLengthType          uv_AvailableData;

    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) pt_Info;
    P2CONST(AB_83_DcmRetryInfoType, AUTOMATIC, DCM_APPL_DATA) pt_Retry;

    if( info != NULL_PTR )
    {
        st_Info.SduLength  = info->SduLength;
        st_Info.SduDataPtr = info->SduDataPtr;
        pt_Info            = &st_Info;
    }
    else
    {
        pt_Info = NULL_PTR;
    }

    if( retry != NULL_PTR )
    {
        st_Retry.TpDataState = retry->TpDataState;
        st_Retry.TxTpDataCnt = retry->TxTpDataCnt;
        pt_Retry             = &st_Retry;
    }
    else
    {
        pt_Retry = NULL_PTR;
    }

    if( availableDataPtr != NULL_PTR )
    {
        u1_Retval = Dcm_Dsl_TxMsg_CopyTxDataCore(id, pt_Info, pt_Retry, &uv_AvailableData);
        if( u1_Retval == (BufReq_ReturnType)BUFREQ_OK )
        {
            *availableDataPtr = (PduLengthType)uv_AvailableData;
        }
    }
    else
    {
        u1_Retval = Dcm_Dsl_TxMsg_CopyTxDataCore(id, pt_Info, pt_Retry, NULL_PTR);
    }

    return u1_Retval;
}

/****************************************************************************/
/* Function Name | Dcm_CopyTxData32                                         */
/* Description   | This function is called to acquire the transmit data of  */
/*               | an I-PDU segment (N-PDU).                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] id    : Identification of the transmitted I-PDU.    */
/*               | [in] info  : Provides the destination buffer             */
/*               |               and the number of bytes to be copied.      */
/*               | [in] retry : This parameter is used to acknowledge       */
/*               |              transmitted data or to retransmit data      */
/*               |              after transmission problems.                */
/*               | [out] availableDataPtr : Indicates the remaining number  */
/*               |              of bytes that are available in the upper    */
/*               |              layer module's Tx buffer.                   */
/* Return Value  | BufReq_ReturnType                                        */
/*               | BUFREQ_OK       : Data has been copied to the transmit   */
/*               |                   buffer completely as requested.        */
/*               | BUFREQ_E_NOT_OK : Data has not been copied. Request      */
/*               |                   failed.                                */
/*               | BUFREQ_E_BUSY   : Request could not be fulfilled         */
/* Notes         | Handle this function in context of PduR                  */
/****************************************************************************/
FUNC(BufReq_ReturnType, DCM_CODE) Dcm_CopyTxData32
(
    PduIdType id,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
    P2CONST(AB_83_DcmRetryInfoType, AUTOMATIC, DCM_APPL_DATA) retry,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) availableDataPtr
)
{
    return Dcm_Dsl_TxMsg_CopyTxDataCore(id, info, retry, availableDataPtr);
}


/****************************************************************************/
/* Function Name | Dcm_TpTxConfirmation                                     */
/* Description   | This function is called after the I-PDU has been .       */
/*               | transmitted on its network, the result indicates whether */
/*               | the transmission was successful or not.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] id     : Identification of the transmitted I-PDU.   */
/*               |                                                          */
/*               | [in] result : Result of the transmission of the I-PDU.   */
/* Return Value  | none                                                     */
/* Notes         | Handle this function in context of PduR                  */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_TpTxConfirmation
(
    PduIdType id,
    Std_ReturnType result
)
{
    Dcm_Dsl_ResponseSettingType u1_ResponseKind;
    boolean                     b_IsTxState;
    uint16                      u2_PduMapIndex;

    u1_ResponseKind = DCM_DSL_SET_NONE_RESPONSE;

    u2_PduMapIndex = Dcm_Dsl_TxMsg_GetPduMapIndexByTxConfPduID(id);
    if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_TxPduInfo();

        /* Return value ignoring */
        (void)Dcm_Dsl_TxAbt_GetLastTransmittedMsg(u2_PduMapIndex, &u1_ResponseKind);

        /* unlock */
        SchM_Exit_Dcm_Dsl_TxPduInfo();

        if( u1_ResponseKind != DCM_DSL_SET_NONE_RESPONSE )
        {
            b_IsTxState = Dcm_Dsl_TxAbt_IsTxState(u2_PduMapIndex);
            if( b_IsTxState == (boolean)TRUE )
            {
                Dcm_Dsl_TxMsg_StopFsTimer();
                if( u1_ResponseKind == DCM_DSL_SET_PENDING_RESPONSE )
                {
                    Dcm_Dsl_TxAbt_HandlTopHalfRcrrpConfirmation(u2_PduMapIndex, result, u1_ResponseKind);
                }
                else
                {
                    Dcm_Dsl_TxAbt_HandlTopHalfLastConfirmation(u2_PduMapIndex, result, u1_ResponseKind);
                }
            }
        }
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_Transmit                                   */
/* Description   | This function sends response message                     */
/*               | P2TO : RCRRP(requestCorrectlyReceivedResponsePending)    */
/*               | P4TO : generalReject                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] ptInfo : PduR sending buffer address                */
/*               |                                                          */
/*               | [in] u1ResponseKind : Response kind                      */
/*               |                DCM_DSL_SET_POSITIVE_RESPONSE             */
/*               |                DCM_DSL_SET_NEGATIVE_RESPONSE             */
/*               |                DCM_DSL_SET_NO_RESPONSE_POS               */
/*               |                DCM_DSL_SET_NO_RESPONSE_NEG               */
/*               |                DCM_DSL_SET_PENDING_RESPONSE              */
/*               |                DCM_DSL_SET_P4TO_NEG_RESPONSE             */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : Success                        */
/*               |   DCM_DSL_TX_E_SEND_ERR : Transmission Error             */
/*               |   DCM_DSL_TX_E_DISABLE  : Transmission prohibited        */
/*               |   DCM_DSL_TX_E_SUPPRES  : Transmission suppressed        */
/*               |   DCM_DSL_TX_E_NORESP   : No answer                      */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_Transmit
(
    const uint16 u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo,
    const Dcm_Dsl_ResponseSettingType u1ResponseKind
)
{
    AB_83_DcmPduLengthType uv_MaxRespSize;
    Std_ReturnType         u1_Result;
    Std_ReturnType         u1_Retval;
    boolean                b_IsNoResponsePduId;
    boolean                b_IsComEnable;
    boolean                b_Transmit;

    u1_Result           = (Std_ReturnType)E_OK;
    b_Transmit          = (boolean)FALSE;
    b_IsNoResponsePduId = Dcm_Dsl_TxMsg_IsNoResPduID(u2PduMapIndex);

    if( ( u1ResponseKind == (Dcm_Dsl_ResponseSettingType)DCM_DSL_SET_POSITIVE_RESPONSE )
     || ( u1ResponseKind == (Dcm_Dsl_ResponseSettingType)DCM_DSL_SET_NEGATIVE_RESPONSE ) )
    {
        if( b_IsNoResponsePduId == (boolean)FALSE )
        {
            b_Transmit = (boolean)TRUE;
        }
        else
        {
            u1_Result = DCM_DSL_TX_E_NORESP;
        }
    }
    else if( ( u1ResponseKind == (Dcm_Dsl_ResponseSettingType)DCM_DSL_SET_PENDING_RESPONSE )
          || ( u1ResponseKind == (Dcm_Dsl_ResponseSettingType)DCM_DSL_SET_P4TO_NEG_RESPONSE ) )
    {
        if( b_IsNoResponsePduId == (boolean)FALSE )
        {
            b_Transmit = (boolean)TRUE;
        }
        else
        {
            u1_Result = DCM_DSL_TX_E_SUPPRES;
        }
    }
    else
    {
        u1_Result = DCM_DSL_TX_E_NORESP;
    }

    if( b_Transmit == (boolean)TRUE )
    {
        b_IsComEnable = Dcm_Dsl_CmHdl_IsComEnable(u2PduMapIndex, DCM_DSL_COMTYPE_TRANSMIT);
        if( b_IsComEnable == (boolean)TRUE )
        {
            if( ( u1ResponseKind != (Dcm_Dsl_ResponseSettingType)DCM_DSL_SET_PENDING_RESPONSE )
             && ( u1ResponseKind != (Dcm_Dsl_ResponseSettingType)DCM_DSL_SET_P4TO_NEG_RESPONSE ) )
            {
                Dcm_Dsl_TxAbt_NotifyTxStart();
            }

            uv_MaxRespSize = Dcm_Dsl_TxMsg_GetMaximumResponseSize(u2PduMapIndex);
            if( uv_MaxRespSize < ptInfo->SduLength )
            {
                Dcm_Dsl_bFirstPageOfPagedBuffer = (boolean)TRUE;
            }
            else
            {
                Dcm_Dsl_bFirstPageOfPagedBuffer = (boolean)FALSE;
            }

            Dcm_Dsl_u4AvailableDataLength = ptInfo->SduLength;
            u1_Retval                     = Dcm_Dsl_TxMsg_TransmitCore(u2PduMapIndex, ptInfo);
            if( u1_Retval == (Std_ReturnType)E_OK )
            {
                Dcm_Dsl_TxMsg_StartFsTimer();
            }
            else
            {
                u1_Result = DCM_DSL_TX_E_SEND_ERR;
            }
        }
        else
        {
            u1_Result = DCM_DSL_TX_E_DISABLE;
        }
    }
    else
    {
        if( u1_Result == DCM_DSL_TX_E_NORESP )
        {
            Dcm_Dsl_TxAbt_NotifyTxStart();
        }
    }

    return u1_Result;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

#if( DCM_PAGEDBUFFER_ENABLED == STD_OFF )
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_Transmit
(
    const uint16 u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo,
    const Dcm_Dsl_ResponseSettingType u1ResponseKind
)
{
    Std_ReturnType u1_Result;
    Std_ReturnType u1_Retval;
    boolean        b_IsNoResponsePduId;
    boolean        b_IsComEnable;
    boolean        b_Transmit;

    u1_Result           = (Std_ReturnType)E_OK;
    b_Transmit          = (boolean)FALSE;
    b_IsNoResponsePduId = Dcm_Dsl_TxMsg_IsNoResPduID(u2PduMapIndex);

    if( ( u1ResponseKind == (Dcm_Dsl_ResponseSettingType)DCM_DSL_SET_POSITIVE_RESPONSE )
     || ( u1ResponseKind == (Dcm_Dsl_ResponseSettingType)DCM_DSL_SET_NEGATIVE_RESPONSE ) )
    {
        if( b_IsNoResponsePduId == (boolean)FALSE )
        {
            b_Transmit = (boolean)TRUE;
        }
        else
        {
            u1_Result = DCM_DSL_TX_E_NORESP;
        }
    }
    else if( ( u1ResponseKind == (Dcm_Dsl_ResponseSettingType)DCM_DSL_SET_PENDING_RESPONSE )
          || ( u1ResponseKind == (Dcm_Dsl_ResponseSettingType)DCM_DSL_SET_P4TO_NEG_RESPONSE ) )
    {
        if( b_IsNoResponsePduId == (boolean)FALSE )
        {
            b_Transmit = (boolean)TRUE;
        }
        else
        {
            u1_Result = DCM_DSL_TX_E_SUPPRES;
        }
    }
    else
    {
        u1_Result = DCM_DSL_TX_E_NORESP;
    }

    if( b_Transmit == (boolean)TRUE )
    {
        b_IsComEnable = Dcm_Dsl_CmHdl_IsComEnable(u2PduMapIndex, DCM_DSL_COMTYPE_TRANSMIT);
        if( b_IsComEnable == (boolean)TRUE )
        {
            if( ( u1ResponseKind != (Dcm_Dsl_ResponseSettingType)DCM_DSL_SET_PENDING_RESPONSE )
             && ( u1ResponseKind != (Dcm_Dsl_ResponseSettingType)DCM_DSL_SET_P4TO_NEG_RESPONSE ) )
            {
                Dcm_Dsl_TxAbt_NotifyTxStart();
            }

            u1_Retval  = Dcm_Dsl_TxMsg_TransmitCore(u2PduMapIndex, ptInfo);
            if( u1_Retval == (Std_ReturnType)E_OK )
            {
                Dcm_Dsl_TxMsg_StartFsTimer();
            }
            else
            {
                u1_Result = DCM_DSL_TX_E_SEND_ERR;
            }
        }
        else
        {
            u1_Result = DCM_DSL_TX_E_DISABLE;
        }
    }
    else
    {
        if( u1_Result == DCM_DSL_TX_E_NORESP )
        {
            Dcm_Dsl_TxAbt_NotifyTxStart();
        }
    }

    return u1_Result;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_OFF */

#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_PosResTransmit                             */
/* Description   | This function sends response message                     */
/* Preconditions | Call only from Dcm_Dsl_TxAbt_RespReqAfterEcuReset()      */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] ptInfo : PduR sending buffer address                */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : Success                        */
/*               |   DCM_DSL_TX_E_SEND_ERR : Transmission Error             */
/*               |   DCM_DSL_TX_E_DISABLE  : Transmission prohibited        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_PosResTransmit
(
    const uint16 u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo
)
{
    Std_ReturnType u1_Result;
    Std_ReturnType u1_Retval;
    boolean        b_IsComEnable;

    u1_Result        = (Std_ReturnType)E_OK;
    b_IsComEnable    = Dcm_Dsl_CmHdl_IsComEnable(u2PduMapIndex, DCM_DSL_COMTYPE_TRANSMIT);
    if( b_IsComEnable == (boolean)TRUE )
    {
        u1_Retval  = Dcm_Dsl_TxMsg_TransmitCore(u2PduMapIndex, ptInfo);
        if( u1_Retval == (Std_ReturnType)E_OK )
        {
            Dcm_Dsl_TxAbt_NotifyTxStart();
            Dcm_Dsl_TxMsg_StartFsTimer();
        }
        else
        {
            u1_Result = DCM_DSL_TX_E_SEND_ERR;
        }
    }
    else
    {
        u1_Result = DCM_DSL_TX_E_DISABLE;
    }


    return u1_Result;
}
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_NegResTransmit                             */
/* Description   | This function sends response message                     */
/* Preconditions | Call only from Dcm_Dsl_TxAbt_BusyResTransmit()           */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] ptInfo : PduR sending buffer address                */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : Success                        */
/*               |   DCM_DSL_TX_E_SEND_ERR : Transmission Error             */
/*               |   DCM_DSL_TX_E_DISABLE  : Transmission prohibited        */
/*               |   DCM_DSL_TX_E_SUPPRES  : Transmission suppressed        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_NegResTransmit
(
    const uint16 u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo
)
{
    Std_ReturnType u1_Result;
    Std_ReturnType u1_Retval;
    boolean        b_IsComEnable;
    boolean        b_IsNoResponsePduId;

    u1_Result           = (Std_ReturnType)E_OK;
    b_IsNoResponsePduId = Dcm_Dsl_TxMsg_IsNoResPduID(u2PduMapIndex);

    if( b_IsNoResponsePduId == (boolean)FALSE )
    {
        b_IsComEnable = Dcm_Dsl_CmHdl_IsComEnable(u2PduMapIndex, DCM_DSL_COMTYPE_TRANSMIT);
        if( b_IsComEnable == (boolean)TRUE )
        {
            u1_Retval = Dcm_Dsl_TxMsg_TransmitCore(u2PduMapIndex, ptInfo);
            if( u1_Retval == (Std_ReturnType)E_OK )
            {
                Dcm_Dsl_TxMsg_StartFsTimer();
            }
            else
            {
                u1_Result = DCM_DSL_TX_E_SEND_ERR;
            }
        }
        else
        {
            u1_Result = DCM_DSL_TX_E_DISABLE;
        }
    }
    else
    {
        u1_Result = DCM_DSL_TX_E_SUPPRES;
    }

    return u1_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_CancelTransmit                             */
/* Description   | This function cancels the transmission process           */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_TxMsg_CancelTransmit
(
    const uint16 u2PduMapIndex
)
{
    uint16     u2_RowNum;
    PduIdType  uv_TxPduId;

    u2_RowNum = Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2RowIndex;
    if( Dcm_Dsl_stRow[u2_RowNum].bCommunicationCancelUsed == (boolean)TRUE )
    {
        uv_TxPduId = Dcm_Dsl_TxMsg_GetTxPduID(u2PduMapIndex);
        if( uv_TxPduId != DCM_DSL_INVALID_U2_DATA )
        {
            /* Return value ignoring */
            (void)Dcm_Dsl_Cnct_CancelTransmit(uv_TxPduId);
        }
    }
    Dcm_Dsl_TxMsg_StopFsTimer();

    return ;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_TransmitCore                               */
/* Description   | This function is a connector for -                       */
/*               | PduR_DcmTransmit/XxxTpTransmit function.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] ptInfo : PduR sending buffer address                */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK     : request is accepted by the destination module */
/*               |                   transmission is continued.             */
/*               | E_NOT_OK : request is not accepted by the destination    */
/*               |            module transmission is aborted.               */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_TransmitCore
(
    const uint16 u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo
)
{
    P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) pt_wrpInfo;
    AB_83_DcmPduInfoType st_Info;
    PduIdType      uv_TxPduId;
    Std_ReturnType u1_Result;
    boolean        b_Extended;
    /* Measures to avoid worrying about member MetaDataPtr */
    PduInfoType    st_wrpInfo;

    Dcm_Main_SetMemory( (uint8*)&st_wrpInfo, (uint8)0U, (uint16)(sizeof(st_wrpInfo)) );
    uv_TxPduId = Dcm_Dsl_TxMsg_GetTxPduID(u2PduMapIndex);
    if( uv_TxPduId != DCM_DSL_INVALID_U2_DATA )
    {
        b_Extended = Dcm_Dsl_TxMsg_IsExtendedPduLength(u2PduMapIndex);
        if( b_Extended == (boolean)TRUE )
        {
            st_Info.SduDataPtr = ptInfo->SduStartAddr;
            st_Info.SduLength  = ptInfo->SduLength;

            u1_Result = Dcm_Dsl_Cnct_Transmit32(uv_TxPduId, &st_Info);
        }
        else
        {
            st_wrpInfo.SduLength   = (PduLengthType)ptInfo->SduLength;
            st_wrpInfo.SduDataPtr  = ptInfo->SduStartAddr;
            pt_wrpInfo             = &st_wrpInfo;

            u1_Result = Dcm_Dsl_Cnct_Transmit(uv_TxPduId, pt_wrpInfo);
        }
    }
    else
    {
        u1_Result = E_NOT_OK;
    }
    return u1_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_CopyTxDataCore                             */
/* Description   | This function is called to acquire the transmit data of  */
/*               | an I-PDU segment (N-PDU).                                */
/* Preconditions | none                                                     */
/* Parameters    | [in] uvTxPduId : Identification of the transmitted I-PDU.*/
/*               | [in] ptInfo : Provides the destination buffer            */
/*               |               and the number of bytes to be copied.      */
/*               | [in] ptRetry : This parameter is used to acknowledge     */
/*               |              transmitted data or to retransmit data      */
/*               |              after transmission problems.                */
/*               | [out] ptAvailableData : Indicates the remaining number   */
/*               |              of bytes that are available in the upper    */
/*               |              layer module's Tx buffer.                   */
/* Return Value  | BufReq_ReturnType                                        */
/*               | BUFREQ_OK       : Data has been copied to the transmit   */
/*               |                   buffer completely as requested.        */
/*               | BUFREQ_E_NOT_OK : Data has not been copied. Request      */
/*               |                   failed.                                */
/*               | BUFREQ_E_BUSY   : Request could not be fulfilled         */
/* Notes         | Handle this function in context of PduR                  */
/****************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_CopyTxDataCore
(
    PduIdType                                              uvTxPduId,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA)   ptInfo,
    P2CONST(AB_83_DcmRetryInfoType, AUTOMATIC, DCM_APPL_DATA) ptRetry,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) ptAvailableData
)
{
    uint16                 u2_PduMapIndex;
    BufReq_ReturnType      u1_Result;
    boolean                b_IsTxState;
    boolean                b_IsInvalidAddress;

    b_IsInvalidAddress = (boolean)FALSE;

    u2_PduMapIndex = Dcm_Dsl_TxMsg_GetPduMapIndexByTxConfPduID(uvTxPduId);
    if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
    {
        if( ptInfo != NULL_PTR )
        {
            if( ptInfo->SduDataPtr == NULL_PTR )
            {
                if( ptInfo->SduLength != (AB_83_DcmPduLengthType)0U )
                {
                    b_IsInvalidAddress = (boolean)TRUE;
                }
            }

            if( b_IsInvalidAddress == (boolean)FALSE )
            {
                b_IsTxState = Dcm_Dsl_TxAbt_IsTxState(u2_PduMapIndex);
                if( b_IsTxState == (boolean)TRUE )
                {
                    Dcm_Dsl_TxMsg_StopFsTimer();

                    if( ptInfo->SduLength == (AB_83_DcmPduLengthType)0U )
                    {
                        u1_Result = Dcm_Dsl_TxMsg_Query(u2_PduMapIndex, ptRetry, ptAvailableData);
                    }
                    else
                    {
                        u1_Result = Dcm_Dsl_TxMsg_Copy(u2_PduMapIndex, ptInfo, ptRetry, ptAvailableData);
                    }

                    Dcm_Dsl_TxMsg_StartFsTimer();

                }
                else
                {
                    u1_Result = BUFREQ_E_NOT_OK;
                }
            }
            else
            {
                u1_Result = BUFREQ_E_NOT_OK;
            }
        }
        else
        {
            u1_Result = BUFREQ_E_NOT_OK;
        }
    }
    else
    {
        u1_Result = BUFREQ_E_NOT_OK;
    }

    return u1_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_Copy                                       */
/* Description   | This function performs message copy processing           */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               | [in] ptInfo   : Provides the destination buffer          */
/*               |                 and the number of bytes to be copied.    */
/*               | [in] ptRetry  : This parameter is used to acknowledge    */
/*               |                 transmitted data or to retransmit data   */
/*               |                 after transmission problems.             */
/*               | [out] ptAvailableData : Indicates the remaining number   */
/*               |              of bytes that are available in the upper    */
/*               |              layer module's Tx buffer.                   */
/*               |                                                          */
/* Return Value  | BufReq_ReturnType                                        */
/*               | BUFREQ_OK       : Data has been copied to the transmit   */
/*               |                   buffer completely as requested.        */
/*               | BUFREQ_E_NOT_OK : Data has not been copied. Request      */
/*               |                   failed.                                */
/*               | BUFREQ_E_BUSY   : Request could not be fulfilled         */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_Copy
(
    const uint16                                           u2PduMapIndex,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA)   ptInfo,
    P2CONST(AB_83_DcmRetryInfoType, AUTOMATIC, DCM_APPL_DATA) ptRetry,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) ptAvailableData
)
{
    P2VAR(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) pt_TxBuf;
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA)           pt_SduDataPtr;
    AB_83_DcmPduLengthType  uv_CopyLength;
    AB_83_DcmPduLengthType  uv_MaxRespSize;
    BufReq_ReturnType       u1_Result;

    u1_Result = BUFREQ_OK;
    pt_TxBuf  = Dcm_Dsl_TxAbt_GetTxBuf(u2PduMapIndex);

    uv_MaxRespSize = Dcm_Dsl_TxMsg_GetMaximumResponseSize(u2PduMapIndex);
    if( Dcm_Dsl_bFirstPageOfPagedBuffer == (boolean)TRUE )
    {
        pt_TxBuf->SduLength             = Dcm_Dsl_TxAbt_GetResponseDataLength();
        Dcm_Dsl_bFirstPageOfPagedBuffer = (boolean)FALSE;
    }

    if( ptRetry != NULL_PTR )
    {
        u1_Result = Dcm_Dsl_TxMsg_CopyRetry(ptInfo, ptRetry, pt_TxBuf, &Dcm_Dsl_u4AvailableDataLength);
        if( u1_Result != (BufReq_ReturnType)BUFREQ_OK )
        {
            if( uv_MaxRespSize < ptInfo->SduLength )
            {
                u1_Result = BUFREQ_E_NOT_OK;
            }
            else
            {
                u1_Result = Dcm_Dsl_TxAbt_HandlTopHalfUpdatePage(u2PduMapIndex);
            }
        }
    }
    else
    {
        if( ptInfo->SduLength <= pt_TxBuf->SduLength )
        {
            pt_SduDataPtr = &pt_TxBuf->SduStartAddr[pt_TxBuf->SduPos];
            for( uv_CopyLength = (AB_83_DcmPduLengthType)0U; uv_CopyLength < ptInfo->SduLength; uv_CopyLength++ )
            {
                ptInfo->SduDataPtr[uv_CopyLength] = pt_SduDataPtr[uv_CopyLength];
            }
            pt_TxBuf->SduLength           -= uv_CopyLength;                               /* no wrap around */
            pt_TxBuf->SduPos              += uv_CopyLength;                               /* no wrap around */
            Dcm_Dsl_u4AvailableDataLength -= uv_CopyLength;                               /* no wrap around */
        }
        else if( uv_MaxRespSize < ptInfo->SduLength )
        {
            u1_Result = BUFREQ_E_NOT_OK;
        }
        else
        {
            u1_Result = Dcm_Dsl_TxAbt_HandlTopHalfUpdatePage(u2PduMapIndex);
        }
    }

    if( ptAvailableData != NULL_PTR )
    {
        *ptAvailableData = pt_TxBuf->SduLength;
    }

    return u1_Result;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */
#if( DCM_PAGEDBUFFER_ENABLED == STD_OFF )
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_Copy
(
    const uint16                                           u2PduMapIndex,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA)   ptInfo,
    P2CONST(AB_83_DcmRetryInfoType, AUTOMATIC, DCM_APPL_DATA) ptRetry,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) ptAvailableData
)
{
    P2VAR(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) pt_TxBuf;
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA)           pt_SduDataPtr;
    AB_83_DcmPduLengthType          uv_CopyLength;
    AB_83_DcmPduLengthType          uv_DummyRemaindLength;
    BufReq_ReturnType      u1_Result;

    u1_Result = BUFREQ_OK;
    pt_TxBuf  = Dcm_Dsl_TxAbt_GetTxBuf(u2PduMapIndex);

    if( ptRetry != NULL_PTR )
    {
        uv_DummyRemaindLength = pt_TxBuf->SduLength;
        u1_Result             = Dcm_Dsl_TxMsg_CopyRetry(ptInfo, ptRetry, pt_TxBuf, &uv_DummyRemaindLength);
    }
    else
    {
        if( ptInfo->SduLength <= pt_TxBuf->SduLength )
        {
            pt_SduDataPtr = &pt_TxBuf->SduStartAddr[pt_TxBuf->SduPos];
            for( uv_CopyLength = (AB_83_DcmPduLengthType)0U; uv_CopyLength < ptInfo->SduLength; uv_CopyLength++ )
            {
                ptInfo->SduDataPtr[uv_CopyLength] = pt_SduDataPtr[uv_CopyLength];
            }
            pt_TxBuf->SduLength -= uv_CopyLength;                                         /* no wrap around */
            pt_TxBuf->SduPos    += uv_CopyLength;                                         /* no wrap around */
        }
        else
        {
            u1_Result = BUFREQ_E_BUSY;
        }
    }

    if( ptAvailableData != NULL_PTR )
    {
        *ptAvailableData = pt_TxBuf->SduLength;
    }

    return u1_Result;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_OFF */

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_CopyRetry                                  */
/* Description   | This function performs the retry of the copy process     */
/* Preconditions | none                                                     */
/* Parameters    | [in] ptInfo   : Provides the destination buffer          */
/*               |                 and the number of bytes to be copied.    */
/*               | [in] ptRetry  : This parameter is used to acknowledge    */
/*               |                 transmitted data or to retransmit data   */
/*               |                 after transmission problems.             */
/*               | [in/out] ptTxBuf : PduR sending buffer address           */
/*               | [in/out] ptRemaindLength : remaind data length           */
/*               |                                                          */
/* Return Value  | BufReq_ReturnType                                        */
/*               | BUFREQ_OK       : Data has been copied to the transmit   */
/*               |                   buffer completely as requested.        */
/*               | BUFREQ_E_BUSY   : Request could not be fulfilled         */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_CopyRetry
(
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo,
    P2CONST(AB_83_DcmRetryInfoType, AUTOMATIC, DCM_APPL_DATA) ptRetry,
    P2VAR(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptTxBuf,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) ptRemaindLength
)
{
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) pt_SduDataPtr;
    AB_83_DcmPduLengthType uv_CopyLength;
    BufReq_ReturnType      u1_Result;

    u1_Result = BUFREQ_OK;

    if( ptInfo->SduLength <= ( ptTxBuf->SduLength + ptRetry->TxTpDataCnt ) )       /* no wrap around */
    {
        if( ptRetry->TpDataState == (TpDataStateType)TP_DATACONF )
        {
            pt_SduDataPtr = &ptTxBuf->SduStartAddr[ptTxBuf->SduPos];
            for( uv_CopyLength = (AB_83_DcmPduLengthType)0U; uv_CopyLength < ptInfo->SduLength; uv_CopyLength++ )
            {
                ptInfo->SduDataPtr[uv_CopyLength] = pt_SduDataPtr[uv_CopyLength];
            }
            ptTxBuf->SduLength -= uv_CopyLength;                                   /* no wrap around */
            ptTxBuf->SduPos    += uv_CopyLength;                                   /* no wrap around */
            *ptRemaindLength   -= uv_CopyLength;                                   /* no wrap around */
        }
        else if( ptRetry->TpDataState == (TpDataStateType)TP_DATARETRY )
        {
            if( ptTxBuf->SduPos >= ptRetry->TxTpDataCnt )
            {
                ptTxBuf->SduLength  += ptRetry->TxTpDataCnt;                       /* no wrap around */
                ptTxBuf->SduPos     -= ptRetry->TxTpDataCnt;                       /* no wrap around */
                *ptRemaindLength    = *ptRemaindLength + ptRetry->TxTpDataCnt;     /* no wrap around */

                pt_SduDataPtr = &ptTxBuf->SduStartAddr[ptTxBuf->SduPos];
                for( uv_CopyLength = (AB_83_DcmPduLengthType)0U; uv_CopyLength < ptInfo->SduLength; uv_CopyLength++ )
                {
                    ptInfo->SduDataPtr[uv_CopyLength] = pt_SduDataPtr[uv_CopyLength];
                }
                ptTxBuf->SduLength -= uv_CopyLength;                               /* no wrap around */
                ptTxBuf->SduPos    += uv_CopyLength;                               /* no wrap around */
                *ptRemaindLength   -= uv_CopyLength;                               /* no wrap around */
            }
            else
            {
                u1_Result = BUFREQ_E_BUSY;
            }
        }
        else
        {
            pt_SduDataPtr = &ptTxBuf->SduStartAddr[ptTxBuf->SduPos];
            for( uv_CopyLength = (AB_83_DcmPduLengthType)0U; uv_CopyLength < ptInfo->SduLength; uv_CopyLength++ )
            {
                ptInfo->SduDataPtr[uv_CopyLength] = pt_SduDataPtr[uv_CopyLength];
            }
        }
    }
    else
    {
        u1_Result = BUFREQ_E_BUSY;
    }

    return u1_Result;
}

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_Query                                      */
/* Description   | This function queries the size of data stored in         */
/*               | the send buffer.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] ptRetry : This parameter is used to acknowledge     */
/*               |              transmitted data or to retransmit data      */
/*               |              after transmission problems.                */
/*               | [out] ptAvailableData : Indicates the remaining number   */
/*               |              of bytes that are available in the upper    */
/*               |              layer module's Tx buffer.                   */
/* Return Value  | BufReq_ReturnType                                        */
/*               | BUFREQ_OK       : Data has been copied to the transmit   */
/*               |                   buffer completely as requested.        */
/*               | BUFREQ_E_NOT_OK : Data has not been copied. Request      */
/*               |                   failed.                                */
/*               | BUFREQ_E_BUSY   : Request could not be fulfilled         */
/* Notes         | Handle this function in context of PduR                  */
/****************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_Query
(
    const uint16                                           u2PduMapIndex,
    P2CONST(AB_83_DcmRetryInfoType, AUTOMATIC, DCM_APPL_DATA) ptRetry,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) ptAvailableData
)
{
    P2VAR(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) pt_TxBuf;
    BufReq_ReturnType      u1_Result;
    BufReq_ReturnType      u1_UpdateResult;

    u1_Result = BUFREQ_OK;

    if( ptAvailableData != NULL_PTR )
    {
        pt_TxBuf = Dcm_Dsl_TxAbt_GetTxBuf(u2PduMapIndex);

        if( Dcm_Dsl_bFirstPageOfPagedBuffer == (boolean)TRUE )
        {
            *ptAvailableData = Dcm_Dsl_TxAbt_GetResponseDataLength();
        }
        else if( pt_TxBuf->SduLength == (AB_83_DcmPduLengthType)0U )
        {
            if( Dcm_Dsl_u4AvailableDataLength > (AB_83_DcmPduLengthType)0U )
            {
                u1_UpdateResult = Dcm_Dsl_TxAbt_HandlTopHalfUpdatePage(u2PduMapIndex);
                if( u1_UpdateResult == (BufReq_ReturnType)BUFREQ_E_NOT_OK )
                {
                    u1_Result = u1_UpdateResult;
                }
            }
            *ptAvailableData = pt_TxBuf->SduLength;
        }
        else
        {
            *ptAvailableData = pt_TxBuf->SduLength;
        }

        if( ptRetry != NULL_PTR )
        {
            if( ptRetry->TpDataState == (TpDataStateType)TP_DATACONF )
            {
                Dcm_Dsl_u4AvailableDataLength -= pt_TxBuf->SduLength;                 /* no wrap around */
                pt_TxBuf->SduLength            = (AB_83_DcmPduLengthType)0U;
                *ptAvailableData               = (AB_83_DcmPduLengthType)0U;
            }
            else
            {
                /* no process */
                /* TP_DATARETRY is not supported because it can not detect buffer underrun */
                /* TP_CONFPENDING does not make sense because SduLength is 0. */
            }
        }
    }
    else
    {
        u1_Result = BUFREQ_E_NOT_OK;
    }

    return u1_Result;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

#if( DCM_PAGEDBUFFER_ENABLED == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_Query                                      */
/* Description   | This function queries the size of data stored in         */
/*               | the send buffer.                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/*               |                                                          */
/*               | [in] ptRetry : This parameter is used to acknowledge     */
/*               |              transmitted data or to retransmit data      */
/*               |              after transmission problems.                */
/*               | [out] ptAvailableData : Indicates the remaining number   */
/*               |              of bytes that are available in the upper    */
/*               |              layer module's Tx buffer.                   */
/* Return Value  | BufReq_ReturnType                                        */
/*               | BUFREQ_OK       : Data has been copied to the transmit   */
/*               |                   buffer completely as requested.        */
/*               | BUFREQ_E_NOT_OK : Data has not been copied. Request      */
/*               |                   failed.                                */
/* Notes         | Handle this function in context of PduR                  */
/****************************************************************************/
static FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_Query
(
    const uint16                                           u2PduMapIndex,
    P2CONST(AB_83_DcmRetryInfoType, AUTOMATIC, DCM_APPL_DATA) ptRetry,
    P2VAR(AB_83_DcmPduLengthType, AUTOMATIC, DCM_APPL_DATA) ptAvailableData
)
{
    P2VAR(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) pt_TxBuf;
    BufReq_ReturnType u1_Result;

    u1_Result = BUFREQ_OK;

    if( ptAvailableData != NULL_PTR )
    {
        pt_TxBuf         = Dcm_Dsl_TxAbt_GetTxBuf(u2PduMapIndex);
        *ptAvailableData = pt_TxBuf->SduLength;

        if( ptRetry != NULL_PTR )
        {
            if( ptRetry->TpDataState == (TpDataStateType)TP_DATACONF )
            {
                pt_TxBuf->SduLength = (AB_83_DcmPduLengthType)0U;
                *ptAvailableData    = (AB_83_DcmPduLengthType)0U;
            }
            else
            {
                /* no process */
                /* TP_DATARETRY is not supported because it can not detect buffer underrun */
                /* TP_CONFPENDING does not make sense because SduLength is 0. */
            }
        }
    }
    else
    {
        u1_Result = BUFREQ_E_NOT_OK;
    }

    return u1_Result;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_OFF */

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_StartFsTimer                               */
/* Description   | Start fail-safe timer according to parallel transmission */
/*               | status.                                                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxMsg_StartFsTimer
(void)
{
    uint32  u4_TimerValue;
    u4_TimerValue = Dcm_Dsl_stGeneral[0].u4FailSafeTimeout;
    Dcm_Main_TmrSrv_StartTimer(DCM_M_TMRID_TXFSTIMER, u4_TimerValue);
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_StopFsTimer                                */
/* Description   | Stop fail-safe timer according to parallel transmission  */
/*               | status.                                                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_TxMsg_StopFsTimer
(void)
{
    uint8 u1_CurrentNumOfTransmissions;

    u1_CurrentNumOfTransmissions = Dcm_Dsl_TxAbt_GetNumOfConcurrentTx();
    if( u1_CurrentNumOfTransmissions == DCM_DSL_SINGLE_CLIENT )
    {
        Dcm_Main_TmrSrv_StopTimer(DCM_M_TMRID_TXFSTIMER);
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_GetTxPduID                                 */
/* Description   | Get a Transimit PduID.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | PduIdType                                                */
/*               |       0U~PduIdmax             : Transimit PduID          */
/*               |       DCM_DSL_INVALID_U2_DATA : Undefined error          */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_DSL_ROE_EXTENDED_ENABLE == STD_OFF )
static FUNC(PduIdType, DCM_CODE) Dcm_Dsl_TxMsg_GetTxPduID
(
    const uint16 u2PduMapIndex
)
{
    PduIdType u2_Result;
    uint16    u2_RowIndex;
    uint16    u2_ConnectionIndex;
    P2CONST(AB_83_ConstV Dcm_Dsl_ProtocolTxType, AUTOMATIC, DCM_APPL_CONST) pt_ProtocolTx;

    u2_Result = DCM_DSL_INVALID_U2_DATA;
    Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);

    pt_ProtocolTx = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolTx;
    if( pt_ProtocolTx != NULL_PTR )
    {
        u2_Result = pt_ProtocolTx->TxPdu;
    }

    return u2_Result;

}
#endif /* DCM_DSL_ROE_EXTENDED_ENABLE == STD_OFF */

#if( DCM_DSL_ROE_EXTENDED_ENABLE == STD_ON )
static FUNC(PduIdType, DCM_CODE) Dcm_Dsl_TxMsg_GetTxPduID
(
    const uint16 u2PduMapIndex
)
{
    boolean   b_ServiceToRespondTo;
    boolean   b_MainConnection;
    PduIdType u2_Result;
    uint16    u2_RowIndex;
    uint16    u2_ConnectionIndex;
    P2CONST(AB_83_ConstV Dcm_Dsl_ProtocolTxType, AUTOMATIC, DCM_APPL_CONST) pt_ProtocolTx;
    P2CONST(AB_83_ConstV Dcm_Dsl_SubConnectionType, AUTOMATIC, DCM_APPL_CONST) pt_ResponseOnEvent;

    u2_Result        = DCM_DSL_INVALID_U2_DATA;
    b_MainConnection = (boolean)FALSE;
    Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);

    b_ServiceToRespondTo = Dcm_Dsl_Ctrl_IsServiceToRespondTo(u2PduMapIndex);
    if( b_ServiceToRespondTo == (boolean)TRUE )
    {
        pt_ResponseOnEvent = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptRoeConnectionRef;
        if( pt_ResponseOnEvent != NULL_PTR )
        {
            if( pt_ResponseOnEvent->TxPdu != DCM_DSL_INVALID_U2_DATA )
            {
                u2_Result = pt_ResponseOnEvent->TxPdu;
            }
            else
            {
                b_MainConnection = (boolean)TRUE;
            }
        }
    }
    else
    {
        b_MainConnection = (boolean)TRUE;
    }

    if( b_MainConnection == (boolean)TRUE )
    {
        pt_ProtocolTx = Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolTx;
        if( pt_ProtocolTx != NULL_PTR )
        {
            u2_Result = pt_ProtocolTx->TxPdu;
        }
    }

    return u2_Result;

}
#endif /* DCM_DSL_ROE_EXTENDED_ENABLE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_GetPduMapIndexByTxConfPduID                */
/* Description   | This function gets PduMapIndex from txConfirmationId.    */
/* Preconditions | none                                                     */
/* Parameters    | [in] uvTxConfPduId : Transimit Confirmation PduID        */
/* Return Value  | uint16                                                   */
/*               |       0x000~0xFFFEU           : Valid value              */
/*               |       DCM_DSL_INVALID_U2_DATA : Invalid value            */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_DSL_ROE_EXTENDED_ENABLE == STD_OFF )
static FUNC(uint16, DCM_CODE) Dcm_Dsl_TxMsg_GetPduMapIndexByTxConfPduID
(
    const PduIdType uvTxConfPduId
)
{
    P2CONST(AB_83_ConstV Dcm_Dsl_RowType, AUTOMATIC, DCM_APPL_CONST)        pt_Row;
    P2CONST(AB_83_ConstV Dcm_Dsl_ProtocolTxType, AUTOMATIC, DCM_APPL_CONST) pt_ProtocolTx;
    uint16          u2_RowIndex;
    uint16          u2_ConnectionIndex;
    uint16          u2_PduMapIndex;
    uint16          u2_Result;
    uint16          u2_PduIdNumMax;

    u2_PduIdNumMax = Dcm_Dsl_u2PduIdNum;
    pt_Row         = &Dcm_Dsl_stRow[0];
    u2_Result      = DCM_DSL_INVALID_U2_DATA;

    /* Get PduMapIndex by TxConfPduId */
    for( u2_PduMapIndex = (uint16)0U; u2_PduMapIndex < u2_PduIdNumMax; u2_PduMapIndex++ )
    {
        Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2_PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);
        pt_ProtocolTx = pt_Row[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolTx;
        if( pt_ProtocolTx != NULL_PTR )
        {
            if( pt_ProtocolTx->TxConfirmationPduId == uvTxConfPduId )
            {
                u2_Result = Dcm_Dsl_TxAbt_GetSrcPduMapIndex(u2_PduMapIndex);
                break;
            }
        }
    }

    return u2_Result;
}
#endif /* DCM_DSL_ROE_EXTENDED_ENABLE == STD_OFF */

#if( DCM_DSL_ROE_EXTENDED_ENABLE == STD_ON )
static FUNC(uint16, DCM_CODE) Dcm_Dsl_TxMsg_GetPduMapIndexByTxConfPduID
(
    const PduIdType uvTxConfPduId
)
{
    P2CONST(AB_83_ConstV Dcm_Dsl_RowType, AUTOMATIC, DCM_APPL_CONST)        pt_Row;
    P2CONST(AB_83_ConstV Dcm_Dsl_ProtocolTxType, AUTOMATIC, DCM_APPL_CONST) pt_ProtocolTx;
    uint16          u2_RowIndex;
    uint16          u2_ConnectionIndex;
    uint16          u2_PduMapIndex;
    uint16          u2_RoeIndex;
    uint16          u2_Result;
    uint16          u2_PduIdNumMax;
    uint16          u2_RoeIdNumMax;
    boolean         b_ServiceToRespondTo;

    u2_PduIdNumMax = Dcm_Dsl_u2PduIdNum;
    u2_RoeIdNumMax = Dcm_Dsl_u2RoePduIdNum;
    pt_Row         = &Dcm_Dsl_stRow[0];
    u2_Result      = DCM_DSL_INVALID_U2_DATA;

    u2_PduMapIndex       = Dcm_Dsl_Ctrl_GetPduMapIndex4Tx();
    b_ServiceToRespondTo = Dcm_Dsl_Ctrl_IsServiceToRespondTo(u2_PduMapIndex);
    if( b_ServiceToRespondTo == (boolean)TRUE )
    {
        for( u2_RoeIndex = (uint16)0U; u2_RoeIndex < u2_RoeIdNumMax; u2_RoeIndex++ )
        {
            if( Dcm_Dsl_RoeMapTable[u2_RoeIndex].TxConfirmationPduId == uvTxConfPduId )
            {
                u2_PduMapIndex = Dcm_Dsl_RoeMapTable[u2_RoeIndex].u2PduMapIndex;
                if( u2_PduMapIndex != DCM_DSL_INVALID_U2_DATA )
                {
                    u2_Result = Dcm_Dsl_TxAbt_GetSrcPduMapIndex(u2_PduMapIndex);
                    break;
                }
            }
        }
    }
    else
    {
        /* Get PduMapIndex by TxConfPduId */
        for( u2_PduMapIndex = (uint16)0U; u2_PduMapIndex < u2_PduIdNumMax; u2_PduMapIndex++ )
        {
            Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2_PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);
            pt_ProtocolTx = pt_Row[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].ptProtocolTx;
            if( pt_ProtocolTx != NULL_PTR )
            {
                if( pt_ProtocolTx->TxConfirmationPduId == uvTxConfPduId )
                {
                    u2_Result = Dcm_Dsl_TxAbt_GetSrcPduMapIndex(u2_PduMapIndex);
                    break;
                }
            }
        }
    }

    return u2_Result;
}
#endif /* DCM_DSL_ROE_EXTENDED_ENABLE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_IsExtendedPduLength                        */
/* Description   | Check if the PDU length is extended.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | boolean                                                  */
/*               |       TRUE : Extended Pdu Length                         */
/*               |      FALSE : Standard Pdu Length                         */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_Dsl_TxMsg_IsExtendedPduLength
(
    const uint16 u2PduMapIndex
)
{
    uint16  u2_RowIndex;
    uint16  u2_ConnectionIndex;

    Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);
    return Dcm_Dsl_stRow[u2_RowIndex].ptConnection[u2_ConnectionIndex].ptMainConnection[0].bExtPduLength;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_IsNoResPduID                               */
/* Description   | Check PduId that is prohibited Response.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex : PduMapIndex Value                   */
/* Return Value  | boolean                                                  */
/*               |       TRUE : Response prohibition                        */
/*               |      FALSE : Response permission                         */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_Dsl_TxMsg_IsNoResPduID
(
    const uint16 u2PduMapIndex
)
{
    PduIdType  uv_TxPduId;
    boolean    b_Result;
    boolean    b_NoResPduId;

    b_Result = (boolean)FALSE;

    uv_TxPduId = Dcm_Dsl_TxMsg_GetTxPduID(u2PduMapIndex);
    if( uv_TxPduId == DCM_DSL_INVALID_U2_DATA )
    {
        b_Result = (boolean)TRUE;
    }
    else
    {
        b_NoResPduId = Dcm_Dsl_Ctrl_IsNoResPduID(u2PduMapIndex);
        if( b_NoResPduId == (boolean)TRUE )
        {
            b_Result = (boolean)TRUE;
        }
    }
    return b_Result;
}

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_TxMsg_GetMaximumResponseSize                     */
/* Description   | Get a MaximumResponseSize Value.                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | AB_83_DcmPduLengthType                                   */
/*               |       1U~65535U : MaximumResponseSize Value              */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(AB_83_DcmPduLengthType, DCM_CODE) Dcm_Dsl_TxMsg_GetMaximumResponseSize
(
    const uint16 u2PduMapIndex
)
{
    uint16        u2_RowIndex;
    uint16        u2_ConnectionIndex;

    Dcm_Dsl_Ctrl_ConvPMIdxToCnctIdx(u2PduMapIndex, &u2_RowIndex, &u2_ConnectionIndex);
    return (AB_83_DcmPduLengthType)Dcm_Dsl_stRow[u2_RowIndex].u2ProtocolMaximumResponseSize;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2022-08-30                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
