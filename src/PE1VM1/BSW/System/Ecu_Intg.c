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
#include <v800_ghs.h>
#include <Std_Types.h>
#include <SS.h>
#if (SS_USE_UP == STD_ON)
#include <Os.h>
#endif
// #include <Wdg.h>

#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_Memmap.h>
#include <Ecu_Intg.h>
#include <Ecu_Intg_Callout.h>
#include <Ecu_IntgHAL.h>
#include <Ecu_IntgHAL_Callout.h>
#include <Ecu_Int.h>
#include <scheduler.h>
#ifdef ECU_INTG_LWH_GUEST
#include <Ecu_Arb.h>
#endif
/*----------------------------------------------------------------------------
 *		置換シンボル定義
 *--------------------------------------------------------------------------*/
#define ECU_INTG_u1MAX_LVDINEST ((uint8)255U)

#define ECU_INTG_u4SLEEP_OK (0x12345670UL)
#define ECU_INTG_u4SLEEP_NG (0xEDCBA98FUL)

#define ECU_ING_u4SLEEPNG_CLR_PERIOD (4UL)

// 過敏スリープ対策の60sスリープ待ち (5ms x 200 x 60)
// #define ECU_INTG_STAY_RUN_CNT (12000UL)
#define ECU_INTG_u4STAY_RUN_CNT (1000UL) // デバッグ用に、5sに設定

/*----------------------------------------------------------------------------
 *		Type
 *--------------------------------------------------------------------------*/
typedef struct
{
    uint8 u1STACK[ECU_INTG_u1MAX_LVDINEST];
    uint8 u1Ptr; // 次にデータを格納する配列INDEX
} Ecu_Intg_LvDINestStackType;

/*----------------------------------------------------------------------------
 *		変数宣言
 *--------------------------------------------------------------------------*/
Ecu_Intg_STResetType Ecu_Intg_u1STResetReason[ECU_INTG_ST_RESET_REASON_NUM] __attribute__((section(".ecu_n_bvar")));

static Ecu_Intg_BootCauseType Ecu_Intg_u4BootCause;

static Ecu_Intg_LvDINestStackType Ecu_Intg_stLDINestStack[SS_USE_CORE_COUNT];

#if (SS_USE_MODE == STD_ON)
static uint32 Ecu_Intg_u4SleepNgFlag[SS_USE_CORE_COUNT];
static uint32 u4TickCntr[SS_USE_CORE_COUNT];
static uint32 Ecu_Intg_u4StayRunCnt[SS_USE_CORE_COUNT];
#endif

#include <Ecu_Memmap_SdaDisableE_env.h>

/*----------------------------------------------------------------------------
 *      プロトタイプ宣言
 *--------------------------------------------------------------------------*/
static Ecu_Intg_LvDINestStackType *Ecu_Intg_selectNestStack(void);

static void Ecu_Intg_setSTResetKey(uint8 u1Reason);

#if (SS_USE_MODE == STD_ON)
static void Ecu_Intg_convSleepNg(void);
#endif

/*----------------------------------------------------------------------------
 *		プログラム
 *--------------------------------------------------------------------------*/

void Ecu_Intg_init(void)
{
    uint32 u4Idx;

    Ecu_IntgHAL_enableFpu();

    SS_CpuCore_entryMasterSection();
    {

        Ecu_Intg_u4BootCause = Ecu_IntgHAL_getBootCause();

        for (u4Idx = 0UL; u4Idx < SS_USE_CORE_COUNT; u4Idx++)
        {
            Ecu_Intg_stLDINestStack[u4Idx].u1Ptr = 0U;
#if (SS_USE_MODE == STD_ON)
/* @ zantei SLEEP NG */
//            Ecu_Intg_u4SleepNgFlag[u4Idx] = ECU_INTG_u4SLEEP_OK;
            Ecu_Intg_u4SleepNgFlag[u4Idx] = ECU_INTG_u4SLEEP_NG;
/* @ zantei SLEEP NG */
            u4TickCntr[u4Idx]             = 0UL;
            Ecu_Intg_u4StayRunCnt[u4Idx]  = 0UL;
#endif
        }
    }
    SS_CpuCore_exitMasterSection();

    return;
}

Ecu_Intg_BootCauseType Ecu_Intg_hasBootCause(void)
{
    return Ecu_Intg_u4BootCause;
}

void Ecu_Intg_initApp(void)
{
    Ecu_Intg_BootCauseType u4BootCause;

    (void)Ecu_Intg_initAppCallout(Ecu_Intg_u4BootCause);

    u4BootCause = Ecu_IntgHAL_getBootCause();
    if (u4BootCause == ECU_INTG_u4BTCAUSE_PON)
    {
        (void)SS_Memory_set(__ghsbegin_ecu_n_bvar_top, 0UL, (uint32)ECU_N_BVAR_SIZE);
    }

    return;
}
#if 0
void Ecu_Intg_preClockup(void)
{
    (void)Ecu_Intg_preClockCallout(Ecu_Intg_u4BootCause);
}

void Ecu_Intg_postClockup(void)
{
    (void)Ecu_Intg_postClockCallout(Ecu_Intg_u4BootCause);
}
#endif

#if (SS_USE_MODE == STD_ON)
static void Ecu_Intg_convSleepNg(void)
{
    uint32 u4cId;

    u4cId = SS_CpuCore_getCoreID();

    if (Ecu_Intg_u4SleepNgFlag[u4cId] == ECU_INTG_u4SLEEP_OK)
    {
        if (Ecu_Intg_u4StayRunCnt[u4cId] < ECU_INTG_u4STAY_RUN_CNT)
        {
            Ecu_Intg_u4StayRunCnt[u4cId]++;
            SS_Mm_requestRun();
        }
        else
        {
#if (SS_MM_USE_ASYNC_ARB == STD_ON)
            SS_Mm_releaseRun();
#endif
        }
    }
    else if (Ecu_Intg_u4SleepNgFlag[u4cId] == ECU_INTG_u4SLEEP_NG)
    {
        Ecu_Intg_u4StayRunCnt[u4cId] = 0UL;
        SS_Mm_requestRun();
    }
    else
    {
        Ecu_Int_performReset();
    }
    return;
}
#endif

#if (SS_USE_MODE == STD_ON)
Std_ReturnType Ecu_Intg_arbitrate(SS_Mm_modeType u4SS_Mode)
{
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
#ifdef ECU_INTG_LWH_GUEST
    boolean bAwake;
    boolean bAwakeArb;
#endif

    uint32 u4cId;

    u4cId = SS_CpuCore_getCoreID();

    // 各APPのSleepNG収集
    vd_g_SchdlrMainTask();

    switch (u4SS_Mode)
    {

    case SS_MM_PRERUN_SUP:
        // MSインテグの想定
        // SS_Callout側で、NvMReadAll完了待ち
        // SS_Callout側のEntryCalloutで、NvMReadAll開始

#if (SS_MM_USE_ASYNC_ARB == STD_ON)
        // 暫定で、即抜け
        SS_Mm_releasePreRun();
#endif
        break;

    case SS_MM_PRERUN_WUP:
        // MSインテグの想定
        // SS_Callout側で、SleepCancelじゃなかったら NvMReadAll完了待ち
        // SS_Callout側のEntryCalloutで、NvMReadAll開始

#if (SS_MM_USE_ASYNC_ARB == STD_ON)
        // 暫定で、即抜け
        SS_Mm_releasePreRun();
#endif
        break;

    case SS_MM_RUN:
#ifdef ECU_INTG_LWH_GUEST
        if (Ecu_Intg_u4SleepNgFlag[u4cId] == ECU_INTG_u4SLEEP_OK)
        {
            bAwake = FALSE;
        }
        else
        {
            bAwake = TRUE;
        }
        /* 暫定でLWH_Guestの場合はVM間調停完了したら即Sleep */
        bAwakeArb = Ecu_Arb_mainFunction(bAwake);
        if (bAwakeArb == TRUE)
        {
            SS_Mm_requestRun();
        }
#if (SS_MM_USE_ASYNC_ARB == STD_ON)
        else
        {
            SS_Mm_releaseRun();
        }
#endif
#else
        // APPのSleepNGをSSに伝える。スリープ安定待ちを含む。
        Ecu_Intg_convSleepNg();
#endif
        break;

    case SS_MM_POSTRUN:
#if (SS_MM_USE_ASYNC_ARB == STD_ON)
        // 暫定で、即抜け
        SS_Mm_releasePostRun();
#endif

        break;

    default:
        Ecu_Int_performReset();
        break;
    }

    // Tick
    u4TickCntr[u4cId]++;

    // 判定処理後に、SleepNGフラグの定期クリア
    if (u4TickCntr[u4cId] >= ECU_ING_u4SLEEPNG_CLR_PERIOD)
    {
/* @ zantei Sleep NG */
//        Ecu_Intg_u4SleepNgFlag[u4cId] = ECU_INTG_u4SLEEP_OK;
/* @ zantei Sleep NG */
        u4TickCntr[u4cId]             = 0UL;
    }
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC) */

    return E_OK;
}
#endif // (SS_USE_MODE == STD_ON)

void Ecu_Intg_checkAndImmShutdown(void)
{
    boolean bRet;

    bRet = Ecu_IntgHAL_isImmShutdown();

    if (bRet == TRUE)
    {
#if (SS_USE_SLEEP == STD_ON)
        SS_ISeq_sleep();
#elif ((SS_USE_SHUTDOWN == STD_ON) && (SS_USE_UP == STD_ON))
        SS_ISeq_shutdown();
#endif
    }

    return;
}

static Ecu_Intg_LvDINestStackType *Ecu_Intg_selectNestStack(void)
{

    Ecu_Intg_LvDINestStackType *ptNestStack;

#if (SS_USE_CORE_COUNT >= 2u)
    uint32 u4cId;

    u4cId = SS_CpuCore_getCoreID();

    if (u4cId == SS_CPUCORE_u4MASTERCORE)
#endif
    {
        ptNestStack = &(Ecu_Intg_stLDINestStack[0UL]);
    }
#if (SS_USE_CORE_COUNT >= 2u)
    else if (u4cId == SS_CPUCORE_u4SLAVECORE1)
    {
        ptNestStack = &(Ecu_Intg_stLDINestStack[1UL]);
    }
#endif
#if (SS_USE_CORE_COUNT >= 3u)
    else if (u4cId == SS_CPUCORE_u4SLAVECORE2)
    {
        ptNestStack = &(Ecu_Intg_stLDINestStack[2UL]);
    }
#endif
#if (SS_USE_CORE_COUNT >= 4u)
    else if (u4cId == SS_CPUCORE_u4SLAVECORE3)
    {
        ptNestStack = &(Ecu_Intg_stLDINestStack[3UL]);
    }
#endif
#if (SS_USE_CORE_COUNT >= 2u)
    else
    {
        ptNestStack = NULL_PTR;
    }
#endif
    return ptNestStack;
}

Std_ReturnType Ecu_Intg_pushLevelDI(uint8 u1PriorityLevel)
{
    Std_ReturnType u1RetVal;
    uint8          u1LvMaskPrevious;

    Ecu_Intg_LvDINestStackType *ptNestStack;

    ptNestStack = Ecu_Intg_selectNestStack();

    if (ptNestStack->u1Ptr >= ECU_INTG_u1MAX_LVDINEST)
    {
        u1RetVal = E_NOT_OK;
    }
    else
    {
#if (SS_USE_UP == STD_ON)
        if (ptNestStack->u1Ptr == 0UL)
        {
            SuspendOSInterrupts();
        }
#endif
        u1LvMaskPrevious = Ecu_IntgHAL_getIntLevelMask();

        // popするときに意識しなくていいように、ネストスタックは積む。
        ptNestStack->u1STACK[ptNestStack->u1Ptr] = u1LvMaskPrevious;
        ptNestStack->u1Ptr++; // push時は後でインクリメント
        u1RetVal = E_OK;

        // 現在より高い割込み優先レベルが指定されたら、割り込みレベルを更新する
        if (u1PriorityLevel < u1LvMaskPrevious)
        {
            Ecu_IntgHAL_setIntLevelMask(u1PriorityLevel);
        }
    }
    return u1RetVal;
}

Std_ReturnType Ecu_Intg_popLevelEI(void)
{
    Std_ReturnType u1RetVal;
    uint8          u1LvMaskPrevious;

    Ecu_Intg_LvDINestStackType *ptNestStack;

    ptNestStack = Ecu_Intg_selectNestStack();

    if (ptNestStack->u1Ptr == 0UL)
    {
        u1RetVal = E_NOT_OK;
    }
    else
    {
        ptNestStack->u1Ptr--; // pop時は先にデクリメント
        u1LvMaskPrevious = ptNestStack->u1STACK[ptNestStack->u1Ptr];
        u1RetVal         = E_OK;

        Ecu_IntgHAL_setIntLevelMask(u1LvMaskPrevious);

#if (SS_USE_UP == STD_ON)
        if (ptNestStack->u1Ptr == 0UL)
        {
            ResumeOSInterrupts();
        }
#endif
    }
    return u1RetVal;
}

#if (SS_USE_SLEEP == STD_ON)
void Ecu_Intg_checkWakeup(void)
{
    Std_ReturnType         u1Ret;
    Ecu_Intg_BootCauseType u4BootCause;
    boolean                bRet;

    u4BootCause = Ecu_Intg_hasBootCause();

    bRet = Ecu_Intg_isWakeupCallout(u4BootCause);
    if (bRet == TRUE)
    {
        SS_Pm_requestWakeup();
    }

    switch (u4BootCause)
    {
    case ECU_INTG_u4BTCAUSE_WKUP_ANY:
        // その他要因があったので、定常周回に戻る。

        SS_Pm_requestWakeup();

        break;

    case ECU_INTG_u4BTCAUSE_WKUP_TMR:
        // タイマ要因のみなので、再スリープ

        u1Ret = SS_SleepTm_isUp(); // 念のため、タイマのWakeup要因確認
        if (u1Ret == TRUE)
        { // WUFクリアして、requestWakeupしない。
            (void)SS_SleepTm_resetUp();
        }

        break;

    default:
        /* Nothing to do */
        break;
    }

    return;
}
#endif /* (SS_USE_SLEEP == STD_ON) */

#if (SS_USE_SLEEP == STD_ON)
void Ecu_Intg_sleep(uint32 u4ResleepFlag)
{
    uint32         u4AlarmPeriod;
    Std_ReturnType u1Ret;

    SS_CpuCore_entryMasterSection();
    {
        if (u4ResleepFlag == ECU_INTG_u4RESLEEP)
        {
            u4AlarmPeriod = Ecu_Intg_reSleepCallout();
        }
        else
        {
            u4AlarmPeriod = Ecu_Intg_sleepCallout();
        }
        if (u4AlarmPeriod == 0UL)
        {
            SS_SleepTm_stop();
        }
        else
        {
            u1Ret = SS_SleepTm_start(u4AlarmPeriod);
            if (u1Ret != E_OK)
            {
                Ecu_Int_performReset();
            }
        }
    }
    SS_CpuCore_exitMasterSection();
    return;
}
#endif // (SS_USE_SLEEP == STD_ON)

#if ((SS_USE_MODE == STD_ON) && (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC))
void Ecu_Intg_sendSleepNG(void)
{

    uint32 u4cId;

    u4cId = SS_CpuCore_getCoreID();

    Ecu_Intg_u4SleepNgFlag[u4cId] = ECU_INTG_u4SLEEP_NG;

    return;
}
#endif

void Ecu_Intg_performSTReset(Ecu_Intg_STResetType u1Type, uint8 u1Reason)
{
    __DI();

    /* 引数で指定したリセット理由をRAMに格納する。*/
    Ecu_Intg_setSTResetKey(u1Reason);

    /* 引数で指定したリセット方式でリセットを実行する。*/
    /* リセット前ユーザ実装処理 */
    Ecu_Intg_preSTResetCallout(u1Type, u1Reason);

    /* リセット処理 */
    if (u1Type == ECU_INTG_ST_RESET_SOFT)
    {
        Ecu_IntgHAL_performSoftReset();
    }
    else if (u1Type == ECU_INTG_ST_RESET_HARD)
    {
        Ecu_IntgHAL_performHardReset();
    }
    else if (u1Type == ECU_INTG_ST_RESET_BRAM)
    {
        Ecu_IntgHAL_performHardReset();
    }
    else
    {
        Ecu_IntgHAL_performHardReset();
    }

    return;
}

static void Ecu_Intg_setSTResetKey(uint8 u1Reason)
{
    volatile uint8 u1Dummy; /* ダミーリード用 */

    /*リセット理由をRAMに格納する。*/
    if (u1Reason < ECU_INTG_ST_RESET_REASON_NUM)
    {
        Ecu_Intg_u1STResetReason[u1Reason] = ECU_INTG_ST_RESET_KEY_ON;

        u1Dummy = Ecu_Intg_u1STResetReason[u1Reason]; /* dummy read */
        Ecu_Int_syncp();
    }
    else
    {
        Ecu_Intg_u1STResetReason[ECU_INTG_ST_RESET_BY_UNKNOWN] = ECU_INTG_ST_RESET_KEY_ON;

        u1Dummy = Ecu_Intg_u1STResetReason[u1Reason]; /* dummy read */
        Ecu_Int_syncp();
    }

    return;
}

boolean Ecu_Intg_checkSTReset(uint8 u1Reason, boolean bClearFlag)
{

    volatile uint8 u1Dummy; /* ダミーリード用 */
    boolean        bRet;

    bRet = FALSE;
    if (u1Reason < ECU_INTG_ST_RESET_REASON_NUM)
    {
        if (Ecu_Intg_u1STResetReason[u1Reason] == ECU_INTG_ST_RESET_KEY_ON)
        {
            bRet = TRUE;
        }
        if (bClearFlag == TRUE)
        {
            Ecu_Intg_u1STResetReason[u1Reason] = ECU_INTG_ST_RESET_KEY_OFF;

            u1Dummy = Ecu_Intg_u1STResetReason[u1Reason]; /* dummy read */
            Ecu_Int_syncp();
        }
    }

    return bRet;
}
