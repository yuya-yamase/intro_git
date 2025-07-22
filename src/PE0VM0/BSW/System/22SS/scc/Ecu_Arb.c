/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 *【ファイル名】	Ecu_Arb.c
 *【モジュール名】	Arbitration
 *【機能】			下記のサンプル
 *					1. 通常VMの起動状態調停
 *					2. スケジューリングID変更によるVM起動
 *【備考】
 ****************************************************************************/
/*----------------------------------------------------------------------------
 *		ヘッダインクルード
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS.h>
#include <ehvm.h>

#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_Memmap.h>
#include <Ecu_Intg.h>
#include <Ecu_Arb.h>
#include <Ecu_Arb_Cfg.h>
#include <Ecu_Arb_Callout.h>

/*----------------------------------------------------------------------------
 *		Types
 *--------------------------------------------------------------------------*/
typedef uint8 Ecu_Arb_OwnCpuStatusType;

/*----------------------------------------------------------------------------
 *		変数宣言
 *--------------------------------------------------------------------------*/
static Ecu_Arb_OwnCpuStatusType Ecu_Arb_u1OwnCpuStatus;
#if (ECU_MY_VM == VMm)
static boolean Ecu_Arb_bVMxInitializedFlag[ECU_ARB_SLAVE_VM_NUM];
static boolean Ecu_Arb_bVMxSleepOKFlag[ECU_ARB_SLAVE_VM_NUM];
static uint32  Ecu_Arb_u4ReadySleepCount;
static uint32  Ecu_Arb_u4SleepCount;
#endif
#if (ECU_MY_VM == VMx)
static ehvm_uint32_t Ecu_Arb_u4VMmCommand;
#endif

#include <Ecu_Memmap_SdaDisableE_env.h>
/*----------------------------------------------------------------------------
 *		置換シンボル定義
 *--------------------------------------------------------------------------*/
#define ECU_ARB_PEID_0 ((ehvm_core_id_t)0U)

/* スケジューリングID */
#define ECU_ARB_SCHEDULEID_PREPARE ((ehvm_sch_scheduling_id_t)0U) /* 準備中(RUN時以外)スケジューリングID */
#define ECU_ARB_SCHEDULEID_RUN     ((ehvm_sch_scheduling_id_t)0U) /* RUN時用スケジューリングID */

/* Ecu_Arb状態 */
#define ECU_ARB_STATE_INIT   ((Ecu_Arb_OwnCpuStatusType)0U)
#define ECU_ARB_STATE_OPE    ((Ecu_Arb_OwnCpuStatusType)1U)
#define ECU_ARB_STATE_PRPSLP ((Ecu_Arb_OwnCpuStatusType)2U)
#define ECU_ARB_STATE_RDYSLP ((Ecu_Arb_OwnCpuStatusType)3U)
#define ECU_ARB_STATE_SLEEP  ((Ecu_Arb_OwnCpuStatusType)4U)

/* VCC関連 */
#define ECU_SLEEP_OK             ((ehvm_uint32_t)0xAA55AA55U)
#define ECU_SLEEP_NG             ((ehvm_uint32_t)0x55AA55AAU)
#define ECU_SLEEP_INITIALIZED    ((ehvm_uint32_t)0xCC33CC33U)
#define ECU_SLEEP_GO_OPE         ((ehvm_uint32_t)0x33CC33CCU)
#define ECU_SLEEP_READY_SLEEP    ((ehvm_uint32_t)0xA5A5A5A5U)
#define ECU_SLEEP_GO_SLEEP       ((ehvm_uint32_t)0xC3C3C3C3U)
#define ECU_SLEEP_UNKNOWN        ((ehvm_uint32_t)0xFFFFFFFFU)
#define ECU_VCC_SLEEP_STATUS_LEN ((ehvm_uint32_t)4U)

/* 関数置き換え */
#if (ECU_MY_VM == VMm)
#define Ecu_Arb_stateInit   Ecu_Arb_stateInit_VMm
#define Ecu_Arb_stateOpe    Ecu_Arb_stateOpe_VMm
#define Ecu_Arb_stateRdySlp Ecu_Arb_stateRdySlp_VMm
#endif
#if (ECU_MY_VM == VMx)
#define Ecu_Arb_stateInit   Ecu_Arb_stateInit_VMx
#define Ecu_Arb_stateOpe    Ecu_Arb_stateOpe_VMx
#define Ecu_Arb_stateRdySlp Ecu_Arb_stateRdySlp_VMx
#endif

/*----------------------------------------------------------------------------
 *      プロトタイプ宣言
 *--------------------------------------------------------------------------*/
#if (SS_USE_MODE == STD_ON)
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
static void Ecu_Arb_initVariable(void);
static void Ecu_Arb_vccSend(ehvm_uint32_t u4TransMessage);
static void Ecu_Arb_stateInit(void);
static void Ecu_Arb_stateOpe(boolean bAwake);
static void Ecu_Arb_stateRdySlp(boolean bAwake);
#if (ECU_MY_VM == VMm)
static void    Ecu_Arb_getVMxStatus(void);
static void    Ecu_Arb_statePrpSlp_VMm(boolean bAwake);
static boolean Ecu_Arb_stateSleep_VMm(void);
static boolean Ecu_Arb_isVMxAllSleep(void);
#endif
#if (ECU_MY_VM == VMx)
static void Ecu_Arb_getVMmCommand(void);
#endif

/*----------------------------------------------------------------------------
 *		プログラム
 *--------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------
 * [Format]     void Ecu_Arb_init(void)
 * [Function]   調停対象の初期化処理
 * [Arguments]  None
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
void Ecu_Arb_init(void)
{
    /* 変数初期化 */
    Ecu_Arb_initVariable();

    /* 自身のVCC受信情報をクリア */
    (void)ehvm_vcc_clear();

#if (ECU_MY_VM == VMm)
    /* マスターコアのスケジューリングIDを切り替える */
    (void)ehvm_sch_set_schedule_table(ECU_ARB_PEID_0, ECU_ARB_SCHEDULEID_RUN);

    /* 通常VMの起動抑制を解除 */
    (void)ehvm_vmm_disable_suppression();

    /* 一般VMの起動 */
#endif

    return;
}

/**---------------------------------------------------------------------------
 * [Format]     static void Ecu_Arb_initVariable(void)
 * [Function]   調停用変数の初期化
 * [Arguments]  None
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
static void Ecu_Arb_initVariable(void)
{
#if (ECU_MY_VM == VMm)
    uint32 u1VmNum;
    Ecu_Arb_u4ReadySleepCount = 0UL;
    Ecu_Arb_u4SleepCount      = 0UL;
    for (u1VmNum = 0U; u1VmNum < ECU_ARB_SLAVE_VM_NUM; u1VmNum++)
    {
        Ecu_Arb_bVMxInitializedFlag[u1VmNum] = FALSE;
        Ecu_Arb_bVMxSleepOKFlag[u1VmNum]     = FALSE;
    }
#endif
#if (ECU_MY_VM == VMx)
    Ecu_Arb_u4VMmCommand = ECU_SLEEP_UNKNOWN;
#endif
    /* 共通 */
    Ecu_Arb_u1OwnCpuStatus = ECU_ARB_STATE_INIT;
}

/**---------------------------------------------------------------------------
 * [Format]     boolean Ecu_Arb_mainFunction(boolean bAwake)
 * [Function]   調停メイン処理
 * [Arguments]  自VMアウェイク要因有無
 * [Return]     Arbアウェイク要因有無
 * [Notes]      None
 *--------------------------------------------------------------------------*/
boolean Ecu_Arb_mainFunction(boolean bAwake)
{
    boolean bRet;

    bRet = TRUE;

    switch (Ecu_Arb_u1OwnCpuStatus)
    {
    case ECU_ARB_STATE_INIT:
        Ecu_Arb_stateInit();
        break;
    case ECU_ARB_STATE_OPE:
        Ecu_Arb_stateOpe(bAwake);
        break;
#if (ECU_MY_VM == VMm)
    case ECU_ARB_STATE_PRPSLP:
        Ecu_Arb_statePrpSlp_VMm(bAwake);
        break;
#endif
    case ECU_ARB_STATE_RDYSLP:
        Ecu_Arb_stateRdySlp(bAwake);
        break;
    case ECU_ARB_STATE_SLEEP:
#if (ECU_MY_VM == VMm)
        bRet = Ecu_Arb_stateSleep_VMm();
#endif
#if (ECU_MY_VM == VMx)
        bRet = FALSE;
#endif
        break;
    default:
        Ecu_Intg_performSTReset(ECU_INTG_ST_RESET_HARD, ECU_INTG_ST_RESET_BY_ECU_ARB);
        break;
    }

    return bRet;
}

/**---------------------------------------------------------------------------
 * [Format]     static void Ecu_Arb_vccSend(ehvm_uint32_t u4TransMessage)
 * [Function]   VCC送信処理
 * [Arguments]  送信メッセージ
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
static void Ecu_Arb_vccSend(ehvm_uint32_t u4TransMessage)
{
    ehvm_uint32_t u4TransmitBuf;

    u4TransmitBuf = u4TransMessage;

    (void)ehvm_vcc_transmit(ECU_MY_VCCID, &u4TransmitBuf, ECU_VCC_SLEEP_STATUS_LEN);

    return;
}

#if (ECU_MY_VM == VMm)
/**---------------------------------------------------------------------------
 * [Format]     static void Ecu_Arb_stateInit_VMm(void)
 * [Function]   Arb Init処理
 * [Arguments]  None
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
static void Ecu_Arb_stateInit_VMm(void)
{
    boolean bInitComplete;
    uint8   u1VmNum;

    bInitComplete = TRUE;

    /* 調停ステータス更新 */
    Ecu_Arb_getVMxStatus();

    /* Init完了判定 */
    for (u1VmNum = 0U; u1VmNum < ECU_ARB_SLAVE_VM_NUM; u1VmNum++)
    {
        bInitComplete &= Ecu_Arb_bVMxInitializedFlag[u1VmNum];
    }

    /* Init完了時にExit処理 */
    if (bInitComplete == TRUE)
    {
        Ecu_Arb_u1OwnCpuStatus = ECU_ARB_STATE_OPE;
        Ecu_Arb_exitInitCallout();
        Ecu_Arb_vccSend(ECU_SLEEP_GO_OPE);
    }

    return;
}

/**---------------------------------------------------------------------------
 * [Format]     static void Ecu_Arb_stateOpe_VMm(boolean bAwake)
 * [Function]   Arb Ope処理
 * [Arguments]  自VMアウェイク有無
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
static void Ecu_Arb_stateOpe_VMm(boolean bAwake)
{
    boolean bSleepOK;
    uint8   u1VmNum;

    if ( bAwake == FALSE)
    {
        bSleepOK = TRUE;
    }
    else
    {
        bSleepOK = FALSE;
    }

    /* 調停ステータス更新 */
    Ecu_Arb_getVMxStatus();

    /* SleepOK判定 */
    for (u1VmNum = 0U; u1VmNum < ECU_ARB_SLAVE_VM_NUM; u1VmNum++)
    {
        bSleepOK &= Ecu_Arb_bVMxSleepOKFlag[u1VmNum];
    }

    /* 全VMスリープOKならPRPSLPに移行 */
    if (bSleepOK == TRUE)
    {
        Ecu_Arb_u1OwnCpuStatus = ECU_ARB_STATE_PRPSLP;
        Ecu_Arb_entryPrpSlpCallout();
    }

    return;
}
/**---------------------------------------------------------------------------
 * [Format]     static void Ecu_Arb_statePrpSlp_VMm(boolean bAwake)
 * [Function]   Arb PrpSlp処理
 * [Arguments]  自VMアウェイク有無
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
static void Ecu_Arb_statePrpSlp_VMm(boolean bAwake)
{
    boolean bSleepOK;
    boolean bPrpSlpComplete;
    uint8   u1VmNum;

    if ( bAwake == FALSE)
    {
        bSleepOK = TRUE;
    }
    else
    {
        bSleepOK = FALSE;
    }

    /* 調停ステータス更新 */
    Ecu_Arb_getVMxStatus();

    /* SleepOK判定 */
    for (u1VmNum = 0U; u1VmNum < ECU_ARB_SLAVE_VM_NUM; u1VmNum++)
    {
        bSleepOK &= Ecu_Arb_bVMxSleepOKFlag[u1VmNum];
    }

    /* SleepNGの場合、OPEに移行 */
    if (bSleepOK == FALSE)
    {
        Ecu_Arb_u1OwnCpuStatus = ECU_ARB_STATE_OPE;
        Ecu_Arb_stopPrpSlpCallout();
    }
    /* SleepOKの場合 */
    else
    {
        /* スリープ前処理完了確認 */
        bPrpSlpComplete = Ecu_Arb_prpSlpCallout();

        /* スリープ前処理完了の場合、Exit to RDYSLP処理 */
        if (bPrpSlpComplete == TRUE)
        {
            Ecu_Arb_u1OwnCpuStatus = ECU_ARB_STATE_RDYSLP;
            Ecu_Arb_vccSend(ECU_SLEEP_READY_SLEEP);
            Ecu_Arb_awakeMskCallout();
        }
    }

    return;
}

/**---------------------------------------------------------------------------
 * [Format]     static void Ecu_Arb_stateRdySlp_VMm(boolean bAwake)
 * [Function]   Arb RdySlp処理
 * [Arguments]  自VMアウェイク有無
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
static void Ecu_Arb_stateRdySlp_VMm(boolean bAwake)
{

    /* READYSLEEPカウント待ち */
    if (Ecu_Arb_u4ReadySleepCount < ECU_ARB_READY_SLEEP_PERIOD)
    {
        Ecu_Arb_u4ReadySleepCount++;
    }
    else
    /* READYSLEEPカウント待ち完了後、GO_SLEEPを送信してSLEEP状態に遷移 */
    {
        Ecu_Arb_vccSend(ECU_SLEEP_GO_SLEEP);
        (void)ehvm_vmm_enable_suppression();
        Ecu_Arb_u1OwnCpuStatus = ECU_ARB_STATE_SLEEP;
    }

    return;
}

/**---------------------------------------------------------------------------
 * [Format]     static boolean Ecu_Arb_stateSleep_VMm(void)
 * [Function]   Arb Sleep処理
 * [Arguments]  None
 * [Return]     Arbアウェイク要因有無
 * [Notes]      None
 *--------------------------------------------------------------------------*/
static boolean Ecu_Arb_stateSleep_VMm(void)
{
    boolean bSleepOK;
    boolean bAwake;

    bSleepOK = Ecu_Arb_isVMxAllSleep();

    if (bSleepOK == TRUE)
    {
        bAwake = FALSE;
    }
    else
    {
        if (Ecu_Arb_u4SleepCount < ECU_ARB_SLEEP_PERIOD)
        {
            Ecu_Arb_u4SleepCount++;
            bAwake = TRUE;
        }
        else
        {
            Ecu_Intg_performSTReset(ECU_INTG_ST_RESET_HARD, ECU_INTG_ST_RESET_BY_ECU_ARB);
        }
    }

    return (bAwake);
}

/**---------------------------------------------------------------------------
 * [Format]     static void Ecu_Arb_getVMxStatus(void)
 * [Function]   VMxの状態取得
 * [Arguments]  None
 * [Return]     None
 * [Notes]      管理VM→一般VMのVCC_IDは1から連番で設定すること
 *--------------------------------------------------------------------------*/
static void Ecu_Arb_getVMxStatus(void)
{
    ehvm_uint32_t     u4ReceiveBuf;
    ehvm_uint32_t     u4ReceiveDataBytes;
    ehvm_std_return_t u1Ret;
    uint8             u1VmNum;

    for (u1VmNum = 0U; u1VmNum < ECU_ARB_SLAVE_VM_NUM; u1VmNum++)
    {
        u4ReceiveBuf = (ehvm_uint32_t)0U;
        u1Ret        = ehvm_vcc_receive((ehvm_uint32_t)(u1VmNum + 1U), &u4ReceiveBuf, ECU_VCC_SLEEP_STATUS_LEN, &u4ReceiveDataBytes);
        if (u1Ret == E_EHVM_OK)
        {
            if (u4ReceiveBuf == ECU_SLEEP_INITIALIZED)
            {
                Ecu_Arb_bVMxInitializedFlag[u1VmNum] = TRUE;
            }
            else if (u4ReceiveBuf == ECU_SLEEP_NG)
            {
                Ecu_Arb_bVMxSleepOKFlag[u1VmNum] = FALSE;
            }
            else if (u4ReceiveBuf == ECU_SLEEP_OK)
            {
                Ecu_Arb_bVMxSleepOKFlag[u1VmNum] = TRUE;
            }
            else
            {
                /* Nothing to do */
            }
        }
    }
    return;
}

/**---------------------------------------------------------------------------
 * [Format]     static boolean Ecu_Arb_isVMxAllSleep(void)
 * [Function]   一般VMのスリープ確認
 * [Arguments]  None
 * [Return]     全一般VMスリープ完了:TRUE、それ以外:FALSE
 * [Notes]      None
 *--------------------------------------------------------------------------*/
static boolean Ecu_Arb_isVMxAllSleep(void)
{
    ehvm_status_check_t u4VmStatusCheck;
    boolean             bRet;

    /* VMのスリープ完了確認 */
    (void)ehvm_vmm_get_all_other_vm_status(&u4VmStatusCheck);
    if (u4VmStatusCheck == EHVM_VMM_STATUS_ALL_VM_STOP)
    {
        bRet = TRUE;
    }
    else
    {
        bRet = FALSE;
    }

    return bRet;
}

#endif /* ECU_MY_VM == VMm */

#if (ECU_MY_VM == VMx)
/**---------------------------------------------------------------------------
 * [Format]     static void Ecu_Arb_stateInit_VMx(void)
 * [Function]   Arb Init処理
 * [Arguments]  None
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
static void Ecu_Arb_stateInit_VMx(void)
{
    /* 調停ステータス更新 */
    Ecu_Arb_getVMmCommand();

    /* 管理VMにINITIALIZE通知 */
    Ecu_Arb_vccSend(ECU_SLEEP_INITIALIZED);

    /* GoOpe指示があったらExit処理 */
    if (Ecu_Arb_u4VMmCommand == ECU_SLEEP_GO_OPE)
    {
        Ecu_Arb_u1OwnCpuStatus = ECU_ARB_STATE_OPE;
    }

    return;
}

/**---------------------------------------------------------------------------
 * [Format]     static void Ecu_Arb_stateOpe_VMx(boolean bAwake)
 * [Function]   Arb Ope処理
 * [Arguments]  自VMアウェイク有無
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
static void Ecu_Arb_stateOpe_VMx(boolean bAwake)
{
    /* 調停ステータス更新 */
    Ecu_Arb_getVMmCommand();

    /* READY_SLEEP指示があればExit処理 */
    if (Ecu_Arb_u4VMmCommand == ECU_SLEEP_READY_SLEEP)
    {
        Ecu_Arb_u1OwnCpuStatus = ECU_ARB_STATE_RDYSLP;
        Ecu_Arb_awakeMskCallout();
    }
    else
    {
        /* 自VMのアウェイクがあればスリープNG送信 */
        if (bAwake == TRUE)
        {
            Ecu_Arb_vccSend(ECU_SLEEP_NG);
        }
        else
        /* 自VMのアウェイクが無い場合 */
        {
            /* スリープOK送信 */
            Ecu_Arb_vccSend(ECU_SLEEP_OK);
        }
    }

    return;
}

/**---------------------------------------------------------------------------
 * [Format]     static void Ecu_Arb_stateRdySlp_VMx(boolean bAwake)
 * [Function]   Arb RdySlp処理
 * [Arguments]  自VMアウェイク有無
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
static void Ecu_Arb_stateRdySlp_VMx(boolean bAwake)
{
    /* 調停ステータス更新 */
    Ecu_Arb_getVMmCommand();

    if (Ecu_Arb_u4VMmCommand == ECU_SLEEP_GO_SLEEP)
    /* GO_SLEEP指示があればSLEEP状態に遷移 */
    {
        Ecu_Arb_u1OwnCpuStatus = ECU_ARB_STATE_SLEEP;
    }
    else
    /* 遷移指示が無い場合 */
    {
        /* Nothing to do */
    }

    return;
}

/**---------------------------------------------------------------------------
 * [Format]     static void Ecu_Arb_getVMmCommand(void)
 * [Function]   VMmからの指示取得
 * [Arguments]  None
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
static void Ecu_Arb_getVMmCommand(void)
{
    ehvm_uint32_t     u4ReceiveBuf;
    ehvm_uint32_t     u4ReceiveDataBytes;
    ehvm_std_return_t u1Ret;

    u4ReceiveBuf = (ehvm_uint32_t)0U;
    u1Ret        = ehvm_vcc_receive(ECU_ARB_MASTER_VCCID, &u4ReceiveBuf, ECU_VCC_SLEEP_STATUS_LEN, &u4ReceiveDataBytes);
    if (u1Ret == E_EHVM_OK)
    {
        Ecu_Arb_u4VMmCommand = u4ReceiveBuf;
    }
    return;
}
#endif /* ECU_MY_VM == VMx */

/* vv Wfdで置き換え予定 vv */
/**---------------------------------------------------------------------------
 * [Format]     void Ecu_Arb_clearWkUpFctr(void)
 * [Function]   自VMのウェイクアップ要因クリア
 * [Arguments]  None
 * [Return]     None
 * [Notes]      None
 *--------------------------------------------------------------------------*/
void Ecu_Arb_clearWkUpFctr(void)
{
    uint32 u4BitNow;
    uint32 u4ValWUF_A0;
    uint32 u4ValWUF_A1;
    uint32 u4ValWUF_A2;

    u4ValWUF_A0 = VAL_u4WUF0_A0;
    u4ValWUF_A1 = VAL_u4WUF0_A1;
    u4ValWUF_A2 = VAL_u4WUF0_A2;

    /* VMに割り付けられらウェイクアップ要因をクリア */
    for (u4BitNow = 0UL; u4BitNow < 32UL; u4BitNow++)
    {
        if ((u4ValWUF_A0 & 1UL) != 0UL)
        {
            (void)ehvm_vmm_clear_wakeup_factor((ehvm_wakeup_factor_num_t)EHVM_WAKEUP_FACTOR_A0, (ehvm_wakeup_factor_bit_t)u4BitNow);
        }
        u4ValWUF_A0 = u4ValWUF_A0 >> 1UL;
    }
    for (u4BitNow = 0UL; u4BitNow < 32UL; u4BitNow++)
    {
        if ((u4ValWUF_A1 & 1UL) != 0UL)
        {
            (void)ehvm_vmm_clear_wakeup_factor((ehvm_wakeup_factor_num_t)EHVM_WAKEUP_FACTOR_A1, (ehvm_wakeup_factor_bit_t)u4BitNow);
        }
        u4ValWUF_A1 = u4ValWUF_A1 >> 1UL;
    }

    for (u4BitNow = 0UL; u4BitNow < 32UL; u4BitNow++)
    {
        if ((u4ValWUF_A2 & 1UL) != 0UL)
        {
            (void)ehvm_vmm_clear_wakeup_factor((ehvm_wakeup_factor_num_t)EHVM_WAKEUP_FACTOR_A2, (ehvm_wakeup_factor_bit_t)u4BitNow);
        }
        u4ValWUF_A2 = u4ValWUF_A2 >> 1UL;
    }

    return;
}
#if (ECU_MY_VM == VMm)
/**---------------------------------------------------------------------------
 * [Format]     void Ecu_Arb_wkUpFctrInit(void)
 * [Function]   ウェイクアップ要因の有効化/セット ついでに、TAUJ3_0のWUF有効化
 * [Arguments]  None
 * [Return]     None
 * [Notes]      管理VMからのみコール
 *--------------------------------------------------------------------------*/
void Ecu_Arb_wkUpFctrInit(void)
{
    (void)ehvm_vmm_enable_wakeup_factor((ehvm_wakeup_factor_num_t)EHVM_WAKEUP_FACTOR_A0, (ehvm_wakeup_factor_bit_t)2u);
    (void)ehvm_vmm_enable_wakeup_factor((ehvm_wakeup_factor_num_t)EHVM_WAKEUP_FACTOR_A0, (ehvm_wakeup_factor_bit_t)3u);
    (void)ehvm_vmm_enable_wakeup_factor((ehvm_wakeup_factor_num_t)EHVM_WAKEUP_FACTOR_A0, (ehvm_wakeup_factor_bit_t)4u);
    (void)ehvm_vmm_enable_wakeup_factor((ehvm_wakeup_factor_num_t)EHVM_WAKEUP_FACTOR_A2, (ehvm_wakeup_factor_bit_t)7u);
    (void)ehvm_vmm_set_wakeup_factor((ehvm_wakeup_factor_num_t)EHVM_WAKEUP_FACTOR_A0, (ehvm_wakeup_factor_bit_t)2u);
    (void)ehvm_vmm_set_wakeup_factor((ehvm_wakeup_factor_num_t)EHVM_WAKEUP_FACTOR_A0, (ehvm_wakeup_factor_bit_t)3u);
    (void)ehvm_vmm_set_wakeup_factor((ehvm_wakeup_factor_num_t)EHVM_WAKEUP_FACTOR_A0, (ehvm_wakeup_factor_bit_t)4u);

    return;
}
#endif
/* ^^ Wfdで置き換え予定 ^^ */

#endif /* SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC */
#endif /* SS_USE_MODE == STD_ON */
