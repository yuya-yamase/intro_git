/* bsw_cansm_public_h_v3-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANSM/PUBLIC/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANSM_PUBLIC_H
#define BSW_CANSM_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* CanSM State */
#define BSW_CANSM_INITED                       (0U)              /* Inited                      */
#define BSW_CANSM_UNINITED                     (1U)              /* UnInited                    */

/* Fail Status */
#define BSW_CANSM_FAIL_NONE                    (0x0000U)         /* No Fail                     */
#define BSW_CANSM_FAIL_BUSOFF                  (0x0001U)         /* BusOff                      */
#define BSW_CANSM_FAIL_SNDLOCK                 (0x0002U)         /* Send Lock                   */
#define BSW_CANSM_FAIL_RCVLOCK                 (0x0004U)         /* Receive Lock                */
#define BSW_CANSM_FAIL_REGCHECK                (0x0008U)         /* Stuck Register              */
#define BSW_CANSM_FAIL_UNUSEDREGCHK            (0x0010U)         /* Stuck Register(Unused MBox) */
#define BSW_CANSM_FAIL_MPU                     (0x0020U)         /* MPU Fail                    */
#define BSW_CANSM_FAIL_INITNG                  (0x0040U)         /* Initialization error        */
#define BSW_CANSM_FAIL_USER                    (0x0080U)         /* Fail Detected by User       */
#define BSW_CANSM_FAIL_ERROR_PASSIVE           (0x0100U)         /* Error Passive               */
#define BSW_CANSM_FAIL_NMTXTIMEOUT             (0x0200U)         /* Nm Tx Timeout               */

/* TX Confirmation/RX Indication Status */
#define BSW_CANSM_NO_NOTIFICATION              (0x5AU)           /* No TX/RX Indication         */
#define BSW_CANSM_TX_RX_NOTIFICATION           (0xA5U)           /* Exist TX/RX Indication      */

/* Busoff Recovery */
#define BSW_CANSM_BUSOFF_RESET                 (0U)              /* Controller Reset            */
#define BSW_CANSM_BUSOFF_ISO_COMPLIANCE        (1U)              /* ISO Compliance              */

/* CanSM State for BswM */
#define BSW_CANSM_BSWM_NO_COMMUNICATION                  (0U)              /* No Communication            */
#define BSW_CANSM_BSWM_SILENT_COMMUNICATION              (1U)              /* Silent Communication        */
#define BSW_CANSM_BSWM_FULL_COMMUNICATION                (2U)              /* Full Communication          */
#define BSW_CANSM_BSWM_BUS_OFF                 (3U)              /* Bus Off                     */
#define BSW_CANSM_BSWM_CHANGE_BAUDRATE         (4U)              /* Change Baudrate             */
#define BSW_CANSM_BSWM_FAIL                    (5U)              /* Fail(Extension)             */

/* Vendor ID */
#define BSW_CANSM_VENDOR_ID                    (83U)

/* Module ID */
#define BSW_CANSM_MODULE_ID                    (140U)

/* AUTOSAR Release Version */
#define BSW_CANSM_AR_RELEASE_MAJOR_VERSION             (4U)
#define BSW_CANSM_AR_RELEASE_MINOR_VERSION             (5U)
#define BSW_CANSM_AR_RELEASE_REVISION_VERSION               (0U)

/* Vendor Specification Version */
#define BSW_CANSM_SW_MAJOR_VERSION             (4U)
#define BSW_CANSM_SW_MINOR_VERSION             (5U)
#define BSW_CANSM_SW_PATCH_VERSION             (0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Data structure for the post build parameters */
typedef struct
{
    uint8 Dummy;   /* Dummy */
} Bsw_CanSM_ConfigType;

typedef uint8   Bsw_CanSM_StateType;                        /* CanSM State                          */
typedef uint8   Bsw_CanSM_NotifStatusType;                  /* TX Confirmation/RX Indication Status */

typedef uint8   Bsw_CanSM_BswMCurrentStateType;             /* CanSM State for BswM                 */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void                      bsw_cansm_st_Init( BswConst Bsw_CanSM_ConfigType* ConfigPtr );
Std_ReturnType            bsw_cansm_st_StartWakeupSrc( NetworkHandleType network );
Std_ReturnType            bsw_cansm_st_StopWakeupSrc( NetworkHandleType network );
void                      bsw_cansm_st_GetVersionInfo( Std_VersionInfoType* VersionInfo ); 
void                      bsw_cansm_st_MainFunction( void );

Std_ReturnType            bsw_cansm_st_RequestComMode( NetworkHandleType network, ComM_ModeType ComM_Mode );
Std_ReturnType            bsw_cansm_st_GetCrntComMode( NetworkHandleType network, ComM_ModeType* ComM_ModePtr );

void                      bsw_cansm_fs_ControllerBusOff( uint8 ControllerId );
void                      bsw_cansm_st_CtrlModeInd( uint8 ControllerId, CanIf_ControllerModeType ControllerMode );
void                      bsw_cansm_st_TrcvModeInd( uint8 TransceiverId, CanTrcv_TrcvModeType TransceiverMode );

/* Extention */
void                      bsw_cansm_st_DeInit( void );
Std_ReturnType            bsw_cansm_st_InitDriver( NetworkHandleType network, boolean RegChk );
Std_ReturnType            bsw_cansm_st_Restart( NetworkHandleType network);
Bsw_CanSM_NotifStatusType bsw_cansm_trx_GetTxCfmState( NetworkHandleType network );
Bsw_CanSM_NotifStatusType bsw_cansm_trx_GetRxIndState( NetworkHandleType network );
uint16                    bsw_cansm_fs_GetFailStatus( NetworkHandleType network );
uint8                     bsw_cansm_fs_GetInitFail( NetworkHandleType network );
uint16                    bsw_cansm_fs_GetControllerErrSt( NetworkHandleType network );
void                      bsw_cansm_fs_EnableRcvLock( NetworkHandleType network );
void                      bsw_cansm_fs_DisableRcvLock( NetworkHandleType network );
void                      bsw_cansm_st_ChkRam( void );

uint8                     bsw_cansm_fs_GetUserFail( uint8 ControllerId );

/* Extention(Callback) */
uint8                     bsw_cansm_fs_CbkJudgeFail( NetworkHandleType network );
void                      bsw_cansm_fs_CbkDetectBusoff( NetworkHandleType network );
void                      bsw_cansm_fs_CbkDetectRcvLock( NetworkHandleType network );
void                      bsw_cansm_fs_CbkDetectMPUFail( NetworkHandleType network );
void                      bsw_cansm_fs_CbkDetectSendLock( NetworkHandleType network );
void                      bsw_cansm_fs_CbkDetectNmTxTout( NetworkHandleType network );
sint16                    bsw_cansm_fs_CbkSetBORestartTm( NetworkHandleType network, sint16 msTime );
sint16                    bsw_cansm_fs_CbkSetUFRestartTm( NetworkHandleType network );
void                      bsw_cansm_st_CbkPreRestChCtrl( NetworkHandleType network );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_CANSM_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/05/13                                             */
/*  v2-1-0          :2022/09/06                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
