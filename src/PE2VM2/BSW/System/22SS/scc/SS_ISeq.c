/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_ISeq.c
 * [Module]			Initialize
 * [Function]		Initialize at updating status
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <SS_TYPE.h>
#include <SS_Internal.h>
#if (SS_USE_UP == STD_ON)
#include <Os.h>
#endif
#include <EcuM.h>
#if (SS_INTG_RTE == STD_ON)
#include <Rte_Main.h>
#endif /* (SS_INTG_RTE == STD_ON) */

#include <SS_MemmapSdaDisableB_Env.h>
#include <SS_Memmap_Env.h>

#include <SS_MemmapSdaDisableE_Env.h>

#include <SS_MemmapSdaSelectB_Env.h>
#include <SS_ISeq.h>
#include <SS_ISeq_Callout.h>
#include <SS_MCALISeq.h>
#include <SS_Error.h>
#include <SS_ResetM.h>
#include <SS_CpuCore.h>
#include <SS_Error_Callout.h>
#include <SS_Memory.h>
#include <SS_Clock.h>
#if (SS_USE_UP == STD_ON)
#include <SS_State.h>
#include <SS_Safety.h>
#endif /* (SS_USE_UP == STD_ON) */


/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/

/* バリア同期用 */
#define SS_ISEQ_u4INITVAL       (0x00000001UL)
#define SS_ISEQ_u4SHIFTCOUNTVAL (16UL)
#define SS_ISEQ_u4SHIFTMASKVAL  (0xFFFF0000UL)

/* バリア同期変数の初期化待ち用 */
#define SS_ISEQ_u4CHECKVAL1   (0xAA55AA55UL)
#define SS_ISEQ_u4CHECKVAL2   (0x55AA55AAUL)
#define SS_ISEQ_u4WAIT_PASSED (0x00000001UL)

/* メインスタックサイズ */
#define SS_ISEQ_u4MAINSTACKSIZE_0 \
    ((uint32)(SS_STACKSIZE_0 - SS_u4PRIMARYSTACKSIZE_0))
#define SS_ISEQ_u4MAINSTACKSIZE_1 \
    ((uint32)(SS_STACKSIZE_1 - SS_u4PRIMARYSTACKSIZE_1))
#define SS_ISEQ_u4MAINSTACKSIZE_2 \
    ((uint32)(SS_STACKSIZE_2 - SS_u4PRIMARYSTACKSIZE_2))
#define SS_ISEQ_u4MAINSTACKSIZE_3 \
    ((uint32)(SS_STACKSIZE_3 - SS_u4PRIMARYSTACKSIZE_3))

/*----------------------------------------------------------------------------
 *		Prototypes
 *--------------------------------------------------------------------------*/
static void SS_ISeq_initBSync(void);
static void SS_ISeq_bSync(uint16 u2_syncID);
#if (SS_USE_CORE_COUNT >= 2u)
static void SS_ISeq_initSyncCores(void);
static void SS_ISeq_waitSyncCoreInit(void);
#endif

#if ((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON))
static void           SS_ISeq_clearUpReq(void);
static SS_RequestType SS_ISeq_getUpReq(void);
#endif

#if ((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON))
static void SS_ISeq_transit(void);
#endif

/*----------------------------------------------------------------------------
 *		Structures
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Constant Variables
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Variables
 *--------------------------------------------------------------------------*/

/* バリア同期変数の初期化待ち用 */
#if (SS_USE_CORE_COUNT >= 2u)
static volatile uint32 SS_ISeq_u4MasterInitComplete;
static volatile uint32 SS_ISeq_u4InitWaitPass_1;
#endif
#if (SS_USE_CORE_COUNT >= 3u)
static volatile uint32 SS_ISeq_u4InitWaitPass_2;
#endif
#if (SS_USE_CORE_COUNT >= 4u)
static volatile uint32 SS_ISeq_u4InitWaitPass_3;
#endif

/* バリア同期用とマスターコア初期化待ち用 */
#if (SS_USE_CORE_COUNT >= 2u)
volatile uint32 SS_ISeq_u4SyncCheck_1;
#endif
#if (SS_USE_CORE_COUNT >= 3u)
volatile uint32 SS_ISeq_u4SyncCheck_2;
#endif
#if (SS_USE_CORE_COUNT >= 4u)
volatile uint32 SS_ISeq_u4SyncCheck_3;
#endif

/* UP Phaseにとどまる要求 */
#if ((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON))
static SS_RequestType SS_ISeq_u4UpReq;
#endif

#if (SS_USE_SLEEP == STD_ON)
static SS_RequestType SS_ISeq_u4WakeupRequest;
#endif /* (SS_USE_SLEEP == STD_ON) */

/* ブート要因 */
static SS_BootType SS_ISeq_u4BootSource;

#include <SS_MemmapSdaSelectE_Env.h>
/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------
 * [Format]		void SS_ISeq_initBSync(void);
 * [Function]	バリア同期初期化（コア間タイミング同期、SS内部エラー通知、マルチコア間同期リセット）
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
static void SS_ISeq_initBSync(void)
{
#if (SS_USE_CORE_COUNT >= 2u)
    SS_ISeq_initSyncCores();
#endif

    SS_CpuCore_entryMasterSection();
    {
        SS_Error_init();
#if (SS_USE_CORE_COUNT >= 2u)
        SS_ResetM_init();
#endif
    }
    SS_CpuCore_exitMasterSection();

    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_ISeq_stupBoot(void)
 * [Function]	スタートアップ直後の初期化処理
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_ISeq_stupBoot(SS_BootType u4BootSource)
{
    
#if (SS_USE_CORE_COUNT >= 2u)
    SS_CoreIdType u4_CoreId;

    u4_CoreId = SS_CpuCore_getCoreID();
    if (u4_CoreId != SS_CPUCORE_u4MASTERCORE)
    {
        SS_ISeq_initBSync();
    }
#endif

    SS_CpuCore_entryMasterSection();
    {

        /* ブート要因の初期化とRAMチェック */
        SS_ISeq_u4BootSource = u4BootSource;
        SS_Memory_writeScan(&SS_ISeq_u4BootSource, sizeof(SS_BootType));
    }
    SS_CpuCore_exitMasterSection();

    
    SS_Pm_preOsInitCallout(SS_ISeq_u4BootSource);
    

    SS_CpuCore_entryMasterSection();
    {

        SS_MCALISeq_initMcu();

#if (SS_USE_SLEEP == STD_ON)
        if (u4BootSource == SS_PM_BOOT_WUP)
        {
            SS_ISeq_checkWakeupAndReSleep();
        }
#endif
    }
    SS_CpuCore_exitMasterSection();

    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_DriverInitZero(void)
 * [Function]	スタートアップ・ウェイクアップ時初期化 (InitBlock0)
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Pm_DriverInitZero(void)
{
    
    SS_Pm_preClockUpCallout(SS_ISeq_u4BootSource);
    

    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_DriverInitOne(void)
 * [Function]	スタートアップ・ウェイクアップ時初期化 (InitBlock1)
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
void SS_Pm_DriverInitOne(void)
{

    

    /* SS_TP_REGCHK_BEFORE_CLOCKUP */
    SS_CpuCore_entryMasterSection();
    {
        SS_Clock_up();

        SS_ISeq_initBSync();
    }
    SS_CpuCore_exitMasterSection();
    /* SS_TP_REGCHK_AFTER_CLOCKUP */

    SS_ISeq_bSync(SS_ISEQ_u2SID_ISEQ_INITONE_A);

    
    
    {
#if (SS_USE_CORE_COUNT >= 2u)
        SS_CoreIdType u4_CoreId;

        u4_CoreId = SS_CpuCore_getCoreID();
        if (u4_CoreId == SS_CPUCORE_u4MASTERCORE)
        {
#endif
            (void)SS_Memory_set(SS_ptSTACKADDR_0, (uint32)SS_STACKINITVAL, SS_ISEQ_u4MAINSTACKSIZE_0);
#if (SS_USE_CORE_COUNT >= 2u)
        }
        else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE1)
        {
            (void)SS_Memory_set(SS_ptSTACKADDR_1, (uint32)SS_STACKINITVAL, SS_ISEQ_u4MAINSTACKSIZE_1);
        }
#if (SS_USE_CORE_COUNT >= 3u)
        else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE2)
        {
            (void)SS_Memory_set(SS_ptSTACKADDR_2, (uint32)SS_STACKINITVAL, SS_ISEQ_u4MAINSTACKSIZE_2);
        }
#if (SS_USE_CORE_COUNT >= 4u)
        else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE3)
        {
            (void)SS_Memory_set(SS_ptSTACKADDR_3, (uint32)SS_STACKINITVAL, SS_ISEQ_u4MAINSTACKSIZE_3);
        }
#endif
#endif
        else
        {
            /* Nothing to do */
        }
#endif
    }
    
    

    SS_ISeq_bSync(SS_ISEQ_u2SID_ISEQ_STUPBOOT_C);
    
    SS_Pm_postOsInitCallout(SS_ISeq_u4BootSource);
    
    SS_ISeq_bSync(SS_ISEQ_u2SID_ISEQ_STUPBOOT_D);

#if (SS_USE_UP == STD_ON)
    SS_MCALISeq_initOs();
#endif

    SS_ISeq_bSync(SS_ISEQ_u2SID_ISEQ_INITONE_D);
    
    SS_Pm_postClockUpCallout(SS_ISeq_u4BootSource);
    
    SS_ISeq_bSync(SS_ISEQ_u2SID_ISEQ_INITONE_E);

#if (SS_USE_UP == STD_ON)
    SS_SafetyM_init();
#endif /* (SS_USE_UP == STD_ON) */
    
    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_Pm_postStartOS(void)
 * [Function]	スタートアップ・ウェイクアップ時初期化 (OS起動後)
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_UP == STD_ON)
void SS_Pm_postStartOS(void)
{
    
    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_POSTOS_A);
    SS_Pm_DisableInterruptsCallout(SS_PM_u4REQSRC_INIT);
    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_POSTOS_B);

    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_POSTOS_F);
    
    SS_Pm_postStartOSCallout(SS_ISeq_u4BootSource);
    
    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_POSTOS_G);

    SS_Pm_EnableInterruptsCallout(SS_PM_u4REQSRC_INIT);

    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_POSTOS_H);

    
    EcuM_StartupTwo();

#if (SS_INTG_RTE == STD_ON)
    {
        Std_ReturnType u1_ResultRteStart;
        
        u1_ResultRteStart = Rte_Start();
        
        if (u1_ResultRteStart != RTE_E_OK)
        {
            SS_Error_notify(SS_ERROR_SCHEDULER);
        }
    }
#endif /* (SS_INTG_RTE == STD_ON) */

    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_POSTOS_I);
    
    SS_Pm_postRteStartCallout(SS_ISeq_u4BootSource);
    
    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_POSTOS_J);

    SS_CpuCore_entryMasterSection();
    {
        SS_CpuCore_clearResetFactor();
    }
    SS_CpuCore_exitMasterSection();

#if (SS_USE_MODE == STD_ON)
    SS_State_init(SS_ISeq_u4BootSource);
#else
    SS_ISeq_clearUpReq();
#endif

    return;
}
#endif /* (SS_USE_UP == STD_ON) */

/**---------------------------------------------------------------------------
 * [Format]		void SS_ISeq_sleep(void)
 * [Function]	スリープ前設定
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_SLEEP == STD_ON)

void SS_ISeq_sleep(void)
{

    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_SLEEP_A);
    
#if (SS_USE_UP == STD_ON)
    SS_Pm_sleepCallout();
#endif /* (SS_USE_UP == STD_ON) */
    
    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_SLEEP_B);

#if 0u /* for future extention */
    SS_MCALISeq_initBeforeSleep();
    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_SLEEP_C);
#endif

    SS_CpuCore_entryMasterSection();
    {
        /* TPcsw_SS_ISeq_sleep_if0 */
        SS_MCALISeq_goStandby();
        /* TPcsw_SS_ISeq_sleep_endif */
    }
    SS_CpuCore_exitMasterSection();

    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_SLEEP_C);

    /* 上の行で処理は終わるはずで、ここまで来たら異常扱い */
    SS_Error_notify(SS_ERROR_SLEEP);
}

#endif /* (SS_USE_SLEEP == STD_ON) */

/**---------------------------------------------------------------------------
 * [Format]		static void SS_ISeq_initSyncCores(void)
 * [Function]	コア間バリア同期の初期化
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_CORE_COUNT >= 2u)
static void SS_ISeq_initSyncCores(void)
{
    SS_CpuCore_entryMasterSection();
    {
        /* バリア同期用変数の初期化＆RAM固着チェック(スタートアップ時のみ)	*/
        /* ・固着検出時は即リセット										 */

        SS_ISeq_u4SyncCheck_1 = SS_ISEQ_u4INITVAL;
        SS_Memory_writeScan(&SS_ISeq_u4SyncCheck_1, sizeof(uint32));

#if (SS_USE_CORE_COUNT >= 3u)
        SS_ISeq_u4SyncCheck_2 = SS_ISEQ_u4INITVAL;
        SS_Memory_writeScan(&SS_ISeq_u4SyncCheck_2, sizeof(uint32));
#endif /* SS_USE_CORE_COUNT >= 3u */

#if (SS_USE_CORE_COUNT >= 4u)
        SS_ISeq_u4SyncCheck_3 = SS_ISEQ_u4INITVAL;
        SS_Memory_writeScan(&SS_ISeq_u4SyncCheck_3, sizeof(uint32));
#endif /* SS_USE_CORE_COUNT >= 4u */
    }
    SS_CpuCore_exitMasterSection();

    /* 初期化が終わるまでスレーブコアが待つ */
    SS_ISeq_waitSyncCoreInit();

    return;
}
#endif /* SS_USE_CORE_COUNT >= 2u */

/**---------------------------------------------------------------------------
 * [Format]		static void SS_ISeq_waitSyncCoreInit(void)
 * [Function]	Wait until initialization of variable for SyncCore is complete
 * [Arguments]	None
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_CORE_COUNT >= 2u)
static void SS_ISeq_waitSyncCoreInit(void)
{
    volatile uint32 u4_DummyRead;
    SS_CoreIdType   u4_CoreId;

    u4_CoreId = SS_CpuCore_getCoreID();

    /* マスターコア */
    if (u4_CoreId == SS_CPUCORE_u4MASTERCORE)
    {

        SS_ISeq_u4MasterInitComplete = SS_ISEQ_u4CHECKVAL1;
        u4_DummyRead                 = SS_ISeq_u4MasterInitComplete; /* RAM固着の場合、ECCエラー */

        SS_ISeq_u4InitWaitPass_1 = SS_ISEQ_u4CHECKVAL1;
        u4_DummyRead             = SS_ISeq_u4InitWaitPass_1; /* RAM固着の場合、ECCエラー */
        SS_ISeq_u4InitWaitPass_1 = SS_ISEQ_u4CHECKVAL2;

#if (SS_USE_CORE_COUNT >= 3u)
        SS_ISeq_u4InitWaitPass_2 = SS_ISEQ_u4CHECKVAL1;
        u4_DummyRead             = SS_ISeq_u4InitWaitPass_2; /* RAM固着の場合、ECCエラー */
        SS_ISeq_u4InitWaitPass_2 = SS_ISEQ_u4CHECKVAL2;
#endif /* SS_USE_CORE_COUNT >= 3u */

#if (SS_USE_CORE_COUNT >= 4u)
        SS_ISeq_u4InitWaitPass_3 = SS_ISEQ_u4CHECKVAL1;
        u4_DummyRead             = SS_ISeq_u4InitWaitPass_3; /* RAM固着の場合、ECCエラー */
        SS_ISeq_u4InitWaitPass_3 = SS_ISEQ_u4CHECKVAL2;
#endif /* SS_USE_CORE_COUNT >= 4u */

        /* 全スレーブコアが待ち処理を抜けるまで待つ */
        /*  ・待ち処理の判定文でSS_ISeq_u4InitWaitPass_#のRAMチェック(パターン2) */
        while (1)
        {
            if (SS_ISeq_u4InitWaitPass_1 == SS_ISEQ_u4WAIT_PASSED)
            {
#if (SS_USE_CORE_COUNT >= 3u)
                if (SS_ISeq_u4InitWaitPass_2 == SS_ISEQ_u4WAIT_PASSED)
#endif
                {
#if (SS_USE_CORE_COUNT >= 4u)
                    if (SS_ISeq_u4InitWaitPass_3 == SS_ISEQ_u4WAIT_PASSED)
#endif
                    {
                        break;
                    }
                }
            }
            SS_ISeq_u4MasterInitComplete = SS_ISEQ_u4CHECKVAL2;
            SS_CpuCore_snooze();
        }

        /* スレーブコア1 */
    }
    else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE1)
    {

        /* ECC対策の初期化 */
        SS_ISeq_u4MasterInitComplete = SS_ISEQ_u4CHECKVAL1;

        /* バリア同期変数の初期化が完了するまで待つ */
        /*	・待ち処理の判定文でSS_ISeq_u4MasterInitCompleteのRAMチェック(パターン2) */
        while (SS_ISeq_u4MasterInitComplete != SS_ISEQ_u4CHECKVAL2)
        {
            SS_CpuCore_snooze();
        }
        SS_ISeq_u4InitWaitPass_1 = SS_ISEQ_u4WAIT_PASSED;

        /* スレーブコア2 */
#if (SS_USE_CORE_COUNT >= 3u)
    }
    else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE2)
    {

        /* ECC対策の初期化 */
        SS_ISeq_u4MasterInitComplete = SS_ISEQ_u4CHECKVAL1;

        /* バリア同期変数の初期化が完了するまで待つ */
        /* ・待ち処理の判定文でSS_ISeq_u4MasterInitCompleteのRAMチェック(パターン2) */
        while (SS_ISeq_u4MasterInitComplete != SS_ISEQ_u4CHECKVAL2)
        {
            SS_CpuCore_snooze();
        }
        SS_ISeq_u4InitWaitPass_2 = SS_ISEQ_u4WAIT_PASSED;
#endif /* SS_USE_CORE_COUNT >= 3u */

        /* スレーブコア3 */
#if (SS_USE_CORE_COUNT >= 4u)
    }
    else if (u4_CoreId == SS_CPUCORE_u4SLAVECORE3)
    {

        /* ECC対策の初期化 */
        SS_ISeq_u4MasterInitComplete = SS_ISEQ_u4CHECKVAL1;

        /* バリア同期変数の初期化が完了するまで待つ */
        /* ・待ち処理の判定文でSS_ISeq_u4MasterInitCompleteのRAMチェック(パターン2) */
        while (SS_ISeq_u4MasterInitComplete != SS_ISEQ_u4CHECKVAL2)
        {
            SS_CpuCore_snooze();
        }
        SS_ISeq_u4InitWaitPass_3 = SS_ISEQ_u4WAIT_PASSED;
#endif /* SS_USE_CORE_COUNT >= 4u */
    }
    else
    {
        /* 不正なコアID */
        /* Nothing to do */
    }

    return;
}
#endif

/**---------------------------------------------------------------------------
 * [Format]		void SS_ISeq_syncCores(uint16 u2_syncID)
 * [Function]	Synchronize Cores
 * [Arguments]	uint16 u2_syncID : Unique synchronize ID
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_CORE_COUNT >= 2u)
void SS_ISeq_syncCores(uint16 u2_syncID)
{
    uint32        u4_checkVal;
    SS_CoreIdType cid;

    u4_checkVal = ((uint32)(~((uint32)u2_syncID << SS_ISEQ_u4SHIFTCOUNTVAL)) & SS_ISEQ_u4SHIFTMASKVAL) | (uint32)u2_syncID;

    cid = SS_CpuCore_getCoreID();

    if (cid == SS_CPUCORE_u4MASTERCORE)
    {
        /* 【マスターコア】								*/
        /*	 <step1> 各コアの到達フラグ更新を待つ		*/
        while (1)
        {
            if (SS_ISeq_u4SyncCheck_1 == u4_checkVal)
            {
#if (SS_USE_CORE_COUNT >= 3u)
                if (SS_ISeq_u4SyncCheck_2 == u4_checkVal)
#endif
                {
#if (SS_USE_CORE_COUNT >= 4u)
                    if (SS_ISeq_u4SyncCheck_3 == u4_checkVal)
#endif
                    {
                        break;
                    }
                }
            }
            SS_CpuCore_snooze();
        }

        /*	 <step2> 各コアの到達フラグをクリア			*/
        SS_ISeq_u4SyncCheck_1 = SS_ISEQ_u4INITVAL;
#if (SS_USE_CORE_COUNT >= 3u)
        SS_ISeq_u4SyncCheck_2 = SS_ISEQ_u4INITVAL;
#endif
#if (SS_USE_CORE_COUNT >= 4u)
        SS_ISeq_u4SyncCheck_3 = SS_ISEQ_u4INITVAL;
#endif
    }
    else if (cid == SS_CPUCORE_u4SLAVECORE1)
    {
        /* 【スレーブコア】								*/
        /*	 <step1> 自コアの到達フラグ更新				*/
        SS_ISeq_u4SyncCheck_1 = u4_checkVal;

        /*	 <step2> 自コアの到達フラグをクリアを待つ	*/
        while (SS_ISeq_u4SyncCheck_1 != SS_ISEQ_u4INITVAL)
        {
            SS_CpuCore_snooze();
        }

#if (SS_USE_CORE_COUNT >= 3u)
    }
    else if (cid == SS_CPUCORE_u4SLAVECORE2)
    {
        /* 【スレーブコア】								*/
        /*	 <step1> 自コアの到達フラグ更新				*/
        SS_ISeq_u4SyncCheck_2 = u4_checkVal;

        /*	 <step2> 自コアの到達フラグをクリアを待つ	*/
        while (SS_ISeq_u4SyncCheck_2 != SS_ISEQ_u4INITVAL)
        {
            SS_CpuCore_snooze();
        }

#endif
#if (SS_USE_CORE_COUNT >= 4u)
    }
    else if (cid == SS_CPUCORE_u4SLAVECORE3)
    {
        /* 【スレーブコア】								*/
        /*	 <step1> 自コアの到達フラグ更新				*/
        SS_ISeq_u4SyncCheck_3 = u4_checkVal;

        /*	 <step2> 自コアの到達フラグをクリアを待つ	*/
        while (SS_ISeq_u4SyncCheck_3 != SS_ISEQ_u4INITVAL)
        {
            SS_CpuCore_snooze();
        }

#endif
    }
    else
    {
        /* 不正なコアID */
        /* Nothing to do */
    }

    return;
}
#endif

/**---------------------------------------------------------------------------
 * [Format]		void SS_ISeq_bSync(uint16 u2_syncID)
 * [Function]	コア間バリア同期 (コア間同期リセット判定あり)
 * [Arguments]	uint16 u2_syncID : Unique synchronize ID
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
static void SS_ISeq_bSync(uint16 u2_syncID)
{
    SS_ISeq_syncCores(u2_syncID);
#if (SS_USE_CORE_COUNT >= 2u)
    SS_ResetM_check();
#endif
    SS_Error_check();
    SS_ISeq_syncCores(~u2_syncID);

    return;
}

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Pm_requestUp(void)
 * [Function]	Request to stay for UP Phase
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON)) && (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC))
void SS_Pm_requestUp(void)
{
    SS_ISeq_u4UpReq = SS_REQUEST_EXIST;

    return;
}
#endif /* (((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON)) && (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)) */

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Pm_releaseUp(void)
 * [Function]	Request to release from UP Phase
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON)) && (SS_MM_ARBITRATION == SS_MM_ARBITRATION_EVENT))
void SS_Pm_releaseUp(void)
{
    SS_ISeq_u4UpReq = SS_REQUEST_NONE;

    return;
}
#endif /* (((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON)) && (SS_MM_ARBITRATION == SS_MM_ARBITRATION_EVENT)) */

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Pm_transit(void)
 * [Function]	Request to transit State
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON)) && (SS_MM_ARBITRATION == SS_MM_ARBITRATION_EVENT))
void SS_Pm_transit(void)
{
    SS_Pm_DisableInterruptsCallout(SS_PM_u4REQSRC_TRANSIT);
    SS_ISeq_transit();
    SS_Pm_EnableInterruptsCallout(SS_PM_u4REQSRC_TRANSIT);

    return;
}
#endif /* (((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON)) && (SS_MM_ARBITRATION == SS_MM_ARBITRATION_EVENT)) */

/**---------------------------------------------------------------------------
 * [Format] 	void SS_ISeq_transit(void)
 * [Function]	Transit State
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if ((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON))
static void SS_ISeq_transit(void)
{
    SS_RequestType u4_Req;

    
    u4_Req = SS_ISeq_getUpReq();
    if (u4_Req == SS_REQUEST_NONE)
    {
#if (SS_USE_SHUTDOWN == STD_ON)
        SS_ISeq_shutdown();
#endif
    }

    SS_ISeq_clearUpReq();

    return;
}
#endif /* ((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON)) */

/**---------------------------------------------------------------------------
 * [Format] 	static void SS_ISeq_clearUpReq(void)
 * [Function]	UP要求のクリア
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if ((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON))
static void SS_ISeq_clearUpReq(void)
{
    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_CLRUPREQ_A);

    SS_CpuCore_entryMasterSection();
    {
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
        SS_ISeq_u4UpReq = SS_REQUEST_NONE;
#else  /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC) */
        SS_ISeq_u4UpReq = SS_REQUEST_EXIST;
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC) */
    }
    SS_CpuCore_exitMasterSection();

    SS_ISeq_syncCores(SS_ISEQ_u2SID_ISEQ_CLRUPREQ_B);

    return;
}
#endif /* ((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON)) */

/**---------------------------------------------------------------------------
 * [Format] 	static SS_RequestType SS_ISeq_getUpReq(void)
 * [Function]	Get request to stay for UP Phase
 * [Arguments]	None
 * [Return] 	Request to stay for UP Phase
 * [Notes]		Do not call before StartOS
 *--------------------------------------------------------------------------*/
#if ((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON))
static SS_RequestType SS_ISeq_getUpReq(void)
{
    SS_RequestType u4_UpReq;

    u4_UpReq = SS_ISeq_u4UpReq;
    if ((u4_UpReq != SS_REQUEST_NONE) && (u4_UpReq != SS_REQUEST_EXIST))
    {
        SS_Error_notify(SS_ERROR_DATA);
    }

    return u4_UpReq;
}
#endif /* ((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON)) */

/**---------------------------------------------------------------------------
 * [Format] 	boolean SS_ISeq_checkWakeup(void)
 * [Function]	Check for request of Wakeup
 * [Arguments]	None
 * [Return] 	Result of check
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_SLEEP == STD_ON)
void SS_ISeq_checkWakeupAndReSleep(void)
{
    SS_ISeq_u4WakeupRequest = SS_REQUEST_NONE;

    
    SS_Pm_wakeupCheckCallout();
    
    

    
    if (SS_ISeq_u4WakeupRequest == SS_REQUEST_EXIST)
    {
        /* Nothing to do */
    }
    else if (SS_ISeq_u4WakeupRequest == SS_REQUEST_NONE)
    {
        SS_MCALISeq_initMcu();

        
        SS_Pm_reSleepCallout();
        

        /* TPcsw_SS_ISeq_resleep_if0 */
        SS_MCALISeq_goReStandby();
        /* TPcsw_SS_ISeq_resleep_endif */

        /* 上の行で処理は終わるはずで、ここまで来たら異常扱い */
        SS_Error_ResetCallout();
    }
    else
    {
        SS_Error_ResetCallout();
    }

    return;
}
#endif /* (SS_USE_SLEEP == STD_ON) */

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Pm_requestWakeup(void)
 * [Function]	Request for wakeup
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if (SS_USE_SLEEP == STD_ON)
void SS_Pm_requestWakeup(void)
{
    SS_ISeq_u4WakeupRequest = SS_REQUEST_EXIST;

    return;
}
#endif /* (SS_USE_SLEEP == STD_ON) */

/**---------------------------------------------------------------------------
 * [Format] 	void SS_ISeq_shutdown(void)
 * [Function]	Call Shutdown Hook
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if ((SS_USE_SHUTDOWN == STD_ON) && (SS_USE_UP == STD_ON))
void SS_ISeq_shutdown(void)
{
    SS_ISeq_syncCores(SS_ISEQ_u2SID_SHUTDOWN_REQ_A);
    
    SS_Pm_DisableInterruptsCallout(SS_PM_u4REQSRC_POWEROFF);
    

    SS_ISeq_syncCores(SS_ISEQ_u2SID_SHUTDOWN_REQ_B);
    
    SS_Pm_shutdownCallout();
    
    SS_ISeq_syncCores(SS_ISEQ_u2SID_SHUTDOWN_REQ_C);

    {
#if (SS_USE_CORE_COUNT >= 2u)
        SS_CoreIdType u4_CoreId;
        u4_CoreId = SS_CpuCore_getCoreID();
        if (u4_CoreId == SS_CPUCORE_u4MASTERCORE)
#endif
        {
            SS_Error_ResetCallout();
        }
#if (SS_USE_CORE_COUNT >= 2u)
        else
        {
            while (1)
            {
                ; /* 無限ループ */
            }
        }
#endif
    }
}
#endif /* (SS_USE_SHUTDOWN == STD_ON) */

/**---------------------------------------------------------------------------
 * [Format] 	void SS_Pm_mainFunction(void)
 * [Function]	定期調停用の状態遷移処理を実行
 * [Arguments]	None
 * [Return] 	None
 * [Notes]		None
 *--------------------------------------------------------------------------*/
#if ((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON))
#if (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC)
void SS_Pm_mainFunction(void)
{
    
    SS_Pm_preArbitrationCallout();
    

    SS_ISeq_transit();

    return;
}
#endif /* (SS_MM_ARBITRATION == SS_MM_ARBITRATION_PERIODIC) */
#endif /* ((SS_USE_MODE == STD_OFF) && (SS_USE_UP == STD_ON)) */
