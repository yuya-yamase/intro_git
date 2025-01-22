/* bsw_cannm_y_ctrl_h_v3-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/Y/CTRL/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANNM_Y_CTRL_H
#define BSW_CANNM_Y_CTRL_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_CANNM_Y_PDU_DATA_LENGTH          (8U)            /* NM-PDU data length */

/* Enable/Disable flag */
#define BSW_CANNM_Y_u1FLAG_DISABLE           ((BswU1)0x0FU) /* Invalid */
#define BSW_CANNM_Y_u1FLAG_ENABLE            ((BswU1)0x1EU) /* Enabled */

/* Transmit and receive event */
#define BSW_CANNM_Y_u1TRX_NONE               ((BswU1)0x00U) /* No event                                            */
#define BSW_CANNM_Y_u1TRX_TX                 ((BswU1)0x01U) /* Transmit event                                      */
#define BSW_CANNM_Y_u1TRX_RX                 ((BswU1)0x02U) /* Received event                                      */
#define BSW_CANNM_Y_u1TRX_TX_ERR             ((BswU1)0x04U) /* Transmit (failure) event                            */
#define BSW_CANNM_Y_u1TRX_TX_DIS             ((BswU1)0x08U) /* Transmit event when communication function disabled */

/* Data location */
#define BSW_CANNM_Y_u1POS_DAT0               ((BswU1)0U)
#define BSW_CANNM_Y_u1POS_DAT1               ((BswU1)1U)
#define BSW_CANNM_Y_u1POS_DAT2               ((BswU1)2U)
#define BSW_CANNM_Y_u1POS_DAT3               ((BswU1)3U)
#define BSW_CANNM_Y_u1POS_DAT4               ((BswU1)4U)
#define BSW_CANNM_Y_u1POS_DAT5               ((BswU1)5U)
#define BSW_CANNM_Y_u1POS_DAT6               ((BswU1)6U)
#define BSW_CANNM_Y_u1POS_DAT7               ((BswU1)7U)

/* NM state (internal) */
#define BSW_CANNM_Y_u2ST_DISABLE_TRX         ((BswU2)0x01FEU)    /* Communication disabled state */
#define BSW_CANNM_Y_u2ST_PWON_WKCHK          ((BswU2)0x02FDU)    /* Start-up check status at power-on */
#define BSW_CANNM_Y_u2ST_BUS_SLEEP           ((BswU2)0x03FCU)    /* Bus-sleep state */
#define BSW_CANNM_Y_u2ST_PREP_BUS_SLP        ((BswU2)0x04FBU)    /* Prepare bus-sleep state */
#define BSW_CANNM_Y_u2ST_READY_SLEEP         ((BswU2)0x05FAU)    /* Bus passive start state */
#define BSW_CANNM_Y_u2ST_NORMAL_OPE          ((BswU2)0x06F9U)    /* Normal operation state */
#define BSW_CANNM_Y_u2ST_RPT_MSG             ((BswU2)0x07F8U)    /* Repeat message state */
#define BSW_CANNM_Y_u2ST_SHUTDOWN            ((BswU2)0x08F7U)    /* Shutdown state */
#define BSW_CANNM_Y_u2ST_SLEEP               ((BswU2)0x09F6U)    /* Microcomputer sleep state */
#define BSW_CANNM_Y_u2ST_WAKE_CHECK          ((BswU2)0x0AF5U)    /* Wake-up check state */
#define BSW_CANNM_Y_u2ST_PWON_CHDRVWT        ((BswU2)0x0BF4U)    /* Channel drive waiting state at power-on */
#define BSW_CANNM_Y_u2ST_CHDRVWT             ((BswU2)0x0CF3U)    /* Channel drive wait state */
#define BSW_CANNM_Y_u2ST_INVALID             ((BswU2)0x0DF2U)    /* failure state */

/* Bus awake factor */
#define BSW_CANNM_Y_u1BUSAWAKE_NONE          ((BswU1)0x0FU)    /* No bus awake factor */
#define BSW_CANNM_Y_u1BUSAWAKE_EXIST         ((BswU1)0x1EU)    /* Bus Awake factor exists */

/* Timer operation state */
#define BSW_CANNM_Y_u1TIMER_ON               ((BswU1)0x0FU)    /* During timer operation */
#define BSW_CANNM_Y_u1TIMER_OFF              ((BswU1)0x1EU)    /* Timer is stopped */

/* Transmission enable/disable state */
#define BSW_CANNM_Y_u1TX_EV_ENABLE           ((BswU1)0x1EU)    /* Enable event transmission     */
#define BSW_CANNM_Y_u1TX_PERI_ENABLE         ((BswU1)0x2DU)    /* Enable periodic transmission         */
#define BSW_CANNM_Y_u1TX_EV_PR_ENABLE        ((BswU1)0x3CU)    /* Event Periodic Transmission Permission */
#define BSW_CANNM_Y_u1TX_DISABLE             ((BswU1)0x0FU)    /* Disable Transmission             */

/* Channel power supply */
#define BSW_CANNM_Y_u1PWSUPPLY_ON            ((BswU1)0x0FU)    /* Channel power ON  */
#define BSW_CANNM_Y_u1PWSUPPLY_OFF           ((BswU1)0x1EU)    /* Channel power OFF */

#define BSW_CANNM_Y_u1COM_DIS                ((BswU1)0x0FU)    /* Communication function disabled */
#define BSW_CANNM_Y_u1COM_ENA                ((BswU1)0x1EU)    /* Communication function enabled */

#define BSW_CANNM_Y_u2TIME_STOP              ((BswU2)0U)       /* Timer stopping value */
#define BSW_CANNM_Y_u1TX_CNT_NONE            ((BswU1)0U)       /* Transmission count 0 */
#define BSW_CANNM_Y_u1TX_CNT_ONE             ((BswU1)1U)       /* Transmission count 1    */

#define BSW_CANNM_Y_u1RXDATA_INIT            ((BswU1)0x00U)    /* Initial value of temporary data for receiving */
#define BSW_CANNM_Y_u1TXDATA_INIT            ((BswU1)0xFFU)    /* Initial value of temporary data for transmission */

/* Bit shift */
#define BSW_CANNM_Y_SHIFT_1BYTE              (8U)              /* 8-Bit shift */
#define BSW_CANNM_Y_SHIFT_2BYTE              (16U)             /* 16-Bit shift */
#define BSW_CANNM_Y_SHIFT_3BYTE              (24U)             /* 24-Bit shift */

/* Mask position */
#define BSW_CANNM_Y_u2MASK_HIGH              ((BswU2)0xFF00U)
#define BSW_CANNM_Y_u2MASK_LOW               ((BswU2)0x00FFU)

/* Enable/Disable the transition from NetworkMode to RepeatMessageState */
#define BSW_CANNM_Y_u1CHG_RPTST_NONE         ((BswU1)0x0FU)    /* No state transition */
#define BSW_CANNM_Y_u1CHG_RPTST_EXIST        ((BswU1)0x1EU)    /* State transition available */

/* NMMessage transmission completion notification Yes/No */
#define BSW_CANNM_Y_u1TXCONF_NONE            ((BswU1)0x0FU)    /* No transmission completion notification exists */
#define BSW_CANNM_Y_u1TXCONF_EXIST           ((BswU1)0x1EU)    /* Transmission completion notification exists */

/* Wake-up type of the start of measurement of the timing of whether or not to send a control message */
#define BSW_CANNM_Y_u1RESET                  ((BswU1)0x01U)
#define BSW_CANNM_Y_u1WAKEUP_SELF            ((BswU1)0x02U)
#define BSW_CANNM_Y_u1WAKEUP_OTHER           ((BswU1)0x03U)

/* Transition destination state when judging a state transition */
#define BSW_CANNM_Y_u1NEXTST_BUS_SLEEP       ((BswU1)0x00U)   /* Transition to bus-sleep state */
#define BSW_CANNM_Y_u1NEXTST_RPTMSG_SLF      ((BswU1)0x01U)   /* Transition to the repeat message state due to own-node factors */
#define BSW_CANNM_Y_u1NEXTST_RPTMSG_OTR      ((BswU1)0x02U)   /* Transition to the repeat message state due to other-node factors */
#define BSW_CANNM_Y_u1NEXTST_CHDRVWT         ((BswU1)0x03U)   /* Transition to channel drive wait state */
#define BSW_CANNM_Y_u1NEXTST_WAKE_CHECK      ((BswU1)0x04U)   /* Transition to Wake-up check state */

/* Awake factor type occurred by BusSleepMode */
#define BSW_CANNM_Y_u1AWAKEKIND_OTHER        ((BswU1)0x0FU)    /* Bus wake-up due to other-node */
#define BSW_CANNM_Y_u1AWAKEKIND_SELF         ((BswU1)0x1EU)    /* Bus wake-up by own-node */

/* NM message transmission request after updating SleepReadyBit */
#define BSW_CANNM_Y_u1REQSRB_NONE            ((BswU1)0x0FU)    /* No request to transmit NM message after updating SleepReadyBit */
#define BSW_CANNM_Y_u1REQSRB_EXIST           ((BswU1)0x1EU)    /* NM message transmission request exists after updating SleepReadyBit */

/* Request bus synchronization */
#define BSW_CANNM_Y_u1REQSYNC_NONE           ((BswU1)0x0FU)    /* No bus synchronization request */
#define BSW_CANNM_Y_u1REQSYNC_EXIST          ((BswU1)0x1EU)    /* Bus synchronization request exists */

/* ON/OFF of each Bit that configures CBV */
#define BSW_CANNM_Y_u1CBVBIT_OFF             ((BswU1)0x0FU)    /* BitOFF */
#define BSW_CANNM_Y_u1CBVBIT_ON              ((BswU1)0x1EU)    /* BitON */

/* Request for PN coordinated shutdown synchronization */
#define BSW_CANNM_Y_u1REQPNSYNC_NONE         ((BswU1)0x0FU)    /* PN coordinated shutdown synchronization request disabled */
#define BSW_CANNM_Y_u1REQPNSYNC_FAIL         ((BswU1)0x1EU)    /* Failed PN coordinated shutdown synchronization request */
#define BSW_CANNM_Y_u1REQPNSYNC_REQ          ((BswU1)0x2DU)    /* Requesting PN coordinated shutdown synchronization */
#define BSW_CANNM_Y_u1REQPNSYNC_NEEDREQ      ((BswU1)0x3CU)    /* Need PN coordinated shutdown synchronization request */
#define BSW_CANNM_Y_u1REQPNSYNC_EXIST        ((BswU1)0x4BU)    /* PN coordinated shutdown synchronization request enabled */

/* Number of byte in PNC ID */
#define BSW_CANNM_Y_u1PNCID_BYTENUM          ((BswU1)2U)

/* Upper/Lower Byte of PNC ID */
#define BSW_CANNM_Y_u1PNCID_LOWBYTE          ((BswU1)0U)    /* Lower Byte of PNC ID */
#define BSW_CANNM_Y_u1PNCID_HIBYTE           ((BswU1)1U)    /* Lower Byte of PNC ID */

/* Initial value of PNC ID for each channel */
#define BSW_CANNM_Y_u4PNCID_INIT             (0x00000000UL)

/* For bit inversion */
#define BSW_CANNM_Y_u4ALL_BIT                (0xFFFFFFFFUL)

/* Tx wait time none value */
#define BSW_CANNM_Y_u2TXWAIT_NONE            ((BswU2)0U)

/* Flag for CanNm_CbkPreEnableTx is called or not */
#define BSW_CANNM_Y_u1PREENA_NONE            ((BswU1)0x0FU)    /* CanNm_CbkPreEnableTx : not called (call request for wake up) */
#define BSW_CANNM_Y_u1PREENA_DONE            ((BswU1)0x1EU)    /* CanNm_CbkPreEnableTx : called */
#define BSW_CANNM_Y_u1PREENA_WKTO_REQ        ((BswU1)0x2DU)    /* CanNm_CbkPreEnableTx : call request for wake up and TxTimeout */
#define BSW_CANNM_Y_u1PREENA_TXTO_REQ        ((BswU1)0x3CU)    /* CanNm_CbkPreEnableTx : call request for TxTimeout */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Structure for maintaining channel status */
typedef struct
{
    BswU2 u2NmSt;              /* NM status                                           */
    BswU2 u2NmStateTimer;      /* Timer for state transition                               */
                               /* NM_TIMEOUTTIME,NM_WAITBUSSLEEP                   */
    BswU1 u1EdgeEnDtctTimOn;   /* Flag for edge detection permission time measurement availability               */
    BswU1  u1PreEnaTxSts;       /* Flag for CanNm_CbkPreEnableTx is called or not */
    BswU2 u2RptMsgTimer;       /* REPEATMSG state maintenance timer                          */
    BswU1 u1TxRxEvent;         /* Transmit and receive event                                   */
    BswU1 u1BusAwakeSelf;      /* Own-node bus wake-up factor                   */
    BswU1 u1BusAwakeOther;     /* Other-node bus wake-up factor                   */
    BswU1 u1WkupTrigger;       /* Awake factor occurred by BusSleepMode             */
    BswU1 u1ChPower;           /* Channel power on/off                                 */
    BswU1 u1ReqRptSt;          /* Transition flag from NetworkMode to RepeatMessageState  */

    BswU2 u2TxCyclicTimer;     /* Timer for periodic transmission/immediate transmission/transmission offset measurement     */
    BswU1 u1TxConf;            /* NMMessage transmission completetion Yes/No                          */
    BswU1 u1TxCnt;             /* Number of times NMMessage transmission                              */
    BswU1 u1StopTxCnt;         /* Number of transmissions after stopping communication request                         */

    BswU1 u1TxStatus;          /* Flag for control message transmission enable/disable                   */
    BswU2 u2EvSendTimer;       /* Event message transmission enable timer                 */
    BswU2 u2PeriSendTimer;     /* Periodic message transmission enable timer                     */

    BswU2 u2TxTimeoutTimer;    /* Timer for measuring transmission timeout                     */
    BswU1 u1TxTimeoutOn;       /* Flag for enabling/disabling  transmit timeout timer measurement           */

    BswU1 u1PwonWaitTimerOn;   /* Flag for using/not using the sleep wait timer at power-on       */
    BswU2 u2PwonWaitTimer;     /* Sleep wait timer at power-on                       */

    BswU1 u1ReqTransSRB;       /* NM message transmission request after updating SleepReadyBit        */
    BswU1 u1ReqBusSync;        /* Request bus synchronization                                     */
    BswU1 u1ReqPnSyncSt;       /* State of PN coordinated shutdown synchronization request. */
    BswU1 u1DmyPad;            /* Padding for alignment adjustment             */
} Bsw_CanNmY_ChStsType;

/* Structure for defining various configurations */
typedef struct
{
    BswU1 u1NmToutRstrt;       /* Re-measurement of the transmit timeout timer for repeat message state and Normal operation state */
    BswU1 u1TxToutStop;        /* Function to stop the transmission timeout timer when TxConf(E_NOT_OK) is notified */
    BswU1 u1NodeIDPos;         /* Position of the Source Node Identifier */
    BswU1 u1CBVPos;            /* Position of the ControlBitVector */
    BswU1 u1UserDataPos;       /* Location of user data */
    BswU1 u1UserDataLen;       /* Length of user data */
    BswU1 u1ActiveWkUp;        /* Switch active wake-up function */
    BswU1 u1NodeID;            /* Source Node Identifier */
    BswU1 u1UsePnc;            /* Use/not use PNC  */
    BswU1 u1UseChannel;        /* Channel used/not used */
    BswU1 u1UseBusSleep;       /* Bus-sleep used/not used */
    BswU1 u1CheckTxConf;       /* Enables/disables the transmission completion check within the judgment of the control message transmission enable/disable */
    BswU1 u1SleepReadyTrriger; /* Use/not use of transmit interval retrigger by cooperation bus-sleep */
    BswU1 u1RxNoPNMsg;         /* Enable/Disable non-partial NM message receive when using partial network function. */
    BswU1 u1ImmNwReq;          /* Enable/disable immediate transmission when own-node awake occurs. */
    BswU1 u1ToTxStop;          /* Stop transmission due to TxTimeout */
} Bsw_CanNmY_CfgType;

/* Structure for defining various configurations (timer) */
typedef struct
{
    BswU2 u2NMToutTim;       /* NetworkTimeout time */
    BswU2 u2RptMsgTim;       /* Duration to maintain RepeatMessageState */
    BswU2 u2TxToutTim;       /* Transmission timeout time */
    BswU2 u2WaitSlpTim;      /* Sleep transition waiting time */
    BswU2 u2MsgCycTim;       /* Periodic transmission interval */
    BswU2 u2ImmCycTim;       /* Immediate transmission interval */
    BswU2 u2SndStartTim;     /* Transmission start waiting time (SendStart) */
    BswU2 u2DisSndTim;       /* Transmission starting wait time at bus wake-up (DisableSend) */
    BswU2 u2EnaPeriTim;      /* Periodic transmission starting wait time at bus wake-up (EnablePeriodic) */
    BswU2 u2WakeChkTim;      /* External request monitoring time at wake-up */
    BswU2 u2TrcvWaitTim;     /* Transceiver mode transition waiting time */
    BswU2 u2PwOnWkChkTim;    /* Startup check state transition wait time at power-on */
    BswU2 u2HardStpWtTim;    /* Wait time for hardware stop processing */
    BswU2 u2EvDisTim;        /* Event transmission disable time */
    BswU2 u2MsgCycOfs;       /* Periodic transmission delay time */
    BswU2 u2DisSndComTik;    /* Transmission starting wait time at bus wake-up[Com Tick] (DisableSend) */
    BswU2 u2EnaPeriComTik;   /* Periodic transmission starting wait time at bus wake-up[Com Tick] (EnablePeriodic) */
    BswU2 u2MsgCycComTik;    /* Periodic transmission delay time[Com Tick] */
    BswU1 u1ImmNumOfTx;      /* Number of immediate transmissions */
    BswU1 u1StopTxNum;       /* Number of transmissions after stopping communication request */
    BswU1 u1PwOnWtTxTimType; /* Kind of waiting time to start transmission when power is turned ON. */
    BswU1 u1TimCfgDummyPad;  /* Padding for alignment adjustment             */
} Bsw_CanNmY_TimCfgType;

/* Structure for defining various configurations (Function pointer) */
typedef struct
{
    Std_ReturnType  (* BswConst ptGetPnInReqFn)( NetworkHandleType Channel, uint8* PncAwakePtr );            /* Get PNC Awake factors */
    Std_ReturnType  (* BswConst ptSetPnEiraFn)( NetworkHandleType Channel, BswConstR uint8* EiraDataPtr );   /* Set EIRA */
    Std_ReturnType  (* BswConst ptChkRxPnFn)( NetworkHandleType Channel, BswConstR BswU1* ptEiraDataPtr );   /* Set EIRA when receiving NM message */
    void            (* BswConst ptPrDrvStPnFn)( BswU1 u1NetID );                                             /* Processing at driver start state */
} Bsw_CanNmY_FnCfgType;

/* Structure for CBV information */
typedef struct
{
    BswU1 u1SleepReadyBit;     /* NM Coordinator Sleep Ready Bit */
    BswU1 u1ActvWkupBit;       /* Active Wakeup Bit */
} Bsw_CanNmY_CBVType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/* Component internal publication definition */
void            bsw_cannm_y_ctrl_InitCom( void );                                                      /* Initialize the communication restriction function */
BswU1           bsw_cannm_y_ctrl_CheckDisCom( BswU1 u1NetID );                                         /* Judges whether the communication function is enabled or disabled */
Std_ReturnType  bsw_cannm_y_ctrl_ChkRxPn( NetworkHandleType Channel, BswConstR BswU1* ptEiraDataPtr ); /* Set EIRA when receiving NM message */
void            bsw_cannm_y_ctrl_SendFstMsgSlf( BswU1 u1NetID );                                       /* Transmission of the first NM-PDU at the time of communication start by the own-node factor */
void            bsw_cannm_y_ctrl_SendFstMsgOth( BswU1 u1NetID );                                       /* Transmission of the first NM-PDU at start communication with other-node factor */
void            bsw_cannm_y_ctrl_TrnsRptMsgSt( BswU1 u1NetID, Bsw_CanNmY_ChStsType* ptChSt );          /* Transition processing to RepeatMessageState */
void            bsw_cannm_y_ctrl_SetActWkUpBit( BswU1 u1NetID, BswU1 u1ActiveWakeUpBit );              /* Request to set active wake-up bit */
void            bsw_cannm_y_ctrl_JudgeEnTxCom( BswU1 u1NetID );                                        /* Determine permission to transmit a control message */
void            bsw_cannm_y_ctrl_DriveWaitTrcv( BswU1 u1NetID );                                       /* Processing when the driver is in the start state(Processing using transceiver mode transition waiting time) */
void            bsw_cannm_y_ctrl_StartCom( BswU1 u1NetID, BswU1 u1Kind, BswU2* ptDisableSend, BswU2* ptEnablePeriodic );    /* Start measuring the timing of whether or not to send a control message */
void            bsw_cannm_y_ctrl_ProcPwOnDrWt( BswU1 u1NetID, BswU1 u1TRxEvent );                      /* Processing during the channel drive waiting state at power-on */
void            bsw_cannm_y_ctrl_ProcDrWt( BswU1 u1NetID, BswU1 u1TRxEvent );                          /* Processing of channel drive waiting state */
void            bsw_cannm_y_ctrl_ProcWkChk( BswU1 u1NetID, BswU1 u1TRxEvent );                         /* Processing in Wake-up check state */
void            bsw_cannm_y_ctrl_InitPncReqPos( void );                                                /* Initialize PN multi-stage sleep synchronization request */
void            bsw_cannm_y_ctrl_ActionPNSRSt( BswU1 u1NetID, BswU1 u1TRxEvent );                      /* Action on PN coordinated shutdown synchronization request state */
void            bsw_cannm_y_ctrl_StrPncReqPos( BswU1 u1NetID, BswU1* PncReqPosPtr );                   /* Store PN multi-stage sleep synchronization request */
void            bsw_cannm_y_ctrl_SetFinPncReq( BswU1 u1NetID, BswU1* PncReqPosPtr );                   /* Set PNC ID after PN multi-stage sleep synchronization */

/* Component internal publication definition (Dummy function) */
void            bsw_cannm_y_ctrl_InitComNone( void );                                                      /* Initialize the communication restriction function (Dummy function) */
BswU1           bsw_cannm_y_ctrl_ChkComNone( BswU1 u1NetID );                                              /* Judges whether the communication function is enabled or disabled (Dummy function) */
Std_ReturnType  bsw_cannm_y_ctrl_GetPnInRqtNone( NetworkHandleType Channel, uint8* PncAwakePtr );          /* Get PNC Awake factors(Dummy function) */
Std_ReturnType  bsw_cannm_y_ctrl_SetPnEiraNone( NetworkHandleType Channel, BswConstR uint8* EiraDataPtr ); /* Set EIRA(Dummy function) */
Std_ReturnType  bsw_cannm_y_ctrl_ChkRxPnNone( NetworkHandleType Channel, BswConstR BswU1* ptEiraDataPtr ); /* Set EIRA when receiving NM message(Dummy function) */
void            bsw_cannm_y_ctrl_Drive( BswU1 u1NetID );                                                   /* Processing when the driver is in the start state(Dummy function) */
void            bsw_cannm_y_ctrl_ProcPwOnDrWtNn( BswU1 u1NetID, BswU1 u1TRxEvent );                        /* Processing during the channel drive waiting state at power-on(Dummy function) */
void            bsw_cannm_y_ctrl_ProcDrWtNn( BswU1 u1NetID, BswU1 u1TRxEvent );                            /* Processing of channel drive waiting state(Dummy function) */
void            bsw_cannm_y_ctrl_ProcWkChkNn( BswU1 u1NetID, BswU1 u1TRxEvent );                           /* Processing in Wake-up check state(Dummy function) */
void            bsw_cannm_y_ctrl_InitPncReqPosNone( void );                                                /* Initialize PN multi-stage sleep synchronization request(Dummy function) */
void            bsw_cannm_y_ctrl_ActionPNSRStNone( BswU1 u1NetID, BswU1 u1TRxEvent );                      /* Action on PN coordinated shutdown synchronization request state(Dummy function) */
void            bsw_cannm_y_ctrl_StrPncReqPosNone( BswU1 u1NetID, BswU1* PncReqPosPtr );                   /* Store PN multi-stage sleep synchronization request(Dummy function) */
void            bsw_cannm_y_ctrl_SetFinPncReqNone( BswU1 u1NetID, BswU1* PncReqPosPtr );                   /* Set PNC ID after PN multi-stage sleep synchronization(Dummy function) */

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern Bsw_CanNmY_ChStsType      bsw_cannm_y_ctrl_stChSts[];                  /* NM status  */
extern Bsw_CanNmY_CBVType        bsw_cannm_y_ctrl_stTxCBV[];                  /* CBV for transmission */
extern BswU1                     bsw_cannm_y_ctrl_u1DisableCom[];             /* Enable/Disable the communication restriction function */
extern BswU4                     bsw_cannm_y_ctrl_u4PncReqPos[][BSW_CANNM_Y_u1PNCID_BYTENUM];    /* PNC ID for each channel */
extern BswU4                     bsw_cannm_y_ctrl_u4FinPncReqPos[][BSW_CANNM_Y_u1PNCID_BYTENUM]; /* Transmission requested PNC ID */
extern BswU1                     bsw_cannm_y_ctrl_u1TmpSendData[][BSW_CANNM_Y_PDU_DATA_LENGTH]; /* Temporary data area for transmission */
extern BswU1                     bsw_cannm_y_ctrl_u1TmpRecvData[][BSW_CANNM_Y_PDU_DATA_LENGTH]; /* Temporary data area for receiving */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU1            bsw_cannm_y_u1TxData[][BSW_CANNM_Y_PDU_DATA_LENGTH]; /* Transmit data field value table */

extern BswConst Bsw_CanNmY_CfgType      bsw_cannm_y_ctrl_stCfg[];             /* Various configuration definitions */
extern BswConst Bsw_CanNmY_TimCfgType   bsw_cannm_y_ctrl_stTimCfg[];          /* Various configuration definitions(Timer) */
extern BswConst Bsw_CanNmY_FnCfgType    bsw_cannm_y_ctrl_stFnCfg[];           /* Various configuration definitions(Function pointer) */


extern BswConst BswU1            bsw_cannm_y_ctrl_u1ChNum;                    /* Maximum number of channels              */
extern BswConst BswU1            bsw_cannm_y_ctrl_u1ChOffset;                 /* Channel offset          */
extern BswConst BswU1            bsw_cannm_y_ctrl_u1ImmRestart;               /* Immediate transmission function                */
extern BswConst BswU1            bsw_cannm_y_ctrl_u1UStbToutFnc;              /* Processing when transmission timeout occurs in non-normal condition */
extern BswConst BswU1            bsw_cannm_y_ctrl_u1SlpSync;                  /* Multi-stage sleep synchronization function */
extern BswConst BswU1            bsw_cannm_y_ctrl_u1PNSlpSync;                /* PN multi-stage sleep synchronization function */

extern BswConst BswU2            bsw_cannm_y_ctrl_u2MaxSlpTim;                /* State transition timer (10000ms order)      */
extern BswConst BswU2            bsw_cannm_y_ctrl_u2MaxWkChkTim;              /* State transition timer (10000ms order)      */
extern BswConst BswU2            bsw_cannm_y_ctrl_u2MaxStateTim;              /* State transition timer (1000ms order)       */
extern BswConst BswU2            bsw_cannm_y_ctrl_u2MaxTrcvWtTim;             /* State transition timer (100ms order)      */
extern BswConst BswU2            bsw_cannm_y_ctrl_u2MaxToutTim;               /* Maximum value of transmit timeout timer           */
extern BswConst BswU2            bsw_cannm_y_ctrl_u2MaxEvSndTim;              /* Maximum value of control Msg (event) transmission timer */
extern BswConst BswU2            bsw_cannm_y_ctrl_u2MaxPrSndTim;              /* Maximum value of control Msg (periodic) transmission timer     */
extern BswConst BswU2            bsw_cannm_y_ctrl_u2MaxCycTim;                /* Maximum value of periodic transmission timer(NM Frame)       */
extern BswConst BswU2            bsw_cannm_y_ctrl_u2MaxRpMsgTim;              /* Maximum value of REPEATMSG timer                  */
extern BswConst BswU2            bsw_cannm_y_ctrl_u2MaxPwOnWtTim;             /* Maximum value of TPWONWaitBusSleep timer          */

extern void             (* BswConst bsw_cannm_y_ctrl_ptInitComFunc)( void );
extern BswU1            (* BswConst bsw_cannm_y_ctrl_ptChkComFunc)( BswU1 u1NetID );
extern void             (* BswConst bsw_cannm_y_ctrl_ptPwOnChDrWtFn)( BswU1 u1NetID, BswU1 u1TRxEvent );
extern void             (* BswConst bsw_cannm_y_ctrl_ptChDrWtFunc)( BswU1 u1NetID, BswU1 u1TRxEvent );
extern void             (* BswConst bsw_cannm_y_ctrl_ptWakeCheckFn)( BswU1 u1NetID, BswU1 u1TRxEvent );
extern void             (* BswConst bsw_cannm_y_ctrl_ptInitPncReqPosFn)( void );
extern void             (* BswConst bsw_cannm_y_ctrl_ptStrPncReqPosFn)( BswU1 u1NetID, BswU1* PncReqPosPtr );
extern void             (* BswConst bsw_cannm_y_ctrl_ptSetFinPncReqFn)( BswU1 u1NetID, BswU1* PncReqPosPtr );
extern void             (* BswConst bsw_cannm_y_ctrl_ptActPNSRStFn)( BswU1 u1NetID, BswU1 u1TRxEvent );
extern uint16           (* BswConst bsw_cannm_y_ctrl_ptCnvMs2TickFn)( uint16 msTime );

#endif  /* BSW_CANNM_Y_CTRL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v2-0-0          :2022/02/21                                             */
/*  v2-1-0          :2022/08/01                                             */
/*  v3-0-0          :2024/09/13                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
