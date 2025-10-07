/* 2.1.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  HudDimmer Adjudt Frill Duty                                                                                                      */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HDIMADJFRILL_C_MAJOR                  (2)
#define HDIMADJFRILL_C_MINOR                  (1)
#define HDIMADJFRILL_C_PATCH                  (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hdimmgr_cfg_private.h"

#include "oxcan.h"

#include "veh_opemd.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HDIMADJFRILL_C_MAJOR != HDIMADJ_CFG_H_MAJOR) || \
     (HDIMADJFRILL_C_MINOR != HDIMADJ_CFG_H_MINOR))
#error "hdimmgr_adj_frill.c and hdimmgr_adj_cfg_private.h are inconsistent!"
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
#define HDIMADJFRILL_CDDATA_FAIL                  (0xfffff)                     /* OTHFRLL: Fail data                                */
#define HDIMADJFRILL_CDDATA_INIT                  (0xffffe)                     /* OTHFRLL: Initial data                             */
#define HDIMADJFRILL_CDDATA_MAX                   (0xf4240)                     /* OTHFRLL: MAX data 40000cd/m2(LSB=0.04cd/m2)       */
#define HDIMADJFRILL_CDDATA_LSB                   (40)                          /* OTHFRLL: LSB                                      */

#define HDIMADJFRILL_CDDATA_INMAX                 (9999999)                     /* Max data 9999.999cd/m2(LSB=0.001cd/m2)            */
#define HDIMADJFRILL_CDDATA_INDEF                 (4700)                        /* Default 4.7cd/m2(LSB=0.001cd/m2)                  */

#define HDIMADJFRILL_DTCTTMNG_TIM                 (300 / HDIMMGR_BASE_TASKTIM)  /* illuminance data Update Times                     */

#define HDIMADJFRILL_WEIAVESTS_1ST                (0)                           /* Illuminance Average Status:1st                    */
#define HDIMADJFRILL_WEIAVESTS_2ND                (1)                           /* Illuminance Average Status:2nd                    */
#define HDIMADJFRILL_WEIAVESTS_NRL                (2)                           /* Illuminance Average Status:Normal                 */

#define HDIMADJFRILL_AVE2ND_DIV                   (2)                           /* Illuminance Caluclation:Division(for 2nd)         */
#define HDIMADJFRILL_AVE2ND_OFFSET                (HDIMADJFRILL_AVE2ND_DIV / 2) /* Illuminance Caluclation:Offset(for 2nd)           */
#define HDIMADJFRILL_AVE_OFST                     (2)                           /* Illuminance Caluclation:Offset                    */
#define HDIMADJFRILL_AVE_MULL                     (1)                           /* Illuminance Caluclation:MULL(for Brighter)        */
#define HDIMADJFRILL_AVEDIV_FAILSAFEVAL           (8)                           /* Illuminance Caluclation:Division(for failsafe)    */
#define HDIMADJFRILL_AVEDIV_MIN                   (1)                           /* Illuminance Caluclation:Division Minimum          */

#define HDIMADJFRILL_DUTY_MAX                     (HDIMMGR_BASE_DUTYMAX)
#define HDIMADJFRILL_DUTY_MIN                     (HDIMADJ_DUTY_0PER)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macros                                                                                                                           */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4    u4_s_hdimadj_frill_in;                                             /* hdimfrill.c:input  (Othfrill Sensor)              */
static U1    u1_s_hdimadj_frill_insts;

static U4    u4_s_hdimadj_frill_dtctin;                                         /* hdimfrill:output (Ambient Illuminance)            */
static U1    u1_s_hdimadj_frill_dtctsts;
static U1    u1_s_hdimadj_frill_dtcttmngcnt;                                    /* illuminance data Update Times                     */

static U4    u4_s_hdimadj_frill_ave;
static U1    u1_s_hdimadj_frill_sts;
static U4    u4_s_hdimadj_frill_sum;
static U1    u1_s_hdimadj_frill_prediv;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Variable Definitions                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HDIMADJFRILL_CDM2IDX_NUM                  (21)

static const U4 u4_sp_HDIMADJFRILL_CDM2_X[HDIMADJFRILL_CDM2IDX_NUM] =
{
    (U4)0,          /* Table CdM2 Index 1 */
    (U4)134,        /* Table CdM2 Index 2 */
    (U4)200,        /* Table CdM2 Index 3 */
    (U4)267,        /* Table CdM2 Index 4 */
    (U4)400,        /* Table CdM2 Index 5 */
    (U4)667,        /* Table CdM2 Index 6 */
    (U4)1000,       /* Table CdM2 Index 7 */
    (U4)1320,       /* Table CdM2 Index 8 */
    (U4)1534,       /* Table CdM2 Index 9 */
    (U4)2134,       /* Table CdM2 Index 10 */
    (U4)2800,       /* Table CdM2 Index 11 */
    (U4)3600,       /* Table CdM2 Index 12 */
    (U4)4667,       /* Table CdM2 Index 13 */
    (U4)20000,      /* Table CdM2 Index 14 */
    (U4)86667,      /* Table CdM2 Index 15 */
    (U4)261467,     /* Table CdM2 Index 16 */
    (U4)376134,     /* Table CdM2 Index 17 */
    (U4)541067,     /* Table CdM2 Index 18 */
    (U4)778267,     /* Table CdM2 Index 19 */
    (U4)1119467,    /* Table CdM2 Index 20 */
    (U4)9500000     /* Table CdM2 Index 21 */
};

static const U2 u2_sp_HDIMADJFRILL_DUTY_Y[HDIMSTEP_STEP_NUM][HDIMADJFRILL_CDM2IDX_NUM] =
{
    {    /* STEP 11 */
        (U2)423,      /* Table CdM2 Index 1 */
        (U2)423,      /* Table CdM2 Index 2 */
        (U2)423,      /* Table CdM2 Index 3 */
        (U2)423,      /* Table CdM2 Index 4 */
        (U2)423,      /* Table CdM2 Index 5 */
        (U2)423,      /* Table CdM2 Index 6 */
        (U2)423,      /* Table CdM2 Index 7 */
        (U2)423,      /* Table CdM2 Index 8 */
        (U2)489,      /* Table CdM2 Index 9 */
        (U2)669,      /* Table CdM2 Index 10 */
        (U2)867,      /* Table CdM2 Index 11 */
        (U2)1102,     /* Table CdM2 Index 12 */
        (U2)1411,     /* Table CdM2 Index 13 */
        (U2)5652,     /* Table CdM2 Index 14 */
        (U2)22870,    /* Table CdM2 Index 15 */
        (U2)65529,    /* Table CdM2 Index 16 */
        (U2)65535,    /* Table CdM2 Index 17 */
        (U2)65535,    /* Table CdM2 Index 18 */
        (U2)65535,    /* Table CdM2 Index 19 */
        (U2)65535,    /* Table CdM2 Index 20 */
        (U2)65535     /* Table CdM2 Index 21 */
    },
    {    /* STEP 10 */
        (U2)299,      /* Table CdM2 Index 1 */
        (U2)299,      /* Table CdM2 Index 2 */
        (U2)299,      /* Table CdM2 Index 3 */
        (U2)299,      /* Table CdM2 Index 4 */
        (U2)299,      /* Table CdM2 Index 5 */
        (U2)299,      /* Table CdM2 Index 6 */
        (U2)299,      /* Table CdM2 Index 7 */
        (U2)299,      /* Table CdM2 Index 8 */
        (U2)345,      /* Table CdM2 Index 9 */
        (U2)473,      /* Table CdM2 Index 10 */
        (U2)613,      /* Table CdM2 Index 11 */
        (U2)779,      /* Table CdM2 Index 12 */
        (U2)998,      /* Table CdM2 Index 13 */
        (U2)3996,     /* Table CdM2 Index 14 */
        (U2)16171,    /* Table CdM2 Index 15 */
        (U2)46336,    /* Table CdM2 Index 16 */
        (U2)65534,    /* Table CdM2 Index 17 */
        (U2)65535,    /* Table CdM2 Index 18 */
        (U2)65535,    /* Table CdM2 Index 19 */
        (U2)65535,    /* Table CdM2 Index 20 */
        (U2)65535     /* Table CdM2 Index 21 */
    },
    {    /* STEP 9 */
        (U2)212,      /* Table CdM2 Index 1 */
        (U2)212,      /* Table CdM2 Index 2 */
        (U2)212,      /* Table CdM2 Index 3 */
        (U2)212,      /* Table CdM2 Index 4 */
        (U2)212,      /* Table CdM2 Index 5 */
        (U2)212,      /* Table CdM2 Index 6 */
        (U2)212,      /* Table CdM2 Index 7 */
        (U2)212,      /* Table CdM2 Index 8 */
        (U2)244,      /* Table CdM2 Index 9 */
        (U2)335,      /* Table CdM2 Index 10 */
        (U2)434,      /* Table CdM2 Index 11 */
        (U2)551,      /* Table CdM2 Index 12 */
        (U2)706,      /* Table CdM2 Index 13 */
        (U2)2826,     /* Table CdM2 Index 14 */
        (U2)11435,    /* Table CdM2 Index 15 */
        (U2)32765,    /* Table CdM2 Index 16 */
        (U2)46340,    /* Table CdM2 Index 17 */
        (U2)65535,    /* Table CdM2 Index 18 */
        (U2)65535,    /* Table CdM2 Index 19 */
        (U2)65535,    /* Table CdM2 Index 20 */
        (U2)65535     /* Table CdM2 Index 21 */
    },
    {    /* STEP 8 */
        (U2)150,      /* Table CdM2 Index 1 */
        (U2)150,      /* Table CdM2 Index 2 */
        (U2)150,      /* Table CdM2 Index 3 */
        (U2)150,      /* Table CdM2 Index 4 */
        (U2)150,      /* Table CdM2 Index 5 */
        (U2)150,      /* Table CdM2 Index 6 */
        (U2)150,      /* Table CdM2 Index 7 */
        (U2)150,      /* Table CdM2 Index 8 */
        (U2)173,      /* Table CdM2 Index 9 */
        (U2)237,      /* Table CdM2 Index 10 */
        (U2)307,      /* Table CdM2 Index 11 */
        (U2)390,      /* Table CdM2 Index 12 */
        (U2)499,      /* Table CdM2 Index 13 */
        (U2)1998,     /* Table CdM2 Index 14 */
        (U2)8086,     /* Table CdM2 Index 15 */
        (U2)23168,    /* Table CdM2 Index 16 */
        (U2)32767,    /* Table CdM2 Index 17 */
        (U2)46342,    /* Table CdM2 Index 18 */
        (U2)65535,    /* Table CdM2 Index 19 */
        (U2)65535,    /* Table CdM2 Index 20 */
        (U2)65535     /* Table CdM2 Index 21 */
    },
    {    /* STEP 7 */
        (U2)106,      /* Table CdM2 Index 1 */
        (U2)106,      /* Table CdM2 Index 2 */
        (U2)106,      /* Table CdM2 Index 3 */
        (U2)106,      /* Table CdM2 Index 4 */
        (U2)106,      /* Table CdM2 Index 5 */
        (U2)106,      /* Table CdM2 Index 6 */
        (U2)106,      /* Table CdM2 Index 7 */
        (U2)106,      /* Table CdM2 Index 8 */
        (U2)122,      /* Table CdM2 Index 9 */
        (U2)167,      /* Table CdM2 Index 10 */
        (U2)217,      /* Table CdM2 Index 11 */
        (U2)276,      /* Table CdM2 Index 12 */
        (U2)353,      /* Table CdM2 Index 13 */
        (U2)1413,     /* Table CdM2 Index 14 */
        (U2)5717,     /* Table CdM2 Index 15 */
        (U2)16382,    /* Table CdM2 Index 16 */
        (U2)23170,    /* Table CdM2 Index 17 */
        (U2)32769,    /* Table CdM2 Index 18 */
        (U2)46341,    /* Table CdM2 Index 19 */
        (U2)65535,    /* Table CdM2 Index 20 */
        (U2)65535     /* Table CdM2 Index 21 */
    },
    {    /* STEP 6 */
        (U2)75,       /* Table CdM2 Index 1 */
        (U2)75,       /* Table CdM2 Index 2 */
        (U2)75,       /* Table CdM2 Index 3 */
        (U2)75,       /* Table CdM2 Index 4 */
        (U2)75,       /* Table CdM2 Index 5 */
        (U2)75,       /* Table CdM2 Index 6 */
        (U2)75,       /* Table CdM2 Index 7 */
        (U2)75,       /* Table CdM2 Index 8 */
        (U2)86,       /* Table CdM2 Index 9 */
        (U2)118,      /* Table CdM2 Index 10 */
        (U2)153,      /* Table CdM2 Index 11 */
        (U2)195,      /* Table CdM2 Index 12 */
        (U2)250,      /* Table CdM2 Index 13 */
        (U2)999,      /* Table CdM2 Index 14 */
        (U2)4043,     /* Table CdM2 Index 15 */
        (U2)11584,    /* Table CdM2 Index 16 */
        (U2)16384,    /* Table CdM2 Index 17 */
        (U2)23171,    /* Table CdM2 Index 18 */
        (U2)32768,    /* Table CdM2 Index 19 */
        (U2)46340,    /* Table CdM2 Index 20 */
        (U2)46341     /* Table CdM2 Index 21 */
    },
    {    /* STEP 5 */
        (U2)53,       /* Table CdM2 Index 1 */
        (U2)53,       /* Table CdM2 Index 2 */
        (U2)53,       /* Table CdM2 Index 3 */
        (U2)53,       /* Table CdM2 Index 4 */
        (U2)53,       /* Table CdM2 Index 5 */
        (U2)53,       /* Table CdM2 Index 6 */
        (U2)53,       /* Table CdM2 Index 7 */
        (U2)53,       /* Table CdM2 Index 8 */
        (U2)61,       /* Table CdM2 Index 9 */
        (U2)84,       /* Table CdM2 Index 10 */
        (U2)108,      /* Table CdM2 Index 11 */
        (U2)138,      /* Table CdM2 Index 12 */
        (U2)176,      /* Table CdM2 Index 13 */
        (U2)706,      /* Table CdM2 Index 14 */
        (U2)2859,     /* Table CdM2 Index 15 */
        (U2)8191,     /* Table CdM2 Index 16 */
        (U2)11585,    /* Table CdM2 Index 17 */
        (U2)16384,    /* Table CdM2 Index 18 */
        (U2)23170,    /* Table CdM2 Index 19 */
        (U2)32767,    /* Table CdM2 Index 20 */
        (U2)32768     /* Table CdM2 Index 21 */
    },
    {    /* STEP 4 */
        (U2)37,       /* Table CdM2 Index 1 */
        (U2)37,       /* Table CdM2 Index 2 */
        (U2)37,       /* Table CdM2 Index 3 */
        (U2)37,       /* Table CdM2 Index 4 */
        (U2)37,       /* Table CdM2 Index 5 */
        (U2)37,       /* Table CdM2 Index 6 */
        (U2)37,       /* Table CdM2 Index 7 */
        (U2)37,       /* Table CdM2 Index 8 */
        (U2)43,       /* Table CdM2 Index 9 */
        (U2)59,       /* Table CdM2 Index 10 */
        (U2)77,       /* Table CdM2 Index 11 */
        (U2)97,       /* Table CdM2 Index 12 */
        (U2)125,      /* Table CdM2 Index 13 */
        (U2)500,      /* Table CdM2 Index 14 */
        (U2)2021,     /* Table CdM2 Index 15 */
        (U2)5792,     /* Table CdM2 Index 16 */
        (U2)8192,     /* Table CdM2 Index 17 */
        (U2)11585,    /* Table CdM2 Index 18 */
        (U2)16384,    /* Table CdM2 Index 19 */
        (U2)23170,    /* Table CdM2 Index 20 */
        (U2)23170     /* Table CdM2 Index 21 */
    },
    {    /* STEP 3 */
        (U2)26,       /* Table CdM2 Index 1 */
        (U2)26,       /* Table CdM2 Index 2 */
        (U2)26,       /* Table CdM2 Index 3 */
        (U2)26,       /* Table CdM2 Index 4 */
        (U2)26,       /* Table CdM2 Index 5 */
        (U2)26,       /* Table CdM2 Index 6 */
        (U2)26,       /* Table CdM2 Index 7 */
        (U2)26,       /* Table CdM2 Index 8 */
        (U2)31,       /* Table CdM2 Index 9 */
        (U2)42,       /* Table CdM2 Index 10 */
        (U2)54,       /* Table CdM2 Index 11 */
        (U2)69,       /* Table CdM2 Index 12 */
        (U2)88,       /* Table CdM2 Index 13 */
        (U2)353,      /* Table CdM2 Index 14 */
        (U2)1429,     /* Table CdM2 Index 15 */
        (U2)4096,     /* Table CdM2 Index 16 */
        (U2)5792,     /* Table CdM2 Index 17 */
        (U2)8192,     /* Table CdM2 Index 18 */
        (U2)11585,    /* Table CdM2 Index 19 */
        (U2)16384,    /* Table CdM2 Index 20 */
        (U2)16384     /* Table CdM2 Index 21 */
    },
    {    /* STEP 2 */
        (U2)19,       /* Table CdM2 Index 1 */
        (U2)19,       /* Table CdM2 Index 2 */
        (U2)19,       /* Table CdM2 Index 3 */
        (U2)19,       /* Table CdM2 Index 4 */
        (U2)19,       /* Table CdM2 Index 5 */
        (U2)19,       /* Table CdM2 Index 6 */
        (U2)19,       /* Table CdM2 Index 7 */
        (U2)19,       /* Table CdM2 Index 8 */
        (U2)22,       /* Table CdM2 Index 9 */
        (U2)30,       /* Table CdM2 Index 10 */
        (U2)38,       /* Table CdM2 Index 11 */
        (U2)49,       /* Table CdM2 Index 12 */
        (U2)62,       /* Table CdM2 Index 13 */
        (U2)250,      /* Table CdM2 Index 14 */
        (U2)1011,     /* Table CdM2 Index 15 */
        (U2)2896,     /* Table CdM2 Index 16 */
        (U2)4096,     /* Table CdM2 Index 17 */
        (U2)5793,     /* Table CdM2 Index 18 */
        (U2)8192,     /* Table CdM2 Index 19 */
        (U2)11585,    /* Table CdM2 Index 20 */
        (U2)11585     /* Table CdM2 Index 21 */
    },
    {    /* STEP 1 */
        (U2)13,       /* Table CdM2 Index 1 */
        (U2)13,       /* Table CdM2 Index 2 */
        (U2)13,       /* Table CdM2 Index 3 */
        (U2)13,       /* Table CdM2 Index 4 */
        (U2)13,       /* Table CdM2 Index 5 */
        (U2)13,       /* Table CdM2 Index 6 */
        (U2)13,       /* Table CdM2 Index 7 */
        (U2)13,       /* Table CdM2 Index 8 */
        (U2)15,       /* Table CdM2 Index 9 */
        (U2)21,       /* Table CdM2 Index 10 */
        (U2)27,       /* Table CdM2 Index 11 */
        (U2)34,       /* Table CdM2 Index 12 */
        (U2)44,       /* Table CdM2 Index 13 */
        (U2)177,      /* Table CdM2 Index 14 */
        (U2)715,      /* Table CdM2 Index 15 */
        (U2)2048,     /* Table CdM2 Index 16 */
        (U2)2896,     /* Table CdM2 Index 17 */
        (U2)4096,     /* Table CdM2 Index 18 */
        (U2)5793,     /* Table CdM2 Index 19 */
        (U2)8192,     /* Table CdM2 Index 20 */
        (U2)8192      /* Table CdM2 Index 21 */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void  vd_s_HdimadjFrillReadFrill(void);
static U4    u4_s_HdimadjFrillFrill_CdCal(const U4 u4_a_CD);

static U1    u1_s_HdimadjFrillCalcAveDuty(void);
static U4    u4_s_HdimadjFrillWeiAve(const U4 u4_a_ILLMN, const U4 u4_a_ILLMNAVE);

static U2    u2_s_HdimadjFrillGetTgtDuty(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  HudDimmer Adjust Duty Initialize                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments    -                                                                                                                   */
/*  Return       -                                                                                                                   */
/*===================================================================================================================================*/
void vd_g_HdimadjFrillInit(void)
{
    u4_s_hdimadj_frill_in    = (U4)HDIMADJFRILL_CDDATA_INDEF;
    u1_s_hdimadj_frill_insts = (U1)HDIMMGR_INSTS_UNDET;

    u4_s_hdimadj_frill_dtctin      = (U4)HDIMADJFRILL_CDDATA_INDEF;
    u1_s_hdimadj_frill_dtctsts     = (U1)HDIMMGR_INSTS_UNDET;
    u1_s_hdimadj_frill_dtcttmngcnt = (U1)0;

    u4_s_hdimadj_frill_ave    = (U4)0;
    u4_s_hdimadj_frill_sum    = (U4)0;
    u1_s_hdimadj_frill_sts    = (U1)HDIMADJFRILL_WEIAVESTS_1ST;
    u1_s_hdimadj_frill_prediv = (U1)HDIMADJFRILL_AVEDIV_FAILSAFEVAL;
}

/*===================================================================================================================================*/
/*  HudDimmer Adjust Duty Update                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   * u2_ap_tgtduty : Target Duty                                                                                        */
/*  Return      u1_t_ret : Frill Sensor Status(TRUE:valid,FALSE:invalid)                                                             */
/*===================================================================================================================================*/
U1      u1_g_HdimadjFrilldutyUpdt(U2 * u2_ap_tgtduty)
{
    U1          u1_t_valid;

    vd_s_HdimadjFrillReadFrill();
    u1_t_valid       = u1_s_HdimadjFrillCalcAveDuty();
    (*u2_ap_tgtduty) = u2_s_HdimadjFrillGetTgtDuty();

    return(u1_t_valid);
}

/*===================================================================================================================================*/
/*  U1      u1_g_HdimadjFrillGetOthfrillRawVal(U4 * u4_a_cdm2)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
U1      u1_g_HdimadjFrillGetOthfrillRawVal(U4 * u4_a_cdm2)
{
    (*u4_a_cdm2) = u4_s_hdimadj_frill_in;
    return(u1_s_hdimadj_frill_insts);
}

/*===================================================================================================================================*/
/*  Illuminance Data Average                                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments     : -->  u4_a_ILLMN   : Latest Illuminance                                                                           */
/*  Return        : -->  u4_t_ave     : Average Illuminance                                                                          */
/*===================================================================================================================================*/
static U1 u1_s_HdimadjFrillCalcAveDuty(void)
{
    U4  u4_t_illmn;
    U1  u1_t_valid;

    if(u1_s_hdimadj_frill_dtcttmngcnt >= (U1)HDIMADJFRILL_DTCTTMNG_TIM){
        u1_s_hdimadj_frill_dtcttmngcnt = (U1)0;
        u4_s_hdimadj_frill_dtctin      = u4_s_hdimadj_frill_in;
        u1_s_hdimadj_frill_dtctsts     = u1_s_hdimadj_frill_insts;
        /*-------------------------------------------------------------------*/
        u4_t_illmn = u4_s_hdimadj_frill_dtctin;
        if(u4_t_illmn > (U4)HDIMADJFRILL_CDDATA_INMAX){
            u4_t_illmn = (U4)HDIMADJFRILL_CDDATA_INMAX;
        }
        u4_s_hdimadj_frill_ave = u4_s_HdimadjFrillWeiAve(u4_t_illmn, u4_s_hdimadj_frill_ave);
    }
    u1_s_hdimadj_frill_dtcttmngcnt++;                       /* PRQA S 3383 # over detection */
    /*-----------------------------------------------------------------------*/
    u1_t_valid = (U1)FALSE;
    if(u1_s_hdimadj_frill_dtctsts == (U1)HDIMMGR_INSTS_NML){
        u1_t_valid = (U1)TRUE;
    }
    return(u1_t_valid);
}

/*===================================================================================================================================*/
/*  Illuminance Average                                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments     : -->  u4_a_ILLMN   : Latest Illuminance                                                                           */
/*                : -->  u4_a_ILLMNAVE: Illuminance Current Average Value                                                            */
/*  Return        : <--  u4_t_ave     : Average Illuminance                                                                          */
/*===================================================================================================================================*/
static U4 u4_s_HdimadjFrillWeiAve(const U4 u4_a_ILLMN, const U4 u4_a_ILLMNAVE)
{
    U4          u4_t_ave;
    U1          u1_t_div;
    U1          u1_t_offset;
    U1          u1_t_mull;

    u4_t_ave = (U4)0U;

    if(u4_a_ILLMN >= u4_a_ILLMNAVE){    /* Darker to Brighter   */
        u1_t_div = u1_CALIB_MCUID0584_ATSSUPAVECNT;
    }
    else{                               /* Brighter to Darker   */
        u1_t_div = u1_CALIB_MCUID0585_ATSSDNAVECNT;
    }
    if(u1_t_div < (U1)HDIMADJFRILL_AVEDIV_MIN){
        u1_t_div = (U1)HDIMADJFRILL_AVEDIV_FAILSAFEVAL;
    }
    u1_t_offset = u1_t_div / (U1)HDIMADJFRILL_AVE_OFST;
    u1_t_mull   = u1_t_div - (U1)HDIMADJFRILL_AVE_MULL;

    switch(u1_s_hdimadj_frill_sts){
        case (U1)HDIMADJFRILL_WEIAVESTS_1ST:
            u4_s_hdimadj_frill_sum = u4_a_ILLMN;
            u1_s_hdimadj_frill_sts = (U1)HDIMADJFRILL_WEIAVESTS_2ND;
            break;
        case (U1)HDIMADJFRILL_WEIAVESTS_2ND:
            u4_s_hdimadj_frill_sum += u4_a_ILLMN;                                                                       /* PRQA S 3383 # over detection */
            u4_t_ave = (u4_s_hdimadj_frill_sum + (U4)HDIMADJFRILL_AVE2ND_OFFSET) / (U4)HDIMADJFRILL_AVE2ND_DIV;         /* PRQA S 3383 # over detection */
            u4_s_hdimadj_frill_sum = u4_t_ave * (U4)u1_t_mull;                                                          /* PRQA S 3383 # over detection */
            u1_s_hdimadj_frill_sts = (U1)HDIMADJFRILL_WEIAVESTS_NRL;
            break;
        case (U1)HDIMADJFRILL_WEIAVESTS_NRL:
            if(u1_t_div != u1_s_hdimadj_frill_prediv){
                u4_s_hdimadj_frill_sum = u4_a_ILLMNAVE * (U4)u1_t_mull;                                                 /* PRQA S 3383 # over detection */
            }
            u4_s_hdimadj_frill_sum += u4_a_ILLMN;                                                                       /* PRQA S 3383 # over detection */
            u4_t_ave = (u4_s_hdimadj_frill_sum + (U4)u1_t_offset) / (U4)u1_t_div;                                       /* PRQA S 3383 # over detection */
            u4_s_hdimadj_frill_sum -= u4_t_ave;                                                                         /* PRQA S 3383 # over detection */
            break;
        default:
            u4_t_ave = u4_a_ILLMN;
            u4_s_hdimadj_frill_sum = u4_t_ave * (U4)u1_t_mull;                                                          /* PRQA S 3383 # over detection */
            u1_s_hdimadj_frill_sts = (U1)HDIMADJFRILL_WEIAVESTS_NRL;
            break;
    }

    u1_s_hdimadj_frill_prediv = u1_t_div;
    return(u4_t_ave);
}

/*===================================================================================================================================*/
/*   Target Duty Caluculation                                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments     : --> u4_a_ILLMN  : Illuminance                                                                                    */
/*  Return        : <-- u2_t_duty   : Target Duty                                                                                    */
/*===================================================================================================================================*/
static U2 u2_s_HdimadjFrillGetTgtDuty(void)
{
    U4          u4_t_step;
    U2          u2_t_duty;
    const U2*   u2_tp_tbl;
    const U4*   u4_tp_tbl;

    u4_t_step = (U4)HDIMSTEP_STEP_DEF;
    (void)u1_g_HdimstepGetStepVal(&u4_t_step);

    u2_t_duty = (U2)HDIMADJ_DUTY_0PER;
    if(u4_t_step < (U4)HDIMSTEP_STEP_NUM){
        u2_tp_tbl = &u2_sp_HDIMADJFRILL_DUTY_Y[u4_t_step][0];
        u4_tp_tbl = &u4_sp_HDIMADJFRILL_CDM2_X[0];
        u2_t_duty = u2_g_HdimadjCalcDuty(u4_s_hdimadj_frill_ave, u2_tp_tbl, u4_tp_tbl, (U1)HDIMADJFRILL_CDM2IDX_NUM);
    }

    if(u2_t_duty >= (U2)HDIMADJFRILL_DUTY_MAX){
        u2_t_duty = (U2)HDIMADJFRILL_DUTY_MAX;
    }
    else if(u2_t_duty <= (U2)HDIMADJFRILL_DUTY_MIN){
        u2_t_duty = (U2)HDIMADJFRILL_DUTY_MIN;
    }
    else{
        /* no processing */
    }
    return(u2_t_duty);
}

/******************* TSS Camera Illmn ******************/
/*===================================================================================================================================*/
/*  HudDimmer Frill Sensor Update                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   -                                                                                                                    */
/*  Return      -                                                                                                                    */
/*===================================================================================================================================*/
static void vd_s_HdimadjFrillReadFrill(void)
{
    U4  u4_t_rcvdt;
    U4  u4_t_in;
    U1  u1_t_insts;
    U1  u1_t_msgsts;
    U1  u1_t_ig;

    u1_t_ig = u1_g_VehopemdIgnOn();
    if(u1_t_ig == (U1)TRUE){
        u1_t_msgsts  = Com_GetIPDUStatus((PduIdType)MSG_FCM1S78_RXCH0);
        u1_t_msgsts &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
        if(u1_t_msgsts == (U1)0){
            u4_t_rcvdt = (U4)HDIMADJFRILL_CDDATA_INIT;
            (void)Com_ReceiveSignal(ComConf_ComSignal_OTHFRILL, &u4_t_rcvdt);
            if((u4_t_rcvdt != (U4)HDIMADJFRILL_CDDATA_FAIL) &&
               (u4_t_rcvdt != (U4)HDIMADJFRILL_CDDATA_INIT)){
                u4_t_in    = u4_s_HdimadjFrillFrill_CdCal(u4_t_rcvdt);
                u1_t_insts = (U1)HDIMMGR_INSTS_NML;
            }
            else if(u4_t_rcvdt == (U4)HDIMADJFRILL_CDDATA_INIT){
                u4_t_in    = (U4)HDIMADJFRILL_CDDATA_INDEF;
                u1_t_insts = (U1)HDIMMGR_INSTS_UNDET;
            }
            else{/* u4_t_rcvdt == (U4)HDIMADJFRILL_CDDATA_FAIL */
                u4_t_in    = (U4)HDIMADJFRILL_CDDATA_INDEF;
                u1_t_insts = (U1)HDIMMGR_INSTS_ERR;
            }
        }
        else if((u1_t_msgsts & (U1)COM_NO_RX) != (U1)0){
            u4_t_in    = (U4)HDIMADJFRILL_CDDATA_INDEF;
            u1_t_insts = (U1)HDIMMGR_INSTS_UNDET;
        }
        else{/* (u1_t_msgsts & (U1)COMTIMEOUT) != (U1)0) */
            u4_t_in    = (U4)HDIMADJFRILL_CDDATA_INDEF;
            u1_t_insts = (U1)HDIMMGR_INSTS_ERR;
        }
    }
    else{
        u4_t_in    = (U4)HDIMADJFRILL_CDDATA_INDEF;
        u1_t_insts = (U1)HDIMMGR_INSTS_UNDET;
    }

    u4_s_hdimadj_frill_in    = u4_t_in;
    u1_s_hdimadj_frill_insts = u1_t_insts;
}

/*===================================================================================================================================*/
/*  static U4 u4_s_HdimadjFrillFrill_CdCal(const U4 u4_a_CD)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments   : u2_a_CD               : CDDATA                                                                                     */
/*  Return      : u4_t_retcd            : LSB:0.001cd                                                                                */
/*===================================================================================================================================*/
static U4   u4_s_HdimadjFrillFrill_CdCal(const U4 u4_a_CD)
{
    U4  u4_t_retcd;                                                              /* LSB:0.001Cd/m2                                   */

    if(u4_a_CD > ((U4)U4_MAX / (U4)HDIMADJFRILL_CDDATA_LSB)){
        u4_t_retcd = (U4)HDIMADJFRILL_CDDATA_MAX;
    }
    else{
        u4_t_retcd = u4_a_CD;
    }

    u4_t_retcd = u4_t_retcd * (U4)HDIMADJFRILL_CDDATA_LSB;                      /* PRQA S 3383 # over detection */

    return (u4_t_retcd);
}
/******************* TSS Camera Illmn ******************/

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version          Date        Author  Change Description                                                                          */
/* ---------------   ----------  ------  ------------------------------------------------------------------------------------------- */
/* 1.0.0             2020.03.09  HO      New                                                                                         */
/* 2.1.0             2023.09.27  AA      Applied calibration implementation                                                          */
/* 2.2.1             2024.07.02  His     Delete Calibration Guard Process.                                                           */
/*                                                                                                                                   */
/*  * HO = Hiroyuki, Oomiya, NCOS                                                                                                    */
/*  * HiS = Hidenobu Suzuki, MSE                                                                                                     */
/*  * AA = Anna Asuncion, DT                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
