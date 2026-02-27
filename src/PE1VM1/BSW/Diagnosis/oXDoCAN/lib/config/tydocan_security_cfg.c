/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET based on AUBIST/DEM, DCM                                                                                */
/*  SID27                                                                                                                            */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_SECURITY_CFG_C_MAJOR             (1U)
#define TYDOCAN_SECURITY_CFG_C_MINOR             (1U)
#define TYDOCAN_SECURITY_CFG_C_PATCH             (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "tydocan_security_cfg_private.h"
#include "oxdocan_aubif.h"
#ifdef ES_INSPECT_H  
#include "es_inspect.h"
#endif

#include "NvM.h"
#include "memfill_u2.h"
#include "memfill_u1.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Application Headers */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (TYDOCAN_SECURITY_CFG_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "tydocan_security_cfg.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_SECURITY_CFG_C_MAJOR != TYDOCAN_SECURITY_CFG_H_MAJOR) || \
     (TYDOCAN_SECURITY_CFG_C_MINOR != TYDOCAN_SECURITY_CFG_H_MINOR) || \
     (TYDOCAN_SECURITY_CFG_C_PATCH != TYDOCAN_SECURITY_CFG_H_PATCH))
#error "tydocan_security_cfg.c and tydocan_security_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_SECURITY_SEED_NBYTE                 (16U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4                      u4_key_adr;
    U1                      u1_level;
}ST_TYDC_SECURITY_KEYCFG;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXDC_IDS_REQ_SUP == 1U)
static U1        u1_s_tydc_security_chk;                                     /* Tool authentication error DTC */
static U2        u2_s_tydc_security_ctx;

static U4        u4_s_tydc_security_evt_cnt;
#endif      /* #if (OXCAN_IDS_REQ_SUP == 1U) */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXDC_IDS_REQ_SUP == 1U)
static void      vd_s_TyDoCANSecCfgEvCapt_U2B76(const U1 u1_a_SECID, const U1 u1_a_NRC);
#endif      /* #if (OXCAN_IDS_REQ_SUP == 1U) */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void   vd_g_TyDoCANSecurityCfgInit(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_g_TyDoCANSecurityCfgInit(void)
{
#if (OXDC_IDS_REQ_SUP == 1U)
    U1                      u1_t_ret;

    u1_s_tydc_security_chk         = (U1)OXDC_DTC_TR_UNK;
    u2_s_tydc_security_ctx         = (U2)0x0000U;
#ifdef OXDOCAN_27_IN_VM1
    u1_t_ret = u1_g_Nvmc_ReadU4withSts((U2)NVMCID_U4_OXDC_TAECNT_001, &u4_s_tydc_security_evt_cnt);
    if(u1_t_ret != (U1)NVMC_STATUS_COMP){
        u4_s_tydc_security_evt_cnt = (U4)0U;
    }
#else
    u4_s_tydc_security_evt_cnt = 0U;
#endif
#endif      /* #if (OXCAN_IDS_REQ_SUP == 1U) */
}
/*===================================================================================================================================*/
/*  U1   u1_g_TyDoCANSecurityCfgGetSeed(const U1 u1_a_ID, const Dcm_OpStatusType OpStatus, U1 * u1_ap_seed)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1   u1_g_TyDoCANSecurityCfgGetSeed(const U1 u1_a_ID, const Dcm_OpStatusType OpStatus, U1 * u1_ap_seed)
{
    U1                      u1_t_ret;

    switch(OpStatus)
    {
    case DCM_INITIAL:
        if((u1_a_ID >= (U1)OXDC_SECURITY_ID01) &&
           (u1_a_ID <= (U1)OXDC_SECURITY_ID02)){
            u1_t_ret = (U1)E_OK;
        }
        else{
            u1_t_ret = (U1)E_NOT_OK;
        }
        break;
    case DCM_CANCEL:
        u1_t_ret = (U1)E_OK;
        break;
    case DCM_PENDING:
        vd_g_MemfillU1(&(u1_ap_seed[0]),  (U1)0U, (U4)TYDC_SECURITY_SEED_NBYTE);
        u1_t_ret = (U1)E_OK;
        break;
    default:
        u1_t_ret = (U1)E_NOT_OK;
        break;
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  U1     u1_g_TyDoCANSecurityCfgCompareKey(const U1 u1_a_ID, const U1 * u1_ap_KEY)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1     u1_g_TyDoCANSecurityCfgCompareKey(const U1 u1_a_ID, const U1 * u1_ap_KEY)
{
    U1  u1_t_result;
    U1  u1_t_ret;

    u1_t_ret    = (U1)E_NOT_OK;
    u1_t_result = (U1)TRUE; /* Fix to be True for temp, Key will be compared by SEC  */
    if(u1_t_result == (U1)TRUE){
        u1_t_ret    = (U1)E_OK;
        if(u1_a_ID == (U1)OXDC_SECURITY_ID01){
#ifdef ES_INSPECT_H           
            vd_g_ESInspectReqRx((U1)ES_INSPECT_REQ_RUN, (U1)ES_INSPECT_MD_ACT);
#endif
        }
    }

    return(u1_t_ret);
}
#if (OXDC_IDS_REQ_SUP == 1U)
/*===================================================================================================================================*/
/*  void   vd_g_TyDoCANSecurityCfgEventReg(const U1 u1_a_ID, const U1 u1_a_err)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANSecurityCfgEventReg(const U1 u1_a_ID, const U1 u1_a_err)
{
    u1_s_tydc_security_chk = (U1)OXDC_DTC_TR_ACT;
    vd_s_TyDoCANSecCfgEvCapt_U2B76(u1_a_ID, u1_a_err);
    if(u4_s_tydc_security_evt_cnt < (U4)U4_MAX){
        u4_s_tydc_security_evt_cnt++;
    }
#ifdef OXDOCAN_27_IN_VM1    
    vd_g_Nvmc_WriteU4((U2)NVMCID_U4_OXDC_TAECNT_001, u4_s_tydc_security_evt_cnt);
#endif
}
/*===================================================================================================================================*/
/*  static void    vd_s_TyDoCANSecCfgEvCapt_U2B76(const U1 u1_a_SECID, const U1 u1_a_NRC)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_TyDoCANSecCfgEvCapt_U2B76(const U1 u1_a_SECID, const U1 u1_a_NRC)
{
    U1                       u1_t_lv;

    if((u1_a_SECID >= (U1)OXDC_SECURITY_ID01) && (u1_a_SECID <= (U1)OXDC_SECURITY_ID63)){
        u1_t_lv = st_sp_TYDC_SECURITY_KEYCFG[u1_a_SECID - (U1)1U].u1_level;
    } 
    else{
        u1_t_lv = (U1)0xFFU;
    }

    u2_s_tydc_security_ctx = ((U2)u1_a_NRC << 8U) | (U2)u1_t_lv;
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANDtcTrchk_U2B76(const U2 u2_a_ELPSD)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANDtcTrchk_U2B76(const U2 u2_a_ELPSD)
{
    if(u1_s_tydc_security_chk == (U1)OXDC_DTC_TR_ACT){
#ifdef OXDOCAN_27_IN_VM1        
        (void)Dem_SetEventFailedWithSyncFreezeFrame((Dem_EventIdType)DemConf_DemEventParameter_DemEventDTC_U2B76);
        u2_s_tydc_security_ctx        = (U2)0x0000U;
        u1_s_tydc_security_chk        = (U1)OXDC_DTC_TR_INA;
#endif
    }

    return((U1)OXDC_DTC_TR_UNK);
}
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANAubIfTangFactor(uint8 * u1_ap_factor, Dem_MonitorDataType u4_a_mon)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
uint8   u1_g_oXDoCANAubIfTangFactor(uint8 * u1_ap_factor, Dem_MonitorDataType u4_a_mon)
{
    if(u1_ap_factor != vdp_PTR_NA){
        u1_ap_factor[0] = (U1)(u2_s_tydc_security_ctx >> 8U);
        u1_ap_factor[1] = (U1)((u2_s_tydc_security_ctx      ) & (U2)0x00FFU);
    }

    return((uint8)E_OK);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANRebyId_A9F6(U1 * u1_ap_ans, const U2 u2_a_ELPSD)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANRebyId_A9F6(U1 * u1_ap_ans, const U2 u2_a_ELPSD)
{
    u1_ap_ans[0U] = (U1)(u4_s_tydc_security_evt_cnt >> 24U);
    u1_ap_ans[1U] = (U1)(u4_s_tydc_security_evt_cnt >> 16U);
    u1_ap_ans[2U] = (U1)(u4_s_tydc_security_evt_cnt >>  8U);
    u1_ap_ans[3U] = (U1)u4_s_tydc_security_evt_cnt;

    return((U1)OXDC_SAL_PROC_FIN);
}
#endif      /* #if (OXCAN_IDS_REQ_SUP == 1U) */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    12/08/2023  II       New.                                                                                               */
/*  1.1.0    07/22/2025  MI       Fix for Intruction detection system.                                                               */
/*                                                                                                                                   */
/*  * II = Itsuki Ito, DENSO                                                                                                         */
/*  * MI = Masahiko Izumi, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
