/* bsw_vcan_tx_h_v2-0-0                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/VCAN/TX/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     BSW_VCAN_TX_H
#define     BSW_VCAN_TX_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_VCAN_CANMSG_UNIQUE_SIZE     (2U)                    /* Can message-specific part size   */
#define BSW_VCAN_CANMSG_BUFFER_SIZE     (16U)                   /* Data size (Can data: 64 byte) */

/* Can message send data length       */
#define BSW_VCAN_CANMSG_SIZE            (BSW_VCAN_CANMSG_UNIQUE_SIZE + BSW_VCAN_CANMSG_BUFFER_SIZE)

#define BSW_VCAN_u4RUP_ADD_SIZE         (3UL)

/* Bit mask */
#define BSW_VCAN_u1MASK_2BIT            ((BswU1)0x03U)

/* Transmit data processing*/
#define BSW_VCAN_u4SNDDATA_INVALID      (0x00000000UL)

/* Can message Index for array access */
#define BSW_VCAN_DATAPOS_FRAME_TOP      (0U)
#define BSW_VCAN_DATAPOS4_SNDDATA_TOP   (2U)

/* CAN-ID mask */
#define BSW_VCAN_u4CANID_FDF_MSK        (0x40000000UL)
#define BSW_VCAN_u4CANID_FDF_CANFD      (0x40000000UL)

/* Data Length size */
#define BSW_CAN_u1DATALEN_MAX_CAN       ((BswU1)8U)
#define BSW_CAN_u1DATALEN_MAX_CANFD     ((BswU1)64U)

/* Virtual communication data */
#define BSW_VCAN_u1DLC_INVALID          ((BswU1)0x00U)          /* DLC:Invalid value    */

/* Virtual MBOX setting */
#define BSW_VCAN_u1TIMING_MASK          ((BswU1)0x0FU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void   bsw_vcan_tx_init( void );
void   bsw_vcan_tx_InitConfirmedTx( BswU1 u1VController );

void   bsw_vcan_tx_InitTx( void );
void   bsw_vcan_tx_InitConfTx( BswU1 u1VController );
void   bsw_vcan_tx_TxConfirm( BswU1 u1VController, BswU1 u1TxTiming );
void   bsw_vcan_tx_InitUTx( void );
void   bsw_vcan_tx_InitConfUTx( BswU1 u1VController );
void   bsw_vcan_tx_UTxConfirm( BswU1 u1VController, BswU1 u1TxTiming );

/* Dummy function */
void   bsw_vcan_tx_InitTxNone( void );
void   bsw_vcan_tx_InitConfTxNone( BswU1 u1VController );
void   bsw_vcan_tx_TxConfNone( BswU1 u1VController, BswU1 u1TxTiming );
void   bsw_vcan_tx_InitUTxNone( void );
void   bsw_vcan_tx_InitConfUTxNone( BswU1 u1VController );
void   bsw_vcan_tx_UTxConfNone( BswU1 u1VController, BswU1 u1TxTiming );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern BswU1 bsw_vcan_tx_u1TxCount[];
extern PduIdType bsw_vcan_tx_stConfirmedPdu[];
extern BswU1 bsw_vcan_tx_stConfirmedMBox[];

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU2 bsw_vcan_tx_u2VirtualHthNum;

extern void (* BswConst bsw_vcan_tx_ptInitTxFunc)( void );
extern void (* BswConst bsw_vcan_tx_ptInitConfTxFunc)( BswU1 u1VController );
extern void (* BswConst bsw_vcan_tx_ptTxConfFunc)( BswU1 u1VController, BswU1 u1TxTiming );

extern void (* BswConst bsw_vcan_tx_ptInitUTxFunc)( void );
extern void (* BswConst bsw_vcan_tx_ptInitConfUTxFunc)( BswU1 u1VController );
extern void (* BswConst bsw_vcan_tx_ptUTxConfFunc)( BswU1 u1VController, BswU1 u1TxTiming );

extern BswConst BswU1 bsw_vcan_stVirtualHohTbl[];
extern BswConst BswU1 bsw_vcan_tx_u1TxLimit[];
extern BswConst BswU1 bsw_vcan_tx_u1UserTxContinue[];
extern BswConst BswU1 bsw_vcan_tx_u1VhthNum[];
extern BswConst BswU2 bsw_vcan_tx_u2VhthTop[];
extern BswConst BswU1 bsw_vcan_tx_u1TxVMboxTop[];
extern BswConst BswU1 bsw_vcan_tx_u1UserTxMBoxNum[];
extern BswConst BswU2 bsw_vcan_tx_u2UserTxVMboxTop[];
extern BswConst BswU1 bsw_vcan_tx_u1UTxVMboxVCtrlTop[];

extern BswConst BswU1* BswConst bsw_vcan_tx_u1TxVMboxTbl[];
extern BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl0[];
extern BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl1[];
extern BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl2[];
extern BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl3[];
extern BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl4[];
extern BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl5[];
extern BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl6[];
extern BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl7[];
extern BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl8[];
extern BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl9[];
extern BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl10[];
extern BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl11[];
extern BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl12[];
extern BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl13[];
extern BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl14[];
extern BswConst BswU1 bsw_vcan_u1TxMBoxTbl_VControl15[];

#endif  /* BSW_VCAN_TX_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/03/21                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
