/* SecOC_CD_FV_If_c_v2-1-1                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC_CD_FV/If/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SecOC_CD_FV.h>
#include <SecOCStd_Util.h>

#if (SECOC_AB_BUS_TRUNC_MAX > 0U)
#include "../inc/SecOC_CD_FV_Trunc.h"
#endif

#if (SECOC_AB_BUS_FULL_MAX > 0U)
#include "../inc/SecOC_CD_FV_Full.h"
#endif

#include "../inc/SecOC_CD_FV_If.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define SECOC_CD_FV_INDEX_NONE      ((uint8)0x00U)
#define SECOC_CD_FV_INDEX_TRUNC     ((uint8)0x01U)
#define SECOC_CD_FV_INDEX_FULL      ((uint8)0x02U)
#define SECOC_CD_FV_INDEX_SYNC      ((uint8)0x03U)
#define SECOC_CD_FV_INDEX_TRIP      ((uint8)0x04U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CD_FV_CODE
#include <SecOC_MemMap.h>

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
static FUNC(uint8, SECOC_CD_FV_CODE) SecOC_CD_FV_RxSearchIndex
(
    uint16 u2FvId,
    P2VAR(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex
);
#endif
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
static FUNC(uint8, SECOC_CD_FV_CODE) SecOC_CD_FV_TxSearchIndex
(
    uint16 u2FvId,
    P2VAR(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex
);
#endif
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
static FUNC(SecOC_ErrorStatusType, SECOC_CD_FV_CODE) SecOC_CD_FV_RamCheck
(
    void
);
#endif /* SECOC_AB_RAM_ERROR_CHK */
#if (((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)) || \
    ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)))
static FUNC(void, SECOC_CODE) SecOC_CD_FV_NotifyFullFv
(
    uint16 u2FvId
);
#endif


#define SECOC_STOP_SEC_CD_FV_CODE
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CD_FV_VAR_NO_INIT
#include <SecOC_MemMap.h>
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
static VAR(uint16, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_u2RamChkCounter;
static VAR(uint16, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_u2RamChkMonitor;
static VAR(SecOC_ErrorStatusType, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_udRamChkResult;
#endif

#define SECOC_STOP_SEC_CD_FV_VAR_NO_INIT
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define SECOC_START_SEC_CD_FV_CODE
#include <SecOC_MemMap.h>

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Init                                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Init
(
    void
)
{
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
    SecOC_CD_FV_u2RamChkCounter = 0U;
    SecOC_CD_FV_u2RamChkMonitor  = 0U;
    SecOC_CD_FV_udRamChkResult   = SECOC_E_NONE;
#endif
    
#if (SECOC_AB_BUS_TRUNC_MAX > 0U)
    SecOC_CD_FV_Trunc_Init();
#endif
    
#if (SECOC_AB_BUS_FULL_MAX > 0U)
    SecOC_CD_FV_Full_Init();
#endif
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Read                                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2FvId  :                                                */
/*               | ptFv    :                                                */
/*               | ptFvLen :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK         : Success                                  */
/*               |  E_NOT_OK     : Failure                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Read
(
    uint16 u2FvId,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvLen
)
{
    Std_ReturnType          ud_stdRet = E_NOT_OK;
#if (((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)) || \
    ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)))
    uint8                   u1_searchResult;
    SecOC_CD_FV_IndexType   st_index;
    
    SecOCStd_MemClr( &st_index, sizeof(SecOC_CD_FV_IndexType) );
#endif
    
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    /* Rx FV search */
    u1_searchResult = SecOC_CD_FV_RxSearchIndex( u2FvId, &st_index );
    
    if( u1_searchResult == SECOC_CD_FV_INDEX_TRUNC )
    {
    #if (SECOC_AB_BUS_TRUNC_MAX > 0U)
        ud_stdRet = SecOC_CD_FV_Trunc_ReadRx( st_index.u2FvIndexLast, ptFv, ptFvLen );
    #endif
    }
    else if( u1_searchResult == SECOC_CD_FV_INDEX_FULL )
    {
    #if (SECOC_AB_BUS_FULL_MAX > 0U)
        ud_stdRet = SecOC_CD_FV_Full_ReadRx( st_index.u2FvIndexLast, ptFv, ptFvLen );
    #endif
    }
    else if( u1_searchResult == SECOC_CD_FV_INDEX_SYNC )
    {
    #if (SECOC_AB_BUS_TRUNC_MAX > 0U)
        ud_stdRet = SecOC_CD_FV_Trunc_ReadSync( st_index.u2FvIndexFvType, ptFv, ptFvLen );
    #endif
    }
    else
    {
        /* No Processing */
    }
#endif
    
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    #if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    if( u1_searchResult == SECOC_CD_FV_INDEX_NONE )
    {
    #endif
        /* Tx FV search */
        u1_searchResult = SecOC_CD_FV_TxSearchIndex( u2FvId, &st_index );
        
        if( u1_searchResult == SECOC_CD_FV_INDEX_TRUNC )
        {
    #if (SECOC_AB_BUS_TRUNC_MAX > 0U)
            ud_stdRet = SecOC_CD_FV_Trunc_ReadTx( st_index.u2FvIndexLast, ptFv, ptFvLen );
    #endif
        }
        else if( u1_searchResult == SECOC_CD_FV_INDEX_FULL )
        {
    #if (SECOC_AB_BUS_FULL_MAX > 0U)
            ud_stdRet = SecOC_CD_FV_Full_ReadTx( st_index.u2FvIndexLast, ptFv, ptFvLen );
    #endif
        }
        else if( u1_searchResult == SECOC_CD_FV_INDEX_SYNC )
        {
    #if (SECOC_AB_BUS_TRUNC_MAX > 0U)
            ud_stdRet = SecOC_CD_FV_Trunc_ReadSync( st_index.u2FvIndexFvType, ptFv, ptFvLen );
    #endif
        }
        else if( u1_searchResult == SECOC_CD_FV_INDEX_TRIP )
        {
    #if (SECOC_AB_BUS_FULL_MAX > 0U)
            ud_stdRet = SecOC_CD_FV_Full_ReadTrip( st_index.u2FvIndexFvType, ptFv, ptFvLen );
    #endif
        }
        else
        {
            /* No Processing */
        }
    #if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    }
    #endif
#endif
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Write                                        */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2FvId  :                                                */
/*               | ptFv    :                                                */
/*               | u4FvLen :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK         : Success                                  */
/*               |  E_NOT_OK     : Failure                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Write
(
    uint16 u2FvId,
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    uint32 u4FvLen
)
{
    Std_ReturnType          ud_stdRet = E_NOT_OK;
#if (((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)) || \
    ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)))
    uint8                   u1_searchResult;
    SecOC_CD_FV_IndexType   st_index;
    
    SecOCStd_MemClr( &st_index, sizeof(SecOC_CD_FV_IndexType) );
#endif
    
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    /* Rx FV search */
    u1_searchResult = SecOC_CD_FV_RxSearchIndex( u2FvId, &st_index );
    
    if( u1_searchResult == SECOC_CD_FV_INDEX_TRUNC )
    {
    #if (SECOC_AB_BUS_TRUNC_MAX > 0U)
        ud_stdRet = SecOC_CD_FV_Trunc_WriteRx( st_index.u2FvIndexLast, ptFv, u4FvLen );
    #endif
    }
    else if( u1_searchResult == SECOC_CD_FV_INDEX_FULL )
    {
    #if (SECOC_AB_BUS_FULL_MAX > 0U)
        ud_stdRet = SecOC_CD_FV_Full_WriteRx( st_index.u2FvIndexLast, ptFv, u4FvLen );
    #endif
    }
    else if( u1_searchResult == SECOC_CD_FV_INDEX_SYNC )
    {
    #if (SECOC_AB_BUS_TRUNC_MAX > 0U)
        ud_stdRet = SecOC_CD_FV_Trunc_WriteRxSync( st_index.u2FvIndexFvType, ptFv, u4FvLen );
    #endif
    }
    else
    {
        /* No Processing */
    }
#endif
    
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    #if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    if( u1_searchResult == SECOC_CD_FV_INDEX_NONE )
    {
    #endif
        /* Tx FV search */
        u1_searchResult = SecOC_CD_FV_TxSearchIndex( u2FvId, &st_index );
        
        if( u1_searchResult == SECOC_CD_FV_INDEX_TRUNC )
        {
    #if (SECOC_AB_BUS_TRUNC_MAX > 0U)
            ud_stdRet = SecOC_CD_FV_Trunc_WriteTx( st_index.u2FvIndexLast, ptFv, u4FvLen );
    #endif
        }
        else if( u1_searchResult == SECOC_CD_FV_INDEX_FULL )
        {
    #if (SECOC_AB_BUS_FULL_MAX > 0U)
            ud_stdRet = SecOC_CD_FV_Full_WriteTx( st_index.u2FvIndexLast, ptFv, u4FvLen );
    #endif
        }
        else if( u1_searchResult == SECOC_CD_FV_INDEX_SYNC )
        {
    #if (SECOC_AB_BUS_TRUNC_MAX > 0U)
            ud_stdRet = SecOC_CD_FV_Trunc_WriteTxSync( st_index.u2FvIndexFvType, ptFv, u4FvLen );
    #endif
        }
        else if( u1_searchResult == SECOC_CD_FV_INDEX_TRIP )
        {
    #if (SECOC_AB_BUS_FULL_MAX > 0U)
            ud_stdRet = SecOC_CD_FV_Full_WriteTrip( st_index.u2FvIndexFvType, ptFv, u4FvLen );
    #endif
        }
        else
        {
            /* No Processing */
        }
    #if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    }
    #endif
#endif
    
    return ud_stdRet;
}

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_GetRxFreshness                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | SecOCFreshnessValueID              :                     */
/*               | SecOCTruncatedFreshnessValue       :                     */
/*               | SecOCTruncatedFreshnessValueLength :                     */
/*               | SecOCAuthVerifyAttempts            :                     */
/*               | SecOCFreshnessValue                :                     */
/*               | SecOCFreshnessValueLength          :                     */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK               : Success                            */
/*               |  E_NOT_OK           : Failure(Skip)                      */
/*               |  SECOC_E_FV_NOT_OK  : FV NG                              */
/*               |  SECOC_E_RETRY      : Retry                              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_GetRxFreshness
(
    uint16 SecOCFreshnessValueID,
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) SecOCTruncatedFreshnessValue,
    uint32 SecOCTruncatedFreshnessValueLength,
    uint16 SecOCAuthVerifyAttempts,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) SecOCFreshnessValueLength
)
{
    Std_ReturnType          ud_stdRet = E_NOT_OK;
    SecOC_CD_FV_IndexType   st_index;
    SecOC_CD_FV_InType      st_truncFv;
    SecOC_CD_FV_InOutType   st_fullFv;
    uint8                   u1_searchResult;
    
    st_truncFv.ptFv = SecOCTruncatedFreshnessValue;
    st_truncFv.u4FvLen = SecOCTruncatedFreshnessValueLength;
    st_fullFv.ptFv = SecOCFreshnessValue;
    st_fullFv.ptFvLen = SecOCFreshnessValueLength;
    SecOCStd_MemClr( &st_index, sizeof(SecOC_CD_FV_IndexType) );
    
    /* Rx FV search */
    u1_searchResult = SecOC_CD_FV_RxSearchIndex( SecOCFreshnessValueID, &st_index );
    
    if( u1_searchResult == SECOC_CD_FV_INDEX_TRUNC )
    {
    #if (SECOC_AB_BUS_TRUNC_MAX > 0U)
        ud_stdRet = SecOC_CD_FV_Trunc_GetRx( &st_index, &st_truncFv, SecOCAuthVerifyAttempts, &st_fullFv );
    #endif
    }
    else if( u1_searchResult == SECOC_CD_FV_INDEX_FULL )
    {
    #if (SECOC_AB_BUS_FULL_MAX > 0U)
        ud_stdRet = SecOC_CD_FV_Full_GetRx( &st_index, &st_truncFv, SecOCAuthVerifyAttempts, &st_fullFv );
    #endif
    }
    else if( u1_searchResult == SECOC_CD_FV_INDEX_SYNC )
    {
    #if (SECOC_AB_BUS_TRUNC_MAX > 0U)
        ud_stdRet = SecOC_CD_FV_Trunc_GetRxSync( &st_index, &st_truncFv, SecOCAuthVerifyAttempts, &st_fullFv );
    #endif
    }
    else
    {
        /* No Processing */
    }
    
    return ud_stdRet;
}
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_GetTxFreshnessTruncData                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | SecOCFreshnessValueID              :                     */
/*               | SecOCFreshnessValue                :                     */
/*               | SecOCFreshnessValueLength          :                     */
/*               | SecOCTruncatedFreshnessValue       :                     */
/*               | SecOCTruncatedFreshnessValueLength :                     */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK               : Success                            */
/*               |  E_NOT_OK           : Failure(Skip)                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_GetTxFreshnessTruncData
(
    uint16 SecOCFreshnessValueID,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) SecOCFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) SecOCFreshnessValueLength,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) SecOCTruncatedFreshnessValue,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) SecOCTruncatedFreshnessValueLength
)
{
    Std_ReturnType          ud_stdRet = E_NOT_OK;
    SecOC_CD_FV_IndexType   st_index;
    SecOC_CD_FV_InOutType   st_fullFv;
    SecOC_CD_FV_InOutType   st_truncFv;
    uint8                   u1_searchResult;
    
    st_fullFv.ptFv = SecOCFreshnessValue;
    st_fullFv.ptFvLen = SecOCFreshnessValueLength;
    st_truncFv.ptFv = SecOCTruncatedFreshnessValue;
    st_truncFv.ptFvLen = SecOCTruncatedFreshnessValueLength;
    SecOCStd_MemClr( &st_index, sizeof(SecOC_CD_FV_IndexType) );
    
    /* Tx FV search */
    u1_searchResult = SecOC_CD_FV_TxSearchIndex( SecOCFreshnessValueID, &st_index );
    
    if( u1_searchResult == SECOC_CD_FV_INDEX_TRUNC )
    {
    #if (SECOC_AB_BUS_TRUNC_MAX > 0U)
        ud_stdRet = SecOC_CD_FV_Trunc_GetTx( &st_index, &st_fullFv, &st_truncFv );
    #endif
    }
    else if( u1_searchResult == SECOC_CD_FV_INDEX_FULL )
    {
    #if (SECOC_AB_BUS_FULL_MAX > 0U)
        ud_stdRet = SecOC_CD_FV_Full_GetTx( &st_index, &st_fullFv, &st_truncFv );
    #endif
    }
    else if( u1_searchResult == SECOC_CD_FV_INDEX_SYNC )
    {
    #if (SECOC_AB_BUS_TRUNC_MAX > 0U)
        ud_stdRet = SecOC_CD_FV_Trunc_GetTxSync( &st_index, &st_fullFv, &st_truncFv );
    #endif
    }
    else
    {
        /* No Processing */
    }
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_CD_FV_SPduTxConfirmation                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | SecOCFreshnessValueID :                                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_SPduTxConfirmation
(
    uint16 SecOCFreshnessValueID
)
{
    SecOC_CD_FV_IndexType   st_index;
    uint8                   u1_searchResult;
    Std_ReturnType ud_stdRet = (Std_ReturnType)E_OK;
    
    SecOCStd_MemClr( &st_index, sizeof(SecOC_CD_FV_IndexType) );

    /* Tx FV search */
    u1_searchResult = SecOC_CD_FV_TxSearchIndex( SecOCFreshnessValueID, &st_index );
    
    if( u1_searchResult == SECOC_CD_FV_INDEX_TRUNC )
    {
    #if (SECOC_AB_BUS_TRUNC_MAX > 0U)
        ud_stdRet = SecOC_CD_FV_Trunc_UpdateTx( st_index.u2FvIndexLast, (boolean)TRUE );
    #endif
    }
    else if( u1_searchResult == SECOC_CD_FV_INDEX_FULL )
    {
    #if (SECOC_AB_BUS_FULL_MAX > 0U)
        ud_stdRet = SecOC_CD_FV_Full_UpdateTx( st_index.u2FvIndexLast, (boolean)TRUE );
    #endif
    }
    else
    {
        /* No Processing */
    }
    
    if( ud_stdRet == SECOC_E_OK_FV_FULL )
    {
        SecOC_CD_FV_NotifyFullFv( SecOCFreshnessValueID );
    }
    
    return ;
}
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_VerifyResult                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | stVerResult :                                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_VerifyResult
(
    SecOC_VerificationStatusType stVerResult
)
{
    SecOC_CD_FV_IndexType   st_index;
    uint8                   u1_searchResult;
    boolean                 b_update = (boolean)FALSE;
    Std_ReturnType ud_stdRet = (Std_ReturnType)E_OK;
    
    SecOCStd_MemClr( &st_index, sizeof(SecOC_CD_FV_IndexType) );

    if( stVerResult.verificationStatus == SECOC_VERIFICATIONSUCCESS )
    {
        b_update = (boolean)TRUE;
    }
    
    /* Rx FV search */
    u1_searchResult = SecOC_CD_FV_RxSearchIndex( stVerResult.freshnessValueID, &st_index );
    
    if( u1_searchResult == SECOC_CD_FV_INDEX_TRUNC )
    {
    #if (SECOC_AB_BUS_TRUNC_MAX > 0U)
        ud_stdRet = SecOC_CD_FV_Trunc_UpdateRx( st_index.u2FvIndexLast, b_update );
    #endif
    }
    else if( u1_searchResult == SECOC_CD_FV_INDEX_FULL )
    {
    #if (SECOC_AB_BUS_FULL_MAX > 0U)
        ud_stdRet = SecOC_CD_FV_Full_UpdateRx( st_index.u2FvIndexLast, b_update );
    #endif
    }
    else if( u1_searchResult == SECOC_CD_FV_INDEX_SYNC )
    {
    #if (SECOC_AB_BUS_TRUNC_MAX > 0U)
        SecOC_CD_FV_Trunc_UpdateSync( st_index.u2FvIndexFvType, b_update );
    #endif
    }
    else
    {
        /* No Processing */
    }
    
    if( b_update == (boolean)TRUE )
    {
        if( ud_stdRet == SECOC_E_OK_FV_FULL )
        {
            SecOC_CD_FV_NotifyFullFv( stVerResult.freshnessValueID );
        }
    }
    
    return ;
}
#endif

/****************************************************************************/
/* Function Name | SecOC_CD_FV_ResetBus                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BusId :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK               : Success                            */
/*               |  E_NOT_OK           : Failure                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_ResetBus
(
    uint16 u2BusId
)
{
    Std_ReturnType          ud_stdRet = E_NOT_OK;
#if ((SECOC_AB_BUS_TRUNC_MAX > 0U)||(SECOC_AB_BUS_FULL_MAX > 0U))
    uint16 u2_busIndex;

    u2_busIndex = u2BusId;  /* Config constraint "BusID==BusIndex" is the premise */
#endif
    
#if (SECOC_AB_BUS_TRUNC_MAX > 0U)
    if( SecOC_Ab_BusCollection[u2_busIndex].Ab_FvType == (uint8)SECOC_AB_FV_TRUNC )
    {
        SecOC_CD_FV_Trunc_ResetBus( u2_busIndex, SecOC_Ab_BusCollection[u2_busIndex].Ab_FvTypeIndex );
        ud_stdRet = E_OK;
    }
    else
#endif
#if (SECOC_AB_BUS_FULL_MAX > 0U)
    if( SecOC_Ab_BusCollection[u2_busIndex].Ab_FvType == (uint8)SECOC_AB_FV_FULL )
    {
        SecOC_CD_FV_Full_ResetBus( u2_busIndex, SecOC_Ab_BusCollection[u2_busIndex].Ab_FvTypeIndex );
        ud_stdRet = E_OK;
    }
    else
#endif
    {
        /* No Processing */
    }
    
    return ud_stdRet;
}

#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_CD_FV_GetErrorStatus                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | SecOC_ErrorStatusType                                    */
/*               |  SECOC_E_NONE           : No Error                       */
/*               |  SECOC_E_RAM_CHECK_FAIL : RAM Error                      */
/*               |  SECOC_E_FV_CHECK_FAIL  : FV Error                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(SecOC_ErrorStatusType, SECOC_CD_FV_CODE) SecOC_CD_FV_GetErrorStatus
(
    void
)
{
    SecOC_ErrorStatusType ud_errStatus;
    
    if( SecOC_CD_FV_u2RamChkCounter >= SecOC_Ab_BusMax)
    {
        SecOC_CD_FV_u2RamChkCounter = 0U;
    }
    
    ud_errStatus = SecOC_CD_FV_RamCheck();
    
    if( ud_errStatus != SECOC_E_NONE)
    {
        SecOC_CD_FV_u2RamChkMonitor = SecOC_Ab_BusMax;
        SecOC_CD_FV_udRamChkResult  = ud_errStatus;
    }
    
    if( SecOC_CD_FV_u2RamChkMonitor > (uint16)0U)
    {
        ud_errStatus = SecOC_CD_FV_udRamChkResult;
        SecOC_CD_FV_u2RamChkMonitor--;
    }
    
    SecOC_CD_FV_u2RamChkCounter++;
    
    return ud_errStatus;
}
#endif /* SECOC_AB_RAM_ERROR_CHK */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_RxSearchIndex                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2FvId  :                                                */
/*               | ptIndex :                                                */
/* Return Value  | uint8                                                    */
/*               |  SECOC_CD_FV_INDEX_NONE                                  */
/*               |  SECOC_CD_FV_INDEX_TRUNC                                 */
/*               |  SECOC_CD_FV_INDEX_FULL                                  */
/*               |  SECOC_CD_FV_INDEX_SYNC                                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(uint8, SECOC_CD_FV_CODE) SecOC_CD_FV_RxSearchIndex
(
    uint16 u2FvId,
    P2VAR(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex
)
{
    uint8                   u1_ret = SECOC_CD_FV_INDEX_NONE;
    uint16                  u2_index;
    uint16                  u2_pduIndex;
#if (SECOC_AB_BUS_TRUNC_MAX > 0U)
    uint16                  u2_truncFvIndex = 0U;
#endif
#if (SECOC_AB_BUS_FULL_MAX > 0U)
    uint16                  u2_fullFvIndex = 0U;
#endif
    
    /* Rx FV search */
    for( u2_index = 0U; u2_index < SecOC_RxPduProcessingMax; u2_index++ )
    {
        u2_pduIndex = SecOC_RxPduProcessing[u2_index].Ab_BusIndex;
#if (SECOC_AB_BUS_TRUNC_MAX > 0U)
        if( SecOC_Ab_BusCollection[u2_pduIndex].Ab_FvType == (uint8)SECOC_AB_FV_TRUNC )
        {
            if( u2FvId == SecOC_RxPduProcessing[u2_index].FreshnessValueId )
            {
                ptIndex->u2BusIndex      = u2_pduIndex;
                ptIndex->u2FvIndexFvType = SecOC_Ab_BusCollection[u2_pduIndex].Ab_FvTypeIndex;
                
                if( SecOC_RxPduProcessing[u2_index].Ab_MessageType == (uint8)SECOC_AB_MSGTYPE_SYNC )
                {
                    ptIndex->u2FvIndexLast = 0U;
                    u1_ret = SECOC_CD_FV_INDEX_SYNC;
                }
                else
                {
                    ptIndex->u2FvIndexLast = u2_truncFvIndex;
                    u1_ret = SECOC_CD_FV_INDEX_TRUNC;
                }
            }
            
            if( SecOC_RxPduProcessing[u2_index].Ab_MessageType != (uint8)SECOC_AB_MSGTYPE_SYNC )
            {
                u2_truncFvIndex++;
            }
        }
#endif
#if (SECOC_AB_BUS_FULL_MAX > 0U)
        if( SecOC_Ab_BusCollection[u2_pduIndex].Ab_FvType == (uint8)SECOC_AB_FV_FULL )
        {
            if( u2FvId == SecOC_RxPduProcessing[u2_index].FreshnessValueId )
            {
                ptIndex->u2BusIndex      = u2_pduIndex;
                ptIndex->u2FvIndexFvType = SecOC_Ab_BusCollection[u2_pduIndex].Ab_FvTypeIndex;
                ptIndex->u2FvIndexLast   = u2_fullFvIndex;
                u1_ret = SECOC_CD_FV_INDEX_FULL;
            }
            u2_fullFvIndex++;
        }
#endif
        if( u1_ret != SECOC_CD_FV_INDEX_NONE )
        {
            break;
        }
    }
    
    return u1_ret;
}
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_TxSearchIndex                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2FvId  :                                                */
/*               | ptIndex :                                                */
/* Return Value  | uint8                                                    */
/*               |  SECOC_CD_FV_INDEX_NONE                                  */
/*               |  SECOC_CD_FV_INDEX_TRUNC                                 */
/*               |  SECOC_CD_FV_INDEX_FULL                                  */
/*               |  SECOC_CD_FV_INDEX_TRIP                                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(uint8, SECOC_CD_FV_CODE) SecOC_CD_FV_TxSearchIndex
(
    uint16 u2FvId,
    P2VAR(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex
)
{
    uint8                   u1_ret = SECOC_CD_FV_INDEX_NONE;
    uint16                  u2_index;
    uint16                  u2_pduIndex;
#if (SECOC_AB_BUS_TRUNC_MAX > 0U)
    uint16                  u2_truncFvIndex = 0U;
#endif
#if (SECOC_AB_BUS_FULL_MAX > 0U)
    uint16                  u2_fullFvIndex = 0U;
#endif

    /* Tx FV search */
    for( u2_index = 0U; u2_index < SecOC_TxPduProcessingMax; u2_index++ )
    {
        u2_pduIndex = SecOC_TxPduProcessing[u2_index].Ab_BusIndex;
#if (SECOC_AB_BUS_TRUNC_MAX > 0U)
        if( SecOC_Ab_BusCollection[u2_pduIndex].Ab_FvType == (uint8)SECOC_AB_FV_TRUNC )
        {
            if( u2FvId == SecOC_TxPduProcessing[u2_index].FreshnessValueId )
            {
                ptIndex->u2BusIndex      = u2_pduIndex;
                ptIndex->u2FvIndexFvType = SecOC_Ab_BusCollection[u2_pduIndex].Ab_FvTypeIndex;
                
                if( SecOC_TxPduProcessing[u2_index].Ab_MessageType == (uint8)SECOC_AB_MSGTYPE_SYNC )
                {
                    ptIndex->u2FvIndexLast = 0U;
                    u1_ret = SECOC_CD_FV_INDEX_SYNC;
                }
                else
                {
                    ptIndex->u2FvIndexLast = u2_truncFvIndex;
                    u1_ret = SECOC_CD_FV_INDEX_TRUNC;
                }
            }
            
            if( SecOC_TxPduProcessing[u2_index].Ab_MessageType != (uint8)SECOC_AB_MSGTYPE_SYNC )
            {
                u2_truncFvIndex++;
            }
        }
#endif
#if (SECOC_AB_BUS_FULL_MAX > 0U)
        if( SecOC_Ab_BusCollection[u2_pduIndex].Ab_FvType == (uint8)SECOC_AB_FV_FULL )
        {
            if( u2FvId == SecOC_TxPduProcessing[u2_index].FreshnessValueId )
            {
                ptIndex->u2BusIndex      = u2_pduIndex;
                ptIndex->u2FvIndexFvType = SecOC_Ab_BusCollection[u2_pduIndex].Ab_FvTypeIndex;
                ptIndex->u2FvIndexLast   = u2_fullFvIndex;
                u1_ret = SECOC_CD_FV_INDEX_FULL;
            }
            else if( u2FvId == SecOC_Ab_BusCollection[u2_pduIndex].Ab_FreshnessValueID )
            {
                ptIndex->u2BusIndex      = u2_pduIndex;
                ptIndex->u2FvIndexFvType = SecOC_Ab_BusCollection[u2_pduIndex].Ab_FvTypeIndex;
                ptIndex->u2FvIndexLast   = 0U;
                u1_ret = SECOC_CD_FV_INDEX_TRIP;
            }
            else
            {
                /* No Processing */
            }
            u2_fullFvIndex++;
        }
#endif
        if( u1_ret != SECOC_CD_FV_INDEX_NONE )
        {
            break;
        }
    }
    
    return u1_ret;
}
#endif /* (SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U) */

#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_CD_FV_RamCheck                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | SecOC_ErrorStatusType                                    */
/*               |  SECOC_E_NONE           : No Error                       */
/*               |  SECOC_E_RAM_CHECK_FAIL : RAM Error                      */
/*               |  SECOC_E_FV_CHECK_FAIL  : FV Error                       */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(SecOC_ErrorStatusType, SECOC_CD_FV_CODE) SecOC_CD_FV_RamCheck
(
    void
)
{
    SecOC_ErrorStatusType   ud_errStatus = SECOC_E_NONE;
#if ((SECOC_AB_BUS_TRUNC_MAX > 0U) || (SECOC_AB_BUS_FULL_MAX > 0U))
    uint16                  u2_busIndex;
    
    u2_busIndex = SecOC_CD_FV_u2RamChkCounter;
#endif
    
#if (SECOC_AB_BUS_TRUNC_MAX > 0U)
    if( u2_busIndex < SecOC_Ab_BusTruncMax )
    {
        /* CANBus Ram Check */
        ud_errStatus = SecOC_CD_FV_Trunc_GetErrorStatus( u2_busIndex );
    }
    else
    {
        /* No Processing */
  #if (SECOC_AB_BUS_FULL_MAX > 0U)
        /* EtherBus Ram Check */
        u2_busIndex -= SecOC_Ab_BusTruncMax;
        if( u2_busIndex < SecOC_Ab_BusFullMax )
        {
            ud_errStatus = SecOC_CD_FV_Full_GetErrorStatus( u2_busIndex );
        }
  #endif
    }
#else
  #if (SECOC_AB_BUS_FULL_MAX > 0U)
    /* EtherBus Ram Check */
    if( u2_busIndex < SecOC_Ab_BusFullMax )
    {
        ud_errStatus = SecOC_CD_FV_Full_GetErrorStatus( u2_busIndex );
    }
  #endif
#endif
    
    return ud_errStatus;
}
#endif /* SECOC_AB_RAM_ERROR_CHK */

#if (((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)) || \
    ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_NotifyFullFv                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2FvId :                                                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CODE) SecOC_CD_FV_NotifyFullFv
(
    uint16 u2FvId
)
{
#if (SECOC_AB_FULL_FRESHNESS_VALUE_CALLOUT_MAX > 0U)
    uint16  u2_loop;
    
    for( u2_loop = 0U; u2_loop < SecOC_Ab_FullFvCoMax; u2_loop++ )
    {
        if( SecOC_Ab_FullFVCallout[u2_loop] != NULL_PTR )
        {
            SecOC_Ab_FullFVCallout[u2_loop]( u2FvId );
        }
    }
#endif
    
    return ;
}
#endif

#define SECOC_STOP_SEC_CD_FV_CODE
#include <SecOC_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/*  v2-1-0     :2023/09/29                                                  */
/*  v2-1-1     :2023/11/20                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
