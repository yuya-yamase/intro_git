/* bsw_cannm_public_h_V2-4-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/PUBLIC/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_PUBLIC_H
#define BSW_CANNM_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_CANNM_PDU_BYTE_0                   (0x00U)              /* Data position : byte0         */
#define BSW_CANNM_PDU_BYTE_1                   (0x01U)              /* Data position : byte1         */
#define BSW_CANNM_PDU_OFF                      (0xFFU)              /* Data position : NOUSE         */

#define BSW_CANNM_IPDU_DISABLE_SEND            (0x00U)              /* Disable Send                  */
#define BSW_CANNM_IPDU_ENABLE_EVENT            (0x01U)              /* Enable Event Message          */
#define BSW_CANNM_IPDU_ENABLE_PERI             (0x02U)              /* Enable Periodic Message       */

#define BSW_CANNM_MSGTYP_ACTIVE                (0x01U)              /* NM Message Type : ACTIVE      */
#define BSW_CANNM_MSGTYP_WAKEUP                (0x02U)              /* NM Message Type : WAKEUP      */
#define BSW_CANNM_MSGTYP_SLEEP                 (0x03U)              /* NM Message Type : SLEEP       */

#define BSW_CANNM_BUSWKUP_WBS_IMM              (0x01U)              /* BusWakeup Type : WaitBusSleep(Immidiate) */
#define BSW_CANNM_BUSWKUP_WBS                  (0x02U)              /* BusWakeup Type : WaitBusSleep            */
#define BSW_CANNM_BUSWKUP_BS                   (0x04U)              /* BusWakeup Type : BusSleep                */
#define BSW_CANNM_BUSWKUP_WBS_LIMPHOME         (0x08U)              /* BusWakeup Type : WaitBusSleep(LimpHome)  */

#define BSW_CANNM_WKUP_PWON                    (0x01U)              /* Wakeup Type : PowerOn         */
#define BSW_CANNM_WKUP_BS                      (0x02U)              /* Wakeup Type : BusSleep        */

#define BSW_CANNM_BUSAWAKE_NONE                (0x00U)              /* BusAwake Kind : None          */
#define BSW_CANNM_BUSAWAKE_ACTIVE              (0x01U)              /* BusAwake Kind : Active        */
#define BSW_CANNM_BUSAWAKE_PASSIVE             (0x02U)              /* BusAwake Kind : Passive       */

#define BSW_CANNM_u1OK                         ((BswU1)0x00U)       /* Result : OK                   */
#define BSW_CANNM_u1NG                         ((BswU1)0x01U)       /* Result : NG                   */
#define BSW_CANNM_u1DRVFULL                    ((BswU1)0x02U)       /* Result : CANIF TxQueue Full   */
#define BSW_CANNM_u1DRVNG                      ((BswU1)0x03U)       /* Result : CANIF Error          */

#define BSW_CANNM_NMTYPE_NONE                  (0U)                 /* NM Nouse                      */
#define BSW_CANNM_NMTYPE_Z                     (1U)                 /* Use CanNmZ                    */
#define BSW_CANNM_NMTYPE_A                     (2U)                 /* Use CanNmA                    */
#define BSW_CANNM_NMTYPE_A2                    (3U)                 /* Use CanNmA2                   */
#define BSW_CANNM_NMTYPE_B                     (4U)                 /* Use CanNmB                    */
#define BSW_CANNM_NMTYPE_C2                    (5U)                 /* Use CanNmC2                   */
#define BSW_CANNM_NMTYPE_E                     (6U)                 /* Use CanNmE                    */
#define BSW_CANNM_NMTYPE_X                     (7U)                 /* Use CanNmX                    */
#define BSW_CANNM_NMTYPE_Y                     (8U)                 /* Use CanNmY                    */

#define BSW_CANNM_ENATX_WKUP                   (0x01U)              /* EnableTx Reason : Wakeup    */
#define BSW_CANNM_ENATX_TXTO                   (0x02U)              /* EnableTx Reason : TxTimeout */

/* Vendor ID */
#define BSW_CANNM_VENDOR_ID                    (83U)

/* Module ID */
#define BSW_CANNM_MODULE_ID                    (31U)

/* AUTOSAR Release Version */
#define BSW_CANNM_AR_RELEASE_MAJOR_VERSION             (4U)
#define BSW_CANNM_AR_RELEASE_MINOR_VERSION             (5U)
#define BSW_CANNM_AR_RELEASE_REVISION_VERSION               (0U)

/* Vendor Specification Version */
#define BSW_CANNM_SW_MAJOR_VERSION             (4U)
#define BSW_CANNM_SW_MINOR_VERSION             (5U)
#define BSW_CANNM_SW_PATCH_VERSION             (0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    uint8 dummy;
}Bsw_CanNm_ConfigType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void            bsw_cannm_ch_Init(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);
void            bsw_cannm_ch_DeInit(void);
Std_ReturnType  bsw_cannm_ch_PassiveStartUp( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_cannm_ch_NetworkRequest( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_cannm_ch_NetworkRelease( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_cannm_ch_DisableCom( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_cannm_ch_EnableCom( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_cannm_ch_GetState( NetworkHandleType nmChannelHandle, Nm_StateType* nmStatePtr, Nm_ModeType* nmModePtr );
void            bsw_cannm_ch_MainFunction(void);
void            bsw_cannm_ch_MainFunctionHigh(void);
uint8           bsw_cannm_ch_GetIPDUState( NetworkHandleType nmChannelHandle );
void            bsw_cannm_ch_SetBusOff( NetworkHandleType nmChannelHandle );
void            bsw_cannm_ch_CancelTrFr( NetworkHandleType nmChannelHandle );
uint16          bsw_cannm_ch_TransEvtWkup( NetworkHandleType nmChannelHandle );
void            bsw_cannm_ch_CancelEvtWkup( NetworkHandleType nmChannelHandle );
void            bsw_cannm_ch_PduRxIndication( NetworkHandleType nmChannelHandle );
void            bsw_cannm_ch_GetVersionInfo( Std_VersionInfoType* versioninfo );
void            bsw_cannm_ch_CheckRam( void );

Std_ReturnType  bsw_cannm_ch_TransmitFrame( PduIdType TxPduId, NetworkHandleType nmChannelHandle, BswConstR PduInfoType* PduInfoPtr );
void            bsw_cannm_ch_GetTxConfirmedPdu( PduIdType TxPduId, NetworkHandleType nmChannelHandle, PduInfoType* PduInfoPtr );
void            bsw_cannm_ch_EdgeDisableDetect( NetworkHandleType nmChannelHandle );
void            bsw_cannm_ch_EdgeEnableDetect( NetworkHandleType nmChannelHandle );
uint32          bsw_cannm_ch_GetTxCanID( NetworkHandleType nmChannelHandle, PduIdType CanPduId );
uint32          bsw_cannm_ch_GetRxCanID( NetworkHandleType nmChannelHandle, PduIdType CanPduId );

void            bsw_cannm_ch_Wakeup(BswConst Bsw_CanNm_ConfigType* cannmConfigPtr);
void            bsw_cannm_ch_Sleep(void);
uint8           bsw_cannm_ch_CheckAwake( NetworkHandleType nmChannelHandle );
uint16          bsw_cannm_ch_GetBackupData( NetworkHandleType nmChannelHandle );
void            bsw_cannm_ch_SetBackupData( NetworkHandleType nmChannelHandle, uint16 BackupData );

Std_ReturnType  bsw_cannm_ch_GetNodeId( NetworkHandleType nmChannelHandle, uint8* nmNodeIdPtr );
Std_ReturnType  bsw_cannm_ch_GetLocalNodeId( NetworkHandleType nmChannelHandle, uint8* nmNodeIdPtr );
Std_ReturnType  bsw_cannm_ch_SetUserData( NetworkHandleType nmChannelHandle, BswConstR uint8* nmUserDataPtr );
Std_ReturnType  bsw_cannm_ch_GetUserData( NetworkHandleType nmChannelHandle, uint8* nmUserDataPtr );
Std_ReturnType  bsw_cannm_ch_GetPduData( NetworkHandleType nmChannelHandle, uint8* nmPduDataPtr );

void            bsw_cannm_ch_CbkPreTxRingMsg( NetworkHandleType nmChannelHandle );
void            bsw_cannm_ch_CbkBusWakeup( NetworkHandleType nmChannelHandle, uint8 WkupKind );
void            bsw_cannm_ch_CbkEvtWUTxFn( NetworkHandleType nmChannelHandle );
void            bsw_cannm_ch_CbkTxTimeout( NetworkHandleType nmChannelHandle , uint8 MsgType );

Std_ReturnType  bsw_cannm_ch_CbkGetPwonBusAwake( NetworkHandleType nmChannelHandle );
uint8           bsw_cannm_ch_CbkGetBusAwake( NetworkHandleType nmChannelHandle, uint8 WakeupKind );

void            bsw_cannm_ch_CbkPreEnableTx( NetworkHandleType nmChannelHandle, uint8 EnableTxReason );

Std_ReturnType  bsw_cannm_ch_CbkEnComPreReStTmr( NetworkHandleType nmChannelHandle );

void            bsw_cannm_ch_TxConfirmation(PduIdType TxPduId, Std_ReturnType result);
void            bsw_cannm_ch_RxIndication(PduIdType RxPduId, BswConstR PduInfoType* PduInfoPtr);

Std_ReturnType  bsw_cannm_ch_PreTxMsg( PduIdType CanPduId, NetworkHandleType nmChannelHandle, PduInfoType* PduInfoPtr );

Std_ReturnType  bsw_cannm_ch_SetSleepReadyBit( NetworkHandleType nmChannelHandle, boolean nmSleepReadyBit );
Std_ReturnType  bsw_cannm_ch_RequestBusSync( NetworkHandleType nmChannelHandle );
Std_ReturnType  bsw_cannm_ch_ReqSyncPncSlp( NetworkHandleType nmChannelHandle, PNCHandleType PNC );
Std_ReturnType  bsw_cannm_ch_CancelSyncPncSlp( NetworkHandleType nmChannelHandle, PNCHandleType PNC );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif  /* BSW_CANNM_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/01/06                                             */
/*  v2-2-0          :2022/05/24                                             */
/*  v2-4-0          :2023/12/18                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
