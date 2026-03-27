/* SecOC_Connector_h_v2-0-0                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC/Connector/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef SECOC_CONNECTOR_H
#define SECOC_CONNECTOR_H

/*--------------------------------------------------------------------------*/
/* Config                                                                   */
/*--------------------------------------------------------------------------*/
#include <SecOC.h>

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Connector_PduR_SecOCTransmit
(
    PduIdType udPduId,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptPduInfo
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Connector_PduR_SecOCCancelTransmit
(
    PduIdType udPduId
);
FUNC(void, SECOC_CODE) SecOC_Connector_PduR_SecOCIfTxConfirmation
(
    PduIdType udPduId,
    Std_ReturnType udResult
);
FUNC(void, SECOC_CODE) SecOC_Connector_PduR_SecOCTpTxConfirmation
(
    PduIdType udPduId,
    Std_ReturnType udResult
);
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_Connector_PduR_SecOCTpCopyTxData
(
    PduIdType udPduId,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptPduInfo,
    P2CONST(RetryInfoType, AUTOMATIC, SECOC_APPL_DATA) ptRetryInfo,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) ptAvailableDataSize
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Connector_Csm_MacGenerate
(
    uint32 u4JobId,
    Crypto_OperationModeType udMode,
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) ptData,
    uint32 u4DataLength, 
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptMac,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptMacLength
);
#endif /* ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)) */

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_Connector_PduR_SecOCTpStartOfReception
(
    PduIdType udPduId,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptPduInfo,
    PduLengthType udSduLength,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) ptBufferSize
);
FUNC(void, SECOC_CODE) SecOC_Connector_PduR_SecOCIfRxIndication
(
    PduIdType udPduId,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptPduInfo
);
FUNC(void, SECOC_CODE) SecOC_Connector_PduR_SecOCTpRxIndication
(
    PduIdType udPduId,
    Std_ReturnType udResult
);
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_Connector_PduR_SecOCTpCopyRxData
(
    PduIdType udPduId,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptPduInfo,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) ptBufferSize
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Connector_Csm_MacVerify
(
    uint32 u4JobId,
    Crypto_OperationModeType udMode,
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) ptData,
    uint32 u4DataLength, 
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) ptMac,
    const uint32 u4MacLength,
    P2VAR(Crypto_VerifyResultType, AUTOMATIC, SECOC_APPL_DATA) ptResult
);
#endif /* ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)) */

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* SECOC_CONNECTOR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
