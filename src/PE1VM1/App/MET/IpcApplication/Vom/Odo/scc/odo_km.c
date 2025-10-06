/* 2.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Odo                                                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ODO_KM_C_MAJOR                           (2)
#define ODO_KM_C_MINOR                           (0)
#define ODO_KM_C_PATCH                           (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "odo_km_cfg_private.h"
#include "odo_nvmif.h"
#include "odo_nvmif_km.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ODO_KM_C_MAJOR != ODO_KM_H_MAJOR) || \
     (ODO_KM_C_MINOR != ODO_KM_H_MINOR) || \
     (ODO_KM_C_PATCH != ODO_KM_H_PATCH))
#error "odo_km.c and odo_km.h : source and header files are inconsistent!"

#endif
#if ((ODO_KM_C_MAJOR != ODO_KM_CFG_H_MAJOR) || \
     (ODO_KM_C_MINOR != ODO_KM_CFG_H_MINOR) || \
     (ODO_KM_C_PATCH != ODO_KM_CFG_H_PATCH))
#error "odo_km.c and odo_km_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((ODO_KM_C_MAJOR != ODO_NVMIF_H_MAJOR) || \
     (ODO_KM_C_MINOR != ODO_NVMIF_H_MINOR) || \
     (ODO_KM_C_PATCH != ODO_NVMIF_H_PATCH))
#error "odo_km.c and odo_nvmif.h : source and header files are inconsistent!"
#endif

#if ((ODO_KM_C_MAJOR != ODO_NVMIF_KM_H_MAJOR) || \
     (ODO_KM_C_MINOR != ODO_NVMIF_KM_H_MINOR) || \
     (ODO_KM_C_PATCH != ODO_NVMIF_KM_H_PATCH))
#error "odo_km.c and odo_nvmif_km.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ODO_KM_NUM_LAST                          (3U)
#define ODO_KM_NUM_BRA                           (2U)

#define ODO_KM_LAST_IDX_BRA_0                    (0U)
#define ODO_KM_LAST_IDX_BRA_1                    (1U)
#define ODO_KM_LAST_IDX_NVM                      (2U)

#define ODO_LAST_NUM_CHK                         (8U)
#define ODO_LAST_CHK_BRA_0_UNK                   (0x01U)
#define ODO_LAST_CHK_BRA_1_UNK                   (0x02U)
#define ODO_LAST_CHK_NVM_UNK                     (0x04U)
#define ODO_LAST_CHK_1_GT_0                      (0x04U)

#define ODO_NVM_NUM_CHK                          (8U)
#define ODO_NVM_CHK_WRI_NEXT                     (0x01U)
#define ODO_NVM_CHK_REQ_TOUT                     (0x02U)

#define ODO_NVM_REQ_NUM_STS                      (4U)
#define ODO_NVM_REQ_NOTH                         (0U)
#define ODO_NVM_REQ_SYN_LAST                     (1U)
#define ODO_NVM_REQ_WRI_NEXT                     (2U)
#define ODO_NVM_REQ_INIT                         (3U)

#define ODO_NVM_REQ_ACT_TO_NOTH                  (0U)
#define ODO_NVM_REQ_ACT_TO_WRI_NEXT              (1U)
#define ODO_NVM_REQ_ACT_WRI_NEXT                 (2U)
#define ODO_NVM_REQ_ACT_TO_SYN_LAST              (3U)
#define ODO_NVM_REQ_ACT_SYN_LAST                 (4U)
#define ODO_NVM_REQ_ACT_TO_SYN_INIT              (5U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_ODO_KM          st_s_odo_km_bra_0        __attribute__((section(".bss_BACK_ODO_0")));
static ST_ODO_KM          st_s_odo_km_bra_1        __attribute__((section(".bss_BACK_ODO_1")));
static ST_ODO_KM          st_s_odo_km_nvm;

static U4                 u4_s_odo_km_inst;       /*  1/5096km        */
static U2                 u2_s_odo_trip_tocnt;

static U2                 u2_s_odo_nvm_req_tocnt;
static U1                 u1_s_odo_nvm_req_ctrl;

static U1                 u1_s_odo_trip_manu_reset;

static ST_ODO_KM * const stp_sp_ODO_KM_LAST[ODO_KM_NUM_LAST] = {
    &st_s_odo_km_bra_0,
    &st_s_odo_km_bra_1,
    &st_s_odo_km_nvm
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_OdoBraInit(void);
static U1      u1_s_OdoLastchk(const U4 u4_a_NUM_CHK);
static U1      u1_s_OdoLast(const U1 u1_a_LAST_CHK, ST_ODO_KM * stp_a_km_last);
static void    vd_s_OdoNext(const U4 u4_a_INST_KM, ST_ODO_KM * stp_a_km_next);
static void    vd_s_OdoBraUpdt(const U1 u1_a_LAST, const ST_ODO_KM * stp_a_KM_NEXT);
static void    vd_s_OdoNvmReqCtrl(const U1 u1_a_LAST_CHK, const ST_ODO_KM * stp_a_KM_NEXT);
static void    vd_s_OdoTripUnk(void);
static void    vd_s_OdoTripUpdt(const ST_ODO_KM * stp_a_ODO_NEXT);
static U4      u4_s_OdoTripDiM(const ST_ODO_KM * st_ap_ODO_KM, const ST_ODO_TRIP_KM * st_ap_TRIP_KM);
static void    vd_s_OdoTripResetTOchk(const ST_ODO_KM * stp_a_ODO_NEXT);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_OdoBonInit(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoBonInit(void)
{
    vd_s_OdoBraInit();
    vd_g_OdoCfgBonInit(st_s_odo_km_bra_0.u4_ge_m);
}
/*===================================================================================================================================*/
/*  void    vd_g_OdoRstwkInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoRstwkInit(void)
{
    static const U1      u1_sp_ODO_LAST_INIT[ODO_LAST_NUM_CHK] = {
        (U1)ODO_KM_LAST_IDX_BRA_0,
        (U1)ODO_KM_LAST_IDX_BRA_1,
        (U1)ODO_KM_LAST_IDX_BRA_0,
        (U1)U1_MAX,
        (U1)ODO_KM_LAST_IDX_BRA_1,
        (U1)U1_MAX,
        (U1)U1_MAX,
        (U1)U1_MAX
    };

    ST_ODO_KM            st_t_km_last;
    U1                   u1_t_last;
    U1                   u1_t_last_chk;
    U1                   u1_t_cmpr;

    u1_t_last_chk = u1_s_OdoLastchk((U4)ODO_KM_NUM_BRA);
    if(u1_t_last_chk == (U1)0U){

        u1_t_cmpr = u1_g_OdoNvmIfCmprAwB(&st_s_odo_km_bra_1, &st_s_odo_km_bra_0);
        if(u1_t_cmpr == (U1)ODO_KM_CMPR_A_GT_B){
            u1_t_last_chk |= (U1)ODO_LAST_CHK_1_GT_0;
        }
    }

    u1_t_last = u1_sp_ODO_LAST_INIT[u1_t_last_chk];
    if(u1_t_last < (U1)ODO_KM_NUM_BRA){

        st_s_odo_km_nvm.u4_ge_m  = (U4)ODO_KM_UNK;
        st_s_odo_km_nvm.u4_lt_m  = (U4)ODO_KM_UNK;
        st_s_odo_km_nvm.u4_crc32 = (U4)ODO_KM_UNK;

        u4_s_odo_km_inst         = (U4)0U;

        u2_s_odo_nvm_req_tocnt   = (U2)U2_MAX;
        u1_s_odo_nvm_req_ctrl    = (U1)ODO_NVM_REQ_INIT;

        vd_g_OdoNvmIfOdoInit((U1)FALSE);
        vd_g_OdoNvmIfTripInit((U1)FALSE);

        st_t_km_last.u4_ge_m     = stp_sp_ODO_KM_LAST[u1_t_last]->u4_ge_m;
        st_t_km_last.u4_lt_m     = stp_sp_ODO_KM_LAST[u1_t_last]->u4_lt_m;
        st_t_km_last.u4_crc32    = stp_sp_ODO_KM_LAST[u1_t_last]->u4_crc32;

        vd_s_OdoBraUpdt(u1_t_last, &st_t_km_last);      /* st_s_odo_km_bra_[n] are initialized                         */

        u2_s_odo_trip_tocnt      = (U2)U2_MAX;
        u1_s_odo_trip_manu_reset = (U1)0U;

        vd_s_OdoTripUpdt(&st_t_km_last);
    }
    else{
        vd_s_OdoBraInit();
    }

    vd_g_OdoCfgRstwkInit(st_s_odo_km_bra_0.u4_ge_m);
}
/*===================================================================================================================================*/
/*  void    vd_g_OdoMainTask(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoMainTask(void)
{
    ST_ODO_KM            st_t_km_next;
    U4                   u4_t_inst_km;
    U1                   u1_t_last_chk;
    U1                   u1_t_last;

    vd_g_OdoCfgMainStart();

    st_t_km_next.u4_ge_m   = (U4)ODO_KM_UNK;
    st_t_km_next.u4_lt_m   = (U4)ODO_KM_UNK;
    st_t_km_next.u4_crc32  = (U4)ODO_KM_UNK;

    u4_t_inst_km = u4_g_OdoCfgInstPerKm();
    if(u4_t_inst_km >= (U4)ODO_MIN_PER_KM){

        u1_t_last_chk = u1_s_OdoLastchk((U4)ODO_KM_NUM_LAST);
        u1_t_last     = u1_s_OdoLast(u1_t_last_chk, &st_t_km_next);

        vd_s_OdoNext(u4_t_inst_km, &st_t_km_next);
        vd_s_OdoBraUpdt(u1_t_last, &st_t_km_next);
        vd_s_OdoNvmReqCtrl(u1_t_last_chk,  &st_t_km_next);
    }
    else{
        u1_t_last        = (U1)U1_MAX;
        u4_s_odo_km_inst = (U4)0U;

        vd_s_OdoBraUpdt(u1_t_last, &st_t_km_next);
    }

    if(u1_t_last < (U1)ODO_KM_NUM_LAST){

        vd_s_OdoTripUpdt(&st_t_km_next);
        vd_s_OdoTripResetTOchk(&st_t_km_next);
    }
    else{
        vd_s_OdoTripUnk();
    }

    vd_g_OdoCfgMainFinish(st_t_km_next.u4_ge_m);
}
/*===================================================================================================================================*/
/*  void    vd_g_OdoInst(const U4 u4_a_INST, const U1 u1_a_STSBIT)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoInst(const U4 u4_a_INST)
{
    if(((U4)U4_MAX - u4_a_INST) > u4_s_odo_km_inst){
        u4_s_odo_km_inst += u4_a_INST;/* QAC over-detection */
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoBraInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoBraInit(void)
{
    U1                   u1_t_nvm_unk;

    st_s_odo_km_nvm.u4_ge_m  = (U4)ODO_KM_UNK;
    st_s_odo_km_nvm.u4_lt_m  = (U4)ODO_KM_UNK;
    st_s_odo_km_nvm.u4_crc32 = (U4)ODO_KM_UNK;

    vd_s_OdoTripUnk();                                     /* following variables are initialized at here                 */
                                                           /*  u2_s_odo_trip_tocnt                                        */
                                                           /*  u1_s_odo_trip_manu_reset                                   */
                                                           /*  st_gp_odo_trip_km[]                                        */
    u4_s_odo_km_inst         = (U4)0U;

    u2_s_odo_nvm_req_tocnt   = (U2)U2_MAX;
    u1_s_odo_nvm_req_ctrl    = (U1)ODO_NVM_REQ_INIT;

    vd_g_OdoNvmIfOdoInit((U1)TRUE);                        /* st_s_odo_km_nvm is initialized with NVM record at here      */
    vd_g_OdoNvmIfTripInit((U1)TRUE);                       /* st_gp_odo_trip_km[] are initialized with NVM record at here */

    vd_s_OdoBraUpdt((U1)U1_MAX, &st_s_odo_km_nvm);         /* st_s_odo_km_bra_[n] are initialized                         */

    u1_t_nvm_unk = u1_g_OdoNvmIfKmUnk(&st_s_odo_km_nvm);
    if(u1_t_nvm_unk == (U1)FALSE){
        vd_s_OdoTripUpdt(&st_s_odo_km_nvm);
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_OdoLastchk(const U4 u4_a_NUM_CHK)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_OdoLastchk(const U4 u4_a_NUM_CHK)
{
    U4                   u4_t_lpcnt;
    U1                   u1_t_last_chk;
    U1                   u1_t_unk;

    u1_t_last_chk = (U1)0U;
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < u4_a_NUM_CHK; u4_t_lpcnt++){
        u1_t_unk = u1_g_OdoNvmIfKmUnk(stp_sp_ODO_KM_LAST[u4_t_lpcnt]) ;
        u1_t_last_chk |= (U1)((u1_t_unk & (U1)TRUE) << u4_t_lpcnt);
    }

    return(u1_t_last_chk);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_OdoLast(const U1 u1_a_LAST_CHK, ST_ODO_KM * stp_a_km_last)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_OdoLast(const U1 u1_a_LAST_CHK, ST_ODO_KM * stp_a_km_last)
{
    static const U1      u1_sp_ODO_LAS_SEL[ODO_LAST_NUM_CHK] = {
        (U1)ODO_KM_LAST_IDX_BRA_0,
        (U1)ODO_KM_LAST_IDX_BRA_1,
        (U1)ODO_KM_LAST_IDX_BRA_0,
        (U1)ODO_KM_LAST_IDX_NVM,
        (U1)ODO_KM_LAST_IDX_BRA_0,
        (U1)ODO_KM_LAST_IDX_BRA_1,
        (U1)ODO_KM_LAST_IDX_BRA_0,
        (U1)U1_MAX
    };

    U1                   u1_t_last;
    U1                   u1_t_cmpr;

    u1_t_last = u1_sp_ODO_LAS_SEL[u1_a_LAST_CHK];
    if(u1_a_LAST_CHK < ((U1)ODO_LAST_CHK_BRA_0_UNK | (U1) ODO_LAST_CHK_BRA_1_UNK) ){

        u1_t_cmpr = u1_g_OdoNvmIfCmprAwB(stp_sp_ODO_KM_LAST[u1_t_last], &st_s_odo_km_nvm);
        if(u1_t_cmpr == (U1)ODO_KM_CMPR_A_LT_B){
            u1_t_last = (U1)ODO_KM_LAST_IDX_NVM;
        }
    }

    if(u1_t_last < (U1)ODO_KM_NUM_LAST){
        stp_a_km_last->u4_ge_m  = stp_sp_ODO_KM_LAST[u1_t_last]->u4_ge_m;
        stp_a_km_last->u4_lt_m  = stp_sp_ODO_KM_LAST[u1_t_last]->u4_lt_m;
        stp_a_km_last->u4_crc32 = stp_sp_ODO_KM_LAST[u1_t_last]->u4_crc32;
    }

    return(u1_t_last);
}

/*===================================================================================================================================*/
/*  static void    vd_s_OdoNext(const U4 u4_a_INST_KM, ST_ODO_KM * stp_a_km_next)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoNext(const U4 u4_a_INST_KM, ST_ODO_KM * stp_a_km_next)
{
    U4                   u4_t_ge_m;
    U4                   u4_t_lt_m;
    U4                   u4_t_delta;
    U1                   u1_t_incr_en;

    u1_t_incr_en = u1_g_OdoCfgIncrEn();
    u4_t_ge_m    = stp_a_km_next->u4_ge_m;
    if((u4_s_odo_km_inst >  (U4)0U        ) &&
       (u4_t_ge_m        <  (U4)ODO_KM_MAX) &&
       (u1_t_incr_en     != (U1)FALSE     )){

#if ((U4_MAX - ODO_KM_MAX) < (U4_MAX / ODO_MIN_PER_KM))
#error "odo_km.c : (U4_MAX - ODO_KM_MAX) shall be greater than or equal to (U4_MAX / ODO_MIN_PER_KM)."
#endif
        u4_t_lt_m  = (U4)U4_MAX;
        if(((U4)U4_MAX / (U4)ODO_1_KM) > u4_s_odo_km_inst){
            u4_t_delta = u4_s_odo_km_inst * (U4)ODO_1_KM;
            if(((U4)U4_MAX - stp_a_km_next->u4_lt_m) >= u4_t_delta){
                u4_t_lt_m  = stp_a_km_next->u4_lt_m + u4_t_delta;
            }
        }
        u4_t_delta = u4_t_lt_m / u4_a_INST_KM;
        if(((U4)U4_MAX - u4_t_ge_m) >= u4_t_delta){
            u4_t_ge_m += u4_t_delta;
        }
        else{
            u4_t_ge_m = (U4)U4_MAX;
        }
        if(u4_t_ge_m >= (U4)ODO_KM_MAX){

            stp_a_km_next->u4_ge_m = (U4)ODO_KM_MAX;
            stp_a_km_next->u4_lt_m = (U4)0U;
        }
        else{

            stp_a_km_next->u4_ge_m = u4_t_ge_m;
            stp_a_km_next->u4_lt_m = u4_t_lt_m % u4_a_INST_KM;
        }

        vd_g_OdoNvmIfSetCrc32(stp_a_km_next);
    }

    u4_s_odo_km_inst = (U4)0U;
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoBraUpdt(const U1 u1_a_LAST, const ST_ODO_KM * stp_a_KM_NEXT)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoBraUpdt(const U1 u1_a_LAST, const ST_ODO_KM * stp_a_KM_NEXT)
{
    volatile U4          u4_t_rdbk;
    U1                   u1_t_last;
    U1                   u1_t_idx;

    if(u1_a_LAST > (U1)ODO_KM_LAST_IDX_BRA_1){
        u1_t_last  = (U1)ODO_KM_LAST_IDX_BRA_1;
    }
    else{
        u1_t_last  = u1_a_LAST;
    }

    u1_t_idx = u1_t_last;
    do{

        u1_t_idx                               = (u1_t_idx + (U1)1U) & (U1)ODO_KM_LAST_IDX_BRA_1;

        stp_sp_ODO_KM_LAST[u1_t_idx]->u4_crc32 = (U4)U4_MAX ^ (stp_a_KM_NEXT->u4_crc32);

        stp_sp_ODO_KM_LAST[u1_t_idx]->u4_ge_m  = stp_a_KM_NEXT->u4_ge_m;
        stp_sp_ODO_KM_LAST[u1_t_idx]->u4_lt_m  = stp_a_KM_NEXT->u4_lt_m;
        stp_sp_ODO_KM_LAST[u1_t_idx]->u4_crc32 = stp_a_KM_NEXT->u4_crc32;

        u4_t_rdbk                              = stp_sp_ODO_KM_LAST[u1_t_idx]->u4_crc32;
    }
    while(u1_t_idx != u1_t_last);
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoNvmReqCtrl(const U1 u1_a_LAST_CHK, const ST_ODO_KM * stp_a_KM_NEXT)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoNvmReqCtrl(const U1 u1_a_LAST_CHK, const ST_ODO_KM * stp_a_KM_NEXT)
{
    static const U1      u1_sp_ODO_NVM_REQ_STM[ODO_NVM_NUM_CHK][ODO_NVM_REQ_NUM_STS] = {
        {(U1)ODO_NVM_REQ_ACT_TO_NOTH,    (U1)ODO_NVM_REQ_ACT_TO_NOTH,    (U1)ODO_NVM_REQ_ACT_TO_NOTH,    (U1)ODO_NVM_REQ_ACT_TO_NOTH    },
        {(U1)ODO_NVM_REQ_ACT_TO_WRI_NEXT,(U1)ODO_NVM_REQ_ACT_TO_WRI_NEXT,(U1)ODO_NVM_REQ_ACT_WRI_NEXT,   (U1)ODO_NVM_REQ_ACT_TO_WRI_NEXT},
        {(U1)ODO_NVM_REQ_ACT_TO_NOTH,    (U1)ODO_NVM_REQ_ACT_TO_NOTH,    (U1)ODO_NVM_REQ_ACT_TO_NOTH,    (U1)ODO_NVM_REQ_ACT_TO_NOTH    },
        {(U1)ODO_NVM_REQ_ACT_TO_WRI_NEXT,(U1)ODO_NVM_REQ_ACT_TO_WRI_NEXT,(U1)ODO_NVM_REQ_ACT_TO_WRI_NEXT,(U1)ODO_NVM_REQ_ACT_TO_WRI_NEXT},
        {(U1)ODO_NVM_REQ_ACT_TO_SYN_LAST,(U1)ODO_NVM_REQ_ACT_SYN_LAST,   (U1)ODO_NVM_REQ_ACT_TO_SYN_LAST,(U1)ODO_NVM_REQ_ACT_TO_SYN_INIT},
        {(U1)ODO_NVM_REQ_ACT_TO_SYN_LAST,(U1)ODO_NVM_REQ_ACT_SYN_LAST,   (U1)ODO_NVM_REQ_ACT_TO_SYN_LAST,(U1)ODO_NVM_REQ_ACT_TO_SYN_INIT},
        {(U1)ODO_NVM_REQ_ACT_TO_SYN_LAST,(U1)ODO_NVM_REQ_ACT_TO_SYN_LAST,(U1)ODO_NVM_REQ_ACT_TO_SYN_LAST,(U1)ODO_NVM_REQ_ACT_TO_SYN_INIT},
        {(U1)ODO_NVM_REQ_ACT_TO_SYN_LAST,(U1)ODO_NVM_REQ_ACT_TO_SYN_LAST,(U1)ODO_NVM_REQ_ACT_TO_SYN_LAST,(U1)ODO_NVM_REQ_ACT_TO_SYN_INIT}
    };

    U1                   u1_t_nvm_chk;
    U1                   u1_t_act;

    if(u1_a_LAST_CHK < (U1)ODO_LAST_CHK_NVM_UNK){
        u1_t_nvm_chk = u1_g_OdoCfgKmNextToNvm(stp_a_KM_NEXT->u4_ge_m, st_s_odo_km_nvm.u4_ge_m) & (U1)ODO_NVM_CHK_WRI_NEXT;
    }
    else{
        u1_t_nvm_chk = u1_a_LAST_CHK & (U1)ODO_LAST_CHK_NVM_UNK;
    }
    if(u2_s_odo_nvm_req_tocnt < (U2)U2_MAX){
        u2_s_odo_nvm_req_tocnt++;
    }
    if(u2_s_odo_nvm_req_tocnt >= u2_g_ODO_NVM_REQ_TOUT){
        u1_t_nvm_chk |= (U1)ODO_NVM_CHK_REQ_TOUT;
    }
    u1_t_act = (U1)ODO_NVM_REQ_ACT_TO_NOTH;
    if(u1_s_odo_nvm_req_ctrl < (U1)ODO_NVM_REQ_NUM_STS){
        u1_t_act = u1_sp_ODO_NVM_REQ_STM[u1_t_nvm_chk][u1_s_odo_nvm_req_ctrl];
    }
    switch(u1_t_act){
        case ODO_NVM_REQ_ACT_TO_WRI_NEXT:
            u1_s_odo_nvm_req_ctrl  = (U1)ODO_NVM_REQ_WRI_NEXT;
            u2_s_odo_nvm_req_tocnt = (U2)0U;
            (void)u1_g_OdoNvmIfOdoRWRqst(stp_a_KM_NEXT);
            break;
        case ODO_NVM_REQ_ACT_WRI_NEXT:
            u1_s_odo_nvm_req_ctrl  = (U1)ODO_NVM_REQ_WRI_NEXT;
            break;
        case ODO_NVM_REQ_ACT_TO_SYN_LAST:
            u1_s_odo_nvm_req_ctrl  = (U1)ODO_NVM_REQ_SYN_LAST;
            u2_s_odo_nvm_req_tocnt = (U2)0U;
            (void)u1_g_OdoNvmIfOdoRWRqst(vdp_PTR_NA);
            break;
        case ODO_NVM_REQ_ACT_SYN_LAST:
            u1_s_odo_nvm_req_ctrl  = (U1)ODO_NVM_REQ_SYN_LAST;
            break;
        case ODO_NVM_REQ_ACT_TO_SYN_INIT:
            u1_s_odo_nvm_req_ctrl  = (U1)ODO_NVM_REQ_SYN_LAST;
            u2_s_odo_nvm_req_tocnt = (U2)0U;
            break;
        default:   /*  ODO_NVM_REQ_ACT_TO_NOTH */
            u1_s_odo_nvm_req_ctrl  = (U1)ODO_NVM_REQ_NOTH;
            u2_s_odo_nvm_req_tocnt = (U2)0U;
            break;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoTripUnk(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoTripUnk(void)
{
    U4                   u4_t_lpcnt;

    u2_s_odo_trip_tocnt      = (U2)U2_MAX;
    u1_s_odo_trip_manu_reset = (U1)0U;

    u4_t_lpcnt               = (U4)0U;
    do{
        st_gp_odo_trip_km[u4_t_lpcnt].u4_ge_m = (U4)ODO_KM_UNK;
        st_gp_odo_trip_km[u4_t_lpcnt].u4_lt_m = (U4)ODO_KM_UNK;
        st_gp_odo_trip_km[u4_t_lpcnt].u4_di_m = (U4)ODO_KM_UNK;
        u4_t_lpcnt++;
        /* Since u4_t_lpcnt is determined whether it is smaller than u1_g_ODO_TRIP_NUM_CH within the while condition,   */
        /* it is not necessary to check the wraparound.                                                                 */
    }
    while(u4_t_lpcnt < (U4)u1_g_ODO_TRIP_NUM_CH);
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoTripUpdt(const ST_ODO_KM * stp_a_ODO_NEXT)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoTripUpdt(const ST_ODO_KM * stp_a_ODO_NEXT)
{
    U4                   u4_t_lpcnt;
    U4                   u4_t_di_m;

    U1                   u1_t_chbit;
    U1                   u1_t_reset;
    U1                   u1_t_bit;
    U1                   u1_t_accpt;

    vd_g_OdoCfgTripMirrCpbk();

    u1_t_chbit = (U1)0x01U;
    u4_t_lpcnt = (U4)0U;
    u1_t_reset = u1_s_odo_trip_manu_reset & u1_g_ODO_TRIP_SYNC_RST_BY_CH;
    do{

        u1_t_bit = u1_t_reset & u1_t_chbit;
        if(u1_t_bit != (U1)0U){
            st_gp_odo_trip_km[u4_t_lpcnt].u4_ge_m = stp_a_ODO_NEXT->u4_ge_m;
            st_gp_odo_trip_km[u4_t_lpcnt].u4_lt_m = stp_a_ODO_NEXT->u4_lt_m;
            st_gp_odo_trip_km[u4_t_lpcnt].u4_di_m = (U4)0U;
            vd_g_OdoCfgTripMirrInit((U1)u4_t_lpcnt, (U1)ODO_TRIP_INIT_BY_MANU_RST);
        }
        else{

            u4_t_di_m = u4_s_OdoTripDiM(stp_a_ODO_NEXT, &st_gp_odo_trip_km[u4_t_lpcnt]);
            u1_t_bit  = u1_g_ODO_TRIP_SYNC_RST_BY_CH & u1_t_chbit;
            if((u4_t_di_m > (U4)ODO_KM_MAX) &&
               (u1_t_bit != (U1)0U        )){
                u1_t_accpt = u1_g_OdoNvmIfTripRWRqst((U1)u4_t_lpcnt, stp_a_ODO_NEXT);
                if(u1_t_accpt == (U1)TRUE){
                    st_gp_odo_trip_km[u4_t_lpcnt].u4_ge_m = stp_a_ODO_NEXT->u4_ge_m;
                    st_gp_odo_trip_km[u4_t_lpcnt].u4_lt_m = stp_a_ODO_NEXT->u4_lt_m;
                    st_gp_odo_trip_km[u4_t_lpcnt].u4_di_m = (U4)0U;
                    vd_g_OdoCfgTripMirrInit((U1)u4_t_lpcnt, (U1)ODO_TRIP_INIT_BY_AUTO_RST);
                }
            }
            else{
                st_gp_odo_trip_km[u4_t_lpcnt].u4_di_m = u4_t_di_m;
            }
        }

        u4_t_lpcnt++;
        /* Since u4_t_lpcnt is determined whether it is smaller than u1_g_ODO_TRIP_NUM_CH within the while condition,   */
        /* it is not necessary to check the wraparound.                                                                 */
        u1_t_chbit <<= 1U;
    }
    while(u4_t_lpcnt < (U4)u1_g_ODO_TRIP_NUM_CH);
}
/*===================================================================================================================================*/
/*  static U4      u4_s_OdoTripDiM(const ST_ODO_KM * st_ap_ODO_KM, const ST_ODO_TRIP_KM * st_ap_TRIP_KM)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_OdoTripDiM(const ST_ODO_KM * st_ap_ODO_KM, const ST_ODO_TRIP_KM * st_ap_TRIP_KM)
{
    U4                   u4_t_di_m;

    u4_t_di_m = (U4)ODO_KM_UNK;
    if((st_ap_ODO_KM->u4_ge_m  <= (U4)ODO_KM_MAX) &&
       (st_ap_TRIP_KM->u4_ge_m <= (U4)ODO_KM_MAX)){

        if((st_ap_ODO_KM->u4_ge_m >  st_ap_TRIP_KM->u4_ge_m) &&
           (st_ap_ODO_KM->u4_lt_m >= st_ap_TRIP_KM->u4_lt_m)){
            u4_t_di_m = (st_ap_ODO_KM->u4_ge_m - st_ap_TRIP_KM->u4_ge_m);
            /* The value of (st_ap_ODO_KM->u4_ge_m - st_ap_TRIP_KM->u4_ge_m) is 1 or more,                      */
            /* because it is checked by st_ap_ODO_KM-> u4_ge_m> st_ap_TRIP_KM-> u4_ge_m                         */
            /* Therefor no need wraparound check. */
        }
        else if((st_ap_ODO_KM->u4_ge_m > st_ap_TRIP_KM->u4_ge_m) &&
                (st_ap_ODO_KM->u4_lt_m < st_ap_TRIP_KM->u4_lt_m)){
            u4_t_di_m = (st_ap_ODO_KM->u4_ge_m - st_ap_TRIP_KM->u4_ge_m) - (U4)1U;
            /* The value of (st_ap_ODO_KM->u4_ge_m - st_ap_TRIP_KM->u4_ge_m) is 1 or more,                      */
            /* because it is checked by st_ap_ODO_KM-> u4_ge_m> st_ap_TRIP_KM-> u4_ge_m                         */
            /* So (st_ap_ODO_KM->u4_ge_m - st_ap_TRIP_KM->u4_ge_m) > (U4)1U, therefor no need wraparound check. */
        }
        else if((st_ap_ODO_KM->u4_ge_m == st_ap_TRIP_KM->u4_ge_m) &&
                (st_ap_ODO_KM->u4_lt_m >= st_ap_TRIP_KM->u4_lt_m)){
            u4_t_di_m = (U4)0U;
        }
        else{
            /*      Nothing     */
        }
    }

    return(u4_t_di_m);
}
/*===================================================================================================================================*/
/*  static void    vd_s_OdoTripResetTOchk(const ST_ODO_KM * stp_a_ODO_NEXT)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_OdoTripResetTOchk(const ST_ODO_KM * stp_a_ODO_NEXT)
{
    U4                   u4_t_lpcnt;

    U1                   u1_t_reset;
    U1                   u1_t_chbit;
    U1                   u1_t_accpt;

    if(u2_s_odo_trip_tocnt < (U2)U2_MAX){
        u2_s_odo_trip_tocnt++;
    }

    if((u2_s_odo_trip_tocnt      >= u2_g_ODO_TRIP_RST_TOUT) &&
       (u1_s_odo_trip_manu_reset != (U1)0U                )){

        u4_t_lpcnt = (U4)0U;
        u1_t_reset = u1_s_odo_trip_manu_reset;
        do{

            u1_t_chbit = u1_t_reset & (U1)((U1)0x01U << u4_t_lpcnt);
            if(u1_t_chbit != (U1)0U){
                u1_t_accpt = u1_g_OdoNvmIfTripRWRqst((U1)u4_t_lpcnt, stp_a_ODO_NEXT);
                if(u1_t_accpt == (U1)TRUE){
                    u1_t_reset &= ((U1)U1_MAX ^ u1_t_chbit);
                }
            }
            u4_t_lpcnt++;
            /* Since u4_t_lpcnt is determined whether it is smaller than u1_g_ODO_TRIP_NUM_CH within the while condition,   */
            /* it is not necessary to check the wraparound.                                                                 */
        }
        while(u4_t_lpcnt < (U4)u1_g_ODO_TRIP_NUM_CH);

        u1_s_odo_trip_manu_reset = u1_t_reset;
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_OdoKm( U4 * u4p_a_0p001km)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_OdoKm(U4 * u4p_a_0p001km)
{
    U1                   u1_t_stsbit;

    u1_t_stsbit = (U1)ODO_STSBIT_UNKNOWN;
    if(st_s_odo_km_bra_0.u4_ge_m <= (U4)ODO_KM_MAX){

        u1_t_stsbit = (U1)ODO_STSBIT_VALID;
        if(u4p_a_0p001km != vdp_PTR_NA){
            (*u4p_a_0p001km) = st_s_odo_km_bra_0.u4_ge_m;
        }
    }

    return(u1_t_stsbit);
}

/*===================================================================================================================================*/
/*  U1      u1_g_OdoMile( U4 * u4p_a_0p001mile)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_OdoMile(U4 * u4p_a_0p001mile)
{
    U1                   u1_t_stsbit;

    u1_t_stsbit = (U1)ODO_STSBIT_UNKNOWN;
    if(st_s_odo_km_bra_0.u4_ge_m <= (U4)ODO_KM_MAX){

        u1_t_stsbit = (U1)ODO_STSBIT_VALID;
        if(u4p_a_0p001mile != vdp_PTR_NA){
            (*u4p_a_0p001mile) = u4_g_UnitconvtrKmtoMi(st_s_odo_km_bra_0.u4_ge_m);
        }
    }

    return(u1_t_stsbit);
}

/*===================================================================================================================================*/
/*  U1      u1_g_OdoKmMileByUnit( U4 * u4p_a_0p001kmmile)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_OdoKmMileByUnit(U4 * u4p_a_0p001kmmile)
{
    U1                   u1_t_stsbit;
    U1                   u1_t_unit;

    u1_t_stsbit = (U1)ODO_STSBIT_UNKNOWN;
    if(st_s_odo_km_bra_0.u4_ge_m <= (U4)ODO_KM_MAX){
        u1_t_stsbit = (U1)ODO_STSBIT_VALID;
        if(u4p_a_0p001kmmile != vdp_PTR_NA){
#if 0   /* BEV Rebase provisionally */
            u1_t_unit = u1_g_Unit((U1)UNIT_IDX_DIST);
            if(u1_t_unit == (U1)UNIT_VAL_DIST_MILE){
#else   /* BEV Rebase provisionally */
            u1_t_unit = (U1)0U;
            if(u1_t_unit == (U1)1U){
#endif   /* BEV Rebase provisionally */
                (*u4p_a_0p001kmmile) = u4_g_UnitconvtrKmtoMi(st_s_odo_km_bra_0.u4_ge_m);
            }else{
                (*u4p_a_0p001kmmile) = st_s_odo_km_bra_0.u4_ge_m;
            }
        }
    }

    return(u1_t_stsbit);
}

/*===================================================================================================================================*/
/*  void    vd_g_OdoTripReset(const U1 u1_a_CH, const U1 u1_a_ACT)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoTripReset(const U1 u1_a_CH, const U1 u1_a_ACT)
{
    U1                   u1_t_chbit;
    U1                   u1_t_accpt;
    U1                   u1_t_reset;
    U1                   u1_t_bit;
    U1                   u1_t_syncbit;

    if(st_s_odo_km_bra_0.u4_ge_m <= (U4)ODO_KM_MAX){

        u1_t_reset   = u1_s_odo_trip_manu_reset;
        u1_t_chbit   = (U1)0x01U << u1_a_CH;
        u1_t_bit     = u1_t_reset & u1_t_chbit;
        u1_t_syncbit = u1_g_ODO_TRIP_SYNC_RST_BY_CH & u1_t_chbit;
        
        if(u1_a_ACT == (U1)TRUE){
            u2_s_odo_trip_tocnt  = (U2)0U;
            u1_t_reset          |= u1_t_chbit;
        }
        else if(u1_t_bit != (U1)0U){
            u2_s_odo_trip_tocnt = (U2)U2_MAX;
            u1_t_accpt          = u1_g_OdoNvmIfTripRWRqst(u1_a_CH, &st_s_odo_km_bra_0);
            if(u1_t_accpt == (U1)TRUE){
                u1_t_reset &= ((U1)U1_MAX ^ u1_t_chbit);
            }
        }
        else{
            /*  Nothing */
        }

        if((u1_t_syncbit         != (U1)0U                ) &&
           ((u1_t_bit != (U1)0U) || (u1_a_ACT == (U1)TRUE))){

            st_gp_odo_trip_km[u1_a_CH].u4_ge_m = st_s_odo_km_bra_0.u4_ge_m;
            st_gp_odo_trip_km[u1_a_CH].u4_lt_m = st_s_odo_km_bra_0.u4_lt_m;
            st_gp_odo_trip_km[u1_a_CH].u4_di_m = (U4)0U;

            vd_g_OdoCfgTripMirrInit(u1_a_CH, (U1)ODO_TRIP_INIT_BY_MANU_RST);
        }

        u1_s_odo_trip_manu_reset = u1_t_reset;
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_OdoTripKm(const U1 u1_a_CH, U4 * u4p_a_0p001km)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_OdoTripKm(const U1 u1_a_CH, U4 * u4p_a_0p001km)
{
    U1                   u1_t_stsbit;

    u1_t_stsbit = (U1)ODO_STSBIT_UNKNOWN;
    if((u1_a_CH                            <  u1_g_ODO_TRIP_NUM_CH) &&
       (st_gp_odo_trip_km[u1_a_CH].u4_di_m <= (U4)ODO_KM_MAX      )){

        u1_t_stsbit = (U1)ODO_STSBIT_VALID;
        if(u4p_a_0p001km != vdp_PTR_NA){
            (*u4p_a_0p001km) = st_gp_odo_trip_km[u1_a_CH].u4_di_m;
        }
    }

    return(u1_t_stsbit);
}

/*===================================================================================================================================*/
/*  U1      u1_g_OdoTripMile(const U1 u1_a_CH, U4 * u4p_a_0p001mile)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_OdoTripMile(const U1 u1_a_CH, U4 * u4p_a_0p001mile)
{
    U1                   u1_t_stsbit;

    u1_t_stsbit = (U1)ODO_STSBIT_UNKNOWN;
    if((u1_a_CH                            <  u1_g_ODO_TRIP_NUM_CH) &&
       (st_gp_odo_trip_km[u1_a_CH].u4_di_m <= (U4)ODO_KM_MAX      )){

        u1_t_stsbit = (U1)ODO_STSBIT_VALID;
        if(u4p_a_0p001mile != vdp_PTR_NA){
            (*u4p_a_0p001mile) = u4_g_UnitconvtrKmtoMi(st_gp_odo_trip_km[u1_a_CH].u4_di_m);
        }
    }

    return(u1_t_stsbit);
}

/*===================================================================================================================================*/
/*  U1      u1_g_OdoTripKmMileByUnit(const U1 u1_a_CH, U4 * u4p_a_0p001kmmile)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_OdoTripKmMileByUnit(const U1 u1_a_CH, U4 * u4p_a_0p001kmmile)
{
    U1                   u1_t_stsbit;
    U1                   u1_t_unit;

    u1_t_stsbit = (U1)ODO_STSBIT_UNKNOWN;
    if((u1_a_CH                            <  u1_g_ODO_TRIP_NUM_CH) &&
       (st_gp_odo_trip_km[u1_a_CH].u4_di_m <= (U4)ODO_KM_MAX      )){

        u1_t_stsbit = (U1)ODO_STSBIT_VALID;
        if(u4p_a_0p001kmmile != vdp_PTR_NA){
#if 0   /* BEV Rebase provisionally */
            u1_t_unit = u1_g_Unit((U1)UNIT_IDX_DIST);
            if(u1_t_unit == (U1)UNIT_VAL_DIST_MILE){
#else   /* BEV Rebase provisionally */
            u1_t_unit = (U1)0U;
            if(u1_t_unit == (U1)1U){
#endif   /* BEV Rebase provisionally */
                (*u4p_a_0p001kmmile) = u4_g_UnitconvtrKmtoMi(st_gp_odo_trip_km[u1_a_CH].u4_di_m);
            }else{
                (*u4p_a_0p001kmmile) = st_gp_odo_trip_km[u1_a_CH].u4_di_m;
            }
        }
    }

    return(u1_t_stsbit);
}

/*===================================================================================================================================*/
/*  void    vd_g_OdoNvmIfCbkOdoKm(const ST_ODO_KM * st_ap_KM_NVM)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoNvmIfCbkOdoKm(const ST_ODO_KM * st_ap_KM_NVM)
{
    st_s_odo_km_nvm.u4_ge_m  = st_ap_KM_NVM->u4_ge_m;
    st_s_odo_km_nvm.u4_lt_m  = st_ap_KM_NVM->u4_lt_m;
    st_s_odo_km_nvm.u4_crc32 = st_ap_KM_NVM->u4_crc32;
}
/*===================================================================================================================================*/
/*  void    vd_g_OdoNvmIfCbkTripKm(const U1 u1_a_SYNC, const U1 u1_a_CH, const ST_ODO_KM * st_ap_KM_NVM)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_OdoNvmIfCbkTripKm(const U1 u1_a_SYNC, const U1 u1_a_CH, const ST_ODO_KM * st_ap_KM_NVM)
{
    U1                   u1_t_chbit;

    if(u1_a_CH < u1_g_ODO_TRIP_NUM_CH){

        u1_t_chbit = u1_g_ODO_TRIP_SYNC_RST_BY_CH & (U1)((U1)0x01U << u1_a_CH);
        if((u1_a_SYNC  == (U1)TRUE) ||
           (u1_t_chbit == (U1)0U  )){

            st_gp_odo_trip_km[u1_a_CH].u4_ge_m = st_ap_KM_NVM->u4_ge_m;
            st_gp_odo_trip_km[u1_a_CH].u4_lt_m = st_ap_KM_NVM->u4_lt_m;

            vd_g_OdoCfgTripOmRstJdg(u1_a_CH);
            vd_g_OdoCfgTripMirrInit(u1_a_CH, (U1)ODO_TRIP_INIT_BY_NVM_RDBK);
        }
    }
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    10/ 9/2018  AK       New.                                                                                               */
/*  1.1.0     5/31/2019  TN       vd_g_OdoBonInit was optimized.                                                                     */
/*  1.2.0    12/20/2019  TN       odo_nvmif_odo_km.c v1.1.0 -> v1.2.0.                                                               */
/*  1.2.1    05/14/2020  YN       odo_nvmif_odo_km.c & odo_nvmif_trip_km.c v1.2.0 -> v1.2.1.                                         */
/*  1.3.0     8/20/2020  TN       u4_g_OdoCfgInstToLtM(..) -> u1_g_OdoCfgIncrEn().                                                   */
/*                                u4_g_ODO_INST_TO_KM  -> u4_g_OdoCfgInstPerKm()                                                     */
/*  1.3.1    07/27/2020  YN       Fixed a judgment error in the initialization process when resetting.                               */
/*                                Add Suffix                                                                                         */
/*  1.3.2    08/18/2020  YN       odo_nvmif_km.c v1.3.1 -> v1.3.2                                                                    */
/*  2.0.1    10/18/2021  TA(M)    Change the definition of the null pointer used.(BSW v115_r007)                                     */
/*                                                                                                                                   */
/*  * AK   = Aiko Kishino, Denso                                                                                                     */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*  * YN   = Yasuhiro Nakamura, Denso Techno                                                                                         */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
