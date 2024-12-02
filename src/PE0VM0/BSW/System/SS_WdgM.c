/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_WdgM.c
 * [Module]			WdgM
 * [Function]		WdgM
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_TYPE.h>
#include <SS_Internal.h>
#include <Os.h>

#include <SS_MemmapSdaDisableB_Env.h>
#include <SS_MemmapProtect_Env.h>

#include <SS_MemmapSdaDisableE_Env.h>

#include <SS_MemmapSdaSelectB_Env.h>
#include <SS_WdgM.h>
#include <SS_WdgM_Callout.h>

#include <SS_MemmapSdaSelectE_Env.h>

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
/* 通過チェックポイントのTOP */
#define SS_WDGM_u1CHECKPOINT_TOP ((uint8)0U)
/* 通過チェックポイントなし */
#define SS_WDGM_u1NON_CHECKPOINT ((uint8)0xFFU)

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
static Std_ReturnType SS_WdgM_OrderMon(const SS_WdgM_OrderType *pt_OrderTbl, uint8 u1_CheckPointId);
static Std_ReturnType SS_WdgM_TimeMon(const SS_WdgM_OrderType *pt_OrderTbl, uint8 u1_CheckPointId, uint32 u4_CurrenTickTime);

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------
 * [Format]		Std_ReturnType SS_WdgM_init(const SS_WdgM_OrderType* pt_OrderTbl)
 * [Function]	WdgMの初期化
 * [Arguments]	pt_OrderTbl : Orderテーブルポインタ
 * [Return]		E_OK		: Argument is OK
 *				E_NOT_OK	: Argument is error
 * [Notes]		None
 *--------------------------------------------------------------------------*/
Std_ReturnType SS_WdgM_init(const SS_WdgM_OrderType *pt_OrderTbl)
{
    Std_ReturnType u1_Result;

    /* 戻り値に異常を設定 */
    u1_Result = E_NOT_OK;

    /* RomAreaTypeポインタアドレス正常? */
    if ((pt_OrderTbl != NULL_PTR) && (pt_OrderTbl->pt_RamAreaTbl != NULL_PTR))
    {
        /* チェックポイントID通過時刻クリア */
        pt_OrderTbl->pt_RamAreaTbl->u4_ClockTime = 0UL;
        /* 順序エラーカウンタクリア */
        pt_OrderTbl->pt_RamAreaTbl->u1_ProcessErrorCnt = (uint8)0U;
        /* MIN時間エラーカウンタクリア */
        pt_OrderTbl->pt_RamAreaTbl->u1_MinTimeErrorCnt = (uint8)0U;
        /* MAX時間エラーカウンタクリア */
        pt_OrderTbl->pt_RamAreaTbl->u1_MaxTimeErrorCnt = (uint8)0U;
        /* 通過チェックポイントIDを通過なしで初期化 */
        pt_OrderTbl->pt_RamAreaTbl->u1_PreCheckPoint = SS_WDGM_u1NON_CHECKPOINT;
        /* 戻り値に正常を設定 */
        u1_Result = E_OK;
    }

    return (u1_Result);
}

/**---------------------------------------------------------------------------
 * [Format]		Std_ReturnType SS_WdgM_checkPointReached(const SS_WdgM_OrderType * pt_OrderTbl,uint8 u1_CheckPointId)
 * [Function]	WdgM チェックポイント通過通知
 * [Arguments]	pt_OrderTbl : Order tabel pointer
 				u1_CheckPointId	: 通過チェックポイントID
 * [Return]		E_OK		: 引数パラメータ正常、監視結果正常
 *				E_NOT_OK	: 引数パラメータ異常 または 監視結果異常
 * [Notes]		None
 *--------------------------------------------------------------------------*/
Std_ReturnType SS_WdgM_checkPointReached(const SS_WdgM_OrderType *pt_OrderTbl, uint8 u1_CheckPointId)
{
    Std_ReturnType u1_Result;
    Std_ReturnType u1_OrderChkResult;
    Std_ReturnType u1_TimeChkResult;
    uint32         u4_CurrenTickTime;

    u1_Result = E_NOT_OK;

    /*********** 引数パラメータの取得＆チェック ***********/
    /* Orderテーブルポインタ,ROMエリアテーブルポインタ,ワークRAMテーブルポインタは正常? */
    if ((pt_OrderTbl != NULL_PTR) && (pt_OrderTbl->pt_RomAreaTbl != NULL_PTR) && (pt_OrderTbl->pt_RamAreaTbl != NULL_PTR))
    {
        
        SuspendAllInterrupts();
        /* 現在時間取得 */
        
        u4_CurrenTickTime = SS_WdgM_getCountCallout();
        
        /* Init後の初回通過チェックポイントID */
        if (SS_WDGM_u1NON_CHECKPOINT == pt_OrderTbl->pt_RamAreaTbl->u1_PreCheckPoint)
        {
            /* 通過チェックポイントIDの先頭(0)以外 */
            if (SS_WDGM_u1CHECKPOINT_TOP != u1_CheckPointId)
            {
                /* 順序エラーカウンタインクリメント */
                if (pt_OrderTbl->pt_RamAreaTbl->u1_ProcessErrorCnt < SS_TYPE_u1MAX)
                {
                    pt_OrderTbl->pt_RamAreaTbl->u1_ProcessErrorCnt++;
                }
            }
            /* 通過チェックポイントIDの先頭(0) */
            else
            {
                /* 順序エラーカウンタを0クリア */
                pt_OrderTbl->pt_RamAreaTbl->u1_ProcessErrorCnt = (uint8)0U;
                u1_Result                                      = E_OK;
            }
        }
        /* 2回目以降の通過チェックポイントID */
        else
        {
            u1_OrderChkResult = SS_WdgM_OrderMon(pt_OrderTbl, u1_CheckPointId);
            /* 時間監視設定ありか？ */
            if ((0UL != pt_OrderTbl->pt_RomAreaTbl[u1_CheckPointId].u4_MinTime) || (0UL != pt_OrderTbl->pt_RomAreaTbl[u1_CheckPointId].u4_MaxTime))
            {
                u1_TimeChkResult = SS_WdgM_TimeMon(pt_OrderTbl, u1_CheckPointId, u4_CurrenTickTime);
            }
            else
            {
                u1_TimeChkResult = E_OK;
            }

            /* 順序監視、時間監視の両方OKだった場合、返す結果をE_OKとする */
            if ((u1_OrderChkResult == E_OK) && (u1_TimeChkResult == E_OK))
            {
                u1_Result = E_OK;
            }
        }
        /* ワークRAMに通過チェックポイントIDを記憶 */
        pt_OrderTbl->pt_RamAreaTbl->u1_PreCheckPoint = u1_CheckPointId;
        /* ワークRAMにチェックポイントID通過時の時刻を記憶 */
        pt_OrderTbl->pt_RamAreaTbl->u4_ClockTime = u4_CurrenTickTime;
        ResumeAllInterrupts();
        
    }
    return (u1_Result);
}
/**---------------------------------------------------------------------------
 * [Format]		Std_ReturnType SS_WdgM_timeoutCheck(const SS_WdgM_OrderType* pt_OrderTbl)
 * [Function]	WdgM監視状態の更新
 * [Arguments]	pt_OrderTbl : Order tabel pointer
 * [Return]		E_OK		: Argument is OK
 *				E_NOT_OK	: Argument or timeout is error
 * [Notes]		None
 *--------------------------------------------------------------------------*/
Std_ReturnType SS_WdgM_timeoutCheck(const SS_WdgM_OrderType *pt_OrderTbl)
{
    Std_ReturnType u1_Result;
    uint8          u1_PreCheckPointId;
    uint8          u1_ExpCurCheckPointId;
    uint32         u4_CurrenTickTime;

    u1_Result = E_NOT_OK;

    /* Orderテーブルポインタ,ROMエリアテーブルポインタ,ワークRAMテーブルポインタは正常? */
    if ((pt_OrderTbl != NULL_PTR) && (pt_OrderTbl->pt_RomAreaTbl != NULL_PTR) && (pt_OrderTbl->pt_RamAreaTbl != NULL_PTR))
    {
        
        SuspendAllInterrupts();
        /* 現在時間取得 */
        
        u4_CurrenTickTime = SS_WdgM_getCountCallout();
        
        /* Init後の初回チェックポイントID？ */
        if (SS_WDGM_u1NON_CHECKPOINT == pt_OrderTbl->pt_RamAreaTbl->u1_PreCheckPoint)
        {
            /* Init後初回チェックポイントID */
            /* 初回チェックポイントIDのため、更新判定は不要 */
            u1_Result = E_OK;
        }
        else
        {
            /* 2回目以降のチェックポイントID */
            /* 前回チェックポイントIDを取得 */
            u1_PreCheckPointId = pt_OrderTbl->pt_RamAreaTbl->u1_PreCheckPoint;
            /* 期待するチェックポイントIDを算出 */
            u1_ExpCurCheckPointId = pt_OrderTbl->pt_RomAreaTbl[u1_PreCheckPointId + (uint8)1U].u1_CheckPointID;
            /* 期待するチェックポイントIDが終端？ */
            if (SS_u1WDGM_CHECKPOINT_TERMINATE == u1_ExpCurCheckPointId)
            {
                /* 期待するチェックポイントIDを先頭(0)にする */
                u1_ExpCurCheckPointId = SS_WDGM_u1CHECKPOINT_TOP;
            }

            /* 時間監視設定ありか？ */
            if ((0UL != pt_OrderTbl->pt_RomAreaTbl[u1_ExpCurCheckPointId].u4_MinTime) || (0UL != pt_OrderTbl->pt_RomAreaTbl[u1_ExpCurCheckPointId].u4_MaxTime))
            {
                u1_Result = SS_WdgM_TimeMon(pt_OrderTbl, u1_ExpCurCheckPointId, u4_CurrenTickTime);
            }
            else
            {
                u1_Result = E_OK;
            }
        }
        ResumeAllInterrupts();
        
    }
    return (u1_Result);
}

/**---------------------------------------------------------------------------
 * [Format]		Std_ReturnType SS_WdgM_OrderMon(const SS_WdgM_OrderType * pt_OrderTbl,uint8 u1_CheckPointId)
 * [Function]	順序監視（二回目以降用）
 * [Arguments]	pt_OrderTbl : Order tabel pointer
 				u1_CheckPointId	: 通過チェックポイントID
 * [Return]		E_OK		: 監視結果正常
 *				E_NOT_OK	: 監視結果異常
 * [Notes]		None
 *--------------------------------------------------------------------------*/
static Std_ReturnType SS_WdgM_OrderMon(const SS_WdgM_OrderType *pt_OrderTbl, uint8 u1_CheckPointId)
{
    Std_ReturnType u1_Result;
    uint8          u1_PreCheckPointId;
    uint8          u1_ExpCurCheckPointId;

    u1_Result = E_NOT_OK;

    /* 前回通過通過チェックポイントIDを取得 */
    u1_PreCheckPointId = pt_OrderTbl->pt_RamAreaTbl->u1_PreCheckPoint;
    /* 期待するチェックポイントIDを算出 */
    u1_ExpCurCheckPointId = pt_OrderTbl->pt_RomAreaTbl[u1_PreCheckPointId + (uint8)1U].u1_CheckPointID;
    /* 期待するチェックポイントIDが順序の終端ID？ */
    if (SS_u1WDGM_CHECKPOINT_TERMINATE == u1_ExpCurCheckPointId)
    {
        /* 期待するチェックポイントIDは先頭(0)にする */
        u1_ExpCurCheckPointId = SS_WDGM_u1CHECKPOINT_TOP;
    }
    /* チェックポイントIDの不一致？ */
    if (u1_ExpCurCheckPointId != u1_CheckPointId)
    {

        /* エラーカウンタオーバーフローガード */
        if (pt_OrderTbl->pt_RamAreaTbl->u1_ProcessErrorCnt < SS_TYPE_u1MAX)
        {
            /* 順序エラーカウンタインクリメント */
            pt_OrderTbl->pt_RamAreaTbl->u1_ProcessErrorCnt++;
        }
    }
    else
    {
        /* 順序エラーカウンタを0クリアする */
        pt_OrderTbl->pt_RamAreaTbl->u1_ProcessErrorCnt = (uint8)0U;
        u1_Result                                      = E_OK;
    }

    return (u1_Result);
}
/**---------------------------------------------------------------------------
 * [Format]		Std_ReturnType SS_WdgM_TimeMon(const SS_WdgM_OrderType * pt_OrderTbl,uint8 u1_CheckPointId,uint32 u4_CurrenTickTime)
 * [Function]	時間監視
 * [Arguments]	pt_OrderTbl : Order tabel pointer
 				u1_CheckPointId	: チェックポイントID
 				u4_CurrenTickTime : 現在時間
 * [Return]		E_OK		: 監視結果正常
 *				E_NOT_OK	: 監視結果異常
 * [Notes]		None
 *--------------------------------------------------------------------------*/
static Std_ReturnType SS_WdgM_TimeMon(const SS_WdgM_OrderType *pt_OrderTbl, uint8 u1_CheckPointId, uint32 u4_CurrenTickTime)
{
    Std_ReturnType u1_Result;
    uint32         u4_ElapsedTime;
    uint32         u4_PreviousTime;

    u1_Result = E_NOT_OK;

    u4_PreviousTime = pt_OrderTbl->pt_RamAreaTbl->u4_ClockTime;
    /* 経過時間算出 */
    if (u4_CurrenTickTime >= u4_PreviousTime)
    {
        u4_ElapsedTime = u4_CurrenTickTime - u4_PreviousTime;
    }
    else
    {
        u4_ElapsedTime = SS_TYPE_u4MAX - u4_PreviousTime + u4_CurrenTickTime; /* EDET_INT30 */
    }

    /* チェックポイントIDのMIN時間エラー? */
    if (pt_OrderTbl->pt_RomAreaTbl[u1_CheckPointId].u4_MinTime > u4_ElapsedTime)
    {
        /* MIN時間エラーカウンタをインクリメント */
        if (pt_OrderTbl->pt_RamAreaTbl->u1_MinTimeErrorCnt < SS_TYPE_u1MAX)
        {
            pt_OrderTbl->pt_RamAreaTbl->u1_MinTimeErrorCnt++;
        }
    }
    else
    {
        /* MIN時間エラーカウンタを0クリアする */
        pt_OrderTbl->pt_RamAreaTbl->u1_MinTimeErrorCnt = (uint8)0U;
        u1_Result                                      = E_OK;
    }
    /* チェックポイントIDのMAX時間エラー? */
    if (pt_OrderTbl->pt_RomAreaTbl[u1_CheckPointId].u4_MaxTime < u4_ElapsedTime)
    {
        /* MAX時間エラーカウンタをインクリメント */
        if (pt_OrderTbl->pt_RamAreaTbl->u1_MaxTimeErrorCnt < SS_TYPE_u1MAX)
        {
            pt_OrderTbl->pt_RamAreaTbl->u1_MaxTimeErrorCnt++;
        }
        u1_Result = E_NOT_OK;
    }
    else
    {
        /* MAX時間エラーカウンタを0クリアする */
        pt_OrderTbl->pt_RamAreaTbl->u1_MaxTimeErrorCnt = (uint8)0U;
    }

    return (u1_Result);
}
