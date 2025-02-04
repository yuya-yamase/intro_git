/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 *【ファイル名】	Ecu_AppIntg.c
 *【モジュール名】	Application Sample
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
#include <Ecu_Intg.h>
#include <Ecu_Intg_Callout.h>
#include <Ecu_Int.h>

#include "wdg_drv.h"

#include "stub.h"
#include "veh_opemd.h"
#include "oxcan.h"
#include "xspi.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif
#include "fpcall_vd_fvd.h"
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
#include "datesi.h"
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
#include "ecojdg.h"
#include "mmappctrl.h"
#include "attmp_cel.h"
#include "evschg.h"
#include "batcare.h"
#include "xspi_met.h"

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
ISR(INTOSTM0_ISR);

/*----------------------------------------------------------------------------
 *		プログラム
 *--------------------------------------------------------------------------*/

Std_ReturnType Ecu_Intg_initCdd(Ecu_Intg_BootCauseType u4BootCause)
{

    switch (u4BootCause){
        case ECU_INTG_u4BTCAUSE_PON :
            vd_g_StubBonInit();
            vd_g_oXCANRstInit();
            vd_g_VehopemdRstInit();
            break;
        case ECU_INTG_u4BTCAUSE_RESET:
            vd_g_StubRstInit();
            vd_g_oXCANRstInit();
            vd_g_VehopemdRstInit();
            break;
        default:
            vd_g_StubWkupInit();
            vd_g_oXCANWkupInit();
            vd_g_VehopemdWkupInit();
            break;
    }

    return E_OK;
}


Std_ReturnType Ecu_Intg_initAppCallout(Ecu_Intg_BootCauseType u4BootCause)
{
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
        &vd_g_DateSIBonInit,
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
        &vd_g_EcoJdgInit,
        &vd_g_AttmpInit,
        &vd_g_MMAppCtrlInitial,
        &vd_g_BatcareBonInit,
    };

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
        &vd_g_DateSIRstWkupInit,
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
        &vd_g_EcoJdgInit,
        &vd_g_AttmpInit,
        &vd_g_MMAppCtrlInitial,
        &vd_g_BatcareRstwkInit,
    };

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
        &vd_g_DateSIRstWkupInit,
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
        &vd_g_EcoJdgInit,
        &vd_g_AttmpInit,
        &vd_g_MMAppCtrlInitial,
        &vd_g_BatcareRstwkInit,
    };

    switch (u4BootCause){
        case ECU_INTG_u4BTCAUSE_PON :
            vd_g_NWCMBonInit();
            vd_g_Fpcall_vd_Fvd(&fp_sp_vd_ECU_M_CFG_BON_INIT[0], u2_NC_VD_FVD(fp_sp_vd_ECU_M_CFG_BON_INIT));
            break;
        case ECU_INTG_u4BTCAUSE_RESET:
            vd_g_NWCMWkupInit();
            vd_g_Fpcall_vd_Fvd(&fp_sp_vd_ECU_M_CFG_RST_INIT[0], u2_NC_VD_FVD(fp_sp_vd_ECU_M_CFG_RST_INIT));
            break;
        default:
            vd_g_NWCMWkupInit();
            vd_g_Fpcall_vd_Fvd(&fp_sp_vd_ECU_M_CFG_WKUP_INIT[0], u2_NC_VD_FVD(fp_sp_vd_ECU_M_CFG_WKUP_INIT));
            break;
    }
    /* XSPI初期化処理 */
    xspi_Init( XSPI_CH_02 );
	vd_g_XSpiMETInit();

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddHigh(void)
{
    BswM_CS_MainFunctionHigh();

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddMidIn(void)
{
    /* vd_g_Wdg_SetTriggerCondition((U2)0U); */

    vd_g_oXCANMainPreTask();

    vd_g_VehopemdMainTask();
    /* vd_g_Wdg_SetTriggerCondition((U2)0U);*/

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncApp(void)
{
    vd_g_XSpiMETPduRx();
    vd_g_XSpiMETPduTx();
    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddMidOut(void)
{
    vd_g_oXCANMainPostTask();
    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddLow(void)   /* C-DC MET Low Task: 10ms */
{
    vd_g_Wdg_SetTriggerCondition((U2)0U);
    return E_OK;
}


Std_ReturnType Ecu_Intg_idleFuncOut(void)
{
    return E_OK;
}


#if (SS_USE_SLEEP == STD_ON)
uint32 Ecu_Intg_sleepCallout(void)
{
    // 0: 間欠起床タイマOFF
    // 1000: 1sアラーム設定
    // 10000: 10sアラーム設定

    return (0UL);
}
#endif

#if (SS_USE_SLEEP == STD_ON)
uint32 Ecu_Intg_reSleepCallout(void)
{
    // 0: 間欠起床タイマOFF
    // 1000: 1sアラーム設定
    // 10000: 10sアラーム設定

    return (0UL);
}
#endif

#if (SS_USE_SLEEP == STD_ON)
// TRUE : ウェイクアップ要求する
// FALSE :ウェイクアップ要求しない（起動要因=ECU_INTG_u4BTCAUSE_WKUP_ANYならFALSEでもウェイクアップする）
boolean Ecu_Intg_isWakeupCallout(Ecu_Intg_BootCauseType u4BootCause)
{
    return FALSE;
}
#endif

void Ecu_Intg_preSTResetCallout(Ecu_Intg_STResetType u1Type, uint8 u1Reason)
{
    /* リセット前ユーザ実装処理 */

    return;
}


ISR(INTOSTM0_ISR)
{
    /*    INTOSTM0_ISR;*/

    /* XSPIメイン処理 */
    xspi_Main( XSPI_CH_02 );
}
