/* bsw_ldcom_cmn_h_v3-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/LDCOM/CMN/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_LDCOM_CMN_H
#define BSW_LDCOM_CMN_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Registered number of ALL LdCom HandleID */
#define BSW_LDCOM_HANDLE_ID_REG_NUM         ( BSW_LDCOM_CFG_IF_RX_REG_NUM + BSW_LDCOM_CFG_IF_TX_REG_NUM + BSW_LDCOM_CFG_TP_RX_REG_NUM + BSW_LDCOM_CFG_TP_TX_REG_NUM )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* HandleID information [ common unit ] */
typedef struct
{
    uint16                  u2HandleType;                   /* HandleId Type          */
    uint16                  u2IndvIndex;                    /* individual Index       */
    PduIdType               u2PduRHandleID;                 /* PduR HandleID          */
}Bsw_LdCom_HandleIdInfoComType;

/* HandleID information [ IF_RX individual unit ] */
typedef struct
{
    void    ( *ptRxIndFunc )( BswConstR PduInfoType * PduInfoPtr ); /* Cbk RxIndication       */
}Bsw_LdCom_HandleIdInfoIfRxType;

/* HandleID information [ IF_TX individual unit ] */
typedef struct
{
    Std_ReturnType  ( *ptTrgTrnsFunc )( PduInfoType * PduInfoPtr ); /* Cbk TriggerTransmit    */
    void            ( *ptTxConfFunc )( Std_ReturnType result );     /* Cbk TxConfirmation     */
}Bsw_LdCom_HandleIdInfoIfTxType;

/* HandleID information [ TP_RX individual unit ] */
typedef struct
{
    BufReq_ReturnType   ( *ptStrRecpFunc )( BswConstR PduInfoType * info, PduLengthType TpSduLength, PduLengthType * bufferSizePtr );         /* Cbk StartOfReception   */
    BufReq_ReturnType   ( *ptRxDataFunc )( BswConstR PduInfoType * info, PduLengthType * bufferSizePtr );                                     /* Cbk CopyRxData         */
    void                ( *ptTpRxIndFunc )( Std_ReturnType result );                                                                          /* Cbk TpRxIndication     */
}Bsw_LdCom_HandleIdInfoTpRxType;

/* HandleID information [ TP_TX individual unit ] */
typedef struct
{
    BufReq_ReturnType   ( *ptTxDataFunc )( BswConstR PduInfoType * info, BswConstR RetryInfoType * retry, PduLengthType * availableDataPtr ); /* Cbk CopyTxData         */
    void                ( *ptTpTxConfFunc )( Std_ReturnType result );                                                                         /* Cbk TpTxConfirmation   */
}Bsw_LdCom_HandleIdInfoTpTxType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void                bsw_ldcom_rx_dmy_CbkRxInd( BswConstR PduInfoType * PduInfoPtr );
Std_ReturnType      bsw_ldcom_CbkTriggerTransmit_dummy( PduInfoType * PduInfoPtr );
void                bsw_ldcom_CbkTxConfirmation_dummy( Std_ReturnType result );
BufReq_ReturnType   bsw_ldcom_rx_dmy_CbkStartOfRx( BswConstR PduInfoType * info, PduLengthType TpSduLength, PduLengthType * bufferSizePtr );
BufReq_ReturnType   bsw_ldcom_rx_dmy_CbkCopyRxData( BswConstR PduInfoType * info, PduLengthType * bufferSizePtr );
void                bsw_ldcom_rx_dmy_CbkTpRxInd( Std_ReturnType result );
BufReq_ReturnType   bsw_ldcom_tx_dmy_CbkCopyTxData( BswConstR PduInfoType * info, BswConstR RetryInfoType * retry, PduLengthType * availableDataPtr );
void                bsw_ldcom_tx_dmy_CbkTpTxConf( Std_ReturnType result );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* Handle ID information common table */
extern  BswConst    Bsw_LdCom_HandleIdInfoComType bsw_ldcom_stHandleIdInfoComTbl[];

/* Handle ID information individual table */
extern  BswConst    Bsw_LdCom_HandleIdInfoIfRxType bsw_ldcom_stHandleIdInfoIfRxTbl[];
extern  BswConst    Bsw_LdCom_HandleIdInfoIfTxType bsw_ldcom_stHandleIdInfoIfTxTbl[];
extern  BswConst    Bsw_LdCom_HandleIdInfoTpRxType bsw_ldcom_stHandleIdInfoTpRxTbl[];
extern  BswConst    Bsw_LdCom_HandleIdInfoTpTxType bsw_ldcom_stHandleIdInfoTpTxTbl[];

/* Registered number of ALL LdCom HandleID */
extern  BswConst    PduIdType bsw_ldcom_u2HandleIdNum;

/* Constant of routing destination information from the information individual table getting */
extern  BswConst    Bsw_LdCom_HandleIdInfoIfRxType* BswConst bsw_ldcom_ptIfRxRoutingInfo;
extern  BswConst    Bsw_LdCom_HandleIdInfoIfTxType* BswConst bsw_ldcom_ptIfTxRoutingInfo;
extern  BswConst    Bsw_LdCom_HandleIdInfoTpRxType* BswConst bsw_ldcom_ptTpRxRoutingInfo;
extern  BswConst    Bsw_LdCom_HandleIdInfoTpTxType* BswConst bsw_ldcom_ptTpTxRoutingInfo;

#endif  /* BSW_LDCOM_CMN_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-1-0          :2019/01/25                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
