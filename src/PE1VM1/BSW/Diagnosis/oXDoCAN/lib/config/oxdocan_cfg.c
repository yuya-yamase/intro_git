/* 1.0.8 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET/HCU based on AUBIST/DEM, DCM                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXDOCAN_CFG_C_MAJOR                      (1U)
#define OXDOCAN_CFG_C_MINOR                      (0U)
#define OXDOCAN_CFG_C_PATCH                      (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_aubif.h"
#include "oxdocan_cfg_private.h"
#include "oxdocan_xid_cfg_private.h"
#if(OXDC_SID23_USE == OXDC_USE)
#include "oxdocan_rebyadr_cfg_private.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "tydocan_xid_ma_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*#include "startup_fbl_entry_ctrl.h"*/
#if(OXDC_SID23_USE == OXDC_USE)
#include "mem_section.h"
#endif
#ifdef OXDC_IN_VM1
#include "rprg_if_request.h"
#endif


/* #include "nvmc_mgr.h"             nvmc_mgr.h is included in oxdocan_cfg_private.h              */
/* #include "oxcan.h"                oxcan.h is included in oxdocan_cfg_private.h                 */

#include "veh_opemd.h"
#ifdef OXDC_IN_VM1
#include "can_lpr.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Application Headers */
#include "Dcm_Dsp_SID28_Cfg.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXDOCAN_CFG_C_MAJOR != OXDOCAN_CFG_H_MAJOR) || \
     (OXDOCAN_CFG_C_MINOR != OXDOCAN_CFG_H_MINOR) || \
     (OXDOCAN_CFG_C_PATCH != OXDOCAN_CFG_H_PATCH))
#error "oxdocan_cfg.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if(OXDC_SID23_USE == OXDC_USE)
#define OXDC_REBYADR_MIN_NBYTE                   (3U)
#define OXDC_REBYADR_ALF                         (0U) /* addressAndLengthFormatIdentifier */
#define OXDC_REBYADR_ADR_4TH                     (1U)
#define OXDC_REBYADR_ADR_3RD                     (2U)
#define OXDC_REBYADR_ADR_2ND                     (3U)
#define OXDC_REBYADR_ADR_1ST                     (4U)
#define OXDC_REBYADR_NBY_4TH                     (5U)
#define OXDC_REBYADR_NBY_3RD                     (6U)
#define OXDC_REBYADR_NBY_2ND                     (7U)
#define OXDC_REBYADR_NBY_1ST                     (8U)

#define OXDC_REBYADR_ALF_44                      (0x44U)

#define OXDC_REBYADR_LSB_4TH                     (24U)
#define OXDC_REBYADR_LSB_3RD                     (16U)
#define OXDC_REBYADR_LSB_2ND                     (8U)

#define OXDC_REBYADR_RB_MAX                      (0xFFFFFFFFU)
#endif

#define OXDC_SUPPORT_SES_NUM                     (3U)

#ifdef OXDC_FUNC_RPG_RESET
#define OXDC_MR_RA_WORD_RESF                     (0xfff80760U)
#define OXDC_MR_RA_WORD_RESFR                    (0xfff80860U)
#define OXDC_MR_RA_WORD_RESFC                    (0xfff80768U)
#define OXDC_MR_RA_WORD_RESFCR                   (0xfff80868U)
#define OXDC_MR_REA_INIT                         (0x0000c70fU)
#endif

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
#if(OXDC_SID23_USE == OXDC_USE)
static U1      u1_s_oXDoCANCfgRbaSecuritychk(const U1 u1_a_MEM);
#endif

#ifdef OXDC_FUNC_RPG_RESET
static void    vd_s_oXdcPrepSwReset(void);
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U2                u2_g_OXDC_RPG_TIM_TO_RUN = (U2)1000U / (U2)OXDC_MAIN_TICK;
const U2                u2_g_OXDC_RBID_1CYC_READ = (U2)OXDC_REBYID_NUMOFDID_MAX;	/* Max is OXDC_REBYID_NUMOFDID_MAX */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if(OXDC_SID23_USE == OXDC_USE)
const ST_OXDC_RBA_MEM   st_gp_OXDC_RBA_MEM_CFG[] = {                           /*  oxdocan_rebyadr_cfg_private.h  */
/*   u4_addr_begin                   u4_addr_end                        fp_u1_SEC_CHK       u2_rb_max */
    {(U4)MEM_SEC_ADDR_STA_LOCAL_RBA, (U4)MEM_SEC_ADDR_END_LOCAL_RBA,    vdp_PTR_NA,         (U2)128U},
    {(U4)MEM_SEC_ADDR_STA_BACK_USD,  (U4)MEM_SEC_ADDR_END_BACK_USD,     vdp_PTR_NA,         (U2)64U }
};
const U1                u1_g_OXDC_RBA_MEM_NUM_CFG = (U1)(sizeof(st_gp_OXDC_RBA_MEM_CFG) / sizeof(ST_OXDC_RBA_MEM));
                                                                               /*  oxdocan_rebyadr_cfg_private.h  */
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANCfgBonPreInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANCfgBonPreInit(void)
{
#if(OXDC_SID86_USE == OXDC_USE)
    vd_g_oXDoCANRoePreInit((U1)TRUE);
#endif
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANCfgRstPreInit(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANCfgRstPreInit(void)
{
#if(OXDC_SID86_USE == OXDC_USE)
    vd_g_oXDoCANRoePreInit((U1)FALSE);
#endif
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANCfgWkupPreInit(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANCfgWkupPreInit(void)
{
#if(OXDC_SID86_USE == OXDC_USE)
    vd_g_oXDoCANRoePreInit((U1)FALSE);
#endif
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANCfgBonInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANCfgBonInit(void)
{
#ifdef TYDOCAN_DTC_MM_H
    vd_g_TyDoCANDtcMMInit((U1)TRUE);
#endif /* #ifdef TYDOCAN_DTC_MM_H */

#ifdef TYDOCAN_DTC_NMWK_H
    vd_g_TyDoCANDtcNmwkInit((U1)TRUE);
#endif /* #ifdef TYDOCAN_DTC_NMWK_H */

#ifdef TYDOCAN_DTC_ECUSLP_H
    vd_g_TyDoCANDtcEcuSlpBonInit();
#endif /* #ifdef TYDOCAN_DTC_ECUSLP_H */

#ifdef TYDOCAN_DTC_NMGBL_H
    vd_g_TyDoCANDtcNmGblInit((U1)TRUE);
#endif /* #ifdef TYDOCAN_DTC_NMGBL_H */

#ifdef TYDOCAN_DID_SSR_H
    vd_g_oXDoCANDidSsrInit((U1)TRUE);
#endif /* #ifdef TYDOCAN_DID_SSR_H */

#ifdef TYDOCAN_DTC_MA_CFG_H
    vd_g_TyDoCANDtcMaInit();
#endif /* #ifdef TYDOCAN_DTC_MA_CFG_H */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANCfgRstInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANCfgRstInit(void)
{
#ifdef TYDOCAN_DTC_MM_H
    vd_g_TyDoCANDtcMMInit((U1)FALSE);
#endif /* #ifdef TYDOCAN_DTC_MM_H */

#ifdef TYDOCAN_DTC_NMWK_H
    vd_g_TyDoCANDtcNmwkInit((U1)FALSE);
#endif /* #ifdef TYDOCAN_DTC_NMWK_H */

#ifdef TYDOCAN_DTC_ECUSLP_H
    vd_g_TyDoCANDtcEcuSlpRstInit();
#endif /* #ifdef TYDOCAN_DTC_ECUSLP_H */

#ifdef TYDOCAN_DTC_NMGBL_H
    vd_g_TyDoCANDtcNmGblInit((U1)TRUE);
#endif /* #ifdef TYDOCAN_DTC_NMGBL_H */

#ifdef TYDOCAN_DID_SSR_H
    vd_g_oXDoCANDidSsrInit((U1)FALSE);
#endif /* #ifdef TYDOCAN_DID_SSR_H */

#ifdef TYDOCAN_DTC_MA_CFG_H
    vd_g_TyDoCANDtcMaRstInit();
#endif /* #ifdef TYDOCAN_DTC_MA_CFG_H */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANCfgWkupInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANCfgWkupInit(void)
{
#ifdef TYDOCAN_DTC_MM_H
    vd_g_TyDoCANDtcMMInit((U1)FALSE);
#endif /* #ifdef TYDOCAN_DTC_MM_H */

#ifdef TYDOCAN_DTC_NMWK_H
    vd_g_TyDoCANDtcNmwkInit((U1)FALSE);
#endif /* #ifdef TYDOCAN_DTC_NMWK_H */

#ifdef TYDOCAN_DTC_ECUSLP_H
    vd_g_TyDoCANDtcEcuSlpWkupInit();
#endif /* #ifdef TYDOCAN_DTC_ECUSLP_H */

#ifdef TYDOCAN_DTC_NMGBL_H
    vd_g_TyDoCANDtcNmGblInit((U1)FALSE);
#endif /* #ifdef TYDOCAN_DTC_NMGBL_H */

#ifdef TYDOCAN_DID_SSR_H
    vd_g_oXDoCANDidSsrInit((U1)FALSE);
#endif /* #ifdef TYDOCAN_DID_SSR_H */

#ifdef TYDOCAN_DTC_MA_CFG_H
    vd_g_TyDoCANDtcMaWkupInit();
#endif /* #ifdef TYDOCAN_DTC_MA_CFG_H */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANCfgServiceInit(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANCfgServiceInit(void)
{
    vd_g_oXDoCANRebyIdInit();
#if(OXDC_SID23_USE == OXDC_USE)
    vd_g_oXDoCANRebyAdrInit();
#endif
#if(OXDC_SID2F_USE == OXDC_USE)
    vd_g_oXDoCANIocInit();
#endif
    vd_g_oXDoCANRoutInit();
#if(OXDC_SIDBA_USE == OXDC_USE)
    vd_g_TyDoCANEsiInit();
#endif

#ifdef TYDOCAN_XID_MA_CFG_H
    vd_g_TyDoCANXidMaInit();
#endif /* #ifdef TYDOCAN_XID_MA_CFG_H */

#if(OXDC_SID86_USE == OXDC_USE)
    vd_g_oXDoCANRoeInit();
#endif

}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANCfgMainStart(const ST_OXDC_REQ * st_ap_REQ, const U2 u2_a_TSLOT)                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANCfgMainStart(const ST_OXDC_REQ * st_ap_REQ, const U2 u2_a_TSLOT)
{
    U4                     u4_t_lpcnt;
    U1                     u1_t_ch;
#ifdef TYDOCAN_DTC_MA_CFG_H
    U1                     u1_t_prev;
    U1                     u1_t_next;

    u1_t_prev = st_ap_REQ->u1_eom_bfr & (U1)OXDC_EOM_IGN_ON;
    u1_t_next = st_ap_REQ->u1_eom_aft & (U1)OXDC_EOM_IGN_ON;
 
    if((u1_t_prev == (U1)OXDC_EOM_IGN_ON) && (u1_t_next != (U1)OXDC_EOM_IGN_ON)){
        vd_g_TyDoCANDtcMaResume();
    }
#endif /* #ifdef TYDOCAN_DTC_MA_CFG_H */

    if(st_ap_REQ->u1_ses_aft == (U1)OXDC_SESSION_DEF){
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)DCM_P_COMCTRL_ALLCH_N; u4_t_lpcnt++){
            u1_t_ch = Dcm_P_SID28_stComCtrl_Tbl.ptAllCh[u4_t_lpcnt].u1ComMChannel;
            (void)BswM_CS_ResumeTxPdu(u1_t_ch);
        }
#ifdef OXDC_IN_VM1        
        vd_g_CANLpRDs28PhyTxEN((U1)TRUE);
#endif
    }

#ifdef TYDOCAN_DTC_MM_H
    vd_g_TyDoCANDtcMMMainTask(st_ap_REQ->u1_eom_aft, u2_a_TSLOT);
#endif /* #ifdef TYDOCAN_DTC_MM_H */

#ifdef TYDOCAN_DTC_NMWK_H
    vd_g_TyDoCANDtcNmwkMainTask();
#endif /* #ifdef TYDOCAN_DTC_NMWK_H */

#ifdef TYDOCAN_DTC_ECUSLP_H
    vd_g_TyDoCANDtcEcuSlpMainTask();
#endif /* #ifdef TYDOCAN_DTC_ECUSLP_H */

#ifdef TYDOCAN_DTC_NMGBL_H
    vd_g_TyDoCANDtcNmGblMainTask();
#endif /* #ifdef TYDOCAN_DTC_NMGBL_H */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANCfgServiceMain(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, const U2 u2_a_TSLOT)                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANCfgServiceMain(const ST_OXDC_REQ * st_ap_REQ, ST_OXDC_ANS * st_ap_ans, const U2 u2_a_TSLOT)
{
    U4                     u4_t_ev_dtct;
#ifdef TYDOCAN_DID_SSR_H
    U1                     u1_t_ev_nvm;
#endif /* #ifdef TYDOCAN_DID_SSR_H */

    vd_g_TyDoCANXidMaMainTask(st_ap_REQ);

    u4_t_ev_dtct = u4_g_oXDoCANDtcMainTask(st_ap_REQ, u2_a_TSLOT);
    if(u4_t_ev_dtct != (U4)0U){
        vd_g_oXDoCANCfgReqNvmcToRun();
    }

#ifdef TYDOCAN_DID_SSR_H
    u1_t_ev_nvm = u1_g_oXDoCANDidSsrMainTask(u2_a_TSLOT, st_ap_REQ->u1_eom_aft);
    if(u1_t_ev_nvm != (U1)0U){
        vd_g_oXDoCANCfgReqNvmcToRun();
    }
#endif /* #ifdef TYDOCAN_DID_SSR_H */

    /* ---------------------------------------------------------------------------------------------------- */
    vd_g_oXDoCANRebyIdMainTask(st_ap_REQ, st_ap_ans);  /* SID 0x22 */
#if(OXDC_SID23_USE == OXDC_USE)
    vd_g_oXDoCANRebyAdrMainTask(st_ap_REQ, st_ap_ans); /* SID 0x23 */
#endif
    vd_g_oXDoCANWrbyIdMainTask(st_ap_REQ, st_ap_ans);  /* SID 0x2E */
#if(OXDC_SID2F_USE == OXDC_USE)
    vd_g_oXDoCANIocMainTask(st_ap_REQ, st_ap_ans);     /* SID 0x2F */
#endif
    vd_g_oXDoCANRoutMainTask(st_ap_REQ, st_ap_ans);    /* SID 0x31 */
#if(OXDC_SIDBA_USE == OXDC_USE)
    vd_g_TyDoCANEsiMainTask(st_ap_REQ, st_ap_ans);     /* SID 0xBA */
#endif
#if(OXDC_SID86_USE == OXDC_USE)
    vd_g_oXDoCANRoeMainTask(st_ap_REQ->u1_eom_aft);    /* SID 0x86 */
#endif
    /* ---------------------------------------------------------------------------------------------------- */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANCfgMainFinish(const U2 u2_a_TSLOT)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANCfgMainFinish(const U2 u2_a_TSLOT)
{
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANCfgSesChange(const uint8 u1_a_OLD, const uint8 u1_a_NEW)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANCfgSesChange(const uint8 u1_a_OLD, const uint8 u1_a_NEW)
{
    vd_g_oXDoCANRoutStop(u1_a_NEW);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANCfgComTREOvrrd(const U1 u1_a_COM_CH, const U1 u1_a_MODE)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANCfgComTREOvrrd(const U1 u1_a_COM_CH, const U1 u1_a_MODE)
{
    /* ---------------------------------------------------------------------------------------------------- */
    /* Attention                                                                                            */
    /* ---------------------------------------------------------------------------------------------------- */
    /* Caller : ./Dcm/Dsp/usr/Dcm_Dsp_SID28_Connector.c                                                     */
    /*                                                                                                      */
    /* FUNC( void, DCM_CODE ) Dcm_Dsp_SID28_Cnct_BswMComMode                                                */
    /* (                                                                                                    */
    /*     const uint8 u1ComMChId,                                                                          */
    /*     const Dcm_CommunicationModeType u1ComMode                                                        */
    /* )                                                                                                    */
    /* ---------------------------------------------------------------------------------------------------- */
    /* inc/Dcm_Types.h  / Dcm_CommunicationModeType                                                         */
    /* #define DCM_ENABLE_RX_TX_NORM               (0x00U)   support                                        */
    /* #define DCM_ENABLE_RX_DISABLE_TX_NORM       (0x01U)   not support                                    */
    /* #define DCM_DISABLE_RX_ENABLE_TX_NORM       (0x02U)   not support                                    */
    /* #define DCM_DISABLE_RX_TX_NORMAL            (0x03U)   support                                        */
    /* #define DCM_ENABLE_RX_TX_NM                 (0x04U)   not support                                    */
    /* #define DCM_ENABLE_RX_DISABLE_TX_NM         (0x05U)   not support                                    */
    /* #define DCM_DISABLE_RX_ENABLE_TX_NM         (0x06U)   not support                                    */
    /* #define DCM_DISABLE_RX_TX_NM                (0x07U)   not support                                    */
    /* #define DCM_ENABLE_RX_TX_NORM_NM            (0x08U)   not support                                    */
    /* #define DCM_ENABLE_RX_DISABLE_TX_NORM_NM    (0x09U)   not support                                    */
    /* #define DCM_DISABLE_RX_ENABLE_TX_NORM_NM    (0x0AU)   not support                                    */
    /* #define DCM_DISABLE_RX_TX_NORM_NM           (0x0BU)   not support                                    */
    /* ---------------------------------------------------------------------------------------------------- */

    if((u1_a_MODE == (U1)DCM_ENABLE_RX_TX_NORM) ||
       (u1_a_MODE == (U1)DCM_ENABLE_RX_TX_NORM_NM)){
        (void)BswM_CS_ResumeTxPdu(u1_a_COM_CH);
#ifdef OXDC_IN_VM1        
        vd_g_CANLpRDs28PhyTxEN((U1)TRUE);
#endif
    }
    else if(u1_a_MODE == (U1)DCM_DISABLE_RX_TX_NORMAL){
        (void)BswM_CS_StopTxPdu(u1_a_COM_CH);
#ifdef OXDC_IN_VM1        
        vd_g_CANLpRDs28PhyTxEN((U1)FALSE);
#endif
    }
    else{
        /* Do Nothing */
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANCfgRpgCheck(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE(Check OK)/FALSE(Check NG)                                                                                   */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANCfgRpgCheck(void)
{
    U1                      u1_t_ret;

    u1_t_ret = (U1)TRUE;

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANCfgRpgPrepToRun(const U2 u2_a_ELPSD)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANCfgRpgPrepToRun(const U2 u2_a_ELPSD)
{
}
#ifdef OXDC_FUNC_RPG_RESET
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANCfgRpgSwReset(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANCfgRpgSwReset(void)
{
/* reset for repro-soft start */
    vd_s_oXdcPrepSwReset();
#ifdef OXDC_IN_VM1    
    vd_g_RprgIfRequestReprog();
#endif    
}
#endif
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANCfgRpgCancel(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANCfgRpgCancel(void)
{
#ifdef OXDC_IN_VM1    
    Ecu_Intg_performSTReset(ECU_INTG_ST_RESET_SOFT,ECU_INTG_ST_RESET_BY_FACTORY);
#endif
}
/*===================================================================================================================================*/
/*  U2      u2_g_oXDoCANCfgKmph(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_oXDoCANCfgKmph(void)
{
    return((U2)0U);
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANCfgEomchk(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANCfgEomchk(void)
{
#if (OXDC_EOM_IGN_ON != TRUE)
#error "oxdocan_cfg.c : OXDC_EOM_IGN_ON shall be equal to TRUE."
#endif

#ifdef ES_INSPECT_H

#if ((ES_INSPECT_MDBF_NUO_DI != (OXDC_EOM_NUO_DI >> 2)) || \
     (ES_INSPECT_MDBF_SI_ACT != (OXDC_EOM_SI_ACT >> 2)))
#error "oxdocan_cfg.c : OXDC_EOM_NUO_DI and/or OXDC_EOM_SI_ACT shall be compabile with ES_INSPECT_MDBF_XXX."
#endif

    U1                      u1_t_eom;

    u1_t_eom  = (u1_g_ESInspectMdBfield() << 2U) | (U1)OXDC_EOM_RPG_EN;
    u1_t_eom |= (u1_g_VehopemdIgnOn() & (U1)OXDC_EOM_IGN_ON);

    return(u1_t_eom);
#else  /* #ifdef ES_INSPECT_H */
    return(u1_g_VehopemdIgnOn() | (U1)OXDC_EOM_RPG_EN);
#endif /* #ifdef ES_INSPECT_H */
}
#ifdef OXDC_FUNC_DTC_EXTEND
/*===================================================================================================================================*/
/*  uint8      u1_g_oXDoCANGetDtcRequest(const uint8 u1_a_SUB, const uint8 u1_a_PRM)                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
uint8      u1_g_oXDoCANGetDtcRequest(const uint8 u1_a_SUB, const uint8 u1_a_PRM)
{

    return((U1)OXDC_SAL_PROC_FIN);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXDoCANDTCClrComplete(const uint8 u1_a_KIND)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXDoCANDTCClrComplete(const uint8 u1_a_KIND)
{
}
#endif
#if(OXDC_SID28_NR_22_USE == OXDC_USE)
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANComCtrlChk(uint8 * u1_ap_err)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         E_OK(Check OK)/E_NOT_OK(Check NG)                                                                                */
/*===================================================================================================================================*/
uint8   u1_g_oXDoCANComCtrlChk(uint8 * u1_ap_err)
{
    static const U2         u2_s_TYDC_RPG_KMPH_MIN = (U2)500U;                     /* 5.00 km/h */

    U1                      u1_t_ret;
    U2                      u2_t_sp1;

    u1_t_ret = (U1)E_OK;
    u2_t_sp1 = u2_g_oXDoCANCfgKmph();

    if(u2_t_sp1 != (U2)OXDC_KMPH_UNK){
        if(u2_t_sp1 > u2_s_TYDC_RPG_KMPH_MIN){
            u1_t_ret   = (U1)E_NOT_OK;
            *u1_ap_err = (U1)DCM_E_VEHICLESPEEDTOOHIGH;
        }
    }

    return(u1_t_ret);
}
#endif
#if(OXDC_SID85_NR_22_USE == OXDC_USE)
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANCtrlDTCChk(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         E_OK(Check OK)/E_NOT_OK(Check NG)                                                                                */
/*===================================================================================================================================*/
uint8   u1_g_oXDoCANCtrlDTCChk(void)
{
    return((U1)E_OK);
}
#endif
#if(OXDC_SID14_NR_22_USE == OXDC_USE)
/*===================================================================================================================================*/
/*  uint8   u1_g_oXDoCANClearDTCChk(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         E_OK(Check OK)/E_NOT_OK(Check NG)                                                                                */
/*===================================================================================================================================*/
uint8   u1_g_oXDoCANClearDTCChk(void)
{
    U1                      u1_t_ret;

    u1_t_ret = (U1)E_OK;

    return(u1_t_ret);
}
#endif
#if(OXDC_SID27_NR_22_USE == OXDC_USE)
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANSecurityAccessChk(const U1 u1_a_KIND, const U1 u1_a_ID)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         E_OK(Check OK)/E_NOT_OK(Check NG)                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANSecurityAccessChk(const U1 u1_a_KIND, const U1 u1_a_ID)
{
    U1                      u1_t_ret;

    u1_t_ret = (U1)E_OK;

    return(u1_t_ret);
}
#endif
#if(OXDC_SID22_NR_22_USE == OXDC_USE)
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANCReadByIdChk(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         E_OK(Check OK)/E_NOT_OK(Check NG)                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANCReadByIdChk(void)
{
    U1                      u1_t_ret;

    u1_t_ret = (U1)E_OK;

    return(u1_t_ret);
}
#endif
#if(OXDC_SID2E_NR_22_USE == OXDC_USE)
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANCWriteByIdChk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         E_OK(Check OK)/E_NOT_OK(Check NG)                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANCWriteByIdChk(void)
{
    U1                      u1_t_ret;

    u1_t_ret = (U1)E_OK;

    return(u1_t_ret);
}
#endif
#if(OXDC_SID31_NR_22_USE == OXDC_USE)
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANCRoutineChk(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         E_OK(Check OK)/E_NOT_OK(Check NG)                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANCRoutineChk(void)
{
    U1                      u1_t_ret;

    u1_t_ret = (U1)E_OK;

    return(u1_t_ret);
}
#endif
#if(OXDC_SID2F_NR_22_USE == OXDC_USE)
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANIocChk(const ST_OXDC_REQ * st_ap_REQ)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANIocConditionChk(const ST_OXDC_REQ * st_ap_REQ)
{
    U1                      u1_t_ret;

    u1_t_ret = (U1)OXDC_SAL_PROC_RUN;

    return(u1_t_ret);
}
#endif
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANCfgDidSessionBitChk(const U1 u1_a_CUR_SES, const U2 u2_a_CONF_SES)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANCfgDidSessionBitChk(const U1 u1_a_CUR_SES, const U2 u2_a_CONF_SES)
{
    static const U1          u1_sp_OXDC_SES_TBL[OXDC_SUPPORT_SES_NUM] = {
        (U1)DCM_DEFAULT_SESSION,
        (U1)DCM_RkDcmDspSessionRow_Reprog,
        (U1)DCM_EXTENDED_DIAGNOSTIC_SESSION,
    };

    U1                       u1_t_ret;
    U1                       u1_t_cnt;
    U2                       u2_t_cur_ses;

    u1_t_ret = (U1)E_NOT_OK;
    u2_t_cur_ses = (U2)0U;

    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)OXDC_SUPPORT_SES_NUM; u1_t_cnt++){
        if(u1_sp_OXDC_SES_TBL[u1_t_cnt] == u1_a_CUR_SES){
            u2_t_cur_ses = (U2)((U2)0x0001U << u1_t_cnt);
            break;
        }
    }

    if((u2_t_cur_ses != (U2)0U) &&
       ((u2_a_CONF_SES & u2_t_cur_ses) == u2_t_cur_ses)){
        u1_t_ret = (U1)E_OK;
    }

    return(u1_t_ret);
}
#if(OXDC_SID2F_USE == OXDC_USE)
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANIocReqLenChk(const ST_OXDC_REQ * st_ap_REQ)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         OXDC_SAL_PROC_RUN(Check OK)/OXDC_SAL_PROC_NR_13(Check NG)                                                        */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANIocReqLenChk(const ST_OXDC_REQ * st_ap_REQ)
{
    U4                       u4_t_req_nbyte;
    U1                       u1_t_prm;
    U1                       u1_t_proc;

    /* st_gp_TYDC_DATA_XID_ML[].u2_req_nbyte = length of ControlState */
    u1_t_prm      = st_ap_REQ->u1p_RX[OXDC_IOC_PRM];
    if(u1_t_prm == (U1)OXDC_IOC_PRM_CTE){
        u4_t_req_nbyte = (U4)OXDC_IOC_CSM;
    }
    else if(u1_t_prm == (U1)OXDC_IOC_PRM_STA){
        u4_t_req_nbyte = (U4)st_gp_OXDC_DATA_XID_ML[u2_g_oxdc_ioc_xid].u2_req_nbyte + (U4)OXDC_IOC_CSM;
    }
    else{
        u4_t_req_nbyte = (U4)0U;
    }

    if(st_ap_REQ->u4_nbyte == u4_t_req_nbyte){
        u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
    }
    else{
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_13;
    }

    return(u1_t_proc);
}
#endif
#if(OXDC_SID23_USE == OXDC_USE)
/*===================================================================================================================================*/
/*  U1      u1_g_oXDoCANCfgRbaReqchk(const ST_OXDC_REQ * st_ap_REQ, const ST_OXDC_ANS * st_ap_ANS)                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:                                                                                                                       */
/*  Return:                                                                                                                          */
/*===================================================================================================================================*/
U1      u1_g_oXDoCANCfgRbaReqchk(const ST_OXDC_REQ * st_ap_REQ, const ST_OXDC_ANS * st_ap_ANS)
{
    U4                       u4_t_src_begin;
    U4                       u4_t_src_end;
    U4                       u4_t_src_nbyte;
    U4                       u4_t_dst_begin;
    U4                       u4_t_dst_end;
    U4                       u4_t_mem_begin;
    U4                       u4_t_mem_end;

    U1                       u1_t_mem;
    U1                       u1_t_proc;

    if((st_ap_REQ->u1p_RX   == vdp_PTR_NA                ) ||
       (st_ap_REQ->u4_nbyte <  (U4)OXDC_REBYADR_MIN_NBYTE)){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_13;
    }
    else if(st_ap_REQ->u1p_RX[OXDC_REBYADR_ALF] != (U1)OXDC_REBYADR_ALF_44){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
    }
    else if(st_ap_REQ->u4_nbyte != (U4)OXDC_REBYADR_REQ_NBYTE){
        u1_t_proc = (U1)OXDC_SAL_PROC_NR_13;
    }
    else{

        u4_t_src_begin  = (U4)st_ap_REQ->u1p_RX[OXDC_REBYADR_ADR_4TH] << OXDC_REBYADR_LSB_4TH;
        u4_t_src_begin |= (U4)st_ap_REQ->u1p_RX[OXDC_REBYADR_ADR_3RD] << OXDC_REBYADR_LSB_3RD;
        u4_t_src_begin |= (U4)st_ap_REQ->u1p_RX[OXDC_REBYADR_ADR_2ND] << OXDC_REBYADR_LSB_2ND;
        u4_t_src_begin |= (U4)st_ap_REQ->u1p_RX[OXDC_REBYADR_ADR_1ST];
        u4_t_src_nbyte  = (U4)st_ap_REQ->u1p_RX[OXDC_REBYADR_NBY_4TH] << OXDC_REBYADR_LSB_4TH;
        u4_t_src_nbyte |= (U4)st_ap_REQ->u1p_RX[OXDC_REBYADR_NBY_3RD] << OXDC_REBYADR_LSB_3RD;
        u4_t_src_nbyte |= (U4)st_ap_REQ->u1p_RX[OXDC_REBYADR_NBY_2ND] << OXDC_REBYADR_LSB_2ND;
        u4_t_src_nbyte |= (U4)st_ap_REQ->u1p_RX[OXDC_REBYADR_NBY_1ST];

        u1_t_proc = (U1)OXDC_SAL_PROC_NR_31;
        for(u1_t_mem = (U1)0U; u1_t_mem < u1_g_OXDC_RBA_MEM_NUM_CFG; u1_t_mem++){
            u4_t_mem_begin  = st_gp_OXDC_RBA_MEM_CFG[u1_t_mem].u4_addr_begin;
            u4_t_mem_end    = st_gp_OXDC_RBA_MEM_CFG[u1_t_mem].u4_addr_end;
            u4_t_src_end    = u4_t_src_begin + u4_t_src_nbyte;

            if((u4_t_mem_begin <  u4_t_mem_end  ) &&
               (u4_t_src_begin >= u4_t_mem_begin) &&
               (u4_t_src_begin <  u4_t_mem_end  ) &&
               (u4_t_src_end   <= u4_t_mem_end  ) &&
               (u4_t_src_end   >= u4_t_src_begin) &&
               (u4_t_src_nbyte >  (U4)0U        )){

                u4_t_dst_begin = (U4)st_ap_ANS->u1p_tx;
                u4_t_dst_end   = u4_t_dst_begin + st_ap_ANS->u4_nbyte;
                
                u1_t_proc = u1_s_oXDoCANCfgRbaSecuritychk(u1_t_mem);
                if(u1_t_proc != (U1)OXDC_SAL_PROC_RUN){
                    break;
                }

                if((u4_t_src_begin >= u4_t_dst_end) || (u4_t_dst_begin >= u4_t_src_end)){
                    if(st_ap_ANS->u4_nbyte >= u4_t_src_nbyte){
                        vd_g_oXDoCANRebyAdrStartRamSet(u1_t_mem, u4_t_src_begin, u4_t_src_nbyte);
                    }
                    else{
                        u1_t_proc = (U1)OXDC_SAL_PROC_NR_14;
                    }
                }
                else{
                    u1_t_proc = (U1)OXDC_SAL_PROC_NR_22;
                }
                break;
            }
        }
    }

    return(u1_t_proc);
}
/*===================================================================================================================================*/
/*  static U1      u1_s_oXDoCANCfgRbaSecuritychk(const U1 u1_a_MEM)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_oXDoCANCfgRbaSecuritychk(const U1 u1_a_MEM)
{
    U1                       u1_t_proc;
    U1                       u1_t_sec;

    u1_t_proc = (U1)OXDC_SAL_PROC_NR_33;
    if(u1_a_MEM < u1_g_OXDC_RBA_MEM_NUM_CFG){
        if(st_gp_OXDC_RBA_MEM_CFG[u1_a_MEM].fp_u1_SEC_CHK == vdp_PTR_NA){
            u1_t_proc = (U1)OXDC_SAL_PROC_RUN;
        }
        else{
            u1_t_sec = DCM_SEC_LEV_LOCKED;
            (void)Dcm_GetSecurityLevel(&u1_t_sec);
            u1_t_proc = (*st_gp_OXDC_RBA_MEM_CFG[u1_a_MEM].fp_u1_SEC_CHK)(u1_t_sec);
        }
    }

    return(u1_t_proc);
}
#endif
#ifdef OXDC_FUNC_RPG_RESET
/*===================================================================================================================================*/
/*  static void    vd_s_oXdcPrepSwReset(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXdcPrepSwReset(void)
{
}
#endif
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     3/16/2022  HU       ty19epf_ren_d1x_v220_r009 -> ox25epf_ren_d1x_v100_r000.                                            */
/*  1.0.1    12/13/2022  TM       oxdocan v1.0.0 -> v1.0.1.                                                                          */
/*  1.0.2     7/ 6/2023  ST       Update for OEM standardization.                                                                    */
/*  1.0.3     8/24/2023  TI       Update for OEM standardization & Maximum security level support.                                   */
/*  1.0.4    11/23/2023  ToI      oxdocan v1.0.3 -> v1.0.4.                                                                          */
/*  1.0.5     2/23/2024  ToI      oxdocan v1.0.4 -> v1.0.5.                                                                          */
/*  1.0.6     3/11/2024  ToI      oxdocan v1.0.5 -> v1.0.6.                                                                          */
/*  1.0.7     9/ 6/2024  ToI      oxdocan v1.0.6 -> v1.0.7.                                                                          */
/*  1.0.8     9/25/2024  II       Bug Fixed. Reprog Software Jump function.                                                          */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * HU = Hayato Usui, DENSO                                                                                                        */
/*  * TM = Takanori Maruyama, DENSO                                                                                                  */
/*  * ST = Shohei Takada, DENSO                                                                                                      */
/*  * TI = Takaehisa Inoue, DENSO                                                                                                    */
/*  * ToI= Tomoko Inuzuka, DENSO                                                                                                     */
/*  * II = Itsuki Ito, DENSO                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/
