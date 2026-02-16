/* 2.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Oem eXention of SEC Aubist Interface Layer                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXSEC_AUBIF_SECOC_C_MAJOR                  (2U)
#define OXSEC_AUBIF_SECOC_C_MINOR                  (0U)
#define OXSEC_AUBIF_SECOC_C_PATCH                  (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxsec_aubif_secoc.h"

#include <PduR_SecOC.h>
#include <Csm.h>
#include <SecOC_Connector.h>

#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "can_lpr.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXSEC_AUBIF_SECOC_C_MAJOR != OXSEC_AUBIF_SECOC_H_MAJOR) || \
     (OXSEC_AUBIF_SECOC_C_MINOR != OXSEC_AUBIF_SECOC_H_MINOR) || \
     (OXSEC_AUBIF_SECOC_C_PATCH != OXSEC_AUBIF_SECOC_H_PATCH))
#error "oxsec_aubif_secoc.c and oxsec_aubif_secoc.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXSEC_MAC_MESSAGE_SIZE_MAX                      (64U)
#define OXSEC_KZK_SIZE                                  (4U)
#define OXSEC_MAC_MESSAGE_SIZE_32                       (32U)
#define OXSEC_MAC_MESSAGE_SIZE_64                       (64U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void vd_g_oXSECAubIfSecFullFVAck( uint16 u2FvId )                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_oXSECAubIfSecFullFVAck( uint16 u2FvId )
{

}
/*===================================================================================================================================*/
/*  void vd_g_oXSECAubIfSecVerifFinAck( SecOC_VerificationStatusType verificationStatus,                                             */
/*                                                          const uint8* SduDataPtr, PduLengthType SduLength )                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_oXSECAubIfSecVerifFinAck( SecOC_VerificationStatusType verificationStatus,
                                                        const uint8* SduDataPtr, PduLengthType SduLength )
{

#ifdef CAN_LPR_H
    
    PduInfoType            st_t_pduinfo;
    uint32                 u4_t_lpcnt;
    uint32                 u4_t_datasize;
    PduIdType              u2_t_udPduId;
    uint8                  u1_tp_sduData[OXSEC_MAC_MESSAGE_SIZE_MAX];
    
    if( SduDataPtr != NULL_PTR ){
    
        u4_t_datasize = SduLength - (U4)OXSEC_KZK_SIZE;
        for(u4_t_lpcnt = (U1)0; u4_t_lpcnt < u4_t_datasize; u4_t_lpcnt++){
            u1_tp_sduData[u4_t_lpcnt] = SduDataPtr[u4_t_lpcnt];
        }
        u1_tp_sduData[u4_t_lpcnt] = (U1)verificationStatus.verificationStatus;
        u4_t_lpcnt++;
        u1_tp_sduData[u4_t_lpcnt] = (U1)((verificationStatus.Ab_SecOCDataId >> 8U) & (U1)0xFFU);
        u4_t_lpcnt++;
        u1_tp_sduData[u4_t_lpcnt] = (U1)(verificationStatus.Ab_SecOCDataId & 0xFF);

        u2_t_udPduId = verificationStatus.freshnessValueID;
        st_t_pduinfo.SduDataPtr  = &u1_tp_sduData[0U];
        st_t_pduinfo.MetaDataPtr = NULL_PTR;
        st_t_pduinfo.SduLength   = SduLength;

        (void)u1_g_CANLpRIngSecOCTRx(u2_t_udPduId, &st_t_pduinfo, (uint8)CAN_LPR_ING_SECOC_RX);
    }
    
    return;

#endif
}


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Move from SecOC/usr/SecOC_Connector.c                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
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
    return ;
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


/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0    12/02/2025  KT       new                                                                                                */
/*                                                                                                                                   */
/*  * KT   = Kazuya Takayama, DENSO CREATE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
