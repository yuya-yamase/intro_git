/* bsw_cannm_c2_ctrl_h_v2-2-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/C2/CTRL/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_C2_CTRL_H
#define BSW_CANNM_C2_CTRL_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_CANNM_C2_PDU_DATA_LENGTH          (8U)            /* NM-PDU data length */

/* Enable/Disable flag */
#define BSW_CANNM_C2_u1FLAG_DISABLE           ((BswU1)0x0FU) /* Invalid */
#define BSW_CANNM_C2_u1FLAG_ENABLE            ((BswU1)0x1EU) /* Enabled */

/* Transmit and receive event */
#define BSW_CANNM_C2_u1TRX_NONE               ((BswU1)0x00U) /* No event                 */
#define BSW_CANNM_C2_u1TRX_TX                 ((BswU1)0x01U) /* Transmit event                 */
#define BSW_CANNM_C2_u1TRX_RX                 ((BswU1)0x02U) /* Received event                 */

/* Data location */
#define BSW_CANNM_C2_u1POS_DAT0               ((BswU1)0U)
#define BSW_CANNM_C2_u1POS_DAT1               ((BswU1)1U)
#define BSW_CANNM_C2_u1POS_DAT2               ((BswU1)2U)
#define BSW_CANNM_C2_u1POS_DAT3               ((BswU1)3U)
#define BSW_CANNM_C2_u1POS_DAT4               ((BswU1)4U)
#define BSW_CANNM_C2_u1POS_DAT5               ((BswU1)5U)
#define BSW_CANNM_C2_u1POS_DAT6               ((BswU1)6U)
#define BSW_CANNM_C2_u1POS_DAT7               ((BswU1)7U)

/* NM state (internal) */
#define BSW_CANNM_C2_u2ST_DISABLE_TRX         ((BswU2)0x01FEU)
#define BSW_CANNM_C2_u2ST_PWON_WKCHK          ((BswU2)0x02FDU)
#define BSW_CANNM_C2_u2ST_BUS_SLEEP           ((BswU2)0x03FCU)
#define BSW_CANNM_C2_u2ST_PREP_BUS_SLP        ((BswU2)0x04FBU)
#define BSW_CANNM_C2_u2ST_READY_SLEEP         ((BswU2)0x05FAU)
#define BSW_CANNM_C2_u2ST_NORMAL_OPE          ((BswU2)0x06F9U)
#define BSW_CANNM_C2_u2ST_RPT_MSG             ((BswU2)0x07F8U)
#define BSW_CANNM_C2_u2ST_SHUTDOWN            ((BswU2)0x08F7U)
#define BSW_CANNM_C2_u2ST_SLEEP               ((BswU2)0x09F6U)
#define BSW_CANNM_C2_u2ST_WAKE_CHECK          ((BswU2)0x0AF5U)
#define BSW_CANNM_C2_u2ST_INVALID             ((BswU2)0x0BF4U)

/* Bus awake factor */
#define BSW_CANNM_C2_u1BUSAWAKE_NONE          ((BswU1)0x0FU)    /* No bus awake factor */
#define BSW_CANNM_C2_u1BUSAWAKE_EXIST         ((BswU1)0x1EU)    /* Bus Awake factor exists */

/* Timer operation state */
#define BSW_CANNM_C2_u1TIMER_ON               ((BswU1)0x0FU)    /* During timer operation */
#define BSW_CANNM_C2_u1TIMER_OFF              ((BswU1)0x1EU)    /* Timer is stopped */

/* Transmission enable/disable state */
#define BSW_CANNM_C2_u1TX_EV_ENABLE           ((BswU1)0x1EU)    /* Enable event transmission     */
#define BSW_CANNM_C2_u1TX_PERI_ENABLE         ((BswU1)0x2DU)    /* Enable periodic transmission         */
#define BSW_CANNM_C2_u1TX_EV_PR_ENABLE        ((BswU1)0x3CU)    /* Event Periodic Transmission Permission */
#define BSW_CANNM_C2_u1TX_DISABLE             ((BswU1)0x0FU)    /* Disable Transmission             */

/* Channel power supply */
#define BSW_CANNM_C2_u1PWSUPPLY_ON            ((BswU1)0x0FU)    /* Channel power ON  */
#define BSW_CANNM_C2_u1PWSUPPLY_OFF           ((BswU1)0x1EU)    /* Channel power OFF */

#define BSW_CANNM_C2_u1COM_DIS                ((BswU1)0x0FU)    /* Communication function disabled */
#define BSW_CANNM_C2_u1COM_ENA                ((BswU1)0x1EU)    /* Communication function enabled */

#define BSW_CANNM_C2_u2TIME_STOP              ((BswU2)0U)       /* Timer stopping value */
#define BSW_CANNM_C2_u1TX_CNT_NONE            ((BswU1)0U)       /* Transmission count 0 */
#define BSW_CANNM_C2_u1TX_CNT_ONE             ((BswU1)1U)       /* Transmission count 1    */

#define BSW_CANNM_C2_u1CBV_INIT               ((BswU1)0x40U)    /* Initial value of CBV data(PNI=1)   */
#define BSW_CANNM_C2_u1TRXDATA_INIT           ((BswU1)0x00U)    /* Initial value of the temporary data for transmission/receiving */

/* Bit shift */
#define BSW_CANNM_C2_SHIFT_1BYTE              (8U)

/* Mask position */
#define BSW_CANNM_C2_u2MASK_HIGH              ((BswU2)0xFF00U)
#define BSW_CANNM_C2_u2MASK_LOW               ((BswU2)0x00FFU)

/* For inverting bits */
#define BSW_CANNM_C2_u1ALL_BIT                ((BswU1)0xFFU)

/* Enable/Disable the transition from NetworkMode to RepeatMessageState */
#define BSW_CANNM_C2_u1CHG_RPTST_NONE         ((BswU1)0x0FU)    /* No state transition */
#define BSW_CANNM_C2_u1CHG_RPTST_EXIST        ((BswU1)0x1EU)    /* State transition available */

#define BSW_CANNM_C2_u1TXCONF_NONE            ((BswU1)0x0FU)    /* No transmission completion notification exists */
#define BSW_CANNM_C2_u1TXCONF_EXIST           ((BswU1)0x1EU)    /* Transmission completion notification exists */

#define BSW_CANNM_C2_u1PREENA_NONE            ((BswU1)0x0FU)    /* CanNm_CbkPreEnableTx : not called (call request for wake up) */
#define BSW_CANNM_C2_u1PREENA_DONE            ((BswU1)0x1EU)    /* CanNm_CbkPreEnableTx : called */
#define BSW_CANNM_C2_u1PREENA_WKTO_REQ        ((BswU1)0x2DU)    /* CanNm_CbkPreEnableTx : call request for wake up and TxTimeout */
#define BSW_CANNM_C2_u1PREENA_TXTO_REQ        ((BswU1)0x3CU)    /* CanNm_CbkPreEnableTx : call request for TxTimeout */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Structure for maintaining channel status */
typedef struct
{
    BswU2 u2NmSt;              /* NM status                                           */
    BswU2 u2NmStateTimer;      /* Timer for state transition                               */
                               /* NM_TIMEOUTTIME,NM_WAITBUSSLEEP,TEBSDisableWakeup */
    BswU2 u2RptMsgTimer;       /* REPEATMSG state maintenance timer                          */
    BswU1 u1TxRxEvent;         /* Transmit and receive event                                   */
    BswU1 u1BusAwakeSelf;      /* Own-node bus wake-up factor                   */
    BswU1 u1BusAwakeOther;     /* Other-node bus wake-up factor                   */
    BswU1 u1ChPower;           /* Channel power on/off                                 */

    BswU2 u2TxCyclicTimer;     /* Timer for periodic transmission/immediate transmission/transmission offset measurement     */
    BswU1 u1TxConf;            /* NMMessage transmission completetion Yes/No                          */
    BswU1 u1TxCnt;             /* Number of times NMMessage transmission                              */
    BswU1 u1StopTxCnt;         /* Number of transmissions after stopping communication request                         */

    BswU1 u1TxStatus;          /* Flag for control message transmission enable/disable                   */
    BswU2 u2EvSendTimer;       /* Event message transmission enable timer                 */
    BswU2 u2PeriSendTimer;     /* Periodic message transmission enable timer                     */

    BswU2 u2TxTimeoutTimer;    /* Timer for measuring transmission timeout                     */
    BswU1 u1TxTimeoutOn;       /* Flag for enabling/disabling  transmit timeout timer measurement           */
    BswU1 u1PreEnaTxSts;       /* Flag for CanNm_CbkPreEnableTx is called or not */

} Bsw_CanNmC2_ChStsType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/* Component internal publication definition */
void            bsw_cannm_c2_ctrl_InitCom( void );                                              /* Initialize the communication restriction function    */
BswU1           bsw_cannm_c2_ctrl_CheckDisCom( BswU1 u1NetID );                                 /* Judges whether the communication function is enabled or disabled */

/* Component internal publication definition (Dummy function) */
void            bsw_cannm_c2_ctrl_InitComNone( void );                                          /* Initialize the communication restriction function (Dummy function)    */
BswU1           bsw_cannm_c2_ctrl_ChkComNone( BswU1 u1NetID );                                  /* Judges whether the communication function is enabled or disabled (Dummy function) */

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern Bsw_CanNmC2_ChStsType     bsw_cannm_c2_ctrl_stChSts[];                  /* NM status  */
extern BswU1                     bsw_cannm_c2_ctrl_u1TxCBVData[];              /* CBV information */
extern BswU1                     bsw_cannm_c2_ctrl_u1DisableCom[];             /* Enable/Disable the communication restriction function */
extern BswU1                     bsw_cannm_c2_ctrl_u1TmpSendData[][BSW_CANNM_C2_PDU_DATA_LENGTH]; /* Temporary data area for transmission */
extern BswU1                     bsw_cannm_c2_ctrl_u1TmpRecvData[][BSW_CANNM_C2_PDU_DATA_LENGTH]; /* Temporary data area for receiving */

extern BswU1                     bsw_cannm_c2_ctrl_u1ReqRptSt[];               /* Transition flag to RepeatMessageState */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU1            bsw_cannm_c2_ctrl_u1ChNum;                    /* Maximum number of channels              */
extern BswConst BswU1            bsw_cannm_c2_ctrl_u1ChOffset;                 /* Channel offset          */
extern BswConst BswU1            bsw_cannm_c2_ctrl_u1ImmRestart;               /* Immediate transmission function                */
extern BswConst BswU1            bsw_cannm_c2_ctrl_u1UStbToutFnc;              /* Processing when transmission timeout occurs in non-normal condition */

extern BswConst BswU1            bsw_cannm_c2_ctrl_u1Channel[];                /* Channel used/not used table*/
extern BswConst BswU1            bsw_cannm_c2_ctrl_u1BusSleepTbl[];            /* Table to judge whether bus-sleep is used or not */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2NMToutTim[];              /* NetworkTimeout time          */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2RptMsgTim[];              /* Duration to maintain RepeatMessageState  */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2TxToutTim[];              /* Transmission timeout time        */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2WaitSlpTim[];             /* Sleep transition waiting time        */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2MsgCycOfs[];              /* Periodic transmission delay time            */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2MsgCycTim[];              /* Periodic transmission interval                */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2ImmCycTim[];              /* Immediate transmission interval                */
extern BswConst BswU1            bsw_cannm_c2_ctrl_u1ImmNumOfTx[];             /* Number of immediate transmissions                */
extern BswConst BswU1            bsw_cannm_c2_ctrl_u1CBVPos[];                 /* Position of the ControlBitVector      */
extern BswConst BswU1            bsw_cannm_c2_ctrl_u1NodeIDPos[];              /* Position of SourceNodeIdentifer   */
extern BswConst BswU1            bsw_cannm_c2_ctrl_u1UserDataPos[];            /* Location of user data          */
extern BswConst BswU1            bsw_cannm_c2_ctrl_u1UserDataLen[];            /* Length of user data          */
extern BswConst BswU1            bsw_cannm_c2_ctrl_u1ActiveWkUp[];             /* Switching the ActiveWkUp function        */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2SndStartTim[];            /* Transmission start waiting time (SendStart)                              */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2DisSndTim[];              /* Transmission starting wait time at bus wake-up (DisableSend)        */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2EnaPeriTim[];             /* Periodic transmission starting wait time at bus wake-up (EnablePeriodic) */
extern BswConst BswU1            bsw_cannm_c2_ctrl_u1NodeID[];                 /* NodeID                      */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2WakeChkTim[];             /* External request monitoring time during PassiveWakeup */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2TrcvWaitTim[];            /* Transceiver mode transition waiting time */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2WkChkStTim[];             /* Wake-up check state transition wait time */

extern BswConst BswU1            bsw_cannm_c2_ctrl_u1StopTxNum[];              /* Number of transmissions after stopping communication request      */
extern BswConst BswU1            bsw_cannm_c2_ctrl_u1ToTxStop[];               /* Stop transmission due to TxTimeout */

extern BswConst BswU2            bsw_cannm_c2_ctrl_u2MaxSlpTim;                /* State transition timer (10ms order)      */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2MaxStateTim;              /* State transition timer (1ms order)       */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2MaxToutTim;               /* Maximum value of transmit timeout timer           */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2MaxEvSndTim;              /* Maximum value of control Msg (event) transmission timer */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2MaxPrSndTim;              /* Maximum value of control Msg (periodic) transmission timer     */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2MaxCycTim;                /* Maximum value of periodic transmission timer(NM Frame)       */
extern BswConst BswU2            bsw_cannm_c2_ctrl_u2MaxRpMsgTim;              /* Maximum value of REPEATMSG timer                  */

extern void             (* BswConst bsw_cannm_c2_ctrl_ptInitComFunc)( void );
extern BswU1            (* BswConst bsw_cannm_c2_ctrl_ptChkComFunc)( BswU1 u1NetID );

#endif  /* BSW_CANNM_C2_CTRL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2018/11/19                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v2-2-0          :2023/05/24                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
