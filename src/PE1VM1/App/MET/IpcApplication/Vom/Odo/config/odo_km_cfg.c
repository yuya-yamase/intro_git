/* 2.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Odo Configuration                                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ODO_KM_CFG_C_MAJOR                       (2)
#define ODO_KM_CFG_C_MINOR                       (0)
#define ODO_KM_CFG_C_PATCH                       (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "odo_km_cfg_private.h"
#include "odo_nvmif_cfg_private.h"
#include "odo_vslmt_cfg_private.h"
#include "odo_om_rst_if.h"

#include "veh_opemd.h"
#include "vardef.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ODO_KM_CFG_C_MAJOR != ODO_KM_CFG_H_MAJOR) || \
     (ODO_KM_CFG_C_MINOR != ODO_KM_CFG_H_MINOR) || \
     (ODO_KM_CFG_C_PATCH != ODO_KM_CFG_H_PATCH))
#error "odo_km_cfg.c and odo_km_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((ODO_KM_CFG_C_MAJOR != ODO_NVMIF_CFG_H_MAJOR) || \
     (ODO_KM_CFG_C_MINOR != ODO_NVMIF_CFG_H_MINOR) || \
     (ODO_KM_CFG_C_PATCH != ODO_NVMIF_CFG_H_PATCH))
#error "odo_km_cfg.c and odo_nvmif_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ODO_MAIN_TICK                            (50U)

#define ODO_0P1_KM                               (100U)
#define ODO_100_KM                               (100000U)
#define ODO_UNIT_TX_KM                           (0x01U)
#define ODO_UNIT_TX_MI                           (0x02U)

#define ODO_DIST_NUM_TX                          (5U)
#define ODO_DIST_TX_ODO                          (0U)
#define ODO_DIST_TX_TRIP_A                       (1U)
#define ODO_DIST_TX_TRIP_B                       (2U)
#define ODO_DIST_TX_ODO_01                       (3U)
#define ODO_DIST_ODO_TX_MAX                      (999999U)
#define ODO_DIST_ODO_01_TX_MAX                   (9999999U)
#define ODO_DIST_TRIP_TX_MOD                     (100000U)

#define ODO_OM_MLG_MAX                           (50U)
#define ODO_OM_MLG_PRE                           (45U)
#define ODO_OM_MLG_PRE_KM                        (72U)
#define ODO_OM_MLG_UNKNOWN                       (0x7FU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
ST_ODO_TRIP_KM             st_gp_odo_trip_km[ODO_TRIP_NUM_CH] __attribute__((section(".bss_BACK")));

static U4                  u4_sp_odo_dist_tx[ODO_DIST_NUM_TX];

static U4                  u4_s_odo_dist_om_rst;
static U1                  u1_s_odo_pr_om_fl;

static U1                  u1_s_odo_om_rststs;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_OdoCfgIgOff(void);
static void    vd_s_OdoComTxInit(const U4 u4_a_0P001KM);
static void    vd_s_OdoComTxUpdtOdo(const U4 u4_a_0P001KM);
static void    vd_s_OdoComTxUpdtTrip(const U4 u4_a_0P001KM);
static void    vd_s_OdoComTxUpdtOm(const U4 u4_a_0P001KM);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  odo_nvmif_cfg_private.h                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ODO_NVMIF_ODO_DTF_NUM_BLOCK              (20U)
static const U2            u2_sp_ODO_NVMIF_ODO_DTF_BLOCK[ODO_NVMIF_ODO_DTF_NUM_BLOCK] = {
    (U2)NVMC_BLOCKID_DTF_ODO_00,
    (U2)NVMC_BLOCKID_DTF_ODO_01,
    (U2)NVMC_BLOCKID_DTF_ODO_02,
    (U2)NVMC_BLOCKID_DTF_ODO_03,
    (U2)NVMC_BLOCKID_DTF_ODO_04,
    (U2)NVMC_BLOCKID_DTF_ODO_05,
    (U2)NVMC_BLOCKID_DTF_ODO_06,
    (U2)NVMC_BLOCKID_DTF_ODO_07,
    (U2)NVMC_BLOCKID_DTF_ODO_08,
    (U2)NVMC_BLOCKID_DTF_ODO_09,
    (U2)NVMC_BLOCKID_DTF_ODO_10,
    (U2)NVMC_BLOCKID_DTF_ODO_11,
    (U2)NVMC_BLOCKID_DTF_ODO_12,
    (U2)NVMC_BLOCKID_DTF_ODO_13,
    (U2)NVMC_BLOCKID_DTF_ODO_14,
    (U2)NVMC_BLOCKID_DTF_ODO_15,
    (U2)NVMC_BLOCKID_DTF_ODO_16,
    (U2)NVMC_BLOCKID_DTF_ODO_17,
    (U2)NVMC_BLOCKID_DTF_ODO_18,
    (U2)NVMC_BLOCKID_DTF_ODO_19
};

const ST_ODO_NVMIF_REC_KM  st_g_ODO_NVMIF_REC_ODO_KM = {
    &u2_sp_ODO_NVMIF_ODO_DTF_BLOCK[0],                      /* u2p_BLOCK     */
    (U1)ODO_NVMIF_ODO_DTF_NUM_BLOCK,                        /* u1_num_rec    */
    ((U1)sizeof(ST_ODO_KM) / (U1)ODO_NVMIF_BLO_NBYTE_12),   /* u1_rec_nblock */
    (U1)ODO_NVMIF_BLO_NBYTE_12,                             /* u1_blo_nbyte  */
    (U1)NVMC_DEVICE_TYPE_DTF                                /* u1_dev_idx    */
};
const U2                   u2_g_ODO_NVMIF_NVMCID_ODO_KM = (U2)NVMCID_APP_ODO;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2            u2_sp_ODO_NVMIF_TRIP_DTF_BLOCK[] = {
    (U2)NVMC_BLOCKID_DTF_TRIP_0_0,
    (U2)NVMC_BLOCKID_DTF_TRIP_0_1,

    (U2)NVMC_BLOCKID_DTF_TRIP_1_0,
    (U2)NVMC_BLOCKID_DTF_TRIP_1_1,

    (U2)NVMC_BLOCKID_DTF_TRIP_2_0,
    (U2)NVMC_BLOCKID_DTF_TRIP_2_1
};

const ST_ODO_NVMIF_REC_KM  st_g_ODO_NVMIF_REC_TRIP_KM = {
    &u2_sp_ODO_NVMIF_TRIP_DTF_BLOCK[0],                     /* u2p_BLOCK     */
    (U1)ODO_TRIP_NUM_CH * (U1)ODO_NVMIF_TRIP_NUM_REC,       /* u1_num_rec    */
    ((U1)sizeof(ST_ODO_KM) / (U1)ODO_NVMIF_BLO_NBYTE_12),   /* u1_rec_nblock */
    (U1)ODO_NVMIF_BLO_NBYTE_12,                             /* u1_blo_nbyte  */
    (U1)NVMC_DEVICE_TYPE_DTF                                /* u1_dev_idx    */
};
const U2                   u2_g_ODO_NVMIF_NVMCID_TRIP_KM = (U2)NVMCID_APP_ODO_TRIP;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  odo_km_cfg_private.h                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                   u2_g_ODO_NVM_REQ_TOUT        = ((U2)50U * (U2)ODO_NVMIF_ODO_DTF_NUM_BLOCK) / (U2)ODO_MAIN_TICK;
                                                                                                       /* 50 * 20 = 1000 = 1 second  */

const U2                   u2_g_ODO_TRIP_RST_TOUT       = (U2)10000U / (U2)ODO_MAIN_TICK;              /* 10 seconds                 */
const U1                   u1_g_ODO_TRIP_SYNC_RST_BY_CH = (((U1)0x01U << ODO_TRIP_CH_A) |
                                                           ((U1)0x01U << ODO_TRIP_CH_B));

const U1                   u1_g_ODO_TRIP_NUM_CH         = (U1)ODO_TRIP_NUM_CH;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  odo_vslmt_cfg_private.h                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                   u2_g_ODO_VSLMT_TM_UPDT       = (U2)1000U / (U2)ODO_MAIN_TICK;   /*  1 second  */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_OdoCfgBonInit(const U4 u4_a_0P001KM)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoCfgBonInit(const U4 u4_a_0P001KM)
{
    /* ----------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                     */
    /* ----------------------------------------------------------------------------------------------- */
    /* st_gp_odo_trip_km[] are initialized before vd_g_OdoCfgBonInit is invoked.                       */
    /* Therefore, those variables shall NOT be initialized at here.                                    */
    /* ----------------------------------------------------------------------------------------------- */

    vd_g_OdoVslmtInit();
    vd_s_OdoComTxInit(u4_a_0P001KM);

    u1_s_odo_om_rststs = (U1)ODO_OM_RSTSTS_NON;

}
/*===================================================================================================================================*/
/*  void    vd_g_OdoCfgRstwkInit(const U4 u4_a_0P001KM)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoCfgRstwkInit(const U4 u4_a_0P001KM)
{
    /* ----------------------------------------------------------------------------------------------- */
    /* Warning :                                                                                       */
    /* ----------------------------------------------------------------------------------------------- */
    /* st_gp_odo_trip_km[] shall NOT be initialized at here because it's located on Backup-RAM         */
    /* ----------------------------------------------------------------------------------------------- */

    vd_g_OdoVslmtInit();
    vd_s_OdoComTxInit(u4_a_0P001KM);

    u1_s_odo_om_rststs = (U1)ODO_OM_RSTSTS_NON;

}
/*===================================================================================================================================*/
/*  void    vd_g_OdoCfgMainStart(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoCfgMainStart(void)
{
    U1  u1_t_igon;              /* IG Status    */

    vd_g_OdoVslmtMainTask();

    u1_t_igon = u1_g_VehopemdIgnOn();
    if(u1_t_igon == (U1)FALSE){
        vd_s_OdoCfgIgOff();
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_OdoCfgIgOff(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoCfgIgOff(void)
{
    u1_s_odo_om_rststs = (U1)ODO_OM_RSTSTS_NON;
}

/*===================================================================================================================================*/
/*  void    vd_g_OdoCfgMainFinish(const U4 u4_a_0P001KM)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoCfgMainFinish(const U4 u4_a_0P001KM)
{
    vd_s_OdoComTxUpdtOdo(u4_a_0P001KM);
    vd_s_OdoComTxUpdtTrip(u4_a_0P001KM);
    vd_s_OdoComTxUpdtOm(u4_a_0P001KM);
}
/*===================================================================================================================================*/
/*  U4      u4_g_OdoCfgInstPerKm(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_OdoCfgInstPerKm(void)
{
    /* ----------------------------------------------------------------------------------------- */
    /* WARNING                                                                                   */
    /* ----------------------------------------------------------------------------------------- */
    /* The return of u4_g_OdoCfgInstPerKm() shall be greater than or equal to ODO_MIN_PER_KM(50U). */
    /* ----------------------------------------------------------------------------------------- */

    return((U4)5096U);
}
/*===================================================================================================================================*/
/*  U1      u1_g_OdoCfgIncrEn(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_OdoCfgIncrEn(void)
{
    return(u1_g_OdoVslmtIncrEn());
}
/*===================================================================================================================================*/
/*  U1      u1_g_OdoCfgKmNextToNvm(const U4 u4_a_0P001KM_NEXT, const U4 u4_a_0P001KM_NVM)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#define ODO_NVM_AT_IG_OFF                    (1)
U1      u1_g_OdoCfgKmNextToNvm(const U4 u4_a_0P001KM_NEXT, const U4 u4_a_0P001KM_NVM)
{
#if (ODO_NVM_AT_IG_OFF == 1)
    U4                 u4_t_km_next;
    U4                 u4_t_km_nvm;
    U1                 u1_t_rqst;
    U1                 u1_t_igon;

    u1_t_rqst = (U1)FALSE;
    u1_t_igon = u1_g_VehopemdIgnOn();
    if(u1_t_igon == (U1)TRUE){

        u4_t_km_next = u4_a_0P001KM_NEXT / (U4)ODO_1_KM;
        u4_t_km_nvm  = u4_a_0P001KM_NVM  / (U4)ODO_1_KM;
        if(u4_t_km_next > u4_t_km_nvm){
            u1_t_rqst = (U1)TRUE;
        }
    }
    else{
        if(u4_a_0P001KM_NEXT >= u4_a_0P001KM_NVM) {
            u4_t_km_next = u4_a_0P001KM_NEXT - u4_a_0P001KM_NVM;
            if(u4_t_km_next >= (U4)ODO_TRIP_MIN_TO_NVM){
                u1_t_rqst = (U1)TRUE;
            }
        }
    }

    return(u1_t_rqst);
#else
    U4                 u4_t_km_next;
    U4                 u4_t_km_nvm;
    U1                 u1_t_rqst;

    u4_t_km_next = u4_a_0P001KM_NEXT / (U4)ODO_1_KM;
    u4_t_km_nvm  = u4_a_0P001KM_NVM  / (U4)ODO_1_KM;
    if(u4_t_km_next > u4_t_km_nvm){
        u1_t_rqst = (U1)TRUE;
    }
    else{
        u1_t_rqst = (U1)FALSE;
    }

    return(u1_t_rqst);
#endif /* #if (ODO_NVM_AT_IG_OFF == 1) */
}
/*===================================================================================================================================*/
/*  void    vd_g_OdoCfgTripMirrInit(const U1 u1_a_CH, const U1 u1_a_INIT)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoCfgTripMirrInit(const U1 u1_a_CH, const U1 u1_a_INIT)
{
}
/*===================================================================================================================================*/
/*  void    vd_g_OdoCfgTripOmRstJdg(const U1 u1_a_CH)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoCfgTripOmRstJdg(const U1 u1_a_CH)
{
    if(u1_a_CH == (U1)ODO_TRIP_CH_OM) {
        if(st_gp_odo_trip_km[ODO_TRIP_CH_OM].u4_ge_m == (U4)ODO_KM_UNK) {
            u1_s_odo_om_rststs = (U1)ODO_OM_RSTSTS_FAIL;
        } else {
            u1_s_odo_om_rststs = (U1)ODO_OM_RSTSTS_COMP;
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_OdoCfgTripMirrCpbk(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoCfgTripMirrCpbk(void)
{
}
/*===================================================================================================================================*/
/*  void    vd_g_OdoOmReset(const U1 u1_a_ACT)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoOmReset(const U1 u1_a_ACT)
{
    if(u1_a_ACT == (U1)TRUE){
        u4_s_odo_dist_om_rst = st_gp_odo_trip_km[ODO_TRIP_CH_OM].u4_di_m;
        vd_g_OdoTripReset((U1)ODO_TRIP_CH_OM, (U1)TRUE);
        u1_s_odo_om_rststs = (U1)ODO_OM_RSTSTS_NON;
    }
    else{
        vd_g_OdoTripReset((U1)ODO_TRIP_CH_OM, (U1)FALSE);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoComTxInit(const U4 u4_a_0P001KM)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoComTxInit(const U4 u4_a_0P001KM)
{
    U4                 u4_t_tx;
    U1                 u1_t_unit_def;
    U1                 u1_t_odo_unit_tx;
    U1                 u1_t_om_mile;
    U1                 u1_t_om_km;
    U1                 u1_t_om_mlg;
    U1                 u1_t_om_app;
    U1                 u1_t_odo_unit;

    u1_t_unit_def = u1_g_UnitDef((U1)UNIT_IDX_DIST);
    if(u4_a_0P001KM > (U4)ODO_KM_MAX){

        u1_t_odo_unit_tx = (U1)0U;

        u4_sp_odo_dist_tx[ODO_DIST_TX_ODO]      = (U4)0U;
        u4_sp_odo_dist_tx[ODO_DIST_TX_TRIP_A]   = (U4)0U;
        u4_sp_odo_dist_tx[ODO_DIST_TX_TRIP_B]   = (U4)0U;
        u4_sp_odo_dist_tx[ODO_DIST_TX_ODO_01]   = (U4)0U;
    }
    else if(u1_t_unit_def == (U1)UNIT_VAL_DIST_MILE){

        u1_t_odo_unit_tx = (U1)ODO_UNIT_TX_MI;

        u4_t_tx = u4_g_UnitconvtrKmtoMi(u4_a_0P001KM) / (U4)ODO_1_KM;
        u4_sp_odo_dist_tx[ODO_DIST_TX_ODO] = u4_t_tx;

        u4_t_tx = u4_g_UnitconvtrKmtoMi(st_gp_odo_trip_km[ODO_TRIP_CH_A].u4_di_m) / (U4)ODO_0P1_KM;
        u4_sp_odo_dist_tx[ODO_DIST_TX_TRIP_A] = u4_t_tx;

        u4_t_tx = u4_g_UnitconvtrKmtoMi(st_gp_odo_trip_km[ODO_TRIP_CH_B].u4_di_m) / (U4)ODO_0P1_KM;
        u4_sp_odo_dist_tx[ODO_DIST_TX_TRIP_B] = u4_t_tx;

        u4_t_tx = u4_g_UnitconvtrKmtoMi(u4_a_0P001KM) / (U4)ODO_0P1_KM;
        u4_sp_odo_dist_tx[ODO_DIST_TX_ODO_01] = u4_t_tx;

    }
    else{

        u1_t_odo_unit_tx = (U1)ODO_UNIT_TX_KM;

        u4_t_tx = u4_a_0P001KM / (U4)ODO_1_KM;
        u4_sp_odo_dist_tx[ODO_DIST_TX_ODO] = u4_t_tx;

        u4_t_tx = st_gp_odo_trip_km[ODO_TRIP_CH_A].u4_di_m / (U4)ODO_0P1_KM;
        u4_sp_odo_dist_tx[ODO_DIST_TX_TRIP_A] = u4_t_tx;

        u4_t_tx = st_gp_odo_trip_km[ODO_TRIP_CH_B].u4_di_m / (U4)ODO_0P1_KM;
        u4_sp_odo_dist_tx[ODO_DIST_TX_TRIP_B] = u4_t_tx;

        u4_t_tx = u4_a_0P001KM / (U4)ODO_0P1_KM;
        u4_sp_odo_dist_tx[ODO_DIST_TX_ODO_01] = u4_t_tx;

    }

    if(u4_sp_odo_dist_tx[ODO_DIST_TX_ODO] >= (U4)ODO_DIST_ODO_TX_MAX){
        u4_sp_odo_dist_tx[ODO_DIST_TX_ODO] = (U4)ODO_DIST_ODO_TX_MAX;
    }

    if(u4_sp_odo_dist_tx[ODO_DIST_TX_ODO_01] >= (U4)ODO_DIST_ODO_01_TX_MAX){
        u4_sp_odo_dist_tx[ODO_DIST_TX_ODO_01] = (U4)ODO_DIST_ODO_01_TX_MAX;
    }

    u4_sp_odo_dist_tx[ODO_DIST_TX_TRIP_A] = u4_sp_odo_dist_tx[ODO_DIST_TX_TRIP_A] % (U4)ODO_DIST_TRIP_TX_MOD;
    u4_sp_odo_dist_tx[ODO_DIST_TX_TRIP_B] = u4_sp_odo_dist_tx[ODO_DIST_TX_TRIP_B] % (U4)ODO_DIST_TRIP_TX_MOD;


    u1_t_om_mile = (U1)(u4_g_UnitconvtrKmtoMi(st_gp_odo_trip_km[ODO_TRIP_CH_OM].u4_di_m) / (U4)ODO_100_KM);
    u1_t_om_app  = u1_g_VardefTmntOpt();
    u1_t_om_km = (U1)(st_gp_odo_trip_km[ODO_TRIP_CH_OM].u4_di_m / (U4)ODO_100_KM);
    u1_t_odo_unit = u1_g_Unit((U1)UNIT_IDX_DIST);

    if((u1_t_odo_unit_tx == (U1)0U    ) || 
       (u1_t_om_app      == (U1)FALSE)){
        u1_t_om_mlg       = (U1)ODO_OM_MLG_UNKNOWN;
        u1_s_odo_pr_om_fl = (U1)FALSE;
    }
    else{
        if(u1_t_om_mile >= (U1)ODO_OM_MLG_MAX){
            u1_t_om_mlg  = (U1)0U;
        }
        else{
            u1_t_om_mlg  = (U1)ODO_OM_MLG_MAX - u1_t_om_mile;
        }

        if(u1_t_odo_unit          == (U1)UNIT_VAL_DIST_KM){
            if(u1_t_om_km         >= (U1)ODO_OM_MLG_PRE_KM){
                u1_s_odo_pr_om_fl  = (U1)TRUE;
            }
            else{
                u1_s_odo_pr_om_fl  = (U1)FALSE;
            }
        }
        else{
            if(u1_t_om_mile       >= (U1)ODO_OM_MLG_PRE){
                u1_s_odo_pr_om_fl  = (U1)TRUE;
            }
            else{
                u1_s_odo_pr_om_fl  = (U1)FALSE;
            }
        }
    }
    u4_s_odo_dist_om_rst = (U4)0U;

    (void)Com_SendSignal(ComConf_ComSignal_ODO_UNIT, &u1_t_odo_unit_tx);                        /* MET1S02 */
    (void)Com_SendSignal(ComConf_ComSignal_ODO,      &u4_sp_odo_dist_tx[ODO_DIST_TX_ODO]);      /* MET1S02 */
    (void)Com_SendSignal(ComConf_ComSignal_TRIP_A,   &u4_sp_odo_dist_tx[ODO_DIST_TX_TRIP_A]);   /* MET1S10 */
    (void)Com_SendSignal(ComConf_ComSignal_TRIP_B,   &u4_sp_odo_dist_tx[ODO_DIST_TX_TRIP_B]);   /* MET1S11 */
    (void)Com_SendSignal(ComConf_ComSignal_ODO_UNI2, &u1_t_odo_unit_tx);                        /* MET1S52 */
    (void)Com_SendSignal(ComConf_ComSignal_ODO_01,   &u4_sp_odo_dist_tx[ODO_DIST_TX_ODO_01]);   /* MET1S52 */

    (void)Com_SendSignal(ComConf_ComSignal_OM_MLG,   &u1_t_om_mlg);                             /* MET1S10 */
    (void)Com_SendSignal(ComConf_ComSignal_PR_OM_FL, &u1_s_odo_pr_om_fl);                       /* MET1S10 */
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoComTxUpdtOdo(const U4 u4_a_0P001KM)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoComTxUpdtOdo(const U4 u4_a_0P001KM)
{
    U4                 u4_t_odo_tx;
    U1                 u1_t_unit_def;
    U1                 u1_t_odo_unit_tx;
    U4                 u4_t_odo01_tx;

    u1_t_unit_def = u1_g_UnitDef((U1)UNIT_IDX_DIST);
    if(u4_a_0P001KM > (U4)ODO_KM_MAX){
        u1_t_odo_unit_tx = (U1)0U;
        u4_t_odo_tx      = (U4)0U;
        u4_t_odo01_tx    = (U4)0U;
    }
    else if(u1_t_unit_def == (U1)UNIT_VAL_DIST_MILE){
        u1_t_odo_unit_tx = (U1)ODO_UNIT_TX_MI;
        u4_t_odo_tx      = u4_g_UnitconvtrKmtoMi(u4_a_0P001KM) / (U4)ODO_1_KM;
        u4_t_odo01_tx    = u4_g_UnitconvtrKmtoMi(u4_a_0P001KM) / (U4)ODO_0P1_KM;
    }
    else{
        u1_t_odo_unit_tx = (U1)ODO_UNIT_TX_KM;
        u4_t_odo_tx      = u4_a_0P001KM / (U4)ODO_1_KM;
        u4_t_odo01_tx    = u4_a_0P001KM / (U4)ODO_0P1_KM;
    }

    if(u4_t_odo_tx >= (U4)ODO_DIST_ODO_TX_MAX){
        u4_t_odo_tx = (U4)ODO_DIST_ODO_TX_MAX;
    }

    if(u4_t_odo01_tx >= (U4)ODO_DIST_ODO_01_TX_MAX){
        u4_t_odo01_tx = (U4)ODO_DIST_ODO_01_TX_MAX;
    }

    (void)Com_SendSignal(ComConf_ComSignal_ODO_UNIT, &u1_t_odo_unit_tx);                          /* MET1S02 */
    if(u4_t_odo_tx != u4_sp_odo_dist_tx[ODO_DIST_TX_ODO]){
        (void)Com_SendSignal(ComConf_ComSignal_ODO, &u4_t_odo_tx);                                /* MET1S02 */
        (void)Com_TriggerIPDUSend(MSG_MET1S02_TXCH0);
    }
    u4_sp_odo_dist_tx[ODO_DIST_TX_ODO] = u4_t_odo_tx;

    (void)Com_SendSignal(ComConf_ComSignal_ODO_UNI2, &u1_t_odo_unit_tx);                          /* MET1S52 */
    if(u4_t_odo01_tx != u4_sp_odo_dist_tx[ODO_DIST_TX_ODO_01]){
        (void)Com_SendSignal(ComConf_ComSignal_ODO_01, &u4_t_odo01_tx);                           /* MET1S52 */
        (void)Com_TriggerIPDUSend(MSG_MET1S52_TXCH0);
    }
    u4_sp_odo_dist_tx[ODO_DIST_TX_ODO_01] = u4_t_odo01_tx;

}

/*===================================================================================================================================*/
/*  static void    vd_s_OdoComTxUpdtTrip(const U4 u4_a_0P001KM)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoComTxUpdtTrip(const U4 u4_a_0P001KM)
{
    U4                 u4_t_trip_a_tx;
    U4                 u4_t_trip_b_tx;
    U1                 u1_t_unit_def;

    u1_t_unit_def = u1_g_UnitDef((U1)UNIT_IDX_DIST);
    if(u4_a_0P001KM > (U4)ODO_KM_MAX){
        u4_t_trip_a_tx   = (U4)0U;
        u4_t_trip_b_tx   = (U4)0U;
    }
    else if(u1_t_unit_def == (U1)UNIT_VAL_DIST_MILE){
        u4_t_trip_a_tx   = u4_g_UnitconvtrKmtoMi(st_gp_odo_trip_km[ODO_TRIP_CH_A].u4_di_m) / (U4)ODO_0P1_KM;
        u4_t_trip_b_tx   = u4_g_UnitconvtrKmtoMi(st_gp_odo_trip_km[ODO_TRIP_CH_B].u4_di_m) / (U4)ODO_0P1_KM;
    }
    else{
        u4_t_trip_a_tx   = st_gp_odo_trip_km[ODO_TRIP_CH_A].u4_di_m / (U4)ODO_0P1_KM;
        u4_t_trip_b_tx   = st_gp_odo_trip_km[ODO_TRIP_CH_B].u4_di_m / (U4)ODO_0P1_KM;
    }

    u4_t_trip_a_tx = u4_t_trip_a_tx % (U4)ODO_DIST_TRIP_TX_MOD;
    u4_t_trip_b_tx = u4_t_trip_b_tx % (U4)ODO_DIST_TRIP_TX_MOD;

    if(u4_t_trip_a_tx != u4_sp_odo_dist_tx[ODO_DIST_TX_TRIP_A]){

        (void)Com_SendSignal(ComConf_ComSignal_TRIP_A,   &u4_t_trip_a_tx);                        /* MET1S10 */
        (void)Com_TriggerIPDUSend(MSG_MET1S10_TXCH0);
    }
    u4_sp_odo_dist_tx[ODO_DIST_TX_TRIP_A] = u4_t_trip_a_tx;

    if(u4_t_trip_b_tx != u4_sp_odo_dist_tx[ODO_DIST_TX_TRIP_B]){
        (void)Com_SendSignal(ComConf_ComSignal_TRIP_B,   &u4_t_trip_b_tx);                        /* MET1S11 */
        (void)Com_TriggerIPDUSend(MSG_MET1S11_TXCH0);
    }
    u4_sp_odo_dist_tx[ODO_DIST_TX_TRIP_B] = u4_t_trip_b_tx;
}

/*===================================================================================================================================*/
/*  static void    vd_s_OdoComTxUpdtOm(const U4 u4_a_0P001KM)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoComTxUpdtOm(const U4 u4_a_0P001KM)
{
    U4                 u4_t_om_di_m;
    U1                 u1_t_odo_dist_sts;
    U4                 u4_t_om_mile;
    U4                 u4_t_om_km;
    U1                 u1_t_om_mlg;
    U1                 u1_t_pr_om_fl;
    U1                 u1_t_om_app;
    U1                 u1_t_odo_unit;

    if(u4_a_0P001KM > (U4)ODO_KM_MAX){
        u1_t_odo_dist_sts = (U1)FALSE;
    }
    else{
        u1_t_odo_dist_sts = (U1)TRUE;
    }

    u4_t_om_di_m = st_gp_odo_trip_km[ODO_TRIP_CH_OM].u4_di_m;
    if(u4_t_om_di_m < u4_s_odo_dist_om_rst){
        u4_s_odo_dist_om_rst = (U4)0U;
    }

    u4_t_om_mile = (u4_g_UnitconvtrKmtoMi(u4_t_om_di_m) / (U4)ODO_100_KM);
    u1_t_om_app  = u1_g_VardefTmntOpt();
    u4_t_om_km = u4_t_om_di_m / (U4)ODO_100_KM;
    u1_t_odo_unit = u1_g_Unit((U1)UNIT_IDX_DIST);

    if((u1_t_odo_dist_sts    == (U1)FALSE) ||
       (u4_s_odo_dist_om_rst != (U4)0U)    ||
       (u1_t_om_app          == (U1)FALSE)){
	   
        u1_t_om_mlg      = (U1)ODO_OM_MLG_UNKNOWN;
        u1_t_pr_om_fl    = (U1)FALSE;
    }
    else{
        if(u4_t_om_mile >= (U4)ODO_OM_MLG_MAX){
            u1_t_om_mlg  = (U1)0U;
        }
        else{
            u1_t_om_mlg  = (U1)ODO_OM_MLG_MAX - (U1)u4_t_om_mile;
        }

        if(u1_t_odo_unit      == (U1)UNIT_VAL_DIST_KM){
            if(u4_t_om_km     >= (U4)ODO_OM_MLG_PRE_KM){
                u1_t_pr_om_fl  = (U1)TRUE;
            }
            else{
                u1_t_pr_om_fl  = (U1)FALSE;
            }
        }
        else{
            if(u4_t_om_mile   >= (U4)ODO_OM_MLG_PRE){
                u1_t_pr_om_fl  = (U1)TRUE;
            }
            else{
                u1_t_pr_om_fl  = (U1)FALSE;
            }
        }
    }

    (void)Com_SendSignal(ComConf_ComSignal_OM_MLG, &u1_t_om_mlg);                                 /* MET1S10 */
    if(u1_t_pr_om_fl  != u1_s_odo_pr_om_fl){
        (void)Com_SendSignal(ComConf_ComSignal_PR_OM_FL, &u1_t_pr_om_fl);                         /* MET1S10 */
        (void)Com_TriggerIPDUSend(MSG_MET1S10_TXCH0);
    }
    u1_s_odo_pr_om_fl = u1_t_pr_om_fl;
}

/*===================================================================================================================================*/
/*  U1    u1_g_OdoCfgGetOmRstSts(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_OdoCfgGetOmRstSts(void)
{
    return(u1_s_odo_om_rststs);
}


/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     9/18/2018  TN       New.                                                                                               */
/*  1.1.0     5/29/2019  TN       odo_km, odo_nvmif_odo_km, odo_nvmif_trip_km, odo_nvmif_km v1.0.0 -> v1.1.0.                        */
/*  1.2.0    12/20/2019  TN       odo_nvmif_odo_km.c v1.1.0 -> v1.2.0.                                                               */
/*  1.2.1    05/14/2020  YN       odo_nvmif_odo_km.c & odo_nvmif_trip_km.c v1.2.0 -> v1.2.1.                                         */
/*  1.3.0     8/20/2020  TN       odo_km.c v1.2.0 -> v1.3.0.                                                                         */
/*  1.3.1    07/27/2020  YN       Add ODO/TRIP_A/TRIP_B transmit value control                                                       */
/*                                vd_g_OdoNvmIfCfgOdoWriCmplt delete                                                                 */
/*  1.3.2    08/18/2020  YN       odo_nvmif_km.c v1.3.1 -> v1.3.2                                                                    */
/*  2.0.1    10/18/2021  TA(M)    odo_km.c v1.3.2 -> v2.0.1.                                                                         */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    02/26/2020  YN       Transmission handling of ODO_01 and ODO_UNI2 addition                                              */
/*  19PFv3-1 10/03/2023  SH       Remove unnecessary config and rename config_t300d_met to config                                    */
/*  19PFv3-2  2/23/2024  DR       Changed function presence of TMNT                                                                  */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * YN   = Yasuhiro Nakamura, Denso Techno                                                                                         */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
