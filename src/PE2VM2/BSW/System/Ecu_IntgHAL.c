/*****************************************************************************
 *  Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		Ecu_IntgHAL.c
 * [Module]			Int
 * [Function]		Int
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <v800_ghs.h>
#include <Std_Types.h>
#include <SS.h>

#include <Ecu_Memmap_SdaDisableB_env.h>
#include <Ecu_MemmapP.h>
#include <Ecu_IntgHAL.h>
#include <Ecu_IntgHAL_Cfg.h>
#include <Ecu_IntgHAL_Callout.h>
#include <Ecu_Int.h>

#if (SS_USE_LWH == SS_LWH_NONE)
#else
#include <ehvm.h>

#endif
#include <Ecu_Memmap_SdaDisableE_env.h>

/*----------------------------------------------------------------------------
 *		Types
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
#define REG_u4RESF (*(volatile uint32 *)0xFF988500UL)

#if (SS_USE_LWH == SS_LWH_NONE)
#define MSK_u4RESF_PON      (0x00000001UL)
#define MSK_u4RESF_OTHERRST (0x00100010UL) // DPSTOP,PON以外のリセット要因
#define MSK_u4RESF_DPSTP    (0x00008000UL)
#else
#define MSK_u4RESF_PON      (0x00000001UL)
#define MSK_u4RESF_OTHERRST (0x000375DCUL) // DPSTOP,PON以外のリセット要因
#define MSK_u4RESF_DPSTP    (0x00008000UL)
#endif

#define REG_u4WUF0_A0 (*(volatile uint32 *)0xFF98E000UL)
#define REG_u4WUF0_A1 (*(volatile uint32 *)0xFF98E010UL)
#define REG_u4WUF0_A2 (*(volatile uint32 *)0xFF98E020UL)

#define REG_u4PSW_regID ((int)5)
#define REG_u4PSW_selID ((int)0)

#define REG_u4FPSR_regID ((int)6)
#define REG_u4FPSR_selID ((int)0)

/* CU0と予約ビットが書き込み対象 */
#define MSK_u4PSW_CU0   (0xBC097F00UL)
#define VAL_u4PSW_CU0EN (0x00010000UL)

/* for Ecu_IntgHAL_setIntLevelMask */
#define REG_u4PLMR_regID ((int)14)
#define REG_u4PLMR_selID ((int)2)
#define MSK_u4PLMR       (0x0000001FUL)

#define REG_u1VLVF              (*(volatile uint8 *)0xFF983300UL)
#define REG_u1VLVFC             (*(volatile uint8 *)0xFF983308UL)
#define REG_u4VLVIKCPROT        (*(volatile uint32 *)0xFF983F40UL)
#define VAL_u1VLVFC             ((uint8)0x01U)
#define VAL_u4VLVIKCPROT_UNLOCK (0xA5A5A501UL)
#define VAL_u4VLVIKCPROT_LOCK   (0xA5A5A500UL)
#define MSK_u1VLVF              ((uint8)0x01U)

#define REG_u4SWARESA                   (*(volatile uint32 *)0xFF988410UL) /* SWARESA */
#define REG_u4RESKCPROT0                (*(volatile uint32 *)0xFF980F00UL) /* RESKCPROT0 */
#define VAL_u4SWARESA_APPLICATION_RESET (0x00000001UL)                     /* R_SWRESET */
#define VAL_u4RESKCPROT0_KCE_ENABLE     (0xA5A5A501UL)
#define VAL_u4RESKCPROT0_KCE_DISABLE    (0xA5A5A500UL)

/*----------------------------------------------------------------------------
 *		Variables
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------
 * [Format]	Ecu_Intg_BootCauseType Ecu_IntgHAL_getBootCause(void)
 * [Function]	enable FPU
 * [Arguments]	None
 * [Return]	ブート要因
 * [Notes]	None
 *--------------------------------------------------------------------------*/
Ecu_Intg_BootCauseType Ecu_IntgHAL_getBootCause(void)
{
    uint32                 u4RegVal_RESF;
    uint8                  u1RegVal_VLVF;
    Ecu_IntgHAL_WufType    stWUF;
    Ecu_Intg_BootCauseType u4RetVal;
    Std_ReturnType         u1RetVal;

#if (SS_USE_LWH == SS_LWH_NONE)
    u4RegVal_RESF = REG_u4RESF;
#else
    ehvm_reset_factor_t stEhvmResetFactor;

    // リセット要因レジスタの代わりに、ehvm_ifからリセット要因を受け取る。
    (void)ehvm_vmm_get_reset_factor(&stEhvmResetFactor);
//    u4RegVal_RESF = stEhvmResetFactor.category;
    u4RegVal_RESF = REG_u4RESF;
#endif

    u1RetVal = Ecu_IntgHAL_getWUF(&stWUF);
    if (u1RetVal != E_OK)
    {
        // 異常処理
    }

    u1RegVal_VLVF = REG_u1VLVF;

    u4RetVal = 0UL;

    if (((u4RegVal_RESF & MSK_u4RESF_PON) != 0UL) ||
        ((u1RegVal_VLVF & MSK_u1VLVF) != 0U))
    {
        u4RetVal = ECU_INTG_u4BTCAUSE_PON;
    }
    else if ((u4RegVal_RESF & MSK_u4RESF_OTHERRST) != 0UL)
    {
        u4RetVal = ECU_INTG_u4BTCAUSE_RESET;
    }
    else if ((u4RegVal_RESF & MSK_u4RESF_DPSTP) != 0UL)
    {
        if (((stWUF.u4WUF0_A0 & MSK_u4WUF0_A0_ANY) != 0UL) ||
            ((stWUF.u4WUF0_A1 & MSK_u4WUF0_A1_ANY) != 0UL) ||
            ((stWUF.u4WUF0_A2 & MSK_u4WUF0_A2_ANY) != 0UL))
        {
            u4RetVal |= ECU_INTG_u4BTCAUSE_WKUP_ANY;
        }
        if (((stWUF.u4WUF0_A0 & MSK_u4WUF0_A0_TMR) != 0UL) ||
            ((stWUF.u4WUF0_A1 & MSK_u4WUF0_A1_TMR) != 0UL) ||
            ((stWUF.u4WUF0_A2 & MSK_u4WUF0_A2_TMR) != 0UL))
        {
            u4RetVal |= ECU_INTG_u4BTCAUSE_WKUP_TMR;
        }
        if (u4RetVal == 0UL)
        {
            u4RetVal = ECU_INTG_u4BTCAUSE_WKUP_OTHS;
        }
    }
    else
    {
        u4RetVal = ECU_INTG_u4BTCAUSE_RESET;
    }

    return u4RetVal;
}

/**---------------------------------------------------------------------------
 * [Format]	Std_ReturnType Ecu_IntgHAL_getWUF(Ecu_IntgHAL_WufType *ptWUF)
 * [Function]	WUFの取得
 * [Arguments]	None
 * [Return]	WUFレジスタ値(構造体)
 * [Notes]	None
 *--------------------------------------------------------------------------*/
Std_ReturnType Ecu_IntgHAL_getWUF(Ecu_IntgHAL_WufType *ptWUF)
{

#if (SS_USE_LWH == SS_LWH_NONE)
    ptWUF->u4WUF0_A0 = REG_u4WUF0_A0;
    ptWUF->u4WUF0_A1 = REG_u4WUF0_A1;
    ptWUF->u4WUF0_A2 = REG_u4WUF0_A2;
#else
    ehvm_wakeup_factor_t stWakeUpFactor;

    /* WUFレジスタの代わりに、ehvm_ifからウェイクアップ要因を受け取る */
    (void)ehvm_vmm_get_wakeup_factor(EHVM_WAKEUP_FACTOR_SIZE_96, &stWakeUpFactor);
    ptWUF->u4WUF0_A0 = stWakeUpFactor.st1;
    ptWUF->u4WUF0_A1 = stWakeUpFactor.st2;
    ptWUF->u4WUF0_A2 = stWakeUpFactor.st3;

#endif

    return E_OK;
}

/**---------------------------------------------------------------------------
 * [Format]	boolean Ecu_IntgHAL_isImmShutdown(void)
 * [Function]	即時シャットダウン要因有無判定
 * [Arguments]	None
 * [Return]	即時シャットダウン要因有無
 * [Notes]	None
 *--------------------------------------------------------------------------*/
boolean Ecu_IntgHAL_isImmShutdown(void)
{
    boolean             bRet;
    Std_ReturnType      u1RetVal;
    Ecu_IntgHAL_WufType stWUF;

    u1RetVal = Ecu_IntgHAL_getWUF(&stWUF);
    if (u1RetVal != E_OK)
    {
        // 異常処理
    }

    bRet = Ecu_IntgHAL_isImmShutdownCallout(&stWUF);
    bRet |= Ecu_Intg_checkSTReset(ECU_INTG_ST_RESET_BY_FACTORY, FALSE);

    return bRet;
}

/**---------------------------------------------------------------------------
 * [Format]	void Ecu_IntgHAL_enableFpu(void)
 * [Function]	enable FPU
 * [Arguments]	None
 * [Return]	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
void Ecu_IntgHAL_enableFpu(void)
{
    volatile uint32 u4RegVal_PSW;

    u4RegVal_PSW = __STSR(REG_u4PSW_regID, REG_u4PSW_selID);
    u4RegVal_PSW &= ~MSK_u4PSW_CU0;
    u4RegVal_PSW |= VAL_u4PSW_CU0EN;
    __LDSR(REG_u4PSW_regID, REG_u4PSW_selID, u4RegVal_PSW);
    Ecu_Int_syncp();

    __LDSR(REG_u4FPSR_regID, REG_u4FPSR_selID, VAL_u4FPSR);
    Ecu_Int_syncp();

    return;
}

/**---------------------------------------------------------------------------
 * [Format]	void Ecu_IntgHAL_setIntLevelMask(uint8 u1PriorityLevel)
 * [Function]	割り込みレベルマスクのセット
 * [Arguments]	割込みレベルマスク値
 * [Return]	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
void Ecu_IntgHAL_setIntLevelMask(uint8 u1PriorityLevel)
{

    __LDSR(REG_u4PLMR_regID, REG_u4PLMR_selID, (unsigned int)u1PriorityLevel);
    Ecu_Int_syncp();

    return;
}

/**---------------------------------------------------------------------------
 * [Format]	uint8 Ecu_IntgHAL_getIntLevelMask(void)
 * [Function]	現在の割り込みレベルマスク値を取得
 * [Arguments]	None
 * [Return]	割込みレベルマスク値
 * [Notes]	None
 *--------------------------------------------------------------------------*/
uint8 Ecu_IntgHAL_getIntLevelMask(void)
{
    unsigned int u4RegVal_PLMR;

    u4RegVal_PLMR = __STSR(REG_u4PLMR_regID, REG_u4PLMR_selID);

    return ((uint8)(u4RegVal_PLMR & MSK_u4PLMR));
}

/**---------------------------------------------------------------------------
 * [Format]	void Ecu_IntgHAL_clearRAMV(void)
 * [Function]	RAM保持電圧低下フラグクリア処理
 * [Arguments]	None
 * [Return]	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
void Ecu_IntgHAL_clearRAMV(void)
{
    SS_CpuCore_entryMasterSection();
    {
#ifdef ECU_VM0
        /* Unlock registers */
        REG_u4VLVIKCPROT = VAL_u4VLVIKCPROT_UNLOCK;

        REG_u1VLVFC = VAL_u1VLVFC;

        /* Lock Registers */
        REG_u4VLVIKCPROT = VAL_u4VLVIKCPROT_LOCK;

        Ecu_Int_syncp();
#endif
#if ((SS_USE_UP == STD_ON) && (SS_USE_LWH == SS_LWH_NONE))
        /* Unlock registers */
        REG_u4VLVIKCPROT = VAL_u4VLVIKCPROT_UNLOCK;

        REG_u1VLVFC = VAL_u1VLVFC;

        /* Lock Registers */
        REG_u4VLVIKCPROT = VAL_u4VLVIKCPROT_LOCK;

        Ecu_Int_syncp();
#endif
    }
    SS_CpuCore_exitMasterSection();

    return;
}

/**---------------------------------------------------------------------------
 * [Format] void Ecu_IntgHAL_performSoftReset(void)
 * [Function]  Application Resetを行う
 * [Arguments] None
 * [Return]	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
void Ecu_IntgHAL_performSoftReset(void)
{
    while (1)
    {
#if (SS_USE_RESET == STD_ON)
        REG_u4RESKCPROT0 = VAL_u4RESKCPROT0_KCE_ENABLE;
        REG_u4SWARESA    = VAL_u4SWARESA_APPLICATION_RESET;
        REG_u4RESKCPROT0 = VAL_u4RESKCPROT0_KCE_DISABLE;
#endif /* SS_USE_RESET == SS_RESET_ON */
    }
}

/**---------------------------------------------------------------------------
 * [Format] void Ecu_IntgHAL_performHardReset(void)
 * [Function] System Resetを行う
 * [Arguments] None
 * [Return]	None
 * [Notes]	None
 *--------------------------------------------------------------------------*/
void Ecu_IntgHAL_performHardReset(void)
{
    SS_CpuCore_performReset();
}
