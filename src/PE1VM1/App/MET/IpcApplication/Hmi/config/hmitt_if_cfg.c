/* 1.8.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Hmitt                                                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define HMITT_IF_CFG_C_MAJOR                  (1)
#define HMITT_IF_CFG_C_MINOR                  (8)
#define HMITT_IF_CFG_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "hmitt_cfg_private.h"
#include "hmitt_if_cfg.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((HMITT_IF_CFG_C_MAJOR != HMITT_H_MAJOR) || \
     (HMITT_IF_CFG_C_MINOR != HMITT_H_MINOR) || \
     (HMITT_IF_CFG_C_PATCH != HMITT_H_PATCH))
#error "hmitt_if_cfg.c and hmitt_if_cfg.h : source and header files are inconsistent!"
#endif

#if ((HMITT_IF_CFG_C_MAJOR != HMITT_IF_CFG_H_MAJOR) || \
     (HMITT_IF_CFG_C_MINOR != HMITT_IF_CFG_H_MINOR) || \
     (HMITT_IF_CFG_C_PATCH != HMITT_IF_CFG_H_PATCH))
#error "hmitt_if_cfg.c and hmitt__if_cfg.h : source and header files are inconsistent!"
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
const ST_ALERT_REQBIT   st_gp_HMITTREQBIT[HMITTCFG_IF_NUM] = {
    /*  u2_src_ch                     u1_src_act                           u1_dst_idx  u4_dst_bit                                                      */
    {  (U2)ALERT_CH_B_TTAIL,          (U1)ALERT_REQ_B_TTAIL_ON,                 (U1)0U,    u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_B_TRFOG,          (U1)ALERT_REQ_B_TRFOG_ON,                 (U1)0U,    u4_HMITT_HB1(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_B_TFFOG,          (U1)ALERT_REQ_B_TFFOG_ON,                 (U1)0U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_B_TBEAM12,        (U1)ALERT_REQ_B_TBEAM12_ON,               (U1)0U,    u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_B_PEDPRO,         (U1)ALERT_REQ_B_PEDPRO_DIAGDTRMN,         (U1)0U,    u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_B_PEDPRO,         (U1)ALERT_REQ_B_PEDPRO_PRIMARYCHK,        (U1)0U,    u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_B_PEDPRO,         (U1)ALERT_REQ_B_PEDPRO_PUHDVCACT,         (U1)0U,    u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_B_AIRBAG,         (U1)ALERT_REQ_B_AIRBAG_MALFUNC,           (U1)0U,    u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_B_AIRBAG,         (U1)ALERT_REQ_B_AIRBAG_PRMRYCHK,          (U1)0U,    u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P_AIRBAG)             },
    {  (U2)ALERT_CH_C_VSCOFF,         (U1)ALERT_REQ_C_VSCOFF_UNAVAILABLE,       (U1)0U,    u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_TRCOFF_TT,      (U1)ALERT_REQ_C_TRCOFF_TT_MALFUNC,        (U1)0U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_TPMS_TT,        (U1)ALERT_REQ_C_TPMS_TT_LOWPRE,           (U1)1U,    u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_TPMS_TT,        (U1)ALERT_REQ_C_TPMS_TT_INIT,             (U1)1U,    u4_HMITT_HB0(HMITT_BLINK_CO_0P50HZ__50P)                    },
    {  (U2)ALERT_CH_C_TPMS_TT,        (U1)ALERT_REQ_C_TPMS_TT_STOP,             (U1)1U,    u4_HMITT_HB0(HMITT_BLINK_CO_1P00HZ__50P_TPMS)               },
    {  (U2)ALERT_CH_C_TPMS_TT,        (U1)ALERT_REQ_C_TPMS_TT_TEST,             (U1)1U,    u4_HMITT_HB0(HMITT_BLINK_CO_4P00HZ__50P_TPMS)               },
    {  (U2)ALERT_CH_C_TPMS_TT,        (U1)ALERT_REQ_C_TPMS_TT_MALFUNC,          (U1)1U,    u4_HMITT_HB0(HMITT_BLINK_CO_1P00HZ__50P_63TIMS_E__ON)       },
    {  (U2)ALERT_CH_C_SLIP,           (U1)ALERT_REQ_C_SLIP_MALFUNC,             (U1)1U,    u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_SLIP,           (U1)ALERT_REQ_C_SLIP_MALFUNC_RW,          (U1)1U,    u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_SLIP,           (U1)ALERT_REQ_C_SLIP_OPERATING,           (U1)1U,    u4_HMITT_HB3(HMITT_BLINK_CO_2P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_SLIP,           (U1)ALERT_REQ_C_SLIP_TESTMODE,            (U1)1U,    u4_HMITT_HB3(HMITT_BLINK_CO_4P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_STEER_TT,       (U1)ALERT_REQ_C_STEER_TT_ON_R,            (U1)1U,    u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_STEER_TT,       (U1)ALERT_REQ_C_STEER_TT_FLASH_4HZ,       (U1)1U,    u4_HMITT_HB4(HMITT_BLINK_CO_4P00HZ__50P_STEER)              },
    {  (U2)ALERT_CH_C_STEER_TT,       (U1)ALERT_REQ_C_STEER_TT_ON_A,            (U1)1U,    u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_EPB_TT_PKB,     (U1)ALERT_REQ_C_EPB_TT_PKB_TT_ON,         (U1)1U,    u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_EPB_TT_PKB,     (U1)ALERT_REQ_C_EPB_TT_PKB_FLASH_1HZ,     (U1)1U,    u4_HMITT_HB6(HMITT_BLINK_CO_1P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_EPB_TT_PKB,     (U1)ALERT_REQ_C_EPB_TT_PKB_FLASH_2HZ,     (U1)1U,    u4_HMITT_HB6(HMITT_BLINK_CO_2P00HZ__50P_EPB)                },
    {  (U2)ALERT_CH_C_EPB_TT_PKB,     (U1)ALERT_REQ_C_EPB_TT_PKB_FLASH_4HZ,     (U1)1U,    u4_HMITT_HB6(HMITT_BLINK_CO_4P00HZ__50P_EPB)                },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_MALFUNC,              (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_MFNC_RW,              (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_MFNC_DISP,            (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_MFNC_DISP_RW,         (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_UNAVAILABL,           (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_UNABL_RW,             (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_UNABL_DISP,           (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_UNABL_DISP_RW,        (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_LERNING1,             (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_1P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_LNG1_DISP,            (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_1P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_LNG1_DISP_RW,         (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_1P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_TESTMODE,             (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_4P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_TM_DISP,              (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_4P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_TM_DISP_RW,           (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_4P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_LERNING2,             (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_4P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_LNG2_DISP,            (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_4P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_ECB,            (U1)ALERT_REQ_C_ECB_LNG2_DISP_RW,         (U1)1U,    u4_HMITT_HB7(HMITT_BLINK_CO_4P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_BRLV_2_WRN,     (U1)ALERT_REQ_C_BRLV_2_WRN_MALFUNC,       (U1)2U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_BRK_1,          (U1)ALERT_REQ_C_BRK_1_ON,                 (U1)2U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_BRK_1,          (U1)ALERT_REQ_C_BRK_1_ON_MLFNC,           (U1)2U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_BRK_1,          (U1)ALERT_REQ_C_BRK_1_ON_RW,              (U1)2U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_BRK_1,          (U1)ALERT_REQ_C_BRK_1_WRN,                (U1)2U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_BRK_0,          (U1)ALERT_REQ_C_BRK_0_LOW,                (U1)2U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_BRK_0,          (U1)ALERT_REQ_C_BRK_0_TMODE,              (U1)2U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_BRPADW ,        (U1)ALERT_REQ_C_BRPADW_MALFUNC,           (U1)2U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_BRKHLD_STBY,    (U1)ALERT_REQ_C_BRKHLD_STBY_ON,           (U1)3U,    u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_BRKHLD_HLD,     (U1)ALERT_REQ_C_BRKHLD_HLD_ON,            (U1)3U,    u4_HMITT_HB1(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_BRKHLD_HLD,     (U1)ALERT_REQ_C_BRKHLD_HLD_FLASH,         (U1)3U,    u4_HMITT_HB1(HMITT_BLINK_CO_2P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_ABS_TT,         (U1)ALERT_REQ_C_ABS_TT_ON,                (U1)3U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_ABS_TT,         (U1)ALERT_REQ_C_ABS_TT_ON_RW,             (U1)3U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_ABS_TT,         (U1)ALERT_REQ_C_ABS_TT_FLASH_1HZ,         (U1)3U,    u4_HMITT_HB2(HMITT_BLINK_CO_1P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_ABS_TT,         (U1)ALERT_REQ_C_ABS_TT_FLASH_4HZ,         (U1)3U,    u4_HMITT_HB2(HMITT_BLINK_CO_4P00HZ__50P)                    },
    {  (U2)ALERT_CH_S_ITS_TT,         (U1)ALERT_REQ_S_ITS_TT_V2R,               (U1)4U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ITS_TT,         (U1)ALERT_REQ_S_ITS_TT_V2V,               (U1)4U,    u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ITS_TT,         (U1)ALERT_REQ_S_ITS_TT_V2RV2V,            (U1)4U,    u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_PLUSSP,         (U1)ALERT_REQ_S_PLUSSP_SUPPORT_ON,        (U1)4U,    u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_PCS1_TT,        (U1)ALERT_REQ_S_PCS1_TT_MALFUNC,          (U1)4U,    u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_PCS1_TT,        (U1)ALERT_REQ_S_PCS1_TT_CNF_MD,           (U1)4U,    u4_HMITT_HB6(HMITT_BLINK_CO_0P50HZ__50P)                    },
    {  (U2)ALERT_CH_S_MWL_TT_IND,     (U1)ALERT_REQ_S_MWL_TT_IND_ON,            (U1)4U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_LTA_2_TT,       (U1)ALERT_REQ_S_LTA_2_TT_STNDBY,          (U1)5U,    u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_LTA_2_TT,       (U1)ALERT_REQ_S_LTA_2_TT_CTRL,            (U1)5U,    u4_HMITT_HB1(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_LTA_2_TT,       (U1)ALERT_REQ_S_LTA_2_TT_MLFNC,           (U1)5U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_LDA_TT_LDA,     (U1)ALERT_REQ_S_LDA_TT_LDA_ON_W,          (U1)5U,    u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_LDA_TT_LDA,     (U1)ALERT_REQ_S_LDA_TT_LDA_ON_R,          (U1)5U,    u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_LDA_TT_LDA,     (U1)ALERT_REQ_S_LDA_TT_LDA_ON_A,          (U1)5U,    u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_LDA_TT_LDA,     (U1)ALERT_REQ_S_LDA_TT_LDA_FLASH_A,       (U1)5U,    u4_HMITT_HB5(HMITT_BLINK_CO_1P00HZ__50P_S_OFF)              },
    {  (U2)ALERT_CH_S_LDA_TT_LDA,     (U1)ALERT_REQ_S_LDA_TT_LDA_LDAOFF_A,      (U1)5U,    u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_LDA_TT_LDA,     (U1)ALERT_REQ_S_LDA_TT_LDA_LDAOFF_W,      (U1)5U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ISA_TT,         (U1)ALERT_REQ_S_ISA_TT_ON_G,              (U1)6U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ISA_TT,         (U1)ALERT_REQ_S_ISA_TT_ON_A,              (U1)6U,    u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ISA_TT,         (U1)ALERT_REQ_S_ISA_TT_ON_W,              (U1)6U,    u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_CLESON_TT,      (U1)ALERT_REQ_S_CLESON_TT_ON,             (U1)6U,    u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_CLESON_TT,      (U1)ALERT_REQ_S_CLESON_TT_FLASH,          (U1)6U,    u4_HMITT_HB5(HMITT_BLINK_CO_2P50HZ__50P_CLESON)             },
    {  (U2)ALERT_CH_S_CLESON_TT,      (U1)ALERT_REQ_S_CLESON_TT_INDI_ON,        (U1)6U,    u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_LBW,            (U1)ALERT_REQ_H_LBW_PRMRYCHK,             (U1)6U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_LBW,            (U1)ALERT_REQ_H_LBW_LOWBATNOTE,           (U1)6U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_LBW,            (U1)ALERT_REQ_H_LBW_LOWBATWNG,            (U1)6U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_LBW,            (U1)ALERT_REQ_H_LBW_BATTEMPWNG,           (U1)6U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_SPDL_0_TT,      (U1)ALERT_REQ_H_SPDL_0_TT_SPEDAL,         (U1)7U,    u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ACC_TT_VD,      (U1)ALERT_REQ_S_ACC_TT_VD_ON_W_DST1,      (U1)7U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P_ACC_DST1_WHT)       },
    {  (U2)ALERT_CH_S_ACC_TT_VD,      (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST1,      (U1)7U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P_ACC_DST1_GRN)       },
    {  (U2)ALERT_CH_S_ACC_TT_VD,      (U1)ALERT_REQ_S_ACC_TT_VD_ON_W_DST2,      (U1)7U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P_ACC_DST2_WHT)       },
    {  (U2)ALERT_CH_S_ACC_TT_VD,      (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST2,      (U1)7U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P_ACC_DST2_GRN)       },
    {  (U2)ALERT_CH_S_ACC_TT_VD,      (U1)ALERT_REQ_S_ACC_TT_VD_ON_W_DST3,      (U1)7U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P_ACC_DST3_WHT)       },
    {  (U2)ALERT_CH_S_ACC_TT_VD,      (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST3,      (U1)7U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P_ACC_DST3_GRN)       },
    {  (U2)ALERT_CH_S_ACC_TT_VD,      (U1)ALERT_REQ_S_ACC_TT_VD_ON_W_DST4,      (U1)7U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P_ACC_DST4_WHT)       },
    {  (U2)ALERT_CH_S_ACC_TT_VD,      (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST4,      (U1)7U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P_ACC_DST4_GRN)       },
    {  (U2)ALERT_CH_S_FACTMD,         (U1)ALERT_REQ_S_FACTMD_FLASH_4HZ,         (U1)7U,    u4_HMITT_HB4(HMITT_BLINK_CO_4P00HZ__50P_FACTMD)             },
    {  (U2)ALERT_CH_S_FRADAR,         (U1)ALERT_REQ_S_FRADAR_FLASH_4HZ,         (U1)7U,    u4_HMITT_HB4(HMITT_BLINK_CO_4P00HZ__50P_FACTMD)             },
    {  (U2)ALERT_CH_S_FRRADA_TT,      (U1)ALERT_REQ_S_FRRADA_TT_FLASH_4HZ,      (U1)7U,    u4_HMITT_HB4(HMITT_BLINK_CO_4P00HZ__50P_FACTMD)             },
    {  (U2)ALERT_CH_S_CCS_TT_CC,      (U1)ALERT_REQ_S_CCS_TT_CC_ON_G,           (U1)7U,    u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ACC_TT_CC,      (U1)ALERT_REQ_S_ACC_TT_CC_ON_G,           (U1)7U,    u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_CCS_TT_CC,      (U1)ALERT_REQ_S_CCS_TT_CC_ON_Y,           (U1)7U,    u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ACC_TT_CC,      (U1)ALERT_REQ_S_ACC_TT_CC_ON_Y,           (U1)7U,    u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_CCS_TT_CC,      (U1)ALERT_REQ_S_CCS_TT_CC_ON_W_G,         (U1)7U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ACC_TT_CC,      (U1)ALERT_REQ_S_ACC_TT_CC_ON_W,           (U1)7U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ACC_TT_RCC,     (U1)ALERT_REQ_S_ACC_TT_RCC_ON_G,          (U1)8U,    u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ACC_TT_RCC,     (U1)ALERT_REQ_S_ACC_TT_RCC_ON_Y,          (U1)8U,    u4_HMITT_HB1(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ACC_TT_RCC,     (U1)ALERT_REQ_S_ACC_TT_RCC_ON_W,          (U1)8U,    u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_REASYS_TT,      (U1)ALERT_REQ_H_REASYS_TT_ON,             (U1)8U,    u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_REASYS_TT,      (U1)ALERT_REQ_H_REASYS_TT_FLASH,          (U1)8U,    u4_HMITT_HB4(HMITT_BLINK_CO_2P00HZ__50P)                    },
    {  (U2)ALERT_CH_H_EVMOD_TT,       (U1)ALERT_REQ_H_EVMOD_TT_ON,              (U1)8U,    u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_EVMOD_TT,       (U1)ALERT_REQ_H_EVMOD_TT_FLS_LOWBT_V,     (U1)8U,    u4_HMITT_HB5(HMITT_BLINK_SI_1P00HZ__50P_3TIMS_E_OFF_REQ3)   },
    {  (U2)ALERT_CH_H_EVMOD_TT,       (U1)ALERT_REQ_H_EVMOD_TT_FLS_SPD_V,       (U1)8U,    u4_HMITT_HB5(HMITT_BLINK_SI_1P00HZ__50P_3TIMS_E_OFF_REQ4)   },
    {  (U2)ALERT_CH_H_EVMOD_TT,       (U1)ALERT_REQ_H_EVMOD_TT_FLS_ACCL_V,      (U1)8U,    u4_HMITT_HB5(HMITT_BLINK_SI_1P00HZ__50P_3TIMS_E_OFF_REQ5)   },
    {  (U2)ALERT_CH_H_EVMOD_TT,       (U1)ALERT_REQ_H_EVMOD_TT_FLS_OTHER_V,     (U1)8U,    u4_HMITT_HB5(HMITT_BLINK_SI_1P00HZ__50P_3TIMS_E_OFF_REQ6)   },
    {  (U2)ALERT_CH_P_TECOLP2,        (U1)ALERT_REQ_P_TECOLP2_ECOLP_ON,         (U1)9U,    u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_P_STOSTA_TT,      (U1)ALERT_REQ_P_STOSTA_TT_ON_G,           (U1)9U,    u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_P_STOSTA_TT,      (U1)ALERT_REQ_P_STOSTA_TT_FLASH1_G,       (U1)9U,    u4_HMITT_HB5(HMITT_BLINK_CO_0P25HZ__50P)                    },
    {  (U2)ALERT_CH_P_STOSTA_TT,      (U1)ALERT_REQ_P_STOSTA_TT_FLASH2_G,       (U1)9U,    u4_HMITT_HB5(HMITT_BLINK_CO_1P00HZ__50P_STOSTA)             },
    {  (U2)ALERT_CH_P_STOSTA_TT,      (U1)ALERT_REQ_P_STOSTA_TT_FLASH3_G,       (U1)9U,    u4_HMITT_HB5(HMITT_BLINK_CO_3P33HZ__50P)                    },
    {  (U2)ALERT_CH_P_STOSTA_TT,      (U1)ALERT_REQ_P_STOSTA_TT_ON_A,           (U1)9U,    u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_P_STOSTA_TT,      (U1)ALERT_REQ_P_STOSTA_TT_FLASH_A,        (U1)9U,    u4_HMITT_HB6(HMITT_BLINK_CO_1P00HZ__50P)                    },
    {  (U2)ALERT_CH_P_MILREQ,         (U1)ALERT_REQ_P_MILREQ_ON,                (U1)9U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_P_MILREQ,         (U1)ALERT_REQ_P_MILREQ_ON_RW,             (U1)9U,    u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_P_MILREQ,         (U1)ALERT_REQ_P_MILREQ_FLASH_REDUCE,      (U1)9U,    u4_HMITT_HB7(HMITT_BLINK_CO_1P00HZ__50P)                    },
    {  (U2)ALERT_CH_P_MILREQ,         (U1)ALERT_REQ_P_MILREQ_FLASH_READY,       (U1)9U,    u4_HMITT_HB7(HMITT_BLINK_CO_1P00HZ__50P)                    },
    {  (U2)ALERT_CH_P_MILREQ,         (U1)ALERT_REQ_P_MILREQ_FLASH_4HZ,         (U1)9U,    u4_HMITT_HB7(HMITT_BLINK_CO_4P00HZ__50P)                    },
    {  (U2)ALERT_CH_P_MILREQ,         (U1)ALERT_REQ_P_MILREQ_FLASH_EUREADY,     (U1)9U,    u4_HMITT_HB7(HMITT_BLINK_SI_1P00HZ__50P_5TIMS_E_OFF)        },
    {  (U2)ALERT_CH_H_TEVRN,          (U1)ALERT_REQ_H_TEVRN_ON,                 (U1)10U,   u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_OFRMDL,         (U1)ALERT_REQ_C_OFRMDL_MUDSAND,           (U1)10U,   u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_OFRMDL,         (U1)ALERT_REQ_C_OFRMDL_ROCKDIRT,          (U1)10U,   u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_OFRMDL,         (U1)ALERT_REQ_C_OFRMDL_TRAILMODE,         (U1)11U,   u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_DRIMOD_TT,      (U1)ALERT_REQ_C_DRIMOD_TT_SNOW,           (U1)11U,   u4_HMITT_HB1(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_THEVM_TT,       (U1)ALERT_REQ_H_THEVM_TT_EVM_ON,          (U1)11U,   u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_THEVM_TT,       (U1)ALERT_REQ_H_THEVM_TT_EVM_FLS_OFF,     (U1)11U,   u4_HMITT_HB4(HMITT_BLINK_SI_1P67HZ__50P_3TIMS_E_OFF_THEVM)  },
    {  (U2)ALERT_CH_H_THEVM_TT,       (U1)ALERT_REQ_H_THEVM_TT_EVM_FLS_ON,      (U1)11U,   u4_HMITT_HB4(HMITT_BLINK_SI_1P67HZ__50P_3TIMS_E_ON_THEVM)   },
    {  (U2)ALERT_CH_H_THEVM_TT,       (U1)ALERT_REQ_H_THEVM_TT_CHG_ON,          (U1)11U,   u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_THEVM_TT,       (U1)ALERT_REQ_H_THEVM_TT_CHG_FLS_OFF,     (U1)11U,   u4_HMITT_HB5(HMITT_BLINK_SI_1P67HZ__50P_3TIMS_E_OFF_THEVM)  },
    {  (U2)ALERT_CH_H_THEVM_TT,       (U1)ALERT_REQ_H_THEVM_TT_CHG_FLASH,       (U1)11U,   u4_HMITT_HB5(HMITT_BLINK_CO_1P00HZ__50P_S_OFF_THEVM)        },
    {  (U2)ALERT_CH_H_THEVM_TT,       (U1)ALERT_REQ_H_THEVM_TT_EVA_ON,          (U1)11U,   u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_THEVM_TT,       (U1)ALERT_REQ_H_THEVM_TT_EVA_FLS_OFF,     (U1)11U,   u4_HMITT_HB6(HMITT_BLINK_SI_1P67HZ__50P_3TIMS_E_OFF_THEVM)  },
    {  (U2)ALERT_CH_H_THEVM_TT,       (U1)ALERT_REQ_H_THEVM_TT_EVA_FLS_ON,      (U1)11U,   u4_HMITT_HB6(HMITT_BLINK_SI_1P67HZ__50P_3TIMS_E_ON_THEVM)   },
    {  (U2)ALERT_CH_H_THEVM_TT,       (U1)ALERT_REQ_H_THEVM_TT_HVM_ON,          (U1)11U,   u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_THEVM_TT,       (U1)ALERT_REQ_H_THEVM_TT_HVM_FLS_OFF,     (U1)11U,   u4_HMITT_HB7(HMITT_BLINK_SI_1P67HZ__50P_3TIMS_E_OFF_THEVM)  },
    {  (U2)ALERT_CH_H_THEVM_TT,       (U1)ALERT_REQ_H_THEVM_TT_HVM_FLS_ON,      (U1)11U,   u4_HMITT_HB7(HMITT_BLINK_SI_1P67HZ__50P_3TIMS_E_ON_THEVM)   },
    {  (U2)ALERT_CH_B_THEAD,          (U1)ALERT_REQ_B_THEAD_ON,                 (U1)12U,   u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_PKSB_TT,        (U1)ALERT_REQ_S_PKSB_TT_ON,               (U1)12U,   u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_PKSB_TT,        (U1)ALERT_REQ_S_PKSB_TT_FLASH,            (U1)12U,   u4_HMITT_HB4(HMITT_BLINK_CO_0P50HZ__50P)                    },
    {  (U2)ALERT_CH_C_DRIMOD_TT,      (U1)ALERT_REQ_C_DRIMOD_TT_SPORT,          (U1)12U,   u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_DRIMOD_TT,      (U1)ALERT_REQ_C_DRIMOD_TT_ECO,            (U1)13U,   u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_DRIMOD_TT,      (U1)ALERT_REQ_C_DRIMOD_TT_CUSTOM,         (U1)13U,   u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_DAC_TT,         (U1)ALERT_REQ_C_DAC_TT_GRN_ON,            (U1)13U,   u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_DAC_TT,         (U1)ALERT_REQ_C_DAC_TT_GRN_FLASH,         (U1)13U,   u4_HMITT_HB4(HMITT_BLINK_CO_2P00HZ__50P)                    },
    {  (U2)ALERT_CH_H_QUICHA_TT,      (U1)ALERT_REQ_H_QUICHA_TT_ON,             (U1)15U,   u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_DRIMOD_TT,      (U1)ALERT_REQ_C_DRIMOD_TT_REAR_COMF,      (U1)15U,   u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_DRIMOD_TT,      (U1)ALERT_REQ_C_DRIMOD_TT_RANGE,          (U1)16U,   u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ADTJA_TT,       (U1)ALERT_REQ_S_ADTJA_TT_MALFUNC,         (U1)18U,   u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_D_TATLSD,         (U1)ALERT_REQ_D_TATLSD_ON,                (U1)18U,   u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_D_TATLSD,         (U1)ALERT_REQ_D_TATLSD_FLASH,             (U1)18U,   u4_HMITT_HB5(HMITT_BLINK_CO_2P00HZ__50P)                    },
    {  (U2)ALERT_CH_S_ADTJA_TT_DMCR,  (U1)ALERT_REQ_S_ADTJA_TT_DMCR_REC,        (U1)19U,   u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ADTJA_TT_DMCR,  (U1)ALERT_REQ_S_ADTJA_TT_DMCR_STNBY,      (U1)19U,   u4_HMITT_HB0(HMITT_BLINK_CO_1P00HZ__50P_S_OFF)              },
    {  (U2)ALERT_CH_S_ADTJA_TT,       (U1)ALERT_REQ_S_ADTJA_TT_STNBY,           (U1)19U,   u4_HMITT_HB1(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ADTJA_TT,       (U1)ALERT_REQ_S_ADTJA_TT_CTRL,            (U1)19U,   u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ERM_TT,         (U1)ALERT_REQ_S_ERM_TT_ON_G,              (U1)19U,   u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ERM_TT,         (U1)ALERT_REQ_S_ERM_TT_ON_A,              (U1)19U,   u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ERM_TT,         (U1)ALERT_REQ_S_ERM_TT_ON_W,              (U1)19U,   u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_LCA_TT_L,       (U1)ALERT_REQ_S_LCA_TT_L_ON_GY,           (U1)19U,   u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_LCA_TT_L,       (U1)ALERT_REQ_S_LCA_TT_L_ON_W,            (U1)19U,   u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_LCA_TT_L,       (U1)ALERT_REQ_S_LCA_TT_L_ON_G,            (U1)20U,   u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_LCA_TT_R,       (U1)ALERT_REQ_S_LCA_TT_R_ON_GY,           (U1)20U,   u4_HMITT_HB1(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_LCA_TT_R,       (U1)ALERT_REQ_S_LCA_TT_R_ON_W,            (U1)20U,   u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_LCA_TT_R,       (U1)ALERT_REQ_S_LCA_TT_R_ON_G,            (U1)20U,   u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ADASTT_TT,      (U1)ALERT_REQ_S_ADASTT_TT_A_OFF,          (U1)20U,   u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ADASTT_TT,      (U1)ALERT_REQ_S_ADASTT_TT_A_ABN,          (U1)20U,   u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ADASTT_TT,      (U1)ALERT_REQ_S_ADASTT_TT_A_FLASH,        (U1)20U,   u4_HMITT_HB4(HMITT_BLINK_CO_0P50HZ__50P)                    },
    {  (U2)ALERT_CH_S_ADASTT_TT,      (U1)ALERT_REQ_S_ADASTT_TT_GREEN,          (U1)20U,   u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ADASTT_TT,      (U1)ALERT_REQ_S_ADASTT_TT_W_STB,          (U1)20U,   u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_ADASTT_TT,      (U1)ALERT_REQ_S_ADASTT_TT_W_OFF,          (U1)20U,   u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_AHSS,           (U1)ALERT_REQ_S_AHSS_AHBAHS_ON,           (U1)21U,   u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_AHSS,           (U1)ALERT_REQ_S_AHSS_AHS_ON_SHADED,       (U1)21U,   u4_HMITT_HB1(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_AHSS,           (U1)ALERT_REQ_S_AHSS_AHS_ON_HI,           (U1)21U,   u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_AHSS,           (U1)ALERT_REQ_S_AHSS_AHB_ON_HI,           (U1)21U,   u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_P_COOTEM_TT_BC,   (U1)ALERT_REQ_P_COOTEM_TT_BC_PREWRN,      (U1)21U,   u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_P_COOTEM_TT_BC,   (U1)ALERT_REQ_P_COOTEM_TT_BC_WRN,         (U1)21U,   u4_HMITT_HB3(HMITT_BLINK_CO_0P50HZ__50P)                    },
    {  (U2)ALERT_CH_S_AHSS,           (U1)ALERT_REQ_S_AHSS_AHB_SW,              (U1)21U,   u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_DRIMOD_TT,      (U1)ALERT_REQ_C_DRIMOD_TT_TRACK,          (U1)21U,   u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_P_CIRMOD_TT_CM,   (U1)ALERT_REQ_P_CIRMOD_TT_CM_ON,          (U1)21U,   u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_P_CIRMOD_TT_ALC,  (U1)ALERT_REQ_P_CIRMOD_TT_ALC_ON,         (U1)21U,   u4_HMITT_HB7(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_DAC_TT,         (U1)ALERT_REQ_C_DAC_TT_WHT_ON,            (U1)22U,   u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_XMGRIP_TT_IND,  (U1)ALERT_REQ_H_XMGRIP_TT_IND_STNDBY,     (U1)22U,   u4_HMITT_HB1(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_XMGRIP_TT_IND,  (U1)ALERT_REQ_H_XMGRIP_TT_IND_OPRTNG,     (U1)22U,   u4_HMITT_HB2(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_H_XMGRIP_TT_SPD,  (U1)ALERT_REQ_H_XMGRIP_TT_SPD_FRSTLV,     (U1)22U,   u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P_XMGRIP_SPD1LVL)     },
    {  (U2)ALERT_CH_H_XMGRIP_TT_SPD,  (U1)ALERT_REQ_H_XMGRIP_TT_SPD_SCNDLV,     (U1)22U,   u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P_XMGRIP_SPD2LVL)     },
    {  (U2)ALERT_CH_H_XMGRIP_TT_SPD,  (U1)ALERT_REQ_H_XMGRIP_TT_SPD_THRDLV,     (U1)22U,   u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P_XMGRIP_SPD3LVL)     },
    {  (U2)ALERT_CH_H_XMGRIP_TT_SPD,  (U1)ALERT_REQ_H_XMGRIP_TT_SPD_FRTHLV,     (U1)22U,   u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P_XMGRIP_SPD4LVL)     },
    {  (U2)ALERT_CH_H_XMGRIP_TT_SPD,  (U1)ALERT_REQ_H_XMGRIP_TT_SPD_FFTHLV,     (U1)22U,   u4_HMITT_HB3(HMITT_BLINK_CO_ON_____100P_XMGRIP_SPD5LVL)     },
    {  (U2)ALERT_CH_C_HCS_TT,         (U1)ALERT_REQ_C_HCS_TT_GRN_ON,            (U1)22U,   u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_HCS_TT,         (U1)ALERT_REQ_C_HCS_TT_GRN_FLASH,         (U1)22U,   u4_HMITT_HB4(HMITT_BLINK_CO_1P00HZ__50P)                    },
    {  (U2)ALERT_CH_C_HCS_TT,         (U1)ALERT_REQ_C_HCS_TT_AMBER_ON,          (U1)22U,   u4_HMITT_HB5(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_DMC_TT,         (U1)ALERT_REQ_S_DMC_TT_MAL_DMC,           (U1)22U,   u4_HMITT_HB6(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_S_DMC_TT,         (U1)ALERT_REQ_S_DMC_TT_WHT_DMC_OFF,       (U1)23U,   u4_HMITT_HB0(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_VSCEXP_NOSTEP,  (U1)ALERT_REQ_C_VSCEXP_NOSTEP_ON,         (U1)23U,   u4_HMITT_HB4(HMITT_BLINK_CO_ON_____100P)                    },
    {  (U2)ALERT_CH_C_VSCEXP_WDSTEP,  (U1)ALERT_REQ_C_VSCEXP_WDSTEP_3ST_0,      (U1)23U,   u4_HMITT_HB5(HMITT_BLINK_CO_ON_100P_VSCEXP_0)               },
    {  (U2)ALERT_CH_C_VSCEXP_WDSTEP,  (U1)ALERT_REQ_C_VSCEXP_WDSTEP_3ST_1,      (U1)23U,   u4_HMITT_HB5(HMITT_BLINK_CO_ON_100P_VSCEXP_1)               },
    {  (U2)ALERT_CH_C_VSCEXP_WDSTEP,  (U1)ALERT_REQ_C_VSCEXP_WDSTEP_3ST_2,      (U1)23U,   u4_HMITT_HB5(HMITT_BLINK_CO_ON_100P_VSCEXP_2)               },
    {  (U2)ALERT_CH_C_VSCEXP_WDSTEP,  (U1)ALERT_REQ_C_VSCEXP_WDSTEP_3ST_3,      (U1)23U,   u4_HMITT_HB5(HMITT_BLINK_CO_ON_100P_VSCEXP_3)               },
    {  (U2)ALERT_CH_C_VSCEXP_WDSTEP,  (U1)ALERT_REQ_C_VSCEXP_WDSTEP_5ST_0,      (U1)23U,   u4_HMITT_HB6(HMITT_BLINK_CO_ON_100P_VSCEXP_0)               },
    {  (U2)ALERT_CH_C_VSCEXP_WDSTEP,  (U1)ALERT_REQ_C_VSCEXP_WDSTEP_5ST_1,      (U1)23U,   u4_HMITT_HB6(HMITT_BLINK_CO_ON_100P_VSCEXP_1)               },
    {  (U2)ALERT_CH_C_VSCEXP_WDSTEP,  (U1)ALERT_REQ_C_VSCEXP_WDSTEP_5ST_2,      (U1)23U,   u4_HMITT_HB6(HMITT_BLINK_CO_ON_100P_VSCEXP_2)               },
    {  (U2)ALERT_CH_C_VSCEXP_WDSTEP,  (U1)ALERT_REQ_C_VSCEXP_WDSTEP_5ST_3,      (U1)23U,   u4_HMITT_HB6(HMITT_BLINK_CO_ON_100P_VSCEXP_3)               },
    {  (U2)ALERT_CH_C_VSCEXP_WDSTEP,  (U1)ALERT_REQ_C_VSCEXP_WDSTEP_5ST_4,      (U1)23U,   u4_HMITT_HB6(HMITT_BLINK_CO_ON_100P_VSCEXP_4)               },
    {  (U2)ALERT_CH_C_VSCEXP_WDSTEP,  (U1)ALERT_REQ_C_VSCEXP_WDSTEP_5ST_5,      (U1)23U,   u4_HMITT_HB6(HMITT_BLINK_CO_ON_100P_VSCEXP_5)               },
    {  (U2)ALERT_CH_C_HCS_TTB,        (U1)ALERT_REQ_C_HCS_TTB_ACCESS_MODE,      (U1)24U,   u4_HMITT_HB1(HMITT_BLINK_CO_ON_____100P)                    }
};
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*===================================================================================================================================*/
/*  U2    u2_g_HmittSizeReqbit(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u2_t_ret : array element number                                                                                  */
/*===================================================================================================================================*/
U2 u2_g_HmittSizeReqbit(void){

    U2 u2_t_ret;

    u2_t_ret = (U2)(sizeof(st_gp_HMITTREQBIT) / sizeof(st_gp_HMITTREQBIT[0]));

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
/*  1.1.0    04/18/2020  TH       Setting for 800B CV.                                                                               */
/*  1.2.0    09/07/2020  TH       Setting for 800B CV-R.                                                                             */
/*  1.3.0    01/06/2021  TH       Setting for 800B 1A.                                                                               */
/*  1.4.0    06/02/2021  TH       Setting for 22-24FGM CV.                                                                           */
/*  1.6.0    02/02/2024  DR       Setting for 19PFv3                                                                                 */
/*  1.8.0    10/15/2024  KO       Setting for BEV System_Consideration_1.                                                            */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  19PFv3-1 02/20/2024  GM       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-2 07/10/2024  YR       Added config for HCS                                                                               */
/*  BEV-1    10/15/2024  KO       Change for BEV System_Consideration_1.(MET-C_STEER-CSTD-0-00-A-C0)                                 */
/*  BEV-2    11/12/2024  KO       Change for BEV System_Consideration_1.(MET-C_BRLV-CSTD-2-00-A-C0)                                  */
/*  BEV-3    11/25/2024  KO       Change for BEV System_Consideration_1.(MET-C_ECB-CSTD-1-00-A-C0 / MET-C_EPB-CSTD-1-00-A-C0)        */
/*  BEV-4    12/23/2024  KO       Change for BEV System_Consideration_1.(MET-H_ZMILREQ-CSTD-1-00-A-C0                       )        */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * TH   = Takahiro Hirano, Denso Techno                                                                                           */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*  * YR   = Yhana Regalario, DTPH                                                                                                   */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
