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
#include "oxdocan.h"
#include "ivdsh.h"

/* Memory               */
#include "rim_ctl.h"
/* #include "nvmc_mgr.h" */

#include "ExtSigCtrl_Main.h"

/* IVI */
#include "Mcu_I2c_Ctrl.h"
#include "x_spi_ivi.h"
#include "IVI_PwrCtrl_Main.h"
#include "IVI_ExtSigCtrl_Main.h"
#include "IVI_PictCtrl_Main.h"
#include "IVI_GyrCtrl_Main.h"
#include "IVI_DspCtrl_Main.h"
#include "IVI_DrcCtrl_Main.h"
#include "IVI_CanCtrl_Main.h"
#include "fwupx.h"
#include "iVDTr_Main.h"
#include "DiagApp.h"

/* ClkCtrl */
#include "RtcIc_drv.h"
#include "Date_clk.h"
#include "datesi.h"

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
/*    U1    u1_t_rslt;     */

    /*****************************************************/
    /* Rim, Nvmc Init Function should be called at first */
    /*****************************************************/
    vd_g_Rim_BonInit();

/*    vd_g_Nvmc_BonInit(); */
/*    do{  */
/*        u1_t_rslt = u1_g_Nvmc_BonRead(); */
/*    }while(u1_t_rslt != (U1)FALSE); */

    vd_g_oXCANRstInit();
    vd_g_oXDoCANBonInit();
    vd_g_VehopemdRstInit();
    vd_g_iVDshInit();

    /* vv User Hook start vv */
    ExtSigCtrl_Init();

    /* IVI */
    Mcu_Dev_I2c_Ctrl_Init();
    vd_g_XspiIviBonInit();
    vd_g_Ivi_PwrCtrl_Main_Bon_init();
    vd_g_Ivi_ExtSigCtrl_Main_Bon_init();
    vd_g_Ivi_PictCtrl_Main_Bon_init();
    vd_g_Ivi_GyrCtrl_Main_Bon_init();
    vd_g_Ivi_DspCtrl_Main_Bon_init();
	vd_g_Ivi_DrcCtrl_Main_Bon_init();
    vd_g_Ivi_CanCtrl_Main_Bon_init();
    vd_g_FwupxInit();
    vd_g_iVDTrInit();
    vd_g_DiagAppInit();

    /* ClkCtrl */
    vd_g_RtcIcBonInit();
    vd_g_DateclkBonInit();
    vd_g_DateSIBonInit();
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
/*    U1    u1_t_rslt;     */

    /*****************************************************/
    /* Rim, Nvmc Init Function should be called at first */
    /*****************************************************/
    vd_g_Rim_WkupInit();

/*    vd_g_Nvmc_WkupInit(); */
/*    do{  */
/*        u1_t_rslt = u1_g_Nvmc_WkupRead(); */
/*    }while(u1_t_rslt != (U1)FALSE); */

    vd_g_oXCANRstInit();
    vd_g_oXDoCANRstInit();
    vd_g_VehopemdRstInit();
    vd_g_iVDshInit();

    /* vv User Hook start vv */
    ExtSigCtrl_Init();

    /* IVI */
    Mcu_Dev_I2c_Ctrl_Init();
    vd_g_XspiIviRstInit();
    vd_g_Ivi_PwrCtrl_Main_Rst_init();
    vd_g_Ivi_ExtSigCtrl_Main_Rst_init();
    vd_g_Ivi_PictCtrl_Main_Rst_init();
    vd_g_Ivi_GyrCtrl_Main_Rst_init();
    vd_g_Ivi_DspCtrl_Main_Rst_init();
    vd_g_Ivi_CanCtrl_Main_Rst_init();
    vd_g_FwupxInit();
    vd_g_iVDTrInit();
    vd_g_DiagAppInit();

    /* ClkCtrl */
    vd_g_RtcIcRstwkInit();
    vd_g_DateclkRstwkInit();
    vd_g_DateSIRstWkupInit();
    vd_g_Ivi_DrcCtrl_Main_Rst_init();
    
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
/*    U1    u1_t_rslt;     */

    /*****************************************************/
    /* Rim, Nvmc Init Function should be called at first */
    /*****************************************************/
    vd_g_Rim_WkupInit();

/*    vd_g_Nvmc_WkupInit(); */
/*    do{  */
/*        u1_t_rslt = u1_g_Nvmc_WkupRead(); */
/*    }while(u1_t_rslt != (U1)FALSE); */

    vd_g_oXCANWkupInit();
    vd_g_oXDoCANWkupInit();
    vd_g_VehopemdWkupInit();
    vd_g_iVDshInit();

    /* vv User Hook start vv */
    ExtSigCtrl_Init();

    /* IVI */
    Mcu_Dev_I2c_Ctrl_Init();
    vd_g_XspiIviWkupInit();
    vd_g_Ivi_PwrCtrl_Main_Wkup_init();
    vd_g_Ivi_ExtSigCtrl_Main_Wkup_init();
    vd_g_Ivi_PictCtrl_Main_Wkup_init();
    vd_g_Ivi_GyrCtrl_Main_Wkup_init();
    vd_g_Ivi_DspCtrl_Main_Wkup_init();
    vd_g_Ivi_DrcCtrl_Main_Wkup_init();
    vd_g_Ivi_CanCtrl_Main_Wkup_init();
    vd_g_FwupxInit();
	vd_g_iVDTrInit();
    vd_g_DiagAppInit();

    /* ClkCtrl */
    vd_g_RtcIcRstwkInit();
    vd_g_DateclkRstwkInit();
    vd_g_DateSIRstWkupInit();
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
}
