/* bsw_bswm_can_connector_h_v3-0-0                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CAN/CONNECTOR/HEADER                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef     BSW_BSWM_CAN_CONNECTOR_H
#define     BSW_BSWM_CAN_CONNECTOR_H

#include <cansm/bsw_cansm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* BswM Function Table */
typedef struct
{
    void (*CanSM_CurrentState)( NetworkHandleType Network, CanSM_BswMCurrentStateType CurrentState );
} Bsw_BswmCan_BswMFuncTblType;

/* CDD Function Table */
typedef struct
{
    void (*TxConfirmation)( PduIdType TxPduId, Std_ReturnType result );
    void (*RxIndication)( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
} Bsw_BswmCan_CddFuncTblType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void           bsw_bswm_can_BswMCanSMCurrentState( NetworkHandleType Network, CanSM_BswMCurrentStateType CurrentState );

void           bsw_bswm_can_CanTpInit(void);
void           bsw_bswm_can_CanTpShutdown(void);
void           bsw_bswm_can_CanTpMainFunction(void);
void           bsw_bswm_can_CanTpTxConfirmation(PduIdType TxPduId, Std_ReturnType result );
void           bsw_bswm_can_CanTpRxIndication(PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr);
Std_ReturnType bsw_bswm_can_CanTpTransmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType bsw_bswm_can_CanTpCancelTransmit( PduIdType TxPduId );
Std_ReturnType bsw_bswm_can_CanTpCancelReceive( PduIdType RxPduId );
void           bsw_bswm_can_CanTpCheckRam( void );
void           bsw_bswm_can_CanTpEnableTx( NetworkHandleType Network );
void           bsw_bswm_can_CanTpDisableTx( NetworkHandleType Network );

void           bsw_bswm_can_Cdd1TxConfirmation( PduIdType TxPduId, Std_ReturnType result );
void           bsw_bswm_can_Cdd1RxIndication( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
void           bsw_bswm_can_Cdd2TxConfirmation( PduIdType TxPduId, Std_ReturnType result );
void           bsw_bswm_can_Cdd2RxIndication( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );

/* Dummy Function */
void           bsw_bswm_can_BswMCanSMCrntState_dmy( NetworkHandleType Network, CanSM_BswMCurrentStateType CurrentState );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst Bsw_BswmCan_BswMFuncTblType  bsw_bswm_can_cnct_BswM_Func;
extern BswConst Bsw_BswmCan_CddFuncTblType bsw_bswm_can_cnct_Cdd1_Func;
extern BswConst Bsw_BswmCan_CddFuncTblType bsw_bswm_can_cnct_Cdd2_Func;

#endif  /* BSW_BSWM_CAN_CONNECTOR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/02/22                                             */
/*  v1-1-0          :2018/11/16                                             */
/*  v2-0-0          :2021/02/25                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
