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

#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_Memmap.h>
#include <Ecu_Intg.h>
#include <Ecu_Intg_Callout.h>
#include <Ecu_Int.h>

#include "Dio.h"
#include "Adc.h"
#include "wdg_drv.h"

#include "iohw_adc.h"
#include "iohw_diflt.h"

#include "icu_drv_wk.h"

#include "veh_opemd.h"
#include "oxcan.h"
#include "oxdocan.h"
#include "L3R_Scheduler.h"

#include "stub.h"

/*----------------------------------------------------------------------------
 *		置換シンボル定義
 *--------------------------------------------------------------------------*/
#define REG_u4SWSRESA                (*(volatile uint32 *)((uint32)0xFF98840CUL)) /* SWSRESA */
#define REG_u4RESKCPROT0             (*(volatile uint32 *)((uint32)0xFF980F00UL)) /* RESKCPROT0 */
#define VAL_u4RESKCPROT0_KCE_ENABLE  (0xA5A5A501UL)
#define VAL_u4RESKCPROT0_KCE_DISABLE (0xA5A5A500UL)

/* BSEQ0CTL - BIST Skip Control Register for FBIST0 */
#define APL_REG_BSEQ0CTL            (*(volatile uint32 *)0xFF988400UL)
#define APL_BSEQ0CTL_BIST_SKIP_SET  (0x00000002UL)

/* RESFC - Reset Factor Clear Register */
#define APL_REG_RESFC               (*(volatile uint32 *)0xFF980C00UL)
#define APL_RESFC_ALL_CLEAR         (0x0000F5DDUL)

#define RPRG_APL_RPGFLAGADDR        (0xFE800000UL)  /* ECU Software Launch Request Address */
#define RPRG_APL_RPGDATAADDR        (0xFE800004UL)  /* Launch Request Parameter Address */
#define RPRG_APL_SIDDATAADDR        (0xFE800024UL)  /* SID Information Address */

/*----------------------------------------------------------------------------
 *		変数宣言
 *--------------------------------------------------------------------------*/
static U1                    u1_s_iohw_adc_flipcount;
#include <Ecu_Memmap_SdaDisableE_env.h>

/*----------------------------------------------------------------------------
 *      プロトタイプ宣言
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		プログラム
 *--------------------------------------------------------------------------*/

Std_ReturnType Ecu_Intg_initCdd(Ecu_Intg_BootCauseType u4BootCause)
{

    switch (u4BootCause){
        case ECU_INTG_u4BTCAUSE_PON :
            vd_g_oXDoCANPreInit();      /* vd_g_oXDoCANPreInit shall be called before vd_g_oXCANRstInit */
            vd_g_oXCANRstInit();
            vd_g_oXDoCANBonInit();
            vd_g_VehopemdRstInit();

            vd_g_StubBonInit();
            break;
        case ECU_INTG_u4BTCAUSE_RESET:
            vd_g_oXDoCANPreInit();      /* vd_g_oXDoCANPreInit shall be called before vd_g_oXCANRstInit */
            vd_g_oXCANRstInit();
            vd_g_oXDoCANRstInit();
            vd_g_VehopemdRstInit();

            vd_g_StubRstInit();
            break;
        default:
            vd_g_oXDoCANPreInit();      /* vd_g_oXDoCANPreInit shall be called before vd_g_oXCANWkupInit */
            vd_g_oXCANWkupInit();
            vd_g_oXDoCANWkupInit();
            vd_g_VehopemdWkupInit();

            vd_g_StubWkupInit();
            break;
    }

    return E_OK;
}


Std_ReturnType Ecu_Intg_initAppCallout(Ecu_Intg_BootCauseType u4BootCause)
{
    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddHigh(void)
{
    BswM_CS_MainFunctionHigh();
    L3R_System_DriverTask();

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddMidIn(void)
{
    vd_g_oXCANMainPreTask();
    vd_g_VehopemdMainTask();

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncApp(void)
{
    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddMidOut(void)
{
    if ( ( u1_s_iohw_adc_flipcount & 0x01 ) == 0x01 )
    {
        vd_g_IoHwDifltMainTask();               /* 10ms */
        vd_g_IoHwAdcSeqAct((U1)FALSE);
        vd_g_IoHwAdcCvstStart();
    }
    else
    {
        vd_g_IoHwAdcCvstFinish();
        vd_g_IoHwAdcMainTask();
    }
    u1_s_iohw_adc_flipcount++;

    vd_g_oXDoCANMainTask();
    vd_g_oXCANMainPostTask();

    return E_OK;
}


Std_ReturnType Ecu_Intg_mainFuncCddLow(void)   /* C-DC VM0 Low Task: 10ms */
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

/**---------------------------------------------------------------------------
 * [Format]		void SS_CpuCore_requestReprog(void)
 * [Function]	Reprog Request
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
/*static void SS_CpuCore_requestReprog(void)*/
void SS_CpuCore_requestReprog(void)     /* @@@ */
{
    uint32 *papl_rpgparamByte;
    uint32 *papl_sidparamByte;
    uint32 *papl_rpgflag;
    
    papl_rpgparamByte = (uint32 *)RPRG_APL_RPGDATAADDR;
    papl_sidparamByte = (uint32 *)RPRG_APL_SIDDATAADDR;
    papl_rpgflag = (uint32 *)RPRG_APL_RPGFLAGADDR;
    
    papl_rpgparamByte[0] = (uint32)0x17DA1805UL;
    papl_rpgparamByte[1] = (uint32)0x020000E0UL;
    papl_rpgparamByte[2] = (uint32)0x240080FEUL;
    papl_rpgparamByte[3] = (uint32)0x00000000UL;
    papl_rpgparamByte[4] = (uint32)0x45230100UL;
    papl_rpgparamByte[5] = (uint32)0xCDAB8967UL;
    papl_rpgparamByte[6] = (uint32)0x543210EFUL;
    papl_rpgparamByte[7] = (uint32)0xDCBA9876UL;
   
    papl_sidparamByte[0] = (uint32)0xFFFF0210UL;

#if 0
    papl_rpgparamByte[0] = (uint8)0x05U;        /* Receive channel */       /* ^^^ */
    papl_rpgparamByte[1] = (uint8)0x18U;        /* Incoming CAN ID #0 */
    papl_rpgparamByte[2] = (uint8)0xDAU;        /* Incoming CAN ID #1 */
    papl_rpgparamByte[3] = (uint8)0x17U;        /* Incoming CAN ID #2 */    /* ^^^ */
    papl_rpgparamByte[4] = (uint8)0xE0U;        /* Incoming CAN ID #3 */    /* ^^^ */
    papl_rpgparamByte[5] = (uint8)0x00U;        /* SubMicon Type */
    papl_rpgparamByte[6] = (uint8)0x00U;        /* Message size #0 */
    papl_rpgparamByte[7] = (uint8)0x02U;        /* Message size #1 */
    papl_rpgparamByte[8] = (uint8)((RPRG_APL_SIDDATAADDR >> 24U) & 0x000000FFUL);   /* Message address #0 */
    papl_rpgparamByte[9] = (uint8)((RPRG_APL_SIDDATAADDR >> 16U) & 0x000000FFUL);   /* Message address #1 */
    papl_rpgparamByte[10] = (uint8)((RPRG_APL_SIDDATAADDR >> 8U) & 0x000000FFUL);   /* Message address #2 */
    papl_rpgparamByte[11] = (uint8)(RPRG_APL_SIDDATAADDR & 0x000000FFUL);           /* Message address #3 */
    papl_rpgparamByte[12] = (uint8)0x00U;       /* Reserve */
    papl_rpgparamByte[13] = (uint8)0x00U;       /* Reserve */
    papl_rpgparamByte[14] = (uint8)0x00U;       /* Reserve */
    papl_rpgparamByte[15] = (uint8)0x00U;       /* Reserve */
    papl_rpgparamByte[16] = (uint8)0x00U;       /* Reserve */
    papl_rpgparamByte[17] = (uint8)0x01U;       /* User Optional */
    papl_rpgparamByte[18] = (uint8)0x23U;       /* User Optional */
    papl_rpgparamByte[19] = (uint8)0x45U;       /* User Optional */
    papl_rpgparamByte[20] = (uint8)0x67U;       /* User Optional */
    papl_rpgparamByte[21] = (uint8)0x89U;       /* User Optional */
    papl_rpgparamByte[22] = (uint8)0xABU;       /* User Optional */
    papl_rpgparamByte[23] = (uint8)0xCDU;       /* User Optional */
    papl_rpgparamByte[24] = (uint8)0xEFU;       /* User Optional */
    papl_rpgparamByte[25] = (uint8)0x10U;       /* User Optional */
    papl_rpgparamByte[26] = (uint8)0x32U;       /* User Optional */
    papl_rpgparamByte[27] = (uint8)0x54U;       /* User Optional */
    papl_rpgparamByte[28] = (uint8)0x76U;       /* User Optional */
    papl_rpgparamByte[29] = (uint8)0x98U;       /* User Optional */
    papl_rpgparamByte[30] = (uint8)0xBAU;       /* User Optional */
    papl_rpgparamByte[31] = (uint8)0xDCU;       /* User Optional */

    /* set SID Information - BSC ADD */
    papl_sidparamByte[0] = (uint8)0x10U;        /* SID */
    papl_sidparamByte[1] = (uint8)0x02U;        /* Subfunction */
    papl_sidparamByte[2] = (uint8)0xFFU;
    papl_sidparamByte[3] = (uint8)0xFFU;
#endif

    *papl_rpgflag = 0x5AA5A55AUL;

    APL_REG_RESFC = APL_RESFC_ALL_CLEAR;        /* Reset Factor Clear */

    /* LBIST Only */
    REG_u4RESKCPROT0 = VAL_u4RESKCPROT0_KCE_ENABLE;
    APL_REG_BSEQ0CTL = APL_BSEQ0CTL_BIST_SKIP_SET;
    REG_u4RESKCPROT0 = VAL_u4RESKCPROT0_KCE_DISABLE;

    Ecu_Int_performReset();

    return;
}
