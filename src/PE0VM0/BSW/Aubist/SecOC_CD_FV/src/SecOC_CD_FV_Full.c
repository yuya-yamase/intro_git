/* SecOC_CD_FV_Full_c_v2-1-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC_CD_FV/Full/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SchM_SecOC.h>
#include <SecOCStd_String.h>
#include <SecOCStd_Util.h>
#include "../inc/SecOC_CD_FV_Full.h"

#if (SECOC_AB_BUS_FULL_MAX > 0U)

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if (SECOC_AB_FULLFV_TRIP_CNT_LENGTH == 32U)
#define SECOC_CD_FV_FULL_TRIP_MSK   (0xFFFFFFFFU)
#else
#define SECOC_CD_FV_FULL_TRIP_MSK   ((1UL << SECOC_AB_FULLFV_TRIP_CNT_LENGTH) - 1UL)
#endif
#if (SECOC_AB_FULLFV_MSG_CNT_LENGTH == 32U)
#define SECOC_CD_FV_FULL_MSG_MSK    (0xFFFFFFFFU)
#else
#define SECOC_CD_FV_FULL_MSG_MSK    ((1UL << SECOC_AB_FULLFV_MSG_CNT_LENGTH)  - 1UL)
#endif

#define SECOC_CD_FV_FULL_TRIP_MAX   (SECOC_CD_FV_FULL_TRIP_MSK)
#define SECOC_CD_FV_FULL_MSG_MAX    (SECOC_CD_FV_FULL_MSG_MSK)

#define SECOC_CD_FV_FULL_LEN        (SECOC_AB_FULLFV_TRIP_CNT_LENGTH + SECOC_AB_FULLFV_MSG_CNT_LENGTH)

#define SECOC_CD_FV_FULL_OEM_TRIP_LEN   (24U)
#define SECOC_CD_FV_FULL_OEM_MSG_LEN    (32U)

#define SECOC_CD_FV_FULL_TRIP_TX_INIT   (1UL)
#define SECOC_CD_FV_FULL_MSG_TX_INIT    (0UL)

#define SECOC_CD_FV_FULL_OFFSET_INIT    (0UL)

#define SECOC_CD_FV_FULL_MSG_INCREMENT   (1UL)

#define SECOC_CD_FV_FULL_BYTE_0         ((uint16)0U)    /* 0bit equal 0byte */
#define SECOC_CD_FV_FULL_BYTE_1         ((uint16)8U)    /* 8bit equal 1byte */
#define SECOC_CD_FV_FULL_BYTE_2         ((uint16)16U)   /* 16bit equal 2byte */
#define SECOC_CD_FV_FULL_BYTE_3         ((uint16)24U)   /* 24bit equal 3byte */
#define SECOC_CD_FV_FULL_BYTE_4         ((uint16)32U)   /* 32bit equal 4byte */
#define SECOC_CD_FV_FULL_BYTESURPLUS    (0x07U)
#define SECOC_CD_FV_FULL_BYTESHIFT      (3U)

#define SECOC_CD_FV_FULL_MSK_8BIT       (0x000000FFUL)

#define SECOC_CD_FV_FULL_INDEX1         ((uint16)1U)
#define SECOC_CD_FV_FULL_INDEX2         ((uint16)2U)
#define SECOC_CD_FV_FULL_INDEX3         ((uint16)3U)
#define SECOC_CD_FV_FULL_INDEX4         ((uint16)4U)

#define SECOC_CD_FV_FULL_FALSE          ((uint8)0x5AU)
#define SECOC_CD_FV_FULL_TRUE           ((uint8)0xA5U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    uint32  u4Trip;
    uint32  u4Msg;
} SecOC_CD_FV_Full_LastType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CD_FV_CODE
#include <SecOC_MemMap.h>

static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_ClearLast
(
    uint16 u2BusIndex
);
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_AryToU4
(
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptArray,
    uint32 u4OffsetLen,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptData,
    uint16 u2DataLen
);
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_U4ToAry
(
    uint32 u4Data,
    uint16 u2DataLen,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptArray,
    uint32 u4OffsetLen
);

#define SECOC_STOP_SEC_CD_FV_CODE
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CD_FV_VAR_NO_INIT
#include <SecOC_MemMap.h>

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_TX_PDU_FULLFV_MAX > 0U))
static VAR(uint32, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Full_u4NewTrip[SECOC_AB_BUS_FULL_MAX];
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
static VAR(uint32, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Full_u4NewTripRedundant[SECOC_AB_BUS_FULL_MAX];
static VAR(SecOC_ErrorStatusType, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Full_udRamChkResult[SECOC_AB_BUS_FULL_MAX];
#endif
static VAR(SecOC_CD_FV_Full_LastType, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Full_stTxLast[SECOC_AB_TX_PDU_FULLFV_MAX];
static VAR(SecOC_CD_FV_Full_LastType, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Full_stTxWork[SECOC_AB_TX_PDU_FULLFV_MAX];
static VAR(uint8, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Full_u1TxRenewalFlag[SECOC_AB_TX_PDU_FULLFV_MAX];
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_RX_PDU_FULLFV_MAX > 0U))
static VAR(SecOC_CD_FV_Full_LastType, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Full_stRxLast[SECOC_AB_RX_PDU_FULLFV_MAX];
static VAR(SecOC_CD_FV_Full_LastType, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Full_stRxWork[SECOC_AB_RX_PDU_FULLFV_MAX];
static VAR(uint8, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Full_u1RxRenewalFlag[SECOC_AB_RX_PDU_FULLFV_MAX];
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
/* Function Name | SecOC_CD_FV_Full_Init                                    */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_Init
(
    void
)
{
    uint16 u2_loop;

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_TX_PDU_FULLFV_MAX > 0U))
    uint32 u4_trip;
    
    u4_trip = SECOC_CD_FV_FULL_TRIP_TX_INIT;
    
    for( u2_loop = 0U; u2_loop < SecOC_Ab_BusFullMax; u2_loop++ )
    {
        SecOC_CD_FV_Full_u4NewTrip[u2_loop] = u4_trip;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        SecOC_CD_FV_Full_u4NewTripRedundant[u2_loop] = ~u4_trip;
        SecOC_CD_FV_Full_udRamChkResult[u2_loop] = SECOC_E_NONE;
#endif
    }
    
    for( u2_loop = 0U; u2_loop < SecOC_Ab_TxPduFullFvMax; u2_loop++ )
    {
        SecOC_CD_FV_Full_stTxLast[u2_loop].u4Trip = u4_trip;
        SecOC_CD_FV_Full_stTxLast[u2_loop].u4Msg  = SECOC_CD_FV_FULL_MSG_TX_INIT;
        SecOC_CD_FV_Full_u1TxRenewalFlag[u2_loop] = SECOC_CD_FV_FULL_FALSE;
    }
    SecOCStd_MemClr( &SecOC_CD_FV_Full_stTxWork[0], sizeof(SecOC_CD_FV_Full_stTxWork) );
#endif
    
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_RX_PDU_FULLFV_MAX > 0U))
    SecOCStd_MemClr( &SecOC_CD_FV_Full_stRxLast[0], sizeof(SecOC_CD_FV_Full_stRxLast) );
    SecOCStd_MemClr( &SecOC_CD_FV_Full_stRxWork[0], sizeof(SecOC_CD_FV_Full_stRxWork) );
    for( u2_loop = 0U; u2_loop < SecOC_Ab_RxPduFullFvMax; u2_loop++ )
    {
        SecOC_CD_FV_Full_u1RxRenewalFlag[u2_loop] = SECOC_CD_FV_FULL_FALSE;
    }
#endif
    
    return ;
}

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Full_ReadTx                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index:                                                 */
/*               | ptFv:                                                    */
/*               | ptFvLen:                                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK         : Success                                  */
/*               |  E_NOT_OK     : Failure                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_ReadTx
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvLen
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
#if (SECOC_AB_TX_PDU_FULLFV_MAX > 0U)
    uint32 u4_lastTrip;
    uint32 u4_lastMsg;
    
    /* Parameters check */
    if( (u2Index < SecOC_Ab_TxPduFullFvMax)
      && (ptFv != NULL_PTR)
      && (ptFvLen != NULL_PTR)
    #if (SECOC_CD_FV_FULL_LEN > 0U)
      && (*ptFvLen >= SECOC_CD_FV_FULL_LEN)
    #endif
      )
    {
        SchM_Enter_SecOC_CD_FV();
        u4_lastTrip = SecOC_CD_FV_Full_stTxLast[u2Index].u4Trip;
        u4_lastMsg  = SecOC_CD_FV_Full_stTxLast[u2Index].u4Msg;
        SchM_Exit_SecOC_CD_FV();
        
        SecOC_CD_FV_Full_U4ToAry( u4_lastTrip, SECOC_AB_FULLFV_TRIP_CNT_LENGTH, ptFv, SECOC_CD_FV_FULL_OFFSET_INIT );
        SecOC_CD_FV_Full_U4ToAry( u4_lastMsg, SECOC_AB_FULLFV_MSG_CNT_LENGTH, ptFv, SECOC_AB_FULLFV_TRIP_CNT_LENGTH );
        *ptFvLen = (uint32)(SECOC_CD_FV_FULL_LEN);
        ud_stdRet = E_OK;
    }
#endif
    
    return ud_stdRet;
}
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Full_ReadRx                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index:                                                 */
/*               | ptFv:                                                    */
/*               | ptFvLen:                                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK         : Success                                  */
/*               |  E_NOT_OK     : Failure                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_ReadRx
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvLen
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
#if (SECOC_AB_RX_PDU_FULLFV_MAX > 0U)
    uint32 u4_lastTrip;
    uint32 u4_lastMsg;
    
    /* Parameters check */
    if( (u2Index < SecOC_Ab_RxPduFullFvMax)
      && (ptFv != NULL_PTR)
      && (ptFvLen != NULL_PTR)
    #if (SECOC_CD_FV_FULL_LEN > 0U)
      && (*ptFvLen >= SECOC_CD_FV_FULL_LEN)
    #endif
      )
    {
        SchM_Enter_SecOC_CD_FV();
        u4_lastTrip = SecOC_CD_FV_Full_stRxLast[u2Index].u4Trip;
        u4_lastMsg  = SecOC_CD_FV_Full_stRxLast[u2Index].u4Msg;
        SchM_Exit_SecOC_CD_FV();
        
        SecOC_CD_FV_Full_U4ToAry( u4_lastTrip, SECOC_AB_FULLFV_TRIP_CNT_LENGTH, ptFv, SECOC_CD_FV_FULL_OFFSET_INIT );
        SecOC_CD_FV_Full_U4ToAry( u4_lastMsg, SECOC_AB_FULLFV_MSG_CNT_LENGTH, ptFv, SECOC_AB_FULLFV_TRIP_CNT_LENGTH );
        *ptFvLen = (uint32)(SECOC_CD_FV_FULL_LEN);
        ud_stdRet = E_OK;
    }
#endif
    
    return ud_stdRet;
}
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Full_ReadTrip                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index:                                                 */
/*               | ptFv:                                                    */
/*               | ptFvLen:                                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK         : Success                                  */
/*               |  E_NOT_OK     : Failure                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_ReadTrip
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvLen
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
    
#if (SECOC_AB_TX_PDU_FULLFV_MAX > 0U)
    /* Parameters check */
    if( (u2Index < SecOC_Ab_BusFullMax)
      && (ptFv != NULL_PTR)
      && (ptFvLen != NULL_PTR)
    #if (SECOC_AB_FULLFV_TRIP_CNT_LENGTH > 0U)
      && (*ptFvLen >= (uint32)SECOC_AB_FULLFV_TRIP_CNT_LENGTH)
    #endif
      )
    {
        SecOC_CD_FV_Full_U4ToAry( SecOC_CD_FV_Full_u4NewTrip[u2Index], SECOC_AB_FULLFV_TRIP_CNT_LENGTH, ptFv, SECOC_CD_FV_FULL_OFFSET_INIT );
        *ptFvLen = SECOC_AB_FULLFV_TRIP_CNT_LENGTH;
        ud_stdRet = E_OK;
    }
#endif
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Full_WriteTx                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index:                                                 */
/*               | ptFv:                                                    */
/*               | u4FvLen:                                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK         : Success                                  */
/*               |  E_NOT_OK     : Failure                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_WriteTx
(
    uint16 u2Index,
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    uint32 u4FvLen
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
#if (SECOC_AB_TX_PDU_FULLFV_MAX > 0U)
    uint32 u4_lastTrip;
    uint32 u4_lastMsg;
    
    /* Parameters check */
    if( (u2Index < SecOC_Ab_TxPduFullFvMax)
      && (ptFv != NULL_PTR)
    #if (SECOC_CD_FV_FULL_LEN > 0U)
      && (u4FvLen == SECOC_CD_FV_FULL_LEN)
    #endif
      )
    {
        SecOC_CD_FV_Full_AryToU4( ptFv, SECOC_CD_FV_FULL_OFFSET_INIT, &u4_lastTrip, SECOC_AB_FULLFV_TRIP_CNT_LENGTH );
        SecOC_CD_FV_Full_AryToU4( ptFv, SECOC_AB_FULLFV_TRIP_CNT_LENGTH, &u4_lastMsg, SECOC_AB_FULLFV_MSG_CNT_LENGTH );
        
        SchM_Enter_SecOC_CD_FV();
        SecOC_CD_FV_Full_u1TxRenewalFlag[u2Index] = SECOC_CD_FV_FULL_FALSE;
        SecOC_CD_FV_Full_stTxLast[u2Index].u4Trip = u4_lastTrip;
        SecOC_CD_FV_Full_stTxLast[u2Index].u4Msg  = u4_lastMsg;
        SecOC_CD_FV_Full_stTxWork[u2Index].u4Trip = u4_lastTrip;
        SecOC_CD_FV_Full_stTxWork[u2Index].u4Msg  = u4_lastMsg;
        SchM_Exit_SecOC_CD_FV();
        
        ud_stdRet = E_OK;
    }
#endif
    
    return ud_stdRet;
}
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Full_WriteRx                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index:                                                 */
/*               | ptFv:                                                    */
/*               | u4FvLen:                                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK         : Success                                  */
/*               |  E_NOT_OK     : Failure                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_WriteRx
(
    uint16 u2Index,
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    uint32 u4FvLen
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
#if (SECOC_AB_RX_PDU_FULLFV_MAX > 0U)
    uint32 u4_lastTrip;
    uint32 u4_lastMsg;
    
    /* Parameters check */
    if( (u2Index < SecOC_Ab_RxPduFullFvMax)
      && (ptFv != NULL_PTR)
    #if (SECOC_CD_FV_FULL_LEN > 0U)
      && (u4FvLen == SECOC_CD_FV_FULL_LEN)
    #endif
      )
    {
        SecOC_CD_FV_Full_AryToU4( ptFv, SECOC_CD_FV_FULL_OFFSET_INIT, &u4_lastTrip, SECOC_AB_FULLFV_TRIP_CNT_LENGTH );
        SecOC_CD_FV_Full_AryToU4( ptFv, SECOC_AB_FULLFV_TRIP_CNT_LENGTH, &u4_lastMsg, SECOC_AB_FULLFV_MSG_CNT_LENGTH );
        
        SchM_Enter_SecOC_CD_FV();
        SecOC_CD_FV_Full_u1RxRenewalFlag[u2Index] = SECOC_CD_FV_FULL_FALSE;
        SecOC_CD_FV_Full_stRxLast[u2Index].u4Trip = u4_lastTrip;
        SecOC_CD_FV_Full_stRxLast[u2Index].u4Msg  = u4_lastMsg;
        SecOC_CD_FV_Full_stRxWork[u2Index].u4Trip = u4_lastTrip;
        SecOC_CD_FV_Full_stRxWork[u2Index].u4Msg  = u4_lastMsg;
        SchM_Exit_SecOC_CD_FV();
        
        ud_stdRet = E_OK;
    }
#endif
    
    return ud_stdRet;
}
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Full_WriteTrip                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index:                                                 */
/*               | ptFv:                                                    */
/*               | u4FvLen:                                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK         : Success                                  */
/*               |  E_NOT_OK     : Failure                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_WriteTrip
(
    uint16 u2Index,
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    uint32 u4FvLen
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
#if (SECOC_AB_TX_PDU_FULLFV_MAX > 0U)
    uint32 u4_newTrip;
    
    /* Parameters check */
    if( (u2Index < SecOC_Ab_BusFullMax)
      && (ptFv != NULL_PTR)
    #if (SECOC_AB_FULLFV_TRIP_CNT_LENGTH > 0U)
      && (u4FvLen == (uint32)SECOC_AB_FULLFV_TRIP_CNT_LENGTH)
    #endif
      )
    {
        SecOC_CD_FV_Full_AryToU4( ptFv, SECOC_CD_FV_FULL_OFFSET_INIT, &u4_newTrip, SECOC_AB_FULLFV_TRIP_CNT_LENGTH );
        SchM_Enter_SecOC_CD_FV();
        SecOC_CD_FV_Full_u4NewTrip[u2Index] = u4_newTrip;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        SecOC_CD_FV_Full_u4NewTripRedundant[u2Index] = ~u4_newTrip;
#endif
        SchM_Exit_SecOC_CD_FV();
        ud_stdRet = E_OK;
    }
#endif
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Full_GetTx                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptIndex:                                                 */
/*               | ptFullFv:                                                */
/*               | ptTruncFv:                                               */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK               : Success                            */
/*               |  E_NOT_OK           : Failure(Skip)                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_GetTx
(
    P2CONST(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex,
    P2VAR(SecOC_CD_FV_InOutType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFullFv,
    P2VAR(SecOC_CD_FV_InOutType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptTruncFv
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
#if (SECOC_AB_TX_PDU_FULLFV_MAX > 0U)
    uint32 u4_newTrip;
    uint32 u4_lastTrip;
    #if (SECOC_AB_FULLFV_MSG_CNT_LENGTH > 0U)
    uint32 u4_lastMsg;
    #endif
    uint32 u4_workTrip;
    uint32 u4_workMsg;
    
    /* Parameters check */
    if( (ptIndex->u2FvIndexFvType < SecOC_Ab_BusFullMax)
      && (ptIndex->u2FvIndexLast < SecOC_Ab_TxPduFullFvMax)
      && (ptFullFv->ptFv != NULL_PTR)
      && (ptFullFv->ptFvLen != NULL_PTR)
      && (ptTruncFv->ptFv != NULL_PTR)
      && (ptTruncFv->ptFvLen != NULL_PTR)
    #if (SECOC_CD_FV_FULL_LEN > 0U)
      && (*(ptFullFv->ptFvLen) >= SECOC_CD_FV_FULL_LEN)
      && (*(ptTruncFv->ptFvLen) >= SECOC_CD_FV_FULL_LEN)
    #endif
      )
    {
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        if( SecOC_CD_FV_Full_udRamChkResult[ptIndex->u2FvIndexFvType] == SECOC_E_NONE )
        {
#endif
            SchM_Enter_SecOC_CD_FV();
            SecOC_CD_FV_Full_u1TxRenewalFlag[ptIndex->u2FvIndexLast] = SECOC_CD_FV_FULL_TRUE;
            /* Copy */
            u4_newTrip = SecOC_CD_FV_Full_u4NewTrip[ptIndex->u2FvIndexFvType];
            u4_lastTrip = SecOC_CD_FV_Full_stTxLast[ptIndex->u2FvIndexLast].u4Trip;
    #if (SECOC_AB_FULLFV_MSG_CNT_LENGTH > 0U)
            u4_lastMsg  = SecOC_CD_FV_Full_stTxLast[ptIndex->u2FvIndexLast].u4Msg;
    #endif
            SchM_Exit_SecOC_CD_FV();
            
            ud_stdRet = E_OK;
            
            /* Compare TripCnt */
            if( u4_newTrip == u4_lastTrip )
            {
                /* Copy to work TripCnt (from last) */
                u4_workTrip = u4_lastTrip;
                
    #if (SECOC_AB_FULLFV_MSG_CNT_LENGTH > 0U)
                /* Check MsgCnt Max */
                if( u4_lastMsg >= (uint32)SECOC_CD_FV_FULL_MSG_MAX )
                {
    #endif
                    /* Copy to work MsgCnt (MAX) */
                    u4_workMsg = SECOC_CD_FV_FULL_MSG_MAX;
    #if (SECOC_AB_FULLFV_MSG_CNT_LENGTH > 0U)
                }
                else
                {
                    /* Copy to work MsgCnt (last plus 1) */
                    u4_workMsg = u4_lastMsg + SECOC_CD_FV_FULL_MSG_INCREMENT;
                }
    #endif
            }
            else
            {
                /* Copy to work TripCnt (from new) */
                u4_workTrip = u4_newTrip;
                /* Copy to work MsgCnt (InitValue plus 1) */
                u4_workMsg = SECOC_CD_FV_FULL_MSG_TX_INIT + SECOC_CD_FV_FULL_MSG_INCREMENT;
            }
            
            SchM_Enter_SecOC_CD_FV();
            if ( SecOC_CD_FV_Full_u1TxRenewalFlag[ptIndex->u2FvIndexLast] == SECOC_CD_FV_FULL_TRUE )
            {
                /* Copy to work */
                SecOC_CD_FV_Full_stTxWork[ptIndex->u2FvIndexLast].u4Trip = u4_workTrip;
                SecOC_CD_FV_Full_stTxWork[ptIndex->u2FvIndexLast].u4Msg = u4_workMsg;
            }
            SchM_Exit_SecOC_CD_FV();
            
            /* Set FullFv */
            SecOC_CD_FV_Full_U4ToAry( u4_workTrip, SECOC_AB_FULLFV_TRIP_CNT_LENGTH, ptFullFv->ptFv, SECOC_CD_FV_FULL_OFFSET_INIT );
            SecOC_CD_FV_Full_U4ToAry( u4_workMsg, SECOC_AB_FULLFV_MSG_CNT_LENGTH, ptFullFv->ptFv, SECOC_AB_FULLFV_TRIP_CNT_LENGTH );
            *(ptFullFv->ptFvLen) = (uint32)(SECOC_CD_FV_FULL_LEN);
            
            /* Set TxFv */
            SecOC_CD_FV_Full_U4ToAry( u4_workTrip, SECOC_AB_FULLFV_TRIP_CNT_LENGTH, ptTruncFv->ptFv, SECOC_CD_FV_FULL_OFFSET_INIT );
            SecOC_CD_FV_Full_U4ToAry( u4_workMsg, SECOC_AB_FULLFV_MSG_CNT_LENGTH, ptTruncFv->ptFv, SECOC_AB_FULLFV_TRIP_CNT_LENGTH );
            *(ptTruncFv->ptFvLen) = (uint32)(SECOC_CD_FV_FULL_LEN);
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        }
#endif
    }
#endif
    
    return ud_stdRet;
}
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Full_GetRx                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptIndex:                                                 */
/*               | ptTruncFv:                                               */
/*               | u2Attempt:                                               */
/*               | ptFullFv:                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK               : Success                            */
/*               |  E_NOT_OK           : Failure(Skip)                      */
/*               |  SECOC_E_FV_NOT_OK  : FV NG                              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_GetRx
(
    P2CONST(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex,
    P2CONST(SecOC_CD_FV_InType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptTruncFv,
    uint16 u2Attempt,
    P2VAR(SecOC_CD_FV_InOutType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFullFv
)
{
    Std_ReturnType  ud_stdRet = E_NOT_OK;
#if (SECOC_AB_RX_PDU_FULLFV_MAX > 0U)
    uint32 u4_lastTrip;
    uint32 u4_lastMsg;
    uint32 u4_rcvTrip;
    uint32 u4_rcvMsg;
    
    /* Parameters check */
    if( (ptIndex->u2BusIndex < SecOC_Ab_BusMax)
      && (ptIndex->u2FvIndexLast < SecOC_Ab_RxPduFullFvMax)
      && (ptTruncFv->ptFv != NULL_PTR)
      && (ptFullFv->ptFv != NULL_PTR)
      && (ptFullFv->ptFvLen != NULL_PTR)
      && (u2Attempt == (uint16)0U)
    #if (SECOC_CD_FV_FULL_LEN > 0U)
      && (ptTruncFv->u4FvLen == SECOC_CD_FV_FULL_LEN)
      && (*(ptFullFv->ptFvLen) >= SECOC_CD_FV_FULL_LEN)
    #endif
      )
    {
        ud_stdRet = E_OK;
        SecOC_CD_FV_Full_AryToU4( ptTruncFv->ptFv, SECOC_CD_FV_FULL_OFFSET_INIT, &u4_rcvTrip, SECOC_AB_FULLFV_TRIP_CNT_LENGTH );
        SecOC_CD_FV_Full_AryToU4( ptTruncFv->ptFv, SECOC_AB_FULLFV_TRIP_CNT_LENGTH, &u4_rcvMsg, SECOC_AB_FULLFV_MSG_CNT_LENGTH );
        
        SchM_Enter_SecOC_CD_FV();
        SecOC_CD_FV_Full_u1RxRenewalFlag[ptIndex->u2FvIndexLast] = SECOC_CD_FV_FULL_TRUE;
        u4_lastTrip = SecOC_CD_FV_Full_stRxLast[ptIndex->u2FvIndexLast].u4Trip;
        u4_lastMsg  = SecOC_CD_FV_Full_stRxLast[ptIndex->u2FvIndexLast].u4Msg;
        SchM_Exit_SecOC_CD_FV();
        
        /* Compare TripCnt */
        if( u4_rcvTrip > u4_lastTrip )
        {
            /* No Processing */
        }
        else if( u4_rcvTrip == u4_lastTrip )
        {
            /* Compare MsgCnt */
            if( (u4_rcvMsg < u4_lastMsg) ||
                ((u4_rcvMsg == u4_lastMsg) && (u4_rcvMsg != (uint32)SECOC_CD_FV_FULL_MSG_MAX)) )
            {
                ud_stdRet = SECOC_E_FV_NOT_OK;
            }
        }
        else
        {
            /* Check TripCnt Wraparround */
#if (SECOC_AB_FULLFV_TRIP_CNT_LENGTH == 32U)
            if( (u4_lastTrip >= ((uint32)SECOC_CD_FV_FULL_TRIP_MAX - (uint32)SecOC_Ab_BusCollection[ptIndex->u2BusIndex].Ab_ClearAcceptanceWindow)) 
#else
            if( ( (u4_lastTrip >= (SECOC_CD_FV_FULL_TRIP_MAX - (uint32)SecOC_Ab_BusCollection[ptIndex->u2BusIndex].Ab_ClearAcceptanceWindow))
                && (u4_lastTrip <= SECOC_CD_FV_FULL_TRIP_MAX) )
#endif
              && ( (u4_rcvTrip >= SECOC_CD_FV_FULL_TRIP_TX_INIT)
                && (u4_rcvTrip <= (SECOC_CD_FV_FULL_TRIP_TX_INIT + (uint32)SecOC_Ab_BusCollection[ptIndex->u2BusIndex].Ab_ClearAcceptanceWindow)) ) )
            {
                /* Wraparround */
            }
            else
            {
                ud_stdRet = SECOC_E_FV_NOT_OK;
            }
        }
        
        if( ud_stdRet == (Std_ReturnType)E_OK )
        {
            SchM_Enter_SecOC_CD_FV();
            if ( SecOC_CD_FV_Full_u1RxRenewalFlag[ptIndex->u2FvIndexLast] == SECOC_CD_FV_FULL_TRUE )
            {
                /* Copy to work */
                SecOC_CD_FV_Full_stRxWork[ptIndex->u2FvIndexLast].u4Trip = u4_rcvTrip;
                SecOC_CD_FV_Full_stRxWork[ptIndex->u2FvIndexLast].u4Msg  = u4_rcvMsg;
            }
            SchM_Exit_SecOC_CD_FV();
            
            /* Set FullFv */
            SecOC_CD_FV_Full_U4ToAry( u4_rcvTrip, SECOC_AB_FULLFV_TRIP_CNT_LENGTH, ptFullFv->ptFv, SECOC_CD_FV_FULL_OFFSET_INIT );
            SecOC_CD_FV_Full_U4ToAry( u4_rcvMsg, SECOC_AB_FULLFV_MSG_CNT_LENGTH, ptFullFv->ptFv, SECOC_AB_FULLFV_TRIP_CNT_LENGTH );
            *(ptFullFv->ptFvLen) = (uint32)(SECOC_CD_FV_FULL_LEN);
        }
    }
#endif
    
    return ud_stdRet;
}
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Full_UpdateTx                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index:                                                 */
/*               | bUpdate:                                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK               : Success                            */
/*               |  SECOC_E_OK_FV_FULL : Success but FV is full.            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_UpdateTx
(
    uint16 u2Index,
    boolean bUpdate
)
{
    Std_ReturnType  ud_stdRet = (Std_ReturnType)E_OK;
#if (SECOC_AB_TX_PDU_FULLFV_MAX > 0U)
    /* Parameters check */
    if( u2Index < SecOC_Ab_TxPduFullFvMax )
    {
        if( bUpdate == (boolean)TRUE )
        {
            SchM_Enter_SecOC_CD_FV();
            /* Copy to last */
            SecOC_CD_FV_Full_stTxLast[u2Index].u4Trip = SecOC_CD_FV_Full_stTxWork[u2Index].u4Trip;
            SecOC_CD_FV_Full_stTxLast[u2Index].u4Msg  = SecOC_CD_FV_Full_stTxWork[u2Index].u4Msg;
            
            /* Check Counter Full */
            if( (SecOC_CD_FV_Full_stTxLast[u2Index].u4Trip == (uint32)SECOC_CD_FV_FULL_TRIP_MAX) ||
                (SecOC_CD_FV_Full_stTxLast[u2Index].u4Msg == (uint32)SECOC_CD_FV_FULL_MSG_MAX) )
            {
                /* TripCnt Max. or MsgCnt Max. Notify FullFv */
                ud_stdRet = SECOC_E_OK_FV_FULL;
            }
            
            SchM_Exit_SecOC_CD_FV();
        }
    }
#endif
    
    return ud_stdRet;
}
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Full_UpdateRx                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index:                                                 */
/*               | bUpdate:                                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK               : Success                            */
/*               |  SECOC_E_OK_FV_FULL : Success but FV is full.            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_UpdateRx
(
    uint16 u2Index,
    boolean bUpdate
)
{
    Std_ReturnType  ud_stdRet = (Std_ReturnType)E_OK;
#if (SECOC_AB_RX_PDU_FULLFV_MAX > 0U)
    /* Parameters check */
    if( u2Index < SecOC_Ab_RxPduFullFvMax )
    {
        if( bUpdate == (boolean)TRUE )
        {
            SchM_Enter_SecOC_CD_FV();
            /* Copy to last */
            SecOC_CD_FV_Full_stRxLast[u2Index].u4Trip = SecOC_CD_FV_Full_stRxWork[u2Index].u4Trip;
            SecOC_CD_FV_Full_stRxLast[u2Index].u4Msg  = SecOC_CD_FV_Full_stRxWork[u2Index].u4Msg;
            
            /* Check Counter Full */
            if( (SecOC_CD_FV_Full_stRxLast[u2Index].u4Trip == (uint32)SECOC_CD_FV_FULL_TRIP_MAX) ||
                (SecOC_CD_FV_Full_stRxLast[u2Index].u4Msg == (uint32)SECOC_CD_FV_FULL_MSG_MAX) )
            {
                /* TripCnt Max. or MsgCnt Max. Notify FullFv */
                ud_stdRet = SECOC_E_OK_FV_FULL;
            }
            
            SchM_Exit_SecOC_CD_FV();
        }
    }
#endif
    
    return ud_stdRet;
}
#endif

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Full_ResetBus                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BusIndex:                                              */
/*               | u2Index:                                                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_ResetBus
(
    uint16 u2BusIndex,
    uint16 u2Index
)
{
#if (SECOC_AB_TX_PDU_FULLFV_MAX > 0U)
    uint32 u4_trip;
#endif
    
    /* Parameters check */
    if( (u2BusIndex < SecOC_Ab_BusMax)
      && (u2Index < SecOC_Ab_BusFullMax) )
    {
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_TX_PDU_FULLFV_MAX > 0U))
        u4_trip = SECOC_CD_FV_FULL_TRIP_TX_INIT;
        SchM_Enter_SecOC_CD_FV();
        SecOC_CD_FV_Full_u4NewTrip[u2Index] = u4_trip;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        SecOC_CD_FV_Full_u4NewTripRedundant[u2Index] = ~u4_trip;
#endif
        SchM_Exit_SecOC_CD_FV();
#endif
        
        SecOC_CD_FV_Full_ClearLast(u2BusIndex);
    }
    
    return ;
}
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Full_GetErrorStatus                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | SecOC_ErrorStatusType                                    */
/*               |  SECOC_E_NONE           : No Error                       */
/*               |  SECOC_E_FV_CHECK_FAIL  : FV Error                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(SecOC_ErrorStatusType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_GetErrorStatus
(
    uint16 u2BusIndex
)
{
    SecOC_ErrorStatusType   ud_errStatus = SECOC_E_NONE;
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_TX_PDU_FULLFV_MAX > 0U))
    uint32 u4_trip;
    uint32 u4_trip_redundant;
    
    SchM_Enter_SecOC_CD_FV();
    u4_trip = SecOC_CD_FV_Full_u4NewTrip[u2BusIndex];
    u4_trip_redundant = SecOC_CD_FV_Full_u4NewTripRedundant[u2BusIndex];
    SchM_Exit_SecOC_CD_FV();
    
    if( u4_trip_redundant != ~u4_trip )
    {
        /* RAM Error */
        SecOC_CD_FV_Full_udRamChkResult[u2BusIndex] = SECOC_E_FV_CHECK_FAIL;
        ud_errStatus = SECOC_E_FV_CHECK_FAIL;
    }
    else
    {
        SecOC_CD_FV_Full_udRamChkResult[u2BusIndex] = SECOC_E_NONE;
    }
#endif /* (SECOC_AB_TX_PDU_FULLFV_MAX > 0U) */
    
    return ud_errStatus;
}
#endif /* SECOC_AB_RAM_ERROR_CHK */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Full_ClearLast                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BusIndex :                                             */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_ClearLast
(
    uint16 u2BusIndex
)
{
#if (((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_RX_PDU_FULLFV_MAX > 0U) && (SECOC_AB_RX_SECURED_MSG_IN_BUS_COUNT_MAX > 0U)) || \
     ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_TX_PDU_FULLFV_MAX > 0U) && (SECOC_AB_TX_SECURED_MSG_IN_BUS_COUNT_MAX > 0U)))
    uint16  u2_index;
    uint16  u2_clearIndex;
#endif
    

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_RX_PDU_FULLFV_MAX > 0U) && (SECOC_AB_RX_SECURED_MSG_IN_BUS_COUNT_MAX > 0U))
    /* Rx FV Bus Clear */
    for( u2_index = 0U; u2_index < SecOC_Ab_BusId2SecuredMsgIdxLists[u2BusIndex].Ab_RxSecuredMsgCount; u2_index++ )
    {
        u2_clearIndex = SecOC_RxPduProcessing[SecOC_Ab_BusId2SecuredMsgIdxLists[u2BusIndex].Ab_RxSecuredMsgIdxList[u2_index]].Ab_MessageTypeIndex;
        
        SchM_Enter_SecOC_CD_FV();
        SecOC_CD_FV_Full_u1RxRenewalFlag[u2_clearIndex] = SECOC_CD_FV_FULL_FALSE;
        SecOCStd_MemClr( &SecOC_CD_FV_Full_stRxLast[u2_clearIndex], sizeof(SecOC_CD_FV_Full_LastType) );
        SecOCStd_MemClr( &SecOC_CD_FV_Full_stRxWork[u2_clearIndex], sizeof(SecOC_CD_FV_Full_LastType) );
        SchM_Exit_SecOC_CD_FV();
    }
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_TX_PDU_FULLFV_MAX > 0U) && (SECOC_AB_TX_SECURED_MSG_IN_BUS_COUNT_MAX > 0U))
    /* Tx FV Bus Clear */
    for( u2_index = 0U; u2_index < SecOC_Ab_BusId2SecuredMsgIdxLists[u2BusIndex].Ab_TxSecuredMsgCount; u2_index++ )
    {
        u2_clearIndex = SecOC_TxPduProcessing[SecOC_Ab_BusId2SecuredMsgIdxLists[u2BusIndex].Ab_TxSecuredMsgIdxList[u2_index]].Ab_MessageTypeIndex;
        
        SchM_Enter_SecOC_CD_FV();
        SecOC_CD_FV_Full_u1TxRenewalFlag[u2_clearIndex] = SECOC_CD_FV_FULL_FALSE;
        SecOC_CD_FV_Full_stTxLast[u2_clearIndex].u4Trip = SECOC_CD_FV_FULL_TRIP_TX_INIT;
        SecOC_CD_FV_Full_stTxLast[u2_clearIndex].u4Msg  = SECOC_CD_FV_FULL_MSG_TX_INIT;
        SecOCStd_MemClr( &SecOC_CD_FV_Full_stTxWork[u2_clearIndex], sizeof(SecOC_CD_FV_Full_LastType) );
        SchM_Exit_SecOC_CD_FV();
    }
#endif
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Full_AryToU4                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptArray     :                                            */
/*               | u4OffsetLen :                                            */
/*               | ptData      :                                            */
/*               | u2DataLen   :                                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_AryToU4
(
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptArray,
    uint32 u4OffsetLen,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptData,
    uint16 u2DataLen
)
{
#if ((SECOC_AB_FULLFV_TRIP_CNT_LENGTH == SECOC_CD_FV_FULL_OEM_TRIP_LEN) \
    && (SECOC_AB_FULLFV_MSG_CNT_LENGTH == SECOC_CD_FV_FULL_OEM_MSG_LEN))

    uint32  u4_workData;
    uint16  u2_index;
    
    u2_index = (uint16)(u4OffsetLen >> SECOC_CD_FV_FULL_BYTESHIFT);
    
    if( u2DataLen == (uint16)SECOC_CD_FV_FULL_OEM_TRIP_LEN )
    {
        u4_workData  = (uint32)ptArray[u2_index]                           << SECOC_CD_FV_FULL_BYTE_2;
        u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] << SECOC_CD_FV_FULL_BYTE_1;
        u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX2];
        
        *ptData = u4_workData;
    }
    else if( u2DataLen == (uint16)SECOC_CD_FV_FULL_OEM_MSG_LEN )
    {
        u4_workData  = (uint32)ptArray[u2_index]                           << SECOC_CD_FV_FULL_BYTE_3;
        u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] << SECOC_CD_FV_FULL_BYTE_2;
        u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX2] << SECOC_CD_FV_FULL_BYTE_1;
        u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX3];
        
        *ptData = u4_workData;
    }
    else
    {
        /* No Processing */
    }
    
#else
    uint32  u4_workData = 0UL;
    uint32  u4_sftData;
    uint16  u2_index;
    uint16  u2_byteSurplus;
    uint16  u2_sftDataLen;
    
    u2_index = (uint16)(u4OffsetLen >> SECOC_CD_FV_FULL_BYTESHIFT);
    u2_byteSurplus = (uint16)(u4OffsetLen & (uint32)SECOC_CD_FV_FULL_BYTESURPLUS);
    
    if( u2_byteSurplus == (uint16)0U )
    {
        if( u2DataLen > SECOC_CD_FV_FULL_BYTE_3 )
        {
            u4_workData  = (uint32)ptArray[u2_index]                           << SECOC_CD_FV_FULL_BYTE_3;
            u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] << SECOC_CD_FV_FULL_BYTE_2;
            u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX2] << SECOC_CD_FV_FULL_BYTE_1;
            u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX3];
        }
        else if( u2DataLen > SECOC_CD_FV_FULL_BYTE_2 )
        {
            u4_workData  = (uint32)ptArray[u2_index]                           << SECOC_CD_FV_FULL_BYTE_3;
            u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] << SECOC_CD_FV_FULL_BYTE_2;
            u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX2] << SECOC_CD_FV_FULL_BYTE_1;
        }
        else if( u2DataLen > SECOC_CD_FV_FULL_BYTE_1 )
        {
            u4_workData  = (uint32)ptArray[u2_index]                           << SECOC_CD_FV_FULL_BYTE_3;
            u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] << SECOC_CD_FV_FULL_BYTE_2;
        }
        else if( u2DataLen > SECOC_CD_FV_FULL_BYTE_0 )
        {
            u4_workData  = (uint32)ptArray[u2_index]                           << SECOC_CD_FV_FULL_BYTE_3;
        }
        else
        {
            /* No Processing */
        }
    }
    else if( u2DataLen > SECOC_CD_FV_FULL_BYTE_0 )
    {
        u4_sftData = (uint32)ptArray[u2_index] << (SECOC_CD_FV_FULL_BYTE_3 + u2_byteSurplus);
        
        if( u2DataLen > (SECOC_CD_FV_FULL_BYTE_1 - u2_byteSurplus) )
        {
            u2_sftDataLen = u2DataLen - (SECOC_CD_FV_FULL_BYTE_1 - u2_byteSurplus);
            
            if( u2_sftDataLen > SECOC_CD_FV_FULL_BYTE_3 )
            {
                u4_workData  = (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] << SECOC_CD_FV_FULL_BYTE_3;
                u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX2] << SECOC_CD_FV_FULL_BYTE_2;
                u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX3] << SECOC_CD_FV_FULL_BYTE_1;
                u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX4];
            }
            else if( u2_sftDataLen > SECOC_CD_FV_FULL_BYTE_2 )
            {
                u4_workData  = (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] << SECOC_CD_FV_FULL_BYTE_3;
                u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX2] << SECOC_CD_FV_FULL_BYTE_2;
                u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX3] << SECOC_CD_FV_FULL_BYTE_1;
            }
            else if( u2_sftDataLen > SECOC_CD_FV_FULL_BYTE_1 )
            {
                u4_workData  = (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] << SECOC_CD_FV_FULL_BYTE_3;
                u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX2] << SECOC_CD_FV_FULL_BYTE_2;
            }
            else
            {
                u4_workData  = (uint32)ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] << SECOC_CD_FV_FULL_BYTE_3;
            }
        }
        
        u4_workData >>= (SECOC_CD_FV_FULL_BYTE_1 - u2_byteSurplus);
        u4_workData |= u4_sftData;
    }
    else
    {
        /* No Processing */
    }
    
    if( u4_workData != 0UL )
    {
        u4_workData >>= (SECOC_CD_FV_FULL_BYTE_4 - u2DataLen);
        *ptData = u4_workData;
    }
    else
    {
        *ptData = 0UL;
    }
    
#endif
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Full_U4ToAry                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u4Data      :                                            */
/*               | u2DataLen   :                                            */
/*               | ptArray     :                                            */
/*               | u4OffsetLen :                                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_U4ToAry
(
    uint32 u4Data,
    uint16 u2DataLen,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptArray,
    uint32 u4OffsetLen
)
{
#if ((SECOC_AB_FULLFV_TRIP_CNT_LENGTH == SECOC_CD_FV_FULL_OEM_TRIP_LEN) \
    && (SECOC_AB_FULLFV_MSG_CNT_LENGTH == SECOC_CD_FV_FULL_OEM_MSG_LEN))

    uint16  u2_index;
    
    u2_index = (uint16)(u4OffsetLen >> SECOC_CD_FV_FULL_BYTESHIFT);
    
    if( u2DataLen == (uint16)SECOC_CD_FV_FULL_OEM_TRIP_LEN )
    {
        ptArray[u2_index]                           = (uint8)( (u4Data >> SECOC_CD_FV_FULL_BYTE_2) & SECOC_CD_FV_FULL_MSK_8BIT );
        ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] = (uint8)( (u4Data >> SECOC_CD_FV_FULL_BYTE_1) & SECOC_CD_FV_FULL_MSK_8BIT );
        ptArray[u2_index + SECOC_CD_FV_FULL_INDEX2] = (uint8)( u4Data & SECOC_CD_FV_FULL_MSK_8BIT );
    }
    else if( u2DataLen == (uint16)SECOC_CD_FV_FULL_OEM_MSG_LEN )
    {
        ptArray[u2_index]                           = (uint8)(u4Data >> SECOC_CD_FV_FULL_BYTE_3);
        ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] = (uint8)( (u4Data >> SECOC_CD_FV_FULL_BYTE_2) & SECOC_CD_FV_FULL_MSK_8BIT );
        ptArray[u2_index + SECOC_CD_FV_FULL_INDEX2] = (uint8)( (u4Data >> SECOC_CD_FV_FULL_BYTE_1) & SECOC_CD_FV_FULL_MSK_8BIT );
        ptArray[u2_index + SECOC_CD_FV_FULL_INDEX3] = (uint8)( u4Data & SECOC_CD_FV_FULL_MSK_8BIT );
    }
    else
    {
        /* No Processing */
    }
    
#else
    uint32  u4_sftData;
    uint16  u2_index;
    uint16  u2_byteSurplus;
    uint16  u2_sftDataLen;
    
    u2_index = (uint16)(u4OffsetLen >> SECOC_CD_FV_FULL_BYTESHIFT);
    u2_byteSurplus = (uint16)(u4OffsetLen & (uint32)SECOC_CD_FV_FULL_BYTESURPLUS);
    
    if( u2DataLen == (uint16)0U )
    {
        /* No Processing */
    }
    else if( SECOC_CD_FV_FULL_BYTE_4 > u2DataLen )
    {
        u4_sftData = u4Data << (SECOC_CD_FV_FULL_BYTE_4 - u2DataLen);
    }
    else
    {
        u4_sftData = u4Data;
    }
    
    if( u2_byteSurplus == (uint16)0U )
    {
        if( u2DataLen > SECOC_CD_FV_FULL_BYTE_3 )
        {
            ptArray[u2_index]                           = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_3);
            ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_2);
            ptArray[u2_index + SECOC_CD_FV_FULL_INDEX2] = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_1);
            ptArray[u2_index + SECOC_CD_FV_FULL_INDEX3] = (uint8)u4_sftData;
        }
        else if( u2DataLen > SECOC_CD_FV_FULL_BYTE_2 )
        {
            ptArray[u2_index]                           = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_3);
            ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_2);
            ptArray[u2_index + SECOC_CD_FV_FULL_INDEX2] = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_1);
        }
        else if( u2DataLen > SECOC_CD_FV_FULL_BYTE_1 )
        {
            ptArray[u2_index]                           = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_3);
            ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_2);
        }
        else if( u2DataLen > SECOC_CD_FV_FULL_BYTE_0 )
        {
            ptArray[u2_index]                           = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_3);
        }
        else
        {
            /* No Processing */
        }
    }
    else if( u2DataLen > SECOC_CD_FV_FULL_BYTE_0 )
    {
        u4_sftData >>= (SECOC_CD_FV_FULL_BYTE_3 + u2_byteSurplus);
        ptArray[u2_index] |= (uint8)u4_sftData;
        
        if( u2DataLen > (SECOC_CD_FV_FULL_BYTE_1 - u2_byteSurplus) )
        {
            u4_sftData = u4Data << (SECOC_CD_FV_FULL_BYTE_1 - u2_byteSurplus);
            u4_sftData <<= (SECOC_CD_FV_FULL_BYTE_4 - u2DataLen);
            u2_sftDataLen = u2DataLen - (SECOC_CD_FV_FULL_BYTE_1 - u2_byteSurplus);
            
            if( u2_sftDataLen > SECOC_CD_FV_FULL_BYTE_3 )
            {
                ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_3);
                ptArray[u2_index + SECOC_CD_FV_FULL_INDEX2] = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_2);
                ptArray[u2_index + SECOC_CD_FV_FULL_INDEX3] = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_1);
                ptArray[u2_index + SECOC_CD_FV_FULL_INDEX4] = (uint8)u4_sftData;
            }
            else if( u2_sftDataLen > SECOC_CD_FV_FULL_BYTE_2 )
            {
                ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_3);
                ptArray[u2_index + SECOC_CD_FV_FULL_INDEX2] = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_2);
                ptArray[u2_index + SECOC_CD_FV_FULL_INDEX3] = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_1);
            }
            else if( u2_sftDataLen > SECOC_CD_FV_FULL_BYTE_1 )
            {
                ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_3);
                ptArray[u2_index + SECOC_CD_FV_FULL_INDEX2] = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_2);
            }
            else
            {
                ptArray[u2_index + SECOC_CD_FV_FULL_INDEX1] = (uint8)(u4_sftData >> SECOC_CD_FV_FULL_BYTE_3);
            }
        }
    }
    else
    {
        /* No Processing */
    }
    
#endif
    
    return ;
}

#define SECOC_STOP_SEC_CD_FV_CODE
#include <SecOC_MemMap.h>

#endif /* SECOC_AB_BUS_FULL_MAX */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/*  v2-1-0     :2023/08/23                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
