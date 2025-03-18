/* 2.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Meter Customize                                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_CFG_C_MAJOR                     (2)
#define MCST_CFG_C_MINOR                     (4)
#define MCST_CFG_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "mcst_cfg_private.h"
#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif
#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif
#include "vardef.h"
#if 0   /* BEV BSW provisionally */
#include "es_inspect.h"
#else
#include "es_inspect_STUB.h"
#endif
#include "dimmer.h"
#include "datesi_tim.h"
#include "hmimcst.h"
#include "hmirim.h"
#include "engspd_varrz.h"
#include "mcst_bf.h"
#include "calibration.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((MCST_CFG_C_MAJOR != MCST_H_MAJOR) || \
     (MCST_CFG_C_MINOR != MCST_H_MINOR) || \
     (MCST_CFG_C_PATCH != MCST_H_PATCH))
#error "mcst_cfg.c and mcst.h : source and header files are inconsistent!"
#endif

#if ((MCST_CFG_C_MAJOR != MCST_CFG_H_MAJOR) || \
     (MCST_CFG_C_MINOR != MCST_CFG_H_MINOR) || \
     (MCST_CFG_C_PATCH != MCST_CFG_H_PATCH))
#error "mcst_cfg.c and mcst_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define MCST_USRDAT_NUM                          (16U)
#define MCST_USR_NUM                             (4U)

#define MCST_NICKNAME_NUM                        (10U)

#define MCST_STSW_FUNC_NUM                       (8U)
#define MCST_STSWGROUP_FUNC_NUM                  (4U)

#define MCST_DRVMODE_ARRYPOS                     (1U)
#define MCST_DRVMODE_BITPOS                      (18U)
#define MCST_DRVMODE_SIG_MASK                    (0x01FC0000U)
#define MCST_DRVMODE_JDG_MASK                    (0x1FU)
#define MCST_DRVMODE3                            (0x13U)
#define MCST_DRVMODE4                            (0x1DU)

#define MCST_L_STSWRHCSTM1_FUNCMASK              (0x01U)
#define MCST_L_STSWRHCSTM2_FUNCMASK              (0xF5U)
#define MCST_L_STSWRH_FUNCMASK                   (0xFCU)

#define MCST_DIAG_UNDEF                          (0x00U)
#define MCST_DIAG_UNDEF_OFFSET                   (1U)

#define MCST_MM_UNDEF                            (0x00U)
#define MCST_MM_UNDEF_OFFSET                     (1U)

#define MCST_REV_ST_LSB                          (100U)                         /* RevSettingLSB                         */

#define MCST_FUEL_ECO_VARI_NML                      (0U)
#define MCST_FUEL_ECO_VARI_PHV                      (1U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct {
    U1         u1_id;                     /* mcst id                */
    U4          ( * fp_u4_cfgini)(const U1 u1_a_id);  /* init cfg parameter */
}ST_MCST_CFG_INI;

typedef struct {
    U1                      u1_id;        /* mcst id                */
    volatile const U1 *     u1p_mcuid;    /* Calibration ID         */
    U4                      u4_result;    /* Default Value          */
}ST_MCST_ANALOG_INI;

typedef struct {
    volatile const U1 *     u1p_mcuid;    /* Calibration ID         */
    U4                      u4_result;    /* Default Value          */
}ST_MCST_HUDANALOG_INI;

typedef struct {
    U1                      u1_id;        /* mcst id                */
    volatile const U1 *     u1p_mcuid;    /* Calibration ID         */
}ST_MCST_CONTENT_INI;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U4                      u4_gp_mcst_bfword[MCST_NUM_WORD];
U4                      u4_gp_mcst_bfword_unk[MCST_NUM_WORD_USER];

static U4               u4_sp_mcst_user1[MCST_USRDAT_NUM];
static U4               u4_sp_mcst_user2[MCST_USRDAT_NUM];
static U4               u4_sp_mcst_user3[MCST_USRDAT_NUM];

static U2               u2_sp_mcst_nickname1[MCST_NICKNAME_NUM];
static U2               u2_sp_mcst_nickname2[MCST_NICKNAME_NUM];
static U2               u2_sp_mcst_nickname3[MCST_NICKNAME_NUM];
U1                      u1_gp_mcst_func[MCST_FUNC_NUM];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static        U1      u1_s_McstCfgJdg_L_HUD_FUNC(void);
static        U1      u1_s_McstCfgJdg_L_AR_FUNC(void);
static        U1      u1_s_McstCfgJdg_L_MET_TYFN(void);
static        U1      u1_s_McstCfgJdg_L_TACHO_FUNC(void);
static        U1      u1_s_McstCfgJdg_L_RHEOF(void);
static        U1      u1_s_McstCfgJdg_L_CONT_FUNC(void);
static        U1      u1_s_McstCfgJdg_L_ECO_FUNC(void);
static        U1      u1_s_McstCfgJdg_L_EV_FUNC(void);
static        U1      u1_s_McstCfgJdg_L_REV_FUNC(void);
static        U1      u1_s_McstCfgJdg_L_RV_PK_F(void);
static        U1      u1_s_McstCfgJdg_L_MANTE(void);
static        U1      u1_s_McstCfgJdg_L_OMAINTE(void);
static        U1      u1_s_McstCfgJdg_L_VS_FUNC(void);
static        U1      u1_s_McstCfgJdg_L_STSWLHCSTM1(void);
static        U1      u1_s_McstCfgJdg_L_STSWLHCSTM2(void);
static        U1      u1_s_McstCfgJdg_L_STSWRHCSTM1(void);
static        U1      u1_s_McstCfgJdg_L_STSWRHCSTM2(void);
static        U1      u1_s_McstCfgJdg_L_STSWRHCSTM3(void);
static        U1      u1_s_McstCfgJdg_L_STSWLH(void);
static        U1      u1_s_McstCfgJdg_L_STSWRH(void);
static        U1      u1_s_McstCfgJdg_L_STSW_FUNC(void);
static        U1      u1_s_McstCfgJdg_L_GRV_FUNC(void);
static        U1      u1_s_McstCfgJdg_L_MET_TSTFN(void);
static        U1      u1_s_McstCfgDiagHUD(void);
static        U1      u1_s_McstCfgDiagHUD_ILL(void);
static        U1      u1_s_McstCfgDiagHUD_ST(void);
static        U1      u1_s_McstCfgDiagMM_MET_TYP(void);
static        U1      u1_s_McstCfgDiagMM_TACHO(void);
static        U1      u1_s_McstCfgDiagRHEO(void);
static        U1      u1_s_McstCfgDiagMM_ECO_IND(void);
static        U1      u1_s_McstCfgDiagMM_EV_IND(void);
static        U1      u1_s_McstCfgDiagMM_REV_IND(void);
static        U1      u1_s_McstCfgDiagMM_REV_ST(void);
static        U1      u1_s_McstCfgDiagMM_REV_PK(void);
static        U1      u1_s_McstCfgDiagMM_MET_DSP(void);
static        U1      u1_s_McstCfgDiagMM_ANALOG_MET(void);
static        U1      u1_s_McstCfgDiagMM_ECO_DRV_IND(void);
static        U1      u1_s_McstCfgDiagMM_EV_IND_DSP(void);
static        U1      u1_s_McstCfgDiagMM_HV_SYS_IND(void);
static        U1      u1_s_McstCfgDiagMM_MET_DSP_7INCH(void);
static        U1      u1_s_McstCfgDiagMM_MET_DSP_LT(void);
static        U1      u1_s_McstCfgDiagMM_MET_DSP_CT(void);
static        U1      u1_s_McstCfgDiagMM_MET_DSP_RT(void);
static        U1      u1_s_McstCfgDiagMM_MET_DSP_PRESET(void);
static        U1      u1_s_McstCfgDiagMM_MET_LAYOUT(void);
static        U1      u1_s_McstCfgDiagMM_MET_DESIGN(void);
static        U1      u1_s_McstCfgDiagMM_CURCNT_LBYTE(void);
static        U1      u1_s_McstCfgDiagMM_CURCNT_HBYTE(void);
static        U1      u1_s_McstCfgDiagMM_FUEL_FLG(void);
static        U1      u1_s_McstCfgDiagMM_ELEC_FLG(void);
static        U1      u1_s_McstCfgDiagMM_POP_CROSS(void);
static        U1      u1_s_McstCfgDiagMM_POP_TEL(void);
static        U1      u1_s_McstCfgDiagMM_POP_AUDIO(void);
static        U1      u1_s_McstCfgDiagMM_POP_VOLUME(void);
static        U1      u1_s_McstCfgDiagMM_POP_VOICE(void);
static        U1      u1_s_McstCfgDiagMM_POP_TIME(void);
static        U1      u1_s_McstCfgDiagMM_POP_NOTIFY(void);
static        U1      u1_s_McstCfgDiagMM_POP_DIM(void);
static        U1      u1_s_McstCfgDiagMM_EV_DRVINF(void);
static        U1      u1_s_McstCfgDiagMM_DRVINF_CALC(void);
static        U1      u1_s_McstCfgDiagMM_DRVINF_UP(void);
static        U1      u1_s_McstCfgDiagMM_DRVINF_DN(void);
static        U1      u1_s_McstCfgDiagMM_MET_TRIP_A_UP(void);
static        U1      u1_s_McstCfgDiagMM_MET_TRIP_A_DN(void);
static        U1      u1_s_McstCfgDiagMM_MET_TRIP_B_UP(void);
static        U1      u1_s_McstCfgDiagMM_MET_TRIP_B_DN(void);
static        U1      u1_s_McstCfgDiagMM_ENG_MONI(void);
static        U1      u1_s_McstCfgDiagMM_4WD_AWD(void);
static        U1      u1_s_McstCfgRevStInit(void);
static        U4      u4_s_McstCfgRevIndInit(const U1 u1_a_id);
static        U4      u4_s_McstCfgRevPkInit(const U1 u1_a_id);
static        U4      u4_s_McstCfgTelInit(const U1 u1_a_id);
static        U4      u4_s_McstCfgAudioOpeInit(const U1 u1_a_id);
static        U4      u4_s_McstCfgVolOpeInit(const U1 u1_a_id);
static        U4      u4_s_McstCfgVrctrlInit(const U1 u1_a_id);
static        U4      u4_s_McstCfgIllumiAdjInit(const U1 u1_a_id);
static        U4      u4_s_McstCfgEcoIndInit(const U1 u1_a_id);
static        U4      u4_s_McstCfgEvIndInit(const U1 u1_a_id);
static        U4      u4_s_McstCfgHvIndInit(const U1 u1_a_id);
static        U4      u4_s_McstCfgHudInit(const U1 u1_a_id);
static        U4      u4_s_McstCfgHudAnalogInit(const U1 u1_a_id);
static        U4      u4_s_McstCfgRheoNightInit(const U1 u1_a_id);
static        U4      u4_s_McstCfgAnalogInit(const U1 u1_a_id);
static        U4      u4_s_McstCfgContentInit(const U1 u1_a_id);
static inline U1      u1_s_McstCfgCalibU1MaxChk(const U1 u1_a_CALIBID, const U1 u1_a_MAX, const U1 u1_a_DEF);
static inline U1      u1_s_McstCfgCalibU1NumChk(const U1 u1_a_CALIBID, const U1 u1_a_NUM, const U1 u1_a_DEF);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
U4              * const u4_gp_mcst_usrname[MCST_USR_NUM] = {
    vdp_PTR_NA,
    &u4_sp_mcst_user1[0],
    &u4_sp_mcst_user2[0],
    &u4_sp_mcst_user3[0]
};

U2              * const u2_gp_mcst_nickname[MCST_USR_NUM] = {
    vdp_PTR_NA,
    &u2_sp_mcst_nickname1[0],
    &u2_sp_mcst_nickname2[0],
    &u2_sp_mcst_nickname3[0]
};

const U2 u2_sp_MCST_NVMID[MCST_NUM_NVM] = {
    (U2)NVMCID_OTR_MCST_IDX_COMMON,
    (U2)NVMCID_OTR_MCST_IDX_GUEST_1,
    (U2)NVMCID_OTR_MCST_IDX_GUEST_2,
    (U2)NVMCID_OTR_MCST_IDX_GUEST_3,
    (U2)NVMCID_OTR_MCST_IDX_GUEST_4,
    (U2)NVMCID_OTR_MCST_IDX_USER1_1,
    (U2)NVMCID_OTR_MCST_IDX_USER1_2,
    (U2)NVMCID_OTR_MCST_IDX_USER1_3,
    (U2)NVMCID_OTR_MCST_IDX_USER1_4,
    (U2)NVMCID_OTR_MCST_IDX_USER2_1,
    (U2)NVMCID_OTR_MCST_IDX_USER2_2,
    (U2)NVMCID_OTR_MCST_IDX_USER2_3,
    (U2)NVMCID_OTR_MCST_IDX_USER2_4,
    (U2)NVMCID_OTR_MCST_IDX_USER3_1,
    (U2)NVMCID_OTR_MCST_IDX_USER3_2,
    (U2)NVMCID_OTR_MCST_IDX_USER3_3,
    (U2)NVMCID_OTR_MCST_IDX_USER3_4
};

const ST_MCST_BF        st_gp_MCST_BF[MCST_NUM_BF] = {
    /* u1_wid,    u1_lsb,     u4_bit    */
    {(U1)MCST_SUP_FC_IND,         (U1)0U,    (U1)28U,    (U4)0x00000003U    },    /* MCST_BFI_FC_IND                          */
    {(U1)MCST_SUP_ELE_CO_HIS,     (U1)0U,    (U1)26U,    (U4)0x00000003U    },    /* MCST_BFI_ELE_CO_HIS                      */
    {(U1)MCST_SUP_FUEL_CO_HIS,    (U1)0U,    (U1)24U,    (U4)0x00000003U    },    /* MCST_BFI_FUEL_CO_HIS                     */
    {(U1)MCST_SUP_ELE_CO_GRH,     (U1)0U,    (U1)22U,    (U4)0x00000003U    },    /* MCST_BFI_ELE_CO_GRH                      */
    {(U1)MCST_SUP_FUEL_CO_GRH,    (U1)0U,    (U1)20U,    (U4)0x00000003U    },    /* MCST_BFI_FUEL_CO_GRH                     */
    {(U1)MCST_SUP_AMBTMP,         (U1)0U,    (U1)16U,    (U4)0x00000003U    },    /* MCST_BFI_AMBTMP                          */
    {(U1)MCST_SUP_SPEED,          (U1)0U,    (U1)12U,    (U4)0x00000003U    },    /* MCST_BFI_SPEED                           */
    {(U1)MCST_SUP_DIST,           (U1)0U,    (U1)8U,     (U4)0x00000003U    },    /* MCST_BFI_DIST                            */
    {(U1)MCST_SUP_FUECO,          (U1)0U,    (U1)4U,     (U4)0x00000007U    },    /* MCST_BFI_FUECO                           */
    {(U1)MCST_SUP_ELECO,          (U1)0U,    (U1)0U,     (U4)0x00000007U    },    /* MCST_BFI_ELECO                           */
    {(U1)MCST_SUP_REV_ST,         (U1)1U,    (U1)12U,    (U4)0x0000007FU    },    /* MCST_BFI_REV_ST                          */
    {(U1)MCST_SUP_REV_LIM,        (U1)1U,    (U1)4U,     (U4)0x0000003FU    },    /* MCST_BFI_REV_LIM                         */
    {(U1)MCST_SUP_REV_IND,        (U1)1U,    (U1)2U,     (U4)0x00000003U    },    /* MCST_BFI_REV_IND                         */
    {(U1)MCST_SUP_REV_PK,         (U1)1U,    (U1)0U,     (U4)0x00000003U    },    /* MCST_BFI_REV_PK                          */
    {(U1)MCST_SUP_TRIP_A_UP,      (U1)2U,    (U1)12U,    (U4)0x00000007U    },    /* MCST_BFI_TRIP_A_UP                       */
    {(U1)MCST_SUP_TRIP_A_DN,      (U1)2U,    (U1)8U,     (U4)0x00000007U    },    /* MCST_BFI_TRIP_A_DN                       */
    {(U1)MCST_SUP_TRIP_B_UP,      (U1)2U,    (U1)4U,     (U4)0x00000007U    },    /* MCST_BFI_TRIP_B_UP                       */
    {(U1)MCST_SUP_TRIP_B_DN,      (U1)2U,    (U1)0U,     (U4)0x00000007U    },    /* MCST_BFI_TRIP_B_DN                       */
    {(U1)MCST_SUP_TAST_FLG,       (U1)3U,    (U1)16U,    (U4)0x000001FFU    },    /* MCST_BFI_TAST_FLG                        */
    {(U1)MCST_SUP_NAME_DRV1,      (U1)3U,    (U1)8U,     (U4)0x00000003U    },    /* MCST_BFI_NAME_DRV1                       */
    {(U1)MCST_SUP_NAME_DRV2,      (U1)3U,    (U1)4U,     (U4)0x00000003U    },    /* MCST_BFI_NAME_DRV2                       */
    {(U1)MCST_SUP_NAME_DRV3,      (U1)3U,    (U1)0U,     (U4)0x00000003U    },    /* MCST_BFI_NAME_DRV3                       */
    {(U1)MCST_SUP_LANG,           (U1)4U,    (U1)24U,    (U4)0x0000003FU    },    /* MCST_BFI_LANG                            */
    {(U1)MCST_SUP_WDG_EYE0,       (U1)4U,    (U1)22U,    (U4)0x00000003U    },    /* MCST_BFI_WDG_EYE0                        */
    {(U1)MCST_SUP_WDG_EYE1,       (U1)4U,    (U1)20U,    (U4)0x00000003U    },    /* MCST_BFI_WDG_EYE1                        */
    {(U1)MCST_SUP_WDG_NAVI,       (U1)4U,    (U1)18U,    (U4)0x00000003U    },    /* MCST_BFI_WDG_NAVI                        */
    {(U1)MCST_SUP_WDG_ADAS,       (U1)4U,    (U1)16U,    (U4)0x00000003U    },    /* MCST_BFI_WDG_ADAS                        */
    {(U1)MCST_SUP_WDG_ECO,        (U1)4U,    (U1)14U,    (U4)0x00000003U    },    /* MCST_BFI_WDG_ECO                         */
    {(U1)MCST_SUP_ANALOG_EYE1,    (U1)4U,    (U1)8U,     (U4)0x00000007U    },    /* MCST_BFI_ANALOG_EYE1                     */
    {(U1)MCST_SUP_ANALOG_EYE2,    (U1)4U,    (U1)4U,     (U4)0x00000007U    },    /* MCST_BFI_ANALOG_EYE2                     */
    {(U1)MCST_SUP_ANALOG,         (U1)4U,    (U1)0U,     (U4)0x00000007U    },    /* MCST_BFI_ANALOG                          */
    {(U1)MCST_SUP_AUDIO_TAB,      (U1)5U,    (U1)30U,    (U4)0x00000003U    },    /* MCST_BFI_AUDIO_TAB                       */
    {(U1)MCST_SUP_ENEMON,         (U1)5U,    (U1)28U,    (U4)0x00000003U    },    /* MCST_BFI_ENEMON                          */
    {(U1)MCST_SUP_4WD,            (U1)5U,    (U1)26U,    (U4)0x00000003U    },    /* MCST_BFI_4WD                             */
    {(U1)MCST_SUP_DRVINF_OPE,     (U1)5U,    (U1)24U,    (U4)0x00000003U    },    /* MCST_BFI_DRVINF_OPE                      */
    {(U1)MCST_SUP_DRVINF_UP,      (U1)5U,    (U1)20U,    (U4)0x00000007U    },    /* MCST_BFI_DRVINF_UP                       */
    {(U1)MCST_SUP_DRVINF_DN,      (U1)5U,    (U1)16U,    (U4)0x00000007U    },    /* MCST_BFI_DRVINF_DN                       */
    {(U1)MCST_SUP_NOW_RUN,        (U1)5U,    (U1)12U,    (U4)0x00000003U    },    /* MCST_BFI_NOW_RUN                         */
    {(U1)MCST_SUP_EV_DRINFO,      (U1)5U,    (U1)8U,     (U4)0x00000003U    },    /* MCST_BFI_EV_DRINFO                       */
    {(U1)MCST_SUP_CROSS_ADV,      (U1)6U,    (U1)30U,    (U4)0x00000003U    },    /* MCST_BFI_CROSS_ADV                       */
    {(U1)MCST_SUP_TEL,            (U1)6U,    (U1)28U,    (U4)0x00000003U    },    /* MCST_BFI_TEL                             */
    {(U1)MCST_SUP_AUDIO_OPE,      (U1)6U,    (U1)26U,    (U4)0x00000003U    },    /* MCST_BFI_AUDIO_OPE                       */
    {(U1)MCST_SUP_VOL_OPE,        (U1)6U,    (U1)24U,    (U4)0x00000003U    },    /* MCST_BFI_VOL_OPE                         */
    {(U1)MCST_SUP_VRCTRL,         (U1)6U,    (U1)22U,    (U4)0x00000003U    },    /* MCST_BFI_VRCTRL                          */
    {(U1)MCST_SUP_STS_TIM,        (U1)6U,    (U1)20U,    (U4)0x00000003U    },    /* MCST_BFI_STS_TIM                         */
    {(U1)MCST_SUP_STS_ACT,        (U1)6U,    (U1)18U,    (U4)0x00000003U    },    /* MCST_BFI_STS_ACT                         */
    {(U1)MCST_SUP_CAR_APP,        (U1)6U,    (U1)16U,    (U4)0x00000003U    },    /* MCST_BFI_CAR_APP                         */
    {(U1)MCST_SUP_ILLUMI_ADJ,     (U1)6U,    (U1)14U,    (U4)0x00000003U    },    /* MCST_BFI_ILLUMI_ADJ                      */
    {(U1)MCST_SUP_VIEW_EYE0,      (U1)7U,    (U1)30U,    (U4)0x00000003U    },    /* MCST_BFI_VIEW_EYE0                       */
    {(U1)MCST_SUP_VIEW_EYE1,      (U1)7U,    (U1)28U,    (U4)0x00000003U    },    /* MCST_BFI_VIEW_EYE1                       */
    {(U1)MCST_SUP_VIEW_EYE2,      (U1)7U,    (U1)26U,    (U4)0x00000003U    },    /* MCST_BFI_VIEW_EYE2                       */
    {(U1)MCST_SUP_VIEW_NAVI,      (U1)7U,    (U1)24U,    (U4)0x00000003U    },    /* MCST_BFI_VIEW_NAVI                       */
    {(U1)MCST_SUP_VIEW_ADAS,      (U1)7U,    (U1)22U,    (U4)0x00000003U    },    /* MCST_BFI_VIEW_ADAS                       */
    {(U1)MCST_SUP_VIEW_ECO,       (U1)7U,    (U1)20U,    (U4)0x00000003U    },    /* MCST_BFI_VIEW_ECO                        */
    {(U1)MCST_SUP_VIEW_TRACK,     (U1)7U,    (U1)18U,    (U4)0x00000003U    },    /* MCST_BFI_VIEW_TRACK                      */
    {(U1)MCST_SUP_VIEW_SHIFT,     (U1)7U,    (U1)16U,    (U4)0x00000003U    },    /* MCST_BFI_VIEW_SHIFT                      */
    {(U1)MCST_SUP_VIEW_OFFROAD,   (U1)7U,    (U1)14U,    (U4)0x00000003U    },    /* MCST_BFI_VIEW_OFFROAD                    */
    {(U1)MCST_SUP_VIEW_EYE6,      (U1)7U,    (U1)12U,    (U4)0x00000003U    },    /* MCST_BFI_VIEW_EYE6                       */
    {(U1)MCST_SUP_TACHO,          (U1)7U,    (U1)0U,     (U4)0x00000007U    },    /* MCST_BFI_TACHO                           */
    {(U1)MCST_SUP_LEFT_FU_ECO,    (U1)8U,    (U1)30U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_FU_ECO                     */
    {(U1)MCST_SUP_LEFT_EL_ECO,    (U1)8U,    (U1)28U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_EL_ECO                     */
    {(U1)MCST_SUP_LEFT_CONSUMP,   (U1)8U,    (U1)26U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_CONSUMP                    */
    {(U1)MCST_SUP_LEFT_ECO_IND,   (U1)8U,    (U1)24U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_ECO_IND                    */
    {(U1)MCST_SUP_LEFT_ECO_JDG,   (U1)8U,    (U1)22U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_ECO_JDG                    */
    {(U1)MCST_SUP_LEFT_EV_RATIO,  (U1)8U,    (U1)20U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_EV_RATIO                   */
    {(U1)MCST_SUP_LEFT_NAVI,      (U1)8U,    (U1)18U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_NAVI                       */
    {(U1)MCST_SUP_LEFT_AUDIO,     (U1)8U,    (U1)16U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_AUDIO                      */
    {(U1)MCST_SUP_LEFT_DRV_INFO,  (U1)8U,    (U1)14U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_DRV_INFO                   */
    {(U1)MCST_SUP_LEFT_TRIP_A,    (U1)8U,    (U1)12U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_TRIP_A                     */
    {(U1)MCST_SUP_LEFT_TRIP_B,    (U1)8U,    (U1)10U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_TRIP_B                     */
    {(U1)MCST_SUP_LEFT_ENE_MON,   (U1)8U,    (U1)8U,     (U4)0x00000003U    },    /* MCST_BFI_LEFT_ENE_MON                    */
    {(U1)MCST_SUP_LEFT_4WD,       (U1)8U,    (U1)6U,     (U4)0x00000003U    },    /* MCST_BFI_LEFT_4WD                        */
    {(U1)MCST_SUP_LEFT_TRAC,      (U1)8U,    (U1)4U,     (U4)0x00000003U    },    /* MCST_BFI_LEFT_TRAC                       */
    {(U1)MCST_SUP_LEFT_ANGEL,     (U1)8U,    (U1)2U,     (U4)0x00000003U    },    /* MCST_BFI_LEFT_ANGEL                      */
    {(U1)MCST_SUP_LEFT_PITCH,     (U1)8U,    (U1)0U,     (U4)0x00000003U    },    /* MCST_BFI_LEFT_PITCH                      */
    {(U1)MCST_SUP_LEFT_TR_BRAKE,  (U1)9U,    (U1)30U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_TR_BRAKE                   */
    {(U1)MCST_SUP_LEFT_TR_BSM,    (U1)9U,    (U1)28U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_TR_BSM                     */
    {(U1)MCST_SUP_LEFT_VOLT,      (U1)9U,    (U1)26U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_VOLT                       */
    {(U1)MCST_SUP_LEFT_OIL_VOLT,  (U1)9U,    (U1)24U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_OIL_VOLT                   */
    {(U1)MCST_SUP_LEFT_ENG_AT,    (U1)9U,    (U1)22U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_ENG_AT                     */
    {(U1)MCST_SUP_LEFT_ENGINE,    (U1)9U,    (U1)20U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_ENGINE                     */
    {(U1)MCST_SUP_LEFT_AT,        (U1)9U,    (U1)18U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_AT                         */
    {(U1)MCST_SUP_LEFT_TURBO,     (U1)9U,    (U1)16U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_TURBO                      */
    {(U1)MCST_SUP_LEFT_BOOST,     (U1)9U,    (U1)14U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_BOOST                      */
    {(U1)MCST_SUP_LEFT_MOTOR,     (U1)9U,    (U1)12U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_MOTOR                      */
    {(U1)MCST_SUP_LEFT_SPORTS,    (U1)9U,    (U1)10U,    (U4)0x00000003U    },    /* MCST_BFI_LEFT_SPORTS                     */
    {(U1)MCST_SUP_LEFT_G_FORCE,   (U1)9U,    (U1)8U,     (U4)0x00000003U    },    /* MCST_BFI_LEFT_G_FORCE                    */
    {(U1)MCST_SUP_LEFT_ADBLUE,    (U1)9U,    (U1)6U,     (U4)0x00000003U    },    /* MCST_BFI_LEFT_ADBLUE                     */
    {(U1)MCST_SUP_LEFT_TPMS,      (U1)9U,    (U1)4U,     (U4)0x00000003U    },    /* MCST_BFI_LEFT_TPMS                       */
    {(U1)MCST_SUP_LEFT_OILLVL,    (U1)9U,    (U1)2U,     (U4)0x00000003U    },    /* MCST_BFI_LEFT_OILLVL                     */
    {(U1)MCST_SUP_LEFT_FU_ECO_PHV,(U1)9U,    (U1)0U,     (U4)0x00000003U    },    /* MCST_BFI_LEFT_FU_ECO_PHV                 */
    {(U1)MCST_SUP_ECO_IND,        (U1)10U,   (U1)28U,    (U4)0x00000003U    },    /* MCST_BFI_ECO_IND                         */
    {(U1)MCST_SUP_EV_IND,         (U1)10U,   (U1)26U,    (U4)0x00000003U    },    /* MCST_BFI_EV_IND                          */
    {(U1)MCST_SUP_HVIND,          (U1)10U,   (U1)24U,    (U4)0x00000003U    },    /* MCST_BFI_HVIND                           */
    {(U1)MCST_SUP_MM_TIMEFMT,     (U1)10U,   (U1)20U,    (U4)0x00000003U    },    /* MCST_BFI_MM_TIMEFMT                      */
    {(U1)MCST_SUP_MM_OFFSET_TIME, (U1)10U,   (U1)0U,     (U4)0x0001FFFFU    },    /* MCST_BFI_MM_OFFSET_TIME                  */
    {(U1)MCST_SUP_RHEO_NIGHT,     (U1)12U,   (U1)27U,    (U4)0x0000001FU    },    /* MCST_BFI_RHEO_NIGHT                      */
    {(U1)MCST_SUP_HUDILL,         (U1)12U,   (U1)20U,    (U4)0x0000003FU    },    /* MCST_BFI_HUDILL                          */
    {(U1)MCST_SUP_HUD_ST,         (U1)12U,   (U1)16U,    (U4)0x00000007U    },    /* MCST_BFI_HUD_ST                          */
    {(U1)MCST_SUP_HUD,            (U1)12U,   (U1)14U,    (U4)0x00000003U    },    /* MCST_BFI_HUD                             */
    {(U1)MCST_SUP_AR,             (U1)12U,   (U1)12U,    (U4)0x00000003U    },    /* MCST_BFI_AR                              */
    {(U1)MCST_SUP_HUD_ANALOG,     (U1)12U,   (U1)9U,     (U4)0x00000007U    },    /* MCST_BFI_HUD_ANALOG                      */
    {(U1)MCST_SUP_HUD_ROT,        (U1)12U,   (U1)0U,     (U4)0x000001FFU    },    /* MCST_BFI_HUD_ROT                         */
    {(U1)MCST_SUP_DISP_VIEW,      (U1)13U,   (U1)24U,    (U4)0x0000000FU    },    /* MCST_BFI_DISP_VIEW                       */
    {(U1)MCST_SUP_DISP_EYE0,      (U1)13U,   (U1)16U,    (U4)0x0000003FU    },    /* MCST_BFI_DISP_EYE0                       */
    {(U1)MCST_SUP_DISP_EYE1,      (U1)13U,   (U1)8U,     (U4)0x0000003FU    },    /* MCST_BFI_DISP_EYE1                       */
    {(U1)MCST_SUP_DISP_EYE2,      (U1)13U,   (U1)0U,     (U4)0x0000003FU    },    /* MCST_BFI_DISP_EYE2                       */
    {(U1)MCST_SUP_DISP_MAP,       (U1)14U,   (U1)24U,    (U4)0x0000003FU    },    /* MCST_BFI_DISP_MAP                        */
    {(U1)MCST_SUP_DISP_ADAS,      (U1)14U,   (U1)16U,    (U4)0x0000003FU    },    /* MCST_BFI_DISP_ADAS                       */
    {(U1)MCST_SUP_DISP_ECO,       (U1)14U,   (U1)8U,     (U4)0x0000003FU    },    /* MCST_BFI_DISP_ECO                        */
    {(U1)MCST_SUP_DISP_TRACK,     (U1)14U,   (U1)0U,     (U4)0x0000003FU    },    /* MCST_BFI_DISP_TRACK                      */
    {(U1)MCST_SUP_DISP_SHIFT,     (U1)15U,   (U1)24U,    (U4)0x0000003FU    },    /* MCST_BFI_DISP_SHIFT                      */
    {(U1)MCST_SUP_DISP_OFFROAD,   (U1)15U,   (U1)16U,    (U4)0x0000003FU    },    /* MCST_BFI_DISP_OFFROAD                    */
    {(U1)MCST_SUP_DISP_EYE6,      (U1)15U,   (U1)8U,     (U4)0x0000003FU    },    /* MCST_BFI_DISP_EYE6                       */
    {(U1)MCST_SUP_DISP_CHARGEMODE,(U1)15U,   (U1)0U,     (U4)0x0000003FU    },    /* MCST_BFI_DISP_CHARGEMODE                 */
    {(U1)MCST_SUP_RHEO_DAY,       (U1)16U,   (U1)24U,    (U4)0x0000001FU    },    /* MCST_BFI_RHEO_DAY                        */
    {(U1)MCST_SUP_TIMEFMT,        (U1)16U,   (U1)20U,    (U4)0x00000003U    },    /* MCST_BFI_TIMEFMT                         */
    {(U1)MCST_SUP_OFFSET_TIME,    (U1)16U,   (U1)0U,     (U4)0x0001FFFFU    },    /* MCST_BFI_OFFSET_TIME                     */
    {(U1)MCST_SUP_METWRNCSTM,     (U1)17U,   (U1)28U,    (U4)0x00000007U    }     /* MCST_BFI_METWRNCSTM                      */
};

const ST_MCST_INI        st_gp_MCST_INI[MCST_NUM_BF] = {
    /* u1_id,                            u1_ini                                 */
    {(U1)MCST_BFI_FC_IND,                (U4)MCST_INI_FC_IND                     },
    {(U1)MCST_BFI_ELE_CO_HIS,            (U4)MCST_INI_ELE_CO_HIS                 },
    {(U1)MCST_BFI_FUEL_CO_HIS,           (U4)MCST_INI_FUEL_CO_HIS                },
    {(U1)MCST_BFI_ELE_CO_GRH,            (U4)MCST_INI_ELE_CO_GRH                 },
    {(U1)MCST_BFI_FUEL_CO_GRH,           (U4)MCST_INI_FUEL_CO_GRH                },
    {(U1)MCST_BFI_AMBTMP,                (U4)MCST_INI_AMBTMP                     },
    {(U1)MCST_BFI_SPEED,                 (U4)MCST_INI_SPEED                      },
    {(U1)MCST_BFI_DIST,                  (U4)MCST_INI_DIST                       },
    {(U1)MCST_BFI_FUECO,                 (U4)MCST_INI_FUECO                      },
    {(U1)MCST_BFI_ELECO,                 (U4)MCST_INI_ELECO                      },
    {(U1)MCST_BFI_REV_ST,                (U4)MCST_INI_REV_ST                     },
    {(U1)MCST_BFI_REV_LIM,               (U4)MCST_INI_REV_LIM                    },
    {(U1)MCST_BFI_REV_IND,               (U4)MCST_INI_REV_IND                    },
    {(U1)MCST_BFI_REV_PK,                (U4)MCST_INI_REV_PK                     },
    {(U1)MCST_BFI_TRIP_A_UP,             (U4)MCST_INI_TRIP_A_UP                  },
    {(U1)MCST_BFI_TRIP_A_DN,             (U4)MCST_INI_TRIP_A_DN                  },
    {(U1)MCST_BFI_TRIP_B_UP,             (U4)MCST_INI_TRIP_B_UP                  },
    {(U1)MCST_BFI_TRIP_B_DN,             (U4)MCST_INI_TRIP_B_DN                  },
    {(U1)MCST_BFI_TAST_FLG,              (U4)MCST_INI_TAST_FLG                   },
    {(U1)MCST_BFI_NAME_DRV1,             (U4)MCST_INI_NAME_DRV1                  },
    {(U1)MCST_BFI_NAME_DRV2,             (U4)MCST_INI_NAME_DRV2                  },
    {(U1)MCST_BFI_NAME_DRV3,             (U4)MCST_INI_NAME_DRV3                  },
    {(U1)MCST_BFI_LANG,                  (U4)MCST_INI_LANG                       },
    {(U1)MCST_BFI_WDG_EYE0,              (U4)MCST_INI_WDG_EYE0                   },
    {(U1)MCST_BFI_WDG_EYE1,              (U4)MCST_INI_WDG_EYE1                   },
    {(U1)MCST_BFI_WDG_NAVI,              (U4)MCST_INI_WDG_NAVI                   },
    {(U1)MCST_BFI_WDG_ADAS,              (U4)MCST_INI_WDG_ADAS                   },
    {(U1)MCST_BFI_WDG_ECO,               (U4)MCST_INI_WDG_ECO                    },
    {(U1)MCST_BFI_ANALOG_EYE1,           (U4)MCST_INI_ANALOG_EYE1                },
    {(U1)MCST_BFI_ANALOG_EYE2,           (U4)MCST_INI_ANALOG_EYE2                },
    {(U1)MCST_BFI_ANALOG,                (U4)MCST_INI_ANALOG                     },
    {(U1)MCST_BFI_AUDIO_TAB,             (U4)MCST_INI_AUDIO_TAB                  },
    {(U1)MCST_BFI_ENEMON,                (U4)MCST_INI_ENEMON                     },
    {(U1)MCST_BFI_4WD,                   (U4)MCST_INI_4WD                        },
    {(U1)MCST_BFI_DRVINF_OPE,            (U4)MCST_INI_DRVINF_OPE                 },
    {(U1)MCST_BFI_DRVINF_UP,             (U4)MCST_INI_DRVINF_UP                  },
    {(U1)MCST_BFI_DRVINF_DN,             (U4)MCST_INI_DRVINF_DN                  },
    {(U1)MCST_BFI_NOW_RUN,               (U4)MCST_INI_NOW_RUN                    },
    {(U1)MCST_BFI_EV_DRINFO,             (U4)MCST_INI_EV_DRINFO                  },
    {(U1)MCST_BFI_CROSS_ADV,             (U4)MCST_INI_CROSS_ADV                  },
    {(U1)MCST_BFI_TEL,                   (U4)MCST_INI_TEL                        },
    {(U1)MCST_BFI_AUDIO_OPE,             (U4)MCST_INI_AUDIO_OPE                  },
    {(U1)MCST_BFI_VOL_OPE,               (U4)MCST_INI_VOL_OPE                    },
    {(U1)MCST_BFI_VRCTRL,                (U4)MCST_INI_VRCTRL                     },
    {(U1)MCST_BFI_STS_TIM,               (U4)MCST_INI_STS_TIM                    },
    {(U1)MCST_BFI_STS_ACT,               (U4)MCST_INI_STS_ACT                    },
    {(U1)MCST_BFI_CAR_APP,               (U4)MCST_INI_CAR_APP                    },
    {(U1)MCST_BFI_ILLUMI_ADJ,            (U4)MCST_INI_ILLUMI_ADJ                 },
    {(U1)MCST_BFI_VIEW_EYE0,             (U4)MCST_INI_VIEW_EYE0                  },
    {(U1)MCST_BFI_VIEW_EYE1,             (U4)MCST_INI_VIEW_EYE1                  },
    {(U1)MCST_BFI_VIEW_EYE2,             (U4)MCST_INI_VIEW_EYE2                  },
    {(U1)MCST_BFI_VIEW_NAVI,             (U4)MCST_INI_VIEW_NAVI                  },
    {(U1)MCST_BFI_VIEW_ADAS,             (U4)MCST_INI_VIEW_ADAS                  },
    {(U1)MCST_BFI_VIEW_ECO,              (U4)MCST_INI_VIEW_ECO                   },
    {(U1)MCST_BFI_VIEW_TRACK,            (U4)MCST_INI_VIEW_TRACK                 },
    {(U1)MCST_BFI_VIEW_SHIFT,            (U4)MCST_INI_VIEW_SHIFT                 },
    {(U1)MCST_BFI_VIEW_OFFROAD,          (U4)MCST_INI_VIEW_OFFROAD               },
    {(U1)MCST_BFI_VIEW_EYE6,             (U4)MCST_INI_VIEW_EYE6                  },
    {(U1)MCST_BFI_TACHO,                 (U4)MCST_INI_TACHO                      },
    {(U1)MCST_BFI_LEFT_FU_ECO,           (U4)MCST_INI_LEFT_FU_ECO                },
    {(U1)MCST_BFI_LEFT_EL_ECO,           (U4)MCST_INI_LEFT_EL_ECO                },
    {(U1)MCST_BFI_LEFT_CONSUMP,          (U4)MCST_INI_LEFT_CONSUMP               },
    {(U1)MCST_BFI_LEFT_ECO_IND,          (U4)MCST_INI_LEFT_ECO_IND               },
    {(U1)MCST_BFI_LEFT_ECO_JDG,          (U4)MCST_INI_LEFT_ECO_JDG               },
    {(U1)MCST_BFI_LEFT_EV_RATIO,         (U4)MCST_INI_LEFT_EV_RATIO              },
    {(U1)MCST_BFI_LEFT_NAVI,             (U4)MCST_INI_LEFT_NAVI                  },
    {(U1)MCST_BFI_LEFT_AUDIO,            (U4)MCST_INI_LEFT_AUDIO                 },
    {(U1)MCST_BFI_LEFT_DRV_INFO,         (U4)MCST_INI_LEFT_DRV_INFO              },
    {(U1)MCST_BFI_LEFT_TRIP_A,           (U4)MCST_INI_LEFT_TRIP_A                },
    {(U1)MCST_BFI_LEFT_TRIP_B,           (U4)MCST_INI_LEFT_TRIP_B                },
    {(U1)MCST_BFI_LEFT_ENE_MON,          (U4)MCST_INI_LEFT_ENE_MON               },
    {(U1)MCST_BFI_LEFT_4WD,              (U4)MCST_INI_LEFT_4WD                   },
    {(U1)MCST_BFI_LEFT_TRAC,             (U4)MCST_INI_LEFT_TRAC                  },
    {(U1)MCST_BFI_LEFT_ANGEL,            (U4)MCST_INI_LEFT_ANGEL                 },
    {(U1)MCST_BFI_LEFT_PITCH,            (U4)MCST_INI_LEFT_PITCH                 },
    {(U1)MCST_BFI_LEFT_TR_BRAKE,         (U4)MCST_INI_LEFT_TR_BRAKE              },
    {(U1)MCST_BFI_LEFT_TR_BSM,           (U4)MCST_INI_LEFT_TR_BSM                },
    {(U1)MCST_BFI_LEFT_VOLT,             (U4)MCST_INI_LEFT_VOLT                  },
    {(U1)MCST_BFI_LEFT_OIL_VOLT,         (U4)MCST_INI_LEFT_OIL_VOLT              },
    {(U1)MCST_BFI_LEFT_ENG_AT,           (U4)MCST_INI_LEFT_ENG_AT                },
    {(U1)MCST_BFI_LEFT_ENGINE,           (U4)MCST_INI_LEFT_ENGINE                },
    {(U1)MCST_BFI_LEFT_AT,               (U4)MCST_INI_LEFT_AT                    },
    {(U1)MCST_BFI_LEFT_TURBO,            (U4)MCST_INI_LEFT_TURBO                 },
    {(U1)MCST_BFI_LEFT_BOOST,            (U4)MCST_INI_LEFT_BOOST                 },
    {(U1)MCST_BFI_LEFT_MOTOR,            (U4)MCST_INI_LEFT_MOTOR                 },
    {(U1)MCST_BFI_LEFT_SPORTS,           (U4)MCST_INI_LEFT_SPORTS                },
    {(U1)MCST_BFI_LEFT_G_FORCE,          (U4)MCST_INI_LEFT_G_FORCE               },
    {(U1)MCST_BFI_LEFT_ADBLUE,           (U4)MCST_INI_LEFT_ADBLUE                },
    {(U1)MCST_BFI_LEFT_TPMS,             (U4)MCST_INI_LEFT_TPMS                  },
    {(U1)MCST_BFI_LEFT_OILLVL,           (U4)MCST_INI_LEFT_OILLVL                },
    {(U1)MCST_BFI_LEFT_FU_ECO_PHV,       (U4)MCST_INI_LEFT_FU_ECO_PHV            },
    {(U1)MCST_BFI_ECO_IND,               (U4)MCST_INI_ECO_IND                    },
    {(U1)MCST_BFI_EV_IND,                (U4)MCST_INI_EV_IND                     },
    {(U1)MCST_BFI_HVIND,                 (U4)MCST_INI_HVIND                      },
    {(U1)MCST_BFI_MM_TIMEFMT,            (U4)MCST_INI_MM_TIMEFMT                 },
    {(U1)MCST_BFI_MM_OFFSET_TIME,        (U4)MCST_INI_MM_OFFSET_TIME             },
    {(U1)MCST_BFI_RHEO_NIGHT,            (U4)MCST_INI_RHEO_NIGHT                 },
    {(U1)MCST_BFI_HUDILL,                (U4)MCST_INI_HUDILL                     },
    {(U1)MCST_BFI_HUD_ST,                (U4)MCST_INI_HUD_ST                     },
    {(U1)MCST_BFI_HUD,                   (U4)MCST_INI_HUD                        },
    {(U1)MCST_BFI_AR,                    (U4)MCST_INI_AR                         },
    {(U1)MCST_BFI_HUD_ANALOG,            (U4)MCST_INI_HUD_ANALOG                 },
    {(U1)MCST_BFI_HUD_ROT,               (U4)MCST_INI_HUD_ROT                    },
    {(U1)MCST_BFI_DISP_VIEW,             (U4)MCST_INI_DISP_VIEW                  },
    {(U1)MCST_BFI_DISP_EYE0,             (U4)MCST_INI_DISP_EYE0                  },
    {(U1)MCST_BFI_DISP_EYE1,             (U4)MCST_INI_DISP_EYE1                  },
    {(U1)MCST_BFI_DISP_EYE2,             (U4)MCST_INI_DISP_EYE2                  },
    {(U1)MCST_BFI_DISP_MAP,              (U4)MCST_INI_DISP_MAP                   },
    {(U1)MCST_BFI_DISP_ADAS,             (U4)MCST_INI_DISP_ADAS                  },
    {(U1)MCST_BFI_DISP_ECO,              (U4)MCST_INI_DISP_ECO                   },
    {(U1)MCST_BFI_DISP_TRACK,            (U4)MCST_INI_DISP_TRACK                 },
    {(U1)MCST_BFI_DISP_SHIFT,            (U4)MCST_INI_DISP_SHIFT                 },
    {(U1)MCST_BFI_DISP_OFFROAD,          (U4)MCST_INI_DISP_OFFROAD               },
    {(U1)MCST_BFI_DISP_EYE6,             (U4)MCST_INI_DISP_EYE6                  },
    {(U1)MCST_BFI_DISP_CHARGEMODE,       (U4)MCST_INI_DISP_CHARGEMODE            },
    {(U1)MCST_BFI_RHEO_DAY,              (U4)MCST_INI_RHEO_DAY                   },
    {(U1)MCST_BFI_TIMEFMT,               (U4)MCST_INI_TIMEFMT                    },
    {(U1)MCST_BFI_OFFSET_TIME,           (U4)MCST_INI_OFFSET_TIME                },
    {(U1)MCST_BFI_METWRNCSTM,            (U4)MCST_INI_METWRNCSTM                 }
};

const ST_MCST_OFFSET st_gp_MCST_OFFSET[MCST_USR_NUM] =
{
    /* u1_offset                   u1_offset_ini,                  u1_offset_max             */
    {(U1)MCST_BF_OFFSET_GUEST,    (U1)MCST_BF_OFFSET_GUEST_INI,   (U1)MCST_BF_OFFSET_GUEST_MAX},
    {(U1)MCST_BF_OFFSET_USER1,    (U1)MCST_BF_OFFSET_USER1_INI,   (U1)MCST_BF_OFFSET_USER1_MAX},
    {(U1)MCST_BF_OFFSET_USER2,    (U1)MCST_BF_OFFSET_USER2_INI,   (U1)MCST_BF_OFFSET_USER2_MAX},
    {(U1)MCST_BF_OFFSET_USER3,    (U1)MCST_BF_OFFSET_USER3_INI,   (U1)MCST_BF_OFFSET_USER3_MAX}
};

const U1 u1_gp_MCST_PSUND_TABLE[MCST_PSUND_NUM] =
{
    (U1)MCST_USR_UNKNOWN,
    (U1)MCST_USR_USER1,
    (U1)MCST_USR_USER2,
    (U1)MCST_USR_USER3,
    (U1)MCST_USR_UNKNOWN,
    (U1)MCST_USR_UNKNOWN,
    (U1)MCST_USR_UNKNOWN,
    (U1)MCST_USR_GUEST
};

const U1 u1_gp_MCST_PSEU_TABLE[MCST_PSEU_NUM] =
{
    (U1)MCST_USR_NON,
    (U1)MCST_USR_USER1,
    (U1)MCST_USR_USER2,
    (U1)MCST_USR_USER3,
    (U1)MCST_USR_NON,
    (U1)MCST_USR_NON,
    (U1)MCST_USR_NON,
    (U1)MCST_USR_GUEST
};

static const U2 u2_sp_MCST_NAME_RIMID_USER1[MCST_USRDAT_NUM] =
{
    (U2)RIMID_U4_MCST_NAME_UPDTNUM_USER1,
    (U2)RIMID_U4_MCST_NAME_USER1_01,
    (U2)RIMID_U4_MCST_NAME_USER1_02,
    (U2)RIMID_U4_MCST_NAME_USER1_03,
    (U2)RIMID_U4_MCST_NAME_USER1_04,
    (U2)RIMID_U4_MCST_NAME_USER1_05,
    (U2)RIMID_U4_MCST_NAME_USER1_06,
    (U2)RIMID_U4_MCST_NAME_USER1_07,
    (U2)RIMID_U4_MCST_NAME_USER1_08,
    (U2)RIMID_U4_MCST_NAME_USER1_09,
    (U2)RIMID_U4_MCST_NAME_USER1_10,
    (U2)RIMID_U4_MCST_NAME_USER1_11,
    (U2)RIMID_U4_MCST_NAME_USER1_12,
    (U2)RIMID_U4_MCST_NAME_USER1_13,
    (U2)RIMID_U4_MCST_NAME_USER1_14,
    (U2)RIMID_U4_MCST_NAME_USER1_15
};

static const U2 u2_sp_MCST_NAME_RIMID_USER2[MCST_USRDAT_NUM] =
{
    (U2)RIMID_U4_MCST_NAME_UPDTNUM_USER2,
    (U2)RIMID_U4_MCST_NAME_USER2_01,
    (U2)RIMID_U4_MCST_NAME_USER2_02,
    (U2)RIMID_U4_MCST_NAME_USER2_03,
    (U2)RIMID_U4_MCST_NAME_USER2_04,
    (U2)RIMID_U4_MCST_NAME_USER2_05,
    (U2)RIMID_U4_MCST_NAME_USER2_06,
    (U2)RIMID_U4_MCST_NAME_USER2_07,
    (U2)RIMID_U4_MCST_NAME_USER2_08,
    (U2)RIMID_U4_MCST_NAME_USER2_09,
    (U2)RIMID_U4_MCST_NAME_USER2_10,
    (U2)RIMID_U4_MCST_NAME_USER2_11,
    (U2)RIMID_U4_MCST_NAME_USER2_12,
    (U2)RIMID_U4_MCST_NAME_USER2_13,
    (U2)RIMID_U4_MCST_NAME_USER2_14,
    (U2)RIMID_U4_MCST_NAME_USER2_15
};

static const U2 u2_sp_MCST_NAME_RIMID_USER3[MCST_USRDAT_NUM] =
{
    (U2)RIMID_U4_MCST_NAME_UPDTNUM_USER3,
    (U2)RIMID_U4_MCST_NAME_USER3_01,
    (U2)RIMID_U4_MCST_NAME_USER3_02,
    (U2)RIMID_U4_MCST_NAME_USER3_03,
    (U2)RIMID_U4_MCST_NAME_USER3_04,
    (U2)RIMID_U4_MCST_NAME_USER3_05,
    (U2)RIMID_U4_MCST_NAME_USER3_06,
    (U2)RIMID_U4_MCST_NAME_USER3_07,
    (U2)RIMID_U4_MCST_NAME_USER3_08,
    (U2)RIMID_U4_MCST_NAME_USER3_09,
    (U2)RIMID_U4_MCST_NAME_USER3_10,
    (U2)RIMID_U4_MCST_NAME_USER3_11,
    (U2)RIMID_U4_MCST_NAME_USER3_12,
    (U2)RIMID_U4_MCST_NAME_USER3_13,
    (U2)RIMID_U4_MCST_NAME_USER3_14,
    (U2)RIMID_U4_MCST_NAME_USER3_15
};

const U2 * const u2_gp2_MCST_USRNAME_DAT[MCST_USR_NUM]  = {
    vdp_PTR_NA,
    &u2_sp_MCST_NAME_RIMID_USER1[0],
    &u2_sp_MCST_NAME_RIMID_USER2[0],
    &u2_sp_MCST_NAME_RIMID_USER3[0]
};

U1 ( * const fp_gp_u1_MCST_GETFUNC[MCST_FUNC_NUM])(void) = {
    &u1_s_McstCfgJdg_L_HUD_FUNC,
    &u1_s_McstCfgJdg_L_AR_FUNC,
    &u1_s_McstCfgJdg_L_MET_TYFN,
    &u1_s_McstCfgJdg_L_TACHO_FUNC,
    &u1_s_McstCfgJdg_L_RHEOF,
    &u1_s_McstCfgJdg_L_CONT_FUNC,
    &u1_s_McstCfgJdg_L_ECO_FUNC,
    &u1_s_McstCfgJdg_L_EV_FUNC,
    &u1_s_McstCfgJdg_L_REV_FUNC,
    &u1_s_McstCfgJdg_L_RV_PK_F,
    &u1_s_McstCfgJdg_L_MANTE,
    &u1_s_McstCfgJdg_L_OMAINTE,
    &u1_s_McstCfgJdg_L_VS_FUNC,
    &u1_s_McstCfgJdg_L_STSWLHCSTM1,
    &u1_s_McstCfgJdg_L_STSWLHCSTM2,
    &u1_s_McstCfgJdg_L_STSWRHCSTM1,
    &u1_s_McstCfgJdg_L_STSWRHCSTM2,
    &u1_s_McstCfgJdg_L_STSWRHCSTM3,
    &u1_s_McstCfgJdg_L_STSWLH,
    &u1_s_McstCfgJdg_L_STSWRH,
    &u1_s_McstCfgJdg_L_STSW_FUNC,
    &u1_s_McstCfgJdg_L_GRV_FUNC,
    &u1_s_McstCfgJdg_L_MET_TSTFN
};

U1 ( * const fp_gp_u1_MCST_GETDIAG[MCST_DIAG_NUM])(void) = {
    &u1_s_McstCfgDiagHUD,
    &u1_s_McstCfgDiagHUD_ILL,
    &u1_s_McstCfgDiagHUD_ST,
    &u1_s_McstCfgDiagMM_MET_TYP,
    &u1_s_McstCfgDiagMM_TACHO,
    &u1_s_McstCfgDiagRHEO,
    &u1_s_McstCfgDiagMM_ECO_IND,
    &u1_s_McstCfgDiagMM_EV_IND,
    &u1_s_McstCfgDiagMM_REV_IND,
    &u1_s_McstCfgDiagMM_REV_ST,
    &u1_s_McstCfgDiagMM_REV_PK,
    &u1_s_McstCfgDiagMM_MET_DSP,
    &u1_s_McstCfgDiagMM_ANALOG_MET,
    &u1_s_McstCfgDiagMM_ECO_DRV_IND,
    &u1_s_McstCfgDiagMM_EV_IND_DSP,
    &u1_s_McstCfgDiagMM_HV_SYS_IND,
    &u1_s_McstCfgDiagMM_MET_DSP_7INCH,
    &u1_s_McstCfgDiagMM_MET_DSP_LT,
    &u1_s_McstCfgDiagMM_MET_DSP_CT,
    &u1_s_McstCfgDiagMM_MET_DSP_RT,
    &u1_s_McstCfgDiagMM_MET_DSP_PRESET,
    &u1_s_McstCfgDiagMM_MET_LAYOUT,
    &u1_s_McstCfgDiagMM_MET_DESIGN,
    &u1_s_McstCfgDiagMM_CURCNT_LBYTE,
    &u1_s_McstCfgDiagMM_CURCNT_HBYTE,
    &u1_s_McstCfgDiagMM_FUEL_FLG,
    &u1_s_McstCfgDiagMM_ELEC_FLG,
    &u1_s_McstCfgDiagMM_POP_CROSS,
    &u1_s_McstCfgDiagMM_POP_TEL,
    &u1_s_McstCfgDiagMM_POP_AUDIO,
    &u1_s_McstCfgDiagMM_POP_VOLUME,
    &u1_s_McstCfgDiagMM_POP_VOICE,
    &u1_s_McstCfgDiagMM_POP_TIME,
    &u1_s_McstCfgDiagMM_POP_NOTIFY,
    &u1_s_McstCfgDiagMM_POP_DIM,
    &u1_s_McstCfgDiagMM_EV_DRVINF,
    &u1_s_McstCfgDiagMM_DRVINF_CALC,
    &u1_s_McstCfgDiagMM_DRVINF_UP,
    &u1_s_McstCfgDiagMM_DRVINF_DN,
    &u1_s_McstCfgDiagMM_MET_TRIP_A_UP,
    &u1_s_McstCfgDiagMM_MET_TRIP_A_DN,
    &u1_s_McstCfgDiagMM_MET_TRIP_B_UP,
    &u1_s_McstCfgDiagMM_MET_TRIP_B_DN,
    &u1_s_McstCfgDiagMM_ENG_MONI,
    &u1_s_McstCfgDiagMM_4WD_AWD
};

const U1 u1_gp_MCST_PSEU_CHG_TABLE[MCST_PSEU_NUM][MCST_PSEU_NUM] = {
    /* NON(INIT)       USER1          USER2         USER3       Do Nothing     Do Nothing      Do Nothing      GUEST         */
    { (U1)FALSE,      (U1)TRUE,     (U1)TRUE,     (U1)TRUE,     (U1)FALSE,     (U1)FALSE,     (U1)FALSE,     (U1)TRUE       }, /* NON(INIT)  */
    { (U1)FALSE,      (U1)FALSE,    (U1)TRUE,     (U1)TRUE,     (U1)FALSE,     (U1)FALSE,     (U1)FALSE,     (U1)TRUE       }, /* USER1      */
    { (U1)FALSE,      (U1)TRUE,     (U1)FALSE,    (U1)TRUE,     (U1)FALSE,     (U1)FALSE,     (U1)FALSE,     (U1)TRUE       }, /* USER2      */
    { (U1)FALSE,      (U1)TRUE,     (U1)TRUE,     (U1)FALSE,    (U1)FALSE,     (U1)FALSE,     (U1)FALSE,     (U1)TRUE       }, /* USER3      */
    { (U1)FALSE,      (U1)TRUE,     (U1)TRUE,     (U1)TRUE,     (U1)FALSE,     (U1)FALSE,     (U1)FALSE,     (U1)TRUE       }, /* Do Nothing */
    { (U1)FALSE,      (U1)TRUE,     (U1)TRUE,     (U1)TRUE,     (U1)FALSE,     (U1)FALSE,     (U1)FALSE,     (U1)TRUE       }, /* Do Nothing */
    { (U1)FALSE,      (U1)TRUE,     (U1)TRUE,     (U1)TRUE,     (U1)FALSE,     (U1)FALSE,     (U1)FALSE,     (U1)TRUE       }, /* Do Nothing */
    { (U1)FALSE,      (U1)TRUE,     (U1)TRUE,     (U1)TRUE,     (U1)FALSE,     (U1)FALSE,     (U1)FALSE,     (U1)FALSE      }  /* GUEST      */
};

static const U2 u2_sp_MCST_NAME_NVMCID_USER1[MCST_NICKNAME_NUM] =
{
    (U2)NVMCID_U2_MCST_NAME_USER1_1,
    (U2)NVMCID_U2_MCST_NAME_USER1_2,
    (U2)NVMCID_U2_MCST_NAME_USER1_3,
    (U2)NVMCID_U2_MCST_NAME_USER1_4,
    (U2)NVMCID_U2_MCST_NAME_USER1_5,
    (U2)NVMCID_U2_MCST_NAME_USER1_6,
    (U2)NVMCID_U2_MCST_NAME_USER1_7,
    (U2)NVMCID_U2_MCST_NAME_USER1_8,
    (U2)NVMCID_U2_MCST_NAME_USER1_9,
    (U2)NVMCID_U2_MCST_NAME_USER1_10
};

static const U2 u2_sp_MCST_NAME_NVMCID_USER2[MCST_NICKNAME_NUM] =
{
    (U2)NVMCID_U2_MCST_NAME_USER2_1,
    (U2)NVMCID_U2_MCST_NAME_USER2_2,
    (U2)NVMCID_U2_MCST_NAME_USER2_3,
    (U2)NVMCID_U2_MCST_NAME_USER2_4,
    (U2)NVMCID_U2_MCST_NAME_USER2_5,
    (U2)NVMCID_U2_MCST_NAME_USER2_6,
    (U2)NVMCID_U2_MCST_NAME_USER2_7,
    (U2)NVMCID_U2_MCST_NAME_USER2_8,
    (U2)NVMCID_U2_MCST_NAME_USER2_9,
    (U2)NVMCID_U2_MCST_NAME_USER2_10
};

static const U2 u2_sp_MCST_NAME_NVMCID_USER3[MCST_NICKNAME_NUM] =
{
    (U2)NVMCID_U2_MCST_NAME_USER3_1,
    (U2)NVMCID_U2_MCST_NAME_USER3_2,
    (U2)NVMCID_U2_MCST_NAME_USER3_3,
    (U2)NVMCID_U2_MCST_NAME_USER3_4,
    (U2)NVMCID_U2_MCST_NAME_USER3_5,
    (U2)NVMCID_U2_MCST_NAME_USER3_6,
    (U2)NVMCID_U2_MCST_NAME_USER3_7,
    (U2)NVMCID_U2_MCST_NAME_USER3_8,
    (U2)NVMCID_U2_MCST_NAME_USER3_9,
    (U2)NVMCID_U2_MCST_NAME_USER3_10
};

const U2 * const u2_gp2_MCST_NICKNAME_NVMCID[MCST_USR_NUM]  = {
    vdp_PTR_NA,
    &u2_sp_MCST_NAME_NVMCID_USER1[0],
    &u2_sp_MCST_NAME_NVMCID_USER2[0],
    &u2_sp_MCST_NAME_NVMCID_USER3[0]
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1                u1_g_MCST_NWORD               = (U1)MCST_NUM_WORD;
const U1                u1_g_MCST_NUM_WORD_COMMON     = (U1)MCST_NUM_WORD_COMMON;
const U1                u1_g_MCST_NUM_WORD_USER       = (U1)MCST_NUM_WORD_USER;
const U1                u1_g_MCST_NUM_BF              = (U1)MCST_NUM_BF;
const U1                u1_g_MCST_FUNC_NUM            = (U1)MCST_FUNC_NUM;
const U1                u1_g_MCST_USRDAT_NUM          = (U1)MCST_USRDAT_NUM;
const U1                u1_g_MCST_USR_NUM             = (U1)MCST_USR_NUM;
const U1                u1_g_MCST_OFFSET_GUEST_INI    = (U1)MCST_BF_OFFSET_GUEST_INI;
const U1                u1_g_MCST_OFFSET_GUEST_MAX    = (U1)MCST_BF_OFFSET_GUEST_MAX;
const U2                u2_g_MCST_RES_TOUT            = (U2)5000U / (U2)MCST_MAIN_TICK;
const U2                u2_g_MCST_RIMID_USER          = (U2)RIMID_U1_MCST_USRNUM_D;
const U1                u1_g_MCST_BFI_REV_ST          = (U1)MCST_BFI_REV_ST;
const U1                u1_g_MCST_BFI_HUD             = (U1)MCST_BFI_HUD;
const U1                u1_g_MCST_REV_ST_MIN          = (U1)MCST_REV_ST_MIN;
const U1                u1_g_MCST_NICKNAME_NUM        = (U1)MCST_NICKNAME_NUM;
const U1                u1_g_MCST_BFI_NAME_DRV1       = (U1)MCST_BFI_NAME_DRV1;
const U1                u1_g_MCST_BFI_NAME_DRV2       = (U1)MCST_BFI_NAME_DRV2;
const U1                u1_g_MCST_BFI_NAME_DRV3       = (U1)MCST_BFI_NAME_DRV3;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_McstCfgEsichk(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_McstCfgEsichk(void)
{
#ifdef ES_INSPECT_H

#if ((ES_INSPECT_MDBF_NUO_DI != MCST_ESI_NUO_DI) || \
     (ES_INSPECT_MDBF_SI_ACT != MCST_ESI_SI_ACT))
#error "mcst_cfg.c : MCST_ESI_XXX shall be equal to ES_INSPECT_MDBF_XXX."
#endif
#if 0   /* BEV BSW provisionally */
    return(u1_g_ESInspectMdBfield());
#else
    return((U1)0U);
#endif
#else
    return((U1)0U);
#endif /* #ifdef ES_INSPECT_H */
}

/*===================================================================================================================================*/
/* U1    u1_g_McstRcvSgnlPSUN_D(U1 * u1p_a_sgnl)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_McstCfgRcvSgnlPSUN_D(U1 * u1p_a_sgnl)
{
    U1  u1_t_sts;

#if defined(MSG_BDB1S27_RXCH0) && defined(ComConf_ComSignal_PSUN_D)
    u1_t_sts = (U1)Com_GetIPDUStatus(MSG_BDB1S27_RXCH0);
    u1_t_sts &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    (void)Com_ReceiveSignal(ComConf_ComSignal_PSUN_D, u1p_a_sgnl);
#else
    u1_t_sts   = (U1)COM_NO_RX;
    *u1p_a_sgnl = (U1)0U;
#endif

    return(u1_t_sts);
}

/*===================================================================================================================================*/
/* U1    u1_g_McstRcvSgnlPSER(U1 * u1p_a_sgnl)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_McstCfgRcvSgnlPSER(U1 * u1p_a_sgnl)
{
    U1  u1_t_sts;
#if defined(MSG_BDB1S28_RXCH0) && defined(ComConf_ComSignal_PSER)
    u1_t_sts = (U1)Com_GetIPDUStatus(MSG_BDB1S28_RXCH0);
    u1_t_sts &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    (void)Com_ReceiveSignal(ComConf_ComSignal_PSER, u1p_a_sgnl);
#else
    u1_t_sts   = (U1)COM_NO_RX;
    *u1p_a_sgnl = (U1)0U;
#endif

    return(u1_t_sts);
}

/*===================================================================================================================================*/
/* U1    u1_g_McstRcvSgnlPSEU(U1 * u1p_a_sgnl)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_McstCfgRcvSgnlPSEU(U1 * u1p_a_sgnl)
{
    U1  u1_t_sts;

#if defined(MSG_BDB1S28_RXCH0) && defined(ComConf_ComSignal_PSEU)
    u1_t_sts = (U1)Com_GetIPDUStatus(MSG_BDB1S28_RXCH0);
    u1_t_sts &= ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    (void)Com_ReceiveSignal(ComConf_ComSignal_PSEU, u1p_a_sgnl);
#else
    u1_t_sts   = (U1)COM_NO_RX;
    *u1p_a_sgnl = (U1)0U;
#endif

    return(u1_t_sts);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_HUD_FUNC(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_HUD_FUNC(void)
{
    U1  u1_t_result;
    U1  u1_t_gvif;

    u1_t_gvif = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_GVIF2);
    if(u1_t_gvif == (U1)TRUE){
        u1_t_result = (U1)TRUE;     /* With drawing function HUD */
    }
    else{
        u1_t_result = (U1)FALSE;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_AR_FUNC(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_AR_FUNC(void)
{
    U1  u1_t_result;

    u1_t_result = (U1)FALSE;     /* 800B Not Applicable */

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_MET_TYFN(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_MET_TYFN(void)
{
    U1  u1_t_result;

    u1_t_result = (U1)TRUE;     /* 800B Applicable */

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_TACHO_FUNC(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_TACHO_FUNC(void)
{
#if 0  /* @@@ u1_g_VardefPtsByPid() is not applied. @@@ */
    U1  u1_t_result;
    U1  u1_t_pwrtrn;

    u1_t_pwrtrn = u1_g_VardefPtsByPid();

    if((u1_t_pwrtrn == (U1)VDF_PTS_HV ) ||
       (u1_t_pwrtrn == (U1)VDF_PTS_PHV)){
        u1_t_result = (U1)TRUE;
    }
    else{
        u1_t_result = (U1)FALSE;
    }

    return(u1_t_result);
#endif
    return((U1)FALSE);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_RHEOF(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_RHEOF(void)
{
    U1  u1_t_result;

    u1_t_result = (U1)FALSE;     /* 800B Not Applicable */

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_CONT_FUNC(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_CONT_FUNC(void)
{
    U1  u1_t_result;
    U1  u1_t_aismm;
    U1  u1_t_aiseth;
    U1  u1_t_stsw;

    u1_t_aismm = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_AISMM);
    u1_t_aiseth = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_AISETH);
    u1_t_stsw  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXMPS1S01);

    if(((u1_t_aismm == (U1)TRUE) ||
       (u1_t_aiseth == (U1)TRUE)) &&
       (u1_t_stsw  == (U1)TRUE)){
        u1_t_result = (U1)TRUE;
    }
    else{
        u1_t_result = (U1)FALSE;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_ECO_FUNC(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_ECO_FUNC(void)
{
#if 0  /* @@@ u1_g_VardefPtsByPid() is not applied. @@@ */
    U1  u1_t_result;
    U1  u1_t_pwrtrn;

    u1_t_pwrtrn = u1_g_VardefPtsByPid();

    if(u1_t_pwrtrn == (U1)VDF_PTS_CONV){
        u1_t_result = (U1)TRUE;
    }
    else{
        u1_t_result = (U1)FALSE;
    }

    return(u1_t_result);
#endif
    return((U1)FALSE);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_EV_FUNC(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_EV_FUNC(void)
{
#if 0  /* @@@ u1_g_VardefPtsByPid() is not applied. @@@ */
    U1  u1_t_result;
    U1  u1_t_pwrtrn;

    u1_t_pwrtrn = u1_g_VardefPtsByPid();

    if((u1_t_pwrtrn == (U1)VDF_PTS_HV ) ||
       (u1_t_pwrtrn == (U1)VDF_PTS_PHV)){
        u1_t_result = (U1)TRUE;
    }
    else{
        u1_t_result = (U1)FALSE;
    }

    return(u1_t_result);
#endif
    return((U1)FALSE);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_REV_FUNC(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_REV_FUNC(void)
{
#if 0
    U1  u1_t_result;
    U1  u1_t_grade;

    u1_t_grade = (U1)u4_g_VardefGrade();

    if(u1_t_grade == (U1)VDF_GRADE_F_SPO){
        u1_t_result = (U1)TRUE;
    }
    else{
        u1_t_result = (U1)FALSE;
    }

    return(u1_t_result);
#endif
    return((U1)FALSE);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_RV_PK_F(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_RV_PK_F(void)
{
#if 0
    U1  u1_t_result;
    U1  u1_t_grade;

    u1_t_grade = (U1)u4_g_VardefGrade();

    if(u1_t_grade == (U1)VDF_GRADE_F_SPO){
        u1_t_result = (U1)TRUE;
    }
    else{
        u1_t_result = (U1)FALSE;
    }

    return(u1_t_result);
#endif
    return((U1)FALSE);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_MANTE(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_MANTE(void)
{
    U1  u1_t_result;
    U1  u1_t_mainte;

    u1_t_mainte = u1_g_VardefTmntOpt();

    if(u1_t_mainte == (U1)TRUE){
        u1_t_result = (U1)TRUE;
    }
    else{
        u1_t_result = (U1)FALSE;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_OMAINTE(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_OMAINTE(void)
{
    U1  u1_t_result;
    U1  u1_t_omainte;

    u1_t_omainte = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_OILMNT);

    if(u1_t_omainte == (U1)TRUE){
        u1_t_result = (U1)TRUE;
    }
    else{
        u1_t_result = (U1)FALSE;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_VS_FUNC(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_VS_FUNC(void)
{
    U1  u1_t_result;
    U1  u1_t_aismm;
    U1  u1_t_aiseth;
    U1  u1_t_stsw;

    u1_t_aismm = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_AISMM);
    u1_t_aiseth = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_AISETH);
    u1_t_stsw  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_CXMPS1S01);

    if((u1_t_aismm == (U1)TRUE) ||
       (u1_t_aiseth == (U1)TRUE) ||
       (u1_t_stsw  == (U1)TRUE)){
        u1_t_result = (U1)TRUE;
    }
    else{
        u1_t_result = (U1)FALSE;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_STSWLHCSTM1(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_STSWLHCSTM1(void)
{
    static const ST_MCST_FUNC      st_sp_MCST_L_STSWLHCSTM1_FUNC[MCST_STSW_FUNC_NUM] = {
        {(U1)TRUE ,   (U2)U2_MAX      },         /*  Empty       */
        {(U1)TRUE ,   (U2)U2_MAX      },         /*  AUDIO_MODE  */
        {(U1)TRUE ,   (U2)U2_MAX      },         /*  AUDIO_PWR   */
        {(U1)TRUE ,   (U2)U2_MAX      },         /*  SEEK/TRACK  */
        {(U1)TRUE ,   (U2)U2_MAX      },         /*  A/C TEMP    */
        {(U1)TRUE ,   (U2)U2_MAX      },         /*  A/C FLOW    */
        {(U1)TRUE ,   (U2)U2_MAX      },         /*  A/C INOUT   */
        {(U1)TRUE ,   (U2)U2_MAX      }          /*  A/C OUTLET  */
    };

    U1  u1_t_result;
    U1  u1_t_func;
    U2  u2_t_id;
    U4  u4_t_loop;

    u1_t_result = (U1)0U;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)MCST_STSW_FUNC_NUM ; u4_t_loop++){

        u1_t_func   = st_sp_MCST_L_STSWLHCSTM1_FUNC[u4_t_loop].u1_func;
        u2_t_id     = st_sp_MCST_L_STSWLHCSTM1_FUNC[u4_t_loop].u2_esopt_id;

        if(u1_t_func == (U1)U1_MAX){
            u1_t_func = u1_g_VardefEsOptAvaByCh(u2_t_id);
        }

        u1_t_result |= (U1)(u1_t_func << u4_t_loop);
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_STSWLHCSTM2(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_STSWLHCSTM2(void)
{
    static const ST_MCST_FUNC     st_sp_MCST_L_STSWLHCSTM2_FUNC[MCST_STSW_FUNC_NUM] = {
        {(U1)FALSE ,  (U2)U2_MAX     },        /*  Undefined   */
        {(U1)TRUE  ,  (U2)U2_MAX     },        /*  A/C AUTO    */
        {(U1)TRUE  ,  (U2)U2_MAX     },        /*  A/C OFF     */
        {(U1)TRUE  ,  (U2)U2_MAX     },        /*  A/C A/C     */
        {(U1)FALSE ,  (U2)U2_MAX     },        /*  Undefined   */
        {(U1)FALSE ,  (U2)U2_MAX     },        /*  Undefined   */
        {(U1)FALSE ,  (U2)U2_MAX     },        /*  Undefined   */
        {(U1)FALSE ,  (U2)U2_MAX     }         /*  Undefined   */
    };

    U1  u1_t_result;
    U1  u1_t_func;
    U2  u2_t_id;
    U4  u4_t_loop;

    u1_t_result = (U1)0U;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)MCST_STSW_FUNC_NUM ; u4_t_loop++){

        u1_t_func   = st_sp_MCST_L_STSWLHCSTM2_FUNC[u4_t_loop].u1_func;
        u2_t_id     = st_sp_MCST_L_STSWLHCSTM2_FUNC[u4_t_loop].u2_esopt_id;

        if(u1_t_func == (U1)U1_MAX){
            u1_t_func = u1_g_VardefEsOptAvaByCh(u2_t_id);
        }

        u1_t_result |= (U1)(u1_t_func << u4_t_loop);
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_STSWRHCSTM1(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_STSWRHCSTM1(void)
{
    static const ST_MCST_FUNC     st_sp_MCST_L_STSWRHCSTM1_FUNC[MCST_STSW_FUNC_NUM] = {
        {    (U1)TRUE    ,  (U2)U2_MAX                     },        /*  Empty                */
        {    (U1)U1_MAX  ,  (U2)VDF_ESO_CH_DRVMD_NRML      },        /*  Drive Mode:Normal   */
        {    (U1)U1_MAX  ,  (U2)VDF_ESO_CH_DRVMD_SPRT      },        /*  Drive Mode:Sport    */
        {    (U1)U1_MAX  ,  (U2)VDF_ESO_CH_DRVMD_SPRT_S    },        /*  Drive Mode:Sport S  */
        {    (U1)U1_MAX  ,  (U2)VDF_ESO_CH_DRVMD_SPRT_SP   },        /*  Drive Mode:Sport S+ */
        {    (U1)U1_MAX  ,  (U2)VDF_ESO_CH_DRVMD_ECO       },        /*  Drive Mode:ECO      */
        {    (U1)U1_MAX  ,  (U2)VDF_ESO_CH_DRVMD_CMFRT     },        /*  Drive Mode:Comfort  */
        {    (U1)U1_MAX  ,  (U2)VDF_ESO_CH_DRVMD_CSTM      }         /*  Drive Mode:Custom   */
    };

    U1  u1_t_result;
    U1  u1_t_func;
    U2  u2_t_id;
    U4  u4_t_loop;

    u1_t_result = (U1)0U;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)MCST_STSW_FUNC_NUM ; u4_t_loop++){

        u1_t_func   = st_sp_MCST_L_STSWRHCSTM1_FUNC[u4_t_loop].u1_func;
        u2_t_id     = st_sp_MCST_L_STSWRHCSTM1_FUNC[u4_t_loop].u2_esopt_id;

        if(u1_t_func == (U1)U1_MAX){
            u1_t_func = u1_g_VardefEsOptAvaByCh(u2_t_id);
        }

        u1_t_result |= (U1)(u1_t_func << u4_t_loop);
    }

    u1_t_result &= (U1)MCST_L_STSWRHCSTM1_FUNCMASK;     /* 800B Drive Mode Without Function  */

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_STSWRHCSTM2(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_STSWRHCSTM2(void)
{
    static const ST_MCST_FUNC     st_sp_MCST_L_STSWRHCSTM2_FUNC[MCST_STSW_FUNC_NUM] = {
        {    (U1)FALSE   ,  (U2)U2_MAX              },        /*  Undefined            */
        {    (U1)FALSE   ,  (U2)U2_MAX              },        /*  Drive Mode:Power     */
        {    (U1)FALSE   ,  (U2)U2_MAX              },        /*  EV Mode(HV)          */
        {    (U1)FALSE   ,  (U2)U2_MAX              },        /*  Snow Mode            */
        {    (U1)U1_MAX  ,  (U2)VDF_ESO_CH_PVM      },        /*  PVM                  */
        {    (U1)U1_MAX  ,  (U2)VDF_ESO_CH_MTM      },        /*  MTM                  */
        {    (U1)U1_MAX  ,  (U2)VDF_ESO_CH_SIM      },        /*  SIM                  */
        {    (U1)FALSE   ,  (U2)U2_MAX              }         /*  Idling stop          */
    };

    U1  u1_t_result;
    U1  u1_t_func;
    U2  u2_t_id;
    U4  u4_t_loop;

    u1_t_result = (U1)0U;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)MCST_STSW_FUNC_NUM ; u4_t_loop++){

        u1_t_func   = st_sp_MCST_L_STSWRHCSTM2_FUNC[u4_t_loop].u1_func;
        u2_t_id     = st_sp_MCST_L_STSWRHCSTM2_FUNC[u4_t_loop].u2_esopt_id;

        if(u1_t_func == (U1)U1_MAX){
            u1_t_func = u1_g_VardefEsOptAvaByCh(u2_t_id);
        }

        u1_t_result |= (U1)(u1_t_func << u4_t_loop);
    }

    u1_t_result &= (U1)MCST_L_STSWRHCSTM2_FUNCMASK;     /* 800B Drive Mode Without Function  */

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_STSWRHCSTM3(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_STSWRHCSTM3(void)
{
    static const ST_MCST_FUNC     st_sp_MCST_L_STSWRHCSTM3_FUNC[MCST_STSW_FUNC_NUM] = {
        {    (U1)FALSE  ,  (U2)U2_MAX      },        /*  Undefined                */
        {    (U1)TRUE   ,  (U2)U2_MAX      },        /*  Meter Contents           */
        {    (U1)TRUE   ,  (U2)U2_MAX      },        /*  HUD Position             */
        {    (U1)TRUE   ,  (U2)U2_MAX      },        /*  HUD Dimmer               */
        {    (U1)FALSE  ,  (U2)U2_MAX      },        /*  EV  Charge               */
        {    (U1)FALSE  ,  (U2)U2_MAX      },        /*  EV  Mode(PHV)            */
        {    (U1)TRUE   ,  (U2)U2_MAX      },        /*  HUD ON/OFF               */
        {    (U1)TRUE   ,  (U2)U2_MAX      }         /*  HUD MODE                 */
    };

    U1  u1_t_result;
    U1  u1_t_func;
    U2  u2_t_id;
    U4  u4_t_loop;

    u1_t_result = (U1)0U;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)MCST_STSW_FUNC_NUM ; u4_t_loop++){

        u1_t_func   = st_sp_MCST_L_STSWRHCSTM3_FUNC[u4_t_loop].u1_func;
        u2_t_id     = st_sp_MCST_L_STSWRHCSTM3_FUNC[u4_t_loop].u2_esopt_id;

        if(u1_t_func == (U1)U1_MAX){
            u1_t_func = u1_g_VardefEsOptAvaByCh(u2_t_id);
        }

        u1_t_result |= (U1)(u1_t_func << u4_t_loop);
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_STSWLH(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_STSWLH(void)
{
    static const U1     u1_sp_MCST_L_STSWLH[MCST_STSWGROUP_FUNC_NUM] = {
        (U1)FALSE,        /*  Undefined                */
        (U1)TRUE,         /*  Audio                    */
        (U1)TRUE,         /*  A/C                      */
        (U1)TRUE          /*  Custom                   */
    };

    U1  u1_t_result;
    U1  u1_t_func;
    U4  u4_t_loop;

    u1_t_result = (U1)0U;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)MCST_STSWGROUP_FUNC_NUM ; u4_t_loop++){

        u1_t_func   = u1_sp_MCST_L_STSWLH[u4_t_loop];
        u1_t_result |= (U1)(u1_t_func << u4_t_loop);
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_STSWRH(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_STSWRH(void)
{
    static const U1     u1_sp_MCST_L_STSWRH[MCST_STSWGROUP_FUNC_NUM] = {
        (U1)FALSE,        /*  Undefined                */
        (U1)U1_MAX,       /*  Drive Mode               */
        (U1)TRUE,         /*  Change Disp              */
        (U1)TRUE          /*  Custom                   */
    };

    U4  u4_tp_mcst_esopt[VDF_ESO_NOW_AVA];
    U1  u1_t_result;
    U1  u1_t_func;
    U4  u4_t_loop;
    U1  u1_t_data;

    u1_t_data   = (U1)0U;
    u1_t_result = (U1)0U;

    for(u4_t_loop = (U1)0U ; u4_t_loop < (U4)VDF_ESO_NOW_AVA ; u4_t_loop++){
        u4_tp_mcst_esopt[u4_t_loop] = (U4)0U;
    }

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)MCST_STSWGROUP_FUNC_NUM ; u4_t_loop++){

        u1_t_func   = u1_sp_MCST_L_STSWRH[u4_t_loop];

        if(u1_t_func == (U1)U1_MAX){
            vd_g_VardefEsOptAva(&u4_tp_mcst_esopt[0], (U1)VDF_ESO_NOW_AVA);
            u1_t_data =  (U1)((u4_tp_mcst_esopt[MCST_DRVMODE_ARRYPOS] & (U4)MCST_DRVMODE_SIG_MASK) >> MCST_DRVMODE_BITPOS);
            u1_t_data &= (U1)MCST_DRVMODE_JDG_MASK;

            if(((u1_t_data & (U1)MCST_DRVMODE3) == (U1)MCST_DRVMODE3) ||
               ((u1_t_data & (U1)MCST_DRVMODE4) == (U1)MCST_DRVMODE4)){
                u1_t_func = (U1)TRUE;
            }
            else {
                u1_t_func = (U1)FALSE;
            }
        }

        u1_t_result |= (U1)(u1_t_func << u4_t_loop);
    }

    u1_t_result &= (U1)MCST_L_STSWRH_FUNCMASK;     /* 800B Drive Mode Without Function  */

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_STSW_FUNC(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_STSW_FUNC(void)
{
    U1  u1_t_result;

    u1_t_result = (U1)TRUE;     /* 800B Applicable */

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_GRV_FUNC(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_GRV_FUNC(void)
{
    U1  u1_t_result;

    u1_t_result = (U1)TRUE;     /* 800B Applicable */

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* static U1    u1_s_McstCfgJdg_L_MET_TSTFN(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgJdg_L_MET_TSTFN(void)
{
    U1  u1_t_result;

    u1_t_result = (U1)FALSE;     /* 220D Not Applicable */

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* U1    u1_g_McstCfgJdg_L_MET_TST(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_McstCfgJdg_L_MET_TST(void)
{
    U1  u1_t_result;

    u1_t_result = (U1)MCST_MM_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/* U1    u1_g_McstCfgJdg_L_RHEOST(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_McstCfgJdg_L_RHEOST(void)
{
    U1  u1_t_result;

    u1_t_result = (U1)MCST_MM_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  U1    u1_g_McstCfgJdgHUDFail(const U1 u1_a_NOW)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_McstCfgJdgHUDFail(const U1 u1_a_NOW){

    U1      u1_t_fail;

    u1_t_fail = u1_g_HmiMcstJdgHUDFail(u1_a_NOW);

    return(u1_t_fail);
}

/*===================================================================================================================================*/
/*  U1    u1_g_McstCfgReplaceCustomize(const U1 u1_a_BFI, const U1 u1_t_mcst)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_McstCfgReplaceCustomize(const U1 u1_a_BFI, const U1 u1_a_mcst){
    U1      u1_t_result;
    U2      u2_t_rzrpm;
    U1      u1_t_revmax;

    u1_t_result = u1_a_mcst;
    u2_t_rzrpm  = u2_g_EngspdVarrzGetRzrpm();
    u1_t_revmax = (U1)(u2_t_rzrpm / (U2)MCST_REV_ST_LSB);

    if((u1_a_BFI == u1_g_MCST_BFI_REV_ST ) &&
       ((u1_a_mcst > u1_t_revmax) || (u1_a_mcst < u1_g_MCST_REV_ST_MIN))){
        u1_t_result = u1_s_McstCfgRevStInit();
        if(u1_t_result > u1_t_revmax){
            u1_t_result = u1_t_revmax;
        }
    }

    if(u1_a_BFI == u1_g_MCST_BFI_HUD){
        u1_t_result = u1_g_McstCfgJdgHUDFail(u1_a_mcst);
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  U4    u4_g_McstCfgReplaceCustomize(const U1 u1_a_BFI, const U4 u4_t_mcst)                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4    u4_g_McstCfgU4ReplaceCustomize(const U1 u1_a_BFI, const U4 u4_a_mcst){

    return(u4_a_mcst);
}

/*===================================================================================================================================*/
/*  U4    u4_g_McstCfgInit(const U1 u1_a_BFI){                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4    u4_g_McstCfgInit(const U1 u1_a_BFI){
    static const ST_MCST_CFG_INI     st_sp_MCST_CFG_INI[] = {
        /* u1_id,                            fp_u4_cfgini                           */
        {(U1)MCST_BFI_FC_IND,                vdp_PTR_NA                              },
        {(U1)MCST_BFI_ELE_CO_HIS,            vdp_PTR_NA                              },
        {(U1)MCST_BFI_FUEL_CO_HIS,           vdp_PTR_NA                              },
        {(U1)MCST_BFI_ELE_CO_GRH,            vdp_PTR_NA                              },
        {(U1)MCST_BFI_FUEL_CO_GRH,           vdp_PTR_NA                              },
        {(U1)MCST_BFI_AMBTMP,                vdp_PTR_NA                              },
        {(U1)MCST_BFI_SPEED,                 vdp_PTR_NA                              },
        {(U1)MCST_BFI_DIST,                  vdp_PTR_NA                              },
        {(U1)MCST_BFI_FUECO,                 vdp_PTR_NA                              },
        {(U1)MCST_BFI_ELECO,                 vdp_PTR_NA                              },
        {(U1)MCST_BFI_REV_ST,                vdp_PTR_NA                              },
        {(U1)MCST_BFI_REV_LIM,               vdp_PTR_NA                              },
        {(U1)MCST_BFI_REV_IND,               &u4_s_McstCfgRevIndInit                 },
        {(U1)MCST_BFI_REV_PK,                &u4_s_McstCfgRevPkInit                  },
        {(U1)MCST_BFI_TRIP_A_UP,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_TRIP_A_DN,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_TRIP_B_UP,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_TRIP_B_DN,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_TAST_FLG,              vdp_PTR_NA                              },
        {(U1)MCST_BFI_NAME_DRV1,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_NAME_DRV2,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_NAME_DRV3,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_LANG,                  vdp_PTR_NA                              },
        {(U1)MCST_BFI_WDG_EYE0,              vdp_PTR_NA                              },
        {(U1)MCST_BFI_WDG_EYE1,              vdp_PTR_NA                              },
        {(U1)MCST_BFI_WDG_NAVI,              vdp_PTR_NA                              },
        {(U1)MCST_BFI_WDG_ADAS,              vdp_PTR_NA                              },
        {(U1)MCST_BFI_WDG_ECO,               vdp_PTR_NA                              },
        {(U1)MCST_BFI_ANALOG_EYE1,           &u4_s_McstCfgAnalogInit                 },
        {(U1)MCST_BFI_ANALOG_EYE2,           &u4_s_McstCfgAnalogInit                 },
        {(U1)MCST_BFI_ANALOG,                vdp_PTR_NA                              },
        {(U1)MCST_BFI_AUDIO_TAB,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_ENEMON,                vdp_PTR_NA                              },
        {(U1)MCST_BFI_4WD,                   vdp_PTR_NA                              },
        {(U1)MCST_BFI_DRVINF_OPE,            vdp_PTR_NA                              },
        {(U1)MCST_BFI_DRVINF_UP,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_DRVINF_DN,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_NOW_RUN,               vdp_PTR_NA                              },
        {(U1)MCST_BFI_EV_DRINFO,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_CROSS_ADV,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_TEL,                   &u4_s_McstCfgTelInit                    },
        {(U1)MCST_BFI_AUDIO_OPE,             &u4_s_McstCfgAudioOpeInit               },
        {(U1)MCST_BFI_VOL_OPE,               &u4_s_McstCfgVolOpeInit                 },
        {(U1)MCST_BFI_VRCTRL,                &u4_s_McstCfgVrctrlInit                 },
        {(U1)MCST_BFI_STS_TIM,               vdp_PTR_NA                              },
        {(U1)MCST_BFI_STS_ACT,               vdp_PTR_NA                              },
        {(U1)MCST_BFI_CAR_APP,               vdp_PTR_NA                              },
        {(U1)MCST_BFI_ILLUMI_ADJ,            &u4_s_McstCfgIllumiAdjInit              },
        {(U1)MCST_BFI_VIEW_EYE0,             &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_VIEW_EYE1,             &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_VIEW_EYE2,             &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_VIEW_NAVI,             &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_VIEW_ADAS,             &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_VIEW_ECO,              &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_VIEW_TRACK,            &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_VIEW_SHIFT,            &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_VIEW_OFFROAD,          &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_VIEW_EYE6,             &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_TACHO,                 vdp_PTR_NA                              },
        {(U1)MCST_BFI_LEFT_FU_ECO,           &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_EL_ECO,           &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_CONSUMP,          &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_ECO_IND,          &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_ECO_JDG,          &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_EV_RATIO,         &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_NAVI,             &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_AUDIO,            &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_DRV_INFO,         &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_TRIP_A,           &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_TRIP_B,           &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_ENE_MON,          &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_4WD,              &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_TRAC,             &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_ANGEL,            &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_PITCH,            &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_TR_BRAKE,         &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_TR_BSM,           &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_VOLT,             &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_OIL_VOLT,         &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_ENG_AT,           &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_ENGINE,           &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_AT,               &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_TURBO,            &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_BOOST,            &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_MOTOR,            &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_SPORTS,           &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_G_FORCE,          &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_ADBLUE,           &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_TPMS,             &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_OILLVL,           &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_LEFT_FU_ECO_PHV,       &u4_s_McstCfgContentInit                },
        {(U1)MCST_BFI_ECO_IND,               &u4_s_McstCfgEcoIndInit                 },
        {(U1)MCST_BFI_EV_IND,                &u4_s_McstCfgEvIndInit                  },
        {(U1)MCST_BFI_HVIND,                 &u4_s_McstCfgHvIndInit                  },
        {(U1)MCST_BFI_MM_TIMEFMT,            vdp_PTR_NA                              },
        {(U1)MCST_BFI_MM_OFFSET_TIME,        vdp_PTR_NA                              },
        {(U1)MCST_BFI_RHEO_NIGHT,            &u4_s_McstCfgRheoNightInit              },
        {(U1)MCST_BFI_HUDILL,                vdp_PTR_NA                              },
        {(U1)MCST_BFI_HUD_ST,                vdp_PTR_NA                              },
        {(U1)MCST_BFI_HUD,                   &u4_s_McstCfgHudInit                    },
        {(U1)MCST_BFI_AR,                    vdp_PTR_NA                              },
        {(U1)MCST_BFI_HUD_ANALOG,            &u4_s_McstCfgHudAnalogInit              },
        {(U1)MCST_BFI_HUD_ROT,               vdp_PTR_NA                              },
        {(U1)MCST_BFI_DISP_VIEW,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_DISP_EYE0,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_DISP_EYE1,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_DISP_EYE2,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_DISP_MAP,              vdp_PTR_NA                              },
        {(U1)MCST_BFI_DISP_ADAS,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_DISP_ECO,              vdp_PTR_NA                              },
        {(U1)MCST_BFI_DISP_TRACK,            vdp_PTR_NA                              },
        {(U1)MCST_BFI_DISP_SHIFT,            vdp_PTR_NA                              },
        {(U1)MCST_BFI_DISP_OFFROAD,          vdp_PTR_NA                              },
        {(U1)MCST_BFI_DISP_EYE6,             vdp_PTR_NA                              },
        {(U1)MCST_BFI_DISP_CHARGEMODE,       vdp_PTR_NA                              },
        {(U1)MCST_BFI_RHEO_DAY,              vdp_PTR_NA                              },
        {(U1)MCST_BFI_TIMEFMT,               vdp_PTR_NA                              },
        {(U1)MCST_BFI_OFFSET_TIME,           vdp_PTR_NA                              },
        {(U1)MCST_BFI_METWRNCSTM,            vdp_PTR_NA                              }
    };

    U4      u4_t_result;

    u4_t_result = (U4)MCST_BF_UNK_U4;
    if(u1_a_BFI < (U1)MCST_NUM_BF){
        u4_t_result = st_gp_MCST_INI[u1_a_BFI].u4_ini;

        if(st_sp_MCST_CFG_INI[u1_a_BFI].fp_u4_cfgini != vdp_PTR_NA){
            u4_t_result = st_sp_MCST_CFG_INI[u1_a_BFI].fp_u4_cfgini(st_sp_MCST_CFG_INI[u1_a_BFI].u1_id);
        }
    }

    return(u4_t_result);
}

/*===================================================================================================================================*/
/*  void    vd_g_McstCfgUserChgHook(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_McstCfgUserChgHook(void){

    vd_g_DimMcstReadHook();
    vd_g_DateSITimMcstReadHook();
    vd_g_HmiMcstRefHook();

}

/*===================================================================================================================================*/
/*  void    vd_g_McstCfgUserCstmInitHook(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_McstCfgUserCstmInitHook(void){

    vd_g_DimMcstDataResetHook();
    vd_g_DateSITimMcstDelHook();
    vd_g_HmiMcstRefHook();

}

/*===================================================================================================================================*/
/*  void    vd_g_McstCfgCstmInitHook(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_McstCfgCstmInitHook(void){
    vd_g_HmiMcstRefHook();
}

/*===================================================================================================================================*/
/*  void    vd_g_McstCfgSR_DNAMESend(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_McstCfgSR_DNAMESend(void)
{
#if(MCST_PERSET_SUPPORT == 1)
    static const U1     u1_sp_MCST_SR_DNAME[MCST_SR_DNAME_NUM] = {
        (U1)MCST_BFI_NAME_DRV1,
        (U1)MCST_BFI_NAME_DRV2,
        (U1)MCST_BFI_NAME_DRV3
    };

    U1      u1_t_data;
    U1      u1_t_mcstid;
    U1      u1_t_sr_dname;
    U1      u1_t_pre_tx;
    U4      u4_t_loop;

    u1_t_sr_dname = (U1)0U;
    u1_t_pre_tx   = (U1)0U;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)MCST_SR_DNAME_NUM ; u4_t_loop++){
        u1_t_mcstid    = u1_sp_MCST_SR_DNAME[u4_t_loop];
        u1_t_data      = u1_g_McstBf(u1_t_mcstid);
        if(u1_t_data <= (U1)MCST_BFI_NAME_ON){
            u1_t_sr_dname |= (U1)(u1_t_data << u4_t_loop);
        }
    }
    (void)Com_ReceiveSignal(ComConf_ComSignal_SR_DNAME, &u1_t_pre_tx);
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_SR_DNAME,  &u1_t_sr_dname);    /* COM Tx STUB delete */
#endif

    if(u1_t_sr_dname != u1_t_pre_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S50_TXCH0);
    }
#endif
}

/*===================================================================================================================================*/
/*  void    vd_g_McstCfgNickNameInitHook(const U1 u1_a_USER)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_McstCfgNickNameInitHook(const U1 u1_a_USER){

    /* Do Nothing */

}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagHUD(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgDiagHUD(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_HUD);

    if(u1_t_result > (U1)MCST_HUD_ON){
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagHUD_ILL(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgDiagHUD_ILL(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_HUDILL);

    if(u1_t_result > (U1)MCST_HUDILL_BRIGHTNESS31){
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagHUD_ST(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgDiagHUD_ST(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_HUD_ST);

    if(u1_t_result > (U1)MCST_HUD_ST_MIN){
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_MET_TYP(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgDiagMM_MET_TYP(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_TACHO(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgDiagMM_TACHO(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagRHEO(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgDiagRHEO(void){
    U1      u1_t_daynight;
    U1      u1_t_result;

    u1_t_daynight = u1_g_DimLvlDaynight();

    if(u1_t_daynight == (U1)DIM_DAYNIGHT_LVL_NIGHT){
        u1_t_result = u1_g_McstBf((U1)MCST_BFI_RHEO_NIGHT);
    }else{
        u1_t_result = u1_g_McstBf((U1)MCST_BFI_RHEO_DAY);
    }

    if(u1_t_result  <=  (U1)MCST_RHEO_DAY_MAX_HOLD){
        u1_t_result = u1_t_result + (U1)MCST_DIAG_UNDEF_OFFSET;
    }else{
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_ECO_IND(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgDiagMM_ECO_IND(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_ECO_IND);

    if(u1_t_result > (U1)MCST_ECO_IND_ON){
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_EV_IND(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgDiagMM_EV_IND(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_EV_IND);

    if(u1_t_result > (U1)MCST_EV_IND_ON){
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_REV_IND(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgDiagMM_REV_IND(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_REV_ST(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgDiagMM_REV_ST(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_REV_PK(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgDiagMM_REV_PK(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_MET_DSP(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_McstCfgDiagMM_MET_DSP(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_ANALOG_MET(void)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_ANALOG_MET(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_ECO_DRV_IND(void){                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_ECO_DRV_IND(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_ECO_IND);

    if(u1_t_result > (U1)MCST_ECO_IND_ON){
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_EV_IND_DSP(void){                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_EV_IND_DSP(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_EV_IND);

    if(u1_t_result > (U1)MCST_EV_IND_ON){
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_HV_SYS_IND(void){                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_HV_SYS_IND(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_HVIND);

    if(u1_t_result > (U1)MCST_HVIND_ON){
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_MET_DSP_7INCH(void){                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_MET_DSP_7INCH(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_MET_DSP_LT(void){                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_MET_DSP_LT(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_MET_DSP_CT(void){                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_MET_DSP_CT(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_MET_DSP_RT(void){                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_MET_DSP_RT(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_MET_DSP_PRESET(void){                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_MET_DSP_PRESET(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_MET_LAYOUT(void){                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_MET_LAYOUT(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_MET_DESIGN(void){                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_MET_DESIGN(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_CURCNT_LBYTE(void){                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_CURCNT_LBYTE(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_CURCNT_HBYTE(void){                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_CURCNT_HBYTE(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_FUEL_FLG(void){                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_FUEL_FLG(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_FUEL_CO_GRH);

    if(u1_t_result <= (U1)MCST_FUE_CO_GRH_AFT_FUEL){
        u1_t_result = (U1)(u1_t_result + (U1)MCST_DIAG_UNDEF_OFFSET);
    }
    else{
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_ELEC_FLG(void){                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_ELEC_FLG(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_POP_CROSS(void){                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_POP_CROSS(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_CROSS_ADV);

    if(u1_t_result > (U1)MCST_CROSS_ADV_ON){
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_POP_TEL(void){                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_POP_TEL(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_TEL);

    if(u1_t_result > (U1)MCST_TEL_ON){
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_POP_AUDIO(void){                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_POP_AUDIO(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_AUDIO_OPE);

    if(u1_t_result > (U1)MCST_DRVINF_AUDIO_OPE_ON){
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_POP_VOLUME(void){                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_POP_VOLUME(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_VOL_OPE);

    if(u1_t_result > (U1)MCST_VOL_OPE_ON){
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_POP_VOICE(void){                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_POP_VOICE(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_VRCTRL);

    if(u1_t_result > (U1)MCST_VRCTRL_ON){
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_POP_TIME(void){                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_POP_TIME(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_POP_NOTIFY(void){                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_POP_NOTIFY(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_STS_ACT);

    if(u1_t_result > (U1)MCST_STS_ACT_ON){
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_POP_DIM(void){                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_POP_DIM(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_ILLUMI_ADJ);

    if(u1_t_result > (U1)MCST_ILLUMI_ADJ_ON){
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_EV_DRVINF(void){                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_EV_DRVINF(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_DRVINF_CALC(void){                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_DRVINF_CALC(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_DRVINF_UP(void){                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_DRVINF_UP(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_DRVINF_UP);

    if(u1_t_result <= (U1)MCST_DRVINF_UP_DRV_TIM){
        u1_t_result = (U1)(u1_t_result + (U1)MCST_DIAG_UNDEF_OFFSET);
    }
    else{
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_DRVINF_DN(void){                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_DRVINF_DN(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_DRVINF_DN);

    if(u1_t_result <= (U1)MCST_DRVINF_DN_DRV_TIM){
        u1_t_result = (U1)(u1_t_result + (U1)MCST_DIAG_UNDEF_OFFSET);
    }
    else{
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_MET_TRIP_A_UP(void){                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_MET_TRIP_A_UP(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_TRIP_A_UP);

    if(u1_t_result <= (U1)MCST_TRIP_A_UP_DRV_TIM){
        u1_t_result = (U1)(u1_t_result + (U1)MCST_DIAG_UNDEF_OFFSET);
    }
    else{
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_MET_TRIP_A_DN(void){                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_MET_TRIP_A_DN(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_TRIP_A_DN);

    if(u1_t_result <= (U1)MCST_TRIP_A_DN_DRV_TIM){
        u1_t_result = (U1)(u1_t_result + (U1)MCST_DIAG_UNDEF_OFFSET);
    }
    else{
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_MET_TRIP_B_UP(void){                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_MET_TRIP_B_UP(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_TRIP_B_UP);

    if(u1_t_result <= (U1)MCST_TRIP_B_UP_DRV_TIM){
        u1_t_result = (U1)(u1_t_result + (U1)MCST_DIAG_UNDEF_OFFSET);
    }
    else{
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_MET_TRIP_B_DN(void){                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_MET_TRIP_B_DN(void){
    U1      u1_t_result;

    u1_t_result = u1_g_McstBf((U1)MCST_BFI_TRIP_B_DN);

    if(u1_t_result <= (U1)MCST_TRIP_B_DN_DRV_TIM){
        u1_t_result = (U1)(u1_t_result + (U1)MCST_DIAG_UNDEF_OFFSET);
    }
    else{
        u1_t_result = (U1)MCST_DIAG_UNDEF;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_ENG_MONI(void){                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_ENG_MONI(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_McstCfgDiagMM_4WD_AWD(void){                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgDiagMM_4WD_AWD(void){
    U1      u1_t_result;

    u1_t_result = (U1)MCST_DIAG_UNDEF;

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_McstCfgRevStInit(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U1      u1_s_McstCfgRevStInit(void)
{
    U2      u2_t_revinit;
    U1      u1_t_result;

    u2_t_revinit = u2_CALIB_MCUID0266_REVINIT;

    u1_t_result = (U1)(u2_t_revinit / (U2)MCST_REV_ST_LSB);

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_McstCfgRevIndInit(const U1 u1_a_id)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U4      u4_s_McstCfgRevIndInit(const U1 u1_a_id)
{
    U1      u1_t_revind_sup;
    U4      u4_t_result;

    u1_t_revind_sup = u1_CALIB_MCUID0265_REVIND;

    if(u1_t_revind_sup == (U1)TRUE){
        u4_t_result = (U4)MCST_REV_IND_ON;
    }
    else{
        u4_t_result = (U4)MCST_REV_IND_OFF;
    }

    return(u4_t_result);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_McstCfgRevPkInit(const U1 u1_a_id)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U4      u4_s_McstCfgRevPkInit(const U1 u1_a_id)
{
    static const U1 u1_sp_MCST_CFG_REVPKSUP[CALIB_MCUID0025_NUM] = {
        {(U1)FALSE  },  /* Switch NON */
        {(U1)FALSE  },  /* GR-S       */
        {(U1)TRUE   },  /* GR         */
        {(U1)TRUE   },  /* GRMN       */
        {(U1)TRUE   },  /* F-SPORT    */
        {(U1)TRUE   },  /* F          */
        {(U1)TRUE   }   /* 070D       */
    };

    U1      u1_t_sports;
    U1      u1_t_revpk_sup;
    U4      u4_t_result;

    u1_t_sports    = u1_s_McstCfgCalibU1NumChk(u1_CALIB_MCUID0025_SPORTS, (U1)CALIB_MCUID0025_NUM, (U1)CALIB_MCUID0025_DEF);
    u1_t_revpk_sup = u1_sp_MCST_CFG_REVPKSUP[u1_t_sports];

    if(u1_t_revpk_sup == (U1)TRUE){
        u4_t_result = (U4)MCST_REV_PK_ON;
    }
    else{
        u4_t_result = (U4)MCST_REV_PK_OFF;
    }

    return(u4_t_result);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_McstCfgTelInit(const U1 u1_a_id)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U4      u4_s_McstCfgTelInit(const U1 u1_a_id)
{
    U1      u1_t_tel_sup;
    U4      u4_t_result;

    u1_t_tel_sup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MM_TEL);
    if(u1_t_tel_sup == (U1)TRUE){
        u4_t_result = (U4)MCST_TEL_ON;
    }
    else{
        u4_t_result = (U4)MCST_TEL_OFF;
    }

    return(u4_t_result);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_McstCfgAudioOpeInit(const U1 u1_a_id)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U4      u4_s_McstCfgAudioOpeInit(const U1 u1_a_id)
{
    U1      u1_t_audio_sup;
    U4      u4_t_result;

    u1_t_audio_sup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MM_AUDIO);
    if(u1_t_audio_sup == (U1)TRUE){
        u4_t_result = (U4)MCST_DRVINF_AUDIO_OPE_ON;
    }
    else{
        u4_t_result = (U4)MCST_DRVINF_AUDIO_OPE_OFF;
    }

    return(u4_t_result);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_McstCfgVolOpeInit(const U1 u1_a_id)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U4      u4_s_McstCfgVolOpeInit(const U1 u1_a_id)
{
    U1      u1_t_vol_sup;
    U4      u4_t_result;

    u1_t_vol_sup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MM_AUDIO);
    if(u1_t_vol_sup == (U1)TRUE){
        u4_t_result = (U4)MCST_VOL_OPE_ON;
    }
    else{
        u4_t_result = (U4)MCST_VOL_OPE_OFF;
    }

    return(u4_t_result);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_McstCfgVrctrlInit(const U1 u1_a_id)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U4      u4_s_McstCfgVrctrlInit(const U1 u1_a_id)
{
    static const U4 u4_s_VRINT_BIT = (U4)0x00000010U;
    static const U1 u1_s_VRINT_LSB = (U1)4U;
    U4        u4_t_vr_int;
    U1        u1_t_vr_sup;
    U4        u4_t_result;

    u4_t_vr_int = u4_g_HmiRim((U1)HMIRIM_INTERRUPT_CSTM);
    u1_t_vr_sup = (U1)(u4_t_vr_int & u4_s_VRINT_BIT) >> u1_s_VRINT_LSB;
    if(u1_t_vr_sup == (U1)TRUE){
        u4_t_result = (U4)MCST_VRCTRL_ON;
    }
    else{
        u4_t_result = (U4)MCST_VRCTRL_OFF;
    }

    return(u4_t_result);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_McstCfgIllumiAdjInit(const U1 u1_a_id)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U4      u4_s_McstCfgIllumiAdjInit(const U1 u1_a_id)
{
    U1      u1_t_illumi_type;
    U1      u1_t_illumi_sup;
    U4      u4_t_result;

    u1_t_illumi_type = u1_CALIB_MCUID0430_RHEOSW;

    if(u1_t_illumi_type != (U1)CALIB_MCUID0430_SOFTSW){
        u1_t_illumi_sup = (U1)TRUE;
    }
    else{
        u1_t_illumi_sup = (U1)FALSE;
    }
    if(u1_t_illumi_sup == (U1)TRUE){
        u4_t_result = (U4)MCST_ILLUMI_ADJ_ON;
    }
    else{
        u4_t_result = (U4)MCST_ILLUMI_ADJ_OFF;
    }

    return(u4_t_result);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_McstCfgEcoIndInit(const U1 u1_a_id)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U4      u4_s_McstCfgEcoIndInit(const U1 u1_a_id)
{
    U1      u1_t_ptsys;
    U1      u1_t_ecoind_sup;
    U4      u4_t_result;

    u1_t_ptsys = u1_g_VardefPtsRx();
    if((u1_t_ptsys == (U1)VDF_PTS_RX_01_GAS    ) ||
       (u1_t_ptsys == (U1)VDF_PTS_RX_02_GAS_ISS)) {
        u1_t_ecoind_sup = (U1)TRUE;
    }
    else{
        u1_t_ecoind_sup = (U1)FALSE;
    }

    if(u1_t_ecoind_sup == (U1)TRUE){
        u4_t_result = (U4)MCST_ECO_IND_ON;
    }
    else{
        u4_t_result = (U4)MCST_ECO_IND_OFF;
    }

    return(u4_t_result);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_McstCfgEvIndInit(const U1 u1_a_id)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U4      u4_s_McstCfgEvIndInit(const U1 u1_a_id)
{
    U1      u1_t_spsw;
    U1      u1_t_ptsys;
    U1      u1_t_evind_sup;
    U4      u4_t_result;

    u1_t_spsw  = u1_s_McstCfgCalibU1NumChk(u1_CALIB_MCUID0025_SPORTS, (U1)CALIB_MCUID0025_NUM, (U1)CALIB_MCUID0025_DEF);
    u1_t_ptsys = u1_g_VardefPtsRx();
    if((u1_t_spsw  != (U1)CALIB_MCUID0025_070D ) && 
      ((u1_t_ptsys == (U1)VDF_PTS_RX_03_HYB    ) ||
       (u1_t_ptsys == (U1)VDF_PTS_RX_04_HYB_PLU) ||
       (u1_t_ptsys == (U1)VDF_PTS_RX_06_HYB_MOT))) {
        u1_t_evind_sup = (U1)TRUE;
    }
    else{
        u1_t_evind_sup = (U1)FALSE;
    }

    if(u1_t_evind_sup == (U1)TRUE){
        u4_t_result = (U4)MCST_EV_IND_ON;
    }
    else{
        u4_t_result = (U4)MCST_EV_IND_OFF;
    }

    return(u4_t_result);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_McstCfgHvIndInit(const U1 u1_a_id)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U4      u4_s_McstCfgHvIndInit(const U1 u1_a_id)
{
    U1      u1_t_spsw;
    U1      u1_t_ptsys;
    U1      u1_t_hvind_sup;
    U4      u4_t_result;

    u1_t_spsw  = u1_s_McstCfgCalibU1NumChk(u1_CALIB_MCUID0025_SPORTS, (U1)CALIB_MCUID0025_NUM, (U1)CALIB_MCUID0025_DEF);
    u1_t_ptsys = u1_g_VardefPtsRx();
    if((u1_t_spsw  != (U1)CALIB_MCUID0025_070D ) && 
      ((u1_t_ptsys == (U1)VDF_PTS_RX_03_HYB    ) ||
       (u1_t_ptsys == (U1)VDF_PTS_RX_04_HYB_PLU) ||
       (u1_t_ptsys == (U1)VDF_PTS_RX_06_HYB_MOT))) {
        u1_t_hvind_sup = (U1)TRUE;
    }
    else{
        u1_t_hvind_sup = (U1)FALSE;
    }

    if(u1_t_hvind_sup == (U1)TRUE){
        u4_t_result = (U4)MCST_HVIND_ON;
    }
    else{
        u4_t_result = (U4)MCST_HVIND_OFF;
    }

    return(u4_t_result);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_McstCfgHudInit(const U1 u1_a_id)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U4      u4_s_McstCfgHudInit(const U1 u1_a_id)
{
    U1      u1_t_hud_sup;
    U4      u4_t_result;

    u1_t_hud_sup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_GVIF2);
    if(u1_t_hud_sup == (U1)TRUE){
        u4_t_result = (U4)MCST_HUD_ON;
    }
    else{
        u4_t_result = (U4)MCST_HUD_OFF;
    }

    return(u4_t_result);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_McstCfgHudAnalogInit(const U1 u1_a_id)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_id : MCST_BFI_XXX                                                                                           */
/*  Return:         u4_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U4      u4_s_McstCfgHudAnalogInit(const U1 u1_a_id)
{
    static const U1 u1_s_MCST_HUDANALOG_SUP = (U1)1U;
    static const U1 u1_s_MCST_HUDANALOG_DEF = (U1)2U;
    static const ST_MCST_HUDANALOG_INI  st_sp_MCST_HUDANALOG_INI[] = {
        /* u1p_mcuid,                       u4_result,                     */
        {&u1_CALIB_MCUID0715_HUD_TACHO,     (U4)MCST_HUD_ANALOG_TACHOMET,   },
        {&u1_CALIB_MCUID0716_HUD_ECOIND,    (U4)MCST_HUD_ANALOG_ECOIND,     },
        {&u1_CALIB_MCUID0717_HUD_HVIND,     (U4)MCST_HUD_ANALOG_HVIND,      },
        {&u1_CALIB_MCUID0718_HUD_FCIND,     (U4)MCST_HUD_ANALOG_FCIND,      },
        {&u1_CALIB_MCUID0719_HUD_PWR,       (U4)MCST_HUD_ANALOG_POWER,      },
        {&u1_CALIB_MCUID0756_HUD_DRVMD,     (U4)MCST_HUD_ANALOG_DMODE,      }
    };
    static const U4 u4_s_MCST_NUM_HUDANALOG_BF = (U4)(sizeof(st_sp_MCST_HUDANALOG_INI) / sizeof(st_sp_MCST_HUDANALOG_INI[0]));

    U1      u1_t_calib_val;
    U4      u4_t_result;
    U1      u1_t_supchk;
    U4      u4_t_loop;

    if(u1_a_id < (U1)MCST_NUM_BF){
        u4_t_result = st_gp_MCST_INI[u1_a_id].u4_ini;
    }
    else{
        u4_t_result = (U4)MCST_BF_INI;
    }
    u1_t_supchk = (U1)FALSE;
    for(u4_t_loop = (U4)0U ; u4_t_loop < u4_s_MCST_NUM_HUDANALOG_BF; u4_t_loop++){
        u1_t_calib_val = *(st_sp_MCST_HUDANALOG_INI[u4_t_loop].u1p_mcuid);
        if(u1_t_calib_val == u1_s_MCST_HUDANALOG_DEF){
            u4_t_result = st_sp_MCST_HUDANALOG_INI[u4_t_loop].u4_result;
            break;
        }
        else if((u1_t_calib_val == u1_s_MCST_HUDANALOG_SUP) && (u1_t_supchk == (U1)FALSE)
             && ((st_sp_MCST_HUDANALOG_INI[u4_t_loop].u4_result != (U4)MCST_HUD_ANALOG_DMODE)
              || (u1_CALIB_MCUID0648_HUDHVSYSIND == (U1)TRUE))){
            u4_t_result = st_sp_MCST_HUDANALOG_INI[u4_t_loop].u4_result;
            u1_t_supchk = (U1)TRUE;
        }
        else{
            /* Do Nothing */
        }
    }

    return(u4_t_result);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_McstCfgRheoNightInit(const U1 u1_a_id)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u4_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U4      u4_s_McstCfgRheoNightInit(const U1 u1_a_id)
{
    U1      u1_t_rheo_pos;

    u1_t_rheo_pos = u1_s_McstCfgCalibU1MaxChk(u1_CALIB_MCUID0340_RHEOPOS_NIGHT, (U1)CALIB_MCUID0340_MAX, (U1)CALIB_MCUID0340_DEF);

    return((U4)u1_t_rheo_pos);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_McstCfgAnalogInit(const U1 u1_a_id)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_id : MCST_BFI_XXX                                                                                           */
/*  Return:         u4_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U4      u4_s_McstCfgAnalogInit(const U1 u1_a_id)
{
    static const U1 u1_s_MCST_ANALOG_SUP = (U1)1U;
    static const U1 u1_s_MCST_ANALOG_DEF = (U1)2U;
    static const ST_MCST_ANALOG_INI  st_sp_MCST_ANALOG_INI[] = {
        /* u1_id,                       u1p_mcuid,                          u4_result,                    */
        {(U1)MCST_BFI_ANALOG_EYE1,      &u1_CALIB_MCUID0705_MET_CD_TACHO,   (U4)MCST_ANALOG_EYE1_TACHOMET },
        {(U1)MCST_BFI_ANALOG_EYE1,      &u1_CALIB_MCUID0706_MET_CD_SPEED,   (U4)MCST_ANALOG_EYE1_SPEEDMET },
        {(U1)MCST_BFI_ANALOG_EYE1,      &u1_CALIB_MCUID0707_MET_CD_HVIND,   (U4)MCST_ANALOG_EYE1_HVIND    },
        {(U1)MCST_BFI_ANALOG_EYE1,      &u1_CALIB_MCUID0708_MET_CD_FCIND,   (U4)MCST_ANALOG_EYE1_FCIND    },
        {(U1)MCST_BFI_ANALOG_EYE1,      &u1_CALIB_MCUID0709_MET_CD_PWR,     (U4)MCST_ANALOG_EYE1_POWER    },
        {(U1)MCST_BFI_ANALOG_EYE1,      &u1_CALIB_MCUID0754_MET_CD_DRVMD,   (U4)MCST_ANALOG_EYE1_DMODE    },
        {(U1)MCST_BFI_ANALOG_EYE2,      &u1_CALIB_MCUID0710_MET_LD_TACHO,   (U4)MCST_ANALOG_EYE2_TACHOMET },
        {(U1)MCST_BFI_ANALOG_EYE2,      &u1_CALIB_MCUID0711_MET_LD_HVIND,   (U4)MCST_ANALOG_EYE2_HVIND    },
        {(U1)MCST_BFI_ANALOG_EYE2,      &u1_CALIB_MCUID0712_MET_LD_FCIND,   (U4)MCST_ANALOG_EYE2_FCIND    },
        {(U1)MCST_BFI_ANALOG_EYE2,      &u1_CALIB_MCUID0713_MET_LD_PWR,     (U4)MCST_ANALOG_EYE2_POWER    },
        {(U1)MCST_BFI_ANALOG_EYE2,      &u1_CALIB_MCUID0755_MET_LD_DRVMD,   (U4)MCST_ANALOG_EYE2_DMODE    }
    };
    static const U4 u4_s_MCST_NUM_ANALOG_BF = (U4)(sizeof(st_sp_MCST_ANALOG_INI) / sizeof(st_sp_MCST_ANALOG_INI[0]));

    U1      u1_t_calib_val;
    U4      u4_t_result;
    U4      u4_t_loop;

    if(u1_a_id < (U1)MCST_NUM_BF){
        u4_t_result = st_gp_MCST_INI[u1_a_id].u4_ini;
    }
    else{
        u4_t_result = (U4)MCST_BF_INI;
    }
    for(u4_t_loop = (U4)0U ; u4_t_loop < u4_s_MCST_NUM_ANALOG_BF; u4_t_loop++){
        u1_t_calib_val = *(st_sp_MCST_ANALOG_INI[u4_t_loop].u1p_mcuid);
        if((u1_a_id == st_sp_MCST_ANALOG_INI[u4_t_loop].u1_id)
        && (u1_t_calib_val == u1_s_MCST_ANALOG_SUP)
        && ((((u1_a_id != (U1)MCST_BFI_ANALOG_EYE1) || (st_sp_MCST_ANALOG_INI[u4_t_loop].u4_result != (U4)MCST_ANALOG_EYE1_DMODE))
          && ((u1_a_id != (U1)MCST_BFI_ANALOG_EYE2) || (st_sp_MCST_ANALOG_INI[u4_t_loop].u4_result != (U4)MCST_ANALOG_EYE2_DMODE)))
         || (u1_CALIB_MCUID0647_METHVSYSIND == (U1)TRUE))){
            u4_t_result = st_sp_MCST_ANALOG_INI[u4_t_loop].u4_result;
            break;
        }
    }
    for(u4_t_loop = (U4)0U ; u4_t_loop < u4_s_MCST_NUM_ANALOG_BF; u4_t_loop++){
        u1_t_calib_val = *(st_sp_MCST_ANALOG_INI[u4_t_loop].u1p_mcuid);
        if((u1_a_id == st_sp_MCST_ANALOG_INI[u4_t_loop].u1_id)
        && (u1_t_calib_val == u1_s_MCST_ANALOG_DEF)){
            u4_t_result = st_sp_MCST_ANALOG_INI[u4_t_loop].u4_result;
            break;
        }
    }

    return(u4_t_result);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_McstCfgContentInit(const U1 u1_a_id)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_id : MCST_BFI_XXX                                                                                           */
/*  Return:         u4_t_result                                                                                                      */
/*===================================================================================================================================*/
static  U4      u4_s_McstCfgContentInit(const U1 u1_a_id)
{
    static const ST_MCST_CONTENT_INI st_sp_MCST_CONTENT_INI[] = {
        /* u1_id,                       u1p_mcuid                        */
        {(U1)MCST_BFI_VIEW_EYE0,        &u1_CALIB_MCUID0662_0DIAL_VIEW    },
        {(U1)MCST_BFI_VIEW_EYE1,        &u1_CALIB_MCUID0663_1DIAL_VIEW    },
        {(U1)MCST_BFI_VIEW_EYE2,        &u1_CALIB_MCUID0664_2DIAL_VIEW    },
        {(U1)MCST_BFI_VIEW_NAVI,        &u1_CALIB_MCUID0665_MAP_VIEW      },
        {(U1)MCST_BFI_VIEW_ADAS,        &u1_CALIB_MCUID0666_ADAS_VIEW     },
        {(U1)MCST_BFI_VIEW_ECO,         &u1_CALIB_MCUID0667_ECO_VIEW      },
        {(U1)MCST_BFI_VIEW_TRACK,       &u1_CALIB_MCUID0668_1DIAL_TR_VIEW },
        {(U1)MCST_BFI_VIEW_SHIFT,       &u1_CALIB_MCUID0669_SHTUPIND_VIEW },
        {(U1)MCST_BFI_VIEW_OFFROAD,     &u1_CALIB_MCUID0670_OFFROAD_VIEW  },
        {(U1)MCST_BFI_VIEW_EYE6,        &u1_CALIB_MCUID0671_6DIAL_VIEW    },
        {(U1)MCST_BFI_LEFT_FU_ECO,      &u1_CALIB_MCUID0672_FC_DEF,       },
        {(U1)MCST_BFI_LEFT_EL_ECO,      &u1_CALIB_MCUID0673_PWR_DEF       },
        {(U1)MCST_BFI_LEFT_CONSUMP,     &u1_CALIB_MCUID0704_ENGCNSMP      },
        {(U1)MCST_BFI_LEFT_ECO_IND,     &u1_CALIB_MCUID0675_ECOIND_DEF    },
        {(U1)MCST_BFI_LEFT_ECO_JDG,     &u1_CALIB_MCUID0676_ECOSCR_DEF    },
        {(U1)MCST_BFI_LEFT_EV_RATIO,    &u1_CALIB_MCUID0677_EVRATIO       },
        {(U1)MCST_BFI_LEFT_NAVI,        &u1_CALIB_MCUID0678_NAVI_DEF      },
        {(U1)MCST_BFI_LEFT_AUDIO,       &u1_CALIB_MCUID0679_AUDIO_DEF     },
        {(U1)MCST_BFI_LEFT_DRV_INFO,    &u1_CALIB_MCUID0680_DRVINFO_DEF   },
        {(U1)MCST_BFI_LEFT_TRIP_A,      &u1_CALIB_MCUID0681_TRIPA_DEF     },
        {(U1)MCST_BFI_LEFT_TRIP_B,      &u1_CALIB_MCUID0682_TRIPB_DEF     },
        {(U1)MCST_BFI_LEFT_ENE_MON,     &u1_CALIB_MCUID0683_EGMNTR_DEF    },
        {(U1)MCST_BFI_LEFT_4WD,         &u1_CALIB_MCUID0685_4WD_DEF       },
        {(U1)MCST_BFI_LEFT_TRAC,        &u1_CALIB_MCUID0686_TRC_DEF       },
        {(U1)MCST_BFI_LEFT_ANGEL,       &u1_CALIB_MCUID0687_STR_DEF       },
        {(U1)MCST_BFI_LEFT_PITCH,       &u1_CALIB_MCUID0688_PTCHROLL_DEF  },
        {(U1)MCST_BFI_LEFT_TR_BRAKE,    &u1_CALIB_MCUID0689_TRABRK_DEF    },
        {(U1)MCST_BFI_LEFT_TR_BSM,      &u1_CALIB_MCUID0690_TRABSM_DEF    },
        {(U1)MCST_BFI_LEFT_VOLT,        &u1_CALIB_MCUID0691_VOLTMET_DEF   },
        {(U1)MCST_BFI_LEFT_OIL_VOLT,    &u1_CALIB_MCUID0692_OILPRS_DEF    },
        {(U1)MCST_BFI_LEFT_ENG_AT,      &u1_CALIB_MCUID0693_EATOILTMP_DEF },
        {(U1)MCST_BFI_LEFT_ENGINE,      &u1_CALIB_MCUID0694_EOILTMP_DEF   },
        {(U1)MCST_BFI_LEFT_AT,          &u1_CALIB_MCUID0695_ATOILTMP_DEF  },
        {(U1)MCST_BFI_LEFT_TURBO,       &u1_CALIB_MCUID0696_TRBOGAG_W_L   },
        {(U1)MCST_BFI_LEFT_BOOST,       &u1_CALIB_MCUID0698_BOSTGAG_W_L   },
        {(U1)MCST_BFI_LEFT_MOTOR,       &u1_CALIB_MCUID0700_MTRPWR        },
        {(U1)MCST_BFI_LEFT_SPORTS,      &u1_CALIB_MCUID0701_SPRTSGAG      },
        {(U1)MCST_BFI_LEFT_G_FORCE,     &u1_CALIB_MCUID0702_GFORCE        },
        {(U1)MCST_BFI_LEFT_ADBLUE,      &u1_CALIB_MCUID0703_ADBLUE        },
        {(U1)MCST_BFI_LEFT_TPMS,        &u1_CALIB_MCUID0684_TPMS_DEF      },
        {(U1)MCST_BFI_LEFT_OILLVL,      &u1_CALIB_MCUID0740_OILLVL_DEF    },
        {(U1)MCST_BFI_LEFT_FU_ECO_PHV,  &u1_CALIB_MCUID0674_PHEV_FC_DEF,  }
    };
    static const U4 u4_s_MCST_NUM_CONTENT_BF = (U4)(sizeof(st_sp_MCST_CONTENT_INI) / sizeof(st_sp_MCST_CONTENT_INI[0]));

    U1      u1_t_calib_val;
    U4      u4_t_result;
    U4      u4_t_loop;

    u4_t_result = (U4)1U;
    for(u4_t_loop = (U4)0U ; u4_t_loop < u4_s_MCST_NUM_CONTENT_BF; u4_t_loop++){
        if(u1_a_id == st_sp_MCST_CONTENT_INI[u4_t_loop].u1_id){
            u1_t_calib_val = *(st_sp_MCST_CONTENT_INI[u4_t_loop].u1p_mcuid);
            u4_t_result = (U4)u1_t_calib_val;
            break;
        }
    }

    return(u4_t_result);
}

/*===================================================================================================================================*/
/*  static inline U1      u1_s_McstCfgCalibU1MaxChk(const U1 u1_a_CALIBID, const U1 u1_a_MAX, const U1 u1_a_DEF)                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_CALIBID                                                                                            */
/*                  const U1 u1_a_MAX                                                                                                */
/*                  const U1 u1_a_DEF                                                                                                */
/*  Return:         U1 u1_t_ret                                                                                                      */
/*===================================================================================================================================*/
static inline U1      u1_s_McstCfgCalibU1MaxChk(const U1 u1_a_CALIBID, const U1 u1_a_MAX, const U1 u1_a_DEF)
{
    U1 u1_t_ret;

    u1_t_ret = u1_a_CALIBID;
    if(u1_t_ret > u1_a_MAX){
        u1_t_ret = u1_a_DEF;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  static inline U1      u1_s_McstCfgCalibU1NumChk(const U1 u1_a_CALIBID, const U1 u1_a_NUM, const U1 u1_a_DEF)                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      const U1 u1_a_CALIBID                                                                                            */
/*                  const U1 u1_a_NUM                                                                                                */
/*                  const U1 u1_a_DEF                                                                                                */
/*  Return:         U1 u1_t_ret                                                                                                      */
/*===================================================================================================================================*/
static inline U1      u1_s_McstCfgCalibU1NumChk(const U1 u1_a_CALIBID, const U1 u1_a_NUM, const U1 u1_a_DEF)
{
    U1 u1_t_ret;

    u1_t_ret = u1_a_CALIBID;
    if(u1_t_ret >= u1_a_NUM){
        u1_t_ret = u1_a_DEF;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1 u1_g_McstCfgGetBfIf(const U1 u1_a_BFI)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_McstCfgGetBfIf(const U1 u1_a_BFI){
    U1 u1_t_result;
    U1 u1_t_fuel_eco_vari;

    u1_t_fuel_eco_vari = u1_g_McstCfgGetFuelEcoVari();

    if((u1_a_BFI == (U1)MCST_BFI_LEFT_FU_ECO) && (u1_t_fuel_eco_vari == (U1)MCST_FUEL_ECO_VARI_PHV)) {
        u1_t_result = (U1)MCST_BFI_LEFT_FU_ECO_PHV;
    }
    else {
        u1_t_result = u1_a_BFI;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  U1 u1_g_McstCfgGetFuelEcoVari(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1 u1_g_McstCfgGetFuelEcoVari(void){
    U1 u1_t_result;
    U1 u1_t_ptsys;

    u1_t_ptsys  = u1_g_VardefPtsRx();

    switch(u1_t_ptsys){
        case (U1)VDF_PTS_RX_00_UNK:
        case (U1)VDF_PTS_RX_01_GAS:
        case (U1)VDF_PTS_RX_02_GAS_ISS:
        case (U1)VDF_PTS_RX_03_HYB:
        case (U1)VDF_PTS_RX_05_ELE_BAT:
        case (U1)VDF_PTS_RX_06_HYB_MOT:
        case (U1)VDF_PTS_RX_07_ELE_HYD:
        case (U1)VDF_PTS_RX_08_48V:
            u1_t_result = (U1)MCST_FUEL_ECO_VARI_NML;
            break;
        case (U1)VDF_PTS_RX_04_HYB_PLU:
            u1_t_result = (U1)MCST_FUEL_ECO_VARI_PHV;
            break;
        default:
            u1_t_result = (U1)MCST_FUEL_ECO_VARI_NML;
            break;
    }

    return(u1_t_result);
}

/*===================================================================================================================================*/
/*  void vd_g_McstCfgGetLeftFuelEco(U4 * u4_ap_bf)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_McstCfgGetLeftFuelEco(U4 * u4_ap_bf){
    U1 u1_t_bf_if;
    U1 u1_t_wid;
    U4 u4_t_bit;
    U1 u1_t_lsb;
    U4 u4_t_mask;

    u1_t_wid    =  st_gp_MCST_BF[MCST_BFI_LEFT_FU_ECO_PHV].u1_wid;
    u4_t_bit    =  st_gp_MCST_BF[MCST_BFI_LEFT_FU_ECO_PHV].u4_bit;
    u1_t_lsb    =  st_gp_MCST_BF[MCST_BFI_LEFT_FU_ECO_PHV].u1_lsb;
    u4_t_mask   =  (U4)U4_MAX ^ (u4_t_bit << u1_t_lsb);

    u4_ap_bf[u1_t_wid] &= u4_t_mask;

    u1_t_bf_if  =  u1_g_McstCfgGetBfIf((U1)MCST_BFI_LEFT_FU_ECO);
    u1_t_wid    =  st_gp_MCST_BF[MCST_BFI_LEFT_FU_ECO].u1_wid;
    u4_t_bit    =  st_gp_MCST_BF[MCST_BFI_LEFT_FU_ECO].u4_bit;
    u1_t_lsb    =  st_gp_MCST_BF[MCST_BFI_LEFT_FU_ECO].u1_lsb;
    u4_t_mask   =  (U4)U4_MAX ^ (u4_t_bit << u1_t_lsb);

    u4_ap_bf[u1_t_wid] &= u4_t_mask;
    u4_ap_bf[u1_t_wid] |= (U4)u1_g_McstBf(u1_t_bf_if) << u1_t_lsb;
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    12/07/2018  TA       New.                                                                                               */
/*  1.1.0     3/16/2020  TN       mcst.c v1.0.0 -> v1.1.0.                                                                           */
/*  2.0.0     9/22/2020  TM       mcst.c v1.1.0 -> v2.0.0.                                                                           */
/*  2.1.0     1/13/2021  TM       mcst.c v2.0.0 -> v2.1.0.                                                                           */
/*  2.1.1     4/ 9/2021  TM       mcst.c v2.1.0 -> v2.1.1.                                                                           */
/*  2.1.2     8/ 2/2021  SI       mcst.c v2.1.1 -> v2.1.2.                                                                           */
/*  2.1.3    11/16/2021  SI       mcst.c v2.1.2 -> v2.1.3.                                                                           */
/*  2.1.4    12/27/2021  SI       mcst.c v2.1.3 -> v2.1.4.                                                                           */
/*  2.2.0    02/06/2022  SI       mcst.c v2.1.4 -> v2.2.0.                                                                           */
/*  2.4.0    06/21/2024  SW       mcst.c v2.3.0 -> v2.4.0.                                                                           */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/* 19PFv3-1  12/01/2023  SH       Add u4_s_McstCfgRevStInit(), u4_s_McstCfgRevIndInit() and u4_s_McstCfgRheoNightInit()              */
/*                                Changed to read calibration parameter                                                              */
/* 19PFv3-2  12/22/2023  SI       Add meter warning buzzer parameter(M_MWVCUS-)                                                      */
/* 19PFv3-3  04/12/2024  SH       Add calibration guard                                                                              */
/* 19PFv3-4  04/15/2024  SW       Add u4_s_McstCfgContentInitByPtsys() and u1_s_McstCfgCalibU1MinMaxChk()                            */
/*                                for switch MCUCONST of MCST_BFI_LEFT_FU_ECO                                                        */
/*                                Change MCST_INI_DISP_EYE0 ~ MCST_INI_DISP_EYE6(G_T_SCREEN-CSTD-)                                   */
/* 19PFv3-5  05/02/2024  GM       Delete reference process for u1_g_VardefIllOutType and u1_g_VardefPtsByPid                         */
/* 19PFv3-6  04/18/2024  SK       Change Custmize DTF ID                                                                             */
/* 19PFv3-7  05/16/2024  SH       Change calibration guard                                                                           */
/* 19PFv3-7  05/21/2024  SK       Change initial process                                                                             */
/* 19PFv3-8  05/28/2024  TN       Delete reference process for u4_g_VardefGrade                                                      */
/* 19PFv3-9  06/21/2024  SW       Add IF for PHV Fuel Economy                                                                        */
/* 19PFv3-10 07/04/2024  TN       Delete Calibration Guard Process except for out of array references.                               */
/* 19PFv3-11 07/12/2024  TN       Add Calibration Guard to Unify Vehicle Operation.                                                  */
/* 19PFv3-12 07/12/2024  SW       Add IF for Left Contents of IG-ON ChargeMode                                                       */
/* BEV-1     02/06/2025  SF       Change for BEV System_Consideration_1.(MET-M_ONOFF-CSTD-1-02-A-C0)                                 */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TM   = Takuya Mitsui,   Denso Techno                                                                                           */
/*  * SI   = Shugo Ichinose,  Denso Techno                                                                                           */
/*  * SH   = Sae Hirose,      Denso Techno                                                                                           */
/*  * SW   = Shun Watanabe,   Denso Techno                                                                                           */
/*  * GM   = Glen Monteposo,  DTPH                                                                                                   */
/*  * SK   = Shintaro Kano,   Denso Techno                                                                                           */
/*  * TN   = Tetsushi Nakano, Denso Techno                                                                                           */
/*  * SF   = Shiro Furui,     Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
