/*****************************************************************************
 *	Copyright DENSO Corporation. All rights reserved.
 ****************************************************************************/
/*****************************************************************************
 * [File Name]		SS_HSTm.c
 * [Module]			HSTm
 * [Function]		ハードスリープタイマ (ハード操作部)
 * [Notes]			None
 ****************************************************************************/

/*----------------------------------------------------------------------------
 *		Headers
 *--------------------------------------------------------------------------*/
#include <stdint.h>
#include <Std_Types.h>
#include <SS_TYPE.h>
#include <SS_Internal.h>
#if (SS_USE_UP == STD_ON)
#include <Os.h>
#endif

#include <SS_MemmapSdaDisableB_Env.h>
#include <SS_Memmap_Env.h>
#include <SS_MemmapSdaDisableE_Env.h>

#include <SS_MemmapSdaSelectB_Env.h>
#include <SS_HSTm.h>
#include <SS_CpuCore.h>

#include <SS_MemmapSdaSelectE_Env.h>
/*----------------------------------------------------------------------------
 *		Symbols
 *--------------------------------------------------------------------------*/
typedef struct REG_ST_SS_HSTM_TAUJ
{
    uint32 u4CDR0;          /* 0x00 */
    uint32 u4CDR1;          /* 0x04 */
    uint32 u4CDR2;          /* 0x08 */
    uint32 u4CDR3;          /* 0x0C */
    uint32 u4CNT0;          /* 0x10 */
    uint32 u4CNT1;          /* 0x14 */
    uint32 u4CNT2;          /* 0x18 */
    uint32 u4CNT3;          /* 0x1C */
    uint8  u1CMUR0;         /* 0x20 */
    uint8  u1Reserved21[3]; /* 0x21 */
    uint8  u1CMUR1;         /* 0x24 */
    uint8  u1Reserved25[3]; /* 0x25 */
    uint8  u1CMUR2;         /* 0x28 */
    uint8  u1Reserved29[3]; /* 0x29 */
    uint8  u1CMUR3;         /* 0x2C */
    uint8  u1Reserved2D[3]; /* 0x2D */
    uint8  u1CSR0;          /* 0x30 */
    uint8  u1Reserved31[3]; /* 0x31 */
    uint8  u1CSR1;          /* 0x34 */
    uint8  u1Reserved35[3]; /* 0x35 */
    uint8  u1CSR2;          /* 0x38 */
    uint8  u1Reserved39[3]; /* 0x39 */
    uint8  u1CSR3;          /* 0x3C */
    uint8  u1Reserved3D[3]; /* 0x3D */
    uint8  u1CSC0;          /* 0x40 */
    uint8  u1Reserved41[3]; /* 0x41 */
    uint8  u1CSC1;          /* 0x44 */
    uint8  u1Reserved45[3]; /* 0x45 */
    uint8  u1CSC2;          /* 0x48 */
    uint8  u1Reserved49[3]; /* 0x49 */
    uint8  u1CSC3;          /* 0x4C */
    uint8  u1Reserved4D[3]; /* 0x4D */
    uint8  u1TE;            /* 0x50 */
    uint8  u1Reserved51[3]; /* 0x51 */
    uint8  u1TS;            /* 0x54 */
    uint8  u1Reserved55[3]; /* 0x55 */
    uint8  u1TT;            /* 0x58 */
    uint8  u1Reserved59[3]; /* 0x59 */
    uint8  u1TO;            /* 0x5C */
    uint8  u1Reserved5D[3]; /* 0x5D */
    uint8  u1TOE;           /* 0x60 */
    uint8  u1Reserved61[3]; /* 0x61 */
    uint8  u1TOL;           /* 0x64 */
    uint8  u1Reserved65[3]; /* 0x65 */
    uint8  u1RDT;           /* 0x68 */
    uint8  u1Reserved69[3]; /* 0x69 */
    uint8  u1RSF;           /* 0x6C */
    uint8  u1Reserved6D[3]; /* 0x6D */
    uint32 u4Reserved70[4]; /* 0x70 */
    uint16 u2CMOR0;         /* 0x80 */
    uint16 u2Reserved82;    /* 0x82 */
    uint16 u2CMOR1;         /* 0x84 */
    uint16 u2Reserved86;    /* 0x86 */
    uint16 u2CMOR2;         /* 0x88 */
    uint16 u2Reserved8A;    /* 0x8A */
    uint16 u2CMOR3;         /* 0x8C */
    uint16 u2Reserved8E;    /* 0x8E */
    uint16 u2TPS;           /* 0x90 */
    uint16 u2Reserved92;    /* 0x92 */
    uint8  u1BRS;           /* 0x94 */
    uint8  u1Reserved95[3]; /* 0x95 */
    uint8  u1TOM;           /* 0x98 */
    uint8  u1Reserved99[3]; /* 0x99 */
    uint8  u1TOC;           /* 0x9C */
    uint8  u1Reserved9D[3]; /* 0x9D */
    uint8  u1RDE;           /* 0xA0 */
    uint8  u1ReservedA1[3]; /* 0xA1 */
    uint8  u1RDM;           /* 0xA4 */
    uint8  u1ReservedA5[3]; /* 0xA5 */
    uint32 u4ReservedA8[2]; /* 0xA8 */
} REG_ST_SS_HSTM_TAUJ;

#define REG_ptTAUJn ((volatile REG_ST_SS_HSTM_TAUJ *)((uintptr_t)0xFFE81000UL)) /* TAUJ3_base */

#define REG_WUFMSK0_A2 (*(volatile uint32 *)((uintptr_t)0xFF98E024UL)) /* WUFMSK0_A2 */
#define REG_WUF0_A2    (*(volatile uint32 *)((uintptr_t)0xFF98E020UL)) /* WUF0_A2 */
#define REG_WUFC0_A2   (*(volatile uint32 *)((uintptr_t)0xFF98E028UL)) /* WUFC0_A2 */

/* HST's pre-scaller */
#define SS_HSTM_u1PRS_CK0 (0U)
#define SS_HSTM_u1PRS_CK1 (1U)
#define SS_HSTM_u1PRS_CK2 (2U)
#define SS_HSTM_u1PRS_CK3 (3U)

/* HST's timer channel */
#define SS_HSTM_u1TAUJ_CH0 (0U)
#define SS_HSTM_u1TAUJ_CH1 (1U)
#define SS_HSTM_u1TAUJ_CH2 (2U)

#if (SS_TARGETDEVICE == SS_U2A16)
#define SS_HSTM_u1PRS     (SS_HSTM_u1PRS_CK3)
#define SS_HSTM_u1TAUJ_CH (SS_HSTM_u1TAUJ_CH0)

#elif (SS_TARGETDEVICE == SS_U2A6)
#define SS_HSTM_u1PRS     (SS_HSTM_u1PRS_CK1)
#define SS_HSTM_u1TAUJ_CH (SS_HSTM_u1TAUJ_CH1)

#endif

/* RegSleepTimeのLSB */
#define SS_HSTM_u4REGSLEEP_SRCCLK (240UL) /* 240kHz */
#define SS_HSTM_u4REGSLEEP_DIV    (1UL)
#define SS_HSTM_u2PRS_DIV         (0x0000U) /* TAUJnPRSm設定値 PCLK/2^0 */
#define VAL_u1TAUJnCMUR_FALL      (0x00U)   /* Falling edge */

/* Timer Ch for TE */
#define VAL_u1TAUJnTE_DISABLE (0x00U)

/* Timeout value for updating the status registers of count enable status register for timer stop */
#define SS_HSTM_u4TIMEOUT_COUNT (240U)

#if (SS_HSTM_u1TAUJ_CH == SS_HSTM_u1TAUJ_CH0)
/* Register value for timer */
#define VAL_u1TAUJnTS_ENABLE   (0x01U) /* Timer Ch for TS */
#define VAL_u1TAUJnTT_STOP     (0x01U) /* Timer Ch for TT */
#define VAL_u1TAUJnTE_ENABLE   (0x01U) /* Timer Ch for TE */
#define MSK_u1TAUJnTE          (0x01U)
#define MSK_u1TAUJnRDE_DISABLE (0x0EU) /* disables simultaneous */
#define MSK_u1TAUJnRDM_DISABLE (0x0EU) /* disables simultaneous */
/* Replace register name */
#define REG_u4TAUJnCDRX  (REG_ptTAUJn->u4CDR0)
#define REG_u4TAUJnCNTX  (REG_ptTAUJn->u4CNT0)
#define REG_u2TAUJnCMORX (REG_ptTAUJn->u2CMOR0)
#define REG_u1TAUJnCMURX (REG_ptTAUJn->u1CMUR0)

/* Wakeup flag bit */
#define MSK_u4WUF0_A2_TAUJn        (0x00000080UL)
#define VAL_u4WUF0_A2_TAUJn_ENABLE (0x00000080UL)
#define VAL_u4WUFC0_A2_TAUJn       (0x00000080UL)
#define VAL_u4WUFMSK0_A2_TAUJn     (0x00000080UL)

#elif (SS_HSTM_u1TAUJ_CH == SS_HSTM_u1TAUJ_CH1)
/* Register value for timer */
#define VAL_u1TAUJnTS_ENABLE       (0x02U) /* Timer Ch for TS */
#define VAL_u1TAUJnTT_STOP         (0x02U) /* Timer Ch for TT */
#define VAL_u1TAUJnTE_ENABLE       (0x02U) /* Timer Ch for TE */
#define MSK_u1TAUJnTE              (0x02U)
#define MSK_u1TAUJnRDE_DISABLE     (0x0DU) /* disables simultaneous */
#define MSK_u1TAUJnRDM_DISABLE     (0x0DU) /* disables simultaneous */
/* Replace register name */
#define REG_u4TAUJnCDRX            (REG_ptTAUJn->u4CDR1)
#define REG_u4TAUJnCNTX            (REG_ptTAUJn->u4CNT1)
#define REG_u2TAUJnCMORX           (REG_ptTAUJn->u2CMOR1)
#define REG_u1TAUJnCMURX           (REG_ptTAUJn->u1CMUR1)

/* Wakeup flag bit */
#define MSK_u4WUF0_A2_TAUJn        (0x00000100UL)
#define VAL_u4WUF0_A2_TAUJn_ENABLE (0x00000100UL)
#define VAL_u4WUFC0_A2_TAUJn       (0x00000100UL)
#define VAL_u4WUFMSK0_A2_TAUJn     (0x00000100UL)

#else
/* invalid config */
#error "Invalid channel number"
#endif

/* Wakeup flag bit */
#define SS_HSTM_u4WUFBIT (0x00000100UL)

/* Register value for pre-scaller */
#if (SS_HSTM_u1PRS == SS_HSTM_u1PRS_CK0)
#define VAL_u2TAUJnTPS_CLK  (SS_HSTM_u2PRS_DIV)
#define MSK_u2TAUJnTPS_CLK  (0xFFF0U)
#define VAL_u2TAUJnCMOR_CKS (0x0000U)

#elif (SS_HSTM_u1PRS == SS_HSTM_u1PRS_CK1)
#define VAL_u2TAUJnTPS_CLK  (SS_HSTM_u2PRS_DIV << 4U)
#define MSK_u2TAUJnTPS_CLK  (0xFF0FU)
#define VAL_u2TAUJnCMOR_CKS (0x4000U)

#elif (SS_HSTM_u1PRS == SS_HSTM_u1PRS_CK2)
#define VAL_u2TAUJnTPS_CLK  (SS_HSTM_u2PRS_DIV << 8U)
#define MSK_u2TAUJnTPS_CLK  (0xF0FFU)
#define VAL_u2TAUJnCMOR_CKS (0x8000U)

#elif (SS_HSTM_u1PRS == SS_HSTM_u1PRS_CK3)
#define VAL_u2TAUJnTPS_CLK         (SS_HSTM_u2PRS_DIV << 16U)
#define VAL_u1TAUJnBRS_DIV         (0x17U)
#define MSK_u2TAUJnTPS_CLK         (0x0FFFU)
#define VAL_u2TAUJnCMOR_CKS        (0xC000U)
#define SS_HSTM_u2PRESCAL_DIV_CALC (24U)

#endif
/*----------------------------------------------------------------------------
 *		Codes
 *--------------------------------------------------------------------------*/

#if (SS_USE_SLEEP == STD_ON)

/**---------------------------------------------------------------------------
 * [Format]		void SS_HSTm_start(uint32 u4RegTime)
 * [Function]	タイマ発火時間を指定し、タイマ動作を開始する
 * [Arguments]	u4RegTime : スリープ指定時間(レジスタ設定用LSB)
 * [Return]		None
 * [Notes]		
 *--------------------------------------------------------------------------*/

void SS_HSTm_start(uint32 u4RegTime)
{
    volatile uint8  u1Dummy;
    volatile uint16 u2TPS;
    uint32          u4Time;

    /* ●リロード値を RegSleepTime にする */
    REG_u4TAUJnCDRX = u4RegTime - 1UL; /* EDET_INT30 */

    /* ●ウェイクアップ要因有効化 */
    REG_WUFMSK0_A2 &= (~SS_HSTM_u4WUFBIT);

#if (SS_USE_UP == STD_ON)
    SuspendAllInterrupts(); /* DI */
#endif

    /* ●TAUJxのプリスケーラーを設定 */
    u2TPS = REG_ptTAUJn->u2TPS;
    u2TPS &= MSK_u2TAUJnTPS_CLK;
    u2TPS |= VAL_u2TAUJnTPS_CLK;
    REG_ptTAUJn->u2TPS = u2TPS;

#if (SS_HSTM_u1PRS == SS_HSTM_u1PRS_CK3)
    REG_ptTAUJn->u1BRS = VAL_u1TAUJnBRS_DIV;
#endif

    REG_u2TAUJnCMORX = VAL_u2TAUJnCMOR_CKS;
    REG_u1TAUJnCMURX = VAL_u1TAUJnCMUR_FALL;

    /* ●TAUJxの一斉書き換えを禁止 */
    REG_ptTAUJn->u1RDE &= MSK_u1TAUJnRDE_DISABLE;
    REG_ptTAUJn->u1RDM &= MSK_u1TAUJnRDM_DISABLE;

    u1Dummy = REG_ptTAUJn->u1RDM; /* dummy read */
    SS_CpuCore_syncp();           /* syncp */

#if (SS_USE_UP == STD_ON)
    ResumeAllInterrupts(); /* EI */
#endif

    /* ●タイマ開始 */
    REG_ptTAUJn->u1TS = VAL_u1TAUJnTS_ENABLE;

    /* ●ステータスレジスタ更新待ち */
    u4Time = 0UL;
    while ((u4Time < SS_HSTM_u4TIMEOUT_COUNT) && (VAL_u1TAUJnTE_ENABLE != (REG_ptTAUJn->u1TE & MSK_u1TAUJnTE)))
    {
        u4Time++;
    }

    u1Dummy = REG_ptTAUJn->u1TE; /* dummy read */
    SS_CpuCore_syncp();          /* syncp */

    return;
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_HSTm_stop(void)
 * [Function]	ハードスリープタイマのタイマ動作を停止する
 * [Arguments]	None
 * [Return]		None
 * [Notes]		This Function must call in DI
 *--------------------------------------------------------------------------*/

void SS_HSTm_stop(void)
{
    volatile uint8 u1Dummy;
    uint32         u4Time;

    /* ●タイマ停止 */
    REG_ptTAUJn->u1TT = VAL_u1TAUJnTT_STOP;

    /* ●ステータスレジスタ更新待ち */
    u4Time = 0UL;
    while ((u4Time < SS_HSTM_u4TIMEOUT_COUNT) && (VAL_u1TAUJnTE_DISABLE != (REG_ptTAUJn->u1TE & MSK_u1TAUJnTE)))
    {
        u4Time++;
    }

    u1Dummy = REG_ptTAUJn->u1TE; /* dummy read */
    SS_CpuCore_syncp();          /* syncp */

    /* ●ウェイクアップ要因無効化 */
    REG_WUFMSK0_A2 |= SS_HSTM_u4WUFBIT;

    /* ●ウェイクアップ要因フラグをクリア */
    SS_HSTm_reload(0UL);

    return;
}

/**---------------------------------------------------------------------------
 * [Format]		uint32 SS_HSTm_getTime(uint32 u4AlarmPeriodCnt)
 * [Function]	前回リロードからの経過時間を返す。
 * [Arguments]	u4AlarmPeriodCnt : アラーム周期
 * [Return]		uint32 : スリープ経過時間(レジスタ値)
 * [Notes]		
 *--------------------------------------------------------------------------*/

uint32 SS_HSTm_getTime(uint32 u4AlarmPeriodCnt)
{
    uint32  u4RetVal;
    boolean bIsExpired;
    uint32  u4CounterGet1st;
    uint32  u4CounterGet2nd;

    /* カウント値#1を取得する */
    u4CounterGet1st = REG_u4TAUJnCNTX;

    /* タイマ満了フラグを取得する */
    bIsExpired = SS_HSTm_isExpired();

    /* カウント値#2を取得する */
    u4CounterGet2nd = REG_u4TAUJnCNTX;

    /* 1回目の取得時より、2回目の取得時のほうが大きかった場合 */
    /* ラップアラウンドしたとしてu4AlarmPeriodCntを加算する */
    if ((u4CounterGet1st < u4CounterGet2nd) || (bIsExpired == TRUE))
    {
        u4RetVal = REG_u4TAUJnCDRX - u4CounterGet2nd + u4AlarmPeriodCnt; /* EDET_INT30 */
    }
    else
    {
        u4RetVal = REG_u4TAUJnCDRX - u4CounterGet2nd; /* EDET_INT30 */
    }

    return (u4RetVal);
}

/**---------------------------------------------------------------------------
 * [Format]		boolean SS_HSTm_isExpired(void)
 * [Function]	スリープ時間満了確認
 * [Arguments]	None
 * [Return]		TRUE :	スリープ時間満了した
 *				FALSE :	スリープ時間満了していない
 * [Notes]		This Function must call in DI
 *--------------------------------------------------------------------------*/

boolean SS_HSTm_isExpired(void)
{
    boolean bRet; /* 戻り値 */

    bRet = FALSE;
    if ((REG_WUF0_A2 & MSK_u4WUF0_A2_TAUJn) == VAL_u4WUF0_A2_TAUJn_ENABLE)
    {
        bRet = TRUE;
    }

    return (bRet);
}

/**---------------------------------------------------------------------------
 * [Format]		void SS_HSTm_reload(uint32 u4AlarmPeriodCnt)
 * [Function]	アラーム周期の時間をリロードする
 * [Arguments]	u4AlarmPeriodCnt : アラーム周期
 * [Return]		None
 * [Notes]		None
 *--------------------------------------------------------------------------*/

void SS_HSTm_reload(uint32 u4AlarmPeriodCnt)
{
    volatile uint32 u4Dummy;

    REG_WUFC0_A2 = VAL_u4WUFC0_A2_TAUJn;

    u4Dummy = REG_WUFC0_A2; /* dummy read */
    SS_CpuCore_syncp();     /* syncp */

    return;
}

/**---------------------------------------------------------------------------
 * [Format]		uint32 SS_HSTm_convLsbRealToReg(uint32 u4RealTime)
 * [Function]	実時間（パッケージ適合LSB） → レジスタ設定用LSB変換
 * [Arguments]	uint32 u4RealTime : 変換前時間 (実時間（パッケージ適合LSB)
 * [Return]		uint32 : 変換後時間 (レジスタ設定用のLSB)
 * [Notes]		None
 *--------------------------------------------------------------------------*/

uint32 SS_HSTm_convLsbRealToReg(uint32 u4RealTime)
{
    uint64 u8ConvertedReg;

#if (SS_HSTM_u1PRS == SS_HSTM_u1PRS_CK3)
    u8ConvertedReg = ((uint64)u4RealTime * (SS_HSTM_u4REGSLEEP_SRCCLK / SS_HSTM_u2PRESCAL_DIV_CALC)) / SS_HSTM_u4REGSLEEP_DIV; /* EDET_INT30 */
#else
    u8ConvertedReg = ((uint64)u4RealTime * SS_HSTM_u4REGSLEEP_SRCCLK) / SS_HSTM_u4REGSLEEP_DIV; /* EDET_INT30 */
#endif

    return ((uint32)u8ConvertedReg);
}

/**---------------------------------------------------------------------------
 * [Format]		uint32 SS_HSTm_convLsbRegToReal(uint32 u4RegTime)
 * [Function]	レジスタ設定用LSB変換 → 実時間（パッケージ適合LSB）
 * [Arguments]	uint32 u4RegTime : 変換前時間 (レジスタ設定用のLSB)
 * [Return]		uint32 : 変換後時間 (実時間（パッケージ適合LSB）)
 * [Notes]		None
 *--------------------------------------------------------------------------*/

uint32 SS_HSTm_convLsbRegToReal(uint32 u4RegTime)
{
    uint64 u8ConvertedReal;

    u8ConvertedReal = ((uint64)u4RegTime * SS_HSTM_u4REGSLEEP_DIV) / SS_HSTM_u4REGSLEEP_SRCCLK;

    return ((uint32)u8ConvertedReal);
}

#endif /* (SS_USE_SLEEP == STD_ON) */
