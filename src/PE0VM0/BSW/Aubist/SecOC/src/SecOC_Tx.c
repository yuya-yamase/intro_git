/* SecOC_Tx_c_v2-1-1                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC/Tx/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SchM_SecOC.h>
#include <SecOCStd_String.h>
#include <SecOCStd_Util.h>
#include <PduR_SecOC.h>
#include <Csm.h>
#include <SecOC.h>
#if (SECOC_AB_EXTD_TRANSMIT != STD_ON)
#include <SecOC_CD_FV.h>
#endif
#include "../usr/SecOC_Connector.h"
#include "../inc/SecOC_Buff.h"
#include "../inc/SecOC_Com.h"
#if (SECOC_AB_EXTENDED_ENABLE == STD_ON)
#include "../inc/SecOC_Extd_Internal.h"
#endif

#include "../inc/SecOC_Tx.h"

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Tx flag */
#define SECOC_TX_FLAG_FALSE         ((uint8)0x5AU)
#define SECOC_TX_FLAG_TRUE          ((uint8)0xA5U)

/* Buffer size */
#define SECOC_TX_PROTPADDING_SIZE   (16U)   /* 16byte */
#define SECOC_TX_FV_SIZE            (64U)   /* 64byte */
#define SECOC_TX_AUTHINFO_SIZE      (16U)   /* 16byte */
#define SECOC_TX_SECDATA_SIZE       (SECOC_TX_PROTPADDING_SIZE + SECOC_AB_TX_FV_BUFF_SIZE + SECOC_TX_AUTHINFO_SIZE)
#if (SECOC_AB_TX_FV_BUFF_SIZE != 0U)
#define SECOC_TX_FV_BUFF_SIZE       (SECOC_AB_TX_FV_BUFF_SIZE)
#else
#define SECOC_TX_FV_BUFF_SIZE       (4U)    /* Dummy */
#endif

/* Reserve size */
#define SECOC_TX_RESERVE_SIZE_12    (12U)
#define SECOC_TX_RESERVE_SIZE_16    (16U)
#define SECOC_TX_RESERVE_SIZE_28    (28U)
#define SECOC_TX_RESERVE_SIZE_48    (48U)
#define SECOC_TX_RESERVE_SIZE_60    (60U)
/* Bit define */
#define SECOC_TX_BIT_8              (8U)
#define SECOC_TX_U1_MSK             ((uint8)0xFFU)
#define SECOC_TX_CLEAR_SECDATA_SIZE ((uint32)0U)
#define SECOC_TX_INVALID_INDEX      ((uint16)0xFFFFU)
/* Padding */
#define SECOC_TX_PROT_PADDING       (0x00U)
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Tx control struct */
typedef struct {
    volatile uint8   u1Status;
    volatile uint8   u1BuffUseFlag;
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
    uint8            u1DefalutAuthFlag;
    uint8            u1Reserve;
#else
    uint16           u2Reserve;
#endif
} SecOC_Tx_CtrlType;

#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
typedef struct {
    Std_ReturnType    udCsmResult;
    uint8             u1NotifyCsmResultFlg;
    uint16            u2Reserve;
} SecOC_Tx_AsyncCtrlType;
typedef struct {
    uint8             u1CallBackEvt;
    Std_ReturnType    udCallBackCsmResult;
    uint16            u2Reserve;
} SecOC_Tx_AsyncCallBackType;
#endif

typedef struct {
    uint32  u4TxFVLen;
    uint8   u1TxFV[SECOC_TX_FV_BUFF_SIZE];
    uint16  u2GenerateRetryCnt ;
    uint16  u2CopyRetryCnt;
    uint16  u2TransmitRetryCnt;
    uint16  u2Reserve;
} SecOC_Tx_ProcessType;

typedef struct {
    uint32  u4InputDataSize;
} SecOC_Tx_CsmProcessType;

/* for HSM shared RAM. so cache align needed if cache is valid. (16/32/64Byte) */
typedef struct {
    uint32                  u4AuthInfoSize;
  #if (SECOC_AB_CACHE_ALIGN_TX_AUTHSIZE == 4U)
    /* No Reserve area */
  #elif (SECOC_AB_CACHE_ALIGN_TX_AUTHSIZE == 16U)
    uint8                   u1Reserve[SECOC_TX_RESERVE_SIZE_12];
  #elif (SECOC_AB_CACHE_ALIGN_TX_AUTHSIZE == 32U)
    uint8                   u1Reserve[SECOC_TX_RESERVE_SIZE_28];
  #elif (SECOC_AB_CACHE_ALIGN_TX_AUTHSIZE == 64U)
    uint8                   u1Reserve[SECOC_TX_RESERVE_SIZE_60];
  #else
    /* No Reserve area */
  #endif
} SecOC_Tx_CsmInOutAuthSizeType;

typedef struct {
    uint8                   u1AuthInfo[SECOC_TX_AUTHINFO_SIZE];
  #if (SECOC_AB_CACHE_ALIGN_TX_AUTHINFO == 16U)
    /* No Reserve area */
  #elif (SECOC_AB_CACHE_ALIGN_TX_AUTHINFO == 32U)
    uint8                   u1Reserve[SECOC_TX_RESERVE_SIZE_16];
  #elif (SECOC_AB_CACHE_ALIGN_TX_AUTHINFO == 64U)
    uint8                   u1Reserve[SECOC_TX_RESERVE_SIZE_48];
  #else
    /* No Reserve area */
  #endif
} SecOC_Tx_CsmOutputAuthType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

static FUNC(uint16, SECOC_CODE) SecOC_Tx_GenerateStart
(
    uint16 u2Index
);
static FUNC(uint16, SECOC_CODE) SecOC_Tx_GenerateMac
(
    uint16 u2Index,
    P2CONST(SecOC_Buff_DataType, AUTOMATIC, SECOC_APPL_DATA) ptBuff,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptFullFv,
    uint32 u4FullFvLen
);
static FUNC(uint16, SECOC_CODE) SecOC_Tx_GenerateFinish
(
    uint16 u2Index
);
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
static FUNC(void, SECOC_CODE) SecOC_Tx_GenerateNotify
(
    uint16 u2Index
);
#endif
static FUNC(void, SECOC_CODE) SecOC_Tx_StatusCheck
(
    uint16 u2Index
);
static FUNC(void, SECOC_CODE) SecOC_Tx_BuildSecData
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptMsg,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptMsgSize
);
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
static FUNC(void, SECOC_CODE) SecOC_Tx_BuildDefaultSecData
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptMsg,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptMsgSize
);
#endif
static FUNC(uint16, SECOC_CODE) SecOC_Tx_BuildRetryJudge
(
    uint16 u2Index,
    uint16 u2NgFactor
);
static FUNC(uint16, SECOC_CODE) SecOC_Tx_PduRRetryJudge
(
    uint16 u2Index,
    uint16 u2NgFactor
);
static FUNC(void, SECOC_CODE) SecOC_Tx_GenerateProcExit
(
    uint16 u2Index
);
static FUNC(void, SECOC_CODE) SecOC_Tx_UpperCopy
(
    uint16 u2Index
);
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_SearchFvIdIndex
(
    uint16 u2FvId,
    P2VAR(uint16, AUTOMATIC, SECOC_APPL_DATA) ptIndex
);
#endif

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_VAR_NO_INIT
#include <SecOC_MemMap.h>

static VAR(SecOC_Tx_CtrlType, SECOC_VAR_NO_INIT) SecOC_Tx_stCtrlInfo[SECOC_TX_PDU_PROCESSING_MAX];
static VAR(SecOC_Tx_ProcessType, SECOC_VAR_NO_INIT) SecOC_Tx_stProcInfo[SECOC_TX_PDU_PROCESSING_MAX];
static VAR(volatile uint16, SECOC_VAR_NO_INIT) SecOC_Tx_u2MainProcMsgCount;
static VAR(SecOC_Tx_CsmProcessType, SECOC_VAR_NO_INIT) SecOC_Tx_stCsmProcInfo[SECOC_TX_PDU_PROCESSING_MAX];

#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
static VAR(SecOC_Tx_AsyncCtrlType, SECOC_VAR_NO_INIT) SecOC_Tx_stAsyncCtrlInfo[SECOC_TX_PDU_PROCESSING_MAX];
static VAR(SecOC_Tx_AsyncCallBackType, SECOC_VAR_NO_INIT) SecOC_Tx_stAsyncCallBackInfo[SECOC_TX_PDU_PROCESSING_MAX];
#endif

#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
static VAR(uint16, SECOC_VAR_NO_INIT) SecOC_Tx_u2RamCheckCounter;
static VAR(uint16, SECOC_VAR_NO_INIT) SecOC_Tx_u2RamErrorCounter;
#endif
static VAR(uint32, SECOC_VAR_NO_INIT) SecOC_Tx_u4OnePeriodAuthTpCopySize;

#define SECOC_STOP_SEC_VAR_NO_INIT
#include <SecOC_MemMap.h>

/****************************************************************************/
/*****     CSM(HSM) access area. Message data. Input to Csm             *****/
/****************************************************************************/
#define SECOC_START_SEC_SHARED_TXMSG_VAR_NO_INIT
#include <SecOC_MemMap.h>

static VAR(uint8, SECOC_VAR_NO_INIT) SecOC_Tx_CsmInputData[SECOC_TX_INPUT_DATA_LENGTH_TOTAL];

#define SECOC_STOP_SEC_SHARED_TXMSG_VAR_NO_INIT
#include <SecOC_MemMap.h>

/****************************************************************************/
/***** CSM(HSM) access area. Authentication(MAC) data. Output from Csm  *****/
/****************************************************************************/
#define SECOC_START_SEC_SHARED_TXAUTH_VAR_NO_INIT
#include <SecOC_MemMap.h>

static VAR(SecOC_Tx_CsmOutputAuthType, SECOC_VAR_NO_INIT) SecOC_Tx_stCsmOutputAuthInfo[SECOC_TX_PDU_PROCESSING_MAX];

#define SECOC_STOP_SEC_SHARED_TXAUTH_VAR_NO_INIT
#include <SecOC_MemMap.h>


/****************************************************************************/
/***** CSM(HSM) access area. Authentication(MAC) data size. Output from Csm */
/****************************************************************************/
#define SECOC_START_SEC_SHARED_TXAUTHSIZE_VAR_NO_INIT
#include <SecOC_MemMap.h>

static VAR(SecOC_Tx_CsmInOutAuthSizeType, SECOC_VAR_NO_INIT) SecOC_Tx_stCsmInOutAuthInfoSize[SECOC_TX_PDU_PROCESSING_MAX];

#define SECOC_STOP_SEC_SHARED_TXAUTHSIZE_VAR_NO_INIT
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
/* Function Name | SecOC_Tx_Reset                                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Tx_Reset
(
    void
)
{
    uint16  u2_loop;
    
    SecOCStd_MemClr( &SecOC_Tx_stProcInfo[0], sizeof(SecOC_Tx_stProcInfo) );
    SecOCStd_MemClr( &SecOC_Tx_stCsmProcInfo[0], sizeof(SecOC_Tx_stCsmProcInfo) );
    SecOCStd_MemClr( &SecOC_Tx_stCsmOutputAuthInfo[0], sizeof(SecOC_Tx_stCsmOutputAuthInfo) );
    SecOCStd_MemClr( &SecOC_Tx_stCsmInOutAuthInfoSize[0], sizeof(SecOC_Tx_stCsmInOutAuthInfoSize) );
    SecOC_Tx_u2MainProcMsgCount = 0U;
    SecOCStd_MemClr( &SecOC_Tx_CsmInputData[0], sizeof(SecOC_Tx_CsmInputData) );
    
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
    SecOCStd_MemClr( &SecOC_Tx_stAsyncCtrlInfo[0], sizeof(SecOC_Tx_stAsyncCtrlInfo) );
#endif

#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
    SecOC_Tx_u2RamCheckCounter = 0U;
    SecOC_Tx_u2RamErrorCounter = 0U;
#endif
    SecOC_Tx_u4OnePeriodAuthTpCopySize = 0U;
    
    for( u2_loop = 0U; u2_loop < SecOC_TxPduProcessingMax; u2_loop++ )
    {
        SecOC_Tx_stCtrlInfo[u2_loop].u1Status = SECOC_TX_ST_IDLE;
        SecOC_Tx_stCtrlInfo[u2_loop].u1BuffUseFlag = SECOC_TX_FLAG_FALSE;
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
        SecOC_Tx_stCtrlInfo[u2_loop].u1DefalutAuthFlag = SECOC_TX_FLAG_FALSE;
#endif
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
        SecOC_Tx_stAsyncCallBackInfo[u2_loop].u1CallBackEvt = SECOC_TX_FLAG_FALSE;
        SecOC_Tx_stAsyncCallBackInfo[u2_loop].udCallBackCsmResult = E_NOT_OK;
#endif
    }
    return ;
}



/****************************************************************************/
/* Function Name | SecOC_Tx_GetMode                                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | SecOC_ModeType                                           */
/*               |  SECOC_M_IDLE     : Idle                                 */
/*               |  SECOC_M_RUN      : Run                                  */
/*               |  SECOC_M_ABNORMAL : Abnormal                             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(SecOC_ModeType, SECOC_CODE) SecOC_Tx_GetMode
(
    void
)
{
    SecOC_ModeType  ud_retMode = SECOC_M_IDLE;
    uint16          u2_loop;
    uint8           u1_status;
    uint8           u1_abnormalFlag = SECOC_TX_FLAG_FALSE;
    
    for( u2_loop = 0U; u2_loop < SecOC_TxPduProcessingMax; u2_loop++ )
    {
        u1_status = SecOC_Tx_stCtrlInfo[u2_loop].u1Status;
        
        if( u1_status == SECOC_TX_ST_IDLE )
        {
            /* Mode IDLE */
        }
        else if( (u1_status == SECOC_TX_ST_UPPER_COPY)
          || (u1_status == SECOC_TX_ST_ACCEPT)
          || (u1_status == SECOC_TX_ST_GENERATE)
          || (u1_status == SECOC_TX_ST_WAIT_CALLBACK)
          || (u1_status == SECOC_TX_ST_CALLBACK_RECEIVED)
          || (u1_status == SECOC_TX_ST_WAIT_NOTIFY)
          || (u1_status == SECOC_TX_ST_RETRY)
          || (u1_status == SECOC_TX_ST_TRANSMIT)
          || (u1_status == SECOC_TX_ST_END)
          || (u1_status == SECOC_TX_ST_WAIT_CANCEL_CALLBACK)
          || (u1_status == SECOC_TX_ST_GENERATE_DEFAULT) )
        {
            ud_retMode = SECOC_M_RUN;
        }
        else
        {
            u1_abnormalFlag = SECOC_TX_FLAG_TRUE;
        }
    }
    
    if( (u1_abnormalFlag == SECOC_TX_FLAG_TRUE)
      && (ud_retMode == SECOC_M_IDLE) )
    {
        ud_retMode = SECOC_M_ABNORMAL;
    }
    
    return ud_retMode;
}

/****************************************************************************/
/* Function Name | SecOC_Tx_IfTransmit                                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | ptMsg   :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK             : Success                              */
/*               |  E_NOT_OK         : Failure                              */
/*               |  PDUR_BUSY        : Busy                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_IfTransmit
(
    uint16 u2Index,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptMsg
)
{
    SecOC_Buff_DataType st_buff;
    Std_ReturnType      ud_stdRet = E_OK;
    uint8               u1_overWriteTransmitFlag = SECOC_TX_FLAG_FALSE;
    uint16              u2_MainProcMsgCount;
    uint8               u1_status;
    uint8               u1_buffUseFlag;
    
#if (SECOC_AB_EXTD_TRANSMIT == STD_ON)
    ud_stdRet = SecOC_Extd_Transmit( u2Index );
#else
  #if (SECOC_AB_TRANSMIT_CONDITION_CHECK == STD_ON)
    if( SecOC_TxPduProcessing[u2Index].Ab_MessageType == (uint8)SECOC_AB_MSGTYPE_SECURED )
    {
        ud_stdRet = SecOC_CD_FV_SyncJudge( SecOC_Ab_BusCollection[SecOC_TxPduProcessing[u2Index].Ab_BusIndex].Ab_BusID );
    }
  #endif
#endif
    
#if ((SECOC_AB_EXTD_TRANSMIT == STD_ON) || (SECOC_AB_TRANSMIT_CONDITION_CHECK == STD_ON))
    if( ud_stdRet == (Std_ReturnType)E_OK )
    {
#endif
        SchM_Enter_SecOC_Tx();

        u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
        u1_buffUseFlag = SecOC_Tx_stCtrlInfo[u2Index].u1BuffUseFlag;
        
        /* Status check */
        if( u1_status == SECOC_TX_ST_IDLE )
        {
            if( u1_buffUseFlag == SECOC_TX_FLAG_FALSE )
            {
                u1_status = SECOC_TX_ST_ACCEPT;
                u1_buffUseFlag = SECOC_TX_FLAG_TRUE;
                u2_MainProcMsgCount = SecOC_Tx_u2MainProcMsgCount;
                u2_MainProcMsgCount++;
                SecOC_Tx_u2MainProcMsgCount = u2_MainProcMsgCount;
            }
            else
            {
                ud_stdRet = PDUR_BUSY;
            }
        }
        else if( ( u1_status == SECOC_TX_ST_TRANSMIT )
         && ( SecOC_TxPduProcessing[u2Index].Ab_TxSecuredPduType == (uint8)SECOC_TPPDU ) )
        {
            if( u1_buffUseFlag == SECOC_TX_FLAG_FALSE )
            {
                u1_status = SECOC_TX_ST_ACCEPT;
                u1_buffUseFlag = SECOC_TX_FLAG_TRUE;
                u1_overWriteTransmitFlag = SECOC_TX_FLAG_TRUE;
            }
            else
            {
                ud_stdRet = PDUR_BUSY;
            }
        }
        else
        {
            ud_stdRet = PDUR_BUSY;
        }
        
        SecOC_Tx_stCtrlInfo[u2Index].u1Status = u1_status;
        SecOC_Tx_stCtrlInfo[u2Index].u1BuffUseFlag = u1_buffUseFlag;
        
        SchM_Exit_SecOC_Tx();
#if ((SECOC_AB_EXTD_TRANSMIT == STD_ON) || (SECOC_AB_TRANSMIT_CONDITION_CHECK == STD_ON))
    }
#endif
    
    if( ud_stdRet == (Std_ReturnType)E_OK )
    {
        if( u1_overWriteTransmitFlag == SECOC_TX_FLAG_TRUE )
        {
            (void)SecOC_Buff_WriteDividePos( SECOC_BUFF_TX, u2Index, (uint32)0U ); /* no return check required */
            (void)SecOC_Buff_ClearSelect( SECOC_BUFF_TX, u2Index ); /* no return check required */
        }
        
        st_buff.ptData = ptMsg->SduDataPtr;
        st_buff.u4Size = (uint32)(ptMsg->SduLength - SecOC_TxPduProcessing[u2Index].Ab_ProtDataPaddingSize);
        
        ud_stdRet = SecOC_Buff_SetOrder( SECOC_BUFF_TX, u2Index, &st_buff );
        
        if( ud_stdRet != (Std_ReturnType)E_OK )
        {
            SchM_Enter_SecOC_Tx();
            
            SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_IDLE;
            u2_MainProcMsgCount = SecOC_Tx_u2MainProcMsgCount;
            u2_MainProcMsgCount--;
            SecOC_Tx_u2MainProcMsgCount = u2_MainProcMsgCount;
            
            SchM_Exit_SecOC_Tx();
        }
        
        SecOC_Tx_stCtrlInfo[u2Index].u1BuffUseFlag = SECOC_TX_FLAG_FALSE;
    }
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Tx_TpTransmit                                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | ptMsg   :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK             : Success                              */
/*               |  E_NOT_OK         : Failure                              */
/*               |  PDUR_BUSY        : Busy                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_TpTransmit
(
    uint16 u2Index,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptMsg
)
{
    Std_ReturnType      ud_stdRet = E_OK;
    uint32              u4_TotalAuthMsgSize;
    uint8               u1_overWriteTransmitFlag = SECOC_TX_FLAG_FALSE;
    uint8               u1_status;
    uint8               u1_buffUseFlag;
    
#if (SECOC_AB_EXTD_TRANSMIT == STD_ON)
    ud_stdRet = SecOC_Extd_Transmit( u2Index );
#else
  #if (SECOC_AB_TRANSMIT_CONDITION_CHECK == STD_ON)
    if( SecOC_TxPduProcessing[u2Index].Ab_MessageType == (uint8)SECOC_AB_MSGTYPE_SECURED )
    {
        ud_stdRet = SecOC_CD_FV_SyncJudge( SecOC_Ab_BusCollection[SecOC_TxPduProcessing[u2Index].Ab_BusIndex].Ab_BusID );
    }
  #endif
#endif
    
#if ((SECOC_AB_EXTD_TRANSMIT == STD_ON) || (SECOC_AB_TRANSMIT_CONDITION_CHECK == STD_ON))
    if( ud_stdRet == (Std_ReturnType)E_OK )
    {
#endif
        SchM_Enter_SecOC_Tx();

        u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
        u1_buffUseFlag = SecOC_Tx_stCtrlInfo[u2Index].u1BuffUseFlag;
        
        /* Status check */
        if( u1_status == SECOC_TX_ST_IDLE )
        {
            if( u1_buffUseFlag == SECOC_TX_FLAG_FALSE )
            {
                u1_status = SECOC_TX_ST_UPPER_COPY;
                u1_buffUseFlag = SECOC_TX_FLAG_TRUE;
            }
            else
            {
                ud_stdRet = PDUR_BUSY;
            }
        }
        else if( ( u1_status == SECOC_TX_ST_TRANSMIT )
         && ( SecOC_TxPduProcessing[u2Index].Ab_TxSecuredPduType == (uint8)SECOC_TPPDU ) )
        {
            if( u1_buffUseFlag == SECOC_TX_FLAG_FALSE )
            {
                u1_status = SECOC_TX_ST_UPPER_COPY;
                u1_buffUseFlag = SECOC_TX_FLAG_TRUE;
                u1_overWriteTransmitFlag = SECOC_TX_FLAG_TRUE;
            }
            else
            {
                ud_stdRet = PDUR_BUSY;
            }
        }
        else
        {
            ud_stdRet = PDUR_BUSY;
        }
        
        SecOC_Tx_stCtrlInfo[u2Index].u1Status = u1_status;
        SecOC_Tx_stCtrlInfo[u2Index].u1BuffUseFlag = u1_buffUseFlag;
        
        SchM_Exit_SecOC_Tx();
#if ((SECOC_AB_EXTD_TRANSMIT == STD_ON) || (SECOC_AB_TRANSMIT_CONDITION_CHECK == STD_ON))
    }
#endif
    
    if( ud_stdRet == (Std_ReturnType)E_OK )
    {
        if( u1_overWriteTransmitFlag == SECOC_TX_FLAG_TRUE )
        {
            (void)SecOC_Buff_WriteDividePos( SECOC_BUFF_TX, u2Index, (uint32)0U ); /* no return check required */
            (void)SecOC_Buff_ClearSelect( SECOC_BUFF_TX, u2Index ); /* no return check required */
        }
        
        u4_TotalAuthMsgSize = (uint32)(ptMsg->SduLength - SecOC_TxPduProcessing[u2Index].Ab_ProtDataPaddingSize);
        (void)SecOC_Buff_WriteTotalSize( SECOC_BUFF_TX, u2Index, u4_TotalAuthMsgSize ); /* no return check required */
        (void)SecOC_Buff_SetNextIndex( SECOC_BUFF_TX, u2Index ); /* no return check required */
        SecOC_Tx_stProcInfo[u2Index].u2CopyRetryCnt = 0U;
        
        SecOC_Tx_stCtrlInfo[u2Index].u1BuffUseFlag = SECOC_TX_FLAG_FALSE;
    }
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Tx_Cancel                                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_Cancel
(
    uint16 u2Index
)
{
    Std_ReturnType  ud_stdRet = E_OK;
    uint8           u1_cancelTransmitFlag = SECOC_TX_FLAG_FALSE;
    uint8           u1_status;
    uint16          u2_MainProcMsgCount;
    uint8           u1_buffUseFlag;
    
    SchM_Enter_SecOC_Tx();
    
    /* Busy Check */
    u1_buffUseFlag = SecOC_Tx_stCtrlInfo[u2Index].u1BuffUseFlag;
    if( u1_buffUseFlag == SECOC_TX_FLAG_FALSE )
    {
        /* Status check */
        u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
        if( u1_status == SECOC_TX_ST_TRANSMIT )
        {
            u1_cancelTransmitFlag = SECOC_TX_FLAG_TRUE;
            u1_buffUseFlag = SECOC_TX_FLAG_TRUE;
            SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_IDLE;
        }
        else if( u1_status == SECOC_TX_ST_GENERATE )
        {
            SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_END;
        }
        else if( u1_status == SECOC_TX_ST_IDLE )
        {
            u1_cancelTransmitFlag = SECOC_TX_FLAG_TRUE;
        }
        else if( u1_status == SECOC_TX_ST_END )
        {
            /* No Processing */
        }
        else
        {
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
            u1_buffUseFlag = SECOC_TX_FLAG_TRUE;
            SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_IDLE;
#else
            if( ( u1_status == SECOC_TX_ST_RETRY )
              || (u1_status == SECOC_TX_ST_CALLBACK_RECEIVED)
              || (u1_status == SECOC_TX_ST_WAIT_NOTIFY)
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
              || (u1_status == SECOC_TX_ST_GENERATE_DEFAULT)
#endif
               )
            {
                SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_END;
            }
            else if ( u1_status == SECOC_TX_ST_WAIT_CALLBACK )
            {
                SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_WAIT_CANCEL_CALLBACK;
            }
            else if ( u1_status == SECOC_TX_ST_WAIT_CANCEL_CALLBACK )
            {
                /* No Processing */
            }
            else
            {
                /* in case of bellow status */
                /*  SECOC_TX_ST_ACCEPT      */
                /*  SECOC_TX_ST_UPPER_COPY  */
                u1_buffUseFlag = SECOC_TX_FLAG_TRUE;
                SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_IDLE;
            }
#endif
            if( (u1_status == SECOC_TX_ST_ACCEPT)
              || (u1_status == SECOC_TX_ST_RETRY) )
            {
                u2_MainProcMsgCount = SecOC_Tx_u2MainProcMsgCount;
                u2_MainProcMsgCount--;
                SecOC_Tx_u2MainProcMsgCount = u2_MainProcMsgCount;
            }
        }
        
        if( u1_buffUseFlag != SECOC_TX_FLAG_FALSE )
        {
            (void)SecOC_Buff_WriteDividePos( SECOC_BUFF_TX, u2Index, (uint32)0U ); /* no return check required */
            (void)SecOC_Buff_ClearSelect( SECOC_BUFF_TX, u2Index ); /* no return check required */
        }
    }
    else
    {
        ud_stdRet = E_NOT_OK;
    }
    
    SecOC_Tx_stCtrlInfo[u2Index].u1BuffUseFlag = u1_buffUseFlag;
    
    SchM_Exit_SecOC_Tx();
    
    if( ud_stdRet == (Std_ReturnType)E_OK )
    {
        if( u1_cancelTransmitFlag == SECOC_TX_FLAG_TRUE )
        {
            (void)SecOC_Connector_PduR_SecOCCancelTransmit( SecOC_TxPduProcessing[u2Index].Ab_TxSecuredLayerPduRefId );  /* no return check required */
        }
        
        u1_buffUseFlag = SecOC_Tx_stCtrlInfo[u2Index].u1BuffUseFlag;
        if( u1_buffUseFlag != SECOC_TX_FLAG_FALSE )
        {
            SecOC_Tx_stCtrlInfo[u2Index].u1BuffUseFlag = SECOC_TX_FLAG_FALSE;
        }
    }
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Tx_Finish                                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | udResult:                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Tx_Finish
(
    uint16          u2Index,
    Std_ReturnType  udResult
)
{
    uint8           u1_status;
    
    u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
    if( u1_status == SECOC_TX_ST_IDLE )
    {
        if( SecOC_TxPduProcessing[u2Index].TxAuthPduType == (uint8)SECOC_IFPDU )
        {
            SecOC_Connector_PduR_SecOCIfTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, udResult );
        }
        else
        {
            SecOC_Connector_PduR_SecOCTpTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, udResult );
        }
    }
    
    return ;
}

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_Tx_GetMainProcMsgNum                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | uint16 : TxMessageNum                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint16, SECOC_CODE) SecOC_Tx_GetMainProcMsgNum
(
    void
)
{
    uint16  u2_msgNum;
    
    u2_msgNum = SecOC_Tx_u2MainProcMsgCount;
    
    if( u2_msgNum >= SecOC_Ab_TxProcessingCount )
    {
        u2_msgNum = SecOC_Ab_TxProcessingCount;
    }
    
    return u2_msgNum;
}
#endif

/****************************************************************************/
/* Function Name | SecOC_Tx_MainProcess                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | uint16                                                   */
/*               |  SECOC_TX_PROC_OK         :                              */
/*               |  SECOC_TX_PROC_NG_FV      :                              */
/*               |  SECOC_TX_PROC_NG_CSM     :                              */
/*               |  SECOC_TX_PROC_NG_PDUR    :                              */
/*               |  SECOC_TX_PROC_NG_RETRY   :                              */
/*               |  SECOC_TX_PROC_NG_OTHER   :                              */
/*               |  SECOC_TX_PROC_RETRY_CSM  :                              */
/*               |  SECOC_TX_PROC_RETRY_PDUR :                              */
/*               |  SECOC_TX_PROC_NONE       :                              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint16, SECOC_CODE) SecOC_Tx_MainProcess
(
    uint16 u2Index
)
{
    uint16          u2_ret = SECOC_TX_PROC_NONE;
    uint8           u1_status;
    
    u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
    
    if( (u1_status == SECOC_TX_ST_ACCEPT)
     || (u1_status == SECOC_TX_ST_RETRY) )
    {
        /* MAC Generate */
        u2_ret = SecOC_Tx_GenerateStart( u2Index );
        
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
        if( u2_ret == SECOC_TX_PROC_OK )
        {
            /* Make Secured Message And Send Request */
            u2_ret = SecOC_Tx_GenerateFinish( u2Index );
        }
#endif
    }
    
    return u2_ret;
}

#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Tx_GenerateCallback                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | udRet   :                                                */
/* Return Value  | None                                                     */
/* Notes         | Async Only                                               */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Tx_GenerateCallback
(
    uint16 u2Index,
    Std_ReturnType udRet
)
{
    /* Check Processing Message */
    if( u2Index < SecOC_TxPduProcessingMax )
    {
        SchM_Enter_SecOC_Tx();
        SecOC_Tx_stAsyncCallBackInfo[u2Index].u1CallBackEvt = SECOC_TX_FLAG_TRUE;
        SecOC_Tx_stAsyncCallBackInfo[u2Index].udCallBackCsmResult = udRet;
        SchM_Exit_SecOC_Tx();
    }
    
    return ;
}


/****************************************************************************/
/* Function Name | SecOC_Tx_ReapCallbackEvt                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | Async Only                                               */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Tx_ReapCallbackEvt
(
    void
)
{
    uint8           u1_status;
    uint8           u1_callbackEvt;
    uint16          u2_loop;

    SchM_Enter_SecOC_Tx();
    /* Reap callback event for all tx message. */
    for(u2_loop=0; u2_loop<SecOC_TxPduProcessingMax; u2_loop++)
    {
        u1_status = SecOC_Tx_stCtrlInfo[u2_loop].u1Status;
        u1_callbackEvt = SecOC_Tx_stAsyncCallBackInfo[u2_loop].u1CallBackEvt;

        if(u1_callbackEvt == SECOC_TX_FLAG_TRUE)
        {
            if( u1_status == SECOC_TX_ST_WAIT_CALLBACK )
            {
                SecOC_Tx_stCtrlInfo[u2_loop].u1Status = SECOC_TX_ST_CALLBACK_RECEIVED;
                SecOC_Tx_stAsyncCtrlInfo[u2_loop].u1NotifyCsmResultFlg = SECOC_TX_FLAG_TRUE;
                SecOC_Tx_stAsyncCtrlInfo[u2_loop].udCsmResult = SecOC_Tx_stAsyncCallBackInfo[u2_loop].udCallBackCsmResult;
                SecOC_Tx_stAsyncCallBackInfo[u2_loop].u1CallBackEvt = SECOC_TX_FLAG_FALSE;
                SecOC_Tx_stAsyncCallBackInfo[u2_loop].udCallBackCsmResult = E_NOT_OK;
            }
            else if( u1_status == SECOC_TX_ST_WAIT_CANCEL_CALLBACK )
            {
                SecOC_Tx_stCtrlInfo[u2_loop].u1Status = SECOC_TX_ST_END;
                SecOC_Tx_stAsyncCtrlInfo[u2_loop].u1NotifyCsmResultFlg = SECOC_TX_FLAG_TRUE;
                SecOC_Tx_stAsyncCtrlInfo[u2_loop].udCsmResult = SecOC_Tx_stAsyncCallBackInfo[u2_loop].udCallBackCsmResult;
                SecOC_Tx_stAsyncCallBackInfo[u2_loop].u1CallBackEvt = SECOC_TX_FLAG_FALSE;
                SecOC_Tx_stAsyncCallBackInfo[u2_loop].udCallBackCsmResult = E_NOT_OK;
            }
            else
            {
                /* No Processing */
            }
        }
    }
    SchM_Exit_SecOC_Tx();
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Tx_AsyncNotify                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | None                                                     */
/* Notes         | Async Only                                               */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Tx_AsyncNotify
(
    uint16 u2Index
)
{
    uint8           u1_status;
    Std_ReturnType  ud_stdRet;
    uint16          u2_retJudge;
    uint8           u1_generateFinishFlag = SECOC_TX_FLAG_FALSE;
#if (SECOC_AB_TXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
    P2CONST(SecOC_TxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_txConfig = &SecOC_TxPduProcessing[u2Index];
    uint16  u2_loop;
#endif
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
    uint8   u1_defalutAuthFlag;
#endif
    
    u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
    if( u1_status == SECOC_TX_ST_CALLBACK_RECEIVED )
    {
        ud_stdRet = SecOC_Tx_stAsyncCtrlInfo[u2Index].udCsmResult;
        
        if( ud_stdRet == (Std_ReturnType)E_OK )
        {
            u1_generateFinishFlag = SECOC_TX_FLAG_TRUE;
        }
        else if( ud_stdRet == (Std_ReturnType)CRYPTO_E_BUSY )
        {
            u2_retJudge = SecOC_Tx_BuildRetryJudge( u2Index, SECOC_TX_PROC_RETRY_CSM );
            
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
            if( (u2_retJudge != SECOC_TX_PROC_RETRY_CSM)
             && (u2_retJudge != SECOC_TX_PROC_OK) )
#else
            if( u2_retJudge != SECOC_TX_PROC_RETRY_CSM )
#endif
            {
#if (SECOC_AB_TXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
                if( u2_retJudge == SECOC_TX_PROC_NG_RETRY )
                {
                    for( u2_loop = 0U; u2_loop < SecOC_Ab_TxMsgBusyDestCoMax; u2_loop++ )
                    {
                        if( pt_txConfig->Ab_TxMsgBusyDestructionCallout[u2_loop] != NULL_PTR )
                        {
                            pt_txConfig->Ab_TxMsgBusyDestructionCallout[u2_loop]( pt_txConfig->FreshnessValueId, pt_txConfig->Ab_DataId );
                        }
                    }
                }
#endif

                if( SecOC_TxPduProcessing[u2Index].TxAuthPduType == (uint8)SECOC_IFPDU )
                {
                    SecOC_Connector_PduR_SecOCIfTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, E_NOT_OK );
                }
                else
                {
                    SecOC_Connector_PduR_SecOCTpTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, E_NOT_OK );
                }
            }
            
        }
        else
        {
            /* CSM Error */
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
            u1_defalutAuthFlag = SecOC_Tx_stCtrlInfo[u2Index].u1DefalutAuthFlag;
            if( u1_defalutAuthFlag == SECOC_TX_FLAG_TRUE )
            {
                SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_GENERATE_DEFAULT;
            }
            else
            {
#endif
                SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_END;
                
                if( SecOC_TxPduProcessing[u2Index].TxAuthPduType == (uint8)SECOC_IFPDU )
                {
                    SecOC_Connector_PduR_SecOCIfTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, E_NOT_OK );
                }
                else
                {
                    SecOC_Connector_PduR_SecOCTpTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, E_NOT_OK );
                }
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
            }
#endif
        }
        /* Get Tx Status */
        u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
    }
    
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
    if( (u1_generateFinishFlag == SECOC_TX_FLAG_TRUE)
     || (u1_status == SECOC_TX_ST_GENERATE_DEFAULT) )
#else
    if( u1_generateFinishFlag == SECOC_TX_FLAG_TRUE )
#endif
    {
        /* Make Secured Message And Send Request */
        (void)SecOC_Tx_GenerateFinish( u2Index ); /* no return check required */
        
        /* Get Tx Status */
        u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
    }
    
    if( (u1_status == SECOC_TX_ST_WAIT_NOTIFY)
      || (u1_status == SECOC_TX_ST_RETRY)
      || (u1_status == SECOC_TX_ST_END)
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
      || (u1_status == SECOC_TX_ST_GENERATE_DEFAULT)
#endif
      )
    {
        /* Tx Notify */
        SecOC_Tx_GenerateNotify( u2Index );
    }
    
    return ;
}
#endif

#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Tx_GetErrorStatus                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | SecOC_ErrorStatusType                                    */
/*               |  SECOC_E_NONE            : No Error                      */
/*               |  SECOC_E_RAM_CHECK_FAIL  : RAM Error                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(SecOC_ErrorStatusType, SECOC_CODE) SecOC_Tx_GetErrorStatus
(
    void
)
{
    SecOC_ErrorStatusType   ud_errorStatus = SECOC_E_RAM_CHECK_FAIL;
    uint16                  u2_index;
    uint16                  u2_msgNum;
    uint16                  u2_loop;
    uint8                   u1_status;
    uint8                   u1_buffUseFlag;
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
    uint8                   u1_callbackEvt;
#endif

    u2_index = SecOC_Tx_u2RamCheckCounter;
    
    if( u2_index >= SecOC_TxPduProcessingMax )
    {
        u2_index = 0U;
        u2_msgNum = 0U;
        
        SchM_Enter_SecOC_Tx();
        
        /* Refresh */
        for( u2_loop = 0U; u2_loop < SecOC_TxPduProcessingMax; u2_loop++ )
        {
            u1_status = SecOC_Tx_stCtrlInfo[u2_loop].u1Status;
            
            if( (u1_status == SECOC_TX_ST_ACCEPT)
              || (u1_status == SECOC_TX_ST_RETRY) )
            {
                u2_msgNum++;
            }
        }
        SecOC_Tx_u2MainProcMsgCount = u2_msgNum;
        
        SchM_Exit_SecOC_Tx();
    }
    
    /* RAM check */
    u1_status = SecOC_Tx_stCtrlInfo[u2_index].u1Status;
    u1_buffUseFlag = SecOC_Tx_stCtrlInfo[u2_index].u1BuffUseFlag;
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
    u1_callbackEvt = SecOC_Tx_stAsyncCallBackInfo[u2_index].u1CallBackEvt;
#endif

    if( (u1_status == SECOC_TX_ST_IDLE)
      ||  (u1_status == SECOC_TX_ST_UPPER_COPY)
      ||  (u1_status == SECOC_TX_ST_ACCEPT)
      ||  (u1_status == SECOC_TX_ST_GENERATE)
      ||  (u1_status == SECOC_TX_ST_WAIT_CALLBACK)
      ||  (u1_status == SECOC_TX_ST_CALLBACK_RECEIVED)
      ||  (u1_status == SECOC_TX_ST_WAIT_NOTIFY)
      ||  (u1_status == SECOC_TX_ST_RETRY)
      ||  (u1_status == SECOC_TX_ST_TRANSMIT)
      ||  (u1_status == SECOC_TX_ST_END)
      ||  (u1_status == SECOC_TX_ST_WAIT_CANCEL_CALLBACK)
      ||  (u1_status == SECOC_TX_ST_GENERATE_DEFAULT) )
    {
        if( (u1_buffUseFlag == SECOC_TX_FLAG_FALSE)
          || (u1_buffUseFlag == SECOC_TX_FLAG_TRUE) )
        {
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
            ud_errorStatus = SECOC_E_NONE;
#else
            if( (u1_callbackEvt == SECOC_TX_FLAG_FALSE)
              || (u1_callbackEvt == SECOC_TX_FLAG_TRUE) )
            {
                ud_errorStatus = SECOC_E_NONE;
            }
#endif
        }
    }
    
    if( ud_errorStatus != SECOC_E_NONE )
    {
        SecOC_Tx_u2RamErrorCounter = SecOC_TxPduProcessingMax;
    }
    
    if( SecOC_Tx_u2RamErrorCounter > (uint16)0U )
    {
        ud_errorStatus = SECOC_E_RAM_CHECK_FAIL;
        SecOC_Tx_u2RamErrorCounter--;
    }
    
    u2_index++;
    SecOC_Tx_u2RamCheckCounter = u2_index;
    
    return ud_errorStatus;
}
#endif

/****************************************************************************/
/* Function Name | SecOC_Tx_CopyDivide                                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index              :                                   */
/*               | ptMsg                :                                   */
/*               | ptRemainMsgSize      :                                   */
/* Return Value  | BufReq_ReturnType                                        */
/*               |  BUFREQ_OK           : Success                           */
/*               |  BUFREQ_E_NOT_OK     : Failure                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_Tx_CopyDivide
(
    uint16 u2Index,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) ptMsg,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) ptRemainMsgSize
)
{
    SecOC_Buff_DataType     st_useBuff;
    BufReq_ReturnType       ud_bufRet = BUFREQ_E_NOT_OK;
    Std_ReturnType          ud_stdGetSelectRet;
    Std_ReturnType          ud_stdReadDividePosRet;
    Std_ReturnType          ud_stdWriteDivideRet;
    uint32                  u4_divideDataPos;
    uint32                  u4_remainMsgSize;
    uint8                   u1_status;
    uint8                   u1_bufRetFlag = SECOC_TX_FLAG_FALSE;
    
    u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
    
    if( u1_status == SECOC_TX_ST_TRANSMIT )
    {
        /* Get Tx Data */
        ud_stdGetSelectRet = SecOC_Buff_GetSelect( SECOC_BUFF_TX, u2Index, &st_useBuff );
        
        ud_stdReadDividePosRet = SecOC_Buff_ReadDividePos( SECOC_BUFF_TX, u2Index, &u4_divideDataPos );
        
        if( ( ud_stdGetSelectRet == (Std_ReturnType)E_OK )
         && ( ud_stdReadDividePosRet == (Std_ReturnType)E_OK )
         && ( st_useBuff.u4Size >= u4_divideDataPos ) )
        {
            u4_remainMsgSize = st_useBuff.u4Size - u4_divideDataPos;
            
            if( ptMsg->SduLength == (uint32)0U )
            {
                u1_bufRetFlag = SECOC_TX_FLAG_TRUE;
            }
            else if( ( ptMsg->SduLength <= SecOC_TxPduProcessing[u2Index].SameBufferPduRef )
               &&    ( ptMsg->SduLength <= u4_remainMsgSize ) )
            {
                ud_stdWriteDivideRet = SecOC_Buff_WriteDividePos( SECOC_BUFF_TX, u2Index, u4_divideDataPos + ptMsg->SduLength );
                
                if( ud_stdWriteDivideRet == (Std_ReturnType)E_OK )
                {
                    (void)SecOCStd_MemCpy( ptMsg->SduDataPtr, &st_useBuff.ptData[u4_divideDataPos], (uint32)ptMsg->SduLength ); /* no return check required */
                    
                    u4_remainMsgSize = u4_remainMsgSize - ptMsg->SduLength;
                    u1_bufRetFlag = SECOC_TX_FLAG_TRUE;
                }
            }
            else
            {
                /* No Processing */
            }
            
            if( u1_bufRetFlag == SECOC_TX_FLAG_TRUE )
            {
                ud_bufRet = BUFREQ_OK;
                *ptRemainMsgSize = u4_remainMsgSize;
                
                if( u4_remainMsgSize == (uint32)0U )
                {
                    SecOC_Tx_GenerateProcExit( u2Index );
                }
            }
        }
    }
    
    return ud_bufRet;
}

/****************************************************************************/
/* Function Name | SecOC_Tx_DivideFinish                                    */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index   :                                              */
/*               | udResult  :                                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Tx_DivideFinish
(
    uint16          u2Index,
    Std_ReturnType  udResult
)
{
    uint8           u1_txNotifyFlag = SECOC_TX_FLAG_FALSE;
    uint8           u1_status;
    uint8           u1_buffUseFlag;
    
    u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
    if( u1_status == SECOC_TX_ST_IDLE )
    {
        if( SecOC_TxPduProcessing[u2Index].TxAuthPduType == (uint8)SECOC_IFPDU )
        {
            SecOC_Connector_PduR_SecOCIfTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, udResult );
        }
        else
        {
            SecOC_Connector_PduR_SecOCTpTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, udResult );
        }
    }
    else
    {
        SchM_Enter_SecOC_Tx();
        
        u1_buffUseFlag = SecOC_Tx_stCtrlInfo[u2Index].u1BuffUseFlag;
        if( u1_buffUseFlag == SECOC_TX_FLAG_FALSE )
        {
            u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
            if( u1_status == SECOC_TX_ST_TRANSMIT )
            {
                u1_txNotifyFlag = SECOC_TX_FLAG_TRUE;
                SecOC_Tx_stCtrlInfo[u2Index].u1BuffUseFlag = SECOC_TX_FLAG_TRUE;
                SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_IDLE;
                (void)SecOC_Buff_ClearSelect( SECOC_BUFF_TX, u2Index ); /* no return check required */
                (void)SecOC_Buff_WriteDividePos( SECOC_BUFF_TX, u2Index, (uint32)0U ); /* no return check required */
            }
        }
        
        SchM_Exit_SecOC_Tx();
        
        if( u1_txNotifyFlag != SECOC_TX_FLAG_FALSE )
        {
            SecOC_Tx_stCtrlInfo[u2Index].u1BuffUseFlag = SECOC_TX_FLAG_FALSE;
            
            if( SecOC_TxPduProcessing[u2Index].TxAuthPduType == (uint8)SECOC_IFPDU )
            {
                SecOC_Connector_PduR_SecOCIfTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, udResult );
            }
            else
            {
                SecOC_Connector_PduR_SecOCTpTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, udResult );
            }
        }
    }
    return;
}
/****************************************************************************/
/* Function Name | SecOC_Tx_TpCopy                                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index   :                                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Tx_TpCopy
(
    uint16 u2Index
)
{
    uint8  u1_status;

    if( SecOC_TxPduProcessing[u2Index].TxAuthPduType == (uint8)SECOC_TPPDU )
    {
        u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
        if( u1_status == SECOC_TX_ST_UPPER_COPY )
        {
            SecOC_Tx_UpperCopy( u2Index );
        }
    }
    
    return ;
}

#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Tx_FinishChk                                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Tx_FinishChk
(
    uint16 u2Index
)
{
    uint8 u1_status;
    
    /* Tx Status check */
    u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
    if( ( u1_status == SECOC_TX_ST_TRANSMIT )
     && ( SecOC_TxPduProcessing[u2Index].Ab_TxSecuredPduType == (uint8)SECOC_IFPDU ) )
      {
        SecOC_Tx_GenerateProcExit( u2Index );
#if ( SECOC_AB_EARLY_TXCNF == STD_ON )
        /* Protocol check */
        if( SecOC_Ab_BusCollection[SecOC_TxPduProcessing[u2Index].Ab_BusIndex].Ab_Protocol == (uint8)SECOC_AB_PROTOCOL_ETHER )
        {
            SecOC_Tx_Finish( u2Index, E_OK );
        }
#endif
      }
}
#endif

/****************************************************************************/
/* Function Name | SecOC_Tx_GetStatus                                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | ptStatus :                                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Tx_GetStatus
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptStatus
)
{
    *ptStatus = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Tx_ClearSelect                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Tx_ClearSelect
(
    uint16 u2Index
)
{
    SecOC_Tx_GenerateProcExit( u2Index );
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Tx_ResetTpCopySize                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Tx_ResetTpCopySize
(
    void
)
{
    SecOC_Tx_u4OnePeriodAuthTpCopySize = 0U;
    
    return ;
}

#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Tx_SetDefaultAuthInfo                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2FvId           :                                       */
/*               | bDefaultAuthInfo :                                       */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK             : Success                              */
/*               |  E_NOT_OK         : Failure                              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_SetDefaultAuthInfo
(
    uint16 u2FvId,
    boolean bDefaultAuthInfo
)
{
    Std_ReturnType  ud_stdRet;
    uint16          u2_index;
    
    ud_stdRet = SecOC_Tx_SearchFvIdIndex( u2FvId, &u2_index );
    
    if( ud_stdRet == (Std_ReturnType)E_OK )
    {
        if( bDefaultAuthInfo == (boolean)TRUE )
        {
            SecOC_Tx_stCtrlInfo[u2_index].u1DefalutAuthFlag = SECOC_TX_FLAG_TRUE;
        }
        else if( bDefaultAuthInfo == (boolean)FALSE )
        {
            SecOC_Tx_stCtrlInfo[u2_index].u1DefalutAuthFlag = SECOC_TX_FLAG_FALSE;
        }
        else
        {
            ud_stdRet = E_NOT_OK;
        }
    }
    
    return ud_stdRet;
}
#endif

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | SecOC_Tx_GenerateStart                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | uint16                                                   */
/*               |  SECOC_TX_PROC_OK        :                               */
/*               |  SECOC_TX_PROC_NG_FV     :                               */
/*               |  SECOC_TX_PROC_NG_CSM    :                               */
/*               |  SECOC_TX_PROC_NG_RETRY  :                               */
/*               |  SECOC_TX_PROC_NG_OTHER  :                               */
/*               |  SECOC_TX_PROC_RETRY_CSM :                               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(uint16, SECOC_CODE) SecOC_Tx_GenerateStart
(
    uint16 u2Index
)
{
    P2CONST(SecOC_TxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_txConfig = &SecOC_TxPduProcessing[u2Index];
    SecOC_Buff_DataType         st_buff;
    Std_ReturnType              ud_buffRet;
    Std_ReturnType              ud_fvRet = E_NOT_OK;
    uint32                      u4_fullFvLen = pt_txConfig->FreshnessValueLength;
    uint16                      u2_ret = SECOC_TX_PROC_OK;
    uint8                       u1_freshnessValue[SECOC_TX_FV_SIZE];
    uint8                       u1_status;
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
    uint8                       u1_defalutAuthFlag;
#endif
    
    st_buff.ptData = NULL_PTR;
    st_buff.u4Size = 0U;
    
    /* Status check */
    SecOC_Tx_StatusCheck( u2Index );
    
    u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
    if( u1_status == SECOC_TX_ST_GENERATE )
    {
        /* Get Tx Data */
        ud_buffRet = SecOC_Buff_GetSelect( SECOC_BUFF_TX, u2Index, &st_buff );
        
        if( ud_buffRet == (Std_ReturnType)E_OK )
        {
            /* Get FreshnessValue */
            if( (pt_txConfig->Ab_QueryFreshnessValue == (uint16)SECOC_AB_FV_CFUNC)
              && (pt_txConfig->Ab_FreshnessValueFuncName != NULL_PTR) )
            {
                SecOC_Tx_stProcInfo[u2Index].u4TxFVLen = pt_txConfig->FreshnessValueTruncLength;
                
                ud_fvRet = pt_txConfig->Ab_FreshnessValueFuncName( pt_txConfig->FreshnessValueId,
                                                                   &u1_freshnessValue[0],
                                                                   &u4_fullFvLen,
                                                                   &(SecOC_Tx_stProcInfo[u2Index].u1TxFV[0]),
                                                                   &(SecOC_Tx_stProcInfo[u2Index].u4TxFVLen) );
            }
            
            if( ud_fvRet == (Std_ReturnType)E_OK )
            {
                /* No Processing */
            }
            else
            {
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
                u1_defalutAuthFlag = SecOC_Tx_stCtrlInfo[u2Index].u1DefalutAuthFlag;
                if( u1_defalutAuthFlag == SECOC_TX_FLAG_TRUE )
                {
                    SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_GENERATE_DEFAULT;
                }
                else
                {
#endif
                    SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_END;
                    u2_ret = SECOC_TX_PROC_NG_FV;
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
                }
#endif
            }
        }
        else
        {
            SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_END;
            u2_ret = SECOC_TX_PROC_NG_OTHER;
        }
    }
    else
    {
        u2_ret = SECOC_TX_PROC_NG_OTHER;
    }
    
    /* Generate MAC */
    u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
    if( u1_status == SECOC_TX_ST_GENERATE )
    {
        u2_ret = SecOC_Tx_GenerateMac( u2Index, &st_buff, &u1_freshnessValue[0], u4_fullFvLen );
    }
    
    if( (u2_ret != SECOC_TX_PROC_OK)
      && (u2_ret != SECOC_TX_PROC_RETRY_CSM) )
    {
        if( SecOC_TxPduProcessing[u2Index].TxAuthPduType == (uint8)SECOC_IFPDU )
        {
            SecOC_Connector_PduR_SecOCIfTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, E_NOT_OK );
        }
        else
        {
            SecOC_Connector_PduR_SecOCTpTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, E_NOT_OK );
        }
    }
    
    /* Buffer Clear */
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
    u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
    if( (u1_status != SECOC_TX_ST_GENERATE)
      && (u1_status != SECOC_TX_ST_RETRY)
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
      && (u1_status != SECOC_TX_ST_GENERATE_DEFAULT)
#endif
       )
    {
        SecOC_Tx_GenerateProcExit( u2Index );
    }
#endif
    
    return u2_ret;
}

/****************************************************************************/
/* Function Name | SecOC_Tx_GenerateMac                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index     :                                            */
/*               | ptBuff      :                                            */
/*               | ptFullFv    :                                            */
/*               | u4FullFvLen :                                            */
/* Return Value  | uint16                                                   */
/*               |  SECOC_TX_PROC_OK        :                               */
/*               |  SECOC_TX_PROC_NG_CSM    :                               */
/*               |  SECOC_TX_PROC_NG_RETRY  :                               */
/*               |  SECOC_TX_PROC_NG_OTHER  :                               */
/*               |  SECOC_TX_PROC_RETRY_CSM :                               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(uint16, SECOC_CODE) SecOC_Tx_GenerateMac
(
    uint16 u2Index,
    P2CONST(SecOC_Buff_DataType, AUTOMATIC, SECOC_APPL_DATA) ptBuff,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptFullFv,
    uint32 u4FullFvLen
)
{
    P2CONST(SecOC_TxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_txConfig = &SecOC_TxPduProcessing[u2Index];
    SecOC_Com_BuildAuthDataType st_bldAuth;
    Std_ReturnType              ud_macRet;
    uint16                      u2_ret = SECOC_TX_PROC_OK;
#if (SECOC_AB_TXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
    uint16                      u2_loop;
#endif
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
    uint8                       u1_defalutAuthFlag;
#endif
    
    SecOC_Tx_stCsmProcInfo[u2Index].u4InputDataSize = SecOC_TxPduProcessing[u2Index].Ab_TxMakeAuthBufferSize;
    SecOC_Tx_stCsmInOutAuthInfoSize[u2Index].u4AuthInfoSize = SECOC_TX_AUTHINFO_SIZE;
    st_bldAuth.u4DataId = pt_txConfig->Ab_DataId;
    st_bldAuth.u2DataIdLength = SecOC_Ab_BusCollection[pt_txConfig->Ab_BusIndex].Ab_DataIdLength;
    st_bldAuth.ptProtData = ptBuff->ptData;
    st_bldAuth.u4ProtDataSize = ptBuff->u4Size;
    st_bldAuth.ptFreshnessValue = ptFullFv;
    st_bldAuth.u2FreshnessValueSize = (uint16)((u4FullFvLen + SECOC_COM_BIT2BYTE_ROUND_ADD) >> SECOC_COM_BIT2BYTE_SHIFT);
    
    SecOC_Com_BuildAuthData( &st_bldAuth, &(SecOC_Tx_CsmInputData[SecOC_TxPduProcessing[u2Index].Ab_TxBufferStartOffset]), &(SecOC_Tx_stCsmProcInfo[u2Index].u4InputDataSize) );
    
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
    SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_WAIT_CALLBACK;
#endif
    ud_macRet = SecOC_Connector_Csm_MacGenerate( pt_txConfig->TxAuthServiceConfigRef.CsmJobId,
                                                 CRYPTO_OPERATIONMODE_SINGLECALL,
                                                 &(SecOC_Tx_CsmInputData[SecOC_TxPduProcessing[u2Index].Ab_TxBufferStartOffset]),
                                                 SecOC_Tx_stCsmProcInfo[u2Index].u4InputDataSize,
                                                 &(SecOC_Tx_stCsmOutputAuthInfo[u2Index].u1AuthInfo[0]),
                                                 &(SecOC_Tx_stCsmInOutAuthInfoSize[u2Index].u4AuthInfoSize) );
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
    if( pt_txConfig->Ab_ErrorDetailNotifyCallout != NULL_PTR )
    {
         pt_txConfig->Ab_ErrorDetailNotifyCallout( pt_txConfig->FreshnessValueId, ud_macRet );
    }
#endif
    
    if( ud_macRet == (Std_ReturnType)E_OK )
    {
        /* No Processing */
    }
    else if( ud_macRet == (Std_ReturnType)CRYPTO_E_BUSY )
    {
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
        SecOC_Tx_stAsyncCtrlInfo[u2Index].u1NotifyCsmResultFlg = SECOC_TX_FLAG_TRUE;
        SecOC_Tx_stAsyncCtrlInfo[u2Index].udCsmResult = ud_macRet;
#endif
        u2_ret = SecOC_Tx_BuildRetryJudge( u2Index, SECOC_TX_PROC_RETRY_CSM );
    }
    else
    {
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
        SecOC_Tx_stAsyncCtrlInfo[u2Index].u1NotifyCsmResultFlg = SECOC_TX_FLAG_TRUE;
        SecOC_Tx_stAsyncCtrlInfo[u2Index].udCsmResult = ud_macRet;
#endif
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
        u1_defalutAuthFlag = SecOC_Tx_stCtrlInfo[u2Index].u1DefalutAuthFlag;
        if( u1_defalutAuthFlag == SECOC_TX_FLAG_TRUE )
        {
            SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_GENERATE_DEFAULT;
        }
        else
        {
#endif
            SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_END;
            u2_ret = SECOC_TX_PROC_NG_CSM;
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
        }
#endif
    }

#if (SECOC_AB_TXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
    if( u2_ret == SECOC_TX_PROC_NG_RETRY )
    {
        for( u2_loop = 0U; u2_loop < SecOC_Ab_TxMsgBusyDestCoMax; u2_loop++ )
        {
            if( pt_txConfig->Ab_TxMsgBusyDestructionCallout[u2_loop] != NULL_PTR )
            {
                pt_txConfig->Ab_TxMsgBusyDestructionCallout[u2_loop]( pt_txConfig->FreshnessValueId, pt_txConfig->Ab_DataId );
            }
        }
    }
#endif
    
    return u2_ret;
}

/****************************************************************************/
/* Function Name | SecOC_Tx_GenerateFinish                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | uint16                                                   */
/*               |  SECOC_TX_PROC_OK         :                              */
/*               |  SECOC_TX_PROC_NG_PDUR    :                              */
/*               |  SECOC_TX_PROC_NG_RETRY   :                              */
/*               |  SECOC_TX_PROC_NG_OTHER   :                              */
/*               |  SECOC_TX_PROC_RETRY_PDUR :                              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(uint16, SECOC_CODE) SecOC_Tx_GenerateFinish
(
    uint16 u2Index
)
{
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
    P2CONST(SecOC_TxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_txConfig = &SecOC_TxPduProcessing[u2Index];
#endif
    SecOC_Buff_DataType st_buff;
    Std_ReturnType      ud_buffRet;
    uint32              u4_secDataSize = (uint32)SECOC_TX_SECDATA_SIZE;
    uint16              u2_ret = SECOC_TX_PROC_OK;
    uint32              u4_offset;
    uint8               u1_secData[SECOC_TX_SECDATA_SIZE];
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
    PduInfoType         st_pduInfo;
    Std_ReturnType      ud_pdurRet = E_NOT_OK;
#if (SECOC_AB_TXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
    uint16              u2_loop;
#endif
#endif
    uint8               u1_status;
    
    u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
  #if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
    if( (u1_status == SECOC_TX_ST_GENERATE)
     || (u1_status == SECOC_TX_ST_GENERATE_DEFAULT) )
  #else
    if( u1_status == SECOC_TX_ST_GENERATE )
  #endif
#else
  #if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
    if( (u1_status == SECOC_TX_ST_CALLBACK_RECEIVED)
     || (u1_status == SECOC_TX_ST_GENERATE_DEFAULT) )
  #else
    if( u1_status == SECOC_TX_ST_CALLBACK_RECEIVED )
  #endif
#endif
    {
        /* Get Tx Data */
        ud_buffRet = SecOC_Buff_GetSelect( SECOC_BUFF_TX, u2Index, &st_buff );
        
        if( ud_buffRet == (Std_ReturnType)E_OK )
        {
            u4_offset = st_buff.u4Size;
            
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
            if( u1_status == SECOC_TX_ST_GENERATE_DEFAULT )
            {
                SecOC_Tx_BuildDefaultSecData( u2Index, &u1_secData[0], &u4_secDataSize );
            }
            else
            {
#endif
                SecOC_Tx_BuildSecData( u2Index, &u1_secData[0], &u4_secDataSize );
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
            }
#endif
            
            st_buff.ptData = &u1_secData[0];
            st_buff.u4Size = u4_secDataSize;
            
            ud_buffRet = SecOC_Buff_SetSelect( SECOC_BUFF_TX, u2Index, u4_offset, &st_buff );
        }
        
        if( ud_buffRet == (Std_ReturnType)E_OK )
        {
#if( SECOC_AB_EXTD_AFTER_MAC_GENERATE == STD_ON )
            SecOC_Extd_AfterMacGen( u2Index );
#endif
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
            st_pduInfo.SduDataPtr = st_buff.ptData;
            st_pduInfo.SduLength = st_buff.u4Size;
            st_pduInfo.MetaDataPtr = NULL_PTR;
            
            SchM_Enter_SecOC_Tx();
            u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
            if( (u1_status == SECOC_TX_ST_GENERATE)
             || (u1_status == SECOC_TX_ST_GENERATE_DEFAULT) )
#else
            if( u1_status == SECOC_TX_ST_GENERATE )
#endif
            {
                if( SecOC_TxPduProcessing[u2Index].Ab_TxSecuredPduType == (uint8)SECOC_TPPDU )
                {
                    SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_TRANSMIT;
                }
                ud_pdurRet = SecOC_Connector_PduR_SecOCTransmit( pt_txConfig->Ab_TxSecuredLayerPduRefId, &st_pduInfo );
            }
            SchM_Exit_SecOC_Tx();
            
            if( ud_pdurRet == (Std_ReturnType)E_OK )
            {
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
                if( u1_status != SECOC_TX_ST_GENERATE_DEFAULT )
                {
#endif
                    if( (pt_txConfig->Ab_QueryFreshnessValue == (uint16)SECOC_AB_FV_CFUNC)
                      && (pt_txConfig->Ab_SecuredPduTransmitFuncName != NULL_PTR) )
                    {
                        pt_txConfig->Ab_SecuredPduTransmitFuncName( pt_txConfig->FreshnessValueId );
                    }
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
                }
#endif
            }
            else if( ud_pdurRet == SECOC_E_BUSY )
            {
                /* Clear SecData */
                st_buff.u4Size = SECOC_TX_CLEAR_SECDATA_SIZE;
                (void)SecOC_Buff_SetSelect( SECOC_BUFF_TX, u2Index, u4_offset, &st_buff ); /* no return check required */
                
                u2_ret = SecOC_Tx_PduRRetryJudge( u2Index, SECOC_TX_PROC_RETRY_PDUR );

#if (SECOC_AB_TXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
                if( u2_ret == SECOC_TX_PROC_NG_RETRY )
                {
                    for( u2_loop = 0U; u2_loop < SecOC_Ab_TxMsgBusyDestCoMax; u2_loop++ )
                    {
                        if( pt_txConfig->Ab_TxMsgBusyDestructionCallout[u2_loop] != NULL_PTR )
                        {
                            pt_txConfig->Ab_TxMsgBusyDestructionCallout[u2_loop]( pt_txConfig->FreshnessValueId, pt_txConfig->Ab_DataId );
                        }
                    }
                }
#endif
            }
            else
            {
                SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_END;
                u2_ret = SECOC_TX_PROC_NG_PDUR;
            }
#else
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
            if( u1_status != SECOC_TX_ST_GENERATE_DEFAULT )
            {
#endif
                SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_WAIT_NOTIFY;
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
            }
#endif
#endif
        }
        else
        {
            SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_END;
            u2_ret = SECOC_TX_PROC_NG_OTHER;
        }
    }
    else
    {
        u2_ret = SECOC_TX_PROC_NG_OTHER;
    }
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)    
    if( (u2_ret != SECOC_TX_PROC_OK)
      && (u2_ret != SECOC_TX_PROC_RETRY_PDUR) )
#else
    if(u2_ret != SECOC_TX_PROC_OK)
#endif
    {
        if( SecOC_TxPduProcessing[u2Index].TxAuthPduType == (uint8)SECOC_IFPDU )
        {
            SecOC_Connector_PduR_SecOCIfTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, E_NOT_OK );
        }
        else
        {
            SecOC_Connector_PduR_SecOCTpTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, E_NOT_OK );
        }
    }
    
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
    /* Buffer Clear */
    u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
    if( (u1_status != SECOC_TX_ST_RETRY)
        && (u1_status != SECOC_TX_ST_TRANSMIT) )
    {
        SecOC_Tx_GenerateProcExit( u2Index );
    }
#endif
    
    return u2_ret;
}

#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Tx_GenerateNotify                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | None                                                     */
/* Notes         | Async Only                                               */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Tx_GenerateNotify
(
    uint16 u2Index
)
{
    P2CONST(SecOC_TxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_txConfig = &SecOC_TxPduProcessing[u2Index];
    SecOC_Buff_DataType st_buff;
    PduInfoType         st_pduInfo;
    Std_ReturnType      ud_buffRet;
    Std_ReturnType      ud_pdurRet = E_NOT_OK;
    uint32              u4_offset;
    uint8               u1_status;
    uint8               u1_pdurNotifyFlag = SECOC_TX_FLAG_FALSE;
    uint16              u2_ret;
#if (SECOC_AB_TXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
    uint16              u2_loop;
#endif
    
    if( SecOC_Tx_stAsyncCtrlInfo[u2Index].u1NotifyCsmResultFlg == SECOC_TX_FLAG_TRUE )
    {
        if( pt_txConfig->Ab_ErrorDetailNotifyCallout != NULL_PTR )
        {
            pt_txConfig->Ab_ErrorDetailNotifyCallout( pt_txConfig->FreshnessValueId, SecOC_Tx_stAsyncCtrlInfo[u2Index].udCsmResult );
        }
    }
    
    u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
    if( (u1_status == SECOC_TX_ST_WAIT_NOTIFY)
     || (u1_status == SECOC_TX_ST_GENERATE_DEFAULT) )
#else
    if( u1_status == SECOC_TX_ST_WAIT_NOTIFY )
#endif
    {
        /* Get Tx Data */
        ud_buffRet = SecOC_Buff_GetSelect( SECOC_BUFF_TX, u2Index, &st_buff );
        
        if( ud_buffRet == (Std_ReturnType)E_OK )
        {
            st_pduInfo.SduDataPtr = st_buff.ptData;
            st_pduInfo.SduLength = st_buff.u4Size;
            st_pduInfo.MetaDataPtr = NULL_PTR;
            
            SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_TRANSMIT;
            ud_pdurRet = SecOC_Connector_PduR_SecOCTransmit( pt_txConfig->Ab_TxSecuredLayerPduRefId, &st_pduInfo );
            
            if( ud_pdurRet == (Std_ReturnType)E_OK )
            {
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
                if( u1_status != SECOC_TX_ST_GENERATE_DEFAULT )
                {
#endif
                    if( (pt_txConfig->Ab_QueryFreshnessValue == (uint16)SECOC_AB_FV_CFUNC)
                      && (pt_txConfig->Ab_SecuredPduTransmitFuncName != NULL_PTR) )
                    {
                        pt_txConfig->Ab_SecuredPduTransmitFuncName( pt_txConfig->FreshnessValueId );
                    }
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
                }
#endif
            }
            else if( ud_pdurRet == SECOC_E_BUSY )
            {
                /* Clear SecData */
                u4_offset = st_buff.u4Size - ((uint32)pt_txConfig->Ab_TxSecurityDataSize + (uint32)pt_txConfig->Ab_ProtDataPaddingSize);
                st_buff.u4Size = SECOC_TX_CLEAR_SECDATA_SIZE;
                (void)SecOC_Buff_SetSelect( SECOC_BUFF_TX, u2Index, u4_offset, &st_buff ); /* no return check required */
                
                u2_ret = SecOC_Tx_PduRRetryJudge( u2Index, SECOC_TX_PROC_RETRY_PDUR );
                
                if( u2_ret != SECOC_TX_PROC_RETRY_PDUR )
                {
#if (SECOC_AB_TXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
                    if( u2_ret == SECOC_TX_PROC_NG_RETRY )
                    {
                        for( u2_loop = 0U; u2_loop < SecOC_Ab_TxMsgBusyDestCoMax; u2_loop++ )
                        {
                            if( pt_txConfig->Ab_TxMsgBusyDestructionCallout[u2_loop] != NULL_PTR )
                            {
                                pt_txConfig->Ab_TxMsgBusyDestructionCallout[u2_loop]( pt_txConfig->FreshnessValueId, pt_txConfig->Ab_DataId );
                            }
                        }
                    }
#endif
                    u1_pdurNotifyFlag = SECOC_TX_FLAG_TRUE;
                }
            }
            else
            {
                SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_END;
                u1_pdurNotifyFlag = SECOC_TX_FLAG_TRUE;
            }
        }
        else
        {
            SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_END;
            u1_pdurNotifyFlag = SECOC_TX_FLAG_TRUE;
        }
    }
    else if( ( u1_status == SECOC_TX_ST_RETRY )
      || ( u1_status == SECOC_TX_ST_END ) )
    {
        /* No Processing */
    }
    else
    {
        u1_pdurNotifyFlag = SECOC_TX_FLAG_TRUE;
    }
    
    if( u1_pdurNotifyFlag == SECOC_TX_FLAG_TRUE )
    {
        if( SecOC_TxPduProcessing[u2Index].TxAuthPduType == (uint8)SECOC_IFPDU )
        {
            SecOC_Connector_PduR_SecOCIfTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, E_NOT_OK );
        }
        else
        {
            SecOC_Connector_PduR_SecOCTpTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, E_NOT_OK );
        }
    }
    
    SecOCStd_MemClr( &SecOC_Tx_stAsyncCtrlInfo[u2Index], sizeof(SecOC_Tx_AsyncCtrlType) );
    
    /* Buffer Clear */
    u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
    if( (u1_status != SECOC_TX_ST_RETRY)
        && (u1_status != SECOC_TX_ST_TRANSMIT) )
    {
        SecOC_Tx_GenerateProcExit( u2Index );
    }
    return ;
}
#endif

/****************************************************************************/
/* Function Name | SecOC_Tx_StatusCheck                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Tx_StatusCheck
(
    uint16 u2Index
)
{
    uint8   u1_status;
    uint16  u2_MainProcMsgCount;
    
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
    SecOCStd_MemClr( &SecOC_Tx_stAsyncCtrlInfo[u2Index], sizeof(SecOC_Tx_AsyncCtrlType) );
#endif
    
    SchM_Enter_SecOC_Tx();
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
    SecOC_Tx_stAsyncCallBackInfo[u2Index].u1CallBackEvt = SECOC_TX_FLAG_FALSE;
    SecOC_Tx_stAsyncCallBackInfo[u2Index].udCallBackCsmResult = E_NOT_OK;
#endif
    u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
    u2_MainProcMsgCount = SecOC_Tx_u2MainProcMsgCount;

    if( u1_status == SECOC_TX_ST_ACCEPT )
    {
        SecOC_Tx_stProcInfo[u2Index].u2GenerateRetryCnt = 0U;
        SecOC_Tx_stProcInfo[u2Index].u2TransmitRetryCnt = 0U;
        SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_GENERATE;
        u2_MainProcMsgCount--;
    }
    else if( u1_status == SECOC_TX_ST_RETRY )
    {
        SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_GENERATE;
        u2_MainProcMsgCount--;
    }
    else
    {
        SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_END;
    }
    
    SecOC_Tx_u2MainProcMsgCount = u2_MainProcMsgCount;
    
    SchM_Exit_SecOC_Tx();
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Tx_BuildSecData                                    */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index   :                                              */
/*               | ptMsg     :                                              */
/*               | ptMsgSize :                                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Tx_BuildSecData
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptMsg,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptMsgSize
)
{
    P2CONST(SecOC_TxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_txConfig = &SecOC_TxPduProcessing[u2Index];
    uint32  u4_len;
    uint32  u4_lenAuth;
    uint32  u4_bitCnt;
    uint32  u4_authInfoLen;
    uint16  u2_size;
    uint16  u2_loop;
    uint16  u2_index;
    uint8   u1_msk;
    
    /* Protection data padding */
    (void)SecOCStd_MemSet( &ptMsg[0], SECOC_TX_PROT_PADDING, (uint32)(pt_txConfig->Ab_ProtDataPaddingSize) ); /* no return check required */
    u2_index = pt_txConfig->Ab_ProtDataPaddingSize;
    
    /* Tx freshness value */
    u4_bitCnt = SecOC_Tx_stProcInfo[u2Index].u4TxFVLen;
    if( u4_bitCnt > (uint32)pt_txConfig->FreshnessValueTruncLength )
    {
        u4_bitCnt = (uint32)pt_txConfig->FreshnessValueTruncLength;
    }
    u2_size = (uint16)((u4_bitCnt + SECOC_COM_BIT2BYTE_ROUND_ADD) >> SECOC_COM_BIT2BYTE_SHIFT);
    for( u2_loop = 0U; u2_loop < u2_size; u2_loop++ )
    {
        ptMsg[u2_index] = SecOC_Tx_stProcInfo[u2Index].u1TxFV[u2_loop];
        u2_index++;
    }
    
    /* Tx MAC */
    u4_len = u4_bitCnt & SECOC_COM_BIT2BYTE_SURPLUS;
    u4_authInfoLen = SecOC_Tx_stCsmInOutAuthInfoSize[u2Index].u4AuthInfoSize << SECOC_COM_BIT2BYTE_SHIFT;
    if( u4_authInfoLen > (uint32)pt_txConfig->AuthInfoTruncLength )
    {
        u4_authInfoLen = (uint32)pt_txConfig->AuthInfoTruncLength;
    }
    
    if( u4_len != 0UL )
    {
        u2_index--;
        u2_size = (uint16)(u4_authInfoLen >> SECOC_COM_BIT2BYTE_SHIFT);
        for( u2_loop = 0U; u2_loop < u2_size; u2_loop++ )
        {
            ptMsg[u2_index] |= (SecOC_Tx_stCsmOutputAuthInfo[u2Index].u1AuthInfo[u2_loop] >> u4_len);
            u2_index++;
            ptMsg[u2_index] = (uint8)((uint32)SecOC_Tx_stCsmOutputAuthInfo[u2Index].u1AuthInfo[u2_loop] << ((uint32)SECOC_TX_BIT_8 - u4_len));
        }
        
        u4_lenAuth = u4_authInfoLen & SECOC_COM_BIT2BYTE_SURPLUS;
        if( u4_lenAuth != 0UL )
        {
            u1_msk = (uint8)((SECOC_TX_U1_MSK >> ((uint32)SECOC_TX_BIT_8 - u4_lenAuth)) << ((uint32)SECOC_TX_BIT_8 - u4_lenAuth));
            ptMsg[u2_index] |= ((SecOC_Tx_stCsmOutputAuthInfo[u2Index].u1AuthInfo[u2_loop] & u1_msk) >> u4_len);
        }
    }
    else
    {
        u2_size = (uint16)(u4_authInfoLen >> SECOC_COM_BIT2BYTE_SHIFT);
        for( u2_loop = 0U; u2_loop < u2_size; u2_loop++ )
        {
            ptMsg[u2_index] = SecOC_Tx_stCsmOutputAuthInfo[u2Index].u1AuthInfo[u2_loop];
            u2_index++;
        }
        
        u4_len = u4_authInfoLen & SECOC_COM_BIT2BYTE_SURPLUS;
        if( u4_len != 0UL )
        {
            u1_msk = (uint8)((SECOC_TX_U1_MSK >> ((uint32)SECOC_TX_BIT_8 - u4_len)) << ((uint32)SECOC_TX_BIT_8 - u4_len));
            ptMsg[u2_index] = SecOC_Tx_stCsmOutputAuthInfo[u2Index].u1AuthInfo[u2_loop] & u1_msk;
        }
    }
    u4_bitCnt += u4_authInfoLen;
    
    /* Set message size */
    *ptMsgSize = (u4_bitCnt + SECOC_COM_BIT2BYTE_ROUND_ADD) >> SECOC_COM_BIT2BYTE_SHIFT;
    *ptMsgSize += pt_txConfig->Ab_ProtDataPaddingSize;
    
    return ;
}

#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Tx_BuildDefaultSecData                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index   :                                              */
/*               | ptMsg     :                                              */
/*               | ptMsgSize :                                              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Tx_BuildDefaultSecData
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptMsg,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptMsgSize
)
{
    P2CONST(SecOC_TxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_txConfig = &SecOC_TxPduProcessing[u2Index];
    uint32  u4_len;
    uint32  u4_lenAuth;
    uint32  u4_bitCnt;
    uint32  u4_authInfoLen;
    uint16  u2_size;
    uint16  u2_loop;
    uint16  u2_index;
    uint8   u1_msk;
    uint8   u1_defaultPatternByte;
    uint8   u1_defaultPatternBit;
    
    /* Protection data padding */
    (void)SecOCStd_MemSet( &ptMsg[0], SECOC_TX_PROT_PADDING, (uint32)(pt_txConfig->Ab_ProtDataPaddingSize) ); /* no return check required */
    u2_index = pt_txConfig->Ab_ProtDataPaddingSize;
    
    /* Tx freshness value */
    u4_bitCnt = (uint32)pt_txConfig->FreshnessValueTruncLength;
    u2_size = (uint16)(u4_bitCnt >> SECOC_COM_BIT2BYTE_SHIFT);
    u4_len = u4_bitCnt & SECOC_COM_BIT2BYTE_SURPLUS;
    
    u1_defaultPatternBit = (uint8)(((uint32)SecOC_DefaultAuthInfoPattern << ((uint32)SECOC_TX_BIT_8 - u4_len)) & (uint32)SECOC_TX_U1_MSK);
    u1_defaultPatternByte = u1_defaultPatternBit | (SecOC_DefaultAuthInfoPattern >> u4_len);
    
    for( u2_loop = 0U; u2_loop < u2_size; u2_loop++ )
    {
        ptMsg[u2_index] = u1_defaultPatternByte;
        u2_index++;
    }
    
    if( u4_len != 0UL )
    {
        ptMsg[u2_index] = u1_defaultPatternBit;
    }
    
    /* Tx MAC */
    u4_authInfoLen = (uint32)pt_txConfig->AuthInfoTruncLength;
    u2_size = (uint16)(u4_authInfoLen >> SECOC_COM_BIT2BYTE_SHIFT);
    u1_defaultPatternByte = SecOC_DefaultAuthInfoPattern;
    
    if( u4_len != 0UL )
    {
        for( u2_loop = 0U; u2_loop < u2_size; u2_loop++ )
        {
            ptMsg[u2_index] |= (u1_defaultPatternByte >> u4_len);
            u2_index++;
            ptMsg[u2_index] = (uint8)(((uint32)u1_defaultPatternByte << ((uint32)SECOC_TX_BIT_8 - u4_len)) & (uint32)SECOC_TX_U1_MSK);
        }
        
        u4_lenAuth = u4_authInfoLen & SECOC_COM_BIT2BYTE_SURPLUS;
        if( u4_lenAuth != 0UL )
        {
            u1_msk = (uint8)((SECOC_TX_U1_MSK >> ((uint32)SECOC_TX_BIT_8 - u4_lenAuth)) << ((uint32)SECOC_TX_BIT_8 - u4_lenAuth));
            ptMsg[u2_index] |= ((u1_defaultPatternByte & u1_msk) >> u4_len);
        }
    }
    else
    {
        for( u2_loop = 0U; u2_loop < u2_size; u2_loop++ )
        {
            ptMsg[u2_index] = u1_defaultPatternByte;
            u2_index++;
        }
        
        u4_len = u4_authInfoLen & SECOC_COM_BIT2BYTE_SURPLUS;
        if( u4_len != 0UL )
        {
            u1_msk = (uint8)((SECOC_TX_U1_MSK >> ((uint32)SECOC_TX_BIT_8 - u4_len)) << ((uint32)SECOC_TX_BIT_8 - u4_len));
            ptMsg[u2_index] = u1_defaultPatternByte & u1_msk;
        }
    }
    u4_bitCnt += u4_authInfoLen;
    
    /* Set message size */
    *ptMsgSize = (u4_bitCnt + SECOC_COM_BIT2BYTE_ROUND_ADD) >> SECOC_COM_BIT2BYTE_SHIFT;
    *ptMsgSize += pt_txConfig->Ab_ProtDataPaddingSize;
    
    return ;
}
#endif

/****************************************************************************/
/* Function Name | SecOC_Tx_BuildRetryJudge                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index    :                                             */
/*               | u2NgFactor :                                             */
/* Return Value  | uint16                                                   */
/*               |  SECOC_TX_PROC_OK         :                              */
/*               |  SECOC_TX_PROC_NG_RETRY   :                              */
/*               |  SECOC_TX_PROC_NG_OTHER   :                              */
/*               |  SECOC_TX_PROC_RETRY_CSM  :                              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(uint16, SECOC_CODE) SecOC_Tx_BuildRetryJudge
(
    uint16 u2Index,
    uint16 u2NgFactor
)
{
    uint16  u2_ret = SECOC_TX_PROC_NG_OTHER;
    uint8   u1_status;
    uint16  u2_MainProcMsgCount;
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
    uint8   u1_defalutAuthFlag;
#endif
    
    if( SecOC_Tx_stProcInfo[u2Index].u2GenerateRetryCnt  < SecOC_TxPduProcessing[u2Index].AuthenticationBuildAttempts )
    {
        SchM_Enter_SecOC_Tx();
        
        u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
        
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
        if(u1_status == SECOC_TX_ST_GENERATE)
#else
        if( (u1_status == SECOC_TX_ST_GENERATE)
          || (u1_status == SECOC_TX_ST_WAIT_CALLBACK)
          || (u1_status == SECOC_TX_ST_CALLBACK_RECEIVED) )
#endif
        {
            SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_RETRY;
            u2_MainProcMsgCount = SecOC_Tx_u2MainProcMsgCount;
            u2_MainProcMsgCount++;
            SecOC_Tx_u2MainProcMsgCount = u2_MainProcMsgCount;
            u2_ret = u2NgFactor;
            SecOC_Tx_stProcInfo[u2Index].u2GenerateRetryCnt++;
        }
        
        SchM_Exit_SecOC_Tx();
    }
    else
    {
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
        u1_defalutAuthFlag = SecOC_Tx_stCtrlInfo[u2Index].u1DefalutAuthFlag;
        if( u1_defalutAuthFlag == SECOC_TX_FLAG_TRUE )
        {
            SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_GENERATE_DEFAULT;
            u2_ret = SECOC_TX_PROC_OK;
        }
        else
        {
#endif
            SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_END;
            u2_ret = SECOC_TX_PROC_NG_RETRY;
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
        }
#endif
    }
    
    return u2_ret;
}

/****************************************************************************/
/* Function Name | SecOC_Tx_PduRRetryJudge                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index    :                                             */
/*               | u2NgFactor :                                             */
/* Return Value  | uint16                                                   */
/*               |  SECOC_TX_PROC_NG_RETRY   :                              */
/*               |  SECOC_TX_PROC_NG_OTHER   :                              */
/*               |  SECOC_TX_PROC_RETRY_PDUR :                              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(uint16, SECOC_CODE) SecOC_Tx_PduRRetryJudge
(
    uint16 u2Index,
    uint16 u2NgFactor
)
{
    uint16  u2_ret = SECOC_TX_PROC_NG_OTHER;
    uint8   u1_status;
    uint16  u2_MainProcMsgCount;
    
    if( SecOC_Tx_stProcInfo[u2Index].u2TransmitRetryCnt < SecOC_TxPduProcessing[u2Index].Ab_TxTransmitAttempts )
    {
        SchM_Enter_SecOC_Tx();
        
        u1_status = SecOC_Tx_stCtrlInfo[u2Index].u1Status;
        
        if( (u1_status == SECOC_TX_ST_GENERATE)
          || (u1_status == SECOC_TX_ST_TRANSMIT) )
        {
            SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_RETRY;
            u2_MainProcMsgCount = SecOC_Tx_u2MainProcMsgCount;
            u2_MainProcMsgCount++;
            SecOC_Tx_u2MainProcMsgCount = u2_MainProcMsgCount;
            u2_ret = u2NgFactor;
            SecOC_Tx_stProcInfo[u2Index].u2TransmitRetryCnt++;
        }
        
        SchM_Exit_SecOC_Tx();
    }
    else
    {
        SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_END;
        u2_ret = SECOC_TX_PROC_NG_RETRY;
    }
    
    return u2_ret;
}

/****************************************************************************/
/* Function Name | SecOC_Tx_GenerateProcExit                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index:                                                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Tx_GenerateProcExit
(
    uint16 u2Index
)
{
    Std_ReturnType  ud_buffRet;
    
    ud_buffRet = SecOC_Buff_ClearSelect( SECOC_BUFF_TX, u2Index );
    if( ud_buffRet == (Std_ReturnType)E_OK )
    {
        SecOCStd_MemClr( &SecOC_Tx_stProcInfo[u2Index], sizeof(SecOC_Tx_stProcInfo[u2Index]) );
        SecOCStd_MemClr( &SecOC_Tx_stCsmProcInfo[u2Index], sizeof(SecOC_Tx_CsmProcessType) );
        SecOCStd_MemClr( &SecOC_Tx_stCsmOutputAuthInfo[u2Index], sizeof(SecOC_Tx_CsmOutputAuthType) );
        SecOCStd_MemClr( &SecOC_Tx_stCsmInOutAuthInfoSize[u2Index], sizeof(SecOC_Tx_CsmInOutAuthSizeType) );
        (void)SecOC_Buff_WriteTotalSize( SECOC_BUFF_TX, u2Index, (uint32)0U ); /* no return check required */
        (void)SecOC_Buff_WriteDividePos( SECOC_BUFF_TX, u2Index, (uint32)0U ); /* no return check required */
        SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_IDLE;
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Tx_UpperCopy                                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index:                                                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_Tx_UpperCopy
(
    uint16 u2Index
)
{
    P2CONST(SecOC_TxPduProcessingType, AUTOMATIC, SECOC_APPL_DATA) pt_txConfig = &SecOC_TxPduProcessing[u2Index];
    uint8               u1_ngCopyFlag = SECOC_TX_FLAG_FALSE;
    SecOC_Buff_DataType st_buff;
    Std_ReturnType      ud_stdGetSelectRet;
    Std_ReturnType      ud_stdReadTotalSizeRet;
    uint32              u4_totalMsgSize = 0U;
    BufReq_ReturnType   ud_buffRet = BUFREQ_E_NOT_OK;
    PduInfoType         st_pduInfo;
    RetryInfoType*      pt_pduRetryPtr = NULL_PTR;
    uint32              u4_diffMsgSize = 0U;
    PduLengthType       ud_pduAvailableDataSize = 0U;
    uint32              u4_remainAuthTpCopySize = 0U;
    uint32              u4_useSize;
    uint16              u2_MainProcMsgCount;
#if (SECOC_AB_TXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
    uint16              u2_loop;
#endif
    
    SecOCStd_MemClr( &st_pduInfo, sizeof(PduInfoType) );

    /* Get Tx Data */
    ud_stdGetSelectRet = SecOC_Buff_GetSelect( SECOC_BUFF_TX, u2Index, &st_buff );
    
    ud_stdReadTotalSizeRet = SecOC_Buff_ReadTotalSize( SECOC_BUFF_TX, u2Index, &u4_totalMsgSize );
    
    if( ( ud_stdGetSelectRet == (Std_ReturnType)E_OK )
     && ( ud_stdReadTotalSizeRet == (Std_ReturnType)E_OK ) )
    {
        if( u4_totalMsgSize >= st_buff.u4Size )
        {
            u4_diffMsgSize = u4_totalMsgSize - st_buff.u4Size;
            
            st_pduInfo.SduDataPtr = &st_buff.ptData[st_buff.u4Size];
        }
        else
        {
            u1_ngCopyFlag = SECOC_TX_FLAG_TRUE;
        }
    }
    else
    {
        u1_ngCopyFlag = SECOC_TX_FLAG_TRUE;
    }
    
    if( u1_ngCopyFlag == SECOC_TX_FLAG_FALSE )
    {
        if( SecOC_TxPduProcessing[u2Index].Ab_TxAuthTpCopySize <= u4_diffMsgSize )
        {
            st_pduInfo.SduLength = SecOC_TxPduProcessing[u2Index].Ab_TxAuthTpCopySize;
        }
        else
        {
            st_pduInfo.SduLength = u4_diffMsgSize;
        }
        
        if( SecOC_Ab_TxAuthTpCopyTotalSize > SecOC_Tx_u4OnePeriodAuthTpCopySize)
        {
            u4_remainAuthTpCopySize = SecOC_Ab_TxAuthTpCopyTotalSize - SecOC_Tx_u4OnePeriodAuthTpCopySize;
        }
        
        if( st_pduInfo.SduLength > u4_remainAuthTpCopySize )
        {
            st_pduInfo.SduLength = u4_remainAuthTpCopySize;
        }
        
        if( st_pduInfo.SduLength > 0U )
        {
            u4_useSize = st_buff.u4Size + st_pduInfo.SduLength;
            
            /* Size check */
            if( u4_useSize <= SecOC_TxPduProcessing[u2Index].SameBufferPduRef )
            {
                ud_buffRet = SecOC_Connector_PduR_SecOCTpCopyTxData( pt_txConfig->Ab_TxAuthenticLayerPduRefId, &st_pduInfo, pt_pduRetryPtr, &ud_pduAvailableDataSize );
            }
        }
        else
        {
            ud_buffRet = BUFREQ_OK;
        }
        
        if( ud_buffRet == (BufReq_ReturnType)BUFREQ_OK )
        {
            st_buff.u4Size += st_pduInfo.SduLength;
            
            SecOC_Tx_u4OnePeriodAuthTpCopySize += st_pduInfo.SduLength;
            
            (void)SecOC_Buff_SetSelectSize( u2Index, st_buff.u4Size ); /* no return check required */
            
            if( st_buff.u4Size >= u4_totalMsgSize )
            {
                SchM_Enter_SecOC_Tx();
                
                SecOC_Tx_stCtrlInfo[u2Index].u1Status = SECOC_TX_ST_ACCEPT;
                u2_MainProcMsgCount = SecOC_Tx_u2MainProcMsgCount;
                u2_MainProcMsgCount++;
                SecOC_Tx_u2MainProcMsgCount = u2_MainProcMsgCount;
                SecOC_Tx_stProcInfo[u2Index].u2CopyRetryCnt = 0U;
                (void)SecOC_Buff_WriteTotalSize( SECOC_BUFF_TX, u2Index, (uint32)0U ); /* no return check required */
                
                SchM_Exit_SecOC_Tx();
            }
        }
        else if( ud_buffRet == (BufReq_ReturnType)BUFREQ_E_BUSY )
        {
            if( SecOC_Tx_stProcInfo[u2Index].u2CopyRetryCnt < SecOC_TxPduProcessing[u2Index].Ab_TxAuthTpCopyAttempts )
            {
                SecOC_Tx_stProcInfo[u2Index].u2CopyRetryCnt++;
            }
            else
            {
#if (SECOC_AB_TXMSG_BUSY_DESTRUCTION_CALLOUT_MAX > 0U)
                for( u2_loop = 0U; u2_loop < SecOC_Ab_TxMsgBusyDestCoMax; u2_loop++ )
                {
                    if( pt_txConfig->Ab_TxMsgBusyDestructionCallout[u2_loop] != NULL_PTR )
                    {
                        pt_txConfig->Ab_TxMsgBusyDestructionCallout[u2_loop]( pt_txConfig->FreshnessValueId, pt_txConfig->Ab_DataId );
                    }
                }
#endif
                SecOC_Tx_GenerateProcExit( u2Index );
                SecOC_Connector_PduR_SecOCTpTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, E_NOT_OK );
            }
        }
        else
        {
            SecOC_Tx_GenerateProcExit( u2Index );
            SecOC_Connector_PduR_SecOCTpTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, E_NOT_OK );
        }
    }
    else
    {
        SecOC_Tx_GenerateProcExit( u2Index );
        SecOC_Connector_PduR_SecOCTpTxConfirmation( SecOC_TxPduProcessing[u2Index].Ab_TxAuthenticLayerPduRefId, E_NOT_OK );
    }
    
    return ;
}

#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_Tx_SearchFvIdIndex                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2FvId  :                                                */
/*               | ptIndex :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK             : Success                              */
/*               |  E_NOT_OK         : Failure                              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Tx_SearchFvIdIndex
(
    uint16 u2FvId,
    P2VAR(uint16, AUTOMATIC, SECOC_APPL_DATA) ptIndex
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    uint16          u2_index;
    
    for( u2_index = 0U; u2_index < (uint16)SecOC_TxPduProcessingMax; u2_index++ )
    {
        if( u2FvId == SecOC_TxPduProcessing[u2_index].FreshnessValueId )
        {
            *ptIndex = u2_index;
            ud_stdRet = E_OK;
            break;
        }
    }
    
    return ud_stdRet;
}
#endif

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

#endif /* SECOC_TX_PDU_PROCESSING */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/*  v2-1-0     :2023/04/14                                                  */
/*  v2-1-1     :2023/06/02                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
