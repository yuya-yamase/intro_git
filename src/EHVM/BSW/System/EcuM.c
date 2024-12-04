/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		EcuM.c
 * [Module]			EcuM
 * [Function]		EcuM
 * [Notes]			インテグ対象の汎用BSWがAubistの場合に有効となる（ビルド対象とする）
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_TYPE.h>
#include <SS_Internal.h>
#include <ehvm.h>

#include <SS_MemmapSdaDisableB_Env.h>
#include <SS_Memmap_Env.h>

#include <SS_MemmapSdaDisableE_Env.h>

#include <SS_MemmapSdaSelectB_Env.h>
#include <SS_ISeq.h>
#include <SS_ISeq_Callout.h>
#include <EcuM.h>

#include <SS_MemmapSdaSelectE_Env.h>

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
static void EcuM_AL_DriverInitZero(void);
static void EcuM_AL_DriverInitOne(void);

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------
 * [Format]		void EcuM_Init(void)
 * [Function]	EcuMの初期化ステップ、及びStartOSを実行する
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void EcuM_Init(void)
{
    EcuM_AL_DriverInitZero();
    EcuM_AL_DriverInitOne();

    /* TPcsw_StartOS_if0 */
    ehvm_start_hv();
    /* TPcsw_StartOS_endif */

    return;
}

/**---------------------------------------------------------------------------
 * [Format]		static void EcuM_AL_DriverInitZero(void)
 * [Function]	DriverInitZeroを実行する
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
static void EcuM_AL_DriverInitZero(void)
{
    SS_Pm_DriverInitZero();

    return;
}

/**---------------------------------------------------------------------------
 * [Format]		static void EcuM_AL_DriverInitOne(void)
 * [Function]	DriverInitOneを実行する
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
static void EcuM_AL_DriverInitOne(void)
{
    SS_Pm_DriverInitOne();

    return;
}

