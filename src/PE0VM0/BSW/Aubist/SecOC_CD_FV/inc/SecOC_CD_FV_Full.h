/* SecOC_CD_FV_Full_h_v2-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | SecOC_CD_FV_/Full/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef SECOC_CD_FV_FULL_H
#define SECOC_CD_FV_FULL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <SecOC_CD_FV.h>
#include "./SecOC_CD_FV_If.h"

#if (SECOC_AB_BUS_FULL_MAX > 0U)

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define SECOC_START_SEC_CD_FV_CODE
#include <SecOC_MemMap.h>

FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_Init
(
    void
);
#if ((SECOC_TX_PDU_PROCESSING == STD_ON) && (SECOC_TX_PDU_PROCESSING_MAX > 0U))
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_ReadTx
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvLen
);
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_ReadTrip
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvLen
);
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_WriteTx
(
    uint16 u2Index,
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    uint32 u4FvLen
);
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_WriteTrip
(
    uint16 u2Index,
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    uint32 u4FvLen
);
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_GetTx
(
    P2CONST(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex,
    P2VAR(SecOC_CD_FV_InOutType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFullFv,
    P2VAR(SecOC_CD_FV_InOutType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptTruncFv
);
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_UpdateTx
(
    uint16 u2Index,
    boolean bUpdate
);
#endif
#if ((SECOC_RX_PDU_PROCESSING == STD_ON) && (SECOC_RX_PDU_PROCESSING_MAX > 0U))
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_ReadRx
(
    uint16 u2Index,
    P2VAR(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    P2VAR(uint32, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFvLen
);
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_WriteRx
(
    uint16 u2Index,
    P2CONST(uint8, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFv,
    uint32 u4FvLen
);
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_GetRx
(
    P2CONST(SecOC_CD_FV_IndexType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptIndex,
    P2CONST(SecOC_CD_FV_InType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptTruncFv,
    uint16 u2Attempt,
    P2VAR(SecOC_CD_FV_InOutType, AUTOMATIC, SECOC_CD_FV_APPL_DATA) ptFullFv
);
FUNC(Std_ReturnType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_UpdateRx
(
    uint16 u2Index,
    boolean bUpdate
);
#endif
FUNC(void, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_ResetBus
(
    uint16 u2BusIndex,
    uint16 u2Index
);
#if(SECOC_AB_RAM_ERROR_CHK == STD_ON)
FUNC(SecOC_ErrorStatusType, SECOC_CD_FV_CODE) SecOC_CD_FV_Full_GetErrorStatus
(
    uint16 u2BusIndex
);
#endif
#define SECOC_STOP_SEC_CD_FV_CODE
#include <SecOC_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* SECOC_AB_BUS_FULL_MAX */

#endif /* SECOC_CD_FV_FULL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version    :Date                                                        */
/*  v2-0-0     :2023/02/28                                                  */
/****************************************************************************/

/**** End of File ***********************************************************/
