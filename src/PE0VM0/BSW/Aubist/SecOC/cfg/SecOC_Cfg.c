/* SecOC_Cfg_c_v2-1-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC/Cfg/CODE                                             */
/*--------------------------------------------------------------------------*/
/* Notes                                                                    */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "SecOC_Cfg.h"
#include <Csm.h>
#include <SecOC_CD_FV.h>
#include "SecOC_User.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/



/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CONST_CONFIG
#include <SecOC_MemMap.h>

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    CONST(uint16, SECOC_CONST_CONFIG) SecOC_RxPduProcessingMax = SECOC_RX_PDU_PROCESSING_MAX;
#endif
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    CONST(uint16, SECOC_CONST_CONFIG) SecOC_TxPduProcessingMax = SECOC_TX_PDU_PROCESSING_MAX;
#endif
#if (SECOC_VERIFICATION_STATUS_CALLOUT_MAX > 0U)
    CONST(uint16, SECOC_CONST_CONFIG) SecOC_VerStaCoMax = SECOC_VERIFICATION_STATUS_CALLOUT_MAX;
#endif
CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_BusMax = SECOC_AB_BUS_MAX;
#if (SECOC_AB_BUS_FULL_MAX > 0U)
    CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_BusFullMax = SECOC_AB_BUS_FULL_MAX;
#endif
#if (SECOC_AB_BUS_TRUNC_MAX > 0U)
    CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_BusTruncMax = SECOC_AB_BUS_TRUNC_MAX;
#endif
#if (SECOC_AB_FULL_FRESHNESS_VALUE_CALLOUT_MAX > 0U)
    CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_FullFvCoMax = SECOC_AB_FULL_FRESHNESS_VALUE_CALLOUT_MAX;
#endif
#if (SECOC_AB_REPORT_ERROR_CALLOUT_MAX > 0U)
    CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_RepErrCoMax = SECOC_AB_REPORT_ERROR_CALLOUT_MAX;
#endif
#if (SECOC_AB_RX_PDU_FULLFV_MAX > 0U)
    CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_RxPduFullFvMax = SECOC_AB_RX_PDU_FULLFV_MAX;
#endif
#if (SECOC_AB_TX_PDU_FULLFV_MAX > 0U)
    CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_TxPduFullFvMax = SECOC_AB_TX_PDU_FULLFV_MAX;
#endif
#if (SECOC_AB_RX_PDU_TRUNCFV_MAX > 0U)
    CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_RxPduTruncFvMax = SECOC_AB_RX_PDU_TRUNCFV_MAX;
#endif
#if (SECOC_AB_TX_PDU_TRUNCFV_MAX > 0U)
    CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_TxPduTruncFvMax = SECOC_AB_TX_PDU_TRUNCFV_MAX;
#endif
#if (SECOC_AB_RXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
    CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_RxMsgBusyDestCoMax = SECOC_AB_RXMSG_BUSY_DESTRUCTION_CALLOUT_MAX;
#endif
#if (SECOC_AB_TXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
    CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_TxMsgBusyDestCoMax = SECOC_AB_TXMSG_BUSY_DESTRUCTION_CALLOUT_MAX;
#endif
#if (SECOC_AB_RXMSG_OVERFLOW_DESTRUCTION_CALLOUT_MAX > 0U)
    CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_RxMsgOvfDestCoMax = SECOC_AB_RXMSG_OVERFLOW_DESTRUCTION_CALLOUT_MAX;
#endif
#if (SECOC_AB_VERIFICATION_FINAL_STATUS_CALLOUT_MAX > 0U)
    CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_VerFinStaCoMax = SECOC_AB_VERIFICATION_FINAL_STATUS_CALLOUT_MAX;
#endif
#if (SECOC_DEFAULT_AUTH_INFO == STD_ON)
    CONST(uint8, SECOC_CONST_CONFIG) SecOC_DefaultAuthInfoPattern = SECOC_DEFAULT_AUTHENTICATION_INFORMATION_PATTERN;
#endif

CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_ProcessingCount = 4U;
CONST(uint16, SECOC_CONST_CONFIG) SecOC_Ab_TxProcessingCount = 3U;

CONST(uint32, SECOC_CONST_CONFIG) SecOC_Ab_RxAuthTpCopyTotalSize = 1U;
CONST(uint32, SECOC_CONST_CONFIG) SecOC_Ab_TxAuthTpCopyTotalSize = 1U;



CONST(SecOC_SPduTxConfirmationType, SECOC_CONST_CONFIG) SecOC_Ab_FullFVCallout[SECOC_AB_FULL_FRESHNESS_VALUE_CALLOUT_MAX] = 
{
    &SecOC_Callout_User_FullFreshnessValue

};



CONST(SecOC_Ab_BusCollectionType, SECOC_CONST_CONFIG) SecOC_Ab_BusCollection[SECOC_AB_BUS_MAX] = 
{
    {
      0U, /* Ab_BusID */
      SECOC_AB_PROTOCOL_CAN, /* Ab_Protocol */
      0U, /* Ab_VerifyStartCount */
      0U, /* Ab_FreshnessValueID */
      15U, /* Ab_ClearAcceptanceWindow */
      0U, /* dummy1 */
      SECOC_AB_FV_FULL, /* Ab_FvType */
      0U, /* Ab_FvTypeIndex */
      16U, /* Ab_DataIdLength */
      0U /* dummy2 */
    },
    {
      1U, /* Ab_BusID */
      SECOC_AB_PROTOCOL_CAN, /* Ab_Protocol */
      0U, /* Ab_VerifyStartCount */
      1U, /* Ab_FreshnessValueID */
      15U, /* Ab_ClearAcceptanceWindow */
      0U, /* dummy1 */
      SECOC_AB_FV_FULL, /* Ab_FvType */
      1U, /* Ab_FvTypeIndex */
      16U, /* Ab_DataIdLength */
      0U /* dummy2 */
    },
    {
      2U, /* Ab_BusID */
      SECOC_AB_PROTOCOL_CAN, /* Ab_Protocol */
      0U, /* Ab_VerifyStartCount */
      2U, /* Ab_FreshnessValueID */
      15U, /* Ab_ClearAcceptanceWindow */
      0U, /* dummy1 */
      SECOC_AB_FV_FULL, /* Ab_FvType */
      2U, /* Ab_FvTypeIndex */
      16U, /* Ab_DataIdLength */
      0U /* dummy2 */
    },
    {
      3U, /* Ab_BusID */
      SECOC_AB_PROTOCOL_CAN, /* Ab_Protocol */
      0U, /* Ab_VerifyStartCount */
      3U, /* Ab_FreshnessValueID */
      15U, /* Ab_ClearAcceptanceWindow */
      0U, /* dummy1 */
      SECOC_AB_FV_FULL, /* Ab_FvType */
      3U, /* Ab_FvTypeIndex */
      16U, /* Ab_DataIdLength */
      0U /* dummy2 */
    }
};

CONST(uint16, SECOC_CONST_CONFIG) SecOC_JobId2MsgTblIdx[SECOC_JOBID_2_MSG_TBL_IDX_MAX] =
{
    0U,
    1U,
    2U,
    3U,
    4U,
    5U,
    6U,
    7U,
    8U,
    9U,
    10U,
    11U,
    12U,
    13U,
    14U,
    15U
};


CONST(SecOC_TxPduProcessingType, SECOC_CONST_CONFIG) SecOC_TxPduProcessing[SECOC_TX_PDU_PROCESSING_MAX] = 
{
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        1U, /* AuthenticationBuildAttempts */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        722U, /* Ab_DataId */
        53U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        0U, /* Ab_ProtDataPaddingSize */
        { 0U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* TxAuthServiceConfigRef */
        32U, /* SameBufferPduRef */
        0U, /* Ab_BufferStartOffset */
        32U, /* Ab_TxMakeAuthBufferSize */
        0U, /* Ab_TxBufferStartOffset */
        &SecOC_CD_FV_SPduTxConfirmation, /* Ab_SecuredPduTransmitFuncName */
        0U, /* TxAuthenticLayerPduId */
        0U, /* TxSecuredLayerPduId */
        &SecOC_CD_FV_GetTxFreshnessTruncData, /* Ab_FreshnessValueFuncName */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_TxAuthTpCopySize */
        0U, /* dummy1 */
        0U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_IFPDU, /* TxAuthPduType */
        SECOC_IFPDU, /* Ab_TxSecuredPduType */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        0U, /* Ab_TxAuthTpCopyAttempts */
        0U, /* Ab_TxAuthenticLayerPduRefId */
        0U, /* Ab_TxSecuredLayerPduRefId */
        1U, /* Ab_TxTransmitAttempts */
        { NULL_PTR }, /* Ab_TxMsgBusyDestructionCallout */
        0U /* Ab_CsmReqSaSizeMax */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        1U, /* AuthenticationBuildAttempts */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        724U, /* Ab_DataId */
        54U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        0U, /* Ab_ProtDataPaddingSize */
        { 1U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* TxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        32U, /* Ab_BufferStartOffset */
        64U, /* Ab_TxMakeAuthBufferSize */
        32U, /* Ab_TxBufferStartOffset */
        &SecOC_CD_FV_SPduTxConfirmation, /* Ab_SecuredPduTransmitFuncName */
        1U, /* TxAuthenticLayerPduId */
        1U, /* TxSecuredLayerPduId */
        &SecOC_CD_FV_GetTxFreshnessTruncData, /* Ab_FreshnessValueFuncName */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_TxAuthTpCopySize */
        0U, /* dummy1 */
        1U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_IFPDU, /* TxAuthPduType */
        SECOC_IFPDU, /* Ab_TxSecuredPduType */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        0U, /* Ab_TxAuthTpCopyAttempts */
        1U, /* Ab_TxAuthenticLayerPduRefId */
        1U, /* Ab_TxSecuredLayerPduRefId */
        1U, /* Ab_TxTransmitAttempts */
        { NULL_PTR }, /* Ab_TxMsgBusyDestructionCallout */
        0U /* Ab_CsmReqSaSizeMax */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        1U, /* AuthenticationBuildAttempts */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        725U, /* Ab_DataId */
        55U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        0U, /* Ab_ProtDataPaddingSize */
        { 2U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* TxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        96U, /* Ab_BufferStartOffset */
        64U, /* Ab_TxMakeAuthBufferSize */
        96U, /* Ab_TxBufferStartOffset */
        &SecOC_CD_FV_SPduTxConfirmation, /* Ab_SecuredPduTransmitFuncName */
        2U, /* TxAuthenticLayerPduId */
        2U, /* TxSecuredLayerPduId */
        &SecOC_CD_FV_GetTxFreshnessTruncData, /* Ab_FreshnessValueFuncName */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_TxAuthTpCopySize */
        0U, /* dummy1 */
        2U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_IFPDU, /* TxAuthPduType */
        SECOC_IFPDU, /* Ab_TxSecuredPduType */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        0U, /* Ab_TxAuthTpCopyAttempts */
        2U, /* Ab_TxAuthenticLayerPduRefId */
        2U, /* Ab_TxSecuredLayerPduRefId */
        1U, /* Ab_TxTransmitAttempts */
        { NULL_PTR }, /* Ab_TxMsgBusyDestructionCallout */
        0U /* Ab_CsmReqSaSizeMax */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        1U, /* AuthenticationBuildAttempts */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        726U, /* Ab_DataId */
        56U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        0U, /* Ab_ProtDataPaddingSize */
        { 3U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* TxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        160U, /* Ab_BufferStartOffset */
        64U, /* Ab_TxMakeAuthBufferSize */
        160U, /* Ab_TxBufferStartOffset */
        &SecOC_CD_FV_SPduTxConfirmation, /* Ab_SecuredPduTransmitFuncName */
        3U, /* TxAuthenticLayerPduId */
        3U, /* TxSecuredLayerPduId */
        &SecOC_CD_FV_GetTxFreshnessTruncData, /* Ab_FreshnessValueFuncName */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_TxAuthTpCopySize */
        0U, /* dummy1 */
        3U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_IFPDU, /* TxAuthPduType */
        SECOC_IFPDU, /* Ab_TxSecuredPduType */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        0U, /* Ab_TxAuthTpCopyAttempts */
        3U, /* Ab_TxAuthenticLayerPduRefId */
        3U, /* Ab_TxSecuredLayerPduRefId */
        1U, /* Ab_TxTransmitAttempts */
        { NULL_PTR }, /* Ab_TxMsgBusyDestructionCallout */
        0U /* Ab_CsmReqSaSizeMax */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        1U, /* AuthenticationBuildAttempts */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        727U, /* Ab_DataId */
        57U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        0U, /* Ab_ProtDataPaddingSize */
        { 4U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* TxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        224U, /* Ab_BufferStartOffset */
        64U, /* Ab_TxMakeAuthBufferSize */
        224U, /* Ab_TxBufferStartOffset */
        &SecOC_CD_FV_SPduTxConfirmation, /* Ab_SecuredPduTransmitFuncName */
        4U, /* TxAuthenticLayerPduId */
        4U, /* TxSecuredLayerPduId */
        &SecOC_CD_FV_GetTxFreshnessTruncData, /* Ab_FreshnessValueFuncName */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_TxAuthTpCopySize */
        0U, /* dummy1 */
        4U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_IFPDU, /* TxAuthPduType */
        SECOC_IFPDU, /* Ab_TxSecuredPduType */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        0U, /* Ab_TxAuthTpCopyAttempts */
        4U, /* Ab_TxAuthenticLayerPduRefId */
        4U, /* Ab_TxSecuredLayerPduRefId */
        1U, /* Ab_TxTransmitAttempts */
        { NULL_PTR }, /* Ab_TxMsgBusyDestructionCallout */
        0U /* Ab_CsmReqSaSizeMax */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        1U, /* AuthenticationBuildAttempts */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        735U, /* Ab_DataId */
        58U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        0U, /* Ab_ProtDataPaddingSize */
        { 5U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* TxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        288U, /* Ab_BufferStartOffset */
        64U, /* Ab_TxMakeAuthBufferSize */
        288U, /* Ab_TxBufferStartOffset */
        &SecOC_CD_FV_SPduTxConfirmation, /* Ab_SecuredPduTransmitFuncName */
        5U, /* TxAuthenticLayerPduId */
        5U, /* TxSecuredLayerPduId */
        &SecOC_CD_FV_GetTxFreshnessTruncData, /* Ab_FreshnessValueFuncName */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_TxAuthTpCopySize */
        0U, /* dummy1 */
        5U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_IFPDU, /* TxAuthPduType */
        SECOC_IFPDU, /* Ab_TxSecuredPduType */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        0U, /* Ab_TxAuthTpCopyAttempts */
        5U, /* Ab_TxAuthenticLayerPduRefId */
        5U, /* Ab_TxSecuredLayerPduRefId */
        1U, /* Ab_TxTransmitAttempts */
        { NULL_PTR }, /* Ab_TxMsgBusyDestructionCallout */
        0U /* Ab_CsmReqSaSizeMax */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        1U, /* AuthenticationBuildAttempts */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        736U, /* Ab_DataId */
        59U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        0U, /* Ab_ProtDataPaddingSize */
        { 6U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* TxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        352U, /* Ab_BufferStartOffset */
        64U, /* Ab_TxMakeAuthBufferSize */
        352U, /* Ab_TxBufferStartOffset */
        &SecOC_CD_FV_SPduTxConfirmation, /* Ab_SecuredPduTransmitFuncName */
        6U, /* TxAuthenticLayerPduId */
        6U, /* TxSecuredLayerPduId */
        &SecOC_CD_FV_GetTxFreshnessTruncData, /* Ab_FreshnessValueFuncName */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_TxAuthTpCopySize */
        0U, /* dummy1 */
        6U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_IFPDU, /* TxAuthPduType */
        SECOC_IFPDU, /* Ab_TxSecuredPduType */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        0U, /* Ab_TxAuthTpCopyAttempts */
        6U, /* Ab_TxAuthenticLayerPduRefId */
        6U, /* Ab_TxSecuredLayerPduRefId */
        1U, /* Ab_TxTransmitAttempts */
        { NULL_PTR }, /* Ab_TxMsgBusyDestructionCallout */
        0U /* Ab_CsmReqSaSizeMax */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        1U, /* AuthenticationBuildAttempts */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        737U, /* Ab_DataId */
        60U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        0U, /* Ab_ProtDataPaddingSize */
        { 7U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* TxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        416U, /* Ab_BufferStartOffset */
        64U, /* Ab_TxMakeAuthBufferSize */
        416U, /* Ab_TxBufferStartOffset */
        &SecOC_CD_FV_SPduTxConfirmation, /* Ab_SecuredPduTransmitFuncName */
        7U, /* TxAuthenticLayerPduId */
        7U, /* TxSecuredLayerPduId */
        &SecOC_CD_FV_GetTxFreshnessTruncData, /* Ab_FreshnessValueFuncName */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_TxAuthTpCopySize */
        0U, /* dummy1 */
        7U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_IFPDU, /* TxAuthPduType */
        SECOC_IFPDU, /* Ab_TxSecuredPduType */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        0U, /* Ab_TxAuthTpCopyAttempts */
        7U, /* Ab_TxAuthenticLayerPduRefId */
        7U, /* Ab_TxSecuredLayerPduRefId */
        1U, /* Ab_TxTransmitAttempts */
        { NULL_PTR }, /* Ab_TxMsgBusyDestructionCallout */
        0U /* Ab_CsmReqSaSizeMax */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        1U, /* AuthenticationBuildAttempts */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        738U, /* Ab_DataId */
        61U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        0U, /* Ab_ProtDataPaddingSize */
        { 8U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* TxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        480U, /* Ab_BufferStartOffset */
        64U, /* Ab_TxMakeAuthBufferSize */
        480U, /* Ab_TxBufferStartOffset */
        &SecOC_CD_FV_SPduTxConfirmation, /* Ab_SecuredPduTransmitFuncName */
        8U, /* TxAuthenticLayerPduId */
        8U, /* TxSecuredLayerPduId */
        &SecOC_CD_FV_GetTxFreshnessTruncData, /* Ab_FreshnessValueFuncName */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_TxAuthTpCopySize */
        0U, /* dummy1 */
        8U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_IFPDU, /* TxAuthPduType */
        SECOC_IFPDU, /* Ab_TxSecuredPduType */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        0U, /* Ab_TxAuthTpCopyAttempts */
        8U, /* Ab_TxAuthenticLayerPduRefId */
        8U, /* Ab_TxSecuredLayerPduRefId */
        1U, /* Ab_TxTransmitAttempts */
        { NULL_PTR }, /* Ab_TxMsgBusyDestructionCallout */
        0U /* Ab_CsmReqSaSizeMax */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        1U, /* AuthenticationBuildAttempts */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        751U, /* Ab_DataId */
        62U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        0U, /* Ab_ProtDataPaddingSize */
        { 9U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* TxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        544U, /* Ab_BufferStartOffset */
        64U, /* Ab_TxMakeAuthBufferSize */
        544U, /* Ab_TxBufferStartOffset */
        &SecOC_CD_FV_SPduTxConfirmation, /* Ab_SecuredPduTransmitFuncName */
        9U, /* TxAuthenticLayerPduId */
        9U, /* TxSecuredLayerPduId */
        &SecOC_CD_FV_GetTxFreshnessTruncData, /* Ab_FreshnessValueFuncName */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_TxAuthTpCopySize */
        0U, /* dummy1 */
        9U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_IFPDU, /* TxAuthPduType */
        SECOC_IFPDU, /* Ab_TxSecuredPduType */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        0U, /* Ab_TxAuthTpCopyAttempts */
        9U, /* Ab_TxAuthenticLayerPduRefId */
        9U, /* Ab_TxSecuredLayerPduRefId */
        1U, /* Ab_TxTransmitAttempts */
        { NULL_PTR }, /* Ab_TxMsgBusyDestructionCallout */
        0U /* Ab_CsmReqSaSizeMax */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        1U, /* AuthenticationBuildAttempts */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        752U, /* Ab_DataId */
        63U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        0U, /* Ab_ProtDataPaddingSize */
        { 10U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* TxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        608U, /* Ab_BufferStartOffset */
        64U, /* Ab_TxMakeAuthBufferSize */
        608U, /* Ab_TxBufferStartOffset */
        &SecOC_CD_FV_SPduTxConfirmation, /* Ab_SecuredPduTransmitFuncName */
        10U, /* TxAuthenticLayerPduId */
        10U, /* TxSecuredLayerPduId */
        &SecOC_CD_FV_GetTxFreshnessTruncData, /* Ab_FreshnessValueFuncName */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_TxAuthTpCopySize */
        0U, /* dummy1 */
        10U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_IFPDU, /* TxAuthPduType */
        SECOC_IFPDU, /* Ab_TxSecuredPduType */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        0U, /* Ab_TxAuthTpCopyAttempts */
        10U, /* Ab_TxAuthenticLayerPduRefId */
        10U, /* Ab_TxSecuredLayerPduRefId */
        1U, /* Ab_TxTransmitAttempts */
        { NULL_PTR }, /* Ab_TxMsgBusyDestructionCallout */
        0U /* Ab_CsmReqSaSizeMax */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        1U, /* AuthenticationBuildAttempts */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        754U, /* Ab_DataId */
        64U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        0U, /* Ab_ProtDataPaddingSize */
        { 11U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* TxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        672U, /* Ab_BufferStartOffset */
        64U, /* Ab_TxMakeAuthBufferSize */
        672U, /* Ab_TxBufferStartOffset */
        &SecOC_CD_FV_SPduTxConfirmation, /* Ab_SecuredPduTransmitFuncName */
        11U, /* TxAuthenticLayerPduId */
        11U, /* TxSecuredLayerPduId */
        &SecOC_CD_FV_GetTxFreshnessTruncData, /* Ab_FreshnessValueFuncName */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_TxAuthTpCopySize */
        0U, /* dummy1 */
        11U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_IFPDU, /* TxAuthPduType */
        SECOC_IFPDU, /* Ab_TxSecuredPduType */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        0U, /* Ab_TxAuthTpCopyAttempts */
        11U, /* Ab_TxAuthenticLayerPduRefId */
        11U, /* Ab_TxSecuredLayerPduRefId */
        1U, /* Ab_TxTransmitAttempts */
        { NULL_PTR }, /* Ab_TxMsgBusyDestructionCallout */
        0U /* Ab_CsmReqSaSizeMax */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        1U, /* AuthenticationBuildAttempts */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        757U, /* Ab_DataId */
        65U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        0U, /* Ab_ProtDataPaddingSize */
        { 12U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* TxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        736U, /* Ab_BufferStartOffset */
        64U, /* Ab_TxMakeAuthBufferSize */
        736U, /* Ab_TxBufferStartOffset */
        &SecOC_CD_FV_SPduTxConfirmation, /* Ab_SecuredPduTransmitFuncName */
        12U, /* TxAuthenticLayerPduId */
        12U, /* TxSecuredLayerPduId */
        &SecOC_CD_FV_GetTxFreshnessTruncData, /* Ab_FreshnessValueFuncName */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_TxAuthTpCopySize */
        0U, /* dummy1 */
        12U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_IFPDU, /* TxAuthPduType */
        SECOC_IFPDU, /* Ab_TxSecuredPduType */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        0U, /* Ab_TxAuthTpCopyAttempts */
        12U, /* Ab_TxAuthenticLayerPduRefId */
        12U, /* Ab_TxSecuredLayerPduRefId */
        1U, /* Ab_TxTransmitAttempts */
        { NULL_PTR }, /* Ab_TxMsgBusyDestructionCallout */
        0U /* Ab_CsmReqSaSizeMax */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        1U, /* AuthenticationBuildAttempts */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        819U, /* Ab_DataId */
        66U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        0U, /* Ab_ProtDataPaddingSize */
        { 13U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* TxAuthServiceConfigRef */
        32U, /* SameBufferPduRef */
        800U, /* Ab_BufferStartOffset */
        32U, /* Ab_TxMakeAuthBufferSize */
        800U, /* Ab_TxBufferStartOffset */
        &SecOC_CD_FV_SPduTxConfirmation, /* Ab_SecuredPduTransmitFuncName */
        13U, /* TxAuthenticLayerPduId */
        13U, /* TxSecuredLayerPduId */
        &SecOC_CD_FV_GetTxFreshnessTruncData, /* Ab_FreshnessValueFuncName */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_TxAuthTpCopySize */
        0U, /* dummy1 */
        13U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_IFPDU, /* TxAuthPduType */
        SECOC_IFPDU, /* Ab_TxSecuredPduType */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        0U, /* Ab_TxAuthTpCopyAttempts */
        13U, /* Ab_TxAuthenticLayerPduRefId */
        13U, /* Ab_TxSecuredLayerPduRefId */
        1U, /* Ab_TxTransmitAttempts */
        { NULL_PTR }, /* Ab_TxMsgBusyDestructionCallout */
        0U /* Ab_CsmReqSaSizeMax */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        1U, /* AuthenticationBuildAttempts */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        1006U, /* Ab_DataId */
        67U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        0U, /* Ab_ProtDataPaddingSize */
        { 14U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* TxAuthServiceConfigRef */
        32U, /* SameBufferPduRef */
        832U, /* Ab_BufferStartOffset */
        32U, /* Ab_TxMakeAuthBufferSize */
        832U, /* Ab_TxBufferStartOffset */
        &SecOC_CD_FV_SPduTxConfirmation, /* Ab_SecuredPduTransmitFuncName */
        14U, /* TxAuthenticLayerPduId */
        14U, /* TxSecuredLayerPduId */
        &SecOC_CD_FV_GetTxFreshnessTruncData, /* Ab_FreshnessValueFuncName */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_TxAuthTpCopySize */
        0U, /* dummy1 */
        14U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_IFPDU, /* TxAuthPduType */
        SECOC_IFPDU, /* Ab_TxSecuredPduType */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        0U, /* Ab_TxAuthTpCopyAttempts */
        14U, /* Ab_TxAuthenticLayerPduRefId */
        14U, /* Ab_TxSecuredLayerPduRefId */
        1U, /* Ab_TxTransmitAttempts */
        { NULL_PTR }, /* Ab_TxMsgBusyDestructionCallout */
        0U /* Ab_CsmReqSaSizeMax */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        2U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        1U, /* AuthenticationBuildAttempts */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        589U, /* Ab_DataId */
        74U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        0U, /* Ab_ProtDataPaddingSize */
        { 15U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* TxAuthServiceConfigRef */
        32U, /* SameBufferPduRef */
        864U, /* Ab_BufferStartOffset */
        32U, /* Ab_TxMakeAuthBufferSize */
        864U, /* Ab_TxBufferStartOffset */
        &SecOC_CD_FV_SPduTxConfirmation, /* Ab_SecuredPduTransmitFuncName */
        15U, /* TxAuthenticLayerPduId */
        15U, /* TxSecuredLayerPduId */
        &SecOC_CD_FV_GetTxFreshnessTruncData, /* Ab_FreshnessValueFuncName */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_TxAuthTpCopySize */
        0U, /* dummy1 */
        15U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_IFPDU, /* TxAuthPduType */
        SECOC_IFPDU, /* Ab_TxSecuredPduType */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        0U, /* Ab_TxAuthTpCopyAttempts */
        15U, /* Ab_TxAuthenticLayerPduRefId */
        15U, /* Ab_TxSecuredLayerPduRefId */
        1U, /* Ab_TxTransmitAttempts */
        { NULL_PTR }, /* Ab_TxMsgBusyDestructionCallout */
        0U /* Ab_CsmReqSaSizeMax */
    }

};

CONST(SecOC_Ab_BusId2SecuredMsgIdxType, SECOC_CONST_CONFIG) SecOC_Ab_BusId2SecuredMsgIdxLists[SECOC_AB_BUS_MAX] = 
{
    {        /* Bus[0] */
        15U, /* Ab_TxSecuredMsgCount */
        {    /* Ab_TxSecuredMsgIdxList */
            0U,
            1U,
            2U,
            3U,
            4U,
            5U,
            6U,
            7U,
            8U,
            9U,
            10U,
            11U,
            12U,
            13U,
            14U
        }
    },
    {        /* Bus[1] */
        0U, /* Ab_TxSecuredMsgCount */
        {    /* Ab_TxSecuredMsgIdxList */
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U
        }
    },
    {        /* Bus[2] */
        1U, /* Ab_TxSecuredMsgCount */
        {    /* Ab_TxSecuredMsgIdxList */
            15U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U
        }
    },
    {        /* Bus[3] */
        0U, /* Ab_TxSecuredMsgCount */
        {    /* Ab_TxSecuredMsgIdxList */
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U,
            0U
        }
    }
};

#define SECOC_STOP_SEC_CONST_CONFIG
#include <SecOC_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

/****************************************************************************/
/* Function Name | SecOC_Config_Init                                        */
/* Description   | SecOC Config initialize Function                         */
/* Preconditions |                                                          */
/* Parameters    | SecOC_ConfigType *SecOC_ConfigData                       */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Config_Init
(
    P2CONST(SecOC_ConfigType, AUTOMATIC, SECOC_APPL_DATA) SecOC_ConfigData
)
{
    return ;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name |                                                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    |                                                          */
/* Return Value  |                                                          */
/* Notes         |                                                          */
/****************************************************************************/


#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>


/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-1-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

