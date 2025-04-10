/* bsw_cantp_tx_h_v3-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANTP/TX/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANTP_TX_H
#define BSW_CANTP_TX_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
Std_ReturnType  bsw_cantp_tx_TransmitCore( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2NSduId, uint32 u4TxNSduLength );
Std_ReturnType  bsw_cantp_tx_CancelTransmitCore( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2NSduId );
void            bsw_cantp_tx_MainFunction_Tx( void );
void            bsw_cantp_tx_RxIndFC( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo );
void            bsw_cantp_tx_TxConfTX( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Std_ReturnType u1Result );
void            bsw_cantp_tx_TerminateTx( BswConst Bsw_CanTp_TxNSduCfgType * ptTxNSduCfgTbl, Bsw_CanTp_st_SenderStatType * ptSenderStatTbl, Std_ReturnType u1Ret );
void            bsw_cantp_tx_SenderToIdle( Bsw_CanTp_st_SenderStatType * ptSenderStatTbl );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* BSW_CANTP_TX_H */


/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/09/25                                             */
/*  v1-1-0          :2018/12/13                                             */
/*  v2-0-0          :2020/11/26                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
