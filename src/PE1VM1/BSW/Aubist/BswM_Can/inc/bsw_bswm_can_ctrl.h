/* bsw_bswm_can_ctrl_h_v3-0-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CAN/CTRL/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef     BSW_BSWM_CAN_CTRL_H
#define     BSW_BSWM_CAN_CTRL_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_BSWM_CAN_u4ALLBIT                ((BswU4)0xFFFFFFFFUL)

#define BSW_BSWM_CAN_u1VERIFY_KEY_B8         ((BswU1)0xFFU)

#define BSW_BSWM_CAN_u1INIT_DONE             ((BswU1)0x4BU)      /* Driver initialization state:Complete initialization   */
#define BSW_BSWM_CAN_u1INIT_INITING          ((BswU1)0x2DU)      /* Driver initialization state:Initializing     */
#define BSW_BSWM_CAN_u1INIT_PREINIT          ((BswU1)0x1EU)      /* Driver initialization state:Before initialization     */

#define BSW_BSWM_CAN_u1CHINIT_DONE           ((BswU1)0x4BU)      /* CH initialization state:Complete initialization                          */
#define BSW_BSWM_CAN_u1CHINIT_REGCHK         ((BswU1)0x2DU)      /* CH initialization state:Uninitialized (Check for register sticking) */
#define BSW_BSWM_CAN_u1CHINIT_DRVINT         ((BswU1)0x1EU)      /* CH initialization state:Uninitialized(Only controller initialization)  */

#define BSW_BSWM_CAN_u1FAILST_NONE           ((BswU1)0x00U)      /* Fail status:No fail                    */
#define BSW_BSWM_CAN_u1FAILST_INITNG         ((BswU1)0x01U)      /* Fail status:Initialization error       */
#define BSW_BSWM_CAN_u1FAILST_REGCHECK       ((BswU1)0x02U)      /* Fail status:Stuck Register             */
#define BSW_BSWM_CAN_u1FAILST_UNUSRGCHK      ((BswU1)0x03U)      /* Fail status:Stuck Register(Unused MBox)*/
#define BSW_BSWM_CAN_u1FAILST_INVALID        ((BswU1)0x04U)      /* Fail status:invalid                    */

#define BSW_BSWM_CAN_u1BUSWAKEUP_ON          ((BswU1)0x0FU)      /* Bus wake-up is complete                   */
#define BSW_BSWM_CAN_u1BUSWAKEUP_OFF         ((BswU1)0x1EU)      /* Before bus wake-up                     */

#define BSW_BSWM_CAN_u1CHFAIL_ON             ((BswU1)0x0FU)      /* Channel fail occurred                     */
#define BSW_BSWM_CAN_u1CHFAIL_OFF            ((BswU1)0x1EU)      /* Channel fail not occurred                   */

#define BSW_BSWM_CAN_u1REQ_EXIST             ((BswU1)0x0FU)      /* Communication restriction:Request exists   */
#define BSW_BSWM_CAN_u1REQ_NONE              ((BswU1)0x1EU)      /* Communication restriction:No request   */

#define BSW_BSWM_CAN_u1CHRST_EXIST           ((BswU1)0x0FU)      /* Channel restart flag:Accepting   */
#define BSW_BSWM_CAN_u1CHRST_NONE            ((BswU1)0x1EU)      /* Channel restart flag:Not accepted   */

#define BSW_BSWM_CAN_u1DMREQ_EXIST           ((BswU1)0x0FU)      /* Receive disconnection monitoring flag:Stopped   */
#define BSW_BSWM_CAN_u1DMREQ_NONE            ((BswU1)0x1EU)      /* Receive disconnection monitoring flag:Normal operation   */

#define BSW_BSWM_CAN_u1PERIRST_NONE          ((BswU1)0x01U)      /* Periodic tx reset factor:Reset none */
#define BSW_BSWM_CAN_u1PERIRST_BUSWKUP       ((BswU1)0x02U)      /* Periodic tx reset factor:Bus Wakeup */
#define BSW_BSWM_CAN_u1PERIRST_RESUMETX      ((BswU1)0x03U)      /* Periodic tx reset factor:Resume Tx  */

#define BSW_BSWM_CAN_u1INDEX_0               ((BswU1)0U)         /* Array element 0 */
#define BSW_BSWM_CAN_u1INDEX_1               ((BswU1)1U)         /* Array element 1 */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Channel state */
typedef struct
{
    BswU1        u1BusWkup;                             /* Bus wake-up flag   */
    BswU1        u1ChFail;                              /* Channel fail exists/no       */
    BswU1        u1ChInitStat;                          /* Driver initialization state         */
    BswU1        u1ChInitResult;                        /* Driver initialization result         */
    BswU1        u1ChInitResultMrr;                     /* Driver initialization result (Mirror)   */
    BswU1        u1Dmy;
} Bsw_BswMCan_ChStatType;

/* ----Unit internal public definition ---- */
/* Transmission stop/resume state */
typedef struct
{
    BswU1        u1StopReq;                              /* Exist/none of stop request               */
    BswU1        u1TxCtrlStat;                           /* Transmission control state               */
    BswU2        u2TxWaitTimer;                          /* Restart wait timer             */
} Bsw_BswMCan_TxCtrlType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void  bsw_bswm_can_ctrl_Init( void );
void  bsw_bswm_can_ctrl_Wakeup( void );
void  bsw_bswm_can_ctrl_ResetInit( void );
void  bsw_bswm_can_ctrl_EdgeInit( void );
void  bsw_bswm_can_ctrl_EdgeDeInit( void );
void  bsw_bswm_can_ctrl_EdgeWakeup( void );
void  bsw_bswm_can_ctrl_EdgeSleep( void );
void  bsw_bswm_can_ctrl_RestartChReq( void );
void  bsw_bswm_can_ctrl_Reset( void );

/* ----Unit internal public definition ---- */
void  bsw_bswm_can_ctrl_InitTxCtrl( void );
void  bsw_bswm_can_ctrl_IntTxCtrlNone( void );
BswU1 bsw_bswm_can_ctrl_UpdateTxCtrl( BswU1 u1Channel, BswU1 u1PeriReset );
BswU1 bsw_bswm_can_ctrl_UpdTxCtrlNone( BswU1 u1Channel, BswU1 u1PeriReset );
void  bsw_bswm_can_ctrl_SetTxStat( BswU1 u1Channel, BswU1 u1TxStatus, BswU1 u1PeriReset );
void  bsw_bswm_can_ctrl_InitRstCh( void );
void  bsw_bswm_can_ctrl_InitDMCtrl( void );
void  bsw_bswm_can_ctrl_InitRstChNone( void );
void  bsw_bswm_can_ctrl_IntDMCtrlNone( void );
void  bsw_bswm_can_ctrl_UpdDmCtrlNone( BswU1 u1Channel, BswU4* u4DmGroup );
void  bsw_bswm_can_ctrl_UpdateDmCtrl( BswU1 u1Channel, BswU4* u4DmGroup );
void  bsw_bswm_can_ctrl_CntTimTxCtrl( BswU1 u1Channel );
void  bsw_bswm_can_ctrl_CtTmTxCtrNone( BswU1 u1Channel );
void  bsw_bswm_can_ctrl_TpEnTxNone( NetworkHandleType Network );
void  bsw_bswm_can_ctrl_TpDisTxNone( NetworkHandleType Network );

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern Bsw_BswMCan_ChStatType   bsw_bswm_can_ctrl_stChStat[];

/* ----Unit internal public definition ---- */
extern BswU1                    bsw_bswm_can_ctrl_u1InitDrvSts;
extern Bsw_BswMCan_TxCtrlType   bsw_bswm_can_ctrl_stTxStat[];
extern BswU1                    bsw_bswm_can_ctrl_u1ChRstReq[];
extern BswU1                    bsw_bswm_can_ctrl_u1DmReq[];

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU1 bsw_bswm_can_ctrl_u1ChNum;

/* ----Unit internal public definition ---- */
extern void (* BswConst bsw_bswm_can_ctrl_ptIntTxCtrFnc)( void );
extern BswU1 (* BswConst bsw_bswm_can_ctrl_ptUpdTxCtrFnc)( BswU1 u1Channel, BswU1 u1PeriReset );
extern void (* BswConst bsw_bswm_can_ctrl_ptCntTmTxFnc)( BswU1 u1Channel );
extern void (* BswConst bsw_bswm_can_ctrl_ptIntRstChFnc)( void );
extern void (* BswConst bsw_bswm_can_ctrl_ptIntDmCtrFnc)( void );
extern void (* BswConst bsw_bswm_can_ctrl_ptUpdDmCtrFnc)( BswU1 u1Channel, BswU4* u4DmGroup );
extern void (* BswConst bsw_bswm_can_ctrl_ptTPEnTxFunc)( NetworkHandleType Network );
extern void (* BswConst bsw_bswm_can_ctrl_ptTPDisTxFunc)( NetworkHandleType Network );
extern BswConst BswU1 bsw_bswm_can_ctrl_u1ChOffset;
extern BswConst BswU1 bsw_bswm_can_ctrl_u1RegChk;
extern BswConst BswU1 bsw_bswm_can_ctrl_u1WpRgCkStart;
extern BswConst BswU1 bsw_bswm_can_ctrl_u1DMPeriodTbl[];
extern BswConst BswU1 bsw_bswm_can_ctrl_u1DMCoAwkTbl[];
extern BswConst BswU1 bsw_bswm_can_ctrl_u1BsSlpUseTbl[];

#endif  /* BSW_BSWM_CAN_CTRL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/04/28                                             */
/*  v1-1-0          :2018/11/19                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v2-1-0          :2022/05/24                                             */
/*  v3-0-0          :2024/11/13                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
