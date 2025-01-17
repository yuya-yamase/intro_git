/* bsw_cansm_st_h_v2-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANSM/ST/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef BSW_CANSM_ST_H
#define BSW_CANSM_ST_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Driver stop wait timeout time */
#define BSW_CANSM_u1DRVSTOP_TIMEOUT     ((BswU1)3U)

/******************/
/* Unit internal public definition */
/******************/
/* Channel state */
#define BSW_CANSM_u2CH_NOCOM            ((BswU2)0x00FFU) /* No Communication state                                           */
#define BSW_CANSM_u2CH_SILENTCOM        ((BswU2)0x01FEU) /* Silent communication state                                       */
#define BSW_CANSM_u2CH_FULLCOM          ((BswU2)0x02FDU) /* Full communication state                                         */
#define BSW_CANSM_u2CH_PRE_NOCOM_STPCTR ((BswU2)0x03FCU) /* NO Communication transition waiting state (waiting for controller stop transition)         */
#define BSW_CANSM_u2CH_PRE_NOCOM_STBTRC ((BswU2)0x04FBU) /* NO Communication transition waiting state (waiting for transceiver standby transition)   */
#define BSW_CANSM_u2CH_PRE_SILENTCOM    ((BswU2)0x05FAU) /* Silent Communication transition waiting state (transceiver normal transition waiting) */
#define BSW_CANSM_u2CH_PRE_FULLCOM      ((BswU2)0x08F7U) /* Full Communication transition waiting state (transceiver normal transition waiting)   */
#define BSW_CANSM_u2CH_FATAL            ((BswU2)0x06F9U) /* failure state                                                       */
#define BSW_CANSM_u2CH_UNINIT           ((BswU2)0x07F8U) /* Uninitialized                                                       */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/******************/
/* Unit internal public definition */
/******************/
/* Structure for maintaining channel status */
typedef struct
{
    BswU2 u2CurrentChState;       /* Channel state                 */
    BswU1 u1CanStTransTime;       /* CAN state transition waiting time          */
    BswU1 u1Extend;               /* For future extension                   */
} Bsw_CanSM_ChStsType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/************************/
/* Component internal publication definition */
/************************/
void  bsw_cansm_st_DetectChFail(BswU1 u1ChId, BswU1 u1Busoff);
void  bsw_cansm_st_ReleaseChFail(BswU1 u1ChId);
void  bsw_cansm_st_DetectNmTxTout(BswU1 u1ChId, BswU2 u2Fail);
void  bsw_cansm_st_DetectNmTxToutNone(BswU1 u1ChId, BswU2 u2Fail);
void  bsw_cansm_st_RestoreCtrlMode(BswU1 u1ChId);

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
/******************/
/* Unit internal public definition */
/******************/
extern Bsw_CanSM_ChStsType bsw_cansm_st_stChSts[];

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/************************/
/* Component internal publication definition */
/************************/
extern BswConst BswU1      bsw_cansm_st_u1ChNum;
extern BswConst BswU1      bsw_cansm_st_u1ChOffset;
extern BswConst BswU1      bsw_cansm_st_u1TrcvWaitTime[];
extern BswConst BswU1      bsw_cansm_st_u1MaxWaitTime;

extern void (* BswConst bsw_cansm_st_ptDetectNmTxToutFn)(BswU1 u1ChId, BswU2 u2Fail);

#endif /* BSW_CANSM_ST_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/04/19                                             */
/*  v1-1-0          :2018/09/20                                             */
/*  v2-0-0          :2021/12/02                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
