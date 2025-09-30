/* 2.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Distance To Empty for Trip Computer, Electric Delay                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DTE_ED_C_MAJOR                        (2)
#define DTE_ED_C_MINOR                        (3)
#define DTE_ED_C_PATCH                        (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "dte_ed_cfg_private.h"

#include "tripcom_calc.h"
#include "tripcom_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DTE_ED_C_MAJOR != DTE_ED_H_MAJOR) || \
     (DTE_ED_C_MINOR != DTE_ED_H_MINOR) || \
     (DTE_ED_C_PATCH != DTE_ED_H_PATCH))
#error "dte_ed.c and dte_ed.h : source and header files are inconsistent!"
#endif

#if ((DTE_ED_C_MAJOR != DTE_ED_CFG_H_MAJOR) || \
     (DTE_ED_C_MINOR != DTE_ED_CFG_H_MINOR) || \
     (DTE_ED_C_PATCH != DTE_ED_CFG_H_PATCH))
#error "dte_ed.c and dte_ed_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CGSTS_BONRDY                        (0U)                               /* 学習燃費 BON状態                                   */
#define CGSTS_SETDEFCG                      (1U)                               /* 学習燃費 デフォルト燃費設定状態                    */
#define CGSTS_FAIL                          (2U)                               /* 学習燃費 FAIL状態                                  */
#define CGSTS_HOLD                          (3U)                               /* 学習燃費 保持状態                                  */
#define CGSTS_RDYUPDT                       (4U)                               /* 学習燃費 更新待ち状態                              */
#define CGSTS_UPDT                          (5U)                               /* 学習燃費 演算状態                                  */

#define CRSSTS_BONRDY                       (0U)                               /* 航続可能距離 BON初回表示待ち状態                   */
#define CRSSTS_BONFAIL                      (1U)                               /* 航続可能距離 BON初回表示待ちフェール状態           */
#define CRSSTS_FAIL                         (2U)                               /* 航続可能距離 FAIL状態                              */
#define CRSSTS_RDY                          (3U)                               /* 航続可能距離 演算待ち状態                          */
#define CRSSTS_RECALRDY                     (4U)                               /* 航続可能距離 再計算待ち状態                        */
#define CRSSTS_CAL                          (5U)                               /* 航続可能距離 演算状態                              */
#define CRSSTS_RECAL                        (6U)                               /* 航続可能距離 再計算状態                            */
#define CRSSTS_MAXSTS                       (6U)                               /* 航続可能距離 最大状態                              */

#define DTE_ED_CGADDMAX                     (0xE6666665U)                      /* U4_MAX x 0.9                                       */

#define DTE_ED_RES_0P1KM_TO_1KM             (10U)                              /* Resolution 0.1 to 1                                */
#define DTE_ED_LOW_CG_0P5_KMPL              (255U)                             /* Low Cg Thresh   0.5[km/l] = 254.8[0.1pls/10cc]     */
#define DTE_ED_CG_WA_NOW                    (1U)                               /* Now CG weighted average                            */
#define DTE_ED_CG_WA_CURRENT                (2U)                               /* Current CG weighted average                        */
#define DTE_ED_CG_WA_TOTAL                  (DTE_ED_CG_WA_NOW + DTE_ED_CG_WA_CURRENT)  /* Total                                      */

/* 燃料使用量 10cc 変換処理     */
#define CRSFCPTO10CC_K                      (20000U)                           /* 10cc相当のB_FC値(固定)                             */
#define CRSFCPTO10CC_RND                    (10000U)                           /* 四捨五入オフセット                                 */

/* 給油間燃費演算用係数         */
#define CRSCG_CNSPCOEF                      (204800000U)                       /* pls,tau -> 0.1pls/10cc演算係数(固定)               */

#define DTE_ED_CALSUB_RDY                   (0U)                               /* 電子遅延 初期演算状態                              */
#define DTE_ED_CALSUB_RUN_DEC               (1U)                               /* 電子遅延 走行減算待ち状態                          */
#define DTE_ED_CALSUB_IDLE_DEC              (2U)                               /* 電子遅延 停車時減算待ち状態                        */
#define DTE_ED_CALSUB_IDLE_DECSTOP          (3U)                               /* 電子遅延 停車時減算停止状態                        */

#define DTE_ED_DSPCOR10CC                   (1500U)                            /* 表示距離補正判定容量 15[L] = 1500[10cc]  [LSB0.1]  */

#define DTE_ED_PLSPNTKM                     (5096U)                            /* 0.1kmあたりのpls数 LSB 0.1                         */

#define DTE_ED_RUN_1S                       (  1000U / 50U)                    /* 走行減算時時間判定 1[s] = 20[50ms]                 */
#define DTE_ED_BLWMETIM_64S                 ( 64000U / 50U)                    /* ME点補正判定時間 64[s] = 1280[50ms]                */
#define DTE_ED_DSPCOR_TIM_128S              (128000U / 50U)                    /* 表示補正判定時間 128[s] = 2560[50ms]               */

#define DTE_ED_KHCOR_RND                    (50U)                              /* 表示距離補正四捨五入オフセット                     */
#define DTE_ED_DSPCOR_SPD                   (2000U)

#define DTE_ED_G_RES                        (100U / DTE_ED_RES_0P1KM_TO_1KM)

#define DTE_ED_SHIFT_03BIT                  (3U)                                /* 1/8                                               */
#define DTE_ED_SHIFT_10BIT                  (10U)

#define DTE_ED_COEF_BASE_100P               (100U)
#define DTE_ED_COEF_BASE_100P_RND           (50U)                               /* Round                                             */

#define DTE_ED_CNSP_RND                     (512U)

#define DTE_ED_CALC_ENA                     (0x8000U)
#define DTE_ED_INC_INVALID                  (0x0001U)
#define DTE_ED_IGON                         (0x0002U)
#define DTE_ED_GFI                          (0x0004U)   /* Gas FIlling                     */
#define DTE_ED_RCM_OOR                      (0x0008U)   /* Rental Car Mode or Out Of Range */
#define DTE_ED_EVRUN                        (0x0010U)   /* Running EV Status               */
#define DTE_ED_OVER_SF                      (0x0100U)   /* Over Sender Full                */
#define DTE_ED_INIT_COMP                    (0x0200U)   /* Initial Complete                */
#define DTE_ED_CG_UNKOWN                    (0x1000U)
#define DTE_ED_CG_INVALD                    (0x2000U)
#define DTE_ED_FAILCHK                      (0x4000U)

#define DTE_ED_CG_STS_SFT                   (12U)

#define DTE_ED_CRSRST_RUN                   (0x8000U)   /* Reset Runnning                  */
#define DTE_ED_CRSRST_INIT                  (0x7FFFU)   /* Reset Initial/Not executed      */
#define DTE_ED_CRSRST_FAIL                  (0x7FFEU)   /* Reset Fail                      */
#define DTE_ED_CRSRST_SUCC                  (0x7FFDU)   /* Reset Success                   */

#define DTE_ED_CANTX_MAX                    (9999U)

#define DTE_ED_PIEVSTS_ON                   (1U)
#define DTE_ED_PHVMDIND_EVMODE              (0x01U)
#define DTE_ED_PHVMDIND_EVAUTOMODE          (0x0AU)


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2                          u2_bit;
    U1    (* const              fp_u1_CND)(const U2 * u2_ap_STSFIELD);
}ST_DTE_ED_APPLTASK;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2 u2_s_dte_ed_cgrst_to;
static U1 u1_s_dte_ed_calsub;                       /* サブ演算状態                           */
static U1 u1_s_dte_ed_runintvl_cnt;                 /* 通常減算1Sカウンタ                     */
static U2 u2_s_dte_ed_cordsp_cnt;                   /* 表示補正判定時間カウンタ               */
static U4 u4_s_dte_ed_fcp_dec;                      /* 停車時減算燃料噴射量積算               */
static U4 u4_s_dte_ed_spdpls_dec;                   /* 走行時減算車速PLS                      */
static U2 u2_s_dte_ed_applsts;
static ST_DTE_ED_PRM st_s_dte_ed_prm;
static U1 u1_s_det_ed_bfc_inv;
static U1 u1_s_dte_ed_rstimmw;
static U2 u2_s_dte_ed_cg_0p001kmpl;


/* RIM Backup Memory */
static U1 u1_s_dte_ed_bra_cg_sts;               /* Cg Status                                                                         */
static U2 u2_s_dte_ed_bra_cg;                   /* Learning fuel economy. Resolution [0.1 pls/10cc]                                  */
static U4 u4_s_dte_ed_bra_spdpls_cg;            /* Integrated value of vehicle speed pulse for learning fuel consumption calculation */
static U4 u4_s_dte_ed_bra_fcp_cg;               /* Integrated value of fuel injection for learning fuel consumption calculation      */
static U4 u4_s_dte_ed_bra_cnsm_fuel;            /* Integrated value of fuel injection during stop count(TC)                          */
static U1 u1_s_dte_ed_bra_crs_sts;              /* Dte calcurate status                                                              */
static U4 u4_s_dte_ed_bra_ks_sppls;             /* Estimated mileage for Public, Resolution 1/50960[km]                              */
static U2 u2_s_dte_ed_bra_kh_1km;               /* Rounddown(KS) Estimated mileage for Public, Resolution 1Km                        */
static U2 u2_s_dte_ed_bra_kh_1mi;               /* Rounddown(KS) Estimated mileage for Public, Resolution 1Mile                      */
static U4 u4_s_dte_ed_bra_kf_sppls;             /* Estimated mileage for Private:kz * Cg * DKHCoef  , Resolution 1/50960[km]         */
static U2 u2_s_dte_ed_bra_kz_10cc;              /* Fuel remaining amount data: Display Fuel Data H - Meter E point[FulMEnp]          */
static U4 u4_s_dte_ed_bra_tc;                   /* Counter when stopped                                                              */
static U2 u2_s_dte_ed_bra_blwme_cnt;            /* Below meter E counter:Meter E point or less Duration                              */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1       u1_s_DteEdTrnsit(void);                                                 /* 航続可能距離状態遷移                      */
static U1       u1_s_DteEdFuelPrmtd(void);
static U1       u1_s_DteEdCalStrtd(void);
static U1       u1_s_DteEdCrsstsCalcDis(void);
static U1       u1_s_DteEdCrsstsCalcEna(const U1 u1_a_FUEL_PRMTD, const U1 u1_a_CAL_PRMTD);

static void     vd_s_DteEdKHUpdt(void);
static U4       u4_s_DteEdCalKS(const U2 u2_a_KZ);
static void     vd_s_DteEdCalKH(void);
static U1       u1_s_DteEdCgTrnsit(void);                                               /* 学習燃費状態遷移                          */
static void     vd_s_DteEdCgUpdt(void);                                                 /* 学習燃費更新処理                          */
static void     vd_s_DteEdCgCal(void);                                                  /* 学習燃費演算処理                          */
static U2       u2_s_DteEdUseFuel(const U2 u2_a_FULL);
static U2       u2_s_DteEdMlgRefuInt(void);                                             /* 給油間燃費算出処理                        */
static void     vd_s_DteEdCgReset(void);                                                /* Cg Reset                                  */
static void     vd_s_DteEdDistCalBkgnd(const U1 u1_a_CRS_STS_PRE, const U1 u1_a_CALSTRTD); /* 航続可能距離サブ状態遷移バックグランド */
static U1       u1_s_DteEdDistCalTrnsit(void);                                          /* 航続可能距離サブ状態遷移処理              */
static void     vd_s_DteEdSpplsUpdt(void);
static U1       u1_s_DteEdJdgBlwME(void);                                               /* ME以下判定処理                            */
static U1       u1_s_DteEdJdgCor(const U2 u2_a_SPD);                                    /* 表示補正処理                              */
static U1       u1_s_DteEdStopCal(void);
static void     vd_s_DteEdRunDecUpdt(void);                                             /* 走行時減算処理                            */
static U2       u2_s_DteEdCalG(void);                                                   /* Calculate the G(subtraction factor)       */
static void     vd_s_DteEdSetTC(void);
static void     vd_s_DteEdIdleDecUpdt(void);                                            /* 停車時減算処理                            */
static void     vd_s_DteEdRunDecClr(void);                                              /* 走行時減算用RAMクリア処理                 */
static void     vd_s_DteEdDistReCal(void);                                              /* 航続可能距離再計算処理                    */
static void     vd_s_DteEdBraRea(void);
static void     vd_s_DteEdBraWri(void);
static U1       u1_s_DteEdImmwRunAct(const U1 u1_a_UPDT);
static U1       u1_s_DteEdImmwRstChk(void);
static U2       u2_s_DteEdSfLit(void);
static void     vd_s_DteEdCgRea(void);
static U1       u1_s_DteEdCrsstsBonfailAct(const U1 u1_a_CAL_PRMTD);
static U1       u1_s_DteEdCrsstsRdyAct(const U1 u1_a_CAL_PRMTD);
static U1       u1_s_DteEdCrsstsCalAct(const U1 u1_a_CAL_PRMTD);
static U1       u1_s_DteEdCgStsSetdefcgAct(void);
static U1       u1_s_DteEdCgStsFailAct(void);
static U1       u1_s_DteEdCgStsUpdtAct(void);
static U1       u1_s_DteEdCgStsRdyUpdtAct(void);

static U1       u1_s_DteEdIncInvalid(const U2 * u2_ap_STSFIELD);
static U1       u1_s_DteEdEvrun(const U2 * u2_ap_STSFIELD);
static U1       u1_s_DteEdUpdtEna(const U2 * u2_ap_STSFIELD);
static U1       u1_s_DteEdIgon(const U2 * u2_ap_STSFIELD);
static U1       u1_s_DteEdGfi(const U2 * u2_ap_STSFIELD);
static U1       u1_s_DteEdRcmOor(const U2 * u2_ap_STSFIELD);
static U1       u1_s_DteEdOverSenderFull(const U2 * u2_ap_STSFIELD);
static U1       u1_s_DteEdInitComp(const U2 * u2_ap_STSFIELD);
static U1       u1_s_DteEdCgUnk(const U2 * u2_ap_STSFIELD);
static U1       u1_s_DteEdCgInv(const U2 * u2_ap_STSFIELD);
static U1       u1_s_DteEdChkFail(const U2 * u2_ap_STSFIELD);
static void     vd_s_DteEdCgplspccTo0p001kmpl(void);
static void     vd_s_DteEdRunIntCnt(const U2 u2_a_SPD);
static U2       u2_s_DteEdSpdChk(void);
static U2       u2_s_DteEdCalKHMi(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2     u2_s_DTE_ED_STOPJDG       = (U2)175U;
static const U2     u2_s_DTE_ED_ACCMLT_JDGBIT = (U2)DTE_ED_CALC_ENA | (U2)DTE_ED_INC_INVALID | (U2)DTE_ED_EVRUN;
static const U2     u2_s_DTE_ED_FUCHG_JDGBIT  = (U2)DTE_ED_GFI | (U2)DTE_ED_RCM_OOR;

static const U1     u1_sp_DTE_ED_MSID[]={           /* see vd_s_DteEdBraRea and vd_s_DteEdBraWri */
    (U1)TRIPCOM_MS_ID_DTE_ED_U1_CG_STS,
    (U1)TRIPCOM_MS_ID_DTE_ED_U2_CRSCG,
    (U1)TRIPCOM_MS_ID_DTE_ED_U4_SPDPLS_CG,
    (U1)TRIPCOM_MS_ID_DTE_ED_U4_FCP_CG,
    (U1)TRIPCOM_MS_ID_DTE_ED_U4_CNSM_FUEL,
    (U1)TRIPCOM_MS_ID_DTE_ED_U1_CRS_STS,
    (U1)TRIPCOM_MS_ID_DTE_ED_U4_KS_SPPLS,
    (U1)TRIPCOM_MS_ID_DTE_ED_U2_KH_1KM,
    (U1)TRIPCOM_MS_ID_DTE_ED_U2_KH_1MI,
    (U1)TRIPCOM_MS_ID_DTE_ED_U4_KF_SPPLS,
    (U1)TRIPCOM_MS_ID_DTE_ED_U2_KZ_10CC,
    (U1)TRIPCOM_MS_ID_DTE_ED_U4_TC,
    (U1)TRIPCOM_MS_ID_DTE_ED_U2_BLWME_CNT
};
static const U1 u1_s_DTE_ED_MSID_NUM = (U1)(sizeof(u1_sp_DTE_ED_MSID) / sizeof(u1_sp_DTE_ED_MSID[0]));

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_DteEdInit(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DteEdInit(void)
{
    vd_g_DteEdSyncUpdtInit();

    u1_s_dte_ed_rstimmw = (U1)TRIPCOM_RSTIMMW_UNK;
}

/*===================================================================================================================================*/
/*  void    vd_g_DteEdSyncUpdtInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DteEdSyncUpdtInit(void)
{
    vd_s_DteEdBraRea();

    u1_s_dte_ed_calsub          = (U1)DTE_ED_CALSUB_RDY;
    vd_s_DteEdRunDecClr();
    u2_s_dte_ed_cgrst_to        = (U2)DTE_ED_CRSRST_INIT;
    u2_s_dte_ed_applsts         = (U2)0U;
    u1_s_det_ed_bfc_inv         = (U1)FALSE;
    vd_s_DteEdCgplspccTo0p001kmpl();
    vd_s_DteEdCgRea();
}

/*===================================================================================================================================*/
/*  void    vd_g_DteEdAppTask(const U2 * u2_ap_STSFIELD)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DteEdAppTask(const U2 * u2_ap_STSFIELD)
{
    static const ST_DTE_ED_APPLTASK     st_sp_DTE_ED_APPLTASK[] = {
        {(U2)DTE_ED_INC_INVALID, &u1_s_DteEdIncInvalid      },
        {(U2)DTE_ED_EVRUN,       &u1_s_DteEdEvrun           },
        {(U2)DTE_ED_CALC_ENA,    &u1_s_DteEdUpdtEna         },
        {(U2)DTE_ED_IGON,        &u1_s_DteEdIgon            },
        {(U2)DTE_ED_GFI,         &u1_s_DteEdGfi             },
        {(U2)DTE_ED_RCM_OOR,     &u1_s_DteEdRcmOor          },
        {(U2)DTE_ED_OVER_SF,     &u1_s_DteEdOverSenderFull  },
        {(U2)DTE_ED_INIT_COMP,   &u1_s_DteEdInitComp        },
        {(U2)DTE_ED_CG_UNKOWN,   &u1_s_DteEdCgUnk           },
        {(U2)DTE_ED_CG_INVALD,   &u1_s_DteEdCgInv           },
        {(U2)DTE_ED_FAILCHK,     &u1_s_DteEdChkFail         }
    };
    static const U1 u1_s_DTE_ED_NUM_APPLTASK = (U1)(sizeof(st_sp_DTE_ED_APPLTASK) / sizeof(st_sp_DTE_ED_APPLTASK[0]));
    U1              u1_t_ret;
    U4              u4_t_loop;
    U2              u2_t_preig;

    u2_t_preig = u2_s_dte_ed_applsts & (U2)DTE_ED_IGON;
    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)u1_s_DTE_ED_NUM_APPLTASK ; u4_t_loop++){
        u1_t_ret = (st_sp_DTE_ED_APPLTASK[u4_t_loop].fp_u1_CND)(u2_ap_STSFIELD);
        if(u1_t_ret == (U1)TRUE){
            u2_s_dte_ed_applsts |= st_sp_DTE_ED_APPLTASK[u4_t_loop].u2_bit;
        }
        else{
            u2_s_dte_ed_applsts &= ((U2)U2_MAX ^ st_sp_DTE_ED_APPLTASK[u4_t_loop].u2_bit);
        }
    }

    u2_t_preig = u2_t_preig ^ (u2_s_dte_ed_applsts & (U2)DTE_ED_IGON);
    if(u2_t_preig != (U2)0U ){ /* IG ON/OFF Event */
        u1_s_dte_ed_calsub  = (U1)DTE_ED_CALSUB_RDY;
        vd_s_DteEdRunDecClr();
    }

    vd_s_DteEdCgRea();
}

/*===================================================================================================================================*/
/*  void    vd_g_DteEdAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DteEdAccmlt(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD, const U4 * u4_ap_DELTA)
{
    U2  u2_t_spd;
    U1  u1_t_sts;
    U1  u1_t_emgf_exist;
    U4  u4_t_fuelused;
    U4  u4_t_odocnt;

    if((u2_s_dte_ed_applsts & u2_s_DTE_ED_ACCMLT_JDGBIT) == (U2)DTE_ED_CALC_ENA){
        u1_t_emgf_exist = u1_g_DteEdCfgEMGFExist();
        if(u1_t_emgf_exist == (U1)FALSE){
            u4_t_fuelused = u4_ap_DELTA[TRIPCOM_DELTA_DC_FUELUSD_PC];
            u4_t_odocnt   = u4_ap_DELTA[TRIPCOM_DELTA_DC_ODOCNT_PC];
        }
        else{
            u4_t_fuelused = u4_ap_DELTA[TRIPCOM_DELTA_DC_FUELUSD_W_EMGF_PC];
            u4_t_odocnt   = u4_ap_DELTA[TRIPCOM_DELTA_DC_ODOCNT_W_EMGF_PC];
        }
        if(u1_s_dte_ed_bra_cg_sts != (U1)CGSTS_RDYUPDT){
            u4_s_dte_ed_bra_spdpls_cg = u4_g_TripcomCalcAddU4U4(u4_s_dte_ed_bra_spdpls_cg, u4_t_odocnt);
            u4_s_dte_ed_bra_fcp_cg    = u4_g_TripcomCalcAddU4U4(u4_s_dte_ed_bra_fcp_cg   , u4_t_fuelused);
            u4_s_dte_ed_bra_cnsm_fuel = u4_g_TripcomCalcAddU4U4(u4_s_dte_ed_bra_cnsm_fuel, u4_t_fuelused);
            if((u4_s_dte_ed_bra_spdpls_cg >= (U4)DTE_ED_CGADDMAX) ||
               (u4_s_dte_ed_bra_fcp_cg    >= (U4)DTE_ED_CGADDMAX)){
                u4_s_dte_ed_bra_spdpls_cg -= (u4_s_dte_ed_bra_spdpls_cg >> DTE_ED_SHIFT_03BIT);      /* 7/8                           */
                u4_s_dte_ed_bra_fcp_cg    -= (u4_s_dte_ed_bra_fcp_cg    >> DTE_ED_SHIFT_03BIT);      /* 7/8                           */
            }
        }
        if(u4_s_dte_ed_spdpls_dec >= ((U4)U4_MAX - u4_t_odocnt)){
            u4_s_dte_ed_spdpls_dec = (U4)U4_MAX;
        }
        else{
            u4_s_dte_ed_spdpls_dec += u4_t_odocnt;
        }

        u2_t_spd = (U2)0U;
        u1_t_sts = u1_g_TripsnsrVspKmph(&u2_t_spd);
        if(u1_t_sts != (U1)0U){
            u2_t_spd = (U2)0U;
        }
        if(u2_t_spd <= u2_s_DTE_ED_STOPJDG){
            u4_s_dte_ed_fcp_dec = u4_g_TripcomCalcAddU4U4(u4_s_dte_ed_fcp_dec, u4_t_fuelused);
        }
    }

    vd_s_DteEdBraWri();

}

/*===================================================================================================================================*/
/*  U1      u1_g_DteEdCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DteEdCalcTrnst(const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)
{
    static U2   u2_s_DTE_ED_CGRESET_TO = (U2)5000U / 50U;
    U1          u1_t_req;
    U2          u2_t_cg;
    U2          u2_t_cnt;

    if(((u2_ap_STSFIELD[TRIPCOM_STSFIELD_MANUAL_RSTRQ] & (U2)TRIPCOM_RSTRQBIT_M_DTE_RF) != (U2)0U) &&
       ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_MARST_IMMW]   & (U2)TRIPCOM_RSTRQBIT_M_DTE_RF) != (U2)0U)){
        (void)u1_g_DteEdCgResetReq();
    }

    if(u2_s_dte_ed_cgrst_to == (U2)DTE_ED_CRSRST_RUN){
        vd_s_DteEdCgReset();
        u2_s_dte_ed_cgrst_to = (U2)DTE_ED_CRSRST_RUN + (U2)1U;
    }
    else if((u2_s_dte_ed_cgrst_to & (U2)DTE_ED_CRSRST_RUN) != (U2)0U){
        u2_t_cg = (U2)u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U2_CRSCG);
        if(st_s_dte_ed_prm.u2_cg_def != u2_t_cg){
            vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U2_CRSCG, (U4)st_s_dte_ed_prm.u2_cg_def);
            u2_t_cnt = u2_s_dte_ed_cgrst_to & ((U2)U2_MAX ^ (U2)DTE_ED_CRSRST_RUN);
            if(u2_t_cnt > u2_s_DTE_ED_CGRESET_TO){
                u2_s_dte_ed_cgrst_to  = (U2)DTE_ED_CRSRST_FAIL;
            }
            else{
                u2_t_cnt++;
                u2_s_dte_ed_cgrst_to  = (U2)DTE_ED_CRSRST_RUN | u2_t_cnt;
            }
        }
        else{
            u2_s_dte_ed_cgrst_to  = (U2)DTE_ED_CRSRST_SUCC;
        }
    }
    else{
        /* Nothing */
    }

    u1_t_req  = u1_s_DteEdCgTrnsit();
    u1_t_req |= u1_s_DteEdTrnsit();

    vd_s_DteEdBraWri();

    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  void    vd_g_DteEdUpdt(const U1 u1_a_CNTTID)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DteEdUpdt(const U1 u1_a_CNTTID)
{
    vd_s_DteEdCgUpdt();
    vd_s_DteEdKHUpdt();
    vd_s_DteEdBraWri();
    vd_s_DteEdCgplspccTo0p001kmpl();
}

/*===================================================================================================================================*/
/*  void    vd_g_DteEdRstImmw(const U1 u1_a_ACTV, const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_DteEdRstImmw(const U1 u1_a_ACTV, const U1 u1_a_CNTTID, const U2 * u2_ap_STSFIELD)
{
    U1                                          u1_t_rstimmw;
    U1                                          u1_t_updt;
    U1                                          u1_t_accpt;
    U1                                          u1_t_stsbit;

    u1_t_rstimmw = u1_s_dte_ed_rstimmw;

    if((u1_t_rstimmw & (U1)TRIPCOM_RSTIMMW_RUN) == (U1)0U){
        /* TRIPCOM_RSTIMMW_UNK or TRIPCOM_RSTIMMW_SUC or TRIPCOM_RSTIMMW_FAI */
        if(((u2_ap_STSFIELD[TRIPCOM_STSFIELD_MANUAL_RSTRQ] & (U2)TRIPCOM_RSTRQBIT_M_DTE_RF) != (U2)0U) &&
           ((u2_ap_STSFIELD[TRIPCOM_STSFIELD_MARST_IMMW]   & (U2)TRIPCOM_RSTRQBIT_M_DTE_RF) != (U2)0U)){
            if(u1_a_ACTV == (U1)TRUE){
                u1_t_updt = (U1)FALSE;
                if((u2_s_dte_ed_cgrst_to & (U2)DTE_ED_CRSRST_RUN) != (U2)0U){
                    u1_t_updt = (U1)TRUE;
                }
            }
            else{
                vd_s_DteEdCgReset();
                u1_t_updt = (U1)TRUE;
            }

            u1_t_accpt = u1_s_DteEdImmwRunAct(u1_t_updt);
            if(u1_t_accpt == (U1)TRUE){
                u1_t_rstimmw = (U1)TRIPCOM_RSTIMMW_RUN;
            }
            else{
                u1_t_rstimmw = (U1)TRIPCOM_RSTIMMW_FAI;
            }
        }
    }
    else{
        /* TRIPCOM_RSTIMMW_RUN */
        u1_t_stsbit = u1_s_DteEdImmwRstChk();

        if((u1_t_stsbit & (U1)TRIPCOM_MS_NVMSTS_SUC) != (U1)0x00U){
            u1_t_rstimmw = (U1)TRIPCOM_RSTIMMW_SUC;
        }
        else if((u1_t_stsbit & (U1)TRIPCOM_MS_NVMSTS_FAIL) != (U1)0x00U){
            u1_t_rstimmw = (U1)TRIPCOM_RSTIMMW_FAI;
        }
        else{
            /* nothing */
        }
    }
    u1_s_dte_ed_rstimmw = u1_t_rstimmw;
}

/*===================================================================================================================================*/
/*  U2      u2_g_DteEdKm(void)                                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u2_s_dte_ed_bra_kh_1km:Distant to Empty(km)                                                                      */
/*===================================================================================================================================*/
U2      u2_g_DteEdKm(void)
{
    return(u2_s_dte_ed_bra_kh_1km);
}

/*===================================================================================================================================*/
/*  U2      u2_g_DteEdMi(void)                                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u2_s_dte_ed_bra_kh_1mi:Distant to Empty(mile)                                                                    */
/*===================================================================================================================================*/
U2      u2_g_DteEdMi(void)
{
    return(u2_s_dte_ed_bra_kh_1mi);
}
/*===================================================================================================================================*/
/*  U2      u2_g_DteEdCgPlsp10cc(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_DteEdCgPlsp10cc(void)
{
    return(u2_s_dte_ed_bra_cg);
}
/*===================================================================================================================================*/
/*  U1      u1_g_DteEdCg0p001kmpl(U2 * u2p_a_kmpl)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DteEdCg0p001kmpl(U4 * u4p_a_kmpl)
{
    U1  u1_t_sts;

    if(u4p_a_kmpl != vdp_PTR_NA){
        (*u4p_a_kmpl) = (U4)u2_s_dte_ed_cg_0p001kmpl;
    }
    u1_t_sts = (U1)((u2_s_dte_ed_applsts & ((U2)DTE_ED_CG_UNKOWN | (U2)DTE_ED_CG_INVALD)) >> DTE_ED_CG_STS_SFT);

    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  U2      u2_g_DteEdCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_DteEdCalcTx(const U1 u1_a_CNTTID, const U1 u1_a_UNIT)
{
    U4          u4_t_dist;
    U2          u2_t_txval;

    if(u1_a_UNIT == (U1)TRIPCOM_CALC_DSTUNT_KM){
        u4_t_dist = (U4)u2_s_dte_ed_bra_kh_1km;
    }
    else{
        u4_t_dist = (U4)u2_s_dte_ed_bra_kh_1mi;
    }
    if(u4_t_dist == (U4)DTE_ED__FAIL_VLE){
        u2_t_txval = (U2)TRIPCOM_CANTX_TIMEOUT;
    }
    else if(u4_t_dist == (U4)DTE_ED_UNDET_VLE){
        u2_t_txval = (U2)TRIPCOM_CANTX_UNKNOWN;
    }
    else{
        u2_t_txval  = (U2)DTE_ED_CANTX_MAX;
        if (u4_t_dist  < (U4)DTE_ED_CANTX_MAX) {
            u2_t_txval = (U2)u4_t_dist;
        }
    }

    return (u2_t_txval);
}

/*===================================================================================================================================*/
/*  U1      u1_g_DteEdCgResetReq(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_DteEdCgResetReq(void)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;
    if(u2_s_dte_ed_cgrst_to < (U2)DTE_ED_CRSRST_RUN){
        u1_t_ret             = (U1)TRUE;
        u2_s_dte_ed_cgrst_to = (U2)DTE_ED_CRSRST_RUN;
    }
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  U2      u2_g_DteEdCgResetRslt(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_DteEdCgResetRslt(void)
{
    U2  u2_t_rslt;

    if(u2_s_dte_ed_cgrst_to == (U2)DTE_ED_CRSRST_INIT){
        u2_t_rslt = (U2)DTE_ED_CG_RSET_UNK;
    }
    else if(u2_s_dte_ed_cgrst_to == (U2)DTE_ED_CRSRST_FAIL){
        u2_t_rslt = (U2)DTE_ED_CG_RSET_FAI;
    }
    else if(u2_s_dte_ed_cgrst_to == (U2)DTE_ED_CRSRST_SUCC){
        u2_t_rslt = (U2)DTE_ED_CG_RSET_SUC;
    }else{
        u2_t_rslt = (U2)DTE_ED_CG_RSET_RUN;
    }

    return(u2_t_rslt);
}

/*===================================================================================================================================*/
/*  U1              u1_g_DteEdRstImmwRslt(const U1 u1_a_DTE_ED_CH)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DteEdRstImmwRslt(const U1 u1_a_DTE_ED_CH)
{
    U1                                          u1_t_rslt;

    u1_t_rslt = u1_s_dte_ed_rstimmw;

    return(u1_t_rslt);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_DteEdIncInvalid(const U2 * u2_ap_STSFIELD)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_DteEdIncInvalid(const U2 * u2_ap_STSFIELD)
{
    U1  u1_t_ret;
    U2  u2_t_bfc_unk;
    U2  u2_t_bfc_inv;
    U2  u2_t_odo_unkinv;
    U1  u1_t_sts;
    U1  u1_t_pievsts; 
    U1  u1_t_phvmdind;
    U2  u2_t_jdgig;
    U1  u1_t_emgf_exist;

    u1_t_emgf_exist = u1_g_DteEdCfgEMGFExist();
    if(u1_t_emgf_exist == (U1)FALSE){
        u2_t_bfc_unk    = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & (U2)TRIPCOM_SNSRBIT_B_FC_UNKNOWN;
        u2_t_bfc_inv    = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & (U2)TRIPCOM_SNSRBIT_B_FC_INVALID;
        u2_t_odo_unkinv = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & ((U2)TRIPCOM_SNSRBIT_ODOCNT_UNKNOWN | (U2)TRIPCOM_SNSRBIT_ODOCNT_INVALID);
    }
    else{
        u2_t_bfc_unk    = u2_g_TripsnsrFuelusdEmgfSts() & (U2)TRIPCOM_SNSRBIT_DTEED_B_FC_UNKNOWN;
        u2_t_bfc_inv    = u2_g_TripsnsrFuelusdEmgfSts() & (U2)TRIPCOM_SNSRBIT_DTEED_B_FC_INVALID;
        u2_t_odo_unkinv = u2_g_TripsnsrOdocntEmgfSts()  & ((U2)TRIPCOM_SNSRBIT_DTEED_ODOCNT_UNKNOWN | (U2)TRIPCOM_SNSRBIT_DTEED_ODOCNT_INVALID);
    }

    u1_t_pievsts    = (U1)0U; 
    u1_t_phvmdind   = (U1)0U; 
    u1_t_sts        = u1_g_TripcomGetPHVMDIND(&u1_t_phvmdind);
    u1_t_sts       |= u1_g_TripcomGetPIEVSTS(&u1_t_pievsts);

    u2_t_jdgig = u2_ap_STSFIELD[TRIPCOM_STSFIELD_VSTS] & (U2)TRIPCOM_VEHSTS_IGON;
    if(u2_t_jdgig == (U2)0U){
        u1_s_det_ed_bfc_inv = (U1)FALSE;
    }
    else if(u2_t_bfc_inv != (U2)0U){
        u1_s_det_ed_bfc_inv = (U1)TRUE;
    }else{
        /* Nothing */
    }

    if(( u2_t_odo_unkinv                    != (U2)0U) ||
       ( u2_t_bfc_unk                       != (U2)0U) ||
       ( u2_t_bfc_inv                       != (U2)0U) ||
       ((u1_t_sts & (U1)DTE_ED_STS_INVALID) != (U1)0U)){
        u1_t_ret = (U1)TRUE;
    }
    else{
        u1_t_ret = (U1)FALSE;
    }
    u1_t_ret |= u1_s_det_ed_bfc_inv;

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1   u1_s_DteEdEvrun(const U2 * u2_ap_STSFIELD)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1   u1_s_DteEdEvrun(const U2 * u2_ap_STSFIELD)
{
    U1  u1_t_ret;
    U1  u1_t_sts;
    U1  u1_t_pievsts; 
    U1  u1_t_phvmdind; 

    u1_t_pievsts   = (U1)0U; 
    u1_t_phvmdind  = (U1)0U; 
    u1_t_sts       = u1_g_TripcomGetPHVMDIND(&u1_t_phvmdind);
    u1_t_sts      |= u1_g_TripcomGetPIEVSTS(&u1_t_pievsts);
    if((u1_t_sts & (U1)DTE_ED_STS_INVALID) != (U1)0U){
        u1_t_ret = (U1)FALSE;
    }else if((u1_t_sts & (U1)DTE_ED_STS_UNKNOWN) != (U1)0U){
        u1_t_ret = (U1)FALSE;
    }
    else{
        if((u1_t_pievsts == (U1)DTE_ED_PIEVSTS_ON                ) &&
           ((u1_t_phvmdind == (U1)DTE_ED_PHVMDIND_EVMODE    ) ||
            (u1_t_phvmdind == (U1)DTE_ED_PHVMDIND_EVAUTOMODE)    )){
            u1_t_ret = (U1)TRUE;
        }
        else{
            u1_t_ret = (U1)FALSE;
        }
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdUpdtEna(const U2 * u2_ap_STSFIELD)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdUpdtEna(const U2 * u2_ap_STSFIELD)
{
    U1  u1_t_ret;
    U1  u1_t_sts;
    U1  u1_t_emgf;
    U2  u2_t_jdgbit; 

    u2_t_jdgbit  = u2_ap_STSFIELD[TRIPCOM_STSFIELD_VSTS] &  (U2)TRIPCOM_VEHSTS_DRVCYC;
    u1_t_emgf    = (U1)0U;
    u1_t_sts     = u1_g_TripcomGetEMGF(&u1_t_emgf);
    if((u1_t_sts & (U1)DTE_ED_STS_UNKNOWN) != (U1)0U){
        u1_t_emgf = (U1)0U;
    }

    if((u1_t_sts & (U1)DTE_ED_STS_INVALID) != (U1)0U){
        u1_t_ret = (U1)FALSE;
    }
    else if((u2_t_jdgbit != (U2)0U) ||
            (u1_t_emgf   == (U1)1U)) {
        u1_t_ret = (U1)TRUE;
    }
    else{
        u1_t_ret = (U1)FALSE;
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdIgon(const U2 * u2_ap_STSFIELD)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdIgon(const U2 * u2_ap_STSFIELD)
{
    U1  u1_t_ret;
    U2  u2_t_jdgbit;

    u2_t_jdgbit = u2_ap_STSFIELD[TRIPCOM_STSFIELD_VSTS] & (U2)TRIPCOM_VEHSTS_IGON;
    if(u2_t_jdgbit != (U2)0U){
        u1_t_ret = (U1)TRUE;
    }
    else{
        u1_t_ret = (U1)FALSE;
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdGfi(const U2 * u2_ap_STSFIELD)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdGfi(const U2 * u2_ap_STSFIELD)
{
    U1  u1_t_ret;

    u1_t_ret = u1_g_DteEdCfgFuelGsiAct();
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdRcmOor(const U2 * u2_ap_STSFIELD)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdRcmOor(const U2 * u2_ap_STSFIELD)
{
    U1  u1_t_ret;

    u1_t_ret = u1_g_DteEdCfgFuelRcmOOR();
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdOverSenderFull(const U2 * u2_ap_STSFIELD)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdOverSenderFull(const U2 * u2_ap_STSFIELD)
{
    U2  u2_t_curr_lit_0p01_basese;
    U2  u2_t_full_lit_0p01;
    U1  u1_t_ret;

    u2_t_curr_lit_0p01_basese = u2_g_DteEdCfgCurrLit0p01BaseSE();
    u2_t_full_lit_0p01        = u2_g_DteEdCfgSeFullLit0p01();
    if(u2_t_curr_lit_0p01_basese >= u2_t_full_lit_0p01){
        u1_t_ret = (U1)TRUE;
    }
    else{
        u1_t_ret = (U1)FALSE;
    }
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdInitComp(const U2 * u2_ap_STSFIELD)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdInitComp(const U2 * u2_ap_STSFIELD)
{
    U1  u1_t_ret;

    u1_t_ret = u1_g_DteEdCfgFuelInitComp();
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdCgUnk(const U2 * u2_ap_STSFIELD)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdCgUnk(const U2 * u2_ap_STSFIELD)
{
    U1  u1_t_ret;
    U1  u1_t_sts;
    U1  u1_t_phvmdind;
    U1  u1_t_pievsts;
    U1  u1_t_emgf;
    U2  u2_t_jdgbit;

    u1_t_phvmdind  = (U1)0U;
    u1_t_pievsts   = (U1)0U;
    u1_t_emgf      = (U1)0U;
    u1_t_sts       = u1_g_TripcomGetPHVMDIND(&u1_t_phvmdind);
    u1_t_sts      |= u1_g_TripcomGetPIEVSTS(&u1_t_pievsts);
    u1_t_sts      |= u1_g_TripcomGetEMGF(&u1_t_emgf);
    u2_t_jdgbit    = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & ((U2)TRIPCOM_SNSRBIT_ODOCNT_UNKNOWN  |
                                                              (U2)TRIPCOM_SNSRBIT_FUELUSD_UNKNOWN |
                                                              (U2)TRIPCOM_SNSRBIT_B_FC_UNKNOWN     );
    u1_t_ret       = (U1)FALSE;
    if(((u1_t_sts & (U1)DTE_ED_STS_UNKNOWN) != (U1)0U)||
       (u2_t_jdgbit                         != (U2)0U)){
        u1_t_ret = (U1)TRUE;
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdCgInv(const U2 * u2_ap_STSFIELD)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdCgInv(const U2 * u2_ap_STSFIELD)
{
    U1  u1_t_ret;
    U1  u1_t_sts;
    U1  u1_t_phvmdind;
    U1  u1_t_pievsts;
    U1  u1_t_emgf;
    U2  u2_t_jdgbit;

    u1_t_phvmdind    = (U1)0U;
    u1_t_pievsts     = (U1)0U;
    u1_t_emgf        = (U1)0U;
    u1_t_sts         = u1_g_TripcomGetPHVMDIND(&u1_t_phvmdind);
    u1_t_sts        |= u1_g_TripcomGetPIEVSTS(&u1_t_pievsts);
    u1_t_sts        |= u1_g_TripcomGetEMGF(&u1_t_emgf);
    u2_t_jdgbit      = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & ((U2)TRIPCOM_SNSRBIT_ODOCNT_INVALID  |
                                                                (U2)TRIPCOM_SNSRBIT_FUELUSD_INVALID |
                                                                (U2)TRIPCOM_SNSRBIT_B_FC_INVALID     );
    u1_t_ret = (U1)FALSE;
    if(((u1_t_sts & (U1)DTE_ED_STS_INVALID) != (U1)0U  ) ||
       (u2_t_jdgbit                         != (U2)0U  ) ||
       (u1_s_det_ed_bfc_inv                 == (U1)TRUE) ){
        u1_t_ret = (U1)TRUE;
    }
    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdCgInv(const U2 * u2_ap_STSFIELD)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdChkFail(const U2 * u2_ap_STSFIELD)
{
    U1  u1_t_ret;
    U1  u1_t_sts;
    U1  u1_t_phvmdind;
    U1  u1_t_pievsts;
    U1  u1_t_emgf;
    U2  u2_t_jdgbit;

    u1_t_phvmdind    = (U1)0U;
    u1_t_pievsts     = (U1)0U;
    u1_t_emgf        = (U1)0U;
    u1_t_sts         = u1_g_TripcomGetPHVMDIND(&u1_t_phvmdind);
    u1_t_sts        |= u1_g_TripcomGetPIEVSTS(&u1_t_pievsts);
    u1_t_sts        |= u1_g_TripcomGetEMGF(&u1_t_emgf);
    u2_t_jdgbit      = u2_ap_STSFIELD[TRIPCOM_STSFIELD_SNSR] & ((U2)TRIPCOM_SNSRBIT_ODOCNT_INVALID  |
                                                                (U2)TRIPCOM_SNSRBIT_FUELUSD_INVALID |
                                                                (U2)TRIPCOM_SNSRBIT_B_FC_INVALID     );

    u1_t_ret = (U1)FALSE;
    if(((u1_t_sts & (U1)DTE_ED_STS_INVALID) != (U1)0U  ) ||
       (u2_t_jdgbit                         != (U2)0U  ) ||
       (u1_s_det_ed_bfc_inv                 == (U1)TRUE) ){
        u1_t_ret = (U1)TRUE;
    }
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdTrnsit(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdTrnsit(void)
{
    U1 u1_t_req;                            /* Update Request                              */
    U1 u1_t_fuel_prmtd;                     /* フューエル演算可状態                        */
    U1 u1_t_cal_prmtd;                      /* ドラモニ演算開始状態 & フューエル演算可    */
    U1 u1_t_calstrtd;                       /* ドラモニ演算開始状態 & フューエル演算可    */
    U1 u1_t_crs_sts_pre;

    u1_t_fuel_prmtd  = u1_s_DteEdFuelPrmtd();
    u1_t_calstrtd    = u1_s_DteEdCalStrtd();
    u1_t_cal_prmtd   = u1_t_fuel_prmtd & u1_t_calstrtd;
    u1_t_crs_sts_pre = u1_s_dte_ed_bra_crs_sts;

    u1_t_req = (U1)FALSE;

    if((u2_s_dte_ed_applsts & (U2)DTE_ED_FAILCHK) != (U2)0U){
        u1_t_req = u1_s_DteEdCrsstsCalcDis();
    }
    else{
        u1_t_req = u1_s_DteEdCrsstsCalcEna(u1_t_fuel_prmtd , u1_t_cal_prmtd);
    }

    vd_s_DteEdDistCalBkgnd(u1_t_crs_sts_pre, u1_t_calstrtd);

    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdCrsstsCalcDis(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdCrsstsCalcDis(void)
{
    U1 u1_t_req;                            /* Update Request                           */

    u1_t_req = (U1)FALSE;
    if((u1_s_dte_ed_bra_crs_sts <= (U1)CRSSTS_BONFAIL) ||               /* Unknown      */
        (u1_s_dte_ed_bra_crs_sts >  (U1)CRSSTS_MAXSTS )){               /* RAM Error    */
        if(u1_s_dte_ed_bra_crs_sts != (U1)CRSSTS_BONFAIL){
            u1_t_req = (U1)TRUE;
        }
        u1_s_dte_ed_bra_crs_sts = (U1)CRSSTS_BONFAIL;
    }
    else{
        if(u1_s_dte_ed_bra_crs_sts != (U1)CRSSTS_FAIL){
            u1_t_req = (U1)TRUE;
        }
        u1_s_dte_ed_bra_crs_sts = (U1)CRSSTS_FAIL;
    }
    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdCrsstsCalcEna(const U1 u1_a_FUEL_PRMTD, const U1 u1_a_CAL_PRMTD)                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdCrsstsCalcEna(const U1 u1_a_FUEL_PRMTD, const U1 u1_a_CAL_PRMTD)
{
    U1 u1_t_req;                            /* Update Request                           */

    u1_t_req = (U1)FALSE;
    switch(u1_s_dte_ed_bra_crs_sts){
        case (U1)CRSSTS_BONRDY:
            if(u1_a_CAL_PRMTD == (U1)TRUE){
                u1_s_dte_ed_bra_crs_sts = (U1)CRSSTS_RECAL;
                u1_t_req                = (U1)TRUE;
            }
            break;
        case (U1)CRSSTS_BONFAIL:
            u1_s_dte_ed_bra_crs_sts = u1_s_DteEdCrsstsBonfailAct(u1_a_CAL_PRMTD);
            u1_t_req                = (U1)TRUE;
            break;
        case (U1)CRSSTS_RDY:
            u1_s_dte_ed_bra_crs_sts = u1_s_DteEdCrsstsRdyAct(u1_a_CAL_PRMTD);
            break;
        case (U1)CRSSTS_RECAL:
            /* Fall Through */
        case (U1)CRSSTS_CAL:
            u1_s_dte_ed_bra_crs_sts = u1_s_DteEdCrsstsCalAct(u1_a_CAL_PRMTD);
            if(u1_s_dte_ed_bra_crs_sts == (U1)CRSSTS_CAL){
                u1_t_req = u1_s_DteEdDistCalTrnsit();
            }
            break;
        case (U1)CRSSTS_FAIL:
            if((u1_a_FUEL_PRMTD                         == (U1)TRUE) &&
               ((u2_s_dte_ed_applsts & (U2)DTE_ED_IGON) != (U2)0U  )){
                u1_s_dte_ed_bra_crs_sts = (U1)CRSSTS_RECAL;
                u1_t_req                = (U1)TRUE;
            }
            break;
        case (U1)CRSSTS_RECALRDY:
            if((u2_s_dte_ed_applsts & u2_s_DTE_ED_FUCHG_JDGBIT) == (U2)0U){
                u1_s_dte_ed_bra_crs_sts = (U1)CRSSTS_RECAL;
                u1_t_req                = (U1)TRUE;
            }
            break;
        default:
            u1_s_dte_ed_bra_crs_sts = (U1)CRSSTS_BONRDY;
            u1_t_req                = (U1)TRUE;
            break;
    }
    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdFuelPrmtd(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdFuelPrmtd(void)
{
    U1 u1_t_fuel_prmtd;

    u1_t_fuel_prmtd = (U1)FALSE;
    if(((u2_s_dte_ed_applsts & (U2)DTE_ED_INIT_COMP) != (U2)0U            ) &&
       (u1_s_dte_ed_bra_cg_sts                       >  (U1)CGSTS_SETDEFCG)) {
        u1_t_fuel_prmtd = (U1)TRUE;
    }
    return(u1_t_fuel_prmtd);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdCalStrtd(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdCalStrtd(void)
{
    U1 u1_t_calstrtd;

    u1_t_calstrtd = (U1)FALSE;
    if((u2_s_dte_ed_cgrst_to                        <  (U2)DTE_ED_CRSRST_RUN) &&
       ((u2_s_dte_ed_applsts & (U2)DTE_ED_CALC_ENA) != (U2)0U               )){
        u1_t_calstrtd = (U1)TRUE;
    }
    return(u1_t_calstrtd);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdCrsstsBonfailAct(const U1 u1_a_CAL_PRMTD)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdCrsstsBonfailAct(const U1 u1_a_CAL_PRMTD)
{
    U1  u1_t_sts;

    if(u1_a_CAL_PRMTD == (U1)TRUE){
        u1_t_sts = (U1)CRSSTS_RECAL;
    }
    else{
        u1_t_sts = (U1)CRSSTS_BONRDY;
    }
    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdCrsstsRdyAct(const U1 u1_a_CAL_PRMTD)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdCrsstsRdyAct(const U1 u1_a_CAL_PRMTD)
{
    U1  u1_t_sts;

    if((u2_s_dte_ed_applsts & u2_s_DTE_ED_FUCHG_JDGBIT) != (U2)0U){
        u1_t_sts = (U1)CRSSTS_RECALRDY;
    }
    else if(u1_a_CAL_PRMTD == (U1)TRUE){
        u1_t_sts = (U1)CRSSTS_CAL;
    }
    else{
        u1_t_sts = (U1)CRSSTS_RDY;
    }
    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdCrsstsCalAct(const U1 u1_a_CAL_PRMTD)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdCrsstsCalAct(const U1 u1_a_CAL_PRMTD)
{
    U1  u1_t_sts;

    if((u2_s_dte_ed_applsts & u2_s_DTE_ED_FUCHG_JDGBIT) != (U2)0U){
        u1_t_sts = (U1)CRSSTS_RECALRDY;
    }
    else if(u1_a_CAL_PRMTD == (U1)FALSE){
        u1_t_sts = (U1)CRSSTS_RDY;
    }
    else{
        u1_t_sts = (U1)CRSSTS_CAL;
    }
    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  static void     vd_s_DteEdKHUpdt(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DteEdKHUpdt(void)
{
    switch(u1_s_dte_ed_bra_crs_sts){
        case (U1)CRSSTS_BONRDY:
            u2_s_dte_ed_bra_kh_1km = (U2)DTE_ED_UNDET_VLE;
            u2_s_dte_ed_bra_kh_1mi = (U2)DTE_ED_UNDET_VLE;
            break;
        case (U1)CRSSTS_BONFAIL:
        case (U1)CRSSTS_FAIL:
            u2_s_dte_ed_bra_kh_1km = (U2)DTE_ED__FAIL_VLE;
            u2_s_dte_ed_bra_kh_1mi = (U2)DTE_ED__FAIL_VLE;
            break;
        case (U1)CRSSTS_CAL:
            vd_s_DteEdCalKH();
            break;
        case (U1)CRSSTS_RECAL:
            vd_s_DteEdDistReCal();
            vd_s_DteEdCalKH();
            break;
        case (U1)CRSSTS_RDY:
            /* Fall Through */
        case (U1)CRSSTS_RECALRDY:
            /* Fall Through */
        default:
            /* Nothing      */
            break;
    }
}

/*===================================================================================================================================*/
/*  static U4       u4_s_DteEdCalKS(const U2 u2_a_KZ)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      --> const U2 u2_a_KZ:残燃料(LSB=10cc)                                                                            */
/*  Return:          U4 u4_t_ksret:航続可能距離pls数                                                                                 */
/*===================================================================================================================================*/
static U4       u4_s_DteEdCalKS(const U2 u2_a_KZ)
{
    U4              u4_t_ksret;

    if(u2_a_KZ == (U2)0U){
        u4_t_ksret = (U4)0U;
    }
    else{
        if(st_s_dte_ed_prm.u1_khcor_per != (U1)DTE_ED_COEF_BASE_100P){
            u4_t_ksret  = (U4)u2_s_dte_ed_bra_cg * (U4)st_s_dte_ed_prm.u1_khcor_per;
            u4_t_ksret += (U4)DTE_ED_KHCOR_RND;
            u4_t_ksret /= (U4)DTE_ED_COEF_BASE_100P;
        }
        else{
            u4_t_ksret = (U4)u2_s_dte_ed_bra_cg;
        }
        u4_t_ksret *= (U4)u2_a_KZ;
    }
    return(u4_t_ksret);
}

/*===================================================================================================================================*/
/*  static void     vd_s_DteEdCalKH(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DteEdCalKH(void)
{
    static const U2     u2_s_DTE_ED_MAX_KH  = (U2)9999U;
    static const U4     u4_s_DTE_ED_PLS_1KM = (U4)(5096U * DTE_ED_RES_0P1KM_TO_1KM);
    U4                  u4_t_work;

    u4_t_work  = u4_s_dte_ed_bra_ks_sppls / u4_s_DTE_ED_PLS_1KM;
    if(u4_t_work > (U4)u2_s_DTE_ED_MAX_KH){
        u2_s_dte_ed_bra_kh_1km = u2_s_DTE_ED_MAX_KH;
    }
    else{
        u2_s_dte_ed_bra_kh_1km = (U2)u4_t_work;
    }

    u2_s_dte_ed_bra_kh_1mi = u2_s_DteEdCalKHMi();
}

/*===================================================================================================================================*/
/*  static U2       u2_s_DteEdCalKHMi(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2       u2_s_DteEdCalKHMi(void)
{
    static const U2     u2_s_DTE_ED_MAX_MI      = (U2)9999U;
    static const U4     u4_s_DTE_ED_PLS_MPH_MUL = (U4)100U;
    static const U4     u4_s_DTE_ED_PLS_MPH_DIV = (U4)(5096U * 1609U);
    U2  u2_t_kh_mi;
    U4  u4_tp_rslt[CALC_U8_NUM_RSLT];
    U4  u4_tp_arg[CALC_U8_NUM_TERM];
    U1  u1_t_rslt;

    u4_tp_rslt[CALC_U8_QUO] = (U4)0U;
    u4_tp_rslt[CALC_U8_RES] = (U4)0U;
    u4_tp_arg[CALC_U8_LO]   = u4_s_DTE_ED_PLS_MPH_MUL;
    u4_tp_arg[CALC_U8_HI]   = u4_s_dte_ed_bra_ks_sppls;
    u4_tp_arg[CALC_U8_DIV]  = u4_s_DTE_ED_PLS_MPH_DIV;
    u1_t_rslt               = u1_g_MuldivU8(&u4_tp_arg[CALC_U8_LO], &u4_tp_rslt[CALC_U8_QUO]);

    if((u1_t_rslt & (U1)CALC_U8_RSLT_DIVBYZERO) != (U1)0U){
        u2_t_kh_mi = (U2)0U;
    }
    else if((u1_t_rslt & (U1)CALC_U8_RSLT_OVRFLW_U4) != (U1)0U){
        u2_t_kh_mi = u2_s_DTE_ED_MAX_MI;
    }
    else if((u1_t_rslt & (U1)CALC_U8_RSLT_ZERO) != (U1)0U){
        u2_t_kh_mi = (U2)0U;
    }
    else{
        if(u4_tp_rslt[CALC_U8_QUO] >= (U4)u2_s_DTE_ED_MAX_MI){
            u2_t_kh_mi = u2_s_DTE_ED_MAX_MI;
        }
        else{
            u2_t_kh_mi = (U2)u4_tp_rslt[CALC_U8_QUO];
        }
    }
    return(u2_t_kh_mi);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdCgTrnsit(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdCgTrnsit(void)
{
    U1              u1_t_req;                               /* 要求定義                        */

    u1_t_req = (U1)FALSE;
    switch(u1_s_dte_ed_bra_cg_sts){
        case (U1)CGSTS_BONRDY:
            if((u2_s_dte_ed_applsts & (U2)DTE_ED_IGON) != (U2)0U){
                u1_s_dte_ed_bra_cg_sts = (U1)CGSTS_SETDEFCG;
                u1_t_req               = (U1)TRUE;
            }
            break;
        case (U1)CGSTS_SETDEFCG:
            u1_s_dte_ed_bra_cg_sts = u1_s_DteEdCgStsSetdefcgAct();
            break;
        case (U1)CGSTS_HOLD:
            /* Fall Through */
        case (U1)CGSTS_FAIL:
            u1_s_dte_ed_bra_cg_sts = u1_s_DteEdCgStsFailAct();
            break;
        case (U1)CGSTS_RDYUPDT:
            u1_s_dte_ed_bra_cg_sts = u1_s_DteEdCgStsRdyUpdtAct();
            if(u1_s_dte_ed_bra_cg_sts == (U1)CGSTS_UPDT){
                u1_t_req               = (U1)TRUE;
            }
            break;
        case (U1)CGSTS_UPDT:
            u1_s_dte_ed_bra_cg_sts = u1_s_DteEdCgStsUpdtAct();
            break;
        default:
            u1_s_dte_ed_bra_cg_sts = (U1)CGSTS_BONRDY;
            break;
    }

    /* 定期学習燃費再設定処理                            */
    if((u1_s_dte_ed_bra_cg_sts >  (U1)CGSTS_SETDEFCG       ) &&
       ((u2_s_dte_ed_bra_cg > st_s_dte_ed_prm.u2_cg_max) ||
        (u2_s_dte_ed_bra_cg < st_s_dte_ed_prm.u2_cg_min)    )){
        u2_s_dte_ed_bra_cg = st_s_dte_ed_prm.u2_cg_def;
        vd_s_DteEdCgplspccTo0p001kmpl();
    }

    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdCgStsSetdefcgAct(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdCgStsSetdefcgAct(void)
{
    U1  u1_t_sts;

    if((u2_s_dte_ed_applsts & (U2)DTE_ED_IGON) != (U2)0U){
        if((u2_s_dte_ed_applsts & (U2)DTE_ED_GFI) != (U2)0U){
            u1_t_sts = (U1)CGSTS_RDYUPDT;
        }
        else{
            u1_t_sts = (U1)CGSTS_HOLD;
        }
    }
    else{
        u1_t_sts = (U1)CGSTS_BONRDY;
    }
    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdCgStsFailAct(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdCgStsFailAct(void)
{
    U1  u1_t_sts;

    if((u2_s_dte_ed_applsts & (U2)DTE_ED_FAILCHK) != (U2)0U){
        u1_t_sts = (U1)CGSTS_FAIL;
    }
    else if(((u2_s_dte_ed_applsts & (U2)DTE_ED_GFI    ) != (U2)0U) &&
            ((u2_s_dte_ed_applsts & (U2)DTE_ED_RCM_OOR) == (U2)0U)){
        u1_t_sts = (U1)CGSTS_RDYUPDT;
    }
    else{
        u1_t_sts = (U1)CGSTS_HOLD;
    }
    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdCgStsUpdtAct(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdCgStsUpdtAct(void)
{
    U1  u1_t_sts;

    if((u2_s_dte_ed_applsts & (U2)DTE_ED_FAILCHK) != (U2)0U){
        u1_t_sts = (U1)CGSTS_FAIL;
    }
    else{
        u1_t_sts = (U1)CGSTS_HOLD;
    }
    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdCgStsRdyUpdtAct(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdCgStsRdyUpdtAct(void)
{
    U1  u1_t_sts;

    if((u2_s_dte_ed_applsts & (U2)DTE_ED_FAILCHK) != (U2)0U){
        u1_t_sts = (U1)CGSTS_FAIL;
    }
    else if((u2_s_dte_ed_applsts & (U2)DTE_ED_RCM_OOR) != (U2)0U){
        u1_t_sts = (U1)CGSTS_HOLD;
    }
    else if((u2_s_dte_ed_applsts & (U2)DTE_ED_GFI) == (U2)0U){
        u1_t_sts = (U1)CGSTS_UPDT;
    }
    else{
        u1_t_sts = (U1)CGSTS_RDYUPDT; /* Nothing. Refueling status is ongoing */
    }
    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  static void    vd_s_DteEdCgUpdt(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DteEdCgUpdt(void)
{
    switch(u1_s_dte_ed_bra_cg_sts){
        case (U1)CGSTS_SETDEFCG:
            if((u2_s_dte_ed_bra_cg > st_s_dte_ed_prm.u2_cg_max) ||
               (u2_s_dte_ed_bra_cg < st_s_dte_ed_prm.u2_cg_min)){
                u2_s_dte_ed_bra_cg = st_s_dte_ed_prm.u2_cg_def;
            }
            break;
        case (U1)CGSTS_UPDT:
            vd_s_DteEdCgCal();
            break;
        default:
            /* Nothing */
            break;
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_DteEdCgCal(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DteEdCgCal(void)
{
    U2          u2_t_econ;                      /* 給油間燃費                       */
    U2          u2_t_cnspdiff;                  /* 給油間と学習燃費差異             */
    U2          u2_t_cg;                        /* 学習燃費                         */
    U2          u2_t_fuel_full;                 /* 満タン量                         */
    U2          u2_t_fuel_use;                  /* 燃料使用量                       */
    U4          u4_t_nowcg;                     /* 今回Cg                           */
    U1          u1_t_sts;

    /*************************/
    /* 給油間燃費算出         */
    /*************************/
    u2_t_econ = u2_s_DteEdMlgRefuInt();
    if(u2_t_econ <= (U2)DTE_ED_LOW_CG_0P5_KMPL){
        u2_t_econ = st_s_dte_ed_prm.u2_cg_def;
    }

    u2_t_fuel_full = (U2)0U;
    u1_t_sts       = u1_g_TripcomGetMaterialInfo((U1)TRIPCOM_FUELINFO_FULL_10ML, &u2_t_fuel_full);
    if(u1_t_sts != (U1)TRIPCOM_STSBIT_VALID){
        u2_t_fuel_full = (U2)0U;
    }
    u2_t_fuel_use  = u2_s_DteEdUseFuel(u2_t_fuel_full);
    /****************************************************************/
    /*     学習燃費計算処理                                         */
    /*                                                              */
    /*     (今回燃費 － 現在学習燃費)    × 燃料使用量               */
    /*     ---------------------------------------- ＋ 現在学習燃費 */
    /*                     満タン量                                 */
    /****************************************************************/
    if(u2_t_fuel_full != (U2)0U){
        if(u2_t_econ >= u2_s_dte_ed_bra_cg){
            u2_t_cnspdiff = u2_t_econ - u2_s_dte_ed_bra_cg;
            u4_t_nowcg    = (U4)u2_t_cnspdiff * (U4)u2_t_fuel_use;
            u4_t_nowcg   /= (U4)u2_t_fuel_full;
            u4_t_nowcg    = (U4)u2_s_dte_ed_bra_cg + u4_t_nowcg;
            if(u4_t_nowcg >= (U4)U2_MAX){
                u4_t_nowcg = (U4)U2_MAX;
            }
        }
        else{
            u2_t_cnspdiff  = u2_s_dte_ed_bra_cg - u2_t_econ;
            u4_t_nowcg     = (U4)u2_t_cnspdiff * (U4)u2_t_fuel_use;
            u4_t_nowcg    /= (U4)u2_t_fuel_full;
            if((U4)u2_s_dte_ed_bra_cg >= u4_t_nowcg){
                u4_t_nowcg = (U4)u2_s_dte_ed_bra_cg - u4_t_nowcg;
            }
            else {                                                          /* 異常時                                                */
                u4_t_nowcg = (U4)u2_s_dte_ed_bra_cg;                        /* 現在の燃費を設定                                      */
            }
        }
        /***************************************************/
        /*            CurrentCg *2 ＋ NowCg                */
        /*  New Cg =  -------------------------            */
        /*                   (1+2)                         */
        /***************************************************/
        u2_t_cg = (U2)((((U4)u2_s_dte_ed_bra_cg * (U4)DTE_ED_CG_WA_CURRENT) + (u4_t_nowcg * (U4)DTE_ED_CG_WA_NOW)) / (U4)DTE_ED_CG_WA_TOTAL);
    }
    else{                                                                   /* 異常時 現在の学習燃費を設定                           */
        u2_t_cg = u2_s_dte_ed_bra_cg;
    }

    if(u2_t_cg > st_s_dte_ed_prm.u2_cg_max){
        u2_s_dte_ed_bra_cg = st_s_dte_ed_prm.u2_cg_max;
    }
    else if(u2_t_cg < st_s_dte_ed_prm.u2_cg_min){
        u2_s_dte_ed_bra_cg = st_s_dte_ed_prm.u2_cg_min;
    }
    else{
        u2_s_dte_ed_bra_cg = u2_t_cg;
    }
}

/*===================================================================================================================================*/
/*  static U2       u2_s_DteEdUseFuel(const U2 u2_a_FULL)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:  -                                                                                                                    */
/*  Return:     -                                                                                                                    */
/*===================================================================================================================================*/
static U2       u2_s_DteEdUseFuel(const U2 u2_a_FULL)
{
    U2    u2_t_fuel_use;                        /* 使用量(LSB 10cc)                 */
    U4    u4_t_work;

    u4_t_work  = u4_g_TripcomCalcAddU4U4(u4_s_dte_ed_bra_cnsm_fuel, (U4)CRSFCPTO10CC_RND);
    u4_t_work /= (U4)CRSFCPTO10CC_K;
    if(u4_t_work >= (U4)U2_MAX){
        u2_t_fuel_use = (U2)U2_MAX;
    }
    else{
        u2_t_fuel_use = (U2)u4_t_work;
    }
    u4_s_dte_ed_bra_cnsm_fuel =(U4)0U;

    if(u2_t_fuel_use >= u2_a_FULL){
        u2_t_fuel_use = u2_a_FULL;
    }
    return(u2_t_fuel_use);
}

/*===================================================================================================================================*/
/*  static U2       u2_s_DteEdMlgRefuInt(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:  -                                                                                                                    */
/*  Return:      U2 u2_t_cnsp:給油間燃費                                                                                             */
/*===================================================================================================================================*/
static U2       u2_s_DteEdMlgRefuInt(void)
{
    U2  u2_t_cnsp;
    U4  u4_tp_rslt[CALC_U8_NUM_RSLT];
    U4  u4_tp_arg[CALC_U8_NUM_TERM];
    U4  u4_t_tmp;
    U1  u1_t_rslt;

    /* CRSCG_CNSPCOEF * u4_s_dte_ed_bra_spdpls_cg / u4_s_dte_ed_bra_fcp_cg */
    u4_tp_rslt[CALC_U8_QUO] = (U4)0U;
    u4_tp_rslt[CALC_U8_RES] = (U4)0U;
    u4_tp_arg[CALC_U8_LO]   = (U4)CRSCG_CNSPCOEF;
    u4_tp_arg[CALC_U8_HI]   = u4_s_dte_ed_bra_spdpls_cg;
    u4_tp_arg[CALC_U8_DIV]  = u4_s_dte_ed_bra_fcp_cg;
    u1_t_rslt               = u1_g_MuldivU8(&u4_tp_arg[CALC_U8_LO], &u4_tp_rslt[CALC_U8_QUO]);

    if((u1_t_rslt & (U1)(CALC_U8_RSLT_OVRFLW_U4 | CALC_U8_RSLT_DIVBYZERO)) != (U1)0U){
        u2_t_cnsp = (U2)U2_MAX;
    }
    else if((u1_t_rslt & (U1)CALC_U8_RSLT_ZERO) != (U1)0U){
        u2_t_cnsp = (U2)0U;
    }
    else{
        if(u4_tp_rslt[CALC_U8_QUO] >= ((U4)U4_MAX - (U4)DTE_ED_CNSP_RND)){
            u2_t_cnsp = (U2)U2_MAX;
        }
        else{
            u4_t_tmp = u4_tp_rslt[CALC_U8_QUO] + (U4)DTE_ED_CNSP_RND;
            u4_t_tmp = u4_t_tmp >> DTE_ED_SHIFT_10BIT;
            if(u4_t_tmp >= (U4)U2_MAX){
                u2_t_cnsp = (U2)U2_MAX;
            }
            else{
                u2_t_cnsp = (U2)u4_t_tmp;
            }
        }
    }

    u4_s_dte_ed_bra_spdpls_cg = (U4)0U;
    u4_s_dte_ed_bra_fcp_cg    = (U4)0U;

    return(u2_t_cnsp);
}

/*===================================================================================================================================*/
/*  static void     vd_s_DteEdCgReset(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DteEdCgReset(void)
{
    u1_s_dte_ed_bra_cg_sts      = (U1)CGSTS_BONRDY;
    u2_s_dte_ed_bra_cg          = st_s_dte_ed_prm.u2_cg_def;                      /* Cg to Default                */
    u4_s_dte_ed_bra_spdpls_cg   = (U4)0U;
    u4_s_dte_ed_bra_fcp_cg      = (U4)0U;
    u4_s_dte_ed_bra_cnsm_fuel   = (U4)0U;
    u1_s_dte_ed_bra_crs_sts     = (U1)CRSSTS_BONRDY;
    u2_s_dte_ed_bra_kh_1km      = (U2)DTE_ED_UNDET_VLE;
    u2_s_dte_ed_bra_kh_1mi      = (U2)DTE_ED_UNDET_VLE;

    u4_s_dte_ed_bra_ks_sppls    = (U4)0U;
    u2_s_dte_ed_bra_kz_10cc     = (U2)0U;
    u4_s_dte_ed_bra_kf_sppls    = (U4)0U;
    u2_s_dte_ed_bra_blwme_cnt   = (U2)0U;
    u1_s_dte_ed_calsub          = (U1)DTE_ED_CALSUB_RDY;

    vd_s_DteEdRunDecClr();
    u4_s_dte_ed_bra_tc          = (U4)0U;
    vd_s_DteEdCgplspccTo0p001kmpl();
    vd_s_DteEdBraWri();

}

/*===================================================================================================================================*/
/*  static void     vd_s_DteEdDistCalBkgnd(const U1 u1_a_CRS_STS_PRE, const U1 u1_a_CALSTRTD);                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DteEdDistCalBkgnd(const U1 u1_a_CRS_STS_PRE, const U1 u1_a_CALSTRTD)
{
    if((u1_s_dte_ed_bra_crs_sts != (U1)CRSSTS_CAL) ||
       (u1_a_CRS_STS_PRE        == (U1)CRSSTS_RDY)){
        u1_s_dte_ed_calsub = (U1)DTE_ED_CALSUB_RDY;

        switch(u1_s_dte_ed_bra_crs_sts){
            case (U1)CRSSTS_CAL:                        /* 前回状態がRDYでないとこのパスには通らない                */
                /* Fall Through */
            case (U1)CRSSTS_RDY:
                if(u1_a_CALSTRTD != (U1)TRUE){
                    vd_s_DteEdRunDecClr();                    /* RDY時、演算停止ならクリア            */
                }
                else{
                    u2_s_dte_ed_cordsp_cnt   = (U2)0U;            /* 演算開始中ならカウンタのみクリア        */
                    u1_s_dte_ed_runintvl_cnt = (U1)0U;            /* 演算開始中の積算値クリアは不可        */
                }
                break;
            default:                                    /* CALとRDY以外は必ず再計算実施    */
                vd_s_DteEdRunDecClr();
                break;
        }
    }
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdDistCalTrnsit(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdDistCalTrnsit(void)
{
    U1          u1_t_req;                                /* 更新要求                            */
    U1          u1_t_mebelow;                            /* ME点以下判定                        */
    U1          u1_t_dspcor;                             /* 表示補正判定                        */
    U2          u2_t_spd;

    u1_t_req = (U1)FALSE;
    vd_s_DteEdSpplsUpdt();
    u2_t_spd = u2_s_DteEdSpdChk();
    vd_s_DteEdRunIntCnt(u2_t_spd);

    /************************************************************************************************/
    /* ME点補正、表示補正距離の実施                                                                 */
    /************************************************************************************************/
    u1_t_mebelow = u1_s_DteEdJdgBlwME();
    u1_t_dspcor  = u1_s_DteEdJdgCor(u2_t_spd);
    if(u1_t_mebelow == (U1)TRUE){
        if(u4_s_dte_ed_bra_ks_sppls != (U4)0U){
            u1_t_req = (U1)TRUE;
        }
        u4_s_dte_ed_bra_ks_sppls = (U4)0U;
        vd_s_DteEdRunDecClr();
        u1_s_dte_ed_calsub       = (U1)DTE_ED_CALSUB_RDY;
    }
    else if(u1_t_dspcor == (U1)TRUE){
        u1_t_req = (U1)TRUE;
        vd_s_DteEdRunDecClr();
        u4_s_dte_ed_bra_ks_sppls = u4_s_dte_ed_bra_kf_sppls;
        u1_s_dte_ed_calsub       = (U1)DTE_ED_CALSUB_RUN_DEC;   /* 走行中でないと成立しないため                */
    }
    else{
    /************************************************************************************************/
    /* 走行時減算,停車時減算の実施                                                                  */
    /************************************************************************************************/
        if(u2_t_spd > (U2)u2_s_DTE_ED_STOPJDG){
            if(u1_s_dte_ed_runintvl_cnt >= (U1)DTE_ED_RUN_1S){
                u1_s_dte_ed_runintvl_cnt = (U1)0U;
                vd_s_DteEdRunDecUpdt();
                u1_t_req = (U1)TRUE;
            }
            u1_s_dte_ed_calsub = (U1)DTE_ED_CALSUB_RUN_DEC;
        }
        else{
            u1_t_req = u1_s_DteEdStopCal();
        }
    }

    return(u1_t_req);
}
/*===================================================================================================================================*/
/*  static void     vd_s_DteEdSpplsUpdt(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DteEdSpplsUpdt(void)
{
    U2          u2_t_pre_kz;
    if((u2_s_dte_ed_applsts & (U2)DTE_ED_INIT_COMP) != (U2)0U){
        u2_t_pre_kz             = u2_s_dte_ed_bra_kz_10cc;
        u2_s_dte_ed_bra_kz_10cc = u2_g_DteEdCfgCurrLit0p01BaseME();
        if(u2_t_pre_kz != u2_s_dte_ed_bra_kz_10cc){
            u4_s_dte_ed_bra_kf_sppls = u4_s_DteEdCalKS(u2_s_dte_ed_bra_kz_10cc);
        }
    }
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdJdgBlwME(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdJdgBlwME(void)
{
    U1 u1_t_belowme;

    u1_t_belowme = (U1)FALSE;
    if(u2_s_dte_ed_bra_kz_10cc == (U2)0U){
        if(u2_s_dte_ed_bra_blwme_cnt >= ((U2)U2_MAX - (U2)1U)){
            u2_s_dte_ed_bra_blwme_cnt = (U2)U2_MAX;
        }
        else{
            u2_s_dte_ed_bra_blwme_cnt++;
        }
        if(u2_s_dte_ed_bra_blwme_cnt >= (U2)DTE_ED_BLWMETIM_64S){
            u1_t_belowme = (U1)TRUE;
        }
    }
    else{
        u2_s_dte_ed_bra_blwme_cnt = (U2)0U;
    }
    return(u1_t_belowme);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdJdgCor(const U2 u2_a_SPD)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:        --> const U2 u2_a_SPD:車速                                                                                     */
/*  Return:            U1 u1_t_req:判定結果(TRUE:条件成立 FALSE:未成立)                                                              */
/*===================================================================================================================================*/
static U1       u1_s_DteEdJdgCor(const U2 u2_a_SPD)
{
    U1  u1_t_req;
    U4  u4_t_jdgpls_15l;                        /* Distance for 15L [0.1 pulse]   */
    U4  u4_t_diffpls;                           /* KZ * Cg * DKHCoef - KS         */

    u1_t_req = (U1)FALSE;
    if((u2_a_SPD                 >= (U2)DTE_ED_DSPCOR_SPD   ) &&
       (u4_s_dte_ed_bra_kf_sppls >  u4_s_dte_ed_bra_ks_sppls)){
        u4_t_diffpls = u4_s_dte_ed_bra_kf_sppls - u4_s_dte_ed_bra_ks_sppls;
        u4_t_jdgpls_15l  = (U4)u2_s_dte_ed_bra_cg * (U4)DTE_ED_DSPCOR10CC;
        if(u4_t_diffpls >= u4_t_jdgpls_15l){
            if(u2_s_dte_ed_cordsp_cnt >= ((U2)U2_MAX - (U2)1U)){
                u2_s_dte_ed_cordsp_cnt = (U2)U2_MAX;
            }
            else{
                u2_s_dte_ed_cordsp_cnt++;
            }
            if(u2_s_dte_ed_cordsp_cnt >= (U2)DTE_ED_DSPCOR_TIM_128S){
                u1_t_req = (U1)TRUE;
            }
        }
        else{
            u2_s_dte_ed_cordsp_cnt = (U2)0U;
        }
    }
    else{
        u2_s_dte_ed_cordsp_cnt = (U2)0U;
    }
    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdStopCal(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdStopCal(void)
{
    U1  u1_t_req;

    u1_t_req = (U1)FALSE;
    switch(u1_s_dte_ed_calsub){
        case (U1)DTE_ED_CALSUB_IDLE_DEC:
            if(u4_s_dte_ed_bra_tc <= u4_s_dte_ed_fcp_dec){
                vd_s_DteEdIdleDecUpdt();
                u1_t_req = (U1)TRUE;
            }
            break;
        case (U1)DTE_ED_CALSUB_IDLE_DECSTOP:
            u4_s_dte_ed_fcp_dec = (U4)0U;
            break;
        case (U1)DTE_ED_CALSUB_RDY:
            /* Fall Through */
        case (U1)DTE_ED_CALSUB_RUN_DEC:
            /* Fall Through */
        default:
            if((u2_s_dte_ed_bra_kz_10cc  == (U2)0U) ||
                (u4_s_dte_ed_bra_ks_sppls == (U4)0U)){
                u4_s_dte_ed_fcp_dec = (U4)0U;
                u1_s_dte_ed_calsub  = (U1)DTE_ED_CALSUB_IDLE_DECSTOP;
            }
            else{
                vd_s_DteEdSetTC();
                if(u4_s_dte_ed_bra_tc <= u4_s_dte_ed_fcp_dec){
                    vd_s_DteEdIdleDecUpdt();
                    u1_t_req = (U1)TRUE;
                }
                u1_s_dte_ed_calsub = (U1)DTE_ED_CALSUB_IDLE_DEC;
            }
            break;
    }
    return(u1_t_req);
}

/*===================================================================================================================================*/
/*  static void    vd_s_DteEdRunDecUpdt(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_DteEdRunDecUpdt(void)
{
    U2  u2_t_g;                                 /* G:Subtraction coefficient                        */
    U4  u4_t_ivl_pls;                           /* MI:Number of sp pulses during 1sec               */

    u4_t_ivl_pls = u4_s_dte_ed_spdpls_dec;
    if(u4_t_ivl_pls != (U4)0U){
        u2_t_g        = u2_s_DteEdCalG();
        if(((U4)U4_MAX / u4_t_ivl_pls) > (U4)u2_t_g){
            u4_t_ivl_pls *= (U4)u2_t_g;
            u4_t_ivl_pls /= (U4)DTE_ED_G_RES;       /* G resolution is 1%, (u4_t_ivl_pls / 100) * DTE_ED_RES_0P1KM_TO_1KM */
        }
        else{
            u4_t_ivl_pls = (U4)U4_MAX;
        }
        if(u4_s_dte_ed_bra_ks_sppls <= u4_t_ivl_pls){
            u4_s_dte_ed_bra_ks_sppls = (U4)0U;
        }
        else{
            u4_s_dte_ed_bra_ks_sppls -= u4_t_ivl_pls;
        }
    }
    u4_s_dte_ed_spdpls_dec = (U4)0U;
}

/*===================================================================================================================================*/
/*  static U2 u2_s_DteEdCalG(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2 u2_s_DteEdCalG(void)
{
    static const U2 u2_s_DTE_ED_G_OVER_SF = (U2)100U;
    U4  u4_t_plsdif;
    U2  u2_t_g;

    if((u2_s_dte_ed_applsts & (U2)DTE_ED_EVRUN) != (U2)0U){
        u2_t_g = (U2)0U;
    }
    else if((u2_s_dte_ed_applsts & (U2)DTE_ED_OVER_SF) != (U2)0U){
        u2_t_g = u2_s_DTE_ED_G_OVER_SF;
    }
    else if(u4_s_dte_ed_bra_ks_sppls < u4_s_dte_ed_bra_kf_sppls){
        u2_t_g = (U2)st_s_dte_ed_prm.u1_g_min_per;
    }
    else{
        u4_t_plsdif = u4_s_dte_ed_bra_ks_sppls - u4_s_dte_ed_bra_kf_sppls;
        if(u4_t_plsdif <= (U4)DTE_ED_PLSP1KM){
            u2_t_g = (U2)st_s_dte_ed_prm.u1_g_cen_per;
        }
        else{
            u2_t_g = (U2)st_s_dte_ed_prm.u1_g_max_per;
        }
    }
    return(u2_t_g);
}

/*===================================================================================================================================*/
/*  static void     vd_s_DteEdSetTC(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DteEdSetTC(void)
{
    U4 u4_tp_rslt[CALC_U8_NUM_RSLT];
    U4 u4_tp_arg[CALC_U8_NUM_TERM];
    U1 u1_t_rslt;

    /* u2_s_dte_ed_bra_kz_10cc * CRSFCPTO10CC_K * DTE_ED_PLSPNTKM / u4_s_dte_ed_bra_ks_sppls */
    u4_tp_rslt[CALC_U8_QUO] = (U4)0U;
    u4_tp_rslt[CALC_U8_RES] = (U4)0U;
    u4_tp_arg[CALC_U8_LO]   = (U4)u2_s_dte_ed_bra_kz_10cc * (U4)DTE_ED_PLSPNTKM;
    u4_tp_arg[CALC_U8_HI]   = (U4)CRSFCPTO10CC_K;
    u4_tp_arg[CALC_U8_DIV]  = u4_s_dte_ed_bra_ks_sppls;
    u1_t_rslt               = u1_g_MuldivU8(&u4_tp_arg[CALC_U8_LO], &u4_tp_rslt[CALC_U8_QUO]);

    if((u1_t_rslt & (U1)CALC_U8_RSLT_OVRFLW_U4) != (U1)0U){
        u4_s_dte_ed_bra_tc = (U4)U4_MAX;
    }
    else if((u1_t_rslt & (U1)CALC_U8_RSLT_DIVBYZERO) != (U1)0U){
        /* Nothing           */
    }
    else if((u1_t_rslt & (U1)CALC_U8_RSLT_ZERO) != (U1)0U){
        u4_s_dte_ed_bra_tc = (U4)0U;
    }
    else{
        u4_s_dte_ed_bra_tc = u4_tp_rslt[CALC_U8_QUO];
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_DteEdIdleDecUpdt(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DteEdIdleDecUpdt(void)
{
    if(u4_s_dte_ed_bra_tc <= u4_s_dte_ed_fcp_dec){
        if(u4_s_dte_ed_bra_ks_sppls > (U4)DTE_ED_PLSPNTKM){
            u4_s_dte_ed_bra_ks_sppls -= (U4)DTE_ED_PLSPNTKM;
        }
        else{
            u4_s_dte_ed_bra_ks_sppls = (U4)0U;
        }
        u4_s_dte_ed_fcp_dec -= u4_s_dte_ed_bra_tc;
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_DteEdRunDecClr(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DteEdRunDecClr(void)
{
    u4_s_dte_ed_spdpls_dec   = (U4)0U;
    u4_s_dte_ed_fcp_dec      = (U4)0U;
    u1_s_dte_ed_runintvl_cnt = (U1)0U;
    u2_s_dte_ed_cordsp_cnt   = (U2)0U;
}

/*===================================================================================================================================*/
/*  static void     vd_s_DteEdDistReCal(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DteEdDistReCal(void)
{
    U2    u2_t_sf_lit_10cc;

    u2_s_dte_ed_bra_kz_10cc = u2_g_DteEdCfgCurrLit0p01BaseME();

    if((u2_s_dte_ed_applsts & (U2)DTE_ED_OVER_SF) != (U2)0U){
        u2_t_sf_lit_10cc         = u2_s_DteEdSfLit();
        u4_s_dte_ed_bra_kf_sppls = u4_s_DteEdCalKS(u2_s_dte_ed_bra_kz_10cc);
        u4_s_dte_ed_bra_ks_sppls = u4_s_DteEdCalKS(u2_t_sf_lit_10cc);
    }
    else{
        u4_s_dte_ed_bra_kf_sppls = u4_s_DteEdCalKS(u2_s_dte_ed_bra_kz_10cc);
        u4_s_dte_ed_bra_ks_sppls = u4_s_dte_ed_bra_kf_sppls;
    }
}
/*===================================================================================================================================*/
/*  static U2       u2_s_DteEdSfLit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2       u2_s_DteEdSfLit(void)
{
    U1  u1_t_sts;
    U2  u2_t_ncfull_0p01;
    U4  u4_t_ncfull_corr;
    U2  u2_t_me_lit;
    U4  u4_t_fuel_rest;
    U2  u2_t_fuel_rest;

    u2_t_ncfull_0p01 = (U2)0U;
    u1_t_sts         = u1_g_TripcomGetMaterialInfo((U1)TRIPCOM_FUELINFO_FULL_10ML, &u2_t_ncfull_0p01); /* Nominal capacity of Full Litter */
    if(u1_t_sts != (U1)TRIPCOM_STSBIT_VALID){
        u2_t_ncfull_0p01 = (U2)0U;
    }
    u4_t_ncfull_corr  = (U4)u2_t_ncfull_0p01 * (U4)st_s_dte_ed_prm.u1_fulcor_per;
    u4_t_ncfull_corr += (U4)DTE_ED_COEF_BASE_100P_RND;
    u4_t_ncfull_corr /= (U4)DTE_ED_COEF_BASE_100P;
    u2_t_me_lit       = u2_g_DteEdCfgMeEmptyLit0p01();
    u4_t_fuel_rest    = (U2)0U;
    if(u4_t_ncfull_corr > (U4)u2_t_me_lit){
        u4_t_fuel_rest = (u4_t_ncfull_corr - (U4)u2_t_me_lit);
    }
    if(u4_t_fuel_rest > (U4)U2_MAX){
        u2_t_fuel_rest = (U2)U2_MAX;
    }
    else{
        u2_t_fuel_rest = (U2)u4_t_fuel_rest;
    }
    return(u2_t_fuel_rest);
}

/*===================================================================================================================================*/
/*  static void     vd_s_DteEdBraRea(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DteEdBraRea(void)
{
    u1_s_dte_ed_bra_cg_sts      = (U1)u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U1_CG_STS);
    u2_s_dte_ed_bra_cg          = (U2)u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U2_CRSCG);
    u4_s_dte_ed_bra_spdpls_cg   =     u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U4_SPDPLS_CG);
    u4_s_dte_ed_bra_fcp_cg      =     u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U4_FCP_CG);
    u4_s_dte_ed_bra_cnsm_fuel   =     u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U4_CNSM_FUEL);
    u1_s_dte_ed_bra_crs_sts     = (U1)u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U1_CRS_STS);
    u4_s_dte_ed_bra_ks_sppls    =     u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U4_KS_SPPLS);
    u2_s_dte_ed_bra_kh_1km      = (U2)u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U2_KH_1KM);
    u2_s_dte_ed_bra_kh_1mi      = (U2)u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U2_KH_1MI);
    u4_s_dte_ed_bra_kf_sppls    =     u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U4_KF_SPPLS);
    u2_s_dte_ed_bra_kz_10cc     = (U2)u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U2_KZ_10CC);
    u4_s_dte_ed_bra_tc          =     u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U4_TC);
    u2_s_dte_ed_bra_blwme_cnt   = (U2)u4_g_TripcomMsGetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U2_BLWME_CNT);
}

/*===================================================================================================================================*/
/*  static void     vd_s_DteEdBraWri(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DteEdBraWri(void)
{
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U1_CG_STS       ,(U4)u1_s_dte_ed_bra_cg_sts         );
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U2_CRSCG        ,(U4)u2_s_dte_ed_bra_cg             );
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U4_SPDPLS_CG    ,    u4_s_dte_ed_bra_spdpls_cg      );
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U4_FCP_CG       ,    u4_s_dte_ed_bra_fcp_cg         );
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U4_CNSM_FUEL    ,    u4_s_dte_ed_bra_cnsm_fuel      );
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U1_CRS_STS      ,(U4)u1_s_dte_ed_bra_crs_sts        );
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U4_KS_SPPLS    ,     u4_s_dte_ed_bra_ks_sppls       );
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U2_KH_1KM       ,(U4)u2_s_dte_ed_bra_kh_1km         );
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U2_KH_1MI       ,(U4)u2_s_dte_ed_bra_kh_1mi         );
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U4_KF_SPPLS     ,    u4_s_dte_ed_bra_kf_sppls       );
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U2_KZ_10CC      ,(U4)u2_s_dte_ed_bra_kz_10cc        );
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U4_TC           ,    u4_s_dte_ed_bra_tc             );
    vd_g_TripcomMsSetAccmltVal((U1)TRIPCOM_MS_ID_DTE_ED_U2_BLWME_CNT    ,(U4)u2_s_dte_ed_bra_blwme_cnt      );
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdImmwRunAct(const U1 u1_a_UPDT)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdImmwRunAct(const U1 u1_a_UPDT)
{
    U4                                          u4_t_loop;
    U1                                          u1_t_accpt;
    U1                                          u1_t_rslt;

    u1_t_accpt = (U1)FALSE;

    if(u1_a_UPDT == (U1)TRUE){

        u1_t_accpt = (U1)TRUE;
        for(u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_s_DTE_ED_MSID_NUM; u4_t_loop++){
            u1_t_rslt = u1_g_TripcomMsGetNvmRslt(u1_sp_DTE_ED_MSID[u4_t_loop]);
            if(u1_t_rslt == (U1)TRIPCOM_MS_NVMSTS_WAIT){
                u1_t_accpt = (U1)FALSE;
            }
        }

        if(u1_t_accpt == (U1)TRUE){
            for(u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_s_DTE_ED_MSID_NUM; u4_t_loop++){
                vd_g_TripcomMsSetNvmRqst(u1_sp_DTE_ED_MSID[u4_t_loop]);
            }
        }
    }
    return(u1_t_accpt);
}

/*===================================================================================================================================*/
/*  static U1       u1_s_DteEdImmwRstChk(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_DteEdImmwRstChk(void)
{
    U4                                          u4_t_loop;
    U1                                          u1_t_tmpbit;
    U1                                          u1_t_stsbit;
    U1                                          u1_t_sucbit;
    U1                                          u1_t_faibit;

    u1_t_stsbit = (U1)TRIPCOM_MS_NVMSTS_SUC;
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)u1_s_DTE_ED_MSID_NUM; u4_t_loop++){
        u1_t_tmpbit = u1_g_TripcomMsGetNvmRslt(u1_sp_DTE_ED_MSID[u4_t_loop]);
        u1_t_sucbit = (U1)((u1_t_stsbit & u1_t_tmpbit) & (U1)TRIPCOM_MS_NVMSTS_SUC);
        u1_t_faibit = (U1)((u1_t_stsbit | u1_t_tmpbit) & (U1)TRIPCOM_MS_NVMSTS_FAIL);
        u1_t_stsbit = u1_t_sucbit | u1_t_faibit;
    }
    return(u1_t_stsbit);
}

/*===================================================================================================================================*/
/*  static void     vd_s_DteEdCgRea(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DteEdCgRea(void)
{
    st_s_dte_ed_prm.u2_cg_def       = (U2)0U;
    st_s_dte_ed_prm.u2_cg_min       = (U2)0U;
    st_s_dte_ed_prm.u2_cg_max       = (U2)0U;
    st_s_dte_ed_prm.u1_khcor_per    = (U1)100U;
    st_s_dte_ed_prm.u1_fulcor_per   = (U1)100U;
    st_s_dte_ed_prm.u1_g_min_per    = (U1)50U;
    st_s_dte_ed_prm.u1_g_cen_per    = (U1)100U;
    st_s_dte_ed_prm.u1_g_max_per    = (U1)200U;

    vd_g_DteEdCfgPrm(&st_s_dte_ed_prm);
}

/*===================================================================================================================================*/
/*  static void     vd_s_DteEdCgplspccTo0p001kmpl(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DteEdCgplspccTo0p001kmpl(void)
{
    U4  u4_tp_rslt[CALC_U8_NUM_RSLT];
    U4  u4_tp_arg[CALC_U8_NUM_TERM];
    U1  u1_t_rslt;

    u4_tp_rslt[CALC_U8_QUO] = (U4)0U;
    u4_tp_rslt[CALC_U8_RES] = (U4)0U;
    u4_tp_arg[CALC_U8_LO]   = (U4)100000U;
    u4_tp_arg[CALC_U8_HI]   = (U4)u2_s_dte_ed_bra_cg;
    u4_tp_arg[CALC_U8_DIV]  = (U4)DTE_ED_PLSP1KM;
    u1_t_rslt               = u1_g_MuldivU8(&u4_tp_arg[0], &u4_tp_rslt[0]);
    if((u1_t_rslt & (U1)(CALC_U8_RSLT_OVRFLW_U4 | CALC_U8_RSLT_DIVBYZERO)) != (U1)0U){
        u2_s_dte_ed_cg_0p001kmpl = (U2)U2_MAX;
    }
    else if((u1_t_rslt & (U1)CALC_U8_RSLT_ZERO) != (U1)0U){
        u2_s_dte_ed_cg_0p001kmpl = (U2)0U;
    }
    else{
        if(u4_tp_rslt[CALC_U8_QUO] >= (U2)U2_MAX){
            u2_s_dte_ed_cg_0p001kmpl = (U2)U2_MAX;
        }
        else{
            if(u4_tp_rslt[CALC_U8_RES] >= (U4)(DTE_ED_PLSP1KM >> 1)){
                u2_s_dte_ed_cg_0p001kmpl = (U2)u4_tp_rslt[CALC_U8_QUO] + (U2)1U;
            }
            else{
                u2_s_dte_ed_cg_0p001kmpl = (U2)u4_tp_rslt[CALC_U8_QUO];
            }
        }
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_DteEdRunIntCnt(const U2 u2_a_SPD)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DteEdRunIntCnt(const U2 u2_a_SPD)
{
    if(u2_a_SPD > u2_s_DTE_ED_STOPJDG){
        if(u1_s_dte_ed_runintvl_cnt >= ((U1)U1_MAX - (U1)1U)){
            u1_s_dte_ed_runintvl_cnt = (U1)U1_MAX;
        }
        else{
            u1_s_dte_ed_runintvl_cnt++;
        }
    }
}

/*===================================================================================================================================*/
/*  static U2       u2_s_DteEdSpdChk(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2       u2_s_DteEdSpdChk(void)
{
    U2          u2_t_spd;
    U1          u1_t_sts;

    u2_t_spd = (U2)0U;
    u1_t_sts = u1_g_TripsnsrVspKmph(&u2_t_spd);
    if(u1_t_sts != (U1)0U){
        u2_t_spd = (U2)0U;
    }
    return(u2_t_spd);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*    Change History                                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version         Date        Author   Change Description                                                                          */
/* ---------        ----------  -------  ------------------------------------------------------------------------------------------- */
/*  0.1.0           2006.10.12  MK       新規作成                                                                                    */
/*  0.1.0-dev1      2006.11.10  MK       学習燃費varの配列外アクセスガード追加、RECAL失敗時安全のためRECALRDYへ遷移する処理追加      */
/*  0.1.0-dev2      2006.11.20  MK       4Byte*4Btye後の下位4Byte加算桁上げ時の処理修正、単位MAXガード処理修正                       */
/*  0.1.0-dev3      2006.11.22  MK       表示距離補正係数をKSにかけるよう修正                                                        */
/*  0.1.0-dev4      2006.11.22  MK       キャスト修正                                                                                */
/*  0.1.0-dev5      2006.12.04  MK       状態変数RAM化け時ガード追加                                                                 */
/*  0.1.0-dev6      2006.12.15  MK       UPDT関数引数にリセット要求追加(実処理差分なし)                                              */
/*  0.1.1           2007.01.11  MK       CH情報を.hに用意、CHによる切り分け情報テーブルを構造体に変更                                */
/*  0.2.0-dev0      2007.02.20  MK       0.1.0イベント終了 0.2.0へ移行                                                               */
/*  0.2.0-dev1      2007.03.10  MK       KSのLSBを0.1に変更、電子遅延をALL メートル減算に変更、KH判定をKS判定に変更                  */
/*  0.2.0-dev2      2007.03.13  MK       状態遷移処理にて電子遅延用RAMクリア処理実施                                                 */
/*  0.2.0-dev3      2007.03.21  MK       減算RAMクリア処理変更、TC算出タイミング変更、電子遅延サブ状態バックグランド処理追加         */
/*  0.2.0-dev4      2007.04.04  MK       バッググランド関数内キャスト修正                                                            */
/*  0.2.0-dev5      2007.04.09  MK       単位異常時KSを強制的に0にする処理削除(減算はKM固定で問題なしとなったため)                   */
/*  0.2.0-dev6      2007.04.10  MK       KH演算時のオート変数名とキャスト修正                                                        */
/*  1.0.0           2007.07.12  MK       コメント修正                                                                                */
/*  1.1.0           2007.12.04  HK       計測最大値取得方法を変更                                                                    */
/*  1.1.1           2008.03.20  HK       走行判定車速・表示距離補正判定車速のマクロ定義をcrsrng.prmへ移動                            */
/*  P0.0.0          2009.09.14  YN       1.1.1を元にSPF (BSW for Meter) 対応                                                         */
/*  P0.0.1          2010.06.10  KI       Change Historyの修正                                                                        */
/*  P1.0.0          2010.10.14  MK       #pragma segment命令追加                                                                     */
/*  P2.0.0          2012.02.20  MK       停車判定車速を0km/h⇒1.75km/hに変更,航続可能距離専用の給油判定に変更                        */
/*  P2.0.0-740A-1   2014.11.12  TS       ドライブモニタEEPROM記憶対応                                                                */
/*  P2.0.0-740A-2   2015.02.04  KO       学習燃費リセット対応                                                                        */
/*  P2.0.0-010B-1   2015.03.23  SM       #pragma segment命令削除                                                                     */
/*  P2.0.0-010B-2   2015.03.31  MN       BackUpRAM変数使用箇所をRIMのRead/Write関数に置き換え                                        */
/*  P2.0.0-010B-3   2015.03.31  HK       ECU_Lib対応                                                                                 */
/*                                       vd_g_Mulu44からu1_g_MulU8に置き換え                                                         */
/*                                       vd_g_Divu84からu1_g_DivU8に置き換え                                                         */
/*  P2.0.0-010B-4   2015.06.10  HK       RIM 不要なRead処理の削除、関数先頭にRead処理追加(変数初期化漏れのため)                      */
/*  P2.0.0-010B-5   2015.06.18  HK       ECU_Lib対応                                                                                 */
/*                                       除算処理の判定処理を修正                                                                    */
/*  P2.0.0-010B-6   2015.11.27  SM       RIM correspondence                                                                          */
/*  P2.0.0-010B-7   2015.11.30  SM       Max guard add (vd_s_DteEdCgUpdt())                                                          */
/*  P2.0.0-010B-8   2016.03.18  SO       QAC correspondence                                                                          */
/*  P2.0.0-010B-9   2016.03.23  SO       Initialization leakage correspondence                                                       */
/*  P2.0.0-010B-10  2016.03.24  EK       RANGE update timing change (Delete Condition IG ON)                                         */
/*  P3.1.0-010B-11  2016.03.25  SO       RIM correspondence                                                                          */
/*  P3.1.0-010B-12  2016.04.04  SO       Delete unnecessary if statement                                                             */
/*  P3.1.0-010B-13  2016.04.05  SO       Change RIM Read / Write timing                                                              */
/*  P3.1.0-010B-14  2016.05.25  EK       Add Interface Write Cg                                                                      */
/*  P3.1.0-010B-15  2016.05.25  SO       Response when receiving the unsupport engine type                                           */
/*  P3.1.0-010B-16  2016.06.13  SO       Change:It not to use a return value.                                                        */
/*  P3.1.0-010B-17  2016.07.14  EK       QAC correspondence(No.570)                                                                  */
/*  2.0.0           2021.11.16  TA(M)    Re New                                                                                      */
/*  2.1.1           2022.02.07  TA(M)    Change the condition to transition to the fail state                                        */
/*  2.2.0           2022.04.14  TA(M)    Change the condition to Cg transition to the fail state                                     */
/*                                       Fixed Range to be subtracted when EMGF = 1                                                  */
/*  2.2.1           2022.12.13  TA(M)    Change mile conversion formula                                                              */
/*  2.2.2           2024.11.21  TH       Fix : Cg Calcurate                                                                          */
/*  2.3.0           02/18/2025  MaO(M)   Add privacy data delete/result API                                                          */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  19PFv3-1 04/03/2024  DR       Deleted engine type and info functions                                                             */
/*  19PFv3-2 12/24/2024  SH       Change Rental Car Mode timing to same Out Of Range                                                 */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*    * MK = Masahiro Kuno, DensoTechno                                                                                              */
/*    * HK = Hideki Kitahara, DensoTechno                                                                                            */
/*    * YN = Yoshihiro Nakai, DensoTechno                                                                                            */
/*    * KI = ITO Kiyohiro, ATEC INC.                                                                                                 */
/*    * TS = Tomomasa Sakata                                                                                                         */
/*    * KO = Kana Okazaki                                                                                                            */
/*    * SM = Shinji Maekawa                                                                                                          */
/*    * MN = Masato Nakata                                                                                                           */
/*    * HK = Hisanori Kawasaki                                                                                                       */
/*    * SO = Shintarou Oosumi                                                                                                        */
/*    * EK = Eiji Kito                                                                                                               */
/*    * TA(M) = Teruyuki Anjima, NTT Data MSE                                                                                        */
/*    * DR   = Dyan Reyes, DTPH                                                                                                      */
/*    * TH   = Taisuke Hirakawa, KSE                                                                                                 */
/*    * SH   = Sae Hirose, Denso Techno                                                                                              */
/*    * MaO(M) = Masayuki Okada, NTT Data MSE                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
