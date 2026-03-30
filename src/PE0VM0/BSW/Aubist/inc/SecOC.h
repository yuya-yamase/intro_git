/* SecOC_h_v2-1-0                                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC/HEADER                                               */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef SECOC_H
#define SECOC_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../SecOC/cfg/SecOC_Cfg.h"
#if (SECOC_AB_EXTENDED_ENABLE == STD_ON)
#include <SecOC_Extd.h>
#endif

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Local Config */
#define SECOC_COM_PADDING_ENABLE    (STD_OFF)

/* Version Infomation Macros */
#define SECOC_VENDOR_ID                     (0x0053U)
#define SECOC_MODULE_ID                     (150U)
#define SECOC_SW_MAJOR_VERSION              (1U)
#define SECOC_SW_MINOR_VERSION              (0U)
#define SECOC_SW_PATCH_VERSION              (0U)
#define SECOC_AR_RELEASE_MAJOR_VERSION      (4U)
#define SECOC_AR_RELEASE_MINOR_VERSION      (5U)
#define SECOC_AR_RELEASE_REVISION_VERSION   (0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

FUNC(void, SECOC_CODE) SecOC_Init
(
    P2CONST(SecOC_ConfigType, AUTOMATIC, SECOC_APPL_CONST) config
);
FUNC(void, SECOC_CODE) SecOC_DeInit
(
    void
);
FUNC(void, SECOC_CODE) SecOC_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, SECOC_APPL_DATA) versioninfo
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_IfTransmit
(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) PduInfoPtr
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_TpTransmit
(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) PduInfoPtr
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_IfCancelTransmit
(
    PduIdType TxPduId
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_TpCancelTransmit
(
    PduIdType TxPduId
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_TpCancelReceive
(
    PduIdType RxPduId
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Ab_VerifyStatusOverride
(
    uint32 ValueID,
    SecOC_OverrideStatusType overrideStatus,
    uint8 numberOfMessagesToOverride
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Ab_FreshnessValueRead
(
    uint16 u2FvId,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptFv,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptFvLen
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Ab_FreshnessValueWrite
(
    uint16 u2FvId,
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) ptFv,
    uint32 u4FvLen
);
FUNC(void, SECOC_CODE) SecOC_RxIndication
(
    PduIdType RxPduId,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) PduInfoPtr
);
FUNC(void, SECOC_CODE) SecOC_TxConfirmation
(
    PduIdType TxPduId,
    Std_ReturnType result
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Ab_GetMode
(
    P2VAR(SecOC_ModeType, AUTOMATIC, SECOC_APPL_DATA) ptMode
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Ab_ResetBus
(
    uint16 u2BusId
);
FUNC(void, SECOC_CODE) SecOC_TpRxIndication
(
    PduIdType id,
    Std_ReturnType result
);
FUNC(void, SECOC_CODE) SecOC_TpTxConfirmation
(
    PduIdType id,
    Std_ReturnType result
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_TriggerTransmit
(
    PduIdType TxPduId,
    P2VAR(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) PduInfoPtr
);
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_CopyRxData
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) info,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) bufferSizePtr
);
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_CopyTxData
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) info,
    P2CONST(RetryInfoType, AUTOMATIC, SECOC_APPL_DATA) retry,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) availableDataPtr
);
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_StartOfReception
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA)  info,
    PduLengthType TpSduLength,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) bufferSizePtr
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_SendDefaultAuthenticationInformation
(
    uint16 FreshnessValueID,
    boolean sendDefaultAuthenticationInformation
);

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* SECOC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/*  v2-1-0     :2023/04/14                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
