/* SecOC_CD_FV_Trunc_c_v2-1-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC_CD_FV/Trunc/CODE                                     */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SchM_SecOC.h>
#include <SecOCStd_String.h>
#include <SecOCStd_Util.h>
#include "../inc/SecOC_CD_FV_Trunc.h"

#if (SECOC_AB_BUS_TRUNC_MAX > 0U)

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define SECOC_CD_FV_TRUNC_TRIP_MSK  ((1UL << SECOC_AB_TRIP_CNT_LENGTH)  - 1UL)
#define SECOC_CD_FV_TRUNC_RESET_MSK ((1UL << SECOC_AB_RESET_CNT_LENGTH) - 1UL)
#define SECOC_CD_FV_TRUNC_MSG_MSK   ((1UL << SECOC_AB_MSG_CNT_LENGTH)   - 1UL)
#define SECOC_CD_FV_TRUNC_R_FLG_MSK ((1UL << SECOC_AB_RESET_FLAG_LENGTH) - 1UL)

#define SECOC_CD_FV_TRUNC_TRIP_MAX  (SECOC_CD_FV_TRUNC_TRIP_MSK)
#define SECOC_CD_FV_TRUNC_RESET_MAX (SECOC_CD_FV_TRUNC_RESET_MSK)
#define SECOC_CD_FV_TRUNC_MSG_MAX   (SECOC_CD_FV_TRUNC_MSG_MSK)

#define SECOC_CD_FV_TRUNC_FULL_LEN  (SECOC_AB_TRIP_CNT_LENGTH + SECOC_AB_RESET_CNT_LENGTH + SECOC_AB_MSG_CNT_LENGTH + SECOC_AB_RESET_FLAG_LENGTH)
#define SECOC_CD_FV_TRUNC_SYNC_LEN  (SECOC_AB_TRIP_CNT_LENGTH + SECOC_AB_RESET_CNT_LENGTH)

#define SECOC_CD_FV_TRUNC_OEM_TRIP_LEN  (16U)
#define SECOC_CD_FV_TRUNC_OEM_RESET_LEN (20U)
#define SECOC_CD_FV_TRUNC_OEM_MSG_LEN   (8U)
#define SECOC_CD_FV_TRUNC_OEM_RFLG_LEN  (2U)
#define SECOC_CD_FV_TRUNC_OEM_TXFV_LEN  (4U)

#define SECOC_CD_FV_TRUNC_MST_TRIP_INIT (1UL)
#define SECOC_CD_FV_TRUNC_TX_MSG_INIT   (1U)

#define SECOC_CD_FV_TRUNC_MSK_BASE  (1UL)
#define SECOC_CD_FV_TRUNC_MSK_SUB   (1UL)
#define SECOC_CD_FV_TRUNC_ADD_BASE  (1UL)

#define SECOC_CD_FV_TRUNC_BYTE_0    ((uint16)0U)    /* 0bit equal 0byte */
#define SECOC_CD_FV_TRUNC_BYTE_1    ((uint16)8U)    /* 8bit equal 1byte */
#define SECOC_CD_FV_TRUNC_BYTE_2    ((uint16)16U)   /* 16bit equal 2byte */
#define SECOC_CD_FV_TRUNC_BYTE_3    ((uint16)24U)   /* 24bit equal 3byte */
#define SECOC_CD_FV_TRUNC_BYTE_4    ((uint16)32U)   /* 32bit equal 3byte */
#define SECOC_CD_FV_TRUNC_BYTESURPLUS   (0x07U)
#define SECOC_CD_FV_TRUNC_BYTESHIFT     (3U)
#define SECOC_CD_FV_TRUNC_BITSFT_2  (2U)
#define SECOC_CD_FV_TRUNC_BITSFT_4  (4U)
#define SECOC_CD_FV_TRUNC_BITSFT_6  (6U)
#define SECOC_CD_FV_TRUNC_BITSFT_12 (12U)
#define SECOC_CD_FV_TRUNC_MSK_8BIT  (0x000000FFUL)
#define SECOC_CD_FV_TRUNC_MSK_2BIT  (0x00000003UL)

#define SECOC_CD_FV_TRUNC_RXPTN0    ((uint8)0U)
#define SECOC_CD_FV_TRUNC_RXPTN1    ((uint8)1U)
#define SECOC_CD_FV_TRUNC_RXPTN2    ((uint8)2U)
#define SECOC_CD_FV_TRUNC_RXPTN3    ((uint8)3U)
#define SECOC_CD_FV_TRUNC_RXPTN4    ((uint8)4U)
#define SECOC_CD_FV_TRUNC_RXPTNMAX  ((uint8)5U)

#define SECOC_CD_FV_TRUNC_RXPTN1_NUM    (1UL)
#define SECOC_CD_FV_TRUNC_RXPTN2_NUM    (1UL)
#define SECOC_CD_FV_TRUNC_RXPTN3_NUM    (2UL)
#define SECOC_CD_FV_TRUNC_RXPTN4_NUM    (2UL)

#define SECOC_CD_FV_TRUNC_INDEX0    ((uint16)0U)
#define SECOC_CD_FV_TRUNC_INDEX1    ((uint16)1U)
#define SECOC_CD_FV_TRUNC_INDEX2    ((uint16)2U)
#define SECOC_CD_FV_TRUNC_INDEX3    ((uint16)3U)
#define SECOC_CD_FV_TRUNC_INDEX4    ((uint16)4U)
#define SECOC_CD_FV_TRUNC_INDEX5    ((uint16)5U)

#define SECOC_CD_FV_TRUNC_RESERVE   (3)

#define SECOC_CD_FV_TRUNC_FALSE     ((uint8)0x5AU)
#define SECOC_CD_FV_TRUNC_TRUE      ((uint8)0xA5U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    uint32  u4Trip;
    uint32  u4Reset;
    uint16  u2Msg;
    uint8   u1ResetFlag;
    uint8   u1Length;
} SecOC_CD_FV_Trunc_InfoType;

typedef struct {
    uint32  u4Trip;
    uint32  u4Reset;
} SecOC_CD_FV_Trunc_NewType;

typedef struct {
    uint32  u4Trip;
    uint32  u4Reset;
    uint16  u2Msg;
    uint16  u2Reserve;
} SecOC_CD_FV_Trunc_LastType;

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_RX_PDU_TRUNCFV_MAX > 0U))
typedef struct {
    uint32  u4TxFvMsgLen;
    uint32  u4TxFvRFlgLen;
    uint32  u4NewReset;
    uint16  u2Attempt;
    uint16  u2Pattern;
    boolean bUpDigit;
    uint8   u1Reserve[SECOC_CD_FV_TRUNC_RESERVE];
} SecOC_CD_FV_Trunc_RxWorkType;
#endif

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CD_FV_CODE
#include <SecOC_MemMap.h>

static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_ClearLast
(
    uint16 u2BusIndex
);
#if !((SECOC_AB_TRIP_CNT_LENGTH == SECOC_CD_FV_TRUNC_OEM_TRIP_LEN) \
     && (SECOC_AB_RESET_CNT_LENGTH == SECOC_CD_FV_TRUNC_OEM_RESET_LEN) \
     && (SECOC_AB_MSG_CNT_LENGTH == SECOC_CD_FV_TRUNC_OEM_MSG_LEN) \
     && (SECOC_AB_RESET_FLAG_LENGTH == SECOC_CD_FV_TRUNC_OEM_RFLG_LEN))
  #if ((SECOC_AB_TRIP_CNT_LENGTH > 0U) || (SECOC_AB_RESET_CNT_LENGTH > 0U) || \
       (SECOC_AB_MSG_CNT_LENGTH > 0U)  || (SECOC_AB_RESET_FLAG_LENGTH > 0U))
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_AryToU4
(
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptArray,
    uint32 u4OffsetLen,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptData,
    uint16 u2DataLen
);
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_U4ToAry
(
    uint32 u4Data,
    uint16 u2DataLen,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptArray,
    uint32 u4OffsetLen
);
  #endif
#endif
#if ((SECOC_AB_TX_PDU_TRUNCFV_MAX > 0U) || (SECOC_AB_RX_PDU_TRUNCFV_MAX > 0U))
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_Ary2St
(
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptArray,
    uint32 u4Length,
    P2VAR(SecOC_CD_FV_Trunc_InfoType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvInfo
);
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_St2Ary
(
    P2CONST(SecOC_CD_FV_Trunc_InfoType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvInfo,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptArray,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptLength
);
#endif
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_Ary2St_Sync
(
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptArray,
    uint32 u4Length,
    P2VAR(SecOC_CD_FV_Trunc_InfoType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvInfo
);
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_St2Ary_Sync
(
    P2CONST(SecOC_CD_FV_Trunc_InfoType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvInfo,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptArray,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptLength
);
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_RX_PDU_TRUNCFV_MAX > 0U))
static FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_BuildVerifyFv
(
    P2CONST(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex,
    P2CONST(SecOC_CD_FV_Trunc_InfoType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptTxFv,
    uint16 u2Attempt,
    P2VAR(SecOC_CD_FV_Trunc_LastType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptWork
);
static FUNC(boolean, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_ResetFlgComp
(
    P2CONST(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex,
    P2CONST(SecOC_CD_FV_Trunc_InfoType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptTxFv,
    P2VAR(SecOC_CD_FV_Trunc_RxWorkType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptRxWork
);
static FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_TripResetComp
(
    P2CONST(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex,
    P2CONST(SecOC_CD_FV_Trunc_InfoType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptTxFv,
    P2CONST(SecOC_CD_FV_Trunc_RxWorkType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptRxWork,
    P2VAR(SecOC_CD_FV_Trunc_LastType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptWork
);
#endif

#define SECOC_STOP_SEC_CD_FV_CODE
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CD_FV_VAR_NO_INIT
#include <SecOC_MemMap.h>

static VAR(SecOC_CD_FV_Trunc_NewType, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Trunc_stNew[SECOC_AB_BUS_TRUNC_MAX];
static VAR(SecOC_CD_FV_Trunc_NewType, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Trunc_stNewWork[SECOC_AB_BUS_TRUNC_MAX];
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
static VAR(SecOC_CD_FV_Trunc_NewType, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Trunc_stNewRedundant[SECOC_AB_BUS_TRUNC_MAX];
#endif /* SECOC_AB_RAM_ERROR_CHK */
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
static VAR(uint8, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Trunc_u1NewRenewalFlag[SECOC_AB_BUS_TRUNC_MAX];
static VAR(boolean, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Trunc_bWraparound[SECOC_AB_BUS_TRUNC_MAX];
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
static VAR(SecOC_ErrorStatusType, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Trunc_udRamChkResult[SECOC_AB_BUS_TRUNC_MAX];
#endif /* SECOC_AB_RAM_ERROR_CHK */
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_TX_PDU_TRUNCFV_MAX > 0U))
static VAR(SecOC_CD_FV_Trunc_LastType, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Trunc_stTxLast[SECOC_AB_TX_PDU_TRUNCFV_MAX];
static VAR(SecOC_CD_FV_Trunc_LastType, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Trunc_stTxWork[SECOC_AB_TX_PDU_TRUNCFV_MAX];
static VAR(uint8, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Trunc_u1TxRenewalFlag[SECOC_AB_TX_PDU_TRUNCFV_MAX];
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_RX_PDU_TRUNCFV_MAX > 0U))
static VAR(SecOC_CD_FV_Trunc_LastType, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Trunc_stRxLast[SECOC_AB_RX_PDU_TRUNCFV_MAX];
static VAR(SecOC_CD_FV_Trunc_LastType, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Trunc_stRxWork[SECOC_AB_RX_PDU_TRUNCFV_MAX];
static VAR(uint8, SECOC_CD_FV_VAR_NO_INIT) SecOC_CD_FV_Trunc_u1RxRenewalFlag[SECOC_AB_RX_PDU_TRUNCFV_MAX];
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
/* Function Name | SecOC_CD_FV_Trunc_Init                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_Init
(
    void
)
{
    uint16  u2_loop;
    
    SecOCStd_MemClr( &SecOC_CD_FV_Trunc_stNew, sizeof(SecOC_CD_FV_Trunc_stNew) );
    SecOCStd_MemClr( &SecOC_CD_FV_Trunc_stNewWork, sizeof(SecOC_CD_FV_Trunc_stNewWork) );
    
    for( u2_loop = 0U; u2_loop < SecOC_Ab_BusTruncMax; u2_loop++ )
    {
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        SecOC_CD_FV_Trunc_stNewRedundant[u2_loop].u4Trip = ~SecOC_CD_FV_Trunc_stNew[u2_loop].u4Trip;
        SecOC_CD_FV_Trunc_stNewRedundant[u2_loop].u4Reset = ~SecOC_CD_FV_Trunc_stNew[u2_loop].u4Reset;
#endif
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
        SecOC_CD_FV_Trunc_u1NewRenewalFlag[u2_loop] = SECOC_CD_FV_TRUNC_FALSE;
        SecOC_CD_FV_Trunc_bWraparound[u2_loop] = (boolean)FALSE;
#endif
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
        SecOC_CD_FV_Trunc_udRamChkResult[u2_loop] = SECOC_E_NONE;
#endif
#endif /* SECOC_AB_RAM_ERROR_CHK */
    }
    
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_TX_PDU_TRUNCFV_MAX > 0U))
    SecOCStd_MemClr( &SecOC_CD_FV_Trunc_stTxLast[0], sizeof(SecOC_CD_FV_Trunc_stTxLast) );
    SecOCStd_MemClr( &SecOC_CD_FV_Trunc_stTxWork[0], sizeof(SecOC_CD_FV_Trunc_stTxWork) );
    for( u2_loop = 0U; u2_loop < SecOC_Ab_TxPduTruncFvMax; u2_loop++ )
    {
        SecOC_CD_FV_Trunc_u1TxRenewalFlag[u2_loop] = SECOC_CD_FV_TRUNC_FALSE;
    }
#endif
    
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_RX_PDU_TRUNCFV_MAX > 0U))
    SecOCStd_MemClr( &SecOC_CD_FV_Trunc_stRxLast[0], sizeof(SecOC_CD_FV_Trunc_stRxLast) );
    SecOCStd_MemClr( &SecOC_CD_FV_Trunc_stRxWork[0], sizeof(SecOC_CD_FV_Trunc_stRxWork) );
    for( u2_loop = 0U; u2_loop < SecOC_Ab_RxPduTruncFvMax; u2_loop++ )
    {
        SecOC_CD_FV_Trunc_u1RxRenewalFlag[u2_loop] = SECOC_CD_FV_TRUNC_FALSE;
    }
#endif
    
    return ;
}

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_ReadTx                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | ptFv    :                                                */
/*               | ptFvLen :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK         : Success                                   */
/*               | E_NOT_OK     : Failure                                   */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_ReadTx
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvLen
)
{
    Std_ReturnType          ud_stdRet = E_NOT_OK;
#if (SECOC_AB_TX_PDU_TRUNCFV_MAX > 0U)
    SecOC_CD_FV_Trunc_InfoType    st_info;
    
    /* Parameters check */
    if( (u2Index < SecOC_Ab_TxPduTruncFvMax)
      && (ptFv != NULL_PTR)
      && (ptFvLen != NULL_PTR)
    #if (SECOC_CD_FV_TRUNC_FULL_LEN > 0U)
      && (*ptFvLen >= SECOC_CD_FV_TRUNC_FULL_LEN)
    #endif
      )
    {
        SchM_Enter_SecOC_CD_FV();
        st_info.u4Trip = SecOC_CD_FV_Trunc_stTxLast[u2Index].u4Trip;
        st_info.u4Reset = SecOC_CD_FV_Trunc_stTxLast[u2Index].u4Reset;
        st_info.u2Msg = SecOC_CD_FV_Trunc_stTxLast[u2Index].u2Msg;
        SchM_Exit_SecOC_CD_FV();
        
        st_info.u1ResetFlag = (uint8)(st_info.u4Reset & SECOC_CD_FV_TRUNC_R_FLG_MSK);
        st_info.u1Length = (uint8)SECOC_CD_FV_TRUNC_FULL_LEN;
        
        SecOC_CD_FV_Trunc_St2Ary( &st_info, ptFv, ptFvLen );
        
        ud_stdRet = E_OK;
    }
#endif
    
    return ud_stdRet;
}
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_ReadRx                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | ptFv    :                                                */
/*               | ptFvLen :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK         : Success                                  */
/*               |  E_NOT_OK     : Failure                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_ReadRx
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvLen
)
{
    Std_ReturnType          ud_stdRet = E_NOT_OK;
#if (SECOC_AB_RX_PDU_TRUNCFV_MAX > 0U)
    SecOC_CD_FV_Trunc_InfoType    st_info;
    
    /* Parameters check */
    if( (u2Index < SecOC_Ab_RxPduTruncFvMax)
      && (ptFv != NULL_PTR)
      && (ptFvLen != NULL_PTR)
    #if (SECOC_CD_FV_TRUNC_FULL_LEN > 0U)
      && (*ptFvLen >= SECOC_CD_FV_TRUNC_FULL_LEN)
    #endif
      )
    {
        SchM_Enter_SecOC_CD_FV();
        st_info.u4Trip = SecOC_CD_FV_Trunc_stRxLast[u2Index].u4Trip;
        st_info.u4Reset = SecOC_CD_FV_Trunc_stRxLast[u2Index].u4Reset;
        st_info.u2Msg = SecOC_CD_FV_Trunc_stRxLast[u2Index].u2Msg;
        SchM_Exit_SecOC_CD_FV();
        
        st_info.u1ResetFlag = (uint8)(st_info.u4Reset & SECOC_CD_FV_TRUNC_R_FLG_MSK);
        st_info.u1Length = (uint8)SECOC_CD_FV_TRUNC_FULL_LEN;
        
        SecOC_CD_FV_Trunc_St2Ary( &st_info, ptFv, ptFvLen );
        
        ud_stdRet = E_OK;
    }
#endif
    
    return ud_stdRet;
}
#endif

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_ReadSync                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | ptFv    :                                                */
/*               | ptFvLen :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK         : Success                                  */
/*               |  E_NOT_OK     : Failure                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_ReadSync
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvLen
)
{
    Std_ReturnType          ud_stdRet = E_NOT_OK;
    SecOC_CD_FV_Trunc_InfoType    st_info;
    
    /* Parameters check */
    if( (u2Index < SecOC_Ab_BusTruncMax)
      && (ptFv != NULL_PTR )
      && (ptFvLen != NULL_PTR)
#if (SECOC_CD_FV_TRUNC_SYNC_LEN > 0U)
      && (*ptFvLen >= SECOC_CD_FV_TRUNC_SYNC_LEN)
#endif
      )
    {
        SchM_Enter_SecOC_CD_FV();
        st_info.u4Trip = SecOC_CD_FV_Trunc_stNew[u2Index].u4Trip;
        st_info.u4Reset = SecOC_CD_FV_Trunc_stNew[u2Index].u4Reset;
        SchM_Exit_SecOC_CD_FV();
        
        st_info.u2Msg = 0U;
        st_info.u1ResetFlag = 0U;
        st_info.u1Length = (uint8)SECOC_CD_FV_TRUNC_SYNC_LEN;
        
        SecOC_CD_FV_Trunc_St2Ary_Sync( &st_info, ptFv, ptFvLen );
        
        ud_stdRet = E_OK;
    }
    
    return ud_stdRet;
}

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_WriteTx                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | ptFv    :                                                */
/*               | u4FvLen :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK         : Success                                  */
/*               |  E_NOT_OK     : Failure                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_WriteTx
(
    uint16 u2Index,
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    uint32 u4FvLen
)
{
    Std_ReturnType          ud_stdRet = E_NOT_OK;
#if (SECOC_AB_TX_PDU_TRUNCFV_MAX > 0U)
    SecOC_CD_FV_Trunc_InfoType    st_info;
    
    /* Parameters check */
    if( (u2Index < SecOC_Ab_TxPduTruncFvMax)
      && (ptFv != NULL_PTR)
      && (u4FvLen == SECOC_CD_FV_TRUNC_FULL_LEN) )
    {
        SecOC_CD_FV_Trunc_Ary2St( ptFv, u4FvLen, &st_info );
        
        SchM_Enter_SecOC_CD_FV();
        SecOC_CD_FV_Trunc_u1TxRenewalFlag[u2Index] = SECOC_CD_FV_TRUNC_FALSE;
        SecOC_CD_FV_Trunc_stTxLast[u2Index].u4Trip  = st_info.u4Trip;
        SecOC_CD_FV_Trunc_stTxLast[u2Index].u4Reset = st_info.u4Reset;
        SecOC_CD_FV_Trunc_stTxLast[u2Index].u2Msg   = st_info.u2Msg;
        SecOC_CD_FV_Trunc_stTxWork[u2Index].u4Trip  = st_info.u4Trip;
        SecOC_CD_FV_Trunc_stTxWork[u2Index].u4Reset = st_info.u4Reset;
        SecOC_CD_FV_Trunc_stTxWork[u2Index].u2Msg   = st_info.u2Msg;
        SchM_Exit_SecOC_CD_FV();
        
        ud_stdRet = E_OK;
    }
#endif
    
    return ud_stdRet;
}
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_WriteRx                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | ptFv    :                                                */
/*               | u4FvLen :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK         : Success                                  */
/*               |  E_NOT_OK     : Failure                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_WriteRx
(
    uint16 u2Index,
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    uint32 u4FvLen
)
{
    Std_ReturnType          ud_stdRet = E_NOT_OK;
#if (SECOC_AB_RX_PDU_TRUNCFV_MAX > 0U)
    SecOC_CD_FV_Trunc_InfoType    st_info;
    
    /* Parameters check */
    if( (u2Index < SecOC_Ab_RxPduTruncFvMax)
      && (ptFv != NULL_PTR)
      && (u4FvLen == SECOC_CD_FV_TRUNC_FULL_LEN) )
    {
        SecOC_CD_FV_Trunc_Ary2St( ptFv, u4FvLen, &st_info );
        
        SchM_Enter_SecOC_CD_FV();
        SecOC_CD_FV_Trunc_u1RxRenewalFlag[u2Index] = SECOC_CD_FV_TRUNC_FALSE;
        SecOC_CD_FV_Trunc_stRxLast[u2Index].u4Trip  = st_info.u4Trip;
        SecOC_CD_FV_Trunc_stRxLast[u2Index].u4Reset = st_info.u4Reset;
        SecOC_CD_FV_Trunc_stRxLast[u2Index].u2Msg   = st_info.u2Msg;
        SecOC_CD_FV_Trunc_stRxWork[u2Index].u4Trip  = st_info.u4Trip;
        SecOC_CD_FV_Trunc_stRxWork[u2Index].u4Reset = st_info.u4Reset;
        SecOC_CD_FV_Trunc_stRxWork[u2Index].u2Msg   = st_info.u2Msg;
        SchM_Exit_SecOC_CD_FV();
        
        ud_stdRet = E_OK;
    }
#endif
    
    return ud_stdRet;
}
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_WriteTxSync                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | ptFv    :                                                */
/*               | u4FvLen :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK         : Success                                  */
/*               |  E_NOT_OK     : Failure                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_WriteTxSync
(
    uint16 u2Index,
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    uint32 u4FvLen
)
{
    Std_ReturnType          ud_stdRet = E_NOT_OK;
    SecOC_CD_FV_Trunc_InfoType    st_info;
    
    /* Parameters check */
    if( (u2Index < SecOC_Ab_BusTruncMax)
      && (ptFv != NULL_PTR)
      && (u4FvLen == SECOC_CD_FV_TRUNC_SYNC_LEN)
      )
    {
        SecOC_CD_FV_Trunc_Ary2St_Sync( ptFv, u4FvLen, &st_info );
        
        SchM_Enter_SecOC_CD_FV();
        SecOC_CD_FV_Trunc_stNew[u2Index].u4Trip  = st_info.u4Trip;
        SecOC_CD_FV_Trunc_stNew[u2Index].u4Reset = st_info.u4Reset;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        SecOC_CD_FV_Trunc_stNewRedundant[u2Index].u4Trip  = ~st_info.u4Trip;
        SecOC_CD_FV_Trunc_stNewRedundant[u2Index].u4Reset = ~st_info.u4Reset;
#endif

        SchM_Exit_SecOC_CD_FV();
        
        ud_stdRet = E_OK;
    }
    
    return ud_stdRet;
}
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_WriteRxSync                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index :                                                */
/*               | ptFv    :                                                */
/*               | u4FvLen :                                                */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK         : Success                                  */
/*               |  E_NOT_OK     : Failure                                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_WriteRxSync
(
    uint16 u2Index,
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    uint32 u4FvLen
)
{
    Std_ReturnType          ud_stdRet = E_NOT_OK;
    SecOC_CD_FV_Trunc_InfoType    st_info;
    
    /* Parameters check */
    if( (u2Index < SecOC_Ab_BusTruncMax)
      && (ptFv != NULL_PTR)
      && (u4FvLen == SECOC_CD_FV_TRUNC_SYNC_LEN) )
    {
        SecOC_CD_FV_Trunc_Ary2St_Sync( ptFv, u4FvLen, &st_info );
        
        SchM_Enter_SecOC_CD_FV();
        SecOC_CD_FV_Trunc_u1NewRenewalFlag[u2Index] = SECOC_CD_FV_TRUNC_FALSE;
        SecOC_CD_FV_Trunc_stNew[u2Index].u4Trip  = st_info.u4Trip;
        SecOC_CD_FV_Trunc_stNew[u2Index].u4Reset = st_info.u4Reset;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        SecOC_CD_FV_Trunc_stNewRedundant[u2Index].u4Trip  = ~st_info.u4Trip;
        SecOC_CD_FV_Trunc_stNewRedundant[u2Index].u4Reset = ~st_info.u4Reset;
#endif
        SecOC_CD_FV_Trunc_stNewWork[u2Index].u4Trip  = st_info.u4Trip;
        SecOC_CD_FV_Trunc_stNewWork[u2Index].u4Reset = st_info.u4Reset;
        SchM_Exit_SecOC_CD_FV();
        
        ud_stdRet = E_OK;
    }
    
    return ud_stdRet;
}
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_GetTx                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptIndex   :                                              */
/*               | ptFullFv  :                                              */
/*               | ptTruncFv :                                              */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK               : Success                            */
/*               |  E_NOT_OK           : Failure(Skip)                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_GetTx
(
    P2CONST(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex,
    P2VAR(SecOC_CD_FV_InOutType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFullFv,
    P2VAR(SecOC_CD_FV_InOutType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptTruncFv
)
{
    Std_ReturnType          ud_stdRet = E_NOT_OK;
#if (SECOC_AB_TX_PDU_TRUNCFV_MAX > 0U)
    SecOC_CD_FV_Trunc_InfoType    st_info;
    SecOC_CD_FV_Trunc_NewType     st_new;
    SecOC_CD_FV_Trunc_LastType    st_work;
    
    /* Parameters check */
    if( (ptIndex->u2FvIndexFvType < SecOC_Ab_BusTruncMax)
      && (ptIndex->u2FvIndexLast < SecOC_Ab_TxPduTruncFvMax)
      && (ptFullFv->ptFv != NULL_PTR)
      && (ptFullFv->ptFvLen != NULL_PTR)
      && (ptTruncFv->ptFv != NULL_PTR)
      && (ptTruncFv->ptFvLen != NULL_PTR)
    #if (SECOC_CD_FV_TRUNC_FULL_LEN > 0U)
      && (*(ptFullFv->ptFvLen) >= SECOC_CD_FV_TRUNC_FULL_LEN)
    #endif
      )
    {
        #if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        if( SecOC_CD_FV_Trunc_udRamChkResult[ptIndex->u2FvIndexFvType] == SECOC_E_NONE )
        {
        #endif /* SECOC_AB_RAM_ERROR_CHK */
            SchM_Enter_SecOC_CD_FV();
            SecOC_CD_FV_Trunc_u1TxRenewalFlag[ptIndex->u2FvIndexLast] = SECOC_CD_FV_TRUNC_TRUE;
            /* Copy */
            st_new.u4Trip = SecOC_CD_FV_Trunc_stNew[ptIndex->u2FvIndexFvType].u4Trip;
            st_new.u4Reset = SecOC_CD_FV_Trunc_stNew[ptIndex->u2FvIndexFvType].u4Reset;
            st_work.u4Trip  = SecOC_CD_FV_Trunc_stTxLast[ptIndex->u2FvIndexLast].u4Trip;
            st_work.u4Reset = SecOC_CD_FV_Trunc_stTxLast[ptIndex->u2FvIndexLast].u4Reset;
            st_work.u2Msg   = SecOC_CD_FV_Trunc_stTxLast[ptIndex->u2FvIndexLast].u2Msg;
            SchM_Exit_SecOC_CD_FV();
            
            ud_stdRet = E_OK;
            
            if( (st_new.u4Trip == st_work.u4Trip)
              && (st_new.u4Reset == st_work.u4Reset) )
            {
                /* Reset counter max check */
    #if (SECOC_AB_RESET_CNT_LENGTH > 0U)
                if( st_work.u4Reset >= SECOC_CD_FV_TRUNC_RESET_MAX )
                {
    #endif
                    st_work.u2Msg = (uint16)SECOC_CD_FV_TRUNC_MSG_MAX;
    #if (SECOC_AB_RESET_CNT_LENGTH > 0U)
                }
    #endif
                
                /* Message counter increment */
    #if (SECOC_AB_MSG_CNT_LENGTH > 0U)
                if( st_work.u2Msg < (uint16)SECOC_CD_FV_TRUNC_MSG_MAX )
                {
                    st_work.u2Msg++;
                }
    #endif
            }
            else
            {
                /* Set trip and reset counter */
                st_work.u4Trip = st_new.u4Trip;
                st_work.u4Reset = st_new.u4Reset;
                
                /* Set message counter */
    #if (SECOC_AB_RESET_CNT_LENGTH > 0U)
                if( st_work.u4Reset < SECOC_CD_FV_TRUNC_RESET_MAX )
                {
                    st_work.u2Msg = SECOC_CD_FV_TRUNC_TX_MSG_INIT;
                }
                else
                {
    #endif
                    st_work.u2Msg = (uint16)SECOC_CD_FV_TRUNC_MSG_MAX;
    #if (SECOC_AB_RESET_CNT_LENGTH > 0U)
                }
    #endif
            }
            
            SchM_Enter_SecOC_CD_FV();
            /* Copy to Work */
            if ( SecOC_CD_FV_Trunc_u1TxRenewalFlag[ptIndex->u2FvIndexLast] == SECOC_CD_FV_TRUNC_TRUE )
            {
                SecOC_CD_FV_Trunc_stTxWork[ptIndex->u2FvIndexLast].u4Trip  = st_work.u4Trip;
                SecOC_CD_FV_Trunc_stTxWork[ptIndex->u2FvIndexLast].u4Reset = st_work.u4Reset;
                SecOC_CD_FV_Trunc_stTxWork[ptIndex->u2FvIndexLast].u2Msg   = st_work.u2Msg;
            }
            SchM_Exit_SecOC_CD_FV();
            
            st_info.u4Trip = st_work.u4Trip;
            st_info.u4Reset = st_work.u4Reset;
            st_info.u2Msg = st_work.u2Msg;
            st_info.u1ResetFlag = (uint8)(st_info.u4Reset & SECOC_CD_FV_TRUNC_R_FLG_MSK);
            
            /* Set Full FV */
            if( *(ptFullFv->ptFvLen) > SECOC_CD_FV_TRUNC_FULL_LEN )
            {
                *(ptFullFv->ptFvLen) = SECOC_CD_FV_TRUNC_FULL_LEN;
            }
            st_info.u1Length = (uint8)(*(ptFullFv->ptFvLen));
            SecOC_CD_FV_Trunc_St2Ary( &st_info, ptFullFv->ptFv, ptFullFv->ptFvLen );
            
            /* Set Tx FV */
            if( *(ptTruncFv->ptFvLen) > SECOC_CD_FV_TRUNC_FULL_LEN )
            {
                *(ptTruncFv->ptFvLen) = SECOC_CD_FV_TRUNC_FULL_LEN;
            }
            st_info.u1Length = (uint8)(*(ptTruncFv->ptFvLen));
            SecOC_CD_FV_Trunc_St2Ary( &st_info, ptTruncFv->ptFv, ptTruncFv->ptFvLen );
        #if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        }
        #endif /* SECOC_AB_RAM_ERROR_CHK */
    }
#endif
    
    return ud_stdRet;
}
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_GetRx                                  */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptIndex   :                                              */
/*               | ptTruncFv :                                              */
/*               | u2Attempt :                                              */
/*               | ptFullFv  :                                              */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK               : Success                            */
/*               |  E_NOT_OK           : Failure(Skip)                      */
/*               |  SECOC_E_FV_NOT_OK  : FV NG                              */
/*               |  SECOC_E_RETRY      : Retry                              */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_GetRx
(
    P2CONST(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex,
    P2CONST(SecOC_CD_FV_InType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptTruncFv,
    uint16 u2Attempt,
    P2VAR(SecOC_CD_FV_InOutType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFullFv
)
{
    Std_ReturnType          ud_stdRet = E_NOT_OK;
#if (SECOC_AB_RX_PDU_TRUNCFV_MAX > 0U)
    SecOC_CD_FV_Trunc_InfoType    st_info;
    SecOC_CD_FV_Trunc_LastType    st_work;
    
    SecOCStd_MemClr( &st_info, sizeof(SecOC_CD_FV_Trunc_InfoType) );
    SecOCStd_MemClr( &st_work, sizeof(SecOC_CD_FV_Trunc_LastType) );

    /* Parameters check */
    if( (ptIndex->u2FvIndexFvType < SecOC_Ab_BusTruncMax)
      && (ptIndex->u2FvIndexLast < SecOC_Ab_RxPduTruncFvMax)
      && (ptTruncFv->ptFv != NULL_PTR)
      && (ptFullFv->ptFv != NULL_PTR)
      && (ptFullFv->ptFvLen != NULL_PTR)
    #if (SECOC_CD_FV_TRUNC_FULL_LEN > 0U)
      && (*(ptFullFv->ptFvLen) >= SECOC_CD_FV_TRUNC_FULL_LEN)
    #endif
      )
    {
        SecOC_CD_FV_Trunc_Ary2St( ptTruncFv->ptFv, ptTruncFv->u4FvLen, &st_info );
        
        /* Build verify freshness value */
        ud_stdRet = SecOC_CD_FV_Trunc_BuildVerifyFv( ptIndex, &st_info, u2Attempt, &st_work );
        
        if( ud_stdRet == (Std_ReturnType)E_OK )
        {
            SchM_Enter_SecOC_CD_FV();
            /* Copy to Work */
            if ( SecOC_CD_FV_Trunc_u1RxRenewalFlag[ptIndex->u2FvIndexLast] == SECOC_CD_FV_TRUNC_TRUE )
            {
                SecOC_CD_FV_Trunc_stRxWork[ptIndex->u2FvIndexLast].u4Trip  = st_work.u4Trip;
                SecOC_CD_FV_Trunc_stRxWork[ptIndex->u2FvIndexLast].u4Reset = st_work.u4Reset;
                SecOC_CD_FV_Trunc_stRxWork[ptIndex->u2FvIndexLast].u2Msg   = st_work.u2Msg;
            }
            SchM_Exit_SecOC_CD_FV();
            
            st_info.u4Trip = st_work.u4Trip;
            st_info.u4Reset = st_work.u4Reset;
            st_info.u2Msg = st_work.u2Msg;
            st_info.u1ResetFlag = (uint8)(st_info.u4Reset & SECOC_CD_FV_TRUNC_R_FLG_MSK);
            
            if( *(ptFullFv->ptFvLen) > SECOC_CD_FV_TRUNC_FULL_LEN )
            {
                *(ptFullFv->ptFvLen) = SECOC_CD_FV_TRUNC_FULL_LEN;
            }
            st_info.u1Length = (uint8)(*(ptFullFv->ptFvLen));
            SecOC_CD_FV_Trunc_St2Ary( &st_info, ptFullFv->ptFv, ptFullFv->ptFvLen );
        }
    }
#endif
    
    return ud_stdRet;
}
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_GetTxSync                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptIndex   :                                              */
/*               | ptFullFv  :                                              */
/*               | ptTruncFv :                                              */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK               : Success                            */
/*               |  E_NOT_OK           : Failure(Skip)                      */
/*               |  SECOC_E_OK_FV_FULL : Success but FV is full.            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_GetTxSync
(
    P2CONST(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex,
    P2VAR(SecOC_CD_FV_InOutType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFullFv,
    P2VAR(SecOC_CD_FV_InOutType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptTruncFv
)
{
    Std_ReturnType          ud_stdRet = E_NOT_OK;
    SecOC_CD_FV_Trunc_InfoType    st_info;
    SecOC_CD_FV_Trunc_NewType     st_new;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
    SecOC_CD_FV_Trunc_NewType     st_new_redundant;
#endif /* SECOC_AB_RAM_ERROR_CHK */
    
    SecOCStd_MemClr( &st_info, sizeof(SecOC_CD_FV_Trunc_InfoType) );

    /* Parameters check */
    if( (ptIndex->u2FvIndexFvType < SecOC_Ab_BusTruncMax)
      && (ptFullFv->ptFv != NULL_PTR)
      && (ptFullFv->ptFvLen != NULL_PTR)
      && (ptTruncFv->ptFv != NULL_PTR)
      && (ptTruncFv->ptFvLen != NULL_PTR)
    #if (SECOC_CD_FV_TRUNC_SYNC_LEN > 0U)
      && (*(ptFullFv->ptFvLen) >= SECOC_CD_FV_TRUNC_SYNC_LEN)
      && (*(ptTruncFv->ptFvLen) >= SECOC_CD_FV_TRUNC_SYNC_LEN)
    #endif
      )
    {
        #if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        if( SecOC_CD_FV_Trunc_udRamChkResult[ptIndex->u2FvIndexFvType] == SECOC_E_NONE )
        {
        #endif  /* SECOC_AB_RAM_ERROR_CHK */
            SchM_Enter_SecOC_CD_FV();
            /* Copy */
            st_new.u4Trip = SecOC_CD_FV_Trunc_stNew[ptIndex->u2FvIndexFvType].u4Trip;
            st_new.u4Reset = SecOC_CD_FV_Trunc_stNew[ptIndex->u2FvIndexFvType].u4Reset;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
            st_new_redundant.u4Trip = SecOC_CD_FV_Trunc_stNewRedundant[ptIndex->u2FvIndexFvType].u4Trip;
            st_new_redundant.u4Reset = SecOC_CD_FV_Trunc_stNewRedundant[ptIndex->u2FvIndexFvType].u4Reset;
#endif  /* SECOC_AB_RAM_ERROR_CHK */
            SchM_Exit_SecOC_CD_FV();

#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)        
            if( (st_new_redundant.u4Trip == ~st_new.u4Trip) && (st_new_redundant.u4Reset == ~st_new.u4Reset) )
            {
#endif  /* SECOC_AB_RAM_ERROR_CHK */
                st_info.u4Trip = st_new.u4Trip;
                st_info.u4Reset = st_new.u4Reset;
                
                /* Set Full FV */
                if( *(ptFullFv->ptFvLen) > SECOC_CD_FV_TRUNC_SYNC_LEN )
                {
                    *(ptFullFv->ptFvLen) = SECOC_CD_FV_TRUNC_SYNC_LEN;
                }
                
                st_info.u1Length = (uint8)(*(ptFullFv->ptFvLen));
                SecOC_CD_FV_Trunc_St2Ary_Sync( &st_info, ptFullFv->ptFv, ptFullFv->ptFvLen );
                
                /* Set Tx FV */
                if( *(ptTruncFv->ptFvLen) > SECOC_CD_FV_TRUNC_SYNC_LEN )
                {
                    *(ptTruncFv->ptFvLen) = SECOC_CD_FV_TRUNC_SYNC_LEN;
                }
                
                st_info.u1Length = (uint8)(*(ptTruncFv->ptFvLen));
                SecOC_CD_FV_Trunc_St2Ary_Sync( &st_info, ptTruncFv->ptFv, ptTruncFv->ptFvLen );
                
                ud_stdRet = E_OK;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
            }
            else
            {
                SecOC_CD_FV_Trunc_udRamChkResult[ptIndex->u2FvIndexFvType] = SECOC_E_RAM_CHECK_FAIL;
            }
        }
#endif /* SECOC_AB_RAM_ERROR_CHK */
    }
    
    return ud_stdRet;
}
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_GetRxSync                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptIndex   :                                              */
/*               | ptTruncFv :                                              */
/*               | u2Attempt :                                              */
/*               | ptFullFv  :                                              */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK              : Success                             */
/*               |  E_NOT_OK          : Failure(Skip)                       */
/*               |  SECOC_E_FV_NOT_OK : FV NG                               */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_GetRxSync
(
    P2CONST(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex,
    P2CONST(SecOC_CD_FV_InType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptTruncFv,
    uint16 u2Attempt,
    P2VAR(SecOC_CD_FV_InOutType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFullFv
)
{
    Std_ReturnType          ud_stdRet = E_NOT_OK;
    SecOC_CD_FV_Trunc_InfoType    st_info;
    boolean                 b_wraparound = (boolean)FALSE;
    SecOC_CD_FV_Trunc_NewType     st_new;
    
    /* Parameters check */
    if( (ptIndex->u2BusIndex < SecOC_Ab_BusMax)
      && (ptIndex->u2FvIndexFvType < SecOC_Ab_BusTruncMax)
      && (ptTruncFv->ptFv != NULL_PTR)
      && (ptFullFv->ptFv != NULL_PTR)
      && (ptFullFv->ptFvLen != NULL_PTR)
#if (SECOC_CD_FV_TRUNC_SYNC_LEN > 0U)
      && (*(ptFullFv->ptFvLen) >= SECOC_CD_FV_TRUNC_SYNC_LEN)
#endif
      )
    {
        /* Sync length and Attempt check */
        if( (ptTruncFv->u4FvLen == SECOC_CD_FV_TRUNC_SYNC_LEN)
          && (u2Attempt == (uint16)0U) )
        {
            SecOC_CD_FV_Trunc_Ary2St_Sync( ptTruncFv->ptFv, ptTruncFv->u4FvLen, &st_info );
            
            SchM_Enter_SecOC_CD_FV();
            SecOC_CD_FV_Trunc_u1NewRenewalFlag[ptIndex->u2FvIndexFvType] = SECOC_CD_FV_TRUNC_TRUE;
            /* Copy */
            st_new.u4Trip = SecOC_CD_FV_Trunc_stNew[ptIndex->u2FvIndexFvType].u4Trip;
            st_new.u4Reset = SecOC_CD_FV_Trunc_stNew[ptIndex->u2FvIndexFvType].u4Reset;
            SchM_Exit_SecOC_CD_FV();
            
            /* Wraparound check */
            if( (st_new.u4Trip >= (SECOC_CD_FV_TRUNC_TRIP_MAX - SecOC_Ab_BusCollection[ptIndex->u2BusIndex].Ab_ClearAcceptanceWindow))
              && (st_info.u4Trip >= SECOC_CD_FV_TRUNC_MST_TRIP_INIT)
              && (st_info.u4Trip <= ((uint32)SecOC_Ab_BusCollection[ptIndex->u2BusIndex].Ab_ClearAcceptanceWindow + SECOC_CD_FV_TRUNC_MST_TRIP_INIT)) )
            {
                b_wraparound = (boolean)TRUE;
            }
            
            /* Freshness Value compare */
            if( ( (st_info.u4Trip > st_new.u4Trip)
                || ( (st_info.u4Trip == st_new.u4Trip)
                  && (st_info.u4Reset > st_new.u4Reset) ) )
              || (b_wraparound == (boolean)TRUE) )
            {
                ud_stdRet = E_OK;
            }
            else if( (st_info.u4Trip == st_new.u4Trip)
              && (st_info.u4Reset == st_new.u4Reset) )
            {
#if ( SECOC_AB_EQUIVALENT_FV_VERIFY == STD_ON )
                ud_stdRet = E_OK;
#else
                ud_stdRet = E_NOT_OK;
#endif
            }
            else
            {
                ud_stdRet = SECOC_E_FV_NOT_OK;
            }
            
            if( ud_stdRet == (Std_ReturnType)E_OK )
            {
                SchM_Enter_SecOC_CD_FV();
                if ( SecOC_CD_FV_Trunc_u1NewRenewalFlag[ptIndex->u2FvIndexFvType] == SECOC_CD_FV_TRUNC_TRUE )
                {
                    SecOC_CD_FV_Trunc_stNewWork[ptIndex->u2FvIndexFvType].u4Trip  = st_info.u4Trip;
                    SecOC_CD_FV_Trunc_stNewWork[ptIndex->u2FvIndexFvType].u4Reset = st_info.u4Reset;
                    SecOC_CD_FV_Trunc_bWraparound[ptIndex->u2FvIndexFvType] = b_wraparound;
                }
                SchM_Exit_SecOC_CD_FV();
                
                if( *(ptFullFv->ptFvLen) > SECOC_CD_FV_TRUNC_SYNC_LEN )
                {
                    *(ptFullFv->ptFvLen) = SECOC_CD_FV_TRUNC_SYNC_LEN;
                }
                SecOC_CD_FV_Trunc_St2Ary_Sync( &st_info, ptFullFv->ptFv, ptFullFv->ptFvLen );
                
                ud_stdRet = E_OK;
            }
        }
        else
        {
            ud_stdRet = SECOC_E_FV_NOT_OK;
        }
    }
    
    return ud_stdRet;
}
#endif

#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_UpdateTx                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index:                                                 */
/*               | bUpdate:                                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK               : Success                            */
/*               |  SECOC_E_OK_FV_FULL : Success but FV is full.            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_UpdateTx
(
    uint16 u2Index,
    boolean bUpdate
)
{
    Std_ReturnType          ud_stdRet = (Std_ReturnType)E_OK;
#if (SECOC_AB_TX_PDU_TRUNCFV_MAX > 0U)
    /* Parameters check */
    if( u2Index < SecOC_Ab_TxPduTruncFvMax )
    {
        if( bUpdate == (boolean)TRUE )
        {
            SchM_Enter_SecOC_CD_FV();
            /* Copy */
            (void)SecOCStd_MemCpy( &SecOC_CD_FV_Trunc_stTxLast[u2Index], &SecOC_CD_FV_Trunc_stTxWork[u2Index], sizeof(SecOC_CD_FV_Trunc_LastType) ); /* no return check required */
            
            /* Check Counter Full */
            if(SecOC_CD_FV_Trunc_stTxLast[u2Index].u2Msg == (uint16)SECOC_CD_FV_TRUNC_MSG_MAX)
            {
                /* Full Notify */
                ud_stdRet =  SECOC_E_OK_FV_FULL;
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
/* Function Name | SecOC_CD_FV_Trunc_UpdateRx                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index:                                                 */
/*               | bUpdate:                                                 */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK               : Success                            */
/*               |  SECOC_E_OK_FV_FULL : Success but FV is full.            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_UpdateRx
(
    uint16 u2Index,
    boolean bUpdate
)
{
    Std_ReturnType          ud_stdRet = (Std_ReturnType)E_OK;
#if (SECOC_AB_RX_PDU_TRUNCFV_MAX > 0U)
    /* Parameters check */
    if( u2Index < SecOC_Ab_RxPduTruncFvMax )
    {
        if( bUpdate == (boolean)TRUE )
        {
            SchM_Enter_SecOC_CD_FV();
            /* Copy */
            (void)SecOCStd_MemCpy( &SecOC_CD_FV_Trunc_stRxLast[u2Index], &SecOC_CD_FV_Trunc_stRxWork[u2Index], sizeof(SecOC_CD_FV_Trunc_LastType) ); /* no return check required */
            
            /* Check Counter Full */
            if( SecOC_CD_FV_Trunc_stRxLast[u2Index].u2Msg == (uint16)SECOC_CD_FV_TRUNC_MSG_MAX )
            {
                /* Full Notify */
                ud_stdRet = SECOC_E_OK_FV_FULL;
            }
            
            SchM_Exit_SecOC_CD_FV();
        }
    }
#endif
    
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_UpdateSync                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2Index:                                                 */
/*               | bUpdate:                                                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_UpdateSync
(
    uint16 u2Index,
    boolean bUpdate
)
{
    /* Parameters check */
    if( u2Index < SecOC_Ab_BusTruncMax )
    {
        if( bUpdate == (boolean)TRUE )
        {
            SchM_Enter_SecOC_CD_FV();
            /* Copy */
            (void)SecOCStd_MemCpy( &SecOC_CD_FV_Trunc_stNew[u2Index], &SecOC_CD_FV_Trunc_stNewWork[u2Index], sizeof(SecOC_CD_FV_Trunc_NewType) ); /* no return check required */
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
            SecOC_CD_FV_Trunc_stNewRedundant[u2Index].u4Trip  = ~SecOC_CD_FV_Trunc_stNew[u2Index].u4Trip;
            SecOC_CD_FV_Trunc_stNewRedundant[u2Index].u4Reset = ~SecOC_CD_FV_Trunc_stNew[u2Index].u4Reset;
#endif
            SchM_Exit_SecOC_CD_FV();
            
            /* Wraparound check */
            if( SecOC_CD_FV_Trunc_bWraparound[u2Index] == (boolean)TRUE )
            {
                SecOC_CD_FV_Trunc_ClearLast( u2Index );
            }
        }
        
        /* Wraparound clear */
        SecOC_CD_FV_Trunc_bWraparound[u2Index] = (boolean)FALSE;
    }
    
    return ;
}
#endif

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_ResetBus                               */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BusIndex :                                             */
/*               | u2Index:                                                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_ResetBus
(
    uint16 u2BusIndex,
    uint16 u2Index
)
{
    /* Parameters check */
    if( (u2BusIndex < SecOC_Ab_BusMax)
      && (u2Index < SecOC_Ab_BusTruncMax) )
    {
        SchM_Enter_SecOC_CD_FV();
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
        SecOC_CD_FV_Trunc_u1NewRenewalFlag[u2Index] = SECOC_CD_FV_TRUNC_FALSE;
        SecOC_CD_FV_Trunc_bWraparound[u2Index] = (boolean)FALSE;
#endif
        SecOC_CD_FV_Trunc_stNew[u2Index].u4Trip = 0UL;
        SecOC_CD_FV_Trunc_stNew[u2Index].u4Reset = 0UL;
        SecOC_CD_FV_Trunc_stNewWork[u2Index].u4Trip = 0UL;
        SecOC_CD_FV_Trunc_stNewWork[u2Index].u4Reset = 0UL;
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
        SecOC_CD_FV_Trunc_stNewRedundant[u2Index].u4Trip  = ~SecOC_CD_FV_Trunc_stNew[u2Index].u4Trip;
        SecOC_CD_FV_Trunc_stNewRedundant[u2Index].u4Reset = ~SecOC_CD_FV_Trunc_stNew[u2Index].u4Reset;
#endif
        SchM_Exit_SecOC_CD_FV();
        
        SecOC_CD_FV_Trunc_ClearLast( u2BusIndex );
    }
    
    return ;
}

#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_GetErrorStatus                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | SecOC_ErrorStatusType                                    */
/*               |  SECOC_E_NONE           : No Error                       */
/*               |  SECOC_E_RAM_CHECK_FAIL : RAM Error                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(SecOC_ErrorStatusType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_GetErrorStatus
(
    uint16 u2BusIndex
)
{
    SecOC_ErrorStatusType   ud_errStatus;
    SecOC_CD_FV_Trunc_NewType     st_new;
    SecOC_CD_FV_Trunc_NewType     st_new_redundant;
    
    SchM_Enter_SecOC_CD_FV();
    st_new.u4Trip  = SecOC_CD_FV_Trunc_stNew[u2BusIndex].u4Trip;
    st_new.u4Reset = SecOC_CD_FV_Trunc_stNew[u2BusIndex].u4Reset;
    st_new_redundant.u4Trip  = SecOC_CD_FV_Trunc_stNewRedundant[u2BusIndex].u4Trip;
    st_new_redundant.u4Reset = SecOC_CD_FV_Trunc_stNewRedundant[u2BusIndex].u4Reset;
    SchM_Exit_SecOC_CD_FV();
    
    if( (st_new_redundant.u4Trip != ~st_new.u4Trip) || (st_new_redundant.u4Reset != ~st_new.u4Reset) )
    {
        /* RAM Error */
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
        SecOC_CD_FV_Trunc_udRamChkResult[u2BusIndex] = SECOC_E_RAM_CHECK_FAIL;
#endif
        ud_errStatus = SECOC_E_RAM_CHECK_FAIL;
    }
    else
    {
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
        SecOC_CD_FV_Trunc_udRamChkResult[u2BusIndex] = SECOC_E_NONE;
#endif
        ud_errStatus = SECOC_E_NONE;
    }
    
    return ud_errStatus;
}
#endif

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_ClearLast                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u2BusIndex :                                             */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_ClearLast
(
    uint16 u2BusIndex
)
{
#if (((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_RX_PDU_TRUNCFV_MAX > 0U) && (SECOC_AB_RX_SECURED_MSG_IN_BUS_COUNT_MAX > 0U)) || \
     ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_TX_PDU_TRUNCFV_MAX > 0U) && (SECOC_AB_TX_SECURED_MSG_IN_BUS_COUNT_MAX > 0U)))
    uint16  u2_index;
    uint16  u2_clearIndex;
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_RX_PDU_TRUNCFV_MAX > 0U) && (SECOC_AB_RX_SECURED_MSG_IN_BUS_COUNT_MAX > 0U))
    /* Rx FV Bus Clear */
    for( u2_index = 0U; u2_index < SecOC_Ab_BusId2SecuredMsgIdxLists[u2BusIndex].Ab_RxSecuredMsgCount; u2_index++ )
    {
        u2_clearIndex = SecOC_RxPduProcessing[SecOC_Ab_BusId2SecuredMsgIdxLists[u2BusIndex].Ab_RxSecuredMsgIdxList[u2_index]].Ab_MessageTypeIndex;
        
        SchM_Enter_SecOC_CD_FV();
        SecOC_CD_FV_Trunc_u1RxRenewalFlag[u2_clearIndex] = SECOC_CD_FV_TRUNC_FALSE;
        SecOCStd_MemClr( &SecOC_CD_FV_Trunc_stRxLast[u2_clearIndex], sizeof(SecOC_CD_FV_Trunc_LastType) );
        SecOCStd_MemClr( &SecOC_CD_FV_Trunc_stRxWork[u2_clearIndex], sizeof(SecOC_CD_FV_Trunc_LastType) );
        SchM_Exit_SecOC_CD_FV();
    }
#endif
    
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_TX_PDU_TRUNCFV_MAX > 0U) && (SECOC_AB_TX_SECURED_MSG_IN_BUS_COUNT_MAX > 0U))
    /* Tx FV Bus Clear */
    for( u2_index = 0U; u2_index < SecOC_Ab_BusId2SecuredMsgIdxLists[u2BusIndex].Ab_TxSecuredMsgCount; u2_index++ )
    {
        u2_clearIndex = SecOC_TxPduProcessing[SecOC_Ab_BusId2SecuredMsgIdxLists[u2BusIndex].Ab_TxSecuredMsgIdxList[u2_index]].Ab_MessageTypeIndex;
        
        SchM_Enter_SecOC_CD_FV();
        SecOC_CD_FV_Trunc_u1TxRenewalFlag[u2_clearIndex] = SECOC_CD_FV_TRUNC_FALSE;
        SecOCStd_MemClr( &SecOC_CD_FV_Trunc_stTxLast[u2_clearIndex], sizeof(SecOC_CD_FV_Trunc_LastType) );
        SecOCStd_MemClr( &SecOC_CD_FV_Trunc_stTxWork[u2_clearIndex], sizeof(SecOC_CD_FV_Trunc_LastType) );
        SchM_Exit_SecOC_CD_FV();
    }
#endif
    
    return ;
}

#if !((SECOC_AB_TRIP_CNT_LENGTH == SECOC_CD_FV_TRUNC_OEM_TRIP_LEN) \
     && (SECOC_AB_RESET_CNT_LENGTH == SECOC_CD_FV_TRUNC_OEM_RESET_LEN) \
     && (SECOC_AB_MSG_CNT_LENGTH == SECOC_CD_FV_TRUNC_OEM_MSG_LEN) \
     && (SECOC_AB_RESET_FLAG_LENGTH == SECOC_CD_FV_TRUNC_OEM_RFLG_LEN))
  #if ((SECOC_AB_TRIP_CNT_LENGTH > 0U) || (SECOC_AB_RESET_CNT_LENGTH > 0U) || \
       (SECOC_AB_MSG_CNT_LENGTH > 0U)  || (SECOC_AB_RESET_FLAG_LENGTH > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_AryToU4                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptArray     :                                            */
/*               | u4OffsetLen :                                            */
/*               | ptData      :                                            */
/*               | u2DataLen   :                                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_AryToU4
(
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptArray,
    uint32 u4OffsetLen,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptData,
    uint16 u2DataLen
)
{
    uint32  u4_workData = 0UL;
    uint32  u4_sftData;
    uint16  u2_index;
    uint16  u2_byteSurplus;
    uint16  u2_sftDataLen;
    
    u2_index = (uint16)(u4OffsetLen >> SECOC_CD_FV_TRUNC_BYTESHIFT);
    u2_byteSurplus = (uint16)(u4OffsetLen & (uint32)SECOC_CD_FV_TRUNC_BYTESURPLUS);
    
    if( u2_byteSurplus == (uint16)0U )
    {
        if( u2DataLen > SECOC_CD_FV_TRUNC_BYTE_3 )
        {
            u4_workData  = (uint32)ptArray[u2_index]                            << SECOC_CD_FV_TRUNC_BYTE_3;
            u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX1] << SECOC_CD_FV_TRUNC_BYTE_2;
            u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX2] << SECOC_CD_FV_TRUNC_BYTE_1;
            u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX3];
        }
        else if( u2DataLen > SECOC_CD_FV_TRUNC_BYTE_2 )
        {
            u4_workData  = (uint32)ptArray[u2_index]                            << SECOC_CD_FV_TRUNC_BYTE_3;
            u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX1] << SECOC_CD_FV_TRUNC_BYTE_2;
            u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX2] << SECOC_CD_FV_TRUNC_BYTE_1;
        }
        else if( u2DataLen > SECOC_CD_FV_TRUNC_BYTE_1 )
        {
            u4_workData  = (uint32)ptArray[u2_index]                            << SECOC_CD_FV_TRUNC_BYTE_3;
            u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX1] << SECOC_CD_FV_TRUNC_BYTE_2;
        }
        else if( u2DataLen > SECOC_CD_FV_TRUNC_BYTE_0 )
        {
            u4_workData  = (uint32)ptArray[u2_index]                            << SECOC_CD_FV_TRUNC_BYTE_3;
        }
        else
        {
            /* No Processing */
        }
    }
    else if( u2DataLen > SECOC_CD_FV_TRUNC_BYTE_0 )
    {
        u4_sftData = (uint32)ptArray[u2_index] << (SECOC_CD_FV_TRUNC_BYTE_3 + u2_byteSurplus);
        
        if( u2DataLen > (SECOC_CD_FV_TRUNC_BYTE_1 - u2_byteSurplus) )
        {
            u2_sftDataLen = u2DataLen - (SECOC_CD_FV_TRUNC_BYTE_1 - u2_byteSurplus);
            
            if( u2_sftDataLen > SECOC_CD_FV_TRUNC_BYTE_3 )
            {
                u4_workData  = (uint32)ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX1] << SECOC_CD_FV_TRUNC_BYTE_3;
                u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX2] << SECOC_CD_FV_TRUNC_BYTE_2;
                u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX3] << SECOC_CD_FV_TRUNC_BYTE_1;
                u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX4];
            }
            else if( u2_sftDataLen > SECOC_CD_FV_TRUNC_BYTE_2 )
            {
                u4_workData  = (uint32)ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX1] << SECOC_CD_FV_TRUNC_BYTE_3;
                u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX2] << SECOC_CD_FV_TRUNC_BYTE_2;
                u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX3] << SECOC_CD_FV_TRUNC_BYTE_1;
            }
            else if( u2_sftDataLen > SECOC_CD_FV_TRUNC_BYTE_1 )
            {
                u4_workData  = (uint32)ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX1] << SECOC_CD_FV_TRUNC_BYTE_3;
                u4_workData |= (uint32)ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX2] << SECOC_CD_FV_TRUNC_BYTE_2;
            }
            else
            {
                u4_workData  = (uint32)ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX1] << SECOC_CD_FV_TRUNC_BYTE_3;
            }
        }
        
        u4_workData >>= (SECOC_CD_FV_TRUNC_BYTE_1 - u2_byteSurplus);
        u4_workData |= u4_sftData;
    }
    else
    {
        /* No Processing */
    }
    
    if( u4_workData != 0UL )
    {
        u4_workData >>= (SECOC_CD_FV_TRUNC_BYTE_4 - u2DataLen);
        *ptData = u4_workData;
    }
    else
    {
        *ptData = 0UL;
    }
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_U4ToAry                                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | u4Data      :                                            */
/*               | u2DataLen   :                                            */
/*               | ptArray     :                                            */
/*               | u4OffsetLen :                                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_U4ToAry
(
    uint32 u4Data,
    uint16 u2DataLen,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptArray,
    uint32 u4OffsetLen
)
{
    uint32  u4_sftData;
    uint16  u2_index;
    uint16  u2_byteSurplus;
    uint16  u2_sftDataLen;
    
    u2_index = (uint16)(u4OffsetLen >> SECOC_CD_FV_TRUNC_BYTESHIFT);
    u2_byteSurplus = (uint16)(u4OffsetLen & (uint32)SECOC_CD_FV_TRUNC_BYTESURPLUS);
    
    if( u2_byteSurplus == (uint16)0U )
    {
        if( u2DataLen > SECOC_CD_FV_TRUNC_BYTE_3 )
        {
            ptArray[u2_index]                            = (uint8)(u4Data >> SECOC_CD_FV_TRUNC_BYTE_3);
            ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX1] = (uint8)(u4Data >> SECOC_CD_FV_TRUNC_BYTE_2);
            ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX2] = (uint8)(u4Data >> SECOC_CD_FV_TRUNC_BYTE_1);
            ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX3] = (uint8)u4Data;
        }
        else if( u2DataLen > SECOC_CD_FV_TRUNC_BYTE_2 )
        {
            ptArray[u2_index]                            = (uint8)(u4Data >> SECOC_CD_FV_TRUNC_BYTE_3);
            ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX1] = (uint8)(u4Data >> SECOC_CD_FV_TRUNC_BYTE_2);
            ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX2] = (uint8)(u4Data >> SECOC_CD_FV_TRUNC_BYTE_1);
        }
        else if( u2DataLen > SECOC_CD_FV_TRUNC_BYTE_1 )
        {
            ptArray[u2_index]                            = (uint8)(u4Data >> SECOC_CD_FV_TRUNC_BYTE_3);
            ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX1] = (uint8)(u4Data >> SECOC_CD_FV_TRUNC_BYTE_2);
        }
        else if( u2DataLen > SECOC_CD_FV_TRUNC_BYTE_0 )
        {
            ptArray[u2_index]                            = (uint8)(u4Data >> SECOC_CD_FV_TRUNC_BYTE_3);
        }
        else
        {
            /* No Processing */
        }
    }
    else if( u2DataLen > SECOC_CD_FV_TRUNC_BYTE_0 )
    {
        u4_sftData = u4Data >> (SECOC_CD_FV_TRUNC_BYTE_3 + u2_byteSurplus);
        ptArray[u2_index] |= (uint8)u4_sftData;
        
        if( u2DataLen > (SECOC_CD_FV_TRUNC_BYTE_1 - u2_byteSurplus) )
        {
            u4_sftData = u4Data << (SECOC_CD_FV_TRUNC_BYTE_1 - u2_byteSurplus);
            u2_sftDataLen = u2DataLen - (SECOC_CD_FV_TRUNC_BYTE_1 - u2_byteSurplus);
            
            if( u2_sftDataLen > SECOC_CD_FV_TRUNC_BYTE_3 )
            {
                ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX1] = (uint8)(u4_sftData >> SECOC_CD_FV_TRUNC_BYTE_3);
                ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX2] = (uint8)(u4_sftData >> SECOC_CD_FV_TRUNC_BYTE_2);
                ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX3] = (uint8)(u4_sftData >> SECOC_CD_FV_TRUNC_BYTE_1);
                ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX4] = (uint8)u4_sftData;
            }
            else if( u2_sftDataLen > SECOC_CD_FV_TRUNC_BYTE_2 )
            {
                ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX1] = (uint8)(u4_sftData >> SECOC_CD_FV_TRUNC_BYTE_3);
                ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX2] = (uint8)(u4_sftData >> SECOC_CD_FV_TRUNC_BYTE_2);
                ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX3] = (uint8)(u4_sftData >> SECOC_CD_FV_TRUNC_BYTE_1);
            }
            else if( u2_sftDataLen > SECOC_CD_FV_TRUNC_BYTE_1 )
            {
                ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX1] = (uint8)(u4_sftData >> SECOC_CD_FV_TRUNC_BYTE_3);
                ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX2] = (uint8)(u4_sftData >> SECOC_CD_FV_TRUNC_BYTE_2);
            }
            else
            {
                ptArray[u2_index + SECOC_CD_FV_TRUNC_INDEX1] = (uint8)(u4_sftData >> SECOC_CD_FV_TRUNC_BYTE_3);
            }
        }
    }
    else
    {
        /* No Processing */
    }
    
    return ;
}
  #endif
#endif

#if ((SECOC_AB_TX_PDU_TRUNCFV_MAX > 0U) || (SECOC_AB_RX_PDU_TRUNCFV_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_Ary2St                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptArray  :                                               */
/*               | u4Length :                                               */
/*               | ptFvInfo :                                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_Ary2St
(
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptArray,
    uint32 u4Length,
    P2VAR(SecOC_CD_FV_Trunc_InfoType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvInfo
)
{
#if ((SECOC_AB_TRIP_CNT_LENGTH == SECOC_CD_FV_TRUNC_OEM_TRIP_LEN) \
     && (SECOC_AB_RESET_CNT_LENGTH == SECOC_CD_FV_TRUNC_OEM_RESET_LEN) \
     && (SECOC_AB_MSG_CNT_LENGTH == SECOC_CD_FV_TRUNC_OEM_MSG_LEN) \
     && (SECOC_AB_RESET_FLAG_LENGTH == SECOC_CD_FV_TRUNC_OEM_RFLG_LEN))

    uint32  u4_counterCalc;
    
    if( u4Length == (uint32)SECOC_CD_FV_TRUNC_OEM_TXFV_LEN )
    {
        /* Tx FV */
        
        ptFvInfo->u4Trip = 0UL;
        ptFvInfo->u4Reset = 0UL;
        
        u4_counterCalc  = (uint32)ptArray[SECOC_CD_FV_TRUNC_INDEX0] >> SECOC_CD_FV_TRUNC_BITSFT_6;
        ptFvInfo->u2Msg = (uint16)u4_counterCalc;
        
        u4_counterCalc  = (uint32)ptArray[SECOC_CD_FV_TRUNC_INDEX0] >> SECOC_CD_FV_TRUNC_BITSFT_4;
        u4_counterCalc &= SECOC_CD_FV_TRUNC_MSK_2BIT;
        ptFvInfo->u1ResetFlag = (uint8)u4_counterCalc;
        
        ptFvInfo->u1Length = (uint8)SECOC_CD_FV_TRUNC_OEM_TXFV_LEN;
    }
    else if( u4Length == (uint32)SECOC_CD_FV_TRUNC_FULL_LEN )
    {
        /* Full FV */
        
        u4_counterCalc  = (uint32)ptArray[SECOC_CD_FV_TRUNC_INDEX0] << SECOC_CD_FV_TRUNC_BYTE_1;
        u4_counterCalc |= (uint32)ptArray[SECOC_CD_FV_TRUNC_INDEX1];
        ptFvInfo->u4Trip = u4_counterCalc;
        
        u4_counterCalc  = (uint32)ptArray[SECOC_CD_FV_TRUNC_INDEX2] << SECOC_CD_FV_TRUNC_BITSFT_12;
        u4_counterCalc |= (uint32)ptArray[SECOC_CD_FV_TRUNC_INDEX3] << SECOC_CD_FV_TRUNC_BITSFT_4;
        u4_counterCalc |= (uint32)ptArray[SECOC_CD_FV_TRUNC_INDEX4] >> SECOC_CD_FV_TRUNC_BITSFT_4;
        ptFvInfo->u4Reset = u4_counterCalc;
        
        u4_counterCalc  = (uint32)ptArray[SECOC_CD_FV_TRUNC_INDEX4] << SECOC_CD_FV_TRUNC_BITSFT_4;
        u4_counterCalc |= (uint32)ptArray[SECOC_CD_FV_TRUNC_INDEX5] >> SECOC_CD_FV_TRUNC_BITSFT_4;
        u4_counterCalc &= SECOC_CD_FV_TRUNC_MSK_8BIT;
        ptFvInfo->u2Msg = (uint16)u4_counterCalc;
        
        u4_counterCalc  = (uint32)ptArray[SECOC_CD_FV_TRUNC_INDEX5] >> SECOC_CD_FV_TRUNC_BITSFT_2;
        u4_counterCalc &= SECOC_CD_FV_TRUNC_MSK_2BIT;
        ptFvInfo->u1ResetFlag = (uint8)u4_counterCalc;
        
        ptFvInfo->u1Length = (uint8)SECOC_CD_FV_TRUNC_FULL_LEN;
    }
    else
    {
        /* Error */
        ptFvInfo->u4Trip = 0UL;
        ptFvInfo->u4Reset = 0UL;
        ptFvInfo->u2Msg = 0U;
        ptFvInfo->u1ResetFlag = 0U;
        ptFvInfo->u1Length = 0U;
    }
    
#else
    
  #if ((SECOC_AB_TRIP_CNT_LENGTH > 0U) || (SECOC_AB_RESET_CNT_LENGTH > 0U) || \
       (SECOC_AB_MSG_CNT_LENGTH > 0U)  || (SECOC_AB_RESET_FLAG_LENGTH > 0U))
    uint32  u4_counterCalc = 0UL;
    uint32  u4_offset = 0UL;
    uint16  u2_tripLength = 0U;
  #endif
  #if ((SECOC_AB_RESET_CNT_LENGTH > 0U) || (SECOC_AB_MSG_CNT_LENGTH > 0U) || \
       (SECOC_AB_RESET_FLAG_LENGTH > 0U))
    uint16  u2_resetLength = 0U;
  #endif
  #if ((SECOC_AB_MSG_CNT_LENGTH > 0U) || (SECOC_AB_RESET_FLAG_LENGTH > 0U))
    uint16  u2_msgLength = 0U;
  #endif
  #if (SECOC_AB_RESET_FLAG_LENGTH > 0U)
    uint16  u2_resetFlgLength;
  #endif
    
    /* Trip Counter */
  #if (SECOC_AB_TRIP_CNT_LENGTH > 0U)
    if( u4Length > (SECOC_AB_RESET_CNT_LENGTH + SECOC_AB_MSG_CNT_LENGTH + SECOC_AB_RESET_FLAG_LENGTH) )
    {
        u2_tripLength = (uint16)(u4Length - (SECOC_AB_RESET_CNT_LENGTH + SECOC_AB_MSG_CNT_LENGTH + SECOC_AB_RESET_FLAG_LENGTH));
        
        SecOC_CD_FV_Trunc_AryToU4( ptArray, u4_offset, &u4_counterCalc, u2_tripLength );
        
        ptFvInfo->u4Trip = u4_counterCalc;
    }
  #endif
    
    /* Reset Counter */
  #if (SECOC_AB_RESET_CNT_LENGTH > 0U)
    if( u4Length > (SECOC_AB_MSG_CNT_LENGTH + SECOC_AB_RESET_FLAG_LENGTH) )
    {
        u4_offset = (uint32)u2_tripLength;
        u2_resetLength = (uint16)(u4Length - ((uint32)u2_tripLength + (uint32)SECOC_AB_MSG_CNT_LENGTH + (uint32)SECOC_AB_RESET_FLAG_LENGTH));
        
        SecOC_CD_FV_Trunc_AryToU4( ptArray, u4_offset, &u4_counterCalc, u2_resetLength );
        
        ptFvInfo->u4Reset = u4_counterCalc;
    }
  #endif
    
    /* Message Counter */
  #if (SECOC_AB_MSG_CNT_LENGTH > 0U)
    if( u4Length > (uint32)SECOC_AB_RESET_FLAG_LENGTH )
    {
        u4_offset += (uint32)u2_resetLength;
        u2_msgLength = (uint16)(u4Length - ((uint32)u2_tripLength + (uint32)u2_resetLength + (uint32)SECOC_AB_RESET_FLAG_LENGTH));
        
        SecOC_CD_FV_Trunc_AryToU4( ptArray, u4_offset, &u4_counterCalc, u2_msgLength );
        
        ptFvInfo->u2Msg = (uint16)u4_counterCalc;
    }
  #endif
    
    /* Reset Flag */
  #if (SECOC_AB_RESET_FLAG_LENGTH > 0U)
    if( u4Length > 0UL )
    {
        u4_offset += (uint32)u2_msgLength;
        u2_resetFlgLength = (uint16)(u4Length - ((uint32)u2_tripLength + (uint32)u2_resetLength + (uint32)u2_msgLength));
        
        SecOC_CD_FV_Trunc_AryToU4( ptArray, u4_offset, &u4_counterCalc, u2_resetFlgLength );
        
        ptFvInfo->u1ResetFlag = (uint8)u4_counterCalc;
    }
  #endif
    
    ptFvInfo->u1Length = (uint8)u4Length;
    
#endif
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_St2Ary                                 */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptFvInfo :                                               */
/*               | ptArray  :                                               */
/*               | ptLength :                                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_St2Ary
(
    P2CONST(SecOC_CD_FV_Trunc_InfoType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvInfo,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptArray,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptLength
)
{
#if ((SECOC_AB_TRIP_CNT_LENGTH == SECOC_CD_FV_TRUNC_OEM_TRIP_LEN) \
     && (SECOC_AB_RESET_CNT_LENGTH == SECOC_CD_FV_TRUNC_OEM_RESET_LEN) \
     && (SECOC_AB_MSG_CNT_LENGTH == SECOC_CD_FV_TRUNC_OEM_MSG_LEN) \
     && (SECOC_AB_RESET_FLAG_LENGTH == SECOC_CD_FV_TRUNC_OEM_RFLG_LEN))

    if( ptFvInfo->u1Length <= (uint8)( (*ptLength) & SECOC_CD_FV_TRUNC_MSK_8BIT ) )
    {
        if( ptFvInfo->u1Length == (uint8)SECOC_CD_FV_TRUNC_FULL_LEN )
        {
            /* Full FV */
            
            ptArray[SECOC_CD_FV_TRUNC_INDEX0]  = (uint8)( (ptFvInfo->u4Trip >> SECOC_CD_FV_TRUNC_BYTE_1) & SECOC_CD_FV_TRUNC_MSK_8BIT );
            ptArray[SECOC_CD_FV_TRUNC_INDEX1]  = (uint8)( ptFvInfo->u4Trip & SECOC_CD_FV_TRUNC_MSK_8BIT );
            ptArray[SECOC_CD_FV_TRUNC_INDEX2]  = (uint8)( (ptFvInfo->u4Reset >> SECOC_CD_FV_TRUNC_BITSFT_12) & SECOC_CD_FV_TRUNC_MSK_8BIT );
            ptArray[SECOC_CD_FV_TRUNC_INDEX3]  = (uint8)( (ptFvInfo->u4Reset >> SECOC_CD_FV_TRUNC_BITSFT_4) & SECOC_CD_FV_TRUNC_MSK_8BIT );
            ptArray[SECOC_CD_FV_TRUNC_INDEX4]  = (uint8)( (ptFvInfo->u4Reset << SECOC_CD_FV_TRUNC_BITSFT_4) & SECOC_CD_FV_TRUNC_MSK_8BIT );
            ptArray[SECOC_CD_FV_TRUNC_INDEX4] |= (uint8)( (ptFvInfo->u2Msg >> SECOC_CD_FV_TRUNC_BITSFT_4) & (uint16)SECOC_CD_FV_TRUNC_MSK_8BIT );
            ptArray[SECOC_CD_FV_TRUNC_INDEX5]  = (uint8)( (ptFvInfo->u2Msg << SECOC_CD_FV_TRUNC_BITSFT_4) & (uint16)SECOC_CD_FV_TRUNC_MSK_8BIT );
            ptArray[SECOC_CD_FV_TRUNC_INDEX5] |= (uint8)(ptFvInfo->u1ResetFlag << SECOC_CD_FV_TRUNC_BITSFT_2);
            *ptLength = (uint32)ptFvInfo->u1Length;
        }
        else if( ptFvInfo->u1Length == (uint8)SECOC_CD_FV_TRUNC_OEM_TXFV_LEN )
        {
            /* Tx FV */
            
            ptArray[SECOC_CD_FV_TRUNC_INDEX0]  = (uint8)( (ptFvInfo->u2Msg << SECOC_CD_FV_TRUNC_BITSFT_6) & (uint16)SECOC_CD_FV_TRUNC_MSK_8BIT );
            ptArray[SECOC_CD_FV_TRUNC_INDEX0] |= (uint8)(ptFvInfo->u1ResetFlag << SECOC_CD_FV_TRUNC_BITSFT_4);
            *ptLength = (uint32)ptFvInfo->u1Length;
        }
        else
        {
            /* Error */
            *ptLength = 0UL;
        }
    }
    
#else
    
  #if ((SECOC_AB_TRIP_CNT_LENGTH > 0U) || (SECOC_AB_RESET_CNT_LENGTH > 0U) || \
       (SECOC_AB_MSG_CNT_LENGTH > 0U)  || (SECOC_AB_RESET_FLAG_LENGTH > 0U))
    uint32  u4_counterCalc;
    uint32  u4_offset = 0UL;
    uint16  u2_tripLength = 0U;
  #endif
  #if ((SECOC_AB_RESET_CNT_LENGTH > 0U) || (SECOC_AB_MSG_CNT_LENGTH > 0U) || \
       (SECOC_AB_RESET_FLAG_LENGTH > 0U))
    uint16  u2_resetLength = 0U;
  #endif
  #if ((SECOC_AB_MSG_CNT_LENGTH > 0U) || (SECOC_AB_RESET_FLAG_LENGTH > 0U))
    uint16  u2_msgLength = 0U;
  #endif
  #if (SECOC_AB_RESET_FLAG_LENGTH > 0U)
    uint16  u2_resetFlgLength;
  #endif
    
    if( ptFvInfo->u1Length <= (uint8)( (*ptLength) & SECOC_CD_FV_TRUNC_MSK_8BIT) )
    {
        /* Trip Counter */
  #if (SECOC_AB_TRIP_CNT_LENGTH > 0U)
        if( ptFvInfo->u1Length > (uint8)(SECOC_AB_RESET_CNT_LENGTH + SECOC_AB_MSG_CNT_LENGTH + SECOC_AB_RESET_FLAG_LENGTH) )
        {
            u2_tripLength = (uint16)ptFvInfo->u1Length - ((uint16)SECOC_AB_RESET_CNT_LENGTH + (uint16)SECOC_AB_MSG_CNT_LENGTH + (uint16)SECOC_AB_RESET_FLAG_LENGTH);
            u4_counterCalc = ptFvInfo->u4Trip << (SECOC_CD_FV_TRUNC_BYTE_4 - u2_tripLength);
            
            SecOC_CD_FV_Trunc_U4ToAry( u4_counterCalc, u2_tripLength, ptArray, u4_offset );
        }
  #endif
        
        /* Reset Counter */
  #if (SECOC_AB_RESET_CNT_LENGTH > 0U)
        if( ptFvInfo->u1Length > (uint8)(SECOC_AB_MSG_CNT_LENGTH + SECOC_AB_RESET_FLAG_LENGTH) )
        {
            u4_offset = (uint32)u2_tripLength;
            u2_resetLength = (uint16)ptFvInfo->u1Length - (u2_tripLength + (uint16)SECOC_AB_MSG_CNT_LENGTH + (uint16)SECOC_AB_RESET_FLAG_LENGTH);
            u4_counterCalc = ptFvInfo->u4Reset << (SECOC_CD_FV_TRUNC_BYTE_4 - u2_resetLength);
            
            SecOC_CD_FV_Trunc_U4ToAry( u4_counterCalc, u2_resetLength, ptArray, u4_offset );
        }
  #endif
        
        /* Message Counter */
  #if (SECOC_AB_MSG_CNT_LENGTH > 0U)
        if( ptFvInfo->u1Length > (uint8)SECOC_AB_RESET_FLAG_LENGTH )
        {
            u4_offset += (uint32)u2_resetLength;
            u2_msgLength = (uint16)ptFvInfo->u1Length - (u2_tripLength + u2_resetLength + (uint16)SECOC_AB_RESET_FLAG_LENGTH);
            u4_counterCalc = (uint32)ptFvInfo->u2Msg << (SECOC_CD_FV_TRUNC_BYTE_4 - u2_msgLength);
            
            SecOC_CD_FV_Trunc_U4ToAry( u4_counterCalc, u2_msgLength, ptArray, u4_offset );
        }
  #endif
        
    /* Reset Flag */
  #if (SECOC_AB_RESET_FLAG_LENGTH > 0U)
        if( ptFvInfo->u1Length > (uint8)0U )
        {
            u4_offset += (uint32)u2_msgLength;
            u2_resetFlgLength = (uint16)(ptFvInfo->u1Length - (u2_tripLength + u2_resetLength + u2_msgLength));
            u4_counterCalc = (uint32)ptFvInfo->u1ResetFlag << (SECOC_CD_FV_TRUNC_BYTE_4 - u2_resetFlgLength);
            
            SecOC_CD_FV_Trunc_U4ToAry( u4_counterCalc, u2_resetFlgLength, ptArray, u4_offset );
        }
  #endif
        *ptLength = (uint32)ptFvInfo->u1Length;
    }
#endif
    
    return ;
}
#endif

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_Ary2St_Sync                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptArray  :                                               */
/*               | u4Length :                                               */
/*               | ptFvInfo :                                               */
/* Return Value  | None                                                     */
/* Notes         | Sync Message Only                                        */
/****************************************************************************/
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_Ary2St_Sync
(
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptArray,
    uint32 u4Length,
    P2VAR(SecOC_CD_FV_Trunc_InfoType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvInfo
)
{
#if ((SECOC_AB_TRIP_CNT_LENGTH == SECOC_CD_FV_TRUNC_OEM_TRIP_LEN) \
     && (SECOC_AB_RESET_CNT_LENGTH == SECOC_CD_FV_TRUNC_OEM_RESET_LEN))

    uint32  u4_counterCalc;
    
    if( u4Length == (uint32)SECOC_CD_FV_TRUNC_SYNC_LEN )
    {
        u4_counterCalc  = (uint32)ptArray[SECOC_CD_FV_TRUNC_INDEX0] << SECOC_CD_FV_TRUNC_BYTE_1;
        u4_counterCalc |= (uint32)ptArray[SECOC_CD_FV_TRUNC_INDEX1];
        ptFvInfo->u4Trip = u4_counterCalc;
        
        u4_counterCalc  = (uint32)ptArray[SECOC_CD_FV_TRUNC_INDEX2] << SECOC_CD_FV_TRUNC_BITSFT_12;
        u4_counterCalc |= (uint32)ptArray[SECOC_CD_FV_TRUNC_INDEX3] << SECOC_CD_FV_TRUNC_BITSFT_4;
        u4_counterCalc |= (uint32)ptArray[SECOC_CD_FV_TRUNC_INDEX4] >> SECOC_CD_FV_TRUNC_BITSFT_4;
        ptFvInfo->u4Reset = u4_counterCalc;
        
        ptFvInfo->u2Msg = 0U;
        ptFvInfo->u1ResetFlag = 0U;
        ptFvInfo->u1Length = (uint8)SECOC_CD_FV_TRUNC_SYNC_LEN;
    }
    else
    {
        /* Error */
        ptFvInfo->u4Trip = 0UL;
        ptFvInfo->u4Reset = 0UL;
        ptFvInfo->u2Msg = 0U;
        ptFvInfo->u1ResetFlag = 0U;
        ptFvInfo->u1Length = 0U;
    }
    
#else
    
  #if ((SECOC_AB_TRIP_CNT_LENGTH > 0U) || (SECOC_AB_RESET_CNT_LENGTH > 0U))
    uint32  u4_counterCalc = 0UL;
    uint32  u4_offset = 0UL;
    uint16  u2_tripLength = 0U;
  #endif
  #if (SECOC_AB_RESET_CNT_LENGTH > 0U)
    uint16  u2_resetLength;
  #endif
    
    /* Trip Counter */
  #if (SECOC_AB_TRIP_CNT_LENGTH > 0U)
    if( u4Length > (uint32)SECOC_AB_RESET_CNT_LENGTH )
    {
        u2_tripLength = (uint16)(u4Length - (uint32)SECOC_AB_RESET_CNT_LENGTH);
        
        SecOC_CD_FV_Trunc_AryToU4( ptArray, u4_offset, &u4_counterCalc, u2_tripLength );
        
        ptFvInfo->u4Trip = u4_counterCalc;
    }
  #endif
    
    /* Reset Counter */
  #if (SECOC_AB_RESET_CNT_LENGTH > 0U)
    if( u4Length > 0UL )
    {
        u4_offset = (uint32)u2_tripLength;
        u2_resetLength = (uint16)(u4Length - u2_tripLength);
        
        SecOC_CD_FV_Trunc_AryToU4( ptArray, u4_offset, &u4_counterCalc, u2_resetLength );
        
        ptFvInfo->u4Reset = u4_counterCalc;
    }
  #endif
    
    ptFvInfo->u2Msg = 0U;
    ptFvInfo->u1ResetFlag = 0U;
    ptFvInfo->u1Length = (uint8)u4Length;
    
#endif
    
    return ;
}

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_St2Ary_Sync                            */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptFvInfo :                                               */
/*               | ptArray  :                                               */
/*               | ptLength :                                               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_St2Ary_Sync
(
    P2CONST(SecOC_CD_FV_Trunc_InfoType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvInfo,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptArray,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptLength
)
{
#if ((SECOC_AB_TRIP_CNT_LENGTH == SECOC_CD_FV_TRUNC_OEM_TRIP_LEN) \
     && (SECOC_AB_RESET_CNT_LENGTH == SECOC_CD_FV_TRUNC_OEM_RESET_LEN))

    if( ptFvInfo->u1Length <= (uint8)( (*ptLength) & SECOC_CD_FV_TRUNC_MSK_8BIT ) )
    {
        ptArray[SECOC_CD_FV_TRUNC_INDEX0] = (uint8)(ptFvInfo->u4Trip >> SECOC_CD_FV_TRUNC_BYTE_1);
        ptArray[SECOC_CD_FV_TRUNC_INDEX1] = (uint8)ptFvInfo->u4Trip;
        ptArray[SECOC_CD_FV_TRUNC_INDEX2] = (uint8)(ptFvInfo->u4Reset >> SECOC_CD_FV_TRUNC_BITSFT_12);
        ptArray[SECOC_CD_FV_TRUNC_INDEX3] = (uint8)(ptFvInfo->u4Reset >> SECOC_CD_FV_TRUNC_BITSFT_4);
        ptArray[SECOC_CD_FV_TRUNC_INDEX4] = (uint8)(ptFvInfo->u4Reset << SECOC_CD_FV_TRUNC_BITSFT_4);
        *ptLength = (uint32)ptFvInfo->u1Length;
    }
    else
    {
        /* Error */
        *ptLength = 0UL;
    }
    
#else
    
  #if ((SECOC_AB_TRIP_CNT_LENGTH > 0U) || (SECOC_AB_RESET_CNT_LENGTH > 0U))
    uint32  u4_counterCalc;
    uint32  u4_offset = 0UL;
    uint16  u2_tripLength = 0U;
  #endif
  #if (SECOC_AB_RESET_CNT_LENGTH > 0U)
    uint16  u2_resetLength;
  #endif
    
    if( ptFvInfo->u1Length <= (uint8)( (*ptLength) & SECOC_CD_FV_TRUNC_MSK_8BIT ) )
    {
        /* Trip Counter */
  #if (SECOC_AB_TRIP_CNT_LENGTH > 0U)
        if( ptFvInfo->u1Length > (uint8)SECOC_AB_RESET_CNT_LENGTH )
        {
            u2_tripLength = (uint16)ptFvInfo->u1Length - (uint16)SECOC_AB_RESET_CNT_LENGTH;
            u4_counterCalc = ptFvInfo->u4Trip << (SECOC_CD_FV_TRUNC_BYTE_4 - u2_tripLength);
            
            SecOC_CD_FV_Trunc_U4ToAry( u4_counterCalc, u2_tripLength, ptArray, u4_offset );
        }
  #endif
        
        /* Reset Counter */
  #if (SECOC_AB_RESET_CNT_LENGTH > 0U)
        if( ptFvInfo->u1Length > (uint8)0U )
        {
            u4_offset = (uint32)u2_tripLength;
            u2_resetLength = (uint16)(ptFvInfo->u1Length - u2_tripLength);
            u4_counterCalc = ptFvInfo->u4Reset << (SECOC_CD_FV_TRUNC_BYTE_4 - u2_resetLength);
            
            SecOC_CD_FV_Trunc_U4ToAry( u4_counterCalc, u2_resetLength, ptArray, u4_offset );
        }
  #endif
        
        *ptLength = (uint32)ptFvInfo->u1Length;
    }
#endif
    
    return ;
}

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_RX_PDU_TRUNCFV_MAX > 0U))
/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_BuildVerifyFv                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptIndex   :                                              */
/*               | ptTxFv    :                                              */
/*               | u2Attempt :                                              */
/*               | ptWork    :                                              */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK              : Success                             */
/*               |  SECOC_E_RETRY     : Retry                               */
/*               |  SECOC_E_FV_NOT_OK : FV NG                               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_BuildVerifyFv
(
    P2CONST(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex,
    P2CONST(SecOC_CD_FV_Trunc_InfoType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptTxFv,
    uint16 u2Attempt,
    P2VAR(SecOC_CD_FV_Trunc_LastType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptWork
)
{
    Std_ReturnType          ud_stdRet = SECOC_E_FV_NOT_OK;
    SecOC_CD_FV_Trunc_RxWorkType  st_rxWork;
    boolean                 b_tripResetCompare;
    uint32                  u4_mask;
    uint16                  u2_lastMsg;
    
    SecOCStd_MemClr( &st_rxWork, sizeof(SecOC_CD_FV_Trunc_RxWorkType) );
    st_rxWork.u4NewReset = 0UL;
    st_rxWork.u2Attempt = u2Attempt;
    st_rxWork.u2Pattern = SECOC_CD_FV_TRUNC_RXPTNMAX;
    st_rxWork.bUpDigit = (boolean)FALSE;
    
    /* Length check */
    if( ptTxFv->u1Length > (uint8)(SECOC_AB_MSG_CNT_LENGTH + SECOC_AB_RESET_FLAG_LENGTH) )
    {
        st_rxWork.u4TxFvMsgLen = SECOC_AB_MSG_CNT_LENGTH;
        st_rxWork.u4TxFvRFlgLen = SECOC_AB_RESET_FLAG_LENGTH;
    }
    else
    {
#if (SECOC_AB_RESET_FLAG_LENGTH > 0U)
        if( ptTxFv->u1Length >= (uint8)SECOC_AB_RESET_FLAG_LENGTH )
        {
#endif
            st_rxWork.u4TxFvMsgLen = (uint32)ptTxFv->u1Length - (uint32)SECOC_AB_RESET_FLAG_LENGTH;
            st_rxWork.u4TxFvRFlgLen = SECOC_AB_RESET_FLAG_LENGTH;
#if (SECOC_AB_RESET_FLAG_LENGTH > 0U)
        }
        else
        {
            st_rxWork.u4TxFvMsgLen = 0UL;
            st_rxWork.u4TxFvRFlgLen = (uint32)ptTxFv->u1Length;
        }
#endif
    }
    
    u4_mask = SECOC_CD_FV_TRUNC_MSK_BASE << st_rxWork.u4TxFvMsgLen;
    u4_mask -= SECOC_CD_FV_TRUNC_MSK_SUB;
    SchM_Enter_SecOC_CD_FV();
    SecOC_CD_FV_Trunc_u1RxRenewalFlag[ptIndex->u2FvIndexLast] = SECOC_CD_FV_TRUNC_TRUE;
    
    u2_lastMsg = (uint16)((uint32)SecOC_CD_FV_Trunc_stRxLast[ptIndex->u2FvIndexLast].u2Msg & u4_mask);
    
    /* Freshness Value compare : message counter */
    if( ptTxFv->u2Msg <= u2_lastMsg )
    {
        st_rxWork.bUpDigit = (boolean)TRUE;
    }
    
    /* 1 Reset flag compare */
    b_tripResetCompare = SecOC_CD_FV_Trunc_ResetFlgComp( ptIndex, ptTxFv, &st_rxWork );
    
    /* 2 Trip and reset counter compare */
    if( b_tripResetCompare == (boolean)TRUE )
    {
        ud_stdRet = SecOC_CD_FV_Trunc_TripResetComp( ptIndex, ptTxFv, &st_rxWork, ptWork );
    }
    SchM_Exit_SecOC_CD_FV();
    return ud_stdRet;
}

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_ResetFlgComp                           */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptIndex   :                                              */
/*               | ptTxFv    :                                              */
/*               | ptRxWork  :                                              */
/* Return Value  | boolean                                                  */
/*               |  TRUE  : Freshness Value OK                              */
/*               |  FALSE : Freshness Value NG                              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(boolean, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_ResetFlgComp
(
    P2CONST(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex,
    P2CONST(SecOC_CD_FV_Trunc_InfoType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptTxFv,
    P2VAR(SecOC_CD_FV_Trunc_RxWorkType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptRxWork
)
{
    uint32          u4_mask;
    uint16          u2_ptnAttempt;
    uint8           u1_newRFlg;
    boolean         b_newRFlgEnable;
    boolean         b_tripResetCompare = (boolean)FALSE;
    
    u2_ptnAttempt = ptRxWork->u2Attempt;
    for( ptRxWork->u2Pattern = SECOC_CD_FV_TRUNC_RXPTN0; ptRxWork->u2Pattern < SECOC_CD_FV_TRUNC_RXPTNMAX; ptRxWork->u2Pattern++ )
    {
        b_newRFlgEnable = (boolean)FALSE;
        ptRxWork->u4NewReset = SecOC_CD_FV_Trunc_stNew[ptIndex->u2FvIndexFvType].u4Reset;
        
        if( ptRxWork->u2Pattern == SECOC_CD_FV_TRUNC_RXPTN0 )
        {
            b_newRFlgEnable = (boolean)TRUE;
        }
        else if( ptRxWork->u2Pattern == SECOC_CD_FV_TRUNC_RXPTN1 )
        {
            if( ptRxWork->u4NewReset >= SECOC_CD_FV_TRUNC_RXPTN1_NUM )
            {
                ptRxWork->u4NewReset -= SECOC_CD_FV_TRUNC_RXPTN1_NUM;
                b_newRFlgEnable = (boolean)TRUE;
            }
        }
        else if( ptRxWork->u2Pattern == SECOC_CD_FV_TRUNC_RXPTN2 )
        {
#if (SECOC_CD_FV_TRUNC_RESET_MAX > SECOC_CD_FV_TRUNC_RXPTN2_NUM)
            if( ptRxWork->u4NewReset <= (SECOC_CD_FV_TRUNC_RESET_MAX - SECOC_CD_FV_TRUNC_RXPTN2_NUM) )
            {
                ptRxWork->u4NewReset += SECOC_CD_FV_TRUNC_RXPTN2_NUM;
                b_newRFlgEnable = (boolean)TRUE;
            }
#endif
        }
        else if( ptRxWork->u2Pattern == SECOC_CD_FV_TRUNC_RXPTN3 )
        {
            if( ptRxWork->u4NewReset >= SECOC_CD_FV_TRUNC_RXPTN3_NUM )
            {
                ptRxWork->u4NewReset -= SECOC_CD_FV_TRUNC_RXPTN3_NUM;
                b_newRFlgEnable = (boolean)TRUE;
            }
        }
        else
        {
            /* No Processing */
#if (SECOC_CD_FV_TRUNC_RESET_MAX > SECOC_CD_FV_TRUNC_RXPTN4_NUM)
            if( ptRxWork->u4NewReset <= (SECOC_CD_FV_TRUNC_RESET_MAX - SECOC_CD_FV_TRUNC_RXPTN4_NUM) )
            {
                ptRxWork->u4NewReset += SECOC_CD_FV_TRUNC_RXPTN4_NUM;
                b_newRFlgEnable = (boolean)TRUE;
            }
#endif
        }
        
        if( b_newRFlgEnable == (boolean)TRUE )
        {
            u4_mask = SECOC_CD_FV_TRUNC_MSK_BASE << ptRxWork->u4TxFvRFlgLen;
            u4_mask -= SECOC_CD_FV_TRUNC_MSK_SUB;
            u1_newRFlg = (uint8)(ptRxWork->u4NewReset & u4_mask);
            
            if( ptTxFv->u1ResetFlag == u1_newRFlg )
            {
                if( u2_ptnAttempt > (uint16)0U )
                {
                    u2_ptnAttempt--;
                }
                else
                {
                    b_tripResetCompare = (boolean)TRUE;
                    break;
                }
            }
        }
    }
    
    return b_tripResetCompare;
}

/****************************************************************************/
/* Function Name | SecOC_CD_FV_Trunc_TripResetComp                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | ptIndex   :                                              */
/*               | ptTxFv    :                                              */
/*               | ptRxWork  :                                              */
/*               | ptWork    :                                              */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK               : Success                            */
/*               |  SECOC_E_RETRY      : Retry                              */
/*               |  SECOC_E_FV_NOT_OK  : FV NG                              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Trunc_TripResetComp
(
    P2CONST(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex,
    P2CONST(SecOC_CD_FV_Trunc_InfoType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptTxFv,
    P2CONST(SecOC_CD_FV_Trunc_RxWorkType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptRxWork,
    P2VAR(SecOC_CD_FV_Trunc_LastType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptWork
)
{
    Std_ReturnType  ud_stdRet = SECOC_E_FV_NOT_OK;
#if (SECOC_AB_RESET_CNT_LENGTH > 0U)
    uint32          u4_mask;
#endif
    uint32          u4_newTrip;
    SecOC_CD_FV_Trunc_LastType st_last;
    
    u4_newTrip = SecOC_CD_FV_Trunc_stNew[ptIndex->u2FvIndexFvType].u4Trip;
    
    /* Copy */
    st_last.u4Trip  = SecOC_CD_FV_Trunc_stRxLast[ptIndex->u2FvIndexLast].u4Trip;
    st_last.u4Reset = SecOC_CD_FV_Trunc_stRxLast[ptIndex->u2FvIndexLast].u4Reset;
    st_last.u2Msg   = SecOC_CD_FV_Trunc_stRxLast[ptIndex->u2FvIndexLast].u2Msg;
    
    if( (u4_newTrip == st_last.u4Trip)
      && (ptRxWork->u4NewReset == st_last.u4Reset) )
    {
        ptWork->u4Trip  = st_last.u4Trip;
        ptWork->u4Reset = st_last.u4Reset;
        
        ud_stdRet = E_OK;
        
#if (SECOC_AB_RESET_CNT_LENGTH > 0U)
        if( st_last.u4Reset < SECOC_CD_FV_TRUNC_RESET_MAX )
        {
            /* Make Message Counter MSB */
            u4_mask = SECOC_CD_FV_TRUNC_MSK_BASE << ptRxWork->u4TxFvMsgLen;
            u4_mask -= SECOC_CD_FV_TRUNC_MSK_SUB;
            ptWork->u2Msg = (st_last.u2Msg & (uint16)~u4_mask);

            /* 3 Digit flag check */
            if( ptRxWork->bUpDigit == (boolean)TRUE )
            {
                /* Max check */
                if( ptWork->u2Msg < (uint16)(SECOC_CD_FV_TRUNC_MSG_MAX & ~u4_mask) )
                {
    #if (SECOC_AB_MSG_CNT_LENGTH > 0U)
                    ptWork->u2Msg += (uint16)(SECOC_CD_FV_TRUNC_ADD_BASE << ptRxWork->u4TxFvMsgLen);
    #endif
                    /* Make Message Counter LSB */
                    ptWork->u2Msg |= ptTxFv->u2Msg;
                }
                else
                {
                    /* Overflow MSB and LSB set to MAX */
                    ptWork->u2Msg = (uint16)SECOC_CD_FV_TRUNC_MSG_MAX;
                }
            }
            else
            {
                /* Make Message Counter LSB */
                ptWork->u2Msg |= ptTxFv->u2Msg;
            }
        }
        else
        {
#endif
            /* Max value */
            ptWork->u2Msg = (uint16)SECOC_CD_FV_TRUNC_MSG_MAX;
#if (SECOC_AB_RESET_CNT_LENGTH > 0U)
        }
#endif
    }
    else if( (u4_newTrip > st_last.u4Trip)
      || ( (u4_newTrip == st_last.u4Trip)
        && (ptRxWork->u4NewReset > st_last.u4Reset) ) )
    {
        ptWork->u4Trip  = u4_newTrip;
        ptWork->u4Reset = ptRxWork->u4NewReset;
        ptWork->u2Msg = ptTxFv->u2Msg;
        
        ud_stdRet = E_OK;
        
#if (SECOC_AB_RESET_CNT_LENGTH > 0U)
        if( ptRxWork->u4NewReset >= SECOC_CD_FV_TRUNC_RESET_MAX )
        {
#endif
            /* Max value */
            ptWork->u2Msg = (uint16)SECOC_CD_FV_TRUNC_MSG_MAX;
#if (SECOC_AB_RESET_CNT_LENGTH > 0U)
        }
#endif
    }
    else
    {
        if( ptRxWork->u2Pattern < SECOC_CD_FV_TRUNC_RXPTN4 )
        {
            ud_stdRet = SECOC_E_RETRY;
        }
    }
    
    return ud_stdRet;
}
#endif /* ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U) && (SECOC_AB_RX_PDU_TRUNCFV_MAX > 0U))*/

#define SECOC_STOP_SEC_CD_FV_CODE
#include <SecOC_MemMap.h>

#endif /* SECOC_AB_BUS_TRUNC_MAX */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/*  v2-1-0     :2023/09/28                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
