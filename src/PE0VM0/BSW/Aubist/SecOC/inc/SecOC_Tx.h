/* SecOC_Tx_h_v2-1-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC/Tx/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef SECOC_TX_H
#define SECOC_TX_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SecOC.h>

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Return of Tx MainProcess */
#define SECOC_TX_PROC_OK            ((uint16)0x0000U)
#define SECOC_TX_PROC_NG_FV         ((uint16)0x0100U)
#define SECOC_TX_PROC_NG_CSM        ((uint16)0x0101U)
#define SECOC_TX_PROC_NG_PDUR       ((uint16)0x0102U)
#define SECOC_TX_PROC_NG_RETRY      ((uint16)0x0103U)
#define SECOC_TX_PROC_NG_OTHER      ((uint16)0x0104U)
#define SECOC_TX_PROC_RETRY_CSM     ((uint16)0x0202U)
#define SECOC_TX_PROC_RETRY_PDUR    ((uint16)0x0203U)
#define SECOC_TX_PROC_NONE          ((uint16)0x0300U)

/* Tx Pdu Kind */
#define SECOC_TX_PDU_AUTH           ((uint8)0U)
#define SECOC_TX_PDU_SEC            ((uint8)1U)

/* Tx Status */
#define SECOC_TX_ST_IDLE                  ((uint8)0xE1U)
#define SECOC_TX_ST_ACCEPT                ((uint8)0xD2U)
#define SECOC_TX_ST_GENERATE              ((uint8)0xC3U)
#define SECOC_TX_ST_RETRY                 ((uint8)0xB4U)
#define SECOC_TX_ST_TRANSMIT              ((uint8)0xA5U)
#define SECOC_TX_ST_END                   ((uint8)0x96U)
#define SECOC_TX_ST_UPPER_COPY            ((uint8)0x87U)
#define SECOC_TX_ST_WAIT_CALLBACK         ((uint8)0x78U)
#define SECOC_TX_ST_WAIT_NOTIFY           ((uint8)0x69U)
#define SECOC_TX_ST_CALLBACK_RECEIVED     ((uint8)0x5AU)
#define SECOC_TX_ST_WAIT_CANCEL_CALLBACK  ((uint8)0x4BU)
#define SECOC_TX_ST_GENERATE_DEFAULT      ((uint8)0x3CU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

FUNC(void, SECOC_CODE) SecOC_Tx_Reset
(
    void
);

FUNC(SecOC_ModeType, SECOC_CODE) SecOC_Tx_GetMode
(
    void
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_IfTransmit
(
    uint16 u2Index,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptMsg
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_TpTransmit
(
    uint16 u2Index,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptMsg
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_Cancel
(
    uint16 u2Index
);
FUNC(void, SECOC_CODE) SecOC_Tx_Finish
(
    uint16 u2Index,
    Std_ReturnType  udResult
);
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
FUNC(uint16, SECOC_CODE) SecOC_Tx_GetMainProcMsgNum
(
    void
);
#endif
FUNC(uint16, SECOC_CODE) SecOC_Tx_MainProcess
(
    uint16 u2Index
);
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
FUNC(void, SECOC_CODE) SecOC_Tx_GenerateCallback
(
    uint16 u2Index,
    Std_ReturnType udRet
);
FUNC(void, SECOC_CODE) SecOC_Tx_ReapCallbackEvt
(
    void
);
FUNC(void, SECOC_CODE) SecOC_Tx_AsyncNotify
(
    uint16 u2Index
);
#endif
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
FUNC(SecOC_ErrorStatusType, SECOC_CODE) SecOC_Tx_GetErrorStatus
(
    void
);
#endif
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_Tx_CopyDivide
(
    uint16 u2Index,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptMsg,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) ptRemainMsgSize
);
FUNC(void, SECOC_CODE) SecOC_Tx_DivideFinish
(
    uint16          u2Index,
    Std_ReturnType  udResult
);

FUNC(void, SECOC_CODE) SecOC_Tx_TpCopy
(
    uint16 u2Index
);

#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
FUNC(void, SECOC_CODE) SecOC_Tx_FinishChk
(
    uint16 u2Index
);
#endif


FUNC(void, SECOC_CODE) SecOC_Tx_GetStatus
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptStatus
);

FUNC(void, SECOC_CODE) SecOC_Tx_ClearSelect
(
    uint16 u2Index
);

FUNC(void, SECOC_CODE) SecOC_Tx_ResetTpCopySize
(
    void
);

#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_SetDefaultAuthInfo
(
    uint16 u2FvId,
    boolean bDefaultAuthInfo
);
#endif

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* SECOC_TX_PDU_PROCESSING */

#endif /* SECOC_TX_H */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/*  v2-1-0     :2023/04/14                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
