/* bsw_cannm_a2_ctrl_h_v2-0-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/A2/CTRL/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_A2_CTRL_H
#define BSW_CANNM_A2_CTRL_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_CANNM_A2_PDU_DATA_LENGTH          (8U)            /* NM-PDU data length */

/* Enable/Disable flag */
#define BSW_CANNM_A2_u1FLAG_DISABLE           ((BswU1)0x0FU) /* Invalid */
#define BSW_CANNM_A2_u1FLAG_ENABLE            ((BswU1)0x1EU) /* Enabled */

/* Transmit and receive event */
#define BSW_CANNM_A2_u1TRX_NONE               ((BswU1)0x00U) /* No event                 */
#define BSW_CANNM_A2_u1TRX_TX                 ((BswU1)0x01U) /* Transmit event                 */
#define BSW_CANNM_A2_u1TRX_RX                 ((BswU1)0x02U) /* Received event                 */

/* Data location */
#define BSW_CANNM_A2_u1POS_DAT0               ((BswU1)0U)
#define BSW_CANNM_A2_u1POS_DAT1               ((BswU1)1U)
#define BSW_CANNM_A2_u1POS_DAT2               ((BswU1)2U)
#define BSW_CANNM_A2_u1POS_DAT3               ((BswU1)3U)
#define BSW_CANNM_A2_u1POS_DAT4               ((BswU1)4U)
#define BSW_CANNM_A2_u1POS_DAT5               ((BswU1)5U)
#define BSW_CANNM_A2_u1POS_DAT6               ((BswU1)6U)
#define BSW_CANNM_A2_u1POS_DAT7               ((BswU1)7U)

/* NM state (internal) */
#define BSW_CANNM_A2_STATE_DISABLE_TRX        (0x01FEU)
#define BSW_CANNM_A2_STATE_PWON_WAIT          (0x02FDU)
#define BSW_CANNM_A2_STATE_BUS_SLEEP          (0x03FCU)
#define BSW_CANNM_A2_STATE_PREP_BUS_SLP       (0x04FBU)
#define BSW_CANNM_A2_STATE_READY_SLEEP        (0x05FAU)
#define BSW_CANNM_A2_STATE_NORMAL_OPE         (0x06F9U)
#define BSW_CANNM_A2_STATE_RPT_MSG            (0x07F8U)
#define BSW_CANNM_A2_STATE_SHUTDOWN           (0x08F7U)
#define BSW_CANNM_A2_STATE_SLEEP              (0x09F6U)
#define BSW_CANNM_A2_STATE_INVALID            (0x0AF5U)

/* For judging communication failure state */
#define BSW_CANNM_A2_u1COM_NORMAL             ((BswU1)0x0FU)
#define BSW_CANNM_A2_u1COM_ERROR              ((BswU1)0x1EU)

/* Bus awake factor */
#define BSW_CANNM_A2_u1BUSAWAKE_NONE          ((BswU1)0x0FU)    /* No bus awake factor */
#define BSW_CANNM_A2_u1BUSAWAKE_EXIST         ((BswU1)0x1EU)    /* Bus Awake factor exists */

/* Timer operation state */
#define BSW_CANNM_A2_u1TIMER_ON               ((BswU1)0x0FU)    /* During timer operation */
#define BSW_CANNM_A2_u1TIMER_OFF              ((BswU1)0x1EU)    /* Timer is stopped */

/* Channel power supply */
#define BSW_CANNM_A2_u1PWSUPPLY_ON            ((BswU1)0x0FU)    /* Channel power ON  */
#define BSW_CANNM_A2_u1PWSUPPLY_OFF           ((BswU1)0x1EU)    /* Channel power OFF */

#define BSW_CANNM_A2_u1COM_DIS                ((BswU1)0x0FU)    /* Communication function disabled */
#define BSW_CANNM_A2_u1COM_ENA                ((BswU1)0x1EU)    /* Communication function enabled */

#define BSW_CANNM_A2_u1TXTO_CNT_CLR           ((BswU1)0U)       /* Initial value of transmission timeout count */

#define BSW_CANNM_A2_u2TIME_STOP              ((BswU2)0U)       /* Timer stopping value */
#define BSW_CANNM_A2_u1TX_CNT_NONE            ((BswU1)0U)       /* Transmission count 0 */
#define BSW_CANNM_A2_u1TX_CNT_ONE             ((BswU1)1U)       /* Transmission count 1    */

#define BSW_CANNM_A2_u1CBV_INIT               ((BswU1)0x00U)    /* Initial value of CBV data          */
#define BSW_CANNM_A2_u1TRXDATA_INIT           ((BswU1)0x00U)    /* Initial value of the temporary data for transmission/receiving */

/* Bit shift */
#define BSW_CANNM_A2_SHIFT_1BYTE              (8U)

/* Mask position */
#define BSW_CANNM_A2_u2MASK_HIGH              ((BswU2)0xFF00U)
#define BSW_CANNM_A2_u2MASK_LOW               ((BswU2)0x00FFU)

/* ECU Specification No. Number of bytes */
#define BSW_CANNM_A2_ECUSPECNO_SIZE           (2U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Structure for maintaining channel status */
typedef struct
{
    BswU1 u1TxRxEvent;         /* Transmit and receive event                 */
    BswU1 u1BusAwakeSelf;      /* Own-node bus wake-up factor */
    BswU1 u1BusAwakeOther;     /* Other-node bus wake-up factor */

    BswU1 u1ChPower;           /* Channel power on/off */

    BswU1 u1TxFail;            /* Number of successful transmissions (for communication failure detection) */
    BswU1 u1ComErrorSt;        /* Communication failure state                 */

    BswU1 u1TxTimeoutOn;       /* Flag for enabling/disabling  transmit timeout timer measurement           */
    BswU1 u1EvTimerOn;         /* Flag for event message transmission permission timer measurement availability */
    BswU1 u1PeriTimerOn;       /* Flag for periodic message transmission enable timer measurement availability     */
    BswU1 u1PwonWaitTimerOn;   /* Flag for using/not using the sleep wait timer at power-on       */

    BswU1 u1TxCnt;             /* Number of times NMMessage transmission                              */
    BswU1 u1DummyPad;          /* Padding for alignment adjustment             */

    BswU2 u2NmSt;              /* NM status                                           */

    BswU2 u2NmStateTimer;      /* Timer for state transition                               */
                               /* NM_TIMEOUTTIME,NM_WAITBUSSLEEP,TEBSDisableWakeup */
    BswU2 u2TxCyclicTimer;     /* Timer for periodic transmission/immediate transmission/transmission offset measurement     */
    BswU2 u2RptMsgTimer;       /* REPEATMSG state maintenance timer                          */
    BswU2 u2TxTimeoutTimer;    /* Timer for measuring transmission timeout                     */
    BswU2 u2EvSendTimer;       /* Event message transmission enable timer                 */
    BswU2 u2PeriSendTimer;     /* Periodic message transmission enable timer                     */
    BswU2 u2PwonWaitTimer;     /* Sleep wait timer at power-on                       */

} Bsw_CanNmA2_ChStsType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/* Component internal publication definition */
void            bsw_cannm_a2_ctrl_InitCom( void );                                              /* Initialize the communication restriction function    */
BswU1           bsw_cannm_a2_ctrl_CheckDisCom( BswU1 u1NetID );                                 /* Judges whether the communication function is enabled or disabled */

/* Component internal publication definition (Dummy function) */
void            bsw_cannm_a2_ctrl_InitComNone( void );                                          /* Initialize the communication restriction function (Dummy function)    */
BswU1           bsw_cannm_a2_ctrl_ChkComNone( BswU1 u1NetID );                                  /* Judges whether the communication function is enabled or disabled (Dummy function) */

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern Bsw_CanNmA2_ChStsType     bsw_cannm_a2_ctrl_stChSts[];                  /* NM status  */
extern BswU1                     bsw_cannm_a2_ctrl_u1TxCBVData[];              /* CBV information */
extern BswU1                     bsw_cannm_a2_ctrl_u1DisableCom[];             /* Enable/Disable the communication restriction function */
extern BswU1                     bsw_cannm_a2_ctrl_u1TmpSendData[][BSW_CANNM_A2_PDU_DATA_LENGTH]; /* Temporary data area for transmission */
extern BswU1                     bsw_cannm_a2_ctrl_u1TmpRecvData[][BSW_CANNM_A2_PDU_DATA_LENGTH]; /* Temporary data area for receiving */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU1            bsw_cannm_a2_ctrl_u1ChNum;                    /* Maximum number of channels              */
extern BswConst BswU1            bsw_cannm_a2_ctrl_u1ChOffset;                 /* Channel offset          */
extern BswConst BswU1            bsw_cannm_a2_ctrl_u1ImmRestart;               /* Immediate transmission function                */
extern BswConst BswU1            bsw_cannm_a2_ctrl_u1TxLimit;                  /* Upper limit of the transmission counter          */

extern BswConst BswU1            bsw_cannm_a2_ctrl_u1Channel[];                /* Channel used/not used table*/
extern BswConst BswU1            bsw_cannm_a2_ctrl_u1BusSleepTbl[];            /* Table to judge whether bus-sleep is used or not */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2NMToutTim[];              /* NetworkTimeout time          */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2RptMsgTim[];              /* Duration to maintain RepeatMessageState  */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2TxToutTim[];              /* Transmission timeout time        */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2WaitSlpTim[];             /* Sleep transition waiting time        */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2MsgCycOfs[];              /* Periodic transmission delay time            */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2MsgCycTim[];              /* Periodic transmission interval                */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2ImmCycTim[];              /* Immediate transmission interval                */
extern BswConst BswU1            bsw_cannm_a2_ctrl_u1ImmNumOfTx[];             /* Number of immediate transmissions                */
extern BswConst BswU1            bsw_cannm_a2_ctrl_u1CBVPos[];                 /* Position of the ControlBitVector      */
extern BswConst BswU1            bsw_cannm_a2_ctrl_u1NodeIDPos[];              /* Position of SourceNodeIdentifer   */
extern BswConst BswU1            bsw_cannm_a2_ctrl_u1ActiveWkUp[];             /* Switching the ActiveWkUp function        */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2DisWkupTim[];             /* Edge detection permission wait time after bus sleep (DisableWakeup)      */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2SndStartTim[];            /* Transmission start waiting time (SendStart)                              */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2DisSndTim[];              /* Transmission starting wait time at bus wake-up (DisableSend)        */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2EnaPeriTim[];             /* Periodic transmission starting wait time at bus wake-up (EnablePeriodic) */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2PwOnWaitTim[];            /* Sleep wait time at power-on (PwOnWaitSleepTime)              */
extern BswConst BswU1            bsw_cannm_a2_ctrl_u1NodeID[];                 /* NodeID                      */
extern BswConst BswU1            bsw_cannm_a2_ctrl_u1InitTxData[];             /* Initial value of transmission data fields  */
extern BswConst BswU1            bsw_cannm_a2_ctrl_u1EcuSpecNo[][BSW_CANNM_A2_ECUSPECNO_SIZE]; /* ECU Specification No */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2EvDisTim[];               /* Event transmission disable time        */

extern BswConst BswU2            bsw_cannm_a2_ctrl_u2MaxSlpTim;                /* State transition timer (10ms order) */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2MaxStateTim;              /* State transition timer (1ms order)  */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2MaxToutTim;               /* Maximum value of transmit timeout timer      */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2MaxEvSndTim;              /* Maximum value of control Msg (event) transmission timer */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2MaxPrSndTim;              /* Maximum value of control Msg (periodic) transmission timer     */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2MaxCycTim;                /* Maximum value of periodic transmission timer(NM Frame)  */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2MaxRpMsgTim;              /* Maximum value of REPEATMSG timer             */
extern BswConst BswU2            bsw_cannm_a2_ctrl_u2MaxPWONWTim;              /* Maximum value of TPWONWaitBusSleep timer     */

extern void    (* BswConst bsw_cannm_a2_ctrl_InitComFunc)( void );
extern BswU1   (* BswConst bsw_cannm_a2_ctrl_ChkComFunc)( BswU1 u1NetID );


#endif  /* BSW_CANNM_A2_CTRL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/04/27                                             */
/*  v1-1-0          :2018/12/17                                             */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
