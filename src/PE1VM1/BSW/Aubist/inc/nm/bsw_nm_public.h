/* bsw_nm_public_h_v3-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/NM/PUBLIC/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_NM_PUBLIC_H
#define BSW_NM_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Vendor ID */
#define BSW_NM_VENDOR_ID                    (83U)

/* Module ID */
#define BSW_NM_MODULE_ID                    (29U)

/* AUTOSAR Release Version */
#define BSW_NM_AR_RELEASE_MAJOR_VERSION             (4U)
#define BSW_NM_AR_RELEASE_MINOR_VERSION             (5U)
#define BSW_NM_AR_RELEASE_REVISION_VERSION          (0U)

/* Vendor Specification Version */
#define BSW_NM_SW_MAJOR_VERSION             (4U)
#define BSW_NM_SW_MINOR_VERSION             (5U)
#define BSW_NM_SW_PATCH_VERSION             (0U)

/* NM State */
#define BSW_NM_STATE_UNINIT             (0xFF00U)
#define BSW_NM_STATE_BUS_SLEEP          (0x01FEU)
#define BSW_NM_STATE_PREPARE_BUS_SLEEP  (0x02FDU)
#define BSW_NM_STATE_READY_SLEEP        (0x03FCU)
#define BSW_NM_STATE_NORMAL_OPERATION   (0x04FBU)
#define BSW_NM_STATE_REPEAT_MESSAGE     (0x05FAU)
#define BSW_NM_STATE_SYNCHRONIZE        (0x06F9U)
#define BSW_NM_STATE_OFFLINE            (0x07F8U)
#define BSW_NM_STATE_INVALID            (0x00FFU)

/* NM Mode */
#define BSW_NM_MODE_BUS_SLEEP           (0x00U)
#define BSW_NM_MODE_PREPARE_BUS_SLEEP   (0x01U)
#define BSW_NM_MODE_SYNCHRONIZE         (0x02U)
#define BSW_NM_MODE_NETWORK             (0x03U)
#define BSW_NM_MODE_INVALID             (0xFFU)

/* BusNm Type */
#define BSW_NM_BUSNM_CANNM              (0x00U)
#define BSW_NM_BUSNM_LINNM              (0x01U)
#define BSW_NM_BUSNM_UDPNM              (0x02U)
#define BSW_NM_BUSNM_GENERICNM1         (0x03U)
#define BSW_NM_BUSNM_GENERICNM2         (0x04U)
#define BSW_NM_BUSNM_UNDEF              (0xFFU)

/* Direction */
#define BSW_NM_DIRECTION_TX             (0x01U)
#define BSW_NM_DIRECTION_RX             (0x02U)

/* Wakeup Type */
#define BSW_NM_WKUP_PWON                (0x01U)
#define BSW_NM_WKUP_BS                  (0x02U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint16 Bsw_Nm_StateType;
typedef uint8  Bsw_Nm_ModeType;
typedef uint8  Bsw_Nm_BusNmType;
typedef uint8  Bsw_Nm_DirectionType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void            bsw_nm_status_Init( void );
void            bsw_nm_status_DeInit( void );
Std_ReturnType  bsw_nm_sw_PassiveStartUp( NetworkHandleType NetworkHandle );
Std_ReturnType  bsw_nm_sw_NetworkRequest( NetworkHandleType NetworkHandle );
Std_ReturnType  bsw_nm_sw_NetworkRelease( NetworkHandleType NetworkHandle );
Std_ReturnType  bsw_nm_sw_DisableComm( NetworkHandleType NetworkHandle );
Std_ReturnType  bsw_nm_sw_EnableComm( NetworkHandleType NetworkHandle );
Std_ReturnType  bsw_nm_sw_SetUserData( NetworkHandleType NetworkHandle, BswConstR uint8* nmUserDataPtr );
Std_ReturnType  bsw_nm_sw_GetUserData( NetworkHandleType NetworkHandle, uint8* nmUserDataPtr );
Std_ReturnType  bsw_nm_sw_GetPduData( NetworkHandleType NetworkHandle, uint8* nmPduData );
Std_ReturnType  bsw_nm_sw_GetNodeId( NetworkHandleType NetworkHandle, uint8* nmNodeIdPtr );
Std_ReturnType  bsw_nm_sw_GetLocalNodeId( NetworkHandleType NetworkHandle, uint8* nmNodeIdPtr );
Std_ReturnType  bsw_nm_sw_GetState( NetworkHandleType nmNetworkHandle, Bsw_Nm_StateType* nmStatePtr, Bsw_Nm_ModeType* nmModePtr );
void            bsw_nm_status_GetVersionInfo( Std_VersionInfoType* nmVerInfoPtr );
void            bsw_nm_status_MainFunction( void );
uint16          bsw_nm_sw_TransmitEvtWakeup( NetworkHandleType nmNetworkHandle );
void            bsw_nm_sw_CancelEvtWakeup( NetworkHandleType nmNetworkHandle );

void            bsw_nm_sw_CbkPduRxIndication( NetworkHandleType nmNetworkHandle );
void            bsw_nm_coord_CbkCtrlCoBusAwake( void );
Std_ReturnType  bsw_nm_sw_CbkPreTxMsg( PduIdType PduId, NetworkHandleType nmNetworkHandle, PduInfoType* PduInfoPtr );
void            bsw_nm_sw_CbkTRxIndication( PduIdType PduId, NetworkHandleType nmNetworkHandle, BswConstR PduInfoType* PduInfoPtr, Bsw_Nm_DirectionType nmDir );
void            bsw_nm_sw_CbkStateChangeNotif( NetworkHandleType nmNetworkHandle, Bsw_Nm_StateType nmPreviousState, Bsw_Nm_StateType nmCurrentState );
Std_ReturnType  bsw_nm_sw_CbkSetDisableTxTime( NetworkHandleType nmNetworkHandle, uint8 WakeupKind, uint16* EventTimePtr, uint16* PeriTimePtr );

void            bsw_nm_sw_NetworkStartInd( NetworkHandleType nmNetworkHandle );
void            bsw_nm_sw_NetworkMode( NetworkHandleType nmNetworkHandle );
void            bsw_nm_sw_PrepNetworkMode( NetworkHandleType nmNetworkHandle );
void            bsw_nm_sw_BusSleepMode( NetworkHandleType nmNetworkHandle );
void            bsw_nm_sw_PrepBusSleepMode( NetworkHandleType nmNetworkHandle );
void            bsw_nm_sw_PduRxIndication( NetworkHandleType nmNetworkHandle );
void            bsw_nm_sw_StateChangeNotif( NetworkHandleType nmNetworkHandle, Bsw_Nm_StateType nmPreviousState, Bsw_Nm_StateType nmCurrentState );
void            bsw_nm_sw_TxTimeoutException( NetworkHandleType nmNetworkHandle );
void            bsw_nm_sw_EvtWkupTxConfirm( NetworkHandleType nmNetworkHandle, uint16 DisableTime );
void            bsw_nm_sw_TRxIndication( PduIdType PduId, NetworkHandleType nmNetworkHandle, BswConstR PduInfoType* PduInfoPtr, Bsw_Nm_DirectionType nmDir );

Std_ReturnType  bsw_nm_coord_StartSyncSleep( NetworkHandleType nmNetworkHandle );
Std_ReturnType  bsw_nm_coord_CancelSyncSleep( NetworkHandleType nmNetworkHandle );
Std_ReturnType  bsw_nm_coord_ReqSyncPncSlp( NetworkHandleType nmNetworkHandle, PNCHandleType PNC );
Std_ReturnType  bsw_nm_coord_CancelSyncPncSlp( NetworkHandleType nmNetworkHandle, PNCHandleType PNC );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_NM_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/01/12                                             */
/*  v2-1-0          :2022/06/16                                             */
/*  v3-0-0          :2024/10/15                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
