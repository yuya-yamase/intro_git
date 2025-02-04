/* bsw_cannm_a_timer_h_v3-0-0                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/CANNM/A/TIMER/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef BSW_CANNM_A_TIMER_H
#define BSW_CANNM_A_TIMER_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_CANNM_A_TIMER_NONE             (0U)     /* Timer unset        */
/* CVT-NM TIMER */
#define BSW_CANNM_A_TIMER_CVT_TPONW        (1U)     /* Wait for initial start                                 */
#define BSW_CANNM_A_TIMER_CVT_TAWAKE       (2U)     /* AWAKE Holding waiting                                */
#define BSW_CANNM_A_TIMER_CVT_TPONS        (3U)     /* Waiting for bus sleep after reset                   */
#define BSW_CANNM_A_TIMER_CVT_TNWUW        (4U)     /* Awake wait timer before bus-sleep         */
#define BSW_CANNM_A_TIMER_CVT_TWUW         (5U)     /* Waiting for start after bus wake-up                 */
#define BSW_CANNM_A_TIMER_CVT_TWUW00       (6U)     /* No waiting for start after bus wake-up             */
#define BSW_CANNM_A_TIMER_CVT_TNONEDGE     (7U)     /* Monitoring of transmitting and receiving failures in the network and monitoring of NM state of other nodes         */
#define BSW_CANNM_A_TIMER_CVT_TNRMEDGE     (8U)     /* Waiting for edge detection to start during bus-sleep transition (normal) */
#define BSW_CANNM_A_TIMER_CVT_TENPRD       (9U)     /* Waiting for periodic transmission messages to be enabled for transmission               */
#define BSW_CANNM_A_TIMER_CVT_TENPRDIMM    (10U)    /* Waiting for periodic transmission messages to be enabled for transmission(At immediate WKUP)   */

#define BSW_CANNM_A_TIMER_CENTER           (11U)    /* Timer number threshold      */
/* OSEK-NM TIMER */
#define BSW_CANNM_A_TIMER_OSEK_TTYP        (11U)    /* Ring transmission interval - TTyp                */
#define BSW_CANNM_A_TIMER_OSEK_TMAX        (12U)    /* Ring Enabling Interval - TMax                */
#define BSW_CANNM_A_TIMER_OSEK_TERROR      (13U)    /* LimpHome transmission interval   Terror              */
#define BSW_CANNM_A_TIMER_OSEK_TWBS        (14U)    /* Wait for BUSSLEEP state transition NORM TWbs                */
#define BSW_CANNM_A_TIMER_OSEK_TERRWBS     (15U)    /* Wait for BUSSLEEP state transition LMP  TErrWbs             */
#define BSW_CANNM_A_TIMER_LIMITIDX         (16U)    /* Upper limit of timer number                             */

#define BSW_CANNM_A_TIMER_RUNAW_NONE       (0xe1U)  /* AWAKE holding state:None */
#define BSW_CANNM_A_TIMER_RUNAW_EXIST      (0xd2U)  /* AWAKE holding state:Exist */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
void   bsw_cannm_a_timer_InitAll(void);
void   bsw_cannm_a_timer_InitChMod(BswU1 u1NetID, BswU1 u1ModKind);
void   bsw_cannm_a_timer_Count(void);
BswU1  bsw_cannm_a_timer_GetTout(BswU1 u1NetID, BswU1 u1ModKind);
BswU1  bsw_cannm_a_timer_GetRunAwake(BswU1 u1NetID);
void   bsw_cannm_a_timer_Start(BswU1 u1NetID, BswU1 u1TimerNo);
void   bsw_cannm_a_timer_ResetStart(BswU1 u1NetID, BswU1 u1TimerNo);
void   bsw_cannm_a_timer_Stop(BswU1 u1NetID, BswU1 u1TimerNo);
BswU1  bsw_cannm_a_timer_Check(BswU1 u1NetID, BswU1 u1TimerNo);
void   bsw_cannm_a_timer_CheckRam(BswU1 u1NetID);


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* BSW_CANNM_A_TIMER_H */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v1-0-0          :2017/03/16                                             */
/*  v2-0-0          :2021/12/03                                             */
/*  v3-0-0          :2024/08/30                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
