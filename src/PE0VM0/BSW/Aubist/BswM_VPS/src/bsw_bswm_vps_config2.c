/* bsw_bswm_vps_config2_c_v3-0-0                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | BSW/BSWM/VPS/CONFIG2/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <cs/bsw_cs_common.h>
#include <cs/bsw_cs_system.h>
#include <cs/bsw_cs_system_memmap_pre.h>
#include <ComStack_Types.h>

#include <comm/bsw_comm.h>
#include <bswm_cs/bsw_bswm_cs.h>
#include "../../ComM/inc/bsw_comm_config.h"
#include "../../BswM_CS/inc/bsw_bswm_cs_config.h"
#include <cs/bsw_cs_system_memmap_post.h>

#if( BSW_BSWM_CS_FUNC_BSWM_VPS == BSW_USE )
#include <cs/bsw_cs_system_memmap_pre.h>
#include <bswm_vps/bsw_bswm_vps.h>
#include "../inc/bsw_bswm_vps_ctrl.h"
#include "../inc/bsw_bswm_vps_config.h"
#include "../cfg/BswM_VPS_Cfg.h"
#include <cs/bsw_cs_system_memmap_post.h>

#if( BSW_BSWM_VPS_VPSMSG_E2EUSE == BSW_USE )
#include <E2E.h>
#endif /* BSW_BSWM_VPS_VPSMSG_E2EUSE == BSW_USE */

#if( BSW_BSWM_VPS_CFG_DATA_DIV_LOC == BSW_NOUSE )
#include "../inc/bsw_bswm_vps_MemMap.h"
#else
#include "../inc/bsw_bswm_vps_MemMap2.h"
#endif /* BSW_BSWM_VPS_CFG_DATA_DIV_LOC == BSW_NOUSE */

#include "../inc/bsw_bswm_vps_ctrl2.h"

#if( BSW_BSWM_VPS_VPSMSG_E2EUSE == BSW_USE )
#include "../inc/bsw_bswm_vps_ctrl_e2e.h"
#endif /* BSW_BSWM_VPS_VPSMSG_E2EUSE == BSW_USE */

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
Bsw_BswM_VPS_StsType bsw_bswm_vps_ctrl_stSts;
BswU4                bsw_bswm_vps_ctrl_u4SysSt[BSW_BSWM_VPS_SYSSTATTBLNUM];
BswU4                bsw_bswm_vps_ctrl_u4SysStMrr[BSW_BSWM_VPS_SYSSTATTBLNUM];
BswU4                bsw_bswm_vps_ctrl_u4RxSysSt0[BSW_BSWM_VPS_SYSSTATTBLNUM];
BswU4                bsw_bswm_vps_ctrl_u4RxSysStMrr0[BSW_BSWM_VPS_SYSSTATTBLNUM];
BswU4                bsw_bswm_vps_ctrl_u4RxSysSt1[BSW_BSWM_VPS_SYSSTATTBLNUM];
BswU4                bsw_bswm_vps_ctrl_u4RxSysStMrr1[BSW_BSWM_VPS_SYSSTATTBLNUM];

#if( BSW_BSWM_VPS_AWKFACTNUM > 0U )
BswU1   bsw_bswm_vps_ctrl_u1SetWkFc[BSW_BSWM_VPS_AWKFACTNUM];
#else
BswU1   bsw_bswm_vps_ctrl_u1SetWkFc[BSW_BSWM_VPS_TBLNUM_DUMMY];
#endif /* BSW_BSWM_VPS_AWKFACTNUM > 0U */
#if( BSW_BSWM_VPS_CFG_VPS_RXPDUIDNUM > 0U )
Bsw_BswM_RxVPS_StsType bsw_bswm_vps_ctrl_stRxVPSSts[BSW_BSWM_VPS_CFG_VPS_RXPDUIDNUM];
#else
Bsw_BswM_RxVPS_StsType bsw_bswm_vps_ctrl_stRxVPSSts[BSW_BSWM_VPS_TBLNUM_DUMMY];
#endif/* BSW_BSWM_VPS_CFG_VPS_RXPDUIDNUM > 0U */

#if( BSW_BSWM_VPS_VPSMSG_E2EUSE == BSW_USE )
#if( BSW_BSWM_VPS_CFG_VPS_TXPDUIDNUM > 0U )
E2E_P05ProtectStateType   bsw_bswm_vps_stTxProtectState[BSW_BSWM_VPS_CFG_VPS_TXPDUIDNUM];
#else
E2E_P05ProtectStateType   bsw_bswm_vps_stTxProtectState[BSW_BSWM_VPS_TBLNUM_DUMMY];
#endif /* BSW_BSWM_VPS_CFG_VPS_TXPDUIDNUM > 0U */
#if( BSW_BSWM_VPS_CFG_VPS_RXPDUIDNUM > 0U )
E2E_P05CheckStateType     bsw_bswm_vps_stRxCheckState[BSW_BSWM_VPS_CFG_VPS_RXPDUIDNUM];
#else
E2E_P05CheckStateType     bsw_bswm_vps_stRxCheckState[BSW_BSWM_VPS_TBLNUM_DUMMY];
#endif /* BSW_BSWM_VPS_CFG_VPS_RXPDUIDNUM > 0U */
#endif /* BSW_BSWM_VPS_VPSMSG_E2EUSE == BSW_USE */

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

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
/*  v3-0-0          :2025/02/25                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
