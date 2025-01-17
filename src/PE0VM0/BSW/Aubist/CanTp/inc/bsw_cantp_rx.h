/* bsw_cantp_rx_h_v2-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANTP/RX/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANTP_RX_H
#define BSW_CANTP_RX_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
Std_ReturnType  bsw_cantp_rx_CancelReceiveCore( BswConst Bsw_CanTp_CfgType * ptCfgTbl, uint16 u2NSduId );
void            bsw_cantp_rx_MainFunction_Rx( void );
void            bsw_cantp_rx_RxIndSF( BswConst Bsw_CanTp_CfgType * ptCfgTbl, BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo );
void            bsw_cantp_rx_RxIndFF( BswConst Bsw_CanTp_CfgType * ptCfgTbl, BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo );
void            bsw_cantp_rx_RxIndCF( BswConst Bsw_CanTp_CfgType * ptCfgTbl, BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, BswConstR Bsw_CanTp_PduInfoType * ptTpPduInfo );
void            bsw_cantp_rx_TxConfRX( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, Std_ReturnType u1Result );
void            bsw_cantp_rx_ChangeParamBS( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, uint16 u2NewBS );
void            bsw_cantp_rx_ChangeParamSTmin( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl, uint16 u2NewSTmin );
uint16          bsw_cantp_rx_ReadParamBS( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl );
uint16          bsw_cantp_rx_ReadParamSTmin( BswConst Bsw_CanTp_RxNSduCfgType * ptRxNSduCfgTbl );
void            bsw_cantp_rx_ChangeParamBSByIdx( uint16 u2CfgTblIdx, uint16 u2NewBS );
void            bsw_cantp_rx_ChgParamSTminByIdx( uint16 u2CfgTblIdx, uint16 u2NewSTmin );
uint16          bsw_cantp_rx_ReadParamBSByIdx( uint16 u2CfgTblIdx, uint8 u1RxParamPtn );
uint16          bsw_cantp_rx_ReadParaSTminByIdx( uint16 u2CfgTblIdx, uint8 u1RxParamPtn );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* BSW_CANTP_RX_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2017/09/25                                              */
/*  v1-1-0         :2018/12/13                                              */
/*  v1-2-0         :2020/01/23                                              */
/*  v2-0-0         :2020/11/26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
