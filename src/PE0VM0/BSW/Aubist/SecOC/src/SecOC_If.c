/* SecOC_If_c_v2-1-2                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC/If/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Rte_SecOC.h>
#include <SchM_SecOC.h>
#include <SecOC_CD_FV.h>
#include <SecOC.h>
#include <SecOC_Cbk.h>
#include <SecOCStd_Util.h>
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING == STD_ON)
#include <Csm.h>
#include "../usr/SecOC_Connector.h"
#endif
#include "../inc/SecOC_Buff.h"
#if (SECOC_AB_EXTENDED_ENABLE == STD_ON)
#include "../inc/SecOC_Extd_Internal.h"
#endif
#include "../inc/SecOC_Rx.h"
#include "../inc/SecOC_Tx.h"
#include "../inc/SecOC_If.h"

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

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
static FUNC(uint16, SECOC_CODE) SecOC_If_RxMain
(
    uint16 u2Index
);
#endif
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
static FUNC(void, SECOC_CODE) SecOC_If_TxMain
(
    uint16 u2Index
);
#endif
#if (SECOC_AB_REPORT_ERROR_CALLOUT_MAX > 0U)
static FUNC(void, SECOC_CODE) SecOC_If_DetectErrorRx
(
    void
);
static FUNC(void, SECOC_CODE) SecOC_If_DetectErrorTx
(
    void
);
static FUNC(SecOC_ErrorStatusType, SECOC_CODE) SecOC_If_RamCheck
(
    void
);
static FUNC(void, SECOC_CODE) SecOC_If_NotifyError
(
    SecOC_ErrorStatusType  udErrorStatus
);
#endif

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_VAR_CLEARED_WAKEUP
#include <SecOC_MemMap.h>

VAR(SecOC_StateType, SECOC_VAR_CLEARED_WAKEUP) SecOC_If_udState;    /* SecOC Status */

#define SECOC_STOP_SEC_VAR_CLEARED_WAKEUP
#include <SecOC_MemMap.h>

#define SECOC_START_SEC_VAR_NO_INIT
#include <SecOC_MemMap.h>

#if (((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)) \
  || ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)))
static VAR(uint16, SECOC_VAR_NO_INIT) SecOC_If_u2ProcessedMsgNum;
#endif

#define SECOC_STOP_SEC_VAR_NO_INIT
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
/* Function Name | SecOC_Init                                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | config : not use                                         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Init
(
    P2CONST(SecOC_ConfigType, AUTOMATIC, SECOC_APPL_CONST) config
)
{
    SecOC_If_udState = SECOC_UNINIT;
#if (((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)) \
  || ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)))
    SecOC_If_u2ProcessedMsgNum = 0U;
#endif
    
    SecOC_Config_Init( config );
    
    /* Unit initialize */
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    SecOC_Tx_Reset();
#endif
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    SecOC_Rx_Reset();
#endif
    
#if ( ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)) \
    || ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)) )
    SecOC_Buff_Init();
#endif
    
#if (SECOC_AB_EXTD_INIT == STD_ON)
    SecOC_Extd_Init();
#endif
    /* FV initialize */
    SecOC_CD_FV_Init();
    
    /* Init finish */
    SecOC_If_udState = SECOC_INIT;
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_DeInit                                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_DeInit
(
    void
)
{
    /* SecOC status check */
    if( SecOC_If_udState == SECOC_INIT )
    {
        SecOC_If_udState = SECOC_UNINIT;
#if (((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)) \
  || ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)))
        SecOC_If_u2ProcessedMsgNum = 0U;
#endif
        
        /* Unit deinitialize */
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
        SecOC_Tx_Reset();
#endif
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
        SecOC_Rx_Reset();
#endif
       
#if ( ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)) \
    || ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)) )
        SecOC_Buff_Reset();
#endif
        
#if (SECOC_AB_EXTD_DEINIT == STD_ON)
        SecOC_Extd_DeInit();
#endif
        /* FV initialize */
        SecOC_CD_FV_Init();
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_GetVersionInfo                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | versioninfo :                                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, SECOC_APPL_DATA) versioninfo
)
{
#if (SECOC_VERSION_INFO_API == STD_ON)
    /* Parameters check */
    if( versioninfo != NULL_PTR )
    {
        versioninfo->vendorID = SECOC_VENDOR_ID;
        versioninfo->moduleID = SECOC_MODULE_ID;
        versioninfo->sw_major_version = SECOC_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = SECOC_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = SECOC_SW_PATCH_VERSION;
    }
#endif
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_IfTransmit                                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | TxPduId    :                                             */
/*               | PduInfoPtr :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK             : Success                              */
/*               |  E_NOT_OK         : Failure                              */
/*               |  PDUR_BUSY        : Busy                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_IfTransmit
(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) PduInfoPtr
)
{
    Std_ReturnType      ud_stdRet = E_NOT_OK;
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    
    /* Parameters check */
    if( (SecOC_If_udState == SECOC_INIT)
        && (PduInfoPtr != NULL_PTR)
        && (PduInfoPtr->SduDataPtr != NULL_PTR)
        && (TxPduId < SecOC_TxPduProcessingMax) )
    {
        /* PduId check */
        if( SecOC_TxPduProcessing[TxPduId].SameBufferPduRef >= SecOC_TxPduProcessing[TxPduId].Ab_TxSecurityDataSize )
        {
            if( SecOC_TxPduProcessing[TxPduId].TxAuthPduType == (uint8)SECOC_IFPDU )
            {
                /* Size check */
#if( SECOC_AB_FIXED_MESSAGE_SIZE == STD_ON )
                if( PduInfoPtr->SduLength == (SecOC_TxPduProcessing[TxPduId].SameBufferPduRef - SecOC_TxPduProcessing[TxPduId].Ab_TxSecurityDataSize) )

#else
                if( (PduInfoPtr->SduLength <= (SecOC_TxPduProcessing[TxPduId].SameBufferPduRef - SecOC_TxPduProcessing[TxPduId].Ab_TxSecurityDataSize) )
                  && (PduInfoPtr->SduLength >= SecOC_TxPduProcessing[TxPduId].Ab_ProtDataPaddingSize) )
#endif
                {
                    ud_stdRet = SecOC_Tx_IfTransmit( TxPduId, PduInfoPtr );
                }
            }
        }
    }
#endif
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_IfCancelTransmit                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | TxPduId :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_IfCancelTransmit
(
    PduIdType TxPduId
)
{
    Std_ReturnType      ud_stdRet = E_NOT_OK;
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    
    /* Parameters check */
    if( ( SecOC_If_udState == SECOC_INIT ) &&
      ( TxPduId < SecOC_TxPduProcessingMax ) )
    {

            if( SecOC_TxPduProcessing[TxPduId].TxAuthPduType == (uint8)SECOC_IFPDU )
            {
               ud_stdRet = SecOC_Tx_Cancel( TxPduId );
            }
    }
#endif
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Ab_VerifyStatusOverride                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ValueID  :                                               */
/*               | overrideStatus :                                         */
/*               | numberOfMessagesToOverride :                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Ab_VerifyStatusOverride
(
    uint32 ValueID,
    SecOC_OverrideStatusType overrideStatus,
    uint8 numberOfMessagesToOverride
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    
    /* Parameters check */
    if( SecOC_If_udState == SECOC_INIT )
    {
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
        if ( overrideStatus == SECOC_OVERRIDE_CANCEL )
        {
            ud_stdRet = SecOC_Rx_SetVerifyStatusOverride( ValueID, SECOC_RX_OVERRIDE_CANCEL, numberOfMessagesToOverride );
        }
        else if ( overrideStatus == SECOC_OVERRIDE_DROP_UNTIL_NOTICE )
        {
            ud_stdRet = SecOC_Rx_SetVerifyStatusOverride( ValueID, SECOC_RX_OVERRIDE_DROP_UNTIL_NOTICE, numberOfMessagesToOverride );
        }
        else if ( overrideStatus == SECOC_OVERRIDE_DROP_UNTIL_LIMIT )
        {
            ud_stdRet = SecOC_Rx_SetVerifyStatusOverride( ValueID, SECOC_RX_OVERRIDE_DROP_UNTIL_LIMIT, numberOfMessagesToOverride );
        }
#if (SECOC_ENABLE_FORCED_PASS_OVERRIDE == STD_ON)
        else if ( overrideStatus == SECOC_OVERRIDE_PASS_UNTIL_NOTICE )
        {
            ud_stdRet = SecOC_Rx_SetVerifyStatusOverride( ValueID, SECOC_RX_OVERRIDE_PASS_UNTIL_NOTICE, numberOfMessagesToOverride );
        }
        else if ( overrideStatus == SECOC_OVERRIDE_PASS_UNTIL_LIMIT )
        {
            ud_stdRet = SecOC_Rx_SetVerifyStatusOverride( ValueID, SECOC_RX_OVERRIDE_PASS_UNTIL_LIMIT, numberOfMessagesToOverride );
        }
        else if ( overrideStatus == SECOC_OVERRIDE_SKIP_UNTIL_NOTICE )
        {
            ud_stdRet = SecOC_Rx_SetVerifyStatusOverride( ValueID, SECOC_RX_OVERRIDE_SKIP_UNTIL_NOTICE, numberOfMessagesToOverride );
        }
        else if ( overrideStatus == SECOC_OVERRIDE_SKIP_UNTIL_LIMIT )
        {
            ud_stdRet = SecOC_Rx_SetVerifyStatusOverride( ValueID, SECOC_RX_OVERRIDE_SKIP_UNTIL_LIMIT, numberOfMessagesToOverride );
        }
#endif
        else
        {
            /* No Processing */
#endif
#if (SECOC_AB_EXTD_VERIFY_STATUS_OVERRIDE == STD_ON)
            ud_stdRet = SecOC_Extd_VerifyStatusOverride( ValueID, overrideStatus, numberOfMessagesToOverride);
#endif
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
        }
#endif
    }
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Ab_FreshnessValueRead                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2FvId  :                                                */
/*               | ptFv    :                                                */
/*               | ptFvLen :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Ab_FreshnessValueRead
(
    uint16 u2FvId,
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptFv,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptFvLen
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    
    /* Parameters check */
    if( SecOC_If_udState == SECOC_INIT)
    {
        ud_stdRet = SecOC_CD_FV_Read( u2FvId, ptFv, ptFvLen );
    }
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Ab_FreshnessValueWrite                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2FvId  :                                                */
/*               | ptFv    :                                                */
/*               | u4FvLen :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Ab_FreshnessValueWrite
(
    uint16 u2FvId,
    P2CONST(uint8, AUTOMATIC, SECOC_APPL_DATA) ptFv,
    uint32 u4FvLen
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    
    /* Parameters check */
    if( SecOC_If_udState == SECOC_INIT)
    {
        ud_stdRet = SecOC_CD_FV_Write( u2FvId, ptFv, u4FvLen );
    }
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_RxIndication                                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | RxPduId    :                                             */
/*               | PduInfoPtr :                                             */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_RxIndication
(
    PduIdType RxPduId,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) PduInfoPtr
)
{
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    
    /* Parameters check */
    if( (SecOC_If_udState == SECOC_INIT)
        && (PduInfoPtr != NULL_PTR)
        && (PduInfoPtr->SduDataPtr != NULL_PTR)
        && (RxPduId < SecOC_RxPduProcessingMax ) )
    {
            if( SecOC_RxPduProcessing[RxPduId].Ab_RxSecuredPduType == (uint8)SECOC_IFPDU )
            {
#if( SECOC_AB_FIXED_MESSAGE_SIZE == STD_ON )
                /* Size check */
                if( PduInfoPtr->SduLength == SecOC_RxPduProcessing[RxPduId].SameBufferPduRef )
                {
                    SecOC_Rx_Receive( RxPduId, PduInfoPtr );
                }
#else
                /* Size check */
                if( PduInfoPtr->SduLength >= ( (uint32)SecOC_RxPduProcessing[RxPduId].Ab_TxSecurityDataSize + (uint32)SecOC_RxPduProcessing[RxPduId].Ab_ProtDataPaddingSize ) )
                {
                    SecOC_Rx_Receive( RxPduId, PduInfoPtr );
                }
#endif
            }
    }
#endif
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_TxConfirmation                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | TxPduId :                                                */
/*               | result  :                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_TxConfirmation
(
    PduIdType TxPduId,
    Std_ReturnType result
)
{
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    
    /* Parameters check */
    if(( SecOC_If_udState == SECOC_INIT ) &&
      ( TxPduId < SecOC_TxPduProcessingMax ) )
    {
            if( SecOC_TxPduProcessing[TxPduId].Ab_TxSecuredPduType == (uint8)SECOC_IFPDU )
            {
#if ((SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON) && \
     (SECOC_AB_EARLY_TXCNF == STD_ON) )
                /* Protocol check */
                if( SecOC_Ab_BusCollection[SecOC_TxPduProcessing[TxPduId].Ab_BusIndex].Ab_Protocol != (uint8)SECOC_AB_PROTOCOL_ETHER )
                {
                    SecOC_Tx_Finish( TxPduId, result );
                }
#else
                SecOC_Tx_Finish( TxPduId, result );
#endif
            }
    }
#endif
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_MainFunctionTx                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_MainFunctionTx
(
    void
)
{
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    Std_ReturnType  ud_buffRet;
    uint16          u2_index = 0U;
    uint16          u2_OrderCount = 0U;
    uint8           u1_statusRet;
#endif

#if (SECOC_AB_REPORT_ERROR_CALLOUT_MAX > 0U)
    SecOC_If_DetectErrorTx();
#endif
    
    /* Parameters check */
    if( SecOC_If_udState == SECOC_INIT )
    {
#if (((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)) \
  && ((SECOC_RX_PDU_PROCESSING == STD_OFF) || (SECOC_RX_PDU_PROCESSING_MAX == 0U)))
        SecOC_If_u2ProcessedMsgNum = (uint16)0U;
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
        SecOC_Tx_ResetTpCopySize();
#endif

#if( SECOC_AB_EXTD_AFTER_ASYNC_NOTIFY_TX == STD_ON )
        SecOC_Extd_AfterAsyncNotifyTx();
#endif

#if (SECOC_AB_EXTD_MAIN_FUNC_PERIOD_TX == STD_ON)
        SecOC_Extd_MainFuncPeriodTx();
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U) \
  && (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON))
        SecOC_Tx_ReapCallbackEvt();
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
        do
        {
            u1_statusRet = SECOC_TX_ST_IDLE;
            
            ud_buffRet = SecOC_Buff_GetOrder( SECOC_BUFF_TX, u2_OrderCount, &u2_index );
            
            if( ud_buffRet == (Std_ReturnType)E_OK )
            {
                SecOC_Tx_GetStatus( u2_index, &u1_statusRet );
                
                if( u1_statusRet == SECOC_TX_ST_IDLE )
                {
                    SecOC_Tx_ClearSelect( u2_index );
                }
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
                SecOC_Tx_AsyncNotify( u2_index );
                
                SecOC_Tx_FinishChk( u2_index );
#endif
                SecOC_Tx_TpCopy( u2_index );
                
                SecOC_If_TxMain( u2_index );
                
                SecOC_Tx_GetStatus( u2_index, &u1_statusRet );
                
                if( u1_statusRet == SECOC_TX_ST_IDLE )
                {
                    /* No Processing */
                }
                else
                {
                    u2_OrderCount++;
                }
            }
        }
        while( ud_buffRet == (Std_ReturnType)E_OK );
#endif
    }
    
    return ;
}


/****************************************************************************/
/* Function Name | SecOC_MainFunctionRx                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_MainFunctionRx
(
    void
)
{
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    Std_ReturnType  ud_buffRet;
    uint16          u2_index = 0U;
    uint16          u2_OrderCount = 0U;
    uint8           u1_statusRet;
    uint16          u2_processResult;
#endif
    
#if (SECOC_AB_REPORT_ERROR_CALLOUT_MAX > 0U)
    SecOC_If_DetectErrorRx();
#endif
    
    /* Parameters check */
    if( SecOC_If_udState == SECOC_INIT )
    {
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
        SecOC_If_u2ProcessedMsgNum = (uint16)0U;
        
        SecOC_Rx_ResetTpCopySize();
#endif

#if( SECOC_AB_EXTD_AFTER_ASYNC_NOTIFY_RX == STD_ON )
        SecOC_Extd_AfterAsyncNotifyRx();
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
        /* Period */
        SecOC_Rx_MainFuncPeriod();
#endif

#if (SECOC_AB_EXTD_MAIN_FUNC_PERIOD_RX == STD_ON)
        SecOC_Extd_MainFuncPeriodRx();
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
        SecOC_Rx_ReapEvt();

        do
        {
            u1_statusRet = SECOC_RX_ST_IDLE;
            
            ud_buffRet = SecOC_Buff_GetOrder( SECOC_BUFF_RX, u2_OrderCount, &u2_index );
            
            if( ud_buffRet == (Std_ReturnType)E_OK )
            {
                SecOC_Rx_GetStatus( u2_index, &u1_statusRet );
                
                if( u1_statusRet == SECOC_RX_ST_IDLE )
                {
                    SecOC_Rx_ClearSelect( u2_index );
                }
                
#if (SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON)
                SecOC_Rx_AsyncNotify( u2_index );
#endif
                SecOC_Rx_VerifyDropSkip( u2_index );
                
                u2_processResult = SecOC_If_RxMain( u2_index );
                    
                SecOC_Rx_TpNotify( u2_index );
                
                SecOC_Rx_GetStatus( u2_index, &u1_statusRet );
                
                if( u1_statusRet == SECOC_RX_ST_IDLE )
                {
                    /* No Processing */
                }
                else if( u1_statusRet == SECOC_RX_ST_RETRY )
                {
                    if( (u2_processResult == SECOC_RX_PROC_RETRY_FV)
                     || (u2_processResult == SECOC_RX_PROC_RETRY_MAC) )
                    {
                        /* No Processing */
                    }
                    else
                    {
                        u2_OrderCount++;
                    }
                }
                else
                {
                    u2_OrderCount++;
                }
            }
        }
        while( ud_buffRet == (Std_ReturnType)E_OK );
#endif
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_MacGenCallback                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | jobId :                                                  */
/*               | result :                                                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_MacGenCallback
(
    uint32 jobId,
    Crypto_ResultType result
)
{
#if ((SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON) && (SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))

    
    /* Parameters check */
    if((SecOC_If_udState == SECOC_INIT ) &&
      ( jobId < SECOC_JOBID_2_MSG_TBL_IDX_MAX ) )
    {
            SecOC_Tx_GenerateCallback( SecOC_JobId2MsgTblIdx[jobId], result );
    }
#endif
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_MacVerCallback                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | jobId :                                                  */
/*               | result :                                                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_MacVerCallback
(
    uint32 jobId,
    Crypto_ResultType result
)
{
#if ((SECOC_AB_CSM_USE_SYNC_JOB_PROCESSING != STD_ON) && (SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))

    /* Parameters check */
    if((SecOC_If_udState == SECOC_INIT ) &&
      ( jobId < SECOC_JOBID_2_MSG_TBL_IDX_MAX ) )
    {
            SecOC_Rx_VerifyCallback( SecOC_JobId2MsgTblIdx[jobId], result );
    }
#endif
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Ab_GetMode                                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptMode :                                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Ab_GetMode
(
    P2VAR(SecOC_ModeType, AUTOMATIC, SECOC_APPL_DATA) ptMode
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    SecOC_ModeType  ud_txMode;
#endif
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    SecOC_ModeType  ud_rxMode;
#endif
    
    /* Parameter check */
    if( ptMode != NULL_PTR )
    {
        ud_stdRet = E_OK;
        
        /* SecOC status check */
        if( SecOC_If_udState == SECOC_INIT )
        {
            *ptMode = SECOC_M_IDLE;
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
            /* Tx Massage check */
            ud_txMode = SecOC_Tx_GetMode();
            
            if( ud_txMode == SECOC_M_RUN )
            {
                *ptMode = SECOC_M_RUN;
            }
            if( (*ptMode != SECOC_M_RUN) && (ud_txMode == SECOC_M_ABNORMAL) )
            {
                *ptMode = SECOC_M_ABNORMAL;
            }
#endif
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
            /* Rx Massage check */
            ud_rxMode = SecOC_Rx_GetMode();
            
            if( ud_rxMode == SECOC_M_RUN )
            {
                *ptMode = SECOC_M_RUN;
            }
            if( (*ptMode != SECOC_M_RUN) && (ud_rxMode == SECOC_M_ABNORMAL) )
            {
                *ptMode = SECOC_M_ABNORMAL;
            }
#endif
        }
        else
        {
            *ptMode = SECOC_M_UNINIT;
        }
    }
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Ab_ResetBus                                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BusId :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Ab_ResetBus
(
    uint16 u2BusId
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    
    /* Parameters check */
    if(( SecOC_If_udState == SECOC_INIT ) &&
      ( u2BusId < SecOC_Ab_BusMax ) )
    {

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
                /* Reset VerifyStart */
                SecOC_Rx_ResetBus( u2BusId );
#endif

#if (SECOC_AB_EXTD_BUS_RESET == STD_ON)
                SecOC_Extd_ResetBus( u2BusId );
#endif
                
                /* Reset FV */
                ud_stdRet = SecOC_CD_FV_ResetBus( u2BusId );
    }
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_TpTransmit                                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | TxPduId    :                                             */
/*               | PduInfoPtr :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK             : Success                              */
/*               |  E_NOT_OK         : Failure                              */
/*               |  PDUR_BUSY        : Busy                                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_TpTransmit
(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) PduInfoPtr
)
{
    Std_ReturnType      ud_stdRet = E_NOT_OK;
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    
    /* Parameters check */
    if( (SecOC_If_udState == SECOC_INIT)
        && (PduInfoPtr != NULL_PTR)
        && (PduInfoPtr->SduDataPtr != NULL_PTR)
        && (TxPduId < SecOC_TxPduProcessingMax) )
    {
        
        /* PduId check */
        if( SecOC_TxPduProcessing[TxPduId].SameBufferPduRef >= SecOC_TxPduProcessing[TxPduId].Ab_TxSecurityDataSize )
        {
            if( SecOC_TxPduProcessing[TxPduId].TxAuthPduType == (uint8)SECOC_TPPDU )
            {
                /* Size check */
#if( SECOC_AB_FIXED_MESSAGE_SIZE == STD_ON )
                if( PduInfoPtr->SduLength == (SecOC_TxPduProcessing[TxPduId].SameBufferPduRef - SecOC_TxPduProcessing[TxPduId].Ab_TxSecurityDataSize) )

#else
                if( (PduInfoPtr->SduLength <= ( SecOC_TxPduProcessing[TxPduId].SameBufferPduRef - SecOC_TxPduProcessing[TxPduId].Ab_TxSecurityDataSize) )
                  && (PduInfoPtr->SduLength >= SecOC_TxPduProcessing[TxPduId].Ab_ProtDataPaddingSize) )
#endif
                {
                    ud_stdRet = SecOC_Tx_TpTransmit( TxPduId, PduInfoPtr );
                }
            }
        }
    }
#endif
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_TpCancelTransmit                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | TxPduId :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_TpCancelTransmit
(
    PduIdType TxPduId
)
{
    Std_ReturnType      ud_stdRet = E_NOT_OK;
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))

    
    /* Parameters check */
    if(( SecOC_If_udState == SECOC_INIT ) &&
      ( TxPduId < SecOC_TxPduProcessingMax ) )
    {
            if( SecOC_TxPduProcessing[TxPduId].TxAuthPduType == (uint8)SECOC_TPPDU )
            {
               ud_stdRet = SecOC_Tx_Cancel( TxPduId );
            }
    }
#endif
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_TpCancelReceive                                    */
/* Description   |  Dummy Function                                          */
/* Preconditions |                                                          */
/* Parameters    | RxPduId :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_TpCancelReceive
(
    PduIdType RxPduId
)
{
    return E_NOT_OK;
}

/****************************************************************************/
/* Function Name | SecOC_TpRxIndication                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | id     :                                                 */
/*               | result :                                                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_TpRxIndication
(
    PduIdType id,
    Std_ReturnType result
)
{
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    
    /* Parameters check */
    if( ( SecOC_If_udState == SECOC_INIT )
      &&( id < SecOC_RxPduProcessingMax) )
    {
            if( SecOC_RxPduProcessing[id].Ab_RxSecuredPduType == (uint8)SECOC_TPPDU )
            {
                SecOC_Rx_ReceiveDivideFinish( id, result );
            }
    }

#endif
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_TpTxConfirmation                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | id     :                                                 */
/*               | result :                                                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_TpTxConfirmation
(
    PduIdType id,
    Std_ReturnType result
)
{
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))

    
    /* Parameters check */
    if((SecOC_If_udState == SECOC_INIT ) &&
      ( id < SecOC_TxPduProcessingMax ) )
    {
            if( SecOC_TxPduProcessing[id].Ab_TxSecuredPduType == (uint8)SECOC_TPPDU )
            {
                SecOC_Tx_DivideFinish( id, result );
            }
    }
#endif
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_TriggerTransmit                                    */
/* Description   |  Dummy Function                                          */
/* Preconditions |                                                          */
/* Parameters    | TxPduId    :                                             */
/*               | PduInfoPtr :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_TriggerTransmit
(
    PduIdType TxPduId,
    P2VAR(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) PduInfoPtr
)
{
    return E_NOT_OK;
}

/****************************************************************************/
/* Function Name | SecOC_CopyRxData                                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | id            :                                          */
/*               | info          :                                          */
/*               | bufferSizePtr :                                          */
/* Return Value  | BufReq_ReturnType                                        */
/*               |  BUFREQ_OK       : Success                               */
/*               |  BUFREQ_E_NOT_OK : Failure                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_CopyRxData
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) info,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) bufferSizePtr
)
{
    BufReq_ReturnType   ud_bufRet = BUFREQ_E_NOT_OK;
    
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    PduInfoType         st_divideData;
    boolean             b_copyDivideFlag = (boolean)FALSE;
    
    SecOCStd_MemClr( &st_divideData, sizeof(PduInfoType) );

    /* Parameters check */
    if( ( SecOC_If_udState == SECOC_INIT )
        && ( info != NULL_PTR )
        && ( bufferSizePtr != NULL_PTR ) )
    {
        if( ( info->SduDataPtr != NULL_PTR )
         && ( info->SduLength > (uint32)0U ) )
        {
            b_copyDivideFlag = (boolean)TRUE;
            st_divideData.SduDataPtr = info->SduDataPtr;
            st_divideData.SduLength = info->SduLength;
        }
        else if( info->SduLength == (uint32)0U )
        {
            b_copyDivideFlag = (boolean)TRUE;
            st_divideData.SduLength = info->SduLength;
        }
        else
        {
            /* No Processing */
        }
        
        if( b_copyDivideFlag == (boolean)TRUE )
        {
            
            if( id < SecOC_RxPduProcessingMax )
            {
                if( ( SecOC_RxPduProcessing[id].Ab_RxSecuredPduType == (uint8)SECOC_TPPDU )
                 && ( info->SduLength <= SecOC_RxPduProcessing[id].SameBufferPduRef ) )
                {
                    ud_bufRet = SecOC_Rx_CopyDivide(id, &st_divideData, bufferSizePtr );
                }
            }
        }
    }
#endif
    return ud_bufRet;
}

/****************************************************************************/
/* Function Name | SecOC_CopyTxData                                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | id               :                                       */
/*               | info             :                                       */
/*               | retry            :                                       */
/*               | availableDataPtr :                                       */
/* Return Value  | BufReq_ReturnType                                        */
/*               |  BUFREQ_OK       : Success                               */
/*               |  BUFREQ_E_NOT_OK : Failure                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_CopyTxData
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA) info,
    P2CONST(RetryInfoType, AUTOMATIC, SECOC_APPL_DATA) retry,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) availableDataPtr
)
{
    BufReq_ReturnType   ud_bufRet = BUFREQ_E_NOT_OK;
    
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))

    /* Parameters check */
    if( ( SecOC_If_udState == SECOC_INIT )
        && ( info != NULL_PTR )
        && ( availableDataPtr != NULL_PTR )
        && ( id < SecOC_TxPduProcessingMax ) )
    {
        if( ( info->SduDataPtr != NULL_PTR )
         || ( info->SduLength == (uint32)0U ) )
        {

            if( SecOC_TxPduProcessing[id].Ab_TxSecuredPduType == (uint8)SECOC_TPPDU )
            {
                ud_bufRet = SecOC_Tx_CopyDivide(id, info, availableDataPtr );
            }
        }
    }
#endif
    return ud_bufRet;
}

/****************************************************************************/
/* Function Name | SecOC_StartOfReception                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | id            :                                          */
/*               | info          :                                          */
/*               | TpSduLength   :                                          */
/*               | bufferSizePtr :                                          */
/* Return Value  | BufReq_ReturnType                                        */
/*               |  BUFREQ_OK       : Success                               */
/*               |  BUFREQ_E_NOT_OK : Failure                               */
/*               |  BUFREQ_E_OVFL   : Failure                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(BufReq_ReturnType, SECOC_CODE) SecOC_StartOfReception
(
    PduIdType id,
    P2CONST(PduInfoType, AUTOMATIC, SECOC_APPL_DATA)  info,
    PduLengthType TpSduLength,
    P2VAR(PduLengthType, AUTOMATIC, SECOC_APPL_DATA) bufferSizePtr
)
{
    BufReq_ReturnType   ud_bufRet = BUFREQ_E_NOT_OK;
    
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    PduInfoType         st_divideData;
    uint32              u4_totalMsgSize = 0U;
    uint32              u4_remainMsgSize;
    boolean             b_divideStartFlag = (boolean)FALSE;
    
    SecOCStd_MemClr( &st_divideData, sizeof(PduInfoType) );

    /* Parameters check */
    if( ( SecOC_If_udState == SECOC_INIT )
     && ( bufferSizePtr != NULL_PTR ) )
    {
        
        if( ( info == NULL_PTR )
         || ( info->SduLength == (uint32)0U ) )
        {
            b_divideStartFlag = (boolean)TRUE;
            st_divideData.SduLength = 0U;
        }
        else if( info->SduDataPtr != NULL_PTR )
        {
            b_divideStartFlag = (boolean)TRUE;
            st_divideData.SduDataPtr = info->SduDataPtr;
            st_divideData.SduLength = info->SduLength;
        }
        else
        {
            /* No Processing */
        }
        
        if( b_divideStartFlag == (boolean)TRUE )
        {
            /* PduId check */
            if( id < SecOC_RxPduProcessingMax )
            {
                if( SecOC_RxPduProcessing[id].Ab_RxSecuredPduType == (uint8)SECOC_TPPDU )
                {
                    if( TpSduLength == (uint32)0U )
                    {
                        u4_totalMsgSize = SecOC_RxPduProcessing[id].SameBufferPduRef;
                        ud_bufRet = BUFREQ_OK;
                    }
#if( SECOC_AB_FIXED_MESSAGE_SIZE == STD_ON )
                    else if( TpSduLength == SecOC_RxPduProcessing[id].SameBufferPduRef )
#else
                    else if( ( TpSduLength <= SecOC_RxPduProcessing[id].SameBufferPduRef )
                           && ( TpSduLength >= ( (uint32)SecOC_RxPduProcessing[id].Ab_TxSecurityDataSize + (uint32)SecOC_RxPduProcessing[id].Ab_ProtDataPaddingSize ) ) )
#endif
                    {
                        u4_totalMsgSize = (uint32)TpSduLength;
                        ud_bufRet = BUFREQ_OK;
                    }
                    else if( TpSduLength > SecOC_RxPduProcessing[id].SameBufferPduRef )
                    {
                        ud_bufRet = BUFREQ_E_OVFL;
                    }
                    else
                    {
                        ud_bufRet = BUFREQ_E_NOT_OK;
                    }
                    
                    if( ud_bufRet == (BufReq_ReturnType)BUFREQ_OK )
                    {
                        if( st_divideData.SduLength <= u4_totalMsgSize )
                        {
                            ud_bufRet = SecOC_Rx_ReceiveDivideStart( id, &st_divideData, (uint32)TpSduLength, &u4_remainMsgSize );
                            
                            if( ud_bufRet == (BufReq_ReturnType)BUFREQ_OK )
                            {
                                *bufferSizePtr = (PduLengthType)u4_remainMsgSize;
                            }
                        }
                        else
                        {
                            ud_bufRet = BUFREQ_E_OVFL;
                        }
                    }
                }
            }
        }
    }
#endif
    return ud_bufRet;
}

/****************************************************************************/
/* Function Name | SecOC_SendDefaultAuthenticationInformation               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | FreshnessValueID                     :                   */
/*               | sendDefaultAuthenticationInformation :                   */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_SendDefaultAuthenticationInformation
(
    uint16 FreshnessValueID,
    boolean sendDefaultAuthenticationInformation
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
#if(SECOC_DEFAULT_AUTH_INFO == STD_ON)
    /* Parameters check */
    if( SecOC_If_udState == SECOC_INIT )
    {
        ud_stdRet = SecOC_Tx_SetDefaultAuthInfo( FreshnessValueID, sendDefaultAuthenticationInformation );
    }
#endif
#endif
    
    return ud_stdRet;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_If_RxMain                                          */
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
static FUNC(uint16, SECOC_CODE) SecOC_If_RxMain
(
    uint16 u2Index
)
{
    uint16  u2_processResult = SECOC_RX_PROC_NONE;
    
    #if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    uint16  u2_txMessageNum;

    u2_txMessageNum = SecOC_Tx_GetMainProcMsgNum();
    if( SecOC_If_u2ProcessedMsgNum < (SecOC_Ab_ProcessingCount - u2_txMessageNum) )
    #else
    if( SecOC_If_u2ProcessedMsgNum < SecOC_Ab_ProcessingCount )
    #endif
    {
        SecOC_If_u2ProcessedMsgNum++;
        u2_processResult = SecOC_Rx_MainProcess( u2Index );
        
        if( u2_processResult == SECOC_RX_PROC_NONE )
        {
            SecOC_If_u2ProcessedMsgNum--;
        }
    }
    
    return u2_processResult;
}
#endif /* SECOC_RX_PDU_PROCESSING */

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_If_TxMain                                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_If_TxMain
(
    uint16 u2Index
)
{
    uint16  u2_processResult = SECOC_TX_PROC_NONE;
    
    if( SecOC_If_u2ProcessedMsgNum < SecOC_Ab_ProcessingCount )
    {
        SecOC_If_u2ProcessedMsgNum++;
        u2_processResult = SecOC_Tx_MainProcess( u2Index );
        
        if( u2_processResult == SECOC_TX_PROC_NONE )
        {
            SecOC_If_u2ProcessedMsgNum--;
        }
    }
    
    return ;
}
#endif /* SECOC_TX_PDU_PROCESSING */

#if (SECOC_AB_REPORT_ERROR_CALLOUT_MAX > 0U)
/****************************************************************************/
/* Function Name | SecOC_If_DetectErrorTx                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_If_DetectErrorTx
(
    void
)
{
    SecOC_ErrorStatusType   ud_errorStatus;
    
    /* SecOC error check */
    ud_errorStatus = SecOC_If_RamCheck();
    
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
    
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    /* Tx error check */
    if( ud_errorStatus == SECOC_E_NONE )
    {
        ud_errorStatus = SecOC_Tx_GetErrorStatus();
    }
    
    /* Buff error check */
    if( ud_errorStatus == SECOC_E_NONE )
    {
        ud_errorStatus = SecOC_Buff_GetErrorStatusTx();
    }
#endif
    
    /* FV error check */
    if( ud_errorStatus == SECOC_E_NONE )
    {
        ud_errorStatus = SecOC_CD_FV_GetErrorStatus();
    }
    
#endif /* SECOC_AB_RAM_ERROR_CHK */
    
    /* Notify error */
    if( ud_errorStatus != SECOC_E_NONE )
    {
        SecOC_If_NotifyError( ud_errorStatus );
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_If_DetectErrorRx                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_If_DetectErrorRx
(
    void
)
{
    SecOC_ErrorStatusType   ud_errorStatus;
    
    /* SecOC error check */
    ud_errorStatus = SecOC_If_RamCheck();
    
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
    
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    /* Rx error check */
    if( ud_errorStatus == SECOC_E_NONE )
    {
        ud_errorStatus = SecOC_Rx_GetErrorStatus();
    }
    
    /* Buff error check */
    if( ud_errorStatus == SECOC_E_NONE )
    {
        ud_errorStatus = SecOC_Buff_GetErrorStatusRx();
    }
#endif
    
    /* FV error check */
    if( ud_errorStatus == SECOC_E_NONE )
    {
        ud_errorStatus = SecOC_CD_FV_GetErrorStatus();
    }
    
#endif /* SECOC_AB_RAM_ERROR_CHK */

    /* Notify error */
    if( ud_errorStatus != SECOC_E_NONE )
    {
        SecOC_If_NotifyError( ud_errorStatus );
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_If_RamCheck                                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | SecOC_ErrorStatusType                                    */
/*               |  SECOC_E_NONE            : No Error                      */
/*               |  SECOC_E_NOT_INITIALIZED : UNINIT                        */
/*               |  SECOC_E_RAM_CHECK_FAIL  : RAM Error                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(SecOC_ErrorStatusType, SECOC_CODE) SecOC_If_RamCheck
(
    void
)
{
    SecOC_ErrorStatusType   ud_errorStatus;
    SecOC_StateType         ud_secocStateWork;
    
    /* RAM check */
    ud_secocStateWork = SecOC_If_udState;
    if( ud_secocStateWork == SECOC_INIT )
    {
        ud_errorStatus = SECOC_E_NONE;
    }
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
    else if( ud_secocStateWork == SECOC_UNINIT )
    {
        ud_errorStatus = SECOC_E_NOT_INITIALIZED;
    }
    else
    {
        ud_errorStatus = SECOC_E_RAM_CHECK_FAIL;
    }
#else
    else
    {
        ud_errorStatus = SECOC_E_NOT_INITIALIZED;
    }
#endif /* SECOC_AB_RAM_ERROR_CHK */
    return ud_errorStatus;
}

/****************************************************************************/
/* Function Name | SecOC_If_NotifyError                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | udErrorStatus :                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_If_NotifyError
(
    SecOC_ErrorStatusType  udErrorStatus
)
{
#if (SECOC_AB_REPORT_ERROR_CALLOUT_MAX > 0U)
    uint16  u2_loop;
    
    for( u2_loop = 0U; u2_loop < SecOC_Ab_RepErrCoMax; u2_loop++ )
    {
        if( SecOC_Ab_ReportErrorCallout[u2_loop] != NULL_PTR )
        {
            (void)SecOC_Ab_ReportErrorCallout[u2_loop]( udErrorStatus ); /* no return check required */
        }
    }
#endif
    return ;
}
#endif



#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/*  v2-1-0     :2023/04/14                                                  */
/*  v2-1-1     :2023/07/04                                                  */
/*  v2-1-2     :2023/11/15                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
