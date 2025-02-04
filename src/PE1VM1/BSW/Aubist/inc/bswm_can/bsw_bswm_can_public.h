/* bsw_bswm_can_public_h_v3-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CAN/PUBLIC/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_BSWM_CAN_PUBLIC_H
#define BSW_BSWM_CAN_PUBLIC_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*------------------------------*/
/* Unit:status                  */
/*------------------------------*/
/* Register check               */
#define BSW_BSWM_CAN_RGSTCHK_EVERY           (0x01U)
#define BSW_BSWM_CAN_RGSTCHK_NOTEVERY        (0x00U)
#define BSW_BSWM_CAN_RGSTCHK_NONE            (0xFFU)

#define BSW_BSWM_CAN_WURGSTCHK_BUSAWAKE      (0x00U)
#define BSW_BSWM_CAN_WURGSTCHK_WAKEUP        (0x01U)

/*------------------------------*/
/* Unit:ctrl                    */
/*------------------------------*/
/* Driver Initialization Status */
#define BSW_BSWM_CAN_DRVSTS_OK               (0x00U)
#define BSW_BSWM_CAN_DRVSTS_INITNG           (0x01U)
#define BSW_BSWM_CAN_DRVSTS_REGFAIL          (0x02U)
#define BSW_BSWM_CAN_DRVSTS_UNUSEDREGFAIL      (0x03U)

/* Channel Fail Status          */
#define BSW_BSWM_CAN_CHFAILST_NONE           (0x0000U)
#define BSW_BSWM_CAN_CHFAILST_BUSOFF         (0x0001U)
#define BSW_BSWM_CAN_CHFAILST_SNDLOCK        (0x0002U)
#define BSW_BSWM_CAN_CHFAILST_RCVLOCK        (0x0004U)
#define BSW_BSWM_CAN_CHFAILST_REGCHECK       (0x0008U)
#define BSW_BSWM_CAN_CHFAILST_UNUSEDREGCHK      (0x0010U)
#define BSW_BSWM_CAN_CHFAILST_MPU            (0x0020U)
#define BSW_BSWM_CAN_CHFAILST_INITNG         (0x0040U)
#define BSW_BSWM_CAN_CHFAILST_USER           (0x0080U)
#define BSW_BSWM_CAN_CHFAILST_ERROR_PASSIVE       (0x0100U)
#define BSW_BSWM_CAN_CHFAILST_NMTXTIMEOUT       (0x0200U)

/* Controller Error Status      */
#define BSW_BSWM_CAN_CTRERRST_NONE           (0x00U)
#define BSW_BSWM_CAN_CTRERRST_BUSOFF         (0x01U)
#define BSW_BSWM_CAN_CTRERRST_PASSIVE        (0x02U)

/* Channel Invalid              */
#define BSW_BSWM_CAN_CHANNEL_INVALID         (0xFFU)

/* Reception deadline monitoring period */
#define BSW_BSWM_CAN_DMPRD_NET_ALL           (0x00U)
#define BSW_BSWM_CAN_DMPRD_NET_RPTNRML       (0x01U)

/* Wakeup Type */
#define BSW_BSWM_CAN_WKUP_PWON               (0x01U)
#define BSW_BSWM_CAN_WKUP_BS                 (0x02U)

/* Maximum number of power supply */
#define BSW_BSWM_CAN_SYSSTATMAXNUM           (64U)
#define BSW_BSWM_CAN_SYSSTATTBLNUM           (BSW_BSWM_CAN_SYSSTATMAXNUM >> 5U)

/*------------------------------*/
/* Unit:backup                  */
/*------------------------------*/
/* BackupData Size(MAX)         */
#define BSW_BSWM_CAN_BACKUPDATASIZE          (BSW_BSWM_CAN_BU_MAX_CH_NUM * BSW_BSWM_CAN_BU_CH_DATASIZE)

#define BSW_BSWM_CAN_BU_MAX_CH_NUM           (32U)
#define BSW_BSWM_CAN_BU_CH_DATASIZE          (BSW_BSWM_CAN_BU_CH_CANNM_SIZE + BSW_BSWM_CAN_BU_CH_INITRESULT_SIZE)
#define BSW_BSWM_CAN_BU_CH_CANNM_SIZE         (2U)
#define BSW_BSWM_CAN_BU_CH_INITRESULT_SIZE      (2U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*------------------------------*/
/* Unit:status                  */
/*------------------------------*/
void                 bsw_bswm_can_st_Init( void );
void                 bsw_bswm_can_st_PrepareDeInit( void );
void                 bsw_bswm_can_st_DeInit( void );
void                 bsw_bswm_can_st_Wakeup( void );
void                 bsw_bswm_can_st_Sleep( void );
void                 bsw_bswm_can_st_Reset( void );

void                 bsw_bswm_can_st_MainFuncHiIn( void );
void                 bsw_bswm_can_st_MainFuncHiOut( void );
void                 bsw_bswm_can_st_MainFuncMidIn( void );
void                 bsw_bswm_can_st_MainFuncMidCtrl( void );
void                 bsw_bswm_can_st_MainFuncMidOut( void );

void                 bsw_bswm_can_st_DetectFail( void );
void                 bsw_bswm_can_st_CheckRam( void );
void                 bsw_bswm_can_st_CbkDetectEdge( NetworkHandleType Network );

/*------------------------------*/
/* Unit:ctrl                    */
/*------------------------------*/
void                 bsw_bswm_can_ctrl_InitDriver( void );
uint8                bsw_bswm_can_ctrl_CheckAwake( void );
void                 bsw_bswm_can_ctrl_UpdIPDUStatus( void );
BswM_CS_RetCtrlType  bsw_bswm_can_ctrl_StopTxPdu( NetworkHandleType Network );
BswM_CS_RetCtrlType  bsw_bswm_can_ctrl_ResumeTxPdu( NetworkHandleType Network );
void                 bsw_bswm_can_ctrl_CbkInitDrvInd( NetworkHandleType Network, uint8 DrvStatus );
void                 bsw_bswm_can_ctrl_RestartChCtrl( NetworkHandleType Network );
BswM_CS_RetCtrlType  bsw_bswm_can_ctrl_StopDMControl( NetworkHandleType Network );
BswM_CS_RetCtrlType  bsw_bswm_can_ctrl_ResumeDMCtrl( NetworkHandleType Network );
void                 bsw_bswm_can_ctrl_CbkPreCtrlRx( void );
void                 bsw_bswm_can_ctrl_CbkPreCtrlTx( void );
Std_ReturnType       bsw_bswm_can_ctrl_GetChFailStat( NetworkHandleType network, uint16* state );
Std_ReturnType       bsw_bswm_can_ctrl_GetCtrErrStat( NetworkHandleType network, uint8* state );
uint8                bsw_bswm_can_ctrl_GetTxChannel( PduIdType PduId );
uint8                bsw_bswm_can_ctrl_GetRxChannel( PduIdType PduId );
Std_ReturnType       bsw_bswm_can_ctrl_CbkPreRgstChk( void );

void                 bsw_bswm_can_ctrl_DetectFail( NetworkHandleType Network );
void                 bsw_bswm_can_ctrl_ReleaseFail( NetworkHandleType Network );

void                 bsw_bswm_can_ctrl_UpdateTxIPDU( NetworkHandleType Network );
void                 bsw_bswm_can_ctrl_BusWakeup( NetworkHandleType Network, uint8 WakeupKind, uint16 DisableSend, uint16 EnablePeriodic );
void                 bsw_bswm_can_ctrl_DisableTx( NetworkHandleType Network );
void                 bsw_bswm_can_ctrl_EnableTx( NetworkHandleType Network );
void                 bsw_bswm_can_ctrl_StopNetwork( NetworkHandleType Network );
void                 bsw_bswm_can_ctrl_StartNetwork( NetworkHandleType Network );

/*------------------------------*/
/* Unit:backup                  */
/*------------------------------*/
void                 bsw_bswm_can_bkup_SetBackupData( BswConstR uint8* BackupDataPtr );
void                 bsw_bswm_can_bkup_GetBackupData( uint8* BackupDataPtr );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* BSW_BSWM_CAN_PUBLIC_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2021/12/09                                             */
/*  v2-1-0          :2022/09/15                                             */
/*  v3-0-0          :2024/11/12                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
