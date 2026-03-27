/**
 * \file  Hsm_82_CycurHsm_Cfg.c
 * \copyright  DENSO Corporation 2022
*/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "Std_Types.h"
#include "Hsm_82_CycurHsm_Cfg.h"

#include "gpt_drv_frt.h"

/* #if (USR_USE_OSTIMER_ONE == STD_ON) */
#include "Os.h"
/* #endif */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define HSM_82_CYCURHSM_CFG_TIMER_DEV (1000U * GPT_FRT_1US) /* 1/80[us] -> 1[ms] */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Internal Functions                                                       */
/*--------------------------------------------------------------------------*/
#if (USR_HSM_SETTINR_RAM == STD_ON)
#pragma ghs section text = ".P_RAM_RPGEVTHK"
/******************************************************************/
/* Hsm_82_CycurHsm_GetResourceRAM */
/******************************************************************/
void Hsm_82_CycurHsm_GetResourceRAM(void)
{
    /* -- UserCode Start ------------- */
    /* Example: SuspendAllInterrupts(); */
    return;
    /* -- UserCode End   ------------- */
}

/******************************************************************/
/* Hsm_82_CycurHsm_ReleaseResourceRAM */
/******************************************************************/
void Hsm_82_CycurHsm_ReleaseResourceRAM(void)
{
    /* -- UserCode Start ------------- */
    /* Example: ResumeAllInterrupts(); */
    return;
    /* -- UserCode End   ------------- */
}

/******************************************************************/
/* Hsm_82_CycurHsm_GetCounterValueRAM */
/******************************************************************/
void Hsm_82_CycurHsm_GetCounterValueRAM(uint32 * value)
{
    /* -- UserCode Start ------------- */
    /* Example: (void)GetCounterValue(0, &value); */
    *value = 0; /*TBD*/
    return;
    /* -- UserCode End   ------------- */
}

/******************************************************************/
/* Hsm_82_CycurHsm_GetElapsedCounterValueRAM */
/******************************************************************/
void Hsm_82_CycurHsm_GetElapsedCounterValueRAM(uint32 startvalue, uint32 * elapsedvalue)
{
    /* -- UserCode Start ------------- */
    /* Example: (void)GetElapsedValue(0, &startvalue, elapsedvalue); */
    *elapsedvalue = 0; /*TBD*/
    return;
    /* -- UserCode End   ------------- */
}

/******************************************************************/
/* Hsm_82_CycurHsm_Callout_ErrorRAM */
/******************************************************************/
void Hsm_82_CycurHsm_Callout_ErrorRAM(void)
{
    /* -- UserCode Start ------------- */
    while(1){}
    return;
    /* -- UserCode End   ------------- */
}
#pragma ghs section text = default
#endif

/*--------------------------------------------------------------------------*/
/* External Functions                                                       */
/*--------------------------------------------------------------------------*/
#define CRYPTO_82_HSM_START_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"

/******************************************************************/
/* Hsm_82_CycurHsm_GetResource0 */
/******************************************************************/
void Hsm_82_CycurHsm_GetResource0(void)
{
    /* SECTODO: 排他制御の開始を実装してください。 ※並列でSEC処理が走らない場合には実装不要です。 */
    /* -- UserCode Start ------------- */
    /* Example: SuspendAllInterrupts(); */
    SuspendAllInterrupts();
    return;
    /* -- UserCode End   ------------- */
}

/******************************************************************/
/* Hsm_82_CycurHsm_ReleaseResource0 */
/******************************************************************/
void Hsm_82_CycurHsm_ReleaseResource0(void)
{
    /* SECTODO: 排他制御の終了を実装してください。 ※並列でSEC処理が走らない場合には実装不要です。 */
    /* -- UserCode Start ------------- */
    /* Example: ResumeAllInterrupts(); */
    ResumeAllInterrupts();
    return;
    /* -- UserCode End   ------------- */
}

/******************************************************************/
/* Hsm_82_CycurHsm_GetCounterValue0 */
/******************************************************************/
void Hsm_82_CycurHsm_GetCounterValue0(uint32 * value)
{
    /* SECTODO: カウンタ取得処理を実装してください。カウンタのLSBは1msです。 */
    /* SECTODO: 本関数で取得できる最大値は (4294967295/ HSM_82_CYCURHSM_CFG_TIMER_DEV)[ms] となります。 */
    /* -- UserCode Start ------------- */
    /* Example: (void)GetCounterValue(0, &value); */
    *value = (uint32)u4_g_Gpt_FrtGetUsElapsed(NULL_PTR);
    *value = (uint32)(*value / HSM_82_CYCURHSM_CFG_TIMER_DEV);
    return;
    /* -- UserCode End   ------------- */
}

/******************************************************************/
/* Hsm_82_CycurHsm_GetElapsedCounterValue0 */
/******************************************************************/
void Hsm_82_CycurHsm_GetElapsedCounterValue0(uint32 startvalue, uint32 * elapsedvalue)
{
    /* SECTODO: 経過カウンタ取得処理を実装してください。カウンタのLSBは1msです。 */
    /* SECTODO: 経過時間が (4294967295/ HSM_82_CYCURHSM_CFG_TIMER_DEV)[ms] を超過する場合、正しく値を取得できない点に注意ください。 */
    /* -- UserCode Start ------------- */
    /* Example: (void)GetElapsedValue(0, &startvalue, elapsedvalue); */
    uint32 EndValue;
    uint32 TimeDiff;
    EndValue = (uint32)u4_g_Gpt_FrtGetUsElapsed(NULL_PTR);
    startvalue = (uint32)(startvalue * HSM_82_CYCURHSM_CFG_TIMER_DEV);
    TimeDiff = (uint32)((EndValue - startvalue) / HSM_82_CYCURHSM_CFG_TIMER_DEV); /* EndValue - startvalue < 0の際にラップアラウンドしますが問題ありません。（CERT-INT30） */
    (*elapsedvalue) = TimeDiff;
    return;
    /* -- UserCode End   ------------- */
}

#if (USR_HSM_RESETTING_HSMCONF == STD_ON)
/******************************************************************/
/* Hsm_82_CycurHsm_GetResource1 */
/******************************************************************/
void Hsm_82_CycurHsm_GetResource1(void)
{
    /* -- UserCode Start ------------- */
    /* Example: SuspendAllInterrupts(); */
    return;
    /* -- UserCode End   ------------- */
}

/******************************************************************/
/* Hsm_82_CycurHsm_ReleaseResource1 */
/******************************************************************/
void Hsm_82_CycurHsm_ReleaseResource1(void)
{
    /* -- UserCode Start ------------- */
    /* Example: ResumeAllInterrupts(); */
    return;
    /* -- UserCode End   ------------- */
}

/******************************************************************/
/* Hsm_82_CycurHsm_GetCounterValue1 */
/******************************************************************/
void Hsm_82_CycurHsm_GetCounterValue1(uint32 * value)
{
#if (USR_USE_OSTIMER_ONE == STD_ON) 
    (void)GetCounterValue(USR_OSTIMER_ID, value);
#else
    /* -- UserCode Start ------------- */
    *value = 0; /*Sample*/
    /* -- UserCode End   ------------- */
#endif
    return;
}

/******************************************************************/
/* Hsm_82_CycurHsm_GetElapsedCounterValue1 */
/******************************************************************/
void Hsm_82_CycurHsm_GetElapsedCounterValue1(uint32 startvalue, uint32 * elapsedvalue)
{
#if (USR_USE_OSTIMER_ONE == STD_ON) 
    (void)GetElapsedValue(USR_OSTIMER_ID, &startvalue, elapsedvalue);
#else
    /* -- UserCode Start ------------- */
    *elapsedvalue = 0; /*Sample*/
    /* -- UserCode End   ------------- */
#endif
    return;
}
#endif

/******************************************************************/
/* Hsm_82_CycurHsm_Callout_ClockConfig */
/******************************************************************/
void Hsm_82_CycurHsm_Callout_ClockConfig(void)
{
    /* SECTODO: HSMのクロック分周を設定しなおす場合に実装してください。 なお、TVIIのCycurHSMはクロック分周の設定に対応していますが、RH850とTC3xは非対応です。 */
    /* -- UserCode Start ------------- */
    /* Example: (void)ecy_HSM_ClockConfigure( number ); */
    return;
    /* -- UserCode End   ------------- */
}

/******************************************************************/
/* Hsm_82_CycurHsm_Callout_Error */
/******************************************************************/
void Hsm_82_CycurHsm_Callout_Error(void)
{
    /* SECTODO: CycurHsmからエラーが通知された場合のユーザー処理を実装ください。 */
    /* -- UserCode Start ------------- */
    /* Example:
    unit32 Error;
    Error = ecy_hsm_IpcDrv_GetHsmStatus();
    If (Error != 0 )
    {
        store Error info
    }
    */
    while(1){}
    /* return; */
    /* -- UserCode End   ------------- */
}

/******************************************************************/
/* Hsm_82_CycurHsm_Callout_WaitForMode */
/******************************************************************/
#if (USR_HSM_WAITFORMODEAPPL_DOWHILE == STD_ON)
void Hsm_82_CycurHsm_Callout_WaitForMode(void)
{
    /* SECTODO: ecy_HSM_WaitForMode()の完了待ち中に実行したい任意の処理を実装してください。 */
    /* -- UserCode Start ------------- */
    /* Example: Watchdog Clear         */
    return;
    /* -- UserCode End   ------------- */
}
#endif

/******************************************************************/
/* Hsm_82_CycurHsm_Callout_WaitForInitialKeyRead */
/******************************************************************/
#if (USR_CRYPTO_DRIVER == USE_CRYPTO_82_HSM)
void Hsm_82_CycurHsm_Callout_WaitForInitialKeyRead(void)
{
    /* SECTODO: 鍵読み出しの完了待ち中に実行したい任意の処理を実装してください。 */
    /* -- UserCode Start ------------- */
    /* Example: Watchdog Clear         */
    return;
    /* -- UserCode End   ------------- */
}
#endif

#define CRYPTO_82_HSM_STOP_SEC_CODE
#include "Crypto_82_Hsm_MemMap.h"
/*--------------------------------------------------------------------------*/
/* History                                                                  */
/*  Version    :Date       :Description                                     */
/*  1.0.0      :yyyy/mm/dd :Create new                xxx                   */
/*--------------------------------------------------------------------------*/
/**** End of File ***********************************************************/
