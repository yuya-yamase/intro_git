/* bsw_com_public_h_v3-0-0                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/COM/PUBLIC/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_COM_PUBLIC_H
#define BSW_COM_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_COM_UNINIT                      (0U)
#define BSW_COM_INIT                        (1U)

#define BSW_COM_SERVICE_NOT_AVAILABLE       (0x20U)
#define BSW_COM_BUSY                        (0x21U)
#define BSW_COM_INVALID                     (0x22U)
#define BSW_COM_FIRST_RX                    (0x23U)

#define BSW_COM_IPDUGROUP_NONE              (0x00000000UL)
#define BSW_COM_IPDUGROUP_BAT               (0x00000001UL)
#define BSW_COM_IPDUGROUP_ACC               (0x00000002UL)
#define BSW_COM_IPDUGROUP_IG                (0x00000004UL)
#define BSW_COM_IPDUGROUP_USER1             (0x00000008UL)
#define BSW_COM_IPDUGROUP_USER2             (0x00000010UL)
#define BSW_COM_IPDUGROUP_USER3             (0x00000020UL)
#define BSW_COM_IPDUGROUP_USER4             (0x00000040UL)
#define BSW_COM_IPDUGROUP_USER5             (0x00000080UL)
#define BSW_COM_IPDUGROUP_USER6             (0x00000100UL)
#define BSW_COM_IPDUGROUP_USER7             (0x00000200UL)
#define BSW_COM_IPDUGROUP_USER8             (0x00000400UL)
#define BSW_COM_IPDUGROUP_USER9             (0x00000800UL)
#define BSW_COM_IPDUGROUP_USER10            (0x00001000UL)
#define BSW_COM_IPDUGROUP_USER11            (0x00002000UL)
#define BSW_COM_IPDUGROUP_USER12            (0x00004000UL)
#define BSW_COM_IPDUGROUP_USER13            (0x00008000UL)
#define BSW_COM_IPDUGROUP_USER14            (0x00010000UL)
#define BSW_COM_IPDUGROUP_USER15            (0x00020000UL)
#define BSW_COM_IPDUGROUP_USER16            (0x00040000UL)
#define BSW_COM_IPDUGROUP_USER17            (0x00080000UL)
#define BSW_COM_IPDUGROUP_USER18            (0x00100000UL)
#define BSW_COM_IPDUGROUP_USER19            (0x00200000UL)
#define BSW_COM_IPDUGROUP_USER20            (0x00400000UL)
#define BSW_COM_IPDUGROUP_USER21            (0x00800000UL)
#define BSW_COM_IPDUGROUP_USER22            (0x01000000UL)
#define BSW_COM_IPDUGROUP_USER23            (0x02000000UL)
#define BSW_COM_IPDUGROUP_USER24            (0x04000000UL)
#define BSW_COM_IPDUGROUP_USER25            (0x08000000UL)
#define BSW_COM_IPDUGROUP_USER26            (0x10000000UL)
#define BSW_COM_IPDUGROUP_USER27            (0x20000000UL)
#define BSW_COM_IPDUGROUP_USER28            (0x40000000UL)
#define BSW_COM_IPDUGROUP_USER29            (0x80000000UL)
#define BSW_COM_IPDUGROUP_USER30            (0x00000001UL)
#define BSW_COM_IPDUGROUP_USER31            (0x00000002UL)
#define BSW_COM_IPDUGROUP_USER32            (0x00000004UL)
#define BSW_COM_IPDUGROUP_USER33            (0x00000008UL)
#define BSW_COM_IPDUGROUP_USER34            (0x00000010UL)
#define BSW_COM_IPDUGROUP_USER35            (0x00000020UL)
#define BSW_COM_IPDUGROUP_USER36            (0x00000040UL)
#define BSW_COM_IPDUGROUP_USER37            (0x00000080UL)
#define BSW_COM_IPDUGROUP_USER38            (0x00000100UL)
#define BSW_COM_IPDUGROUP_USER39            (0x00000200UL)
#define BSW_COM_IPDUGROUP_USER40            (0x00000400UL)
#define BSW_COM_IPDUGROUP_USER41            (0x00000800UL)
#define BSW_COM_IPDUGROUP_USER42            (0x00001000UL)
#define BSW_COM_IPDUGROUP_USER43            (0x00002000UL)
#define BSW_COM_IPDUGROUP_USER44            (0x00004000UL)
#define BSW_COM_IPDUGROUP_USER45            (0x00008000UL)
#define BSW_COM_IPDUGROUP_USER46            (0x00010000UL)
#define BSW_COM_IPDUGROUP_USER47            (0x00020000UL)
#define BSW_COM_IPDUGROUP_USER48            (0x00040000UL)
#define BSW_COM_IPDUGROUP_USER49            (0x00080000UL)
#define BSW_COM_IPDUGROUP_USER50            (0x00100000UL)
#define BSW_COM_IPDUGROUP_USER51            (0x00200000UL)
#define BSW_COM_IPDUGROUP_USER52            (0x00400000UL)
#define BSW_COM_IPDUGROUP_USER53            (0x00800000UL)
#define BSW_COM_IPDUGROUP_USER54            (0x01000000UL)
#define BSW_COM_IPDUGROUP_USER55            (0x02000000UL)
#define BSW_COM_IPDUGROUP_USER56            (0x04000000UL)
#define BSW_COM_IPDUGROUP_USER57            (0x08000000UL)
#define BSW_COM_IPDUGROUP_USER58            (0x10000000UL)
#define BSW_COM_IPDUGROUP_USER59            (0x20000000UL)
#define BSW_COM_IPDUGROUP_USER60            (0x40000000UL)
#define BSW_COM_IPDUGROUP_USER61            (0x80000000UL)

#define BSW_COM_TX_MODE_PERIODIC            (0x40U)
#define BSW_COM_TX_MODE_EVENT               (0x80U)
#define BSW_COM_TX_MODE_ALL                 (BSW_COM_TX_MODE_PERIODIC|BSW_COM_TX_MODE_EVENT)
#define BSW_COM_TX_MODE_INVALID             (0x00U)

#define BSW_COM_TX_DISABLE                  (0x00U)
#define BSW_COM_PERIODIC_TX_ENABLE          (0x01U)
#define BSW_COM_EVENT_TX_ENABLE             (0x02U)

#define BSW_COM_STATUS_NONE                 (0x00U)
#define BSW_COM_TRX_START                   (0x80U)
#define BSW_COM_FAILINIT                    (0x20U)
#define BSW_COM_TXSTOP                      (0x10U)
#define BSW_COM_TIMEOUT                     (0x02U)
#define BSW_COM_NO_RX                       (0x01U)

#define BSW_COM_DATATYPE_S                  (0x01U)
#define BSW_COM_DATATYPE_U                  (0x00U)

/* Configuration Value */
#define BSW_COM_TIMER_RETRIGGER_REQ         (0x01U)
#define BSW_COM_TIMER_RETRIGGER_FIN         (0x02U)
#define BSW_COM_TIMER_RETRIGGER_TOUT        (0x03U)
#define BSW_COM_TIMER_RETRIGGER_NONE        (0x00U)

#define BSW_COM_ALIVECOUNTER_PTN0           (0x00U)
#define BSW_COM_ALIVECOUNTER_PTN1           (0x01U)
#define BSW_COM_ALIVECOUNTER_PTN2           (0x02U)
#define BSW_COM_ALIVECOUNTER_PTN3           (0x03U)
#define BSW_COM_ALIVECOUNTER_NONE           (0xFFU)

#define BSW_COM_ENDIAN_LITTLE               (0x00U)
#define BSW_COM_ENDIAN_BIG                  (0x01U)

#define BSW_COM_u1CH00                      ((BswU1) 0U)
#define BSW_COM_u1CH01                      ((BswU1) 1U)
#define BSW_COM_u1CH02                      ((BswU1) 2U)
#define BSW_COM_u1CH03                      ((BswU1) 3U)
#define BSW_COM_u1CH04                      ((BswU1) 4U)
#define BSW_COM_u1CH05                      ((BswU1) 5U)
#define BSW_COM_u1CH06                      ((BswU1) 6U)
#define BSW_COM_u1CH07                      ((BswU1) 7U)
#define BSW_COM_u1CH08                      ((BswU1) 8U)
#define BSW_COM_u1CH09                      ((BswU1) 9U)
#define BSW_COM_u1CH10                      ((BswU1)10U)
#define BSW_COM_u1CH11                      ((BswU1)11U)
#define BSW_COM_u1CH12                      ((BswU1)12U)
#define BSW_COM_u1CH13                      ((BswU1)13U)
#define BSW_COM_u1CH14                      ((BswU1)14U)
#define BSW_COM_u1CH15                      ((BswU1)15U)
#define BSW_COM_u1CH16                      ((BswU1)16U)
#define BSW_COM_u1CH17                      ((BswU1)17U)
#define BSW_COM_u1CH18                      ((BswU1)18U)
#define BSW_COM_u1CH19                      ((BswU1)19U)
#define BSW_COM_u1CH20                      ((BswU1)20U)
#define BSW_COM_u1CH21                      ((BswU1)21U)
#define BSW_COM_u1CH22                      ((BswU1)22U)
#define BSW_COM_u1CH23                      ((BswU1)23U)
#define BSW_COM_u1CH24                      ((BswU1)24U)
#define BSW_COM_u1CH25                      ((BswU1)25U)
#define BSW_COM_u1CH26                      ((BswU1)26U)
#define BSW_COM_u1CH27                      ((BswU1)27U)
#define BSW_COM_u1CH28                      ((BswU1)28U)
#define BSW_COM_u1CH29                      ((BswU1)29U)
#define BSW_COM_u1CH30                      ((BswU1)30U)
#define BSW_COM_u1CH31                      ((BswU1)31U)

#define BSW_COM_u1EVCOND_NONE               ((BswU1)0x00U)
#define BSW_COM_u1EVCOND_CHG0TO1            ((BswU1)0x01U)
#define BSW_COM_u1EVCOND_CHG1TO0            ((BswU1)0x02U)
#define BSW_COM_u1EVCOND_VALCHG             ((BswU1)0x03U)
#define BSW_COM_u1EVCOND_WDATA              ((BswU1)0x04U)

#define BSW_COM_TXTO_REQ_SUCCESS            (0x00U)
#define BSW_COM_TXTO_REQ_WAIT               (0x01U)

/* Message Information Setting */
/* u1ExtFunc */
#define BSW_COM_VPS_USE                     (0x01U)
#define BSW_COM_VPS_NOUSE                   (0x00U)

/* u1TxFunc */
#define BSW_COM_EVENTDELAY_USE              (0x01U)
#define BSW_COM_EVENTDELAY_NOUSE            (0x00U)
#define BSW_COM_EVTAWAKE_USE                (0x02U)
#define BSW_COM_EVTAWAKE_NOUSE              (0x00U)
#define BSW_COM_PREPRDTXRTRG_USE            (0x04U)
#define BSW_COM_PREPRDTXRTRG_NOUSE          (0x00U)
#define BSW_COM_SENDNTIMES_USE              (0x08U)
#define BSW_COM_SENDNTIMES_NOUSE            (0x00U)
#define BSW_COM_CHGPRDIPDU_USE              (0x10U)
#define BSW_COM_CHGPRDIPDU_NOUSE            (0x00U)
#define BSW_COM_EVTWAKEUPTX_USE             (0x20U)
#define BSW_COM_EVTWAKEUPTX_NOUSE           (0x00U)

/* u1Hook */
#define BSW_COM_TXREQCONF_USE               (0x01U)
#define BSW_COM_TXREQCONF_NOUSE             (0x00U)
#define BSW_COM_TXCONF_USE                  (0x02U)
#define BSW_COM_TXCONF_NOUSE                (0x00U)
#define BSW_COM_RXMSG_USE                   (0x04U)
#define BSW_COM_RXMSG_NOUSE                 (0x00U)
#define BSW_COM_PRESTORE_USE                (0x08U)
#define BSW_COM_PRESTORE_NOUSE              (0x00U)
#define BSW_COM_ALIVECOUNTER_USE            (0x10U)
#define BSW_COM_ALIVECOUNTER_NOUSE          (0x00U)
#define BSW_COM_PRETX_USE                   (0x20U)
#define BSW_COM_PRETX_NOUSE                 (0x00U)

/* Vendor ID */
#define BSW_COM_VENDOR_ID                   (83U)

/* Module ID */
#define BSW_COM_MODULE_ID                   (50U)

/* AUTOSAR Release Version */
#define BSW_COM_AR_RELEASE_MAJOR_VERSION    (4U)
#define BSW_COM_AR_RELEASE_MINOR_VERSION    (5U)
#define BSW_COM_AR_RELEASE_REVISION_VERSION (0U)

/* Vendor Specification Version */
#define BSW_COM_SW_MAJOR_VERSION            (4U)
#define BSW_COM_SW_MINOR_VERSION            (5U)
#define BSW_COM_SW_PATCH_VERSION            (0U)

/* Frame ID */
#define BSW_COM_INVALID_FRAME_ID            (0xFFFFFFFFUL)

/* PNC Awake Factor */
#define BSW_COM_u4IPDUGRP_PNC_NONE          (0x00000000UL)
#define BSW_COM_u4IPDUGRP_PNC_0             (0x00000001UL)
#define BSW_COM_u4IPDUGRP_PNC_1             (0x00000002UL)
#define BSW_COM_u4IPDUGRP_PNC_2             (0x00000004UL)
#define BSW_COM_u4IPDUGRP_PNC_3             (0x00000008UL)
#define BSW_COM_u4IPDUGRP_PNC_4             (0x00000010UL)
#define BSW_COM_u4IPDUGRP_PNC_5             (0x00000020UL)
#define BSW_COM_u4IPDUGRP_PNC_6             (0x00000040UL)
#define BSW_COM_u4IPDUGRP_PNC_7             (0x00000080UL)
#define BSW_COM_u4IPDUGRP_PNC_8             (0x00000100UL)
#define BSW_COM_u4IPDUGRP_PNC_9             (0x00000200UL)
#define BSW_COM_u4IPDUGRP_PNC_10            (0x00000400UL)
#define BSW_COM_u4IPDUGRP_PNC_11            (0x00000800UL)
#define BSW_COM_u4IPDUGRP_PNC_12            (0x00001000UL)
#define BSW_COM_u4IPDUGRP_PNC_13            (0x00002000UL)
#define BSW_COM_u4IPDUGRP_PNC_14            (0x00004000UL)
#define BSW_COM_u4IPDUGRP_PNC_15            (0x00008000UL)
#define BSW_COM_u4IPDUGRP_PNC_16            (0x00010000UL)
#define BSW_COM_u4IPDUGRP_PNC_17            (0x00020000UL)
#define BSW_COM_u4IPDUGRP_PNC_18            (0x00040000UL)
#define BSW_COM_u4IPDUGRP_PNC_19            (0x00080000UL)
#define BSW_COM_u4IPDUGRP_PNC_20            (0x00100000UL)
#define BSW_COM_u4IPDUGRP_PNC_21            (0x00200000UL)
#define BSW_COM_u4IPDUGRP_PNC_22            (0x00400000UL)
#define BSW_COM_u4IPDUGRP_PNC_23            (0x00800000UL)
#define BSW_COM_u4IPDUGRP_PNC_24            (0x01000000UL)
#define BSW_COM_u4IPDUGRP_PNC_25            (0x02000000UL)
#define BSW_COM_u4IPDUGRP_PNC_26            (0x04000000UL)
#define BSW_COM_u4IPDUGRP_PNC_27            (0x08000000UL)
#define BSW_COM_u4IPDUGRP_PNC_28            (0x10000000UL)
#define BSW_COM_u4IPDUGRP_PNC_29            (0x20000000UL)
#define BSW_COM_u4IPDUGRP_PNC_30            (0x40000000UL)
#define BSW_COM_u4IPDUGRP_PNC_31            (0x80000000UL)
#define BSW_COM_u4IPDUGRP_PNC_32            (0x00000001UL)
#define BSW_COM_u4IPDUGRP_PNC_33            (0x00000002UL)
#define BSW_COM_u4IPDUGRP_PNC_34            (0x00000004UL)
#define BSW_COM_u4IPDUGRP_PNC_35            (0x00000008UL)
#define BSW_COM_u4IPDUGRP_PNC_36            (0x00000010UL)
#define BSW_COM_u4IPDUGRP_PNC_37            (0x00000020UL)
#define BSW_COM_u4IPDUGRP_PNC_38            (0x00000040UL)
#define BSW_COM_u4IPDUGRP_PNC_39            (0x00000080UL)
#define BSW_COM_u4IPDUGRP_PNC_40            (0x00000100UL)
#define BSW_COM_u4IPDUGRP_PNC_41            (0x00000200UL)
#define BSW_COM_u4IPDUGRP_PNC_42            (0x00000400UL)
#define BSW_COM_u4IPDUGRP_PNC_43            (0x00000800UL)
#define BSW_COM_u4IPDUGRP_PNC_44            (0x00001000UL)
#define BSW_COM_u4IPDUGRP_PNC_45            (0x00002000UL)
#define BSW_COM_u4IPDUGRP_PNC_46            (0x00004000UL)
#define BSW_COM_u4IPDUGRP_PNC_47            (0x00008000UL)
#define BSW_COM_u4IPDUGRP_PNC_48            (0x00010000UL)
#define BSW_COM_u4IPDUGRP_PNC_49            (0x00020000UL)
#define BSW_COM_u4IPDUGRP_PNC_50            (0x00040000UL)
#define BSW_COM_u4IPDUGRP_PNC_51            (0x00080000UL)
#define BSW_COM_u4IPDUGRP_PNC_52            (0x00100000UL)
#define BSW_COM_u4IPDUGRP_PNC_53            (0x00200000UL)
#define BSW_COM_u4IPDUGRP_PNC_54            (0x00400000UL)
#define BSW_COM_u4IPDUGRP_PNC_55            (0x00800000UL)
#define BSW_COM_u4IPDUGRP_PNC_56            (0x01000000UL)
#define BSW_COM_u4IPDUGRP_PNC_57            (0x02000000UL)
#define BSW_COM_u4IPDUGRP_PNC_58            (0x04000000UL)
#define BSW_COM_u4IPDUGRP_PNC_59            (0x08000000UL)
#define BSW_COM_u4IPDUGRP_PNC_60            (0x10000000UL)
#define BSW_COM_u4IPDUGRP_PNC_61            (0x20000000UL)
#define BSW_COM_u4IPDUGRP_PNC_62            (0x40000000UL)
#define BSW_COM_u4IPDUGRP_PNC_63            (0x80000000UL)

/* Wakeup Type */
#define BSW_COM_WKUP_PWON                   (0x01U)
#define BSW_COM_WKUP_BS                     (0x02U)

/* Periodic Tx Reset Reason */
#define BSW_COM_RSTR_NONE                   (0x0FU)
#define BSW_COM_RSTR_BUSWAKEUP              (0x1EU)
#define BSW_COM_RSTR_RESUMETX               (0x2DU)
 
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8          Bsw_Com_StatusType;
typedef uint16         Bsw_Com_SignalIdType;
typedef uint16         Bsw_Com_SignalGroupIdType;
typedef uint16         Bsw_Com_IpduGroupIdType;
typedef uint32*        Bsw_Com_IpduGroupVector;
typedef uint8          Bsw_Com_ServiceIdType;
typedef uint8          Bsw_Com_ConfigType;
typedef uint8          Bsw_Com_TxModeType;
typedef uint8          Bsw_Com_TxStatusType;
typedef uint16         Bsw_Com_DataHandlerType;
typedef uint16         Bsw_Com_MsgOffsetType;
typedef uint16         Bsw_Com_MsgSizeType;
typedef uint8          Bsw_Com_IpduStatusType;
typedef uint32*        Bsw_Com_PncIpduGroupVector;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void                   bsw_com_st_Init( BswConst Bsw_Com_ConfigType* ConfigPtr );
void                   bsw_com_st_Wakeup( BswConst Bsw_Com_ConfigType* ConfigPtr );
void                   bsw_com_st_Shutdown( void );
void                   bsw_com_st_Sleep( void );
void                   bsw_com_st_Reset( BswConst Bsw_Com_ConfigType* ConfigPtr );
void                   bsw_com_ctrl_IpduGroupCtrl( BswConstR Bsw_Com_IpduGroupVector ipduGroupVector );
void                   bsw_com_ctrl_ClearIpduGroup( Bsw_Com_IpduGroupVector ipduGroupVector );
void                   bsw_com_ctrl_SetIpduGroup( Bsw_Com_IpduGroupVector ipduGroupVector, Bsw_Com_IpduGroupIdType ipduGroupId, boolean bitval );
void                   bsw_com_rx_ReceptionDMCtrl( BswConstR Bsw_Com_IpduGroupVector ipduGroupVector );
void                   bsw_com_tx_SetStatus( NetworkHandleType network, Bsw_Com_TxStatusType status );
void                   bsw_com_tx_ResetPeriodicTx( NetworkHandleType network, uint8 ResetReason, uint16 offset );
void                   bsw_com_rx_SetWakeupMask( BswConstR Bsw_Com_IpduGroupVector ipduGroupVector );
void                   bsw_com_st_GetVersionInfo( Std_VersionInfoType* Versioninfo );
Std_ReturnType         bsw_com_tx_SetTxReq( PduIdType PduId );
void                   bsw_com_tx_ImmSetTxReq( PduIdType PduId );
void                   bsw_com_tx_SetPeriTxReq( PduIdType PduId );
void                   bsw_com_tx_SwitchIpduTxMode( PduIdType PduId, boolean Mode );
Std_ReturnType         bsw_com_tx_TriggerTransmit( PduIdType TxPduId, PduInfoType* PduInfoPtr );
void                   bsw_com_rx_ReceiveIndication( PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr );
void                   bsw_com_rx_TpRxIndication( PduIdType id, Std_ReturnType result );
void                   bsw_com_tx_TxConfirmation( PduIdType TxPduId, Std_ReturnType result );
void                   bsw_com_tx_TpTransmitCfm( PduIdType id, Std_ReturnType result );
BufReq_ReturnType      bsw_com_rx_StartOfReception( PduIdType id, BswConstR PduInfoType* info, PduLengthType TpSduLength, PduLengthType* bufferSizePtr );
BufReq_ReturnType      bsw_com_rx_CopyRxData( PduIdType id, BswConstR PduInfoType* info, PduLengthType* bufferSizePtr );
BufReq_ReturnType      bsw_com_tx_CopyTxData( PduIdType id, BswConstR PduInfoType* info, BswConstR RetryInfoType* retry, PduLengthType* availableDataPtr );
void                   bsw_com_rx_MainFunctionRx( void );
void                   bsw_com_tx_MainFunctionTx( void );
void                   bsw_com_fs_CheckRam( void );
Std_ReturnType         bsw_com_data_WriteMsg( PduIdType id, BswConstR uint8* SduDataPtr );
Std_ReturnType         bsw_com_data_SetInitMsg( PduIdType id );
void                   bsw_com_data_SetInitMsgStatus( PduIdType id, uint8 InitStatus );
uint8                  bsw_com_data_SendSignalB( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData );
uint8                  bsw_com_data_SendSignalL( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData );
uint8                  bsw_com_data_SendSignalEvB( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData );
uint8                  bsw_com_data_SendSignalEvL( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData );
uint8                  bsw_com_data_ReceiveSignalB( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, uint8 DataType, void *ptData );
uint8                  bsw_com_data_ReceiveSignalL( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, uint8 DataType, void *ptData );
Std_ReturnType         bsw_com_data_WriteIpduMskTxCnt( PduIdType id, BswConstR uint8* SduDataPtr );
Std_ReturnType         bsw_com_data_SendIPDU( PduIdType TxPduId, BswConstR uint8 *SduDataPtr );
Std_ReturnType         bsw_com_data_SendIPDUMskTxCnt( PduIdType TxPduId, BswConstR uint8 *SduDataPtr );
Std_ReturnType         bsw_com_data_ReadMsg( PduIdType PduId, uint8 *ptMsg );
Bsw_Com_MsgSizeType    bsw_com_data_GetMsgSize( PduIdType PduId );
uint32                 bsw_com_data_GetFrameID( PduIdType PduId );
Bsw_Com_TxModeType     bsw_com_tx_GetCurentTxMode( PduIdType TxPduId );
void                   bsw_com_rx_SetTickTime( PduIdType id, uint16 SetTime );
uint16                 bsw_com_rx_GetTickTimeConfig( PduIdType id );
Std_ReturnType         bsw_com_tx_StopTx( PduIdType PduId );
Std_ReturnType         bsw_com_tx_ResumeTx( PduIdType PduId );
Bsw_Com_IpduStatusType bsw_com_data_GetDataStat( Bsw_Com_DataHandlerType DataHandler );
Bsw_Com_IpduStatusType bsw_com_data_GetMsgStat( PduIdType PduId );
void                   bsw_com_rx_ClearTickTime( PduIdType PduId );
void                   bsw_com_rx_SetRxTickTime( NetworkHandleType network, uint16 Offset );
Std_ReturnType         bsw_com_data_FailInitMsg( PduIdType PduId );
void                   bsw_com_tx_ClearTxIpdu( NetworkHandleType network, Bsw_Com_TxModeType mode );
void                   bsw_com_tx_ClearNonAwakeEvt( NetworkHandleType network, uint32* SysStatus );
void                   bsw_com_tx_StartChangePeriodCh( NetworkHandleType network );
void                   bsw_com_tx_StopChangePeriodCh( NetworkHandleType network );
void                   bsw_com_tx_CancelTxIpdu( PduIdType PduId, Bsw_Com_TxModeType mode );
uint16                 bsw_com_data_GetBackupIPDU( uint8 *BackupAreaPtr );
uint16                 bsw_com_data_SetBackupIPDU( BswConstR uint8 *BackupAreaPtr );
uint8                  bsw_com_data_SndSgnlGrpArry( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint16 DataSize, BswConstR uint8 *ptData );
uint8                  bsw_com_data_SndSgnlGrpArryEv( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint16 DataSize, BswConstR uint8 *ptData );
uint8                  bsw_com_data_RcvSgnlGrpArry( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint16 DataSize, uint8 *ptData );
Bsw_Com_StatusType     bsw_com_st_GetStatus( void );
void                   bsw_com_ctrl_PncIpduGroupCtrl( BswConstR Bsw_Com_PncIpduGroupVector PncIpduGroupVector );
void                   bsw_com_rx_PncReceptionDMCtrl( BswConstR Bsw_Com_PncIpduGroupVector PncIpduGroupVector );
void                   bsw_com_tx_SetPncIpduGrpTxSts( BswConstR Bsw_Com_PncIpduGroupVector PncIpduGroupVector );
uint8                  bsw_com_data_SendSignalB64( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData );
uint8                  bsw_com_data_SendSignalL64( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData );
uint8                  bsw_com_data_SendSignalEvB64( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData );
uint8                  bsw_com_data_SendSignalEvL64( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData );
uint8                  bsw_com_data_ReceiveSignalB64( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, uint8 DataType, void *ptData );
uint8                  bsw_com_data_ReceiveSignalL64( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, uint8 DataType, void *ptData );
uint8                  bsw_com_data_SendSignalBOvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData );
uint8                  bsw_com_data_SendSignalLOvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData );
uint8                  bsw_com_data_SendSignalEvBOvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData );
uint8                  bsw_com_data_SendSignalEvLOvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData );
uint8                  bsw_com_data_SendSignalB64OvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData );
uint8                  bsw_com_data_SendSignalL64OvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData );
uint8                  bsw_com_data_SendSignalEvB64OvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData );
uint8                  bsw_com_data_SendSignalEvL64OvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData );
uint8                  bsw_com_data_ReceiveSignalBOvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, uint8 DataType, void *ptData );
uint8                  bsw_com_data_ReceiveSignalLOvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, uint8 DataType, void *ptData );
uint8                  bsw_com_data_ReceiveSignalB64OvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, uint8 DataType, void *ptData );
uint8                  bsw_com_data_ReceiveSignalL64OvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, uint8 DataType, void *ptData );
void                   bsw_com_tx_SetFirstTxStatus( NetworkHandleType network );
void                   bsw_com_tx_BusWakeup( NetworkHandleType network, uint8 WakeupKind, uint16 DisableSend, uint16 EnablePeriodic );
void                   bsw_com_tx_SetTxDelayTime( PduIdType u2PduId, uint16 SetTime );
void                   bsw_com_tx_SetPeriodicTxTime( PduIdType u2PduId, uint16 SetTime, uint8 FirstOffset );


uint8                  bsw_com_data_SendSgnlMDB( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData, BswConstR uint8 *ptMetaData );
uint8                  bsw_com_data_SendSgnlMDL( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData, BswConstR uint8 *ptMetaData );
uint8                  bsw_com_data_SendSgnlMDEvB( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData, BswConstR uint8 *ptMetaData );
uint8                  bsw_com_data_SendSgnlMDEvL( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData, BswConstR uint8 *ptMetaData );
uint8                  bsw_com_data_SendSgnlMDB64( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData, BswConstR uint8 *ptMetaData );
uint8                  bsw_com_data_SendSgnlMDL64( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData, BswConstR uint8 *ptMetaData );
uint8                  bsw_com_data_SendSgnlMDEvB64( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData, BswConstR uint8 *ptMetaData );
uint8                  bsw_com_data_SendSgnlMDEvL64( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData, BswConstR uint8 *ptMetaData );
uint8                  bsw_com_data_SendSgnlMDBOvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData, BswConstR uint8 *ptMetaData );
uint8                  bsw_com_data_SendSgnlMDLOvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData, BswConstR uint8 *ptMetaData );
uint8                  bsw_com_data_SendSgnlMDEvBOvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData, BswConstR uint8 *ptMetaData );
uint8                  bsw_com_data_SendSgnlMDEvLOvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData, BswConstR uint8 *ptMetaData );
uint8                  bsw_com_data_SendSgnlMDB64OvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData, BswConstR uint8 *ptMetaData );
uint8                  bsw_com_data_SendSgnlMDL64OvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData, BswConstR uint8 *ptMetaData );
uint8                  bsw_com_data_SendSgnlMDEvB64OvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData, BswConstR uint8 *ptMetaData );
uint8                  bsw_com_data_SendSgnlMDEvL64OvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, BswConstR void *ptData, BswConstR uint8 *ptMetaData );

uint8                  bsw_com_data_SndSgnlGrpArryMD( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint16 DataSize, BswConstR uint8 *ptData, BswConstR uint8 *ptMetaData );
uint8                  bsw_com_data_SndSgnlGrpArryMDEv( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint16 DataSize, BswConstR uint8 *ptData, BswConstR uint8 *ptMetaData );

Std_ReturnType         bsw_com_tx_SetTxReqMetaData( PduIdType PduId, BswConstR uint8* MetaData );
void                   bsw_com_tx_SetPeriTxReqMetaData( PduIdType PduId, BswConstR uint8* MetaData );
Std_ReturnType         bsw_com_data_WriteMsgMetaData( PduIdType id, BswConstR uint8* SduDataPtr, BswConstR uint8* MetaData );
Std_ReturnType         bsw_com_data_WrtIpduMskTxCntMD( PduIdType id, BswConstR uint8* SduDataPtr, BswConstR uint8* MetaData );
Std_ReturnType         bsw_com_data_SendIPDUMetaData( PduIdType TxPduId, BswConstR uint8 *SduDataPtr, BswConstR uint8 *MetaData );
Std_ReturnType         bsw_com_data_SendIPDUMskTxCntMD( PduIdType TxPduId, BswConstR uint8 *SduDataPtr, BswConstR uint8 *MetaData );

uint8                  bsw_com_data_ReceiveSgnlMDB( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, uint8 DataType, void *ptData, uint8 *ptMetaData );
uint8                  bsw_com_data_ReceiveSgnlMDL( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, uint8 DataType, void *ptData, uint8 *ptMetaData );
uint8                  bsw_com_data_ReceiveSgnlMDB64( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, uint8 DataType, void *ptData, uint8 *ptMetaData );
uint8                  bsw_com_data_ReceiveSgnlMDL64( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, uint8 DataType, void *ptData, uint8 *ptMetaData );
uint8                  bsw_com_data_ReceiveSgnlMDBOvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, uint8 DataType, void *ptData, uint8 *ptMetaData );
uint8                  bsw_com_data_ReceiveSgnlMDLOvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, uint8 DataType, void *ptData, uint8 *ptMetaData );
uint8                  bsw_com_data_ReceiveSgnlMDB64OvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, uint8 DataType, void *ptData, uint8 *ptMetaData );
uint8                  bsw_com_data_ReceiveSgnlMDL64OvA( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint8 DataSize, uint8 Offset, uint8 DataType, void *ptData, uint8 *ptMetaData );

uint8                  bsw_com_data_RcvSgnlGrpArryMD( Bsw_Com_DataHandlerType DataHandler, Bsw_Com_MsgOffsetType MsgOffset, uint16 DataSize, uint8 *ptData, uint8 *ptMetaData );

Std_ReturnType         bsw_com_data_ReadMsgMetaData( PduIdType PduId, uint8 *ptMsg, uint8 *ptMetaData  );

Std_ReturnType         bsw_com_data_RespSendMetaData( PduIdType PduId, uint8 *MetaData );
Std_ReturnType         bsw_com_data_SetInitMetaData( PduIdType id );
Std_ReturnType         bsw_com_data_SetSendMetaData( PduIdType TxPduId, uint8 *ptMetaData );
Std_ReturnType         bsw_com_data_GetSendMetaData( PduIdType TxPduId, uint8 *ptMetaData );

/* Callback */
void                   bsw_com_tx_TxReqClear( NetworkHandleType network, Bsw_Com_TxModeType mode );
void                   bsw_com_ctrl_CbkStartIPDU( PduIdType PduId );
void                   bsw_com_ctrl_CbkStopIPDU( PduIdType PduId );
void                   bsw_com_rx_RxMsg( PduIdType PduId );
boolean                bsw_com_rx_PreStoreMsg( PduIdType PduId, BswConstR PduInfoType* PduInfoPtr );
void                   bsw_com_rx_TimeoutMsg( PduIdType PduId );
void                   bsw_com_tx_TimeoutTxMsg( PduIdType PduId );
boolean                bsw_com_tx_PreEventTxReq( PduIdType PduId );
boolean                bsw_com_fs_RxAliveCounter( PduIdType PduId, Std_ReturnType CheckResult, uint8 ExpectedCounter, uint8 ReceivedCounter );
void                   bsw_com_tx_CbkTxReq( NetworkHandleType network, PduIdType PduId, Bsw_Com_TxModeType TxMode );
void                   bsw_com_tx_CbkTxAck( PduIdType PduId );
void                   bsw_com_tx_CbkTxErr( PduIdType PduId );
uint16                 bsw_com_tx_CbkPrePeriTxRtrgr( NetworkHandleType network, PduIdType PduId, uint16 NextTime );
boolean                bsw_com_tx_PreTxIpdu( PduIdType PduId, PduInfoType* PduInfoPtr );
void                   bsw_com_tx_PreTrgTxIPdu( PduIdType PduId, PduInfoType* PduInfoPtr );
void                   bsw_com_tx_CbkSetStatus( NetworkHandleType network, Bsw_Com_TxStatusType status );
void                   bsw_com_tx_CbkBusWakeUp( NetworkHandleType network, uint8 WakeupKind );
void                   bsw_com_tx_CbkEnablePeriTx( NetworkHandleType network, uint8 WakeupKind );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_COM_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/09/10                                             */
/*  v2-1-0          :2022/10/11                                             */
/*  v2-2-0          :2023/05/24                                             */
/*  v3-0-0          :2024/11/12                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
