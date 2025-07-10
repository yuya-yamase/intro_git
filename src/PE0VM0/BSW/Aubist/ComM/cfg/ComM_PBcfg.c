/* comm_pbcfg_c_v3-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | COMM/PBCFG/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include "../inc/bsw_comm_MemMap.h"
#include <ComStack_Types.h>

#include <comm/bsw_comm.h>
#include "../inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"
#include "../inc/bsw_comm_ctrl.h"

#if (BSW_BSWM_CS_FUNC_COMM == BSW_USE)
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#if ( BSW_COMM_CFG_CHNUM > 0U )
/* communication Activated System Status per channel */
BswConst BswU4 bsw_comm_ctrl_u4SysStsPerCh[BSW_COMM_CHNUM][BSW_COMM_SYSSTATTBLNUM] = {
    {    /* ComMConf_ComMChannel_CANFD_G2M_1_BUS */
        (BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
       ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    }
   ,{    /* ComMConf_ComMChannel_CANFD_G2M_2_BUS */
        (BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
       ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    }
   ,{    /* ComMConf_ComMChannel_CDC_VCAN_BUS */
        (BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
       ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    }
   ,{    /* ComMConf_ComMChannel_CANFD_G5M_BUS */
        (BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
       ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    }
};

/* Channel power per channel */
BswConst BswU4 bsw_comm_ctrl_u4CHPowSupply[BSW_COMM_CHNUM][BSW_COMM_SYSSTATTBLNUM] = {
    {    /* ComMConf_ComMChannel_CANFD_G2M_1_BUS */
        (BswU4)(BSW_COMM_PWSTAT_BAT|BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_PBA|ComMConf_SysStatusName_IGR)
       ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    }
   ,{    /* ComMConf_ComMChannel_CANFD_G2M_2_BUS */
        (BswU4)(BSW_COMM_PWSTAT_BAT|BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_PBA|ComMConf_SysStatusName_IGR)
       ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    }
   ,{    /* ComMConf_ComMChannel_CDC_VCAN_BUS */
        (BswU4)(BSW_COMM_PWSTAT_BAT|BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_PBA|ComMConf_SysStatusName_IGR)
       ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    }
   ,{    /* ComMConf_ComMChannel_CANFD_G5M_BUS */
        (BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
       ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    }
};
#endif /* ( BSW_COMM_CFG_CHNUM > 0U ) */

#if ( BSW_COMM_CFG_PNC_AWAKEPW == BSW_USE )
#if ( BSW_COMM_CFG_CHNUM > 0U )
#if ( BSW_COMM_CH_PNCNUM_0 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_0[BSW_COMM_CH_PNAWKPW_NUM_0] = {
    /* ComMConf_ComMPnc_Awake_16 */
    (BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
   ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    /* ComMConf_ComMPnc_Awake_40 */
   ,(BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
   ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    /* ComMConf_ComMPnc_Awake_43 */
   ,(BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
   ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    /* ComMConf_ComMPnc_Awake_44 */
   ,(BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
   ,(BswU4)(BSW_COMM_PWSTAT_NONE)
};
#endif /* ( BSW_COMM_CH_PNCNUM_0 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 0U ) */
#if ( BSW_COMM_CFG_CHNUM > 1U )
#if ( BSW_COMM_CH_PNCNUM_1 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_1[BSW_COMM_CH_PNAWKPW_NUM_1] = {
    /* ComMConf_ComMPnc_Awake_16 */
    (BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
   ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    /* ComMConf_ComMPnc_Awake_40 */
   ,(BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
   ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    /* ComMConf_ComMPnc_Awake_43 */
   ,(BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
   ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    /* ComMConf_ComMPnc_Awake_44 */
   ,(BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
   ,(BswU4)(BSW_COMM_PWSTAT_NONE)
};
#endif /* ( BSW_COMM_CH_PNCNUM_1 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 1U ) */
#if ( BSW_COMM_CFG_CHNUM > 2U )
#if ( BSW_COMM_CH_PNCNUM_2 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_2[BSW_COMM_CH_PNAWKPW_NUM_2] = {
    /* ComMConf_ComMPnc_Awake_16 */
    (BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
   ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    /* ComMConf_ComMPnc_Awake_40 */
   ,(BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
   ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    /* ComMConf_ComMPnc_Awake_43 */
   ,(BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
   ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    /* ComMConf_ComMPnc_Awake_44 */
   ,(BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
   ,(BswU4)(BSW_COMM_PWSTAT_NONE)
    /* ComMConf_ComMPnc_Awake_60 */
   ,(BswU4)(BSW_COMM_PWSTAT_ACC|BSW_COMM_PWSTAT_IG|ComMConf_SysStatusName_IGR)
   ,(BswU4)(BSW_COMM_PWSTAT_NONE)
};
#endif /* ( BSW_COMM_CH_PNCNUM_2 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 2U ) */
#if ( BSW_COMM_CFG_CHNUM > 3U )
#if ( BSW_COMM_CH_PNCNUM_3 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_3[BSW_COMM_CH_PNAWKPW_NUM_3] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_3 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 3U ) */
#if ( BSW_COMM_CFG_CHNUM > 4U )
#if ( BSW_COMM_CH_PNCNUM_4 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_4[BSW_COMM_CH_PNAWKPW_NUM_4] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_4 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 4U ) */
#if ( BSW_COMM_CFG_CHNUM > 5U )
#if ( BSW_COMM_CH_PNCNUM_5 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_5[BSW_COMM_CH_PNAWKPW_NUM_5] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_5 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 5U ) */
#if ( BSW_COMM_CFG_CHNUM > 6U )
#if ( BSW_COMM_CH_PNCNUM_6 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_6[BSW_COMM_CH_PNAWKPW_NUM_6] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_6 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 6U ) */
#if ( BSW_COMM_CFG_CHNUM > 7U )
#if ( BSW_COMM_CH_PNCNUM_7 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_7[BSW_COMM_CH_PNAWKPW_NUM_7] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_7 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 7U ) */
#if ( BSW_COMM_CFG_CHNUM > 8U )
#if ( BSW_COMM_CH_PNCNUM_8 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_8[BSW_COMM_CH_PNAWKPW_NUM_8] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_8 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 8U ) */
#if ( BSW_COMM_CFG_CHNUM > 9U )
#if ( BSW_COMM_CH_PNCNUM_9 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_9[BSW_COMM_CH_PNAWKPW_NUM_9] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_9 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 9U ) */
#if ( BSW_COMM_CFG_CHNUM > 10U )
#if ( BSW_COMM_CH_PNCNUM_10 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_10[BSW_COMM_CH_PNAWKPW_NUM_10] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_10 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 10U ) */
#if ( BSW_COMM_CFG_CHNUM > 11U )
#if ( BSW_COMM_CH_PNCNUM_11 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_11[BSW_COMM_CH_PNAWKPW_NUM_11] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_11 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 11U ) */
#if ( BSW_COMM_CFG_CHNUM > 12U )
#if ( BSW_COMM_CH_PNCNUM_12 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_12[BSW_COMM_CH_PNAWKPW_NUM_12] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_12 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 12U ) */
#if ( BSW_COMM_CFG_CHNUM > 13U )
#if ( BSW_COMM_CH_PNCNUM_13 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_13[BSW_COMM_CH_PNAWKPW_NUM_13] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_13 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 13U ) */
#if ( BSW_COMM_CFG_CHNUM > 14U )
#if ( BSW_COMM_CH_PNCNUM_14 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_14[BSW_COMM_CH_PNAWKPW_NUM_14] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_14 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 14U ) */
#if ( BSW_COMM_CFG_CHNUM > 15U )
#if ( BSW_COMM_CH_PNCNUM_15 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_15[BSW_COMM_CH_PNAWKPW_NUM_15] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_15 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 15U ) */
#if ( BSW_COMM_CFG_CHNUM > 16U )
#if ( BSW_COMM_CH_PNCNUM_16 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_16[BSW_COMM_CH_PNAWKPW_NUM_16] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_16 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 16U ) */
#if ( BSW_COMM_CFG_CHNUM > 17U )
#if ( BSW_COMM_CH_PNCNUM_17 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_17[BSW_COMM_CH_PNAWKPW_NUM_17] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_17 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 17U ) */
#if ( BSW_COMM_CFG_CHNUM > 18U )
#if ( BSW_COMM_CH_PNCNUM_18 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_18[BSW_COMM_CH_PNAWKPW_NUM_18] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_18 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 18U ) */
#if ( BSW_COMM_CFG_CHNUM > 19U )
#if ( BSW_COMM_CH_PNCNUM_19 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_19[BSW_COMM_CH_PNAWKPW_NUM_19] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_19 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 19U ) */
#if ( BSW_COMM_CFG_CHNUM > 20U )
#if ( BSW_COMM_CH_PNCNUM_20 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_20[BSW_COMM_CH_PNAWKPW_NUM_20] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_20 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 20U ) */
#if ( BSW_COMM_CFG_CHNUM > 21U )
#if ( BSW_COMM_CH_PNCNUM_21 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_21[BSW_COMM_CH_PNAWKPW_NUM_21] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_21 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 21U ) */
#if ( BSW_COMM_CFG_CHNUM > 22U )
#if ( BSW_COMM_CH_PNCNUM_22 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_22[BSW_COMM_CH_PNAWKPW_NUM_22] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_22 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 22U ) */
#if ( BSW_COMM_CFG_CHNUM > 23U )
#if ( BSW_COMM_CH_PNCNUM_23 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_23[BSW_COMM_CH_PNAWKPW_NUM_23] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_23 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 23U ) */
#if ( BSW_COMM_CFG_CHNUM > 24U )
#if ( BSW_COMM_CH_PNCNUM_24 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_24[BSW_COMM_CH_PNAWKPW_NUM_24] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_24 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 24U ) */
#if ( BSW_COMM_CFG_CHNUM > 25U )
#if ( BSW_COMM_CH_PNCNUM_25 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_25[BSW_COMM_CH_PNAWKPW_NUM_25] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_25 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 25U ) */
#if ( BSW_COMM_CFG_CHNUM > 26U )
#if ( BSW_COMM_CH_PNCNUM_26 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_26[BSW_COMM_CH_PNAWKPW_NUM_26] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_26 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 26U ) */
#if ( BSW_COMM_CFG_CHNUM > 27U )
#if ( BSW_COMM_CH_PNCNUM_27 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_27[BSW_COMM_CH_PNAWKPW_NUM_27] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_27 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 27U ) */
#if ( BSW_COMM_CFG_CHNUM > 28U )
#if ( BSW_COMM_CH_PNCNUM_28 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_28[BSW_COMM_CH_PNAWKPW_NUM_28] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_28 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 28U ) */
#if ( BSW_COMM_CFG_CHNUM > 29U )
#if ( BSW_COMM_CH_PNCNUM_29 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_29[BSW_COMM_CH_PNAWKPW_NUM_29] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_29 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 29U ) */
#if ( BSW_COMM_CFG_CHNUM > 30U )
#if ( BSW_COMM_CH_PNCNUM_30 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_30[BSW_COMM_CH_PNAWKPW_NUM_30] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_30 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 30U ) */
#if ( BSW_COMM_CFG_CHNUM > 31U )
#if ( BSW_COMM_CH_PNCNUM_31 > 0U )
BswConst BswU4 bsw_comm_ctrl_u4PncAwake_31[BSW_COMM_CH_PNAWKPW_NUM_31] = {
};
#endif /* ( BSW_COMM_CH_PNCNUM_31 > 0U ) */
#endif /* ( BSW_COMM_CFG_CHNUM > 31U ) */
#endif /* ( BSW_COMM_CFG_PNC_AWAKEPW == BSW_USE ) */

#endif /* (BSW_BSWM_CS_FUNC_COMM == BSW_USE) */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v3-0-0          :2024/11/14                                             */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v3-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
