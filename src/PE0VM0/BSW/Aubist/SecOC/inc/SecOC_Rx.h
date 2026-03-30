/* SecOC_Rx_h_v2-1-1                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC/Rx/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef SECOC_RX_H
#define SECOC_RX_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SecOC.h>

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Return of Rx MainProcess */
#define SECOC_RX_PROC_OK            ((uint16)0x0000U)
#define SECOC_RX_PROC_NG_FV         ((uint16)0x0100U)
#define SECOC_RX_PROC_NG_CSM        ((uint16)0x0101U)
#define SECOC_RX_PROC_NG_RETRY      ((uint16)0x0102U)
#define SECOC_RX_PROC_NG_OTHER      ((uint16)0x0103U)
#define SECOC_RX_PROC_RETRY_MAC     ((uint16)0x0200U)
#define SECOC_RX_PROC_RETRY_FV      ((uint16)0x0201U)
#define SECOC_RX_PROC_RETRY_CSM     ((uint16)0x0202U)
#define SECOC_RX_PROC_NONE          ((uint16)0x0300U)

/* Rx Pdu Kind */
#define SECOC_RX_PDU_SEC            ((uint8)0U)
#define SECOC_RX_PDU_AUTH           ((uint8)1U)

/* Rx Status */
#define SECOC_RX_ST_IDLE                ((uint8)0xE1U)
#define SECOC_RX_ST_RECEIVE             ((uint8)0xD2U)
#define SECOC_RX_ST_VERIFY              ((uint8)0xC3U)
#define SECOC_RX_ST_RETRY               ((uint8)0xB4U)
#define SECOC_RX_ST_FV_NG               ((uint8)0xA5U)
#define SECOC_RX_ST_END                 ((uint8)0x96U)
#define SECOC_RX_ST_LOWER_COPY          ((uint8)0x87U)
#define SECOC_RX_ST_WAIT_CALLBACK       ((uint8)0x78U)
#define SECOC_RX_ST_UPPER_COPY          ((uint8)0x69U)
#define SECOC_RX_ST_CALLBACK_RECEIVED   ((uint8)0x5AU)
#define SECOC_RX_ST_WAIT_NOTIFY_CALLOUT ((uint8)0x4BU)

/* Defines setting values to override the verification status. */
#define SECOC_RX_OVERRIDE_DROP_UNTIL_NOTICE   ((uint16)0x00E1U)   /* Authenticator verification is skipped and notice to upper layer */
#define SECOC_RX_OVERRIDE_DROP_UNTIL_LIMIT    ((uint16)0x00D2U)   /* Until NumberOfMessagesToOverride is reached, authenticator verification is not performed */
#define SECOC_RX_OVERRIDE_CANCEL              ((uint16)0x00C3U)   /* Cancel Override of VerifyStatus. */
#define SECOC_RX_OVERRIDE_PASS_UNTIL_NOTICE   ((uint16)0x00B4U)   /* Until further notice, authenticator verification is performed, I-PDU is sent to upper layer independent of verification result */
#define SECOC_RX_OVERRIDE_SKIP_UNTIL_LIMIT    ((uint16)0x00A5U)   /* Until NumberOfMessagesToOverride is reached, authenticator verification is not performed, I-PDU is sent to upper layer */
#define SECOC_RX_OVERRIDE_PASS_UNTIL_LIMIT    ((uint16)0x0096U)   /* Until NumberOfMessagesToOverride is reached, authenticator verification is performed, I-PDU is sent to upper layer independent of verification result */
#define SECOC_RX_OVERRIDE_SKIP_UNTIL_NOTICE   ((uint16)0x0087U)   /* Until further notice, authenticator verification is not performed, I-PDU is sent to upper layer */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

FUNC(void, SECOC_CODE) SecOC_Rx_Reset
(
    void
);

FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_SetVerifyStatusOverride
(
    uint32 u4ValueID,
    uint16 u2OverrideStatus,
    uint8  u1NumberOfMessagesToOverride
);
FUNC(void, SECOC_CODE) SecOC_Rx_VerifyDropSkip
(
    uint16 u2Index
);

FUNC(SecOC_ModeType, SECOC_CODE) SecOC_Rx_GetMode
(
    void
);
FUNC(void, SECOC_CODE) SecOC_Rx_Receive
(
    uint16 u2Index,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptMsg
);
FUNC(void, SECOC_CODE) SecOC_Rx_MainFuncPeriod
(
    void
);
FUNC(void, SECOC_CODE) SecOC_Rx_ResetBus
(
    uint16 u2BusIndex
);
FUNC(uint16, SECOC_CODE) SecOC_Rx_MainProcess
(
    uint16 u2Index
);
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
FUNC(void, SECOC_CODE) SecOC_Rx_VerifyCallback
(
    uint16 u2Index,
    Std_ReturnType udRet
);
#endif
FUNC(void, SECOC_CODE) SecOC_Rx_ReapEvt
(
    void
);
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
FUNC(void, SECOC_CODE) SecOC_Rx_AsyncNotify
(
    uint16 u2Index
);
#endif
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
FUNC(SecOC_ErrorStatusType, SECOC_CODE) SecOC_Rx_GetErrorStatus
(
    void
);
#endif
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_Rx_ReceiveDivideStart
(
    uint16 u2Index,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptMsg,
    uint32 u4SduLength,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptAvailableMsgSize
);
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_Rx_CopyDivide
(
    uint16 u2Index,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptMsg,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) ptAvailableMsgSize
);
FUNC(void, SECOC_CODE) SecOC_Rx_ReceiveDivideFinish
(
    uint16          u2Index,
    Std_ReturnType  udResult
);

FUNC(void, SECOC_CODE) SecOC_Rx_TpNotify
(
    uint16 u2Index
);

FUNC(void, SECOC_CODE) SecOC_Rx_GetStatus
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptStatus
);

FUNC(void, SECOC_CODE) SecOC_Rx_ClearSelect
(
    uint16 u2Index
);

FUNC(void, SECOC_CODE) SecOC_Rx_ResetTpCopySize
(
    void
);

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_VAR_NO_INIT
#include <SecOC_MemMap.h>

extern VAR(uint32, SECOC_VAR_NO_INIT) SecOC_Rx_u4VerifyStartCount[SECOC_AB_BUS_MAX];

#define SECOC_STOP_SEC_VAR_NO_INIT
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* SECOC_RX_PDU_PROCESSING */

#endif /* SECOC_RX_H */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/*  v2-1-0     :2023/04/14                                                  */
/*  v2-1-1     :2023/07/04                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
