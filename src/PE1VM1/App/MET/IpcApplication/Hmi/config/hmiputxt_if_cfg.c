/* 1.10.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Hmiputxt                                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMIPUTXT_IF_CFG_C_MAJOR                  (1)
#define HMIPUTXT_IF_CFG_C_MINOR                  (10)
#define HMIPUTXT_IF_CFG_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmiputxt_cfg_private.h"
#include "hmiputxt_if_cfg.h"
#include "alert.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HMIPUTXT_IF_CFG_C_MAJOR != HMIPUTXT_H_MAJOR) || \
     (HMIPUTXT_IF_CFG_C_MINOR != HMIPUTXT_H_MINOR) || \
     (HMIPUTXT_IF_CFG_C_PATCH != HMIPUTXT_H_PATCH))
#error "hmiputxt_if_cfg.c and hmiputxt_if_cfg.h : source and header files are inconsistent!"
#endif

#if ((HMIPUTXT_IF_CFG_C_MAJOR != HMIPUTXT_IF_CFG_H_MAJOR) || \
     (HMIPUTXT_IF_CFG_C_MINOR != HMIPUTXT_IF_CFG_H_MINOR) || \
     (HMIPUTXT_IF_CFG_C_PATCH != HMIPUTXT_IF_CFG_H_PATCH))
#error "hmiputxt_if_cfg.c and hmiputxt__if_cfg.h : source and header files are inconsistent!"
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
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_REQBIT   st_gp_HMIPUTXTREQBIT[HMIPUTXTCFG_IF_NUM] = {
    /*  u2_src_ch                           u1_src_act                              u1_dst_idx   u4_dst_bit         */
    {    (U2)ALERT_CH_C_BRK_2,              (U1)ALERT_REQ_C_BRK_2_MALFUNC,          (U1)2U,     (U4)0x00000010U    },
    {    (U2)ALERT_CH_C_BRK_2,              (U1)ALERT_REQ_C_BRK_2_ON_MLFNC,         (U1)2U,     (U4)0x00000010U    },
    {    (U2)ALERT_CH_C_BRK_2,              (U1)ALERT_REQ_C_BRK_2_MLFNC_RW,         (U1)2U,     (U4)0x00000010U    },
    {    (U2)ALERT_CH_C_BRK_2,              (U1)ALERT_REQ_C_BRK_2_WRN,              (U1)2U,     (U4)0x00000010U    },
    {    (U2)ALERT_CH_C_BRLV_2_WRN,         (U1)ALERT_REQ_C_BRLV_2_WRN_MALFUNC,     (U1)2U,     (U4)0x00000020U    },
    {    (U2)ALERT_CH_C_ECB,                (U1)ALERT_REQ_C_ECB_FAILDISP,           (U1)2U,     (U4)0x00000040U    },
    {    (U2)ALERT_CH_C_ECB,                (U1)ALERT_REQ_C_ECB_FDISP_RW,           (U1)2U,     (U4)0x00000040U    },
    {    (U2)ALERT_CH_C_ECB,                (U1)ALERT_REQ_C_ECB_TM_DISP,            (U1)2U,     (U4)0x00000040U    },
    {    (U2)ALERT_CH_C_ECB,                (U1)ALERT_REQ_C_ECB_TM_DISP_RW,         (U1)2U,     (U4)0x00000040U    },
    {    (U2)ALERT_CH_C_ECB,                (U1)ALERT_REQ_C_ECB_LNG1_DISP,          (U1)2U,     (U4)0x00000040U    },
    {    (U2)ALERT_CH_C_ECB,                (U1)ALERT_REQ_C_ECB_LNG1_DISP_RW,       (U1)2U,     (U4)0x00000040U    },
    {    (U2)ALERT_CH_C_ECB,                (U1)ALERT_REQ_C_ECB_LNG2_DISP,          (U1)2U,     (U4)0x00000040U    },
    {    (U2)ALERT_CH_C_ECB,                (U1)ALERT_REQ_C_ECB_LNG2_DISP_RW,       (U1)2U,     (U4)0x00000040U    },
    {    (U2)ALERT_CH_C_ECB,                (U1)ALERT_REQ_C_ECB_MFNC_DISP,          (U1)2U,     (U4)0x00000040U    },
    {    (U2)ALERT_CH_C_ECB,                (U1)ALERT_REQ_C_ECB_MFNC_DISP_RW,       (U1)2U,     (U4)0x00000040U    },
    {    (U2)ALERT_CH_C_ECB,                (U1)ALERT_REQ_C_ECB_UNABL_DISP,         (U1)2U,     (U4)0x00000040U    },
    {    (U2)ALERT_CH_C_ECB,                (U1)ALERT_REQ_C_ECB_UNABL_DISP_RW,      (U1)2U,     (U4)0x00000040U    },
    {    (U2)ALERT_CH_H_PEXI,               (U1)ALERT_REQ_H_PEXI_MALFUNC,           (U1)3U,     (U4)0x00000400U    },
    {    (U2)ALERT_CH_B_TDOOR,              (U1)ALERT_REQ_B_TDOOR_RUN,              (U1)9U,     (U4)0x00010000U    },
    {    (U2)ALERT_CH_B_TDOOR,              (U1)ALERT_REQ_B_TDOOR_RUN_ON,           (U1)9U,     (U4)0x00010000U    },
    {    (U2)ALERT_CH_B_TRWIP,              (U1)ALERT_REQ_B_TRWIP_WIPERMALF,        (U1)9U,     (U4)0x00020000U    },
    {    (U2)ALERT_CH_B_TPWSR,              (U1)ALERT_REQ_B_TPWSR_WRN_SR,           (U1)11U,    (U4)0x00040000U    },
    {    (U2)ALERT_CH_B_RSEREM_IGOFF,       (U1)ALERT_REQ_B_RSEREM_IGOFF_REARCHK,   (U1)11U,    (U4)0x00400000U    },
    {    (U2)ALERT_CH_B_TPWSR,              (U1)ALERT_REQ_B_TPWSR_WRN,              (U1)11U,    (U4)0x02000000U    },
    {    (U2)ALERT_CH_B_TPWSR,              (U1)ALERT_REQ_B_TPWSR_WRN_PW,           (U1)11U,    (U4)0x04000000U    },
    {    (U2)ALERT_CH_B_MLGT,               (U1)ALERT_REQ_B_MLGT_MALFUNC,           (U1)12U,    (U4)0x01000000U    },
    {    (U2)ALERT_CH_C_BRPADW,             (U1)ALERT_REQ_C_BRPADW_MALFUNC,         (U1)21U,    (U4)0x00000040U    },
    {    (U2)ALERT_CH_B_RSEREM_IGOFF,       (U1)ALERT_REQ_B_RSEREM_IGOFF_ALLCHK,    (U1)24U,    (U4)0x00800000U    },
    {    (U2)ALERT_CH_B_RSEREM_BAT,         (U1)ALERT_REQ_B_RSEREM_BAT_MUTE,        (U1)24U,    (U4)0x01000000U    },
    {    (U2)ALERT_CH_B_RSEREM_OFFTT,       (U1)ALERT_REQ_B_RSEREM_OFFTT_ALLCHK,    (U1)24U,    (U4)0x02000000U    },
    {    (U2)ALERT_CH_B_RSEREM_BAT2,        (U1)ALERT_REQ_B_RSEREM_BAT2_UNAVBL,     (U1)24U,    (U4)0x04000000U    },
    {    (U2)ALERT_CH_B_RSEREM_BAT3,        (U1)ALERT_REQ_B_RSEREM_BAT3_MALFNC,     (U1)24U,    (U4)0x08000000U    },
    {    (U2)ALERT_CH_B_TDOOR,              (U1)ALERT_REQ_B_TDOOR_STOP,             (U1)32U,    (U4)0x00000008U    },
    {    (U2)ALERT_CH_B_TDOOR,              (U1)ALERT_REQ_B_TDOOR_STOP_ON,          (U1)32U,    (U4)0x00000008U    },
    {    (U2)ALERT_CH_B_TDOOR,              (U1)ALERT_REQ_B_TDOOR_IG_OFF,           (U1)32U,    (U4)0x00000010U    },
    {    (U2)ALERT_CH_B_TDOOR,              (U1)ALERT_REQ_B_TDOOR_IG_OFF_ON,        (U1)32U,    (U4)0x00000010U    },
    {    (U2)ALERT_CH_H_MAICER_PD3,         (U1)ALERT_REQ_H_MAICER_PD3_MALFUNC,     (U1)38U,    (U4)0x00020000U    },
    {    (U2)ALERT_CH_H_MAICER_PD4,         (U1)ALERT_REQ_H_MAICER_PD4_MALFUNC,     (U1)38U,    (U4)0x00040000U    },
    {    (U2)ALERT_CH_H_MAICER_PD1,         (U1)ALERT_REQ_H_MAICER_PD1_MALFUNC,     (U1)38U,    (U4)0x00080000U    },
    {    (U2)ALERT_CH_H_MAICER_PD2,         (U1)ALERT_REQ_H_MAICER_PD2_MALFUNC,     (U1)38U,    (U4)0x00100000U    },
    {    (U2)ALERT_CH_B_RSEREM_IGOFF2,      (U1)ALERT_REQ_B_RSEREM_IGOFF2_C_MUTE,   (U1)38U,    (U4)0x10000000U    },
    {    (U2)ALERT_CH_B_RSEREM_OFFTT,       (U1)ALERT_REQ_B_RSEREM_OFFTT_MUTED,     (U1)38U,    (U4)0x20000000U    }
};

const ST_ALERT_REQBIT   st_gp_HMIPUTXTREQBIT_SLOTA[HMIPUTXTCFG_IF_SLOTA_NUM] = {
    {    (U2)ALERT_CH_O_PDSMAL_PD,          (U1)ALERT_REQ_O_PDSMAL_PD_MULFUNC,      (U1)0U,     (U4)0x00400000U    },
    {    (U2)ALERT_CH_C_HCS_PD,             (U1)ALERT_REQ_C_HCS_PD_HCSMLFNC,        (U1)0U,     (U4)0x10000000U    },
    {    (U2)ALERT_CH_C_HCS_PD,             (U1)ALERT_REQ_C_HCS_PD_ASUSMLFNC,       (U1)0U,     (U4)0x20000000U    },
    {    (U2)ALERT_CH_C_HCS_PD,             (U1)ALERT_REQ_C_HCS_PD_AHCMLFNC,        (U1)1U,     (U4)0x00000010U    },
    {    (U2)ALERT_CH_C_HCS_PD,             (U1)ALERT_REQ_C_HCS_PD_ASUSTMODE,       (U1)1U,     (U4)0x00000020U    },
    {    (U2)ALERT_CH_C_HCS_PD,             (U1)ALERT_REQ_C_HCS_PD_VHRISE,          (U1)1U,     (U4)0x00000040U    },
    {    (U2)ALERT_CH_C_HCS_PD,             (U1)ALERT_REQ_C_HCS_PD_VHLOW,           (U1)1U,     (U4)0x00000080U    },
    {    (U2)ALERT_CH_C_HCS_PD,             (U1)ALERT_REQ_C_HCS_PD_VSPD_HIGH,       (U1)1U,     (U4)0x00000100U    },
    {    (U2)ALERT_CH_C_HCS_PD,             (U1)ALERT_REQ_C_HCS_PD_SYSTMP_HIGH,     (U1)1U,     (U4)0x00000200U    },
    {    (U2)ALERT_CH_C_HCS_PD,             (U1)ALERT_REQ_C_HCS_PD_HCS_UNAVAIL,     (U1)1U,     (U4)0x00000400U    },
    {    (U2)ALERT_CH_C_HCS_PD,             (U1)ALERT_REQ_C_HCS_PD_FRLIFTMLFNC,     (U1)1U,     (U4)0x00000800U    },
    {    (U2)ALERT_CH_B_BVOOPE,             (U1)ALERT_REQ_B_BVOOPE_OPERATING,       (U1)5U,     (U4)0x00800000U    },
    {    (U2)ALERT_CH_B_THESEN,             (U1)ALERT_REQ_B_THESEN_SENOFF,          (U1)11U,    (U4)0x00008000U    },
    {    (U2)ALERT_CH_B_THESEN,             (U1)ALERT_REQ_B_THESEN_SENON,           (U1)11U,    (U4)0x00010000U    },
    {    (U2)ALERT_CH_B_AVAS,               (U1)ALERT_REQ_B_AVAS_MALFUNC,           (U1)12U,    (U4)0x80000000U    },
    {    (U2)ALERT_CH_B_AVAS,               (U1)ALERT_REQ_B_AVAS_MALFUNC_PD,        (U1)12U,    (U4)0x80000000U    },
    {    (U2)ALERT_CH_B_WASLEV,             (U1)ALERT_REQ_B_WASLEV_TT_PD_ON,        (U1)13U,    (U4)0x04000000U    },
    {    (U2)ALERT_CH_B_WASLEV,             (U1)ALERT_REQ_B_WASLEV_PD_ON,           (U1)13U,    (U4)0x04000000U    },
    {    (U2)ALERT_CH_B_ALOA2,              (U1)ALERT_REQ_B_ALOA2_PARK_LT,          (U1)31U,    (U4)0x00000008U    },
    {    (U2)ALERT_CH_B_ALOA2,              (U1)ALERT_REQ_B_ALOA2_RUN_LT,           (U1)31U,    (U4)0x00000010U    },
    {    (U2)ALERT_CH_H_TVPSOF,             (U1)ALERT_REQ_H_TVPSOF_STOPPOW,         (U1)37U,    (U4)0x00000020U    },
    {    (U2)ALERT_CH_B_PBD,                (U1)ALERT_REQ_B_PBD_OPENVIO,            (U1)37U,    (U4)0x00004000U    },
    {    (U2)ALERT_CH_B_RPWSEA,             (U1)ALERT_REQ_B_RPWSEA_IMPSBLUSE,       (U1)39U,    (U4)0x01000000U    }
};

const ST_ALERT_REQBIT   st_gp_HMIPUTXTREQBIT_SLOTB[HMIPUTXTCFG_IF_SLOTB_NUM] = {
    {    (U2)ALERT_CH_C_EPB_WRN_BAT,        (U1)ALERT_REQ_C_EPB_WRN_BAT_STOPPED,    (U1)1U,     (U4)0x04000000U    },
    {    (U2)ALERT_CH_C_BRKHLD_WRN,         (U1)ALERT_REQ_C_BRKHLD_WRN_WRN1,        (U1)4U,     (U4)0x00200000U    },
    {    (U2)ALERT_CH_C_BRKHLD_WRN,         (U1)ALERT_REQ_C_BRKHLD_WRN_ACT,         (U1)4U,     (U4)0x01000000U    },
    {    (U2)ALERT_CH_C_BRKHLD_WRN,         (U1)ALERT_REQ_C_BRKHLD_WRN_UNAVBL2,     (U1)4U,     (U4)0x04000000U    },
    {    (U2)ALERT_CH_C_BRKHLD_WRN,         (U1)ALERT_REQ_C_BRKHLD_WRN_UNAVBL1,     (U1)4U,     (U4)0x10000000U    },
    {    (U2)ALERT_CH_C_BRKHLD_WRN,         (U1)ALERT_REQ_C_BRKHLD_WRN_WRN2,        (U1)4U,     (U4)0x40000000U    },
    {    (U2)ALERT_CH_C_BRKHLD_WRN,         (U1)ALERT_REQ_C_BRKHLD_WRN_UNAVBL3,     (U1)4U,     (U4)0x80000000U    },
    {    (U2)ALERT_CH_C_BRKHLD_WRN,         (U1)ALERT_REQ_C_BRKHLD_WRN_UNAVBL4,     (U1)6U,     (U4)0x00000002U    },
    {    (U2)ALERT_CH_C_EPB_WRN_BAT,        (U1)ALERT_REQ_C_EPB_WRN_BAT_AUTOLOCK,   (U1)8U,     (U4)0x00000800U    },
    {    (U2)ALERT_CH_C_ABS_PD,             (U1)ALERT_REQ_C_ABS_PD_MALFUNC,         (U1)9U,     (U4)0x02000000U    },
    {    (U2)ALERT_CH_C_MCBW,               (U1)ALERT_REQ_C_MCBW_MALFUNC,           (U1)10U,    (U4)0x00000200U    },
    {    (U2)ALERT_CH_C_MCBW,               (U1)ALERT_REQ_C_MCBW_MALFUNC_RW,        (U1)10U,    (U4)0x00000200U    },
    {    (U2)ALERT_CH_B_AIRBAG,             (U1)ALERT_REQ_B_AIRBAG_MALFUNC,         (U1)12U,    (U4)0x00000100U    },
    {    (U2)ALERT_CH_C_BRKHLD_WRN,         (U1)ALERT_REQ_C_BRKHLD_WRN_DEACT2,      (U1)13U,    (U4)0x00008000U    },
    {    (U2)ALERT_CH_C_BRKHLD_WRN,         (U1)ALERT_REQ_C_BRKHLD_WRN_MAINT1,      (U1)13U,    (U4)0x00020000U    },
    {    (U2)ALERT_CH_C_BRKHLD_WRN,         (U1)ALERT_REQ_C_BRKHLD_WRN_MALFNC1,     (U1)13U,    (U4)0x00080000U    },
    {    (U2)ALERT_CH_C_BRKHLD_WRN,         (U1)ALERT_REQ_C_BRKHLD_WRN_MALFNC2,     (U1)13U,    (U4)0x00100000U    },
    {    (U2)ALERT_CH_C_BRKHLD_WRN,         (U1)ALERT_REQ_C_BRKHLD_WRN_MAINT3,      (U1)13U,    (U4)0x01000000U    },
    {    (U2)ALERT_CH_C_BRKHLD_WRN,         (U1)ALERT_REQ_C_BRKHLD_WRN_MAINT2,      (U1)13U,    (U4)0x02000000U    },
    {    (U2)ALERT_CH_C_BRKHLD_WRN,         (U1)ALERT_REQ_C_BRKHLD_WRN_DEACT1,      (U1)14U,    (U4)0x00000004U    },
    {    (U2)ALERT_CH_C_AVSWAR,             (U1)ALERT_REQ_C_AVSWAR_MALFUNC,         (U1)18U,    (U4)0x00200000U    },
    {    (U2)ALERT_CH_C_EPB_WRN_IG,         (U1)ALERT_REQ_C_EPB_WRN_IG_UNRELABLE,   (U1)24U,    (U4)0x00000010U    },
    {    (U2)ALERT_CH_C_EPB_WRN_BAT,        (U1)ALERT_REQ_C_EPB_WRN_BAT_ADVICE1,    (U1)24U,    (U4)0x00000020U    },
    {    (U2)ALERT_CH_C_EPB_WRN_BAT,        (U1)ALERT_REQ_C_EPB_WRN_BAT_ADVICE2,    (U1)24U,    (U4)0x00000040U    },
    {    (U2)ALERT_CH_C_EPB_WRN_IG,         (U1)ALERT_REQ_C_EPB_WRN_IG_LOCK,        (U1)24U,    (U4)0x00000080U    },
    {    (U2)ALERT_CH_C_EPB_WRN_IG,         (U1)ALERT_REQ_C_EPB_WRN_IG_ADVICE1,     (U1)24U,    (U4)0x00000100U    },
    {    (U2)ALERT_CH_C_EPB_WRN_IG,         (U1)ALERT_REQ_C_EPB_WRN_IG_ADVICE2,     (U1)24U,    (U4)0x00000200U    },
    {    (U2)ALERT_CH_C_EPB_WRN_BAT,        (U1)ALERT_REQ_C_EPB_WRN_BAT_NOTUSE1,    (U1)24U,    (U4)0x00000400U    },
    {    (U2)ALERT_CH_C_EPB_WRN_BAT,        (U1)ALERT_REQ_C_EPB_WRN_BAT_NOTUSE2,    (U1)24U,    (U4)0x00000800U    },
    {    (U2)ALERT_CH_C_EPB_WRN_IG,         (U1)ALERT_REQ_C_EPB_WRN_IG_MALFUNC,     (U1)24U,    (U4)0x00001000U    },
    {    (U2)ALERT_CH_C_EPB_WRN_IG,         (U1)ALERT_REQ_C_EPB_WRN_IG_ACTIVE,      (U1)24U,    (U4)0x00002000U    },
    {    (U2)ALERT_CH_C_EPB_WRN_IG,         (U1)ALERT_REQ_C_EPB_WRN_IG_DEACTIVE,    (U1)24U,    (U4)0x00004000U    },
    {    (U2)ALERT_CH_B_PBDKS,              (U1)ALERT_REQ_B_PBDKS_UNAVLBL,          (U1)24U,    (U4)0x00200000U    },
    {    (U2)ALERT_CH_B_PBDKS,              (U1)ALERT_REQ_B_PBDKS_MALFUNC,          (U1)24U,    (U4)0x00400000U    },
    {    (U2)ALERT_CH_B_SPAT,               (U1)ALERT_REQ_B_SPAT_MALFUNC,           (U1)24U,    (U4)0x20000000U    },
    {    (U2)ALERT_CH_C_AVSWAR,             (U1)ALERT_REQ_C_AVSWAR_MALFUNC_RW,      (U1)25U,    (U4)0x01000000U    },
    {    (U2)ALERT_CH_B_PEDPRO,             (U1)ALERT_REQ_B_PEDPRO_DIAGDTRMN,       (U1)32U,    (U4)0x00000002U    },
    {    (U2)ALERT_CH_B_PEDPRO,             (U1)ALERT_REQ_B_PEDPRO_PUHDVCACT,       (U1)32U,    (U4)0x00000004U    },
    {    (U2)ALERT_CH_C_DRS,                (U1)ALERT_REQ_C_DRS_TESTMODE,           (U1)34U,    (U4)0x00000080U    },
    {    (U2)ALERT_CH_C_DRS,                (U1)ALERT_REQ_C_DRS_MALFUNC_RW,         (U1)36U,    (U4)0x08000000U    },
    {    (U2)ALERT_CH_C_DRS,                (U1)ALERT_REQ_C_DRS_MALFUNC,            (U1)36U,    (U4)0x08000000U    }
};

const ST_ALERT_REQBIT   st_gp_HMIPUTXTREQBIT_SLOTC[HMIPUTXTCFG_IF_SLOTC_NUM] = {
    {    (U2)ALERT_CH_O_FNCLIM,             (U1)ALERT_REQ_O_FNCLIM_WRN_POW,         (U1)0U,     (U4)0x00000100U    },
    {    (U2)ALERT_CH_O_FNCLIM,             (U1)ALERT_REQ_O_FNCLIM_WRN_TMP,         (U1)0U,     (U4)0x00000200U    },
    {    (U2)ALERT_CH_H_BATINS_PD,          (U1)ALERT_REQ_H_BATINS_PD_DIAGNOSIS,    (U1)0U,     (U4)0x08000000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_ASSIST_STOP,   (U1)2U,     (U4)0x00000008U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_POWSTOP,       (U1)2U,     (U4)0x00000400U    },
    {    (U2)ALERT_CH_H_ACCHOL,             (U1)ALERT_REQ_H_ACCHOL_EVSYSOVHT,       (U1)2U,     (U4)0x02000000U    },
    {    (U2)ALERT_CH_H_ACCHOL,             (U1)ALERT_REQ_H_ACCHOL_FCVSYSOVHT,      (U1)2U,     (U4)0x04000000U    },
    {    (U2)ALERT_CH_H_SYSMAL_PD2,         (U1)ALERT_REQ_H_SYSMAL_PD2_IND15,       (U1)2U,     (U4)0x80000000U    },
    {    (U2)ALERT_CH_H_ACCHOL,             (U1)ALERT_REQ_H_ACCHOL_HVSYSOVHT,       (U1)3U,     (U4)0x00000008U    },
    {    (U2)ALERT_CH_H_SYSMAL_PD2,         (U1)ALERT_REQ_H_SYSMAL_PD2_IND7,        (U1)3U,     (U4)0x00000020U    },
    {    (U2)ALERT_CH_H_SYSMAL_PD2,         (U1)ALERT_REQ_H_SYSMAL_PD2_IND14,       (U1)3U,     (U4)0x00000100U    },
    {    (U2)ALERT_CH_H_SYSMAL_PD2,         (U1)ALERT_REQ_H_SYSMAL_PD2_IND2,        (U1)3U,     (U4)0x00000200U    },
    {    (U2)ALERT_CH_H_SYSMAL_PD2,         (U1)ALERT_REQ_H_SYSMAL_PD2_IND6,        (U1)4U,     (U4)0x00010000U    },
    {    (U2)ALERT_CH_H_BATINS_PD,          (U1)ALERT_REQ_H_BATINS_PD_UNAVAILABL,   (U1)7U,     (U4)0x00000100U    },
    {    (U2)ALERT_CH_H_DRIPOW,             (U1)ALERT_REQ_H_DRIPOW_OVHT_CHN,        (U1)8U,     (U4)0x00000010U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_ASSIST_CNTI,   (U1)8U,     (U4)0x00002000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_EV_STOP,       (U1)8U,     (U4)0x00004000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_ENGSTOP,       (U1)8U,     (U4)0x00020000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_HV_STOP,       (U1)8U,     (U4)0x02000000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_ASSIST_LMT,    (U1)9U,     (U4)0x00000010U    },
    {    (U2)ALERT_CH_H_SYSMAL_PD2,         (U1)ALERT_REQ_H_SYSMAL_PD2_IND3,        (U1)9U,     (U4)0x00000020U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_POWLIMIT,      (U1)9U,     (U4)0x00000080U    },
    {    (U2)ALERT_CH_H_SYSMAL_PD2,         (U1)ALERT_REQ_H_SYSMAL_PD2_IND8,        (U1)9U,     (U4)0x00000100U    },
    {    (U2)ALERT_CH_H_SYSMAL_PD2,         (U1)ALERT_REQ_H_SYSMAL_PD2_IND9,        (U1)9U,     (U4)0x00000200U    },
    {    (U2)ALERT_CH_H_SYSMAL_PD2,         (U1)ALERT_REQ_H_SYSMAL_PD2_IND10,       (U1)9U,     (U4)0x00000400U    },
    {    (U2)ALERT_CH_H_SYSMAL_PD2,         (U1)ALERT_REQ_H_SYSMAL_PD2_IND13,       (U1)9U,     (U4)0x00000800U    },
    {    (U2)ALERT_CH_H_SYSMAL_PD2,         (U1)ALERT_REQ_H_SYSMAL_PD2_IND11,       (U1)9U,     (U4)0x00001000U    },
    {    (U2)ALERT_CH_H_SYSMAL_PD2,         (U1)ALERT_REQ_H_SYSMAL_PD2_IND12,       (U1)9U,     (U4)0x00002000U    },
    {    (U2)ALERT_CH_H_DRIPOW,             (U1)ALERT_REQ_H_DRIPOW_BATLOW_CHN,      (U1)9U,     (U4)0x00400000U    },
    {    (U2)ALERT_CH_H_SYSMAL_PD2,         (U1)ALERT_REQ_H_SYSMAL_PD2_IND1,        (U1)10U,    (U4)0x00800000U    },
    {    (U2)ALERT_CH_H_SYSMAL_PD2,         (U1)ALERT_REQ_H_SYSMAL_PD2_IND5,        (U1)11U,    (U4)0x00000040U    },
    {    (U2)ALERT_CH_H_SYSMAL_PD2,         (U1)ALERT_REQ_H_SYSMAL_PD2_IND4,        (U1)11U,    (U4)0x01000000U    },
    {    (U2)ALERT_CH_H_DRIPOW,             (U1)ALERT_REQ_H_DRIPOW_OTHER_CHN,       (U1)12U,    (U4)0x00000010U    },
    {    (U2)ALERT_CH_H_TOWWAR,             (U1)ALERT_REQ_H_TOWWAR_MLFNC_EV,        (U1)12U,    (U4)0x00000040U    },
    {    (U2)ALERT_CH_H_TOWWAR,             (U1)ALERT_REQ_H_TOWWAR_MLFNC_FCV,       (U1)12U,    (U4)0x00000080U    },
    {    (U2)ALERT_CH_H_DRIPOW,             (U1)ALERT_REQ_H_DRIPOW_OVHT,            (U1)12U,    (U4)0x00010000U    },
    {    (U2)ALERT_CH_H_DRIPOW,             (U1)ALERT_REQ_H_DRIPOW_BATLOW,          (U1)12U,    (U4)0x00020000U    },
    {    (U2)ALERT_CH_H_DRIPOW,             (U1)ALERT_REQ_H_DRIPOW_OTHER,           (U1)12U,    (U4)0x00040000U    },
    {    (U2)ALERT_CH_H_TOWWAR,             (U1)ALERT_REQ_H_TOWWAR_MLFNC_HV,        (U1)12U,    (U4)0x00100000U    },
    {    (U2)ALERT_CH_H_TOWWAR,             (U1)ALERT_REQ_H_TOWWAR_MLFNC_HV2,       (U1)12U,    (U4)0x00100000U    },
    {    (U2)ALERT_CH_H_BATINS_PD,          (U1)ALERT_REQ_H_BATINS_PD_EMERGENCY,    (U1)12U,    (U4)0x00800000U    },
    {    (U2)ALERT_CH_H_BATINS_PD,          (U1)ALERT_REQ_H_BATINS_PD_REQINSPECT,   (U1)12U,    (U4)0x10000000U    },
    {    (U2)ALERT_CH_H_REGBRA,             (U1)ALERT_REQ_H_REGBRA_MALFUNC,         (U1)25U,    (U4)0x00020000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_CAR_STOP,      (U1)26U,    (U4)0x00000100U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_CALL_DEALER,   (U1)26U,    (U4)0x00000200U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_LMT_SPD,       (U1)26U,    (U4)0x00000400U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_SPD_SNS_ERR,   (U1)26U,    (U4)0x00000800U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_CANT_SFT,      (U1)26U,    (U4)0x00001000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_OVRHEAT,       (U1)26U,    (U4)0x00002000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_SRT_UP_FAIL,   (U1)26U,    (U4)0x00004000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_RMV_HAND,      (U1)26U,    (U4)0x00008000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_COMM_ERR,      (U1)26U,    (U4)0x00010000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_NONSYNC_MOD,   (U1)26U,    (U4)0x00020000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_SELF_CALIB,    (U1)26U,    (U4)0x00040000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_RDY_DRIVE,     (U1)26U,    (U4)0x00080000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_SPDLIMIT,      (U1)26U,    (U4)0x00100000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_FURLMTSPD,     (U1)26U,    (U4)0x00200000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_CMAXSPDLMT,    (U1)26U,    (U4)0x00400000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_CMAXSPDFLMT,   (U1)26U,    (U4)0x00800000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_MAXLMTSOON,    (U1)26U,    (U4)0x01000000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_MAXFURLMT,     (U1)26U,    (U4)0x02000000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_STOPVEH,       (U1)26U,    (U4)0x04000000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_VEHUNAVAIL,    (U1)26U,    (U4)0x08000000U    },
    {    (U2)ALERT_CH_H_ONACCN,             (U1)ALERT_REQ_H_ONACCN_MALFUNC,         (U1)32U,    (U4)0x00100000U    },
    {    (U2)ALERT_CH_C_STEER_PD,           (U1)ALERT_REQ_C_STEER_PD_FCV_STOP,      (U1)33U,    (U4)0x08000000U    }
};

const ST_ALERT_REQBIT   st_gp_HMIPUTXTREQBIT_SLOTD[HMIPUTXTCFG_IF_SLOTD_NUM] = {
    {    (U2)ALERT_CH_O_CHAMAL,             (U1)ALERT_REQ_O_CHAMAL_MALFUNC,         (U1)2U,     (U4)0x00400000U    },
    {    (U2)ALERT_CH_O_CHAMAL,             (U1)ALERT_REQ_O_CHAMAL_MALFUNC_BZ,      (U1)2U,     (U4)0x00400000U    },
    {    (U2)ALERT_CH_D_SBW_PD_RIS,         (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_12,      (U1)4U,     (U4)0x00000004U    },
    {    (U2)ALERT_CH_D_SBW_PD_RIS,         (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_35,      (U1)4U,     (U4)0x00000008U    },
    {    (U2)ALERT_CH_D_SBW_PD_RIS,         (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_13,      (U1)4U,     (U4)0x00000010U    },
    {    (U2)ALERT_CH_D_SBW_PD_RIS,         (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_16,      (U1)4U,     (U4)0x00000020U    },
    {    (U2)ALERT_CH_D_SBW_PD_RIS,         (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_19,      (U1)4U,     (U4)0x00000040U    },
    {    (U2)ALERT_CH_D_SBW_PD_RIS,         (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_17,      (U1)4U,     (U4)0x00000080U    },
    {    (U2)ALERT_CH_D_SBW_PD_NSFT,        (U1)ALERT_REQ_D_SBW_PD_NSFT_MSG_21,     (U1)4U,     (U4)0x00000100U    },
    {    (U2)ALERT_CH_D_SBW_PD_RIS,         (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_20,      (U1)4U,     (U4)0x00000200U    },
    {    (U2)ALERT_CH_D_SBW_PD_RIS,         (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_18,      (U1)4U,     (U4)0x00000400U    },
    {    (U2)ALERT_CH_D_SBW_PD_RIS,         (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_36,      (U1)4U,     (U4)0x00000800U    },
    {    (U2)ALERT_CH_D_SBW_PD_NSFT,        (U1)ALERT_REQ_D_SBW_PD_NSFT_MSG_24,     (U1)4U,     (U4)0x00001000U    },
    {    (U2)ALERT_CH_D_SBW_PD_ACCN,        (U1)ALERT_REQ_D_SBW_PD_ACCN_MSG_32,     (U1)4U,     (U4)0x00004000U    },
    {    (U2)ALERT_CH_D_SBW_PD_DAP,         (U1)ALERT_REQ_D_SBW_PD_DAP_MSG_29,      (U1)4U,     (U4)0x00008000U    },
    {    (U2)ALERT_CH_D_SBW_PD_RIS,         (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_14,      (U1)4U,     (U4)0x00020000U    },
    {    (U2)ALERT_CH_D_SBW_PD_RIS,         (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_33,      (U1)5U,     (U4)0x00000080U    },
    {    (U2)ALERT_CH_D_SBW_PD_RIS,         (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_39,      (U1)6U,     (U4)0x00000004U    },
    {    (U2)ALERT_CH_D_SBW_PD_RIS,         (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_11,      (U1)6U,     (U4)0x00000008U    },
    {    (U2)ALERT_CH_D_SBW_PD_RIS,         (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_08,      (U1)6U,     (U4)0x00010000U    },
    {    (U2)ALERT_CH_D_SBW_PD_RIS,         (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_38,      (U1)6U,     (U4)0x00100000U    },
    {    (U2)ALERT_CH_O_CHAMAL,             (U1)ALERT_REQ_O_CHAMAL_INSPECTION,      (U1)7U,     (U4)0x80000000U    },
    {    (U2)ALERT_CH_O_CHAMAL,             (U1)ALERT_REQ_O_CHAMAL_INSPECTION_BZ,   (U1)7U,     (U4)0x80000000U    },
    {    (U2)ALERT_CH_D_SBW_PD_PSWF,        (U1)ALERT_REQ_D_SBW_PD_PSWF_MSG_04,     (U1)8U,     (U4)0x00000100U    },
    {    (U2)ALERT_CH_D_SBW_PD_SFTF,        (U1)ALERT_REQ_D_SBW_PD_SFTF_MSG_07,     (U1)8U,     (U4)0x00100000U    },
    {    (U2)ALERT_CH_D_SBW_PD_ACTF,        (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02,     (U1)8U,     (U4)0x00400000U    },
    {    (U2)ALERT_CH_D_SBW_PD_SBWF,        (U1)ALERT_REQ_D_SBW_PD_SBWF_MSG_05,     (U1)8U,     (U4)0x00800000U    },
    {    (U2)ALERT_CH_D_SBW_PD_LBAT,        (U1)ALERT_REQ_D_SBW_PD_LBAT_MSG_03,     (U1)8U,     (U4)0x04000000U    },
    {    (U2)ALERT_CH_D_SBW_PD_PREQ,        (U1)ALERT_REQ_D_SBW_PD_PREQ_MSG_26,     (U1)8U,     (U4)0x20000000U    },
    {    (U2)ALERT_CH_M_T120,               (U1)ALERT_REQ_M_T120_TT_PD_ON,          (U1)9U,     (U4)0x00040000U    },
    {    (U2)ALERT_CH_M_T120,               (U1)ALERT_REQ_M_T120_PRMRYCHK_PD,       (U1)9U,     (U4)0x00040000U    },
    {    (U2)ALERT_CH_D_SBW_PD_SFML,        (U1)ALERT_REQ_D_SBW_PD_SFML_MSG_28,     (U1)11U,    (U4)0x00004000U    },
    {    (U2)ALERT_CH_B_GRISHU,             (U1)ALERT_REQ_B_GRISHU_MALFUNC,         (U1)12U,    (U4)0x00000800U    },
    {    (U2)ALERT_CH_D_SBW_PD_SFML,        (U1)ALERT_REQ_D_SBW_PD_SFML_MSG_27,     (U1)12U,    (U4)0x00001000U    },
    {    (U2)ALERT_CH_D_SBW_PD_CHK,         (U1)ALERT_REQ_D_SBW_PD_CHK_MSG_06,      (U1)12U,    (U4)0x00002000U    },
    {    (U2)ALERT_CH_D_SBW_PD_CHK,         (U1)ALERT_REQ_D_SBW_PD_CHK_MSG6_SBW8,   (U1)12U,    (U4)0x00002000U    },
    {    (U2)ALERT_CH_D_SBW_PD_CHK,         (U1)ALERT_REQ_D_SBW_PD_CHK_MSG6_SBW9,   (U1)12U,    (U4)0x00002000U    },
    {    (U2)ALERT_CH_D_SBW_PD_RIS,         (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_40,      (U1)24U,    (U4)0x00080000U    },
    {    (U2)ALERT_CH_D_SBW_PD_SILUA,       (U1)ALERT_REQ_D_SBW_PD_SILUA_MSG_41,    (U1)24U,    (U4)0x00100000U    },
    {    (U2)ALERT_CH_B_ESWUOC_PDB,         (U1)ALERT_REQ_B_ESWUOC_PDB_RHDSHOCK,    (U1)25U,    (U4)0x00000008U    },
    {    (U2)ALERT_CH_B_ESWUOC_PDB,         (U1)ALERT_REQ_B_ESWUOC_PDB_LHDSHOCK,    (U1)25U,    (U4)0x00000010U    },
    {    (U2)ALERT_CH_B_ESWUOC_PD,          (U1)ALERT_REQ_B_ESWUOC_PD_STPATUNLCK,   (U1)25U,    (U4)0x00000020U    },
    {    (U2)ALERT_CH_B_ESWUOC_PD,          (U1)ALERT_REQ_B_ESWUOC_PD_SPDATUNLCK,   (U1)25U,    (U4)0x00000040U    },
    {    (U2)ALERT_CH_B_ESWUOC_PDB,         (U1)ALERT_REQ_B_ESWUOC_PDB_SYSMLFNC,    (U1)25U,    (U4)0x00000080U    },
    {    (U2)ALERT_CH_B_ESWUOC_PD,          (U1)ALERT_REQ_B_ESWUOC_PD_UNLTCHFL,     (U1)25U,    (U4)0x00000100U    },
    {    (U2)ALERT_CH_H_LEAUNF,             (U1)ALERT_REQ_H_LEAUNF_UNCOMP,          (U1)34U,    (U4)0x00000100U    },
    {    (U2)ALERT_CH_D_SBW_PD_SFPF,        (U1)ALERT_REQ_D_SBW_PD_SFPF_MSG_42,     (U1)34U,    (U4)0x00000400U    }
};

/* const ST_ALERT_REQBIT   st_gp_HMIPUTXTREQBIT_SLOTE[HMIPUTXTCFG_IF_SLOTE_NUM] = { */
/* }; */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*===================================================================================================================================*/
/*  U2    u2_g_HmiputxtSizeReqbit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u2_t_ret : array element number                                                                                  */
/*===================================================================================================================================*/
U2 u2_g_HmiputxtSizeReqbit(void){

    U2 u2_t_ret;

    u2_t_ret = (U2)(sizeof(st_gp_HMIPUTXTREQBIT) / sizeof(st_gp_HMIPUTXTREQBIT[0]));

    return (u2_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    07/16/2017  TA       New.                                                                                               */
/*  1.0.1    04/23/2020  TH       Setting for 800B CV.                                                                               */
/*  1.2.0    09/09/2020  TH       Setting for 800B CV-R.                                                                             */
/*  1.3.0    01/06/2021  TH       Setting for 800B 1A.                                                                               */
/*  1.4.0    06/04/2021  TH       Setting for 22-24FGM CV.                                                                           */
/*  1.6.0    08/01/2024  TH       Change how to get alert table requests.                                                            */
/*  1.7.0    10/25/2024  RS       Setting for BEV System_Consideration_1                                                             */
/*  1.8.0    06/23/2025  HY       Setting for BEV System_Consideration_2                                                             */
/*  1.9.0    07/07/2025  KT       Setting for BEV System_Consideration_2 (Delete for CONTDISP2)                                      */
/*  1.10.0   01/07/2026  SN       Setting for BEV FF2                                                                                */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  19PFv3-1 02/20/2024  GM       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-2 07/10/2024  YR       Added config for HCS                                                                               */
/*  19PFv3-3 09/04/2024  JMH      Changed config for 19PFv3 R2.0 (Added config for XMODE and DRIMOD)                                 */
/*  19PFv3-4 10/23/2024  YR       Changed config for 19PFv3 R2.1 (S_EDSS)                                                            */
/*  19PFv3-5 11/25/2024  JMH      Changed config for 19PFv3 R3 (S_LTA)                                                               */
/*  19PFv3-6 11/25/2024  YR       Deleted TRCOFF config for 19PFv3 R3                                                                */
/*  19PFv3-7 12/09/2024  KH       Deleted config for 19PFv3 R3.0 (M_VCOPE)                                                           */
/*  19PFv3-8 03/20/2025  SH       Added config for BATTRW                                                                            */
/*  19PFv3-9 05/07/2025  JMH      Changed config for 19PFv3 310D (D_TMWRN)                                                           */
/*  BEV-1    10/25/2024  RS       Change for BEV System_Consideration_1.(MET-H_DRIPOW-CSTD-1-00-A-C0)                                */
/*  BEV-2    10/30/2024  RS       Change for BEV System_Consideration_1.(MET-H_SYSMAL-CSTD-2-00-A-C0)                                */
/*  BEV-3    10/31/2024  KO       Change for BEV System_Consideration_1.(MET-C_TRCOFF-CSTD-1-00-A-C0)                                */
/*  BEV-4    11/12/2024  KO       Change for BEV System_Consideration_1.(MET-C_BRLV-CSTD-2-00-A-C0)                                  */
/*  BEV-5    11/25/2024  KO       Change for BEV System_Consideration_1.(MET-C_ECB-CSTD-1-00-A-C0 / MET-C_EPB-CSTD-1-00-A-C0)        */
/*  BEV-6     2/10/2025  HF       Change for BEV System_Consideration_1.(MET-C_BRK-CSTD-2-00-A-C0)                                   */
/*  BEV-7     2/10/2025  HF       Change for BEV System_Consideration_1.(MET-D_SBW-CSTD-3-00-A-C0)                                   */
/*  BEV-8     6/20/2025  KO       Change for BEV System_Consideration_2.(MET-O_PDSMAL-CSTD-0-00-A-C0)                                */
/*  BEV-9    06/23/2025  HY       Change for BEV System_Consideration_2.(MET-S_ADMID-CSTD-0-02-A-C0 / MET-S_ADTT-CSTD-0-02-A-C0)     */
/*  BEV-10    7/07/2025  KT       Change for BEV System_Consideration_2.(MET-M_CONTDISP2-CSTD-0010-C0)                               */
/*  BEV-11   12/05/2025  KH       Change for BEV System_Consideration_ADAS.(MET-C_STEER-CSTD-0-02-B-C0)                              */
/*  BEV-12   12/19/2025  KH       Update for BEV System_Consideration_ADAS.(B_PBDKS / H_LEAUNF)                                      */
/*  BEV-13   01/07/2026  SN       Change for BEV FF2.(MET-O_FNCLIM-CSTD-0-00-A-C0)                                                   */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TH   = Takahiro Hirano, Denso Techno                                                                                           */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*  * YR   = Yhana Regalario, DTPH                                                                                                   */
/*  * JMH  = James Michael Hilarion, DTPH                                                                                            */
/*  * SH   = Sae Hirose, Denso Techno                                                                                                */
/*  * RS   = Ryuki Sako,      Denso Techno                                                                                           */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*  * HF   = Hinari Fukamachi,KSE                                                                                                    */
/*  * HY   = Haruki Yagi, KSE                                                                                                        */
/*  * KT   = Kenta Takaji,    Denso Techno                                                                                           */
/*  * KH   = Kiko Huerte,     DTPH                                                                                                   */
/*  * SN   = Shizuka Nakajima, KSE                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
