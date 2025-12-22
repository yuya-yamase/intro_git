/* Dcm_Dsl_TxMsg_h(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name | DCM/Dsl_TxMsg/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/
#ifndef DCM_DSLTXMSG_H
#define DCM_DSLTXMSG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Main_Common.h>
#include "../../Dsl/inc/Dcm_Dsl_Ctrl_local.h"
#include "../../Dsl/inc/Dcm_Dsl_Main.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSL_TX_E_SEND_ERR  ((Std_ReturnType)0x81U) /* Transmission Error      */
#define DCM_DSL_TX_E_DISABLE   ((Std_ReturnType)0x82U) /* Transmission prohibited */
#define DCM_DSL_TX_E_SUPPRES   ((Std_ReturnType)0x83U) /* Transmission suppressed */
#define DCM_DSL_TX_E_NORESP    ((Std_ReturnType)0x84U) /* No answer               */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

#if( DCM_PAGEDBUFFER_ENABLED == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsl_TxMsg_Init
(void);
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_Transmit
(
    const uint16 u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo,
    const Dcm_Dsl_ResponseSettingType u1ResponseKind
);

#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_PosResTransmit
(
    const uint16 u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo
);
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */

FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_TxMsg_NegResTransmit
(
    const uint16 u2PduMapIndex,
    P2CONST(Dcm_TxPduInfoType, AUTOMATIC, DCM_APPL_DATA) ptInfo
);

FUNC(void, DCM_CODE) Dcm_Dsl_TxMsg_CancelTransmit
(
    const uint16 u2PduMapIndex
);

FUNC(void, DCM_CODE) Dcm_Dsl_TxMsg_StopTimer
(void);

FUNC(void, DCM_CODE) Dcm_Dsl_TxMsg_Abort
(void);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* DCM_DSLTXMSG_H */
/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
