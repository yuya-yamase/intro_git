/* 2.1.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  HudDimmer Adjudt Duty                                                                                                            */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HDIMADJ_C_MAJOR                  (2)
#define HDIMADJ_C_MINOR                  (1)
#define HDIMADJ_C_PATCH                  (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hdimmgr_cfg_private.h"

#include "memcpy_u4.h"
#include "memfill_u4.h"
#include "calc_u8.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HDIMADJ_C_MAJOR != HDIMADJ_CFG_H_MAJOR) || \
     (HDIMADJ_C_MINOR != HDIMADJ_CFG_H_MINOR) || \
     (HDIMADJ_C_PATCH != HDIMADJ_CFG_H_PATCH))
#error "hdimmgr_adj.c and hdimmgr_adj_cfg_private.h are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Defines                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HDIMADJ_ILLMN_0LX                    (0)                                /* Min Illuminance                                   */

#define HDIMADJ_ALLCLR                       (0)                                /* Illuminance Data:All Clear                        */
#define HDIMADJ_ERRCLR                       (1)                                /* Illuminance Data:Error Clear                      */

#define HDIMADJ_WEIAVESTS_1ST                (0)                                /* Illuminance Average Status:1st                    */
#define HDIMADJ_WEIAVESTS_2ND                (1)                                /* Illuminance Average Status:2nd                    */
#define HDIMADJ_WEIAVESTS_NRL                (2)                                /* Illuminance Average Status:Normal                 */
#define HDIMADJ_WEIAVESTS_RPDCHG             (3)                                /* Illuminance Average Status:Rapid Change           */

#define HDIMADJ_AVE2ND_DIV                   (2)                                /* Illuminance Caluclation:Division(for 2nd)         */
#define HDIMADJ_AVE2ND_OFFSET                (HDIMADJ_AVE2ND_DIV / 2)           /* Illuminance Caluclation:Offset(for 2nd)           */

#define HDIMADJ_AVE_OFST                     (2)                                /* Illuminance Caluclation:Offset                    */
#define HDIMADJ_AVE_MULL                     (1)                                /* Illuminance Caluclation:MULL(for Brighter)        */

#define HDIMADJ_DIV_FAILSAFEVAL              (8)                                /* Illuminance Caluclation:Division(for failsafe)    */
#define HDIMADJ_DIV_MIN                      (1)                                /* Illuminance Caluclation:Division : minimum        */

#define HDIMADJ_ILMMN_NUMHIS                 (15)                               /* Illuminance History Times(Don't change)           */
#define HDIMADJ_RPDCHGHIS_NUM                (5)                                /* Illuminance History Times                         */

#define HDIMADJ_AVECNT_DEF                   (8)                                /* Illuminance Duty Average Times : default          */
#define HDIMADJ_AVECNT_MIN                   (1)                                /* Illuminance Duty Average Times : minimum          */

#define HDIMADJ_DUTY_MAX                     (HDIMMGR_BASE_DUTYMAX)
#define HDIMADJ_DUTY_MIN                     (HDIMADJ_DUTY_0PER)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4               u4_s_hdimadj_illmn_ave;
static U1               u1_s_hdimadj_illmn_sts;
static U4               u4_s_hdimadj_illmn_sum;
static U1               u1_s_hdimadj_illmn_prediv;
static U1               u1_s_hdimadj_history_cnt;
static U4               u4_s_hdimadj_history[HDIMADJ_ILMMN_NUMHIS];

static U1               u1_s_hdimadj_snsrupdt_flg;

static U4               u4_s_hdimadj_outduty_sum;
static U1               u1_s_hdimadj_outduty_initon_flg;
static U1               u1_s_hdimadj_outduty_div;
static U2               u2_s_hdimadj_outduty_ave;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void      vd_s_HdimadjClrAutDat(const U1 u1_a_CLRMODE);
static U4        u4_s_HdimadjSetIllmn(const U4 u4_a_ILLMN, const U4 u4_a_ILLMNAVE, const U1 u1_a_STS);
static void      vd_s_HdimadjChkRpdChg(const U4 u4_a_ILLMN, U1 *u1_a_avests);
static U4        u4_s_HdimadjWeiAve(const U4 u4_a_ILLMN, const U4 u4_a_ILLMNAVE, U1 *u1_a_avests);

static U2        u2_s_HdimadjGetTgtDuty(const U4 u4_a_SITUAT, const U4 u4_a_STEP, const U4 u4_a_ILLMN);
static U2        u2_s_HdimadjCalcAdjDuty(const U1 u1_a_INIT, const U2 u2_a_TGTDUTY);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  HudDimmer Adjust Duty Initialize                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments    -                                                                                                                   */
/*  Return       -                                                                                                                   */
/*===================================================================================================================================*/
void vd_g_HdimadjInit(void)
{
    vd_g_HdimadjCfgInit();

    vd_s_HdimadjClrAutDat((U1)HDIMADJ_ALLCLR);
    u4_s_hdimadj_illmn_ave = (U4)HDIMADJ_ILLMN_0LX;
    u1_s_hdimadj_illmn_prediv = (U1)HDIMADJ_DIV_FAILSAFEVAL;
    u1_s_hdimadj_snsrupdt_flg = (U1)FALSE;

    u4_s_hdimadj_outduty_sum = (U4)0;
    u1_s_hdimadj_outduty_initon_flg = (U1)FALSE;
    u1_s_hdimadj_outduty_div = (U1)HDIMADJ_AVECNT_DEF;
    u2_s_hdimadj_outduty_ave = (U2)HDIMADJ_DUTY_0PER;
}

/*===================================================================================================================================*/
/*  HudDimmer Adjust Duty Update                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   * u2_ap_tgtduty : Target Duty                                                                                        */
/*              * u2_ap_adjduty : Adjust Duty                                                                                        */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_HdimadjDutyUpdt(U2 * u2_ap_tgtduty , U2 * u2_ap_adjduty)
{
    U4          u4_t_situat;
    U4          u4_t_step;
    U4          u4_t_illmn;

    U2          u2_t_tgtduty;
    U2          u2_t_adjduty;

    U1          u1_t_illmn_sts;
    U1          u1_t_act;
    U1          u1_t_init;

    u1_t_act = u1_g_HdimadjCfgActUpdt(&u1_t_illmn_sts, &u4_t_situat, &u4_t_step, &u4_t_illmn);
    u4_t_illmn = u4_s_HdimadjSetIllmn(u4_t_illmn, u4_s_hdimadj_illmn_ave, u1_t_illmn_sts);

    if((u1_t_act & (U1)HDIMADJ_ACTTYPE_ADJDUTY_BLK) == (U1)HDIMADJ_ACTTYPE_ADJDUTY_BLK){
        u4_s_hdimadj_illmn_ave = (U4)HDIMADJ_ILLMN_0LX;
        u2_t_tgtduty = (U2)HDIMADJ_DUTY_0PER;
        u1_t_init    = (U1)TRUE;
    }
    else if((u1_t_act & (U1)HDIMADJ_ACTTYPE_ADJDUTY_DEF) == (U1)HDIMADJ_ACTTYPE_ADJDUTY_DEF){
        u4_s_hdimadj_illmn_ave = u4_g_HDIMILLMN_DEF_LXDATA;
        u2_t_tgtduty = u2_s_HdimadjGetTgtDuty(u4_t_situat, u4_t_step, u4_s_hdimadj_illmn_ave);
        u1_t_init    = (U1)FALSE;
    }
    else if((u1_t_act & (U1)HDIMADJ_ACTTYPE_ADJDUTY_CAL) == (U1)HDIMADJ_ACTTYPE_ADJDUTY_CAL){
        u4_s_hdimadj_illmn_ave = u4_t_illmn;
        u2_t_tgtduty = u2_s_HdimadjGetTgtDuty(u4_t_situat, u4_t_step, u4_s_hdimadj_illmn_ave);
        u1_t_init    = (U1)FALSE;
    }
    else{
        u4_s_hdimadj_illmn_ave = (U4)HDIMADJ_ILLMN_0LX;
        u2_t_tgtduty = (U2)HDIMADJ_DUTY_0PER;
        u1_t_init    = (U1)TRUE;
    }

    u2_t_tgtduty = u2_g_HdimadjCfgDtctTgtDuty(u2_t_tgtduty);
    u2_t_adjduty = u2_s_HdimadjCalcAdjDuty(u1_t_init, u2_t_tgtduty);

    (*u2_ap_tgtduty) = u2_g_HdimmgrDutyExchgBaseToIfLSB(u2_t_tgtduty);
    (*u2_ap_adjduty) = u2_g_HdimmgrDutyExchgBaseToIfLSB(u2_t_adjduty);
}

/*===================================================================================================================================*/
/*  Illuminance Caluclation Update Hook                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
void vd_g_HdimadjHookIllmnCalUpdt(void)
{
    u1_s_hdimadj_snsrupdt_flg = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  Illuminance Date Clear                                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments     u1_a_CLRMODE:Clear Mode                                                                                            */
/*  Return        -                                                                                                                  */
/*===================================================================================================================================*/
static void vd_s_HdimadjClrAutDat(const U1 u1_a_CLRMODE)
{
    if(u1_a_CLRMODE == (U1)HDIMADJ_ALLCLR){
        u1_s_hdimadj_history_cnt = (U1)0;
        vd_g_MemfillU4(&u4_s_hdimadj_history[0], (U4)0, (U4)HDIMADJ_ILMMN_NUMHIS);
    }

    u4_s_hdimadj_illmn_sum = (U4)0;
    u1_s_hdimadj_illmn_sts = (U1)HDIMADJ_WEIAVESTS_1ST;
}

/*===================================================================================================================================*/
/*  Illuminance Data Average                                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments     : -->  u4_a_ILLMNAVE: Current Illuminance                                                                          */
/*                : -->  u4_a_ILLMN    : Latest Illuminance                                                                           */
/*                : -->  u1_a_STS     : Illuminance Status                                                                           */
/*  Return        : -->  u4_t_ave     : Average Illuminance                                                                          */
/*===================================================================================================================================*/
static U4 u4_s_HdimadjSetIllmn(const U4 u4_a_ILLMN, const U4 u4_a_ILLMNAVE, const U1 u1_a_STS)
{
    U4  u4_t_ave;
    U4  u4_t_illmn;

    u4_t_ave = u4_a_ILLMNAVE;
    u4_t_illmn = u4_a_ILLMN;

    switch(u1_a_STS){
        case (U1)HDIMMGR_INSTS_UNDET:
            vd_s_HdimadjClrAutDat((U1)HDIMADJ_ERRCLR);
            break;
        case (U1)HDIMMGR_INSTS_ERR:
            vd_s_HdimadjClrAutDat((U1)HDIMADJ_ERRCLR);
            break;
        default:
            if(u1_s_hdimadj_snsrupdt_flg == (U1)TRUE){
                if(u4_t_illmn > u4_g_HDIMILLMN_MAX_LXDATA){
                    u4_t_illmn = u4_g_HDIMILLMN_MAX_LXDATA;
                }
                vd_s_HdimadjChkRpdChg(u4_t_illmn, &u1_s_hdimadj_illmn_sts);
                u4_t_ave = u4_s_HdimadjWeiAve(u4_t_illmn, u4_a_ILLMNAVE, &u1_s_hdimadj_illmn_sts);
            }
            break;
    }

    u1_s_hdimadj_snsrupdt_flg = (U1)FALSE;

    return (u4_t_ave);
}

/*===================================================================================================================================*/
/*  Illuminance Rapid Change Judgment                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments     : -->  u4_a_ILLMN   : Latest Illuminance                                                                           */
/*                : --> *u1_a_avests  : Illuminance Average Status                                                                   */
/*  Return        -                                                                                                                  */
/*===================================================================================================================================*/
static void vd_s_HdimadjChkRpdChg(const U4 u4_a_ILLMN, U1 *u1_a_avests)
{
    U4          u4_t_history[HDIMADJ_ILMMN_NUMHIS];
    U1          u1_t_cnt;
    U1          u1_t_jdg;

    if(u1_s_hdimadj_history_cnt < (U1)HDIMADJ_RPDCHGHIS_NUM){
        u4_s_hdimadj_history[u1_s_hdimadj_history_cnt] = u4_a_ILLMN;
        u1_s_hdimadj_history_cnt++;
    }
    else{
        if(*u1_a_avests != (U1)HDIMADJ_WEIAVESTS_RPDCHG){
            for(u1_t_cnt = (U1)0; u1_t_cnt < (U1)HDIMADJ_RPDCHGHIS_NUM; u1_t_cnt++){
                u1_t_jdg = u1_g_HdimadjCfgJdgRpdChg(u4_a_ILLMN , u4_s_hdimadj_history[u1_t_cnt]);
                if(u1_t_jdg == (U1)TRUE){
                    *u1_a_avests = (U1)HDIMADJ_WEIAVESTS_RPDCHG;
                    break;
                }
            }
        }
        vd_g_MemfillU4(&u4_t_history[0], (U4)0, (U4)HDIMADJ_ILMMN_NUMHIS);
        vd_g_MemcpyU4(&u4_t_history[0], &u4_s_hdimadj_history[1], ((U4)HDIMADJ_RPDCHGHIS_NUM - (U4)1));
        vd_g_MemcpyU4(&u4_s_hdimadj_history[0], &u4_t_history[0], ((U4)HDIMADJ_RPDCHGHIS_NUM - (U4)1));
        u4_s_hdimadj_history[(U1)HDIMADJ_RPDCHGHIS_NUM - (U1)1] = u4_a_ILLMN;
    }
}

/*===================================================================================================================================*/
/*  Illuminance Average                                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments     : -->  u4_a_ILLMN   : Latest Illuminance                                                                           */
/*                : -->  u4_a_ILLMNAVE: Illuminance Current Average Value                                                            */
/*                : --> *u1_a_avests  : Illuminance Average Status                                                                   */
/*  Return        : <--  u4_t_ave     : Average Illuminance                                                                          */
/*===================================================================================================================================*/
static U4 u4_s_HdimadjWeiAve(const U4 u4_a_ILLMN, const U4 u4_a_ILLMNAVE, U1 *u1_a_avests)
{
    U4          u4_t_ave;
    U1          u1_t_isdk2br;
    U1          u1_t_div;
    U1          u1_t_offset;
    U1          u1_t_mull;

    u1_t_isdk2br = (U1)FALSE;       /* Bright to Dark   */
    if(u4_a_ILLMN >= u4_a_ILLMNAVE){
        u1_t_isdk2br = (U1)TRUE;    /* Dark   to Bright */
    }
    u1_t_div = u1_g_HdimadjCfgInMvaveNum(u1_t_isdk2br);
    if(u1_t_div < (U1)HDIMADJ_DIV_MIN){
        u1_t_div = (U1)HDIMADJ_DIV_FAILSAFEVAL;
    }
    u1_t_offset = u1_t_div / (U1)HDIMADJ_AVE_OFST;
    u1_t_mull   = u1_t_div - (U1)HDIMADJ_AVE_MULL;

    /*-----------------------------------------------------------------------*/
    u4_t_ave = (U4)HDIMADJ_ILLMN_0LX;
    switch(*u1_a_avests){
        case (U1)HDIMADJ_WEIAVESTS_1ST:
            u4_s_hdimadj_illmn_sum = u4_a_ILLMN;
            *u1_a_avests = (U1)HDIMADJ_WEIAVESTS_2ND;
            break;
        case (U1)HDIMADJ_WEIAVESTS_2ND:
            u4_s_hdimadj_illmn_sum += u4_a_ILLMN;                                                             /* PRQA S 3383 # over detection */
            u4_t_ave = (u4_s_hdimadj_illmn_sum + (U4)HDIMADJ_AVE2ND_OFFSET) / (U4)HDIMADJ_AVE2ND_DIV;         /* PRQA S 3383 # over detection */
            u4_s_hdimadj_illmn_sum = u4_t_ave * (U4)u1_t_mull;                                                /* PRQA S 3383 # over detection */
            *u1_a_avests = (U1)HDIMADJ_WEIAVESTS_NRL;
            break;
        case (U1)HDIMADJ_WEIAVESTS_NRL:
            if(u1_t_div != u1_s_hdimadj_illmn_prediv){
                u4_s_hdimadj_illmn_sum = u4_a_ILLMNAVE * (U4)u1_t_mull;                                       /* PRQA S 3383 # over detection */
            }
            u4_s_hdimadj_illmn_sum += u4_a_ILLMN;                                                             /* PRQA S 3383 # over detection */
            u4_t_ave = (u4_s_hdimadj_illmn_sum + (U4)u1_t_offset) / (U4)u1_t_div;                             /* PRQA S 3383 # over detection */
            u4_s_hdimadj_illmn_sum -= u4_t_ave;                                                               /* PRQA S 3383 # over detection */
            break;
        case (U1)HDIMADJ_WEIAVESTS_RPDCHG:
            /* break */
        default:
            u4_t_ave = u4_a_ILLMN;
            u4_s_hdimadj_illmn_sum = u4_t_ave * (U4)u1_t_mull;                                                /* PRQA S 3383 # over detection */
            *u1_a_avests = (U1)HDIMADJ_WEIAVESTS_NRL;
            break;
    }
    u1_s_hdimadj_illmn_prediv = u1_t_div;

    return(u4_t_ave);
}

/*===================================================================================================================================*/
/*   Target Duty Caluculation                                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments     : --> u4_a_SITUAT: Situation                                                                                       */
/*                : --> u4_a_STEP  : Step                                                                                            */
/*                : --> u4_a_ILLMN : Illuminance                                                                                     */
/*  Return        : <-- u2_t_duty   : Target Duty                                                                                    */
/*===================================================================================================================================*/
static U2 u2_s_HdimadjGetTgtDuty(const U4 u4_a_SITUAT, const U4 u4_a_STEP, const U4 u4_a_ILLMN)
{
    U2          u2_t_duty;
    const U2*   u2_tp_tbl;
    const U4*   u4_tp_tbl;

    u2_t_duty = (U2)HDIMADJ_DUTY_0PER;
    u2_tp_tbl = u2_gp_HdimadjCfgDmmngTbl_Y(u4_a_SITUAT, u4_a_STEP);
    u4_tp_tbl = u4_gp_HdimadjCfgDmmngTbl_X();
    if((u2_tp_tbl != vdp_PTR_NA) &&
       (u4_tp_tbl != vdp_PTR_NA)){
        u2_t_duty = u2_g_HdimadjCalcDuty(u4_a_ILLMN, u2_tp_tbl, u4_tp_tbl, u1_g_HDIMADJ_DMMNGTBL_X_NUM);
    }

    if(u2_t_duty >= (U2)HDIMADJ_DUTY_MAX){
        u2_t_duty = (U2)HDIMADJ_DUTY_MAX;
    }
    else if(u2_t_duty <= (U2)HDIMADJ_DUTY_MIN){
        u2_t_duty = (U2)HDIMADJ_DUTY_MIN;
    }
    else{
        /* no processing */
    }
    return(u2_t_duty);
}

/*===================================================================================================================================*/
/*  static U2   u2_s_HdimadjCalcAdjDuty(const U1 u1_a_INIT, const U2 u2_a_TGTDUTY)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/* Arguments    -                                                                                                                    */
/* Return       -                                                                                                                    */
/*===================================================================================================================================*/
static U2   u2_s_HdimadjCalcAdjDuty(const U1 u1_a_INIT, const U2 u2_a_TGTDUTY)
{
    U2      u2_t_adjduty;
	U1      u1_t_div;

    u1_t_div = u1_g_HdimadjCfgAdjMvaveNum();
    if(u1_t_div < (U1)HDIMADJ_AVECNT_MIN){
        u1_t_div = (U1)HDIMADJ_AVECNT_DEF;
    }

    if(u1_a_INIT == (U1)TRUE){
        u2_t_adjduty = (U2)HDIMADJ_DUTY_0PER;
        u4_s_hdimadj_outduty_sum = (U4)0;
        u1_s_hdimadj_outduty_initon_flg = (U1)FALSE;
    }
    else{
        if(u1_s_hdimadj_outduty_initon_flg != (U1)TRUE){
            u4_s_hdimadj_outduty_sum = (U4)u2_a_TGTDUTY * (U4)u1_t_div;                                       /* PRQA S 3383 # over detection */
            u1_s_hdimadj_outduty_initon_flg = (U1)TRUE;
        }
        else{
            if(u1_s_hdimadj_outduty_div != u1_t_div){
                u4_s_hdimadj_outduty_sum = (U4)u2_s_hdimadj_outduty_ave * ((U4)u1_t_div - (U4)1);             /* PRQA S 3383,3384 # over detection */
            }
            u4_s_hdimadj_outduty_sum += (U4)u2_a_TGTDUTY;                                                     /* PRQA S 3383 # over detection */
        }
        u2_t_adjduty = (U2)(u4_s_hdimadj_outduty_sum / (U4)u1_t_div);
        u4_s_hdimadj_outduty_sum -= (U4)u2_t_adjduty;                                                         /* PRQA S 3383 # over detection */
    }

    u1_s_hdimadj_outduty_div = u1_t_div;
    u2_s_hdimadj_outduty_ave = u2_t_adjduty;
    return(u2_t_adjduty);
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Private Function Definitions                                                                                                     */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  HudDimmer Table Search                                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments     : --> U4 u4_a_ILLMN : Illuminance                                                                                  */
/*                : --> U2* u2_ap_TBL : HudDimmer Table Adress                                                                       */
/*  Return        : <-- U2 u2_t_lv_trgt : Target Duty                                                                                */
/*===================================================================================================================================*/
U2  u2_g_HdimadjCalcDuty(const U4 u4_a_ILLMN, const U2 u2_ap_TBL[], const U4 u4_ap_TBL[], const U1 u1_a_X_IDX_NUM)
{
    U4          u4_t_xlo;
    U4          u4_t_xup;
    U4          u4_t_ylo;
    U4          u4_t_yup;
    U4          u4_t_tmp;
    U4          u4_tp_term1[CALC_U8_NUM_TERM];
    U4          u4_tp_term2[CALC_U8_NUM_TERM];
    U4          u4_tp_term3[CALC_U8_NUM_TERM];
    U4          u4_tp_dat1[CALC_U8_NUM_RSLT];
    U4          u4_tp_dat2[CALC_U8_NUM_RSLT];
    U4          u4_tp_dat3[CALC_U8_NUM_RSLT];

    U2          u2_t_lv_trgt;

    U1          u1_t_x_idx;
    U1          u1_t_rsltbit;

    for(u1_t_x_idx = (U1)0; u1_t_x_idx < u1_a_X_IDX_NUM; u1_t_x_idx++){
        if(u4_a_ILLMN < u4_ap_TBL[u1_t_x_idx]){
            break;
        }
    }

    if(u1_t_x_idx >= u1_a_X_IDX_NUM){
        u2_t_lv_trgt = u2_ap_TBL[u1_a_X_IDX_NUM - (U1)1];
    }
    else if(u1_t_x_idx > (U1)0){
        u4_t_xlo = u4_ap_TBL[u1_t_x_idx - (U1)1];
        u4_t_xup = u4_ap_TBL[u1_t_x_idx];
        u4_t_ylo = (U4)u2_ap_TBL[u1_t_x_idx - (U1)1];
        u4_t_yup = (U4)u2_ap_TBL[u1_t_x_idx];

        /* (u4_t_ylo * (u4_t_xup - u4_a_ILLMN)) + (u4_t_yup * (u4_a_ILLMN - u4_t_xlo))    */
        u4_tp_term1[CALC_U8_LO] = u4_t_ylo;
        u4_tp_term1[CALC_U8_HI] = u4_t_xup - u4_a_ILLMN;                                  /* PRQA S 3383 # over detection */
        u4_tp_term1[CALC_U8_DIV] = (U4)0;
        (void)u1_g_MulU8(&u4_tp_term1[0],&u4_tp_dat1[0]);

        u4_tp_term2[CALC_U8_LO] = u4_t_yup;
        u4_tp_term2[CALC_U8_HI] = u4_a_ILLMN - u4_t_xlo;                                  /* PRQA S 3383 # over detection */
        u4_tp_term2[CALC_U8_DIV] = (U4)0;
        (void)u1_g_MulU8(&u4_tp_term2[0],&u4_tp_dat2[0]);

        u4_tp_term3[CALC_U8_LO] = u4_tp_dat1[CALC_U8_LO] + u4_tp_dat2[CALC_U8_LO];
        u4_tp_term3[CALC_U8_HI] = u4_tp_dat1[CALC_U8_HI] + u4_tp_dat2[CALC_U8_HI];        /* PRQA S 3383 # over detection */
        if( (u4_tp_term3[CALC_U8_LO] < u4_tp_dat1[CALC_U8_LO]) &&
            (u4_tp_term3[CALC_U8_LO] < u4_tp_dat2[CALC_U8_LO])){
            u4_tp_term3[CALC_U8_HI]++;                                                    /* PRQA S 3383 # over detection */
        }

        /* u4_tp_dat3[] / (u4_t_xup - u4_t_xlo) */
        u4_tp_term3[CALC_U8_DIV] = u4_t_xup - u4_t_xlo;                                   /* PRQA S 3383 # over detection */
        u1_t_rsltbit = u1_g_DivU8(&u4_tp_term3[0], &u4_tp_dat3[0]);
        if((u1_t_rsltbit & (U1)CALC_U8_RSLT_DIVBYZERO) != (U1)CALC_U8_RSLT_DIVBYZERO){
            if((u1_t_rsltbit & (U1)CALC_U8_RSLT_OVRFLW_U4) == (U1)CALC_U8_RSLT_OVRFLW_U4){
                u4_t_tmp = u4_t_yup;
            }
            else{
                u4_t_tmp = u4_tp_dat3[CALC_U8_QUO];
            }
            if(u4_t_tmp >= (U4)U2_MAX){
                u2_t_lv_trgt = (U2)U2_MAX;
            }
            else{
                u2_t_lv_trgt = (U2)u4_t_tmp;
            }
        }
        else{
            u2_t_lv_trgt = (U2)u4_t_yup;
        }
    }
    else{
        u2_t_lv_trgt = u2_ap_TBL[0];
    }

    return(u2_t_lv_trgt);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version          Date        Author  Change Description                                                                          */
/* ---------------   ----------  ------  ------------------------------------------------------------------------------------------- */
/* 1.0.0             2016.03.31  HS      New                                                                                         */
/* 1.0.1             2016.07.22  HS      Illuminance Average was revised. (u4_s_HdimadjWeiAve)                                       */
/* 2.0.0             2020.02.27  MaO     Added LSB configuration.                                                                    */
/* 2.1.0             2023.09.27  AA      Applied calibration implementation                                                          */
/* 2.2.1             2024.07.02  His     Delete Calibration Guard Process.                                                           */
/*                                                                                                                                   */
/*  * HS = Hidenobu Suzuki, NCOS                                                                                                     */
/*  * HiS = Hidenobu Suzuki, MSE                                                                                                     */
/*  * MaO = Masayuki Okada, DENSO                                                                                                    */
/*  * AA = Anna Asuncion, DT                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
