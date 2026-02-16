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
#include "oxsec_aubif_secoc.h"

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
    &vd_g_oXSECAubIfSecFullFVAck

};



CONST(SecOC_Ab_BusCollectionType, SECOC_CONST_CONFIG) SecOC_Ab_BusCollection[SECOC_AB_BUS_MAX] = 
{
    {
      0U, /* Ab_BusID */
      SECOC_AB_PROTOCOL_CAN, /* Ab_Protocol */
      0U, /* Ab_VerifyStartCount */
      45U, /* Ab_FreshnessValueID */
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
      46U, /* Ab_FreshnessValueID */
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
      47U, /* Ab_FreshnessValueID */
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
      48U, /* Ab_FreshnessValueID */
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
    15U,
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
    15U,
    16U,
    17U,
    18U,
    19U,
    20U,
    21U,
    22U,
    23U,
    24U,
    25U,
    26U,
    27U,
    28U
};

CONST(SecOC_RxPduProcessingType, SECOC_CONST_CONFIG) SecOC_RxPduProcessing[SECOC_RX_PDU_PROCESSING_MAX] = 
{
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        0U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        786U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        0U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 16U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        32U, /* SameBufferPduRef */
        0U, /* Ab_BufferStartOffset */
        32U, /* Ab_RxMakeAuthBufferSize */
        0U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        0U, /* RxSecuredLayerPduId */
        0U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        0U, /* Ab_RxAuthenticLayerPduRefId */
        0U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        1U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        915U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        1U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 17U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        32U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        32U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        1U, /* RxSecuredLayerPduId */
        1U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        1U, /* Ab_RxAuthenticLayerPduRefId */
        1U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        2U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        917U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        2U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 18U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        96U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        96U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        2U, /* RxSecuredLayerPduId */
        2U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        2U, /* Ab_RxAuthenticLayerPduRefId */
        2U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        3U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        918U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        3U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 19U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        160U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        160U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        3U, /* RxSecuredLayerPduId */
        3U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        3U, /* Ab_RxAuthenticLayerPduRefId */
        3U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        4U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        922U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        4U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 20U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        224U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        224U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        4U, /* RxSecuredLayerPduId */
        4U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        4U, /* Ab_RxAuthenticLayerPduRefId */
        4U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        5U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        923U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        5U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 21U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        288U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        288U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        5U, /* RxSecuredLayerPduId */
        5U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        5U, /* Ab_RxAuthenticLayerPduRefId */
        5U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        6U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        925U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        6U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 22U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        352U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        352U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        6U, /* RxSecuredLayerPduId */
        6U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        6U, /* Ab_RxAuthenticLayerPduRefId */
        6U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        7U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        926U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        7U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 23U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        416U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        416U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        7U, /* RxSecuredLayerPduId */
        7U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        7U, /* Ab_RxAuthenticLayerPduRefId */
        7U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        8U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        927U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        8U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 24U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        480U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        480U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        8U, /* RxSecuredLayerPduId */
        8U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        8U, /* Ab_RxAuthenticLayerPduRefId */
        8U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        9U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        933U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        9U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 25U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        544U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        544U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        9U, /* RxSecuredLayerPduId */
        9U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        9U, /* Ab_RxAuthenticLayerPduRefId */
        9U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        10U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        940U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        10U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 26U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        608U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        608U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        10U, /* RxSecuredLayerPduId */
        10U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        10U, /* Ab_RxAuthenticLayerPduRefId */
        10U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        11U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        942U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        11U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 27U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        672U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        672U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        11U, /* RxSecuredLayerPduId */
        11U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        11U, /* Ab_RxAuthenticLayerPduRefId */
        11U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        12U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        946U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        12U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 28U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        736U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        736U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        12U, /* RxSecuredLayerPduId */
        12U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        12U, /* Ab_RxAuthenticLayerPduRefId */
        12U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        13U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        947U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        13U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 29U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        800U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        800U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        13U, /* RxSecuredLayerPduId */
        13U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        13U, /* Ab_RxAuthenticLayerPduRefId */
        13U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        14U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        953U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        14U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 30U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        864U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        864U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        14U, /* RxSecuredLayerPduId */
        14U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        14U, /* Ab_RxAuthenticLayerPduRefId */
        14U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        15U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        956U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        15U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 31U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        928U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        928U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        15U, /* RxSecuredLayerPduId */
        15U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        15U, /* Ab_RxAuthenticLayerPduRefId */
        15U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        16U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        966U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        16U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 32U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        992U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        992U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        16U, /* RxSecuredLayerPduId */
        16U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        16U, /* Ab_RxAuthenticLayerPduRefId */
        16U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        17U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        967U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        17U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 33U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        1056U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        1056U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        17U, /* RxSecuredLayerPduId */
        17U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        17U, /* Ab_RxAuthenticLayerPduRefId */
        17U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        18U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        973U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        18U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 34U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        1120U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        1120U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        18U, /* RxSecuredLayerPduId */
        18U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        18U, /* Ab_RxAuthenticLayerPduRefId */
        18U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        19U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        979U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        19U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 35U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        1184U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        1184U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        19U, /* RxSecuredLayerPduId */
        19U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        19U, /* Ab_RxAuthenticLayerPduRefId */
        19U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        20U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        982U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        20U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 36U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        1248U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        1248U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        20U, /* RxSecuredLayerPduId */
        20U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        20U, /* Ab_RxAuthenticLayerPduRefId */
        20U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        21U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        989U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        21U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 37U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        1312U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        1312U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        21U, /* RxSecuredLayerPduId */
        21U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        21U, /* Ab_RxAuthenticLayerPduRefId */
        21U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        22U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        993U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        22U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 38U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        1376U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        1376U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        22U, /* RxSecuredLayerPduId */
        22U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        22U, /* Ab_RxAuthenticLayerPduRefId */
        22U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        23U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        1003U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        23U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 39U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        1440U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        1440U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        23U, /* RxSecuredLayerPduId */
        23U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        23U, /* Ab_RxAuthenticLayerPduRefId */
        23U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        24U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        1007U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        24U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 40U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        1504U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        1504U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        24U, /* RxSecuredLayerPduId */
        24U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        24U, /* Ab_RxAuthenticLayerPduRefId */
        24U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        25U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        1013U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        25U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 41U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        1568U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        1568U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        25U, /* RxSecuredLayerPduId */
        25U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        25U, /* Ab_RxAuthenticLayerPduRefId */
        25U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        26U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        1332U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        26U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 42U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        1632U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        1632U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        26U, /* RxSecuredLayerPduId */
        26U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        26U, /* Ab_RxAuthenticLayerPduRefId */
        26U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        27U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        888U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        27U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 43U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        64U, /* SameBufferPduRef */
        1696U, /* Ab_BufferStartOffset */
        64U, /* Ab_RxMakeAuthBufferSize */
        1696U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        27U, /* RxSecuredLayerPduId */
        27U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        27U, /* Ab_RxAuthenticLayerPduRefId */
        27U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    },
    {
        128U, /* Ab_AuthInfoLength */
        32U, /* AuthInfoTruncLength */
        0U, /* Ab_BusIndex */
        11U, /* Ab_TxSecurityDataSize */
        0U, /* dummy1 */
        28U, /* Ab_MessageTypeIndex */
        SECOC_AB_MSGTYPE_SECURED, /* Ab_MessageType */
        SECOC_NONE, /* VerifyStatusPropagationMode */
        1U, /* AuthenticationBuildAttempts */
        957U, /* Ab_DataId */
        0U, /* AuthenticationVerifyAttempts */
        28U, /* FreshnessValueId */
        56U, /* FreshnessValueLength */
        56U, /* FreshnessValueTruncLength */
        { 44U, CRYPTO_PROCESSING_ASYNC, {0U, 0U, 0U} }, /* RxAuthServiceConfigRef */
        32U, /* SameBufferPduRef */
        1760U, /* Ab_BufferStartOffset */
        32U, /* Ab_RxMakeAuthBufferSize */
        1760U, /* Ab_RxBufferStartOffset */
        &SecOC_CD_FV_VerifyResult, /* Ab_FreshnessValueCallout */
        28U, /* RxSecuredLayerPduId */
        28U, /* Ab_RxAuthenticLayerPduId */
        &SecOC_CD_FV_GetRxFreshness, /* Ab_FreshnessValueFuncName */
        {&vd_g_oXSECAubIfSecVerifFinAck}, /* Ab_VerificationFinalStatusCallout */
        SECOC_AB_FV_CFUNC, /* Ab_QueryFreshnessValue */
        0U, /* Ab_ProtDataPaddingSize */
        NULL_PTR, /* Ab_ErrorDetailNotifyCallout */
        1U, /* Ab_RxAuthTpCopySize */
        SECOC_IFPDU, /* RxAuthPduType */
        SECOC_IFPDU, /* Ab_RxSecuredPduType */
        FALSE, /* Ab_ForceReceive */
        SECOC_BOTH, /* Ab_VerifyFinalStatusPropagationMode */
        28U, /* Ab_RxAuthenticLayerPduRefId */
        28U, /* Ab_RxSecuredLayerPduRefId */
        0U, /* Ab_CsmReqSaSizeMax */
        { NULL_PTR }, /* Ab_RxMsgOverflowDestructionCallout */
        { NULL_PTR }, /* Ab_RxMsgBusyDestructionCallout */
        SECOC_AB_CSM_REQ_SC, /* Ab_CsmReqType */
        TRUE, /* SecuredRxPduVerification */
        0U /* dummy2 */
    }

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
        29U, /* FreshnessValueId */
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
        30U, /* FreshnessValueId */
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
        31U, /* FreshnessValueId */
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
        32U, /* FreshnessValueId */
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
        33U, /* FreshnessValueId */
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
        34U, /* FreshnessValueId */
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
        35U, /* FreshnessValueId */
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
        36U, /* FreshnessValueId */
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
        37U, /* FreshnessValueId */
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
        38U, /* FreshnessValueId */
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
        39U, /* FreshnessValueId */
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
        40U, /* FreshnessValueId */
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
        41U, /* FreshnessValueId */
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
        42U, /* FreshnessValueId */
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
        43U, /* FreshnessValueId */
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
        44U, /* FreshnessValueId */
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
        29U, /* Ab_RxSecuredMsgCount */
        {    /* Ab_RxSecuredMsgIdxList */
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
            15U,
            16U,
            17U,
            18U,
            19U,
            20U,
            21U,
            22U,
            23U,
            24U,
            25U,
            26U,
            27U,
            28U
        },
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
        0U, /* Ab_RxSecuredMsgCount */
        {    /* Ab_RxSecuredMsgIdxList */
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
        },
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
        0U, /* Ab_RxSecuredMsgCount */
        {    /* Ab_RxSecuredMsgIdxList */
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
        },
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
        0U, /* Ab_RxSecuredMsgCount */
        {    /* Ab_RxSecuredMsgIdxList */
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
        },
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

