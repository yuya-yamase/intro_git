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
#define BSW_BSWM_VPS_DATA_LENGTH              (8U)                       /* data length */
#define BSW_BSWM_VPS_CHANNEL_INVALID          (0xFFU)
#define BSW_BSWM_VPS_u1ALLBITNONE             ((BswU1)0x00U)

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

/* RxVPSFix Allowed Status */
#define BSW_BSWM_VPS_u1RXVPSFIX_OK            ((BswU1)0x0FU)         /* RxVPSFix Allowed */
#define BSW_BSWM_VPS_u1RXVPSFIX_NG            ((BswU1)0x1EU)         /* RxVPSFix Prohibited */

/* Rx Event */
#define BSW_BSWM_VPS_u1RXEVNT_NONE            ((BswU1)0x0FU)         /* Rx No event    */
#define BSW_BSWM_VPS_u1RXEVNT_EXIST           ((BswU1)0x1EU)         /* Receivi event  */
#define BSW_BSWM_VPS_u1RXEVNT_WAITRES         ((BswU1)0x2DU)         /* Wait Responce  */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    BswU1           u1RxPncEvnt0;
    BswU1           u1RxPncEvnt1;
} Bsw_BswM_VPS_RxPncEvntType;

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
    BswU1           u1MsgKind;
    BswU1           u1Extend;
} Bsw_BswM_VPS_TxMsgType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/*********************/
/* Ctrl              */
/*********************/
void    bsw_bswm_vps_ctrl_InitTxData( uint8 *SduDataPtr );
void    bsw_bswm_vps_ctrl_SetSysStatIn( uint32* Mask, uint32* SysStatus );
void    bsw_bswm_vps_ctrl_FixSysSt( void );
void    bsw_bswm_vps_ctrl_SetFixedSt( void );
void    bsw_bswm_vps_ctrl_CkRxVPSTO( void );
void    bsw_bswm_vps_ctrl_TxVPSMsg( void );
void    bsw_bswm_vps_ctrl_RxVPSMsg( uint8 u1RxEvntIdx, uint8 *SduDataPtr );
void    bsw_bswm_vps_ctrl_RxRlyMsg( uint8 u1RxEvntIdx, uint8 *SduDataPtr, uint8 u1RxEvent );
void    bsw_bswm_vps_ctrl_TxIpduCoIn( PduIdType PduId, PduInfoType* PduInfoPtr );
/*********************/
/* Ctrl (Dummy)      */
/*********************/
void    bsw_bswm_vps_ctrl_InitNone( void );
void    bsw_bswm_vps_ctrl_DeInitNone( void );
void    bsw_bswm_vps_ctrl_WakeupNone( void );
void    bsw_bswm_vps_ctrl_MainFunctionNone( void );
void    bsw_bswm_vps_ctrl_GetSysStatNone( uint32* SysStatus );
void    bsw_bswm_vps_ctrl_SetSysStatNone( uint32* Mask, uint32* SysStatus );
void    bsw_bswm_vps_ctrl_FixSysStNone( void );
void    bsw_bswm_vps_ctrl_SetFixedStNone( void );
void    bsw_bswm_vps_ctrl_CkRxVPSTONone( void );
void    bsw_bswm_vps_ctrl_TxVPSMsgNone( void );
void    bsw_bswm_vps_ctrl_RxVPSMsgNone( uint8 u1RxEvntIdx, uint8 *SduDataPtr );
void    bsw_bswm_vps_ctrl_RxRlyMsgNone( uint8 u1RxEvntIdx, uint8 *SduDataPtr, uint8 u1RxEvent );
void    bsw_bswm_vps_ctrl_TxIpduCoNone( PduIdType PduId, PduInfoType* PduInfoPtr );

/*********************/
/* RlyOnConf         */
/*********************/
void    bsw_bswm_vps_ctrl_TxRlyConfReq( void );
void    bsw_bswm_vps_ctrl_UpdtROCTimer( void );
/*********************/
/* RlyOnConf (Dummy) */
/*********************/
void    bsw_bswm_vps_ctrl_TxRlyConfReqNone( void );
void    bsw_bswm_vps_ctrl_UpdtROCTimerNone( void );
void    bsw_bswm_vps_ctrl_StopStatHdlNone( void );

/*********************/
/* E2E               */
/*********************/
void    bsw_bswm_vps_ctrl_E2EInit( void );
void    bsw_bswm_vps_ctrl_E2ETxProtect (uint8 u1TxIdx, uint8* DataPtr);
boolean bsw_bswm_vps_ctrl_E2ERxCheck (uint8 u1RxIdx, uint8* DataPtr);
/*********************/
/* E2E (Dummy)       */
/*********************/
void    bsw_bswm_vps_ctrl_E2EInitNone( void );
void    bsw_bswm_vps_ctrl_E2ETxProtectNone (uint8 u1TxIdx, uint8* DataPtr);
boolean bsw_bswm_vps_ctrl_E2ERxCheckNone (uint8 u1RxIdx, uint8* DataPtr);

/***************************/
/* Other Component (Dummy) */
/***************************/
Std_ReturnType    bsw_bswm_vps_ctrl_RequestChPncComModeNone( NetworkHandleType Channel, Bsw_ComM_UserHandleType User, Bsw_ComM_ModeType ComMode );
Std_ReturnType    bsw_bswm_vps_ctrl_SetCoPncAwakeNone( NetworkHandleType Channel, uint32 PncAwakeLo, uint32 PncAwakeUp );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern Bsw_BswM_VPS_RxPncEvntType bsw_bswm_vps_ctrl_stRxPncEvnt;
extern BswU1                bsw_bswm_vps_u1RxEvent[];
extern BswU1                bsw_bswm_vps_u1RxStatus[];

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* Vehicle Power State */
extern BswConst BswU4       bsw_bswm_vps_u4SysStVPS[][BSW_BSWM_VPS_SYSSTATTBLNUM];
extern BswConst BswU1       bsw_bswm_vps_u1Info[];
extern BswConst BswU4       bsw_bswm_vps_u4SysStVPSSp[][BSW_BSWM_VPS_SYSSTATTBLNUM];
extern BswConst Bsw_BswM_VPS_InfoSpType bsw_bswm_vps_stInfoSpTbl[];

extern BswConst BswU1       bsw_bswm_vps_u1VehiPwStNum;
extern BswConst BswU1       bsw_bswm_vps_u1VehiPwStSpNum;

extern BswConst BswU4       bsw_bswm_vps_u4PwOnConst[];
extern BswConst BswU4       bsw_bswm_vps_u4ActiveVPS[];
extern BswConst BswU4       bsw_bswm_vps_u4ActiveVPSSp[];

extern BswConst BswU1       bsw_bswm_vps_u1RxVPSFix;

/* Message */
extern BswConst Bsw_BswM_VPS_RxMsgType bsw_bswm_vps_stRxMsgTbl[];
extern BswConst Bsw_BswM_VPS_TxMsgType bsw_bswm_vps_stTxMsgTbl[];

extern BswConst BswU1       bsw_bswm_vps_u1PwStPos;
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
extern BswConst BswU1       bsw_bswm_vps_u1TxPduIdNum;
extern BswConst BswU1       bsw_bswm_vps_u1RxPduIdNum;

extern BswConst BswU1       bsw_bswm_vps_u1VpsMsgE2EUse;
extern BswConst BswU1       bsw_bswm_vps_u1E2ERxCntError;

extern BswConst BswU2       bsw_bswm_vps_u2VpsRxTOTim;
extern BswConst BswU2       bsw_bswm_vps_u2VpsFirstRxTOTim;
extern BswConst BswU4       bsw_bswm_vps_u4VPSToFsVal[];

extern BswConst BswU1       bsw_bswm_vps_u1GlobalBus0;
extern BswConst BswU1       bsw_bswm_vps_u1GlobalBus1;

/* Wakeup Factor */
extern BswConst BswU1       bsw_bswm_vps_u1AwkFctNum;
extern BswConst BswU1       bsw_bswm_vps_u1ConPncAwkHdskNum;
extern BswConst BswU1       bsw_bswm_vps_u1ChPncChNumTbl[];
extern BswConst BswU1       bsw_bswm_vps_u1CoBusChNumTbl[];
extern BswConst BswU1       bsw_bswm_vps_u1CoPncChNumTbl[];
extern BswConst BswU1       bsw_bswm_vps_u1UserHandleTbl[];
extern BswConst Bsw_BswM_VPS_ChPncAwakeType* bsw_bswm_vps_ptChPncAwake[];
extern BswConst BswU1*      bsw_bswm_vps_ptCoBusAwake[];
extern BswConst Bsw_BswM_VPS_CoPncAwakeType* bsw_bswm_vps_ptCoPncAwake[];
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
extern BswConst BswU1       bsw_bswm_vps_u1HandShake;

/* Function Table */
/* E2E Function Table */
extern void    (* BswConst bsw_bswm_vps_ctrl_ptE2EInitFn)( void );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptE2ETxProtectFn)( uint8 u1TxIdx, uint8* DataPtr );
extern boolean (* BswConst bsw_bswm_vps_ctrl_ptE2ERxCheckFn)( uint8 u1TxIdx, uint8* DataPtr );

/* PNC Function Table */
extern Std_ReturnType    (* BswConst bsw_bswm_vps_ctrl_ptReqChPNCComModeFn)( NetworkHandleType Channel, Bsw_ComM_UserHandleType User, Bsw_ComM_ModeType ComMode );
extern Std_ReturnType    (* BswConst bsw_bswm_vps_ctrl_ptSetCoPncAwakeFn)( NetworkHandleType Channel, uint32 PncAwakeLo, uint32 PncAwakeUp );

/* CS Function Table */
extern void    (* BswConst bsw_bswm_vps_ctrl_ptInitFn)( void );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptDeInitFn)( void );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptWakeupFn)( void );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptMainFunctionFn)( void );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptGetSystemStatusFn)( uint32* SysStatus );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptSetSystemStatusFn)( uint32* Mask, uint32* SysStatus );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptFixSysStFn)( void );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptSetFixedStFn)( void );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptCkRxVPSTOFn)( void );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptTxVpsMsgFn)( void );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptRxVpsMsgFn)( uint8 u1RxEvntIdx, uint8 *SduDataPtr );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptRxRlyMsgFn)( uint8 u1RxEvntIdx, uint8 *SduDataPtr, uint8 u1RxEvent );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptTxIpduCoFn)( PduIdType PduId, PduInfoType* PduInfoPtr );

/* RlyOnConf Function Table */
extern void    (* BswConst bsw_bswm_vps_ctrl_ptStopStatHdlFn)( void );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptTxRlyOnConfReqFn)( void );
extern void    (* BswConst bsw_bswm_vps_ctrl_ptUpdtROCTimFn)( void );
#endif  /* BSW_BSWM_VPS_CTRL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v3-0-0          :2024/11/14                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
