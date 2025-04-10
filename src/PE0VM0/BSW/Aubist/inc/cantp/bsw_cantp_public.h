/* bsw_cantp_public_h_v3-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANTP/PUBLIC/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANTP_PUBLIC_H
#define BSW_CANTP_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* User Hook return value */
#define BSW_CANTP_PRESEND_TP                   (0U)
#define BSW_CANTP_PRESEND_USER_OK              (1U)
#define BSW_CANTP_PRESEND_USER_NOT_OK          (2U)

/* Vendor ID */
#define BSW_CANTP_VENDOR_ID                    (83U)

/* Module ID */
#define BSW_CANTP_MODULE_ID                    (35U)

/* AUTOSAR Release Version */
#define BSW_CANTP_AR_RELEASE_MAJOR_VERSION     (4U)
#define BSW_CANTP_AR_RELEASE_MINOR_VERSION     (5U)
#define BSW_CANTP_AR_RELEASE_REVISION_VERSION  (0U)

/* Vendor Specification Version */
#define BSW_CANTP_SW_MAJOR_VERSION             (4U)
#define BSW_CANTP_SW_MINOR_VERSION             (5U)
#define BSW_CANTP_SW_PATCH_VERSION             (0U)

/*---------------------*/
/* Configuration value */
/*---------------------*/
/* TRUE/FALSE */
#define BSW_CANTP_TRUE                         (1U)
#define BSW_CANTP_FALSE                        (0U)

/* ON/OFF */
#define BSW_CANTP_ON                           (1U)
#define BSW_CANTP_OFF                          (0U)

/* Dynamic BSSTmin adoption */
#define BSW_CANTP_LATEST_BSSTMIN               (0U)
#define BSW_CANTP_FIRST_BSSTMIN                (1U)
#define BSW_CANTP_FIXED_BSSTMIN                (2U)

/* Change the definition of us STmin */
#define BSW_CANTP_USSTMIN_NORMAL               (0U)
#define BSW_CANTP_USSTMIN_MAX                  (1U)

/* The max Length of Pdu */
#define BSW_CANTP_LENGTH_4K                    (0x00000FFFUL)
#define BSW_CANTP_LENGTH_64K                   (0x0000FFFFUL)
#define BSW_CANTP_LENGTH_4G                    (0xFFFFFFFFUL)

/* CanTp channel mode */
#define BSW_CANTP_MODE_FULL_DUPLEX             (0U)
#define BSW_CANTP_MODE_HALF_DUPLEX             (1U)

/* Network target address type */
#define BSW_CANTP_PHYSICAL                     (0x00U)
#define BSW_CANTP_FUNCTIONAL                   (0x01U)

/* The handling pattern of new message reception at the time of waiting for tx confirmation */
#define BSW_CANTP_TX_INCOMPLETE                (0x00U)
#define BSW_CANTP_TX_REGARD_OK                 (0x01U)
#define BSW_CANTP_TX_REGARD_NG                 (0x02U)

/* Addressing format */
#define BSW_CANTP_STANDARD                     (0x00U)
#define BSW_CANTP_NORMALFIXED                  (0x01U)
#define BSW_CANTP_MIXED                        (0x02U)
#define BSW_CANTP_MIXED29BIT                   (0x03U)
#define BSW_CANTP_EXTENDED                     (0x04U)

/* SeparationTime minimum parameter definition */
#define BSW_CANTP_STMIN_RANGE_SIZE             (256U)

/* DL check(SF) pattern */
#define BSW_CANTP_DLCHKSF_PTN0                 (0x00U)
#define BSW_CANTP_DLCHKSF_PTN1                 (0x01U)

/* DL check error action */
#define BSW_CANTP_ERRACT_ABORT                 (0x00U)
#define BSW_CANTP_ERRACT_IGNORE                (0x01U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef   uint8    Bsw_CanTp_ConfigType;
typedef   uint8    Bsw_CanTp_PreSendReturnType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void                        bsw_cantp_cmn_Init( BswConst Bsw_CanTp_ConfigType * CfgPtr );
void                        bsw_cantp_cmn_GetVersionInfo( Std_VersionInfoType * versioninfo );
void                        bsw_cantp_cmn_Shutdown( void );
Std_ReturnType              bsw_cantp_cmn_Transmit( PduIdType CanTpTxSduId, BswConstR PduInfoType * CanTpTxInfoPtr );
Std_ReturnType              bsw_cantp_cmn_CancelTransmit( PduIdType CanTpTxSduId );
Std_ReturnType              bsw_cantp_cmn_CancelReceive( PduIdType CanTpRxSduId );
Std_ReturnType              bsw_cantp_cmn_ChangeParameter( PduIdType id, TPParameterType parameter, uint16 value );
Std_ReturnType              bsw_cantp_cmn_ReadParameter( PduIdType id, TPParameterType parameter, uint16 * value );
void                        bsw_cantp_cmn_MainFunction( void );

Std_ReturnType              bsw_cantp_rx_CbkPreCheckSOR( PduIdType RxNSduId, PduIdType RxNPduId, uint8 PduLength, BswConstR uint8 * PduDataPtr );
void                        bsw_cantp_rx_CbkRxIndication( PduIdType RxNPduId, BswConstR PduInfoType* PduInfoPtr );
Bsw_CanTp_PreSendReturnType bsw_cantp_tx_CbkPreSendControl( PduIdType TxNPduId, BswConstR PduInfoType * PduInfoPtr );
Std_ReturnType              bsw_cantp_tx_CbkPreAbrtSndCtrl( PduIdType TxNPduId );
uint8                       bsw_cantp_tx_CbkFCCTSRxInd( PduIdType TxNSduId, uint8 BS, uint8 STmin, uint8 STminCyc );


void                        bsw_cantp_snd_EnableTx( NetworkHandleType network );
void                        bsw_cantp_snd_DisableTx( NetworkHandleType network );
void                        bsw_cantp_snd_CbkEnableTx( NetworkHandleType network );
void                        bsw_cantp_snd_CbkDisableTx( NetworkHandleType network );

void                        bsw_cantp_cmn_CheckRam( void );

void                        bsw_cantp_cmn_RxIndication( PduIdType RxPduId, BswConstR PduInfoType * PduInfoPtr );
void                        bsw_cantp_cmn_TxConfirmation( PduIdType TxPduId, Std_ReturnType result );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* BSW_CANTP_PUBLIC_H */


/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/08/17                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
