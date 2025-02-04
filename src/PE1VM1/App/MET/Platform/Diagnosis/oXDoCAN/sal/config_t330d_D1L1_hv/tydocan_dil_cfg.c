/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  TyDoCAN Service Application Layer / Digital Input Logger                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DIL_CFG_C_MAJOR                  (1)
#define TYDOCAN_DIL_CFG_C_MINOR                  (0)
#define TYDOCAN_DIL_CFG_C_PATCH                  (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tydocan_dil_cfg_private.h"
#include "oxdocan_saif.h"
#include "oxdocan_cfg_private.h"
#include "vardef.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((TYDOCAN_DIL_CFG_C_MAJOR != TYDOCAN_DIL_H_MAJOR) || \
     (TYDOCAN_DIL_CFG_C_MINOR != TYDOCAN_DIL_H_MINOR) || \
     (TYDOCAN_DIL_CFG_C_PATCH != TYDOCAN_DIL_H_PATCH))
#error "tydocan_dil_cfg.c and tydocan_dil.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_DIL_CFG_C_MAJOR != TYDOCAN_DIL_CFG_H_MAJOR) || \
     (TYDOCAN_DIL_CFG_C_MINOR != TYDOCAN_DIL_CFG_H_MINOR) || \
     (TYDOCAN_DIL_CFG_C_PATCH != TYDOCAN_DIL_CFG_H_PATCH))
#error "tydocan_dil_cfg.c and tydocan_dil_cfg_private.h : source and header files are inconsistent!"
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
U4                   u4_gp_tydc_dil_chb[TYDC_DIL_NUM_CHB * TYDC_DIL_NUM_GR];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_DIL_SWI           st_gp_TYDC_DIL_SWI[] = {
    /* u2_disignl,                     u2_dil_ch */             
    {(U2)IOHW_DISGNL_STSW_BK,          (U2)TYDC_DIL_CH_STE_L0_BA }, /*  0 */
    {(U2)IOHW_DISGNL_STSW_EN,          (U2)TYDC_DIL_CH_STE_L0_EN }, /*  1 */
    {(U2)IOHW_DISGNL_STSW_UP,          (U2)TYDC_DIL_CH_STE_L0_UP }, /*  2 */
    {(U2)IOHW_DISGNL_STSW_DN,          (U2)TYDC_DIL_CH_STE_L0_DW }, /*  3 */
    {(U2)IOHW_DISGNL_STSW_LF,          (U2)TYDC_DIL_CH_STE_L0_LE }, /*  4 */
    {(U2)IOHW_DISGNL_STSW_RT,          (U2)TYDC_DIL_CH_STE_L0_RI }, /*  5 */
    {(U2)IOHW_DISGNL_ODO,              (U2)TYDC_DIL_CH_OT_SEL    }, /*  6 */
    {(U2)IOHW_DISGNL_DBKL,             (U2)TYDC_DIL_CH_BLT_BK_D  }, /*  7 */
    {(U2)IOHW_DISGNL_HAZARD,           (U2)TYDC_DIL_CH_HAZ       }, /*  8 */
    {(U2)IOHW_DISGNL_RHEO_UP,          (U2)TYDC_DIL_CH_DIM_UP    }, /*  9 */
    {(U2)IOHW_DISGNL_RHEO_DN,          (U2)TYDC_DIL_CH_DIM_DW    }, /* 10 */
    {(U2)IOHW_DISGNL_LID_IN,           (U2)TYDC_DIL_CH_FLO_SW    }, /* 11 */
    {(U2)IOHW_DISGNL_RHEOSTAT_DOWN_SW, (U2)TYDC_DIL_CH_DIM_2IN_DW}, /* 12 */
    {(U2)IOHW_DISGNL_TAIL_CANCEL_IN,   (U2)TYDC_DIL_CH_TAI_CN    }, /* 13 */
    {(U2)IOHW_DISGNL_HUD_MAIN_SW_IN,   (U2)TYDC_DIL_CH_HUD_SW    }  /* 14 */
};
                                                        
const U2                        u2_g_TYDC_DIL_NUM_SWI        = ((U2)sizeof(st_gp_TYDC_DIL_SWI) / (U2)sizeof(ST_TYDC_DIL_SWI));
const U2                        u2_g_TYDC_DIL_NUM_SWI_BY_RUN = (U2)15U / (U2)TYDC_DIL_NUM_TSLOT;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_DIL_GR            st_gp_TYDC_DIL_GR[TYDC_DIL_NUM_GR] = {
    {
        {
            (U4)0x00000079U,                        /* u4p_vom[BAT] */
            (U4)0x00000079U                         /* u4p_vom[IGN] */
        },
        (U2)TYDC_DIL_MEM_BRA,                       /* u2_mem       */
        (U2)RIMID_U4_TYDC_DIL_1                     /* u2_mid       */
    },
    {
        {
            (U4)0x0000C000U,                        /* u4p_vom[BAT] */
            (U4)0x0000C000U                         /* u4p_vom[IGN] */
        },
        (U2)TYDC_DIL_MEM_BRA,                       /* u2_mem       */
        (U2)RIMID_U4_TYDC_DIL_2                     /* u2_mid       */
    }
};

const U1                        u1_g_TYDC_DIL_NUM_GR = (U1)TYDC_DIL_NUM_GR;
const U2                        u2_g_TYDC_DIL_NUM_CH = (U2)TYDC_DIL_NUM_CH;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_TYDC_BITX_CH    st_sp_TYDC_BITX_CH_1001[] = {
    /* u2_ch,                            u1_byte,  u1_bit */
    {(U2)TYDC_DIL_CH_OT_SEL,             (U1)0U,   (U1)0x80U},
 /* {(U2)TYDC_DIL_CH_OT_RES,             (U1)0U,   (U1)0x40U}, */
 /* {(U2)TYDC_DIL_CH_MI_SEL,             (U1)0U,   (U1)0x20U}, */
    {(U2)TYDC_DIL_CH_TAI_CN,             (U1)0U,   (U1)0x10U},
    {(U2)TYDC_DIL_CH_DIM_UP,             (U1)0U,   (U1)0x08U},  /* Separete Input (UP)   Port Assign Pin115  */
    {(U2)TYDC_DIL_CH_DIM_2IN_DW,         (U1)0U,   (U1)0x04U},  /* Separete Input (DOWN) Port Assign Pin127  */
    {(U2)TYDC_DIL_CH_DIM_DW,             (U1)0U,   (U1)0x04U},  /* One Input(DOWN) Port Assign Pin115        */
    {(U2)TYDC_DIL_CH_FLO_SW,             (U1)0U,   (U1)0x01U}  

 /* {(U2)TYDC_DIL_CH_TIM_PLU,            (U1)2U,   (U1)0x80U}, */
 /* {(U2)TYDC_DIL_CH_TIM_MIN,            (U1)2U,   (U1)0x40U}, */
 /* {(U2)TYDC_DIL_CH_TIM_SYN,            (U1)2U,   (U1)0x20U}, */
 /* {(U2)TYDC_DIL_CH_TIM_1B,             (U1)2U,   (U1)0x10U}  */
};
#define u2_TYDC_BITX_NUM_CH_1001                 ((U2)sizeof(st_sp_TYDC_BITX_CH_1001) / (U2)sizeof(ST_TYDC_BITX_CH))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_TYDC_BITX_CH    st_sp_TYDC_BITX_CH_1002[] = {
    /* u2_ch,                            u1_byte,  u1_bit */
    {(U2)TYDC_DIL_CH_STE_L0_UP,          (U1)0U,   (U1)0x80U},
    {(U2)TYDC_DIL_CH_STE_L0_DW,          (U1)0U,   (U1)0x40U},
    {(U2)TYDC_DIL_CH_STE_L0_LE,          (U1)0U,   (U1)0x20U},
    {(U2)TYDC_DIL_CH_STE_L0_RI,          (U1)0U,   (U1)0x10U},
    {(U2)TYDC_DIL_CH_STE_L0_EN,          (U1)0U,   (U1)0x08U},
    {(U2)TYDC_DIL_CH_STE_L0_BA,          (U1)0U,   (U1)0x04U}
 /* {(U2)TYDC_DIL_CH_STE_L0_TO,          (U1)0U,   (U1)0x02U}, */
};
#define u2_TYDC_BITX_NUM_CH_1002                 ((U2)sizeof(st_sp_TYDC_BITX_CH_1002) / (U2)sizeof(ST_TYDC_BITX_CH))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_TYDC_BITX_CH    st_sp_TYDC_BITX_CH_10A5[] = {
    /* u2_ch,                            u1_byte,  u1_bit */
    {(U2)TYDC_DIL_CH_OT_SEL,             (U1)0U,   (U1)0x80U},
 /* {(U2)TYDC_DIL_CH_OT_RES,             (U1)0U,   (U1)0x40U}, */
 /* {(U2)TYDC_DIL_CH_MI_SEL,             (U1)0U,   (U1)0x20U}, */
    {(U2)TYDC_DIL_CH_TAI_CN,             (U1)0U,   (U1)0x10U},
    {(U2)TYDC_DIL_CH_DIM_UP,             (U1)0U,   (U1)0x08U},  /* Separete Input (UP)   Port Assign Pin115  */
    {(U2)TYDC_DIL_CH_DIM_2IN_DW,         (U1)0U,   (U1)0x04U},  /* Separete Input (DOWN) Port Assign Pin127  */
    {(U2)TYDC_DIL_CH_DIM_DW,             (U1)0U,   (U1)0x04U},  /* One Input(DOWN) Port Assign Pin115        */
 /* {(U2)TYDC_DIL_CH_TIM_PLU,            (U1)0U,   (U1)0x01U}, */

 /* {(U2)TYDC_DIL_CH_TIM_MIN,            (U1)2U,   (U1)0x80U}, */
 /* {(U2)TYDC_DIL_CH_TIM_SYN,            (U1)2U,   (U1)0x40U}, */
 /* {(U2)TYDC_DIL_CH_TIM_1B,             (U1)2U,   (U1)0x20U}, */
 /* {(U2)TYDC_DIL_CH_STE_L0_UP,          (U1)2U,   (U1)0x10U}, */
 /* {(U2)TYDC_DIL_CH_STE_L0_DW,          (U1)2U,   (U1)0x08U}, */
 /* {(U2)TYDC_DIL_CH_STE_L0_LE,          (U1)2U,   (U1)0x04U}, */
 /* {(U2)TYDC_DIL_CH_STE_L0_RI,          (U1)2U,   (U1)0x02U}, */
 /* {(U2)TYDC_DIL_CH_STE_L0_EN,          (U1)2U,   (U1)0x01U}, */

 /* {(U2)TYDC_DIL_CH_STE_L0_BA,          (U1)4U,   (U1)0x80U}, */
 /* {(U2)TYDC_DIL_CH_STE_L0_TO,          (U1)4U,   (U1)0x40U}, */
 /* {(U2)TYDC_DIL_CH_BLT_BK_D,           (U1)4U,   (U1)0x20U}, */
 /* {(U2)TYDC_DIL_CH_BLT_BK_P,           (U1)4U,   (U1)0x10U}, */
 /* {(U2)TYDC_DIL_CH_SEA_P,              (U1)4U,   (U1)0x08U}, */
 /* {(U2)TYDC_DIL_CH_BLT_P,              (U1)4U,   (U1)0x04U}, */
 /* {(U2)TYDC_DIL_CH_BLT_2ND_R,          (U1)4U,   (U1)0x02U}, */
 /* {(U2)TYDC_DIL_CH_BLT_2ND_L,          (U1)4U,   (U1)0x01U}, */

 /* {(U2)TYDC_DIL_CH_BLT_2ND_C,          (U1)6U,   (U1)0x80U}, */
 /* {(U2)TYDC_DIL_CH_BLT_3RD_R,          (U1)6U,   (U1)0x40U}, */
 /* {(U2)TYDC_DIL_CH_BLT_3RD_L,          (U1)6U,   (U1)0x20U}, */
 /* {(U2)TYDC_DIL_CH_BLT_3RD_C,          (U1)6U,   (U1)0x10U}, */
 /* {(U2)TYDC_DIL_CH_TURN_L,             (U1)6U,   (U1)0x08U}, */
 /* {(U2)TYDC_DIL_CH_TURN_R,             (U1)6U,   (U1)0x04U}, */
 /* {(U2)TYDC_DIL_CH_FLA_CR,             (U1)6U,   (U1)0x02U}, */
 /* {(U2)TYDC_DIL_CH_HAZ,                (U1)6U,   (U1)0x01U}, */

 /* {(U2)TYDC_DIL_CH_OIL_PR,             (U1)8U,   (U1)0x80U}, */
 /* {(U2)TYDC_DIL_CH_OIL_LV,             (U1)8U,   (U1)0x40U}, */
 /* {(U2)TYDC_DIL_CH_FU_SED,             (U1)8U,   (U1)0x20U}, */
 /* {(U2)TYDC_DIL_CH_FU_FIL,             (U1)8U,   (U1)0x10U}, */
 /* {(U2)TYDC_DIL_CH_PARK,               (U1)8U,   (U1)0x08U}, */
 /* {(U2)TYDC_DIL_CH_BRK_VA,             (U1)8U,   (U1)0x04U}, */
 /* {(U2)TYDC_DIL_CH_STR_HEAT,           (U1)8U,   (U1)0x02U}, */
 /* {(U2)TYDC_DIL_CH_BRK_PAD,            (U1)8U,   (U1)0x01U}, */

 /* {(U2)TYDC_DIL_CH_BLT_4TH_R,          (U1)10U,  (U1)0x80U}, */
 /* {(U2)TYDC_DIL_CH_BLT_4TH_L,          (U1)10U,  (U1)0x40U}, */
 /* {(U2)TYDC_DIL_CH_BLT_4TH_C,          (U1)10U,  (U1)0x20U}, */
 /* {(U2)TYDC_DIL_CH_BLT_BK_C,           (U1)10U,  (U1)0x10U}, */
 /* {(U2)TYDC_DIL_CH_SEA_C,              (U1)10U,  (U1)0x08U}, */
 /* {(U2)TYDC_DIL_CH_BLT_C,              (U1)10U,  (U1)0x04U}, */
    {(U2)TYDC_DIL_CH_FLO_SW,             (U1)10U,  (U1)0x02U},
    {(U2)TYDC_DIL_CH_HUD_SW,             (U1)10U,  (U1)0x01U}
};
#define u2_TYDC_BITX_NUM_CH_10A5                 ((U2)sizeof(st_sp_TYDC_BITX_CH_10A5) / (U2)sizeof(ST_TYDC_BITX_CH))

#if 0
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_TYDC_BITX_CH    st_sp_TYDC_BITX_CH_1101[] = {
    /* u2_ch,                            u1_byte,  u1_bit */
 /* {(U2)TYDC_DIL_CH_WAS_LV,             (U1)0U,   (U1)0x80U}, */
    {(U2)TYDC_DIL_CH_BLT_BK_D,           (U1)0U,   (U1)0x40U},
 /* {(U2)TYDC_DIL_CH_BLT_BK_P,           (U1)0U,   (U1)0x20U}, */
 /*  {(U2)TYDC_DIL_CH_SEA_P,             (U1)0U,   (U1)0x10U}, */
 /* {(U2)TYDC_DIL_CH_BLT_P,              (U1)0U,   (U1)0x08U}, */
 /* {(U2)TYDC_DIL_CH_BLT_2ND_R,          (U1)0U,   (U1)0x04U}, */
 /* {(U2)TYDC_DIL_CH_BLT_2ND_L,          (U1)0U,   (U1)0x02U}, */
 /* {(U2)TYDC_DIL_CH_BLT_2ND_C,          (U1)0U,   (U1)0x01U}, */

 /* {(U2)TYDC_DIL_CH_BLT_3RD_R,          (U1)2U,   (U1)0x80U}, */
 /* {(U2)TYDC_DIL_CH_BLT_3RD_L,          (U1)2U,   (U1)0x40U}, */
 /* {(U2)TYDC_DIL_CH_BLT_3RD_C,          (U1)2U,   (U1)0x20U}, */
 /* {(U2)TYDC_DIL_CH_TURN_L,             (U1)2U,   (U1)0x10U}, */
 /* {(U2)TYDC_DIL_CH_TURN_R,             (U1)2U,   (U1)0x08U}, */
 /* {(U2)TYDC_DIL_CH_FLA_CR,             (U1)2U,   (U1)0x04U}, */
    {(U2)TYDC_DIL_CH_HAZ,                (U1)2U,   (U1)0x02U}
 /* {(U2)TYDC_DIL_CH_BLT_4TH_R,          (U1)2U,   (U1)0x01U}, */

 /* {(U2)TYDC_DIL_CH_BLT_4TH_L,          (U1)4U,   (U1)0x80U}, */
 /* {(U2)TYDC_DIL_CH_BLT_4TH_C,          (U1)4U,   (U1)0x40U}, */
 /* {(U2)TYDC_DIL_CH_BLT_BK_C,           (U1)4U,   (U1)0x20U}, */
 /* {(U2)TYDC_DIL_CH_SEA_C,              (U1)4U,   (U1)0x10U}, */
 /* {(U2)TYDC_DIL_CH_BLT_C,              (U1)4U,   (U1)0x08U}, */
 /* {(U2)TYDC_DIL_CH_STOP_SW,            (U1)4U,   (U1)0x04U}  */
};
#define u2_TYDC_BITX_NUM_CH_1101                 ((U2)sizeof(st_sp_TYDC_BITX_CH_1101) / (U2)sizeof(ST_TYDC_BITX_CH))
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_TYDC_BITX_CH    st_sp_TYDC_BITX_CH_1201[] = {
    /* u2_ch,                            u1_byte,  u1_bit */
 /* {(U2)TYDC_DIL_CH_OIL_PR,             (U1)0U,   (U1)0x80U}, */
 /* {(U2)TYDC_DIL_CH_OIL_LV,             (U1)0U,   (U1)0x40U}  */
 /* {(U2)TYDC_DIL_CH_FU_SED,             (U1)0U,   (U1)0x20U}, */
 /* {(U2)TYDC_DIL_CH_FU_FIL,             (U1)0U,   (U1)0x10U}, */
    {(U2)0U,                             (U1)0U,   (U1)0x00U}
};
#define u2_TYDC_BITX_NUM_CH_1201                 ((U2)sizeof(st_sp_TYDC_BITX_CH_1201) / (U2)sizeof(ST_TYDC_BITX_CH))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_TYDC_BITX_CH    st_sp_TYDC_BITX_CH_1401[] = {
    /* u2_ch,                            u1_byte,  u1_bit */
 /* {(U2)TYDC_DIL_CH_PARK,               (U1)0U,   (U1)0x80U}, */
 /* {(U2)TYDC_DIL_CH_BRK_FL,             (U1)0U,   (U1)0x40U}, */
 /* {(U2)TYDC_DIL_CH_BRK_VA,             (U1)0U,   (U1)0x20U}  */
 /* {(U2)TYDC_DIL_CH_STR_HEAT,           (U1)0U,   (U1)0x10U}, */
 /* {(U2)TYDC_DIL_CH_BRK_PAD,            (U1)0U,   (U1)0x80U}  */
    {(U2)0U,                             (U1)0U,   (U1)0x00U}
};
#define u2_TYDC_BITX_NUM_CH_1401                 ((U2)sizeof(st_sp_TYDC_BITX_CH_1401) / (U2)sizeof(ST_TYDC_BITX_CH))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_TYDC_BITX_TX           st_gp_TYDC_DIL_TX[TYDC_DIL_NUM_TX] = {
    {&u1_g_TyDoCANDilLasAct,  &st_sp_TYDC_BITX_CH_1001[0], u2_TYDC_BITX_NUM_CH_1001,  (U2)OXDC_DATA_REA_ANS_NB_1001},
    {&u1_g_TyDoCANDilLasAct,  &st_sp_TYDC_BITX_CH_1002[0], u2_TYDC_BITX_NUM_CH_1002,  (U2)OXDC_DATA_REA_ANS_NB_1002},
    {&u1_g_TyDoCANDilLogAct,  &st_sp_TYDC_BITX_CH_10A5[0], u2_TYDC_BITX_NUM_CH_10A5,  (U2)OXDC_DATA_REA_ANS_NB_10A5},
#if 0/*Phase6Diag Stub*/
    {&u1_g_TyDoCANDilLasAct,  &st_sp_TYDC_BITX_CH_1101[0], u2_TYDC_BITX_NUM_CH_1101,  (U2)OXDC_DATA_REA_ANS_NB_1101},
#else
    {vdp_PTR_NA,              vdp_PTR_NA,                  (U2)0U,                    (U2)0U                       },
#endif
    {vdp_PTR_NA            ,  &st_sp_TYDC_BITX_CH_1201[0], (U2)0U                  ,  (U2)0U                       },
    {vdp_PTR_NA            ,  &st_sp_TYDC_BITX_CH_1401[0], (U2)0U                  ,  (U2)0U                       }
};
const U2                        u2_g_TYDC_DIL_NUM_TX = (U1)TYDC_DIL_NUM_TX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                        u2_g_TYDC_DIL_RES_TOUT = (U2)5000U / (U2)OXDC_MAIN_TICK;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/ 2/2020  TN       New.                                                                                               */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  800B-1   10/06/2020  AS       Configured for 800B                                                                                */
/*  19PFv3-1 03/20/2024  TK       Configured for 19PFv3                                                                              */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * AS   = Atsunori Sugita, DENSO-TECHNO                                                                                           */
/*  * TK   = Toru kamishina,  DENSO-TECHNO                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
