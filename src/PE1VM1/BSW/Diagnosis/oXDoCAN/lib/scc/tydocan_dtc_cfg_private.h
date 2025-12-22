/* 1.9.4 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for Toyota MET/HUD based on AUBIST/DEM, DCM                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#ifndef TYDOCAN_DTC_CFG_H
#define TYDOCAN_DTC_CFG_H

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DTC_CFG_H_MAJOR                  (1U)
#define TYDOCAN_DTC_CFG_H_MINOR                  (9U)
#define TYDOCAN_DTC_CFG_H_PATCH                  (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "memfill_u1.h"

#include "Dem_MM_Cfg.h"           /* DEM_NVM_USE_NVBLOCK_NUM is defined in Dem_MM_Cfg.h           */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_DTC_NVM_REC_KIND_PRIM_EVT              (0U)
#define TYDC_DTC_NVM_REC_KIND_UDM_EVT               (1U)
#define TYDC_DTC_NVM_REC_KIND_OTHER                 (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2                      u2_pdu_idx;               /* Aubist/Com    PDU Index defined in Com_Cfg.h                      */
    U2                      u2_sys_chk;               /* See oxcan.h/u1_g_oXCANRxStat.                                     */
    U2                      u2_rx_tout;               /* Rx Timeout Thresh  See oxcan.h/u1_g_oXCANRxStat.                  */
    U2                      u2_rxc_cyc;
    U2                      u2_rxc_min;
}ST_TYDC_DTC_PDU_RX;

typedef struct{
    U4                      u4_ev;
    U4                      u4_rx;
}ST_TYDC_DTC_LOG_RX;

typedef struct{
    U1 ( * const            fp_u1_SUP)(void);         /* Return TRUE = DEM_DemEventDTC_XXXXX is supported, FALSE = not     */

    U2                      u2_smpl_tslot;            /* event sampling timing, See oxdocan_cfg_private.h OXDC_TSLOT_BIT_X */
    U2                      u2_dtc_id;                /* DEM_DemEventDTC_XXXXX defined in Dem.h                            */

    U1                      u1_pdu_begin;             /* index of st_gp_TYDC_DTC_PDU_RX[]                                  */
    U1                      u1_num_pdu;               /* number of pdu to set/rest DTC                                     */

    U1                      u1_log_bit;               /* bit postion of st_gp_tydc_dtc_log_rx[].u4_rx                      */
    U1                      u1_log_idx;               /* index of st_gp_tydc_dtc_log_rx[]                                  */
}ST_TYDC_DTC_COM_RX;

typedef struct{
    U1 ( * const            fp_u1_CHK)(const U2 u2_a_ELPSD);
                                                      /* Return OXDC_DTC_TR_XXXX defined in oxdocan_sal.h                  */
                                                      /* u2_a_ELPSD = elapsd time since trouble check operation is enabled */
    U2                      u2_smpl_tslot;            /* event sampling timing, See oxdocan_cfg_private.h OXDC_TSLOT_BIT_X */
    U2                      u2_dtc_id;
}ST_TYDC_DTC_TR_CHK;

typedef struct{
    U2                      u2_mem_slct;
    U1 ( * const            fp_u1_UDM_DEL)(void);
}ST_TYDC_DTC_UDM_DEL;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern U4                          u4_gp_tydc_dtc_tr_act[];                    /* size of array = u1_g_TYDC_DTC_NOW_TR_ACT */
extern ST_TYDC_DTC_LOG_RX          st_gp_tydc_dtc_log_rx[];                    /* size of array = u1_g_TYDC_DTC_NOW_LOG_RX */
extern U2                          u2_gp_tydc_dtc_rxc_st[];                    /* size of array = u1_g_TYDC_DTC_NUM_PDU_RX */
extern U1                          u1_gp_tydc_dtc_rx_cnt[];                    /* size of array = u1_g_TYDC_DTC_NUM_PDU_RX */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void    vd_g_TyDoCANDtcCfgEvmFinish(const U1 u1_a_S14);                    /* u1_a_S14 TRUE  = SID 0x14 has been performed */
                                                                           /*          FALSE = not.                        */
U1      u1_g_TyDoCANDtcCfgNvmKind(const U2 u2_a_rec_id);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
extern const U1                    u1_g_TYDC_DTC_NOW_TR_ACT;          /* Number of Words / Size of u4_gp_tydc_dtc_tr_act[] */

extern const ST_TYDC_DTC_PDU_RX    st_gp_TYDC_DTC_PDU_RX[];
extern const U1                    u1_g_TYDC_DTC_NUM_PDU_RX;

extern const U2                    u2_gp_TYDC_DTC_NVMC_LOG_RX[];
extern const U1                    u1_g_TYDC_DTC_NOW_LOG_RX;          /* Number of Words / Size of st_gp_tydc_dtc_log_rx[] */

extern const ST_TYDC_DTC_COM_RX    st_gp_TYDC_DTC_COM_RX[];
extern const U1                    u1_g_TYDC_DTC_NUM_COM_RX;

extern const ST_TYDC_DTC_TR_CHK    st_gp_TYDC_DTC_TR_CHK[];
extern const U1                    u1_g_TYDC_DTC_NUM_TR_CHK;

extern const ST_TYDC_DTC_UDM_DEL   st_gp_TYDC_DTC_UDM_DEL[];
extern const U1                    u1_g_TYDC_DTC_NUM_UDM_DEL;

extern const U2                    u2_gp_TYDC_DTC_NVMC_BLOCK[DEM_NVM_USE_NVBLOCK_NUM];
extern const U2                    u2_g_TYDC_DTC_S14_TOUT;

extern const U2                    u2_g_TYDC_DTC_RIMID_UDM_EV_CNT;
extern const U2                    u2_g_TYDC_DTC_RIMID_UDM_EV_ID;

#endif      /* TYDOCAN_DTC_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  see tydocan_dtc.c                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
