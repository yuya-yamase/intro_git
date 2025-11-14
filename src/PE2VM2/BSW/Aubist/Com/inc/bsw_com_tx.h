/* bsw_com_tx_h_v3-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
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
#define BSW_COM_QUEKIND_PERIOD          (1U)                    /* Specify the periodic transmit queue   */

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

#define BSW_COM_u1WKUP_PWON_OFF         ((BswU1)0x0FU)
#define BSW_COM_u1WKUP_PWON_ON          ((BswU1)0x1EU)
#define BSW_COM_u1WKUP_BS_OFF           ((BswU1)0x2DU)
#define BSW_COM_u1WKUP_BS_ON            ((BswU1)0x3CU)

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
void                  bsw_com_tx_InitComTxStat( NetworkHandleType Network, BswConstR BswU4* ptIpduGrpStat );
void                  bsw_com_tx_ShutdownComTxStat( void );
BswU1                 bsw_com_tx_GetPncIpduTxSt( NetworkHandleType Network, PduIdType u2PduId );
BswU1                 bsw_com_tx_GetPncIpduTxStNone( NetworkHandleType Network, PduIdType u2PduId );
void                  bsw_com_tx_InitTxTempBuf( void );

/* Unit internal public definition */
BswU2                 bsw_com_tx_NotifyPeriTxRtrgr( Bsw_Com_NetworkType u1Network, PduIdType u2PduId, BswU2 u2Time);
void                  bsw_com_tx_InitBit( void );
Bsw_Com_RetStatusType bsw_com_tx_AddBit( Bsw_Com_NetworkType u1Network, PduIdType u2PduId, Bsw_Com_TxQueType u1QueType );
void                  bsw_com_tx_DelBit( Bsw_Com_NetworkType u1Network, PduIdType u2PduId );
void                  bsw_com_tx_InitTxReqStat( PduIdType u2PduId );
void                  bsw_com_tx_SetTxReqStat( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
BswU1                 bsw_com_tx_GetTxReqStat( PduIdType u2PduId );
void                  bsw_com_tx_TransmitCfm( PduIdType u2PduId, Std_ReturnType u1Result );
BswU2                 bsw_com_tx_TxTimeout( PduIdType u2PduId );
void                  bsw_com_tx_InitTxReqStatNone( PduIdType u2PduId );
void                  bsw_com_tx_SetTxReqStatNone( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
BswU1                 bsw_com_tx_GetTxReqStatNone( PduIdType u2PduId );
void                  bsw_com_tx_TransmitCfmNone( PduIdType u2PduId, Std_ReturnType u1Result );
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
BswU1                 bsw_com_tx_GetPncIpduTxEnSt( PduIdType u2PduId, BswU1 u1PncUse );
BswU1                 bsw_com_tx_GetPncIpduTxEnStNone( PduIdType u2PduId, BswU1 u1PncUse );
void                  bsw_com_tx_SetPncIpduPeriOfsOn( PduIdType u2PduId );
void                  bsw_com_tx_SetPncIpdPrOfsOnNone( PduIdType u2PduId );
BswU1                 bsw_com_tx_GetPncChUse( NetworkHandleType Network );
BswU1                 bsw_com_tx_GetPncChUseNone( NetworkHandleType Network );
void                  bsw_com_tx_SetPncIpduFstDly( PduIdType u2PduId, BswU1 u1PncUse );
void                  bsw_com_tx_SetIpduFstDly( PduIdType u2PduId, BswU1 u1PncUse );
void                  bsw_com_tx_CancelTxToutBusWkup( PduIdType u2PduId );
void                  bsw_com_tx_CnclTxToutBusWkupNn( PduIdType u2PduId );
void                  bsw_com_tx_CancelTxToutClrIpdu( PduIdType u2PduId );
void                  bsw_com_tx_CnclTxToutClrIpduNn( PduIdType u2PduId );
BswU2                 bsw_com_tx_GetTxFinDlyTimer( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode, BswU2 u2Offset );
void                  bsw_com_tx_NotifyToutRtrgr( Bsw_Com_NetworkType u1Network, PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
void                  bsw_com_tx_UpdateTxStatus( BswU1 u1Ch );
void                  bsw_com_tx_UpdateTxStatusPnc( BswU1 u1Ch );
void                  bsw_com_tx_ResetPeriodicTimer( PduIdType u2PduID, BswU2 u2TxOffset );
void                  bsw_com_tx_ClearMDRmCh( NetworkHandleType Network );
void                  bsw_com_tx_ClearMDRmChNone( NetworkHandleType Network );
void                  bsw_com_tx_ClearMDRmMsg( Bsw_Com_NetworkType u1Network, PduIdType u2PduId );
void                  bsw_com_tx_ClearMDRmMsgNone( Bsw_Com_NetworkType u1Network, PduIdType u2PduId );
void                  bsw_com_tx_GetMetaDataTxMsg( PduIdType u2PduId, PduInfoType* ptSendMsg, Bsw_Com_RetStatusType s1QueExist );
void                  bsw_com_tx_GetMetaDataTxMsgNone( PduIdType u2PduId, PduInfoType* ptSendMsg, Bsw_Com_RetStatusType s1QueExist );
void                  bsw_com_tx_GetTxMsgUseMetaData( PduIdType u2PduId, PduInfoType* ptSendMsg, Bsw_Com_RetStatusType s1QueExist );
void                  bsw_com_tx_GetTxMsg( PduIdType u2PduId, PduInfoType* ptSendMsg, Bsw_Com_RetStatusType s1QueExist );
void                  bsw_com_tx_VPSTxIpduCalloutNone( PduIdType PduId, PduInfoType* PduInfoPtr );
void                  bsw_com_tx_VPSTxConfNone( PduIdType TxPduId );
void                  bsw_com_tx_VPSTxReqConfNone( PduIdType TxPduId );
void                  bsw_com_tx_InitBitRsp( void );
void                  bsw_com_tx_InitBitRspNone( void );
void                  bsw_com_tx_InitChannelRsp( NetworkHandleType network );
void                  bsw_com_tx_InitChannelRspNone( NetworkHandleType network );
void                  bsw_com_tx_InitTempMetaDataBuf( void );
void                  bsw_com_tx_InitTmpMetaBufNone( void );
void                  bsw_com_tx_AddBitRsp( Bsw_Com_NetworkType u1Network, PduIdType u2PduId );
void                  bsw_com_tx_DelBitRsp( Bsw_Com_NetworkType u1Network, PduIdType u2PduId );
void                  bsw_com_tx_DelBitRspNone( Bsw_Com_NetworkType u1Network, PduIdType u2PduId );
Bsw_Com_RetStatusType bsw_com_tx_GetBitRsp( Bsw_Com_NetworkType u1Network, PduIdType u2PduId );
Bsw_Com_RetStatusType bsw_com_tx_GetBitRspNone( Bsw_Com_NetworkType u1Network, PduIdType u2PduId );
void                  bsw_com_tx_DelBitUseMD( Bsw_Com_NetworkType u1Network, PduIdType u2PduId, Bsw_Com_RetStatusType s1QueExist );
void                  bsw_com_tx_DelBitUseMDNone( Bsw_Com_NetworkType u1Network, PduIdType u2PduId, Bsw_Com_RetStatusType s1QueExist );
Std_ReturnType        bsw_com_tx_CheckMetaDataUpdated( PduIdType u2PduId );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern  BswU2              bsw_com_tx_u2Tx[];                                       /* Periodic transmission timer                                      */
extern  BswU1              bsw_com_tx_u1ChgPrdStat[];                               /* Per-channel periodic switching state                             */
extern  BswU4              bsw_com_tx_u4TxIpduGrpReqStat[][BSW_COM_SYSSTATTBLNUM];  /* The transmit I-PDU group state (Request)                         */
extern  BswU4              bsw_com_tx_u4TxIpduGrpStat[][BSW_COM_SYSSTATTBLNUM];     /* The transmit I-PDU group state                                   */
extern  BswU4              bsw_com_tx_u4PncTxIpduGrReqStat[][BSW_COM_PNC_REQNUM];   /* PNC transmit I-PDU group state (Request)                         */
extern  BswU4              bsw_com_tx_u4PncTxIpduGrStat[][BSW_COM_PNC_REQNUM];      /* PNC transmit I-PDU group state                                   */
extern  BswU1              bsw_com_tx_u1BusWkupReq[];                               /* Request Bus Wakeup */
extern  BswU2              bsw_com_tx_u2DisableSend[];                              /* DisableSend */
extern  BswU2              bsw_com_tx_u2EnablePeriodic[];                           /* EnablePeriodic */

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
extern  BswU1              bsw_com_tx_u1BitIndRsp[];                                /* Queue for response sending                                       */
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
extern  BswU1              bsw_com_tx_u1MetaDataBuf[];                              /* MetaData size maximum                                            */

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
extern  BswConst BswU2            bsw_com_rom_u2PRETXBUFSIZE;
extern  BswConst BswU1            bsw_com_rom_u1TMPMETABUFSIZE;
extern  BswConst BswU2            bsw_com_rom_u2PncPeriodicOffset[];
extern  BswConst BswU1            bsw_com_rom_u1TXTIMEOUTMODE[];
extern  BswConst BswU1            bsw_com_rom_u1TXREQCONTINUE[];
extern  BswConst BswU1            bsw_com_rom_u1SENDNTIMESRTRG[];
extern  BswConst BswU1            bsw_com_rom_u1NonAwakePwonWait[];
extern  BswConst BswU1            bsw_com_rom_u1TXDISTIMBYMSG[];
extern  BswConst BswU1            bsw_com_rom_u1TXCLRSTOPTOUT[];
extern  BswConst BswU1            bsw_com_rom_u1TXSTOPTOUTHOOK[];

extern  BswConst Bsw_Com_TickTimeType      bsw_com_u2TxDelayTbl[];            /* Initial transmission delay time table                     */
extern  BswConst Bsw_Com_TickTimeType      bsw_com_u2DelayTbl[];              /* Transmission delay time table                         */
extern  BswConst Bsw_Com_TickTimeType      bsw_com_u2PrdDelayTbl[];           /* Periodic transmission delay time table                     */
extern  BswConst Bsw_Com_TickTimeType      bsw_com_u2TxTimeoutTbl[];          /* Transmission completion waiting time table                     */
extern  BswConst Bsw_Com_TickTimeType      bsw_com_u2FirstTxTimeoutTbl[];     /* First Transmission completion waiting time table               */
extern  BswConst Bsw_Com_NetInfoType       bsw_com_stNetInfoTxMsgTbl[];       /* Transmit message ID index table         */
extern  BswConst Bsw_Com_NTimesInfoType    bsw_com_tx_stSendNTimesInfo[];     /* N times transmission information table                          */
extern  BswConst Bsw_Com_ChgPrdInfoType    bsw_com_tx_stChgPeriodIpduInfo[];  /* Per-message periodic switching transmission information table   */
extern  BswConst Bsw_Com_TickTimeType      bsw_com_u2SendStartPwTbl[];        /* Per-message SendStart time table*/
extern  BswConst Bsw_Com_TickTimeType      bsw_com_u2DisableSendTbl[];        /* Per-message DisableSend time table */
extern  BswConst Bsw_Com_TickTimeType      bsw_com_u2EnablePeriodicTbl[];     /* Per-message EnablePeriodic time table */

extern  void            (* BswConst bsw_com_rom_ptAlvCntrFuncTx[])( PduIdType u2PduId, BswConstR PduInfoType *ptCanTrsMsg );
extern  void            (* BswConst bsw_com_rom_ptInitTxReqStFunc)( PduIdType u2PduId );
extern  void            (* BswConst bsw_com_rom_ptSetTxReqStFunc)( PduIdType u2PduId, Bsw_Com_TxModeType u1TxMode );
extern  BswU1           (* BswConst bsw_com_rom_ptGetTxReqStFunc)( PduIdType u2PduId );
extern  void            (* BswConst bsw_com_rom_ptTransCfmFunc)( PduIdType u2PduId, Std_ReturnType u1Result );
extern  BswU2           (* BswConst bsw_com_rom_ptTxTimeoutFunc)( PduIdType u2PduId );
extern  void            (* BswConst bsw_com_rom_ptTxCnclToutBWFunc)( PduIdType u2PduId );
extern  void            (* BswConst bsw_com_rom_ptTxCnclToutClrFunc)( PduIdType u2PduId );
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
extern  BswU1           (* BswConst bsw_com_rom_ptGetPncIpduTxEnStFunc)( PduIdType u2PduId, BswU1 u1PncUse );
extern  void            (* BswConst bsw_com_rom_ptSetPncIpduPrOfsOnFunc)( PduIdType u2PduId );
extern  BswU1           (* BswConst bsw_com_rom_ptGetPncChUseFunc)( NetworkHandleType Network );
extern  void            (* BswConst bsw_com_rom_ptSetPncIpduFstDlyFunc)( PduIdType u2PduId, BswU1 u1PncUse );
extern  void            (* BswConst bsw_com_rom_ptUpdateTxStsFunc[])( BswU1 u1Ch );

extern  void            (* BswConst bsw_com_rom_ptInitBitRspFunc)( void );
extern  void            (* BswConst bsw_com_rom_ptInitChRspFunc)( NetworkHandleType network );
extern  void            (* BswConst bsw_com_rom_ptInitTpMetaBufFunc)( void );
extern  void            (* BswConst bsw_com_rom_ptDelBitRspFunc)( Bsw_Com_NetworkType u1Network, PduIdType u2PduId );
extern  Bsw_Com_RetStatusType (* BswConst bsw_com_rom_ptGetBitRspFunc)( Bsw_Com_NetworkType u1Network, PduIdType u2PduId );
extern  void            (* BswConst bsw_com_rom_ptDelBitUseMDFunc)( Bsw_Com_NetworkType u1Network, PduIdType u2PduId, Bsw_Com_RetStatusType s1QueExist );
extern  void            (* BswConst bsw_com_rom_ptClrMDRmChFunc)( NetworkHandleType Network );
extern  void            (* BswConst bsw_com_rom_ptClrMDRmMsgFunc)( Bsw_Com_NetworkType u1Network, PduIdType u2PduId );
extern  void            (* BswConst bsw_com_rom_ptGetMDTxMsgFunc)( PduIdType u2PduId, PduInfoType* ptSendMsg, Bsw_Com_RetStatusType s1QueExist );
extern  void            (* BswConst bsw_com_rom_ptGetTxMsgFunc)( PduIdType u2PduId, PduInfoType* ptSendMsg, Bsw_Com_RetStatusType s1QueExist );
extern void             (* BswConst bsw_com_rom_ptVpsTxIpduCOFunc)( PduIdType PduId, PduInfoType* PduInfoPtr );
extern void             (* BswConst bsw_com_rom_ptVpsTxConfFunc)( PduIdType TxPduId );
extern void             (* BswConst bsw_com_rom_ptVpsTxReqConfFunc)( PduIdType TxPduId );
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
/*  v3-0-0          :2025/03/04                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
