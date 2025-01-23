/* bsw_bswm_vps_config_c_v3-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/VPS/CONFIG/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <ComStack_Types.h>
#include "../inc/bsw_bswm_vps_MemMap.h"

#include <comm/bsw_comm.h>
#include <bswm_cs/bsw_bswm_cs.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"

#if( BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE )
#include <bswm_vps/bsw_bswm_vps.h>
#include "../inc/bsw_bswm_vps_ctrl.h"
#include "../inc/bsw_bswm_vps_config.h"
#include "../cfg/BswM_VPS_Cfg.h"

#if( BSW_BSWM_VPS_VPSMSG_E2EUSE == BSW_USE )
#include <E2E.h>
#include "../inc/bsw_bswm_vps_ctrl_e2e.h"
#endif /* BSW_BSWM_VPS_VPSMSG_E2EUSE == BSW_USE */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define BSW_BSWM_VPS_CHANNELNUM_DUMMY          (1U)
#define BSW_BSWM_VPS_AWKFACTNUM_DUMMY          (1U)
#define BSW_BSWM_VPS_CHANNELNUM_ZERO           (0U)
#define BSW_BSWM_VPS_USERHANDLE_DUMMY          (BSW_BSWM_VPS_USERHANDLE_USRAWKNONE)
#define BSW_BSWM_VPS_u1INFO_INVALID            ((BswU1)0x00U)

#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_00 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_00      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_00      (bsw_bswm_vps_stChPncAwake_00)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_00 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_01 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_01      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_01      (bsw_bswm_vps_stChPncAwake_01)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_01 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_02 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_02      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_02      (bsw_bswm_vps_stChPncAwake_02)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_02 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_03 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_03      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_03      (bsw_bswm_vps_stChPncAwake_03)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_03 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_04 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_04      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_04      (bsw_bswm_vps_stChPncAwake_04)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_04 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_05 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_05      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_05      (bsw_bswm_vps_stChPncAwake_05)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_05 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_06 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_06      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_06      (bsw_bswm_vps_stChPncAwake_06)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_06 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_07 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_07      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_07      (bsw_bswm_vps_stChPncAwake_07)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_07 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_08 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_08      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_08      (bsw_bswm_vps_stChPncAwake_08)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_08 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_09 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_09      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_09      (bsw_bswm_vps_stChPncAwake_09)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_09 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_10 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_10      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_10      (bsw_bswm_vps_stChPncAwake_10)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_10 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_11 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_11      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_11      (bsw_bswm_vps_stChPncAwake_11)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_11 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_12 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_12      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_12      (bsw_bswm_vps_stChPncAwake_12)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_12 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_13 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_13      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_13      (bsw_bswm_vps_stChPncAwake_13)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_13 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_14 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_14      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_14      (bsw_bswm_vps_stChPncAwake_14)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_14 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_15 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_15      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_15      (bsw_bswm_vps_stChPncAwake_15)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_15 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_16 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_16      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_16      (bsw_bswm_vps_stChPncAwake_16)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_16 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_17 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_17      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_17      (bsw_bswm_vps_stChPncAwake_17)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_17 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_18 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_18      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_18      (bsw_bswm_vps_stChPncAwake_18)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_18 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_19 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_19      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_19      (bsw_bswm_vps_stChPncAwake_19)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_19 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_20 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_20      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_20      (bsw_bswm_vps_stChPncAwake_20)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_20 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_21 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_21      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_21      (bsw_bswm_vps_stChPncAwake_21)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_21 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_22 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_22      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_22      (bsw_bswm_vps_stChPncAwake_22)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_22 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_23 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_23      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_23      (bsw_bswm_vps_stChPncAwake_23)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_23 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_24 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_24      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_24      (bsw_bswm_vps_stChPncAwake_24)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_24 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_25 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_25      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_25      (bsw_bswm_vps_stChPncAwake_25)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_25 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_26 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_26      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_26      (bsw_bswm_vps_stChPncAwake_26)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_26 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_27 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_27      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_27      (bsw_bswm_vps_stChPncAwake_27)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_27 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_28 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_28      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_28      (bsw_bswm_vps_stChPncAwake_28)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_28 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_29 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_29      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_29      (bsw_bswm_vps_stChPncAwake_29)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_29 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_30 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_30      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_30      (bsw_bswm_vps_stChPncAwake_30)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_30 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U )
#if ( BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_31 == 0U )
#define BSW_BSWM_VPS_CHPNCAWAKE_31      (bsw_bswm_vps_stChPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_CHPNCAWAKE_31      (bsw_bswm_vps_stChPncAwake_31)
#endif /* BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_31 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U */

#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_00 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_00      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_00      (bsw_bswm_vps_u1CoBusAwake_00)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_00 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_01 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_01      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_01      (bsw_bswm_vps_u1CoBusAwake_01)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_01 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_02 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_02      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_02      (bsw_bswm_vps_u1CoBusAwake_02)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_02 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_03 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_03      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_03      (bsw_bswm_vps_u1CoBusAwake_03)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_03 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_04 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_04      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_04      (bsw_bswm_vps_u1CoBusAwake_04)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_04 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_05 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_05      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_05      (bsw_bswm_vps_u1CoBusAwake_05)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_05 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_06 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_06      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_06      (bsw_bswm_vps_u1CoBusAwake_06)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_06 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_07 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_07      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_07      (bsw_bswm_vps_u1CoBusAwake_07)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_07 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_08 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_08      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_08      (bsw_bswm_vps_u1CoBusAwake_08)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_08 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_09 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_09      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_09      (bsw_bswm_vps_u1CoBusAwake_09)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_09 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_10 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_10      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_10      (bsw_bswm_vps_u1CoBusAwake_10)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_10 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_11 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_11      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_11      (bsw_bswm_vps_u1CoBusAwake_11)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_11 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_12 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_12      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_12      (bsw_bswm_vps_u1CoBusAwake_12)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_12 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_13 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_13      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_13      (bsw_bswm_vps_u1CoBusAwake_13)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_13 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_14 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_14      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_14      (bsw_bswm_vps_u1CoBusAwake_14)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_14 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_15 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_15      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_15      (bsw_bswm_vps_u1CoBusAwake_15)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_15 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_16 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_16      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_16      (bsw_bswm_vps_u1CoBusAwake_16)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_16 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_17 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_17      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_17      (bsw_bswm_vps_u1CoBusAwake_17)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_17 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_18 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_18      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_18      (bsw_bswm_vps_u1CoBusAwake_18)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_18 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_19 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_19      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_19      (bsw_bswm_vps_u1CoBusAwake_19)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_19 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_20 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_20      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_20      (bsw_bswm_vps_u1CoBusAwake_20)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_20 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_21 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_21      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_21      (bsw_bswm_vps_u1CoBusAwake_21)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_21 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_22 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_22      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_22      (bsw_bswm_vps_u1CoBusAwake_22)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_22 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_23 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_23      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_23      (bsw_bswm_vps_u1CoBusAwake_23)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_23 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_24 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_24      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_24      (bsw_bswm_vps_u1CoBusAwake_24)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_24 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_25 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_25      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_25      (bsw_bswm_vps_u1CoBusAwake_25)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_25 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_26 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_26      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_26      (bsw_bswm_vps_u1CoBusAwake_26)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_26 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_27 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_27      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_27      (bsw_bswm_vps_u1CoBusAwake_27)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_27 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_28 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_28      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_28      (bsw_bswm_vps_u1CoBusAwake_28)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_28 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_29 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_29      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_29      (bsw_bswm_vps_u1CoBusAwake_29)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_29 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_30 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_30      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_30      (bsw_bswm_vps_u1CoBusAwake_30)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_30 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U )
#if ( BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_31 == 0U )
#define BSW_BSWM_VPS_COBUSAWAKE_31      (bsw_bswm_vps_u1CoBusAwake_Dummy)
#else
#define BSW_BSWM_VPS_COBUSAWAKE_31      (bsw_bswm_vps_u1CoBusAwake_31)
#endif /* BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_31 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U */

#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_00 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_00      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_00      (bsw_bswm_vps_stCoPncAwake_00)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_00 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_01 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_01      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_01      (bsw_bswm_vps_stCoPncAwake_01)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_01 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_02 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_02      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_02      (bsw_bswm_vps_stCoPncAwake_02)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_02 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_03 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_03      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_03      (bsw_bswm_vps_stCoPncAwake_03)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_03 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_04 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_04      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_04      (bsw_bswm_vps_stCoPncAwake_04)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_04 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_05 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_05      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_05      (bsw_bswm_vps_stCoPncAwake_05)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_05 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_06 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_06      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_06      (bsw_bswm_vps_stCoPncAwake_06)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_06 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_07 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_07      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_07      (bsw_bswm_vps_stCoPncAwake_07)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_07 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_08 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_08      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_08      (bsw_bswm_vps_stCoPncAwake_08)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_08 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_09 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_09      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_09      (bsw_bswm_vps_stCoPncAwake_09)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_09 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_10 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_10      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_10      (bsw_bswm_vps_stCoPncAwake_10)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_10 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_11 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_11      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_11      (bsw_bswm_vps_stCoPncAwake_11)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_11 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_12 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_12      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_12      (bsw_bswm_vps_stCoPncAwake_12)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_12 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_13 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_13      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_13      (bsw_bswm_vps_stCoPncAwake_13)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_13 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_14 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_14      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_14      (bsw_bswm_vps_stCoPncAwake_14)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_14 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_15 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_15      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_15      (bsw_bswm_vps_stCoPncAwake_15)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_15 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_16 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_16      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_16      (bsw_bswm_vps_stCoPncAwake_16)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_16 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_17 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_17      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_17      (bsw_bswm_vps_stCoPncAwake_17)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_17 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_18 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_18      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_18      (bsw_bswm_vps_stCoPncAwake_18)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_18 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_19 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_19      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_19      (bsw_bswm_vps_stCoPncAwake_19)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_19 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_20 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_20      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_20      (bsw_bswm_vps_stCoPncAwake_20)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_20 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_21 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_21      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_21      (bsw_bswm_vps_stCoPncAwake_21)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_21 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_22 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_22      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_22      (bsw_bswm_vps_stCoPncAwake_22)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_22 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_23 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_23      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_23      (bsw_bswm_vps_stCoPncAwake_23)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_23 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_24 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_24      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_24      (bsw_bswm_vps_stCoPncAwake_24)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_24 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_25 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_25      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_25      (bsw_bswm_vps_stCoPncAwake_25)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_25 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_26 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_26      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_26      (bsw_bswm_vps_stCoPncAwake_26)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_26 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_27 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_27      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_27      (bsw_bswm_vps_stCoPncAwake_27)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_27 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_28 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_28      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_28      (bsw_bswm_vps_stCoPncAwake_28)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_28 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_29 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_29      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_29      (bsw_bswm_vps_stCoPncAwake_29)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_29 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_30 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_30      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_30      (bsw_bswm_vps_stCoPncAwake_30)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_30 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U )
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_31 == 0U )
#define BSW_BSWM_VPS_COPNCAWAKE_31      (bsw_bswm_vps_stCoPncAwake_Dummy)
#else
#define BSW_BSWM_VPS_COPNCAWAKE_31      (bsw_bswm_vps_stCoPncAwake_31)
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_31 == 0U */
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U */

/* E2E Function Table */
#if ( BSW_BSWM_VPS_CFG_VPSMSG_E2EUSE == BSW_USE )
#define BSW_BSWM_VPS_E2E_INIT_FUNC          ( &bsw_bswm_vps_ctrl_E2EInit )
#define BSW_BSWM_VPS_E2E_TXPROTECT_FUNC     ( &bsw_bswm_vps_ctrl_E2ETxProtect )
#define BSW_BSWM_VPS_E2E_RXCHECK_FUNC       ( &bsw_bswm_vps_ctrl_E2ERxCheck )
#else
#define BSW_BSWM_VPS_E2E_INIT_FUNC          ( &bsw_bswm_vps_ctrl_E2EInitNone )
#define BSW_BSWM_VPS_E2E_TXPROTECT_FUNC     ( &bsw_bswm_vps_ctrl_E2ETxProtectNone )
#define BSW_BSWM_VPS_E2E_RXCHECK_FUNC       ( &bsw_bswm_vps_ctrl_E2ERxCheckNone )
#endif /* BSW_BSWM_VPS_CFG_VPSMSG_E2EUSE == BSW_USE */

/* PNC Function Table */
#if ( BSW_COMM_PNC_FUNC == BSW_USE )
#define BSW_BSWM_VPS_REQCHPNCCOMMODE_FUNC           ( &ComM_RequestChPncComMode )
#define BSW_BSWM_VPS_SETCOPNCAWAKE_FUNC             ( &ComM_SetCoPncAwake )
#else
#define BSW_BSWM_VPS_REQCHPNCCOMMODE_FUNC           ( &bsw_bswm_vps_ctrl_RequestChPncComModeNone )
#define BSW_BSWM_VPS_SETCOPNCAWAKE_FUNC             ( &bsw_bswm_vps_ctrl_SetCoPncAwakeNone )
#endif /* BSW_COMM_PNC_FUNC == BSW_USE */

/* CS Function Table */
#if ( BSW_BSWM_VPS_CFG_DATA_DIV_LOC == BSW_NOUSE )
#define BSW_BSWM_VPS_INIT_FUNC                      ( &bsw_bswm_vps_ctrl_Init )
#define BSW_BSWM_VPS_DEINIT_FUNC                    ( &bsw_bswm_vps_ctrl_DeInit )
#define BSW_BSWM_VPS_WAKEUP_FUNC                    ( &bsw_bswm_vps_ctrl_Wakeup )
#define BSW_BSWM_VPS_MAINFUNCTION_FUNC              ( &bsw_bswm_vps_ctrl_MainFunction )
#define BSW_BSWM_VPS_GETSYSTEMSTATUS_FUNC           ( &bsw_bswm_vps_ctrl_GetSysStat )
#define BSW_BSWM_VPS_TXIPDUCO_FUNC                  ( &bsw_bswm_vps_ctrl_TxIpduCoIn )
#else
#define BSW_BSWM_VPS_INIT_FUNC                      ( &bsw_bswm_vps_ctrl_InitNone )
#define BSW_BSWM_VPS_DEINIT_FUNC                    ( &bsw_bswm_vps_ctrl_DeInitNone )
#define BSW_BSWM_VPS_WAKEUP_FUNC                    ( &bsw_bswm_vps_ctrl_WakeupNone )
#define BSW_BSWM_VPS_MAINFUNCTION_FUNC              ( &bsw_bswm_vps_ctrl_MainFunctionNone )
#define BSW_BSWM_VPS_GETSYSTEMSTATUS_FUNC           ( &bsw_bswm_vps_ctrl_GetSysStatNone )
#define BSW_BSWM_VPS_TXIPDUCO_FUNC                  ( &bsw_bswm_vps_ctrl_TxIpduCoNone )
#endif /* BSW_BSWM_VPS_CFG_DATA_DIV_LOC == BSW_NOUSE */

#if (( BSW_BSWM_VPS_CFG_DATA_DIV_LOC == BSW_NOUSE ) && ( BSW_BSWM_VPS_CFG_RXVPSFIX == BSW_NOUSE ))
#define BSW_BSWM_VPS_SETSYSTEMSTATUS_FUNC           ( &bsw_bswm_vps_ctrl_SetSysStatIn )
#else
#define BSW_BSWM_VPS_SETSYSTEMSTATUS_FUNC           ( &bsw_bswm_vps_ctrl_SetSysStatNone )
#endif /* ( BSW_BSWM_VPS_CFG_DATA_DIV_LOC == BSW_NOUSE ) && ( BSW_BSWM_VPS_CFG_RXVPSFIX == BSW_NOUSE ) */

#if ( BSW_BSWM_VPS_CFG_HANDSHAKE == BSW_USE )
#define BSW_BSWM_VPS_STOPSTATHDL_FUNC               ( &bsw_bswm_vps_ctrl_StopStatHdl )
#define BSW_BSWM_VPS_TXRLYONCONFREQ_FUNC            ( &bsw_bswm_vps_ctrl_TxRlyConfReq )
#define BSW_BSWM_VPS_UPDTROCTIM_FUNC                ( &bsw_bswm_vps_ctrl_UpdtROCTimer )
#else
#define BSW_BSWM_VPS_STOPSTATHDL_FUNC               ( &bsw_bswm_vps_ctrl_StopStatHdlNone )
#define BSW_BSWM_VPS_TXRLYONCONFREQ_FUNC            ( &bsw_bswm_vps_ctrl_TxRlyConfReqNone )
#define BSW_BSWM_VPS_UPDTROCTIM_FUNC                ( &bsw_bswm_vps_ctrl_UpdtROCTimerNone )
#endif /* BSW_BSWM_VPS_CFG_HANDSHAKE == BSW_USE */

#if ( BSW_BSWM_VPS_CFG_RXVPSFIX == BSW_USE )
#define BSW_BSWM_VPS_FIXSYSST_FUNC                  ( &bsw_bswm_vps_ctrl_FixSysSt )
#else
#define BSW_BSWM_VPS_FIXSYSST_FUNC                  ( &bsw_bswm_vps_ctrl_FixSysStNone )
#endif /* BSW_BSWM_VPS_CFG_RXVPSFIX == BSW_USE */

#if (( BSW_BSWM_VPS_CFG_DATA_DIV_LOC == BSW_USE ) || ( BSW_BSWM_VPS_CFG_RXVPSFIX == BSW_USE ))
#define BSW_BSWM_VPS_SETFIXEDST_FUNC                ( &bsw_bswm_vps_ctrl_SetFixedSt )
#else
#define BSW_BSWM_VPS_SETFIXEDST_FUNC                ( &bsw_bswm_vps_ctrl_SetFixedStNone )
#endif /* ( BSW_BSWM_VPS_CFG_DATA_DIV_LOC == BSW_USE ) && ( BSW_BSWM_VPS_CFG_RXVPSFIX == BSW_NOUSE ) */

#if ( BSW_BSWM_VPS_CFG_VPSTO != 0U )
#define BSW_BSWM_VPS_CKRXVPSTO_FUNC                 ( &bsw_bswm_vps_ctrl_CkRxVPSTO )
#else
#define BSW_BSWM_VPS_CKRXVPSTO_FUNC                 ( &bsw_bswm_vps_ctrl_CkRxVPSTONone )
#endif /* BSW_BSWM_VPS_CFG_VPSTO != 0U */

#if ( BSW_BSWM_VPS_CFG_VPS_TXPDUIDNUM != 0U )
#define BSW_BSWM_VPS_TXVPSMSG_FUNC                  ( &bsw_bswm_vps_ctrl_TxVPSMsg )
#else
#define BSW_BSWM_VPS_TXVPSMSG_FUNC                  ( &bsw_bswm_vps_ctrl_TxVPSMsgNone )
#endif /* BSW_BSWM_VPS_CFG_VPS_TXPDUIDNUM != 0U */

#if ( BSW_BSWM_VPS_CFG_VPS_RXPDUIDNUM != 0U )
#define BSW_BSWM_VPS_RXVPSMSG_FUNC                  ( &bsw_bswm_vps_ctrl_RxVPSMsg )
#else
#define BSW_BSWM_VPS_RXVPSMSG_FUNC                  ( &bsw_bswm_vps_ctrl_RxVPSMsgNone )
#endif /* BSW_BSWM_VPS_CFG_VPS_TXPDUIDNUM != 0U */

#if ( (BSW_BSWM_VPS_CFG_RLYONCONFREQ_RXPDUIDNUM + BSW_BSWM_VPS_CFG_RLYONCONFRES_RXPDUIDNUM) != 0U )
#define BSW_BSWM_VPS_RXRLYMSG_FUNC                  ( &bsw_bswm_vps_ctrl_RxRlyMsg )
#else
#define BSW_BSWM_VPS_RXRLYMSG_FUNC                  ( &bsw_bswm_vps_ctrl_RxRlyMsgNone )
#endif /* (BSW_BSWM_VPS_CFG_RLYONCONFREQ_RXPDUIDNUM + BSW_BSWM_VPS_CFG_RLYONCONFRES_RXPDUIDNUM) != 0U */
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
Bsw_BswM_VPS_RxPncEvntType bsw_bswm_vps_ctrl_stRxPncEvnt;

#if( BSW_BSWM_VPS_RX_MESSAGE_NUM > 0U )
BswU1 bsw_bswm_vps_u1RxEvent[BSW_BSWM_VPS_RX_MESSAGE_NUM];
BswU1 bsw_bswm_vps_u1RxStatus[BSW_BSWM_VPS_RX_MESSAGE_NUM];
#else
BswU1 bsw_bswm_vps_u1RxEvent[BSW_BSWM_VPS_TBLNUM_DUMMY];
BswU1 bsw_bswm_vps_u1RxStatus[BSW_BSWM_VPS_TBLNUM_DUMMY];
#endif /* BSW_BSWM_VPS_RX_MESSAGE_NUM > 0U */
/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
/* Vehicle Power State */
BswConst BswU1  bsw_bswm_vps_u1VehiPwStNum      = (BswU1)BSW_BSWM_VPS_CFG_VPS_NUM;
BswConst BswU1  bsw_bswm_vps_u1VehiPwStSpNum    = (BswU1)BSW_BSWM_VPS_CFG_VPSSP_NUM;
BswConst BswU1  bsw_bswm_vps_u1RxVPSFix         = (BswU1)BSW_BSWM_VPS_CFG_RXVPSFIX;

/* Message */
BswConst BswU1  bsw_bswm_vps_u1PwStPos          = (BswU1)BSW_BSWM_VPS_CFG_VPS_POS;
BswConst BswU1  bsw_bswm_vps_u1PwStSpPos        = (BswU1)BSW_BSWM_VPS_CFG_VPSSP_POS;
BswConst BswU1  bsw_bswm_vps_u1PwStSpTransPos   = (BswU1)BSW_BSWM_VPS_CFG_VPSSPTRANS_POS;
BswConst BswU1  bsw_bswm_vps_u1PwStSpOtaPos     = (BswU1)BSW_BSWM_VPS_CFG_VPSSP_OTA_POS;
BswConst BswU1  bsw_bswm_vps_u1PwStSpTransOnBit = (BswU1)BSW_BSWM_VPS_CFG_VPSSPTRANS_ON_BIT;
BswConst BswU1  bsw_bswm_vps_u1PwStSpTransOffBit= (BswU1)BSW_BSWM_VPS_CFG_VPSSPTRANS_OFF_BIT;

BswConst BswU1  bsw_bswm_vps_u1VhPwStRxPduIdNum       = (BswU1)BSW_BSWM_VPS_CFG_VPS_RXPDUIDNUM;
BswConst BswU1  bsw_bswm_vps_u1RxPduIdNum             = (BswU1)BSW_BSWM_VPS_RX_MESSAGE_NUM;
BswConst BswU1  bsw_bswm_vps_u1VhPwStTxPduIdNum       = (BswU1)BSW_BSWM_VPS_CFG_VPS_TXPDUIDNUM;
BswConst BswU1  bsw_bswm_vps_u1RlyOnConfReqTxPduIdNum = (BswU1)BSW_BSWM_VPS_CFG_RLYONCONFREQ_TXPDUIDNUM;
BswConst BswU1  bsw_bswm_vps_u1TxPduIdNum             = (BswU1)BSW_BSWM_VPS_TX_MESSAGE_NUM;

BswConst BswU1  bsw_bswm_vps_u1VpsMsgE2EUse           = (BswU1)BSW_BSWM_VPS_CFG_VPSMSG_E2EUSE;
BswConst BswU1  bsw_bswm_vps_u1E2ERxCntError          = (BswU1)BSW_BSWM_VPS_CFG_E2E_RXCNTERROR;

BswConst BswU1  bsw_bswm_vps_u1RlyOnConfBytePos = (BswU1)BSW_BSWM_VPS_CFG_RLYONCONF_BYTE_POS;
BswConst BswU1  bsw_bswm_vps_u1RlyOnConfBitPos  = (BswU1)BSW_BSWM_VPS_CFG_RLYONCONF_BIT_POS;

BswConst BswU1  bsw_bswm_vps_u1GlobalBus0       = (BswU1)BSW_BSWM_VPS_CFG_GLOBALBUS_0;
BswConst BswU1  bsw_bswm_vps_u1GlobalBus1       = (BswU1)BSW_BSWM_VPS_CFG_GLOBALBUS_1;

BswConst BswU2  bsw_bswm_vps_u2VpsRxTOTim       = BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_VPS_CFG_VPSTO);
BswConst BswU2  bsw_bswm_vps_u2VpsFirstRxTOTim  = BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_VPS_CFG_VPSTO + BSW_BSWM_VPS_CFG_VPSTO_PWONMSK);

#if( BSW_BSWM_VPS_VPSMSG_E2EUSE == BSW_USE )
BswConst BswU1  bsw_bswm_vps_u1E2EProtectTxMsgNum = (BswU1)BSW_BSWM_VPS_CFG_VPS_TXPDUIDNUM;
BswConst BswU1  bsw_bswm_vps_u1E2EProtectRxMsgNum = (BswU1)BSW_BSWM_VPS_CFG_VPS_RXPDUIDNUM;
#endif /* BSW_BSWM_VPS_VPSMSG_E2EUSE == BSW_USE */

/* Handshake */
BswConst BswU2  bsw_bswm_vps_u2RlyOnConfTOTim   = BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_VPS_CFG_RLYONCONFTO);
BswConst BswU1  bsw_bswm_vps_u1HandShake        = (BswU1)BSW_BSWM_VPS_CFG_HANDSHAKE;

/* Wakeup Factor */
BswConst BswU1  bsw_bswm_vps_u1AwkFctNum        = (BswU1)BSW_BSWM_VPS_CFG_AWKFACTNUM;
BswConst BswU1  bsw_bswm_vps_u1ConPncAwkHdskNum = (BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_HDSK_CHNUM;

BswConst BswU2  bsw_bswm_vps_u2WfChgVPS         = (BswU2)BSW_BSWM_VPS_CFG_WF_CHGVPS;
BswConst BswU2  bsw_bswm_vps_u2WfReset          = (BswU2)BSW_BSWM_VPS_CFG_WF_RESET;
BswConst BswU2  bsw_bswm_vps_u2WfRxPnc          = (BswU2)BSW_BSWM_VPS_CFG_WF_RXPNC;

BswConst BswU2  bsw_bswm_vps_u2WfChgVPSTim      = BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_VPS_CFG_WF_CHGVPS_TIME);
BswConst BswU2  bsw_bswm_vps_u2WfResetTim       = BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_VPS_CFG_WF_RESET_TIME);
BswConst BswU2  bsw_bswm_vps_u2WfRxPncTim       = BSW_BSWM_CS_u2MS2TICK_RUP_MID(BSW_BSWM_VPS_CFG_WF_RXPNC_TIME);

BswConst BswU4  bsw_bswm_vps_u4WfPncLo          = (BswU4)BSW_BSWM_VPS_CFG_WF_PNCLO;
BswConst BswU4  bsw_bswm_vps_u4WfPncUp          = (BswU4)BSW_BSWM_VPS_CFG_WF_PNCUP;

/* Dummy Table */
BswConst Bsw_BswM_VPS_ChPncAwakeType bsw_bswm_vps_stChPncAwake_Dummy[BSW_BSWM_VPS_AWKFACTNUM_DUMMY] =
{
    { (BswU4)BSW_COMM_PNCAWAKE_NONE, (BswU4)BSW_COMM_PNCAWAKE_NONE, (BswU1)BSW_BSWM_VPS_CHANNEL_INVALID, (BswU1)0U, (BswU1)0U, (BswU1)0U }
};

BswConst BswU1 bsw_bswm_vps_u1CoBusAwake_Dummy[BSW_BSWM_VPS_AWKFACTNUM_DUMMY] = 
{
    (BswU1)BSW_BSWM_VPS_CHANNEL_INVALID
};

BswConst Bsw_BswM_VPS_CoPncAwakeType bsw_bswm_vps_stCoPncAwake_Dummy[BSW_BSWM_VPS_AWKFACTNUM_DUMMY] =
{
    { (BswU4)BSW_COMM_PNCAWAKE_NONE, (BswU4)BSW_COMM_PNCAWAKE_NONE, (BswU1)BSW_BSWM_VPS_CHANNEL_INVALID, (BswU1)0U, (BswU1)0U, (BswU1)0U }
};

/***********************/
/* Wakeup Factor Table */
/***********************/
/* UserHandle Table */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U )
BswConst BswU1 bsw_bswm_vps_u1UserHandleTbl[BSW_BSWM_VPS_CFG_AWKFACTNUM] = 
{
    BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_00
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_01
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_02
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_03
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_04
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_05
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_06
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_07
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_08
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_09
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_10
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_11
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_12
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_13
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_14
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_15
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_16
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_17
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_18
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_19
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_20
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_21
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_22
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_23
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_24
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_25
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_26
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_27
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_28
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_29
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_30
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U )
   ,BSW_BSWM_VPS_CFG_AWKFACT_USRAWAKE_31
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U */
};
#else /* BSW_BSWM_VPS_CFG_AWKFACTNUM == 0U */
BswConst BswU1 bsw_bswm_vps_u1UserHandleTbl[BSW_BSWM_VPS_AWKFACTNUM_DUMMY] =
{ BSW_BSWM_VPS_USERHANDLE_DUMMY };
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U */

/* ChPncAwake Table */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U )
BswConst Bsw_BswM_VPS_ChPncAwakeType* bsw_bswm_vps_ptChPncAwake[BSW_BSWM_VPS_CFG_AWKFACTNUM] =
{
    BSW_BSWM_VPS_CHPNCAWAKE_00
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_01
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_02
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_03
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_04
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_05
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_06
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_07
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_08
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_09
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_10
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_11
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_12
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_13
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_14
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_15
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_16
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_17
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_18
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_19
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_20
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_21
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_22
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_23
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_24
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_25
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_26
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_27
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_28
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_29
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_30
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U )
   ,BSW_BSWM_VPS_CHPNCAWAKE_31
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U */
};
#else /* BSW_BSWM_VPS_CFG_AWKFACTNUM == 0U */
BswConst Bsw_BswM_VPS_ChPncAwakeType* bsw_bswm_vps_ptChPncAwake[BSW_BSWM_VPS_AWKFACTNUM_DUMMY] =
{ bsw_bswm_vps_stChPncAwake_Dummy };
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U */

/* ChPncAwake Table */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U )
BswConst BswU1* bsw_bswm_vps_ptCoBusAwake[BSW_BSWM_VPS_CFG_AWKFACTNUM] =
{
    BSW_BSWM_VPS_COBUSAWAKE_00
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U )
   ,BSW_BSWM_VPS_COBUSAWAKE_01
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U )
   ,BSW_BSWM_VPS_COBUSAWAKE_02
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U )
   ,BSW_BSWM_VPS_COBUSAWAKE_03
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U )
   ,BSW_BSWM_VPS_COBUSAWAKE_04
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U )
   ,BSW_BSWM_VPS_COBUSAWAKE_05
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U )
   ,BSW_BSWM_VPS_COBUSAWAKE_06
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U )
   ,BSW_BSWM_VPS_COBUSAWAKE_07
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U )
   ,BSW_BSWM_VPS_COBUSAWAKE_08
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U )
   ,BSW_BSWM_VPS_COBUSAWAKE_09
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U )
   ,BSW_BSWM_VPS_COBUSAWAKE_10
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U )
   ,BSW_BSWM_VPS_COBUSAWAKE_11
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U )
   ,BSW_BSWM_VPS_COBUSAWAKE_12
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U )
   ,BSW_BSWM_VPS_COBUSAWAKE_13
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U )
   ,BSW_BSWM_VPS_COBUSAWAKE_14
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U )
   ,BSW_BSWM_VPS_COBUSAWAKE_15
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U )
   ,BSW_BSWM_VPS_COBUSAWAKE_16
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U )
   ,BSW_BSWM_VPS_COBUSAWAKE_17
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U )
   ,BSW_BSWM_VPS_COBUSAWAKE_18
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U )
   ,BSW_BSWM_VPS_COBUSAWAKE_19
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U )
   ,BSW_BSWM_VPS_COBUSAWAKE_20
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U )
   ,BSW_BSWM_VPS_COBUSAWAKE_21
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U )
   ,BSW_BSWM_VPS_COBUSAWAKE_22
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U )
   ,BSW_BSWM_VPS_COBUSAWAKE_23
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U )
   ,BSW_BSWM_VPS_COBUSAWAKE_24
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U )
   ,BSW_BSWM_VPS_COBUSAWAKE_25
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U )
   ,BSW_BSWM_VPS_COBUSAWAKE_26
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U )
   ,BSW_BSWM_VPS_COBUSAWAKE_27
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U )
   ,BSW_BSWM_VPS_COBUSAWAKE_28
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U )
   ,BSW_BSWM_VPS_COBUSAWAKE_29
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U )
   ,BSW_BSWM_VPS_COBUSAWAKE_30
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U )
   ,BSW_BSWM_VPS_COBUSAWAKE_31
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U */
};
#else /* BSW_BSWM_VPS_CFG_AWKFACTNUM == 0U */
BswConst BswU1* bsw_bswm_vps_ptCoBusAwake[BSW_BSWM_VPS_AWKFACTNUM_DUMMY] =
{ bsw_bswm_vps_u1CoBusAwake_Dummy };
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U */

/* CoPncAwake Table */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U )
BswConst Bsw_BswM_VPS_CoPncAwakeType* bsw_bswm_vps_ptCoPncAwake[BSW_BSWM_VPS_CFG_AWKFACTNUM] =
{
    BSW_BSWM_VPS_COPNCAWAKE_00
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U )
   ,BSW_BSWM_VPS_COPNCAWAKE_01
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U )
   ,BSW_BSWM_VPS_COPNCAWAKE_02
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U )
   ,BSW_BSWM_VPS_COPNCAWAKE_03
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U )
   ,BSW_BSWM_VPS_COPNCAWAKE_04
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U )
   ,BSW_BSWM_VPS_COPNCAWAKE_05
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U )
   ,BSW_BSWM_VPS_COPNCAWAKE_06
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U )
   ,BSW_BSWM_VPS_COPNCAWAKE_07
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U )
   ,BSW_BSWM_VPS_COPNCAWAKE_08
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U )
   ,BSW_BSWM_VPS_COPNCAWAKE_09
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U )
   ,BSW_BSWM_VPS_COPNCAWAKE_10
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U )
   ,BSW_BSWM_VPS_COPNCAWAKE_11
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U )
   ,BSW_BSWM_VPS_COPNCAWAKE_12
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U )
   ,BSW_BSWM_VPS_COPNCAWAKE_13
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U )
   ,BSW_BSWM_VPS_COPNCAWAKE_14
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U )
   ,BSW_BSWM_VPS_COPNCAWAKE_15
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U )
   ,BSW_BSWM_VPS_COPNCAWAKE_16
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U )
   ,BSW_BSWM_VPS_COPNCAWAKE_17
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U )
   ,BSW_BSWM_VPS_COPNCAWAKE_18
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U )
   ,BSW_BSWM_VPS_COPNCAWAKE_19
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U )
   ,BSW_BSWM_VPS_COPNCAWAKE_20
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U )
   ,BSW_BSWM_VPS_COPNCAWAKE_21
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U )
   ,BSW_BSWM_VPS_COPNCAWAKE_22
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U )
   ,BSW_BSWM_VPS_COPNCAWAKE_23
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U )
   ,BSW_BSWM_VPS_COPNCAWAKE_24
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U )
   ,BSW_BSWM_VPS_COPNCAWAKE_25
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U )
   ,BSW_BSWM_VPS_COPNCAWAKE_26
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U )
   ,BSW_BSWM_VPS_COPNCAWAKE_27
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U )
   ,BSW_BSWM_VPS_COPNCAWAKE_28
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U )
   ,BSW_BSWM_VPS_COPNCAWAKE_29
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U )
   ,BSW_BSWM_VPS_COPNCAWAKE_30
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U )
   ,BSW_BSWM_VPS_COPNCAWAKE_31
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U */
};
#else /* BSW_BSWM_VPS_CFG_AWKFACTNUM == 0U */
BswConst Bsw_BswM_VPS_CoPncAwakeType* bsw_bswm_vps_ptCoPncAwake[BSW_BSWM_VPS_AWKFACTNUM_DUMMY] =
{ bsw_bswm_vps_stCoPncAwake_Dummy };
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U */

/* ChPncChNum Tbl */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U )
BswConst BswU1 bsw_bswm_vps_u1ChPncChNumTbl[BSW_BSWM_VPS_CFG_AWKFACTNUM] = 
{
    (BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_00
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_01
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_02
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_03
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_04
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_05
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_06
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_07
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_08
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_09
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_10
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_11
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_12
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_13
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_14
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_15
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_16
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_17
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_18
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_19
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_20
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_21
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_22
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_23
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_24
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_25
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_26
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_27
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_28
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_29
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_30
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U )
   ,(BswU1)BSW_BSWM_VPS_CFG_CHPNCAWAKE_CHNUM_31
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U */
};
#else /* BSW_BSWM_VPS_CFG_AWKFACTNUM == 0U */
BswConst BswU1 bsw_bswm_vps_u1ChPncChNumTbl[BSW_BSWM_VPS_CHANNELNUM_DUMMY] = 
{ (BswU1)BSW_BSWM_VPS_CHANNELNUM_ZERO };
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U */

/* CoBusChNum Tbl */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U )
BswConst BswU1 bsw_bswm_vps_u1CoBusChNumTbl[BSW_BSWM_VPS_CFG_AWKFACTNUM] = 
{
    (BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_00
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_01
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_02
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_03
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_04
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_05
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_06
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_07
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_08
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_09
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_10
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_11
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_12
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_13
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_14
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_15
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_16
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_17
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_18
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_19
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_20
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_21
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_22
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_23
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_24
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_25
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_26
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_27
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_28
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_29
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_30
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COBUSAWAKE_CHNUM_31
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U */
};
#else /* BSW_BSWM_VPS_CFG_AWKFACTNUM == 0U */
BswConst BswU1 bsw_bswm_vps_u1CoBusChNumTbl[BSW_BSWM_VPS_CHANNELNUM_DUMMY] = 
{ (BswU1)BSW_BSWM_VPS_CHANNELNUM_ZERO };
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U */

/* CoPncChNum Tbl */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U )
BswConst BswU1 bsw_bswm_vps_u1CoPncChNumTbl[BSW_BSWM_VPS_CFG_AWKFACTNUM] = 
{
    (BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_00
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_01
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 1U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_02
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 2U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_03
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 3U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_04
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 4U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_05
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 5U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_06
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 6U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_07
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 7U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_08
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 8U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_09
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 9U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_10
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 10U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_11
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 11U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_12
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 12U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_13
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 13U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_14
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 14U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_15
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 15U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_16
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 16U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_17
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 17U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_18
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 18U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_19
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 19U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_20
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 20U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_21
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 21U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_22
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 22U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_23
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 23U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_24
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 24U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_25
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 25U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_26
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 26U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_27
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 27U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_28
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 28U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_29
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 29U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_30
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 30U */
#if ( BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U )
   ,(BswU1)BSW_BSWM_VPS_CFG_COPNCAWAKE_CHNUM_31
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 31U */
};
#else /* BSW_BSWM_VPS_CFG_AWKFACTNUM == 0U */
BswConst BswU1 bsw_bswm_vps_u1CoPncChNumTbl[BSW_BSWM_VPS_CHANNELNUM_DUMMY] = 
{ (BswU1)BSW_BSWM_VPS_CHANNELNUM_ZERO };
#endif /* BSW_BSWM_VPS_CFG_AWKFACTNUM > 0U */

/* E2E Function Table */
void    (* BswConst bsw_bswm_vps_ctrl_ptE2EInitFn)( void )                                = BSW_BSWM_VPS_E2E_INIT_FUNC;
void    (* BswConst bsw_bswm_vps_ctrl_ptE2ETxProtectFn)( uint8 u1TxIdx, uint8* DataPtr )  = BSW_BSWM_VPS_E2E_TXPROTECT_FUNC;
boolean (* BswConst bsw_bswm_vps_ctrl_ptE2ERxCheckFn)( uint8 u1TxIdx, uint8* DataPtr )    = BSW_BSWM_VPS_E2E_RXCHECK_FUNC;

/* PNC Function Table */
Std_ReturnType    (* BswConst bsw_bswm_vps_ctrl_ptReqChPNCComModeFn)( NetworkHandleType Channel, Bsw_ComM_UserHandleType User, Bsw_ComM_ModeType ComMode ) = BSW_BSWM_VPS_REQCHPNCCOMMODE_FUNC;
Std_ReturnType    (* BswConst bsw_bswm_vps_ctrl_ptSetCoPncAwakeFn)( NetworkHandleType Channel, uint32 PncAwakeLo, uint32 PncAwakeUp )                      = BSW_BSWM_VPS_SETCOPNCAWAKE_FUNC;

/* CS Function Table */
void    (* BswConst bsw_bswm_vps_ctrl_ptInitFn)( void )                 = BSW_BSWM_VPS_INIT_FUNC;
void    (* BswConst bsw_bswm_vps_ctrl_ptDeInitFn)( void )               = BSW_BSWM_VPS_DEINIT_FUNC;
void    (* BswConst bsw_bswm_vps_ctrl_ptWakeupFn)( void )               = BSW_BSWM_VPS_WAKEUP_FUNC;
void    (* BswConst bsw_bswm_vps_ctrl_ptMainFunctionFn)( void )         = BSW_BSWM_VPS_MAINFUNCTION_FUNC;
void    (* BswConst bsw_bswm_vps_ctrl_ptGetSystemStatusFn)( uint32* SysStatus )               = BSW_BSWM_VPS_GETSYSTEMSTATUS_FUNC;
void    (* BswConst bsw_bswm_vps_ctrl_ptSetSystemStatusFn)( uint32* Mask, uint32* SysStatus ) = BSW_BSWM_VPS_SETSYSTEMSTATUS_FUNC;
void    (* BswConst bsw_bswm_vps_ctrl_ptFixSysStFn)( void )             = BSW_BSWM_VPS_FIXSYSST_FUNC;
void    (* BswConst bsw_bswm_vps_ctrl_ptSetFixedStFn)( void )           = BSW_BSWM_VPS_SETFIXEDST_FUNC;
void    (* BswConst bsw_bswm_vps_ctrl_ptCkRxVPSTOFn)( void )            = BSW_BSWM_VPS_CKRXVPSTO_FUNC;
void    (* BswConst bsw_bswm_vps_ctrl_ptTxVpsMsgFn)( void )             = BSW_BSWM_VPS_TXVPSMSG_FUNC;
void    (* BswConst bsw_bswm_vps_ctrl_ptRxVpsMsgFn)( uint8 u1RxEvntIdx, uint8 *SduDataPtr )                  = BSW_BSWM_VPS_RXVPSMSG_FUNC;
void    (* BswConst bsw_bswm_vps_ctrl_ptRxRlyMsgFn)( uint8 u1RxEvntIdx, uint8 *SduDataPtr, uint8 u1RxEvent ) = BSW_BSWM_VPS_RXRLYMSG_FUNC;
void    (* BswConst bsw_bswm_vps_ctrl_ptTxIpduCoFn)( PduIdType PduId, PduInfoType* PduInfoPtr )              = BSW_BSWM_VPS_TXIPDUCO_FUNC;

/* RlyOnConf Function Table */
void    (* BswConst bsw_bswm_vps_ctrl_ptStopStatHdlFn)( void )          = BSW_BSWM_VPS_STOPSTATHDL_FUNC;
void    (* BswConst bsw_bswm_vps_ctrl_ptTxRlyOnConfReqFn)( void )       = BSW_BSWM_VPS_TXRLYONCONFREQ_FUNC;
void    (* BswConst bsw_bswm_vps_ctrl_ptUpdtROCTimFn)( void )           = BSW_BSWM_VPS_UPDTROCTIM_FUNC;

/****************/
/* Dummy CfgTbl */
/****************/
/* E2E Message Info Table */
#if( BSW_BSWM_VPS_VPSMSG_E2EUSE == BSW_USE )
#if ( BSW_BSWM_VPS_CFG_VPS_TXPDUIDNUM == 0U )
BswConst E2E_P05ConfigType bsw_bswm_vps_stTxE2EMsgInfoTbl[BSW_BSWM_VPS_TBLNUM_DUMMY] =
{
    /* Offset, DataLength, DataID, MaxDeltaCounter */
    { (BswU2)0x0000, (BswU2)0x0000, (BswU2)0x0000, (BswU1)0x00 }
};
#endif /* BSW_BSWM_VPS_CFG_VPS_TXPDUIDNUM == 0U */

#if( BSW_BSWM_VPS_CFG_VPS_RXPDUIDNUM == 0U )
BswConst E2E_P05ConfigType bsw_bswm_vps_stRxE2EMsgInfoTbl[BSW_BSWM_VPS_TBLNUM_DUMMY] =
{
    /* Offset, DataLength, DataID, MaxDeltaCounter */
    { (BswU2)0x0000, (BswU2)0x0000, (BswU2)0x0000, (BswU1)0x00 }
};
#endif /* BSW_BSWM_VPS_CFG_VPS_RXPDUIDNUM == 0U */
#endif /* BSW_BSWM_VPS_VPSMSG_E2EUSE == BSW_USE */

/* Vehicle Power State Table */
#if( BSW_BSWM_VPS_CFG_VPS_NUM == 0U )
BswConst BswU4 bsw_bswm_vps_u4SysStVPS[BSW_BSWM_VPS_TBLNUM_DUMMY][BSW_BSWM_VPS_SYSSTATTBLNUM] = {
    { (BswU4)BSW_BSWM_CS_SYSSTAT_BAT, (BswU4)BSW_BSWM_CS_SYSSTAT_NONE }
};

BswConst BswU1 bsw_bswm_vps_u1Info[BSW_BSWM_VPS_TBLNUM_DUMMY] = {
    BSW_BSWM_VPS_u1INFO_INVALID
};
#endif /* BSW_BSWM_VPS_CFG_VPS_NUM == 0U */

/* Vehicle Power State (Special) Table */
#if( BSW_BSWM_VPS_CFG_VPSSP_NUM == 0U )
BswConst BswU4 bsw_bswm_vps_u4SysStVPSSp[BSW_BSWM_VPS_TBLNUM_DUMMY][BSW_BSWM_VPS_SYSSTATTBLNUM] = {
    { (BswU4)BSW_BSWM_CS_SYSSTAT_BAT, (BswU4)BSW_BSWM_CS_SYSSTAT_NONE }
};

BswConst Bsw_BswM_VPS_InfoSpType bsw_bswm_vps_stInfoSpTbl[BSW_BSWM_VPS_TBLNUM_DUMMY] = {
    { BSW_BSWM_VPS_u1INFO_INVALID, BSW_BSWM_VPS_u1INFO_INVALID }
};
#endif /* BSW_BSWM_VPS_CFG_VPSSP_NUM == 0U */

/* Rx Message Table */
#if( BSW_BSWM_VPS_RX_MESSAGE_NUM == 0U )
BswConst Bsw_BswM_VPS_RxMsgType bsw_bswm_vps_stRxMsgTbl[BSW_BSWM_VPS_TBLNUM_DUMMY] = {
    { (BswU2)0U, (BswU1)0U, (BswU1)BSW_BSWM_VPS_MSG_VPS, (BswU2)BSW_BSWM_VPS_PDUID_INVALID }
};
#endif /* BSW_BSWM_VPS_RX_MESSAGE_NUM == 0U */

/* Tx Message Table */
#if( BSW_BSWM_VPS_TX_MESSAGE_NUM == 0U )
BswConst Bsw_BswM_VPS_TxMsgType bsw_bswm_vps_stTxMsgTbl[BSW_BSWM_VPS_TBLNUM_DUMMY] = {
    { (BswU2)0U, (BswU1)BSW_BSWM_VPS_MSG_VPS, (BswU1)0U }
};
#endif /* BSW_BSWM_VPS_TX_MESSAGE_NUM == 0U */

/* CoPncAwake Table for HandShake */
#if ( BSW_BSWM_VPS_CFG_COPNCAWAKE_HDSK_CHNUM == 0U )
BswConst Bsw_BswM_VPS_CoPncAwakeType bsw_bswm_vps_stCoPncAwake_HandShake[BSW_BSWM_VPS_CHANNELNUM_DUMMY] = 
{
    { (BswU4)BSW_COMM_PNCAWAKE_NONE, (BswU4)BSW_COMM_PNCAWAKE_NONE, (BswU1)BSW_BSWM_VPS_CHANNEL_INVALID, (BswU1)0U, (BswU1)0U, (BswU1)0U }
};
#endif /* BSW_BSWM_VPS_CFG_COPNCAWAKE_HDSK_CHNUM == 0U */

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif /* BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE */

/****************************************************************************/
/* History                                                                  */
/*  Version         :Date                                                   */
/*  v3-0-0          :2024/11/14                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
