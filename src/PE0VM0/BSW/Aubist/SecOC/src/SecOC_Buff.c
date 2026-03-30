/* SecOC_Buff_c_v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC/Buff/CODE                                            */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SchM_SecOC.h>
#include <SecOCStd_String.h>
#include <SecOCStd_Util.h>
#include "../inc/SecOC_Buff.h"

#if ( ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)) \
    || ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)) )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define SECOC_BUFF_END_INDEX        ((uint16)0xFFFFU)   /* End of Index */

/* Buff flag */
#define SECOC_BUFF_FLAG_FALSE       ((uint8)0x5AU)
#define SECOC_BUFF_FLAG_TRUE        ((uint8)0xA5U)

#define SECOC_BUFF_UINT32_MAX_VALUE ((uint32)0xFFFFFFFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Buffer control structure */
typedef struct {
    uint32  u4UseSize;
    uint16  u2NextIndex;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
    uint16  u2NextIndexRedundant;
#else
    uint16  u2Reserve;
#endif
} SecOC_Buff_CtrlType;

/* Buffer infomation */
typedef struct {
    P2VAR(SecOC_Buff_CtrlType, AUTOMATIC, SECOC_APPL_DATA) ptCtrlInfo;
    P2VAR(uint16, AUTOMATIC, SECOC_APPL_DATA) ptTopMsgIndex;
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptBuffTop;
    uint16  u2MaxIndexNum;
    uint16  u2Reserve;
} SecOC_Buff_InfoType;

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/* Tx Buffer */
typedef struct {
    uint32  u4DummyForAlignment;
    uint8   u1TxBuffer[SECOC_TX_BUFFER_LENGTH_TOTAL]; /* u1TxBuffer should be 4byte aligned */
} SecOC_Buff_TxBufferType;
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/* Rx Buffer */
typedef struct {
    uint32  u4DummyForAlignment;
    uint8   u1RxBuffer[SECOC_RX_BUFFER_LENGTH_TOTAL]; /* u1RxBuffer should be 4byte aligned */
} SecOC_Buff_RxBufferType;
#endif

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_GetInfo
(
    uint16 u2BuffKind,
    P2VAR(SecOC_Buff_InfoType, AUTOMATIC, SECOC_APPL_DATA) ptInfo
);
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_GetMsgConfig
(
    uint16 u2BuffKind,
    uint16 u2Index,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptMsgMaxSize,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptBufferStartOffset
);
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_GetTopIndex
(
    uint16 u2BuffKind,
    P2VAR(uint16, AUTOMATIC, SECOC_APPL_DATA) ptTopIndex
);
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_SetTopIndex
(
    uint16 u2BuffKind,
    uint16 u2TopIndex
);

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_VAR_NO_INIT
#include <SecOC_MemMap.h>

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
static VAR(SecOC_Buff_CtrlType, SECOC_VAR_NO_INIT) SecOC_Buff_stTxCtrlInfo[SECOC_TX_PDU_PROCESSING_MAX];
static VAR(SecOC_Buff_TxBufferType, SECOC_VAR_NO_INIT) SecOC_Buff_stTxBuffer;
static VAR(uint16, SECOC_VAR_NO_INIT) SecOC_Buff_u2TxTopIndex;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
static VAR(uint16, SECOC_VAR_NO_INIT) SecOC_Buff_u2TxTopIndexRedundant;
#endif
static VAR(uint32, SECOC_VAR_NO_INIT) SecOC_Buff_u4TxDivideTotalSize[SECOC_TX_PDU_PROCESSING_MAX];
static VAR(uint32, SECOC_VAR_NO_INIT) SecOC_Buff_u4TxDivideCopyPos[SECOC_TX_PDU_PROCESSING_MAX];
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
static VAR(SecOC_Buff_CtrlType, SECOC_VAR_NO_INIT) SecOC_Buff_stRxCtrlInfo[SECOC_RX_PDU_PROCESSING_MAX];
static VAR(SecOC_Buff_RxBufferType, SECOC_VAR_NO_INIT) SecOC_Buff_stRxBuffer;
static VAR(uint16, SECOC_VAR_NO_INIT) SecOC_Buff_u2RxTopIndex;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
static VAR(uint16, SECOC_VAR_NO_INIT) SecOC_Buff_u2RxTopIndexRedundant;
#endif
static VAR(uint32, SECOC_VAR_NO_INIT) SecOC_Buff_u4RxDivideTotalSize[SECOC_RX_PDU_PROCESSING_MAX];
static VAR(uint32, SECOC_VAR_NO_INIT) SecOC_Buff_u4RxDivideCopyPos[SECOC_RX_PDU_PROCESSING_MAX];
#endif
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
static VAR(uint8, SECOC_VAR_NO_INIT) SecOC_Buff_u1RamCheckFailFlag;
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
/* Function Name | SecOC_Buff_Init                                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Buff_Init
(
    void
)
{
    uint16  u2_loop;
    
    SecOC_Buff_Reset();
    
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    SecOC_Buff_u2TxTopIndex = SECOC_BUFF_END_INDEX;
    for( u2_loop = 0U; u2_loop < SecOC_TxPduProcessingMax; u2_loop++ )
    {
        SecOC_Buff_stTxCtrlInfo[u2_loop].u2NextIndex = SECOC_BUFF_END_INDEX;
    }
#endif
    
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    SecOC_Buff_u2RxTopIndex = SECOC_BUFF_END_INDEX;
    for( u2_loop = 0U; u2_loop < SecOC_RxPduProcessingMax; u2_loop++ )
    {
        SecOC_Buff_stRxCtrlInfo[u2_loop].u2NextIndex = SECOC_BUFF_END_INDEX;
    }
#endif
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
    SecOC_Buff_u1RamCheckFailFlag = SECOC_BUFF_FLAG_FALSE;
#endif
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Buff_Reset                                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CODE) SecOC_Buff_Reset
(
    void
)
{
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    SecOC_Buff_u2TxTopIndex = 0U;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
    SecOC_Buff_u2TxTopIndexRedundant = 0U;
#endif
    SecOCStd_MemClr( &SecOC_Buff_u4TxDivideCopyPos[0], sizeof(SecOC_Buff_u4TxDivideCopyPos) );
    SecOCStd_MemClr( &SecOC_Buff_u4TxDivideTotalSize[0], sizeof(SecOC_Buff_u4TxDivideTotalSize) );
    SecOCStd_MemClr( &SecOC_Buff_stTxCtrlInfo[0], sizeof(SecOC_Buff_stTxCtrlInfo) );
    SecOCStd_MemClr( &SecOC_Buff_stTxBuffer, sizeof(SecOC_Buff_TxBufferType) );
#endif
    
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    SecOC_Buff_u2RxTopIndex = 0U;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
    SecOC_Buff_u2RxTopIndexRedundant = 0U;
#endif
    SecOCStd_MemClr( &SecOC_Buff_u4RxDivideCopyPos[0], sizeof(SecOC_Buff_u4RxDivideCopyPos) );
    SecOCStd_MemClr( &SecOC_Buff_u4RxDivideTotalSize[0], sizeof(SecOC_Buff_u4RxDivideTotalSize) );
    SecOCStd_MemClr( &SecOC_Buff_stRxCtrlInfo[0], sizeof(SecOC_Buff_stRxCtrlInfo) );
    SecOCStd_MemClr( &SecOC_Buff_stRxBuffer, sizeof(SecOC_Buff_RxBufferType) );
#endif
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
    SecOC_Buff_u1RamCheckFailFlag = 0U;
#endif
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_Buff_GetOrder                                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BuffKind :                                             */
/*               | u2OrderNo  :                                             */
/*               | ptIndex    :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_GetOrder
(
    uint16 u2BuffKind,
    uint16 u2OrderNo,
    P2VAR(uint16, AUTOMATIC, SECOC_APPL_DATA) ptIndex
)
{
    SecOC_Buff_InfoType st_info;
    Std_ReturnType      ud_stdRet = E_NOT_OK;
    Std_ReturnType      ud_getInfoRet;
    uint16              u2_current;
    uint16              u2_loop;
    
    ud_getInfoRet = SecOC_Buff_GetInfo( u2BuffKind, &st_info );
    
    /* Parameters check */
    if( (ud_getInfoRet == (Std_ReturnType)E_OK)
        && (ptIndex != NULL_PTR)
        && (u2OrderNo < st_info.u2MaxIndexNum)
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        && (SecOC_Buff_u1RamCheckFailFlag == SECOC_BUFF_FLAG_FALSE) 
#endif
      )
    {
        SchM_Enter_SecOC_Buff();
        
        /* Search index */
        u2_current = *st_info.ptTopMsgIndex;
        for( u2_loop = 0U; u2_loop < u2OrderNo; u2_loop++ )
        {
            if( u2_current < st_info.u2MaxIndexNum )
            {
                u2_current = st_info.ptCtrlInfo[u2_current].u2NextIndex;
            }
            else
            {
                break;
            }
        }
        
        if( (u2_loop == u2OrderNo)
          && (u2_current < st_info.u2MaxIndexNum) )
        {
            *ptIndex = u2_current;
            ud_stdRet = E_OK;
        }
        
        SchM_Exit_SecOC_Buff();
    }
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Buff_SetOrder                                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BuffKind :                                             */
/*               | u2Index    :                                             */
/*               | ptSetData  :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_SetOrder
(
    uint16 u2BuffKind,
    uint16 u2Index,
    P2CONST(SecOC_Buff_DataType, AUTOMATIC, SECOC_APPL_DATA) ptSetData
)
{
    SecOC_Buff_InfoType st_info;
    Std_ReturnType      ud_stdRet = E_NOT_OK;
    Std_ReturnType      ud_getInfoRet;
    Std_ReturnType      ud_getConfigRet;
    uint32              u4_bufferStartOffset;
    uint32              u4_msgMaxSize;
    uint16              u2_current;
    uint16              u2_next;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
    Std_ReturnType      ud_topIndexRet;
    uint16              u2_redundant;
#endif
    uint8               u1_loopFlag;
    
    ud_getInfoRet = SecOC_Buff_GetInfo( u2BuffKind, &st_info );
    ud_getConfigRet = SecOC_Buff_GetMsgConfig( u2BuffKind, u2Index, &u4_msgMaxSize, &u4_bufferStartOffset );
    
    /* Parameters check */
    if( (ud_getInfoRet == (Std_ReturnType)E_OK)
      && (ud_getConfigRet == (Std_ReturnType)E_OK)
      && (ptSetData != NULL_PTR)
      && (ptSetData->u4Size <= u4_msgMaxSize) )
    {
        (void)SecOCStd_MemCpy( &st_info.ptBuffTop[u4_bufferStartOffset], ptSetData->ptData, ptSetData->u4Size ); /* no return check required */
        st_info.ptCtrlInfo[u2Index].u4UseSize = ptSetData->u4Size;
        st_info.ptCtrlInfo[u2Index].u2NextIndex = SECOC_BUFF_END_INDEX;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        st_info.ptCtrlInfo[u2Index].u2NextIndexRedundant = (uint16)(~SECOC_BUFF_END_INDEX);
#endif
        
        SchM_Enter_SecOC_Buff();
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        ud_topIndexRet = SecOC_Buff_GetTopIndex( u2BuffKind, &u2_current );
        
        if( ud_topIndexRet == (Std_ReturnType)E_OK )
#else
        (void)SecOC_Buff_GetTopIndex( u2BuffKind, &u2_current ); /* no return check required */
#endif
        {
            if( u2_current == SECOC_BUFF_END_INDEX )
            {
                ud_stdRet = SecOC_Buff_SetTopIndex( u2BuffKind, u2Index );
            }
            else if( u2_current < st_info.u2MaxIndexNum )
            {
                /* Last index search */
                u1_loopFlag = SECOC_BUFF_FLAG_TRUE;
                while( u1_loopFlag == SECOC_BUFF_FLAG_TRUE )
                {
                    u2_next = st_info.ptCtrlInfo[u2_current].u2NextIndex;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
                    u2_redundant = (uint16)(~st_info.ptCtrlInfo[u2_current].u2NextIndexRedundant);
                    if( u2_next == u2_redundant )
                    {
#endif
                        if( u2_next < st_info.u2MaxIndexNum )
                        {
                            u2_current = u2_next;
                        }
                        else
                        {
                            st_info.ptCtrlInfo[u2_current].u2NextIndex = u2Index;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
                            st_info.ptCtrlInfo[u2_current].u2NextIndexRedundant = (uint16)(~u2Index);
#endif
                            ud_stdRet = E_OK;
                            u1_loopFlag = SECOC_BUFF_FLAG_FALSE;
                        }
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
                    }
                    else
                    {
                        /* error */
                        SecOC_Buff_u1RamCheckFailFlag = SECOC_BUFF_FLAG_TRUE;
                        u1_loopFlag = SECOC_BUFF_FLAG_FALSE;
                    }
#endif
                }
            }
            else
            {
                st_info.ptCtrlInfo[u2Index].u4UseSize = 0U;
            }
        }
        
        SchM_Exit_SecOC_Buff();
    }
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Buff_SetSelect                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BuffKind :                                             */
/*               | u2Index    :                                             */
/*               | u2SetPos   :                                             */
/*               | ptSetData  :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_SetSelect
(
    uint16 u2BuffKind,
    uint16 u2Index,
    uint32 u4SetPos,
    P2VAR(SecOC_Buff_DataType, AUTOMATIC, SECOC_APPL_DATA) ptSetData
)
{
    SecOC_Buff_InfoType st_info;
    Std_ReturnType      ud_stdRet = E_NOT_OK;
    Std_ReturnType      ud_getInfoRet;
    Std_ReturnType      ud_getConfigRet;
    uint32              u4_bufferStartOffset;
    uint32              u4_msgMaxSize;
    uint32              u4_useSize;
    
    ud_getInfoRet = SecOC_Buff_GetInfo( u2BuffKind, &st_info );
    ud_getConfigRet = SecOC_Buff_GetMsgConfig( u2BuffKind, u2Index, &u4_msgMaxSize, &u4_bufferStartOffset );
    
    /* Parameters check */
    if( (ud_getInfoRet == (Std_ReturnType)E_OK)
      && (ud_getConfigRet == (Std_ReturnType)E_OK)
      && (ptSetData != NULL_PTR)
      && ((SECOC_BUFF_UINT32_MAX_VALUE - ptSetData->u4Size) >= u4SetPos) )
    {
        u4_useSize = u4SetPos + ptSetData->u4Size;
        
        /* Size check */
        if( u4_useSize <= u4_msgMaxSize )
        {
            (void)SecOCStd_MemCpy( &st_info.ptBuffTop[u4_bufferStartOffset + u4SetPos], ptSetData->ptData, ptSetData->u4Size ); /* no return check required */
            st_info.ptCtrlInfo[u2Index].u4UseSize = u4_useSize;
            ud_stdRet = E_OK;
            
            /* Get data */
            ptSetData->ptData = &st_info.ptBuffTop[u4_bufferStartOffset];
            ptSetData->u4Size = st_info.ptCtrlInfo[u2Index].u4UseSize;
        }
    }
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Buff_GetSelect                                     */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BuffKind :                                             */
/*               | u2Index    :                                             */
/*               | ptGetData  :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_GetSelect
(
    uint16 u2BuffKind,
    uint16 u2Index,
    P2VAR(SecOC_Buff_DataType, AUTOMATIC, SECOC_APPL_DATA) ptGetData
)
{
    SecOC_Buff_InfoType st_info;
    Std_ReturnType      ud_stdRet = E_NOT_OK;
    Std_ReturnType      ud_getInfoRet;
    Std_ReturnType      ud_getConfigRet;
    uint32              u4_bufferStartOffset;
    uint32              u4_msgMaxSize;
    uint32              u4_useSize;
    
    ud_getInfoRet = SecOC_Buff_GetInfo( u2BuffKind, &st_info );
    ud_getConfigRet = SecOC_Buff_GetMsgConfig( u2BuffKind, u2Index, &u4_msgMaxSize, &u4_bufferStartOffset );
    
    /* Parameters check */
    if( (ud_getInfoRet == (Std_ReturnType)E_OK)
      && (ud_getConfigRet == (Std_ReturnType)E_OK)
      && (ptGetData != NULL_PTR) )
    {
        ptGetData->ptData = &st_info.ptBuffTop[u4_bufferStartOffset];
        u4_useSize = st_info.ptCtrlInfo[u2Index].u4UseSize;
        if( u4_useSize > u4_msgMaxSize )
        {
            u4_useSize = u4_msgMaxSize;
        }
        ptGetData->u4Size = u4_useSize;
        
        ud_stdRet = E_OK;
    }
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Buff_ClearSelect                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BuffKind :                                             */
/*               | u2Index    :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_ClearSelect
(
    uint16 u2BuffKind,
    uint16 u2Index
)
{
    SecOC_Buff_InfoType st_info;
    Std_ReturnType      ud_stdRet = E_NOT_OK;
    Std_ReturnType      ud_getInfoRet;
    Std_ReturnType      ud_getConfigRet;
    uint32              u4_bufferStartOffset = 0UL;
    uint32              u4_msgMaxSize = 0UL;
    uint16              u2_current;
    uint16              u2_prev;
    uint16              u2_next;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
    Std_ReturnType      ud_topIndexRet;
    uint16              u2_redundant;
#endif
    uint8               u1_loopFlag;
    
    ud_getInfoRet = SecOC_Buff_GetInfo( u2BuffKind, &st_info );
    ud_getConfigRet = SecOC_Buff_GetMsgConfig( u2BuffKind, u2Index, &u4_msgMaxSize, &u4_bufferStartOffset );
    
    /* Parameters check */
    if( (ud_getInfoRet == (Std_ReturnType)E_OK)
      && (ud_getConfigRet == (Std_ReturnType)E_OK) )
    {
        SchM_Enter_SecOC_Buff();
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        ud_topIndexRet = SecOC_Buff_GetTopIndex( u2BuffKind, &u2_current );
        
        if( ud_topIndexRet == (Std_ReturnType)E_OK )
#else
        (void)SecOC_Buff_GetTopIndex( u2BuffKind, &u2_current ); /* no return check required */
#endif
        {
            /* NextIndex check */
            if( u2_current == u2Index )
            {
                u2_next = st_info.ptCtrlInfo[u2_current].u2NextIndex;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
                u2_redundant = (uint16)(~st_info.ptCtrlInfo[u2_current].u2NextIndexRedundant);
                if( u2_next == u2_redundant )
                {
#endif
                    (void)SecOC_Buff_SetTopIndex( u2BuffKind, u2_next ); /* no return check required */
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
                }
                else
                {
                    /* error */
                    SecOC_Buff_u1RamCheckFailFlag = SECOC_BUFF_FLAG_TRUE;
                }
#endif
            }
            else if( u2_current < st_info.u2MaxIndexNum )
            {
                u1_loopFlag = SECOC_BUFF_FLAG_TRUE;
                u2_prev = u2_current;
                
                while( u1_loopFlag == SECOC_BUFF_FLAG_TRUE )
                {
                    u2_next = st_info.ptCtrlInfo[u2_current].u2NextIndex;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
                    u2_redundant = (uint16)(~st_info.ptCtrlInfo[u2_current].u2NextIndexRedundant);
                    if( u2_next == u2_redundant )
                    {
#endif
                        if( u2_current == u2Index )
                        {
                            st_info.ptCtrlInfo[u2_prev].u2NextIndex = u2_next;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
                            st_info.ptCtrlInfo[u2_prev].u2NextIndexRedundant = (uint16)(~u2_next);
#endif
                            break;
                        }
                        else if( u2_next < st_info.u2MaxIndexNum )
                        {
                            u2_prev = u2_current;
                            u2_current = u2_next;
                        }
                        else
                        {
                            u1_loopFlag = SECOC_BUFF_FLAG_FALSE;
                        }
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
                    }
                    else
                    {
                        /* error */
                        SecOC_Buff_u1RamCheckFailFlag = SECOC_BUFF_FLAG_TRUE;
                        u1_loopFlag = SECOC_BUFF_FLAG_FALSE;
                    }
#endif
                }
            }
            else
            {
                (void)SecOC_Buff_SetTopIndex( u2BuffKind, SECOC_BUFF_END_INDEX ); /* no return check required */
            }
        }
        
        SchM_Exit_SecOC_Buff();
        
        /* Buff Clear */
        st_info.ptCtrlInfo[u2Index].u4UseSize = 0U;
        st_info.ptCtrlInfo[u2Index].u2NextIndex = SECOC_BUFF_END_INDEX;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        st_info.ptCtrlInfo[u2Index].u2NextIndexRedundant = (uint16)(~SECOC_BUFF_END_INDEX);
#endif
        
        ud_stdRet = E_OK;
    }
    
    return ud_stdRet;
}

#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_Buff_GetErrorStatusTx                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | SecOC_ErrorStatusType                                    */
/*               |  SECOC_E_NONE            : No Error                      */
/*               |  SECOC_E_RAM_CHECK_FAIL  : RAM Error                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(SecOC_ErrorStatusType, SECOC_CODE) SecOC_Buff_GetErrorStatusTx
(
    void
)
{
    SecOC_ErrorStatusType   ud_errorStatus = SECOC_E_NONE;
    uint16                  u2_topIndex;
    uint16                  u2_topIndexRedundant;
    
    SchM_Enter_SecOC_Buff();
    
    u2_topIndex = SecOC_Buff_u2TxTopIndex;
    u2_topIndexRedundant = (uint16)(~SecOC_Buff_u2TxTopIndexRedundant);
    
    if( u2_topIndex == u2_topIndexRedundant )
    {
        SecOC_Buff_u2TxTopIndex = u2_topIndex;
    }
    else
    {
        SecOC_Buff_u1RamCheckFailFlag = SECOC_BUFF_FLAG_TRUE;
    }
    
    SchM_Exit_SecOC_Buff();
    
    if( SecOC_Buff_u1RamCheckFailFlag != SECOC_BUFF_FLAG_FALSE )
    {
        ud_errorStatus = SECOC_E_RAM_CHECK_FAIL;
    }
    
    return ud_errorStatus;
}
#endif
#endif /* SECOC_AB_RAM_ERROR_CHK */

#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_Buff_GetErrorStatusRx                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | SecOC_ErrorStatusType                                    */
/*               |  SECOC_E_NONE            : No Error                      */
/*               |  SECOC_E_RAM_CHECK_FAIL  : RAM Error                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(SecOC_ErrorStatusType, SECOC_CODE) SecOC_Buff_GetErrorStatusRx
(
    void
)
{
    SecOC_ErrorStatusType   ud_errorStatus = SECOC_E_NONE;
    uint16                  u2_topIndex;
    uint16                  u2_topIndexRedundant;
    
    SchM_Enter_SecOC_Buff();
    
    u2_topIndex = SecOC_Buff_u2RxTopIndex;
    u2_topIndexRedundant = (uint16)(~SecOC_Buff_u2RxTopIndexRedundant);
    
    if( u2_topIndex == u2_topIndexRedundant )
    {
        SecOC_Buff_u2RxTopIndex = u2_topIndex;
    }
    else
    {
        SecOC_Buff_u1RamCheckFailFlag = SECOC_BUFF_FLAG_TRUE;
    }
    
    SchM_Exit_SecOC_Buff();
    
    if( SecOC_Buff_u1RamCheckFailFlag != SECOC_BUFF_FLAG_FALSE )
    {
        ud_errorStatus = SECOC_E_RAM_CHECK_FAIL;
    }
    
    return ud_errorStatus;
}
#endif
#endif /* SECOC_AB_RAM_ERROR_CHK */

/****************************************************************************/
/* Function Name | SecOC_Buff_ReadDividePos                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BuffKind    :                                          */
/*               | u2Index       :                                          */
/*               | ptGetPos      :                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_ReadDividePos
(
    uint16 u2BuffKind,
    uint16 u2Index,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptGetPos
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    uint32          u4_divideDataPos;
    
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    if( u2BuffKind == SECOC_BUFF_TX )
    {
        if( u2Index < SecOC_TxPduProcessingMax )
        {
            u4_divideDataPos = SecOC_Buff_u4TxDivideCopyPos[u2Index];
            
            if( u4_divideDataPos <= SecOC_TxPduProcessing[u2Index].SameBufferPduRef )
            {
                *ptGetPos = u4_divideDataPos;
                ud_stdRet = E_OK;
            }
        }
    }
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    if( u2BuffKind == SECOC_BUFF_RX )
    {
        if( u2Index < SecOC_RxPduProcessingMax )
        {
            u4_divideDataPos = SecOC_Buff_u4RxDivideCopyPos[u2Index];
            
            if( u4_divideDataPos <= SecOC_RxPduProcessing[u2Index].SameBufferPduRef )
            {
                *ptGetPos = u4_divideDataPos;
                ud_stdRet = E_OK;
            }
        }
    }
#endif
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Buff_WriteDividePos                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BuffKind    :                                          */
/*               | u2Index       :                                          */
/*               | u4SetPos      :                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_WriteDividePos
(
    uint16 u2BuffKind,
    uint16 u2Index,
    uint32 u4SetPos
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    if( u2BuffKind == SECOC_BUFF_TX )
    {
        if( u2Index < SecOC_TxPduProcessingMax )
        {
            SecOC_Buff_u4TxDivideCopyPos[u2Index] = u4SetPos;
            ud_stdRet = E_OK;
        }
    }
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    if( u2BuffKind == SECOC_BUFF_RX )
    {
        if( u2Index < SecOC_RxPduProcessingMax )
        {
            SecOC_Buff_u4RxDivideCopyPos[u2Index] = u4SetPos;
            ud_stdRet = E_OK;
        }
    }
#endif
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Buff_ReadTotalSize                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BuffKind :                                             */
/*               | u2Index    :                                             */
/*               | ptMsgSize  :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_ReadTotalSize
(
    uint16 u2BuffKind,
    uint16 u2Index,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptMsgSize
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    uint32          u4_totalMsgSize;
    
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    if( u2BuffKind == SECOC_BUFF_RX )
    {
        if( u2Index < SecOC_RxPduProcessingMax )
        {
            u4_totalMsgSize = SecOC_Buff_u4RxDivideTotalSize[u2Index];
            
            if( u4_totalMsgSize <= SecOC_RxPduProcessing[u2Index].SameBufferPduRef )
            {
                *ptMsgSize = u4_totalMsgSize;
                ud_stdRet = E_OK;
            }
        }
    }
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    if( u2BuffKind == SECOC_BUFF_TX )
    {
        if( u2Index < SecOC_TxPduProcessingMax )
        {
            u4_totalMsgSize = SecOC_Buff_u4TxDivideTotalSize[u2Index];
            
            if( u4_totalMsgSize <= SecOC_TxPduProcessing[u2Index].SameBufferPduRef )
            {
                *ptMsgSize = u4_totalMsgSize;
                ud_stdRet = E_OK;
            }
        }
    }
#endif

    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Buff_WriteTotalSize                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BuffKind :                                             */
/*               | u2Index    :                                             */
/*               | u4SetSize  :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_WriteTotalSize
(
    uint16 u2BuffKind,
    uint16 u2Index,
    uint32 u4SetSize
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    if( u2BuffKind == SECOC_BUFF_RX )
    {
        if( u2Index < SecOC_RxPduProcessingMax )
        {
            SecOC_Buff_u4RxDivideTotalSize[u2Index] = u4SetSize;
            ud_stdRet = E_OK;
        }
    }
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    if( u2BuffKind == SECOC_BUFF_TX )
    {
        if( u2Index < SecOC_TxPduProcessingMax )
        {
            SecOC_Buff_u4TxDivideTotalSize[u2Index] = u4SetSize;
            ud_stdRet = E_OK;
        }
    }
#endif

    return ud_stdRet;
}


/****************************************************************************/
/* Function Name | SecOC_Buff_SetNextIndex                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BuffKind :                                             */
/*               | u2Index    :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_SetNextIndex
(
    uint16 u2BuffKind,
    uint16 u2Index
)
{
    SecOC_Buff_InfoType st_info;
    Std_ReturnType      ud_stdRet = E_NOT_OK;
    Std_ReturnType      ud_stdGetInfoRet;
    uint16              u2_current;
    uint16              u2_next;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
    Std_ReturnType      ud_stdGetTopIndexRet;
    uint16              u2_redundant;
#endif
    uint8               u1_loopFlag;
    
    ud_stdGetInfoRet = SecOC_Buff_GetInfo( u2BuffKind, &st_info );
    
    if( ud_stdGetInfoRet == (Std_ReturnType)E_OK )
    {
        st_info.ptCtrlInfo[u2Index].u2NextIndex = SECOC_BUFF_END_INDEX;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        st_info.ptCtrlInfo[u2Index].u2NextIndexRedundant = (uint16)(~SECOC_BUFF_END_INDEX);
#endif
        
        SchM_Enter_SecOC_Buff();
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        ud_stdGetTopIndexRet = SecOC_Buff_GetTopIndex( u2BuffKind, &u2_current );
        
        if( ud_stdGetTopIndexRet == (Std_ReturnType)E_OK )
#else
        (void)SecOC_Buff_GetTopIndex( u2BuffKind, &u2_current ); /* no return check required */
#endif
        {
            /* NextIndex check */
            if( u2_current == SECOC_BUFF_END_INDEX )
            {
                ud_stdRet = SecOC_Buff_SetTopIndex( u2BuffKind, u2Index );
            }
            else if( u2_current < st_info.u2MaxIndexNum )
            {
                /* Last index search */
                u1_loopFlag = SECOC_BUFF_FLAG_TRUE;
                
                while( u1_loopFlag == SECOC_BUFF_FLAG_TRUE )
                {
                    u2_next = st_info.ptCtrlInfo[u2_current].u2NextIndex;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
                    u2_redundant = (uint16)(~st_info.ptCtrlInfo[u2_current].u2NextIndexRedundant);
                    
                    if( u2_next == u2_redundant )
                    {
#endif
                        if( u2_next < st_info.u2MaxIndexNum )
                        {
                            u2_current = u2_next;
                        }
                        else
                        {
                            st_info.ptCtrlInfo[u2_current].u2NextIndex = u2Index;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
                            st_info.ptCtrlInfo[u2_current].u2NextIndexRedundant = (uint16)(~u2Index);
#endif
                            ud_stdRet = E_OK;
                            u1_loopFlag = SECOC_BUFF_FLAG_FALSE;
                        }
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
                    }
                    else
                    {
                        /* error */
                        SecOC_Buff_u1RamCheckFailFlag = SECOC_BUFF_FLAG_TRUE;
                        u1_loopFlag = SECOC_BUFF_FLAG_FALSE;
                    }
#endif
                }
            }
            else
            {
                /* No Processing */
            }
        }
        
        SchM_Exit_SecOC_Buff();
    }
    
    return ud_stdRet;
}

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_Buff_ClearSelectSize                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BuffKind :                                             */
/*               | u2Index    :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_ClearSelectSize
(
    uint16 u2BuffKind,
    uint16 u2Index
)
{
    SecOC_Buff_InfoType st_info;
    Std_ReturnType      ud_getInfoRet;
    Std_ReturnType      ud_getConfigRet;
    Std_ReturnType      ud_stdRet = E_NOT_OK;
    uint32              u4_bufferStartOffset = 0UL;
    uint32              u4_msgMaxSize = 0UL;
    
    ud_getInfoRet = SecOC_Buff_GetInfo( u2BuffKind, &st_info );
    ud_getConfigRet = SecOC_Buff_GetMsgConfig( u2BuffKind, u2Index, &u4_msgMaxSize, &u4_bufferStartOffset );
    
    /* Parameters check */
    if( (ud_getInfoRet == (Std_ReturnType)E_OK)
      && (ud_getConfigRet == (Std_ReturnType)E_OK) )
    {
        /* buffer clear */
        st_info.ptCtrlInfo[u2Index].u4UseSize = 0U;
        ud_stdRet = E_OK;
    }
    
    return ud_stdRet;
}
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_Buff_SetSelectSize                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index    :                                             */
/*               | u4SetDataSize  :                                         */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_SetSelectSize
(
    uint16 u2Index,
    uint32 u4SetDataSize
)
{
    SecOC_Buff_InfoType st_info;
    Std_ReturnType      ud_stdRet = E_NOT_OK;
    
    (void)SecOC_Buff_GetInfo( SECOC_BUFF_TX, &st_info ); /* no return check required */
    
    /* Parameters check */
    if( (u2Index < SecOC_TxPduProcessingMax)
      && (u4SetDataSize <= SecOC_TxPduProcessing[u2Index].SameBufferPduRef) )
    {
        st_info.ptCtrlInfo[u2Index].u4UseSize = u4SetDataSize;
        ud_stdRet = E_OK;
    }
    
    return ud_stdRet;
}
#endif

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | SecOC_Buff_GetInfo                                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BuffKind :                                             */
/*               | ptInfo     :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_GetInfo
(
    uint16 u2BuffKind,
    P2VAR(SecOC_Buff_InfoType, AUTOMATIC, SECOC_APPL_DATA) ptInfo
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    if( u2BuffKind == SECOC_BUFF_TX )
    {
        ptInfo->ptCtrlInfo = &SecOC_Buff_stTxCtrlInfo[0];
        ptInfo->ptTopMsgIndex = &SecOC_Buff_u2TxTopIndex;
        ptInfo->ptBuffTop = &SecOC_Buff_stTxBuffer.u1TxBuffer[0];
        ptInfo->u2MaxIndexNum = SecOC_TxPduProcessingMax;
        ud_stdRet = E_OK;
    }
#endif
    
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    if( u2BuffKind == SECOC_BUFF_RX )
    {
        ptInfo->ptCtrlInfo = &SecOC_Buff_stRxCtrlInfo[0];
        ptInfo->ptTopMsgIndex = &SecOC_Buff_u2RxTopIndex;
        ptInfo->ptBuffTop = &SecOC_Buff_stRxBuffer.u1RxBuffer[0];
        ptInfo->u2MaxIndexNum = SecOC_RxPduProcessingMax;
        ud_stdRet = E_OK;
    }
#endif
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Buff_GetMsgConfig                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BuffKind          :                                    */
/*               | u2Index             :                                    */
/*               | ptMsgMaxSize        :                                    */
/*               | ptBufferStartOffset :                                    */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_GetMsgConfig
(
    uint16 u2BuffKind,
    uint16 u2Index,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptMsgMaxSize,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptBufferStartOffset
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    if( (u2BuffKind == SECOC_BUFF_TX)
      && (u2Index < SecOC_TxPduProcessingMax) )
    {
        *ptMsgMaxSize = SecOC_TxPduProcessing[u2Index].SameBufferPduRef;
        *ptBufferStartOffset = SecOC_TxPduProcessing[u2Index].Ab_BufferStartOffset;
        ud_stdRet = E_OK;
    }
#endif
    
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    if( (u2BuffKind == SECOC_BUFF_RX)
      && (u2Index < SecOC_RxPduProcessingMax) )
    {
        *ptMsgMaxSize = SecOC_RxPduProcessing[u2Index].SameBufferPduRef;
        *ptBufferStartOffset = SecOC_RxPduProcessing[u2Index].Ab_BufferStartOffset;
        ud_stdRet = E_OK;
    }
#endif
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Buff_GetTopIndex                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BuffKind :                                             */
/*               | ptTopIndex :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_GetTopIndex
(
    uint16 u2BuffKind,
    P2VAR(uint16, AUTOMATIC, SECOC_APPL_DATA) ptTopIndex
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    uint16          u2_topIndex;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
    uint16          u2_topIndexRedundant;
#endif
    
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    if( u2BuffKind == SECOC_BUFF_TX )
    {
        u2_topIndex = SecOC_Buff_u2TxTopIndex;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        u2_topIndexRedundant = (uint16)(~SecOC_Buff_u2TxTopIndexRedundant);
        
        if( u2_topIndex == u2_topIndexRedundant )
        {
#endif /* SECOC_AB_RAM_ERROR_CHK */
            *ptTopIndex = u2_topIndex;
            ud_stdRet = E_OK;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        }
        else
        {
            SecOC_Buff_u1RamCheckFailFlag = SECOC_BUFF_FLAG_TRUE;
        }
#endif /* SECOC_AB_RAM_ERROR_CHK */
    }
#endif
    
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    if( u2BuffKind == SECOC_BUFF_RX )
    {
        u2_topIndex = SecOC_Buff_u2RxTopIndex;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        u2_topIndexRedundant = (uint16)(~SecOC_Buff_u2RxTopIndexRedundant);
        
        if( u2_topIndex == u2_topIndexRedundant )
        {
#endif /* SECOC_AB_RAM_ERROR_CHK */
            *ptTopIndex = u2_topIndex;
            ud_stdRet = E_OK;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        }
        else
        {
            SecOC_Buff_u1RamCheckFailFlag = SECOC_BUFF_FLAG_TRUE;
        }
#endif /* SECOC_AB_RAM_ERROR_CHK */
    }
#endif
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_Buff_SetTopIndex                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BuffKind :                                             */
/*               | u2TopIndex :                                             */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     : Success                                      */
/*               |  E_NOT_OK : Failure                                      */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_SetTopIndex
(
    uint16 u2BuffKind,
    uint16 u2TopIndex
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
    if( u2BuffKind == SECOC_BUFF_TX )
    {
        SecOC_Buff_u2TxTopIndex = u2TopIndex;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        SecOC_Buff_u2TxTopIndexRedundant = (uint16)(~u2TopIndex);
#endif /* SECOC_AB_RAM_ERROR_CHK */
        ud_stdRet = E_OK;
    }
#endif
    
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
    if( u2BuffKind == SECOC_BUFF_RX )
    {
        SecOC_Buff_u2RxTopIndex = u2TopIndex;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        SecOC_Buff_u2RxTopIndexRedundant = (uint16)(~u2TopIndex);
#endif /* SECOC_AB_RAM_ERROR_CHK */
        ud_stdRet = E_OK;
    }
#endif
    
    return ud_stdRet;
}

#define SECOC_STOP_SEC_CODE
#include <SecOC_MemMap.h>

#endif /* #if ( ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)) || ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)) ) */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
