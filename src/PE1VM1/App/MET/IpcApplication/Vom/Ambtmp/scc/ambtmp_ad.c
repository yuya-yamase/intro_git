/* 2.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Ambient Temprature Celsius/Fahrenheit detected by A/D                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AMBTMP_AD_C_MAJOR                         (2)
#define AMBTMP_AD_C_MINOR                         (2)
#define AMBTMP_AD_C_PATCH                         (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "ambtmp_cfg_private.h"
#include "ambtmp_ad.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((AMBTMP_AD_C_MAJOR != AMBTMP_H_MAJOR) || \
     (AMBTMP_AD_C_MINOR != AMBTMP_H_MINOR) || \
     (AMBTMP_AD_C_PATCH != AMBTMP_H_PATCH))
#error "ambtmp_ad.c and ambtmp_ad.h : source and header files are inconsistent!"
#endif

#if ((AMBTMP_AD_C_MAJOR != AMBTMP_CFG_H_MAJOR) || \
     (AMBTMP_AD_C_MINOR != AMBTMP_CFG_H_MINOR) || \
     (AMBTMP_AD_C_PATCH != AMBTMP_CFG_H_PATCH))
#error "ambtmp_ad.c and ambtmp_ad_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define AMBTMP_AD_TICK                  (20U)

#define AMBTMP_AD_SNSR_UNKNOWN          (0U)
#define AMBTMP_AD_SNSR_VALID            (1U)

#define AMBTMP_AD_STS_AD_UNKNOWN        (0x0001U)
#define AMBTMP_AD_STS_AD_SNSRMAL_TO     (0x0002U)
#define AMBTMP_AD_STS_AD_SNSRMAL        (0x0004U)
#define AMBTMP_AD_STS_SMPL_INI_COMP     (0x0010U)
#define AMBTMP_AD_STS_SMPL_NRM_COMP     (0x0020U)
#define AMBTMP_AD_STS_SMPL_INTV         (0x0040U)
#define AMBTMP_AD_STS_UPDT              (0x0080U)
#define AMBTMP_AD_STS_TNOW_SELECTED     (0x1000U)
#define AMBTMP_AD_STS_AD_IGOFF_UNK      (0x4000U)
#define AMBTMP_AD_STS_BON               (0x8000U)

#define AMBTMP_AD_STS_NUM_AD            (8U)
#define AMBTMP_AD_STS_BIT_AD            (AMBTMP_AD_STS_AD_UNKNOWN     | \
                                         AMBTMP_AD_STS_AD_SNSRMAL_TO  | \
                                         AMBTMP_AD_STS_AD_SNSRMAL)

#define AMBTMP_AD_STS_SMPLBIT           (AMBTMP_AD_STS_SMPL_INI_COMP | \
                                         AMBTMP_AD_STS_SMPL_NRM_COMP | \
                                         AMBTMP_AD_STS_UPDT)

#define AMBTMP_AD_STS_COMPBIT           (AMBTMP_AD_STS_SMPL_INI_COMP | \
                                         AMBTMP_AD_STS_SMPL_NRM_COMP)

#define AMBTMP_AD_CAL_LEN_EVT           (8U) 
#define AMBTMP_AD_CAL_EVT_SP_LOW        (0x00U) /*           Speed < 15km/h */
#define AMBTMP_AD_CAL_EVT_SP_MID        (0x01U) /* 15km/h <= Speed < 25km/h */
#define AMBTMP_AD_CAL_EVT_SP__HI        (0x02U) /* 25km/h <= Speed          */
#define AMBTMP_AD_CAL_EVT_OLD_HI        (0x04U)

#define AMBTMP_AD_NUM_CAL               (4U)
#define AMBTMP_AD_CAL____IGOFF          (0U)
#define AMBTMP_AD_CAL_IMMEDIAT          (1U)
#define AMBTMP_AD_CAL_SLOW_SEL          (2U)
#define AMBTMP_AD_CAL_SLOW_NOW          (3U)

#define AMBTMP_AD_SMPL_INTV_TIM         (240U)
#define AMBTMP_AD_SMPL_INTV_CNT         (AMBTMP_AD_SMPL_INTV_TIM / AMBTMP_AD_TICK)

#define AMBTMP_AD_SMPL_INI_TIMS         ( 4U)
#define AMBTMP_AD_SMPL_INI_SHFT         ( 2U)   /* Div AMBTMP_AD_SMPL_INI_TIMS = Shift AMBTMP_AD_SMPL_INI_SHFT*/
#define AMBTMP_AD_SMPL_NRM_TIMS         (16U)
#define AMBTMP_AD_SMPL_NRM_SHFT         ( 4U)   /* Div AMBTMP_AD_SMPL_NRM_TIMS = Shift AMBTMP_AD_SMPL_NRM_SHFT*/

#define AMBTMP_AD_RUNTIM_MAX            (0xfffffffeU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2       u2_s_ambtmp_ad_sts;
static U2       u2_s_ambtmp_ad_err_to;
static U2       u2_s_ambtmp_ad_lastad;
static U2       u2_s_ambtmp_ad_told;
static U2       u2_s_ambtmp_ad_tnow;

static U1       u1_s_ambtmp_ad_smpl_intv;     /* for 240 ms       */
static U1       u1_s_ambtmp_ad_smpl_tims;     /* for 16 times     */
static U4       u4_s_ambtmp_ad_sum;
static U1       u1_s_ambtmp_ad_cal;
static U4       u4_s_ambtmp_ad_runtim;
static U1       u1_s_ambtmp_ad_60m_over;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void     vd_s_AmbtmpAdSmplIntv(void);
static void     vd_s_AmbtmpAdRngChk(void);
static void     vd_s_AmbtmpAdAve(void);
static void     vd_s_AmbtmpIniSync(U2 * u2p_a_cel);
static U2       u2_s_AmbtmpAdTNowUpdt(const U4 u4_t_AD);
static U2       u2_s_AmbtmpAdMin(const U2 u2_a_CEL1, const U2 u2_a_CEL2);
static U1       u1_s_AmbtmpAdSpdChk(void);
static void     vd_s_AmbtmpAdCalIgoff(U2 * u2p_a_cel);
static void     vd_s_AmbtmpAdCalImm(U2 * u2p_a_cel);
static void     vd_s_AmbtmpAdCalSlowSel(U2 * u2p_a_cel);
static void     vd_s_AmbtmpAdCalSlowNow(U2 * u2p_a_cel);
static void     vd_s_AmbtmpAdRuntim(void);
static U1       u1_s_AmbtmpAdIgoff60min(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void   vd_g_AmbtmpAdBonInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_g_AmbtmpAdBonInit(void)
{
    u2_s_ambtmp_ad_sts       = (U2)(AMBTMP_AD_STS_AD_UNKNOWN | AMBTMP_AD_STS_BON | AMBTMP_AD_STS_AD_IGOFF_UNK);
    u2_s_ambtmp_ad_err_to    = (U2)0U;
    u2_s_ambtmp_ad_lastad    = (U2)0U;
    u2_s_ambtmp_ad_told      = (U2)AMBTMP_DEG_UNK;  /* B-Backup RAM */
    vd_g_Ambtmp_Rim_WriteU2(u2_g_AMBTMP_AD_RIMID_TOLD, u2_s_ambtmp_ad_told);
    u2_s_ambtmp_ad_tnow      = (U2)AMBTMP_DEG_UNK;

    u1_s_ambtmp_ad_smpl_intv = (U1)U1_MAX;
    u1_s_ambtmp_ad_smpl_tims = (U1)0U;
    u4_s_ambtmp_ad_sum       = (U4)0U;
    u1_s_ambtmp_ad_cal       = (U1)AMBTMP_AD_CAL____IGOFF;
    u4_s_ambtmp_ad_runtim    = (U4)U4_MAX;
    u1_s_ambtmp_ad_60m_over  = (U1)FALSE;
}
/*===================================================================================================================================*/
/*  void   vd_g_AmbtmpAdRstWkInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_g_AmbtmpAdRstWkInit(void)
{
    U1  u1_t_sts;
    U2  u2_t_data;
    
    u2_s_ambtmp_ad_sts       = (U2)AMBTMP_AD_STS_AD_UNKNOWN;
    u2_s_ambtmp_ad_err_to    = (U2)0U;
    u2_s_ambtmp_ad_lastad    = (U2)0U;

    u2_t_data = (U2)0U;
    u1_t_sts  = u1_g_Rim_ReadU2withStatus((U2)u2_g_AMBTMP_AD_RIMID_TOLD, &u2_t_data) & (U1)RIM_RESULT_KIND_MASK;
    if(u1_t_sts != (U1)RIM_RESULT_KIND_OK){
        u2_s_ambtmp_ad_told = (U2)AMBTMP_DEG_UNK;
    }
    else{
        u2_s_ambtmp_ad_told = u2_t_data;
    }
    u2_s_ambtmp_ad_tnow      = (U2)AMBTMP_DEG_UNK;

    u1_s_ambtmp_ad_smpl_intv = (U1)U1_MAX;
    u1_s_ambtmp_ad_smpl_tims = (U1)0U;     /* for 16 times     */
    u4_s_ambtmp_ad_sum       = (U4)0U;
    u1_s_ambtmp_ad_cal       = (U1)AMBTMP_AD_CAL____IGOFF;
    u4_s_ambtmp_ad_runtim    = (U4)U4_MAX;
    u1_s_ambtmp_ad_60m_over  = (U1)FALSE;
}

/*===================================================================================================================================*/
/*  U1   u1_g_AmbtmpAd(U2 * u2p_a_cel)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1   u1_g_AmbtmpAd(U2 * u2p_a_cel)
{
    static const U1 u1_sp_AMBTMP_AD_CAL_TR[AMBTMP_AD_CAL_LEN_EVT * AMBTMP_AD_NUM_CAL] = {
        (U1)AMBTMP_AD_CAL_IMMEDIAT,   (U1)AMBTMP_AD_CAL_IMMEDIAT,  (U1)AMBTMP_AD_CAL_IMMEDIAT,   (U1)AMBTMP_AD_CAL_IMMEDIAT, /* 000b */
        (U1)AMBTMP_AD_CAL_IMMEDIAT,   (U1)AMBTMP_AD_CAL_IMMEDIAT,  (U1)AMBTMP_AD_CAL_SLOW_SEL,   (U1)AMBTMP_AD_CAL_SLOW_NOW, /* 001b */
        (U1)AMBTMP_AD_CAL_SLOW_SEL,   (U1)AMBTMP_AD_CAL_SLOW_SEL,  (U1)AMBTMP_AD_CAL_SLOW_SEL,   (U1)AMBTMP_AD_CAL_SLOW_NOW, /* 010b */
        (U1)AMBTMP_AD_CAL_IMMEDIAT,   (U1)AMBTMP_AD_CAL_IMMEDIAT,  (U1)AMBTMP_AD_CAL_SLOW_SEL,   (U1)AMBTMP_AD_CAL_SLOW_NOW, /* 011b */
        (U1)AMBTMP_AD_CAL_IMMEDIAT,   (U1)AMBTMP_AD_CAL_IMMEDIAT,  (U1)AMBTMP_AD_CAL_IMMEDIAT,   (U1)AMBTMP_AD_CAL_IMMEDIAT, /* 100b */
        (U1)AMBTMP_AD_CAL_IMMEDIAT,   (U1)AMBTMP_AD_CAL_IMMEDIAT,  (U1)AMBTMP_AD_CAL_SLOW_NOW,   (U1)AMBTMP_AD_CAL_SLOW_NOW, /* 101b */
        (U1)AMBTMP_AD_CAL_SLOW_NOW,   (U1)AMBTMP_AD_CAL_SLOW_NOW,  (U1)AMBTMP_AD_CAL_SLOW_NOW,   (U1)AMBTMP_AD_CAL_SLOW_NOW, /* 110b */
        (U1)AMBTMP_AD_CAL_IMMEDIAT,   (U1)AMBTMP_AD_CAL_IMMEDIAT,  (U1)AMBTMP_AD_CAL_SLOW_SEL,   (U1)AMBTMP_AD_CAL_SLOW_NOW  /* 111b */
    };
    static void    (* const fp_sp_vd_AMBTMP_AD_CAL[AMBTMP_AD_NUM_CAL])(U2 * u2p_a_cel) ={
        &vd_s_AmbtmpAdCalIgoff,     /* #define AMBTMP_AD_CAL____IGOFF        (0U)  */
        &vd_s_AmbtmpAdCalImm,       /* #define AMBTMP_AD_CAL_IMMEDIAT        (1U)  */
        &vd_s_AmbtmpAdCalSlowSel,   /* #define AMBTMP_AD_CAL_SLOW_SEL        (2U)  */
        &vd_s_AmbtmpAdCalSlowNow    /* #define AMBTMP_AD_CAL_SLOW_NOW        (3U)  */
    };
    static const U1 u1_s_AMBTMP_AD_STS[AMBTMP_AD_STS_NUM_AD] = {
        (U1)AMBTMP_STS_VALID,       /* 000b */
        (U1)AMBTMP_STS_UNKNOWN,     /* 001b */
        (U1)AMBTMP_STS_SNSRERROR,   /* 010b */
        (U1)AMBTMP_STS_SNSRERROR,   /* 011b */
        (U1)AMBTMP_STS_VALID,       /* 100b */
        (U1)AMBTMP_STS_SNSRERROR,   /* 101b */
        (U1)AMBTMP_STS_SNSRERROR,   /* 110b */
        (U1)AMBTMP_STS_SNSRERROR    /* 111b */
    };
    
    U1 u1_t_sts;
    U1 u1_t_igon;
    U1 u1_t_evt;
    U1 u1_t_prests;
    U1 u1_t_60m_over;
    U1 u1_t_inicomp;

    u1_t_igon   = u1_g_AmbtmpIgnon();
    u1_t_prests = u1_s_ambtmp_ad_cal;
    if((u1_s_ambtmp_ad_cal == (U1)AMBTMP_AD_CAL____IGOFF) &&
       (u1_t_igon          == (U1)TRUE                  )){
        u1_t_60m_over = u1_s_AmbtmpAdIgoff60min();
        if(u1_t_60m_over == (U1)TRUE){
            u1_s_ambtmp_ad_60m_over  = (U1)TRUE;
            }
        else{
            u1_s_ambtmp_ad_60m_over  = (U1)FALSE;
        }
    }

    vd_s_AmbtmpAdSmplIntv();
    vd_s_AmbtmpAdRngChk();
    vd_s_AmbtmpAdAve();
    vd_s_AmbtmpIniSync(u2p_a_cel);

    u1_t_inicomp = u1_g_AmbtmpAdInitComp();
    if(u1_t_inicomp == (U1)TRUE){
        if(u1_t_igon == (U1)TRUE){
            u1_t_evt = u1_s_AmbtmpAdSpdChk();
            if(u2_s_ambtmp_ad_tnow < u2_s_ambtmp_ad_told){
                u1_t_evt |= (U1)AMBTMP_AD_CAL_EVT_OLD_HI;
            }
            if(u1_s_ambtmp_ad_cal < (U1)AMBTMP_AD_NUM_CAL){
                u1_s_ambtmp_ad_cal = u1_sp_AMBTMP_AD_CAL_TR[(u1_t_evt * (U1)AMBTMP_AD_NUM_CAL) + u1_s_ambtmp_ad_cal];
            }
            else{
                u1_s_ambtmp_ad_cal = (U1)AMBTMP_AD_CAL_IMMEDIAT;
            }
        }
        else{
            if(u1_t_prests != (U1)AMBTMP_AD_CAL____IGOFF){
                vd_s_AmbtmpAdCalImm(u2p_a_cel);
            }
            u1_s_ambtmp_ad_cal  = (U1)AMBTMP_AD_CAL____IGOFF;
        }
        (fp_sp_vd_AMBTMP_AD_CAL[u1_s_ambtmp_ad_cal])(u2p_a_cel);
        vd_g_Rim_WriteU2((U2)u2_g_AMBTMP_AD_RIMID_TOLD, u2_s_ambtmp_ad_told);
    }
    u1_t_sts = u1_s_AMBTMP_AD_STS[u2_s_ambtmp_ad_sts & (U2)AMBTMP_AD_STS_BIT_AD];
    return(u1_t_sts);
}

/*===================================================================================================================================*/
/*  U1      u1_g_AmbtmpAdInitComp(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_AmbtmpAdInitComp(void)
{
    U1  u1_t_comp;

    u1_t_comp = (U1)FALSE;
    if((u2_s_ambtmp_ad_sts & (U2)AMBTMP_AD_STS_SMPL_INI_COMP) != (U2)0U){
        u1_t_comp = (U1)TRUE;
    }
    return(u1_t_comp);
}

/*===================================================================================================================================*/
/*  static void     vd_s_AmbtmpIniSync(U2 * u2p_a_cel)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_AmbtmpIniSync(U2 * u2p_a_cel)
{
    if((u2_s_ambtmp_ad_sts & (U2)AMBTMP_AD_STS_SMPL_INI_COMP) != (U2)0U){
        if(((u2_s_ambtmp_ad_sts & (U2)AMBTMP_AD_STS_BON) != (U2)0U  ) ||
            (u1_s_ambtmp_ad_60m_over                     == (U1)TRUE)){
            u2_s_ambtmp_ad_told = u2_s_ambtmp_ad_tnow;
            (*u2p_a_cel)        = u2_s_ambtmp_ad_tnow;
            u2_s_ambtmp_ad_sts &= ((U2)U2_MAX ^ (U2)AMBTMP_AD_STS_BON);
            u1_s_ambtmp_ad_60m_over = (U1)FALSE;
        }
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_AmbtmpAdSmplIntv(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_AmbtmpAdSmplIntv(void)
{
    if(u1_s_ambtmp_ad_smpl_intv < (U1)AMBTMP_AD_SMPL_INTV_CNT){
        u1_s_ambtmp_ad_smpl_intv++;
    }
    else{
        u1_s_ambtmp_ad_smpl_intv = (U1)0U;
    }
    if(u1_s_ambtmp_ad_smpl_intv == (U1)AMBTMP_AD_SMPL_INTV_CNT){
        u1_s_ambtmp_ad_smpl_intv = (U1)0U;
        u2_s_ambtmp_ad_sts      |= (U2)AMBTMP_AD_STS_SMPL_INTV;
    }
    else{
        u2_s_ambtmp_ad_sts &= ((U2)U2_MAX ^ (U2)AMBTMP_AD_STS_SMPL_INTV);
    }
}

/*===================================================================================================================================*/
/*  static void     vd_s_AmbtmpAdRngChk(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_AmbtmpAdRngChk(void)
{
    static const U2 u2_s_AMBTMP_ERR_TO = ((U2)60000U / (U2)AMBTMP_AD_SMPL_INTV_TIM); /* 60s(=1min) is the range error judgment threshold */
    U1              u1_t_sts;
    U2              u2_t_ad;

    if((u2_s_ambtmp_ad_sts & (U2)AMBTMP_AD_STS_SMPL_INTV) != (U2)0U){
        u2_t_ad  = (U2)0U;
        u1_t_sts = u1_g_AmbtmpAdCfgReAd(&u2_t_ad);
        if((u1_t_sts == (U1)FALSE           ) || 
           (u2_t_ad  >= u2_g_AMBTMP_AD_RNG_H) ||
           (u2_t_ad  <  u2_g_AMBTMP_AD_RNG_L)){
            u1_s_ambtmp_ad_smpl_intv  = (U1)0U;
            u2_s_ambtmp_ad_sts       &= ((U2)U2_MAX ^ (U2)AMBTMP_AD_STS_SMPLBIT);
            u1_s_ambtmp_ad_smpl_tims  = (U1)0U;
            u4_s_ambtmp_ad_sum        = (U4)0U;
            u2_s_ambtmp_ad_lastad     = (U2)0U;
            u2_s_ambtmp_ad_sts       |= (U2)AMBTMP_AD_STS_AD_SNSRMAL;
            if(u2_s_ambtmp_ad_err_to < (U2)U2_MAX){
                u2_s_ambtmp_ad_err_to++;
            }
            if((u2_s_ambtmp_ad_sts & (U2)AMBTMP_AD_STS_AD_IGOFF_UNK) != (U2)0U){
                u2_s_ambtmp_ad_err_to = (U2)U2_MAX; 
            }
        }
        else{
            if((u2_s_ambtmp_ad_sts & (U2)AMBTMP_AD_STS_AD_SNSRMAL) != (U2)0U){
                u2_s_ambtmp_ad_sts       &= ((U2)U2_MAX ^ (U2)AMBTMP_AD_STS_SMPLBIT);
                u2_s_ambtmp_ad_sts       |= (U2)AMBTMP_AD_STS_AD_UNKNOWN;
                u1_s_ambtmp_ad_smpl_tims  = (U1)0U;
                u4_s_ambtmp_ad_sum        = (U4)0U;
            }
            u2_s_ambtmp_ad_lastad  = u2_t_ad;
            u2_s_ambtmp_ad_sts    &= ((U2)U2_MAX ^ (U2)AMBTMP_AD_STS_AD_SNSRMAL);
            u2_s_ambtmp_ad_err_to  = (U2)0U;
        }
        if(u2_s_ambtmp_ad_err_to > u2_s_AMBTMP_ERR_TO){
            u2_s_ambtmp_ad_sts |= (U2)AMBTMP_AD_STS_AD_SNSRMAL_TO;
        }
        else{
            u2_s_ambtmp_ad_sts &= ((U2)U2_MAX ^ (U2)AMBTMP_AD_STS_AD_SNSRMAL_TO);
        }
    }
}
/*===================================================================================================================================*/
/*  static void     vd_s_AmbtmpAdAve(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_AmbtmpAdAve(void)
{
    U4              u4_t_ad;

    if((u2_s_ambtmp_ad_sts & (U2)AMBTMP_AD_STS_SMPL_INTV) != (U2)0U){
        if(((U4)U4_MAX - (U4)u2_s_ambtmp_ad_lastad) >= u4_s_ambtmp_ad_sum){
            u4_s_ambtmp_ad_sum += (U4)u2_s_ambtmp_ad_lastad;
        }
        else{
            u4_s_ambtmp_ad_sum = (U4)U4_MAX;
        }
        if(u1_s_ambtmp_ad_smpl_tims < (U1)AMBTMP_AD_SMPL_NRM_TIMS){
            u1_s_ambtmp_ad_smpl_tims++;
        }
        if((u2_s_ambtmp_ad_sts & (U2)AMBTMP_AD_STS_SMPL_INI_COMP) != (U2)0U){
            if(u1_s_ambtmp_ad_smpl_tims >= (U1)AMBTMP_AD_SMPL_NRM_TIMS){
                u4_t_ad                  = u4_s_ambtmp_ad_sum >> AMBTMP_AD_SMPL_NRM_SHFT;
                u2_s_ambtmp_ad_sts      |= (U2)AMBTMP_AD_STS_SMPL_NRM_COMP;
                u2_s_ambtmp_ad_sts      &= ((U2)U2_MAX ^ (U2)AMBTMP_AD_STS_AD_UNKNOWN);
                u2_s_ambtmp_ad_sts      &= ((U2)U2_MAX ^ (U2)AMBTMP_AD_STS_AD_IGOFF_UNK);
                u2_s_ambtmp_ad_sts      |= (U2)AMBTMP_AD_STS_UPDT;
                u4_s_ambtmp_ad_sum       = (U4)0U;
                u1_s_ambtmp_ad_smpl_tims = (U1)0U;
                u2_s_ambtmp_ad_tnow      = u2_s_AmbtmpAdTNowUpdt(u4_t_ad);
            }
        }
        else{
            if(u1_s_ambtmp_ad_smpl_tims >= (U1)AMBTMP_AD_SMPL_INI_TIMS){
                u4_t_ad                  = u4_s_ambtmp_ad_sum >> AMBTMP_AD_SMPL_INI_SHFT;
                u2_s_ambtmp_ad_sts      |= (U2)AMBTMP_AD_STS_SMPL_INI_COMP;
                u2_s_ambtmp_ad_sts      |= (U2)AMBTMP_AD_STS_UPDT;
                u2_s_ambtmp_ad_sts      &= ((U2)U2_MAX ^ (U2)AMBTMP_AD_STS_AD_UNKNOWN);
                u2_s_ambtmp_ad_sts      &= ((U2)U2_MAX ^ (U2)AMBTMP_AD_STS_AD_IGOFF_UNK);
                u4_s_ambtmp_ad_sum       = (U4)0U;
                u1_s_ambtmp_ad_smpl_tims = (U1)0U;
                u2_s_ambtmp_ad_tnow      = u2_s_AmbtmpAdTNowUpdt(u4_t_ad);
            }
        }
    }
    else{
        u2_s_ambtmp_ad_sts &= ((U2)U2_MAX ^ (U2)AMBTMP_AD_STS_UPDT);
    }
}

/*===================================================================================================================================*/
/*  static U2       u2_s_AmbtmpAdTNowUpdt(const U4 u4_t_AD)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2       u2_s_AmbtmpAdTNowUpdt(const U4 u4_t_AD)
{
    static const U2 u2_s_AMBTMP_AD_MAX             = (U2)1023U;
    U2  u2_t_tnow;

    if(u4_t_AD >= (U4)U4_MAX){
        u2_t_tnow = (U2)AMBTMP_DEG_UNK;
    }
    else if(u4_t_AD > (U4)u2_s_AMBTMP_AD_MAX){
        u2_t_tnow = u2_g_AmbtmpAdCfgAd2Cel(u2_s_AMBTMP_AD_MAX);
    }
    else{
        u2_t_tnow = u2_g_AmbtmpAdCfgAd2Cel((U2)u4_t_AD);
    }
    return(u2_t_tnow);
}
/*===================================================================================================================================*/
/*  static U2       u2_s_AmbtmpAdMin(const U2 u2_a_CEL1, const U2 u2_a_CEL2)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2       u2_s_AmbtmpAdMin(const U2 u2_a_CEL1, const U2 u2_a_CEL2)
{
    U2  u2_t_cel;
    
    if(u2_a_CEL1 < u2_a_CEL2){
        u2_t_cel = u2_a_CEL1;
    }
    else{
        u2_t_cel = u2_a_CEL2;
    }
    return(u2_t_cel);
}
/*===================================================================================================================================*/
/*  static U1       u1_s_AmbtmpAdSpdChk(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_AmbtmpAdSpdChk(void)
{
    static const U2 u2_s_AMBTMP_AD_SPD_RUN   = (U2)2500U;/* 25 [km\h] */
    static const U2 u2_s_AMBTMP_AD_SPD_STOP  = (U2)1500U;/* 15 [km\h] */
    U1              u1_t_sts;
    U1              u1_t_evt;
    U2              u2_t_kmph;

    u2_t_kmph = (U2)0U;
    u1_t_sts  = u1_g_VehspdKmphInst(&u2_t_kmph, (U1)TRUE) & ((U1)VEHSPD_STSBIT_UNKNOWN | (U1)VEHSPD_STSBIT_INVALID);
    if(u1_t_sts != (U1)VEHSPD_STSBIT_VALID){
        u2_t_kmph = (U2)0U;
    }
    if(u2_t_kmph < u2_s_AMBTMP_AD_SPD_STOP){
        u1_t_evt = (U1)AMBTMP_AD_CAL_EVT_SP_LOW;
    }
    else if(u2_t_kmph < u2_s_AMBTMP_AD_SPD_RUN){
        u1_t_evt = (U1)AMBTMP_AD_CAL_EVT_SP_MID;
    }
    else{
        u1_t_evt = (U1)AMBTMP_AD_CAL_EVT_SP__HI;
    }
    return(u1_t_evt);
}
/*===================================================================================================================================*/
/*  static void     vd_s_AmbtmpAdCalIgoff(U2 * u2p_a_cel)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_AmbtmpAdCalIgoff(U2 * u2p_a_cel)
{

    u4_s_ambtmp_ad_runtim  = (U4)U4_MAX;
    u2_s_ambtmp_ad_sts    &= ((U2)U2_MAX ^ (U2)AMBTMP_AD_STS_TNOW_SELECTED);
    u2_s_ambtmp_ad_sts    |= (U2)AMBTMP_AD_STS_AD_IGOFF_UNK;

}
/*===================================================================================================================================*/
/*  static U1       u1_s_AmbtmpAdIgoff60min(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1       u1_s_AmbtmpAdIgoff60min(void)
{
    static const U4 u4_s_AMBTMP_AD_TOLD_CLR_TH_SEC = (U4)3600000U; /* = 60min = 60 * 60 * 1000*/
    U4              u4_t_igofftim;
    U1              u1_t_60min_over;

    u1_t_60min_over = (U1)FALSE;
    u4_t_igofftim   = u4_g_AmbtmpAdCfgIgoffMilliSec();
    if(u4_t_igofftim > u4_s_AMBTMP_AD_TOLD_CLR_TH_SEC){
        u1_t_60min_over = (U1)TRUE;
    }
    return(u1_t_60min_over);
}
/*===================================================================================================================================*/
/*  static void     vd_s_AmbtmpAdCalImm(U2 * u2p_a_cel)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_AmbtmpAdCalImm(U2 * u2p_a_cel)
{
    *u2p_a_cel            = u2_s_AmbtmpAdMin(*u2p_a_cel, u2_s_ambtmp_ad_tnow);
    u2_s_ambtmp_ad_told   = *u2p_a_cel;
    u4_s_ambtmp_ad_runtim = (U4)U4_MAX;
    u2_s_ambtmp_ad_sts   &= ((U2)U2_MAX ^ (U2)AMBTMP_AD_STS_TNOW_SELECTED);
}
/*===================================================================================================================================*/
/*  static void     vd_s_AmbtmpAdCalSlowSel(U2 * u2p_a_cel)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_AmbtmpAdCalSlowSel(U2 * u2p_a_cel)
{
    U2 u2_t_cel_add;
    U4 u4_t_cel_add;
    U2 u2_t_slow_comp;

    vd_s_AmbtmpAdRuntim();
    if((u2_s_ambtmp_ad_sts & (U2)AMBTMP_AD_STS_UPDT) != (U2)0U){
        if((u2_s_ambtmp_ad_sts & (U2)AMBTMP_AD_STS_TNOW_SELECTED) == (U2)0U){
            u4_t_cel_add = u4_s_ambtmp_ad_runtim / (U4)100U;
                                /* 5*10^(-3) * 100(=AMBTEMP_CEL_LSB) * 20ms(=AMBTMP_AD_TICK)/1000ms * u4_s_ambtmp_ad_runtim */
            if(u4_t_cel_add >= (U2)U2_MAX){
                u2_t_cel_add = (U2)U2_MAX;
            }
            else{
                u2_t_cel_add = (U2)u4_t_cel_add;
            }
            if(((U2)U2_MAX - u2_s_ambtmp_ad_told) < u2_t_cel_add){
                u2_t_slow_comp = (U2)U2_MAX;
            }
            else{
                u2_t_slow_comp = u2_s_ambtmp_ad_told + u2_t_cel_add;
            }
            *u2p_a_cel = u2_s_AmbtmpAdMin(u2_t_slow_comp, u2_s_ambtmp_ad_tnow);
            if(*u2p_a_cel == u2_s_ambtmp_ad_tnow){
                u2_s_ambtmp_ad_told  = u2_s_ambtmp_ad_tnow;
                u2_s_ambtmp_ad_sts  |= (U2)AMBTMP_AD_STS_TNOW_SELECTED;
            }
        }
        else{
            u2_s_ambtmp_ad_told  = u2_s_ambtmp_ad_tnow;
            *u2p_a_cel           = u2_s_ambtmp_ad_tnow;
        }
    }
}
/*===================================================================================================================================*/
/*  static void     vd_s_AmbtmpAdRuntim(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_AmbtmpAdRuntim(void)
{
    if(u4_s_ambtmp_ad_runtim == (U4)U4_MAX){
        u4_s_ambtmp_ad_runtim = (U4)0U;
    }
    else if(u4_s_ambtmp_ad_runtim < (U4)AMBTMP_AD_RUNTIM_MAX){
        u4_s_ambtmp_ad_runtim++;
    }
    else{
        /* Nothing */
    }
}
/*===================================================================================================================================*/
/*  static void     vd_s_AmbtmpAdCalSlowNow(U2 * u2p_a_cel)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_AmbtmpAdCalSlowNow(U2 * u2p_a_cel)
{
    *u2p_a_cel             = u2_s_ambtmp_ad_tnow;
    u2_s_ambtmp_ad_told    = u2_s_ambtmp_ad_tnow;
    u4_s_ambtmp_ad_runtim  = (U4)U4_MAX;
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0    04/30/2021  TA       New.                                                                                               */
/*  2.0.1    10/18/2021  TA(M)    ambtmp.c v2.0.0 -> v2.0.1.                                                                         */
/*  2.1.0    11/25/2021  TA(M)    ambtmp.c v2.0.1 -> v2.1.0.                                                                         */
/*  2.2.0    03/09/2021  TA(M)    ambtmp.c v2.1.0 -> v2.2.0.                                                                         */
/*  2.2.1    06/28/2022  TA(M)    ambtmp.c v2.2.0 -> v2.2.1.                                                                         */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
