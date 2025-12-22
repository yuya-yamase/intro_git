/* Dcm_Dsl_TxAbt_h(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | DCM/Dsl_TxAbt/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/
#ifndef DCM_DSLTXABT_H
#define DCM_DSLTXABT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Main_Common.h>
#include "../../Dsl/inc/Dcm_Dsl_Ctrl_local.h"
#include "../../Dsl/inc/Dcm_Dsl_Main.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_SID_TX_NRC          ((uint8)0x7F)      /* SID of the negative acknowledge                       */
#define DCM_DSL_POS_SID             ((uint8)0x00)      /* Index of SID of the req/positive acknowledge message  */
#define DCM_DSL_NEG_SID             ((uint8)0x01)      /* Index of SID of the negative acknowledge              */
#define DCM_DSL_ERROR_INDEX         ((uint8)0x02)      /* Index of the error code plant                         */


/* Refer to a definition of Dcm_Dsl_Ctrl.h      */
/*      DCM_DSL_SET_POSITIVE_RESPONSE           */
/*      DCM_DSL_SET_NEGATIVE_RESPONSE           */
/*      DCM_DSL_SET_NO_RESPONSE_POS             */
/*      DCM_DSL_SET_NO_RESPONSE_NEG             */
#define DCM_DSL_SET_PENDING_RESPONSE   ((uint8)0x10U)  /* Response pending response designation */
#define DCM_DSL_SET_P4TO_NEG_RESPONSE  ((uint8)0x11U)  /* P4TO(NRC0x10) response designation    */
#define DCM_DSL_SET_NONE_RESPONSE      ((uint8)0xFFU)  /* Unspecified default value             */

/********************** Tx State ***************************************/
/* Idle State */
#define DCM_DSL_TXST_IDLE                  ((uint8)0x00U)

/* State waiting for response request */
#define DCM_DSL_TXST_WT_SV_COMP            ((uint8)0x10U)
#define DCM_DSL_TXST_WT_SV_COMP_P2MINTO    ((uint8)0x11U)

/* State waiting for transmission */
#define DCM_DSL_TXST_WT_TX_RCRRP           ((uint8)0x20U)
#define DCM_DSL_TXST_WT_TX_LAST            ((uint8)0x21U)
#define DCM_DSL_TXST_WT_TX_LAST_P4         ((uint8)0x22U)

/* State waiting for cancellation */
#define DCM_DSL_TXST_WT_CL_SV_COMP         ((uint8)0x23U)
#define DCM_DSL_TXST_WT_CL_TX              ((uint8)0x24U)
#define DCM_DSL_TXST_WT_CL_TXERR           ((uint8)0x25U)

/* Response Pending Responding State */
#define DCM_DSL_TXST_WT_TX_COMP_RP         ((uint8)0x30U)
#define DCM_DSL_TXST_WT_TX_COMP_RP_ABT     ((uint8)0x31U)
#define DCM_DSL_TXST_WT_TX_COMP_RP_ABT_P4  ((uint8)0x32U)

/* State in final response */
#define DCM_DSL_TXST_WT_TX_COMP_LAST       ((uint8)0x40U)
#define DCM_DSL_TXST_WT_TX_PAGE_UPDATE     ((uint8)0x41U)

/* State waiting for completion processing */
#define DCM_DSL_TXST_WT_COMP_LAST          ((uint8)0x50U)

/********************** Tx State End ***********************************/

/* Refer to a definition of Dcm_Dsl_TxMsg.h     */
/*      DCM_DSL_TX_E_SEND_ERR                   */
/*      DCM_DSL_TX_E_DISABLE                    */
/*      DCM_DSL_TX_E_SUPPRES                    */
/*      DCM_DSL_TX_E_NORESP                     */
#define DCM_DSL_TX_E_CHG_DEFSES ((Std_ReturnType)0x91U) /* Changed to a default session */
                                                        /* by Transmission Error        */
#define DCM_DSL_TX_E_RETRY_OVR  ((Std_ReturnType)0x92U) /* Re-Transmission Time Over    */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_Init
(void);

FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_Activate
(
    const uint16 u2PduMapIndex
);

FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_Deactivate
(
    const uint16 u2PduMapIndex
);

FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_WriteNRCData
(
    const uint16 u2PduMapIndex,
    const uint8 u1SID,
    const Dcm_NegativeResponseCodeType u1ErrorCode
);

FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_P2TO
(
    const uint16 u2PduMapIndex,
    const uint8 u1SID
);

FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_P2MinTO
(
    const uint16 u2PduMapIndex
);

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_P4TO
(
    const uint16 u2PduMapIndex,
    const uint8 u1SID
);

FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_FailSafeTO
(
    const uint16 u2PduMapIndex
);

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_TransmitReq
(
    const uint16 u2PduMapIndex
);

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_TxRetryReq
(
    const uint16 u2PduMapIndex
);

FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_SendForcePendingResponse
(
    const uint16 u2PduMapIndex,
    const uint8 u1SID
);

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_TransmitFunctionality
(
    const uint16 u2PduMapIndex,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo,
    const Dcm_Dsl_ResponseSettingType u1ResponseKind
);

#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_SetRespReqMsg
(
    const uint16 u2PduMapIndex,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo
);

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_RespReqAfterEcuReset
(
    const uint16 u2PduMapIndex
);

#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_SetBusyRespReq
(
    const uint16 u2PduMapIndex,
    const uint8 u1SID,
    const Dcm_NegativeResponseCodeType u1ErrorCode
);

FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_CancelTransmit
(
    const uint16 u2PduMapIndex
);

FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_HandlTopHalfLastConfirmation
(
    const uint16 u2PduMapIndex,
    const Std_ReturnType u1Result,
    const Dcm_Dsl_ResponseSettingType u1ResponseKind
);

FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_HandlTopHalfRcrrpConfirmation
(
    const uint16 u2PduMapIndex,
    const Std_ReturnType u1Result,
    const Dcm_Dsl_ResponseSettingType u1ResponseKind
);


FUNC(boolean, DCM_CODE) Dcm_Dsl_TxAbt_IsTxState
(
    const uint16 u2PduMapIndex
);

#if( DCM_DSL_ROE_ENABLE == STD_ON )
FUNC(boolean, DCM_CODE) Dcm_Dsl_TxAbt_IsActive
(
    const uint16 u2PduMapIndex
);

FUNC(boolean, DCM_CODE) Dcm_Dsl_TxAbt_CanStartRoe
(
    const uint16 u2ReqPduMapIndex,
    const uint16 u2ActivePduMapIndex
);
#endif /* DCM_DSL_ROE_ENABLE == STD_ON */

FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_CancelReq
(
    const uint16 u2PduMapIndex
);

#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_CancelRespReq
(
    const uint16 u2PduMapIndex
);
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */

FUNC_P2VAR(AB_83_DcmPduInfoType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_GetLastTransmittedMsg
(
    const uint16 u2PduMapIndex,
    P2VAR(Dcm_Dsl_ResponseSettingType, AUTOMATIC, DCM_APPL_DATA) ptResponseKind
);

FUNC_P2VAR(Dcm_TxPduInfoType, DCM_APPL_DATA, DCM_CODE) Dcm_Dsl_TxAbt_GetTxBuf
(
    const uint16 u2PduMapIndex
);

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_CancelPagedBuffer
(
    const uint16 u2PduMapIndex
);

FUNC(BufReq_ReturnType, DCM_CODE) Dcm_Dsl_TxAbt_HandlTopHalfUpdatePage
(
    const uint16 u2PduMapIndex
);

FUNC(AB_83_DcmPduLengthType, DCM_CODE) Dcm_Dsl_TxAbt_GetResponseDataLength
(void);

#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

FUNC(uint16, DCM_CODE) Dcm_Dsl_TxAbt_GetSrcPduMapIndex
(
    const uint16 u2PduMapIndex
);

FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_NotifyTxStart
(void);

FUNC(uint8, DCM_CODE) Dcm_Dsl_TxAbt_GetNumOfConcurrentTx
(void);

FUNC(void, DCM_CODE) Dcm_Dsl_TxAbt_Abort
(void);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* DCM_DSLTXABT_H */
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-3-0         :2022-08-30                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
