/* 2.1.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Control sensors for Tripcom                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef TRIPSNSR_CFG_H
#define TRIPSNSR_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPSNSR_CFG_H_MAJOR                    (2)
#define TRIPSNSR_CFG_H_MINOR                    (1)
#define TRIPSNSR_CFG_H_PATCH                    (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "tripcom.h"
#include "tripsnsr.h"

#include "tripsnsr_elpsdtm.h"
#include "tripsnsr_odocnt.h"
#include "tripsnsr_fuelusd.h"
#include "tripsnsr_hydrusd.h"
#include "tripsnsr_avgee.h"
#include "tripsnsr_instee.h"

#include "veh_opemd.h"
#if 0   /* BEV BSW provisionally */
#else
#include "veh_opemd_xmode_STUB.h"
#endif
#include "vehspd_kmph.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TRIPSNSR_VEH_STOP_THSLD                 (175U)          /* 1.75 * VEHSPD_1_KMPH                                              */

#define TRIPSNSR_NUM_SNSR                       (8U)

#define TRIPSNSR_EVDTE_VALID                    (0x00U)
#define TRIPSNSR_EVDTE_UNKNOWN                  (0x01U)
#define TRIPSNSR_EVDTE_INVALID                  (0x02U)

/** PNC check **/
#define OXCAN_SYS_PNC_ALL                        (OXCAN_SYS_PNC_16 | OXCAN_SYS_PNC_40 | OXCAN_SYS_PNC_43 | OXCAN_SYS_PNC_44)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_g_TripsnsrIgnOn()                    (u1_g_VehopemdIgnOn())
#define u1_g_TripsnsrAccOn()                    (u1_g_VehopemdAccOn())
#define u1_g_TripsnsrPtsOn()                    (u1_g_VehopemdPtsOn((U1)VEH_OPEMD_PTS_INV_OFF))
                                                                    /* If any pts souce signal is invalid/rxto, return PTS-OFF/FALSE */
#define u1_g_TripsnsrVspKmph(x)                 (u1_g_VehspdKmphInst((x), (U1)TRUE))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    void    (* const                            fp_vd_TRIPSNSR_INIT)(void);
    void    (* const                            fp_vd_TRIPSNSR_SMPLNG_TASK)(const U2 u2_a_VEHSYSSTS, const U1 u1_a_PTSSTS);
    U2      (* const                            fp_u2_TRIPSNSR_DELTA_CHK)(U4 * u4_ap_delta);
    U1      (* const                            fp_u1_TRIPSNSR_RESET)(void);
} ST_TRIPSNSR_CNTTS;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* U1           u1_g_TripsnsrIgnOn(void);                                                                                            */
/* U1           u1_g_TripsnsrAccOn(void);                                                                                            */
/* U1           u1_g_TripsnsrPtsOn(void);                                                                                            */
/* U1           u1_g_TripsnsrVspKmph(U2 * u2_ap_kmph);                                                                               */

U1              u1_g_TripsnsrCfgEcoMode(void);
U1              u1_g_TripsnsrCfgGetECOMODE3(U1 * u1p_a_ecomode);

void            vd_g_TripsnsrCfgElpsdtmInit(void);
U4              u4_g_TripsnsrCfgElpsdtmGetDlt(void);

U1              u1_g_TripsnsrCfgGetBFC(U4 * u4p_a_fuel_inst);
U1              u1_g_TripsnsrCfgRxCntBFC(U1 * u1p_a_rollcnt);

U1              u1_g_TripsnsrCfgGetCNSMH2(U4 * u4p_a_hydr_inst);
U1              u1_g_TripsnsrCfgRxCntCNSMH2(U1 * u1p_a_rollcnt);

void            vd_g_TripsnsrCfgEvDteDist(U2 * u2p_a_dist);
void            vd_g_TripsnsrCfgEvDteSubRate(U1 * u1p_a_subrate);
void            vd_g_TripsnsrCfgEvDtePIEVE06(U1 * u1p_a_pieve06);
U1              u1_g_TripsnsrCfgEvDteCNGPIEVD(U1 * u1p_a_cngpievd);

U1              u1_g_TripsnsrCfgEvDteSts(void);
U1              u1_g_TripsnsrCfgEvDteBatSts(void);

U1              u1_g_TripsnsrCfgGetInsEpusd(S4 * s4p_a_insepusd);
U1              u1_g_TripsnsrCfgGetInsEvdist(U4 * u4p_a_evdist);
U1              u1_g_TripsnsrCfgGetInsUpdtflg(U1 * u1p_a_updtflg);

U1              u1_g_TripsnsrCfgGetEpusd(S4 * s4p_a_epusd);
U1              u1_g_TripsnsrCfgGetEpUpdflg(U1 * u1p_a_epupdflg);

U1              u1_g_TripsnsrCfgGetPtsSts(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern  const   ST_TRIPSNSR_CNTTS               st_gp_TRIPSNSR_CNTTS_CFG[];
extern  const   U4                              u4_g_TRIPSNSR_ELPSDTM_FRT_1US;

#endif      /* TRIPSNSR_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  tripsnsr.c                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
