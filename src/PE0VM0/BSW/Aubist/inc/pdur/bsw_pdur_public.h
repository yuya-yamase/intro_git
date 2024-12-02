/* bsw_pdur_public_h_V2-0-0                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/PDUR/PUBLIC/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_PDUR_PUBLIC_H
#define BSW_PDUR_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Component Identifier */
/* Upper */
#define BSW_PDUR_UPCOMP_COM                   (0x0000U)
#define BSW_PDUR_UPCOMP_DCM                   (0x0800U)
#define BSW_PDUR_UPCOMP_LDCOM                 (0x1000U)
#define BSW_PDUR_UPCOMP_CDD1                  (0x1800U)
#define BSW_PDUR_UPCOMP_CDD2                  (0x2000U)

/* Lower */
#define BSW_PDUR_LOCOMP_IF                    (0x0000U)
#define BSW_PDUR_LOCOMP_TP                    (0x0800U)
#define BSW_PDUR_LOCOMP_CAN                   (0x0000U)
#define BSW_PDUR_LOCOMP_LIN                   (0x1000U)
#define BSW_PDUR_LOCOMP_SOAD                  (0x2000U)
#define BSW_PDUR_LOCOMP_DOIP                  (0x3000U)
#define BSW_PDUR_LOCOMP_CDD1                  (0x4000U)
#define BSW_PDUR_LOCOMP_CDD2                  (0x5000U)

#define BSW_PDUR_LOCOMP_CANIF                 (BSW_PDUR_LOCOMP_CAN  | BSW_PDUR_LOCOMP_IF)
#define BSW_PDUR_LOCOMP_CANTP                 (BSW_PDUR_LOCOMP_CAN  | BSW_PDUR_LOCOMP_TP)
#define BSW_PDUR_LOCOMP_LINIF                 (BSW_PDUR_LOCOMP_LIN  | BSW_PDUR_LOCOMP_IF)
#define BSW_PDUR_LOCOMP_LINTP                 (BSW_PDUR_LOCOMP_LIN  | BSW_PDUR_LOCOMP_TP)
#define BSW_PDUR_LOCOMP_SOADIF                (BSW_PDUR_LOCOMP_SOAD | BSW_PDUR_LOCOMP_IF)
#define BSW_PDUR_LOCOMP_SOADTP                (BSW_PDUR_LOCOMP_SOAD | BSW_PDUR_LOCOMP_TP)
#define BSW_PDUR_LOCOMP_DOIPIF                (BSW_PDUR_LOCOMP_DOIP | BSW_PDUR_LOCOMP_IF)
#define BSW_PDUR_LOCOMP_DOIPTP                (BSW_PDUR_LOCOMP_DOIP | BSW_PDUR_LOCOMP_TP)
#define BSW_PDUR_LOCOMP_CDD1IF                (BSW_PDUR_LOCOMP_CDD1 | BSW_PDUR_LOCOMP_IF)
#define BSW_PDUR_LOCOMP_CDD1TP                (BSW_PDUR_LOCOMP_CDD1 | BSW_PDUR_LOCOMP_TP)
#define BSW_PDUR_LOCOMP_CDD2IF                (BSW_PDUR_LOCOMP_CDD2 | BSW_PDUR_LOCOMP_IF)
#define BSW_PDUR_LOCOMP_CDD2TP                (BSW_PDUR_LOCOMP_CDD2 | BSW_PDUR_LOCOMP_TP)
#define BSW_PDUR_LOCOMP_CANNM                 (0x6000U)
#define BSW_PDUR_LOCOMP_CANCDD1               (0xB800U)
#define BSW_PDUR_LOCOMP_CANCDD2               (0xC000U)
#define BSW_PDUR_LOCOMP_LINNM                 (0xC800U)
#define BSW_PDUR_LOCOMP_LINCDD1               (0xD000U)
#define BSW_PDUR_LOCOMP_LINCDD2               (0xD800U)
#define BSW_PDUR_LOCOMP_UDPNM                 (0xE000U)
#define BSW_PDUR_LOCOMP_ETHCDD1               (0xE800U)
#define BSW_PDUR_LOCOMP_ETHCDD2               (0xF000U)
#define BSW_PDUR_LOCOMP_XCP                   (0xF800U)

/* Component Identifier for SecOC */
/* Lower */
#define BSW_PDUR_COMPID_CANIF                 (BSW_PDUR_LOCOMP_CAN  | BSW_PDUR_LOCOMP_IF)
#define BSW_PDUR_COMPID_CANTP                 (BSW_PDUR_LOCOMP_CAN  | BSW_PDUR_LOCOMP_TP)
#define BSW_PDUR_COMPID_LINIF                 (BSW_PDUR_LOCOMP_LIN  | BSW_PDUR_LOCOMP_IF)
#define BSW_PDUR_COMPID_LINTP                 (BSW_PDUR_LOCOMP_LIN  | BSW_PDUR_LOCOMP_TP)
#define BSW_PDUR_COMPID_SOADIF                (BSW_PDUR_LOCOMP_SOAD | BSW_PDUR_LOCOMP_IF)
#define BSW_PDUR_COMPID_SOADTP                (BSW_PDUR_LOCOMP_SOAD | BSW_PDUR_LOCOMP_TP)
#define BSW_PDUR_COMPID_DOIPIF                (BSW_PDUR_LOCOMP_DOIP | BSW_PDUR_LOCOMP_IF)
#define BSW_PDUR_COMPID_DOIPTP                (BSW_PDUR_LOCOMP_DOIP | BSW_PDUR_LOCOMP_TP)
#define BSW_PDUR_COMPID_CDD1IF                (BSW_PDUR_LOCOMP_CDD1 | BSW_PDUR_LOCOMP_IF)
#define BSW_PDUR_COMPID_CDD1TP                (BSW_PDUR_LOCOMP_CDD1 | BSW_PDUR_LOCOMP_TP)
#define BSW_PDUR_COMPID_CDD2IF                (BSW_PDUR_LOCOMP_CDD2 | BSW_PDUR_LOCOMP_IF)
#define BSW_PDUR_COMPID_CDD2TP                (BSW_PDUR_LOCOMP_CDD2 | BSW_PDUR_LOCOMP_TP)

/* Upper */
#define BSW_PDUR_COMPID_COM                   (0xC000U)
#define BSW_PDUR_COMPID_DCM                   (0xC800U)
#define BSW_PDUR_COMPID_LDCOM                 (0xD000U)
#define BSW_PDUR_COMPID_CDD1                  (0xD800U)
#define BSW_PDUR_COMPID_CDD2                  (0xE000U)

/* Component Identifier Offset */
#define BSW_PDUR_COMPID_UPOFFSET              (24U)

/* PDU ID */
#define BSW_PDUR_COMP_MASK                    (0xF800U)
#define BSW_PDUR_ID_MASK                      (0x07FFU)
#define BSW_PDUR_INVALID_PDU_ID               (0xFFFFU)
#define BSW_PDUR_LOCOMPKIND_MASK              (0x0800U)

/* Frame ID */
#define BSW_PDUR_INVALID_FRAME_ID             (0xFFFFFFFFUL)

/* TxMode */
#define BSW_PDUR_TX_MODE_PERIODIC             (0x00U)
#define BSW_PDUR_TX_MODE_EVENT                (0x80U)
#define BSW_PDUR_TX_MODE_INVALID              (0xFFU)

/* PDUR State */
#define BSW_PDUR_UNINIT                       (0U)
#define BSW_PDUR_ONLINE                       (1U)

/* Return Value (Extend) */
#define BSW_PDUR_BUSY                         (2U)

/* SecOC Component Identifier */
#define BSW_PDUR_LOCOMP_SECOCIF               (0x0000U)
#define BSW_PDUR_LOCOMP_SECOCTP               (0x8000U)

/* Vendor ID */
#define BSW_PDUR_VENDOR_ID                    (83U)

/* Module ID */
#define BSW_PDUR_MODULE_ID                    (51U)

/* AUTOSAR Release Version */
#define BSW_PDUR_AR_RELEASE_MAJOR_VERSION             (4U)
#define BSW_PDUR_AR_RELEASE_MINOR_VERSION             (5U)
#define BSW_PDUR_AR_RELEASE_REVISION_VERSION               (0U)

/* Vendor Specification Version */
#define BSW_PDUR_SW_MAJOR_VERSION             (4U)
#define BSW_PDUR_SW_MINOR_VERSION             (5U)
#define BSW_PDUR_SW_PATCH_VERSION             (0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8           Bsw_PduR_PBConfigType;
typedef uint16          Bsw_PduR_PBConfigIdType;
typedef uint16          Bsw_PduR_RoutingPathGroupIdType;
typedef uint8           Bsw_PduR_StateType;
typedef uint8           Bsw_PduR_TxModeType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void                    bsw_pdur_st_Init( BswConst Bsw_PduR_PBConfigType* ConfigPtr );
void                    bsw_pdur_st_DeInit( void );
void                    bsw_pdur_st_GetVersionInfo( Std_VersionInfoType* versionInfo );
Bsw_PduR_PBConfigIdType     bsw_pdur_st_GetConfigurationId( void );
void                    bsw_pdur_ctrl_EnableRouting( Bsw_PduR_RoutingPathGroupIdType id );
void                    bsw_pdur_ctrl_DisableRouting( Bsw_PduR_RoutingPathGroupIdType id, boolean initialize );
uint32                  bsw_pdur_rt_GetTxId( PduIdType PduId );
uint32                  bsw_pdur_rt_GetCurrentRxId( PduIdType PduId );
PduIdType               bsw_pdur_inf_GetIpduId( PduIdType PduId );
PduIdType               bsw_pdur_inf_GetLpduId( uint16 CompId, PduIdType PduId );
Bsw_PduR_TxModeType     bsw_pdur_rt_GetTxMode( PduIdType TxPduId );

void                    bsw_pdur_rt_CanIfRxIndication( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
void                    bsw_pdur_rt_CanIfTxConfirm( PduIdType TxPduId, Std_ReturnType result );

void                    bsw_pdur_rt_CanTpTxConfirm( PduIdType id, Std_ReturnType result );
void                    bsw_pdur_rt_CanTpRxIndication( PduIdType id, Std_ReturnType result );
BufReq_ReturnType       bsw_pdur_rt_CanTpStartOfRecept( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
BufReq_ReturnType       bsw_pdur_rt_CanTpCopyRxData( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
BufReq_ReturnType       bsw_pdur_rt_CanTpCopyTxData( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );

Std_ReturnType          bsw_pdur_rt_Cdd1Transmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType          bsw_pdur_rt_Cdd1CancelTx( PduIdType TxPduId );
Std_ReturnType          bsw_pdur_rt_Cdd1CancelReceive( PduIdType RxPduId );

void                    bsw_pdur_rt_Cdd1IfRxIndication( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType          bsw_pdur_rt_Cdd1IfTriggerTx( PduIdType TxPduId, PduInfoType* PduInfoPtr );
void                    bsw_pdur_rt_Cdd1IfTxConfirm( PduIdType TxPduId, Std_ReturnType result );

void                    bsw_pdur_rt_Cdd1TpRxIndication( PduIdType id, Std_ReturnType result );
BufReq_ReturnType       bsw_pdur_rt_Cdd1TpStartOfRecept( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
BufReq_ReturnType       bsw_pdur_rt_Cdd1TpCopyRxData( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
void                    bsw_pdur_rt_Cdd1TpTxConfirm( PduIdType id, Std_ReturnType result );
BufReq_ReturnType       bsw_pdur_rt_Cdd1TpCopyTxData( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );

Std_ReturnType          bsw_pdur_rt_Cdd2Transmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType          bsw_pdur_rt_Cdd2CancelTx( PduIdType TxPduId );
Std_ReturnType          bsw_pdur_rt_Cdd2CancelReceive( PduIdType RxPduId );

void                    bsw_pdur_rt_Cdd2IfRxIndication( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType          bsw_pdur_rt_Cdd2IfTriggerTx( PduIdType TxPduId, PduInfoType* PduInfoPtr );
void                    bsw_pdur_rt_Cdd2IfTxConfirm( PduIdType TxPduId, Std_ReturnType result );

void                    bsw_pdur_rt_Cdd2TpRxIndication( PduIdType id, Std_ReturnType result );
BufReq_ReturnType       bsw_pdur_rt_Cdd2TpStartOfRecept( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
BufReq_ReturnType       bsw_pdur_rt_Cdd2TpCopyRxData( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
void                    bsw_pdur_rt_Cdd2TpTxConfirm( PduIdType id, Std_ReturnType result );
BufReq_ReturnType       bsw_pdur_rt_Cdd2TpCopyTxData( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );

Std_ReturnType          bsw_pdur_rt_ComTransmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType          bsw_pdur_rt_ComCancelTransmit( PduIdType TxPduId );
uint32                  bsw_pdur_rt_ComGetTxId( PduIdType PduId );
uint32                  bsw_pdur_rt_ComGetRxId( PduIdType PduId );
PduIdType               bsw_pdur_inf_ComGetLpduId( PduIdType PduId );

Std_ReturnType          bsw_pdur_rt_DcmTransmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType          bsw_pdur_rt_DcmCancelTransmit( PduIdType TxPduId );
Std_ReturnType          bsw_pdur_rt_DcmCancelReceive( PduIdType RxPduId );

void                    bsw_pdur_rt_DoIPIfTxConfirm( PduIdType TxPduId, Std_ReturnType result );
void                    bsw_pdur_rt_DoIPTpTxConfirm( PduIdType id, Std_ReturnType result );
BufReq_ReturnType       bsw_pdur_rt_DoIPTpCopyTxData( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );
void                    bsw_pdur_rt_DoIPTpRxIndication( PduIdType id, Std_ReturnType result );
BufReq_ReturnType       bsw_pdur_rt_DoIPTpStartOfRecept( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
BufReq_ReturnType       bsw_pdur_rt_DoIPTpCopyRxData( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );

Std_ReturnType          bsw_pdur_rt_IpduMTransmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType          bsw_pdur_rt_IpduMCancelTx( PduIdType TxPduId );
void                    bsw_pdur_rt_IpduMRxIndication( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
void                    bsw_pdur_rt_IpduMTxConfirm( PduIdType TxPduId, Std_ReturnType result );
Std_ReturnType          bsw_pdur_rt_IpduMTriggerTx( PduIdType TxPduId, PduInfoType* PduInfoPtr );

Std_ReturnType          bsw_pdur_rt_LdComTransmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType          bsw_pdur_rt_LdComCancelTransmit( PduIdType TxPduId );

void                    bsw_pdur_rt_LinIfRxIndication( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
void                    bsw_pdur_rt_LinIfTxConfirm( PduIdType TxPduId, Std_ReturnType result );
Std_ReturnType          bsw_pdur_rt_LinIfTriggerTx( PduIdType TxPduId, PduInfoType* PduInfoPtr );

void                    bsw_pdur_rt_LinTpRxIndication( PduIdType RxPduId, Std_ReturnType result );
BufReq_ReturnType       bsw_pdur_rt_LinTpStartOfRecept( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
BufReq_ReturnType       bsw_pdur_rt_LinTpCopyRxData( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
void                    bsw_pdur_rt_LinTpTxConfirm( PduIdType id, Std_ReturnType result );
BufReq_ReturnType       bsw_pdur_rt_LinTpCopyTxData( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );

Std_ReturnType          bsw_pdur_rt_SecOCTransmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
Std_ReturnType          bsw_pdur_rt_SecOCCancelTx( PduIdType TxPduId );
void                    bsw_pdur_rt_SecOCIfRxIndication( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
void                    bsw_pdur_rt_SecOCIfTxConfirm( PduIdType TxPduId, Std_ReturnType result );
void                    bsw_pdur_rt_SecOCTpRxIndication( PduIdType id, Std_ReturnType result );
BufReq_ReturnType       bsw_pdur_rt_SecOCTpSOR( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
BufReq_ReturnType       bsw_pdur_rt_SecOCTpCopyRxData( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
void                    bsw_pdur_rt_SecOCTpTxConfirm( PduIdType id, Std_ReturnType result );
BufReq_ReturnType       bsw_pdur_rt_SecOCTpCopyTxData( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );
Std_ReturnType          bsw_pdur_rt_SecOCCancelRx( PduIdType RxPduId );
Std_ReturnType          bsw_pdur_rt_SecOCIfTriggerTx( PduIdType TxPduId, PduInfoType* PduInfoPtr );

void                    bsw_pdur_rt_SoAdIfRxIndication( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
void                    bsw_pdur_rt_SoAdIfTxConfirm( PduIdType TxPduId, Std_ReturnType result );
Std_ReturnType          bsw_pdur_rt_SoAdIfTriggerTx( PduIdType TxPduId, PduInfoType* PduInfoPtr );
void                    bsw_pdur_rt_SoAdTpRxIndication( PduIdType id, Std_ReturnType result );
BufReq_ReturnType       bsw_pdur_rt_SoAdTpStartOfRecept( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
BufReq_ReturnType       bsw_pdur_rt_SoAdTpCopyRxData( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
void                    bsw_pdur_rt_SoAdTpTxConfirm( PduIdType id, Std_ReturnType result );
BufReq_ReturnType       bsw_pdur_rt_SoAdTpCopyTxData( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );

Std_ReturnType          bsw_pdur_rt_SomeIpTpTransmit( PduIdType TxPduId, BswConstR PduInfoType* PduInfoPtr );
void                    bsw_pdur_rt_SomeIpTpRxInd( PduIdType id, Std_ReturnType result );
BufReq_ReturnType       bsw_pdur_rt_SomeIpTpSOR( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
BufReq_ReturnType       bsw_pdur_rt_SomeIpTpCopyRxData( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
void                    bsw_pdur_rt_SomeIpTpTxConfirm( PduIdType id, Std_ReturnType result );
BufReq_ReturnType       bsw_pdur_rt_SomeIpTpCopyTxData( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_PDUR_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/02/25                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
