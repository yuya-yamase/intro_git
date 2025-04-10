/* bsw_bswm_cs_ctrl_h_v3-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/CS/CTRL/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef     BSW_BSWM_CS_CTRL_H
#define     BSW_BSWM_CS_CTRL_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_BSWM_CS_u2TIME_STOP            ((BswU2)0U)
#define BSW_BSWM_CS_u2IMM_COUNT            ((BswU2)1U)

#define BSW_BSWM_CS_u2COMPID_INVALID       ((BswU2)0xFFFFU)

/* Change in channel power supply */
#define BSW_BSWM_CS_u1CHPWCHG_OFF           ((BswU1)0x0FU) /* No change(OFF) */
#define BSW_BSWM_CS_u1CHPWCHG_ON            ((BswU1)0x1EU) /* No change(NO)  */
#define BSW_BSWM_CS_u1CHPWCHG_TOOFF         ((BswU1)0x2DU) /* Change(OFF) */
#define BSW_BSWM_CS_u1CHPWCHG_TOON          ((BswU1)0x3CU) /* Change(ON)  */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Structure for transmission limitation function protocol switching */
typedef struct
{
    Bsw_BswM_CS_RetCtrlType (*StopTxPdu)( NetworkHandleType Network );       /* Request to stop transmission */
    Bsw_BswM_CS_RetCtrlType (*ResumeTxPdu)( NetworkHandleType Network );     /* Request to resume transmission */
} Bsw_BswmCS_BusTxFuncTblType;

/* Structure for receiver disconnection restriction function protocol switching */
typedef struct
{
    Bsw_BswM_CS_RetCtrlType (*StopDMCtrl)( NetworkHandleType Network );     /* Request to stop receiving disconnection monitoring */
    Bsw_BswM_CS_RetCtrlType (*ResumeDMCtrl)( NetworkHandleType Network );   /* Request to resume receiving disconnection monitoring */
} Bsw_BswmCS_BusDmFuncTblType;

/* Structure for managing event-transmission PDUs */
typedef struct
{
    BswU2 u2Rp;
    BswU2 u2Wp;
    BswU2 u2Num;
} Bsw_BswMCS_EvPduType;

/* Structure of channel power state management */
typedef struct
{
    BswU1 u1LastStatus;
    BswU1 u1Status;
} Bsw_BswMCS_ChPowerType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void bsw_bswm_cs_ctrl_Init( void );
void bsw_bswm_cs_ctrl_ChkEvWkupRam( void );
void bsw_bswm_cs_ctrl_CntEvtAwTimer( void );
void bsw_bswm_cs_ctrl_CntEvtTxDlyTmr( void );
BswU1 bsw_bswm_cs_ctrl_GetTxChCan( BswU2 u2CompId, PduIdType u2PduId );
BswU1 bsw_bswm_cs_ctrl_GetRxChCan( BswU2 u2CompId, PduIdType u2PduId );
void bsw_bswm_cs_ctrl_UpdateChPwStat( void );
BswU1 bsw_bswm_cs_ctrl_GetChPwChange( NetworkHandleType Network );

/* ----Unit internal public definition ---- */
void bsw_bswm_cs_ctrl_Init_EvtAwake( void );
void bsw_bswm_cs_ctrl_Init_WkupEvt( void );
void bsw_bswm_cs_ctrl_EvtWkupClear(  NetworkHandleType Network );
void bsw_bswm_cs_ctrl_InitChPwStat( void );

/* Dummy function for protocol switching */
Bsw_BswM_CS_RetCtrlType bsw_bswm_cs_ctrl_StopTxPdu_dmy( NetworkHandleType Network );
Bsw_BswM_CS_RetCtrlType bsw_bswm_cs_ctrl_RsmTxPdu_dmy( NetworkHandleType Network );
void bsw_bswm_cs_ctrl_RestartCh_dmy( NetworkHandleType Network );
Bsw_BswM_CS_RetCtrlType bsw_bswm_cs_ctrl_StopDMCtrl_dmy( NetworkHandleType Network );
Bsw_BswM_CS_RetCtrlType bsw_bswm_cs_ctrl_RsmDMCtrl_dmy( NetworkHandleType Network );
BswU1 bsw_bswm_cs_ctrl_GetTxChCan_dmy( BswU2 u2CompId, PduIdType u2PduId );
BswU1 bsw_bswm_cs_ctrl_GetRxChCan_dmy( BswU2 u2CompId, PduIdType u2PduId );


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
extern BswU2                  bsw_bswm_cs_ctrl_u2EvAwakeTimer[];
extern BswU2                  bsw_bswm_cs_ctrl_u2EvTxDlyTimer[];
extern Bsw_BswMCS_EvPduType   bsw_bswm_cs_ctrl_stEvPduIndex[];
extern BswU1                  bsw_bswm_cs_ctrl_u1TRXStatus[];
extern Bsw_BswMCS_ChPowerType bsw_bswm_cs_ctrl_stChPw[];

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
extern BswConst BswU1       bsw_bswm_cs_ctrl_u1ChNum;

extern BswConst BswU1       bsw_bswm_cs_ctrl_u1TxCtrlType[];
extern BswConst BswU2       bsw_bswm_cs_ctrl_u2EvAwakeTime[];

extern BswConst BswU1       bsw_bswm_cs_ctrl_u1ChToIdxTbl[];
extern BswConst Bsw_BswmCS_BusTxFuncTblType* BswConst bsw_bswm_cs_ctrl_ptBusTxFuncTbl[];
extern void (* BswConst bsw_bswm_cs_ptBusChRstFuncTbl[])( NetworkHandleType Network );
extern BswConst Bsw_BswmCS_BusDmFuncTblType* BswConst bsw_bswm_cs_ctrl_ptBusDmFuncTbl[];

extern BswConst   BswU2     bsw_bswm_cs_ctrl_u2EvPduNum[];
extern PduIdType* BswConst  bsw_bswm_cs_ctrl_ptEvPduQue[];
extern BswConst   BswU1     bsw_bswm_cs_ctrl_u1PduTxCtrlUse[];

extern uint16 (* BswConst bsw_bswm_cs_ctrl_ptCnvMsTkRpFnc)( uint16 msTime );
extern BswU1 (* BswConst bsw_bswm_cs_ctrl_ptGetChCanFnc)( BswU2 u2CompId, PduIdType u2PduId );
extern BswU1 (* BswConst bsw_bswm_cs_ctrl_ptGetRxChCanFn)( BswU2 u2CompId, PduIdType u2PduId );

#endif  /* BSW_BSWM_CS_CTRL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/06/16                                             */
/*  v1-1-0          :2018/09/12                                             */
/*  v1-2-0          :2020/04/15                                             */
/*  v2-0-0          :2021/12/02                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
