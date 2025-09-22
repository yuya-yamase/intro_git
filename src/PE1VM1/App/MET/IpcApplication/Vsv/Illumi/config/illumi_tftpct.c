/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Illumination TFT Percent                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ILLUMI_TFT_PCT_C_MAJOR                      (1)
#define ILLUMI_TFT_PCT_C_MINOR                      (0)
#define ILLUMI_TFT_PCT_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "illumi_cfg_private.h"
#include "illumi_tftpct.h"

#include "lerp_u2.h"
#include "calibration.h"
#include "vardef_esopt.h"
#include "iohw_adc.h"
#include "scheduler.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ILLUMI_TFT_PCT_C_MAJOR != ILLUMI_TFT_PCT_H_MAJOR) || \
     (ILLUMI_TFT_PCT_C_MINOR != ILLUMI_TFT_PCT_H_MINOR) || \
     (ILLUMI_TFT_PCT_C_PATCH != ILLUMI_TFT_PCT_H_PATCH))
#error "illumi_tftpct.c and illumi_tftpct.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ILLUMI_TFTPCT_OFF                      (0U)
#define ILLUMI_TFTALPHA_OFF                    (255U)

#define ILLUMI_TFTPCT_THERM_OFS                (40U)   /* Offset:-40[cel] */
#define ILLUMI_TFTPCT_THERM_LSB                (100U)  /* LSB:0.01[cel]   */
#define ILLUMI_TFTPCT_THERM_DEF                ((25U  + ILLUMI_TFTPCT_THERM_OFS) * ILLUMI_TFTPCT_THERM_LSB)  /* Default temperature                */
#define ILLUMI_TFTPCT_THERM_UNK                ((125U + ILLUMI_TFTPCT_THERM_OFS) * ILLUMI_TFTPCT_THERM_LSB)  /* Temperature In abnormal conditions */
#define ILLUMI_TFTPCT_THERM_ROUOFF             (5U)
#define ILLUMI_TFTPCT_THERM_PRECISION          (10U)
#define ILLUMI_TFTPCT_THERM_DLYCAL_STA         ((94U  + ILLUMI_TFTPCT_THERM_OFS) * ILLUMI_TFTPCT_THERM_LSB)  /* Start thermistor temperature for using the calculation */
#define ILLUMI_TFTPCT_THERM_DLYCAL_FIN         ((101U + ILLUMI_TFTPCT_THERM_OFS) * ILLUMI_TFTPCT_THERM_LSB)  /* End thermistor temperature for using the calculation   */

#define ILLUMI_TFTPCT_MVAVGTIMS                (10U)   /* Moving Average Number */

#define ILLUMI_TFTPCT_AD_MIN                   (32U)   /* Lower limit of the AD value In normal conditions */
#define ILLUMI_TFTPCT_AD_MAX                   (941U)  /* Upper limit of the AD value In normal conditions */

#define ILLUMI_TFTPCT_DUTYLMT_LSB              (10U)   /* LSB:0.1[%] */
#define ILLUMI_TFTPCT_DUTYLMT_DEF              (100U * ILLUMI_TFTPCT_DUTYLMT_LSB) /* Default Duty                     */
#define ILLUMI_TFTPCT_DUTYLMT_UPPER            (100U * ILLUMI_TFTPCT_DUTYLMT_LSB) /* Maximum value of the upper limit */
#define ILLUMI_TFTPCT_DUTYLMT_LOWER            (30U  * ILLUMI_TFTPCT_DUTYLMT_LSB) /* Minimum value of the upper limit */
#define ILLUMI_TFTPCT_DUTYLMT_ROUOFF           (5U)
#define ILLUMI_TFTPCT_DUTYLMT_PRECISION        (10U)

#define ILLUMI_TFTPCT_PER_TO_RATE              (100U)  /* percent to rate */

#define ILLUMI_TFTPCT_DUTY_ROUOFF              (5U)

#define ILLUMI_TFTPCT_NUM_AD2CEL               (166U)
#define ILLUMI_TFTPCT_TBL_AD2CEL               ((ILLUMI_TFTPCT_NUM_AD2CEL * 2U) + 1U)

#define ILLUMI_TFTPCT_NUM_CEL2DUTY             (2U)
#define ILLUMI_TFTPCT_TBL_CEL2DUTY             ((ILLUMI_TFTPCT_NUM_CEL2DUTY * 2U) + 1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2      u2_sp_illumi_tftpct_therm[ILLUMI_TFTPCT_MVAVGTIMS];  /* Moving Average Sample       */
static U2      u2_s_illumi_tftpct_pct_uplmt;                        /* The Upper Limit             */
static U4      u4_s_illumi_tftpct_mvavgsum;                         /* The Sum of Moving Average   */
static U1      u1_s_illumi_tftpct_mvavgcnt;                         /* The Count of Moving Average */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1    u1_s_IllumiTftPct(const U2 * u2_ap_DIM_LVL);
static U2    u2_s_IllumiTftPctMvAvg(const U2 u2_a_AD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U2 u2_sp_ILLUMI_TFTPCT_ADTODEGC[ILLUMI_TFTPCT_TBL_AD2CEL]={
    (U2)ILLUMI_TFTPCT_NUM_AD2CEL,

    (U2)33U,
    (U2)34U,
    (U2)35U,
    (U2)35U,
    (U2)36U,
    (U2)37U,
    (U2)38U,
    (U2)39U,
    (U2)40U,
    (U2)41U,
    (U2)41U,
    (U2)42U,
    (U2)43U,
    (U2)44U,
    (U2)45U,
    (U2)47U,
    (U2)48U,
    (U2)49U,
    (U2)50U,
    (U2)51U,
    (U2)52U,
    (U2)54U,
    (U2)55U,
    (U2)56U,
    (U2)58U,
    (U2)59U,
    (U2)60U,
    (U2)62U,
    (U2)64U,
    (U2)65U,
    (U2)67U,
    (U2)68U,
    (U2)70U,
    (U2)72U,
    (U2)74U,
    (U2)76U,
    (U2)77U,
    (U2)79U,
    (U2)81U,
    (U2)83U,
    (U2)86U,
    (U2)88U,
    (U2)90U,
    (U2)92U,
    (U2)95U,
    (U2)97U,
    (U2)100U,
    (U2)102U,
    (U2)105U,
    (U2)108U,
    (U2)110U,
    (U2)113U,
    (U2)116U,
    (U2)119U,
    (U2)122U,
    (U2)126U,
    (U2)129U,
    (U2)132U,
    (U2)136U,
    (U2)139U,
    (U2)143U,
    (U2)147U,
    (U2)151U,
    (U2)155U,
    (U2)159U,
    (U2)163U,
    (U2)167U,
    (U2)172U,
    (U2)176U,
    (U2)181U,
    (U2)186U,
    (U2)191U,
    (U2)196U,
    (U2)201U,
    (U2)206U,
    (U2)212U,
    (U2)217U,
    (U2)223U,
    (U2)229U,
    (U2)235U,
    (U2)241U,
    (U2)248U,
    (U2)254U,
    (U2)261U,
    (U2)267U,
    (U2)274U,
    (U2)281U,
    (U2)288U,
    (U2)295U,
    (U2)303U,
    (U2)310U,
    (U2)318U,
    (U2)326U,
    (U2)334U,
    (U2)342U,
    (U2)350U,
    (U2)359U,
    (U2)367U,
    (U2)376U,
    (U2)385U,
    (U2)394U,
    (U2)403U,
    (U2)412U,
    (U2)422U,
    (U2)431U,
    (U2)440U,
    (U2)450U,
    (U2)460U,
    (U2)470U,
    (U2)479U,
    (U2)489U,
    (U2)499U,
    (U2)510U,
    (U2)520U,
    (U2)530U,
    (U2)540U,
    (U2)551U,
    (U2)561U,
    (U2)571U,
    (U2)581U,
    (U2)592U,
    (U2)602U,
    (U2)612U,
    (U2)623U,
    (U2)633U,
    (U2)643U,
    (U2)653U,
    (U2)663U,
    (U2)673U,
    (U2)683U,
    (U2)693U,
    (U2)703U,
    (U2)713U,
    (U2)722U,
    (U2)732U,
    (U2)741U,
    (U2)750U,
    (U2)759U,
    (U2)768U,
    (U2)777U,
    (U2)785U,
    (U2)794U,
    (U2)802U,
    (U2)810U,
    (U2)818U,
    (U2)825U,
    (U2)833U,
    (U2)840U,
    (U2)847U,
    (U2)854U,
    (U2)861U,
    (U2)868U,
    (U2)874U,
    (U2)880U,
    (U2)886U,
    (U2)892U,
    (U2)898U,
    (U2)903U,
    (U2)908U,
    (U2)914U,
    (U2)919U,
    (U2)923U,
    (U2)928U,
    (U2)932U,
    (U2)936U,
    (U2)941U,

    (U2)16500U,    /*AD=33*/
    (U2)16400U,    /*AD=34*/
    (U2)16200U,    /*AD=35*/
    (U2)16300U,    /*AD=35*/
    (U2)16100U,    /*AD=36*/
    (U2)16000U,    /*AD=37*/
    (U2)15900U,    /*AD=38*/
    (U2)15800U,    /*AD=39*/
    (U2)15700U,    /*AD=40*/
    (U2)15500U,    /*AD=41*/
    (U2)15600U,    /*AD=41*/
    (U2)15400U,    /*AD=42*/
    (U2)15300U,    /*AD=43*/
    (U2)15200U,    /*AD=44*/
    (U2)15100U,    /*AD=45*/
    (U2)15000U,    /*AD=47*/
    (U2)14900U,    /*AD=48*/
    (U2)14800U,    /*AD=49*/
    (U2)14700U,    /*AD=50*/
    (U2)14600U,    /*AD=51*/
    (U2)14500U,    /*AD=52*/
    (U2)14400U,    /*AD=54*/
    (U2)14300U,    /*AD=55*/
    (U2)14200U,    /*AD=56*/
    (U2)14100U,    /*AD=58*/
    (U2)14000U,    /*AD=59*/
    (U2)13900U,    /*AD=60*/
    (U2)13800U,    /*AD=62*/
    (U2)13700U,    /*AD=64*/
    (U2)13600U,    /*AD=65*/
    (U2)13500U,    /*AD=67*/
    (U2)13400U,    /*AD=68*/
    (U2)13300U,    /*AD=70*/
    (U2)13200U,    /*AD=72*/
    (U2)13100U,    /*AD=74*/
    (U2)13000U,    /*AD=76*/
    (U2)12900U,    /*AD=77*/
    (U2)12800U,    /*AD=79*/
    (U2)12700U,    /*AD=81*/
    (U2)12600U,    /*AD=83*/
    (U2)12500U,    /*AD=86*/
    (U2)12400U,    /*AD=88*/
    (U2)12300U,    /*AD=90*/
    (U2)12200U,    /*AD=92*/
    (U2)12100U,    /*AD=95*/
    (U2)12000U,    /*AD=97*/
    (U2)11900U,    /*AD=100*/
    (U2)11800U,    /*AD=102*/
    (U2)11700U,    /*AD=105*/
    (U2)11600U,    /*AD=108*/
    (U2)11500U,    /*AD=110*/
    (U2)11400U,    /*AD=113*/
    (U2)11300U,    /*AD=116*/
    (U2)11200U,    /*AD=119*/
    (U2)11100U,    /*AD=122*/
    (U2)11000U,    /*AD=126*/
    (U2)10900U,    /*AD=129*/
    (U2)10800U,    /*AD=132*/
    (U2)10700U,    /*AD=136*/
    (U2)10600U,    /*AD=139*/
    (U2)10500U,    /*AD=143*/
    (U2)10400U,    /*AD=147*/
    (U2)10300U,    /*AD=151*/
    (U2)10200U,    /*AD=155*/
    (U2)10100U,    /*AD=159*/
    (U2)10000U,    /*AD=163*/
    (U2)9900U,     /*AD=167*/
    (U2)9800U,     /*AD=172*/
    (U2)9700U,     /*AD=176*/
    (U2)9600U,     /*AD=181*/
    (U2)9500U,     /*AD=186*/
    (U2)9400U,     /*AD=191*/
    (U2)9300U,     /*AD=196*/
    (U2)9200U,     /*AD=201*/
    (U2)9100U,     /*AD=206*/
    (U2)9000U,     /*AD=212*/
    (U2)8900U,     /*AD=217*/
    (U2)8800U,     /*AD=223*/
    (U2)8700U,     /*AD=229*/
    (U2)8600U,     /*AD=235*/
    (U2)8500U,     /*AD=241*/
    (U2)8400U,     /*AD=248*/
    (U2)8300U,     /*AD=254*/
    (U2)8200U,     /*AD=261*/
    (U2)8100U,     /*AD=267*/
    (U2)8000U,     /*AD=274*/
    (U2)7900U,     /*AD=281*/
    (U2)7800U,     /*AD=288*/
    (U2)7700U,     /*AD=295*/
    (U2)7600U,     /*AD=303*/
    (U2)7500U,     /*AD=310*/
    (U2)7400U,     /*AD=318*/
    (U2)7300U,     /*AD=326*/
    (U2)7200U,     /*AD=334*/
    (U2)7100U,     /*AD=342*/
    (U2)7000U,     /*AD=350*/
    (U2)6900U,     /*AD=359*/
    (U2)6800U,     /*AD=367*/
    (U2)6700U,     /*AD=376*/
    (U2)6600U,     /*AD=385*/
    (U2)6500U,     /*AD=394*/
    (U2)6400U,     /*AD=403*/
    (U2)6300U,     /*AD=412*/
    (U2)6200U,     /*AD=422*/
    (U2)6100U,     /*AD=431*/
    (U2)6000U,     /*AD=440*/
    (U2)5900U,     /*AD=450*/
    (U2)5800U,     /*AD=460*/
    (U2)5700U,     /*AD=470*/
    (U2)5600U,     /*AD=479*/
    (U2)5500U,     /*AD=489*/
    (U2)5400U,     /*AD=499*/
    (U2)5300U,     /*AD=510*/
    (U2)5200U,     /*AD=520*/
    (U2)5100U,     /*AD=530*/
    (U2)5000U,     /*AD=540*/
    (U2)4900U,     /*AD=551*/
    (U2)4800U,     /*AD=561*/
    (U2)4700U,     /*AD=571*/
    (U2)4600U,     /*AD=581*/
    (U2)4500U,     /*AD=592*/
    (U2)4400U,     /*AD=602*/
    (U2)4300U,     /*AD=612*/
    (U2)4200U,     /*AD=623*/
    (U2)4100U,     /*AD=633*/
    (U2)4000U,     /*AD=643*/
    (U2)3900U,     /*AD=653*/
    (U2)3800U,     /*AD=663*/
    (U2)3700U,     /*AD=673*/
    (U2)3600U,     /*AD=683*/
    (U2)3500U,     /*AD=693*/
    (U2)3400U,     /*AD=703*/
    (U2)3300U,     /*AD=713*/
    (U2)3200U,     /*AD=722*/
    (U2)3100U,     /*AD=732*/
    (U2)3000U,     /*AD=741*/
    (U2)2900U,     /*AD=750*/
    (U2)2800U,     /*AD=759*/
    (U2)2700U,     /*AD=768*/
    (U2)2600U,     /*AD=777*/
    (U2)2500U,     /*AD=785*/
    (U2)2400U,     /*AD=794*/
    (U2)2300U,     /*AD=802*/
    (U2)2200U,     /*AD=810*/
    (U2)2100U,     /*AD=818*/
    (U2)2000U,     /*AD=825*/
    (U2)1900U,     /*AD=833*/
    (U2)1800U,     /*AD=840*/
    (U2)1700U,     /*AD=847*/
    (U2)1600U,     /*AD=854*/
    (U2)1500U,     /*AD=861*/
    (U2)1400U,     /*AD=868*/
    (U2)1300U,     /*AD=874*/
    (U2)1200U,     /*AD=880*/
    (U2)1100U,     /*AD=886*/
    (U2)1000U,     /*AD=892*/
    (U2)900U,      /*AD=898*/
    (U2)800U,      /*AD=903*/
    (U2)700U,      /*AD=908*/
    (U2)600U,      /*AD=914*/
    (U2)500U,      /*AD=919*/
    (U2)400U,      /*AD=923*/
    (U2)300U,      /*AD=928*/
    (U2)200U,      /*AD=932*/
    (U2)100U,      /*AD=936*/
    (U2)0U         /*AD=941*/
};

static const U2 u2_sp_ILLUMI_TFTPCT_DEGCTODUTY[ILLUMI_TFTPCT_TBL_CEL2DUTY]={
    (U2)ILLUMI_TFTPCT_NUM_CEL2DUTY,

    (U2)ILLUMI_TFTPCT_THERM_DLYCAL_STA,
    (U2)ILLUMI_TFTPCT_THERM_DLYCAL_FIN,

    (U2)ILLUMI_TFTPCT_DUTYLMT_UPPER,
    (U2)ILLUMI_TFTPCT_DUTYLMT_LOWER
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_IllumiTftPctInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_IllumiTftPctInit(void)
{
    U4      u4_t_lpcnt;
    
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)ILLUMI_TFTPCT_MVAVGTIMS; u4_t_lpcnt++){
        u2_sp_illumi_tftpct_therm[u4_t_lpcnt] = (U2)ILLUMI_TFTPCT_THERM_DEF;
    }

    u4_s_illumi_tftpct_mvavgsum  = (U4)(ILLUMI_TFTPCT_THERM_DEF * ILLUMI_TFTPCT_MVAVGTIMS);
    u1_s_illumi_tftpct_mvavgcnt  = (U1)0U;
    u2_s_illumi_tftpct_pct_uplmt = (U2)ILLUMI_TFTPCT_DUTYLMT_DEF;
}
/*===================================================================================================================================*/
/*  U2    u2_g_IllumiTftPctDuty(const U2 * u2_ap_DIM_LVL, const U2 u2_a_OW)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2    u2_g_IllumiTftPctDuty(const U2 * u2_ap_DIM_LVL, const U2 u2_a_OW)
{
    U1      u1_t_dsp;
    U1      u1_t_pct_target;
    U1      u1_t_pct_min;
    U2      u2_t_illumi_ad;
    U2      u2_t_daynight;
    U2      u2_t_therm;      /* Current thermistor temperature */
    U2      u2_t_pct;
    U2      u2_t_pct_uplmt;
    U4      u4_t_schd;

    u1_t_pct_target = u1_s_IllumiTftPct(u2_ap_DIM_LVL);
    
    u1_t_dsp = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_GVIF2_METDISP);
    if(u1_t_dsp != (U1)TRUE){
        u4_t_schd = (U4)(u4_g_SchdlrTaskActivated() & (U4)SCHDLR_TASKBIT_100MS_I);
        if(u4_t_schd != (U4)0U){
            u2_t_illumi_ad = u2_g_IoHwAdcLv((U1)ADC_CH_TFT_TH);
            u2_t_therm     = u2_s_IllumiTftPctMvAvg(u2_t_illumi_ad);
            if(u2_t_therm < (U2)ILLUMI_TFTPCT_THERM_DLYCAL_STA){
                u2_t_pct_uplmt = (U2)ILLUMI_TFTPCT_DUTYLMT_UPPER;
            }
            else if(u2_t_therm < (U2)ILLUMI_TFTPCT_THERM_DLYCAL_FIN){
                u2_t_pct_uplmt = u2_g_LerpU2(u2_t_therm, &u2_sp_ILLUMI_TFTPCT_DEGCTODUTY[0]);
            }
            else{
                u2_t_pct_uplmt = (U2)ILLUMI_TFTPCT_DUTYLMT_LOWER;
            }
            u2_s_illumi_tftpct_pct_uplmt = ((u2_t_pct_uplmt + (U2)ILLUMI_TFTPCT_DUTYLMT_ROUOFF) / (U2)ILLUMI_TFTPCT_DUTYLMT_PRECISION) * (U2)ILLUMI_TFTPCT_DUTYLMT_PRECISION;
        }

        if(u1_t_pct_target != (U1)ILLUMI_TFTPCT_OFF){
            u2_t_daynight = u2_ap_DIM_LVL[ILLUMI_DIM_LVL_DAYNIGHT];
            if(u2_t_daynight == (U2)ILLUMI_DIM_LVL_USADJ_DAY){
                u1_t_pct_min = u1_CALIB_MCUID0342_BL_PCT_DAY[CALIB_MCUID0342_BL_STEP_DAY - 1U];
            }
            else{
                u1_t_pct_min = u1_CALIB_MCUID0386_BL_PCT_NIGHT[CALIB_MCUID0386_BL_STEP_NIGHT - 1U];
            }
            u2_t_pct = (U2)(((U4)u1_t_pct_target * (U4)u2_s_illumi_tftpct_pct_uplmt) / (U4)ILLUMI_TFTPCT_PER_TO_RATE);
            u2_t_pct = (u2_t_pct + (U2)ILLUMI_TFTPCT_DUTY_ROUOFF) / (U2)ILLUMI_TFTPCT_DUTYLMT_LSB;
            if(u2_t_pct < (U2)u1_t_pct_min){
                u2_t_pct = (U2)u1_t_pct_min;
            }
            else if((U2)u1_t_pct_target < u2_t_pct){
                u2_t_pct = (U2)u1_t_pct_target;
            }
            else{
                /* Nothing */
            }
        }
        else{
            u2_t_pct = (U2)ILLUMI_TFTPCT_OFF;
        }
    }
    else{
        vd_g_IllumiTftPctInit();
        u2_t_pct = (U2)u1_t_pct_target;
    }

    return(u2_t_pct);
}
/*===================================================================================================================================*/
/*  static U1    u1_s_IllumiTftPct(const U2 * u2_ap_DIM_LVL)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_IllumiTftPct(const U2 * u2_ap_DIM_LVL)
{
    U1      u1_t_pct;
    U1      u1_t_daynight;
    U2      u2_t_lvl;

    u1_t_pct      = (U1)ILLUMI_TFTPCT_OFF;
    u1_t_daynight = (U1)u2_ap_DIM_LVL[ILLUMI_DIM_LVL_DAYNIGHT];
    if(u1_t_daynight < (U1)ILLUMI_DIM_LVL_DAYNIGHT){
        u2_t_lvl = u2_ap_DIM_LVL[u1_t_daynight];
        if(u2_t_lvl < (U2)CALIB_BL_STEP){
            u2_t_lvl = ((U2)CALIB_BL_STEP - (U2)1U) - u2_t_lvl;
            if(u1_t_daynight == (U1)ILLUMI_DIM_LVL_USADJ_DAY){
                u1_t_pct = u1_CALIB_MCUID0342_BL_PCT_DAY[u2_t_lvl];
            }
            else{
                u1_t_pct = u1_CALIB_MCUID0386_BL_PCT_NIGHT[u2_t_lvl];
            }
        }
    }
    return(u1_t_pct);
}
/*===================================================================================================================================*/
/*  U2    u2_g_IllumiTftPctAlpha(const U2 * u2_ap_DIM_LVL, const U2 u2_a_OW)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2    u2_g_IllumiTftPctAlpha(const U2 * u2_ap_DIM_LVL, const U2 u2_a_OW)
{
    U1      u1_t_daynight;
    U2      u2_t_pct;
    U2      u2_t_lvl;

    u2_t_pct      = (U2)ILLUMI_TFTALPHA_OFF;
    u1_t_daynight = (U1)u2_ap_DIM_LVL[ILLUMI_DIM_LVL_DAYNIGHT];
    if(u1_t_daynight < (U1)ILLUMI_DIM_LVL_DAYNIGHT){
        u2_t_lvl = u2_ap_DIM_LVL[u1_t_daynight];
        if(u2_t_lvl < (U2)CALIB_RGB_STEP){
            u2_t_lvl = ((U2)CALIB_RGB_STEP - (U2)1U) - u2_t_lvl;
            if(u1_t_daynight == (U1)ILLUMI_DIM_LVL_USADJ_DAY){
                u2_t_pct = (U2)u1_CALIB_MCUID0364_RGB_ALPHA_DAY[u2_t_lvl];
            }
            else{
                u2_t_pct = (U2)u1_CALIB_MCUID0408_RGB_ALPHA_NGT[u2_t_lvl];
            }
        }
    }
    return(u2_t_pct);
}
/*===================================================================================================================================*/
/*  static U2    u2_s_IllumiTftPctMvAvg(const U2 u2_a_AD)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U2    u2_s_IllumiTftPctMvAvg(const U2 u2_a_AD)
{
    U2      u2_t_therm;        /* Current thermistor temperature */
    U2      u2_t_therm_old;    /* The oldest temperature         */

    if(u1_s_illumi_tftpct_mvavgcnt >= (U1)ILLUMI_TFTPCT_MVAVGTIMS){
        u1_s_illumi_tftpct_mvavgcnt = (U1)0U;
    }
    u2_t_therm_old = u2_sp_illumi_tftpct_therm[u1_s_illumi_tftpct_mvavgcnt];

    if(((U2)ILLUMI_TFTPCT_AD_MIN < u2_a_AD                 ) &&
       (u2_a_AD                  < (U2)ILLUMI_TFTPCT_AD_MAX)){
        u2_sp_illumi_tftpct_therm[u1_s_illumi_tftpct_mvavgcnt] = u2_g_LerpU2(u2_a_AD, &u2_sp_ILLUMI_TFTPCT_ADTODEGC[0]);
    }
    else{
        u2_sp_illumi_tftpct_therm[u1_s_illumi_tftpct_mvavgcnt] = (U2)ILLUMI_TFTPCT_THERM_UNK;
    }

    u4_s_illumi_tftpct_mvavgsum += (U4)u2_sp_illumi_tftpct_therm[u1_s_illumi_tftpct_mvavgcnt];
    u4_s_illumi_tftpct_mvavgsum -= (U4)u2_t_therm_old;

    u2_t_therm = (U2)(u4_s_illumi_tftpct_mvavgsum / (U4)ILLUMI_TFTPCT_MVAVGTIMS);
    u2_t_therm = ((u2_t_therm + (U2)ILLUMI_TFTPCT_THERM_ROUOFF) / (U2)ILLUMI_TFTPCT_THERM_PRECISION) * (U2)ILLUMI_TFTPCT_THERM_PRECISION;

    u1_s_illumi_tftpct_mvavgcnt++;

    return(u2_t_therm);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    12/18/2024  KA       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  19PFv3-1  1/13/2025  SN       Change Calib Macro Name                                                                            */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * KA = Kapuri Ando, NTTD-MSE                                                                                                     */
/*  * SN = Shimon Nambu, Denso Techno                                                                                                */
/*                                                                                                                                   */
/*===================================================================================================================================*/
