/* Dcm_Dsl_RxAbt_h(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | DCM/Dsl_RxAbt/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/
#ifndef DCM_DSLRXABT_H
#define DCM_DSLRXABT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>
#include "../../Dsl/inc/Dcm_Dsl_Main.h"
#include "../../Dsl/inc/Dcm_Dsl_Ctrl_local.h"
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_RX_REQ_OTHER     ((uint8)0x00U)
#define DCM_DSL_RX_REQ_KAL       ((uint8)0x01U)
#define DCM_DSL_RX_REQ_PSEUDOKAL ((uint8)0x02U)
#define DCM_DSL_RX_REQ_NORMAL    ((uint8)0x10U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

FUNC(boolean, DCM_CODE) Dcm_Dsl_RxAbt_ArbitrateSOR
(
    const uint16 u2PduIdMapIndex,
    P2CONST(AB_83_DcmPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo,
    const boolean bOverwriteSOR,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptReqKind
);

FUNC(void, DCM_CODE) Dcm_Dsl_RxAbt_StartOfReception
(
    const uint16 u2PduIdMapIndex,
    const boolean bKeepAliveMsg
);

FUNC(void, DCM_CODE) Dcm_Dsl_RxAbt_ArbitrateRxInd
(
    const uint16 u2PduIdMapIndex
);

FUNC(void, DCM_CODE) Dcm_Dsl_RxAbt_ProcKeepAliveReq
(
    const uint16 u2PduIdMapIndex
);

FUNC(void, DCM_CODE) Dcm_Dsl_RxAbt_ArbitrateRxIndPseudoKAL
(
    const uint16 u2PduIdMapIndex
);

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_RxAbt_GetRxResource
(
    const uint16 u2PduMapIndex
);

FUNC(void, DCM_CODE) Dcm_Dsl_RxAbt_GetCurRxResource
(
    const uint16 u2PduMapIndex,
    P2VAR(Dcm_Dsl_RxResInfoType, AUTOMATIC, DCM_APPL_DATA) ptBufferInfo
);

FUNC(void, DCM_CODE) Dcm_Dsl_RxAbt_GetCurKALResource
(
    const uint16 u2PduMapIndex,
    P2VAR(Dcm_Dsl_RxResInfoType, AUTOMATIC, DCM_APPL_DATA) ptBufferInfo
);

FUNC(void, DCM_CODE) Dcm_Dsl_RxAbt_RxErrNotification
(
    const uint16 u2PduIdMapIndex
);

FUNC(boolean, DCM_CODE) Dcm_Dsl_RxAbt_IsReceivingClient
(
    const uint16 u2PduIdMapIndex
);

FUNC(boolean, DCM_CODE) Dcm_Dsl_RxAbt_IsReceivingDiag
(void);

FUNC(void, DCM_CODE) Dcm_Dsl_RxAbt_Init
(void);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* DCM_DSLRXABT_H */
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-08-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2022-08-30                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
