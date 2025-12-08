/* can_rscf3_tx_h_m10700_v3-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CAN/RSCF3/TX/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     CAN_RSCF3_TX_H
#define     CAN_RSCF3_TX_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* コントローラ別送信完了割り込みの使用/未使用 */
#define CAN_TX_TXFINISH_USE_0 \
    ( ( ( CAN_CFG_CONTROLLER_ACTIVATION_0 == CAN_TRUE ) \
     && ( CAN_CFG_CONTROLLER_CAN_0 == CAN_USE )         \
     && ( CAN_CFG_TX_PROCESSING_0 == CAN_INTERRUPT ) ) ? CAN_USE : CAN_NOUSE )

#define CAN_TX_TXFINISH_USE_1 \
    ( ( ( CAN_CFG_CONTROLLER_ACTIVATION_1 == CAN_TRUE ) \
     && ( CAN_CFG_CONTROLLER_CAN_1 == CAN_USE )         \
     && ( CAN_CFG_TX_PROCESSING_1 == CAN_INTERRUPT ) ) ? CAN_USE : CAN_NOUSE )

#define CAN_TX_TXFINISH_USE_2 \
    ( ( ( CAN_CFG_CONTROLLER_ACTIVATION_2 == CAN_TRUE ) \
     && ( CAN_CFG_CONTROLLER_CAN_2 == CAN_USE )         \
     && ( CAN_CFG_TX_PROCESSING_2 == CAN_INTERRUPT ) ) ? CAN_USE : CAN_NOUSE )

#define CAN_TX_TXFINISH_USE_3 \
    ( ( ( CAN_CFG_CONTROLLER_ACTIVATION_3 == CAN_TRUE ) \
     && ( CAN_CFG_CONTROLLER_CAN_3 == CAN_USE )         \
     && ( CAN_CFG_TX_PROCESSING_3 == CAN_INTERRUPT ) ) ? CAN_USE : CAN_NOUSE )

#define CAN_TX_TXFINISH_USE_4 \
    ( ( ( CAN_CFG_CONTROLLER_ACTIVATION_4 == CAN_TRUE ) \
     && ( CAN_CFG_CONTROLLER_CAN_4 == CAN_USE )         \
     && ( CAN_CFG_TX_PROCESSING_4 == CAN_INTERRUPT ) ) ? CAN_USE : CAN_NOUSE )

#define CAN_TX_TXFINISH_USE_5 \
    ( ( ( CAN_CFG_CONTROLLER_ACTIVATION_5 == CAN_TRUE ) \
     && ( CAN_CFG_CONTROLLER_CAN_5 == CAN_USE )         \
     && ( CAN_CFG_TX_PROCESSING_5 == CAN_INTERRUPT ) ) ? CAN_USE : CAN_NOUSE )

#define CAN_TX_TXFINISH_USE_6 \
    ( ( ( CAN_CFG_CONTROLLER_ACTIVATION_6 == CAN_TRUE ) \
     && ( CAN_CFG_CONTROLLER_CAN_6 == CAN_USE )         \
     && ( CAN_CFG_TX_PROCESSING_6 == CAN_INTERRUPT ) ) ? CAN_USE : CAN_NOUSE )

#define CAN_TX_TXFINISH_USE_7 \
    ( ( ( CAN_CFG_CONTROLLER_ACTIVATION_7 == CAN_TRUE ) \
     && ( CAN_CFG_CONTROLLER_CAN_7 == CAN_USE )         \
     && ( CAN_CFG_TX_PROCESSING_7 == CAN_INTERRUPT ) ) ? CAN_USE : CAN_NOUSE )

/* 送信完了割り込み共通処理の使用/未使用 */
#define CAN_TX_TXFINISH_ANYCH_USE \
    ( ( ( CAN_TX_TXFINISH_USE_0 == CAN_USE ) \
     || ( CAN_TX_TXFINISH_USE_1 == CAN_USE ) \
     || ( CAN_TX_TXFINISH_USE_2 == CAN_USE ) \
     || ( CAN_TX_TXFINISH_USE_3 == CAN_USE ) \
     || ( CAN_TX_TXFINISH_USE_4 == CAN_USE ) \
     || ( CAN_TX_TXFINISH_USE_5 == CAN_USE ) \
     || ( CAN_TX_TXFINISH_USE_6 == CAN_USE ) \
     || ( CAN_TX_TXFINISH_USE_7 == CAN_USE ) ) ? CAN_USE : CAN_NOUSE )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/**********************/
/* CAN共通部項目      */
/**********************/
void  Can_tx_Init( void );
void  Can_tx_ClearTxInf( uint8 u1Controller );
void  Can_tx_TxConfMbox( uint8 u1Controller, uint8 u1Mbox );


/**********************/
/* マイコン依存部項目 */
/**********************/
uint8 Can_tx_TxReq_CanFrame( uint8 u1Controller, uint8 u1Mbox, CanConstR CanMsgType* ptMsg );
uint8 Can_tx_TxReq_CanFdFrame( uint8 u1Controller, uint8 u1Mbox, CanConstR CanMsgType* ptMsg );
uint8 Can_tx_ChkTxFinMbox( uint8 u1Controller, uint8 u1Kind );
uint8 Can_tx_TxAbt( uint8 u1Controller, uint8 u1Mbox );
void  Can_tx_ChkTxAbtMbox( uint8 u1Controller );
void  Can_tx_TxAbtAll( uint8 u1Controller );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* CAN_RSCF3_TX_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-1-0         :2017/08/31                                              */
/*  v2-2-0         :2020/02/26                                              */
/*  v3-0-0         :2025/02/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
