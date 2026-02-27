/* SecOC_Rx_c_v2-1-3                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name | SecOC/Rx/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SchM_SecOC.h>
#include <SecOCStd_String.h>
#include <SecOCStd_Util.h>
#include <Csm.h>
#include "../usr/SecOC_Connector.h"
#include "../inc/SecOC_Buff.h"
#include "../inc/SecOC_Com.h"
#if (SECOC_AB_EXTENDED_ENABLE == STD_ON)
#include "../inc/SecOC_Extd_Internal.h"
#endif

#include "../inc/SecOC_Rx.h"

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Rx flag */
#define SECOC_RX_FLAG_FALSE         ((uint8)0x00U)
#define SECOC_RX_FLAG_TRUE          ((uint8)0xFFU)

/* Buffer size */
#define SECOC_RX_AUTHINFO_SIZE      (16UL)  /* 16byte */
#define SECOC_RX_FV_SIZE            (64U)   /* 64byte */

/* Reserve size */
#define SECOC_RX_RESERVE_SIZE_3     (3U)
#define SECOC_RX_RESERVE_SIZE_15    (15U)
#define SECOC_RX_RESERVE_SIZE_16    (16U)
#define SECOC_RX_RESERVE_SIZE_31    (31U)
#define SECOC_RX_RESERVE_SIZE_48    (48U)
#define SECOC_RX_RESERVE_SIZE_63    (63U)

#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
#define SECOC_RX_ASYNC_RESERVE_SIZE (2U)
#endif
#if (SECOC_AB_RX_FV_BUFF_SIZE != 0U)
#define SECOC_RX_FV_BUFF_SIZE       (SECOC_AB_RX_FV_BUFF_SIZE)
#else
#define SECOC_RX_FV_BUFF_SIZE       (4U)    /* Dummy */
#endif

/* Bit define */
#define SECOC_RX_BIT_8              (8U)
#define SECOC_RX_TOP_MESSAGE        (0U)
#define SECOC_RX_INVALID_INDEX      ((uint16)0xFFFFU)
#define SECOC_RX_REWRITE_POS        ((uint32)0U)
#define SECOC_RX_UINT32_MAX_VALUE   ((uint32)0xFFFFFFFFU)


/* Mask */
#if( SECOC_OVERRIDE_STATUS_WITH_DATA_ID == STD_OFF )
#define SECOC_RX_U2_MAX            ((uint16)0xFFFFU)
#endif

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Rx control struct */
typedef struct {
    volatile uint8                  u1Status;
    uint8                           u1Reserve[SECOC_RX_RESERVE_SIZE_3];
} SecOC_Rx_CtrlType;

#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
typedef struct {
    SecOC_VerificationResultType    udVerResult;
    SecOC_VerificationResultType    udNgResult;
    Std_ReturnType                  udCsmResult;
    uint8                           u1NotifyCsmResultFlg;
    uint8                           u1NotifyVerResultFlg;
    uint8                           u1NotifyNgFlg;
} SecOC_Rx_AsyncCtrlType;

typedef struct {
    uint8                           u1CallBackEvt;
    Std_ReturnType                  udCallBackCsmResult;
    uint16                          u2Reserve;
} SecOC_Rx_AsyncCallBackType;
#endif

typedef struct {
    uint16                  u2BuildRetryCnt;
    uint16                  u2VerifyRetryCnt;
} SecOC_Rx_ProcessType;

typedef struct {
    uint32                  u4InputDataSize;
    uint32                  u4AuthInfoLen;
} SecOC_Rx_CsmProcessType;

typedef struct {
    Crypto_VerifyResultType udVerifyResult;
  #if (SECOC_AB_CACHE_ALIGN_RX_VERIFYRESULT == 1U)
    /* No Reserve area */
  #elif (SECOC_AB_CACHE_ALIGN_RX_VERIFYRESULT == 4U)
    uint8                   u1Reserve[SECOC_RX_RESERVE_SIZE_3];
  #elif (SECOC_AB_CACHE_ALIGN_RX_VERIFYRESULT == 16U)
    uint8                   u1Reserve[SECOC_RX_RESERVE_SIZE_15];
  #elif (SECOC_AB_CACHE_ALIGN_RX_VERIFYRESULT == 32U)
    uint8                   u1Reserve[SECOC_RX_RESERVE_SIZE_31];
  #elif (SECOC_AB_CACHE_ALIGN_RX_VERIFYRESULT == 64U)
    uint8                   u1Reserve[SECOC_RX_RESERVE_SIZE_63];
  #else
    /* No Reserve area */
  #endif
} SecOC_Rx_CsmOutputResultType;

/* for HSM shared RAM. so cache align needed if cache is valid. (16/32/64Byte) */
typedef struct {
    uint8                   u1AuthInfo[SECOC_RX_AUTHINFO_SIZE];
  #if (SECOC_AB_CACHE_ALIGN_RX_AUTHINFO == 16U)
    /* No Reserve area */
  #elif (SECOC_AB_CACHE_ALIGN_RX_AUTHINFO == 32U)
    uint8                   u1Reserve[SECOC_RX_RESERVE_SIZE_16];
  #elif (SECOC_AB_CACHE_ALIGN_RX_AUTHINFO == 64U)
    uint8                   u1Reserve[SECOC_RX_RESERVE_SIZE_48];
  #else
    /* No Reserve area */
  #endif
} SecOC_Rx_CsmInputAuthType;

typedef struct {
    uint16                  u2OverrideStatus;
    uint8                   u1NumberOfMessagesToOverride;
    uint8                   u1OverrideFlag;
} SecOC_Rx_VerifyOverrideType;

typedef struct {
    uint16                  u2OverrideStatus;
    uint8                   u1NumberOfMessagesToOverride;
    uint8                   u1OverrideCounter;
} SecOC_Rx_VerifyOverrideCurrentType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

static FUNC(uint16, SECOC_CODE) SecOC_Rx_VerifyStart
(
    uint16 u2Index
);
static FUNC(uint16, SECOC_CODE) SecOC_Rx_VerifyMac
(
    uint16 u2Index,
    P2CONST(SecOC_Buff_DataType, AUTOMATIC, SECOC_APPL_DATA) ptBuff,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptFullFv,
    uint32 u4FullFvLen
);
static FUNC(uint16, SECOC_CODE) SecOC_Rx_VerifyFinish
(
    uint16 u2Index
);
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
static FUNC(void, SECOC_CODE) SecOC_Rx_VerifyNotify
(
    uint16 u2Index
);
#endif
static FUNC(void, SECOC_CODE) SecOC_Rx_StatusCheck
(
    uint16 u2Index
);
static FUNC(void, SECOC_CODE) SecOC_Rx_ExtractTxFVAuth
(
    uint16 u2Index,
    P2CONST(SecOC_Buff_DataType, AUTOMATIC, SECOC_APPL_DATA) ptBuff,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptTxFv
);
static FUNC(uint16, SECOC_CODE) SecOC_Rx_BuildRetryJudge
(
    uint16 u2Index,
    uint16 u2NgFactor
);
static FUNC(uint16, SECOC_CODE) SecOC_Rx_VerifyRetryJudge
(
    uint16 u2Index,
    uint16 u2NgFactor
);
static FUNC(void, SECOC_CODE) SecOC_Rx_NgNotify
(
    uint16 u2Index,
    SecOC_VerificationResultType udVerifyResult
);
static FUNC(void, SECOC_CODE) SecOC_Rx_NotifyVerResult
(
    uint16 u2Index,
    SecOC_VerificationResultType udResult
);
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
static FUNC(void, SECOC_CODE) SecOC_Rx_AsyncNotifyVerResult
(
    uint16 u2Index,
    SecOC_VerificationResultType udResult
);
static FUNC(void, SECOC_CODE) SecOC_Rx_AsyncNotifyCsmResult
(
    uint16 u2Index,
    Std_ReturnType udResult
);
#endif
static FUNC(void, SECOC_CODE) SecOC_Rx_NotifyFv
(
    uint16 u2Index,
    Std_ReturnType udRet
);
static FUNC(void, SECOC_CODE) SecOC_Rx_NotifyMessage
(
    uint16 u2Index

);
static FUNC(void, SECOC_CODE) SecOC_Rx_NofityVerificationFinalStatus
(
    uint16 u2Index,
    SecOC_VerificationResultType udResult
);
static FUNC(void, SECOC_CODE) SecOC_Rx_VerifyProcExit
(
    uint16 u2Index
);
static FUNC(void, SECOC_CODE) SecOC_Rx_NotifyTpRxIndication
(
    uint16 u2Index,
    Std_ReturnType udResult
);
static FUNC(void, SECOC_CODE) SecOC_Rx_UpperCopy
(
    uint16 u2Index
);
static FUNC(SecOC_VerificationResultType, SECOC_CODE) SecOC_Rx_VerifyStartJudge
(
    uint16 u2Index,
    SecOC_VerificationResultType udResult,
    uint32 u4VerifyStartCount
);
#if( SECOC_OVERRIDE_STATUS_WITH_DATA_ID == STD_ON )
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_SearchDataId
(
    uint32 u4DataId,
    P2VAR(uint16, AUTOMATIC, SECOC_APPL_DATA) ptIndex
);
#else
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_SearchFvId
(
    uint16 u2FvId,
    P2VAR(uint16, AUTOMATIC, SECOC_APPL_DATA) ptIndex
);
#endif
#if ((SECOC_AB_EXTD_MSG_NOTIFY_JUDGE == STD_ON) || (SECOC_AB_FORCE_RECEIVE == STD_ON) || (SECOC_ENABLE_FORCED_PASS_OVERRIDE == STD_ON))
static FUNC(boolean, SECOC_CODE) SecOC_Rx_ForceReceiveJudge
(
    uint16 u2Index
);
#endif
#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_VAR_NO_INIT
#include <SecOC_MemMap.h>

static VAR(SecOC_Rx_CtrlType, SECOC_VAR_NO_INIT) SecOC_Rx_stCtrlInfo[SECOC_RX_PDU_PROCESSING_MAX];
static VAR(SecOC_Rx_ProcessType, SECOC_VAR_NO_INIT) SecOC_Rx_stProcInfo[SECOC_RX_PDU_PROCESSING_MAX];
VAR(uint32, SECOC_VAR_NO_INIT) SecOC_Rx_u4VerifyStartCount[SECOC_AB_BUS_MAX];
static VAR(SecOC_Rx_CsmProcessType, SECOC_VAR_NO_INIT) SecOC_Rx_stCsmProcInfo[SECOC_RX_PDU_PROCESSING_MAX];

#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
static VAR(SecOC_Rx_AsyncCtrlType, SECOC_VAR_NO_INIT) SecOC_Rx_stAsyncCtrlInfo[SECOC_RX_PDU_PROCESSING_MAX];
static VAR(SecOC_Rx_AsyncCallBackType, SECOC_VAR_NO_INIT) SecOC_Rx_stAsyncCallBackInfo[SECOC_RX_PDU_PROCESSING_MAX];
#endif

#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
static VAR(uint16, SECOC_VAR_NO_INIT) SecOC_Rx_u2RamCheckCounter;
static VAR(uint16, SECOC_VAR_NO_INIT) SecOC_Rx_u2RamErrorCounter;
#endif /* SECOC_AB_RAM_ERROR_CHK */
static VAR(uint32, SECOC_VAR_NO_INIT) SecOC_Rx_u4OnePeriodAuthTpCopySize;

static VAR(SecOC_Rx_VerifyOverrideType, SECOC_VAR_NO_INIT) SecOC_Rx_stVerifyOverrideInfo[SECOC_RX_PDU_PROCESSING_MAX];
static VAR(SecOC_Rx_VerifyOverrideCurrentType, SECOC_VAR_NO_INIT) SecOC_Rx_stVerifyOverrideCurrentInfo[SECOC_RX_PDU_PROCESSING_MAX];

#define SECOC_STOP_SEC_VAR_NO_INIT
#include <SecOC_MemMap.h>

/****************************************************************************/
/*****     CSM(HSM) access area. Message data. Input to Csm             *****/
/****************************************************************************/
#define SECOC_START_SEC_SHARED_RXMSG_VAR_NO_INIT
#include <SecOC_MemMap.h>

static VAR(uint8, SECOC_VAR_NO_INIT) SecOC_Rx_CsmInputData[SECOC_RX_INPUT_DATA_LENGTH_TOTAL];

#define SECOC_STOP_SEC_SHARED_RXMSG_VAR_NO_INIT
#include <SecOC_MemMap.h>

/****************************************************************************/
/***** CSM(HSM) access area. Authentication(MAC) data. Input to Csm     *****/
/****************************************************************************/
#define SECOC_START_SEC_SHARED_RXAUTH_VAR_NO_INIT
#include <SecOC_MemMap.h>

static VAR(SecOC_Rx_CsmInputAuthType, SECOC_VAR_NO_INIT) SecOC_Rx_stCsmInputAuthInfo[SECOC_RX_PDU_PROCESSING_MAX];

#define SECOC_STOP_SEC_SHARED_RXAUTH_VAR_NO_INIT
#include <SecOC_MemMap.h>

/****************************************************************************/
/***** CSM(HSM) access area. VerifyResult data. Output from Csm         *****/
/****************************************************************************/
#define SECOC_START_SEC_SHARED_RXRESULT_VAR_NO_INIT
#include <SecOC_MemMap.h>

static VAR(SecOC_Rx_CsmOutputResultType, SECOC_VAR_NO_INIT) SecOC_Rx_stCsmOutputResultInfo[SECOC_RX_PDU_PROCESSING_MAX];

#define SECOC_STOP_SEC_SHARED_RXRESULT_VAR_NO_INIT
#include <SecOC_MemMap.h>



/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

/****************************************************************************/
/* Function Name | SecOC_Rx_Reset                                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Rx_Reset
(
    void
)
{
    uint16  u2_loop;
    
    SecOCStd_MemClr( &SecOC_Rx_stProcInfo[0], sizeof(SecOC_Rx_stProcInfo) );
    SecOCStd_MemClr( &SecOC_Rx_u4VerifyStartCount[0], sizeof(SecOC_Rx_u4VerifyStartCount) );
    SecOCStd_MemClr( &SecOC_Rx_stCsmProcInfo[0], sizeof(SecOC_Rx_stCsmProcInfo) );
    SecOCStd_MemClr( &SecOC_Rx_stCsmInputAuthInfo[0], sizeof(SecOC_Rx_stCsmInputAuthInfo) );
    SecOCStd_MemClr( &SecOC_Rx_CsmInputData[0], sizeof(SecOC_Rx_CsmInputData) );
    
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
    SecOCStd_MemClr( &SecOC_Rx_stAsyncCtrlInfo[0], sizeof(SecOC_Rx_stAsyncCtrlInfo) );
#endif
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
    SecOC_Rx_u2RamCheckCounter = 0U;
    SecOC_Rx_u2RamErrorCounter = 0U;
#endif
    SecOC_Rx_u4OnePeriodAuthTpCopySize = 0U;
    
    for( u2_loop = 0U; u2_loop < SecOC_RxPduProcessingMax; u2_loop++ )
    {
        SecOC_Rx_stCtrlInfo[u2_loop].u1Status = SECOC_RX_ST_IDLE;
        SecOC_Rx_stCsmOutputResultInfo[u2_loop].udVerifyResult = CRYPTO_E_VER_NOT_OK;
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
        SecOC_Rx_stAsyncCallBackInfo[u2_loop].u1CallBackEvt = SECOC_RX_FLAG_FALSE;
        SecOC_Rx_stAsyncCallBackInfo[u2_loop].udCallBackCsmResult = E_NOT_OK;
#endif
        SecOC_Rx_stVerifyOverrideInfo[u2_loop].u2OverrideStatus = SECOC_RX_OVERRIDE_CANCEL;
        SecOC_Rx_stVerifyOverrideInfo[u2_loop].u1NumberOfMessagesToOverride = 0U;
        SecOC_Rx_stVerifyOverrideInfo[u2_loop].u1OverrideFlag = SECOC_RX_FLAG_FALSE;
        SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u2OverrideStatus = SECOC_RX_OVERRIDE_CANCEL;
        SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u1NumberOfMessagesToOverride = 0U;
        SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u1OverrideCounter = 0U;
    }
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_SetVerifyStatusOverride                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u4ValueID     :                                          */
/*               | u2OverrideStatus :                                       */
/*               | u1NumberOfMessagesToOverride :                           */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_SetVerifyStatusOverride
(
    uint32 u4ValueID,
    uint16 u2OverrideStatus,
    uint8  u1NumberOfMessagesToOverride
)
{
    Std_ReturnType  ud_stdRet;
    uint16          u2_index = 0U;

#if( SECOC_OVERRIDE_STATUS_WITH_DATA_ID == STD_OFF )
    if( u4ValueID <= (uint32)SECOC_RX_U2_MAX )
    {
        ud_stdRet = SecOC_Rx_SearchFvId((uint16)u4ValueID, &u2_index);
    }
    else
    {
        ud_stdRet = E_NOT_OK;
    }
#else
    ud_stdRet = SecOC_Rx_SearchDataId(u4ValueID, &u2_index);
#endif /* SECOC_OVERRIDE_STATUS_WITH_DATA_ID */
    if( ud_stdRet == (Std_ReturnType)E_OK )
    {
        SchM_Enter_SecOC_Rx();

        SecOC_Rx_stVerifyOverrideInfo[u2_index].u2OverrideStatus = u2OverrideStatus;
        SecOC_Rx_stVerifyOverrideInfo[u2_index].u1OverrideFlag = SECOC_RX_FLAG_TRUE;
        if( ( u2OverrideStatus == SECOC_RX_OVERRIDE_PASS_UNTIL_LIMIT )
         || ( u2OverrideStatus == SECOC_RX_OVERRIDE_DROP_UNTIL_LIMIT )
         || ( u2OverrideStatus == SECOC_RX_OVERRIDE_SKIP_UNTIL_LIMIT ) )
        {
            SecOC_Rx_stVerifyOverrideInfo[u2_index].u1NumberOfMessagesToOverride = u1NumberOfMessagesToOverride;
        }
        
        SchM_Exit_SecOC_Rx();
    }
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_GetMode                                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | SecOC_ModeType                                           */
/*               |  SECOC_M_IDLE     : Idle                                 */
/*               |  SECOC_M_RUN      : Run                                  */
/*               |  SECOC_M_ABNORMAL : Abnormal                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(SecOC_ModeType, SECOC_CODE) SecOC_Rx_GetMode
(
    void
)
{
    SecOC_ModeType  ud_retMode = SECOC_M_IDLE;
    uint16          u2_loop;
    uint8           u1_status;
    uint8           u1_abnormalFlag = SECOC_RX_FLAG_FALSE;
    
    for( u2_loop = 0U; u2_loop < SecOC_RxPduProcessingMax; u2_loop++ )
    {
        u1_status = SecOC_Rx_stCtrlInfo[u2_loop].u1Status;
        
        if( u1_status == SECOC_RX_ST_IDLE )
        {
            /* Mode IDLE */
        }
        else if( (u1_status == SECOC_RX_ST_RECEIVE)
          || (u1_status == SECOC_RX_ST_VERIFY)
          || (u1_status == SECOC_RX_ST_WAIT_CALLBACK)
          || (u1_status == SECOC_RX_ST_CALLBACK_RECEIVED)
          || (u1_status == SECOC_RX_ST_WAIT_NOTIFY_CALLOUT)
          || (u1_status == SECOC_RX_ST_UPPER_COPY)
          || (u1_status == SECOC_RX_ST_RETRY)
          || (u1_status == SECOC_RX_ST_FV_NG)
          || (u1_status == SECOC_RX_ST_END)
          || (u1_status == SECOC_RX_ST_LOWER_COPY) )
        {
            ud_retMode = SECOC_M_RUN;
        }
        else
        {
            u1_abnormalFlag = SECOC_RX_FLAG_TRUE;
        }
    }
    
    if( (u1_abnormalFlag == SECOC_RX_FLAG_TRUE)
      && (ud_retMode == SECOC_M_IDLE) )
    {
        ud_retMode = SECOC_M_ABNORMAL;
    }
    
    return ud_retMode;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_Receive                                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | ptMsg   :                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Rx_Receive
(
    uint16 u2Index,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptMsg
)
{
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    Std_ReturnType      ud_stdRet = E_NOT_OK;
    SecOC_Buff_DataType st_buff;
    uint8               u1_status;
    BufReq_ReturnType   ud_bufRet;
    uint32              u4_pduNotifyMsgSize;
    PduInfoType         st_pduInfo;
    PduLengthType       u4_pduAvailableDataSize = 0U;
#if (SECOC_AB_RXMSG_OVERFLOW_DESTRUCTION_CALLOUT_MAX > 0U)
    uint16  u2_loop;
#endif

    st_buff.ptData = ptMsg->SduDataPtr;
    st_buff.u4Size = (uint32)ptMsg->SduLength;
    st_pduInfo.SduDataPtr = NULL_PTR;
    st_pduInfo.MetaDataPtr = NULL_PTR;
    st_pduInfo.SduLength = 0U;
    
#if( SECOC_AB_FIXED_MESSAGE_SIZE != STD_ON )
    if( st_buff.u4Size > SecOC_RxPduProcessing[u2Index].SameBufferPduRef )
    {
        st_buff.u4Size = SecOC_RxPduProcessing[u2Index].SameBufferPduRef;
    }
#endif
    
    u4_pduNotifyMsgSize = st_buff.u4Size - ( (uint32)SecOC_RxPduProcessing[u2Index].Ab_TxSecurityDataSize + (uint32)SecOC_RxPduProcessing[u2Index].Ab_ProtDataPaddingSize );
    
    SchM_Enter_SecOC_Rx();
    
    /* Status check */
    u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
    if( u1_status == SECOC_RX_ST_IDLE )
    {
        SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_RECEIVE;
        
        SchM_Exit_SecOC_Rx();
        
        if( SecOC_RxPduProcessing[u2Index].RxAuthPduType == (uint8)SECOC_TPPDU )
        {
            ud_bufRet = SecOC_Connector_PduR_SecOCTpStartOfReception( pt_rxConfig->Ab_RxAuthenticLayerPduRefId, &st_pduInfo, u4_pduNotifyMsgSize, &u4_pduAvailableDataSize );
        }
        else
        {
            ud_bufRet = BUFREQ_OK;
        }
        
        if( ud_bufRet == (BufReq_ReturnType)BUFREQ_OK )
        {
            ud_stdRet = SecOC_Buff_SetOrder( SECOC_BUFF_RX, u2Index, &st_buff );
        }
        if( ud_stdRet != (Std_ReturnType)E_OK )
        {
            SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_IDLE;
            
            if( ud_bufRet == (BufReq_ReturnType)BUFREQ_OK )
            {
                SecOC_Rx_NotifyTpRxIndication( u2Index, E_NOT_OK );
            }
        }
    }
    else if( u1_status == SECOC_RX_ST_RECEIVE )
    {
        if( SecOC_RxPduProcessing[u2Index].RxAuthPduType == (uint8)SECOC_TPPDU )
        {
            SecOC_Connector_PduR_SecOCTpRxIndication( pt_rxConfig->Ab_RxAuthenticLayerPduRefId, E_NOT_OK );
            
            ud_bufRet = SecOC_Connector_PduR_SecOCTpStartOfReception( pt_rxConfig->Ab_RxAuthenticLayerPduRefId, &st_pduInfo, u4_pduNotifyMsgSize, &u4_pduAvailableDataSize );
        }
        else
        {
            ud_bufRet = BUFREQ_OK;
        }
        
        if( ud_bufRet == (BufReq_ReturnType)BUFREQ_OK )
        {
            (void)SecOC_Buff_SetSelect( SECOC_BUFF_RX, u2Index, SECOC_RX_REWRITE_POS, &st_buff ); /* no return check required */
        }
        else
        {
            (void)SecOC_Buff_ClearSelect( SECOC_BUFF_RX, u2Index ); /* no return check required */
            
            SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_IDLE;
        }
        
        SchM_Exit_SecOC_Rx();
        
#if (SECOC_AB_RXMSG_OVERFLOW_DESTRUCTION_CALLOUT_MAX > 0U)
        for( u2_loop = 0U; u2_loop < SecOC_Ab_RxMsgOvfDestCoMax; u2_loop++ )
        {
            if( pt_rxConfig->Ab_RxMsgOverflowDestructionCallout[u2_loop] != NULL_PTR )
            {
                pt_rxConfig->Ab_RxMsgOverflowDestructionCallout[u2_loop]( pt_rxConfig->FreshnessValueId, pt_rxConfig->Ab_DataId,SECOC_AB_DESTRUCTION_OVERRIDE );
            }
        }
#endif

    }
    else
    {
        SchM_Exit_SecOC_Rx();
        
#if (SECOC_AB_RXMSG_OVERFLOW_DESTRUCTION_CALLOUT_MAX > 0U)
        for( u2_loop = 0U; u2_loop < SecOC_Ab_RxMsgOvfDestCoMax; u2_loop++ )
        {
            if( pt_rxConfig->Ab_RxMsgOverflowDestructionCallout[u2_loop] != NULL_PTR )
            {
                pt_rxConfig->Ab_RxMsgOverflowDestructionCallout[u2_loop]( pt_rxConfig->FreshnessValueId, pt_rxConfig->Ab_DataId, SECOC_AB_DESTRUCTION_IGNORE);
            }
        }
#endif
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_MainFuncPeriod                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Rx_MainFuncPeriod
(
    void
)
{
    uint16  u2_loop;
    
    SchM_Enter_SecOC_Rx();

    for( u2_loop = 0U; u2_loop < SecOC_Ab_BusMax; u2_loop++ )
    {
        if( SecOC_Rx_u4VerifyStartCount[u2_loop] <= SecOC_Ab_BusCollection[u2_loop].Ab_VerifyStartCount )
        {
            SecOC_Rx_u4VerifyStartCount[u2_loop]++;
        }
    }
    
    SchM_Exit_SecOC_Rx();
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_ResetBus                                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BusIndex :                                             */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Rx_ResetBus
(
    uint16 u2BusIndex
)
{
    SecOC_Rx_u4VerifyStartCount[u2BusIndex] = 0UL;
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_MainProcess                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | uint16                                                   */
/*               |  SECOC_RX_PROC_OK        :                               */
/*               |  SECOC_RX_PROC_NG_FV     :                               */
/*               |  SECOC_RX_PROC_NG_CSM    :                               */
/*               |  SECOC_RX_PROC_NG_RETRY  :                               */
/*               |  SECOC_RX_PROC_NG_OTHER  :                               */
/*               |  SECOC_RX_PROC_RETRY_MAC :                               */
/*               |  SECOC_RX_PROC_RETRY_FV  :                               */
/*               |  SECOC_RX_PROC_RETRY_CSM :                               */
/*               |  SECOC_RX_PROC_NONE      :                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint16, SECOC_CODE) SecOC_Rx_MainProcess
(
    uint16 u2Index
)
{
    uint16          u2_ret = SECOC_RX_PROC_NONE;
    uint8           u1_status;
    
    u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
    
    if( (u1_status == SECOC_RX_ST_RECEIVE)
      || (u1_status == SECOC_RX_ST_RETRY) )
    {
        /* MAC Verify */
        u2_ret = SecOC_Rx_VerifyStart( u2Index );
        
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
        if( u2_ret == SECOC_RX_PROC_OK )
        {
            /* Receive Message */
            u2_ret = SecOC_Rx_VerifyFinish( u2Index );
        }
#endif
    }
    return u2_ret;
}

#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Rx_VerifyCallback                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | udRet   :                                                */
/* Return Value  | None                                                     */
/* Notes         | Async Only                                               */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Rx_VerifyCallback
(
    uint16 u2Index,
    Std_ReturnType udRet
)
{
    /* Check Processing Message */
    if( u2Index < SecOC_RxPduProcessingMax )
    {
        SchM_Enter_SecOC_Rx();
        SecOC_Rx_stAsyncCallBackInfo[u2Index].u1CallBackEvt = SECOC_RX_FLAG_TRUE;
        SecOC_Rx_stAsyncCallBackInfo[u2Index].udCallBackCsmResult = udRet;
        SchM_Exit_SecOC_Rx();
    }
    
    return ;
}
#endif

/****************************************************************************/
/* Function Name | SecOC_Rx_ReapEvt                                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Return Value  | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Rx_ReapEvt
(
    void
)
{
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
    uint8           u1_status;
    uint8           u1_callbackEvt;
#endif
    uint16          u2_loop;
    
    SchM_Enter_SecOC_Rx();

    for( u2_loop = 0U; u2_loop < SecOC_RxPduProcessingMax; u2_loop++ )
    {
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
        /* Reap callback event for all rx message. */
        u1_status = SecOC_Rx_stCtrlInfo[u2_loop].u1Status;
        u1_callbackEvt = SecOC_Rx_stAsyncCallBackInfo[u2_loop].u1CallBackEvt;
        
        if( (u1_status == SECOC_RX_ST_WAIT_CALLBACK) && (u1_callbackEvt == SECOC_RX_FLAG_TRUE) )
        {
            SecOC_Rx_stCtrlInfo[u2_loop].u1Status = SECOC_RX_ST_CALLBACK_RECEIVED;

            SecOC_Rx_AsyncNotifyCsmResult( u2_loop, SecOC_Rx_stAsyncCallBackInfo[u2_loop].udCallBackCsmResult );
            SecOC_Rx_stAsyncCallBackInfo[u2_loop].u1CallBackEvt = SECOC_RX_FLAG_FALSE;
            SecOC_Rx_stAsyncCallBackInfo[u2_loop].udCallBackCsmResult = E_NOT_OK;
        }
#endif
        
        /* Reflect VerifyStatusOverride */
        if( SecOC_Rx_stVerifyOverrideInfo[u2_loop].u1OverrideFlag == SECOC_RX_FLAG_FALSE )
        {
            /* No Processing */
        }
        else if( SecOC_Rx_stVerifyOverrideInfo[u2_loop].u1OverrideFlag == SECOC_RX_FLAG_TRUE )
        {
            SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u2OverrideStatus = SecOC_Rx_stVerifyOverrideInfo[u2_loop].u2OverrideStatus;
            SecOC_Rx_stVerifyOverrideInfo[u2_loop].u2OverrideStatus = SECOC_RX_OVERRIDE_CANCEL;
            SecOC_Rx_stVerifyOverrideInfo[u2_loop].u1OverrideFlag = SECOC_RX_FLAG_FALSE;
            
            if( ( SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u2OverrideStatus == SECOC_RX_OVERRIDE_PASS_UNTIL_LIMIT )
             || ( SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u2OverrideStatus == SECOC_RX_OVERRIDE_DROP_UNTIL_LIMIT )
             || ( SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u2OverrideStatus == SECOC_RX_OVERRIDE_SKIP_UNTIL_LIMIT ) )
            {
                SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u1NumberOfMessagesToOverride = SecOC_Rx_stVerifyOverrideInfo[u2_loop].u1NumberOfMessagesToOverride;
                SecOC_Rx_stVerifyOverrideInfo[u2_loop].u1NumberOfMessagesToOverride = 0U;
                SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u1OverrideCounter = 0U;
            }
        }
        else
        {
            /* Initialize override variables due to RAM error. */
            SecOC_Rx_stVerifyOverrideInfo[u2_loop].u2OverrideStatus = SECOC_RX_OVERRIDE_CANCEL;
            SecOC_Rx_stVerifyOverrideInfo[u2_loop].u1NumberOfMessagesToOverride = 0U;
            SecOC_Rx_stVerifyOverrideInfo[u2_loop].u1OverrideFlag = SECOC_RX_FLAG_FALSE;
            SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u2OverrideStatus = SECOC_RX_OVERRIDE_CANCEL;
            SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u1NumberOfMessagesToOverride = 0U;
            SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u1OverrideCounter = 0U;
        }
        
        if( ( ( SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u2OverrideStatus == SECOC_RX_OVERRIDE_PASS_UNTIL_LIMIT )
           || ( SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u2OverrideStatus == SECOC_RX_OVERRIDE_DROP_UNTIL_LIMIT )
           || ( SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u2OverrideStatus == SECOC_RX_OVERRIDE_SKIP_UNTIL_LIMIT ) )
         && ( SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u1OverrideCounter >= SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u1NumberOfMessagesToOverride ) )
        {
            SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u2OverrideStatus = SECOC_RX_OVERRIDE_CANCEL;
            SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u1NumberOfMessagesToOverride = 0U;
            SecOC_Rx_stVerifyOverrideCurrentInfo[u2_loop].u1OverrideCounter = 0U;
        }
    }
    SchM_Exit_SecOC_Rx();
    return ;
}

#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Rx_AsyncNotify                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | None                                                     */
/* Notes         | Async Only                                               */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Rx_AsyncNotify
(
    uint16 u2Index
)
{
    uint8           u1_status;
    Std_ReturnType  ud_stdRet;
#if (SECOC_AB_RXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
    uint16          u2_retJudge;
    uint16          u2_loop;
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
#endif
    
    u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
    if( u1_status == SECOC_RX_ST_CALLBACK_RECEIVED )
    {
        ud_stdRet = SecOC_Rx_stAsyncCtrlInfo[u2Index].udCsmResult;

        if( ud_stdRet == (Std_ReturnType)E_OK )
        {
            /* Receive Message */
            (void)SecOC_Rx_VerifyFinish( u2Index );/* no return check required */
        }
        else if( ud_stdRet == (Std_ReturnType)CRYPTO_E_BUSY )
        {
#if (SECOC_AB_RXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
            u2_retJudge = SecOC_Rx_BuildRetryJudge( u2Index, SECOC_RX_PROC_RETRY_CSM );
            
            if( u2_retJudge == SECOC_RX_PROC_NG_RETRY )
            {
                for( u2_loop = 0U; u2_loop < SecOC_Ab_RxMsgBusyDestCoMax; u2_loop++ )
                {
                    if( pt_rxConfig->Ab_RxMsgBusyDestructionCallout[u2_loop] != NULL_PTR )
                    {   
                        pt_rxConfig->Ab_RxMsgBusyDestructionCallout[u2_loop]( pt_rxConfig->FreshnessValueId, pt_rxConfig->Ab_DataId );
                    }
                }
            }
#else
            (void)SecOC_Rx_BuildRetryJudge( u2Index, SECOC_RX_PROC_RETRY_CSM );/* no return check required */
#endif
        }
        else
        {
            /* CSM Error */
            SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_END;
            SecOC_Rx_NgNotify( u2Index, SECOC_VERIFICATIONFAILURE );
        }
        
        /* Get Rx Status */
        u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
    }
    
    if( (u1_status == SECOC_RX_ST_WAIT_NOTIFY_CALLOUT)
      || (u1_status == SECOC_RX_ST_RETRY)
      || (u1_status == SECOC_RX_ST_FV_NG)
      || (u1_status == SECOC_RX_ST_END) )
    {
        /* Rx Notify */
        SecOC_Rx_VerifyNotify( u2Index );
    }
    
    return ;
}
#endif

#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Rx_GetErrorStatus                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | SecOC_ErrorStatusType                                    */
/*               |  SECOC_E_NONE            : No Error                      */
/*               |  SECOC_E_RAM_CHECK_FAIL  : RAM Error                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(SecOC_ErrorStatusType, SECOC_CODE) SecOC_Rx_GetErrorStatus
(
    void
)
{
    SecOC_ErrorStatusType   ud_errorStatus = SECOC_E_RAM_CHECK_FAIL;
    uint16                  u2_index;
    uint8                   u1_status;
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
    uint8                   u1_callbackEvt;
#endif

    u2_index = SecOC_Rx_u2RamCheckCounter;
    
    if( u2_index >= SecOC_RxPduProcessingMax )
    {
        u2_index = 0U;
    }
    
    /* RAM check */
    u1_status = SecOC_Rx_stCtrlInfo[u2_index].u1Status;
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
    u1_callbackEvt = SecOC_Rx_stAsyncCallBackInfo[u2_index].u1CallBackEvt;
#endif

    if( (u1_status == SECOC_RX_ST_IDLE)
      || (u1_status == SECOC_RX_ST_RECEIVE)
      || (u1_status == SECOC_RX_ST_VERIFY)
      || (u1_status == SECOC_RX_ST_WAIT_CALLBACK)
      || (u1_status == SECOC_RX_ST_CALLBACK_RECEIVED)
      || (u1_status == SECOC_RX_ST_WAIT_NOTIFY_CALLOUT)
      || (u1_status == SECOC_RX_ST_UPPER_COPY)
      || (u1_status == SECOC_RX_ST_RETRY)
      || (u1_status == SECOC_RX_ST_FV_NG)
      || (u1_status == SECOC_RX_ST_END)
      || (u1_status == SECOC_RX_ST_LOWER_COPY) )
    {
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
        ud_errorStatus = SECOC_E_NONE;
#else
        if( (u1_callbackEvt == SECOC_RX_FLAG_FALSE)
          || (u1_callbackEvt == SECOC_RX_FLAG_TRUE) )
        {
            ud_errorStatus = SECOC_E_NONE;
        }
#endif
    }
    
    if( ud_errorStatus != SECOC_E_NONE )
    {
        SecOC_Rx_u2RamErrorCounter = SecOC_RxPduProcessingMax;
    }
    
    if( SecOC_Rx_u2RamErrorCounter > (uint16)0U )
    {
        ud_errorStatus = SECOC_E_RAM_CHECK_FAIL;
        SecOC_Rx_u2RamErrorCounter--;
    }
    
    u2_index++;
    SecOC_Rx_u2RamCheckCounter = u2_index;
    
    return ud_errorStatus;
}
#endif

/****************************************************************************/
/* Function Name | SecOC_Rx_ReceiveDivideStart                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index              :                                   */
/*               | ptMsg                :                                   */
/*               | u4SduLength          :                                   */
/*               | ptAvailableMsgSize   :                                   */
/* Return Value  | BufReq_ReturnType                                        */
/*               |  BUFREQ_OK           : Success                           */
/*               |  BUFREQ_E_NOT_OK     : Failure                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_Rx_ReceiveDivideStart
(
    uint16 u2Index,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptMsg,
    uint32 u4SduLength,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptAvailableMsgSize
)
{
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    SecOC_Buff_DataType st_divideData;
    BufReq_ReturnType   ud_bufRet = BUFREQ_E_NOT_OK;
    uint8               u1_status;
    uint8               u1_dataSetFlag = SECOC_RX_FLAG_FALSE;
    uint32              u4_pduNotifyMsgSize;
    uint32              u4_totalMsgSize;
    PduInfoType         st_pduInfo;
    PduLengthType       u4_pduAvailableDataSize = 0U;
    uint8               u1_pdurNotifyFlag = SECOC_RX_FLAG_FALSE;
#if (SECOC_AB_RXMSG_OVERFLOW_DESTRUCTION_CALLOUT_MAX > 0U)
    uint16              u2_loop;
    uint8               u1_notice = SECOC_AB_DESTRUCTION_OVERRIDE;
    uint8               u1_notifyFlag = SECOC_RX_FLAG_FALSE;
#endif
    st_pduInfo.SduDataPtr = NULL_PTR;
    st_pduInfo.MetaDataPtr = NULL_PTR;
    st_pduInfo.SduLength = 0U;
    
    SchM_Enter_SecOC_Rx();
    
    u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
    
    if( u1_status == SECOC_RX_ST_RECEIVE )
    {
        u1_dataSetFlag = SECOC_RX_FLAG_TRUE;
        SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_LOWER_COPY;
        
        (void)SecOC_Buff_ClearSelect( SECOC_BUFF_RX, u2Index ); /* no return check required */

#if (SECOC_AB_RXMSG_OVERFLOW_DESTRUCTION_CALLOUT_MAX > 0U)
        u1_notifyFlag = SECOC_RX_FLAG_TRUE;
        u1_notice = SECOC_AB_DESTRUCTION_OVERRIDE;
#endif
        u1_pdurNotifyFlag = SECOC_RX_FLAG_TRUE;
    }
    else if( u1_status == SECOC_RX_ST_IDLE )
    {
        u1_dataSetFlag = SECOC_RX_FLAG_TRUE;
        SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_LOWER_COPY;
    }
    else if( u1_status == SECOC_RX_ST_LOWER_COPY )
    {
        u1_dataSetFlag = SECOC_RX_FLAG_TRUE;

        (void)SecOC_Buff_ClearSelectSize( SECOC_BUFF_RX, u2Index ); /* no return check required */

#if (SECOC_AB_RXMSG_OVERFLOW_DESTRUCTION_CALLOUT_MAX > 0U)
        u1_notifyFlag = SECOC_RX_FLAG_TRUE;
        u1_notice = SECOC_AB_DESTRUCTION_OVERRIDE;
#endif
        
        u1_pdurNotifyFlag = SECOC_RX_FLAG_TRUE;
    }
    else
    {
        /* No Processing */
#if (SECOC_AB_RXMSG_OVERFLOW_DESTRUCTION_CALLOUT_MAX > 0U)
        u1_notifyFlag = SECOC_RX_FLAG_TRUE;
        u1_notice = SECOC_AB_DESTRUCTION_IGNORE;
#endif
    }
    
    SchM_Exit_SecOC_Rx();

#if (SECOC_AB_RXMSG_OVERFLOW_DESTRUCTION_CALLOUT_MAX > 0U)
    if ( u1_notifyFlag == SECOC_RX_FLAG_TRUE )
    {
         for( u2_loop = 0U; u2_loop < SecOC_Ab_RxMsgOvfDestCoMax; u2_loop++ )
         {
             if( pt_rxConfig->Ab_RxMsgOverflowDestructionCallout[u2_loop] != NULL_PTR )
             {
                 pt_rxConfig->Ab_RxMsgOverflowDestructionCallout[u2_loop]( pt_rxConfig->FreshnessValueId, pt_rxConfig->Ab_DataId, u1_notice );
             }
         }
    }
#endif

    if( u1_dataSetFlag == SECOC_RX_FLAG_TRUE )
    {
        
        u4_totalMsgSize = u4SduLength;
        
        if( u4_totalMsgSize == (uint32)0U )
        {
            u4_totalMsgSize = SecOC_RxPduProcessing[u2Index].SameBufferPduRef;
            u4_pduNotifyMsgSize = 0U;
        }
        else
        {
            u4_pduNotifyMsgSize = u4_totalMsgSize - ( (uint32)SecOC_RxPduProcessing[u2Index].Ab_TxSecurityDataSize + (uint32)SecOC_RxPduProcessing[u2Index].Ab_ProtDataPaddingSize );
        }
        
        if( u1_pdurNotifyFlag == SECOC_RX_FLAG_TRUE )
        {
            SecOC_Rx_NotifyTpRxIndication( u2Index, E_NOT_OK );
        }
        if( SecOC_RxPduProcessing[u2Index].RxAuthPduType == (uint8)SECOC_TPPDU )
        {
            ud_bufRet = SecOC_Connector_PduR_SecOCTpStartOfReception( pt_rxConfig->Ab_RxAuthenticLayerPduRefId, &st_pduInfo, u4_pduNotifyMsgSize, &u4_pduAvailableDataSize );
        }
        else
        {
            ud_bufRet = BUFREQ_OK;
        }
        
        if( ud_bufRet == (BufReq_ReturnType)BUFREQ_OK )
        {
            if( ptMsg->SduLength > (uint32)0U )
            {
                st_divideData.ptData = ptMsg->SduDataPtr;
                st_divideData.u4Size = (uint32)ptMsg->SduLength;
                
                (void)SecOC_Buff_SetSelect( SECOC_BUFF_RX, u2Index, SECOC_RX_REWRITE_POS, &st_divideData ); /* no return check required */
            }
            
            (void)SecOC_Buff_WriteTotalSize( SECOC_BUFF_RX, u2Index, u4_totalMsgSize ); /* no return check required */
            
            *ptAvailableMsgSize = u4_totalMsgSize - (uint32)ptMsg->SduLength;
        }
        else
        {
            SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_IDLE;
        }
    }
    
    return ud_bufRet;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_CopyDivide                                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index                  :                               */
/*               | ptMsg                    :                               */
/*               | ptAvailableMsgSize       :                               */
/* Return Value  | BufReq_ReturnType                                        */
/*               |  BUFREQ_OK               : Success                       */
/*               |  BUFREQ_E_NOT_OK         : Failure                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_Rx_CopyDivide
(
    uint16 u2Index,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptMsg,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) ptAvailableMsgSize
)
{
    SecOC_Buff_DataType st_useBuff;
    SecOC_Buff_DataType st_divideData;
    BufReq_ReturnType   ud_bufRet = BUFREQ_E_NOT_OK;
    Std_ReturnType      ud_stdGetSelectRet;
    Std_ReturnType      ud_stdReadTotalSizeRet;
    Std_ReturnType      ud_stdSetSelectRet;
    uint32              u4_totalMsgSize;
    uint8               u1_status;
    
    u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
    
    if( u1_status == SECOC_RX_ST_LOWER_COPY )
    {
        /* Get Rx Data */
        ud_stdGetSelectRet = SecOC_Buff_GetSelect( SECOC_BUFF_RX, u2Index, &st_useBuff );
        
        /* Get Rx Total Size */
        ud_stdReadTotalSizeRet = SecOC_Buff_ReadTotalSize( SECOC_BUFF_RX, u2Index, &u4_totalMsgSize );
        
        if( ( ud_stdGetSelectRet == (Std_ReturnType)E_OK )
         && ( ud_stdReadTotalSizeRet == (Std_ReturnType)E_OK )
         && ( ( SECOC_RX_UINT32_MAX_VALUE - st_useBuff.u4Size ) >= ptMsg->SduLength ) )
        {
            if( ptMsg->SduLength == (uint32)0U )
            {
                *ptAvailableMsgSize = u4_totalMsgSize - st_useBuff.u4Size;
                ud_bufRet = BUFREQ_OK;
            }
            else if( ( (uint32)ptMsg->SduLength + (uint32)st_useBuff.u4Size ) <= u4_totalMsgSize )
            {
                st_divideData.ptData = ptMsg->SduDataPtr;
                st_divideData.u4Size = (uint32)ptMsg->SduLength;
                
                ud_stdSetSelectRet = SecOC_Buff_SetSelect( SECOC_BUFF_RX, u2Index, st_useBuff.u4Size , &st_divideData );
                
                if( ud_stdSetSelectRet == (Std_ReturnType)E_OK )
                {
                    *ptAvailableMsgSize = u4_totalMsgSize - st_divideData.u4Size;
                    ud_bufRet = BUFREQ_OK;
                }
            }
            else
            {
                /* No Processing */
            }
        }
    }
    return ud_bufRet;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_ReceiveDivideFinish                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index          :                                       */
/*               | udResult         :                                       */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Rx_ReceiveDivideFinish
(
    uint16          u2Index,
    Std_ReturnType  udResult
)
{
    uint8               u1_status;
    Std_ReturnType      ud_stdRet;
#if( SECOC_AB_FIXED_MESSAGE_SIZE == STD_ON )
    Std_ReturnType      ud_stdGetSelectRet;
    SecOC_Buff_DataType st_useBuff;
#endif
    
    u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
    ud_stdRet = udResult;
    
    if( u1_status == SECOC_RX_ST_LOWER_COPY )
    {
#if( SECOC_AB_FIXED_MESSAGE_SIZE == STD_ON )
        /* Get Rx Data */
        ud_stdGetSelectRet = SecOC_Buff_GetSelect( SECOC_BUFF_RX, u2Index, &st_useBuff );
        
        if( ( ud_stdGetSelectRet != (Std_ReturnType)E_OK )
          || ( st_useBuff.u4Size != SecOC_RxPduProcessing[u2Index].SameBufferPduRef ) )
        {
            ud_stdRet = E_NOT_OK;
        }
#endif
        if( ud_stdRet == (Std_ReturnType)E_OK )
        {
            SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_RECEIVE;
            
            (void)SecOC_Buff_SetNextIndex( SECOC_BUFF_RX, u2Index ); /* no return check required */
        }
        else
        {
            (void)SecOC_Buff_ClearSelectSize( SECOC_BUFF_RX, u2Index ); /* no return check required */
            
            SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_IDLE;
            
            SecOC_Rx_NotifyTpRxIndication( u2Index, E_NOT_OK );
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_TpNotify                                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Rx_TpNotify
(
    uint16 u2Index
)
{
    uint8  u1_status;
    if( SecOC_RxPduProcessing[u2Index].RxAuthPduType == (uint8)SECOC_TPPDU )
    {            
        u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
        if( u1_status == SECOC_RX_ST_UPPER_COPY )
        {
            /* Rx TpCopy */
            SecOC_Rx_UpperCopy( u2Index );
        }
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_GetStatus                                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | ptStatus :                                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Rx_GetStatus
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptStatus
)
{
    *ptStatus = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_ClearSelect                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Rx_ClearSelect
(
    uint16 u2Index
)
{
    SecOC_Rx_VerifyProcExit( u2Index );
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_ResetTpCopySize                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Rx_ResetTpCopySize
(
    void
)
{
    SecOC_Rx_u4OnePeriodAuthTpCopySize = 0U;
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_VerifyDropSkip                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Rx_VerifyDropSkip
(
    uint16 u2Index
)
{
    uint16  u2_override;
    uint8   u1_status;
    SecOC_VerificationResultType ud_verifyresult;
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    
    u2_override = SecOC_Rx_stVerifyOverrideCurrentInfo[u2Index].u2OverrideStatus;
    u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
    
    if( ( u2_override == SECOC_RX_OVERRIDE_DROP_UNTIL_NOTICE )
     || ( u2_override == SECOC_RX_OVERRIDE_DROP_UNTIL_LIMIT )
     || ( u2_override == SECOC_RX_OVERRIDE_SKIP_UNTIL_NOTICE )
     || ( u2_override == SECOC_RX_OVERRIDE_SKIP_UNTIL_LIMIT )
     || ( pt_rxConfig->SecuredRxPduVerification == (boolean)FALSE ) )
    {
        if( u1_status == SECOC_RX_ST_RECEIVE )
        {
            ud_verifyresult = SECOC_NO_VERIFICATION;
            
            SecOC_Rx_NotifyVerResult( u2Index, ud_verifyresult );

#if (SECOC_AB_EXTD_VERIFICATION_FINAL_STATUS == STD_ON)
            SecOC_Extd_VerificationFinalStatus( u2Index, ud_verifyresult );
#endif
            SecOC_Rx_NofityVerificationFinalStatus( u2Index, ud_verifyresult );
            
            if( ( u2_override == SECOC_RX_OVERRIDE_SKIP_UNTIL_NOTICE )
             || ( u2_override == SECOC_RX_OVERRIDE_SKIP_UNTIL_LIMIT )
             || ( pt_rxConfig->SecuredRxPduVerification == (boolean)FALSE ) )
            {
                /* SKIP */
                SecOC_Rx_NotifyMessage( u2Index );
                if( SecOC_RxPduProcessing[u2Index].RxAuthPduType == (uint8)SECOC_IFPDU )
                {
                    SecOC_Rx_VerifyProcExit( u2Index );
                }
            }
            else
            {
                /* DROP */
                SecOC_Rx_NotifyTpRxIndication( u2Index, E_NOT_OK );
                SecOC_Rx_VerifyProcExit( u2Index );
            }
            
            if( ( u2_override == SECOC_RX_OVERRIDE_DROP_UNTIL_LIMIT )
             || ( u2_override == SECOC_RX_OVERRIDE_SKIP_UNTIL_LIMIT ) )
            {
                SecOC_Rx_stVerifyOverrideCurrentInfo[u2Index].u1OverrideCounter++;
            }
        }
    }
    
    return ;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | SecOC_Rx_VerifyStart                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | uint16                                                   */
/*               |  SECOC_RX_PROC_OK        :                               */
/*               |  SECOC_RX_PROC_NG_FV     :                               */
/*               |  SECOC_RX_PROC_NG_CSM    :                               */
/*               |  SECOC_RX_PROC_NG_RETRY  :                               */
/*               |  SECOC_RX_PROC_NG_OTHER  :                               */
/*               |  SECOC_RX_PROC_RETRY_FV  :                               */
/*               |  SECOC_RX_PROC_RETRY_CSM :                               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(uint16, SECOC_CODE) SecOC_Rx_VerifyStart
(
    uint16 u2Index
)
{
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    SecOC_Buff_DataType         st_buff;
    Std_ReturnType              ud_buffRet;
    Std_ReturnType              ud_fvRet = E_NOT_OK;
    uint32                      u4_fullFvLen = pt_rxConfig->FreshnessValueLength;
    uint16                      u2_ret = SECOC_RX_PROC_OK;
    uint8                       u1_txFv[SECOC_RX_FV_BUFF_SIZE];
    uint8                       u1_fullFv[SECOC_RX_FV_SIZE];
    uint8                       u1_status;
    
    st_buff.ptData = NULL_PTR;
    st_buff.u4Size = 0U;
    SecOCStd_MemClr( &u1_txFv[0], SECOC_RX_FV_BUFF_SIZE );
    
    /* Status check */
    SecOC_Rx_StatusCheck( u2Index );
    
    u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
    if( u1_status == SECOC_RX_ST_VERIFY )
    {
        /* Get Rx Data */
        ud_buffRet = SecOC_Buff_GetSelect( SECOC_BUFF_RX, u2Index, &st_buff );
        
        if( ud_buffRet == (Std_ReturnType)E_OK )
        {
            if( st_buff.u4Size >= ( (uint32)pt_rxConfig->Ab_TxSecurityDataSize + (uint32)pt_rxConfig->Ab_ProtDataPaddingSize ) )
            {
                /* Extract TxFV and Auth */
                SecOC_Rx_ExtractTxFVAuth( u2Index, &st_buff, &u1_txFv[0] );
                
                /* Get FreshnessValue */
                if( (pt_rxConfig->Ab_QueryFreshnessValue == (uint16)SECOC_AB_FV_CFUNC)
                  && (pt_rxConfig->Ab_FreshnessValueFuncName != NULL_PTR) )
                {
                    ud_fvRet = pt_rxConfig->Ab_FreshnessValueFuncName( pt_rxConfig->FreshnessValueId,
                                                                       &u1_txFv[0],
                                                                       (uint32)pt_rxConfig->FreshnessValueTruncLength,
                                                                       SecOC_Rx_stProcInfo[u2Index].u2VerifyRetryCnt,
                                                                       &u1_fullFv[0],
                                                                       &u4_fullFvLen );
                }
            }
            else
            {
                ud_fvRet = SECOC_E_FV_NOT_OK;
            }
            
#if( SECOC_AB_EXTD_AFTER_GET_RX_FV == STD_ON )
            ud_fvRet = SecOC_Extd_AfterGetRxFv( u2Index, ud_fvRet);
#endif
            
            if( ud_fvRet == SECOC_E_FV_NOT_OK )
            {
                SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_FV_NG;
                u2_ret = SECOC_RX_PROC_NG_FV;
                
                SecOC_Rx_NgNotify( u2Index, SECOC_FRESHNESSFAILURE );
            }
            else if( ud_fvRet == SECOC_E_RETRY )
            {
                u2_ret = SecOC_Rx_VerifyRetryJudge( u2Index, SECOC_RX_PROC_RETRY_FV );
            }
            else if( ud_fvRet != (Std_ReturnType)E_OK )
            {
                SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_END;
                u2_ret = SECOC_RX_PROC_NG_OTHER;
            }
            else
            {
                /* No Processing */
            }
        }
        else
        {
            SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_END;
            u2_ret = SECOC_RX_PROC_NG_OTHER;
        }
    }
    else
    {
        u2_ret = SECOC_RX_PROC_NG_OTHER;
    }
    
    u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
    if( u1_status == SECOC_RX_ST_VERIFY )
    {
        u2_ret = SecOC_Rx_VerifyMac( u2Index, &st_buff, &u1_fullFv[0], u4_fullFvLen );
    }
    
    if( u2_ret == SECOC_RX_PROC_NG_OTHER )
    {
        SecOC_Rx_NotifyTpRxIndication( u2Index, E_NOT_OK );
    }
    
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
    /* Buffer Clear */
    u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
    if( ( SecOC_RxPduProcessing[u2Index].RxAuthPduType == (uint8)SECOC_IFPDU )
          && ( u1_status != SECOC_RX_ST_VERIFY )
          && ( u1_status != SECOC_RX_ST_RETRY ) )
    {
        SecOC_Rx_VerifyProcExit( u2Index );
    }
    else if( ( SecOC_RxPduProcessing[u2Index].RxAuthPduType == (uint8)SECOC_TPPDU )
          && ( u1_status != SECOC_RX_ST_VERIFY )
          && ( u1_status != SECOC_RX_ST_RETRY )
          && ( u1_status != SECOC_RX_ST_UPPER_COPY ) )
    {
        SecOC_Rx_VerifyProcExit( u2Index );
    }
    else
    {
        /* No Processing */
    }
#endif
    
    return u2_ret;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_VerifyMac                                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index     :                                            */
/*               | ptBuff      :                                            */
/*               | ptFullFv    :                                            */
/*               | u4FullFvLen :                                            */
/* Return Value  | uint16                                                   */
/*               |  SECOC_RX_PROC_OK        :                               */
/*               |  SECOC_RX_PROC_NG_CSM    :                               */
/*               |  SECOC_RX_PROC_NG_RETRY  :                               */
/*               |  SECOC_RX_PROC_NG_OTHER  :                               */
/*               |  SECOC_RX_PROC_RETRY_CSM :                               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(uint16, SECOC_CODE) SecOC_Rx_VerifyMac
(
    uint16 u2Index,
    P2CONST(SecOC_Buff_DataType, AUTOMATIC, SECOC_APPL_DATA) ptBuff,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptFullFv,
    uint32 u4FullFvLen
)
{
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    SecOC_Com_BuildAuthDataType st_bldAuth;
    Std_ReturnType              ud_macRet;
    uint16                      u2_ret = SECOC_RX_PROC_OK;
#if (SECOC_AB_RXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
    uint16                      u2_loop;
#endif
    
    SecOC_Rx_stCsmProcInfo[u2Index].u4InputDataSize = SecOC_RxPduProcessing[u2Index].Ab_RxMakeAuthBufferSize;
    SecOC_Rx_stCsmProcInfo[u2Index].u4AuthInfoLen = (uint32)pt_rxConfig->AuthInfoTruncLength;
    st_bldAuth.u4DataId = pt_rxConfig->Ab_DataId;
    st_bldAuth.u2DataIdLength = SecOC_Ab_BusCollection[pt_rxConfig->Ab_BusIndex].Ab_DataIdLength;
    st_bldAuth.ptProtData = ptBuff->ptData;
    st_bldAuth.u4ProtDataSize = ptBuff->u4Size - ( (uint32)pt_rxConfig->Ab_TxSecurityDataSize + (uint32)pt_rxConfig->Ab_ProtDataPaddingSize );
    st_bldAuth.ptFreshnessValue = ptFullFv;
    st_bldAuth.u2FreshnessValueSize = (uint16)((u4FullFvLen + SECOC_COM_BIT2BYTE_ROUND_ADD) >> SECOC_COM_BIT2BYTE_SHIFT);
    
    SecOC_Com_BuildAuthData( &st_bldAuth, &(SecOC_Rx_CsmInputData[SecOC_RxPduProcessing[u2Index].Ab_RxBufferStartOffset]), &(SecOC_Rx_stCsmProcInfo[u2Index].u4InputDataSize) );
    
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
    SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_WAIT_CALLBACK;
#endif
    ud_macRet = SecOC_Connector_Csm_MacVerify( pt_rxConfig->RxAuthServiceConfigRef.CsmJobId,
                                               CRYPTO_OPERATIONMODE_SINGLECALL,
                                               &(SecOC_Rx_CsmInputData[SecOC_RxPduProcessing[u2Index].Ab_RxBufferStartOffset]),
                                               SecOC_Rx_stCsmProcInfo[u2Index].u4InputDataSize,
                                               &(SecOC_Rx_stCsmInputAuthInfo[u2Index].u1AuthInfo[0]),
                                               SecOC_Rx_stCsmProcInfo[u2Index].u4AuthInfoLen,
                                               &SecOC_Rx_stCsmOutputResultInfo[u2Index].udVerifyResult );
    
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
    if( pt_rxConfig->Ab_ErrorDetailNotifyCallout != NULL_PTR )
    {
         pt_rxConfig->Ab_ErrorDetailNotifyCallout( pt_rxConfig->FreshnessValueId, ud_macRet );
    }
#endif
    
    if( ud_macRet == (Std_ReturnType)E_OK )
    {
        /* No Processing */
    }
    else if( ud_macRet == (Std_ReturnType)CRYPTO_E_BUSY )
    {
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
        SecOC_Rx_AsyncNotifyCsmResult( u2Index, ud_macRet );
#endif
        u2_ret = SecOC_Rx_BuildRetryJudge( u2Index, SECOC_RX_PROC_RETRY_CSM );
    }
    else
    {
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
        SecOC_Rx_AsyncNotifyCsmResult( u2Index, ud_macRet );
#endif
        SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_END;
        u2_ret = SECOC_RX_PROC_NG_CSM;
        
        SecOC_Rx_NgNotify( u2Index, SECOC_VERIFICATIONFAILURE );
    }

    if( u2_ret == SECOC_RX_PROC_NG_RETRY)
    {
#if (SECOC_AB_RXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
        for( u2_loop = 0U; u2_loop < SecOC_Ab_RxMsgBusyDestCoMax; u2_loop++ )
        {
            if( pt_rxConfig->Ab_RxMsgBusyDestructionCallout[u2_loop] != NULL_PTR )
            {   
                pt_rxConfig->Ab_RxMsgBusyDestructionCallout[u2_loop]( pt_rxConfig->FreshnessValueId, pt_rxConfig->Ab_DataId );
            }
        }
#endif
    }
    
    return u2_ret;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_VerifyFinish                                    */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | uint16                                                   */
/*               |  SECOC_RX_PROC_OK        :                               */
/*               |  SECOC_RX_PROC_NG_RETRY  :                               */
/*               |  SECOC_RX_PROC_NG_OTHER  :                               */
/*               |  SECOC_RX_PROC_RETRY_MAC :                               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(uint16, SECOC_CODE) SecOC_Rx_VerifyFinish
(
    uint16 u2Index
)
{
    SecOC_VerificationResultType    ud_verificationStatus;
    Std_ReturnType      ud_macResultFvNotify;
    Std_ReturnType      ud_macResult = (Std_ReturnType)E_NOT_OK;
    uint16              u2_ret = SECOC_RX_PROC_OK;
    uint8               u1_status;
    
    u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
    if( u1_status == SECOC_RX_ST_VERIFY )
#else
    if( u1_status == SECOC_RX_ST_CALLBACK_RECEIVED )
#endif
    {
        if( SecOC_Rx_stCsmOutputResultInfo[u2Index].udVerifyResult == CRYPTO_E_VER_OK )
        {
            ud_macResult = (Std_ReturnType)E_OK;
        }
        
#if (SECOC_AB_EXTD_FV_UPDATE_JUDGE == STD_ON)
        ud_macResultFvNotify = SecOC_Extd_PreFvUpdate( u2Index, ud_macResult );
#else
        ud_macResultFvNotify = ud_macResult;
#endif
        SecOC_Rx_NotifyFv( u2Index, ud_macResultFvNotify );
        
        if( ud_macResult == (Std_ReturnType)E_OK )
        {
#if( SECOC_AB_EXTD_PRE_VER_OK_NOTIFY == STD_ON )
            ud_verificationStatus = SecOC_Extd_PreVerOkNotify( u2Index );
#else
            ud_verificationStatus = SECOC_VERIFICATIONSUCCESS;
#endif
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
            SecOC_Rx_NotifyVerResult( u2Index, ud_verificationStatus );
            
    #if (SECOC_AB_EXTD_VERIFICATION_FINAL_STATUS == STD_ON)
            SecOC_Extd_VerificationFinalStatus( u2Index, ud_verificationStatus );
    #endif
            ud_verificationStatus = SecOC_Rx_VerifyStartJudge( u2Index, ud_verificationStatus, SecOC_Rx_u4VerifyStartCount[SecOC_RxPduProcessing[u2Index].Ab_BusIndex]);
            SecOC_Rx_NofityVerificationFinalStatus( u2Index, ud_verificationStatus );

#if( SECOC_AB_EXTD_PRE_VER_OK_NOTIFY == STD_ON )
            if( ud_verificationStatus == SECOC_VERIFICATIONSUCCESS )
            {
                SecOC_Rx_NotifyMessage( u2Index );
            }
#else
            SecOC_Rx_NotifyMessage( u2Index );
#endif
#else
#if( SECOC_AB_EXTD_PRE_VER_OK_NOTIFY == STD_ON )
            if( ud_verificationStatus != SECOC_VERIFICATIONSUCCESS )
            {
                SecOC_Rx_stAsyncCtrlInfo[u2Index].u1NotifyNgFlg = SECOC_RX_FLAG_TRUE;
                SecOC_Rx_stAsyncCtrlInfo[u2Index].udNgResult = ud_verificationStatus;
                SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_END;
            }
            else
            {
                SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_WAIT_NOTIFY_CALLOUT;
            }
#else
            SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_WAIT_NOTIFY_CALLOUT;
#endif
            SecOC_Rx_AsyncNotifyVerResult( u2Index, ud_verificationStatus );
#endif
        }
        else
        {
            u2_ret = SecOC_Rx_VerifyRetryJudge( u2Index, SECOC_RX_PROC_RETRY_MAC );
        }
    }
    else
    {
        u2_ret = SECOC_RX_PROC_NG_OTHER;
    }
    
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
    /* Buffer Clear */
    u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
    if( ( SecOC_RxPduProcessing[u2Index].RxAuthPduType == (uint8)SECOC_IFPDU )
     && ( u1_status != SECOC_RX_ST_RETRY ) )
    {
        SecOC_Rx_VerifyProcExit( u2Index );
    }
    else if( ( SecOC_RxPduProcessing[u2Index].RxAuthPduType == (uint8)SECOC_TPPDU )
          && ( u1_status != SECOC_RX_ST_RETRY )
          && ( u1_status != SECOC_RX_ST_UPPER_COPY ) )
    {
        SecOC_Rx_VerifyProcExit( u2Index );
    }
    else
    {
        /* No Processing */
    }
#endif
    
    return u2_ret;
}

#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Rx_VerifyNotify                                    */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | None                                                     */
/* Notes         | Async Only                                               */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Rx_VerifyNotify
(
    uint16 u2Index
)
{
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    
    uint8   u1_status;
    uint8   u1_notifyNgFlg;
    uint32  u4_verifyStartCount = SecOC_Rx_u4VerifyStartCount[pt_rxConfig->Ab_BusIndex];
#if ((SECOC_AB_EXTD_MSG_NOTIFY_JUDGE == STD_ON) || (SECOC_AB_FORCE_RECEIVE == STD_ON) || (SECOC_ENABLE_FORCED_PASS_OVERRIDE == STD_ON))
    boolean b_forceReceive = (boolean)FALSE;
#endif
    
#if (SECOC_ENABLE_FORCED_PASS_OVERRIDE == STD_ON)
    uint16  u2_Override;
    u2_Override = SecOC_Rx_stVerifyOverrideCurrentInfo[u2Index].u2OverrideStatus;
#endif
    u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
    u1_notifyNgFlg = SecOC_Rx_stAsyncCtrlInfo[u2Index].u1NotifyNgFlg;
    
    if( SecOC_Rx_stAsyncCtrlInfo[u2Index].u1NotifyCsmResultFlg == SECOC_RX_FLAG_TRUE )
    {
        if( pt_rxConfig->Ab_ErrorDetailNotifyCallout != NULL_PTR )
        {
             pt_rxConfig->Ab_ErrorDetailNotifyCallout( pt_rxConfig->FreshnessValueId, SecOC_Rx_stAsyncCtrlInfo[u2Index].udCsmResult );
        }
    }
    
    if( SecOC_Rx_stAsyncCtrlInfo[u2Index].u1NotifyVerResultFlg == SECOC_RX_FLAG_TRUE )
    {
#if (SECOC_ENABLE_FORCED_PASS_OVERRIDE == STD_ON)
        if( ( ( u2_Override == SECOC_RX_OVERRIDE_PASS_UNTIL_NOTICE )
           || ( u2_Override == SECOC_RX_OVERRIDE_PASS_UNTIL_LIMIT ) )
         && ( u1_notifyNgFlg == SECOC_RX_FLAG_TRUE ) )
        {
            SecOC_Rx_stAsyncCtrlInfo[u2Index].udVerResult = SECOC_VERIFICATIONFAILURE_OVERWRITTEN;
            SecOC_Rx_stAsyncCtrlInfo[u2Index].udNgResult = SECOC_VERIFICATIONFAILURE_OVERWRITTEN;
        }
#endif
        SecOC_Rx_NotifyVerResult( u2Index, SecOC_Rx_stAsyncCtrlInfo[u2Index].udVerResult );
    }
    
    if( u1_notifyNgFlg == SECOC_RX_FLAG_TRUE )
    {
#if (SECOC_AB_EXTD_VERIFICATION_FINAL_STATUS == STD_ON)
        SecOC_Extd_VerificationFinalStatus( u2Index, SecOC_Rx_stAsyncCtrlInfo[u2Index].udNgResult );
#endif
        SecOC_Rx_stAsyncCtrlInfo[u2Index].udNgResult = SecOC_Rx_VerifyStartJudge( u2Index, SecOC_Rx_stAsyncCtrlInfo[u2Index].udNgResult, u4_verifyStartCount );
        SecOC_Rx_NofityVerificationFinalStatus( u2Index, SecOC_Rx_stAsyncCtrlInfo[u2Index].udNgResult );
        
#if ((SECOC_AB_EXTD_MSG_NOTIFY_JUDGE == STD_ON) || (SECOC_AB_FORCE_RECEIVE == STD_ON) || (SECOC_ENABLE_FORCED_PASS_OVERRIDE == STD_ON))
        b_forceReceive = SecOC_Rx_ForceReceiveJudge( u2Index );
       
        if( (b_forceReceive == (boolean)TRUE)
         || ( (pt_rxConfig->Ab_MessageType == (uint8)SECOC_AB_MSGTYPE_SECURED)
           && (u4_verifyStartCount <= SecOC_Ab_BusCollection[pt_rxConfig->Ab_BusIndex].Ab_VerifyStartCount) ) )
#else
        if( (pt_rxConfig->Ab_MessageType == (uint8)SECOC_AB_MSGTYPE_SECURED)
         && (u4_verifyStartCount <= SecOC_Ab_BusCollection[pt_rxConfig->Ab_BusIndex].Ab_VerifyStartCount) )
#endif
        {
            SecOC_Rx_NotifyMessage( u2Index );
        }
        else
        {
            SecOC_Rx_NotifyTpRxIndication( u2Index, E_NOT_OK );
        }
    }
    else
    {
        if( u1_status == SECOC_RX_ST_WAIT_NOTIFY_CALLOUT )
        {
#if (SECOC_AB_EXTD_VERIFICATION_FINAL_STATUS == STD_ON)
            SecOC_Extd_VerificationFinalStatus( u2Index, SECOC_VERIFICATIONSUCCESS );
#endif
            SecOC_Rx_NofityVerificationFinalStatus( u2Index, SECOC_VERIFICATIONSUCCESS );
            SecOC_Rx_NotifyMessage( u2Index );
        }
    }
    
    SecOCStd_MemClr( &SecOC_Rx_stAsyncCtrlInfo[u2Index], sizeof(SecOC_Rx_AsyncCtrlType) );
    u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
    
    
    /* Buffer Clear */
    if( ( SecOC_RxPduProcessing[u2Index].RxAuthPduType == (uint8)SECOC_IFPDU )
     && ( u1_status != SECOC_RX_ST_RETRY ) )
    {
        SecOC_Rx_VerifyProcExit( u2Index );
    }
    else if( ( SecOC_RxPduProcessing[u2Index].RxAuthPduType == (uint8)SECOC_TPPDU )
          && ( u1_status != SECOC_RX_ST_RETRY )
          && ( u1_status != SECOC_RX_ST_UPPER_COPY ) )
    {
        SecOC_Rx_VerifyProcExit( u2Index );
    }
    else
    {
        /* No Processing */
    }
    
    return ;
}
#endif

/****************************************************************************/
/* Function Name | SecOC_Rx_StatusCheck                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Rx_StatusCheck
(
    uint16 u2Index
)
{
    uint8   u1_status;
    SchM_Enter_SecOC_Rx();
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
    SecOC_Rx_stAsyncCallBackInfo[u2Index].u1CallBackEvt = SECOC_RX_FLAG_FALSE;
    SecOC_Rx_stAsyncCallBackInfo[u2Index].udCallBackCsmResult = E_NOT_OK;
#endif
    u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
    if( u1_status == SECOC_RX_ST_RECEIVE )
    {
        SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_VERIFY;
    }
    else if( u1_status == SECOC_RX_ST_RETRY )
    {
        SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_VERIFY;
    }
    else
    {
        SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_END;
    }
    
    SchM_Exit_SecOC_Rx();
    
    if( u1_status == SECOC_RX_ST_RECEIVE )
    {
        SecOC_Rx_stProcInfo[u2Index].u2BuildRetryCnt = 0U;
        SecOC_Rx_stProcInfo[u2Index].u2VerifyRetryCnt = 0U;
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
        SecOCStd_MemClr( &SecOC_Rx_stAsyncCtrlInfo[u2Index], sizeof(SecOC_Rx_AsyncCtrlType) );
#endif
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_ExtractTxFVAuth                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | ptBuff  :                                                */
/*               | ptTxFv  :                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Rx_ExtractTxFVAuth
(
    uint16 u2Index,
    P2CONST(SecOC_Buff_DataType, AUTOMATIC, SECOC_APPL_DATA) ptBuff,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptTxFv 
)
{
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) pt_authWork;
    uint16  u2_size;
    uint16  u2_surplus;
    uint32  u4_offset;
    uint16  u2_fvOffset;
    uint16  u2_length;
    uint16  u2_authSftR;
    uint16  u2_loop;
    uint16  u2_index;
    
    if( ptBuff->u4Size >= pt_rxConfig->Ab_TxSecurityDataSize )
    {
        u4_offset = ptBuff->u4Size - pt_rxConfig->Ab_TxSecurityDataSize;
        
        /* Tx freshness value */
        u2_size = (uint16)(((uint32)pt_rxConfig->FreshnessValueTruncLength + SECOC_COM_BIT2BYTE_ROUND_ADD) >> SECOC_COM_BIT2BYTE_SHIFT);
        
        (void)SecOCStd_MemCpy( ptTxFv, &ptBuff->ptData[u4_offset], (uint32)u2_size ); /* no return check required */
        
        /* Tx authenticator */
        u2_fvOffset = (uint16)((uint32)pt_rxConfig->FreshnessValueTruncLength >> SECOC_COM_BIT2BYTE_SHIFT);
        u2_length = (uint16)((uint32)pt_rxConfig->FreshnessValueTruncLength & SECOC_COM_BIT2BYTE_SURPLUS);
        u2_authSftR = (uint16)SECOC_RX_BIT_8 - u2_length;
        u2_size = (uint16)((uint32)pt_rxConfig->AuthInfoTruncLength >> SECOC_COM_BIT2BYTE_SHIFT);
        u2_surplus = (uint16)((uint32)pt_rxConfig->AuthInfoTruncLength & SECOC_COM_BIT2BYTE_SURPLUS);
        
        pt_authWork = &ptBuff->ptData[u4_offset + u2_fvOffset];
        u2_index = 0U;
        
        for( u2_loop = 0U; u2_loop < u2_size; u2_loop++ )
        {
            SecOC_Rx_stCsmInputAuthInfo[u2Index].u1AuthInfo[u2_loop] = (uint8)((uint32)pt_authWork[u2_index] << u2_length);
            u2_index++;
            SecOC_Rx_stCsmInputAuthInfo[u2Index].u1AuthInfo[u2_loop] |= (uint8)((uint32)pt_authWork[u2_index] >> u2_authSftR);
        }
        
        if( u2_surplus != (uint16)0U )
        {
            if( u2_surplus <= u2_authSftR )
            {
                SecOC_Rx_stCsmInputAuthInfo[u2Index].u1AuthInfo[u2_loop] = (uint8)((uint32)pt_authWork[u2_index] << u2_length);
            }
            else
            {
                SecOC_Rx_stCsmInputAuthInfo[u2Index].u1AuthInfo[u2_loop] = (uint8)((uint32)pt_authWork[u2_index] << u2_length);
                u2_index++;
                SecOC_Rx_stCsmInputAuthInfo[u2Index].u1AuthInfo[u2_loop] |= (uint8)((uint32)pt_authWork[u2_index] >> u2_authSftR);
            }
        }
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_BuildRetryJudge                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index    :                                             */
/*               | u2NgFactor :                                             */
/* Return Value  | uint16                                                   */
/*               |  SECOC_RX_PROC_NG_RETRY :                                */
/*               |  SECOC_RX_PROC_NG_OTHER :                                */
/*               |  u2NgFactor             :                                */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(uint16, SECOC_CODE) SecOC_Rx_BuildRetryJudge
(
    uint16 u2Index,
    uint16 u2NgFactor
)
{
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    uint16  u2_ret = SECOC_RX_PROC_NG_OTHER;
    uint8   u1_status;
    
    if( SecOC_Rx_stProcInfo[u2Index].u2BuildRetryCnt < pt_rxConfig->AuthenticationBuildAttempts )
    {
        u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;

#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
        if( u1_status == SECOC_RX_ST_VERIFY )
#else
        if( ( u1_status == SECOC_RX_ST_WAIT_CALLBACK )
         || ( u1_status == SECOC_RX_ST_CALLBACK_RECEIVED ) )
#endif
        {
            SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_RETRY;
            SecOC_Rx_stProcInfo[u2Index].u2BuildRetryCnt++;
            u2_ret = u2NgFactor;
        }
        
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
        SecOC_Rx_NotifyVerResult( u2Index, SECOC_AUTHENTICATIONBUILDFAILURE );
#else
        SecOC_Rx_AsyncNotifyVerResult( u2Index, SECOC_AUTHENTICATIONBUILDFAILURE );
#endif
    }
    else
    {
        SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_END;
        
        SecOC_Rx_NgNotify( u2Index, SECOC_AUTHENTICATIONBUILDFAILURE );
        
        u2_ret = SECOC_RX_PROC_NG_RETRY;
    }
    
    return u2_ret;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_VerifyRetryJudge                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index    :                                             */
/*               | u2NgFactor :                                             */
/* Return Value  | uint16                                                   */
/*               |  SECOC_RX_PROC_NG_RETRY :                                */
/*               |  SECOC_RX_PROC_NG_OTHER :                                */
/*               |  u2NgFactor             :                                */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(uint16, SECOC_CODE) SecOC_Rx_VerifyRetryJudge
(
    uint16 u2Index,
    uint16 u2NgFactor
)
{
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    SecOC_VerificationResultType    ud_result = SECOC_VERIFICATIONFAILURE;
    uint16                          u2_ret = SECOC_RX_PROC_NG_OTHER;
    uint8                           u1_status;
    
    if( u2NgFactor == SECOC_RX_PROC_RETRY_FV )
    {
        ud_result = SECOC_FRESHNESSFAILURE;
    }

    if( SecOC_Rx_stProcInfo[u2Index].u2VerifyRetryCnt < pt_rxConfig->AuthenticationVerifyAttempts )
    {
        u1_status = SecOC_Rx_stCtrlInfo[u2Index].u1Status;
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
        if( u1_status == SECOC_RX_ST_VERIFY )
#else
        if( ( u1_status == SECOC_RX_ST_VERIFY )
         || ( u1_status == SECOC_RX_ST_CALLBACK_RECEIVED ) )
#endif
        {
            SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_RETRY;
            SecOC_Rx_stProcInfo[u2Index].u2VerifyRetryCnt++;
            SecOC_Rx_stProcInfo[u2Index].u2BuildRetryCnt = 0U;
            u2_ret = u2NgFactor;
        }
        
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
        SecOC_Rx_NotifyVerResult( u2Index, ud_result );
#else
        SecOC_Rx_AsyncNotifyVerResult( u2Index, ud_result );
#endif
    }
    else
    {
        SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_END;
        
        SecOC_Rx_NgNotify( u2Index, ud_result );
        
        u2_ret = SECOC_RX_PROC_NG_RETRY;
    }
    
    return u2_ret;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_NgNotify                                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Rx_NgNotify
(
    uint16 u2Index,
    SecOC_VerificationResultType udVerifyResult
)
{
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    uint32  u4_verifyStartCount = SecOC_Rx_u4VerifyStartCount[pt_rxConfig->Ab_BusIndex];

#if ((SECOC_AB_EXTD_MSG_NOTIFY_JUDGE == STD_ON) || (SECOC_AB_FORCE_RECEIVE == STD_ON) || (SECOC_ENABLE_FORCED_PASS_OVERRIDE == STD_ON))
    boolean                         b_forceReceive = (boolean)FALSE;
#endif

    SecOC_VerificationResultType    ud_verifyResult = udVerifyResult;

    #if (SECOC_ENABLE_FORCED_PASS_OVERRIDE == STD_ON)
    uint16  u2_Override;
    u2_Override = SecOC_Rx_stVerifyOverrideCurrentInfo[u2Index].u2OverrideStatus;

    if( ( u2_Override == SECOC_RX_OVERRIDE_PASS_UNTIL_NOTICE )
     || ( u2_Override == SECOC_RX_OVERRIDE_PASS_UNTIL_LIMIT ) )
    {
        ud_verifyResult = SECOC_VERIFICATIONFAILURE_OVERWRITTEN;
    }
    #endif
    
    SecOC_Rx_NotifyVerResult( u2Index, ud_verifyResult );
    
    #if (SECOC_AB_EXTD_VERIFICATION_FINAL_STATUS == STD_ON)
    SecOC_Extd_VerificationFinalStatus( u2Index, ud_verifyResult );
    #endif
    ud_verifyResult = SecOC_Rx_VerifyStartJudge( u2Index, ud_verifyResult, u4_verifyStartCount );
    SecOC_Rx_NofityVerificationFinalStatus( u2Index, ud_verifyResult );
    
#if ((SECOC_AB_EXTD_MSG_NOTIFY_JUDGE == STD_ON) || (SECOC_AB_FORCE_RECEIVE == STD_ON) || (SECOC_ENABLE_FORCED_PASS_OVERRIDE == STD_ON))
    b_forceReceive = SecOC_Rx_ForceReceiveJudge( u2Index );

    if( (b_forceReceive == (boolean)TRUE)
      || ( (pt_rxConfig->Ab_MessageType == (uint8)SECOC_AB_MSGTYPE_SECURED)
        && (u4_verifyStartCount <= SecOC_Ab_BusCollection[pt_rxConfig->Ab_BusIndex].Ab_VerifyStartCount) ) )
#else
    if( (pt_rxConfig->Ab_MessageType == (uint8)SECOC_AB_MSGTYPE_SECURED)
        && (u4_verifyStartCount <= SecOC_Ab_BusCollection[pt_rxConfig->Ab_BusIndex].Ab_VerifyStartCount) )
#endif
    {
        SecOC_Rx_NotifyMessage( u2Index );
    }
    else
    {
        SecOC_Rx_NotifyTpRxIndication( u2Index, E_NOT_OK );
    }
    
#else
    SecOC_Rx_AsyncNotifyVerResult( u2Index, udVerifyResult );
    
    SecOC_Rx_stAsyncCtrlInfo[u2Index].u1NotifyNgFlg = SECOC_RX_FLAG_TRUE;
    SecOC_Rx_stAsyncCtrlInfo[u2Index].udNgResult = udVerifyResult;
    
#endif
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_NotifyVerResult                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index  :                                               */
/*               | udResult :                                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Rx_NotifyVerResult
(
    uint16 u2Index,
    SecOC_VerificationResultType udResult
)
{
#if (SECOC_VERIFICATION_STATUS_CALLOUT_MAX > 0U)
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    SecOC_VerificationStatusType    st_verifyResult;
    uint16                          u2_loop;
    
    st_verifyResult.freshnessValueID = pt_rxConfig->FreshnessValueId;
    st_verifyResult.verificationStatus = udResult;
    st_verifyResult.Ab_SecOCDataId = pt_rxConfig->Ab_DataId;
    
    if( (pt_rxConfig->VerifyStatusPropagationMode == (uint16)SECOC_BOTH)
      || ( (pt_rxConfig->VerifyStatusPropagationMode == (uint16)SECOC_FAILURE_ONLY)
        && (udResult != SECOC_VERIFICATIONSUCCESS) ) )
    {
        for( u2_loop = 0U; u2_loop < SecOC_VerStaCoMax; u2_loop++ )
        {
            if( SecOC_VerificationStatusCallout[u2_loop] != NULL_PTR )
            {
                SecOC_VerificationStatusCallout[u2_loop]( st_verifyResult );
            }
        }
    }
#endif
    
    return ;
}

#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Rx_AsyncNotifyVerResult                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index  :                                               */
/*               | udResult :                                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Rx_AsyncNotifyVerResult
(
    uint16 u2Index,
    SecOC_VerificationResultType udResult
)
{
    SecOC_Rx_stAsyncCtrlInfo[u2Index].u1NotifyVerResultFlg = SECOC_RX_FLAG_TRUE;
    SecOC_Rx_stAsyncCtrlInfo[u2Index].udVerResult = udResult;
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_AsyncNotifyCsmResult                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index  :                                               */
/*               | udResult :                                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Rx_AsyncNotifyCsmResult
(
    uint16 u2Index,
    Std_ReturnType udResult
)
{
    SecOC_Rx_stAsyncCtrlInfo[u2Index].u1NotifyCsmResultFlg = SECOC_RX_FLAG_TRUE;
    SecOC_Rx_stAsyncCtrlInfo[u2Index].udCsmResult = udResult;
    
    return ;
}
#endif

/****************************************************************************/
/* Function Name | SecOC_Rx_NotifyFv                                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | udRet   :                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Rx_NotifyFv
(
    uint16 u2Index,
    Std_ReturnType udRet
)
{
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    SecOC_VerificationStatusType        st_verifyResult;
    
    if( pt_rxConfig->Ab_QueryFreshnessValue == (uint16)SECOC_AB_FV_CFUNC )
    {
        st_verifyResult.freshnessValueID = pt_rxConfig->FreshnessValueId;
        st_verifyResult.verificationStatus = SECOC_VERIFICATIONFAILURE;
        st_verifyResult.Ab_SecOCDataId = pt_rxConfig->Ab_DataId;
        
        if( udRet == (Std_ReturnType)E_OK )
        {
            st_verifyResult.verificationStatus = SECOC_VERIFICATIONSUCCESS;
        }
        
        if( pt_rxConfig->Ab_FreshnessValueCallout != NULL_PTR )
        {
            pt_rxConfig->Ab_FreshnessValueCallout( st_verifyResult );
        }
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_NotifyMessage                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               |                                                          */
/* Return Value  | None                                                     */
/*               |                                                          */
/*               |                                                          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Rx_NotifyMessage
(
    uint16 u2Index

)
{
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    PduInfoType         st_pduInfo;
    SecOC_Buff_DataType st_buff;
    
    st_pduInfo.SduLength = 0U;
    st_pduInfo.MetaDataPtr = NULL_PTR;
    
    /* Get RxData for Buffer */
    (void)SecOC_Buff_GetSelect( SECOC_BUFF_RX, u2Index, &st_buff ); /* no return check required */
    
    st_pduInfo.SduDataPtr = st_buff.ptData;
    
    if( st_buff.u4Size >= ( (uint32)SecOC_RxPduProcessing[u2Index].Ab_TxSecurityDataSize + (uint32)SecOC_RxPduProcessing[u2Index].Ab_ProtDataPaddingSize ) )
    {
        st_pduInfo.SduLength = st_buff.u4Size - ( (uint32)SecOC_RxPduProcessing[u2Index].Ab_TxSecurityDataSize + (uint32)SecOC_RxPduProcessing[u2Index].Ab_ProtDataPaddingSize );
    }
    
    if( SecOC_RxPduProcessing[u2Index].RxAuthPduType == (uint8)SECOC_IFPDU )
    {
        SecOC_Connector_PduR_SecOCIfRxIndication( pt_rxConfig->Ab_RxAuthenticLayerPduRefId, &st_pduInfo );
    }
    else
    {
        SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_UPPER_COPY;
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_NofityVerificationFinalStatus                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index  :                                               */
/*               | udResult :                                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Rx_NofityVerificationFinalStatus
(
    uint16 u2Index,
    SecOC_VerificationResultType udResult
)
{
#if (SECOC_AB_VERIFICATION_FINAL_STATUS_CALLOUT_MAX > 0U)
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    SecOC_VerificationStatusType               st_verifyResult;
    uint16                                     u2_loop;
    SecOC_Buff_DataType                        st_buff;
    Std_ReturnType                             ud_buffRet;
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) pt_sduData;
    PduLengthType                              u4_sduLength;
    
    if( (pt_rxConfig->Ab_VerifyFinalStatusPropagationMode == (uint16)SECOC_BOTH)
      || ( (pt_rxConfig->Ab_VerifyFinalStatusPropagationMode == (uint16)SECOC_FAILURE_ONLY)
        && (udResult != SECOC_VERIFICATIONSUCCESS) ) )
    {
        /* parameter setting */
        st_verifyResult.freshnessValueID = pt_rxConfig->FreshnessValueId;
        st_verifyResult.verificationStatus = udResult;
        st_verifyResult.Ab_SecOCDataId = pt_rxConfig->Ab_DataId;

        /* Get message data from Buffer */
        ud_buffRet = SecOC_Buff_GetSelect( SECOC_BUFF_RX, u2Index, &st_buff );
        
        if( ud_buffRet == (Std_ReturnType)E_OK )
        {
            pt_sduData   = st_buff.ptData;
            u4_sduLength = st_buff.u4Size;
        }
        else
        {
            pt_sduData   = NULL_PTR;
            u4_sduLength = 0U;
        }

        /* indicate VerificationFinalStatusCallout */
        for( u2_loop = 0U; u2_loop < SecOC_Ab_VerFinStaCoMax; u2_loop++ )
        {
            if( pt_rxConfig->Ab_VerificationFinalStatusCallout[u2_loop] != NULL_PTR )
            {
                pt_rxConfig->Ab_VerificationFinalStatusCallout[u2_loop]( st_verifyResult, pt_sduData, u4_sduLength );
            }
        }
    }
#endif
    
    return ;
}



/****************************************************************************/
/* Function Name | SecOC_Rx_VerifyProcExit                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Rx_VerifyProcExit
(
    uint16 u2Index 
)
{
    Std_ReturnType  ud_buffRet;
    
    ud_buffRet = SecOC_Buff_ClearSelect( SECOC_BUFF_RX, u2Index );
    if( ud_buffRet == (Std_ReturnType)E_OK )
    {
        SecOCStd_MemClr( &SecOC_Rx_stProcInfo[u2Index], sizeof(SecOC_Rx_ProcessType) );
        SecOCStd_MemClr( &SecOC_Rx_stCsmProcInfo[u2Index], sizeof(SecOC_Rx_CsmProcessType) );
        SecOCStd_MemClr( &SecOC_Rx_stCsmInputAuthInfo[u2Index], sizeof(SecOC_Rx_CsmInputAuthType) );
        SecOC_Rx_stCsmOutputResultInfo[u2Index].udVerifyResult = CRYPTO_E_VER_NOT_OK;
        (void)SecOC_Buff_WriteDividePos( SECOC_BUFF_RX, u2Index, 0U ); /* no return check required */
        
        SecOC_Rx_stCtrlInfo[u2Index].u1Status = SECOC_RX_ST_IDLE;
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_NotifyTpRxIndication                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index   :                                              */
/*               | udResult  :                                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Rx_NotifyTpRxIndication
(
    uint16 u2Index,
    Std_ReturnType udResult
)
{
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    
    if( SecOC_RxPduProcessing[u2Index].RxAuthPduType == (uint8)SECOC_TPPDU )
    {
        SecOC_Connector_PduR_SecOCTpRxIndication( pt_rxConfig->Ab_RxAuthenticLayerPduRefId, udResult );
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_UpperCopy                                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index:                                                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Rx_UpperCopy
(
    uint16 u2Index
)
{
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    uint8               u1_ngCopyFlag = SECOC_RX_FLAG_FALSE;
    SecOC_Buff_DataType st_buff;
    Std_ReturnType      ud_stdGetSelectRet;
    Std_ReturnType      ud_stdReadDividePosRet;
    uint32              u4_divideDataPos = 0U;
    BufReq_ReturnType   ud_buffRet = BUFREQ_E_NOT_OK;
    PduInfoType         st_pduInfo;
    uint32              u4_diffMsgSize = 0U;
    PduLengthType       ud_pduAvailableDataSize = 0U;
    uint32              u4_remainAuthTpCopySize = 0U;
    uint32              u4_useSize;
    
    SecOCStd_MemClr( &st_pduInfo, sizeof(PduInfoType) );

    /* Get Rx Data */
    ud_stdGetSelectRet = SecOC_Buff_GetSelect( SECOC_BUFF_RX, u2Index, &st_buff );
    
    ud_stdReadDividePosRet = SecOC_Buff_ReadDividePos( SECOC_BUFF_RX, u2Index, &u4_divideDataPos );
    
    if( ( ud_stdGetSelectRet == (Std_ReturnType)E_OK )
     && ( ud_stdReadDividePosRet == (Std_ReturnType)E_OK ) )
    {
        if( st_buff.u4Size >= ( (uint32)SecOC_RxPduProcessing[u2Index].Ab_TxSecurityDataSize + (uint32)SecOC_RxPduProcessing[u2Index].Ab_ProtDataPaddingSize ) )
        {
            st_buff.u4Size -= ( (uint32)SecOC_RxPduProcessing[u2Index].Ab_TxSecurityDataSize + (uint32)SecOC_RxPduProcessing[u2Index].Ab_ProtDataPaddingSize );
            
            if( u4_divideDataPos <= st_buff.u4Size )
            {
                u4_diffMsgSize = st_buff.u4Size - u4_divideDataPos;
                
                st_pduInfo.SduDataPtr = &st_buff.ptData[u4_divideDataPos];
            }
            else
            {
                u1_ngCopyFlag = SECOC_RX_FLAG_TRUE;
            }
        }
        else
        {
            u1_ngCopyFlag = SECOC_RX_FLAG_TRUE;
        }
    }
    else
    {
        u1_ngCopyFlag = SECOC_RX_FLAG_TRUE;
    }
    
    if( u1_ngCopyFlag == SECOC_RX_FLAG_FALSE )
    {
        if( SecOC_RxPduProcessing[u2Index].Ab_RxAuthTpCopySize <= u4_diffMsgSize )
        {
            st_pduInfo.SduLength = SecOC_RxPduProcessing[u2Index].Ab_RxAuthTpCopySize;
        }
        else
        {
            st_pduInfo.SduLength = u4_diffMsgSize;
        }
        
        if( SecOC_Ab_RxAuthTpCopyTotalSize > SecOC_Rx_u4OnePeriodAuthTpCopySize)
        {
            u4_remainAuthTpCopySize = SecOC_Ab_RxAuthTpCopyTotalSize - SecOC_Rx_u4OnePeriodAuthTpCopySize;
        }
        
        if( st_pduInfo.SduLength > u4_remainAuthTpCopySize )
        {
            st_pduInfo.SduLength = u4_remainAuthTpCopySize;
        }
        
        if( st_pduInfo.SduLength > 0U )
        {
            u4_useSize = u4_divideDataPos + st_pduInfo.SduLength;
            
            /* Size check */
            if( u4_useSize <= SecOC_RxPduProcessing[u2Index].SameBufferPduRef )
            {
                ud_buffRet = SecOC_Connector_PduR_SecOCTpCopyRxData( pt_rxConfig->Ab_RxAuthenticLayerPduRefId, &st_pduInfo, &ud_pduAvailableDataSize );
            }
        }
        else
        {
            ud_buffRet = BUFREQ_OK;
        }
        
        if( ud_buffRet == (BufReq_ReturnType)BUFREQ_OK )
        {
            u4_divideDataPos += st_pduInfo.SduLength;
            
            SecOC_Rx_u4OnePeriodAuthTpCopySize += st_pduInfo.SduLength;
            
            if( u4_divideDataPos >= st_buff.u4Size )
            {
                SecOC_Rx_VerifyProcExit( u2Index );
                SecOC_Rx_NotifyTpRxIndication( u2Index, E_OK );
            }
            else
            {
                (void)SecOC_Buff_WriteDividePos( SECOC_BUFF_RX, u2Index, u4_divideDataPos ); /* no return check required */
            }
        }
        else
        {
            SecOC_Rx_VerifyProcExit( u2Index );
            SecOC_Rx_NotifyTpRxIndication( u2Index, E_NOT_OK );
        }
    }
    else
    {
        SecOC_Rx_VerifyProcExit( u2Index );
        SecOC_Rx_NotifyTpRxIndication( u2Index, E_NOT_OK );
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Rx_VerifyStartJudge                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index  :                                               */
/*               | udResult :                                               */
/*               | u4VerifyStartCount :                                     */
/* Return Value  | SecOC_VerificationResultType                             */
/*               |  SECOC_VERIFICATIONFAILURE                 :             */
/*               |  SECOC_FRESHNESSFAILURE                    :             */
/*               |  SECOC_AUTHENTICATIONBUILDFAILURE          :             */
/*               |  SECOC_VERIFICATIONFAILURE_OVERWRITTEN     :             */
/*               |  SECOC_AB_VERIFICATIONFAILURE_VERIFYSTART  :             */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(SecOC_VerificationResultType, SECOC_CODE) SecOC_Rx_VerifyStartJudge
(
    uint16 u2Index,
    SecOC_VerificationResultType udResult,
    uint32 u4VerifyStartCount
)
{
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
    SecOC_VerificationResultType               ud_verificationStatus = udResult;
    
    if( (u4VerifyStartCount <= SecOC_Ab_BusCollection[pt_rxConfig->Ab_BusIndex].Ab_VerifyStartCount)
        && (pt_rxConfig->Ab_MessageType == (uint8)SECOC_AB_MSGTYPE_SECURED)
        && ( (ud_verificationStatus == SECOC_VERIFICATIONFAILURE)
          || (ud_verificationStatus == SECOC_FRESHNESSFAILURE)
          || (ud_verificationStatus == SECOC_AUTHENTICATIONBUILDFAILURE)
          || (ud_verificationStatus == SECOC_VERIFICATIONFAILURE_OVERWRITTEN) ) )
    {
        ud_verificationStatus = SECOC_AB_VERIFICATIONFAILURE_VERIFYSTART;
    }
    
    return ud_verificationStatus;
}

#if( SECOC_OVERRIDE_STATUS_WITH_DATA_ID == STD_ON )
/****************************************************************************/
/* Function Name | SecOC_Rx_SearchDataId                                    */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u4DataId  :                                              */
/*               | ptIndex   :                                              */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_SearchDataId
(
    uint32 u4DataId,
    P2VAR(uint16, AUTOMATIC, SECOC_APPL_DATA) ptIndex
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    uint16          u2_loop;

    if( ptIndex != NULL_PTR )
    {
        for( u2_loop = 0U; u2_loop < SecOC_RxPduProcessingMax; u2_loop++ )
        {
            if( u4DataId == SecOC_RxPduProcessing[u2_loop].Ab_DataId )
            {
                *ptIndex = u2_loop;
                ud_stdRet = E_OK;
                break;
            }
        }
    }
    return ud_stdRet;
}
#else
/****************************************************************************/
/* Function Name | SecOC_Rx_SearchFvId                                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2FvId  :                                                */
/*               | ptIndex :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Rx_SearchFvId
(
    uint16 u2FvId,
    P2VAR(uint16, AUTOMATIC, SECOC_APPL_DATA) ptIndex
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    uint16          u2_loop;

    if( ptIndex != NULL_PTR )
    {
        for( u2_loop = 0U; u2_loop < SecOC_RxPduProcessingMax; u2_loop++ )
        {
            if( u2FvId == SecOC_RxPduProcessing[u2_loop].FreshnessValueId )
            {
                *ptIndex = u2_loop;
                ud_stdRet = E_OK;
                break;
            }
        }
    }
    return ud_stdRet;
}
#endif

#if ((SECOC_AB_EXTD_MSG_NOTIFY_JUDGE == STD_ON) || (SECOC_AB_FORCE_RECEIVE == STD_ON) || (SECOC_ENABLE_FORCED_PASS_OVERRIDE == STD_ON))
/****************************************************************************/
/* Function Name | SecOC_Rx_ForceReceiveJudge                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index  :                                               */
/* Return Value  | boolean                                                  */
/*               |  TRUE                                                    */
/*               |  FALSE                                                   */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(boolean, SECOC_CODE) SecOC_Rx_ForceReceiveJudge
(
    uint16 u2Index
)
{
#if (SECOC_AB_FORCE_RECEIVE == STD_ON)
    P2CONST(SecOC_RxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_rxConfig = &SecOC_RxPduProcessing[u2Index];
#endif
    boolean b_forceReceive = (boolean)FALSE;
    
#if (SECOC_AB_EXTD_MSG_NOTIFY_JUDGE == STD_ON)
    b_forceReceive = SecOC_Extd_MessageNotifyJudge( u2Index );
#endif
        
#if (SECOC_AB_FORCE_RECEIVE == STD_ON)
    if( pt_rxConfig->Ab_ForceReceive == (boolean)TRUE )
    {
        b_forceReceive = (boolean)TRUE;
    }
#endif

#if (SECOC_ENABLE_FORCED_PASS_OVERRIDE == STD_ON)
    if( ( SecOC_Rx_stVerifyOverrideCurrentInfo[u2Index].u2OverrideStatus == SECOC_RX_OVERRIDE_PASS_UNTIL_NOTICE )
     || ( SecOC_Rx_stVerifyOverrideCurrentInfo[u2Index].u2OverrideStatus == SECOC_RX_OVERRIDE_PASS_UNTIL_LIMIT ) )
    {
        b_forceReceive = (boolean)TRUE;
        if( SecOC_Rx_stVerifyOverrideCurrentInfo[u2Index].u2OverrideStatus == SECOC_RX_OVERRIDE_PASS_UNTIL_LIMIT )
        {
            SecOC_Rx_stVerifyOverrideCurrentInfo[u2Index].u1OverrideCounter++;
        }
    }
#endif
    return b_forceReceive;
}
#endif

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

#endif /* SECOC_RX_PDU_PROCESSING */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/*  v2-1-0     :2023/04/14                                                  */
/*  v2-1-1     :2023/05/24                                                  */
/*  v2-1-2     :2023/09/30                                                  */
/*  v2-1-3     :2023/11/20                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
