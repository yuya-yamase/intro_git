/* SecOC_CD_FV_h_v2-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC_CD_FV/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef SECOC_CD_FV_H
#define SECOC_CD_FV_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SecOC.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CD_FV_CODE
#include <SecOC_MemMap.h>

FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Init
(
    void
);
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Read
(
    uint16 u2FvId,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvLen
);
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Write
(
    uint16 u2FvId,
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    uint32 u4FvLen
);
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_GetRxFreshness
(
    uint16 SecOCFreshnessValueID,
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) SecOCTruncatedFreshnessValue,
    uint32 SecOCTruncatedFreshnessValueLength,
    uint16 SecOCAuthVerifyAttempts,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) SecOCFreshnessValueLength
);
#endif
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_GetTxFreshnessTruncData
(
    uint16 SecOCFreshnessValueID,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) SecOCFreshnessValueLength,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) SecOCTruncatedFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) SecOCTruncatedFreshnessValueLength
);
FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_SPduTxConfirmation
(
    uint16 SecOCFreshnessValueID
);
#endif
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_VerifyResult
(
    SecOC_VerificationStatusType stVerResult
);
#endif
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_ResetBus
(
    uint16 u2BusId
);
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
FUNC(SecOC_ErrorStatusType, SECOC_CD_FV_CODE) SecOC_CD_FV_GetErrorStatus
(
    void
);
#endif /* SECOC_AB_RAM_ERROR_CHK */
#define SECOC_STOP_SEC_CD_FV_CODE
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* SECOC_CD_FV_H */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
