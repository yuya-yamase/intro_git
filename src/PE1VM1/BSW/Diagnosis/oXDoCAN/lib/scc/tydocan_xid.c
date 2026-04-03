/* 1.2.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for Toyota MET/HUD based on AUBIST/DEM, DCM                                                                     */
/*  SID 0x22/0x2E/0x2F/0x31 DataIdentifer and Routine Identifer                                                                      */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_XID_C_MAJOR                      (1U)
#define TYDOCAN_XID_C_MINOR                      (2U)
#define TYDOCAN_XID_C_PATCH                      (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "oxdocan_xid_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (TYDOCAN_XID_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "tydocan_xid.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if (TYDOCAN_XID_C_MAJOR != OXDOCAN_SAL_H_MAJOR)
#error "tydocan_xid.c and oxdocan_sal.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_XID_SUP_DID_ORG                     (0xA100U)
#define TYDC_XID_SUP_RID_ORG                     (0xD100U)
#define TYDC_XID_SUP_XID_SFT                     (0x0100U)
#define TYDC_XID_SUP_GR_MASK                     (0xFF00U)

#define TYDC_XID_LSB_XGR                         (8U)
#define TYDC_XID_SUP_LSB_IDX                     (3U)
#define TYDC_XID_SUP_MSB                         (7U)

#define TYDC_XID_SUP_NBYTE                       (32U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2             u2_s_tydc_xid_lp_begin;
static U1             u1_s_tydc_xid_supchk;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2    u2_s_oXDoCANXidSearchXidGr(const U2 u2_a_XID, const ST_OXDC_XID * st_ap_CFG, const U2 u2_a_NUM_CFG);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U2    u2_g_oXDoCANXidSearchXid(const U2 u2_a_XID, const ST_OXDC_XID * st_ap_CFG, const U2 u2_a_NUM_CFG)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_XID    : Input data identifier                                                                          */
/*  Return:         U2  u2_t_ret    : Xid index                                                                                      */
/*===================================================================================================================================*/
U2    u2_g_oXDoCANXidSearchXid(const U2 u2_a_XID, const ST_OXDC_XID * st_ap_CFG, const U2 u2_a_NUM_CFG)
{
    U4              u4_t_idx_chk;
    U4              u4_t_idx_min;
    U4              u4_t_idx_max;

    U2              u2_t_xid_chk;
    U2              u2_t_idx;

    u2_t_idx = (U2)U2_MAX;

    if((u2_a_NUM_CFG > (U2)0U    ) &&
       (st_ap_CFG   != vdp_PTR_NA)){

        u4_t_idx_min = (U4)0U;
        u4_t_idx_max = (U4)u2_a_NUM_CFG - (U4)1U;
        do{
            u4_t_idx_chk = (u4_t_idx_min + u4_t_idx_max) >> 1U;
            u2_t_xid_chk = st_ap_CFG[u4_t_idx_chk].u2_xid;
            if(u2_a_XID > u2_t_xid_chk){
                u4_t_idx_min = u4_t_idx_chk + (U4)1U;
            }
            else{
                u4_t_idx_max = u4_t_idx_chk;
            }
        }while(u4_t_idx_min < u4_t_idx_max);

        u2_t_xid_chk = st_ap_CFG[u4_t_idx_min].u2_xid;
        if(u2_t_xid_chk == u2_a_XID){
            u2_t_idx = (U2)u4_t_idx_min;
        }
    }

    return (u2_t_idx);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANXidSupInit(const U2 u2_a_LP_BEGIN, U1 * u1_ap_sup)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
void    vd_g_oXDoCANXidSupInit(const U2 u2_a_LP_BEGIN, U1 * u1_ap_sup)
{
    U4                        u4_t_lpcnt;

    u2_s_tydc_xid_lp_begin = u2_a_LP_BEGIN;
    u1_s_tydc_xid_supchk   = (U1)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TYDC_XID_SUP_NBYTE; u4_t_lpcnt++){
        u1_ap_sup[u4_t_lpcnt] = (U1)0U;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANDidSupInit(const U2 u2_a_LP_BEGIN, U1 * u1_ap_sup)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
void    vd_g_oXDoCANDidSupInit(const U2 u2_a_LP_BEGIN, U1 * u1_ap_sup)
{
    U2                        u2_t_did;
    U2                        u2_t_idx;

    u2_t_did = (st_gp_OXDC_DATA_XID[u2_a_LP_BEGIN].u2_xid - (U2)TYDC_XID_SUP_DID_ORG) * (U2)TYDC_XID_SUP_XID_SFT;
    u2_t_idx = u2_s_oXDoCANXidSearchXidGr(u2_t_did, &st_gp_OXDC_DATA_XID[0], u2_g_OXDC_DATA_NUM_XID);

    vd_g_oXDoCANXidSupInit(u2_t_idx, u1_ap_sup);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANRidSupInit(const U2 u2_a_LP_BEGIN, U1 * u1_ap_sup)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
void    vd_g_oXDoCANRidSupInit(const U2 u2_a_LP_BEGIN, U1 * u1_ap_sup)
{
    U2                        u2_t_rid;
    U2                        u2_t_idx;

    u2_t_rid = (st_gp_OXDC_ROUT_XID[u2_a_LP_BEGIN].u2_xid - (U2)TYDC_XID_SUP_RID_ORG) * (U2)TYDC_XID_SUP_XID_SFT;
    u2_t_idx = u2_s_oXDoCANXidSearchXidGr(u2_t_rid, &st_gp_OXDC_ROUT_XID[0], u2_g_OXDC_ROUT_NUM_XID);

    vd_g_oXDoCANXidSupInit(u2_t_idx, u1_ap_sup);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANXidSupchk(const ST_OXDC_XID * st_ap_XID, const U2 u2_a_NUM_XID, U1 * u1_ap_sup)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANXidSupchk(const ST_OXDC_XID * st_ap_XID, const U2 u2_a_NUM_XID, U1 * u1_ap_sup)
{
    U4                        u4_t_lpcnt;
    U4                        u4_t_lpend;

    U2                        u2_t_xid;

    U1                        u1_t_xgr;
    U1                        u1_t_xid_hi;
    U1                        u1_t_xid_lo;
    U1                        u1_t_pos;
    U1                        u1_t_bit;
    U1                        u1_t_sup;

    U1                        u1_t_proc;

    if((st_ap_XID              != vdp_PTR_NA  ) &&
       (u2_s_tydc_xid_lp_begin <  u2_a_NUM_XID)){

        u1_t_xgr   = (U1)(st_ap_XID[u2_s_tydc_xid_lp_begin].u2_xid >> TYDC_XID_LSB_XGR);
        u4_t_lpcnt = (U4)u2_s_tydc_xid_lp_begin;
        u4_t_lpend = u4_t_lpcnt + (U4)u2_g_OXDC_XID_SUP_LP_LMT;
        if(u4_t_lpend >= (U4)u2_a_NUM_XID){
            u2_s_tydc_xid_lp_begin  = (U2)U2_MAX;
            u4_t_lpend              = (U4)u2_a_NUM_XID;
            u1_t_proc               = (U1)OXDC_SAL_PROC_FIN;
        }
        else{
            u2_s_tydc_xid_lp_begin += u2_g_OXDC_XID_SUP_LP_LMT;
            u1_t_proc               = (U1)OXDC_SAL_PROC_RUN;
        }

        while(u4_t_lpcnt < u4_t_lpend){

            if(st_ap_XID[u4_t_lpcnt].fp_u1_SUP == vdp_PTR_NA){
                u1_t_sup = (U1)OXDC_XID_SUP_PUB;
            }
            else{
                u1_t_sup = (*st_ap_XID[u4_t_lpcnt].fp_u1_SUP)();
            }

            u2_t_xid    = st_ap_XID[u4_t_lpcnt].u2_xid;
            u1_t_xid_hi = (U1)(u2_t_xid >> TYDC_XID_LSB_XGR);
            u1_t_xid_lo = (U1)u2_t_xid;
            if(u1_t_xid_hi != u1_t_xgr){
                u1_t_proc  = (U1)OXDC_SAL_PROC_FIN;
                u4_t_lpend = (U4)0U;                /* loop is terminated */
            }
            else if(u1_t_sup == (U1)OXDC_XID_SUP_PUB){

                /* -------------------------------------------------- */
                /* TRS_UDS-DA 5.1.28                                  */
                /* TRS_UDS-DA 8.1.5                                   */
                /* -------------------------------------------------- */
                /* byte bit description                               */
                /* -------------------------------------------------- */
                /*  byte  bit                                         */
                /*  1     7   XIdentifier 0x**00 is Supported or NOT. */
                /*        6   XIdentifier 0x**01 is Supported or NOT. */
                /*        5   XIdentifier 0x**02 is Supported or NOT. */
                /*        4   XIdentifier 0x**03 is Supported or NOT. */
                /*        3   XIdentifier 0x**04 is Supported or NOT. */
                /*        2   XIdentifier 0x**05 is Supported or NOT. */
                /*        1   XIdentifier 0x**06 is Supported or NOT. */
                /*        0   XIdentifier 0x**07 is Supported or NOT. */
                /*  2     7   XIdentifier 0x**08 is Supported or NOT. */
                /*        6   XIdentifier 0x**09 is Supported or NOT. */
                /*        5   XIdentifier 0x**0A is Supported or NOT. */
                /*        4   XIdentifier 0x**0B is Supported or NOT. */
                /*        3   XIdentifier 0x**0C is Supported or NOT. */
                /*        2   XIdentifier 0x**0D is Supported or NOT. */
                /*        1   XIdentifier 0x**0E is Supported or NOT. */
                /*        0   XIdentifier 0x**0F is Supported or NOT. */

                u1_t_pos              = u1_t_xid_lo >> TYDC_XID_SUP_LSB_IDX;
                u1_t_bit              = (U1)0x01U << (TYDC_XID_SUP_MSB - (u1_t_xid_lo & (U1)TYDC_XID_SUP_MSB));
                u1_ap_sup[u1_t_pos]  |= u1_t_bit;
                u1_s_tydc_xid_supchk |= u1_t_bit;
            }
            else{
                /* Do Nothing */
            }
            u4_t_lpcnt++;
        }

        if((u1_t_proc            == (U1)OXDC_SAL_PROC_FIN) &&
           (u1_s_tydc_xid_supchk == (U1)0U               )){
            u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
        }
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_10;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANXgrSupchk(const ST_OXDC_XID * st_ap_XID, const U2 u2_a_NUM_XID, U1 * u1_ap_sup)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANXgrSupchk(const ST_OXDC_XID * st_ap_XID, const U2 u2_a_NUM_XID, U1 * u1_ap_sup)
{
    U4                        u4_t_lpcnt;
    U4                        u4_t_lpend;

    U2                        u2_t_xid;

    U1                        u1_t_xgr;
    U1                        u1_t_xid_hi;
    U1                        u1_t_pos;
    U1                        u1_t_bit;
    U1                        u1_t_sup;

    U1                        u1_t_proc;

    if((st_ap_XID              != vdp_PTR_NA  ) &&
       (u2_s_tydc_xid_lp_begin <  u2_a_NUM_XID)){

        u4_t_lpcnt = (U4)u2_s_tydc_xid_lp_begin;
        u4_t_lpend = u4_t_lpcnt + (U4)u2_g_OXDC_XID_SUP_LP_LMT;
        if(u4_t_lpend >= (U4)u2_a_NUM_XID){
            u2_s_tydc_xid_lp_begin  = (U2)U2_MAX;
            u4_t_lpend              = (U4)u2_a_NUM_XID;
            u1_t_proc               = (U1)OXDC_SAL_PROC_FIN;
        }
        else{
            u2_s_tydc_xid_lp_begin += u2_g_OXDC_XID_SUP_LP_LMT;
            u1_t_proc               = (U1)OXDC_SAL_PROC_RUN;
        }

        u1_t_xgr = (U1)0U;
        while(u4_t_lpcnt < u4_t_lpend){

            u2_t_xid    = st_ap_XID[u4_t_lpcnt].u2_xid;
            u1_t_xid_hi = (U1)(u2_t_xid >> TYDC_XID_LSB_XGR);
                if(u1_t_xid_hi != u1_t_xgr){

                if(st_ap_XID[u4_t_lpcnt].fp_u1_SUP == vdp_PTR_NA){
                    u1_t_sup = (U1)OXDC_XID_SUP_PUB;
                }
                else{
                    u1_t_sup = (*st_ap_XID[u4_t_lpcnt].fp_u1_SUP)();
                }

                if(u1_t_sup == (U1)OXDC_XID_SUP_PUB){
                    
                    /* ----------------------------------------------- */
                    /* TRS_UDS-DA 5.1.27                               */
                    /* TRS_UDS-DA 8.1.4                                */
                    /* ----------------------------------------------- */
                    /* 1    7   Reserve                                */
                    /*      6   XIdentifier 0x*101 is supported or NOT */
                    /*      5   XIdentifier 0x*102 is supported or NOT */
                    /*      4   XIdentifier 0x*103 is supported or NOT */
                    /*      3   XIdentifier 0x*104 is supported or NOT */
                    /*      2   XIdentifier 0x*105 is supported or NOT */
                    /*      1   XIdentifier 0x*106 is supported or NOT */
                    /*      0   XIdentifier 0x*107 is supported or NOT */
                    /* 2    7   XIdentifier 0x*108 is supported or NOT */
                    /*      6   XIdentifier 0x*109 is supported or NOT */
                    /*      5   XIdentifier 0x*10A is supported or NOT */
                    /*      4   XIdentifier 0x*10B is supported or NOT */
                    /*      3   XIdentifier 0x*10C is supported or NOT */
                    /*      2   XIdentifier 0x*10D is supported or NOT */
                    /*      1   XIdentifier 0x*10E is supported or NOT */
                    /*      0   XIdentifier 0x*10F is supported or NOT */
                    u1_t_xgr              = u1_t_xid_hi;
                    u1_t_pos              = u1_t_xid_hi >> TYDC_XID_SUP_LSB_IDX;
                    u1_t_bit              = (U1)0x01U << (TYDC_XID_SUP_MSB - (u1_t_xid_hi & (U1)TYDC_XID_SUP_MSB));
                    u1_ap_sup[u1_t_pos]  |= u1_t_bit;
                    u1_s_tydc_xid_supchk |= u1_t_bit;
                }
            }
            u4_t_lpcnt++;
        } /* while((u4_t_lpcnt < (U4)u2_a_NUM_XID         ) && */

        if((u1_t_proc            == (U1)OXDC_SAL_PROC_FIN) &&
           (u1_s_tydc_xid_supchk == (U1)0U               )){
            u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
        }
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_10;
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  static U2    u2_s_oXDoCANXidSearchXidGr(const U2 u2_a_XID, const ST_OXDC_XID * st_ap_CFG, const U2 u2_a_NUM_CFG)                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> u2_a_XID    : Input data identifier                                                                          */
/*  Return:         U2  u2_t_ret    : Xid index                                                                                      */
/*===================================================================================================================================*/
static U2    u2_s_oXDoCANXidSearchXidGr(const U2 u2_a_XID, const ST_OXDC_XID * st_ap_CFG, const U2 u2_a_NUM_CFG)
{
    U4              u4_t_idx_chk;
    U4              u4_t_idx_min;
    U4              u4_t_idx_max;

    U2              u2_t_xid_chk;
    U2              u2_t_idx;


    u2_t_idx = (U2)U2_MAX;

    if((u2_a_NUM_CFG > (U2)0U    ) &&
       (st_ap_CFG   != vdp_PTR_NA)){

        u4_t_idx_min = (U4)0U;
        u4_t_idx_max = (U4)u2_a_NUM_CFG - (U4)1U;
        do{
            u4_t_idx_chk = (u4_t_idx_min + u4_t_idx_max) >> 1U;
            u2_t_xid_chk = (U2)(st_ap_CFG[u4_t_idx_chk].u2_xid & (U2)TYDC_XID_SUP_GR_MASK);
            if(u2_a_XID > u2_t_xid_chk){
                u4_t_idx_min = u4_t_idx_chk + (U4)1U;
            }
            else{
                u4_t_idx_max = u4_t_idx_chk;
            }
        }while(u4_t_idx_min < u4_t_idx_max);

        u2_t_xid_chk = (U2)(st_ap_CFG[u4_t_idx_min].u2_xid & (U2)TYDC_XID_SUP_GR_MASK);
        if(u2_t_xid_chk == u2_a_XID){
            u2_t_idx = (U2)u4_t_idx_min;
        }
    }

    return (u2_t_idx);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     5/ 9/2019  TN       New.                                                                                               */
/*  1.1.0    10/10/2019  TN       tydocan_xid service application interface was optimized.                                           */
/*  1.2.0     2/21/2020  HK       u1_g_TyDoCANXidSupchk was optimized.                                                               */
/*  1.2.1     4/ 2/2021  HK       QAC warnigs were fixed.                                                                            */
/*  1.2.2     9/ 9/2021  TN       NULL->vdp_PTR_NA.                                                                                  */
/*  1.2.3    12/14/2022  MI       Fix Phase6(XID:A901, D902, D903, D904)                                                             */
/*                                                                                                                                   */
/*  * TN = Takashi Nagai, DENSO                                                                                                      */
/*  * HK = Hayato Kanamori, DENSO Create                                                                                             */
/*  * MI = Masahiko Izumi, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
