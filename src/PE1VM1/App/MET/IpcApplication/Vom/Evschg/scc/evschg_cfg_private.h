/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Eelectric Vehicle System Charging                                                                                                */
/*===================================================================================================================================*/

#ifndef EVSCHG_CFG_H
#define EVSCHG_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define EVSCHG_CFG_H_MAJOR                  (1)
#define EVSCHG_CFG_H_MINOR                  (0)
#define EVSCHG_CFG_H_PATCH                  (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif

#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif

#include "evschg.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define EVSCHG_STSBIT_VALID                 (0x00U)
#define EVSCHG_STSBIT_UNKNOWN               (0x01U)
#define EVSCHG_STSBIT_INVALID               (0x02U)

#define EVSCHG_RIMSIZE_U1                   (0U)
#define EVSCHG_RIMSIZE_U2                   (1U)

#define EVSCHG_TOUT_INIT                    (0U)
#define EVSCHG_TOUT_BHOLD                   (1U)
#define EVSCHG_TOUT_SP                      (2U)

/* TIMCHG-CSTD */
#define EVSCHG_P_NCTYP_INIT                 (  0x00U)
#define EVSCHG_P_NCWKD_INIT                 (  0x00U)
#define EVSCHG_P_NCSTM_INIT                 (0x01FFU)
#define EVSCHG_P_NCFTM_INIT                 (0x01FFU)
#define EVSCHG_P_ADDDSP_INIT                (  0x00U)
#define EVSCHG_PCNOWDSP_INIT                (  0x00U)
#define EVSCHG_P_NCDSP_INIT                 (  0x00U)
#define EVSCHG_P_TMPID_INIT                 (  0x3FU)
#define EVSCHG_P_TMPTYP_INIT                (  0x00U)
#define EVSCHG_P_TMPACD_INIT                (  0x00U)
#define EVSCHG_P_TMPACN_INIT                (  0x00U)
#define EVSCHG_P_TMPSTM_INIT                (0x01FFU)
#define EVSCHG_P_TMPFTM_INIT                (0x01FFU)
#define EVSCHG_P_TMPSWK_INIT                (  0x00U)
#define EVSCHG_P_TMPNWK_INIT                (  0x00U)
#define EVSCHG_PARK_S_INIT                  (  0x00U)

/* SWQUICHA-CSTD */
#define EVSCHG_P_CURDSP_INIT                (  0x00U)
#define EVSCHG_P_CUR200_INIT                (  0x00U)
#define EVSCHG_P_CURSEL_INIT                (  0x00U)
#define EVSCHG_CBLC_AVA_INIT                (  0x00U)
#define EVSCHG_CBLOCKSU_INIT                (  0x00U)
#define EVSCHG_P_LMTDSP_INIT                (  0x00U)
#define EVSCHG_P_CURAVA_INIT                (  0x00U)
#define EVSCHG_P_CLCAVA_INIT                (  0x00U)
#define EVSCHG_P_LMTAVA_INIT                (  0x00U)
#define EVSCHG_P_LMTNOW_INIT                (  0x00U)
#define EVSCHG_P_LMTSEL_INIT                (  0x00U)
#define EVSCHG_P_DPWAVA_INIT                (  0x00U)
#define EVSCHG_P_DPW_INIT                   (  0x00U)
#define EVSCHG_P_DPWSL0_INIT                (  0x00U)
#define EVSCHG_P_DPWSL1_INIT                (  0x00U)
#define EVSCHG_P_DPWSL2_INIT                (  0x00U)
#define EVSCHG_P_DPWSL3_INIT                (  0x00U)
#define EVSCHG_P_DPWSL4_INIT                (  0x00U)
#define EVSCHG_P_DPWSL5_INIT                (  0x00U)
#define EVSCHG_P_DPWSL6_INIT                (  0x00U)
#define EVSCHG_P_DPWSL7_INIT                (  0x00U)
#define EVSCHG_P_DPWSL8_INIT                (  0x00U)
#define EVSCHG_P_DPWSL9_INIT                (  0x00U)
#define EVSCHG_P_TMRAVA_INIT                (  0x00U)
#define EVSCHG_P_SLMAVA_INIT                (  0x00U)
#define EVSCHG_P_CURSL1_INIT                (  0x00U)
#define EVSCHG_P_CURSL2_INIT                (  0x00U)
#define EVSCHG_P_CURSL3_INIT                (  0x00U)
#define EVSCHG_P_CURSL4_INIT                (  0x00U)

#define EVSCHG_TIMCHG_SCHDSGNL_NUM          (7U)
#define EVSCHG_ID_P_SETID                   (0U)
#define EVSCHG_ID_P_SETON                   (1U)
#define EVSCHG_ID_P_SETTYP                  (2U)
#define EVSCHG_ID_P_SETSTM                  (3U)
#define EVSCHG_ID_P_SETFTM                  (4U)
#define EVSCHG_ID_P_SETWKD                  (5U)
#define EVSCHG_ID_P_SETNXT                  (6U)

#define EVSCHG_P_SETID_INIT                 (  0x00U)
#define EVSCHG_P_SETON_INIT                 (  0x00U)
#define EVSCHG_P_SETTYP_INIT                (  0x00U)
#define EVSCHG_P_SETSTM_INIT                (0x01FFU)
#define EVSCHG_P_SETFTM_INIT                (0x01FFU)
#define EVSCHG_P_SETWKD_INIT                (  0x00U)
#define EVSCHG_P_SETNXT_INIT                (  0x3FU)

/* Send Data */
#define EVSCHG_M_SETSTS_INIT                (  0x00U)
#define EVSCHG_M_SETID_INIT                 (  0x3FU)
#define EVSCHG_M_SETTYP_INIT                (  0x00U)
#define EVSCHG_M_SETWKD_INIT                (  0x00U)
#define EVSCHG_M_SETACN_INIT                (  0x00U)
#define EVSCHG_M_SETSTM_INIT                (0x01FFU)
#define EVSCHG_M_SETFTM_INIT                (0x01FFU)
#define EVSCHG_M_SETNXT_INIT                (  0x00U)

#define EVSCHG_M_CUR200_INIT                (  0x07U)
#define EVSCHG_CLOCK_SU_INIT                (  0x00U)
#define EVSCHG_M_LMTSEL_INIT                (  0x03U)
#define EVSCHG_M_LMTREQ_INIT                (  0x07U)
#define EVSCHG_M_DPWREQ_INIT                (  0x0FU)

#define EVSCHG_M_PNCSW_INIT                 (  0x00U)

/* Senddate MAX */
#define EVSCHG_M_SETACN_MAX                 (  0x02U)
#define EVSCHG_M_SETSTM_MAX                 (0x011FU)                               /*  M_SETSTM MAX 23:55 = 0x011f(287d)            */
#define EVSCHG_M_SETFTM_MAX                 (0x011FU)                               /*  M_SETFTM MAX 23:55 = 0x011f(287d)            */

#define EVSCHG_HOLD_TIME                    (15U)                                   /* 150ms(Tx Hold time)  /  10ms(Evcom 10msTask)  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define vd_g_Evschg_RimU1Write(id, data)    (vd_g_Rim_WriteU1((id), (data)))
#define vd_g_Evschg_RimU2Write(id, data)    (vd_g_Rim_WriteU2((id), (data)))

#define u1_g_Evschg_RimU1Read(id, data)     (u1_g_Rim_ReadU1withStatus((id), (data)))
#define u1_g_Evschg_RimU2Read(id, data)     (u1_g_Rim_ReadU2withStatus((id), (data)))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1                          u1_rimsize;
    U2                          u2_memoryid;
    U1                          u1_on_tout;
} ST_EVSCHG_RX;

typedef struct {
    U1                          u1_sts;
    U2                          u2_sig;
} ST_EVSCHG_SGNL;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void                    vd_g_EvschgCfgBonInit(void);
void                    vd_g_EvschgCfgBonTxInit(void);
void                    vd_g_EvschgCfgRstwkInit(void);
void                    vd_g_EvschgCfgMainTask(void);
void                    vd_g_EvschgCfgSgnlInst(ST_EVSCHG_SGNL * st_ap_sig, ST_EVSCHG_SGNL * st_ap_schd_sig);
U2                      u2_g_EvschgCfgToutSp(U4 u4_a_ID, U2 u2_a_sig);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern  const   ST_EVSCHG_RX        st_gp_EVSCHG_RX_CFG[];
extern  const   U2                  u2_gp_EVSCHG_RIMID_P_SETID[];
extern  const   U2                  u2_gp_EVSCHG_RIMID_P_SETON[];
extern  const   U2                  u2_gp_EVSCHG_RIMID_P_SETTYP[];
extern  const   U2                  u2_gp_EVSCHG_RIMID_P_SETSTM[];
extern  const   U2                  u2_gp_EVSCHG_RIMID_P_SETFTM[];
extern  const   U2                  u2_gp_EVSCHG_RIMID_P_SETWKD[];
extern  const   U2                  u2_gp_EVSCHG_RIMID_P_SETNXT[];

extern  void    (* const            fp_gp_vd_EVSCHG_TX[])(const U2 u2_a_RXDATA);

#endif /* EVSCHG_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see  evschg.c                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
