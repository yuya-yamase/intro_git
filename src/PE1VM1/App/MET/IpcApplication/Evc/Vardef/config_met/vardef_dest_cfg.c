/* 3.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vardef / Destination                                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VARDEF_DEST_CFG_C_MAJOR                 (3)
#define VARDEF_DEST_CFG_C_MINOR                 (0)
#define VARDEF_DEST_CFG_C_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vardef_dest_cfg_private.h"

#include "locale.h"

#include "oxcan.h"

#include "rim_ctl.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VARDEF_DEST_CFG_C_MAJOR != VARDEF_DEST_CFG_H_MAJOR) || \
     (VARDEF_DEST_CFG_C_MINOR != VARDEF_DEST_CFG_H_MINOR) || \
     (VARDEF_DEST_CFG_C_PATCH != VARDEF_DEST_CFG_H_PATCH))
#error "vardef_dest_cfg.c and vardef_dest_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((VARDEF_DEST_CFG_C_MAJOR != VARDEF_DEST_DBF_H_MAJOR) || \
     (VARDEF_DEST_CFG_C_MINOR != VARDEF_DEST_DBF_H_MINOR) || \
     (VARDEF_DEST_CFG_C_PATCH != VARDEF_DEST_DBF_H_PATCH))
#error "vardef_dest_cfg.c and vardef_dest_dbf.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDF_DEST_NUM_LAW_DESTID         (16U)
#define VDF_DEST_SPEC_DESTID0001        (0U)
#define VDF_DEST_SPEC_DESTID0002        (1U)
#define VDF_DEST_SPEC_DESTID0014        (2U)
#define VDF_DEST_SPEC_DESTID0017        (3U)
#define VDF_DEST_SPEC_DESTID0018        (4U)
#define VDF_DEST_SPEC_DESTID0019        (5U)
#define VDF_DEST_SPEC_DESTID0020        (6U)
#define VDF_DEST_SPEC_DESTID0021        (7U)
#define VDF_DEST_SPEC_DESTID0022        (8U)
#define VDF_DEST_SPEC_DESTID0023        (9U)
#define VDF_DEST_SPEC_DESTID0024        (10U)
#define VDF_DEST_SPEC_DESTID0025        (11U)
#define VDF_DEST_SPEC_DESTID0026        (12U)
#define VDF_DEST_SPEC_DESTID0027        (13U)
#define VDF_DEST_SPEC_DESTID0028        (14U)
#define VDF_DEST_SPEC_DESTID0029        (15U)

#define VDF_DEST_SPEC_LAW_DESTID        (4U)

#define VDF_NUM_UNIT_DEF_CFG            (4U)
#define VDF_DEST_UNIT_DEF_MPGIMP        (0U)
#define VDF_DEST_UNIT_DEF_MPGUSA        (1U)
#define VDF_DEST_UNIT_DEF_KMPH          (2U)
#define VDF_DEST_UNIT_DEF_LP100KM       (3U)

#define VDF_NUM_VEH_SPD_UNIT            (4U)
#define VDF_VEH_SPD_UNIT_KMH            (0U)
#define VDF_VEH_SPD_UNIT_MPHKMH         (1U)
#define VDF_VEH_SPD_UNIT_KMHMPH         (2U)
#define VDF_VEH_SPD_UNIT_MPH            (3U)

#define VDF_NUM_VEH_SPD_UNIT_MSSW       (2U)
#define VDF_VEH_SPD_UNIT_MSSW_WITHOUT   (0U)
#define VDF_VEH_SPD_UNIT_MSSW_WITH      (1U)

#define VDF_NUM_VEH_SPD_UNIT_DSP        (3U)
#define VDF_VEH_SPD_UNIT_DSP_WITHOUT    (0U)
#define VDF_VEH_SPD_UNIT_DSP_ALWAYS     (1U)
#define VDF_VEH_SPD_UNIT_DSP_NONDEF     (2U)

#define VDF_DST_NUM_C_CODE              (21U)
#define VDF_DST_LAW_NUM_C_CODE          (21U)

#define VDF_DST_SPEC_NUM_C_CODE_REG     (10U)
#define VDF_DST_SPEC_C_CODE_ONE         (0U)
#define VDF_DST_SPEC_C_CODE_TWO         (1U)
#define VDF_DST_SPEC_C_CODE_THREE       (2U)
#define VDF_DST_SPEC_C_CODE_FOUR        (3U)
#define VDF_DST_SPEC_C_CODE_FIVE        (4U)
#define VDF_DST_SPEC_C_CODE_SIX         (5U)
#define VDF_DST_SPEC_C_CODE_SEVEN       (6U)
#define VDF_DST_SPEC_C_CODE_EIGHT       (7U)
#define VDF_DST_SPEC_C_CODE_NINE        (8U)
#define VDF_DST_SPEC_C_CODE_TEN         (9U)

#define VDF_DST_LAW_NUM_C_CODE_REG      (23U)
#define VDF_DST_LAW_C_CODE_CAN          (0U)
#define VDF_DST_LAW_C_CODE_KOR          (1U)
#define VDF_DST_LAW_C_CODE_GBR          (2U)
#define VDF_DST_LAW_C_CODE_MEX          (3U)
#define VDF_DST_LAW_C_CODE_ZAF          (4U)
#define VDF_DST_LAW_C_CODE_IND          (5U)
#define VDF_DST_LAW_C_CODE_CHN          (6U)
#define VDF_DST_LAW_C_CODE_BHR          (7U)
#define VDF_DST_LAW_C_CODE_QAT          (8U)
#define VDF_DST_LAW_C_CODE_KWT          (9U)
#define VDF_DST_LAW_C_CODE_UAE          (10U)
#define VDF_DST_LAW_C_CODE_SAU          (11U)
#define VDF_DST_LAW_C_CODE_OMN          (12U)
#define VDF_DST_LAW_C_CODE_HKG          (13U)
#define VDF_DST_LAW_C_CODE_MAC          (14U)
#define VDF_DST_LAW_C_CODE_AUS          (15U)
#define VDF_DST_LAW_C_CODE_PNG          (16U)
#define VDF_DST_LAW_C_CODE_NZL          (17U)
#define VDF_DST_LAW_C_CODE_SLB          (18U)
#define VDF_DST_LAW_C_CODE_TWN          (19U)
#define VDF_DST_LAW_C_CODE_SGP          (20U)
#define VDF_DST_LAW_C_CODE_KOR_FMVSS    (21U)
#define VDF_DST_LAW_C_CODE_MEX_FMVSS    (22U)

#define VDF_DST_C_CODE_CAN              (0U)
#define VDF_DST_C_CODE_KOR              (1U)
#define VDF_DST_C_CODE_GBR              (2U)
#define VDF_DST_C_CODE_MEX              (3U)
#define VDF_DST_C_CODE_ZAF              (4U)
#define VDF_DST_C_CODE_IND              (5U)
#define VDF_DST_C_CODE_CHN              (6U)
#define VDF_DST_C_CODE_BHR              (7U)
#define VDF_DST_C_CODE_QAT              (8U)
#define VDF_DST_C_CODE_KWT              (9U)
#define VDF_DST_C_CODE_UAE              (10U)
#define VDF_DST_C_CODE_SAU              (11U)
#define VDF_DST_C_CODE_OMN              (12U)
#define VDF_DST_C_CODE_HKG              (13U)
#define VDF_DST_C_CODE_MAC              (14U)
#define VDF_DST_C_CODE_AUS              (15U)
#define VDF_DST_C_CODE_PNG              (16U)
#define VDF_DST_C_CODE_NZL              (17U)
#define VDF_DST_C_CODE_SLB              (18U)
#define VDF_DST_C_CODE_TWN              (19U)
#define VDF_DST_C_CODE_SGP              (20U)

#define VDF_DST_LAW_NUM_DEST_BDB        (12U)

#define VDF_DST_LAW_NUM_DEST_BDB_REG    (13U)
#define VDF_DST_LAW_DEST_BDB_A_USA      (0U)
#define VDF_DST_LAW_DEST_BDB_B_TUR      (1U)
#define VDF_DST_LAW_DEST_BDB_C_CHN      (2U)
#define VDF_DST_LAW_DEST_BDB_N_ZAF      (3U)
#define VDF_DST_LAW_DEST_BDB_Q_AUS      (4U)
#define VDF_DST_LAW_DEST_BDB_V_MDE      (5U)
#define VDF_DST_LAW_DEST_BDB_W_EU       (6U)
#define VDF_DST_LAW_DEST_BDB_X_RUS      (7U)
#define VDF_DST_LAW_DEST_BDB_Z_NZL      (8U)
#define VDF_DST_LAW_DEST_BDB_B_JPN      (9U)
#define VDF_DST_LAW_DEST_BDB_B_GNR_L    (10U)
#define VDF_DST_LAW_DEST_BDB_B_GNR_R    (11U)
#define VDF_DST_LAW_DEST_BDB_B_GNR_FMVSS (12U)

#define VDF_DST_NUM_DEST_BDB            (12U)
#define VDF_DST_DEST_BDB_A_USA          (0U)
#define VDF_DST_DEST_BDB_B_TUR          (1U)
#define VDF_DST_DEST_BDB_C_CHN          (2U)
#define VDF_DST_DEST_BDB_N_ZAF          (3U)
#define VDF_DST_DEST_BDB_Q_AUS          (4U)
#define VDF_DST_DEST_BDB_V_MDE          (5U)
#define VDF_DST_DEST_BDB_W_EU           (6U)
#define VDF_DST_DEST_BDB_X_RUS          (7U)
#define VDF_DST_DEST_BDB_Z_NZL          (8U)
#define VDF_DST_DEST_BDB_B_JPN          (9U)
#define VDF_DST_DEST_BDB_B_GNR_L        (10U)
#define VDF_DST_DEST_BDB_B_GNR_R        (11U)

#define VDF_NUM_PTSYS                       (16U)

/* Sub Vehicle speed true value table configuration index */
#define VDF_DET_SUB_DIG_SPD_IDX                 (8U)
/* Sub Vehicle Speed Offset Used During the Combination of Determination Conditions */
#define VDF_DET_SUB_DIG_SPD_OFFSET_UNIT         (4U)
#define VDF_DET_SUB_DIG_SPD_OFFSET_UNTCHG       (2U)
#define VDF_DET_SUB_DIG_SPD_OFFSET_VIEW         (0U)

/* Optional unit groups */
#define VDF_DET_UNIT_SLCT_NUM                   (4U)

/* North America region seat belt buzzer mode index */
#define VDF_SEATBLT_DEST_USA_IDX                (0U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U2          u1_t_sub_spd_cfg; /* Subspeed Configuration Table (Result after Bit Operations) */
    U1          u1_t_sub_dig_spd; /* Final Output Result */
}ST_VDF_DST_SUB_VEHSPD;

typedef struct{
    U1          u1_t_law_if_name; /* Regulation Project Inquiry Interface Name */
    U1          u1_t_law_destid;  /* Regulation Project DestID */
}ST_VDF_DST_LAW_IFID_IDX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2        u2_g_VDF_DST_C_CODE_RIM_U2      = (U2)RIMID_U2_VDF_C_CODE;
const U2        u2_g_VDF_DST_DEST_BDB_RIM_U1    = (U2)RIMID_U1_VDF_DEST_BDB;
const U2        u2_g_VDF_DST_STRG_WHL_RIM_U1    = (U2)RIMID_U1_VDF_STRG_WHL;
const U2        u2_g_VDF_DST_IDX_RIM_U1         = (U2)RIMID_U1_VDF_DST_IDX;
/* Laws and Regulations Project Index Storage RIMID */
const U2        u2_g_VDF_DST_LAW_IDX_RIM_U1     = (U2)RIMID_U1_VDF_DST_LAW_IDX;

const U1        u1_g_VDF_DST_RXEV_CNT_INIT      = (U1)OXCAN_RXD_EVC_UNK;

const U1        u1_g_VDF_DST_LAW_SPEC_IDX_DEF   = (U1)U1_MAX;
const U1        u1_g_VDF_DST_C_CODE_IDX_DEF     = (U1)U1_MAX;
const U1        u1_g_VDF_DST_LAW_C_CODE_IDX_DEF = (U1)U1_MAX;
const U1        u1_g_VDF_DST_DEST_BDB_IDX_DEF   = (U1)VDF_DST_DEST_BDB_B_GNR_L;
const U1        u1_g_VDF_DST_IDX_DEF            = (U1)U1_MAX;
const U1        u1_g_VDF_DST_LAW_IDX_DEF        = (U1)U1_MAX;

const U1        u1_g_VDF_DST_HDSIDE_DEF         = (U1)VDF_HDSIDE_LHD;

const U1        u1_g_VDF_DST_LAW_NUM_C_CODE     = (U1)VDF_DST_LAW_NUM_C_CODE;
const U1        u1_g_VDF_DST_NUM_C_CODE         = (U1)VDF_DST_NUM_C_CODE;
const U1        u1_g_VDF_DST_LAW_NUM_DEST_BDB   = (U1)VDF_DST_LAW_NUM_DEST_BDB;
const U1        u1_g_VDF_DST_NUM_DEST_BDB       = (U1)VDF_DST_NUM_DEST_BDB;

const U1        u1_g_VDF_DST_LAW_NUM_C_CODE_REG = (U1)VDF_DST_LAW_NUM_C_CODE_REG;
const U1        u1_g_VDF_DST_LAW_C_CODE_KOR     = (U1)VDF_DST_LAW_C_CODE_KOR;
const U1        u1_g_VDF_DST_LAW_C_CODE_MEX     = (U1)VDF_DST_LAW_C_CODE_MEX;
const U1        u1_g_VDF_DST_LAW_KOR_FMVSS      = (U1)VDF_DST_LAW_C_CODE_KOR_FMVSS;
const U1        u1_g_VDF_DST_LAW_MEX_FMVSS      = (U1)VDF_DST_LAW_C_CODE_MEX_FMVSS;

const U1        u1_g_VDF_DST_SPEC_NUM_C_CODE    = (U1)VDF_DST_SPEC_NUM_C_CODE_REG;

const U1        u1_g_VDF_DST_LAW_NUM_DEST_BDB_REG     = (U1)VDF_DST_LAW_NUM_DEST_BDB_REG;
const U1        u1_g_VDF_DST_LAW_DEST_BDB_B_GNR_L     = (U1)VDF_DST_LAW_DEST_BDB_B_GNR_L;
const U1        u1_g_VDF_DST_LAW_DEST_BDB_B_GNR_R     = (U1)VDF_DST_LAW_DEST_BDB_B_GNR_R;
const U1        u1_g_VDF_DST_LAW_DEST_BDB_B_GNR_FMVSS = (U1)VDF_DST_LAW_DEST_BDB_B_GNR_FMVSS;

const ST_VDF_DST_SPEC_C_CODE    st_gp_VDF_DST_SPEC_C_CODE[VDF_DST_SPEC_NUM_C_CODE_REG] = {
/*  u2_t_c_code                               u1_t_c_code_idx                        */
    { &u2_CALIB_MCUID0923_CNTY_CODE_1     ,   &u1_CALIB_MCUID1103_JUDG_RES_1    },
    { &u2_CALIB_MCUID0924_CNTY_CODE_2     ,   &u1_CALIB_MCUID1104_JUDG_RES_2    },
    { &u2_CALIB_MCUID0925_CNTY_CODE_3     ,   &u1_CALIB_MCUID1105_JUDG_RES_3    },
    { &u2_CALIB_MCUID0926_CNTY_CODE_4     ,   &u1_CALIB_MCUID1106_JUDG_RES_4    },
    { &u2_CALIB_MCUID0927_CNTY_CODE_5     ,   &u1_CALIB_MCUID1107_JUDG_RES_5    },
    { &u2_CALIB_MCUID0928_CNTY_CODE_6     ,   &u1_CALIB_MCUID1108_JUDG_RES_6    },
    { &u2_CALIB_MCUID0929_CNTY_CODE_7     ,   &u1_CALIB_MCUID1109_JUDG_RES_7    },
    { &u2_CALIB_MCUID0930_CNTY_CODE_8     ,   &u1_CALIB_MCUID1110_JUDG_RES_8    },
    { &u2_CALIB_MCUID0931_CNTY_CODE_9     ,   &u1_CALIB_MCUID1111_JUDG_RES_9    },
    { &u2_CALIB_MCUID0932_CNTY_CODE_10    ,   &u1_CALIB_MCUID1112_JUDG_RES_10   }
};

const ST_VDF_DST_LAW_C_CODE    st_gp_VDF_DST_LAW_C_CODE[VDF_DST_LAW_NUM_C_CODE] = {
    /*  u2_t_c_code    u1_t_c_code_idx                                                      */
    { (U2)0x0102U     , (U1)VDF_DST_LAW_C_CODE_CAN },           /* Canada                   */
    { (U2)0x0719U     , (U1)VDF_DST_LAW_C_CODE_KOR },           /* Rep of Korea             */
    { (U2)0x0408U     , (U1)VDF_DST_LAW_C_CODE_GBR },           /* United Kingdom           */
    { (U2)0x0209U     , (U1)VDF_DST_LAW_C_CODE_MEX },           /* Mexico                   */
    { (U2)0x0537U     , (U1)VDF_DST_LAW_C_CODE_ZAF },           /* South Africa             */
    { (U2)0x0709U     , (U1)VDF_DST_LAW_C_CODE_IND },           /* India                    */
    { (U2)0x0707U     , (U1)VDF_DST_LAW_C_CODE_CHN },           /* China                    */
    { (U2)0x0611U     , (U1)VDF_DST_LAW_C_CODE_BHR },           /* Bahrain                  */
    { (U2)0x0612U     , (U1)VDF_DST_LAW_C_CODE_QAT },           /* Qatar                    */
    { (U2)0x0613U     , (U1)VDF_DST_LAW_C_CODE_KWT },           /* Kuwait                   */
    { (U2)0x0615U     , (U1)VDF_DST_LAW_C_CODE_UAE },           /* UAE                      */
    { (U2)0x0618U     , (U1)VDF_DST_LAW_C_CODE_SAU },           /* Saudi Arabia             */
    { (U2)0x0620U     , (U1)VDF_DST_LAW_C_CODE_OMN },           /* Oman                     */
    { (U2)0x0708U     , (U1)VDF_DST_LAW_C_CODE_HKG },           /* Hong Kong                */
    { (U2)0x0726U     , (U1)VDF_DST_LAW_C_CODE_MAC },           /* Macao                    */
    { (U2)0x0801U     , (U1)VDF_DST_LAW_C_CODE_AUS },           /* Australia                */
    { (U2)0x0808U     , (U1)VDF_DST_LAW_C_CODE_PNG },           /* Papua New Guinea         */
    { (U2)0x0809U     , (U1)VDF_DST_LAW_C_CODE_NZL },           /* New Zealand              */
    { (U2)0x0813U     , (U1)VDF_DST_LAW_C_CODE_SLB },           /* Solomon Islands          */
    { (U2)0x0721U     , (U1)VDF_DST_LAW_C_CODE_TWN },           /* Taiwan                   */
    { (U2)0x0718U     , (U1)VDF_DST_LAW_C_CODE_SGP }            /* Singapore                */
};

const U2    u2_gp_VDF_DST_C_CODE[VDF_DST_NUM_C_CODE] = {
    (U2)0x0102U,             /* Canada                   */
    (U2)0x0719U,             /* Rep of Korea             */
    (U2)0x0408U,             /* United Kingdom           */
    (U2)0x0209U,             /* Mexico                   */
    (U2)0x0537U,             /* South Africa             */
    (U2)0x0709U,             /* India                    */
    (U2)0x0707U,             /* China                    */
    (U2)0x0611U,             /* Bahrain                  */
    (U2)0x0612U,             /* Qatar                    */
    (U2)0x0613U,             /* Kuwait                   */
    (U2)0x0615U,             /* UAE                      */
    (U2)0x0618U,             /* Saudi Arabia             */
    (U2)0x0620U,             /* Oman                     */
    (U2)0x0708U,             /* Hong Kong                */
    (U2)0x0726U,             /* Macao                    */
    (U2)0x0801U,             /* Australia                */
    (U2)0x0808U,             /* Papua New Guinea         */
    (U2)0x0809U,             /* New Zealand              */
    (U2)0x0813U,             /* Solomon Islands          */
    (U2)0x0721U,             /* Taiwan                   */
    (U2)0x0718U              /* Singapore                */
};

const ST_VDF_DST_LAW_DEST_BDB_JDGIDX st_gp_VDF_DST_LAW_DEST_BDB_JDGIDX[VDF_DST_LAW_NUM_DEST_BDB] = {
/*  u2_dest_bdb_val   u2_dest_bdb_mask   u1_t_dest_bdb_idx           */
    {(U2)0x0041U     ,(U2)0x00ffU       ,(U1)VDF_DST_LAW_DEST_BDB_A_USA   },    /* A_USA   */
    {(U2)0x0042U     ,(U2)0x00ffU       ,(U1)VDF_DST_LAW_DEST_BDB_B_TUR   },    /* B_TUR   */
    {(U2)0x0043U     ,(U2)0x00ffU       ,(U1)VDF_DST_LAW_DEST_BDB_C_CHN   },    /* C_CHN   */
    {(U2)0x004EU     ,(U2)0x00ffU       ,(U1)VDF_DST_LAW_DEST_BDB_N_ZAF   },    /* N_ZAF   */
    {(U2)0x0051U     ,(U2)0x00ffU       ,(U1)VDF_DST_LAW_DEST_BDB_Q_AUS   },    /* Q_AUS   */
    {(U2)0x0056U     ,(U2)0x00ffU       ,(U1)VDF_DST_LAW_DEST_BDB_V_MDE   },    /* V_MDE   */
    {(U2)0x0057U     ,(U2)0x00ffU       ,(U1)VDF_DST_LAW_DEST_BDB_W_EU    },    /* W_EU    */
    {(U2)0x0058U     ,(U2)0x00ffU       ,(U1)VDF_DST_LAW_DEST_BDB_X_RUS   },    /* X_RUS   */
    {(U2)0x005AU     ,(U2)0x00ffU       ,(U1)VDF_DST_LAW_DEST_BDB_Z_NZL   },    /* Z_NZL   */
    {(U2)0x0000U     ,(U2)0x03ffU       ,(U1)VDF_DST_LAW_DEST_BDB_B_JPN   },    /* B_JPN   */
    {(U2)0x0100U     ,(U2)0x03ffU       ,(U1)VDF_DST_LAW_DEST_BDB_B_GNR_L },    /* B_GNR_L */
    {(U2)0x0200U     ,(U2)0x03ffU       ,(U1)VDF_DST_LAW_DEST_BDB_B_GNR_R }     /* B_GNR_R */
};

const ST_VDF_DST_DEST_BDB_JDGIDX st_gp_VDF_DST_DEST_BDB_JDGIDX[VDF_DST_NUM_DEST_BDB] = {
/*  u2_dest_bdb_val  u2_dest_bdb_mask             */
    {(U2)0x0041U    ,(U2)0x00ffU },    /* A_USA   */
    {(U2)0x0042U    ,(U2)0x00ffU },    /* B_TUR   */
    {(U2)0x0043U    ,(U2)0x00ffU },    /* C_CHN   */
    {(U2)0x004EU    ,(U2)0x00ffU },    /* N_ZAF   */
    {(U2)0x0051U    ,(U2)0x00ffU },    /* Q_AUS   */
    {(U2)0x0056U    ,(U2)0x00ffU },    /* V_MDE   */
    {(U2)0x0057U    ,(U2)0x00ffU },    /* W_EU    */
    {(U2)0x0058U    ,(U2)0x00ffU },    /* X_RUS   */
    {(U2)0x005AU    ,(U2)0x00ffU },    /* Z_NZL   */
    {(U2)0x0000U    ,(U2)0x03ffU },    /* B_JPN   */
    {(U2)0x0100U    ,(U2)0x03ffU },    /* B_GNR_L */
    {(U2)0x0200U    ,(U2)0x03ffU }     /* B_GNR_R */
};

static const ST_VDF_DST_LAW_IFID_IDX  st_sp_VDF_DEST_LAW_IFID_IDX[VDF_DEST_LAW_DBF_NBYTE] = {
    /* LAW_IF_NAME                         DESTID                       */
    {(U1)VDF_DEST_LAW_DBF_DEFUNIT_SPD    , (U1)VDF_DEST_SPEC_DESTID0001 },
    {(U1)VDF_DEST_LAW_DBF_DEFUNIT_DST    , (U1)VDF_DEST_SPEC_DESTID0001 },
    {(U1)VDF_DEST_LAW_DBF_DEFUNIT_FUECO  , (U1)VDF_DEST_SPEC_DESTID0001 },
    {(U1)VDF_DEST_LAW_DBF_DEFUNIT_ELECO  , (U1)VDF_DEST_SPEC_DESTID0001 },
    {(U1)VDF_DEST_LAW_DBF_UNITSLCT_FUECO , (U1)VDF_DEST_SPEC_DESTID0001 },
    {(U1)VDF_DEST_LAW_DBF_UNITSLCT_DEST  , (U1)VDF_DEST_SPEC_DESTID0002 },
    {(U1)VDF_DEST_LAW_DBF_BZ_SBW_SUP     , (U1)VDF_DEST_SPEC_DESTID0014 },
    {(U1)VDF_DEST_LAW_DBF_MDLEST_WRN     , (U1)VDF_DEST_SPEC_DESTID0017 },
    {(U1)VDF_DEST_LAW_DBF_INDIASPDBZR    , (U1)VDF_DEST_SPEC_DESTID0018 },
    {(U1)VDF_DEST_LAW_DBF_BZ_REV_DEST    , (U1)VDF_DEST_SPEC_DESTID0019 },
    {(U1)VDF_DEST_LAW_DBF_SEATBLT_CONST  , (U1)VDF_DEST_SPEC_DESTID0020 },
    {(U1)VDF_DEST_LAW_DBF_SUBDIGSPD      , (U1)VDF_DEST_SPEC_DESTID0021 },
    {(U1)VDF_DEST_LAW_DBF_SPDTLRNC       , (U1)VDF_DEST_SPEC_DESTID0024 },
    {(U1)VDF_DEST_LAW_DBF_CHAINAREQ      , (U1)VDF_DEST_SPEC_DESTID0025 },
    {(U1)VDF_DEST_LAW_DBF_TTBRAKE        , (U1)VDF_DEST_SPEC_DESTID0026 },
    {(U1)VDF_DEST_LAW_DBF_TTABS          , (U1)VDF_DEST_SPEC_DESTID0027 },
    {(U1)VDF_DEST_LAW_DBF_TTEPBPKB       , (U1)VDF_DEST_SPEC_DESTID0028 },
    {(U1)VDF_DEST_LAW_DBF_TTTAILHEAD     , (U1)VDF_DEST_SPEC_DESTID0029 }
};

static volatile const U1 *const    u1p_sp2_VDF_DST_SPEC_CCODESUP[VDF_DST_SPEC_NUM_C_CODE_REG][VDF_DEST_NUM_LAW_DESTID] = {
     /* DESTID0001                       DESTID0002                       DESTID0014                       DESTID0017                       DESTID0018                       DESTID0019                       DESTID0020                        DESTID0021                       DESTID0022                         DESTID0023                          DESTID0024                      DESTID0025                         DESTID0026                         DESTID0027                         DESTID0028                        DESTID0029                      */
    {&u1_CALIB_MCUID0933_FUECO_UNIT_1  , &u1_CALIB_MCUID0943_UNIT_SW_1  , &u1_CALIB_MCUID0953_BUZ_REV_1  , &u1_CALIB_MCUID0963_BUZ_GSO_1  , &u1_CALIB_MCUID0973_BUZ_AIS_1  , &u1_CALIB_MCUID0983_BUZ_NOT_1  , &u1_CALIB_MCUID1093_BUZ_BELT_1  , &u1_CALIB_MCUID0993_SP_UNIT_1  , &u1_CALIB_MCUID1003_SPUN_MSSW_1  , &u1_CALIB_MCUID1013_SUB_SP_DIS_1  , &u1_CALIB_MCUID1023_SP_TOL_1  , &u1_CALIB_MCUID1033_CH_REG_GB_1  , &u1_CALIB_MCUID1043_FMV_BRATT_1  , &u1_CALIB_MCUID1053_FMV_ABSTT_1  , &u1_CALIB_MCUID1063_FMV_EPTT_1  , &u1_CALIB_MCUID1073_FMV_THTT_1  },
    {&u1_CALIB_MCUID0934_FUECO_UNIT_2  , &u1_CALIB_MCUID0944_UNIT_SW_2  , &u1_CALIB_MCUID0954_BUZ_REV_2  , &u1_CALIB_MCUID0964_BUZ_GSO_2  , &u1_CALIB_MCUID0974_BUZ_AIS_2  , &u1_CALIB_MCUID0984_BUZ_NOT_2  , &u1_CALIB_MCUID1094_BUZ_BELT_2  , &u1_CALIB_MCUID0994_SP_UNIT_2  , &u1_CALIB_MCUID1004_SPUN_MSSW_2  , &u1_CALIB_MCUID1014_SUB_SP_DIS_2  , &u1_CALIB_MCUID1024_SP_TOL_2  , &u1_CALIB_MCUID1034_CH_REG_GB_2  , &u1_CALIB_MCUID1044_FMV_BRATT_2  , &u1_CALIB_MCUID1054_FMV_ABSTT_2  , &u1_CALIB_MCUID1064_FMV_EPTT_2  , &u1_CALIB_MCUID1074_FMV_THTT_2  },
    {&u1_CALIB_MCUID0935_FUECO_UNIT_3  , &u1_CALIB_MCUID0945_UNIT_SW_3  , &u1_CALIB_MCUID0955_BUZ_REV_3  , &u1_CALIB_MCUID0965_BUZ_GSO_3  , &u1_CALIB_MCUID0975_BUZ_AIS_3  , &u1_CALIB_MCUID0985_BUZ_NOT_3  , &u1_CALIB_MCUID1095_BUZ_BELT_3  , &u1_CALIB_MCUID0995_SP_UNIT_3  , &u1_CALIB_MCUID1005_SPUN_MSSW_3  , &u1_CALIB_MCUID1015_SUB_SP_DIS_3  , &u1_CALIB_MCUID1025_SP_TOL_3  , &u1_CALIB_MCUID1035_CH_REG_GB_3  , &u1_CALIB_MCUID1045_FMV_BRATT_3  , &u1_CALIB_MCUID1055_FMV_ABSTT_3  , &u1_CALIB_MCUID1065_FMV_EPTT_3  , &u1_CALIB_MCUID1075_FMV_THTT_3  },
    {&u1_CALIB_MCUID0936_FUECO_UNIT_4  , &u1_CALIB_MCUID0946_UNIT_SW_4  , &u1_CALIB_MCUID0956_BUZ_REV_4  , &u1_CALIB_MCUID0966_BUZ_GSO_4  , &u1_CALIB_MCUID0976_BUZ_AIS_4  , &u1_CALIB_MCUID0986_BUZ_NOT_4  , &u1_CALIB_MCUID1096_BUZ_BELT_4  , &u1_CALIB_MCUID0996_SP_UNIT_4  , &u1_CALIB_MCUID1006_SPUN_MSSW_4  , &u1_CALIB_MCUID1016_SUB_SP_DIS_4  , &u1_CALIB_MCUID1026_SP_TOL_4  , &u1_CALIB_MCUID1036_CH_REG_GB_4  , &u1_CALIB_MCUID1046_FMV_BRATT_4  , &u1_CALIB_MCUID1056_FMV_ABSTT_4  , &u1_CALIB_MCUID1066_FMV_EPTT_4  , &u1_CALIB_MCUID1076_FMV_THTT_4  },
    {&u1_CALIB_MCUID0937_FUECO_UNIT_5  , &u1_CALIB_MCUID0947_UNIT_SW_5  , &u1_CALIB_MCUID0957_BUZ_REV_5  , &u1_CALIB_MCUID0967_BUZ_GSO_5  , &u1_CALIB_MCUID0977_BUZ_AIS_5  , &u1_CALIB_MCUID0987_BUZ_NOT_5  , &u1_CALIB_MCUID1097_BUZ_BELT_5  , &u1_CALIB_MCUID0997_SP_UNIT_5  , &u1_CALIB_MCUID1007_SPUN_MSSW_5  , &u1_CALIB_MCUID1017_SUB_SP_DIS_5  , &u1_CALIB_MCUID1027_SP_TOL_5  , &u1_CALIB_MCUID1037_CH_REG_GB_5  , &u1_CALIB_MCUID1047_FMV_BRATT_5  , &u1_CALIB_MCUID1057_FMV_ABSTT_5  , &u1_CALIB_MCUID1067_FMV_EPTT_5  , &u1_CALIB_MCUID1077_FMV_THTT_5  },
    {&u1_CALIB_MCUID0938_FUECO_UNIT_6  , &u1_CALIB_MCUID0948_UNIT_SW_6  , &u1_CALIB_MCUID0958_BUZ_REV_6  , &u1_CALIB_MCUID0968_BUZ_GSO_6  , &u1_CALIB_MCUID0978_BUZ_AIS_6  , &u1_CALIB_MCUID0988_BUZ_NOT_6  , &u1_CALIB_MCUID1098_BUZ_BELT_6  , &u1_CALIB_MCUID0998_SP_UNIT_6  , &u1_CALIB_MCUID1008_SPUN_MSSW_6  , &u1_CALIB_MCUID1018_SUB_SP_DIS_6  , &u1_CALIB_MCUID1028_SP_TOL_6  , &u1_CALIB_MCUID1038_CH_REG_GB_6  , &u1_CALIB_MCUID1048_FMV_BRATT_6  , &u1_CALIB_MCUID1058_FMV_ABSTT_6  , &u1_CALIB_MCUID1068_FMV_EPTT_6  , &u1_CALIB_MCUID1078_FMV_THTT_6  },
    {&u1_CALIB_MCUID0939_FUECO_UNIT_7  , &u1_CALIB_MCUID0949_UNIT_SW_7  , &u1_CALIB_MCUID0959_BUZ_REV_7  , &u1_CALIB_MCUID0969_BUZ_GSO_7  , &u1_CALIB_MCUID0979_BUZ_AIS_7  , &u1_CALIB_MCUID0989_BUZ_NOT_7  , &u1_CALIB_MCUID1099_BUZ_BELT_7  , &u1_CALIB_MCUID0999_SP_UNIT_7  , &u1_CALIB_MCUID1009_SPUN_MSSW_7  , &u1_CALIB_MCUID1019_SUB_SP_DIS_7  , &u1_CALIB_MCUID1029_SP_TOL_7  , &u1_CALIB_MCUID1039_CH_REG_GB_7  , &u1_CALIB_MCUID1049_FMV_BRATT_7  , &u1_CALIB_MCUID1059_FMV_ABSTT_7  , &u1_CALIB_MCUID1069_FMV_EPTT_7  , &u1_CALIB_MCUID1079_FMV_THTT_7  },
    {&u1_CALIB_MCUID0940_FUECO_UNIT_8  , &u1_CALIB_MCUID0950_UNIT_SW_8  , &u1_CALIB_MCUID0960_BUZ_REV_8  , &u1_CALIB_MCUID0970_BUZ_GSO_8  , &u1_CALIB_MCUID0980_BUZ_AIS_8  , &u1_CALIB_MCUID0990_BUZ_NOT_8  , &u1_CALIB_MCUID1100_BUZ_BELT_8  , &u1_CALIB_MCUID1000_SP_UNIT_8  , &u1_CALIB_MCUID1010_SPUN_MSSW_8  , &u1_CALIB_MCUID1020_SUB_SP_DIS_8  , &u1_CALIB_MCUID1030_SP_TOL_8  , &u1_CALIB_MCUID1040_CH_REG_GB_8  , &u1_CALIB_MCUID1050_FMV_BRATT_8  , &u1_CALIB_MCUID1060_FMV_ABSTT_8  , &u1_CALIB_MCUID1070_FMV_EPTT_8  , &u1_CALIB_MCUID1080_FMV_THTT_8  },
    {&u1_CALIB_MCUID0941_FUECO_UNIT_9  , &u1_CALIB_MCUID0951_UNIT_SW_9  , &u1_CALIB_MCUID0961_BUZ_REV_9  , &u1_CALIB_MCUID0971_BUZ_GSO_9  , &u1_CALIB_MCUID0981_BUZ_AIS_9  , &u1_CALIB_MCUID0991_BUZ_NOT_9  , &u1_CALIB_MCUID1101_BUZ_BELT_9  , &u1_CALIB_MCUID1001_SP_UNIT_9  , &u1_CALIB_MCUID1011_SPUN_MSSW_9  , &u1_CALIB_MCUID1021_SUB_SP_DIS_9  , &u1_CALIB_MCUID1031_SP_TOL_9  , &u1_CALIB_MCUID1041_CH_REG_GB_9  , &u1_CALIB_MCUID1051_FMV_BRATT_9  , &u1_CALIB_MCUID1061_FMV_ABSTT_9  , &u1_CALIB_MCUID1071_FMV_EPTT_9  , &u1_CALIB_MCUID1081_FMV_THTT_9  },
    {&u1_CALIB_MCUID0942_FUECO_UNIT_10 , &u1_CALIB_MCUID0952_UNIT_SW_10 , &u1_CALIB_MCUID0962_BUZ_REV_10 , &u1_CALIB_MCUID0972_BUZ_GSO_10 , &u1_CALIB_MCUID0982_BUZ_AIS_10 , &u1_CALIB_MCUID0992_BUZ_NOT_10 , &u1_CALIB_MCUID1102_BUZ_BELT_10 , &u1_CALIB_MCUID1002_SP_UNIT_10 , &u1_CALIB_MCUID1012_SPUN_MSSW_10 , &u1_CALIB_MCUID1022_SUB_SP_DIS_10 , &u1_CALIB_MCUID1032_SP_TOL_10 , &u1_CALIB_MCUID1042_CH_REG_GB_10 , &u1_CALIB_MCUID1052_FMV_BRATT_10 , &u1_CALIB_MCUID1062_FMV_ABSTT_10 , &u1_CALIB_MCUID1072_FMV_EPTT_10 , &u1_CALIB_MCUID1082_FMV_THTT_10 }
};

static const U1    u1_sp2_VDF_DST_LAW_CCODESUP[VDF_DST_LAW_NUM_C_CODE_REG][VDF_DEST_LAW_DBF_NBYTE] = {
     /* DEFUNIT_SPD               DEFUNIT_DST              DEFUNIT_FUECO   DEFUNIT_ELECO                  UNITSLCT_FUECO                                                                                                                     UNITSLCT_DEST           BZ_SBW_SUP            MDLEST_WRN   INDSDBZR                BZ_REV_DST           SEATBLT_CONST               SUBDIGSPD                SPDTLRNC                   CHN_REQ     TTBRAKE               TTABS               TTEPBPKB                TTTAILHEAD                     */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_USA | (U1)VDF_UNIT_FUECO_BIT_MPG_UKIMP , (U1)VDF_UNIT_TYPE_NA  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID1136 , (U1)VDF_SUBDIGSPD_KMPH , (U1)VDF_SPDTLRNC_USA_CAN , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Canada            */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KMPKWH    , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_JPN , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0606 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Rep of Korea_UNR  */
      { (U1)UNIT_VAL_SPEED_MPH  , (U1)UNIT_VAL_DIST_MILE , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_MILEPKWH  , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_UK                                     , (U1)VDF_UNIT_TYPE_UK  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_MPH  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* United Kingdom    */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_USA | (U1)VDF_UNIT_FUECO_BIT_MPG_UKIMP , (U1)VDF_UNIT_TYPE_NA  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0604 , (U1)VDF_SUBDIGSPD_BOTH , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Mexico_UNR        */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* South Africa      */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_WITH , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* India             */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0607 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)TRUE  , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* China             */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)TRUE   , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID1136 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Bahrain           */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)TRUE   , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID1136 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Qatar             */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)TRUE   , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID1136 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Kuwait            */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)TRUE   , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID1136 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* UAE               */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)TRUE   , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID1136 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Saudi Arabia      */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)TRUE   , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID1136 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Oman              */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Hong Kong         */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Macau             */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Australia         */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Papua New Guinea  */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* New Zealand       */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Solomon Islands   */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Taiwan            */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Singapore         */
      { (U1)UNIT_VAL_SPEED_MPH  , (U1)UNIT_VAL_DIST_MILE , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_MILEPKWH  , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_USA | (U1)VDF_UNIT_FUECO_BIT_MPG_UKIMP , (U1)VDF_UNIT_TYPE_NA  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0606 , (U1)VDF_SUBDIGSPD_MPH  , (U1)VDF_SPDTLRNC_USA_CAN , (U1)FALSE , (U1)VDF_TTBRAKE_NO4 , (U1)VDF_TTABS_NO6 , (U1)VDF_TTEPBPKB_NO10 , (U1)VDF_TTTAILHEAD_NO12 },      /* Rep of Korea_FMVSS*/
      { (U1)UNIT_VAL_SPEED_MPH  , (U1)UNIT_VAL_DIST_MILE , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_MILEPKWH  , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_USA | (U1)VDF_UNIT_FUECO_BIT_MPG_UKIMP , (U1)VDF_UNIT_TYPE_NA  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0604 , (U1)VDF_SUBDIGSPD_BOTH , (U1)VDF_SPDTLRNC_USA_CAN , (U1)FALSE , (U1)VDF_TTBRAKE_NO4 , (U1)VDF_TTABS_NO6 , (U1)VDF_TTEPBPKB_NO10 , (U1)VDF_TTTAILHEAD_NO12 }       /* Mexico_FMVSS      */
};

static const U1    u1_sp2_VDF_DST_CCODESUP[VDF_DST_NUM_C_CODE][VDF_DEST_DBF_NBYTE] = {
     /* DESTINATION              TIMEFMT               CALDSPTYP                    SMASTAMID                 ENGUNT                EUSPDSCALE               TTTRCOFF                 TTVSCEXP                STPIND     UNIT_AMBTMP                    */
      { (U1)VDF_DEST_CAN       , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_NA    , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO155 , (U1)VDF_TT_VSCEXPERT1 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Canada            */
      { (U1)VDF_DEST_KOR       , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Rep of Korea      */
      { (U1)VDF_DEST_UK        , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_EU  , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* United Kingdom    */
      { (U1)VDF_DEST_MEX       , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_NA    , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO155 , (U1)VDF_TT_VSCEXPERT1 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Mexico            */
      { (U1)VDF_DEST_ZAF       , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* South Africa      */
      { (U1)VDF_DEST_IND       , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* India             */
      { (U1)VDF_DEST_CHN       , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* China             */
      { (U1)VDF_DEST_MDLEST    , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Bahrain           */
      { (U1)VDF_DEST_MDLEST    , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Qatar             */
      { (U1)VDF_DEST_MDLEST    , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Kuwait            */
      { (U1)VDF_DEST_MDLEST    , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* UAE               */
      { (U1)VDF_DEST_MDLEST    , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Saudi Arabia      */
      { (U1)VDF_DEST_MDLEST    , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Oman              */
      { (U1)VDF_DEST_HKGMACSGP , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Hong Kong         */
      { (U1)VDF_DEST_HKGMACSGP , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Macau             */
      { (U1)VDF_DEST_AUST      , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Australia         */
      { (U1)VDF_DEST_AUST      , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Papua New Guinea  */
      { (U1)VDF_DEST_AUST      , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* New Zealand       */
      { (U1)VDF_DEST_AUST      , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Solomon Islands   */
      { (U1)VDF_DEST_TWN       , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Taiwan            */
      { (U1)VDF_DEST_HKGMACSGP , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL }       /* Singapore         */
};

static const U1    u1_sp2_VDF_DST_LAW_DESTBDBSUP[VDF_DST_LAW_NUM_DEST_BDB_REG][VDF_DEST_LAW_DBF_NBYTE] = {
     /* DEFUNIT_SPD               DEFUNIT_DST              DEFUNIT_FUECO   DEFUNIT_ELECO                  UNITSLCT_FUECO                                                                                                                     UNITSLCT_DEST           BZ_SBW_SUP            MDLEST_WRN   INDSDBZR                BZ_REV_DST           SEATBLT_CONST               SUBDIGSPD                SPDTLRNC                   CHN_REQ     TTBRAKE               TTABS               TTEPBPKB                TTTAILHEAD                     */
      { (U1)UNIT_VAL_SPEED_MPH  , (U1)UNIT_VAL_DIST_MILE , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_MILEPKWH  , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_USA | (U1)VDF_UNIT_FUECO_BIT_MPG_UKIMP , (U1)VDF_UNIT_TYPE_NA  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID1135 , (U1)VDF_SUBDIGSPD_MPH  , (U1)VDF_SPDTLRNC_USA_CAN , (U1)FALSE , (U1)VDF_TTBRAKE_NO4 , (U1)VDF_TTABS_NO6 , (U1)VDF_TTEPBPKB_NO10 , (U1)VDF_TTTAILHEAD_NO12 },      /* America           */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_UK                                     , (U1)VDF_UNIT_TYPE_UK  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_KMPH , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Turkey            */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0607 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)TRUE  , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* China             */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* South Africa      */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Australia         */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)TRUE   , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID1136 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* MDE               */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_UK                                     , (U1)VDF_UNIT_TYPE_UK  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_KMPH , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Europe            */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_UK                                     , (U1)VDF_UNIT_TYPE_UK  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_KMPH , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Russia            */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* New Zealand       */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KMPKWH    , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_JPN , (U1)VDF_BZ_SBW_NON  , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_JPN , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* Japan             */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* GNR_L_UNR         */
      { (U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_KWHP100KM , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     , (U1)VDF_UNIT_TYPE_EU  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_NON  , (U1)VDF_SPDTLRNC_UNR_AUS , (U1)FALSE , (U1)VDF_TTBRAKE_NO3 , (U1)VDF_TTABS_NO7 , (U1)VDF_TTEPBPKB_NO9  , (U1)VDF_TTTAILHEAD_NO11 },      /* GNR_R_UNR         */
      { (U1)UNIT_VAL_SPEED_MPH  , (U1)UNIT_VAL_DIST_MILE , (U1)U1_MAX    , (U1)UNIT_VAL_ELECO_MILEPKWH  , (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_USA | (U1)VDF_UNIT_FUECO_BIT_MPG_UKIMP , (U1)VDF_UNIT_TYPE_NA  , (U1)VDF_BZ_SBW_WITH , (U1)FALSE  , (U1)VDF_INDSDBZR_NON  , (U1)VDF_BZ_REV_OTR , (U1)VDF_SEATBLT_MCUID0605 , (U1)VDF_SUBDIGSPD_MPH  , (U1)VDF_SPDTLRNC_USA_CAN , (U1)FALSE , (U1)VDF_TTBRAKE_NO4 , (U1)VDF_TTABS_NO6 , (U1)VDF_TTEPBPKB_NO10 , (U1)VDF_TTTAILHEAD_NO12 }       /* GNR_FMVSS         */
};

static const U1    u1_sp2_VDF_DST_DESTBDBSUP[VDF_DST_NUM_DEST_BDB][VDF_DEST_DBF_NBYTE] = {
     /* DESTINATION              TIMEFMT               CALDSPTYP                    SMASTAMID                 ENGUNT                EUSPDSCALE               TTTRCOFF                 TTVSCEXP                STPIND     UNIT_AMBTMP                    */
      { (U1)VDF_DEST_USA       , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_MMDDYYYY , (U1)VDF_SMASTAMID_NA    , (U1)VDF_ENGUNT_RPM  , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO155 , (U1)VDF_TT_VSCEXPERT1 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_FAH },      /* America           */
      { (U1)VDF_DEST_EU        , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_EU  , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Turkey            */
      { (U1)VDF_DEST_CHN       , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* China             */
      { (U1)VDF_DEST_ZAF       , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* South Africa      */
      { (U1)VDF_DEST_AUST      , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Australia         */
      { (U1)VDF_DEST_MDLEST    , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* MDE               */
      { (U1)VDF_DEST_EU        , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_EU  , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Europe            */
      { (U1)VDF_DEST_EU        , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_EU  , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Russia            */
      { (U1)VDF_DEST_AUST      , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* New Zealand       */
      { (U1)VDF_DEST_JPN       , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_YYYYMMDD , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* Japan             */
      { (U1)VDF_DEST_GEN       , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL },      /* GNR_L             */
      { (U1)VDF_DEST_GEN       , (U1)TIMEFMT_VAL_12H , (U1)VDF_CALDSPTYP_DDMMYYYY , (U1)VDF_SMASTAMID_WO_NA , (U1)VDF_ENGUNT_RMIN , (U1)VDF_EUSPDSCALE_NML , (U1)VDF_TTTRCOFF_NO8   , (U1)VDF_TT_VSCEXPERT2 , (U1)TRUE , (U1)UNIT_VAL_AMBTMP_CEL }       /* GNR_R             */
};

static const U1    u1_sp_VDF_DST_SPEC_DESTID[VDF_NUM_UNIT_DEF_CFG][VDF_DEST_SPEC_LAW_DESTID] = {
    /*  DEFUNIT_SPD            DEFUNIT_DST              DEFUNIT_FUECO                DEFUNIT_ELECO               */
    {(U1)UNIT_VAL_SPEED_MPH  , (U1)UNIT_VAL_DIST_MILE , (U1)U1_MAX ,                 (U1)UNIT_VAL_ELECO_MILEPKWH },
    {(U1)UNIT_VAL_SPEED_MPH  , (U1)UNIT_VAL_DIST_MILE , (U1)U1_MAX ,                 (U1)UNIT_VAL_ELECO_MILEPKWH },
    {(U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX ,                 (U1)UNIT_VAL_ELECO_KMPKWH   },
    {(U1)UNIT_VAL_SPEED_KMPH , (U1)UNIT_VAL_DIST_KM   , (U1)U1_MAX ,                 (U1)UNIT_VAL_ELECO_KWHP100KM}
};

static const U1    u1_sp_VDF_UNIT_SLCT[VDF_DET_UNIT_SLCT_NUM] = {
    (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_USA | (U1)VDF_UNIT_FUECO_BIT_MPG_UKIMP ,      /* North America         */
    (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     ,      /* Commercially availabl */
    (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM                                                                     ,      /* Europe                */
    (U1)VDF_UNIT_FUECO_BIT_KMPL | (U1)VDF_UNIT_FUECO_BIT_LP100KM | (U1)VDF_UNIT_FUECO_BIT_MPG_UK                                            /* United Kingdom        */
};

static const ST_VDF_DST_SUB_VEHSPD    st_sp_VDF_DST_SUB_DIG_SPD[VDF_DET_SUB_DIG_SPD_IDX] = {
    /* DESTID0021                                                           DESTID0022                                                                     DESTID0023                         SUBDIGSPD              */
    {((U1)VDF_VEH_SPD_UNIT_KMHMPH << (U1)VDF_DET_SUB_DIG_SPD_OFFSET_UNIT) | ((U1)VDF_VEH_SPD_UNIT_MSSW_WITH    << (U1)VDF_DET_SUB_DIG_SPD_OFFSET_UNTCHG) | (U1)VDF_VEH_SPD_UNIT_DSP_WITHOUT , (U1)VDF_SUBDIGSPD_NON  },
    {((U1)VDF_VEH_SPD_UNIT_KMHMPH << (U1)VDF_DET_SUB_DIG_SPD_OFFSET_UNIT) | ((U1)VDF_VEH_SPD_UNIT_MSSW_WITH    << (U1)VDF_DET_SUB_DIG_SPD_OFFSET_UNTCHG) | (U1)VDF_VEH_SPD_UNIT_DSP_ALWAYS  , (U1)VDF_SUBDIGSPD_BOTH },
    {((U1)VDF_VEH_SPD_UNIT_KMHMPH << (U1)VDF_DET_SUB_DIG_SPD_OFFSET_UNIT) | ((U1)VDF_VEH_SPD_UNIT_MSSW_WITH    << (U1)VDF_DET_SUB_DIG_SPD_OFFSET_UNTCHG) | (U1)VDF_VEH_SPD_UNIT_DSP_NONDEF  , (U1)VDF_SUBDIGSPD_KMPH },
    {((U1)VDF_VEH_SPD_UNIT_MPHKMH << (U1)VDF_DET_SUB_DIG_SPD_OFFSET_UNIT) | ((U1)VDF_VEH_SPD_UNIT_MSSW_WITH    << (U1)VDF_DET_SUB_DIG_SPD_OFFSET_UNTCHG) | (U1)VDF_VEH_SPD_UNIT_DSP_WITHOUT , (U1)VDF_SUBDIGSPD_NON  },
    {((U1)VDF_VEH_SPD_UNIT_MPHKMH << (U1)VDF_DET_SUB_DIG_SPD_OFFSET_UNIT) | ((U1)VDF_VEH_SPD_UNIT_MSSW_WITH    << (U1)VDF_DET_SUB_DIG_SPD_OFFSET_UNTCHG) | (U1)VDF_VEH_SPD_UNIT_DSP_ALWAYS  , (U1)VDF_SUBDIGSPD_BOTH },
    {((U1)VDF_VEH_SPD_UNIT_MPHKMH << (U1)VDF_DET_SUB_DIG_SPD_OFFSET_UNIT) | ((U1)VDF_VEH_SPD_UNIT_MSSW_WITH    << (U1)VDF_DET_SUB_DIG_SPD_OFFSET_UNTCHG) | (U1)VDF_VEH_SPD_UNIT_DSP_NONDEF  , (U1)VDF_SUBDIGSPD_MPH  },
    {((U1)VDF_VEH_SPD_UNIT_KMH    << (U1)VDF_DET_SUB_DIG_SPD_OFFSET_UNIT) | ((U1)VDF_VEH_SPD_UNIT_MSSW_WITHOUT << (U1)VDF_DET_SUB_DIG_SPD_OFFSET_UNTCHG) | (U1)VDF_VEH_SPD_UNIT_DSP_WITHOUT , (U1)VDF_SUBDIGSPD_NON  },
    {((U1)VDF_VEH_SPD_UNIT_MPH    << (U1)VDF_DET_SUB_DIG_SPD_OFFSET_UNIT) | ((U1)VDF_VEH_SPD_UNIT_MSSW_WITHOUT << (U1)VDF_DET_SUB_DIG_SPD_OFFSET_UNTCHG) | (U1)VDF_VEH_SPD_UNIT_DSP_WITHOUT , (U1)VDF_SUBDIGSPD_NON  }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_VardefDestCfg(U2 * u2p_a_c_code, U1 * u1p_a_dest_bdb, U1 * u1p_a_strg_whl)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefDestCfg(U2 * u2p_a_c_code, U1 * u1p_a_dest_bdb, U1 * u1p_a_strg_whl)
{
    static const U2 u2_s_VDF_DST_C_CODE_MSK  = (U2)0x000FU;
    static const U1 u1_s_VDF_DST_C_CODE1_BIT = (U1)8U;
    static const U1 u1_s_VDF_DST_C_CODE2_BIT = (U1)4U;
    U1  u1_t_rxcnt;
    U1  u1_t_c_code;

    u1_t_c_code = (U1)0U;
    u1_t_rxcnt = u1_g_oXCANRxdEvcnt((U2)OXCAN_RXD_PDU_CAN_BDB1S08_CH0);

    (void)Com_ReceiveSignal(ComConf_ComSignal_C_CODE1, &u1_t_c_code);
    *u2p_a_c_code =  ((U2)u1_t_c_code & u2_s_VDF_DST_C_CODE_MSK) << u1_s_VDF_DST_C_CODE1_BIT;

    (void)Com_ReceiveSignal(ComConf_ComSignal_C_CODE2, &u1_t_c_code);
    *u2p_a_c_code |= (U2)(((U2)u1_t_c_code & u2_s_VDF_DST_C_CODE_MSK) << u1_s_VDF_DST_C_CODE2_BIT);

    (void)Com_ReceiveSignal(ComConf_ComSignal_C_CODE3, &u1_t_c_code);
    *u2p_a_c_code |= ((U2)u1_t_c_code & u2_s_VDF_DST_C_CODE_MSK);

    (void)Com_ReceiveSignal(ComConf_ComSignal_DEST_BDB, u1p_a_dest_bdb);
    (void)Com_ReceiveSignal(ComConf_ComSignal_STRG_WHL, u1p_a_strg_whl);

    return(u1_t_rxcnt);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VardefDestCfgDBSup(const U1 u1_a_DBF, const U1 u1_a_C_CODE_IDX, const U1 u1_a_DEST_BDB_IDX)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefDestCfgDBSup(const U1 u1_a_DBF, const U1 u1_a_C_CODE_IDX, const U1 u1_a_DEST_BDB_IDX)
{
    U1  u1_t_sup;

    u1_t_sup = (U1)0U;

    if(u1_a_DBF < (U1)VDF_DEST_DBF_NBYTE){
        if(u1_a_C_CODE_IDX < (U1)VDF_DST_NUM_C_CODE){
            u1_t_sup = u1_sp2_VDF_DST_CCODESUP[u1_a_C_CODE_IDX][u1_a_DBF];
        }
        else{
            u1_t_sup = (U1)U1_MAX;
        }

        if(u1_t_sup == (U1)U1_MAX){
            if(u1_a_DEST_BDB_IDX < (U1)VDF_DST_NUM_DEST_BDB){
                u1_t_sup = u1_sp2_VDF_DST_DESTBDBSUP[u1_a_DEST_BDB_IDX][u1_a_DBF];
            }
            else{
                u1_t_sup = u1_sp2_VDF_DST_DESTBDBSUP[u1_g_VDF_DST_DEST_BDB_IDX_DEF][u1_a_DBF];
            }
        }
    }

    return(u1_t_sup);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VardefDestSpecCfgDBSup(const U1 u1_a_LAW_DBF, const U1 u1_a_SPEC_C_CODE_IDX)                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefDestSpecCfgDBSup(const U1 u1_a_LAW_DBF, const U1 u1_a_SPEC_C_CODE_IDX)
{
    U1  u1_t_sup;
    U1  u1_t_spec_cfg;
    U1  u1_t_idx_loop;
    U1  u1_t_destid0021;
    U1  u1_t_destid0022;
    U1  u1_t_destid0023;

    u1_t_sup = (U1)U1_MAX;
    u1_t_spec_cfg = (U1)U1_MAX;
    u1_t_destid0021 = (U1)U1_MIN;
    u1_t_destid0022 = (U1)U1_MIN;
    u1_t_destid0023 = (U1)U1_MIN;

    /* Special country constant processing logic */
    if((U1)VDF_DST_SPEC_NUM_C_CODE_REG > u1_a_SPEC_C_CODE_IDX){
        if(((U1)VDF_DEST_LAW_DBF_DEFUNIT_SPD    == u1_a_LAW_DBF) ||
            ((U1)VDF_DEST_LAW_DBF_DEFUNIT_DST   == u1_a_LAW_DBF) ||
            ((U1)VDF_DEST_LAW_DBF_DEFUNIT_FUECO == u1_a_LAW_DBF) ||
            ((U1)VDF_DEST_LAW_DBF_DEFUNIT_ELECO == u1_a_LAW_DBF)){
            /* Query the special country constant configuration table to get the configuration value */
            u1_t_spec_cfg = *(u1p_sp2_VDF_DST_SPEC_CCODESUP[u1_a_SPEC_C_CODE_IDX][VDF_DEST_SPEC_DESTID0001]);

            if((U1)VDF_NUM_UNIT_DEF_CFG > u1_t_spec_cfg){
                /* Read the value of the corresponding interface from the configuration table */
                u1_t_sup = u1_sp_VDF_DST_SPEC_DESTID[u1_t_spec_cfg][u1_a_LAW_DBF];
            }
            else{
                /* u1_t_sup = (U1)U1_MAX; */
            }
        }
        else if((U1)VDF_DEST_LAW_DBF_UNITSLCT_FUECO == u1_a_LAW_DBF){
            /* Query the special country constant configuration table to get the configuration value */
            u1_t_spec_cfg = *(u1p_sp2_VDF_DST_SPEC_CCODESUP[u1_a_SPEC_C_CODE_IDX][VDF_DEST_SPEC_DESTID0002]);

            /* Search for in the Select Unit configuration table */
            u1_t_sup = u1_sp_VDF_UNIT_SLCT[u1_t_spec_cfg];
        }
        else if((U1)VDF_DEST_LAW_DBF_SUBDIGSPD == u1_a_LAW_DBF){
            /* Configure combinations of sub-vehicle speed-related configuration items */
            u1_t_destid0021 = (*(u1p_sp2_VDF_DST_SPEC_CCODESUP[u1_a_SPEC_C_CODE_IDX][VDF_DEST_SPEC_DESTID0021]));
            u1_t_destid0022 = (*(u1p_sp2_VDF_DST_SPEC_CCODESUP[u1_a_SPEC_C_CODE_IDX][VDF_DEST_SPEC_DESTID0022]));
            u1_t_destid0023 = (*(u1p_sp2_VDF_DST_SPEC_CCODESUP[u1_a_SPEC_C_CODE_IDX][VDF_DEST_SPEC_DESTID0023]));
            u1_t_spec_cfg   = (u1_t_destid0021 << VDF_DET_SUB_DIG_SPD_OFFSET_UNIT);
            u1_t_spec_cfg   |= (u1_t_destid0022 << VDF_DET_SUB_DIG_SPD_OFFSET_UNTCHG);
            u1_t_spec_cfg   |= u1_t_destid0023;
            for(u1_t_idx_loop = (U1)0U; u1_t_idx_loop < (U1)VDF_DET_SUB_DIG_SPD_IDX; ++u1_t_idx_loop){
                if(st_sp_VDF_DST_SUB_DIG_SPD[u1_t_idx_loop].u1_t_sub_spd_cfg == u1_t_spec_cfg){
                    u1_t_sup = st_sp_VDF_DST_SUB_DIG_SPD[u1_t_idx_loop].u1_t_sub_dig_spd;
                }
                else{
                     /* u1_t_sup = (U1)U1_MAX; */
                }
            }
        }
        else{
            for(u1_t_idx_loop = (U1)0U; u1_t_idx_loop < (U1)VDF_DEST_LAW_DBF_NBYTE; ++u1_t_idx_loop){
                /* Obtain the DESTID of the special country */
                if(st_sp_VDF_DEST_LAW_IFID_IDX[u1_t_idx_loop].u1_t_law_if_name == u1_a_LAW_DBF){
                    u1_t_spec_cfg = st_sp_VDF_DEST_LAW_IFID_IDX[u1_t_idx_loop].u1_t_law_destid;
                }
                else{
                     /* u1_t_sup = (U1)U1_MAX; */
                }

                /* Query configuration table configuration */
                if(u1_t_spec_cfg < (U1)VDF_DEST_NUM_LAW_DESTID){
                    u1_t_sup = *(u1p_sp2_VDF_DST_SPEC_CCODESUP[u1_a_SPEC_C_CODE_IDX][u1_t_spec_cfg]);
                }
                else{
                    /* u1_t_sup = (U1)U1_MAX; */
                }
            }

        }

    }
    else{
        /* u1_t_sup = (U1)U1_MAX; */
    }

    return(u1_t_sup);
}
/*==============================================================================================================================================================================*/
/*  U1      u1_g_VardefDestLawCfgDBSup(const U1 u1_a_LAW_DBF, const U1 u1_a_SPEC_C_CODE_IDX, const U1 u1_a_LAW_C_CODE_IDX, const U1 u1_a_LAW_DEST_BDB_IDX)                      */
/* ----------------------------------------------------------------------------------------------------------------------------------- ----------------------------- ---------- */
/*  Arguments:      -                                                                                                                                                           */
/*  Return:         -                                                                                                                                                           */
/*==============================================================================================================================================================================*/
U1      u1_g_VardefDestLawCfgDBSup(const U1 u1_a_LAW_DBF, const U1 u1_a_SPEC_C_CODE_IDX, const U1 u1_a_LAW_C_CODE_IDX, const U1 u1_a_LAW_DEST_BDB_IDX)
{
    U1  u1_t_sup;
    U1  u1_t_law_destbdb_idx_def;

    u1_t_sup = (U1)U1_MAX;
    u1_t_law_destbdb_idx_def = u1_g_VardefDestLawCfgBdbDefJdg();

    if (u1_a_LAW_DBF < (U1)VDF_DEST_LAW_DBF_NBYTE) {

        u1_t_sup = u1_g_VardefDestSpecCfgDBSup(u1_a_LAW_DBF, u1_a_SPEC_C_CODE_IDX);

        /* Special Country Constant Matching Failure processing Logic */
        if (((U1)U1_MAX == u1_t_sup) && (u1_a_LAW_C_CODE_IDX < (U1)VDF_DST_LAW_NUM_C_CODE_REG)) {
            u1_t_sup = u1_sp2_VDF_DST_LAW_CCODESUP[u1_a_LAW_C_CODE_IDX][u1_a_LAW_DBF];
        }
        else {
            /* Do nothing */
        }

        if (u1_t_sup == (U1)U1_MAX) {
            if (u1_a_LAW_DEST_BDB_IDX < (U1)VDF_DST_LAW_NUM_DEST_BDB_REG) {
                u1_t_sup = u1_sp2_VDF_DST_LAW_DESTBDBSUP[u1_a_LAW_DEST_BDB_IDX][u1_a_LAW_DBF];
            }
            else {
                u1_t_sup = u1_sp2_VDF_DST_LAW_DESTBDBSUP[u1_t_law_destbdb_idx_def][u1_a_LAW_DBF];
            }
        }
        else {
            /* Keep last */
        }
    }
    else {
        /* u1_t_sup = (U1)U1_MAX; */
    }


    return(u1_t_sup);
}
/*===================================================================================================================================*/
/*  U1      u1_g_VardefCfgUnitType(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefCfgUnitType(void)
{
    static const U1 u1_s_UNITTYPE_TBL[VDF_NUM_PTSYS][VDF_NUM_UNIT_TYPE_DEST] = {
        /* VDF_UNIT_TYPE_NA   , VDF_UNIT_TYPE_JPN   , VDF_UNIT_TYPE_EU    , VDF_UNIT_TYPE_UK     */
        { (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* UNK       */
        { (U1)VDF_UNIT_TYPE_A , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_B },    /* GAS       */
        { (U1)VDF_UNIT_TYPE_A , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_B },    /* GAS_ISS   */
        { (U1)VDF_UNIT_TYPE_A , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_B },    /* HYB       */
        { (U1)VDF_UNIT_TYPE_D , (U1)VDF_UNIT_TYPE_F , (U1)VDF_UNIT_TYPE_F , (U1)VDF_UNIT_TYPE_E },    /* HYB_PLU   */
        { (U1)VDF_UNIT_TYPE_H , (U1)VDF_UNIT_TYPE_G , (U1)VDF_UNIT_TYPE_G , (U1)VDF_UNIT_TYPE_H },    /* ELE_BAT   */
        { (U1)VDF_UNIT_TYPE_A , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_B },    /* HYB_MOT   */
        { (U1)VDF_UNIT_TYPE_I , (U1)VDF_UNIT_TYPE_L , (U1)VDF_UNIT_TYPE_K , (U1)VDF_UNIT_TYPE_J },    /* ELE_HYD   */
        { (U1)VDF_UNIT_TYPE_A , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_B },    /* 48V       */
        { (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* UNK       */
        { (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* UNK       */
        { (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* UNK       */
        { (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* UNK       */
        { (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* UNK       */
        { (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C },    /* UNK       */
        { (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C , (U1)VDF_UNIT_TYPE_C }     /* UNK       */
    };

    U1 u1_t_unit_dest;
    U1 u1_t_unit_type;
    U1 u1_t_ptsys;

    u1_t_unit_type = (U1)VDF_UNIT_TYPE_C;
    u1_t_unit_dest = u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_UNITSLCT_DEST);
    u1_t_ptsys     = u1_g_VardefPtsRx();

    if((u1_t_unit_dest < (U1)VDF_NUM_UNIT_TYPE_DEST) &&
       (u1_t_ptsys     < (U1)VDF_NUM_PTSYS)){
        u1_t_unit_type = u1_s_UNITTYPE_TBL[u1_t_ptsys][u1_t_unit_dest];
    }

    return(u1_t_unit_type);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefCfgBltDst(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefCfgBltDst(void)
{
    static const U1    u1_s_BLTDST_TBL[CALIB_SEATBELT_REGULATION_NUM] = {
        (U1)VDF_SEATBLT_DEST_USA,          /* CALIB_MCUID1135,CALIB_MCUID1136 and CALIB_MCUID0604_TO_MCUID0607_USA         (0) */
        (U1)VDF_SEATBLT_DEST_EU,           /* CALIB_MCUID1135,CALIB_MCUID1136 and CALIB_MCUID0604_TO_MCUID0607_AUS         (1) */
        (U1)VDF_SEATBLT_DEST_CHN           /* CALIB_MCUID1135,CALIB_MCUID1136 and CALIB_MCUID0604_TO_MCUID0607_CHN         (2) */
    };

    U1 u1_t_blt_const;
    U1 u1_t_blt_dst;
    U1 u1_t_blt_calib;
    U1 u1_t_blt_lawidx;

    u1_t_blt_dst   = (U1)VDF_SEATBLT_DEST_USA;
    u1_t_blt_calib = (U1)VDF_SEATBLT_DEST_USA_IDX;

    u1_t_blt_lawidx = u1_g_VardefLawIdx();
    if (u1_g_VDF_DST_LAW_SPEC_IDX_DEF == u1_t_blt_lawidx) {
        u1_t_blt_const = u1_g_VardefDestLawDbfByPid((U1)VDF_DEST_LAW_DBF_SEATBLT_CONST);

        switch(u1_t_blt_const){
            case (U1)VDF_SEATBLT_MCUID1135:
                u1_t_blt_calib = u1_g_VardefOmusMCUID1135();
                break;
            case (U1)VDF_SEATBLT_MCUID1136:
                u1_t_blt_calib = u1_g_VardefOmusMCUID1136();
                break;
            case (U1)VDF_SEATBLT_MCUID0604:
                u1_t_blt_calib = u1_g_VardefOmusMCUID0604();
                break;
            case (U1)VDF_SEATBLT_MCUID0605:
                u1_t_blt_calib = u1_g_VardefOmusMCUID0605();
                break;
            case (U1)VDF_SEATBLT_MCUID0606:
                u1_t_blt_calib = u1_g_VardefOmusMCUID0606();
                break;
            case (U1)VDF_SEATBLT_MCUID0607:
                u1_t_blt_calib = u1_g_VardefOmusMCUID0607();
                break;
            default:
                u1_t_blt_calib = u1_g_VardefOmusMCUID0605();
                break;
    }
        }
    else {
        if (u1_t_blt_lawidx < (U1)VDF_DST_SPEC_NUM_C_CODE_REG) {
            u1_t_blt_calib = *(u1p_sp2_VDF_DST_SPEC_CCODESUP[u1_t_blt_lawidx][VDF_DEST_SPEC_DESTID0020]);
        }
        else {
            /* u1_t_blt_dst   = (U1)VDF_SEATBLT_DEST_USA; */
        }
    }

    u1_t_blt_dst = u1_s_BLTDST_TBL[u1_t_blt_calib];

    return(u1_t_blt_dst);
}

/*===================================================================================================================================*/
/*  U1      u1_g_VardefDestLawCfgBdbDefJdg(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VardefDestLawCfgBdbDefJdg(void)
{
    U1 u1_t_law_idx_def;

    u1_t_law_idx_def = VDF_DST_LAW_DEST_BDB_B_GNR_FMVSS;
    if(u1_CALIB_MCUID3020_GEN_LOW == (U1)CALIB_MCUID3020_UNR){
        u1_t_law_idx_def = VDF_DST_LAW_DEST_BDB_B_GNR_L;
    }

    return(u1_t_law_idx_def);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     1/25/2021  SF       New.                                                                                               */
/*  2.0.0     1/24/2024  HF       19PFv3.                                                                                            */
/*  2.1.0    10/28/2024  AA       M_DESTVARI-CSTD-A0-07 spec update                                                                  */
/*  2.2.0     6/27/2025  SNk      for BEV System_Consideration_2.(MET-M_DESTVARI-CSTD-A0-06)                                         */
/*  3.0.0     1/30/2026  YN       for BEVstep3_FF2.(MET-M_DESTVARI-CSTD-0-01)                                                        */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  032D-1    1/25/2021  SF       Change config for 032D CV                                                                          */
/*  840B-1    4/14/2021  AT       Change config for 840B CV                                                                          */
/*  893B-1    6/14/2021  RO       Change config for 893B CV                                                                          */
/*  178D-1    7/19/2021  SF       Change config for 178D CV                                                                          */
/*  300D-1    8/02/2021  RO       Change config for 300D CV                                                                          */
/*  460B-1    9/27/2021  RO       Change config for 460B CV                                                                          */
/*  893B-2   11/18/2021  RO       Change config for 893B 1A                                                                          */
/*  840B-2   12/20/2021  RO       Change config for 840B 1A                                                                          */
/*  840B-3    1/24/2022  RO       Change config for 840B MPT                                                                         */
/*  300D-2    2/14/2022  SK       Change config for 300D ECI                                                                         */
/*  175D-1    3/31/2022  HA       Change config for 175D/177D/227D 1A                                                                */
/*  178D-2    4/04/2022  RO       Change config for 178D MPT                                                                         */
/*  460B-2    4/15/2022  RO       Change config for 178D MPT                                                                         */
/*  025D182D-1 4/14/2022 SK       Change config for 025D182D 1A                                                                      */
/*  200D-1    6/08/2022  RO       Change config for 200D Certified Car                                                               */
/*  200D-2    7/01/2022  RO       Change config for 200D 970B Pre1A                                                                  */
/*  220D-1    7/14/2022  RO       Change config for 220D Pre1A                                                                       */
/*  115D117D-1 8/24/2022 RO       Change config for 115D117D 1A                                                                      */
/*  115D117D-2 8/31/2022 RO       Change config for 115D117D 1A                                                                      */
/*  200D-3    9/05/2022  RO       Change config for 200D 1A                                                                          */
/*  296D-1    9/02/2022  HA       Change config for 296D CV                                                                          */
/*  960B-1     9/13/2022 SK       Change config for 960B Pre1A                                                                       */
/*  115D117D-4 10/31/2022 RO      Change config for 115D117D MPT                                                                     */
/*  448D-1    12/05/2022 SK       Change config for 448D CV                                                                          */
/*  458D-1     2/01/2023 HA       Change config for 458D Certified Car                                                               */
/*  539D-1    2/16/2023  HA       Change config for 539D CV-R                                                                        */
/*  396D-1    2/21/2023  HA       Change config for 396D Certified Car                                                               */
/*  234D-1    3/14/2023  HA       Change config for 234D239D Certified Car                                                           */
/*  458D-2    4/18/2023  RO       Change config for 448D539D396D234D239D458D 1A                                                      */
/*  960B-2    5/08/2023  RO       Change config for 960B 1A                                                                          */
/*  234D-1    5/22/2023  RO       Change config for 234D239D458D 1A                                                                  */
/*  587D588D-1 6/01/2023 HA       Change config for 587D588D CV                                                                      */
/*  19PFv3-1  1/19/2024  HF       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-2  2/23/2024  DR       Added config for TMNT                                                                              */
/*  19PFv3-3  4/12/2024  SH       Add calibration guard                                                                              */
/*  19PFv3-4  5/16/2024  SH       Add calibration guard(MCUID0603toMCUID0607)                                                        */
/*  19PFv3-5  6/06/2024  SM       Change config for 19PFv3 R1(MET-M_DESTVARI-CSTD-A0-04)                                             */
/*  19PFv3-6  7/05/2024  TN       Delete Calibration Guard Process except for out of array references.                               */
/*  19PFv3-7  7/09/2024  KH       Change config for 19PFv3 R1.2 (BSTPR -> PRESSUNIT)                 .                               */
/*  19PFv3-8  7/12/2024  TN       Add Calibration Guard to Unify Vehicle Operation.                                                  */
/*  19PFv3-9 12/03/2024  AA       Deleted Colombia control parameter              .                                                  */
/*  19PFv3-10 1/16/2025  SN       Change DEFUNIT_FUECO United Kingdom parameter             .                                        */
/*  19PFv3-11 4/10/2025  TR       Deletion of TMNT function presence judgement function             .                                */
/*  BEV-1     3/06/2025  SF       Setting for BEV System_Consideration_1.(Requests from the SOC team)                                */
/*  BEV-2     6/27/2025  SNk      Setting for BEV System_Consideration_2.(MET-M_DESTVARI-CSTD-A0-06)                                 */
/*  BEV-3    10/15/2025  SN       Configured for BEVstep3_Rebase                                                                     */
/*  BEV-4     1/22/2026  YN       Change config for BEV FF2(MET-D_4WDSYS-CSTD-2-02-A-C1)                                             */
/*  BEV-5     2/09/2026  MA       Delete u1_g_VardefTmntOpt                                                                          */
/*                                                                                                                                   */
/*  * SF   = Seiya Fukutome, DENSO TECHNO                                                                                            */
/*  * AT   = Ayano Tomimoto, KSE                                                                                                     */
/*  * RO   = Reiya Okuda, KSE                                                                                                        */
/*  * SK   = Shotaro Kitayama, PRD                                                                                                   */
/*  * HA   = Hiroki Asano, PRD                                                                                                       */
/*  * HF   = Hinari Fukamachi, KSE                                                                                                   */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * SM   = Shota Maegawa, Denso Techno                                                                                             */
/*  * TN   = Tetsushi Nakano, Denso Techno                                                                                           */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*  * AA   = Anna Asuncion, DTPH                                                                                                     */
/*  * SF   = Shiro Furui,  DENSO TECHNO                                                                                              */
/*  * SNk  = Shizuka Nakajima, KSE                                                                                                   */
/*  * SN   = Shimon Nambu, Denso Techno                                                                                              */
/*  * TR   = Tebs Ramos, DTPH                                                                                                        */
/*  * YN   = Yujiro Nagaya, Denso Techno                                                                                             */
/*  * MA   = Misaki Aiki, Denso Techno                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/
