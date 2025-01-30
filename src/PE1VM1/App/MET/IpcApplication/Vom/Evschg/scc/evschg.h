/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Eelectric Vehicle System Charging                                                                                                */
/*===================================================================================================================================*/

#ifndef EVSCHG_H
#define EVSCHG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define EVSCHG_H_MAJOR                      (1)
#define EVSCHG_H_MINOR                      (0)
#define EVSCHG_H_PATCH                      (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define EVSCHG_ID_RX_NUM                    (45U)
/* TIMCHG-CSTD-2 */
#define EVSCHG_ID_P_NCTYP                   ( 0U)
#define EVSCHG_ID_P_NCWKD                   ( 1U)
#define EVSCHG_ID_P_NCSTM                   ( 2U)
#define EVSCHG_ID_P_NCFTM                   ( 3U)
#define EVSCHG_ID_P_ADDDSP                  ( 4U)
#define EVSCHG_ID_PCNOWDSP                  ( 5U)
#define EVSCHG_ID_P_NCDSP                   ( 6U)
#define EVSCHG_ID_P_TMPID                   ( 7U)
#define EVSCHG_ID_P_TMPTYP                  ( 8U)
#define EVSCHG_ID_P_TMPACD                  ( 9U)
#define EVSCHG_ID_P_TMPACN                  (10U)
#define EVSCHG_ID_P_TMPSTM                  (11U)
#define EVSCHG_ID_P_TMPFTM                  (12U)
#define EVSCHG_ID_P_TMPSWK                  (13U)
#define EVSCHG_ID_P_TMPNWK                  (14U)
#define EVSCHG_ID_PARK_S                    (15U)
/* SWQUICHA-CSTD-2 */
#define EVSCHG_ID_P_CURDSP                  (16U)
#define EVSCHG_ID_P_CUR200                  (17U)
#define EVSCHG_ID_P_CURSEL                  (18U)
#define EVSCHG_ID_CBLC_AVA                  (19U)
#define EVSCHG_ID_CBLOCKSU                  (20U)
#define EVSCHG_ID_P_LMTDSP                  (21U)
#define EVSCHG_ID_P_CURAVA                  (22U)
#define EVSCHG_ID_P_CLCAVA                  (23U)
#define EVSCHG_ID_P_LMTAVA                  (24U)
#define EVSCHG_ID_P_LMTNOW                  (25U)
#define EVSCHG_ID_P_LMTSEL                  (26U)
#define EVSCHG_ID_P_DPWAVA                  (27U)
#define EVSCHG_ID_P_DPW                     (28U)
#define EVSCHG_ID_P_DPWSL0                  (29U)
#define EVSCHG_ID_P_DPWSL1                  (30U)
#define EVSCHG_ID_P_DPWSL2                  (31U)
#define EVSCHG_ID_P_DPWSL3                  (32U)
#define EVSCHG_ID_P_DPWSL4                  (33U)
#define EVSCHG_ID_P_DPWSL5                  (34U)
#define EVSCHG_ID_P_DPWSL6                  (35U)
#define EVSCHG_ID_P_DPWSL7                  (36U)
#define EVSCHG_ID_P_DPWSL8                  (37U)
#define EVSCHG_ID_P_DPWSL9                  (38U)
#define EVSCHG_ID_P_TMRAVA                  (39U)
#define EVSCHG_ID_P_SLMAVA                  (40U)
#define EVSCHG_ID_P_CURSL1                  (41U)
#define EVSCHG_ID_P_CURSL2                  (42U)
#define EVSCHG_ID_P_CURSL3                  (43U)
#define EVSCHG_ID_P_CURSL4                  (44U)

/* TIMCHG-CSTD : Schedule Information */
#define EVSCHG_TIMCHG_SCHDINFO_SIZE         (16U)

#define EVSCHG_ID_TX_NUM                    (3U)

#define EVSCHG_ID_M_SETACN                  (0U)
#define EVSCHG_ID_M_SETSTM                  (1U)
#define EVSCHG_ID_M_SETFTM                  (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1 u1_id;                                                                   /* Signal Data : P_SETID                             */
    U1 u1_onoff;                                                                /* Signal Data : P_SETON                             */
    U1 u1_type;                                                                 /* Signal Data : P_SETTYP                            */
    U2 u2_start_tim;                                                            /* Signal Data : P_SETSTM                            */
    U2 u2_finish_tim;                                                           /* Signal Data : P_SETFTM                            */
    U1 u1_wkd_bit;                                                              /* Signal Data : P_SETWKD                            */
    U1 u1_nxt_id;                                                               /* Signal Data : P_SETNXT                            */
}ST_EVSCHG_TMCHG_SCHDINFO;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void                        vd_g_EvschgBonInit(void);
void                        vd_g_EvschgRstwkInit(void);
void                        vd_g_EvschgMainTask(void);
U2                          u2_g_EvschgGetSignal(const U1 u1_a_EVSCHG_ID_RX);
ST_EVSCHG_TMCHG_SCHDINFO    st_g_EvschgGetSchdInfo(const U1 u1_a_SCHDINFO_ID);

void                        vd_g_Evschg10msTask(void);
void                        vd_g_EvschgSendSignal(const U1 u1_a_ID, const U2 u2_a_RXDATA);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* EVSCHG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  evschg.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
