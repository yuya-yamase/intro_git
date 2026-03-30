/* SecOC_Buff_h_v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC/Buff/HEADER                                          */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef SECOC_BUFF_H
#define SECOC_BUFF_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SecOC.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Buffer Kind */
#define SECOC_BUFF_TX       ((uint16)0U)
#define SECOC_BUFF_RX       ((uint16)1U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    P2VAR(uint8, AUTOMATIC, SECOC_APPL_DATA) ptData;
    uint32  u4Size;
} SecOC_Buff_DataType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CODE
#include <SecOC_MemMap.h>

#if (((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)) || ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)))

FUNC(void, SECOC_CODE) SecOC_Buff_Init
(
    void
);
FUNC(void, SECOC_CODE) SecOC_Buff_Reset
(
    void
);

FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_GetOrder
(
    uint16 u2BuffKind,
    uint16 u2OrderNo,
    P2VAR(uint16, AUTOMATIC, SECOC_APPL_DATA) ptIndex
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_SetOrder
(
    uint16 u2BuffKind,
    uint16 u2Index,
    P2CONST(SecOC_Buff_DataType, AUTOMATIC, SECOC_APPL_DATA) ptSetData
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_SetSelect
(
    uint16 u2BuffKind,
    uint16 u2Index,
    uint32 u4SetPos,
    P2VAR(SecOC_Buff_DataType, AUTOMATIC, SECOC_APPL_DATA) ptSetData
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_GetSelect
(
    uint16 u2BuffKind,
    uint16 u2Index,
    P2VAR(SecOC_Buff_DataType, AUTOMATIC, SECOC_APPL_DATA) ptGetData
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_ClearSelect
(
    uint16 u2BuffKind,
    uint16 u2Index
);
#endif
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
FUNC(SecOC_ErrorStatusType, SECOC_CODE) SecOC_Buff_GetErrorStatusRx
(
    void
);
#endif
#endif /* SECOC_AB_RAM_ERROR_CHK */
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
FUNC(SecOC_ErrorStatusType, SECOC_CODE) SecOC_Buff_GetErrorStatusTx
(
    void
);
#endif
#endif /* SECOC_AB_RAM_ERROR_CHK */

#if (((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U)) || ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U)))
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_ReadDividePos
(
    uint16 u2BuffKind,
    uint16 u2Index,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptGetPos
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_WriteDividePos
(
    uint16 u2BuffKind,
    uint16 u2Index,
    uint32 u4SetPos
);

FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_ReadTotalSize
(
    uint16 u2BuffKind,
    uint16 u2Index,
    P2VAR(uint32, AUTOMATIC, SECOC_APPL_DATA) ptMsgSize
);
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_WriteTotalSize
(
    uint16 u2BuffKind,
    uint16 u2Index,
    uint32 u4SetSize
);

FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_SetNextIndex
(
    uint16 u2BuffKind,
    uint16 u2Index
);
#endif

#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_ClearSelectSize
(
    uint16 u2BuffKind,
    uint16 u2Index
);
#endif
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
FUNC(Std_ReturnType, SECOC_CODE) SecOC_Buff_SetSelectSize
(
    uint16 u2Index,
    uint32 u4SetDataSize
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

#endif /* SECOC_BUFF_H */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
