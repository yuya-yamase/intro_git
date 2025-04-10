/* 2.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Status Viewer / Toyota IPC/MET Coolant Temperature Gauge - Segment                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GAGDST_TEMPSEG_CFG_C_MAJOR                 (2)
#define GAGDST_TEMPSEG_CFG_C_MINOR                 (1)
#define GAGDST_TEMPSEG_CFG_C_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "gagdst_tempseg_cfg_private.h"

#include "vardef.h"
#include "ptsctmp_cel.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((GAGDST_TEMPSEG_CFG_C_MAJOR != GAGDST_TEMPSEG_CFG_H_MAJOR) || \
     (GAGDST_TEMPSEG_CFG_C_MINOR != GAGDST_TEMPSEG_CFG_H_MINOR) || \
     (GAGDST_TEMPSEG_CFG_C_PATCH != GAGDST_TEMPSEG_CFG_H_PATCH))
#error "gagdst_tempseg_cfg.c and gagdst_tempseg_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GAGDST_TEMPSEG_NUM_CFG          (3U)
#define GAGDST_TEMPSEG_CSTD_CNV         (0U)
#define GAGDST_TEMPSEG_CSTD_HYB         (1U)
#define GAGDST_TEMPSEG_CSTD_MDE         (2U)

#define GAGDST_TEMPSEG_NODISP           (255U)

#define GAGDST_TEMPSEG_NUM_PTSYS        (16U)
#define GAGDST_TEMPSEG_NUM_DEST         (2U)

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
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2        u2_g_GAGDST_TEMPSEG_SRC_CHK  = ((U2)PTSCTMP_STSBIT_UNKNOWN |
                                                (U2)PTSCTMP_STSBIT_INVALID |
                                                (U2)PTSCTMP_STSBIT_WTSW_OP |
                                                (U2)PTSCTMP_STSBIT_WTSW_HI);

const U2        u2_g_GAGDST_TEMPSEG_SRC_UNK  = (U2)PTSCTMP_STSBIT_UNKNOWN;       /* Source Singale Valid                          */
const U2        u2_g_GAGDST_TEMPSEG_SRC_INV  = (U2)PTSCTMP_STSBIT_INVALID;       /* Source Singale Valid                          */
const U2        u2_g_GAGDST_TEMPSEG_WTSW_HI  = (U2)(PTSCTMP_STSBIT_WTSW_HI | PTSCTMP_STSBIT_WTSW_OP);  /* Source Singale WT_SW=HI */
const U1        u1_g_GAGDST_TEMPSEG_NUM_CFG  = (U1)GAGDST_TEMPSEG_NUM_CFG;    /* Num of thresh variation                       */

const U2        u2_gp_GAGDST_TEMPSEG_OWACT[GAGDST_TEMP_SEG_NUM_IOC] = { /* Target temperature of Overwirte Action.[LSB:0.01Celsius] */
    (U2)12700U,   /* Diagnosis data's byte#6 bit0 : 127 degrees[Celsius]                    */
    (U2)12000U,   /* Diagnosis data's byte#6 bit1 : 120 degrees[Celsius]                    */
    (U2)11000U,   /* Diagnosis data's byte#6 bit2 : 110 degrees[Celsius]                    */
    (U2) 9950U,    /* Diagnosis data's byte#6 bit3 : Degrees[Celsius] to lighting 4 segments */
    (U2) 8000U,    /* Diagnosis data's byte#6 bit4 : 80 degrees[Celsius]                     */
    (U2) 7000U,    /* Diagnosis data's byte#6 bit5 : 70 degrees[Celsius]                     */
    (U2) 6000U,    /* Diagnosis data's byte#6 bit6 : 60 degrees[Celsius]                     */
    (U2) 5000U     /* Diagnosis data's byte#6 bit7 : 50 degrees[Celsius]                     */
};

static const U2                u2_sp_GAG_TMPSEG_CSTD_CNV_LIMIT[GAGDST_TEMPSEG_NUM_RNG_CSTD << 1] = {
    (U2)    0U,   /* 00 : Min    0seg        */
    (U2) 4201U,   /* 01 : Min    1seg        */
    (U2) 5201U,   /* 02 : Min    2seg        */
    (U2) 6201U,   /* 03 : Min    3seg        */
    (U2) 7201U,   /* 04 : Min    4seg        */
    (U2)10701U,   /* 05 : Min    5seg        */
    (U2)11301U,   /* 06 : Min    6seg        */
    (U2)11401U,   /* 07 : Min    7seg        */
    (U2)11501U,   /* 08 : Min    8seg        */

    (U2) 4499U,   /* 00 : Max    0seg        */
    (U2) 5499U,   /* 01 : Max    1seg        */
    (U2) 6499U,   /* 02 : Max    2seg        */
    (U2) 7499U,   /* 03 : Max    3seg        */
    (U2)10999U,   /* 04 : Max    4seg        */
    (U2)11499U,   /* 05 : Max    5seg        */
    (U2)11699U,   /* 06 : Max    6seg        */
    (U2)11999U,   /* 07 : Max    7seg        */
    (U2)U2_MAX    /* 08 : Max    8seg        */
};
static const ST_RNG_CMPR_U2    st_s_GAG_TMPSEG_CSTD_CNV_LIMIT_CMPR = {
    &u2_sp_GAG_TMPSEG_CSTD_CNV_LIMIT[0],    /* u2p_LIMIT   */
    (U2)0U,                                 /* u2_idx_init */
    (U2)GAGDST_TEMPSEG_NUM_RNG_CSTD         /* u2_num_rng  */
};
static const U2                u2_sp_GAG_TMPSEG_CSTD_HYB_LIMIT[GAGDST_TEMPSEG_NUM_RNG_CSTD << 1] = {
    (U2)    0U,   /* 00 : Min    0seg        */
    (U2) 3001U,   /* 01 : Min    1seg        */
    (U2) 3801U,   /* 02 : Min    2seg        */
    (U2) 4701U,   /* 03 : Min    3seg        */
    (U2) 5501U,   /* 04 : Min    4seg        */
    (U2)10701U,   /* 05 : Min    5seg        */
    (U2)11301U,   /* 06 : Min    6seg        */
    (U2)11401U,   /* 07 : Min    7seg        */
    (U2)11501U,   /* 08 : Min    8seg        */

    (U2) 3499U,   /* 00 : Max    0seg        */
    (U2) 4299U,   /* 01 : Max    1seg        */
    (U2) 5199U,   /* 02 : Max    2seg        */
    (U2) 5999U,   /* 03 : Max    3seg        */
    (U2)10999U,   /* 04 : Max    4seg        */
    (U2)11499U,   /* 05 : Max    5seg        */
    (U2)11699U,   /* 06 : Max    6seg        */
    (U2)11999U,   /* 07 : Max    7seg        */
    (U2)U2_MAX    /* 08 : Max    8seg        */
};
static const ST_RNG_CMPR_U2    st_s_GAG_TMPSEG_CSTD_HYB_LIMIT_CMPR = {
    &u2_sp_GAG_TMPSEG_CSTD_HYB_LIMIT[0],    /* u2p_LIMIT   */
    (U2)0U,                                 /* u2_idx_init */
    (U2)GAGDST_TEMPSEG_NUM_RNG_CSTD         /* u2_num_rng  */
};
static const U2                u2_sp_GAG_TMPSEG_CSTD_MDE_LIMIT[GAGDST_TEMPSEG_NUM_RNG_CSTD << 1] = {
    (U2)    0U,   /* 00 : Min    0seg        */
    (U2) 6501U,   /* 01 : Min    1seg        */
    (U2) 7601U,   /* 02 : Min    2seg        */
    (U2) 8501U,   /* 03 : Min    3seg        */
    (U2)10701U,   /* 04 : Min    4seg        */
    (U2)11001U,   /* 05 : Min    5seg        */
    (U2)11301U,   /* 06 : Min    6seg        */
    (U2)11401U,   /* 07 : Min    7seg        */
    (U2)11501U,   /* 08 : Min    8seg        */

    (U2) 6999U,   /* 00 : Max    0seg        */
    (U2) 8099U,   /* 01 : Max    1seg        */
    (U2) 9199U,   /* 02 : Max    2seg        */
    (U2)10999U,   /* 03 : Max    3seg        */
    (U2)11299U,   /* 04 : Max    4seg        */
    (U2)11499U,   /* 05 : Max    5seg        */
    (U2)11699U,   /* 06 : Max    6seg        */
    (U2)11999U,   /* 07 : Max    7seg        */
    (U2)U2_MAX    /* 08 : Max    8seg        */
};
static const ST_RNG_CMPR_U2    st_s_GAG_TMPSEG_CSTD_MDE_LIMIT_CMPR = {
    &u2_sp_GAG_TMPSEG_CSTD_MDE_LIMIT[0],    /* u2p_LIMIT   */
    (U2)0U,                                 /* u2_idx_init */
    (U2)GAGDST_TEMPSEG_NUM_RNG_CSTD         /* u2_num_rng  */
};

const ST_GAGDST_TEMPCFG st_gp_GAGDST_TEMPSEGCFG[GAGDST_TEMPSEG_NUM_CFG] = {
    {   
        /*  GAGDST_TEMPSEG_CSTD_CNV    (0) */
        &st_s_GAG_TMPSEG_CSTD_CNV_LIMIT_CMPR,
        (U1)GAGDST_TEMPSEG_TYPE_CSTD_SEG8
    },
    {   
        /*  GAGDST_TEMPSEG_CSTD_HYB    (1) */
        &st_s_GAG_TMPSEG_CSTD_HYB_LIMIT_CMPR,
        (U1)GAGDST_TEMPSEG_TYPE_CSTD_SEG8
    },
    {
        /*  GAGDST_TEMPSEG_CSTD_MDE    (2) */
        &st_s_GAG_TMPSEG_CSTD_MDE_LIMIT_CMPR,
        (U1)GAGDST_TEMPSEG_TYPE_CSTD_SEG8
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_GagdstTempRng(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_GagdstTempRng(void)
{
    static const U1 u1_sp2_GAGDST_TEMPSEG_PWRTRN[GAGDST_TEMPSEG_NUM_PTSYS][GAGDST_TEMPSEG_NUM_DEST] = {
        { (U1)GAGDST_TEMPSEG_NODISP   , (U1)GAGDST_TEMPSEG_NODISP   },      /*  VDF_PTS_RX_00_UNK        ( 0) */
        { (U1)GAGDST_TEMPSEG_CSTD_CNV , (U1)GAGDST_TEMPSEG_CSTD_MDE },      /*  VDF_PTS_RX_01_GAS        ( 1) */
        { (U1)GAGDST_TEMPSEG_CSTD_CNV , (U1)GAGDST_TEMPSEG_CSTD_MDE },      /*  VDF_PTS_RX_02_GAS_ISS    ( 2) */
        { (U1)GAGDST_TEMPSEG_CSTD_HYB , (U1)GAGDST_TEMPSEG_CSTD_MDE },      /*  VDF_PTS_RX_03_HYB        ( 3) */
        { (U1)GAGDST_TEMPSEG_CSTD_HYB , (U1)GAGDST_TEMPSEG_CSTD_MDE },      /*  VDF_PTS_RX_04_HYB_PLU    ( 4) */
        { (U1)GAGDST_TEMPSEG_NODISP   , (U1)GAGDST_TEMPSEG_NODISP   },      /*  VDF_PTS_RX_05_ELE_BAT    ( 5) */
        { (U1)GAGDST_TEMPSEG_CSTD_HYB , (U1)GAGDST_TEMPSEG_CSTD_MDE },      /*  VDF_PTS_RX_06_HYB_MOT    ( 6) */
        { (U1)GAGDST_TEMPSEG_NODISP   , (U1)GAGDST_TEMPSEG_NODISP   },      /*  VDF_PTS_RX_07_ELE_HYD    ( 7) */
        { (U1)GAGDST_TEMPSEG_CSTD_HYB , (U1)GAGDST_TEMPSEG_CSTD_MDE },      /*  VDF_PTS_RX_08_48V        ( 8) */
        { (U1)GAGDST_TEMPSEG_NODISP   , (U1)GAGDST_TEMPSEG_NODISP   },      /*  VDF_PTS_RX_09_UNK        ( 9) */
        { (U1)GAGDST_TEMPSEG_NODISP   , (U1)GAGDST_TEMPSEG_NODISP   },      /*  VDF_PTS_RX_0A_UNK        (10) */
        { (U1)GAGDST_TEMPSEG_NODISP   , (U1)GAGDST_TEMPSEG_NODISP   },      /*  VDF_PTS_RX_0B_UNK        (11) */
        { (U1)GAGDST_TEMPSEG_NODISP   , (U1)GAGDST_TEMPSEG_NODISP   },      /*  VDF_PTS_RX_0C_UNK        (12) */
        { (U1)GAGDST_TEMPSEG_NODISP   , (U1)GAGDST_TEMPSEG_NODISP   },      /*  VDF_PTS_RX_0D_UNK        (13) */
        { (U1)GAGDST_TEMPSEG_NODISP   , (U1)GAGDST_TEMPSEG_NODISP   },      /*  VDF_PTS_RX_0E_UNK        (14) */
        { (U1)GAGDST_TEMPSEG_NODISP   , (U1)GAGDST_TEMPSEG_NODISP   }       /*  VDF_PTS_RX_0F_UNK        (15) */
    };

    U1  u1_t_tmpgag;
    U1  u1_t_pwrtrn;
    U1  u1_t_idx;

    u1_t_pwrtrn = u1_g_VardefPtsRx();
    u1_t_tmpgag = u1_g_VardefTempChrByPid();
    if ((u1_t_pwrtrn < (U1)GAGDST_TEMPSEG_NUM_PTSYS) &&
        (u1_t_tmpgag < (U1)GAGDST_TEMPSEG_NUM_DEST)) {
        u1_t_idx = u1_sp2_GAGDST_TEMPSEG_PWRTRN[u1_t_pwrtrn][u1_t_tmpgag];
    }
    else {
        u1_t_idx = (U1)GAGDST_TEMPSEG_NODISP;
    }
    return(u1_t_idx);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  2.0.0    06/03/2021  TA       New.                                                                                               */
/*  2.0.1    10/18/2021  TK       gagdst_tempseg.c v2.0.0 -> v2.0.1.                                                                 */
/*  2.0.2    10/25/2021  TK       gagdst_tempseg.c v2.0.1 -> v2.0.2.                                                                 */
/*  2.1.0    11/15/2021  TA(M)    gagdst_tempseg.c v2.0.2 -> v2.1.0.                                                                 */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/* 22-24FGM  11/15/2021  MK       Apply 22-24FGM 1A configlation.                                                                    */
/*  19PFv3-1 02/01/2024  KH       Apply 19PFv3 configuration                                                                         */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TK   = Takanori Kuno, DensoTechno                                                                                              */
/*  * MK   = Mitsuhiro Kato, DensoTechno                                                                                             */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/
