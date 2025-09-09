/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 *【ファイル名】    22SS_Callout.c
 *【モジュール名】  22SS Callout
 *【機能】
 *【備考】
 ****************************************************************************/
/*----------------------------------------------------------------------------
 *		ヘッダインクルード
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS.h>
#include "OS.h"

#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_Memmap.h>
#include <22SS_Callout.h>

#include "veh_opemd.h"
#include "oxcan.h"
#include "ivdsh.h"

/* Memory               */
#include "rim_ctl.h"
#include "nvmc_mgr.h"

#include "fpcall_vd_fvd.h"
#if 0   /* BEV Rebase provisionally */
/* Complex Device Driver */
#include "nwcm.h"
#include "drec_tx.h"
#include "dio_if.h"
#include "sound_cri_mgr.h"
#include "gateway_mm.h"

/* Application           */
#include "dimmer.h"
#include "illumi.h"
#include "thblnkr.h"
#include "vehspd_kmph.h"
#include "vptran_sel.h"
#include "ptsctmp_cel.h"
#include "alert.h"
#include "sbltwrn.h"
#include "engspd_rpm.h"
#include "engspd_det_rpm.h"
#include "odo_km.h"
#include "tripsnsr.h"
#include "tripcom.h"
#include "ambtmp.h"
#include "mulmed_color.h"
#include "mulmed_mulfr.h"
#include "rcmmui.h"
#include "gauge.h"
#include "telltale.h"
#include "wchime.h"
#include "sbltsync.h"
#include "locale.h"
#include "vardef.h"
#include "hud_ca.h"
#include "mcst.h"
#include "vds_ci.h"
#include "hmiproxy.h"
#include "battpow.h"
#include "drvind_pwr_pct.h"
#include "drvind_eco.h"
#include "drvind_hv_pct.h"
#include "oilmil.h"
#include "gateway_cxpi.h"
#include "hdimmgr.h"
#include "himgadj.h"
#include "mmlang.h"
#include "vmmunit.h"
#include "fspomgr.h"
#include "mmappctrl.h"
#include "attmp_cel.h"
#include "evschg.h"
#include "batcare.h"
#endif   /* BEV Rebase provisionally */
#include "xspi_met.h"
#if 0   /* BEV Rebase provisionally */
#include "datesi_met.h"
#endif   /* BEV Rebase provisionally */

/*----------------------------------------------------------------------------
 *		置換シンボル定義
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		変数宣言
 *--------------------------------------------------------------------------*/

#include <Ecu_Memmap_SdaDisableE_env.h>

/*----------------------------------------------------------------------------
 *      プロトタイプ宣言
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		プログラム
 *--------------------------------------------------------------------------*/

/*===================================================================================================================================*/
/*  void    vd_g_22SSCallout_StaBonInit(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_22SSCallout_StaBonInit(void)
{
#if 0   /* BEV Rebase provisionally */
    static const FP_VD_FVD             fp_sp_vd_ECU_M_CFG_BON_INIT[] = {
        &vd_g_EvschgBonInit,
        &vd_g_VardefBonInit,
        &vd_g_HudCaInit,
        &vd_g_McstBonInit,
        &vd_g_LocaleBonInit,
        &vd_g_SoundCriMgrInitialize,
        &vd_g_DrectxBonInit,
        &vd_g_DioIfInit,
        &vd_g_DimInit,
        &vd_g_IllumiBonInit,
        &vd_g_PtsctmpInit,
        &vd_g_AlertInit,
        &vd_g_SbltwrnInit,
        &vd_g_TelltaleInit,
        &vd_g_ThblnkrBonInit,
        &vd_g_VehspdInit,
        &vd_g_VptranInit,
        &vd_g_wChimeInit,
        &vd_g_GaugeBonInit,
        &vd_g_EngspdBonInit,
        &vd_g_EngspdDetInit,
        &vd_g_OdoBonInit,
        &vd_g_TripsnsrInit,
        &vd_g_TripcomBonInit,
        &vd_g_AmbtmpBonInit,
        &vd_g_VdsCIInit,
        &vd_g_MulmedColorInit,
        &vd_g_MulmedMulfrInit,
        &vd_g_RcmmUIInit,
        &vd_g_BattpowInit,
        &vd_g_DrvIndPwrInit,
        &vd_g_DrvIndEcoInit,
        &vd_g_DrvIndHvInit,
        &vd_g_SbltsyncInit,
        &vd_g_OilmilInit,
        &vd_g_HmiProxyBonInit,
        &vd_g_GatewayCxpiInit,
        &vd_g_GatewaymmInit,
        &vd_g_HdimmgrBonInit,
        &vd_g_HudImgAdjInit,
        &vd_g_MmLangBonInit,
        &vd_g_VardefMmUnitBonInit,
        &vd_g_FspomgrBonInit,
        &vd_g_AttmpInit,
        &vd_g_MMAppCtrlInitial,
        &vd_g_BatcareBonInit,
        &vd_g_DateSIMETInit
    };
#endif   /* BEV Rebase provisionally */

    U1    u1_t_rslt;

    /*****************************************************/
    /* Rim, Nvmc Init Function should be called at first */
    /*****************************************************/
    vd_g_Rim_BonInit();

    vd_g_Nvmc_BonInit();
    do{
        u1_t_rslt = u1_g_Nvmc_BonRead();
    }while(u1_t_rslt != (U1)FALSE);

    vd_g_oXCANRstInit();
    vd_g_VehopemdRstInit();
    vd_g_iVDshInit();

    /* vv User Hook start vv */
#if 0   /* BEV Rebase provisionally */
    vd_g_NWCMBonInit();
    vd_g_Fpcall_vd_Fvd(&fp_sp_vd_ECU_M_CFG_BON_INIT[0], u2_NC_VD_FVD(fp_sp_vd_ECU_M_CFG_BON_INIT));
#endif   /* BEV Rebase provisionally */
    vd_g_XSpiMETInit();
    /* ^^ User Hook end   ^^ */

    /*******************************************************************/
    /* vd_g_Rim_PostInit should be called after all user init function */
    /*******************************************************************/
    vd_g_Rim_PostInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_22SSCallout_StaRstInit(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_22SSCallout_StaRstInit(void)
{
#if 0   /* BEV Rebase provisionally */
    static const FP_VD_FVD             fp_sp_vd_ECU_M_CFG_RST_INIT[] = {
        &vd_g_EvschgRstwkInit,
        &vd_g_VardefRstwkInit,
        &vd_g_HudCaInit,
        &vd_g_McstRstwkInit,
        &vd_g_LocaleRstWkupInit,
        &vd_g_SoundCriMgrInitialize,
        &vd_g_DrectxRstInit,
        &vd_g_DioIfInit,
        &vd_g_DimInit,
        &vd_g_IllumiRstInit,
        &vd_g_PtsctmpInit,
        &vd_g_AlertInit,
        &vd_g_SbltwrnInit,
        &vd_g_TelltaleInit,
        &vd_g_ThblnkrRstWkInit,
        &vd_g_VehspdInit,
        &vd_g_VptranInit,
        &vd_g_wChimeInit,
        &vd_g_GaugeRstwkInit,
        &vd_g_EngspdRstwkInit,
        &vd_g_EngspdDetInit,
        &vd_g_OdoRstwkInit,
        &vd_g_TripsnsrInit,
        &vd_g_TripcomWkupInit,
        &vd_g_AmbtmpRstWkInit,
        &vd_g_VdsCIInit,
        &vd_g_MulmedColorInit,
        &vd_g_MulmedMulfrInit,
        &vd_g_RcmmUIInit,
        &vd_g_BattpowInit,
        &vd_g_DrvIndPwrInit,
        &vd_g_DrvIndEcoInit,
        &vd_g_DrvIndHvInit,
        &vd_g_SbltsyncInit,
        &vd_g_OilmilInit,
        &vd_g_HmiProxyRstInit,
        &vd_g_GatewayCxpiInit,
        &vd_g_GatewaymmInit,
        &vd_g_HdimmgrWkRstInit,
        &vd_g_HudImgAdjInit,
        &vd_g_MmLangWkupInit,
        &vd_g_VardefMmUnitWkupInit,
        &vd_g_FspomgrWkupInit,
        &vd_g_AttmpInit,
        &vd_g_MMAppCtrlInitial,
        &vd_g_BatcareRstwkInit,
        &vd_g_DateSIMETInit
    };
#endif   /* BEV Rebase provisionally */

    U1    u1_t_rslt;

    /*****************************************************/
    /* Rim, Nvmc Init Function should be called at first */
    /*****************************************************/
    vd_g_Rim_WkupInit();

    vd_g_Nvmc_WkupInit();
    do{
        u1_t_rslt = u1_g_Nvmc_WkupRead();
    }while(u1_t_rslt != (U1)FALSE);

    vd_g_oXCANRstInit();
    vd_g_VehopemdRstInit();
    vd_g_iVDshInit();

    /* vv User Hook start vv */
#if 0   /* BEV Rebase provisionally */
    vd_g_NWCMWkupInit();
    vd_g_Fpcall_vd_Fvd(&fp_sp_vd_ECU_M_CFG_RST_INIT[0], u2_NC_VD_FVD(fp_sp_vd_ECU_M_CFG_RST_INIT));
#endif   /* BEV Rebase provisionally */
    vd_g_XSpiMETInit();
    /* ^^ User Hook end   ^^ */

    /*******************************************************************/
    /* vd_g_Rim_PostInit should be called after all user init function */
    /*******************************************************************/
    vd_g_Rim_PostInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_22SSCallout_StaWkupInit(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_22SSCallout_StaWkupInit(void)
{
#if 0   /* BEV Rebase provisionally */
    static const FP_VD_FVD             fp_sp_vd_ECU_M_CFG_WKUP_INIT[] = {
        &vd_g_EvschgRstwkInit,
        &vd_g_VardefRstwkInit,
        &vd_g_HudCaInit,
        &vd_g_McstRstwkInit,
        &vd_g_LocaleRstWkupInit,
        &vd_g_SoundCriMgrInitialize,
        &vd_g_DrectxWkupInit,
        &vd_g_DioIfInit,
        &vd_g_DimInit,
        &vd_g_IllumiWkupInit,
        &vd_g_PtsctmpInit,
        &vd_g_AlertInit,
        &vd_g_SbltwrnInit,
        &vd_g_TelltaleInit,
        &vd_g_ThblnkrRstWkInit,
        &vd_g_VehspdInit,
        &vd_g_VptranInit,
        &vd_g_wChimeInit,
        &vd_g_GaugeRstwkInit,
        &vd_g_EngspdRstwkInit,
        &vd_g_EngspdDetInit,
        &vd_g_OdoRstwkInit,
        &vd_g_TripsnsrInit,
        &vd_g_TripcomWkupInit,
        &vd_g_AmbtmpRstWkInit,
        &vd_g_VdsCIInit,
        &vd_g_MulmedColorInit,
        &vd_g_MulmedMulfrInit,
        &vd_g_RcmmUIInit,
        &vd_g_BattpowInit,
        &vd_g_DrvIndPwrInit,
        &vd_g_DrvIndEcoInit,
        &vd_g_DrvIndHvInit,
        &vd_g_SbltsyncInit,
        &vd_g_OilmilInit,
        &vd_g_HmiProxyWkupInit,
        &vd_g_GatewayCxpiInit,
        &vd_g_GatewaymmInit,
        &vd_g_HdimmgrWkRstInit,
        &vd_g_HudImgAdjInit,
        &vd_g_MmLangWkupInit,
        &vd_g_VardefMmUnitWkupInit,
        &vd_g_FspomgrWkupInit,
        &vd_g_AttmpInit,
        &vd_g_MMAppCtrlInitial,
        &vd_g_BatcareRstwkInit,
        &vd_g_DateSIMETInit
    };
#endif   /* BEV Rebase provisionally */

    U1    u1_t_rslt;

    /*****************************************************/
    /* Rim, Nvmc Init Function should be called at first */
    /*****************************************************/
    vd_g_Rim_WkupInit();

    vd_g_Nvmc_WkupInit();
    do{
        u1_t_rslt = u1_g_Nvmc_WkupRead();
    }while(u1_t_rslt != (U1)FALSE);

    vd_g_oXCANWkupInit();
    vd_g_VehopemdWkupInit();
    vd_g_iVDshInit();

    /* vv User Hook start vv */
#if 0   /* BEV Rebase provisionally */
    vd_g_NWCMWkupInit();
    vd_g_Fpcall_vd_Fvd(&fp_sp_vd_ECU_M_CFG_WKUP_INIT[0], u2_NC_VD_FVD(fp_sp_vd_ECU_M_CFG_WKUP_INIT));
#endif   /* BEV Rebase provisionally */
    vd_g_XSpiMETInit();
    /* ^^ User Hook end   ^^ */

    /*******************************************************************/
    /* vd_g_Rim_PostInit should be called after all user init function */
    /*******************************************************************/
    vd_g_Rim_PostInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_22SSCallout_PrepShtdwn(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void vd_g_22SSCallout_PrepShtdwn(void)
{
#if 0   /* BEV Rebase provisionally */
    vd_g_SoundCriMgr_DeInit();
#endif   /* BEV Rebase provisionally */
}
