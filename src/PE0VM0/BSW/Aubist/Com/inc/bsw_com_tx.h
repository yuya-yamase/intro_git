/* bsw_com_tx_h_v2-2-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/COM/TX/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_COM_TX_H
#define BSW_COM_TX_H


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_COM_u1RETRIGGER_OFF         ((BswU1)0x00U)
#define BSW_COM_u1RETRIGGER_ON          ((BswU1)0x01U)

/* bsw_com_tx_AddBit,GetBit related */
#define BSW_COM_QUEKIND_EVENT           (0U)                    /* Specify event transmission queue      */
#define BSW_COM_QUEKIND_PERIOD          (1U)                    /* Specify the periodic transmit queue          */

#define BSW_COM_BITIND_BYTEPOS_SHIFT    (3U)
#define BSW_COM_BITIND_ROUNDUP_VALUE    (7U)
#define BSW_COM_BITIND_u1OFFSET_MASK    ((BswU1)0x07U)
#define BSW_COM_BITIND_u1NONE           ((BswU1)0U)

#define BSW_COM_TX_REQ_IDLE             (0x01U)                 /* Idle (no transmission request)    */
#define BSW_COM_TX_REQ_EVT              (0x02U)                 /* During event transmission              */
#define BSW_COM_TX_REQ_PRD              (0x03U)                 /* Periodic transmitting                  */

/* Message information mask */
#define BSW_COM_EVENTDELAY_MASK         (0x01U)
#define BSW_COM_EVTAWAKE_MASK           (0x02U)
#define BSW_COM_PREPRDTXRTRG_MASK       (0x04U)
#define BSW_COM_SENDNTIMES_MASK         (0x08U)
#define BSW_COM_CHGPRDIPDU_MASK         (0x10U)
#define BSW_COM_EVTWAKEUPTX_MASK        (0x20U)
#define BSW_COM_TXREQCONF_MASK          (0x01U)
#define BSW_COM_TXCONF_MASK             (0x02U)
#define BSW_COM_PRETX_MASK              (0x20U)

#define BSW_COM_TX_CHGPRD_ON            (0x01U)                 /* During period switching                       */
#define BSW_COM_TX_CHGPRD_OFF           (0x02U)                 /* Not in period switching                 */

#define BSW_COM_u1TX_ENABLE             ((BswU1)0x01U)
#define BSW_COM_u1TX_DISABLE            ((BswU1)0x02U)

#define BSW_COM_u1PNCIPDU_TX_DISABLE    ((BswU1)0x0FU)
#define BSW_COM_u1PNCIPDU_TX_ENABLE     ((BswU1)0x1EU)

#define BSW_COM_u1PNCIPDU_SET_ON        ((BswU1)0x0FU)
#define BSW_COM_u1PNCIPDU_SET_OFF       ((BswU1)0x1EU)
#define BSW_COM_u1PNCIPDU_MEASURE       ((BswU1)0x2DU)

#define BSW_COM_u1TXIPDU_NONE           ((BswU1)0U)             /* No process                                           */
#define BSW_COM_u1TXIPDU_START          ((BswU1)1U)             /* Start I-PDU                                          */
#define BSW_COM_u1TXIPDU_STOP           ((BswU1)2U)             /* Stop I-PDU                                           */

#define BSW_COM_u1TXIPDU_BIT_NONE       ((BswU1)0x00U)          /* No process                                           */
#define BSW_COM_u1TXIPDU_BIT_SETSENDTM  ((BswU1)0x01U)          /* Set SENDSTART                                        */
#define BSW_COM_u1TXIPDU_BIT_CLRDELAYTM ((BswU1)0x02U)          /* Clear the tx delay timer                             */
#define BSW_COM_u1TXIPDU_BIT_SETTXTM    ((BswU1)0x04U)          /* Set the periodic tx timer                            */
#define BSW_COM_u1TXIPDU_BIT_SETTXTMCHK ((BswU1)0x08U)          /* Set the periodic tx timer   (With FST_DELAY check)   */
#define BSW_COM_u1TXIPDU_BIT_CLRTXTM    ((BswU1)0x10U)          /* Clear the periodic tx timer                          */
#define BSW_COM_u1TXIPDU_BIT_CLRTXTMCHK ((BswU1)0x20U)          /* Clear the periodic tx timer (With FST_DELAY check)   */

#define BSW_COM_u1FIRSTTX_OFF           ((BswU1)0x0FU)
#define BSW_COM_u1FIRSTTX_ON            ((BswU1)0x1EU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef BswU1               Bsw_Com_TxQueType;

typedef struct {
    PduIdType              u2PduId;
    BswU2                  u2IntervalTime;
    BswU1                  u1SndTimes;
    BswU1                  u1Extend;
} Bsw_Com_NTimesInfoType;

typedef struct {
    PduIdType              u2PduId;
    BswU2                  u2PeriodTime;
    BswU1                  u1AfterSnd;
    BswU1                  u1SndOffImm;
    BswU1                  u1TimerRetrigger;
    BswU1                  u1Extend;
} Bsw_Com_ChgPrdInfoType;

typedef struct {
    BswU1                  u1EnableStatus;
    BswU1                  u1SetPeriOffset;
} Bsw_Com_PncIpduTxInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void                  bsw_com_tx_InitPeriSendSub( Bsw_Com_NetworkType u1Network );
Bsw_Com_RetStatusType bsw_com_tx_SendReq( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
void                  bsw_com_tx_InitAllTxReqSt( void );
void                  bsw_com_tx_InitAllTxReqStNone( void );
void                  bsw_com_tx_InitSendNTimes( void );
void                  bsw_com_tx_InitSndNTimesNone( void );
void                  bsw_com_tx_InitPrdStat( void );
void                  bsw_com_tx_InitDelayTime( void );
void                  bsw_com_tx_InitComTxStat( Bsw_Com_IpduGroupVector ipduGroupVector );
void                  bsw_com_tx_ShutdownComTxStat( void );
BswU1                 bsw_com_tx_GetPncIpduTxSt( NetworkHandleType Network, PduIdType u2PduId );
BswU1                 bsw_com_tx_GetPncIpduTxStNone( NetworkHandleType Network, PduIdType u2PduId );

/* Unit internal public definition */
BswU2                 bsw_com_tx_NotifyPeriTxRtrgr( Bsw_Com_NetworkType u1Network, PduIdType u2PduId, BswU2 u2Time);
void                  bsw_com_tx_InitBit( void );
Bsw_Com_RetStatusType bsw_com_tx_AddBit( Bsw_Com_NetworkType u1Network, PduIdType u2PduId, Bsw_Com_TxQueType u1QueType );
void                  bsw_com_tx_DelBit( Bsw_Com_NetworkType u1Network, PduIdType u2PduId );
void                  bsw_com_tx_InitTxReqStat( PduIdType u2PduId );
void                  bsw_com_tx_SetTxReqStat( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
BswU1                 bsw_com_tx_GetTxReqStat( PduIdType u2PduId );
void                  bsw_com_tx_TransmitCfm( PduIdType u2PduId );
BswU2                 bsw_com_tx_TxTimeout( PduIdType u2PduId );
void                  bsw_com_tx_InitTxReqStatNone( PduIdType u2PduId );
void                  bsw_com_tx_SetTxReqStatNone( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
BswU1                 bsw_com_tx_GetTxReqStatNone( PduIdType u2PduId );
void                  bsw_com_tx_TransmitCfmNone( PduIdType u2PduId );
BswU2                 bsw_com_tx_TxTimeoutNone( PduIdType u2PduId );
void                  bsw_com_tx_ChgPrdIpduCnt( void );
void                  bsw_com_tx_SendNTimesCnt( void );
Bsw_Com_RetStatusType bsw_com_tx_ChgPeriToNTimes( PduIdType u2PduId, Bsw_Com_RetStatusType s1QueExist );
void                  bsw_com_tx_SendNTimesMsg( PduIdType u2PduId );
void                  bsw_com_tx_SetTxReqNTimTimer( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
void                  bsw_com_tx_SetTxFinNTimTimer( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
void                  bsw_com_tx_ClearSendNTimesCh( Bsw_Com_NetworkType u1Network );
void                  bsw_com_tx_ClearSendNTimesMsg( PduIdType u2PduId );
void                  bsw_com_tx_ChgPrdIpduCntNone( void );
void                  bsw_com_tx_SendNTimesCntNone( void );
Bsw_Com_RetStatusType bsw_com_tx_ChgPeriToNTimesNone( PduIdType u2PduId, Bsw_Com_RetStatusType s1QueExist );
void                  bsw_com_tx_SendNTimesMsgNone( PduIdType u2PduId );
void                  bsw_com_tx_SetTxReqNTimerNone( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
void                  bsw_com_tx_SetTxFinNTimerNone( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
void                  bsw_com_tx_ClrSndNTimesChNone( Bsw_Com_NetworkType u1Network );
void                  bsw_com_tx_ClrSndNTimesMsgNone( PduIdType u2PduId );
void                  bsw_com_tx_SetTxReqChgPrdTimer( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
void                  bsw_com_tx_SetTxFinChgPrdTimer( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
Bsw_Com_RetStatusType bsw_com_tx_GetChgPrdIpduStat( PduIdType u2PduId );
void                  bsw_com_tx_InitChgPrdIpdu( void );
void                  bsw_com_tx_SetTxReqChgPrdTmrNn( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
void                  bsw_com_tx_SetTxFinChgPrdTmrNn( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
Bsw_Com_RetStatusType bsw_com_tx_GetChgPrdIpduStNone( PduIdType u2PduId );
void                  bsw_com_tx_InitChgPrdIpduNone( void );
void                  bsw_com_tx_SetEventAwakeNone( NetworkHandleType Network );
BswU1                 bsw_com_tx_TxWakeupEventNone( NetworkHandleType Network, PduIdType PduId );
void                  bsw_com_tx_InitPncTxStat( void );
void                  bsw_com_tx_InitPncTxStatNone( void );
void                  bsw_com_tx_ShutdownPncTxSt( void );
void                  bsw_com_tx_ShutdownPncTxStNone( void );
void                  bsw_com_tx_GetPncChTxSt( NetworkHandleType Network, BswU4* ptPrevStat, BswU4* ptReqStat, BswU1* ptStatChg, BswU1* ptPncNum, BswU2* ptPncPeriOffset );
void                  bsw_com_tx_GetPncChTxStNone( NetworkHandleType Network, BswU4* ptPrevStat, BswU4* ptReqStat, BswU1* ptStatChg, BswU1* ptPncNum, BswU2* ptPncPeriOffset );
void                  bsw_com_tx_GetPncChTxEnSt( NetworkHandleType Network, BswU1 u1PncNum, BswU4* ptReqStat, BswU1* ptStatChg );
void                  bsw_com_tx_GetPncChTxEnStNone( NetworkHandleType Network, BswU1 u1PncNum, BswU4* ptReqStat, BswU1* ptStatChg );
BswU1                 bsw_com_tx_ChkPncIpduTxSt( PduIdType u2PduId, BswU1 u1PncNum, BswConstR BswU4* ptPrevStat, BswConstR BswU4* ptReqStat );
BswU1                 bsw_com_tx_ChkPncIpduTxStNone( PduIdType u2PduId, BswU1 u1PncNum, BswConstR BswU4* ptPrevStat, BswConstR BswU4* ptReqStat );
void                  bsw_com_tx_SetPncChTxSt( NetworkHandleType Network, BswConstR BswU4* ptReqStat );
void                  bsw_com_tx_SetPncChTxStNone( NetworkHandleType Network, BswConstR BswU4* ptReqStat );
void                  bsw_com_tx_SetPncChTxEnSt( NetworkHandleType Network, BswConstR BswU4* ptReqStat );
void                  bsw_com_tx_SetPncChTxEnStNone( NetworkHandleType Network, BswConstR BswU4* ptReqStat );
void                  bsw_com_tx_SetPncIpduTxEnSt( PduIdType u2PduId, BswU1 u1PncNum, BswConstR BswU4* ptIpduGrpStat, BswConstR BswU4* ptTxStat, BswU2 u2PncPeriOffset );
void                  bsw_com_tx_SetPncIpduTxEnStNone( PduIdType u2PduId, BswU1 u1PncNum, BswConstR BswU4* ptIpduGrpStat, BswConstR BswU4* ptTxStat, BswU2 u2PncPeriOffset );
BswU1                 bsw_com_tx_GetPncIpduTxEnSt( PduIdType u2PduId );
BswU1                 bsw_com_tx_GetPncIpduTxEnStNone( PduIdType u2PduId );
BswU1                 bsw_com_tx_GetPncIpduPeriOfsSt( PduIdType u2PduId );
BswU1                 bsw_com_tx_GetPncIpduPrOfsNone( PduIdType u2PduId );
void                  bsw_com_tx_SetPncIpduPeriOfsOn( PduIdType u2PduId );
void                  bsw_com_tx_SetPncIpdPrOfsOnNone( PduIdType u2PduId );
BswU1                 bsw_com_tx_GetPncChNumber( NetworkHandleType Network );
BswU1                 bsw_com_tx_GetPncChNumberNone( NetworkHandleType Network );
void                  bsw_com_tx_SetPncIpduFstDly( PduIdType u2PduId, BswU1 u1PncNum );
void                  bsw_com_tx_SetIpduFstDly( PduIdType u2PduId, BswU1 u1PncNum );
void                  bsw_com_tx_JudgePncIpduTxStProc( BswU1 u1PncNum, BswU1 u1IpduChgSts, BswU1 u1PncIpduChgSts, BswU1* ptIpduProc, BswU1* ptIpduSubProc );
void                  bsw_com_tx_JudgeIpduTxStProc( BswU1 u1PncNum, BswU1 u1IpduChgSts, BswU1 u1PncIpduChgSts, BswU1* ptIpduProc, BswU1* ptIpduSubProc );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern  BswU2              bsw_com_tx_u2Tx[];                                       /* Periodic transmission timer                                      */
extern  BswU1              bsw_com_tx_u1ChgPrdStat[];                               /* Per-channel periodic switching state                             */
extern  BswU1              bsw_com_tx_u1TxIpduGrpReqStat[];                         /* The transmit I-PDU group state (Request)                         */
extern  BswU1              bsw_com_tx_u1TxIpduGrpStat[];                            /* The transmit I-PDU group state                                   */
extern  BswU4              bsw_com_tx_u4PncTxIpduGrReqStat[][BSW_COM_PNC_REQNUM];   /* PNC transmit I-PDU group state (Request)                         */
extern  BswU4              bsw_com_tx_u4PncTxIpduGrStat[][BSW_COM_PNC_REQNUM];      /* PNC transmit I-PDU group state                                   */

/* Unit internal public definition */
extern  BswU2              bsw_com_tx_u2Delay[];                                    /* Transmission delay timer                                         */
extern  Bsw_Com_TxModeType bsw_com_tx_CurrentTxMode[];                              /* Current transmission mode                                        */
extern  BswU1              bsw_com_tx_u1TxStop[];                                   /* Stop transmitting state                                          */
extern  BswU1              bsw_com_tx_u1TxStopMrr[];                                /* Stop transmitting state(mirror)                                  */
extern  BswU1              bsw_com_tx_u1TxReqStat[];                                /* Transmission request state                                       */
extern  BswU2              bsw_com_tx_u2NTimesIntv[];                               /* N times transmission timer                                       */
extern  BswU1              bsw_com_tx_u1NTimesCnt[];                                /* Number of transmissions when sending N times                     */
extern  BswU2              bsw_com_tx_u2ChgPrdIpduTime[];                           /* Per-message periodic switching transmission timer                */
extern  BswU1              bsw_com_tx_u1ChgPrdIpduCnt[];                            /* Transmission count at the end of the period switch for per-message */
extern  BswU1              bsw_com_tx_u1BitIndPrd[];                                /* Periodic transmit queue                                          */
extern  BswU1              bsw_com_tx_u1BitIndEv[];                                 /* Queue for event transmission                                     */
extern  BswU1              bsw_com_tx_u1TxRtyStop[];                                /* RAM for stop transmission retry                                  */
extern  BswU1              bsw_com_tx_u1EvTxStat[];                                 /* Event transmission availability                                  */
extern  BswU1              bsw_com_tx_u1PrdTxStat[];                                /* Enable/disable state of periodic transmission                    */
extern  BswU1              bsw_com_tx_u1PeriTxResetReq[];                           /* Request a periodic transmission reset                            */
extern  BswU2              bsw_com_tx_u2PeriTxOffset[];                             /* Periodic transmission offset time                                */
extern  BswU1              bsw_com_tx_u1PreTxMsgBuf[];                              /* Temporary buffer for notification before tansmission             */
extern  BswU4              bsw_com_tx_u4PncTxEnableReqStat[][BSW_COM_PNC_REQNUM];   /* PNC transmit Tx Enable/Disable state (Request)                   */
extern  BswU4              bsw_com_tx_u4PncTxEnableStat[][BSW_COM_PNC_REQNUM];      /* PNC transmit I-PDU Tx Enable/Disable state                       */
extern  Bsw_Com_PncIpduTxInfoType bsw_com_tx_stPncIpduTxInfo[];                     /* PNC I-PDU Tx Info                                                */
extern  BswU1              bsw_com_tx_u1FirstTxSetReq[];                            /* Request first transmission setting                               */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern  BswU1           (* BswConst bsw_com_rom_ptGetPncIpduTxStFunc)( NetworkHandleType Network, PduIdType u2PduId );

/* Unit internal public definition */
extern  BswConst BswU2            bsw_com_rom_u2BITINDNUM;
extern  BswConst BswU1            bsw_com_rom_u1DLYRTRGPRD;
extern  BswConst BswU1            bsw_com_rom_u1TXDLYBYMSG;
extern  BswConst BswU1            bsw_com_rom_u1TXDLYSW;
extern  BswConst BswU1            bsw_com_rom_u1TXTIMEOUT;
extern  BswConst BswU1            bsw_com_rom_u1EVTAWAKEFUNC;
extern  BswConst BswU1            bsw_com_rom_u1RETRIGGER[];
extern  BswConst BswU1            bsw_com_rom_u1TXDLY[];
extern  BswConst BswU1            bsw_com_rom_u1EVTRTRG[];
extern  BswConst BswU2            bsw_com_rom_u2SENDSTART[];
extern  BswConst BswU2            bsw_com_rom_u2CHGPERIODMSGNUM;
extern  BswConst BswU2            bsw_com_rom_u2SENDNTIMESMSGNUM;
extern  BswConst BswU2            bsw_com_rom_u2TXLIM[];
extern  BswConst BswU2            bsw_com_rom_u2BITINDCHTOP[];
extern  BswConst BswU2            bsw_com_rom_u2EVDELAYTIME;
extern  BswConst BswU2            bsw_com_rom_u2PncPeriodicOffset[];
extern  BswConst BswU1            bsw_com_rom_u1TXTIMEOUTMODE[];
extern  BswConst BswU1            bsw_com_rom_u1TXREQCONTINUE[];
extern  BswConst BswU1            bsw_com_rom_u1NonAwakePwonWait[];

extern  BswConst Bsw_Com_TickTimeType      bsw_com_u2TxDelayTbl[];            /* Initial transmission delay time table                     */
extern  BswConst Bsw_Com_TickTimeType      bsw_com_u2DelayTbl[];              /* Transmission delay time table                         */
extern  BswConst Bsw_Com_TickTimeType      bsw_com_u2PrdDelayTbl[];           /* Periodic transmission delay time table                     */
extern  BswConst Bsw_Com_TickTimeType      bsw_com_u2TxTimeoutTbl[];          /* Transmission completion waiting time table                     */
extern  BswConst Bsw_Com_TickTimeType      bsw_com_u2FirstTxTimeoutTbl[];     /* First Transmission completion waiting time table               */
extern  BswConst Bsw_Com_NetInfoType       bsw_com_stNetInfoTxMsgTbl[];       /* Transmit message ID index table         */
extern  BswConst Bsw_Com_NTimesInfoType    bsw_com_tx_stSendNTimesInfo[];     /* N times transmission information table                          */
extern  BswConst Bsw_Com_ChgPrdInfoType    bsw_com_tx_stChgPeriodIpduInfo[];  /* Per-message periodic switching transmission information table   */

extern  void            (* BswConst bsw_com_rom_ptAlvCntrFuncTx[])( PduIdType u2PduId, BswConstR PduInfoType *ptCanTrsMsg );
extern  void            (* BswConst bsw_com_rom_ptInitTxReqStFunc)( PduIdType u2PduId );
extern  void            (* BswConst bsw_com_rom_ptSetTxReqStFunc)( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
extern  BswU1           (* BswConst bsw_com_rom_ptGetTxReqStFunc)( PduIdType u2PduId );
extern  void            (* BswConst bsw_com_rom_ptTransCfmFunc)( PduIdType u2PduId );
extern  BswU2           (* BswConst bsw_com_rom_ptTxTimeoutFunc)( PduIdType u2PduId );
extern  void            (* BswConst bsw_com_rom_ptSndNTimCntFunc)( void );
extern  Bsw_Com_RetStatusType (* BswConst bsw_com_rom_ptChgPeriToNTimFunc)( PduIdType u2PduId, Bsw_Com_RetStatusType s1QueExist );
extern  void            (* BswConst bsw_com_rom_ptSndNTimMsgFunc)( PduIdType u2PduId );
extern  void            (* BswConst bsw_com_rom_ptSetTxReqNTimFunc)( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
extern  void            (* BswConst bsw_com_rom_ptSetTxFinNTimFunc)( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
extern  void            (* BswConst bsw_com_rom_ptClrSndNTimChFunc)( Bsw_Com_NetworkType u1Network );
extern  void            (* BswConst bsw_com_rom_ptClrSndNTimMsgFunc)( PduIdType u2PduId );
extern  void            (* BswConst bsw_com_rom_ptChgPrdCntFunc)( void );
extern  void            (* BswConst bsw_com_rom_ptTxReqChgPrdFunc)( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
extern  void            (* BswConst bsw_com_rom_ptTxFinChgPrdFunc)( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
extern  Bsw_Com_RetStatusType (* BswConst bsw_com_rom_ptGetChgPrdStatFunc)( PduIdType u2PduId );
extern  void            (* BswConst bsw_com_tx_ptSetEventAwake)( NetworkHandleType Network );
extern  BswU1           (* BswConst bsw_com_tx_ptTxWakeupEvent)( NetworkHandleType Network, PduIdType PduId );
extern  void            (* BswConst bsw_com_rom_ptInitPncTxStatFunc)( void );
extern  void            (* BswConst bsw_com_rom_ptDeInitPncTxStFunc)( void );
extern  void            (* BswConst bsw_com_rom_ptGetPncChTxStFunc)( NetworkHandleType Network, BswU4* ptPrevStat, BswU4* ptReqStat, BswU1* ptStatChg, BswU1* ptPncNum, BswU2* ptPncPeriOffset );
extern  void            (* BswConst bsw_com_rom_ptGetPncChTxEnStFunc)( NetworkHandleType Network, BswU1 u1PncNum, BswU4* ptReqStat, BswU1* ptStatChg );
extern  BswU1           (* BswConst bsw_com_rom_ptChkPncIpduTxStFunc)( PduIdType u2PduId, BswU1 u1PncNum, BswConstR BswU4* ptPrevStat, BswConstR BswU4* ptReqStat );
extern  void            (* BswConst bsw_com_rom_ptSetPncChTxStFunc)( NetworkHandleType Network, BswConstR BswU4* ptReqStat );
extern  void            (* BswConst bsw_com_rom_ptSetPncChTxEnStFunc)( NetworkHandleType Network, BswConstR BswU4* ptReqStat );
extern  void            (* BswConst bsw_com_rom_ptSetPncIpduTxEnStFunc)( PduIdType u2PduId, BswU1 u1PncNum, BswConstR BswU4* ptIpduGrpStat, BswConstR BswU4* ptTxStat, BswU2 u2PncPeriOffset );
extern  BswU1           (* BswConst bsw_com_rom_ptGetPncIpduTxEnStFunc)( PduIdType u2PduId );
extern  BswU1           (* BswConst bsw_com_rom_ptGetPncIpduPeriOfsFunc)( PduIdType u2PduId );
extern  void            (* BswConst bsw_com_rom_ptSetPncIpduPrOfsOnFunc)( PduIdType u2PduId );
extern  BswU1           (* BswConst bsw_com_rom_ptGetPncChNumberFunc)( NetworkHandleType Network );
extern  void            (* BswConst bsw_com_rom_ptSetPncIpduFstDlyFunc)( PduIdType u2PduId, BswU1 u1PncNum );
extern  void            (* BswConst bsw_com_rom_ptJdgPncTxStProcFunc)( BswU1 u1PncNum, BswU1 u1IpduChgSts, BswU1 u1PncIpduChgSts, BswU1* ptIpduProc, BswU1* ptIpduSubProc );

#endif /* BSW_COM_TX_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/06/30                                             */
/*  v1-0-1          :2018/04/04                                             */
/*  v1-1-0          :2018/11/15                                             */
/*  v2-0-0          :2022/02/21                                             */
/*  v2-1-0          :2022/11/08                                             */
/*  v2-2-0          :2023/07/06                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
