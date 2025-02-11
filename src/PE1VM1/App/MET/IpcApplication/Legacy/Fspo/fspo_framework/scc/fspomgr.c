/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  F-Spo Manager                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define FSPOMGR_C_MAJOR                          (1)
#define FSPOMGR_C_MINOR                          (0)
#define FSPOMGR_C_PATCH                          (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "fspomgr_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((FSPOMGR_C_MAJOR != FSPOMGR_H_MAJOR) || \
     (FSPOMGR_C_MINOR != FSPOMGR_H_MINOR) || \
     (FSPOMGR_C_PATCH != FSPOMGR_H_PATCH))
#error "fspomgr.c and fspomgr.h : source and header files are inconsistent!"
#endif

#if ((FSPOMGR_C_MAJOR != FSPOMGR_CFG_H_MAJOR) || \
     (FSPOMGR_C_MINOR != FSPOMGR_CFG_H_MINOR) || \
     (FSPOMGR_C_PATCH != FSPOMGR_CFG_H_PATCH))
#error "fspomgr.c and fspomgr_cfg_private.h : source and parameter files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static        void     vd_s_FspomgrIgon(void);
static        void     vd_s_FspomgrIgoff(void);
static        U2       u2_s_FspomgrChkEvt(void);
static        void     vd_s_FspomgrTrnst(const ST_FSPO_ITEMCFG* st_ap_FSPO_INFTBL, U2 u2_a_evtbit);
static        void     vd_s_FspomgrExeCal(const ST_FSPO_ITEMCFG* st_ap_FSPO_INFTBL);
static        U1       u1_s_FspomgrGetFspoSup(void);
static inline U1       u1_s_FspomgrCalibU1NumChk(const U1 u1_a_CALIBID, const U1 u1_a_NUM, const U1 u1_a_DEF);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_FspomgrBonInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FspomgrBonInit(void)
{
    const ST_FSPO_ITEMCFG*  st_tp_fspo_inftbl;
    U1                      u1_t_loopcnt;

    st_tp_fspo_inftbl = &st_sp_FSPO_ITEMCFG[0];

    vd_FSPOMGR_SNSR_BON();
    vd_FSPOMGR_CMN_BON();

    for(u1_t_loopcnt = (U1)0U; u1_t_loopcnt < (U1)FSPO_ITEM_MAX; u1_t_loopcnt++){
        if(st_tp_fspo_inftbl[u1_t_loopcnt].fp_vd_BONFUNC != vdp_PTR_NA){
            (st_tp_fspo_inftbl[u1_t_loopcnt].fp_vd_BONFUNC)();
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_FspomgrWkupInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FspomgrWkupInit(void)
{
    const ST_FSPO_ITEMCFG*  st_tp_fspo_inftbl;
    U1                      u1_t_loopcnt;

    st_tp_fspo_inftbl = &st_sp_FSPO_ITEMCFG[0];

    vd_FSPOMGR_SNSR_WKUP();
    vd_FSPOMGR_CMN_WKUP();

    for(u1_t_loopcnt = (U1)0U; u1_t_loopcnt < (U1)FSPO_ITEM_MAX; u1_t_loopcnt++){
        if(st_tp_fspo_inftbl[u1_t_loopcnt].fp_vd_WKUPFUNC != vdp_PTR_NA){
            (st_tp_fspo_inftbl[u1_t_loopcnt].fp_vd_WKUPFUNC)();
        }
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_FspoOpemdEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVBIT)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FspoOpemdEvhk(const U4 u4_a_MDBIT, const U4 u4_a_EVBIT)
{
    U4                      u4_t_ign_chk;
#if 0   /* BEV BSW provisionally */
    u4_t_ign_chk = u4_a_EVBIT & ((U4)VEH_OPEMD_EVTBIT_IGN_TO_ON  |
                                 (U4)VEH_OPEMD_EVTBIT_IGN_TO_OFF  );

    if(u4_t_ign_chk == (U4)VEH_OPEMD_EVTBIT_IGN_TO_ON){
        vd_s_FspomgrIgon();
    }
    else if(u4_t_ign_chk == (U4)VEH_OPEMD_EVTBIT_IGN_TO_OFF){
        vd_s_FspomgrIgoff();
    }
    else{
        /* Nothing */
    }
#else
    u4_t_ign_chk = u4_a_EVBIT & ((U4)0x00002020U);
    
    if(u4_t_ign_chk == (U4)0x00000020U){
        vd_s_FspomgrIgon();
    }
    else if(u4_t_ign_chk == (U4)0x00002000U){
        vd_s_FspomgrIgoff();
    }
    else{
        /* Nothing */
    }
#endif
}

/*===================================================================================================================================*/
/*  static void     vd_s_FspomgrIgon(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_FspomgrIgon(void)
{
    vd_FSPOMGR_SNSR_IGON();
    vd_FSPOMGR_CMN_IGON();
}

/*===================================================================================================================================*/
/*  static void     vd_s_FspomgrIgoff(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_FspomgrIgoff(void)
{
    vd_FSPOMGR_SNSR_IGOFF();
    vd_FSPOMGR_CMN_IGOFF();
}

/*===================================================================================================================================*/
/*  void    vd_g_FspomgrRoutine(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FspomgrRoutine(void)
{
    const ST_FSPO_ITEMCFG*  st_tp_fspo_inftbl;
    U2                      u2_t_evtbit;

    u2_t_evtbit = (U2)0U;

    st_tp_fspo_inftbl = &st_sp_FSPO_ITEMCFG[0];

    vd_FSPOMGR_CMN_SIGUPDT();

    u2_t_evtbit = u2_s_FspomgrChkEvt();
    vd_s_FspomgrTrnst(st_tp_fspo_inftbl, u2_t_evtbit);
    vd_s_FspomgrExeCal(st_tp_fspo_inftbl);
}

/*===================================================================================================================================*/
/*  void vd_g_FspomgrEventInc(const ST_FSPOSNSR_INCARG* stp_a_INCARG)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const ST_FSPOSNSR_INCARG* stp_a_INCARG                                                                           */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_FspomgrEventInc(const ST_FSPOSNSR_INCARG* stp_a_INCARG)
{
    const ST_FSPO_ITEMCFG*  st_tp_fspo_inftbl;
    U1                      u1_t_loopcnt;
    U1                      u1_t_supd_sts;
    U1                      u1_t_supd_msk;

    st_tp_fspo_inftbl = &st_sp_FSPO_ITEMCFG[0];
    u1_t_supd_sts     = u1_s_FspomgrGetFspoSup();
    
    for(u1_t_loopcnt = (U1)0U; u1_t_loopcnt < (U1)FSPO_ITEM_MAX; u1_t_loopcnt++){
        u1_t_supd_msk = st_tp_fspo_inftbl[u1_t_loopcnt].u1_supd_msk;
        if((u1_t_supd_sts & u1_t_supd_msk) != (U1)0U){
            if(st_tp_fspo_inftbl[u1_t_loopcnt].fp_vd_INCFUNC != vdp_PTR_NA){
                (st_tp_fspo_inftbl[u1_t_loopcnt].fp_vd_INCFUNC)(stp_a_INCARG);
            }
        }
    }
}

/*===================================================================================================================================*/
/*  static U2   u2_s_FspomgrChkEvt(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U2 u2_t_evtbit                                                                                                   */
/*===================================================================================================================================*/
static U2   u2_s_FspomgrChkEvt(void)
{
    U2                      u2_t_evtbit;
    U1                      u1_t_jdg;

    u2_t_evtbit = (U2)0U;

    u1_t_jdg = u1_FSPOMGR_IG_ISON();
    if( u1_t_jdg == (U1)TRUE){
        u2_t_evtbit |= (U2)FSPOMGR_IGON_EVT;
    }

    u1_t_jdg = u1_FSPOMGR_OILPRSWRN_ISON();
    if((u1_t_jdg == (U1)FSPOMGR_OILPRE_WRN_WRN_ON  ) 
    || (u1_t_jdg == (U1)FSPOMGR_OILPRE_WRN_WRN_FLSH) 
    || (u1_t_jdg == (U1)FSPOMGR_OILPRE_WRN_WRN_OFF )){
        u2_t_evtbit |= (U2)FSPOMGR_OILPRSWRN_EVT;
    }

    return(u2_t_evtbit);
}

/*===================================================================================================================================*/
/*  static void     vd_s_FspomgrTrnst(const ST_FSPO_ITEMCFG* st_ap_FSPO_INFTBL, U2 u2_a_evtbit)                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const ST_FSPO_ITEMCFG* st_ap_FSPO_INFTBL                                                                         */
/*                  U2                     u2_a_evtbit                                                                               */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_FspomgrTrnst(const ST_FSPO_ITEMCFG* st_ap_FSPO_INFTBL, U2 u2_a_evtbit)
{
    U2                      u2_t_sigfail;
    U1                      u1_t_loopcnt;
    U1                      u1_t_supd_sts;
    U1                      u1_t_supd_msk;

    u2_t_sigfail  = u2_FSPOMGR_GET_SIGSTS();
    u1_t_supd_sts = u1_s_FspomgrGetFspoSup();

    for(u1_t_loopcnt = (U1)0U; u1_t_loopcnt < (U1)FSPO_ITEM_MAX; u1_t_loopcnt++){
        u1_t_supd_msk = st_ap_FSPO_INFTBL[u1_t_loopcnt].u1_supd_msk;
        if((u1_t_supd_sts & u1_t_supd_msk) != (U1)0U){
            if(st_ap_FSPO_INFTBL[u1_t_loopcnt].fp_vd_TRSFUNC != vdp_PTR_NA){
                (st_ap_FSPO_INFTBL[u1_t_loopcnt].fp_vd_TRSFUNC)(u2_a_evtbit, u2_t_sigfail);
            }
        }
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_FspomgrExeCal(const ST_FSPO_ITEMCFG* st_ap_FSPO_INFTBL)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const ST_FSPO_ITEMCFG* st_ap_FSPO_INFTBL                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_FspomgrExeCal(const ST_FSPO_ITEMCFG* st_ap_FSPO_INFTBL)
{
    U1                      u1_t_loopcnt;
    U1                      u1_t_supd_sts;
    U1                      u1_t_supd_msk;

    u1_t_supd_sts = u1_s_FspomgrGetFspoSup();

    for(u1_t_loopcnt = (U1)0U; u1_t_loopcnt < (U1)FSPO_ITEM_MAX; u1_t_loopcnt++){
        u1_t_supd_msk = st_ap_FSPO_INFTBL[u1_t_loopcnt].u1_supd_msk;
        if((u1_t_supd_sts & u1_t_supd_msk)!=(U1)0U){
            if(st_ap_FSPO_INFTBL[u1_t_loopcnt].fp_vd_UPDTFUNC != vdp_PTR_NA){
                (st_ap_FSPO_INFTBL[u1_t_loopcnt].fp_vd_UPDTFUNC)();
            }
        }
        else{
            if(st_ap_FSPO_INFTBL[u1_t_loopcnt].fp_vd_BONFUNC != vdp_PTR_NA){
                (st_ap_FSPO_INFTBL[u1_t_loopcnt].fp_vd_BONFUNC)();
            }
        }
    }
}

/*===================================================================================================================================*/
/*  static U1       u1_s_FspomgrGetFspoSup(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_sup                                                                                                      */
/*===================================================================================================================================*/
static U1       u1_s_FspomgrGetFspoSup(void)
{
    U1                      u1_t_sup;
    U1                      u1_t_brand;
    U1                      u1_t_sports;

    u1_t_sup      = u1_FSPOMGR_GET_FSPO_NOSUPD();
    u1_t_brand    = u1_s_FspomgrCalibU1NumChk(u1_FSPOMGR_CALIB_BRAND,  (U1)CALIB_MCUID0024_NUM, (U1)CALIB_MCUID0024_DEF);
    u1_t_sports   = u1_s_FspomgrCalibU1NumChk(u1_FSPOMGR_CALIB_SPORTS, (U1)CALIB_MCUID0025_NUM, (U1)CALIB_MCUID0025_DEF);

    if(u1_t_brand == (U1)CALIB_MCUID0024_LEXUS){
        u1_t_sup = u1_FSPOMGR_GET_FSPO_SUPD();
    }
    else if((u1_t_sports == (U1)CALIB_MCUID0025_GRMN) ||
            (u1_t_sports == (U1)CALIB_MCUID0025_GR)   ){
        u1_t_sup = u1_FSPOMGR_GET_FSPO_SUPD();
    }else{
        /*u1_t_sup = u1_FSPOMGR_GET_FSPO_NOSUPD();*/
    }
    return(u1_t_sup);
}

/*===================================================================================================================================*/
/*  static inline U1    u1_s_FspomgrCalibU1NumChk(const U1 u1_a_CALIBID, const U1 u1_a_NUM, const U1 u1_a_DEF)                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_CALIBID                                                                                            */
/*                  const U1 u1_a_NUM                                                                                                */
/*                  const U1 u1_a_DEF                                                                                                */
/*  Return:         U1 u1_t_ret                                                                                                      */
/*===================================================================================================================================*/
static inline U1    u1_s_FspomgrCalibU1NumChk(const U1 u1_a_CALIBID, const U1 u1_a_NUM, const U1 u1_a_DEF)
{
    U1 u1_t_ret;

    u1_t_ret = u1_a_CALIBID;
    if(u1_t_ret >= u1_a_NUM){
        u1_t_ret = u1_a_DEF;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author  Change Description                                                                           */
/* ---------------  ----------  ------  -------------------------------------------------------------------------------------------  */
/*  0.0.0           04/15/2013  YK      New.                                                                                         */
/*  0.0.1           05/08/2013  YK      Support for sample software.                                                                 */
/*  0.0.2           05/22/2013  YK      treatment improvement.                                                                       */
/*  0.0.3           11/22/2013  YK      F-SPO variation judgment processing was added.                                               */
/*                                      Hydraulic Abnormality Warning No 390 established I/F was enabled.                            */
/*                                      The results of QAC/PCS3 -2/single unit were reflected.                                       */
/*  0.0.4           06/07/2017  SM      Delete:#pragma segment                                                                       */
/*  0.0.4-310B-1    10/23/2017  SM      Delete:fspo_cmn App                                                                          */
/*  0.0.5           10/22/2018  HT      Delete:function vd_g_FspomgrInitial                                                          */
/*  0.1.0           12/14/2020  SK      OilPressWrn judgment processing changed                                                      */
/*                                      QAC treatment, Add cast to NULL                                                              */
/*  1.0.0           12/13/2021  SK      Add bstpeak process.                                                                         */
/*  1.0.0-19PFv3-1  12/22/2023  TK      Chage specification M_GRGMN-CORG to C_GMN-CSTD.                                              */
/*  1.0.0-19PFv3-2  04/12/2024  SH      Add calibration guard                                                                        */
/*  1.0.0-19PFv3-3  06/27/2024  TN      Delete Calibration Guard Process.                                                            */
/*  1.0.0-19PFv3-4  07/02/2024  KH      Fix calibration macro                                                                        */
/*  1.0.0-19PFv3-5  07/09/2024  KH      Fix calib macro, Remove logic for pressure unit fail event                                   */
/*  1.0.0-19PFv3-6  07/12/2024  TN      Add Calibration Guard to Unify Vehicle Operation.                                            */
/*                                                                                                                                   */
/*  * YK = Yosuke Kawahara, NCOS                                                                                                     */
/*  * SM = Shouhei Matsumoto                                                                                                         */
/*  * HT = Hirotaka Takekoshi, Denso Techno                                                                                          */
/*  * SK = Shintaro Kanou, Denso Techno                                                                                              */
/*  * TK = Toru Kamishina, Denso Techno                                                                                              */
/*  * SH = Sae Hirose, Denso Techno                                                                                                  */
/*  * TN = Tetsushi Nakano, Denso Techno                                                                                             */
/*  * KH = Kiko Huerte, DTPH                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
