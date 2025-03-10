/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_ResetM.c
 * [Module]			ResetM
 * [Function]		Manage reset
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_TYPE.h>
#include <SS_Internal.h>

#include <SS_MemmapSdaDisableB_Env.h>
#include <SS_Memmap_Env.h>

#include <SS_MemmapSdaDisableE_Env.h>

#include <SS_MemmapSdaSelectB_Env.h>
#include <SS_ResetM.h>
#include <SS_ResetM_Callout.h>
#include <SS_CpuCore.h>
#include <SS_Error_Callout.h>
#include <SS_ISeq.h>
#include <SS_Error.h>
#include <SS_Memory.h>

/*----------------------------------------------------------------------------
 *		Variables
 *--------------------------------------------------------------------------*/
#if (SS_USE_CORE_COUNT >= 2u)
static SS_RequestType SS_ResetM_u4SyncResetReqFlag;
#endif /* (SS_USE_CORE_COUNT >= 2u) */

#include <SS_MemmapSdaSelectE_Env.h>

#if (SS_USE_CORE_COUNT >= 2u)
/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------
 * [Format]		void SS_ResetM_init(void)
 * [Function]	コア同期リセット機能で用いる変数の初期化とRAM Test
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_ResetM_init(void)
{
    /* コア同期リセット用変数初期化＆固着チェック(スタートアップ時のみ)	*/
    /* ・固着検出時は即リセット											*/
    SS_ResetM_u4SyncResetReqFlag = SS_REQUEST_NONE;

    /* SS_TEST_MEMORY_CHECK_RESET_INIT */
    SS_Memory_writeScan(&SS_ResetM_u4SyncResetReqFlag, sizeof(SS_RequestType));

    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_ResetM_requestReset(void)
 * [Function]	コア間同期リセット要求を発行 (定期タスク非動作時用)
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_ResetM_requestReset(void)
{
    SS_ResetM_u4SyncResetReqFlag = SS_REQUEST_EXIST;

    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_ResetM_check(void)
 * [Function]	コア同期リセット要求が出されているかのチェック・リセット実施
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_ResetM_check(void)
{

    if (SS_ResetM_u4SyncResetReqFlag == SS_REQUEST_NONE)
    {
        /* 何もしない */
    }
    else if (SS_ResetM_u4SyncResetReqFlag == SS_REQUEST_EXIST)
    {
        /* リセット前フック実行 */
        SS_ISeq_syncCores(SS_ISEQ_u2SID_RESETM_RSTREQ_A);
        
        SS_Pm_resetCallout();
        
        SS_ISeq_syncCores(SS_ISEQ_u2SID_RESETM_RSTREQ_B);

        /* マスターコアからリセット発行 */
        SS_CpuCore_entryMasterSection();
        {
            SS_Error_ResetCallout();
        }
        SS_CpuCore_exitMasterSection();

        while (1)
        {
            ; /* 無限ループ */
        }
    }
    else
    {
        SS_Error_setFactor(SS_ERROR_DATA);
    }
}
#endif /* (SS_USE_CORE_COUNT >= 2u) */
