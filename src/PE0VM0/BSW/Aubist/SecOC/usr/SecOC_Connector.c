/* SecOC_Connector_c_v2-0-0                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC/Connector/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <PduR_SecOC.h>
#include <Csm.h>
#include "./SecOC_Connector.h"

#include "can_lpr.h"

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

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_Connector_PduR_SecOCTransmit                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udPduId   :                                              */
/*               | ptPduInfo :                                              */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK         : Success                                  */
/*               |  E_NOT_OK     : Failure                                  */
/*               |  SECOC_E_BUSY : Busy                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Connector_PduR_SecOCTransmit
(
    PduIdType udPduId,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptPduInfo
)
{
#ifdef CAN_LPR_H
    return(u1_g_CANLpRIngSecOCTRx(udPduId, ptPduInfo, (uint8)CAN_LPR_ING_SECOC_TX));
#else
    Std_ReturnType ud_stdRet;

    ud_stdRet = PduR_SecOCTransmit( udPduId, ptPduInfo );

    if( ud_stdRet == (Std_ReturnType)PDUR_BUSY )
    {
        ud_stdRet = SECOC_E_BUSY;
    }

    return ud_stdRet;
#endif
}

/****************************************************************************/
/* Function Name | SecOC_Connector_PduR_SecOCCancelTransmit                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udPduId :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK      : Success                                     */
/*               |  E_NOT_OK  : Failure                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Connector_PduR_SecOCCancelTransmit
(
    PduIdType udPduId
)
{
    return PduR_SecOCCancelTransmit( udPduId );
}

/****************************************************************************/
/* Function Name | SecOC_Connector_PduR_SecOCIfTxConfirmation               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udPduId  :                                               */
/*               | udResult :                                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Connector_PduR_SecOCIfTxConfirmation
(
    PduIdType udPduId,
    Std_ReturnType udResult
)
{
    PduR_SecOCIfTxConfirmation( udPduId, udResult );
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Connector_PduR_SecOCTpTxConfirmation               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udPduId  :                                               */
/*               | udResult :                                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Connector_PduR_SecOCTpTxConfirmation
(
    PduIdType udPduId,
    Std_ReturnType udResult
)
{
    PduR_SecOCTpTxConfirmation( udPduId, udResult );
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Connector_PduR_SecOCTpCopyTxData                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udPduId             :                                    */
/*               | ptPduInfo           :                                    */
/*               | ptRetryInfo         :                                    */
/*               | ptAvailableDataSize :                                    */
/* Return Value  | BufReq_ReturnType                                        */
/*               |  BUFREQ_OK       : Success                               */
/*               |  BUFREQ_E_NOT_OK : Failure                               */
/*               |  BUFREQ_E_BUSY   : Not enough message data               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_Connector_PduR_SecOCTpCopyTxData
(
    PduIdType udPduId,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptPduInfo,
    P2CONST(RetryInfoType, AUTOMATIC, SECOC_APPL_DATA) ptRetryInfo,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) ptAvailableDataSize
)
{
    return PduR_SecOCTpCopyTxData( udPduId, ptPduInfo, ptRetryInfo, ptAvailableDataSize );
}

/****************************************************************************/
/* Function Name | SecOC_Connector_Csm_MacGenerate                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u4JobId  :                                               */
/*               | udMode :                                                 */
/*               | ptData :                                                 */
/*               | u4DataLength :                                           */
/*               | ptMac :                                                  */
/*               | ptMacLength :                                            */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          : request successful                       */
/*               | E_NOT_OK      : request failed                           */
/*               | CRYPTO_E_BUSY : request failed, service is still busy    */
/*               | other error   : request failed, refer to Csm             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Connector_Csm_MacGenerate
(
    uint32 u4JobId,
    Crypto_OperationModeType udMode,
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) ptData,
    uint32 u4DataLength, 
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptMac,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptMacLength
)
{
    return Csm_MacGenerate( u4JobId,
                            udMode,
                            ptData,
                            u4DataLength,
                            ptMac,
                            ptMacLength );
}

#endif /* ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)) */

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_Connector_PduR_SecOCTpStartOfReception             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udPduId      :                                           */
/*               | ptPduInfo    :                                           */
/*               | udSduLength  :                                           */
/*               | ptBufferSize :                                           */
/* Return Value  | BufReq_ReturnType                                        */
/*               |  BUFREQ_OK       : Success                               */
/*               |  BUFREQ_E_NOT_OK : Failure                               */
/*               |  BUFREQ_E_BUSY   : Insufficient buffer                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_Connector_PduR_SecOCTpStartOfReception
(
    PduIdType udPduId,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptPduInfo,
    PduLengthType udSduLength,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) ptBufferSize
)
{
    return PduR_SecOCTpStartOfReception( udPduId, ptPduInfo, udSduLength, ptBufferSize );
}

/****************************************************************************/
/* Function Name | SecOC_Connector_PduR_SecOCIfRxIndication                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udPduId   :                                              */
/*               | ptPduInfo :                                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Connector_PduR_SecOCIfRxIndication
(
    PduIdType udPduId,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptPduInfo
)
{
#ifdef CAN_LPR_H
    static const uint32    u4_s_CAN_LPR_SECOC_NB_FVKKZ = (uint32)11U;
    PduInfoType            st_t_pduinfo;

    st_t_pduinfo.SduDataPtr  = ptPduInfo->SduDataPtr;
    st_t_pduinfo.MetaDataPtr = NULL_PTR;
    st_t_pduinfo.SduLength   = ptPduInfo->SduLength + u4_s_CAN_LPR_SECOC_NB_FVKKZ;

    (void)u1_g_CANLpRIngSecOCTRx(udPduId, &st_t_pduinfo, (uint8)CAN_LPR_ING_SECOC_RX);
#else
    PduR_SecOCIfRxIndication( udPduId, ptPduInfo );

    return ;
#endif
}

/****************************************************************************/
/* Function Name | SecOC_Connector_PduR_SecOCTpRxIndication                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udPduId   :                                              */
/*               | udResult  :                                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Connector_PduR_SecOCTpRxIndication
(
    PduIdType udPduId,
    Std_ReturnType udResult
)
{
    PduR_SecOCTpRxIndication( udPduId, udResult );
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Connector_PduR_SecOCTpCopyRxData                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udPduId      :                                           */
/*               | ptPduInfo    :                                           */
/*               | ptBufferSize :                                           */
/* Return Value  | BufReq_ReturnType                                        */
/*               |  BUFREQ_OK       : Success                               */
/*               |  BUFREQ_E_NOT_OK : Failure                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_Connector_PduR_SecOCTpCopyRxData
(
    PduIdType udPduId,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptPduInfo,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) ptBufferSize
)
{
    return PduR_SecOCTpCopyRxData( udPduId, ptPduInfo, ptBufferSize );
}

/****************************************************************************/
/* Function Name | SecOC_Connector_Csm_MacVerify                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u4JobId  :                                               */
/*               | udMode :                                                 */
/*               | ptData :                                                 */
/*               | u4DataLength :                                           */
/*               | ptMac     :                                              */
/*               | u4MacLength :                                            */
/*               | ptResult :                                               */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          : request successful                       */
/*               | E_NOT_OK      : request failed                           */
/*               | CRYPTO_E_BUSY : request failed, service is still busy    */
/*               | other error   : request failed, refer to Csm             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Connector_Csm_MacVerify
(
    uint32 u4JobId,
    Crypto_OperationModeType udMode,
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) ptData,
    uint32 u4DataLength, 
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) ptMac,
    const uint32 u4MacLength,
    P2VAR(Crypto_VerifyResultType, AUTOMATIC, SECOC_APPL_DATA) ptResult
)
{
    return Csm_MacVerify( u4JobId,
                          udMode,
                          ptData,
                          u4DataLength,
                          ptMac,
                          u4MacLength,
                          ptResult );
}
#endif /* ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)) */

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
