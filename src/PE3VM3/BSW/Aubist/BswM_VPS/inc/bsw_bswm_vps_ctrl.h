/* bsw_bswm_vps_ctrl_h_v3-0-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/VPS/CTRL/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef     BSW_BSWM_VPS_CTRL_H
#define     BSW_BSWM_VPS_CTRL_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_BSWM_VPS_CHANNEL_INVALID          (0xFFU)

#define BSW_BSWM_VPS_SYSSTATMAXNUM            (64U)
#define BSW_BSWM_VPS_SYSSTATTBLNUM            (BSW_BSWM_VPS_SYSSTATMAXNUM >> 5U)
#define BSW_BSWM_VPS_INDEX_0                  (0U)
#define BSW_BSWM_VPS_INDEX_1                  (1U)

/* RLY_ON_CONF Message */
#define BSW_BSWM_VPS_u1RLYCONFREQ_NONE        ((BswU1)0x00U)         /* Request None */
#define BSW_BSWM_VPS_u1RLYCONFREQ_WKUP        ((BswU1)0x01U)         /* Wakeup Request Exists */
#define BSW_BSWM_VPS_u1RLYCONFREQ_SLP         ((BswU1)0x02U)         /* Sleep Request Exists */
#define BSW_BSWM_VPS_u1RLYCONFREQ_RESERVE     ((BswU1)0x03U)         /* Reserve */
#define BSW_BSWM_VPS_u1RLYCONFACK_NONE        ((BswU1)0x00U)         /* Request None */
#define BSW_BSWM_VPS_u1RLYCONFACK_WKUP        ((BswU1)0x01U)         /* Wakeup Finish Response Exists */
#define BSW_BSWM_VPS_u1RLYCONFACK_SLP         ((BswU1)0x02U)         /* Sleep Finish Responese Exists */
#define BSW_BSWM_VPS_u1RLYCONFACK_RESERVE     ((BswU1)0x03U)         /* Reserve */
#define BSW_BSWM_VPS_u1RLYCONFINFO_MASK       ((BswU1)0x03U)         /* Mask for RlyOnConf Info */

/* Transition Status */
#define BSW_BSWM_VPS_u1VPSTRANS_NONE          ((BswU1)0x0FU)        /* Not Called StartHandling */
#define BSW_BSWM_VPS_u1VPSTRANS_REQ_ROC       ((BswU1)0x1EU)        /* RlyOnConf Request Exists */
#define BSW_BSWM_VPS_u1VPSTRANS_SENDING_ROC   ((BswU1)0x2DU)        /* RlyOnConf Request in Progress */
#define BSW_BSWM_VPS_u1VPSTRANS_REQ_VPS       ((BswU1)0x3CU)        /* Handling is over, but VPS Tx is not done */
#define BSW_BSWM_VPS_u1VPSTRANS_DONE          ((BswU1)0x4BU)        /* Handling and VPS Tx is done */

/* Timer Status */
#define BSW_BSWM_VPS_u1TIMER_ON               ((BswU1)0x0FU)         /* During timer operation */
#define BSW_BSWM_VPS_u1TIMER_OFF              ((BswU1)0x1EU)         /* Timer is stopped */
#define BSW_BSWM_VPS_u2TIME_STOP              ((BswU2)0U)            /* Init Timer */
#define BSW_BSWM_VPS_u2TIME_TRG_OFFSET        ((BswU2)1U)            /* Timer offset 1Cycle */

/* Data Byte Pos */
#define BSW_BSWM_VPS_u1POS_DAT0               ((BswU1)0U)
#define BSW_BSWM_VPS_u1POS_DAT1               ((BswU1)1U)
#define BSW_BSWM_VPS_u1POS_DAT2               ((BswU1)2U)
#define BSW_BSWM_VPS_u1POS_DAT3               ((BswU1)3U)
#define BSW_BSWM_VPS_u1POS_DAT4               ((BswU1)4U)
#define BSW_BSWM_VPS_u1POS_DAT5               ((BswU1)5U)
#define BSW_BSWM_VPS_u1POS_DAT6               ((BswU1)6U)
#define BSW_BSWM_VPS_u1POS_DAT7               ((BswU1)7U)

/* Bit Control */
#define BSW_BSWM_VPS_u4ALLBITMSK              ((BswU4)0xFFFFFFFFUL)  /* System State All Bit Mask */
#define BSW_BSWM_VPS_u4ALLBITNONE             ((BswU4)0x00000000UL)  /* System State All Bit Zero */
#define BSW_BSWM_VPS_u4ALLBITON               ((BswU4)0xFFFFFFFFUL)  /* System State All Bit On */
#define BSW_BSWM_VPS_u1VERIFY_KEY_B8          ((BswU1)0xFFU)         /* Ram Check Key */
#define BSW_BSWM_VPS_u4VERIFY_KEY_B32         ((BswU4)0xFFFFFFFFUL)  /* Ram Check Key */

/* E2E RxCheck Return Value */
#define BSW_BSWM_VPS_u1_E2E_CHK_OK            ((BswU1)0x0FU)
#define BSW_BSWM_VPS_u1_E2E_CHK_FAIL          ((BswU1)0x1EU)
#define BSW_BSWM_VPS_u1_E2E_CHK_CNTERR        ((BswU1)0x2DU)

#define BSW_BSWM_VPS_u1RXSTATUS_NONE          ((BswU1)0x0FU)         /* Rx status : No recieve */
#define BSW_BSWM_VPS_u1RXSTATUS_EXIST         ((BswU1)0x1EU)         /* Rx status : received   */

#define BSW_BSWM_VPS_u1RXVPSST_FRST_NONE      ((BswU1)0x0FU)         /* Rx status : First No recieve */
#define BSW_BSWM_VPS_u1RXVPSST_NONE           ((BswU1)0x1EU)         /* Rx status : No recieve */
#define BSW_BSWM_VPS_u1RXVPSST_EXIST          ((BswU1)0x2DU)         /* Rx status : received   */

/* Receive SystemStatus Change Event */
#define BSW_BSWM_VPS_u1RXSYSSTCHNG_NONE       ((BswU1)0x0FU)         /* No rx status change event */
#define BSW_BSWM_VPS_u1RXSYSSTCHNG_EXIST      ((BswU1)0x1EU)         /* Rx status change event exist */

/* SetSystemStatus Request */
#define BSW_BSWM_VPS_u1SETSYSSTATREQ_NONE     ((BswU1)0x0FU)         /* No setting system status request */
#define BSW_BSWM_VPS_u1SETSYSSTATREQ_EXIST    ((BswU1)0x1EU)         /* Setting system status request exist */

/* SetSystemStatus Event */
#define BSW_BSWM_VPS_u1SETSYSSTEVNT_NONE      ((BswU1)0x0FU)         /* No setting system status event */
#define BSW_BSWM_VPS_u1SETSYSSTEVNT_EXIST     ((BswU1)0x1EU)         /* Setting system status event exist */
#define BSW_BSWM_VPS_u1SETSYSSTEVNT_RETRY     ((BswU1)0x2DU)         /* Retry to transmit setting system status event */

/* RxVPSFix Allowed Status */
#define BSW_BSWM_VPS_u1RXVPSFIX_OK            ((BswU1)0x0FU)         /* RxVPSFix Allowed */
#define BSW_BSWM_VPS_u1RXVPSFIX_NG            ((BswU1)0x1EU)         /* RxVPSFix Prohibited */

/* Rx Event */
#define BSW_BSWM_VPS_u1RXEVNT_NONE            ((BswU1)0x0FU)         /* Rx No event    */
#define BSW_BSWM_VPS_u1RXEVNT_EXIST           ((BswU1)0x1EU)         /* Receivi event  */
#define BSW_BSWM_VPS_u1RXEVNT_WAITRES         ((BswU1)0x2DU)         /* Wait Responce  */

/* Tx VPS Message State */
#define BSW_BSWM_VPS_u1TXMSGST_NONE           ((BswU1)0x0FU)         /* Tx status : No transmission */
#define BSW_BSWM_VPS_u1TXMSGST_PEND           ((BswU1)0x1EU)         /* Tx status : Pending transmission request */
#define BSW_BSWM_VPS_u1TXMSGST_REQCNFWT       ((BswU1)0x2DU)         /* Tx status : Waiting transmission request confirmation */
#define BSW_BSWM_VPS_u1TXMSGST_TXCNFWT        ((BswU1)0x3CU)         /* Tx status : Waiting transmission confirmation */
#define BSW_BSWM_VPS_u1TXMSGST_DONE           ((BswU1)0x4BU)         /* Tx status : Transmission Confirmation */

/* Tx Message Mask */
#define BSW_BSWM_VPS_u1SNDMSK_OFF             ((BswU1)0x00U)         /* Write Tx Message Mask : Off */
#define BSW_BSWM_VPS_u1SNDMSK_ON              ((BswU1)0xFFU)         /* Write Tx Message Mask : On */
#define BSW_BSWM_VPS_u1SNDBITMSK_ON           ((BswU1)0x03U)         /* Write Tx RlyMessage Bit Mask : On */

/* Set wakeup factor */
#define BSW_BSWM_VPS_u1SETWKFC_OFF            ((BswU1)0x0FU)         /* Request communication : OFF */
#define BSW_BSWM_VPS_u1SETWKFC_ON             ((BswU1)0x1EU)         /* Request communication : ON */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    BswU1           u1InfoSp;
    BswU1           u1InfoSpOpt;
}Bsw_BswM_VPS_InfoSpType;

typedef struct {
    BswU4           u4CoPncLo;
    BswU4           u4CoPncUp;
    BswU1           u1Channel;
    BswU1           u1Extend0;
    BswU1           u1Extend1;
    BswU1           u1Extend2;
}Bsw_BswM_VPS_CoPncAwakeType;

typedef struct {
    BswU4           u4ChPncLo;
    BswU4           u4ChPncUp;
    BswU1           u1Channel;
    BswU1           u1Extend0;
    BswU1           u1Extend1;
    BswU1           u1Extend2;
}Bsw_BswM_VPS_ChPncAwakeType;

typedef struct {
    BswU2           u2RxPduId;
    BswU1           u1NetworkHandle;
    BswU1           u1RxMsgKind;
    BswU2           u2TxPduId;
} Bsw_BswM_VPS_RxMsgType;

typedef struct {
    BswU2           u2TxPduId;
    BswU1           u1NetworkHandle;
    BswU1           u1MsgKind;
} Bsw_BswM_VPS_TxMsgType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*********************/
/* Ctrl              */
/*********************/
void       bsw_bswm_vps_ctrl_InitTxData( void );
void       bsw_bswm_vps_ctrl_SetSysStatIn( BswConstR uint32* Mask, BswConstR uint32* SysStatus );
void       bsw_bswm_vps_ctrl_FixSysSt( void );
void       bsw_bswm_vps_ctrl_SetFixedSt( void );
void       bsw_bswm_vps_ctrl_CkRxVPSTO( void );
void       bsw_bswm_vps_ctrl_TxVPSMsg( void );
void       bsw_bswm_vps_ctrl_PrRxVpsMsg( uint8 u1RxEvntIdx, BswConstR uint8 *SduDataPtr );
boolean    bsw_bswm_vps_ctrl_RxVPSMsg( uint8 u1RxEvntIdx, BswConstR uint8 *SduDataPtr );
void       bsw_bswm_vps_ctrl_RxRlyMsg( uint8 u1RxEvntIdx, BswConstR uint8 *SduDataPtr, uint8 u1RxEvent );
void       bsw_bswm_vps_ctrl_UpdROCRxTimer( void );
void       bsw_bswm_vps_ctrl_StopROCRxTimer( BswU1 u1RxTrSt );
void       bsw_bswm_vps_ctrl_TxIpduCoIn( PduIdType PduId, PduInfoType* PduInfoPtr );
/*********************/
/* Ctrl (Dummy)      */
/*********************/
void       bsw_bswm_vps_ctrl_InitNone( void );
void       bsw_bswm_vps_ctrl_DeInitNone( void );
void       bsw_bswm_vps_ctrl_WakeupNone( void );
void       bsw_bswm_vps_ctrl_MainFunctionNone( void );
void       bsw_bswm_vps_ctrl_GetSysStatNone( uint32* SysStatus );
void       bsw_bswm_vps_ctrl_SetSysStatNone( BswConstR uint32* Mask, BswConstR uint32* SysStatus );
void       bsw_bswm_vps_ctrl_FixSysStNone( void );
void       bsw_bswm_vps_ctrl_SetFixedStNone( void );
void       bsw_bswm_vps_ctrl_CkRxVPSTONone( void );
void       bsw_bswm_vps_ctrl_TxVPSMsgNone( void );
void       bsw_bswm_vps_ctrl_PrRxVpsMsgNo( uint8 u1RxEvntIdx, BswConstR uint8 *SduDataPtr );
boolean    bsw_bswm_vps_ctrl_RxVPSMsgNone( uint8 u1RxEvntIdx, BswConstR uint8 *SduDataPtr );
void       bsw_bswm_vps_ctrl_RxRlyMsgNone( uint8 u1RxEvntIdx, BswConstR uint8 *SduDataPtr, uint8 u1RxEvent );
void       bsw_bswm_vps_ctrl_UpdROCRxTimNn( void );
void       bsw_bswm_vps_ctrl_StopROCRxTimNn( BswU1 u1RxTrSt );
void       bsw_bswm_vps_ctrl_TxIpduCoNone( PduIdType PduId, PduInfoType* PduInfoPtr );

/*********************/
/* RlyOnConf         */
/*********************/
void    bsw_bswm_vps_ctrl_TxRlyConfReq( void );
void    bsw_bswm_vps_ctrl_UpdtROCTimer( void );
void    bsw_bswm_vps_ctrl_StHdlSysChg( void );

/*********************/
/* RlyOnConf (Dummy) */
/*********************/
void    bsw_bswm_vps_ctrl_TxRlyConfReqNone( void );
void    bsw_bswm_vps_ctrl_UpdtROCTimerNone( void );
void    bsw_bswm_vps_ctrl_StHdlSysChgNo( void );

/*********************/
/* E2E               */
/*********************/
void    bsw_bswm_vps_ctrl_E2EInit( void );
void    bsw_bswm_vps_ctrl_E2ETxProtect(uint8 u1TxIdx, uint8* DataPtr);
boolean bsw_bswm_vps_ctrl_E2ERxCheck( uint8 u1RxIdx, BswConstR uint8* DataPtr );
/*********************/
/* E2E (Dummy)       */
/*********************/
void    bsw_bswm_vps_ctrl_E2EInitNone( void );
void    bsw_bswm_vps_ctrl_E2ETxProtectNone(uint8 u1TxIdx, uint8* DataPtr);
boolean bsw_bswm_vps_ctrl_E2ERxCheckNone( uint8 u1RxIdx, BswConstR uint8* DataPtr );

/***************************/
/* PNC                     */
/***************************/
void    bsw_bswm_vps_ctrl_RqChPncCM( void );
void    bsw_bswm_vps_ctrl_SetCoPncAwk( BswConst Bsw_BswM_VPS_CoPncAwakeType* ptCfgCoPncData, uint8 u1CfgCoPncChNum );

/***************************/
/* PNC (Dummy)             */
/***************************/
void    bsw_bswm_vps_ctrl_RqChPncCMNo( void );
void    bsw_bswm_vps_ctrl_SetCoPncAwkNo( BswConst Bsw_BswM_VPS_CoPncAwakeType* ptCfgCoPncData, uint8 u1CfgCoPncChNum );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern BswU1                bsw_bswm_vps_u1RxEvent[];
extern BswU1                bsw_bswm_vps_u1RxStatus[];
extern BswU1                bsw_bswm_vps_u1TxVPSMsgSt[];
extern BswU1                bsw_bswm_vps_u1TmpMsgData[];
extern BswU1                bsw_bswm_vps_u1SndDataMsk[];

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* Vehicle Power State */
extern BswConst BswU4       bsw_bswm_vps_u4SysStVPS[][BSW_BSWM_VPS_SYSSTATTBLNUM];
extern BswConst BswU1       bsw_bswm_vps_u1Info[];
extern BswConst BswU4       bsw_bswm_vps_u4SysStVPSSp[][BSW_BSWM_VPS_SYSSTATTBLNUM];
extern BswConst Bsw_BswM_VPS_InfoSpType bsw_bswm_vps_stInfoSpTbl[];
extern BswConst Bsw_BswM_VPS_InfoSpType bsw_bswm_vps_stInfoSpOff;

extern BswConst BswU1       bsw_bswm_vps_u1VehiPwStNum;
extern BswConst BswU1       bsw_bswm_vps_u1VehiPwStSpNum;

extern BswConst BswU4       bsw_bswm_vps_u4PwOnConst[];
extern BswConst BswU4       bsw_bswm_vps_u4ActiveVPS[];
extern BswConst BswU4       bsw_bswm_vps_u4ActiveVPSSp[];

/* Message */
extern BswConst Bsw_BswM_VPS_RxMsgType bsw_bswm_vps_stRxMsgTbl[];
extern BswConst Bsw_BswM_VPS_TxMsgType bsw_bswm_vps_stTxMsgTbl[];

extern BswConst BswU1       bsw_bswm_vps_u1DataDivLocUse;
extern BswConst BswU2       bsw_bswm_vps_u2MaxMsgSize;
extern BswConst BswU1       bsw_bswm_vps_u1PwStPos;
extern BswConst BswU1       bsw_bswm_vps_u1PwStActiveBit;
extern BswConst BswU1       bsw_bswm_vps_u1PwStSpPos;
extern BswConst BswU1       bsw_bswm_vps_u1PwStSpTransPos;
extern BswConst BswU1       bsw_bswm_vps_u1PwStSpOtaPos;
extern BswConst BswU1       bsw_bswm_vps_u1RlyOnConfBytePos;
extern BswConst BswU1       bsw_bswm_vps_u1RlyOnConfBitPos;

extern BswConst BswU1       bsw_bswm_vps_u1PwStSpTransOnBit;
extern BswConst BswU1       bsw_bswm_vps_u1PwStSpTransOffBit;

extern BswConst BswU1       bsw_bswm_vps_u1VhPwStRxPduIdNum;
extern BswConst BswU1       bsw_bswm_vps_u1VhPwStTxPduIdNum;
extern BswConst BswU1       bsw_bswm_vps_u1RlyOnConfReqTxPduIdNum;
extern BswConst BswU1       bsw_bswm_vps_u1RxPduIdNum;

extern BswConst BswU1       bsw_bswm_vps_u1E2ERxCntError;

extern BswConst BswU2       bsw_bswm_vps_u2VpsRxTOTim;
extern BswConst BswU2       bsw_bswm_vps_u2VpsFirstRxTOTim;
extern BswConst BswU4       bsw_bswm_vps_u4VPSToFsVal[];

extern BswConst BswU1       bsw_bswm_vps_u1GlobalBus0;
extern BswConst BswU1       bsw_bswm_vps_u1GlobalBus1;

/* Wakeup Factor */
extern BswConst BswU1       bsw_bswm_vps_u1PncChNum;
extern BswConst BswU1       bsw_bswm_vps_u1PncChNumTbl[];
extern BswConst BswU1       bsw_bswm_vps_u1AwkFctNum;
extern BswConst BswU1       bsw_bswm_vps_u1ConPncAwkHdskNum;
extern BswConst BswU1       bsw_bswm_vps_u1ChPncChNumTbl[];
extern BswConst BswU1       bsw_bswm_vps_u1CoBusChNumTbl[];
extern BswConst BswU1       bsw_bswm_vps_u1CoPncChNumTbl[];
extern BswConst BswU1       bsw_bswm_vps_u1UserHandleTbl[];
extern BswConst Bsw_BswM_VPS_ChPncAwakeType* BswConst bsw_bswm_vps_ptChPncAwake[];
extern BswConst BswU1*      BswConst bsw_bswm_vps_ptCoBusAwake[];
extern BswConst Bsw_BswM_VPS_CoPncAwakeType* BswConst bsw_bswm_vps_ptCoPncAwake[];
extern BswConst Bsw_BswM_VPS_CoPncAwakeType bsw_bswm_vps_stCoPncAwake_HandShake[];

extern BswConst BswU2       bsw_bswm_vps_u2WfChgVPS;
extern BswConst BswU2       bsw_bswm_vps_u2WfReset;
extern BswConst BswU2       bsw_bswm_vps_u2WfRxPnc;

extern BswConst BswU2       bsw_bswm_vps_u2WfChgVPSTim;
extern BswConst BswU2       bsw_bswm_vps_u2WfResetTim;
extern BswConst BswU2       bsw_bswm_vps_u2WfRxPncTim;

extern BswConst BswU4       bsw_bswm_vps_u4WfPncLo;
extern BswConst BswU4       bsw_bswm_vps_u4WfPncUp;

/* Handshake */
extern BswConst BswU2       bsw_bswm_vps_u2RlyOnConfTOTim;

/* Function Table */
/* E2E Function Table */
extern void    (* BswConst bsw_bswm_vps_ctrl_ptE2EInitFn)( void );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptE2ETxProtectFn)( uint8 u1TxIdx, uint8* DataPtr );
extern boolean (* BswConst bsw_bswm_vps_ctrl_ptE2ERxCheckFn)( uint8 u1TxIdx, BswConstR uint8* DataPtr );

/* PNC Function Table */
extern void    (* BswConst bsw_bswm_vps_ctrl_ptRqChPncCMFn)( void );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptSetCoPncAwkFn)( BswConst Bsw_BswM_VPS_CoPncAwakeType* ptCfgCoPncData, uint8 u1CfgCoPncChNum );

/* CS Function Table */
extern void       (* BswConst bsw_bswm_vps_ctrl_ptInitFn)( void );
extern void       (* BswConst bsw_bswm_vps_ctrl_ptDeInitFn)( void );
extern void       (* BswConst bsw_bswm_vps_ctrl_ptWakeupFn)( void );
extern void       (* BswConst bsw_bswm_vps_ctrl_ptMainFunctionFn)( void );
extern void       (* BswConst bsw_bswm_vps_ctrl_ptGetSystemStatusFn)( uint32* SysStatus );
extern void       (* BswConst bsw_bswm_vps_ctrl_ptSetSystemStatusFn)( BswConstR uint32* Mask, BswConstR uint32* SysStatus );
extern void       (* BswConst bsw_bswm_vps_ctrl_ptFixSysStFn)( void );
extern void       (* BswConst bsw_bswm_vps_ctrl_ptSetFixedStFn)( void );
extern void       (* BswConst bsw_bswm_vps_ctrl_ptCkRxVPSTOFn)( void );
extern void       (* BswConst bsw_bswm_vps_ctrl_ptTxVpsMsgFn)( void );
extern boolean    (* BswConst bsw_bswm_vps_ctrl_ptRxIndVpsMsgFn)( uint8 u1RxEvntIdx, BswConstR uint8 *SduDataPtr );
extern void       (* BswConst bsw_bswm_vps_ctrl_ptPrRxVpsMsgFn)( uint8 u1RxEvntIdx, BswConstR uint8 *SduDataPtr );
extern void       (* BswConst bsw_bswm_vps_ctrl_ptRxRlyMsgFn)( uint8 u1RxEvntIdx, BswConstR uint8 *SduDataPtr, uint8 u1RxEvent );
extern void       (* BswConst bsw_bswm_vps_ctrl_ptUpdROCRxTimFn)( void );
extern void       (* BswConst bsw_bswm_vps_ctrl_ptStopROCRxTimFn)( BswU1 u1RxTrSt );
extern void       (* BswConst bsw_bswm_vps_ctrl_ptTxIpduCoFn)( PduIdType PduId, PduInfoType* PduInfoPtr );

/* RlyOnConf Function Table */
extern void       (* BswConst bsw_bswm_vps_ctrl_ptStHdlSysChgFn)( void );
extern void       (* BswConst bsw_bswm_vps_ctrl_ptTxRlyOnConfReqFn)( void );
extern void       (* BswConst bsw_bswm_vps_ctrl_ptUpdtROCTimFn)( void );
#endif  /* BSW_BSWM_VPS_CTRL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v3-0-0          :2025/04/10                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
