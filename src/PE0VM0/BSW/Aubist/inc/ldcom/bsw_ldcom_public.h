/* bsw_ldcom_public_h_v3-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/LDCOM/PUBLIC/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_LDCOM_PUBLIC_H
#define BSW_LDCOM_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Vendor ID */
#define BSW_LDCOM_VENDOR_ID                     (83U)

/* Module ID */
#define BSW_LDCOM_MODULE_ID                     (49U)

/* AUTOSAR Release Version */
#define BSW_LDCOM_AR_RELEASE_MAJOR_VERSION              (4U)
#define BSW_LDCOM_AR_RELEASE_MINOR_VERSION              (5U)
#define BSW_LDCOM_AR_RELEASE_REVISION_VERSION                (0U)

/* Vendor Specification Version */
#define BSW_LDCOM_SW_MAJOR_VERSION              (4U)
#define BSW_LDCOM_SW_MINOR_VERSION              (5U)
#define BSW_LDCOM_SW_PATCH_VERSION              (0U)

/* HandleID Type [ Api Type + I-Pdu Direction ] */
#define BSW_LDCOM_HANDLE_ID_TYPE_IF_RX          (0x0101U)
#define BSW_LDCOM_HANDLE_ID_TYPE_IF_TX          (0x0102U)
#define BSW_LDCOM_HANDLE_ID_TYPE_TP_RX          (0x0201U)
#define BSW_LDCOM_HANDLE_ID_TYPE_TP_TX          (0x0202U)

/* PduR Handle ID */
#define BSW_LDCOM_PDUR_HANDLE_ID_NONE           (0xFFFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Initialization Data */
typedef struct
{
    uint32      u4IPduCount;            /* Number of registered   */
                                        /*   I-Pdu containers     */
}Bsw_LdCom_ConfigType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void                bsw_ldcom_st_Init( BswConst Bsw_LdCom_ConfigType * config );
void                bsw_ldcom_st_DeInit( void );
Std_ReturnType      bsw_ldcom_tx_Transmit( PduIdType Id, BswConstR PduInfoType * InfoPtr );
Std_ReturnType      bsw_ldcom_tx_CancelTransmit( PduIdType Id );
void                bsw_ldcom_st_GetVersionInfo( Std_VersionInfoType * versioninfo );

Std_ReturnType      bsw_ldcom_tx_TriggerTransmit( PduIdType TxPduId, PduInfoType * PduInfoPtr );
void                bsw_ldcom_tx_Confirmation( PduIdType TxPduId, Std_ReturnType result );
BufReq_ReturnType   bsw_ldcom_tx_CopyTxData( PduIdType id, BswConstR PduInfoType * info, BswConstR RetryInfoType * retry, PduLengthType * availableDataPtr );
void                bsw_ldcom_tx_TpConfirmation( PduIdType id, Std_ReturnType result );
void                bsw_ldcom_rx_Indication( PduIdType RxPduId, BswConstR PduInfoType * PduInfoPtr );
BufReq_ReturnType   bsw_ldcom_rx_StartOfReception( PduIdType id, BswConstR PduInfoType * info, PduLengthType TpSduLength, PduLengthType * bufferSizePtr );
BufReq_ReturnType   bsw_ldcom_rx_CopyRxData( PduIdType id, BswConstR PduInfoType * info, PduLengthType * bufferSizePtr );
void                bsw_ldcom_rx_TpIndication( PduIdType id, Std_ReturnType result );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* BSW_LDCOM_PUBLIC_H */


/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/05/13                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
