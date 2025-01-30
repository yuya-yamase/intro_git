/* 1.0.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HUD based on AUBIST/DEM, DCM                                                                            */
/*  Snapshot Recorder for SID 0x22                                                                                                   */
/*===================================================================================================================================*/

#ifndef TYDOCAN_DID_SSR_CFG_H
#define TYDOCAN_DID_SSR_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DID_SSR_CFG_H_MAJOR              (1U)
#define TYDOCAN_DID_SSR_CFG_H_MINOR              (0U)
#define TYDOCAN_DID_SSR_CFG_H_PATCH              (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "rim_ctl.h"
#include "tydocan_did_ssr.h"
#include "memfill_u1.h"
#include "memcpy_u1.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4                u4_odo_last;
    U2                u2_num_last;                     /* Max. of ST_OXDC_DID_SSR.u2_rec_num                                */
    U2                u2_pau_elpsd;
    U1                u1_rec_run;
    U1                u1_rec_last;
    U1                u1_rec_cnt;
    U1                u1_del_cnt;
}ST_OXDC_DID_SSR_CTRL;

typedef struct{
    void ( * const    fp_vd_SYN)(const U1 u1_a_SSR_CH, const U1 u1_a_BON_INIT);
    U1   ( * const    fp_u1_REA)(const U1 u1_a_SSR_CH, const U1 u1_a_REC_IDX, ST_OXDC_DID_SSR * st_ap_ssr);
                                                       /* Return : TRUE = st_ap_ssr is valid, FALSE = not                   */
    U1   ( * const    fp_u1_RUN)(const U1 u1_a_SSR_CH, const ST_OXDC_DID_SSR * st_ap_SSR);
                                                       /* Return : TRUE = NvMC Write Requested, FALSE = not                 */
    U1   ( * const    fp_u1_DEL)(const U1 u1_a_SSR_CH);
                                                       /* Return : TRUE = NvMC Write Requested, FALSE = not                 */
}ST_OXDC_DID_SSR_IF;

typedef struct{
    U1   ( * const    fp_u1_EV_CAPT)(const U1 u1_a_ODO_UPDT, U4 * u4_ap_ss);
                                                       /* Return TRUE = recording event is captured, FALSE = not.           */
    const U2 *        u2p_MEM_ID;                      /* NVMC ID or RIM ID Table                                           */
    U2                u2_smpl_tslot;                   /* event sampling timing, See oxdocan_cfg_private.h OXDC_TSLOT_BIT_X */
    U1                u1_num_rec;
    U1                u1_mem_nbyte;
}ST_OXDC_DID_SSR_CH;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern ST_OXDC_DID_SSR_CTRL           st_gp_oxdc_did_ssr_ctrl[];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Standard Interface */
void    vd_g_oXDoCANDidSsrIfSynNvmbyCh(const U1 u1_a_SSR_CH, const U1 u1_a_BON_INIT);
U1      u1_g_oXDoCANDidSsrIfReaNvmbyCh(const U1 u1_a_SSR_CH, const U1 u1_a_REC_IDX, ST_OXDC_DID_SSR * st_ap_ssr);
U1      u1_g_oXDoCANDidSsrIfRunNvmbyCh(const U1 u1_a_SSR_CH, const ST_OXDC_DID_SSR * st_ap_SSR);
U1      u1_g_oXDoCANDidSsrIfDelNvmbyCh(const U1 u1_a_SSR_CH);
void    vd_g_oXDoCANDidSsrIfSynRimbyCh(const U1 u1_a_SSR_CH, const U1 u1_a_BON_INIT);
U1      u1_g_oXDoCANDidSsrIfReaRimbyCh(const U1 u1_a_SSR_CH, const U1 u1_a_REC_IDX, ST_OXDC_DID_SSR * st_ap_ssr);
U1      u1_g_oXDoCANDidSsrIfRunRimbyCh(const U1 u1_a_SSR_CH, const ST_OXDC_DID_SSR * st_ap_SSR);
U1      u1_g_oXDoCANDidSsrIfDelRimbyCh(const U1 u1_a_SSR_CH);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const ST_OXDC_DID_SSR_IF * const stp_gp_OXDC_DID_SSR_IF_BY_CH[]; /* The array size shall be equal to u1_g_OXDC_DID_SSR_NUM_CH */
extern const ST_OXDC_DID_SSR_CH         st_gp_OXDC_DID_SSR_CH_CFG[];    /* The array size shall be equal to u1_g_OXDC_DID_SSR_NUM_CH */
extern const U1                         u1_g_OXDC_DID_SSR_NUM_CH;

#endif      /* TYDOCAN_DID_SSR_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see tydocan_did_ssr.c                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
